d1 2046
a2046 2011
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPUdp.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip6/src/IPUdp.c $
    
    51    2/27/06 15:07 Shiki
    Modified to count UDPNumber and UDP6Number.

    50    2/20/06 17:43 Shiki
    Added UDPDumpHeader().

    49    2/15/06 14:45 Shiki
    Added UDPReport and UDP6Report.

    48    2/14/06 18:47 Shiki
    Revised to collect interface statistics.

    47    2/01/06 16:25 Shiki
    Added full support of IPv6 PMTU discovery.

    46    1/26/06 11:30 Shiki
    Modified to support PMTU.

    45    1/13/06 13:02 Shiki
    Revised ICMP6SendError() to check received packet before sending an
    error message.

    44    12/13/05 19:57 Shiki
    Revised to support default TTL for RFC 3927 (1 for link-local, IP_TTL
    for others).

    43    05/10/14 15:38 Ueno_kyu
    Modified not to verify checksum if checksum is zero.

    42    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    49    04/10/21 16:59 Ueno_kyu
    Enclosed IPv6 specific codes in #ifdef IP_INET6... #endif blocks.

    48    04/09/28 20:20 Ueno_kyu
    Modified UDP6Out() to use the IPv6 minimum link MTU to send a UDP
    unicast datagram.

    47    04/08/18 16:36 Ueno_kyu
    Modified ICMP6SendError() to set a pointer field.

    46    6/29/04 11:06 Shiki
    Modified the use of IF_FLAG_* for better loopback support. Now
    IF_FLAG_* is set to IFDatagram{} before sending the packet.

    45    6/14/04 10:19 Shiki
    Fixed broken assertion in DiscardInput().

    44    6/09/04 17:01 Shiki
    Fixed for IPv4 build.

    43    6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    41    2/04/04 9:14 Shiki
    Fixed UDPGetSockOpt() to return IP_ERR_NONE correctly in case
    SO_SO_TYPE.

    40    11/13/03 21:37 Shiki
    Fixed Cancel() so that other UDP operations can be issued from
    callbacks unless the result is IP_ERR_CLOSING.

    39    11/04/03 14:13 Shiki
    Fixed IP_ERR_DATASIZE error check code in UDPSendAsync().

    38    10/29/03 21:59 Shiki
    Revised using IFInitDatagram().

    37    10/22/03 10:47 Shiki
    Modified to get ephemeral port number between 49152 and 65535 rather
    than from between 1024 and. 5000.

    36    5/15/03 15:54 Shiki
    Modified to clear the IF_DATAGRAM_FLAG_DROP bit in IFDatagram.flag
    before sending a Ethernet packet.

    35    5/07/03 14:17 Shiki
    Revised to send back ICMP port unreachable error.

    34    5/07/03 11:31 Shiki
    Modified discarded packets due to ins. resources.

    33    5/07/03 11:20 Shiki
    Clean up.

    32    5/03/03 12:59 Shiki
    Implemented IPInterfaceStat{} support functions.

    31    4/01/03 10:19 Shiki
    Modified IP multicast logic so that a socket receives multicast
    datagrams only from the joined group.

    30    3/27/03 17:38 Shiki
    Added support for multicast.

    29    2/25/03 16:06 Shiki
    Fixed buffer management bug in UDPSendAsync().

    28    1/30/03 18:36 Shiki
    Added support for UDP send buffering.

    27    1/23/03 17:25 Shiki
    Revised UDPInfo receive buffer structure using ring buffer.

    26    1/22/03 18:12 Shiki
    Added SOPoll() interface.
    Added support for SO_SO_REUSEADDR option.
    Fixed UDPSendAsync() not to hung if remote peer has been specified with
    UDPConnect().

    25    11/11/02 11:04 Shiki
    Implemented UDPReceiveExAsync(). Fixed a bug in receive buffer
    management code.

    24    7/22/02 15:47 Shiki
    Added UDP[Get/Set]RecvBuff().

    23    7/19/02 16:12 Shiki
    Added support for non-blocking I/O.

    22    4/30/02 14:52 Shiki
    Implemented UDPPeek().

    21    4/26/02 16:47 Shiki
    Added support for check sum error counters.

    20    4/24/02 11:18 Shiki
    Added more ASSERT()s.

    19    4/23/02 11:20 Shiki
    Modified Async functions to update *result even if the function failed.

    18    4/19/02 11:03 Shiki
    Revised UDP header check code. Fixed UDPReceiveAsync() length test
    code.

    17    4/18/02 21:46 Shiki
    Fixed UDPIn() to set socket->len and family correctly.

    16    4/18/02 20:57 Shiki
    Fixed UDPSendAsync()to clear sendCallback upon IPOut() failure.

    15    4/18/02 18:45 Shiki
    Fixed UDPSendAsync() to check remote socket address.

    14    4/18/02 9:30 Shiki
    Fixed UDP[Set|Get]SockOpt() to check info->pair.proto member.

    13    4/18/02 9:08 Shiki
    Modified UDP[Set|Get]SockOpt() to return IP_ERR_INV_OPTION error for
    unsupported options.

    12    4/17/02 10:47 Shiki
    Fixed UDPNotify() to handle the error code correctly.

    11    4/08/02 16:39 Shiki
    Implemented UDPGetSockOpt() and UDPSetSockOpt().
    Revised to support new IPSocket{} type.

    10    4/05/02 14:09 Shiki
    Refined using 'const'.

    9     3/27/02 16:47 Shiki
    Revised UDPNotify().

    8     3/27/02 9:37 Shiki
    Fixed to use the alias address for src address if the interface address
    is not configured.

    7     3/22/02 9:21 Shiki
    Modified so UDPInfo can save multiple UDP datagrams in its receive
    buffer.

    6     3/18/02 20:35 Shiki
    Modified Open() to test info for not being used.

    5     3/18/02 14:35 Shiki
    Clean up.

    4     3/14/02 16:15 Shiki
    Renamed UDPInfo.buffer to UDPInfo.header.

    3     3/13/02 9:17 Shiki
    Clean up with IP_ALEN.

    2     3/12/02 12:48 Shiki
    Added an assertion UDPSendAsync().

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <dolphin/os.h>
#include <dolphin/ip.h>
#include <dolphin/socket.h>
#include "IPPrivate.h"
#ifdef IP_INET6
#include "IP6Private.h"
#endif // IP_INET6

#include <string.h>

IFQueue    UDPInfoQueue;
int        UDPNumber;
int        UDP6Number;
static u16 Port = 49152;    // 49152-65535. 0 reserved as any.

