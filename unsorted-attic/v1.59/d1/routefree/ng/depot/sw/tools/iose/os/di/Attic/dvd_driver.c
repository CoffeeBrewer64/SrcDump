d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.58 2006/03/14 04:35:24 craig Exp $"
d147 1
a147 1
        printf ("(dvd_driver) IOS_ReceiveMessage returned - got message\n");
a359 2
    printf ("(initDvdDriverStage2) IOP DI Kernel interrupt enabled: %d\n",
	     IOPDiIntrEnabled());
d542 2
