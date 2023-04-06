/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPRoute.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPRoute.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    22    2/27/06 15:06 Shiki
    Modified using IP_ROUTING_NUMBER.

    21    2/23/06 14:01 Shiki
    Added IPReportAddrTable().

    20    2/23/06 10:58 Shiki
    Revised using IP_ROUTE_FLAG_*.

    19    2/14/06 18:30 Shiki
    Revised IPGetInterfaceStat() and IPClearInterfaceStat().

    18    2/14/06 9:56 Shiki
    Added IPReportRoutingTable().

    17    12/13/05 19:33 Shiki
    Revised to support RFC 3927.

    16    11/05/03 8:54 Shiki
    Fixed IPInitRoute().

    15    11/04/03 13:33 Shiki
    Revised IPInitRoute() to check arguments strictly.

    14    10/30/03 21:04 Shiki
    Added support for RFC 3021.

    13    5/03/03 12:58 Shiki
    Implemented IPInterfaceStat{} support functions.

    12    5/01/03 10:19 Shiki
    Modified IPSetMtu() not to use bad MTU value.

    11    10/07/02 10:45 Shiki
    Added support for IPGetConfigError().

    10    9/19/02 10:58 Shiki
    Implemented IPIsLocalAddr().

    9     6/13/02 11:31 Shiki
    Added IPSetMtu().

    8     4/24/02 13:41 Shiki
    Implemented IPGetLinkState().

    7     4/15/02 11:47 Shiki
    Revised to support multiple default gateways and added
    IPRecoverGateway() function.

    6     4/05/02 14:05 Shiki
    Implemented IPGetMtu().

    5     3/28/02 15:12 Shiki
    Modified public functions to be atomic.

    4     3/28/02 14:29 Shiki
    Implemented simple route cache replacement code.
    Revised IPRemoveRoute() implementation.

    3     3/27/02 20:17 Shiki
    Completed IPIsBroadcastAddr(). Modified IPInitRoute() to set proper
    broadcast address if possible.

    2     3/13/02 9:14 Shiki
    Clean up with IP_ALEN and ETH_ALEN.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <dolphin/socket.h>
#include "IPPrivate.h"

#include <string.h>

typedef struct IPRoute
{
    IFLink  link;

    u8      dst[IP_ALEN];       // destination IP address
    u8      netmask[IP_ALEN];   // netmask
    u8      gateway[IP_ALEN];   // next-hop gateway IP address

    u32     flag;
    OSTime  time;               // time of last access

    IPInterface* interface;
} IPRoute;

static BOOL    Initialized;
static IFQueue Up;
static IFQueue Free;
static IPRoute RoutingTable[IP_ROUTING_NUMBER];

static int CountBits(const u8* addr)
{
    int count;
    int i;
    u8  mask;

    count = 0;
    for (i = 0; i < IP_ALEN; ++i)
    {
        for (mask = 0x80; mask; mask >>= 1)
        {
            if (addr[i] & mask)
            {
                ++count;
            }
        }
    }
    return count;
}

void IPGetMacAddr(IPInterface* interface, u8* macAddr)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    memcpy(macAddr, interface->mac, ETH_ALEN);
    OSRestoreInterrupts(enabled);
}

void IPGetBroadcastAddr(IPInterface* interface, u8* broadcastAddr)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    memcpy(broadcastAddr, interface->broadcast, IP_ALEN);
    OSRestoreInterrupts(enabled);
}

void IPGetNetmask(IPInterface* interface, u8* netmask)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    memcpy(netmask, interface->netmask, IP_ALEN);
    OSRestoreInterrupts(enabled);
}

void IPGetAddr(IPInterface* interface, u8* addr)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    memcpy(addr, interface->addr, IP_ALEN);
    OSRestoreInterrupts(enabled);
}

void IPGetGateway(IPInterface* interface, u8* gateway)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    memcpy(gateway, interface->gateway, IP_ALEN);
    OSRestoreInterrupts(enabled);
}

void IPGetAlias(IPInterface* interface, u8* alias)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    memcpy(alias, interface->alias, IP_ALEN);
    OSRestoreInterrupts(enabled);
}

