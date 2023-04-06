d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.4 2006/01/10 20:40:59 craig Exp $"
d16 1
a16 1
 * of a DVD disk
d60 2
a61 2
    uint32_t    physBlockNum;
    uint32_t    physSubBlockNum;
d104 1
a104 1
                                        - (DATA_SUBBLOCKS_PER_BLOCK * diskPosition->physBlockNum);
d128 2
d146 2
d183 2
d191 2
d197 1
a197 2
                       must be >= 31K bytes in size
            startPosition - which blo
d199 3
a201 3
            verified.
            DI_ERR_HASH if there was a hash error.
            The actual read error if the data couldn't be read from disk.
