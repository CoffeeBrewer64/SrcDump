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
#include <sk.h>
#include <ng.h>
#include <sktypes.h>
#include <arm.h>
#include <nglibc.h>
#include <skusb.h>
#include <skusbtypes.h>
#include "emu_usb.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <errno.h>
#include <usb.h>

#define DEV_BASE "/dev/usb"
#define RHUB_OHCI "ohci"
#define RHUB_UHCI "uhci"
#define RHUB_EHCI "ehci"

#define SK_DEV_EHCI_MAX 2
#define EHCI_MSGQ_MAX   4
#define EHCI_PID_MASK 0xffffffff /* XXX choose more appropriate mask later */

static int __sk_EHCI_count = 0;
static int __sk_OHCI_count = 0;
static int __sk_UHCI_count = 0;

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
            USB_AddTree(devpath, SK_DEV_USB, emu_dev, -1);
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
    SKMessageQueueId qid;
    if ( dev->descriptor.bcdUSB >= 0x200 ) {
        sprintf(devpath,"%s/%s%d", DEV_BASE, RHUB_EHCI, __sk_EHCI_count++);
    }
    else if ( (udev = usb_open(dev))  &&  (dev->descriptor.iProduct) ) {
        if ( usb_get_string_simple(udev, dev->descriptor.iProduct, 
                    string, sizeof(string)) > 0 
                && NULL != strstr(string, "UHCI") ) {
            sprintf(devpath,"%s/%s%d", DEV_BASE, RHUB_UHCI, __sk_UHCI_count++);
        }
    }
    else 
        sprintf(devpath,"%s/%s%d", DEV_BASE, RHUB_OHCI, __sk_OHCI_count++);
    
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
    USB_AddTree(devpath, SK_DEV_USBHC, emu_dev, qid);
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

/* Returns # of devices found.
 * Space separated device pathnames in buf
 */

int
USB_find_device(u16 vendorId, u16 productId, char *buf, int buflen)
{
 return 0;
}
