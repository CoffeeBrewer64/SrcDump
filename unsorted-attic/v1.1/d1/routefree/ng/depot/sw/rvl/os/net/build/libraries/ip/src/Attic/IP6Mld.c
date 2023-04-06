d1 409
a409 388
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API - Multicast Listener Discovery (MLD) for IPv6
  File:     IP6Mld.c
  RFC:      2710

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip/src/IP6Mld.c $
    
    16    3/06/06 16:07 Shiki
    Enabled IPv6 by default by globally defining IP_INET6.

    15    3/02/06 9:50 Shiki
    Fixed MLDDoListenerQuery() to handle zero mld->maxDelay.

    14    2/28/06 9:07 Shiki
    Revised using modified IP6Entry{}.

    13    2/01/06 16:24 Shiki
    Added full support of IPv6 PMTU discovery.
    Supported ND_STATE_NON_LISTENER state.

    12    1/26/06 18:41 Shiki
    Renamed IP6Neighbor to IP6Entry.

    11    1/24/06 9:55 Shiki
    Fixed MLDDoListenerQuery().

    10    1/20/06 16:19 Shiki
    Revised to handle SOIn6AddrLinkLocalAllNodes, etc. more uniformly.

    9     1/19/06 18:25 Shiki
    Renamed IP6GetNeighbor() to IP6GetNextNeighbor().

    8     1/19/06 17:46 Shiki
    Fixed to send MLD listener done messages during cleanup and before
    reset.

    7     1/18/06 18:19 Shiki
    Revised the reference count management of IP6Neighbor{}.

    6     1/13/06 9:48 Shiki
    Added ND_STATE_INIT state.

    5     1/11/06 17:01 Shiki
    Fixed to clean up MLDTable[] from SOCleanup().

    3     04/07/22 8:58 Ueno_kyu
    Modified IP6MulticastJoin() to increase reference count
    in the case of ND_STATE_INVALID.

    2     6/22/04 9:29 Shiki
    Clean up.

    1     6/09/04 15:58 Shiki
    IPv6 pilot implementation
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <stddef.h>
#include <dolphin/os.h>
#include <dolphin/socket.h>
#include <private/eth.h>
#include <private/OSRtc.h>
#include "IPPrivate.h"
#include "IP6Private.h"

IP6Entry* MLDTabel[IGMP_MAXGROUP];
int       MLDCount;

// Program NIC to receive group's packets [RFC 2464]
BOOL IP6JoinLocalGroup(IPInterface* interface, const SOIn6Addr* groupAddr)
{
    u8 mac[ETH_ALEN];

    switch (groupAddr->addr[1] & 0x0f)
    {
      case 0:   // reserved
      case 1:   // interface-local scope
        return TRUE;
        break;
    }

    switch (interface->type)
    {
      case IF_TYPE_AUTO:
      case IF_TYPE_100FULL:
      case IF_TYPE_100HALF:
      case IF_TYPE_10FULL:
      case IF_TYPE_10HALF:
        mac[0] = 0x33;
        mac[1] = 0x33;
        mac[2] = groupAddr->addr[12];
        mac[3] = groupAddr->addr[13];
        mac[4] = groupAddr->addr[14];
        mac[5] = groupAddr->addr[15];
        ETHAddMulticastAddress(mac);
        break;
      default:
        break;
    }
    return TRUE;
}

BOOL IP6LeaveLocalGroup(IPInterface* interface, const SOIn6Addr* groupAddr)
{
    #pragma unused(interface, groupAddr)
    return TRUE;
}

// Send report
static void Timeout(OSAlarm* alarm, OSContext* context)
{
    #pragma unused(context)
    IP6Entry* neighbor;

    neighbor = (IP6Entry*) ((u8*) alarm - offsetof(IP6Entry, alarm));
    ICMP6Out(neighbor, MLD_LISTENER_REPORT, &neighbor->addr);
    neighbor->flags |= ND_FLAG_LAST_HOST;
    IP6SetNeighborState(neighbor, ND_STATE_IDLE_LISTENER);
}

