/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API - An Ethernet Address Resolution Protocol
  File:     IPArp.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPArp.c,v $
  Revision 1.5  2006/04/18 17:41:05  mxu
  process NET_IP_ALIGN for arp header alignment

  Revision 1.4  2006/04/14 22:55:58  mxu
  add workaround for ARP

  Revision 1.3  2006/04/12 01:45:05  mxu
  change sprintf to snprintf

  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    40    2/23/06 10:35 Shiki
    Included <dolphin/socket.h>.

    39    2/14/06 18:23 Shiki
    Fixed ARPOut().

    38    2/14/06 9:55 Shiki
    Added ARPReport() and ARPRemove().
    Fixed ARPAdd().

    37    2/10/06 18:27 Shiki
    Revised a comment.

    36    2/09/06 18:17 Shiki
    Clean up.

    35    1/24/06 14:55 Shiki
    Modified ARPHold() to increment interface->stat.outDiscards if it
    discards a packet.

    34    1/12/06 11:42 Shiki
    Fixed DiscardPendingPackets() to call ICMPFreeDatagram().

    33    12/13/05 19:36 Shiki
    Revised to conform RFC 3927.

    32    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    33    6/29/04 11:06 Shiki
    Modified the use of IF_FLAG_* for better loopback support. Now
    IF_FLAG_* is set to IFDatagram{} before sending the packet.

    31    2/23/04 13:49 Shiki
    Fixed wrong assertion in ARPHold().

    30    10/29/03 21:57 Shiki
    Revised using IFInitDatagram().

    29    8/20/03 16:36 Shiki
    Added ARPAdd().

    27    5/15/03 15:54 Shiki
    Modified to clear the IF_DATAGRAM_FLAG_DROP bit in IFDatagram.flag
    before sending a Ethernet packet.

    26    5/03/03 13:07 Shiki
    Clean up.

    25    4/28/03 18:50 Shiki
    Modified DetectCollision() to keep conf->addr upon failure.

    24    4/28/03 18:18 Shiki
    Fixed to have a random interval before the next ARP probe when an
    address collision is detected in ARPClaim().

    23    4/28/03 16:18 Shiki
    Clean up.

    22    4/28/03 15:57 Shiki
    Implemented ARPRefresh().

    21    4/18/03 22:06 Shiki
    Implemented ARPRevalidate().  XXX not fully checked yet.

    20    3/07/03 10:43 Shiki
    Fixed ARPOut() to use link-level broadcast for a link-local sender IP
    address.
    Added support for IP_ERR_ADDR_COLLISION.
    Revised ARPGratuitous() to send the 2nd gratuitous ARP after three
    seconds.

    19    10/07/02 10:40 Shiki
    Modified not to transmit ARP packet if host is configured by PPPoE.

    18    8/05/02 9:19 Shiki
    Clean up.

    17    7/29/02 10:24 Shiki
    Implemented Ethernet packet length check code.

    16    7/11/02 16:25 Shiki
    Fixed a bug in ARPHold().

    15    07/01/02 13:29 Shiki
    Fixed ARPHold() so that it releases the datagram memory in the reverse
    order to the allocation order to cooperate with IFFifo component.
    Fixed ARPOut() so that it allocates the datagram memory by a single
    call to interface->alloc to cooperate with IFFifo component.

    14    4/24/02 11:17 Shiki
    Added more ASSERT()s.

    13    4/23/02 20:40 Shiki
    Fixed ARPGratuitous() to make it broadcast its request.

    12    4/19/02 11:01 Shiki
    Fixed alarm handling code bugs.

    11    4/18/02 18:33 Shiki
    Fixed typo in IP_ERR_INS_RESOURCES.

    10    4/18/02 9:40 Shiki
    Fixed DiscardPendingPackets() not to call redundant interface->free().

    9     4/17/02 19:49 Shiki
    Fixed ARP packet memory management code.

    8     4/15/02 12:46 Shiki
    Modified to call IPRecoverGateway() after request timeout.

    7     4/12/02 13:31 Shiki
    Fixed ARPHold() to discard datagram safely if required.

    6     4/10/02 14:39 Shiki
    Fixed ARPOut() not to set wrong datagram length.

    5     4/09/02 18:57 Shiki
    Fixed ARPHold() it can work even if the datagram is allocated from the
    interface send fifo.

    4     3/27/02 19:52 Shiki
    Added support for multicast address.

    3     3/18/02 14:19 Shiki
    Fixed to cancel the outgoing datagram whenever necessary.

    2     3/13/02 9:14 Shiki
    Clean up with IP_ALEN and ETH_ALEN.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifdef IOP_OS
