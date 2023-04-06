d1 2894
a2894 2840
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPTcp.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip/src/IPTcp.c $
    
    85    2/28/06 14:22 Shiki
    Fixed DoListen() for IPv4 build.

    84    2/27/06 15:09 Shiki
    Modified to count TCPNumber and TCP6Number.

    83    2/22/06 10:20 Shiki
    Aligned TCP_STATE_* in MIB-II tcpConnState order.

    82    2/21/06 17:48 Shiki
    Fixed TCP4In() and TCP6In() to abort TCP after TIME-WAIT state is
    reset.

    81    2/15/06 11:23 Shiki
    Modified to collect more tcpStat.

    80    2/14/06 18:47 Shiki
    Revised to collect interface statistics.

    79    2/14/06 9:57 Shiki
    Modified TCP4In() and TCP6In() to use interface->closeWaitInterval.

    78    2/10/06 17:47 Shiki
    Modified TCPNotify() and TCP6Notify() to trigger a slow start.

    77    2/10/06 13:57 Shiki
    Revised TCPNotify().

    76    2/09/06 17:31 Shiki
    Revised ICMPv6 error handling code.

    75    2/09/06 14:34 Shiki
    Fixed TIME-WAIT state management when time wait buffer is no available.

    74    2/08/06 10:52 Shiki
    Added support for SO_TCP_STDURG.

    73    2/02/06 15:33 Shiki
    Modified delayed ACK implementation.

    72    2/01/06 16:24 Shiki
    Added full support of IPv6 PMTU discovery.

    71    1/23/06 13:30 Shiki
    Fixed TCP6In().

    70    1/23/06 13:15 Shiki
    Fixed TCP6In().

    69    1/23/06 10:21 Shiki
    Fixed MSS management of IPv6.

    68    1/19/06 18:25 Shiki
    Renamed IP6GetNeighbor() to IP6GetNextNeighbor().

    67    1/11/06 14:42 Shiki
    Fixed IPv6 to use interface->linkMTU instead of interface->mtu.

    66    12/28/05 14:06 Shiki
    Fixed DoAck().

    65    12/22/05 18:53 Shiki
    Fixed TIME-WAIT management code bug that TCPInfo remains in TIME-WAIT
    even after TCPTimeWaitInfo is expired.

    64    12/22/05 18:31 Shiki
    Fixed TCPIn().

    63    12/22/05 14:31 Shiki
    Added IPAnvl.

    62    12/22/05 12:00 Shiki
    Modified TIME-WAIT management to process SYN following RFC 1122.

    61    12/22/05 11:02 Shiki
    Modified TCPTestTimeWait() interface.

    60    12/22/05 9:31 Shiki
    Fixed TIME-WAIT TCB abort/RST operations.

    59    12/19/05 14:22 Shiki
    Fixed DoSynSent() to support simultaneous open.

    58    12/13/05 19:57 Shiki
    Revised to support default TTL for RFC 3927 (1 for link-local, IP_TTL
    for others).

    57    12/09/05 15:18 Shiki
    Implemented the limited transmit algorithm (RFC 3042).
    Fixed TCPIsn().

    56    12/08/05 21:46 Shiki
    Implemented RFC 3517.

    55    12/08/05 20:25 Shiki
    Revised to test fast recovery mode by counting dupAcks.

    54    12/08/05 17:56 Shiki
    Fixed the fast recovery procedure.

    53    12/08/05 10:29 Shiki
    Revised TCPDumpHeader() to show times.

    52    12/07/05 22:00 Shiki
    Implemented RFC 3782 (The NewReno Modification to TCP's Fast Recovery
    Algorithm).

    51    11/30/05 11:41 Shiki
    Revised to maintain cWin in units of bytes.

    50    11/29/05 17:43 Shiki
    Fixed DoOption() not to process the TCP_OPT_MSS option for non-SYN
    segment.
    Temporarily fixed TCPOpenWindow() to open cWin precisely.

    49    11/25/05 14:18 Shiki
    Temporarily fixed TCP4In() and TCP6In()assuming SOShutdown(s,
    SO_SHUT_RDWR) has been called if TCP state is TCP_STATE_CLOSED.

    48    11/24/05 11:16 Shiki
    Fixed to set the MSS value to the default minimum if no MSS option is
    specified from the remote node.

    47    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    52    04/10/21 16:59 Ueno_kyu
    Enclosed IPv6 specific codes in #ifdef IP_INET6... #endif blocks.

    51    6/29/04 9:34 Shiki
    Revised using IP_TTL.

    50    6/14/04 11:31 Shiki
    Fixed DoListen().

    49    6/09/04 17:01 Shiki
    Fixed for IPv4 build.

    48    6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    46    3/03/04 14:28 Shiki
    Modified to use a TCP initial cwnd of 2 segments as allowed in RFC
    2581.

    45    2/25/04 14:49 Shiki
    Added support for delayed ACK.

    44    10/29/03 21:59 Shiki
    Revised using IFInitDatagram().

    43    10/20/03 15:01 Shiki
    Added support for SO_SO_SNDLOWAT and SO_SO_RCVLOWAT.

    42    10/17/03 14:50 Shiki
    Modified TCPSendIn() to check sendLowat.

    41    8/28/03 20:37 Shiki
    Fixed comment.

    40    8/28/03 17:57 Shiki
    Fixed FIN handling bug in DoData(). (Enbugged by version 38)

    39    8/25/03 9:39 Shiki
    Fixed TCPDeleteSackHoles().

    38    8/21/03 20:58 Shiki
    Added support for SACK/FACK.

    37    8/04/03 10:39 Shiki
    Fixed DoData() to wake up polling thread upon data receive.

    36    5/15/03 21:38 Shiki
    Fixed DoListen() to initialize accepted->interface properly so that
    accepted can send packet with TCPRespond() immediately.

    35    5/15/03 15:54 Shiki
    Modified to clear the IF_DATAGRAM_FLAG_DROP bit in IFDatagram.flag
    before sending a Ethernet packet.

    34    5/13/03 12:51 Shiki
    Fixed FIN handling code in DoData() to pass listen_local test.

    33    5/07/03 11:17 Shiki
    Fixed not to update interface statistics.

    32    5/03/03 12:59 Shiki
    Implemented IPInterfaceStat{} support functions.

    31    3/27/03 17:38 Shiki
    Added support for multicast.

    30    3/26/03 15:03 Shiki
    Implemented TCP support for SOPoll().

    29    11/11/02 21:56 Shiki
    Added support for SO_MSG_DONTWAIT.

    28    11/08/02 11:33 Shiki
    Fixed TCPIn() and DoData() to call valid user callback before calling
    TCPStartTimeWait() since TCPStartTimeWait() calls TCPAbort().

    27    10/18/02 12:01 Shiki
    Fixed not to send RST that indicates data lost for FIN.

    26    9/18/02 13:26 Shiki
    Fixed TCPIn() to update sendUna properly in SYN_RECEIVED state.

    25    8/05/02 11:11 Shiki
    Implemented TCPOpenWindow(). [Moved from IPTcpTimer.c]
    Revised DoData() to support out-of-order segment queuing.

    24    7/19/02 16:12 Shiki
    Added support for non-blocking I/O.

    23    7/18/02 10:18 Shiki
    Added supoprt for TCPStat.

    22    7/10/02 17:11 Shiki
    Fixed send window update code so that it does not lose the window
    update segment. Revised TCPDumpHeader().

    21    6/20/02 14:06 Shiki
    Fixed DoSynSent() and DoListen() to initialize 'recvUp' pointer
    properly after setting 'recvNext' pointer.

    20    4/26/02 16:47 Shiki
    Added support for check sum error counters.

    19    4/25/02 21:37 Shiki
    Revised TCPListen() interface with TCPListenCallback.

    18    4/24/02 11:19 Shiki
    Fixed comment.

    17    4/23/02 16:05 Shiki
    Modified DoListen() to make accepted TCP inherit the listening socket
    properties.

    16    4/23/02 14:47 Shiki
    Fixed TCPIn() to validate RST segment correctly. Added more LAND attack
    protection.

    15    4/15/02 12:54 Shiki
    Fixed a bug in DoReset().
    Fixed TCPIn() to check TCP header more strictly.
    Implemented more RFC 793 compliance codes.
    Fixed TCPRecvOut() to handle out-of-band byte properly.

    14    4/12/02 13:10 Shiki
    Implemented initial sequence number randomizing for TCPIsn().
    Fixed TCPRespond() to release fifo memory block upon IPOut() failure.

    13    4/09/02 18:47 Shiki
    Modified DoData() so it can send back RSTs to indicate data lost while
    closing connections.

    12    4/08/02 16:46 Shiki
    Fixed TCP flag bug against the bogus flag probe.

    11    4/05/02 14:09 Shiki
    Refined using 'const'.

    10    4/02/02 13:23 Shiki
    Added support for half-close and urgent mode.

    9     3/27/02 16:48 Shiki
    Implemented TCPSourceQuench (). Revised TCPNotify().

    8     3/19/02 21:15 Shiki
    Fixed TCPCheckSum().

    7     3/18/02 14:32 Shiki
    Fixed the ACK response code following the RFC ACK bit rules.

    6     3/14/02 16:07 Shiki
    Renamed TCPInfo.template to TCPInfo.header.

    5     3/13/02 18:30 Shiki
    Revised TCPSend() so it can directly transfer user data from the user
    space to the link layer.

    4     3/12/02 12:48 Shiki
    Fixed persist state management code bugs.

    3     3/12/02 9:17 Shiki
    Fixed a TCPIn() crash bug that happens when a TCP segment to a
    non-exist connection is received.

    2     3/11/02 20:21 Shiki
    Fixed to initialize datagram->queue before IPOut().

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

// #define VERBOSE

#include <dolphin/os.h>
#include <dolphin/md5.h>
#include <dolphin/socket.h>
#ifndef WIN32
#include <private/OSLoMem.h>
#endif
#include "IPPrivate.h"
#ifdef IP_INET6
#include "IP6Private.h"
#endif // IP_INET6

#include <string.h>

static void    TCPIn    ( IPInterface* interface, TCPObj* info, void* ip, TCPHeader* tcp, s32 len, u32 linkFlag );
static TCPObj* DoListen ( IPInterface* interface, TCPObj* info, void* ip, TCPHeader* tcp, s32 len );
static TCPObj* DoSynSent( IPInterface* interface, TCPObj* info, void* ip, TCPHeader* tcp, s32 len );
static void    DoData   ( IPInterface* interface, TCPObj* info, void* ip, TCPHeader* tcp, s32 len, u16 flag );

void TCPDeleteSackHoles(TCPObj* info, TCPHeader* tcp);
void TCPUpdateScoreboard(TCPObj* info, TCPHeader* tcp, u8* opt, int optlen);

char* TCPStateNames[] =
{
    "Deleted",
    "Closed",
    "Listen",
    "SynSent",
    "SynReceived",
    "Established",
    "FinWait1",
    "FinWait2",
    "CloseWait",
    "LastAck",
    "Closing",
    "Time_Wait"
};

typedef struct TCPPseudoHeader
{
    u8  src[IP_ALEN];
    u8  dst[IP_ALEN];
    u8  zero;
    u8  proto;
    u16 len;
} TCPPseudoHeader;

