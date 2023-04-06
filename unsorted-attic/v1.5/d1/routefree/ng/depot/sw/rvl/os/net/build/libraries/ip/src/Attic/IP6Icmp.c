/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API - Internet Control Message Protocol for IPv6
  File:     IP6Icmp.c
  RFC:      2461 (ND), 2463 (ICMPv6)

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IP6Icmp.c,v $
  Revision 1.4  2006/04/12 17:43:41  mxu
  include ip.h header file

  Revision 1.3  2006/04/11 01:40:35  mxu
  update to Nintendo's April 05 release

  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    98    4/03/06 19:26 Shiki
    Modified IP6GetPathMTU() timer settings.

    97    4/03/06 19:20 Shiki
    Modified IP6GetPathMTU() not to increase PMTU less than 1 min after the
    previous attempted increase.

    96    3/06/06 16:07 Shiki
    Enabled IPv6 by default by globally defining IP_INET6.

    95    3/03/06 10:43 Shiki
    Fixed ICMP6In() to silently ignore an unrecognized value fields in a
    router alert option.

    94    3/02/06 10:19 Shiki
    Modified ICMP6In() to check the router alert value for MLD packets.
    Fixed ICMP6Out() to send a MLD Done message to the link-scope
    all-routers multicast address.

    93    2/28/06 14:16 Shiki
    Fixed GetNeighbor() to sort IP6Entries correctly.
    Modified DoTooBig() to update lastTooBig separately.
    Revised to set and clear ND_FLAG_*.

    92    2/28/06 9:07 Shiki
    Revised using modified IP6Entry{}.
    Added IP6ReportEntryTable() (not completed).

    91    2/22/06 15:51 Shiki
    Fixed IP6Startup() to create the IP6Entry entry for the loopback
    address.

    90    2/20/06 17:44 Shiki
    Clean up.

    89    2/16/06 13:52 Shiki
    Fixed IP6ReportPrefixTable().

    88    2/14/06 18:47 Shiki
    Revised to collect interface statistics.

    87    2/14/06 9:54 Shiki
    Added IP6ReportPrefixTable().

    86    2/10/06 17:40 Shiki
    Revised Recover() to call IP6Shuffle() internally.

    85    2/10/06 13:56 Shiki
    Fixed ICMP6In().

    84    2/09/06 18:40 Shiki
    Implemented Reroute().

    83    2/09/06 17:31 Shiki
    Revised ICMPv6 error handling code.

    82    2/07/06 11:18 Shiki
    Fixed ICMP6SendError().

    81    2/06/06 15:07 Shiki
    Renamed Shuffle() to IP6Shuffle().

    80    2/02/06 18:58 Shiki
    Fixed DoTooBig() and ICMP6In().

    79    2/01/06 16:25 Shiki
    Added full support of IPv6 PMTU discovery.
    Supported ND_STATE_NON_LISTENER state.

    78    1/26/06 18:41 Shiki
    Renamed IP6Neighbor to IP6Entry.

    77    1/26/06 18:20 Shiki
    Fixed ICMP6In().
    Fixed IP6GetNextNeighbor() for multicast addresses.
    Fixed ICMP6Ping().

    76    1/26/06 16:53 Shiki
    Fixed ICMP6Out() to set correct hops count.

    75    1/26/06 16:28 Shiki
    Revised IP6Fragment() to support Packet Size Issues in RFC 2460.

    74    1/26/06 15:01 Shiki
    Fixed DoTooBig() not to increase PMTU.
    Fixed IP6AddRoute().
    Implemented SetTarget().

    73    1/26/06 11:30 Shiki
    Modified to support PMTU.

    72    1/25/06 17:19 Shiki
    Fixed to revoke every neighbor cache associated to a prefix which is
    being invalidated.

    71    1/25/06 15:54 Shiki
    Integrated IP6Destination{} and IP6Neighbor{}. (under testing)
    Added IP6AddRoute() and IP6RemoveRoute(). (not tested)

    70    1/24/06 18:44 Shiki
    Renamed IP6Route to IP6Destination as it was misleading.

    69    1/24/06 17:23 Shiki
    Fixed ICMP6SendError().

    68    1/24/06 14:56 Shiki
    Modified NDHold() to increment interface->stat.outDiscards if it
    discards a packet.

    67    1/24/06 13:27 Shiki
    Fixed IP6GetNextNeighbor().

    66    1/24/06 10:29 Shiki
    Clean up.

    65    1/23/06 13:55 Shiki
    Fixed DoTooBig().

    64    1/20/06 17:06 Shiki
    Revised to use interface->curHopLimit.

    63    1/20/06 16:25 Shiki
    Fixed IP6SetNeighborState().

    62    1/20/06 16:14 Shiki
    Revised IP6Startup(), etc.

    61    1/20/06 14:03 Shiki
    Revised to not using ETHGetEUI64() and ETHGetLinkLocal() which are
    Ethernet specific.

    60    1/20/06 13:25 Shiki
    Fixed IP6SetNeighborState() to leave from the solicited-node multicast
    address if required.

    59    1/20/06 13:11 Shiki
    Revised state-transition diagram of a neighbor cache.

    58    1/20/06 11:36 Shiki
    Clean up.

    57    1/20/06 11:19 Shiki
    Revised IP6GetNextNeighbor() to support a round-robin selection of
    default routers
    Fixed IP6RemoveAddr().

    56    1/20/06 10:51 Shiki
    Fixed IP6GetNeighbor(),IP6GetNextNeighbor().
    Added IP6SwitchToHost() and IP6SwitchToRouter().

    55    1/19/06 19:04 Shiki
    Implemented IP6RemoveAddr().
    Revised IP6SetNeighborState().

    54    1/19/06 18:38 Shiki
    Fixed IP6Claim() to get neighbor by using IP6GetNeighbor() not
    IP6GetNextNeighbor().

    53    1/19/06 18:25 Shiki
    Renamed IP6GetNeighbor() to IP6GetNextNeighbor().

    52    1/18/06 18:19 Shiki
    Revised the reference count management of IP6Neighbor{}.

    51    1/18/06 9:19 Shiki
    Fixed DoRedirect().

    50    1/18/06 8:57 Shiki
    Fixed neighbor->isRouter management.

    49    1/17/06 15:04 Shiki
    Fixed DoNeighborSolicit().

    48    1/17/06 11:36 Shiki
    Revised DoRouterAdvert() not to ignore prefix option even if the
    on-link flag is not set.

    47    1/16/06 17:41 Shiki
    Fixed DoRouterAdvert().

    46    1/16/06 14:25 Shiki
    Fixed CheckOptionType() to support (e.2) of RFC 2463.
    Fixed ICMP6Out() to correctly calculate the checksum of an MLD packet.

    45    1/13/06 16:20 Shiki
    Fixed Revalidate() to keep neighbor if it is still a valid router.

    44    1/13/06 15:56 Shiki
    Fixed IP6GetNextNeighbor() to assume the destination is on-link if the
    Default Router List is empty.

    43    1/13/06 14:08 Shiki
    Fixed DoRedirect().

    42    1/13/06 13:14 Shiki
    Fixed ICMP6SendError().

    41    1/13/06 13:02 Shiki
    Revised ICMP6SendError() to check received packet before sending an
    error message.

    40    1/13/06 9:52 Shiki
    Added ND_STATE_INIT state.
    Fixed DoRouterAdvert() to process Router Advertisement without source
    link layer address.
    Implemented IP6SetAddr().

    39    1/12/06 11:42 Shiki
    Fixed DiscardPendingPackets() to call ICMPFreeDatagram().

    38    1/12/06 11:01 Shiki
    Fixed DoNeighborAdvert() to transit ND_STATE_DELAY if necessary.

    37    1/12/06 9:37 Shiki
    Fixed DoRouterAdvert(),DoNeighborAdvert(),DoNeighborSolicit(), and
    DoRedirect() to check ICMPv6 options have a length that is greater than
    zero.

    36    1/11/06 17:01 Shiki
    Fixed to clean up MLDTable[] from SOCleanup().

    35    1/11/06 14:42 Shiki
    Fixed IPv6 to use interface->linkMTU instead of interface->mtu.

    34    1/11/06 10:28 Shiki
    Fixed ICMP6SendError() to use the minimum IPv6 MTU, not interface->mtu.

    33    1/06/06 17:44 Shiki
    Revised ICMP packet buffer management code.

    32    06/01/06 13:59 Ueno_kyu
    Cleanup.

    31    06/01/06 13:28 Ueno_kyu
    Moved functions to save datagram to IPIcmp.c.

    29    04/10/27 9:20 Ueno_kyu
    Modified IP6EnumAddresses() to stop, when the callback returns FALSE.

    28    04/10/20 11:00 Ueno_kyu
    Added ICMP6Notify().

    27    04/10/12 18:35 Ueno_kyu
        Replaced IP6_HLEN as sizeof(IP6Hdr).
        Replaced IP6_ALEN as sizeof(SOIn6Addr).
        Replaced SO_IN6_ARE_ADDR_NOT_EQUAL() as !SO_IN6_ARE_ADDR_EQUAL().

    26    10/12/04 18:00 Shiki
    Implemented IP6Cleanup(). Cleanup.

    25    04/10/01 10:44 Ueno_kyu
    Cleanup.

    24    04/09/28 16:45 Ueno_kyu
    Revised IPv6 ping program.

    23    04/09/28 10:30 Ueno_kyu
    Modified IP6EnumAddresses() to enable interrupts, before calling a
    callback.
    Cleanup.

    22    04/09/27 17:47 Ueno_kyu
    Added IP6EnumAddresses() to get all IPv6 addresses assigned to an
    interface.

    21    04/09/24 11:19 Ueno_kyu
    Added support for IPv6 ping program.

    20    04/09/21 13:24 Ueno_kyu
    Fixed IP6SearchNeighbor(), IP6GetNextNeighbor(), Revalidate(),
    DoRouterAdvert() and DoNeighborSolicit().

    19    04/09/15 13:58 Ueno_kyu
    Cleanup.

    18    04/09/15 13:48 Ueno_kyu
    Modified DoNeighborSolicit() to check whether the address in the target
    field of NS matches a valid address assigned to the receiving
    interface.

    17    04/09/10 15:53 Ueno_kyu
    Modified IP6SearchNeighbor() to change the state of a neighbor cache
    entry from REACHBLE to STALE, when more than ReachableTime milliseconds
    have elapsed.
    Modified IP6GetNextNeighbor() to select a default router, when no
    destination cache entry exists for an off-link destination.
    Modified DoRouterAdvert() to set Router Lifetime to a routerLifetime
    member of IP6Neighbor{}, instead of a validTime member.

    16    04/09/08 16:29 Ueno_kyu
    Modified DoNeighborAdvert() to set "update", regardless of the override
    flag of NA.

    15    04/09/07 14:25 Ueno_kyu
    Modified AllocPrefix() not to return a destination cache entry
    whose valid lifetime expires.

    14    04/09/03 15:02 Ueno_kyu
    Revised to save outgoing ICMPv6 datagrams in static buffers
    (ICMP6Buffer[]),
    if available.

    13    04/09/02 13:30 Ueno_kyu
    Modified Revalidate() to send a unicast Neighbor Solicitation probe in
    the PROBE state.
    Modified IP6SetNeighborState() to increase neighbor->count in the
    INCOMPLETE state.

    12    04/09/02 9:16 Ueno_kyu
    Modified IP6Startup() to join the all-nodes multicast address.

    11    04/08/31 19:17 Ueno_kyu
    Modified buffer size of Echo Reply packets, according to RFC2460.

    10    04/08/23 9:05 Ueno_kyu
    Modified DoEchoRequest() to call SendCallback(),
    when an error occurs in IP6Out().

    9     04/08/19 13:36 Ueno_kyu
    Added error-handling code to SelectBuffer().
    Modified Revalidate() to discard a waiting packet (Echo Reply).

    8     04/08/18 16:36 Ueno_kyu
    Modified ICMP6SendError() to set a pointer field.

    7     04/08/18 13:25 Ueno_kyu
    Modified SelectBuffer() to check a packet size.

    6     04/08/18 10:10 Ueno_kyu
    Cleanup.

    5     04/08/18 10:04 Ueno_kyu
    Modified DoEchoRequest() to save packets (echo reply).

    4     04/07/14 16:41 Ueno_kyu
    Modified IP6Startup() to initialize IP6RouteTable and NDCache
    everytime.

    3     04/07/13 20:14 Ueno_kyu
    Removed an assertion in ICMP6In().

    2     6/22/04 9:29 Shiki
    Clean up.

    1     6/09/04 15:58 Shiki
    IPv6 pilot implementation
  $NoKeywords: $

                                         Timeout/Neighbor Solicitation
                                                  +-------+
                                                  |       |
                                                  V       |
     ------                              ------------     |
    |      |  -/Neighbor Solicitation   |            |    |
    | INIT |--------------------------->| INCOMPLETE |----+
    |      |<---------------------------|            |
     ------     Retries Exceeded/-       ------------
       A                                      |
       |             +------------------------+
       |             v   Neighbor Advertisement/-
       |    -----------
       |   |           |
       |   | REACHABLE |<--------------+-------------------+
       |   |           |               |                   |
       |    -----------                |                   |Neighbor
       |       |                       |                   |Advertisement/-
       |  ReachableTime                |                   |
       |  elapsed/-                    |                   |
       |       |                       |                   |
       |       v                       |                   |
       |    -------                 -------              -------
       |   |       |               |       |            |       |
       |   | STALE |-------------->| DELAY |----------->| PROBE |<--+
       |   |       | Send packet/- |       | DelayTime  |       |   |Timeout/
       |    -------                 -------  elapsed/    -------    |Neighbor
       |                                     Neighbor     |   |     |Solicitation
       |                                     Solicitation |   |     |
       +--------------------------------------------------+   +-----+
                        Retries Exceeded/-

                  State-transition diagram of a neighbor cache

 *---------------------------------------------------------------------------*/

#include <stddef.h>
#include <dolphin/os.h>

#ifdef IOP_OS
#include <dolphin/ip.h>
#endif // IOP_OS

#include <dolphin/socket.h>
#include "IPPrivate.h"
#include "IP6Private.h"

#define IP6_FRAG_OFFSET(frag)   ((u16) (((IP6Frag*) frag)->offlg & 0xfff8))

