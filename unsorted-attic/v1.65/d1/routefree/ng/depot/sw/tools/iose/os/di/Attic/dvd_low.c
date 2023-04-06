#ident "$Id: dvd_low.c,v 1.64 2006/03/26 22:43:16 jprincen Exp $"
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
 * The lower part of the DI device driver.  This talks directly to the disk
 * drive.
 */

#include "iostypes.h"

#ifdef RVL
#include "hw.h"
#include "ioslibc.h"
#include "stdint.h"
#include "stdbool.h"
#else // ! defined(RVL)
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void IOS_ClearAndEnableDIIntr();
#endif

#include "ios.h"

#include "dvd.h"
#include "dvd_hw.h"
#include "dvd_driver.h"
#include "dvd_low.h"
#include "dvd_low_rvl.h"
#include "dvd_hw_reg.i"
#include "debug.h"

typedef enum transferMode {DMA, Immediate} transferMode_t;

enum commandReturn {commandSuccess, commandIOerror, commandCover};
typedef enum commandReturn      commandReturn_t;

const char        *timerErrorToString(const IOSTimerId errorId);
static IOSTimerId startTimedTransfer(IOSTime duration,
                                     const transferMode_t mode);
static void             clearTimeoutsFromQueue(IOSMessageQueueId queueId);
static diOtherMesg_t    timeoutMesg, resetTimeoutMesg;

uint32_t                driverLengthReg;
void                    debugPoint();
void                    doResetCommand(const uint32_t spinup);
static void             clearTimeoutsIntrFromQueue(IOSMessageQueueId queueId,
                                                   const int queueLen);

/*************************************************************/
/*
 * Assumes current command byte contents are 0 and words are
 * in big-endian format
 */

static inline void
setDiCommandByte(const uint8_t commandByte)
{
    uint32_t    tempVal;

    tempVal = readDICmdBuf0();
    tempVal |= (commandByte << 24);
    writeDICmdBuf0(tempVal);
}

static inline void
setDiReadSubCommandByte(const uint8_t subCommand)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= ((subCommand & 0x3) << 6);
    writeDICmdBuf0(tempVal);
}

static inline void
setDiEjectBit(const uint8_t bitValue)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= ((bitValue & 0x1) << 17);
    writeDICmdBuf0(tempVal);
}

static inline void
setDiSavingBit(const uint8_t bitValue)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= ((bitValue & 0x1) << 20);
    writeDICmdBuf0(tempVal);
}

static inline void
setDiAudioSubCode(const uint8_t value)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= ((value & 0x3) << 16);
    writeDICmdBuf0(tempVal);
}

static inline void
setDiAudioBufferSwitch(const uint8_t value)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= ((value & 0x1) << 16);
    writeDICmdBuf0(tempVal);
}

static inline void
setDiAudioBufferSize(const uint8_t value)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= (value & 0xF);
    writeDICmdBuf0(tempVal);
}

static inline void
setDiAudioBufferSequence(const uint8_t value)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= ((value & 0xF) << 28);
    writeDICmdBuf0(tempVal);
}

static inline void
setDiStartLSN(const uint32_t lsn)
{
    uint32_t    tempVal;

    tempVal  = lsn & 0xFFFFFF;
    writeDICmdBuf1(tempVal);
}

static inline void
setDiTransferLength(const uint32_t length)
{
    uint32_t    tempVal;

    tempVal  = length & 0xFFFFFF;
    writeDICmdBuf2(tempVal);
}

static inline void
setDiDVDStrm(const uint8_t strmVal)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= (strmVal & 0x1) << 15;
    writeDICmdBuf0(tempVal);
}

static inline void
setDiDVDRetry(const uint8_t retryVal)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= (retryVal & 0x1) << 14;
    writeDICmdBuf0(tempVal);
}

static inline void
setDiDVDConfigSet(const uint8_t setVal)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= (setVal & 0x1) << 16;
    writeDICmdBuf0(tempVal);
}

static inline void
setDiDVDConfigType(const uint8_t typeVal)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= (typeVal & 0xFF);
    writeDICmdBuf0(tempVal);
}

static inline void
setDiDVDConfigValue(const uint32_t value)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf1();
    tempVal |= (value & 0xFFFFFF);
    writeDICmdBuf1(tempVal);
}

static inline void
setDiDVDStructSubCmdByte(const uint8_t subCmd)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= (subCmd & 0xFF) << 16;
    writeDICmdBuf0(tempVal);
}

static inline void
setDiDVDStructLayer(const uint8_t layer)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= (layer & 0xFF) << 8;
    writeDICmdBuf0(tempVal);
}

static inline void
setDiReportKeyFormat(const uint8_t format)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= (format & 0xFF) << 16;
    writeDICmdBuf0(tempVal);
}

static inline void
setDiReportKeyLSN(const uint32_t lsn)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf1();
    tempVal |= (lsn & 0xFFFFFF);
    writeDICmdBuf1(tempVal);
}

static inline void
setDiOffsetSubCode(const uint8_t subCode)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= (subCode & 0x1) << 23;
    writeDICmdBuf0(tempVal);
}

static inline void
setDiSerMeasClr(const uint8_t clearVal)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= (clearVal & 0x1) << 17;
    writeDICmdBuf0(tempVal);
}

static inline void
setDiSerMeasENA(const uint8_t ENAVal)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= (ENAVal & 0x1) << 16;
    writeDICmdBuf0(tempVal);
}

static inline void
setDiMaxRotationSubcode(const uint8_t subCode)
{
    uint32_t    tempVal;

    tempVal  = readDICmdBuf0();
    tempVal |= (subCode & 0x3) << 16;
    writeDICmdBuf0(tempVal);
}

static inline void
setDiCommandWord1(const uint32_t command_word)
{
    writeDICmdBuf1(command_word);
}

static inline void
setDiCommandWord2(const uint32_t command_word)
{
    writeDICmdBuf2(command_word);
}

/*************************************************************/

void
diClearTransCompStatus(void)
{
    uint32_t    tempVal;

    tempVal  = readDIStatusForWrite();

#ifdef EMULATOR
    tempVal  &= ~DI_TRANS_COMPLETE_INTR;
#else
    /* In the real drive, a '1' is written to make the value '0' */
    tempVal  |= DI_TRANS_COMPLETE_INTR;
#endif
    writeDIStatus(tempVal);
}

