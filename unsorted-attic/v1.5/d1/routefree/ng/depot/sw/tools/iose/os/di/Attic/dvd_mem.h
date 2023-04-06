#ident "$Id: dvd_mem.h,v 1.4 2006/03/29 18:57:49 craig Exp $"

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

#ifndef DVD_MEM_H
#define DVD_MEM_H

void    initDvdMemAlloc(void);
void    *dvdMemAlloc(uint32_t size);
void    dvdMemFree(void *ptrToFree);
bool    dvdMemAllocAlign32(const uint32_t size,
                           void **ptrToMem,
                           void** ptrToFree);

#endif
