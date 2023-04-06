d11 1
a11 1
 * $Id: sd_api_test.c,v 1.2 2006/03/15 01:11:03 gbarnard Exp $
d14 1
a14 1
static char ident[] = "$Id: sd_api_test.c,v 1.2 2006/03/15 01:11:03 gbarnard Exp $";
d367 1
a367 1
    int i;
d381 15
a395 2
    	printf("     %x %x %x %x\n", data[0], data[1], data[2], data[3]);
    	printf("     %x %x %x %x\n", data[128], data[129], data[130], data[131]);
d441 1
a441 1
	/* ======= Device 0 Setup ======= */
d510 1
a510 1
	set_driver_debug(Handles[config.SDDevSlot][0],0x0001|DEBUG_SER_SD_CMD); //0x2401
d532 1
a532 1
	    #if 0