/*************************************************************/

static inline void
diClearErrorStatus(void)
{
    uint32_t    tempVal;

    tempVal  = readDIStatusForWrite();

#ifdef EMULATOR
    tempVal  &= ~DI_ERROR_INTR;
#else
    /* In the real drive, a '1' is written to make the value '0' */
    tempVal  |= DI_ERROR_INTR;
#endif
    writeDIStatus(tempVal);
}

bool
isErrorInterruptSet(void)
{
    return((readDIStatus() & DI_ERROR_INTR) == 0 ? false : true);
}

/*************************************************************/

static inline void
diStartTransfer(const transferMode_t transferMode)
{
    if (transferMode == Immediate) {
        writeDIControl(DI_TRANSFER & ~DI_DMA_MODE);
    }
    else {
        writeDIControl(DI_TRANSFER | DI_DMA_MODE);
    }
    IOS_FlushMem(IOS_WB_IOD);
}

/*************************************************************/

void
diClearCoverIntr(void)
{
    uint32_t    tempVal;

    tempVal  = readDICoverRegForWrite();
#ifdef EMULATOR
    tempVal &= ~DI_COVER_INTR;
#else
    tempVal |=  DI_COVER_INTR;
#endif
    writeDICoverReg(tempVal);
}

/*************************************************************/

/*
 * IMPORTANT: MUST call IOS_InvalidateRdb shortly before calling
 *            this function and should call IOS_FlushMem soon after
 *            calling this function.
 *            We don't call the invalidate/flush in here so that
 *            calling code can do invalidate/flush once after
 *            changing many registers.
 */
void
enableCoverInterrupt(void)
{
    uint32_t    tempVal;

    tempVal  = readDICoverRegForWrite();
    tempVal |= DI_COVER_INTR_MASK;
    writeDICoverReg(tempVal);
}

/*************************************************************/

/*
 * IMPORTANT: MUST call IOS_InvalidateRdb shortly before calling
 *            this function and should call IOS_FlushMem soon after
 *            calling this function.
 *            We don't call the invalidate/flush in here so that
 *            calling code can do invalidate/flush once after
 *            changing many registers.
 */
void
disableCoverInterrupt(void)
{
    uint32_t    tempVal;

    tempVal     = readDICoverRegForWrite();
    tempVal    &= ~DI_COVER_INTR_MASK;
    writeDICoverReg(tempVal);
}

/*************************************************************/
/*
 * IMPORTANT: MUST call IOS_InvalidateRdb shortly before calling
 *            this function and should call IOS_FlushMem soon after
 *            calling this function.
 *            We don't call the invalidate/flush in here so that
 *            calling code can do invalidate/flush once after
 *            changing many registers.
 */
void
enableTransferCompleteIntr(void)
{
    uint32_t    tempVal;

    tempVal   = readDIStatusForWrite();
    tempVal  |= DI_TRANS_COMPLETE_INTR_MASK;
    writeDIStatus(tempVal);
}

/*************************************************************/

/*
 * IMPORTANT: MUST call IOS_InvalidateRdb shortly before calling
 *            this function and should call IOS_FlushMem soon after
 *            calling this function.
 *            We don't call the invalidate/flush in here so that
 *            calling code can do invalidate/flush once after
 *            changing many registers.
 */
void
enableErrorIntr(void)
{
    uint32_t    tempVal;

    tempVal   = readDIStatusForWrite();
    tempVal  |= DI_ERROR_INTR_MASK;
    writeDIStatus(tempVal);
}

/*************************************************************/

void
disableErrorIntr(void)
{
    uint32_t    tempVal;

    /*
    DPRINT2 ("(disableErrorIntr) Status value before: 0x%x\n",
	      readDIStatus());
    */
    tempVal   = readDIStatusForWrite();
    tempVal  &= ~DI_ERROR_INTR_MASK;
    writeDIStatus(tempVal);
    /*
    DPRINT2 ("(disableErrorIntr) Status value after: 0x%x\n",
	      readDIStatus());
    */
}
/*************************************************************/

bool
isTransCompInterruptSet(void)
{
    uint32_t    tempVal;

    tempVal = readDIStatus();
    if ((tempVal & DI_TRANS_COMPLETE_INTR) == 0) {
        return(false);
    }
    else {
        return(true);
    }
}

/*************************************************************/

bool
isCoverInterruptSet(void)
{
    uint32_t    tempVal;

    tempVal = readDICoverReg();
    if ((tempVal & DI_COVER_INTR) == 0) {
        return(false);
    }
    else {
        return(true);
    }
}

/*************************************************************/
inline int
IOPDiIntrEnabled(void)
{
    uint32_t	reg;

    reg  = busRd32(ACR_REGS_BASE + ACRIOPIRQINTEN_OFFSET + BUS_ENABLE_MASK);
    if ((reg & (1 << 18)) == 0) {
	return(0);
    }
    else {
        return(1);
    }
}
/*************************************************************/

/*
 * Set up the the drive register to handle the first transaction
 * after power up or reset.
 */
void
initializeDriveRegisters()
{
    uint32_t    diStatus;
    /*
     * FIXME - find out if we need to invalidate AHB buffers when
     * reading and writing drive registers.  Modify code here
     * and all other places if it isn't.
     */
    IOS_InvalidateRdb(IOS_RB_IOD);

    /*
     * The transaction complete and error interrupts shouldn't be set
     * after reset/power up, but sometimes they are.
     */ 
    diClearTransCompStatus();
    diClearErrorStatus();

    enableTransferCompleteIntr();
    enableErrorIntr();
    disableCoverInterrupt();

    diStatus = readDIStatus();
    if ((diStatus & DI_ERROR_INTR) != 0) {
        ERR_DPRINT("**** Error interrupt cannot be cleared after reset ****");
    }
    if ((diStatus & DI_TRANS_COMPLETE_INTR) != 0) {
        ERR_DPRINT("***** Trans complete interrupt cannot be cleared after reset ****");
    }

    IOS_ClearAndEnableDIIntr();

    IOS_FlushMem(IOS_WB_IOD);
}

/****************************************************************************/
/*
 * Check that the system state is what it should be before starting a 
 * transaction.  If the state is not OK, try to fix it up.  Verify
 * that the fix works.
 */
