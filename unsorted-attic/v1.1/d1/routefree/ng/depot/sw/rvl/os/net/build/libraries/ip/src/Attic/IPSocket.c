d1 4016
a4016 3945
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPSocket.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip6/src/IPSocket.c $
    
    79    3/06/06 14:36 Shiki
    Fixed SOCleanup() and SOStartup() to clean the time wait buffer before
    releasing the buffer memory.

    78    3/02/06 15:40 Shiki
    Modified SOGetHostByName().

    77    06/03/01 14:21 Ueno_kyu
    Moved SO_SOCKET_MAX  to socket.h.


    76    2/23/06 15:10 Shiki
    Added SOReportResolverTable().

    75    2/23/06 10:55 Shiki
    Added SOGetInterfaceOpt and SOSetInterfaceOpt.

    74    2/20/06 18:13 Shiki
    Modified SOGetHostByAddr() to support for SOHostEnt.aliases.

    73    2/09/06 14:34 Shiki
    Fixed TIME-WAIT state management when time wait buffer is no available.

    72    1/30/06 15:47 Shiki
    Clean up.

    71    1/19/06 17:46 Shiki
    Fixed to send MLD listener done messages during cleanup and before
    reset.

    70    1/19/06 14:50 Shiki
    Fixed SOAccept().

    69    1/18/06 16:47 Shiki
    Added support for domain name suffix.

    68    1/12/06 16:07 Shiki
    Revised GetRwin() to return the fixed default value for both IPv4 and
    IPv6.

    67    1/11/06 14:42 Shiki
    Fixed IPv6 to use interface->linkMTU instead of interface->mtu.

    66    12/28/05 13:45 Shiki
    Fixed AcceptCallback().

    65    12/21/05 14:42 Shiki
    Fixed SOSendTo() to return SO_ENOTCONN for the listening TCP socket.

    64    12/01/05 17:53 Shiki
    Fixed SOStartup() to call IGMPInit() to join all-hosts group.

    63    11/28/05 18:18 Shiki
    Added support for SO_EALREADY with SOConnect().

    62    05/10/20 11:49 Ueno_kyu
    Added support for SO_ERROR option.
    Added SOGetLastError() to support errno.

    61    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    72    10/12/04 18:00 Shiki
    Modified SOCleanup() to call IP6Cleanup().

    71    04/09/22 10:25 Ueno_kyu
    Added support for ping over IPv4.

    70    04/09/01 13:23 Ueno_kyu
    Revised to allocate a reassembly buffer of IPv6 besides that of IPv4.

    69    04/08/31 19:49 Ueno_kyu
    Added support for IPv6 fragmentation and reassembly.

    68    04/07/01 12:00 Ueno_kyu
    Added support for AOL.

    67    7/01/04 8:59 Shiki
    Fixed SOSetResolver() to accept NULL arguments.

    66    6/23/04 14:55 Shiki
    Revised to support Ethernet and other network devices in a uniform way.

    65    04/06/21 13:51 Ueno_kyu
    Modified SOInit() to call MDMLinkInit() instead of MDMStartup().

    64    04/06/17 8:54 Ueno_kyu
    Cleanup.

    63    04/06/15 15:02 Ueno_kyu
    Added support for modem.

    62    6/14/04 17:16 Shiki
    Fixed AddBackLog().

    61    6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    59    1/26/04 11:18 Shiki
    Modified IPAtoN() to return non-NULL pointer if succeeded.

    58    11/21/03 21:13 Shiki
    Fixed SOConnect() bug in case non-block TCP.

    57    11/14/03 13:10 Shiki
    Added support for SOGetAddrInfo(), SOFreeAddrInfo(), and
    SOGetNameInfo().

    56    11/04/03 15:59 Shiki
    Fixed to use (UdpSendBuff + IP_MIN_HLEN) as the maximum IP datagram
    size than can be reassembled.

    55    11/04/03 15:35 Shiki
    Added support for udpSendBuff and udpRecvBuff in SOConfig{}.

    54    10/24/03 13:39 Shiki
    Added support for client DHCP host name.

    53    10/23/03 20:31 Shiki
    Added support for PPPoE service name.

    52    9/29/03 17:56 Shiki
    Fixed SOCleanup() to uninstall the reassembly buffer.

    51    9/25/03 14:24 Shiki
    Modified SOGetHostByName() to accept a numeric address string.

    50    7/01/03 14:03 Shiki
    Restructured the PPP layer structure.

    49    6/04/03 9:32 Shiki
    Revised so that an application does not incur interrupts from the
    network interface while it is not configured. Implemented IFMute().

    48    5/15/03 15:57 Shiki
    Fixed AcceptCallback() to reinsert tcp to the backlog queue correctly
    upon failure.

    47    5/14/03 16:48 Shiki
    Modified SOAccept() so that the accepted socket inherits the SOFcntl()
    flags set with the listening socket.

    46    5/14/03 9:31 Shiki
    Fixed node reference count management bug in __SOClose() for
    SO_O_NONBLOCK sockets.

    45    5/13/03 13:17 Shiki
    Implemented default TCP close timeout.

    44    5/03/03 13:07 Shiki
    Clean up.

    43    5/01/03 10:42 Shiki
    Modified to set interface MTU from DHCP MTU option by default.

    42    4/28/03 21:14 Shiki
    Modified SOCleanup() to call IPAutoStop().

    41    4/28/03 16:10 Shiki
    Modified to clear ARP cache entries in SOStartup() and SOCleanup().

    40    4/18/03 22:04 Shiki
    Added support for config->rdhcp.

    39    3/26/03 15:02 Shiki
    Clean up SOSendTo().
    Implemented TCP support for SOPoll().

    38    3/25/03 13:52 Shiki
    Fixed SOSendTo() to perform non-blocking send correctly.

    37    3/12/03 11:29 Shiki
    Implemented OnReset().

    36    3/07/03 14:34 Shiki
    Revised to check if the network have been configured using the
    low-level IP functions before SOInit(). Both SOStartup() and
    SOCleanup() keep the low-level configuration.

    35    3/07/03 10:45 Shiki
    Added SOInit().
    Fixed SOStartup() to release allocated memory blocks upon failure.

    34    1/30/03 18:32 Shiki
    Added support for SO_MEM_UDP_SENDBUF.

    33    1/23/03 17:23 Shiki
    Revised UDPInfo receive buffer structure using ring buffer.

    32    1/22/03 18:10 Shiki
    Added SOPoll() interface.

    31    12/13/02 14:44 Shiki
    Fixed SOInetPtoN() description.

    30    11/11/02 21:56 Shiki
    Added support for SO_MSG_DONTWAIT.

    29    10/17/02 13:18 Shiki
    Fixed SOInetAtoN() to accept NULL ipn.
    Revised SOStartup() to set up mtu and other SOConfig parameters before
    sending any packets.
    Fixed SOCleanup() return code when the library is not initialized.
    Modified SOGetPeerName() to return SO_ENOTCONN if socket is not
    connected.
    Fixed SOGetHostByAddr() function prototype.
    Added SOInetPtoN() and SOInetNtoP().
    Added function descriptions.

    28    10/07/02 10:46 Shiki
    Revised SOSetResolver()/SOGetResolver() prototypes.

    27    8/05/02 10:12 Shiki
    Modified so that the settings of SOConfig{}.dns? precedes any other
    automatic host configuration settings.
    Modified to updated interface MTU from the DHCP MTU setting.

    26    8/01/02 11:46 Shiki
    Integrated PPPoE. Added SOSetResolver() and SOGetResolver(). Fixed Rwin
    calculation method to use the current MTU.

    25    7/22/02 15:48 Shiki
    Added support for SO_SO_RCVBUF for UDP.

    24    7/22/02 14:27 Shiki
    Added support for SO_SO_SNDBUF and SO_SO_RCVBUF for TCP.

    23    7/19/02 16:12 Shiki
    Added support for non-blocking I/O.

    22    7/18/02 15:25 Shiki
    Revised TCP R2 management code.

    21    7/15/02 16:59 Shiki
    Revised for better multi-thread support. Now more than one SORead() and
    SOWrite() can be issued simultaneously.

    20    7/05/02 16:47 Shiki
    Fixed SOCleanup() to wait for the memory release completion of
    SOAccept().

    19    7/05/02 15:51 Shiki
    Added VERBOSE print calls.

    18    7/04/02 15:57 Shiki
    Fixed memory allocation bugs.

    17    7/04/02 11:50 Shiki
    Fixed SOCleanup() so that it closes open socket descriptors by the
    socket functions and also it waits for the completion of DHCPCleanup()
    without busy-wait.

    16    02/07/01 15:34 Shiki
    Modified SOStartup to configure the host using mtu and rwin field in
    SOConfig{}.

    15    02/07/01 13:40 Shiki
    Modified so that SOStartup()/SOCleanup() pair can be called more than
    once. Fixed SOCleanup() so that it cleans up its resources totally.

    14    4/30/02 14:51 Shiki
    Implemented SOGetHostID().
    Directly implemented SONtoHl() and other functions for WIN32.
    Added support for SO_MSG_PEEK for UDP.

    13    4/26/02 15:51 Shiki
    Revised to support new SOConfig{} structure.

    12    4/24/02 11:50 Shiki
    Added IP_ERR_NETDOWN error handling code.

    11    4/23/02 16:03 Shiki
    Implemented linger timer and socket address check routines.

    10    4/19/02 11:02 Shiki
    Fixed SORecvFrom() to handle IP_ERR_DATASIZE error.

    9     4/18/02 18:52 Shiki
    Implemented error code handling.

    8     4/17/02 20:15 Shiki
    Defined IP_ERR_SOURCE_QUENCH.

    7     4/17/02 11:12 Shiki
    Fixed SOGetHostBy*() to also check IP_ERR_INS_RESOURCES for the server
    recovery.

    6     4/17/02 11:05 Shiki
    Implemented RecoverNameServer().

    5     4/17/02 10:04 Shiki
    Revised to use new IPDns.c implementation for CNAME lookup.

    4     4/15/02 11:47 Shiki
    Implemented SONtoHl() and other macros for WIN32 build.

    3     4/12/02 18:52 Shiki
    Modified SOConnect() to reset the remote socket if SO_PF_UNSPEC is
    specified as the destination protocol family.

    2     4/12/02 13:44 Shiki
    Fixed backlog queue management code.

    1     4/08/02 16:51 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <dolphin/socket.h>
#include <dolphin/ip/IPPpp.h>
#include "IPPrivate.h"
#include "IPPPPConf.h"
#ifdef  IP_INET6
#include "IP6Private.h"
#endif  // IP_INET6

typedef struct SONode
{
    u8      proto;          // protocol
    u8      flag;           // flag for fcntl()
    s16     ref;            // reference count
    IPInfo* info;
    OSMutex mutexRead;
    OSMutex mutexWrite;
    int     error;          // last socket error
} SONode;

static void* (* Alloc )(u32 name, s32 size);
static void  (* Free ) (u32 name, void* ptr, s32 size);
static u32        Allocated;

static SONode     SocketTable[SO_SOCKET_MAX];
static IFQueue    LingerQueue;  // Closed stream socket queue
static SOSockAddr SockAnyIn =
{
    IP_SOCKLEN,
    SO_PF_INET
};

SOResolver __SOResolver;

static u8* TimeWaitBuf;
static s32 TimeWaitBufSize;
static u8* ReassemblyBuffer;
static s32 ReassemblyBufferSize;

#ifdef IP_INET6
static u8* IP6ReassemblyBuffer;
static s32 IP6ReassemblyBufferSize;
#endif // IP_INET6

#define STATE_CLEAN         0
#define STATE_INITIALIZED   1
#define STATE_MORIBUND      2
#define STATE_RESET         3

static vs32          State = STATE_CLEAN;
static u32           Flag;
static s32           Mtu;
static s32           Rwin;
static OSTime        R2;
static s32           UdpSendBuff;
static s32           UdpRecvBuff;

static OSThreadQueue CleaningQueue;
static OSThreadQueue PollingQueue;
static BOOL          LowInitialized;
static BOOL          Initialized;

int SOGetLastError(void)
{
    OSThread* currentThread = OSGetCurrentThread();
    return currentThread->error;
}

static BOOL OnReset( BOOL final );

static OSResetFunctionInfo ResetFunctionInfo =
{
    OnReset,
    OS_RESET_PRIO_SO
};

static void LingerCallback(TCPInfo* info, s32 result);
static int __SOSetSockOpt(int s, int level, int optname,
                          const void* optval, int optlen);
static int __SOClose(int s);

#define IsModemAttached(x)    ( __IFDefault.type == IF_TYPE_MODEM )

void* SOAlloc(u32 name, s32 size)
{
    void* ptr;
    BOOL  enabled;

    ASSERT(Alloc);
    ptr = Alloc(name, size);
    if (ptr)
    {
#ifdef VERBOSE
        OSReport("SOAlloc(%d, %d): %p\n", name, size, ptr);
#endif
        enabled = OSDisableInterrupts();
        Allocated += size;
        OSRestoreInterrupts(enabled);
    }
    return ptr;
}

void SOFree(u32 name, void* ptr, s32 size)
{
    BOOL  enabled;

    ASSERT(Free);
    if (ptr)
    {
        Free(name, ptr, size);
#ifdef VERBOSE
        OSReport("SOFree(%d, %p, %d)\n", name, ptr, size);
#endif
        enabled = OSDisableInterrupts();
        Allocated -= size;
        if (Allocated == 0 && State == STATE_MORIBUND)
        {
            OSWakeupThread(&CleaningQueue);
        }
        OSRestoreInterrupts(enabled);
    }
}

