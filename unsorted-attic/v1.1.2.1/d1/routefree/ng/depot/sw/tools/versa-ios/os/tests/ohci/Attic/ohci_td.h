a0 17
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
#ifndef __OHCI_TD_H__
#define __OHCI_TD_H__
#define OHCI_TD_MAX 32
void initTDPool(void);
s8 allocTD(void);
void freeTD(s8 tdnum);
#endif /* __OHCI_TD_H__ */
