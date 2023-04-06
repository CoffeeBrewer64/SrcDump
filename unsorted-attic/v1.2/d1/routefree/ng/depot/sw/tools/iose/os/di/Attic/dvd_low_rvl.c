d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.1 2005/12/16 01:07:42 craig Exp $"
d15 2
a16 2
 * Program comments here
 * 
d26 2
d43 1
d51 2
a52 2
#define DATA_BYTES_PER_SUBBLOCK         1024
#define DATA_BYTES_PER_BLOCK            (DATA_SUBBLOCKS_PER_BLOCK * DATA_BYTES_PER_SUBBLOCK)
d111 1
a111 1
    diskPosition->physBlockOffset = (diskPosition->physSubBlockNum * DATA_BYTES_PER_SUBBLOCK)
d204 3
d216 1
d224 24
a247 4
    /* FIXME - decrypt hash info to readBuffer */
    /* FIXME - decrypt data to destAddr */
    memcpy(destAddr, readBuffer + DATA_BYTES_PER_SUBBLOCK,
           31 * DATA_BYTES_PER_SUBBLOCK);
d254 1
a254 1
                          DATA_BYTES_PER_SUBBLOCK, SHA1_HASH_START,
d262 1
a262 1
        dataPtr += DATA_BYTES_PER_SUBBLOCK;
