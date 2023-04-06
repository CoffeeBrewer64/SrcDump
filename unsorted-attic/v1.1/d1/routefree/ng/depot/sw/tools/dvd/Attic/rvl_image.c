d1 1
a1 1
#ident "$Id: dvd_image.c,v 1.8 2006/01/20 02:34:42 craig Exp $"
d44 1
d50 1
d59 1
a59 1
typedef struct inputGameArea {
d65 1
a65 9
} inputGameArea_t;

typedef struct inputUpdateArea {
    char *eTicketName;
    char *tmdName;
    int  numCertificates;
    char **certNames;
    char *content;
} inputUpdateArea_t;
d71 1
a71 1
    inputGameArea_t     **inputGameAreas;
d73 1
a73 1
    inputUpdateArea_t   **inputUpdateAreas;
a75 2


d88 1
a88 1
bool gameAreaInputOK(const inputGameArea_t const *inputGame);
d90 1
a90 1
inputGameArea_t *checkAndCopyInputGameArea(const inputGameArea_t* const gameArea);
d94 9
a126 7
    char        outFileName[256];
    FILE        *outFile, *inFile;
    struct stat statBuf;
    int         numDvdSuperblocks;
    char        *h3Buf, *h3BufPtr;
    int         h3Bytes;
    size_t      numWritten;
d134 1
a143 50
    if ((inFile = fopen64(argv[1], "r")) == NULL) {
        fprintf (stderr, "Error: can't open %s for reading - exit\n", argv[1]);
        exit(1);
    }
    if ((outFile = fopen(outFileName, "w")) == NULL) {
        fprintf (stderr, "Error: can't open %s for writing - exit\n", argv[1]);
        exit(1);
    }

    if (stat(argv[1], &statBuf) != 0) {
        printf ("Error: can't access %s - exit\n", argv[1]);
        exit(1);
    }

    numDvdSuperblocks = statBuf.st_size / DVD_DATA_BYTES_PER_SUPERBLOCK;

    if (statBuf.st_size % DVD_DATA_BYTES_PER_BLOCK != 0) {
        numDvdSuperblocks++;
    }

    h3Buf = (char *) malloc (SHA1_DIGESTSIZE * numDvdSuperblocks);
    assert(h3Buf != NULL);
    h3BufPtr = h3Buf;

    /* Make room for the H3 hashes */
    fseek(outFile, BLOCKS_FOR_H3 * DVD_BLOCK_SIZE, SEEK_SET);

    while (computeSuperBlock(inFile, outFile, h3BufPtr,
                             TitleKey, true) == true) {
        h3BufPtr += SHA1_DIGESTSIZE;
    }
    h3Bytes = (h3BufPtr - h3Buf) + SHA1_DIGESTSIZE;

    if (h3Bytes > BLOCKS_FOR_H3 * DVD_BLOCK_SIZE) {
        fprintf (stderr, "Error: H3 hashes won't fit in space - exit\n");
        exit(1);
    }
    /*
     * Write the H3 hashes to the beginning of the file
     */
    rewind(outFile);
    numWritten = fwrite(h3Buf, 1, h3Bytes, outFile);
    if (numWritten != h3Bytes) {
        fprintf (stderr, "Can't write H3 hash bytes - exit\n");
        exit(1);
    }
    fclose(inFile);
    fclose(outFile);
    free(h3Buf);
    exit(0);
d195 53
d316 498
d816 1
d818 1
d829 6
d836 1
a836 1
    if ((outFile = fopen(outputName, "w")) == NULL) {
d844 1
a844 3
        fclose(outFile);
        unlink(outputName);
        return(false);
d848 1
a848 3
        fclose(outFile);
        unlink(outputName);
        return(false);
d851 78
a928 3
        fclose(outFile);
        unlink(outputName);
        return(false);
d931 29
a959 5
    if (fseek(outFile, GLOBAL_TOC_OFFSET, SEEK_SET) == -1) {
        perror ("fseek");
        fclose(outFile);
        unlink(outputName);
        return(false);
d964 1
a964 2
        unlink(outputName);
        return(false);
d967 5
d976 6
d992 1
a992 1
    inputGameArea_t             inputGameArea;
d995 2
a996 2
    inputGameArea_t             *tempGamePtrs[512];
    inputUpdateArea_t           *tempUpdatePtrs[512];
d1003 1
a1003 1
    lineNum = 0;
d1023 1
d1026 1
a1026 1
                    checkAndCopyInputGameArea(&inputGameArea);
d1032 18
a1049 4
            currentSection = GAME_SECTION;
            inputGameArea.eTicketName = NULL;
            inputGameArea.tmdName = NULL;
            inputGameArea.numCertificates = 0;
d1065 5
a1069 9
            if (currentSection == GAME_SECTION) {
                if (inputGameArea.eTicketName != NULL) {
                    fprintf(stderr,
                            "Error: Duplicate eTicket names (line %d)\n",
                            lineNum);
                    fclose(script);
                    return(NULL);
                }
                inputGameArea.eTicketName = stringVal;
d1071 1
d1076 1
a1076 2
                fprintf(stderr,
                        "Error: TMD found without section (line %d)\n",
d1086 5
a1090 8
            if (currentSection == GAME_SECTION) {
                if (inputGameArea.tmdName != NULL) {
                    fprintf(stderr, "Error: Duplicate TMD names (line %d)\n",
                            lineNum);
                    fclose(script);
                    return(NULL);
                }
                inputGameArea.tmdName = stringVal;
d1092 1
d1108 5
a1112 8
            if (currentSection == GAME_SECTION) {
                if (inputGameArea.content != NULL) {
                    fprintf(stderr, "Error: Duplicate TMD names (line %d)\n",
                            lineNum);
                    fclose(script);
                    return(NULL);
                }
                inputGameArea.content = stringVal;
d1114 1
d1125 12
a1136 14
            if (currentSection == GAME_SECTION) {
                if (inputGameArea.numCertificates != 0) {
                    fprintf(stderr, "Error: Duplicate certificate lines (line %d)\n",
                            lineNum);
                    fclose(script);
                    return(NULL);
                }
                getMultipleStringVals(lineBuf, &lineIdx, lineNum,
                                      &inputGameArea.numCertificates,
                                      &(inputGameArea.certNames));
                if (inputGameArea.numCertificates == 0) {
                    fclose(script);
                    return(NULL);
                }
d1140 7
d1160 1
a1160 2
        tempGamePtrs[numGameAreas] =
            checkAndCopyInputGameArea(&inputGameArea);
d1166 8
d1179 2
d1182 2
a1183 1
    returnVal->inputGameAreas = (inputGameArea_t **) malloc(numGameAreas * sizeof (inputGameArea_t *));
a1188 1

d1192 13
d1248 3
d1409 1
a1409 1
gameAreaInputOK(const inputGameArea_t const *inputGame)
d1411 1
a1411 1
    if (inputGame->eTicketName == NULL) {
d1414 1
a1414 1
    else if (inputGame->tmdName == NULL) {
d1417 1
a1417 1
    else if (inputGame->numCertificates == 0) {
d1420 1
a1420 1
    else if (inputGame->content == NULL) {
d1430 2
a1431 2
inputGameArea_t *
checkAndCopyInputGameArea(const inputGameArea_t* const inputGameArea)
d1433 3
a1435 2
    inputGameArea_t     *returnVal;
    if (gameAreaInputOK(inputGameArea) == false) {
d1438 1
a1438 1
    returnVal = (inputGameArea_t *) malloc (sizeof(inputGameArea_t));
d1443 1
a1443 1
    memcpy(returnVal, inputGameArea, sizeof(inputGameArea_t));
