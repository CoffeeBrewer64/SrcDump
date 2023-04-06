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
 *      This file implements the flash device driver operations
 *
 */


#ifdef NET_CARD
#include <sc/libc.h>
#include <sc/sc.h>
#include <sc/ios.h>
#include <sc/iostypes.h>
#include <sc/flash.h>

#include "fl_utils.h"
#include "sc/fl_ops.h"
#else
#include <ioslibc.h>
#include <iop.h>
#include <ios.h>
#include <iostypes.h>
#include <flash.h>
#ifndef IOS_ENABLE
#include <sys.h>
#endif

#include "fl_utils.h"
#include "fl_ops.h"
#endif


/* Message queue for handling flash interrupt */
#define FL_MSG_QUEUE_SIZE   4
#define FL_MSG_INTR         0x1

/* Buffer alignment macro */
#define FL_ALIGN_BUF(buf, sz)   (u8 *) (((u32)(buf) + ((sz) - 1)) & ~((sz) - 1))

/* Byte swap */
#define FL_BYTE_SWAP(x)     (((x & 0xff000000) >> 24) |                     \
                                ((x & 0x00ff0000) >> 8) |                   \
                                ((x & 0x0000ff00) << 8) |                   \
                                ((x & 0x000000ff) << 24))


/* Resource manager context */
static FLContext            __flCtx[FL_RESRC_MGR_NUMCTX];

/* Flash device driver is ready to accept normal operations */
static u32                  __flReady = 0;

/*
 * The __flSpareBuf is used for writing to or reading from
 * the spare region. It is aligned on FL_SPARE_ALIGN_SZ.
 * The __flBuf is used for reading the manufacturer's ID and
 * the operation status. It is aligned on FL_BASE_ALIGN_SZ.
 * Two separate buffers are needed because when writing a
 * page, both __flSpareBuf and __flBuf are used. Alignment
 * on more than 16-byte boundary does not work well with
 * da.link, therefore twice the size of FL_SPARE_ALIGN_SZ is
 * allocated to __flSpareBuf and the buffer is aligned by
 * the macro FL_ALIGN_BUF(buf, sz)
 */
static u8                   __flSpareBuf[FL_SPARE_ALIGN_SZ*2];
static u8                   __flBuf[FL_BASE_ALIGN_SZ]               \
                                __attribute__ ((aligned (FL_BASE_ALIGN_SZ)));

#ifdef IOS_ENABLE
/* Message queue for handling flash interrupt */
static IOSMessage            __flMsgQ[FL_MSG_QUEUE_SIZE];
static IOSMessageQueueId     __flMsgQId;
#endif

/* Flash operation statistics */
static FLStats              __flStats;

/* Flash device driver info, exposed to be used by other flash tests */
FLDev                       __flDev;

