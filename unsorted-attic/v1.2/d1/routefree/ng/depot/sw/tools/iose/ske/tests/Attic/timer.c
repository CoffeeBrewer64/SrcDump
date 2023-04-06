#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

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
timer(u32 id)
{
  char msg[32];
  int idx;
  sprintf(msg, "timer_msg");
  qid = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
  if ( qid < 0 ) {
      SK_Perror("creating msg queue failed", qid);
      goto done;
  }

#if 0
  idx = SK_SetTimer(5, qid, (u32)msg); 
  fprintf(stderr,"[timer]: settimer(10) returned index: %d\n",idx);
#endif

  idx = SK_SetTimer(3, qid, (u32)msg); 
  fprintf(stderr,"[timer]: settimer(3) returned index: %d\n",idx);
  SK_StopTimer(idx);
  fprintf(stderr,"[timer]: stopped timer(3)\n");
  fprintf(stderr,"[timer]: Timer list should be empty again\n");
  SK_DebugTimerListDump();
 
#if 0
  idx = SK_SetTimer(2, qid, (u32)msg); 
  fprintf(stderr,"[timer]: settimer(2) returned index: %d\n",idx);
  
  sleep(8); /* all till after above timers are done */
  
  fprintf(stderr,"[timer]: Timer list should be empty now\n");
  SK_DebugTimerListDump();
#endif
  idx = SK_SetTimer(3, qid, (u32)msg); 
  fprintf(stderr,"[timer]: new settimer(3) returned index: %d\n",idx);
  sleep(4); /* all till after above timers are done */
  fprintf(stderr,"[timer]: Timer list should be empty again\n");
  SK_DebugTimerListDump();
  
done:
  SK_ThreadExit(0);
}
