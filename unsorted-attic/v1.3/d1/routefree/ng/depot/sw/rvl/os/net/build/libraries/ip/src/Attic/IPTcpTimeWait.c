/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPTcpTimeWait.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPTcpTimeWait.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    22    3/06/06 14:34 Shiki
    Fixed TCPSetTimeWaitBuffer() so it can clear the time wait buffer.

    21    2/27/06 15:08 Shiki
    Added TCPReportTimeWaitNumber() and TCP6ReportTimeWaitNumber().

    20    2/21/06 14:33 Shiki
    Fixed IsExpired().

    19    2/15/06 14:47 Shiki
    Adde TCPReportTimeWait and TCP6ReportTimeWait.
    Revised TCPTimeWaitInfo{} using SOIn6Addr.

    18    2/14/06 9:59 Shiki
    Modified using use interface->closeWaitInterval.
    Modified type of the expire time value to OSTime.

    17    2/09/06 14:32 Shiki
    Fixed TCPStartTimeWait().

    16    12/28/05 11:34 Shiki
    Fixed TCPTestTimeWait().

    15    12/22/05 18:53 Shiki
    Fixed TIME-WAIT management code bug that TCPInfo remains in TIME-WAIT
    even after TCPTimeWaitInfo is expired.

    14    12/22/05 15:46 Shiki
    Removed segLen check from TCPTestTimeWait().

    13    12/22/05 12:00 Shiki
    Modified TIME-WAIT management to process SYN following RFC 1122.

    12    12/22/05 11:05 Shiki
    Modified TCPTestTimeWait() to drop valid URG.

    11    12/22/05 9:31 Shiki
    Fixed TIME-WAIT TCB abort/RST operations.

    10    12/21/05 17:27 Shiki
    Fixed TCPCancel() to delete TCB in TIME-WAIT state.

    9     11/24/05 17:00 Shiki
    Fixed LookupTimeWaitInfo4().

    8     04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    10    04/10/21 16:59 Ueno_kyu
    Enclosed IPv6 specific codes in #ifdef IP_INET6... #endif blocks.

    9     6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    7     8/21/03 20:58 Shiki
    Added support for SACK/FACK.

    6     6/13/02 11:17 Shiki
    Fixed TCPStartTimeWait() so it doesn't crash even if
    TCPSetTimeWaitBuffer() has not been called.

    5     4/15/02 14:39 Shiki
    Added comment regarding RFC 1337.

    4     4/08/02 16:48 Shiki
    Fixed TCPStartTimeWait() to call TCPAbort() at the last.

    3     4/05/02 14:09 Shiki
    Refined using 'const'.

    2     3/13/02 9:17 Shiki
    Clean up with IP_ALEN.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <dolphin/os.h>
#include <dolphin/socket.h>
#include <dolphin/ip.h>
#include <dolphin/ip/IFFifo.h>
#include "IPPrivate.h"
#ifdef IP_INET6
#include "IP6Private.h"
#endif // IP_INET6

#include <string.h>

/*

The TIME-WAIT state:

 * Prevents delayed packets from being accepted by a later connection
 * TCB kept in memory until 2MSL timeout, then state moves to CLOSED
 * MSL 30s. ~ 2min.

 */

// 52 byte structure. 2 MSL = 4 min.
// Assume 1 transaction: 1 sec
// 4 min / 1 sec = 240
// 240 * 52 = 12 KB
typedef struct TCPTimeWaitInfo
{
    SOIn6Addr remoteAddr;
    SOIn6Addr localAddr;
    u16       remotePort;
    u16       localPort;
    s32       sendMax;
    s32       recvNext;
    OSTime    expire;
    // OSAlarm takes 40 bytes, so avoid it as well
    // OSAlarm  timeWaitAlarm;
} TCPTimeWaitInfo;

typedef struct TCPTimeWaitControl
{
    TCPTimeWaitInfo* array;
    TCPTimeWaitInfo* end;
    TCPTimeWaitInfo* head;
    s32              used;
    s32              max;
} TCPTimeWaitControl;

#define NEXT(twInfo)    (((twInfo) + 1 == Control.end) ? Control.array : (twInfo) + 1)

static TCPTimeWaitControl Control;

