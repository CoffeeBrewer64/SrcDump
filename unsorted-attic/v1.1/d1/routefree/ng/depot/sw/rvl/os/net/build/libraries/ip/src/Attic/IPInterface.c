d1 1501
a1501 1458
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPInterface.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip/src/IPInterface.c $
    
    20    3/06/06 16:07 Shiki
    Enabled IPv6 by default by globally defining IP_INET6.

    19    2/28/06 14:17 Shiki
    Removed a call to IP6ReportPrefixTable().

    18    2/28/06 9:08 Shiki
    Modified IFGetSockOpt() to support SO_CONFIG_IPV6_*_TABLEs.

    17    2/27/06 15:10 Shiki
    Modified IFGetSockOpt() to support SO_CONFIG_*_NUMBERs.

    16    2/27/06 11:02 Shiki
    Modified IFSetSockOpt() to support SO_CONFIG_DNS_DOMAIN_NAME and
    SO_CONFIG_DNS_SERVER_TABLE.

    15    2/23/06 15:14 Shiki
    Modified IFGetSockOpt() to support SO_CONFIG_DNS_DOMAIN_NAME and
    SO_CONFIG_DNS_SERVER_TABLE.

    14    2/23/06 13:59 Shiki
    Modified IFGetSockOpt to support SO_CONFIG_IP_ADDR_TABLE.

    13    2/23/06 10:34 Shiki
    Clean up.

    12    2/22/06 11:13 Shiki
    Modified IFGetSockOpt() to support SO_CONFIG_PPP_MESSAGE.

    11    2/22/06 9:24 Shiki
    Fixed IFSetSockOpt().

    10    2/21/06 14:34 Shiki
    Fixed IFSetSockOpt() # compiler bug?

    9     2/20/06 11:43 Shiki
    Fixed IFGetSockOpt().

    8     2/15/06 13:31 Shiki
    Modified IFGetSockOpt() to support SO_CONFIG_UDP_TABLE,
    SO_CONFIG_UDP6_TABLE, SO_CONFIG_TCP_TABLE and SO_CONFIG_TCP6_TABLE.

    7     2/14/06 18:47 Shiki
    Revised to collect interface statistics.

    6     2/14/06 11:03 Shiki
    Added SO_CONFIG_ERROR.

    5     2/14/06 9:56 Shiki
    Added IFGetSockOpt() and IFSetSockOpt().

    4     1/19/06 17:46 Shiki
    Fixed to send MLD listener done messages during cleanup and before
    reset.

    3     12/08/05 9:22 Shiki
    Modified to set DOLPHIN_LIB_VERSION(IP6) if IP_INET6 is defined.

    2     12/01/05 10:00 Shiki
    Revised to use the PPP configurable parameters in to IPInterface{}.

    1     04/11/02 11:01 Ueno_kyu
    Added support for IPv6 Core Protocol.

    57    04/10/21 16:59 Ueno_kyu
    Enclosed IPv6 specific codes in #ifdef IP_INET6... #endif blocks.

    56    04/10/13 10:53 Ueno_kyu
    Cleanup.

    55    04/10/13 10:28 Ueno_kyu
    Added MDMInitInterface().

    53    6/23/04 15:26 Shiki
    Fixed not to initialize interface->seed by OSGetTime(). Seed should be
    initialized to a fixed value as long as the same NIC is used.

    52    6/23/04 14:55 Shiki
    Revised to support Ethernet and other network devices in a uniform way.

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
    Modified to clear the IF_DATAGRAM_FLAG_DROP bit in IFDatagram.flag
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
#ifdef IP_INET4_ONLY
DOLPHIN_LIB_VERSION(IP4);
#else   // IP_INET4_ONLY
DOLPHIN_LIB_VERSION(IP);
#endif  // IP_INET4_ONLY
/* $NoKeywords: $ */

#include <string.h>

