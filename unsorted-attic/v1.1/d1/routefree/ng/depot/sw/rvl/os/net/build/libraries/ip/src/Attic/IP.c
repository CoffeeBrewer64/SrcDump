d1 641
a641 628
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IP.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip6/src/IP.c $
    
    44    1/26/06 11:28 Shiki
    Modified IFInitDatagram() to initialize datagram->mtu.

    43    1/20/06 17:00 Shiki
    Fixed IPGetSockOpt() and IPSetSockOpt().

    42    12/22/05 14:31 Shiki
    Added IPAnvl.

    41    12/13/05 19:51 Shiki
    Modified the return value type of IPSetOption().

    40    12/13/05 19:10 Shiki
    Revised IPGetSockOpt() so that it can handle default TTL (1 for
    link-local, IP_TTL for others).

    39    04/12/21 9:24 Ueno_kyu
    Removed SOIn6AddrSolicited.

    38    04/12/21 9:11 Ueno_kyu
    Moved some constants from IP6.c to IP.c for SN.

    37    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    41    04/10/27 9:20 Ueno_kyu
    Modified IPEnumAddresses() to stop, if the callback returns FALSE.

    40    04/10/01 10:44 Ueno_kyu
    Cleanup.

    39    04/09/28 10:29 Ueno_kyu
    Modified IPEnumAddresses() to enable interrupts, before calling a
    callback.
    Modified IPEnumAddresses() to return an auto-ip address.

    38    04/09/27 17:46 Ueno_kyu
    Added IPEnumAddresses() to get all addresses assigned to an interface.

    37    6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    35    1/26/04 11:26 Shiki
    Modified IPAtoN() to return non-NULL pointer if succeeded.

    34    10/29/03 21:56 Shiki
    Added support for fragmenting outgoing datagrams.
    Implemented IFInitDatagram().

    33    10/22/03 10:47 Shiki
    Modified to get ephemeral port number between 49152 and 65535 rather
    than from between 1024 and. 5000.

    32    9/03/03 9:42 Shiki
    Fixed IPConnect() to check UDP connect operation strictly.

    31    8/21/03 20:58 Shiki
    Added support for SACK/FACK.

    30    5/07/03 11:19 Shiki
    Clean up.

    28    4/01/03 10:19 Shiki
    Modified IP multicast logic so that a socket receives multicast
    datagrams only from the joined group.

    27    3/27/03 17:38 Shiki
    Added support for multicast.

    26    1/22/03 18:05 Shiki
    Fixed IPBind() to support UDP.

    25    12/06/02 10:20 Shiki
    Fixed IPConnect() not to commit connect if TCPInfo is connecting to the
    same destination from the same local socket.

    24    11/15/02 9:44 Shiki
    Fixed not to use macro version of isspace() for SN.

    23    7/29/02 10:24 Shiki
    Implemented Ethernet packet length check code.

    22    7/10/02 17:05 Shiki
    Revised VERBOSE message.

    21    6/14/02 10:32 Shiki
    Revised IPAtoN() to make it compatible with inet_aton().

    20    4/26/02 16:47 Shiki
    Added support for check sum error counters.

    19    4/25/02 9:09 Shiki
    Fixed IPOut() not to filter out loopback datagram.

    18    4/24/02 11:17 Shiki
    Modified IPOut() to check datagram source IP address against possible
    network configuration change..
    Fixed IPIn() so it will accept every IP packet if the interface address
    is not configured and even if the interface alias is configured.

    17    4/23/02 15:12 Shiki
    Added function description for IPOut().

    16    4/18/02 18:33 Shiki
    Revised error code from IPConnect().

    15    4/18/02 9:08 Shiki
    Modified IP[Set|Get]SockOpt() to return IP_ERR_INV_OPTION error for
    unsupported options.

    14    4/12/02 19:16 Shiki
    Modified IPConnect() to reject invalid remote IP address for TCP.

    13    4/12/02 13:33 Shiki
    Modified IPIn() to silently discard TCP segment to bcast/mcast addr.

    12    4/10/02 18:36 Shiki
    Modified IPIn() to silently discard link-layer-only broadcast datagram.

    11    4/08/02 17:45 Shiki
    Fixed IPGetAnonPort() to increment anonymous port number correctly.

    10    4/08/02 13:59 Shiki
    Added IPGetSockOpt() and IPSetSockOpt().
    Revised using new IPSocket{} type.

    9     4/05/02 14:08 Shiki
    Refined using 'const'.

    8     4/04/02 17:24 Shiki
    Enabled call to IPReassemble().

    7     3/27/02 20:18 Shiki
    Revised IPIn() to sync with new IPIsBroadcastAddr() implementation.

    6     3/27/02 17:48 Shiki
    Modified IPIn() to discard datagram with incomplete IP source route
    options.

    5     3/27/02 9:37 Shiki
    Fixed to use the alias address for src address if the interface address
    is not configured.

    4     3/18/02 20:31 Shiki
    Added __IPIsMember().

    3     3/15/02 11:49 Shiki
    Added support for loopback interface.

    2     3/13/02 9:14 Shiki
    Clean up with IP_ALEN and ETH_ALEN.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <dolphin/os.h>
