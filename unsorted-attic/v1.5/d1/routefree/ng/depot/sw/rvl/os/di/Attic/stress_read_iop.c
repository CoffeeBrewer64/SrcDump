#ident "$Id: stress_read_iop.c,v 1.4 2006/03/21 02:26:01 wheeler Exp $"
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

#include <stdlib.h>
#include <string.h>

#include "stdint.h"

#include "ios.h"
#include "ioslibc.h"

#include "dvd_hw_reg.i"
#include "dvd_hw.h"
#include "dvd_command.h"
#include "md5.h"

#define STDIO
#define STDDEF
#include "standard.h"
#include "rand.h"

#define         ALL_PIDS                ~0

#define STACK_SIZE (128 * 1024)
const uint8_t  _initStack[STACK_SIZE];
const uint32_t _initStackSize = sizeof(_initStack);
const uint32_t _initPriority = 11;

#define BUS_ENABLE_MASK 0x00800000

static diCommand_t  diCommand[4]  __attribute__((aligned(32)));

static bool             callReadDiskID(const IOSFd diFilePtr,
                                       const bool verbose);
static bool             callReadDisk(const IOSFd diFilePtr, uint8_t *buffer,
                                     const uint32_t length,
                                     const uint32_t diskOffsetByte);

void                    MD5_sum_disk_section(const IOSFd diFilePtr,
                                             const uint32_t startAddr,
                                             const uint32_t bytesToRead,
                                             md5_byte_t *resultDigest);

void                   fillBufWithRandom(randctx *context,
                                         uint8_t *buf,
                                         const uint32_t numBytes);
void                   MD5_sum_rand_sequence(const uint32_t startAddr,
                                             const uint32_t byteLength,
                                             md5_byte_t *resultDigest);
void enableAHB_IO_MEM(void);
bool		       do_read_stress(const IOSFd diFilePtr);
void 		       doSleep(const int numSecs);

/* ---------------------------------------------------------------------- */
#define REPLY_QUEUE_SIZE        8
#define SLEEP_QUEUE_SIZE	2

static IOSMessage              replyQueueBuf[REPLY_QUEUE_SIZE];
static IOSMessageQueueId       replyQueue;

static IOSMessage              sleepQueueBuf[SLEEP_QUEUE_SIZE];
static IOSMessageQueueId       sleepQueue;

int
main(int argc, char *argv[])
{
    /* Must be multiple of 32 bytes long and aligned to 32 bytes */
    char                pathBuf[32] __attribute__((aligned(32)));
    // uint32_t            retVal;
    IOSFd               diFilePtr;
    // md5_byte_t          digest[16];

    replyQueue = IOS_CreateMessageQueue(replyQueueBuf,
                                        REPLY_QUEUE_SIZE);
    if (replyQueue < 0) {
        printf ("Can't create reply queue - exit\n");
        IOS_DestroyThread(0, NULL);
    }

    sleepQueue = IOS_CreateMessageQueue(sleepQueueBuf,
                                        SLEEP_QUEUE_SIZE);
    if (sleepQueue < 0) {
        printf ("Can't create reply queue - exit\n");
        IOS_DestroyThread(0, NULL);
    }
    printf ("Stress tests starting in 10 seconds\n");
    doSleep(10);


    printf ("*** Enabling AHB IO MEM ***\n");
    enableAHB_IO_MEM();


    strncpy(pathBuf, "/dev/di", sizeof(pathBuf));
    diFilePtr = IOS_Open(pathBuf, 0);
    
    switch(diFilePtr) {

    case IOS_ERROR_NOEXISTS:
        printf ("() Error: pathname does not exist\n");
        return(false);
        break;

    case IOS_ERROR_ACCESS:
        printf ("(main) Error: calling thread lacks permission\n");
        return(false);

    case IOS_ERROR_MAX:
        printf ("(main) Error: connection limit has been reached\n");
        return(false);

    default:
        /* IOS_Open call succeeded */
        printf("(DVDLowInit) IOS_Open succeeded\n");
        break;
    }
    diCommand[0].theCommand = DI_CLEAR_COVER_INTERRUPT;

    IOS_Ioctl(diFilePtr, DI_CLEAR_COVER_INTERRUPT, &(diCommand[0]),
              sizeof(diCommand_t), NULL, 0);

    if (callReadDiskID(diFilePtr, false) == false) {
        printf ("Read Disk ID FAILED - exiting!!!");
	IOS_DestroyThread(0, NULL);
    }

    if (do_read_stress(diFilePtr) == false) {
        printf ("do_read_stress failed\n");
	IOS_DestroyThread(0, NULL);
	exit(0);
    }


    /*
    MD5_sum_disk_section(diFilePtr, 0x40000, 32, digest);

    printf ("\n\nMD5 Sum: ");
    for (int di = 0; di < 16; ++di) {
        printf("%02x", digest[di]);
    }
    printf ("\n");
    */

    printf ("(dvd_main) Exiting normally (PASSED)\n");
    IOS_DestroyThread(0, NULL);
    exit(0);
}

