a0 24
#ident "$Id: debug.h,v 1.5 2008/01/23 20:59:05 cnguyen Exp $"
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

#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef DEBUG
#define DPRINT(f, args...) printf("(%s) "f, __func__, ## args)
#else
#define DPRINT(f, args...)
#endif // DEBUG

extern void wfsLog(u8 *msg);

#endif // __DEBUG_H
