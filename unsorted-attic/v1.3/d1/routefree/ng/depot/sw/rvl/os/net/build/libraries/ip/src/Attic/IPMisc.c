/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPMisc.c

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPMisc.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    6     3/02/06 15:02 Shiki
    Fixed IPRandTime().

    5     3/02/06 9:47 Shiki
    Modified IPRandTime().

    4     1/18/06 16:00 Shiki
    Added strnlen().

    3     04/12/20 9:25 Ueno_kyu
    Enclosed functions declared in ctype.h in parentheses for SN.

    2     04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    4     04/10/18 11:41 Ueno_kyu
    Replaced LLu as LL.

    3     6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    1     11/17/03 13:22 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifdef IOP_OS
#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#else
#include <ctype.h>
#include <string.h>
#endif // IOP_OS

#include <dolphin/os.h>
#include <dolphin/ip.h>
#include "IPPrivate.h"

#define A 0x0005deece66dLL
#define C 0xbu
#define M (1LL << 48u)

u64 IPRand48(IPInterface* interface)
{
    interface->seed = (A * interface->seed + C) % M;
    return interface->seed;
}

OSTime IPRandTime(IPInterface* interface, OSTime min, OSTime max)
{
    OSTime d;

    if (min == max)
    {
        return min;
    }

    if (max < min)
    {
        d = max;
        max = min;
        min = d;
    }

#ifdef IOP_OS
    d = (((OSTime) OSGetTick() << 24) + (OSTime) IPRand48(interface)) % (max - min);
#else
    d = (((OSTime) OSGetTick() << 48) + (OSTime) IPRand48(interface)) % (max - min);
#endif // IOP_OS
    
    if (d < 0)
    {
        d = -d;
    }
    return min + d;
}

#ifndef IOP_OS

#ifndef WIN32

size_t strnlen(const char *s, const size_t n);
int stricmp(const char *s1, const char *s2);
int strnicmp(const char *s1, const char *s2, size_t n);

__declspec(weak) size_t strnlen(const char *s, const size_t n)
{
    int i;
    const char* t;

    for (i = 0, t = s; i < n && *t != '\0'; ++i, ++t)
    {

    }
    return (size_t) (t - s);
}

__declspec(weak) int stricmp(const char *s1, const char *s2)
{
    char c1;
    char c2;

    for (;;)
    {
        c1 = (char) (tolower)(*s1++);
        c2 = (char) (tolower)(*s2++);
        if (c1 < c2)
        {
            return -1;
        }
        if (c1 > c2)
        {
            return 1;
        }
        if (c1 == '\0')
        {
            return 0;
        }
    }
    return 0;
}

__declspec(weak) int strnicmp(const char *s1, const char *s2, size_t n)
{
    int i;
    char c1;
    char c2;

    for (i = 0; i < n; ++i)
    {
        c1 = (char) (tolower)(*s1++);
        c2 = (char) (tolower)(*s2++);
        if (c1 < c2)
        {
            return -1;
        }
        if (c1 > c2)
        {
            return 1;
        }
        if (c1 == '\0')
        {
            return 0;
        }
    }
    return 0;
}

#endif  // WIN32

#endif // IOP_OS
