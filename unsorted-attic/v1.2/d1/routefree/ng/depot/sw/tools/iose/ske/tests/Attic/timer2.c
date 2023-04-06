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
//#define PID_MASK 0x00000004
#define Q_MAX 32

SKMessage msgQ[MSGQ_SIZE];
SKMessageQueueId Qid[Q_MAX + 1];

SKMessageQueueId qid = -1;
void
timer2(u32 id)
{
  char msg[32];
  int idx;
  unsigned v = 10;
  sprintf(msg, "timer_msg");
  qid = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
  if ( qid < 0 ) {
      goto done;
  }

  idx = SK_SetTimer(2, qid, (u32)msg); 
  idx = SK_SetTimer(2, qid, (u32)msg); 
  idx = SK_SetTimer(3, qid, (u32)msg); 
  idx = SK_SetTimer(3, qid, (u32)msg); 
  idx = SK_SetTimer(3, qid, (u32)msg); 
  fprintf(stderr,"[timer]: Timer list\n");
  SK_DebugTimerListDump();
  /* all till after above timers are done */
  while (1) {
      if ( 0 != (v = sleep(v)) && errno == EINTR )
          continue; 
      break;
  }

  fprintf(stderr,"[timer]: Timer list should be empty\n");
  SK_DebugTimerListDump();
  
done:
  SK_ThreadExit(0);
}
