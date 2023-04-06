#ident "$Id: rvl_image.c,v 1.14 2006/04/01 00:46:51 craig Exp $"
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
#include <netinet/in.h>         // For htonl()
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "aes.h"
#include "sha1.h"
#include "image_superblock.h"
#include "types.h"
#include "disk_format.h"
#include "estypes.h"
#include "md5.h"

#define AES_KEY_LENGTH          16

enum formatToken {NO_TOKEN, INVALID_TOKEN, GAME, UPDATE, E_TICKET, TMD,
                  CERTIFICATES, CONTENT};
typedef enum formatToken      formatToken_t;

enum section {GAME_SECTION, UPDATE_SECTION, NO_SECTION};
typedef enum section section_t;

typedef struct inputArea {
    char *eTicketName;
    char *tmdName;
    char *certName;
    char *content;
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
    {"full",            0, 0, 'f'},     /* Generate entire disk image */
    {"help",            0, 0, 'h'},     /* Print usage */
    {"output",          1, 0, 'o'},     /* Output image name */
    {"script",          1, 0, 's'},     /* Input script file */             
    {"titleKey",        1, 0, 't'},     /* Title key file */             
    {"verbose",         0, 0, 'v'},     /* Print status output when running */
    {"hash",            0, 0, 'z'},     /* Hash disk image */
    {0, 0, 0, 0}
};
#endif

static char* options = "efho:s:t:z";

formatToken_t getToken (char *inputLine, int *startPos);
char *getOneStringValue (char *inputLine, int *position, const int lineNum);
void getMultipleStringVals (char *inputLine, int *position, const int lineNum,
                            int *numStrings, char ***strArrayPtr);
bool gameInputOK(const inputArea_t const *inputGame);

bool parseScriptFile(const char* const scriptName,
                     inputDisk_t* const inputDisk);

inputArea_t *checkAndCopyInputArea(const inputArea_t* const area);
bool generateDiskImage(inputDisk_t* const inputDisk,
                       const uint8_t* const titleKey,
                       const char* const outputName);

bool getETicket(const char* const eTicketFileName, ESTicket *ticket);

bool getTMD(const char* const TMDFileName, uint32_t *tmdSize,
            ESTitleMeta **tmdHandle);

bool getCertBlob(const char* const certName, uint32_t *certBlobSize,
                 void **certBlob);

bool getPartitionElements(const inputArea_t* const inputArea,
                          ESTicket *ticket,
                          uint32_t *tmdSize, ESTitleMeta **tmd,
                          uint32_t *certBlobSize, void **certBlob);

void truncateImage(char *inFileName, off_t truncateOffset);
void zeroFile(FILE *theFile, off_t start, off_t length);
void printMD5sum(const void* const ptr, const uint32_t numBytes);

DVDDiskId       defaultDiskId = {{"CROP"}, {'S', 'S'},
                          17, 47, 0, 0, {0}, RVL_MAGIC, {0}};

DVDDiskInfo     defaultDiskInfo = {"CropDuster", 1, 1};

static char     *scriptFileName = NULL, *outputFileName = NULL;
char            *ProgName;

static bool     Full_image = false, Verbose = false;
/* ------------------------------------------------------------------------ */

