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
#ifndef __IOS_USB_H__
#define __IOS_USB_H__
IOSError IUSB_GetAsciiStr(IOSFd fd, u8 ep, u16 index, u16 langId,
        char *buf, u16 buflen);
IOSError IUSB_GetDevDescr(IOSFd fd, struct USB_DevDescr *d);
IOSError IUSB_ReadCtrlMsg(IOSFd fd, u8 reqType, u8 request, u16 value,
             u16 index, u16 length, char *data);
IOSError IUSB_WriteCtrlMsg(IOSFd fd, u8 reqType, u8 request, u16 value,
             u16 index, u16 length, char *data);
IOSError IUSB_ReadIntrMsg(IOSFd fd, u32 ep, u32 buflen, char *buf);
IOSError IUSB_WriteIntrMsg(IOSFd fd, u32 ep, u32 buflen, char *buf);
IOSError IUSB_ReadBlkMsg(IOSFd fd, u32 ep, u32 buflen, char *buf);
IOSError IUSB_WriteBlkMsg(IOSFd fd, u32 ep, u32 buflen, char *buf);
#endif /* __IOS_USB_H__ */