// Generate initial sequence number [RFC 1948]
// [RFC 1948 Bellovin] ISN = M + F(localhost,localport,remotehost,remoteport)
// Initial Sequence Number Randomizing
s32 TCPIsn(IPInfo* info)
{
#if defined(VERBOSE) || defined(WIN32)
    #pragma unused(info)
    return 0;
#else
    s32            m;
    MD5Context     context;
    IPSocket*      sockAddr;
#ifdef IP_INET6
    SOSockAddrIn6* sockAddr6;
#endif  // IP_INET6
    u8             digest[16];

    MD5Init(&context);
    MD5Update(&context, (u8*) (OS_BASE_CACHED + OS_SYSTEMTIME_BASE), sizeof(OSTime));
    if (info)
    {
        switch (info->family)
        {
          case SO_PF_INET:
            sockAddr = IPGetLocalSockAddr(info);
            MD5Update(&context, sockAddr->addr, 4);
            MD5Update(&context, (u8*) &sockAddr->port, 2);
            sockAddr = IPGetRemoteSockAddr(info);
            MD5Update(&context, sockAddr->addr, 4);
            MD5Update(&context, (u8*) &sockAddr->port, 2);
            break;
#ifdef IP_INET6
          case SO_PF_INET6:
            sockAddr6 = IPGetLocalSockAddr(info);
            MD5Update(&context, (u8*) &sockAddr6->addr, 16);
            MD5Update(&context, (u8*) &sockAddr6->port, 2);
            sockAddr6 = IPGetRemoteSockAddr(info);
            MD5Update(&context, (u8*) &sockAddr6->addr, 16);
            MD5Update(&context, (u8*) &sockAddr6->port, 2);
            break;
#endif  // IP_INET6
        }
    }
    MD5Final(digest, &context);
    m = *(s32*) &digest[0];
    m ^= *(s32*) &digest[4];
    m ^= *(s32*) &digest[8];
    m ^= *(s32*) &digest[12];
    m += (s32) (OSGetTime() / (OS_TIMER_CLOCK / TCP_IIS_CLOCK));
    return m;
#endif
}

void TCPDumpHeader(const IPHeader* ip, const TCPHeader* tcp)
{
    int    optlen;
    u8*    opt;
    int    len;
    OSTime t;

    t = __OSGetSystemTime();
    OSReport("%4llu.%03llu  ",
             OSTicksToSeconds(t) % 10000,
             OSTicksToMilliseconds(t) % 1000);

    OSReport("%d.%d.%d.%d:%d > %d.%d.%d.%d:%d  TCP   ",
             ip->src[0], ip->src[1], ip->src[2], ip->src[3], tcp->src,
             ip->dst[0], ip->dst[1], ip->dst[2], ip->dst[3], tcp->dst);

    if (tcp->flag & TCP_FLAG_SYN)
        OSReport("S");
    if (tcp->flag & TCP_FLAG_FIN)
        OSReport("F");
    if (tcp->flag & TCP_FLAG_RST)
        OSReport("R");
    if (tcp->flag & TCP_FLAG_PSH)
        OSReport("P");
    if ((tcp->flag & (TCP_FLAG_SYN | TCP_FLAG_FIN | TCP_FLAG_RST | TCP_FLAG_PSH)) == 0)
        OSReport(".");

    len = ip->len - IP_HLEN(ip) - TCP_HLEN(tcp);
    OSReport(" %u:%u(%d) ", tcp->seq, tcp->seq + len, len);

    if (tcp->flag & TCP_FLAG_ACK)
        OSReport("ack %u ", tcp->ack);

    OSReport("win %u ", tcp->win);

    if (tcp->flag & TCP_FLAG_URG)
        OSReport("urg %u ", tcp->urg);

    ASSERT(0 <= ip->len - IP_HLEN(ip) - TCP_HLEN(tcp));

    // option (if any)
    optlen = TCP_HLEN(tcp) - TCP_MIN_HLEN;
    opt = (u8*) tcp + TCP_MIN_HLEN;
    while (0 < optlen && *opt != TCP_OPT_EOL)
    {
        if (*opt == TCP_OPT_NOP)
        {
            len = 1;
        }
        else
        {
            len = opt[1];
            if (len < 2)
            {
                break;  // quit loop
            }
        }

        switch (*opt)
        {
          case TCP_OPT_NOP:
            OSReport("<nop> ");
            break;
          case TCP_OPT_EOL:
            OSReport("<eol> ");
            break;
          case TCP_OPT_MSS:
            if (len == 4)
            {
                OSReport("<mss: %d> ", *(u16*) &opt[2]);
            }
            break;
          case TCP_OPT_SACKP:
            if (len == 2)
            {
                OSReport("<sack-permitted> ", *(u16*) &opt[2]);
                break;
            }
            break;
          case TCP_OPT_SACK:
            if (2 < len && (len - 2) % (2 * sizeof(s32)) == 0)
            {
                s32* edge = (s32*) (opt + 2);
                int  edgelen = len - 2;

                OSReport("<sack:");
                while (0 < edgelen)
                {
                    OSReport(" %u", SONtoHl(edge[0]));
                    OSReport("-%u", SONtoHl(edge[1]));
                    edge += 2;
                    edgelen -= 2 * sizeof(s32);
                }
                OSReport("> ");
            }
            break;
          default:
            OSReport("<opt: [%d]> ", opt[0]);
            break;
        }

        opt    += len;
        optlen -= len;
    }

    OSReport("\n");
}

// Process TCP options called by DoListen(), DoSynSent() and TCPIn().
static BOOL DoOption(TCPObj* info, IPHeader* ip, TCPHeader* tcp)
{
    #pragma unused(ip)
    int optlen;
    u8* opt;
    int len;
    u16 mss;

    // Set mss to IP minimal (default)
    switch (info->pair->family)
    {
      case SO_PF_INET:
        mss = 576 - IP_MIN_HLEN - TCP_MIN_HLEN;
        break;
      case SO_PF_INET6:
        mss = IP6_MIN_MTU - sizeof(IP6Hdr) - TCP_MIN_HLEN;
        break;
    }

    // option (if any)
    optlen = TCP_HLEN(tcp) - TCP_MIN_HLEN;
    opt = (u8*) tcp + TCP_MIN_HLEN;
    while (0 < optlen && *opt != TCP_OPT_EOL)
    {
        if (*opt == TCP_OPT_NOP)
        {
            len = 1;
        }
        else
        {
            len = opt[1];
            if (len < 2)
            {
                break;  // quit loop
            }
        }

        switch (*opt)
        {
          case TCP_OPT_MSS:
            // Initialize congestion window to one segment. It will be increased
            // by on segment each time an ACK is received.
            if (len != 4 || !(tcp->flag & TCP_FLAG_SYN))
            {
                break;
            }
            mss = *(u16*) &opt[2];
            break;

#ifdef TCP_SACK

          case TCP_OPT_SACKP:
            if (len != 2 || !(tcp->flag & TCP_FLAG_SYN))
            {
                break;
            }
            info->flag |= TCP_SO_SACK;
            break;

          case TCP_OPT_SACK:
            TCPUpdateScoreboard(info, tcp, opt, len);
            break;

#endif // TCP_SACK

          default:
            // Do not process unknowen options.
            break;
        }

        opt    += len;
        optlen -= len;
    }

    if (tcp->flag & TCP_FLAG_SYN)
    {
        // Update info->mss to the default minimum value (536), if
        // TCP_OPT_MSS option is not specified.
        info->mss = info->mssBase = MIN(mss, info->mss);
        info->cWin = TCP_IW(info);
        info->ssThresh = TCP_DEF_SSTHRESH;
    }

    return TRUE;
}

s32 TCPGetSegmentLength(TCPHeader* tcp, s32 plen)
{
    ASSERT(TCP_HLEN(tcp) <= plen);
    plen -= TCP_HLEN(tcp);
    // SYN is considered to occur before the first actual data
    if (tcp->flag & TCP_FLAG_SYN)
    {
        ++plen;
    }
    // FIN is considered to occur after the last actual data
    if (tcp->flag & TCP_FLAG_FIN)
    {
        ++plen;
    }
    return plen;
}

static s32 TCPCalcOptLen(TCPObj* info, u16 flag)
{
#ifndef _DEBUG
    #pragma unused(flag)
#endif  // _DEBUG
    s32 optlen = 0;

#ifdef TCP_SACK
    // Calculate TCP option length for SACK
    if (info && (info->flag & TCP_SO_SACK) && info->asb[0].ptr != NULL)
    {
        IFBlock* block;

        ASSERT(!(flag & TCP_FLAG_SYN));
        optlen += 2;
        for (block = &info->asb[TCP_ASB - 1]; info->asb <= block; --block)
        {
            if (block->ptr == NULL)
            {
                continue;
            }
            break;
        }
        optlen += (block + 1 - info->asb) * (2 * sizeof(s32));
        optlen = (optlen + 3) & ~3;
        ASSERT(optlen % 4 == 0);
        ASSERT(TCP_MIN_HLEN + optlen <= TCP_MAX_HLEN);
    }
#endif  // TCP_SACK

    return optlen;
}

void TCP4Respond(IPInterface* interface, TCPObj* info,
                 const u8* dstAddr, u16 dst,
                 const u8* srcAddr, u16 src,
                 s32 seq, s32 ack, u16 flag, u16 win)
{
    IPHeader*   ip;
    TCPHeader*  tcp;
    IFDatagram* datagram;
    s32         len;
    s32         optlen;

    optlen = TCPCalcOptLen(info, flag);

    len = (s32) sizeof(IFDatagram) + IP_MIN_HLEN + TCP_MIN_HLEN + optlen;
    datagram = interface->alloc(interface, len);
    if (datagram == NULL)
    {
        ++interface->ipStat.outDiscards;
        return;
        // NOT REACHED HERE
    }

    IFInitDatagram(datagram, ETH_IP, 1);

    ip = (IPHeader*) ((u8*) datagram + sizeof(IFDatagram));
    memmove(ip->dst, dstAddr, IP_ALEN);
    memmove(ip->src, srcAddr, IP_ALEN);
    ip->verlen = IP_VERHLEN;
    ip->tos    = 0;    // default
    ip->len    = (u16) (IP_HLEN(ip) + TCP_MIN_HLEN + optlen);
    if (info)
    {
        IPHeader* header = (IPHeader*) &info->header[0];
        ip->ttl = header->ttl;
    }
    else
    {
        ip->ttl = (u8) (IPIsLinkLocalAddr(interface, srcAddr) ? 1 : IP_TTL);
    }

    ip->proto  = IP_PROTO_TCP;
    ip->frag   = 0;

    tcp = (TCPHeader*) ((u8*) ip + IP_HLEN(ip));
    tcp->flag = (u16) (flag & TCP_FLAG_793);
    TCPMakeOption(tcp, info, flag);
    tcp->src = src;
    tcp->dst = dst;
    tcp->seq = seq;
    tcp->ack = ack;
    tcp->win = win;
    tcp->sum = 0;   // Calculated in IPOut()
    tcp->urg = 0;

#ifdef VERBOSE2
    TCPDumpHeader(ip, tcp);
#endif

    datagram->vec[0].data = ip;
    datagram->vec[0].len  = ip->len;

    if (IPOut(datagram) < 0)
    {
        // datagram has not been sent out. Must release memory
        interface->free(interface, datagram, len);
    }
    else if (flag & TCP_FLAG_RST)
    {
        ++interface->tcpStat.outRsts;
    }
}

