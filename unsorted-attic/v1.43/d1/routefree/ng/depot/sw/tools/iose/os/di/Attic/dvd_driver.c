d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.42 2006/03/03 04:33:51 craig Exp $"
d270 1
a270 5
    IOS_InvalidateRdb(rb_iod);
    enableTransferCompleteIntr();
    enableErrorIntr();
    disableCoverInterrupt();
    IOS_FlushMem(wb_iod);
a282 15
#ifdef notdef
    /* The h3HashArray is statically declared now */
    /* Init space for H3 hashes */
    h3HashPages = h3HashSize / IOS_DDR_PAGE_SIZE;
    if (h3HashSize % IOS_DDR_PAGE_SIZE != 0) {
        h3HashPages++;
    }
    h3HashArray = IOS_Alloc(h3HashPages);
    if (h3HashArray == NULL) {
        diFatalError("Error: can't allocate space for H3 hashes - exit\n");
        driverRunning = false;
        IOS_DestroyThread(0, NULL);
    }
#endif