void
checkStateBeforeTransaction()
{
    uint32_t            errorIntr, errorIntrMask;
    uint32_t            diStatus;


    /* Make sure transaction interrupt is off */
    if ((readDIStatus() & DI_TRANS_COMPLETE_INTR) != 0) {
        /*
         * This could happen if the driver times out a transaction but
         * it eventually completes
         */
        DPRINT ("(checkState..) Warning: Transaction complete intr set\n");
        clearTimeoutsIntrFromQueue(dvdDriverInQueue, DVD_IN_QUEUE_LEN);
        diClearTransCompStatus();
        if ((readDIStatus() & DI_TRANS_COMPLETE_INTR) != 0) {
            diFatalError("(checkState...) Can't clear TC interrupt bit\n");
        }
    }

    /* Make sure transaction interrupt mask is on */
    if ((readDIStatus() & DI_TRANS_COMPLETE_INTR_MASK) == 0) {
        /* This should never happen */
        ERR_DPRINT ("(checkState..) ERROR: TC intr mask off - fixing\n");
        enableTransferCompleteIntr();
        if ((readDIStatus() & DI_TRANS_COMPLETE_INTR_MASK) == 0) {
            diFatalError("(checkState...) Can't enable TC interrupt mask\n");
        }
    }

    /*
     * Make sure that either the error interrupt is on, or the error
     * interrupt mask is enabled
     */
    diStatus      = readDIStatus();
    errorIntr     = diStatus & DI_ERROR_INTR;
    errorIntrMask = diStatus & DI_ERROR_INTR_MASK;
    if (errorIntr == 0 && errorIntrMask == 0) {
        ERR_DPRINT("(checkState...) Error interrupt mask and interrupt are off - correcting\n");
        enableErrorIntr();
    }
    else if (errorIntr != 0 && errorIntrMask != 0) {
        diFatalError("(checkState...) Error interrupt mask and interrupt are on - exit\n");
    }
    if (IOPDiIntrEnabled() == 0) {
        ERR_DPRINT("##### (checkState...) The kernel DI interrupt is disabled - fixing\n");
        IOS_ClearAndEnableDIIntr();
        if (IOPDiIntrEnabled() == 0) {
            diFatalError("(checkState...) Enabling kernel interrupts is broken");
        }
    }
} // checkStateBeforeTransaction

/****************************************************************************/

/*
 * RETURNS:
 *              DI_ERR_NO_ERROR          - if there was no error
 *              DI_ERR_TIMEOUT           - if there was a timeout error
 *              DI_ERR_HASH              - if there the hash values on disk
 *                                         did not verify.  This can only be
 *                                         returned if diCommand->theCommand
 *                                         is DI_READ_RVL_CMD
 *              DI_ERR_NONSPECIFIC       - if there was an error that was
 *                                         not a hash or timeout error
 */
