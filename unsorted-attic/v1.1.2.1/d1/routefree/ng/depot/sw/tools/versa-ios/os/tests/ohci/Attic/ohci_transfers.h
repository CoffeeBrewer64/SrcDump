a0 14
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
#ifndef __OHCI_TRANSFERS_H__
#define __OHCI_TRANSFERS_H__
IOSError ohci_CtrlMsg (struct ohci_hcd *hcd, u16 devnum, struct USB_CtrlReq *req, u8 ep, u8 addr);
#endif /* __OHCI_TRANSFERS_H__ */
