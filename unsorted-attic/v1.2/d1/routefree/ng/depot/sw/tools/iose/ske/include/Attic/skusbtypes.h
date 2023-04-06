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
#ifndef __SK_USBTYPES_H__
#define __SK_USBTYPES_H__

#include <ng.h>
#include <sktypes.h>
#include <ngtypes.h>
#include <arm.h>

#define SK_DEV_NODE_MAX 16
#define SK_DEV_CHLD_MAX 4
#define SK_DEV_NAME_MAX 8 /* [a-zA-Z0-9_-] */

typedef enum {SK_DEV_UNUSED, SK_DEV_USED, SK_DEV_DUMMY, SK_DEV_USBROOT, SK_DEV_USBHC, SK_DEV_USB} SKDevType; 

struct SKDevice {
    char name[SK_DEV_NAME_MAX];
    SKDevType typ;
    void *dev; /* device-type specific struct */
    SKMessageQueueId driverQId;
    SKMessageQueueId hcdQId;
    int parent;
    int chld[SK_DEV_CHLD_MAX];
};
typedef struct SKDevice SKDevice_t;

/* Commands that can be sent to the emulated hcd. */
typedef enum {   
                USB_SUBMIT_UTP = 123
               , USB_REAP_UTP
               , USB_CANCEL_UTP
               , USB_WRITE_INTR_MSG
               , USB_READ_INTR_MSG
               , USB_WRITE_BULK_MSG
               , USB_READ_BULK_MSG
               , USB_WRITE_CTRL_MSG
               , USB_GET_DEV_DESCR
               , USB_GET_CONF_DESCR
              } USB_hcdreq_t;

struct USB_hcd_msg {
    void *req;
    USB_hcdreq_t typ; 
    SKCid devId; /* Index into devnodes for now*/ 
    SKMessageQueueId replyQid;
};
typedef struct USB_hcd_msg USB_hcd_msg_t;

struct USB_hcdreq_ctrl {
    u8 bRequestType; 
    u8 bRequest;
    u16 wValue;
    u16 wIndex;
    u16 wLength;
    u8  endpt;
    u32 data;
};
typedef struct USB_hcdreq_ctrl USB_hcdreq_ctrl_t;

struct USB_hcdreq_getstr{
    u16 idx;
    u16 lang;
    u32 buflen;
    u32 buf;
};
typedef struct USB_hcdreq_getstr USB_hcdreq_getstr_t;

struct USB_hcdreq_bulk{
    u8 endpt;
    u32 buflen;
    u32 buf;
};
typedef struct USB_hcdreq_bulk USB_hcdreq_bulk_t;

struct USB_hcdreq_intr{
    u8 endpt;
    u32 buflen;
    u32 buf;
};
typedef struct USB_hcdreq_intr USB_hcdreq_intr_t;

/* Definitions from the USB standard */

/* See http://www.usb.org/developers/docs/USB_LANGIDS.pdf */
#define USB_STD_LANG_EN_US 0x0409

/* USB descriptor types */
#define USB_STD_DT_DEVICE			0x01
#define USB_STD_DT_CONFIG			0x02
#define USB_STD_DT_STRING			0x03
#define USB_STD_DT_INTERFACE		0x04
#define USB_STD_DT_ENDPOINT			0x05

#define USB_STD_DT_HID			0x21
#define USB_STD_DT_REPORT			0x22
#define USB_STD_DT_PHYSICAL			0x23
#define USB_STD_DT_HUB			0x29

/* USB requests */
#define USB_STD_REQ_GET_STATUS		0x00
#define USB_STD_REQ_CLEAR_FEATURE		0x01
/* 0x02 is reserved */
#define USB_STD_REQ_SET_FEATURE		0x03
/* 0x04 is reserved */
#define USB_STD_REQ_SET_ADDRESS		0x05
#define USB_STD_REQ_GET_DESCRIPTOR		0x06
#define USB_STD_REQ_SET_DESCRIPTOR		0x07
#define USB_STD_REQ_GET_CONFIGURATION	0x08
#define USB_STD_REQ_SET_CONFIGURATION	0x09
#define USB_STD_REQ_GET_INTERFACE		0x0A
#define USB_STD_REQ_SET_INTERFACE		0x0B
#define USB_STD_REQ_SYNCH_FRAME		0x0C

#define USB_STD_TYPE_STANDARD		(0x00 << 5)
#define USB_STD_TYPE_CLASS			(0x01 << 5)
#define USB_STD_TYPE_VENDOR			(0x02 << 5)
#define USB_STD_TYPE_RESERVED		(0x03 << 5)

#define USB_RECIP_DEVICE		0x00
#define USB_RECIP_INTERFACE		0x01
#define USB_RECIP_ENDPOINT		0x02
#define USB_RECIP_OTHER			0x03

#define USB_ENDPT_IN_FLAG			0x80
#define USB_ENDPT_OUT_FLAG 		0x00

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
struct USB_DevDescr{
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
};
typedef struct USB_DevDescr USB_DevDescr_t;
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
/* Interface descriptor */
#define USB_MAX_ENDPOINTS 16
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
/* Configuration descriptor */
#define USB_MAX_ALTSETTINGS 8
struct USB_ConfDescr{
    u8  bLength;
    u8  bDescriptorType;
    u16 wTotalLength;
    u8  bNumInterfaces;
    u8  bConfigurationValue;
    u8  iConfiguration;
    u8  bmAttributes;
    u8  MaxPower;
    u8 numAltSettings;
    struct USB_IntfDescr intf[USB_MAX_ALTSETTINGS];
};
typedef struct USB_ConfDescr USB_ConfDescr_t;

/* USB Transfer Packet */
struct USB_TransPkt {        
    u8 type;
    u8 endpt;
    u32 flags;
    u32 buflen;
    u32 buf;
    u32 datalen;
    int status;
};
typedef struct USB_TransPkt  USB_TransPkt_t;
#endif /* __SK_USBTYPES_H__ */
