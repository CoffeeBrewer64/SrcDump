d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.23 2006/02/16 21:51:05 craig Exp $"
a28 1
#include "dvd_hw_reg.h"
a31 1

a47 14

/* TODO - remove this when the real thing is defined */
#if 0
#include <unistd.h>             // For sleep(3)
uint32_t
IOS_GetTimer(void)
{
    printf ("IOS_GetTimer is bogus!\n");
    sleep(5);
    return(0);
}
#endif

/*************************************************************/
a57 2
    DICmdBuf[0] |= (commandByte << 24);

a67 1
    DICmdBuf[0] |= ((subCommand & 0x3) << 6);
a77 1
    DICmdBuf[0] |= ((bitValue & 0x1) << 17);
a87 2
    DICmdBuf[0] |= ((bitValue & 0x1) << 20);

a97 2
    DICmdBuf[0] |= ((value & 0x3) << 16);

a107 2
    DICmdBuf[0] |= ((value & 0x1) << 16);

a117 2
    DICmdBuf[0] |= (value & 0xF);

a127 2
    DICmdBuf[0] |= ((value & 0xF) << 28);

a137 2
    DICmdBuf[1] = lsn & 0xFFFFFF;

a146 2
    DICmdBuf[2] = length & 0xFFFFFF;

a155 2
    DICmdBuf[0] |= (strmVal & 0x1) << 15;

a165 2
    DICmdBuf[0] |= (retryVal & 0x1) << 14;

a175 2
    DICmdBuf[0] |= (setVal & 0x1) << 16;

a185 2
    DICmdBuf[0] |= (typeVal & 0xFF);

a195 2
    DICmdBuf[1] |= (value & 0xFFFFFF);

a205 2
    DICmdBuf[0] |= (subCmd & 0xFF) << 16;

a215 2
    DICmdBuf[0] |= (layer & 0xFF) << 8;

a225 2
    DICmdBuf[0] |= (format & 0xFF) << 16;

a235 2
    DICmdBuf[1] |= (lsn & 0xFFFFFF);

a245 2
    DICmdBuf[0] |= (subCode & 0x1) << 23;

a255 2
    DICmdBuf[0] |= (clearVal & 0x1) << 17;

a265 2
    DICmdBuf[0] |= (ENAVal & 0x1) << 16;

a275 2
    DICmdBuf[0] |= (subCode & 0x3) << 16;

a283 1
    DICmdBuf[1] = command_word;
a289 1
    DICmdBuf[2] = command_word;
a300 1
    DIStatus &= ~DI_TRANS_COMPLETE_INTR;
a303 1
    DIStatus |= DI_TRANS_COMPLETE_INTR;
a316 1
    DIStatus &= ~DI_TRANS_COMPLETE_INTR;
a319 1
    DIStatus |= DI_ERROR_INTR;
a336 1
        DIControl = DI_TRANSFER;
a339 1
        DIControl = DI_TRANSFER | DI_DMA_MODE;
a361 2
    DICoverReg |= DI_COVER_INTR;

a371 2
    DICoverReg |= DI_COVER_INTR_MASK;

a381 2
    DICoverReg &= ~DI_COVER_INTR_MASK;

a391 2
    DIStatus |= DI_TRANS_COMPLETE_INTR_MASK;

a401 2
    DIStatus |= DI_ERROR_INTR_MASK;

a486 1
        DILength        = sizeof(DVDDriveInfo);
a514 1
        DILength        = diCommand->arg[1];
a527 1
        DILength        = sizeof(DVDDiskID);
a537 1
        DILength        = sizeof(DVDDiskBca);
a552 1
        DILength        = diCommand->arg[3];
a578 1
        DILength        = sizeof(DVDVideoPhysical);
a602 1
        DILength        = sizeof(DVDVideoDiscKey);
a629 1
        DILength        = sizeof(DVDVideoReportKey);
a678 1
        DILength        = sizeof(DVDLowDriveSer);
d737 1
a737 1
            printf ("(handleDiCommand) Stopping timer\n");
d889 1
a889 1
            && ((DICoverReg & DI_COVER_STATUS) == 0)) {
