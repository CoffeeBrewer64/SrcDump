d1 2018
a2018 1963
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API -- DHCP [RFC 2131, RFC 2132]
  File:     IPDhcp.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip6/src/IPDhcp.c $
    
    35    06/02/03 16:56 Ueno_kyu
    Modified DHCPProcessOptions() to check yiaddr in case of DHCP OFFER and
    ACK.
    
    34    1/18/06 16:44 Shiki
    Fixed InitDHCPInfo().

    33    1/06/06 17:30 Shiki
    Added support for DHCP_OPT_DEFAULT_TTL and DHCP_OPT_STATIC_ROUTE.

    32    1/05/06 16:16 Shiki
    Modified DHCPProcessOptions() to check validity of yiaddr.
    Fixed xid value of the DHCPREQUEST for the DHCPOFFER.
    Revised timer management code to be more accurate.
    Fixed RecvCallback() to check validity of yiaddr for ACK.

    31    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    33    6/14/04 11:40 Shiki
    IPv6 pilot implementation

    32    6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    30    10/24/03 13:39 Shiki
    Added support for client DHCP host name.

    29    7/04/03 16:46 Shiki
    Declared DHCPProcessOptions() as extern for the use of could internet
    emulator.

    28    5/12/03 20:50 Shiki
    Modified so that the size of DHCP message is at least 300 bytes for
    interoperability with BOOTP derived systems.
    Modified to ignore invalid MTU size reported by the DHCP server.

    27    5/06/03 14:03 Shiki
    Modified to desynchronize the use of DHCP at startup.

    26    5/01/03 18:51 Shiki
    Fixed FLAG_MORIBUND flag management code.

    25    5/01/03 15:59 Shiki
    Modified to adjust ARP probe delay before setting timers.

    24    5/01/03 13:36 Shiki
    Fixed DHCP decline procedure.

    23    5/01/03 10:42 Shiki
    Modified to set interface MTU from DHCP MTU option by default.

    22    4/30/03 18:03 Shiki
    Fixed DHCP request message timer management in the RENEWING and
    REBINDING states.

    21    4/28/03 21:26 Shiki
    Fixed xid management code.
    Fixed ClaimHandler() to use the result code parameter.
    Fixed DHCPRelease() and DHCPDecline() to timeout to avoid waiting for
    the ARP timeout.

    20    4/25/03 9:06 Shiki
    Fixed to check chaddr field in a rececived DHCP message.

    19    4/24/03 21:13 Shiki
    Revised UpdateDHCPInfo() to update more fields from DHCP ACK message
    for NTT ME BA 5000 PRO.

    18    4/24/03 19:54 Shiki
    Revised to use request list options for Windows 2000 server...

    17    4/24/03 13:58 Shiki
    Fixed to accept infinity (0xffffffff) lease time.

    16    4/23/03 11:51 Shiki
    Revised not to use DHCP_OPT_REQUEST_LIST as the returned options are
    DHCP server-dependent. Also revised to use default T1 and T2 if
    DHCP_OPT_RENEWAL_TIME  and /or DHCP_OPT_REBINDING_TIME options are not
    presented.

    15    4/21/03 19:56 Shiki
    Modified to send DHCP_OPT_CLIENT_IDENTIFIER and DHCP_OPT_REQUEST_LIST
    to support NEC Aterm WBR75H.

    14    4/18/03 22:04 Shiki
    Implemented DHCPStartupEx().

    13    3/07/03 10:44 Shiki
    Fixed DHCPStartup() and DHCPCleanup() to use FLAG_INIT flag properly.

    12    10/07/02 10:41 Shiki
    Added support for IPGetConfigError().

    11    8/05/02 9:48 Shiki
    Fixed a warning.

    10    8/05/02 9:24 Shiki
    Added support for DHCP_OPT_MTU.

    9     4/26/02 15:50 Shiki
    Added support for DHCP callback.

    8     4/26/02 13:41 Shiki
    Fixed DHCPDiscover() and DHCPRequest() to start alarm and receive
    operation immediately after the send operation.
    Implemented DHCPAuto() function.

    7     4/25/02 21:05 Shiki
    Modified TIMER_DEBUG code.

    6     4/24/02 11:22 Shiki
    Implemented backoff randomization.
    Implemented DHCPReboot().
    Fixed to use the limited broadcast address rather then network
    broadcast address.
    Fixed to wait for the completion of DHCP decline and release before
    closing the UDPInfo.

    5     4/08/02 13:47 Shiki
    Revised using new IPSocket{} type.

    4     3/18/02 14:23 Shiki
    Fixed the state machine bug that stalled when UDPSendAsync() failed.

    3     3/13/02 9:14 Shiki
    Clean up with IP_ALEN and ETH_ALEN.

    2     3/12/02 15:18 Shiki
    Fixed T1Handler() and T2Handler() to check DHCPRequest() result
    correctly.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <dolphin/os.h>
#include <dolphin/ip.h>
#include <dolphin/ip/IPDhcp.h>
#include "IPPrivate.h"

#include <stddef.h>
#include <string.h>

#define MIN_WAIT        4       // [sec] -1 to +1
#define MAX_WAIT        64      // [sec]
#define MAX_RXMIT       4

#define AUTO_WAIT       OSSecondsToTicks((OSTime) (5 * 60))     // 5 [min]

// DHCPControl.flag
#define FLAG_INIT       0x01
#define FLAG_AUTO       0x02    // Automatically restart configuration after failure.
#define FLAG_MORIBUND   0x04

// Define TIMER_DEBUG to test DHCP timer operations
// #define TIMER_DEBUG

// Define NO_REQUEST_LIST not to use request list options.
// Note Windows 2000 server appears that it violate the following RFC
// 2131 term.
//   The server MUST supply as many of the requested parameters as
//   possible and MUST omit any parameters it cannot provide.
// So for better interoperability, we send request list options
// including all interesting options.
// #define NO_REQUEST_LIST

// DHCP Control Block
typedef struct DHCPControl
{
    UDPInfo      udp;

    int          state;
    u32          xid;
    u32          flag;

    IPSocket     socket;
    u8           heap[536];
    s32          len;

    int          rxmitMax;
    int          rxmitCount;
    OSAlarm      rxmitAlarm;

    OSAlarm      t1; // Time at which the client enters the RENEWING state
    OSAlarm      t2; // Time at which the client enters the REBINDING state
    OSAlarm      expire;

    OSTime       t2Time;
    OSTime       expireTime;
    OSTime       ackTime;

    DHCPInfo     info;
    DHCPInfo     tempInfo;

    DHCPCallback callback;

    char         hostName[DNS_NAME_MAX + 1];
} DHCPControl;

static void ReleaseCallback( UDPInfo* info, s32 result );
static void RecvCallback   ( UDPInfo* info, s32 result );
static void RxmitHandler   ( OSAlarm* alarm, OSContext* context );
static void T1Handler      ( OSAlarm* alarm, OSContext* context );
static void T2Handler      ( OSAlarm* alarm, OSContext* context );
static void ExHandler      ( OSAlarm* alarm, OSContext* context );
static void Start          ( DHCPControl* ctrl );
static void Claim          ( DHCPControl* ctrl );
static void Stop           ( DHCPControl* ctrl );
static BOOL Restart        ( DHCPControl* ctrl, OSTime wait );

static s32 DHCPDiscover( DHCPControl* ctrl);
static s32 DHCPDecline ( DHCPControl* ctrl);
static s32 DHCPRelease ( DHCPControl* ctrl);
static s32 DHCPRequest ( DHCPControl* ctrl);

static DHCPControl     Control;
static IPInterfaceConf Conf;
static u8              MagicCookie[IP_ALEN] = { 99, 130, 83, 99 };
static char*           TypeNames[] =
{
    "(None)",
    "DISCOVER",
    "OFFER",
    "REQUEST",
    "DECLINE",
    "ACK",
    "NAK",
    "RELEASE",
};

