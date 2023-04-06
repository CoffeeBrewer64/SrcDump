d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.7 2005/12/22 03:07:32 craig Exp $"
d40 2
a41 2
static void       doDiskRequestError(dvdStatus_t *status, uint32_t *errorCode);
static void       doWaitForCoverClose(void);
d43 2
a44 2
void doRvlRead(uint8_t *dest_addr, uint32_t byteLength,
               uint32_t virtWordOffset);
d308 1
a308 1
    printf ("(handleDiCommand) Command is: 0x%x\n", diCommand->the_command);
d310 3
a312 1
    switch (diCommand->the_command) {
d378 1
a378 1
        setDiCommandWord1(diCommand->arg[0]);
d380 1
a380 1
        DIDmaDestAddr = diCommand->arg[2];
d466 4
a469 5
        /* FIXME - Decomment this */
        /*
        doRvlRead((uint8_t *) diCommand->arg[0], diCommand->arg[1],
                  diCommand->arg[2]);
        */
d557 1
a557 1
                diCommand->the_command);
d563 1
a563 1
        return(DI_ERR_NO_ERROR);
d566 5
a648 1
#ifdef notused
d653 2
a654 5
    IOSError            receiveError;
    diInQueueMesg_t     inMesg;
    bool                timerStopped = false;
    bool                commandTimedOut = false, commandTerminated = false;
    IOSTimerId          commandTimeoutId;
d656 6
a661 8
    DICmdBuf[0] = 0;
    setDiCommandByte(DI_READ_CMD);
    setDiReadSubCommandByte(DI_NORMAL_READ);
    setDiCommandWord1(wordOffset);
    setDiCommandWord2(length);
    DIDmaDestAddr = (uint32_t) destAddr;
    commandTimeoutId =
         startTimedTransfer(readLengthToTimeout(length));
d663 2
a664 59
    /* It is not a problem when currentCommandNum wraps from 255 to 0 */
    currentCommandNum++;

    commandTimedOut = commandTerminated = false;

    do {
        receiveError = IOS_ReceiveMessage(dvdDriverInQueue,
                                          (IOSMessage *) &inMesg,
                                          IOS_MESSAGE_BLOCK);
        if (receiveError != IOS_ERROR_OK) {
            diFatalError ("(doDiskRead) Receiving message on DVD in queue failed\n");
        }

        if (timerStopped == false) {
            IOS_StopTimer(commandTimeoutId);
            timerStopped = true;
        }

        switch(inMesg.mesgType) {
        
        case DI_MESG_TIMEOUT:
            if (inMesg.commandNum == currentCommandNum) {
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
        return(DI_ERR_TIMEOUT);
    }
    if (commandTerminated && inMesg.mesgType == DI_MESG_TRANS_COMPLETE) {
        return(DI_ERR_NO_ERROR);
    } else if (commandTerminated && inMesg.mesgType == DI_MESG_TRANS_ERROR) {
        return(DI_ERR_NONSPECIFIC);
    } else {
        fprintf (stderr, "(DoDiskRequestError): Driver error\n");
        exit(1);
    }
a666 2
#endif