#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <stddef.h>
#else
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#endif // IOP_OS

#include <dolphin/socket.h>
#include "IPPrivate.h"
#include "IPArp.h"

#ifdef IOP_OS
#include <dolphin/ip/iop_netif.h>
#endif // IOP_OS

// Constants from RFC 3927
#define PROBE_WAIT           1 // second   (initial random delay)
#define PROBE_NUM            3 //          (number of probe packets)
#define PROBE_MIN            1 // second   (minimum delay till repeated probe)
#define PROBE_MAX            2 // seconds  (maximum delay till repeated probe)
#define ANNOUNCE_WAIT        2 // seconds  (delay before announcing)
#define ANNOUNCE_NUM         2 //          (number of announcement packets)
#define ANNOUNCE_INTERVAL    2 // seconds  (time between announcement packets)
#define MAX_CONFLICTS       10 //          (max conflicts before rate limiting)
#define RATE_LIMIT_INTERVAL 60 // seconds  (delay between successive attempts)
#define DEFEND_INTERVAL     10 // seconds  (minimum interval between defensive

static void ARPCancel(ARPCache* cache);

//
// ARP RFC826, RFC1122
//

static ARPCache Cache[NARP];
static IFQueue  Up;
static IFQueue  Free;

#ifndef IOP_OS
static OSAlarm  GratuitousAlarm;
#endif // IOP_OS

static char* ARPNtoA(const u8* addr, s32 len)
{
    static char ascii[18];
    int   i;
    char* p;
#ifdef IOP_OS
    int   num = 0;
    int   total = 0;
#endif

    ASSERT(1 <= len);
    len = MIN(len, ETH_ALEN);
    for (i = 0, p = ascii; i < len; ++i)
    {
#ifdef IOP_OS
        num = snprintf(p, 18-total, "%02x", addr[i]);
        total += num;
        p += num;
        if (i < len - 1)
        {
            num = snprintf(p, 18-total, ":");
            total += num;
            p += num;
        }
#else
        p += sprintf(p, "%02x", addr[i]);
        if (i < len - 1)
        {
            p += sprintf(p, ":");
        }
#endif // IOP_OS
    }
    return ascii;
    return NULL;
}

void ARPDumpPacket(const ETHHeader* eh, s32 len)
{
#ifdef IOP_OS
    ARPHeader* arp = (ARPHeader*) ((u8*) eh + ETH_HLEN + NET_IP_ALIGN);
#else
    ARPHeader* arp = (ARPHeader*) ((u8*) eh + ETH_HLEN);
#endif

    // Source hardware address
    OSReport("%s ", ARPNtoA(eh->src, ETH_ALEN));

    // Destination hardware address
    OSReport("%s ", ARPNtoA(eh->dst, ETH_ALEN));

    switch (eh->type)
    {
      case ETH_ARP:
        OSReport("arp %d:\n", len);
        break;
      case ETH_RARP:
        OSReport("rarp %d:\n", len);
        break;
    }

    switch (arp->opCode)
    {
      case ARP_OPCODE_REQUEST:
        OSReport("arp who-has %s ", IPNtoA(ARPGetDstPrAddr(arp)));
        OSReport("tell %s\n", IPNtoA(ARPGetSrcPrAddr(arp)));
        break;
      case ARP_OPCODE_REPLY:
        OSReport("arp reply %s ", IPNtoA(ARPGetSrcPrAddr(arp)));
        OSReport("is-at %s\n", ARPNtoA(ARPGetSrcHwAddr(arp), arp->hwAddrLen));
        break;
      case ARP_OPCODE_REQUEST_REVERSE:
        OSReport("rarp who-is %s ", ARPNtoA(ARPGetSrcHwAddr(arp), arp->hwAddrLen));
        OSReport("tell %s\n", ARPNtoA(ARPGetSrcHwAddr(arp), arp->hwAddrLen));
        break;
      case ARP_OPCODE_REPLY_REVERSE:
        OSReport("rarp reply %s ", ARPNtoA(ARPGetDstHwAddr(arp), arp->hwAddrLen));
        OSReport("at %s\n", IPNtoA(ARPGetDstPrAddr(arp)));
        break;
    }
}

