#ident "$Id: dvd_low_rvl.c,v 1.31 2006/03/31 00:14:27 craig Exp $"

/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

/*
 * These functions imlement reading and verifying the secure portion
 * of a DVD disk, otherwise known as the virtual disk image
 */

#ifdef RVL
#include "stdint.h"
#include "stdbool.h"
#include "hw.h"
#include "ioslibc.h"
#include "endian_macros.h"
#include "es.h"            // WARNING! defines ntohl as nothing - even on X86!
#else  // ! RVL
#include <assert.h>
#include <netinet/in.h>    // For ntohl() and its brothers
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#endif // ifdef RVL

#include <string.h>

#include "iostypes.h"
#include "aes.h"
#include "key.h"
#include "dvd_hw.h"
#include "dvd.h"
#include "dvd_driver.h"
#include "dvd_low_rvl.h"
#include "disk_format.h"
#include "crypto_stub.h"
#include "dvd_mem.h"
#include "debug.h"
#include "flush.i"

#define SHA1_HASH_START                 0
#define SHA1_HASH_CONTINUE              1
#define SHA1_HASH_END                   2

#define HASH_LENGTH                     20
#define H0_HASH_LENGTH                  (31 * HASH_LENGTH)
#define H1_HASH_OFFSET                  640
#define H1_HASH_LENGTH                  (8 * HASH_LENGTH)
#define H2_HASH_OFFSET                  832
#define H2_HASH_LENGTH                  (8 * HASH_LENGTH)
#define H2_PAD_LENGTH                   32
#define BYTES_PER_BLOCK                 (32 * 1024)
#define WORDS_PER_BLOCK                 (BYTES_PER_BLOCK / 4)
#define DATA_SUBBLOCKS_PER_BLOCK        31
#define SUBBLOCK_OFFSET_WORD(addr)      ((addr) & 0xFF)

#define H3_HASH_WORD_OFFSET             0
#define BYTES_PER_WORD                  4
#define BYTES_PER_SUBBLOCK              1024
#define DATA_BYTES_PER_BLOCK            (DATA_SUBBLOCKS_PER_BLOCK * BYTES_PER_SUBBLOCK)
#define DATA_WORDS_PER_BLOCK            (DATA_BYTES_PER_BLOCK / BYTES_PER_WORD)
#define MIN(X,Y)                        ((X) > (Y) ? (Y) : (X))

typedef struct diskPosition {
    uint32_t    virtWordAddr;
    uint32_t    physBlockNum;           /* Physical blocks are 31K in size */
    uint32_t    physSubBlockNum;        /* Subblocks are 1K in size */
    /*
     * Difference between physical byte address corresponding to
     * the virtWordAddr and the address of the start of the
     * physical block
     */
    uint32_t    physBlockOffset;
} diskPosition_t;

typedef struct blockCache {
    bool        isValid;
    uint32_t    physBlockNum;
    uint8_t     data[DATA_BYTES_PER_BLOCK] __attribute__((aligned(32)));
} blockCache_t;

static blockCache_t             globalBlockCache = {false};

diskState_t                     diskState;

uint32_t doRawDiskRead(uint8_t* const destAddr, const uint32_t length,
                       const uint32_t wordOffset);

static uint32_t doNonconformingDiskRead(uint8_t* const destAddr,
                                        const uint32_t length,
                                        const uint32_t wordOffset);

static uint32_t readVerifyGameMetaData(const uint32_t gamePartitionWordOffset);
static bool     getGamePartitionOffset(uint32_t *Wordoffset, uint32_t *error);

uint32_t        doRvlReadWithHashes(uint8_t *destAddr, uint32_t byteLength,
                                    uint32_t virtWordOffset);

// #define RVL_DEBUG   1

#ifdef RVL_DEBUG_1
static void dumpBytes (const uint8_t* const ptr, const int length);
#endif

/*
 * These variables are file-level because the alignment attribute
 * is not enforced for stack variables
 */
static DVDDiskInfo         diskInfo      __attribute__((aligned(32)));
static globalTOC_t         globalTOC     __attribute__((aligned(32)));
static gameTOC_t           gameTOC       __attribute__((aligned(32)));
static gamePartition_t     gamePartition __attribute__((aligned(32)));
static uint8_t             readBuffer[BYTES_PER_BLOCK] __attribute__((aligned(32)));