void IPGetMtu(IPInterface* interface, s32* mtu)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    *mtu = interface->mtu;
    OSRestoreInterrupts(enabled);
}

void IPGetLinkState(IPInterface* interface, BOOL* up)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    *up = interface->up;
    OSRestoreInterrupts(enabled);
}

void IPGetInterfaceStat(IPInterface* interface, IPInterfaceStat* stat)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    if (stat)
    {
        enabled = OSDisableInterrupts();
        stat->inUcastPackets = interface->stat.inUcastPkts;
        stat->inNonUcastPackets = interface->stat.inNUcastPkts;
        stat->inDiscards = interface->stat.inDiscards;
        stat->inErrors = interface->stat.inErrors;
        stat->outUcastPackets = interface->stat.outUcastPkts;
        stat->outNonUcastPackets = interface->stat.outNUcastPkts;
        stat->outDiscards = interface->stat.outDiscards;
        stat->outErrors = interface->stat.outErrors;
        stat->outCollisions = interface->stat.outCollisions;
        OSRestoreInterrupts(enabled);
    }
}

void IPClearInterfaceStat(IPInterface* interface)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    memset(&interface->stat, 0, sizeof(IFStat));
    OSRestoreInterrupts(enabled);
}

void IPSetBroadcastAddr(IPInterface* interface, const u8* broadcastAddr)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    memcpy(interface->broadcast, broadcastAddr ? broadcastAddr : IPLimited, IP_ALEN);
    OSRestoreInterrupts(enabled);
}

void IPSetNetmask(IPInterface* interface, const u8* netmask)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    memcpy(interface->netmask, netmask ? netmask : IPAddrAny, IP_ALEN);
    OSRestoreInterrupts(enabled);
}

void IPSetAddr(IPInterface* interface, const u8* addr)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    memcpy(interface->addr, addr ? addr : IPAddrAny, IP_ALEN);
    OSRestoreInterrupts(enabled);
}

void IPSetGateway(IPInterface* interface, const u8* gateway)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    memcpy(interface->gateway, gateway ? gateway : IPAddrAny, IP_ALEN);
    OSRestoreInterrupts(enabled);
}

// Set link-local address (169.254/16)
void IPSetAlias(IPInterface* interface, const u8* alias)
{
    BOOL enabled;

    ASSERT(alias == NULL ||
           IPIsLinkLocalAddr(interface, alias) ||
           IP_ADDR_EQ(alias, IPAddrAny));
    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    memcpy(interface->alias, alias ? alias : IPAddrAny, IP_ALEN);
    OSRestoreInterrupts(enabled);
}

void IPSetMtu(IPInterface* interface, s32 mtu)
{
    BOOL enabled;

    ASSERT(68 <= mtu);  // Official minimum MTU [RFC 791]
    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    interface->mtu = MAX(68, mtu);
    OSRestoreInterrupts(enabled);
}

void IPPrintRoutingTable(void)
{
    IPRoute* route;
    IPRoute* next;

    OSReport("IP Routing table\n");
    OSReport("Destination        Netmask            Gateway            Flags\n");
    IFIterateQueue(IPRoute*, &Up, route, next, link)
    {
        OSReport("%3d.%3d.%3d.%3d    %3d.%3d.%3d.%3d    %3d.%3d.%3d.%3d    ",
                 route->dst[0], route->dst[1], route->dst[2], route->dst[3],
                 route->netmask[0], route->netmask[1], route->netmask[2], route->netmask[3],
                 route->gateway[0], route->gateway[1], route->gateway[2], route->gateway[3]);
        if (route->flag & IP_ROUTE_FLAG_G)
        {
            OSReport("G");
        }
        if (route->flag & IP_ROUTE_FLAG_D)
        {
            OSReport("D");
        }
        if (route->flag & IP_ROUTE_FLAG_M)
        {
            OSReport("M");
        }
        OSReport("\n");
    }
}

