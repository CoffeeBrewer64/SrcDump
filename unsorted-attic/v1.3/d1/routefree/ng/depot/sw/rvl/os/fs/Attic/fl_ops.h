/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished proprietary information of BroadOn Communications Corp.,
 *  and are protected by federal copyright law. They may not be disclosed
 *  to third parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 *  Description:
 *      This file declares the flash device driver operations
 *
 */


#ifndef __FL_OPS_H__
#define __FL_OPS_H__


#ifdef NET_CARD
#include <sc/iostypes.h>
#include <sc/flash.h>
#else
#include <iostypes.h>
#include <flash.h>
#endif


/* Resource manager context */
typedef struct {
    u32     inUse;
    u32     pageOffset;
} FLContext;


/* Structures for defining device specific information */
typedef struct {
    u8      makerID;
    u8      deviceID;
} FLIdentifier;

typedef struct {
    u8      reset;
    u8      readSetup;
    u8      read;
    u8      readSecondHalf;
    u8      readSpare;
    u8      readForCopy;
    u8      readForMultiplane;
    u8      programSetup;
    u8      program;
    u8      programForCopy;
    u8      programMultiplane;
    u8      cache;
    u8      copyBack;
    u8      eraseSetup;
    u8      eraseSetupMultiplane;
    u8      erase;
    u8      randomOutputSetup;
    u8      randomOutput;
    u8      randomInput;
    u8      readOpStatus;
    u8      readOpStatusMultiplane;
    u8      addrBytePhase;
} FLCommandSet;

typedef struct {
    u8      eoc;
    u8      rsa;
    u8      rea;
    u8      wea;
    u8      caa;
} FLConfig;

typedef struct {
    FLIdentifier    flashID;
    FLCommandSet    cmdSet;
    FLDevCap        cap;
    FLConfig        cfg;
} FLDev;


/* These commands have to be common for all flash devices */
#define FL_CMD_RESET            0xff
#define FL_CMD_READ_ID          0x90

/* Invalid values */
#define FL_REG_ADDR_INVALID     0xffffffff
#define FL_CMD_INVALID          0xfe

/* Status byte value */
#define FL_STATUS_GOOD          0xff

/* Flash controller-related constants */
#define FL_SPARE_ECC_OFFSET     64      /* ECC is 64 bytes above spare */
#define FL_SPARE_ALIGN_SZ       128
#define FL_ECC_UNIT             512     /* ECC is calculated per 512 bytes */
#define FL_ECC_UNIT_SHIFT       9
#define FL_ECC_SIZE             4       /* 4 byte occupied for each ECC */


/* Flash device driver info, exposed to be used by other flash tests */
extern FLDev                    __flDev;


/*
 *  Description
 *      Execute a flash command
 *
 */
void        flSetDevAddr(u32 ad0, u32 ad1);
void        flSetMemAddr(u32 ma0, u32 ma1);
IOSError    flExecCmd(u32 cmd, u32 adp, u32 opmask, u32 size);

/*
 *  Description:
 *      Page-level operations
 *
 */
IOSError    flWritePage(u32 pageIndex, const u8 *buf, const u8 *spare,
                    u32 cache, u32 ecc);
IOSError    flReadPage(u32 pageIndex, u8 *buf, u8 *spare);
IOSError    flCopyPage(u32 source, u32 dest);

/*
 *  Description:
 *      Flash device driver operations
 *
 */
IOSError    flOpen(void);
IOSError    flGetCap(FLDevCap *cap);
IOSError    flGetId(FLIdentifier *id);
IOSError    flErase(u32 blockIndex);
IOSError    flWrite(u32 blockIndex, const u8 *buf, const u8 *spare);
IOSError    flRead(u32 blockIndex, u8 *buf, u8 *spare);
IOSError    flCopy(u32 source, u32 dest);
IOSError    flGetStats(FLStats *stats);
IOSError    flStatus(u32 blockIndex);
IOSError    flClose(void);

/* Internal operations */
IOSError    flGetNextAvailCtx(void);
IOSError    flCtxCheck(void *);


#endif /* __FL_OPS_H__ */
