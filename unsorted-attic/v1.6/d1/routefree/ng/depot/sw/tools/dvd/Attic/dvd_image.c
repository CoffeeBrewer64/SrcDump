d1 1
a1 1
#ident "$Id: dvd_image.c,v 1.5 2005/12/23 21:51:02 craig Exp $"
a93 1
    printf ("Bytes per superblock: %d\n", DVD_DATA_BYTES_PER_SUPERBLOCK);
d253 1
a253 1
    outStartPos = ftell(outFile);
d259 1
a259 1
        blockStartPos = ftell(outFile);
d334 1
a334 1
        assert(ftell(outFile) - blockStartPos == DVD_BLOCK_SIZE);
