a0 192
/* Derived from Nintendo's Eyetoy driver */
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
#include <iostypes.h>
#include <ios.h>
#include <iop.h>
#include <ioslibc.h>
#include "eyetoy.h"
#ifndef ENABLE_TEST
#define STACK_SIZE 8192
const u8        _initStack[STACK_SIZE];
const u32       _initStackSize = sizeof(_initStack);
const u32       _initPriority = 20;
#endif /* ENABLE_TEST */

#include "iosusbtypes.h"
#include "iosusb.h"

/* Some globals */
IOSFd fd0;

static void
__ctrlTransferTests(void)
{
    u8 buf[IOS_USB_STR_MAX];
    struct USB_DevDescr d;
    IUSB_GetDevDescr(fd0, &d); 

    printf("--- Ctrl transfer tests \n");
    if ( (d.iManufacturer != 0 )
            && (0 < IUSB_GetAsciiStr(fd0, 0, d.iManufacturer, 
                    USB_LANG_EN_US, buf, sizeof(buf))))
        printf("Manufacturer: %s\n", buf);
    if ( (d.iProduct != 0)
            && (0 < IUSB_GetAsciiStr(fd0, 0, d.iProduct, 
                    USB_LANG_EN_US, buf, sizeof(buf))) ) 
        printf("Product: %s\n", buf);

    if ( (d.iSerialNumber != 0)
            && (0 < IUSB_GetAsciiStr(fd0, 0, d.iSerialNumber, 
                    USB_LANG_EN_US, buf, sizeof(buf))) ) 
        printf("Serial number: %s\n", buf);
}

static IOSError
__sendRawCommand(USBRawCommand *cmd)
{
    IOSError rv;
    int i;
    u8 *cmdData = cmd->cmdData;
    u8 *xferData = cmd->xferData;
    u16 len = cmdData[6];
    rv = IUSB_WriteCtrlMsg(fd0,
            cmdData[0],
            cmdData[1],
            (u16) ((((u32)cmdData[3]) << 8) | ((u32)cmdData[2])),
            (u16) ((((u32)cmdData[5]) << 8) | ((u32)cmdData[4])),
            len,
            (0 != len)? xferData: NULL);
    for (i = 0; i < cmdData[6]; ++i) {
        printf("%02x ", (u8)xferData[i]);
    }
    printf("\n");
    return rv;
}

static void 
__sendRawCommandArray(USBRawCommand *cmd, u32 size)
{
  u32 i;
  for (i = 0; i < size; ++i) {
      printf("cmd %u:\t", i);
      __sendRawCommand(cmd + i);
  }
}

void
__initEyeToy(void)
{
  __sendRawCommandArray(USBEyeToyCmd, sizeof(USBEyeToyCmd)/sizeof(USBRawCommand));
}

static u8 buf[4096] __attribute__((aligned(4096)));
void
__initPacketSize(u16 *packetSize, u8 numpackets)
{
        packetSize[0] = 784;
        packetSize[1] = 128;
        packetSize[2] = 128;
        packetSize[3] = 128;
        packetSize[4] = 256;
        packetSize[5] = 128;
        packetSize[6] = 128;
        packetSize[7] = 368 ;

}

u8 vecBuf[1024];
u8 vecBuf1[1024];
u8 vecBuf2[1024];
u16 packetSize[8];
u16 packetSize1[8];
u16 packetSize2[8];
void
__isoTest()
{
    u8 ep = 0x06;
    u16 buflen = 2048;
    u8 numPackets = 8;
    //    u8 i;

    IOSError rv; 
    IOSMessage msgQ[8];
    IOSMessage msg;
    IOSMessageQueueId qid;
    IOSResourceRequest reply; 

    qid = IOS_CreateMessageQueue(msgQ, 8);
    printf("iso test: %p\n", buf);
   
    { 
        __initPacketSize(packetSize, 8);
        __initPacketSize(packetSize1, 8);
        __initPacketSize(packetSize2, 8);
        /* Initialize buffer */
        char *b = buf;
        memset(b, 0xab, packetSize[0]);
        b += packetSize[0];
        memset(b, 0xcd, packetSize[1]);
        b += packetSize[1];
        memset(b, 0xef, packetSize[2]);
        b += packetSize[2];
        memset(b, 0x12, packetSize[3]);
        b += packetSize[3];
        memset(b, 0x34, packetSize[4]);
        b += packetSize[4];
        memset(b, 0x56, packetSize[5]);
        b += packetSize[5];
        memset(b, 0x78, packetSize[6]);
        b += packetSize[6];
        memset(b, 0x9a, packetSize[7]);
    }
    printf("starting iso OUT transfers\n");
    rv = IUSB_IsoMsgAsync(fd0, &ep, &buflen, buf,
            &numPackets, (u16 *)packetSize1, 
            qid, &reply, vecBuf1);
    rv = IUSB_IsoMsgAsync(fd0, &ep, &buflen, buf,
            &numPackets, (u16 *)packetSize2, 
            qid, &reply, vecBuf2);
    while (1) {
        rv = IUSB_IsoMsgAsync(fd0, &ep, &buflen, buf,
                &numPackets, (u16 *)packetSize, 
                qid, &reply, vecBuf);
        if (rv >= 0) {
            IOS_ReceiveMessage(qid, &msg, IOS_MESSAGE_BLOCK);
            __initPacketSize(packetSize, 8);
        } else {
            printf("error rv = %d\n", rv);
            usleep(1000);
        }
    }

}

#ifdef ENABLE_TEST
void
ehci_test(u32 arg)
#else
void
main(u32 arg)
#endif
{
    do {
        fd0 = IOS_Open("/dev/usb/ehc/054c/0155", 0);
    }
    while (fd0 < 0);
    __ctrlTransferTests();
    __initEyeToy();
    __isoTest();
    IOS_Close(fd0);
    printf("audio driver exiting \n");
    IOS_DestroyThread(0, NULL);
    return;
}
