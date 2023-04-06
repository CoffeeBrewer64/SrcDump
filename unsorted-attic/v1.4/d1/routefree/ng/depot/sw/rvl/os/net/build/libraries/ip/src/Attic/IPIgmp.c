/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API - Internet Group Management Protocol (IGMP)
  File:     IPIgmp.c

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPIgmp.c,v $
  Revision 1.3  2006/04/11 01:40:35  mxu
  update to Nintendo's April 05 release

  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    17    4/05/06 9:08 Shiki
    Modified IPClose().

    16    2/01/06 16:24 Shiki
    Added full support of IPv6 PMTU discovery.

    15    1/26/06 18:41 Shiki
    Renamed IP6Neighbor to IP6Entry.

    14    1/12/06 15:59 Shiki
    Fixed IPClose() so that it doesn't break IPv4 only stack.

    13    1/11/06 17:01 Shiki
    Fixed to clean up MLDTable[] from SOCleanup().

    12    05/12/22 11:07 Ueno_kyu
    Added IGMPLeaveV1Mode().

    11    12/02/05 9:30 Shiki
    Revised not to send Leave if not the last host in the group.

    10    12/01/05 18:49 Shiki
    Fixed IGMPIn() to set interface->igmpv1 correctly.

    9     12/01/05 18:46 Shiki
    Fixed IPMulticastJoin() to wait IGMP_UNSOLICITED_REPORT_INTERVAL.

    8     12/01/05 17:52 Shiki
    Added support for IGMPv2.

    7     04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    9     04/10/21 16:59 Ueno_kyu
    Enclosed IPv6 specific codes in #ifdef IP_INET6... #endif blocks.

    8     6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    6     10/29/03 21:58 Shiki
    Revised using IFInitDatagram().

    5     10/16/03 11:52 Shiki
    Fixed IGMPOnReset() not to voluntarily clear host group table as it is
    done by each UDP close on reset.

    4     5/15/03 15:54 Shiki
    Modified to clear the IF_DATAGRAM_FLAG_DROP bit in IFDatagram.flag
    before sending a Ethernet packet.

    3     5/03/03 13:07 Shiki
    Clean up.

    2     4/01/03 10:19 Shiki
    Modified IP multicast logic so that a socket receives multicast
    datagrams only from the joined group.

    1     3/27/03 17:27 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifdef IOP_OS
#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#else
#include <stdio.h>
#endif // IOP_OS
#include <stddef.h>

#include <dolphin/os.h>
#include <dolphin/socket.h>
#include <private/eth.h>
#include "IPPrivate.h"
#ifdef IP_INET6
#include "IP6Private.h"
#endif // IP_INET6

const u8 IPAllHosts[IP_ALEN] = { 224, 0, 0, 1 };
const u8 IPAllRouters[IP_ALEN] = { 224, 0, 0, 2 };

static IGMPInfo IgmpTable[IGMP_MAXGROUP];

// Program NIC to receive group's packets
BOOL IPJoinLocalGroup(IPInterface* interface, const u8* groupAddr)
{
    u8 mac[ETH_ALEN];

    switch (interface->type)
    {
      case IF_TYPE_AUTO:
      case IF_TYPE_100FULL:
      case IF_TYPE_100HALF:
      case IF_TYPE_10FULL:
      case IF_TYPE_10HALF:
        mac[0] = 0x01;
        mac[1] = 0x00;
        mac[2] = 0x5e;
        mac[3] = (u8) (groupAddr[1] & 0x7f);
        mac[4] = groupAddr[2];
        mac[5] = groupAddr[3];
        ETHAddMulticastAddress(mac);
        break;
      default:
        break;
    }
    return TRUE;
}

BOOL IPLeaveLocalGroup(IPInterface* interface, const u8* groupAddr)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
    TCPIP_UNUSED(groupAddr);
#else
    #pragma unused(interface, groupAddr)
#endif // IOP_OS

    return TRUE;
}

static OSTime GetRandomValue(u8* addr, u8 maxRespTime)
{
    OSTime tick;

    tick = OSGetTime();
    tick ^= *(u32*) addr;
    tick = OSMicrosecondsToTicks(tick);
    tick ^= *(u32*) addr;
    tick %= OSMillisecondsToTicks(maxRespTime * 100LL);
    return (0 <= tick) ? tick : -tick;
}

IGMPInfo* IGMPLookupInfo(u8* groupAddr)
{
    IGMPInfo* info;

    if (IP_ADDR_EQ(groupAddr, IPAddrAny))
    {
        return NULL;
    }

    for (info = IgmpTable; info < &IgmpTable[IGMP_MAXGROUP]; ++info)
    {
        if (IP_ADDR_EQ(groupAddr, info->addr))
        {
            return info;
        }
    }
    return NULL;
}

