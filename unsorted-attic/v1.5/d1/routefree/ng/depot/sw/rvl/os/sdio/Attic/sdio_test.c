d12 1
a12 1
#ident "$Id: sdio_test.c,v 1.4 2006/03/16 19:28:45 gbarnard Exp $"
d52 1
a52 1
testthr(u32 arg)
d86 2
d121 10
a130 5
    testthr(10000);
	printf("\n=== SDIO Init RM     ===\n");
    {
    	u32 hcnum = 0;
    	sdio_rm(hcnum);
a132 5
    testthr(10000);    	
    printf("\n=== SDIO_0 Init Driver ===\n");
	sdio_init_module(0x0D070000);
	
    testthr(10000);
d179 10
a188 3
	printf("\n=== Run Test Application ===\n");
	//sdio_api_test();
	sd_api_test();