void DHCPDump(DHCPHeader* dhcp, s32 optlen)
{
    u8  type;
    u8* opt;
    s32 len;
    u8* sname = 0;
    u8* file  = 0;

    opt = (u8*) dhcp + DHCP_MIN_HLEN;
    if (optlen < 5 || IP_ADDR_NE(opt, MagicCookie))
    {
        return;
    }
    opt += 4;
    optlen -= 4;

    OSReport("op %d, htype %d, hlen %d, hops %d, xid %u, secs %u, flags %u\n",
             dhcp->op, dhcp->htype, dhcp->hlen, dhcp->hops, dhcp->xid, dhcp->secs, dhcp->flags);
    OSReport("ciaddr: %d.%d.%d.%d\n",
             dhcp->ciaddr[0], dhcp->ciaddr[1], dhcp->ciaddr[2], dhcp->ciaddr[3]);
    OSReport("yiaddr: %d.%d.%d.%d\n",
             dhcp->yiaddr[0], dhcp->yiaddr[1], dhcp->yiaddr[2], dhcp->yiaddr[3]);
    OSReport("siaddr: %d.%d.%d.%d\n",
             dhcp->siaddr[0], dhcp->siaddr[1], dhcp->siaddr[2], dhcp->siaddr[3]);
    OSReport("giaddr: %d.%d.%d.%d\n",
             dhcp->giaddr[0], dhcp->giaddr[1], dhcp->giaddr[2], dhcp->giaddr[3]);
    OSReport("chaddr: %02x:%02x:%02x:%02x:%02x:%02x\n",
             dhcp->chaddr[0], dhcp->chaddr[1], dhcp->chaddr[2],
             dhcp->chaddr[3], dhcp->chaddr[4], dhcp->chaddr[5]);

  Overload:
    while (0 < optlen && *opt != DHCP_OPT_END)
    {
        type = *opt++;
        --optlen;
        switch (type)
        {
          case DHCP_OPT_PAD:
            len = 1;
          default:
            if (optlen < 1)
            {
                return;
            }
            len = *opt++;
            --optlen;
            if (optlen < len)
            {
                return;
            }
            break;
        }

        switch (type)
        {
          //
          // BOOTP options
          //
          case DHCP_OPT_SUBNETMASK:
            if (len != IP_ALEN)
            {
                return;
            }
            OSReport("DHCP: SUBNETMASK: %d.%d.%d.%d\n",
                     opt[0], opt[1], opt[2], opt[3]);
            break;
          case DHCP_OPT_ROUTER:
            OSReport("DHCP: ROUTER: %d.%d.%d.%d\n",
                     opt[0], opt[1], opt[2], opt[3]);
            break;
          case DHCP_OPT_DNS:
            if (len <= 0 || len % IP_ALEN)
            {
                return;
            }
            // Select the 1st two
            OSReport("DHCP: DNS1: %d.%d.%d.%d\n",
                     opt[0], opt[1], opt[2], opt[3]);
            if (8 <= len)
            {
                OSReport("DHCP: DNS2: %d.%d.%d.%d\n",
                         opt[4], opt[5], opt[6], opt[7]);
            }
            break;
          case DHCP_OPT_HOST_NAME:
            OSReport("DHCP: HOST_NAME: %.*s\n", len, opt);
            break;
          case DHCP_OPT_DOMAIN_NAME:
            OSReport("DHCP: DOMAIN_NAME: %.*s\n", len, opt);
            break;

          case DHCP_OPT_DEFAULT_TTL:
            OSReport("DHCP: TTL: %u\n", *(u8*) opt);
            break;
          case DHCP_OPT_MTU:
            OSReport("DHCP: MTU: %d\n", *(u16*) opt);
            break;

          case DHCP_OPT_BROADCAST_ADDR:
            if (len != IP_ALEN)
            {
                return;
            }
            OSReport("DHCP: BROADCAST_ADDR: %d.%d.%d.%d\n",
                     opt[0], opt[1], opt[2], opt[3]);
            break;

          case DHCP_OPT_STATIC_ROUTE:
            if (len <= 0 || len % 8)
            {
                return;
            }
            OSReport("DHCP: STATIC_ROUTE: %d.%d.%d.%d %d.%d.%d.%d\n",
                     opt[0], opt[1], opt[2], opt[3],
                     opt[4], opt[5], opt[6], opt[6]);
            break;

          //
          // DHCP Extensions
          //
          case DHCP_OPT_LEASE_TIME:
            if (len != 4)
            {
                return;
            }
            OSReport("DHCP: LEASE_TIME: %u\n", *(u32*) opt);
            break;
          case DHCP_OPT_OVERLOAD:
            if (len != 1)
            {
                return;
            }
            switch (*opt)
            {
              case DHCP_FILE:
                file = dhcp->file;
                break;
              case DHCP_SNAME:
                sname = dhcp->sname;
                break;
              case DHCP_FILE_AND_SNAME:
                file = dhcp->file;
                sname = dhcp->sname;
                break;
            }
            break;
          case DHCP_OPT_DHCP_TYPE:
            if (len != 1)
            {
                return;
            }
            OSReport("DHCP: Type: %d (%s)\n", *opt, TypeNames[*opt]);
            break;
          case DHCP_OPT_SERVER_ID:
            if (len != IP_ALEN)
            {
                return;
            }
            OSReport("DHCP: SERVER_ID: %d.%d.%d.%d\n",
                     opt[0], opt[1], opt[2], opt[3]);
            break;
          case DHCP_OPT_RENEWAL_TIME:
            if (len != 4)
            {
                return;
            }
            OSReport("DHCP: RENEWAL_TIME: %u\n", *(u32*) opt);
            break;
          case DHCP_OPT_REBINDING_TIME:
            if (len != 4)
            {
                return;
            }
            OSReport("DHCP: REBINDING_TIME: %u\n", *(u32*) opt);
            break;
          default:
            break;
        }

        opt += len;
        optlen -= len;
    }

    if (sname)
    {
        opt = sname;
        optlen = 64;
        sname = 0;
        goto Overload;
    }

    if (file)
    {
        opt = file;
        optlen = 128;
        file = 0;
        goto Overload;
    }
}

static u32 Rotate(u32 n, u32 s)
{
    return (n << s) | (n >> (32 - s));
}

// DHCP Exponential backoff: 4, 8, 16, 32, 64, ...
static OSTime DHCPBackoff(DHCPControl* ctrl, int n)
{
    OSTime backoff;
    OSTick r;

    ASSERT(0 <= n);
    if (n <= ctrl->rxmitMax)
    {
        n = MIN_WAIT << n;
    }
    else
    {
        n = MAX_WAIT;
    }
    backoff = OSSecondsToTicks((OSTime) n);

    // Randomize -1 sec to +1 sec.
    r = OSGetTick();
    r = Rotate(r, r % 32);
    r %= OSSecondsToTicks(2);

    return (backoff + r) - OSSecondsToTicks(1);
}

static void InitDHCPInfo(DHCPInfo* info)
{
    memmove(info->ipaddr,    IPAddrAny, IP_ALEN);

    // BOOTP options
    memmove(info->netmask,   IPAddrAny, IP_ALEN);
    memmove(info->router,    IPAddrAny, IP_ALEN);
    memmove(info->dns1,      IPAddrAny, IP_ALEN);
    memmove(info->dns2,      IPAddrAny, IP_ALEN);
    memset(info->host,       0,         sizeof info->host);
    memset(info->domain,     0,         sizeof info->domain);
    info->ttl = IP_TTL;
    info->mtu = 0;
    memmove(info->broadcast, IPLimited, IP_ALEN);

#if (0 < DHCP_MAX_STATIC_ROUTE)
    memset(&info->staticRoute[0], 0, DHCP_MAX_STATIC_ROUTE * sizeof(DHCPStaticRoute));
#endif

    // DHCP Extensions
    info->lease = 0;
    memmove(info->server,    IPAddrAny, IP_ALEN);
    info->renewal = 0;
    info->rebinding = 0;
}