static void IGMPOut(int op, u8* addr)
{
    IPInterface* interface = &__IFDefault;   // XXX
    IPHeader*    ip;
    IGMP*        igmp;
    IFDatagram*  datagram;
    IGMPInfo*    info;

    info = IGMPLookupInfo(addr);
    if (info == NULL)
    {
        return;
    }

    datagram = interface->alloc(interface,
                                (s32) (sizeof(IFDatagram) + IP_MIN_HLEN + IGMP_LEN));
    if (datagram == NULL)
    {
        return;
    }
    IFInitDatagram(datagram, ETH_IP, 1);

    ip = (IPHeader*) ((u8*) datagram + sizeof(IFDatagram));
    igmp = (IGMP*) ((u8*) ip + IP_MIN_HLEN);

    // Assemble packet header
    ip->verlen = IP_VERHLEN;
    ip->tos = 0;
    ip->len = (u16) (IP_HLEN(ip) + IGMP_LEN);
    ip->ttl = 1;
    ip->proto = IP_PROTO_IGMP;
    ip->frag = 0;   // no fragment

    switch (IGMPVersion(interface))
    {
    case 1: // RFC 1112 (IGMPv1)
        igmp->maxRespTime = 0;
        switch (op)
        {
          case IGMP_OP_QUERY:
            igmp->type = IGMP_TYPE_QUERY;
            memmove(igmp->addr, IPAddrAny, IP_ALEN);
            memmove(ip->dst, IPAllHosts, IP_ALEN);
            break;
          case IGMP_OP_REPORT:
            info->flag |= IGMP_FLAG_LAST;
            igmp->type = IGMP_TYPE_REPORT_V1;
            memmove(igmp->addr, addr, IP_ALEN);
            memmove(ip->dst, addr, IP_ALEN);
            break;
          default:
            goto OnError;
        }
        break;
    case 2: // RFC 2236 (IGMPv2)
        switch (op)
        {
          case IGMP_OP_QUERY:
            igmp->type = IGMP_TYPE_QUERY;
            igmp->maxRespTime = IGMP_QUERY_RESPONSE_INTERVAL;
            memmove(igmp->addr, IPAddrAny, IP_ALEN);
            memmove(ip->dst, IPAllHosts, IP_ALEN);
            break;
          case IGMP_OP_REPORT:
            info->flag |= IGMP_FLAG_LAST;
            igmp->type = IGMP_TYPE_REPORT_V2;
            igmp->maxRespTime = 0;
            memmove(igmp->addr, addr, IP_ALEN);
            memmove(ip->dst, addr, IP_ALEN);
            break;
          case IGMP_OP_LEAVE:
            igmp->type = IGMP_TYPE_LEAVE;
            igmp->maxRespTime = 0;
            memmove(igmp->addr, addr, IP_ALEN);
            memmove(ip->dst, IPAllRouters, IP_ALEN);
            break;
          default:
            goto OnError;
        }
        break;
    default:
        OSHalt("Inv. IGMPVersion().");
        break;
    }

    // Select the source address [SHOULD avoid using interface but IPConnect is slow...]
    if (IP_ADDR_NE(info->interface, IPAddrAny))
    {
        memmove(ip->src, info->interface, IP_ALEN);
    }
    else if (IP_ADDR_EQ(interface->addr, IPAddrAny))
    {
        memmove(ip->src, interface->alias, IP_ALEN);
    }
    else
    {
        memmove(ip->src, interface->addr, IP_ALEN);
    }

    datagram->vec[0].data = ip;
    datagram->vec[0].len  = IP_HLEN(ip) + IGMP_LEN;

    if (0 <= IPOut(datagram))
    {
        return;
    }

OnError:
    // datagram has not been sent out. Must release memory
    interface->free(interface, datagram,
                    (s32) (sizeof(IFDatagram) + IP_MIN_HLEN + IGMP_LEN));
}

// Send report
static void Timeout(OSAlarm* alarm, OSContext* context)
{
#ifdef IOP_OS
    TCPIP_UNUSED(context);
#else
    #pragma unused(context)
#endif // IOP_OS

    IGMPInfo* info;

    info = (IGMPInfo*) ((u8*) alarm - offsetof(IGMPInfo, alarm));
    IGMPOut(IGMP_OP_REPORT, info->addr);
}