static TCPTimeWaitInfo* CreateTimeWaitInfo(void)
{
    TCPTimeWaitInfo* twInfo;

    if (Control.used < Control.max)
    {
        twInfo = Control.head + Control.used;
        ++Control.used;
        if (Control.end <= twInfo)
        {
            twInfo -= Control.max;
        }
    }
    else if (Control.array != NULL)
    {
        // Discard the oldest one XXX Should not happen...
        twInfo = Control.head;
        Control.head = NEXT(Control.head);
    }
    else
    {
        // Time-wait buffer is not specified. XXX Should not happen...
        twInfo = NULL;
    }
    return twInfo;
}

s32 TCPSetTimeWaitBuffer(void* buffer, s32 len)
{
    BOOL enabled;

    if (buffer && len < sizeof(TCPTimeWaitInfo))
    {
        return IP_ERR_INVALID;
    }

    enabled = OSDisableInterrupts();

    if (Control.array)
    {
        memset(Control.array, 0, Control.max * sizeof(TCPTimeWaitInfo));
    }

    Control.head = Control.array = buffer;
    Control.used = 0;
    Control.max = (s32) (len / sizeof(TCPTimeWaitInfo));
    Control.end = Control.head + Control.max;

    OSRestoreInterrupts(enabled);

    return IP_ERR_NONE;
}

static BOOL IsExpired(TCPTimeWaitInfo* twInfo, OSTime now)
{
    return (twInfo->expire <= now || twInfo->localPort == 0 || twInfo->remotePort == 0) ? TRUE : FALSE;
}

static void DiscardExpiredTimeWaitInfo(OSTime now)
{
    s32              i;
    s32              expired;
    TCPTimeWaitInfo* twInfo;

    // Discard expired entries
    expired = 0;
    for (twInfo = Control.head, i = 0;
         i < Control.used;
         twInfo = NEXT(twInfo), ++i)
    {
        if (IsExpired(twInfo, now))
        {
            ++expired;
        }
        else
        {
            break;
        }
    }
    if (0 < expired)
    {
        Control.head += expired;
        if (Control.end <= Control.head)
        {
            Control.head -= Control.max;
        }
        Control.used -= expired;
    }
}

static TCPTimeWaitInfo* LookupTimeWaitInfo4(const u8* src, u16 srcPort, const u8* dst, u16 dstPort)
{
    s32              i;
    TCPTimeWaitInfo* twInfo;

    for (twInfo = Control.head, i = 0;
         i < Control.used;
         twInfo = NEXT(twInfo), ++i)
    {
        if (twInfo->remotePort != srcPort ||
            twInfo->localPort != dstPort ||
            IP_ADDR_NE(&twInfo->remoteAddr.addr[12], src) ||
            IP_ADDR_NE(&twInfo->localAddr.addr[12], dst) ||
            !SO_IN6_IS_ADDR_V4MAPPED(&twInfo->remoteAddr) ||
            !SO_IN6_IS_ADDR_V4MAPPED(&twInfo->localAddr))
        {
            continue;
        }

        return twInfo;
    }
    return NULL;
}

#ifdef IP_INET6
static TCPTimeWaitInfo* LookupTimeWaitInfo6(const SOIn6Addr* src, u16 srcPort, const SOIn6Addr* dst, u16 dstPort)
{
    s32              i;
    TCPTimeWaitInfo* twInfo;

    for (twInfo = Control.head, i = 0;
         i < Control.used;
         twInfo = NEXT(twInfo), ++i)
    {
        if (twInfo->remotePort != srcPort ||
            twInfo->localPort != dstPort ||
            !SO_IN6_ARE_ADDR_EQUAL(&twInfo->remoteAddr, src) ||
            !SO_IN6_ARE_ADDR_EQUAL(&twInfo->localAddr, dst))
        {
            continue;
        }

        return twInfo;
    }
    return NULL;
}
#endif  // IP_INET6

BOOL TCP4LookupTimeWaitInfo(const u8* src, u16 srcPort, const u8* dst, u16 dstPort)
{
    DiscardExpiredTimeWaitInfo(OSGetTime());
    return LookupTimeWaitInfo4(src, srcPort, dst, dstPort) ? TRUE : FALSE;
}

