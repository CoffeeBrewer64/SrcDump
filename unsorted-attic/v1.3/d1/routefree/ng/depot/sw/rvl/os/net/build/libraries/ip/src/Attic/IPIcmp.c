/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API -- ICMP
  File:     IPIcmp.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPIcmp.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    28    2/14/06 18:47 Shiki
    Revised to collect interface statistics.

    27    2/10/06 17:48 Shiki
    Modified TCPNotify() and TCP6Notify() to trigger a slow start.

    26    2/10/06 13:57 Shiki
    Implemented Reroute().

    25    1/23/06 10:21 Shiki
    Fixed MSS management of IPv6.

    24    1/06/06 17:44 Shiki
    Revised ICMP packet buffer management code.

    23    06/01/06 14:01 Ueno_kyu
    Fixed SelectDatagramBuffer() to set datagram type.

    22    06/01/06 13:27 Ueno_kyu
    Modified to save ICMP datagram.

    21    12/13/05 19:58 Shiki
    Revised to support default TTL for RFC 3927 (1 for link-local, IP_TTL
    for others).

    20    12/09/05 15:49 Shiki
    Added note from RFC 3390.

    19    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    25    04/09/28 18:36 Ueno_kyu
    Modified ICMPCancel() to cancel a datagram.

    24    04/09/28 16:45 Ueno_kyu
    Revised IPv6 ping program.

    23    04/09/28 14:55 Ueno_kyu
    Revised IPv4 ping program.

    22    04/09/24 11:19 Ueno_kyu
    Added support for IPv6 ping program.

    21    04/09/22 10:25 Ueno_kyu
    Added support for ping over IPv4.

    20    6/29/04 9:33 Shiki
    Revised using IP_TTL.

    19    6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    17    3/03/04 14:28 Shiki
    Modified to use a TCP initial cwnd of 2 segments as allowed in RFC
    2581.

    16    10/29/03 21:58 Shiki
    Revised using IFInitDatagram().

    15    5/15/03 15:54 Shiki
    Modified to clear the IF_DATAGRAM_FLAG_DROP bit in IFDatagram.flag
    before sending a Ethernet packet.

    14    5/07/03 14:11 Shiki
    Fixed packet length test code in ICMPSendError().

    13    5/07/03 13:26 Shiki
    Revised ICMPIn() to check input ICMP messages more strictly.

    12    02/07/01 13:31 Shiki
    Fixed DoEchoRequest() and ICMPSendError() so that they allocate the
    datagram memory by a single call to interface->alloc to cooperate with
    IFFifo component.

    11    4/18/02 18:33 Shiki
    Fixed typo in IP_ERR_INS_RESOURCES.

    10    4/17/02 20:15 Shiki
    Defined IP_ERR_SOURCE_QUENCH.

    9     4/12/02 13:29 Shiki
    Fixed DoEchoRequest() and ICMPSendError() to release fifo memory block
    upon IPOut() failure, and not to send the response if the host
    addresses have not been configured.

    8     4/04/02 17:17 Shiki
    Implemented ICMPSendError().

    7     3/27/02 20:46 Shiki
    Added comment.

    6     3/27/02 16:51 Shiki
    Modified to pass ICMP_SOURCE_QUENCH, ICMP_TIME_EXCEEDED and
    ICMP_PARAMETER_PROBLEM to higher layer.

    5     3/25/02 17:09 Shiki
    Modified to process IP options for ECHO reply.

    4     3/18/02 14:30 Shiki
    Minor clean up.

    3     3/13/02 9:14 Shiki
    Clean up with IP_ALEN and ETH_ALEN.

    2     3/11/02 20:21 Shiki
    Fixed to initialize datagram->queue before IPOut().

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*
    [RFC 1122]

    Every ICMP error message includes the Internet header and at
    least the first 8 data octets of the datagram that triggered
    the error; more than 8 octets MAY be sent; this header and data
    MUST be unchanged from the received datagram.
 */

#include <dolphin/os.h>
#include <dolphin/ip.h>
#include <dolphin/socket.h>
#include "IPPrivate.h"
#ifdef IP_INET6
#include "IP6Private.h"
#endif // IP_INET6

static void DoNotify(const IPHeader* org, s32 err, BOOL abort);
static void ICMPNotify(const IPHeader* org, s32 err);
static void DoEchoReply(IPInterface* interface, IPHeader* ip, u32 flag);

IFQueue ICMPInfoQueue;

// A node must be able to accept a fragmented packet that, after
// reassembly, is as large as 1500 octets. [RFC2460]
#define IP_MAX_REASSEMBLED_SIZE    1500
#define ICMP_MAX_WAITING_PACKET    2

typedef struct DatagramBuffer
{
    u8  datagram[sizeof(IFDatagram) + IP_MAX_REASSEMBLED_SIZE];
    s32 len;
} DatagramBuffer;

