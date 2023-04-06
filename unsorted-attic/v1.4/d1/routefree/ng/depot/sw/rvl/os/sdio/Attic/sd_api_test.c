d11 1
a11 1
 * $Id: sd_api_test.c,v 1.3 2006/03/16 19:31:58 gbarnard Exp $
d14 1
a14 1
static char ident[] = "$Id: sd_api_test.c,v 1.3 2006/03/16 19:31:58 gbarnard Exp $";
d457 1
a457 1
	set_driver_debug(Handles[config.SDDevSlot][0],1); //|DEBUG_SER_CMD|DEBUG_SER_SD_CMD|DEBUG_SER_REG_READ|DEBUG_SER_REG_WRITE); /* debug error messages in sdio host driver */    
d550 2
a551 2
    IOSMessageQueueId qid;
    IOSMessage msgQ[MSGQ_SIZE];
d569 1
d587 1
d600 1
a600 1
    return IOS_ThreadExit(0);
