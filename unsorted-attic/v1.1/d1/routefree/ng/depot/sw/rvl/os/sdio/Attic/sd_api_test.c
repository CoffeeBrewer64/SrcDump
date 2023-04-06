d11 1
a11 1
 * $Id: sd_api_test.c,v 1.10 2006/01/18 23:21:27 gbarnard Exp $
d14 1
a14 1
static char ident[] = "$Id: sd_api_test.c,v 1.10 2006/01/18 23:21:27 gbarnard Exp $";
d246 2
a247 1
    	printf(" - GetSdStatus:%X %s\n",resp[0],(char*)decode_card_status(resp[0]));  	
d444 1
a444 1
	set_driver_debug(Handles[config.SDDevSlot][0],1|DEBUG_SER_CMD|DEBUG_SER_SD_CMD|DEBUG_SER_REG_READ|DEBUG_SER_REG_WRITE); /* debug error messages in sdio host driver */    
d454 1
d463 1
