#ident "$Id: debug.h,v 1.6 2006/03/31 00:03:48 craig Exp $"
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

#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define DPRINT(str)                      printf(str)
#define DPRINT2(str, arg1)               printf(str, arg1)
#define DPRINT3(str, arg1, arg2)         printf(str, arg1, arg2)
#define DPRINT4(str, arg1, arg2, arg3)   printf(str, arg1, arg2, arg3)
#define DPRINT5(str, arg1, arg2, arg3, arg4) printf(str, arg1, arg2, arg3, arg4)
#else
#define DPRINT(str)
#define DPRINT2(str, arg1)
#define DPRINT3(str, arg1, arg2)
#define DPRINT4(str, arg1, arg2, arg3)
#define DPRINT5(str, arg1, arg2, arg3, arg4)
#endif // DEBUG

#if defined(ERR_DEBUG) || defined (DEBUG)
#define ERR_DPRINT(str)                      printf(str)
#define ERR_DPRINT2(str, arg1)               printf(str, arg1)
#define ERR_DPRINT3(str, arg1, arg2)         printf(str, arg1, arg2)
#define ERR_DPRINT4(str, arg1, arg2, arg3)   printf(str, arg1, arg2, arg3)
#define ERR_DPRINT5(str, arg1, arg2, arg3, arg4) printf(str, arg1, arg2, arg3, arg4)
#else
#define ERR_DPRINT(str)
#define ERR_DPRINT2(str, arg1)
#define ERR_DPRINT3(str, arg1, arg2)
#define ERR_DPRINT4(str, arg1, arg2, arg3)
#define ERR_DPRINT5(str, arg1, arg2, arg3, arg4)
#endif // ERR_DEBUG || DEBUG

#ifdef RVL
#include "stdint.h"
#endif

#include "md5.h"

void doSleep(const int numSecs);
void printMD5sum(const void* const ptr, const uint32_t numBytes);

#endif // DEBUG_H
