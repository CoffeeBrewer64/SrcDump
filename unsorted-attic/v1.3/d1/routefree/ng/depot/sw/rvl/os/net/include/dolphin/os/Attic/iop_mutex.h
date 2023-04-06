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
 * OS mutex support
 * 
 *---------------------------------------------------------------------------*/

#ifndef __IOP_MUTEX_H__
#define __IOP_MUTEX_H__

#ifdef __cplusplus
extern "C" {
#endif


typedef struct OSMutex
{
    IOSMessageQueueId	mqid;	// Message queue
    IOSMessage          mq[1];
    s32                 count;  // lock count
    IOSThreadId         owner;
} OSMutex;


void OSInitMutex   ( OSMutex* mutex );
void OSLockMutex   ( OSMutex* mutex );
void OSUnlockMutex ( OSMutex* mutex );

#ifdef __cplusplus
}
#endif

#endif  // __IOP_MUTEX_H__
