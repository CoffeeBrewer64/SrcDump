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
#include <ioserrno.h>
#include <iosusbtypes.h>
#include <iosusb.h>
#include <emu_iosusb.h>
#include <ioslibc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGQ_SIZE 4
#define PID_MASK 0xFFFFFFFF
IOSMessage msgQ[MSGQ_SIZE];

static int
__USB_GetStr(IOSCid fd, IOSCid qid, u16 index, u16 langid, u32 buflen, char *buf)
{
    IOSError err = IOS_ERROR_OK;
    int reply = -1;
    USB_HcdMsg_t msg;
    USB_HcdReqCtrl_t *req = NULL;
    if ( -1 == fd || -1 == qid )
        goto done;
    req = malloc(sizeof(USB_HcdReqCtrl_t));
    if ( NULL == req)
        goto done;
    req->bRequestType = USB_STD_REQ_GET_DESCRIPTOR;
    req->bRequest = USB_STD_DT_STRING;
    req->wValue = USB_STD_LANG_EN_US;
    req->wIndex = index ;
    req->wLength = buflen;
    req->endpt = USB_ENDPT_IN_FLAG;
    req->data = (u32) buf;
    
    msg.typ = USB_WRITE_CTRL_MSG;
    msg.devId = fd;
    msg.req = req;
    msg.replyQid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
    
    err = IOS_SendMessage(qid, (IOSMessage)&msg, IOS_MESSAGE_BLOCK);
    if ( IOS_ERROR_OK != err) {
        IOS_Perror("USB_GetStr: IOS_SendMessage failed:", err);
        goto done;
    }
    err = IOS_ReceiveMessage(msg.replyQid, &reply, IOS_MESSAGE_BLOCK);
    if ( IOS_ERROR_OK != err ) {
        IOS_Perror("usb_cdrvr: IOS_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    if ( reply < 0  ) {
        IOS_Perror("usb_cdrvr: request to ehci driver failed:", err);
        reply = -1;
        goto done;
    }
    
done:
    if ( NULL != req) free(req);
    if ( msg.replyQid >= 0) 
        IOS_DestroyMessageQueue(msg.replyQid);
    return reply;
}

IOSError
IUSB_GetStr(IOSCid fd, IOSCid qid, u16 index, u16 langid, u32 buflen, char *buf)
{
  return __USB_GetStr(fd, qid, index, langid, buflen, buf);
}

static int
__USB_Unicode2Ascii(char *tbuf, int buflen)
{
    char *buf;
    buf = malloc(buflen*sizeof(char));
    int di, si;
    if (tbuf[1] != USB_STD_DT_STRING )
        return -1;
    for (di = 0, si = 2; si < tbuf[0]; si += 2) {
        if (di >= (buflen - 1))
            break;
        if (tbuf[si + 1])   /* high byte */
            buf[di++] = '?';
        else
            buf[di++] = tbuf[si];
    }
    buf[di] = 0;
    memcpy(tbuf, buf, di + 1);
    return 0;
}

IOSError
IUSB_GetAsciiStr(IOSCid fd, IOSCid qid, u16 index, u16 langid, u32 buflen, char *buf)
{
  int ret =  __USB_GetStr(fd, qid, index, langid, buflen, buf);
  if ( ret < 0 ) 
      return ret;
  return __USB_Unicode2Ascii(buf, buflen);
}

#define DIR_READ 0
#define DIR_WRITE 1
static int
__USB_ReadOrWrite_Msgs(IOSCid fd, IOSCid qid, u32 ep, u32 buflen, char *buf, int rw, int type)
{
    IOSError err = IOS_ERROR_OK;
//    int reply = -1;
    int *preply = NULL;
    USB_HcdMsg_t msg;
    USB_TransPkt_t *utp = NULL;
    if ( -1 == fd || -1 == qid )
        goto done;
    utp = malloc(sizeof(USB_TransPkt_t));
    if ( NULL == utp ) {
        printf("Failed to allocate UTP\n");
        goto done;
    }
    utp->type = type;
    utp->endpt = ep;
    if ( DIR_READ == rw)
        utp->endpt |= USB_ENDPT_IN_FLAG;
    utp->buf = (u32) buf;
    utp->buflen = buflen;
    utp->flags = 0;
    utp->datalen = 0;
    utp->status = 0;
    msg.typ = USB_SUBMIT_UTP;
    msg.devId = fd;
    msg.req = utp;
    msg.replyQid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
    if (msg.replyQid == IOS_ERROR_MAX) {
        IOS_Perror("USB_ReadOrWrite: Creation of message queue failed\n", msg.replyQid);
        goto done;
    }
    err = IOS_SendMessage(qid, (IOSMessage)&msg, IOS_MESSAGE_BLOCK);
    if ( IOS_ERROR_OK != err) {
        IOS_Perror("USB_ReadOrWrite: IOS_SendMessage failed", err);
        goto done;
    }
    err = IOS_ReceiveMessage(msg.replyQid, (IOSMessage *) &preply, IOS_MESSAGE_BLOCK);
    if ( IOS_ERROR_OK != err ) {
        IOS_Perror("USB_ReadOrWrite: IOS_ReceiveMessage failed:", err);
        goto done;
    }
done:
    if ( NULL != utp ) free(utp);
    if ( msg.replyQid >= 0) 
        IOS_DestroyMessageQueue(msg.replyQid);
    return *preply;
}

IOSError
IUSB_ReadBulkMsg(IOSCid fd, IOSCid qid, u32 ep, u32 buflen, char *buf)
{
    return __USB_ReadOrWrite_Msgs(fd, qid, ep, buflen, buf, DIR_READ, USB_EMU_URB_BULK);
}

IOSError
IUSB_WriteBulkMsg(IOSCid fd, IOSCid qid, u32 ep, u32 buflen, char  *buf)
{
    return __USB_ReadOrWrite_Msgs(fd, qid, ep, buflen, buf, DIR_WRITE, USB_EMU_URB_BULK);
}

IOSError
IUSB_ReadIntrMsg(IOSCid fd, IOSCid qid, u32 ep, u32 buflen, char *buf)
{
    return __USB_ReadOrWrite_Msgs(fd, qid, ep, buflen, buf, DIR_READ, USB_EMU_URB_INTERRUPT);
}

IOSError
IUSB_WriteIntrMsg(IOSCid fd, IOSCid qid, u32 ep, u32 buflen, char *buf)
{
    return __USB_ReadOrWrite_Msgs(fd, qid, ep, buflen, buf, DIR_WRITE, USB_EMU_URB_INTERRUPT);
}

IOSError
IUSB_GetDevDescr(IOSCid fd, IOSCid qid, USB_DevDescr_t *devDescr)
{
    IOSError err = IOS_ERROR_OK;
    int reply = -1;
    USB_HcdMsg_t msg;
    if ( -1 == fd || -1 == qid || NULL == devDescr )
        goto done;
    msg.typ = USB_GET_DEV_DESCR;
    msg.devId = fd;
    msg.req = devDescr;
    msg.replyQid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );

    err = IOS_SendMessage(qid, (IOSMessage)&msg, IOS_MESSAGE_BLOCK);
    if ( IOS_ERROR_OK != err) {
        IOS_Perror("USB_GetDevDescr: IOS_SendMessage failed:", err);
        goto done;
    }
    err = IOS_ReceiveMessage(msg.replyQid, &reply, IOS_MESSAGE_BLOCK);
    if ( IOS_ERROR_OK != err ) {
        IOS_Perror("USB_GetDevDescr: IOS_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    if ( reply < 0  ) {
        IOS_Perror("USB_GetDevDescr:IOS_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    
done:
    if ( msg.replyQid >= 0) 
        IOS_DestroyMessageQueue(msg.replyQid);
    return reply;
}

IOSError
IUSB_GetConfDescr(IOSCid fd, IOSCid qid, USB_ConfDescr_t *confDescr)
{
    IOSError err = IOS_ERROR_OK;
    int reply = -1;
    USB_HcdMsg_t msg;
    if ( -1 == fd || -1 == qid || NULL == confDescr )
        goto done;
    msg.typ = USB_GET_CONF_DESCR;
    msg.devId = fd;
    msg.req = confDescr;
    msg.replyQid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
    err = IOS_SendMessage(qid, (IOSMessage)&msg, IOS_MESSAGE_BLOCK);
    if ( IOS_ERROR_OK != err) {
        IOS_Perror("USB_GetDevDescr: IOS_SendMessage failed:", err);
        goto done;
    }
    err = IOS_ReceiveMessage(msg.replyQid, &reply, IOS_MESSAGE_BLOCK);
    if ( IOS_ERROR_OK != err ) {
        IOS_Perror("USB_GetDevDescr: IOS_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    if ( reply < 0  ) {
        IOS_Perror("USB_GetDevDescr:IOS_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    
done:
    if ( msg.replyQid >= 0) 
        IOS_DestroyMessageQueue(msg.replyQid);
    return reply;
}

IOSError 
IUSB_ResetDevice(IOSCid fd, IOSCid qid)
{
    IOSError err = IOS_ERROR_OK;
    int reply = -1;
    USB_HcdMsg_t msg;
    if ( -1 == fd || -1 == qid) {
       err = IOS_ERROR_INVALID;
        goto done;
    }
    msg.typ = USB_RESET_DEV;
    msg.devId = fd;
    msg.req = 0;
    msg.replyQid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );

    err = IOS_SendMessage(qid, (IOSMessage)&msg, IOS_MESSAGE_BLOCK);
    if ( IOS_ERROR_OK != err) {
        IOS_Perror("IUSB_ResetDevice: IOS_SendMessage failed:", err);
        goto done;
    }
    err = IOS_ReceiveMessage(msg.replyQid, &reply, IOS_MESSAGE_BLOCK);
    if ( IOS_ERROR_OK != err ) {
        IOS_Perror("IUSB_ResetDevice: IOS_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    if ( reply < 0  ) {
        IOS_Perror("USB_ResetDevice:IOS_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    
done:
    if ( msg.replyQid >= 0) 
        IOS_DestroyMessageQueue(msg.replyQid);
    return reply;
}

IOSError 
IUSB_ResetEndpoint(IOSCid fd, IOSCid qid, unsigned int ep )
{
    IOSError err = IOS_ERROR_OK;
    int reply = -1;
    USB_HcdMsg_t msg;
    if ( -1 == fd || -1 == qid) {
       err = IOS_ERROR_INVALID;
        goto done;
    }
    msg.typ = USB_RESET_DEV;
    msg.devId = fd;
    msg.req = &ep;
    printf("Resetting endpoint: %d\n", ep);
    msg.replyQid = IOS_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );

    err = IOS_SendMessage(qid, (IOSMessage)&msg, IOS_MESSAGE_BLOCK);
    if ( IOS_ERROR_OK != err) {
        IOS_Perror("IUSB_ResetDevice: IOS_SendMessage failed:", err);
        goto done;
    }
    err = IOS_ReceiveMessage(msg.replyQid, &reply, IOS_MESSAGE_BLOCK);
    if ( IOS_ERROR_OK != err ) {
        IOS_Perror("IUSB_ResetDevice: IOS_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    if ( reply < 0  ) {
        IOS_Perror("USB_ResetDevice:IOS_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    
done:
    if ( msg.replyQid >= 0) 
        IOS_DestroyMessageQueue(msg.replyQid);
    return reply;
}
