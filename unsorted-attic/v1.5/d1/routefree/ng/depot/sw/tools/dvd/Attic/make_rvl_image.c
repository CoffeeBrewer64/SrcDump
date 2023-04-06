#ident "$Id: make_rvl_image.c,v 1.4 2006/05/05 19:57:55 craig Exp $"
/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

/*
 * Program to generate RVL secure DVD images.
 * By default, only generates file bytes from the security
 * area onwards.
 *
 * See the Powerpoint
 * presentation on the Web for details.
 *
 * Format of 32K byte disc block:
 * 620 bytes of of H0 hashes
 * 20 bytes of padding 
 *
 * 160 bytes of H1 hashes
 * 36 bytes of padding
 *
 * 160 bytes of H2 hashes
 * 32 bytes of padding
 * Total: 1024 bytes
 *
 * 31K of data
 */

#ifdef __CYGWIN__
#undef __STRICT_ANSI__
#else
#define fseeko(file, where, whence)     fseeko64(file, where, whence)
#define ftello(file)                    ftello64(file)
#endif

#include <assert.h>
#include <ctype.h>
#include <getopt.h>
#include <inttypes.h>
#include <netinet/in.h>         // For htonl()
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "aes.h"
#include "sha1.h"
#include "image_superblock.h"
#include "types.h"
#include "disk_format.h"
#include "estypes.h"
#include "md5.h"

#define AES_KEY_LENGTH          16

enum formatToken {NO_TOKEN, INVALID_TOKEN, GAME, UPDATE, CONTENT, TITLE_ID};
typedef enum formatToken      formatToken_t;

enum section {GAME_SECTION, UPDATE_SECTION, NO_SECTION};
typedef enum section section_t;

typedef struct inputArea {
    char        *certName;
    char        *content;
    uint32_t    titleId;
} inputArea_t;

typedef struct inputDisk {
    DVDDiskId           *diskId;
    DVDDiskInfo         *diskInfo;
    int                 numGameAreas;
    inputArea_t         **inputGameAreas;
    int                 numUpdateAreas;
    inputArea_t         **inputUpdateAreas;
} inputDisk_t;

#if !defined(__CYGWIN__)
static struct option longOptions[] = {
    {"encypt",          0, 0, 'e'},     /* Encrypt disk image */
    {"help",            0, 0, 'h'},     /* Print usage */
    {"output",          1, 0, 'o'},     /* Output image name */
    {"script",          1, 0, 's'},     /* Input script file */             
    {"titleKey",        1, 0, 't'},     /* Title key file */             
    {"verbose",         0, 0, 'v'},     /* Print status output when running */
    {"hash",            0, 0, 'z'},     /* Hash disk image */
    {0, 0, 0, 0}
};
#endif

static char* options = "efho:s:t:vz";

formatToken_t getToken (char *inputLine, int *startPos);
char *getOneStringValue (char *inputLine, int *position, const int lineNum);
void getMultipleStringVals (char *inputLine, int *position, const int lineNum,
                            int *numStrings, char ***strArrayPtr);
bool gameInputOK(const inputArea_t const *inputGame);

bool parseScriptFile(const char* const scriptName,
                     inputDisk_t* const inputDisk);

inputArea_t *checkAndCopyInputArea(const inputArea_t* const area);
bool generateDiskImage(inputDisk_t* const inputDisk,
                       const char* const titleKeyName,
                       const char* const outputName);


bool getCertBlob(const char* const certName, uint32_t *certBlobSize,
                 void **certBlob);


void truncateImage(char *inFileName, off_t truncateOffset);
void zeroFile(FILE *theFile, off_t start, off_t length);
void printMD5sum(const void* const ptr, const uint32_t numBytes);
bool getOneU32value (const char* const inputLine,
                     int *position, const int lineNum,
                     uint32_t *value);

bool generateTmd(const char* const contentName, const uint32_t titleId,
                 const char* const encryptedTitleKeyFile,
                 const bool diskEncryption, char *tmdFileName,
                 char *encryptedContentName, char *h3FileName,
                 char *titleKeyName);

bool generateEticket(const char* const encryptedTitleKeyFile, 
                     char *ticketName);

DVDDiskId       defaultDiskId = {{"CROP"}, {'S', 'S'},
                          17, 47, 0, 0, {0}, RVL_MAGIC, {0}};

DVDDiskInfo     defaultDiskInfo = {"CropDuster", 1, 1};

static char     *scriptFileName = NULL, *outputFileName = NULL;
char            *ProgName;

static bool     Full_image = false, Verbose = false;
/* ------------------------------------------------------------------------ */

void
usage()
{
    fprintf (stderr, "Usage: %s\n", ProgName);
    fprintf(stderr,
        " -e, --encrypt         - encrypt disk image\n"
        " -f, --full            - generate full image (disk id, etc.)\n"
        " -h, --help            - print usage message\n"
        " -o, --out <file>      - output image name [default: output.image]\n"
        " -s, --script <file>   - input script file name\n"
        " -t, --titleKey <file> - title key file (encrypted)\n"
        " -v, --verbose         - print out messages as image is created\n"
        " -z, --hash            - hash disk image\n");
}
/* ------------------------------------------------------------------------ */

/*
 * Process the program arguments.
 * OUTPUT:
 *              Sets the titleKey
 */

static void
processOptions(int argc, char* argv[], inputDisk_t* const inputDisk,
               char** titleKeyName)
{
    *titleKeyName = NULL;

    while (1) {
#if defined(__CYGWIN__)
        int ch = getopt(argc, argv, options);
#else
        int ch = getopt_long_only(argc, argv, options, longOptions, 0);
#endif

        if (ch == -1)
            break;

        switch (ch) {

        case 'e':
            inputDisk->diskInfo->noEncryption = 0;
            break;

        case 'f':
            Full_image = true;
            break;

        case 'h':
            usage();
            exit(0);
            break;

        case 'o':
            outputFileName = optarg;
            break;

        case 's':
            scriptFileName = optarg;
            break;
        
        case 't':
            *titleKeyName = optarg;
            break;

        case 'v':
            Verbose = true;

        case 'z':
            inputDisk->diskInfo->noHash = 0;
            break;

        default:
            usage();
            exit(1);
        }
    }
    if (scriptFileName == NULL) {
        fprintf (stderr, "(%s) Need script file name\n", argv[0]);
        usage();
        exit(1);
    }
    if (outputFileName == NULL) {
        outputFileName = "output.image";
    }
}
/* ------------------------------------------------------------------------ */