/*************************************************************/
void
resetDriverState(void)
{
    diskState.isRvlDisk          = false;
    diskState.hashEncryptedValid = false;
    diskState.gameMetaDataRead   = false;
    diskState.lastDiskOffset     = 0;
    globalBlockCache.isValid     = false;
}
/*************************************************************/

/*
 * INPUT: the virtual word address (byte address >> 2)
 * OUTPUT: the filled-in diskPosition structure.
 */
void
diskVirtualToPhysical(const uint32_t virtualWordAddr,
                      diskPosition_t *diskPosition)
{
    uint32_t            virtualSubBlockNum;

    virtualSubBlockNum = virtualWordAddr >> 8;
    diskPosition->virtWordAddr = virtualWordAddr;
    diskPosition->physBlockNum = virtualSubBlockNum / DATA_SUBBLOCKS_PER_BLOCK;
    diskPosition->physSubBlockNum = virtualSubBlockNum
                                     - (DATA_SUBBLOCKS_PER_BLOCK * diskPosition->physBlockNum);
    diskPosition->physBlockOffset = (diskPosition->physSubBlockNum * BYTES_PER_SUBBLOCK)
                                    + SUBBLOCK_OFFSET_WORD(virtualWordAddr) * 4;
}

/*************************************************************/

static inline uint32_t
blockNumToH2Index(const uint32_t blockNum)
{
    return ((blockNum >> 3) & 0x7);
}

/*************************************************************/

/*
 * Given a block number, return a pointer to beginning of
 * the respective H3 hash for the superblock that contains
 * that block
 */
static inline uint8_t*
blockNumToH3Ptr(const uint32_t blockNum)
{
    uint32_t    returnVal;

    returnVal = (uint32_t) h3HashArray;
    returnVal += (blockNum >> 6) * HASH_LENGTH;
    return ((uint8_t *) returnVal);
}

/*************************************************************/

/*
 * ACTION:
 *           Compute the hash value of length 'hashArrayLength'
 *           bytes pointed to by hashArray.  Compare that hash value
 *           against the value pointed at by 'hashValue'.
 * RETURNS:
 *           true   -  if the hashes verify
 *           false  -  if the they don't or some other error occurs.
 */
static bool
verifyHashArray(uint8_t* hashArray, const uint32_t hashArrayLength,
                const uint8_t* const hashValuePtr)
{
    IOSHashContext      hashContext;
    IOSHash             hashResult;
    IOSMessage          ignoredMessage;
    IOSError            result;

    /*
     * Compiler fodder.  ingnoredMessage is passed to routines
     * that require an IOS Message, even though it will never
     * be sent because the queue parameter is NULL
     */
    ignoredMessage = 0xdead;

    result = IOS_GenerateHash(&hashContext, hashArray, hashArrayLength,
                              SHA1_HASH_START, NULL, (IOSMessageQueueId) NULL,
                              ignoredMessage);
    /*
    printf ("Bytes to be hashed: \n");
    dumpBytes(hashArray, hashArrayLength);
    */


    if (result != IOS_ERROR_OK) {
        return(false);
    }
    result = IOS_GenerateHash(&hashContext, NULL,
                              0, SHA1_HASH_END, &hashResult,
                              (IOSMessageQueueId) NULL, ignoredMessage);

    if (result != IOS_ERROR_OK) {
        return(false);
    }

    /*
    printf ("Computed hash value: \n");
    dumpBytes((uint8_t *) hashResult, hashArrayLength);

    printf ("Actual hash value: \n");
    dumpBytes(hashValuePtr, hashArrayLength);
    */

    if (memcmp(hashResult, hashValuePtr, HASH_LENGTH) != 0) {
        return(false);
    }
    else {
        return(true);
    }
}

/*************************************************************/

static inline uint32_t
blockNumToWordOffset(const uint32_t blockNum)
{
    return(blockNum * WORDS_PER_BLOCK);
}

/*************************************************************/

