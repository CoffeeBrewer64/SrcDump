a0 122
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
#define STACK_SIZE 2048
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

static void
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

static void
__registerInsertionHandlerTest(const char *path, u16 vid, u16 pid)
{
    IOSError rv;
    IOSMessage msgQ[1];
    IOSMessage msg;
    IOSMessageQueueId qid;
    IOSResourceRequest reply; 
    u8 buffer[IUSB_DEVINSERT_BUFSIZE];
    qid = IOS_CreateMessageQueue(msgQ, 1);
    if (qid < 0) {
        printf("test: creating message queue failed\n");
        goto done;
    }
    rv = IUSB_RegisterInsertionNotify(path, qid, &reply, &vid, &pid, (u8 *) buffer);
    if (rv < 0) {
        printf("test: registering insertion notification handler failed: %d\n", rv);
    } else {
        printf("test: registering insertion notification handler succeeded\n");
        printf("test: waiting for device insertion...\n");
        rv = IOS_ReceiveMessage(qid, &msg, IOS_MESSAGE_BLOCK);
        if (IOS_ERROR_OK != rv) {
            printf("test: failed to receive msg: %d\n", rv);
        } else { 
            printf("test: device vid: 0x%04x pid: 0x%04x inserted\n", vid, pid);
        }
    }
done:
    return;
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

    while (1) {
        __registerInsertionHandlerTest("/dev/usb/oh0", 0x046d, 0x0c016);
        fd0 = IOS_Open("/dev/usb/oh0/046d/c016", 0);
        __ctrlTransferTests(fd0);
        __registerRemovalHandlerTest(fd0);
        IOS_Close(fd0);
    }
    printf("mouse: driver exiting \n");
    IOS_DestroyThread(0, NULL);
    return;
}