/* Supported flash devices */
static FLDev devices[] = {

    {
        /* Flash type */
        {FL_HYNIX_ID, FL_HYNIX_64MB_ID},

        /* Command set and address byte phase */

        {0xff,            /* reset */
         FL_CMD_INVALID,  /* readSetup */
         0x0,             /* read */
         0x1,             /* readSecondHalf */
         0x50,            /* readSpare */
         FL_CMD_INVALID,  /* readForCopy */
         FL_CMD_INVALID,  /* readForMultiplane */
         0x80,            /* programSetup */
         0x10,            /* program */
         FL_CMD_INVALID,  /* programForCopy */
         FL_CMD_INVALID,  /* programMultiplane */
         FL_CMD_INVALID,  /* cache */
         0x8a,            /* copyBack */
         0x60,            /* eraseSetup */
         FL_CMD_INVALID,  /* eraseSetupMultiplane */
         0xd0,            /* erase */
         FL_CMD_INVALID,  /* randomOutput */
         FL_CMD_INVALID,  /* randomOutput */
         FL_CMD_INVALID,  /* randomInput */
         0x70,            /* readOpStatus */
         FL_CMD_INVALID,  /* readOpStatusMultiplane */
         0x1d},           /* addrBytePhase */

        /* Flash capability */
        {26,    /* totalSzShift */
         14,    /* erasableBlockSzShift */
         9,     /* pageSzShift */
         4,     /* pageSpareSzShift */
         2,     /* userSpareSzShift */
         1,     /* numPlanes */
         1,     /* supportCopy */
         5},    /* Status byte offset */

        /*  FL_CONF_REG parameters  */
        /* eoc  rsa   rea  wea  caa */
        {  0x4, 0x3, 0x1e, 0xe, 0x7f }
    },

    {
        {FL_HYNIX_ID, FL_HYNIX_512MB_ID},

        /* Command set and address byte phase */

        {0xff,            /* reset */
         0x00,            /* readSetup */
         0x30,            /* read */
         FL_CMD_INVALID,  /* readSecondHalf */
         FL_CMD_INVALID,  /* readSpare */
         0x35,            /* readForCopy */
         FL_CMD_INVALID,  /* readForMultiplane */
         0x80,            /* programSetup */
         0x10,            /* program */
         0x10,            /* programForCopy */
         FL_CMD_INVALID,  /* programMultiplane */
         0x15,            /* cache */
         0x85,            /* copyBack */
         0x60,            /* eraseSetup */
         FL_CMD_INVALID,  /* eraseSetupMultiplane */
         0xd0,            /* erase */
         0x05,            /* randomOutput */
         0xe0,            /* randomOutput */
         0x85,            /* randomInput */
         0x70,            /* readOpStatus */
         FL_CMD_INVALID,  /* readOpStatusMultiplane */
         0x1f},           /* addrBytePhase */

        /* Flash capability */
        {29,    /* totalSzShift */
         17,    /* erasableBlockSzShift */
         11,    /* pageSzShift */
         6,     /* pageSpareSzShift */
         5,     /* userSpareSzShift */
         1,     /* numPlanes */
         1,     /* supportCopy */
         0},    /* Status byte offset */

        /*  FL_CONF_REG parameters   */
        /* eoc  rsa   rea  wea   caa */
        /* {0x4, 0x3, 0x1e, 0xe, 0x7f} */
        {0x4, 0x3, 0x3e, 0xe, 0x7f}			/* REA = 0x3e in DV */
    },

    {
        /* Flash type */
        {FL_SAMSUNG_ID, FL_SAMSUNG_64MB_ID},

        /* Command set and address byte phase */

        {0xff,            /* reset */
         FL_CMD_INVALID,  /* readSetup */
         0x0,             /* read */
         0x1,             /* readSecondHalf */
         0x50,            /* readSpare */
         FL_CMD_INVALID,  /* readForCopy */
         0x3,             /* readForMultiplane */
         0x80,            /* programSetup */
         0x10,            /* program */
         0x10,            /* programForCopy */
         0x11,            /* programMultiplane */
         FL_CMD_INVALID,  /* cache */
         0x8a,            /* copyBack */
         0x60,            /* eraseSetup */
         0x60,            /* eraseSetupMultiplane */
         0xd0,            /* erase */
         FL_CMD_INVALID,  /* randomOutput */
         FL_CMD_INVALID,  /* randomOutput */
         FL_CMD_INVALID,  /* randomInput */
         0x70,            /* readOpStatus */
         0x71,            /* readOpStatusMultiplane */
         0x1d},           /* addrBytePhase */

        /* Flash capability */
        {26,    /* totalSzShift */
         14,    /* erasableBlockSzShift */
         9,     /* pageSzShift */
         4,     /* pageSpareSzShift */
         2,     /* userSpareSzShift */
         4,     /* numPlanes */
         1,     /* supportCopy */
         5},    /* Status byte offset */

        /*  FL_CONF_REG parameters  */
        /* eoc  rsa   rea  wea  caa */
        {  0x4, 0x3, 0x1e, 0xe, 0x7f }
    },

    {
        {FL_SAMSUNG_ID, FL_SAMSUNG_128MB_ID},

        /* Command set and address byte phase */

        {0xff,            /* reset */
         0x00,            /* readSetup */
         0x30,            /* read */
         FL_CMD_INVALID,  /* readSecondHalf */
         FL_CMD_INVALID,  /* readSpare */
         0x35,            /* readForCopy */
         FL_CMD_INVALID,  /* readForMultiplane */
         0x80,            /* programSetup */
         0x10,            /* program */
         0x10,            /* programForCopy */
         FL_CMD_INVALID,  /* programMultiplane */
         0x15,            /* cache */
         0x85,            /* copyBack */
         0x60,            /* eraseSetup */
         FL_CMD_INVALID,  /* eraseSetupMultiplane */
         0xd0,            /* erase */
         0x05,            /* randomOutput */
         0xe0,            /* randomOutput */
         0x85,            /* randomInput */
         0x70,            /* readOpStatus */
         FL_CMD_INVALID,  /* readOpStatusMultiplane */
         0x0f},           /* addrBytePhase */

        /* Flash capability */
        {27,    /* totalSzShift */
         17,    /* erasableBlockSzShift */
         11,    /* pageSzShift */
         6,     /* pageSpareSzShift */
         5,     /* userSpareSzShift */
         1,     /* numPlanes */
         1,     /* supportCopy */
         0},    /* Status byte offset */

        /*  FL_CONF_REG parameters   */
        /* eoc  rsa   rea  wea   caa */
        {  0x3, 0x3, 0x1e, 0xe, 0x7f}
    },

    {
        {FL_SAMSUNG_ID, FL_SAMSUNG_256MB_ID},

        /* Command set and address byte phase */

        {0xff,            /* reset */
         0x00,            /* readSetup */
         0x30,            /* read */
         FL_CMD_INVALID,  /* readSecondHalf */
         FL_CMD_INVALID,  /* readSpare */
         0x35,            /* readForCopy */
         FL_CMD_INVALID,  /* readForMultiplane */
         0x80,            /* programSetup */
         0x10,            /* program */
         0x10,            /* programForCopy */
         FL_CMD_INVALID,  /* programMultiplane */
         0x15,            /* cache */
         0x85,            /* copyBack */
         0x60,            /* eraseSetup */
         FL_CMD_INVALID,  /* eraseSetupMultiplane */
         0xd0,            /* erase */
         0x05,            /* randomOutput */
         0xe0,            /* randomOutput */
         0x85,            /* randomInput */
         0x70,            /* readOpStatus */
         FL_CMD_INVALID,  /* readOpStatusMultiplane */
         0x1f},           /* addrBytePhase */

        /* Flash capability */
        {28,    /* totalSzShift */
         17,    /* erasableBlockSzShift */
         11,    /* pageSzShift */
         6,     /* pageSpareSzShift */
         5,     /* userSpareSzShift */
         1,     /* numPlanes */
         1,     /* supportCopy */
         0},    /* Status byte offset */

        /*  FL_CONF_REG parameters   */
        /* eoc  rsa   rea  wea   caa */
        {0x4, 0x3, 0x1e, 0xe, 0x7f}
    },

    {
        {FL_SAMSUNG_ID, FL_SAMSUNG_512MB_ID},

        /* Command set and address byte phase */

        {0xff,            /* reset */
         0x00,            /* readSetup */
         0x30,            /* read */
         FL_CMD_INVALID,  /* readSecondHalf */
         FL_CMD_INVALID,  /* readSpare */
         0x35,            /* readForCopy */
         FL_CMD_INVALID,  /* readForMultiplane */
         0x80,            /* programSetup */
         0x10,            /* program */
         0x10,            /* programForCopy */
         // 0x11,            /* programMultiplane */ 
         FL_CMD_INVALID,  /* programMultiplane */     
         FL_CMD_INVALID,  /* cache */
         0x85,            /* copyBack */
         0x60,            /* eraseSetup */
         // 0x60,            /* eraseSetupMultiplane */
         FL_CMD_INVALID,  /* eraseSetupMultiplane */  
         0xd0,            /* erase */
         0x05,            /* randomOutput */
         0xe0,            /* randomOutput */
         0x85,            /* randomInput */
         0x70,            /* readOpStatus */
         // 0x70,            /* readOpStatusMultiplane */
         FL_CMD_INVALID,  /* readOpStatusMultiplane */  
         0x1f},           /* addrBytePhase */

        /* Flash capability */
        {29,    /* totalSzShift */                      /* 512MB */
         17,    /* erasableBlockSzShift */              /* 128KB */
         11,    /* pageSzShift */                       /* 2KB */
         6,     /* pageSpareSzShift */                  /* 64B */
         5,     /* userSpareSzShift */                  /* 32B */
         2,     /* numPlanes */                         /* 4 planes? */
         1,     /* supportCopy */
         0},    /* Status byte offset */

        /*  FL_CONF_REG parameters   */
        /* eoc  rsa   rea  wea   caa */
        {0x4, 0x3, 0x3e, 0xe, 0x7f}			/* REA = 0x3e in DV */
    },

    {
        {FL_TOSHIBA_ID, FL_TOSHIBA_64MB_ID},

        /* Command set and address byte phase */

        {0xff,            /* reset */
         FL_CMD_INVALID,  /* readSetup */
         0x00,            /* read */
         0x01,            /* readSecondHalf */
         0x50,            /* readSpare */
         FL_CMD_INVALID,  /* readForCopy */
         FL_CMD_INVALID,  /* readForMultiplane */
         0x80,            /* programSetup */
         0x10,            /* program */
         FL_CMD_INVALID,  /* programForCopy */
         0x11,            /* programMultiplane */
         FL_CMD_INVALID,  /* cache */
         FL_CMD_INVALID,  /* copyBack */
         0x60,            /* eraseSetup */
         0x60,            /* eraseSetupMultiplane */
         0xd0,            /* erase */
         FL_CMD_INVALID,  /* randomOutput */
         FL_CMD_INVALID,  /* randomOutput */
         FL_CMD_INVALID,  /* randomInput */
         0x70,            /* readOpStatus */
         0x71,            /* readOpStatusMultiplane */
         0x1d},           /* addrBytePhase */

        /* Flash capability */
        {26,    /* totalSzShift */
         14,    /* erasableBlockSzShift */
         9,     /* pageSzShift */
         4,     /* pageSpareSzShift */
         2,     /* userSpareSzShift */
         4,     /* numPlanes */
         0,     /* supportCopy */
         5},    /* Status byte offset */

        /*  FL_CONF_REG parameters   */
        /* eoc  rsa   rea  wea   caa */
        {  0x4, 0x3, 0x1e, 0xe, 0x7f}
    },

    {
        {FL_TOSHIBA_ID, FL_TOSHIBA_128MB_ID},

        /* Command set and address byte phase */

        {0xff,            /* reset */
         0x00,            /* readSetup */
         0x30,            /* read */
         FL_CMD_INVALID,  /* readSecondHalf */
         FL_CMD_INVALID,  /* readSpare */
         FL_CMD_INVALID,  /* readForCopy */
         FL_CMD_INVALID,  /* readForMultiplane */
         0x80,            /* programSetup */
         0x10,            /* program */
         FL_CMD_INVALID,  /* programForCopy */
         FL_CMD_INVALID,  /* programMultiplane */
         FL_CMD_INVALID,  /* cache */
         FL_CMD_INVALID,  /* copyBack */
         0x60,            /* eraseSetup */
         FL_CMD_INVALID,  /* eraseSetupMultiplane */
         0xd0,            /* erase */
         0x05,            /* randomOutput */
         0xe0,            /* randomOutput */
         FL_CMD_INVALID,  /* randomInput */
         0x70,            /* readOpStatus */
         FL_CMD_INVALID,  /* readOpStatusMultiplane */
         0x0f},           /* addrBytePhase */

        /* Flash capability */
        {27,    /* totalSzShift */
         17,    /* erasableBlockSzShift */
         11,    /* pageSzShift */
         6,     /* pageSpareSzShift */
         5,     /* userSpareSzShift */
         1,     /* numPlanes */
         0,     /* supportCopy */
         0},    /* Status byte offset */

        /*  FL_CONF_REG parameters   */
        /* eoc  rsa   rea  wea   caa */
        {  0x3, 0x3, 0x1e, 0xe, 0x7f}
    },

    {
        {FL_TOSHIBA_ID, FL_TOSHIBA_256MB_ID},

        /* Command set and address byte phase */

        {0xff,            /* reset */
         0x00,            /* readSetup */
         0x30,            /* read */
         FL_CMD_INVALID,  /* readSecondHalf */
         FL_CMD_INVALID,  /* readSpare */
         FL_CMD_INVALID,  /* readForCopy */
         FL_CMD_INVALID,  /* readForMultiplane */
         0x80,            /* programSetup */
         0x10,            /* program */
         FL_CMD_INVALID,  /* programForCopy */
         FL_CMD_INVALID,  /* programMultiplane */
         FL_CMD_INVALID,  /* cache */
         FL_CMD_INVALID,  /* copyBack */
         0x60,            /* eraseSetup */
         FL_CMD_INVALID,  /* eraseSetupMultiplane */
         0xd0,            /* erase */
         0x05,            /* randomOutput */
         0xe0,            /* randomOutput */
         FL_CMD_INVALID,  /* randomInput */
         0x70,            /* readOpStatus */
         FL_CMD_INVALID,  /* readOpStatusMultiplane */
         0x1f},           /* addrBytePhase */

        /* Flash capability */
        {28,    /* totalSzShift */
         17,    /* erasableBlockSzShift */
         11,    /* pageSzShift */
         6,     /* pageSpareSzShift */
         5,     /* userSpareSzShift */
         1,     /* numPlanes */
         0,     /* supportCopy */
         0},    /* Status byte offset */

        /*  FL_CONF_REG parameters   */
        /* eoc  rsa   rea  wea   caa */
        {  0x4, 0x3, 0x1e, 0xe, 0x7f}
    }

};


/* Static functions */
static void                 __flRecordStats(u32, u32, IOSError);
static IOSError             __flCheckOpStatus(void);


/*
 *  Function: __flRecordStats
 *
 *  Description:
 *      This function records the statistics after a read/write/erase
 *      operation
 *
 *  Inputs:
 *      blockIndex - The logical block index where this operation was applied
 *      opType - The type of operation: erase, write, or read
 *      reason - The return code of the operation, IOS_ERROR_OK for success
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      None
 *
 */
static void
__flRecordStats(u32 blockIndex, u32 opType, IOSError reason)
{
    FL_ENTRY();

    if (reason == IOS_ERROR_OK) {
        if (opType == FL_OP_ERASE) {
            __flStats.numErasesSinceInit++;
        } else if (opType == FL_OP_WRITE) {
            __flStats.numWritesSinceInit++;
        } else if (opType == FL_OP_READ) {
            __flStats.numReadsSinceInit++;
        } else {        /* Copy operation */
            __flStats.numCopiesSinceInit++;
        }
    } else {
        u32     nextFailRecordIndex = 0;

        if (__flStats.failRecordNum == FL_FAILED_ENTRIES) {
            /*
             * No more free entries exist. From this point on,
             * the oldest entry will be over-written as each
             * new entry comes in
             */
            nextFailRecordIndex = __flStats.failRecordStart;
            __flStats.failRecordStart =
                    (__flStats.failRecordStart + 1) &
                        (FL_FAILED_ENTRIES - 1);
        } else {
            nextFailRecordIndex = __flStats.failRecordStart +
                                        __flStats.failRecordNum;

            __flStats.failRecordNum++;
        }

        __flStats.failRecord[nextFailRecordIndex].blockIndex = blockIndex;
        __flStats.failRecord[nextFailRecordIndex].opType = opType;
        __flStats.failRecord[nextFailRecordIndex].reason = reason;
    }

    FL_EXIT();
}