#include <dolphin/ip.h>
#include <dolphin/socket.h>
#include "IPPrivate.h"
#ifdef IP_INET6
#include "IP6Private.h"
#endif // IP_INET6

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// RFC 791

const u8 IPAddrAny[IP_ALEN]      = {   0,   0,   0,   0 };
const u8 IPLoopbackAddr[IP_ALEN] = { 127,   0,   0,   1 };
const u8 IPLinkLocal[IP_ALEN]    = { 169, 254,   0,   0 };
const u8 IPLimited[IP_ALEN]      = { 255, 255, 255, 255 };

const SOIn6Addr SOIn6AddrAny = SO_IN6ADDR_ANY_INIT;
const SOIn6Addr SOIn6AddrLoopback = SO_IN6ADDR_LOOPBACK_INIT;
const SOIn6Addr SOIn6AddrLinkLocalAllNodes = SO_IN6ADDR_LINKLOCAL_ALL_NODES_INIT;
const SOIn6Addr SOIn6AddrLinkLocalAllRouters = SO_IN6ADDR_LINKLOCAL_ALL_ROUTERS_INIT;

static u16 Id = 1;      // IP packet identification

u32 IPAnvl;

//
// Common functions (IPInfo)
//

void* IPGetLocalSockAddr(IPInfo* info)
{
    switch (info->family)
    {
      case SO_PF_INET:
        return (IPSocket*) ((u8*) info + sizeof(IPInfo));
#ifdef IP_INET6
      case SO_PF_INET6:
        return (SOSockAddrIn6*) ((u8*) info + sizeof(IPInfo));
#endif  // IP_INET6
      default:
        return NULL;
    }
}

void* IPGetRemoteSockAddr(IPInfo* info)
{
    switch (info->family)
    {
      case SO_PF_INET:
        return (IPSocket*) ((u8*) info + sizeof(IPInfo) + sizeof(IPSocket));
#ifdef IP_INET6
      case SO_PF_INET6:
        return (SOSockAddrIn6*) ((u8*) info + sizeof(IPInfo) + sizeof(SOSockAddrIn6));
#endif  // IP_INET6
      default:
        return NULL;
    }
}

// getsockname
s32 IPGetLocalSocket(IPInfo* info, void* sockAddr)
{
    SOSockAddr* local = IPGetLocalSockAddr(info);
    int         len;

    ASSERT(local);
#ifndef IP_INET6
    ASSERT(local->family == SO_PF_INET);
    ASSERT(local->family != SO_PF_INET || sizeof(SOSockAddrIn) <= local->len);
#else
    ASSERT(local->family == SO_PF_INET || local->family == SO_PF_INET6);
    ASSERT(local->family != SO_PF_INET || sizeof(SOSockAddrIn) <= local->len);
    ASSERT(local->family != SO_PF_INET6 || sizeof(SOSockAddrIn6) <= local->len);
#endif
    len = MIN(local->len, ((SOSockAddr*) sockAddr)->len);
    memmove(sockAddr, local, (size_t) len);
    return IP_ERR_NONE;
}

