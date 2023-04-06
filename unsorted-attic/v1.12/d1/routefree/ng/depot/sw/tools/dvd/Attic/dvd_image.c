#ident "$Id: dvd_image.c,v 1.11 2006/02/14 19:32:36 craig Exp $"
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
 * Program to generate RVL secure DVD images.  See the Powerpoint
 * presentation on the Web for details.
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

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

#include "aes.h"
#include "sha1.h"
#include "key.h"
#include "image_superblock.h"

#ifdef __CYGWIN__
#define fopen64(name, mode)     _fopen64(name,mode)
#define ftello64(stream)        _ftello64(stream)
#endif

void
usage(const char* const prog_name)
{
    printf ("Usage: %s file_name\n", prog_name);
}


int
main(int argc, char *argv[])
{
    char        outFileName[256];
    FILE        *outFile, *inFile;
    struct stat statBuf;
    int         numDvdSuperblocks;
    char        *h3Buf, *h3BufPtr;
    int         h3Bytes;
    size_t      numWritten;

    if (argc != 2) {
        usage(argv[0]);
        exit(1);
    }

    sprintf (outFileName, "%s.%s", argv[1], "img");

    if ((inFile = fopen64(argv[1], "r")) == NULL) {
        printf ("Error: can't open %s for reading - exit\n", argv[1]);
        exit(1);
    }
    if ((outFile = fopen(outFileName, "w")) == NULL) {
        printf ("Error: can't open %s for writing - exit\n", argv[1]);
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
                             TitleKey, true, true) == true) {
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
}
