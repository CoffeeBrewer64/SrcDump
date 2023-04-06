d11 1
a11 1
 * $Id: sd_api_test.c,v 1.5 2006/03/18 01:16:12 gbarnard Exp $
d14 1
a14 1
static char ident[] = "$Id: sd_api_test.c,v 1.5 2006/03/18 01:16:12 gbarnard Exp $";
a62 2
#define PID_MASK 0xFFFFFFFF

d571 1
a571 1
    if ( (qid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, 0 ))<0) //PID_MASK )) < 0 ) 