static void TCPFree(TCPInfo* info)
{
    TCPObj* obj;

    obj = TCPGetObj(info);
    ASSERT(obj);
    SOFree(SO_MEM_TCP_RECVBUF, obj->recvData, obj->recvBuff);
    SOFree(SO_MEM_TCP_SENDBUF, obj->sendData, obj->sendBuff);
    switch (info->info.family)
    {
      case SO_PF_INET:
        SOFree(SO_MEM_TCP_INFO, info, sizeof(TCPInfo));
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        SOFree(SO_MEM_TCP_INFO, info, sizeof(TCP6Info));
        break;
#endif
    }
}

static void UDPFree(UDPInfo* info)
{
    UDPObj* obj;

    obj = UDPGetObj(info);
    SOFree(SO_MEM_UDP_RECVBUF, obj->recvRing, obj->recvBuff);
    SOFree(SO_MEM_UDP_SENDBUF, obj->sendData, obj->sendBuff);
    switch (info->info.family)
    {
      case SO_PF_INET:
        SOFree(SO_MEM_UDP_INFO, info, sizeof(UDPInfo));
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        SOFree(SO_MEM_UDP_INFO, info, sizeof(UDP6Info));
        break;
#endif
    }
}

#ifndef WIN32
u32 (SONtoHl)(u32 netlong)
{
    return netlong;
}

u16 (SONtoHs)(u16 netshort)
{
    return netshort;
}

u32 (SOHtoNl)(u32 hostlong)
{
    return hostlong;
}

u16 (SOHtoNs)(u16 hostshort)
{
    return hostshort;
}
#else
u32 (SONtoHl)(u32 netlong)
{
    return (netlong >> 24) & 0x000000ff |
           (netlong >> 8)  & 0x0000ff00 |
           (netlong << 8)  & 0x00ff0000 |
           (netlong << 24) & 0xff000000;
}

u16 (SONtoHs)(u16 netshort)
{
    return (netshort >> 8) | (netshort << 8);
}

u32 (SOHtoNl)(u32 hostlong)
{
    return (hostlong >> 24) & 0x000000ff |
           (hostlong >> 8)  & 0x0000ff00 |
           (hostlong << 8)  & 0x00ff0000 |
           (hostlong << 24) & 0xff000000;
}

u16 (SOHtoNs)(u16 hostshort)
{
    return (hostshort >> 8) | (hostshort << 8);
}
#endif  // WIN32

/*---------------------------------------------------------------------------*
  Name:         SOInetAtoN

  Description:  SOInetAtoN() converts an Internet host address in the dotted
                decimal notation into binary address.

  Arguments:    cp      dotted-decimal notation of an IPv4 address.
                inp     binary IPv4 address in network byte order.

  Returns:      1 if cp is a valid IPv4 address notation (even if inp is
                NULL). 0 if cp is not a valid IPv4 address notation.
 *---------------------------------------------------------------------------*/
int SOInetAtoN(const char* cp, SOInAddr* inp)
{
    u8 addr[IP_ALEN];

    return IPAtoN(cp, inp ? (u8*) &inp->addr : addr) ? 1 : 0;
}

/*---------------------------------------------------------------------------*
  Name:         SOInetNtoA

  Description:  SOInetNtoA() converts an internet host address specified by
                in to a string in the dotted-decimal notation.

  Note:         SOInetNtoA() is not reentrant and not thread-safe.

  Arguments:    in      Internet host address.

  Returns:      Pointer to the character string in the dotted-decimal
                notation in a statically allocated buffer.
 *---------------------------------------------------------------------------*/
char* SOInetNtoA(SOInAddr in)
{
    return IPNtoA((u8*) &in.addr);
}

/*---------------------------------------------------------------------------*
  Name:         SOInetPtoN

  Description:  SOInetPtoN() converts an address in its standard text
                presentation into its numeric binary form.

  Arguments:    af      The family of the address (must be SO_PF_INET).
                src     A pointer to the string being passed in.
                        (e.g., ddd.ddd.ddd.ddd)
                dst     A pointer to a buffer where the function stores the
                        numeric address.

  Returns:      1               Succeeded.
                0               src is not a valid IPv4 address notation.
                SO_EAFNOSUPPORT af is not SO_PF_INET.
 *---------------------------------------------------------------------------*/
int SOInetPtoN(int af, const char* src, void* dst)
{
    switch (af)
    {
      case SO_PF_INET:
        return IPAtoN(src, dst) ? 1 : 0;
#ifdef IP_INET6
      case SO_PF_INET6:
        return IP6AtoN(src, dst) ? 1 : 0;
#endif
    }
    return SO_EAFNOSUPPORT;
}

/*---------------------------------------------------------------------------*
  Name:         SOInetNtoP

  Description:  SOInetNtoP() converts a numeric address to a suitable text
                string.

  Arguments:    af      The family of the address (must be SO_PF_INET).
                src     A pointer to a buffer holding an IPv4 address.
                dst     A pointer to a buffer where the function stores the
                        resulting text string.
                len     The buffer size of dst. len should be large enough to
                        hold the text string (INET_ADDRSTRLEN for SO_PF_INET).

  Returns:      Pointer to the character string in the dotted-decimal notation.
 *---------------------------------------------------------------------------*/
const char* SOInetNtoP(int af, const void* src, char* dst, unsigned len)
{
    const u8* addr = src;

    switch (af)
    {
      case SO_PF_INET:
        if (dst != NULL && SO_INET_ADDRSTRLEN <= len)
        {
            sprintf(dst, "%u.%u.%u.%u", addr[0], addr[1], addr[2], addr[3]);
            return dst;
        }
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        if (dst != NULL && SO_INET6_ADDRSTRLEN <= len)
        {
            IP6NtoA(src, dst);
            return dst;
        }
        break;
#endif
    }
    return NULL;
}

static SONode* GetNode(int s, IPInfo** pinfo)
{
    SONode*  node;
    IPInfo*  info;
    IPInfo*  next;
    TCPInfo* tcp;
    TCPObj*  obj;
    BOOL     enabled;
    IFQueue  queue;

    IFInitQueue(&queue);

    enabled = OSDisableInterrupts();
    IFIterateQueue(IPInfo*, &LingerQueue, info, next, link)
    {
        tcp = (TCPInfo*) info;
        obj = TCPGetObj(tcp);
        ASSERT(obj);
        if (obj->node == NULL || ((SONode*) obj->node)->ref == 0)
        {
            IFDequeueItem(IPInfo*, &LingerQueue, info, link);
            IFEnqueueTail(IPInfo*, &queue, info, link);
        }
    }
    OSRestoreInterrupts(enabled);

    while (!IFIsEmptyQueue(&queue))
    {
        IFDequeueHead(IPInfo*, &queue, info, link);
        TCPFree((TCPInfo*) info);
    }

    node = NULL;
    enabled = OSDisableInterrupts();
    if (0 <= s && s < SO_SOCKET_MAX)
    {
        node = &SocketTable[s];
        if (node->ref <= 0 || node->info == NULL) // Closed?
        {
            node = NULL;
        }
        else
        {
            ++node->ref;
            if (pinfo)
            {
                *pinfo = node->info;
            }
        }
    }
    OSRestoreInterrupts(enabled);
    return node;
}

static void PutNode(SONode* node, int error)
{
    BOOL    enabled;
    IPInfo* info;
    u8      proto;
    OSThread* currentThread;

    ASSERT(node);
    proto = 0;
    info = NULL;
    enabled = OSDisableInterrupts();
    ASSERT(0 < node->ref);
    if (--node->ref == 0 && node->info) // Note if info is in LingerQueue, node->info is NULL.
    {
        info = node->info;
        node->info = NULL;
        proto = node->proto;
        node->proto = 0;
    }
    node->error = error;

    currentThread = OSGetCurrentThread();
    currentThread->error = error;

    OSRestoreInterrupts(enabled);

    if (info)
    {
        switch (proto)
        {
          case IP_PROTO_UDP:
            UDPFree((UDPInfo*) info);
            break;
          case IP_PROTO_TCP:
            TCPFree((TCPInfo*) info);
            break;
          default:
            OSHalt("PutNode: unknown proto");
            break;
        }
    }
}

int SOSetResolver(const SOInAddr* dns1, const SOInAddr* dns2)
{
    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }
    DNSClose(&__SOResolver.info);
    DNSOpen2(&__SOResolver.info,
             dns1 ? (u8*) &dns1->addr : NULL,
             dns2 ? (u8*) &dns2->addr : NULL);
    __SOResolver.info.flag |= DNS_FLAG_SOCKET;
    return 0;
}