void UDPDumpHeader(const IPHeader* ip, const UDPHeader* udp)
{
    OSTime t;

    t = __OSGetSystemTime();
    OSReport("%4llu.%03llu  ",
             OSTicksToSeconds(t) % 10000,
             OSTicksToMilliseconds(t) % 1000);

    OSReport("%d.%d.%d.%d:%d > %d.%d.%d.%d:%d  UDP\n",
             ip->src[0], ip->src[1], ip->src[2], ip->src[3], udp->src,
             ip->dst[0], ip->dst[1], ip->dst[2], ip->dst[3], udp->dst);
}

//
// UDP receive buffer subroutines
//

static s32 PeekInput(UDPObj* info, void* ptr, s32 len, s32 offset)
{
    u8*   head;
    IFVec vec[2];
    int   i;
    int   n;

    if (info->recvUsed < offset + len)
    {
        len = info->recvUsed - offset;
    }
    if (len <= 0)
    {
        return 0;
    }

    head = info->recvPtr + offset;
    if (info->recvPtr + info->recvBuff <= head)
    {
        head -= info->recvBuff;
    }
    n = IFRingGet(info->recvRing, info->recvBuff,
                  head, info->recvUsed - offset,
                  vec, len);
    for (i = 0, head = ptr; i < n; ++i)
    {
        memmove(head, vec[i].data, (u32) vec[i].len);
        head += vec[i].len;
    }
    return len;
}

// Discard the packet from the receive buffer
static void DiscardInput(UDPObj* info, const void* packet, int len)
{
    #pragma unused(packet)
    len += sizeof(u32);     // for flag

    ASSERT(len <= info->recvUsed);
    info->recvPtr = IFRingPut(info->recvRing, info->recvBuff,
                              info->recvPtr, info->recvUsed,
                              (s32) len);
    info->recvUsed -= len;
}

// Save packet (FIFO). Note UDPIn() can discard the packet
// if there is already one saved. No overflow message
// like ICMP source quench is required.
static void* SaveInput(UDPObj* info, const void* packet, int len, u32 flag)
{
    if (info->recvBuff - info->recvUsed < len + sizeof(flag))
    {
        // Do not let the program peek the packet if it cannot be kept in
        // the receive buffer.
        return NULL;
    }

    info->recvPtr = IFRingIn(info->recvRing, info->recvBuff,
                             info->recvPtr, info->recvUsed,
                             packet, len);
    info->recvUsed += len;

    info->recvPtr = IFRingIn(info->recvRing, info->recvBuff,
                             info->recvPtr, info->recvUsed,
                             (const u8*) &flag, sizeof(flag));
    info->recvUsed += sizeof(flag);
    return (void*) packet;
}

UDPObj* UDPGetObj(UDPInfo* info)
{
    switch (info->info.family)
    {
      case SO_PF_INET:
        return &info->obj;
#ifdef IP_INET6
      case SO_PF_INET6:
        return &((UDP6Info*) info)->obj;
#endif  // IP_INET6
      default:
        return NULL;
    }
}

static void NullCallback(UDPInfo* info, s32 result)
{
    #pragma unused(info, result)
}

static void SyncCallback(UDPInfo* info, s32 result)
{
    #pragma unused(result)
    OSWakeupThread(&UDPGetObj(info)->queueThread);
}

// getpeername
s32 UDPGetRemoteSocket(UDPInfo* info, void* sockAddr)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        rc = IPGetRemoteSocket(&info->info, sockAddr);
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

// getsockname
s32 UDPGetLocalSocket(UDPInfo* info, void* sockAddr)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        rc = IPGetLocalSocket(&info->info, sockAddr);
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 UDPSetOption(UDPInfo* info, u8 ttl, u8 tos)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        rc = IPSetOption(&info->info, ttl, tos);
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 UDPBind(UDPInfo* info, const void* socket)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    else if (info->info.family == SO_PF_INET)
    {
        rc = IP4Bind(&UDPInfoQueue, &info->info, socket,
                     (UDPGetObj(info)->flag & UDP_SO_REUSE) ? TRUE : FALSE);
    }
#ifdef IP_INET6
    else if (info->info.family == SO_PF_INET6)
    {
        rc = IP6Bind(&UDPInfoQueue, &info->info, socket,
                     (UDPGetObj(info)->flag & UDP_SO_REUSE) ? TRUE : FALSE);
    }
