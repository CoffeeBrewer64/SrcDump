/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPTcpUser.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPTcpUser.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    70    2/27/06 15:09 Shiki
    Modified to count TCPNumber and TCP6Number.

    69    2/21/06 17:46 Shiki
    Fixed TCPAbortAs() to remove the closed TCPObj from TCPInfoQueue.

    68    2/17/06 14:45 Shiki
    Fixed TCPReport() and TCP6Report().

    67    2/15/06 14:46 Shiki
    Added TCPReport and TCP6Report.

    66    2/15/06 11:23 Shiki
    Modified to collect more tcpStat.

    65    2/14/06 10:01 Shiki
    Modified TCPGetObj() to use interface->closeWaitInterval.
    Revised TCPConnectAsync() and TCPSocket() to call TCPInitRtt() only
    after the interface is selected.

    64    2/09/06 14:34 Shiki
    Fixed TIME-WAIT state management when time wait buffer is no available.

    63    2/08/06 10:52 Shiki
    Added support for SO_TCP_STDURG.

    62    2/06/06 11:43 Shiki
    Fixed TCPConnectAsync() to set the correct MSS value for a IPv6 socket.

    61    2/01/06 16:25 Shiki
    Added full support of IPv6 PMTU discovery.
    Modified TCPSetSockOpt() to support SO_TCP_MAXSEG option.

    60    1/23/06 10:21 Shiki
    Fixed MSS management of IPv6.

    59    1/20/06 17:07 Shiki
    Revised TCPSetSockOpt() to check SO_IPV6_UNICAST_HOPS option.

    58    1/11/06 14:42 Shiki
    Fixed IPv6 to use interface->linkMTU instead of interface->mtu.

    57    12/22/05 17:26 Shiki
    Fixed TCPCloseAsync().

    56    12/22/05 17:23 Shiki
    Fixed TCPAbortAs().

    55    12/22/05 9:31 Shiki
    Fixed TIME-WAIT TCB abort/RST operations.

    54    12/21/05 17:27 Shiki
    Fixed TCPCancel() to delete TCB in TIME-WAIT state.

    53    12/20/05 10:40 Shiki
    Revised the transition from SYN_RECEIVED to FINWAIT1.

    52    12/19/05 19:12 Shiki
    Fixed the receive functions to return the stored error code when TCP
    has been closed no matter what.

    51    12/19/05 18:34 Shiki
    Fixed the receive functions to return the stored error code when TCP
    has been closed.

    50    12/13/05 20:03 Shiki
    Revised to support default TTL for RFC 3927 (1 for link-local, IP_TTL
    for others).
    Fixed to update the header field in TCPObj{} when the setting of TTL is
    changed.

    49    12/09/05 15:19 Shiki
    Implemented the limited transmit algorithm (RFC 3042).

    48    12/07/05 22:00 Shiki
    Implemented RFC 3782 (The NewReno Modification to TCP's Fast Recovery
    Algorithm).

    47    11/28/05 18:18 Shiki
    Added support for SO_EALREADY with SOConnect().

    46    04/12/07 13:51 Ueno_kyu
    Fixed TCPSocket() to initialize IP header template.

    45    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    49    04/10/21 16:59 Ueno_kyu
    Enclosed IPv6 specific codes in #ifdef IP_INET6... #endif blocks.

    48    6/29/04 9:33 Shiki
    Revised using IP_TTL.

    47    6/09/04 17:01 Shiki
    Fixed for IPv4 build.

    46    6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    44    3/03/04 14:28 Shiki
    Modified to use a TCP initial cwnd of 2 segments as allowed in RFC
    2581.

    43    2/25/04 14:49 Shiki
    Added support for delayed ACK.

    42    10/22/03 10:47 Shiki
    Modified to get ephemeral port number between 49152 and 65535 rather
    than from between 1024 and. 5000.

    41    10/20/03 15:01 Shiki
    Added support for SO_SO_SNDLOWAT and SO_SO_RCVLOWAT.

    40    10/17/03 14:54 Shiki
    Modified TCPOpen() to initialized sendLowat and recvLowat.
    Fixed SendAsync() to cancel on-going send operation in case
    SO_MSG_DONTWAIT.
    Fixed TCPCancel() not to set TCP_SO_CLOSED flag before calling
    TCPRespond().
    Modified TCPGetSockOpt() and TCPSetSockOpt() to handle SO_SO_SNDLOWAT
    and SO_SO_RCVLOWAT options.
    Modified __TCPPoll() to check sendLowat and recvLowat.

    39    8/21/03 20:58 Shiki
    Added support for SACK/FACK.

    38    5/15/03 16:12 Shiki
    Revised TCPAbort() to call callbacks more atomically (need signature in
    TCPInfo for further strict atomicity).

    37    5/13/03 12:48 Shiki
    Fixed typo.

    36    5/13/03 12:41 Shiki
    Clean up.

    35    4/10/03 16:00 Shiki
    Fixed TCPAbort() bug.

    34    4/01/03 10:19 Shiki
    Modified IP multicast logic so that a socket receives multicast
    datagrams only from the joined group.

    33    3/27/03 17:38 Shiki
    Added support for multicast.

    32    3/26/03 15:04 Shiki
    Revised TCPSendNonblock() and TCPSendUrgNonblock() to return
    IP_ERR_AGAIN error directly.
    Implemented TCP support for SOPoll().

    31    11/11/02 21:56 Shiki
    Added support for SO_MSG_DONTWAIT.

    30    11/05/02 19:40 Shiki
    Fixed a TCPCloseAsync() bug that it failed if TCPInfo had been
    half-closed with TCPShutdonw().

    29    8/05/02 11:19 Shiki
    Modified to send a RST if there is any unread received data when a
    connection is closed.

    28    7/22/02 13:56 Shiki
    Added TCP[Get/Set][Send/Recv]Buff(). Added SO_TCP_MAXSEG option.

    27    7/19/02 16:12 Shiki
    Added support for non-blocking I/O.

    26    7/18/02 15:25 Shiki
    Revised TCP R2 management code.

    25    7/05/02 16:30 Shiki
    Clean up.

    24    7/05/02 15:52 Shiki
    Fixed TCPCancel() not to return IP_ERR_NOT_EXIST for closed TCPInfo.

    23    7/04/02 12:48 Shiki
    Fixed TCPAbort() so that open callback is called for waiting TCPInfo
    with TCPAccept() when listening TCPInfo with TCPListen() is aborted.

    22    02/06/25 15:54 Shiki
    Fixed TCPReceiveAsync() and TCPPeek() to return zero rather than
    IP_ERR_CLOSING if TCP has received FIN and TCP is in the
    TCP_STATE_CLOSE_WAIT state following Posix convention.

    21    6/13/02 15:31 Shiki
    Fixed TCPAcceptAsync() and TCPConnectAsync() to return IP_ERR_INVALID
    error if either send buffer or receive buffer is not associated with
    the TCPInfo.

    Fixed TCPAbort() not to call openCallback for TCPInfo that is a
    listening TCPInfo with TCPListen().

    20    4/30/02 14:52 Shiki
    Implemented TCPOnReset() and TCPEnumInfoQueue().
    Fixed TCPReceiveAsync() semantics for shutdown socket. (it returns zero
    rather than an error)
    Fixed TCPAbort() bug in queue management.

    19    4/25/02 21:37 Shiki
    Revised TCPListen() interface with TCPListenCallback.

    18    4/23/02 15:15 Shiki
    Modified Async functions to update *result even if the function failed.
    Modified TCPBind() not to take reuse argument.
    Implemented linger timer.

    17    4/18/02 18:48 Shiki
    Fixed TCPListen() to attempt to allocate an ephemeral source port if
    required.
    Fixed TCPBind() not to call IPBind unless TCP state is CLOSED.

    16    4/18/02 9:30 Shiki
    Fixed TCP[Set|Get]SockOpt() to check info->pair.proto member.

    15    4/18/02 9:09 Shiki
    Modified TCP[Set|Get]SockOpt() to return IP_ERR_INV_OPTION error for
    unsupported options.

    14    4/15/02 15:00 Shiki
    Fixed TCPCloseAsync() to make it empty the receive buffer completely.
    Also fixed a bug in TCP_STATE_SYN_RECEIVED case.

    13    4/15/02 12:53 Shiki
    Fixed TCPPeek() to handle out-of-band byte properly.

    12    4/12/02 13:10 Shiki
    Implemented initial sequence number randomizing for TCPIsn()

    11    4/09/02 17:22 Shiki
    Fixed TCPConnectAsync() to initialize info->sendUp properly.

    10    4/08/02 16:50 Shiki
    Implemented TCPGetSockOpt() and TCPSetSockOpt().
    Revised to support new IPSocket{} type.
    Added support for SOAccept() and SOListen().

    9     4/05/02 14:17 Shiki
    Fixed TCPCancel() to make it close the specified TCPInfo.

    8     4/05/02 14:09 Shiki
    Refined using 'const'.

    7     4/02/02 13:23 Shiki
    Added support for half-close and urgent mode.

    6     3/18/02 20:35 Shiki
    Modified Open() to test info for not being used.

    5     3/18/02 14:32 Shiki
    Minor clean up.

    4     3/14/02 16:07 Shiki
    Renamed TCPInfo.template to TCPInfo.header.

    3     3/13/02 21:35 Shiki
    Added TCPPeek().

    2     3/13/02 18:30 Shiki
    Revised TCPSend() so it can directly transfer user data from the user
    space to the link layer.

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
#include <stdarg.h>
#include <string.h>
#endif // IOP_OS

#include <dolphin/os.h>
#include <dolphin/socket.h>
#include "IPPrivate.h"
#ifdef IP_INET6
#include "IP6Private.h"
#endif // IP_INET6

IFQueue    TCPInfoQueue;    // for any and for fixed
int        TCPNumber;
int        TCP6Number;
static u16 Port = 49152;    // 49152-65535. 0 reserved as any.