s32 IP6MulticastLookup(IPInterface* interface, const SOIn6Addr* groupAddr)
{
    IP6Entry** slot;
    IP6Entry*  neighbor;

    if (!SO_IN6_IS_ADDR_MULTICAST(groupAddr))
    {
        return IP_ERR_INVALID;
    }

    for (slot = MLDTabel; slot < &MLDTabel[IGMP_MAXGROUP]; ++slot)
    {
        neighbor = *slot;
        if (neighbor &&
            (interface == NULL || neighbor->interface == interface) &&
            SO_IN6_ARE_ADDR_EQUAL(&neighbor->addr, groupAddr))
        {
            return slot - MLDTabel;
        }
    }

    return IP_ERR_NOT_EXIST;
}

s32 IP6MulticastJoin(IPInterface* interface, const SOIn6Addr* groupAddr)
{
    IP6Entry*  neighbor;
    IP6Entry** slot;

    if (!SO_IN6_IS_ADDR_MULTICAST(groupAddr))
    {
        return IP_ERR_INVALID;
    }

    neighbor = IP6GetNextNeighbor(interface, groupAddr, NULL);
    if (neighbor == NULL)
    {
        return IP_ERR_INS_RESOURCES;
    }

    switch (neighbor->state)
    {
      case ND_STATE_NON_LISTENER:
        if (IGMP_MAXGROUP <= MLDCount)
        {
            return IP_ERR_INS_RESOURCES;
        }
        ++MLDCount;

        IP6JoinLocalGroup(interface, groupAddr);

        switch (groupAddr->addr[1] & 0x0f)
        {
          case 0:   // reserved
          case 1:   // interface-local scope
            neighbor->flags &= ~ND_FLAG_LAST_HOST;
            IP6SetNeighborState(neighbor, ND_STATE_IDLE_LISTENER);
            break;
          case 2:
            if (SO_IN6_ARE_ADDR_EQUAL(groupAddr, &SOIn6AddrLinkLocalAllNodes))
            {
                neighbor->flags &= ~ND_FLAG_LAST_HOST;
                IP6SetNeighborState(neighbor, ND_STATE_IDLE_LISTENER);
                break;
            }
            // FALL THROUGH
          default:
            IP6SetNeighborState(neighbor, ND_STATE_DELAYING_LISTENER);

            // Immediately transmit a report
            ICMP6Out(neighbor, MLD_LISTENER_REPORT, &neighbor->addr);
            neighbor->flags |= ND_FLAG_LAST_HOST;

            // Repeat after Unsolicited Report Interval
            OSSetAlarm(&neighbor->alarm, OSSecondsToTicks(10), Timeout);
            break;
        }

        for (slot = MLDTabel; slot < &MLDTabel[IGMP_MAXGROUP]; ++slot)
        {
            if (*slot == NULL)
            {
                *slot = neighbor;
                break;
            }
        }
        return slot - MLDTabel;

        break;

      case ND_STATE_DELAYING_LISTENER:
      case ND_STATE_IDLE_LISTENER:
        IP6RefNeighbor(neighbor);
        for (slot = MLDTabel; slot < &MLDTabel[IGMP_MAXGROUP]; ++slot)
        {
            if (*slot == neighbor)
            {
                break;
            }
        }
        ASSERT(slot < &MLDTabel[IGMP_MAXGROUP]);
        return slot - MLDTabel;
        break;

      default:
        OSHalt("ip6.a: IP6MulticastJoin: inv. state\n");
        break;
    }

    return IP_ERR_INVALID;
}

s32 IP6MulticastLeave(IPInterface* interface, const SOIn6Addr* groupAddr)
{
    #pragma unused( interface )
    IP6Entry*  neighbor;
    IP6Entry** slot;

    if (!SO_IN6_IS_ADDR_MULTICAST(groupAddr))
    {
        return IP_ERR_INVALID;
    }

    for (slot = MLDTabel; slot < &MLDTabel[IGMP_MAXGROUP]; ++slot)
    {
        neighbor = *slot;
        if (SO_IN6_ARE_ADDR_EQUAL(&neighbor->addr, groupAddr))
        {
            break;
        }
    }
    if (&MLDTabel[IGMP_MAXGROUP] <= slot)
    {
        return IP_ERR_NOT_EXIST;
    }

    if (neighbor->ref == 1)
    {
        if (neighbor->flags & ND_FLAG_LAST_HOST)
        {
            // Send done
            ICMP6Out(neighbor, MLD_LISTENER_REDUCTION, &neighbor->addr);
        }
        IP6SetNeighborState(neighbor, ND_STATE_INVALID);
        --MLDCount;
        *slot = NULL;

        IP6LeaveLocalGroup(interface, groupAddr);
    }
    IP6PutNeighbor(neighbor);

    return slot - MLDTabel;
}

