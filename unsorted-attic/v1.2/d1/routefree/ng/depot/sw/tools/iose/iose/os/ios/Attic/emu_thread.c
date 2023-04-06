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
#include <iosdebug.h>
#include <iostypes.h>
#include <arm.h>
#include "thread.h"
#include "except.h"
#include "context.h"
#include "emu_thread.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*func_t)(void);

extern IOSThread *__iosRunQueue;
extern IOSThread *__iosRunningThread;
extern IOSThread * __iosPopThread(IOSThread **queue);
extern void __iosEnqueueThread(IOSThread **queue, IOSThread *new);

int 
emuInitContext( IOSContext *ctx,
        IOSEntryProc entry,
        void *arg,
        void *stack,
        u32 stackSize)
{
    u32 arg_val;
    if ( -1 == getcontext(& (ctx->uctx)) ) {
        perror("getcontext failed");
        return -1;
    }
    ctx->uctx.uc_link = NULL;
    ctx->uctx.uc_stack.ss_sp = stack;
    ctx->uctx.uc_stack.ss_size = stackSize;
    ctx->uctx.uc_stack.ss_flags = 0;
    if ( NULL == arg)
        arg_val = 0;
    else 
        arg_val = *(u32 *)arg;
    makecontext(&(ctx->uctx), (func_t) entry, 1+1, arg_val);
    return 0;
}

void
__iosDispatchThread(IOSThread *current)
{
    IOSThread *t = __iosPopThread(&__iosRunQueue);
    t->state = IOS_STATE_READY;
    __iosRunningThread = t;

    if ( t == current) {
        DBG_PRINTF((dbg_fp,"__iosDispatchThread: don't need to switch %p --> %p\n", current, t));
        goto done;
    }
    if ( NULL == current) {
        DBG_PRINTF((dbg_fp,"Current thread = NULL. Jumping to thread %x\n",(unsigned int) t));
        errno = t->context.ios_errno;
        setcontext(&(t->context.uctx));
        /* Don't get here */
    }
    else {
        DBG_PRINTF((dbg_fp,"__iosDispatchThread: %p --> %p\n", current, t));
        current->context.ios_errno = errno;
        errno = t->context.ios_errno;
        swapcontext(&(current->context.uctx), &(t->context.uctx));
        /* Don't get here */
    }

done:
    return;
}

/*
 * void __iosEnqueueAndYield(IOSThread **queue)
 * Save the current running threads context.  If the given queue is non-NULL,
 * enqueue the current running thread on it.  Yield the current thread by
 * invoking the dispatcher.
 *
 */

void
__iosEnqueueAndYield(IOSThread **queue)
{

    if ( NULL == queue) {
        DBG_PRINTF((dbg_fp, "Queue is null. iosEnqueueYield does nothing \n"));
        return;
    }
    IOSThread *current = __iosRunningThread;
    __iosEnqueueThread(queue, current);
    __iosDispatchThread(current);
    return;
}