TCPObj* TCPGetObj(TCPInfo* tcp)
{
    TCPObj *obj;

    switch (tcp->info.family)
    {
      case SO_PF_INET:
        obj = &tcp->obj;
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        obj = &((TCP6Info*) tcp)->obj;
        break;
#endif  // IP_INET6
      default:
        return NULL;
    }

    if (obj->state == TCP_STATE_TIME_WAIT)
    {
        ASSERT(obj->interface);
        if (obj->lastSend + obj->interface->closeWaitInterval <= OSGetTime())
        {
            obj->state = TCP_STATE_CLOSED;
        }
    }
    return obj;
}

void TCPEnumInfoQueue(TCPCallback callback)
{
    IPInfo* info;
    IPInfo* next;

    IFIterateQueue(IPInfo*, &TCPInfoQueue, info, next, link)
    {
        callback((TCPInfo*) info, IP_ERR_NONE);
    }
}

static void NullCallback(TCPInfo* tcp, s32 result)
{
#ifdef IOP_OS
    TCPIP_UNUSED(tcp);
    TCPIP_UNUSED(result);    
#else
    #pragma unused(tcp, result)
#endif // IOP_OS
}

static void SyncCallback(TCPInfo* tcp, s32 result)
{
#ifdef IOP_OS
    TCPIP_UNUSED(result);    
#else
    #pragma unused(result)
#endif // IOP_OS
    
    OSWakeupThread(&TCPGetObj(tcp)->queueThread);
}

s32 TCPGetState(TCPInfo* tcp)
{
    TCPObj *obj = TCPGetObj(tcp);

    if (tcp->info.proto != IP_PROTO_TCP || !obj)
    {
        return IP_ERR_INVALID;
    }
    return obj->state;
}

// getpeername
s32 TCPGetRemoteSocket(TCPInfo* tcp, IPSocket* socket)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        rc = IPGetRemoteSocket(&tcp->info, socket);
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

// getsockname
s32 TCPGetLocalSocket(TCPInfo* tcp, IPSocket* socket)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        rc = IPGetLocalSocket(&tcp->info, socket);
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPBind(TCPInfo* tcp, const void* socket)
{
    BOOL    enabled;
    s32     rc;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        rc = IP_ERR_INVALID;
    }
    else if (info->state != TCP_STATE_CLOSED)
    {
        rc = IP_ERR_INVALID;
    }
    else if (tcp->info.family == SO_PF_INET)
    {
        if (IP_CLASSD(((IPSocket*) socket)->addr))
        {
            rc = IP_ERR_INV_SOCKET;
        }
        else
        {
            rc = IP4Bind(&TCPInfoQueue, &tcp->info, socket,
                        (info->flag & TCP_SO_REUSE) ? TRUE : FALSE);
            if (rc == IP_ERR_NONE)
            {
                // Initialize IP header template
                IPHeader* header = (IPHeader*) &info->header[0];
                IPSocket* sockAddr = IPGetLocalSockAddr(&tcp->info);
                memmove(header->src, sockAddr->addr, IP_ALEN);
                if (tcp->info.ttl)
                {
                    header->ttl = tcp->info.ttl;
                }
                else
                {
                    header->ttl = (u8) (IPIsLinkLocalAddr(NULL, sockAddr->addr) ? 1 : IP_TTL);
                }
            }
        }
    }
#ifdef IP_INET6
    else if (tcp->info.family == SO_PF_INET6)
    {
        if (SO_IN6_IS_ADDR_MULTICAST(&((SOSockAddrIn6*) socket)->addr))
        {
            rc = IP_ERR_INV_SOCKET;
        }
        else
        {
            rc = IP6Bind(&TCPInfoQueue, &tcp->info, socket,
                        (info->flag & TCP_SO_REUSE) ? TRUE : FALSE);
            if (rc == IP_ERR_NONE)
            {
                // Initialize IP header template
                IP6Hdr* header6 = (IP6Hdr*) &info->header[0];
                SOSockAddrIn6* sockAddr6 = IPGetLocalSockAddr(&tcp->info);
                header6->src = sockAddr6->addr;
                if (tcp->info.ttl)
                {
                    header6->hops = tcp->info.ttl;
                }
            }
        }
    }
