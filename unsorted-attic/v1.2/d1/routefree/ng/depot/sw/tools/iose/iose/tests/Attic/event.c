/* Register handler for "event" IOS_EVENT_MIN.
 * Handle NUM_EVENTS events.
 * De-register handler and exit.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>

#define MSGQ_SIZE 8
#define PID_MASK 0xFFFFFFFF

IOSMessage msgQ[MSGQ_SIZE];
#define MSGQ_SIZE 8
#define NUM_EVENTS 5

void
event()
{
  char msg[32];
  char *rmsg;
  IOSMessage msgQ[MSGQ_SIZE];
  IOSMessageQueueId qid;
  int i;

  sprintf(msg,"tst-event-%d", IOS_EVENT_MIN);
  qid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
  if ( qid < 0 ) {
    IOS_Perror("creating msg queue failed", qid);
  }
  IOS_HandleEvent(IOS_EVENT_MIN, qid, (IOSMessage) msg);
  printf("Event handler registered for %d\n", IOS_EVENT_MIN );
  for ( i = 0; i < 5; ++i ) {
    IOS_ReceiveMessage(qid, (IOSMessage *) &rmsg, IOS_MESSAGE_BLOCK);
    printf("reader read msg: %s\n", rmsg);
  }
  IOS_UnhandleEvent(IOS_EVENT_MIN);
  IOS_ThreadExit(0);
}
