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
#include <arm.h>
#include "timer.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <errno.h>

#define RESET_HEAD_START_TIMER(x)  \
        if ( -1 != ( head = __timers[(x)].nxt)) \
            __skStartTimer();

static SKTimer_t __timers[SK_TIMER_MAX]; /* Space for allowed timers */
static int head = -1;

static void
__skStartTimer()
{
    struct itimerval v; 
    if ( -1 == head )
        return;
    v.it_value.tv_sec = __timers[head].expires - time(NULL);
    v.it_value.tv_usec = 0;
    v.it_interval.tv_sec = v.it_interval.tv_usec = 0;  
    if ( -1 == setitimer(ITIMER_REAL, &v, NULL) )
        perror("setitimer failed:");
    return;
}

static void
__skDelNode(SKTimerId idx)
{
    int i;
    if ( -1 != (i = __timers[idx].prev) )
        __timers[i].nxt = __timers[idx].nxt; 
    if ( -1 != (i = __timers[idx].nxt) )
        __timers[i].prev = __timers[idx].prev; 
    __timers[idx].nxt = __timers[idx].prev = -1;
}

static void
__skAddNode(int idx, int prev, int nxt)
{
    __timers[idx].nxt = nxt;
    __timers[idx].prev = prev;
    if ( -1 != nxt)
        __timers[nxt].prev = idx;
    if ( -1 != prev )
        __timers[prev].nxt = idx;
    else {
        head = idx;
        __skStartTimer();
    }
    return;
}

static void
__skAddSorted(int idx)
{
    int prev = -1;
    int i = head;
    SKTime expires = __timers[idx].expires;
    while ( -1 != i ) {
        if ( expires >= __timers[i].expires ) {
            prev = i;
            i = __timers[i].nxt;
            continue;
        }
        else if ( expires < __timers[i].expires ) {
            __skAddNode(idx, prev, i);
            goto done;
        }
    }
    __skAddNode(idx, prev, -1); /* Add at the end*/
    goto done;

done:
    return;
}

static void
__skResetTimer(SKTimerId idx, time_t now)
{
    __skDelNode(idx);
    __timers[idx].expires = (SKTime) now + __timers[idx].period;
    __skAddSorted(idx);
}

static void
__skCleanTimer(SKTimerId idx)
{
    __skDelNode(idx);
    __timers[idx].expires = 0; 
}

static void
__sk_sigalarm(int s)
{
    int old;
    time_t now = time(NULL);
    if ( s != SIGALRM || -1 == head ) goto err;
    while ( head >= 0 && __timers[head].expires <= now) {
        old = head;
        skSendEvent(__timers[head].es); 
        if ( 1 == __timers[old].type )
            __skResetTimer(old, now);
        else
            __skCleanTimer(old);
        head = __timers[head].nxt;
    }
    if ( -1 != head) __skStartTimer();
    return;
err:
    return;
}

static int
__skRegisterAlarmHandler(void)
{ 
    if ( SIG_ERR == signal(SIGALRM, __sk_sigalarm ) ) { 
        perror("signal() failed");
        return 1; 
    }
    return 0;
}

int 
__skInitTimers(void)
{
    int i;
    for ( i = 0; i < SK_TIMER_MAX; ++i) 
        __timers[i].expires = 0; 
    return __skRegisterAlarmHandler();
}

static inline SKError 
__skAllocTimer(SKTime expires, SKMessageQueueId mq, SKMessage mesg, 
        u8 typ, SKTime period)
{
    int i;
    for (i = 0; i < SK_TIMER_MAX; ++i ) {
        if (0 != __timers[i].expires)
            continue;
        __timers[i].expires = expires;
        __timers[i].es.messageQueue = __queues + mq;
        __timers[i].es.message = mesg;
        __timers[i].es.owner = skGetThreadId(); 
        __timers[i].type = typ;
        __timers[i].period = period;
        __timers[i].nxt = __timers[i].prev = -1;
        return i;
    }
    return SK_ERROR_MAX;
}

static void 
__skTimerDump( SKTimer_t t, int idx)
{
    if ( t.expires != 0 ) {
        fprintf(stderr, "----------------------\n");
        fprintf(stderr, "owner = %u\n", t.es.owner);
        fprintf(stderr, "expires = %u\n", t.expires);
        fprintf(stderr, "this timer's idx = %d\n", idx);
        fprintf(stderr, "nxt timer's idx = %d\n", t.nxt);
        fprintf(stderr, "prev timer's idx = %d\n", t.prev);
        fprintf(stderr, "----------------------\n");
    }
    return;
}

/* System calls */
void
skDebugTimerListDump(void)
{
    int i;
    i = head;
    fprintf(stderr, "head = %d; now = %u\n", head, (unsigned) time(NULL));
    while ( -1 != i ) {
        __skTimerDump (__timers[i], i);
        i = __timers[i].nxt;
    }
    return;
}

/* Add to new timer to __timers array.
 * Fix nxt, prev ptrs to keep timer list is sorted. 
 * Stop and start timers, if needed.
 */
SKTimerId
skSetTimer(SKTime duration, SKMessageQueueId mq, SKMessage mesg, u8 typ)
{
    int idx = SK_ERROR_INVALID;
    if ( 0 == duration ) goto done;
    /* XXX horti check mq, mesg ownership? */
    idx = __skAllocTimer( time(NULL) + duration, mq, mesg, typ, duration);
    if ( SK_ERROR_MAX == idx ) 
        goto done;
    __skAddSorted(idx);
done:
    return idx;
}

SKTimerId
skStopTimer(SKTimerId id)
{
    if ( head == id ) {
        RESET_HEAD_START_TIMER(id);
    }
    __skCleanTimer(id);
    return SK_ERROR_OK;
}