static void UpdateDHCPInfo(DHCPInfo* info, DHCPInfo* update)
{
    if (IP_ADDR_EQ(info->ipaddr, IPAddrAny))
    {
        memmove(info->ipaddr, update->ipaddr, IP_ALEN);
    }

    // BOOTP options
    if (IP_ADDR_NE(update->netmask, IPAddrAny))
    {
        memmove(info->netmask, update->netmask, IP_ALEN);
    }
    if (IP_ADDR_NE(update->router, IPAddrAny))
    {
        memmove(info->router, update->router, IP_ALEN);
    }
    if (IP_ADDR_NE(update->dns1, IPAddrAny))
    {
        memmove(info->dns1, update->dns1, IP_ALEN);
    }
    if (IP_ADDR_NE(update->dns2, IPAddrAny))
    {
        memmove(info->dns2, update->dns2, IP_ALEN);
    }
    if (update->host[0])
    {
        memmove(info->host, update->host, sizeof info->host);
    }
    if (update->domain[0])
    {
        memmove(info->domain, update->domain, sizeof info->domain);
    }
    if (0 < update->ttl)
    {
        info->ttl = update->ttl;
    }
    if (0 < update->mtu)
    {
        info->mtu = update->mtu;
    }
    if (IP_ADDR_NE(update->broadcast, IPLimited))
    {
        memmove(info->broadcast, update->broadcast, IP_ALEN);
    }

#if (0 < DHCP_MAX_STATIC_ROUTE)
{
    int i;

    for (i = 0; i < DHCP_MAX_STATIC_ROUTE; ++i)
    {
        if (IP_ADDR_EQ(update->staticRoute[i].dest, IPAddrAny))
        {
            break;
        }
        memmove(&info->staticRoute[i], &update->staticRoute[i], sizeof(DHCPStaticRoute));
    }
}
#endif

    // DHCP Extensions
    if (update->lease != 0)
    {
        info->lease = update->lease;
    }
    if (IP_ADDR_NE(update->server, IPAddrAny))
    {
        memmove(info->server, update->server, IP_ALEN);
    }
    if (update->renewal != 0)
    {
        info->renewal = update->renewal;
    }
    if (update->rebinding != 0)
    {
        info->rebinding = update->rebinding;
    }
}

int DHCPProcessOptions(DHCPHeader* dhcp, int mlen, DHCPInfo* info)
{
    int messageType;
    u8  type;
    u8* opt;
    s32 len;
    s32 optlen;
    u8  ttl;
    u16 mtu;
    u8* sname = 0;
    u8* file  = 0;

    // Check magic cookie
    opt = (u8*) dhcp + DHCP_MIN_HLEN;
    optlen = mlen - DHCP_MIN_HLEN;
    if (optlen < 5 || IP_ADDR_NE(opt, MagicCookie))
    {
        return -1;
    }
    opt += 4;
    optlen -= 4;

    // Set to default
    messageType = -1;
    InitDHCPInfo(info);

  Overload:
    while (0 < optlen && *opt != DHCP_OPT_END)
    {
        type = *opt++;
        --optlen;
        switch (type)
        {
          case DHCP_OPT_PAD:
            len = 1;
          default:
            if (optlen < 1)
            {
                return -1;
            }
            len = *opt++;
            --optlen;
            if (optlen < len)
            {
                return -1;
            }
            break;
        }

        switch (type)
        {
          //
          // BOOTP options
          //
          case DHCP_OPT_SUBNETMASK:
            if (len != IP_ALEN)
            {
                return -1;
            }
            memmove(info->netmask, opt, IP_ALEN);
            break;
          case DHCP_OPT_ROUTER:
            if (len <= 0 || len % IP_ALEN)
            {
                return -1;
            }
            // Select the 1st one
            memmove(info->router, opt, IP_ALEN);
            break;
          case DHCP_OPT_DNS:
            if (len <= 0 || len % IP_ALEN)
            {
                return -1;
            }
            // Select the 1st two
            memmove(info->dns1, opt, IP_ALEN);
            if (8 <= len)
            {
                memmove(info->dns2, opt + IP_ALEN, IP_ALEN);
            }
            break;
          case DHCP_OPT_HOST_NAME:
            memmove(info->host, opt, (size_t) len);
            info->host[len] = '\0';
            break;
          case DHCP_OPT_DOMAIN_NAME:
            memmove(info->domain, opt, (size_t) len);
            info->domain[len] = '\0';
            break;

          case DHCP_OPT_DEFAULT_TTL:
            ttl = *(u8*) opt;
            if (0 < ttl)
            {
                info->ttl = ttl;
            }
            break;
          case DHCP_OPT_MTU:
            mtu = *(u16*) opt;
            if (68 <= mtu)
            {
                // Note COREGA SW-4P HG returns zero for MTU. The
                // library just ignores those illegal MTU values.
                mtu = (u16) MIN(mtu, 65535);
                info->mtu = mtu;
            }
            break;

          case DHCP_OPT_BROADCAST_ADDR:
            if (len != IP_ALEN)
            {
                return -1;
            }
            memmove(info->broadcast, opt, IP_ALEN);
            break;

#if (0 < DHCP_MAX_STATIC_ROUTE)
          case DHCP_OPT_STATIC_ROUTE:
            if (len <= 0 || len % 8)
            {
                return -1;
            }
            memmove(&info->staticRoute[0], opt,
                    MIN(DHCP_MAX_STATIC_ROUTE * sizeof(DHCPStaticRoute), len));
            break;
#endif

          //
          // DHCP Extensions
          //
          case DHCP_OPT_LEASE_TIME:
            if (len != 4)
            {
                return -1;
            }
            info->lease = *(u32*) opt;
            break;
          case DHCP_OPT_OVERLOAD:
            if (len != 1)
            {
                return -1;
            }
            switch (*opt)
            {
              case DHCP_FILE:
                file = dhcp->file;
                break;
              case DHCP_SNAME:
                sname = dhcp->sname;
                break;
              case DHCP_FILE_AND_SNAME:
                file = dhcp->file;
                sname = dhcp->sname;
                break;
            }
            break;
          case DHCP_OPT_DHCP_TYPE:
            if (len != 1)
            {
                return -1;
            }
            messageType = *opt;
            break;
          case DHCP_OPT_SERVER_ID:
            if (len != IP_ALEN)
            {
                return -1;
            }
            memmove(info->server, opt, IP_ALEN);
            break;
          case DHCP_OPT_RENEWAL_TIME:
            if (len != 4)
            {
                return -1;
            }
            info->renewal = *(u32*) opt;
            break;
          case DHCP_OPT_REBINDING_TIME:
            if (len != 4)
            {
                return -1;
            }
            info->rebinding = *(u32*) opt;
            break;
          default:
            break;
        }

        opt += len;
        optlen -= len;
    }

    if (sname)
    {
        opt = sname;
        optlen = 64;
        sname = 0;
        goto Overload;
    }

    if (file)
    {
        opt = file;
        optlen = 128;
        file = 0;
        goto Overload;
    }

	switch (messageType)
	{
	  case DHCP_OFFER:
	  case DHCP_ACK:
	    // Check dhcp->yiaddr
	    if (IP_CLASSD(dhcp->yiaddr) ||
	        IP_CLASSE(dhcp->yiaddr) ||
	        IP_ADDR_EQ(dhcp->yiaddr, IPAddrAny) ||
	        IP_ADDR_EQ(dhcp->yiaddr, IPLoopbackAddr) ||
	        IP_ADDR_EQ(dhcp->yiaddr, IPLimited))
	    {
	        return -1;
	    }
	    break;
	}

    memmove(info->ipaddr, dhcp->yiaddr, IP_ALEN);

    return messageType;
}

