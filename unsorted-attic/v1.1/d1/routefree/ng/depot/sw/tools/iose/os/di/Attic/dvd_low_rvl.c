d1 1
a1 1
#ident "$Id$"
d19 1
d59 5
d67 6
d188 13
d202 1
a202 1
doBlockRead(uint8_t *destAddr, diskPosition_t *startPosition)
d213 1
a213 1
                            blockNumToWordOffset(startPosition->physBlockNum));
d242 1
a242 1
                    + ((startPosition->physBlockNum % 8) * HASH_LENGTH);
d250 1
a250 1
               + (blockNumToH2Index(startPosition->physBlockNum) * HASH_LENGTH);
d257 1
a257 1
                        blockNumToH3Ptr(startPosition->physBlockNum)) == false){
d264 62
a325 1
void
d328 3
a330 3
    static uint8_t      decryptedData[DATA_BYTES_PER_BLOCK];
    static uint32_t     decryptDataWordOffset;
    diskPosition_t      startPosition;
d338 13
a350 22
    /*
     * First, read data out of the cache if posssible
     */
    if (decryptDataValid && (virtWordOffset > decryptDataWordOffset)
                         && (virtWordOffset < (  decryptDataWordOffset
                                               + DATA_BYTES_PER_BLOCK))
        ) {
        uint32_t bytesInBuffer, bytesToTransfer, cacheOffset;

        bytesInBuffer = BYTES_PER_WORD * (  decryptDataWordOffset
                                          + DATA_WORDS_PER_BLOCK
                                          - virtWordOffset);
        bytesToTransfer = MIN(bytesInBuffer, byteLength);
        cacheOffset = (uint32_t) decryptedData
                      + (BYTES_PER_WORD * (virtWordOffset - decryptDataWordOffset));
        memcpy(destAddr, (void *) cacheOffset, bytesToTransfer); 
        if (bytesToTransfer == byteLength) {
            return;
        } else {
            byteLength -= bytesToTransfer;
            virtWordOffset += bytesToTransfer / 4;
            destAddr += bytesToTransfer;
d352 1
a352 4
    } else if (startPosition.physBlockOffset != 0) {
        /*
         * Handle partial block read that isn't in the cache
         */
d359 8
d372 15