static DatagramBuffer  ICMPBuffer[ICMP_MAX_WAITING_PACKET];

// Returns ICMP error message header size. Returns zero
// if the type is not an ICMP error.
static int ICMPIsErrorMessage(u8 type)
{
    switch (type)
    {
      case ICMP_UNREACHABLE:
        return sizeof(ICMPUnreachable);
        break;
      case ICMP_SOURCE_QUENCH:
        return sizeof(ICMPSourceQuench);
        break;
      case ICMP_REDIRECT:
        return sizeof(ICMPRedirect);
        break;
      case ICMP_TIME_EXCEEDED:
        return sizeof(ICMPTimeExceeded);
        break;
      case ICMP_PARAMETER_PROBLEM:
        return sizeof(ICMPParameterProblem);
        break;
    }
    return 0;
}

static u16 ICMPCheckSum(ICMPHeader* icmp, int len)
{
    u32  sum = 0;
    u16* p;

    p = (u16*) icmp;
    while (1 < len)
    {
        sum += *p++;
        len -= 2;
    }
    if (len == 1)
    {
        sum += (*(u8*) p) << 8;
    }
    sum = (sum & 0xffff) + (sum >> 16);
    sum = (sum & 0xffff) + (sum >> 16);
    return (u16) (sum ^ 0xffff);
}

static void DoEchoRequest(IPInterface* interface, IPHeader* ip, u32 flag)
{
    IFDatagram* datagram;
    IPHeader*   res;
    ICMPHeader* icmp;
    void*       data;

    // See local host addresses have been configured.
    if (ip->dst[0] != 127 &&
        IP_ADDR_NE(ip->dst, interface->addr) &&
        IP_ADDR_NE(ip->dst, interface->alias))
    {
        return;
    }

    if (flag & (IF_FLAG_BROADCAST | IF_FLAG_MULTICAST))
    {
        return;
    }

    // [MAY] Discard echo request to broadcast or multicast address [RFC 1122]
    if (IPIsBroadcastAddr(interface, ip->src) ||
        IP_CLASSD(ip->src) || IP_CLASSE(ip->src))
    {
        return;
    }

    ++interface->icmpStat.outMsgs;
    datagram = ICMPAllocDatagram(interface, ip->len);
    if (datagram == NULL)
    {
        ++interface->icmpStat.outErrors;
        return;
    }
    IFInitDatagram(datagram, ETH_IP, 1);
    datagram->vec[0].data = data = (u8*) datagram + sizeof(IFDatagram);
    datagram->vec[0].len  = ip->len;

    // Form ICMP echo replay
    res = (IPHeader*) datagram->vec[0].data;
    memmove(res, ip, (u32) IP_HLEN(ip));
    memmove(res->src, ip->dst, IP_ALEN);
    memmove(res->dst, ip->src, IP_ALEN);
    res->tos = 0;       // [RFC 1122]
    res->ttl = (u8) (IPIsLinkLocalAddr(interface, res->src) ? 1 : IP_TTL);

    // Process IP options
    if (IP_MIN_HLEN < IP_HLEN(res))
    {
        // Record Route
        IPUpdateRecordRoute(res, res->src);

        // Source Route
        IPReverseSourceRoute(res);
    }

    icmp = (ICMPHeader*) ((u8*) res + IP_HLEN(res));
    memmove(icmp, (u8*) ip + IP_HLEN(ip), (u32) (ip->len - IP_HLEN(ip)));
    icmp->type = ICMP_ECHO_REPLY;
    icmp->sum = 0;
    icmp->sum = ICMPCheckSum(icmp, res->len - IP_HLEN(res));

    if (IPOut(datagram) < 0)
    {
        // datagram has not been sent out. Must release memory
        ICMPFreeDatagram(datagram);
        interface->free(interface, datagram, (s32) sizeof(IFDatagram) + ip->len);
    }
    else
    {
        ++interface->icmpStat.outEchoReps;
    }
}

// Reduce estimate of the PMTU
static u16 ReduceMtu(s32 mtu)
{
    if (1492 < mtu)
    {
        return 1006;
    }
    if (1006 < mtu)
    {
        return 508;
    }
    return 68;  // Official minimum MTU [RFC 791]
}