static void DoRouterAdvert   (IPInterface* interface, IP6Hdr* ip6, NDRouterAdvert* ra, s32 len);
static void DoNeighborAdvert (IPInterface* interface, IP6Hdr* ip6, NDNeighborAdvert* na, s32 len, u32 flag);
static void DoNeighborSolicit(IPInterface* interface, IP6Hdr* ip6, NDNeighborSolicit* ns, s32 len, u32 flag);
static void DoRedirect       (IPInterface* interface, IP6Hdr* ip6, NDRedirect* redirect, s32 len);

static void RouterSolicitHandler(OSAlarm* alarm, OSContext* context);
static IP6Entry* GetNeighbor(IPInterface* interface, const SOIn6Addr* addr, u8 prefixLen);

IFQueue NDCache;

static IP6Entry NeighborTable[MAX_NEIGHBORS];

static void SetNetwork(IP6Entry* neighbor, IP6Entry* network)
{
    if (neighbor->network == network)
    {
        return;
    }
    if (neighbor->network)
    {
        IP6Entry* prev = neighbor->network;
        IFDequeueItem(IP6Entry*, &prev->queueNetwork, neighbor, linkNetwork);
        IP6PutNeighbor(prev);
    }
    if (network)
    {
        IP6RefNeighbor(network);
        IFEnqueueTail(IP6Entry*, &network->queueNetwork, neighbor, linkNetwork);
    }
    neighbor->network = network;
}

static u16 ICMP6CheckSum(IP6Hdr* ip6, void* icmp6, s32 plen)
{
    IFVec vec;

    vec.data = ip6;
    vec.len  = (u8*) icmp6 + plen - (u8*) ip6;
    return IP6CheckSum(SO_IPPROTO_ICMPV6, &vec, 1, icmp6, plen);
}

static void DoEchoReply(IPInterface* interface, IP6Hdr* ip, ICMP6Hdr* icmp, s32 len, u32 flag)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
    TCPIP_UNUSED(flag);
    TCPIP_UNUSED(len);
#else
    #pragma unused(interface, flag, len)
#endif // IOP_OS
    void*        data;
    IPInfo*      curr;
    IPInfo*      next;
    ICMP6Info*   info;
    ICMPCallback callback;
    ICMPObj*     obj;

    data = (void*) ((u8*) icmp + sizeof(ICMP6Hdr));

    IFIterateQueue(IPInfo*, &ICMPInfoQueue, curr, next, link)
    {
        info = (ICMP6Info*) curr;

        if (info->info.family != SO_PF_INET6)
        {
            continue;
        }

        obj = ICMPGetObj((ICMPInfo*) info);
        if (obj->callback == NULL)
        {
            continue;
        }
        if (obj->seq != (icmp->data & 0x00ff) ||
            info->local.port != (icmp->data >> 16))
        {
            continue;
        }
        if (!SO_IN6_ARE_ADDR_EQUAL(&ip->src, (SOIn6Addr*) &info->remote.addr) ||
            !SO_IN6_ARE_ADDR_EQUAL(&ip->dst, (SOIn6Addr*) &info->local.addr))
        {
            continue;
        }

        callback = obj->callback;
        if (callback &&
            ip->plen + sizeof(IP6Hdr) - ((u8*) icmp + sizeof(ICMP6Hdr) - (u8*) ip) == obj->len &&
            memcmp(data, obj->data, (size_t) obj->len) == 0)
        {
            obj->callback = NULL;
            if (obj->result)
            {
                *obj->result = IP_ERR_NONE;
            }
            callback((ICMPInfo*) info, IP_ERR_NONE);
        }
    }
}

static void ICMP6Notify(const IP6Hdr* org, ICMP6Hdr* icmp, s32 err)
{
    IPInfo*      curr;
    IPInfo*      next;
    ICMP6Info*   info;
    ICMPCallback callback;
    ICMPObj*     obj;

    if (icmp->type != ICMP_ECHO_REQUEST)
    {
        return;
    }
    IFIterateQueue(IPInfo*, &ICMPInfoQueue, curr, next, link)
    {
        info = (ICMP6Info*) curr;
        obj  = ICMPGetObj((ICMPInfo*) info);
        if (obj->callback == NULL)
        {
            continue;
        }
        if (obj->seq != (icmp->data & 0x00ff) ||
            info->local.port != (icmp->data >> 16))
        {
            continue;
        }
        if (!SO_IN6_ARE_ADDR_EQUAL(&org->src, (SOIn6Addr*) &info->remote.addr) ||
            !SO_IN6_ARE_ADDR_EQUAL(&org->dst, (SOIn6Addr*) &info->local.addr))
        {
            continue;
        }

        callback = obj->callback;
        if (callback)
        {
            obj->callback = NULL;
            if (obj->result)
            {
                *obj->result = err;
            }
            callback((ICMPInfo*) info, err);
        }
    }
}

static void DoEchoRequest(IPInterface* interface, IP6Hdr* ip6, ICMP6Hdr* icmp6, s32 len, u32 flag)
{
    IFDatagram* datagram;
    IP6Hdr*     echo;
    ICMP6Hdr*   reply;
    s32         plen;
    IP6Entry*   linkLocal;
    IP6Entry*   nextHop;
    IP6Entry*   dst;

    // See local host addresses have been configured.
    linkLocal = interface->linkLocal;
    if (linkLocal == NULL || linkLocal->state == ND_STATE_TENTATIVE)
    {
        return;
    }

    if ((flag & IF_FLAG_BROADCAST) || SO_IN6_IS_ADDR_MULTICAST(&ip6->src))
    {
        return;
    }

    plen = len;

    ++interface->icmpv6Stat.outMsgs;

    datagram = ICMPAllocDatagram(interface, (s32) sizeof(IP6Hdr) + plen);
    if (datagram == NULL)
    {
        ++interface->icmpv6Stat.outErrors;
        return;
    }
    IFInitDatagram(datagram, ETH_IPv6, 1);
    echo = (IP6Hdr*) ((u8*) datagram + sizeof(IFDatagram));
    reply = (ICMP6Hdr*) ((u8*) echo + sizeof(IP6Hdr));

    if (!SO_IN6_IS_ADDR_MULTICAST(&ip6->dst))
    {
        echo->src = ip6->dst;
    }
    else
    {
        echo->src = linkLocal->addr;
    }
    echo->dst = ip6->src;
    echo->next = SO_IPPROTO_ICMPV6;
    echo->hops = interface->curHopLimit;
    echo->flow = 6u << 28;
    echo->plen = (u16) plen;

    memmove(reply, icmp6, (u32) len);
    reply->type = ICMP6_ECHO_REPLY;
    reply->cksum = 0;
    reply->cksum = ICMP6CheckSum(echo, reply, plen);

    datagram->vec[0].data = echo;
    datagram->vec[0].len = (s32) sizeof(IP6Hdr) + plen;

    nextHop = IP6GetNextNeighbor(interface, &echo->dst, &dst);
    datagram->mtu = (u16) IP6GetPathMTU(dst, datagram->vec[0].len);
    if (IP6Out(interface, datagram, nextHop) < 0)
    {
        // datagram has not been sent out. Must release memory
        ICMPFreeDatagram(datagram);
        interface->free(interface, datagram, (s32) (sizeof(IFDatagram) + sizeof(IP6Hdr) + plen));
    }
    else
    {
        ++interface->icmpv6Stat.outEchoReplies;
    }
}

static void DoTooBig(IPInterface* interface, ICMP6Hdr* icmp6, IP6Hdr* org)
{
    s32       mtu;
    s32       mss;
    IPInfo*   info;
    IPInfo*   next;
    IP6Entry* nextHop;
    IP6Entry* dst;

    mtu = (s32) MAX(sizeof(IP6Hdr) + TCP_MIN_HLEN + 8, icmp6->data);
    mtu = (s32) MIN(interface->linkMTU, mtu);

    nextHop = IP6GetNextNeighbor(interface, &org->dst, NULL);
    if (!nextHop)
    {
        return;
    }
    // Create destination cache for org->dst
    dst = GetNeighbor(interface, &org->dst, 128);
    if (dst)
    {
        if (dst != nextHop)
        {
            IP6SetNeighborState(dst, ND_STATE_DESTINATION);
            SetNetwork(dst, nextHop);
        }
        // A node MUST NOT increase its estimate of the Path MTU in response to
        // the contents of a Packet Too Big message. [RFC 1981]
        if (dst->mtu == 0)
        {
            dst->mtu = mtu;
        }
        else
        {
            dst->mtu = mtu = MIN(mtu, dst->mtu);
        }
        dst->lastTooBig = dst->lastUpdated = OSGetTime();
    }

    if (mtu < IP6_MIN_MTU)
    {
        // In response to an IPv6 packet that is sent to an IPv4 destination
        // (i.e., a packet that undergoes translation from IPv6 to IPv4), the
        // originating IPv6 node may receive an ICMP Packet Too Big message
        // reporting a Next-Hop MTU less than 1280.  [RFC 2460 5. Packet Size Issues]
        mtu = IP6_MIN_MTU;
    }

    // Set info->to to dst
    mss = mtu - (s32) sizeof(IP6Hdr) - TCP_MIN_HLEN;
    IFIterateQueue(IPInfo*, &TCPInfoQueue, info, next, link)
    {
        TCPObj* tcp;

        if (info->family != SO_AF_INET6 ||
            !SO_IN6_ARE_ADDR_EQUAL(&((SOSockAddrIn6*) IPGetRemoteSockAddr(info))->addr, &org->dst))
        {
            continue;
        }
        IP6SetDestination(info, dst);

        tcp = TCPGetObj((TCPInfo*) info);
        if (mss < tcp->mss)
        {
            tcp->mss = mss;
        }

        // Goes back to slow start without changing slow start threshold
        // like source quench
        tcp->cWin = TCP_IW(tcp);

        // XXX Rxmit segment
    }

    IFIterateQueue(IPInfo*, &UDPInfoQueue, info, next, link)
    {
        if (info->family != SO_AF_INET6 ||
            !SO_IN6_ARE_ADDR_EQUAL(&((SOSockAddrIn6*) IPGetRemoteSockAddr(info))->addr, &org->dst))
        {
            continue;
        }
        IP6SetDestination(info, dst);
        UDPAbort((UDPInfo*) info, IP_ERR_DATASIZE);
    }
}