s32 IPReportRoutingTable(IPInterface* interface, void* optval, int* optlen)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused( interface )
#endif // IOP_OS
    
    int           len;
    IPRoute*      route;
    IPRoute*      next;
    IPRouteEntry* ent;

    len = 0;
    ent = optval;
    IFIterateQueue(IPRoute*, &Up, route, next, link)
    {
        if (*optlen < len + sizeof(IPRouteEntry))
        {
            break;
        }
        memcpy(ent->dst, route->dst, IP_ALEN);
        memcpy(ent->netmask, route->netmask, IP_ALEN);
        memcpy(ent->gateway, route->gateway, IP_ALEN);
        ent->flag = route->flag;
        ent->time = route->time;
        len += sizeof(IPRouteEntry);
        ++ent;
    }
    *optlen = len;
    return IP_ERR_NONE;
}

static BOOL Hit(const u8* dst, const u8* addr, const u8* netmask)
{
    int i;

    for (i = 0; i < IP_ALEN; ++i)
    {
        if (dst[i] != (addr[i] & netmask[i]))
        {
            return FALSE;
        }
    }
    return TRUE;
}

// Returns FLASE for multicast address
BOOL IPIsBroadcastAddr(IPInterface* interface, const u8* addr)
{
    u32  netmask;
    u32  netid;
    u32  ipaddr;

    interface = interface ? interface : &__IFDefault;

    if (IP_CLASSD(addr) || IP_CLASSE(addr))
    {
        return FALSE;
    }

    if (IP_ADDR_EQ(addr, IPLimited) ||
        IP_ADDR_EQ(addr, IPAddrAny) ||  // Old Berkeley
        IP_ADDR_EQ(addr, interface->broadcast))
    {
        return TRUE;
    }

    ipaddr = SONtoHl(*(u32*) addr);

    // Subnet-directed broadcast for primary address
    netmask = SONtoHl(*(u32*) interface->netmask);
    netid   = SONtoHl(*(u32*) interface->addr) & netmask;
    if (netid)
    {
        if ((ipaddr & netmask) == netid &&
            ((ipaddr & ~netmask) == ~netmask || (ipaddr & ~netmask) == 0) &&
            CountBits(interface->netmask) < 31) // RFC 3021
        {
            return TRUE;
        }
#if 0
        // All-subnet-directed broadcast have been deprecated in
        // RFC 1812. See RFC 1878 for detail.
        if (IP_CLASSA(interface->addr))
        {
            netmask = 0xff000000;
        }
        else if (IP_CLASSB(interface->addr))
        {
            netmask = 0xffff0000;
        }
        else if (IP_CLASSC(interface->addr))
        {
            netmask = 0xffffff00;
        }
        netid = SONtoHl(*(u32*) interface->addr) & netmask;
        if ((ipaddr & netmask) == netid &&
            (ipaddr & ~netmask) == ~netmask)
        {
            return TRUE;
        }
#endif
    }

    // Subnet-directed broadcast for alias
    netmask = 0xffff0000;   // Class B link-local
    netid   = SONtoHl(*(u32*) interface->alias) & netmask;
    if (netid)
    {
        if ((ipaddr & netmask) == netid &&
            ((ipaddr & ~netmask) == ~netmask || (ipaddr & ~netmask) == 0))
        {
            return TRUE;
        }
    }

    return FALSE;
}

BOOL IPIsLoopbackAddr(IPInterface* interface, const u8* addr)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused( interface )
#endif // IOP_OS

    if (addr[0] == 127)
    {
        return TRUE;
    }
    return FALSE;
}

BOOL IPIsLinkLocalAddr(IPInterface* interface, const u8* addr)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused( interface )
#endif // IOP_OS
    
    if (memcmp(IPLinkLocal, addr, 2) == 0)
    {
        return TRUE;
    }
    return FALSE;
}

