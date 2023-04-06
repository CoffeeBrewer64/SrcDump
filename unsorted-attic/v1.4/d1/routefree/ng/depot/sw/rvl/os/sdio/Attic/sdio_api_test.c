d11 1
a11 1
 * $Id: sdio_api_test.c,v 1.3 2006/03/18 01:16:12 gbarnard Exp $
d14 1
a14 1
char ident[] = "$Id: sdio_api_test.c,v 1.3 2006/03/18 01:16:12 gbarnard Exp $";
a55 1
#define PID_MASK 0xFFFFFFFF
d705 1
a705 1
    if ( (qid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK )) < 0 ) {
