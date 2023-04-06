/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IP6.c

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IP6.c,v $
  Revision 1.5  2006/04/14 23:02:59  mxu
  fix a compiling bug when VERBOSE is turned on

  Revision 1.4  2006/04/12 01:45:05  mxu
  change sprintf to snprintf

  Revision 1.3  2006/04/11 01:40:35  mxu
  update to Nintendo's April 05 release

  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    38    4/03/06 15:59 Shiki
    Fixed IP6SetSource() and IP6SetDestination().

    37    3/03/06 10:24 Shiki
    Fixed IP6SelectSourceAddress().

    36    3/02/06 11:19 Shiki
    Fixed IP6In() to drop packets with extra router alert options.

    35    3/02/06 9:50 Shiki
    Modified IP6In() to take the router alert value.

    34    2/28/06 9:06 Shiki
    Modified IP6GetNextHop() to use modified IP6Entry{}.

    33    2/22/06 15:52 Shiki
    Modified IP6Out() not to check the loopback address separately now that
    IP6Startup() creates the IP6Entry entry for the loopback address.

    32    2/14/06 18:47 Shiki
    Revised to collect interface statistics.

    31    2/01/06 16:23 Shiki
    Added full support of IPv6 PMTU discovery.

    30    1/26/06 18:41 Shiki
    Renamed IP6Neighbor to IP6Entry.

    29    1/26/06 18:16 Shiki
    Modified IP6Out() to support PMTU for multicast addresses.

    28    1/26/06 11:44 Shiki
    Fixed IP6SelectSourceAddress().

    27    1/26/06 11:29 Shiki
    Modified IP6GetNextHop() to update info->mtu.
    Modified IP6Out() to support PMTU.
    Fixed an IP6Out() show stopper bug.
    Fixed IP6SelectSourceAddress().

    26    1/24/06 17:24 Shiki
    Fixed IP6In().

    25    1/20/06 17:01 Shiki
    Fixed IP6GetSockOpt() and IP6SetSockOpt().

    24    1/20/06 10:53 Shiki
    Fixed IP6GetNextHop() to check routerLifetime.
    Fixed IP6Out() to hold a datagram to a neighbor in the
    ND_STATE_INCOMPLETE state.

    23    1/19/06 19:04 Shiki
    Fixed IP6SelectSourceAddress().

    22    1/19/06 18:25 Shiki
    Renamed IP6GetNeighbor() to IP6GetNextNeighbor().

    21    1/18/06 18:19 Shiki
    Revised the reference count management of IP6Entry{}.

    20    1/16/06 14:23 Shiki
    Fixed CheckOptionType() to support (e.2) - (2) of RFC 2463.

    19    1/13/06 9:46 Shiki
    Added ND_STATE_INIT state.

    18    1/11/06 10:26 Shiki
    Fixed IP6In() to send parameter problem if Hop-by-Hop Options header
    does not immediately follow the IPv6 header.

    17    1/10/06 10:54 Shiki
    Fixed IP6In().

    16    1/06/06 17:43 Shiki
    Fixed option type check code.

    15    1/06/06 13:18 Shiki
    Moved some constants from IP6.c to IP.c for SN.

    13    04/09/28 20:19 Ueno_kyu
    Modified IP6Out() to use the IPv6 minimum link MTU to send a multicast
    datagram.

    12    04/09/24 11:00 Ueno_kyu
    Removed an assertion in IP6Out().

    11    04/09/16 15:06 Ueno_kyu
    Modified an assertion in IP6Out().

    10    04/09/07 14:32 Ueno_kyu
    Added brief support for Routing Header Option.

    9     04/08/31 19:23 Ueno_kyu
    Added support for IPv6 fragmentation and reassembly.

    8     04/08/18 16:30 Ueno_kyu
    Modified IP6In() to support Hop-by-Hop Options header and Destination
    Options header.

    7     04/07/26 8:59 Ueno_kyu
    Modified IP6Out() to call NDHold() before IP6SetNeighborState().

    6     04/07/13 10:13 Ueno_kyu
    Modified an assertion in IP6Out().

    5     6/29/04 11:08 Shiki
    Modified the use of IF_FLAG_* for better loopback support. Now
    IF_FLAG_* is set to IFDatagram{} before sending the packet.

    4     6/24/04 16:45 Shiki
    Fixed IP6In() to discard the packet with a unrecognized header.

    3     6/22/04 9:29 Shiki
    Clean up.

    2     6/21/04 12:03 Shiki
    Revised to support AAAA.

    1     6/09/04 15:58 Shiki
    IPv6 pilot implementation
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifdef IOP_OS
#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <dolphin/iop_libc.h>
#else
#include <stdio.h>
#endif // IOP_OS

#include <stddef.h>
#include <dolphin/os.h>
#include <dolphin/socket.h>
#include "IPPrivate.h"
#include "IP6Private.h"

#ifdef IOP_OS
const SOIn6Addr SOIn6AddrSolicited = { { 0xff, 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01, 0xff, 0, 0, 0 } };
#else
const SOIn6Addr SOIn6AddrSolicited = { 0xff, 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01, 0xff, 0, 0, 0 };
#endif // IOP_OS

// RFC 2460

