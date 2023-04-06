d1 997
a997 962
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPInterface.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip6/src/IPEther.c $
    
    58    2/21/06 11:45 Shiki
    Fixed ETHIn().

    57    2/14/06 18:47 Shiki
    Revised to collect interface statistics.

    56    2/06/06 9:41 Shiki
    Added IPv6 spoof protection.

    55    06/02/02 14:56 Ueno_kyu
    Modified ETHInitInterface() to assign the specific MAC address for
    IxANVL.

    54    1/20/06 14:02 Shiki
    Modified ETHInitInterface() to set eui64[].

    53    1/13/06 13:15 Shiki
    Fixed ETHIn().

    52    1/06/06 17:44 Shiki
    Revised ICMP packet buffer management code.

    51    12/07/05 20:53 Shiki
    Fixed ETHOut() to emulate external interrupt condition before calling
    GoCallback().

    50    05/12/02 19:23 Ueno_kyu
    Moved ETH_IPv6 case not to be entered from PPPoE case in Go().

    49    04/12/21 16:55 Ueno_kyu
    Removed declaration of __IPVersion.

    48    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    57    04/10/21 16:59 Ueno_kyu
    Enclosed IPv6 specific codes in #ifdef IP_INET6... #endif blocks.

    56    04/09/28 14:49 Ueno_kyu
    Enclosed IPv6 specific code in Go().

    55    04/08/31 19:26 Ueno_kyu
    Added support for IPv6 fragmentation and reassembly.

    54    6/29/04 11:06 Shiki
    Modified the use of IF_FLAG_* for better loopback support. Now
    IF_FLAG_* is set to IFDatagram{} before sending the packet.

    53    6/23/04 14:55 Shiki
    Revised to support Ethernet and other network devices in a uniform way.

    52    6/22/04 14:18 Shiki
    Added support for IPv6 loopback.

    51    6/22/04 13:13 Shiki
    Removed redundant define names.

    50    6/21/04 14:20 Shiki
    Fixed fragment packet handling code.

    49    6/14/04 10:19 Shiki
    Fixed ETHIn() not to decrease len twice.

    48    6/09/04 16:52 Shiki
    Fixed for IPv4 build.

    47    6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    45    2/25/04 14:49 Shiki
    Added support for delayed ACK.

    44    10/29/03 22:02 Shiki
    Added support for fragmenting outgoing datagrams.

    43    10/16/03 11:55 Shiki
    Fixed OnReset() not call IGMPOnReset() other than the last call for
    check.

    42    6/04/03 10:29 Shiki
    Fixed initial variable Mute value to TRUE as the interface is muted by
    default.

    41    6/04/03 9:32 Shiki
    Revised so that an application does not incur interrupts from the
    network interface while it is not configured. Implemented IFMute().

    40    5/28/03 17:30 Shiki
    Added support for inFilter and outFilter to IPInterface{}.

    39    5/15/03 15:54 Shiki
    Modified to clear the IF_FLAG_DROP bit in IFDatagram.flag
    before sending a Ethernet packet.

    38    5/03/03 12:58 Shiki
    Implemented IPInterfaceStat{} support functions.

    37    4/30/03 10:02 Shiki
    Modified LinkCheckHandler() not to check sending state.

    36    3/27/03 17:38 Shiki
    Added support for multicast.

    35    3/12/03 11:30 Shiki
    Modified OnReset() priority to make it lower than socket.

    34    3/07/03 10:44 Shiki
    Added support for IP_ERR_LINK_DOWN.
    Fixed IFInit() not to call ETHGetLinkStateAsync() just after ETHInit()
    is called since ETHGetLinkStateAsync() does not work correctly for 65
    usec after the chip reset.

    33    1/30/03 18:41 Shiki
    Declared __IPVersion.

    32    1/30/03 18:30 Shiki
    Enlarged SendHeap size to support UDP send buffering.

    31    10/07/02 10:41 Shiki
    Modified ETHOut() to an external function.

    30    8/01/02 17:53 Shiki
    Added VERBOSE messages for PPPoE.

    29    8/01/02 10:35 Shiki
    Fixed to apply tail zero-padding to short (< 60) Ethernet packet.

    28    7/31/02 16:13 Shiki
    Added support for PPP.

    27    7/29/02 10:24 Shiki
    Implemented Ethernet packet length check code.

    26    7/29/02 9:03 Shiki
    Implemented ETHIn().

    25    7/11/02 16:26 Shiki
    Fixed GO() to free IFDatagram properly.

    24    02/07/01 13:39 Shiki
    Modified so that the library can use loopback address without the
    broadband adapter.

    23    6/20/02 14:15 Shiki
    Modified GoCallback() to ignore ETH_LTPS_CRSLOST (avoid BBA adapter
    hardware bug).

    22    6/13/02 11:38 Shiki
    Fixed IFInit() so it can be called more than once.

    21    4/30/02 14:49 Shiki
    Fixed OnReset().

    20    4/26/02 17:17 Shiki
    Modified to install OS reset function.

    19    4/25/02 21:04 Shiki
    Revised ETHGetLinkStateAsync() management code.

    18    4/25/02 9:48 Shiki
    Modified to update IPInterface{} tx and rx counts.

    17    4/25/02 9:19 Shiki
    Fixed bugs in datagram canceling mechanism. Previously, Cancel() could
    not cancel the currently sending datagram.

    16    4/24/02 11:24 Shiki
    Implemented LinkCheckHandler().
    Modified GoCallback() to check ltps codes. Fixed a bug in GoCallback().

    15    4/23/02 9:13 Shiki
    Modified to include <private/eth.h>.

    14    4/16/02 17:17 Shiki
    Modified not to call GoCallback() recursively from Go() to save stack
    space (a little conservative).

    13    4/15/02 12:44 Shiki
    Implemented a filter against multi-homing land packets.

    12    4/12/02 12:50 Shiki
    Added more ASSERT()s.

    11    4/10/02 10:24 Shiki
    Fixed Callback1() to make it generate correct IF_FLAG_* again.

    10    4/10/02 9:56 Shiki
    Added IP spoof protection code.

    9     4/09/02 19:59 Shiki
    Fixed 'Current' to save all vec{}s.

    8     4/09/02 18:56 Shiki
    Revised SendFifo management code so the it can work even if the
    datagram is allocated from the SendFifo.

    7     4/04/02 17:13 Shiki
    Fixed Callback1() to make it generate correct IF_FLAG_*.

    6     3/27/02 18:57 Shiki
    Modified Out() to check ARP_MULTICAST as well.

    5     3/20/02 13:06 Shiki
    Modified loopback interface so that recvCalback is called after
    sendCallback.

    4     3/18/02 14:29 Shiki
    Fixed the GoCallback() bug that prevents sending a new packet after
    Cancel().

    3     3/13/02 9:14 Shiki
    Clean up with IP_ALEN and ETH_ALEN.

    2     3/11/02 21:12 Shiki
    Clean up.

    1     3/11/02 19:36 Shiki
    Initial check-in.
 *---------------------------------------------------------------------------*/