// Note do not abort TCP connection due to this error.
static void DoUnreachable(IPInterface* interface, IPHeader* ip, u32 flag)
{
#ifdef IOP_OS
    TCPIP_UNUSED(flag);
#else
    #pragma unused(flag)
#endif // IOP_OS
    
    ICMPUnreachable* icmp;
    IPHeader* org;
    u16     mtu;
    IPInfo* info;
    IPInfo* next;

    icmp = (ICMPUnreachable*) ((u8*) ip + IP_HLEN(ip));
    org  = (IPHeader*) ((u8*) icmp + sizeof(ICMPUnreachable));
    switch (icmp->code)
    {
      case ICMP_UNREACHABLE_NEED_FRAGMENT:
        // RFC 1191
        // Any packetization layer instance (for example, a TCP
        // connection) that is actively using the path must be notified if the
        // PMTU estimate is decreased.
        if (0 < icmp->mtu)
        {
            mtu = (u16) MAX(68, icmp->mtu);
        }
        else
        {
            mtu = ReduceMtu(MIN(interface->mtu, org->len));
        }
Again:
        mtu = (u16) MIN(interface->mtu, mtu);
        IFIterateQueue(IPInfo*, &TCPInfoQueue, info, next, link)
        {
            TCPObj* tcp;

            // If too big message is received, all connections using
            // the given path must reduce its PMTU.
            if (IP_ADDR_NE(((IPSocket*) IPGetRemoteSockAddr(info))->addr, org->dst))
            {
                continue;
            }

            tcp = TCPGetObj((TCPInfo*) info);
            if (tcp->mss < mtu - IP_MIN_HLEN - TCP_MIN_HLEN)
            {
                mtu = ReduceMtu(tcp->mss + IP_MIN_HLEN + TCP_MIN_HLEN);
                goto Again;
            }
            tcp->mss = mtu - IP_MIN_HLEN - TCP_MIN_HLEN;

            // Goes back to slow start without changing slow start threshold
            // like source quench
            //
            // Specifically, `cwnd' SHOULD be reduced by the ratio of the
            // old segment size to the new segment size. [RFC 3390]
            tcp->cWin = TCP_IW(tcp);
        }

        if (org->proto == IP_PROTO_TCP)
        {
            break;
        }

        DoNotify(org, IP_ERR_UNREACHABLE, FALSE);
        break;

      // Soft error condition
      //
      // A Destination Unreachable message that is received with code
      // 0 (Net), 1 (Host), or 5 (Bad Source Route) may result from a
      // routing transient and MUST therefore be interpreted as only
      // a hint, not proof, that the specified destination is
      // unreachable [IP:11].  For example, it MUST NOT be used as
      // proof of a dead gateway (see Section 3.3.1). [RFC 1122]
      case ICMP_UNREACHABLE_NET:        // 0
      case ICMP_UNREACHABLE_HOST:       // 1
      case ICMP_UNREACHABLE_SRC_FAIL:   // 5
        // Since these Unreachable messages indicate soft error
        // conditions, TCP MUST NOT abort the connection, and it
        // SHOULD make the information available to the
        // application.

      case ICMP_UNREACHABLE_NET_UNKNOWN:
      case ICMP_UNREACHABLE_NET_PROHIBITED:
      case ICMP_UNREACHABLE_NET_TOS:

      case ICMP_UNREACHABLE_HOST_UNKNOWN:
      case ICMP_UNREACHABLE_ISOLATED:
      case ICMP_UNREACHABLE_HOST_PROHIBITED:
      case ICMP_UNREACHABLE_HOST_TOS:

      case ICMP_UNREACHABLE_PROHIBITED: case 14: case 15:
        DoNotify(org, IP_ERR_UNREACHABLE, FALSE);
        break;

      // Hard error condition
      case ICMP_UNREACHABLE_PROTOCOL:   // 4
      case ICMP_UNREACHABLE_PORT:       // 2
        // These are hard error conditions, so TCP SHOULD abort
        // the connection. [RFC 1122|
        DoNotify(org, IP_ERR_UNREACHABLE, TRUE);
        break;
    }
}

static BOOL DoRedirect(IPInterface* interface, IPHeader* ip, u32 flag)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
    TCPIP_UNUSED(flag);
#else
    #pragma unused(interface)
    #pragma unused(flag)
#endif // IOP_OS
    
    ICMPRedirect* icmp;
    IPHeader* org;

    icmp = (ICMPRedirect*) ((u8*) ip + IP_HLEN(ip));
    org  = (IPHeader*) ((u8*) icmp + sizeof(ICMPRedirect));
    if (ICMP_REDIRECT_TOSHOST < icmp->code)
    {
        return FALSE;
    }

    // [RFC1122] Since the subnet mask appropriate to the destination
    // address is generally not known, a Network Redirect message
    // SHOULD be treated identically to a Host Redirect message
    return IPRedirect(org->dst, icmp->gateway, ip->src);
}

static void DoSourceQuench(const IPHeader* org)
{
    switch (org->proto)
    {
      case IP_PROTO_UDP:
        UDPNotify(org, IP_ERR_SOURCE_QUENCH);
        break;
      case IP_PROTO_TCP:
        TCPNotify(org, IP_ERR_NONE, FALSE);
        break;
    }
}

