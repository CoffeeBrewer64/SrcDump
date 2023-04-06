/* Create threads that register to handle events 
 * SK_EVENT_MIN, SK_EVENT_MIN + 1, ..., SK_EVENT_MIN + 4.
 * Test whether they get woken up by sending "events" to ske
 * in the form of signals SK_EVENT_MIN, ... SK_EVENT_MIN + 4
 * (say, by running 'killall -s <signal #> ske')
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
#define STACK_SIZE 16*1024
#define MSGQ_SIZE 8
#define NUM_EVENTS 5
SKMessage msgQ[MSGQ_SIZE];

void
event_thread(u32 s)
{
  char msg[32];
  char *rmsg;
  SKMessage msgQ[MSGQ_SIZE];
  SKMessageQueueId Qid;

  sprintf(msg,"tst-event-%u", s);
  Qid = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
  if ( Qid < 0 ) {
    SK_Perror("creating msg queue failed", Qid);
  }
  SK_HandleEvent(s, Qid, (SKMessage) msg);
  printf("Event handler registered for %u\n", s);
  while(1) {
    SK_ReceiveMessage(Qid, (SKMessage *) &rmsg, SK_MESSAGE_BLOCK);
    printf("reader read msg: %s\n", rmsg);
  }
  SK_ThreadExit(0);
}

void 
create_eventthr(u32 sig)
{
  u32 *progStack = (void *) malloc(STACK_SIZE);
  u32 id = SK_CreateThread(event_thread, (void *) &sig, progStack, STACK_SIZE, SK_GetThreadPriority(0) - 1);
  SK_StartThread(id);
}

void
multi_event(void)
{
  int i;
  for ( i = 0; i < NUM_EVENTS; ++i )
    create_eventthr(SK_EVENT_MIN + i);
  SK_SetThreadPriority(0, 50);
  while (1)
    SK_YieldThread();
}
