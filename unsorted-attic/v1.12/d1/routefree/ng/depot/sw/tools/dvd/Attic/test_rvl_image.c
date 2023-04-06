#ident "$Id: test_rvl_image.c,v 1.11 2006/03/30 23:58:23 craig Exp $"
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
 * Program comments here
 * 
 */

#ifdef __CYGWIN__
#undef __STRICT_ANSI__
#else
#define fseeko(file, where, whence)     fseeko64(file, where, whence)
#define ftello(file)                    ftello64(file)
#endif

#include <assert.h>
#include <inttypes.h>
#include <netinet/in.h>         // for ntohl()
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          // for off_t definition

#include "dvd_hw.h"
#include "types.h"
#include "disk_format.h"
#include "md5.h"

uint32_t doRawDiskRead(uint8_t* const destAddr, const uint32_t length,
                       const uint32_t wordOffset);
void dumpUpdatePartition(const uint32_t updatePartitionAddr);
void dumpGamePartition(const uint32_t gamePartitionAddr,
                       const uint32_t contentSize);
void printSizes();
void dumpDiskId(), dumpDiskInfo();
uint32_t doRvlRead(uint8_t *destAddr, uint32_t byteLength,
                   uint32_t virtWordOffset);

uint8_t         h3HashArray[96 * 1024];

/* ------------------------------------------------------------- */
inline void
efseeko (FILE *stream, off_t offset, int whence)
{
    if (fseeko(stream, offset, whence) == -1) {
        fprintf (stderr, "fseeko to %llu failed - exit\n", offset);
        exit(1);
    }
}
/* ------------------------------------------------------------- */

FILE                *imageFile;

