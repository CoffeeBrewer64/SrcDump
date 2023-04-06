d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.11 2006/01/19 22:57:05 craig Exp $"
a39 3
static void     doDiskRequestError(dvdStatus_t *status, uint32_t *errorCode);
static void     doWaitForCoverClose(void);

d45 17
a61 5
/*
static uint32_t
doDiskRead(uint8_t* const destAddr, const uint32_t length,
           const uint32_t wordOffset);
*/
d241 7
d278 1
a278 1
static inline void
a306 1
 *    The error code for the command
d316 1
a316 1
    bool                transactionNeeded = false;
d329 2
d334 3
a336 1
        /* TODO */
d372 3
a374 1
        DILength = sizeof(DVDDriveInfo);
d399 3
a401 1
        DILength      = diCommand->arg[1];
d412 1
d414 1
d422 1
d424 1
d437 3
a439 1
        DILength = diCommand->arg[3];
d463 3
a465 1
        DILength = sizeof(DVDVideoPhysical);
a474 1
        DILength = sizeof(DVDVideoCopyright);
d477 3
a488 1
        DILength = sizeof(DVDVideoDiscKey);
d491 3
d500 7
a506 2
                                   diCommand->arg[1],
                                   diCommand->arg[2]);
a513 1
        DILength = sizeof(DVDVideoReportKey);
d518 3
d567 3
a569 1
        DILength = sizeof(DVDLowDriveSer);
d598 1
a598 3
        enableCoverInterrupt();
        doWaitForCoverClose();
        transactionNeeded = false;
d651 10
d679 4
a682 2
        uint32_t driveStatus;
        doDiskRequestError(&driveStatus, &commandResult);
d685 3
a693 12
/*************************************************************/


static IOSTimerId
sendRequestError(void)
{
    IOSTimerId  return_val;
    setDiCommandByte(DI_REQUEST_ERROR_CMD);
    return_val = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT, Immediate);
    return(return_val);
}

d724 1
d727 2
a728 2
static void
doDiskRequestError(dvdStatus_t *driveStatus, uint32_t *errorCode)
d730 2
a731 5
    IOSError            receiveError;
    diInQueueMesg_t     inMesg;
    bool                timerStopped = false;
    bool                commandTimedOut, commandTerminated;
    IOSTimerId          commandTimeoutId;
a732 5
    printf ("(doDiskRequestError) Enter\n");
    /* It is not a problem when currentCommandNum wraps from 255 to 0 */
    currentCommandNum++;

    DICmdBuf[0] = 0;
d734 1
a734 1
    commandTimeoutId = sendRequestError();
d736 3
a738 65
    commandTimedOut = commandTerminated = false;

    do {
        receiveError = IOS_ReceiveMessage(dvdDriverInQueue,
                                          (IOSMessage *) &inMesg,
                                          IOS_MESSAGE_BLOCK);
        if (receiveError != IOS_ERROR_OK) {
            diFatalError ("(doDiskRequestError) Receiving message on DVD in queue failed\n");
        }

        if (timerStopped == false) {
            IOS_StopTimer(commandTimeoutId);
            timerStopped = true;
        }

        switch(inMesg.otherMesg->mesgType) {
        
        case DI_MESG_TIMEOUT:
            if (inMesg.otherMesg->commandNum == currentCommandNum) {
                commandTimedOut = true;
            }
            else {
                /*
                 * Timeout was for a previous command.  Wait for message
                 * corresponding to the current command
                 */
                 continue;
            }
            break;

        case DI_MESG_TRANS_COMPLETE:
        case DI_MESG_TRANS_ERROR:
            commandTerminated = true;
            break;

        case DI_MESG_COMMAND:
            diFatalError ("(doDiskRequestError) Driver botch: command mesg \n");
            break;
        
        default:
            diFatalError ("(doDiskRequestError) Unhandled message case\n");
            break;
        }
    } while (commandTimedOut == false && commandTerminated == false);

    if (commandTimedOut) {
        *driveStatus = dvdStatusBogus;
        *errorCode = DI_ERR_TIMEOUT;
        return;
    }

    if (   commandTerminated
        && inMesg.otherMesg->mesgType == DI_MESG_TRANS_COMPLETE) {
        *errorCode = DIImmData & 0xFFFFFF;
        *driveStatus = DIImmData >> 24;
    } else if (   commandTerminated
               && inMesg.otherMesg->mesgType == DI_MESG_TRANS_ERROR) {
        *errorCode = DI_ERR_DOUBLE_FATAL;
        *driveStatus = DIImmData >> 24;
    } else {
        fprintf (stderr, "(DoDiskRequestError): Driver error\n");
        exit(1);
    }
    printf ("(doDiskRequestError) Exit\n");
} // doDiskRequestError
d747 1
a747 1
static void
d759 1
d761 1