int
main(int argc, char *argv[])
{
    char*       titleKeyName;
    inputDisk_t inputDisk;

    ProgName = argv[0];

    /* Set defaults before processing options */
    inputDisk.diskId   = &defaultDiskId;
    inputDisk.diskInfo = &defaultDiskInfo;

    processOptions(argc, argv, &inputDisk, &titleKeyName);

    parseScriptFile(scriptFileName, &inputDisk);

    if (parseScriptFile(scriptFileName, &inputDisk) == false) {
        fprintf (stderr, "%s: Processing of script file failed - exit\n",
                 ProgName);
        exit(1);
    }

    if (generateDiskImage(&inputDisk, titleKeyName, outputFileName) == false) {
        fprintf (stderr, "%s: Generation of output disk image failed\n",
                 ProgName);
        exit(1);
    }
    if (Full_image == false) {
        truncateImage(outputFileName, GLOBAL_TOC_OFFSET);
    }
    exit(0);
}

/* ------------------------------------------------------------------------ */

extern char *tempnam(const char *dir, const char *pfx);

void
truncateImage(char *inFileName, off_t truncateOffset)
{
    char        *tempFileName, buf[4096];
    FILE        *oldFile, *newFile;
    size_t      bytesRead, bytesWritten;
    bool        done = false;

    tempFileName = tempnam(".", "rvl");
    if (tempFileName == NULL) {
        printf ("(truncateImage) tempnam failed - exit\n");
        exit(1);
    }
    if (rename(inFileName, tempFileName) != 0) {
        perror ("(truncateImage) rename failed - exit\n");
        exit(1);
    }
    if ((oldFile = fopen(tempFileName, "r")) == NULL) {
        fprintf (stderr, "(%s) Error: Can't open file '%s'\n",
                 ProgName, tempFileName);
        exit(1);
    }
    if ((newFile = fopen(inFileName, "w")) == NULL) {
        fprintf (stderr, "(%s) Error: Can't open file '%s'\n",
                 ProgName, inFileName);
        exit(1);
    }
    if (fseeko(oldFile, truncateOffset, SEEK_SET) == -1) {
        perror("fseeko");
        exit(1);
    }

    do {
        bytesRead = fread(buf, 1, sizeof(buf), oldFile);
        if (bytesRead != sizeof(buf)) {
            if (ferror(oldFile)) {
                printf ("Error in reading old file - exit\n");
                exit(1);
            }
            else {
                done = true;
            }
        }
        bytesWritten = fwrite(buf, 1, bytesRead, newFile);
        if (bytesWritten != bytesRead) {
            printf ("Error in writing new file - exit\n");
            exit(1);
        }
    }
    while (! done);
    if (unlink(tempFileName) != 0) {
        fprintf (stderr, "(%s) Can't unlink %s\n", ProgName, tempFileName);
    }
}


/* ------------------------------------------------------------------------ */

/*
 * Skip white space in the string passed in, except for newlines.
 * RETURNS:
 *           false if a newline is found before a non space character.
 *           true otherwise.
 */
inline bool
skipSpace(const char* theString, int *position)
{
    while(isspace (theString[*position])) {
        if (theString[*position] == '\n') {
            return(false);
        }
        else {
            (*position)++;
        }
    }
    return(true);
}
/* ------------------------------------------------------------------------ */

/*
 * INPUT:  an unsigned integer N which is a power of 2
 * OUTPUT: an unsigned integer which has log2(N) 1 bits in the lower
 *         part of the word
 */

inline off_t
log2Mask(off_t powerOf2)
{
    off_t    mask;

    if (powerOf2 == 0) {
        printf ("(%s) Error: can't take log of 0\n", ProgName);
        exit(1);
    }

    mask = 0;
    for (int i = 0; i < sizeof(off_t) * 8; i++) {
        if ((powerOf2 & 0x1) == 0x1) {
            return(mask);
        }
        else {
            mask <<= 1;
            mask |= 0x1;
            powerOf2 >>= 1;
        }
    }
    fprintf (stderr, "Code should never reach here!\n");
    exit(1);
}

/* ------------------------------------------------------------------------ */

inline off_t
alignOffset(off_t address, const uint32_t alignment)
{
    uint32_t    alignmentMask;
    off_t       addVal;

    alignmentMask = log2Mask((off_t) alignment);
    if ((address & alignmentMask) == 0) {
        return(address);
    }
    else {
        addVal = alignmentMask + 1;
        address &= ~alignmentMask;
        address += addVal;
        return(address);
    }
}

/* ------------------------------------------------------------------------ */

bool
writeDiskId(const DVDDiskId* const diskId, FILE *outFile)
{
    size_t      numWritten;
    uint32_t    magicBigEnd;

    numWritten = fwrite(&(diskId->gameName), sizeof(uint8_t), 4, outFile);
    if (numWritten != 4) {
        return(false);
    }
    numWritten = fwrite(&(diskId->company), sizeof(uint8_t), 2, outFile);
    if (numWritten != 2) {
        return(false);
    }
    numWritten = fwrite(&(diskId->diskNumber), sizeof(uint8_t), 1, outFile);
    if (numWritten != 1) {
        return(false);
    }
    numWritten = fwrite(&(diskId->streaming), sizeof(uint8_t), 1, outFile);
    if (numWritten != 1) {
        return(false);
    }
    numWritten = fwrite(&(diskId->streamingBufSize), sizeof(uint8_t),
                        1, outFile);
    if (numWritten != 1) {
        return(false);
    }
    numWritten = fwrite(&(diskId->padding1), sizeof(uint8_t), 14, outFile);
    if (numWritten != 14) {
        return(false);
    }
    magicBigEnd = htonl(diskId->magic);
    numWritten = fwrite(&magicBigEnd, sizeof(uint32_t), 1, outFile);
    if (numWritten != 1) {
        return(false);
    }
    numWritten = fwrite(&(diskId->padding1), sizeof(uint8_t), 4, outFile);
    if (numWritten != 4) {
        return(false);
    }
    return(true);
} // writeDiskId