/*
 *  Function: __flCheckOpStatus
 *
 *  Description:
 *      This function checks the status after a write or erase operation
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_BADBLOCK - Operation status indicates a bad block
 *
 */
static IOSError
__flCheckOpStatus(void)
{
    IOSError    rc = IOS_ERROR_OK;
    u8          *opStatusBuf;

    FL_ENTRY();

    /* Status buffer needs to be FL_BASE_ALIGN_SZ aligned */
    opStatusBuf = __flBuf;

    /*
     * Check the operation status
     *  ad0=N/A, ad1=N/A, ma0=buffer, ma1=N/A
     *  adp=0x0, wdp=0, rdp=1, inten=0, ecc=0, rdy=0, sz=op_status
     */
    flSetMemAddr((u32)&opStatusBuf[0], FL_REG_ADDR_INVALID);
    rc = flExecCmd(__flDev.cmdSet.readOpStatus, 0x0, FL_CTRL_RDP,
                FL_BASE_ALIGN_SZ);
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Read operation status failed to complete"
                            " rc=%d\n", rc);
        goto __flCheckOpStatus_out;
    }

    /*
     * Translate opStatusBuf into opStatus. Operation failed
     * only if bit 0 of byte 0 is 1
     */
    if ((opStatusBuf[0] & 0x1) != 0) {
        rc = IOS_ERROR_BADBLOCK;
    }

__flCheckOpStatus_out:

    FL_EXIT();

    return (rc);
}


/*
 *  Function: flExecCmd
 *
 *  Description:
 *      This function issues a command by setting the FL_CTRL register.
 *      The address registers should be set appropriately before making
 *      this call. It will wait for the completion of the command before
 *      returning to the caller
 *
 *  Inputs:
 *      cmd - Command to be executed
 *      adp - Address byte phases
 *      opmask - Mask for WDP, RDP, INTEN, ECC, and RDY
 *      size - Size of transfer, 0 if command does not involve transfer
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_ACCESS - Memory violation
 *      IOS_ERROR_TIMEOUT - Timed out
 *
 */
IOSError
flExecCmd(u32 cmd, u32 adp, u32 opmask, u32 size)
{
    IOSError    rc = IOS_ERROR_OK;
    u32         flCtrlReg;

    FL_ENTRY();

    if (cmd == FL_CMD_INVALID) {
        flPrint(FL_DEBUG_ERROR, "Invalid command %d\n", cmd);

        rc = IOS_ERROR_INVALID;
        goto flExecCmd_out;
    }

    /* Issue the STOP command to clear the interrupt */
    if (opmask & FL_CTRL_MASK) {
        IO_WRITE(FL_CTRL_REG, 0x0);
    }

#ifndef IOS_ENABLE
    /* Turn off interrupt mask */
    opmask = opmask & ~FL_CTRL_MASK;
#endif

    /* Set the fields */
    flCtrlReg = (FL_CTRL_EXEC | (adp << FL_CTRL_ADP_SHIFT) | opmask |
            (cmd << FL_CTRL_CMD_SHIFT) | (size << FL_CTRL_SIZE_SHIFT));

#ifdef NET_CARD
    /* Flush the write buffer before issuing the command */
    IO_READ(L1_START);
#else
    /* TODO: Should optimize this */
#ifdef IOS_ENABLE
    IOS_FlushMem(IOS_WB_IOD);
    IOS_FlushMem(IOS_WB_FLA);
    IOS_InvalidateRdb(IOS_RB_IOD);
    IOS_InvalidateRdb(IOS_RB_FLA);
#else
    ahbMemFlush(IOS_WB_IOD);
    ahbMemFlush(IOS_WB_FLA);
    ahbMemRBInvalidate(IOS_RB_IOD);
    ahbMemRBInvalidate(IOS_RB_FLA);
#endif
#endif

    /* Execute the command */
    flPrint(FL_DEBUG_TRACE, "FL_CTRL_REG is 0x%x\n", flCtrlReg);
    IO_WRITE(FL_CTRL_REG, flCtrlReg);

    /* Poll for result or wait for interrupt */
    if ((opmask & FL_CTRL_MASK) == 0) {
        while (IO_READ(FL_CTRL_REG) & FL_CTRL_EXEC);
    } else {
#ifdef IOS_ENABLE
        IOSMessage   msg;

        rc = IOS_ReceiveMessage(__flMsgQId, &msg, IOS_MESSAGE_BLOCK);
        if ((rc != IOS_ERROR_OK) || (msg != FL_MSG_INTR)) { 
            flPrint(FL_DEBUG_ERROR, "Failed to retrieve message, rc=%d,"
                                " type=%d\n", rc, msg);

            /*
             * Something is terribly wrong here. Reset the
             * flash state and hope that things can recover
             */
            goto flExecCmd_reset_out;
        }
#else
            flPrint(FL_DEBUG_ERROR, "ERROR - No IOS support!\n");
#endif
    }

    /* Check for memory access violation */
    if (IO_READ(FL_CTRL_REG) & FL_CTRL_MVIOL) {
        flPrint(FL_DEBUG_ERROR, "Memory access violation\n");

        rc = IOS_ERROR_ACCESS;
        goto flExecCmd_reset_out;
    }

#ifndef NET_CARD
    /* TODO: Should optimize this */
#ifdef IOS_ENABLE
    IOS_FlushMem(IOS_WB_IOD);
    IOS_FlushMem(IOS_WB_FLA);
    IOS_InvalidateRdb(IOS_RB_IOD);
    IOS_InvalidateRdb(IOS_RB_FLA);
#else
    ahbMemFlush(IOS_WB_IOD);
    ahbMemFlush(IOS_WB_FLA);
    ahbMemRBInvalidate(IOS_RB_IOD);
    ahbMemRBInvalidate(IOS_RB_FLA);
#endif
#endif

    goto flExecCmd_out;

flExecCmd_reset_out:

    /* Reset the flash state */
    flCtrlReg = (FL_CTRL_EXEC | FL_CTRL_RDY |
            (FL_CMD_RESET << FL_CTRL_CMD_SHIFT));
    flPrint(FL_DEBUG_INFO, "Issue reset command 0x%x\n", flCtrlReg);
    IO_WRITE(FL_CTRL_REG, flCtrlReg);
    while (IO_READ(FL_CTRL_REG) & FL_CTRL_EXEC);

flExecCmd_out:

    FL_EXIT();

    return (rc);
}


void
flSetDevAddr(u32 ad0, u32 ad1)
{
    /* Set the address registers */
    if (ad0 != FL_REG_ADDR_INVALID) {
        IO_WRITE(FL_AD0_REG, ad0);
    }
    if (ad1 != FL_REG_ADDR_INVALID) {
        IO_WRITE(FL_AD1_REG, ad1);
    }
}


void
flSetMemAddr(u32 ma0, u32 ma1)
{
    if (ma0 != FL_REG_ADDR_INVALID) {
        IO_WRITE(FL_MA0_REG, CPU_TO_BUS_ADDR(ma0));
    }
    if (ma1 != FL_REG_ADDR_INVALID) {
        IO_WRITE(FL_MA1_REG, CPU_TO_BUS_ADDR(ma1));
    }
}


/*
 *  Function: flOpen
 *
 *  Description:
 *      This function initializes the flash and the device driver, and
 *      does nothing if the driver is already initialized
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_ACCESS - The flash controller rejected the operation
 *      IOS_ERROR_UNKNOWN - Unknown error
 *
 */
IOSError
flOpen(void)
{
    IOSError    rc = IOS_ERROR_OK;
    u32         flConfReg, numDev, count;
    u8          *flashID;
    FLDev       *dev_p;

    FL_ENTRY();

    if (__flReady) {
        goto flOpen_out;
    }

    /* Enable the flash controller with default timing parameters */
    flConfReg = IO_READ(FL_CONF_REG) | FL_CONF_DEV;
    IO_WRITE(FL_CONF_REG, flConfReg);

#ifdef IOS_ENABLE
    IOSMessage   msg;

    /* Message queue for handling flash interrupt */
    __flMsgQId = IOS_CreateMessageQueue(__flMsgQ, FL_MSG_QUEUE_SIZE);
    if (__flMsgQId < 0) {
        flPrint(FL_DEBUG_ERROR, "Failed to create flash message queue,"
                            " rc=%d\n", __flMsgQId);

        rc = IOS_ERROR_UNKNOWN;
        goto flOpen_create_out;
    }

    msg = FL_MSG_INTR;
    rc = IOS_HandleEvent(IOS_EVENT_FLASH, __flMsgQId, msg);
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Failed to register event for flash"
                            " message queue, rc=%d\n", rc);
        goto flOpen_handle_out;
    }