int SOGetResolver(SOInAddr* dns1, SOInAddr* dns2)
{
    BOOL enabled;
    int  rc;

    enabled = OSDisableInterrupts();
    if (State != STATE_INITIALIZED)
    {
        rc = SO_ENETRESET;
    }
    else
    {
        if (dns1)
        {
            memcpy(&dns1->addr, __SOResolver.info.dns1, IP_ALEN);
        }
        if (dns2)
        {
            memcpy(&dns2->addr, __SOResolver.info.dns2, IP_ALEN);
        }
        rc = 0;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

int SOSetSuffix(const char* domainName)
{
    BOOL enabled;
    int  rc;

    enabled = OSDisableInterrupts();
    if (State != STATE_INITIALIZED)
    {
        rc = SO_ENETRESET;
    }
    else if (SO_MAXDNAME <= strnlen(domainName, SO_MAXDNAME))
    {
        rc = SO_ENAMETOOLONG;
    }
    else
    {
        strcpy(__SOResolver.suffix, domainName);
        rc = 0;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

int SOGetSuffix(char* domainName)
{
    BOOL enabled;
    int  rc;

    enabled = OSDisableInterrupts();
    if (State != STATE_INITIALIZED)
    {
        rc = SO_ENETRESET;
    }
    else
    {
        strcpy(domainName, __SOResolver.suffix);
        rc = 0;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

s32 SOReportResolverTable(IPInterface* interface, void* optval, int* optlen)
{
    #pragma unused( interface )
    int len;
    u8* addr;

    len = 0;
    addr = optval;
    if (IP_ADDR_NE(__SOResolver.info.dns1, IPAddrAny))
    {
        if (len + sizeof(IP_ALEN) <= *optlen)
        {
            memmove(addr, __SOResolver.info.dns1, IP_ALEN);
            addr += IP_ALEN;
            len += IP_ALEN;
        }
    }
    if (IP_ADDR_NE(__SOResolver.info.dns2, IPAddrAny))
    {
        if (len + sizeof(IP_ALEN) <= *optlen)
        {
            memmove(addr, __SOResolver.info.dns2, IP_ALEN);
            addr += IP_ALEN;
            len += IP_ALEN;
        }
    }
    *optlen = len;
    return 0;
}

static void LcpHandler(PPPConf* conf)
{
    if (conf->state == 0 && State == STATE_MORIBUND)
    {
        OSWakeupThread(&CleaningQueue);
    }
}

static void DhcpHandler(int state)
{
    u8 prev1[IP_ALEN];
    u8 prev2[IP_ALEN];
    u8 dns[2 * IP_ALEN];

    switch (state)
    {
      case DHCP_STATE_BOUND:
        if (SOGetResolver((SOInAddr*) prev1, (SOInAddr*) prev2) == 0)
        {
            if (IP_ADDR_EQ(prev1, IPAddrAny) && IP_ADDR_EQ(prev2, IPAddrAny))
            {
                DHCPGetOpt(DHCP_OPT_DNS, dns, sizeof(dns));
                SOSetResolver((SOInAddr*) &dns[0], (SOInAddr*) &dns[IP_ALEN]);
                DHCPGetOpt(DHCP_OPT_DOMAIN_NAME, __SOResolver.suffix, SO_MAXDNAME);
            }
            else
            {
                // Since the inteface may not have been initialized when
                // SOSetResolver() is called for the 1st time, we call
                // SOSetResolver() again.
                SOSetResolver((SOInAddr*) prev1, (SOInAddr*) prev2);
            }
        }

        break;
      case DHCP_STATE_INIT:
        IPSetMtu(NULL, Mtu);    // Reset to default
        if (State == STATE_MORIBUND)
        {
            OSWakeupThread(&CleaningQueue);
        }
        break;
      default:
        break;
    }
}

void SOInit(void)
{
    u32 type;

    if (!Initialized)
    {
        Initialized = TRUE;
        OSRegisterResetFunction(&ResetFunctionInfo);
    }

    // Call IFInit() here to check link status as soon as possible.
    EXIGetType(0, 2, &type);    // Check Serial Port 1
    switch (type)
    {
      case EXI_ETHER:
        if (!IFInit(IF_TYPE_10HALF))
        {
            return;
        }
        break;
      case EXI_MODEM:
        if (!IFInit(IF_TYPE_MODEM))
        {
            return;
        }
        break;
      default:
        return;
    }

    if (State != STATE_CLEAN)
    {
        return;
    }

    // Check if the network have been configured using the
    // low-level IP functions before SOInit().
    if (SOGetHostID() != SOHtoNl(SO_INADDR_ANY) ||
        DHCPGetStatus(NULL) != DHCP_STATE_INIT)
    {
        LowInitialized = TRUE;
    }
    else
    {
        // Do not receive any packets until SOStartup() is called.
        IFMute(TRUE);
    }
}

int SOStartup(const SOConfig* config)
{
    SOHostEnt* ent = &__SOResolver.ent;
    s32        mtu;
    u32        type;

    if (config->vendor  != SO_VENDOR_NINTENDO ||
        config->version != SO_VERSION)
    {
        return SO_EINVAL;
    }

    EXIGetType(0, 2, &type);    // Check Serial Port 1
    switch (type)
    {
      case EXI_ETHER:
        if (!IFInit(IF_TYPE_10HALF))
        {
            return SO_EINVAL;
        }
        break;
      case EXI_MODEM:
        __IFDefault.countryCode = config->countryCode;
        if (!IFInit(IF_TYPE_MODEM))
        {
            return SO_EINVAL;
        }
        break;
      default:
        return SO_EINVAL;
    }

    if (State != STATE_CLEAN)
    {
        return SO_EINVAL;
    }

    if (0 < config->mtu)
    {
        mtu = MAX(68, MIN(1500, config->mtu));
    }
    else
    {
        mtu = 1500;
    }
    Mtu = mtu;
    IPSetMtu(NULL, mtu);

    if (0 < config->rwin)
    {
        Rwin = MAX(68 - IP_MIN_HLEN - TCP_MIN_HLEN, config->rwin);
    }
    else
    {
        Rwin = 0;
    }

    if (0 < config->r2)
    {
        R2 = config->r2;
    }
    else
    {
        R2 = OSSecondsToTicks((OSTime) 100);     // RFC 1122 SHOULD
    }

    UdpSendBuff = config->udpSendBuff;
    if (UdpSendBuff <= 0)
    {
        UdpSendBuff = 1500 - IP_MIN_HLEN - UDP_HLEN;
    }
    if (UdpSendBuff < 576 - IP_MIN_HLEN)
    {
        UdpSendBuff = 576 - IP_MIN_HLEN;
    }
    UdpRecvBuff = config->udpRecvBuff;
    if (UdpRecvBuff <= 0)
    {
        UdpRecvBuff = 3 * UdpSendBuff;
    }
    if (UdpRecvBuff < 576 - IP_MIN_HLEN)
    {
        UdpRecvBuff = 576 - IP_MIN_HLEN;
    }

    OSInitThreadQueue(&CleaningQueue);
    OSInitThreadQueue(&PollingQueue);

    Alloc = config->alloc;
    Free  = config->free;
    Flag  = config->flag;

    if (!LowInitialized)
    {
        if (config->timeWaitBuffer)
        {
            TimeWaitBufSize = config->timeWaitBuffer;
            TimeWaitBuf = SOAlloc(SO_MEM_TIMEWAITBUF, TimeWaitBufSize);
            TCPSetTimeWaitBuffer(TimeWaitBuf, TimeWaitBufSize);
        }

        if (config->reassemblyBuffer)
        {
            ReassemblyBufferSize = config->reassemblyBuffer;
            ReassemblyBuffer = SOAlloc(SO_MEM_REASSEMBLYBUF, ReassemblyBufferSize);
            IPSetReassemblyBuffer(ReassemblyBuffer, ReassemblyBufferSize,
                                  UdpSendBuff + IP_MIN_HLEN);
#ifdef IP_INET6
            if (Flag & SO_FLAG_IPv6)
            {
                IP6ReassemblyBufferSize = config->reassemblyBuffer;
                IP6ReassemblyBuffer     = SOAlloc(SO_MEM_REASSEMBLYBUF, IP6ReassemblyBufferSize);
                IP6SetReassemblyBuffer(IP6ReassemblyBuffer, IP6ReassemblyBufferSize,
                                       UdpSendBuff + (s32) sizeof(IP6Hdr));
            }
#endif // IP_INET6
        }

        // Clear interface configuration error code
        IPClearConfigError(NULL);
    }

    if (LowInitialized)
    {
        // Do nothing
    }
    else if ((Flag & SO_FLAG_PPP) && IsModemAttached())
    {
        Flag &= ~(SO_FLAG_DHCP | SO_FLAG_ZEROCONF);

        if (!PPPInit(&__IFDefault, &PPPLcpConf, &PPPIpcpConf,
                     config->peerid, config->passwd,
                     config->dial, config->dialMode, config->ispCode))
        {
            goto Error;
            // NOT REACHED HERE
        }
        PPPLcpConf.callback = LcpHandler;
    }
    else if (Flag & SO_FLAG_PPPoE)
    {
        Flag &= ~(SO_FLAG_DHCP | SO_FLAG_ZEROCONF);

        PPPoEInit(&__IFDefault, config->serviceName);
        if (!PPPInit(&__IFDefault, &PPPLcpConf, &PPPIpcpConf,
                     config->peerid, config->passwd,
                     NULL, 0, config->ispCode))
        {
            goto Error;
            // NOT REACHED HERE
        }
        PPPLcpConf.callback = LcpHandler;
    }
    else if (Flag & SO_FLAG_DHCP)
    {
        // Ignore the return code from DHCPStartup() since
        // the network may have been configured using the
        // low-level IP functions.
        if (!DHCPStartupEx(DhcpHandler, config->rdhcp, config->hostName))
        {
            LowInitialized = TRUE;
        }

        // Do not automatically restart DHCP state machine.
        DHCPAuto(FALSE);
    }
    else if (config->addr.addr != SOHtoNl(SO_INADDR_ANY))
    {
        // Checks the current host id since the network has
        // been configured using the low-level IP functions.
        if (SOGetHostID() == SOHtoNl(SO_INADDR_ANY))
        {
            IPInitRoute((u8*) &config->addr,
                        (u8*) &config->netmask,
                        (u8*) &config->router);
        }
        else
        {
            LowInitialized = TRUE;
        }
    }

    if (!LowInitialized)
    {
        // Clear ARP cache entries
        ARPRefresh();

        // Join all-hosts group
        IGMPInit(&__IFDefault);
    }

    if (Flag & SO_FLAG_ZEROCONF)
    {
        IPAutoConfig();
    }

#ifdef IP_INET6
    if (Flag & SO_FLAG_IPv6)
    {
        IP6Startup(&__IFDefault);
    }
#endif  // IP_INET6

    IFInitQueue(&LingerQueue);

    // Initialize __SOResolver
    memset(&__SOResolver, 0, sizeof(SOResolver));
    ent->name = __SOResolver.name;
    ent->addrType = SO_PF_INET;
    ent->length = IP_ALEN;
    ent->addrList = __SOResolver.ptrList;
    ent->aliases = (char**) __SOResolver.ptrList + 2;

    State = STATE_INITIALIZED;

    SOSetResolver(&config->dns1, &config->dns2);

    return 0;

Error:
    if (TimeWaitBuf)
    {
        TCPSetTimeWaitBuffer(NULL, 0);
        SOFree(SO_MEM_TIMEWAITBUF, TimeWaitBuf,
               TimeWaitBufSize);
    }
    if (ReassemblyBuffer)
    {
        SOFree(SO_MEM_REASSEMBLYBUF, ReassemblyBuffer, ReassemblyBufferSize);
#ifdef IP_INET6
        if (Flag & SO_FLAG_IPv6)
        {
            SOFree(SO_MEM_REASSEMBLYBUF, IP6ReassemblyBuffer, IP6ReassemblyBufferSize);
        }
#endif // IP_INET6
    }
    return SO_EINVAL;
}

/*---------------------------------------------------------------------------*
  Name:         SOCleanup

  Description:  SSOCleanup() closes all the open sockets and shutdowns the
                socket library.

  Arguments:    None

  Returns:      zero            Succeeded.
                SO_ENETRESET
 *---------------------------------------------------------------------------*/
int SOCleanup(void)
{
    int      s;
    SONode*  node;
    IPInfo*  info;
    IPInfo*  next;
    SOLinger linger;
    int      optlen;
    BOOL     enabled;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }
    State = STATE_MORIBUND;

    // Abort SOPoll() operations
    __IPWakeupPollingThreads();

    for (s = 0; s < SO_SOCKET_MAX; ++s)
    {
        node = &SocketTable[s];
        if (node->ref == 0)
        {
            continue;
        }
        switch (node->proto)
        {
          case IP_PROTO_UDP:
            __SOClose(s);
            break;
          case IP_PROTO_TCP:
            // Force reset
            optlen = sizeof linger;
            linger.onoff  = TRUE;
            linger.linger = 0;
            __SOSetSockOpt(s, SO_SOL_SOCKET, SO_SO_LINGER, &linger, optlen);
            __SOClose(s);
            break;
        }
    }

    // Abort lingering TCPs. Canceled TCPInfo are enqueued into LingerQueue.
    IFIterateQueue(IPInfo*, &TCPInfoQueue, info, next, link)
    {
        TCPInfo* tcp = (TCPInfo*) info;
        TCPObj*  obj = TCPGetObj(tcp);

        ASSERT(obj);
        if (obj->closeCallback == LingerCallback)
        {
            TCPCancel(tcp);
        }
    }

    ICMPReset(TRUE);

    GetNode(-1, NULL);    // Clear linger queue

    DNSClose(&__SOResolver.info);

    if (Flag & SO_FLAG_ZEROCONF)
    {
        // Stop on-going ARPClaim() for the Auto-IP address;
        IPAutoStop();
    }

    if (LowInitialized)
    {
        // Do nothing.
    }
    else if (Flag & SO_FLAG_PPPoE || Flag & SO_FLAG_PPP)
    {
        PPPClose(&PPPIpcpConf);
        enabled = OSDisableInterrupts();
        while (PPPGetState(&PPPLcpConf) != 0 /* Initial */)
        {
            OSSleepThread(&CleaningQueue);
        }
        OSRestoreInterrupts(enabled);
    }
    else if (Flag & SO_FLAG_DHCP)
    {
        enabled = OSDisableInterrupts();
        DHCPCleanup();
        // Wait for release completion
        while (DHCPGetStatus(NULL) != DHCP_STATE_INIT)
        {
            OSSleepThread(&CleaningQueue);
        }
        OSRestoreInterrupts(enabled);
    }
    else
    {
        // Halt network
        IPInitRoute(NULL, NULL, NULL);
        IPSetBroadcastAddr(&__IFDefault, IPLimited);
    }

#ifdef IP_INET6
    MLDOnReset(FALSE);
#endif  // IP_INET6

    if (TimeWaitBuf)
    {
        TCPSetTimeWaitBuffer(NULL, 0);
        SOFree(SO_MEM_TIMEWAITBUF, TimeWaitBuf,
               TimeWaitBufSize);
    }
    if (ReassemblyBuffer)
    {
        IPSetReassemblyBuffer(NULL, 0, UdpSendBuff + IP_MIN_HLEN);
        SOFree(SO_MEM_REASSEMBLYBUF, ReassemblyBuffer, ReassemblyBufferSize);
#ifdef IP_INET6
        if (Flag & SO_FLAG_IPv6)
        {
            IP6SetReassemblyBuffer(NULL, 0, UdpSendBuff + (s32) sizeof(IP6Hdr));
            SOFree(SO_MEM_REASSEMBLYBUF, IP6ReassemblyBuffer, IP6ReassemblyBufferSize);
        }
#endif // IP_INET6
    }

    // Wait until all references to SONode{}s are closed.
    enabled = OSDisableInterrupts();
    while (0 < Allocated)
    {
        // Wait for completion of SOAccept(), etc.
        OSSleepThread(&CleaningQueue);
    }
    OSRestoreInterrupts(enabled);
    ASSERT(Allocated == 0);

    if (!LowInitialized)
    {
        // Mute the network interface so as not receive any further
        // packets.
        IFMute(TRUE);  // XXX remove this line to temporarily fix eth.a lock up bug.

        // Clear ARP cache entries
        ARPRefresh();
    }

#ifdef IP_INET6
    if (Flag & SO_FLAG_IPv6)
    {
        IP6Cleanup(&__IFDefault);
    }
#endif  // IP_INET6

    State = STATE_CLEAN;

    return 0;
}

static s32 GetRwin(void)
{
    if (Rwin)
    {
        return Rwin;
    }

    // Return 2 x MSS
    return 2 * (1500 - IP_MIN_HLEN - TCP_MIN_HLEN);
}

/*---------------------------------------------------------------------------*
  Name:         SOSocket

  Description:  SOSocket() creates an unbound socket and returns a socket
                descriptor.

  Arguments:    af          Specifies the protocol family in which a socket
                            is to be created.  Currently pf must be SO_PF_INET
                            (IPv4 Internet protocols).
                type        Specifies the type of socket to be created.
                            Currently SO_SOCK_STREAM for TCP and SO_SOCK_DGRAM
                            for UDP are supported.
                protocol    Specifies a particular protocol to be used with
                            the socket.  If protocol is zero, the default
                            protocol for this protocol family and type is used.
                            Currently protocol must be zero.

  Returns:      non-negative        The new socket descriptor.
                SO_EAFNOSUPPORT     Non-supported address family.
                SO_EMFILE           No more socket descriptors.
                SO_ENETRESET        Socket library is not initialized.
                SO_ENOMEM           Insufficient memory.
                SO_EPROTONOSUPPORT  Non-supported protocol.
                SO_EPROTOTYPE       Non-supported socket type.
 *---------------------------------------------------------------------------*/
int SOSocket(int af, int type, int protocol)
{
    BOOL     enabled;
    int      socket;
    SONode*  node;
    s32      rc      = -1;
    TCPInfo* tcp     = NULL;
    TCPObj*  obj;
    UDPInfo* udp     = NULL;
    void*    sendbuf = NULL;
    void*    recvbuf = NULL;
    s32      rwin;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }
#ifdef IP_INET6
    if (af != SO_PF_INET && af != SO_PF_INET6)
    {
        return SO_EAFNOSUPPORT;
    }
#else
    if (af != SO_PF_INET)
    {
        return SO_EAFNOSUPPORT;
    }
#endif
    if (protocol != 0)
    {
        return SO_EPROTONOSUPPORT;
    }

    GetNode(-1, NULL);    // Clear linger queue

    // Look for free node
    node = NULL;
    enabled = OSDisableInterrupts();
    for (socket = 0; socket < SO_SOCKET_MAX; ++socket)
    {
        node = &SocketTable[socket];
        if (node->ref == 0)
        {
            ASSERT(node->info == NULL);
            node->ref = 2;  // Reserve node
            break;
        }
    }
    OSRestoreInterrupts(enabled);
    if (node == NULL)
    {
        return SO_EMFILE;
    }

    rwin = GetRwin();

    switch (type)
    {
      case SO_SOCK_STREAM:  // TCP
        switch (af)
        {
          case SO_PF_INET:
            tcp = SOAlloc(SO_MEM_TCP_INFO, sizeof(TCPInfo));
            break;
#ifdef IP_INET6
          case SO_PF_INET6:
            tcp = SOAlloc(SO_MEM_TCP_INFO, sizeof(TCP6Info));
            break;
#endif
        }
        sendbuf = SOAlloc(SO_MEM_TCP_SENDBUF, rwin);
        recvbuf = SOAlloc(SO_MEM_TCP_RECVBUF, rwin);
        rc = TCPSocket(af, tcp);
        if (0 <= rc)
        {
            TCPSetSendBuff(tcp, sendbuf, rwin);
            TCPSetRecvBuff(tcp, recvbuf, rwin);
            TCPSetTimeout(tcp, R2);
        }
        break;
      case SO_SOCK_DGRAM:   // UDP
        switch (af)
        {
          case SO_PF_INET:
            udp = SOAlloc(SO_MEM_UDP_INFO, sizeof(UDPInfo));
            break;
#ifdef IP_INET6
          case SO_PF_INET6:
            udp = SOAlloc(SO_MEM_UDP_INFO, sizeof(UDP6Info));
            break;
#endif
        }
        sendbuf = SOAlloc(SO_MEM_UDP_SENDBUF, UdpSendBuff);
        recvbuf = SOAlloc(SO_MEM_UDP_RECVBUF, UdpRecvBuff);
        rc = UDPSocket(af, udp);
        if (0 <= rc)
        {
            UDPSetRecvBuff(udp, recvbuf, UdpRecvBuff);
            UDPSetSendBuff(udp, sendbuf, UdpSendBuff);
        }
        break;
      default:
        PutNode(node, SO_EPROTOTYPE);
        PutNode(node, SO_EPROTOTYPE);
        return SO_EPROTOTYPE;
    }

    if (rc < 0)
    {
        switch (type)
        {
          case SO_SOCK_STREAM:  // TCP
            switch (af)
            {
              case SO_PF_INET:
                SOFree(SO_MEM_TCP_INFO, tcp, sizeof(TCPInfo));
                break;
#ifdef IP_INET6
              case SO_PF_INET6:
                SOFree(SO_MEM_TCP_INFO, tcp, sizeof(TCP6Info));
                break;
#endif
            }
            SOFree(SO_MEM_TCP_SENDBUF, sendbuf, rwin);
            SOFree(SO_MEM_TCP_RECVBUF, recvbuf, rwin);
            break;
          case SO_SOCK_DGRAM:   // UDP
            switch (af)
            {
              case SO_PF_INET:
                SOFree(SO_MEM_UDP_INFO, udp, sizeof(UDPInfo));
                break;
#ifdef IP_INET6
              case SO_PF_INET6:
                SOFree(SO_MEM_UDP_INFO, udp, sizeof(UDP6Info));
                break;
#endif
            }
            SOFree(SO_MEM_UDP_SENDBUF, sendbuf, UdpSendBuff);
            SOFree(SO_MEM_UDP_RECVBUF, recvbuf, UdpRecvBuff);
            break;
        }
        PutNode(node, SO_ENOMEM);
        PutNode(node, SO_ENOMEM);
        return SO_ENOMEM;
    }

    // Initialize node
    node->flag = 0;
    OSInitMutex(&node->mutexRead);
    OSInitMutex(&node->mutexWrite);

    // Commit open by setting node->info
    switch (type)
    {
      case SO_SOCK_STREAM:  // TCP
        obj = TCPGetObj(tcp);
        obj->node = node;
        node->proto = IP_PROTO_TCP;
        node->info = (IPInfo*) tcp;
        break;
      case SO_SOCK_DGRAM:   // UDP
        node->proto = IP_PROTO_UDP;
        node->info = (IPInfo*) udp;
        break;
    }
    PutNode(node, socket);
    return socket;
}

static void LingerCallback(TCPInfo* info, s32 result)
{
    #pragma unused( result )
    SONode* node;
    TCPObj* obj;

    obj = TCPGetObj(info);
    ASSERT(obj);
    node = obj->node;
    if (node)
    {
        ASSERT(0 < node->ref);
        --node->ref;    // for SOSocket();
    }
    IFEnqueueTail(IPInfo*, &LingerQueue, &info->info, link);
}

static void LingerTimeout(OSAlarm* alarm, OSContext* context)
{
    #pragma unused(context)
    TCPObj*  obj;

    obj = (TCPObj*) ((u8*) alarm - offsetof(TCPObj, lingerAlarm));
    TCPCancel((TCPInfo*) obj->pair);
}

static int __SOClose(int s)
{
    SONode*  node;
    IPInfo*  info;
    TCPInfo* tcp;
    TCPObj*  log;
    UDPInfo* udp;
    SOLinger linger;
    int      optlen;
    BOOL     enabled;
    s32      rc = -1;
    IFQueue  queue;
    TCPObj*  obj;

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }
    ASSERT(0 < node->ref);

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        udp = (UDPInfo*) info;
        rc = UDPClose(udp);
        ASSERT(0 <= rc);
        --node->ref;    // for SOSocket()
        break;
      case IP_PROTO_TCP:
        tcp = (TCPInfo*) info;

        optlen = sizeof(linger);
        rc = TCPGetSockOpt(tcp, SO_SOL_SOCKET, SO_SO_LINGER, &linger, &optlen);
        ASSERT(0 <= rc);

        IFInitQueue(&queue);

        enabled = OSDisableInterrupts();

        obj = TCPGetObj(tcp);

        // Remove all TCPInfo that are not accepted
        while (!IFIsEmptyQueue(&obj->queueBacklog))
        {
            IFDequeueHead(TCPObj*, &obj->queueBacklog, log, linkLog);
            log->logging = NULL;
            TCPCancel((TCPInfo*) log->pair);
            IFEnqueueTail(TCPObj*, &queue, log, linkLog);
        }
        while (!IFIsEmptyQueue(&obj->queueCompleted))
        {
            IFDequeueHead(TCPObj*, &obj->queueCompleted, log, linkLog);
            log->logging = NULL;
            TCPCancel((TCPInfo*) log->pair);
            IFEnqueueTail(TCPObj*, &queue, log, linkLog);
        }

        if (TCPGetState(tcp) == TCP_STATE_LISTEN)
        {
            // Force cancel
            rc = TCPCancel(tcp);
            ASSERT(TCPGetState(tcp) != TCP_STATE_LISTEN);

            // Wake up all accepting threads. Tcp is released when every call to
            // SOAccept() is completed.
            if (0 < obj->accepting)
            {
                OSWakeupThread(&obj->queueThread);
            }

            --node->ref;    // for SOSocket();
        }
        else if (node->flag & SO_O_NONBLOCK)
        {
            // Dismantles the connection and returns immediately
            rc = TCPCancel(tcp);
            --node->ref;    // for SOSocket();
        }
        else if (linger.onoff)
        {
            if (linger.linger <= 0)
            {
                // Resets the connection and returns immediately
                rc = TCPCancel(tcp);
            }
            else
            {
                // Blocks until all data sent till time-out expires
                // Note alarm must not be expired before TCPClose()
                // is called.
                OSSetAlarm(&obj->lingerAlarm,
                           OSSecondsToTicks((OSTime) linger.linger),
                           LingerTimeout);
                rc = TCPClose(tcp);
            }
            --node->ref;    // for SOSocket();
        }
        else
        {
            // Linger off: Returns immediately and close the connection
            // in background and waits up to 15 seconds (changeable by
            // I_SETCLTIME ioctl request).
            OSSetAlarm(&obj->lingerAlarm,
                       OSSecondsToTicks((OSTime) 15),
                       LingerTimeout);

            rc = TCPCloseAsync(tcp, LingerCallback, NULL);
            if (node->ref == 2)
            {
                // Normal case. Only SOClose() is the active call to socket s.
                obj->node = NULL;
                --node->ref;    // for SOSocket();
            }
            // Note memory blocks will be released after LingerCallback() is called.
            node->info = NULL;  // Mark as closed
        }

        OSRestoreInterrupts(enabled);

        while (!IFIsEmptyQueue(&queue))
        {
            IFDequeueHead(TCPObj*, &queue, log, linkLog);
            TCPFree((TCPInfo*) log->pair);
        }

        ASSERT(0 <= rc);
        break;
      default:
        rc = SO_EBADF;
        break;
    }

    PutNode(node, rc);

    return (rc < 0) ? SO_EBADF : 0;
}

/*---------------------------------------------------------------------------*
  Name:         SOClose

  Description:  SOClose() closes the socket descriptor.

                The following table summarizes the SOClose() behavior for
                the SO_SOCK_STREAM (TCP) socket:

                SOLinger                Description

                onoff = 0 (default)     SOClose() returns as quickly as
                                        possible and all data is transmitted
                                        in the background.

                onoff = 1, linger = 0   SOClose() returns immediately and the
                                        current connection is aborted.

                onoff = 1, linger != 0  SOClose() blocks until all data is
                                        transmitted for up to the specified
                                        linger time.

  Arguments:    s       The socket descriptor to be closed.

  Returns:      zero            Succeeded.
                SO_EBADF
                SO_ENETRESET
 *---------------------------------------------------------------------------*/
int SOClose(int s)
{
    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }
    return __SOClose(s);
}

static void AcceptCallback(TCPInfo* info, s32 result)
{
    TCPObj* tcp;
    TCPObj* logging;

    tcp = TCPGetObj(info);
    logging = tcp->logging;
    if (logging == NULL)
    {
        // listening socket has been closed.
        return;
        // NOT REACHED HERE
    }

    if (0 <= result)
    {
        IFDequeueItem(TCPObj*, &logging->queueBacklog,   tcp, linkLog);
        IFEnqueueTail(TCPObj*, &logging->queueCompleted, tcp, linkLog);
        OSWakeupThread(&logging->queueThread);
        if (0 < logging->pair->poll)
        {
            __IPWakeupPollingThreads();
        }
    }
    else
    {
        // Reinsert tcp to backlog queue again
        // Note in this case, AcceptCallback() is called from
        // the middle of TCPAbort() in TCPRxmitTimeOut().
        // Therefore we should not call TCPOpen() inside the callback.
        // However, in this particular case, we can call TCPOpen() from
        // here. XXX
        void* sendData = tcp->sendData;
        void* recvData = tcp->recvData;
        s32   sendBuff = tcp->sendBuff;
        s32   recvBuff = tcp->recvBuff;

        IFDequeueItem(TCPObj*, &logging->queueBacklog, tcp, linkLog);
        TCPCancel(info);

        // TCPSocket() clears the tcp structure by zero. The logging
        // queues are broken unless they are re-initialized.
        TCPSocket(info->info.family, info);
        TCPSetSendBuff(info, sendData, sendBuff);
        TCPSetRecvBuff(info, recvData, recvBuff);
        TCPSetTimeout(info, R2);

        tcp->logging = logging;
        IFEnqueueTail(TCPObj*, &logging->queueBacklog, tcp, linkLog);
        TCPAcceptAsync(info, (TCPInfo*) logging->pair, AcceptCallback, NULL);
    }
}

// Add one more TCPInfo to the listening socket's backlog queue
static TCPInfo* AddBackLog(TCPObj* listening)
{
    u8       af;
    TCPInfo* tcp;
    TCPObj*  obj;
    void*    sendbuf;
    s32      sendbufLen;
    void*    recvbuf;
    s32      recvbufLen;
    s32      rc;
    BOOL     enabled;

    ASSERT(listening);
    af = listening->pair->family;
    switch (af)
    {
      case SO_PF_INET:
        tcp = SOAlloc(SO_MEM_TCP_INFO, sizeof(TCPInfo));
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        tcp = SOAlloc(SO_MEM_TCP_INFO, sizeof(TCP6Info));
        break;
#endif  // IP_INET6
    }
    sendbufLen = listening->sendBuff;
    recvbufLen = listening->recvBuff;
    sendbuf = SOAlloc(SO_MEM_TCP_SENDBUF, sendbufLen);
    recvbuf = SOAlloc(SO_MEM_TCP_RECVBUF, recvbufLen);

    rc = TCPSocket(af, tcp);
    if (rc < 0)
    {
        goto Error;
    }

    TCPSetSendBuff(tcp, sendbuf, sendbufLen);
    TCPSetRecvBuff(tcp, recvbuf, recvbufLen);
    TCPSetTimeout(tcp, R2);

    enabled = OSDisableInterrupts();
    obj = TCPGetObj(tcp);
    if (listening->state == TCP_STATE_LISTEN)
    {
        obj->logging = listening;
        IFEnqueueTail(TCPObj*, &listening->queueBacklog, obj, linkLog);
        OSRestoreInterrupts(enabled);
        TCPAcceptAsync(tcp, (TCPInfo*) listening->pair, AcceptCallback, NULL);
        OSRestoreInterrupts(enabled);
        return tcp;
        // NOT REACHED HERE
    }

    OSRestoreInterrupts(enabled);
Error:
    SOFree(SO_MEM_TCP_RECVBUF, recvbuf, recvbufLen);
    SOFree(SO_MEM_TCP_SENDBUF, sendbuf, sendbufLen);
    switch (af)
    {
      case SO_PF_INET:
        SOFree(SO_MEM_TCP_INFO, tcp, sizeof(TCPInfo));
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        SOFree(SO_MEM_TCP_INFO, tcp, sizeof(TCP6Info));
        break;
#endif
    }
    return NULL;
}

/*---------------------------------------------------------------------------*
  Name:         SOListen

  Description:  SOListen() enables the connection-mode socket to accept
                connections.

  Arguments:    s           The socket descriptor.
                backlog     The maximum number of pending connections in the
                            socket's listen backlog queue. If backlog is less
                            than or equal to zero, backlog is set to one.

  Returns:      zero            Succeeded.
                SO_EBADF
                SO_EINVAL
                SO_ENETRESET
                SO_ENOBUFS
                SO_EOPNOTSUPP
 *---------------------------------------------------------------------------*/
int SOListen(int s, int backlog)
{
    SONode*  node;
    IPInfo*  info;
    TCPInfo* listening;
    s32      rc;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    if (backlog < 1)
    {
        backlog = 1;
    }

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        rc = SO_EOPNOTSUPP;
        break;
      case IP_PROTO_TCP:
        listening = (TCPInfo*) info;
        rc = TCPListen(listening, NULL, NULL, NULL, NULL);
        switch (rc)
        {
          case IP_ERR_NONE:
            while (0 < backlog--)
            {
                if (AddBackLog(TCPGetObj(listening)) == NULL)
                {
                    break;
                }
            }
            break;
          case IP_ERR_INS_RESOURCES:
            rc = SO_ENOBUFS;
            break;
          case IP_ERR_EXIST:
          default:
            rc = SO_EINVAL;
            break;
        }
        break;
      default:
        rc = SO_EBADF;
        break;
    }

    PutNode(node, rc);
    return rc;
}

