d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.16 2006/02/25 21:22:06 craig Exp $"
d44 1
d796 2
a797 3
        /* FIXME - dynamically allocate this? */
        uint8_t         scratchBuf[4 * 1024];
        uint32_t        readLength;
d800 8
a807 3
        if (readLength > sizeof(scratchBuf)) {

            printf("Error: scratch buffer is too small for request of %u bytes",
d809 5
a813 2
            diFatalError("Scratch buffer is too small");
            /* Code should never reach here */
d816 6
a821 4
            returnVal = doRawDiskRead(scratchBuf, readLength, wordOffset);
            if (returnVal == DI_ERR_NO_ERROR) {
                memcpy(destAddr, scratchBuf, length);
            }
d823 1