// Compute internet header checksums
void ICMP6In(IPInterface* interface, IP6Hdr* ip6, ICMP6Hdr* icmp6, s32 len, u32 flag, int routerAlert)
{
    IP6Hdr*       org;
#ifdef IOP_OS
    u8*           hdr = NULL;
    s32           hlen;
    u8            next = 0;
#else
    u8*           hdr;
    s32           hlen;
    u8            next;
#endif
    ICMP6Hdr*     orgIcmp6;
    BOOL          abort = FALSE;

    ++interface->icmpv6Stat.inMsgs;
    if (len < sizeof(ICMP6Hdr) || ICMP6CheckSum(ip6, icmp6, len) != 0)
    {
        ++interface->icmpv6Stat.inErrors;
        return;
    }

    if (icmp6->type < 128)
    {
        if (flag & (IF_FLAG_BROADCAST | IF_FLAG_MULTICAST)) // (e.3, e.4)
        {
            ++interface->icmpv6Stat.inErrors;
            return;
        }

        // ICMPv6 error messages
        if (len < sizeof(ICMP6Hdr) + sizeof(IP6Hdr))
        {
            ++interface->icmpv6Stat.inErrors;
            return;
        }

        org = (IP6Hdr*) ((u8*) icmp6 + sizeof(ICMP6Hdr));

        // (e.5)
        if (SO_IN6_IS_ADDR_UNSPECIFIED(&org->src) ||
            SO_IN6_IS_ADDR_MULTICAST(&org->src))    // XXX or anycast address
        {
            ++interface->icmpv6Stat.inErrors;
            return;
        }

        hdr = (u8*) org + sizeof(IP6Hdr);
        len -= sizeof(ICMP6Hdr) + sizeof(IP6Hdr);
        next = org->next;
        while (next != SO_IPPROTO_NONE)
        {
            switch (next)
            {
              case SO_IPPROTO_HOPOPTS:
              case SO_IPPROTO_ROUTING:
              case SO_IPPROTO_FRAGMENT:
              case SO_IPPROTO_DSTOPTS:
              case SO_IPPROTO_AH:
              case SO_IPPROTO_ESP:
                if (len < 2)
                {
                    ++interface->icmpv6Stat.inErrors;
                    return;
                }
                hlen = (1 + hdr[1]) << 3;
                if (len < hlen)
                {
                    ++interface->icmpv6Stat.inErrors;
                    return;
                }
                next = hdr[0];
                len -= hlen;
                hdr += hlen;
                break;
              case IP_PROTO_UDP:
              case IP_PROTO_TCP:
                if (len < 0)
                {
                    ++interface->icmpv6Stat.inErrors;
                    return;
                }
                goto Found;
                break;
              case SO_IPPROTO_ICMPV6:
                orgIcmp6 = (ICMP6Hdr*) hdr;
                if (orgIcmp6->type < 128)
                {
                    ++interface->icmpv6Stat.inErrors;
                    return; // (e.1)
                }
                if (SO_IN6_IS_ADDR_MULTICAST(&org->dst))
                {
                    if (icmp6->type != ICMP6_PACKET_TOO_BIG &&
                        (icmp6->type != ICMP6_PARAM_PROB ||
                         icmp6->code != ICMP6_PARAMPROB_OPTION))
                    {
                        ++interface->icmpv6Stat.inErrors;
                        return; // (e.2)
                    }
                }
                goto Found;
                break;
              default:
                ++interface->icmpv6Stat.inErrors;
                return;
            }
        }
      Found:
        if (SO_IN6_ARE_ADDR_EQUAL(&org->dst, &ip6->src))
        {
            abort = TRUE;
        }
    }
    else
    {
        // ICMPv6 informational messages
        org = NULL;
    }

    //
    // Process ICMP message
    //
    switch (icmp6->type)
    {
      case ICMP6_DST_UNREACH:
        ++interface->icmpv6Stat.inDestUnreachs;
        if (icmp6->code == ICMP6_DST_UNREACH_ADMIN)
        {
            ++interface->icmpv6Stat.inAdminProhibs;
        }
        switch (next)
        {
          case IP_PROTO_UDP:
            UDP6Notify(org, (UDPHeader*) hdr, IP_ERR_UNREACHABLE);
            break;
          case IP_PROTO_TCP:
            switch (icmp6->code)
            {
              case ICMP6_DST_UNREACH_ADMIN:
              case ICMP6_DST_UNREACH_BEYONDSCOPE:
              case ICMP6_DST_UNREACH_NOPORT:
                abort = TRUE;
                break;
            }
            TCP6Notify(org, (TCPHeader*) hdr, IP_ERR_UNREACHABLE, abort);
            break;
          case SO_IPPROTO_ICMPV6:
            ICMP6Notify(org, (ICMP6Hdr*) hdr, IP_ERR_UNREACHABLE);
            break;
        }
        break;

      case ICMP6_PACKET_TOO_BIG:
        ++interface->icmpv6Stat.inPktTooBigs;
        DoTooBig(interface, icmp6, org);
        break;

      case ICMP6_TIME_EXCEEDED:
        ++interface->icmpv6Stat.inTimeExcds;
        switch (next)
        {
          case IP_PROTO_UDP:
            UDP6Notify(org, (UDPHeader*) hdr, IP_ERR_TIMEOUT);   // XXX define error code
            break;
          case IP_PROTO_TCP:
            TCP6Notify(org, (TCPHeader*) hdr, IP_ERR_TIMEOUT, abort);   // XXX define error code
            break;
          case SO_IPPROTO_ICMPV6:
            ICMP6Notify(org, (ICMP6Hdr*) hdr, IP_ERR_TIMEOUT);
            break;
        }
        break;

      case ICMP6_PARAM_PROB:
        ++interface->icmpv6Stat.inParmProblems;
        switch (next)
        {
          case IP_PROTO_UDP:
            UDP6Notify(org, (UDPHeader*) hdr, IP_ERR_INVALID);   // XXX define error code
            break;
          case IP_PROTO_TCP:
            TCP6Notify(org, (TCPHeader*) hdr, IP_ERR_INVALID, abort);   // XXX define error code
            break;
          case SO_IPPROTO_ICMPV6:
            ICMP6Notify(org, (ICMP6Hdr*) hdr, IP_ERR_INVALID);
            break;
        }
        break;

      case ICMP6_ECHO_REQUEST:
        ++interface->icmpv6Stat.inEchos;
        DoEchoRequest(interface, ip6, icmp6, len, flag);
        break;

      case ICMP6_ECHO_REPLY:
        ++interface->icmpv6Stat.inEchoReplies;
        DoEchoReply(interface, ip6, icmp6, len, flag);
        break;

      case ND_ROUTER_SOLICIT:
        ++interface->icmpv6Stat.inRouterSolicits;
        break;
      case ND_ROUTER_ADVERT:
        if (ip6->hops != 255 || len < sizeof(NDRouterAdvert))
        {
            ++interface->icmpv6Stat.inErrors;
            return;
        }
        ++interface->icmpv6Stat.inRouterAdvertisements;
        DoRouterAdvert(interface, ip6, (NDRouterAdvert*) icmp6, len);
        break;

      case ND_NEIGHBOR_SOLICIT:
        if (ip6->hops != 255 || len < sizeof(NDNeighborSolicit))
        {
            ++interface->icmpv6Stat.inErrors;
            return;
        }
        ++interface->icmpv6Stat.inNeighborSolicits;
        DoNeighborSolicit(interface, ip6, (NDNeighborSolicit*) icmp6, len, flag);
        break;
      case ND_NEIGHBOR_ADVERT:
        if (ip6->hops != 255 || len < sizeof(NDNeighborAdvert))
        {
            ++interface->icmpv6Stat.inErrors;
            return;
        }
        ++interface->icmpv6Stat.inNeighborAdvertisements;
        DoNeighborAdvert(interface, ip6, (NDNeighborAdvert*) icmp6, len, flag);
        break;

      case ND_REDIRECT:
        if (ip6->hops != 255 || len < sizeof(NDRedirect))
        {
            ++interface->icmpv6Stat.inErrors;
            return;
        }
        ++interface->icmpv6Stat.inRedirects;
        DoRedirect(interface, ip6, (NDRedirect*) icmp6, len);
        break;

      case MLD_LISTENER_QUERY:
        // Unrecognized value fields MUST be silently ignored and the processing
        // of the header continued. [RTR-ALERT]
        if (ip6->hops != 1 || !SO_IN6_IS_ADDR_LINKLOCAL(&ip6->src) || routerAlert < 0)
        {
            ++interface->icmpv6Stat.inErrors;
            return;
        }
        ++interface->icmpv6Stat.inGroupMembQueries;
        MLDDoListenerQuery(interface, (ICMP6MldHder*) icmp6);
        break;
      case MLD_LISTENER_REPORT:
        // Unrecognized value fields MUST be silently ignored and the processing
        // of the header continued. [RTR-ALERT]
        if (ip6->hops != 1 || !SO_IN6_IS_ADDR_LINKLOCAL(&ip6->src) || routerAlert < 0)
        {
            ++interface->icmpv6Stat.inErrors;
            return;
        }
        ++interface->icmpv6Stat.inGroupMembResponses;
        MLDDoListenerReport(interface, (ICMP6MldHder*) icmp6);
        break;
      case MLD_LISTENER_REDUCTION:
        // Unrecognized value fields MUST be silently ignored and the processing
        // of the header continued. [RTR-ALERT]
        if (ip6->hops != 1 || !SO_IN6_IS_ADDR_LINKLOCAL(&ip6->src) || routerAlert < 0)
        {
            ++interface->icmpv6Stat.inErrors;
            return;
        }
        ++interface->icmpv6Stat.inGroupMembReductions;
        break;

      default:
        if (icmp6->type < 128)
        {
            // If an ICMPv6 error message of unknown type is received, it MUST
            // be passed to the upper layer. [RFC 2463]
            switch (next)
            {
              case IP_PROTO_UDP:
                UDP6Notify(org, (UDPHeader*) hdr, IP_ERR_INVALID);
                break;
              case IP_PROTO_TCP:
                TCP6Notify(org, (TCPHeader*) hdr, IP_ERR_INVALID, abort);
                break;
              case SO_IPPROTO_ICMPV6:
                ICMP6Notify(org, (ICMP6Hdr*) hdr, IP_ERR_INVALID);
                break;
            }
        }
        break;
    }
}

static BOOL Hit(const u8* prefix, const u8* addr, u8 prefixLen)
{
    int i;

    for (i = 0; i < prefixLen / 8; ++i)
    {
        if (prefix[i] != addr[i])
        {
            return FALSE;
        }
    }
    if (i < 16)
    {
        if (prefix[i] != (addr[i] & ~(0xff >> (prefixLen % 8))))
        {
            return FALSE;
        }
    }
    return TRUE;
}

static IP6Entry* IP6LookupPrefix(const SOIn6Addr* addr, u8 prefixLen)
{
    OSTime    now;
    IP6Entry* prefix;
    IP6Entry* next;

    // multicast address and is considered to be on-link.
    ASSERT(!SO_IN6_IS_ADDR_MULTICAST(addr));

    now = OSGetTime();
    IFIterateQueue(IP6Entry*, &NDCache, prefix, next, link)
    {
        if (prefix->prefixLen < prefixLen)
        {
            break;
        }
        if (prefix->state != ND_STATE_PREFIX && prefix->state != ND_STATE_DESTINATION)
        {
            continue;
        }
        if (prefix->validTime <= now)
        {
            IP6SetNeighborState(prefix, ND_STATE_INVALID);
            IP6PutNeighbor(prefix);
            continue;
        }
        if (prefix->prefixLen != prefixLen)
        {
            continue;
        }
        if (Hit(prefix->addr.addr, addr->addr, prefixLen))
        {
            return prefix;
        }
    }
    return NULL;
}

static IP6Entry* GetNeighbor(IPInterface* interface, const SOIn6Addr* addr, u8 prefixLen)
{
    IP6Entry* neighbor;
    IP6Entry* next;
    IP6Entry* free;
    IP6Entry* stale;
    IP6Entry* insert;
    OSTime    now;
    int       i;
    s32       ref;

    interface = interface ? interface : &__IFDefault;

    ASSERT(0 < prefixLen);
    now = OSGetTime();
    free = stale = insert = NULL;
    IFIterateQueue(IP6Entry*, &NDCache, neighbor, next, link)
    {
        ASSERT(0 <= neighbor->ref);

        if ((neighbor->flags & ND_FLAG_IS_ROUTER) && neighbor->routerLifetime <= now)
        {
            switch (neighbor->state)
            {
              case ND_STATE_INIT:
              case ND_STATE_INCOMPLETE:
              case ND_STATE_REACHABLE:
              case ND_STATE_STALE:
              case ND_STATE_DELAY:
              case ND_STATE_PROBE:
                ref = neighbor->ref;
                IP6SwitchToHost(neighbor);
                if (ref == 1)
                {
                    continue;
                }
                break;
            }
        }

        if (neighbor->validTime <= now)
        {
            switch (neighbor->state)
            {
              case ND_STATE_DESTINATION:
              case ND_STATE_PREFIX:
                IP6SetNeighborState(neighbor, ND_STATE_INVALID);
                IP6PutNeighbor(neighbor);
                continue;
                break;
            }
        }

        if (neighbor->state != ND_STATE_INVALID &&
            neighbor->prefixLen == prefixLen &&
            Hit(neighbor->addr.addr, addr->addr, neighbor->prefixLen))
        {
            neighbor->interface = interface;
            return neighbor;
        }

        if (insert == NULL && neighbor->prefixLen < prefixLen)
        {
            insert = neighbor;
        }

        if (free == NULL)
        {
            switch (neighbor->state)
            {
              case ND_STATE_INVALID:
                if (neighbor->ref <= 0)
                {
                    free = neighbor;
                    if (free == insert)
                    {
                        insert = next;
                    }
                }
                break;
              case ND_STATE_INIT:
              case ND_STATE_INCOMPLETE:
              case ND_STATE_REACHABLE:
              case ND_STATE_STALE:
              case ND_STATE_DELAY:
              case ND_STATE_PROBE:
              case ND_STATE_NON_LISTENER:
              case ND_STATE_DESTINATION:
                ASSERT(0 < neighbor->ref);
                if ((neighbor->flags & ND_FLAG_IS_ROUTER) || 1 < neighbor->ref ||
                    (neighbor->mtu < interface->linkMTU &&
                     neighbor->lastTooBig + OSSecondsToTicks(10 * 60LL) <= now))
                {
                    break;
                }
                if (stale == NULL || stale->state < neighbor->state)
                {
                    stale = neighbor;
                    if (stale == insert)
                    {
                        insert = next;
                    }
                }
                break;
            }
        }

        if (free)
        {
            break;
        }
    }

    if (free == NULL)
    {
        if (stale == NULL)
        {
            return NULL;
        }
        IP6PutNeighbor(stale);
        free = stale;
    }
    ASSERT(free->ref == 0);

    IFDequeueItem(IP6Entry*, &NDCache, free, link);
    memset(free, 0, sizeof(IP6Entry));

    IP6RefNeighbor(free);
    OSCreateAlarm(&free->alarm);
    IFInitQueue(&free->queueNext);
    IFInitQueue(&free->queueFrom);
    IFInitQueue(&free->queueTo);
    IFInitQueue(&free->queueNetwork);
    free->routerLifetime = free->validTime = free->preferredTime = free->lastTooBig = -OS_TIME_INFINITE;
    free->interface = interface;
    free->mtu = 1500;
    free->lastUpdated = now;

    for (i = 0; i < prefixLen / 8; ++i)
    {
        free->addr.addr[i] = addr->addr[i];
    }
    if (i < 16)
    {
        free->addr.addr[i] = (u8) (addr->addr[i] & ~(0xff >> (prefixLen % 8)));
    }
    free->prefixLen = prefixLen;

    if (insert)
    {
        IFEnqueueBefore(IP6Entry*, &NDCache, free, insert, link);
    }
    else
    {
        IFEnqueueTail(IP6Entry*, &NDCache, free, link);
    }

    IP6SetNeighborState(free, ND_STATE_INIT);
    if (SO_IN6_IS_ADDR_MULTICAST(addr))
    {
        IP6SetNeighborState(free, ND_STATE_NON_LISTENER);

        // XXX The following lines are the Ethernet specific code.
        free->linkAddr[0] = 0x33;
        free->linkAddr[1] = 0x33;
        free->linkAddr[2] = addr->addr[12];
        free->linkAddr[3] = addr->addr[13];
        free->linkAddr[4] = addr->addr[14];
        free->linkAddr[5] = addr->addr[15];
    }
    return free;
}

IP6Entry* IP6GetNeighbor(IPInterface* interface, const SOIn6Addr* addr)
{
    return GetNeighbor(interface, addr, 128);
}

static IP6Entry* AllocPrefix(const SOIn6Addr* prefix, u8 prefixLen)
{
    IP6Entry* dest;

    // multicast address is considered to be on-link.
    ASSERT(!SO_IN6_IS_ADDR_MULTICAST(prefix));
    dest = GetNeighbor(&__IFDefault, prefix, prefixLen);
    if (dest)
    {
        IP6SetNeighborState(dest, ND_STATE_PREFIX);
    }
    return dest;
}

static IP6Entry* AllocDestination(const SOIn6Addr* prefix, u8 prefixLen)
{
    IP6Entry* dest;

    // multicast address is considered to be on-link.
    ASSERT(!SO_IN6_IS_ADDR_LINKLOCAL(prefix));
    ASSERT(!SO_IN6_IS_ADDR_MULTICAST(prefix));
    if (SO_IN6_IS_ADDR_LINKLOCAL(prefix) ||
        SO_IN6_IS_ADDR_MULTICAST(prefix))
    {
        return NULL;
    }
    dest = GetNeighbor(&__IFDefault, prefix, prefixLen);
    if (dest)
    {
        IP6SetNeighborState(dest, ND_STATE_DESTINATION);
        SetNetwork(dest, NULL);
    }
    return dest;
}

void IP6Shuffle(IP6Entry* router)
{
    IP6Entry* next;

    for (next = (IP6Entry*) IFQueryLinkNext(router, link);
         next;
         next = (IP6Entry*) IFQueryLinkNext(next, link))
    {
        if (next->prefixLen < router->prefixLen)
        {
            break;
        }
    }

    IFDequeueItem(IP6Entry*, &NDCache, router, link);
    if (next)
    {
        IFEnqueueBefore(IP6Entry*, &NDCache, router, next, link);
    }
    else
    {
        IFEnqueueTail(IP6Entry*, &NDCache, router, link);
    }
}

