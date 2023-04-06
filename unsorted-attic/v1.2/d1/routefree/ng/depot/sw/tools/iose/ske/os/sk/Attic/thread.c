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
#include "alloc.h"
#include "emu_thread.h"
#include "idle.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


static SKThread __threads[SK_THREAD_MAX];
static u8 __pids[SK_PID_MAX]; /* compiler initialized to all 0's */

SKThread __skThreadTail = {
    {},
    NULL,
    -1
};

SKThread *__skRunQueue = &__skThreadTail;
SKThread *__skRunningThread = 0;

#define CHECK_THREAD_ID(id) \
    if (((id) < 0) || ((id) >= SK_THREAD_MAX)) {\
        rv = SK_ERROR_INVALID; \
        goto end; \
    } else

#define CHECK_PROCESS_ID(p) \
    if ((p) != (__skRunningThread ? __skRunningThread->pid : 0)) { \
        rv = SK_ERROR_INVALID; \
        goto end; \
    } else

#define CHECK_PRIORITY(pri) \
    if ((pri) > SK_PRIORITY_MAX) { \
        rv = SK_ERROR_INVALID; \
        goto end; \
    } else

#define GET_THREAD(t, id) \
    if (id == 0 && __skRunningThread) { \
        t = __skRunningThread; \
    } else { \
        CHECK_THREAD_ID(id); \
        t = __threads + id; \
        CHECK_PROCESS_ID(t->pid); \
    }
    
#define GET_THREAD_NO_PIDCHECK(t,id) \
    if (id == 0 && __skRunningThread) { \
        t = __skRunningThread; \
    } else { \
        CHECK_THREAD_ID(id); \
        t = __threads + id; \
    }

void
__skEnqueueThread(SKThread **queue, SKThread *new)
{
    SKThread **prev = queue;
    SKThread *next = *prev;

    while (next->priority >= new->priority) {
        prev = &(next->next);
        next = next->next;
    }

    *prev = new;
    new->next = next;
    new->queue = queue;
}

void
__skDequeueThread(SKThread **queue, SKThread *t)
{
    SKThread **prev = queue;
    SKThread *next = *prev;

    while (next != NULL) {
        if (next == t) {
            *prev = next->next;
            return;
        }
        prev = &(next->next);
        next = next->next;
    }
}

SKThread *
__skPopThread(SKThread **queue)
{
    SKThread *t = *queue;
    *queue = t->next;
    return t;
}

static inline void
__skUsePid(u32 i)
{
  ++__pids[i];
  DBG_PRINTF((dbg_fp, "Setting use count for pid %u to %u\n", i, __pids[i]));
}

static inline void 
__skFreePid(u32 i)
{
  --__pids[i];
  DBG_PRINTF((dbg_fp, "Setting use count for pid %u to %u\n", i, __pids[i]));
}

static inline u8
__skIsUsedPid(u32 i)
{
   return __pids[i];
}
static u32 
__skGetFreePid()
{
  u32 i;
  for (i = 0; i < SK_PID_MAX; ++i) {
    if ( 0 == __pids[i] ) {
      __pids[i] = 1;
      return i;
    }
  }
  return 0;
}

static SKThreadId
__skCreateThread(SKEntryProc entry,
                 void *arg, 
                 void *stack,
                 u32   stackSize,
                 u32   priority,
                 u32    pid
                )
{
  SKThreadId rv;
  SKThread *t;

  /* Check parameters */
  CHECK_PRIORITY(priority);

  /* Look for a free thread structure */
  for (rv = 0; rv < SK_THREAD_MAX; ++rv) {
    if (__threads[rv].state == SK_STATE_FREE) {
      break;
    }
  }
  if (rv == SK_THREAD_MAX) {
    rv = SK_ERROR_MAX;
    goto end;
  }

  /* Initialize thread structure */
  t = __threads + rv;

  t->pid = pid;
  t->state = SK_STATE_STOPPED;
  t->priority = priority;
  emuInitContext( &(t->context), entry, arg, stack, stackSize);
  t->next = NULL;
  t->queue = NULL;
end:
  return rv;
}

static SKError
__skStartThread(SKThreadId id, int pidCheckFlag)
{
  SKError rv = SK_ERROR_OK;
  SKThread *t;

  DBG_ENTRY;
  if ( 0 == pidCheckFlag ) {
    GET_THREAD(t, id);
  }
  else { 
    GET_THREAD_NO_PIDCHECK(t,id);
  }
  switch(t->state) {
    case SK_STATE_STOPPED:
      if ((t->queue == NULL) || (t->queue == &__skRunQueue)) {
        /* Thread t was just started or pulled out of the run queue */
        t->state = SK_STATE_READY;
        __skEnqueueThread(&__skRunQueue, t);
      } else {
        /* Thread t was pulled out of a message queue */
        t->state = SK_STATE_WAITING;
        __skEnqueueThread(t->queue, t);
      }
      break;
  }

  if (__skRunningThread == NULL) {
    __skDispatchThread(NULL);
  } else if (__skRunningThread->priority < __skRunQueue->priority) {
    __skRunningThread->state = SK_STATE_READY;
    __skEnqueueAndYield(&__skRunQueue);
  }

end:
  DBG_EXIT;
  return rv;
}