/*
 * Read, decrypt and verify an encrypted, hashed (32K) block
 * from disk.
 * INPUT:   destAddr - where the decrypted data will be written
 *                     must be >= 31K bytes in size
 * ACTION:
 *         The raw data is written by the disk into a separate 32K buffer.
 *         The data is decrypted into the buffer pointed to by destAddr.
 *         The hash data remains in the separate buffer.
 * RETURNS: DI_ERR_NO_ERROR if the data was correctly read and
 *          verified.
 *          DI_ERR_HASH if there was a hash error.
 *          The actual read error if the data couldn't be read from disk.
 * OUTPUT: the 31K bytes of unencrypted data in the buffer pointed
 *         to by destAddr if the return value is DI_ERR_NO_ERROR.
 *
 */

static uint32_t
doBlockRead(uint8_t *destAddr, const uint32_t physBlockNum,
            const bool decrypt, const bool checkHashes)
{
    uint32_t            readReturn;
    IOSHash             hashResult;
    uint8_t             *dataPtr, *hashValuePtr;
    IOSHashContext      hashContext;
    IOSMessage          ignoredMessage;
    uint8_t             hashIv[16], dataIv[16];

    /*
     * Compiler fodder.  ingnoredMessage is passed to routines
     * that require an IOS Message, even though it will never
     * be sent because the queue parameter is NULL
     */
    ignoredMessage = 0xdead;


    readReturn = doRawDiskRead(readBuffer, BYTES_PER_BLOCK,
                            diskState.dataWordOffset +
                            blockNumToWordOffset(physBlockNum));
    if (readReturn != DI_ERR_NO_ERROR) {
        return(readReturn);
    }

    // FIXME - This flush is for doing decrypt and hash on
    //         the IOP.  Different flushes are needed when
    //         using hardware decrypt and hash.
    flushDItoIOP(readBuffer, BYTES_PER_BLOCK);


    if (decrypt) {
        memset(hashIv, 0, 16);
        /*
         * FIXME - if the Crypto API returns the right Iv for
         * the data after decrypting the hashes, skip this memcpy call
         */
        memcpy(dataIv, readBuffer + 1024 - 32 - 16, 16);

#ifdef RVL_DEBUG
        printf ("Encrypt Hash bytes: ");
        for (int i = 0; i < 16; i++) {
            printf ("0x%x ", readBuffer[i]);
        }
        printf ("\n");
#endif

        aes_SwDecryptWrapper(TitleKey, hashIv, readBuffer,
                             1024 - H2_PAD_LENGTH, readBuffer);

#ifdef RVL_DEBUG
        printf ("Decrypt Hash bytes: ");
        for (int i = 0; i < 16; i++) {
            printf ("0x%x ", readBuffer[i]);
        }
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
#endif

        aes_SwDecryptWrapper(TitleKey, dataIv,
                             readBuffer + BYTES_PER_SUBBLOCK,
                             DATA_BYTES_PER_BLOCK, destAddr);
    }
    else {
	printf ("First 16 hash bytes (not encrypted):\n\t");
	for (int i = 0; i < 16; i++) {
	    printf ("0x%x ", readBuffer[i]);
	}
	printf ("\n");
        memcpy(destAddr, readBuffer + BYTES_PER_SUBBLOCK,
               31 * BYTES_PER_SUBBLOCK);
    }

#ifdef RVL_DEBUG
    printf ("*** DBR: 1 ***\n");
    printf ("(DoBlockRead) :\n\t");
    for (int i = 0; i < 16; i++) {
        printf ("0x%x ", destAddr[i]);
    }
    printf ("\n");
#endif


    if (checkHashes) {
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
                return(DI_ERR_HASH);
            }
            dataPtr += BYTES_PER_SUBBLOCK;
            hashValuePtr += HASH_LENGTH;
        }

        /* Verify the H0 Hashes against the correct H1 */
        hashValuePtr =    readBuffer
                        + H1_HASH_OFFSET
                        + ((physBlockNum % 8) * HASH_LENGTH);
        if (verifyHashArray(readBuffer, H0_HASH_LENGTH, hashValuePtr) == false){
            ERR_DPRINT ("(doBlockRead) H0 Hashes failed to verify\n");
            return(DI_ERR_HASH);
        }
	else {
            // printf ("H0 Hashes verified\n");
	}

        /* Verify the H1 hashes against the correct H2 */
        hashValuePtr =   readBuffer
                   + H2_HASH_OFFSET
                   + (blockNumToH2Index(physBlockNum) * HASH_LENGTH);
        if (verifyHashArray(readBuffer + H1_HASH_OFFSET, H1_HASH_LENGTH,
                            hashValuePtr) == false) {
            ERR_DPRINT ("(doBlockRead) H1 Hashes failed to verify\n");
            return(DI_ERR_HASH);
        }
	else {
            // printf ("H1 Hashes verified\n");
	}

        /* Verify the H2 hashes against the correct H3 */
        if (verifyHashArray(readBuffer + H2_HASH_OFFSET, H2_HASH_LENGTH,
                            blockNumToH3Ptr(physBlockNum)) == false) {
            ERR_DPRINT ("(doBlockRead) H2 Hashes failed to verify\n");
            return(DI_ERR_HASH);
        }
	else {
            // printf ("H2 Hashes verified\n");
	}
    }
    return(DI_ERR_NO_ERROR);
} // doBlockRead

