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
#include <ios.h>
#include <iosdebug.h>
#include "emu_usb.h"

#include <stdio.h>
#include <string.h>
#include <usb.h>

#define DEV_BASE "/dev/usb"
#define RHUB_OHCI "ohci"
#define RHUB_UHCI "uhci"
#define RHUB_EHCI "ehci"

#define IOS_DEV_EHCI_MAX 2
#define EHCI_MSGQ_MAX   4
#define EHCI_PID_MASK 0xffffffff /* XXX choose more appropriate mask later */

static int __ios_EHCI_count = 0;
static int __ios_OHCI_count = 0;
static int __ios_UHCI_count = 0;
extern IOSMessageQueueId iosCreateMessageQueue(IOSMessage *msgarray, u32 size, u32 pidMask);
void dumpNode( IOSDevice_t node);
IOSError iosDestroyMessageQueue(IOSMessageQueueId id);
IOSThreadId iosGetThreadId(void);

extern IOSDevice_t  __devnodes[];
extern int __devroot;

int
gen_node(struct usb_device *dev, int level, char *devpath)
{
    int i;
    char mydevpath[128];
    USB_emu_device_t *emu_dev;
    if ( level > 0 ) {
        char devpathtmp[8];
        sprintf(devpathtmp, "/dev%d/", dev->devnum);
        strcat(devpath, devpathtmp);
        if ( 0 == dev->num_children ) /* non-hub leaves */ {
            emu_dev = (USB_emu_device_t *) malloc(sizeof(USB_emu_device_t));
            emu_dev->dev = dev;
            emu_dev->handle = usb_open(dev);
            emu_dev->idVendor = dev->descriptor.idVendor;
            emu_dev->idProduct = dev->descriptor.idProduct;
            USB_AddTree(devpath, IOS_DEV_USB, emu_dev, -1);
        }
    }
    for (i = 0; i < dev->num_children; i++) {
        strcpy(mydevpath, devpath);
        gen_node(dev->children[i], level + 1, mydevpath);
    }
    return 0;
}

int
gen_hub(struct usb_device *dev, char *devpath)
{
    char string[256];
    USB_emu_device_t *emu_dev;
    usb_dev_handle *udev;
    IOSMessageQueueId qid;
    if ( dev->descriptor.bcdUSB >= 0x200 ) {
        sprintf(devpath,"%s/%s%d", DEV_BASE, RHUB_EHCI, __ios_EHCI_count++);
    }
    else if ( (udev = usb_open(dev))  &&  (dev->descriptor.iProduct) ) {
        if ( usb_get_string_simple(udev, dev->descriptor.iProduct, 
                    string, sizeof(string)) > 0 
                && NULL != strstr(string, "UHCI") ) {
            sprintf(devpath,"%s/%s%d", DEV_BASE, RHUB_UHCI, __ios_UHCI_count++);
        }
    }
    else 
        sprintf(devpath,"%s/%s%d", DEV_BASE, RHUB_OHCI, __ios_OHCI_count++);

    emu_dev = (USB_emu_device_t *) malloc(sizeof(USB_emu_device_t));
    if ( NULL == emu_dev ) {
        printf("malloc for emu_dev failed\n");
        return -1;
    }
    emu_dev->dev = dev;
    emu_dev->handle = usb_open(dev);
    qid = USB_CreateHcd(emu_dev->inQ);
    emu_dev->idVendor = dev->descriptor.idVendor;
    emu_dev->idProduct = dev->descriptor.idProduct;
    USB_AddTree(devpath, IOS_DEV_USBHC, emu_dev, qid);
    return 0;
}

int
USB_EmuTreeInit(void) 
{
    struct usb_bus *bus;
    char devpath[128];
    usb_init();
    usb_find_busses();
    usb_find_devices();
    for (bus = usb_busses; bus; bus = bus->next) {
        if ( bus->root_dev != NULL ) {
            if ( -1 != gen_hub(bus->root_dev, devpath) )
                gen_node(bus->root_dev, 0, devpath);
        }
    }
    return 0;
}