/*---------------------------------------------------------------------------*
  Name:         SOAccept

  Description:  SOAccept() extracts the first connection on the queue of
                pending connections, creates a new socket with the same
                socket type, protocol and address family as the specified
                socket, and returns a new socket descriptor. The original
                socket remains open and can accept more connections.

                SOAccept() blocks if there are no connections pending,
                unless the socket descriptor is set to the nonblocking mode
                with SOFcntl().

  Arguments:    s       Specifies a socket that was created with SOSocket(),
                        has been bound to an address with SOBind(), and has
                        issued a successful call to SOListen().
                addr    Either a null pointer, or a pointer to a socket
                        address structure where the address of the peer for
                        the accepted connection is stored. If specifying a
                        non-null pointer, the len field of the socket address
                        must be properly initialized
                        (e.g., sizeof(SOSockAddrIn)).

  Returns:      non-negative    Socket descriptor of the accepted socket.
                SO_EBADF
                SO_ECONNABORTED
                SO_EEINVAL
                SO_EMFILE
                SO_ENETRESET
                SO_EOPNOTSUPP
                SO_EAGAIN (SO_EWOULDBLOCK)
 *---------------------------------------------------------------------------*/
int SOAccept(int s, void* sockAddr)
{
    BOOL     enabled;
    SONode*  node;
    IPInfo*  info;
    TCPInfo* listeningInfo;
    TCPObj*  listening;
    TCPObj*  tcp;
    int      socket;
    s32      rc;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    ASSERT(sockAddr == NULL ||
           sizeof(SOSockAddrIn) <= ((SOSockAddr*) sockAddr)->len);
    if (sockAddr &&
        ((SOSockAddr*) sockAddr)->len < sizeof(SOSockAddrIn))
    {
        return SO_EINVAL;
    }

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    enabled = OSDisableInterrupts();

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        rc = SO_EOPNOTSUPP;
        break;
      case IP_PROTO_TCP:
        listeningInfo = (TCPInfo*) info;
        listening = TCPGetObj(listeningInfo);
      Retry:
        if (listening->state != TCP_STATE_LISTEN)
        {
            rc = SO_EINVAL;
            break;
        }
        ++listening->accepting;
        while (listening->state == TCP_STATE_LISTEN &&
               IFIsEmptyQueue(&listening->queueCompleted))
        {
            if (node->flag & SO_O_NONBLOCK)
            {
                --listening->accepting;
                rc = SO_EAGAIN;
                goto Error;
                // NOT REACHED HERE
            }
            OSSleepThread(&listening->queueThread);
        }
        --listening->accepting;
        if (listening->state != TCP_STATE_LISTEN)
        {
            // listening socket has been closed.
            rc = SO_ECONNABORTED;
            break;
        }
        for (socket = 0; socket < SO_SOCKET_MAX; ++socket)
        {
            SONode* connected = &SocketTable[socket];
            if (connected->ref == 0)
            {
                TCPInfo* ti;

                // Retreive the first completed connection
                IFDequeueHead(TCPObj*, &listening->queueCompleted, tcp, linkLog);
                ASSERT(tcp);
                ti = (TCPInfo*) tcp->pair;

                rc = 0;
                if (sockAddr)
                {
                    rc = TCPGetRemoteSocket(ti, sockAddr);
                }

                if (tcp->state != TCP_STATE_ESTABLISHED && tcp->state != TCP_STATE_CLOSE_WAIT ||
                    rc < 0)
                {
                    void* sendData = tcp->sendData;
                    void* recvData = tcp->recvData;
                    s32   sendBuff = tcp->sendBuff;
                    s32   recvBuff = tcp->recvBuff;

                    TCPCancel(ti);
                    TCPSocket(ti->info.family, ti);
                    TCPSetSendBuff(ti, sendData, sendBuff);
                    TCPSetRecvBuff(ti, recvData, recvBuff);
                    TCPSetTimeout(ti, R2);
                    tcp->logging = listening;
                    IFEnqueueTail(TCPObj*, &listening->queueBacklog, tcp, linkLog);
                    TCPAcceptAsync(ti, listeningInfo, AcceptCallback, NULL);
                    goto Retry;
                }

                // Initialize connected
                connected->flag = node->flag;   // Inherit flags
                connected->ref = 1;
                OSInitMutex(&connected->mutexRead);
                OSInitMutex(&connected->mutexWrite);

                // Commit accept by setting connected->info
                connected->proto = IP_PROTO_TCP;
                connected->info = tcp->pair;
                rc = socket;

                // Add one more backlog TCPInfo
                OSRestoreInterrupts(enabled);   // it's okay to call OSRestoreInterrupts() twice.
                AddBackLog(listening);
                break;
            }
        }
        if (SO_SOCKET_MAX <= socket)
        {
            rc = SO_EMFILE;
        }
        break;
      default:
        rc = SO_EBADF;
        break;
    }