#ifndef NO_REQUEST_LIST
static u8* AddRequestList(u8* opt)
{
    u8* ptr = opt;

    // Request list
    *ptr++ = DHCP_OPT_REQUEST_LIST;
    *ptr++ = 2; // length
    *ptr++ = DHCP_OPT_SUBNETMASK;
    *ptr++ = DHCP_OPT_ROUTER;
    *ptr++ = DHCP_OPT_DNS;
    *ptr++ = DHCP_OPT_HOST_NAME;
    *ptr++ = DHCP_OPT_DOMAIN_NAME;
//  *ptr++ = DHCP_OPT_DEFAULT_TTL;
//  *ptr++ = DHCP_OPT_MTU;
    *ptr++ = DHCP_OPT_BROADCAST_ADDR;

#if (0 < DHCP_MAX_STATIC_ROUTE)
    *ptr++ = DHCP_OPT_STATIC_ROUTE;
#endif

    *ptr++ = DHCP_OPT_RENEWAL_TIME;
    *ptr++ = DHCP_OPT_REBINDING_TIME;
    opt[1] = (u8) (ptr - opt - 2);
    return ptr;
}
#endif

static void RecvCallback(UDPInfo* info, s32 result)
{
    DHCPControl* ctrl;
    DHCPHeader*  dhcp;
    int          type;
    u8           addr[IP_ALEN];

    ctrl = (DHCPControl*) ((u8*) info - offsetof(DHCPControl, udp));
    dhcp = (DHCPHeader*) ctrl->heap;
    if (result < DHCP_MIN_HLEN + 5 ||
        dhcp->xid != ctrl->xid ||
        dhcp->htype != ARP_HARDWARE_ETHERNET ||
        dhcp->hlen != ETH_ALEN ||
        memcmp(dhcp->chaddr, __IFDefault.mac, ETH_ALEN) != 0 ||
        (type = DHCPProcessOptions(dhcp, result, &ctrl->tempInfo)) < 0)
    {
        goto Drop;
    }

#ifdef VERBOSE
    DHCPDump(dhcp, result - DHCP_MIN_HLEN);
#endif

    switch (ctrl->state)
    {
      case DHCP_STATE_SELECTING:
        if (type == DHCP_OFFER && ctrl->tempInfo.lease != 0)
        {
            memmove(&ctrl->info, &ctrl->tempInfo, sizeof(DHCPInfo));
            ctrl->rxmitCount = 0;
            ctrl->state = DHCP_STATE_REQUESTING;
            ctrl->callback(ctrl->state);
            // The DHCPREQUEST message contains the same 'xid' as the DHCPOFFER
            // message. [RFC 2131]
            DHCPRequest(ctrl);
            return;
            // NOT REACHED HERE
        }
        break;
      case DHCP_STATE_REQUESTING:
        switch (type)
        {
          case DHCP_ACK:
            if (ctrl->tempInfo.lease == 0)
            {
                return;
            }
            ctrl->ackTime = OSGetTime();
            UpdateDHCPInfo(&ctrl->info, &ctrl->tempInfo);
            Claim(ctrl);
            return;
            // NOT REACHED HERE
          case DHCP_NAK:
            Stop(ctrl); // Discard offer
            IPSetConfigError(NULL, IP_ERR_DHCP_NAK);
            return;
            // NOT REACHED HERE
        }
        break;
      case DHCP_STATE_RENEWING:
      case DHCP_STATE_REBINDING:
        switch (type)
        {
          case DHCP_ACK:
            if (ctrl->tempInfo.lease == 0)
            {
                return;
            }

            // If the client is given a new
            // network address, it MUST NOT continue using the previous network
            // address and SHOULD notify the local users of the problem. [RFC 2113]
            IPGetAddr(NULL, addr);
            if (IP_ADDR_NE(dhcp->yiaddr, addr))
            {
                Stop(ctrl); // Halt network
                IPSetConfigError(NULL, IP_ERR_DHCP_NAK);
                return;
                // NOT REACHED HERE
            }

            ctrl->ackTime = OSGetTime();
            UpdateDHCPInfo(&ctrl->info, &ctrl->tempInfo);
            Start(ctrl);
            return;
            // NOT REACHED HERE
          case DHCP_NAK:
            Stop(ctrl); // Halt network
            IPSetConfigError(NULL, IP_ERR_DHCP_NAK);
            return;
            // NOT REACHED HERE
        }
        break;

      case DHCP_STATE_REBOOTING:
        switch (type)
        {
          case DHCP_ACK:
            if (ctrl->tempInfo.lease == 0)
            {
                return;
            }
            ctrl->ackTime = OSGetTime();
            UpdateDHCPInfo(&ctrl->info, &ctrl->tempInfo);
            Claim(ctrl);
            return;
            // NOT REACHED HERE
          case DHCP_NAK:
            Stop(ctrl);
            IPSetConfigError(NULL, IP_ERR_DHCP_NAK);
            // Try again
            if ((ctrl->flag & FLAG_AUTO) == 0)
            {
                Restart(ctrl, AUTO_WAIT);
            }
            return;
            // NOT REACHED HERE
        }
        break;
    }

Drop:
    // Wait for another DHCP server's response keeping the current time-out timer
    UDPReceiveAsync(&ctrl->udp, ctrl->heap, sizeof(ctrl->heap),
                    NULL, &ctrl->socket,
                    RecvCallback, NULL);
}

static void T1Handler(OSAlarm* alarm, OSContext* context)
{
    #pragma unused(context)
    DHCPControl*  ctrl;

    ctrl = (DHCPControl*) ((u8*) alarm - offsetof(DHCPControl, t1));
    ctrl->state = DHCP_STATE_RENEWING;
    ctrl->callback(ctrl->state);

    ++ctrl->xid;
    ctrl->rxmitCount = 0;

    DHCPRequest(ctrl);
}

static void T2Handler(OSAlarm* alarm, OSContext* context)
{
    #pragma unused(context)
    DHCPControl*  ctrl;

    ctrl = (DHCPControl*) ((u8*) alarm - offsetof(DHCPControl, t2));
    ctrl->state = DHCP_STATE_REBINDING;
    ctrl->callback(ctrl->state);

    ++ctrl->xid;
    ctrl->rxmitCount = 0;

    DHCPRequest(ctrl);
}

static void ExHandler(OSAlarm* alarm, OSContext* context)
{
    #pragma unused(context)
    DHCPControl*  ctrl;

    ctrl = (DHCPControl*) ((u8*) alarm - offsetof(DHCPControl, expire));
    IPSetConfigError(NULL, IP_ERR_DHCP_EXPIRED);
    Stop(ctrl);
}

static void RxmitHandler(OSAlarm* alarm, OSContext* context)
{
    #pragma unused(context)
    DHCPControl* ctrl;

    ctrl = (DHCPControl*) ((u8*) alarm - offsetof(DHCPControl, rxmitAlarm));

    ++ctrl->rxmitCount;
    if (ctrl->rxmitCount == ctrl->rxmitMax)
    {
        switch (ctrl->state)
        {
          case DHCP_STATE_SELECTING:
          case DHCP_STATE_REQUESTING:
            IPSetConfigError(NULL, IP_ERR_DHCP_TIMEOUT);
            Stop(ctrl);
            return;
          case DHCP_STATE_RENEWING:
          case DHCP_STATE_REBINDING:
            return;
          case DHCP_STATE_REBOOTING:
            // Time-out: Use the previously allocated network address
            ctrl->state = DHCP_STATE_BOUND;
            ctrl->callback(ctrl->state);
            return;
        }
    }

    if (ctrl->rxmitMax <= ctrl->rxmitCount)
    {
        ctrl->rxmitCount = ctrl->rxmitMax;
    }
    switch (ctrl->state)
    {
      case DHCP_STATE_SELECTING:
        DHCPDiscover(ctrl);
        break;
      case DHCP_STATE_REQUESTING:
      case DHCP_STATE_RENEWING:
      case DHCP_STATE_REBINDING:
      case DHCP_STATE_REBOOTING:
        DHCPRequest(ctrl);
        break;
    }
}