/* 0 - claim
 * 1 - free 
 */
static void
emuClaimOrRelIntf(IOSCid fd, int typ)
{
    int numConf;
    int i, j, k;
    struct usb_device *udev;
    USB_emu_device_t *usb_dev;
    IOSDevice_t *d = &__devnodes[fd];
    usb_dev = (USB_emu_device_t *) d->dev;
    udev = usb_dev->dev;
    numConf = udev->descriptor.bNumConfigurations;
    for (i = 0; i < numConf; ++i) {
        for (j = 0; j < udev->config[i].bNumInterfaces; ++j ) {
            for (k = 0; k < udev->config[i].interface[j].num_altsetting; ++ k) {
                if ( 0 == typ) {
                    usb_claim_interface(usb_dev->handle, udev->config[i].interface[j].altsetting[k].bInterfaceNumber);
                    DBG_PRINTF((dbg_fp,"Claiming interface #: %d\n", udev->config[i].interface[j].altsetting[k].bInterfaceNumber));
                }
                else {
                    usb_release_interface(usb_dev->handle, udev->config[i].interface[j].altsetting[k].bInterfaceNumber);
                    DBG_PRINTF((dbg_fp,"Releasing interface #: %d\n", udev->config[i].interface[j].altsetting[k].bInterfaceNumber));
                }

            }
        }
    }
    dumpNode(*d);
    return;
}

IOSError 
usbRegisterResourceManager(IOSCid fd)
{
    IOSDevice_t *d = &__devnodes[fd];
    IOSError ret = IOS_ERROR_OK;

    /* Verify this node is a USB device and no driver has claimed
     * it already. 
     */
    if ( d->typ != IOS_DEV_USB ) {
        ret = IOS_ERROR_INVALID;
        DBG_PRINTF((dbg_fp, "IUSB_RegisterResource: Invalid node.. typ(%d) != DEV_USB(%d)\n", d->typ, IOS_DEV_USB));
        goto done;
    }
    if ( d->drvQId != -1 ) {
        ret = IOS_ERROR_EXISTS;
        DBG_PRINTF((dbg_fp,"IUSB_RegisterResource: Driver already exists..\n"));
        goto done;
    }
    d->drvTId = iosGetThreadId();
    DBG_PRINTF((dbg_fp,"IUSB_RegisterResource: setting thread id of drvr: %d\n", d->drvTId));

    /* Create a message-queue for driver */
    d->drvQId = iosCreateMessageQueue(d->drvMsgQ, IUSB_DRV_MSGQ_MAX, IUSB_DRV_PID_MASK);
    if ( d->drvQId < 0 ) {
        ret = d->drvQId;
        DBG_PRINTF((dbg_fp,"IUSB_RegisterResource: Message queue creation failed..\n"));
        goto done;
    }
    /* Emulation only: "claim" all interfaces */
    emuClaimOrRelIntf(fd, 0);
done:
    return ret;
}

IOSError 
usbUnregisterResourceManager(IOSCid fd)
{
    IOSDevice_t *d = &__devnodes[fd];
    IOSError ret = IOS_ERROR_OK;

    dumpNode(*d);
    /* Verify this device is a USB device and that 
     * current thread is the driver for this device
     */
    if ( d->drvTId != iosGetThreadId() ) {
        ret = IOS_ERROR_INVALID;
        DBG_PRINTF((dbg_fp,"IUSB_UnregisterResourceManager: Thread is not registered\n"));
        DBG_PRINTF((dbg_fp,"IUSB_RegisterResource: thread id of drvr: %d current thread id %d\n", d->drvTId, iosGetThreadId()));
        goto done;
    }

    /* Destroy message-queue for driver and mark unclaimed */
    iosDestroyMessageQueue(d->drvQId);
    d->drvQId = -1;
    d->drvTId = -1;

    /* Emulation only: "release" interface */
    emuClaimOrRelIntf(fd, 1);
done:
    return ret;
}
