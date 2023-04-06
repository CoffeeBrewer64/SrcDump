d1 1
a1 1
#ident "$Id: rvl_image.c,v 1.11 2006/03/25 02:01:27 craig Exp $"
d62 1
d76 1
a76 2
    int  numCertificates;
    char **certNames;
d120 1
d123 4
a126 2
bool getCertificates(const int numCerts, char** certNames,
                     IOSCSigRsa2048 **certArray);
d128 3
a130 2
                          ESTicket *ticket, uint32_t *tmdSize,
                          ESTitleMeta **tmd, IOSCSigRsa2048 **certArray);
d134 1
a524 1
    returnVal->numCertificates = inputGame->numCertificates;
d527 2
a528 1
                             &(returnVal->certificates)) == false) {
a546 1
    returnVal->numCertificates = inputUpdate->numCertificates;
d549 2
a550 1
                             &(returnVal->certificates)) == false) {
d568 4
a571 2
                     ESTicket *ticket, uint32_t *tmdSize, ESTitleMeta **tmd,
                     IOSCSigRsa2048 *certArray[])
d579 1
a579 2
    if (getCertificates(inputArea->numCertificates, inputArea->certNames,
                        certArray) == false) {
d587 5
a591 2
 * INPUT: the number of certificates and an array of certificate
 *         file names
d594 1
a594 2
getCertificates(const int numCerts, char** certNames,
                IOSCSigRsa2048 *certArray[])
d600 8
a607 3
    *certArray = (IOSCSigRsa2048 *)
                  malloc (sizeof (IOSCSigRsa2048) * numCerts);
    if (*certArray == NULL) {
d611 11
a621 27
    for (int i = 0; i < numCerts; i++) {
        if (stat(certNames[i], &statBuf) == -1) {
            perror ("cert file stat");
            free(*certArray);
            return(false);
        }
        if (sizeof(IOSCSigRsa2048) != statBuf.st_size) {
            fprintf (stderr,
                     "(%s) Cert file is the wrong size %llu (should be %u)\n",
                     ProgName, statBuf.st_size, sizeof(IOSCSigRsa2048));
            free(*certArray);
            return(false);
        }
        if ((inFile = fopen(certNames[i], "r")) == NULL) {
            fprintf (stderr, "(%s) Can't open cert file %s\n",
                     ProgName, certNames[i]);
            free(*certArray);
            return(false);
        }
        numRead = fread(&((*certArray)[i]), sizeof(IOSCSigRsa2048),
                           1, inFile);
        if (numRead != 1) {
            fprintf(stderr, "Read of cert failed\n");
            free(*certArray);
            return(false);
        }
        fclose(inFile);
d623 1
d625 1
a625 1
} // getCertificates
d674 3
d693 5
d728 1
a728 1
    off_t               certArrayStart, h3HashStart, cryptAreaStart;
d759 2
a760 3
        certArrayStart = alignOffset(tmdStart + gamePart->tmdSize, ITEM_ALIGN);
        h3HashStart = certArrayStart
                      + (gamePart->numCertificates * sizeof(IOSCSigRsa2048));
d772 2
a773 3
        gameCopy.numCertificates = htonl(gamePart->numCertificates);
        gameCopy.certificates    = (IOSCSigRsa2048 *)
                                    DISK_ADDR(certArrayStart);
d792 1
a792 1
        if (fseeko(outFile, certArrayStart, SEEK_SET) == -1) {
d796 5
a800 5
        if (fwrite(gamePart->certificates,
                   sizeof(IOSCSigRsa2048),
                   gamePart->numCertificates,
                   outFile) != gamePart->numCertificates) {
            fprintf(stderr, "Game partition certificates write failed\n");
d825 2
a826 1
        memcpy(gamePart->tmd->contents[0].hash, h4HashArray, SHA1_DIGESTSIZE);
d939 1
a939 1
    off_t               certArrayStart, imageStart;
d965 1
a965 1
        certArrayStart = alignOffset(tmdStart + updatePart->tmdSize,
d967 1
a967 2
        imageStart = certArrayStart
                    + (updatePart->numCertificates * sizeof(IOSCSigRsa2048));
d976 4
a979 5
        updateCopy.tmdSize = htonl(updatePart->tmdSize);
        updateCopy.tmd = (ESTitleMeta *) DISK_ADDR(tmdStart);
        updateCopy.numCertificates = htonl(updatePart->numCertificates);
        updateCopy.certificates = (IOSCSigRsa2048 *)
                                  DISK_ADDR(certArrayStart);
d1007 1
a1007 1
        if (fseeko(outFile, certArrayStart, SEEK_SET) == -1) {
d1011 4
a1014 4
        if (fwrite(updatePart->certificates,
                   sizeof(IOSCSigRsa2048),
                   updatePart->numCertificates,
                   outFile) != updatePart->numCertificates) {
d1249 5
d1323 3
a1325 3
            inputArea.tmdName = NULL;
            inputArea.content = NULL;
            inputArea.numCertificates = 0;
d1401 1
a1401 1
            if (inputArea.numCertificates != 0) {
d1408 2
a1409 4
            getMultipleStringVals(lineBuf, &lineIdx, lineNum,
                                  &inputArea.numCertificates,
                                  &(inputArea.certNames));
            if (inputArea.numCertificates == 0) {
d1686 1
a1686 1
    else if (inputArea->numCertificates == 0) {
d1750 19
