/*---------------------------------------------------------------------------*
  Project:  Dolphin IP API -- UUIDs and GUIDs
  File:     IPUuid.c

  Copyright 2003 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  software derived from Network Working Group INTERNET-DRAFT
  <draft-leach-uuids-guids-01.txt>.

  $Log: IPUuid.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    5     04/12/20 9:25 Ueno_kyu
    Enclosed functions declared in ctype.h in parentheses for SN.
    
    4     8/25/03 9:20 Shiki
    Revised for WIN32.
    
    3     5/13/03 10:47 Shiki
    Fixed for CW 2.5.

    2     4/18/03 22:02 Shiki
    Added utility functions.

    1     4/03/03 18:20 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*
** Copyright (c) 1990- 1993, 1996 Open Software Foundation, Inc.
** Copyright (c) 1989 by Hewlett-Packard Company, Palo Alto, Ca. &
** Digital Equipment Corporation, Maynard, Mass.
** Copyright (c) 1998 Microsoft.
** To anyone who acknowledges that this file is provided "AS IS"
** without any express or implied warranty: permission to use, copy,
** modify, and distribute this file for any purpose is hereby
** granted without fee, provided that the above copyright notices and
** this notice appears in all source code copies, and that none of
** the names of Open Software Foundation, Inc., Hewlett-Packard
** Company, or Digital Equipment Corporation be used in advertising
** or publicity pertaining to distribution of the software without
** specific, written prior permission.  Neither Open Software
** Foundation, Inc., Hewlett-Packard Company, Microsoft, nor Digital Equipment
** Corporation makes any representations about the suitability of
** this software for any purpose.
*/

#ifdef IOP_OS
#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <stddef.h>
#else
#include <ctype.h>
#include <stdio.h>
#endif // IOP_OS

#include <dolphin/md5.h>
#include <dolphin/os.h>
#include <dolphin/ip.h>
#include <dolphin/ip/IPUuid.h>
#include <private/OSRtc.h>

// 10ns ticks since 10/15/1582 00:00:00 to 1/1/2000
//  10/15/1582 17 + 30 + 31
//  1/1/1600   25
//  1/1/1700   25 - 1(1700)
//  1/1/1800   25 - 1(1800)
//  1/1/1900   25 - 1(1900)
//  1/1/2000
#define BIAS    (((s64) (400 * 365 + 17 + 30 + 31 + 25 + 3 * 24)) * 86400 * 10000000)

// 60 bit 100ns ticks since 15 October 1582
#define OSTicksToTimestamp(ticks)   ((((ticks) * 80) / (OS_TIMER_CLOCK / 125000)) + BIAS)
#define OSTimestampToTicks(ts)      ((((ts) - BIAS) * (OS_TIMER_CLOCK / 125000)) / 80)

static u32 GetCounterBias(void)
{
    OSSram* sram;
    u32     counterBias;

    sram = __OSLockSram();
    counterBias = sram->counterBias;
    __OSUnlockSram(FALSE);
    return counterBias;
}

void IPPrintUuid(const IPUuid* u)
{
    int i;

    OSReport("%8.8x-%4.4x-%4.4x-%2.2x%2.2x-",
             u->timeLow,
             u->timeMid,
             u->timeHiAndVersion,
             u->clockSeqHiAndReserved,
             u->clockSeqLow);
    for (i = 0; i < 6; i++)
    {
        OSReport("%2.2x", u->node[i]);
    }
    OSReport("\n");
}

const char* IPGetUuidString(const IPUuid* u, char* str)
{
#ifndef IOP_OS // MX TODO
    int i;
    char* ptr = str;

    ptr += sprintf(ptr, "%8.8x-%4.4x-%4.4x-%2.2x%2.2x-",
                   u->timeLow,
                   u->timeMid,
                   u->timeHiAndVersion,
                   u->clockSeqHiAndReserved,
                   u->clockSeqLow);
    for (i = 0; i < 6; i++)
    {
        ptr += sprintf(ptr, "%2.2x", u->node[i]);
    }
    ASSERT(ptr - str == IP_UUID_STR_LEN - 1);
    return str;
#endif // IOP_OS
    return NULL;
}

