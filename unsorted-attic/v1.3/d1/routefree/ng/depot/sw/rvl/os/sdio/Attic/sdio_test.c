d12 1
a12 1
#ident "$Id: sdio_test.c,v 1.2 2006/03/15 01:10:15 gbarnard Exp $"
d121 2
a122 2
    printf("\n=== SDIO Init Driver ===\n");
	sdio_init_module();
d126 2
a127 2
    	u32 arg = 0;
    	sdio_rm(arg);
