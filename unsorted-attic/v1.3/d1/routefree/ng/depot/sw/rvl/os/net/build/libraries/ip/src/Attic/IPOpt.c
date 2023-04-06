/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:

  Copyright 2002 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPOpt.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    2     3/27/02 17:42 Shiki
    Implemented IPProcessSourceRoute().

    1     3/25/02 17:08 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <dolphin/os.h>
#include <dolphin/ip.h>
#include "IPPrivate.h"

// Source Route
// Record Route
// Time Stamp

#define OPT_MAX     (IP_MAX_HLEN - IP_MIN_HLEN) // Max option length

void IPSwapAddr(u8* a, u8* b)
{
    u8 c[IP_ALEN];

    memmove(c, a, IP_ALEN);
    memmove(a, b, IP_ALEN);
    memmove(b, c, IP_ALEN);
}

// Return IP_ERR_NONE or IP_ERR_UNREACHABLE, IP_ERR_INVALID
s32 IPProcessSourceRoute(IPHeader* ip)
{
    u8* opt;
    int optlen;
    int i;
    s32 len;
    s32 ptr;

    ASSERT(ip);
    optlen = IP_HLEN(ip) - IP_MIN_HLEN;
    ASSERT(0 <= optlen);

    opt = (u8*) ip + IP_MIN_HLEN;
    for (i = 0;
         i < optlen && opt[i] != IP_OPT_EOOL;
         i += len)
    {
        switch (opt[i])
        {
          case IP_OPT_EOOL:
          case IP_OPT_NOP:
            len = 1;
            break;
          default:
            if (optlen <= i + 1)
            {
                return IP_ERR_INVALID;
            }
            len = opt[i + 1];
            if (optlen < i + len)
            {
                return IP_ERR_INVALID;
            }
            break;
        }

        if (opt[i] == IP_OPT_LSRR || opt[i] == IP_OPT_SSRR)
        {
            if (len < 3 + IP_ALEN)
            {
                return IP_ERR_INVALID;
            }

            ptr = opt[i + 2];
            if (ptr - 1 + IP_ALEN <= len)
            {
                // Not the last destination (incomplete)
                //
                // [RFC 1122]
                // SHOULD send ICMP Destination Unreachable if drop and
                // unless the datagram was itself an ICMP error message.
                // MAY be able to act as an intermediate hop.
                return IP_ERR_INVALID;
            }

            return IP_ERR_NONE;
        }
    }

    return IP_ERR_NONE;
}

s32 IPReverseSourceRoute(IPHeader* ip)
{
    u8* opt;
    int optlen;
    int i;
    s32 len;
    s32 ptr;

    if (ip == NULL)
    {
        return IP_ERR_INVALID;
    }

    optlen = IP_HLEN(ip) - IP_MIN_HLEN;
    if (optlen <= 0)
    {
        return IP_ERR_NONE;
    }

    opt = (u8*) ip + IP_MIN_HLEN;
    for (i = 0;
         i < optlen && opt[i] != IP_OPT_EOOL;
         i += len)
    {
        switch (opt[i])
        {
          case IP_OPT_EOOL:
          case IP_OPT_NOP:
            len = 1;
            break;
          default:
            if (optlen <= i + 1)
            {
                return IP_ERR_INVALID;
            }
            len = opt[i + 1];
            if (optlen < i + len)
            {
                return IP_ERR_INVALID;
            }
            break;
        }

        if (opt[i] == IP_OPT_LSRR || opt[i] == IP_OPT_SSRR)
        {
            if (len < 3 + IP_ALEN)
            {
                return IP_ERR_INVALID;
            }

            ptr = opt[i + 2];
            if (ptr - 1 + IP_ALEN <= len)
            {
                // Not the last destination (incomplete)
                return IP_ERR_INVALID;
            }

            len -= 3;
            len &= ~(IP_ALEN - 1);
            opt += i;
            opt[2] = 4;
            opt += 3;
            IPSwapAddr(ip->dst, opt + len - IP_ALEN);
            len -= IP_ALEN;
            for (i = len / 2; IP_ALEN <= i; i -= IP_ALEN)
            {
                IPSwapAddr(opt + i, opt + len - IP_ALEN - i);
            }
            return IP_ERR_NONE;
            // Succeeded
        }
    }

    return IP_ERR_NONE;
    // Not found
}

s32 IPUpdateRecordRoute(IPHeader* ip, u8* addr)
{
    u8* opt;
    int optlen;
    int i;
    s32 len;
    s32 ptr;

    if (ip == NULL || addr == NULL)
    {
        return IP_ERR_INVALID;
    }

    optlen = IP_HLEN(ip) - IP_MIN_HLEN;
    if (optlen <= 0)
    {
        return IP_ERR_NONE;
    }

    i = 0;
    opt = (u8*) ip + IP_MIN_HLEN;
    while (i < optlen && opt[i] != IP_OPT_EOOL)
    {
        switch (opt[i])
        {
          case IP_OPT_EOOL:
          case IP_OPT_NOP:
            len = 1;
            break;
          default:
            if (optlen <= i + 1)
            {
                return IP_ERR_INVALID;
            }
            len = opt[i + 1];
            if (optlen < i + len)
            {
                return IP_ERR_INVALID;
            }
            break;
        }

        if (opt[i] == IP_OPT_RR)
        {
            if (len < 3 + IP_ALEN)
            {
                return IP_ERR_INVALID;
            }

            ptr = opt[i + 2];
            if (ptr - 1 + IP_ALEN <= len)
            {
                memmove(opt + i + ptr - 1, addr, IP_ALEN);
                opt[i + 2] = (u8) (ptr + IP_ALEN);
            }
            return IP_ERR_NONE;
            // Succeeded
        }

        i += len;
    }

    return IP_ERR_NONE;
}

