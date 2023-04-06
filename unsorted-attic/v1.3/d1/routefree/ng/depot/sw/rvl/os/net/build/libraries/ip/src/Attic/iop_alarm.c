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

/*---------------------------------------------------------------------------*
 * 
 * Timer management scheme on IOP
 * 
 *---------------------------------------------------------------------------*/

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>

#include <dolphin/os.h>
#include <dolphin/ip/IFQueue.h>

#define NET_ALARM_STACK_SIZE    (4 * 1024)
#define NET_ALARM_PRIORITY      60
#define NET_ALARM_MSGQ_SIZE     32

static char __alarmStack[NET_ALARM_STACK_SIZE] ATTRIBUTE_ALIGN(4);
static IOSMessage __msgQ[NET_ALARM_MSGQ_SIZE];
static IOSMessageQueueId __qid;

static void
alarmHandler(u32 arg)
{
    IOSMessage msg;
    OSAlarm *alarm;

    OSReport("*** Alarm Thread Started ***\n");

    /* Sit in a loop processing requests */
    while(1) {
        IOS_ReceiveMessage(__qid, &msg, IOS_MESSAGE_BLOCK);
        alarm = (OSAlarm *)msg;
        alarm->handler(alarm, NULL);
    }

    IOS_DestroyMessageQueue(__qid);
    return;
}

void
OSInitAlarm( void )
{
    IOSThreadId threadId;

    /* Create a message queue for timer management */
    if ( (__qid = IOS_CreateMessageQueue(__msgQ, NET_ALARM_MSGQ_SIZE)) < 0 ) {
        OSReport("%s: Creating message queue failed\n", __FUNCTION__);
        return;
    }

    /* Create the timer management thread */
    threadId = IOS_CreateThread(alarmHandler, NULL, __alarmStack + sizeof(__alarmStack),
        sizeof(__alarmStack), IOS_GetThreadPriority(IOS_GetThreadId()), 
        IOS_THREAD_CREATE_DETACHED);
//        sizeof(__alarmStack), NET_ALARM_PRIORITY, IOS_THREAD_CREATE_DETACHED);
    
    if (threadId < 0) {
        OSReport("%s: could not create the timer thread - exiting\n", __FUNCTION__);
        return;
    }
    if (IOS_StartThread(threadId) != IOS_ERROR_OK) {
        OSReport("%s: could not start the timer thread\n", __FUNCTION__);
        return;
    }

    return;
}

void
OSSetAlarm ( OSAlarm* alarm, OSTime tick, OSAlarmHandler handler )
{
	alarm->handler  = handler;

	alarm->fire     = OSTicksToMicroseconds(tick);
	alarm->timerId  = IOS_CreateTimer((IOSTime)alarm->fire, 0, __qid, (IOSMessage)alarm);
}

void
OSSetAlarmTag ( OSAlarm* alarm, u32 tag )
{
	alarm->tag=tag;
}

void
OSSetAbsAlarm ( OSAlarm* alarm, OSTime time, OSAlarmHandler handler )
{
	OSSetAlarm( alarm, time, handler );
}

void
OSSetPeriodicAlarm ( OSAlarm* alarm, OSTime start, OSTime period,
                          OSAlarmHandler handler )
{
	alarm->handler  = handler;
	alarm->fire     = OSTicksToMilliseconds(period);
	alarm->start    = start;
	alarm->period   = alarm->fire;
	alarm->timerId  = IOS_CreateTimer(0, (IOSTime)alarm->period, __qid, (IOSMessage)alarm);
}

void
OSCreateAlarm ( OSAlarm* alarm )
{
    alarm->timerId  = -1;
	alarm->handler  = NULL;
	alarm->tag      = 0;
	alarm->fire     = 0;
	alarm->period   = 0;
	alarm->start    = 0;
}

void
OSCancelAlarm ( OSAlarm* alarm )
{
    if (alarm->timerId == -1)
        return;

    IOS_DestroyTimer(alarm->timerId);
	alarm->timerId=-1;
}