IP6Entry* IP6SearchNeighbor(const SOIn6Addr* addr)
{
    IP6Entry* neighbor;
    IP6Entry* next;

    IFIterateQueue(IP6Entry*, &NDCache, neighbor, next, link)
    {
        ASSERT(0 <= neighbor->ref);
        if (neighbor->state != ND_STATE_INVALID &&
            SO_IN6_ARE_ADDR_EQUAL(addr, &neighbor->addr))
        {
            break;
        }
    }
    return neighbor;
}

// Get next-hop for addr
IP6Entry* IP6GetNextNeighbor(IPInterface* interface, const SOIn6Addr* addr, IP6Entry** dst)
{
    IP6Entry* prefix;
    IP6Entry* neighbor;
    IP6Entry* router;
    IP6Entry* next;
    OSTime    now;
    IP6Entry* null;

    if (!dst)
    {
        dst = &null;
    }

    // multicast address is considered to be on-link.
    if (SO_IN6_IS_ADDR_MULTICAST(addr))
    {
        neighbor = IP6GetNeighbor(interface, addr);
        *dst = neighbor;
        return neighbor;
    }

    // Perform longest prefix match
    now = OSGetTime();
    router = NULL;
    IFIterateQueue(IP6Entry*, &NDCache, prefix, next, link)
    {
        if (prefix->prefixLen == 0)
        {
            prefix = NULL;
            break;
        }
        if (prefix->state == ND_STATE_PREFIX ||
            prefix->state == ND_STATE_DESTINATION)
        {
            if (prefix->validTime <= now)
            {
                IP6SetNeighborState(prefix, ND_STATE_INVALID);
                IP6PutNeighbor(prefix);
                continue;
            }
        }
        if (Hit(prefix->addr.addr, addr->addr, prefix->prefixLen))
        {
            break;
        }
    }

    if (prefix)
    {
        switch (prefix->state)
        {
          case ND_STATE_PREFIX:
            // on-link
            neighbor = IP6GetNeighbor(interface, addr);
            if (neighbor)
            {
                SetNetwork(neighbor, prefix);
            }
            *dst = neighbor;
            return neighbor;
            break;
          case ND_STATE_DESTINATION:
            // redirected
            if (prefix->network)
            {
                if (prefix->prefixLen == 128)
                {
                    *dst = prefix;
                }
                else
                {
                    *dst = NULL;
                }
                return prefix->network;
            }
            // select a default router
            break;
          default:
            neighbor = IP6GetNeighbor(interface, addr);
            *dst = neighbor;
            return neighbor;
            break;
        }
    }

    // Select default router [RFC 2461  6.3.6.]
    IFIterateQueue(IP6Entry*, &NDCache, neighbor, next, link)
    {
        if (neighbor->prefixLen == 0)
        {
            break;
        }
        if (neighbor->state != ND_STATE_INVALID && (neighbor->flags & ND_FLAG_IS_ROUTER))
        {
            if (neighbor->routerLifetime == OS_TIME_INFINITE)
            {
                continue;   // Not a default router
            }
            if (neighbor->routerLifetime <= now)
            {
                IP6SwitchToHost(neighbor);
                continue;
            }
            if (!router ||
                (router->state <= ND_STATE_INCOMPLETE &&
                 ND_STATE_INCOMPLETE < neighbor->state))
            {
                router = neighbor;
                IP6Shuffle(router);
            }
        }
    }
    neighbor = router;

    if (neighbor == 0)
    {
        // If the Default Router List is empty,
        // the sender assumes that the destination is on-link. [RFC 2461]
        neighbor = IP6GetNeighbor(interface, addr);
        if (neighbor && prefix && prefix->prefixLen < 128)
        {
            SetNetwork(neighbor, prefix);
        }
        *dst = neighbor;
    }
    else
    {
        *dst = NULL;
    }

    return neighbor;
}

static void DiscardPendingPackets(IP6Entry* neighbor, s32 result)
{
    IPInterface* interface;
    IFDatagram*  datagram;

    interface = neighbor->interface;
    while (!IFIsEmptyQueue(&neighbor->queue))
    {
        IFDequeueHead(IFDatagram*, &neighbor->queue, datagram, link);
        ASSERT(datagram->queue == &neighbor->queue);
        ASSERT(datagram->interface == interface);
        // Now the datagram must be discarded and cannot be canceled.
        // Clear 'interface' and 'queue' to make sure the datagram won't be
        // canceled from now on.
        datagram->interface = NULL;
        datagram->queue = NULL;
        if (datagram->callback)
        {
            datagram->callback(datagram->param, result);
        }
        ICMPFreeDatagram(datagram);
    }
}

void IP6RefNeighbor(IP6Entry* neighbor)
{
    ++neighbor->ref;
}

void IP6PutNeighbor(IP6Entry* neighbor)
{
    IPInterface* interface;

    ASSERT(0 <= neighbor->ref);
    if (--neighbor->ref <= 0)
    {
        IP6SetNeighborState(neighbor, ND_STATE_INVALID);
        ASSERT(IFIsEmptyQueue(&neighbor->queue));
        ASSERT(IFIsEmptyQueue(&neighbor->queueNext));
        ASSERT(IFIsEmptyQueue(&neighbor->queueFrom));
        ASSERT(IFIsEmptyQueue(&neighbor->queueNetwork));
        interface = neighbor->interface;
        if (interface && interface->linkLocal == neighbor)
        {
            interface->linkLocal = NULL;
        }
        neighbor->prefixLen = 0;
        IFDequeueItem(IP6Entry*, &NDCache, neighbor, link);
        IFEnqueueTail(IP6Entry*, &NDCache, neighbor, link);
    }
}

static void Recover(IP6Entry* router)
{
    IPInfo* info;
    IPInfo* next;

    IFIterateQueue(IPInfo*, &router->queueNext, info, next, linkNext)
    {
        IP6SetNextHop(info, NULL);
    }
    IP6Shuffle(router);
}

void IP6SwitchToHost(IP6Entry* router)
{
    IP6Entry* prefix;
    IP6Entry* next;
#ifndef IOP_OS
    OSTime    now = OSGetTime();
#endif // IOP_OS

    if (!(router->flags & ND_FLAG_IS_ROUTER))
    {
        return;
    }

    // All IPInfo entries using this router MUST perform next-hop
    // determination again.
    Recover(router);

    // Remove this router from the Default Router List
    router->flags &= ~ND_FLAG_IS_ROUTER;

    // Update target
    IFIterateQueue(IP6Entry*, &router->queueNetwork, prefix, next, link)
    {
        SetNetwork(prefix, NULL);
    }

    IP6PutNeighbor(router);
}

void IP6SwitchToRouter(IP6Entry* neighbor, OSTime routerLifetime)
{
    if (!(neighbor->flags & ND_FLAG_IS_ROUTER))
    {
        IP6RefNeighbor(neighbor);
    }
    neighbor->flags |= ND_FLAG_IS_ROUTER;
    if (routerLifetime == OS_TIME_INFINITE)
    {
        if (neighbor->routerLifetime <= OSGetTime())
        {
            neighbor->routerLifetime = OS_TIME_INFINITE;
        }
    }
    else
    {
        neighbor->routerLifetime = routerLifetime;
    }
}

static void Revalidate(IP6Entry* neighbor)
{
    IPInterface* interface;
    SOIn6Addr    solicited;

    interface = neighbor->interface;
    switch (neighbor->state)
    {
      case ND_STATE_DELAY:
        IP6SetNeighborState(neighbor, ND_STATE_PROBE);
        neighbor->count = 0;
        // FALL THROUGH
      case ND_STATE_INCOMPLETE:
      case ND_STATE_PROBE:
        if (neighbor->count < MAX_MULTICAST_SOLICIT)
        {
            ++neighbor->count;
            if (neighbor->state == ND_STATE_INCOMPLETE)
            {
                ICMP6Out(neighbor, ND_NEIGHBOR_SOLICIT, IP6GetSolicited(&neighbor->addr, &solicited));
            }
            else
            {
                ICMP6Out(neighbor, ND_NEIGHBOR_SOLICIT, &neighbor->addr);
            }
            OSSetAlarm(&neighbor->alarm, interface->retransTimer, IP6NeighborTimeout);
        }
        else
        {
            if (neighbor->flags & ND_FLAG_IS_ROUTER)
            {
                if (OSGetTime() < neighbor->routerLifetime)
                {
                    // All IPInfo entries using this router MUST perform next-hop
                    // determination again.
                    Recover(neighbor);
                    IP6SetNeighborState(neighbor, ND_STATE_INIT);
                }
                else
                {
                    IP6SwitchToHost(neighbor);
                    IP6SetNeighborState(neighbor, ND_STATE_INVALID);
                }
            }
            else
            {
                IP6SetNeighborState(neighbor, ND_STATE_INVALID);
            }
            IP6PutNeighbor(neighbor);
        }
        break;
    }
}

void IP6NeighborTimeout(OSAlarm* alarm, OSContext* context)
{
#ifdef IOP_OS
    TCPIP_UNUSED(context);
#else
    #pragma unused(context)
#endif // IOP_OS
    IP6Entry* neighbor;

    neighbor = (IP6Entry*) ((u8*) alarm - offsetof(IP6Entry, alarm));
    switch (neighbor->state)
    {
      case ND_STATE_INCOMPLETE:
      case ND_STATE_REACHABLE:
      case ND_STATE_STALE:
      case ND_STATE_DELAY:
      case ND_STATE_PROBE:
        Revalidate(neighbor);
        break;

      case ND_STATE_TENTATIVE:
      case ND_STATE_PREFERRED:
      case ND_STATE_DEPRECATED:
        IP6SetNeighborState(neighbor, ND_STATE_INVALID);
        IP6PutNeighbor(neighbor);
        break;
    }
}

static void DoRouterAdvert(IPInterface* interface, IP6Hdr* ip6, NDRouterAdvert* ra, s32 len)
{
    IP6Entry* router;
    NDOptHdr* opt;
#ifndef IOP_OS
    BOOL      update = FALSE;
#endif // IOP_OS
    s32       olen;
    s32       plen = 0; // len after the first NDOptPrefixInfo.

    NDOptLinkAddrEthernet*  optLinkAddr = NULL;
    NDOptPrefixInfo*        optPrefix = NULL;
    NDOptMtu*               optMtu = NULL;

    OSTime now;

    if (ra->code != 0)
    {
        return;
    }

    if (!SO_IN6_IS_ADDR_LINKLOCAL(&ip6->src))
    {
        return;
    }

    opt = (NDOptHdr*) ((u8*) ra + sizeof(NDRouterAdvert));
    len -= sizeof(NDRouterAdvert);
    while (0 < len)
    {
        if (len < 2)
        {
            return;
        }
        olen = opt->len << 3;
        if (len < olen ||
            olen <= 0)      // All included options have a length that is greater than zero. [RFC 2461]
        {
            return;
        }

        switch (opt->type)
        {
          case ND_OPT_SOURCE_LINKADDR:
            if (olen < sizeof(NDOptLinkAddrEthernet))
            {
                return;
            }
            optLinkAddr = (NDOptLinkAddrEthernet*) opt;
            break;
          case ND_OPT_PREFIX_INFORMATION:
            if (olen < sizeof(NDOptPrefixInfo))
            {
                return;
            }
            if (optPrefix == NULL)
            {
                optPrefix = (NDOptPrefixInfo*) opt;
                plen = len;
            }
            break;
          case ND_OPT_MTU:
            if (olen < sizeof(NDOptMtu))
            {
                return;
            }
            optMtu = (NDOptMtu*) opt;
            break;
        }

        opt = (NDOptHdr*) ((u8*) opt + olen);
        len -= olen;
    }

    now = OSGetTime();

    router = IP6SearchNeighbor(&ip6->src);
    if (0 < ra->routerLifetime)
    {
        if (router == NULL)
        {
            router = IP6GetNeighbor(interface, &ip6->src);
            ASSERT(router->state == ND_STATE_INIT);
        }
        IP6SwitchToRouter(router, NDTime(now, ra->routerLifetime));
    }
    else
    {
        if (router)
        {
            IP6SwitchToHost(router);   // immediately time-out the entry
        }
        return;
        // NOT REACHED HERE
    }

    if (0 < ra->curHopLimit)
    {
        interface->curHopLimit = ra->curHopLimit;
    }

    if (0 < ra->reachable)
    {
        OSTime reachable = OSMillisecondsToTicks((OSTime) ra->reachable);

        if (reachable != interface->baseReachableTime)
        {
            interface->baseReachableTime = reachable;
        }
        interface->reachableTime = IPRandTime(interface,
                                              MIN_RANDOM_FACTOR(interface->baseReachableTime),
                                              MAX_RANDOM_FACTOR(interface->baseReachableTime));
    }

    if (0 < ra->retransmit)
    {
        interface->retransTimer = OSMillisecondsToTicks(ra->retransmit);
    }

    if (optLinkAddr)
    {
        if (memcmp(router->linkAddr, optLinkAddr->addr, ETH_ALEN) != 0)
        {
            // link-layer address is changed
            IP6SetNeighborState(router, ND_STATE_STALE);
            memmove(router->linkAddr, optLinkAddr->addr, ETH_ALEN);
        }
    }

    if (optMtu && IP6_MIN_MTU <= optMtu->mtu && optMtu->mtu <= interface->linkMTU)
    {
        interface->linkMTU = (s32) optMtu->mtu;
    }

    for (len = plen; 0 < len; len -= olen)
    {
        ASSERT(optPrefix);

        if (optPrefix->type != ND_OPT_PREFIX_INFORMATION ||
            optPrefix->validTime < optPrefix->preferredTime ||
            SO_IN6_IS_ADDR_LINKLOCAL(&optPrefix->prefix) ||
            optPrefix->prefixLen != 64)
        {
            goto Ignore;
        }

        if (optPrefix->flagsReserved & ND_OPT_PI_FLAG_ONLINK)
        {
            IP6Entry* prefix;

            // Follow steps described in Section 6.3.4. and 6.3.5. [RFC 2461]
            prefix = IP6LookupPrefix(&optPrefix->prefix, optPrefix->prefixLen);
            if (optPrefix->validTime)
            {
                if (prefix == NULL)
                {
                    prefix = AllocPrefix(&optPrefix->prefix, optPrefix->prefixLen);
                }
                if (prefix)
                {
                    // since the effect of the same denial of service targeted at
                    // the on-link prefix list is not catastrophic (hosts would send packets
                    // to a default router and receive a redirect rather than sending
                    // packets directly to a neighbor) the Neighbor Discovery protocol does
                    // not impose such a check on the prefix lifetime values. [RFC 2461]
                    prefix->preferredTime = NDTime(now, optPrefix->preferredTime);
                    prefix->validTime = NDTime(now, optPrefix->validTime);
                    prefix->flags |= ND_FLAG_ON_LINK;
                    if (optPrefix->flagsReserved & ND_OPT_PI_FLAG_AUTO)
                    {
                        prefix->flags |= ND_FLAG_AUTONOMOUS;
                    }
                }
            }
            else if (prefix)
            {
                // Time-out the prefix immediately
                IP6SetNeighborState(prefix, ND_STATE_INVALID);
                IP6PutNeighbor(prefix);
            }
        }

        if (optPrefix->flagsReserved & ND_OPT_PI_FLAG_AUTO)
        {
            SOIn6Addr addr;

            memcpy(addr.addr, optPrefix->prefix.addr, 8);
            memcpy(&addr.addr[8], interface->eui64, 8);
            IP6Claim(interface, &addr, optPrefix->validTime, optPrefix->preferredTime, ND_FLAG_AUTONOMOUS);
        }

    Ignore:
        olen = optPrefix->len << 3;
        optPrefix = (NDOptPrefixInfo*) ((u8*) optPrefix + olen);
    }
}

