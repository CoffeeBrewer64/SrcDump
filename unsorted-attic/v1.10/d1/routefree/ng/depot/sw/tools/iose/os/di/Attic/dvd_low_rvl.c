d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.9 2006/01/21 02:52:23 craig Exp $"
d31 1
d33 1
a57 2
static bool     h3HashesRead = false;

d76 1
a76 1
static blockCache_t         globalBlockCache = {false};
d78 1
a78 1
diskInfo_t      diskInfo;
d80 1
a80 1
uint32_t doDiskRead(uint8_t* const destAddr, const uint32_t length,
d83 6
d99 4
a102 2
    h3HashesRead             = false;
    globalBlockCache.isValid = false;
a127 3
 * Input: dest is destination for data
          blockNum is the physical block number to read
 *        len is the length to read
a129 1

d135 1
a135 1
    returnVal = doDiskRead(destAddr, MAX_H3_HASH_SIZE, wordOffset);
d147 7
d167 4
d172 2
a173 2
 *           true if the hashes verify
 *           false if the they don't or some other error occurs.
d250 3
a252 4
#define DECRYPT 1

uint32_t
doBlockRead(uint8_t *destAddr, const uint32_t physBlockNum) 
a259 1
#ifdef DECRYPT
a260 1
#endif
d270 2
a271 2
    readReturn = doDiskRead(readBuffer, BYTES_PER_BLOCK,
                            diskInfo.dataWordOffset +
d282 13
a294 7
#ifdef DECRYPT
    memset(hashIv, 0, 16);
    /*
     * FIXME - if the Crypto API returns the right Iv for
     * the data after decrypting the hashes, skip this memcpy call
     */
    memcpy(dataIv, readBuffer + 1024 - 32 - 16, 16);
d296 2
a297 5
    printf ("Encrypt Hash bytes: ");
    for (int i = 0; i < 16; i++) {
        printf ("0x%x ", readBuffer[i]);
    }
    printf ("\n");
d299 5
a303 2
    aes_SwDecryptWrapper(TitleKey, hashIv, readBuffer,
                         1024 - H2_PAD_LENGTH, readBuffer);
d305 17
a321 3
    printf ("Decrypt Hash bytes: ");
    for (int i = 0; i < 16; i++) {
        printf ("0x%x ", readBuffer[i]);
a322 19
    printf ("\n");

    printf ("decryptIv: 0x%x 0x%x 0x%x 0x%x\n",
             * (uint32_t *) dataIv,
             * (uint32_t *) (dataIv + 4),
             * (uint32_t *) (dataIv + 8),
             * (uint32_t *) (dataIv + 12));
    printf ("TitleKey: 0x%x 0x%x 0x%x 0x%x\n",
             * (uint32_t *) TitleKey,
             * (uint32_t *) (TitleKey + 4),
             * (uint32_t *) (TitleKey + 8),
             * (uint32_t *) (TitleKey + 12));
    aes_SwDecryptWrapper(TitleKey, dataIv,
                         readBuffer + BYTES_PER_SUBBLOCK,
                         DATA_BYTES_PER_BLOCK, destAddr);
#else
    memcpy(destAddr, readBuffer + BYTES_PER_SUBBLOCK,
           31 * BYTES_PER_SUBBLOCK);
#endif
d330 38
a367 12
    /* Verify the data against the H0 Hashes */
    dataPtr = destAddr;
    hashValuePtr = readBuffer;
    for (int i = 0; i < DATA_SUBBLOCKS_PER_BLOCK; i++) {
        IOS_GenerateHash(&hashContext, dataPtr,
                          BYTES_PER_SUBBLOCK, SHA1_HASH_START,
                          NULL, (IOSMessageQueueId) NULL, ignoredMessage);
        IOS_GenerateHash(&hashContext, NULL,
                          0, SHA1_HASH_END, &hashResult,
                          (IOSMessageQueueId) NULL, ignoredMessage);
        if (memcmp(hashResult, hashValuePtr, HASH_LENGTH) != 0) {
            printf ("Data failed to verify against H0 Hash\n");
a369 3
        dataPtr += BYTES_PER_SUBBLOCK;
        hashValuePtr += HASH_LENGTH;
    }
d371 6
a376 25
    /* Verify the H0 Hashes against the correct H1 */
    printf ("*** DBR: 2 ***\n");
    hashValuePtr =    readBuffer
                    + H1_HASH_OFFSET
                    + ((physBlockNum % 8) * HASH_LENGTH);
    if (verifyHashArray(readBuffer, H0_HASH_LENGTH, hashValuePtr) == false) {
        printf ("H0 Hashes failed to verify\n");
        return(DI_ERR_HASH);
    }

    /* Verify the H1 hashes against the correct H2 */
    hashValuePtr =   readBuffer
               + H2_HASH_OFFSET
               + (blockNumToH2Index(physBlockNum) * HASH_LENGTH);
    if (verifyHashArray(readBuffer + H1_HASH_OFFSET, H1_HASH_LENGTH,
                        hashValuePtr) == false) {
        printf ("H1 Hashes failed to verify\n");
        return(DI_ERR_HASH);
    }

    /* Verify the H2 hashes against the correct H3 */
    if (verifyHashArray(readBuffer + H2_HASH_OFFSET, H2_HASH_LENGTH,
                        blockNumToH3Ptr(physBlockNum)) == false){
        printf ("H2 Hashes failed to verify\n");
        return(DI_ERR_HASH);
d388 3
a390 2
uint32_t
fillBlockCache(blockCache_t* const blockCache, const uint32_t physBlockNum) 
d394 2
a395 1
    returnVal = doBlockRead(blockCache->data, physBlockNum);
d424 1
a424 1
bool
d454 16
d477 1
a477 1
    if (h3HashesRead == false) {
d479 1
d486 13
a499 1
        h3HashesRead = true;
d503 4
d513 2
a514 1
                                       startPosition.physBlockNum);
d531 2
a532 1
        returnVal = doBlockRead(destAddr, startPosition.physBlockNum);
d543 2
a544 1
     * Finally, do the partial block at the end
d554 2
a555 1
                                       startPosition.physBlockNum);
d567 89
a655 1
/*************************************************************/
d657 28
