#ident "$Id: dvd_driver.c,v 1.66 2006/03/26 22:43:16 jprincen Exp $"

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
 * This file contains the main loop and initialization code
 * for the low part of the DI
 * driver.
 */

#include "iostypes.h"

#ifdef RVL
#include "hw.h"
#include "ioslibc.h"
#include "ios.h"
#include "stdint.h"
#include "stdbool.h"
#define SIGNAL_OFFSET   0

#else // ! defined(RVL)
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>                      /* For printf */
#include <stdint.h>
#include "ioserrno.h"
#include "iosresource.h"
#include "iosiobuf.h"
#define SIGNAL_OFFSET   SIGRTMIN
#define IOS_ResourceReply(mesg, status)       IOS_ResourceRespond(mesg, status)
void IOS_ClearAndEnableDIIntr(void);

#endif // ifdef RVL

#include "ios.h"

#include "dvd_mem.h"
#include "dvd.h"
#include "dvd_hw.h"
#include "dvd_driver.h"
#include "dvd_low.h"
#include "dvd_hw_reg.i"
#include "debug.h"

#define         ALL_PIDS                ~0
#define         DVD_PATH                "/dev/di"

/*
 * For now, file descriptors don't contain any information
 * other than if it is in use or not.  This may be expanded
 * later
 */
typedef struct {
    bool        inUse;
} DiFileDescriptor_t;

dvdState_t              dvdState;
IOSMessageQueueId       dvdDriverInQueue, dvdDriverOutQueue;
IOSMessageQueueId       dvdDriverSleepQueue;
diCommand_t             interfaceDiCommand;
uint8_t                 h3HashArray[MAX_H3_HASH_SIZE] __attribute__((aligned(32)));
uint32_t                dvdCoverStatus;
uint8_t                 currentCommandNum;

static bool             driverRunning = false, driverInitStage2 = false;
static void             initDvdDriverStage1(void);
static void             initDvdDriverStage2(const uint32_t h3HashSize);

#define HIGH_STACK_SIZE   (16 * 1024)


#define DI_NUM_DESCRIPTORS      2
static DiFileDescriptor_t       DiFD[DI_NUM_DESCRIPTORS]; 

IOSError        DiOpen(void);
IOSError        DiClose(DiFileDescriptor_t* const fileDescriptor);
uint32_t        DiIoctl(IOSResourceIoctl* const ioctlMesg);

diOtherMesg_t   intrMesg = {DI_MESG_INTR, true, 0};

uint32_t                lastResetTime;
/*
 * This is set to false once we are past the dummy interrupt
 * time so that the system doesn't think it is just past a reset
 * once the time wraps around again
 */
bool                    resetTimeValid = false, coverWasClosed = false;
bool                    doDecrypt = true;

#ifdef SIMPLE_IMAGE
extern diskInfo_t       diskInfo;
#endif

extern void             resetDriverState(void);
void 			enableDIRegisterAccess(void);
void                    checkDIRegisterAccess(void);

/* ---------------------------------------------------------------------- */

