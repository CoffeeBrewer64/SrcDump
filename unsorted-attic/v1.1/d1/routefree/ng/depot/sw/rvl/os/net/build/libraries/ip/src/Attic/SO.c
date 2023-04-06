d1 1058
a1058 1055
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS SIP API -- Simple GameCube SO emulation for Win32
  File:     SO.c

  Copyright 2003, 2004 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip6/src/SO.c $
    
    1     04/11/02 11:10 Ueno_kyu
    Added support for IPv6 Core Protocol.
    
    1     6/09/04 15:58 Shiki
    IPv6 pilot implementation

    4     2/19/04 13:22 Shiki
    Fixed typo in SOAccept(), etc.

    3     1/30/04 9:35 Shiki
    Implemented the GameCube socket interface over winsock2.

    2     1/26/04 11:55 Shiki
    Updated IPAtoN().

    1     1/30/03 18:46 Shiki
    Initial check-in.
 *---------------------------------------------------------------------------*/

#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <dolphin/socket.h>
#include <dolphin/upnp.h>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

const u8 IPAddrAny[IP_ALEN]      = {   0,   0,   0,   0 };
const u8 IPLoopbackAddr[IP_ALEN] = { 127,   0,   0,   1 };
const u8 IPLimited[IP_ALEN]      = { 255, 255, 255, 255 };

const SOIn6Addr SOIn6AddrAny = SO_IN6ADDR_ANY_INIT;
const SOIn6Addr SOIn6AddrLoopback = SO_IN6ADDR_LOOPBACK_INIT;
const SOIn6Addr SOIn6AddrLinkLocalAllNodes = SO_IN6ADDR_LINKLOCAL_ALL_NODES_INIT;
const SOIn6Addr SOIn6AddrLinkLocalAllRouters = SO_IN6ADDR_LINKLOCAL_ALL_ROUTERS_INIT;

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
    static char ascii[16];

    sprintf(ascii, "%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
    return ascii;
}

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

char* IP6AtoN(const char* dotted, SOIn6Addr* addr)
{
    int   compressed = -1;
    int   c;
    u32   part[8];
    int   n;
    u32   val;
    int   i;
    int   j;
    const char* v4 = NULL;
    int   max = 8;

    n = 0;
    c = *dotted;
    for (;;)
    {
        if (c == ':')
        {
            if (max <= n)
            {
                return NULL;
            }
            c = *++dotted;
            if (c == ':')
            {
                if (0 <= compressed)
                {
                    return NULL;
                }
                compressed = n;
                c = *++dotted;
            }
            else if (n == 0)
            {
                return NULL;
            }
        }
        if (c == '.')
        {
            --n;
            if (v4 &&
                ((0 <= compressed && n < 6) ||
                 (compressed < 0 && n == 6)))
            {
                max = 6;
                break;
            }
            ++n;
        }
        if (!(isxdigit)(c))
        {
            if (c <= 127 && (0 <= compressed || n == max))
            {
                break;
            }
            return NULL;
        }
        v4 = dotted;
        for (val = 0 ;; c = *++dotted)
        {
            if ((isdigit)(c))
            {
                val *= 16;
                val += c - '0';
            }
            else if ((isxdigit)(c))
            {
                val *= 16;
                val += 10 + c - ((islower)(c) ? 'a' : 'A');
            }
            else
            {
                break;
            }
        }
        part[n++] = val;
        if (127 < c)   // !isascii()
        {
            return NULL;
        }
        if (0xffff < val)
        {
            return NULL;
        }
    }

    if (compressed < 0)
    {
        compressed = 0;
    }
    j = 0;
    for (i = 0; i < compressed; ++i)
    {
        addr->addr[j++] = (u8) (part[i] >> 8);
        addr->addr[j++] = (u8) part[i];
    }
    for (i = 0; i < max - n; ++i)
    {
        addr->addr[j++] = 0;
        addr->addr[j++] = 0;
    }
    for (i = compressed; i < n; ++i)
    {
        addr->addr[j++] = (u8) (part[i] >> 8);
        addr->addr[j++] = (u8) part[i];
    }
    ASSERT(max == 6 || j == 16);
    if (max == 6)
    {
        return IPAtoN(v4, &addr->addr[12]);
    }
    return (char*) dotted;
}

