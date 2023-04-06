d1 1
a1 1
#ident "$Id: test_rvl_image.c,v 1.9 2006/03/25 02:01:27 craig Exp $"
d193 3
a195 3
    uint32_t            tmdAddress, tmdSize, certArrayAddr, numCerts;
    uint32_t            certAddr, imageAddr;
    uint8_t             tmdBuf[4096];
d230 2
a231 2
    numCerts      = ntohl(updatePartition.numCertificates);
    certArrayAddr = ntohl((uint32_t) updatePartition.certificates);
d234 5
a238 13
    printf ("\tNum certificates: %" PRIu32
            "; Array start addr: 0x%" PRIx32"\n",
             numCerts, certArrayAddr << 2);

    // printf ("Certificate size: %d\n", sizeof(IOSCSigRsa2048));

    for (int i = 0; i < numCerts; i++) {
        IOSCSigRsa2048        cert;

        certAddr = certArrayAddr + (i * sizeof(IOSCSigRsa2048));
        printf ("\t\tCertificate #%d Address = 0x%" PRIx32 "\n",
                 i, certAddr << 2);
        printf ("\t\tMD5 Sum: ");
d240 6
a245 8
        doRawDiskRead((uint8_t *) &cert, sizeof(IOSCSigRsa2048), certAddr);
        md5_init(&state);
        md5_append(&state, (md5_byte_t *) &cert, sizeof(IOSCSigRsa2048));
        md5_finish(&state, digest);
        for (int di = 0; di < 16; ++di) {
            printf("%02x", digest[di]);
        }
        printf ("\n");
d247 2
d266 3
a268 3
    uint32_t            tmdAddress, tmdSize, certArrayAddr, numCerts;
    uint32_t            certAddr, cryptAddr;
    uint8_t             tmdBuf[4096];
d305 2
a306 2
    numCerts      = ntohl(gamePartition.numCertificates);
    certArrayAddr = ntohl((uint32_t) gamePartition.certificates);
d309 3
a311 2
    printf ("\tNum certificates: %" PRIu32 "; Array start addr: 0x%"
             PRIx32 "\n", numCerts, certArrayAddr << 2);
d313 1
a313 1
    // printf ("Certificate size: %d\n", sizeof(IOSCSigRsa2048));
d315 8
a322 7
    for (int i = 0; i < numCerts; i++) {
        IOSCSigRsa2048        cert;

        certAddr = certArrayAddr + (i * sizeof(IOSCSigRsa2048));
        printf ("\t\tCertificate #%d Address = 0x%" PRIx32 "\n",
                i, certAddr << 2);
        printf ("\t\tMD5 Sum: ");
a323 9
        doRawDiskRead((uint8_t *) &cert, sizeof(IOSCSigRsa2048), certAddr);
        md5_init(&state);
        md5_append(&state, (md5_byte_t *) &cert, sizeof(IOSCSigRsa2048));
        md5_finish(&state, digest);
        for (int di = 0; di < 16; ++di) {
            printf("%02x", digest[di]);
        }
        printf ("\n");
    }
d400 1
a400 1
                printf ("Read failed because of eofn");
d447 17
