d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.29 2006/03/30 04:06:40 craig Exp $"
d789 1
a789 1
#ifdef RVL_1
d791 1
a791 2
    IOSCSigRsa2048      *certs;
    void                *certMemory, *tmdMemory;
d807 1
a807 1
#ifdef RVL_1
d835 3
a837 6
    /* Read certificates */
    if ((sizeof(IOSCSigRsa2048) & 0x1F) != 0) {
        diFatalError("IOSCSigRsa2048 size is not a multiple of 32\n");
    }
    if (dvdMemAllocAlign32(sizeof(IOSCSigRsa2048) * gamePartition.numCertificates,
                           (void **) &certs, &certMemory) == false) {
d840 3
a842 3
    returnVal = doNonconformingDiskRead((uint8_t *) certs,
                                        sizeof(IOSCSigRsa2048) * gamePartition.numCertificates,
                                        (uint32_t) gamePartition.certificates);
d846 2
a847 1
    printf ("VerifyGameMetaData: num certs = %d\n", gamePartition.numCertificates);
d849 2
a850 2
    printf ("Certificates MD5 Sum: ");
    printMD5sum(certs, sizeof(IOSCSigRsa2048) * gamePartition.numCertificates);
d857 2
a858 3
    verifyError = ES_DiVerify(certs,
                              sizeof(IOSCSigRsa2048) * gamePartition.numCertificates,
                              NULL, 0,
d860 1
a860 1
                              tmd, gamePartition.tmdSize,
d865 2
