/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */


#include <ios.h>
#include <iosdebug.h>
#include <iostypes.h>
#include "thread.h"
#include "except.h"
#include "message.h"
//#include "memory.h"

#include <signal.h>

IOSMessageQueue __queues[IOS_MESSAGE_QUEUE_MAX];
IOSEventState __iosEventState[IOS_NUM_EVENTS];

#define CHECK_MESSAGE_QUEUE_ID(id) \
    if (((id) < 0) || ((id) >= IOS_MESSAGE_QUEUE_MAX)) {\
        rv = IOS_ERROR_INVALID; \
        goto end; \
    } else

#define CHECK_MESSAGE_QUEUE_FLAGS(flag) \
    if (((flag) != IOS_MESSAGE_BLOCK) && ((flag) != IOS_MESSAGE_NOBLOCK)) {\
        rv = IOS_ERROR_INVALID; \
        goto end; \
    } else

#define CHECK_MESSAGE_QUEUE_MASK(mq) \
    if ((mq)->maios) { \
        if (!((mq)->maios & (1 << __iosRunningThread->pid))) {\
            rv = IOS_ERROR_ACCESS; \
            goto end; \
        } \
    } else { \
        if ((mq)->owner != __iosRunningThread->pid) {\
            rv = IOS_ERROR_ACCESS; \
            goto end; \
        } \
    }

#define CHECK_MESSAGE_QUEUE_OWNER(mq) \
    if ((mq)->owner != __iosRunningThread->pid) {\
        rv = IOS_ERROR_ACCESS; \
        goto end; \
    } else

IOSMessageQueueId
iosCreateMessageQueue(IOSMessage *msgarray, u32 size, u32 pidMaios)
{
    IOSMessageQueueId rv;
    IOSMessageQueue *mq;


    /* Look for a free mq structure */
    for (rv = 0; rv < IOS_MESSAGE_QUEUE_MAX; ++rv) {
        if (__queues[rv].size == 0) {
            break;
        }
    }
    if (rv == IOS_MESSAGE_QUEUE_MAX) {
        rv = IOS_ERROR_MAX;
        goto end;
    }

    mq = __queues + rv;
    mq->emptyQ = (IOSThread *)&__iosThreadTail;
    mq->fullQ = (IOSThread *)&__iosThreadTail;
    mq->count = 0;
    mq->rptr = 0;
    mq->size = size;
    mq->buffer = msgarray;
    mq->maios = pidMaios;
    mq->owner = __iosRunningThread->pid;

end:
    return rv;
}


IOSError
iosDestroyMessageQueue(IOSMessageQueueId id)
{
    IOSError rv = IOS_ERROR_OK;
    IOSMessageQueue *mq;


    CHECK_MESSAGE_QUEUE_ID(id);

    mq = __queues + id;

    CHECK_MESSAGE_QUEUE_OWNER(mq);

    /* Mark the mq as available */
    mq->size = 0;

    /* Dispatch any threads blocked on this queue */
    /* XXXwheeler */

end:
    return rv;
}


IOSError
iosSendMessage(IOSMessageQueueId id, IOSMessage msg, u32 flag)
{
    IOSError rv = IOS_ERROR_OK;
    IOSMessageQueue *mq;
    u32 wptr;


    CHECK_MESSAGE_QUEUE_ID(id);
    CHECK_MESSAGE_QUEUE_FLAGS(flag);

    mq = __queues + id;

    CHECK_MESSAGE_QUEUE_MASK(mq);

    /* While mq is full */
    while (mq->count >= mq->size) {
        if (flag == IOS_MESSAGE_BLOCK) {
          DBG_PRINTF((dbg_fp,"iosSendMessage: queue is full. Blocking...\n"));
          __iosRunningThread->state = IOS_STATE_WAITING;
          __iosEnqueueAndYield(&mq->fullQ);
          DBG_PRINTF((dbg_fp,"iosSendMessage: woke up from being blocked...\n"));
        } else {
          rv = IOS_ERROR_QFULL;
          goto end;
        }
    }

    /* Compute next available slot and store message */
    wptr = mq->rptr + mq->count;
    if (wptr >= mq->size) wptr -= mq->size;
    mq->buffer[wptr] = msg;
    mq->count++;

    /* If a thread is blocked on this queue, start it */
    if (mq->emptyQ->next != NULL) {
      __iosRestartThread(&mq->emptyQ);
    }

end:
    return rv;
}