#include <dolphin/doldefs.h>
/* $NoKeywords: $ */

#include <string.h>

#include <dolphin/os.h>
#include <dolphin/ip.h>
#include <private/eth.h>
#include "IPPrivate.h"
#ifdef IP_INET6
#include "IP6Private.h"
#endif // IP_INET6
#include "IPPPPConf.h"

extern BOOL IPAutoConfig( void );

static u16  Protocols[] =
{
    ETH_IP,
    ETH_ARP,
#ifdef IP_INET6
    ETH_IPv6,
#endif  // IP_INET6
    ETH_PPPoE_DISCOVERY,
    ETH_PPPoE_SESSION
};

const u8 ETHAddrBroadcast[ETH_ALEN] =
{
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

/*
    GC will receive new packets at every 20 usec to 460 usec
    depending on the packet size.
    len includes 4 byte FCS.
 */
void ETHIn(IPInterface* interface, ETHHeader* eh, s32 len)
{
    u32        flag;
    IPHeader*  ip;
    BOOL       localSrc;
    BOOL       localDst;
#ifdef IP_INET6
    IP6Hdr*    ip6;
#endif  // IP_INET6

    if (len < ETH_HLEN)
    {
        // Disacard packet
        ++interface->stat.inErrors;
        return;
    }

    if (interface->inFilter(interface, eh, len) == FALSE)
    {
        // Disacard packet
        ++interface->stat.inDiscards;
        return;
    }

    // [RFC1122] The link layer MUST include a flag to indicate
    // whether the incoming packet was addressed to a link-layer
    // broadcast address.
    if (memcmp(eh->dst, ETHAddrBroadcast, ETH_ALEN) == 0)
    {
        flag = IF_FLAG_BROADCAST;
        ++interface->stat.inNUcastPkts;
    }
    else if (eh->dst[0] & 0x01)
    {
        flag = IF_FLAG_MULTICAST;
        ++interface->stat.inNUcastPkts;
    }
    else
    {
        flag = IF_FLAG_UNICAST;
        ++interface->stat.inUcastPkts;
    }
    interface->stat.inOctets += len;

    switch (eh->type)
    {
      case ETH_ARP:
        ARPIn(interface, eh, len, flag);
        break;
      case ETH_IP:
        len -= ETH_HLEN;
        if (len < IP_MIN_HLEN)
        {
            // Disacard packet
            return;
        }
        ip = (IPHeader*) ((u8*) eh + ETH_HLEN);
        //
        // IP spoof protection
        //
        if (ip->src[0] == 127 || ip->dst[0] == 127)
        {
            // Reject packets claiming to come from/to the local loopback interface
            break;
        }
        if (IP_ADDR_EQ(ip->src, ip->dst))
        {
            // Land attack protection
            break;
        }
        localSrc = localDst = FALSE;
        if (IP_ADDR_NE(interface->addr, IPAddrAny))
        {
            localSrc |= IP_ADDR_EQ(interface->addr, ip->src);
            localDst |= IP_ADDR_EQ(interface->addr, ip->dst);
        }
        if (IP_ADDR_NE(interface->alias, IPAddrAny))
        {
            localSrc |= IP_ADDR_EQ(interface->alias, ip->src);
            localDst |= IP_ADDR_EQ(interface->alias, ip->dst);
        }
        if (localSrc && localDst)
        {
            // Land attack protection (multi-homing)
            break;
        }
        IPIn(interface, ip, len, flag);
        break;
      case ETH_PPPoE_DISCOVERY:
      case ETH_PPPoE_SESSION:
#ifdef VERBOSE
        PPPoEDumpPacket((PPPoEHeader*) ((u8*) eh + ETH_HLEN));
#endif
        PPPoEIn(interface, eh, len, flag);
        break;
#ifdef IP_INET6
      case ETH_IPv6:
        //
        // IP spoof protection
        //
        ip6 = (IP6Hdr*) ((u8*) eh + ETH_HLEN);
        if (SO_IN6_IS_ADDR_LOOPBACK(&ip6->src) ||
            SO_IN6_IS_ADDR_LOOPBACK(&ip6->dst))
        {
            // Reject packets claiming to come from/to the local loopback interface
            break;
        }
        IP6In(interface, (IP6Hdr*) ((u8*) eh + ETH_HLEN), len - ETH_HLEN, flag);
        break;
#endif  // IP_INET6
      default:
        ++interface->stat.inUnknownProtos;
        break;
    }
}

static void* Callback0(u16 type, s32 len, u8 lrps)
{
    #pragma unused(lrps, len)
    IPInterface* interface;

    interface = &__IFDefault;
    switch (type)
    {
      case ETH_IP:
      case ETH_ARP:
      case ETH_IPv6:
      case ETH_PPPoE_DISCOVERY:
      case ETH_PPPoE_SESSION:
        if (!(interface->flag & IP_IF_FLAG_RESET))
        {
            return interface->recvBuf;
        }
        // FALL THROUGH
      default:
        // Drop packet
        return NULL;
        break;
    }
}

static void Callback1(u8* rbuf, s32 len)
{
    if (ETH_HLEN + 4 <= len)    // +4 for CRC
    {
        ETHIn(&__IFDefault, (ETHHeader*) rbuf, len - 4);
    }
}

// Return TRUE to loopback
static BOOL Go(void)
{
    static void GoCallback(u8 ltps);
    IPInterface* interface;
    BOOL         enabled;
    IFDatagram*  datagram;
    ETHHeader*   eh;
    s32          len;
    s32          plen;
    u8*          ptr;
    IFVec*       vec;
    IFVec*       end;
    BOOL         loopback;
    BOOL         eth;    // TRUE if using ETH
    BOOL         discard;
    int          dlen;

    interface = &__IFDefault;
    switch (interface->type)
    {
      case IF_TYPE_AUTO:
      case IF_TYPE_100FULL:
      case IF_TYPE_100HALF:
      case IF_TYPE_10FULL:
      case IF_TYPE_10HALF:
        eth = TRUE;
        break;
      default:
        eth = FALSE;
        break;
    }

    enabled = OSDisableInterrupts();

    ASSERT(!IFIsEmptyQueue(&interface->sendQueue) || interface->sendFifo.used == 0);
    if ((interface->loopback & IF_FLAG_LOOPBACK) ||
        interface->sending ||
        IFIsEmptyQueue(&interface->sendQueue))
    {
        OSRestoreInterrupts(enabled);
        return FALSE;
        // NOT REACHED HERE
    }

#ifdef _DEBUG
{
    int i;

    datagram = (IFDatagram*) IFQueryQueueHead(&interface->sendQueue);
    for (i = 0; i < sizeof Protocols / sizeof Protocols[0]; ++i)
    {
        if (datagram->type == Protocols[i])
            break;
    }
    if (sizeof Protocols / sizeof Protocols[0] <= i)
    {
        OSHalt("Sending illegal packet type.");
    }
}
#endif

    // The IP layer MAY implement a mechanism to fragment
    // outgoing datagrams intentionally.

    // Get the first datagram from SendQueue.
    datagram = (IFDatagram*) IFQueryQueueHead(&interface->sendQueue);
    ASSERT(datagram->queue == &interface->sendQueue);
    ASSERT(datagram->interface == interface);
    interface->sending = datagram;

    // Save the datagram to Current.
    dlen = (s32) (sizeof(IFDatagram) +
                  ((1 < datagram->nVec) ? sizeof(IFVec) * (datagram->nVec - 1) : 0));
    memmove(__IFCurrent, datagram, (u32) dlen);

#ifdef _DEBUG
    if (datagram->type == ETH_IP)
    {
        IPHeader* ip = (IPHeader*) datagram->vec->data;
        ASSERT(IPCheckSum(ip) == 0);
    }
#endif  // _DEBUG

    eh = (ETHHeader*) interface->sendBuf;
    eh->type = datagram->type;
    memmove(eh->dst, datagram->hwAddr, ETH_ALEN);
    memmove(eh->src, interface->mac, ETH_ALEN);

    len = ETH_HLEN;
    ptr = &interface->sendBuf[ETH_HLEN];

    if (0 < datagram->prefixLen)
    {
        ASSERT(datagram->type == ETH_PPPoE_SESSION);
        memmove(ptr, datagram->prefix, datagram->prefixLen);
        len += datagram->prefixLen;
        ptr += datagram->prefixLen;
    }

    switch (datagram->type)
    {
      case ETH_IP:
        plen = IPFragment(datagram, ptr, &discard);
        len += plen;
        ptr += plen;
        break;
#ifdef IP_INET6
      case ETH_IPv6:
        plen = IP6Fragment(datagram, ptr, &discard);
        len += plen;
        ptr += plen;
        break;
#endif // IP_INET6
      case ETH_PPPoE_SESSION:
        if (ETH_HLEN + PPPoE_HLEN + 2 <= len &&
            PPP_IP == *((u16*) &interface->sendBuf[ETH_HLEN + PPPoE_HLEN]))
        {
            plen = IPFragment(datagram, ptr, &discard);
            len += plen;
            ptr += plen;
            break;
        }
        // FALL THROUGH
      default:
        for (vec = datagram->vec, end = &datagram->vec[datagram->nVec];
             vec && vec < end;
             ++vec)
        {
            memmove(ptr, vec->data, (u32) vec->len);
            len += vec->len;
            ptr += vec->len;
        }
        discard = TRUE;
        break;
    }
    if (len < 60)
    {
        memset(ptr, 0, (u32) (60 - len));
    }

    if (discard)
    {
        // Remove the first datagram from SendQueue.
        IFDequeueHead(IFDatagram*, &interface->sendQueue, datagram, link);
        // Though the datagram is committed to send, it still can
        // be canceled by preventing the callback invocation from
        // GoCallback(). So just clear 'queue' here to indicate the
        // datagram has been removed from the queue.
        datagram->queue = NULL;

        // Clean up
        ICMPFreeDatagram(datagram);
        interface->free(interface, datagram, dlen);
        datagram = __IFCurrent;
        for (vec = datagram->vec, end = &datagram->vec[datagram->nVec];
             vec && vec < end;
             ++vec)
        {
            interface->free(interface, vec->data, vec->len);
        }
    }
    else
    {
        // Invoke callback only for the last fragment
        datagram = __IFCurrent;
        datagram->callback = NULL;
    }
    ASSERT(!IFIsEmptyQueue(&interface->sendQueue) || interface->sendFifo.used == 0);

#ifdef VERBOSE
    if (eh->type == ETH_PPPoE_SESSION || eh->type == ETH_PPPoE_DISCOVERY)
    {
        PPPoEDumpPacket((PPPoEHeader*) ((u8*) eh + ETH_HLEN));
    }
#endif

    datagram->flag &= ~IF_FLAG_DROP;
    if (interface->outFilter(interface, interface->sendBuf, len) == FALSE)
    {
        // Disacard packet
        datagram->flag |= IF_FLAG_DROP;
        loopback = TRUE;
    }
    else if (eth && (datagram->flag & (IF_FLAG_UNICAST | IF_FLAG_BROADCAST | IF_FLAG_MULTICAST)))
    {
        ASSERT(memcmp(datagram->hwAddr, interface->mac, ETH_ALEN) != 0);
        loopback = FALSE;
        if (eh->dst[0] & 0x01)
        {
            ASSERT(datagram->flag & (IF_FLAG_BROADCAST | IF_FLAG_MULTICAST));
            ++interface->stat.outNUcastPkts;
        }
        else
        {
            ASSERT(!(datagram->flag & (IF_FLAG_BROADCAST | IF_FLAG_MULTICAST)));
            ++interface->stat.outUcastPkts;
        }
        interface->stat.outOctets += len;
        ETHSendAsync(interface->sendBuf, len, GoCallback);
    }
    else
    {
        loopback = TRUE;
    }

    OSRestoreInterrupts(enabled);

    return loopback;
}

static void GoCallback(u8 ltps)
{
    #pragma unused(ltps)
    IPInterface* interface;
    IFDatagram*  datagram;
    void*        param;
    IFCallback   callback = NULL;
    s32          rc;
    BOOL         eth;    // TRUE if using ETH

    interface = &__IFDefault;
Repeat:
    ASSERT(interface->sending);

    switch (interface->type)
    {
      case IF_TYPE_AUTO:
      case IF_TYPE_100FULL:
      case IF_TYPE_100HALF:
      case IF_TYPE_10FULL:
      case IF_TYPE_10HALF:
        eth = TRUE;
        break;
      default:
        eth = FALSE;
        break;
    }

    rc = IP_ERR_NONE;

    if (eth)
    {
        ETHGetLinkStateAsync((BOOL*) &interface->linkState);
#if 0
        if (ltps & ETH_LTPS_CRSLOST)
        {
            rc = IP_ERR_NETDOWN;
            ltps = 0;
        }
#endif

        if (ltps & 0x0f)
        {
            ++interface->stat.outCollisions;
        }
        if (ltps & ME_LTPS_TERR)
        {
            ++interface->stat.outErrors;
        }
    }

    if (interface->sending != IP_DG_CANCELED)  // Make sure sending packet has not been canceled
    {
        // Note IFDatagram pointed by 'Sending' should not be touched here.
        // It has been copied to __IFCurrent with Go(). Though
        // 'Sending' points to the original datagram structure, whose memory
        // block might have been released already.
        datagram = __IFCurrent;

        callback = datagram->callback;
        param    = datagram->param;
        // Check loopback addresses
        if (datagram->flag & IF_FLAG_DROP)
        {
            interface->loopback = 0x00;
        }
        else
        {
            interface->loopback = (datagram->flag & IF_FLAG_ALL);
        }

        if (callback)
        {
            // Determines whether Sending datagram is not allocated from sendHeap.
            if ((u8*) interface->sending < interface->sendHeap ||
                &interface->sendHeap[IP_IF_SENDHEAPSIZE] <= (u8*) interface->sending)
            {
               interface->sending->interface = NULL;
            }
            callback(param, rc);
        }

        if (0 <= rc && (interface->loopback & IF_FLAG_LOOPBACK))
        {
            switch (datagram->type)
            {
              case ETH_PPPoE_SESSION:
                switch (*((u16*) &interface->sendBuf[ETH_HLEN + PPPoE_HLEN]))
                {
                  case PPP_IP:
                  {
                    IPHeader* ip = (IPHeader*) &interface->sendBuf[ETH_HLEN + datagram->prefixLen];

                    ASSERT(IP_VERSION(ip) == 4);
                    IPIn(&__IFDefault, ip, ip->len, interface->loopback);
                    break;
                  }
                }
                break;
              case ETH_IP:
              {
                IPHeader* ip = (IPHeader*) &interface->sendBuf[ETH_HLEN];

                IPIn(&__IFDefault, ip, ip->len, interface->loopback);
                break;
              }
#ifdef IP_INET6
              case ETH_IPv6:
              {
                IP6Hdr* ip = (IP6Hdr*) &interface->sendBuf[ETH_HLEN];

                IP6In(&__IFDefault, ip, (s32) (ip->plen + sizeof(IP6Hdr)), interface->loopback);
                break;
              }
#endif  // IP_INET6
            }
        }

        interface->loopback = 0x00;
    }

    interface->sending = NULL;
    if (Go())
    {
        goto Repeat;
    }
}

/*---------------------------------------------------------------------------*
  Name:         ETHOut

  Description:  ETHOut() enqueues the specified datagram for future delivery.

  Arguments:    interface   Pointer to the IPInterface to use
                datagram    Pointer to IFDatagram to send

  Returns:      None.

  Callback:     IP_ERR_NONE             Succeeded
                IP_ERR_NETDOWN          Local network interface is donw
                IP_ERR_INS_RESOURCES    ARP cannot hold the datagram
                IP_ERR_UNREACHABLE      ARP unreachable
 *---------------------------------------------------------------------------*/
void ETHOut(IPInterface* interface, IFDatagram* datagram)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    ASSERT(0 < datagram->nVec && datagram->nVec <= IF_MAX_VEC);
    datagram->queue = NULL;
    datagram->interface = interface;
    datagram->offset = 0;
    switch (datagram->type)
    {
      case ETH_ARP:
      case ETH_PPPoE_DISCOVERY:
      case ETH_PPPoE_SESSION:
        datagram->queue = &interface->sendQueue;
        IFEnqueueTail(IFDatagram*, &interface->sendQueue, datagram, link);
        break;
      case ETH_IP:
        switch (ARPLookup(interface, datagram->dst, datagram->hwAddr))
        {
          case ARP_NOT_FOUND:
            ARPHold(interface, datagram);
            break;
          case ARP_LOOPBACK:
          case ARP_FOUND:
          case ARP_BROADCAST:
          case ARP_MULTICAST:
          default:
            // Note fragment must have been processed by IP layer
            datagram->queue = &interface->sendQueue;
            IFEnqueueTail(IFDatagram*, &interface->sendQueue, datagram, link);
#ifdef _DEBUG
            {
                IPHeader* ip = (IPHeader*) datagram->vec->data;
                ASSERT(IPCheckSum(ip) == 0);
            }
#endif  // _DEBUG
            break;
        }
        break;
      case ETH_IPv6:
        datagram->queue = &interface->sendQueue;
        IFEnqueueTail(IFDatagram*, &interface->sendQueue, datagram, link);
        break;
      default:
#ifdef VERBOSE
        OSReport("IP: ETHOut() - Unknow frame type %d\n", datagram->type);
#endif
        break;
    }
    OSRestoreInterrupts(enabled);

    if (Go())
    {
        // Emulate external interrupt condition. Otherwise, thread switch could
        // happen during GoCallback().
        enabled = OSDisableInterrupts();
        OSDisableScheduler();
        GoCallback(0);
        OSEnableScheduler();
        OSYieldThread();
        OSRestoreInterrupts(enabled);
    }
}

