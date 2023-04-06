d1 1
a1 1
#ident "$Id: dvd_image.c,v 1.2 2005/12/03 04:02:08 craig Exp $"
d18 1
a18 2
 * 16 bytes of current hash IV
 * 4 bytes of padding 
d21 1
a21 2
 * 16 bytes of current data IV
 * 16 bytes of padding
d64 3
a66 5
#define H0_PAD_WORDS                    5
#define H1_PAD_WORDS                    8
#define H2_PAD_WORDS                    8
#define PAD_WORD_CONST                  0xdeadbeef

d70 1
a70 1
                       uint8_t* const titleKey);
d123 1
a123 1
                             dataIv, TitleKey) == true) {
d146 7
a152 1
 * all the DVD blocks which share the same H2 hash.
d160 1
a160 1
                  uint8_t* const titleKey)
a169 1
    uint32_t    pad_word;
a239 1
    /* Now write the output file */
a242 1
    pad_word = PAD_WORD_CONST;
d257 2
a258 2
        memset(hashSubBlockPtr, 0, H0_PAD_WORDS);
        hashSubBlockPtr += H0_PAD_WORDS;
d268 2
a269 2
        memset(hashSubBlockPtr, 0, H1_PAD_WORDS);
        hashSubBlockPtr += H1_PAD_WORDS;
d275 2
a276 2
        memset(hashSubBlockPtr, 0, H2_PAD_WORDS);
        hashSubBlockPtr += H2_PAD_WORDS;
d280 8
a287 3
        /* Encrypt the hashes */
        aes_SwEncryptWrapper(titleKey, hashIv, hashSubBlock, SUBBLOCK_SIZE,
                             encryptedSubBlock);
d294 7
a300 2
        aes_SwEncryptWrapper(titleKey, dataIv, readPtr, 31 * SUBBLOCK_SIZE,
                             encryptedDataBlock);