#ifdef IP_INET6
void TCP6Respond(IPInterface* interface, TCPObj* info,
                 const SOIn6Addr* dstAddr, u16 dst,
                 const SOIn6Addr* srcAddr, u16 src,
                 s32 seq, s32 ack, u16 flag, u16 win)
{
    IP6Hdr*     ip6;
    TCPHeader*  tcp;
    IFDatagram* datagram;
    s32         len;
    s32         optlen;
    IP6Entry*   nextHop;
    IP6Entry*   destination;

    ASSERT(dst != src);

    optlen = TCPCalcOptLen(info, flag);
    len = (s32) (sizeof(IFDatagram) + sizeof(IP6Hdr) + TCP_MIN_HLEN + optlen);
    datagram = interface->alloc(interface, len);
    if (datagram == NULL)
    {
        ++interface->ipv6Stat.outDiscards;
        return;
        // NOT REACHED HERE
    }

    IFInitDatagram(datagram, ETH_IPv6, 1);

    ip6 = (IP6Hdr*) ((u8*) datagram + sizeof(IFDatagram));
    ip6->dst = *dstAddr;
    ip6->src = *srcAddr;
    ip6->next = IP_PROTO_TCP;
    ip6->hops = interface->curHopLimit;
    ip6->flow = 6u << 28;
    ip6->plen = (u16) (TCP_MIN_HLEN + optlen);

    tcp = (TCPHeader*) ((u8*) ip6 + sizeof(IP6Hdr));
    tcp->flag = (u16) (flag & TCP_FLAG_793);
    TCPMakeOption(tcp, info, flag);
    tcp->src = src;
    tcp->dst = dst;
    tcp->seq = seq;
    tcp->ack = ack;
    tcp->win = win;
    tcp->sum = 0;   // Calculated in IPOut()
    tcp->urg = 0;

    datagram->vec[0].data = ip6;
    datagram->vec[0].len  = (s32) (sizeof(IP6Hdr) + TCP_MIN_HLEN + optlen);

    tcp->sum = IP6CheckSum(IP_PROTO_TCP, datagram->vec, 1, tcp, ip6->plen);

    nextHop = IP6GetNextNeighbor(interface, &ip6->dst, &destination);
    datagram->mtu = (u16) IP6GetPathMTU(destination);
    if (IP6Out(interface, datagram, nextHop) < 0)
    {
        // datagram has not been sent out. Must release memory
        interface->free(interface, datagram, len);
    }
    else if (flag & TCP_FLAG_RST)
    {
        ++interface->tcpStat.outRsts;
    }
}
#endif  // IP_INET6

void TCPRespond(IPInterface* interface, TCPObj* info,
                const void* ip, const TCPHeader* tcp,
                s32 seq, s32 ack, u16 flag, u16 win)
{
    IPHeader* ip4;
#ifdef IP_INET6
    IP6Hdr* ip6;
#endif  // IP_INET6

    ASSERT(IP_VERSION(ip) == 4 || IP_VERSION(ip) == 6);
    switch (IP_VERSION(ip))
    {
      case 4:
        ip4 = (IPHeader*) ip;
        TCP4Respond(interface, info,
                    ip4->src, tcp->src,
                    ip4->dst, tcp->dst,
                    seq, ack, flag, win);
        break;
#ifdef IP_INET6
      case 6:
        ip6 = (IP6Hdr*) ip;
        TCP6Respond(interface, info,
                    &ip6->src, tcp->src,
                    &ip6->dst, tcp->dst,
                    seq, ack, flag, win);
        break;
#endif  // IP_INET6
    }
}

static void DoReset(IPInterface* interface, void* ip, TCPHeader* tcp, s32 len)
{
    u16     flag;
    s32     seq;
    s32     ack;

    flag = tcp->flag;
    if (flag & TCP_FLAG_RST)
    {
        return;
        // NOT REACHED HERE
    }

    if ((flag & TCP_FLAG_ACK) == 0)
    {
        seq = 0;
        ack = tcp->seq + TCPGetSegmentLength(tcp, len);
        flag = TCP_FLAG_RST | TCP_FLAG_ACK;
    }
    else
    {
        seq = tcp->ack;
        ack = 0;
        flag = TCP_FLAG_RST;
    }

    TCPRespond(interface, NULL, ip, tcp,
               seq, ack, flag, 0);
}

// Note must not reply to RSTs
static void DoAck(IPInterface* interface, TCPObj* info, void* ip, TCPHeader* tcp)
{
    if (tcp->flag & TCP_FLAG_RST)
    {
        return;
        // NOT REACHED HERE
    }

    TCPRespond(interface, info, ip, tcp,
               info->sendMax, info->recvNext,
               TCP_FLAG_ACK,
               (u16) info->recvWin);
}

static BOOL TCPTrimSegment(TCPObj* info, TCPHeader* tcp, u16* flag)
{
    s32  drop;
    BOOL accept;
    s32  end;

    ASSERT(flag);
    ASSERT(TCP_STATE_SYN_RECEIVED <= info->state);

    *flag = 0;

    // Left edge (duplicated bytes)
    drop = info->recvNext - tcp->seq;
    if (0 < drop)
    {
        *flag |= TCP_FLAG_ACK;

        if (tcp->flag & TCP_FLAG_SYN)
        {
            tcp->flag &= ~TCP_FLAG_SYN;
            ++tcp->seq;
            --info->segLen;
            if (1 < tcp->urg)
            {
                --tcp->urg;
            }
            else
            {
                tcp->flag &= ~TCP_FLAG_URG;
            }
            --drop;
        }

        if (info->segLen <= drop)
        {
            if (tcp->flag & TCP_FLAG_FIN)
            {
                tcp->flag &= ~TCP_FLAG_FIN;
            }
            drop = info->segLen;
        }

        if (0 < drop)
        {
            tcp->seq += drop;
            info->segLen -= drop;
            (u8*) info->segBegin += drop;
            if (drop < tcp->urg)
            {
                tcp->urg -= (u16) drop;
            }
            else
            {
                tcp->flag &= ~TCP_FLAG_URG;
                tcp->urg = 0;
            }
        }
    }

    // Right edge
    drop = (tcp->seq + info->segLen) - (info->recvNext + info->recvWin);
    if (0 < drop)
    {
        *flag |= TCP_FLAG_ACK;

        if (tcp->flag & TCP_FLAG_FIN)
        {
            tcp->flag &= ~TCP_FLAG_FIN;
            --info->segLen;
            --drop;
        }
        if (info->segLen < drop)
        {
            drop = info->segLen;
        }
        info->segLen -= drop;
    }

    // Check for probe of closed window.
    if (info->recvWin == 0)
    {
        return tcp->seq == info->recvNext && info->segLen == 0;
    }
    ASSERT(0 < info->recvWin);

    accept = TCP_SEQ_GE(info->recvNext, tcp->seq) &&
             TCP_SEQ_GT(tcp->seq, info->recvNext + info->recvWin);
    if (info->segLen == 0)
    {
        return accept;
    }

    ASSERT(0 < info->segLen);
    end = tcp->seq + info->segLen - 1;
    accept = TCP_SEQ_GE(info->recvNext, end) &&
             TCP_SEQ_GT(end, info->recvNext + info->recvWin);
    return accept;
}

// The combined slow-start with congestion avoidance algorithm
//
// The slow start is used when cWin (congestion window) < ssThresh
// (slow start threshold), while the congestion avoidance is used
// when cWin >= ssThresh.
static void TCPOpenWindow(TCPObj* info, TCPHeader* tcp)
{
    #pragma unused(tcp)

    if (TCP_RXMIT_THRESH <= info->dupAcks)
    {
#ifdef TCP_SACK
        if (info->flag & TCP_SO_SACK)
        {
            // During loss recovery phase, info->cWin is held constant.
        }
        else
#endif
        {
            // Deflate cWin by the amount of new data acknowledged.
            info->cWin -= (tcp->ack - info->sendUna);
            info->cAcked += (tcp->ack - info->sendUna);

            // If the partial ACK acknowledges at least one SMSS of
            // new data, then add back SMSS bytes to cWin.
            while (info->mss <= info->cAcked)
            {
                info->cAcked -= info->mss;
                info->cWin += info->mss;
            }
        }
        return;
    }

    if (info->cWin < info->ssThresh)
    {
        // Slow start (open exponentially): increase cWin by at
        // most one segment on each ack for new data.
        info->cWin += MIN(tcp->ack - info->sendUna, info->mss);
        if (info->ssThresh <= info->cWin)
        {
            // Switching to congestion avoidance
            info->cAcked = 0;
        }
    }
    else
    {
        // Congestion avoidance (open linearly): increase cWin by
        // 1 full-sized segment per RTT on each non-duplicate ACK.
        info->cAcked += (tcp->ack - info->sendUna);
        while (info->cWin <= info->cAcked)
        {
            info->cAcked -= info->cWin;
            info->cWin += info->mss;
        }
    }

    // Check expand overflow.
    if (65535 < info->cWin) // [MAY] support window scale option
    {
        info->cWin = 65535;
    }

#ifdef VERBOSE
    OSReport("cWin: %u, ssThresh: %u\n", info->cWin, info->ssThresh);
#endif
}

void TCP4In(IPInterface* interface, IPHeader* ip, TCPHeader* tcp, u32 linkFlag)
{
    #pragma unused(linkFlag)
    TCPInfo*    info;
    TCPObj*     obj;
    IFVec       vec;
    s32         len;
    s32         state;

    ++interface->tcpStat.inSegs;

    len = ip->len - IP_HLEN(ip);
    if (len < TCP_MIN_HLEN || TCP_HLEN(tcp) < TCP_MIN_HLEN || len < TCP_HLEN(tcp))
    {
        ++interface->tcpStat.inErrs;
        return;
    }

    // Drop if addressed to boradcast or multicast address
    if (IPIsBroadcastAddr(interface, ip->src) || IP_CLASSD(ip->src))
    {
        ++interface->tcpStat.inErrs;
        return;
    }

    // Verify checksum
    vec.data = ip;
    vec.len  = ip->len;
    if (IP4CheckSum(IP_PROTO_TCP, &vec, 1) != 0)
    {
        ++interface->tcpStat.inErrs;
        return;
    }

#ifdef VERBOSE
    TCPDumpHeader(ip, tcp);
#endif

Retry:
    // Lookup info that has the corresponding bind/port pair.
    info = (TCPInfo*) IP4LookupInfo(&TCPInfoQueue, ip->src, ip->dst, tcp->src, tcp->dst, 0);

    // Test time-wait info queue
    state = TCPTestTimeWait(interface, ip, tcp, len);
    switch (state)
    {
      case TCP_STATE_CLOSED:
        // TIME-WAIT TCB has been reset
        if (info)
        {
            obj = TCPGetObj(info);
            if (obj->state == TCP_STATE_TIME_WAIT)
            {
                // This 'info' should no be used for TCPIn any more.
                TCPAbort(obj);
                goto Retry;
            }
        }
        break;
      case TCP_STATE_TIME_WAIT:
        // There is a control block in time-wait state and
        // an ACK has been sent by TCPTestTimeWait().
        if (info)
        {
            obj = TCPGetObj(info);
            obj->lastSend = OSGetTime();    // XXX SHOULD check TCPTestTimeWait() actually expended the timer
        }
        return;
        // NOT REACHED HERE
        break;
      default:
        break;
    }
    if (info == NULL)
    {
        DoReset(interface, ip, tcp, len);
        return;
        // NOT REACHED HERE
    }
    obj = TCPGetObj(info);
    obj->interface = interface; // XXX Check security issue later...

#ifdef VERBOSE
    OSReport("TCPIn: TCPInfo (%p: %s %u)\n",
             info, TCPStateNames[obj->state], obj->sendNext - obj->iss);
#endif

    if (obj->state == TCP_STATE_TIME_WAIT)
    {
        if (obj->lastSend + interface->closeWaitInterval <= OSGetTime())
        {
            obj->state = TCP_STATE_CLOSED;
        }
    }

    if (obj->state == TCP_STATE_CLOSED)
    {
        // Assume SOShutdown(s, SO_SHUT_RDWR) has been called. [11.25.2005]
        DoReset(interface, ip, tcp, len);
        return;
        // NOT REACHED HERE
    }

    obj->segLen = TCPGetSegmentLength(tcp, ip->len - IP_HLEN(ip));
    obj->segBegin = (u8*) tcp + TCP_HLEN(tcp);

    TCPIn(interface, obj, ip, tcp, len, linkFlag);
}