char* IP6AtoN(const char* dotted, SOIn6Addr* addr)
{
    int   compressed = -1;
    int   c;
    u32   part[8];
    int   n;
    u32   val;
    int   i;
    int   j;
    const char* v4 = NULL;
    int   max = 8;

    n = 0;
    c = *dotted;
    for (;;)
    {
        if (c == ':')
        {
            if (max <= n)
            {
                return NULL;
            }
            c = *++dotted;
            if (c == ':')
            {
                if (0 <= compressed)
                {
                    return NULL;
                }
                compressed = n;
                c = *++dotted;
            }
            else if (n == 0)
            {
                return NULL;
            }
        }
        if (c == '.')
        {
            --n;
            if (v4 &&
                ((0 <= compressed && n < 6) ||
                 (compressed < 0 && n == 6)))
            {
                max = 6;
                break;
            }
            ++n;
        }
        if (!(isxdigit)(c))
        {
            if (c <= 127 && (0 <= compressed || n == max))
            {
                break;
            }
            return NULL;
        }
        v4 = dotted;
        for (val = 0 ;; c = *++dotted)
        {
            if ((isdigit)(c))
            {
                val *= 16;
                val += c - '0';
            }
            else if ((isxdigit)(c))
            {
                val *= 16;
                val += 10 + c - ((islower)(c) ? 'a' : 'A');
            }
            else
            {
                break;
            }
        }
        part[n++] = val;
        if (127 < c)   // !isascii()
        {
            return NULL;
        }
        if (0xffff < val)
        {
            return NULL;
        }
    }

    if (compressed < 0)
    {
        compressed = 0;
    }
    j = 0;
    for (i = 0; i < compressed; ++i)
    {
        addr->addr[j++] = (u8) (part[i] >> 8);
        addr->addr[j++] = (u8) part[i];
    }
    for (i = 0; i < max - n; ++i)
    {
        addr->addr[j++] = 0;
        addr->addr[j++] = 0;
    }
    for (i = compressed; i < n; ++i)
    {
        addr->addr[j++] = (u8) (part[i] >> 8);
        addr->addr[j++] = (u8) part[i];
    }
    ASSERT(max == 6 || j == 16);
    if (max == 6)
    {
        return IPAtoN(v4, &addr->addr[12]);
    }
    return (char*) dotted;
}

