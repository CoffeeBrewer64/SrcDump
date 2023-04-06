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
#ifndef __SKUSB_H__
#define __SKUSB_H__
#include <skusbtypes.h>

/* Getting info */
int USB_GetDevDescr(SKCid fd, SKCid qid, USB_DevDescr_t *devDescr);
int USB_GetConfDescr(SKCid fd, SKCid qid, USB_ConfDescr_t *confDescr);
int USB_GetStr(SKCid fd, SKCid qid, u16 index, u16 langid, u32 buflen, char *buf);
int USB_GetAsciiStr(SKCid fd, SKCid qid, u16 index, u16 langid, u32 buflen, char *buf);
int USB_ReadBulkMsg(SKCid fd, SKCid qid, u32 ep, u32 buflen, char *buf);
int USB_WriteBulkMsg(SKCid fd, SKCid qid, u32 ep, u32 buflen, char  *buf);
int USB_ReadIntrMsg(SKCid fd, SKCid qid, u32 ep, u32 buflen, char *buf);
int USB_WriteIntrMsg(SKCid fd, SKCid qid, u32 ep, u32 buflen, char *buf);

#endif /* __SKUSB_H__ */