/* --------------------------------------------------------------------- */

static uint32_t
fillBlockCache(blockCache_t* const blockCache, const uint32_t physBlockNum,
               const bool decrypt, const bool checkHashes)
{
    uint32_t    returnVal;

    returnVal = doBlockRead(blockCache->data, physBlockNum,
                            decrypt, checkHashes);
    if (returnVal == DI_ERR_NO_ERROR) {
        blockCache->isValid = true;
        blockCache->physBlockNum = physBlockNum;
    }
    else {
        blockCache->isValid = false;
    }
    return(returnVal);
}

/* --------------------------------------------------------------------- */

/*
 * Fulfill a read request starting at 'readStart'
 * by taking the data from the blockCache.  Routine assumes that
 * the request and the data in the blockCache are from the same
 * physical block.  If the entire request is not satisfied
 * by the cache, update the 'destAddr', 'byteLength' and 'readStart'
 * parameters to reflect that part of the overall read has been done.
 * 
 * RETURNS:
 *              'true' if entire request could be satisfied by cache
 *              'false' otherwise.
 *              Note that destAddr, byteLength, and readStart are updated
 *              only if 'false' is returned - the values are not needed
 *              otherwise.
 *                
 */
static bool
fillRequestFromCache(const blockCache_t* const blockCache,
                     uint8_t                   **destAddr,
                     uint32_t                  *byteLength,
                     diskPosition_t            *readStart)
{

    uint32_t bytesInBuffer, bytesToTransfer, cacheOffset;

    if (((uint32_t) globalBlockCache.data & 0x1F) != 0) {
        diFatalError ("'data' element of globalBlockCache is not aligned\n");
    }

    bytesInBuffer = DATA_BYTES_PER_BLOCK - readStart->physBlockOffset;
    bytesToTransfer = MIN(bytesInBuffer, *byteLength);
    cacheOffset = (uint32_t) blockCache->data + readStart->physBlockOffset;
    memcpy(*destAddr, (void *) cacheOffset, bytesToTransfer); 

    if (bytesToTransfer == *byteLength) {
        /* All the requested data was in the cache */
        return (true);
    } else {
        *byteLength -= bytesToTransfer;
        *destAddr += bytesToTransfer;
#ifndef RVL
        assert(bytesToTransfer % 4 == 0);
#endif
        readStart->virtWordAddr += (bytesToTransfer / 4);
        readStart->physBlockNum++;
        readStart->physSubBlockNum = 0;
        return(false);
    }
}

/* --------------------------------------------------------------------- */

/*
 * Read data from a Revolution 'virtual disk image'.
 * The read is broken up into three parts:
 *      1. The part of the read that starts in the middle of a
 *         31K data block, and ends not later than the end of the block.
 *      2. The part of the read which consists of entire disk blocks.
 *      3. The part of the read which starts in the beginning of a
 *         disk block and ends before the end of the block.
 * Any of the three parts may not be present in a given read.
 * Partial block reads are done out of block cache.  
 *
 * If the H3 hashes have not been read, they are read assuming that
 * the disk offset command has been used so that the 0 address is
 * where the gamePartition_t structure exists.
 * RETURNS: DI_ERR_NO_ERROR if the read went OK
 *          DI_ERR_HASH         if the H3 hashes don't verify against H4 hash
 *                              in the eTicket, or if the tmd or eticket
 *                              doesn't verify.
 *          DI_ERR_TIMEOUT      timeout error on data read
 *          DI_ERR_NONSPECIFIC  some other data error read
 *          
 *
 */
