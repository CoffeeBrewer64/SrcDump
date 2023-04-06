/* Test creating and destroying message queues.
 * Create a message queue and a reader thread.
 * Write messages to queue.
 * Verify that reader thread can read the messages.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sk.h>
#include <sktypes.h>
#include <nglibc.h>

#define NUM_ITER 5
#define MSGQ_SIZE 8
#define STACK_SIZE 16*1024
#define PID_MASK 0xFFFFFFFF
//#define PID_MASK 0x00000004
#define Q_MAX 32

SKMessage msgQ[MSGQ_SIZE];
SKMessageQueueId Qid[Q_MAX + 1];

void 
test_createQ()
{
  int i;
  for ( i = 0; i < Q_MAX + 1; ++i ) { 
    printf("Creating queue %d\n", i);
    Qid[i]  = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
    if ( Qid[i] < 0 ) {
      SK_Perror("creating msg queue failed", Qid[i]);
    }
  }
}

void 
test_destroyQ()
{
  int i;
  for ( i = 0; i < Q_MAX + 1; ++i ) { 
    printf("Destroying queue %d\n", Qid[i]);
    SKError ret = SK_DestroyMessageQueue(Qid[i]);
    if ( ret < 0 ) {
      SK_Perror("destroying msg queue failed", ret);
    }
  }
}

/* Create a thread of higher priority than current thread.
 * It creates a msgQ and puts id in global, lowers it priority/
 * Send msg to thread. Thread reads message.
 */

#define STACK_SIZE 16*1024
SKMessageQueueId qid = -1;

void
rdr_thread(u32 x)
{
  char *msg;
  unsigned i = 0;
  unsigned k = 0;
  qid = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
  if ( qid < 0 ) {
    SK_Perror("creating msg queue failed", qid);
    goto out;
  }
  printf("msg queue %d created...\n", qid);
  for ( i = 0; i < NUM_ITER; ++i) {
    for ( k = 0; k < MSGQ_SIZE; ++k ) {
      SK_ReceiveMessage(qid, (SKMessage *) &msg, SK_MESSAGE_BLOCK);
      if ( NULL == msg) {
        DBG_PRINTF((dbg_fp,"Received null message\n"));
        goto out;
      }
    }
    printf("|reader read msg: %s %d times\n", msg, MSGQ_SIZE);
  }
  SK_DestroyMessageQueue(qid);
out:
  SK_ThreadExit(0);
}

void 
create_rdr()
{
  u32 *progStack = (void *) malloc(STACK_SIZE);
  u32 id = SK_CreateThread(rdr_thread, 0, progStack, STACK_SIZE, SK_GetThreadPriority(0) + 1);
  SK_StartThread(id);
}

void
send_msgs()
{
  SKError err;
  char msg[32];
  unsigned i = 0;
  unsigned k = 0;
  for ( i = 0; i < NUM_ITER; ++i) {
    sprintf(msg,"tst-msg-%u", i);
    printf("writer sending msg: %s %d times\t", msg, MSGQ_SIZE);
    for ( k = 0; k < MSGQ_SIZE; ++k ) {
      err = SK_SendMessage(qid, (SKMessage) msg, SK_MESSAGE_BLOCK);
      if ( err != SK_ERROR_OK ) {
        SK_Perror("SendMessage failed: ", err);
        SK_ThreadExit(0);
      }
    }
  }
}

void 
test_sndmsg()
{
  create_rdr();
  send_msgs();
}

void
msg(u32 id)
{
  test_createQ();
  test_destroyQ();
  test_sndmsg();
  SK_ThreadExit(0);
}