void ARPDump(void)
{
    ARPCache* ent;
    ARPCache* next;

    if (IP_ADDR_NE(__IFDefault.addr, IPAddrAny))
    {
        OSReport("Internet Address: %d.%d.%d.%d\n",
                 __IFDefault.addr[0], __IFDefault.addr[1], __IFDefault.addr[2], __IFDefault.addr[3]);
    }
    if (IP_ADDR_NE(__IFDefault.alias, IPAddrAny))
    {
        OSReport("Alias Address: %d.%d.%d.%d\n",
                 __IFDefault.alias[0], __IFDefault.alias[1], __IFDefault.alias[2], __IFDefault.alias[3]);
    }
    OSReport("Hardware Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
             __IFDefault.mac[0], __IFDefault.mac[1], __IFDefault.mac[2],
             __IFDefault.mac[3], __IFDefault.mac[4], __IFDefault.mac[5]);
    OSReport("  Internet Address    Hardware Address\n");
    IFIterateQueue(ARPCache*, &Up, ent, next, link)
    {
        OSReport("  %3d.%3d.%3d.%3d     %02x:%02x:%02x:%02x:%02x:%02x\n",
                 ent->prAddr[0], ent->prAddr[1], ent->prAddr[2], ent->prAddr[3],
                 ent->hwAddr[0], ent->hwAddr[1], ent->hwAddr[2],
                 ent->hwAddr[3], ent->hwAddr[4], ent->hwAddr[5]);
    }
    OSReport("\n");
}

s32 ARPReport(IPInterface* interface, void* optval, int* optlen)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused( interface )
#endif // IOP_OS

    int       len;
    ARPCache* ent;
    ARPCache* next;
    ARPEntry* arp;

    len = 0;
    arp = optval;
    IFIterateQueue(ARPCache*, &Up, ent, next, link)
    {
        if (*optlen < len + sizeof(ARPEntry))
        {
            break;
        }
        arp->state = ent->state;
        memcpy(arp->prAddr, ent->prAddr, IP_ALEN);
        memcpy(arp->hwAddr, ent->hwAddr, ETH_ALEN);
        len += sizeof(ARPEntry);
        ++arp;
    }
    *optlen = len;
    return IP_ERR_NONE;
}