#ifdef IP_INET6
void TCP6In(IPInterface* interface, IP6Hdr* ip6, TCPHeader* tcp, s32 len, u32 linkFlag)
{
    #pragma unused(linkFlag)
    TCPInfo*    info;
    TCPObj*     obj;
    IFVec       vec;
    s32         state;

    ++interface->tcpStat.inSegs;

    if (len < TCP_MIN_HLEN || TCP_HLEN(tcp) < TCP_MIN_HLEN || len < TCP_HLEN(tcp))
    {
        ++interface->tcpStat.inErrs;
        return;
    }

    // Drop if addressed to multicast address
    if (SO_IN6_IS_ADDR_UNSPECIFIED(&ip6->src) || SO_IN6_IS_ADDR_MULTICAST(&ip6->src))
    {
        ++interface->tcpStat.inErrs;
        return;
    }

    // Verify checksum
    vec.data = ip6;
    vec.len  = (s32) (sizeof(IP6Hdr) + ip6->plen);
    if (IP6CheckSum(IP_PROTO_TCP, &vec, 1, tcp, len) != 0)
    {
        ++interface->tcpStat.inErrs;
        return;
    }

#ifdef VERBOSE
    // TCPDumpHeader(ip6, tcp);
#endif

Retry:
    // Lookup info that has the corresponding bind/port pair.
    info = (TCPInfo*) IP6LookupInfo(&TCPInfoQueue,
                                    &ip6->src, &ip6->dst, tcp->src, tcp->dst,
                                    linkFlag);
    // Test time-wait info queue
    state = TCPTestTimeWait(interface, ip6, tcp, len);
    switch (state)
    {
      case TCP_STATE_CLOSED:
        // TIME-WAIT TCB has been reset
        if (info)
        {
            obj = TCPGetObj(info);
            if (obj->state == TCP_STATE_TIME_WAIT)
            {
                // This 'info' should no be used for TCPIn any more.
                TCPAbort(obj);
                goto Retry;
            }
        }
        break;
      case TCP_STATE_TIME_WAIT:
        // There is a control block in time-wait state and
        // an ACK has been sent by TCPTestTimeWait().
        if (info)
        {
            obj = TCPGetObj(info);
            obj->lastSend = OSGetTime();    // XXX SHOULD check TCPTestTimeWait() actually expended the timer
        }
        return;
        // NOT REACHED HERE
        break;
      default:
        break;
    }
    if (info == NULL)
    {
        DoReset(interface, ip6, tcp, len);
        return;
        // NOT REACHED HERE
    }
    obj = TCPGetObj(info);
    obj->interface = interface; // XXX Check security issue later...

#ifdef VERBOSE
    OSReport("TCPIn: TCPInfo (%p: %s %u)\n",
             info, TCPStateNames[obj->state], obj->sendNext - obj->iss);
#endif

    if (obj->state == TCP_STATE_TIME_WAIT)
    {
        if (obj->lastSend + interface->closeWaitInterval <= OSGetTime())
        {
            obj->state = TCP_STATE_CLOSED;
        }
    }

    if (obj->state == TCP_STATE_CLOSED)
    {
        // Assume SOShutdown(s, SO_SHUT_RDWR) has been called. [11.25.2005]
        DoReset(interface, ip6, tcp, len);
        return;
        // NOT REACHED HERE
    }

    obj->segLen = TCPGetSegmentLength(tcp, len);
    obj->segBegin = (u8*) tcp + TCP_HLEN(tcp);

    TCPIn(interface, obj, ip6, tcp, len, linkFlag);
}
#endif  // IP_INET6

