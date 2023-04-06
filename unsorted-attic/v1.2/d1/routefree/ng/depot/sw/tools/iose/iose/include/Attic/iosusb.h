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
#ifndef __IOSUSB_H__
#define __IOSUSB_H__
#include <iosusbtypes.h>

IOSError  IUSB_RegisterResourceManager(IOSCid fd);
IOSError  IUSB_UnregisterResourceManager(IOSCid fd);
IOSError  IUSB_FindDevice(u16 vendorId, u16 productId,
                            char *buf, int bufsize);
IOSError IUSB_FindDeviceIds(u16 vendorId, u16 productId, IOSCid *qid, IOSCid *fd);
IOSError IUSB_ResetDevice(IOSCid fd, IOSCid qid); 
IOSError IUSB_ResetEndpoint(IOSCid fd, IOSCid qid, unsigned int ep); 
IOSError IUSB_GetDevDescr(IOSCid fd, IOSCid qid, USB_DevDescr_t *devDescr);
IOSError IUSB_GetConfDescr(IOSCid fd, IOSCid qid, USB_ConfDescr_t *confDescr);

IOSError IUSB_GetStr(IOSCid fd, IOSCid qid, u16 index, u16 langid, u32 buflen, char *buf);
IOSError IUSB_GetAsciiStr(IOSCid fd, IOSCid qid, u16 index, u16 langid, u32 buflen, char *buf);
IOSError IUSB_ReadBulkMsg(IOSCid fd, IOSCid qid, u32 ep, u32 buflen, char *buf);
IOSError IUSB_WriteBulkMsg(IOSCid fd, IOSCid qid, u32 ep, u32 buflen, char  *buf);
IOSError IUSB_ReadIntrMsg(IOSCid fd, IOSCid qid, u32 ep, u32 buflen, char *buf);
IOSError IUSB_WriteIntrMsg(IOSCid fd, IOSCid qid, u32 ep, u32 buflen, char *buf);

#endif /* __IOSUSB_H__ */
