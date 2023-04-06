d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.40 2006/03/03 01:45:39 craig Exp $"
d71 1
a71 1
uint8_t                 h3HashArray[MAX_H3_HASH_SIZE];
d121 1
a121 1
    DPRINT("#### Starting DI driver version 0.1\n");
a134 7
    IOS_InvalidateRdb(rb_iod);

    enableTransferCompleteIntr();
    enableErrorIntr();
    disableCoverInterrupt();

    IOS_FlushMem(wb_iod);
d265 11
d351 1
a351 1
    resetDriverState();
d354 1
a354 1
    DPRINT("Doing ClearAndEnableDIIntr\n");
d356 1
a356 1
    DPRINT("ClearAndEnableDIIntr done \n");
d642 1
d644 1
a644 1
 * Triggers a fatal error if the register configuration is incorrect
d646 1
d661 1
a661 1
	/*
d666 1
a666 1
        */
d670 1
a683 2


