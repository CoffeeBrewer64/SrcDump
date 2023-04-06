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
#ifndef __EMU_USB__
#define __EMU_USB__
#include <usb.h> /* from libusb */
#include <skusbtypes.h>

#define USB_EHCI_MSGQ_MAX   4
#define USB_EHCI_PID_MASK 0xffffffff /* XXX choose more appropriate mask later */
#define USB_DEV_PIDMASK 0xffffffff
#define USB_HCD_INQ_MAX 8
struct USB_emu_device {
    struct usb_device *dev;
    struct usb_dev_handle *handle;
    SKMessage inQ[USB_HCD_INQ_MAX];
    u16 idVendor;
    u16 idProduct;
};
typedef struct USB_emu_device USB_emu_device_t;

SKMessageQueueId USB_CreateHcd(SKMessage *inQ);
int USB_EmuTreeInit(void); 
extern void USB_AddTree(const char *path, SKDevType typ, void *dev, SKMessageQueueId driverQId);
#endif /* _EMU_USB__ */