int IPScanUuid(const char* str, IPUuid* u)
{
    int x;
    int b;
    u8* p = (u8*) u;
    int i;
    int j;

    // 0         1         2         3
    // 012345678901234567890123456789012345
    // 83ba18aa-3e2e-425f-b6ee-0a2e46ea1d9a
    for (i = 0, j = 0; i < IP_UUID_STR_LEN - 1; ++i)
    {
        switch (i)
        {
          case 8: case 13: case 18: case 23:
            if (str[i] != '-')
            {
                return -1;
            }
            continue;
            break;
          default:
            break;
        }

        x = str[i];
        if (!(isxdigit)(x))
        {
            return -1;
        }
        if ((isdigit)(x))
        {
            x -= '0';
        }
        else
        {
            x = (tolower)(x);
            x -= 'a';
            x += 10;
        }

        if (j & 1)
        {
            b = (b << 4) | x;
            *p++ = (u8) b;
        }
        else
        {
            b = x;
        }
        ++j;
        ASSERT(b < 256);
    }
    ASSERT(j == 32);
    return 0;
}

/* IPCreateUuid -- generate a v1 UUID */
int IPCreateUuid(IPUuid* uuid)
{
    static u64 lasttime;
    BOOL enabled;
    u64 timestamp;
    u16 clockseq;
    u32 bias;
    u8  node[ETH_ALEN];

    /* acquire system wide lock so we're alone */
    enabled = OSDisableInterrupts();

    /* get time as 60 bit 100ns ticks since whenever. */
    do
    {
        timestamp = (u64) OSTicksToTimestamp(OSGetTime());
        timestamp &= (u64) 0x0fffffffffffffff;
    } while (lasttime == timestamp);
    lasttime = timestamp;

    /* get saved state from NV storage */
    bias = GetCounterBias();

    /* get node ID */
    IPGetMacAddr(NULL, node);
    if (node[1] == 0)   // no IEEE address?
    {
        OSTime random;
        random = OSGetTime();
        random ^= __OSGetSystemTime();
        random ^= ~bias;
        random ^= ((OSTime) bias) << 32;
        memmove(node, &random, ETH_ALEN);
        node[0] |= 0x80;    // set the most significant bit to 1
    }

    /* get 14-bit clock sequece */
    clockseq = (u16) (bias & 0x3fff);

    /* stuff fields into the UUID */
    /* Construct a version 1 uuid with the information we've gathered
     * plus a few constants. */
    uuid->timeLow = (u32) timestamp;
    uuid->timeMid = (u16) (timestamp >> 32);
    uuid->timeHiAndVersion = (u16) (timestamp >> 48);
    uuid->timeHiAndVersion |= (1 << 12);
    uuid->clockSeqLow = (u8) clockseq;
    uuid->clockSeqHiAndReserved = (u8) (clockseq >> 8);
    uuid->clockSeqHiAndReserved |= 0x80;
    memmove(&uuid->node, node, sizeof node);

    OSRestoreInterrupts(enabled);
    return 1;
}

/* IPCreateUuid -- generate a v4 UUID */
int IPCreateUuid4(IPUuid* uuid)
{
    MD5Context context;

    IPCreateUuid(uuid);
    MD5Init(&context);
    MD5Update(&context, (u8*) uuid, sizeof(IPUuid));
    MD5Final((u8*) uuid, &context);

    uuid->timeHiAndVersion &= ~(0x0f << 12);
    uuid->timeHiAndVersion |= (0x04 << 12);
    uuid->clockSeqHiAndReserved &= ~0xc0;
    uuid->clockSeqHiAndReserved |= 0x80;
    return 1;
}

/* IPCompareUuid --  Compare two UUID's "lexically" and return
       -1   u1 is lexically before u2
        0   u1 is equal to u2
        1   u1 is lexically after u2
    Note:   lexical ordering is not temporal ordering!
*/
#define CHECK(f1, f2) if (f1 != f2) return f1 < f2 ? -1 : 1;

int IPCompareUuid(const IPUuid* u1, const IPUuid* u2)
{
    int i;

    CHECK(u1->timeLow, u2->timeLow);
    CHECK(u1->timeMid, u2->timeMid);
    CHECK(u1->timeHiAndVersion, u2->timeHiAndVersion);
    CHECK(u1->clockSeqHiAndReserved, u2->clockSeqHiAndReserved);
    CHECK(u1->clockSeqLow, u2->clockSeqLow)
    for (i = 0; i < ETH_ALEN; i++)
    {
        if (u1->node[i] < u2->node[i])
        {
            return -1;
        }
        if (u1->node[i] > u2->node[i])
        {
            return 1;
        }
      }
    return 0;
}

#undef CHECK

#ifdef WIN32

void IPGetMacAddr(IPInterface* interface, u8* macAddr)
{
    memset(macAddr, 0, ETH_ALEN);
}

#endif