#endif

    /*
     * Reset
     *  ad0=N/A, ad1=N/A, ma0=N/A, ma1=N/A
     *  adp=0x0, wdp=0, rdp=0, inten=1, ecc=0, rdy=1, sz=0
     */
    rc = flExecCmd(FL_CMD_RESET, 0x0, (FL_CTRL_MASK | FL_CTRL_RDY), 0);
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Reset to flash failed, rc=%d\n", rc);
        goto flOpen_reset_out;
    }
    flPrint(FL_DEBUG_INFO, "Flash is resetted\n");

    /* Read ID buffer needs to be cacheline aligned */
    flashID = __flBuf;

    /*
     * Read the manufacturing ID
     *  ad0=0x0, ad1=N/A, ma0=buffer, ma1=N/A
     *  adp=0x1, wdp=0, rdp=1, inten=0, ecc=0, rdy=0, sz=id
     */
    flSetDevAddr(0x0, FL_REG_ADDR_INVALID);
    flSetMemAddr((u32) flashID, FL_REG_ADDR_INVALID);
    rc = flExecCmd(FL_CMD_READ_ID, 0x1, FL_CTRL_RDP, FL_BASE_ALIGN_SZ);
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Read ID failed to complete, rc=%d\n", rc);
        goto flOpen_reset_out;
    }

    /* Initialize driver data structures based on flash type */
    numDev = sizeof (devices) / sizeof (FLDev);
    for (count = 0; count < numDev; count++) {
        dev_p = &devices[count];

        if ((flashID[0] == dev_p->flashID.makerID) &&
                (flashID[1] == dev_p->flashID.deviceID)) {
            __flDev = *dev_p;

            /* Set config register */
            flConfReg = (__flDev.cfg.eoc << FL_CONF_EOC_SHIFT) | FL_CONF_DEV |
                    (__flDev.cfg.rsa << FL_CONF_RSA_SHIFT) |
                    (__flDev.cfg.rea << FL_CONF_REA_SHIFT) |
                    (__flDev.cfg.wea << FL_CONF_WEA_SHIFT) |
                    (__flDev.cfg.caa << FL_CONF_CAA_SHIFT);
            IO_WRITE(FL_CONF_REG, flConfReg);

#ifdef FL_DEBUG_LOG
            flPrint(FL_DEBUG_INFO, "\nDevice: MID:0x%x DID:0x%x\n", 
                __flDev.flashID.makerID, __flDev.flashID.deviceID);
            flPrint(FL_DEBUG_INFO, "Capabilities:\n"
                "\ttotalSzShift\t\t=%d\t-> Total size=%d\n"
                "\terasableBlockSzShift\t=%d\t-> Block size=%d\n"
                "\tpageSzShift\t\t=%d\t-> Page size=%d\n"
                "\tpageSpareSzShift\t=%d\t-> Page spare size=%d\n"
                "\tuserSpareSzShift\t=%d\t-> User spare size=%d\n"
                "\tnumPlanes\t\t=%d\n"
                "\tsupportCopy\t\t=%d\n"
                "\tstatusByteOffset\t=0x%x\n",
                __flDev.cap.totalSzShift, (1 << __flDev.cap.totalSzShift),
                __flDev.cap.erasableBlockSzShift, 
                    (1 << __flDev.cap.erasableBlockSzShift),
                __flDev.cap.pageSzShift, (1 << __flDev.cap.pageSzShift),
                __flDev.cap.pageSpareSzShift, 
                    (1 << __flDev.cap.pageSpareSzShift),
                __flDev.cap.userSpareSzShift, 
                    (1 << __flDev.cap.userSpareSzShift),
                __flDev.cap.numPlanes, __flDev.cap.supportCopy, 
                __flDev.cap.statusByteOffset);
        
            flPrint(FL_DEBUG_INFO, "Config: {eoc, rsa, rea, wea, caa }\n"
                "        {0x%x, 0x%x, 0x%x, 0x%x, 0x%x}\n",
                __flDev.cfg.eoc, __flDev.cfg.rsa, __flDev.cfg.rea,
                __flDev.cfg.wea, __flDev.cfg.caa);
#endif

            break;
        }
    }
    if (count == numDev) {
        flPrint(FL_DEBUG_ERROR, "Unsupported device type - MID:0x%x,"
                            " DID:0x%x\n", flashID[0], flashID[1]);

        rc = IOS_ERROR_UNKNOWN;
        goto flOpen_reset_out;
    }

    /* Initialize statistics structure */
    __flStats.numErasesSinceInit = 0;
    __flStats.numWritesSinceInit = 0;
    __flStats.numReadsSinceInit = 0;
    __flStats.failRecordStart = 0;
    __flStats.failRecordNum = 0;

    /* Set flash device driver ready for other operations */
    __flReady = 1;
    goto flOpen_out;

    /* Initialize resource manager contexts */
    for (count = 0; count < FL_RESRC_MGR_NUMCTX; count++) {
        __flCtx[count].inUse = 0;
    }

flOpen_reset_out:

#ifdef IOS_ENABLE
    (void) IOS_UnhandleEvent(IOS_EVENT_FLASH);

flOpen_handle_out:

    (void) IOS_DestroyMessageQueue(__flMsgQId);

flOpen_create_out:

#endif

    /* Disable the flash */
    IO_WRITE(FL_CONF_REG, IO_READ(FL_CONF_REG) & ~FL_CONF_DEV);

flOpen_out:

    FL_EXIT();

    return (rc);
}


/*
 *  Function: flGetCap
 *
 *  Description:
 *      This function retrieves the capability of the flash
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      cap - The capability
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_INVALID - Invalid input parameters
 *      IOS_ERROR_NOTREADY - The device driver is not initialized
 *
 */
IOSError
flGetCap(FLDevCap *cap)
{
    IOSError    rc = IOS_ERROR_OK;

    FL_ENTRY();

    if (cap == NULL) {
        flPrint(FL_DEBUG_ERROR, "Invalid input parameters\n");

        rc = IOS_ERROR_INVALID;
        goto flGetCap_out;
    }

    if (__flReady == 0) {
        flPrint(FL_DEBUG_ERROR, "Flash device driver not initialized\n");

        rc = IOS_ERROR_NOTREADY;
        goto flGetCap_out;
    }

    memcpy(cap, &__flDev.cap, sizeof (FLDevCap));

flGetCap_out:

    FL_EXIT();

    return (rc);
}

/*
 *  Function: flGetId
 *
 *  Description:
 *      This function retrieves the flash ID
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      id - The flash manufacturer and device ID
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_INVALID - Invalid input parameters
 *      IOS_ERROR_NOTREADY - The device driver is not initialized
 *
 */
IOSError
flGetId(FLIdentifier *id)
{
    IOSError    rc = IOS_ERROR_OK;

    FL_ENTRY();

    if (id == NULL) {
        flPrint(FL_DEBUG_ERROR, "Invalid input parameters\n");

        rc = IOS_ERROR_INVALID;
        goto flGetId_out;
    }

    if (__flReady == 0) {
        flPrint(FL_DEBUG_ERROR, "Flash device driver not initialized\n");

        rc = IOS_ERROR_NOTREADY;
        goto flGetId_out;
    }

    memcpy(id, &__flDev.flashID, sizeof(FLIdentifier));

flGetId_out:

    FL_EXIT();

    return (rc);
}

/*
 *  Function: flWritePage
 *
 *  Description:
 *      This function writes the buffer and spare area to the specified
 *      page in the flash
 *
 *  Inputs:
 *      pageIndex - The index of the page to be written
 *      buf - 512B/2KB data buffer to be written to the flash
 *      spare - 16B/64B spare data buffer to be written to the flash
 *      cache - 1 to use cache programming, 0 to use normal program
 *      ecc - 1 to enable ECC, 0 otherwise
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_INVALID - Invalid input parameters
 *      IOS_ERROR_NOTREADY - The device driver is not initialized
 *      IOS_ERROR_ACCESS - The flash controller rejected the operation
 *      IOS_ERROR_BADBLOCK - Bad block status is detected
 *
 */