static void DoNeighborAdvert(IPInterface* interface, IP6Hdr* ip6, NDNeighborAdvert* na, s32 len, u32 flag)
{
    IP6Entry* neighbor;
    NDOptLinkAddrEthernet*
              opt;
    NDOptLinkAddrEthernet*
              optLinkAddr;
    BOOL      update = FALSE;
    s32       olen;

    if (na->code != 0 || SO_IN6_IS_ADDR_MULTICAST(&na->target))
    {
        return;
    }
    if (SO_IN6_IS_ADDR_MULTICAST(&ip6->dst) && (na->flagsReserved & ND_NA_FLAG_SOLICITED))
    {
        return;
    }

    optLinkAddr = NULL;
    opt = (NDOptLinkAddrEthernet*) ((u8*) na + sizeof(NDNeighborAdvert));
    len -= sizeof(NDNeighborAdvert);
    while (0 < len)
    {
        if (len < 2)
        {
            return;
        }
        olen = opt->len << 3;
        if (len < olen ||
            olen <= 0)      // All included options have a length that is greater than zero. [RFC 2461]
        {
            return;
        }
        if (opt->type == ND_OPT_TARGET_LINKADDR)
        {
            optLinkAddr = opt;
        }
        opt = (NDOptLinkAddrEthernet*) ((u8*) opt + olen);
        len -= olen;
    }

    neighbor = IP6SearchNeighbor(&na->target);
    if (neighbor == NULL || neighbor->interface != interface)
    {
        // If no entry exists, the advertisement SHOULD be silently discarded.
        return;
    }

    switch (neighbor->state)
    {
      case ND_STATE_INCOMPLETE:
        if (optLinkAddr == NULL)
        {
            return;
        }
        memmove(neighbor->linkAddr, optLinkAddr->addr, ETH_ALEN);
        if (na->flagsReserved & ND_NA_FLAG_SOLICITED)
        {
            IP6SetNeighborState(neighbor, ND_STATE_REACHABLE);
        }
        else
        {
            IP6SetNeighborState(neighbor, ND_STATE_STALE);
        }
        if (na->flagsReserved & ND_NA_FLAG_ROUTER)
        {
            IP6SwitchToRouter(neighbor, OS_TIME_INFINITE);
        }
        else
        {
            IP6SwitchToHost(neighbor);
        }

        if (!IFIsEmptyQueue(&neighbor->queue))
        {
            // Transmit waiting packets using the sender's address
            if (neighbor->state == ND_STATE_STALE)
            {
                IP6SetNeighborState(neighbor, ND_STATE_DELAY);
            }
            do {
                IFDatagram* datagram;

                IFDequeueHead(IFDatagram*, &neighbor->queue, datagram, link);
                ASSERT(datagram->queue == &neighbor->queue);
                ASSERT(datagram->type == ETH_IPv6);
                datagram->queue = NULL;

                // XXX The following line is the Ethernet specific code.
                memmove(datagram->hwAddr, neighbor->linkAddr, ETH_ALEN);
                datagram->type = ETH_IPv6;
                interface->out(interface, datagram);
            } while (!IFIsEmptyQueue(&neighbor->queue));
        }
        break;

      case ND_STATE_REACHABLE:
      case ND_STATE_STALE:
      case ND_STATE_DELAY:
      case ND_STATE_PROBE:
        if (!(na->flagsReserved & ND_NA_FLAG_OVERRIDE) &&
            optLinkAddr &&
            memcmp(neighbor->linkAddr, optLinkAddr->addr, ETH_ALEN) != 0)
        {
            switch (neighbor->state)
            {
              case ND_STATE_REACHABLE:
                IP6SetNeighborState(neighbor, ND_STATE_STALE);
                break;
              default:
                break;
            }
            return;
        }

        if (optLinkAddr)
        {
            update = (memcmp(neighbor->linkAddr, optLinkAddr->addr, ETH_ALEN) != 0);
        }

        if ((na->flagsReserved & ND_NA_FLAG_OVERRIDE) ||
            optLinkAddr == NULL || !update)
        {
            if (optLinkAddr)
            {
                memmove(neighbor->linkAddr, optLinkAddr->addr, ETH_ALEN);
            }
            if (na->flagsReserved & ND_NA_FLAG_SOLICITED)
            {
                IP6SetNeighborState(neighbor, ND_STATE_REACHABLE);
            }
            else if (optLinkAddr && update) //link-layer address was updated?
            {
                IP6SetNeighborState(neighbor, ND_STATE_STALE);
            }
        }
        if (na->flagsReserved & ND_NA_FLAG_ROUTER)
        {
            IP6SwitchToRouter(neighbor, OS_TIME_INFINITE);
        }
        else
        {
            IP6SwitchToHost(neighbor);
        }
        break;

      case ND_STATE_TENTATIVE:
        // [ADDRCONF]
        if (flag == IF_FLAG_LOOPBACK)
        {
            break;
        }
        IP6SetNeighborState(neighbor, ND_STATE_INVALID);
        IPSetConfigError(interface, IP_ERR_ADDR_COLLISION);
        IP6PutNeighbor(neighbor);
        break;

      case ND_STATE_PREFERRED:
      case ND_STATE_DEPRECATED:
        break;

      default:
        break;
    }
}

static void DoNeighborSolicit(IPInterface* interface, IP6Hdr* ip6, NDNeighborSolicit* ns, s32 len, u32 flag)
{
    IP6Entry* neighbor;
    NDOptLinkAddrEthernet*
              opt;
    NDOptLinkAddrEthernet*
              optLinkAddr;
    s32       olen;

    if (ns->code != 0 || SO_IN6_IS_ADDR_MULTICAST(&ns->target))
    {
        return;
    }

    optLinkAddr = NULL;
    opt = (NDOptLinkAddrEthernet*) ((u8*) ns + sizeof(NDNeighborSolicit));
    len -= sizeof(NDNeighborSolicit);
    while (0 < len)
    {
        if (len < 2)
        {
            return;
        }
        olen = opt->len << 3;
        if (len < olen ||
            olen <= 0)      // All included options have a length that is greater than zero. [RFC 2461]
        {
            return;
        }
        if (opt->type == ND_OPT_SOURCE_LINKADDR)
        {
            optLinkAddr = opt;
        }
        opt = (NDOptLinkAddrEthernet*) ((u8*) opt + olen);
        len -= olen;
    }

    if (SO_IN6_IS_ADDR_UNSPECIFIED(&ip6->src))
    {
        // If the IP source address is the unspecified address, ...
        if (!IP6IsSolicited(&ip6->dst))
        {
            //  the IP destination address is a solicited-node multicast address. [RFC 2461]
            return;
        }
        if (optLinkAddr)
        {
            // there is no source link-layer address option in the message. [RFC 2461]
            return;
        }
    }

    neighbor = IP6SearchNeighbor(&ns->target);
    if (neighbor == NULL || neighbor->interface != interface)
    {
        return;
    }

    switch (neighbor->state)
    {
      case ND_STATE_INVALID:
        break;

      case ND_STATE_INIT:
      case ND_STATE_INCOMPLETE:
      case ND_STATE_REACHABLE:
      case ND_STATE_STALE:
      case ND_STATE_DELAY:
      case ND_STATE_PROBE:
        break;

      case ND_STATE_TENTATIVE:
        // [ADDRCONF]
        if (flag == IF_FLAG_LOOPBACK)
        {
            break;
        }
        if (SO_IN6_IS_ADDR_UNSPECIFIED(&ip6->src))
        {
            IP6SetNeighborState(neighbor, ND_STATE_INVALID);
            IPSetConfigError(interface, IP_ERR_ADDR_COLLISION);
            IP6PutNeighbor(neighbor);
        }
        break;

      case ND_STATE_PREFERRED:
      case ND_STATE_DEPRECATED:
        // Send a Neighbor Advertisement response
        if (SO_IN6_IS_ADDR_UNSPECIFIED(&ip6->src))
        {
            // if the solicitation's Source Address is the unspecified
            // address, the all-nodes multicast address. [RFC 2461]
            ICMP6Out(neighbor, ND_NEIGHBOR_ADVERT, &SOIn6AddrLinkLocalAllNodes);
        }
        else
        {
            // If the Source Address is not the unspecified
            // address and, on link layers that have addresses, the solicitation
            // includes a Source Link-Layer Address option, then the recipient
            // SHOULD create or update the Neighbor Cache entry for the IP Source
            // Address of the solicitation.  If an entry does not already exist, the
            // node SHOULD create a new one and set its reachability state to STALE
            // as specified in Section 7.3.3. [RFC 2461]
            if (optLinkAddr)
            {
                IP6Entry* remote = IP6GetNextNeighbor(interface, &ip6->src, NULL);
                if (remote == NULL)
                {
                    // cannot send back NEIGHBOR_ADVERT.
                    return;
                }
                // If an entry already exists, and the
                // cached link-layer address differs from the one in the received Source
                // Link-Layer option, the cached address should be replaced by the
                // received address and the entry's reachability state MUST be set to
                // STALE. [RFC 2461]
                if (memcmp(remote->linkAddr, optLinkAddr->addr, ETH_ALEN) != 0)
                {
                    memmove(remote->linkAddr, optLinkAddr->addr, ETH_ALEN);
                    IP6SetNeighborState(remote, ND_STATE_STALE);
                }
            }
            // Set the Solicited flag
            ICMP6Out(neighbor, ND_NEIGHBOR_ADVERT, &ip6->src);
        }
        break;

      case ND_STATE_DELAYING_LISTENER:
      case ND_STATE_IDLE_LISTENER:
        break;

      default:
        break;
    }
}

static void DoRedirect(IPInterface* interface, IP6Hdr* ip6, NDRedirect* redirect, s32 len)
{
    IP6Entry* neighbor;
    NDOptHdr* opt;
    s32       olen;
    NDOptLinkAddrEthernet*
              optLinkAddr = NULL;
    IP6Entry* dst;

    if (redirect->code != 0)
    {
        return;
    }

    if (!SO_IN6_IS_ADDR_LINKLOCAL(&ip6->src))
    {
        return;
    }

    if (SO_IN6_IS_ADDR_MULTICAST(&redirect->dst))
    {
        return;
    }

    // The IP source address of the Redirect is the same as the current
    // first-hop router for the specified ICMP Destination Address. [RFC 2461]
    neighbor = IP6GetNextNeighbor(interface, &redirect->dst, NULL);
    if (neighbor == NULL ||
        !SO_IN6_ARE_ADDR_EQUAL(&neighbor->addr, &ip6->src))
    {
        return;
    }

    opt = (NDOptHdr*) ((u8*) redirect + sizeof(NDRedirect));
    len -= sizeof(NDRedirect);
    while (0 < len)
    {
        if (len < 2)
        {
            return;
        }
        olen = opt->len << 3;
        if (len < olen ||
            olen <= 0)      // All included options have a length that is greater than zero. [RFC 2461]
        {
            return;
        }

        switch (opt->type)
        {
          case ND_OPT_TARGET_LINKADDR:
            if (olen < sizeof(NDOptLinkAddrEthernet))
            {
                return;
            }
            optLinkAddr = (NDOptLinkAddrEthernet*) opt;
            break;
        }

        opt = (NDOptHdr*) ((u8*) opt + olen);
        len -= olen;
    }

    if (!SO_IN6_ARE_ADDR_EQUAL(&redirect->target, &redirect->dst))
    {
        // the target is a better first-hop router and the Target Address MUST be the
        // router's link-local address
        if (!SO_IN6_IS_ADDR_LINKLOCAL(&redirect->target))
        {
            return;
        }

        // Install new destination cache for the new next-hop
        dst = AllocDestination(&redirect->dst, 128);
        if (dst == NULL)
        {
            return;
        }
        dst->flags |= ND_FLAG_REDIRECT;

        // Create a new neighbor which is a new first-hop router
        neighbor = IP6GetNextNeighbor(interface, &redirect->target, NULL);
        if (neighbor == NULL)
        {
            return;
        }

        IP6SwitchToRouter(neighbor, OS_TIME_INFINITE);
        SetNetwork(dst, neighbor);
    }
    else
    {
        // Create a new neighbor which is the actual endpoint of communication
        neighbor = IP6GetNeighbor(interface, &redirect->target);
        neighbor->flags |= ND_FLAG_REDIRECT;
    }

    if (optLinkAddr && neighbor)
    {
        if (memcmp(neighbor->linkAddr, optLinkAddr->addr, ETH_ALEN) != 0 ||
            neighbor->state == ND_STATE_INIT)
        {
            IP6SetNeighborState(neighbor, ND_STATE_STALE);
        }
        memmove(neighbor->linkAddr, optLinkAddr->addr, ETH_ALEN);
    }
}