void MLDDoListenerQuery(IPInterface* interface, ICMP6MldHder* mld)
{
    IP6Entry* neighbor;
    IP6Entry* next;
    OSTime    wait;

    IFIterateQueue(IP6Entry*, &NDCache, neighbor, next, link)
    {
        switch (neighbor->state)
        {
          case ND_STATE_DELAYING_LISTENER:
          case ND_STATE_IDLE_LISTENER:
            ASSERT(SO_IN6_IS_ADDR_MULTICAST(&neighbor->addr));
            if (SO_IN6_IS_ADDR_UNSPECIFIED(&mld->addr) ||           // General Query, or
                SO_IN6_ARE_ADDR_EQUAL(&mld->addr, &neighbor->addr)) // Multicast-Address-Specific Query
            {
                switch (neighbor->addr.addr[1] & 0x0f)
                {
                  case 0:   // reserved
                  case 1:   // interface-local scope
                    break;
                  case 2:
                    if (SO_IN6_ARE_ADDR_EQUAL(&neighbor->addr, &SOIn6AddrLinkLocalAllNodes))
                    {
                        break;
                    }
                    // FALL THROUGH
                  default:
                    if (mld->maxDelay == 0)
                    {
                        OSCancelAlarm(&neighbor->alarm);
                        IP6SetNeighborState(neighbor, ND_STATE_DELAYING_LISTENER);
                        Timeout(&neighbor->alarm, NULL);
                    }
                    else
                    {
                        wait = IPRandTime(interface, 0, OSMillisecondsToTicks((OSTime) mld->maxDelay));
                        if (neighbor->alarm.handler == NULL)
                        {
                            OSSetAlarm(&neighbor->alarm, wait, Timeout);
                        }
                        else if (__OSGetSystemTime() + wait < neighbor->alarm.fire)
                        {
                            OSCancelAlarm(&neighbor->alarm);
                            OSSetAlarm(&neighbor->alarm, wait, Timeout);
                        }
                        IP6SetNeighborState(neighbor, ND_STATE_DELAYING_LISTENER);
                    }
                    break;
                }
            }
            break;
        }
    }
}

void MLDDoListenerReport(IPInterface* interface, ICMP6MldHder* mld)
{
    IP6Entry* neighbor;
    IP6Entry* next;

    #pragma unused( interface )
    IFIterateQueue(IP6Entry*, &NDCache, neighbor, next, link)
    {
        switch (neighbor->state)
        {
          case ND_STATE_DELAYING_LISTENER:
            ASSERT(SO_IN6_IS_ADDR_MULTICAST(&neighbor->addr));
            if (SO_IN6_ARE_ADDR_EQUAL(&mld->addr, &neighbor->addr))    // Multicast-Address-Specific Query
            {
                OSCancelAlarm(&neighbor->alarm);
                neighbor->flags &= ~ND_FLAG_LAST_HOST;
                IP6SetNeighborState(neighbor, ND_STATE_IDLE_LISTENER);
            }
            break;
        }
    }
}

BOOL MLDOnReset(BOOL final)
{
    IP6Entry*  neighbor;
    IP6Entry** slot;

    if (final || MLDCount == 0)
    {
        return TRUE;
    }
    for (slot = MLDTabel; slot < &MLDTabel[IGMP_MAXGROUP]; ++slot)
    {
        neighbor = *slot;
        if (!neighbor)
        {
            continue;
        }
        if (neighbor->flags & ND_FLAG_LAST_HOST)
        {
            // Send done
            ICMP6Out(neighbor, MLD_LISTENER_REDUCTION, &neighbor->addr);
        }
        IP6SetNeighborState(neighbor, ND_STATE_INVALID);
        --MLDCount;
        *slot = NULL;
    }
    return TRUE;
}
