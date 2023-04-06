d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.19 2006/03/03 04:33:51 craig Exp $"
d102 3
d117 1
a117 1
    diskState.offsetsSizesValid  = false;
d119 1
a119 1
    globalBlockCache.isValid    = false;
d503 1
a503 2
    diskPosition_t              startPosition;
    uint32_t                    returnVal;
d506 12
a517 1
    if (diskState.h3HashesRead == false) {
a519 11
#ifdef SIMPLE_IMAGE
        printf ("Reading H3 hashes\n");
        returnVal = readH3Hashes(h3HashArray, H3_HASH_WORD_OFFSET);
        if (returnVal != DI_ERR_NO_ERROR) {
            printf ("(doRvlRead) readH3Hashes returns error (0x%x)\n",
                      returnVal);
            return(returnVal);
        }
        diskState.h3HashesRead = true;
        printf ("(doRvlRead) Done reading H3 hashes\n");
#else
a538 1
#endif
d540 13
d554 1
a554 1
    diskVirtualToPhysical(virtWordOffset, &startPosition);
d556 6
a561 5
    /*
     * FIXME - This check is only necessary when this function is not run
     * on the disk emulator, because the state is set when the disk ID
     * is read
     */
d563 1
a563 3
    if (diskState.hashEncryptedValid == false) {
        doReadHashEncryptedState();
    }
d568 1
d575 2
a576 1
                                       diskState.encrypted, diskState.hashed);
d593 1
a593 1
                                diskState.encrypted, diskState.hashed);
d614 2
a615 1
                                       diskState.encrypted, diskState.hashed);
d646 2
d649 17
a665 4
        diskState.encrypted = diskInfo.noEncryption == 0 ? true : false;
        diskState.hashed    = diskInfo.noHash       == 0 ? true : false;
        DPRINT3 ("(readHashEncrypted) noEncrypt = %d, noHashed = %d\n",
                  diskInfo.noEncryption, diskInfo.noHash);
d687 2
a688 2
    globalTOC_t         globalTOC __attribute__((aligned(32)));
    gameTOC_t           gameTOC __attribute__((aligned(32)));
d732 1
a732 2
 *                                  structure on disk.  This should
 *                                  be 0 in most cases.
a765 1
    diskState.offsetsSizesValid = true;
d771 5
d786 1
a786 1
        diskState.h3HashesRead = true;
d789 1
a789 1
        diskState.h3HashesRead = false;
