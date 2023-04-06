d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.17 2006/02/26 02:14:53 craig Exp $"
d85 1
a85 1
    uint8_t     data[DATA_BYTES_PER_BLOCK];
d623 1
a623 1
    DVDDiskInfo         diskInfo;
d655 2
a656 2
    globalTOC_t         globalTOC;
    gameTOC_t           gameTOC;
d724 1
a724 1
    gamePartition_t     gamePartition;
d766 3
a768 1
    returnVal = doRawDiskRead(certs, sizeof(ESRsa2048RsaCert) * diskState.numCertificates, diskState.certificates);
d782 6
a787 1
 * possible that the length is not a multiple of 32.
