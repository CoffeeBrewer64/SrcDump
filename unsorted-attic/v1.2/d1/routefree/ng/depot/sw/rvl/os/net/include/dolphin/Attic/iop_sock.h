/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

/*---------------------------------------------------------------------------*
 * 
 * definitions and structures used between socket lib and network stack
 * 
 *---------------------------------------------------------------------------*/

#ifndef __IOP_SOCK_H__
#define __IOP_SOCK_H__

#include "dolphin/os.h"
#include "dolphin/ip.h"

#define NET_RM_SOCK             "/dev/net/ip/top"

#define NET_SO_ACCEPT           0x01
#define NET_SO_BIND             0x02
#define NET_SO_CLOSE            0x03
#define NET_SO_CONNECT          0x04
#define NET_SO_FCNTL            0x05
#define NET_SO_GETPEERNAME      0x06
#define NET_SO_GETSOCKNAME      0x07
#define NET_SO_GETSOCKOPT       0x08
#define NET_SO_SETSOCKOPT       0x09
#define NET_SO_LISTEN           0x0A
#define NET_SO_POLL             0x0B
#define NET_SO_RECVFROM         0x0C
#define NET_SO_SENDTO           0x0D
#define NET_SO_SHUTDOWN         0x0E
#define NET_SO_SOCKET           0x0F
#define NET_SO_GETHOSTBYNAME    0x10
#define NET_SO_GETHOSTBYADDR    0x11

// 35 aliases, 35 addr, 8192 buffer
typedef struct SOResolver
{
    DNSInfo     info;
    SOHostEnt   ent;
    char        name[SO_MAXDNAME];
#ifndef IP_INET6
    u8          addrList[35 * sizeof(SOInAddr)];
#else
    u8          addrList[35 * sizeof(SOIn6Addr)];
#endif  // IP_INET6
    char        buf[8192 - 35 * sizeof(SOInAddr)];
    u8*         ptrList[72];
    char        suffix[SO_MAXDNAME];
} SOResolver;

#endif // __IOP_SOCK_H__