uint32_t
handleDiCommand(const diCommand_t* const diCommand, void *outputPtr)
{
    IOSTimerId          commandTimeoutId;
    diInQueueMesg_t     inMesg, bufferedMesg;
    IOSError            receiveError;
    bool                commandTimedOut = false, commandTerminated = false;
    bool                transactionNeeded = false, isDmaCommand;
    bool                mesgIsBuffered = false, readImmReg = false;
    uint32_t            commandResult;

    /* It is not a problem when currentCommandNum wraps from 255 to 0 */
    currentCommandNum++;

    writeDICmdBuf0(0);

    DPRINT2("(handleDiCommand) Command is: 0x%x\n", diCommand->theCommand);

    commandResult = DI_ERR_NO_ERROR;

    isDmaCommand = false;

    checkStateBeforeTransaction();
    // DPRINT2("(handleDICommand) DIStatus(1): 0x%x\n", readDIStatus());

    /*
     * Disable PPC's access to the DI.
     * This cannot be done until after the PPC boots, because it
     * uses direct DI commands to boot.
     */

    uint32_t	reg;
    reg  = busRd32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK);
    reg  &= ~AIPPROT_ENAHBPI2DI_MASK;
    // DPRINT2("(handleDiCommand) Writing 0x%x to AIPPROT\n", reg);
    busWrt32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK, reg);

    switch (diCommand->theCommand) {

    case DI_NOTIFY_RESET_CMD:
        lastResetTime = IOS_GetTimer();
        resetTimeValid = true;
        resetDriverState();
        initializeDriveRegisters();
        break;

    case DI_RESET_CMD:
        doResetCommand(diCommand->arg[0]);
        transactionNeeded = false;
        break;

    case DI_AUDIO_STREAM_CMD:
        setDiCommandByte(DI_AUDIO_STREAM_CMD);
        setDiAudioSubCode(diCommand->arg[0]);
        setDiCommandWord1(diCommand->arg[2]);
        setDiCommandWord2(diCommand->arg[1]);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT,
                                              Immediate);
        transactionNeeded = true;
        break;
        
    case DI_AUDIO_REQUEST_STATUS_CMD:
        setDiCommandByte(DI_AUDIO_REQUEST_STATUS_CMD);
        setDiAudioSubCode(diCommand->arg[0]);
        setDiCommandWord1(0);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT,
                                              Immediate);
        transactionNeeded = true;
        break;

    case DI_AUDIO_BUF_CONFIG_CMD:
        setDiCommandByte(DI_AUDIO_BUF_CONFIG_CMD);
        setDiAudioBufferSwitch(diCommand->arg[0]);
        setDiAudioBufferSize(diCommand->arg[1]);
        setDiAudioBufferSequence(0);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT,
                                              Immediate);
        transactionNeeded = true;
        readImmReg = true;
        break;

    case DI_INQUIRY_CMD:
        setDiCommandByte(DI_INQUIRY_CMD);
        writeDIDmaDestAddr( (uint32_t) outputPtr);
        setDiCommandWord1(0);
        isDmaCommand = true;
        writeDILength(sizeof(DVDDriveInfo));
        driverLengthReg = sizeof(DVDDriveInfo);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT, DMA);
        transactionNeeded = true;
        break;

    case DI_OFFSET_CMD:
        setDiCommandByte(DI_OFFSET_CMD);
        setDiOffsetSubCode(diCommand->arg[0]);
        setDiCommandWord1(diCommand->arg[1]);
        diskState.lastDiskOffset = diCommand->arg[1];
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT,
                                              Immediate);
        transactionNeeded = true;
        readImmReg = true;
        break;

    /*
     * This reads the raw data from a RVL game disk only, not a GameCube
     * or DVD-Video disk.
     */

    case DI_READ_CMD:
        DPRINT3 ("(handleDICommand) DI_READ_CMD: Reading %u bytes into memory address 0x%x\n",
                  diCommand->arg[1], (uint32_t) outputPtr);
        setDiCommandByte(DI_READ_CMD);
        setDiReadSubCommandByte(DI_NORMAL_READ);
        setDiCommandWord1(diCommand->arg[2]);
        // Force disk address to 0.
        // setDiCommandWord1(0);
        setDiCommandWord2(diCommand->arg[1]);
        writeDIDmaDestAddr( (uint32_t) outputPtr);
        isDmaCommand    = true;
        writeDILength(diCommand->arg[1]);
        driverLengthReg = diCommand->arg[1];
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT, DMA);
        transactionNeeded = true;
        break;

    case DI_READ_DISK_ID_CMD:
        DPRINT("(handleDiCommand) Doing DI_READ_DISK_ID_CMD\n");
        setDiCommandByte(DI_READ_CMD);
        setDiReadSubCommandByte(DI_DISC_ID_READ);
        writeDIDmaDestAddr( (uint32_t) outputPtr);
        /*
         * CommandWord1 is the disk address to read.  This shouldn't
         * matter when reading the ID.
         */
        setDiCommandWord1(0);
        setDiCommandWord2(sizeof(DVDDiskID));
        isDmaCommand    = true;
        writeDILength(sizeof(DVDDiskID));
        driverLengthReg = sizeof(DVDDiskID);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT, DMA);
        transactionNeeded = true;
        break;

    case DI_READ_DISC_INFO_CMD:         /* AKA READ_DISK_BCA */
        setDiCommandByte(DI_READ_DISC_INFO_CMD);
        writeDIDmaDestAddr( (uint32_t) outputPtr);
        isDmaCommand    = true;
        writeDILength(sizeof(DVDDiskBca));
        driverLengthReg = sizeof(DVDDiskBca);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT, DMA);
        transactionNeeded = true;
        break;

    case DI_READ_DVD_CMD:
        setDiCommandByte(DI_READ_DVD_CMD);
        setDiDVDStrm(diCommand->arg[0]);
        setDiDVDRetry(diCommand->arg[1]);
        writeDIDmaDestAddr( (uint32_t) outputPtr);
        setDiCommandWord1(0);
        setDiStartLSN(diCommand->arg[4]);
        setDiTransferLength(diCommand->arg[3]);
        isDmaCommand    = true;
        writeDILength(diCommand->arg[3]);
        driverLengthReg = diCommand->arg[3];
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT, DMA);
        transactionNeeded = true;
        break;

    case DI_READ_DVD_CONFIG_CMD:
        setDiCommandByte(DI_READ_DVD_CONFIG_CMD);
        setDiDVDConfigSet(diCommand->arg[0]);
        setDiDVDConfigType(diCommand->arg[1]);
        setDiCommandWord1(0);
        setDiDVDConfigValue(diCommand->arg[2]);
        setDiCommandWord2(0);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT,
                                              Immediate);
        transactionNeeded = true;
        readImmReg = true;
        break;

    case DI_READ_DVD_PHYSICAL_CMD:
        setDiCommandByte(DI_READ_DVD_STRUCT_CMD);
        setDiDVDStructSubCmdByte(DI_DVD_STRUCT_PHYSICAL);
        setDiDVDStructLayer(diCommand->arg[1]);
        writeDIDmaDestAddr( (uint32_t) outputPtr);
        setDiCommandWord1(0);
        setDiCommandWord2(0);
        isDmaCommand    = true;
        writeDILength(sizeof(DVDVideoPhysical));
        driverLengthReg = sizeof(DVDVideoPhysical);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT, DMA);
        transactionNeeded = true;
        break;

    case DI_READ_DVD_COPYRIGHT_CMD:
        setDiCommandByte(DI_READ_DVD_STRUCT_CMD);
        setDiDVDStructSubCmdByte(DI_DVD_STRUCT_COPYRIGHT);
        setDiDVDStructLayer(diCommand->arg[0]);
        setDiCommandWord1(0);
        setDiCommandWord2(0);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT, Immediate);
        transactionNeeded = true;
        readImmReg = true;
        break;

    case DI_READ_DVD_DISC_KEY_CMD:
        setDiCommandByte(DI_READ_DVD_STRUCT_CMD);
        setDiDVDStructSubCmdByte(DI_DVD_STRUCT_DISC_KEY);
        setDiDVDStructLayer(diCommand->arg[1]);
        writeDIDmaDestAddr( (uint32_t) outputPtr);
        setDiCommandWord1(0);
        setDiCommandWord2(0);
        isDmaCommand    = true;
        writeDILength(sizeof(DVDVideoDiscKey));
        driverLengthReg = sizeof(DVDVideoDiscKey);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT, DMA);
        transactionNeeded = true;
        break;

    case DI_READ_RVL_CMD:
        commandResult = doRvlRead((uint8_t *) diCommand->arg[0],
                                              diCommand->arg[1],
                                              diCommand->arg[2]);
        if (commandResult == DI_ERR_NO_ERROR) {
            driverLengthReg = diCommand->arg[1];
        } else {
            driverLengthReg = 0;
        }
        DPRINT2 ("READ RVL result: 0x%x\n", commandResult);
        transactionNeeded = false;
        break;

    case DI_REPORT_KEY_CMD:
        setDiCommandByte(DI_REPORT_KEY_CMD);
        writeDIDmaDestAddr( (uint32_t) outputPtr);
        setDiReportKeyFormat(diCommand->arg[1]);
        setDiCommandWord1(0);
        setDiReportKeyLSN(diCommand->arg[2]);
        setDiCommandWord2(0);
        isDmaCommand    = true;
        writeDILength(sizeof(DVDVideoReportKey));
        driverLengthReg = sizeof(DVDVideoReportKey);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT, DMA);
        transactionNeeded = true;
        break;

    case DI_REQUEST_DISC_STATUS_CMD:
        setDiCommandByte(DI_REQUEST_DISC_STATUS_CMD);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT,
                                              Immediate);
        transactionNeeded = true;
        readImmReg = true;
        break;

    case DI_REQUEST_ERROR_CMD:
        setDiCommandByte(DI_REQUEST_ERROR_CMD);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT,
                                              Immediate);
        transactionNeeded = true;
        readImmReg = true;
        break;

    case DI_REQUEST_RETRY_NUMBER_CMD:
        setDiCommandByte(DI_REQUEST_RETRY_NUMBER_CMD);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT,
                                              Immediate);
        transactionNeeded = true;
        readImmReg = true;
        break;

    case DI_SEEK_CMD:
        setDiCommandByte(DI_SEEK_CMD);
        setDiCommandWord1(diCommand->arg[0]);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT,
                                              Immediate);
        transactionNeeded = true;
        break;

    case DI_SET_MAXIMUM_ROTATION_CMD:
        setDiCommandByte(DI_SET_MAXIMUM_ROTATION_CMD);
        setDiMaxRotationSubcode(diCommand->arg[0]);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT,
                                              Immediate);
        transactionNeeded = true;
        break;

    case DI_SER_MEAS_CONTROL_CMD:
        setDiCommandByte(DI_SER_MEAS_CONTROL_CMD);
        writeDIDmaDestAddr( (uint32_t) outputPtr);
        setDiSerMeasClr(diCommand->arg[1]);
        setDiSerMeasENA(diCommand->arg[2]);
        isDmaCommand    = true;
        writeDILength(sizeof(DVDLowDriveSer));
        driverLengthReg = sizeof(DVDLowDriveSer);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT, DMA);
        transactionNeeded = true;
        break;

    case DI_SET_SPINUP_FLAG_CMD:
        /* FIXME - Do something here */
        printf  ("******* Implement DI_SET_SPINUP_FLAG_CMD!!! *******\n");
        printf  ("***************************************************\n");
        commandResult = DI_ERR_NO_ERROR;
        break;

    case DI_STOP_LASER_CMD:
        setDiCommandByte(DI_STOP_LASER_CMD);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT,
                                              Immediate);
        transactionNeeded = true;
        readImmReg = true;
        break;

    case DI_STOP_MOTOR_CMD:
        setDiCommandByte(DI_STOP_MOTOR_CMD);
        setDiEjectBit(diCommand->arg[0]);
        setDiSavingBit(diCommand->arg[1]);
        commandTimeoutId = startTimedTransfer(DI_COMMAND_TIMEOUT,
                                              Immediate);
        transactionNeeded = true;
        readImmReg = true;
        break;

    case DI_WAIT_FOR_COVER_CLOSE_CMD:
        diFatalError("Should have been handled in DiIoctl!\n");
        break;

    default:
        ERR_DPRINT2("Unknown drive command '0x%x' encountered in handleDiCommand\n",
                     diCommand->theCommand);

        diFatalError("Unhandled command case in handleDiCommand");
        break;
    }

    if (transactionNeeded == false) {
        return(commandResult);
    }

    /*
     * Loop until we get a message back on the driver input queue
     * that tells us that the command succeeded, failed, or
     * timed out.
     */
    do {

        // DPRINT2("(handleDICommand) DIStatus(2): 0x%x\n", readDIStatus());
        DPRINT2 ("(handleDiCommand) Calling IOS_ReceiveMessage (queueId = %d)\n",
                 dvdDriverInQueue);

        receiveError = IOS_ReceiveMessage(dvdDriverInQueue,
                                          (IOSMessage *) &inMesg,
                                          IOS_MESSAGE_BLOCK);
        DPRINT ("(handleDiCommand) IOS_ReceiveMessage returns.\n");
        // DPRINT2("(handleDICommand) DIStatus(3): 0x%x\n", readDIStatus());
        if (receiveError != IOS_ERROR_OK) {
            diFatalError ("(handleDiCommand) Receiving message on DVD in queue failed\n");
        }

        /*
         * The next command after an error occurs is always DI_REQUEST_ERROR.
         * We need to re-enable error interrupts, because they were disabled
         * just after the error occurred.
         */


        IOS_InvalidateRdb(IOS_RB_IOD);
        if (diCommand->theCommand == DI_REQUEST_ERROR_CMD) {
            // TODO: Check if request error had an error and handle
            enableErrorIntr();
        }
        DPRINT2("(handleDiCommand) message type is: %d\n",
                  inMesg.otherMesg->mesgType);

        switch(inMesg.otherMesg->mesgType) {
        
        case DI_MESG_TIMEOUT:
            if (inMesg.otherMesg->commandNum == currentCommandNum) {
                DPRINT ("(handleDiCommand) **** Current command timed out ***\n");
                IOS_DestroyTimer(commandTimeoutId);
                commandTimedOut = true;
                if (isDmaCommand) {
                    driverLengthReg = 0;
                }
                commandResult = DI_ERR_TIMEOUT;
                commandTerminated = true;
            }
            else {
                DPRINT ("(handleDiCommand) Received time out for previous command - continuing\n");
            }
            break;

        case DI_MESG_INTR:
            DPRINT("(handleDiCommand) Got DI_MESG_INTR\n");  
            if (isTransCompInterruptSet()) {

                DPRINT2 ("(handleDiCommand) Stopping timer %u\n", commandTimeoutId);
                IOS_DestroyTimer(commandTimeoutId);
                clearTimeoutsFromQueue(dvdDriverInQueue);

                DPRINT ("(handleDiCommand) TC intr received\n");
                diClearTransCompStatus();
                commandResult = DI_ERR_NO_ERROR;
                commandTerminated = true;
                DPRINT ("(handleDiCommand) End of  TC intr handling\n");
            }
            else if (isErrorInterruptSet()) {
                DPRINT2 ("(handleDiCommand) Stopping timer %u\n",
                          commandTimeoutId);
                IOS_DestroyTimer(commandTimeoutId);
                clearTimeoutsFromQueue(dvdDriverInQueue);
                
                DPRINT ("(handleDiCommand) Error intr received\n");
                if (isDmaCommand) {
                    driverLengthReg = 0;
                }
                /*
                 * Must mask/disable error interrupt, because interrupt can only
                 * be cleared after error status bit is cleared
                 * AND a transaction happens.
                 */
                // disableErrorIntr();
                diClearErrorStatus();
                commandResult = DI_ERR_NONSPECIFIC;
                commandTerminated = true;
            }
            if (isCoverInterruptSet()) {
                DPRINT ("(handleDiCommand) Cover Interrupt Set\n");
                if (withinResetTime(DUMMY_COVER_INTR_TIME) == false) {
                    DPRINT ("Received cover interrupt message!\n");
                    if ((readDICoverReg() & DI_COVER_STATUS) == 0) {
                        coverWasClosed = true;
                        // Do resetDriverState() here?
                    }
                }
                diClearCoverIntr();
            }
            IOS_FlushMem(IOS_WB_IOD);
            // DPRINT("(handleDiCommand): Starting ClearAndEnableDiIntr\n");  
	    // DPRINT2("(handleDICommand) DIStatus before clear and enable: 0x%x\n", readDIStatus());
            IOS_ClearAndEnableDIIntr();
            // DPRINT("(handleDiCommand) : Done ClearAndEnableDiIntr\n");  
            break;              // case DI_MESG_INTR

        case IOS_IOCTL:
        case IOS_OPEN:
        case IOS_CLOSE:
            DPRINT ("(handleDiCommand) Got request from IPC - buffering message.\n");
            if (mesgIsBuffered == false) {
                diCommand_t  *comm;
                mesgIsBuffered  = true;
                bufferedMesg = inMesg;
                comm = (diCommand_t *) inMesg.resourceMesg->args.ioctl.inPtr;
                printf("(handleDiCommand) Buffering IPC Request: 0x%x\n", comm->theCommand);
            }
            else {
                diFatalError ("(handleDiCommand) Error: too many message commands\n");
            }
            break;
        
        default:
            {
                ERR_DPRINT2("(handleDiCommand) Unhandled message case (message = 0x%x)\n",
                        inMesg.otherMesg->mesgType);
                diFatalError ("(handleDiCommand) Unhandled message case\n");
                break;
            }
        } // switch

    } while (commandTerminated == false);

    if (readImmReg) {
        diRegVals_t      *regValPtr;

        regValPtr = (diRegVals_t *) outputPtr;
        regValPtr->ImmRegVal = readDIImmData();
    }

    if (   diCommand->theCommand == DI_READ_DISK_ID_CMD &&
           commandResult == DI_ERR_NO_ERROR) {

        DVDDiskID*      diskID;
        if (outputPtr == NULL) {
            ERR_DPRINT("(handleDiComand) !!!! OUTPUT PTR IS NULL !!!!\n");
        }
        diskID = (DVDDiskID *) outputPtr;
        if (diskID->rvlMagic == REVOLUTION_MAGIC) {
            printf ("(handleDiCommand) Found REVOLUTION disk\n");
            diskState.isRvlDisk = true;
            if (diskState.hashEncryptedValid == false) {
                commandResult = doReadHashEncryptedState();
            }
        }
        else {
            DPRINT ("(handleDiCommand) Found GAMECUBE disk\n");
        }
    }
    DPRINT2 ("(handleDiCommand) Returning 0x%x\n", commandResult);
    if (mesgIsBuffered) {
        IOSError        sendError;

        sendError = IOS_JamMessage(dvdDriverInQueue,
                                    (IOSMessage) bufferedMesg.otherMesg,
                                    IOS_MESSAGE_NOBLOCK);
        if (sendError != IOS_ERROR_OK) {
            diFatalError("(handleDiMessage) Can't send buffered message");
        }
        mesgIsBuffered = false;
    }
    return(commandResult);
} // handleDiCommand

