d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.14 2006/01/23 22:25:23 craig Exp $"
d344 1
a344 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT,
d353 1
a353 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT,
d363 1
a363 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT,
d375 1
a375 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT, DMA);
d383 1
a383 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT,
d402 1
a402 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT, DMA);
d415 1
a415 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT, DMA);
d425 1
a425 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT, DMA);
d440 1
a440 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT, DMA);
d451 1
a451 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT,
d466 1
a466 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT, DMA);
d473 1
a473 2
        setDiDVDStructLayer(diCommand->arg[1]);
        DIDmaDestAddr = (uint32_t) outputPtr;
d477 1
a477 3
        DILength        = sizeof(DVDVideoCopyright);
        driverLengthReg = sizeof(DVDVideoCopyright);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT, DMA);
d491 1
a491 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT, DMA);
d518 1
a518 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT, DMA);
d524 1
a524 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT,
d531 1
a531 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT,
d538 1
a538 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT,
d546 1
a546 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT,
d554 1
a554 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT,
d567 1
a567 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT, DMA);
d578 1
a578 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT,
d587 1
a587 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT,
d752 1
d762 1
d766 2
a767 1
}
