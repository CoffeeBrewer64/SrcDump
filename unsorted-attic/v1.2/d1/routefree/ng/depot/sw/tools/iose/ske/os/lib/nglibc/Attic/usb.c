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

#include <ng.h>
#include <sktypes.h>
#include <sk.h>
#include <skerrno.h>
#include <skusbtypes.h>
#include <skusb.h>
#include <emu_skusb.h>
#include <nglibc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGQ_SIZE 4
#define PID_MASK 0xFFFFFFFF
SKMessage msgQ[MSGQ_SIZE];

int
__USB_GetStr(SKCid fd, SKCid qid, u16 index, u16 langid, u32 buflen, char *buf)
{
    SKError err = SK_ERROR_OK;
    int reply = -1;
    USB_hcd_msg_t msg;
    USB_hcdreq_ctrl_t *req = NULL;
    if ( -1 == fd || -1 == qid )
        goto done;
    req = malloc(sizeof(USB_hcdreq_ctrl_t));
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
    msg.replyQid = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
    
    err = SK_SendMessage(qid, (SKMessage)&msg, SK_MESSAGE_BLOCK);
    if ( SK_ERROR_OK != err) {
        SK_Perror("USB_GetStr: SK_SendMessage failed:", err);
        goto done;
    }
    err = SK_ReceiveMessage(msg.replyQid, &reply, SK_MESSAGE_BLOCK);
    if ( SK_ERROR_OK != err ) {
        SK_Perror("usb_cdrvr: SK_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    if ( reply < 0  ) {
        SK_Perror("usb_cdrvr: request to ehci driver failed:", err);
        reply = -1;
        goto done;
    }
    
done:
    if ( NULL != req) free(req);
    if ( msg.replyQid >= 0) 
        SK_DestroyMessageQueue(msg.replyQid);
    return reply;
}

int
USB_GetStr(SKCid fd, SKCid qid, u16 index, u16 langid, u32 buflen, char *buf)
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

int
USB_GetAsciiStr(SKCid fd, SKCid qid, u16 index, u16 langid, u32 buflen, char *buf)
{
  int ret =  __USB_GetStr(fd, qid, index, langid, buflen, buf);
  if ( ret < 0 ) 
      return ret;
  return __USB_Unicode2Ascii(buf, buflen);
}

#define DIR_READ 0
#define DIR_WRITE 1
static int
__USB_ReadOrWrite_Msgs(SKCid fd, SKCid qid, u32 ep, u32 buflen, char *buf, int rw, int type)
{
    SKError err = SK_ERROR_OK;
//    int reply = -1;
    int *preply = NULL;
    USB_hcd_msg_t msg;
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
    msg.replyQid = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
    if (msg.replyQid == SK_ERROR_MAX) {
        SK_Perror("USB_ReadOrWrite: Creation of message queue failed\n", msg.replyQid);
        goto done;
    }
    err = SK_SendMessage(qid, (SKMessage)&msg, SK_MESSAGE_BLOCK);
    if ( SK_ERROR_OK != err) {
        SK_Perror("USB_ReadOrWrite: SK_SendMessage failed", err);
        goto done;
    }
    err = SK_ReceiveMessage(msg.replyQid, (SKMessage *) &preply, SK_MESSAGE_BLOCK);
    if ( SK_ERROR_OK != err ) {
        SK_Perror("USB_ReadOrWrite: SK_ReceiveMessage failed:", err);
        goto done;
    }
done:
    if ( NULL != utp ) free(utp);
    if ( msg.replyQid >= 0) 
        SK_DestroyMessageQueue(msg.replyQid);
    return *preply;
}

int
USB_ReadBulkMsg(SKCid fd, SKCid qid, u32 ep, u32 buflen, char *buf)
{
    return __USB_ReadOrWrite_Msgs(fd, qid, ep, buflen, buf, DIR_READ, USB_EMU_URB_BULK);
}

int
USB_WriteBulkMsg(SKCid fd, SKCid qid, u32 ep, u32 buflen, char  *buf)
{
    return __USB_ReadOrWrite_Msgs(fd, qid, ep, buflen, buf, DIR_WRITE, USB_EMU_URB_BULK);
}

int
USB_ReadIntrMsg(SKCid fd, SKCid qid, u32 ep, u32 buflen, char *buf)
{
    return __USB_ReadOrWrite_Msgs(fd, qid, ep, buflen, buf, DIR_READ, USB_EMU_URB_INTERRUPT);
}

int
USB_WriteIntrMsg(SKCid fd, SKCid qid, u32 ep, u32 buflen, char *buf)
{
    return __USB_ReadOrWrite_Msgs(fd, qid, ep, buflen, buf, DIR_WRITE, USB_EMU_URB_INTERRUPT);
}

int
USB_GetDevDescr(SKCid fd, SKCid qid, USB_DevDescr_t *devDescr)
{
    SKError err = SK_ERROR_OK;
    int reply = -1;
    USB_hcd_msg_t msg;
    if ( -1 == fd || -1 == qid || NULL == devDescr )
        goto done;
    msg.typ = USB_GET_DEV_DESCR;
    msg.devId = fd;
    msg.req = devDescr;
    msg.replyQid = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );

    err = SK_SendMessage(qid, (SKMessage)&msg, SK_MESSAGE_BLOCK);
    if ( SK_ERROR_OK != err) {
        SK_Perror("USB_GetDevDescr: SK_SendMessage failed:", err);
        goto done;
    }
    err = SK_ReceiveMessage(msg.replyQid, &reply, SK_MESSAGE_BLOCK);
    if ( SK_ERROR_OK != err ) {
        SK_Perror("USB_GetDevDescr: SK_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    if ( reply < 0  ) {
        SK_Perror("USB_GetDevDescr:SK_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    
done:
    if ( msg.replyQid >= 0) 
        SK_DestroyMessageQueue(msg.replyQid);
    return reply;
}

int
USB_GetConfDescr(SKCid fd, SKCid qid, USB_ConfDescr_t *confDescr)
{
    SKError err = SK_ERROR_OK;
    int reply = -1;
    USB_hcd_msg_t msg;
    if ( -1 == fd || -1 == qid || NULL == confDescr )
        goto done;
    msg.typ = USB_GET_CONF_DESCR;
    msg.devId = fd;
    msg.req = confDescr;
    msg.replyQid = SK_CreateMessageQueue(msgQ, MSGQ_SIZE, PID_MASK );
    err = SK_SendMessage(qid, (SKMessage)&msg, SK_MESSAGE_BLOCK);
    if ( SK_ERROR_OK != err) {
        SK_Perror("USB_GetDevDescr: SK_SendMessage failed:", err);
        goto done;
    }
    err = SK_ReceiveMessage(msg.replyQid, &reply, SK_MESSAGE_BLOCK);
    if ( SK_ERROR_OK != err ) {
        SK_Perror("USB_GetDevDescr: SK_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    if ( reply < 0  ) {
        SK_Perror("USB_GetDevDescr:SK_ReceiveMessage failed:", err);
        reply = -1;
        goto done;
    }
    
done:
    if ( msg.replyQid >= 0) 
        SK_DestroyMessageQueue(msg.replyQid);
    return reply;
}
