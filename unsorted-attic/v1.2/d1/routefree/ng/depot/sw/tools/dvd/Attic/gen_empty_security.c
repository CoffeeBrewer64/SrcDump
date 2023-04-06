#ident "$Id: gen_empty_security.c,v 1.1 2006/04/08 00:54:38 craig Exp $"
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
 * Program comments here
 * 
 */

#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>             // for memset
#include <sys/types.h>          // for off_t definition
#include <unistd.h>

#include "types.h"
#include "estypes.h"
#include "disk_format.h"

#ifdef __CYGWIN__
#undef __STRICT_ANSI__
#else
#define fseeko(file, where, whence)     fseeko64(file, where, whence)
#define ftello(file)                    ftello64(file)
#endif

static char     *ProgName;
static bool     Verbose = true;

bool generateEmpty(const char* const outputName, const int secureAreaSize);
gameTOC_t * writeEmptyGamePartition(FILE *outFile, const int secureAreaSize);

/* ------------------------------------------------------------------------ */
int main(int argc, char *argv[])
{
    ProgName = argv[0];

    generateEmpty("rvl.bin.empty", 2 * 1024 * 1024);
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
generateEmpty(const char* const outputName, const int emptySize)
{
    FILE        *outFile;
    off_t       globalTocOff, updateTocOff, gameTocOff;
    off_t       updatePartPtrArrayOff, gamePartPtrArrayOff;
    off_t       updateOff;
    gameTOC_t   *gameToc;
    updateTOC_t updateTOC;
    globalTOC_t globalToc;
    uint8_t     *zeroArray;

    if ((outFile = fopen(outputName, "w")) == NULL) {
        fprintf (stderr, "(%s) Error - can't open file %s for writing\n",
                 ProgName, outputName);
        return(false);
    }
    size_t numWritten;

    zeroArray = malloc(emptySize);
    if (zeroArray == NULL) {
        printf ("%s: malloc returned NULL\n", ProgName);
        exit(1);
    }
    memset(zeroArray, 0, emptySize);

    numWritten = fwrite(zeroArray, emptySize, 1, outFile);
    free(zeroArray);

    if (numWritten != 1) {
        if (feof(outFile)) {
            printf ("EOF on output\n");
        }
        else if (ferror(outFile)) {
            printf ("File error on output\n");
        }
        fprintf(stderr, "Error writing pad bytes\n");
        goto handleError;
    }
    fseeko(outFile, 0, SEEK_SET);

    /*
     * Calculate the places that the tables of contents
     * and associated arrays of pointers to partitions will go
     */
    globalTocOff = SECURITY_OFFSET;
    updateTocOff = alignOffset(globalTocOff + sizeof(globalTOC_t),
                               ITEM_ALIGN);
    updatePartPtrArrayOff = alignOffset(updateTocOff + sizeof(updateTOC_t),
                                        ITEM_ALIGN);
    gameTocOff =   updatePartPtrArrayOff;
                 
    gameTocOff = alignOffset(gameTocOff, ITEM_ALIGN);
    gamePartPtrArrayOff = alignOffset(gameTocOff + sizeof(gameTOC_t),
                                      ITEM_ALIGN);

    updateOff = gamePartPtrArrayOff + sizeof(gamePartition_t *);
    updateOff = alignOffset(updateOff, UPDATE_AREA_ALIGN);

    /*
     * Calculate and write global TOC
     */
    globalToc.updateTOC = (updateTOC_t *) DISK_ADDR(updateTocOff);
    globalToc.gameTOC   = (gameTOC_t *) DISK_ADDR(gameTocOff);

    if (fseeko(outFile, globalTocOff - SECURITY_OFFSET, SEEK_SET) == -1) {
        perror("fseeko");
        goto handleError;
    }
    if (fwrite(&globalToc, sizeof(globalTOC_t), 1, outFile) != 1) {
        fprintf(stderr, "Error writing global TOC\n");
        goto handleError;
    }


    updateTOC.numUpdatePartitions = 0;
    updateTOC.updatePartitions = 0;

    if (fseeko(outFile, updateOff - SECURITY_OFFSET, SEEK_SET) == -1) {
        perror("fseeko");
        goto handleError;
    }
    if (fwrite(&updateTOC, sizeof(updateTOC), 1, outFile) != 1) {
        fprintf(stderr, "Error writing update TOC\n");
        goto handleError;
    }

    /*
     * Write the actual game partitions.
     * This must be done before writing the game table of contents
     * because in writing the game partitions, we determine where
     * each partition starts
     */
    gameToc = writeEmptyGamePartition(outFile, emptySize);
    if (gameToc == NULL) {
        goto handleError;
    }

    /* Write the game table of contents and pointers to partitons */
    gameTOC_t         gameTocDisk;

    gameTocDisk.numGamePartitions = htonl(gameToc->numGamePartitions);
    gameTocDisk.gamePartitions =
                        (gamePartition_t **) DISK_ADDR(gamePartPtrArrayOff);

    if (fseeko(outFile, gameTocOff - SECURITY_OFFSET, SEEK_SET) == -1) {
        perror("fseeko");
        goto handleError;
    }
    if (fwrite(&gameTocDisk, sizeof(gameTOC_t), 1, outFile) != 1) {
        fprintf(stderr, "Error writing game TOC\n");
        goto handleError;
    }

    if (fseeko(outFile, gamePartPtrArrayOff - SECURITY_OFFSET,
               SEEK_SET) == -1) {
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

/* ----------------------------------------------------------------------- */

/*
 */

gameTOC_t *
writeEmptyGamePartition(FILE *outFile, const int secureAreaSize)
{
    gamePartition_t     gamePart;
    gameTOC_t           *returnVal;
    off_t               fileOffset, partitionStart;

    returnVal = (gameTOC_t *) malloc (sizeof (gameTOC_t));
    if (returnVal == NULL) {
        printf ("Memory allocation error\n");
        exit(1);
    }
    returnVal->numGamePartitions = 1;
    returnVal->gamePartitions = (gamePartition_t **)
                                 malloc (sizeof(gamePartition_t *));

    gamePart.tmdSize            = 0;
    gamePart.tmd                = 0;
    gamePart.certBlobSize       = 0;
    gamePart.certBlob           = 0;
    gamePart.h3Hashes           = 0;
    gamePart.encryptedArea      = (uint8_t *) DISK_ADDR(GLOBAL_TOC_OFFSET
                                                        + secureAreaSize);


    /* Determine at which offset each of the items will live */
    fileOffset = ftello(outFile) + SECURITY_OFFSET;
    partitionStart = alignOffset(fileOffset, GAME_PARTITION_ALIGN);
    if (Verbose) {
        printf ("Game partition #%d starts at 0x%llx.\n",
                 0, partitionStart);
    }
    returnVal->gamePartitions[0] =
                            (gamePartition_t *) DISK_ADDR(partitionStart);


    /*
     * Write out the game partition structure, which includes
     * the eTicket
     */
    if (fseeko(outFile, partitionStart - SECURITY_OFFSET, SEEK_SET) == -1) {
        perror("fseeko");
        return(NULL);
    }
    if (fwrite(&gamePart, sizeof(gamePartition_t), 1, outFile) != 1) {
        fprintf(stderr, "Game partition struct write failed\n");
        return(NULL);
    }
    return(returnVal);
} // writeGames

/* ----------------------------------------------------------------------- */
