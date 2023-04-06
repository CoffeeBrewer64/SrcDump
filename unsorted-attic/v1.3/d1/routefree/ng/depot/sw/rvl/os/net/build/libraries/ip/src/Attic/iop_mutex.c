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
 * Mutex Functions layer on IOP OS
 * 
 *---------------------------------------------------------------------------*/

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>

#include <dolphin/os.h>

static OSMutex              __mutex;    // use this mutex to map Nintendo's 
                                        // disable/enable/restore interrupt
static IOSMessageQueueId    __mqid;     // use this to manage nested mutex
static IOSMessage           __mq;

static void inline
LOCK_SYSTEM()
{
    IOSMessage msg;
    // gain the permission to access the mutex
    if ((IOS_ReceiveMessage(__mqid, &msg, IOS_MESSAGE_BLOCK)) < 0)
    {
        OSReport("%s: failed to receive message from %d\n", __FUNCTION__, __mqid);
    }
}

static void inline
UNLOCK_SYSTEM()
{
    IOSMessage msg = 0;

    if ((IOS_SendMessage(__mqid, msg, 0)) <0)
    {
        OSReport("%s: failed to send message to %d\n", __FUNCTION__, __mqid);
    }
}

void 
OSInitMutex ( OSMutex* mutex )
{
    IOSMessage msg = 0;

    mutex->count = 0;
    mutex->owner = -1;
    if ((mutex->mqid = IOS_CreateMessageQueue(mutex->mq, 1)) < 0) 
    {
        OSReport("%s: failed to create message queue\n", __FUNCTION__);
    }

    if ((IOS_SendMessage(mutex->mqid, msg, 0)) <0)
    {
        OSReport("%s: failed to send message to %d\n", __FUNCTION__, mutex->mqid);
    }
}

void
OSLockMutex ( OSMutex* mutex )
{
    IOSMessage msg;

    LOCK_SYSTEM();
    // handle nested mutex
    if (mutex->owner == IOS_GetThreadId())
    {
        mutex->count++;
        UNLOCK_SYSTEM();
        return;
    }
    UNLOCK_SYSTEM();

    if ((IOS_ReceiveMessage(mutex->mqid, &msg, IOS_MESSAGE_BLOCK)) < 0)
    {
        OSReport("%s: failed to receive message from %d\n", __FUNCTION__, mutex->mqid);
    }

    LOCK_SYSTEM();
    ++mutex->count;
    mutex->owner = IOS_GetThreadId();
    UNLOCK_SYSTEM();
}

void
OSUnlockMutex ( OSMutex* mutex )
{
    IOSMessage msg = 0;

    LOCK_SYSTEM();

    // the mutex is not locked
    if (mutex->count <= 0)
    {
        UNLOCK_SYSTEM();
        return;
    }

    --mutex->count;
    if ( mutex->count == 0)
    {
        mutex->owner = -1;
        UNLOCK_SYSTEM();

        if ((IOS_SendMessage(mutex->mqid, msg, 0)) <0 )
        {
            OSReport("%s: failed to send message to %d\n", __FUNCTION__, mutex->mqid);
        }
        return;
    }

    UNLOCK_SYSTEM();   
}

void
OSInitInterrupts(void)
{
    IOSMessage msg = 0;

    // init __mqid which will be used to manage nested mutex
    __mqid = IOS_CreateMessageQueue(&__mq, 1);
    if (__mqid < 0) 
    {
        OSReport("%s: failed to create message queue\n", __FUNCTION__);
    }
    if ((IOS_SendMessage(__mqid, msg, 0)) <0)
    {
        OSReport("%s: failed to send message to %d\n", __FUNCTION__, __mqid);
    }

    // init __mutex for interrupt handling
    OSInitMutex (&__mutex);
}

BOOL
OSDisableInterrupts(void)
{
    OSLockMutex(&__mutex);
    return TRUE;
}

BOOL
OSEnableInterrupts(void)
{
    OSUnlockMutex(&__mutex);
    return TRUE;
}

BOOL
OSRestoreInterrupts(BOOL level)
{
    OSUnlockMutex(&__mutex);
    return TRUE;
}
