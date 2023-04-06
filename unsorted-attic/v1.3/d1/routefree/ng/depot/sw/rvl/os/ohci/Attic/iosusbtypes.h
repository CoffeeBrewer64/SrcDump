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
#ifndef __IOS_USBTYPES_H__
#define __IOS_USBTYPES_H__

/* Note about the addr field in these structs:
 *   You don't need to set the device address. If you do, it
 *   will be ignored.
 */

/* Request for control transfers */
typedef struct {
    u8 bmRequestType;
    u8 bRequest;
    u16 wValue;
    u16 wIndex;
    u16 wLength;
    u32 data;
    u8 ep;
    u8 addr;  
} USBCtrlReq;

/* Request for bulk and interrupt transfers */
typedef struct {
    u8 ep;
    u8 addr; 
    u16 wLength;
    u32 data;
} USBIntrBlkReq;

/* Ioctl commands */
#define OHC_CTRL_MSG           0         
#define OHC_BLK_MSG            1
#define OHC_INTR_MSG           2

#define SWAP32(val) \
    ((u32)( \
            (((u32)(val) & (u32)0x000000ffUL) << 24) | \
            (((u32)(val) & (u32)0x0000ff00UL) <<  8) | \
            (((u32)(val) & (u32)0x00ff0000UL) >>  8) | \
            (((u32)(val) & (u32)0xff000000UL) >> 24) ))

#define SWAP16(val) \
    ((u16)( \
            (((u16)(val) & (u16)0x00ffUL) << 8) | \
            (((u16)(val) & (u16)0xff00) >> 8) ))

/* Device descriptor */
#ifndef __HAVE_USB_DEVDESCR__
typedef struct USB_DevDescr{
    u8 bLength;
    u8 bDescriptorType;
    u16 bcdUSB;
    u8 bDeviceClass;
    u8 bDeviceSubClass;
    u8 bDeviceProtocol;
    u8 bMaxPacketSize0;
    u16 idVendor;
    u16 idProduct;
    u16 bcdDevice;
    u8 iManufacturer;
    u8 iProduct;
    u8 iSerialNumber;
   u8 bNumConfigurations;
} USB_DevDescr_t;
#define __HAVE_USB_DEVDESCR__ 1
#endif /* !__HAVE_USB_DEVDESCR__ */

/* See http://www.usb.org/developers/docs/USB_LANGIDS.pdf */
#ifndef USB_LANG_EN_US 
#define USB_LANG_EN_US 0x0409
#endif /* USB_LANG_EN_US */
#endif /* __IOS_USBTYPES_H__ */