SKThreadId
skFork(SKEntryProc entry,
    void *arg, 
    void *stack,
    u32   stackSize,
    u32   priority)
{
  u32 rv = __skCreateThread(entry, arg, stack, stackSize, priority, 
                            __skGetFreePid());
  __skStartThread(rv, 1); /* No pid check, because pid changes */
  return rv;
}

SKThreadId
skCreateThread(SKEntryProc entry,
    void *arg, 
    void *stack,
    u32   stackSize,
    u32   priority)
{
  u32 pid = 0;
  if ( __skRunningThread ) {
    pid = __skRunningThread->pid;
    __skUsePid(pid);
  }
  return __skCreateThread(entry, arg, stack, stackSize, priority, pid);
}

static void 
__skFreeResources(u32 pid)
{
  __skFreeMem(pid);
  return;
}

SKError
skDestroyThread(SKThreadId id)
{
  SKError rv = SK_ERROR_OK;
  SKThread *t;

  GET_THREAD(t, id);

  __skFreePid(t->pid);
  if ( 0 == __skIsUsedPid(t->pid) ) {
    __skFreeResources(t->pid);
  }
  if (t->state != SK_STATE_STOPPED) {
    __skDequeueThread(t->queue, t);
  }
  t->state = SK_STATE_FREE;
  DBG_PRINTF((dbg_fp,"SK: thread id:%d destroyed\n", __skRunningThread - __threads));

  if (t == __skRunningThread) {
    __skDispatchThread(t);
  }

end:
  return rv;
}

SKThreadId
skGetThreadId(void)
{
  return __skRunningThread - __threads;
}

SKProcessId
skGetProcessId(void)
{
  return __skRunningThread->pid;
}

void
__skRestartThread(SKThread **queue)
{
  SKThread *t = __skPopThread(queue);
  t->state = SK_STATE_READY;
  __skEnqueueThread(&__skRunQueue, t);
  if (__skRunningThread->priority < __skRunQueue->priority) {
    __skRunningThread->state = SK_STATE_READY;
    __skEnqueueAndYield(&__skRunQueue);
  }

}


SKError
skStartThread(SKThreadId id)
{
 return  __skStartThread(id, 0); /* With pid check */
}

SKError
skStopThread(SKThreadId id)
{
  SKError rv = SK_ERROR_OK;
  SKThread *t;

  GET_THREAD(t, id);

  switch(t->state) {
    case SK_STATE_RUNNING:
      t->state = SK_STATE_STOPPED;
      __skEnqueueAndYield(NULL);
      break;
    case SK_STATE_READY:
    case SK_STATE_WAITING:
      t->state = SK_STATE_STOPPED;
      __skDequeueThread(t->queue, t);
      break;
  }

end:
  return rv;
}

void
skYieldThread(void)
{
  __skRunningThread->state = SK_STATE_READY;
  __skEnqueueAndYield(&__skRunQueue);
}

s32
skGetThreadPriority(SKThreadId id)
{
  SKThread *t;
  s32 rv;

  GET_THREAD(t, id);

  rv = t->priority;
end:
  return rv;
}

SKError
skSetThreadPriority(SKThreadId id, u32 priority)
{
  SKThread *t;
  SKError rv = SK_ERROR_OK;

  CHECK_PRIORITY(priority);

  GET_THREAD(t, id);

  /* Update scheduling if priorities changed */
  if (t->priority != priority) {
    t->priority = priority;

    /* Reschedule thread by removing and reinserting into queue */
    if ((t != __skRunningThread) &&
        (t->state != SK_STATE_STOPPED)) {
      __skDequeueThread(t->queue, t);
      __skEnqueueThread(t->queue, t);
    }

    /* If running thread is no longer the highest priority, then yield */
    if (__skRunningThread->priority < __skRunQueue->priority) {
      __skRunningThread->state = SK_STATE_READY;
      __skEnqueueAndYield(&__skRunQueue);
    }
  }

end:
  return rv;
}

void
__skInitThreads(void)
{
  u32 id = skCreateThread(__idleThread, 0, __skIdleStack, IDLE_STACK_SIZE, SK_PRIORITY_MAX);
  skStartThread(id);
}
