a0 279
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

#ifndef ENABLE_TEST
#define STACK_SIZE 8192
const u8        _initStack[STACK_SIZE];
const u32       _initStackSize = sizeof(_initStack);
const u32       _initPriority = 20;
#endif /* ENABLE_TEST */

/* Sample mouse driver */
#include "iosusbtypes.h"
#include "iosusb.h"

static void
__ctrlTransferTests(IOSFd fd)
{
    u8 buf[IOS_USB_STR_MAX];
    struct USB_DevDescr d;
    IUSB_GetDevDescr(fd, &d); 

    printf("--- Ctrl transfer tests \n");
    if ( (d.iManufacturer != 0 )
            && (0 < IUSB_GetAsciiStr(fd, 0, d.iManufacturer, 
                    USB_LANG_EN_US, buf, sizeof(buf))))
        printf("Manufacturer: %s\n", buf);
    if ( (d.iProduct != 0)
            && (0 < IUSB_GetAsciiStr(fd, 0, d.iProduct, 
                    USB_LANG_EN_US, buf, sizeof(buf))) ) 
        printf("Product: %s\n", buf);

    if ( (d.iSerialNumber != 0)
            && (0 < IUSB_GetAsciiStr(fd, 0, d.iSerialNumber, 
                    USB_LANG_EN_US, buf, sizeof(buf))) ) 
        printf("Serial number: %s\n", buf);
}

#if 0

static void 
__getConfDescr(IOSFd fd, u8 *buf, u16 size)
{
    IUSB_ReadCtrlMsg(fd, 0x80, 0x06, SWAP16(0x0002), 0, size, buf);
}

static void 
__confDescrTest(IOSFd fd, u8 *buf, u16 size)
{
    u8 i;
    u8 dbuf[32]; /* size < 32 */
    __getConfDescr(fd, buf, size);
    __getConfDescr(fd, dbuf, size);
    for ( i = 0; i < size; ++i) {
     if (buf[i] != dbuf[i]) printf("***ERROR:  ");
     
     printf("    %u: DDR[%p] = 0x%02x  SRAM[%p] = 0x%02x\n",
             i, dbuf+i, dbuf[i], buf+i,  buf[i]);
    }
}

static void
__test1byteTransfer(IOSFd fd, u8 *buf)
{
    printf("--- 1 byte transfer test: \n");
    printf("    Get 9 bytes of conf descr in: %p\n", buf);
    __confDescrTest(fd, buf, 9);
}

static void
__test2byteTransfer(IOSFd fd, u8 *buf)
{
    printf("--- 2 byte transfer test: \n");
    printf("    Get 18 bytes of conf descr in supplied buffer : %p\n", buf);
    __confDescrTest(fd, buf, 18);
}

void
__test4byteTransfer(IOSFd fd, u8 *buf)
{
    printf("--- 4 byte transfer test: \n");
    printf("    Get 20 bytes of conf descr in supplied buffer : %p\n", buf);
    __confDescrTest(fd, buf, 20);
}

/* Interrupt transfer test */
void
__intrTransferTest(IOSFd fd, u8 *data)
{
    u8 i;
    u8 k;
    printf("--- Interrupt transfer tests to dstn buffer: %p\n", data);
    for (i = 0; i < 4; ++i) {
        printf("mouse: waiting for data sample %u: \n", i);
        memset(data, 0, 8);
        IUSB_ReadIntrMsg(fd, 0x81, 8, data);
        for (k = 0; k < 8; ++k )
            printf("mouse: data[0x%08x] = 0x%02x\n", data + k, data[k] & 0xff);
    }
}
#endif
/* Generate error */
#ifdef GENERATE_CTRL_ERR
static void
__genError(IOSFd fd0)
{
    USBCtrlReq req;

    req.bmRequestType = 0x80; /* USB_REQTYPE_GETDESC */
    req.bRequest = 0xff; /* junk */
    req.wValue = 0;
    req.wIndex = 0;
    req.wLength = SWAP16(24); /* junk */
    req.data = (u32)0;
    req.ep = 0; /* junk */
    printf("sending junk ioctl\n");
    IOS_Ioctl(fd0, OHC_CTRL_MSG, &req, sizeof(USBCtrlReq), 0, 0);
}
#endif /* GENERATE_CTRL_ERR */

