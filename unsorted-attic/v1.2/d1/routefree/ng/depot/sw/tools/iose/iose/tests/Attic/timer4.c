#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>

#define MSGQ_SIZE 8
#define STACK_SIZE 16*1024
#define PID_MASK 0xFFFFFFFF
#define Q_MAX 32

IOSMessage msgQ[MSGQ_SIZE];
IOSMessageQueueId Qid[Q_MAX + 1];

IOSMessageQueueId qid = -1;
#define NUM_TIMER 5
void
rdr_thread(u32 x)
{
  char *msg;
  unsigned count = 0;
  
  printf("rdr thread starts running\n");
  while (1) {
      IOS_ReceiveMessage(qid, (IOSMessage *) &msg, IOS_MESSAGE_BLOCK);
      if ( NULL == msg) {
          printf("Received null message\n");
          goto out;
      }
      count++;
      printf("Read timer msg[%d]: %s\n", count, msg);
      if ( count >= NUM_TIMER ) 
          goto out;
  }
out:
  IOS_DestroyMessageQueue(qid);
  IOS_ThreadExit(0);
}

u32
create_rdr()
{
  u32 *progStack = (void *) malloc(STACK_SIZE);
  u32 id = IOS_CreateThread(rdr_thread, 0, progStack, STACK_SIZE, IOS_GetThreadPriority(0) - 1);
  IOS_StartThread(id);
  return id;
}

void
timer4(u32 x)
{
    char msg[NUM_TIMER][32];
    int t[]= {6, 9, 5, 2, 4}; /* NUM_TIMER # of times for timers */
    u32 id;
    int i;
    if ( 0 > (qid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK )))
            goto done;
    id = create_rdr();
    for ( i = 0; i < NUM_TIMER; ++i ) {
        sprintf(msg[i], "timer-period:%d expired\n", t[i]);
        IOS_SetTimer(t[i], qid, (u32)msg[i]);
    }
    IOS_SetThreadPriority(id, 127);
    sleep(20);
done:
    IOS_ThreadExit(0);
}
