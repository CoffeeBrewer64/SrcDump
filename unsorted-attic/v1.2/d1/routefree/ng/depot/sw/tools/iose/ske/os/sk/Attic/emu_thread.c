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
#include "thread.h"
#include "except.h"
#include "context.h"
#include "emu_thread.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*func_t)(void);

extern SKThread *__skRunQueue;
extern SKThread *__skRunningThread;
extern SKThread * __skPopThread(SKThread **queue);
extern void __skEnqueueThread(SKThread **queue, SKThread *new);

int 
emuInitContext( SKContext *ctx,
        SKEntryProc entry,
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
__skDispatchThread(SKThread *current)
{
    SKThread *t = __skPopThread(&__skRunQueue);
    t->state = SK_STATE_READY;
    __skRunningThread = t;

    if ( t == current) {
        DBG_PRINTF((dbg_fp,"__skDispatchThread: don't need to switch %p --> %p\n", current, t));
        goto done;
    }
    if ( NULL == current) {
        DBG_PRINTF((dbg_fp,"Current thread = NULL. Jumping to thread %x\n",(unsigned int) t));
        errno = t->context.sk_errno;
        setcontext(&(t->context.uctx));
        /* Don't get here */
    }
    else {
        DBG_PRINTF((dbg_fp,"__skDispatchThread: %p --> %p\n", current, t));
        current->context.sk_errno = errno;
        errno = t->context.sk_errno;
        swapcontext(&(current->context.uctx), &(t->context.uctx));
        /* Don't get here */
    }

done:
    return;
}

/*
 * void __skEnqueueAndYield(SKThread **queue)
 * Save the current running threads context.  If the given queue is non-NULL,
 * enqueue the current running thread on it.  Yield the current thread by
 * invoking the dispatcher.
 *
 */

void
__skEnqueueAndYield(SKThread **queue)
{

    if ( NULL == queue) {
        DBG_PRINTF((dbg_fp, "Queue is null. skEnqueueYield does nothing \n"));
        return;
    }
    SKThread *current = __skRunningThread;
    __skEnqueueThread(queue, current);
    __skDispatchThread(current);
    return;
}