/* ------------------------------------------------------------------------ */

bool
writeDiskInfo(const DVDDiskInfo* const diskInfo, FILE *outFile)
{
    size_t      numWritten;

    numWritten = fwrite(&(diskInfo->gameNameLong), sizeof(uint8_t),
                        64, outFile);
    if (numWritten != 64) {
        return(false);
    }
    numWritten = fwrite(&(diskInfo->noHash), sizeof(uint8_t), 1, outFile);
    if (numWritten != 1) {
        return(false);
    }
    numWritten = fwrite(&(diskInfo->noEncryption), sizeof(uint8_t), 1, outFile);
    if (numWritten != 1) {
        return(false);
    }
    return(true);
} // writeDiskId

/* ------------------------------------------------------------------------ */
bool
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
            const char* const encryptedTitleKeyFile,
            const bool diskEncryption, char *tmdName,
            char *encryptedContentName, char* h3HashName, char* titleKeyName)
{
    char        commandBuf[1024];
    int         status;
    uint32_t    contentCID = 0;

    sprintf (commandBuf, "tmd -O -T 0x%" PRIx32 " -c 0x%" PRIx32,
                          titleId, contentCID);
    strcat (commandBuf, " -i 0");               // content index is 0
    strcat (commandBuf, " -P d");               // devel PKI
    strcat (commandBuf, " -n  ");
    strcat (commandBuf, contentName);           // input content
    strcat (commandBuf, " -t 2");               // content is shared
    if (encryptedTitleKeyFile != NULL) {
        strcat (commandBuf, " -K ");
        strcat (commandBuf, encryptedTitleKeyFile);
    }
    if (diskEncryption) {
        strcat (commandBuf, " -d ");
    }
    strcat (commandBuf, " > tmd.out 2>&1 ");
    status = system(commandBuf);
    if (Verbose) {
        printf ("TMD command is: %s\n", commandBuf);
    }
    if (status == -1) {
        fprintf (stderr, "%s: fork failed for command '%s'\n",
                 ProgName, commandBuf);
        return(false);
    }
    if (WEXITSTATUS(status) != 0) {
        fprintf (stderr, "%s: tmd create command '%s' failed.\n",
                 ProgName, commandBuf);
        return(false);
    }

    sprintf(tmdName, "%08" PRIx32 ".tmd", titleId);
    if (! fileExists(tmdName)) {
        fprintf (stderr, "%s: expected 'tmd' to create file %s\n",
                 ProgName, tmdName);
        return(false);
    }

    sprintf(encryptedContentName, "%08" PRIx32 ".app", contentCID);
    if (! fileExists(encryptedContentName)) {
        fprintf (stderr, "%s: expected 'tmd' to create file %s\n",
                 ProgName, encryptedContentName);
        return(false);
    }

    sprintf(titleKeyName, "%08" PRIx32 ".titleKey", titleId);
    if (! fileExists(titleKeyName)) {
        fprintf (stderr, "%s: expected 'tmd' to create file %s\n",
                 ProgName, titleKeyName);
        return(false);
    }

    if (diskEncryption) {
        sprintf(h3HashName, "%08" PRIx32 ".hash", contentCID);
        if (! fileExists(h3HashName)) {
            fprintf (stderr, "%s: expected 'tmd' to create file %s\n",
                     ProgName, h3HashName);
            return(false);
        }
    }
    return(true);
} // generateTmd

/* ------------------------------------------------------------------------ */

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

/*
 * Write out the update meta-data and update data (collectively, the
 * update partition) for each update.
 * Each partition consists of, in order:
 * - update structure (includes eTicket, since it is fixed length)
 * - the TMD (variable length)
 * - the variable size certificate blob
 * - the image
 * RETURNS:
 *           an array of pointers to update tables of content
 */

