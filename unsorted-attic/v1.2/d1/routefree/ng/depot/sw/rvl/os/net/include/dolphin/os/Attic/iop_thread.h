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
 * OS thread header file for network stack
 * 
 *---------------------------------------------------------------------------*/

#ifndef __IOP_THREAD_H__
#define __IOP_THREAD_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSThread         OSThread;
typedef struct OSThreadQueue    OSThreadQueue;

struct OSThreadQueue
{
    OSThread*  head;
    OSThread*  tail;
};

struct OSThread
{
    IOSThreadId     threadId;
    s32             error;
    OSThread        *next;
    OSThread        *prev;
};

void       OSInitThreadQueue   ( OSThreadQueue* queue );
OSThread*  OSGetCurrentThread  ( void );
s32        OSDisableScheduler  ( void );
s32        OSEnableScheduler   ( void );
void       OSYieldThread       ( void );
void       OSSleepThread       ( OSThreadQueue* queue );
void       OSWakeupThread      ( OSThreadQueue* queue );

#ifdef __cplusplus
}
#endif

#endif  // __IOP_THREAD_H__