#ifdef IP_INET6
BOOL TCP6LookupTimeWaitInfo(const SOIn6Addr* src, u16 srcPort, const SOIn6Addr* dst, u16 dstPort)
{
    DiscardExpiredTimeWaitInfo(OSGetTime());
    return LookupTimeWaitInfo6(src, srcPort, dst, dstPort) ? TRUE : FALSE;
}
#endif  // IP_INET6

s32 TCPTestTimeWait(IPInterface* interface, void* ip, TCPHeader* tcp, s32 len)
{
    OSTime           now;
    s32              segLen;
    TCPTimeWaitInfo* twInfo = NULL;
    TCPTimeWaitInfo* twExtended;
    IPHeader*        ip4;
#ifdef IP_INET6
    IP6Hdr*          ip6;
#endif  // IP_INET6

    now = OSGetTime();
    DiscardExpiredTimeWaitInfo(now);

    // Look for a match from (ip->src, tcp->src, ip->dst, tcp->dst)
    switch (IP_VERSION(ip))
    {
      case 4:
        ip4 = ip;
        twInfo = LookupTimeWaitInfo4(ip4->src, tcp->src, ip4->dst, tcp->dst);
        break;
#ifdef IP_INET6
      case 6:
        ip6 = ip;
        twInfo = LookupTimeWaitInfo6(&ip6->src, tcp->src, &ip6->dst, tcp->dst);
        break;
#endif  // IP_INET6
    }
    if (twInfo == NULL)
    {
        return -1;
    }

    // Found a match

    // Test acceptability
    segLen = TCPGetSegmentLength(tcp, len);
    if (twInfo->recvNext == tcp->seq)
    {
        if (tcp->flag & TCP_FLAG_RST)
        {
            // If the RST bit is set then, enter the CLOSED state, delete the
            // TCB, and return. [RFC 793]

            // Delete twInfo virtually
            twInfo->remotePort = twInfo->localPort = 0;
            return TCP_STATE_CLOSED;
        }

        if (!(tcp->flag & TCP_FLAG_ACK) || (tcp->flag & TCP_FLAG_URG))
        {
            // drop the segment and return
            return TCP_STATE_TIME_WAIT;
        }

        // Check ACK (This is not clearly documented in RFC 793)
        if (TCP_SEQ_GT(twInfo->sendMax, tcp->ack))   // something not yet sent (SEG.ACK > SND.NXT)?
        {
            goto SendAck;
        }

        if (0 < segLen)
        {
            // drop the segment and return
            return TCP_STATE_TIME_WAIT;
        }
    }

    if (tcp->flag & TCP_FLAG_RST)
    {
        return TCP_STATE_TIME_WAIT;
    }

    if (tcp->flag & TCP_FLAG_SYN)
    {
        // Follow RFC 1122 4.2.2.13
        if (TCP_SEQ_GE(twInfo->recvNext, tcp->seq) &&
            !(tcp->flag & TCP_FLAG_ACK))
        {
            // SYN is not an old duplicate.
            // Delete twInfo virtually
            twInfo->remotePort = twInfo->localPort = 0;
            return TCP_STATE_CLOSED;
        }
        goto SendAck;
    }

    // Test Retransmission
    if (twInfo->recvNext != tcp->seq + segLen)
    {
        goto SendAck;
    }

    if (!(tcp->flag & TCP_FLAG_ACK) || !(tcp->flag & TCP_FLAG_FIN))
    {
        // drop the segment and return
        return TCP_STATE_TIME_WAIT;
    }

    // Acknowledge FIN, and restart the 2 MSL timeout.

    // Extend timer (by creating new entry and clear the current one)
    twExtended = CreateTimeWaitInfo();
    memmove(twExtended, twInfo, sizeof(TCPTimeWaitInfo));
    twExtended->expire = now + interface->closeWaitInterval;
    twInfo->remotePort = twInfo->localPort = 0;
    twInfo = twExtended;

    // Send ACK but ignore RST segments [RFC 1337]
SendAck:
    TCPRespond(interface, NULL, ip, tcp,
               twInfo->sendMax, twInfo->recvNext,
               (TCP_MIN_HLEN << 10) | TCP_FLAG_ACK,
               (u16) 0);    // recvWin := 0 XXX okay ???
    return TCP_STATE_TIME_WAIT;
}