IOSError
flWritePage(u32 pageIndex, const u8 *buf, const u8 *spare, u32 cache, u32 ecc)
{
    IOSError    rc = IOS_ERROR_OK;
    u32         totalEccSize, program_cmd;
    u8          *spareBuf;

    FL_ENTRY();

    if ((pageIndex >=
        (1 << (__flDev.cap.totalSzShift - __flDev.cap.pageSzShift))) ||
            (buf == NULL)) {
        flPrint(FL_DEBUG_ERROR, "Invalid input parameters\n");

        rc = IOS_ERROR_INVALID;
        goto flWritePage_out;
    }

    if (__flReady == 0) {
        flPrint(FL_DEBUG_ERROR, "Flash device driver not initialized\n");

        rc = IOS_ERROR_NOTREADY;
        goto flWritePage_out;
    }

    /* Cache programming is only supported on the Samsung 128MB flash */
    if ((cache) && (__flDev.cmdSet.cache == FL_CMD_INVALID)) {
        cache = 0;      /* Turn off cache programming */
    }
    if (cache) {
        program_cmd = __flDev.cmdSet.cache;
    } else {
        program_cmd = __flDev.cmdSet.program;
    }

    /* Spare buffer needs to be FL_SPARE_ALIGN_SZ aligned */
    spareBuf = FL_ALIGN_BUF(__flSpareBuf, FL_SPARE_ALIGN_SZ);

    /*
     * The flash controller requires a 128-byte aligned spare buffer
     * in order to return the computed ECC
     */
    if (spare) {
        memcpy(spareBuf, spare, (1 << __flDev.cap.pageSpareSzShift));
    } else {
        memset(spareBuf, 0, (1 << __flDev.cap.pageSpareSzShift));
    }
    spareBuf[__flDev.cap.statusByteOffset] = FL_STATUS_GOOD;

    /*
     * Program setup
     *  ad0=0x0, ad1=pageIndex, ma0=buf, ma1=spareBuf
     *  adp=normal, wdp=1, rdp=0, inten=1, ecc=1, rdy=0, sz=data
     */
    flSetDevAddr(0, pageIndex);
    flSetMemAddr((u32)buf, (u32) spareBuf);
    rc = flExecCmd(__flDev.cmdSet.programSetup, __flDev.cmdSet.addrBytePhase,
                (FL_CTRL_WDP | FL_CTRL_MASK | (ecc ? FL_CTRL_ECC : 0)),
                (1 << __flDev.cap.pageSzShift));
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Program setup failed to complete"
                            " rc=%d\n", rc);
        goto flWritePage_out;
    }

    /* Copy the ECC into the spare area */
    if (ecc) {
        totalEccSize = FL_ECC_SIZE <<
                    (__flDev.cap.pageSzShift - FL_ECC_UNIT_SHIFT);
        memcpy(&spareBuf[(1 << __flDev.cap.pageSpareSzShift) - totalEccSize],
            &spareBuf[FL_SPARE_ECC_OFFSET], totalEccSize);
    }

    if (spare || ecc) {
        if (__flDev.cmdSet.randomInput == FL_CMD_INVALID) {
            u32     ad0 = 0x0;

            /*
             * Program or cache data
             *  ad0=N/A, ad1=N/A, ma0=N/A, ma1=N/A
             *  adp=0x0, wdp=0, rdp=0, inten=1, ecc=0, rdy=1, sz=0
             */
             rc = flExecCmd(program_cmd, 0x0, (FL_CTRL_MASK | FL_CTRL_RDY), 0);
             if (rc != IOS_ERROR_OK) {
                flPrint(FL_DEBUG_ERROR, "Program operation failed, rc=%d\n",
                                        rc);
                goto flWritePage_out;
            }

            /* Check operation status for program */
            if (!cache) {
                rc = __flCheckOpStatus();
                if (rc != IOS_ERROR_OK) {
                    flPrint(FL_DEBUG_ERROR, "Bad op status for page %d,"
                                        " rc=%d\n", pageIndex, rc);
                    goto flWritePage_out;
                }
            }

            if (__flDev.cmdSet.readSpare != FL_CMD_INVALID) {
                /*
                 * Set the column address selector to point to the spare
                 *  ad0=N/A, ad1=N/A, ma0=N/A, ma1=N/A
                 *  adp=0x0, wdp=0, rdp=0, inten=0, ecc=0, rdy=0, sz=0
                 */
                rc = flExecCmd(__flDev.cmdSet.readSpare, 0, 0, 0);
                if (rc != IOS_ERROR_OK) {
                    flPrint(FL_DEBUG_ERROR, "Point to spare failed to complete,"
                                        " rc=%d\n", rc);
                    goto flWritePage_out;
                }
            } else {
                ad0 = 1 << __flDev.cap.pageSzShift;
            }

            /*
             * Program setup for spare area
             *  ad0=ad0, ad1=pageIndex, ma0=spareBuf, ma1=N/A
             *  adp=normal, wdp=1, rdp=0, inten=1, ecc=0, rdy=0, sz=spare
             */
            flSetDevAddr(ad0, pageIndex);
            flSetMemAddr((u32) spareBuf, FL_REG_ADDR_INVALID);
            rc = flExecCmd(__flDev.cmdSet.programSetup, 
                        __flDev.cmdSet.addrBytePhase,
                        (FL_CTRL_WDP | FL_CTRL_MASK),
                        (1 << __flDev.cap.pageSpareSzShift));
            if (rc != IOS_ERROR_OK) {
                flPrint(FL_DEBUG_ERROR, "Program setup failed to complete,"
                                    " rc=%d\n", rc);
                goto flWritePage_out;
            }
        } else {
            /*
             * Random input for spare area
             *  ad0=page_sz, ad1=N/A, ma0=spareBuf, ma1=N/A
             *  adp=column_addr, wdp=1, rdp=0, inten=1, ecc=0, rdy=0, sz=spare
             */
            flSetDevAddr((1 << __flDev.cap.pageSzShift), FL_REG_ADDR_INVALID);
            flSetMemAddr((u32) spareBuf, FL_REG_ADDR_INVALID);
            rc = flExecCmd(__flDev.cmdSet.randomInput,
                        __flDev.cmdSet.addrBytePhase & 0x3,
                        (FL_CTRL_WDP | FL_CTRL_MASK),
                        (1 << __flDev.cap.pageSpareSzShift));
            if (rc != IOS_ERROR_OK) {
                flPrint(FL_DEBUG_ERROR, "Random input failed to complete,"
                                    " rc=%d\n", rc);
                goto flWritePage_out;
            }
        }
    }

    /*
     * Program or cache data 
     *  ad0=N/A, ad1=N/A, ma0=N/A, ma1=N/A
     *  adp=0x0, wdp=0, rdp=0, inten=1, ecc=0, rdy=1, sz=0
     */
    rc = flExecCmd(program_cmd, 0x0, (FL_CTRL_MASK | FL_CTRL_RDY), 0);
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Program failed to complete, rc=%d\n", rc);
        goto flWritePage_out;
    }

    /* Check operation status for program */
    if (!cache) {
        rc = __flCheckOpStatus();
        if (rc != IOS_ERROR_OK) {
            flPrint(FL_DEBUG_ERROR, "Bad op status for spare of page %d,"
                            " rc=%d\n", pageIndex, rc);
            goto flWritePage_out;
        }
    }

    if ((spare || ecc) && (__flDev.cmdSet.randomInput == FL_CMD_INVALID) &&
            (__flDev.cmdSet.readSpare != FL_CMD_INVALID)) {
        /*
         * Set the column address selector to point to the beginning
         *  ad0=N/A, ad1=N/A, ma0=N/A, ma1=N/A
         *  adp=0x0, wdp=0, rdp=0, inten=0, ecc=0, rdy=0, sz=0
         */
        rc = flExecCmd(__flDev.cmdSet.read, 0, 0, 0);
        if (rc != IOS_ERROR_OK) {
            flPrint(FL_DEBUG_ERROR, "Point to beginning failed to complete,"
                                " rc=%d\n", rc);
            goto flWritePage_out;
        }
    }

flWritePage_out:

    /* Record statistics */
    __flRecordStats((pageIndex >>
                (FL_LOGI_BLOCK_SIZE_SHIFT - __flDev.cap.pageSzShift)),
                FL_OP_WRITE, rc);

    FL_EXIT();

    return (rc);
}


/*
 *  Function: flReadPage
 *
 *  Description:
 *      This function reads data from the specified flash page to the
 *      buffer and spare area in memory
 *
 *  Inputs:
 *      pageIndex - The source page index on flash
 *
 *  Outputs:
 *      buf - 512B/2KB destination buffer
 *      spare - 16B/64B spare area buffer
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_INVALID - Invalid input parameters
 *      IOS_ERROR_NOTREADY - The device driver is not initialized
 *      IOS_ERROR_ACCESS - The flash controller rejected the operation
 *      IOS_ERROR_ECC - Single bit ECC error is detected and repaired
 *      IOS_ERROR_ECC_CRIT - Multi-bit ECC error is detected
 *
 */
IOSError
flReadPage(u32 pageIndex, u8 *buf, u8 *spare)
{
    IOSError    rc = IOS_ERROR_OK;
    u8          *spareBuf;
    u32         adp = 0x0, eccCount, totalEccSize;

    FL_ENTRY();

    if ((pageIndex >=
                (1 << (__flDev.cap.totalSzShift - __flDev.cap.pageSzShift))) ||
            (buf == NULL)) {
        flPrint(FL_DEBUG_ERROR, "Invalid input parameters\n");

        rc = IOS_ERROR_INVALID;
        goto flReadPage_out;
    }

    if (__flReady == 0) {
        flPrint(FL_DEBUG_ERROR, "Flash device driver not initialized\n");

        rc = IOS_ERROR_NOTREADY;
        goto flReadPage_out;
    }

    /* Spare buffer needs to be FL_SPARE_ALIGN_SZ aligned */
    spareBuf = FL_ALIGN_BUF(__flSpareBuf, FL_SPARE_ALIGN_SZ);

    flSetDevAddr(0, pageIndex);
    if (__flDev.cmdSet.readSetup != FL_CMD_INVALID) {
        /*
         * Setup read 
         *  ad0=0, ad1=pageIndex, ma0=N/A, ma1=N/A
         *  adp=normal, wdp=0, rdp=0, inten=0, ecc=0, rdy=0, sz=0
         */
        rc = flExecCmd(__flDev.cmdSet.readSetup, __flDev.cmdSet.addrBytePhase,
                    0x0, 0);
        if (rc != IOS_ERROR_OK) {
            flPrint(FL_DEBUG_ERROR, "Read setup failed to complete,"
                                " rc=%d\n", rc);
            goto flReadPage_out;
        }
    } else {
        /* Only need ADP in the read command if there's no read setup */
        adp = __flDev.cmdSet.addrBytePhase;
    }

    /*
     * Read data
     *  ad0=0, ad1=pageIndex, ma0=buf, ma1=spareBuf
     *  adp=0x0 or normal, wdp=0, rdp=1, inten=1, ecc=1, rdy=1, sz=data+spare
     */
    flSetMemAddr((u32)buf, (u32) spareBuf);
    rc = flExecCmd(__flDev.cmdSet.read, adp,
                (FL_CTRL_RDP | FL_CTRL_MASK | FL_CTRL_ECC | FL_CTRL_RDY),
                (1 << __flDev.cap.pageSzShift) +
                    (1 << __flDev.cap.pageSpareSzShift));
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Read failed to complete, rc=%d\n", rc);
        goto flReadPage_out;
    }

    /*
     * The flash controller requires a 128-byte aligned spare buffer
     * in order to return the computed ECC
     */
    if (spare) {
        memcpy(spare, spareBuf, (1 << __flDev.cap.pageSpareSzShift));
    }

    /*
     * Check ECC and repair if necessary. For each 512 bytes of
     * data, there are 2 12-bit syndromes, each occupying the
     * least signficant 12 bits within a 16-bit half word
     */
    totalEccSize = FL_ECC_SIZE <<
                (__flDev.cap.pageSzShift - FL_ECC_UNIT_SHIFT);
    if (memcmp(&spareBuf[FL_SPARE_ECC_OFFSET],
            &spareBuf[(1 << __flDev.cap.pageSpareSzShift) - totalEccSize],
            totalEccSize) == 0) {
        /* ECC check passed, exit */
        rc = IOS_ERROR_OK;
        goto flReadPage_out;
    }

    for (eccCount = 0; eccCount <
            (1 << (__flDev.cap.pageSzShift - FL_ECC_UNIT_SHIFT));
            eccCount++) {
        u32     eccResult, eccOffset;
        u32     eccStored, eccComputed;

        eccOffset = eccCount * FL_ECC_SIZE;
        eccComputed = *((u32 *) &spareBuf[FL_SPARE_ECC_OFFSET + eccOffset]);
        eccStored = *((u32 *)
            &spareBuf[(1 << __flDev.cap.pageSpareSzShift) - totalEccSize +
                        eccOffset]);

        /* Check for bit errors */
        if (eccStored == eccComputed) {
            continue;
        }

        eccStored = FL_BYTE_SWAP(eccStored);
        eccComputed = FL_BYTE_SWAP(eccComputed);

        /* Result is XOR'ed together, and AND'ed out the unrelated bits */
        eccResult = ((eccStored ^ eccComputed) & 0x0fff0fff);
        if ((eccResult & (eccResult - 1)) == 0) {
            /* Single-bit error in ECC syndrome */
            rc = IOS_ERROR_ECC;
            continue;
        } else {
            u16     high, low;

            /* Check for single-bit error */
            high = eccResult >> 16;
            low = ((eccResult & 0x0000ffff) | 0xf000);
            if ((high ^ low) == 0x0000ffff) {       /* Single-bit error */
                u8      *dataPtr;

                /*
                 * Repair the error. Bits 0 to 2 indicate the bit location,
                 * bits 3 to 11 indicate the byte location
                 */
                dataPtr = ((u8 *)buf) + (eccCount * FL_ECC_UNIT);
                dataPtr[(high & 0x00000ff8) >> 3] ^= (1 << (high & 0x7));

                rc = IOS_ERROR_ECC;
                continue;
            } else {        /* Multi-bit error */
                rc = IOS_ERROR_ECC_CRIT;
                goto flReadPage_out; 
            }
        }
    }

