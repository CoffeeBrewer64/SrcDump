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


#include <ng.h>
#include <sktypes.h>
#include "thread.h"
#include "except.h"
#include "message.h"
//#include "memory.h"

#include <signal.h>

SKMessageQueue __queues[SK_MESSAGE_QUEUE_MAX];
SKEventState __skEventState[SK_NUM_EVENTS];

#define CHECK_MESSAGE_QUEUE_ID(id) \
    if (((id) < 0) || ((id) >= SK_MESSAGE_QUEUE_MAX)) {\
        rv = SK_ERROR_INVALID; \
        goto end; \
    } else

#define CHECK_MESSAGE_QUEUE_FLAGS(flag) \
    if (((flag) != SK_MESSAGE_BLOCK) && ((flag) != SK_MESSAGE_NOBLOCK)) {\
        rv = SK_ERROR_INVALID; \
        goto end; \
    } else

#define CHECK_MESSAGE_QUEUE_MASK(mq) \
    if ((mq)->mask) { \
        if (!((mq)->mask & (1 << __skRunningThread->pid))) {\
            rv = SK_ERROR_ACCESS; \
            goto end; \
        } \
    } else { \
        if ((mq)->owner != __skRunningThread->pid) {\
            rv = SK_ERROR_ACCESS; \
            goto end; \
        } \
    }

#define CHECK_MESSAGE_QUEUE_OWNER(mq) \
    if ((mq)->owner != __skRunningThread->pid) {\
        rv = SK_ERROR_ACCESS; \
        goto end; \
    } else

SKMessageQueueId
skCreateMessageQueue(SKMessage *msgarray, u32 size, u32 pidMask)
{
    SKMessageQueueId rv;
    SKMessageQueue *mq;


    /* Look for a free mq structure */
    for (rv = 0; rv < SK_MESSAGE_QUEUE_MAX; ++rv) {
        if (__queues[rv].size == 0) {
            break;
        }
    }
    if (rv == SK_MESSAGE_QUEUE_MAX) {
        rv = SK_ERROR_MAX;
        goto end;
    }

    mq = __queues + rv;
    mq->emptyQ = (SKThread *)&__skThreadTail;
    mq->fullQ = (SKThread *)&__skThreadTail;
    mq->count = 0;
    mq->rptr = 0;
    mq->size = size;
    mq->buffer = msgarray;
    mq->mask = pidMask;
    mq->owner = __skRunningThread->pid;

end:
    return rv;
}


SKError
skDestroyMessageQueue(SKMessageQueueId id)
{
    SKError rv = SK_ERROR_OK;
    SKMessageQueue *mq;


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


SKError
skSendMessage(SKMessageQueueId id, SKMessage msg, u32 flag)
{
    SKError rv = SK_ERROR_OK;
    SKMessageQueue *mq;
    u32 wptr;


    CHECK_MESSAGE_QUEUE_ID(id);
    CHECK_MESSAGE_QUEUE_FLAGS(flag);

    mq = __queues + id;

    CHECK_MESSAGE_QUEUE_MASK(mq);

    /* While mq is full */
    while (mq->count >= mq->size) {
        if (flag == SK_MESSAGE_BLOCK) {
          DBG_PRINTF((dbg_fp,"skSendMessage: queue is full. Blocking...\n"));
          __skRunningThread->state = SK_STATE_WAITING;
          __skEnqueueAndYield(&mq->fullQ);
          DBG_PRINTF((dbg_fp,"skSendMessage: woke up from being blocked...\n"));
        } else {
          rv = SK_ERROR_QFULL;
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
      __skRestartThread(&mq->emptyQ);
    }

end:
    return rv;
}


SKError
skJamMessage(SKMessageQueueId id, SKMessage msg, u32 flag)
{
    SKError rv = SK_ERROR_OK;
    SKMessageQueue *mq;


    CHECK_MESSAGE_QUEUE_ID(id);
    CHECK_MESSAGE_QUEUE_FLAGS(flag);

    mq = __queues + id;

    CHECK_MESSAGE_QUEUE_MASK(mq);

    /* While mq is full */
    while (mq->count >= mq->size) {
        if (flag == SK_MESSAGE_BLOCK) {
            __skRunningThread->state = SK_STATE_WAITING;
            __skEnqueueAndYield(&mq->fullQ);
        } else {
            rv = SK_ERROR_QFULL;
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
        __skRestartThread(&mq->emptyQ);
    }

end:
    return rv;
}

SKError
skReceiveMessage(SKMessageQueueId id, SKMessage *msg, u32 flag)
{
    SKError rv = SK_ERROR_OK;
    SKMessageQueue *mq;


    /* Check arguments */
    CHECK_MESSAGE_QUEUE_ID(id);
    CHECK_MESSAGE_QUEUE_FLAGS(flag);
//    CHECK_MEMORY_REGION(msg, sizeof(SKMessage));

    mq = __queues + id;

    /* Only allow threads in the creator's process to receive messages */
    CHECK_MESSAGE_QUEUE_OWNER(mq);

    /* While mq is empty */
    while (mq->count == 0) {
        if (flag == SK_MESSAGE_BLOCK) {
            __skRunningThread->state = SK_STATE_WAITING;
            __skEnqueueAndYield(&mq->emptyQ);
        } else {
            rv = SK_ERROR_QEMPTY;
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
        __skRestartThread(&mq->fullQ);
    }

end:
    return rv;
}

SKError
skHandleEvent(SKEvent event, SKMessageQueueId id, SKMessage msg)
{
    SKError rv = SK_ERROR_OK;
    SKMessageQueue *mq;
    SKEventState *es;

    CHECK_EVENT(event);
    CHECK_MESSAGE_QUEUE_ID(id);

    mq = __queues + id;

    CHECK_MESSAGE_QUEUE_OWNER(mq);

    if (__skRunningThread->pid) {
      DBG_PRINTF((dbg_fp,"Registering event %u...\n", event));
        es = __skEventState + event - SK_EVENT_MIN;
        es->messageQueue = mq;
        es->message = msg;
        es->owner = __skRunningThread->pid;
    } else {
        rv = SK_ERROR_ACCESS;
        goto end;
    }

end:
    return rv;
}

SKError
skUnhandleEvent(SKEvent event)
{
    SKError rv = SK_ERROR_OK;
    SKEventState *es;

    CHECK_EVENT(event);

    es = __skEventState + event - SK_EVENT_MIN;
    if (__skRunningThread->pid == es->owner) {
        es->messageQueue = NULL;
        es->message = 0;
    } else {
        rv = SK_ERROR_ACCESS;
        goto end;
    }
end:
    return rv;
}