// Start time-wait timer
void TCPStartTimeWait(IPInterface* interface, TCPObj* info, void* ip, TCPHeader* tcp)
{
    TCPTimeWaitInfo* twInfo;
    OSTime           expire;
    IPHeader*        ip4;
#ifdef IP_INET6
    IP6Hdr*          ip6;
#endif  // IP_INET6

#ifndef IP_INET6
    ASSERT(IP_VERSION(ip) == 4);
#else
    ASSERT(IP_VERSION(ip) == 4 || IP_VERSION(ip) == 6);
#endif  // IP_INET6

    expire = OSGetTime() + interface->closeWaitInterval;

    // Turn off other timers
    // OSCancelAlarm(&info->ackAlarm);
    TCPCancelRxmitTimer(info);

    // Create a TCPTimeWaitInfo entry
    twInfo = CreateTimeWaitInfo();
    if (twInfo)
    {
        switch (IP_VERSION(ip))
        {
          case 4:
            ip4 = ip;
            memset(twInfo->remoteAddr.addr, 0, 10);
            *(u16*) &twInfo->remoteAddr.addr[10] = 0xffff;
            memmove(twInfo->remoteAddr.addr + 12, ip4->src, IP_ALEN);
            ASSERT(SO_IN6_IS_ADDR_V4MAPPED(&twInfo->remoteAddr));
            memset(twInfo->localAddr.addr, 0, 10);
            *(u16*) &twInfo->localAddr.addr[10] = 0xffff;
            memmove(twInfo->localAddr.addr + 12, ip4->dst, IP_ALEN);
            ASSERT(SO_IN6_IS_ADDR_V4MAPPED(&twInfo->localAddr));
            break;
#ifdef IP_INET6
          case 6:
            ip6 = ip;
            twInfo->remoteAddr = ip6->src;
            twInfo->localAddr = ip6->dst;
            break;
#endif  // IP_INET6
        }
        twInfo->remotePort = tcp->src;
        twInfo->localPort = tcp->dst;
        twInfo->sendMax = info->sendMax;
        twInfo->recvNext = info->recvNext;
        twInfo->expire = expire;
    }

    // Send ACK
    if (TCP_SEQ_GT(info->recvAcked, info->recvNext))
    {
        info->lastSend = OSGetTime();
        info->recvAcked = info->recvNext;
        TCPRespond(interface, NULL, ip, tcp,
                   info->sendMax, info->recvNext,
                   (TCP_MIN_HLEN << 10) | TCP_FLAG_ACK,
                   (u16) (u16) info->recvWin);
    }

    // Close info
    TCPAbortAs(info, TCP_STATE_TIME_WAIT);
}

void TCPDeleteTimeWaitInfo(TCPInfo* tcp)
{
    TCPTimeWaitInfo* twInfo = 0;
    IPSocket* local;
    IPSocket* remote;
#ifdef IP_INET6
    SOSockAddrIn6* local6;
    SOSockAddrIn6* remote6;
#endif  // IP_INET6

    // Look for a match from (ip->src, tcp->src, ip->dst, tcp->dst)
    switch (tcp->info.family)
    {
      case SO_AF_INET:
        local = IPGetLocalSockAddr(&tcp->info);
        remote = IPGetRemoteSockAddr(&tcp->info);
        twInfo = LookupTimeWaitInfo4(remote->addr, remote->port, local->addr, local->port);
        break;
#ifdef IP_INET6
      case SO_AF_INET6:
        local6 = IPGetLocalSockAddr(&tcp->info);
        remote6 = IPGetRemoteSockAddr(&tcp->info);
        twInfo = LookupTimeWaitInfo6(&remote6->addr, remote6->port, &local6->addr, local6->port);
        break;
#endif  // IP_INET6
    }
    if (twInfo == NULL)
    {
        return;
    }

    // Delete twInfo virtually
    twInfo->remotePort = twInfo->localPort = 0;
}