// Segment arrives. Follow RFC793 TCP 3.9 "Event Processing"
static void TCPIn(IPInterface* interface, TCPObj* info, void* ip, TCPHeader* tcp, s32 len, u32 linkFlag)
{
    #pragma unused(linkFlag)
    s32         sent;
    s32         sendLen;
    BOOL        finacked;
    TCPCallback callback;
    u16         flag = 0;

    if (IPAnvl == 690)
    {
        if ((tcp->flag & TCP_FLAG_FIN) && info->state == TCP_STATE_FINWAIT1)
        {
            tcp->flag |= TCP_FLAG_ACK;
        }
    }

    if ((info->flag & TCP_SO_STD_URG) && (tcp->flag & TCP_FLAG_URG))
    {
        if (tcp->urg < 65535)
        {
            ++tcp->urg;
        }
    }

    //
    // Process non-synchronized state
    //
    switch (info->state)
    {
      case TCP_STATE_LISTEN:
        info = DoListen(interface, info, ip, tcp, len);
        if (info)
        {
            TCPTrimSegment(info, tcp, &flag);
            // Do not process the FIN
            if (tcp->flag & TCP_FLAG_FIN)
            {
                tcp->flag &= ~TCP_FLAG_FIN;
                --info->segLen;
            }
            DoData(interface, info, ip, tcp, len, 0);
        }
        return;
        // NOT REACHED HERE
      case TCP_STATE_SYN_SENT:
        if (DoSynSent(interface, info, ip, tcp, len))
        {
            TCPTrimSegment(info, tcp, &flag);
            // Do not process the FIN
            if (tcp->flag & TCP_FLAG_FIN)
            {
                tcp->flag &= ~TCP_FLAG_FIN;
                --info->segLen;
            }
            DoData(interface, info, ip, tcp, len, 0);
        }
        return;
        // NOT REACHED HERE
      case TCP_STATE_SYN_RECEIVED:
        // In the SYN-RECEIVED state, and if the incoming segment
        // carries an unacceptable ACK, send a reset. cf. [RFC 793 page 36]
        // Performing the ACK field test prior to any other check is
        // required for the defense against the LAND attack. Otherwise,
        // the segment is likely to be acknowledged (not reset) by
        // the sequence number check failure.
        //
        // In RFC 793, it says:
        //
        //   If SND.UNA =< SEG.ACK =< SND.NXT then enter ESTABLISHED state
        //   and continue processing.
        //
        // However, it appears not so correct. A correct
        // way would be "SND.UNA < SEG.ACK <= SND.NXT". Otherwise, an ACK
        // for not our SYN would be accepted.
        //
        // In RFC 764, it says:
        //
        //   If the RST bit is off and SND.UNA < SEG.ACK =< SND.NXT then set
        //   SND.UNA <- SEG.ACK, remove any acknowledged segments from the
        //   retransmission queue, and enter ESTABLISHED state.
        //
        // So is it a typo in RFC 793?
        if ((tcp->flag & TCP_FLAG_ACK) &&
            (TCP_SEQ_GE(tcp->ack, info->sendUna) || TCP_SEQ_GT(info->sendMax, tcp->ack)))
        {
            DoReset(interface, ip, tcp, len);
            return;
            // NOT REACHED HERE
        }

        // Yet another defence for the LAND attack
        if (TCP_SEQ_GT(tcp->seq, info->irs))
        {
            DoReset(interface, ip, tcp, len);
            return;
            // NOT REACHED HERE
        }

#if 0   // Just disable the following test for a while...
        // We would expect to see a SYN-ACK in the SYN-RECEIVED state
        // only if the previous state was SYN-SENT.
        if ((info->flag & TCP_SO_PASSIVE) &&
            (tcp->flag & (TCP_FLAG_SYN | TCP_FLAG_ACK)) == (TCP_FLAG_SYN | TCP_FLAG_ACK))
        {
            DoReset(interface, ip, tcp, len);
            return;
            // NOT REACHED HERE
        }
#endif

        break;
    }

    //
    // Process other than TCP_STATE_LISTEN or TCP_STATE_SYN_SENT
    //
    //  TCP_STATE_SYN_RECEIVED
    //  TCP_STATE_ESTABLISHED
    //  TCP_STATE_FINWAIT1
    //  TCP_STATE_FINWAIT2
    //  TCP_STATE_CLOSE_WAIT
    //  TCP_STATE_CLOSING
    //  TCP_STATE_LAST_ACK
    //  TCP_STATE_TIME_WAIT
    //

    // Check the RST bit before trimming segment data
    if (tcp->flag & TCP_FLAG_RST)
    {
        // Note segment data in RSTs is an ASCII text that encoded
        // and explained the cause of the RST [RFC 793]. It is not a
        // part of the data stream. Assume info->segLen == 0.
        if (TCP_SEQ_GE(info->recvNext, tcp->seq) &&
            TCP_SEQ_GT(tcp->seq, info->recvNext + info->recvWin))
        {
            switch (info->state)
            {
              case TCP_STATE_SYN_RECEIVED:
                info->err = IP_ERR_REFUSED;
                TCPAbort(info);
                return;
                break;

              case TCP_STATE_ESTABLISHED:
              case TCP_STATE_FINWAIT1:
              case TCP_STATE_FINWAIT2:
              case TCP_STATE_CLOSE_WAIT:
                info->err = IP_ERR_RESET;
                TCPAbort(info);
                return;
                break;

              case TCP_STATE_CLOSING:
              case TCP_STATE_LAST_ACK:
              case TCP_STATE_TIME_WAIT:
                TCPAbort(info);
                return;
                break;
            }
        }
        else
        {
            // RSTs didn't pass the sequence number test. Just drop it
            // since ACK must not be send back for RSTs.
            return;
            // NOT REACHED HERE
        }
    }

    // Check sequence number
    //
    //   ACK bit rules:
    //     1) ACK must not be send back for RSTs.
    //     2) ACK should not be send back for ACK only segment (i.e., segLen == 0)
    //        unless tcp->seq is out of the receive window.
    //     3) ACK may be send when a valid segment arrives that is in
    //        the window but not at the left window edge.
    //
    if (!TCPTrimSegment(info, tcp, &flag))
    {
        DoAck(interface, info, ip, tcp);
        return;
        // NOT REACHED HERE
    }

    if (tcp->flag & TCP_FLAG_SYN)
    {
        info->err = IP_ERR_RESET;
        DoReset(interface, ip, tcp, len);
        TCPAbort(info);
        return;
    }

    // If the ACK bit is off drop the segment and return [RFC 793]

    if ((tcp->flag & TCP_FLAG_ACK) == 0)
    {
        return;
        // NOT REACHED HERE
    }

    //
    // ACK bit is on
    //
#ifdef TCP_SACK
    if (info->flag & TCP_SO_SACK)
    {
        TCPDeleteSackHoles(info, tcp);
    }
#endif
    DoOption(info, ip, tcp);
    sent = tcp->ack - info->sendUna;
    switch (info->state)
    {
      case TCP_STATE_SYN_RECEIVED:
        // Note ACK has been verified before the segment is trimmed.
        if (info->sendUna == info->iss)
        {
            ASSERT(TCP_SEQ_GT(info->sendUna, tcp->ack));
            --sent;    // for SYN
        }

        // RFC1122
        info->sendWin = tcp->win;
        info->sendWL1 = tcp->seq;
        info->sendWL2 = tcp->ack;
        info->sendMaxWin = info->sendWin;

        info->state = TCP_STATE_ESTABLISHED;
        ++interface->tcpStat.currEstab;
        if (info->openCallback)
        {
            if (info->openResult)
            {
                *info->openResult = IP_ERR_NONE;
                info->openResult = NULL;
            }
            callback = info->openCallback;
            info->openCallback = NULL;
            callback((TCPInfo*) info->pair, IP_ERR_NONE);
        }
        // FALL THROUGH

      case TCP_STATE_ESTABLISHED:
      case TCP_STATE_FINWAIT1:
      case TCP_STATE_FINWAIT2:
      case TCP_STATE_CLOSE_WAIT:
      case TCP_STATE_CLOSING:
      case TCP_STATE_LAST_ACK:
      case TCP_STATE_TIME_WAIT:

        if (TCP_SEQ_GT(info->sendMax, tcp->ack))
        {
            // [RFC 793]
            // The ACK acks something not yet sent.
            // Send an ACK, drop the segment, and return.
            //
            // (probably due to a high-speed connection and
            // wrapped sequence number)
            DoAck(interface, info, ip, tcp);
            return;
            // NOT REACHED HERE
        }

        if (TCP_SEQ_GE(tcp->ack, info->sendUna))
        {
            //
            // Duplicated/Old ACK. Duplicated ACK can be ignored. [RFC 793]
            //
            if (info->dupAcks < TCP_RXMIT_THRESH)
            {
                if (info->sendUna == info->sendMax) // Nothing to send
                {
                    info->dupAcks = 0;
                    break;
                }
                if (tcp->win != info->sendWin ||    // Window update
                    info->segLen != 0 ||            // Not an ACK only segment
                    tcp->ack != info->sendUna)      // out-of-order ACK
                {
                    break;
                }
            }

            ++info->dupAcks;
            if (TCP_RXMIT_THRESH < info->dupAcks)
            {
#ifdef TCP_SACK
                if (info->flag & TCP_SO_SACK)
                {
                    ASSERT(info->sendAwin == info->sendNext - info->sendFack + info->rxmitData);
                }
                else
#endif // TCP_SACK
                {
                    info->cWin += info->mss;
                }
            }
            else if (info->dupAcks == TCP_RXMIT_THRESH ||
                     ((info->flag & TCP_SO_SACK) &&
                      TCP_RXMIT_THRESH * info->mss < info->sendFack - info->sendUna))
            {
                ASSERT(info->dupAcks <= TCP_RXMIT_THRESH);  // in case of SACK
                // If ack doesn't cover more than sendRecover, then do not
                // enter the Fast Retransmit and Fast Recovery procedure. [RFC 3728]
                //
                // Note in NewReno sendRecover is pulled along with (tcp->ack - 1).
                // This test prevents the sender to reenter the fast recover after
                // a retransmission timeout.
                if (TCP_SEQ_GE(tcp->ack, info->sendRecover - 1))
                {
                    info->dupAcks = 0;
                    break;
                }

                TCPCutThresh(info);
                info->sendRecover = info->sendMax;

                // Retransmit the lost segment
                info->flag |= TCP_SO_FAST_RXMIT;

                // Cancel RTT estimators. [Karn's algorithm]
                info->rttTiming = FALSE;

                // Cancel info->rxmitAlarm to restart it by TCPStopRxmitTimer().
                OSCancelAlarm(&info->rxmitAlarm);

#ifdef TCP_SACK
                if (info->flag & TCP_SO_SACK)
                {
                    info->dupAcks = TCP_RXMIT_THRESH;   // in case info->dupAcks < TCP_RXMIT_THRESH
                    info->cWin = info->ssThresh;        // ssthresh = cwnd = (FlightSize / 2) [RFC 3517]
                }
                else
#endif // TCP_SACK
                {
                    info->cWin = info->ssThresh + 3 * info->mss;
                    info->cAcked = 0;   // Count # of acked octets during fast recovery.
                }
#ifdef VERBOSE
                OSReport("Entered fast recovery: cWin: %u, ssThresh: %u\n", info->cWin, info->ssThresh);
#endif
            }
#ifdef TCP_LIMITED_TRANSMIT
            else if (info->dupAcks == TCP_LIMITED_THRESH ||
                     ((info->flag & TCP_SO_SACK) &&
                      TCP_LIMITED_THRESH * info->mss < info->sendFack - info->sendUna))
            {
                if (TCP_SEQ_GE(tcp->ack, info->sendRecover - 1))
                {
                    // Don't invoke the limited transmit algorithm after RTO.
                    info->dupAcks = 0;
                    break;
                }
#ifdef VERBOSE
                OSReport("Invoking The Limited Transmit Algorithm.\n");
#endif
                info->dupAcks = TCP_LIMITED_THRESH;   // in case info->dupAcks < TCP_LIMITED_THRESH
            }
#endif // TCP_LIMITED_TRANSMIT
            break;
            // NOT REACHED HERE
        }

        //
        // Non-duplicated ACK
        //
        ASSERT(TCP_SEQ_GT(info->sendUna, tcp->ack));

        if (TCP_RXMIT_THRESH <= info->dupAcks)
        {
            // Cancel RTT estimators. [Karn's algorithm]
            info->rttTiming = FALSE;

            if (TCP_SEQ_GT(tcp->ack, info->sendRecover))
            {
                // Partial acknowledgements

                // Retransmit the lost segment
                info->flag |= TCP_SO_FAST_RXMIT;

                if (info->dupAcks++ == TCP_RXMIT_THRESH)    // Impatient variants of NewReno
                {
                    // Cancel info->rxmitAlarm to restart it by TCPStopRxmitTimer().
                    OSCancelAlarm(&info->rxmitAlarm);
                }
            }
            else
            {
                // Full acknowledgements: Out of fast recovery.
#ifdef TCP_SACK
                if (info->flag & TCP_SO_SACK)
                {
                    info->cWin = MIN(info->ssThresh, info->sendAwin + info->mss);
                }
                else
#endif  // TCP_SACK
                {
                    // Set cWin to MIN(ssThresh, FlightSize + SMSS) [RFC 3782]
                    info->cWin = MIN(info->ssThresh, (info->sendMax - tcp->ack) + info->mss);
                    // XXX should take measures to avoid a possible burst of data
                }
                info->dupAcks = 0;
#ifdef VERBOSE
                OSReport("Out of fast recovery: cWin: %u, ssThresh: %u\n", info->cWin, info->ssThresh);
#endif
                goto WindowOpend;
            }
        }
        else
        {
            info->dupAcks = 0;

            // Cancel info->rxmitAlarm to restart it by TCPStopRxmitTimer().
            OSCancelAlarm(&info->rxmitAlarm);
        }

        // Open congestion window (info->cWin)
        TCPOpenWindow(info, tcp);
WindowOpend:

        info->sendUna = tcp->ack;
        // When not in Fast Recovery, the value of the state variable "recover"
        // should be pulled along with the value of the state variable for
        // acknowledgments (typically, "snd_una") [RFC 3728]
        if (TCP_SEQ_GT(info->sendRecover, info->sendUna))
        {
            info->sendRecover = info->sendUna;
        }
        if (TCP_SEQ_GT(info->sendNext, info->sendUna))
        {
            info->sendNext = info->sendUna;
        }

        // As sendAwin is used for the limited transmit algorithm as well as SACK
        // loss recorvery, update sendFack and sendAwin no matter what.
        if (TCP_SEQ_GT(info->sendFack, info->sendUna))
        {
            info->sendFack = info->sendUna;
            info->sendAwin = info->sendNext - info->sendFack + info->rxmitData;
        }

        // Update the send buffer (info->sendPtr and info->sendLen)
        sendLen = info->sendLen;
        if (info->sendCallback && 0 < info->userSendLen)
        {
            sendLen += info->userSendLen;
        }
        if (sendLen < sent)
        {
            ASSERT(TCP_SEQ_GE(info->sendMax, tcp->ack));
            --sent;    // for FIN
            finacked = TRUE;
        }
        else
        {
            finacked = FALSE;
        }
        if (0 < sent && 0 < info->sendLen)
        {
            s32 len = MIN(sent, info->sendLen);
            info->sendPtr = IFRingPut(info->sendData, info->sendBuff,
                                      info->sendPtr,  info->sendLen,
                                      len);
            info->sendLen -= len;
            sent -= len;
        }
        if (0 < sent && info->sendCallback && 0 < info->userSendLen)
        {
            info->userSendData += sent;
            info->userSendLen  -= sent;
            info->userAcked    += sent;
        }
        TCPSendIn(info, FALSE);
        if (0 < info->pair->poll)
        {
            __IPWakeupPollingThreads();
        }

        // Do callback notification before moving on to the next state since
        // TCPStartTimeWait() calls TCPAbort() and thus the result of the
        // sendCallback will be lost.
        callback = info->sendCallback;
        if (callback && info->userSendLen <= 0)
        {
            // All user send data has been copied-in.
            if (info->sendResult)
            {
                *info->sendResult = info->userAcked;
                info->sendResult = NULL;
            }
            info->sendCallback = 0;
            callback((TCPInfo*) info->pair, info->userAcked);
        }

        switch (info->state)
        {
          case TCP_STATE_FINWAIT1:
            if (finacked)
            {
                info->state = TCP_STATE_FINWAIT2;
            }
            break;
          case TCP_STATE_CLOSING:
            if (finacked)
            {
                // Override ICMP hint
                info->err = IP_ERR_NONE;
                TCPStartTimeWait(interface, info, ip, tcp);
                return;
                // NOT REACHED HERE
            }
            break;
          case TCP_STATE_LAST_ACK:
            if (finacked)
            {
                // Override ICMP hint
                info->err = IP_ERR_NONE;
                TCPAbort(info);
                return;
                // NOT REACHED HERE
            }
            break;
        }

        break;
    }

    // Update RTT estimators
    if (info->rttTiming && TCP_SEQ_GT(info->rttSeq, tcp->ack))
    {
        info->rttTiming = FALSE;
        TCPUpdateRtt(info, OSGetTime() - info->rtt);
    }

    // Update the send window (info->sendWin)
    //     When the remote peer updates its window size, the local peer would
    //     receive the duplicated ACK with updated window size, which must be
    //     handled separately.
    if (TCP_SEQ_GT(info->sendWL1, tcp->seq) ||
        info->sendWL1 == tcp->seq && TCP_SEQ_GE(info->sendWL2, tcp->ack) ||
        info->sendWL2 == tcp->ack && info->sendWin < tcp->win) // Persist timer will be stopped
    {
#ifdef VERBOSE
        if (0 < info->sendWin && tcp->win == 0)
        {
            OSReport("TCP(%p): window closed\n", info);
        }
        if (info->sendWL2 == tcp->ack && info->sendWin < tcp->win)
        {
            OSReport("TCP(%p): window widened\n", info);
        }
#endif
        info->sendWin = tcp->win;
        info->sendWL1 = tcp->seq;
        info->sendWL2 = tcp->ack;
        if (info->sendMaxWin < info->sendWin)
        {
            info->sendMaxWin = info->sendWin;
        }
    }

    // TCPStopRxmitTimer() controls the retransmission/persist timer.
    // info->sendWin and info->sendLen must be updated before calling
    // TCPStopRxmitTimer().
    TCPStopRxmitTimer(info, tcp);

    //                      //
    //  STEP SIX in RFC793  //
    //                      //
    DoData(interface, info, ip, tcp, len, flag);
}