static void ReleaseCallback(UDPInfo* info, s32 result)
{
    #pragma unused(result)
    DHCPControl* ctrl;

    ctrl = (DHCPControl*) ((u8*) info - offsetof(DHCPControl, udp));
    Stop(ctrl);
}

static void ReleaseHandler(OSAlarm* alarm, OSContext* context)
{
    #pragma unused(context)
    DHCPControl* ctrl;

    ctrl = (DHCPControl*) ((u8*) alarm - offsetof(DHCPControl, rxmitAlarm));
    Stop(ctrl);
}

/*---------------------------------------------------------------------------*
  Name:         DHCPDiscover

  Description:  Broadcasts a DHCPDISCOVER message on its local physical subnet

  Arguments:    ctrl    Pointer to DHCPControl

  Returns:
 *---------------------------------------------------------------------------*/
static s32 DHCPDiscover(DHCPControl* ctrl)
{
    DHCPHeader* dhcp;
    u8*         opt;
    IPSocket    socket;
    s32         result;

    if (ctrl->state != DHCP_STATE_SELECTING)
    {
        return IP_ERR_INVALID;
    }

    UDPCancel(&ctrl->udp);
    OSCancelAlarm(&ctrl->rxmitAlarm);

    // Form options
    opt = &ctrl->heap[DHCP_MIN_HLEN];
    memmove(opt, MagicCookie, IP_ALEN);
    opt += IP_ALEN;

    // DHCP message type
    *opt++ = DHCP_OPT_DHCP_TYPE;
    *opt++ = 1;
    *opt++ = DHCP_DISCOVER;

    // Client identifier
    *opt++ = DHCP_OPT_CLIENT_IDENTIFIER;
    *opt++ = 1 + ETH_ALEN;
    *opt++ = ARP_HARDWARE_ETHERNET;
    memmove(opt, __IFDefault.mac, ETH_ALEN);
    opt += ETH_ALEN;

#ifndef NO_REQUEST_LIST
    // Request list
    opt = AddRequestList(opt);
#endif

    // Host name
    if (ctrl->hostName[0])
    {
        size_t len;

        len = strlen(ctrl->hostName);
        ASSERT(len <= 255);
        *opt++ = DHCP_OPT_HOST_NAME;
        *opt++ = (u8) len;
        memmove(opt, ctrl->hostName, len);
        opt += len;
    }

    // End
    *opt++ = DHCP_OPT_END;
    ctrl->len = opt - ctrl->heap;
    if (ctrl->len < DHCP_BOOTP_LEN)
    {
        memset(opt, DHCP_OPT_PAD, (u32) (DHCP_BOOTP_LEN - ctrl->len));
        ctrl->len = DHCP_BOOTP_LEN;
    }

    // Form request
    dhcp = (DHCPHeader*) &ctrl->heap[0];
    dhcp->op = DHCP_BOOTREQUEST;
    dhcp->htype = ARP_HARDWARE_ETHERNET;
    dhcp->hlen = ETH_ALEN;
    dhcp->hops = 0;
    dhcp->xid = ctrl->xid;
    dhcp->secs = 0;
    dhcp->flags = 0;
    memset(dhcp->ciaddr, 0, IP_ALEN);
    memset(dhcp->yiaddr, 0, IP_ALEN);
    memset(dhcp->siaddr, 0, IP_ALEN);
    memset(dhcp->giaddr, 0, IP_ALEN);
    memmove(dhcp->chaddr, __IFDefault.mac, ETH_ALEN);
    memset(dhcp->sname, 0, 64);
    memset(dhcp->file,  0, 128);

#ifdef VERBOSE
    DHCPDump(dhcp, ctrl->len - DHCP_MIN_HLEN);
#endif

    socket.len    = IP_SOCKLEN;
    socket.family = IP_INET;
    memmove(&socket.addr, IPLimited, IP_ALEN);
    socket.port = DHCP_SERVER_PORT;
    result = UDPSendAsync(&ctrl->udp, ctrl->heap, ctrl->len, &socket,
                          NULL, NULL);

    OSSetAlarm(&ctrl->rxmitAlarm, DHCPBackoff(ctrl, ctrl->rxmitCount),
               RxmitHandler);
    UDPReceiveAsync(&ctrl->udp, ctrl->heap, sizeof(ctrl->heap),
                    NULL, &ctrl->socket,
                    RecvCallback, NULL);

    return result;
}

/*---------------------------------------------------------------------------*
  Name:         DHCPDecline

  Description:

  Arguments:    ctrl    Pointer to DHCPControl

  Returns:
 *---------------------------------------------------------------------------*/