#endif
    else
    {
        rc = IP_ERR_INVALID;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

BOOL TCPAbort(TCPObj* info)
{
    return TCPAbortAs(info, TCP_STATE_CLOSED);
}

BOOL TCPAbortAs(TCPObj* info, s32 nextState)
{
    TCPCallback callbackTable[5];
    TCPCallback callback;
    s32         state;
    int         i;

    ASSERT(info->pair->proto == IP_PROTO_TCP);
    if (info->pair->proto != IP_PROTO_TCP)
    {
        return FALSE;
    }

    if (nextState == TCP_STATE_CLOSED)
    {
        switch (info->state)
        {
          case TCP_STATE_SYN_SENT:
          case TCP_STATE_SYN_RECEIVED:
            ASSERT(info->interface);
            ++info->interface->tcpStat.attemptFails;
            break;
          case TCP_STATE_ESTABLISHED:
          case TCP_STATE_CLOSE_WAIT:
            ASSERT(info->interface);
            ++info->interface->tcpStat.estabResets;
            --info->interface->tcpStat.currEstab;
            break;
        }
    }
    state = info->state;
    info->state = nextState;

//  The following line prevents normal SORead return zero. [4/10/2003]
//  info->flag |= TCP_SO_SH_RECEIVE | TCP_SO_SH_SEND;

    // Cancel datagram:
    //   If info->datagram is in IP/ARP pending queue, it must be
    //   removed from the queue before aborting the operation.
    IPCancel(&info->datagram);

    TCPCancelRxmitTimer(info);
    OSCancelAlarm(&info->dackAlarm);
    OSCancelAlarm(&info->lingerAlarm);

    while (!IFIsEmptyQueue(&info->queueListen))
    {
        TCPObj* log;

        log = (TCPObj*) IFQueryQueueHead(&info->queueListen);
        ASSERT(log->listening == info);
        ASSERT(log->state == TCP_STATE_LISTEN);

        // Abort accept operation
        log->err = info->err;
        TCPAbort(log);
    }

    if (info->listening)
    {
        IFDequeueItem(TCPObj*, &info->listening->queueListen, info, linkListen);
        info->listening = NULL;
        ASSERT(state == TCP_STATE_LISTEN);
        IFEnqueueHead(IPInfo*, &TCPInfoQueue, info->pair, link);
        switch (info->pair->family)
        {
          case SO_AF_INET:
            ++TCPNumber;
            break;
          case SO_AF_INET6:
            ++TCP6Number;
            break;
        }
    }
    else if (state == TCP_STATE_LISTEN)
    {
        // info is a listening TCPInfo with TCPListen().
        // Don't have to call openCallback anymore.
        info->openCallback = NullCallback;
    }

    if (!(info->flag & TCP_SO_ABORTED) && nextState == TCP_STATE_CLOSED)
    {
        IFDequeueItem(IPInfo*, &TCPInfoQueue, info->pair, link);
        switch (info->pair->family)
        {
          case SO_AF_INET:
            --TCPNumber;
            break;
          case SO_AF_INET6:
            --TCP6Number;
            break;
        }
        info->flag |= TCP_SO_ABORTED;
    }

    if (info->flag & TCP_SO_CLOSED)
    {
        if (!(info->flag & TCP_SO_ABORTED))
        {
            IFDequeueItem(IPInfo*, &TCPInfoQueue, info->pair, link);
            switch (info->pair->family)
            {
              case SO_AF_INET:
                --TCPNumber;
                break;
              case SO_AF_INET6:
                --TCP6Number;
                break;
            }
            info->flag |= TCP_SO_ABORTED;
        }
        info->pair->proto = 0;
        IPClose(info->pair);
    }

    // Call every pending callbacks
    if (info->openResult)
    {
        *info->openResult = info->err;
        info->openResult = NULL;
    }
    if (info->sendResult)
    {
        *info->sendResult = info->err;
        info->sendResult = NULL;
    }
    if (info->recvResult)
    {
        *info->recvResult = info->err;
        info->recvResult = NULL;
    }
    if (info->urgResult)
    {
        *info->urgResult = info->err;
        info->urgResult = NULL;
    }
    if (info->closeResult)
    {
        *info->closeResult = IP_ERR_NONE;
        info->closeResult = NULL;
    }

    callbackTable[0] = info->openCallback;
    info->openCallback = NULL;
    callbackTable[1] = info->sendCallback;
    info->sendCallback = NULL;
    callbackTable[2] = info->recvCallback;
    info->recvCallback = NULL;
    callbackTable[3] = info->urgCallback;
    info->urgCallback = NULL;
    callbackTable[4] = info->closeCallback;
    info->closeCallback = NULL;

    for (i = 0; i < 4; ++i)
    {
        callback = callbackTable[i];
        if (callback)
        {
            callback((TCPInfo*) info->pair, info->err);
        }
    }

    // Call closeCallback
    callback = callbackTable[4];
    if (callback)
    {
        callback((TCPInfo*) info->pair, IP_ERR_NONE);
    }

    // Wakeup SOPoll()
    if (0 < info->pair->poll)
    {
        __IPWakeupPollingThreads();
    }

    return TRUE;
}

s32 TCPSetSendBuff(TCPInfo* tcp, void* sendbuf, s32 sendbufLen)
{
    BOOL    enabled;
    s32     rc;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP ||
        info->state != TCP_STATE_CLOSED ||
        sendbufLen < 0)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        rc = IP_ERR_NONE;
        info->sendBuff = sendbufLen;
        info->sendPtr = info->sendData = sendbuf;
        info->sendLowat = MAX(1, MIN(info->sendLowat, sendbufLen));
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPSetRecvBuff(TCPInfo* tcp, void* recvbuf, s32 recvbufLen)
{
    BOOL    enabled;
    s32     rc;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP ||
        info->state != TCP_STATE_CLOSED ||
        recvbufLen < 0)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        rc = IP_ERR_NONE;
        info->recvBuff = recvbufLen;
        info->recvPtr = info->recvData = recvbuf;
        info->recvWin = info->recvBuff;
        info->recvLowat = MAX(1, MIN(info->recvLowat, recvbufLen));
   }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPGetSendBuff(TCPInfo* tcp, void** sendbuf, s32* sendbufLen)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        TCPObj* info;

        rc = IP_ERR_NONE;
        info = TCPGetObj(tcp);
        if (sendbufLen)
        {
            *sendbufLen = info->sendBuff;
        }
        if (sendbuf)
        {
            *sendbuf = info->sendData;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPGetRecvBuff(TCPInfo* tcp, void** recvbuf, s32* recvbufLen)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        TCPObj* info;

        rc = IP_ERR_NONE;
        info = TCPGetObj(tcp);
        if (recvbufLen)
        {
            *recvbufLen = info->recvBuff;
        }
        if (recvbuf)
        {
            *recvbuf = info->recvData;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPOpen(TCPInfo* tcp,
            void* sendbuf, s32 sendbufLen,
            void* recvbuf, s32 recvbufLen)
{
    s32 rc;

    rc = TCPSocket(SO_AF_INET, tcp);
    if (0 <= rc)
    {
        TCPSetSendBuff(tcp, sendbuf, sendbufLen);
        TCPSetRecvBuff(tcp, recvbuf, recvbufLen);
    }
    return IP_ERR_NONE;
}

s32 TCPSocket(int af, TCPInfo* tcp)
{
    BOOL      enabled;
    BOOL      used;
    IPHeader* header;
#ifdef IP_INET6
    IP6Hdr*   header6;
#endif  // IP_INET6
    IPSocket* local;
    IPSocket* remote;
#ifdef IOP_OS
    TCPObj*   info = NULL;
#else
    TCPObj*   info;
#endif // IOP_OS
    
#ifdef IP_INET6
    if (tcp == NULL || (af != SO_AF_INET && af != SO_AF_INET6))
#else
    if (tcp == NULL || af != SO_AF_INET)
#endif
    {
        return IP_ERR_INVALID;
    }

    enabled = OSDisableInterrupts();
    used = __IPIsMember(&TCPInfoQueue, &tcp->info);
    OSRestoreInterrupts(enabled);
    if (used)
    {
        return IP_ERR_EXIST;
    }

    switch (af)
    {
      case SO_AF_INET:
        memset(tcp, 0, sizeof(TCPInfo));
        tcp->info.family = (u8) af;
        tcp->info.proto = IP_PROTO_TCP;

        local = IPGetLocalSockAddr(&tcp->info);
        remote = IPGetRemoteSockAddr(&tcp->info);
        local->len = remote->len = IP_SOCKLEN;
        local->family = remote->family = (u8) af;

        // Initialize IP header template
        info = TCPGetObj(tcp);
        header = (IPHeader*) &info->header[0];
        header->verlen = IP_VERHLEN;
        header->tos    = 0;
        header->len    = (u16) (IP_HLEN(header) + TCP_MIN_HLEN);
        header->ttl    = IP_TTL;
        header->proto  = IP_PROTO_TCP;
        header->frag   = IP_DF;   // Don't fragment since path MTU discovery is deployed.

        info->mss = info->mssBase = 576 - IP_MIN_HLEN - TCP_MIN_HLEN;   // IP minimal
        break;
#ifdef IP_INET6
      case SO_AF_INET6:
        memset(tcp, 0, sizeof(TCP6Info));
        tcp->info.family = (u8) af;
        tcp->info.proto = IP_PROTO_TCP;

        local = IPGetLocalSockAddr(&tcp->info);
        remote = IPGetRemoteSockAddr(&tcp->info);
        local->len = remote->len = sizeof(SOSockAddrIn6);
        local->family = remote->family = (u8) af;

        // Initialize IP header template
        info = TCPGetObj(tcp);
        header6 = (IP6Hdr*) &info->header[0];
        header6->flow = 6 << 28;
        header6->plen = 0;
        header6->next = IP_PROTO_TCP;
        header6->hops = 255;

        info->mss = info->mssBase = IP6_MIN_MTU - (s32) sizeof(IP6Hdr) - TCP_MIN_HLEN;
        break;
#endif  // IP_INET6
    }

    // Initialize info and enqueue it
    tcp->info.tos = 0;      // Default
    tcp->info.ttl = 0;      // Default (0 for link-local, IP_TTL for others)
    tcp->info.mttl = 1;     // Default

    tcp->info.poll = 0;
    tcp->info.flag = IP_INFO_FLAG_MCASTLOOP;

    OSInitThreadQueue(&info->queueThread);

    info->state = TCP_STATE_CLOSED;
    info->err   = 0;

    info->cWin     = TCP_IW(info);
    info->ssThresh = TCP_DEF_SSTHRESH;
    info->lastSend = OSGetTime();

    info->flag     = TCP_SO_NAGLE | TCP_SO_OOB;

    // Old telnet terminals did send garbage 'win' without an ACK...
    // However, info->sendWin must be set here as TCPSendSize() refers to it.
    // Set it 536 since a host is required to receive a datagram smaller than
    // or equal to 576 bytes.
    info->sendWin  = info->mss;  // IP minimal

    info->r2 = OSSecondsToTicks((OSTime) 100);    // RFC 1122 4.2.3.5. Note R2 for SYN is handled separately.

    OSCreateAlarm(&info->rxmitAlarm);
    OSCreateAlarm(&info->dackAlarm);

    // Linger
    info->linger = 0;
    OSCreateAlarm(&info->lingerAlarm);

    IFInitQueue(&info->queueListen);

    // Send/receive low water marks
    info->sendLowat = 1;
    info->recvLowat = 1;

    info->pair = &tcp->info;

    //
    // Socket layer initialization
    //
    IFInitQueue(&info->queueBacklog);
    IFInitQueue(&info->queueCompleted);
    info->accepting = 0;

    enabled = OSDisableInterrupts();
    IFEnqueueTail(IPInfo*, &TCPInfoQueue, &tcp->info, link);
    switch (af)
    {
      case SO_AF_INET:
        ++TCPNumber;
        break;
      case SO_AF_INET6:
        ++TCP6Number;
        break;
    }
    OSRestoreInterrupts(enabled);

    return IP_ERR_NONE;
}

/*---------------------------------------------------------------------------*
  Name:         TCPListen

  Description:  Passively wait for the connection establishment.

  Arguments:    tcp        Pointer to TCPInfo
                callback    Informed when a connection request is arrived

  Returns:      IP_ERR_NONE if successed.
 *---------------------------------------------------------------------------*/
s32 TCPListen(TCPInfo* tcp,
              void* local, void* remote,
              TCPListenCallback callback, s32* result)
{
    BOOL    enabled;
    s32     rc;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        rc = IP_ERR_INVALID;
    }
    else if (info->state != TCP_STATE_CLOSED)
    {
        rc = IP_ERR_EXIST;
    }
    else
    {
        SOSockAddrIn* sockAddr;

        sockAddr = IPGetLocalSockAddr(&tcp->info);
        if (sockAddr->port == 0)
        {
            // Assign an ephemeral source port number
            // XXX Check time-wait tcp
            sockAddr->port = IPGetAnonPort(&TCPInfoQueue, &Port);
        }
        if (sockAddr->port == 0)
        {
            rc = IP_ERR_INS_RESOURCES;
        }
        else
        {
            // Note *result is NOT set to BUSY for TCPListen()
            rc = IP_ERR_NONE;

            info->state = TCP_STATE_LISTEN;
            info->openCallback = callback ? (TCPCallback) callback : NullCallback;
            info->openResult = result;
            info->local  = local;
            info->remote = remote;
            ASSERT(info->listening == NULL);
        }
    }
    if (result)
    {
        *result = rc;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPAcceptAsync(TCPInfo* tcp, TCPInfo* listening,
                   TCPCallback callback, s32* result)
{
    BOOL    enabled;
    s32     rc;
    TCPObj* info;
    TCPObj* objListening;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    objListening = TCPGetObj(listening);
    if (tcp->info.proto != IP_PROTO_TCP || objListening == NULL ||
        info->sendBuff == 0 || info->recvBuff == 0)
    {
        rc = IP_ERR_INVALID;
    }
    else if (info->state != TCP_STATE_CLOSED)
    {
        rc = IP_ERR_EXIST;
    }
    else if (objListening->state != TCP_STATE_LISTEN)
    {
        rc = IP_ERR_NOT_EXIST;
    }
    else
    {
        rc = IP_ERR_NONE;
        callback = callback ? callback : NullCallback;

        // Remove info from TCPInfoQueue. It will be re-inserted
        // to TCPInfoQueue when SYN segment is received in DoListen().
        IFDequeueItem(IPInfo*, &TCPInfoQueue, &tcp->info, link);
        switch (tcp->info.family)
        {
          case SO_AF_INET:
            --TCPNumber;
            break;
          case SO_AF_INET6:
            --TCP6Number;
            break;
        }

        info->listening = objListening;
        info->state = TCP_STATE_LISTEN;
        info->openCallback = callback;
        info->openResult = result;
        IFEnqueueTail(TCPObj*, &objListening->queueListen, info, linkListen);
    }
    if (result)
    {
        *result = ((rc == IP_ERR_NONE) ? IP_ERR_BUSY : rc);
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPAccept(TCPInfo* tcp, TCPInfo* listening)
{
    BOOL enabled;
    vs32 result;
    s32  rc;

    rc = TCPAcceptAsync(tcp, listening, SyncCallback, (s32*) &result);
    if (rc < 0)
    {
        return rc;
        // NOT REACHED HERE
    }

    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&TCPGetObj(tcp)->queueThread);
    }
    OSRestoreInterrupts(enabled);

    return (s32) result;
}

s32 TCPConnectAsync(TCPInfo* tcp, const void* socket,
                    TCPCallback callback, s32* result)
{
    BOOL           enabled;
    IPHeader*      header;

#ifdef IOP_OS
    s32            rc = 0;
    IPInterface*   interface = NULL;
#else
    s32            rc;
    IPInterface*   interface;
#endif // IOP_OS

    TCPObj*        info;
    IPSocket*      sockAddr;
#ifdef IP_INET6
    IP6Hdr*        header6;
    SOSockAddrIn6* sockAddr6;
#endif  // IP_INET6

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP || info->sendBuff == 0 || info->recvBuff == 0)
    {
        rc = IP_ERR_INVALID;
    }
    else if (info->state == TCP_STATE_SYN_SENT)
    {
        // To support SO_EALREADY
        rc = IP_ERR_AGAIN;
    }
    else if (info->state != TCP_STATE_CLOSED)
    {
        // Technically, it is possible moving from TCP_STATE_LISTEN to
        // TCP_STATE_SYN_SENT. However, it is basically of no use and
        // the library simply returns an error.
        rc = IP_ERR_EXIST;
    }
    else
    {
        callback = callback ? callback : NullCallback;

        switch (tcp->info.family)
        {
          case SO_PF_INET:
            rc = IP4Connect(&TCPInfoQueue, &tcp->info, socket, &Port);
            if (rc == IP_ERR_NONE)
            {
                // Initialize IP header template
                header = (IPHeader*) &info->header[0];
                sockAddr = IPGetRemoteSockAddr(&tcp->info);
                memmove(header->dst, sockAddr->addr, IP_ALEN);
                sockAddr = IPGetLocalSockAddr(&tcp->info);
                memmove(header->src, sockAddr->addr, IP_ALEN);
                interface = IPGetRoute(header->dst, NULL);
                if (tcp->info.ttl)
                {
                    header->ttl = tcp->info.ttl;
                }
                else
                {
                    header->ttl = (u8) (IPIsLinkLocalAddr(interface, header->src) ? 1 : IP_TTL);
                }
                info->mss = info->mssBase = interface->mtu - IP_MIN_HLEN - TCP_MIN_HLEN;
            }
            break;
#ifdef IP_INET6
          case SO_PF_INET6:
            rc = IP6Connect(&TCPInfoQueue, &tcp->info, socket, &Port);
            if (rc == IP_ERR_NONE)
            {
                // Initialize IP header template
                IP6Entry* nextHop;
                IP6Entry* to;

                header6 = (IP6Hdr*) &info->header[0];
                sockAddr6 = IPGetRemoteSockAddr(&tcp->info);
                header6->dst = sockAddr6->addr;
                sockAddr6 = IPGetLocalSockAddr(&tcp->info);
                header6->src = sockAddr6->addr;
                nextHop = IP6GetNextHop(&tcp->info, &header6->dst, &to);
                ASSERT(nextHop);
                ASSERT(nextHop->interface);
                interface = nextHop->interface;
                if (tcp->info.ttl)
                {
                    header6->hops = tcp->info.ttl;
                }
                else
                {
                    header6->hops = interface->curHopLimit;
                }
                info->mss = info->mssBase = interface->linkMTU - (s32) sizeof(IP6Hdr) - TCP_MIN_HLEN;   // XXX when linkMTU is modified
            }
            break;
#endif  // IP_INET6
        }

        if (rc == IP_ERR_NONE)
        {
            // Initialize tcp
            ASSERT(interface);
            info->interface = interface;
            info->err = IP_ERR_NONE;
            TCPInitRtt(info);
            info->openCallback = callback;
            info->openResult = result;

            info->iss = TCPIsn(&tcp->info);
            info->sendUna = info->iss;
            info->sendNext = info->iss; // incremented later by TCPOutput()
            info->sendMax = info->iss;
            info->sendUp = info->sendUna;

            info->sendRecover = info->sendUna;
            info->sendFack = info->sendUna;
            info->lastSack = info->sendUna;
            info->rxmitData = 0;
            info->sendAwin = 0;

            ++interface->tcpStat.activeOpens;
            info->state = TCP_STATE_SYN_SENT;

            // Send SYN
            if (result)
            {
                *result = IP_ERR_BUSY;
            }
            TCPOutput(info, 0);
        }
    }
    if (result && rc < 0)
    {
        *result = rc;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPConnect(TCPInfo* tcp, const void* socket)
{
    BOOL enabled;
    vs32 result;
    s32  rc;

    rc = TCPConnectAsync(tcp, socket, SyncCallback, (s32*) &result);
    if (rc < 0)
    {
        return rc;
        // NOT REACHED HERE
    }

    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&TCPGetObj(tcp)->queueThread);
    }
    OSRestoreInterrupts(enabled);

    return (s32) result;
}

static s32 SendAsync(TCPInfo* tcp, const void* data, s32 len, u32 flag,
                     TCPCallback callback, s32* result)
{
    BOOL    enabled;
    s32     rc;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP || len < 0)
    {
        rc = IP_ERR_INVALID;
    }
    else if (info->sendCallback)
    {
        rc = IP_ERR_BUSY;
    }
    else if ((flag & SO_MSG_OOB) && len == 0)
    {
        // [RFC 793] To send an urgent indication the user must
        // also send at least one data octet.
        rc = IP_ERR_INVALID;
    }
    else
    {
        rc = IP_ERR_NONE;
        callback = callback ? callback : NullCallback;
        switch (info->state)
        {
          case TCP_STATE_CLOSED:
            rc = IP_ERR_NOT_EXIST;
            break;
          case TCP_STATE_LISTEN:
            // XXX if remote is fully specified, go to SYN-SENT state.
            rc = IP_ERR_SOCKET_UNSPECIFIED;
            break;
          case TCP_STATE_SYN_SENT:
          case TCP_STATE_SYN_RECEIVED:
          case TCP_STATE_ESTABLISHED:
          case TCP_STATE_CLOSE_WAIT:

            if (info->flag & TCP_SO_SH_SEND)
            {
                rc = IP_ERR_CLOSING;
                break;
            }

            info->userAcked    = 0;
            info->userSendData = (u8*) data;
            info->userSendLen  = len;
            info->sendCallback = callback;
            info->sendResult   = result;
            if (result)
            {
                *result = IP_ERR_BUSY;
            }

            rc = TCPSendIn(info, (BOOL) (flag & SO_MSG_DONTWAIT));

            // [RFC 793] If the urgent flag is set, then
            // SND.UP <- SND.NXT-1 and set the urgent pointer
            // in the outgoing segments.
            //
            // However, Berkeley derived system uses SND.UP <- SND.NXT.
            if (flag & SO_MSG_OOB)    // XXX if nonblock, do not set URG if it is not copied-in.
            {
                info->sendUp = info->sendUna + info->sendLen + info->userSendLen;
                if (info->state < TCP_STATE_ESTABLISHED &&
                    info->iss == info->sendUna)
                {
                    ++info->sendUp; // for SYN
                }
            }

            if (info->userSendLen <= 0 || (flag & SO_MSG_DONTWAIT))
            {
                // All user send data has been copied-in.
                info->userSendLen = 0;
                if (info->sendResult)
                {
                    ASSERT(rc == info->userAcked);
                    *info->sendResult = rc;
                    info->sendResult = NULL;
                }
                info->sendCallback = 0;
                callback(tcp, info->userAcked);
            }

            if (info->state == TCP_STATE_ESTABLISHED ||
                info->state == TCP_STATE_CLOSE_WAIT)
            {
                TCPOutput(info, 0);
            }
            break;
          case TCP_STATE_FINWAIT1:
          case TCP_STATE_FINWAIT2:
          case TCP_STATE_CLOSING:
          case TCP_STATE_LAST_ACK:
          case TCP_STATE_TIME_WAIT:
          default:
            rc = IP_ERR_CLOSING;
            break;
        }
    }
    if (result && rc < 0)
    {
        *result = rc;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPSendAsync(TCPInfo* tcp, const void* data, s32 len,
                 TCPCallback callback, s32* result)
{
    return SendAsync(tcp, data, len, 0,
                     callback, result);
}

s32 TCPSendNonblock(TCPInfo* tcp, const void* data, s32 len)
{
    s32 result;
    s32 rc;

    rc = SendAsync(tcp, data, len, SO_MSG_DONTWAIT,
                   NULL, &result);
    if (rc == IP_ERR_NONE)
    {
        rc = result;
    }
    if (rc == 0 && 0 < len)
    {
        rc = IP_ERR_AGAIN;
    }
    return rc;
}

s32 TCPSendUrgAsync(TCPInfo* tcp, const void* data, s32 len,
                    TCPCallback callback, s32* result)
{
    return SendAsync(tcp, data, len, SO_MSG_OOB,
                     callback, result);
}

s32 TCPSendUrgNonblock(TCPInfo* tcp, const void* data, s32 len)
{
    s32 result;
    s32 rc;

    rc = SendAsync(tcp, data, len, SO_MSG_OOB | SO_MSG_DONTWAIT,
                   NULL, &result);
    if (rc == IP_ERR_NONE)
    {
        rc = result;
    }
    if (rc == 0 && 0 < len)
    {
        rc = IP_ERR_AGAIN;
    }
    return rc;
}

static s32 Send(TCPInfo* tcp, const void* data, s32 len, u32 flag)
{
    BOOL enabled;
    vs32 result;
    s32  rc;

    rc = SendAsync(tcp, data, len, flag, SyncCallback, (s32*) &result);
    if (rc < 0)
    {
        return rc;
        // NOT REACHED HERE
    }

    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&TCPGetObj(tcp)->queueThread);
    }
    OSRestoreInterrupts(enabled);

    return (s32) result;
}

s32 TCPSend(TCPInfo* tcp, const void* data, s32 len)
{
    return Send(tcp, data, len, 0);
}

s32 TCPSendUrg(TCPInfo* tcp, const void* data, s32 len)
{
    return Send(tcp, data, len, SO_MSG_OOB);
}

s32 TCPReceiveExAsync(TCPInfo* tcp, void* data, s32 len, u32 flag,
                      TCPCallback callback, s32* result)
{
    BOOL    enabled;
    BOOL    rc;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP || len < 0)
    {
        rc = IP_ERR_INVALID;
    }
    else if (info->recvCallback && !(flag & SO_MSG_DONTWAIT)) // busy
    {
        rc = IP_ERR_BUSY;
    }
    else if (info->flag & (TCP_SO_CLOSED | TCP_SO_SH_RECEIVE))
    {
        rc = IP_ERR_CLOSING;
    }
    else
    {
        rc = IP_ERR_NONE;
        callback = callback ? callback : NullCallback;
        switch (info->state)
        {
          case TCP_STATE_CLOSED:
            rc = info->err;
            if (info->flag & TCP_SO_SH_SEND)
            {
                if (rc == 0)
                {
                    if (result)
                    {
                        *result = rc;
                    }
                    callback(tcp, rc);
                }
            }
            else if (rc == 0)
            {
                rc = IP_ERR_NOT_EXIST;
            }
            break;
          case TCP_STATE_LISTEN:
          case TCP_STATE_SYN_SENT:
          case TCP_STATE_SYN_RECEIVED:
            // Special case first
            if (len == 0)
            {
                rc = 0;
                if (result)
                {
                    *result = rc;
                }
                callback(tcp, rc);
            }
            else if (flag & SO_MSG_DONTWAIT)
            {
                rc = IP_ERR_AGAIN;
            }
            else
            {
                // Just wait
                if (flag & SO_MSG_PEEK)
                {
                    info->flag |= TCP_SO_PEEK;
                }
                else
                {
                    info->flag &= ~TCP_SO_PEEK;
                }
                info->userData = data;
                info->userBuff = len;
                info->userLen  = 0;

                info->recvCallback = callback;
                info->recvResult = result;
                if (result)
                {
                    *result = IP_ERR_BUSY;
                }
            }
            break;
          case TCP_STATE_ESTABLISHED:
          case TCP_STATE_FINWAIT1:
          case TCP_STATE_FINWAIT2:
          case TCP_STATE_CLOSE_WAIT:    // The remote side has already sent FIN
            // Special case first
            if (len == 0)
            {
                rc = 0;
                if (result)
                {
                    *result = rc;
                }
                callback(tcp, rc);
            }
            else
            {
                BOOL urgent;

                if (flag & SO_MSG_PEEK)
                {
                    info->flag |= TCP_SO_PEEK;
                }
                else
                {
                    info->flag &= ~TCP_SO_PEEK;
                }
                info->userData = data;
                info->userBuff = len;
                info->userLen  = 0;
                rc = TCPRecvOut(info, &urgent);
                if (info->recvLowat <= rc ||
                    (0 < rc && (urgent || (flag & SO_MSG_DONTWAIT))))
                {
                    info->userLen = 0;
                    if (result)
                    {
                        *result = rc;
                    }
                    callback(tcp, rc);
                    // Let TCPOutput() send window update segment (if possible)
                    TCPOutput(info, 0);
                }
                else if (info->state == TCP_STATE_CLOSE_WAIT && info->recvUser == 0)
                {
                    // Do not wait since the remote side has already sent FIN.
                    rc = 0;
                    if (result)
                    {
                        *result = rc;
                    }
                    callback(tcp, rc);
                }
                else if (flag & SO_MSG_DONTWAIT)
                {
                    rc = IP_ERR_AGAIN;
                }
                else
                {
                    // Just wait
                    rc = IP_ERR_NONE;
                    info->recvCallback = callback;
                    info->recvResult   = result;
                    if (result)
                    {
                        *result = IP_ERR_BUSY;
                    }
                }
            }
            break;
          case TCP_STATE_CLOSING:
          case TCP_STATE_LAST_ACK:
          case TCP_STATE_TIME_WAIT:
          default:
            rc = 0;
            if (result)
            {
                *result = rc;
            }
            callback(tcp, rc);
            break;
        }
    }
    if (result && rc < 0)
    {
        *result = rc;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPReceiveEx(TCPInfo* tcp, void* data, s32 len, u32 flag)
{
    BOOL enabled;
    vs32 result;
    s32  rc;

    rc = TCPReceiveExAsync(tcp, data, len, flag, SyncCallback, (s32*) &result);
    if (rc < 0)
    {
        return rc;
        // NOT REACHED HERE
    }

    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&TCPGetObj(tcp)->queueThread);
    }
    OSRestoreInterrupts(enabled);

    return (s32) result;
}