static void DiscardPendingPackets(ARPCache* cache, s32 result)
{
    IPInterface* interface;
    IFDatagram*  datagram;

    interface = cache->interface;
    while (!IFIsEmptyQueue(&cache->queue))
    {
        IFDequeueHead(IFDatagram*, &cache->queue, datagram, link);
        ASSERT(datagram->queue == &cache->queue);
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

static void Revalidate(ARPCache* cache)
{
    IPInterface* interface;

    switch (cache->state)
    {
      case ARP_CACHE_FREE:
        break;
      case ARP_CACHE_RESOLVED:
        cache->state = ARP_CACHE_POLLING;
        cache->rxmit = ARP_MIN_WAIT;
        // FALL THROUGH
      case ARP_CACHE_PENDING:
      case ARP_CACHE_POLLING:
        interface = cache->interface;
        ARPCancel(cache);
        if (cache->rxmit < ARP_MAX_WAIT)
        {
            cache->rxmit <<= 1;
            ARPOut(interface,
                   ARP_OPCODE_REQUEST, cache->prAddr,
                   (cache->state == ARP_CACHE_POLLING) ? cache->hwAddr : NULL,
                   IP_ADDR_EQ(interface->addr, IPAddrAny) ? interface->alias : interface->addr,
                   cache);
        }
        else
        {
            // Switch to another gateway [RFC 816]
            IPRecoverGateway(cache->prAddr);

            IFDequeueItem(ARPCache*, &Up, cache, link);
            OSCancelAlarm(&cache->alarm);
            cache->state = ARP_CACHE_FREE;
            IFEnqueueHead(ARPCache*, &Free, cache, link);
            DiscardPendingPackets(cache, IP_ERR_UNREACHABLE);
        }
        break;
    }
}

static void TimeoutCallback(OSAlarm* alarm, OSContext* context)
{
#ifdef IOP_OS
    TCPIP_UNUSED(context);
#else
    #pragma unused(context)
#endif // IOP_OS
    ARPCache*    cache;

    cache = (ARPCache*) ((u8*) alarm - offsetof(ARPCache, alarm));
    Revalidate(cache);
}

static void SendCallback(ARPCache* cache, s32 result)
{
#ifdef IOP_OS
    TCPIP_UNUSED(result);
#else
    #pragma unused(result)
#endif // IOP_OS
    
    ASSERT(cache->datagram.interface == NULL);
    ASSERT(cache->datagram.queue == NULL);

    switch (cache->state)
    {
      case ARP_CACHE_PENDING:
      case ARP_CACHE_POLLING:
        OSCancelAlarm(&cache->alarm);
        OSSetAlarm(&cache->alarm, OSSecondsToTicks((OSTime) cache->rxmit), TimeoutCallback);
        break;
      default:
        break;
    }
}

void ARPInit(void)
{
    ARPCache* ent;

    memset(Cache, 0, sizeof Cache);
    IFInitQueue(&Up);
    IFInitQueue(&Free);
    for (ent = &Cache[0]; ent < &Cache[NARP]; ++ent)
    {
        OSCreateAlarm(&ent->alarm);
        IFEnqueueTail(ARPCache*, &Free, ent, link);
    }
}

static ARPCache* Lookup(const u8* prAddr)
{
    ARPCache* ent;
    ARPCache* next;

    IFIterateQueue(ARPCache*, &Up, ent, next, link)
    {
        if (IP_ADDR_EQ(ent->prAddr, prAddr) &&
            (ent->state == ARP_CACHE_RESOLVED ||
             ent->state == ARP_CACHE_POLLING))
        {
            return ent;
        }
    }
    return NULL;
}

// Looks up an ARP entry given a protocol address
s32 ARPLookup(IPInterface* interface, const u8* prAddr, u8* hwAddr)
{
    ARPCache* ent;

    if (IP_CLASSD(prAddr))
    {
        hwAddr[0] = 0x01;
        hwAddr[1] = 0x00;
        hwAddr[2] = 0x5e;
        hwAddr[3] = (u8) (prAddr[1] & 0x7f);
        hwAddr[4] = prAddr[2];
        hwAddr[5] = prAddr[3];
        return ARP_MULTICAST;
    }

    if (IPIsBroadcastAddr(interface, prAddr))
    {
        memset(hwAddr, 0xff, ETH_ALEN);
        return ARP_BROADCAST;
    }

    if (IPIsLoopbackAddr(interface, prAddr))
    {
        memmove(hwAddr, interface->mac, ETH_ALEN);
        return ARP_LOOPBACK;
    }

    ent = Lookup(prAddr);
    if (ent)
    {
        // LRU
        if ((ARPCache*) IFQueryQueueHead(&Up) != ent)
        {
            IFDequeueItem(ARPCache*, &Up, ent, link);
            IFEnqueueHead(ARPCache*, &Up, ent, link);
        }
        memmove(hwAddr, ent->hwAddr, ETH_ALEN);
#ifdef VERBOSE
        OSReport("ARPLookup: %d.%d.%d.%d (%02x-%02x-%02x-%02x-%02x-%02x)\n",
                 prAddr[0], prAddr[1], prAddr[2], prAddr[3],
                 hwAddr[0], hwAddr[1], hwAddr[2], hwAddr[3], hwAddr[4], hwAddr[5]);
#endif
        return ARP_FOUND;
    }

    return ARP_NOT_FOUND;
}

void ARPRevalidate(const u8* prAddr)
{
    ARPCache* ent;

    ent = Lookup(prAddr);
    if (ent)
    {
        Revalidate(ent);
    }
}

static ARPCache* ARPAlloc(const u8* prAddr, BOOL alloc)
{
    ARPCache* ent;
    ARPCache* next;
    ARPCache* free;

    // Lookup an ARP entry given a source protocol address
    IFIterateQueue(ARPCache*, &Up, ent, next, link)
    {
        if (IP_ADDR_EQ(ent->prAddr, prAddr))
        {
            return ent;
        }
    }

    if (!alloc)
    {
        return NULL;
    }

    if (!IFIsEmptyQueue(&Free))
    {
        IFDequeueHead(ARPCache*, &Free, free, link);
    }
    else
    {
        IFDequeueTail(ARPCache*, &Up, free, link);
        ARPCancel(free);
        OSCancelAlarm(&free->alarm);
        if (free->state == ARP_CACHE_PENDING)
        {
            DiscardPendingPackets(free, IP_ERR_INS_RESOURCES);
        }
        ASSERT(IFIsEmptyQueue(&free->queue));
    }

    memset(free, 0, sizeof(ARPCache));
    IFInitQueue(&free->queue);
    OSCreateAlarm(&free->alarm);
    free->rxmit = ARP_MIN_WAIT;
    memmove(free->prAddr, prAddr, IP_ALEN);
    IFEnqueueHead(ARPCache*, &Up, free, link);

    return free;
}

s32 ARPAdd(IPInterface* interface, const u8* prAddr, const u8* hwAddr)
{
    ARPCache* cache;

    cache = ARPAlloc(prAddr, TRUE);
    if (!cache)
    {
        return IP_ERR_INS_RESOURCES;
    }
    ARPCancel(cache);
    OSCancelAlarm(&cache->alarm);
    cache->state = ARP_CACHE_RESOLVED;
    cache->interface = interface;
    cache->rxmit = ARP_TIMEOUT;
    OSSetAlarm(&cache->alarm, OSSecondsToTicks((OSTime) cache->rxmit), TimeoutCallback);
    memmove(cache->hwAddr, hwAddr, ETH_ALEN);
    return IP_ERR_NONE;
}

s32 ARPRemove(IPInterface* interface, const u8* prAddr, const u8* hwAddr)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
    TCPIP_UNUSED(hwAddr);
#else
    #pragma unused( interface, hwAddr )
#endif // IOP_OS
    
    ARPCache* cache;

    cache = ARPAlloc(prAddr, FALSE);
    if (cache)
    {
        IFDequeueItem(ARPCache*, &Up, cache, link);
        OSCancelAlarm(&cache->alarm);
        cache->state = ARP_CACHE_FREE;
        IFEnqueueHead(ARPCache*, &Free, cache, link);
        DiscardPendingPackets(cache, IP_ERR_UNREACHABLE);
    }
    return IP_ERR_NONE;
}

// Create an entry for dst and hold the datagram.
// Returns FALSE if there is an entry for the specified
// address. (i.e., ARP request has already been sent.)
void ARPHold(IPInterface* interface, IFDatagram* datagram)
{
    ARPCache*  free;
    int        state;
    IFCallback callback;
    void*      param;
    BOOL       discard;
    s32        nVec;
    IFVec      va[IF_MAX_VEC];
    IFVec*     vec;

    ASSERT(datagram->interface == interface);
    callback = datagram->callback;
    param    = datagram->param;
    datagram->interface = NULL;
    datagram->queue     = NULL;

    free = ARPAlloc(datagram->dst, TRUE);
    ASSERT(free);
    ASSERT(free->state != ARP_CACHE_RESOLVED && free->state != ARP_CACHE_POLLING);
    state = free->state;
    free->state = ARP_CACHE_PENDING;
    free->interface = interface;

    // Save the packet [RFC1122]
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
        datagram->queue     = &free->queue;
        IFEnqueueTail(IFDatagram*, &free->queue, datagram, link);
    }
    else
    {
        ++interface->stat.outDiscards;
        if (callback)
        {
            callback(param, IP_ERR_INS_RESOURCES);
        }
    }

    if (state == ARP_CACHE_FREE)
    {
        // ARP request has not been sent. Send one.
        ARPOut(interface,
               ARP_OPCODE_REQUEST, free->prAddr, NULL,
               IP_ADDR_EQ(interface->addr, IPAddrAny) ? interface->alias : interface->addr,
               free);
    }
}