static void LinkCheckHandler(OSAlarm* alarm, OSContext* context)
{
    #pragma unused(alarm, context)
    IPInterface* interface = &__IFDefault;
    BOOL         up;

    ASSERT(interface->type != IF_TYPE_NONE);
    up = interface->up;
    ETHGetLinkStateAsync((BOOL*) &interface->linkState);
    interface->up = interface->linkState;

    if (!up && interface->linkState == TRUE)    // Up
    {
        DHCPReboot();
        if (IP_ADDR_NE(interface->alias, IPAddrAny))
        {
            IPAutoConfig();
        }
    }

    if (up && interface->linkState == FALSE)    // Down
    {
        IPSetConfigError(interface, IP_ERR_LINK_DOWN);
    }
}

static void Mute(IPInterface* interface, BOOL mute)
{
    #pragma unused( interface )

    if (mute)
    {
        ETHSetRecvCallback(NULL, NULL);
        ETHClearMulticastAddresses();
    }
    else
    {
        ETHSetRecvCallback(Callback0, Callback1);
    }
}

static BOOL OnReset(IPInterface* interface, BOOL final)
{
    #pragma unused( interface, final )

    return TRUE;
}

BOOL ETHInitInterface(IPInterface* interface, s32 type)
{
    if (ETHInit(type) == ETH_OK)
    {
        if (0 < IPAnvl)
        {
            // Assign the specific mac address for ANVL
            u8 mac[ETH_ALEN];
            mac[0] = 0x00;
            mac[1] = 0x09;
            mac[2] = 0xbf;
            mac[3] = 0x00;
            mac[4] = 0x01;
            mac[5] = 0x44;
            ETHSetMACAddr(mac);
        }

        interface->out = ETHOut;
        interface->started = PPPoEOpen;
        interface->finished = PPPoETerminate;
        interface->mute = Mute;
        interface->onReset = OnReset;

        interface->type = type;
        interface->up = interface->linkState = FALSE;

        ETHGetMACAddr(interface->mac);
        memcpy((u8*) &interface->seed + 2, interface->mac, ETH_ALEN);

#ifdef IP_INET6
        ETHGetEUI64(interface->mac, interface->eui64);
#endif

        // Register callbacks after we've completed all the other initializations
        // so as not to process halfway ETH interrupts.
        ETHSetProtoType(Protocols, sizeof Protocols / sizeof Protocols[0]);
        IFMute(FALSE);

        // Note ETHGetLinkStateAsync() does not respond correctly
        // before 65 usec after ETHInit() is called. Thus the
        // following code does not work as expected. [3/6/2003]
        //      ETHGetLinkStateAsync((BOOL*) &LinkState);
        //      interface->up = LinkState;
        OSCreateAlarm(&interface->linkAlarm);
        OSSetPeriodicAlarm(&interface->linkAlarm, OSGetTime(), OSMillisecondsToTicks(250), LinkCheckHandler);
    }
    return TRUE;
}

#ifdef IP_INET6

u8* ETHGetEUI64(const u8* mac, u8* eui64)
{
    eui64[0] = (u8) (mac[0] ^ 0x02);
    eui64[1] = mac[1];
    eui64[2] = mac[2];
    eui64[3] = 0xff;
    eui64[4] = 0xfe;
    eui64[5] = mac[3];
    eui64[6] = mac[4];
    eui64[7] = mac[5];
    return eui64;
}

SOIn6Addr* ETHGetLinkLocal(const u8* mac, SOIn6Addr* linkLocal)
{
    linkLocal->addr[0] = 0xfe; linkLocal->addr[1] = 0x80;
    linkLocal->addr[2] = 0x00; linkLocal->addr[3] = 0x00;
    linkLocal->addr[4] = 0x00; linkLocal->addr[5] = 0x00;
    linkLocal->addr[6] = 0x00; linkLocal->addr[7] = 0x00;
    ETHGetEUI64(mac, &linkLocal->addr[8]);
    return linkLocal;
}

#endif