Error:
    OSRestoreInterrupts(enabled);

    PutNode(node, rc);
    return rc;
}

/*---------------------------------------------------------------------------*
  Name:         SOBind

  Description:  SOBind() assigns a local socket address to a socket that has
                no local socket address assigned. Sockets created with the
                SOSocket() are initially not bound to any address.

  Arguments:    s           The socket descriptor to be bound.
                sockAddr    A pointer to a socket address structure
                            containing the address to be bound to the socket.

  Returns:      zero            Succeeded.
                SO_EADDRINUSE
                SO_EAFNOSUPPORT
                SO_EBADF
                SO_EINVAL
                SO_ENETRESET
 *---------------------------------------------------------------------------*/
int SOBind(int s, const void* sockAddr)
{
    SONode*  node;
    IPInfo*  info;
    TCPInfo* tcp;
    UDPInfo* udp;
    s32      rc = -1;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    ASSERT(sockAddr != NULL &&
           sizeof(SOSockAddrIn) <= ((SOSockAddr*) sockAddr)->len);
    if (sockAddr == NULL ||
        ((SOSockAddr*) sockAddr)->len < sizeof(SOSockAddrIn))
    {
        return SO_EINVAL;
    }

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        udp = (UDPInfo*) info;
        rc = UDPBind(udp, sockAddr);
        break;
      case IP_PROTO_TCP:
        tcp = (TCPInfo*) info;
        rc = TCPBind(tcp, sockAddr);
        break;
      default:
        PutNode(node, SO_EBADF);
        return SO_EBADF;
        break;
    }

    switch (rc)
    {
      case IP_ERR_NONE:
        rc = 0;
        break;
      case IP_ERR_INV_SOCKET:
        rc = SO_EAFNOSUPPORT;
        break;
      case IP_ERR_EXIST:
        rc = SO_EADDRINUSE;
        break;
      case IP_ERR_INVALID:
      default:
        rc = SO_EINVAL;
        break;
    }
    PutNode(node, rc);
    return rc;
}

/*---------------------------------------------------------------------------*
  Name:         SOConnect

  Description:  SOConnect() attempts to make a connection on a socket.
                If the socket has not already been bound to a local address,
                SOConnect() binds it to an address which is unused and local.

                For SO_SOCK_STREAM (TCP) sockets, SOConnect() normally blocks
                until the connection is established. SOConnect() returns as
                quickly as possible if the socket is set to the nonblocking
                mode with SOFcntl().

                For SOCK_DGRAM sockets, SOConnect() sets the socket's
                peer address, and no connection is made. The peer address
                identifies where all datagrams are sent on subsequent SOSend()
                functions, and limits the remote sender for subsequent
                SORecv() functions. If sockAddr is a null address for the
                protocol, the socket's peer address is reset.

  Arguments:    s           The socket descriptor.
                sockAddr    A pointer to a socket address structure
                            containing the peer address.

  Returns:      zero                Succeeded.
                SO_EAFNOSUPPORT
                SO_EBADF
                SO_ECONNREFUSED
                SP_ECONNRESET
                SO_EINPROGRESS
                SO_EINVAL
                SO_EISCONN
                SO_ENETDOWN
                SO_ENETRESET
                SO_ENETUNREACH
                SO_ENOBUFS
                SO_ETIMEDOUT
 *---------------------------------------------------------------------------*/
int SOConnect(int s, const void* sockAddr)
{
    SONode*  node;
    IPInfo*  info;
    TCPInfo* tcp;
    UDPInfo* udp;
    s32      rc;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    ASSERT(sockAddr != NULL &&
           sizeof(SOSockAddrIn) <= ((SOSockAddr*) sockAddr)->len);
    if (sockAddr == NULL ||
        ((SOSockAddr*) sockAddr)->len < sizeof(SOSockAddrIn))
    {
        return SO_EINVAL;
    }

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        udp = (UDPInfo*) info;
        if (((SOSockAddr*) sockAddr)->family == SO_PF_UNSPEC)
        {
            sockAddr = &SockAnyIn;
        }
        rc = UDPConnect(udp, sockAddr);
        break;
      case IP_PROTO_TCP:
        tcp = (TCPInfo*) info;
        if ((node->flag & SO_O_NONBLOCK) == 0)
        {
            rc = TCPConnect(tcp, sockAddr);
            if (rc == IP_ERR_AGAIN)
            {
                rc = IP_ERR_EXIST;
            }
        }
        else
        {
            rc = TCPConnectAsync(tcp, sockAddr, NULL, NULL);
            if (rc == 0 && TCPGetObj(tcp)->openCallback)
            {
                rc = IP_ERR_BUSY;
            }
        }
        break;
      default:
        PutNode(node, SO_EBADF);
        return SO_EBADF;
        break;
    }

    switch (rc)
    {
      case IP_ERR_NONE:
        rc = 0;
        break;
      case IP_ERR_AGAIN:
        rc = SO_EALREADY;
        break;
      case IP_ERR_BUSY:
        rc = SO_EINPROGRESS;
        break;
      case IP_ERR_INV_SOCKET:
        rc = SO_EAFNOSUPPORT;
        break;
      case IP_ERR_EXIST:
        rc = SO_EISCONN;
        break;
      case IP_ERR_RESET:
        rc = SO_ECONNRESET;
        break;
      case IP_ERR_REFUSED:
        rc = SO_ECONNREFUSED;
        break;
      case IP_ERR_TIMEOUT:
        rc = SO_ETIMEDOUT;
        break;
      case IP_ERR_INVALID:
        rc = SO_EINVAL;
        break;
      case IP_ERR_INS_RESOURCES:
        rc = SO_ENOBUFS;
        break;
      case IP_ERR_NETDOWN:
        rc = SO_ENETDOWN;
        break;
      default:
      case IP_ERR_UNREACHABLE:
        rc = SO_ENETUNREACH;
        break;
    }

    PutNode(node, rc);
    return rc;
}

/*---------------------------------------------------------------------------*
  Name:         SOGetPeerName

  Description:  SOGetPeerName() gets the name of the peer connected to the
                specified socket.

  Arguments:    s           The socket descriptor.
                sockAddr    A pointer to a socket address structure where
                            the address of the peer connected to the
                            specified socket is stored. The len field of the
                            socket address must be properly initialized
                            (e.g., sizeof(SOSockAddrIn)).

  Returns:      zero
                SO_EBADF
                SO_EINVAL
                SO_ENETRESET
                SO_ENOTCONN
 *---------------------------------------------------------------------------*/