s32 TCPReportTimeWait(IPInterface* interface, void* optval, int* optlen)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused( interface )
#endif // IOP_OS
    
    int              i;
    int              len;
    TCPTimeWaitInfo* info;
    TCPEntry*        tcp;
    OSTime           now = OSGetTime();

    len = 0;
    tcp = optval;
    for (info = Control.head, i = 0;
         i < Control.used;
         info = NEXT(info), ++i)
    {
        if (*optlen < len + sizeof(TCPEntry))
        {
            break;
        }
        if (IsExpired(info, now))
        {
            continue;
        }
        if (!SO_IN6_IS_ADDR_V4MAPPED(&info->remoteAddr))
        {
            continue;
        }
        if (IP4LookupInfo(&TCPInfoQueue,
                          info->remoteAddr.addr + 12, info->localAddr.addr + 12,
                          info->remotePort, info->localPort, 0))
        {
            continue;
        }

        tcp->state = TCP_STATE_TIME_WAIT;
        tcp->local.len = tcp->remote.len = sizeof(SOSockAddrIn);
        tcp->local.family = tcp->remote.family = SO_PF_INET;
        tcp->local.port = info->localPort;
        tcp->remote.port = info->remotePort;
        memcpy(&tcp->local.addr, info->localAddr.addr + 12, IP_ALEN);
        memcpy(&tcp->remote.addr, info->remoteAddr.addr + 12, IP_ALEN);
        len += sizeof(TCPEntry);
        ++tcp;
    }
    *optlen = len;
    return IP_ERR_NONE;
}

int TCPReportTimeWaitNumber(IPInterface* interface)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused( interface )
#endif // IOP_OS
    
    int              i;
    int              tcp;
    TCPTimeWaitInfo* info;
    OSTime           now = OSGetTime();

    tcp = 0;
    for (info = Control.head, i = 0;
         i < Control.used;
         info = NEXT(info), ++i)
    {
        if (IsExpired(info, now))
        {
            continue;
        }
        if (!SO_IN6_IS_ADDR_V4MAPPED(&info->remoteAddr))
        {
            continue;
        }
        if (IP4LookupInfo(&TCPInfoQueue,
                          info->remoteAddr.addr + 12, info->localAddr.addr + 12,
                          info->remotePort, info->localPort, 0))
        {
            continue;
        }
        ++tcp;
    }
    return tcp;
}

#ifdef IP_INET6
s32 TCP6ReportTimeWait(IPInterface* interface, void* optval, int* optlen)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused( interface )
#endif // IOP_OS
    
    int              i;
    int              len;
    TCPTimeWaitInfo* info;
    TCP6Entry*       tcp;
    OSTime           now = OSGetTime();

    len = 0;
    tcp = optval;
    for (info = Control.head, i = 0;
         i < Control.used;
         info = NEXT(info), ++i)
    {
        if (*optlen < len + sizeof(TCP6Entry))
        {
            break;
        }
        if (IsExpired(info, now))
        {
            continue;
        }
        if (SO_IN6_IS_ADDR_V4MAPPED(&info->remoteAddr))
        {
            continue;
        }
        if (IP6LookupInfo(&TCPInfoQueue,
                          &info->remoteAddr, &info->localAddr,
                          info->remotePort, info->localPort, 0))
        {
            continue;
        }

        tcp->state = TCP_STATE_TIME_WAIT;
        tcp->local.len = tcp->remote.len = sizeof(SOSockAddrIn6);
        tcp->local.family = tcp->remote.family = SO_PF_INET6;
        tcp->local.port = info->localPort;
        tcp->remote.port = info->remotePort;
        tcp->local.addr = info->localAddr;
        tcp->remote.addr = info->remoteAddr;
        len += sizeof(TCP6Entry);
        ++tcp;
    }
    *optlen = len;
    return IP_ERR_NONE;
}

int TCP6ReportTimeWaitNumber(IPInterface* interface)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused( interface )
#endif // IOP_OS
    
    int              i;
    int              tcp;
    TCPTimeWaitInfo* info;
    OSTime           now = OSGetTime();

    tcp = 0;
    for (info = Control.head, i = 0;
         i < Control.used;
         info = NEXT(info), ++i)
    {
        if (IsExpired(info, now))
        {
            continue;
        }
        if (SO_IN6_IS_ADDR_V4MAPPED(&info->remoteAddr))
        {
            continue;
        }
        if (IP6LookupInfo(&TCPInfoQueue,
                          &info->remoteAddr, &info->localAddr,
                          info->remotePort, info->localPort, 0))
        {
            continue;
        }
        ++tcp;
    }
    return tcp;
}

#endif // IP_INET6