void
dvd_driver()
{
    diInQueueMesg_t     inMesg;
    IOSError            returnStatus, receiveError;

    // printf ("DI_MESG_INTR is: %u\n", DI_MESG_INTR);
    if (driverRunning == true) {
        /* Somebody screwed up - the driver is already running */
        IOS_DestroyThread(0, NULL);
        // This is never reached
    }
    driverRunning = true;
    DPRINT("#### Starting DI driver version 0.3\n");

    initDvdDriverStage1();
    DPRINT2 ("(dvd_driver [after init]) Status reg val is: 0x%x\n",
              readDIStatus());

    for (int i = 0; i < DI_NUM_DESCRIPTORS; i++) {
        DiFD[i].inUse = false;
    }

    while (1) {
        if (resetTimeValid && withinResetTime(DUMMY_COVER_INTR_TIME) == false) {
            resetTimeValid = false;
        }
        DPRINT ("(dvd_driver: Top of Loop) Doing IOS_ReceiveMessage\n");
        DPRINT2 ("(dvd_driver [before ReceiveMessage]) Status reg val is: 0x%x\n",
                  readDIStatus());
        receiveError = IOS_ReceiveMessage(dvdDriverInQueue,
                                          (IOSMessage *) &inMesg,
                                          IOS_MESSAGE_BLOCK);
        if (receiveError != IOS_ERROR_OK) {
            diFatalError ("Receiving message on DVD in queue failed - exit\n");
        }
        DPRINT("(dvd_driver) IOS_ReceiveMessage returned - got message\n");
        DPRINT2("(dvd_driver [after ReceiveMessage]) Status reg val is: 0x%x\n",
                  readDIStatus());
        checkDIRegisterAccess();
        switch (inMesg.otherMesg->mesgType) {

        case IOS_OPEN:
            DPRINT("(dvd_driver) Receiving OPEN request\n");
            if (driverInitStage2 == false) {
                driverInitStage2 = true;
                initDvdDriverStage2(MAX_H3_HASH_SIZE);
            }
            returnStatus = DiOpen();
	    DPRINT2 ("(dvd_driver [after DiOpen]) Status reg val is: 0x%x\n",
		      readDIStatus());
            DPRINT2("(dvd_driver) Open returns: %d\n", returnStatus);
            IOS_ResourceReply(inMesg.resourceMesg, returnStatus);
            // readGoodDIStatus();
            break;

        case IOS_CLOSE:
            DPRINT3 ("Receiving CLOSE request (%d/0x%x)\n",
                     inMesg.resourceMesg->handle,
                     inMesg.resourceMesg->handle);
            returnStatus = DiClose((DiFileDescriptor_t *) inMesg.resourceMesg->handle);
            IOS_ResourceReply(inMesg.resourceMesg, returnStatus);
            break;

        case IOS_IOCTL:
            if (driverInitStage2 == false) {
                driverInitStage2 = true;
                initDvdDriverStage2(MAX_H3_HASH_SIZE);
            }
            DPRINT("(dvd_driver) Receiving IOCTL request\n");
            returnStatus = DiIoctl(&(inMesg.resourceMesg->args.ioctl));
            DPRINT2("(dvd_driver) IOCTL request finished, returning 0x%x\n",
            returnStatus);
            IOS_ResourceReply(inMesg.resourceMesg, returnStatus);
            break;

        case DI_MESG_TIMEOUT:
            continue;           /* Timeout expired from previous command */

        case DI_MESG_INTR:
            DPRINT("(dvd_driver) Received MESG_INTR\n");
            IOS_InvalidateRdb(IOS_RB_IOD);
            DPRINT2 ("(dvd_driver) Status reg val is: 0x%x\n", readDIStatus());
            if (isTransCompInterruptSet()) {
                /*
                 * This occurs when a transaction completes after the
                 * timeout has occurred
                 */
                DPRINT("(dvd_driver) Trans Complete intr received - ignoring and clearing \n");
                diClearTransCompStatus();
                IOS_FlushMem(IOS_WB_IOD);
            }
            if (isErrorInterruptSet()) {
                /*
                 * This occurs when a transaction has an error after the
                 * timeout has occurred
                 */
                DPRINT("(dvd_driver) Error interrupt received - clearing it.\n");
                clearDriveErrorInterrupt();
            }
            if (isCoverInterruptSet()) {
                DPRINT("(dvd_driver) Cover interrupt received.\n");
                if (withinResetTime(DUMMY_COVER_INTR_TIME) == false) {
                    DPRINT ("Received cover interrupt message!\n");
                    if ((readDICoverReg() & DI_COVER_STATUS) == 0) {
                        coverWasClosed = true;
                    }
                }
                else {
		    DPRINT("(dvd_driver) It is a dummy cover interrupt.\n");
                }
                diClearCoverIntr();
                IOS_FlushMem(IOS_WB_IOD);
            }
            IOS_ClearAndEnableDIIntr();
            break;

        default:
            {
                DPRINT2 ("ERROR Unknown message type (0x%x) received.\n",
                         inMesg.otherMesg->mesgType);
                diFatalError("Unknown message type");
                break;
            }
        }
    }
    /*
     * This code should never be reached.  But, just in case
     * it does....
     */
    IOS_DestroyMessageQueue(dvdDriverInQueue);
    IOS_DestroyThread(0, NULL);
    /* Code REALLY should never reach here */
}