void
usage(const char* const progName)
{
    fprintf (stderr, "Usage: %s\n", progName);
    fprintf(stderr,
        " -e, --encrypt         - encrypt disk image\n"
        " -f, --full            - generate full image (disk id, etc.)\n"
        " -h, --help            - print usage message\n"
        " -o, --out <file>      - output image name [default: output.image]\n"
        " -s, --script <file>   - input script file name\n"
        " -t, --titleKey <file> - title key file (unencrypted)\n"
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
               uint8_t* const titleKey)
{
    char        *titleKeyName = NULL;
    uint8_t     defaultTitleKey[] = {0xde, 0xad, 0xbe, 0xef,
                                     0xde, 0xad, 0xbe, 0xef,
                                     0xde, 0xad, 0xbe, 0xef,
                                     0xde, 0xad, 0xbe, 0xef};
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
            usage(argv[0]);
            exit(0);
            break;

        case 'o':
            outputFileName = optarg;
            break;

        case 's':
            scriptFileName = optarg;
            break;
        
        case 't':
            titleKeyName = optarg;
            break;

        case 'v':
            Verbose = true;

        case 'z':
            inputDisk->diskInfo->noHash = 0;
            break;

        default:
            usage(argv[0]);
            exit(1);
        }
    }
    if (scriptFileName == NULL) {
        fprintf (stderr, "(%s) Need script file name\n", argv[0]);
        usage(argv[0]);
        exit(1);
    }
    if (outputFileName == NULL) {
        outputFileName = "output.image";
    }
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
}
/* ------------------------------------------------------------------------ */

