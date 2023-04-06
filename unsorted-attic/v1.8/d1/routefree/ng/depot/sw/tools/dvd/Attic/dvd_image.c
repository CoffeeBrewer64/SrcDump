d1 1
a1 1
#ident "$Id: dvd_image.c,v 1.7 2006/01/12 00:52:53 craig Exp $"
d16 1
a16 1
 * Format of disc block:
d44 1
a51 22
/* A superblock consists of all DVD blocks that have the same H2 hash */
#define BLOCKS_FOR_H3                   3
#define DATA_PER_H0                     1024
#define H0_PER_H1                       31
#define H1_PER_H2                       8
#define H0_PER_SUPERBLOCK               (H0_PER_H1 * H1_PER_H2 * H2_PER_SUPERBLOCK)
#define H1_PER_SUPERBLOCK               (H1_PER_H2 * H2_PER_SUPERBLOCK)
#define H2_PER_SUPERBLOCK               8
#define SUBBLOCK_SIZE                   1024
#define DVD_BLOCK_SIZE                  (32 * 1024)
#define DVD_DATA_BYTES_PER_BLOCK        (31 * 1024)
#define BLOCKS_PER_SUPERBLOCK           64
#define DVD_DATA_BYTES_PER_SUPERBLOCK        (DVD_DATA_BYTES_PER_BLOCK * BLOCKS_PER_SUPERBLOCK)
#define H0_PAD_BYTES                    20
#define H1_PAD_BYTES                    32
#define H2_PAD_BYTES                    8

/*
 * Offset to the last 16 bytes of the H2 hash in the hash subblock
 * H0 size (w/pad) + H1 size (w/pad) + H2 size (no pad) - the 16
 */
#define DVD_DATA_IV_OFFSET (640 + 192 + 160 - 16)
a66 1
    uint8_t     dataIv[16], hashIv[16];
a88 3
    memcpy(dataIv, TitleIv, 16);
    memcpy(hashIv, TitleIv, 16);

d112 3
a125 192

/*
 * Generate a super block to the output file.  A super block consists of
 * all the DVD blocks which share the same H2 hashes which are present
 * in the hash subblock.
 * The size of the superblock is:
 * 1 H1 hash per data block
 * 8 H1 hashes per H2 hash -> 8 data blocks per H2 hash
 * 8 H2 hashes in each hash subblock -> 64 data blocks
 * -> 64 * 31 * 1024 data bytes per superblock
 * Return: true if more data is present in the image,
 *         false otherwise.
 */