static void DoNotify(const IPHeader* org, s32 err, BOOL abort)
{
    switch (org->proto)
    {
      case IP_PROTO_UDP:
        UDPNotify(org, err);
        break;
      case IP_PROTO_TCP:
        TCPNotify(org, err, abort);
        break;
      case IP_PROTO_ICMP:
        ICMPNotify(org, err);
        break;
    }
}

// Compute internet header checksums
void ICMPIn(IPInterface* interface, IPHeader* ip, u32 flag)
{
#ifdef IOP_OS
    TCPIP_UNUSED(flag);
#else
    #pragma unused(flag)
#endif // IOP_OS
    
    ICMPHeader* icmp;
    IPHeader* org;
    int hlen;

    ASSERT(ip->proto == IP_PROTO_ICMP);
    ++interface->icmpStat.inMsgs;
    icmp = (ICMPHeader*) ((u8*) ip + IP_HLEN(ip));
    if (ip->len < IP_HLEN(ip) + ICMP_MIN_HLEN ||
        ICMPCheckSum(icmp, ip->len - IP_HLEN(ip)) != 0)
    {
        ++interface->icmpStat.inErrors;
        return;
    }

    // [RFC 1122]
    //
    //   An ICMP error message MUST NOT be sent as the result of
    //   receiving:
    //
    //   *    an ICMP error message, or
    //   *    a datagram destined to an IP broadcast or IP multicast
    //        address, or
    //   *    a datagram sent as a link-layer broadcast, or
    //   *    a non-initial fragment, or
    //   *    a datagram whose source address does not define a single
    //        host -- e.g., a zero address, a loopback address, a
    //        broadcast address, a multicast address, or a Class E
    //        address.
    hlen = ICMPIsErrorMessage(icmp->type);
    if (0 < hlen)
    {
        org  = (IPHeader*) ((u8*) icmp + hlen);
        if (ip->len < IP_HLEN(ip) + hlen + IP_MIN_HLEN + 8)
        {
            ++interface->icmpStat.inErrors;
            return;
        }
        if (IP_HLEN(org) < IP_MIN_HLEN)
        {
            ++interface->icmpStat.inErrors;
            return;
        }
        if (ip->len < IP_HLEN(ip) + hlen + IP_HLEN(org) + 8)
        {
            ++interface->icmpStat.inErrors;
            return;
        }
        if (org->proto == IP_PROTO_ICMP)
        {
            ++interface->icmpStat.inErrors;
            return;
        }
        // Although ICMP should not be generated for a broadcast address,
        // there are routers that do this!
        if (IPIsBroadcastAddr(interface, org->dst) ||
            IP_CLASSD(org->dst) || IP_CLASSE(org->dst))
        {
            ++interface->icmpStat.inErrors;
            return;
        }
        if (flag & (IF_FLAG_BROADCAST | IF_FLAG_MULTICAST))
        {
            ++interface->icmpStat.inErrors;
            return;
        }
        if (IP_FRAG(org) != 0)
        {
            ++interface->icmpStat.inErrors;
            return;
        }
        if (org->src[0] == 127 ||
            IPIsBroadcastAddr(interface, org->src) ||
            IP_CLASSD(org->src) || IP_CLASSE(org->src))
        {
            ++interface->icmpStat.inErrors;
            return;
        }
    }
    else
    {
        org = NULL;
    }

    //
    // Process ICMP message
    //
    switch (icmp->type)
    {
      case ICMP_ECHO_REPLY:
        ++interface->icmpStat.inEchoReps;
        DoEchoReply(interface, ip, flag);
        break;

      case ICMP_UNREACHABLE:
        ++interface->icmpStat.inDestUnreachs;
        DoUnreachable(interface, ip, flag);
        break;

      case ICMP_SOURCE_QUENCH:
        // TCP MUST react to a Source Quench by slowing
        // transmission on the connection.  The RECOMMENDED
        // procedure is for a Source Quench to trigger a "slow
        // start," as if a retransmission timeout had occurred. [RFC 1122]
        ++interface->icmpStat.inSrcQuenchs;
        DoSourceQuench(org);
        break;

      case ICMP_ECHO_REQUEST:
        ++interface->icmpStat.inEchos;
        DoEchoRequest(interface, ip, flag);
        break;

      case ICMP_REDIRECT:
        ++interface->icmpStat.inRedirects;
        DoRedirect(interface, ip, flag);
        break;

      case ICMP_TIME_EXCEEDED:
        // This should be handled the same way as Destination
        // Unreachable codes 0, 1, 5 [RFC 1122]
        ++interface->icmpStat.inTimeExcds;
        DoNotify(org, IP_ERR_TIMEOUT, FALSE);  // XXX define error code
        break;

      case ICMP_PARAMETER_PROBLEM:
        // This should be handled the same way as Destination
        // Unreachable codes 0, 1, 5 [RFC 1122]
        ++interface->icmpStat.inParmProbs;
        DoNotify(org, IP_ERR_INVALID, FALSE);  // XXX define error code
        break;

      case ICMP_TIMESTAMP_REQUEST:
        ++interface->icmpStat.inTimestamps;
        break;
      case ICMP_TIMESTAMP_REPLY:
        ++interface->icmpStat.inTimestampReps;
        break;
      case ICMP_ADDRESS_MASK_REQUEST:
        ++interface->icmpStat.inAddrMasks;
        break;
      case ICMP_ADDRESS_MASK_REPLY:
        ++interface->icmpStat.inAddrMaskReps;
        break;
      default:
        // Discard the packet
        break;
    }
}

