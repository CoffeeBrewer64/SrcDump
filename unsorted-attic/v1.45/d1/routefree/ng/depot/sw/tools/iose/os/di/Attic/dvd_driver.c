d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.44 2006/03/03 21:03:57 craig Exp $"
d121 1
a121 1
    DPRINT("#### Starting DI driver version 0.2\n");
a124 5
#ifdef SIMPLE_IMAGE
    diskInfo.dataWordOffset = (96 * 1024) / 4;
#endif


a128 6


#ifdef RVL
    // return;
#endif