// Convert binary address to dotted-decimal notation
#ifdef IOP_OS
char* IP6NtoA(const SOIn6Addr* addr, char* ascii, int buflen)
#else
char* IP6NtoA(const SOIn6Addr* addr, char* ascii)
#endif // IOP_OS
{
    u16* part;
    int  len = 0;
    u16* zero = NULL;
    BOOL compressed = FALSE;

    for (part = (u16*) addr->addr;
         part < (u16*) &addr->addr[16];
         ++part)
    {
        if (*part != 0 || compressed)
        {
            if (zero && !compressed)
            {
                if (zero == (u16*) addr->addr)
                {
                    if (part - zero == 5 && *part == 0xffff)
                    {
                        // V4MAPPED
#ifdef IOP_OS
                        snprintf(ascii, buflen, "::FFFF:%d.%d.%d.%d", addr->addr[12],
#else
                        sprintf(ascii, "::FFFF:%d.%d.%d.%d", addr->addr[12],
#endif // IOP_OS
                                                             addr->addr[13],
                                                             addr->addr[14],
                                                             addr->addr[15]);
                        return ascii;
                    }
                    else if (part - zero == 6 &&
                             !(memcmp(&addr->addr[12], &SOIn6AddrAny.addr[12], 4) == 0 ||
                               memcmp(&addr->addr[12], &SOIn6AddrLoopback.addr[12], 4) == 0))
                    {
                        // V4COMPAT
#ifdef IOP_OS
                        snprintf(ascii, buflen, "::%d.%d.%d.%d", addr->addr[12],
#else
                        sprintf(ascii, "::%d.%d.%d.%d", addr->addr[12],
#endif // IOP_OS
                                                        addr->addr[13],
                                                        addr->addr[14],
                                                        addr->addr[15]);
                        return ascii;
                    }
                }
                if (part - zero < 2)
                {
#ifdef IOP_OS
                    if (0 < len)
                    {
                        len += snprintf(ascii + len, buflen - len, ":");
                    }
                    len += snprintf(ascii + len, buflen - len, "0");
#else
                    if (0 < len)
                    {
                        len += sprintf(ascii + len, ":");
                    }
                    len += sprintf(ascii + len, "0");
#endif // IOP_OS
                    zero = NULL;
                }
                else
                {
#ifdef IOP_OS
                    len += snprintf(ascii + len, buflen - len, ":");
#else
                    len += sprintf(ascii + len, ":");
#endif // IOP_OS
                    compressed = TRUE;
                }
            }
#ifdef IOP_OS
            if (0 < len)
            {
                len += snprintf(ascii + len, buflen - len, ":");
            }
            len += snprintf(ascii + len, buflen - len, "%X", *part);
#else
            if (0 < len)
            {
                len += sprintf(ascii + len, ":");
            }
            len += sprintf(ascii + len, "%X", *part);
#endif // IOP_OS
        }
        else if (zero == NULL)
        {
            zero = part;
        }
    }
    if (zero && !compressed)
    {
        if (part - zero < 2)
        {
#ifdef IOP_OS
            len += snprintf(ascii + len, buflen - len, ":0");
#else
            len += sprintf(ascii + len, ":0");
#endif // IOP_OS
        }
        else
        {
#ifdef IOP_OS
            len += snprintf(ascii + len, buflen - len, "::");
#else
            len += sprintf(ascii + len, "::");
#endif // IOP_OS
        }
    }
    ASSERT(len < SO_INET6_ADDRSTRLEN);
    return ascii;
}

#ifdef IP_INET6

IPInfo* IP6LookupInfo(IFQueue* queue,
                      const SOIn6Addr* srcAddr, const SOIn6Addr* dstAddr,
                      u16 src, u16 dst,
                      u32 flag)
{
#ifdef IOP_OS
    TCPIP_UNUSED(dstAddr);
#else
    #pragma unused(dstAddr)
#endif // IOP_OS
    IPInfo* info;
    IPInfo* next;
    int     wildcard;
    int     minimum = 3;
    IPInfo* match = NULL;
#ifdef IOP_OS
    s32     mcast = 0;
#else
    s32     mcast;
#endif // IOP_OS
    SOSockAddrIn6* local;
    SOSockAddrIn6* remote;

    if (SO_IN6_IS_ADDR_MULTICAST(dstAddr))
    {
        mcast = IP6MulticastLookup(NULL, dstAddr);
        if (mcast < 0)
        {
            return NULL;
        }
    }

    IFIterateQueue(IPInfo*, queue, info, next, link)
    {
        if (info->family != SO_AF_INET6)
        {
            continue;
        }

        local = IPGetLocalSockAddr(info);
        remote = IPGetRemoteSockAddr(info);

        if (local->port == 0 || local->port != dst)
        {
            continue;
        }

        if (SO_IN6_IS_ADDR_MULTICAST(dstAddr))
        {
            if ((info->flag & IP_INFO_FLAG_MCAST(mcast)) == 0) // Joined?
            {
                continue;
            }

            if ((flag & IF_FLAG_LOOPBACK) &&    // Loopback?
                (info->flag & IP_INFO_FLAG_MCASTLOOP) == 0)
            {
                continue;
            }
        }

        wildcard = 0;

        if (!SO_IN6_ARE_ADDR_EQUAL(dstAddr, &SOIn6AddrAny))
        {
            if (SO_IN6_ARE_ADDR_EQUAL(&local->addr, &SOIn6AddrAny))
            {
                ++wildcard;
            }
            else if (!SO_IN6_ARE_ADDR_EQUAL(&local->addr, dstAddr))
            {
                continue;
            }
        }
        else if (!SO_IN6_ARE_ADDR_EQUAL(&local->addr, &SOIn6AddrAny))
        {
            ++wildcard;
        }

        if (!SO_IN6_ARE_ADDR_EQUAL(srcAddr, &SOIn6AddrAny))
        {
            if (SO_IN6_ARE_ADDR_EQUAL(&remote->addr, &SOIn6AddrAny))
            {
                ++wildcard;
            }
            else if (remote->port != src ||
                     !SO_IN6_ARE_ADDR_EQUAL(&remote->addr, srcAddr))
            {
                continue;
            }
        }
        else if (!SO_IN6_ARE_ADDR_EQUAL(&remote->addr, &SOIn6AddrAny))
        {
            ++wildcard;
        }

        if (wildcard < minimum)
        {
            match = info;
            minimum = wildcard;
            if (minimum == 0)
            {
                break;
            }
        }
    }
    return match;
}

/*---------------------------------------------------------------------------*
  Name:         IPBind

  Description:  Specifies the local socket

  Arguments:    Queue   Queue of IPInfo
                info    IPInfo to which local socket is assigned
                socket  Port number must be other than zero.
                        Address can be 0.0.0.0 (any).
                reuse

  Returns:
 *---------------------------------------------------------------------------*/
s32 IP6Bind(IFQueue* queue, IPInfo* info, const SOSockAddrIn6* socket, BOOL reuse)
{
    IPInfo* iter;
    IPInfo* next;
    SOSockAddrIn6* local;
    SOSockAddrIn6* remote;
    SOSockAddrIn6* connected;
    IP6Entry* neighbor = NULL;

    if (socket == NULL ||
        socket->len != sizeof(SOSockAddrIn6) ||
        socket->family != SO_PF_INET6 ||
        socket->port == 0)
    {
        return IP_ERR_INVALID;
        // NOT REACHED HERE
    }

    if (!SO_IN6_ARE_ADDR_EQUAL(&socket->addr, &SOIn6AddrAny) &&
        !SO_IN6_ARE_ADDR_EQUAL(&socket->addr, &SOIn6AddrLoopback) &&
        !SO_IN6_IS_ADDR_MULTICAST(&socket->addr) &&
        !((neighbor = IP6SearchNeighbor(&socket->addr)) != NULL && neighbor->state == ND_STATE_PREFERRED))
    {
        return IP_ERR_INV_SOCKET;
        // NOT REACHED HERE
    }

    IFIterateQueue(IPInfo*, queue, iter, next, link)
    {
        if (iter == info || iter->family != info->family)
        {
            continue;
        }
        local = IPGetLocalSockAddr(iter);
        remote = IPGetRemoteSockAddr(iter);
        if (local->port == socket->port &&
            SO_IN6_ARE_ADDR_EQUAL(&local->addr, &socket->addr))
        {
            if (!reuse)
            {
                return IP_ERR_EXIST;
                // NOT REACHED HERE
            }
            connected = IPGetRemoteSockAddr(info);
            if (remote->port == connected->port &&
                SO_IN6_ARE_ADDR_EQUAL(&remote->addr, &connected->addr))
            {
                return IP_ERR_EXIST;
                // NOT REACHED HERE
            }
        }
    }

/*
    if (info->proto == IP_PROTO_TCP &&
        !reuse &&
        TCP4LookupTimeWaitInfo())
 */

    memmove(IPGetLocalSockAddr(info), socket, sizeof(SOSockAddrIn6));

    IP6SetSource(info, neighbor);

    return IP_ERR_NONE;
}

/*---------------------------------------------------------------------------*
  Name:         IPConnect

  Description:  Specifies the remote socket. Local port number is also
                automatically assigened if not yet specified.

  Arguments:    Queue   Queue of IPInfo
                info    IPInfo to which remote socket is assigned
                socket  Port number must be other than zero.
                        Address cannot be 0.0.0.0.

  Returns:
 *---------------------------------------------------------------------------*/
s32 IP6Connect(IFQueue* queue, IPInfo* info, const SOSockAddrIn6* socket, u16* last)
{
    IPInfo*        iter;
    IPInfo*        next;
    SOIn6Addr      localAddr;
    SOSockAddrIn6* local;
    SOSockAddrIn6* remote;
    IP6Entry*      from = NULL;
    IP6Entry*      nextHop = NULL;
    IP6Entry*      to = NULL;

    if (socket == NULL ||
        socket->len != sizeof(SOSockAddrIn6) ||
        socket->family != SO_PF_INET6 ||
        socket->port == 0)
    {
        return IP_ERR_INVALID;
    }

    if (SO_IN6_ARE_ADDR_EQUAL(&socket->addr, &SOIn6AddrAny))    // Remote address is required
    {
        return IP_ERR_INV_SOCKET;
    }

    nextHop = IP6GetNextHop(info, &socket->addr, &to);
    if (nextHop == NULL)
    {
        return IP_ERR_UNREACHABLE;              // No route to the destination
    }

    if (info->proto == IP_PROTO_TCP)
    {
        // Reject invalid remote IP address (e.g., a broadcast or
        // multicast address).
        if (SO_IN6_IS_ADDR_MULTICAST(&socket->addr))
        {
            return IP_ERR_INV_SOCKET;
        }
    }

    local = IPGetLocalSockAddr(info);
    remote = IPGetRemoteSockAddr(info);
    if (SO_IN6_ARE_ADDR_EQUAL(&local->addr, &SOIn6AddrAny))
    {
        from = IP6SelectSourceAddress(nextHop->interface, &socket->addr, &localAddr);
    }
    else
    {
        localAddr = local->addr;
    }
    if (info->proto == IP_PROTO_TCP && SO_IN6_IS_ADDR_UNSPECIFIED(&localAddr))
    {
        return IP_ERR_UNREACHABLE;              // No route to the destination
    }

    if (local->port == 0)
    {
Next:
        // Assign an ephemeral source port number
        local->port = IPGetAnonPort(queue, last);
        if (local->port == 0)
        {
            return IP_ERR_INS_RESOURCES;
        }

        if (info->proto == IP_PROTO_TCP &&
            TCP6LookupTimeWaitInfo(&socket->addr, socket->port,
                                   &localAddr, local->port))
        {
            // XXX Prevent possible forever loop somehow...
            goto Next;
        }
    }
    else
    {
        // See if connecting to the same destination from the same local socket
        IFIterateQueue(IPInfo*, queue, iter, next, link)
        {
            SOSockAddrIn6* localIter;
            SOSockAddrIn6* remoteIter;

            if (iter == info)
            {
                continue;
            }
            localIter = IPGetLocalSockAddr(iter);
            remoteIter = IPGetRemoteSockAddr(iter);
            if (localIter->port  == local->port &&
                remoteIter->port == remote->port &&
                SO_IN6_ARE_ADDR_EQUAL(&localIter->addr, &localAddr) &&
                SO_IN6_ARE_ADDR_EQUAL(&remoteIter->addr, &remote->addr))
            {
                return IP_ERR_EXIST;
                // NOT REACHED HERE
            }
        }

        if (info->proto == IP_PROTO_TCP &&
            TCP6LookupTimeWaitInfo(&socket->addr, socket->port,
                                   &localAddr, local->port))
        {
            return IP_ERR_EXIST;
            // NOT REACHED HERE
        }
    }

    // Commit connect
    memmove(remote, socket, sizeof(SOSockAddrIn6));
    if (SO_IN6_ARE_ADDR_EQUAL(&local->addr, &SOIn6AddrAny))
    {
        local->addr = localAddr;
    }

    IP6SetSource(info, from);
    IP6SetNextHop(info, nextHop);
    IP6SetDestination(info, to);
    return IP_ERR_NONE;
}

void IP6ReceiveSocket(SOSockAddrIn6* sockAddr6, SOIn6Addr* addr, u16 port)
{
    if (sockAddr6)
    {
        ASSERT(sizeof(SOSockAddrIn6) <= sockAddr6->len);
        sockAddr6->len = sizeof(SOSockAddrIn6);
        sockAddr6->family = SO_AF_INET6;
        memmove(&sockAddr6->addr, addr, 16);
        sockAddr6->port = port;
        // XXX more field
    }
}

u16 IP6CheckSum(u8 proto, IFVec* vec, int nVec, void* payload, s32 plen)
{
    IP6Hdr* ip6;
    s32     hlen;
    u16*    p;
    u32     sum = 0;
    u32     odd;

    ASSERT(0 < nVec);
    ASSERT(sizeof(IP6Hdr) <= vec->len);

    // Add up pseudo header
    hlen = 2 * sizeof(SOIn6Addr);
    ip6 = (IP6Hdr*) vec->data;
    p = (u16*) &ip6->src;
    while (0 < hlen)
    {
        sum += *p++;
        hlen -= 2;
    }
    sum += plen >> 16;
    sum += (plen & 0xffff);
    // sum += 0;
    sum += proto;

    // Add up upper-layer data
    p = (u16*) payload;
#ifdef IOP_OS
    while ((u8*) p < (u8*) vec->data || (u8*) vec->data + vec->len <= (u8*) p)
#else
    while ((u8*) p < vec->data || (u8*) vec->data + vec->len <= (u8*) p)
#endif // IOP_OS
    {
        ++vec;
        if (--nVec <= 0)
        {
            break;
        }
    }
    if (0 < nVec)
    {
        s32 len = vec->len - ((u8*) p - (u8*) vec->data);
        ASSERT(0 < len);
        do {
            if (plen < len)
            {
                len = plen;
            }
            plen -= len;
            while (1 < len)
            {
                sum += *p++;
                len -= 2;
            }
            if (len == 1)
            {
                odd = ((u32) (*(u8*) p)) << 8;
            }
            else
            {
                odd = 0;
            }

            do {
                if (--nVec <= 0 || plen <= 0)
                {
                    sum += odd;
                    goto Done;
                }
                ++vec;
            } while (vec->len == 0);

            p = (u16*) vec->data;
            if (len == 1)
            {
                odd |= *(u8*) p;
                sum += odd;
#ifdef IOP_OS
                (u8*) p ++;
#else
                (u8*) p += 1;
#endif // IOP_OS
                len = vec->len - 1;
                --plen;
            }
            else
            {
                len = vec->len;
            }
        } while (0 < plen);
    }
Done:
    sum = (sum & 0xffff) + (sum >> 16);
    sum = (sum & 0xffff) + (sum >> 16);
    return (u16) (sum ^ 0xffff);
}

/*---------------------------------------------------------------------------*
  Name:         CheckOptionType

  Reference:    [RFC2610 4.2]

  Arguments:    opt     Pointer to IP6Opt.

  Returns:      FALSE to discard the packet. Otherwise, TRUE.
 *---------------------------------------------------------------------------*/
static BOOL CheckOptionType(IPInterface* interface, IP6Hdr* ip6, u32 flag, IP6Opt* opt)
{
    ASSERT(0 < (u8*) opt - (u8*) ip6);
    switch (IP6OPT_TYPE(opt->type))
    {
      case IP6OPT_TYPE_SKIP:
        return TRUE;    // Not discard the packet
        break;
      case IP6OPT_TYPE_DISCARD:
        break;
      case IP6OPT_TYPE_FORCEICMP:
        flag &= ~(IF_FLAG_MULTICAST | IF_FLAG_BROADCAST);   // (e.2) - (2) [RFC 2463]
        ICMP6SendError(interface, ICMP6_PARAM_PROB,
                       ICMP6_PARAMPROB_OPTION, ip6, flag,
                       (u32) ((u8*) opt - (u8*) ip6));
        break;
      case IP6OPT_TYPE_ICMP:
        if (!SO_IN6_IS_ADDR_MULTICAST(&ip6->dst))
        {
            ICMP6SendError(interface, ICMP6_PARAM_PROB,
                           ICMP6_PARAMPROB_OPTION, ip6, flag,
                           (u32) ((u8*) opt - (u8*) ip6));
        }
        break;
    }
    return FALSE;       // Discard the packet
}

void IP6In(IPInterface* interface, IP6Hdr* ip6, s32 len, u32 flag)
{
    u8*     hdr;
    u8      next;
    s32     hlen;
    IP6Opt* opt;
    int     routerAlert = -1;
#ifndef IOP_OS
#ifdef VERBOSE
    char src[SO_INET6_ADDRSTRLEN];
    char dst[SO_INET6_ADDRSTRLEN];
#endif  // VERBOSE
#endif  // IOP_OS

    ++interface->ipv6Stat.inReceives;
    if (flag & (IF_FLAG_BROADCAST | IF_FLAG_MULTICAST))
    {
        ++interface->ipv6Stat.inMcastPkts;
    }

    if (len < sizeof(IP6Hdr))
    {
        ++interface->ipv6Stat.inHdrErrors;
        ++interface->ipv6Stat.inTruncatedPkts;
        return;
    }

    // Check IP version
    if ((ip6->flow >> 28) != 6)
    {
        ++interface->ipv6Stat.inHdrErrors;
        return;
    }

    if (SO_IN6_IS_ADDR_MULTICAST(&ip6->src) || SO_IN6_IS_ADDR_UNSPECIFIED(&ip6->dst))
    {
        ++interface->ipv6Stat.inHdrErrors;
        return;
    }

/*
    // Check destination address
    if (SO_IN6_IS_ADDR_MC_INTFACELOCAL(&ip6->dst) && flags != IF_FLAG_LOOPBACK)
    {
        ++interface->ipv6Stat.inAddrErrors;
        return;
    }
 */

    if (sizeof(IP6Hdr) + ip6->plen < len)
    {
        ++interface->ipv6Stat.inHdrErrors;
        ++interface->ipv6Stat.inTruncatedPkts;
        return;
    }

    hdr = &ip6->next;
    hlen = sizeof(IP6Hdr) - offsetof(IP6Hdr, next);
    next = hdr[0];

    len = hlen + ip6->plen;
    if (next == SO_IPPROTO_HOPOPTS)
    {
        hdr += hlen;
        len -= hlen;
        if (len < 2)
        {
            ++interface->ipv6Stat.inHdrErrors;
            ++interface->ipv6Stat.inTruncatedPkts;
            return;
        }
        hlen = (1 + hdr[1]) << 3;
        if (len < hlen)
        {
            ++interface->ipv6Stat.inHdrErrors;
            ++interface->ipv6Stat.inTruncatedPkts;
            return;
        }

        for (opt = (IP6Opt*) (hdr + 2);
             (u8*) opt < hdr + hlen;
             opt = (IP6Opt*) ((u8*) opt + ((opt->type == IP6OPT_PAD1) ? 1 : 2 + opt->len)))
        {
            if (!CheckOptionType(interface, ip6, flag, opt))
            {
                ++interface->ipv6Stat.inHdrErrors;
                return;
            }

            if (opt->type == IP6OPT_ROUTER_ALERT)
            {
                IP6OptRouter* optRouter = (IP6OptRouter*) opt;

                // There MUST only be one option of this type, regardless of value,
                // per Hop-by-Hop header. [RFC 2711]
                if (optRouter->len != 2 || 0 <= routerAlert)
                {
                    ++interface->ipv6Stat.inHdrErrors;
                    return;
                }
                routerAlert = *(u16*) optRouter->value;     // in network byte order
            }
        }

        next = hdr[0];
    }

    // Deliver the datagram to the destination
    while (next != SO_IPPROTO_NONE)
    {
        switch (next)
        {
          case SO_IPPROTO_HOPOPTS:
            // The Hop-by-Hop Options header, when present, must immediately
            // follow the IPv6 header. [RFC 2460]
            ICMP6SendError(interface, ICMP6_PARAM_PROB,
                           ICMP6_PARAMPROB_NEXTHEADER, ip6, flag,
                           (u32) ((u8*) hdr - (u8*) ip6));
            next = SO_IPPROTO_NONE;
            break;

          case SO_IPPROTO_DSTOPTS:
            hdr += hlen;
            len -= hlen;
            if (len < 2)
            {
                ++interface->ipv6Stat.inHdrErrors;
                ++interface->ipv6Stat.inTruncatedPkts;
                return;
            }
            hlen = (1 + hdr[1]) << 3;
            if (len < hlen)
            {
                ++interface->ipv6Stat.inHdrErrors;
                ++interface->ipv6Stat.inTruncatedPkts;
                return;
            }

            for (opt = (IP6Opt*) (hdr + 2);
                 (u8*) opt < hdr + hlen;
                 opt = (IP6Opt*) ((u8*) opt + ((opt->type == IP6OPT_PAD1) ? 1 : 2 + opt->len)))
            {
                if (!CheckOptionType(interface, ip6, flag, opt))
                {
                    ++interface->ipv6Stat.inHdrErrors;
                    return;
                }
            }

            next = hdr[0];
            break;

          case SO_IPPROTO_FRAGMENT:
            // Reassemble incoming datagram
            hdr += hlen;
            len -= hlen;
            if (len < 2)
            {
                ++interface->ipv6Stat.inHdrErrors;
                ++interface->ipv6Stat.inTruncatedPkts;
                return;
            }
            hlen = (1 + hdr[1]) << 3;
            if (len < hlen)
            {
                ++interface->ipv6Stat.inHdrErrors;
                ++interface->ipv6Stat.inTruncatedPkts;
                return;
            }

            ++interface->ipv6Stat.reasmReqds;
            ip6 = IP6Reassemble(interface, ip6, (IP6Frag*) hdr, flag);
            if (ip6 == NULL)
            {
                return;
            }
            ++interface->ipv6Stat.reasmOKs;
            IP6In(interface, ip6, (s32) (ip6->plen + sizeof(IP6Hdr)), flag);
            // XXX Release reassembly buffer (a hack)
            ip6->flow = 0;
            next = SO_IPPROTO_NONE;
            break;

          case SO_IPPROTO_ROUTING:  // XXX
          // case SO_IPPROTO_AH:
          // case SO_IPPROTO_ESP:
            hdr += hlen;
            len -= hlen;
            if (len < 2)
            {
                ++interface->ipv6Stat.inHdrErrors;
                ++interface->ipv6Stat.inTruncatedPkts;
                return;
            }
            hlen = (1 + hdr[1]) << 3;
            if (len < hlen)
            {
                ++interface->ipv6Stat.inHdrErrors;
                ++interface->ipv6Stat.inTruncatedPkts;
                return;
            }

            next = hdr[0];
            break;

          case SO_IPPROTO_ICMPV6:
            hdr += hlen;
            len -= hlen;
            ++interface->ipv6Stat.inDelivers;
            ICMP6In(interface, ip6, (ICMP6Hdr*) hdr, len, flag, routerAlert);
            next = SO_IPPROTO_NONE;
            break;

          case IP_PROTO_UDP:
            hdr += hlen;
            len -= hlen;
            ++interface->ipv6Stat.inDelivers;
            UDP6In(interface, ip6, (UDPHeader*) hdr, len, flag);
            next = SO_IPPROTO_NONE;
            break;

          case IP_PROTO_TCP:
            hdr += hlen;
            len -= hlen;
            if (flag & (IF_FLAG_BROADCAST | IF_FLAG_MULTICAST))
            {
                // Silently discard seg to bcast/mcast addr
                ++interface->ipv6Stat.inHdrErrors;
                break;
            }
            ++interface->ipv6Stat.inDelivers;
            TCP6In(interface, ip6, (TCPHeader*) hdr, len, flag);
            next = SO_IPPROTO_NONE;
            break;

          default:
            // Discard the packet and send an ICMP Parameter Problem message
            // to the source of the packet, with an ICMP Code value of 1
            // ("unrecognized Next Header type encountered") [RFC 2460]
            ++interface->ipv6Stat.inUnknownProtos;
            ICMP6SendError(interface, ICMP6_PARAM_PROB, ICMP6_PARAMPROB_NEXTHEADER,
                           ip6, flag, (u32) ((u8*) hdr - (u8*) ip6));
            next = SO_IPPROTO_NONE;
            break;
        }
    }
}

IP6Entry* IP6GetNextHop(IPInfo* info, const SOIn6Addr* addr, IP6Entry** destination)
{
    IP6Entry* nextHop;
    IP6Entry* dst;

    nextHop = info->next;
    if (nextHop)
    {
        if ((nextHop->flags & ND_FLAG_IS_ROUTER) && nextHop->routerLifetime < OSGetTime())
        {
            IFDequeueItem(IPInfo*, &nextHop->queueNext, info, linkNext);
            info->next = NULL;
            IP6SwitchToHost(nextHop);
            IP6PutNeighbor(nextHop);
            // Note nextHop may not be exist anymore.
        }
        else
        {
            if (destination)
            {
                *destination = info->to;
            }
            return nextHop;
        }
    }

    if (SO_IN6_IS_ADDR_MULTICAST(addr))
    {
        nextHop = IP6GetNeighbor(NULL, addr);
        if (destination)
        {
            *destination = nextHop;
        }
        return nextHop;
    }

    nextHop = IP6GetNextNeighbor(NULL, addr, &dst);
    if (nextHop)
    {
        if (info->to)
        {
            IP6SetDestination(info, dst);
        }
        if (destination)
        {
            *destination = info->to;
        }
        return nextHop;
    }

    if (destination)
    {
        *destination = NULL;
    }
    return NULL;
}

void IP6SetNextHop(IPInfo* info, IP6Entry* entry)
{
    if (info->next == entry)
    {
        return;
    }
    if (info->next)
    {
        IP6Entry* prev = info->next;
        IFDequeueItem(IPInfo*, &prev->queueNext, info, linkNext);
        IP6PutNeighbor(prev);
    }
    if (entry)
    {
        IP6RefNeighbor(entry);
        IFEnqueueTail(IPInfo*, &entry->queueNext, info, linkNext);
    }
    info->next = entry;
}

void IP6SetSource(IPInfo* info, IP6Entry* entry)
{
    if (info->from == entry)
    {
        return;
    }
    if (info->from)
    {
        IP6Entry* prev = info->from;
        IFDequeueItem(IPInfo*, &prev->queueFrom, info, linkFrom);
        IP6PutNeighbor(prev);
    }
    if (entry)
    {
        IP6RefNeighbor(entry);
        IFEnqueueTail(IPInfo*, &entry->queueFrom, info, linkFrom);
    }
    info->from = entry;
}

void IP6SetDestination(IPInfo* info, IP6Entry* entry)
{
    if (info->to == entry)
    {
        return;
    }
    if (info->to)
    {
        IP6Entry* prev = info->to;
        IFDequeueItem(IPInfo*, &prev->queueTo, info, linkTo);
        IP6PutNeighbor(prev);
    }
    if (entry)
    {
        IP6RefNeighbor(entry);
        IFEnqueueTail(IPInfo*, &entry->queueTo, info, linkTo);
    }
    info->to = entry;
}

/*---------------------------------------------------------------------------*
  Name:         IP6Out

  Description:  Transmits IP datagram

  Arguments:    datagram    Pointer to IFDatagram to send. If the function
                            failed, datagram's callback is not called.

  Returns:      IP_ERR_NONE         Succeeded.
                IP_ERR_UNREACHABLE  No route to the destination.
                IP_ERR_DATASIZE     datagram is too large to be sent.
                IP_ERR_NETDOWN      datagram src address is wrong. Perhaps
                                    due to network configuration change.
 *---------------------------------------------------------------------------*/
s32 IP6Out(IPInterface* interface, IFDatagram* datagram, IP6Entry* neighbor)
{
    IP6Hdr* ip6;

    ++interface->ipv6Stat.outRequests;

    ASSERT(0 < datagram->nVec && datagram->nVec <= IF_MAX_VEC);
    ip6 = (IP6Hdr*) datagram->vec[0].data;
    ASSERT(ip6->flow >> 28 == 6);
    ASSERT(!SO_IN6_ARE_ADDR_EQUAL(&ip6->dst, &SOIn6AddrAny));

    if (SO_IN6_IS_ADDR_MULTICAST(&ip6->dst))
    {
        ++interface->ipv6Stat.outMcastPkts;

        datagram->flag |= IF_FLAG_MULTICAST;

        // XXX The following lines are the Ethernet specific code.
        datagram->hwAddr[0] = 0x33;
        datagram->hwAddr[1] = 0x33;
        datagram->hwAddr[2] = ip6->dst.addr[12];
        datagram->hwAddr[3] = ip6->dst.addr[13];
        datagram->hwAddr[4] = ip6->dst.addr[14];
        datagram->hwAddr[5] = ip6->dst.addr[15];
    }
    else
    {
        if (neighbor == NULL)
        {
            return IP_ERR_UNREACHABLE;
        }

        if ((ND_STATE_TENTATIVE <= neighbor->state && neighbor->state <= ND_STATE_DEPRECATED))
        {
            datagram->flag |= IF_FLAG_LOOPBACK;
        }
        else
        {
            datagram->flag |= IF_FLAG_UNICAST;
        }

        switch (neighbor->state)
        {
          case ND_STATE_INIT:
            // Initiates Address Resolution. Note NDHold() must be called
            // *before* IP6SetNeighborState() to discard any memory blocks
            // allocated from the interface FIFO.
            NDHold(neighbor, datagram);
            IP6SetNeighborState(neighbor, ND_STATE_INCOMPLETE);
            return IP_ERR_NONE;
            // NOT REACHED HERE

          case ND_STATE_INCOMPLETE:
            NDHold(neighbor, datagram);
            return IP_ERR_NONE;
            // NOT REACHED HERE

          case ND_STATE_REACHABLE:
            if (neighbor->validTime <= OSGetTime())
            {
                IP6SetNeighborState(neighbor, ND_STATE_STALE);
            }
            break;
        }
        if (neighbor->state == ND_STATE_STALE)
        {
            IP6SetNeighborState(neighbor, ND_STATE_DELAY);
        }
        // XXX The following line is the Ethernet specific code.
        memmove(datagram->hwAddr, neighbor->linkAddr, ETH_ALEN);
    }

    // Check interface MTU if IP_DF flag is set.
    // if (interface->mtu < ip6->len && (ip6->frag & IP_DF))
    // {
    //     return IP_ERR_DATASIZE;
    // }

    // if (ip6->src[0] != 127 &&
    //     IP_ADDR_NE(interface->addr, ip6->src) &&
    //     IP_ADDR_NE(interface->alias, ip6->src))
    // {
    //     return IP_ERR_NETDOWN;
    // }

    datagram->type = ETH_IPv6;
    interface->out(interface, datagram);

    return IP_ERR_NONE;
}

// Cancel datagram:
//   If info->datagram is in IP/ARP pending queue, it must be
//   removed from the queue before aborting the operation.
void IP6Cancel(IFDatagram* datagram)
{
    IPInterface* interface;

    interface = datagram->interface;
    if (interface)
    {
        interface->cancel(interface, datagram);
        ASSERT(datagram->interface == NULL);
    }
}

SOIn6Addr* IP6GetSolicited(const SOIn6Addr* addr, SOIn6Addr* solicited)
{
    memmove(&solicited->addr[0], &SOIn6AddrSolicited.addr[0], 13);
    memmove(&solicited->addr[13], &addr->addr[13], 3);
    return solicited;
}

BOOL IP6IsSolicited(const SOIn6Addr* addr)
{
    return (memcmp(&addr->addr[0], &SOIn6AddrSolicited.addr[0], 13) == 0) ? TRUE : FALSE;
}

IP6Entry* IP6SelectSourceAddress(IPInterface* interface, const SOIn6Addr* dst, SOIn6Addr* src)
{
    IP6Entry* neighbor;
    IP6Entry* next;
    IP6Entry* linkLocal = interface->linkLocal;
    OSTime    now;

    if (SO_IN6_IS_ADDR_LOOPBACK(dst) || SO_IN6_IS_ADDR_MC_NODELOCAL(dst))
    {
        *src = SOIn6AddrLoopback;
        return NULL;
    }

    if (SO_IN6_IS_ADDR_LINKLOCAL(dst) || SO_IN6_IS_ADDR_MC_LINKLOCAL(dst))
    {
        if (linkLocal && linkLocal->state != ND_STATE_TENTATIVE)
        {
            *src = linkLocal->addr;
            return NULL;
        }
    }

    // Lookup non-linklocal source address
    now = OSGetTime();
    *src = SOIn6AddrAny;
    IFIterateQueue(IP6Entry*, &NDCache, neighbor, next, link)
    {
        if (neighbor->prefixLen <= 0)
        {
            break;
        }

        if (neighbor->interface != interface)
        {
            continue;
        }

        if (SO_IN6_IS_ADDR_LINKLOCAL(&neighbor->addr) || SO_IN6_IS_ADDR_LOOPBACK(&neighbor->addr))
        {
            continue;
        }

        if (neighbor->state == ND_STATE_PREFERRED || neighbor->state == ND_STATE_DEPRECATED)
        {
            if (neighbor->preferredTime <= now)
            {
                IP6SetNeighborState(neighbor, ND_STATE_DEPRECATED);
            }
            if (neighbor->validTime <= now)
            {
                IP6SetNeighborState(neighbor, ND_STATE_INVALID);
                continue;
            }
            *src = neighbor->addr;
            if (neighbor->state == ND_STATE_PREFERRED)
            {
                return neighbor;
            }
        }
    }

    if (linkLocal && linkLocal->state != ND_STATE_TENTATIVE)
    {
        *src = linkLocal->addr;
    }

    return NULL;
}

s32 IP6GetSockOpt(IPInfo* info, int level, int optname,
                  void* optval, int* optlen)
{
    BOOL enabled;
    s32  rc = IP_ERR_INV_OPTION;

    enabled = OSDisableInterrupts();
    if (level == SO_IPPROTO_IPV6 && info->family == SO_PF_INET6)
    {
        switch (optname)
        {
          case SO_IPV6_UNICAST_HOPS:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = info->ttl;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_IPV6_MULTICAST_LOOP:
            if (sizeof(unsigned) <= *optlen)
            {
                *(unsigned*) optval = (unsigned) ((info->flag & IP_INFO_FLAG_MCASTLOOP) ? 1 : 0);
                *optlen = sizeof(unsigned);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_IPV6_MULTICAST_HOPS:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = info->mttl;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 IP6SetSockOpt(IPInfo* info, int level, int optname,
                  const void* optval, int optlen)
{
    BOOL enabled;
    s32  rc = IP_ERR_INV_OPTION;

    enabled = OSDisableInterrupts();
    if (level == SO_IPPROTO_IPV6 && info->family == SO_PF_INET6)
    {
        switch (optname)
        {
          case SO_IPV6_UNICAST_HOPS:
            if (sizeof(int) <= optlen)
            {
                int hoplimit = *(const int*) optval;

                if (hoplimit < -1 || 256 <= hoplimit)
                {
                    rc = IP_ERR_INVALID;
                }
                else
                {
                    if (hoplimit == -1)
                    {
                        hoplimit = 255;
                    }
                    info->ttl = (u8) hoplimit;
                    rc = IP_ERR_NONE;
                }
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_IPV6_MULTICAST_LOOP:
            if (sizeof(unsigned) <= optlen)
            {
                unsigned opt = *(const unsigned*) optval;

                if (opt == 1)
                {
                    info->flag |= IP_INFO_FLAG_MCASTLOOP;
                    rc = IP_ERR_NONE;
                }
                else if (opt == 0)
                {
                    info->flag &= ~IP_INFO_FLAG_MCASTLOOP;
                    rc = IP_ERR_NONE;
                }
                else
                {
                    rc = IP_ERR_INVALID;
                }
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_IPV6_MULTICAST_HOPS:
            if (sizeof(int) <= optlen)
            {
                int hoplimit = *(const int*) optval;

                if (hoplimit < -1 || 256 <= hoplimit)
                {
                    rc = IP_ERR_INVALID;
                }
                else
                {
                    if (hoplimit == -1)
                    {
                        hoplimit = 255;
                    }
                    info->mttl = (u8) hoplimit;
                    rc = IP_ERR_NONE;
                }
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_IPV6_JOIN_GROUP:
            if (sizeof(SOIPv6Mreq) <= optlen)
            {
                const SOIPv6Mreq* mreq = (const SOIPv6Mreq*) optval;
                rc = IP6MulticastLookup(&__IFDefault, &mreq->multiAddr);
                if (0 <= rc)
                {
                    if ((info->flag & IP_INFO_FLAG_MCAST(rc)) == 0)
                    {
                        rc = IP6MulticastJoin(&__IFDefault, &mreq->multiAddr);
                        ASSERT(0 <= rc);
                        info->flag |= IP_INFO_FLAG_MCAST(rc);
                    }
                    rc = IP_ERR_NONE;
                }
                else
                {
                    rc = IP6MulticastJoin(&__IFDefault, &mreq->multiAddr);
                    if (0 <= rc)
                    {
                        info->flag |= IP_INFO_FLAG_MCAST(rc);
                        rc = IP_ERR_NONE;
                    }
                }
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_IPV6_LEAVE_GROUP:
            if (sizeof(SOIPv6Mreq) <= optlen)
            {
                const SOIPv6Mreq* mreq = (const SOIPv6Mreq*) optval;
                rc = IP6MulticastLookup(&__IFDefault, &mreq->multiAddr);
                if (0 <= rc)
                {
                    if (info->flag & IP_INFO_FLAG_MCAST(rc))
                    {
                        rc = IP6MulticastLeave(&__IFDefault, &mreq->multiAddr);
                        ASSERT(0 <= rc);
                        info->flag &= ~IP_INFO_FLAG_MCAST(rc);
                        rc = IP_ERR_NONE;
                    }
                    else
                    {
                        rc = IP_ERR_NOT_EXIST;
                    }
                }
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

#endif  // IP_INET6
