/* Main thread creates a thread of higher priority than itself.
 * This thread creates a msgQ & puts id in a global. It then lowers
 * its own priority. It blocks waiting for messages.
 * Send msg to thread. Thread reads message.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>

#define NUM_ITER 1
#define MSGQ_SIZE 32
#define STACK_SIZE 16*1024
#define PID_MASK 0xFFFFFFFF
//#define PID_MASK 0x00000004
#define Q_MAX 32

IOSMessage msgQ[MSGQ_SIZE];
IOSMessageQueueId Qid[Q_MAX + 1];

#define STACK_SIZE 16*1024
IOSMessageQueueId qid = -1;

void
rdr_thread(u32 x)
{
  char *msg;
  unsigned i = 0;
  qid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
  if ( qid < 0 ) {
    IOS_Perror("creating msg queue failed", qid);
    goto out;
  }
  printf("msg queue %d created...\n", qid);
  for ( i = 0; i < 33; ++i) {
    IOS_ReceiveMessage(qid, (IOSMessage *) &msg, IOS_MESSAGE_BLOCK);
    if ( NULL == msg) {
      printf("Received null message\n");
      goto out;
    }
    printf("reader read msg: %s\n", msg);
    free(msg);
  }
  IOS_DestroyMessageQueue(qid);
out:
  IOS_ThreadExit(0);
}

void 
create_rdr()
{
  u32 *progStack = (void *) malloc(STACK_SIZE);
  u32 id = IOS_CreateThread(rdr_thread, 0, progStack, STACK_SIZE, IOS_GetThreadPriority(0));
  IOS_StartThread(id);
  IOS_YieldThread();
}

void
send_msgs()
{
  IOSError err;
  char *msg[33];
  unsigned i = 0;
  for ( i = 0; i < 32; ++i) {
    msg[i] = (char *) malloc(32*sizeof(char));
    sprintf(msg[i],"tst-msg-%u", i);
    printf("writer sending msg: %s\n", msg[i]);
    err = IOS_SendMessage(qid, (IOSMessage) msg[i], IOS_MESSAGE_BLOCK);
    if ( err != IOS_ERROR_OK ) {
      IOS_Perror("SendMessage failed: ", err);
      IOS_ThreadExit(0);
    }
  }
  msg[32] = (char *) malloc(32*sizeof(char));
  sprintf(msg[32],"block-msg");
  printf("writer sending msg: %s\n", msg[32]);
  err = IOS_SendMessage(qid, (IOSMessage) msg[32], IOS_MESSAGE_BLOCK);
  if ( err != IOS_ERROR_OK ) {
    IOS_Perror("SendMessage failed: ", err);
    IOS_ThreadExit(0);
  }
}

void 
test_blockmsg()
{
  create_rdr();
  send_msgs();
}

void
block(u32 id)
{
  test_blockmsg();
  IOS_ThreadExit(0);
}