int
main(int argc, char *argv[])
{
    uint8_t     titleKey[AES_KEY_LENGTH];
    inputDisk_t inputDisk;

    ProgName = argv[0];

    /* Set defaults before processing options */
    inputDisk.diskId   = &defaultDiskId;
    inputDisk.diskInfo = &defaultDiskInfo;

    processOptions(argc, argv, &inputDisk, titleKey);

    parseScriptFile(scriptFileName, &inputDisk);

    if (parseScriptFile(scriptFileName, &inputDisk) == false) {
        fprintf (stderr, "%s: Processing of script file failed - exit\n",
                 ProgName);
        exit(1);
    }

    if (generateDiskImage(&inputDisk, titleKey, outputFileName) == false) {
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

gamePartition_t *
getGamePartition(const inputArea_t* const inputGame)
{
    gamePartition_t       *returnVal;

    returnVal = (gamePartition_t *) malloc(sizeof (gamePartition_t));
    if (returnVal == NULL) {
        fprintf (stderr, "Memory allocation error\n");
        exit(1);
    }
    if (getPartitionElements(inputGame, &(returnVal->ticket),
                             &(returnVal->tmdSize), &(returnVal->tmd),
                             &(returnVal->certBlobSize),
                             &(returnVal->certBlob)) == false) {
        free(returnVal);
        return(NULL);
    }
    return(returnVal);
} // getGamePartition

/* ------------------------------------------------------------------------ */

updatePartition_t *
getUpdatePartition(const inputArea_t* const inputUpdate)
{
    updatePartition_t       *returnVal;

    returnVal = (updatePartition_t *) malloc(sizeof (updatePartition_t));
    if (returnVal == NULL) {
        fprintf (stderr, "Memory allocation error\n");
        exit(1);
    }
    if (getPartitionElements(inputUpdate, &(returnVal->ticket),
                             &(returnVal->tmdSize), &(returnVal->tmd),
                             &(returnVal->certBlobSize),
                             &(returnVal->certBlob)) == false) {
        free(returnVal);
        return(NULL);
    }
    return(returnVal);
} // getUpdatePartition

/* ------------------------------------------------------------------------ */

/*
 * INPUT:   inputArea
 * OUTPUT:  pointers to - an ETicket, the size of the TMD, the TMD,
 *                        and an array of certificates.
 * RETURNS: true if reading the files went OK, false otherwise
 */

bool
getPartitionElements(const inputArea_t* const inputArea,
                     ESTicket *ticket,
                     uint32_t *tmdSize, ESTitleMeta **tmd,
                     uint32_t *certBlobSize, void **certBlob
                     )
{
    if (getETicket(inputArea->eTicketName, ticket) == false) {
        return(false);
    }
    if (getTMD(inputArea->tmdName, tmdSize, tmd) == false) {
        return(false);
    }
    if (getCertBlob(inputArea->certName, certBlobSize, certBlob) == false) {
        return(false);
    }
    return(true);
}
/* ------------------------------------------------------------------------ */

/*
 * INPUT:    the number of certificates and an array of certificate
 *           file names
 * RETURNS:  true  if everything went OK.
 *           false if there was an error.
 *         
 */
bool
getCertBlob(const char* certName, uint32_t *certBlobSize, void **certBlob)
{
    FILE                *inFile;
    struct stat         statBuf;
    size_t              numRead;

    if (stat(certName, &statBuf) == -1) {
        perror ("cert file stat");
        return(false);
    }
    *certBlob = malloc (statBuf.st_size);
    *certBlobSize = statBuf.st_size;

    if (*certBlob == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    if ((inFile = fopen(certName, "r")) == NULL) {
        fprintf (stderr, "(%s) Can't open cert file %s\n",
                 ProgName, certName);
        free(*certBlob);
        return(false);
    }
    numRead = fread(*certBlob, statBuf.st_size, 1, inFile);
    if (numRead != 1) {
        fprintf(stderr, "Read of cert failed\n");
        free(*certBlob);
        return(false);
    }
    fclose(inFile);
    return(true);
} // getCertBlob

/* ------------------------------------------------------------------------ */

bool
getETicket(const char* const eTicketFileName, ESTicket *ticket)
{
    FILE        *inFile;
    struct stat statBuf;
    size_t      numRead;

    if (stat(eTicketFileName, &statBuf) == -1) {
        perror ("eTicket file stat");
        return(false);
    }
    if (sizeof(ESTicket) != statBuf.st_size) {
        fprintf (stderr,
                 "(%s) Eticket file is the wrong size %llu (should be %u)\n",
                 ProgName, statBuf.st_size, sizeof(ESTicket));
        return(false);
    }
    if ((inFile = fopen(eTicketFileName, "r")) == NULL) {
        fprintf (stderr, "(%s) Can't open eTicket file %s\n",
                 ProgName, eTicketFileName);
        return(false);
    }
    numRead = fread(ticket, sizeof(ESTicket), 1, inFile);
    if (numRead != 1) {
        fprintf(stderr, "Read of eTicket failed\n");
        return(false);
    }
    fclose(inFile);
    return(true);
}
/* ------------------------------------------------------------------------ */

bool
getTMD(const char* const TMDFileName, uint32_t *tmdSize,
       ESTitleMeta **tmdHandle)
{
    FILE        *inFile;
    struct stat statBuf;
    size_t      numRead;

    if (stat(TMDFileName, &statBuf) == -1) {
        perror ("TMD file stat");
        return(false);
    }
    *tmdSize = statBuf.st_size;
    if (Verbose) {
        printf ("Reading %u TMD bytes from file %s\n", *tmdSize, TMDFileName);
    }
    if ((inFile = fopen(TMDFileName, "r")) == NULL) {
        fprintf (stderr, "(%s) Can't open TMD file %s\n",
                 ProgName, TMDFileName);
        return(false);
    }
    *tmdHandle = (ESTitleMeta *) malloc(*tmdSize);
    if (*tmdHandle == NULL) {
        fprintf (stderr, "(%s) Memory allocation failed - exit\n", ProgName);
        exit(1);
    }
    numRead = fread(*tmdHandle, *tmdSize, 1, inFile);
    if (numRead != 1) {
        fprintf(stderr, "Read of TMD failed\n");
        return(false);
    }
    fclose(inFile);
    if (Verbose) {
        printf ("TMD MD5 sum: ");
        printMD5sum(*tmdHandle, *tmdSize);
        printf ("\n");
    }
    return(true);
}
/* ------------------------------------------------------------------------ */

bool
doHashEncrypt(FILE *outFile, const char* const contentName,
              const bool hash, const bool encrypt,
              const off_t h3HashStart, const off_t cryptAreaStart,
              const uint8_t* const titleKey,
              uint8_t *h4HashArray);

/*
 * Write out the game meta-data and game data (collectively, the
 * game partition) for each game.
 * Each partition consists of, in order:
 * - gamePartition structure (includes eTicket, since it is fixed length)
 * - the TMD (variable length)
 * - the variable size certificate array
 * - the H3 hashes
 * - the content area
 */

gameTOC_t *
writeGames(inputDisk_t* const inputDisk,
           const uint8_t* const titleKey,
           FILE *outFile)
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
            malloc (sizeof(gamePartition_t *) * returnVal->numGamePartitions);

    for (int i = 0; i < inputDisk->numGameAreas; i++) {
        uint8_t         h4HashArray[SHA1_DIGESTSIZE];

        gamePart = getGamePartition(inputDisk->inputGameAreas[i]);
        if (gamePart == NULL) {
            return(NULL);
        }

        /* Determine at which offset each of the items will live */
        fileOffset = ftello(outFile);
        partitionStart = alignOffset(fileOffset, GAME_PARTITION_ALIGN);
        if (Verbose) {
            printf ("Game partition #%d starts at 0x%llx.\n",
                     i, partitionStart);
        }
        returnVal->gamePartitions[i] =
                                (gamePartition_t *) DISK_ADDR(partitionStart);

        tmdStart = partitionStart + sizeof(gamePartition_t);
        tmdStart = alignOffset(tmdStart, ITEM_ALIGN);
        certBlobStart = alignOffset(tmdStart + gamePart->tmdSize, ITEM_ALIGN);
        h3HashStart = certBlobStart + gamePart->certBlobSize;
        h3HashStart = alignOffset(h3HashStart, H3_ALIGN);
        cryptAreaStart = alignOffset(h3HashStart + H3_SIZE, ENCRYPT_ALIGN);

        /*
         * We make a copy of the game partition structure because
         * the pointers are going to be coverted to word offsets,
         * and we still need the original pointer values
         */
        gameCopy = *gamePart;
        gameCopy.tmdSize         = htonl(gamePart->tmdSize);
        gameCopy.tmd             = (ESTitleMeta *) DISK_ADDR(tmdStart);
        gameCopy.certBlobSize    = htonl(gamePart->certBlobSize);
        gameCopy.certBlob        = (void *)    DISK_ADDR(certBlobStart);
        gameCopy.h3Hashes        = (uint8_t *) DISK_ADDR(h3HashStart);
        gameCopy.encryptedArea   = (uint8_t *) DISK_ADDR(cryptAreaStart);

        /*
         * Write out the game partition structure, which includes
         * the eTicket
         */
        if (fseeko(outFile, partitionStart, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(&gameCopy, sizeof(gamePartition_t), 1, outFile) != 1) {
            fprintf(stderr, "Game partition struct write failed\n");
            return(NULL);
        }


        /* Write out certificates */
        if (fseeko(outFile, certBlobStart, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(gamePart->certBlob,
                   gamePart->certBlobSize,
                   1,
                   outFile) != 1) {
            fprintf(stderr, "Game partition certificate blob write failed\n");
            return(NULL);
        }

        if (Verbose) {
            printf ("Game partition #%d's content starts at 0x%llx.\n",
                     i, cryptAreaStart);
        }
        /*
         * Compute hashed/encrypted area
         */

        bool            doEncrypt, doHash;
        doEncrypt   = inputDisk->diskInfo->noEncryption == 0 ? true : false;
        doHash      = inputDisk->diskInfo->noHash       == 0 ? true : false;

        if (doHashEncrypt(outFile, inputDisk->inputGameAreas[i]->content,
                          doHash, doEncrypt, h3HashStart,
                          cryptAreaStart, titleKey, h4HashArray) == false) {
            return(NULL);
        }

        /* Write out TMD structure */
        if (fseeko(outFile, tmdStart, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(gamePart->tmd, 1, gamePart->tmdSize, outFile)
                   != gamePart->tmdSize) {
            fprintf(stderr, "Game partition TMD write failed\n");
            return(NULL);
        }

    } // for
    return(returnVal);
} // writeGames

/* ------------------------------------------------------------------------ */

/*
 * Write the game partition data.
 * The data is hashed if 'hash' is true,
 * and encrypted if 'encrypt' is true.
 * INPUT:
 *             outFile:     Output file pointer
 *             contentName: Name of file that contains the unencrypted game
 *                          data.
 *             titleKey: an array of AES_KEY_LENGTH bytes that holds the
 *                       encryption key.
 *             h4Hash: an array of at least SHA1_DIGESTSIZE that will be
 *                     overwritten. 
 * RETURNS:
 *              The H4 hash in h4Hash
 */
bool
doHashEncrypt(FILE *outFile, const char* const contentName,
              const bool hash, const bool encrypt,
              const off_t h3HashStart, const off_t cryptAreaStart,
              const uint8_t* const titleKey,
              uint8_t *h4Hash)
{
    FILE        *content;
    uint8_t     h3Buf[BLOCKS_FOR_H3 * DVD_BLOCK_SIZE], *h3Ptr;
    off_t       endOfImage, h3HashEnd;
    SHA1Context context;

    /* Make sure that any unused bytes in the H3 hash area are 0 */
    memset(h3Buf, 0, sizeof(h3Buf));

    if ((content = fopen(contentName, "r")) == NULL) {
        fprintf (stderr, "Can't open content file %s\n", contentName);
    }
    if (fseeko(outFile, cryptAreaStart, SEEK_SET) == -1) {
        perror("fseeko");
        return(NULL);
    }
    h3Ptr = h3Buf;
    // printf ("Crypt area starts at: 0x%llx\n", cryptAreaStart);

    // Compute the hashed and encrypted blocks
    while (computeSuperBlock(content, outFile, h3Ptr,
                             titleKey, encrypt, hash) == true) {
        h3Ptr += SHA1_DIGESTSIZE;
    }

    fclose(content);

    endOfImage = ftello(outFile);
    if (fseeko(outFile, h3HashStart, SEEK_SET) == -1) {
        perror("fseeko");
        return(NULL);
    }
    if (fwrite(h3Buf, BLOCKS_FOR_H3 * DVD_BLOCK_SIZE, 1, outFile) != 1) {
        fprintf(stderr, "Game partition hash3 write failed\n");
        return(false);
    }

    SHA1Reset(&context);
    SHA1Input(&context, h3Buf, BLOCKS_FOR_H3 * DVD_BLOCK_SIZE);
    SHA1Result(&context, h4Hash);

    h3HashEnd = ftello(outFile);
    if (h3HashEnd < cryptAreaStart) {
        /*
         * Zero any extra bytes be the end of the H3 hashes and
         * the beginning of the encrypted area
         */
        zeroFile(outFile, h3HashEnd, cryptAreaStart - h3HashEnd);
    }

    if (fseeko(outFile, endOfImage, SEEK_SET) == -1) {
        perror("fseeko");
        return(false);
    }
    return(true);
} // doHashEncrypt
/* ------------------------------------------------------------------------ */

bool copyFileToOutFile(FILE *outFile, const char* const inFileName);

/*
 * Write out the update meta-data and update data (collectively, the
 * update partition) for each update.
 * Each partition consists of, in order:
 * - update structure (includes eTicket, since it is fixed length)
 * - the TMD (variable length)
 * - the variable size certificate array
 * - the image
 */

updateTOC_t *
writeUpdates(inputDisk_t* const inputDisk, FILE *outFile)
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
        updatePart = getUpdatePartition(inputDisk->inputUpdateAreas[i]);
        if (updatePart == NULL) {
            return(NULL);
        }

        /* Determine at which offset each of the items will live */
        fileOffset = ftello(outFile);
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
        if (fseeko(outFile, partitionStart, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(&updateCopy, sizeof(updatePartition_t), 1, outFile) != 1) {
            fprintf(stderr, "Update partition struct write failed\n");
            return(NULL);
        }

        /* Write out TMD structure */
        if (fseeko(outFile, tmdStart, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(updatePart->tmd, 1, updatePart->tmdSize, outFile)
                   != updatePart->tmdSize) {
            fprintf(stderr, "Game partition TMD write failed\n");
            return(NULL);
        }

        /* Write out certificates */
        if (fseeko(outFile, certBlobStart, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (fwrite(updatePart->certBlob,
                   updatePart->certBlobSize,
                   1,
                   outFile) != 1) {
            fprintf(stderr, "Game partition certificates write failed\n");
            return(NULL);
        }

        /* Write out content */
        if (fseeko(outFile, imageStart, SEEK_SET) == -1) {
            perror("fseeko");
            return(NULL);
        }
        if (copyFileToOutFile(outFile,
                              inputDisk->inputUpdateAreas[i]->content) == false) {
            return(NULL);
        }
    } // for
    return(returnVal);
} // writeUpdates

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

/*
 * The disk image is laid out as follows:
 * RETURNS:
 *    true   -  if disk image was created
 *    false  -  if there was a problem, and image was not created
 *              
 */
bool
generateDiskImage(inputDisk_t* const inputDisk,
                  const uint8_t* const titleKey,
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

    updateToc = writeUpdates(inputDisk, outFile);
    if (updateToc == NULL) {
        goto handleError;
    }

    /*
     * Write the actual game partitions.
     * This must be done before writing the game table of contents
     * because in writing the game partitions, we determine where
     * each partition starts
     */
    gameToc = writeGames(inputDisk, titleKey, outFile);
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
            inputArea.eTicketName = NULL;
            inputArea.tmdName  = NULL;
            inputArea.certName = NULL;
            inputArea.content  = NULL;
            break;

        case E_TICKET:
            if (currentSection == NO_SECTION) {
                fprintf(stderr,
                        "Error: eTicket found without section (line %d)\n",
                        lineNum);
                fclose(script);
                return(false);
            }
            stringVal = getOneStringValue(lineBuf, &lineIdx, lineNum);
            if (stringVal == NULL) {
                fclose(script);
                return(false);
            }
            if (inputArea.eTicketName != NULL) {
                fprintf(stderr, "Error: Duplicate eTicket names (line %d)\n",
                        lineNum);
                fclose(script);
                return(false);
            }
            inputArea.eTicketName = stringVal;
            break;

        case TMD:
            if (currentSection == NO_SECTION) {
                fprintf(stderr, "Error: TMD found without section (line %d)\n",
                        lineNum);
                fclose(script);
                return(false);
            }
            stringVal = getOneStringValue(lineBuf, &lineIdx, lineNum);
            if (stringVal == NULL) {
                fclose(script);
                return(false);
            }
            if (inputArea.tmdName != NULL) {
                fprintf(stderr, "Error: Duplicate TMD names (line %d)\n",
                        lineNum);
                fclose(script);
                return(false);
            }
            inputArea.tmdName = stringVal;
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

        case CERTIFICATES:
            if (currentSection == NO_SECTION) {
                fprintf(stderr,
                        "Error: 'certificate found without section (line %d)\n",
                        lineNum);
                fclose(script);
                return(false);
            }
            if (inputArea.certName != NULL) {
                fprintf(stderr,
                        "Error: Duplicate certificate lines (line %d)\n",
                        lineNum);
                fclose(script);
                return(false);
            }
            inputArea.certName = getOneStringValue(lineBuf, &lineIdx, lineNum);
            if (inputArea.certName == NULL) {
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

    if (strcmp(copyBuf, "certificates") == 0) {
        return(CERTIFICATES);
    }
    if (strcmp(copyBuf, "content") == 0) {
        return(CONTENT);
    }
    else if (strcmp(copyBuf, "eticket") == 0) {
        return(E_TICKET);
    }
    if (strcmp(copyBuf, "[game]") == 0) {
        return(GAME);
    }
    else if (strcmp(copyBuf, "tmd") == 0) {
        return(TMD);
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

bool
areaInputOK(const inputArea_t const *inputArea)
{
    if (inputArea->eTicketName == NULL) {
        return(false);
    }
    else if (inputArea->tmdName == NULL) {
        return(false);
    }
    else if (inputArea->certName == NULL) {
        return(false);
    }
    else if (inputArea->content == NULL) {
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