/* ---------------------------------------------------------------------- */

bool
do_read_stress(const IOSFd diFilePtr)
{
    md5_byte_t          disk_digest[16], rand_digest[16];
    uint32_t		readSize, readOffset;
    bool		result;
    randctx             func_context;
    int			max_count = 100000, current_count = 0;

    func_context.randa = 0xdeadbeef;
    func_context.randb = 0xcafecafe;
    func_context.randc = 0xbabebabe;
    for (int i=0; i<256; i++) {
	func_context.randrsl[i]= (uint32_t) 0;
    }

    randinit(&func_context, TRUE);

    do {
	readSize   = rand(&func_context) & ~0x1F;
	readOffset = rand(&func_context) & ~0x3;

	/* Cap read size at 512K */
	readSize &= 0x7FFFF;

	/* Cap read offset at 64M */
	readOffset &= 0x3FFFFFF;

	/*
	readSize = 512;
	readOffset = 3 * 1024;
	*/
	printf ("Iteration %d: Reading %u bytes from offset %u\n",
                 current_count, readSize, readOffset);
	MD5_sum_disk_section(diFilePtr, 0x40000 + readOffset, readSize, disk_digest);
	MD5_sum_rand_sequence(readOffset, readSize, rand_digest);

	printf ("Disk MD5 Sum: ");
	for (int di = 0; di < 16; ++di) {
	    printf("%02x", disk_digest[di]);
	}
	printf ("\n");

	printf ("Rand MD5 Sum: ");
	for (int di = 0; di < 16; ++di) {
	    printf("%02x", rand_digest[di]);
	}
	printf ("\n");
	if (memcmp(rand_digest, disk_digest, 16) == 0) {
	    printf ("Strings matched\n");
	    result = true;
	}
	else {
	    printf ("Strings differ\n");
	    result = false;
	    return(false);
	}
	current_count++;
	doSleep(2);
    } while (current_count < max_count);
    return(true);
}

/* ---------------------------------------------------------------------- */

/* IMPORTANT! Aligned attribute doesn't work for auto variables! */
static uint8_t     buf[1024] __attribute__((aligned(32)));
/*
 * Calculate the MD5 sum of the disk contents starting at startAddr
 * 
 */
void
MD5_sum_disk_section(const IOSFd diFilePtr, const uint32_t startAddr,
                     const uint32_t byteLength, md5_byte_t *resultDigest)
{
    uint32_t    bytesToRead, bytesLeftToRead, currentAddr;
    md5_state_t state;

    md5_init(&state);
    currentAddr = startAddr;

    if (byteLength % 32 != 0) {
        printf ("(Error: disk section not a multiple of 32\n");
    }
    
    bytesLeftToRead = byteLength;

    while (bytesLeftToRead != 0) {
        // printf ("Cur: 0x%x; End: 0x%x\n", currentAddr, endAddr);
        if (bytesLeftToRead > sizeof(buf)) {
            bytesToRead = sizeof(buf);
        }
        else {
            bytesToRead = bytesLeftToRead;
        }

        callReadDisk(diFilePtr, buf, bytesToRead, currentAddr);
/* 
        printf ("Read finished\n");
        printf ("Bytes read:\n");
	for (int di = 0; di < 32; ++di) {
	    printf("%02x", buf[di]);
	}
        printf ("\n");
*/
        md5_append(&state, buf, bytesToRead);
        bytesLeftToRead -= bytesToRead;
        currentAddr     += bytesToRead;
    }
    md5_finish(&state, resultDigest);
}

