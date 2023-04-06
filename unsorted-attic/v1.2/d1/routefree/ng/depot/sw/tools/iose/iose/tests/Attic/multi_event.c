/* Create threads that register to handle events 
 * IOS_EVENT_MIN, IOS_EVENT_MIN + 1, ..., IOS_EVENT_MIN + 4.
 * Test whether they get woken up by sending "events" to iose
 * in the form of signals IOS_EVENT_MIN, ... IOS_EVENT_MIN + 4
 * (say, by running 'killall -s <signal #> iose')
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
#define STACK_SIZE 16*1024
#define MSGQ_SIZE 8
#define NUM_EVENTS 5
IOSMessage msgQ[MSGQ_SIZE];

void
event_thread(u32 s)
{
  char msg[32];
  char *rmsg;
  IOSMessage msgQ[MSGQ_SIZE];
  IOSMessageQueueId Qid;

  sprintf(msg,"tst-event-%u", s);
  Qid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
  if ( Qid < 0 ) {
    IOS_Perror("creating msg queue failed", Qid);
  }
  IOS_HandleEvent(s, Qid, (IOSMessage) msg);
  printf("Event handler registered for %u\n", s);
  while(1) {
    IOS_ReceiveMessage(Qid, (IOSMessage *) &rmsg, IOS_MESSAGE_BLOCK);
    printf("reader read msg: %s\n", rmsg);
  }
  IOS_ThreadExit(0);
}

void 
create_eventthr(u32 sig)
{
  u32 *progStack = (void *) malloc(STACK_SIZE);
  u32 id = IOS_CreateThread(event_thread, (void *) &sig, progStack, STACK_SIZE, IOS_GetThreadPriority(0) - 1);
  IOS_StartThread(id);
}

void
multi_event(void)
{
  int i;
  for ( i = 0; i < NUM_EVENTS; ++i )
    create_eventthr(IOS_EVENT_MIN + i);
  IOS_SetThreadPriority(0, 50);
  while (1)
    IOS_YieldThread();
}