#if 0
void
__getDevListTestInt(u8 class)
{
  u8 numDev;
  u8 i = 0;
  IOSError rv;
  USBDeviceInfo deviceList[8];
#if OH0
  rv = IUSB_GetDeviceList("/dev/usb/oh0", deviceList, 8, class, &numDev);
#else 
  rv = IUSB_GetDeviceList("/dev/usb/oh1", deviceList, 8, class, &numDev);
#endif
  if (rv < 0) {
      printf("Get device list failed: %d\n", rv);
      goto done;
  }
  for (i = 0; i < numDev; ++i) {
      printf("\tdevice %u vid = %x pid = %x\n", i, deviceList[i].vid,
              deviceList[i].pid);
  }
done:
  return;
}
static void
__getDevListTest(void)
{
    printf("Getting device list (all connected devices):\n");
    __getDevListTestInt(0);

    printf("Getting list of connected devices of class: 0x03\n");
    __getDevListTestInt(0x03);
}

#if defined(ENABLE_TEST_FUNCTIONS)
#define OHCI_RHUB_DESCA_NDP_MASK  0x000000ff
#define OHCI_RHUB_DESCA_NDP_SHIFT  0

static u8 ndp = 0;
static void
__getRhDescaTest(IOSFd fd)
{
    u32 desca;
    IOSError rv;
    if ((rv = IUSB_GetRhDesca(fd, &desca)) <0) {
        printf("GetRhDesca failed: %d fd = %d\n", rv, fd);
    }
    else {
        printf("RHDESCA = 0x%08x\n", desca);
        ndp = (desca & OHCI_RHUB_DESCA_NDP_MASK) >> OHCI_RHUB_DESCA_NDP_SHIFT;
        printf("Number of downstream ports = %u\n", ndp);
    }
}

static void
__getRhPstatTest(IOSFd fd)
{
    u32 pstat;
    u8 port;
    IOSError rv;
    for (port = 0; port < ndp; ++port) {
        if ((rv = IUSB_GetRhPortStatus(fd, port, &pstat)) <0) {
            printf("GetRhPortStatus[%u] failed: %d\n", port, rv);
        }
        else {
            printf("RHPstat[%u] = 0x%08x\n", port, pstat);
        }
    }
    /* Expect port == ndp to fail */
    if ((rv = IUSB_GetRhPortStatus(fd, port, &pstat)) <0)  {
        printf("RHPstat[invalid port %u] should fail: %d (PASSED)\n", port, rv);
    }
    else {
        printf("RHPstat[invalid port %u] should fail: %d (FAILED)\n", port, rv);
    }
}
#endif

void
 __registerRemovalHandlerTest(IOSFd fd)
{
    IOSError rv;
    IOSMessage msgQ[1];
    IOSMessage msg;
    IOSMessageQueueId qid;
    IOSResourceRequest reply; 
    qid = IOS_CreateMessageQueue(msgQ, 1);
    rv = IUSB_RegisterRemovalNotify(fd, qid, &reply);
    if (rv < 0) {
        printf("registering removal notification handler failed: %d\n", rv);
    }
    else {
        printf("registering removal notification handler succeeded: %d\n", rv);
        printf("waiting for device removal...\n");
        IOS_ReceiveMessage(qid, &msg, IOS_MESSAGE_BLOCK);
        printf("device removed\n");
    }
}
#endif 
void
__isoTest(IOSFd fd0)
{
    u8 buf[4096] __attribute__((aligned(4096)));
    u8 vecBuf[1024];
    IOSError rv; 
    IOSMessage msgQ[1];
    IOSMessage msg;
    IOSMessageQueueId qid;
    IOSResourceRequest reply; 
    u8 ep = 0x06;
    u16 buflen = 512;
    u16 pktsize = 128;

    qid = IOS_CreateMessageQueue(msgQ, 1);
    printf("iso test: %p\n", buf);
    rv = IUSB_IsoWriteMsgAsync(fd0, &ep, &buflen, buf,
            &pktsize, qid, &reply, vecBuf);
    if (rv < 0) {
        printf("iso write msg async failed: %d\n", rv);
    } else {
        printf("waiting for iso write async reply\n");
        IOS_ReceiveMessage(qid, &msg, IOS_MESSAGE_BLOCK);
        printf("iso write async done\n");
    }

}

#ifdef ENABLE_TEST
void
ohci_test(u32 arg)
#else
void
main(u32 arg)
#endif
{
    IOSFd fd0;
    do {
        fd0 = IOS_Open("/dev/usb/oh0/0d8c/0001", 0);
    }
    while (fd0 < 0);

    __ctrlTransferTests(fd0);
    __isoTest(fd0);
    IOS_Close(fd0);
    printf("mouse: driver exiting \n");
    IOS_DestroyThread(0, NULL);
    return;
}
