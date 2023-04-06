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

#include <sk.h>
#include <ng.h>
#include <sktypes.h>
#include <ngtypes.h>
#include <skerrno.h>
#include "thread.h"
#include "message.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

extern SKEventState __skEventState[SK_NUM_EVENTS];

void
skSendEvent (SKEventState es)
{
    u32 wptr;
    SKMessageQueue *mq = es.messageQueue;
    if (mq->count >= mq->size) {
        goto end;
    }
    wptr = mq->rptr + mq->count;
    if (wptr >= mq->size) wptr -= mq->size;
    mq->buffer[wptr] = es.message;
    mq->count++;
    if (mq->emptyQ->next != NULL) {
        __skRestartThread(&mq->emptyQ);
    }
end:
    return;
}

/* If __skEventstate[s] is non-NULL, it means some process has
 * registered an event-handler for event s. Send a msg to the 
 * appropriate message queue.
 * If no event-handler has registered for event s, ignore it.
 */
void
__sk_sigdispatch(int s)
{
    SKError rv; /* dummy */
    CHECK_EVENT(s);
    if ( NULL == __skEventState[s - SK_EVENT_MIN].messageQueue ) {
        fprintf(stderr, "No process has registered to handle event: %d\n", s);
        goto end;
    } 
    DBG_PRINTF((dbg_fp,"__sksigdispatch: sending message to queue\n"));
    skSendEvent(__skEventState[s - SK_EVENT_MIN]);
end:
    return; 
}

void 
__sk_sigintr(int s)
{
  skDestroyThread(0);
}

SKError
__skRegisterHandlers(void)
{
    int i;
    SKError rv = SK_ERROR_OK;
    DBG_ENTRY;
    for ( i = SK_EVENT_MIN; i < SK_EVENT_MAX; ++i ) 
        if ( SIG_ERR == signal(i, __sk_sigdispatch) ) { 
            fprintf(stderr,"signal() failed: %s\n", strerror(errno));
            rv = SK_ERROR_INTR;
            goto end;
        }

    if ( SIG_ERR == signal(SIGINT, __sk_sigintr) ) { 
        fprintf(stderr,"signal() failed: %s\n", strerror(errno));
        rv = SK_ERROR_INTR;
    }
end:
    DBG_EXIT;
    return rv;
}