// Update ARP cache and transmits waiting packets
static void ARPUpdate(IPInterface* interface, ARPHeader* arp)
{
    ARPCache* cache;
    int       state;
    u8*       src;

    src = ARPGetSrcPrAddr(arp);
    if (IP_CLASSD(src) || IP_CLASSE(src) ||
        IP_ADDR_EQ(src, IPAddrAny) ||
        IPIsBroadcastAddr(interface, src))
    {
        // Avoid polluting ARP caches
        return;
    }

    // Lookup an ARP entry given a source protocol address
    // If the request is not directed at the receiver, do not alloc new entry.
    cache = ARPAlloc(src,
                     IP_ADDR_EQ(ARPGetDstPrAddr(arp), interface->addr) ||
                     IP_ADDR_EQ(ARPGetDstPrAddr(arp), interface->alias));
    if (cache == NULL)
    {
        return;
    }

    ARPCancel(cache);
    OSCancelAlarm(&cache->alarm);
    cache->rxmit = ARP_TIMEOUT;
    OSSetAlarm(&cache->alarm, OSSecondsToTicks((OSTime) cache->rxmit), TimeoutCallback);

    state = cache->state;
    cache->state = ARP_CACHE_RESOLVED;
    memmove(cache->hwAddr, ARPGetSrcHwAddr(arp), ETH_ALEN);
    if (cache->interface != interface)
    {
        DiscardPendingPackets(cache, IP_ERR_UNREACHABLE);
        cache->interface = interface;
    }

#ifdef VERBOSE
    OSReport("ARPUpdate: %d.%d.%d.%d (%02x-%02x-%02x-%02x-%02x-%02x)\n",
             cache->prAddr[0], cache->prAddr[1], cache->prAddr[2], cache->prAddr[3],
             cache->hwAddr[0], cache->hwAddr[1], cache->hwAddr[2], cache->hwAddr[3], cache->hwAddr[4], cache->hwAddr[5]);
#endif

    // Transmit waiting packets using the sender's address
    if (state == ARP_CACHE_PENDING)
    {
        while (!IFIsEmptyQueue(&cache->queue))
        {
            IFDatagram* datagram;

            IFDequeueHead(IFDatagram*, &cache->queue, datagram, link);
            ASSERT(datagram->queue == &cache->queue);
            ASSERT(datagram->type == ETH_IP);
            ASSERT(ARPLookup(interface, datagram->dst, datagram->hwAddr) == ARP_FOUND);
            datagram->queue = NULL;
            interface->out(interface, datagram);
        }
    }
}