flReadPage_out:

    /* Record statistics */
    __flRecordStats((pageIndex >>
                (FL_LOGI_BLOCK_SIZE_SHIFT - __flDev.cap.pageSzShift)),
                FL_OP_READ, rc);

    FL_EXIT();

    return (rc);
}


/*
 *  Function: flCopyPage
 *
 *  Description:
 *      This function does an internal page copy from the source
 *      page to the destination page without involving an external
 *      buffer
 *
 *  Inputs:
 *      source - The source page index on flash
 *      dest - The destination page index on flash
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_INVALID - Invalid input parameters
 *      IOS_ERROR_NOTREADY - The device driver is not initialized
 *      IOS_ERROR_ACCESS - The flash controller rejected the operation
 *      IOS_ERROR_BADBLOCK - Bad block status is detected
 *
 */
IOSError
flCopyPage(u32 source, u32 dest)
{
    IOSError    rc = IOS_ERROR_OK;
    u32         maxPage, read_cmd, adp = 0x0;

    FL_ENTRY();

    maxPage = (1 << (__flDev.cap.totalSzShift - __flDev.cap.pageSzShift));

    if ((source >= maxPage) || (dest >= maxPage) || (source == dest)) {
        flPrint(FL_DEBUG_ERROR, "Invalid input parameters %d, %d\n",
                            source, dest);

        rc = IOS_ERROR_INVALID;
        goto flCopyPage_out;
    }

    if (__flReady == 0) {
        flPrint(FL_DEBUG_ERROR, "Flash device driver not initialized\n");

        rc = IOS_ERROR_NOTREADY;
        goto flCopyPage_out;
    }

    if (__flDev.cmdSet.readSetup != FL_CMD_INVALID) {
        /*
         * Setup read 
         *  ad0=0, ad1=source, ma0=N/A, ma1=N/A
         *  adp=normal, wdp=0, rdp=0, inten=0, ecc=0, rdy=0, sz=0
         */
        flSetDevAddr(0, source);
        rc = flExecCmd(__flDev.cmdSet.readSetup, __flDev.cmdSet.addrBytePhase,
                    0x0, 0);
        if (rc != IOS_ERROR_OK) {
            flPrint(FL_DEBUG_ERROR, "Read setup failed to complete,"
                                " rc=%d\n", rc);
            goto flCopyPage_out;
        }
    } else {
        /* Only need ADP in the read command if there's no read setup */
        adp = __flDev.cmdSet.addrBytePhase;
    }

    /* Use readForCopy if available, otherwise just use read */
    read_cmd = __flDev.cmdSet.readForCopy;
    if (read_cmd == FL_CMD_INVALID) {
        read_cmd = __flDev.cmdSet.read;
    }

    /*
     * Read data without read data phase
     *  ad0=0, ad1=source, ma0=N/A, ma1=N/A
     *  adp=0x0 or normal, wdp=0, rdp=0, inten=1, ecc=0, rdy=1, sz=0
     */
    flSetDevAddr(0, source);
    rc = flExecCmd(read_cmd, adp, (FL_CTRL_MASK | FL_CTRL_RDY), 0);
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Read failed to complete, rc=%d\n", rc);
        goto flCopyPage_out;
    }

    /*
     * Copy back
     *  ad0=0, ad1=dest, ma0=N/A, ma1=N/A
     *  adp=normal, wdp=0, rdp=0, inten=0, ecc=0, rdy=0, sz=0
     */
    flSetDevAddr(0, dest);
    rc = flExecCmd(__flDev.cmdSet.copyBack, __flDev.cmdSet.addrBytePhase,
                0x0, 0);
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Copy-back failed to complete, rc=%d\n", rc);
        goto flCopyPage_out;
    }

    if (__flDev.cmdSet.programForCopy != FL_CMD_INVALID) {
        /*
         * Program the copy-back
         *  ad0=N/A, ad1=N/A, ma0=N/A, ma1=N/A
         *  adp=0x0, wdp=0, rdp=0, inten=1, ecc=0, rdy=1, sz=0
         */
        rc = flExecCmd(__flDev.cmdSet.program, 0,
                    (FL_CTRL_MASK | FL_CTRL_RDY), 0);
        if (rc != IOS_ERROR_OK) {
            flPrint(FL_DEBUG_ERROR, "Program failed to complete, rc=%d\n", rc);
            goto flCopyPage_out;
        }
    }

    /* Check the operation status */
    rc = __flCheckOpStatus();
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Bad op status for page %d, rc=%d\n",
                            dest, rc);
        goto flCopyPage_out;
    }

flCopyPage_out:

    /* Record statistics */
    __flRecordStats((dest >>
                (FL_LOGI_BLOCK_SIZE_SHIFT - __flDev.cap.pageSzShift)),
                FL_OP_COPY, rc);

    FL_EXIT();

    return (rc);
}


/*
 *  Function: flErase
 *
 *  Description:
 *      This function erases the flash block that contains the specified
 *      logical block
 *
 *  Inputs:
 *      blockIndex - The destination logical block index on flash
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_INVALID - Invalid input parameters
 *      IOS_ERROR_NOTREADY - The device driver is not initialized
 *      IOS_ERROR_ACCESS - The flash controller rejected the operation
 *      IOS_ERROR_BADBLOCK - Bad block status is detected
 *
 */
IOSError
flErase(u32 blockIndex)
{
    IOSError    rc = IOS_ERROR_OK;

    FL_ENTRY();

#ifdef FL_DEBUG_LOG
    flPrint(FL_DEBUG_INFO, "Block Index=%d, Total logical blocks=%d\n"
        "Logical block size=%d (shift=%d)\n",
        blockIndex, (1 << (__flDev.cap.totalSzShift-FL_LOGI_BLOCK_SIZE_SHIFT)),
        (1 << FL_LOGI_BLOCK_SIZE_SHIFT), FL_LOGI_BLOCK_SIZE_SHIFT);
#endif

    if (blockIndex >=
            (1 << (__flDev.cap.totalSzShift - FL_LOGI_BLOCK_SIZE_SHIFT))) {
        flPrint(FL_DEBUG_ERROR, "Invalid logical block index %d\n",
                            blockIndex);

        rc = IOS_ERROR_INVALID;
        goto flErase_out;
    }

    if (__flReady == 0) {
        flPrint(FL_DEBUG_ERROR, "Flash device driver not initialized\n");

        rc = IOS_ERROR_NOTREADY;
        goto flErase_out;
    }

    /*
     * Erase setup
     *  ad0=N/A, ad1=page, ma0=N/A, ma1=N/A
     *  adp=row_addr, wdp=0, rdp=0, inten=0, ecc=0, rdy=0, sz=0
     */
    flSetDevAddr(FL_REG_ADDR_INVALID,
        (blockIndex << (FL_LOGI_BLOCK_SIZE_SHIFT - __flDev.cap.pageSzShift)));
    rc = flExecCmd(__flDev.cmdSet.eraseSetup,
            (__flDev.cmdSet.addrBytePhase & 0x1c), 0x0, 0);
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Erase setup failed to complete,"
                            " rc=%d\n", rc);
        goto flErase_out;
    }

    /*
     * Erase command
     *  ad0=N/A, ad1=N/A, ma0=N/A, ma1=N/A
     *  adp=0x0, wdp=0, rdp=0, inten=1, ecc=0, rdy=1, sz=0
     */
    rc = flExecCmd(__flDev.cmdSet.erase, 0x0, (FL_CTRL_MASK | FL_CTRL_RDY), 0);
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Erase failed to complete, rc=%d\n", rc);
        goto flErase_out;
    }

    /* Check the operation status */
    rc = __flCheckOpStatus();
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Bad op status for block %d, rc=%d\n",
                            blockIndex, rc);
        goto flErase_out;
    }