// getpeername
s32 IPGetRemoteSocket(IPInfo* info, void* sockAddr)
{
    SOSockAddr* remote = IPGetRemoteSockAddr(info);
    int         len;

    ASSERT(remote);
#ifndef IP_INET6
    ASSERT(remote->family == SO_PF_INET);
    ASSERT(remote->family != SO_PF_INET || sizeof(SOSockAddrIn) <= remote->len);
#else
    ASSERT(remote->family == SO_PF_INET || remote->family == SO_PF_INET6);
    ASSERT(remote->family != SO_PF_INET || sizeof(SOSockAddrIn) <= remote->len);
    ASSERT(remote->family != SO_PF_INET6 || sizeof(SOSockAddrIn6) <= remote->len);
#endif
    len = MIN(remote->len, ((SOSockAddr*) sockAddr)->len);
    memmove(sockAddr, remote, (size_t) len);
    return IP_ERR_NONE;
}

/*---------------------------------------------------------------------------*
  Name:         __IPIsMember

  Description:  Test if info is inserted in the queue

  Arguments:    queue   Queue of IPInfo
                info    info to test

  Returns:      TRUE if info is inserted in the queue. Otherwise, FALSE.
 *---------------------------------------------------------------------------*/
BOOL __IPIsMember(IFQueue* queue, IPInfo* info)
{
    IPInfo* iter;
    IPInfo* next;

    IFIterateQueue(IPInfo*, queue, iter, next, link)
    {
        if (iter == info)
        {
            return TRUE;
        }
    }
    return FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         IPGetAnonPort

  Description:  Get ephemeral port number between 49152 and 65535.

  Arguments:    Queue   Queue of IPInfo
                last    The next ephemeral port number

  Returns:      Returns zero if all numbers have been used up.
 *---------------------------------------------------------------------------*/
u16 IPGetAnonPort(IFQueue* queue, u16* last)
{
    u16       port;
    IPInfo*   info;
    IPInfo*   next;
    int       skip = 0;
    IPSocket* local;

    ASSERT(sizeof(u16) == 2);
    if (*last < 49152)
    {
        *last = 49152;
    }
Skip:
    port = (*last)++;
    if (*last < 49152)
    {
        *last = 49152;
    }
    IFIterateQueue(IPInfo*, queue, info, next, link)
    {
        local = IPGetLocalSockAddr(info);
        if (local->port == port)
        {
            if (65535 - 49152 < ++skip)
            {
                return 0;
            }
            goto Skip;
        }
    }
    return port;
}

s32 IPGetSockOpt(IPInfo* info, int level, int optname,
                 void* optval, int* optlen)
{
    BOOL enabled;
    s32  rc = IP_ERR_INV_OPTION;

    enabled = OSDisableInterrupts();
    if (level == SO_SOL_IP && info->family == SO_PF_INET)
    {
        switch (optname)
        {
          case SO_IP_TOS:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = info->tos;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_IP_TTL:
            if (sizeof(int) <= *optlen)
            {
                if (info->ttl)
                {
                    *(int*) optval = info->ttl;
                }
                else
                {
                    const IPSocket* localSocket = IPGetLocalSockAddr(info);
                    *(int*) optval = (u8) (IPIsLinkLocalAddr(NULL, localSocket->addr) ? 1 : IP_TTL);
                }
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_IP_MULTICAST_LOOP:
            if (sizeof(u8) <= *optlen)
            {
                *(u8*) optval = (u8) ((info->flag & IP_INFO_FLAG_MCASTLOOP) ? 1 : 0);
                *optlen = sizeof(u8);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_IP_MULTICAST_TTL:
            if (sizeof(u8) <= *optlen)
            {
                *(u8*) optval = info->mttl;
                *optlen = sizeof(u8);
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

s32 IPSetSockOpt(IPInfo* info, int level, int optname,
                 const void* optval, int optlen)
{
    BOOL enabled;
    s32  rc = IP_ERR_INV_OPTION;

    enabled = OSDisableInterrupts();
    if (level == SO_SOL_IP && info->family == SO_PF_INET)
    {
        switch (optname)
        {
          case SO_IP_TOS:
            if (sizeof(int) <= optlen)
            {
                info->tos = (u8) MIN(*(const int*) optval, 255);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_IP_TTL:
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
          case SO_IP_MULTICAST_LOOP:
            if (sizeof(u8) <= optlen)
            {
                if (*(const u8*) optval)
                {
                    info->flag |= IP_INFO_FLAG_MCASTLOOP;
                }
                else
                {
                    info->flag &= ~IP_INFO_FLAG_MCASTLOOP;
                }
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_IP_MULTICAST_TTL:
            if (sizeof(u8) <= optlen)
            {
                info->mttl = *(const u8*) optval;
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_IP_ADD_MEMBERSHIP:
            if (sizeof(SOIpMreq) <= optlen)
            {
                const SOIpMreq* mreq = (const SOIpMreq*) optval;
                rc = IPMulticastLookup((u8*) &mreq->multiaddr.addr,
                                       (u8*) &mreq->interface.addr);
                if (0 <= rc)
                {
                    if ((info->flag & IP_INFO_FLAG_MCAST(rc)) == 0)
                    {
                        rc = IPMulticastJoin((u8*) &mreq->multiaddr.addr,
                                             (u8*) &mreq->interface.addr);
                        ASSERT(0 <= rc);
                        info->flag |= IP_INFO_FLAG_MCAST(rc);
                    }
                    rc = IP_ERR_NONE;
                }
                else
                {
                    rc = IPMulticastJoin((u8*) &mreq->multiaddr.addr,
                                         (u8*) &mreq->interface.addr);
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
          case SO_IP_DROP_MEMBERSHIP:
            if (sizeof(SOIpMreq) <= optlen)
            {
                const SOIpMreq* mreq = (const SOIpMreq*) optval;
                rc = IPMulticastLookup((u8*) &mreq->multiaddr.addr,
                                       (u8*) &mreq->interface.addr);
                if (0 <= rc)
                {
                    if (info->flag & IP_INFO_FLAG_MCAST(rc))
                    {
                        rc = IPMulticastLeave((u8*) &mreq->multiaddr.addr,
                                              (u8*) &mreq->interface.addr);
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

// obsolete
s32 IPSetOption(IPInfo* info, u8 ttl, u8 tos)
{
    info->ttl = ttl;
    info->tos = tos;
    return IP_ERR_NONE;
}

void IFInitDatagram(IFDatagram* datagram, u16 type, int nVec)
{
    datagram->interface = NULL;
    datagram->queue = NULL;
    datagram->type = type;
    datagram->offset = 0;
    datagram->prefixLen = 0;
    datagram->mtu = 0;
    datagram->flag = 0;
    datagram->callback = NULL;
    datagram->param = NULL;
    datagram->nVec= nVec;
    memset(datagram->vec, 0, nVec * sizeof(IFVec));
}

void IPEnumAddresses(IPInterface* interface, BOOL (*callback)(int af, const void* addr))
{
    BOOL enabled;
    BOOL ret = FALSE;

    if (interface == NULL)
    {
        interface = &__IFDefault;
    }

    enabled = OSDisableInterrupts();
    if (IP_ADDR_NE(interface->addr, IPAddrAny))
    {
        u8   addr[IP_ALEN];

        memmove(addr, interface->addr, IP_ALEN);
        OSRestoreInterrupts(enabled);
        ret = callback(SO_PF_INET, addr);
        if (ret == FALSE)
        {
            return;
        }
        enabled = OSDisableInterrupts();
    }

    if (IP_ADDR_NE(interface->alias, IPAddrAny))
    {
        u8   addr[IP_ALEN];

        memmove(addr, interface->alias, IP_ALEN);
        OSRestoreInterrupts(enabled);
        ret = callback(SO_PF_INET, addr);
        if (ret == FALSE)
        {
            return;
        }
        enabled = OSDisableInterrupts();
    }
    OSRestoreInterrupts(enabled);
#ifdef IP_INET6
    IP6EnumAddresses(interface, callback);
#else
    if (ret == FALSE)
    {
        callback(SO_AF_UNSPEC, NULL);
    }
#endif // IP_INET6
}
