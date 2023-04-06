d1 1
a1 1
#ident "$Id: dvd_image.c,v 1.1 2005/11/10 21:37:40 craig Exp $"
d282 2
a283 2
        aes_SwEncrypt(titleKey, hashIv, hashSubBlock, SUBBLOCK_SIZE,
                      encryptedSubBlock);
d290 2
a291 2
        aes_SwEncrypt(titleKey, dataIv, readPtr, 31 * SUBBLOCK_SIZE,
                      encryptedDataBlock);
