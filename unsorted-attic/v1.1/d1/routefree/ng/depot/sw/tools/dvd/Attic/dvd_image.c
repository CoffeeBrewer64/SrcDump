d1 1
a1 1
#ident "$Id$"
d16 14
d36 1
d43 1
d45 1
d72 4
a75 1
bool computeSuperBlock(FILE *inFile, FILE *outFile, uint8_t *h3Ptr);
d87 1
d110 3
d126 2
a127 1
    while (computeSuperBlock(inFile, outFile, h3BufPtr) == true) {
d156 3
a158 1
computeSuperBlock(FILE *inFile, FILE *outFile, uint8_t* h3Ptr)
d170 5
d236 3
d250 3
d254 1
a254 6
        numWritten = fwrite(h0Ptr, SHA1_DIGESTSIZE, H0_PER_H1, outFile);
        if (numWritten != H0_PER_H1) {
            fprintf (stderr, "Error: write failed (%d out of %d written) - exit\n",
                     numWritten, H0_PER_H1);
            exit(1);
        }
d256 1
d258 2
a259 6
        for (int n_words = 0; n_words < H0_PAD_WORDS; n_words++) {
            if (fwrite(&pad_word, sizeof(uint32_t), 1, outFile) != 1) {
                fprintf (stderr, "Error: write of pad word failed - exit\n");
                exit(1);
            }
        }
d262 2
a263 6
        numWritten = fwrite(h1Ptr, SHA1_DIGESTSIZE, H1_PER_H2, outFile);
        if (numWritten != H1_PER_H2) {
            fprintf (stderr, "Error: write failed (%d out of %d written) - exit\n",
                     numWritten, H0_PER_H1);
            exit(1);
        }
d269 2
a270 6
        for (int n_words = 0; n_words < H1_PAD_WORDS; n_words++) {
            if (fwrite(&pad_word, sizeof(uint32_t), 1, outFile) != 1) {
                fprintf (stderr, "Error: write of pad word failed - exit\n");
                exit(1);
            }
        }
d273 24
a296 2
        numWritten = fwrite(h2Digest, SHA1_DIGESTSIZE, H2_PER_SUPERBLOCK, outFile);
        if (numWritten != H2_PER_SUPERBLOCK) {
d298 1
a298 1
                     numWritten, H2_PER_SUPERBLOCK);
d302 2
a303 12
        for (int n_words = 0; n_words < H2_PAD_WORDS; n_words++) {
            if (fwrite(&pad_word, sizeof(uint32_t), 1, outFile) != 1) {
                fprintf (stderr, "Error: write of pad word failed - exit\n");
                exit(1);
            }
        }

        assert(ftell(outFile) - blockStartPos == SUBBLOCK_SIZE);

        /* Write Data */
        numWritten = fwrite(readPtr, 1, DVD_DATA_BYTES_PER_BLOCK, outFile);
        if (numWritten != DVD_DATA_BYTES_PER_BLOCK) {
d305 1
a305 1
                     numWritten, DVD_DATA_BYTES_PER_BLOCK);
a307 1
        readPtr += DVD_DATA_BYTES_PER_BLOCK;
