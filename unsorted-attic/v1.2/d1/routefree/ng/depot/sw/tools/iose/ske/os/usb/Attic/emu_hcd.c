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
#include <skusbtypes.h>
#include <skusb.h>
#include <arm.h>
#include <nglibc.h>
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
#include <skusb.h>
#include <usb.h>

extern SKDevice_t  __devnodes[];
extern int __devroot;


/* Command handlers begin */
static SKError
__usbHandleSubmitUTP(USB_hcd_msg_t *msg)
{
    USB_TransPkt_t *utp;
    USB_emu_device_t *usb_dev;
    usb_dev_handle *udev;
    int *reply = malloc(sizeof(int)); /* caller frees */
    *reply = -1;
    if ( NULL == msg || NULL == reply) {
        printf("req message is null or malloc failed\n");
        goto done;
    }
    usb_dev = __devnodes[msg->devId].dev;
    if ( NULL == usb_dev ) {
        printf("dev is null\n");
        goto done;
    }
    udev = usb_dev->handle;
    utp = (USB_TransPkt_t *)msg->req;
    if ( NULL == utp ) {
        printf("handleSubmitUTP: got invalid UTP NULL\n");
        goto done;
    }
    if (-1 == usb_urb_transfer(udev, utp->endpt, utp->type, (char *)utp->buf, utp->buflen, 10))
        *reply = -1;
    else
        *reply = 0;
done:
    SK_SendMessage(msg->replyQid,(SKMessage) reply, SK_MESSAGE_NOBLOCK);
    return *reply;
}

static SKError
__usbHandleReapUTP(USB_hcd_msg_t *msg)
{
    return SK_ERROR_OK;
}

static SKError
__usbHandleCancelUTP(USB_hcd_msg_t *msg)
{
    return SK_ERROR_OK;
}
static SKError
__usbHandleWriteCtrlMsg(USB_hcd_msg_t *msg)
{
    int reply = SK_ERROR_OK;
    USB_emu_device_t *usb_dev;
    usb_dev_handle *udev;
    USB_hcdreq_ctrl_t *req;

    if ( NULL == msg ) {
        printf("req message is null\n");
        goto err;
    }
    if ( NULL == __devnodes[msg->devId].dev) {
        printf("dev is null\n");
        goto err;
    }
    usb_dev = __devnodes[msg->devId].dev;
    udev = usb_dev->handle;
    req = (USB_hcdreq_ctrl_t *)msg->req;
    if ( NULL == req ) goto err;
    reply = usb_control_msg(udev,
            req->endpt,
            req->bRequestType,
            ((req->bRequest << 8) + req->wIndex),
            (int )req->wValue,
            (char *)req->data,
            (int)req->wLength,
            1000);
    return SK_SendMessage(msg->replyQid, reply, SK_MESSAGE_NOBLOCK);
err:
    printf("hcd: handleWriteCtrlMsg: got invalid request\n");
    return SK_ERROR_INVALID;
}

static int
__usbHandleGetDevDescr(USB_hcd_msg_t *msg)
{
    USB_DevDescr_t *devDescr;
    struct usb_device *udev;
    USB_emu_device_t *usb_dev;
    int *reply = malloc(sizeof(int)); /* caller frees */
    *reply = -1;
    if ( NULL == msg || NULL == reply) {
        printf("Request message is null or malloc failed\n");
        goto done;
    }
    usb_dev = __devnodes[msg->devId].dev;
    if ( NULL == usb_dev ) {
        printf("dev is null\n");
        goto done;
    }
    devDescr = (USB_DevDescr_t *) msg->req;
    if ( NULL == devDescr) {
        printf("Got invalid buffer for device descriptor(NULL) \n");
        goto done;
    }
    udev = usb_dev->dev;
    devDescr->bLength = udev->descriptor.bLength;
    devDescr->bLength = udev->descriptor.bLength;
    devDescr->bDescriptorType = udev->descriptor.bDescriptorType;
    devDescr->bcdUSB = udev->descriptor.bcdUSB;
    devDescr->bDeviceClass = udev->descriptor.bDeviceClass;
    devDescr->bDeviceSubClass = udev->descriptor.bDeviceSubClass;
    devDescr->bDeviceProtocol = udev->descriptor.bDeviceProtocol;
    devDescr->bMaxPacketSize0 = udev->descriptor.bMaxPacketSize0;
    devDescr->idVendor = udev->descriptor.idVendor;
    devDescr->idProduct = udev->descriptor.idProduct;
    devDescr->bcdDevice = udev->descriptor.bcdDevice;
    devDescr->iManufacturer  = udev->descriptor.iManufacturer;
    devDescr->iProduct  = udev->descriptor.iProduct;
    devDescr->iSerialNumber = udev->descriptor.iSerialNumber;
    devDescr->bNumConfigurations = udev->descriptor.bNumConfigurations;
done:
    SK_SendMessage(msg->replyQid,(SKMessage) reply, SK_MESSAGE_NOBLOCK);
    return *reply;
}

static void
ep_copy(USB_EpDescr_t *dstn, struct usb_endpoint_descriptor *src)
{
  dstn->bLength = src->bLength;
  dstn->bDescriptorType = src->bDescriptorType;
  dstn->bEndpointAddress = src->bEndpointAddress;
  dstn->bmAttributes = src->bmAttributes;
  dstn->wMaxPacketSize = src->wMaxPacketSize;
  dstn->bInterval = src->bInterval;
}

