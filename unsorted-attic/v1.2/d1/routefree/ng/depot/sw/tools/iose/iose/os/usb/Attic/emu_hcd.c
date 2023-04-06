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
#include <iostypes.h>
#include <iosusbtypes.h>
#include <iosusb.h>
#include <arm.h>
#include <ioslibc.h>
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
#include <iosusb.h>
#include <usb.h>

extern IOSDevice_t  __devnodes[];
extern int __devroot;


/* Command handlers begin */
static IOSError
__usbHandleSubmitUTP(USB_HcdMsg_t *msg)
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
    IOS_SendMessage(msg->replyQid,(IOSMessage) reply, IOS_MESSAGE_NOBLOCK);
    return *reply;
}

static IOSError
__usbHandleReapUTP(USB_HcdMsg_t *msg)
{
    return IOS_ERROR_OK;
}

static IOSError
__usbHandleCancelUTP(USB_HcdMsg_t *msg)
{
    return IOS_ERROR_OK;
}
static IOSError
__usbHandleWriteCtrlMsg(USB_HcdMsg_t *msg)
{
    int reply = IOS_ERROR_OK;
    USB_emu_device_t *usb_dev;
    usb_dev_handle *udev;
    USB_HcdReqCtrl_t *req;

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
    req = (USB_HcdReqCtrl_t *)msg->req;
    if ( NULL == req ) goto err;
    reply = usb_control_msg(udev,
            req->endpt,
            req->bRequestType,
            ((req->bRequest << 8) + req->wIndex),
            (int )req->wValue,
            (char *)req->data,
            (int)req->wLength,
            1000);
    return IOS_SendMessage(msg->replyQid, reply, IOS_MESSAGE_NOBLOCK);
err:
    printf("hcd: handleWriteCtrlMsg: got invalid request\n");
    return IOS_ERROR_INVALID;
}

static int
__usbHandleGetDevDescr(USB_HcdMsg_t *msg)
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
    IOS_SendMessage(msg->replyQid,(IOSMessage) reply, IOS_MESSAGE_NOBLOCK);
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
__usbHandleGetConfDescr(USB_HcdMsg_t *msg)
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
    IOS_SendMessage(msg->replyQid,(IOSMessage) reply, IOS_MESSAGE_NOBLOCK);
    return *reply;
}

static IOSError
__usbHandleResetDevOrEp(USB_HcdMsg_t *msg, int type)
{
    USB_emu_device_t *usb_dev;
    unsigned int *epp = NULL;
    IOSError ret = IOS_ERROR_OK;
    if ( NULL == msg
        || ( type == 1 && (NULL == (epp = (unsigned int *) msg->req)))) {
        printf("Request message or parameter is null\n");
        ret = IOS_ERROR_USB_ERR;
        goto done;
    }
    if ( NULL ==  (usb_dev = __devnodes[msg->devId].dev) ) {
        ret = IOS_ERROR_USB_ERR;
        goto done;
    }
    if ( (0 == type && usb_reset(usb_dev->handle) < 0 )
        ||(1 == type && usb_resetep(usb_dev->handle, *epp) < 0) ) {
      ret = IOS_ERROR_USB_ERR;
      goto done;
    }
done:
    return ret;
}

static IOSError
__usbHandleSetConf(USB_HcdMsg_t *msg)
{
    USB_emu_device_t *usb_dev;
    int *confp = NULL;
    IOSError ret = IOS_ERROR_OK;
    if ( NULL == msg || (NULL == (confp = (int *)msg->req))) {
        printf("Request message or request parameter is null\n");
        ret = IOS_ERROR_USB_ERR;
        goto done;
    }
    if ( NULL ==  (usb_dev = __devnodes[msg->devId].dev) ) {
        ret = IOS_ERROR_USB_ERR;
        goto done;
    }
    if ( usb_set_configuration(usb_dev->handle, *confp ) < 0 ) {
      ret = IOS_ERROR_USB_ERR;
      goto done;
    }
done:
    return ret;
}

/* Command handlers end */
static IOSMessageQueueId
__usbInitHcd(IOSMessage *inQ)
{
  IOSMessageQueueId ret = IOS_CreateMessageQueue(inQ,
            USB_HCD_INQ_MAX, USB_DEV_PIDMASK );
    if ( ret < 0 ) {
        IOS_Perror("creating msg queue failed", ret);
    }
    return ret;
}

void 
__usbHcdThr(u32 qid)
{
    USB_HcdMsg_t *msg;
    while(1) {
        IOS_ReceiveMessage((IOSMessageQueueId)qid, (IOSMessage *) &msg, IOS_MESSAGE_BLOCK);
        if ( NULL == msg) {
            DBG_PRINTF((dbg_fp,"hcd: Received null request\n"));
            continue;
        }
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
            case USB_WRITE_CTRL_MSG:
                __usbHandleWriteCtrlMsg(msg);
                break;
            case USB_GET_DEV_DESCR:
                __usbHandleGetDevDescr(msg);
                break;
            case USB_GET_CONF_DESCR:
                __usbHandleGetConfDescr(msg);
                break;
            case USB_RESET_DEV:
                    __usbHandleResetDevOrEp(msg, 0);
                    break;
                case USB_RESET_EP:
                    __usbHandleResetDevOrEp(msg, 1);
                break;
            case USB_SET_CONF:
                __usbHandleSetConf(msg);
                break;
            default:
                printf("hcd: got unknown message type = 0x%x\n", msg->typ); 
        }
    }
    IOS_ThreadExit(0);
}

IOSMessageQueueId
USB_CreateHcd(IOSMessage *inQ)
{
    u32 *progStack, id;
    IOSMessageQueueId ret = __usbInitHcd(inQ);
    progStack = (void *) malloc(16*1024);
    id = IOS_CreateThread(__usbHcdThr, (void *) &ret, progStack, 16*1024, IOS_GetThreadPriority(0) + 1);
    IOS_StartThread(id);
    return ret;
}
