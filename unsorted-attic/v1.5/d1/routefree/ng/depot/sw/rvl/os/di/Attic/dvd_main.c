d1 1
a1 1
#ident "$Id: dvd_main.c,v 1.4 2006/02/27 02:22:07 craig Exp $"
d22 1
a22 2
// #include "rvl_iop.h"
#include "ahb_fdl_defs.h"
d28 1
a28 1
#define STACK_SIZE 1024
d31 1
a31 1
const uint32_t _initPriority = 10;
d35 2
d39 5
a49 1
    uint32_t            testVal;
d52 5
a56 1
    /* Disable PI control of DIRSTB */
d76 1
a76 11
    printf ("Status reg is: 0x%x\n", readDIStatus());
    testVal = busRd32(DI_STATUS_ADDR);
    printf ("Old val of 0x%x: 0x%x\n", DI_STATUS_ADDR, testVal);
    busWrt32(DI_STATUS_ADDR, testVal);

    IOS_FlushMem(wb_iod);
    IOS_InvalidateRdb(rb_iod);

    testVal = busRd32(DI_STATUS_ADDR);
    printf ("New val: 0x%x\n", testVal);

d78 1
d83 2
a84 3
    retVal = handleDiCommand(&diCommand, &diskId);

    printf ("Return val is: 0x%x\n", retVal);
d86 21