/* ---------------------------------------------------------- */
void
debugPoint(void)
{
    printf ("Debug point\n");
}
/* ---------------------------------------------------------- */

/*
 * Do a raw disk read.
 * ASSUMES:
 *           length is a multiple of 32 - this comes from the
 *           specifics of the disk drive read itself.
 *           An assert checks for this, but asserts will be off
 *           for production...
 * RETURNS: what handleDiCommand returns.
 * 
 */

uint32_t
doRawDiskRead(uint8_t* const destAddr, const uint32_t length,
           const uint32_t wordOffset)
{
    diCommand_t         diCommand;
    uint32_t            commandResult;

    // assert ((length & 0x1F) == 0);

    DPRINT5 ("(doRawDiskRead): Reading %u bytes from disk byte address 0x%x/%u into buffer at 0x%x\n",
              length, wordOffset << 2, wordOffset << 2, (uint32_t) destAddr);
    diCommand.theCommand = DI_READ_CMD;
    diCommand.arg[0] = (uint32_t) destAddr;
    diCommand.arg[1] = length;
    diCommand.arg[2] = wordOffset;

    commandResult = handleDiCommand(&diCommand, destAddr);
    DPRINT2 ("(doRawDiskRead): Returning 0x%x\n", commandResult);
    return(commandResult);
} // doRawDiskRead

