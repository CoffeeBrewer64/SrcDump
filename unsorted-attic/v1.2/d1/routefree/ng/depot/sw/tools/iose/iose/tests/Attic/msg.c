/* Test creating and destroying message queues.
 * Create a message queue and a reader thread.
 * Write messages to queue.
 * Verify that reader thread can read the messages.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>

#define NUM_ITER 5
#define MSGQ_SIZE 8
#define STACK_SIZE 16*1024
#define PID_MASK 0xFFFFFFFF
//#define PID_MASK 0x00000004
#define Q_MAX 32

IOSMessage msgQ[MSGQ_SIZE];
IOSMessageQueueId Qid[Q_MAX + 1];

void 
test_createQ()
{
  int i;
  for ( i = 0; i < Q_MAX + 1; ++i ) { 
    printf("Creating queue %d\n", i);
    Qid[i]  = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
    if ( Qid[i] < 0 ) {
      IOS_Perror("creating msg queue failed", Qid[i]);
    }
  }
}

void 
test_destroyQ()
{
  int i;
  for ( i = 0; i < Q_MAX + 1; ++i ) { 
    printf("Destroying queue %d\n", Qid[i]);
    IOSError ret = IOS_DestroyMessageQueue(Qid[i]);
    if ( ret < 0 ) {
      IOS_Perror("destroying msg queue failed", ret);
    }
  }
}

/* Create a thread of higher priority than current thread.
 * It creates a msgQ and puts id in global, lowers it priority/
 * Send msg to thread. Thread reads message.
 */

#define STACK_SIZE 16*1024
IOSMessageQueueId qid = -1;

void
rdr_thread(u32 x)
{
  char *msg;
  unsigned i = 0;
  unsigned k = 0;
  qid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
  if ( qid < 0 ) {
    IOS_Perror("creating msg queue failed", qid);
    goto out;
  }
  printf("msg queue %d created...\n", qid);
  for ( i = 0; i < NUM_ITER; ++i) {
    for ( k = 0; k < MSGQ_SIZE; ++k ) {
      IOS_ReceiveMessage(qid, (IOSMessage *) &msg, IOS_MESSAGE_BLOCK);
      if ( NULL == msg) {
        printf("Received null message\n");
        goto out;
      }
    }
    printf("|reader read msg: %s %d times\n", msg, MSGQ_SIZE);
  }
  IOS_DestroyMessageQueue(qid);
out:
  IOS_ThreadExit(0);
}

void 
create_rdr()
{
  u32 *progStack = (void *) malloc(STACK_SIZE);
  u32 id = IOS_CreateThread(rdr_thread, 0, progStack, STACK_SIZE, IOS_GetThreadPriority(0) + 1);
  IOS_StartThread(id);
}

void
send_msgs()
{
  IOSError err;
  char msg[32];
  unsigned i = 0;
  unsigned k = 0;
  for ( i = 0; i < NUM_ITER; ++i) {
    sprintf(msg,"tst-msg-%u", i);
    printf("writer sending msg: %s %d times\t", msg, MSGQ_SIZE);
    for ( k = 0; k < MSGQ_SIZE; ++k ) {
      err = IOS_SendMessage(qid, (IOSMessage) msg, IOS_MESSAGE_BLOCK);
      if ( err != IOS_ERROR_OK ) {
        IOS_Perror("SendMessage failed: ", err);
        IOS_ThreadExit(0);
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
  IOS_ThreadExit(0);
}