void IGMPIn(IPInterface* interface, IPHeader* ip, u32 flag)
{
#ifdef IOP_OS
    TCPIP_UNUSED(flag);
#else
    #pragma unused(flag)
#endif // IOP_OS

    IGMPInfo* info;
    IGMP*     igmp;
    IFVec     vec;

    igmp = (IGMP*) ((u8*) ip + IP_HLEN(ip));
    if (ip->len < IP_HLEN(ip) + IGMP_LEN)
    {
        return;
    }

    if (ip->ttl != 1)
    {
        return;
    }

    // Reject loopback
    if (IP_ADDR_EQ(ip->src, interface->addr) ||
        IP_ADDR_EQ(ip->src, interface->alias))
    {
        return;
    }

    // Verify checksum
    vec.data = ip;
    vec.len  = ip->len;
    if (IP4CheckSum(IP_PROTO_IGMP, &vec, 1) != 0)
    {
        return;
    }

    if (IP_ADDR_EQ(igmp->addr, IPAllHosts))
    {
        return;
    }

    switch (igmp->type)
    {
    case IGMP_TYPE_QUERY:
#ifdef VERBOSE
        OSReport("igmp query %u\n", igmp->maxRespTime);
#endif
        if (0 < igmp->maxRespTime)
        {
            interface->igmpMaxRespTime = igmp->maxRespTime;
        }
        else
        {
            interface->igmpMaxRespTime = IGMP_QUERY_RESPONSE_INTERVAL;
            interface->igmpv1 = __OSGetSystemTime();
        }
        for (info = IgmpTable; info < &IgmpTable[IGMP_MAXGROUP]; ++info)
        {
            if (IP_ADDR_NE(info->addr, IPAddrAny) &&
                (IP_ADDR_EQ(igmp->addr, IPAddrAny) || IP_ADDR_EQ(igmp->addr, info->addr)))
            {
                // info is being queried.
                if (__OSGetSystemTime() + OSMillisecondsToTicks(interface->igmpMaxRespTime * 100LL) <=
                    info->alarm.fire)
                {
                    // Reset delay timer
                    OSCancelAlarm(&info->alarm);
                }
                if (info->alarm.handler == NULL)
                {
                    // Set randomly chosen delay timer
                    OSSetAlarm(&info->alarm, GetRandomValue(info->addr, interface->igmpMaxRespTime),
                               Timeout);
                }
            }
        }
        break;
    case IGMP_TYPE_REPORT_V1:
    case IGMP_TYPE_REPORT_V2:
#ifdef VERBOSE
        OSReport("igmp report %d.%d.%d.%d\n",
                 igmp->addr[0], igmp->addr[1], igmp->addr[2], igmp->addr[3]);
#endif
        info = IGMPLookupInfo(igmp->addr);
        if (info && IP_ADDR_EQ(ip->dst, info->addr))
        {
            // Stop timer
            OSCancelAlarm(&info->alarm);
            info->flag &= ~IGMP_FLAG_LAST;
        }
        break;
    case IGMP_TYPE_LEAVE:
#ifdef VERBOSE
        OSReport("igmp leave %d.%d.%d.%d\n",
                 igmp->addr[0], igmp->addr[1], igmp->addr[2], igmp->addr[3]);
#endif
        break;
    default:
        // Ignore silently
        return;
    }
}

void IGMPInit(IPInterface* interface)
{
    interface->igmpv1 = __OSGetSystemTime() - OSSecondsToTicks((OSTime) IGMP_V1_ROUTER_PRESENT_TIMEOUT);
    interface->igmpMaxRespTime = IGMP_QUERY_RESPONSE_INTERVAL;
    IPJoinLocalGroup(interface, IPAllHosts);
}

int IGMPVersion(IPInterface* interface)
{
    BOOL enabled;
    int  version = IGMP_VERSION;

    enabled = OSDisableInterrupts();
    if (__OSGetSystemTime() <
        interface->igmpv1 + OSSecondsToTicks((OSTime) IGMP_V1_ROUTER_PRESENT_TIMEOUT))
    {
        version = 1;
    }
    OSRestoreInterrupts(enabled);
    return version;
}

/*---------------------------------------------------------------------------*
  Name:         IGMPOnReset

  Description:  Reset function for OSResetSystem()

  Arguments:    final       TRUE if OSResetSystem() is about to reset
                            the system

  Returns:      TRUE if IGMP subsystem is ready to reset.
 *---------------------------------------------------------------------------*/
BOOL IGMPOnReset(BOOL final)
{
    IGMPInfo* info;

    if (final)
    {
        for (info = IgmpTable; info < &IgmpTable[IGMP_MAXGROUP]; ++info)
        {
            ASSERT(memcmp(info->addr, IPAddrAny, IP_ALEN) == 0);
        }
    }
    return TRUE;
}

s32 IPMulticastLookup(const u8* groupAddr, const u8* interface)
{
    IGMPInfo*    info;
#ifndef IOP_OS
    IPInterface* nic = &__IFDefault;   // XXX
#endif // IOP_OS

    if (!IP_CLASSD(groupAddr))
    {
        return IP_ERR_INVALID;
    }

    if (IP_ADDR_EQ(groupAddr, IPAllHosts))
    {
        return IGMP_MAXGROUP;
    }

    for (info = IgmpTable; info < &IgmpTable[IGMP_MAXGROUP]; ++info)
    {
        if (IP_ADDR_EQ(info->addr, groupAddr) &&
            IP_ADDR_EQ(info->interface, interface))
        {
            return info - IgmpTable;
        }
    }

    return IP_ERR_NOT_EXIST;
}

