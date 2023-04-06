d1 1
a1 1
#ident "$Id: test_rvl_image.c,v 1.4 2006/02/14 19:32:36 craig Exp $"
d35 1
d39 2
a40 2
void doDiskRead(uint8_t* const destAddr, const uint32_t length,
                const uint32_t wordOffset);
d45 4
d76 1
d82 2
d93 1
a93 1
    doDiskRead((uint8_t *) &globalTOC,
d103 1
a103 1
    doDiskRead((uint8_t *) &updateTOC,
d115 1
a115 1
    doDiskRead((uint8_t *) updatePartArray,
d124 1
a124 1
    doDiskRead((uint8_t *) &gameTOC, sizeof(gameTOC_t), gameTOCOff);
d135 1
a135 1
    doDiskRead((uint8_t *) gamePartArray,
d151 1
a151 1
    doDiskRead((uint8_t *) &diskId, sizeof(DVDDiskId), 0);
d164 1
a164 1
    doDiskRead((uint8_t *) &diskInfo,
d190 1
a190 1
    doDiskRead((uint8_t *) &updatePartition,
d206 1
a206 1
    doDiskRead(tmdBuf, tmdSize, tmdAddress);
d236 1
a236 1
        doDiskRead((uint8_t *) &cert, sizeof(ESRsa2048RsaCert), certAddr);
d245 1
a245 1
    doDiskRead(imageBytes, sizeof(imageBytes), imageAddr);
d265 1
d271 1
a271 1
    doDiskRead((uint8_t *) &gamePartition,
d287 1
a287 1
    doDiskRead(tmdBuf, tmdSize, tmdAddress);
d316 1
a316 1
        doDiskRead((uint8_t *) &cert, sizeof(ESRsa2048RsaCert), certAddr);
d329 1
a329 1
    doDiskRead(cryptBytes, sizeof(cryptBytes), cryptAddr + (1024 >> 2));
d331 1
a331 1
    printf ("\tImage bytes: ");
d336 11
d358 1
d361 2
a362 2
void
doDiskRead(uint8_t* const destAddr, const uint32_t length,
d375 1
a375 1
            printf ("Read from addr 0x%" PRIx32 " failed\n", wordOffset << 2);
d396 10
