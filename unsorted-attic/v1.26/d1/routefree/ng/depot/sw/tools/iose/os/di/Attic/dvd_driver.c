d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.25 2006/02/16 21:51:05 craig Exp $"
d38 1
a38 1
#include "dvd_hw_reg.h"
d176 1
a176 1
                if ((DICoverReg & DI_COVER_STATUS) == 0) {
d364 1
d385 1
a385 1
        * (uint32_t *) ioctlMesg->outPtr = DICoverReg;
d391 1
a391 1
        } else if ((DICoverReg & DI_COVER_STATUS) == 0) {
d403 3
a405 2
        printf ("(DiIoctl) Reading Immediate Reg; val = 0x%x\n", DIImmData);
        * (uint32_t *) ioctlMesg->outPtr = DIImmData;
d413 1
d415 2
d420 1
d422 2
d427 1
d429 2