/* ---------------------------------------------------------- */

uint32_t            wordArray[8] __attribute__((aligned(32)));
/*
 * Clear the error interrupt by clearing the proper bit
 * and requesting the error from the drive.
 * RETURNS: the result from calling handleDiCommand
 */

uint32_t
clearDriveErrorInterrupt()
{
    diCommand_t         diCommand;
    uint32_t            commandResult;

    IOS_InvalidateRdb(IOS_RB_IOD);
    diClearErrorStatus();
    IOS_FlushMem(IOS_WB_IOD);

    diCommand.theCommand = DI_REQUEST_ERROR_CMD;

    commandResult = handleDiCommand(&diCommand, wordArray);
    return(commandResult);
}

/*************************************************************/

/*
 * Loop forever until we receive an interrupt message corresponding
 * to a cover status changed interrupt AND the cover is now closed.
 * NB: The interrupt happens whenever the cover status changes,
 *     not just when the cover is closed.
 */
void
doWaitForCoverClose(void)
{
    IOSError            receiveError;
    diInQueueMesg_t     inMesg;
    bool                done = false;

    enableCoverInterrupt();
    do {
        DPRINT("(doWaitForCoverClose) calling IOS_ReceiveMessage\n");
        receiveError = IOS_ReceiveMessage(dvdDriverInQueue,
                                          (IOSMessage *) &inMesg,
                                          IOS_MESSAGE_BLOCK);
        DPRINT("(doWaitForCoverClose) Received message\n");
        if (inMesg.otherMesg->mesgType == DI_MESG_INTR) {
            IOS_InvalidateRdb(IOS_RB_IOD);
            if (isTransCompInterruptSet()) {
		DPRINT("(doWaitForCoverClose) Got TC int - clearing it\n");
                diClearTransCompStatus();
            }
            if (isErrorInterruptSet()) {
		DPRINT("(doWaitForCoverClose) Got Error int - clearing it\n");
                clearDriveErrorInterrupt();
            }
            if (isCoverInterruptSet()) {
                if (withinResetTime(DUMMY_COVER_INTR_TIME) == false
                    && ((readDICoverReg() & DI_COVER_STATUS) == 0)) {
	            done = true;
                }
                diClearCoverIntr();
            }
            IOS_ClearAndEnableDIIntr();
        }
    } while (! done);

    disableCoverInterrupt();

    DPRINT("(doWaitForCoverClose) returning\n");
} // doWaitForCoverClose
/*************************************************************/
/*
 * Reset the drive, initialize associated driver state,
 * and clearing the cover interrupt
 */