uint32_t
doRvlRead(uint8_t *destAddr, uint32_t byteLength, uint32_t virtWordOffset)
{
    uint32_t                    returnVal, commandResult;
    static bool                 eTicketServicesInited = false;

    DPRINT2("Calling doRvlRead: byteLength = %u\n", byteLength);

#ifdef RVL
    if (eTicketServicesInited == false) {
        ESError         error;

        eTicketServicesInited = true;
        error = ES_InitLib();
        if (error < 0) {
            void printIOS_OpenError(const ESError error);

            printIOS_OpenError(error);
            ERR_DPRINT2("ES_InitLib returned %d\n", error);
            diFatalError("E-ticket services initialize failed\n");
        }
    }
#endif
           
    /*
     * hashEncryptedValid should be already be true, since it is
     * done after a READ_DISK_ID command, but check and handle anyway
     */
    if (diskState.hashEncryptedValid == false) {
        commandResult = doReadHashEncryptedState();
        if (commandResult != DI_ERR_NO_ERROR) {
            return(commandResult);
        }
    }
    if (diskState.gameMetaDataRead == false) {
        uint32_t        gamePartitionOffset;

        /*
         * If the disk offset command hasn't been given, then it is
         * up to the driver to get the game partition offset
         */
        if (diskState.lastDiskOffset == 0) {
            uint32_t error;
            if (getGamePartitionOffset(&gamePartitionOffset, &error) == false) {
                return(error);
            }
        }
        else {
            gamePartitionOffset = 0;
        }

        returnVal = readVerifyGameMetaData(gamePartitionOffset);

        if (returnVal != DI_ERR_NO_ERROR) {
            printf ("(doRvlRead) readGameMetaData returns error (0x%x)\n",
                      returnVal);
            return(returnVal);
        }
    }
    if (diskState.hashesExist) {
        returnVal = doRvlReadWithHashes(destAddr, byteLength, virtWordOffset);
    }
    else {
        /*
         * No hashes at all, and no encryption either.  Just
         * read and return what is on the disk.
         */
        returnVal = doRawDiskRead(destAddr, byteLength,
                                  virtWordOffset + diskState.dataWordOffset);
    }
    return(returnVal);
} // doRvlRead

/* --------------------------------------------------------------------- */

uint32_t
doRvlReadWithHashes(uint8_t *destAddr, uint32_t byteLength,
                    uint32_t virtWordOffset)
{
    diskPosition_t              startPosition;
    uint32_t                    returnVal;

    diskVirtualToPhysical(virtWordOffset, &startPosition);

    /*
     * First, handle disk reads that don't start on a block boundary
     */
    if (startPosition.physBlockOffset != 0) {
        /* Read does not start on block boundary */
        if (globalBlockCache.isValid == false ||
            globalBlockCache.physBlockNum != startPosition.physBlockNum) {
            returnVal = fillBlockCache(&globalBlockCache,
                                       startPosition.physBlockNum,
                                       diskState.encrypted,
                                       diskState.hashesValid);
            if (returnVal != DI_ERR_NO_ERROR) {
                return(returnVal);
            }
        }
        if (fillRequestFromCache(&globalBlockCache, &destAddr, &byteLength,
                                 &startPosition) == true) {
            return(DI_ERR_NO_ERROR);
        }
        startPosition.physBlockOffset = 0;
    }

    /*
     * Do the whole block data reads
     */
    while (byteLength > DATA_BYTES_PER_BLOCK) {
        returnVal = doBlockRead(destAddr, startPosition.physBlockNum,
                                diskState.encrypted, diskState.hashesValid);
        if (returnVal != DI_ERR_NO_ERROR) {
            return(returnVal);
        }
        destAddr += DATA_BYTES_PER_BLOCK;
        byteLength -= DATA_BYTES_PER_BLOCK;
        startPosition.physBlockNum++;
        startPosition.virtWordAddr += (DATA_BYTES_PER_BLOCK / 4);
    }

    /*
     * Finally, read data from the partial block at the end of the
     * request
     */
    if (byteLength != 0) {
        bool    requestFilled;

        if (globalBlockCache.isValid == false ||
            globalBlockCache.physBlockNum != startPosition.physBlockNum) {
            returnVal = fillBlockCache(&globalBlockCache,
                                       startPosition.physBlockNum,
                                       diskState.encrypted,
                                       diskState.hashesValid);
            if (returnVal != DI_ERR_NO_ERROR) {
                return(returnVal);
            }
        }
        requestFilled = fillRequestFromCache(&globalBlockCache, &destAddr,
                                             &byteLength, &startPosition);
#ifndef RVL
        assert(requestFilled == true);
#endif
    }
    return(DI_ERR_NO_ERROR);
}