flErase_out:

    /* Record statistics */
    __flRecordStats(blockIndex, FL_OP_ERASE, rc);

    FL_EXIT();

    return (rc);
}


/*
 *  Function: flWrite
 *
 *  Description:
 *      This function writes a logical block to the flash with the
 *      specified spare
 *
 *  Inputs:
 *      blockIndex - The destination logical block index on flash
 *      buf - The source buffer
 *      spare - The virtual 64B spare area to be written to the flash
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_INVALID - Invalid input parameters
 *      IOS_ERROR_NOTREADY - The device driver is not initialized
 *      IOS_ERROR_ACCESS - The flash controller rejected the operation
 *      IOS_ERROR_BADBLOCK - Bad block status is detected
 *
 */
IOSError
flWrite(u32 blockIndex, const u8 *buf, const u8 *spare)
{
    IOSError    rc = IOS_ERROR_OK;
    u32         pageCount, pageIndex, spareBasePage, pages;
    u8          spareBuf[FL_SPARE_ECC_OFFSET];  /* Largest possible spare */

    FL_ENTRY();

    if ((blockIndex >=
        (1 << (__flDev.cap.totalSzShift - FL_LOGI_BLOCK_SIZE_SHIFT))) ||
            (buf == NULL) || (spare == NULL)) {
        flPrint(FL_DEBUG_ERROR, "Invalid input parameters\n");

        rc = IOS_ERROR_INVALID;
        goto flWrite_out;
    }

    if (__flReady == 0) {
        flPrint(FL_DEBUG_ERROR, "Flash device driver not initialized\n");

        rc = IOS_ERROR_NOTREADY;
        goto flWrite_out;
    }

    /*
     * For the spare user data, only use the last N pages needed
     * to fill all 64 bytes of user spare data. The spareBasePage
     * will point to the first page whose spare area will be
     * used
     */
    pages = (1 << (FL_LOGI_BLOCK_SIZE_SHIFT - __flDev.cap.pageSzShift));
    pageIndex = blockIndex <<
                (FL_LOGI_BLOCK_SIZE_SHIFT - __flDev.cap.pageSzShift);
    spareBasePage = pages -
                    (1 <<
                (FL_VIRT_SPARE_SIZE_SHIFT - __flDev.cap.userSpareSzShift));

    for (pageCount = 0; pageCount < pages; pageCount++) {
        const void      *sparePtr = NULL;

        memset(spareBuf, 0, (1 << __flDev.cap.pageSpareSzShift));
        if (pageCount >= spareBasePage) {
            sparePtr = spare +
                    ((pageCount - spareBasePage) <<
                        __flDev.cap.userSpareSzShift);

            /* Skip all the bytes before the status byte */
            memcpy(&spareBuf[__flDev.cap.statusByteOffset + 1], sparePtr,
                (1 << __flDev.cap.userSpareSzShift));
        }

        /* Write a page at a time, use caching except for the last page */
        rc = flWritePage(pageIndex + pageCount,
                    buf + (pageCount << __flDev.cap.pageSzShift),
                    spareBuf, (pageCount != (pages - 1)), 1);
        if (rc != IOS_ERROR_OK) {
            flPrint(FL_DEBUG_ERROR, "Failed to write to page %d,"
                                " rc=%d\n", pageIndex + pageCount, rc);
            goto flWrite_out;
        }
    }

flWrite_out:

    FL_EXIT();

    return (rc);
}


/*
 *  Function: flRead
 *
 *  Description:
 *      This function reads a logical block from the flash along
 *      with the spare
 *
 *  Inputs:
 *      blockIndex - The source logical block index on flash
 *      buf - The destination buffer
 *      spare - The virtual spare area buffer
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_INVALID - Invalid input parameters
 *      IOS_ERROR_NOTREADY - The device driver is not initialized
 *      IOS_ERROR_ACCESS - The flash controller rejected the operation
 *      IOS_ERROR_ECC - Single bit ECC error is detected and repaired
 *      IOS_ERROR_ECC_CRIT - Multi-bit ECC error is detected
 *
 */
IOSError
flRead(u32 blockIndex, u8 *buf, u8 *spare)
{
    IOSError    rc = IOS_ERROR_OK, final_rc = IOS_ERROR_OK;
    u32         pageCount, pageIndex, spareBasePage, pages;
    u8          spareBuf[FL_SPARE_ECC_OFFSET];  /* Largest possible spare */

    FL_ENTRY();

    if ((blockIndex >= 
        (1 << (__flDev.cap.totalSzShift - FL_LOGI_BLOCK_SIZE_SHIFT))) ||
            (buf == NULL) || (spare == NULL)) {
        flPrint(FL_DEBUG_ERROR, "Invalid input parameters\n");

        rc = IOS_ERROR_INVALID;
        goto flRead_out;
    }

    if (__flReady == 0) {
        flPrint(FL_DEBUG_ERROR, "Flash device driver not initialized\n");

        rc = IOS_ERROR_NOTREADY;
        goto flRead_out;
    }

    /*
     * For the spare user data, only the last N pages are needed
     * to fill all 64 bytes of user spare data are used. The
     * spareBasePage will point to the first page whose spare area
     * is used
     */
    pages = (1 << (FL_LOGI_BLOCK_SIZE_SHIFT - __flDev.cap.pageSzShift));
    pageIndex = blockIndex <<
                (FL_LOGI_BLOCK_SIZE_SHIFT - __flDev.cap.pageSzShift);
    spareBasePage = pages -
                    (1 <<
                (FL_VIRT_SPARE_SIZE_SHIFT - __flDev.cap.userSpareSzShift));

    for (pageCount = 0; pageCount < pages; pageCount++) {
        void        *sparePtr = NULL;

        /* Read one page at a time */
        rc = flReadPage(pageIndex + pageCount,
                            buf + (pageCount << __flDev.cap.pageSzShift),
                            spareBuf);
        if ((rc != IOS_ERROR_OK) && (rc != IOS_ERROR_ECC) &&
                (rc != IOS_ERROR_ECC_CRIT)) {
            flPrint(FL_DEBUG_ERROR, "Failed to read from page %d,"
                                " rc=%d\n", pageIndex + pageCount, rc);
            goto flRead_out;
        }

        if (pageCount >= spareBasePage) {
            sparePtr = spare +
                    ((pageCount - spareBasePage) <<
                        __flDev.cap.userSpareSzShift);

            /* Skip all the bytes before the status byte */
            memcpy(sparePtr, &spareBuf[__flDev.cap.statusByteOffset + 1],
                    (1 << __flDev.cap.userSpareSzShift));
        }

        /* Return only the most serious error within the logical block */
        if ((rc == IOS_ERROR_ECC) && (final_rc != IOS_ERROR_ECC_CRIT)) {
            final_rc = IOS_ERROR_ECC;
        } else if (rc == IOS_ERROR_ECC_CRIT) {
            final_rc = IOS_ERROR_ECC_CRIT;
        }
    }

    rc = final_rc;

flRead_out:

    FL_EXIT();

    return (rc);
}


/*
 *  Function: flCopy
 *
 *  Description:
 *      This function copies data from one logical block to another
 *      logical block
 *
 *  Inputs:
 *      source - Source logical block
 *      dest - Destination logical block
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_INVALID - Invalid input parameters
 *      IOS_ERROR_NOTREADY - The device driver is not initialized
 *      IOS_ERROR_ACCESS - The flash controller rejected the operation
 *      IOS_ERROR_BADBLOCK - Bad block status is detected
 *
 */
IOSError
flCopy(u32 source, u32 dest)
{
    IOSError    rc = IOS_ERROR_OK;
    u32         maxBlock, pageCount, pages, sourceBasePage, destBasePage;
    u32         srcPlane, dstPlane;

    FL_ENTRY();

    maxBlock = (1 << (__flDev.cap.totalSzShift - FL_LOGI_BLOCK_SIZE_SHIFT));

    srcPlane = (source >>
            (__flDev.cap.erasableBlockSzShift - FL_LOGI_BLOCK_SIZE_SHIFT)) &
            (__flDev.cap.numPlanes - 1);
    dstPlane = (dest >>
            (__flDev.cap.erasableBlockSzShift - FL_LOGI_BLOCK_SIZE_SHIFT)) &
            (__flDev.cap.numPlanes - 1);
    if (!__flDev.cap.supportCopy || (srcPlane != dstPlane) ||
            (source >= maxBlock) || (dest >= maxBlock) || (source == dest)) {
        flPrint(FL_DEBUG_ERROR, "Invalid input parameters %d, %d\n",
                            source, dest);

        rc = IOS_ERROR_INVALID;
        goto flCopy_out;
    }

    if (__flReady == 0) {
        flPrint(FL_DEBUG_ERROR, "Flash device driver not initialized\n");

        rc = IOS_ERROR_NOTREADY;
        goto flCopy_out;
    }

    pages = (1 << (FL_LOGI_BLOCK_SIZE_SHIFT - __flDev.cap.pageSzShift));
    sourceBasePage = source * pages;
    destBasePage = dest * pages;

    for (pageCount = 0; pageCount < pages; pageCount++) {
        /* Copy a page at a time, use caching except for the last page */
        rc = flCopyPage(sourceBasePage + pageCount, destBasePage + pageCount);
        if (rc != IOS_ERROR_OK) {
            flPrint(FL_DEBUG_ERROR, "Failed to copy from page %d to page %d,"
                                " rc=%d\n", (sourceBasePage + pageCount),
                                (destBasePage + pageCount), rc);
            goto flCopy_out;
        }
    }

flCopy_out:

    FL_EXIT();

    return (rc);
}


