d1 222
a222 214
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API - IPv6 Stateless Address Autoconfiguration
  File:     IP6Zero.c
  RFC:      2462

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip/src/IP6Zero.c $
    
    15    3/06/06 16:07 Shiki
    Enabled IPv6 by default by globally defining IP_INET6.

    14    2/28/06 14:16 Shiki
    Modified IP6Claim().

    13    2/22/06 15:51 Shiki
    Fixed IP6Claim() not to perform DAD for the loopback address.

    12    2/22/06 9:25 Shiki
    Fixed IP6Claim().

    11    1/26/06 18:41 Shiki
    Renamed IP6Neighbor to IP6Entry.

    10    1/20/06 16:07 Shiki
    Fixed IP6Claim().

    9     1/19/06 18:38 Shiki
    Fixed IP6Claim() to get neighbor by using IP6GetNeighbor() not
    IP6GetNextNeighbor().

    8     1/19/06 18:25 Shiki
    Renamed IP6GetNeighbor() to IP6GetNextNeighbor().

    7     1/13/06 9:48 Shiki
    Added ND_STATE_INIT state.

    5     10/12/04 18:26 Shiki
    Revised IP6Claim().

    4     04/09/28 14:54 Ueno_kyu
    Cleanup.

    3     04/09/22 8:48 Ueno_kyu
    Fixed conditions to update lifetimes in ClaimHandler().

    2     04/09/15 13:49 Ueno_kyu
    Modified IP6Claim() to update stored lifetimes of an address.

    1     6/09/04 15:58 Shiki
    IPv6 pilot implementation
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <stddef.h>
#include <dolphin/os.h>
#include <dolphin/socket.h>
#include "IPPrivate.h"
#include "IP6Private.h"

OSTime NDTime(OSTime now, u32 sec)
{
    if (sec == 0xffffffffu)
    {
        return OS_TIME_INFINITE;
    }
    else
    {
        return now + OSSecondsToTicks((OSTime) sec);
    }
}

static void ClaimHandler(OSAlarm* alarm, OSContext* context)
{
    #pragma unused(context)
    IP6Entry*    neighbor;
    IPInterface* interface;
    SOIn6Addr    solicited;

    neighbor = (IP6Entry*) ((u8*) alarm - offsetof(IP6Entry, alarm));
    interface = neighbor->interface;
    ++neighbor->count;
    if (neighbor->count <= interface->dupAddrDetectTransmits)
    {
        ICMP6Out(neighbor, ND_NEIGHBOR_SOLICIT, IP6GetSolicited(&neighbor->addr, &solicited));
        OSSetAlarm(&neighbor->alarm, interface->retransTimer, ClaimHandler);
    }
    else
    {
        IP6SetNeighborState(neighbor, ND_STATE_PREFERRED);
    }
}

// Duplicate Address Detection
s32 IP6Claim(IPInterface* interface, const SOIn6Addr* addr,
             u32 validTime, u32 preferredTime, u32 flags)
{
    BOOL      enabled;
    IP6Entry* neighbor;
    OSTime    now;
    OSTime    stored;

    ASSERT(interface);
    ASSERT(preferredTime <= validTime);
    neighbor = IP6GetNeighbor(interface, addr);
    if (neighbor == NULL)
    {
        return IP_ERR_INS_RESOURCES;
    }

    switch (neighbor->state)
    {
      case ND_STATE_INIT:
        break;

      case ND_STATE_INCOMPLETE:
      case ND_STATE_REACHABLE:
      case ND_STATE_STALE:
      case ND_STATE_DELAY:
      case ND_STATE_PROBE:
        return IP_ERR_EXIST;    // duplicate IP address
        break;
      case ND_STATE_TENTATIVE:
      case ND_STATE_PREFERRED:
      case ND_STATE_DEPRECATED:
        now = OSGetTime();

        stored = neighbor->validTime - now;
        if (2 * 60 * 60 <= validTime ||
            stored < OSSecondsToTicks((OSTime) validTime))
        {
            // Update the stored validTime
        }
        else if (stored <= OSSecondsToTicks((OSTime) (2 * 60 * 60)) &&
                 OSSecondsToTicks((OSTime) validTime) <= stored)
        {
            // Ignore the prefix (XXX authenticated case)
            return IP_ERR_INVALID;
        }
        else
        {
            validTime = 2 * 60 * 60;
        }

        stored = neighbor->preferredTime - now;
        if (2 * 60 * 60 <= preferredTime ||
            stored < OSSecondsToTicks((OSTime) preferredTime))
        {
            // Update the stored preferredTime
        }
        else if (stored <= OSSecondsToTicks((OSTime) (2 * 60 * 60)) &&
                 OSSecondsToTicks((OSTime) preferredTime) <= stored)
        {
            // Ignore the prefix (XXX authenticated case)
            return IP_ERR_INVALID;
        }
        else
        {
            preferredTime = 2 * 60 * 60;
        }

        neighbor->validTime = NDTime(now, validTime);
        neighbor->preferredTime = NDTime(now, preferredTime);
        if (neighbor->preferredTime < now)
        {
            IP6SetNeighborState(neighbor, ND_STATE_DEPRECATED);
        }
        else
        {
            IP6SetNeighborState(neighbor, ND_STATE_PREFERRED);
        }
        return IP_ERR_NONE;
        break;
      default:
        return IP_ERR_INVALID;
        break;
    }

    enabled = OSDisableInterrupts();
    if (SO_IN6_IS_ADDR_LINKLOCAL(addr))
    {
        interface->linkLocal = neighbor;
    }
    OSCancelAlarm(&neighbor->alarm);
    neighbor->count = 0;
    now = OSGetTime();
    neighbor->preferredTime = NDTime(now, preferredTime);
    neighbor->validTime = NDTime(now, validTime);
    neighbor->flags |= flags;
    memcpy(neighbor->linkAddr, interface->mac, ETH_ALEN);   // XXX Ethernet specific
    if (0 < interface->dupAddrDetectTransmits &&
        !SO_IN6_IS_ADDR_LOOPBACK(&neighbor->addr))
    {
        IP6SetNeighborState(neighbor, ND_STATE_TENTATIVE);
        // Send a Neighbor Solicitation message. The node should delay up
        // to MAX_RTR_SOLICITATION_DELAY [sec] at random.
        OSSetAlarm(&neighbor->alarm,
                   IPRandTime(interface, 0, OSSecondsToTicks((OSTime) MAX_RTR_SOLICITATION_DELAY)),
                   ClaimHandler);
    }
    else
    {
        IP6SetNeighborState(neighbor, ND_STATE_PREFERRED);
    }
    OSRestoreInterrupts(enabled);

    return IP_ERR_NONE;
}