void ARPOut(IPInterface* interface,
            u16 opCode,
            const u8* dstPrAddr, const u8* dstHwAddr,
            const u8* srcPrAddr,
            ARPCache* cache)
{
    BOOL        enabled;
    IFDatagram* datagram;
    ARPHeader*  arp;

    enabled = OSDisableInterrupts();

    if (interface->out != ETHOut)
    {
        // PPP
        OSRestoreInterrupts(enabled);
        return;
    }

    if (cache)
    {
        datagram = &cache->datagram;
        arp = (ARPHeader*) cache->arp;
        ASSERT(datagram->queue == NULL);
    }
    else
    {
        datagram = interface->alloc(interface, sizeof(IFDatagram) + ARP_HLEN + 2 * (ETH_ALEN + IP_ALEN));
        if (datagram)
        {
            arp = (ARPHeader*) ((u8*) datagram + sizeof(IFDatagram));
        }
    }
    if (datagram)
    {
        arp->hwType = ARP_HARDWARE_ETHERNET;
        arp->prType = ARP_PROTOCOL_IP;
        arp->hwAddrLen = ETH_ALEN;
        arp->prAddrLen = IP_ALEN;
        arp->opCode = opCode;
        memmove(ARPGetDstPrAddr(arp), dstPrAddr, IP_ALEN);
        if (dstHwAddr)
        {
            memmove(ARPGetDstHwAddr(arp), dstHwAddr, ETH_ALEN);
        }
        else
        {
            memset(ARPGetDstHwAddr(arp), 0x00, ETH_ALEN);
        }
        memmove(ARPGetSrcPrAddr(arp), srcPrAddr, IP_ALEN);
        memmove(ARPGetSrcHwAddr(arp), interface->mac,  ETH_ALEN);

        IFInitDatagram(datagram, ETH_ARP, 1);
        datagram->vec[0].data = arp;
        datagram->vec[0].len  = ARP_HLEN + 2 * (ETH_ALEN + IP_ALEN);
        datagram->callback = (IFCallback) (cache ? SendCallback : NULL);
        datagram->param    = cache;

        // All ARP packets (*replies* as well as requests) that contain a Link-
        // Local 'sender IP address' MUST be sent using link-layer broadcast
        // instead of link-layer unicast.  This aids timely detection of
        // duplicate addresses. [RFC 3927]
        if (dstHwAddr && !IPIsLinkLocalAddr(interface, srcPrAddr))
        {
            memmove(datagram->hwAddr, dstHwAddr, ETH_ALEN);
            datagram->flag |= IF_FLAG_UNICAST;
        }
        else
        {
            memmove(datagram->hwAddr, ETHAddrBroadcast, ETH_ALEN);
            datagram->flag |= IF_FLAG_BROADCAST;
        }

        interface->out(interface, datagram);
    }

    OSRestoreInterrupts(enabled);
}

static void ARPCancel(ARPCache* cache)
{
    IFDatagram*  datagram;
    IPInterface* interface;

    datagram  = &cache->datagram;
    interface = datagram->interface;
    if (interface)
    {
        interface->cancel(interface, datagram);
    }
}

static void GratuitousCallback(OSAlarm* alarm, OSContext* context)
{
#ifdef IOP_OS
    TCPIP_UNUSED(alarm);
    TCPIP_UNUSED(context);
#else
    #pragma unused(alarm, context)
#endif // IOP_OS
    
    IPInterface* interface;

    interface = (IPInterface*) ((u8*) alarm - offsetof(IPInterface, gratuitousAlarm));
    if (IP_ADDR_NE(interface->addr, IPAddrAny))
    {
        ARPOut(interface, ARP_OPCODE_REQUEST, interface->addr,  NULL, interface->addr,
               NULL);
    }
    if (IP_ADDR_NE(interface->alias, IPAddrAny))
    {
        ARPOut(interface, ARP_OPCODE_REQUEST, interface->alias, NULL, interface->alias,
               NULL);
    }
}

