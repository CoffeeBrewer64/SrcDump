d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.2 2005/11/29 22:01:08 craig Exp $"
d37 1
d60 1
a60 1
    DICmdBuf[0] |= ((bitValue & 0x1) << 15);
d66 1
a66 1
    DICmdBuf[0] |= ((bitValue & 0x1) << 14);
d72 1
a72 1
    DICmdBuf[0] |= ((value & 0x3) << 8);
d78 1
a78 1
    DICmdBuf[0] |= ((value & 0x1) << 8);
d84 1
a84 1
    DICmdBuf[0] |= ((value & 0xF) << 24);
d130 1
a130 1
setDiDVDConfigValue(const uint8_t value)
d192 1
a192 1
    DICmdBuf[3] = command_word;
d236 6
d272 1
a272 1
    IOSError            sendError, receiveError;
d283 2
d316 1
d364 1
d375 2
a376 2
        setDiStartLSN(diCommand->argument2);
        setDiTransferLength(diCommand->argument3);
d399 1
d410 1
d421 1
d432 1
d440 1
d446 1
d453 1
d462 1
d481 1
d541 1
d613 1
a613 1
    printf ("In doDiskRequestError\n");
d628 1
a628 1
            diFatalError ("(handleDiCommand) Receiving message on DVD in queue failed\n");
d657 1
a657 1
            diFatalError ("(handleDiCommand) Driver botch: command mesg \n");
d661 1
a661 1
            diFatalError ("(handleDiCommand) Unhandled message case\n");
d679 1
a679 1
        fprintf (stderr, "(DoDiskRequestError: Driver error\n");
d682 1
d687 23
a712 1
    diInQueueMesg_t     timeoutMesg;
d716 10