// Send an ICMP error message
s32 ICMPSendError(ICMPHeader* icmp, IPInterface* interface, IPHeader* ip, u32 flag)
{
    IFDatagram* datagram;
    IPHeader*   res;
    s32         len;
    s32         rc;
    void*       data;
    u8          type;

    if (icmp == NULL || !ICMPIsErrorMessage(icmp->type) ||
        ip == NULL || IP_HLEN(ip) < IP_MIN_HLEN || ip->len < IP_HLEN(ip) + 8 ||
#ifdef IOP_OS
        (IP_ADDR_NE(ip->dst, interface->addr) && IP_ADDR_NE(ip->dst, interface->alias)))
#else
        IP_ADDR_NE(ip->dst, interface->addr) && IP_ADDR_NE(ip->dst, interface->alias))
#endif // IOP_OS
    {
        return IP_ERR_INVALID;
    }
    type = icmp->type;

    // [RFC 1122]
    //
    //   An ICMP error message MUST NOT be sent as the result of
    //   receiving:
    //
    //   *    an ICMP error message, or
    //   *    a datagram destined to an IP broadcast or IP multicast
    //        address, or
    //   *    a datagram sent as a link-layer broadcast, or
    //   *    a non-initial fragment, or
    //   *    a datagram whose source address does not define a single
    //        host -- e.g., a zero address, a loopback address, a
    //        broadcast address, a multicast address, or a Class E
    //        address.
    if (ip->proto == IP_PROTO_ICMP)
    {
        ICMPHeader* icmpRcvd = (ICMPHeader*) ((u8*) ip + IP_HLEN(ip));
        if (ICMPIsErrorMessage(icmpRcvd->type))
        {
            return IP_ERR_REFUSED;
        }
    }

    if (IPIsBroadcastAddr(interface, ip->dst) ||
        IP_CLASSD(ip->dst) || IP_CLASSE(ip->dst))
    {
        return IP_ERR_REFUSED;
    }

    if (flag & (IF_FLAG_BROADCAST | IF_FLAG_MULTICAST))
    {
        return IP_ERR_REFUSED;
    }

    if (IP_FRAG(ip) != 0)
    {
        return IP_ERR_REFUSED;
    }

    if (ip->src[0] == 127 ||
        IPIsBroadcastAddr(interface, ip->src) ||
        IP_CLASSD(ip->src) || IP_CLASSE(ip->src))
    {
        return IP_ERR_REFUSED;
    }

    //
    // Form ICMP error message
    //
    ++interface->icmpStat.outMsgs;

    interface = IPGetRoute(ip->src, NULL);
    if (interface == NULL)
    {
        ++interface->ipStat.outNoRoutes;
        return IP_ERR_UNREACHABLE;
    }

    len = IP_MIN_HLEN + ICMP_HLEN + IP_HLEN(ip) + 8;
    datagram = ICMPAllocDatagram(interface, len);
    if (datagram == NULL)
    {
        ++interface->icmpStat.outErrors;
        return IP_ERR_INS_RESOURCES;
    }
    IFInitDatagram(datagram, ETH_IP, 1);
    datagram->vec[0].data = data = (u8*) datagram + sizeof(IFDatagram);
    datagram->vec[0].len  = len;

    res = (IPHeader*) datagram->vec[0].data;
    res->verlen = IP_VERHLEN;
    res->tos    = 0;       // [RFC 1122 SHOULD]
    res->len    = (u16) len;
    res->frag   = 0;
    res->ttl    = (u8) (IPIsLinkLocalAddr(interface, ip->dst) ? 1 : IP_TTL);
    res->proto  = IP_PROTO_ICMP;
    memmove(res->src, ip->dst, IP_ALEN);
    memmove(res->dst, ip->src, IP_ALEN);
    memmove((u8*) res + IP_MIN_HLEN, icmp, ICMP_HLEN);
    memmove((u8*) res + IP_MIN_HLEN + ICMP_HLEN, ip, (u8) (IP_HLEN(ip) + 8));
    icmp = (ICMPHeader*) ((u8*) res + IP_MIN_HLEN);
    icmp->sum = 0;
    icmp->sum = ICMPCheckSum(icmp, res->len - IP_HLEN(res));

    rc = IPOut(datagram);
    if (rc < 0)
    {
        ICMPFreeDatagram(datagram);
        interface->free(interface, datagram, (s32) sizeof(IFDatagram) + len);
    }
    else
    {
        switch (type)
        {
          case ICMP_UNREACHABLE:
            ++interface->icmpStat.outDestUnreachs;
            break;
          case ICMP_SOURCE_QUENCH:
            ++interface->icmpStat.outSrcQuenchs;
            break;
          case ICMP_REDIRECT:
            ++interface->icmpStat.outRedirects;
            break;
          case ICMP_TIME_EXCEEDED:
            ++interface->icmpStat.outTimeExcds;
            break;
          case ICMP_PARAMETER_PROBLEM:
            ++interface->icmpStat.outParmProbs;
            break;
        }
    }
    return rc;
}
//
// Simple Ping API
//
// XXX ICMPInfo is not automatically closed upon SOCleanup().
//

