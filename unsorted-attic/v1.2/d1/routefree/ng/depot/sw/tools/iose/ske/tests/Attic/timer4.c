#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include <sk.h>
#include <sktypes.h>
#include <nglibc.h>

#define MSGQ_SIZE 8
#define STACK_SIZE 16*1024
#define PID_MASK 0xFFFFFFFF
#define Q_MAX 32

SKMessage msgQ[MSGQ_SIZE];
SKMessageQueueId Qid[Q_MAX + 1];

SKMessageQueueId qid = -1;
#define NUM_TIMER 5
void
rdr_thread(u32 x)
{
  char *msg;
  unsigned count = 0;
  
  DBG_PRINTF((dbg_fp,"rdr thread starts running\n"));
  while (1) {
      SK_ReceiveMessage(qid, (SKMessage *) &msg, SK_MESSAGE_BLOCK);
      if ( NULL == msg) {
          DBG_PRINTF((dbg_fp,"Received null message\n"));
          goto out;
      }
      count++;
      printf("Read timer msg[%d]: %s\n", count, msg);
      if ( count >= NUM_TIMER ) 
          goto out;
  }
out:
  SK_DestroyMessageQueue(qid);
  SK_ThreadExit(0);
}

u32
create_rdr()
{
  u32 *progStack = (void *) malloc(STACK_SIZE);
  u32 id = SK_CreateThread(rdr_thread, 0, progStack, STACK_SIZE, SK_GetThreadPriority(0) - 1);
  SK_StartThread(id);
  return id;
}

void
timer4(u32 x)
{
    char msg[NUM_TIMER][32];
    int t[]= {6, 9, 5, 2, 4}; /* NUM_TIMER # of times for timers */
    u32 id;
    int i;
    if ( 0 > (qid = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK )))
            goto done;
    id = create_rdr();
    for ( i = 0; i < NUM_TIMER; ++i ) {
        sprintf(msg[i], "timer-period:%d expired\n", t[i]);
        SK_SetTimer(t[i], qid, (u32)msg[i]);
    }
    SK_SetThreadPriority(id, 127);
    sleep(20);
done:
    SK_ThreadExit(0);
}