/* ---------------------------------------------------------------------- */

/*
 * Initialize the memory allocation system and the input queue
 */
void
initDvdDriverStage1(void)
{

    IOSMessage          *dvdDriverInBuf, *dvdDriverOutBuf, *dvdDriverSleepBuf;

#ifdef RVL
    enableDIRegisterAccess();
    checkDIRegisterAccess();
#endif

    initDvdMemAlloc();

    currentCommandNum = 0;

    /* Create In message queue */
    dvdDriverInBuf = dvdMemAlloc(sizeof(IOSMessage) * DVD_IN_QUEUE_LEN);
    if (dvdDriverInBuf == NULL) {
        diFatalError("Can't allocate space for dvd in queue - exit\n");
    }
    dvdDriverInQueue = IOS_CreateMessageQueue(dvdDriverInBuf, DVD_IN_QUEUE_LEN);
    if (dvdDriverInQueue < 0) {
        diFatalError ("Can't create DVD In queue");
    }
    DPRINT2("(InitDVDDriver) dvdDriverInQueue is: %d\n", dvdDriverInQueue);

    /* Create Out message queue */
    dvdDriverOutBuf = dvdMemAlloc(sizeof(IOSMessage) * DVD_OUT_QUEUE_LEN);
    if (dvdDriverOutBuf == NULL) {
        diFatalError("Can't allocate space for dvd OUT queue - exit\n");
    }
    dvdDriverOutQueue = IOS_CreateMessageQueue(dvdDriverOutBuf,
                                               DVD_OUT_QUEUE_LEN);
    if (dvdDriverOutQueue < 0) {
        diFatalError ("Can't create DVD Out queue\n");
    }

    /* Create message queue for sleeping */
    dvdDriverSleepBuf = dvdMemAlloc(sizeof(IOSMessage) * DVD_SLEEP_QUEUE_LEN);
    if (dvdDriverSleepBuf == NULL) {
        diFatalError("Can't allocate space for dvd OUT queue - exit\n");
    }
    dvdDriverSleepQueue = IOS_CreateMessageQueue(dvdDriverSleepBuf,
                                                 DVD_SLEEP_QUEUE_LEN);
    if (dvdDriverOutQueue < 0) {
        diFatalError ("Can't create DVD Out queue\n");
    }

    if (IOS_RegisterResourceManager(DVD_PATH, dvdDriverInQueue)
                                    != IOS_ERROR_OK) {
        diFatalError("Can't register DVD resource mananger - exit\n");
        exit(1);
    }

    resetDriverState();         // Code is in dvd_low_rvl.c
    DPRINT("resetDriverState: done \n");

    // DPRINT("(initDvdDriver) Doing ClearAndEnableDIIntr\n");
    IOS_ClearAndEnableDIIntr();
    // DPRINT("(initDvdDriver) ClearAndEnableDIIntr done \n");
} // initDvdDriverStage1
/* ---------------------------------------------------------------------- */


/*
 * INPUT: h3HashSize in *bytes*
 * ACTION: 
 *         Registers to handle the DI interrupt.
 * RETURN: Nothing
 *          
 */

extern uint32_t IOPDiIntrEnabled(void);

void
initDvdDriverStage2(const uint32_t h3HashSize)
{
    IOSError            theError;

    DPRINT("(initDvdDriverStage2) enter\n");

    /*
     * Set up the interrupt enables so that transaction complete and
     * error interrupts are enabled, but cover interrupts are disabled
     */

    initializeDriveRegisters();

    /* Register to handle (unified) DI interrupts */
    theError =  IOS_HandleEvent(IOS_EVENT_DI + SIGNAL_OFFSET,
                                dvdDriverInQueue, (IOSMessage) &intrMesg);

    DPRINT("(initDvdDriverStage2) Done calling IOS_HandleEvent for IOS_EVENT_DI\n");
    if (theError != IOS_ERROR_OK) {
        diFatalError("Can't register to handle IOS_EVENT_DI  - exit\n");
        if (theError == IOS_ERROR_INVALID) {
            diFatalError("Invalid event or queue\n");
        }
        else if (theError == IOS_ERROR_ACCESS) {
            diFatalError("Permission denied.\n");
        }
        else {
            diFatalError("Unknown error\n");
        }
        exit(1);
    }
    IOS_ClearAndEnableDIIntr();
} // initDvdDriverStage2
/* ---------------------------------------------------------------------- */