ICMPObj* ICMPGetObj(ICMPInfo* info)
{
    switch (info->info.family)
    {
      case SO_PF_INET:
        return &info->obj;
#ifdef IP_INET6
      case SO_PF_INET6:
        return &((ICMP6Info*) info)->obj;
#endif  // IP_INET6
      default:
        return NULL;
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

s32 ICMPSocket(int af, ICMPInfo* info)
{
    IPSocket*  local;
    IPSocket*  remote;
    ICMPObj*   obj;
    BOOL       enabled;
    BOOL       used;

#ifdef IP_INET6
    if (info == NULL || (af != SO_AF_INET && af != SO_AF_INET6))
#else
    if (info == NULL || af != SO_AF_INET)
#endif
    {
        return IP_ERR_INVALID;
    }

    enabled = OSDisableInterrupts();
    used = __IPIsMember(&ICMPInfoQueue, &info->info);
    OSRestoreInterrupts(enabled);
    if (used)
    {
        return IP_ERR_EXIST;
    }

    switch(af)
    {
      case SO_PF_INET:
        memset(info, 0, sizeof(ICMPInfo));
        info->info.family = (u8) af;
        info->info.proto = IP_PROTO_ICMP;

        local = IPGetLocalSockAddr(&info->info);
        remote = IPGetRemoteSockAddr(&info->info);
        local->len = remote->len = IP_SOCKLEN;
        local->family = remote->family = (u8) af;
        break;
#ifdef IP_INET6
    case SO_PF_INET6:
        memset(info, 0, sizeof(ICMP6Info));
        info->info.family = (u8) af;
        info->info.proto = SO_IPPROTO_ICMPV6;

        info->info.family = (u8) af;
        local = IPGetLocalSockAddr(&info->info);
        remote = IPGetRemoteSockAddr(&info->info);
        local->len = remote->len = sizeof(SOSockAddrIn6);
        local->family = remote->family = (u8) af;
        break;
#endif // IP_INET6
    }

    // Initialize info and enqueue it
    info->info.tos = 0;         // Default
    info->info.ttl = IP_TTL;    // The current recommended default time to live (TTL) for
                                // the Internet Protocol (IP) is 64 [RFC791, RFC1122].
    info->info.mttl = 1;        // Default

    info->info.poll = 0;
    info->info.flag = IP_INFO_FLAG_MCASTLOOP;

    obj = ICMPGetObj(info);

    enabled = OSDisableInterrupts();
    IFEnqueueTail(IPInfo*, &ICMPInfoQueue, &info->info, link);
    OSRestoreInterrupts(enabled);

    return IP_ERR_NONE;
}

static s32 ICMP4Ping(ICMPInfo* info, const void* data, s32 len,
             const void* remote, ICMPCallback callback, s32* result)
{
    const IPSocket* remoteAddr = remote;
    IPInterface*    interface;
    IPHeader*       req;
    ICMPEcho*       icmp;
    BOOL            enabled;
    IFDatagram*     datagram;
    s32             rc;
    ICMPObj*        obj;

    if (!callback)
    {
        callback = NullCallback;
    }

    enabled = OSDisableInterrupts();

    ++__IFDefault.icmpStat.outMsgs;

    if (info->info.proto != IP_PROTO_ICMP)
    {
        rc = IP_ERR_INVALID;
        goto Error;
    }

    obj = ICMPGetObj(info);
    if (obj->callback)
    {
        rc =  IP_ERR_BUSY;
        goto Error;
    }

    if (65536 - IP_MIN_HLEN - sizeof(ICMPEcho) < len)
    {
        rc = IP_ERR_DATASIZE;
        goto Error;
    }
    interface = IPGetRoute(remoteAddr->addr, NULL);
    if (interface == NULL)
    {
        rc = IP_ERR_UNREACHABLE;
        goto Error;
    }
    if (IPIsBroadcastAddr(interface, remoteAddr->addr) ||
        IP_CLASSD(remoteAddr->addr) || IP_CLASSE(remoteAddr->addr))
    {
        rc =  IP_ERR_REFUSED;
        goto Error;
    }

    info->local.port = info->remote.port = remoteAddr->port;  // XXX check dup.

    IP4SelectSourceAddress(interface, remoteAddr->addr, info->local.addr);

    memmove(info->remote.addr, remoteAddr->addr, IP_ALEN);

    //
    // Form ICMP echo request message
    //
    datagram = &obj->datagram;
    IFInitDatagram(datagram, ETH_IP, 2);
    datagram->vec[0].data = obj->header;
    datagram->vec[0].len = (s32) (IP_MIN_HLEN + sizeof(ICMPEcho));
    datagram->vec[1].data = (void*) data;
    datagram->vec[1].len = len;

    obj->data = data;
    obj->len = len;
    obj->callback = callback;
    obj->result = result;
    ++obj->seq;

    req = (IPHeader*) datagram->vec[0].data;
    req->verlen = IP_VERHLEN;
    req->tos    = 0;       // [RFC 1122 SHOULD]
    req->len    = (u16) (IP_MIN_HLEN + sizeof(ICMPEcho) + len);
    req->frag   = 0;
    req->ttl    = (u8) (IPIsLinkLocalAddr(interface, info->local.addr) ? 1 : info->info.ttl);
    req->proto  = IP_PROTO_ICMP;
    memmove(req->src, info->local.addr,  IP_ALEN);
    memmove(req->dst, info->remote.addr, IP_ALEN);
    icmp = (ICMPEcho*) ((u8*) req + IP_MIN_HLEN);
    icmp->type = ICMP_ECHO_REQUEST;
    icmp->code = 0;
    icmp->sum = 0;
    icmp->id = remoteAddr->port;
    icmp->seq = obj->seq;
    icmp->sum = IP4CheckSum(IP_PROTO_ICMP, datagram->vec, 2);

    if (result)
    {
        *result = IP_ERR_BUSY;
    }
    rc = IPOut(datagram);
    if (rc < 0)
    {
        obj->callback = NULL;
        goto Error;
    }
    else
    {
        ++__IFDefault.icmpStat.outEchos;
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

s32 ICMPPing(ICMPInfo* info, const void* data, s32 len,
             const void* remote, ICMPCallback callback, s32* result)
{
#ifdef IP_INET6
    if (info->info.proto == SO_IPPROTO_ICMPV6)
    {
        return ICMP6Ping((ICMP6Info*) info, data, len, remote, callback, result);
    }
#endif // IP_INET6

    return ICMP4Ping(info, data, len, remote, callback, result);
}

s32 ICMPCancel(ICMPInfo* info, s32 err)
{
    BOOL enabled;
    ICMPObj* obj;

#ifdef IP_INET6
    if (info->info.proto != IP_PROTO_ICMP &&
        info->info.proto != SO_IPPROTO_ICMPV6)
    {
        return IP_ERR_INVALID;
    }
#else  // IP_INET6
    if (info->info.proto != IP_PROTO_ICMP)
    {
        return IP_ERR_INVALID;
    }
#endif // IP_INET6

    enabled = OSDisableInterrupts();
    obj = ICMPGetObj(info);

    // Cancel datagram.
    if (obj->datagram.queue)
    {
        switch (info->info.proto)
        {
#ifdef IP_INET6
          case SO_IPPROTO_ICMPV6:
            IP6Cancel(&obj->datagram);
            obj->datagram.queue = NULL;
            break;
#endif // IP_INET6
          case IP_PROTO_ICMP:
            IPCancel(&obj->datagram);
            obj->datagram.queue = NULL;
            break;
        }
    }

    if (obj->callback)
    {
        ICMPCallback callback = obj->callback;

        if (obj->result)
        {
            *obj->result = err;
        }
        obj->callback = NULL;
        callback(info, err);
    }
    OSRestoreInterrupts(enabled);
    return IP_ERR_NONE;
}

s32 ICMPClose(ICMPInfo* info)
{
    BOOL enabled;
    ICMPObj* obj;

#ifdef IP_INET6
    if (info->info.proto != SO_IPPROTO_ICMPV6 &&
        info->info.proto != IP_PROTO_ICMP)
    {
        return IP_ERR_INVALID;
    }
#else // IP_INET6
    if (info->info.proto != IP_PROTO_ICMP)
    {
        return IP_ERR_INVALID;
    }
#endif // IP_INET6
    enabled = OSDisableInterrupts();
    IFDequeueItem(IPInfo*, &ICMPInfoQueue, &info->info, link);

    obj = ICMPGetObj(info);
    if (obj->callback)
    {
        ICMPCallback callback = obj->callback;

        if (obj->result)
        {
            *obj->result = IP_ERR_CLOSING;
        }
        obj->callback = NULL;
        callback(info, IP_ERR_CLOSING);
    }
    info->info.proto = 0;
    OSRestoreInterrupts(enabled);
    return IP_ERR_NONE;
}

static void DoEchoReply(IPInterface* interface, IPHeader* ip, u32 flag)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
    TCPIP_UNUSED(flag);
#else
    #pragma unused( interface, flag )
#endif // IOP_OS
    
    ICMPEcho*    icmp;
    void*        data;
    IPInfo*      curr;
    IPInfo*      next;
    ICMPInfo*    info;
    ICMPCallback callback;
    ICMPObj*     obj;

    icmp = (ICMPEcho*) ((u8*) ip + IP_HLEN(ip));
    data = (void*) ((u8*) icmp + sizeof(ICMPEcho));

    IFIterateQueue(IPInfo*, &ICMPInfoQueue, curr, next, link)
    {
        info = (ICMPInfo*) curr;

#ifdef IP_INET6
        if (info->info.family != SO_PF_INET)
        {
            continue;
        }
#endif // IP_INET6

        obj  = ICMPGetObj(info);
        if (obj->callback == NULL)
        {
            continue;
        }
        if (obj->seq != icmp->seq ||
            info->local.port != icmp->id)
        {
            continue;
        }
        if (IP_ADDR_NE(ip->src, info->remote.addr) ||
            IP_ADDR_NE(ip->dst, info->local.addr))
        {
            continue;
        }

        callback = obj->callback;
        if (callback &&
            ip->len - ((u8*) icmp + sizeof(ICMPEcho) - (u8*) ip) == obj->len &&
            memcmp(data, obj->data, (size_t) obj->len) == 0)
        {
            obj->callback = NULL;
            if (obj->result)
            {
                *obj->result = IP_ERR_NONE;
            }
            callback(info, IP_ERR_NONE);
        }
    }
}

static void ICMPNotify(const IPHeader* org, s32 err)
{
    ICMPEcho*    icmp;
    IPInfo*      curr;
    IPInfo*      next;
    ICMPInfo*    info;
    ICMPCallback callback;
    ICMPObj*     obj;

    icmp = (ICMPEcho*) ((u8*) org + IP_HLEN(org));
    if (icmp->type != ICMP_ECHO_REQUEST)
    {
        return;
    }
    IFIterateQueue(IPInfo*, &ICMPInfoQueue, curr, next, link)
    {
        info = (ICMPInfo*) curr;
        obj  = ICMPGetObj(info);
        if (obj->callback == NULL)
        {
            continue;
        }
        if (obj->seq != icmp->seq ||
            info->local.port != icmp->id)
        {
            continue;
        }
        if (IP_ADDR_NE(org->src, info->local.addr) ||
            IP_ADDR_NE(org->dst, info->remote.addr))
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
            callback(info, err);
        }
    }
}

BOOL ICMPReset(BOOL final)
{
#ifdef IOP_OS
    TCPIP_UNUSED(final);
#else
    #pragma unused( final )
#endif // IOP_OS
    
    ICMPInfo* info;
    IPInfo*   curr;
    IPInfo*   next;
    BOOL      enabled;

    enabled = OSDisableInterrupts();
    if (IFIsEmptyQueue(&ICMPInfoQueue))
    {
        OSRestoreInterrupts(enabled);
        return TRUE;
    }
    IFIterateQueue(IPInfo*, &ICMPInfoQueue, curr, next, link)
    {
        info = (ICMPInfo*) curr;
        ICMPCancel(info, IP_ERR_NETDOWN);
    }
    while (!IFIsEmptyQueue(&ICMPInfoQueue))
    {
        info = (ICMPInfo*) IFQueryQueueHead(&ICMPInfoQueue);
        ICMPClose(info);
    }
    OSRestoreInterrupts(enabled);
    return FALSE;
}

IFDatagram* ICMPAllocDatagram(IPInterface* interface, s32 len)
{
    int i;

    ASSERT(0 < len);
    if (len <= IP_MAX_REASSEMBLED_SIZE)
    {
        for (i = 0; i < ICMP_MAX_WAITING_PACKET; ++i)
        {
            DatagramBuffer* buffer = &ICMPBuffer[i];
            if (buffer->len == 0)
            {
                buffer->len = len;
                return (IFDatagram*) buffer->datagram;
            }
        }
    }
    return interface->alloc(interface, (s32) sizeof(IFDatagram) + len);
}

void ICMPFreeDatagram(IFDatagram* datagram)
{
    int i;

    for (i = 0; i < ICMP_MAX_WAITING_PACKET; ++i)
    {
        DatagramBuffer* buffer = &ICMPBuffer[i];
        if (datagram == (IFDatagram*) buffer->datagram)
        {
            ASSERT(0 < buffer->len);
            buffer->len = 0;
            return;
        }
    }
}