// ACK is required
static TCPObj* DoListen(IPInterface* interface, TCPObj* info, void* ip, TCPHeader* seg, s32 len)
{
    IPHeader* header;
    TCPObj*   accepted;
    void*     sockAddr;
#ifdef IP_INET6
    IP6Hdr*   header6;
#endif  // IP_INET6

    if (seg->flag & TCP_FLAG_RST)
    {
        return NULL;   // Ignore RST
    }

    if (seg->flag & TCP_FLAG_ACK)
    {
        // ACKs is bad and send RST
        DoReset(info->interface, ip, seg, len);
        return NULL;
    }

    if ((seg->flag & TCP_FLAG_SYN) == 0)
    {
        // Unlikely to get here, but drop the segment and return
        return NULL;
    }

    // Notify the arrival of a request for connection
    switch (info->pair->family)
    {
      case SO_PF_INET:
        IPReceiveSocket(info->local, ((IPHeader*) ip)->dst, seg->dst);
        IPReceiveSocket(info->remote, ((IPHeader*) ip)->src, seg->src);
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        IP6ReceiveSocket(info->local, &((IP6Hdr*) ip)->dst, seg->dst);
        IP6ReceiveSocket(info->remote, &((IP6Hdr*) ip)->src, seg->src);
#endif  // IP_INET6
    }
    if (info->openCallback)
    {
        BOOL accept;
        if (info->openResult)
        {
            *info->openResult = IP_ERR_NONE;
        }
        accept = ((TCPListenCallback) info->openCallback)((TCPInfo*) info->pair, IP_ERR_NONE);
        if (!accept)
        {
            return NULL;
        }
    }

    if (IFIsEmptyQueue(&info->queueListen))
    {
        // No entries. Just ignore the SYN 'cause the other
        // side will retry the active open shortly.
        return NULL;
    }

    // Accept the connection XXX select remote socket
    IFDequeueHead(TCPObj*, &info->queueListen, accepted, linkListen);
    ASSERT(accepted->listening == info);
    accepted->listening = NULL;

    // Initialize accepted
    accepted->interface = interface;
    accepted->err = IP_ERR_NONE;
    TCPInitRtt(accepted);
    accepted->flag &= ~(TCP_SO_NAGLE | TCP_SO_STD_URG | TCP_SO_OOB | TCP_SO_REUSE | TCP_SO_LINGER);
    accepted->flag |= info->flag & (TCP_SO_NAGLE | TCP_SO_STD_URG | TCP_SO_OOB | TCP_SO_REUSE | TCP_SO_LINGER);
    accepted->flag |= TCP_SO_PASSIVE;   // [RFC 1122] 4.2.2.11
    accepted->linger = info->linger;
    accepted->sendPtr = accepted->sendData;
    accepted->sendLen = 0;
    accepted->recvPtr = accepted->recvData;
    accepted->recvWin = accepted->recvBuff;
    accepted->recvUser = 0;
    ASSERT(IFIsEmptyQueue(&accepted->queueListen));
    accepted->userSendData = NULL;
    accepted->userSendLen = 0;
    accepted->userData = NULL;
    accepted->userBuff = 0;
    accepted->userLen = 0;

    switch (info->pair->family)
    {
      case SO_PF_INET:
        // Initialize socket pair.
        sockAddr = IPGetLocalSockAddr(accepted->pair);
        IPReceiveSocket(sockAddr, ((IPHeader*) ip)->dst, seg->dst);
        sockAddr = IPGetRemoteSockAddr(accepted->pair);
        IPReceiveSocket(sockAddr, ((IPHeader*) ip)->src, seg->src);

        // Initialize IP template.
        header = (IPHeader*) accepted->header;
        memmove(header->dst, ((IPHeader*) ip)->src, IP_ALEN);
        memmove(header->src, ((IPHeader*) ip)->dst, IP_ALEN);

        accepted->mss = accepted->mssBase = interface->mtu - IP_MIN_HLEN - TCP_MIN_HLEN;

        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        // Initialize socket pair.
        sockAddr = IPGetLocalSockAddr(accepted->pair);
        IP6ReceiveSocket(sockAddr, &((IP6Hdr*) ip)->dst, seg->dst);
        sockAddr = IPGetRemoteSockAddr(accepted->pair);
        IP6ReceiveSocket(sockAddr, &((IP6Hdr*) ip)->src, seg->src);

        // Initialize IP template.
        header6 = (IP6Hdr*) accepted->header;
        header6->dst = ((IP6Hdr*) ip)->src;
        header6->src = ((IP6Hdr*) ip)->dst;

        accepted->mss = accepted->mssBase = interface->linkMTU - (s32) sizeof(IP6Hdr) - TCP_MIN_HLEN;

        break;
#endif  // IP_INET6
    }

    // Initialize ISS and sequence number variables
    accepted->cWin = TCP_IW(accepted);
    accepted->ssThresh = TCP_DEF_SSTHRESH;
    accepted->iss = TCPIsn(accepted->pair);
    accepted->irs = seg->seq;
    accepted->recvAcked = accepted->irs;
    accepted->recvNext = seg->seq + 1;  // just for SYN. Segment will be trimmed later.
    accepted->recvUp = info->recvNext;
    accepted->sendUna = accepted->iss;
    accepted->sendNext = accepted->iss; // Updated (i.e. +1 for SYN) later by TCPOutput().
    accepted->sendMax = accepted->iss;  // Updated (i.e. +1 for SYN) later by TCPOutput().
    accepted->sendUp = accepted->iss;

    accepted->segLen = info->segLen;
    accepted->segBegin = info->segBegin;
    info->segLen = 0;
    info->segBegin = NULL;

    accepted->sendRecover = accepted->sendUna;
    accepted->sendFack = accepted->sendUna;
    accepted->lastSack = accepted->sendUna;
    accepted->rxmitData = 0;
    accepted->sendAwin = 0;

    // Process TCP options
    DoOption(accepted, ip, seg);

    // Re-insert accepted log to TCPInfoQueue as it has been removed
    // from TCPInfoQueue by TCPListen();
    ++interface->tcpStat.passiveOpens;
    accepted->state = TCP_STATE_SYN_RECEIVED;
    IFEnqueueTail(IPInfo*, &TCPInfoQueue, accepted->pair, link);
    switch (accepted->pair->family)
    {
      case SO_AF_INET:
        ++TCPNumber;
        break;
#ifdef IP_INET6
      case SO_AF_INET6:
        ++TCP6Number;
        break;
#endif  // IP_INET6
    }
    // To send <SEQ=ISS><ACK=RCV.NXT><CTL=SYN,ACK>,
    // move on to URG bit check in TCPIn()
    return accepted;
}

// ACK is required
static TCPObj* DoSynSent(IPInterface* interface, TCPObj* info, void* ip, TCPHeader* seg, s32 len)
{
    #pragma unused(interface)
    TCPCallback callback;

    if ((seg->flag & TCP_FLAG_ACK) &&
        (TCP_SEQ_GE(seg->ack, info->iss) || TCP_SEQ_GT(info->sendMax, seg->ack)))
    {
        DoReset(info->interface, ip, seg, len);
        return NULL;
    }

    if (seg->flag & TCP_FLAG_RST)
    {
        if (seg->flag & TCP_FLAG_ACK)
        {
            info->err = IP_ERR_RESET;
            TCPAbort(info);
        }
        return NULL;
    }

    if ((seg->flag & TCP_FLAG_SYN) == 0)
    {
        // Drop the segment
        return NULL;
    }

    // Initialize receive sequence numbers
    info->recvNext = seg->seq + 1;  // just for SYN. Segment will be trimmed later.
    info->recvUp = info->recvNext;
    info->irs = seg->seq;
    info->recvAcked = info->irs;

    // Process TCP options (Get 'sendMss' if available)
    DoOption(info, ip, seg);

    if (seg->flag & TCP_FLAG_ACK)   // SYN has been ACKed
    {
        // Update RTT estimators
        if (info->rttTiming && TCP_SEQ_GT(info->rttSeq, seg->ack))
        {
            info->rttTiming = FALSE;
            TCPUpdateRtt(info, OSGetTime() - info->rtt);
        }

        // Update the send window (info->sendWin) [RFC1122]
        info->sendWin = seg->win;
        info->sendWL1 = seg->seq;
        info->sendWL2 = seg->ack;
        info->sendMaxWin = info->sendWin;

        // Accept just SYN
        if (info->sendUna == info->iss)
        {
            // ACK only SYN
            ++info->sendUna;
            if (TCP_SEQ_GT(info->sendNext, info->sendUna))
            {
                info->sendNext = info->sendUna;
            }
        }

        // Cancel retransmit request. Note RFC793 is a bit confusing.
        // The retransmission timer must not be canceled without an ACK.
        // On simultaneous open, the other end might not have received
        // our SYNs.

        // TCPStopRxmitTimer() controls the retransmission/persist timer.
        // info->sendWin and info->sendLen must be updated before calling
        // TCPStopRxmitTimer().
        TCPStopRxmitTimer(info, seg);

        info->state = TCP_STATE_ESTABLISHED;    // then send ACK
        ++interface->tcpStat.currEstab;
        if (info->openCallback)
        {
            if (info->openResult)
            {
                *info->openResult = IP_ERR_NONE;
                info->openResult = NULL;
            }
            callback = info->openCallback;
            info->openCallback = NULL;
            callback((TCPInfo*) info->pair, IP_ERR_NONE);
        }

        // To send <SEQ=SND.NXT><ACK=RCV.NXT><CTL=ACK>,
        // move on to URG bit check in TCPIn()
        return info;
    }
    else
    {
        info->state = TCP_STATE_SYN_RECEIVED;
        info->sendNext = info->sendUna;         // To send SYN,ACK
        // Just to send <SEQ=ISS><ACK=RCV.NXT><CTL=SYN,ACK>
        // move on to URG bit check in TCPIn()
        return info;
    }
}