// Convert binary address to dotted-decimal notation
char* IP6NtoA(const SOIn6Addr* addr, char* ascii)
{
    u16* part;
    int  len = 0;
    u16* zero = NULL;
    BOOL compressed = FALSE;

    for (part = (u16*) addr->addr;
         part < (u16*) &addr->addr[16];
         ++part)
    {
        if (*part != 0 || compressed)
        {
            if (zero && !compressed)
            {
                if (zero == (u16*) addr->addr)
                {
                    if (part - zero == 5 && *part == 0xffff)
                    {
                        // V4MAPPED
                        sprintf(ascii, "::FFFF:%d.%d.%d.%d", addr->addr[12],
                                                             addr->addr[13],
                                                             addr->addr[14],
                                                             addr->addr[15]);
                        return ascii;
                    }
                    else if (part - zero == 6 &&
                             !(memcmp(&addr->addr[12], &SOIn6AddrAny.addr[12], 4) == 0 ||
                               memcmp(&addr->addr[12], &SOIn6AddrLoopback.addr[12], 4) == 0))
                    {
                        // V4COMPAT
                        sprintf(ascii, "::%d.%d.%d.%d", addr->addr[12],
                                                        addr->addr[13],
                                                        addr->addr[14],
                                                        addr->addr[15]);
                        return ascii;
                    }
                }
                if (part - zero < 2)
                {
                    if (0 < len)
                    {
                        len += sprintf(ascii + len, ":");
                    }
                    len += sprintf(ascii + len, "0");
                    zero = NULL;
                }
                else
                {
                    len += sprintf(ascii + len, ":");
                    compressed = TRUE;
                }
            }
            if (0 < len)
            {
                len += sprintf(ascii + len, ":");
            }
            len += sprintf(ascii + len, "%X", *part);
        }
        else if (zero == NULL)
        {
            zero = part;
        }
    }
    if (zero && !compressed)
    {
        if (part - zero < 2)
        {
            len += sprintf(ascii + len, ":0");
        }
        else
        {
            len += sprintf(ascii + len, "::");
        }
    }
    ASSERT(len < SO_INET6_ADDRSTRLEN);
    return ascii;
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

  Returns:      Pointer to the character string in the dotted-decimal
                notation in a statically allocated buffer.
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

static void* ConvertToWinsock(const void* sockAddr, void* winSockAddr)
{
    const SOSockAddrIn* from = sockAddr;
    struct sockaddr_in* to = winSockAddr;
    const SOSockAddrIn6* from6 = sockAddr;
    struct sockaddr_in6* to6 = winSockAddr;

    if (sockAddr == NULL)
    {
        return NULL;
    }

    switch (from->family)
    {
      case SO_PF_INET:
        ASSERT(sizeof(SOSockAddrIn) <= from->len);
        to->sin_family = from->family;
        to->sin_port = from->port;
        to->sin_addr.s_addr = from->addr.addr;
        memset(&to->sin_zero, 0, sizeof(to->sin_zero));
        return to;
        break;

#ifdef IP_INET6
      case SO_PF_INET6:
        ASSERT(sizeof(SOSockAddrIn6) <= from6->len);
        to6->sin6_family = from6->family;
        to6->sin6_port = from6->port;
        to6->sin6_flowinfo = from6->flowInfo;
        memmove(to6->sin6_addr.s6_addr, from6->addr.addr, 16);
        to6->sin6_scope_id = from6->scopeID;
        return to6;
        break;
#endif
    }
    return NULL;
}

static void* ConvertToSocket(const void* winSockAddr, void* sockAddr)
{
    short family;
    const struct sockaddr_in* from = winSockAddr;
    SOSockAddrIn* to = sockAddr;
    const struct sockaddr_in6* from6 = winSockAddr;
    SOSockAddrIn6* to6 = sockAddr;

    if (winSockAddr == NULL)
    {
        return NULL;
    }

    ASSERT(from->sin_family <= 255);
    switch (from->sin_family)
    {
      case SO_PF_INET:
        ASSERT(sizeof(SOSockAddrIn) <= to->len);
        family = from->sin_family;
        to->len = sizeof(SOSockAddrIn);
        to->family = (u8) family;
        to->addr.addr = from->sin_addr.s_addr;
        to->port = from->sin_port;
        return to;
        break;

#ifdef IP_INET6
      case SO_PF_INET6:
        ASSERT(sizeof(SOSockAddrIn6) <= to6->len);
        family = from6->sin6_family;
        to6->len = sizeof(SOSockAddrIn6);
        to6->family = (u8) family;
        to6->flowInfo = from6->sin6_flowinfo;
        memmove(to6->addr.addr, from6->sin6_addr.s6_addr, 16);
        to6->scopeID = from6->sin6_scope_id;
        return to6;
        break;
#endif
    }
    return NULL;
}

int SOSocket(int af, int type, int protocol)
{
    int rc;
    SOCKET s;

    s = socket(af, type, protocol);
    if (s != INVALID_SOCKET)
    {
        ASSERT(0 <= s && s <= INT_MAX);
        return (int) s;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOClose(int s)
{
    int rc;

    rc = closesocket(s);
    if (rc != SOCKET_ERROR)
    {
        return rc;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOShutdown(int s, int how)
{
    int rc;

    rc = shutdown(s, how);
    if (rc != SOCKET_ERROR)
    {
        return rc;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOBind(int s, const void* sockAddr)
{
    int rc;
    struct sockaddr_in6 sa;

    rc = bind(s, ConvertToWinsock(sockAddr, &sa), sizeof sa);
    if (rc != SOCKET_ERROR)
    {
        return rc;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOConnect(int s, const void* sockAddr)
{
    int rc;
    struct sockaddr_in6 sa;

    rc = connect(s, ConvertToWinsock(sockAddr, &sa), sizeof sa);
    if (rc != SOCKET_ERROR)
    {
        return rc;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOGetPeerName(int s, void* sockAddr)
{
    int rc;
    struct sockaddr_in6 sa;
    int salen;

    salen = sizeof sa;
    rc = getpeername(s, (struct sockaddr*) &sa, &salen);
    if (rc != SOCKET_ERROR)
    {
        ASSERT(salen <= sizeof sa);
        ConvertToSocket(&sa, sockAddr);
        return rc;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOGetSockName(int s, void* sockAddr)
{
    int rc;
    struct sockaddr_in6 sa;
    int salen;

    salen = sizeof sa;
    rc = getsockname(s, (struct sockaddr*) &sa, &salen);
    if (rc != SOCKET_ERROR)
    {
        ASSERT(salen <= sizeof sa);
        ConvertToSocket(&sa, sockAddr);
        return rc;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SORead(int s, void* buf, int len)
{
    return SORecvFrom(s, buf, len, 0, NULL);
}

int SORecv(int s, void* buf, int len, int flags)
{
    return SORecvFrom(s, buf, len, flags, NULL);
}

int SORecvFrom(int s, void* buf, int len, int flags, void* sockFrom)
{
    int rc;
    struct sockaddr_in6 sa;
    int fromlen;

    fromlen = sizeof sa;
    rc = recvfrom(s, buf, len, flags, (struct sockaddr*) &sa, &fromlen);
    if (rc != SOCKET_ERROR)
    {
        ASSERT(fromlen <= sizeof sa);
        ConvertToSocket(&sa, sockFrom);
        return rc;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOWrite(int s, const void* buf, int len)
{
    return SOSendTo(s, buf, len, 0, NULL);
}

int SOSend(int s, const void* buf, int len, int flags)
{
    return SOSendTo(s, buf, len, flags, NULL);
}

int SOSendTo(int s, const void* buf, int len, int flags, const void* sockTo)
{
    int rc;
    struct sockaddr_in6 sa;

    rc = sendto(s, buf, len, flags, ConvertToWinsock(sockTo, &sa), sizeof sa);  // XXX Check NULL
    if (rc != SOCKET_ERROR)
    {
        return rc;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOAccept(int s, void* sockAddr)
{
    int rc;
    struct sockaddr_in6 sa;
    int salen;

    salen = sizeof sa;
    rc = accept(s, (struct sockaddr*) &sa, &salen);
    if (rc != SOCKET_ERROR)
    {
        ASSERT(salen <= sizeof sa);
        ConvertToSocket(&sa, sockAddr);
        return rc;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOListen(int s, int backlog)
{
    int rc;

    rc = listen(s, backlog);
    if (rc != SOCKET_ERROR)
    {
        return rc;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOSockAtMark(int s)
{
    int rc;
    u_long flag;

    rc = ioctlsocket(s, SIOCATMARK, &flag);
    if (rc != SOCKET_ERROR)
    {
        return (flag != 0) ? 1 : 0;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOGetSockOpt(int s, int level, int optname, void* optval, int* optlen)
{
    int rc;

    // XXX no socket/win32 conversion
    rc = getsockopt(s, level, optname, optval, optlen);
    if (rc != SOCKET_ERROR)
    {
        return rc;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOSetSockOpt(int s, int level, int optname, const void* optval, int optlen)
{
    int rc;

    // XXX no socket/win32 conversion
    rc = setsockopt(s, level, optname, optval, optlen);
    if (rc != SOCKET_ERROR)
    {
        return rc;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOFcntl(int s, int cmd, ...)
{
    // XXX not supported
    return SO_EINVAL;
}

int SOPoll(SOPollFD fds[], unsigned nfds, OSTime timeout)
{
    int rc;
    unsigned i;
    int n;
    fd_set read;
    fd_set write;
    fd_set except;
    struct timeval tv;

    FD_ZERO(&read);
    FD_ZERO(&write);
    FD_ZERO(&except);

    n = -1;
    for (i = 0; i < nfds; i++)
    {
        if (fds[i].fd < 0)
        {
           continue;
        }
        if (fds[i].events & SO_POLLIN)
        {
           FD_SET(fds[i].fd, &read);
        }
        if (fds[i].events & SO_POLLOUT)
        {
           FD_SET(fds[i].fd, &write);
        }
        if (fds[i].events & SO_POLLERR)
        {
           FD_SET(fds[i].fd, &except);
        }
        if (n < fds[i].fd)
        {
           n = fds[i].fd;
        }
    }

    if (n == -1)
    {
        return 0;
    }

    if (timeout < 0)
    {
        rc = select(n + 1, &read, &write, &except, NULL);
    }
    else
    {
        tv.tv_sec  = (long) OSTicksToSeconds(timeout);
        tv.tv_usec = (long) OSTicksToMicroseconds(timeout % OSSecondsToTicks(1));
        rc = select(n + 1, &read, &write, &except, &tv);
    }

    if (rc != SOCKET_ERROR)
    {
        ASSERT(0 <= rc);
        for (i = 0; i < nfds; i++)
        {
            fds[i].revents = 0;
            if (FD_ISSET(fds[i].fd, &read))
            {
                fds[i].revents |= SO_POLLIN;
            }
            if (FD_ISSET(fds[i].fd, &write))
            {
                fds[i].revents |= SO_POLLOUT;
            }
            if (FD_ISSET(fds[i].fd, &except))
            {
                fds[i].revents |= SO_POLLERR;
            }
        }
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

SOHostEnt* SOGetHostByAddr(const void* addr, int len, int type)
{
    return (SOHostEnt*) gethostbyaddr(addr, len, type);
}

SOHostEnt* SOGetHostByName(const char* name)
{
    return (SOHostEnt*) gethostbyname(name);
}

void SOFreeAddrInfo(SOAddrInfo* ai)
{
    struct addrinfo* p;

    for (p = (struct addrinfo*) ai; p; p = p->ai_next)
    {
        ConvertToWinsock(p->ai_addr, p->ai_addr);
    }
    freeaddrinfo((struct addrinfo*) ai);
}

int SOGetAddrInfo(const char* nodeName, const char* servName,
                  const SOAddrInfo* hints, SOAddrInfo** res)
{
    int rc;
    struct addrinfo* ai;

    rc = getaddrinfo(nodeName, servName,
                     (const struct addrinfo*) hints, (struct addrinfo**) &ai);
    if (rc == 0)
    {
        while (ai)
        {
            ConvertToSocket(ai->ai_addr, ai->ai_addr);
            ai = ai->ai_next;
        }
        *res = (SOAddrInfo*) ai;
        return 0;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

int SOGetNameInfo(const void* sockAddr,
                  char* node, unsigned nodeLen,
                  char* service, unsigned serviceLen,
                  int flags)
{
    int rc;
    struct sockaddr_in6 sa;

    rc = getnameinfo(ConvertToWinsock(sockAddr, &sa), sizeof(sa),
                     node, nodeLen, service, serviceLen, flags);
    if (rc == 0)
    {
        return 0;
    }

    rc = WSAGetLastError();
    ASSERT(0 < rc);
    return -rc;
}

long SOGetHostID(void)
{
    int rc;
    char host[SO_MAXDNAME];
    struct hostent* ent;
    struct in_addr addr;
    struct in_addr temp;

    addr.s_addr = 0;
    rc = gethostname(host, SO_MAXDNAME);
    if (0 <= rc)
    {
        ent = gethostbyname(host);
        if (ent)
        {
            char** ptr;

            for (ptr = ent->h_addr_list; *ptr != NULL; ++ptr)
            {
                temp = *(struct in_addr*) *ptr;
                if (addr.s_addr == 0)
                {
                    addr = temp;
                }
                else if (UPnPIsPrivateAddr(*(SOInAddr*) &addr))
                {
                    addr = temp;
                }
            }
        }
    }
    return addr.s_addr;
}
