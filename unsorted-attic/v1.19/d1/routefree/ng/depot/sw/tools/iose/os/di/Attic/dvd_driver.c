d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.18 2006/01/30 22:14:43 craig Exp $"
d351 2
d365 1
a365 1
        * (uint32_t *) ioctlMesg->outPtr = DVD_INTTYPE_CVR;
d376 1
a376 1
        } else if ((DICoverReg & DI_COVER_STATUS) == DVD_COVER_CLOSED) {
d397 1
a397 2
        // TODO
        DICoverReg &= DI_COVER_INTR_MASK;
d404 5