#define BYTE_OFFSET(x) ( ((uint32_t) (x)) << 2 )
int
main(int argc, char *argv[])
{
    globalTOC_t         globalTOC;
    uint32_t            updateTOCOff, gameTOCOff, updateArrayOff;
    uint32_t            gameArrayOff;
    updateTOC_t         updateTOC;
    gameTOC_t           gameTOC;
    uint32_t            numUpdates, numGames;
    updatePartition_t   **updatePartArray;
    gamePartition_t     **gamePartArray;
    char                *inFileName;
    uint64_t            contentSize = 0;


    // printSizes();
    if (argc != 2 && argc != 4) {
        printf ("Usage: %s [-s content_size] rvl_image\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "-s") == 0) {
        contentSize = atoll(argv[2]);
        inFileName = argv[3];
    }
    else {
        inFileName = argv[1];
    }

    if ( (imageFile = fopen(inFileName, "r")) == NULL) {
        fprintf (stderr, "Can't open file '%s' for read - exit\n", argv[1]);
        exit(1);
    }

    dumpDiskId();
    dumpDiskInfo();

    doRawDiskRead((uint8_t *) &globalTOC,
                sizeof(globalTOC_t), SECURITY_OFFSET >> 2);

    updateTOCOff = ntohl((uint32_t) globalTOC.updateTOC);
    gameTOCOff   = ntohl((uint32_t) globalTOC.gameTOC);

    /* Dump out update structures */
    printf ("Update TOC: 0x%" PRIx32 "; Game TOC: 0x%" PRIx32"\n",
             updateTOCOff << 2, gameTOCOff << 2);

    doRawDiskRead((uint8_t *) &updateTOC,
                sizeof(updateTOC_t), updateTOCOff);

    numUpdates     = ntohl(updateTOC.numUpdatePartitions);
    updateArrayOff = ntohl((uint32_t) updateTOC.updatePartitions);

    printf ("Number of update partitions: %" PRIu32 "\n", numUpdates);

    if (numUpdates > 0) {
        updatePartArray = (updatePartition_t **)
                           malloc (sizeof(updatePartition_t *) * numUpdates);
        assert(updatePartArray != NULL);

        doRawDiskRead((uint8_t *) updatePartArray,
                    sizeof(updatePartition_t *) * numUpdates, updateArrayOff);

        for (int i = 0; i < numUpdates; i++) {
            printf ("Update partition #%d:\n", i);
            dumpUpdatePartition(ntohl((uint32_t) updatePartArray[i]));
        }
    }

    /* Dump out game structures */
    doRawDiskRead((uint8_t *) &gameTOC, sizeof(gameTOC_t), gameTOCOff);

    numGames       = ntohl(gameTOC.numGamePartitions);
    gameArrayOff   = ntohl((uint32_t) gameTOC.gamePartitions);

    printf ("Number of game partitions: %" PRIu32 "\n", numGames);

    gamePartArray = (gamePartition_t **)
                       malloc (sizeof(gamePartition_t *) * numGames);
    assert(gamePartArray != NULL);

    doRawDiskRead((uint8_t *) gamePartArray,
                sizeof(gamePartition_t *) * numGames, gameArrayOff);

    for (int i = 0; i < numGames; i++) {
        printf ("Game partition #%d:\n", i);
        dumpGamePartition(ntohl((uint32_t) gamePartArray[i]), contentSize);
    }
    exit(0);
}

/* ------------------------------------------------------------- */
void
dumpDiskId(void)
{
    DVDDiskId           diskId;

    doRawDiskRead((uint8_t *) &diskId, sizeof(DVDDiskId), 0);
    printf ("DVD Disk ID:\n");
    printf ("\tGame name: %c%c%c%c; Company: %c%c\n", diskId.gameName[0],
            diskId.gameName[1], diskId.gameName[2], diskId.gameName[3],
            diskId.company[0], diskId.company[1]);
}
/* ------------------------------------------------------------- */
void
dumpDiskInfo(void)
{
    DVDDiskInfo         diskInfo;
    char                gameNameBuf[128];

    doRawDiskRead((uint8_t *) &diskInfo,
                sizeof(DVDDiskInfo), DISK_INFO_OFFSET >> 2);
    memcpy(gameNameBuf, diskInfo.gameNameLong, 64);
    gameNameBuf[64] = '\0';
    printf ("DVD Disk Info:\n");
    printf ("\tGame name long: %s\n", gameNameBuf);
    printf ("\tnoHash: %d; noEncryption: %d\n", diskInfo.noHash,
                                                diskInfo.noEncryption);
}
/* ------------------------------------------------------------- */

void
dumpUpdatePartition(const uint32_t updatePartitionAddr)
{
    md5_state_t         state;
    md5_byte_t          digest[16];
    updatePartition_t   updatePartition;
    uint32_t            tmdAddress, tmdSize, certBlobAddr, certBlobSize;
    uint32_t            imageAddr;
    uint8_t             tmdBuf[4096], certBlobBuf[1024 * 32];
    uint8_t             imageBytes[256];

    printf ("\tUpdate partition starts at: 0x%" PRIx32 " (byte addr)\n",
            updatePartitionAddr << 2);

    md5_init(&state);
    doRawDiskRead((uint8_t *) &updatePartition,
                sizeof(updatePartition_t), updatePartitionAddr);
    md5_append(&state, (md5_byte_t *) &(updatePartition.ticket),
               sizeof(ESTicket));
    md5_finish(&state, digest);

    printf ("\tEticket MD5 Sum: ");
    for (int di = 0; di < 16; ++di) {
        printf("%02x", digest[di]);
    }
    printf ("\n");

    tmdSize = ntohl(updatePartition.tmdSize);
    tmdAddress = ntohl((uint32_t) updatePartition.tmd);
    printf ("\tTMD size: %" PRIu32 "\n", tmdSize);

    doRawDiskRead(tmdBuf, tmdSize, tmdAddress);

    md5_init(&state);
    md5_append(&state, (md5_byte_t *) tmdBuf, tmdSize);
    md5_finish(&state, digest);

    printf ("\tTMD MD5 Sum: ");
    for (int di = 0; di < 16; ++di) {
        printf("%02x", digest[di]);
    }
    printf ("\n");

    certBlobSize  = ntohl(updatePartition.certBlobSize);
    certBlobAddr  = ntohl((uint32_t) updatePartition.certBlob);
    imageAddr     = ntohl((uint32_t) updatePartition.image);

    printf ("\tCertificate blob size: %"  PRIu32
            "; Cert blob start addr: 0x%" PRIx32  "\n",
             certBlobSize, certBlobAddr << 2);

    printf ("\t\tCert Blob MD5 Sum: ");

    doRawDiskRead(certBlobBuf, certBlobSize, certBlobAddr);
    md5_init(&state);
    md5_append(&state, (md5_byte_t *) certBlobBuf, certBlobSize);
    md5_finish(&state, digest);
    for (int di = 0; di < 16; ++di) {
        printf("%02x", digest[di]);
    }
    printf ("\n");

    doRawDiskRead(imageBytes, sizeof(imageBytes), imageAddr);
    printf ("\tImage: Address 0x%" PRIx32 "\n", imageAddr << 2);
    printf ("\tImage bytes: ");
    for (int i = 0; i < 16; ++i) {
        printf("%02x ", imageBytes[i]);
    }
    printf ("\n");
}
/* ------------------------------------------------------------- */

void
dumpGamePartition(const uint32_t gamePartitionAddr,
                  const uint32_t contentSize)
{
    md5_state_t         state;
    md5_byte_t          digest[16];
    gamePartition_t     gamePartition;
    uint32_t            tmdAddress, tmdSize, certBlobAddr, certBlobSize;
    uint32_t            cryptAddr;
    uint8_t             tmdBuf[4096], certBlobBuf[1024 * 32];
    uint8_t             cryptBytes[256];
    uint8_t             dataBytes[1024];
    uint32_t            readReturn;

    printf ("\tGame partition starts at: 0x%" PRIx32 " (byte addr)\n",
            gamePartitionAddr << 2);

    md5_init(&state);
    doRawDiskRead((uint8_t *) &gamePartition,
                sizeof(gamePartition_t), gamePartitionAddr);
    md5_append(&state, (md5_byte_t *) &(gamePartition.ticket),
               sizeof(ESTicket));
    md5_finish(&state, digest);

    printf ("\tEticket MD5 Sum: ");
    for (int di = 0; di < 16; ++di) {
        printf("%02x", digest[di]);
    }
    printf ("\n");

    tmdSize = ntohl(gamePartition.tmdSize);
    tmdAddress = ntohl((uint32_t) gamePartition.tmd);
    printf ("\tTMD size: %" PRIu32 "\n", tmdSize);

    doRawDiskRead(tmdBuf, tmdSize, tmdAddress);

    md5_init(&state);
    md5_append(&state, (md5_byte_t *) tmdBuf, tmdSize);
    md5_finish(&state, digest);

    printf ("\tTMD MD5 Sum: ");
    for (int di = 0; di < 16; ++di) {
        printf("%02x", digest[di]);
    }
    printf ("\n");

    certBlobSize  = ntohl(gamePartition.certBlobSize);
    certBlobAddr  = ntohl((uint32_t) gamePartition.certBlob);
    cryptAddr     = ntohl((uint32_t) gamePartition.encryptedArea);

    printf ("\tCertificate blob size: %"  PRIu32
            "; Cert blob start addr: 0x%" PRIx32  "\n",
             certBlobSize, certBlobAddr << 2);

    printf ("\tCert Blob MD5 Sum: ");

    doRawDiskRead(certBlobBuf, certBlobSize, certBlobAddr);
    md5_init(&state);
    md5_append(&state, (md5_byte_t *) certBlobBuf, certBlobSize);
    md5_finish(&state, digest);
    for (int di = 0; di < 16; ++di) {
        printf("%02x", digest[di]);
    }
    printf ("\n");

    printf ("\tH3 Hash Address: 0x%" PRIx32 "\n",
             (ntohl((uint32_t) gamePartition.h3Hashes) << 2));

    /* The 1024 is to skip over the hash bytes */
    doRawDiskRead(cryptBytes, sizeof(cryptBytes), cryptAddr + (1024 >> 2));
    printf ("\tImage: Address 0x%" PRIx32 "\n", cryptAddr << 2);
    printf ("\tRaw image bytes: ");
    for (int i = 0; i < 16; ++i) {
        printf("%02x ", cryptBytes[i]);
    }
    printf ("\n");
    readReturn = doRvlRead(cryptBytes, sizeof(cryptBytes), 0);
    if (readReturn != DI_ERR_NO_ERROR) {
        printf ("doRvlRead failed: %x\n", readReturn);
    }
    else {
        printf ("\tActual image bytes: ");
        for (int i = 0; i < 16; ++i) {
            printf("%02x ", cryptBytes[i]);
        }
        printf ("\n");
    }
    if (contentSize != 0) {
        int iterations;

        md5_init(&state);
        iterations = contentSize / 1024;
        for (int i = 0; i < iterations; i++) {
            readReturn = doRvlRead(dataBytes, sizeof(dataBytes),
                                   (i * 1024) >> 2);
            if (readReturn != DI_ERR_NO_ERROR) {
                printf ("doRvlRead failed: %x - exit\n", readReturn);
                exit(1);
            }
            md5_append(&state, dataBytes, 1024);
        }
        md5_finish(&state, digest);
        printf ("\t\tMD5 Sum: ");
        for (int di = 0; di < 16; ++di) {
            printf("%02x", digest[di]);
        }
    }
}

/* ------------------------------------------------------------- */

void
printSizes()
{
    printf ("ESTicket: %d/0x%x\n", sizeof(ESTicket), sizeof(ESTicket));
    printf ("IOSCSigRsa2048: %d/0x%x\n",
             sizeof(IOSCSigRsa2048), sizeof(IOSCSigRsa2048));
}

/* ------------------------------------------------------------- */

uint32_t
doRawDiskRead(uint8_t* const destAddr, const uint32_t length,
           const uint32_t wordOffset)
{
    efseeko(imageFile, wordOffset << 2, SEEK_SET);

    /*
     * The disk drive only reads multiples of 32 bytes.  If the
     * size requested is not such a multiple, we use a scratch
     * buffer and copy the result into the destination
     */

    if ((length & 0x1F) == 0) {
        if (fread(destAddr, length, 1, imageFile) != 1) {
            printf ("(doRawDiskRead) Read of %u bytes from addr 0x%" PRIx32 " failed -exit\n", length, wordOffset << 2);
            if (ferror(imageFile)) {
                printf ("Read failed because of an error\n");
                perror("fread:");
            }
            if (feof(imageFile)) {
                printf ("Read failed because of eof\n");
            }
            exit(1);
        }
    }
    else {
        uint8_t         scratch[2 * 1024];
        uint32_t        readLength;

        readLength = (length + 32) & ~0x1F;
        if (readLength > sizeof(scratch)) {
            printf ("Error: scratch is too small for request of %"
                     PRIu32 " bytes\n",
                     length);
            exit(1);
        }
        if (fread(scratch, readLength, 1, imageFile) != 1) {
            printf ("Read from addr 0x%" PRIx32 " failed\n", wordOffset << 2);
            exit(1);
        }
        memcpy(destAddr, scratch, length);
    }
    return(DI_ERR_NO_ERROR);
}

/* ------------------------------------------------------------- */

void
diFatalError(const char *message)
{
    printf ("DI fatal errror: %s\n", message);
    exit(1);
}
/* ------------------------------------------------------------- */

void *
dvdMemAlloc(const uint32_t size)
{
    return(malloc(size));
}
/* ------------------------------------------------------------- */

void
dvdMemFree(void *ptr)
{
    free(ptr);
}

/* ------------------------------------------------------------- */
bool
dvdMemAllocAlign32(const uint32_t size, void **ptrToMem, void **ptrToFree)
{
    void        *mallocResult;
    
    mallocResult = malloc(size);
    *ptrToMem = *ptrToFree = mallocResult;
    if (mallocResult == NULL) {
        return(false);
    }
    else {
        return(true);
    }
}
/* ------------------------------------------------------------- */
