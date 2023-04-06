/* Register handler for "event" SK_EVENT_MIN.
 * Handle NUM_EVENTS events.
 * De-register handler and exit.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include <sk.h>
#include <sktypes.h>
#include <nglibc.h>

#define MSGQ_SIZE 8
#define PID_MASK 0xFFFFFFFF

SKMessage msgQ[MSGQ_SIZE];
#define MSGQ_SIZE 8
#define NUM_EVENTS 5

void
event()
{
  char msg[32];
  char *rmsg;
  SKMessage msgQ[MSGQ_SIZE];
  SKMessageQueueId qid;
  int i;

  sprintf(msg,"tst-event-%d", SK_EVENT_MIN);
  qid = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
  if ( qid < 0 ) {
    SK_Perror("creating msg queue failed", qid);
  }
  SK_HandleEvent(SK_EVENT_MIN, qid, (SKMessage) msg);
  printf("Event handler registered for %d\n", SK_EVENT_MIN );
  for ( i = 0; i < 5; ++i ) {
    SK_ReceiveMessage(qid, (SKMessage *) &rmsg, SK_MESSAGE_BLOCK);
    printf("reader read msg: %s\n", rmsg);
  }
  SK_UnhandleEvent(SK_EVENT_MIN);
  SK_ThreadExit(0);
}
