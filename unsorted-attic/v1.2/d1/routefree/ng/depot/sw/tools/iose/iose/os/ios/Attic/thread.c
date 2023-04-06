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
#include <iosdebug.h>
#include <iostypes.h>
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


static IOSThread __threads[IOS_THREAD_MAX];
static u8 __pids[IOS_PID_MAX]; /* compiler initialized to all 0's */

IOSThread __iosThreadTail = {
    {},
    NULL,
    -1
};

IOSThread *__iosRunQueue = &__iosThreadTail;
IOSThread *__iosRunningThread = 0;

#define CHECK_THREAD_ID(id) \
    if (((id) < 0) || ((id) >= IOS_THREAD_MAX)) {\
        rv = IOS_ERROR_INVALID; \
        goto end; \
    } else

#define CHECK_PROCESS_ID(p) \
    if ((p) != (__iosRunningThread ? __iosRunningThread->pid : 0)) { \
        rv = IOS_ERROR_INVALID; \
        goto end; \
    } else

#define CHECK_PRIORITY(pri) \
    if ((pri) > IOS_PRIORITY_MAX) { \
        rv = IOS_ERROR_INVALID; \
        goto end; \
    } else

#define GET_THREAD(t, id) \
    if (id == 0 && __iosRunningThread) { \
        t = __iosRunningThread; \
    } else { \
        CHECK_THREAD_ID(id); \
        t = __threads + id; \
        CHECK_PROCESS_ID(t->pid); \
    }
    
#define GET_THREAD_NO_PIDCHECK(t,id) \
    if (id == 0 && __iosRunningThread) { \
        t = __iosRunningThread; \
    } else { \
        CHECK_THREAD_ID(id); \
        t = __threads + id; \
    }

void
__iosEnqueueThread(IOSThread **queue, IOSThread *new)
{
    IOSThread **prev = queue;
    IOSThread *next = *prev;

    while (next->priority >= new->priority) {
        prev = &(next->next);
        next = next->next;
    }

    *prev = new;
    new->next = next;
    new->queue = queue;
}

void
__iosDequeueThread(IOSThread **queue, IOSThread *t)
{
    IOSThread **prev = queue;
    IOSThread *next = *prev;

    while (next != NULL) {
        if (next == t) {
            *prev = next->next;
            return;
        }
        prev = &(next->next);
        next = next->next;
    }
}

IOSThread *
__iosPopThread(IOSThread **queue)
{
    IOSThread *t = *queue;
    *queue = t->next;
    return t;
}

static inline void
__iosUsePid(u32 i)
{
  ++__pids[i];
  DBG_PRINTF((dbg_fp, "Setting use count for pid %u to %u\n", i, __pids[i]));
}

static inline void 
__iosFreePid(u32 i)
{
  --__pids[i];
  DBG_PRINTF((dbg_fp, "Setting use count for pid %u to %u\n", i, __pids[i]));
}

static inline u8
__iosIsUsedPid(u32 i)
{
   return __pids[i];
}
static u32 
__iosGetFreePid()
{
  u32 i;
  for (i = 0; i < IOS_PID_MAX; ++i) {
    if ( 0 == __pids[i] ) {
      __pids[i] = 1;
      return i;
    }
  }
  return 0;
}

static IOSThreadId
__iosCreateThread(IOSEntryProc entry,
                 void *arg, 
                 void *stack,
                 u32   stackSize,
                 u32   priority,
                 u32    pid
                )
{
  IOSThreadId rv;
  IOSThread *t;

  /* Check parameters */
  CHECK_PRIORITY(priority);

  /* Look for a free thread structure */
  for (rv = 0; rv < IOS_THREAD_MAX; ++rv) {
    if (__threads[rv].state == IOS_STATE_FREE) {
      break;
    }
  }
  if (rv == IOS_THREAD_MAX) {
    rv = IOS_ERROR_MAX;
    goto end;
  }

  /* Initialize thread structure */
  t = __threads + rv;

  t->pid = pid;
  t->state = IOS_STATE_STOPPED;
  t->priority = priority;
  emuInitContext( &(t->context), entry, arg, stack, stackSize);
  t->next = NULL;
  t->queue = NULL;
end:
  return rv;
}

static IOSError
__iosStartThread(IOSThreadId id, int pidCheckFlag)
{
  IOSError rv = IOS_ERROR_OK;
  IOSThread *t;

  DBG_ENTRY;
  if ( 0 == pidCheckFlag ) {
    GET_THREAD(t, id);
  }
  else { 
    GET_THREAD_NO_PIDCHECK(t,id);
  }
  switch(t->state) {
    case IOS_STATE_STOPPED:
      if ((t->queue == NULL) || (t->queue == &__iosRunQueue)) {
        /* Thread t was just started or pulled out of the run queue */
        t->state = IOS_STATE_READY;
        __iosEnqueueThread(&__iosRunQueue, t);
      } else {
        /* Thread t was pulled out of a message queue */
        t->state = IOS_STATE_WAITING;
        __iosEnqueueThread(t->queue, t);
      }
      break;
  }

  if (__iosRunningThread == NULL) {
    __iosDispatchThread(NULL);
  } else if (__iosRunningThread->priority < __iosRunQueue->priority) {
    __iosRunningThread->state = IOS_STATE_READY;
    __iosEnqueueAndYield(&__iosRunQueue);
  }

end:
  DBG_EXIT;
  return rv;
}