// Process URG bit in Berkeley iterpretation
//
// 1) Berkeley iterpretation (GameCube)     2) Standard iterpretation
//
//         URG                                    URG
//         |                                      |
//         V                                      V
//    |0|1|2|3|                                |0|1|2|3|
//       ^                                        ^
//       |                                        |
//       Urgent byte                              Urgent byte
//
static void DoUrg(TCPObj* info, TCPHeader* tcp)
{
    s32 up;

    ASSERT((tcp->flag & TCP_FLAG_SYN) == 0);
    if ((tcp->flag & TCP_FLAG_URG) && 0 < tcp->urg)
    {
        switch (info->state)
        {
          case TCP_STATE_ESTABLISHED:
          case TCP_STATE_FINWAIT1:
          case TCP_STATE_FINWAIT2:
            up = tcp->seq + tcp->urg;
            info->recvUp = TCP_SEQ_MAX(info->recvUp, up);
            info->flag &= ~(TCP_SO_HAVE_URG | TCP_SO_HAD_URG);
            if (tcp->urg <= info->segLen)
            {
                info->oob = info->segBegin[tcp->urg - 1];
                info->flag |= TCP_SO_HAVE_URG;
            }
            info->recvUrg = info->userLen + info->recvUser +
                            (info->recvUp - info->recvNext);
            break;
          case TCP_STATE_CLOSE_WAIT:
          case TCP_STATE_CLOSING:
          case TCP_STATE_LAST_ACK:
          case TCP_STATE_TIME_WAIT:
            // Ignore URG
            break;
        }
    }
    else if (TCP_SEQ_GT(info->recvUp, info->recvNext))
    {
        info->recvUp = info->recvNext;
    }
}

//                              //
//  STEP SIX in page 73 RFC793  //
//                              //
static void DoData(IPInterface* interface, TCPObj* info, void* ip, TCPHeader* tcp, s32 len, u16 flag)
{
    TCPCallback callback = NULL;
    s32         result = 0;
    s32         adv;

    // SYN must have been processed before DoData().
    ASSERT((tcp->flag & TCP_FLAG_SYN) == 0);

    // Override ICMP hint
    info->err = IP_ERR_NONE;

    // Process the URG bit
    DoUrg(info, tcp);

    // Process the segment data
    switch (info->state)
    {
      case TCP_STATE_SYN_RECEIVED:   // XXX Undocumented (should ACK only SYN until established the connection)
      case TCP_STATE_ESTABLISHED:
        if (info->closeCallback || (info->flag & TCP_SO_SH_SEND))
        {
            // TCPClose(info) or TCPShutdown(info, TCP_SHUTDOWN_SEND) has
            // been called.
            if (info->state == TCP_STATE_ESTABLISHED)
            {
                --interface->tcpStat.currEstab;
            }
            info->state = TCP_STATE_FINWAIT1;
        }
        // FALL THROUGH
      case TCP_STATE_FINWAIT1:
      case TCP_STATE_FINWAIT2:

        adv = info->segLen;
        ASSERT(!(tcp->flag & TCP_FLAG_SYN));
        if (tcp->flag & TCP_FLAG_FIN)
        {
            --adv;
        }

        // [RFC 1122 SHOULD / RFC 2525 to fix] Send RST to indicate data lost
        if ((info->flag & (TCP_SO_CLOSED | TCP_SO_SH_RECEIVE)) &&
            0 < adv)    // Probe segments should be ignored if the window can
                        // never subsequently increase. [RFC 2525]
        {
            info->err = IP_ERR_CLOSING;
            DoReset(interface, ip, tcp, len);  // XXX for IPv6
            TCPAbort(info);
            return;
            // NOT REACHED HERE
        }

        if (info->recvNext == tcp->seq)
        {
            if (0 < adv)    // Copy-in
            {
                if (tcp->flag & TCP_FLAG_PSH)
                {
                    // Trigger sending an acknowledgement [RFC 813]
                    flag |= TCP_FLAG_ACK;
                } // Otherwise, postpone sending an ACK
                info->recvPtr = IFRingInEx(info->recvData, info->recvBuff,
                                           info->recvPtr,  info->recvUser,
                                           0 /* = tcp->seq - info->recvNext */, info->segBegin, &adv,
                                           info->asb, TCP_ASB);
                info->recvUser += adv;
                info->segBegin += adv;

                // Do not shrink window right edge
                info->recvNext += adv;
                info->recvWin  -= adv;

                if (0 < info->pair->poll)
                {
                    __IPWakeupPollingThreads();
                }
            }
        }
        else    // Out-of-order
        {
            // [RFC 1122 4.2.2.21]
            //    A TCP MAY send an ACK segment acknowledging RCV.NXT when a
            //    valid segment arrives that is in the window but not at the
            //    left window edge.
            //
            // Note fast retransmit and fast recovery were proposed in
            // 1990 by Jacobson, which is not an required partof RFC 1122.
            // It requires the above mentioned ACKs to be sent.
            ASSERT(TCP_SEQ_GT(info->recvNext, tcp->seq));

            // A TCP receiver SHOULD send an immediate duplicate ACK
            // when an out-of-order segment arrives. [RFC 2581 - 3.2]
            if (0 < adv)
            {
                flag |= TCP_FLAG_ACK;
            }

            // [RFC 1122] While it is not strictly required,
            // a TCP SHOULD be capable of queuing out-of-order
            // TCP segments.
            info->recvPtr = IFRingInEx(info->recvData, info->recvBuff,
                                       info->recvPtr,  info->recvUser,
                                       tcp->seq - info->recvNext, info->segBegin, &adv,
                                       info->asb, TCP_ASB);
            ASSERT(adv == 0);

            // Trun off FIN
            if (tcp->flag & TCP_FLAG_FIN)
            {
                tcp->flag &= ~TCP_FLAG_FIN;
                --info->segLen;
            }
        }

        break;
      case TCP_STATE_CLOSE_WAIT:
      case TCP_STATE_CLOSING:
      case TCP_STATE_LAST_ACK:
      case TCP_STATE_TIME_WAIT:
        // Ignore the text
        break;

    }

    // Check FIN bit
    if (tcp->flag & TCP_FLAG_FIN)
    {
        ++info->recvNext;
        flag |= TCP_FLAG_ACK;
        switch (info->state)
        {
          case TCP_STATE_SYN_RECEIVED:
            // openCallback has not been called yet. Should not be happend.
            ASSERT(info->openCallback == NULL);
            // FALL THROUGH
          case TCP_STATE_ESTABLISHED:
            info->state = TCP_STATE_CLOSE_WAIT;
            break;
          case TCP_STATE_FINWAIT1:
            // if FIN has been ACKed, has been gone to TCP_STATE_FINWAIT2
            info->state = TCP_STATE_CLOSING;
            break;
          case TCP_STATE_FINWAIT2:
            // Do not call TCPStartTimeWait() immediately as it calls TCPAbort() and
            // the received data might be lost.
            break;
        }
    }

    if (info->recvCallback)
    {
        BOOL urgent;

        result = TCPRecvOut(info, &urgent);
        if (info->recvLowat <= result ||
            (tcp->flag & TCP_FLAG_FIN) ||
            (0 < result && urgent))
        {
            callback = info->recvCallback;
            if (info->recvResult)
            {
                *info->recvResult = result;
                info->recvResult = NULL;
            }
            info->recvCallback = NULL;
            info->userData     = NULL;
            info->userLen      = 0;
            callback((TCPInfo*) info->pair, result);
        }
    }

    if (0 < info->recvUrg)
    {
        // Signal if info->recvUp is in advance of info->recvNext.
        if ((0 < info->recvUrg || (info->flag & TCP_SO_HAVE_URG)) &&
            info->urgCallback &&
            (info->flag & TCP_SO_HAD_URG) == 0)
        {
            if (info->flag & TCP_SO_HAVE_URG)
            {
                result = 1;
                if ((info->flag & TCP_SO_PEEK_URG) == 0)
                {
                    info->flag ^= (TCP_SO_HAVE_URG | TCP_SO_HAD_URG);
                }
            }
            else
            {
                result = 0;
            }
            if (info->urgResult)
            {
                *info->urgResult = result;
                info->urgResult = NULL;
            }
            if (info->urgData)
            {
                *info->urgData = info->oob;
                info->urgData = NULL;
            }
            callback = info->urgCallback;
            info->urgCallback = NULL;
            callback((TCPInfo*) info->pair, result);
        }
    }

    // Check FIN bit again for TCP_STATE_FINWAIT2
    if (tcp->flag & TCP_FLAG_FIN)
    {
        if (info->state == TCP_STATE_FINWAIT2)
        {
            // If info has been half closed, it will enter to TCP_STATE_TIME_WAIT state.
            // However the application has not called TCPClose so info must be kept
            // for a while.

            // Restart 2 MSL time-wait
            TCPStartTimeWait(info->interface, info, ip, tcp);
            return;
            // NOT REACHED HERE
        }
    }

    TCPOutput(info, flag);
}

/*---------------------------------------------------------------------------*
  Name:         TCPSendIn

  Description:  Copy-in the send data from user memory space to the send
                buffer. To override SWS avoidance, any copiable user data
                should be copied to the send buffer.

  Arguments:    info        Pointer to TCP information block
                nonblock    TRUE for nonblocking I/O

  Returns:      Number of bytes copied-in to the send buffer
 *---------------------------------------------------------------------------*/
s32 TCPSendIn(TCPObj* info, BOOL nonblock)
{
    s32  useable;
    s32  len;

    if (info->sendCallback == NULL || info->userSendLen <= 0)
    {
        return 0;
    }

    // XXX if SWS timer is active, it should be canceled...

    if (!nonblock && info->sendLen == 0 && info->sendBuff < info->userSendLen)
    {
        // Use info->userSendData as send buffer
        len = 0;
    }
    else
    {
        useable = info->sendBuff - info->sendLen;
        len = MIN(useable, info->userSendLen);
        if (nonblock && len < info->sendLowat)
        {
            return 0;
        }
    }
    if (0 < len)
    {
        info->sendPtr = IFRingIn(info->sendData, info->sendBuff,
                                 info->sendPtr,  info->sendLen,
                                 info->userSendData, len);
        info->sendLen += len;
        info->userSendData += len;
        info->userSendLen  -= len;
        info->userAcked    += len;
    }
    if (nonblock)
    {
        info->userSendData = NULL;
        info->userSendLen  = 0;
    }
    return len;
}

/*---------------------------------------------------------------------------*
  Name:         TCPPeekOut

  Description:  Copy-out received data from info->recvData to info->userData.

  Arguments:    info    Pointer to TCP information block
                ptr     Pointer to the buffer
                len     The length of the buffer
                peek
                urgent

  Returns:      Number of bytes copied-out to the user specified buffer.
 *---------------------------------------------------------------------------*/