/* --------------------------------------------------------------------- */

/*
 * Determine whether or not the disk is encrypted and/or hashed by
 * reading the DVDDiskInfo structure from disk.  The appropriate
 * variables are updated in the global variable diskState.
 */
uint32_t
doReadHashEncryptedState(void)
{
    uint32_t            returnVal;

    DPRINT("(doReadHashEncryptedState) reading diskInfo\n");
    returnVal = doNonconformingDiskRead((uint8_t *) &diskInfo,
                                         sizeof(diskInfo),
                                         DISK_INFO_OFFSET >> 2);
    DPRINT("(doReadHashEncryptedState) diskInfo read\n");
    if (returnVal == DI_ERR_NO_ERROR) {

        printf ("(doReadHashEncryptedState) noEncrypt = %d, noHashed = %d\n",
                  diskInfo.noEncryption, diskInfo.noHash);
        diskState.hashEncryptedValid = true;
        diskState.encrypted    = (diskInfo.noEncryption == 0 ? true : false);
        /*
         * If noHash is true, then currently we assume that there
         * are  hashes, just that the hash areas aren't
         * checked
         */
        if (diskInfo.noHash == 0) {
            diskState.hashesValid = true;
            diskState.hashesExist = true;
        }
        else {
            diskState.hashesValid = false;
            diskState.hashesExist = true;
        }
    }
    else {
        ERR_DPRINT ("(doReadHashEncryptedState) disk read failed\n");
    }
    return(returnVal);
}
/* --------------------------------------------------------------------- */

/*
 * Get the WORD offset of the first/only game partition by reading in turn
 * the disk's global TOC, game TOC, and array of pointers to game
 * partitions
 * RETURNS:
 *           true -  if the offset was able to be read.  The offset is
 *                   returned in 'offset'
 *           false - if the offset could not be read.  The error code
 *                   is returned in error
 *
 */

static bool
getGamePartitionOffset(uint32_t *wordOffset, uint32_t *error)
{
    uint32_t            returnVal, partitionOffset;

#ifndef RVL
    /* If the current offset isn't zero, this code doesn't work */
    assert(diskState.lastDiskOffset == 0);
#endif

    printf ("Reading global TOC\n");
    returnVal = doNonconformingDiskRead((uint8_t *) &globalTOC,
                                        sizeof(globalTOC_t),
                                        SECURITY_OFFSET >> 2);
    if (returnVal != DI_ERR_NO_ERROR) {
        *error = returnVal;
        return(false);
    }

    printf("(gGPO) Game TOC addr: 0x%x (byte addr)\n",
             (ntohl((uint32_t) globalTOC.gameTOC)) << 2); 

    /* Read Game TOC */
    returnVal = doNonconformingDiskRead((uint8_t *) &gameTOC,
                                        sizeof(gameTOC_t),
                                        ntohl((uint32_t) globalTOC.gameTOC));
    if (returnVal != DI_ERR_NO_ERROR) {
        *error = returnVal;
        return(false);
    }

    /* Read (the first) partition offset */
    returnVal = doNonconformingDiskRead((uint8_t *) &partitionOffset,
                                    sizeof(uint32_t),
                                    ntohl((uint32_t) gameTOC.gamePartitions));
    if (returnVal != DI_ERR_NO_ERROR) {
        *error = returnVal;
        return(false);
    }
    *wordOffset = ntohl(partitionOffset);
    printf ("(gamePartitionOffset) game partition offset: 0x%x\n",
             *wordOffset << 2);
    return(true);
}

/* --------------------------------------------------------------------- */