s32 TCPReceiveAsync(TCPInfo* tcp, void* data, s32 len,
                    TCPCallback callback, s32* result)
{
    return TCPReceiveExAsync(tcp, data, len, 0, callback, result);
}

s32 TCPReceiveNonblock(TCPInfo* tcp, void* data, s32 len)
{
    s32 rc;
    s32 result;

    rc = TCPReceiveExAsync(tcp, data, len, SO_MSG_DONTWAIT,
                           NULL, &result);
    return (rc == IP_ERR_NONE) ? result : rc;
}

s32 TCPReceive(TCPInfo* tcp, void* data, s32 len)
{
    return TCPReceiveEx(tcp, data, len, 0);
}

s32 TCPPeek(TCPInfo* tcp, void* data, s32 len)
{
    BOOL    enabled;
    BOOL    rc;
    BOOL    urgent;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        rc = IP_ERR_INVALID;
    }
    else if (info->flag & (TCP_SO_CLOSED | TCP_SO_SH_RECEIVE))
    {
        rc = IP_ERR_CLOSING;
    }
    else
    {
        rc = IP_ERR_NONE;
        switch (info->state)
        {
          case TCP_STATE_CLOSED:
            rc = info->err;
            if (!(info->flag & TCP_SO_SH_SEND) && rc == 0)
            {
                rc = IP_ERR_NOT_EXIST;
            }
            break;
          case TCP_STATE_LISTEN:
          case TCP_STATE_SYN_SENT:
          case TCP_STATE_SYN_RECEIVED:
            rc = 0;
            break;
          case TCP_STATE_ESTABLISHED:
          case TCP_STATE_FINWAIT1:
          case TCP_STATE_FINWAIT2:
          case TCP_STATE_CLOSE_WAIT:    // The remote side has already sent FIN
            // Retreive the data if any
            rc = TCPPeekOut(info, data, len, TRUE, &urgent);
            if (rc <= 0)
            {
                if (info->state == TCP_STATE_CLOSE_WAIT &&
                    info->recvUser == 0)
                {
                    // Do not wait since the remote side has already sent FIN.
                    rc = 0;
                }
                else
                {
                    // Just wait
                    rc = IP_ERR_AGAIN;
                }
            }
            break;
          case TCP_STATE_CLOSING:
          case TCP_STATE_LAST_ACK:
          case TCP_STATE_TIME_WAIT:
          default:
            rc = 0;
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

// Basically record close event and move on to TCPOutput().
s32 TCPCloseAsync(TCPInfo* tcp, TCPCallback callback, s32* result)
{
    BOOL    enabled;
    s32     rc;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    callback = callback ? callback : NullCallback;
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        rc = IP_ERR_INVALID;
    }
    else if (info->flag & TCP_SO_CLOSED)
    {
        rc = IP_ERR_CLOSING;
    }
    else if (0 < info->recvUser)
    {
        info->closeCallback = callback;
        info->closeResult = result;
        if (result)
        {
            *result = IP_ERR_BUSY;
        }
        rc = TCPCancel(tcp);
    }
    else
    {
        ASSERT(info->closeCallback == NULL);
        rc = IP_ERR_NONE;
        info->flag |= TCP_SO_SH_RECEIVE | TCP_SO_SH_SEND | TCP_SO_CLOSED;

        // Just wait
        info->closeCallback = callback;
        info->closeResult = result;
        if (result)
        {
            *result = IP_ERR_BUSY;
        }

        switch (info->state)
        {
          case TCP_STATE_CLOSED:
          case TCP_STATE_LISTEN:
          case TCP_STATE_SYN_SENT:
            info->err = IP_ERR_CLOSING;
            TCPAbort(info);
            break;
          case TCP_STATE_SYN_RECEIVED:
            // We do not immediately move to TCP_STATE_FINWAIT1 here so
            // that we can still retransmit SYN if necessary.
            // DoData() and TCPCalcSendSize() checks info->closeCallback
            // to move on to FIN-WAIT-1 state.
            TCPOutput(info, 0); // To send FIN if possible
            break;
          case TCP_STATE_ESTABLISHED:
            ASSERT(info->interface);
            --info->interface->tcpStat.currEstab;
            info->state = TCP_STATE_FINWAIT1;
            TCPOutput(info, 0); // To send FIN
            break;
          case TCP_STATE_FINWAIT1:
          case TCP_STATE_FINWAIT2:
            break;
          case TCP_STATE_CLOSE_WAIT:
            ASSERT(info->interface);
            --info->interface->tcpStat.currEstab;
            info->state = TCP_STATE_LAST_ACK; // Note RFC793 page 60 is wrong. [RFC1121]
            TCPOutput(info, 0); // To send FIN
            break;
          case TCP_STATE_CLOSING:
          case TCP_STATE_LAST_ACK:
            break;
          case TCP_STATE_TIME_WAIT:
            TCPAbort(info);
            break;
          default:
            rc = IP_ERR_INVALID;
            break;
        }

        if (0 < tcp->info.poll)
        {
            __IPWakeupPollingThreads();
        }
    }
    if (result && rc < 0)
    {
        *result = rc;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPClose(TCPInfo* tcp)
{
    BOOL enabled;
    vs32 result;
    s32  rc;

    rc = TCPCloseAsync(tcp, SyncCallback, (s32*) &result);
    if (rc < 0)
    {
        return rc;
        // NOT REACHED HERE
    }

    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&TCPGetObj(tcp)->queueThread);
    }
    OSRestoreInterrupts(enabled);

    return (s32) result;
}

// Half close. Stop sending and/or receiving.
s32 TCPShutdown(TCPInfo* tcp, u32 flag)
{
    BOOL        enabled;
    BOOL        output;
    s32         rcSend;
    s32         rcRecv;
    TCPCallback callback;
    TCPObj*     info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        OSRestoreInterrupts(enabled);
        return IP_ERR_INVALID;
        // NOT REACHED HERE
    }

    output =  FALSE;
    rcRecv = IP_ERR_NONE;
    rcSend = IP_ERR_NONE;

    // Close input direction
    if (flag == TCP_SHUTDOWN_RECEIVE || flag == TCP_SHUTDOWN_BOTH)
    {
        if (0 < info->recvUser)
        {
            TCPCancel(tcp);
            OSRestoreInterrupts(enabled);
            return IP_ERR_CLOSING;
            // NOT REACHED HERE
        }

        info->flag |= TCP_SO_SH_RECEIVE;

        switch (info->state)
        {
          case TCP_STATE_CLOSED:
            rcRecv = IP_ERR_NOT_EXIST;
            break;
          case TCP_STATE_LISTEN:
          case TCP_STATE_SYN_SENT:
          case TCP_STATE_SYN_RECEIVED:
            // Notify receive callback
            callback = info->recvCallback;
            if (callback)
            {
                if (info->recvResult)
                {
                    *info->recvResult = IP_ERR_CLOSING;
                    info->recvResult = NULL;
                }
                info->recvCallback = NULL;
                callback(tcp, IP_ERR_CLOSING);
            }

            // Notify urg callback
            callback = info->urgCallback;
            if (callback)
            {
                if (info->urgResult)
                {
                    *info->urgResult = IP_ERR_CLOSING;
                    info->urgResult = NULL;
                }
                info->urgCallback = NULL;
                callback(tcp, IP_ERR_CLOSING);
            }

            info->recvUser = 0;
            break;
          case TCP_STATE_ESTABLISHED:
          case TCP_STATE_FINWAIT1:
          case TCP_STATE_FINWAIT2:
          case TCP_STATE_CLOSE_WAIT:
            // Notify receive callback
            callback = info->recvCallback;
            if (callback)
            {
                if (info->recvResult)
                {
                    *info->recvResult = IP_ERR_CLOSING;
                    info->recvResult = NULL;
                }
                info->recvCallback = NULL;
                callback(tcp, IP_ERR_CLOSING);
            }

            // Notify urg callback
            callback = info->urgCallback;
            if (callback)
            {
                if (info->urgResult)
                {
                    *info->urgResult = IP_ERR_CLOSING;
                    info->urgResult = NULL;
                }
                info->urgCallback = NULL;
                callback(tcp, IP_ERR_CLOSING);
            }

            if (0 < info->recvUser)
            {
                info->recvUser = 0;
                output = TRUE;  // To send window update segment (if required)
            }
            break;
          case TCP_STATE_CLOSING:
          case TCP_STATE_LAST_ACK:
          case TCP_STATE_TIME_WAIT:
          default:
            rcRecv = IP_ERR_CLOSING;
            break;
        }
    }

    // Close output direction
    if (flag == TCP_SHUTDOWN_SEND || flag == TCP_SHUTDOWN_BOTH)
    {
        info->flag |= TCP_SO_SH_SEND;

        switch (info->state)
        {
          case TCP_STATE_CLOSED:
            rcSend = IP_ERR_NOT_EXIST;
            break;
          case TCP_STATE_LISTEN:
          case TCP_STATE_SYN_SENT:
            info->err = IP_ERR_CLOSING;
            TCPAbort(info);
            break;
          case TCP_STATE_SYN_RECEIVED:
            // We do not immediately move to TCP_STATE_FINWAIT1 here so
            // that we can still retransmit SYN if necessary.
            // DoData() and TCPCalcSendSize() checks info->closeCallback
            // to move on to FIN-WAIT-1 state.
            output = TRUE;  // To send FIN if possible
            break;
          case TCP_STATE_ESTABLISHED:
            ASSERT(info->interface);
            --info->interface->tcpStat.currEstab;
            info->state = TCP_STATE_FINWAIT1;
            output = TRUE;  // To send FIN
            break;
          case TCP_STATE_FINWAIT1:
          case TCP_STATE_FINWAIT2:
            rcSend = IP_ERR_CLOSING;
            break;
          case TCP_STATE_CLOSE_WAIT:
            ASSERT(info->interface);
            --info->interface->tcpStat.currEstab;
            info->state = TCP_STATE_LAST_ACK; // Note RFC793 page 60 is wrong. [RFC1121]
            output = TRUE;  // To send FIN
            break;
          case TCP_STATE_CLOSING:
          case TCP_STATE_LAST_ACK:
          case TCP_STATE_TIME_WAIT:
          default:
            rcSend = IP_ERR_CLOSING;
            break;
        }

        if (0 < tcp->info.poll)
        {
            __IPWakeupPollingThreads();
        }
    }

    if (output)
    {
        TCPOutput(info, 0); // To send FIN
    }

    OSRestoreInterrupts(enabled);
    return MIN(rcSend, rcRecv);
}