void NDHold(IP6Entry* neighbor, IFDatagram* datagram)
{
    IPInterface* interface;
    IFCallback   callback;
    void*        param;
    BOOL         discard;
    s32          nVec;
    IFVec        va[IF_MAX_VEC];
    IFVec*       vec;

    ASSERT(neighbor->interface);
    interface = neighbor->interface;
    callback = datagram->callback;
    param = datagram->param;
    nVec = datagram->nVec;
    ASSERT(0 < nVec && nVec <= IF_MAX_VEC);
    memmove(va, datagram->vec, nVec * sizeof(IFVec));
    discard = FALSE;
    // Attempt to free in reverse order as current memory allocator is based on FIFO
    while (0 < nVec--)
    {
        vec = &va[nVec];
        discard |= interface->free(interface, vec->data, vec->len);
    }
    discard |= interface->free(interface, datagram,
                               (s32) (sizeof(IFDatagram) + ((1 < datagram->nVec) ? sizeof(IFVec) * (datagram->nVec - 1) : 0)));
    if (!discard)
    {
        datagram->interface = interface;
        datagram->queue = &neighbor->queue;
        IFEnqueueTail(IFDatagram*, &neighbor->queue, datagram, link);
    }
    else
    {
        ++interface->stat.outDiscards;
        if (callback)
        {
            callback(param, IP_ERR_INS_RESOURCES);
        }
    }
}

