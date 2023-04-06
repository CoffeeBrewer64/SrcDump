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

#define SK_THREAD_MAX    32
#define SK_PID_MAX       32
#define SK_PRIORITY_MAX 127

#define SK_THREAD_CONTEXT        0
#define SK_THREAD_NEXT          68
#define SK_THREAD_PRIORITY      72
#define SK_THREAD_STATE         76
#define SK_THREAD_PID           80

#define SK_CONTEXT_CPSR         0
#define SK_CONTEXT_R0           4
#define SK_CONTEXT_R1           8
#define SK_CONTEXT_R2           12
#define SK_CONTEXT_R3           16
#define SK_CONTEXT_R4           20
#define SK_CONTEXT_R5           24
#define SK_CONTEXT_R6           28
#define SK_CONTEXT_R7           32
#define SK_CONTEXT_R8           36
#define SK_CONTEXT_R9           40
#define SK_CONTEXT_R10          44
#define SK_CONTEXT_R11          48
#define SK_CONTEXT_R12          52
#define SK_CONTEXT_R13          56
#define SK_CONTEXT_R14          60
#define SK_CONTEXT_R15          64
#define SK_CONTEXT_SIZE         68
#define SK_CONTEXT_SP   SK_CONTEXT_R13
#define SK_CONTEXT_LR   SK_CONTEXT_R14
#define SK_CONTEXT_PC   SK_CONTEXT_R15

#define SK_STATE_FREE    0
#define SK_STATE_READY   1
#define SK_STATE_RUNNING 2
#define SK_STATE_STOPPED 3
#define SK_STATE_WAITING 4

#if defined (_LANGUAGE_C)
#include "context.h"
typedef struct SKThread {
    SKContext context;
    struct SKThread *next;
    s32 priority;
    u32 state;
    u32 pid;
    struct SKThread **queue;
    SKContext extra;
} SKThread;

extern SKThread __skThreadTail;
extern SKThread *__skRunningThread;

void __skRestartThread(SKThread **queue);
void __skInitThreads(void);
SKProcessId skGetProcessId(void);
SKThreadId skCreateThread(SKEntryProc entry, void *arg, void *stack, 
    u32 stackSize, u32 priority);
void skYieldThread(void);
SKError skStartThread(SKThreadId id);
SKError skSetThreadPriority(SKThreadId id, u32 priority);
SKThreadId skGetThreadId(void);

#endif

#endif /*__THREAD_H__*/
