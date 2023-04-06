d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.26 2006/03/23 00:52:09 craig Exp $"
d38 1
d43 1
a45 1
#include "dvd_low_rvl.h"
d552 1
d554 1
a771 1
#ifdef not_done
d773 5
a777 2
    ESRsa2048RsaCert    *certs;
#endif
d789 53
d862 1
d871 1
d907 2
a908 2
        uint8_t         *scratchBuf, *scratchPtr;
        uint32_t        readLength, allocLength;
d911 5
a915 17
        /*
         * dvdMemAlloc doesn't always deliver space aligned to 32 bytes.
         * Ask for 32 bytes more than needed, then align it ourselves
         */
        allocLength = readLength + 32;
        scratchBuf = dvdMemAlloc(allocLength);
        if (scratchBuf == NULL) {
            printf("Error: scratch buffer allocation of %u bytes is too big",
                    length);
            diFatalError(
            "Can't allocate scratch buf in doNonconformingDiskRead");
        }
        if (((uint32_t) scratchBuf & 0x1F) == 0) {
            scratchPtr = scratchBuf;
        }
        else {
            scratchPtr = (uint8_t *) (((uint32_t) scratchBuf + 32) & ~0x1F);
d923 1
a923 1
        dvdMemFree(scratchBuf);
