/* Tests for some thread related API */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <ios.h>
#include <iostypes.h>
#define NUM_ITER 3
#include <errno.h>
void
test_gettid()
{
 printf("IOS_GetThreadId: Current thread's id = %d\n", IOS_GetThreadId());
 return;
}

void
test_getpid()
{
 printf("IOS_GetProcessId: Current thread's pid = %d\n", IOS_GetProcessId());
 return;
}

void 
test_getpriority()
{
 printf("IOS_GetThreadPriority: Current thread's priority = %d\n", IOS_GetThreadPriority(0));
 return;
}

void 
test_setpriority()
{
 u32 old = IOS_GetThreadPriority(0);
 printf("IOS_SetThreadPriority: Setting current thread's priority to %d\n",100);
 IOS_SetThreadPriority(0, 100);
 sleep(1);
 IOS_SetThreadPriority(0, old);
 return;
}

void
test_yield()
{
 printf("IOS_YieldThread: Current thread yields\n");
 IOS_YieldThread();
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
  IOS_ThreadExit(0);
}

#define STACK_SIZE 16*1024

u32
test_create(void)
{
//  u32 *progStack = (void *) malloc(STACK_SIZE);
  u32 *progStack = (void *) IOS_Alloc(STACK_SIZE/4096);
  if ( NULL == progStack ) {
    printf("IOS_alloc failed \n");
    return 0;
  }
  u32 id = IOS_CreateThread(thread_func, 0, progStack, STACK_SIZE, 49);
  return id;
}
 
void 
test_start(u32 id)
{
  IOS_StartThread(id);
  IOS_SetThreadPriority(id, 100);
}

void 
test_stop(u32 id)
{
  IOS_StopThread(id);
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

  IOS_DebugMemDump();
  IOS_ThreadExit(0);
}