s32 IPMulticastJoin(const u8* groupAddr, const u8* interface)
{
    IGMPInfo*    info;
    IGMPInfo*    free = NULL;
    IPInterface* nic = &__IFDefault;   // XXX

    if (!IP_CLASSD(groupAddr))
    {
        return IP_ERR_INVALID;
    }

    if (IP_ADDR_NE(interface, IPAddrAny) &&
        IP_ADDR_NE(interface, nic->addr) &&
        IP_ADDR_NE(interface, nic->alias))
    {
        return IP_ERR_INVALID;
    }

    if (IP_ADDR_EQ(groupAddr, IPAllHosts))
    {
        return IGMP_MAXGROUP;
    }

    for (info = IgmpTable; info < &IgmpTable[IGMP_MAXGROUP]; ++info)
    {
        if (IP_ADDR_EQ(info->addr, groupAddr) &&
            IP_ADDR_EQ(info->interface, interface))
        {
            ++info->ref;
            return info - IgmpTable;
        }

        if (free == NULL && IP_ADDR_EQ(info->addr, IPAddrAny))
        {
            free = info;
        }
    }

    if (free == NULL)
    {
        return IP_ERR_INS_RESOURCES;
    }

    info = free;
    memmove(info->addr, groupAddr, IP_ALEN);
    memmove(info->interface, interface, IP_ALEN);
    OSCreateAlarm(&info->alarm);
    info->ref = 1;
    info->flag = 0;

    IPJoinLocalGroup(nic, groupAddr);

    // Immediately transmit a report
    IGMPOut(IGMP_OP_REPORT, info->addr);

    // Repeat once after a short delay.
    OSSetAlarm(&info->alarm, OSSecondsToTicks(IGMP_UNSOLICITED_REPORT_INTERVAL),
               Timeout);

    return info - IgmpTable;
}

s32 IPMulticastLeave(const u8* groupAddr, const u8* interface)
{
    IGMPInfo* info;

    if (!IP_CLASSD(groupAddr))
    {
        return IP_ERR_INVALID;
    }

    if (IP_ADDR_EQ(groupAddr, IPAllHosts))
    {
        return IGMP_MAXGROUP;
    }

    for (info = IgmpTable; info < &IgmpTable[IGMP_MAXGROUP]; ++info)
    {
        if (IP_ADDR_EQ(info->addr, groupAddr) &&
            IP_ADDR_EQ(info->interface, interface))
        {
            --info->ref;
            if (info->ref <= 0)
            {
                // Stop timer
                OSCancelAlarm(&info->alarm);

                // Host MAY always send a Leave Group message.
                if (info->flag & IGMP_FLAG_LAST)
                {
                    IGMPOut(IGMP_OP_LEAVE, info->addr);
                }

                // Clear entry
                memmove(info->addr, IPAddrAny, IP_ALEN);
            }
            return info - IgmpTable;
        }
    }

    return IP_ERR_NOT_EXIST;
}

s32 IPClose(IPInfo* info)
{
    int       n;
    s32       rc;
    IGMPInfo* igmpInfo;
#ifdef IP_INET6
    IP6Entry* neighbor;
#endif  // IP_INET6

    for (n = 0; n < IGMP_MAXGROUP; ++n)
    {
        if (info->flag & IP_INFO_FLAG_MCAST(n))
        {
            switch (info->family)
            {
              case SO_PF_INET:
                igmpInfo = &IgmpTable[n];
                rc = IPMulticastLeave(igmpInfo->addr, igmpInfo->interface);
                ASSERT(n == rc);
                break;
#ifdef IP_INET6
              case SO_PF_INET6:
                neighbor = MLDTabel[n];
                ASSERT(neighbor);
                if (neighbor)
                {
                    rc = IP6MulticastLeave(neighbor->interface, &neighbor->addr);
                    ASSERT(n == rc);
                }
                break;
#endif  // IP_INET6
            }
            info->flag &= ~IP_INFO_FLAG_MCAST(n);
        }
    }

#ifdef IP_INET6
    if (info->family == SO_PF_INET6)
    {
        IP6SetNextHop(info, NULL);
        IP6SetSource(info, NULL);
        IP6SetDestination(info, NULL);
    }
#endif  // IP_INET6

    return IP_ERR_NONE;
}

void IGMPLeaveV1Mode(IPInterface* interface)
{
    interface->igmpv1 = __OSGetSystemTime() - OSSecondsToTicks((OSTime) IGMP_V1_ROUTER_PRESENT_TIMEOUT);
}