void
doResetCommand(const uint32_t resetFlag)
{
    IOSError            receiveError;
    diInQueueMesg_t     inMesg;
    uint32_t            reg, time;
    IOSTimerId          sleepId;
    bool                coverInterruptWasEnabled;

    // !!!!!!!!!! FIXME !!!!!!!!!!!! need to set spinup flag
    /*
     * Resetting the drive causes false or 'dummy' cover
     * interrupts.  Make sure that cover interrupts are
     * disabled before we reset, and re-enable them
     * after reset if they were enabled going into this function
     */
    if ((readDICoverReg() & DI_COVER_INTR_MASK) == 0) {
        coverInterruptWasEnabled = false;
    }
    else {
        coverInterruptWasEnabled = true;
        disableCoverInterrupt();
    }

    /* Clear previous timeout, if any */
    receiveError = IOS_ReceiveMessage(dvdDriverSleepQueue,
                                      (IOSMessage *) &inMesg,
                                      IOS_MESSAGE_NOBLOCK);
    if (receiveError != IOS_ERROR_QEMPTY && receiveError != IOS_ERROR_OK) {
        diFatalError("(doResetCommand) ReceiveMessage #1 failed");
    }

    /*
     * Reset the drive by activating the reset signal, waiting
     * for the reset hold time, deactivating the reset signal,
     * then waiting until the drive register become writable again
     */

    /* Activate reset signal */
    reg = busRd32(ACR_REGS_BASE + ACRRSTCTRL_OFFSET + BUS_ENABLE_MASK);
    ACRRSTCTRL_SET_RSTB_IODI(reg, 0);
    busWrt32(ACR_REGS_BASE + ACRRSTCTRL_OFFSET + BUS_ENABLE_MASK, reg);

    time = RESET_HOLD_TIME_MICRO_SEC;
    sleepId = IOS_CreateTimer(time, 0, dvdDriverSleepQueue,
                             (IOSMessage) &resetTimeoutMesg);
    DPRINT2("(doResetCommand) Sleeping for duration %u.\n", time);
    receiveError = IOS_ReceiveMessage(dvdDriverSleepQueue,
                                      (IOSMessage *) &inMesg,
                                      IOS_MESSAGE_BLOCK);
    DPRINT("(doResetCommand) Done sleeping.\n");
    IOS_DestroyTimer(sleepId);

    /* Deactivate reset signal */
    reg = busRd32(ACR_REGS_BASE + ACRRSTCTRL_OFFSET + BUS_ENABLE_MASK);
    ACRRSTCTRL_SET_RSTB_IODI(reg, 1);
    busWrt32(ACR_REGS_BASE + ACRRSTCTRL_OFFSET + BUS_ENABLE_MASK, reg);

    /*
     * After drive is RESET, the registers could be inaccessible for
     * a time.  Keep trying to initialize the drive registers until
     * the registers become available and the write succeeds
     */
    DPRINT("(doResetCommand) Initializing registers\n");
    initializeDriveRegisters();
    while ((readDIStatus() & DI_TRANS_COMPLETE_INTR_MASK) == 0) { 
        IOS_YieldThread();
        initializeDriveRegisters();
    }
    DPRINT("(doResetCommand) Done initializing registers\n");

    diClearCoverIntr();
    resetDriverState();

    if (coverInterruptWasEnabled) {
        enableCoverInterrupt();
    }
}

/*************************************************************/

static IOSTimerId
startTimedTransfer(IOSTime duration, const transferMode_t transferMode)
{
    IOSTimerId          commandTimeoutId;

    /*
     * If the last transaction ended in an error, the error interrupt
     * mask will/must be set
     */
#ifndef RVL
    if ((readDIStatus() & DI_ERROR_INTR_MASK) == 0) {
        diFatalError(
                 "Error: Transfer started, but error INTR is off (exiting)!\n");
    }
#endif

    if ((readDIStatus() & DI_TRANS_COMPLETE_INTR_MASK) == 0) {
        diFatalError(
                 "Error: Transfer started, but TC INTR is off (exiting)!\n");
    }
    timeoutMesg.mesgType = DI_MESG_TIMEOUT;
    timeoutMesg.commandNum = currentCommandNum;

    DPRINT2 ("(TimedTransdfer) IOP DI Kernel interrupt enabled: %d\n",
	      IOPDiIntrEnabled());
    diStartTransfer(transferMode);
    DPRINT3("(startTimedTransfer) Setting timer: time = %d, queue ID = %d\n",
             duration, dvdDriverInQueue);
    commandTimeoutId = IOS_CreateTimer(duration, 0, dvdDriverInQueue,
                                    (IOSMessage) &timeoutMesg);
    if (commandTimeoutId < 0) {
        diFatalError(timerErrorToString(commandTimeoutId));
    }
    return(commandTimeoutId);
} // startTimedTransfer

/*************************************************************/