updateTOC_t *
writeUpdates(inputDisk_t* const inputDisk, FILE *outFile,
             const char* const inputTitleKeyName,
             const off_t fileOriginOffset)
{
    updatePartition_t   *updatePart, updateCopy;
    updateTOC_t         *returnVal;
    off_t               fileOffset, partitionStart, tmdStart;
    off_t               certBlobStart, imageStart;

    returnVal = (updateTOC_t *) malloc (sizeof (updateTOC_t));
    if (returnVal == NULL) {
        printf ("Memory allocation error\n");
        exit(1);
    }
    returnVal->numUpdatePartitions = inputDisk->numUpdateAreas;
    returnVal->updatePartitions = (updatePartition_t **)
                                  malloc (sizeof(updatePartition_t *)
                                * returnVal->numUpdatePartitions);

    for (int i = 0; i < inputDisk->numUpdateAreas; i++) {
        char            tmdName[64], encryptedContentName[64], h3HashName[64];
        char            ticketName[64], titleKeyName[64];
        uint32_t        ticketSize;
        uint8_t         *ticket, *tmd, *certBlob;

        updatePart = (updatePartition_t *) malloc(sizeof (updatePartition_t));
        if (updatePart == NULL) {
            fprintf(stderr, "Memory allocation failed for update partition\n");
            exit(1);
        }

        if (generateTmd(inputDisk->inputUpdateAreas[i]->content,
                        inputDisk->inputUpdateAreas[i]->titleId,
                        NULL, false, tmdName,
                        encryptedContentName,
                        h3HashName, titleKeyName) == false) {
            return(NULL);
        }
        if (generateEticket(titleKeyName, ticketName) == false) {
            return(NULL);
        }
        
        /* Read E-ticket into update partition */
        if (readFileIntoArray(ticketName, &ticket, &ticketSize) == false) {
            return(NULL);
        }
        assert(ticketSize == sizeof(ESTicket));
        memcpy(&(updatePart->ticket), ticket, sizeof(ESTicket));
        free(ticket);

        /* Read TMD */
        if (readFileIntoArray(tmdName, &tmd, &(updatePart->tmdSize)) == false) {
            return(NULL);
        }

        if (readCertBlob(&certBlob, &(updatePart->certBlobSize)) == false) {
            return(NULL);
        }
        fileOffset = ftell(outFile) + fileOriginOffset;

        partitionStart = alignOffset(fileOffset, UPDATE_PARTITION_ALIGN);
        returnVal->updatePartitions[i] =
                            (updatePartition_t *) DISK_ADDR(partitionStart);

        tmdStart = partitionStart + sizeof(updatePartition_t);
        tmdStart = alignOffset(tmdStart, ITEM_ALIGN);
        certBlobStart = alignOffset(tmdStart + updatePart->tmdSize,
                                     ITEM_ALIGN);
        imageStart = certBlobStart + updatePart->certBlobSize;
        imageStart = alignOffset(imageStart, ITEM_ALIGN);

        /*
         * We make a copy of the update partition structure because
         * the pointers in it are going to be coverted to word offsets,
         * and we still need the original pointer values
         */
        updateCopy = *updatePart;
        updateCopy.tmdSize      = htonl(updatePart->tmdSize);
        updateCopy.tmd          = (ESTitleMeta *) DISK_ADDR(tmdStart);
        updateCopy.certBlobSize = htonl(updatePart->certBlobSize);
        updateCopy.certBlob     = (void *) DISK_ADDR(certBlobStart);
        updateCopy.image        = (uint8_t *) DISK_ADDR(imageStart);

        /*
         * Write out the update partition structure, which includes
         * the eTicket
         */
        if (fseeko(outFile,
                   partitionStart - fileOriginOffset, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(&updateCopy, sizeof(updatePartition_t), 1, outFile) != 1) {
            fprintf(stderr, "Update partition struct write failed\n");
            return(NULL);
        }

        /* Write out TMD structure */
        if (fseeko(outFile, tmdStart - fileOriginOffset, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(tmd, 1, updatePart->tmdSize, outFile)
                   != updatePart->tmdSize) {
            fprintf(stderr, "Game partition TMD write failed\n");
            return(NULL);
        }

        /* Write out certificates */
        if (fseeko(outFile, certBlobStart - fileOriginOffset, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(certBlob, updatePart->certBlobSize, 1, outFile) != 1) {
            fprintf(stderr, "Update partition certificates write failed\n");
            return(NULL);
        }

        /* Write out content */
        if (fseeko(outFile, imageStart - fileOriginOffset, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (copyFileToOutFile(outFile,
                              encryptedContentName) == false) {
            return(NULL);
        }
        free(tmd);
        free(certBlob);
    } // for
    return(returnVal);
} // writeUpdates

/* ------------------------------------------------------------------------ */


/*
 * INPUT:   fileOriginOffset - if the beginning of the output file is not
 *                             the beginning of the disk image,
 *                             fileOriginOffset tell how far into the disk
 *                             image the beginning of the output file is.
 *
 * Write out the game meta-data and game data (collectively, the
 * update partition) for each update.
 * Each partition consists of, in order:
 * - game structure (includes eTicket, since it is fixed length)
 * - the TMD (variable length)
 * - the variable size certificate blob
 * - the H3 hashes (fixed length)
 * - the "virtual disk image"
 * RETURNS:
 *           an array of pointers to game tables of content
 *
 * Yes, this does duplicate alot of code in writeUpdates.
 */

gameTOC_t *
writeGames(inputDisk_t* const inputDisk, FILE *outFile,
           const char* const inputTitleKeyName,
           const off_t fileOriginOffset)
{
    gamePartition_t     *gamePart, gameCopy;
    gameTOC_t           *returnVal;
    off_t               fileOffset, partitionStart, tmdStart;
    off_t               certBlobStart, h3HashStart, cryptAreaStart;

    returnVal = (gameTOC_t *) malloc (sizeof (gameTOC_t));
    if (returnVal == NULL) {
        printf ("Memory allocation error\n");
        exit(1);
    }
    returnVal->numGamePartitions = inputDisk->numGameAreas;
    returnVal->gamePartitions = (gamePartition_t **)
                                  malloc (sizeof(gamePartition_t *)
                                * returnVal->numGamePartitions);

    for (int i = 0; i < inputDisk->numGameAreas; i++) {
        char            tmdName[64], encryptedContentName[64], h3HashName[64];
        char            ticketName[64], titleKeyName[64];
        uint32_t        ticketSize;
        uint8_t         *ticket, *tmd, *certBlob;

        gamePart = (gamePartition_t *) malloc(sizeof (gamePartition_t));
        if (gamePart == NULL) {
            fprintf(stderr, "Memory allocation failed for game partition\n");
            exit(1);
        }

        if (generateTmd(inputDisk->inputGameAreas[i]->content,
                        inputDisk->inputGameAreas[i]->titleId,
                        NULL, true, tmdName,
                        encryptedContentName,
                        h3HashName, titleKeyName) == false) {
            return(NULL);
        }
        if (generateEticket(titleKeyName, ticketName) == false) {
            return(NULL);
        }
        
        /* Read E-ticket into game partition */
        if (readFileIntoArray(ticketName, &ticket, &ticketSize) == false) {
            return(NULL);
        }
        assert(ticketSize == sizeof(ESTicket));
        memcpy(&(gamePart->ticket), ticket, sizeof(ESTicket));
        free(ticket);

        /* Read TMD */
        if (readFileIntoArray(tmdName, &tmd, &(gamePart->tmdSize)) == false) {
            return(NULL);
        }

        if (readCertBlob(&certBlob, &(gamePart->certBlobSize)) == false) {
            return(NULL);
        }
        fileOffset = ftell(outFile) + fileOriginOffset;

        partitionStart = alignOffset(fileOffset, GAME_PARTITION_ALIGN);
        returnVal->gamePartitions[i] =
                            (gamePartition_t *) DISK_ADDR(partitionStart);

        tmdStart = partitionStart + sizeof(gamePartition_t);
        tmdStart = alignOffset(tmdStart, ITEM_ALIGN);
        certBlobStart = alignOffset(tmdStart + gamePart->tmdSize,
                                     ITEM_ALIGN);
        h3HashStart = certBlobStart + gamePart->certBlobSize;
        h3HashStart = alignOffset(h3HashStart, H3_ALIGN);

        cryptAreaStart = alignOffset(h3HashStart + H3_SIZE, ENCRYPT_ALIGN);

        /*
         * We make a copy of the game partition structure because
         * the pointers in it are going to be coverted to word offsets,
         * and we still need the original pointer values
         */
        gameCopy = *gamePart;
        gameCopy.tmdSize        = htonl(gamePart->tmdSize);
        gameCopy.tmd            = (ESTitleMeta *) DISK_ADDR(tmdStart);
        gameCopy.certBlobSize   = htonl(gamePart->certBlobSize);
        gameCopy.certBlob       = (void *) DISK_ADDR(certBlobStart);
        gameCopy.h3Hashes       = (uint8_t *) DISK_ADDR(h3HashStart);
        gameCopy.encryptedArea  = (uint8_t *) DISK_ADDR(cryptAreaStart);

        /*
         * Write out the game partition structure, which includes
         * the eTicket
         */
        if (fseeko(outFile,
                   partitionStart - fileOriginOffset, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(&gameCopy, sizeof(gamePartition_t), 1, outFile) != 1) {
            fprintf(stderr, "Game partition struct write failed\n");
            return(NULL);
        }

        /* Write out TMD structure */
        if (fseeko(outFile, tmdStart - fileOriginOffset, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(tmd, 1, gamePart->tmdSize, outFile) != gamePart->tmdSize) {
            fprintf(stderr, "Game partition TMD write failed\n");
            return(NULL);
        }

        /* Write out certificates */
        if (fseeko(outFile, certBlobStart - fileOriginOffset, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(certBlob, gamePart->certBlobSize, 1, outFile) != 1) {
            fprintf(stderr, "Game partition certificates write failed\n");
            return(NULL);
        }

        /* Write out H3 Hashes */
        if (fseeko(outFile, h3HashStart - fileOriginOffset, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (copyFileToOutFile(outFile, h3HashName) == false) {
            return(NULL);
        }

        /* Write out content */
        if (fseeko(outFile, cryptAreaStart - fileOriginOffset,
                   SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (copyFileToOutFile(outFile, encryptedContentName) == false) {
            return(NULL);
        }
        free(tmd);
        free(certBlob);
    } // for
    return(returnVal);
} // writeGames

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

/*
 * The disk image is laid out as follows:
 * RETURNS:
 *    true   -  if disk image was created
 *    false  -  if there was a problem, and image was not created
 *              
 */
bool
generateDiskImage(inputDisk_t* const inputDisk,
                  const char* const titleKeyName,
                  const char* const outputName)
{
    FILE        *outFile;
    off_t       globalTocOff, updateTocOff, gameTocOff;
    off_t       updatePartPtrArrayOff, gamePartPtrArrayOff;
    off_t       updateOff;
    updateTOC_t *updateToc;
    gameTOC_t   *gameToc;
    globalTOC_t globalToc;

    if ((outFile = fopen(outputName, "w")) == NULL) {
        fprintf (stderr, "(%s) Error - can't open file %s for writing\n",
                 ProgName, outputName);
        return(false);
    }

    zeroFile(outFile, 0, GLOBAL_TOC_OFFSET);

    /* Write disk ID and disk info */
    if (writeDiskId(inputDisk->diskId, outFile) == false) {
        goto handleError;
    }
    if (fseek(outFile, DISK_INFO_OFFSET, SEEK_SET) == -1) {
        perror ("fseek");
        goto handleError;
    }
    if (writeDiskInfo(inputDisk->diskInfo, outFile) == false) {
        goto handleError;
    }

    /*
     * Calculate the places that the tables of contents
     * and associated arrays of pointers to partitions will go
     */
    globalTocOff = GLOBAL_TOC_OFFSET;
    updateTocOff = alignOffset(globalTocOff + sizeof(globalTOC_t),
                               ITEM_ALIGN);
    updatePartPtrArrayOff = alignOffset(updateTocOff + sizeof(updateTOC_t),
                                        ITEM_ALIGN);
    gameTocOff =   updatePartPtrArrayOff
                 + (inputDisk->numUpdateAreas * sizeof(updatePartition_t *));
    gameTocOff = alignOffset(gameTocOff, ITEM_ALIGN);
    gamePartPtrArrayOff = alignOffset(gameTocOff + sizeof(gameTOC_t),
                                      ITEM_ALIGN);

    updateOff = gamePartPtrArrayOff 
                 + (inputDisk->numGameAreas * sizeof(gamePartition_t *));
    updateOff = alignOffset(updateOff, UPDATE_AREA_ALIGN);

    /*
     * Calculate and write global TOC
     */
    globalToc.updateTOC = (updateTOC_t *) DISK_ADDR(updateTocOff);
    globalToc.gameTOC   = (gameTOC_t *) DISK_ADDR(gameTocOff);

    if (fseeko(outFile, globalTocOff, SEEK_SET) == -1) {
        perror("fseeko");
        goto handleError;
    }
    if (fwrite(&globalToc, sizeof(globalTOC_t), 1, outFile) != 1) {
        fprintf(stderr, "Error writing global TOC\n");
        goto handleError;
    }

    if (fseeko(outFile, updateOff, SEEK_SET) == -1) {
        perror("fseeko");
        goto handleError;
    }

    /* Write the update paritions */
    updateToc = writeUpdates(inputDisk, outFile, titleKeyName, 0);

    if (updateToc == NULL) {
        goto handleError;
    }

    /*
     * Write the actual game partitions.
     * This must be done before writing the game table of contents
     * because in writing the game partitions, we determine where
     * each partition starts
     */
    gameToc = writeGames(inputDisk, outFile, titleKeyName, 0);
    if (gameToc == NULL) {
        goto handleError;
    }

    /* Write the update tables of contents */
    updateTOC_t         updateTocDisk;
    updateTocDisk.numUpdatePartitions = htonl(updateToc->numUpdatePartitions);
    updateTocDisk.updatePartitions =
                    (updatePartition_t **) DISK_ADDR(updatePartPtrArrayOff);

    if (fseeko(outFile, updateTocOff, SEEK_SET) == -1) {
        perror("fseeko");
        goto handleError;
    }
    /*
    printf ("Writing number of update paritions '%u' at 0x%llx\n",
             updateToc->numUpdatePartitions, updateTocOff);
    */
    if (fwrite(&updateTocDisk, sizeof(updateTOC_t), 1, outFile) != 1) {
        fprintf(stderr, "Error writing update TOC\n");
        goto handleError;
    }

    if (fseeko(outFile, updatePartPtrArrayOff, SEEK_SET) == -1) {
        perror("fseeko");
        goto handleError;
    }
    if (fwrite(updateToc->updatePartitions, sizeof(updatePartition_t *),
               updateToc->numUpdatePartitions,
               outFile) != updateToc->numUpdatePartitions) {
        fprintf(stderr, "Error writing update partition ptrs\n");
        goto handleError;
    }

    /* Write the game table of contents and pointers to partitons */
    gameTOC_t         gameTocDisk;

    gameTocDisk.numGamePartitions = htonl(gameToc->numGamePartitions);
    gameTocDisk.gamePartitions =
                        (gamePartition_t **) DISK_ADDR(gamePartPtrArrayOff);

    if (fseeko(outFile, gameTocOff, SEEK_SET) == -1) {
        perror("fseeko");
        goto handleError;
    }
    if (fwrite(&gameTocDisk, sizeof(gameTOC_t), 1, outFile) != 1) {
        fprintf(stderr, "Error writing game TOC\n");
        goto handleError;
    }

    if (fseeko(outFile, gamePartPtrArrayOff, SEEK_SET) == -1) {
        perror("fseeko");
        goto handleError;
    }
    if (fwrite(gameToc->gamePartitions, sizeof(gamePartition_t *),
               gameToc->numGamePartitions,
               outFile) != gameToc->numGamePartitions) {
        fprintf(stderr, "Error writing game partition ptrs\n");
        goto handleError;
    }

    if (fclose(outFile) == EOF) {
        perror ("fclose");
        goto handleError;
    }
    return(true);

handleError:
    fclose(outFile);
    unlink(outputName);
    return(false);
}

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */

/* Functions that implement reading and parsing the script file */

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */


/*
 * Convert the upper case letters in a string to lower case.
 * The conversion is done in-place.
 */
inline void
lowerCaseString(char* const theString)
{
    size_t      strLength;

    strLength = strlen(theString);

    for (size_t i = 0; i < strLength; i++) {
        if (isupper(theString[i])) {
            theString[i] = tolower(theString[i]);
        }
    }
}

/* ------------------------------------------------------------------------ */

/*
 * Read a script file from disk, and return a filled in inputDisk_t
 * structure representing the contents.
 *
 * Each section in the script file is parsed and put
 * into a temporary area 'inputArea'.  When the section ends,
 * inputArea is checked, and if it OK it is copied into an array
 * for safe keeping.
 * RETURNS: the structure if the file has no errors.
 *          NULL otherwise
 */


bool
parseScriptFile(const char* const scriptName, inputDisk_t* const inputDisk)
{
    FILE                        *script;
    char                        lineBuf[4096], *stringVal;
    int                         lineIdx, lineNum;
    formatToken_t               token;
    section_t                   currentSection;
    inputArea_t                 inputArea;
    int                         numGameAreas, numUpdateAreas;
    inputArea_t                 *tempGamePtrs[512];
    inputArea_t                 *tempUpdatePtrs[512];

    if ((script = fopen (scriptName, "r")) == NULL) {
        fprintf (stderr,
        "%s: Can't open script file '%s' for reading - exit\n", ProgName,
        scriptName);
        exit(1);
    }
    currentSection = NO_SECTION;
    lineNum        = 0;
    numGameAreas   = 0;
    numUpdateAreas = 0;

    while (fgets(lineBuf, sizeof(lineBuf), script) != NULL) {
        lineNum++;
        lineIdx = 0;

        /* Check for all blank lines */
        if (skipSpace(lineBuf, &lineIdx) == false) {
            continue;
        }
        /* Check for comment lines */
        if (lineBuf[lineIdx] == '#') {
            continue;
        }
        token = getToken(lineBuf, &lineIdx); 
        switch(token) {

        case GAME:
        case UPDATE:
            if (currentSection == GAME_SECTION) {
                tempGamePtrs[numGameAreas] =
                    checkAndCopyInputArea(&inputArea);
                if (tempGamePtrs[numGameAreas] == NULL) {
                    return(false);
                }
                numGameAreas++;
            }
            else if (currentSection == UPDATE_SECTION) {
                tempUpdatePtrs[numUpdateAreas] =
                    checkAndCopyInputArea(&inputArea);
                if (tempUpdatePtrs[numUpdateAreas] == NULL) {
                    return(false);
                }
                numUpdateAreas++;
            }
            if (token == GAME) {
                currentSection = GAME_SECTION;
            }
            else {
                currentSection = UPDATE_SECTION;
            }
            inputArea.certName = NULL;
            inputArea.content  = NULL;
            inputArea.titleId  = 0;
            break;

        case CONTENT:
            if (currentSection == NO_SECTION) {
                fprintf(stderr,
                        "Error: 'content found without section (line %d)\n",
                        lineNum);
                fclose(script);
                return(false);
            }
            stringVal = getOneStringValue(lineBuf, &lineIdx, lineNum);
            if (stringVal == NULL) {
                fclose(script);
                return(false);
            }
            if (inputArea.content != NULL) {
                fprintf(stderr, "Error: Duplicate content names (line %d)\n",
                        lineNum);
                fclose(script);
                return(false);
            }
            inputArea.content = stringVal;
            break;

        case TITLE_ID:
            if (currentSection == NO_SECTION) {
                fprintf(stderr,
                        "Error: 'content found without section (line %d)\n",
                        lineNum);
                fclose(script);
                return(false);
            }

            if (getOneU32value(lineBuf, &lineIdx,
                               lineNum, &(inputArea.titleId)) == false) {
                fclose(script);
                return(false);
            }
            break;

        case INVALID_TOKEN:
            fprintf (stderr, "Error: Invalid token (line %d)\n",
                     lineNum);
            fclose(script);
            return(false);
            break;

        default:
            fprintf (stderr, "Internal error: Unhandled token (line %d)\n",
                     lineNum);
            exit(1);
            break;
        }
    }

    if (fclose(script) != 0) {
        perror ("fclose:");
    }

    if (currentSection == GAME_SECTION) {
        tempGamePtrs[numGameAreas] = checkAndCopyInputArea(&inputArea);
        if (tempGamePtrs[numGameAreas] == NULL) {
            return(false);
        }
        numGameAreas++;
    }
    else if (currentSection == UPDATE_SECTION) {
        tempUpdatePtrs[numUpdateAreas] = checkAndCopyInputArea(&inputArea);
        if (tempUpdatePtrs[numUpdateAreas] == NULL) {
            return(false);
        }
        numUpdateAreas++;
    }

    /* Copy over input game areas */
    inputDisk->numGameAreas = numGameAreas;
    inputDisk->inputGameAreas =
        (inputArea_t **) malloc(numGameAreas * sizeof (inputArea_t *));

    if (inputDisk->inputGameAreas == NULL) {
        fprintf (stderr, "(%s) Memory allocation failed - exit\n", ProgName);
        exit(1);
    }
    for (int i = 0; i < inputDisk->numGameAreas; i++) {
        inputDisk->inputGameAreas[i] = tempGamePtrs[i];
    }

    /* Copy over input update areas */
    inputDisk->numUpdateAreas = numUpdateAreas;
    inputDisk->inputUpdateAreas =
        (inputArea_t **) malloc(numUpdateAreas * sizeof (inputArea_t *));

    if (inputDisk->inputUpdateAreas == NULL) {
        fprintf (stderr, "(%s) Memory allocation failed - exit\n", ProgName);
        exit(1);
    }
    for (int i = 0; i < inputDisk->numUpdateAreas; i++) {
        inputDisk->inputUpdateAreas[i] = tempUpdatePtrs[i];
    }
    return(true);
} // parseScriptFile
/* ------------------------------------------------------------------------ */

/*
 * RETURNS:
 *
 *           Updates the current position (*startPos) in the string
 */
formatToken_t
getToken (char *inputLine, int *startPos)
{
    char                copyBuf[1024];
    int                 tokenStartIdx = 0, tokenLength;

    if (skipSpace(inputLine, startPos) == false) {
        return(NO_TOKEN);
    }
    tokenStartIdx = *startPos;
    while (! isspace (inputLine[*startPos])) {
        (*startPos)++;
    }
    tokenLength = *startPos - tokenStartIdx;
    strncpy(copyBuf, inputLine + tokenStartIdx, tokenLength);
    copyBuf[tokenLength] = '\0';

    lowerCaseString(copyBuf);

    if (strcmp(copyBuf, "content") == 0) {
        return(CONTENT);
    }
    else if (strcmp(copyBuf, "titleid") == 0) {
        return(TITLE_ID);
    }
    else if (strcmp(copyBuf, "[game]") == 0) {
        return(GAME);
    }
    else if (strcmp(copyBuf, "[update]") == 0) {
        return(UPDATE);
    }
    else {
        return(INVALID_TOKEN);
    }
} // getToken

/* ------------------------------------------------------------------------ */

/*
 * RETURNS:
 *
 *           Updates the current position (*startPos) in the string
 */
char *
getOneStringValue (char *inputLine, int *position, const int lineNum)
{
    char                *returnVal;
    int                 valueStartIdx = 0, valueLength;

    if (skipSpace(inputLine, position) == false) {
        return(NULL);
    }
    if (inputLine[*position] != '=') {
        fprintf (stderr, "Error: missing '=' (line %d)\n", lineNum);
        return(NULL);
    }

    // Skip past equal sign
    (*position)++;

    if (skipSpace(inputLine, position) == false) {
        return(NULL);
    }

    if (inputLine[*position] != '"') {
        fprintf (stderr, "Error: missing starting '\"' (line %d)\n", lineNum);
        return(NULL);
    }
    (*position)++;

    valueStartIdx = *position;
    while (inputLine[*position] != '\"' && inputLine[*position] != '\n') {
        (*position)++;
    }
    if (inputLine[*position] != '\"') {
        fprintf(stderr, "Unmatched '\"' in string (line %d)\n", lineNum);
        return(NULL);
    }
    valueLength = *position - valueStartIdx;

    (*position)++;

    returnVal = (char *) malloc (valueLength + 1);
    if (returnVal == NULL) {
        fprintf (stderr, "Error: malloc returned NULL - exit\n");
        exit(1);
    }
    strncpy(returnVal, inputLine + valueStartIdx, valueLength);
    returnVal[valueLength] = '\0';
    return(returnVal);
} // getOneStringValue

/* ------------------------------------------------------------------------ */

/*
 * RETURNS:
 *
 *           Updates the current position (*startPos) in the string
 */
void
getMultipleStringVals (char *inputLine, int *position, const int lineNum,
                       int *numStrings, char ***strArrayPtr)
{
    int                 valueStartIdx = 0, valueLength;
    char                *tempStrArray[128];
    bool                errorFound = false;

    *numStrings = 0;

    if (skipSpace(inputLine, position) == false) {
        fprintf (stderr, "Error: missing certificate names (line %d)\n",
                 lineNum);
        return;
    }
    if (inputLine[*position] != '=') {
        fprintf (stderr, "Error: missing '=' (line %d)\n", lineNum);
        return;
    }

    // Skip past equal sign
    (*position)++;

    if (skipSpace(inputLine, position) == false) {
        return;
    }

    while (1) {
        // Currently pointing a non-space character.
        if (inputLine[*position] != '"') {
            fprintf (stderr, "Error: missing starting '\"' (line %d)\n",
                     lineNum);
            errorFound = true;
        }
        (*position)++;

        valueStartIdx = *position;
        while (inputLine[*position] != '\"' && inputLine[*position] != '\n') {
            (*position)++;
        }
        if (inputLine[*position] != '\"') {
            fprintf(stderr, "Unmatched '\"' in string (line %d)\n", lineNum);
            errorFound = true;
            break;
        }
        valueLength = *position - valueStartIdx;

        (*position)++;

        tempStrArray[*numStrings] = (char *) malloc (valueLength + 1);
        if (tempStrArray[*numStrings] == NULL) {
            fprintf (stderr, "Error: malloc returned NULL - exit\n");
            exit(1);
        }
        strncpy(tempStrArray[*numStrings],
                inputLine + valueStartIdx, valueLength);
        tempStrArray[*numStrings][valueLength] = '\0';
        (*numStrings)++;

        if (skipSpace(inputLine, position) == false) {
            break;
        }
        if (inputLine[*position] != ',') {
            fprintf (stderr, "Error: need ',' character (line %d)\n", lineNum);
            errorFound = true;
            break;
        }
    }

    if (errorFound) {
        for (int i = 0; i < *numStrings; i++) {
            free(tempStrArray[i]);
        }
        *numStrings = 0;
    }
    else {
        *strArrayPtr = (char **) malloc(sizeof (char *) * *numStrings);
        if (*strArrayPtr == NULL) {
            fprintf (stderr, "Error: malloc returned NULL - exit\n");
            exit(1);
        }
        for (int i = 0; i < *numStrings; i++) {
            (*strArrayPtr)[i] = tempStrArray[i];
        }
    }
} // getMultipleStringVals

/* ------------------------------------------------------------------------ */

/*
 * RETURNS:
 *           true if a number is successfully read
 *           false otherwise
 *
 *           Updates the current position (*startPos) in the string
 */
bool
getOneU32value (const char* const inputLine, int *position, const int lineNum,
                uint32_t *value)
{
    char                *endPtr;
    bool                returnVal;

    if (skipSpace(inputLine, position) == false) {
        return(false);
    }

    if (inputLine[*position] != '=') {
        fprintf (stderr, "Error: missing '=' (line %d)\n", lineNum);
        return(false);
    }

    // Skip past equal sign
    (*position)++;

    if (skipSpace(inputLine, position) == false) {
        return(false);
    }

    *value = strtoul(inputLine + *position, &endPtr, 16);

    if (endPtr == inputLine + *position) {          // Nothing was read
        returnVal = false;
    }
    else {
        returnVal = true;
    }
    *position = endPtr - inputLine;
    return(returnVal);
} // getOneStringValue

/* ------------------------------------------------------------------------ */

bool
areaInputOK(const inputArea_t const *inputArea)
{
    if (inputArea->content == NULL) {
        return(false);
    }
    else {
        return(true);
    }
}

/* ------------------------------------------------------------------------ */

inputArea_t *
checkAndCopyInputArea(const inputArea_t* const inputArea)
{
    inputArea_t     *returnVal;

    if (areaInputOK(inputArea) == false) {
        return(NULL);
    }
    returnVal = (inputArea_t *) malloc (sizeof(inputArea_t));
    if (returnVal == NULL) {
        fprintf (stderr, "(%s) Memory allocate failed - exit\n", ProgName);
        exit(1);
    }
    memcpy(returnVal, inputArea, sizeof(inputArea_t));
    return(returnVal);
}
/* ------------------------------------------------------------------------ */

/*
 * Write 'length' zero bytes into the file starting at offset.
 * Seek back to the beginning of the write so that the write
 * doesn't have the side-effect of changing the current place in
 * the file.
 * 
 */

void
zeroFile(FILE *theFile, off_t start, off_t length)
{
    uint8_t     *zeroArray;
    off_t       fileOffset;

    fileOffset = ftello(theFile);

    zeroArray = (uint8_t *) malloc (length);
    assert(zeroArray != NULL);
    memset (zeroArray, 0, length);
    if (fseeko(theFile, start, SEEK_SET) == -1) {
        perror("fseeko");
        exit(1);
    }
    if (fwrite(zeroArray, 1, length, theFile) != length) {
        fprintf (stderr, "Can't write %llu 0 bytes to file - exit\n", length);
        exit(1);
    }
    free(zeroArray);
    if (fseeko(theFile, fileOffset, SEEK_SET) == -1) {
        perror("fseeko");
        exit(1);
    }
}

/* ------------------------------------------------------------------------ */

void
printMD5sum(const void* const ptr, const uint32_t numBytes)
{
    md5_state_t state;
    md5_byte_t digest[16];

    md5_init(&state);
    md5_append(&state, ptr, numBytes);
    md5_finish(&state, digest);

    for (int idx = 0; idx < 16; idx++) {
        printf("%02x", digest[idx]);
    }
}

/* ------------------------------------------------------------------------ */