int SOGetPeerName(int s, void* sockAddr)
{
    SONode*  node;
    IPInfo*  info;
    TCPInfo* tcp;
    UDPInfo* udp;
    s32 rc = -1;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    ASSERT(sockAddr);
    ASSERT(sizeof(SOSockAddrIn) <= ((SOSockAddr*) sockAddr)->len);
    if (sockAddr == NULL ||
        ((SOSockAddr*) sockAddr)->len < sizeof(SOSockAddrIn))
    {
        // Note not following the Open Group base specifications
        return SO_EINVAL;
    }

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        udp = (UDPInfo*) info;
        rc = UDPGetRemoteSocket(udp, sockAddr);
        break;
      case IP_PROTO_TCP:
        tcp = (TCPInfo*) info;
        rc = TCPGetRemoteSocket(tcp, sockAddr);
        break;
      default:
        PutNode(node, SO_EBADF);
        return SO_EBADF;
        break;
    }

    if (rc < 0)
    {
        rc = SO_EBADF;
    }
    else if (((SOSockAddrIn*) sockAddr)->port == 0)
    {
        rc = SO_ENOTCONN;
    }
    else
    {
        rc = 0;
    }

    PutNode(node, rc);
    return rc;
}

/*---------------------------------------------------------------------------*
  Name:         SOGetSockName

  Description:  SOGetSockName() gets the locally-bound name (address) of
                the specified socket.

  Arguments:    s           The socket descriptor.
                sockAddr    A pointer to a socket address structure to get
                            the locally-bound name. The len field of the
                            socket address must be properly initialized
                            (e.g., sizeof(SOSockAddrIn)).

  Returns:      zero            Succeeded.
                SO_EBADF        Bad socket descriptor.
                SO_EINVAL       Invalid operation.
                SO_ENETRESET    Socket library is not initialized.

  Note:         If the socket has not been bound to a local name, the value
                stored in the object pointed to by sockAddr is unspecified
                in POSIX.
 *---------------------------------------------------------------------------*/
int SOGetSockName(int s, void* sockAddr)
{
    SONode*  node;
    IPInfo*  info;
    TCPInfo* tcp;
    UDPInfo* udp;
    s32 rc = -1;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    ASSERT(sockAddr);
    ASSERT(sizeof(SOSockAddrIn) <= ((SOSockAddr*) sockAddr)->len);
    if (sockAddr == NULL ||
        ((SOSockAddr*) sockAddr)->len < sizeof(SOSockAddrIn))
    {
        // Note not following the Open Group base specifications
        return SO_EINVAL;
    }

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        udp = (UDPInfo*) info;
        rc = UDPGetLocalSocket(udp, sockAddr);
        break;
      case IP_PROTO_TCP:
        tcp = (TCPInfo*) info;
        rc = TCPGetLocalSocket(tcp, sockAddr);
        break;
      default:
        PutNode(node, SO_EBADF);
        return SO_EBADF;
        break;
    }

    PutNode(node, rc);
    return (rc < 0) ? SO_EBADF : 0;
}

/*---------------------------------------------------------------------------*
  Name:         SOShutdown

  Description:  SOShutdown() shuts down socket send and receive operations.

  Arguments:    s       The socket descriptor to shut down.
                how     Specifies the type of shutdown:

                        SO_SHUT_RD      Disables further receive operations.
                        SO_SHUT_WR      Disables further send operations.
                        SO_SHUT_RDWR    Disables further send and receive
                                        operations.

  Returns:      zero        Succeeded.
                SO_EBADF
                SO_ENOTCONN
                SO_EINVAL
 *---------------------------------------------------------------------------*/
int SOShutdown(int s, int how)
{
    SONode*  node;
    IPInfo*  info;
    TCPInfo* tcp;
    s32 rc = -1;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    switch (how)
    {
      case SO_SHUT_RD:
      case SO_SHUT_WR:
      case SO_SHUT_RDWR:
        break;
      default:
        return SO_EINVAL;
    }

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        rc = 0;
        break;
      case IP_PROTO_TCP:
        tcp = (TCPInfo*) info;
        rc = TCPShutdown(tcp, (u32) how);
        break;
      default:
        PutNode(node, SO_EBADF);
        return SO_EBADF;
        break;
    }

    switch (rc)
    {
      case IP_ERR_NONE:
      case IP_ERR_CLOSING:
        rc = 0;
        break;
      case IP_ERR_NOT_EXIST:
        rc = SO_ENOTCONN;
        break;
      default:
      case IP_ERR_INVALID:
        rc = SO_EINVAL;
        break;
    }
    PutNode(node, rc);
    return rc;
}

int SORead(int s, void* buf, int len)
{
    return SORecvFrom(s, buf, len, 0, NULL);
}

int SORecv(int s, void* buf, int len, int flags)
{
    return SORecvFrom(s, buf, len, flags, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         SORecv, SORecv and SORecvFrom

  Description:  SORecv(), SORecv() and SORecvFrom() attempt to read len bytes
                from the other end of the socket.

                SORead() is equivalent to SORecv() with no flags set.

                SORecv(), SORecv() and SORecvFrom() block until a message
                arrives if no messages are available in the socket's receive
                buffer, unless the socket descriptor is set to the nonblocking
                mode with SOFcntl().

                For SOCK_DGRAM sockets, the entire message shall be read in a
                single operation. If a message is too long to fit in the
                supplied buffer, and MSG_PEEK is not set in the flags, the
                excess bytes shall be discarded. For SOCK_STREAM sockets,
                message boundaries shall be ignored. In this case, data shall
                be returned to the user as soon as it becomes available, and
                no data shall be discarded.

  Arguments:    s           The socket descriptor.
                buf         A pointer to the receive buffer.
                len         The length of the receive buffer.
                flags       Specifies the type of message reception: the flags
                            are formed by logically OR'ing zero or more of the
                            following values:

                            MSG_PEEK    Peeks at an incoming message. The data
                                        is treated as unread and the next
                                        SORecv() or similar function shall
                                        still return this data.

                            MSG_OOB     Requests out-of-band data.
                                        (SO_SOCK_STREAM socket only)

                sockFrom    A pointer to a socket address structure to
                            retrieve the name of the peer. The len field of
                            the socket address must be properly initialized
                            (e.g., sizeof(SOSockAddrIn)).

  Returns:      non-negative    The length of the message in bytes written to
                                the buffer.
                SO_EAGAIN
                SO_EBADF
                SO_ECONNRESET
                SO_EINTR
                SO_EINVAL
                SO_ENETRESET
                SO_ENOTCONN
                SO_EOPNOTSUPP
                SO_ETIMEDOUT
 *---------------------------------------------------------------------------*/
int SORecvFrom(int s, void* buf, int len, int flags, void* sockFrom)
{
    SONode*  node;
    IPInfo*  info;
    UDPInfo* udp;
    TCPInfo* tcp;
    s32      rc;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    ASSERT(sockFrom == NULL ||
           sizeof(SOSockAddrIn) <= ((SOSockAddr*) sockFrom)->len);
    if (sockFrom &&
        ((SOSockAddr*) sockFrom)->len < sizeof(SOSockAddrIn))
    {
        // Note not following the Open Group base specifications
        return SO_EINVAL;
    }

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        // Check flags first
        if (flags & ~(SO_MSG_PEEK | SO_MSG_DONTWAIT))
        {
            PutNode(node, SO_EOPNOTSUPP);
            return SO_EOPNOTSUPP;
            // NOT REACHED HERE
        }

        OSLockMutex(&node->mutexRead);
        if (node->info == NULL) // Closed?
        {
            rc = IP_ERR_CLOSING;
        }
        else
        {
            if (node->flag & SO_O_NONBLOCK)
            {
                flags |= SO_MSG_DONTWAIT;
            }
            udp = (UDPInfo*) info;
            rc = UDPReceiveEx(udp, buf, len, NULL, sockFrom, (u32) flags);
        }
        OSUnlockMutex(&node->mutexRead);

        break;
      case IP_PROTO_TCP:
        // Check flags first
        // XXX Check if SO_MSG_OOB, then OOBINLINE is not enabled.
        if (flags & ~(SO_MSG_OOB | SO_MSG_PEEK | SO_MSG_DONTWAIT))
        {
            PutNode(node, SO_EOPNOTSUPP);
            return SO_EOPNOTSUPP;
            // NOT REACHED HERE
        }

        tcp = (TCPInfo*) info;
        if (sockFrom)
        {
            rc = TCPGetRemoteSocket(tcp, sockFrom);
            if (rc < 0)
            {
                PutNode(node, SO_EBADF);
                return SO_EBADF;
            }
        }

        OSLockMutex(&node->mutexRead);
        if (node->info == NULL) // Closed?
        {
            rc = IP_ERR_CLOSING;
        }
        else
        {
            if (node->flag & SO_O_NONBLOCK)
            {
                flags |= SO_MSG_DONTWAIT;
            }
            tcp = (TCPInfo*) info;
            if ((flags & SO_MSG_OOB) == 0)
            {
                rc = TCPReceiveEx(tcp, buf, len, (u32) flags);
            }
            else
            {
                rc = TCPReceiveUrgEx(tcp, buf, len, (u32) flags);
            }
        }
        OSUnlockMutex(&node->mutexRead);

        break;
      default:
        PutNode(node, SO_EBADF);
        return SO_EBADF;
        break;
    }

    if (rc < 0)
    {
        switch (rc)
        {
          case IP_ERR_AGAIN:
          case IP_ERR_BUSY:
            rc = SO_EAGAIN;
            break;
          case IP_ERR_NOT_EXIST:
          case IP_ERR_CLOSING:
            rc = SO_ENOTCONN;
            break;
          case IP_ERR_CANCELED:
            rc = SO_EINTR;
            break;
          case IP_ERR_NETDOWN:
          case IP_ERR_TIMEOUT:
            rc = SO_ETIMEDOUT;
            break;
          case IP_ERR_SOURCE_QUENCH:
          case IP_ERR_RESET:
          case IP_ERR_REFUSED:
            rc = SO_ECONNRESET;
            break;
          case IP_ERR_DATASIZE:
          case IP_ERR_INVALID:
          default:
            rc = SO_EINVAL;
            break;
        }
    }
    PutNode(node, rc);
    return rc;
}

int SOWrite(int s, const void* buf, int len)
{
    return SOSendTo(s, buf, len, 0, NULL);
}

int SOSend(int s, const void* buf, int len, int flags)
{
    return SOSendTo(s, buf, len, flags, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         SOWrite, SOSend and SendTo

  Description:  SOWrite(), SOSend() and SendTo() send a message through the
                specified socket.

                SOWrite() is equivalent to SOSend() with no flags set. If
                the socket is connectionless-mode, SOSendTo() sends the
                message to the address specified by sockTo. If the socket
                is connection-mode, sockTo is ignored.

                SOWrite(), SOSend() and SendTo() block if space is not
                available at the sending socket's send buffer, unless the
                socket descriptor is set to the nonblocking mode with
                SOFcntl().

  Arguments:    s       The socket descriptor.
                buf     A pointer to the buffer containing the message to
                        send.
                len     The length of the message to be sent in bytes. If the
                        message is too long to pass through the underlying
                        protocol, SOSend() fails and no data shall be
                        transmitted.
                flags   The type of message transmission: the flags are
                        formed by logically OR'ing zero or more of the
                        following values (SO_SOCK_STREAM socket only):

                        MSG_OOB Sends out-of-band data on sockets that support
                                out-of-band communications. (SO_SOCK_STREAM
                                stream socket only)

                sockTo  A pointer to a socket address structure containing
                        the destination address.

  Returns:      non-negative        The number of bytes sent. If SO_O_NONBLOCK
                                    is set for the socket descriptor, the
                                    return value can be smaller than len
                                    (short count).
                SO_EAFNOSUPPORT
                SO_EAGAIN
                SO_EBADF
                SO_ECONNRESET
                SO_EDESTADDRREQ
                SO_EINTR
                SO_EINVAL
                SO_EMSGSIZE
                SO_ENETDOWN
                SO_ENETRESET
                SO_ENETUNREACH
                SO_ENOBUFS
                SO_ENOTCONN
                SO_EOPNOTSUPP
                SO_ETIMEDOUT
 *---------------------------------------------------------------------------*/
int SOSendTo(int s, const void* buf, int len, int flags, const void* sockTo)
{
    SONode*  node;
    IPInfo*  info;
    UDPInfo* udp;
    TCPInfo* tcp;
    s32      rc;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    ASSERT(sockTo == NULL ||
           sizeof(SOSockAddrIn) <= ((SOSockAddr*) sockTo)->len);
    if (sockTo &&
        ((SOSockAddr*) sockTo)->len < sizeof(SOSockAddrIn))
    {
        return SO_EINVAL;
    }

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        // Check flags first
        if (flags)
        {
            PutNode(node, SO_EOPNOTSUPP);
            return SO_EOPNOTSUPP;
            // NOT REACHED HERE
        }

        OSLockMutex(&node->mutexWrite);
        if (node->info == NULL) // Closed?
        {
            rc = IP_ERR_CLOSING;
        }
        else
        {
            udp = (UDPInfo*) info;
            switch (flags)
            {
              case 0:
                rc = UDPSend(udp, buf, len, sockTo);
                break;
            }
        }
        OSUnlockMutex(&node->mutexWrite);

        break;
      case IP_PROTO_TCP:
        // Check flags first
        if (flags & ~(SO_MSG_OOB | SO_MSG_DONTWAIT))
        {
            PutNode(node, SO_EOPNOTSUPP);
            return SO_EOPNOTSUPP;
            // NOT REACHED HERE
        }

        OSLockMutex(&node->mutexWrite);
        if (node->info == NULL) // Closed?
        {
            rc = IP_ERR_CLOSING;
        }
        else
        {
            tcp = (TCPInfo*) info;
            if (node->flag & SO_O_NONBLOCK)
            {
                flags |= SO_MSG_DONTWAIT;
            }

            switch (flags)
            {
              case 0:
                rc = TCPSend(tcp, buf, len);
                break;
              case SO_MSG_OOB:
                rc = TCPSendUrg(tcp, buf, len);
                break;
              case SO_MSG_DONTWAIT:
                rc = TCPSendNonblock(tcp, buf, len);
                break;
              case SO_MSG_DONTWAIT | SO_MSG_OOB:
                rc = TCPSendUrgNonblock(tcp, buf, len);
                break;
            }

            if (rc == IP_ERR_SOCKET_UNSPECIFIED)
            {
                rc = IP_ERR_NOT_EXIST;  // To return SO_ENOTCONN.
            }
        }
        OSUnlockMutex(&node->mutexWrite);

        break;
      default:
        PutNode(node, SO_EBADF);
        return SO_EBADF;
        // NOT REACHED HERE
        break;
    }

    if (rc < 0)
    {
        switch (rc)
        {
          case IP_ERR_INV_SOCKET:
            rc = SO_EAFNOSUPPORT;
            break;
          case IP_ERR_SOCKET_UNSPECIFIED:
            rc = SO_EDESTADDRREQ;
            break;
          case IP_ERR_DATASIZE:
            rc = SO_EMSGSIZE;
            break;
          case IP_ERR_UNREACHABLE:
            rc = SO_ENETUNREACH;
            break;
          case IP_ERR_INS_RESOURCES:
            rc = SO_ENOBUFS;
            break;
          case IP_ERR_AGAIN:
          case IP_ERR_BUSY:
            rc = SO_EAGAIN;
            break;
          case IP_ERR_NOT_EXIST:
          case IP_ERR_CLOSING:
            rc = SO_ENOTCONN;
            break;
          case IP_ERR_CANCELED:
            rc = SO_EINTR;
            break;
          case IP_ERR_TIMEOUT:
            rc = SO_ETIMEDOUT;
            break;
          case IP_ERR_SOURCE_QUENCH:
          case IP_ERR_RESET:
          case IP_ERR_REFUSED:
            rc = SO_ECONNRESET;
            break;
          case IP_ERR_INVALID:
            rc = SO_EINVAL;
            break;
          case IP_ERR_NETDOWN:
            rc = SO_ENETDOWN;
            break;
          default:
            rc = SO_EBADF;
            break;
        }
    }
    PutNode(node, rc);
    return rc;
}

/*---------------------------------------------------------------------------*
  Name:         SOSockAtMark

  Description:  SOSockAtMark() determines whether the specified socket
                descriptor is at the out-of-band data mark.

                An out-of-band data can be send and received using the
                SO_MSG_OOB flag for SO_SOCK_STREAM sockets.

  Note:         The GameCube socket library employs Berkeley interpretation
                for the TCP urgent pointer:  The TCP urgent pointer points to
                the byte next to the urgent byte.

  Arguments:    s           The socket descriptor

  Returns:      zero            There is no mark, or data precedes the mark.
                one             The socket is at an out-of-band data mark.
                SO_EBADF        Bad socket descriptor.
                SO_ENETRESET    Socket library is not initialized.
 *---------------------------------------------------------------------------*/
int SOSockAtMark(int s)
{
    SONode*  node;
    IPInfo*  info;
    TCPInfo* tcp;
    s32      rc;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        rc = 0;
        break;
      case IP_PROTO_TCP:
        tcp = (TCPInfo*) info;
        rc = TCPGetUrgOffset(tcp);
        if (rc < 0)
        {
            rc = SO_EBADF;
        }
        else
        {
            rc = (rc == 1) ? 1 : 0;
        }
        break;
      default:
        rc = SO_EBADF;
        break;
    }
    PutNode(node, rc);
    return rc;
}

/*---------------------------------------------------------------------------*
  Name:         SOGetSockOpt

  Description:  SOGetSockOpt() gets the socket options.

  Arguments:    s           The socket descriptor.
                level       The protocol level (one of SO_SO_*).
                optname     The option name to get (one of SO_* ).
                optval      A pointer to the buffer where the option value
                            is stored.
                optlen      The option length in bytes. Before the call,
                            *optlen must be set to the size of the optval
                            buffer. On return, *optlen contains the number of
                            bytes actually stored in optval.

  Returns:      zero
                SO_EBADF
                SO_EINVAL
                SO_ENETRESET
                SO_ENOPROTOOPT
 *---------------------------------------------------------------------------*/
int SOGetSockOpt(int s, int level, int optname,
                 void* optval, int* optlen)
{
    SONode*  node;
    IPInfo*  info;
    UDPInfo* udp;
    TCPInfo* tcp;
    s32      rc;
    s32      buff;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        udp = (UDPInfo*) info;
        if (level == SO_SOL_SOCKET)
        {
            switch (optname)
            {
              case SO_SO_SNDBUF:
                if (optlen && sizeof(int) <= *optlen && optval)
                {
                    rc = UDPGetSendBuff(udp, NULL, &buff);
                    if (rc == IP_ERR_NONE)
                    {
                        *(int*) optval = (int) buff;
                        *optlen = sizeof(int);
                    }
                }
                goto Done;
                // NOT REACHED HERE
                break;
              case SO_SO_RCVBUF:
                rc = IP_ERR_INVALID;
                if (optlen && sizeof(int) <= *optlen && optval)
                {
                    rc = UDPGetRecvBuff(udp, NULL, &buff);
                    if (rc == IP_ERR_NONE)
                    {
                        *(int*) optval = (int) buff;
                        *optlen = sizeof(int);
                    }
                }
                goto Done;
                // NOT REACHED HERE
                break;
              case SO_SO_ERROR:
                *(int*) optval = node->error;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
                goto Done;
                // NOT REACHED HERE
                break;
              default:
                break;
            }
        }
        rc = UDPGetSockOpt((UDPInfo*) info, level, optname, optval, optlen);
        break;
      case IP_PROTO_TCP:
        tcp = (TCPInfo*) info;
        if (level == SO_SOL_SOCKET)
        {
            switch (optname)
            {
              case SO_SO_SNDBUF:
                if (optlen && sizeof(int) <= *optlen && optval)
                {
                    rc = TCPGetSendBuff(tcp, NULL, &buff);
                    if (rc == IP_ERR_NONE)
                    {
                        *(int*) optval = (int) buff;
                        *optlen = sizeof(int);
                    }
                }
                goto Done;
                // NOT REACHED HERE
                break;
              case SO_SO_RCVBUF:
                rc = IP_ERR_INVALID;
                if (optlen && sizeof(int) <= *optlen && optval)
                {
                    rc = TCPGetRecvBuff(tcp, NULL, &buff);
                    if (rc == IP_ERR_NONE)
                    {
                        *(int*) optval = (int) buff;
                        *optlen = sizeof(int);
                    }
                }
                goto Done;
                // NOT REACHED HERE
                break;
              case SO_SO_ERROR:
                *(int*) optval = node->error;
                *optlen = sizeof(int);
                rc = IP_ERR_NONE;
                goto Done;
                // NOT REACHED HERE
                break;
              default:
                break;
            }
        }
        rc = TCPGetSockOpt((TCPInfo*) info, level, optname, optval, optlen);
        break;
      default:
        PutNode(node, SO_EBADF);
        return SO_EBADF;
        break;
    }

Done:
    switch (rc)
    {
      case 0:
        rc = 0;
        break;
      case IP_ERR_INV_OPTION:
        rc = SO_ENOPROTOOPT;
        break;
      default:
        rc = SO_EINVAL;
        break;
    }

    PutNode(node, rc);
    return rc;
}

