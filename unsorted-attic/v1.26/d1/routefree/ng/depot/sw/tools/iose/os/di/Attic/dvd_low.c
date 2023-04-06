d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.25 2006/02/21 23:45:43 craig Exp $"
d18 8
d32 2
d304 4
a307 2
static inline void
DiClearTCStatus(void)
d322 2
d325 1
a325 1
DiClearErrorStatus(void)
d332 1
a332 1
    tempVal  &= ~DI_TRANS_COMPLETE_INTR;
d366 2
a367 2
    DiClearTCStatus();
    DiClearErrorStatus();
d372 2
a373 2
static inline void
DiClearCoverIntr(void)
d378 5
a382 1
    tempVal |= DI_COVER_INTR;
d386 2
d428 42
a489 1
    bool                timerStopped = false;
a492 1
    char                printBuf[128];
a496 1
    DICmdBuf[0] = 0;
d504 1
d545 1
a545 1
        DIDmaDestAddr = (uint32_t) outputPtr;
d574 1
a574 1
        DIDmaDestAddr = (uint32_t) outputPtr;
d585 1
a585 1
        DIDmaDestAddr = (uint32_t) outputPtr;
d597 1
a597 1
        DIDmaDestAddr = (uint32_t) outputPtr;
d609 1
a609 1
        DIDmaDestAddr = (uint32_t) outputPtr;
d636 1
a636 1
        DIDmaDestAddr = (uint32_t) outputPtr;
d660 1
a660 1
        DIDmaDestAddr = (uint32_t) outputPtr;
d685 1
a685 1
        DIDmaDestAddr = (uint32_t) outputPtr;
d736 1
a736 1
        DIDmaDestAddr = (uint32_t) outputPtr;
d772 1
a772 1
        sprintf(printBuf, "Unhandled case (0x%x) in handleDiCommand",
d774 1
a774 1
        diFatalError(printBuf);
d797 9
a805 4
        if (timerStopped == false) {
            DPRINT2 ("(handleDiCommand) Stopping timer %u\n", commandTimeoutId);
            IOS_DestroyTimer(commandTimeoutId);
            timerStopped = true;
d814 5
d825 2
a826 5
        case DI_MESG_TRANS_COMPLETE:
        case DI_MESG_TRANS_ERROR:
            commandTerminated = true;
            clearTimeoutsFromQueue(dvdDriverInQueue);
            break;
d828 33
a860 6
        case DI_MESG_COVER:
            if (withinResetTime(DUMMY_COVER_INTR_TIME) == false) {
                DPRINT ("Received cover interrupt message!\n");
                if ((readDICoverReg() & DI_COVER_STATUS) == 0) {
                    coverWasClosed = true;
                    // Do resetDriverState() here?
d862 1
d864 1
d871 8
a878 6
        default: {
            char        buf[128];
            sprintf (buf, "(handleDiCommand) Unhandled message case (%d)\n",
                     inMesg.otherMesg->mesgType);
            diFatalError(buf);
        }
d880 1
a880 23
            break;
        }
    } while (commandTimedOut == false && commandTerminated == false);

    if (   commandTerminated
        && inMesg.otherMesg->mesgType == DI_MESG_TRANS_COMPLETE) {
        DPRINT ("(handleDiCommand) TC received\n");
        DiClearTCStatus();
        commandResult = DI_ERR_NO_ERROR;
    } else if (   commandTerminated
               && inMesg.otherMesg->mesgType == DI_MESG_TRANS_ERROR) {
        DPRINT ("(handleDiCommand) Error received\n");
        if (isDmaCommand) {
            driverLengthReg = 0;
        }
        commandResult = DI_ERR_NONSPECIFIC;
    } else {
        DPRINT ("(handleDiCommand) Timeout\n");
        if (isDmaCommand) {
            driverLengthReg = 0;
        }
        commandResult = DI_ERR_TIMEOUT;
    }
a886 1

d911 1
a911 1
    assert ((length & 0x1F) == 0);
d938 1
a938 1
    DiClearErrorStatus();
d956 1
d959 1
a959 1
    while (1) {
d964 16
a979 6
        if (     inMesg.otherMesg->mesgType == DI_MESG_COVER
            && withinResetTime(DUMMY_COVER_INTR_TIME) == false
            && ((readDICoverReg() & DI_COVER_STATUS) == 0)) {
            // Do resetDriverState() here?
            DPRINT ("(**** doWaitForCoverClose) exit 1\n");
            return;
d981 2
a982 2
    }
    DPRINT("(**** doWaitForCoverClose) exit 2\n");
d992 1
a992 1
        fprintf (stderr,
a993 1
        IOS_DestroyThread(0, NULL);
d996 1
a996 1
        fprintf (stderr,
a997 1
        IOS_DestroyThread(0, NULL);