/* ---------------------------------------------------------------------- */

/*
 * Calculate the MD5 sum of the random number sequence.
 */
void
MD5_sum_rand_sequence(const uint32_t startAddr, const uint32_t byteLength,
                      md5_byte_t *resultDigest)
{
    uint8_t     buf[1024];
    uint32_t    bytesToGenerate, bytesLeftToGenerate;
    randctx     context;
    md5_state_t state;


    /*
    printf ("Doing sum_rand_sequence: 0x%x, 0x%x, 0x%x\n",
             startAddr, byteLength, (uint32_t) resultDigest);
    */
    // Must match what is in random_file.c
    /*
    context.randa = 0xdeadbeef;
    context.randb = 0xcafecafe;
    context.randc = 0xbabebabe;
    */

    md5_init(&state);

    context.randa = 0x0;
    context.randb = 0x0;
    context.randc = 0x0;
    for (int i=0; i<256; i++) {
	context.randrsl[i]= (uint32_t) 0;
    }
    randinit(&context, TRUE);

    // Run generator until we get to the section we need.

    printf ("Running RNG forward.\n");
    for (int i = 0; i < startAddr >> 2; i++) {
        uint32_t        rand_num;

        rand_num = rand(&context);
    }

    bytesLeftToGenerate = byteLength;

    printf ("Generating random sequence\n");
    while (bytesLeftToGenerate != 0) {
        if (bytesLeftToGenerate > sizeof(buf)) {
            bytesToGenerate = sizeof(buf);
        }
        else {
            bytesToGenerate = bytesLeftToGenerate;
        }

        // printf ("bytesToGenerate: %u\n", bytesToGenerate);
        fillBufWithRandom(&context, buf, bytesToGenerate);
        /*
        printf ("First bytes generated\n");
	for (int di = 0; di < 32; ++di) {
	    printf("%02x", buf[di]);
	}
        printf ("\n");
        */
        md5_append(&state, buf, bytesToGenerate);
        bytesLeftToGenerate -= bytesToGenerate;
    }
    md5_finish(&state, resultDigest);
}

/* ---------------------------------------------------------------------- */

void
fillBufWithRandom(randctx *context, uint8_t *buf, const uint32_t numBytes)
{
    uint32_t    numWords, *bufPtr;


    if ((numBytes & 0x3) != 0) {
        printf ("(fillBufWithRandom) Error: numBytes is not a multiple of 4\n");
        IOS_DestroyThread(0, NULL);
    }

    numWords = numBytes >> 2;
    bufPtr = (uint32_t *) buf;

    // printf ("\n\nFill buf with random\n");
    for (int i = 0; i < numWords; i++) {
        bufPtr[i] = rand(context);
	// printf("Word: 0x%x\n", bufPtr[i]);
    }
    // printf ("\n");
}

/* ---------------------------------------------------------------------- */
DVDDiskID           diskID __attribute__((aligned(32)));

