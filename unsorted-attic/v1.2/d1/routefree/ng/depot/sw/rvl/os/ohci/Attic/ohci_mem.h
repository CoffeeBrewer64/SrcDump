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
#ifndef __OHCI_MEM_H__
#define __OHCI_MEM_H__
extern IOSHeapId __ohcdHeapId;

struct ohci_td *allocTD(void);
IOSError freeTD(struct ohci_td *td);

struct ohci_ed *allocED(void);
IOSError freeED(struct ohci_ed *ed);

IOSError initOHCDMem(void);

#endif /* __OHCI_MEM_H__ */