/*
 * Loop through all the messages in the queue, looking for
 * timeout messages.  Recycle all non-timeout messages,
 * but don't recycle timeout messages.  Stop when we dequeue
 * the first message seen, which we then need to jam back
 * onto the front.
 */

static void
clearTimeoutsFromQueue(IOSMessageQueueId queueId)
{
    diInQueueMesg_t     firstMesgPtr, inMesgPtr;
    bool                firstMesgSet = false;
    IOSError            sendError, receiveError;

    DPRINT ("(clearTimeoutsFromQueue) DOING NOTHING\n");
    return;

    DPRINT2 ("(clearTimeoutsFromQueue) start queueID = %d\n", queueId);
    while (1) {
        receiveError = IOS_ReceiveMessage(queueId,
                                          (IOSMessage *) &inMesgPtr,
                                          IOS_MESSAGE_NOBLOCK);
        if (receiveError == IOS_ERROR_QEMPTY) {
            DPRINT ("(clearTimeoutsFromQueue) Queue empty\n");
            return;
        }
        if (inMesgPtr.otherMesg->mesgType == DI_MESG_TIMEOUT) {
            DPRINT ("(clearTimeoutsFromQueue) Dropping timeout\n");
            continue;
        }
        if (firstMesgSet == false) {
            DPRINT ("(clearTimeoutsFromQueue) Recycling first message\n");
            firstMesgSet = true;
            firstMesgPtr = inMesgPtr;
            sendError = IOS_SendMessage(queueId,
                                        (IOSMessage) inMesgPtr.otherMesg,
                                        IOS_MESSAGE_NOBLOCK);
            if (sendError != IOS_ERROR_OK) {
                DPRINT2("(clearTimeoutsFromQueue) SendMessage returns %d\n",
                          sendError);
		receiveError = IOS_ReceiveMessage(queueId,
						  (IOSMessage *) &inMesgPtr,
						  IOS_MESSAGE_NOBLOCK);
		if (receiveError == IOS_ERROR_QEMPTY) {
                    DPRINT("Error: queue is full and empty!\n");
                }
                diFatalError("(clearTimeoutsFromQueue) Can't send first message");
            }
        }
        else if (firstMesgPtr.otherMesg == inMesgPtr.otherMesg) {
            /*
             * We just dequeued the first non-timeout message the
             * second time, which means we've probably
             * gone through the entire contents of the queue.
             * Jam this message, and return
             */
            DPRINT ("(clearTimeoutsFromQueue) First message reseen\n");
            firstMesgSet = true;
            sendError = IOS_JamMessage(dvdDriverInQueue,
                                       (IOSMessage) inMesgPtr.otherMesg,
                                       IOS_MESSAGE_NOBLOCK);
            if (sendError != IOS_ERROR_OK) {
                DPRINT2("(clearTimeoutsFromQueue) JamMessage returns %d\n",
                sendError);
                diFatalError("(clearTimeoutsFromQueue) Can't jam message");
            }
            return;
        }
        else {
            DPRINT ("(clearTimeoutsFromQueue) Recycling non-timeout\n");
            sendError = IOS_SendMessage(queueId,
                                        (IOSMessage) inMesgPtr.otherMesg,
                                        IOS_MESSAGE_NOBLOCK);
            if (sendError != IOS_ERROR_OK) {
                DPRINT2("(clearTimeoutsFromQueue) SendMessage returns %d\n",
                          sendError);
                diFatalError("(clearTimeoutsFromQueue) Can't send message");
            }
        }
    }
} // clearTimeoutsFromQueue

/*************************************************************/

#include "dvd_mem.h"
/*
 * An alternate implementation of clearing timeouts from
 * queues, currently not used.  The code is more straightforward.
 */
/*
 * Loop through all the messages in the queue, looking for
 * timeout messages.  
 */

static void
clearTimeoutsIntrFromQueue(IOSMessageQueueId queueId, const int queueLen)
{
    diInQueueMesg_t     inMesgPtr;
    IOSError            sendError, receiveError;
    int                 mesgNum = 0;
    IOSMessage          *mesgArray;

    DPRINT ("(clearTimeoutsFromQueue) start\n");
    receiveError = IOS_ReceiveMessage(queueId, (IOSMessage *) &inMesgPtr,
                                      IOS_MESSAGE_NOBLOCK);
    /* Avoid doing an alloc if the queue is empty */
    if (receiveError == IOS_ERROR_QEMPTY) {
        DPRINT ("(clearTimeoutsFromQueue) Queue empty\n");
        return;
    }
    mesgArray = dvdMemAlloc(sizeof(IOSMessage) * queueLen);
    if (mesgArray == NULL) {
        diFatalError ("Error: dvdMemAlloc return NULL\n");
    }

    do {
        if (inMesgPtr.otherMesg->mesgType != DI_MESG_TIMEOUT) {
            mesgArray[mesgNum++] = (IOSMessage) inMesgPtr.otherMesg;
            DPRINT2 ("(clearTimeoutsFromQueue) Storing message #%d\n",
                      mesgNum - 1);
        }
        receiveError = IOS_ReceiveMessage(queueId,
                                          (IOSMessage *) &inMesgPtr,
                                          IOS_MESSAGE_NOBLOCK);
    } while (receiveError != IOS_ERROR_QEMPTY && mesgNum < queueLen);
    for (int i = 0; i < mesgNum; i++) {
        sendError = IOS_SendMessage(queueId,
                                    (IOSMessage) inMesgPtr.otherMesg,
                                    IOS_MESSAGE_NOBLOCK);
        if (sendError != IOS_ERROR_OK) {
            DPRINT2("(clearTimeoutsFromQueue) SendMessage returns %d\n",
                      sendError);
            diFatalError("(clearTimeoutsFromQueue) Can't send message");
        }
    }
    dvdMemFree(mesgArray);
} // clearTimeoutsFromQueue_v2

/*************************************************************/


const char *
timerErrorToString(const IOSTimerId errorId)
{
    switch (errorId) {
        case IOS_ERROR_MAX:
            return ("no more IOS timers left");
            break;

        case IOS_ERROR_INVALID:
            return ("invalid message queue");
            break;

        case IOS_ERROR_ACCESS:
            return ("thread cannot access message queue");
            break;

        default:
            return ("unhandled timer errorId");
            break;
    }
}

/*************************************************************/
