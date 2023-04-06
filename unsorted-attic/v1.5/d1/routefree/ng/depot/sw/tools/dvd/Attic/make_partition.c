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

/*
 * Need to define this, or else on Cygwin the ticket and tmd
 * structures are laid out differently than on Linux
 */
#define BROADWAY_REV
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

enum section {GAME_SECTION, UPDATE_SECTION, NO_SECTION};
typedef enum section section_t;

typedef struct inputArea {
    char        *certName;
    char        *content;
    uint32_t    titleId;
} inputArea_t;


#if !defined(__CYGWIN__)
static struct option longOptions[] = {
    {"help",            0, 0, 'h'},     /* Print usage */
    {"output",          1, 0, 'o'},     /* Output image name */
    {"titleId",         1, 0, 't'},     /* Title id */             
    {"verbose",         0, 0, 'v'},     /* Print status output when running */
    {0, 0, 0, 0}
};
#endif

static char* options = "ho:t:v";

bool gameInputOK(const inputArea_t const *inputGame);


inputArea_t *checkAndCopyInputArea(const inputArea_t* const area);


bool getCertBlob(const char* const certName, uint32_t *certBlobSize,
                 void **certBlob);


void printMD5sum(const void* const ptr, const uint32_t numBytes);

bool generateTmd(const char* const contentName, const uint32_t titleId,
                 char *tmdFileName,
                 char *encryptedContentName, char *h3FileName,
                 char *titleKeyName);

bool generateEticket(const char* const encryptedTitleKeyFile, 
                     char *ticketName);

bool generatePartition(const char* const contentName,
                       const char* const outputName,
                       const uint32_t titleId);

char            *ProgName;

static bool     Verbose = false;
/* ------------------------------------------------------------------------ */

void
usage()
{
    fprintf (stderr, "Usage: %s [options] content_file\n", ProgName);
    fprintf(stderr,
        " -h, --help            - print usage message\n"
        " -o, --out <file>      - output image name [default: output.image]\n"
        " -t, --titleId <id>    - title key         [default: 0xdeadcafe]\n"
        " -v, --verbose         - print out messages as image is created\n");
}
/* ------------------------------------------------------------------------ */

/*
 * Process the program arguments.
 * OUTPUT:
 *              Sets the titleKey
 */

static void
processOptions(int argc, char* argv[], char **contentName,
               char **outputName, uint32_t *titleId)
{
    ProgName = argv[0];

    // Default values
    *outputName = NULL;
    *titleId = 0xdead;

    while (1) {
#if defined(__CYGWIN__)
        int ch = getopt(argc, argv, options);
#else
        int ch = getopt_long_only(argc, argv, options, longOptions, 0);
#endif

        if (ch == -1)
            break;

        switch (ch) {

        case 'h':
            usage();
            exit(0);
            break;

        case 'o':
            *outputName = optarg;
            break;

        case 't':
            /* Input string can be base 8, 10, or 16 */
            *titleId = strtoul(optarg, NULL, 0);
            break;

        case 'v':
            Verbose = true;
            break;

        default:
            usage();
            exit(1);
        }
    }
    if (optind >= argc) {
        fprintf (stderr, "%s: Need content name\n", argv[0]);
        usage();
        exit(1);
    }
    *contentName = argv[optind];

    if (*outputName == NULL) {
        *outputName = "output.image";
    }
}
/* ------------------------------------------------------------------------ */

