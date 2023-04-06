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
#ifndef __IOS_USB11TYPES_H__
#define __IOS_USB11TYPES_H__

/* Definitions from the USB standard */
#include <ios.h>
#include <iostypes.h>


/* See http://www.usb.org/developers/docs/USB_LANGIDS.pdf */
#ifndef USB_LANG_EN_US 
#define USB_LANG_EN_US 0x0409
#endif /* USB_LANG_EN_US */

/* USB descriptor types */
#define USB_DT_DEVICE			0x01
#define USB_DT_CONFIG			0x02
#define USB_DT_STRING			0x03
#define USB_DT_INTERFACE		0x04
#define USB_DT_ENDPOINT			0x05

#define USB_DT_HID		    	0x21
#define USB_DT_REPORT			0x22
#define USB_DT_PHYSICAL			0x23
#define USB_DT_HUB			    0x29

/* USB Class codes */
#define USB_CLASS_UNDEF  0x00
#define USB_CLASS_AUDIO  0x01
#define USB_CLASS_COMM   0x02
#define USB_CLASS_HID    0x03
/* no 0x04 */
#define USB_CLASS_PHYS   0x05
#define USB_CLASS_IMG    0x06
#define USB_CLASS_PRN    0x07
#define USB_CLASS_MASS   0x08
#define USB_CLASS_HUB    0x09
#define USB_CLASS_CDC    0x0a
#define USB_CLASS_SMRT   0x0b
#define USB_CLASS_CSEC   0x0d
#define USB_CLASS_VIDEO  0x0e
#define USB_CLASS_DIAG   0xdc
#define USB_CLASS_WLESS  0xe0
#define USB_CLASS_MISC   0xef
#define USB_CLASS_APP    0xfe
#define USB_CLASS_VEND   0xff

/* USB requests */
#define USB_REQ_GET_STATUS		0x00
#define USB_REQ_CLEAR_FEATURE	0x01
/* 0x02 is reserved */
#define USB_REQ_SET_FEATURE		0x03
/* 0x04 is reserved */
#define USB_REQ_SET_ADDRESS		0x05
#define USB_REQ_GET_DESCRIPTOR		0x06
#define USB_REQ_SET_DESCRIPTOR		0x07
#define USB_REQ_GET_CONFIGURATION	0x08
#define USB_REQ_SET_CONFIGURATION	0x09
#define USB_REQ_GET_INTERFACE		0x0A
#define USB_REQ_SET_INTERFACE		0x0B
#define USB_REQ_SYNCH_FRAME	    	0x0C
#define USB_SETUP_REQ_SIZE           8 /* 8 bytes */

#define USB_REQ_TYPE_STANDARD		(0x00 << 5)
#define USB_REQ_TYPE_CLASS			(0x01 << 5)
#define USB_REQ_TYPE_VENDOR			(0x02 << 5)
#define USB_REQ_TYPE_RESERVED		(0x03 << 5)

#define USB_REQ_RECIP_DEVICE		0x00
#define USB_REQ_RECIP_INTERFACE		0x01
#define USB_REQ_RECIP_ENDPOINT		0x02
#define USB_REQ_RECIP_OTHER			0x03

#define USB_ENDPT_IN_FLAG		0x80
#define USB_ENDPT_OUT_FLAG 		0x00

#define USB_ENDPT_ATTR_CTRL  0x0
#define USB_ENDPT_ATTR_ISO   0x1
#define USB_ENDPT_ATTR_BLK   0x2
#define USB_ENDPT_ATTR_INTR  0x3
#define USB_ENDPT_ATTR_MASK  0x3

#define USB_REQ_HOST2DEV    0x00
#define USB_REQ_DEV2HOST    0x80

/* Pre-composed bmRequestType */
#define USB_REQTYPE_CLRFEAT_0      0x0
#define USB_REQTYPE_CLRFEAT_INTF   0x1
#define USB_REQTYPE_CLRFEAT_EP     0x2
#define USB_REQTYPE_GETCONFIG      0x80
#define USB_REQTYPE_GETDESC        0x80
#define USB_REQTYPE_GETINTF        0x81
#define USB_REQTYPE_GETSTAT_0      0x80
#define USB_REQTYPE_GETSTAT_INTF   0x81
#define USB_REQTYPE_GETSTAT_EP     0x82
#define USB_REQTYPE_SETADDR        0x0
#define USB_REQTYPE_SETCONFIG      0x0
#define USB_REQTYPE_SETDESC        0x0
#define USB_REQTYPE_SETFEAT_0      0x0
#define USB_REQTYPE_SETFEAT_INTF   0x1
#define USB_REQTYPE_SETFEAT_EP     0x1
#define USB_REQTYPE_SETINTF        0x1
#define USB_REQTYPE_SYNCFRM        0x82