static int __SOSetSockOpt(int s, int level, int optname,
                          const void* optval, int optlen)
{
    SONode*  node;
    IPInfo*  info;
    TCPInfo* tcp;
    UDPInfo* udp;
    s32      rc;

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    switch (info->proto)
    {
      case IP_PROTO_UDP:
        udp = (UDPInfo*) info;
        if (level == SO_SOL_SOCKET)
        {
            switch (optname)
            {
              case SO_SO_SNDBUF:
                rc = IP_ERR_INVALID;
                if (sizeof(int) <= optlen && optval)
                {
                    void* sendData;
                    s32   sendBuff = *(int*) optval;

                    if (sendBuff < 576 - 40)
                    {
                        sendBuff = 576 - 40;
                    }
                    sendBuff += sizeof(IFDatagram) + IP_MIN_HLEN + UDP_HLEN;
                    sendData = SOAlloc(SO_MEM_UDP_SENDBUF, sendBuff);
                    if (sendData)
                    {
                        void* prevData;
                        s32   prevBuff;

                        rc = UDPGetSendBuff(udp, &prevData, &prevBuff);
                        ASSERT(rc == IP_ERR_NONE);
                        rc = UDPSetSendBuff(udp, sendData, sendBuff);
                        if (rc == IP_ERR_NONE)
                        {
                            SOFree(SO_MEM_UDP_SENDBUF, prevData, prevBuff);
                        }
                        else
                        {
                            SOFree(SO_MEM_UDP_SENDBUF, sendData, sendBuff);
                        }
                    }
                    else
                    {
                        rc = IP_ERR_INS_RESOURCES;
                    }
                }
                goto Done;
                // NOT REACHED HERE
                break;
              case SO_SO_RCVBUF:
                rc = IP_ERR_INVALID;
                if (sizeof(int) <= optlen && optval)
                {
                    void* recvData;
                    s32   recvBuff = *(int*) optval;

                    if (recvBuff < 576 - 40)
                    {
                        recvBuff = 576 - 40;
                    }
                    recvData = SOAlloc(SO_MEM_UDP_RECVBUF, recvBuff);
                    if (recvData)
                    {
                        void* prevData;
                        s32   prevBuff;

                        rc = UDPGetRecvBuff(udp, &prevData, &prevBuff);
                        ASSERT(rc == IP_ERR_NONE);
                        rc = UDPSetRecvBuff(udp, recvData, recvBuff);
                        if (rc == IP_ERR_NONE)
                        {
                            SOFree(SO_MEM_UDP_RECVBUF, prevData, prevBuff);
                        }
                        else
                        {
                            SOFree(SO_MEM_UDP_RECVBUF, recvData, recvBuff);
                        }
                    }
                    else
                    {
                        rc = IP_ERR_INS_RESOURCES;
                    }
                }
                goto Done;
                // NOT REACHED HERE
                break;
              default:
                break;
            }
        }
        rc = UDPSetSockOpt((UDPInfo*) info, level, optname, optval, optlen);
        break;
      case IP_PROTO_TCP:
        tcp = (TCPInfo*) info;
        if (level == SO_SOL_SOCKET)
        {
            switch (optname)
            {
              case SO_SO_SNDBUF:
                rc = IP_ERR_INVALID;
                if (sizeof(int) <= optlen && optval)
                {
                    void* sendData;
                    s32   sendBuff = *(int*) optval;

                    if (sendBuff < 576 - 40)
                    {
                        sendBuff = 576 - 40;
                    }
                    sendData = SOAlloc(SO_MEM_TCP_SENDBUF, sendBuff);
                    if (sendData)
                    {
                        void* prevData;
                        s32   prevBuff;

                        rc = TCPGetSendBuff(tcp, &prevData, &prevBuff);
                        ASSERT(rc == IP_ERR_NONE);
                        rc = TCPSetSendBuff(tcp, sendData, sendBuff);
                        if (rc == IP_ERR_NONE)
                        {
                            SOFree(SO_MEM_TCP_SENDBUF, prevData, prevBuff);
                        }
                        else
                        {
                            SOFree(SO_MEM_TCP_SENDBUF, sendData, sendBuff);
                        }
                    }
                    else
                    {
                        rc = IP_ERR_INS_RESOURCES;
                    }
                }
                goto Done;
                // NOT REACHED HERE
                break;
              case SO_SO_RCVBUF:
                rc = IP_ERR_INVALID;
                if (sizeof(int) <= optlen && optval)
                {
                    void* recvData;
                    s32   recvBuff = *(int*) optval;

                    if (recvBuff < 576 - 40)
                    {
                        recvBuff = 576 - 40;
                    }
                    recvData = SOAlloc(SO_MEM_TCP_RECVBUF, recvBuff);
                    if (recvData)
                    {
                        void* prevData;
                        s32   prevBuff;

                        rc = TCPGetRecvBuff(tcp, &prevData, &prevBuff);
                        ASSERT(rc == IP_ERR_NONE);
                        rc = TCPSetRecvBuff(tcp, recvData, recvBuff);
                        if (rc == IP_ERR_NONE)
                        {
                            SOFree(SO_MEM_TCP_RECVBUF, prevData, prevBuff);
                        }
                        else
                        {
                            SOFree(SO_MEM_TCP_RECVBUF, recvData, recvBuff);
                        }
                    }
                    else
                    {
                        rc = IP_ERR_INS_RESOURCES;
                    }
                }
                goto Done;
                // NOT REACHED HERE
                break;
              default:
                break;
            }
        }
        rc = TCPSetSockOpt(tcp, level, optname, optval, optlen);
        break;
      default:
        PutNode(node, SO_EBADF);
        return SO_EBADF;
        break;
    }

Done:
    switch (rc)
    {
      case 0:
        rc = 0;
        break;
      case IP_ERR_INV_OPTION:
        rc = SO_ENOPROTOOPT;
        break;
      case IP_ERR_INS_RESOURCES:
        rc = SO_ENOMEM;
        break;
      default:
        rc = SO_EINVAL;
        break;
    }

    PutNode(node, rc);
    return rc;
}