static void
intf_copy(USB_IntfDescr_t *dstn, struct usb_interface_descriptor *src)
{
    u8 l;
    dstn->bLength = src->bLength;
    dstn->bDescriptorType = src->bDescriptorType;
    dstn->bInterfaceNumber  = src->bInterfaceNumber;
    dstn->bAlternateSetting  = src->bAlternateSetting;
    dstn->bNumEndpoints  = src->bNumEndpoints;
    dstn->bInterfaceClass  = src->bInterfaceClass;
    dstn->bInterfaceSubClass  = src->bInterfaceSubClass;
    dstn->bInterfaceProtocol  = src->bInterfaceProtocol;
    dstn->iInterface  = src->iInterface;
    for (l = 0; l < dstn->bNumEndpoints; ++l)
        ep_copy(&dstn->ep[l], &src->endpoint[l]);
}

static int
__usbHandleGetConfDescr(USB_hcd_msg_t *msg)
{
    USB_ConfDescr_t *confDescr;
    struct usb_device *udev;
    USB_emu_device_t *usb_dev;
    struct usb_config_descriptor c;
    u8 idx;
    int *reply = malloc(sizeof(int)); /* caller frees */
    *reply = -1;
    if ( NULL == msg || NULL == reply) {
        printf("Request message is null or malloc failed\n");
        goto done;
    }
    usb_dev = __devnodes[msg->devId].dev;
    if ( NULL == usb_dev ) {
        printf("dev is null\n");
        goto done;
    }
    udev = usb_dev->dev;
    confDescr = (USB_ConfDescr_t *) msg->req;
    if ( NULL == confDescr) {
        printf("Got invalid buffer for device descriptor(NULL) \n");
        goto done;
    }
    idx = confDescr->bConfigurationValue - 1; /* specified */
    if ( idx > udev->descriptor.bNumConfigurations ) {
      printf("Request for non-existent configuration # %d\n", idx);
      goto done;
    }
    {
         u8 k;
         c = udev->config[idx];
         confDescr->bLength = c.bLength;
         confDescr->bDescriptorType = c.bDescriptorType;
         confDescr->wTotalLength = c.wTotalLength;
         confDescr->bNumInterfaces = c.bNumInterfaces;
         confDescr->bConfigurationValue = c.bConfigurationValue;
         confDescr->iConfiguration = c.iConfiguration;
         confDescr->bmAttributes = c.bmAttributes;
         confDescr->MaxPower = c.MaxPower;
         confDescr->numAltSettings = c.interface->num_altsetting;
         for (k = 0; k < confDescr->numAltSettings; ++k ) {
             intf_copy(&confDescr->intf[k], &c.interface->altsetting[k]);
         }
     }

done:
    SK_SendMessage(msg->replyQid,(SKMessage) reply, SK_MESSAGE_NOBLOCK);
    return *reply;
}
/* Command handlers end */

static SKMessageQueueId
__usbInitHcd(SKMessage *inQ)
{
    SKMessageQueueId ret = SK_CreateMessageQueue(inQ,
            USB_HCD_INQ_MAX, USB_DEV_PIDMASK );
    if ( ret < 0 ) {
        SK_Perror("creating msg queue failed", ret);
    }
    return ret;
}

#if 0
void
dumpMsg(USB_hcd_msg_t *msg)
{
  printf("hcd msg: typ = %d \n", msg->typ - USB_SUBMIT_UTP);
  printf("hcd msg: devId = %d\n", msg->devId);
  printf("hcd msg: replyQid = %d\n", msg->replyQid);
}
#endif

void 
__usbHcdThr(u32 qid)
{
    USB_hcd_msg_t *msg;
    printf("Hcd starts running...\n");
    while(1) {
        SK_ReceiveMessage((SKMessageQueueId)qid, (SKMessage *) &msg, SK_MESSAGE_BLOCK);
        if ( NULL == msg) {
            DBG_PRINTF((dbg_fp,"hcd: Received null request\n"));
            continue;
        }
        /* dumpMsg(msg); */
        switch (msg->typ) {
            /* USB transfer packet requests */
            case USB_SUBMIT_UTP:
                __usbHandleSubmitUTP(msg);
                break;
            case USB_REAP_UTP:
                __usbHandleReapUTP(msg);
                break;
            case USB_CANCEL_UTP:
                __usbHandleCancelUTP(msg);
                break;
                /* USB control transfers */
            case USB_WRITE_CTRL_MSG:
                __usbHandleWriteCtrlMsg(msg);
                break;
            case USB_GET_DEV_DESCR:
                __usbHandleGetDevDescr(msg);
                break;
            case USB_GET_CONF_DESCR:
                __usbHandleGetConfDescr(msg);
                break;
            default:
                printf("ehci_hcd: got unknown message type = 0x%x\n", msg->typ); 
        }
    }
    SK_ThreadExit(0);
}

SKMessageQueueId
USB_CreateHcd(SKMessage *inQ)
{
    u32 *progStack, id;
    SKMessageQueueId ret = __usbInitHcd(inQ);
    progStack = (void *) malloc(16*1024);
    id = SK_CreateThread(__usbHcdThr, (void *) &ret, progStack, 16*1024, SK_GetThreadPriority(0) + 1);
    SK_StartThread(id);
    return ret;
}
