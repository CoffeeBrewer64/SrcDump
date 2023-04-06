d1 1
a1 1
#ident "$Id: key.c,v 1.3 2006/03/31 20:00:04 craig Exp $"
d69 1
a72 10
enum section {GAME_SECTION, UPDATE_SECTION, NO_SECTION};
typedef enum section section_t;

typedef struct inputArea {
    char        *certName;
    char        *content;
    uint32_t    titleId;
} inputArea_t;


a87 6
bool gameInputOK(const inputArea_t const *inputGame);


inputArea_t *checkAndCopyInputArea(const inputArea_t* const area);


a90 1

d93 1
a93 1
bool generateTmd(const char* const contentName, const uint32_t titleId,
a98 3
bool generateEticket(const char* const encryptedTitleKeyFile, 
                     char *ticketName);

d101 1
a101 1
                       const uint32_t titleId,
d141 1
a141 1
               char **outputName, uint32_t *titleId, char **IOSversion,
d183 1
a183 1
            *titleId = strtoul(optarg, NULL, 0);
d191 1
a191 1
            printf ("%s version 0.2 %s\n", ProgName, __DATE__);
d218 1
a218 1
    uint32_t    titleId;
d292 1
a292 132
copyFileToOutFile(FILE *outFile, const char* const inFileName)
{
    FILE        *inFile;
    /* Buffer size is arbitrary - make it bigger or smaller if you like */
    uint8_t     buffer[4 * 1024];
    size_t      numRead, numWritten, bufSize;
    bool        done = false;

    if ((inFile = fopen(inFileName, "r")) == NULL) {
        fprintf (stderr, "(%s) Error: Can't open update content file '%s'\n",
                 ProgName, inFileName);
        return(false);
    }
    bufSize = sizeof(buffer);
    do {
        numRead = fread(buffer, 1, bufSize, inFile);
        if (numRead != bufSize) {
            done = true;
            if (ferror(inFile)) {
                fprintf(stderr, "Read error on content file %s\n", inFileName);
                fclose(inFile);
                return(false);
            }
        }
        numWritten = fwrite(buffer, 1, numRead, outFile);
        if (numWritten != numRead) {
            fprintf(stderr, "Write error when copying content file %s\n",
                    inFileName);
            fclose(inFile);
            return(false);
        }
    } while (! done);

    fclose(inFile);
    return(true);
}

/* ------------------------------------------------------------------------ */

bool
fileSize(const char* const fileName, off_t *fileSize)
{
    struct stat statBuf;

    if (stat(fileName, &statBuf) == -1) {
        return(false);
    }
    else {
        *fileSize = statBuf.st_size;
        return(true);
    }
}

/* ------------------------------------------------------------------------ */

bool
fileExists(const char* const fileName)
{
    struct stat statBuf;

    if (stat(fileName, &statBuf) == -1) {
        return(false);
    }
    else {
        return(true);
    }
}

/* ------------------------------------------------------------------------ */

/*
 * Read the contents of the file 'fileName' into an array allocated
 * in this routine.  Output the array and its size.
 * RETURNS:     true            if everything went OK
 *              false           otherwise
 */

bool
readFileIntoArray(const char* const fileName, uint8_t **array, uint32_t *size)
{
    FILE        *inFile;
    struct stat statBuf;

    *size = 0;
    *array = NULL;

    if (stat(fileName, &statBuf) == -1) {
        return(false);
    }
    *size = (uint32_t) statBuf.st_size;
    *array = (uint8_t *) malloc(*size);
    if ( (inFile = fopen(fileName, "r")) == NULL) {
        fprintf (stderr, "%s: Can't open file %s\n", ProgName, fileName);
        free(*array);
        return(false);
    }
    if (fread(*array, *size, 1, inFile) != 1) {
        fprintf (stderr, "%s: Can't read file %s\n", ProgName, fileName);
        free(*array);
        fclose(inFile);
        return(false);
    }
    fclose(inFile);
    return(true);
}

/* ------------------------------------------------------------------------ */
bool
readCertBlob(uint8_t **certArray, uint32_t *certBlobSize)
{
    char        *root;
    char        certFileName[256];

    if ( (root = getenv("ROOT")) == NULL) {
        fprintf (stderr, "%s: Need to set environment variable ROOT\n",
                 ProgName);
        return(false);
    }
    sprintf(certFileName, "%s/usr/etc/pki_data/cert_dpki.sys", root);
    if (readFileIntoArray(certFileName, certArray, certBlobSize) == false) {
        fprintf(stderr, "%s: Reading certificates from %s failed\n",
                ProgName, certFileName);
        return(false);
    }
    else {
        return(true);
    }
}
/* ------------------------------------------------------------------------ */

bool
generateTmd(const char* const contentName, const uint32_t titleId,
d301 1
a301 1
    sprintf (commandBuf, "tmd -O -T 0x%" PRIx32 " -c 0x%" PRIx32,
d334 1
a334 1
    sprintf(tmdName, "%" PRIx32 ".tmd", titleId);
d348 1
a348 1
    sprintf(titleKeyName, "%" PRIx32 ".titleKey", titleId);
a365 39
bool
generateEticket(const char* const encryptedTitleKeyFile, 
                char *ticketName)
{
    char        commandBuf[1024];
    int         status;
    uint32_t    ticketID = 2, titleID = 1;

    sprintf (commandBuf, "ticket -O -t %" PRIu32 " -T %" PRIu32 " -K %s",
             ticketID, titleID, encryptedTitleKeyFile);
    strcat (commandBuf, " -P d");               // devel PKI
    strcat (commandBuf, " > ticket.out 2>&1 ");
    if (Verbose) {
        printf ("Ticket command is: '%s'\n", commandBuf);
    }
    status = system(commandBuf);
    if (status == -1) {
        fprintf (stderr, "%s: fork failed for command '%s'\n",
                 ProgName, commandBuf);
        return(false);
    }
    if (WEXITSTATUS(status) != 0) {
        fprintf (stderr, "%s: e-ticket create command '%s' failed.\n",
                 ProgName, commandBuf);
        return(false);
    }

    sprintf(ticketName, "%" PRIx32 ".tik", ticketID);
    if (! fileExists(ticketName)) {
        fprintf (stderr, "%s: expected 'ticket' to create file %s\n",
                 ProgName, ticketName);
        return(false);
    }

    return(true);
} // generateEticket

/* ------------------------------------------------------------------------ */

d369 1
a369 1
 * update partition) for each update.
d384 1
a384 1
                  const uint32_t titleId,
d412 1
a412 1
    if (generateEticket(titleKeyName, ticketName) == false) {
d433 1
a433 1
    if (readCertBlob(&certBlob, &(partition.certBlobSize)) == false) {