/*
 * Allocate a file descriptor and return it.  Note that file
 * descriptors aren't used in the rest of the code.
 */
IOSError
DiOpen(void)
{
    for (int i = 0; i < DI_NUM_DESCRIPTORS; i++) {
        if (DiFD[i].inUse == false) {
            DiFD[i].inUse = true;
            DPRINT3 ("(DiOpen) returning 0x%x (i=%d)\n",
                     (uint32_t) &DiFD[i], i);
            return((IOSError) &DiFD[i]);
        }
    }
    DPRINT ("Returning ERROR_MAX\n");
    return(IOS_ERROR_MAX);
}
/* ---------------------------------------------------------------------- */

IOSError
DiClose(DiFileDescriptor_t* const fileDescriptor)
{
    if (fileDescriptor->inUse == true) {
        fileDescriptor->inUse = false;
        return(IOS_ERROR_OK);
    } else {
        return(IOS_ERROR_INVALID);
    }
}

/* ---------------------------------------------------------------------- */

/*
 * RETURNS:
 *           The intType argument which will eventually be returned
 *           to the Broadway caller: DVD_INTTYPE_TC, DVD_INTTYPE_DE, etc.
 */
uint32_t
DiIoctl(IOSResourceIoctl* const ioctlMesg)
{
    diCommand_t         *command;
    uint32_t            ioctlReturn;
    uint32_t            commandResult = DI_ERR_BOGUS;
    bool                executeCommand = true;
    uint32_t            tmpVal;

    ioctlReturn = DVD_INTTYPE_TC;

    if (ioctlMesg->outLen != 0) {
        * (uint32_t *) ioctlMesg->outPtr = 42;
    }

#ifndef RVL
    assert(ioctlMesg->inLen == sizeof(diCommand_t));
#endif

    command = (diCommand_t *) ioctlMesg->inPtr;

    switch(command->theCommand) {

    case DI_WAIT_FOR_COVER_CLOSE_CMD:
        DPRINT("(DIIoctl) Doing DI_WAIT_FOR_COVER_CLOSE_CMD\n");
        IOS_InvalidateRdb(IOS_RB_IOD);
        enableCoverInterrupt();
        IOS_FlushMem(IOS_WB_IOD);
        doWaitForCoverClose();
        ioctlReturn = DVD_INTTYPE_CVR;
        break;

    case DI_GET_COVER_REGISTER_CMD:
        DPRINT("(DIIoctl) Doing DI_GET_COVER_REGISTER_CMD\n");
#ifndef RVL
        assert(ioctlMesg->outLen >= sizeof(uint32_t));
#endif
        IOS_InvalidateRdb(IOS_RB_IOD);
        * (uint32_t *) ioctlMesg->outPtr = readDICoverReg();
        break;

    case DI_GET_COVER_STATUS_CMD:
        DPRINT("(DIIoctl) Doing DI_GET_COVER_STATUS_CMD\n");
        if (withinResetTime(COVER_STATUS_UNKNOWN_TIME)) {
            * (uint32_t *) ioctlMesg->outPtr = DVD_COVER_UNKNOWN;
        } else if ((readDICoverReg() & DI_COVER_STATUS) == 0) {
            * (uint32_t *) ioctlMesg->outPtr = DVD_COVER_CLOSED;
        } else {
            * (uint32_t *) ioctlMesg->outPtr = DVD_COVER_OPEN;
        }
        break;

    case DI_GET_LENGTH_CMD:
        * (uint32_t *) ioctlMesg->outPtr = driverLengthReg;
        DPRINT2("(DIIoctl) Doing DI_GET_LENGTH_CMD: Length = %u\n", driverLengthReg);
        break;

    case DI_GET_IMM_BUFFER_CMD:
        IOS_InvalidateRdb(IOS_RB_IOD);
        DPRINT2("(DiIoctl) Reading Immediate Reg; val = 0x%x\n", readDIImmData());
        * (uint32_t *) ioctlMesg->outPtr = readDIImmData();
        break;

    case DI_UNMASK_STATUS_INTERRUPTS:
        /* This command does nothing */
        break;

    case DI_MASK_COVER_INTERRUPT:
        DPRINT("(DIIoctl) Doing DI_MASK_COVER_INTERRUPT\n");
        IOS_InvalidateRdb(IOS_RB_IOD);
        tmpVal  = readDICoverRegForWrite();
        tmpVal &= ~DI_COVER_INTR_MASK;
        writeDICoverReg(tmpVal);
        IOS_FlushMem(IOS_WB_IOD);
        break;

    case DI_CLEAR_COVER_INTERRUPT:
        DPRINT("(DIIoctl) Doing DI_CLEAR_COVER_INTERRUPT\n");
        IOS_InvalidateRdb(IOS_RB_IOD);
        tmpVal  = readDICoverRegForWrite();
        tmpVal |= DI_COVER_INTR;
        writeDICoverReg(tmpVal);
        IOS_FlushMem(IOS_WB_IOD);
        break;

    case DI_UNMASK_COVER_INTERRUPT:
        DPRINT("(DIIoctl) Doing DI_UNMASK_COVER_INTERRUPT\n");
        IOS_InvalidateRdb(IOS_RB_IOD);
        tmpVal  = readDICoverRegForWrite();
        tmpVal |= DI_COVER_INTR_MASK;
        writeDICoverReg(tmpVal);
        IOS_FlushMem(IOS_WB_IOD);
        DPRINT2 ("(DiIoctl [DI_UNMAKS_COVER_INTERRUPT]) Cover reg val = 0x%x\n", readDICoverReg());
        break;

    default:                    /* Commands that invoke a disc command */
        IOS_InvalidateRdb(IOS_RB_IOD);
        if (   isErrorInterruptSet()
            && command->theCommand != DI_REQUEST_ERROR_CMD) {
            ERR_DPRINT("(DiIoctl) Driver calling clearDriveErrorInterupt on own\n");
            commandResult = clearDriveErrorInterrupt();
            if (commandResult != DI_ERR_NO_ERROR) {
                executeCommand = false;
            }
        }

#ifdef DEVELOPER
        /*
         * This code must not go in the production version of the
         * driver.  It should only go in developer systems.
         */
        if (   command->theCommand == DI_READ_RVL_CMD
            && diskState.isRvlDisk == false) {
            command->theCommand = DI_READ_CMD;
            DPRINT ("+++ DOING READ WITHOUT DECRYPT +++\n");
        }
#endif
        if (executeCommand) {
            commandResult = handleDiCommand(command, ioctlMesg->outPtr);
        }
        switch (commandResult) {

        case DI_ERR_NO_ERROR:
            ioctlReturn = DVD_INTTYPE_TC;
            break;

        case DI_ERR_TIMEOUT:
            ioctlReturn = DVD_INTTYPE_TIMEOUT;
            break;

        case DI_ERR_HASH:
            ioctlReturn = DVD_INTTYPE_SECURITY_ERROR;
            break;

        case DI_ERR_NONSPECIFIC:
            ioctlReturn = DVD_INTTYPE_DE;
            break;

        default:
            diFatalError("(DiIoctl) Inner default case reached");
            break;
        } // switch (commandResult)
        if (coverWasClosed) {
            DPRINT3("(DiIoctl) coverWasClosed is set, ioctlReturn was 0x%x is now 0x%x\n",
                      ioctlReturn, ioctlReturn | DVD_INTTYPE_CVR);
            coverWasClosed = false;
            ioctlReturn |= DVD_INTTYPE_CVR;
        }
        break;
    } 
    return(ioctlReturn);
} // DiIoctl

