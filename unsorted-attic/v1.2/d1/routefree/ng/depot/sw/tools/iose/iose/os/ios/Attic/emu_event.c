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
#include <ioserrno.h>
#include "thread.h"
#include "message.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

extern IOSEventState __iosEventState[IOS_NUM_EVENTS];

void
iosSendEvent (IOSEventState es)
{
    u32 wptr;
    IOSMessageQueue *mq = es.messageQueue;
    if (mq->count >= mq->size) {
        goto end;
    }
    wptr = mq->rptr + mq->count;
    if (wptr >= mq->size) wptr -= mq->size;
    mq->buffer[wptr] = es.message;
    mq->count++;
    if (mq->emptyQ->next != NULL) {
        __iosRestartThread(&mq->emptyQ);
    }
end:
    return;
}

/* If __iosEventstate[s] is non-NULL, it means some process has
 * registered an event-handler for event s. Send a msg to the 
 * appropriate message queue.
 * If no event-handler has registered for event s, ignore it.
 */
void
__ios_sigdispatch(int s)
{
    IOSError rv; /* dummy */
    CHECK_EVENT(s);
    if ( NULL == __iosEventState[s - IOS_EVENT_MIN].messageQueue ) {
        fprintf(stderr, "No process has registered to handle event: %d\n", s);
        goto end;
    } 
    DBG_PRINTF((dbg_fp,"__iossigdispatch: sending message to queue\n"));
    iosSendEvent(__iosEventState[s - IOS_EVENT_MIN]);
end:
    return; 
}

void 
__ios_sigintr(int s)
{
  iosDestroyThread(0);
}

IOSError
__iosRegisterHandlers(void)
{
    int i;
    IOSError rv = IOS_ERROR_OK;
    DBG_ENTRY;
    for ( i = IOS_EVENT_MIN; i < IOS_EVENT_MAX; ++i ) 
        if ( SIG_ERR == signal(i, __ios_sigdispatch) ) { 
            fprintf(stderr,"signal() failed: %s\n", strerror(errno));
            rv = IOS_ERROR_INTR;
            goto end;
        }

    if ( SIG_ERR == signal(SIGINT, __ios_sigintr) ) { 
        fprintf(stderr,"signal() failed: %s\n", strerror(errno));
        rv = IOS_ERROR_INTR;
    }
end:
    DBG_EXIT;
    return rv;
}
