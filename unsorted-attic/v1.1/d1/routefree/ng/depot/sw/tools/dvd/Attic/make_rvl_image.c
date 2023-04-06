d1 1
a1 1
#ident "$Id: rvl_image.c,v 1.14 2006/04/01 00:46:51 craig Exp $"
d114 1
a114 1
                       const uint8_t* const titleKey,
d159 1
a159 1
        " -t, --titleKey <file> - title key file (unencrypted)\n"
d173 1
a173 1
               uint8_t* const titleKey)
d175 2
a176 5
    char        *titleKeyName = NULL;
    uint8_t     defaultTitleKey[] = {0xde, 0xad, 0xbe, 0xef,
                                     0xde, 0xad, 0xbe, 0xef,
                                     0xde, 0xad, 0xbe, 0xef,
                                     0xde, 0xad, 0xbe, 0xef};
d211 1
a211 1
            titleKeyName = optarg;
a233 20
    if (titleKeyName != NULL) {
        FILE            *keyFile;
        size_t          bytes_read;
        if ( (keyFile = fopen(titleKeyName, "r")) == NULL) {
            fprintf (stderr, "Can't open key file '%s' - exit\n",
                     titleKeyName);
            exit(1);
        }

        bytes_read = fread(titleKey, 1, AES_KEY_LENGTH, keyFile);
        if (bytes_read != AES_KEY_LENGTH) {
            printf("(%s) Need %d key bytes from %s, only got %d - exit\n",
                    argv[0], AES_KEY_LENGTH, titleKeyName, bytes_read);
            exit(1);
        }
        fclose(keyFile);
    }
    else {
        memcpy(titleKey, defaultTitleKey, AES_KEY_LENGTH);
    }
d240 1
a240 1
    uint8_t     titleKey[AES_KEY_LENGTH];
d249 1
a249 1
    processOptions(argc, argv, &inputDisk, titleKey);
d259 1
a259 1
    if (generateDiskImage(&inputDisk, titleKey, outputFileName) == false) {
d612 1
a612 1
    uint32_t    contentCID = 0, tmdCID = 1;
d614 2
a615 2
    sprintf (commandBuf, "tmd -O -T %d -c %d -C %d",
                          titleId, contentCID, tmdCID);
d630 3
d644 1
a644 1
    sprintf(tmdName, "%08x.tmd", tmdCID);
d658 1
a658 1
    sprintf(titleKeyName, "%08x.titleKey", tmdCID);
d690 3
d705 1
a705 1
    sprintf(ticketName, "%08x.tik", ticketID);
d731 1
d762 2
a763 2
                        inputDisk->inputUpdateAreas[i]->titleId, false,
                        NULL, tmdName,
d844 1
a844 1
            fprintf(stderr, "Game partition certificates write failed\n");
d849 1
a849 1
        if (fseeko(outFile, imageStart, SEEK_SET) == -1) {
d867 6
a872 1
 * Write out the update meta-data and update data (collectively, the
d875 1
a875 1
 * - update structure (includes eTicket, since it is fixed length)
d878 2
a879 1
 * - the image
d881 3
a883 1
 *           an array of pointers to update tables of content
d888 1
d891 4
a894 4
    gamePartition_t   *updatePart, updateCopy;
    gameTOC_t         *returnVal;
    off_t             fileOffset, partitionStart, tmdStart;
    off_t             certBlobStart, imageStart;
d901 127
a1027 2
    returnVal->numGamePartitions = 0;
    returnVal->gamePartitions = NULL;
d1044 1
a1044 1
                  const uint8_t* const titleKey,
d1114 2
a1115 1
    updateToc = writeUpdates(inputDisk, outFile, 0);
d1127 1
a1127 1
    gameToc = writeGames(inputDisk, outFile, 0);