IOSThreadId
iosFork(IOSEntryProc entry,
    void *arg, 
    void *stack,
    u32   stackSize,
    u32   priority)
{
  u32 rv = __iosCreateThread(entry, arg, stack, stackSize, priority, 
                            __iosGetFreePid());
  __iosStartThread(rv, 1); /* No pid check, because pid changes */
  return rv;
}

IOSThreadId
iosCreateThread(IOSEntryProc entry,
    void *arg, 
    void *stack,
    u32   stackSize,
    u32   priority)
{
  u32 pid = 0;
  if ( __iosRunningThread ) {
    pid = __iosRunningThread->pid;
    __iosUsePid(pid);
  }
  return __iosCreateThread(entry, arg, stack, stackSize, priority, pid);
}

static void 
__iosFreeResources(u32 pid)
{
  __iosFreeMem(pid);
  return;
}

IOSError
iosDestroyThread(IOSThreadId id)
{
  IOSError rv = IOS_ERROR_OK;
  IOSThread *t;

  GET_THREAD(t, id);

  __iosFreePid(t->pid);
  if ( 0 == __iosIsUsedPid(t->pid) ) {
    __iosFreeResources(t->pid);
  }
  if (t->state != IOS_STATE_STOPPED) {
    __iosDequeueThread(t->queue, t);
  }
  t->state = IOS_STATE_FREE;
  DBG_PRINTF((dbg_fp,"IOS: thread id:%d destroyed\n", __iosRunningThread - __threads));

  if (t == __iosRunningThread) {
    __iosDispatchThread(t);
  }

end:
  return rv;
}

IOSThreadId
iosGetThreadId(void)
{
  return __iosRunningThread - __threads;
}

IOSProcessId
iosGetProcessId(void)
{
  return __iosRunningThread->pid;
}

void
__iosRestartThread(IOSThread **queue)
{
  IOSThread *t = __iosPopThread(queue);
  t->state = IOS_STATE_READY;
  __iosEnqueueThread(&__iosRunQueue, t);
  if (__iosRunningThread->priority < __iosRunQueue->priority) {
    __iosRunningThread->state = IOS_STATE_READY;
    __iosEnqueueAndYield(&__iosRunQueue);
  }

}


IOSError
iosStartThread(IOSThreadId id)
{
 return  __iosStartThread(id, 0); /* With pid check */
}

IOSError
iosStopThread(IOSThreadId id)
{
  IOSError rv = IOS_ERROR_OK;
  IOSThread *t;

  GET_THREAD(t, id);

  switch(t->state) {
    case IOS_STATE_RUNNING:
      t->state = IOS_STATE_STOPPED;
      __iosEnqueueAndYield(NULL);
      break;
    case IOS_STATE_READY:
    case IOS_STATE_WAITING:
      t->state = IOS_STATE_STOPPED;
      __iosDequeueThread(t->queue, t);
      break;
  }

end:
  return rv;
}

void
iosYieldThread(void)
{
  __iosRunningThread->state = IOS_STATE_READY;
  __iosEnqueueAndYield(&__iosRunQueue);
}

s32
iosGetThreadPriority(IOSThreadId id)
{
  IOSThread *t;
  s32 rv;

  GET_THREAD(t, id);

  rv = t->priority;
end:
  return rv;
}

IOSError
iosSetThreadPriority(IOSThreadId id, u32 priority)
{
  IOSThread *t;
  IOSError rv = IOS_ERROR_OK;

  CHECK_PRIORITY(priority);

  GET_THREAD(t, id);

  /* Update scheduling if priorities changed */
  if (t->priority != priority) {
    t->priority = priority;

    /* Reschedule thread by removing and reinserting into queue */
    if ((t != __iosRunningThread) &&
        (t->state != IOS_STATE_STOPPED)) {
      __iosDequeueThread(t->queue, t);
      __iosEnqueueThread(t->queue, t);
    }

    /* If running thread is no longer the highest priority, then yield */
    if (__iosRunningThread->priority < __iosRunQueue->priority) {
      __iosRunningThread->state = IOS_STATE_READY;
      __iosEnqueueAndYield(&__iosRunQueue);
    }
  }

end:
  return rv;
}

void
__iosInitThreads(void)
{
  u32 id = iosCreateThread(__idleThread, 0, __iosIdleStack, IDLE_STACK_SIZE, IOS_PRIORITY_MAX);
  iosStartThread(id);
}