void ICMP6SendError(IPInterface* interface, u8 type, u8 code, IP6Hdr* org, u32 flag, u32 pointer)
{
    BOOL        enabled;
    IFDatagram* datagram;
    IP6Hdr*     ip6;
    ICMP6Hdr*   icmp6;
    s32         plen;
    u8*         hdr;
    s32         len;
    u8          next;
    s32         hlen;
    IP6Entry*   nextHop;
    IP6Entry*   dst;

    enabled = OSDisableInterrupts();

    ++interface->icmpv6Stat.outMsgs;

    if ((flag & (IF_FLAG_BROADCAST | IF_FLAG_MULTICAST)) || // (e.3, e.4)
        SO_IN6_IS_ADDR_UNSPECIFIED(&org->src) ||            // (e.5)
        SO_IN6_IS_ADDR_MULTICAST(&org->src))                // (e.5)    XXX or anycast address
    {
        goto Error;
    }

    hdr = (u8*) org + sizeof(IP6Hdr);
    len = org->plen;
    next = org->next;
    while (next != SO_IPPROTO_NONE)
    {
        switch (next)
        {
          case SO_IPPROTO_HOPOPTS:
          case SO_IPPROTO_ROUTING:
          case SO_IPPROTO_FRAGMENT:
          case SO_IPPROTO_DSTOPTS:
          case SO_IPPROTO_AH:
          case SO_IPPROTO_ESP:
            if (len < 2)
            {
                goto Error;
            }
            hlen = (1 + hdr[1]) << 3;
            if (len < hlen)
            {
                goto Error;
            }
            if (next != SO_IPPROTO_FRAGMENT || IP6_FRAG_OFFSET(hdr) == 0)
            {
                next = hdr[0];
            }
            else
            {
                next = SO_IPPROTO_NONE;
            }
            len -= hlen;
            hdr += hlen;
            break;
          case IP_PROTO_UDP:
          case IP_PROTO_TCP:
            if (len < 8)
            {
                goto Error;
            }
            next = SO_IPPROTO_NONE;
            break;
          case SO_IPPROTO_ICMPV6:
            icmp6 = (ICMP6Hdr*) hdr;
            if (icmp6->type < 128)  // (e.1) an ICMPv6 error message
            {
                goto Error;
            }

            if (SO_IN6_IS_ADDR_MULTICAST(&org->dst))
            {
                if (type != ICMP6_PACKET_TOO_BIG &&
                    (type != ICMP6_PARAM_PROB || code != ICMP6_PARAMPROB_OPTION))   // (e.2) [RFC 2463]
                {
                    goto Error;
                }
            }
            next = SO_IPPROTO_NONE;
            break;
          default:
            next = SO_IPPROTO_NONE;
            break;
        }
    }

    plen = (s32) (sizeof(ICMP6Hdr) + sizeof(IP6Hdr) + org->plen);

    // Include as much of invoking packet as will fit without the ICMPv6 packet
    // exceeding the minimum IPv6 MTU. [RFC 2463]
    if (IP6_MIN_MTU < sizeof(IP6Hdr) + plen)
    {
        plen = IP6_MIN_MTU - sizeof(IP6Hdr);
        ASSERT(sizeof(ICMP6Hdr) <= plen);
    }

    datagram = ICMPAllocDatagram(interface, (s32) sizeof(IP6Hdr) + plen);
    if (datagram == NULL)
    {
        goto Error;
    }
    IFInitDatagram(datagram, ETH_IPv6, 1);
    ip6 = (IP6Hdr*) ((u8*) datagram + sizeof(IFDatagram));
    icmp6 = (ICMP6Hdr*) ((u8*) ip6 + sizeof(IP6Hdr));

    ip6->dst = org->src;
    IP6SelectSourceAddress(interface, &ip6->dst, &ip6->src);
    ip6->next = SO_IPPROTO_ICMPV6;
    ip6->hops = interface->curHopLimit;

    icmp6->type = type;
    icmp6->code = code;
    icmp6->cksum = 0;
    icmp6->data = SOHtoNl(pointer);

    memmove((u8*) icmp6 + sizeof(ICMP6Hdr), org, plen - sizeof(ICMP6Hdr));

    datagram->vec[0].data = ip6;
    datagram->vec[0].len  = (s32) sizeof(IP6Hdr) + plen;

    ip6->flow = 6u << 28;
    ASSERT(plen < (1 << 16));
    ip6->plen = (u16) plen;

    icmp6->cksum = ICMP6CheckSum(ip6, icmp6, plen);

    nextHop = IP6GetNextNeighbor(interface, &ip6->dst, &dst);
    datagram->mtu = (u16) IP6GetPathMTU(dst, datagram->vec[0].len);
    if (IP6Out(interface, datagram, nextHop) < 0)
    {
        // datagram has not been sent out. Must release memory
        ICMPFreeDatagram(datagram);
        interface->free(interface, datagram, (s32) (sizeof(IFDatagram) + sizeof(IP6Hdr) + plen));
    }
    else
    {
        switch (type)
        {
          case ICMP6_DST_UNREACH:
            ++interface->icmpv6Stat.outDestUnreachs;
            if (code == ICMP6_DST_UNREACH_ADMIN)
            {
                ++interface->icmpv6Stat.outAdminProhibs;
            }
            break;
          case ICMP6_PACKET_TOO_BIG:
            ++interface->icmpv6Stat.outPktTooBigs;
            break;
          case ICMP6_TIME_EXCEEDED:
            ++interface->icmpv6Stat.outTimeExcds;
            break;
          case ICMP6_PARAM_PROB:
            ++interface->icmpv6Stat.outParmProblems;
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    return;
    // NOT REACHED HERE

Error:
    ++interface->icmpv6Stat.outErrors;
    OSRestoreInterrupts(enabled);
}

void ICMP6Out(IP6Entry* neighbor, u8 type, const SOIn6Addr* dst)
{
    BOOL         enabled;
    IFDatagram*  datagram;
    IP6Hdr*      ip6;
    ICMP6Hdr*    icmp6;
    IPInterface* interface;
    s32          plen;
    IP6Entry*    linkLocal;
    s32          len;
    IP6Entry*    nextHop;
    IP6Entry*    destination;

    enabled = OSDisableInterrupts();

    interface = neighbor->interface;
    linkLocal = interface->linkLocal;

    ++interface->icmpv6Stat.outMsgs;

    switch (type)
    {
      case ND_ROUTER_SOLICIT:
      {
        NDRouterSolicit*       rs;
        NDOptLinkAddrEthernet* optLinkAddr;

        plen = sizeof(NDRouterSolicit);
        if (linkLocal && linkLocal->state != ND_STATE_TENTATIVE)
        {
            plen += sizeof(NDOptLinkAddrEthernet);
        }
        datagram = ICMPAllocDatagram(interface, (s32) sizeof(IP6Hdr) + plen);
        if (datagram == NULL)
        {
            goto Error;
        }
        IFInitDatagram(datagram, ETH_IPv6, 1);
        ip6 = (IP6Hdr*) ((u8*) datagram + sizeof(IFDatagram));
        rs = (NDRouterSolicit*) ((u8*) ip6 + sizeof(IP6Hdr));
        optLinkAddr = (NDOptLinkAddrEthernet*) ((u8*) rs + sizeof(NDRouterSolicit));

        if (linkLocal == NULL || linkLocal->state == ND_STATE_TENTATIVE)
        {
            ip6->src = SOIn6AddrAny;
        }
        else
        {
            ip6->src = linkLocal->addr;
            optLinkAddr->type = ND_OPT_SOURCE_LINKADDR;
            optLinkAddr->len = 1;
            memmove(optLinkAddr->addr, interface->mac, ETH_ALEN);
        }
        ip6->next = SO_IPPROTO_ICMPV6;

        // The IP Hop Limit field has a value of 255, i.e., the packet
        // could not possibly have been forwarded by a router. [RFC 2461]
        ip6->hops = 255;

        rs->type = ND_ROUTER_SOLICIT;
        rs->code = 0;
        rs->cksum = 0;
        rs->reserved = 0;

        len = plen;
        icmp6 = (ICMP6Hdr*) rs;
        break;
      }

      case ND_NEIGHBOR_SOLICIT:
      {
        NDNeighborSolicit*     ns;
        NDOptLinkAddrEthernet* optLinkAddr;

        plen = sizeof(NDNeighborSolicit);
        if (neighbor->state != ND_STATE_TENTATIVE)
        {
            // MUST NOT include Source link-layer address option
            plen += sizeof(NDOptLinkAddrEthernet);
        }
        datagram = ICMPAllocDatagram(interface, (s32) sizeof(IP6Hdr) + plen);
        if (datagram == NULL)
        {
            goto Error;
        }
        IFInitDatagram(datagram, ETH_IPv6, 1);
        ip6 = (IP6Hdr*) ((u8*) datagram + sizeof(IFDatagram));
        ns = (NDNeighborSolicit*) ((u8*) ip6 + sizeof(IP6Hdr));
        optLinkAddr = (NDOptLinkAddrEthernet*) ((u8*) ns + sizeof(NDNeighborSolicit));

        if (neighbor->state == ND_STATE_TENTATIVE)
        {
            ip6->src = SOIn6AddrAny;
        }
        else
        {
            IP6SelectSourceAddress(interface, dst, &ip6->src);
        }
        ip6->next = SO_IPPROTO_ICMPV6;

        // The IP Hop Limit field has a value of 255, i.e., the packet
        // could not possibly have been forwarded by a router. [RFC 2461]
        ip6->hops = 255;

        ns->type = ND_NEIGHBOR_SOLICIT;
        ns->code = 0;
        ns->cksum = 0;
        ns->reserved = 0;
        ns->target = neighbor->addr;

        optLinkAddr->type = ND_OPT_SOURCE_LINKADDR;
        optLinkAddr->len = 1;
        memmove(optLinkAddr->addr, interface->mac, ETH_ALEN);

        len = plen;
        icmp6 = (ICMP6Hdr*) ns;
        break;
      }

      case ND_NEIGHBOR_ADVERT:
      {
        NDNeighborAdvert*      na;
        NDOptLinkAddrEthernet* optLinkAddr;

        ASSERT(neighbor->state != ND_STATE_TENTATIVE);
        plen = sizeof(NDNeighborAdvert);
        if (neighbor->state != ND_STATE_TENTATIVE)
        {
            // MUST NOT include Source link-layer address option
            plen += sizeof(NDOptLinkAddrEthernet);
        }
        datagram = ICMPAllocDatagram(interface, (s32) sizeof(IP6Hdr) + plen);
        if (datagram == NULL)
        {
            goto Error;
        }
        IFInitDatagram(datagram, ETH_IPv6, 1);
        ip6 = (IP6Hdr*) ((u8*) datagram + sizeof(IFDatagram));
        na = (NDNeighborAdvert*) ((u8*) ip6 + sizeof(IP6Hdr));
        optLinkAddr = (NDOptLinkAddrEthernet*) ((u8*) na + sizeof(NDNeighborAdvert));

        IP6SelectSourceAddress(interface, dst, &ip6->src);
        ip6->next = SO_IPPROTO_ICMPV6;

        // The IP Hop Limit field has a value of 255, i.e., the packet
        // could not possibly have been forwarded by a router. [RFC 2461]
        ip6->hops = 255;

        na->type = ND_NEIGHBOR_ADVERT;
        na->code = 0;
        na->cksum = 0;
        na->flagsReserved = 0;
        if (!SO_IN6_IS_ADDR_MULTICAST(dst) /* XXX || unsolicited unicast advertisements */)
        {
            na->flagsReserved |= ND_NA_FLAG_SOLICITED;
        }
        na->flagsReserved |= ND_NA_FLAG_OVERRIDE;    // XXX
        na->target = neighbor->addr;
        ASSERT(!SO_IN6_IS_ADDR_MULTICAST(&na->target));

        if (neighbor->state != ND_STATE_TENTATIVE)
        {
            optLinkAddr->type = ND_OPT_TARGET_LINKADDR;
            optLinkAddr->len = 1;
            memmove(optLinkAddr->addr, interface->mac, ETH_ALEN);
        }

        len = plen;
        icmp6 = (ICMP6Hdr*) na;
        break;
      }

      case MLD_LISTENER_REPORT:
      case MLD_LISTENER_REDUCTION:
      {
        IP6Hbh*       hbh;
        IP6OptRouter* opt;
        ICMP6MldHder* mld;

        plen = sizeof(IP6Hbh) + sizeof(IP6OptRouter) + 2 + sizeof(ICMP6MldHder);
        datagram = ICMPAllocDatagram(interface, (s32) sizeof(IP6Hdr) + plen);
        if (datagram == NULL)
        {
            goto Error;
        }
        IFInitDatagram(datagram, ETH_IPv6, 1);
        ip6 = (IP6Hdr*) ((u8*) datagram + sizeof(IFDatagram));
        hbh = (IP6Hbh*) ((u8*) ip6 + sizeof(IP6Hdr));
        opt = (IP6OptRouter*) ((u8*) hbh + sizeof(IP6Hbh));
        mld = (ICMP6MldHder*) ((u8*) opt + sizeof(IP6OptRouter) + 2);

        if (linkLocal == NULL || linkLocal->state == ND_STATE_TENTATIVE)
        {
            ip6->src = SOIn6AddrAny;    // [RFC 3590]
        }
        else
        {
            ip6->src = linkLocal->addr;
        }
        ip6->next = SO_IPPROTO_HOPOPTS;
        ip6->hops = 1;

        // IPv6 Router Alert option
        hbh->next = SO_IPPROTO_ICMPV6;
        hbh->len = 0;   // 8 octets
        opt->type = IP6OPT_ROUTER_ALERT;
        opt->len = 2;
        opt->value[0] = (u8) (IP6_ALERT_MLD >> 8);
        opt->value[1] = (u8) IP6_ALERT_MLD;
        opt->value[2] = IP6OPT_PADN;
        opt->value[3] = 0;

        mld->type = type;
        mld->code = 0;
        mld->cksum = 0;
        mld->maxDelay = 0;
        mld->reserved = 0;
        mld->addr = neighbor->addr;

        len = plen - ((u8*) mld - (u8*) hbh);
        icmp6 = (ICMP6Hdr*) mld;

        if (type == MLD_LISTENER_REDUCTION)
        {
            // it SHOULD send a single Done message to the link-scope all-routers
            // multicast address (FF02::2) [RFC 2710]
            dst = &SOIn6AddrLinkLocalAllRouters;
        }
        break;
      }

      default:
        goto Error;
    }

    datagram->vec[0].data = ip6;
    datagram->vec[0].len  = (s32) sizeof(IP6Hdr) + plen;

    ip6->flow = 6u << 28;
    ASSERT(plen < (1 << 16));
    ip6->plen = (u16) plen;
    ip6->dst = *dst;

    icmp6->cksum = ICMP6CheckSum(ip6, icmp6, len);

    nextHop = IP6GetNextNeighbor(interface, &ip6->dst, &destination);
    datagram->mtu = (u16) IP6GetPathMTU(destination, datagram->vec[0].len);
    if (IP6Out(interface, datagram, nextHop) < 0)
    {
        // datagram has not been sent out. Must release memory
        ICMPFreeDatagram(datagram);
        interface->free(interface, datagram, (s32) (sizeof(IFDatagram) + sizeof(IP6Hdr) + plen));
    }
    else
    {
        switch (type)
        {
          case ND_ROUTER_SOLICIT:
            ++interface->icmpv6Stat.outRouterSolicits;
            break;
          case ND_ROUTER_ADVERT:
            ++interface->icmpv6Stat.outRouterAdvertisements;
            break;
          case ND_NEIGHBOR_SOLICIT:
            ++interface->icmpv6Stat.outNeighborSolicits;
            break;
          case ND_NEIGHBOR_ADVERT:
            ++interface->icmpv6Stat.outNeighborAdvertisements;
            break;
          case ND_REDIRECT:
            ++interface->icmpv6Stat.outRedirects;
            break;
          case MLD_LISTENER_QUERY:
            ++interface->icmpv6Stat.outGroupMembQueries;
            break;
          case MLD_LISTENER_REPORT:
            ++interface->icmpv6Stat.outGroupMembResponses;
            break;
          case MLD_LISTENER_REDUCTION:
            ++interface->icmpv6Stat.outGroupMembReductions;
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    return;
    // NOT REACHED HERE

Error:
    ++interface->icmpv6Stat.outErrors;
    OSRestoreInterrupts(enabled);
}

void IP6Startup(IPInterface* interface)
{
    BOOL      enabled;
#ifdef IOP_OS
    SOIn6Addr linklocal = { { 0xfe, 0x80 } };
#else
    SOIn6Addr linklocal = { 0xfe, 0x80 };
#endif // IOP_OS
    SOIn6Addr solicited;
    IP6Entry* route;
    IP6Entry* neighbor;

    IP6Cleanup(interface);

    // Setup Link-local unicast prefix
    route = AllocPrefix(&linklocal, 64);
    route->validTime = route->preferredTime = OS_TIME_INFINITE;

    interface->linkMTU = 1500;
    interface->curHopLimit = 255;
    interface->baseReachableTime = OSMillisecondsToTicks((OSTime) REACHABLE_TIME);
    interface->reachableTime = IPRandTime(interface,
                                          MIN_RANDOM_FACTOR(interface->baseReachableTime),
                                          MAX_RANDOM_FACTOR(interface->baseReachableTime));
    interface->retransTimer = OSMillisecondsToTicks((OSTime) RETRANS_TIMER);
    interface->dupAddrDetectTransmits = 1; // RFC 2462
    interface->managedFlag = 0;
    interface->otherConfigFlag = 0;

    IP6MulticastJoin(interface, &SOIn6AddrLinkLocalAllNodes);

    // Create the IP6Entry entry for the loopback address
    IP6Claim(interface, &SOIn6AddrLoopback, 0xffffffff, 0xffffffff, 0);

    switch (interface->type)
    {
      case IF_TYPE_AUTO:
      case IF_TYPE_100FULL:
      case IF_TYPE_100HALF:
      case IF_TYPE_10FULL:
      case IF_TYPE_10HALF:
        // Create a link local address
        linklocal.addr[0] = 0xfe;
        linklocal.addr[1] = 0x80;
        memset(&linklocal.addr[2], 0, 6);
        memcpy(&linklocal.addr[8], interface->eui64, 8);

        // Join the solicited-node multicast address of the tentative address.
        IP6MulticastJoin(interface, IP6GetSolicited(&linklocal, &solicited));

        // A link-local address has an infinite preferred and valid lifetime;
        IP6Claim(interface, &linklocal, 0xffffffff, 0xffffffff, 0);
        break;
    }

    // Sending Router Solicitations before up to MAX_RTR_SOLICITATION_DELAY [sec].
    enabled = OSDisableInterrupts();
    neighbor = IP6GetNeighbor(interface, &SOIn6AddrLinkLocalAllRouters);
    ASSERT(neighbor && neighbor->state == ND_STATE_NON_LISTENER);
    OSSetAlarm(&neighbor->alarm,
               IPRandTime(interface, 0, OSSecondsToTicks((OSTime) MAX_RTR_SOLICITATION_DELAY)),
               RouterSolicitHandler);
    IP6RefNeighbor(neighbor);   // while using the alarm
    OSRestoreInterrupts(enabled);
}

void IP6Cleanup(IPInterface* interface)
{
    BOOL      enabled;
    OSTime    now;
    IP6Entry* neighbor;

    enabled = OSDisableInterrupts();
    now = OSGetTime();

    // Initialize neighbor cache
    IFInitQueue(&NDCache);
    for (neighbor = NeighborTable;
         neighbor < &NeighborTable[MAX_NEIGHBORS];
         ++neighbor)
    {
        OSCancelAlarm(&neighbor->alarm);
        DiscardPendingPackets(neighbor, IP_ERR_NONE);
        neighbor->ref = 0;
        neighbor->validTime = neighbor->preferredTime = now;
        neighbor->prefixLen = 0;
        neighbor->state = ND_STATE_INVALID;
        IFInitQueue(&neighbor->queue);
        IFInitQueue(&neighbor->queueNext);
        IFInitQueue(&neighbor->queueFrom);
        IFInitQueue(&neighbor->queueTo);
        IFInitQueue(&neighbor->queueNetwork);
        IFEnqueueTail(IP6Entry*, &NDCache, neighbor, link);
    }
    interface->linkLocal = NULL;

    // Initialize MLD table
    memset(MLDTabel, 0, sizeof MLDTabel);
    MLDCount = 0;

    OSRestoreInterrupts(enabled);
}

static void RouterSolicitHandler(OSAlarm* alarm, OSContext* context)
{
#ifdef IOP_OS
    TCPIP_UNUSED(context);
#else
    #pragma unused(context)
#endif // IOP_OS
    IP6Entry*    neighbor;
    IPInterface* interface;

    neighbor = (IP6Entry*) ((u8*) alarm - offsetof(IP6Entry, alarm));
    interface = neighbor->interface;
    ++neighbor->count;
    if (neighbor->count <= MAX_RTR_SOLICITATIONS)
    {
        ICMP6Out(neighbor, ND_ROUTER_SOLICIT, &SOIn6AddrLinkLocalAllRouters);
        OSSetAlarm(&neighbor->alarm, OSSecondsToTicks((OSTime) RTR_SOLICITATION_INTERVAL), RouterSolicitHandler);
    }
    else if (neighbor->count == MAX_RTR_SOLICITATIONS + 1)
    {
        OSSetAlarm(&neighbor->alarm, OSSecondsToTicks((OSTime) MAX_RTR_SOLICITATION_DELAY), RouterSolicitHandler);
    }
    else
    {
        IP6PutNeighbor(neighbor);
    }
}

void IP6SetNeighborState(IP6Entry* neighbor, int state)
{
    IPInterface* interface;
    SOIn6Addr    solicited;
    IP6Entry*    dst;
    IP6Entry*    next;
    IPInfo*      info;
    IPInfo*      infoNext;

    neighbor->lastUpdated = OSGetTime();
    if (neighbor->state == state)
    {
        return;
    }
    interface = neighbor->interface;
    switch (state)
    {
      case ND_STATE_INVALID:

        OSCancelAlarm(&neighbor->alarm);
        DiscardPendingPackets(neighbor, IP_ERR_UNREACHABLE);

        while (!IFIsEmptyQueue(&neighbor->queueFrom))
        {
            TCPObj* tcp;

            IFDequeueHead(IPInfo*, &neighbor->queueFrom, info, linkFrom);
            info->from = NULL;
            switch (info->proto)
            {
              case IP_PROTO_UDP:
                UDPAbort((UDPInfo*) info, IP_ERR_UNREACHABLE);
                break;
              case IP_PROTO_TCP:
                tcp = TCPGetObj((TCPInfo*) info);
                if (tcp->err == 0)
                {
                    tcp->err = IP_ERR_UNREACHABLE;
                }
                TCPAbort(tcp);
                break;
            }
            IP6PutNeighbor(neighbor);
        }

        while (!IFIsEmptyQueue(&neighbor->queueTo))
        {
            TCPObj* tcp;

            IFDequeueHead(IPInfo*, &neighbor->queueTo, info, linkTo);
            info->to = NULL;
            switch (info->proto)
            {
              case IP_PROTO_UDP:
                UDPAbort((UDPInfo*) info, IP_ERR_UNREACHABLE);
                break;
              case IP_PROTO_TCP:
                tcp = TCPGetObj((TCPInfo*) info);
                if (tcp->err == 0)
                {
                    tcp->err = IP_ERR_UNREACHABLE;
                }
                TCPAbort(tcp);
                break;
            }
            IP6PutNeighbor(neighbor);
        }

        if (neighbor->state == ND_STATE_DESTINATION && neighbor->network)
        {
            IP6Entry* network = neighbor->network;
            SetNetwork(neighbor, NULL);
            if ((network->flags & ND_FLAG_IS_ROUTER) &&
                network->routerLifetime == OS_TIME_INFINITE &&
                IFIsEmptyQueue(&network->queueNetwork))
            {
                IP6SwitchToHost(neighbor);
            }
        }

        SetNetwork(neighbor, NULL);

        while (!IFIsEmptyQueue(&neighbor->queueNetwork))
        {
            IP6Entry* onLink;

            IFDequeueHead(IP6Entry*, &neighbor->queueNetwork, onLink, linkNetwork);
            IP6SetNeighborState(onLink, ND_STATE_INVALID);
            IP6PutNeighbor(onLink);
        }

        neighbor->state = state;
        neighbor->preferredTime = neighbor->validTime = neighbor->lastTooBig = -OS_TIME_INFINITE;
        neighbor->flags &= ~ND_FLAG_IS_ROUTER;
        break;

      case ND_STATE_INIT:
        neighbor->state = state;
        OSCancelAlarm(&neighbor->alarm);
        DiscardPendingPackets(neighbor, IP_ERR_UNREACHABLE);
        IFIterateQueue(IPInfo*, &neighbor->queueTo, info, infoNext, linkTo)
        {
            IP6SetNextHop(info, NULL);
        }
        break;
      case ND_STATE_INCOMPLETE:
        // Initiates Address Resolution
        neighbor->state = state;
        ++neighbor->count;
        ICMP6Out(neighbor, ND_NEIGHBOR_SOLICIT, IP6GetSolicited(&neighbor->addr, &solicited));
        OSCancelAlarm(&neighbor->alarm);
        OSSetAlarm(&neighbor->alarm,
                   interface->retransTimer,
                   IP6NeighborTimeout);
        break;
      case ND_STATE_REACHABLE:
        neighbor->state = state;
        neighbor->validTime = OSGetTime() + interface->reachableTime;
        OSCancelAlarm(&neighbor->alarm);
        break;
      case ND_STATE_STALE:
        neighbor->state = state;
        OSCancelAlarm(&neighbor->alarm);
        break;
      case ND_STATE_DELAY:
        ASSERT(neighbor->state == ND_STATE_STALE);
        neighbor->state = state;
        OSSetAlarm(&neighbor->alarm,
                   OSSecondsToTicks(DELAY_FIRST_PROBE_TIME),
                   IP6NeighborTimeout);
        break;
      case ND_STATE_PROBE:
        neighbor->state = state;
        break;

      case ND_STATE_TENTATIVE:
        neighbor->state = state;
        break;
      case ND_STATE_PREFERRED:
        neighbor->state = state;
        OSCancelAlarm(&neighbor->alarm);
        if (neighbor->validTime < OS_TIME_INFINITE)
        {
            OSSetAbsAlarm(&neighbor->alarm, neighbor->validTime, IP6NeighborTimeout);
        }
        break;
      case ND_STATE_DEPRECATED:
        neighbor->state = state;
        break;

      case ND_STATE_NON_LISTENER:
      case ND_STATE_DELAYING_LISTENER:
      case ND_STATE_IDLE_LISTENER:
        neighbor->state = state;
        break;

      case ND_STATE_DESTINATION:
        neighbor->state = state;
        neighbor->preferredTime = neighbor->validTime = OS_TIME_INFINITE;
        OSCancelAlarm(&neighbor->alarm);
        DiscardPendingPackets(neighbor, IP_ERR_NONE);

        IFIterateQueue(IPInfo*, &neighbor->queueTo, info, infoNext, linkTo)
        {
            IP6SetNextHop(info, NULL);
        }

        SetNetwork(neighbor, NULL);

        // Dissociate info from the old first-hop router.
        IFIterateQueue(IP6Entry*, &NDCache, dst, next, link)
        {
            if (neighbor->prefixLen == 0)
            {
                break;
            }
            if (neighbor == dst)
            {
                continue;
            }
            switch (dst->state)
            {
              case ND_STATE_INIT:
              case ND_STATE_INCOMPLETE:
              case ND_STATE_REACHABLE:
              case ND_STATE_STALE:
              case ND_STATE_DELAY:
              case ND_STATE_PROBE:
              case ND_STATE_PREFIX:
                if (!Hit(neighbor->addr.addr, dst->addr.addr, neighbor->prefixLen))
                {
                    continue;
                }
                IP6SetNeighborState(dst, ND_STATE_DESTINATION);
                break;
            }
        }
        break;

      case ND_STATE_PREFIX:
        neighbor->state = state;

        // Dissociate default routers of the sockets connected to this prefix
        IFIterateQueue(IP6Entry*, &NDCache, dst, next, link)
        {
            if (neighbor->prefixLen == 0)
            {
                break;
            }
            if (neighbor == dst)
            {
                continue;
            }
            if (dst->state == ND_STATE_DESTINATION)
            {
                if (!Hit(neighbor->addr.addr, dst->addr.addr, neighbor->prefixLen))
                {
                    continue;
                }
                IP6SetNeighborState(dst, ND_STATE_INIT);   // dst is now on-link.
                SetNetwork(dst, neighbor);
            }
        }
        break;
    }
}

static void NullCallback(ICMPInfo* info, s32 result)
{
#ifdef IOP_OS
    TCPIP_UNUSED(info);
    TCPIP_UNUSED(result);
#else
    #pragma unused(info, result)
#endif // IOP_OS
}

s32 ICMP6Ping(ICMP6Info* info, const void* data, s32 len,
              const void* remote, ICMPCallback callback, s32* result)
{
    const SOSockAddrIn6*
                 remoteAddr = remote;
    IPInterface* interface;
    IP6Hdr*      req;
    ICMP6Hdr*    icmp;
    BOOL         enabled;
    IFDatagram*  datagram;
    s32          rc;
    s32          plen;
    ICMPObj*     obj;
    IP6Entry*    nextHop;
    IP6Entry*    dst;

    ASSERT(info->info.proto == SO_IPPROTO_ICMPV6);
    if (!callback)
    {
        callback = NullCallback;
    }

    enabled = OSDisableInterrupts();

    if (info->info.proto != SO_IPPROTO_ICMPV6)
    {
        rc = IP_ERR_INVALID;
        goto Error;
    }

    obj = ICMPGetObj((ICMPInfo*) info);
    if (obj->callback)
    {
        rc =  IP_ERR_BUSY;
        goto Error;
    }

    if (65536 - sizeof(IP6Hdr) - sizeof(ICMPEcho) < len)
    {
        rc = IP_ERR_DATASIZE;
        goto Error;
    }

    plen = (s32) sizeof(ICMPEcho) + len;

    info->local.port = info->remote.port = remoteAddr->port;  // XXX check dup.
    memmove(&info->remote.addr, &remoteAddr->addr, sizeof(SOIn6Addr));

    nextHop = IP6GetNextNeighbor(NULL, &info->remote.addr, &dst);
    if (!nextHop)
    {
        rc = IP_ERR_INS_RESOURCES;
        goto Error;
    }
    ASSERT(nextHop->interface);
    interface = nextHop->interface;
    ++interface->icmpv6Stat.outMsgs;

    // Select the source address
    IP6SelectSourceAddress(interface,
                           (SOIn6Addr*) &info->remote.addr,
                           (SOIn6Addr*) &info->local.addr);

    //
    // Form ICMP echo request message
    //
    datagram = &obj->datagram;
    IFInitDatagram(datagram, ETH_IPv6, 2);
    datagram->vec[0].data = obj->header;
    datagram->vec[0].len = (s32) (sizeof(IP6Hdr) + sizeof(ICMPEcho));
    datagram->vec[1].data = (void*) data;
    datagram->vec[1].len = len;

    obj->data = data;
    obj->len = len;
    obj->callback = callback;
    obj->result = result;
    ++obj->seq;

    req = (IP6Hdr*) datagram->vec[0].data;
    req->next = SO_IPPROTO_ICMPV6;
    req->hops = interface->curHopLimit;
    req->flow = 6u << 28;
    req->plen = (u16) plen;

    memmove(&req->src, &info->local.addr,  sizeof(SOIn6Addr));
    memmove(&req->dst, &info->remote.addr, sizeof(SOIn6Addr));

    icmp = (ICMP6Hdr*) ((u8*) req + sizeof(IP6Hdr));
    icmp->type  = ICMP6_ECHO_REQUEST;
    icmp->data = (u32) ((remoteAddr->port << 16) | (u16) obj->seq);
    icmp->cksum = 0;
    icmp->cksum = IP6CheckSum(SO_IPPROTO_ICMPV6, datagram->vec, 2, icmp, plen);

    if (result)
    {
        *result = IP_ERR_BUSY;
    }

    datagram->mtu = (u16) IP6GetPathMTU(dst, (s32) sizeof(IP6Hdr) + plen);
    rc = IP6Out(interface, datagram, nextHop);
    if (rc < 0)
    {
        obj->callback = NULL;
        goto Error;
    }
    else
    {
        ++interface->icmpv6Stat.outEchos;
    }
    OSRestoreInterrupts(enabled);
    return rc;

Error:
    if (result)
    {
        *result = rc;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

void IP6EnumAddresses(IPInterface* interface, BOOL (*callback)(int af, const void* addr))
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused(interface)
#endif // IOP_OS
    BOOL      ret;
    BOOL      enabled;
    u8        addr[sizeof(SOIn6Addr)];
    IP6Entry* neighbor;
    IP6Entry* next;

    ASSERT(callback);

    enabled = OSDisableInterrupts();
    IFIterateQueue(IP6Entry*, &NDCache, neighbor, next, link)
    {
        if (neighbor->state == ND_STATE_PREFERRED)
        {
            if (neighbor->preferredTime < OSGetTime())
            {
                IP6SetNeighborState(neighbor, ND_STATE_DEPRECATED);
                continue;
            }

            memmove(addr, &neighbor->addr, sizeof(SOIn6Addr));
            OSRestoreInterrupts(enabled);
            ret = callback(SO_PF_INET6, addr);
            if (ret == FALSE)
            {
                OSRestoreInterrupts(enabled);
                return;
            }
            enabled = OSDisableInterrupts();
        }
    }

    OSRestoreInterrupts(enabled);
    callback(SO_AF_UNSPEC, NULL);
}

s32 IP6SetAddr(IPInterface* interface, const SOIn6Addr* addr)
{
    BOOL enabled;
    s32  rc = IP_ERR_INVALID;

    interface = interface ? interface : &__IFDefault;
    enabled = OSDisableInterrupts();
    if (memcmp(interface->eui64, &addr->addr[8], 8) == 0)
    {
        IP6Claim(interface, addr, 0xffffffff, 0xffffffff, ND_FLAG_STATIC);
        rc = IP_ERR_NONE;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 IP6RemoveAddr(IPInterface* interface, const SOIn6Addr* addr)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused( interface )
#endif // IOP_OS
    BOOL      enabled;
    IP6Entry* neighbor;
    s32       rc;

    enabled = OSDisableInterrupts();
    neighbor = IP6SearchNeighbor(addr);
    if (neighbor == NULL)
    {
        rc = IP_ERR_NOT_EXIST;
    }
    else
    {
        switch (neighbor->state)
        {
          case ND_STATE_TENTATIVE:
          case ND_STATE_PREFERRED:
          case ND_STATE_DEPRECATED:
            IP6SetNeighborState(neighbor, ND_STATE_INVALID);
            IP6PutNeighbor(neighbor);
            rc = IP_ERR_NONE;
            break;
          default:
            rc = IP_ERR_NOT_EXIST;
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

BOOL IP6AddRoute(const SOIn6Addr* prefix, u8 prefixLen, const SOIn6Addr* nextHop)
{
    BOOL         enabled;
    IP6Entry*    neighbor;
    IP6Entry*    destination;
    IPInterface* interface = &__IFDefault;
    BOOL         rc = FALSE;

    if (prefixLen < 64 || SO_IN6_IS_ADDR_MULTICAST(prefix) || SO_IN6_IS_ADDR_MULTICAST(nextHop))
    {
        return FALSE;
    }

    enabled = OSDisableInterrupts();

    // Install new destination cache for the new next-hop
    destination = AllocDestination(prefix, prefixLen);
    if (destination == NULL)
    {
        goto Error;
    }
    destination->flags |= ND_FLAG_STATIC;

    // Create new neighbor which is a new first-hop router
    neighbor = IP6GetNeighbor(interface, nextHop);
    if (neighbor == NULL)
    {
        goto Error;
    }

    IP6SwitchToRouter(neighbor, OS_TIME_INFINITE);
    SetNetwork(destination, neighbor);

    rc = TRUE;

Error:
    OSRestoreInterrupts(enabled);
    return rc;
}

BOOL IP6RemoveRoute(const SOIn6Addr* prefix, u8 prefixLen, const SOIn6Addr* nextHop)
{
#ifdef IOP_OS
    TCPIP_UNUSED(prefixLen);
    TCPIP_UNUSED(nextHop);
#else
    #pragma unused( prefixLen, nextHop )
#endif // IOP_OS
    BOOL      enabled;
    BOOL      rc = FALSE;
    IP6Entry* destination;

    if (prefixLen < 64 || SO_IN6_IS_ADDR_MULTICAST(prefix) || SO_IN6_IS_ADDR_MULTICAST(nextHop))
    {
        return FALSE;
    }

    enabled = OSDisableInterrupts();
    destination = IP6LookupPrefix(prefix, prefixLen);
    if (destination)
    {
        IP6SetNeighborState(destination, ND_STATE_INVALID);
        IP6PutNeighbor(destination);
        rc = TRUE;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

// IP6GetPathMTU() returns link MTU if dst is NULL.
s32 IP6GetPathMTU(IP6Entry* dst, s32 est)
{
    IPInterface* interface;

    if (!dst)
    {
        return __IFDefault.linkMTU;
    }

    interface= dst->interface ? dst->interface : &__IFDefault;
    ASSERT(dst->state != ND_STATE_INVALID);
    est = MIN(interface->linkMTU, est);
    if (dst->mtu < est &&
        dst->lastTooBig + OSSecondsToTicks(10 * 60LL) <= OSGetTime())
    {
        s32     mss;
        IPInfo* info;
        IPInfo* next;

        dst->mtu = est;
        mss = dst->mtu - (s32) sizeof(IP6Hdr) - TCP_MIN_HLEN;
        IFIterateQueue(IPInfo*, &dst->queueTo, info, next, linkTo)
        {
            TCPObj* tcp;

            if (info->family != SO_AF_INET6 ||
                info->proto != IP_PROTO_TCP)
            {
                continue;
            }

            tcp = TCPGetObj((TCPInfo*) info);
            if (tcp->mss < mss)
            {
                tcp->mss = MIN(mss, tcp->mssBase);

                // Goes back to slow start without changing slow start threshold
                // like source quench
                tcp->cWin = TCP_IW(tcp);
            }
        }

        dst->lastTooBig = OSGetTime() - OSSecondsToTicks(8 * 60LL);
    }
    return MIN(dst->mtu, interface->linkMTU);
}

s32 IP6ReportEntryTable(IPInterface* interface, int level, int optname, void* optval, int* optlen)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
    TCPIP_UNUSED(level);
#else
    #pragma unused( interface, level )
#endif // IOP_OS
    int             len;
    IP6Entry*       prefix;
    IP6Entry*       next;
    IP6PrefixEntry* ent;
    OSTime          now;

    now = OSGetTime();
    len = 0;
    ent = optval;
    IFIterateQueue(IP6Entry*, &NDCache, prefix, next, link)
    {
        if (*optlen < len + sizeof(IP6PrefixEntry))
        {
            break;
        }
        if (prefix->prefixLen <= 0)
        {
            break;
        }

        if (optname != SO_CONFIG_IPV6_PREFIX_TABLE)
        {
            switch (prefix->state)
            {
              case ND_STATE_INVALID:
                continue;
              case ND_STATE_INIT:
              case ND_STATE_INCOMPLETE:
              case ND_STATE_REACHABLE:
              case ND_STATE_STALE:
              case ND_STATE_DELAY:
              case ND_STATE_PROBE:
                if (optname == SO_CONFIG_IPV6_NET_TO_MEDIA_TABLE)
                {
                    break;
                }
                if (optname == SO_CONFIG_IPV6_ROUTE_TABLE && (prefix->flags & ND_FLAG_REDIRECT))
                {
                    break;
                }
                continue;
              case ND_STATE_TENTATIVE:
              case ND_STATE_PREFERRED:
              case ND_STATE_DEPRECATED:
                if (optname == SO_CONFIG_IPV6_ADDR_TABLE)
                {
                    break;
                }
                continue;
              case ND_STATE_NON_LISTENER:
              case ND_STATE_DELAYING_LISTENER:
              case ND_STATE_IDLE_LISTENER:
              case ND_STATE_DESTINATION:
                if (optname == SO_CONFIG_IPV6_ROUTE_TABLE)
                {
                    break;
                }
                continue;
              case ND_STATE_PREFIX:
                if (optname == SO_CONFIG_IPV6_ADDR_PREFIX_TABLE)
                {
                    break;
                }
                continue;
              default:
                continue;
            }
        }

        ent->addr = prefix->addr;
        ent->prefixLen = prefix->prefixLen;
        memcpy(ent->linkAddr, prefix->linkAddr, ETH_ALEN);
        ent->state = prefix->state;
        ent->flags = prefix->flags;
        ent->routerLifetime = prefix->routerLifetime;
        ent->validTime = prefix->validTime;
        ent->preferredTime = prefix->preferredTime;
        ent->mtu = prefix->mtu;
        if (prefix->network)
        {
            ent->nextHop = prefix->network->addr;
        }
        else
        {
            ent->nextHop = SOIn6AddrAny;
        }
        ent->lastUpdated = prefix->lastUpdated;

        len += sizeof(IP6PrefixEntry);
        ++ent;
    }
    *optlen = len;
    return IP_ERR_NONE;
}
