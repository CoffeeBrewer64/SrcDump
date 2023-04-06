/* Tests for some thread related API */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sk.h>
#include <sktypes.h>
#define NUM_ITER 3
#include <errno.h>
void
test_gettid()
{
 printf("SK_GetThreadId: Current thread's id = %d\n", SK_GetThreadId());
 return;
}

void
test_getpid()
{
 printf("SK_GetProcessId: Current thread's pid = %d\n", SK_GetProcessId());
 return;
}

void 
test_getpriority()
{
 printf("SK_GetThreadPriority: Current thread's priority = %d\n", SK_GetThreadPriority(0));
 return;
}

void 
test_setpriority()
{
 u32 old = SK_GetThreadPriority(0);
 printf("SK_SetThreadPriority: Setting current thread's priority to %d\n",100);
 SK_SetThreadPriority(0, 100);
 sleep(1);
 SK_SetThreadPriority(0, old);
 return;
}

void
test_yield()
{
 printf("SK_YieldThread: Current thread yields\n");
 SK_YieldThread();
 return;
}

#define COUNT 5
void 
thread_func(u32 dummy)
{
  int i;
  for ( i = 0; i < COUNT; ++i) {
    printf("This is a test thread .. count %d of %d\n", i, COUNT);
  }
  errno = 43;
  printf("errno set to %d in thread_func\n", errno);
  SK_ThreadExit(0);
}

#define STACK_SIZE 16*1024

u32
test_create(void)
{
//  u32 *progStack = (void *) malloc(STACK_SIZE);
  u32 *progStack = (void *) SK_Alloc(STACK_SIZE/4096);
  if ( NULL == progStack ) {
    printf("SK_alloc failed \n");
    return 0;
  }
  u32 id = SK_CreateThread(thread_func, 0, progStack, STACK_SIZE, 49);
  return id;
}
 
void 
test_start(u32 id)
{
  SK_StartThread(id);
  SK_SetThreadPriority(id, 100);
}

void 
test_stop(u32 id)
{
  SK_StopThread(id);
}

void
thread_tst(u32 id)
{
  u32 thr;
  
  test_gettid();
  test_getpid();
  test_getpriority();
  test_setpriority();
  errno = 42;
  printf("errno = %d before thread switch\n", errno);
  thr = test_create();
  test_start(thr);
  test_stop(thr);
  test_yield();
  printf("errno = %d after thread switch\n", errno);

  SK_DebugMemDump();
  SK_ThreadExit(0);
}