#if 0

s32 IPSetSourceRoute(u8* opt, u8 type, const u8* addr, s32 addrlen)
{
    int i;
    s32 len;

    if (type != IP_OPT_LSRR && type != IP_OPT_SSRR)
    {
        return IP_ERR_INVALID;
    }

    if (addr && (addrlen <= 0 || addrlen % IP_ALEN || OPT_MAX - 3 < addrlen))
    {
        return IP_ERR_DATASIZE;
    }

    i = 0;
    while (i < OPT_MAX && opt[i] != IP_OPT_EOOL)
    {
        switch (opt[i])
        {
          case IP_OPT_EOOL:
          case IP_OPT_NOP:
            len = 1;
            break;
          default:
            if (OPT_MAX <= i + 1)
            {
                return IP_ERR_INVALID;
            }
            len = opt[i + 1];
            break;
        }

        if (opt[i] == IP_OPT_LSRR || opt[i] == IP_OPT_SSRR)
        {
            memmove(opt + i, opt + i + len, OPT_MAX - i - len);
            memset(opt + OPT_MAX - len, 0, len);
        }
        else
        {
            i += len;
        }
    }

    if (OPT_MAX < i + 3 + addrlen)
    {
        return IP_ERR_DATASIZE;
    }

    if (addr)
    {
        opt[i] = type;
        opt[i+1] = (u8) (3 + addrlen);
        opt[i+2] = 4;
        memmove(opt + i + 3, addr, addrlen);
    }
    return i + 3 + addrlen;
}

s32 IPGetSourceRoute(u8* opt, u8* type, u8* addr, s32 addrlen)
{
    int i;
    s32 len;

    if (addr == NULL || addrlen <= 0 || addrlen % IP_ALEN)
    {
        return IP_ERR_DATASIZE;
    }

    i = 0;
    while (i < OPT_MAX && opt[i] != IP_OPT_EOOL)
    {
        switch (opt[i])
        {
          case IP_OPT_EOOL:
          case IP_OPT_NOP:
            len = 1;
            break;
          default:
            if (OPT_MAX <= i + 1)
            {
                return IP_ERR_INVALID;
            }
            len = opt[i + 1];
            break;
        }

        if (opt[i] == IP_OPT_LSRR || opt[i] == IP_OPT_SSRR)
        {
            len -= 3;
            if (len <= 0 || len % IP_ALEN)
            {
                return IP_ERR_INVALID;
            }
            if (addrlen < len)
            {
                return IP_ERR_DATASIZE;
            }
            if (type)
            {
                *type = opt[i];
            }
            addrlen = len;
            memmove(addr, opt + i, addrlen);
            return addrlen;
            // Succeeded
        }

        i += len;
    }

    return 0;
    // Not found
}

s32 IPSetRecordRoute(u8* opt, s32 addrlen)
{
    int i;
    s32 len;

    if (addrlen < 0 || addrlen % IP_ALEN || OPT_MAX - 3 < addrlen)
    {
        return IP_ERR_DATASIZE;
    }

    i = 0;
    while (i < OPT_MAX && opt[i] != IP_OPT_EOOL)
    {
        switch (opt[i])
        {
          case IP_OPT_EOOL:
          case IP_OPT_NOP:
            len = 1;
            break;
          default:
            if (OPT_MAX <= i + 1)
            {
                return IP_ERR_INVALID;
            }
            len = opt[i + 1];
            break;
        }

        if (opt[i] == IP_OPT_RR)
        {
            memmove(opt + i, opt + i + len, OPT_MAX - i - len);
            memset(opt + OPT_MAX - len, 0, len);
        }
        else
        {
            i += len;
        }
    }

    if (OPT_MAX < i + 3 + addrlen)
    {
        return IP_ERR_DATASIZE;
    }

    if (0 < addrlen)
    {
        opt[i] = IP_OPT_RR;
        opt[i+1] = (u8) (3 + addrlen);
        opt[i+2] = 4;
        memset(opt + i + 3, 0, addrlen);
    }
    return i + 3 + addrlen;
}

s32 IPGetRecordRoute(u8* opt, u8* addr, s32 addrlen)
{
    int i;
    s32 len;

    if (addr == NULL || addrlen <= 0 || addrlen % IP_ALEN)
    {
        return IP_ERR_DATASIZE;
    }

    i = 0;
    while (i < OPT_MAX && opt[i] != IP_OPT_EOOL)
    {
        switch (opt[i])
        {
          case IP_OPT_EOOL:
          case IP_OPT_NOP:
            len = 1;
            break;
          default:
            if (OPT_MAX <= i + 1)
            {
                return IP_ERR_INVALID;
            }
            len = opt[i + 1];
            break;
        }

        if (opt[i] == IP_OPT_RR)
        {
            len -= 3;
            if (len <= 0 || len % IP_ALEN)
            {
                return IP_ERR_INVALID;
            }
            if (addrlen < len)
            {
                return IP_ERR_DATASIZE;
            }
            addrlen = len;
            memmove(addr, opt + i, addrlen);
            return addrlen;
            // Succeeded
        }

        i += len;
    }

    return 0;
    // Not found
}

#endif