/*
 * INPUT: gamePartitionWordOffset - The word offset to the gamePartition
 *                                  structure on disk.
 *
 * Reads the game meta data in the gamePartition_t structure.
 * Reads the H3 hashes and verifies it against the eTicket
 * Verifies the TMD, eTicket, certificates, etc.
 * RETURNS: 
 *          DI_ERR_NO_ERROR     if everything went well
 *          DI_ERR_HASH         if the H3 hashes don't verify against H4 hash
 *                              in the eTicket, or if the tmd or eticket
 *                              doesn't verify.
 *          DI_ERR_TIMEOUT      timeout error on data read
 *          DI_ERR_NONSPECIFIC  some other data error read
 */

static uint32_t
readVerifyGameMetaData(const uint32_t gamePartitionWordOffset)
{
    uint32_t            returnVal;
#ifdef RVL
    ESTitleMeta         *tmd;
    void                *certBlob, *certMemory, *tmdMemory;
    IOSCSecretKeyHandle hTitleKey;
    IOSCHash            hashes;
    ESError             verifyError;
#endif


    // TODO: Verify H3 hashes against H4
    // TODO: Verify TMD, eticket, certs.
    returnVal = doNonconformingDiskRead((uint8_t *) &gamePartition,
                                        sizeof(gamePartition_t),
                                        gamePartitionWordOffset);
    if (returnVal != DI_ERR_NO_ERROR) {
        return(returnVal);
    }

#ifdef RVL
    /* Read TMD */
    if (dvdMemAllocAlign32(gamePartition.tmdSize,
                           (void **) &tmd, &tmdMemory) == false) {
        diFatalError("(readVerifyGameMetaData) Memory allocation failed\n");
    }
    returnVal = doNonconformingDiskRead((uint8_t *) tmd,
                                        gamePartition.tmdSize,
                                        (uint32_t) gamePartition.tmd);
    if (returnVal != DI_ERR_NO_ERROR) {
        return(returnVal);
    }

    printf ("TMD Location (Word): 0x%x Size: %d;  MD5 Sum: ",
             (uint32_t) gamePartition.tmd, gamePartition.tmdSize);
    printMD5sum(tmd, gamePartition.tmdSize);
    printf ("\n");
    uint8_t	*debug_ptr;
    debug_ptr = (uint8_t *) tmd;

    printf ("TMD bytes:\n");
    for (int idx = 0; idx < 16; idx++) {
	printf("%02x", debug_ptr[idx]);
    }
    printf ("\n");



    /* Read certificate blob */
    if (dvdMemAllocAlign32(gamePartition.certBlobSize,
                           (void **) &certBlob, &certMemory) == false) {
        diFatalError("(readVerifyGameMetaData) Memory allocation failed\n");
    }
    returnVal = doNonconformingDiskRead((uint8_t *) certBlob,
                                        gamePartition.certBlobSize,
                                        (uint32_t) gamePartition.certBlob);
    if (returnVal != DI_ERR_NO_ERROR) {
        return(returnVal);
    }
    printf ("VerifyGameMetaData: cert blob size = %d\n",
             gamePartition.certBlobSize);

    printf ("Certificate Blob MD5 Sum: ");
    printMD5sum(certBlob, gamePartition.certBlobSize);
    printf ("\n");

    printf ("Ticket MD5 Sum: ");
    printMD5sum(&(gamePartition.ticket), sizeof(ESTicket));
    printf ("\n");

    verifyError = ES_DiVerify(certBlob, gamePartition.certBlobSize,
                              NULL,     0,
                              &(gamePartition.ticket),
                              tmd,      gamePartition.tmdSize,
                              &hTitleKey, &hashes);

    if (verifyError != IOS_ERROR_OK) {
        ERR_DPRINT2("ES_DiVerify failed: code is: 0x%x\n", verifyError);
        // TODO: Change this to return DI_ERR_HASH after debug is complete
        diFatalError ("ES_DiVerify Failed");
    }
    diFatalError ("No error; verify OK");
#endif


    diskState.h3WordOffset   = ntohl((uint32_t) gamePartition.h3Hashes);
    diskState.dataWordOffset = ntohl((uint32_t) gamePartition.encryptedArea);
    /* For simplicity, the size is always the maximum size */
    diskState.h3Size         = MAX_H3_HASH_SIZE;

    if (diskState.encrypted == false && diskState.hashesExist == false) {
        diskState.gameMetaDataRead = true;
        return(DI_ERR_NO_ERROR);
    }

#ifndef RVL
    /* Image data starts on a 64K boundary */
    assert((diskState.dataWordOffset & 0x3FFF) == 0);
#endif

    printf("(read meta data) H3 offset: 0x%x; data offset 0x%x (byte addrs)\n",
             diskState.h3WordOffset << 2, diskState.dataWordOffset << 2);
    printf ("Reading H3 hashes\n");
    returnVal = doRawDiskRead(h3HashArray, diskState.h3Size,
                              diskState.h3WordOffset);

    if (returnVal == DI_ERR_NO_ERROR) {
        flushDItoIOP(h3HashArray, diskState.h3Size);
        diskState.gameMetaDataRead = true;
	printf ("H3 hash read succeeded\n");
    }
    else {
        diskState.gameMetaDataRead = false;
	ERR_DPRINT ("H3 hash read FAILED!!\n");
        return(returnVal);
    }

    // TODO - verify tmd and certs, get H4 hash, verify H3 against H4, etc.
    return(returnVal);

} // readVerifyGameMetaData