// Having probed to determine a unique address to use, the host MUST
// then announce its claimed address by broadcasting ANNOUNCE_NUM ARP
// announcements, spaced ANNOUNCE_INTERVAL seconds apart. [RFC 3927]
//
// Note since GameCube BBA takes about 2.5 seconds to link up, and thus any
// application program must check the link state by IPGetLinkState() before
// calling SOStartup().
void ARPGratuitous(IPInterface* interface)
{
    OSCancelAlarm(&interface->gratuitousAlarm);
    OSSetAlarm(&interface->gratuitousAlarm,
               OSSecondsToTicks(ANNOUNCE_INTERVAL),
               GratuitousCallback);

    if (IP_ADDR_NE(interface->addr, IPAddrAny))
    {
        ARPOut(interface, ARP_OPCODE_REQUEST, interface->addr,  NULL, interface->addr,
               NULL);
    }
    if (IP_ADDR_NE(interface->alias, IPAddrAny))
    {
        ARPOut(interface, ARP_OPCODE_REQUEST, interface->alias, NULL, interface->alias,
               NULL);
    }
}

void ARPProbe(IPInterface* interface, const u8* prAddr)
{
    ARPOut(interface, ARP_OPCODE_REQUEST, prAddr, NULL, IPAddrAny,
           NULL);
}

static void ClaimHandler(OSAlarm* alarm, OSContext* context)
{
#ifdef IOP_OS
    TCPIP_UNUSED(context);
#else
    #pragma unused(context)
#endif // IOP_OS
    
    IPInterfaceConf* conf;
    IPInterface* interface;

    conf = (IPInterfaceConf*) ((u8*) alarm - offsetof(IPInterfaceConf, alarm));
    interface = conf->interface;

    ++conf->count;
    if (conf->count <= PROBE_NUM)
    {
        // then send PROBE_NUM probe packets, each of these
        // probe packets spaced randomly, PROBE_MIN to PROBE_MAX seconds apart.
        // [RFC 3927]
        OSTime wait;

        ARPProbe(interface, conf->addr);
        // XXX if there is ins. memory, probe packet might not be sent,
        //     which is considered to be very harmful...

        if (conf->count < PROBE_NUM)
        {
            wait = IPRandTime(interface, OSSecondsToTicks(PROBE_MIN), OSSecondsToTicks(PROBE_MAX));
        }
        else
        {
            // If, by ANNOUNCE_WAIT seconds after the transmission of the last ARP
            // Probe no conflicting ARP Reply or ARP Probe has been received, then
            // the host has successfully claimed the desired IPv4 Link-Local
            // address. [RFC 3927]
            wait = OSSecondsToTicks(ANNOUNCE_WAIT);
        }
        OSSetAlarm(&conf->alarm, wait, ClaimHandler);
    }
    else
    {
        conf->callback(conf, IP_ERR_NONE);
    }
}

// Send four ARP probes spaced two seconds apart
// De-claim address if conf->addr is 0.0.0.0
void ARPClaim(IPInterface* interface, IPInterfaceConf* conf)
{
    BOOL   enabled;

    ASSERT(interface);
    enabled = OSDisableInterrupts();
    if (IP_ADDR_NE(conf->addr, IPAddrAny))
    {
        ASSERT(conf->callback);
        if (conf->interface == NULL)
        {
            conf->interface = interface;
            IFEnqueueTail(IPInterfaceConf*, &interface->queue, conf, link);
        }

        OSCancelAlarm(&conf->alarm);
        conf->count = 0;

        // Do not send probe imedeately:
        //
        //    When ready to begin probing, the host should then wait for a random
        //    time interval selected uniformly in the range zero to PROBE_WAIT
        //    seconds [RFC 3927]
        OSSetAlarm(&conf->alarm, IPRandTime(interface, 0, OSSecondsToTicks(PROBE_WAIT)),
                   ClaimHandler);
    }
    else if (conf->interface == interface)
    {
        // De-claim
        OSCancelAlarm(&conf->alarm);
        IFDequeueItem(IPInterfaceConf*, &interface->queue, conf, link);
        conf->interface = NULL;
    }
    OSRestoreInterrupts(enabled);
}