int
main(int argc, char *argv[])
{
    char        *contentName, *outputFileName;
    uint32_t    titleId;

    ProgName = argv[0];

    processOptions(argc, argv, &contentName, &outputFileName, &titleId);

    if (generatePartition(contentName, outputFileName, titleId) == false) {
        fprintf (stderr, "%s: Generation of partition failed\n",
                 ProgName);
        exit(1);
    }
    exit(0);
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
            char *tmdName, char *encryptedContentName,
            char* h3HashName, char* titleKeyName)
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
    strcat (commandBuf, " -d ");
    strcat (commandBuf, " > tmd.out 2>&1 ");

    if (Verbose) {
        printf ("TMD command is: %s\n", commandBuf);
    }
    status = system(commandBuf);
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

    sprintf(tmdName, "%" PRIx32 ".tmd", titleId);
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

    sprintf(titleKeyName, "%" PRIx32 ".titleKey", titleId);
    if (! fileExists(titleKeyName)) {
        fprintf (stderr, "%s: expected 'tmd' to create file %s\n",
                 ProgName, titleKeyName);
        return(false);
    }

    sprintf(h3HashName, "%08" PRIx32 ".hash", contentCID);
    if (! fileExists(h3HashName)) {
        fprintf (stderr, "%s: expected 'tmd' to create file %s\n",
                 ProgName, h3HashName);
        return(false);
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
 */

bool
generatePartition(const char* const contentName, const char* const outputName,
                  const uint32_t titleId)
{
    FILE                *outFile;
    partition_t         partition, partitionOnDisk;
    off_t               fileOffset, partitionStart, tmdStart;
    off_t               certBlobStart, h3HashStart, cryptAreaStart;
    char                tmdName[64], encryptedContentName[64], h3HashName[64];
    char                ticketName[64], titleKeyName[64];
    uint32_t            ticketSize;
    uint8_t             *ticket, *tmd, *certBlob;

    if ((outFile = fopen(outputName, "w")) == NULL) {
        fprintf(stderr, "Can't open output file '%s'\n", outputName);
        return(false);
    }

    if (generateTmd(contentName, titleId, tmdName,
                    encryptedContentName,
                    h3HashName, titleKeyName) == false) {
        return(false);
    }
    if (generateEticket(titleKeyName, ticketName) == false) {
        return(false);
    }
    
    /* Read E-ticket into game partition */
    if (readFileIntoArray(ticketName, &ticket, &ticketSize) == false) {
        return(false);
    }
    if (ticketSize != sizeof(ESTicket)) {
        fprintf(stderr, "(%s) Error: sizeof of ticket file (%u) does not match the sizeof an ESTicket (%u)\n",
        ProgName, ticketSize, sizeof(ESTicket));
    }

    memcpy(&(partition.ticket), ticket, sizeof(ESTicket));
    free(ticket);

    /* Read TMD */
    if (readFileIntoArray(tmdName, &tmd, &(partition.tmdSize)) == false) {
        return(false);
    }

    if (readCertBlob(&certBlob, &(partition.certBlobSize)) == false) {
        return(false);
    }
    fileOffset = ftell(outFile);

    partitionStart = alignOffset(fileOffset, PARTITION_ALIGN);

    tmdStart = partitionStart + sizeof(partition_t);
    tmdStart = alignOffset(tmdStart, ITEM_ALIGN);
    certBlobStart = alignOffset(tmdStart + partition.tmdSize, ITEM_ALIGN);
    h3HashStart = certBlobStart + partition.certBlobSize;
    h3HashStart = alignOffset(h3HashStart, H3_ALIGN);
    cryptAreaStart = alignOffset(h3HashStart + H3_SIZE, ENCRYPT_ALIGN);

    partition.tmdOffset           = DISK_ADDR(tmdStart - partitionStart);
    partition.certBlobOffset      = DISK_ADDR(certBlobStart - partitionStart);
    partition.h3HashesOffset      = DISK_ADDR(h3HashStart - partitionStart);
    partition.encryptedAreaOffset = DISK_ADDR(cryptAreaStart - partitionStart);

    partitionOnDisk = partition;
    partitionOnDisk.tmdSize      = htonl(partition.tmdSize);
    partitionOnDisk.certBlobSize = htonl(partition.certBlobSize);
    /*
     * Write out the game partition structure, which includes
     * the eTicket
     */
    if (fseeko(outFile, partitionStart, SEEK_SET) == -1) {
        perror("fseeko");
        return(false);
    }
    if (fwrite(&partitionOnDisk, sizeof(partition_t), 1, outFile) != 1) {
        fprintf(stderr, "Partition struct write failed\n");
        return(false);
    }

    /* Write out TMD structure */
    if (fseeko(outFile, tmdStart, SEEK_SET) == -1) {
        perror("fseeko");
        return(false);
    }
    if (fwrite(tmd, 1, partition.tmdSize, outFile) != partition.tmdSize) {
        fprintf(stderr, "Partition TMD write failed\n");
        return(false);
    }

    /* Write out certificates */
    if (fseeko(outFile, certBlobStart, SEEK_SET) == -1) {
        perror("fseeko");
        return(false);
    }
    if (fwrite(certBlob, partition.certBlobSize, 1, outFile) != 1) {
        fprintf(stderr, "Partition certificates write failed\n");
        return(false);
    }

    /* Write out H3 Hashes */
    if (fseeko(outFile, h3HashStart, SEEK_SET) == -1) {
        perror("fseeko");
        return(false);
    }
    if (copyFileToOutFile(outFile, h3HashName) == false) {
        return(false);
    }

    /* Write out content */
    if (fseeko(outFile, cryptAreaStart, SEEK_SET) == -1) {
        perror("fseeko");
        return(false);
    }
    if (copyFileToOutFile(outFile, encryptedContentName) == false) {
        return(false);
    }
    free(tmd);
    free(certBlob);
    return(true);
} // writeGames

/* ------------------------------------------------------------------------ */
