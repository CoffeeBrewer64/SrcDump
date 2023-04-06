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

/*---------------------------------------------------------------------------*
 * 
 * Missed libc functions
 * 
 *---------------------------------------------------------------------------*/

#ifndef __IOP_LIBC_H__
#define __IOP_LIBC_H__

#include <iostypes.h>

u32 atoi(const char *s);
u32 strlen(const char *s);
int isdigit(int c);
int isxdigit(int c);
int islower(int c);
int isalnum(int c);
int strnicmp(const char *s1, const char *s2, int len);

#endif // __IOP_LIBC_H__