#include <dolphin/os.h>
#include <dolphin/socket.h>
#include <private/eth.h>
#include "IPPrivate.h"
#ifdef IP_INET6
#include "IP6Private.h"
#endif // IP_INET6
#include "IPPPPConf.h"

extern SOResolver  __SOResolver;

extern BOOL IPAutoConfig( void );

static BOOL OnReset( BOOL final );

static OSResetFunctionInfo ResetFunctionInfo =
{
    OnReset,
    OS_RESET_PRIO_IP
};

IPInterface __IFDefault;

static u8 RecvBuf[IP_IF_RECVBUFSIZE] ATTRIBUTE_ALIGN(32);
static u8 SendBuf[IP_IF_SENDBUFSIZE] ATTRIBUTE_ALIGN(32);
static u8 SendHeap[IP_IF_SENDHEAPSIZE];

static struct
{
    IFDatagram     datagram;
    IFVec          vec[IF_MAX_VEC - 1];
} Current;

IFDatagram* __IFCurrent = &Current.datagram;

static BOOL NullFilter(IPInterface* interface, void* frame, s32 len)
{
    #pragma unused(interface, frame, len)
    return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Cancel

  Description:  Cancel() attemps to cancel the datagram. It assumes the
                datagram is in one of pending queue if datagram->queue
                is not NULL.

  Arguments:    interface   Pointer to the IPInterface to use
                datagram    Pointer to IFDatagram to cancel

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void Cancel(IPInterface* interface, IFDatagram* datagram)
{
#ifdef NDEBUG
    #pragma unused(interface)
#endif
    BOOL enabled;

    enabled = OSDisableInterrupts();
    ASSERT(datagram->interface == interface);
    if (interface->sending == datagram) // Is the datagram currently being sent?
    {
        interface->sending = IP_DG_CANCELED;
    }
    if (datagram->queue != NULL)
    {
        IFDequeueItem(IFDatagram*, datagram->queue, datagram, link);
        datagram->queue = NULL;
    }
    datagram->interface = NULL;
    OSRestoreInterrupts(enabled);
}

/*---------------------------------------------------------------------------*
  Name:         Alloc

  Description:  Alloc() allocates the len bytes of fifo buffer.

  Arguments:    interface   Pointer to the IPInterface to use
                len         The size of the buffer to be allocated

  Returns:      A pointer to the allocated memory. NULL if the request fails.
 *---------------------------------------------------------------------------*/
static void* Alloc(IPInterface* interface, s32 len)
{
    void* ptr = IFFifoAlloc(&interface->sendFifo, len);

    if (ptr == NULL)
    {
        ++interface->stat.outDiscards;
    }
    return ptr;
}

/*---------------------------------------------------------------------------*
  Name:         Free

  Description:  Free() releases the memory space pointed to by ptr, whose
                length is len bytes if the block has been allocated with
                Alloc().

  Arguments:    interface   Pointer to the IPInterface to use
                ptr         Pointer to the memory block
                len         The size of the memory block

  Returns:      TRUE if the block has been allocated with Alloc().
                Otherwise, FALSE.
 *---------------------------------------------------------------------------*/
static BOOL Free(IPInterface* interface, void* ptr, s32 len)
{
    return IFFifoFree(&interface->sendFifo, ptr, len);
}

/*---------------------------------------------------------------------------*
  Name:         IFInit

  Description:  IFInit() initializes the broadband adapter and the internet
                library.

  Arguments:    type    Specifies the interface mode. (IF_TYPE_*)

  Returns:      TRUE if the interface has been successfully initialized.
                Otherwise FALSE. If the function failed, do not use any other
                internet library functions.
 *---------------------------------------------------------------------------*/
BOOL IFInit(s32 type)
{
    static BOOL  initialized;
    IPInterface* interface = &__IFDefault;

    if (initialized)
    {
        IFMute(FALSE);
        return TRUE;
    }
    initialized = TRUE;
#ifdef IP_INET4_ONLY
    OSRegisterVersion(__IP4Version);
#else   // IP_INET6
    OSRegisterVersion(__IPVersion);
#endif  // IP_INET6

    interface->type = IF_TYPE_NONE;
    interface->up = interface->linkState = FALSE;
    OSCreateAlarm(&interface->gratuitousAlarm);
    interface->mtu = 1500;
    interface->flag = IP_IF_FLAG_MUTE;

    // Link layer
    interface->recvBuf = RecvBuf;
    interface->sendBuf = SendBuf;
    interface->sendHeap = SendHeap;
    IFFifoInit(&interface->sendFifo, SendHeap, IP_IF_SENDHEAPSIZE);
    IFInitQueue(&interface->sendQueue);

    // TCP parameters
    interface->closeWaitInterval = OSSecondsToTicks(2LL * TCP_MSL);
    interface->minRtt = OSMillisecondsToTicks((OSTime) TCP_MIN_RTT);
    interface->maxRtt = OSSecondsToTicks((OSTime) TCP_MAX_RTT);
    interface->defaultRtt = OSSecondsToTicks((OSTime) TCP_DEF_RTT);

    // PPP parameters
    interface->pppMaxConfigure = PPP_MAX_CONFIGURE;
    interface->pppMaxTerminate = PPP_MAX_TERMINATE;
    interface->pppMaxFailure = PPP_MAX_FAILURE;
    interface->pppRestartTimer = PPP_RESTART_TIMER;

    // ARP
    ARPInit();

    // IP
    IPInitRoute(NULL, NULL, NULL);
    memcpy(&interface->broadcast, IPLimited, IP_ALEN);

    interface->cancel = Cancel;
    interface->alloc  = Alloc;
    interface->free   = Free;

    interface->inFilter = interface->outFilter = NullFilter;

    // Address configuration request queue
    IFInitQueue(&interface->queue);

    switch (type)
    {
      case IF_TYPE_AUTO:
      case IF_TYPE_100FULL:
      case IF_TYPE_100HALF:
      case IF_TYPE_10FULL:
      case IF_TYPE_10HALF:
        ETHInitInterface(interface, type);
        break;
      case IF_TYPE_MODEM:
        MDMInitInterface(interface, type);
        break;
      default:
        break;
    }

    IGMPInit(interface);

    OSRegisterResetFunction(&ResetFunctionInfo);

    return TRUE;
}

// IFMute() prevents BBA generating receive interrupts.
BOOL IFMute(BOOL mute)
{
    IPInterface* interface = &__IFDefault;
    BOOL         prev;

    prev = (interface->flag & IP_IF_FLAG_MUTE) ? TRUE : FALSE;
    if ((mute && !prev) || (!mute && prev))
    {
        if (mute)
        {
            interface->flag |= IP_IF_FLAG_MUTE;
        }
        else
        {
            interface->flag &= ~IP_IF_FLAG_MUTE;
        }
        interface->mute(interface, mute);
    }
    return prev;
}

static BOOL OnReset(BOOL final)
{
    IPInterface* interface = &__IFDefault;

    interface->flag |= IP_IF_FLAG_RESET;
    if (final)
    {
        UDPOnReset(final);
        TCPOnReset(final);
        IGMPOnReset(final); // For check only. Call after UDPOnReset(TRUE).
#ifdef IP_INET6
        MLDOnReset(final);
#endif
        interface->onReset(interface, final);
        return TRUE;
    }
#ifdef IP_INET6
    else if (UDPOnReset(final) && TCPOnReset(final) && MLDOnReset(final))
#else
    else if (UDPOnReset(final) && TCPOnReset(final))
#endif
    {
        // Linger
        if (interface->sending || !IFIsEmptyQueue(&interface->sendQueue))
        {
            return FALSE;
        }
        IFMute(TRUE);
        interface->onReset(interface, final);
        return TRUE;
    }
    return FALSE;
}

// This is the dummy of MDMInitInterface() in IPModem.c.
__declspec(weak) BOOL MDMInitInterface(IPInterface* interface, s32 type)
{
#pragma unused( interface, type )

    return FALSE;
}

s32 IFGetSockOpt(IPInterface* interface, int level, int optname,
                 void* optval, int* optlen)
{
    BOOL enabled;
    s32  rc = IP_ERR_INV_OPTION;

    if (!interface)
    {
        interface = &__IFDefault;
    }
    enabled = OSDisableInterrupts();
    switch (level)
    {
      case SO_SOL_CONFIG:
        switch (optname)
        {
          case SO_CONFIG_FILTER_INPUT:
            if (sizeof(BOOL (*)(IPInterface*, void*, s32)) <= *optlen)
            {
                *(BOOL (*)(IPInterface*, void*, s32)) optval = interface->inFilter;
                *optlen = sizeof(BOOL (*)(IPInterface*, void*, s32));
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_FILTER_OUTPUT:
            if (sizeof(BOOL (*)(IPInterface*, void*, s32)) <= *optlen)
            {
                *(BOOL (*)(IPInterface*, void*, s32)) optval = interface->outFilter;
                *optlen = sizeof(BOOL (*)(IPInterface*, void*, s32));
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_ERROR:
            if (sizeof(s32) <= *optlen)
            {
                *(s32*) optval = interface->err;
                *optlen = sizeof(s32);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_MAC_ADDRESS:
            if (ETH_ALEN <= *optlen)
            {
                memcpy(optval, interface->mac, ETH_ALEN);
                *optlen = ETH_ALEN;
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_LINK_STATE:
            if (sizeof(BOOL) <= *optlen)
            {
                *(BOOL*) optval = interface->up;
                *optlen = sizeof(BOOL);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_INTERFACE_STATISTICS:
            if (sizeof(IFStat) <= *optlen)
            {
                *(IFStat*) optval = interface->stat;
                *optlen = sizeof(IFStat);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_PPP_MAX_CONFIGURE:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = interface->pppMaxConfigure;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_PPP_MAX_TERMINATE:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = interface->pppMaxTerminate;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_PPP_MAX_FAILURE:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = interface->pppMaxFailure;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_PPP_RESTART_TIMER:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = interface->pppRestartTimer;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_PPP_MESSAGE:
            if (0 <= *optlen)
            {
                *optlen = MIN(256, *optlen);
                strncpy(optval, __PPPAuth.message, (size_t) *optlen);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_ARP_NUMBER:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = NARP;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_ARP_TABLE:
            rc = ARPReport(interface, optval, optlen);
            break;
          case SO_CONFIG_IP_STATISTICS:
            if (sizeof(IPStat) <= *optlen)
            {
                *(IPStat*) optval = interface->ipStat;
                *optlen = sizeof(IPStat);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IP_ADDR_NUMBER:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = 2;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IP_ADDR_TABLE:
            rc = IPReportAddrTable(interface, optval, optlen);
            break;
          case SO_CONFIG_IP_MTU:
            if (sizeof(s32) <= *optlen)
            {
                *(s32*) optval = interface->mtu;
                *optlen = sizeof(s32);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IP_ROUTING_NUMBER:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = IP_ROUTING_NUMBER;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IP_ROUTING_TABLE:
            rc = IPReportRoutingTable(interface, optval, optlen);
            break;
          case SO_CONFIG_IP_BOOT_ADDRESS:
            if (sizeof(IP_ALEN) <= *optlen)
            {
                memcpy(optval, interface->boot, IP_ALEN);
                *optlen = sizeof(IP_ALEN);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_ICMP_STATISTICS:
            if (sizeof(ICMPStat) <= *optlen)
            {
                *(ICMPStat*) optval = interface->icmpStat;
                *optlen = sizeof(ICMPStat);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
#ifdef IP_INET6
          case SO_CONFIG_IPV6_STATISTICS:
            if (sizeof(IPv6Stat) <= *optlen)
            {
                *(IPv6Stat*) optval = interface->ipv6Stat;
                *optlen = sizeof(IPv6Stat);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IPV6_MTU:
            if (sizeof(s32) <= *optlen)
            {
                *(s32*) optval = interface->linkMTU;
                *optlen = sizeof(s32);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IPV6_DUP_ADDR_DETECT_TRANSMITS:
            if (sizeof(u32) <= *optlen)
            {
                *(u32*) optval = interface->dupAddrDetectTransmits;
                *optlen = sizeof(s32);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IPV6_PREFIX_NUMBER:
          case SO_CONFIG_IPV6_ADDR_PREFIX_NUMBER:
          case SO_CONFIG_IPV6_ADDR_NUMBER:
          case SO_CONFIG_IPV6_ROUTE_NUMBER:
          case SO_CONFIG_IPV6_NET_TO_MEDIA_NUMBER:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = MAX_NEIGHBORS;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IPV6_PREFIX_TABLE:
          case SO_CONFIG_IPV6_ADDR_PREFIX_TABLE:
          case SO_CONFIG_IPV6_ADDR_TABLE:
          case SO_CONFIG_IPV6_ROUTE_TABLE:
          case SO_CONFIG_IPV6_NET_TO_MEDIA_TABLE:
            rc = IP6ReportEntryTable(interface, level, optname, optval, optlen);
            break;
          case SO_CONFIG_ICMPV6_STATISTICS:
            if (sizeof(ICMPv6Stat) <= *optlen)
            {
                *(ICMPv6Stat*) optval = interface->icmpv6Stat;
                *optlen = sizeof(ICMPv6Stat);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
#endif // IP_INET6
          case SO_CONFIG_UDP_STATISTICS:
            if (sizeof(UDPStat) <= *optlen)
            {
                *(UDPStat*) optval = interface->udpStat;
                *optlen = sizeof(UDPStat);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_UDP_NUMBER:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = UDPNumber;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_UDP_TABLE:
            rc = UDPReport(interface, optval, optlen);
            break;
#ifdef IP_INET6
          case SO_CONFIG_UDP6_NUMBER:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = UDP6Number;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_UDP6_TABLE:
            rc = UDP6Report(interface, optval, optlen);
            break;
#endif // IP_INET6
          case SO_CONFIG_TCP_STATISTICS:
            if (sizeof(TCPStat) <= *optlen)
            {
                *(TCPStat*) optval = interface->tcpStat;
                *optlen = sizeof(TCPStat);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_TCP_NUMBER:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = TCPNumber + TCPReportTimeWaitNumber(interface);
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_TCP_TABLE:
            rc = TCPReport(interface, optval, optlen);
            break;
#ifdef IP_INET6
          case SO_CONFIG_TCP6_NUMBER:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = TCP6Number + TCP6ReportTimeWaitNumber(interface);
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_TCP6_TABLE:
            rc = TCP6Report(interface, optval, optlen);
            break;
#endif // IP_INET6
          case SO_CONFIG_TCP_MSL:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = (int) OSTicksToSeconds(interface->closeWaitInterval / 2);
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_TCP_RTO_MIN:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = (int) OSTicksToMilliseconds(interface->minRtt);
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_TCP_RTO_MAX:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = (int) OSTicksToSeconds(interface->maxRtt);
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_TCP_RTO_DEFAULT:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = (int) OSTicksToSeconds(interface->defaultRtt);
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IGMP_MODE:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = IGMPVersion(interface);
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_DNS_DOMAIN_NAME:
            if (0 <= *optlen)
            {
                *optlen = MIN(SO_MAXDNAME, *optlen);
                strncpy(optval, __SOResolver.suffix, (size_t) *optlen);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_DNS_SERVER_NUMBER:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = 2;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_DNS_SERVER_TABLE:
            rc = SOReportResolverTable(interface, optval, optlen);
            break;
        }
        break;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 IFSetSockOpt(IPInterface* interface, int level, int optname,
                 const void* optval, int optlen)
{
    BOOL enabled;
    s32  rc = IP_ERR_INV_OPTION;

    if (!interface)
    {
        interface = &__IFDefault;
    }
    enabled = OSDisableInterrupts();
    switch (level)
    {
      case SO_SOL_CONFIG:
        switch (optname)
        {
          case SO_CONFIG_FILTER_INPUT:
            if (sizeof(BOOL (*)(IPInterface*, void*, s32)) <= optlen)
            {
                interface->inFilter = (BOOL (*)(IPInterface*, void*, s32)) optval;
                if (!interface->inFilter)
                {
                    interface->inFilter = NullFilter;
                }
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_FILTER_OUTPUT:
            if (sizeof(BOOL (*)(IPInterface*, void*, s32)) <= optlen)
            {
                interface->outFilter = (BOOL (*)(IPInterface*, void*, s32)) optval;
                if (!interface->outFilter)
                {
                    interface->outFilter = NullFilter;
                }
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_ERROR:
            if (sizeof(s32) <= optlen)
            {
                interface->err = *(const s32*) optval;
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_INTERFACE_STATISTICS:
            if (sizeof(IFStat) <= optlen)
            {
                interface->stat = *(const IFStat*) optval;
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_PPP_MAX_CONFIGURE:
            if (sizeof(int) <= optlen)
            {
                interface->pppMaxConfigure = MAX(*(const int*) optval, 1);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_PPP_MAX_TERMINATE:
            if (sizeof(int) <= optlen)
            {
                interface->pppMaxTerminate = MAX(*(const int*) optval, 1);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_PPP_MAX_FAILURE:
            if (sizeof(int) <= optlen)
            {
                interface->pppMaxFailure = MAX(*(const int*) optval, 1);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_PPP_RESTART_TIMER:
            if (sizeof(int) <= optlen)
            {
                interface->pppRestartTimer = MAX(*(const int*) optval, 1);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_ARP_REFRESH:
            rc = ARPRefresh();
            break;
          case SO_CONFIG_ARP_ADD:
            if (sizeof(ARPEntry) <= optlen)
            {
                const ARPEntry* ent = optval;
                rc = ARPAdd(interface, ent->prAddr, ent->hwAddr);
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_ARP_REMOVE:
            if (sizeof(ARPEntry) <= optlen)
            {
                const ARPEntry* ent = optval;
                rc = ARPRemove(interface, ent->prAddr, ent->hwAddr);
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IP_STATISTICS:
            if (sizeof(IPStat) <= optlen)
            {
                interface->ipStat = *(const IPStat*) optval;
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IP_MTU:
            if (sizeof(s32) <= optlen)
            {
                interface->mtu = MAX(*(s32*) optval, 68);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IP_ADD_ROUTE:
            if (sizeof(IPRouteEntry) <= optlen)
            {
                const IPRouteEntry* ent = optval;
                rc = IPAddRoute(ent->dst, ent->netmask, ent->gateway) ?
                     IP_ERR_NONE : IP_ERR_INS_RESOURCES;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IP_REMOVE_ROUTE:
            if (sizeof(IPRouteEntry) <= optlen)
            {
                const IPRouteEntry* ent = optval;
                rc = IPRemoveRoute(ent->dst, ent->netmask, ent->gateway) ?
                                   IP_ERR_NONE : IP_ERR_INS_RESOURCES;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IP_BOOT_ADDRESS:
            if (sizeof(IP_ALEN) <= optlen)
            {
                memcpy(interface->boot, optval, IP_ALEN);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_ICMP_STATISTICS:
            if (sizeof(ICMPStat) <= optlen)
            {
                interface->icmpStat = *(const ICMPStat*) optval;
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
#ifdef IP_INET6
          case SO_CONFIG_IPV6_STATISTICS:
            if (sizeof(IPv6Stat) <= optlen)
            {
                interface->ipv6Stat = *(const IPv6Stat*) optval;
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IPV6_MTU:
            if (sizeof(s32) <= optlen)
            {
                interface->linkMTU = MAX(*(s32*) optval, IP6_MIN_MTU);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IPV6_ADD_ROUTE:
            if (sizeof(IP6RouteEntry) <= optlen)
            {
                const IP6RouteEntry* ent = optval;

                rc = IP6AddRoute(&ent->prefix, ent->prefixLen, &ent->nextHop) ?
                                 IP_ERR_NONE : IP_ERR_INS_RESOURCES;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IPV6_REMOVE_ROUTE:
            if (sizeof(IP6RouteEntry) <= optlen)
            {
                const IP6RouteEntry* ent = optval;

                rc = IP6RemoveRoute(&ent->prefix, ent->prefixLen, &ent->nextHop) ?
                                    IP_ERR_NONE : IP_ERR_INS_RESOURCES;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IPV6_ADD_ADDRESS:
            if (sizeof(SOIn6Addr) <= optlen)
            {
                const SOIn6Addr* ent = optval;

                rc = IP6SetAddr(interface, ent);
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IPV6_REMOVE_ADDRESS:
            if (sizeof(SOIn6Addr) <= optlen)
            {
                const SOIn6Addr* ent = optval;

                rc = IP6RemoveAddr(interface, ent);
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IPV6_DUP_ADDR_DETECT_TRANSMITS:
            if (sizeof(u32) <= optlen)
            {
                interface->dupAddrDetectTransmits = MAX(*(u32*) optval, 0);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_ICMPV6_STATISTICS:
            if (sizeof(ICMPv6Stat) <= optlen)
            {
                interface->icmpv6Stat = *(const ICMPv6Stat*) optval;
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
#endif // IP_INET6
          case SO_CONFIG_UDP_STATISTICS:
            if (sizeof(UDPStat) <= optlen)
            {
                interface->udpStat = *(const UDPStat*) optval;
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_TCP_STATISTICS:
            if (sizeof(TCPStat) <= optlen)
            {
                interface->tcpStat = *(const TCPStat*) optval;
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_TCP_MSL:
            if (sizeof(int) <= optlen)
            {
                interface->closeWaitInterval = MAX(*(int*) optval, 1);
                interface->closeWaitInterval = OSSecondsToTicks(2 * interface->closeWaitInterval);
                ASSERT(*(int*) optval == OSTicksToSeconds(interface->closeWaitInterval) / 2);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_TCP_RTO_MIN:
            if (sizeof(int) <= optlen)
            {
                interface->minRtt = OSMillisecondsToTicks(MAX(*(int*) optval, 1));
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_TCP_RTO_MAX:
            if (sizeof(int) <= optlen)
            {
                interface->maxRtt = OSSecondsToTicks(MAX(*(int*) optval, 1));
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_TCP_RTO_DEFAULT:
            if (sizeof(int) <= optlen)
            {
                interface->defaultRtt = OSSecondsToTicks(MAX(*(int*) optval, 1));
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_IGMP_MODE:
            if (sizeof(int) <= optlen)
            {
                int mode = *(int*) optval;
                if (1 < mode)
                {
                    IGMPLeaveV1Mode(interface);
                }
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_DNS_DOMAIN_NAME:
            if (0 == optlen)
            {
                memset(__SOResolver.suffix, 0, SO_MAXDNAME);
                rc = IP_ERR_NONE;
            }
            if (0 < optlen && optlen < SO_MAXDNAME)
            {
                strncpy(__SOResolver.suffix, optval, SO_MAXDNAME);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_CONFIG_DNS_SERVER_TABLE:
            if (0 <= optlen && optlen % IP_ALEN == 0)
            {
                SOInAddr dns[2] = { 0, 0 };

                memcpy(dns, optval, MIN(2u * IP_ALEN, optlen));
                rc = SOSetResolver(&dns[0], &dns[1]);
                if (rc == SO_ENETRESET)
                {
                    rc = IP_ERR_INVALID;
                }
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
        }
        break;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}