bool
computeSuperBlock(FILE *inFile, FILE *outFile, uint8_t* h3Ptr,
                  uint8_t* const titleKey, const bool encrypt)
{
    SHA1Context context;
    uint8_t     readBuf[DVD_DATA_BYTES_PER_SUPERBLOCK];
    size_t      numRead;
    bool        notEof = true;   
    uint8_t     h0Digests[H0_PER_SUPERBLOCK * SHA1_DIGESTSIZE];
    uint8_t     h1Digests[H1_PER_H2 * H2_PER_SUPERBLOCK * SHA1_DIGESTSIZE];
    uint8_t     h2Digest[H2_PER_SUPERBLOCK * SHA1_DIGESTSIZE];
    uint8_t     *readPtr, *h0Ptr, *h1Ptr, *h2Ptr;
    off_t       outStartPos, blockStartPos;
    uint8_t     hashSubBlock[SUBBLOCK_SIZE], *hashSubBlockPtr;
    uint8_t     encryptedSubBlock[SUBBLOCK_SIZE];
    uint8_t     encryptedDataBlock[31 * SUBBLOCK_SIZE];
    uint8_t     dataIv[16], hashIv[16];
    /*
    static int  timesCalled = -1;
    */




    numRead = fread(readBuf, 1, DVD_DATA_BYTES_PER_SUPERBLOCK, inFile);
    /* printf ("Num read: %d\n", numRead); */
    if (numRead != DVD_DATA_BYTES_PER_SUPERBLOCK) {
        if (numRead == 0 && feof(inFile)) {
            return(false);
        } else if (numRead == 0 && ferror(inFile)) {
            printf ("Error when reading input file - exiting\n");
            exit(1);
        }
        else {
            /* 
             * The file size is not an exact multiple of the number
             * of data bytes per superblock.  Zero out the bytes
             * that would have been read had the file size been
             * an exact multiple
             */
            bzero(readBuf + numRead, DVD_DATA_BYTES_PER_SUPERBLOCK - numRead);
        }
    }

    notEof = (feof(inFile) == 0) ? true : false;

    h0Ptr = h0Digests;
    readPtr = readBuf;

    /* Generate all the H0 digests needed for H1 and H2 */
    for (int subblock = 0; subblock < H0_PER_SUPERBLOCK; subblock++) {
        SHA1Reset(&context);
        SHA1Input(&context, readPtr, SUBBLOCK_SIZE);
        SHA1Result(&context, h0Ptr);
        readPtr += SUBBLOCK_SIZE;
        h0Ptr   += SHA1_DIGESTSIZE;
    }

    /* Generate the H1 digests */
    h0Ptr = h0Digests;
    h1Ptr = h1Digests;
    for (int h1_count = 0; h1_count < H1_PER_SUPERBLOCK; h1_count++) {
        SHA1Reset(&context);
        SHA1Input(&context, h0Ptr, H0_PER_H1 * SHA1_DIGESTSIZE);
        SHA1Result(&context, h1Ptr);
        h0Ptr += H0_PER_H1 * SHA1_DIGESTSIZE;
        h1Ptr += SHA1_DIGESTSIZE;
    }

    /* Generate the H2 digest */
    h1Ptr = h1Digests;
    h2Ptr = h2Digest;
    for (int i = 0; i < H2_PER_SUPERBLOCK; i++) {
        SHA1Reset(&context);
        SHA1Input(&context, h1Ptr, H1_PER_H2 * SHA1_DIGESTSIZE);
        SHA1Result(&context, h2Ptr);
        h1Ptr += H1_PER_H2 * SHA1_DIGESTSIZE;
        h2Ptr += SHA1_DIGESTSIZE;
    }
    /* Generate the H3 digest */
    SHA1Reset(&context);
    SHA1Input(&context, h2Digest, H2_PER_SUPERBLOCK * SHA1_DIGESTSIZE);
    SHA1Result(&context, h3Ptr);




    h0Ptr = h0Digests;
    h1Ptr = h1Digests;
    readPtr = readBuf;
    outStartPos = ftello(outFile);

    for (int block = 0; block < BLOCKS_PER_SUPERBLOCK; block++) {
        size_t  numWritten;

        /* timesCalled++; */
        blockStartPos = ftello(outFile);

        hashSubBlockPtr = hashSubBlock;

        /* Write H0's */
        memcpy(hashSubBlockPtr, h0Ptr, SHA1_DIGESTSIZE * H0_PER_H1);
        h0Ptr += SHA1_DIGESTSIZE * H0_PER_H1;
        hashSubBlockPtr += SHA1_DIGESTSIZE * H0_PER_H1;

        memset(hashSubBlockPtr, 0, H0_PAD_BYTES);
        hashSubBlockPtr += H0_PAD_BYTES;

        /* Write H1's */
        memcpy(hashSubBlockPtr, h1Ptr, SHA1_DIGESTSIZE * H1_PER_H2);
        hashSubBlockPtr += SHA1_DIGESTSIZE * H1_PER_H2;

        if ((block + 1) % H1_PER_H2 == 0) {
            h1Ptr += SHA1_DIGESTSIZE * H1_PER_H2;
        }

        memset(hashSubBlockPtr, 0, H1_PAD_BYTES);
        hashSubBlockPtr += H1_PAD_BYTES;

        /* Write H2 */
        memcpy(hashSubBlockPtr, h2Digest, SHA1_DIGESTSIZE * H2_PER_SUPERBLOCK);
        hashSubBlockPtr += SHA1_DIGESTSIZE * H2_PER_SUPERBLOCK;

        memset(hashSubBlockPtr, 0, H2_PAD_BYTES);
        hashSubBlockPtr += H2_PAD_BYTES;

        if (encrypt) {
            /* Encrypt the hashes */
            /* The hashIv is always 0 */
            memset(hashIv, 0, 16);
            aes_SwEncryptWrapper(titleKey, hashIv, hashSubBlock, SUBBLOCK_SIZE,
                                 encryptedSubBlock);
        }
        else {
            memcpy(encryptedSubBlock, hashSubBlock, SUBBLOCK_SIZE);
        }

        /* Encrypt the data */
        if (encrypt) {
            memcpy(dataIv, encryptedSubBlock + DVD_DATA_IV_OFFSET, 16);
            /*
            printf ("(%d) dataIv: 0x%x 0x%x 0x%x 0x%x\n",
             timesCalled,
             * (uint32_t *) dataIv,
             * (uint32_t *) (dataIv + 4),
             * (uint32_t *) (dataIv + 8),
             * (uint32_t *) (dataIv + 12));
             */

            aes_SwEncryptWrapper(titleKey, dataIv, readPtr, 31 * SUBBLOCK_SIZE,
                                 encryptedDataBlock);
        }
        else {
            memcpy(encryptedDataBlock, readPtr, 31 * SUBBLOCK_SIZE);
        }
        readPtr += DVD_DATA_BYTES_PER_BLOCK;

        /* Write Data */
        numWritten = fwrite(encryptedSubBlock, 1, SUBBLOCK_SIZE, outFile);
        if (numWritten != SUBBLOCK_SIZE) {
            fprintf (stderr, "Error: write failed (%d out of %d written) - exit\n",
                     numWritten, SUBBLOCK_SIZE);
            exit(1);
        }

        numWritten = fwrite(encryptedDataBlock, 1, SUBBLOCK_SIZE * 31, outFile);
        if (numWritten != SUBBLOCK_SIZE * 31) {
            fprintf (stderr, "Error: write failed (%d out of %d written) - exit\n",
                     numWritten, SUBBLOCK_SIZE * 31);
            exit(1);
        }
        // This assert fails on files > 2Gbytes in size, because
        // ftello is broken.
        // assert(ftello(outFile) - blockStartPos == DVD_BLOCK_SIZE);
    }
    
    return(notEof);
}
