/* Tests to allocate and free memory */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <ios.h>
#include <iostypes.h>
#define NUM_ITER 3
#include <errno.h>

#define COUNT 5
void 
tst_thread(u32 dummy)
{
  int i;
  for ( i = 0; i < COUNT; ++i) {
    printf("This is a test thread .. count %d of %d\n", i, COUNT);
  }
  errno = 43;
  printf("errno set to %d in tst_thread\n", errno);
  IOS_ThreadExit(0);
}

#define STACK_SIZE 16*1024

u32
test_create(void)
{
//  u32 *progStack = (void *) malloc(STACK_SIZE);
  u32 *progStack = (void *) IOS_Alloc(STACK_SIZE/512);
  if ( NULL == progStack ) {
    printf("IOS_alloc failed \n");
    return 0;
  }
  u32 id = IOS_CreateThread(tst_thread, 0, progStack, STACK_SIZE, 49);
  return id;
}
 
void 
test_start(u32 id)
{
  IOS_StartThread(id);
  IOS_SetThreadPriority(id, 100);
}

void
mem(u32 id)
{
  u32 *tst;
  int i = 0;
  for ( i = 0; i < 10; ++i ) {
    tst = IOS_Alloc(STACK_SIZE/4096);
    printf("itr[%d]:allocated %d pages\n", i, STACK_SIZE/4096);
    if (NULL != tst) 
      IOS_Free(tst);
    printf("itr[%d]:freed %d pages\n", i, STACK_SIZE/4096);
  }
  tst = IOS_Alloc(STACK_SIZE/4096);
  tst = IOS_Alloc(STACK_SIZE/4096);
  tst = IOS_Alloc(STACK_SIZE/4096);
  IOS_Free( (tst + 2*1024));
  IOS_DebugMemDump();
  IOS_ThreadExit(0);
}
