/* Main thread creates a thread of higher priority than current thread.
 * That thread creates a msgQ and puts id in a global. It lowers its 
 * priority.
 * Main thread sends 3 msgs. Jams 4th message.
 * The reader thread read and prints messages 4, 1, 2, 3.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sk.h>
#include <sktypes.h>
#include <nglibc.h>

#define NUM_ITER 1
#define MSGQ_SIZE 8
#define STACK_SIZE 16*1024
#define PID_MASK 0xFFFFFFFF /* for now */
#define Q_MAX 32

SKMessage msgQ[MSGQ_SIZE];
SKMessageQueueId Qid[Q_MAX + 1];


#define STACK_SIZE 16*1024
SKMessageQueueId qid = -1;

void
rdr_thread(u32 x)
{
  char *msg;
  unsigned i = 0;
  qid = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
  if ( qid < 0 ) {
    SK_Perror("creating msg queue failed", qid);
    goto out;
  }
  printf("msg queue %d created...\n", qid);
  for ( i = 0; i < 4; ++i) {
    SK_ReceiveMessage(qid, (SKMessage *) &msg, SK_MESSAGE_BLOCK);
    if ( NULL == msg) {
      DBG_PRINTF((dbg_fp,"Received null message\n"));
      goto out;
    }
    printf("reader read msg: %s\n", msg);
  }
  SK_DestroyMessageQueue(qid);
out:
  SK_ThreadExit(0);
}

void 
create_rdr()
{
  u32 *progStack = (void *) malloc(STACK_SIZE);
  u32 id = SK_CreateThread(rdr_thread, 0, progStack, STACK_SIZE, SK_GetThreadPriority(0));
  SK_StartThread(id);
  SK_YieldThread();
}

void
send_msgs()
{
  SKError err;
  char msg[4][32];
  unsigned i = 0;
  for ( i = 0; i < 3; ++i) {
    sprintf(msg[i],"tst-msg-%u", i);
    printf("writer sending msg: %s\n", msg[i]);
    err = SK_SendMessage(qid, (SKMessage) msg[i], SK_MESSAGE_BLOCK);
    if ( err != SK_ERROR_OK ) {
      SK_Perror("SendMessage failed: ", err);
      SK_ThreadExit(0);
    }
  }
  sprintf(msg[3],"jam-msg");
  printf("writer sending msg: %s\n", msg[3]);
  err = SK_JamMessage(qid, (SKMessage) msg[3], SK_MESSAGE_BLOCK);
  if ( err != SK_ERROR_OK ) {
    SK_Perror("SendMessage failed: ", err);
    SK_ThreadExit(0);
  }
  SK_YieldThread();
}

void 
test_jammsg()
{
  create_rdr();
  send_msgs();
}

void
jam(u32 id)
{
  test_jammsg();
  SK_ThreadExit(0);
}
