
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IP4.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IP4.c,v $
  Revision 1.4  2006/04/19 01:03:40  mxu
  fix a compiling error when VERBOSE is defined

  Revision 1.3  2006/04/12 01:45:05  mxu
  change sprintf to snprintf

  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    5     2/14/06 18:47 Shiki
    Revised to collect interface statistics.

    4     12/13/05 19:21 Shiki
    Implemented IP4SelectSourceAddress() to support RFC 3927.

    3     12/01/05 17:52 Shiki
    Added support for IGMPv2.

    2     04/12/21 16:52 Ueno_kyu
    Removed duplicate definition of constant addresses.

    1     04/11/02 11:01 Ueno_kyu
    Added support for IPv6 Core Protocol.

    42    04/09/22 10:25 Ueno_kyu
    Added support for ping over IPv4.

    41    6/30/04 13:28 Shiki
    Fixed a bug in IPOut() enbugged by the previous check-in.

    40    6/29/04 11:08 Shiki
    Modified the use of IF_FLAG_* for better loopback support. Now
    IF_FLAG_* is set to IFDatagram{} before sending the packet.

    39    6/09/04 15:57 Shiki
    IPv6 pilot implementation

    35    1/26/04 11:26 Shiki
    Modified IPAtoN() to return non-NULL pointer if succeeded.

    34    10/29/03 21:56 Shiki
    Added support for fragmenting outgoing datagrams.
    Implemented IFInitDatagram().

    33    10/22/03 10:47 Shiki
    Modified to get ephemeral port number between 49152 and 65535 rather
    than from between 1024 and. 5000.

    32    9/03/03 9:42 Shiki
    Fixed IPConnect() to check UDP connect operation strictly.

    31    8/21/03 20:58 Shiki
    Added support for SACK/FACK.

    30    5/07/03 11:19 Shiki
    Clean up.

    28    4/01/03 10:19 Shiki
    Modified IP multicast logic so that a socket receives multicast
    datagrams only from the joined group.

    27    3/27/03 17:38 Shiki
    Added support for multicast.

    26    1/22/03 18:05 Shiki
    Fixed IPBind() to support UDP.

    25    12/06/02 10:20 Shiki
    Fixed IPConnect() not to commit connect if TCPInfo is connecting to the
    same destination from the same local socket.

    24    11/15/02 9:44 Shiki
    Fixed not to use macro version of isspace() for SN.

    23    7/29/02 10:24 Shiki
    Implemented Ethernet packet length check code.

    22    7/10/02 17:05 Shiki
    Revised VERBOSE message.

    21    6/14/02 10:32 Shiki
    Revised IPAtoN() to make it compatible with inet_aton().

    20    4/26/02 16:47 Shiki
    Added support for check sum error counters.

    19    4/25/02 9:09 Shiki
    Fixed IPOut() not to filter out loopback datagram.

    18    4/24/02 11:17 Shiki
    Modified IPOut() to check datagram source IP address against possible
    network configuration change..
    Fixed IPIn() so it will accept every IP packet if the interface address
    is not configured and even if the interface alias is configured.

    17    4/23/02 15:12 Shiki
    Added function description for IPOut().

    16    4/18/02 18:33 Shiki
    Revised error code from IPConnect().

    15    4/18/02 9:08 Shiki
    Modified IP[Set|Get]SockOpt() to return IP_ERR_INV_OPTION error for
    unsupported options.

    14    4/12/02 19:16 Shiki
    Modified IPConnect() to reject invalid remote IP address for TCP.

    13    4/12/02 13:33 Shiki
    Modified IPIn() to silently discard TCP segment to bcast/mcast addr.

    12    4/10/02 18:36 Shiki
    Modified IPIn() to silently discard link-layer-only broadcast datagram.

    11    4/08/02 17:45 Shiki
    Fixed IPGetAnonPort() to increment anonymous port number correctly.

    10    4/08/02 13:59 Shiki
    Added IPGetSockOpt() and IPSetSockOpt().
    Revised using new IPSocket{} type.

    9     4/05/02 14:08 Shiki
    Refined using 'const'.

    8     4/04/02 17:24 Shiki
    Enabled call to IPReassemble().

    7     3/27/02 20:18 Shiki
    Revised IPIn() to sync with new IPIsBroadcastAddr() implementation.

    6     3/27/02 17:48 Shiki
    Modified IPIn() to discard datagram with incomplete IP source route
    options.

    5     3/27/02 9:37 Shiki
    Fixed to use the alias address for src address if the interface address
    is not configured.

    4     3/18/02 20:31 Shiki
    Added __IPIsMember().

    3     3/15/02 11:49 Shiki
    Added support for loopback interface.

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
#include <dolphin/iop_libc.h>
#endif // IOP_OS