IOSError
iosJamMessage(IOSMessageQueueId id, IOSMessage msg, u32 flag)
{
    IOSError rv = IOS_ERROR_OK;
    IOSMessageQueue *mq;


    CHECK_MESSAGE_QUEUE_ID(id);
    CHECK_MESSAGE_QUEUE_FLAGS(flag);

    mq = __queues + id;

    CHECK_MESSAGE_QUEUE_MASK(mq);

    /* While mq is full */
    while (mq->count >= mq->size) {
        if (flag == IOS_MESSAGE_BLOCK) {
            __iosRunningThread->state = IOS_STATE_WAITING;
            __iosEnqueueAndYield(&mq->fullQ);
        } else {
            rv = IOS_ERROR_QFULL;
            goto end;
        }
    }

    /* Decrement for next available slot and store message */
    mq->rptr += (mq->size - 1);
    if (mq->rptr >= mq->size) mq->rptr -= mq->size;
    mq->buffer[mq->rptr] = msg;
    mq->count++;

    /* If a thread is blocked on this queue, start it */
    if (mq->emptyQ->next != NULL) {
        __iosRestartThread(&mq->emptyQ);
    }

end:
    return rv;
}

IOSError
iosReceiveMessage(IOSMessageQueueId id, IOSMessage *msg, u32 flag)
{
    IOSError rv = IOS_ERROR_OK;
    IOSMessageQueue *mq;


    /* Check arguments */
    CHECK_MESSAGE_QUEUE_ID(id);
    CHECK_MESSAGE_QUEUE_FLAGS(flag);
//    CHECK_MEMORY_REGION(msg, sizeof(IOSMessage));

    mq = __queues + id;

    /* Only allow threads in the creator's process to receive messages */
    CHECK_MESSAGE_QUEUE_OWNER(mq);

    /* While mq is empty */
    while (mq->count == 0) {
        if (flag == IOS_MESSAGE_BLOCK) {
            __iosRunningThread->state = IOS_STATE_WAITING;
            __iosEnqueueAndYield(&mq->emptyQ);
        } else {
            rv = IOS_ERROR_QEMPTY;
            goto end;
        }
    }

    /* Copy out message and remove it from queue */
    if (msg != NULL) {
        *msg = mq->buffer[mq->rptr];
    }
    mq->rptr += 1;
    if (mq->rptr >= mq->size) mq->rptr -= mq->size;
    mq->count--;

    /* If a thread is blocked on this queue, start it */
    if (mq->fullQ->next != NULL) {
        __iosRestartThread(&mq->fullQ);
    }

end:
    return rv;
}

IOSError
iosHandleEvent(IOSEvent event, IOSMessageQueueId id, IOSMessage msg)
{
    IOSError rv = IOS_ERROR_OK;
    IOSMessageQueue *mq;
    IOSEventState *es;

    CHECK_EVENT(event);
    CHECK_MESSAGE_QUEUE_ID(id);

    mq = __queues + id;

    CHECK_MESSAGE_QUEUE_OWNER(mq);

    if (__iosRunningThread->pid) {
      DBG_PRINTF((dbg_fp,"Registering event %u...\n", event));
        es = __iosEventState + event - IOS_EVENT_MIN;
        es->messageQueue = mq;
        es->message = msg;
        es->owner = __iosRunningThread->pid;
    } else {
        rv = IOS_ERROR_ACCESS;
        goto end;
    }

end:
    return rv;
}

IOSError
iosUnhandleEvent(IOSEvent event)
{
    IOSError rv = IOS_ERROR_OK;
    IOSEventState *es;

    CHECK_EVENT(event);

    es = __iosEventState + event - IOS_EVENT_MIN;
    if (__iosRunningThread->pid == es->owner) {
        es->messageQueue = NULL;
        es->message = 0;
    } else {
        rv = IOS_ERROR_ACCESS;
        goto end;
    }
end:
    return rv;
}
