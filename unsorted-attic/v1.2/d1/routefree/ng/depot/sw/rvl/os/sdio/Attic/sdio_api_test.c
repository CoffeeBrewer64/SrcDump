d11 1
a11 1
 * $Id: sdio_api_test.c,v 1.1 2006/03/02 19:02:05 gbarnard Exp $
d14 1
a14 1
char ident[] = "$Id: sdio_api_test.c,v 1.1 2006/03/02 19:02:05 gbarnard Exp $";
a31 6
	
	#ifdef VERSA
		#include "ios_pci.h"
		#include <versaios.h>
	#endif

d35 1
d86 1
a86 1
    #if 0
d95 1
a95 1
   	 	{ SDIO_RD, SDIO_CMD53, 0, 1, 0x80c4, 4, 0x0, 0x40003, 1, SDIO_DMA },
d318 1
a318 1
    unsigned char cis_buffer[CIS_BUFF_LEN];
d322 1
a322 1
    /*cis_buffer = (unsigned char *) malloc (CIS_BUFF_LEN);
d327 1
a327 1
    */
d571 1
a571 1
    config.SDDevSlot = 1;
d585 1
a585 1
    	///printf(">>>>>>> Handle %X\n",Handles[config.SDDevSlot][config.SDDevFunc]);
d588 3
d592 1
a592 2
    printf ("ISD_ResetDevice()\n");

d600 1
a600 1

d604 1
d626 1
d628 1
a628 1

d633 7
a639 1
	    printf ("Run CIS tests on slot 0 function 1\n");
d646 2
a647 1
	    }    
a649 1
	#endif
d651 2
a652 1
	#if 1
d656 2
a657 1
	    printf ("---> Run cmd 53 tests on slot 0 function 1\n");
d659 1
a659 1
	#endif
d685 1
d688 1
a688 1

d695 1
d714 3
d718 1
a718 3
    sdio_test1 ();

    return IOS_ThreadExit(0);
