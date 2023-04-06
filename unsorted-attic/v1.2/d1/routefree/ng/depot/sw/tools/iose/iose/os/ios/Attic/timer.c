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
#include <iostypes.h>
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
            __iosStartTimer();

static IOSTimer_t __timers[IOS_TIMER_MAX]; /* Space for allowed timers */
static int head = -1;

static void
__iosStartTimer()
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
__iosDelNode(IOSTimerId idx)
{
    int i;
    if ( -1 != (i = __timers[idx].prev) )
        __timers[i].nxt = __timers[idx].nxt; 
    if ( -1 != (i = __timers[idx].nxt) )
        __timers[i].prev = __timers[idx].prev; 
    __timers[idx].nxt = __timers[idx].prev = -1;
}

static void
__iosAddNode(int idx, int prev, int nxt)
{
    __timers[idx].nxt = nxt;
    __timers[idx].prev = prev;
    if ( -1 != nxt)
        __timers[nxt].prev = idx;
    if ( -1 != prev )
        __timers[prev].nxt = idx;
    else {
        head = idx;
        __iosStartTimer();
    }
    return;
}

static void
__iosAddSorted(int idx)
{
    int prev = -1;
    int i = head;
    IOSTime expires = __timers[idx].expires;
    while ( -1 != i ) {
        if ( expires >= __timers[i].expires ) {
            prev = i;
            i = __timers[i].nxt;
            continue;
        }
        else if ( expires < __timers[i].expires ) {
            __iosAddNode(idx, prev, i);
            goto done;
        }
    }
    __iosAddNode(idx, prev, -1); /* Add at the end*/
    goto done;

done:
    return;
}

static void
__iosResetTimer(IOSTimerId idx, time_t now)
{
    __iosDelNode(idx);
    __timers[idx].expires = (IOSTime) now + __timers[idx].period;
    __iosAddSorted(idx);
}

static void
__iosCleanTimer(IOSTimerId idx)
{
    __iosDelNode(idx);
    __timers[idx].expires = 0; 
}

static void
__ios_sigalarm(int s)
{
    int old;
    time_t now = time(NULL);
    if ( s != SIGALRM || -1 == head ) goto err;
    while ( head >= 0 && __timers[head].expires <= now) {
        old = head;
        iosSendEvent(__timers[head].es); 
        if ( 1 == __timers[old].type )
            __iosResetTimer(old, now);
        else
            __iosCleanTimer(old);
        head = __timers[head].nxt;
    }
    if ( -1 != head) __iosStartTimer();
    return;
err:
    return;
}

static int
__iosRegisterAlarmHandler(void)
{ 
    if ( SIG_ERR == signal(SIGALRM, __ios_sigalarm ) ) { 
        perror("signal() failed");
        return 1; 
    }
    return 0;
}

int 
__iosInitTimers(void)
{
    int i;
    for ( i = 0; i < IOS_TIMER_MAX; ++i) 
        __timers[i].expires = 0; 
    return __iosRegisterAlarmHandler();
}

static inline IOSError 
__iosAllocTimer(IOSTime expires, IOSMessageQueueId mq, IOSMessage mesg, 
        u8 typ, IOSTime period)
{
    int i;
    for (i = 0; i < IOS_TIMER_MAX; ++i ) {
        if (0 != __timers[i].expires)
            continue;
        __timers[i].expires = expires;
        __timers[i].es.messageQueue = __queues + mq;
        __timers[i].es.message = mesg;
        __timers[i].es.owner = iosGetThreadId(); 
        __timers[i].type = typ;
        __timers[i].period = period;
        __timers[i].nxt = __timers[i].prev = -1;
        return i;
    }
    return IOS_ERROR_MAX;
}

static void 
__iosTimerDump( IOSTimer_t t, int idx)
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
iosDebugTimerListDump(void)
{
    int i;
    i = head;
    fprintf(stderr, "head = %d; now = %u\n", head, (unsigned) time(NULL));
    while ( -1 != i ) {
        __iosTimerDump (__timers[i], i);
        i = __timers[i].nxt;
    }
    return;
}

/* Add to new timer to __timers array.
 * Fix nxt, prev ptrs to keep timer list is sorted. 
 * Stop and start timers, if needed.
 */
IOSTimerId
iosSetTimer(IOSTime duration, IOSMessageQueueId mq, IOSMessage mesg, u8 typ)
{
    int idx = IOS_ERROR_INVALID;
    if ( 0 == duration ) goto done;
    /* XXX horti check mq, mesg ownership? */
    idx = __iosAllocTimer( time(NULL) + duration, mq, mesg, typ, duration);
    if ( IOS_ERROR_MAX == idx ) 
        goto done;
    __iosAddSorted(idx);
done:
    return idx;
}

IOSTimerId
iosStopTimer(IOSTimerId id)
{
    if ( head == id ) {
        RESET_HEAD_START_TIMER(id);
    }
    __iosCleanTimer(id);
    return IOS_ERROR_OK;
}