/* ---------------------------------------------------------------------- */

void
diFatalError(const char *mesg)
{
#ifdef RVL
    ERR_DPRINT2("Fatal error in DI driver: %s\nExiting\n", mesg);
#else
    fprintf (stderr, "Fatal error in DI driver: %s\nExiting\n", mesg);
#endif
    IOS_DestroyThread(0, NULL);
    /*
     * Compiler fodder - it doesn't know that IOS_DestroyThread(0,NULL)
     * doesn't return
     */
    exit(1);
}

/* ---------------------------------------------------------------------- */

/*
 * RETURNS: true if the current time is within timeInMilliSecs
 *          of the last reset.
 *          false otherwise
 */

bool
withinResetTime(const uint32_t timeInMilliSecs)
{
    uint32_t    currentTime, endTime;

    if (resetTimeValid == false) {
        DPRINT("(withinResetTime) returning false(1)\n");
        return(false);
    }
    currentTime = IOS_GetTimer();
    endTime = lastResetTime + (timeInMilliSecs * SYSTEM_TICKS_PER_MILLISEC);

    if (endTime > lastResetTime) {
        if (currentTime < endTime && currentTime >= lastResetTime) {
	    DPRINT("(withinResetTime) returning true(1)\n");
            return(true);
        }
        else {
	    DPRINT("(withinResetTime) returning false(2)\n");
            return(false);
        }
    }
    else {      
        /*
         * lastResetTime is close enough to MAX_UINT_32 that
         * the endTime wraps around past 0
         */
        if (currentTime < endTime || currentTime >= lastResetTime) {
	    DPRINT("(withinResetTime) returning true(2)\n");
            return(true);
        }
        else {
	    DPRINT("(withinResetTime) returning false(3)\n");
            return(false);
        }
    }
} // withinResetTime