/* --------------------------------------------------------------------- */

/*
 * Call this function to read raw data from the disk if it is
 * possible that the length of the data is not a multiple of 32.
 * If the length is a multiple of 32, we just do a disk read
 * into the provided buffer.
 * If the length is not a multiple of 32, we do a disk read into
 * buffer which is sized to the next higher multiple of 32,
 * then copy the data into the buffer.
 * RETURNS:
 *              DI_ERR_NO_ERROR         - if there was no error
 *              DI_ERR_TIMEOUT          - if there was a timeout error
 *              DI_ERR_NONSPECIFIC      - if there was a non-timeout error
 */
static uint32_t 
doNonconformingDiskRead(uint8_t* const destAddr, const uint32_t length,
                        const uint32_t wordOffset)
{
    uint32_t    returnVal;

    printf ("(NonConformingDiskRead) Reading %u bytes from byte addr 0x%x\n",
             length, wordOffset << 2);
    if ((length & 0x1F) == 0) {
        returnVal = doRawDiskRead(destAddr, length, wordOffset);
        flushDItoIOP(destAddr, length);
    }
    else {
        uint8_t         *scratchPtrToFree, *scratchPtr;
        uint32_t        readLength;

        readLength = (length + 32) & ~0x1F;

        if (dvdMemAllocAlign32(readLength,
                               (void **) &scratchPtr,
                               (void **) &scratchPtrToFree) == false) {
            diFatalError("doNonConformingDiskRead: memory allocation failed\n");
        }

        returnVal = doRawDiskRead(scratchPtr, readLength, wordOffset);
        flushDItoIOP(scratchPtr, readLength);
        if (returnVal == DI_ERR_NO_ERROR) {
            memcpy(destAddr, scratchPtr, length);
        }
        dvdMemFree(scratchPtrToFree);
    }
    DPRINT2 ("(NonConformingDiskRead) Returning status 0x%x\n", returnVal);
    return(returnVal);
}
/* ----------------------------------------------------------------------- */
#ifdef DEBUG_1
static void
dumpBytes (const uint8_t* const ptr, const int length)
{
    for (int i = 0; i < length; i++) {
        if (i % 20 == 0)
            printf ("\n");
        printf ("%02x ", ptr[i]);
    }
    printf ("\n");
}
#endif
    
/* ----------------------------------------------------------------------- */
void
printIOS_OpenError(const ESError error)
{
    switch (error) {
    case IOS_ERROR_NOEXISTS:
        printf ("IOS_Open failed - pathname does not exist\n");
        break;

    case IOS_ERROR_ACCESS:
        printf ("IOS_Open failed - calling thread lacks permission\n");
        break;

    case IOS_ERROR_MAX:
        printf ("(DVDLowInit) Error: IOS_Open failed - connection limit has been reached\n");
        break;

    default:
        /* IOS_Open call succeeded */
        printf("IOS_Open succeeded\n");
        break;
    }
}


/* ----------------------------------------------------------------------- */
