d1 1
a1 1
#ident "$Id: dvd_image.c,v 1.3 2005/12/12 23:26:53 craig Exp $"
d68 6
a74 1
                       uint8_t* const hashIv, uint8_t* const dataIv,
d94 1
d128 2
a129 2
    while (computeSuperBlock(inFile, outFile, h3BufPtr, hashIv,
                             dataIv, TitleKey, false) == true) {
a164 1
                  uint8_t* const hashIv, uint8_t* const dataIv,
a175 1
    uint8_t     oldHashIv[16];
d179 6
d188 1
d259 1
a289 2
        memcpy(oldHashIv, hashIv, 16);

d292 2
a300 4
        /* Put the old IV into the hash block */
        memcpy(hashSubBlock + HASH_IV_OFFSET, oldHashIv, 16);
        memcpy(hashSubBlock + DATA_IV_OFFSET, dataIv, 16);

d303 10
