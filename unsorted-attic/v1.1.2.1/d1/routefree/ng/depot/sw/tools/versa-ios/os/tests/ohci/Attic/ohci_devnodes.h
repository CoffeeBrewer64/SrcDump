a0 15
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
#ifndef __OHCI_DEVNODES_H__
#define __OHCI_DEVNODES_H__
u8 initOHCIDevNodes(void);
u16 initDevNode(u8 port, u8 hub, u8 spd);
#endif /* __OHCI_DEVNODES_H__ */