s32 TCPPeekOut(TCPObj* info, void* ptr, s32 len, BOOL peek, BOOL* urgent)
{
    void* nextPtr;

    *urgent = FALSE;

    // Get available size
    len = MIN(len, info->recvUser);
    if (len <= 0)
    {
        return 0;
        // NOT REACHED HERE
    }

    if (0 < info->recvUrg)
    {
        if (info->recvUrg == 1)
        {
            if (info->flag & TCP_SO_OOB)
            {
                u8 oob;

                // Kill the urgent byte
                info->recvPtr = IFRingOut(info->recvData, info->recvBuff,
                                          info->recvPtr,  info->recvUser,
                                          &oob, 1);
                info->recvUser -= 1;
                info->recvUrg  -= 1;

                // Get available size again
                len = MIN(len, info->recvUser);
            }
            else
            {
                // Only read the urgent byte
                len = 1;
                *urgent = TRUE;
            }
        }
        else if (info->recvUrg <= len)
        {
            len = info->recvUrg - 1;
            *urgent = TRUE;
        }
    }

    if (0 < len)
    {
        nextPtr = IFRingOut(info->recvData, info->recvBuff,
                            info->recvPtr,  info->recvUser,
                            ptr, len);
        if (!peek)
        {
            info->recvPtr = nextPtr;
            info->recvUser -= len;
            if (0 < info->recvUrg)
            {
                info->recvUrg -= len;
            }
        }
    }
    return len;
}

s32 TCPRecvOut(TCPObj* info, BOOL* urgent)
{
    u8*  ptr;
    s32  len;
    BOOL peek = (info->flag & TCP_SO_PEEK) ? TRUE : FALSE;

    ASSERT(info->userData);
    ptr = info->userData + info->userLen;
    len = info->userBuff - info->userLen;
    len = TCPPeekOut(info, ptr, len, peek, urgent);
    if (peek)
    {
        return len;
    }
    else
    {
        return info->userLen += len;
    }
}

// ICMP error handler
void TCPNotify(const IPHeader* ip, s32 err, BOOL abort)
{
    TCPInfo*   info;
    TCPHeader* tcp;

    tcp = (TCPHeader*) ((u8*) ip + IP_HLEN(ip));

    // Lookup info reversing dst and src fields
    info = (TCPInfo*) IP4LookupInfo(&TCPInfoQueue, ip->dst, ip->src, tcp->dst, tcp->src, 0);
    if (info)
    {
        TCPObj* obj = TCPGetObj(info);

        obj->err = err;
        if (abort)
        {
            TCPAbort(obj);
        }
        else
        {
            // Trigger a "slow start" as if a retransmission timeout had occurred [RFC 1122]
            // to see if the fault is corrected in reasonable time [RFC 816].
            obj->cWin = obj->mss;
        }
    }
}

#ifdef IP_INET6
// ICMP error handler
void TCP6Notify(const IP6Hdr* ip6, const TCPHeader* tcp, s32 err, BOOL abort)
{
    TCPInfo* info;

    // Lookup info reversing dst and src fields
    info = (TCPInfo*) IP6LookupInfo(&TCPInfoQueue, &ip6->dst, &ip6->src, tcp->dst, tcp->src, 0);
    if (info)
    {
        TCPObj* obj = TCPGetObj(info);

        obj->err = err;
        if (abort)
        {
            TCPAbort(obj);
        }
        else
        {
            // Trigger a "slow start" as if a retransmission timeout had occurred [RFC 1122]
            // to see if the fault is corrected in reasonable time [RFC 816].
            obj->cWin = obj->mss;
        }
    }
}
#endif

#ifdef TCP_SACK
//
// TCP SACK functions
//

// Delete cumulatively ack'd holes.
void TCPDeleteSackHoles(TCPObj* info, TCPHeader* tcp)
{
    s32          lastAck;
    TCPSackHole* hole;
    TCPSackHole* holeEnd;

    if (!(info->flag & TCP_SO_SACK) ||
        info->state == TCP_STATE_LISTEN ||
        TCP_SEQ_GT(info->sendMax, tcp->ack))
    {
        return;
    }
    lastAck = TCP_SEQ_MAX(info->sendUna, tcp->ack);
    holeEnd = &info->scoreboard[info->sendHoles];
    for (hole = info->scoreboard; hole < holeEnd; ++hole)
    {
        if (TCP_SEQ_GT(lastAck, hole->end))
        {
            break;
        }
    }
    if (info->scoreboard < hole)
    {
        info->sendHoles = holeEnd - hole;
        memmove(info->scoreboard, hole, (size_t) ((u8*) holeEnd - (u8*) hole));
    }
    if (0 < info->sendHoles)
    {
        hole = info->scoreboard;
        if (TCP_SEQ_GT(hole->start, lastAck))
        {
            hole->start = lastAck;
            if (TCP_SEQ_GT(hole->rxmit, hole->start))
            {
                hole->rxmit = hole->start;
            }
        }
    }
}

// Update the SACK scoreboard parsing the TCP SACK option.
void TCPUpdateScoreboard(TCPObj* info, TCPHeader* tcp, u8* opt, int optlen)
{
    TCPSackHole* hole;
    TCPSackHole* holeEnd;
    s32*         edge;
    s32          start; // left edge
    s32          end;   // right edge

    ASSERT(0 < info->mss);
    ASSERT(opt[0] == TCP_OPT_SACK);

    if (!(info->flag & TCP_SO_SACK))
    {
        return;
    }
    if (optlen <= 2 || (optlen - 2) % (2 * sizeof(s32)) != 0)
    {
        return;
    }
    if (TCP_SEQ_GT(info->sendMax, tcp->ack) ||
        TCP_SEQ_GT(tcp->ack, info->sendUna))
    {
        return;
    }

    edge = (s32*) (opt + 2);
    optlen -= 2;
    while (0 < optlen)
    {
        start = *edge++;
        start = (s32) SONtoHl(start);
        end   = *edge++;
        end   = (s32) SONtoHl(end);
        optlen -= 2 * sizeof(s32);

        if (TCP_SEQ_GE(end, start))
            continue;   // bad SACK fields
        if (TCP_SEQ_GE(end, info->sendUna))
            continue;   // old block
        if (TCP_SEQ_GE(start, tcp->ack))
            continue;   // D-SACK [RFC 2883]
        if (TCP_SEQ_GT(info->sendMax, end))
            continue;   // bad SACK fields

        // Updates sendFack.
        if (TCP_SEQ_GT(info->sendFack, end))
        {
            info->sendFack = end;
        }

        if (info->sendHoles == 0)   // Scoreboard is empty.
        {
            info->sendHoles = 1;

            hole = &info->scoreboard[0];
            hole->start = tcp->ack;
            hole->end = start;
            ASSERT(TCP_SEQ_GT(hole->start, hole->end));
            hole->rxmit = hole->start;
            hole->dupAcks = MIN(TCP_RXMIT_THRESH, (end - hole->end) / info->mss);
            if (hole->dupAcks < 1)
            {
                hole->dupAcks = 1;
            }
            info->lastSack = end;
            continue;
        }

        holeEnd = &info->scoreboard[info->sendHoles];
        for (hole = info->scoreboard; hole < holeEnd; ++hole)
        {
            if (TCP_SEQ_GE(end, hole->start))           // Left side
            {
                break;
            }
            if (TCP_SEQ_GE(hole->end, start))           // Right side
            {
                ++hole->dupAcks;
                if (TCP_RXMIT_THRESH <= (end - hole->end) / info->mss)
                {
                    hole->dupAcks = TCP_RXMIT_THRESH;
                }
            }
            else if (TCP_SEQ_GE(start, hole->start))    // Left edge
            {
                info->rxmitData -= TCP_SEQ_MIN(hole->rxmit, end) - hole->start;
                if (TCP_SEQ_GE(hole->end, end))         // Cover
                {
                    memmove(hole, hole + 1, (size_t) ((u8*) holeEnd - (u8*) (hole + 1)));
                    --holeEnd;
                    --info->sendHoles;
                    --hole;
                }
                else
                {
                    hole->start = end;
                    hole->rxmit = TCP_SEQ_MAX(hole->rxmit, hole->start);
                }
            }
            else if (TCP_SEQ_GE(hole->end, end))       // Right edge
            {
                if (TCP_SEQ_GT(start, hole->rxmit))
                {
                    info->rxmitData -= hole->rxmit - start;
                }
                hole->end = start;
                hole->rxmit = TCP_SEQ_MIN(hole->rxmit, hole->end);
                ++hole->dupAcks;
                if (TCP_RXMIT_THRESH <= (end - hole->end) / info->mss)
                {
                    hole->dupAcks = TCP_RXMIT_THRESH;
                }
            }
            else                                        // In the middle
            {
                ASSERT(TCP_SEQ_GT(hole->start, start));
                ASSERT(TCP_SEQ_GT(end, hole->end));
                if (info->sendHoles < TCP_ASB)
                {
                    memmove(hole + 1, hole, (size_t) ((u8*) holeEnd - (u8*) hole));
                    ++holeEnd;
                    ++info->sendHoles;
                }
                else if (hole < holeEnd - 1)
                {
                    info->lastSack = (holeEnd - 1)->start;
                    memmove(hole + 1, hole, (size_t) ((u8*) (holeEnd - 1) - (u8*) hole));
                }
                else
                {
                    info->lastSack = end;
                }
                if (TCP_SEQ_GT(end, hole->rxmit))
                {
                    info->rxmitData -= end - start;
                }
                else if (TCP_SEQ_GT(start, hole->rxmit))
                {
                    info->rxmitData -= hole->rxmit - start;
                }
                hole->end = start;
                hole->rxmit = TCP_SEQ_MIN(hole->rxmit, hole->end);
                ++hole->dupAcks;
                if (TCP_RXMIT_THRESH <= (end - hole->end) / info->mss)
                {
                    hole->dupAcks = TCP_RXMIT_THRESH;
                }
                ++hole;
                if (hole < holeEnd)
                {
                    hole->start = end;
                    hole->rxmit = TCP_SEQ_MAX(hole->rxmit, hole->start);
                }
                // else XXX rxmitData would no longer be correct... timeout should recover this...
            }
        }
        if (TCP_SEQ_GT(info->lastSack, start))          // Append new hole at end.
        {
            if (TCP_ASB <= info->sendHoles)
            {
                continue;
            }
            hole = &info->scoreboard[info->sendHoles];
            ++info->sendHoles;
            hole->start = info->lastSack;
            hole->end = start;
            hole->dupAcks = MIN(TCP_RXMIT_THRESH, (end - start) / info->mss);
            if (hole->dupAcks < 1)
            {
                hole->dupAcks = 1;
            }
            hole->rxmit = hole->start;
            info->lastSack = end;
        }
    }

    // Update rxmitData and sendAwin.
    info->rxmitData = 0;
    holeEnd = &info->scoreboard[info->sendHoles];
    for (hole = info->scoreboard; hole < holeEnd; ++hole)
    {
        info->rxmitData += hole->rxmit - hole->start;
    }
    info->sendAwin = (info->sendNext - info->sendFack) + info->rxmitData;
}

#endif  // TCP_SACK

//
// TCP unit test functions
//

BOOL __TCPTrimSegment(TCPInfo* info, IPHeader* ip, u16* flag)
{
    TCPHeader* tcp;
    TCPObj*    obj = TCPGetObj(info);

    tcp = (TCPHeader*) ((u8*) ip + IP_HLEN(ip));
    obj->segLen = TCPGetSegmentLength(tcp, ip->len - IP_HLEN(ip));
    obj->segBegin = (u8*) tcp + TCP_HLEN(tcp);
    return TCPTrimSegment(obj, tcp, flag);
}
