d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.6 2005/12/16 01:07:42 craig Exp $"
d14 2
a15 2
 * Program comments here
 * 
a285 8
uint32_t
readLengthToTimeout(uint32_t readLength)
{
    /* FIXME - find out what real value is */
    return(readLength * 10);
}

/*************************************************************/
d312 1
a312 5
    case DI_BEFORE_RESET:
        /* TODO */
        break;

    case DI_AFTER_RESET:
d318 3
a320 3
        setDiAudioSubCode(diCommand->argument1);
        setDiCommandWord1(diCommand->argument3);
        setDiCommandWord2(diCommand->argument2);
d328 1
a328 1
        setDiAudioSubCode(diCommand->argument1);
d337 2
a338 2
        setDiAudioBufferSwitch(diCommand->argument1);
        setDiAudioBufferSize(diCommand->argument2);
a346 1
        doWaitForCoverClose();
d352 1
a352 1
        DIDmaDestAddr = diCommand->argument1;
d361 2
a362 2
        setDiOffsetSubCode(diCommand->argument1);
        setDiCommandWord1(diCommand->argument2);
d372 1
d376 4
a379 5
        setDiCommandWord1(diCommand->argument1);
        setDiCommandWord2(diCommand->argument2);
        DIDmaDestAddr = diCommand->argument3;
        commandTimeoutId =
             startTimedTransfer(readLengthToTimeout(diCommand->argument2), DMA);
d386 1
a386 1
        DIDmaDestAddr = diCommand->argument1;
d396 1
a396 1
        DIDmaDestAddr = diCommand->argument1;
a401 1
    /* FIXME - Need to explicitly set STRM and Retry */
d404 3
a406 3
        setDiDVDStrm(0x1);
        setDiDVDRetry(0x0);
        DIDmaDestAddr = diCommand->argument1;
d408 3
a410 3
        setDiStartLSN(diCommand->argument3);
        setDiTransferLength(diCommand->argument2);
        DILength = diCommand->argument2;
d417 2
a418 2
        setDiDVDConfigSet(diCommand->argument1);
        setDiDVDConfigType(diCommand->argument2);
d420 1
a420 1
        setDiDVDConfigValue(diCommand->argument3);
d430 2
a431 2
        setDiDVDStructLayer(diCommand->argument2);
        DIDmaDestAddr = diCommand->argument1;
d442 2
a443 2
        setDiDVDStructLayer(diCommand->argument2);
        DIDmaDestAddr = diCommand->argument1;
d454 2
a455 2
        setDiDVDStructLayer(diCommand->argument2);
        DIDmaDestAddr = diCommand->argument1;
d464 5
a468 2
        doRvlRead((uint8_t *) diCommand->argument1, diCommand->argument2,
                  diCommand->argument3);
d474 1
a474 1
        DIDmaDestAddr = diCommand->argument1;
d476 1
a476 1
        setDiReportKeyFormat(diCommand->argument2);
d478 1
a478 1
        setDiReportKeyLSN(diCommand->argument3);
a504 1
    /* FIXME - Need a longer timeout here? */
d507 1
a507 1
        setDiCommandWord1(diCommand->argument1);
d515 1
a515 1
        setDiMaxRotationSubcode(diCommand->argument1);
d523 3
a525 3
        DIDmaDestAddr = diCommand->argument1;
        setDiSerMeasClr(diCommand->argument2);
        setDiSerMeasENA(diCommand->argument3);
d541 2
a542 2
        setDiEjectBit(diCommand->argument1);
        setDiSavingBit(diCommand->argument2);
d576 1
d585 1
d588 3
d609 1
d613 1
d617 1
d673 1
a673 1
            diFatalError ("(doDiskRequestError) Receiving message on DVD in queue failed\n");
d859 2