/*---------------------------------------------------------------------------*
  Name:         SOSetSockOpt

  Description:  SOSetSockOpt() sets the socket options.

  Arguments:    s           The socket descriptor.
                level       The protocol level (one of SO_SO_*).
                optname     The option name to get (one of SO_* ).
                optval      A pointer to the buffer where the option value
                            is stored.
                optlen      Option length in bytes. Before the call, *optlen
                            must be set to the size of the optval buffer. On
                            return, *optlen contains the number of bytes
                            actually stored in optval.

  Returns:      zero
                SO_EBADF
                SO_EINVAL
                SO_ENETRESET
                SO_ENOMEM
                SO_ENOPROTOOPT
 *---------------------------------------------------------------------------*/
int SOSetSockOpt(int s, int level, int optname,
                 const void* optval, int optlen)
{
    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }
    return __SOSetSockOpt(s, level, optname, optval, optlen);
}

/*---------------------------------------------------------------------------*
  Name:         SOFcntl

  Description:  SOFcntl() performs the following operations on open socket
                descriptors.

                cmd         Argument            Type
                SO_F_GETFT  none
                SO_F_SETFL  OR-ed SO_O_* flags  int

                To set the socket descriptor to non-blocking mode, use the
                following mode:

                    val = SOFcntl(s, SO_F_GETFL, 0);
                    SOFcntl(s, SO_F_SETFL, val | SO_O_NONBLOCK);

                To revert the socket descriptor to blocking mode, use the
                following mode:

                    val = SOFcntl(s, SO_F_GETFL, 0);
                    SOFcntl(s, SO_F_SETFL, val & ~SO_O_NONBLOCK);

                The socket descriptor is in blocking mode by default.

  Arguments:    s       Socket descriptor.
                cmd     Command (SO_F_*).

  Returns:      zero or more integer
                SO_EBADF
                SO_EINVAL
                SO_ENETRESET
 *---------------------------------------------------------------------------*/
int SOFcntl(int s, int cmd, ...)
{
    SONode* node;
    IPInfo* info;
    s32     rc;
    va_list marker;
    int     arg;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    node = GetNode(s, &info);
    if (node == NULL || info == NULL)
    {
        return SO_EBADF;
    }

    switch (info->proto)
    {
      case IP_PROTO_UDP:
      case IP_PROTO_TCP:
        switch (cmd)
        {
          case SO_F_GETFL:
            rc = node->flag;
            break;
          case SO_F_SETFL:
            va_start(marker, cmd);
            arg = va_arg(marker, int);
            va_end(marker);
            node->flag = (u8) arg;
            rc = 0;
            break;
          default:
            rc = IP_ERR_INVALID;
            break;
        }
        break;
      default:
        rc = IP_ERR_INVALID;
        break;
    }

    rc = ((0 <= rc) ? rc : SO_EINVAL);
    PutNode(node, rc);

    return rc;
}

/*---------------------------------------------------------------------------*
  Name:         SOGetHostByName

  Description:  SOGetHostByName() returns information about the host named
                /name/.

  Note:         SOGetHostByName() is not reentrant and not thread-safe.

  Arguments:    name    A host name or a numeric address string in the
                        dotted-decimal notation.

  Returns:      A pointer to SOHostEnt structure if the requested entry was
                found. Otherwise NULL.

  XXX:          /name/ shall be included in the list of aliases returned.
 *---------------------------------------------------------------------------*/
SOHostEnt* SOGetHostByName(const char* name)
{
    u8**     ptr;
    u8*      addr;
    s32      rc;
    SOInAddr inaddr;

    if (SOInetAtoN(name, &inaddr))
    {
        return SOGetHostByAddr(&inaddr, IP_ALEN, SO_PF_INET);
    }

    strncpy(__SOResolver.name, name, SO_MAXDNAME);
    rc = DNSGetAddr(&__SOResolver.info, __SOResolver.name,
                    __SOResolver.addrList, IP_ALEN * 35);
    if (0 <= rc)
    {
        __SOResolver.ent.addrType = SO_PF_INET;
        for (ptr = __SOResolver.ptrList, addr = __SOResolver.addrList;
             0 < rc;
             rc -= IP_ALEN, ++ptr, addr += IP_ALEN)
        {
            *ptr = addr;
        }
        *ptr = NULL;
        __SOResolver.ent.aliases = (char**) ptr;
        return &__SOResolver.ent;
        // NOT REACHED HERE
    }
    return NULL;
}

/*---------------------------------------------------------------------------*
  Name:         SOGetHostByAddr

  Description:  SOGetHostByAddr() returns information about the host with
                address /addr/.

  Note:         SOGetHostByAddr() is not reentrant and not thread-safe.

  Arguments:    addr    A pointer to an address in network byte order.
                len     The length of the address pointed to by addr.
                type    The family type of the address. (SO_PF_INET for
                        an IPv4 Internet address).

  Returns:      A pointer to SOHostEnt structure if the requested entry was
                found. Otherwise NULL.
 *---------------------------------------------------------------------------*/
SOHostEnt* SOGetHostByAddr(const void* addr, int len, int type)
{
    SOSockAddrIn  sa;
    SOSockAddrIn6 sa6;
    u8**          ptr;

    switch (type)
    {
      case SO_PF_INET:
        if (len != sizeof(SOInAddr))
        {
            break;
        }
        memset(&sa, 0, sizeof(SOSockAddrIn));
        sa.len = sizeof(SOSockAddrIn);
        sa.family = SO_PF_INET;
        memcpy(&sa.addr, addr, sizeof(SOInAddr));
        if (0 <= SOGetNameInfo(&sa, __SOResolver.name, SO_MAXDNAME, NULL, 0, SO_NI_NAMEREQD))
        {
            __SOResolver.ent.addrType = SO_PF_INET;
            memcpy(__SOResolver.addrList, addr, sizeof(SOInAddr));
            ptr = __SOResolver.ptrList;
            *ptr = __SOResolver.addrList;
            ++ptr;
            *ptr = NULL;
            return &__SOResolver.ent;
            // NOT REACHED HERE
        }
        break;
      case SO_PF_INET6:
        if (len != sizeof(SOIn6Addr))
        {
            break;
        }
        memset(&sa6, 0, sizeof(SOSockAddrIn6));
        sa6.len = sizeof(SOSockAddrIn6);
        sa6.family = SO_PF_INET6;
        memcpy(&sa6.addr, addr, sizeof(SOIn6Addr));
        if (0 <= SOGetNameInfo(&sa6, __SOResolver.name, SO_MAXDNAME, NULL, 0, SO_NI_NAMEREQD))
        {
            __SOResolver.ent.addrType = SO_PF_INET6;
            memcpy(__SOResolver.addrList, addr, sizeof(SOIn6Addr));
            ptr = __SOResolver.ptrList;
            *ptr = __SOResolver.addrList;
            ++ptr;
            *ptr = NULL;
            return &__SOResolver.ent;
            // NOT REACHED HERE
        }
        break;
      default:
        break;
    }
    return NULL;
}

/*---------------------------------------------------------------------------*
  Name:         SOGetHostID

  Description:  SOGetHostID() returns the current primary IPv4 address of
                the host.

  Note:         While DHCP or PPPoE host configuration is in progress,
                SOGetHostID() returns zero (SO_INADDR_ANY).

  Arguments:    None.

  Returns:      The current primary IPv4 address of the host in the network
                byte order.
 *---------------------------------------------------------------------------*/
long SOGetHostID(void)
{
    long addr;

    IPGetAddr(NULL, (u8*) &addr);
    return addr;
}

static void PollTimeout(OSAlarm* alarm, OSContext* context)
{
    #pragma unused(alarm, context)
    OSWakeupThread(&PollingQueue);
}

void __IPWakeupPollingThreads(void)
{
    OSWakeupThread(&PollingQueue);
}

/*---------------------------------------------------------------------------*
  Name:         SOPoll

  Description:  SOPoll() examines the socket descriptor sets to see whether
                some of them are ready for reading, writing, etc.

  Arguments:    fds         Array of SOPollFD{}.
                nfds        Number of SOPollFD{} in the fds array.
                timeout     Timeout. Inf if SO_INFTIM.

  Returns:      Positive        The total number of descriptors being ready.
                Zero            The call timed out and no descriptors have
                                been selected.
                SO_ENETRESET    The socket library is not initialzied.
                SO_EINVAL       nfds is greater than SO_SOCKET_MAX.
 *---------------------------------------------------------------------------*/
int SOPoll(SOPollFD fds[], unsigned nfds, OSTime timeout)
{
    unsigned  i;
    SONode*   node;
    int       selected;
    SOPollFD* pollfd;
    BOOL      enabled;
    OSAlarm   alarm;
    short     revents;
    IPInfo*   info;

    if (State != STATE_INITIALIZED)
    {
        return SO_ENETRESET;
    }

    if (SO_SOCKET_MAX < nfds)
    {
        return SO_EINVAL;
    }

    // Get nodes
    enabled = OSDisableInterrupts();
    for (i = 0; i < nfds; ++i)
    {
        pollfd = &fds[i];
        pollfd->revents = 0;

        // Get node
        node = NULL;
        if (0 <= pollfd->fd && pollfd->fd < SO_SOCKET_MAX)
        {
            node = &SocketTable[pollfd->fd];
            if (node->ref <= 0 || node->info == NULL) // Closed?
            {
                node = NULL;
            }
            else
            {
                ++node->ref;
            }
        }
        if (node == NULL)
        {
            // Just ignore
            continue;
        }

        info = node->info;
        ++info->poll;
    }
    OSRestoreInterrupts(enabled);

    if (0 < timeout)
    {
        OSCreateAlarm(&alarm);
        OSSetAlarm(&alarm, timeout, PollTimeout);
    }

    enabled = OSDisableInterrupts();
    selected = 0;
    while (State == STATE_INITIALIZED)
    {
        for (i = 0; i < nfds; ++i)
        {
            pollfd = &fds[i];
            pollfd->revents = 0;

            // Get node
            node = NULL;
            if (0 <= pollfd->fd && pollfd->fd < SO_SOCKET_MAX)
            {
                node = &SocketTable[pollfd->fd];
                if (node->ref <= 0 || node->info == NULL) // Closed?
                {
                    node = NULL;
                }
            }
            if (node == NULL)
            {
                // Just ignore
                continue;
            }

            info = node->info;
            revents = (short) (pollfd->events | SO_POLLERR | SO_POLLHUP | SO_POLLNVAL);
            switch (info->proto)
            {
              case IP_PROTO_UDP:
                revents &= __UDPPoll((UDPInfo*) node->info);
                break;
              case IP_PROTO_TCP:
                revents &= __TCPPoll((TCPInfo*) node->info);
                break;
              default:
                revents = 0;
                break;
            }
            if (revents)
            {
                ++selected;
                pollfd->revents = revents;
            }
        }
        if (0 < selected || timeout == 0 || (0 < timeout && alarm.handler == NULL))
        {
            break;
        }
        OSSleepThread(&PollingQueue);
    }
    OSRestoreInterrupts(enabled);

    if (0 < timeout)
    {
        OSCancelAlarm(&alarm);
    }

    for (i = 0; i < nfds; ++i)
    {
        pollfd = &fds[i];
        if (0 <= pollfd->fd && pollfd->fd < SO_SOCKET_MAX)
        {
            node = &SocketTable[pollfd->fd];
            if (0 < node->ref && node->info)
            {
                enabled = OSDisableInterrupts();
                node->info->poll -= 1;
                OSRestoreInterrupts(enabled);
                PutNode(node, node->error);
            }
        }
    }

    return selected;
}

/*---------------------------------------------------------------------------*
  Name:         OnReset

  Description:  Reset function for OSResetSystem()

  Arguments:    final       TRUE if OSResetSystem() is about to reset
                            the system

  Returns:      TRUE if ready to reset.
 *---------------------------------------------------------------------------*/
static BOOL OnReset(BOOL final)
{
    #pragma unused( final )

    State = STATE_RESET;
    return TRUE;
}

int SOGetInterfaceOpt(IPInterface* interface, int level, int optname,
                      void* optval, int* optlen)
{
    s32 rc;

    if (!Initialized)
    {
        return SO_ENETRESET;
    }

    rc = IFGetSockOpt(interface, level, optname, optval, optlen);
    switch (rc)
    {
      case 0:
        rc = 0;
        break;
      case IP_ERR_INV_OPTION:
        rc = SO_ENOPROTOOPT;
        break;
      default:
        rc = SO_EINVAL;
        break;
    }
    return rc;
}

int SOSetInterfaceOpt(IPInterface* interface, int level, int optname,
                      const void* optval, int optlen)
{
    s32 rc;

    if (!Initialized)
    {
        return SO_ENETRESET;
    }

    rc = IFSetSockOpt(interface, level, optname, optval, optlen);
    switch (rc)
    {
      case 0:
        rc = 0;
        break;
      case IP_ERR_INV_OPTION:
        rc = SO_ENOPROTOOPT;
        break;
      default:
        rc = SO_EINVAL;
        break;
    }
    return rc;
}
