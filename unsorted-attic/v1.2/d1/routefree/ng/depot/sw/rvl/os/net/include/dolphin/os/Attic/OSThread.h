/*---------------------------------------------------------------------------*
  Project:  Dolphin OS Thread API
  File:     OSThread.h

  Copyright 1998-2002 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: OSThread.h,v $
  Revision 1.1  2006/04/08 00:09:14  mxu
  add os layer header files for the net stack

    
    21    8/27/02 11:46 Shiki
    Modified OSClearStack() interface.

    20    8/19/02 21:42 Shiki
    Added error field to OSThread{}.

    19    8/09/02 10:25 Shiki
    Modified OSSetThreadSpecific() and OSGetThreadSpecific() interface.

    18    8/09/02 10:15 Shiki
    Added OSSetThreadSpecific() and OSGetThreadSpecific().

    17    8/08/02 20:44 Shiki
    Added OSSetSwitchThreadCallback().

    16    8/08/02 20:17 Shiki
    Added OSClearStack().

    15    6/07/00 5:30p Tian
    Added stack and stack size pointers into thread structure.  Changed
    APIs for create thread and idle function.

    14    4/20/00 6:25p Shiki
    Revised to store key data structures in lomem for debugger integration.

    13    3/07/00 10:28p Shiki
    Changed OSCreateThread() and OSSetThreadPriority to return a BOOL
    value.

    12    3/02/00 8:58p Shiki
    Added OSCheckActiveThreads().

    11    2/03/00 6:19p Shiki
    Added a new /attr/ parameter to OSCreateThread().

    10    1/28/00 3:23p Shiki
    Revised OSJoinThread() interface.

    9     1/27/00 2:58p Shiki
    Added more data members for implementing BPI protocol. Also changed
    stack argument type from u32 to void*.

    7     1/25/00 6:54p Shiki
    Added global __OSActiveThreadQueue.

    6     1/25/00 4:25p Shiki
    Modified several definitions.

    5     1/19/00 11:31p Shiki
    Formatted.

    4     1/18/00 4:15p Shiki
    Implemented OSJoinThread().

    3     1/18/00 3:26p Shiki
    Revised OSCreateThread and OSExitThread.

    2     1/18/00 10:43a Shiki
    Implemented basic thread API.

    1     10/07/99 4:12p Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __OSTHREAD_H__
#define __OSTHREAD_H__

#include <dolphin/os/OSContext.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_THREAD_SPECIFIC_MAX  2

typedef struct OSThread         OSThread;
typedef struct OSThreadQueue    OSThreadQueue;
typedef struct OSThreadLink     OSThreadLink;
typedef s32                     OSPriority;     //  0 highest, 31 lowest

typedef struct OSMutex          OSMutex;
typedef struct OSMutexQueue     OSMutexQueue;
typedef struct OSMutexLink      OSMutexLink;
typedef struct OSCond           OSCond;

typedef void                  (*OSIdleFunction)(void* param);
typedef void                  (*OSSwitchThreadCallback)(OSThread* from, OSThread* to);

struct OSThreadQueue
{
    OSThread*  head;
    OSThread*  tail;
};

struct OSThreadLink
{
    OSThread*  next;
    OSThread*  prev;
};

struct OSMutexQueue
{
    OSMutex*   head;
    OSMutex*   tail;
};

struct OSMutexLink
{
    OSMutex*   next;
    OSMutex*   prev;
};

struct OSThread
{
    OSContext       context;    // register context

    u16             state;      // OS_THREAD_STATE_*
    u16             attr;       // OS_THREAD_ATTR_*
    s32             suspend;    // suspended if the count is greater than zero
    OSPriority      priority;   // effective scheduling priority
    OSPriority      base;       // base scheduling priority
    void*           val;        // exit value

    OSThreadQueue*  queue;      // queue thread is on
    OSThreadLink    link;       // queue link

    OSThreadQueue   queueJoin;  // list of threads waiting for termination (join)

    OSMutex*        mutex;      // mutex trying to lock
    OSMutexQueue    queueMutex; // list of mutexes owned

    OSThreadLink    linkActive; // link of all threads for debugging

    u8*             stackBase;  // the thread's designated stack (high address)
    u32*            stackEnd;   // last word of stack (low address)

    s32             error;
    void*           specific[OS_THREAD_SPECIFIC_MAX];   // thread specific data
};

// Thread states
enum OS_THREAD_STATE
{
    OS_THREAD_STATE_READY    =  1,
    OS_THREAD_STATE_RUNNING  =  2,
    OS_THREAD_STATE_WAITING  =  4,
    OS_THREAD_STATE_MORIBUND =  8
};

// Thread priorities
#define OS_PRIORITY_MIN         0                   // highest
#define OS_PRIORITY_MAX         31                  // lowest
#define OS_PRIORITY_IDLE        OS_PRIORITY_MAX

// Thread attributes
#define OS_THREAD_ATTR_DETACH   0x0001u             // detached

// Stack magic value
#define OS_THREAD_STACK_MAGIC   0xDEADBABE

void       OSInitThreadQueue   ( OSThreadQueue* queue );
OSThread*  OSGetCurrentThread  ( void );
BOOL       OSIsThreadSuspended ( OSThread* thread );
BOOL       OSIsThreadTerminated( OSThread* thread );
s32        OSDisableScheduler  ( void );
s32        OSEnableScheduler   ( void );
void       OSYieldThread       ( void );
BOOL       OSCreateThread(       OSThread*  thread,
                                 void*    (*func)(void*),
                                 void*      param,
                                 void*      stack,
                                 u32        stackSize,
                                 OSPriority priority,
                                 u16        attr );
void       OSExitThread        ( void* val );
void       OSCancelThread      ( OSThread* thread );
BOOL       OSJoinThread        ( OSThread* thread, void** val );
void       OSDetachThread      ( OSThread* thread );
s32        OSResumeThread      ( OSThread* thread );
s32        OSSuspendThread     ( OSThread* thread );
BOOL       OSSetThreadPriority ( OSThread* thread, OSPriority priority );
OSPriority OSGetThreadPriority ( OSThread* thread );
void       OSSleepThread       ( OSThreadQueue* queue );
void       OSWakeupThread      ( OSThreadQueue* queue );

// Get/Set the data specific to the calling thread
void*      OSGetThreadSpecific ( s32 index );
void       OSSetThreadSpecific ( s32 index, void* ptr );

OSThread*  OSSetIdleFunction   ( OSIdleFunction idleFunction,
                                 void*          param,
                                 void*          stack,
                                 u32            stackSize);
OSThread*  OSGetIdleFunction   ( void );

void       OSClearStack        ( u8 val );

long       OSCheckActiveThreads( void );

OSSwitchThreadCallback OSSetSwitchThreadCallback( OSSwitchThreadCallback callback );

#ifdef __cplusplus
}
#endif

#endif  // __OSTHREAD_H__