static s32 DHCPDecline(DHCPControl* ctrl)
{
    DHCPHeader* dhcp;
    u8*         opt;
    IPSocket    socket;

    if (ctrl->state != DHCP_STATE_REQUESTING &&
        ctrl->state != DHCP_STATE_REBOOTING &&
        ctrl->state != DHCP_STATE_RENEWING &&
        ctrl->state != DHCP_STATE_REBINDING)
    {
        return IP_ERR_INVALID;
    }

    UDPCancel(&ctrl->udp);
    OSCancelAlarm(&ctrl->rxmitAlarm);

    // Form options
    opt = &ctrl->heap[DHCP_MIN_HLEN];
    memmove(opt, MagicCookie, IP_ALEN);
    opt += IP_ALEN;

    // DHCP message type
    *opt++ = DHCP_OPT_DHCP_TYPE;
    *opt++ = 1;
    *opt++ = DHCP_DECLINE;

    // Server Identifier
    *opt++ = DHCP_OPT_SERVER_ID;
    *opt++ = IP_ALEN;
    memmove(opt, ctrl->info.server, IP_ALEN);
    opt += IP_ALEN;

    // Requested IP Address
    *opt++ = DHCP_OPT_REQUESTED_ADDR;
    *opt++ = IP_ALEN;
    memmove(opt, ctrl->info.ipaddr, IP_ALEN);
    opt += IP_ALEN;

    // Client identifier
    *opt++ = DHCP_OPT_CLIENT_IDENTIFIER;
    *opt++ = 1 + ETH_ALEN;
    *opt++ = ARP_HARDWARE_ETHERNET;
    memmove(opt, __IFDefault.mac, ETH_ALEN);
    opt += ETH_ALEN;

    // End
    *opt++ = DHCP_OPT_END;
    ctrl->len = opt - ctrl->heap;
    if (ctrl->len < DHCP_BOOTP_LEN)
    {
        memset(opt, DHCP_OPT_PAD, (u32) (DHCP_BOOTP_LEN - ctrl->len));
        ctrl->len = DHCP_BOOTP_LEN;
    }

    // Form request
    dhcp = (DHCPHeader*) &ctrl->heap[0];
    dhcp->op = DHCP_BOOTREQUEST;
    dhcp->htype = ARP_HARDWARE_ETHERNET;
    dhcp->hlen = ETH_ALEN;
    dhcp->hops = 0;
    dhcp->xid = ctrl->xid;
    dhcp->secs = 0;
    dhcp->flags = 0;
    memset(dhcp->ciaddr, 0, IP_ALEN);
    memset(dhcp->yiaddr, 0, IP_ALEN);
    memset(dhcp->siaddr, 0, IP_ALEN);
    memset(dhcp->giaddr, 0, IP_ALEN);
    memmove(dhcp->chaddr, __IFDefault.mac, ETH_ALEN);
    memset(dhcp->sname, 0, 64);
    memset(dhcp->file,  0, 128);

#ifdef VERBOSE
    DHCPDump(dhcp, ctrl->len - DHCP_MIN_HLEN);
#endif

    OSSetAlarm(&ctrl->rxmitAlarm, DHCPBackoff(ctrl, ctrl->rxmitCount),
               ReleaseHandler);

    socket.len    = IP_SOCKLEN;
    socket.family = IP_INET;
    memmove(&socket.addr, IPLimited, IP_ALEN);
    socket.port = DHCP_SERVER_PORT;
    return UDPSendAsync(&ctrl->udp, ctrl->heap, ctrl->len, &socket,
                        ReleaseCallback, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         DHCPRelease

  Description:  Unicast DHCPRELEASE to the server

  Arguments:    ctrl    Pointer to DHCPControl

  Returns:
 *---------------------------------------------------------------------------*/
static s32 DHCPRelease(DHCPControl* ctrl)
{
    DHCPHeader* dhcp;
    u8*         opt;
    IPSocket    socket;

    if (ctrl->state != DHCP_STATE_BOUND &&
        ctrl->state != DHCP_STATE_RENEWING &&
        ctrl->state != DHCP_STATE_REBINDING)
    {
        return IP_ERR_INVALID;
    }

    UDPCancel(&ctrl->udp);
    OSCancelAlarm(&ctrl->rxmitAlarm);

    // Form options
    opt = &ctrl->heap[DHCP_MIN_HLEN];
    memmove(opt, MagicCookie, IP_ALEN);
    opt += IP_ALEN;

    // DHCP message type
    *opt++ = DHCP_OPT_DHCP_TYPE;
    *opt++ = 1;
    *opt++ = DHCP_RELEASE;

    // Server Identifier
    *opt++ = DHCP_OPT_SERVER_ID;
    *opt++ = IP_ALEN;
    memmove(opt, ctrl->info.server, IP_ALEN);
    opt += IP_ALEN;

    // Client identifier
    *opt++ = DHCP_OPT_CLIENT_IDENTIFIER;
    *opt++ = 1 + ETH_ALEN;
    *opt++ = ARP_HARDWARE_ETHERNET;
    memmove(opt, __IFDefault.mac, ETH_ALEN);
    opt += ETH_ALEN;

    // End
    *opt++ = DHCP_OPT_END;
    ctrl->len = opt - ctrl->heap;
    if (ctrl->len < DHCP_BOOTP_LEN)
    {
        memset(opt, DHCP_OPT_PAD, (u32) (DHCP_BOOTP_LEN - ctrl->len));
        ctrl->len = DHCP_BOOTP_LEN;
    }

    // Form request
    dhcp = (DHCPHeader*) &ctrl->heap[0];
    dhcp->op = DHCP_BOOTREQUEST;
    dhcp->htype = ARP_HARDWARE_ETHERNET;
    dhcp->hlen = ETH_ALEN;
    dhcp->hops = 0;
    dhcp->xid = ctrl->xid;
    dhcp->secs = 0;
    dhcp->flags = 0;
    memmove(dhcp->ciaddr, ctrl->info.ipaddr, IP_ALEN);
    memset(dhcp->yiaddr, 0, IP_ALEN);
    memset(dhcp->siaddr, 0, IP_ALEN);
    memset(dhcp->giaddr, 0, IP_ALEN);
    memmove(dhcp->chaddr, __IFDefault.mac, ETH_ALEN);
    memset(dhcp->sname, 0, 64);
    memset(dhcp->file,  0, 128);

#ifdef VERBOSE
    DHCPDump(dhcp, ctrl->len - DHCP_MIN_HLEN);
#endif

    OSSetAlarm(&ctrl->rxmitAlarm, DHCPBackoff(ctrl, ctrl->rxmitCount),
               ReleaseHandler);

    // Unicast to the server
    socket.len    = IP_SOCKLEN;
    socket.family = IP_INET;
    memmove(&socket.addr, ctrl->info.server, IP_ALEN);
    socket.port = DHCP_SERVER_PORT;
    return UDPSendAsync(&ctrl->udp, ctrl->heap, ctrl->len, &socket,
                        ReleaseCallback, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         DHCPRequest

  Description:  Broadcasts a DHCPREQUEST message including the 'server
                identifier' option

  Arguments:    ctrl    Pointer to DHCPControl

  Returns:
 *---------------------------------------------------------------------------*/
static s32 DHCPRequest(DHCPControl* ctrl)
{
    DHCPHeader* dhcp;
    u8*         opt;
    IPSocket    socket;
    s32         result;
    OSTime      backoff;

    if (ctrl->state != DHCP_STATE_REQUESTING &&
        ctrl->state != DHCP_STATE_REBOOTING &&
        ctrl->state != DHCP_STATE_RENEWING &&
        ctrl->state != DHCP_STATE_REBINDING)
    {
        return IP_ERR_INVALID;
    }

    UDPCancel(&ctrl->udp);
    OSCancelAlarm(&ctrl->rxmitAlarm);

    //
    // Form options
    //
    opt = &ctrl->heap[DHCP_MIN_HLEN];
    memmove(opt, MagicCookie, IP_ALEN);
    opt += IP_ALEN;

    // DHCP message type
    *opt++ = DHCP_OPT_DHCP_TYPE;
    *opt++ = 1;
    *opt++ = DHCP_REQUEST;

    // Server Identifier
    if (ctrl->state == DHCP_STATE_REQUESTING)
    {
        *opt++ = DHCP_OPT_SERVER_ID;
        *opt++ = IP_ALEN;
        memmove(opt, ctrl->info.server, IP_ALEN);
        opt += IP_ALEN;
    }

    // Requested IP Address
    if (ctrl->state == DHCP_STATE_REQUESTING ||
        ctrl->state == DHCP_STATE_REBOOTING)
    {
        *opt++ = DHCP_OPT_REQUESTED_ADDR;
        *opt++ = IP_ALEN;
        memmove(opt, ctrl->info.ipaddr, IP_ALEN);
        opt += IP_ALEN;
    }

    // Client identifier
    *opt++ = DHCP_OPT_CLIENT_IDENTIFIER;
    *opt++ = 1 + ETH_ALEN;
    *opt++ = ARP_HARDWARE_ETHERNET;
    memmove(opt, __IFDefault.mac, ETH_ALEN);
    opt += ETH_ALEN;

#ifndef NO_REQUEST_LIST
    // Request list
    opt = AddRequestList(opt);
#endif

    // Host name
    if (ctrl->hostName[0])
    {
        size_t len;

        len = strlen(ctrl->hostName);
        ASSERT(len <= 255);
        *opt++ = DHCP_OPT_HOST_NAME;
        *opt++ = (u8) len;
        memmove(opt, ctrl->hostName, len);
        opt += len;
    }

    // End
    *opt++ = DHCP_OPT_END;
    ctrl->len = opt - ctrl->heap;
    if (ctrl->len < DHCP_BOOTP_LEN)
    {
        memset(opt, DHCP_OPT_PAD, (u32) (DHCP_BOOTP_LEN - ctrl->len));
        ctrl->len = DHCP_BOOTP_LEN;
    }

    //
    // Form request
    //
    dhcp = (DHCPHeader*) &ctrl->heap[0];
    if (ctrl->state == DHCP_STATE_RENEWING ||
        ctrl->state == DHCP_STATE_REBINDING)
    {
        memmove(dhcp->ciaddr, ctrl->info.ipaddr, IP_ALEN);
    }
    else
    {
        memset(dhcp->ciaddr, 0, IP_ALEN);
    }
    dhcp->op = DHCP_BOOTREQUEST;
    dhcp->htype = ARP_HARDWARE_ETHERNET;
    dhcp->hlen = ETH_ALEN;
    dhcp->hops = 0;
    dhcp->xid = ctrl->xid;
    dhcp->secs = 0;
    dhcp->flags = 0;
    memset(dhcp->yiaddr, 0, IP_ALEN);
    memset(dhcp->siaddr, 0, IP_ALEN);
    memset(dhcp->giaddr, 0, IP_ALEN);
    memmove(dhcp->chaddr, __IFDefault.mac, ETH_ALEN);
    memset(dhcp->sname, 0, 64);
    memset(dhcp->file,  0, 128);

    //
    // Form Socket
    //
    socket.len    = IP_SOCKLEN;
    socket.family = IP_INET;
    if (ctrl->state == DHCP_STATE_RENEWING)
    {
        memmove(&socket.addr, ctrl->info.server, IP_ALEN);
    }
    else
    {
        memmove(&socket.addr, IPLimited, IP_ALEN);
    }
    socket.port = DHCP_SERVER_PORT;

#ifdef VERBOSE
    DHCPDump(dhcp, ctrl->len - DHCP_MIN_HLEN);
#endif

    switch (ctrl->state)
    {
      case DHCP_STATE_REQUESTING:
      case DHCP_STATE_REBOOTING:
        backoff = DHCPBackoff(ctrl, ctrl->rxmitCount);
        break;
      case DHCP_STATE_RENEWING:
        ctrl->rxmitCount = 0;
        backoff = (ctrl->t2Time - OSGetTime()) / 2;
        if (backoff <= OSSecondsToTicks((OSTime) 60))
        {
            ctrl->rxmitCount = ctrl->rxmitMax - 1;
        }
        break;
      case DHCP_STATE_REBINDING:
        ctrl->rxmitCount = 0;
        backoff = (ctrl->expireTime - OSGetTime()) / 2;
        if (backoff <= OSSecondsToTicks((OSTime) 60))
        {
            ctrl->rxmitCount = ctrl->rxmitMax - 1;
        }
        break;
    }

    result = UDPSendAsync(&ctrl->udp, ctrl->heap, ctrl->len, &socket,
                          NULL, NULL);

    OSSetAlarm(&ctrl->rxmitAlarm, backoff, RxmitHandler);
    UDPReceiveAsync(&ctrl->udp, ctrl->heap, sizeof(ctrl->heap),
                    NULL, &ctrl->socket,
                    RecvCallback, NULL);

    return result;
}

static void Start(DHCPControl* ctrl)
{
    DHCPInfo* info = &ctrl->info;
    u32       renewal;      // DHCP_OPT_RENEWAL_TIME [sec] (t1)
    u32       rebinding;    // DHCP_OPT_REBINDING_TIME [sec] (t2)
    u32       lease;
    OSTime    t;

    ASSERT(info->lease != 0);

    UDPCancel(&ctrl->udp);
    OSCancelAlarm(&ctrl->rxmitAlarm);
    ctrl->rxmitCount = 0;

    OSCancelAlarm(&ctrl->t1);
    OSCancelAlarm(&ctrl->t2);
    OSCancelAlarm(&ctrl->expire);

    lease = info->lease;

    // Check T1 < T2 < lease time
    renewal = info->renewal;
    if (renewal == 0 || lease <= renewal)
    {
        // T1 defaults to (0.5 * duration_of_lease)
        renewal = lease / 2;
    }

    rebinding = info->rebinding;
    if (rebinding == 0 || lease <= rebinding)
    {
        // T2 defaults to (0.875 * duration_of_lease)
        rebinding = (u32) ((7 * (u64) lease) / 8);
    }
    if (rebinding <= renewal)
    {
        renewal = (u32) ((8 * (u64) rebinding) / 14);
    }

#ifdef TIMER_DEBUG
    renewal = 15;
    rebinding = renewal + 260;
    lease = rebinding + 130;
#endif  // TIMER_DEBUG

    ctrl->t2Time = ctrl->ackTime + OSSecondsToTicks((OSTime) rebinding);
    ctrl->expireTime = ctrl->ackTime + OSSecondsToTicks((OSTime) lease);

    // Adjust ARP probe delay
    t = OSGetTime() - ctrl->ackTime;
    if (OSSecondsToTicks((OSTime) renewal) <= t)
    {
        t = OSSecondsToTicks((OSTime) renewal) - 1;
    }

    OSSetAlarm(&ctrl->t1, OSSecondsToTicks((OSTime) renewal) - t, T1Handler);
    OSSetAlarm(&ctrl->t2, OSSecondsToTicks((OSTime) rebinding) - t, T2Handler);
    OSSetAlarm(&ctrl->expire, OSSecondsToTicks((OSTime) lease) - t, ExHandler);

    IPInitRoute(info->ipaddr, info->netmask, info->router);
    IPSetBroadcastAddr(&__IFDefault, info->broadcast);

#if (0 < DHCP_MAX_STATIC_ROUTE)
{
    int i;
    for (i = 0; i < DHCP_MAX_STATIC_ROUTE; ++i)
    {
        if (IP_ADDR_EQ(info->staticRoute[i].dest, IPAddrAny))
        {
            break;
        }
        IPAddRoute(info->staticRoute[i].dest, IPLimited, info->staticRoute[i].router);
    }
}
#endif

    if (68 <= info->mtu)    // Official minimum MTU [RFC 791]
    {
        // Set interface MTU to DHCP MTU
        s32 mtu;

        IPGetMtu(&__IFDefault, &mtu);
        mtu = MIN(info->mtu, mtu);
        IPSetMtu(&__IFDefault, mtu);
    }

    ctrl->state = DHCP_STATE_BOUND;
    ctrl->callback(ctrl->state);
}

static void Stop(DHCPControl* ctrl)
{
    if (ctrl->state == DHCP_STATE_INIT)
    {
        return;
    }

    // Change the state first to block subsequent call to Stop().
    ctrl->state = DHCP_STATE_INIT;

    UDPClose(&ctrl->udp);
    OSCancelAlarm(&ctrl->rxmitAlarm);
    ctrl->rxmitCount = 0;

    OSCancelAlarm(&ctrl->t1);
    OSCancelAlarm(&ctrl->t2);
    OSCancelAlarm(&ctrl->expire);

    ctrl->flag &= ~FLAG_MORIBUND;

    IPInitRoute(NULL, NULL, NULL);
    IPSetBroadcastAddr(&__IFDefault, IPLimited);

    memcpy(Conf.addr, IPAddrAny, IP_ALEN);
    ARPClaim(&__IFDefault, &Conf);   // De-claim

    ctrl->callback(ctrl->state);

    if (ctrl->flag & FLAG_AUTO)
    {
        Restart(ctrl, AUTO_WAIT);
    }
}

static void ClaimHandler(IPInterfaceConf* conf, s32 result)
{
    #pragma unused( conf )
    DHCPControl* ctrl = &Control;

    // De-claim
    memset(conf->addr, 0, IP_ALEN);
    ARPClaim(conf->interface, conf);

    if (result == IP_ERR_NONE)
    {
        // Collision not detected
        Start(&Control);
    }
    else
    {
        // Collision detected
        OSCancelAlarm(&ctrl->rxmitAlarm);
        ctrl->rxmitCount = 0;
        OSCancelAlarm(&ctrl->t1);
        OSCancelAlarm(&ctrl->t2);
        OSCancelAlarm(&ctrl->expire);
        ctrl->flag |= FLAG_MORIBUND;
        ++ctrl->xid;
        if (DHCPDecline(ctrl) < 0)
        {
            Stop(ctrl);
        }
        IPSetConfigError(conf->interface, IP_ERR_ADDR_COLLISION);
    }
}

static void Claim(DHCPControl* ctrl)
{
    DHCPInfo* info = &ctrl->info;

    UDPCancel(&ctrl->udp);
    OSCancelAlarm(&ctrl->rxmitAlarm);
    ctrl->rxmitCount = 0;

    OSCancelAlarm(&ctrl->t1);
    OSCancelAlarm(&ctrl->t2);
    OSCancelAlarm(&ctrl->expire);

    memcpy(Conf.addr, info->ipaddr, IP_ALEN);
    ARPClaim(&__IFDefault, &Conf);
}

static BOOL Restart(DHCPControl* ctrl, OSTime wait)
{
    IPSocket socket;

    if (ctrl->state != DHCP_STATE_INIT)
    {
        return FALSE;
    }

    ctrl->state = DHCP_STATE_SELECTING;
    ctrl->callback(ctrl->state);
    ++ctrl->xid;

    UDPOpen(&ctrl->udp, NULL, 0);

    socket.len    = IP_SOCKLEN;
    socket.family = IP_INET;
    memmove(socket.addr, IPAddrAny, IP_ALEN);
    socket.port = DHCP_CLIENT_PORT;
    if (UDPBind(&ctrl->udp, &socket) < 0)
    {
        return FALSE;
    }

    switch (ctrl->state)
    {
      case DHCP_STATE_SELECTING:
        // The client SHOULD wait a random time between one and
        // ten seconds to desynchronize the use of DHCP at startup.
        // [RFC 2131 4.4.1]
        //
        // Do not call DHCPDiscover() immediately.
        ctrl->rxmitCount = -1;
        OSCancelAlarm(&ctrl->rxmitAlarm);
        OSSetAlarm(&ctrl->rxmitAlarm, wait, RxmitHandler);
        break;
      case DHCP_STATE_REQUESTING:
        DHCPRequest(ctrl);
        break;
    }

    return TRUE;
}

static void NullCallback(int state)
{
    #pragma unused( state )
}

BOOL DHCPStartupEx(DHCPCallback callback, int rxmitMax, const char* hostName)
{
    DHCPControl* ctrl = &Control;
    BOOL         enabled;
    BOOL         rc;

    enabled = OSDisableInterrupts();
    if ((ctrl->flag & FLAG_INIT) == 0)
    {
        memset(ctrl, 0, sizeof(DHCPControl));
        ctrl->flag |= FLAG_AUTO | FLAG_INIT;
        ctrl->rxmitMax = (rxmitMax <= 0) ? MAX_RXMIT : rxmitMax;

        if (hostName)
        {
            strncpy(ctrl->hostName, hostName, sizeof(ctrl->hostName));
        }

        // A client may choose a different, random initial 'xid'
        // each time the client is rebooted. [RFC 2132]
        ctrl->xid = OSGetTick();

        ctrl->socket.len = sizeof(IPSocket);

        OSCreateAlarm(&Conf.alarm);
        Conf.callback = (IFCallback) ClaimHandler;
    }
    ctrl->callback = callback ? callback : NullCallback;
    // The client SHOULD wait a random time between one and
    // ten seconds to desynchronize the use of DHCP at startup.
    // [RFC 2131 4.4.1]
    rc = Restart(ctrl,
                 OSSecondsToTicks(1) + (OSGetTick() % OSSecondsToTicks(1)));
    OSRestoreInterrupts(enabled);
    return rc;
}

BOOL DHCPStartup(DHCPCallback callback)
{
    return DHCPStartupEx(callback, MAX_RXMIT, NULL);
}

BOOL DHCPCleanup(void)
{
    DHCPControl* ctrl = &Control;
    BOOL         enabled;
    BOOL         rc;

    enabled = OSDisableInterrupts();
    if (ctrl->flag & FLAG_INIT)
    {
        DHCPAuto(FALSE);
        if (ctrl->state != DHCP_STATE_INIT &&
            (ctrl->flag & FLAG_MORIBUND) == 0)
        {
            OSCancelAlarm(&ctrl->rxmitAlarm);
            ctrl->rxmitCount = 0;
            OSCancelAlarm(&ctrl->t1);
            OSCancelAlarm(&ctrl->t2);
            OSCancelAlarm(&ctrl->expire);
            ctrl->flag |= FLAG_MORIBUND;
            ++ctrl->xid;
            if (DHCPRelease(ctrl) < 0)
            {
                Stop(ctrl);
            }
        }
        rc = TRUE;
    }
    else
    {
        rc = FALSE;
    }
    OSRestoreInterrupts(enabled);
    return rc;
}

BOOL DHCPReboot(void)
{
    DHCPControl* ctrl = &Control;

    switch (ctrl->state)
    {
      case DHCP_STATE_BOUND:
      case DHCP_STATE_RENEWING:
      case DHCP_STATE_REBINDING:
        ctrl->state = DHCP_STATE_REBOOTING;
        ctrl->callback(ctrl->state);
        ctrl->rxmitCount = 0;
        ++ctrl->xid;
        DHCPRequest(ctrl);
        return TRUE;
        break;
    }
    return FALSE;
}

BOOL DHCPAuto(BOOL enable)
{
    DHCPControl* ctrl = &Control;
    BOOL         prev;
    BOOL         enabled;

    enabled = OSDisableInterrupts();
    prev = (ctrl->flag & FLAG_AUTO) ? TRUE : FALSE;
    if (enable)
    {
        ctrl->flag |= FLAG_AUTO;
        Restart(ctrl, AUTO_WAIT);
    }
    else
    {
        ctrl->flag &= ~FLAG_AUTO;
    }
    OSRestoreInterrupts(enabled);
    return prev;
}

/*---------------------------------------------------------------------------*
  Name:         DHCPGetStatus

  Description:  Get the current DHCP state machine state as well as the
                current host configuration information.

  Arguments:    info    Pointer to DHCPInfo to which store the current
                        information. Set to NULL if not necessary.

  Returns:      The current DHCP state machine state
 *---------------------------------------------------------------------------*/
int DHCPGetStatus(DHCPInfo* info)
{
    DHCPControl* ctrl = &Control;
    BOOL         enabled;
    int          state;

    enabled = OSDisableInterrupts();
    state = ctrl->state;
    if (info)
    {
        memmove(info, &ctrl->info, sizeof(DHCPInfo));
    }
    OSRestoreInterrupts(enabled);
    return state;
}

int DHCPGetOpt(int opt, void* buf, int len)
{
    DHCPControl* ctrl = &Control;
    u32          ulen;

    if (len < 0)
    {
        len = 0;
    }
    ulen = (u32) len;
    switch (opt)
    {
      case DHCP_OPT_SUBNETMASK:
        ulen = MIN(IP_ALEN, ulen);
        memmove(buf, ctrl->info.netmask, ulen);
        break;
      case DHCP_OPT_ROUTER:
        ulen = MIN(IP_ALEN, ulen);
        memmove(buf, ctrl->info.router, ulen);
        break;
      case DHCP_OPT_DNS:
        ulen = MIN(2 * IP_ALEN, ulen);
        memmove(buf, ctrl->info.dns1, ulen);
        break;
      case DHCP_OPT_HOST_NAME:
        ulen = MIN(strlen(ctrl->info.host), ulen);
        strncpy(buf, ctrl->info.host, ulen);
        break;
      case DHCP_OPT_DOMAIN_NAME:
        ulen = MIN(strlen(ctrl->info.domain), ulen);
        strncpy(buf, ctrl->info.domain, ulen);
        break;
      case DHCP_OPT_MTU:
        ulen = MIN(sizeof(u16), ulen);
        memmove(buf, &ctrl->info.mtu, ulen);
        break;
      case DHCP_OPT_BROADCAST_ADDR:
        ulen = MIN(IP_ALEN, ulen);
        memmove(buf, ctrl->info.broadcast, ulen);
        break;
      case DHCP_OPT_LEASE_TIME:
        ulen = MIN(sizeof(u32), ulen);
        memmove(buf, &ctrl->info.lease, ulen);
        break;
      case DHCP_OPT_SERVER_ID:
        ulen = MIN(IP_ALEN, ulen);
        memmove(buf, ctrl->info.server, ulen);
        break;
      case DHCP_OPT_RENEWAL_TIME:
        ulen = MIN(sizeof(u32), ulen);
        memmove(buf, &ctrl->info.renewal, ulen);
        break;
      case DHCP_OPT_REBINDING_TIME:
        ulen = MIN(sizeof(u32), ulen);
        memmove(buf, &ctrl->info.rebinding, ulen);
        break;
      default:
        break;
    }
    return (int) ulen;
}