bool
callReadDiskID(const IOSFd diFilePtr, const bool verbose)
{
    IOSResourceRequest  *reply;
    IOSError	        receiveError;

    // FIXME - cover interrupt is set after emulator starts.
    //         Must clear before doing Ioctl call
    //         Also, disk emulator not logging read disk id command

    diCommand[0].theCommand = DI_READ_DISK_ID_CMD;
    diCommand[0].arg[0] = (uint32_t) &diskID;

    IOS_IoctlAsync(diFilePtr, DI_READ_DISK_ID_CMD, &(diCommand[0]),
                   sizeof(diCommand_t), &diskID, sizeof(DVDDiskID),
                   replyQueue, reply);

    receiveError = IOS_ReceiveMessage(replyQueue, (IOSMessage *) &reply,
                                      IOS_MESSAGE_BLOCK);

    if (receiveError != IOS_ERROR_OK) {
        printf ("Receive error on replyQueue\n");
        return(false);
    }


    if (reply->status == DVD_INTTYPE_TC) {
        if (verbose) {
	    printf ("Game name: (0x%x) '%c%c%c%c'\n",
			 (uint32_t) &(diskID.gameName[0]),
			 diskID.gameName[0],
			 diskID.gameName[1],
			 diskID.gameName[2],
			 diskID.gameName[3]);
	    printf ("Company: '(0x%x) %c%c'\n", (uint32_t) &(diskID.company[0]),
		     diskID.company[0], diskID.company[1]);
	    printf ("Game version: %d\n", diskID.gameVersion);
	}
        return(true);
    }
    else if (reply->status == DVD_INTTYPE_TIMEOUT) {
        printf ("ERROR - Command timed out\n");
        return(false);
    }
    else if (reply->status == DVD_INTTYPE_DE) {
        printf ("ERROR - Command had an error\n");
        return(false);
    }
    else {
        printf ("ERROR - Unknown callback value 0x%x\n", reply->status);
        return(false);
    }
}

/* ---------------------------------------------------------------------- */

bool
callReadDisk(const IOSFd diFilePtr, uint8_t *buffer,
             const uint32_t length, const uint32_t diskOffsetByte)
{
    IOSResourceRequest  *reply;
    IOSError	        receiveError;

    // printf ("(callReadDisk) Buf address: 0x%x\n", (uint32_t) buffer);
    if ((diskOffsetByte & 0x3) != 0) {
        printf ("Error: disk offset is not word aligned\n");
    }
    if ((length & 0x1F) != 0) {
        printf ("Error: length is not a multiple of 32\n");
    }

    diCommand[0].theCommand = DI_READ_CMD;
    diCommand[0].arg[0] = (uint32_t) buffer;
    diCommand[0].arg[1] = length;
    diCommand[0].arg[2] = diskOffsetByte >> 2;

    IOS_IoctlAsync(diFilePtr, DI_READ_CMD, &(diCommand[0]),
                   sizeof(diCommand_t), buffer, length,
                   replyQueue, reply);

    receiveError = IOS_ReceiveMessage(replyQueue, (IOSMessage *) &reply,
                                      IOS_MESSAGE_BLOCK);

    if (receiveError != IOS_ERROR_OK) {
        printf ("Receive error on replyQueue\n");
        return(false);
    }
    if ((reply->status == DVD_INTTYPE_TC)) {
        return(true);
    }
    else if (reply->status == DVD_INTTYPE_TIMEOUT) {
        printf ("ERROR - Read command timed out\n");
        return(false);
    }
    else if (reply->status == DVD_INTTYPE_DE) {
        printf ("ERROR - Read command had an error\n");
        return(false);
    }
    else {
        printf ("ERROR - Unknown callback value 0x%x\n", reply->status);
        return(false);
    }
}

/* ---------------------------------------------------------------------- */
void
enableAHB_IO_MEM(void)
{
    uint32_t	reg;

    reg = busRd32(ACR_REGS_BASE + AIPIOCTRL_OFFSET + BUS_ENABLE_MASK);
    AIPIOCTRL_SET_ENAHBIOMEM(reg, 1);
    busWrt32(ACR_REGS_BASE + AIPIOCTRL_OFFSET + BUS_ENABLE_MASK, reg);
}
/* ---------------------------------------------------------------------- */
void
doSleep(const int numSecs)
{
    IOSError            receiveError;
    IOSMessage          inMesg;
    IOSTimerId          sleepId;
    IOSMessage          timeoutMesg;


    // Compiler fodder - value isn't actually used
    timeoutMesg = 0xdeaddead;

    sleepId = IOS_CreateTimer(numSecs * 1000 * 1000, 0,
                              sleepQueue, timeoutMesg);

    printf ("(doSleep) Sleeping for %u seconds.\n", numSecs);
    receiveError = IOS_ReceiveMessage(sleepQueue,
                                      (IOSMessage *) &inMesg,
                                      IOS_MESSAGE_BLOCK);
    printf("(doSleep) Done sleeping.\n");
    IOS_DestroyTimer(sleepId);
}
