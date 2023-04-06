#ident "$Id: gen_h3_hash.c,v 1.1 2006/04/01 00:46:51 craig Exp $"
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

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "aes.h"
#include "sha1.h"
#include "image_superblock.h"

/* ------------------------------------------------------------------------ */
void
usage(const char* const progName)
{
    printf ("Usage: %s input_content_name\n", progName);
}

/* ------------------------------------------------------------------------ */

int
main(int argc, char *argv[])
{
    FILE        *inFile, *outFile;
    uint8_t     h3Buf[BLOCKS_FOR_H3 * DVD_BLOCK_SIZE], *h3Ptr;
    uint8_t     titleKey[AES_KEY_LENGTH], h4Hash[SHA1_DIGESTSIZE];
    char        fileNameBuf[512];
    SHA1Context context;


    if (argc != 2) {
        usage(argv[0]);
        exit(1);
    }
    if ( (inFile = fopen(argv[1], "r")) == NULL) {
        fprintf (stderr, "%s: Can't open file '%s' - exit\n", argv[0], argv[1]);
        exit(1);
    }

    if ( (outFile = fopen("/dev/null", "w")) == NULL) {
        fprintf (stderr, "%s: Can't open /dev/null - exit\n", argv[0]);
        exit(1);
    }

    memset(titleKey, 0, AES_KEY_LENGTH);
    memset(h3Buf, 0, BLOCKS_FOR_H3 * DVD_BLOCK_SIZE);
    h3Ptr = h3Buf;

    while (computeSuperBlock(inFile, outFile, h3Ptr,
                             titleKey, false, true) == true) {
        h3Ptr += SHA1_DIGESTSIZE;
    }
    fclose(inFile);
    

    sprintf(fileNameBuf, "%s.h3_hash", argv[1]);

    if ( (outFile = fopen(fileNameBuf, "w")) == NULL) {
        fprintf (stderr, "%s: Can't open '%s' - exit\n", argv[0], fileNameBuf);
        exit(1);
    }
    if (fwrite(h3Buf, BLOCKS_FOR_H3 * DVD_BLOCK_SIZE, 1, outFile) != 1) {
        fprintf (stderr, "%s: Writing to '%s' failed - exit\n",
                 argv[0], fileNameBuf);
        fclose(outFile);
        unlink(fileNameBuf);
    }
    fclose(outFile);

    sprintf(fileNameBuf, "%s.h4_hash", argv[1]);
    if ( (outFile = fopen(fileNameBuf, "w")) == NULL) {
        fprintf (stderr, "%s: Can't open '%s' - exit\n", argv[0], fileNameBuf);
        exit(1);
    }

    SHA1Reset(&context);
    SHA1Input(&context, h3Buf, BLOCKS_FOR_H3 * DVD_BLOCK_SIZE);
    SHA1Result(&context, h4Hash);

    if (fwrite(h4Hash, SHA1_DIGESTSIZE, 1, outFile) != 1) {
        fprintf (stderr, "%s: Writing to '%s' failed - exit\n",
                 argv[0], fileNameBuf);
        fclose(outFile);
        unlink(fileNameBuf);
    }
    fclose(outFile);
    exit(0);
} // main

/* ------------------------------------------------------------------------ */