/*
 *  Function: flGetStats
 *
 *  Description:
 *      This function retrieves statistics data from the flash device driver
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      stats - Device driver statistics
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_INVALID - Invalid input parameters
 *      IOS_ERROR_NOTREADY - The device driver is not initialized
 *
 */
IOSError
flGetStats(FLStats *stats)
{
    IOSError    rc = IOS_ERROR_OK;

    FL_ENTRY();

    if (stats == NULL) {
        flPrint(FL_DEBUG_ERROR, "Invalid input parameters\n");

        rc = IOS_ERROR_INVALID;
        goto flGetStats_out;
    }

    if (__flReady == 0) {
        flPrint(FL_DEBUG_ERROR, "Flash device driver not initialized\n");

        rc = IOS_ERROR_NOTREADY;
        goto flGetStats_out;
    }

    memcpy(stats, &__flStats, sizeof (FLStats));

flGetStats_out:

    FL_EXIT();

    return (rc);
}


/*
 *  Function: flStatus
 *
 *  Description:
 *      This function returns the flash block status
 *
 *  Inputs:
 *      16KB block index
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful and the flash block is good
 *      IOS_ERROR_INVALID - Invalid input parameters
 *      IOS_ERROR_NOTREADY - The device driver is not initialized
 *      IOS_ERROR_ACCESS - The flash controller rejected the operation
 *      IOS_ERROR_BADBLOCK - The flash block is bad
 *
 */
IOSError
flStatus(u32 blockIndex)
{
    IOSError    rc = IOS_ERROR_OK;
    u32         flashBlockIndex, pageIndex, pageCount;
    u8          *spareBuf;

    FL_ENTRY();

    if (blockIndex >=
            (1 << (__flDev.cap.totalSzShift - FL_LOGI_BLOCK_SIZE_SHIFT))) {
        flPrint(FL_DEBUG_ERROR, "Invalid input parameters\n");

        rc = IOS_ERROR_INVALID;
        goto flStatus_out;
    }

    if (__flReady == 0) {
        flPrint(FL_DEBUG_ERROR, "Flash device driver not initialized\n");

        rc = IOS_ERROR_NOTREADY;
        goto flStatus_out;
    }

    /* Spare buffer needs to be FL_SPARE_ALIGN_SZ aligned */
    spareBuf = FL_ALIGN_BUF(__flSpareBuf, FL_SPARE_ALIGN_SZ);

    /*
     * To check whether a logical block is bad, need to check
     * status byte in the spare area of page 0 and page 1 of the
     * flash block where this logical block belongs
     */
    flashBlockIndex = blockIndex >>
            (__flDev.cap.erasableBlockSzShift - FL_LOGI_BLOCK_SIZE_SHIFT);
    pageIndex = flashBlockIndex <<
            (__flDev.cap.erasableBlockSzShift - __flDev.cap.pageSzShift);

    for (pageCount = 0; pageCount < 2; pageCount++) {
        if (__flDev.cmdSet.readSpare != FL_CMD_INVALID) {
            /*
             * Read from the spare area
             *  ad0=0, ad1=page+count, ma0=spareBuf, ma1=N/A
             *  adp=normal, wdp=0, rdp=1, inten=1, ecc=0, rdy=1, sz=spare
             */
            flSetDevAddr(0, pageIndex + pageCount);
            flSetMemAddr((u32) spareBuf, FL_REG_ADDR_INVALID);
            rc = flExecCmd(__flDev.cmdSet.readSpare, 
                        __flDev.cmdSet.addrBytePhase,
                        (FL_CTRL_RDP | FL_CTRL_MASK | FL_CTRL_RDY),
                        (1 << __flDev.cap.pageSpareSzShift));
            if (rc != IOS_ERROR_OK) {
                flPrint(FL_DEBUG_ERROR, "Read spare failed to complete,"
                                    " rc=%d\n", rc);
                goto flStatus_out;
            }

            /*
             * Set the column address selector to point to the beginning
             *  ad0=N/A, ad1=N/A, ma0=N/A, ma1=N/A
             *  adp=0x0, wdp=0, rdp=0, inten=0, ecc=0, rdy=0, sz=0
             */
            rc = flExecCmd(__flDev.cmdSet.read, 0, 0, 0);
            if (rc != IOS_ERROR_OK) {
                flPrint(FL_DEBUG_ERROR, "Point to beginning failed to"
                                    " complete, rc=%d\n", rc);
                goto flStatus_out;
            }
        } else {
            /*
             * Read setup
             *  ad0=page_sz, ad1=page+count, ma0=N/A, ma1=N/A
             *  adp=normal, wdp=0, rdp=0, inten=0, ecc=0, rdy=0, sz=0
             */
            flSetDevAddr((1 << __flDev.cap.pageSzShift),
                            pageIndex + pageCount);
            rc = flExecCmd(__flDev.cmdSet.readSetup,
                        __flDev.cmdSet.addrBytePhase, 0x0, 0);
            if (rc != IOS_ERROR_OK) {
                flPrint(FL_DEBUG_ERROR, "Read setup failed to complete,"
                                   " rc=%d\n", rc);
                goto flStatus_out;
            }

            /*
             * Read data from flash
             *  ad0=N/A, ad1=N/A, ma0=spareBuf, ma1=N/A
             *  adp=0x0, wdp=0, rdp=1, inten=1, ecc=0, rdy=1, sz=spare
             */
            flSetMemAddr((u32) spareBuf, FL_REG_ADDR_INVALID);
            rc = flExecCmd(__flDev.cmdSet.read,
                        0x0, (FL_CTRL_RDP | FL_CTRL_MASK | FL_CTRL_RDY),
                        (1 << __flDev.cap.pageSpareSzShift));
            if (rc != IOS_ERROR_OK) {
                flPrint(FL_DEBUG_ERROR, "Read failed to complete, rc=%d\n",
                                    rc);
                goto flStatus_out;
            }
        }

        /*
         * Check status byte of the spare area. The flash block
         * is bad if the status byte is not 0xff
         */
        if (spareBuf[__flDev.cap.statusByteOffset] != FL_STATUS_GOOD) {
#if FL_DEBUG_LOG
            flPrint(FL_DEBUG_ERROR, "Invalid status byte =0x%08x, exp=0x%08x\n",
                spareBuf[__flDev.cap.statusByteOffset], FL_STATUS_GOOD);
#endif
            rc = IOS_ERROR_BADBLOCK;
            goto flStatus_out;
        }
    }

flStatus_out:

    FL_EXIT();

    return (rc);
}


/*
 *  Function: flClose
 *
 *  Description:
 *      This function de-initializes the device driver and the flash, and
 *      does nothing if the driver is not already initialized
 *
 *  Inputs:
 *      None
 *
 *  Outputs:
 *      None
 *
 *  Return values:
 *      IOS_ERROR_OK - Operation is successful
 *      IOS_ERROR_ACCESS - The flash controller rejected the operation
 *
 */
IOSError
flClose(void)
{
    IOSError    rc = IOS_ERROR_OK, final_rc = IOS_ERROR_OK;
    u32         count;

    FL_ENTRY();

#ifdef IOS_ENABLE
    /* Remove message queue */
    rc = IOS_UnhandleEvent(IOS_EVENT_FLASH);
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Failed to unregister event for flash"
                            " message queue, rc=%d\n", rc);

        final_rc = IOS_ERROR_UNKNOWN;

        /* Continue de-initialization anyways */
    }

    rc = IOS_DestroyMessageQueue(__flMsgQId);
    if (rc != IOS_ERROR_OK) {
        flPrint(FL_DEBUG_ERROR, "Failed to destroy flash message"
                            " queue, rc=%d\n", rc);

        final_rc = IOS_ERROR_UNKNOWN;

        /* Continue de-initialization anyways */
    }
#endif

    /* Disable the flash */
    IO_WRITE(FL_CONF_REG, IO_READ(FL_CONF_REG) & ~FL_CONF_DEV);

    __flReady = 0;

    /* Free all resource manager contexts */
    for (count = 0; count < FL_RESRC_MGR_NUMCTX; count++) {
        __flCtx[count].inUse = 0;
    }

    rc = final_rc;

    FL_EXIT();

    return (rc);
}


/*
 * Get a new flash context
 */
IOSError
flGetNextAvailCtx(void)
{
    IOSError    rc = IOS_ERROR_MAX;
    u32         count;

    for (count = 0; count < FL_RESRC_MGR_NUMCTX; count++) {
        if (__flCtx[count].inUse == 0) {
            __flCtx[count].inUse = 1;
            rc = (IOSError) &__flCtx[count];
            break;
        }
    }

    return (rc);
}


/*
 * Check if a given pointer is a valid flash context
 */
IOSError
flCtxCheck(void *ptr)
{
    IOSError    rc = IOS_ERROR_INVALID;

    if ((ptr >= (void *) &__flCtx[0]) &&
            (ptr <= (void *) &__flCtx[FL_RESRC_MGR_NUMCTX-1])) {
        rc = IOS_ERROR_OK;
    }

    return (rc);
}