#include <dolphin/os.h>
#include <dolphin/ip.h>
#include <dolphin/socket.h>
#include "IPPrivate.h"

#ifndef IOP_OS
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#endif // IOP_OS
 
static u16 Id = 1;      // IP packet identification

/*---------------------------------------------------------------------------*
  Name:         IPPrintAddr

  Description:  Print the spcified IP address to the debug output

  Arguments:    addr    IP address

  Returns:      None
 *---------------------------------------------------------------------------*/
 void IPPrintAddr(u8* addr)
{
    OSReport("%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
}

/*---------------------------------------------------------------------------*
  Name:         IPAtoN

  Description:  Convert the standard IPv4 dotted decimal notation to
                an Internet binary address

  Arguments:    dotted  String in IPv4 dotted decimal notation
                addr    Pointer to an Internet binary address

  Returns:      Non-zero pointer upon successful completion. NULL otherwise.
 *---------------------------------------------------------------------------*/
char* IPAtoN(const char* dotted, u8* addr)
{
    int   c;
    u32   part[IP_ALEN];
    int   n;
    u32   val;
    int   base;

    n = 0;
    c = *dotted;
    for (;;)
    {
        if (!(isdigit)(c))
        {
            return NULL;
        }
        base = 10;
        if (c == '0')
        {
            c = *++dotted;
            if (c == 'x' || c == 'X')
            {
                base = 16;
                c = *++dotted;
            }
            else
            {
                base = 8;
            }
        }

        for (val = 0 ;; c = *++dotted)
        {
            if ((isdigit)(c))
            {
                val *= base;
                val += c - '0';
            }
            else if (base == 16 && (isxdigit)(c))
            {
                val <<= 4;
                val += 10 + c - ((islower)(c) ? 'a' : 'A');
            }
            else
            {
                break;
            }
        }
        part[n++] = val;
        if (c == '.')
        {
            if (IP_ALEN <= n || 255 < val)
            {
                return NULL;
            }
            c = *++dotted;
        }
        else if (127 < c)   // !isascii()
        {
            return NULL;
        }
        else
        {
            break;
        }
    }

    switch (n)
    {
      case 1:
        addr[0] = (u8) (val >> 24);
        addr[1] = (u8) (val >> 16);
        addr[2] = (u8) (val >> 8);
        addr[3] = (u8) val;
        break;
      case 2:
        if (0xffffff < val)
        {
            return NULL;
        }
        addr[0] = (u8) part[0];
        addr[1] = (u8) (val >> 16);
        addr[2] = (u8) (val >> 8);
        addr[3] = (u8) val;
        break;
      case 3:
        if (0xffff < val)
        {
            return NULL;
        }
        addr[0] = (u8) part[0];
        addr[1] = (u8) part[1];
        addr[2] = (u8) (val >> 8);
        addr[3] = (u8) val;
        break;
      case 4:
        addr[0] = (u8) part[0];
        addr[1] = (u8) part[1];
        addr[2] = (u8) part[2];
        addr[3] = (u8) val;
        break;
      default:
        return NULL;
    }
    return (char*) dotted;
}

// Convert binary address to dotted-decimal notation
char* IPNtoA(const u8* addr)
{
    static char ascii[SO_INET_ADDRSTRLEN];

#ifdef IOP_OS
    snprintf(ascii, SO_INET_ADDRSTRLEN, "%d.%d.%d.%d", addr[0], addr[1], 
        addr[2], addr[3]);
#else
    sprintf(ascii, "%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
#endif // IOP_OS
    return ascii;
}

/*---------------------------------------------------------------------------*
  Name:         IPLookupInfo

  Description:  Scans queue of IPInfo looking for a matching one.

  Arguments:    queue       Queue of IPInfo
                srcAddr     Remote IP address
                dstAddr     Local IP address
                src         Remote port number
                dst         Local port number
                flag        One of IF_FLAG_*

  Returns:      Pointer to IPInfo or NULL

  Note:         One behind cache is useless for UDP but pretty usuful for TCP
 *---------------------------------------------------------------------------*/
IPInfo* IP4LookupInfo(IFQueue* queue,
                      const u8* srcAddr, const u8* dstAddr, u16 src, u16 dst,
                      u32 flag)
{
#ifdef IOP_OS
    TCPIP_UNUSED(dstAddr);    
#else
    #pragma unused(dstAddr)
#endif // IOP_OS
    IPInfo*   info;
    IPInfo*   next;
    int       wildcard;
    int       minimum = 3;
    IPInfo*   match = NULL;
#ifdef IOP_OS
    s32       mcast = 0;
#else
    s32       mcast;
#endif // IOP_OS
    IPSocket* local;
    IPSocket* remote;

    if (IP_CLASSD(dstAddr)) // Multicast?
    {
        mcast = IPMulticastLookup(dstAddr, IPAddrAny /* XXX */);
        if (mcast < 0)
        {
            return NULL;
        }
    }

    IFIterateQueue(IPInfo*, queue, info, next, link)
    {
        if (info->family != SO_PF_INET)
        {
            continue;
        }

        local = IPGetLocalSockAddr(info);
        remote = IPGetRemoteSockAddr(info);

        if (local->port == 0 || local->port != dst)
        {
            continue;
        }

        if (IP_CLASSD(dstAddr)) // Multicast?
        {
            if ((info->flag & IP_INFO_FLAG_MCAST(mcast)) == 0) // Joined?
            {
                continue;
            }

            if ((flag & IF_FLAG_LOOPBACK) &&    // Loopback?
                (info->flag & IP_INFO_FLAG_MCASTLOOP) == 0)
            {
                continue;
            }
        }

        wildcard = 0;

        if (IP_ADDR_NE(dstAddr, IPAddrAny))
        {
            if (IP_ADDR_EQ(local->addr, IPAddrAny))
            {
                ++wildcard;
            }
            else if (IP_ADDR_NE(local->addr, dstAddr))
            {
                continue;
            }
        }
        else if (IP_ADDR_NE(local->addr, IPAddrAny))
        {
            ++wildcard;
        }

        if (IP_ADDR_NE(srcAddr, IPAddrAny))
        {
            if (IP_ADDR_EQ(remote->addr, IPAddrAny))
            {
                ++wildcard;
            }
            else if (remote->port != src ||
                     IP_ADDR_NE(remote->addr, srcAddr))
            {
                continue;
            }
        }
        else if (IP_ADDR_NE(remote->addr, IPAddrAny))
        {
            ++wildcard;
        }

        if (wildcard < minimum)
        {
            match = info;
            minimum = wildcard;
            if (minimum == 0)
            {
                break;
            }
        }
    }
    return match;
}

/*---------------------------------------------------------------------------*
  Name:         IPBind

  Description:  Specifies the local socket

  Arguments:    Queue   Queue of IPInfo
                info    IPInfo to which local socket is assigned
                socket  Port number must be other than zero.
                        Address can be 0.0.0.0 (any).
                reuse

  Returns:
 *---------------------------------------------------------------------------*/
s32 IP4Bind(IFQueue* queue, IPInfo* info, const IPSocket* socket, BOOL reuse)
{
    IPInfo* iter;
    IPInfo* next;
    IPSocket* local;
    IPSocket* remote;
    IPSocket* connected;
    void* localSocket;

    if (socket == NULL ||
        socket->len != IP_SOCKLEN ||
        socket->family != IP_INET ||
        socket->port == 0 ||
        IP_CLASSE(socket->addr))
    {
        return IP_ERR_INVALID;
        // NOT REACHED HERE
    }

    if (socket->port == 0 ||
        (IP_ADDR_NE(socket->addr, IPAddrAny) &&
         IP_ADDR_NE(socket->addr, IPLoopbackAddr) &&
         IP_ADDR_NE(socket->addr, __IFDefault.addr) &&
         IP_ADDR_NE(socket->addr, __IFDefault.alias) &&
         !IP_CLASSD(socket->addr)))
    {
        return IP_ERR_INV_SOCKET;
        // NOT REACHED HERE
    }

    IFIterateQueue(IPInfo*, queue, iter, next, link)
    {
        if (iter == info || iter->family != info->family)
        {
            continue;
        }
        local = IPGetLocalSockAddr(iter);
        remote = IPGetRemoteSockAddr(iter);
        if (local->port == socket->port &&
            IP_ADDR_EQ(local->addr, socket->addr))
        {
            if (!reuse)
            {
                return IP_ERR_EXIST;
                // NOT REACHED HERE
            }
            connected = IPGetRemoteSockAddr(info);
            if (remote->port == connected->port && IP_ADDR_EQ(remote->addr, connected->addr))
            {
                return IP_ERR_EXIST;
                // NOT REACHED HERE
            }
        }
    }

/*
    if (info->proto == IP_PROTO_TCP &&
        !reuse &&
        TCP4LookupTimeWaitInfo())
 */

    localSocket = IPGetLocalSockAddr(info);
    memmove(localSocket, socket, sizeof(IPSocket));

    return IP_ERR_NONE;
}

/*---------------------------------------------------------------------------*
  Name:         IPConnect

  Description:  Specifies the remote socket. Local port number is also
                automatically assigened if not yet specified.

  Arguments:    Queue   Queue of IPInfo
                info    IPInfo to which remote socket is assigned
                socket  Port number must be other than zero.
                        Address cannot be 0.0.0.0.

  Returns:
 *---------------------------------------------------------------------------*/
s32 IP4Connect(IFQueue* queue, IPInfo* info, const IPSocket* socket, u16* last)
{
    IPInfo* iter;
    IPInfo* next;
    IPInterface* interface;
    u8 localAddr[IP_ALEN];
    IPSocket* local;
    IPSocket* remote;

    if (socket == NULL ||
        socket->len != IP_SOCKLEN ||
        socket->family != IP_INET ||
        socket->port == 0 ||
        IP_CLASSE(socket->addr))
    {
        return IP_ERR_INVALID;
    }

    if (IP_ADDR_EQ(socket->addr, IPAddrAny))    // Remote address is required
    {
        return IP_ERR_INV_SOCKET;
    }

    interface = IPGetRoute(socket->addr, NULL);
    if (interface == NULL)
    {
        return IP_ERR_UNREACHABLE;              // No route to the destination
    }

    if (info->proto == IP_PROTO_TCP)
    {
        // Reject invalid remote IP address (e.g., a broadcast or
        // multicast address).
        if (IP_CLASSD(socket->addr) || IPIsBroadcastAddr(interface, socket->addr))
        {
            return IP_ERR_INV_SOCKET;
        }
    }

    local = IPGetLocalSockAddr(info);
    remote = IPGetRemoteSockAddr(info);
    if (IP_ADDR_EQ(local->addr, IPAddrAny))
    {
        IP4SelectSourceAddress(interface, socket->addr, localAddr);
    }
    else
    {
        memmove(localAddr, local->addr, IP_ALEN);
    }
    if (info->proto == IP_PROTO_TCP && IP_ADDR_EQ(localAddr, IPAddrAny))
    {
        return IP_ERR_UNREACHABLE;              // No route to the destination
    }

    if (local->port == 0)
    {
Next:
        // Assign an ephemeral source port number
        local->port = IPGetAnonPort(queue, last);
        if (local->port == 0)
        {
            return IP_ERR_INS_RESOURCES;
        }

        if (info->proto == IP_PROTO_TCP &&
            TCP4LookupTimeWaitInfo(socket->addr, socket->port,
                                  localAddr, local->port))
        {
            // XXX Prevent possible forever loop somehow...
            goto Next;
        }
    }
    else
    {
        // See if connecting to the same destination from the same local socket
        IFIterateQueue(IPInfo*, queue, iter, next, link)
        {
            IPSocket* localIter;
            IPSocket* remoteIter;

            if (iter == info)
            {
                continue;
            }
            localIter = IPGetLocalSockAddr(iter);
            remoteIter = IPGetRemoteSockAddr(iter);
            if (localIter->port  == local->port &&
                remoteIter->port == remote->port &&
                IP_ADDR_EQ(localIter->addr, localAddr) &&
                IP_ADDR_EQ(remoteIter->addr, remote->addr))
            {
                return IP_ERR_EXIST;
                // NOT REACHED HERE
            }
        }

        if (info->proto == IP_PROTO_TCP)   // UDP does not reuse port number
        {
            if (TCP4LookupTimeWaitInfo(socket->addr, socket->port,
                                       localAddr, local->port))
            {
                return IP_ERR_EXIST;
                // NOT REACHED HERE
            }
        }
    }

    // Commit connect
    memmove(remote, socket, sizeof(IPSocket));
    if (IP_ADDR_EQ(local->addr, IPAddrAny))
    {
        memmove(local->addr, localAddr, IP_ALEN);
    }

    return IP_ERR_NONE;
}

void IPReceiveSocket(IPSocket* sockAddr, u8* addr, u16 port)
{
    if (sockAddr)
    {
        ASSERT(sizeof(IPSocket) <= sockAddr->len);
        sockAddr->len = sizeof(IPSocket);
        sockAddr->family = IP_INET;
        memmove(sockAddr->addr, addr, IP_ALEN);
        sockAddr->port = port;
    }
}

// Compute internet header checksum
u16 IPCheckSum(IPHeader* ip)
{
    int  len;
    u32  sum = 0;
    u16* p;

    len = IP_HLEN(ip);
    ASSERT(len % 2 == 0);
    p = (u16*) ip;
    while (0 < len)
    {
        sum += *p++;
        len -= 2;
    }
    sum = (sum & 0xffff) + (sum >> 16);
    sum = (sum & 0xffff) + (sum >> 16);
    return (u16) (sum ^ 0xffff);
}

// Compute ICMP/UDP/TCP checksum
u16 IP4CheckSum(u8 proto, IFVec* vec, int nVec)
{
    IPHeader* ip;
    s32       hlen;
    u16*      p;
    s32       len;
    u32       sum = 0;
    u32       odd;

    ASSERT(0 < nVec);
    ASSERT(IP_MIN_HLEN <= vec->len);

    // Add pseudo header
    ip = (IPHeader*) vec->data;
    ASSERT(ip->proto == proto);
    hlen = IP_HLEN(ip);
    switch (ip->proto)
    {
      case IP_PROTO_TCP:
      case IP_PROTO_UDP:
        sum += *(u16*) &ip->src[0];
        sum += *(u16*) &ip->src[2];
        sum += *(u16*) &ip->dst[0];
        sum += *(u16*) &ip->dst[2];
        sum += proto;
        sum += ip->len - hlen;
        break;
    }

    // Add payload
    p = (u16*) ((u8*) ip + hlen);
    len = vec->len - hlen;
    for (;;)
    {
        while (1 < len)
        {
            sum += *p++;
            len -= 2;
        }
        if (len == 1)
        {
            odd = ((u32) (*(u8*) p)) << 8;
        }
        else
        {
            odd = 0;
        }

        do {
            if (--nVec <= 0)
            {
                sum += odd;
                goto Done;
            }
            ++vec;
        } while (vec->len == 0);

        p = (u16*) vec->data;
        if (len == 1)
        {
            odd |= *(u8*) p;
            sum += odd;
#ifdef IOP_OS
            (u8*) p++;
#else
            (u8*) p += 1;
#endif // IOP_OS
            len = vec->len - 1;
        }
        else
        {
            len = vec->len;
        }
    }

Done:
    sum = (sum & 0xffff) + (sum >> 16);
    sum = (sum & 0xffff) + (sum >> 16);
    return (u16) (sum ^ 0xffff);
}

void IPIn(IPInterface* interface, IPHeader* ip, s32 len, u32 flag)
{
    BOOL bcast = IPIsBroadcastAddr(interface, ip->dst);

    ++interface->ipStat.inReceives;

    if (len < IP_HLEN(ip) || len < ip->len || ip->len < IP_HLEN(ip))
    {
        ++interface->ipStat.inHdrErrors;
        return;
    }

    // Silently discard link-layer-only broadcast datagram [1122 SHOULD]
    if ((flag & IF_FLAG_BROADCAST) && !bcast)
    {
        ++interface->ipStat.inHdrErrors;
        return;
    }
    if ((flag & IF_FLAG_MULTICAST) && !IP_CLASSD(ip->dst))
    {
        ++interface->ipStat.inHdrErrors;
        return;
    }

    // Check IP version, etc.
    if (IP_VERSION(ip) != IP_VER || ip->len < IP_HLEN(ip))
    {
        ++interface->ipStat.inHdrErrors;
        return;
    }

    // Verify checksum
    if (IPCheckSum(ip) != 0)
    {
        ++interface->ipStat.inHdrErrors;
        return;
    }

    // Check source address
#ifdef IOP_OS
    if (IP_CLASSD(ip->src) ||
        (IP_ADDR_NE(ip->src, IPAddrAny) && IPIsBroadcastAddr(interface, ip->src)))
#else
    if (IP_CLASSD(ip->src) ||
        IP_ADDR_NE(ip->src, IPAddrAny) && IPIsBroadcastAddr(interface, ip->src))
#endif // IOP_OS
    {
        ++interface->ipStat.inHdrErrors;
        return;
    }

    // Check class E address
    if (IP_CLASSE(ip->dst) || IP_CLASSE(ip->src))
    {
        ++interface->ipStat.inHdrErrors;
        return;
    }

    // Check incomplete source route option
    if (IPProcessSourceRoute(ip) < 0)
    {
        ++interface->ipStat.inHdrErrors;
        return;
    }

    // [RFC2131]
    // If non-local, discard it unless alias is 0.0.0.0.
    // The TCP/IP software SHOULD accept and
    // forward to the IP layer any IP packets delivered to the client's
    // hardware address before the IP address is configured.
    // If addr is 0.0.0.0, accept every packet. Otherwise,
    // reject all packets not directed to this host except
    // broadcast, multicast or loopback.
    if (IP_ADDR_NE(interface->addr, IPAddrAny) &&
        !IP_CLASSD(ip->dst) && !bcast && ip->dst[0] != 127 &&
        IP_ADDR_NE(ip->dst, interface->addr)   &&
        IP_ADDR_NE(ip->dst, interface->alias))
    {
        ++interface->ipStat.inAddrErrors;
        return;
    }

#ifdef VERBOSE
    OSReport("\nIPIn(): from %d.%d.%d.%d to %d.%d.%d.%d (%d)\n",
             ip->src[0], ip->src[1], ip->src[2], ip->src[3],
             ip->dst[0], ip->dst[1], ip->dst[2], ip->dst[3],
             ip->id);
    // IFDump((u8*) rbuf + ETH_HLEN, 64);
#endif

    // [MUST] Reassemble incoming datagram
    if ((ip->frag & IP_MF) || IP_FRAG(ip) != 0)
    {
        ++interface->ipStat.reasmReqds;
        ip = IPReassemble(interface, ip, flag);
        if (ip == NULL)
        {
            return;
        }
        ++interface->ipStat.reasmOKs;
    }

    // Deliver the datagram to the destination
    switch (ip->proto)
    {
      case IP_PROTO_ICMP:
        ++interface->ipStat.inDelivers;
        ICMPIn(interface, ip, flag);
        break;
      case IP_PROTO_IGMP:
        ++interface->ipStat.inDelivers;
        IGMPIn(interface, ip, flag);
        break;
      case IP_PROTO_UDP:
#ifndef IOP_OS
#ifdef VERBOSE
        OSReport("UDP: %d.%d.%d.%d (%d) -> %d.%d.%d.%d (%d)\n",
                 ip->src[0], ip->src[1], ip->src[2], ip->src[3], udp->src,
                 ip->dst[0], ip->dst[1], ip->dst[2], ip->dst[3], udp->dst);
#endif
#endif // IOP_OS
        ++interface->ipStat.inDelivers;
        UDP4In(interface, ip, (UDPHeader*) ((u8*) ip + IP_HLEN(ip)), flag);
        break;
      case IP_PROTO_TCP:
        if (flag & (IF_FLAG_BROADCAST | IF_FLAG_MULTICAST))
        {
            // Silently discard seg to bcast/mcast addr
            ++interface->ipStat.inHdrErrors;
            break;
        }
        ++interface->ipStat.inDelivers;
        TCP4In(interface, ip, (TCPHeader*) ((u8*) ip + IP_HLEN(ip)), flag);
        break;
      default:
        ++interface->ipStat.inUnknownProtos;
        break;
    }

    // XXX Release reassembly buffer (a hack)
    ip->verlen = 0;
}

/*---------------------------------------------------------------------------*
  Name:         IPOut

  Description:  Transmits IP datagram

  Arguments:    datagram    Pointer to IFDatagram to send. If the function
                            failed, datagram's callback is not called.

  Returns:      IP_ERR_NONE         Succeeded.
                IP_ERR_UNREACHABLE  No route to the destination.
                IP_ERR_DATASIZE     datagram is too large to be sent.
                IP_ERR_NETDOWN      datagram src address is wrong. Perhaps
                                    due to network configuration change.
 *---------------------------------------------------------------------------*/
s32 IPOut(IFDatagram* datagram)
{
    IPHeader*    ip;
    IPInterface* interface;
    TCPHeader*   tcp;
    UDPHeader*   udp;
    IGMP*        igmp;

    ASSERT(0 < datagram->nVec && datagram->nVec <= IF_MAX_VEC);
    ip = (IPHeader*) datagram->vec[0].data;
    ASSERT(IP_HLEN(ip) <= datagram->vec[0].len);
    ip->id   = Id++;
    // ip->frag = 0;   // no fragment
    // ip->verlen = IP_VERHLEN;
    // ip->tos = 0; // normal
    // ip->len = datalen + IP_HLEN;
    // ip->ttl = IP_TTL;
    // ip->proto set by upper layer
    // ip->dst[IP_ALEN] =
    // ip->src[IP_ALEN] =

    if (IP_CLASSD(ip->dst))
    {
        interface = &__IFDefault;
        memmove(datagram->dst, ip->dst, IP_ALEN);
        datagram->flag |= IF_FLAG_MULTICAST;
    }
    else
    {
        interface = IPGetRoute(ip->dst, datagram->dst);
        if (interface == NULL)
        {
            ++__IFDefault.ipStat.outRequests;
            ++__IFDefault.ipStat.outNoRoutes;
            return IP_ERR_UNREACHABLE;
        }

        if (IPIsBroadcastAddr(interface, ip->dst))
        {
            datagram->flag |= IF_FLAG_BROADCAST | IF_FLAG_LOOPBACK;
        }
        if (IPIsLoopbackAddr(interface, ip->dst) ||
            IP_ADDR_EQ(ip->dst, interface->addr) ||
            IP_ADDR_EQ(ip->dst, interface->alias))
        {
            datagram->flag |= IF_FLAG_LOOPBACK;
        }
        else
        {
            datagram->flag |= IF_FLAG_UNICAST;
        }
    }

    ++interface->ipStat.outRequests;

    // Check interface MTU if IP_DF flag is set.
    if (interface->mtu < ip->len && (ip->frag & IP_DF))
    {
        ++interface->ipStat.fragFails;
        return IP_ERR_DATASIZE;
    }

    if (!IPIsLoopbackAddr(interface, ip->src) &&
        IP_ADDR_NE(interface->addr, ip->src) &&
        IP_ADDR_NE(interface->alias, ip->src))
    {
        ++interface->ipStat.outNoRoutes;
        return IP_ERR_NETDOWN;
    }

    ip->sum = 0;
    ip->sum = IPCheckSum(ip);

    switch (ip->proto)
    {
      case IP_PROTO_IGMP:
        igmp = (IGMP*) ((u8*) ip + IP_HLEN(ip));
        igmp->sum = 0;
        igmp->sum = IP4CheckSum(IP_PROTO_IGMP, datagram->vec, datagram->nVec);
        break;
      case IP_PROTO_UDP:
        udp = (UDPHeader*) ((u8*) ip + IP_HLEN(ip));
        udp->sum = 0;
        udp->sum = IP4CheckSum(IP_PROTO_UDP, datagram->vec, datagram->nVec);
        if (udp->sum == 0)
        {
            udp->sum = 65535;   // RFC1122 4.1.3.4
        }
        break;
      case IP_PROTO_TCP:
        tcp = (TCPHeader*) ((u8*) ip + IP_HLEN(ip));
        tcp->sum = 0;
        tcp->sum = IP4CheckSum(IP_PROTO_TCP, datagram->vec, datagram->nVec);
        ASSERT((tcp->flag & (TCP_FLAG_SYN | TCP_FLAG_FIN)) != (TCP_FLAG_SYN | TCP_FLAG_FIN));
        break;
    }

    datagram->type = ETH_IP;
    interface->out(interface, datagram);

    return IP_ERR_NONE;
}

// Cancel datagram:
//   If info->datagram is in IP/ARP pending queue, it must be
//   removed from the queue before aborting the operation.
void IPCancel(IFDatagram* datagram)
{
    IPInterface* interface;

    interface = datagram->interface;
    if (interface)
    {
        interface->cancel(interface, datagram);
        ASSERT(datagram->interface == NULL);
    }
}

// IP4SelectSourceAddress() must be able to handle the case where dst is
// a non-link-local address and src is a link-local address and the
// interface has been assigned only a link-local address. In such a case,
// this stack uses "ARP for everything" routing.
void IP4SelectSourceAddress(IPInterface* interface, const u8* dst, u8* src)
{
    if (interface == NULL)
    {
        interface = &__IFDefault;
    }

    if (dst[0] == 127) // loopback
    {
        memmove(src, IPLoopbackAddr, IP_ALEN);
    }
    else if (IP_ADDR_NE(interface->alias, IPAddrAny) &&
             memcmp(dst, interface->alias, 2) == 0)
    {
        memmove(src, interface->alias, IP_ALEN);
    }
    else if (IP_ADDR_NE(interface->addr, IPAddrAny))
    {
        memmove(src, interface->addr, IP_ALEN);
    }
    else
    {
        memmove(src, interface->alias, IP_ALEN);
    }
}
