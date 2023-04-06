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
timer1(u32 id)
{
  char msg[32];
  unsigned v = 10;
  sprintf(msg, "timer_msg");
  qid = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
  if ( qid < 0 ) {
      goto done;
  }

  fprintf(stderr,"Setting timer for 2 seconds\n");
  if ( SK_ERROR_MAX == SK_SetTimer(2, qid, (u32)msg ))
      fprintf(stderr,"Failed to set timer. All timers in use.\n");
  fprintf(stderr,"Setting timer for 3 seconds\n");
  if ( SK_ERROR_MAX == SK_SetTimer(3, qid, (u32)msg ))
      fprintf(stderr,"Failed to set timer. All timers in use.\n");
  fprintf(stderr,"Setting timer for 4 seconds\n");
  if ( SK_ERROR_MAX == SK_SetTimer(4, qid, (u32)msg ))
      fprintf(stderr,"Failed to set timer. All timers in use.\n");
  fprintf(stderr,"Setting timer for 5 seconds\n");
  if ( SK_ERROR_MAX == SK_SetTimer(5, qid, (u32)msg ))
      fprintf(stderr,"Failed to set timer. All timers in use.\n");
  fprintf(stderr,"Setting timer for 6 seconds\n");
  if ( SK_ERROR_MAX == SK_SetTimer(6, qid, (u32)msg ))
      fprintf(stderr,"Failed to set timer. All timers in use.\n");
  fprintf(stderr,"Setting timer for 7 seconds\n");
  if ( SK_ERROR_MAX == SK_SetTimer(7, qid, (u32)msg ))
      fprintf(stderr,"Failed to set timer. All timers in use.\n");
  fprintf(stderr,"Setting timer for 8 seconds\n");
  if ( SK_ERROR_MAX == SK_SetTimer(8, qid, (u32)msg ))
      fprintf(stderr,"Failed to set timer. All timers in use.\n");
  fprintf(stderr,"Sleeping waiting for timers to expire\n");
  /* all till after above timers are done */
  while (1) {
      if ( 0 != (v = sleep(v)) && errno == EINTR )
          continue; 
      break;
  }
  fprintf(stderr,"[timer]: Timer list\n");
  SK_DebugTimerListDump();

  fprintf(stderr,"[timer]: Timer list should be empty\n");
  SK_DebugTimerListDump();
  
done:
  SK_ThreadExit(0);
}