// Abort current connection
s32 TCPCancel(TCPInfo* tcp)
{
    BOOL           enabled;
    s32            rc;
    IPSocket*      local;
    IPSocket*      remote;
#ifdef IP_INET6
    SOSockAddrIn6* local6;
    SOSockAddrIn6* remote6;
#endif  // IP_INET6
    TCPObj*        info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        rc = IP_ERR_NONE;
        info->flag |= TCP_SO_SH_RECEIVE | TCP_SO_SH_SEND;
        info->err = IP_ERR_RESET;
        switch (info->state)
        {
          case TCP_STATE_CLOSED:
          case TCP_STATE_LISTEN:
          case TCP_STATE_SYN_SENT:
            break;
          case TCP_STATE_SYN_RECEIVED:
          case TCP_STATE_ESTABLISHED:
          case TCP_STATE_FINWAIT1:
          case TCP_STATE_FINWAIT2:
          case TCP_STATE_CLOSE_WAIT:
            switch (tcp->info.family)
            {
              case SO_PF_INET:
                local = IPGetLocalSockAddr(&tcp->info);
                remote = IPGetRemoteSockAddr(&tcp->info);
                TCP4Respond(info->interface, NULL,
                            remote->addr, remote->port,
                            local->addr, local->port,
                            info->sendMax, 0, TCP_FLAG_RST, 0);
                break;
#ifdef IP_INET6
              case SO_PF_INET6:
                local6 = IPGetLocalSockAddr(&tcp->info);
                remote6 = IPGetRemoteSockAddr(&tcp->info);
                TCP6Respond(info->interface, NULL,
                            &remote6->addr, remote6->port,
                            &local6->addr, local6->port,
                            info->sendMax, 0, TCP_FLAG_RST, 0);
                break;
#endif  // IP_INET6
            }
            break;
          case TCP_STATE_CLOSING:
          case TCP_STATE_LAST_ACK:
            break;
          case TCP_STATE_TIME_WAIT:
            TCPDeleteTimeWaitInfo(tcp);
            break;
          default:
            break;
        }
        // Since TCPRespond() can abort tcp itself in case of simultaneous
        // open, TCP_SO_CLOSED flag must be set after calling TCPRespond().
        // Otherwise, tcp is closed twice by TCPAbort().
        info->flag |= TCP_SO_CLOSED;
        TCPAbort(info);

        if (0 < tcp->info.poll)
        {
            __IPWakeupPollingThreads();
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPReceiveUrgExAsync(TCPInfo* tcp, void* data, s32 len, u32 flag,
                         TCPCallback callback, s32* result)
{
    BOOL    enabled;
    BOOL    rc;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP || len < 1)
    {
        rc = IP_ERR_INVALID;
    }
    else if (info->urgCallback) // busy
    {
        rc = IP_ERR_BUSY;
    }
    else if (info->flag & (TCP_SO_CLOSED | TCP_SO_SH_RECEIVE))
    {
        rc = IP_ERR_CLOSING;
    }
    else
    {
        rc = IP_ERR_NONE;
        callback = callback ? callback : NullCallback;
        switch (info->state)
        {
          case TCP_STATE_CLOSED:
            rc = info->err;
            if (!(info->flag & TCP_SO_SH_SEND) && rc == 0)
            {
                rc = IP_ERR_NOT_EXIST;
            }
            break;
          case TCP_STATE_LISTEN:
          case TCP_STATE_SYN_SENT:
          case TCP_STATE_SYN_RECEIVED:
            if (flag & SO_MSG_DONTWAIT)
            {
                rc = IP_ERR_INVALID;
            }
            else
            {
                // Just wait
                if (flag & SO_MSG_PEEK)
                {
                    info->flag |= TCP_SO_PEEK_URG;
                }
                else
                {
                    info->flag &= ~TCP_SO_PEEK_URG;
                }
                info->urgData     = data;
                info->urgCallback = callback;
                info->urgResult   = result;
                if (result)
                {
                    *result = IP_ERR_BUSY;
                }
            }
            break;
          case TCP_STATE_ESTABLISHED:
          case TCP_STATE_FINWAIT1:
          case TCP_STATE_FINWAIT2:
          case TCP_STATE_CLOSE_WAIT:    // The remote side has already sent FIN
            if (flag & SO_MSG_PEEK)
            {
                info->flag |= TCP_SO_PEEK_URG;
            }
            else
            {
                info->flag &= ~TCP_SO_PEEK_URG;
            }

            info->urgData = data;
            if ((0 < info->recvUrg || (info->flag & TCP_SO_HAVE_URG)) &&
                (info->flag & TCP_SO_HAD_URG) == 0)
            {
                if (info->flag & TCP_SO_HAVE_URG)
                {
                    rc = 1;
                    if (data)
                    {
                        *info->urgData = info->oob;
                    }
                    if (info->flag & TCP_SO_PEEK_URG)
                    {
                        info->flag ^= (TCP_SO_HAVE_URG | TCP_SO_HAD_URG);
                    }
                    if (result)
                    {
                        *result = rc;
                    }
                    callback(tcp, rc);
                }
                else
                {
                    rc = IP_ERR_AGAIN;
                }
            }
            else if (info->state == TCP_STATE_CLOSE_WAIT)
            {
                // Do not wait since the remote side has already sent FIN.
                rc = 0;
                if (result)
                {
                    *result = rc;
                }
                callback(tcp, rc);
            }
            else if (flag & SO_MSG_DONTWAIT)
            {
                rc = IP_ERR_INVALID;
            }
            else
            {
                // Just wait
                rc = 0;
                info->urgCallback = callback;
                info->urgResult   = result;
                if (result)
                {
                    *result = IP_ERR_BUSY;
                }
            }
            break;
          case TCP_STATE_CLOSING:
          case TCP_STATE_LAST_ACK:
          case TCP_STATE_TIME_WAIT:
          default:
            rc = 0;
            if (result)
            {
                *result = rc;
            }
            callback(tcp, rc);
            break;
        }
    }
    if (result && rc < 0)
    {
        *result = rc;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPReceiveUrgAsync(TCPInfo* tcp, void* data, s32 len,
                       TCPCallback callback, s32* result)
{
    return TCPReceiveUrgExAsync(tcp, data, len, SO_MSG_OOB,
                                callback, result);
}

s32 TCPReceiveUrgNonblock(TCPInfo* tcp, void* data, s32 len)
{
    s32 rc;
    s32 result;

    rc = TCPReceiveUrgExAsync(tcp, data, len, SO_MSG_OOB | SO_MSG_DONTWAIT,
                              NULL, &result);
    return (rc == IP_ERR_NONE) ? result : rc;
}

s32 TCPReceiveUrgEx(TCPInfo* tcp, void* data, s32 len, u32 flags)
{
    BOOL enabled;
    vs32 result;
    s32  rc;

    rc = TCPReceiveUrgExAsync(tcp, data, len, flags, SyncCallback, (s32*) &result);
    if (rc < 0)
    {
        return rc;
        // NOT REACHED HERE
    }

    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&TCPGetObj(tcp)->queueThread);
    }
    OSRestoreInterrupts(enabled);

    return (s32) result;
}

s32 TCPReceiveUrg(TCPInfo* tcp, void* data, s32 len)
{
    return TCPReceiveUrgEx(tcp, data, len, 0);
}

s32 TCPPeekUrg(TCPInfo* tcp, void* data, s32 len)
{
    BOOL    enabled;
    BOOL    rc;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP || len < 1)
    {
        rc = IP_ERR_INVALID;
    }
    else if (info->flag & (TCP_SO_CLOSED | TCP_SO_SH_RECEIVE))
    {
        rc = IP_ERR_CLOSING;
    }
    else
    {
        rc = IP_ERR_NONE;
        switch (info->state)
        {
          case TCP_STATE_CLOSED:
            rc = info->err;
            if (!(info->flag & TCP_SO_SH_SEND) && rc == 0)
            {
                rc = IP_ERR_NOT_EXIST;
            }
            break;
          case TCP_STATE_LISTEN:
          case TCP_STATE_SYN_SENT:
          case TCP_STATE_SYN_RECEIVED:
            rc = IP_ERR_INVALID;
            break;
          case TCP_STATE_ESTABLISHED:
          case TCP_STATE_FINWAIT1:
          case TCP_STATE_FINWAIT2:
          case TCP_STATE_CLOSE_WAIT:
            if ((0 < info->recvUrg || (info->flag & TCP_SO_HAVE_URG)) &&
                (info->flag & TCP_SO_HAD_URG) == 0)
            {
                if (info->flag & TCP_SO_HAVE_URG)
                {
                    rc = 1;
                    if (data)
                    {
                        *(u8*) data = info->oob;
                    }
                }
                else
                {
                    rc = IP_ERR_AGAIN;
                }
            }
            else if (info->state == TCP_STATE_CLOSE_WAIT)
            {
                // The remote side has already sent FIN.
                rc = 0;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case TCP_STATE_CLOSING:
          case TCP_STATE_LAST_ACK:
          case TCP_STATE_TIME_WAIT:
          default:
            rc = 0;
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

// Returns the number of bytes before the urgent "mark". Returns zero
// if the connection is not in urgent mode.
s32 TCPGetUrgOffset(TCPInfo* tcp)
{
    BOOL    enabled;
    s32     rc;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        rc = info->recvUrg;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPGetSockOpt(TCPInfo* tcp, int level, int optname,
                  void* optval, int* optlen)
{
    BOOL    enabled;
    s32     rc = IP_ERR_INV_OPTION;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP)
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
                *(BOOL*) optval = (info->flag & TCP_SO_REUSE) ? TRUE : FALSE;
                *optlen = sizeof(BOOL);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_SO_OOBINLINE:
            if (sizeof(BOOL) <= *optlen)
            {
                *(BOOL*) optval = (info->flag & TCP_SO_OOB) ? FALSE : TRUE;
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
                *(int*) optval = SO_SOCK_STREAM;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_SO_LINGER:
            if (sizeof(SOLinger) <= *optlen)
            {
                SOLinger* linger = (SOLinger*) optval;
                linger->onoff  = (info->flag & TCP_SO_LINGER) ? 1 : 0;
                linger->linger = info->linger;
                *optlen = sizeof(SOLinger);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_SO_SNDLOWAT:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = info->sendLowat;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_SO_RCVLOWAT:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = info->recvLowat;
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
        rc = IPGetSockOpt(&tcp->info, level, optname, optval, optlen);
    }
    else if (level == SO_SOL_TCP)
    {
        switch (optname)
        {
          case SO_TCP_NODELAY:
            if (sizeof(BOOL) <= *optlen)
            {
                *(BOOL*) optval = (info->flag & TCP_SO_NAGLE) ? FALSE : TRUE;
                *optlen = sizeof(BOOL);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_TCP_MAXSEG:
            if (sizeof(int) <= *optlen)
            {
                *(int*) optval = info->mss;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_TCP_STDURG:
            if (sizeof(BOOL) <= *optlen)
            {
                *(BOOL*) optval = (info->flag & TCP_SO_STD_URG) ? TRUE : FALSE;
                *optlen = sizeof(BOOL);
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
        }
    }
#ifdef IP_INET6
    else if (level == SO_IPPROTO_IPV6)
    {
        rc = IP6GetSockOpt(&tcp->info, level, optname, optval, optlen);
    }
#endif  // IP_INET6
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 TCPSetSockOpt(TCPInfo* tcp, int level, int optname,
                  const void* optval, int optlen)
{
    BOOL    enabled;
    s32     rc = IP_ERR_INV_OPTION;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP)
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
                    info->flag |= TCP_SO_REUSE;
                }
                else
                {
                    info->flag &= ~TCP_SO_REUSE;
                }
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_SO_OOBINLINE:
            if (sizeof(BOOL) <= optlen)
            {
                if (*(const BOOL*) optval)
                {
                    info->flag &= ~TCP_SO_OOB;
                }
                else
                {
                    info->flag |= TCP_SO_OOB;
                }
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_SO_LINGER:
            if (sizeof(SOLinger) <= optlen)
            {
                const SOLinger* linger = (const SOLinger*) optval;
                if (linger->onoff)
                {
                    info->flag |= TCP_SO_LINGER;
                }
                else
                {
                    info->flag &= ~TCP_SO_LINGER;
                }
                info->linger = (0 < linger->linger) ? linger->linger : 0;
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_SO_SNDLOWAT:
            if (sizeof(int) <= optlen)
            {
                int lowat = *(const int*) optval;

                info->sendLowat = MAX(1, MIN(info->sendBuff, lowat));
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_SO_RCVLOWAT:
            if (sizeof(int) <= optlen)
            {
                int lowat = *(const int*) optval;

                info->recvLowat = MAX(1, MIN(info->recvBuff, lowat));
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
        rc = IPSetSockOpt(&tcp->info, level, optname, optval, optlen);
        if (optname == SO_IP_TTL && rc == IP_ERR_NONE)
        {
            // Initialize IP header template
            IPHeader* header = (IPHeader*) &info->header[0];
            header->ttl = tcp->info.ttl;
        }
    }
    else if (level == SO_SOL_TCP)
    {
        switch (optname)
        {
          case SO_TCP_NODELAY:
            if (sizeof(BOOL) <= optlen)
            {
                if (*(const BOOL*) optval)
                {
                    info->flag &= ~TCP_SO_NAGLE;
                }
                else
                {
                    info->flag |= TCP_SO_NAGLE;
                }
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_TCP_MAXSEG:
            if (sizeof(int) <= optlen)
            {
                s32 mss = *(int*) optval;
#ifdef IOP_OS
                s32 mssMax = 0;
#else
                s32 mssMax;
#endif // IOP_OS
                
                switch (tcp->info.family)
                {
                  case SO_AF_INET:
                    mssMax = __IFDefault.mtu - IP_MIN_HLEN - TCP_MIN_HLEN;
                    break;
#ifdef IP_INET6
                  case SO_AF_INET6:
                    mssMax = __IFDefault.linkMTU - (s32) sizeof(IP6Hdr) - TCP_MIN_HLEN;
                    break;
#endif // IP_INET6
                }
                if (0 < mss && mss <= mssMax)
                {
                    info->mss = info->mssBase = mss;

                    // Goes back to slow start without changing slow start threshold
                    // like source quench
                    info->cWin = TCP_IW(info);

                    rc = IP_ERR_NONE;
                }
                else
                {
                    rc = IP_ERR_INVALID;
                }
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
          case SO_TCP_STDURG:
            if (sizeof(BOOL) <= optlen)
            {
                if (*(const BOOL*) optval)
                {
                    info->flag |= TCP_SO_STD_URG;
                }
                else
                {
                    info->flag &= ~TCP_SO_STD_URG;
                }
                rc = IP_ERR_NONE;
            }
            else
            {
                rc = IP_ERR_INVALID;
            }
            break;
        }
    }
#ifdef IP_INET6
    else if (level == SO_IPPROTO_IPV6)
    {
        rc = IP6SetSockOpt(&tcp->info, level, optname, optval, optlen);
        if (optname == SO_IPV6_UNICAST_HOPS && rc == IP_ERR_NONE)
        {
            // Initialize IP header template
            IP6Hdr* header = (IP6Hdr*) &info->header[0];
            header->hops = tcp->info.ttl;
        }
    }
#endif  // IP_INET6
    OSRestoreInterrupts(enabled);
    return rc;
}

/*---------------------------------------------------------------------------*
  Name:         TCPSetTimeout

  Description:  Set threshold of retransmissions. When transmissions
                reach the threshold, the connection is closed.

                While establishing connection, threshold should be greater
                than 3 minutes.

                R1 SHOULD correspond to at least 3 retransmissions
                R2 SHOULD correspond to at least 100 seconds
                [RFC 1122 4.2.3.5]

  Arguments:    tcp        Pointer to TCPInfo block to which threshold is set
                threshold   Should be at least 100 seconds

  Returns:      IP_ERR_NONE
 *---------------------------------------------------------------------------*/
// sysctl(2) tcp_retries[1|2]
s32 TCPSetTimeout(TCPInfo* tcp, OSTime threshold)
{
    BOOL    enabled;
    s32     rc;
    TCPObj* info;

    enabled = OSDisableInterrupts();
    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        info->r2 = threshold;
        rc = IP_ERR_NONE;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

//
// Obsolete functions...
//

s32 TCPControlNagle(TCPInfo* tcp, BOOL enable)
{
    return TCPSetSockOpt(tcp, SO_SOL_TCP, SO_TCP_NODELAY, &enable, sizeof enable);
}

s32 TCPSetUrgInLine(TCPInfo* tcp, BOOL inLine)
{
    return TCPSetSockOpt(tcp, SO_SOL_SOCKET, SO_SO_OOBINLINE, &inLine, sizeof inLine);
}

s32 TCPSetOption(TCPInfo* tcp, u8 ttl, u8 tos)
{
    BOOL enabled;
    s32  rc;

    enabled = OSDisableInterrupts();
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        rc = IP_ERR_INVALID;
    }
    else
    {
        rc = IPSetOption(&tcp->info, ttl, tos);
        if (rc == IP_ERR_NONE)
        {
            // Initialize IP header template
            IPHeader* header = (IPHeader*) &TCPGetObj(tcp)->header[0];
            header->ttl = tcp->info.ttl;
        }
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

/*---------------------------------------------------------------------------*
  Name:         TCPOnReset

  Description:  Reset function for OSResetSystem()

  Arguments:    final       TRUE if OSResetSystem() is about to reset
                            the system

  Returns:      TRUE if GBA subsystem is ready to reset.
 *---------------------------------------------------------------------------*/
BOOL TCPOnReset(BOOL final)
{
#ifdef IOP_OS
    TCPIP_UNUSED(final);
#else
    #pragma unused( final )
#endif // IOP_OS

    TCPInfo* tcp;

    if (IFIsEmptyQueue(&TCPInfoQueue))
    {
        return TRUE;
    }

    while (!IFIsEmptyQueue(&TCPInfoQueue))
    {
        tcp = (TCPInfo*) IFQueryQueueHead(&TCPInfoQueue);
        TCPCancel(tcp);
    }
    return FALSE;
}

short __TCPPoll(TCPInfo* tcp)
{
    short   event;
    TCPObj* info;

    info = TCPGetObj(tcp);
    if (tcp->info.proto != IP_PROTO_TCP)
    {
        return SO_POLLNVAL;
    }
    event = 0;

    // Accept
    if (info->state == TCP_STATE_LISTEN)
    {
        if (!IFIsEmptyQueue(&info->queueCompleted))
        {
            event |= SO_POLLRDNORM;
        }
    }

    // Send
    switch (info->state)
    {
      case TCP_STATE_CLOSED:
        event |= SO_POLLWRNORM; // closed
        break;
      case TCP_STATE_LISTEN:
        break;
      case TCP_STATE_SYN_SENT:
      case TCP_STATE_SYN_RECEIVED:
      case TCP_STATE_ESTABLISHED:
      case TCP_STATE_CLOSE_WAIT:
        if (info->userSendLen <= 0 &&   // Has all user send data been copied-in?
            info->sendLowat <= info->sendBuff - info->sendLen)  // Any useable space?
        {
            event |= (SO_POLLWRNORM | SO_POLLWRBAND);
        }
        break;
      case TCP_STATE_FINWAIT1:
      case TCP_STATE_FINWAIT2:
      case TCP_STATE_CLOSING:
      case TCP_STATE_LAST_ACK:
      case TCP_STATE_TIME_WAIT:
      default:
        event |= SO_POLLWRNORM; // sent FIN
        break;
    }

    // Receive
    switch (info->state)
    {
      case TCP_STATE_CLOSED:
        event |= SO_POLLRDNORM; // closed
        break;
      case TCP_STATE_LISTEN:
      case TCP_STATE_SYN_SENT:
      case TCP_STATE_SYN_RECEIVED:
        break;
      case TCP_STATE_ESTABLISHED:
      case TCP_STATE_FINWAIT1:
      case TCP_STATE_FINWAIT2:
      case TCP_STATE_CLOSE_WAIT:    // The remote side has already sent FIN

        // Normal data
        if (info->recvLowat <= info->recvUser)
        {
            event |= SO_POLLRDNORM;
        }
        else if (info->state == TCP_STATE_CLOSE_WAIT)
        {
            // Do not wait since the remote side has already sent FIN.
            event |= SO_POLLRDNORM; // closed
        }

        // Priority data
        if ((0 < info->recvUrg || (info->flag & TCP_SO_HAVE_URG)) &&
            (info->flag & TCP_SO_HAD_URG) == 0)
        {
            // if (info->flag & TCP_SO_HAVE_URG) ???
            event |= SO_POLLRDBAND; // received URG

            if (0 < info->recvUser)
            {
                event |= SO_POLLRDNORM;     // urgent
            }
        }

        break;

      case TCP_STATE_CLOSING:
      case TCP_STATE_LAST_ACK:
      case TCP_STATE_TIME_WAIT:
      default:
        event |= SO_POLLRDNORM; // received FIN
        break;
    }

    if (info->flag & TCP_SO_SH_SEND)
    {
        event |= SO_POLLWRNORM;
    }
    if (info->flag & TCP_SO_SH_RECEIVE)
    {
        event |= SO_POLLRDNORM;
    }

    // Error
    if (info->state == TCP_STATE_CLOSED &&
        (info->flag & (TCP_SO_SH_RECEIVE | TCP_SO_SH_SEND)) ==
                            (TCP_SO_SH_RECEIVE | TCP_SO_SH_SEND))
    {
        if (info->err)
        {
            event |= SO_POLLERR;
        }
    }

    return event;
}

s32 TCPReport(IPInterface* interface, void* optval, int* optlen)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused( interface )
#endif // IOP_OS

    int       len;
    IPInfo*   info;
    IPInfo*   next;
    TCPEntry* tcp;

    len = 0;
    tcp = optval;
    IFIterateQueue(IPInfo*, &TCPInfoQueue, info, next, link)
    {
        if (*optlen < len + sizeof(TCPEntry))
        {
            break;
        }
        if (info->family == SO_PF_INET)
        {
            TCPObj* obj = TCPGetObj((TCPInfo*) info);
            tcp->state = obj->state;
            memcpy(&tcp->local, IPGetLocalSockAddr(info), sizeof(SOSockAddrIn));
            memcpy(&tcp->remote, IPGetRemoteSockAddr(info), sizeof(SOSockAddrIn));
            len += sizeof(TCPEntry);
            ++tcp;
        }
    }

    // Scan time-wait buffer
    *optlen -= len;
    TCPReportTimeWait(interface, tcp, optlen);

    *optlen = len + *optlen;
    return IP_ERR_NONE;
}

#ifdef IP_INET6
s32 TCP6Report(IPInterface* interface, void* optval, int* optlen)
{
#ifdef IOP_OS
    TCPIP_UNUSED(interface);
#else
    #pragma unused( interface )
#endif // IOP_OS

    int        len;
    IPInfo*    info;
    IPInfo*    next;
    TCP6Entry* tcp;

    len = 0;
    tcp = optval;
    IFIterateQueue(IPInfo*, &TCPInfoQueue, info, next, link)
    {
        if (*optlen < len + sizeof(TCP6Entry))
        {
            break;
        }
        if (info->family == SO_PF_INET6)
        {
            TCPObj* obj = TCPGetObj((TCPInfo*) info);
            tcp->state = obj->state;
            memcpy(&tcp->local, IPGetLocalSockAddr(info), sizeof(SOSockAddrIn6));
            memcpy(&tcp->remote, IPGetRemoteSockAddr(info), sizeof(SOSockAddrIn6));
            len += sizeof(TCP6Entry);
            ++tcp;
        }
    }

    // Scan time-wait buffer
    *optlen -= len;
    TCP6ReportTimeWait(interface, tcp, optlen);

    *optlen = len + *optlen;
    return IP_ERR_NONE;
}
#endif // IP_INET6
