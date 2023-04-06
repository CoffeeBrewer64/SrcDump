d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.43 2006/03/03 07:27:22 craig Exp $"
d422 1
d466 1
a466 1
        DPRINT("(DIIoctl) Doing DI_MASK_COVER_INTERRUPT\n");
d472 1
a472 1
        DPRINT2 ("++++ (DiIoctl) Cover Reg; val = 0x%x\n", readDICoverReg);
