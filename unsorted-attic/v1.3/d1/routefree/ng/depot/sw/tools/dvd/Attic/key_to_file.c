#ident "$Id: key_to_file.c,v 1.2 2006/04/14 01:30:38 craig Exp $"
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
 * Encrypt or decrypt a file using AES.
 * The encryption key comes from a file.
 * The initial vector is all zeros.  This is designed to match what
 * the tmd program expects as input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    uint8_t  titleKey[] = {0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xee,
                           0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef};
    FILE        *key_file;
    size_t      bytes_written;

    if (argc != 2) {
        printf ("Usage: %s output_file\n", argv[0]);
        exit(1);
    }
    if ( (key_file = fopen(argv[1], "w")) == NULL) {
        fprintf (stderr, "Can't open ouput file '%s' - exit\n", argv[1]);
        exit(1);
    }

    bytes_written = fwrite(titleKey, 1, sizeof(titleKey), key_file);
    fclose(key_file);

    if (bytes_written != sizeof(titleKey)) {
        printf("%s: Write failed - exit\n", argv[0]);
        unlink(argv[1]);
        exit(1);
    }
} // main
