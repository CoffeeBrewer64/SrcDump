#ident "$Id: dvd_high.c,v 1.2 2006/01/13 21:35:53 craig Exp $"
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
 * The upper half of the DI device driver.
 */


#include <stdio.h>

#include "iostypes.h"
#include "ioserrno.h"
#include "ios.h"

#include "dvd.h"
#include "dvd_hw.h"

extern diskInfo_t       diskInfo;

static uint8_t     outBuf[1024 * 64];
void
dvd_high(void)
{
    IOSError    mesgError;
    IOSMessage  receiveMesg;

    diskInfo.dataWordOffset = (96 * 1024) / 4;

    /*
    IOSCid      connectId;
    connectId = IOS_Open("/tmp/di", 0);
    if (connectId == IOS_ERROR_NOEXISTS) {
        printf ("Error: pathname does not exist\n");
        exit(1);
    if (connectId <= 0) {
        printf ("Error: IOS_Open failed: %d (exiting)\n", connectId);
    }
    if (IOS_Close(connectId) != IOS_ERROR_OK) {
        printf ("Error: IOS_Close failed\n");
    }
    */


    /*
    interfaceDiCommand.theCommand = DI_READ_DISK_ID;
    interfaceDiCommand.arg[0] = (uint32_t) outBuf;

    mesgError = IOS_SendMessage(dvdDriverInQueue, DI_MESG_COMMAND,
                                IOS_MESSAGE_BLOCK);
    if (mesgError != IOS_ERROR_OK) {
        fprintf(stderr, "IOS_SendMessage failed - exit\n");
        IOS_DestroyThread(0);
    }

    printf ("Message sent, waiting on receive message\n");
    mesgError = IOS_ReceiveMessage(dvdDriverOutQueue, &receiveMesg,
                                   IOS_MESSAGE_BLOCK);
    if (mesgError != IOS_ERROR_OK) {
        fprintf(stderr, "IOS_SendMessage failed - exit\n");
        IOS_DestroyThread(0);
    }
    printf ("Message received: 0x%x\n", receiveMesg);
    */

    interfaceDiCommand.theCommand = DI_READ_RVL;
    interfaceDiCommand.arg[0] = (uint32_t) outBuf;
    interfaceDiCommand.arg[1] = 32;
    //interfaceDiCommand.arg[2] = (32 * 1024) - 32;
    interfaceDiCommand.arg[2] = 0;

    mesgError = IOS_SendMessage(dvdDriverInQueue, DI_MESG_COMMAND,
                                IOS_MESSAGE_BLOCK);
    if (mesgError != IOS_ERROR_OK) {
        fprintf(stderr, "IOS_SendMessage failed - exit\n");
        IOS_DestroyThread(0);
    }
    printf ("Message sent, waiting on receive message\n");
    mesgError = IOS_ReceiveMessage(dvdDriverOutQueue, &receiveMesg,
                                   IOS_MESSAGE_BLOCK);
    if (mesgError != IOS_ERROR_OK) {
        fprintf(stderr, "IOS_SendMessage failed - exit\n");
        IOS_DestroyThread(0);
    }
    printf ("Message received: 0x%x\n", receiveMesg);
    for (int i = 0; i < 16; i++) {
        printf ("0x%x \n", outBuf[i]);
    }

    /*
    interfaceDiCommand.theCommand = DI_READ_CMD;
    interfaceDiCommand.arg[0] = (uint32_t) outBuf;
    interfaceDiCommand.arg[1] = 32;
    interfaceDiCommand.arg[2] = 0;

    mesgError = IOS_SendMessage(dvdDriverInQueue, DI_MESG_COMMAND,
                                IOS_MESSAGE_BLOCK);
    if (mesgError != IOS_ERROR_OK) {
        fprintf(stderr, "IOS_SendMessage failed - exit\n");
        IOS_DestroyThread(0);
    }
    printf ("Message sent, waiting on receive message\n");
    mesgError = IOS_ReceiveMessage(dvdDriverOutQueue, &receiveMesg,
                                   IOS_MESSAGE_BLOCK);
    if (mesgError != IOS_ERROR_OK) {
        fprintf(stderr, "IOS_SendMessage failed - exit\n");
        IOS_DestroyThread(0);
    }
    printf ("Message received: 0x%x\n", receiveMesg);
    for (int i = 0; i < 16; i++) {
        printf ("0x%x \n", outBuf[i]);
    }
    */
}