static BOOL IsConflicting(IPInterface* interface, ARPHeader* arp, u8* addr)
{
    if (IP_ADDR_NE(IPAddrAny, addr) &&
        IP_ADDR_EQ(ARPGetSrcPrAddr(arp), addr) &&
        memcmp(ARPGetSrcHwAddr(arp), interface->mac, ETH_ALEN) != 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static BOOL DetectCollision(IPInterface* interface, ARPHeader* arp)
{
    IPInterfaceConf* conf;
    IPInterfaceConf* next;

    IFIterateQueue(IPInterfaceConf*, &interface->queue, conf, next, link)
    {
        if (IP_ADDR_NE(IPAddrAny, conf->addr) &&
            memcmp(ARPGetSrcHwAddr(arp), interface->mac, ETH_ALEN) != 0 &&
            (IP_ADDR_EQ(ARPGetSrcPrAddr(arp), conf->addr) ||
             (IP_ADDR_EQ(ARPGetDstPrAddr(arp), conf->addr) &&
              IP_ADDR_EQ(ARPGetSrcPrAddr(arp), IPAddrAny))))
        {
            OSCancelAlarm(&conf->alarm);
            if (conf->callback)
            {
                conf->callback(conf, IP_ERR_ADDR_COLLISION);
            }
        }
    }

    if (IsConflicting(interface, arp, interface->addr) ||
        IsConflicting(interface, arp, interface->alias))
    {
        IPSetConfigError(interface, IP_ERR_ADDR_COLLISION);
        return TRUE;
    }

    return FALSE;
}

void ARPIn(IPInterface* interface, ETHHeader* eh, s32 len, u32 flag)
{
#ifdef IOP_OS
    TCPIP_UNUSED(flag);
#else
    #pragma unused(flag)
#endif // IOP_OS
    
#ifdef IOP_OS
    ARPHeader* arp = (ARPHeader*) ((u8*) eh + ETH_HLEN + NET_IP_ALIGN);
#else
    ARPHeader* arp = (ARPHeader*) ((u8*) eh + ETH_HLEN);
#endif // IOP_OS

    BOOL       conflicting;

    if (interface->out != ETHOut)
    {
        // PPP
        return;
    }

#ifdef IOP_OS
    if (len < ETH_HLEN + NET_IP_ALIGN + ARP_HLEN ||
        len < ETH_HLEN + NET_IP_ALIGN + ARP_HLEN + 2 * (arp->hwAddrLen + arp->prAddrLen))
#else
    if (len < ETH_HLEN + ARP_HLEN ||
        len < ETH_HLEN + ARP_HLEN + 2 * (arp->hwAddrLen + arp->prAddrLen))
#endif // IOP_OS
    {
        // Short packet
        return;
    }

    // Ether and IP only
    if (arp->hwType != ARP_HARDWARE_ETHERNET ||
        arp->prType != ARP_PROTOCOL_IP ||
        arp->hwAddrLen != ETH_ALEN ||
        arp->prAddrLen != IP_ALEN)
    {
        // Discard the request packet.
        return;
    }

#ifdef VERBOSE
    ARPDumpPacket(eh, len);
#endif

    // Check for address collision
    conflicting = DetectCollision(interface, arp);

    // Update ARP cache and transmits waiting packets.
    // If IP address in the request has been in the cache,
    // the Ethernet address must be updated even if the request
    // is not directed to the receiver.
    if (!conflicting)
    {
        ARPUpdate(interface, arp);
    }

    // Reply to the request
    if (arp->opCode == ARP_OPCODE_REQUEST)
    {
        // If the request is not directed at the receiver, do not replay
        if (IP_ADDR_EQ(ARPGetDstPrAddr(arp), IPAddrAny) ||
            (IP_ADDR_NE(ARPGetDstPrAddr(arp), interface->addr) &&
             IP_ADDR_NE(ARPGetDstPrAddr(arp), interface->alias)))
        {
            return;
        }
        ARPOut(interface,
               ARP_OPCODE_REPLY,
               ARPGetSrcPrAddr(arp), ARPGetSrcHwAddr(arp),
               ARPGetDstPrAddr(arp),
               NULL);
    }
}

s32 ARPRefresh(void)
{
    ARPCache* cache;
    BOOL      enabled;

    enabled = OSDisableInterrupts();
    while (!IFIsEmptyQueue(&Up))
    {
        IFDequeueHead(ARPCache*, &Up, cache, link);
        ARPCancel(cache);
        OSCancelAlarm(&cache->alarm);
        cache->state = ARP_CACHE_FREE;
        IFEnqueueHead(ARPCache*, &Free, cache, link);
        DiscardPendingPackets(cache, IP_ERR_NONE);
    }
    OSRestoreInterrupts(enabled);
    return IP_ERR_NONE;
}

#ifdef IOP_OS
// TODO: it will be removed. This is to work around ARP
void myAddArp( const u8 *Host, u8 *MAC )
{
    ARPAdd(&__IFDefault, Host, MAC);
}
#endif // IOP_OS