#endif  // IP_INET6
    else
    {
        rc = IP_ERR_INVALID;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 UDPConnect(UDPInfo* info, const void* socket)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    else if (info->info.family == SO_PF_INET)
    {
        rc = IP4Connect(&UDPInfoQueue, &info->info, socket, &Port);
    }
#ifdef IP_INET6
    else if (info->info.family == SO_PF_INET6)
    {
        rc = IP6Connect(&UDPInfoQueue, &info->info, socket, &Port);
    }
#endif  // IP_INET6
    else
    {
        rc = IP_ERR_INVALID;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 UDPGetRecvBuff(UDPInfo* info, void** recvbuf, s32* recvbufLen)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        UDPObj* obj = UDPGetObj(info);

        rc = IP_ERR_NONE;
        if (recvbufLen)
        {
            *recvbufLen = obj->recvBuff;
        }
        if (recvbuf)
        {
            *recvbuf = obj->recvRing;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 UDPSetRecvBuff(UDPInfo* info, void* recvbuf, s32 recvbufLen)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        // Note all the received packets are simply discarded.
        UDPObj* obj = UDPGetObj(info);

        rc = IP_ERR_NONE;
        obj->recvRing = recvbuf;
        obj->recvBuff = recvbufLen;
        obj->recvPtr = recvbuf;
        obj->recvUsed = 0;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 UDPGetSendBuff(UDPInfo* info, void** sendbuf, s32* sendbufLen)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        UDPObj* obj = UDPGetObj(info);

        rc = IP_ERR_NONE;
        if (sendbufLen)
        {
            *sendbufLen = obj->sendBuff;
        }
        if (sendbuf)
        {
            *sendbuf = obj->sendData;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 UDPSetSendBuff(UDPInfo* info, void* sendbuf, s32 sendbufLen)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        UDPObj* obj = UDPGetObj(info);

        if (obj->sendUsed != 0)
        {
            rc = IP_ERR_BUSY;
        }
        else
        {
            // Note all the received packets are simply discarded.
            rc = IP_ERR_NONE;
            obj->sendData = sendbuf;
            obj->sendBuff = sendbufLen;
            obj->sendUsed = 0;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

// heap, heapLen   Receive heap. 0 byte or more than 576 byte is recommended.
// Note just one datagram will be kept
s32 UDPOpen(UDPInfo* info, void* recvbuf, s32 recvbufLen)
{
    s32 rc;

    rc = UDPSocket(SO_AF_INET, info);
    if (0 <= rc)
    {
        UDPSetRecvBuff(info, recvbuf, recvbufLen);
    }
    return rc;
}

s32 UDPSocket(int af, UDPInfo* info)
{
    BOOL      enabled;
    BOOL      used;
    IPSocket* local;
    IPSocket* remote;
    UDPObj*   obj;

#ifdef IP_INET6
    if (info == NULL || (af != SO_AF_INET && af != SO_AF_INET6))
#else
    if (info == NULL || af != SO_AF_INET)
#endif
    {
        return IP_ERR_INVALID;
    }

    enabled = OSDisableInterrupts();
    used = __IPIsMember(&UDPInfoQueue, &info->info);
    OSRestoreInterrupts(enabled);
    if (used)
    {
        return IP_ERR_EXIST;
    }

    switch (af)
    {
      case SO_AF_INET:
        memset(info, 0, sizeof(UDPInfo));
        info->info.family = (u8) af;
        info->info.proto = IP_PROTO_UDP;
        local = IPGetLocalSockAddr(&info->info);
        remote = IPGetRemoteSockAddr(&info->info);
        local->len = remote->len = IP_SOCKLEN;
        local->family = remote->family = (u8) af;
        break;
#ifdef IP_INET6
      case SO_AF_INET6:
        memset(info, 0, sizeof(UDP6Info));
        info->info.family = (u8) af;
        info->info.proto = IP_PROTO_UDP;
        info->info.family = (u8) af;
        local = IPGetLocalSockAddr(&info->info);
        remote = IPGetRemoteSockAddr(&info->info);
        local->len = remote->len = sizeof(SOSockAddrIn6);
        local->family = remote->family = (u8) af;
        break;
#endif  // IP_INET6
    }

    // Initialize info and enqueue it
    info->info.tos = 0;         // Default
    info->info.ttl = 0;         // Default (1 for link-local, IP_TTL for others)
    info->info.mttl = 1;        // Default

    info->info.poll = 0;
    info->info.flag = IP_INFO_FLAG_MCASTLOOP;

    obj = UDPGetObj(info);
    OSInitThreadQueue(&obj->queueThread);

    enabled = OSDisableInterrupts();
    IFEnqueueTail(IPInfo*, &UDPInfoQueue, &info->info, link);
    switch (af)
    {
      case SO_AF_INET:
        ++UDPNumber;
        break;
      case SO_AF_INET6:
        ++UDP6Number;
        break;
    }
    OSRestoreInterrupts(enabled);

    return IP_ERR_NONE;
}

static void SendCallback(UDPInfo* info, s32 result)
{
    UDPCallback callback;
    UDPObj*     obj;

    obj = UDPGetObj(info);
    ASSERT(obj->datagram.interface == NULL);
    ASSERT(obj->datagram.queue == NULL);

    result = (result < 0) ? result : obj->datagram.vec[1].len;
    if (obj->sendResult)
    {
        *obj->sendResult = result;
        obj->sendResult = NULL;
    }

    if (obj->sendData)
    {
        ASSERT(obj->sendCallback == NULL);
        ASSERT(0 < obj->sendUsed);
        obj->sendUsed = 0;
    }
    else
    {
        ASSERT(obj->sendCallback != NULL);
        callback = obj->sendCallback;
        obj->sendCallback = NULL;
        callback(info, result);
    }

    if (0 < info->info.poll && obj->sendData == NULL)
    {
        __IPWakeupPollingThreads();
    }
}

static s32 UDP4Out(UDPInfo* info, const void* data, s32 len,
                      const IPSocket* sockAddr,
                      UDPCallback callback, s32* result)
{
    UDPObj*      obj = UDPGetObj(info);
    IPSocket*    local = IPGetLocalSockAddr(&info->info);
    IPSocket*    remote = IPGetRemoteSockAddr(&info->info);
    IPHeader*    ip;
    UDPHeader*   udp;
    s32          rc;
    IFDatagram*  datagram;
    IPInterface* interface = NULL;

    if (len < 0 || 65535 - UDP_HLEN - IP_MIN_HLEN < len)
    {
        rc = IP_ERR_DATASIZE;
        goto Error;
    }
    if (remote->port == 0)    // Connected?
    {
        if (sockAddr == NULL) // Peer specified?
        {
            rc = IP_ERR_SOCKET_UNSPECIFIED;
            goto Error;
        }
        else if (sockAddr->len != IP_SOCKLEN ||
                 sockAddr->family != IP_INET ||
                 sockAddr->port == 0 ||
                 IP_CLASSE(sockAddr->addr))   // Verify sockAddr is a valid socket
        {
            rc = IP_ERR_INVALID;
            goto Error;
        }
        else if (IP_ADDR_EQ(sockAddr->addr, IPAddrAny))   // Remote address is required
        {
            rc = IP_ERR_INV_SOCKET;
            goto Error;
        }
    }

    // Mode select
    if (obj->sendData == NULL)
    {
        ip = (IPHeader*) &obj->header[0];
        udp = (UDPHeader*) &obj->header[IP_MIN_HLEN];
        datagram = &obj->datagram;
        IFInitDatagram(datagram, ETH_IP, 2);

        obj->sendCallback = callback ? callback : NullCallback;
        obj->sendResult = result;
        if (result)
        {
            *result = IP_ERR_BUSY;
        }

        datagram->vec[1].data = (void*) data;
        datagram->callback = (IFCallback) SendCallback;
    }
    else if (obj->sendUsed <= 0)
    {
        ip = (IPHeader*) &obj->header[0];
        udp = (UDPHeader*) &obj->header[IP_MIN_HLEN];
        datagram = &obj->datagram;
        IFInitDatagram(datagram, ETH_IP, 2);

        memmove(obj->sendData, data, (u32) len);
        obj->sendUsed = len;

        datagram->vec[1].data = obj->sendData;
        datagram->callback = (IFCallback) SendCallback;
    }
    else
    {
        interface = &__IFDefault;   // XXX
        datagram = interface->alloc(interface, (s32) (sizeof(IFDatagram) + sizeof(IFVec) +
                                    IP_MIN_HLEN + UDP_HLEN + len));
        if (datagram == NULL)
        {
            ++interface->ipStat.outDiscards;
            rc = IP_ERR_INS_RESOURCES;
            goto Error;
        }
        IFInitDatagram(datagram, ETH_IP, 2);

        ip = (IPHeader*) ((u8*) datagram + sizeof(IFDatagram) + sizeof(IFVec));
        udp = (UDPHeader*) ((u8*) ip + IP_MIN_HLEN);
        memmove((u8*) udp + UDP_HLEN, data, (u32) len);

        datagram->vec[1].data = (u8*) udp + UDP_HLEN;
    }

    // Assemble packet header
    ip->verlen = IP_VERHLEN;
    ip->tos = info->info.tos;
    ip->len = (u16) (IP_HLEN(ip) + UDP_HLEN + len);
    ip->proto = IP_PROTO_UDP;
    ip->frag = 0;   // no fragment

    udp->src = local->port;
    udp->len = (u16) (UDP_HLEN + len);
    udp->sum = 0;   // Calculated in IPOut()

    if (remote->port != 0)                // Connected UDP socket?
    {
        udp->dst = remote->port;
        memmove(ip->dst, remote->addr, IP_ALEN);
    }
    else
    {
        udp->dst = sockAddr->port;
        memmove(ip->dst, sockAddr->addr, IP_ALEN);
    }

    // Select the source address [SHOULD avoid using __IFDefault but IPConnect is slow...]
    if (!IP_CLASSD(local->addr) &&
        IP_ADDR_NE(local->addr, IPAddrAny))
    {
        memmove(ip->src, local->addr, IP_ALEN);
    }
    else
    {
        IP4SelectSourceAddress(interface, ip->dst, ip->src);
    }

    // Use multicast ttl for multicast datagram
    if (IP_CLASSD(ip->dst))
    {
        ip->ttl = info->info.mttl;
        if (info->info.flag & IP_INFO_FLAG_MCASTLOOP)
        {
            datagram->flag |= IF_FLAG_LOOPBACK;
        }
    }
    else if (info->info.ttl)
    {
        ip->ttl = info->info.ttl;
    }
    else
    {
        ip->ttl = (u8) (IPIsLinkLocalAddr(interface, ip->src) ? 1 : IP_TTL);
    }

    datagram->vec[0].data = ip;
    datagram->vec[0].len  = IP_HLEN(ip) + UDP_HLEN;
    datagram->vec[1].len  = len;
    datagram->param = info;

    rc = IPOut(datagram);
    if (rc < 0)
    {
        ++interface->udpStat.outDatagrams;
        if (result)
        {
            *result = rc;
        }
        obj->sendCallback = NULL;

        if (0 < info->info.poll && obj->sendData == NULL)
        {
            __IPWakeupPollingThreads();
        }

        if (interface)
        {
            // datagram has not been sent out. Must release memory
            interface->free(interface, datagram, (s32) (sizeof(IFDatagram) + sizeof(IFVec) +
                            IP_MIN_HLEN + UDP_HLEN + len));
        }
    }
    else if (obj->sendData)
    {
        if (result)
        {
            *result = len;
        }
        if (callback)
        {
            callback(info, len);
        }
    }
    return rc;

Error:
    if (result)
    {
        *result = rc;
    }
    return rc;
}

#ifdef IP_INET6

static s32 UDP6Out(UDPInfo* info, const void* data, s32 len,
                   const SOSockAddrIn6* sockAddr,
                   UDPCallback callback, s32* result)
{
    UDPObj*        obj = UDPGetObj(info);
    SOSockAddrIn6* local = IPGetLocalSockAddr(&info->info);
    const
    SOSockAddrIn6* remote = IPGetRemoteSockAddr(&info->info);
    IP6Hdr*        ip6;
    UDPHeader*     udp;
    s32            rc;
    IFDatagram*    datagram;
    IP6Entry*      nextHop;
    IP6Entry*      destination;
    IPInterface*   interface;

    if (len < 0 || 65535 - UDP_HLEN < len)
    {
        rc = IP_ERR_DATASIZE;
        goto Error;
    }
    if (remote->port == 0)    // Not connected?
    {
        if (sockAddr == NULL) // Peer specified?
        {
            rc = IP_ERR_SOCKET_UNSPECIFIED;
            goto Error;
        }
        else if (sockAddr->len != sizeof(SOSockAddrIn6) ||
                 sockAddr->family != SO_PF_INET6 ||
                 sockAddr->port == 0)   // Verify sockAddr is a valid socket
        {
            rc = IP_ERR_INVALID;
            goto Error;
        }
        else if (SO_IN6_ARE_ADDR_EQUAL(&sockAddr->addr, &SOIn6AddrAny))   // Remote address is required
        {
            rc = IP_ERR_INV_SOCKET;
            goto Error;
        }
        remote = sockAddr;
    }
    else
    {
        sockAddr = NULL;
    }

    // Determine next-hop
    nextHop = IP6GetNextHop(&info->info, &remote->addr, &destination);
    if (nextHop == 0)
    {
        rc = IP_ERR_INS_RESOURCES;
        goto Error;
    }
    ASSERT(nextHop->interface);
    interface = nextHop->interface;

    // Mode select
    if (obj->sendData == NULL)
    {
        ip6 = (IP6Hdr*) &obj->header[0];
        udp = (UDPHeader*) &obj->header[sizeof(IP6Hdr)];
        datagram = &obj->datagram;
        IFInitDatagram(datagram, ETH_IPv6, 2);

        obj->sendCallback = callback ? callback : NullCallback;
        obj->sendResult = result;
        if (result)
        {
            *result = IP_ERR_BUSY;
        }

        datagram->vec[1].data = (void*) data;
        datagram->callback = (IFCallback) SendCallback;
    }
    else if (obj->sendUsed <= 0)
    {
        ip6 = (IP6Hdr*) &obj->header[0];
        udp = (UDPHeader*) &obj->header[sizeof(IP6Hdr)];
        datagram = &obj->datagram;
        IFInitDatagram(datagram, ETH_IPv6, 2);

        memmove(obj->sendData, data, (u32) len);
        obj->sendUsed = len;

        datagram->vec[1].data = obj->sendData;
        datagram->callback = (IFCallback) SendCallback;
    }
    else
    {
        datagram = interface->alloc(interface, (s32) (sizeof(IFDatagram) + sizeof(IFVec) +
                                    sizeof(IP6Hdr) + UDP_HLEN + len));
        if (datagram == NULL)
        {
            ++interface->ipv6Stat.outDiscards;
            rc = IP_ERR_INS_RESOURCES;
            goto Error;
        }
        IFInitDatagram(datagram, ETH_IPv6, 2);

        ip6 = (IP6Hdr*) ((u8*) datagram + sizeof(IFDatagram) + sizeof(IFVec));
        udp = (UDPHeader*) ((u8*) ip6 + sizeof(IP6Hdr));
        memmove((u8*) udp + UDP_HLEN, data, (u32) len);

        datagram->vec[1].data = (u8*) udp + UDP_HLEN;
    }

    // Assemble packet header
    ip6->flow = 6u << 28;
    ip6->plen = (u16) (UDP_HLEN + len);
    ip6->next = IP_PROTO_UDP;
    ip6->dst = remote->addr;

    // Use multicast ttl for multicast datagram
    if (SO_IN6_IS_ADDR_MULTICAST(&ip6->dst))
    {
        ip6->hops = info->info.mttl;
        if (info->info.flag & IP_INFO_FLAG_MCASTLOOP)
        {
            datagram->flag |= IF_FLAG_LOOPBACK;
        }
    }
    else
    {
        ip6->hops = info->info.ttl;
    }

    udp->src = local->port;
    udp->len = (u16) (UDP_HLEN + len);
    udp->sum = 0;   // Calculated in IPOut()
    udp->dst = remote->port;

    // Select the source address
    if (!SO_IN6_IS_ADDR_MULTICAST(&local->addr) &&
        !SO_IN6_ARE_ADDR_EQUAL(&local->addr, &SOIn6AddrAny))
    {
        ip6->src = local->addr;
    }
    else
    {
        IP6SelectSourceAddress(interface, &ip6->dst, &ip6->src);
    }

    datagram->vec[0].data = ip6;
    datagram->vec[0].len  = sizeof(IP6Hdr) + UDP_HLEN;
    datagram->vec[1].len  = len;
    datagram->param = info;
    datagram->mtu = (u16) IP6GetPathMTU(destination);

    udp->sum = IP6CheckSum(IP_PROTO_UDP, datagram->vec, datagram->nVec, udp, ip6->plen);
    rc = IP6Out(interface, datagram, nextHop);
    if (rc < 0)
    {
        ++interface->udpStat.outDatagrams;
        if (result)
        {
            *result = rc;
        }
        obj->sendCallback = NULL;

        if (0 < info->info.poll && obj->sendData == NULL)
        {
            __IPWakeupPollingThreads();
        }

        if (interface)
        {
            // datagram has not been sent out. Must release memory
            interface->free(interface, datagram, (s32) (sizeof(IFDatagram) + sizeof(IFVec) +
                            sizeof(IP6Hdr) + UDP_HLEN + len));
        }
    }
    else if (obj->sendData)
    {
        if (result)
        {
            *result = len;
        }
        if (callback)
        {
            callback(info, len);
        }
    }
    return rc;

Error:
    if (result)
    {
        *result = rc;
    }
    return rc;
}

#endif  // IP_INET6

// If info->sendData is NULL, UDPSendAsync() waits for the
// completion of the packet transfer. Otherwise, it copies
// data to info->sendData and returns immedeately if
// info->sendUsed == 0. If info->sendUsed is greater than
// zero, it tries to allocate a memory block from the
// interface FIFO to send the packet immediately and returns.
s32 UDPSendAsync(UDPInfo* info, const void* data, s32 len,
                 const void* sockAddr,
                 UDPCallback callback, s32* result)
{
    BOOL          enabled;
    s32           rc;
    IPInterface*  interface = NULL;
    UDPObj*       obj;
    SOSockAddrIn* local;
    SOSockAddrIn* remote;

    rc = IP_ERR_NONE;
    enabled = OSDisableInterrupts();
    obj = UDPGetObj(info);
    local = IPGetLocalSockAddr(&info->info);
    remote = IPGetRemoteSockAddr(&info->info);

    // Error check
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
        goto Error;
    }

    if (local->port == 0)
    {
        // Attempts to assign an ephemeral source port number
        local->port = IPGetAnonPort(&UDPInfoQueue, &Port);
        if (local->port == 0)
        {
            rc = IP_ERR_INS_RESOURCES;
            goto Error;
        }
    }

    if (obj->sendCallback && obj->sendData == NULL)
    {
        rc = IP_ERR_BUSY;
        goto Error;
    }
    if (obj->sendData && obj->sendBuff < len)
    {
        rc = IP_ERR_DATASIZE;
        goto Error;
    }

    switch (info->info.family)
    {
      case SO_PF_INET:
        rc = UDP4Out(info, data, len,
                     sockAddr,
                     callback, result);
        OSRestoreInterrupts(enabled);
        return rc;
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        rc = UDP6Out(info, data, len,
                     sockAddr,
                     callback, result);
        OSRestoreInterrupts(enabled);
        return rc;
        break;
#endif  // IP_INET6
      default:
        rc = IP_ERR_INVALID;
        goto Error;
        break;
    }

Error:
    if (result)
    {
        *result = rc;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 UDPSend(UDPInfo* info, const void* data, s32 len,
            const void* remote)
{
    BOOL enabled;
    vs32 result;
    s32  rc;

    rc = UDPSendAsync(info, data, len, remote,
                      SyncCallback, (s32*) &result);
    if (rc < 0)
    {
        return rc;
        // NOT REACHED HERE
    }

    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&UDPGetObj(info)->queueThread);
    }
    OSRestoreInterrupts(enabled);

    return (s32) result;
}

s32 UDPReceiveExAsync(UDPInfo* info, void* data, s32 len,
                      void* localSockAddr, void* remoteSockAddr, u32 flag,
                      UDPCallback callback, s32* result)
{
    BOOL          enabled;
    s32           rc;
    SOSockAddrIn* local;
    SOSockAddrIn* remote;
    UDPObj*       obj;

    enabled = OSDisableInterrupts();
    rc = IP_ERR_NONE;
    obj = UDPGetObj(info);
    local = IPGetLocalSockAddr(&info->info);
    remote = IPGetRemoteSockAddr(&info->info);
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    else if (len < 0)
    {
        rc = IP_ERR_DATASIZE;
    }
    else if (local->port == 0)
    {
        rc = IP_ERR_NOT_EXIST;
    }
    else if (obj->recvCallback && !(flag & SO_MSG_DONTWAIT))
    {
        rc = IP_ERR_BUSY;
    }
    if (rc != IP_ERR_NONE)
    {
        if (result)
        {
            *result = rc;
        }
        OSRestoreInterrupts(enabled);
        return rc;
    }

    callback = callback ? callback : NullCallback;

    if (0 < obj->recvUsed)
    {
        UDPHeader udp;

        if (info->info.family == SO_PF_INET)
        {
            IPHeader ip;

            rc = PeekInput(obj, &ip, sizeof(IPHeader), 0);
            ASSERT(rc == sizeof(IPHeader));
            rc = PeekInput(obj, &udp, sizeof(UDPHeader), IP_HLEN(&ip));
            ASSERT(rc == sizeof(UDPHeader));

            len = MIN(udp.len - UDP_HLEN, len);
            rc = PeekInput(obj, data, len, IP_HLEN(&ip) + UDP_HLEN);
            IPReceiveSocket(localSockAddr, ip.dst, udp.dst);
            IPReceiveSocket(remoteSockAddr, ip.src, udp.src);

            if ((flag & SO_MSG_PEEK) == 0)
            {
                DiscardInput(obj, &ip, ip.len);
            }
        }
#ifdef IP_INET6
        else if (info->info.family == SO_PF_INET6)
        {
            IP6Hdr ip6;

            rc = PeekInput(obj, &ip6, sizeof(IP6Hdr), 0);
            ASSERT(rc == sizeof(IP6Hdr));
            rc = PeekInput(obj, &udp, sizeof(UDPHeader), sizeof(IP6Hdr));
            ASSERT(rc == sizeof(UDPHeader));

            // XXX externsion header

            len = MIN(udp.len - UDP_HLEN, len);
            rc = PeekInput(obj, data, len, sizeof(IP6Hdr) + UDP_HLEN);
            IP6ReceiveSocket(localSockAddr, &ip6.dst, udp.dst);
            IP6ReceiveSocket(remoteSockAddr, &ip6.src, udp.src);

            if ((flag & SO_MSG_PEEK) == 0)
            {
                DiscardInput(obj, &ip6, (s32) (sizeof(IP6Hdr) + ip6.plen));
            }
        }
#endif  // IP_INET6
        else
        {
            OSRestoreInterrupts(enabled);
            return *result = IP_ERR_INVALID;
        }

        if (result)
        {
            *result = udp.len - UDP_HLEN;
        }
        callback(info, udp.len - UDP_HLEN);
    }
    else if (flag & SO_MSG_DONTWAIT)
    {
        rc = IP_ERR_AGAIN;
        if (result)
        {
            *result = rc;
        }
    }
    else
    {
        // Wait for the packet...
        if (flag & SO_MSG_PEEK)
        {
            obj->flag |= UDP_SO_PEEK;
        }
        else
        {
            obj->flag &= ~UDP_SO_PEEK;
        }
        obj->recvCallback = callback;
        obj->recvResult = result;
        if (result)
        {
            *result = IP_ERR_BUSY;
        }
        obj->data   = data;
        obj->len    = len;
        obj->remote = remoteSockAddr;
        obj->local  = localSockAddr;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 UDPReceiveAsync(UDPInfo* info, void* data, s32 len,
                    void* local, void* remote,
                    UDPCallback callback, s32* result)
{
    return UDPReceiveExAsync(info, data, len,
                             local, remote, 0,
                             callback, result);
}

s32 UDPReceiveNonblock(UDPInfo* info, void* data, s32 len,
                       void* local, void* remote)
{
    s32 rc;
    s32 result;

    rc = UDPReceiveExAsync(info, data, len,
                           local, remote, SO_MSG_DONTWAIT,
                           NULL, &result);
    return (rc == IP_ERR_NONE) ? result : rc;
}

s32 UDPReceiveEx(UDPInfo* info, void* data, s32 len,
                 void* local, void* remote, u32 flag)
{
    BOOL enabled;
    vs32 result;
    s32  rc;

    rc = UDPReceiveExAsync(info, data, len,
                           local, remote, flag,
                           SyncCallback, (s32*) &result);
    if (rc < 0)
    {
        return rc;
        // NOT REACHED HERE
    }

    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&UDPGetObj(info)->queueThread);
    }
    OSRestoreInterrupts(enabled);

    return (s32) result;
}

s32 UDPReceive(UDPInfo* info, void* data, s32 len,
               void* local, void* remote)
{
    return UDPReceiveEx(info, data, len, local, remote, 0);
}

static void Cancel(UDPInfo* info, s32 result)
{
    UDPCallback sendCallback;
    UDPCallback recvCallback;
    s32*        sendResult;
    s32*        recvResult;
    UDPObj*     obj;

    obj = UDPGetObj(info);

    // Cancel datagram:
    //   If obj->datagram is in IP/ARP pending queue, it must be
    //   removed from the queue before aborting the operation.
    IPCancel(&obj->datagram);

    sendCallback = obj->sendCallback;
    recvCallback = obj->recvCallback;
    sendResult = obj->sendResult;
    recvResult = obj->recvResult;
    obj->sendResult = NULL;
    obj->recvResult = NULL;

    if (result == IP_ERR_CLOSING)
    {
        // Prevent further UDP operation to perform
        obj->sendCallback = NullCallback;
        obj->recvCallback = NullCallback;
    }
    else
    {
        obj->sendCallback = NULL;
        obj->recvCallback = NULL;
    }

    if (sendCallback)
    {
        if (sendResult)
        {
            ASSERT(*sendResult == IP_ERR_BUSY);
            *sendResult = result;
        }
        sendCallback(info, result);
    }

    if (recvCallback)
    {
        if (recvResult)
        {
            ASSERT(*recvResult == IP_ERR_BUSY);
            *recvResult = result;
        }
        recvCallback(info, result);
    }

    if (0 < info->info.poll)
    {
        __IPWakeupPollingThreads();
    }
}

// Cancels current operations
s32 UDPCancel(UDPInfo* info)
{
    BOOL enabled;
    s32  rc;

    rc = IP_ERR_NONE;
    enabled = OSDisableInterrupts();
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    if (rc != IP_ERR_NONE)
    {
        OSRestoreInterrupts(enabled);
        return rc;
    }

    Cancel(info, IP_ERR_CANCELED);

    OSRestoreInterrupts(enabled);
    return rc;
}

BOOL UDPAbort(UDPInfo* info, s32 rc)
{
    ASSERT(info->info.proto == IP_PROTO_UDP);
    if (info->info.proto != IP_PROTO_UDP)
    {
        return FALSE;
    }
    Cancel(info, rc);
    return TRUE;
}

s32 UDPClose(UDPInfo* info)
{
    BOOL enabled;
    s32  rc;

    rc = IP_ERR_NONE;
    enabled = OSDisableInterrupts();
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    if (rc != IP_ERR_NONE)
    {
        OSRestoreInterrupts(enabled);
        return rc;
    }

    Cancel(info, IP_ERR_CLOSING);

    IPClose(&info->info);

    // Dequeue info from the queue
    IFDequeueItem(IPInfo*, &UDPInfoQueue, &info->info, link);
    switch (info->info.family)
    {
      case SO_AF_INET:
        --UDPNumber;
        break;
      case SO_AF_INET6:
        --UDP6Number;
        break;
    }
    info->info.proto = 0;

    OSRestoreInterrupts(enabled);
    return rc;
}

s32 UDPGetSockOpt(UDPInfo* info, int level, int optname,
                  void* optval, int* optlen)
{
    BOOL    enabled;
    s32     rc = IP_ERR_INV_OPTION;
    UDPObj* obj;

    enabled = OSDisableInterrupts();
    obj = UDPGetObj(info);
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    else if (level == SO_SOL_SOCKET)
    {
        switch (optname)
        {
          case SO_SO_REUSEADDR:
            if (sizeof(BOOL) <= *optlen)
            {
                *(BOOL*) optval = (obj->flag & UDP_SO_REUSE) ? TRUE : FALSE;
                *optlen = sizeof(BOOL);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_SO_TYPE:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = SO_SOCK_DGRAM;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
        }
    }
    else if (level == SO_SOL_IP)
    {
        rc = IPGetSockOpt(&info->info, level, optname, optval, optlen);
    }
#ifdef IP_INET6
    else if (level == SO_IPPROTO_IPV6)
    {
        rc = IP6GetSockOpt(&info->info, level, optname, optval, optlen);
    }
#endif  // IP_INET6
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 UDPSetSockOpt(UDPInfo* info, int level, int optname,
                  const void* optval, int optlen)
{
    BOOL    enabled;
    s32     rc = IP_ERR_INV_OPTION;
    UDPObj* obj;

    enabled = OSDisableInterrupts();
    obj = UDPGetObj(info);
    if (info->info.proto != IP_PROTO_UDP)
    {
        rc = IP_ERR_INVALID;
    }
    else if (level == SO_SOL_SOCKET)
    {
        switch (optname)
        {
          case SO_SO_REUSEADDR:
            if (sizeof(BOOL) <= optlen)
            {
                if (*(const BOOL*) optval)
                {
                    obj->flag |= UDP_SO_REUSE;
                }
                else
                {
                    obj->flag &= ~UDP_SO_REUSE;
                }
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          default:
            break;
        }
    }
    else if (level == SO_SOL_IP)
    {
        rc = IPSetSockOpt(&info->info, level, optname, optval, optlen);
    }
#ifdef IP_INET6
    else if (level == SO_IPPROTO_IPV6)
    {
        rc = IP6SetSockOpt(&info->info, level, optname, optval, optlen);
    }
#endif  // IP_INET6
    OSRestoreInterrupts(enabled);
    return rc;
}

short __UDPPoll(UDPInfo* info)
{
    short   event;
    UDPObj* obj;

    if (info->info.proto != IP_PROTO_UDP)
    {
        return SO_POLLNVAL;
    }
    obj = UDPGetObj(info);
    event = 0;
    if (obj->sendCallback == NULL || obj->sendData != NULL)
    {
        event |= SO_POLLWRNORM;
    }
    if (0 < obj->recvUsed)
    {
        event |= SO_POLLRDNORM;
    }
    return event;
}

void UDP4In(IPInterface* interface, IPHeader* ip, UDPHeader* udp, u32 flag)
{
    UDPInfo*    info;
    UDPCallback callback;
    void*       data;
    s32         len;
    IFVec       vec;
    UDPObj*     obj;

    if (ip->len < IP_HLEN(ip) + UDP_HLEN ||
        ip->len < IP_HLEN(ip) + udp->len ||
        udp->len < UDP_HLEN)
    {
        ++interface->udpStat.inErrors;
        return;
    }

    // Verify checksum ([SHOULD] Be done by memmove)
    vec.data = ip;
    vec.len  = ip->len;
    if (udp->sum != 0 && IP4CheckSum(IP_PROTO_UDP, &vec, 1) != 0)
    {
        ++interface->udpStat.inErrors;
        return;
    }

    // XXX Multicast/boradcst demulplexing

    // Lookup info that has the corresponding bind/port pair.
    info = (UDPInfo*) IP4LookupInfo(&UDPInfoQueue,
                                    ip->src, ip->dst, udp->src, udp->dst,
                                    flag);
    if (info == NULL)
    {
        ++interface->udpStat.noPorts;
        if (flag == IF_FLAG_UNICAST)
        {
            // [SHOULD] Send ICMP port unreachable error back to the sender
            // if the datagram was not *link-level* broadcast or multicast.
            // However, the other end host is very unlikely to check ICMP
            // error for UDP...
            ICMPUnreachable ur;

            ur.type   = ICMP_UNREACHABLE;
            ur.code   = ICMP_UNREACHABLE_PORT;
            ur.unused = 0;
            ur.mtu    = 0;
            ICMPSendError((ICMPHeader*) &ur, interface, ip, flag);
        }
        return;
        // NOT REACHED HERE
    }

    //
    // Copy-in
    //
    ++interface->udpStat.inDatagrams;
    data = (u8*) udp + UDP_HLEN;
    len  = udp->len - UDP_HLEN;
    obj = UDPGetObj(info);
    callback = obj->recvCallback;

    if (callback == NULL || (obj->flag & UDP_SO_PEEK))
    {
        // Save packet (FIFO). Note UDPIn() can discard the packet
        // if there is already one saved. No overflow message
        // like ICMP source quench is required.
        ip = SaveInput(obj, ip, ip->len, flag);
        if (ip == NULL)
        {
            // Do not let the program peek the packet if it cannot be kept in
            // the receive buffer.
            ++interface->stat.inDiscards;
            return;
            // NOT REACHED HERE
        }
        else if (0 < info->info.poll)
        {
            __IPWakeupPollingThreads();
        }
    }

    if (callback) // Already waiting for the packet?
    {
        len = MIN(obj->len, udp->len - UDP_HLEN);
        memmove(obj->data, (u8*) udp + UDP_HLEN, (u32) len);

        IPReceiveSocket(obj->local, ip->dst, udp->dst);
        IPReceiveSocket(obj->remote, ip->src, udp->src);

        if (obj->recvResult)
        {
            *obj->recvResult = udp->len - UDP_HLEN;
            obj->recvResult = NULL;
        }

        obj->recvCallback = NULL;
        callback(info, udp->len - UDP_HLEN);
    }
}

#ifdef IP_INET6
void UDP6In(IPInterface* interface, IP6Hdr* ip6, UDPHeader* udp, s32 len, u32 flag)
{
    UDPInfo*    info;
    UDPCallback callback;
    void*       data;
    IFVec       vec;
    UDPObj*     obj;

    if (len < UDP_HLEN || udp->len < UDP_HLEN || len < udp->len)
    {
        ++interface->udpStat.inErrors;
        return;
    }

    // Verify checksum ([SHOULD] Be done by memmove)
    vec.data = ip6;
    vec.len  = (s32) (sizeof(IP6Hdr) + ip6->plen);
    if (IP6CheckSum(IP_PROTO_UDP, &vec, 1, udp, len) != 0)
    {
        ++interface->udpStat.inErrors;
        return;
    }

    // XXX Multicast/boradcst demulplexing

    // Lookup info that has the corresponding bind/port pair.
    info = (UDPInfo*) IP6LookupInfo(&UDPInfoQueue,
                                    &ip6->src, &ip6->dst, udp->src, udp->dst,
                                    flag);
    if (info == NULL)
    {
        ++interface->udpStat.noPorts;
        ICMP6SendError(interface, ICMP6_DST_UNREACH, ICMP6_DST_UNREACH_NOPORT, ip6, flag, 0);
        return;
        // NOT REACHED HERE
    }

    //
    // Copy-in
    //
    ++interface->udpStat.inDatagrams;
    data = (u8*) udp + UDP_HLEN;
    len  = udp->len - UDP_HLEN;
    obj = UDPGetObj(info);
    callback = obj->recvCallback;

    if (callback == NULL || (obj->flag & UDP_SO_PEEK))
    {
        // Save packet (FIFO). Note UDPIn() can discard the packet
        // if there is already one saved. No overflow message
        // like ICMP source quench is required.
        ip6 = SaveInput(obj, ip6, (s32) (sizeof(IP6Hdr) + ip6->plen), flag);
        if (ip6 == NULL)
        {
            // Do not let the program peek the packet if it cannot be kept in
            // the receive buffer.
            ++interface->stat.inDiscards;
            return;
            // NOT REACHED HERE
        }
        else if (0 < info->info.poll)
        {
            __IPWakeupPollingThreads();
        }
    }

    if (callback) // Already waiting for the packet?
    {
        len = MIN(obj->len, udp->len - UDP_HLEN);
        memmove(obj->data, (u8*) udp + UDP_HLEN, (u32) len);

        IP6ReceiveSocket(obj->local, &ip6->dst, udp->dst);
        IP6ReceiveSocket(obj->remote, &ip6->src, udp->src);

        if (obj->recvResult)
        {
            *obj->recvResult = udp->len - UDP_HLEN;
            obj->recvResult = NULL;
        }

        obj->recvCallback = NULL;
        callback(info, udp->len - UDP_HLEN);
    }
}
#endif

// ICMP error handler
void UDPNotify(const IPHeader* ip, s32 err)
{
    UDPHeader* udp;
    IPInfo*    info;
    IPInfo*    next;
    UDPInfo*   match;

    udp = (UDPHeader*) ((u8*) ip + IP_HLEN(ip));
    if (udp->dst == 0)
    {
        return;
    }

    // Lookup info reversing dst and src fields
    IFIterateQueue(IPInfo*, &UDPInfoQueue, info, next, link)
    {
        IPSocket* local = IPGetLocalSockAddr(info);
        IPSocket* remote = IPGetRemoteSockAddr(info);

        if (info->family != SO_AF_INET)
        {
            continue;
        }

        if (local->port == 0 || local->port != udp->src)
        {
            continue;
        }
        if (IP_ADDR_NE(local->addr, IPAddrAny) &&
            IP_ADDR_NE(local->addr, ip->src))
        {
            continue;
        }
        if (remote->port != udp->dst ||
            IP_ADDR_NE(remote->addr, ip->dst))
        {
            continue;
        }

        match = (UDPInfo*) info;
        Cancel(match, err);
    }
}

#ifdef IP_INET6
// ICMP error handler
void UDP6Notify(const IP6Hdr* ip6, const UDPHeader* udp, s32 err)
{
    IPInfo*    info;
    IPInfo*    next;
    UDPInfo*   match;

    if (udp->dst == 0)
    {
        return;
    }

    // Lookup info reversing dst and src fields
    IFIterateQueue(IPInfo*, &UDPInfoQueue, info, next, link)
    {
        SOSockAddrIn6* local = IPGetLocalSockAddr(info);
        SOSockAddrIn6* remote = IPGetRemoteSockAddr(info);

        if (info->family != SO_AF_INET6)
        {
            continue;
        }

        if (local->port == 0 || local->port != udp->src)
        {
            continue;
        }
        if (!SO_IN6_IS_ADDR_UNSPECIFIED(&local->addr) &&
            !SO_IN6_ARE_ADDR_EQUAL(&local->addr, &ip6->src))
        {
            continue;
        }
        if (remote->port != udp->dst ||
            !SO_IN6_ARE_ADDR_EQUAL(&remote->addr, &ip6->dst))
        {
            continue;
        }

        match = (UDPInfo*) info;
        Cancel(match, err);
    }
}
#endif  // IP_INET6

s32 UDPPeek(UDPInfo* info, void* data, s32 len,
            void* local, void* remote)
{
    return UDPReceiveExAsync(info, data, len,
                             local, remote,
                             SO_MSG_PEEK | SO_MSG_DONTWAIT,
                             NULL, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         UDPOnReset

  Description:  Reset function for OSResetSystem()

  Arguments:    final       TRUE if OSResetSystem() is about to reset
                            the system

  Returns:      TRUE if GBA subsystem is ready to reset.
 *---------------------------------------------------------------------------*/
BOOL UDPOnReset(BOOL final)
{
    #pragma unused( final )
    UDPInfo* info;

    if (IFIsEmptyQueue(&UDPInfoQueue))
    {
        return TRUE;
    }

    while (!IFIsEmptyQueue(&UDPInfoQueue))
    {
        info = (UDPInfo*) IFQueryQueueHead(&UDPInfoQueue);
        UDPClose(info);
    }
    return FALSE;
}

s32 UDPReport(IPInterface* interface, void* optval, int* optlen)
{
    #pragma unused( interface )
    int       len;
    IPInfo*   info;
    IPInfo*   next;
    UDPEntry* udp;

    len = 0;
    udp = optval;
    IFIterateQueue(IPInfo*, &UDPInfoQueue, info, next, link)
    {
        if (*optlen < len + sizeof(UDPEntry))
        {
            break;
        }
        if (info->family == SO_PF_INET)
        {
            memcpy(&udp->local, IPGetLocalSockAddr(info), sizeof(SOSockAddrIn));
            memcpy(&udp->remote, IPGetRemoteSockAddr(info), sizeof(SOSockAddrIn));
            len += sizeof(UDPEntry);
            ++udp;
        }
    }
    *optlen = len;
    return IP_ERR_NONE;
}

#ifdef IP_INET6
s32 UDP6Report(IPInterface* interface, void* optval, int* optlen)
{
    #pragma unused( interface )
    int        len;
    IPInfo*    info;
    IPInfo*    next;
    UDP6Entry* udp;

    len = 0;
    udp = optval;
    IFIterateQueue(IPInfo*, &UDPInfoQueue, info, next, link)
    {
        if (*optlen < len + sizeof(UDP6Entry))
        {
            break;
        }
        if (info->family == SO_PF_INET6)
        {
            memcpy(&udp->local, IPGetLocalSockAddr(info), sizeof(SOSockAddrIn6));
            memcpy(&udp->remote, IPGetRemoteSockAddr(info), sizeof(SOSockAddrIn6));
            len += sizeof(UDP6Entry);
            ++udp;
        }
    }
    *optlen = len;
    return IP_ERR_NONE;
}
#endif // IP_INET6