BOOL IPIsLocalAddr(IPInterface* interface, const u8* addr)
{
    const u8 classB[IP_ALEN] = { 255, 255, 0, 0 };
    BOOL  enabled;
    BOOL  rc = FALSE;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    if (IP_ADDR_NE(interface->addr, IPAddrAny))
    {
        if (IP_ADDR_IN_NET(addr, interface->addr, interface->netmask))
        {
            rc = TRUE;
        }
    }
    if (IP_ADDR_NE(interface->alias, IPAddrAny))
    {
        if (IP_ADDR_IN_NET(addr, interface->alias, classB))
        {
            rc = TRUE;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

IPInterface* IPGetRoute(const u8* addr, u8* dst)
{
    IPRoute* route;
    IPRoute* next;

    IFIterateQueue(IPRoute*, &Up, route, next, link)
    {
        if (!Hit(route->dst, addr, route->netmask))
        {
            continue;
        }

        // Hit
        if (dst)
        {
            if (route->flag & IP_ROUTE_FLAG_G)
            {
                memmove(dst, route->gateway, IP_ALEN);
            }
            else
            {
                memmove(dst, addr,           IP_ALEN);
            }

#ifdef VERBOSE
            OSReport("IPGetRoute: %d.%d.%d.%d -> %d.%d.%d.%d\n",
                     addr[0], addr[1], addr[2], addr[3],
                     dst[0], dst[1], dst[2], dst[3]);
#endif
        }

        route->time = __OSGetSystemTime();

        return route->interface;
    }

    return NULL;
}

static BOOL AddRoute(const u8* dst, const u8* netmask, const u8* gateway, u32 flag)
{
    IPRoute* route;
    IPRoute* next;
    IPRoute* ent;
    int      i;
    int      bits;

    if (!Hit(dst, dst, netmask))
    {
        return FALSE;   // Impossible
    }

    if (IP_ADDR_EQ(gateway, IPAddrAny))
    {
        flag &= ~IP_ROUTE_FLAG_G;
    }
    else
    {
        flag |= IP_ROUTE_FLAG_G;
    }

    // See if there is a route for the destination
    IFIterateQueue(IPRoute*, &Up, route, next, link)
    {
        for (i = 0; i < IP_ALEN; ++i)
        {
            if ((route->dst[i] & route->netmask[i]) != (dst[i] & netmask[i]))
            {
                break;
            }
        }
        if (i < IP_ALEN)
        {
            continue;
        }

        // Support multiple default gateways
        if ((flag & IP_ROUTE_FLAG_G) && (route->flag & (IP_ROUTE_FLAG_D | IP_ROUTE_FLAG_M)) == 0)
        {
            if (IP_ADDR_EQ(gateway, route->gateway))
            {
                return TRUE;
            }
            else
            {
                continue;
            }
        }

        //
        // Update the route
        //
        memmove(route->gateway, gateway, IP_ALEN);
        memmove(route->netmask, netmask, IP_ALEN);

        if ((route->flag & IP_ROUTE_FLAG_D) == 0)
        {
            flag &= ~IP_ROUTE_FLAG_D;
        }

        route->flag = flag;
        route->time = __OSGetSystemTime();
        route->interface = &__IFDefault;
        return TRUE;
    }

    //
    // Add a new route (Replace if necessary and possible)
    //
    if (IFIsEmptyQueue(&Free))
    {
        // Attempt to remove one entry from Up queue. An entry can be removed
        // only if D bit is set. The entry is currently chosen by the last-used
        // timestamp. (Can be by reference count)
        ent = NULL;
        IFIterateQueue(IPRoute*, &Up, route, next, link)
        {
            if (route->flag & IP_ROUTE_FLAG_D)
            {
                if (ent == NULL)
                {
                    ent = route;
                }
                else if (route->time < ent->time)
                {
                    ent = route;
                }
            }
        }
        if (ent == NULL)
        {
            return FALSE;
            // NOT REACHED HERE
        }
        IFDequeueItem(IPRoute*, &Up,   ent, link);
    }
    else
    {
        IFDequeueHead(IPRoute*, &Free, ent, link);
    }
    memmove(ent->dst,     dst,     IP_ALEN);
    memmove(ent->netmask, netmask, IP_ALEN);
    memmove(ent->gateway, gateway, IP_ALEN);

    flag &= ~IP_ROUTE_FLAG_M;

    ent->flag = flag;
    ent->time = __OSGetSystemTime();
    ent->interface = &__IFDefault;

    // Routes are sorted by the number of one bits in the netmask.
    bits = CountBits(netmask);
    IFIterateQueue(IPRoute*, &Up, route, next, link)
    {
        if (CountBits(route->netmask) < bits)
        {
            IFEnqueueBefore(IPRoute*, &Up, ent, route, link);
            return TRUE;
        }
    }

    IFEnqueueTail(IPRoute*, &Up, ent, link);
    return TRUE;
}

// XXX Note redirect may instruct the host to restore the original
//     route for the destination. Then simply remove the current
//     route cache marked 'D'.
BOOL IPRedirect(const u8* dst, const u8* gateway, const u8* router)
{
    IPInterface* interface;
    u8 addr[IP_ALEN];

    if (IP_ADDR_EQ(gateway, IPAddrAny))
    {
        return FALSE;
    }

    // Verify dst can be reached using the current routing table
    interface = IPGetRoute(dst, addr);
    if (interface == NULL)
    {
        return FALSE;
    }

    // Verify gateway is directly reachable valid address
    if (!IP_ADDR_IN_NET(gateway, interface->addr, interface->netmask) ||
        IPIsBroadcastAddr(interface, gateway))
    {
        return FALSE;
    }

    // Verify the router is the current gateway for dst
    if (IP_ADDR_NE(addr, router))
    {
        return FALSE;
    }

    // Verify the interface for gateway is same as for the router
    if (IPGetRoute(gateway, NULL) != IPGetRoute(router, NULL))
    {
        return FALSE;
    }

    // Verify gateway is not one of the host's address
    if (IP_ADDR_EQ(gateway, __IFDefault.addr) ||
        IP_ADDR_EQ(gateway, __IFDefault.alias))
    {
        return FALSE;
    }

    // [RFC1122] Since the subnet mask appropriate to the destination
    // address is generally not known, a Network Redirect message
    // SHOULD be treated identically to a Host Redirect message
    return AddRoute(dst, IPLimited, gateway,
                    IP_ROUTE_FLAG_G | IP_ROUTE_FLAG_D | IP_ROUTE_FLAG_M);
}

BOOL IPAddRoute(const u8* dst, const u8* netmask, const u8* gateway)
{
    BOOL enabled;
    BOOL rc;

    enabled = OSDisableInterrupts();
    rc = AddRoute(dst, netmask, gateway, 0);
    OSRestoreInterrupts(enabled);
    return rc;
}

// Remove from least specific one first.
BOOL IPRemoveRoute(const u8* dst, const u8* netmask, const u8* gateway)
{
    BOOL     enabled;
    BOOL     rc;
    IPRoute* route;
    IPRoute* next;

    enabled = OSDisableInterrupts();
    rc = FALSE;
    IFIterateQueueReverse(IPRoute*, &Up, route, next, link)
    {
        if (IP_ADDR_EQ(dst, route->dst) &&
            (IP_ADDR_EQ(netmask, IPAddrAny) || IP_ADDR_EQ(netmask, route->netmask)) &&
            (IP_ADDR_EQ(gateway, IPAddrAny) || IP_ADDR_EQ(gateway, route->gateway)))
        {
            // Remove route
            IFDequeueItem(IPRoute*, &Up,   route, link);
            IFEnqueueHead(IPRoute*, &Free, route, link);
            rc = TRUE;
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

// Initializes IP routing table
BOOL IPInitRoute(const u8* addr, const u8* netmask, const u8* gateway)
{
    BOOL         enabled;
    IPRoute*     route;
    IPRoute*     end;
    IPInterface* interface = &__IFDefault;
    int          prefix;

    enabled = OSDisableInterrupts();
    if (!Initialized)
    {
        Initialized = TRUE;
        memset(RoutingTable, 0, sizeof RoutingTable);
        IFInitQueue(&Up);
        IFInitQueue(&Free);
        end = &RoutingTable[IP_ROUTING_NUMBER];
        for (route = &RoutingTable[0]; route < end; ++route)
        {
            IFEnqueueTail(IPRoute*, &Free, route, link);
        }
    }
    OSRestoreInterrupts(enabled);

    IPSetAddr(interface, addr);
    IPSetNetmask(interface, netmask);
    IPSetGateway(interface, gateway);
    IPSetBroadcastAddr(interface, NULL);

    prefix = CountBits(interface->netmask);
    if (prefix < 31)
    {
        u8  broadcast[IP_ALEN];
        int i;

        for (i = 0; i < IP_ALEN; ++i)
        {
            broadcast[i] = (u8) (interface->addr[i] & interface->netmask[i]);
            broadcast[i] |= ~interface->netmask[i];
        }
        IPSetBroadcastAddr(interface, broadcast);
    }

    if (IPIsBroadcastAddr(interface, interface->addr) ||
        IP_ADDR_EQ(interface->gateway, interface->addr) ||
        (IP_ADDR_NE(interface->gateway, IPAddrAny) &&
         (IPIsBroadcastAddr(interface, interface->gateway) ||
          (prefix != 32 && !IP_ADDR_IN_NET(interface->gateway, interface->addr,
                                           interface->netmask)))))
    {
        IPSetAddr(interface, NULL);
        IPSetNetmask(interface, NULL);
        IPSetGateway(interface, NULL);
        IPSetBroadcastAddr(interface, NULL);
    }

    return IPRefreshRoute();
}

BOOL IPRefreshRoute(void)
{
    BOOL     enabled;
    IPRoute* route;
    IPRoute* next;
    u8*      addr;
    u8*      netmask;
    u8*      gateway;
    u8*      alias;
    const u8 loopback[IP_ALEN] = { 127, 0, 0, 0 };
    const u8 classA[IP_ALEN]   = { 255, 0, 0, 0 };
    const u8 classB[IP_ALEN]   = { 255, 255, 0, 0 };
    u8       netid[IP_ALEN];
    int      i;

    enabled = OSDisableInterrupts();

    addr    = __IFDefault.addr;
    netmask = __IFDefault.netmask;
    gateway = __IFDefault.gateway;
    alias   = __IFDefault.alias;

    // Clear every routing table entries
    IFIterateQueue(IPRoute*, &Up, route, next, link)
    {
        IFDequeueItem(IPRoute*, &Up,   route, link);
        IFEnqueueHead(IPRoute*, &Free, route, link);
    }

    // Limited broadcast 255.255.255.255/255.255.255.255/0.0.0.0/0
    IPAddRoute(IPLimited, IPLimited, IPAddrAny);

    if (IP_ADDR_NE(addr, IPAddrAny))
    {
        // Loopback addr/255.255.255.255/127.0.0.1/G
        IPAddRoute(addr, IPLimited, IPLoopbackAddr);

        // Interface addr netid/netmask/0.0.0.0/0
        for (i = 0; i < IP_ALEN; ++i)
        {
            netid[i] = (u8) (addr[i] & netmask[i]);
        }
        IPAddRoute(netid, netmask, IPAddrAny);
    }

    if (IP_ADDR_NE(alias, IPAddrAny))
    {
        // Loopback alias/255.255.255.255/127.0.0.1/G
        IPAddRoute(alias, IPLimited, IPLoopbackAddr);

        // Link-local netid/255.255.0.0/0.0.0.0/0
        for (i = 0; i < IP_ALEN; ++i)
        {
            netid[i] = (u8) (alias[i] & classB[i]);
        }
        IPAddRoute(netid, classB, IPAddrAny);
    }

    // Loopback 127.0.0.0/255.0.0.0/127.0.0.1/G
    IPAddRoute(loopback, classA, IPLoopbackAddr);

    // IPv4 Link-Local Addresses [RFC 3927]
    // any host conforming to this specification knows that
    // regardless of source address an IPv4 Link-Local destination must be
    // reached by forwarding directly to the destination, not via a router;
    // it is not necessary for that host to have a Link-Local source address
    // in order to send to a Link-Local destination address.
    IPAddRoute(IPLinkLocal, classB, IPAddrAny);

    if (IP_ADDR_NE(gateway, IPAddrAny) ||
#ifdef IOP_OS
        (IP_ADDR_NE(alias, IPAddrAny) && IP_ADDR_EQ(addr, IPAddrAny)))    // ARP for everything
#else
        IP_ADDR_NE(alias, IPAddrAny) && IP_ADDR_EQ(addr, IPAddrAny))    // ARP for everything
#endif // IOP_OS
    {
        // Default route 0.0.0.0/0.0.0.0/gateway/G
        IPAddRoute(IPAddrAny, IPAddrAny, gateway);
    }

    ARPGratuitous(&__IFDefault);
    // [SHOULD] Send one more gratuitous ARP after two seconds

    OSRestoreInterrupts(enabled);

#ifdef VERBOSE
    IPPrintRoutingTable();
#endif

    return TRUE;
}

// Move dead route to the end of the list of the same netmask bit count
static void DecayRoute(IPRoute* dead)
{
    int      bits;
    IPRoute* route;
    IPRoute* next;

    bits = CountBits(dead->netmask);
    IFDequeueItem(IPRoute*, &Up, dead, link);
    IFIterateQueueReverse(IPRoute*, &Up, route, next, link)
    {
        if (bits <= CountBits(route->netmask))
        {
            IFEnqueueAfter(IPRoute*, &Up, route, dead, link);
            return;
        }
    }
    IFEnqueueHead(IPRoute*, &Up, dead, link);
}

// Gateway for the specified destination address apears to be down.
// Switch to another gateway if possible
BOOL IPRecoverGateway(const u8* dst)
{
    IPRoute* route;
    IPRoute* next;

    if (IP_ADDR_EQ(dst, IPAddrAny) || dst[0] == 127)
    {
        return FALSE;
        // NOT REACHED HERE
    }

    // See if dst is the next-hop gateway address
    IFIterateQueueReverse(IPRoute*, &Up, route, next, link)
    {
        if ((route->flag & IP_ROUTE_FLAG_G) == 0 ||
            route->gateway[0] == 127)
        {
            continue;
        }

        if (IP_ADDR_EQ(route->gateway, dst))
        {
            DecayRoute(route);
            return TRUE;
            // NOT REACHED HERE
        }
    }

    IFIterateQueue(IPRoute*, &Up, route, next, link)
    {
        if (Hit(route->dst, dst, route->netmask))
        {
            if ((route->flag & IP_ROUTE_FLAG_G) && route->gateway[0] != 127)
            {
                DecayRoute(route);
                return TRUE;
                // NOT REACHED HERE
            }
            break;
        }
    }

    return FALSE;
}

s32 IPGetConfigError(IPInterface* interface)
{
    interface = interface ? interface : &__IFDefault;
    return interface->err;
}

s32 IPSetConfigError(IPInterface* interface, s32 err)
{
    BOOL enabled;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    if (interface->err == IP_ERR_NONE)
    {
        interface->err = err;
    }
    OSRestoreInterrupts(enabled);
    return interface->err;
}

s32 IPClearConfigError(IPInterface* interface)
{
    BOOL enabled;
    s32  prev;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    prev = interface->err;
    interface->err = IP_ERR_NONE;
    OSRestoreInterrupts(enabled);
    return prev;
}

s32 IPReportAddrTable(IPInterface* interface, void* optval, int* optlen)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused( interface )
#endif // IOP_OS
    
    int          len;
    IPAddrEntry* addrEntry;

    len = 0;
    addrEntry = optval;

    if (IP_ADDR_NE(interface->addr, IPAddrAny))
    {
        if (len + sizeof(IPAddrEntry) <= *optlen)
        {
            memmove(addrEntry->addr, interface->addr, IP_ALEN);
            memmove(addrEntry->netMask, interface->netmask, IP_ALEN);
            memmove(addrEntry->bcastAddr, interface->broadcast, IP_ALEN);
            len += sizeof(IPAddrEntry);
            ++addrEntry;
        }
    }

    if (IP_ADDR_NE(interface->alias, IPAddrAny))
    {
        const u8 classB[IP_ALEN] = { 255, 255, 0, 0 };

        if (len + sizeof(IPAddrEntry) <= *optlen)
        {
            memmove(addrEntry->addr, interface->alias, IP_ALEN);
            memmove(addrEntry->netMask, classB, IP_ALEN);
            memmove(addrEntry->bcastAddr, IPLinkLocal, 2);
            memmove(addrEntry->bcastAddr + 2, IPLimited + 2, 2);
            len += sizeof(IPAddrEntry);
            ++addrEntry;
        }
    }

    *optlen = len;
    return IP_ERR_NONE;
}
