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
#ifndef __THREAD_H__
#define __THREAD_H__

#define IOS_THREAD_MAX    32
#define IOS_PID_MAX       32
#define IOS_PRIORITY_MAX 127

#define IOS_THREAD_CONTEXT        0
#define IOS_THREAD_NEXT          68
#define IOS_THREAD_PRIORITY      72
#define IOS_THREAD_STATE         76
#define IOS_THREAD_PID           80

#define IOS_CONTEXT_CPSR         0
#define IOS_CONTEXT_R0           4
#define IOS_CONTEXT_R1           8
#define IOS_CONTEXT_R2           12
#define IOS_CONTEXT_R3           16
#define IOS_CONTEXT_R4           20
#define IOS_CONTEXT_R5           24
#define IOS_CONTEXT_R6           28
#define IOS_CONTEXT_R7           32
#define IOS_CONTEXT_R8           36
#define IOS_CONTEXT_R9           40
#define IOS_CONTEXT_R10          44
#define IOS_CONTEXT_R11          48
#define IOS_CONTEXT_R12          52
#define IOS_CONTEXT_R13          56
#define IOS_CONTEXT_R14          60
#define IOS_CONTEXT_R15          64
#define IOS_CONTEXT_SIZE         68
#define IOS_CONTEXT_SP   IOS_CONTEXT_R13
#define IOS_CONTEXT_LR   IOS_CONTEXT_R14
#define IOS_CONTEXT_PC   IOS_CONTEXT_R15

#define IOS_STATE_FREE    0
#define IOS_STATE_READY   1
#define IOS_STATE_RUNNING 2
#define IOS_STATE_STOPPED 3
#define IOS_STATE_WAITING 4

#if defined (_LANGUAGE_C)
#include "context.h"
typedef struct IOSThread {
    IOSContext context;
    struct IOSThread *next;
    s32 priority;
    u32 state;
    u32 pid;
    struct IOSThread **queue;
    IOSContext extra;
} IOSThread;

extern IOSThread __iosThreadTail;
extern IOSThread *__iosRunningThread;

void __iosRestartThread(IOSThread **queue);
void __iosInitThreads(void);
IOSProcessId iosGetProcessId(void);
IOSThreadId iosCreateThread(IOSEntryProc entry, void *arg, void *stack, 
    u32 stackSize, u32 priority);
void iosYieldThread(void);
IOSError iosStartThread(IOSThreadId id);
IOSError iosSetThreadPriority(IOSThreadId id, u32 priority);
IOSThreadId iosGetThreadId(void);

#endif

#endif /*__THREAD_H__*/