/* Header for descriptors */
struct USB_DescrHdr{
    u8  bLength;
    u8  bDescriptorType;
};
/*
struct USB_StrDescr {
    u8  bLength;
    u8  bDescriptorType;
    u16 wData[8];
};
*/

/* Device descriptor */
#ifndef __HAVE_USB_DEVDESCR__
#define USB_DEVDESCR_SIZE 18
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

/* Endpoint descriptor */
struct USB_EpDescr{
    u8  bLength;
    u8  bDescriptorType;
    u8  bEndpointAddress;
    u8  bmAttributes;
    u16 wMaxPacketSize;
    u8  bInterval;
};
typedef struct USB_EpDescr USB_EpDescr_t;
#define  USB_EPDESCR_bLength               0
#define  USB_EPDESCR_bDescriptorType       1
#define  USB_EPDESCR_bEndpointAddress      2
#define  USB_EPDESCR_bAttributes           3
#define  USB_EPDESCR_wMaxPacketSize        4
#define  USB_EPDESCR_bInterval             6
#define EPDESCR_FIELD(ptr, field) \
    (ptr + USB_EPDESCR_##field)

#define USB_MAX_ENDPOINTS 4
struct USB_IntfDescr{
    u8  bLength;
    u8  bDescriptorType;
    u8  bInterfaceNumber;
    u8  bAlternateSetting;
    u8  bNumEndpoints;
    u8  bInterfaceClass;
    u8  bInterfaceSubClass;
    u8  bInterfaceProtocol;
    u8  iInterface;
    struct USB_EpDescr ep[USB_MAX_ENDPOINTS] ;
};
typedef struct USB_IntfDescr USB_IntfDescr_t;

#define  USB_INTFDESCR_bLength               0
#define  USB_INTFDESCR_bDescriptorType       1
#define  USB_INTFDESCR_bInterfaceNumber      2
#define  USB_INTFDESCR_bAlternateSetting     3
#define  USB_INTFDESCR_bNumEndpoints         4
#define  USB_INTFDESCR_bInterfaceClass       5
#define  USB_INTFDESCR_bInterfaceSubClass    6
#define  USB_INTFDESCR_bInterfaceProtocol    7
#define  USB_INTFDESCR_iInterface            8
#define INTFDESCR_FIELD(ptr, field) \
    (ptr + USB_INTFDESCR_##field)

#define USB_MAX_ALTSETTINGS 4
typedef struct USB_IntfDescrSet {
   USB_IntfDescr_t intf[USB_MAX_ALTSETTINGS];
   u8 numAltSettings;

} USB_IntfDescrSet_t;

/* Configuration descriptor */
#define USB_MAX_INTFS 8 /* interfaces * alt_settings */
struct USB_ConfDescr{
    u8  bLength;
    u8  bDescriptorType;
    u16 wTotalLength;
    u8  bNumInterfaces;
    u8  bConfigurationValue;
    u8  iConfiguration;
    u8  bmAttributes;
    u8  MaxPower;
    USB_IntfDescrSet_t intfSet[USB_MAX_INTFS];
};
typedef struct USB_ConfDescr USB_ConfDescr_t;

/* Descriptors used internally */
#define CONFDESCR_NOINTF_SIZE  9

struct USB_ConfDescrNoIntf{
    u8  bLength;
    u8  bDescriptorType;
    u16 wTotalLength;
    u8  bNumInterfaces;
    u8  bConfigurationValue;
    u8  iConfiguration;
    u8  bmAttributes;
    u8  MaxPower;
};

#define  USB_CONFDESCR_bLength                 0
#define  USB_CONFDESCR_bDescriptorType         1
#define  USB_CONFDESCR_wTotalLength            2
#define  USB_CONFDESCR_bNumInterfaces          4
#define  USB_CONFDESCR_bConfigurationValue     5
#define  USB_CONFDESCR_iConfiguration          6
#define  USB_CONFDESCR_bmAttributes            7
#define  USB_CONFDESCR_bMaxPower               8
#define CONFDESCR_FIELD(ptr, field) \
    (ptr + USB_CONFDESCR_##field)
#endif /* __IOS_USB11TYPES_H__ */
