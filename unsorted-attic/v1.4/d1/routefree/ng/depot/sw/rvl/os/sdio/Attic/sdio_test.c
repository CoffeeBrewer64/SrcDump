d12 1
a12 1
#ident "$Id: sdio_test.c,v 1.3 2006/03/15 20:42:50 gbarnard Exp $"
d87 3
a89 3
	printf("\n=== RVL PLL Init 2===\n");
	init_USB_PLL();
	enableChipBlocks();
d119 1
a119 5
    //testthr(0);
    	
    printf("\n=== SDIO_0 Init Driver ===\n");
	sdio_init_module(0x0D070000);
	
d124 1
a124 1
    }	
d126 5
d186 1
a186 1
        // IOS_YieldThread();