/* ---------------------------------------------------------------------- */

#ifdef RVL
#define BUS_ENABLE_MASK 0x00800000


void
enableDIRegisterAccess(void)
{
    uint32_t	reg;

    reg = busRd32(ACR_REGS_BASE + ACRCOMPAT_OFFSET + BUS_ENABLE_MASK);
    ACRCOMPAT_SET_PI_DIRSTB_EN(reg, 0);
    busWrt32(ACR_PROT_REGS_BASE + ACRCOMPAT_OFFSET + BUS_ENABLE_MASK, reg);

    /* Take needed blocks out of reset */
    reg = busRd32(ACR_REGS_BASE + ACRRSTCTRL_OFFSET + BUS_ENABLE_MASK);
    ACRRSTCTRL_SET_RSTB_IOPI(reg, 1);
    ACRRSTCTRL_SET_RSTB_IODI(reg, 1);
    busWrt32(ACR_REGS_BASE + ACRRSTCTRL_OFFSET + BUS_ENABLE_MASK, reg);


    reg = busRd32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK);

#ifdef notdef
    // FIXME - This code goes into production software
    /* Disable PPC access to DI */
    AIPPROT_SET_ENAHBPI2DI(reg, 0);
#endif

    busWrt32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK, reg);
}
/* ---------------------------------------------------------------------- */

/*
 * Triggers a fatal error if the AHB register configuration is incorrect.
 */

void
checkDIRegisterAccess(void)
{
    uint32_t    reg;

    /* Make sure blocks are not being reset */
    reg = busRd32(ACR_REGS_BASE + ACRRSTCTRL_OFFSET + BUS_ENABLE_MASK);
    if ((reg & ACRRSTCTRL_RSTB_IOPI_MASK) == 0) {
        diFatalError("RSTB_IOPI in ACRCOMPT reg is 0");
    }
    if ((reg & ACRRSTCTRL_RSTB_IODI_MASK) == 0) {
        diFatalError("RSTB_IODI in ACRCOMPT reg is 0");
    }

    /*
    reg = busRd32(ACR_REGS_BASE + ACRCOMPAT_OFFSET + BUS_ENABLE_MASK);
    if ((reg & ACRRSTCTRL_RSTB_DIRSTB_MASK) != 0) {
        diFatalError("PI_DIRSTB in ACRCOMPT reg is 1");
    }
    */

    reg = busRd32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK);
#ifdef not_def
    /* FIXME - This code needs to run in final production mode */
    /* Check the keeping of PI from accessing DI */
    if ((reg & AIPPROT_ENAHBPI2DI_MASK) != 0) {
        diFatalError("ENAHBPI2DI in AIPPROT reg is 1");
    }
#endif

#ifndef WORK_AROUND
    /* Check bus path setting */
    if ((reg & AIPPROT_ENAHBIOPI_MASK) == 0) {
        diFatalError("ENAHBIOPI in AIPPROT reg is 0");
    }
#endif
}
/* ---------------------------------------------------------------------- */

#endif // RVL
