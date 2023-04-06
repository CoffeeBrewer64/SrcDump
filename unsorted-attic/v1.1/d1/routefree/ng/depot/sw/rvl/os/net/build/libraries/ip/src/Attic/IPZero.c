d1 192
a192 180
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:

  Copyright 2002 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip6/src/IPZero.c $
    
    9     12/13/05 19:12 Shiki
    Revised using IPLinkLocal[]. 
    Revised IPAutoConfig() to check Conf.addr so that it can be called more
    than once while claiming the address.

    8     8/20/03 16:27 Shiki
    Clean up.

    7     4/28/03 21:16 Shiki
    Revised IPAutoStop().

    6     4/28/03 21:03 Shiki
    Implemented IPAutoStop().
    Fixed suffix selection code.

    5     4/28/03 18:49 Shiki
    Fixed ClaimHandler() to use the result code parameter. Also fixed to
    retry at most ten times upon address collisions (previously eleven).

    4     4/30/02 14:52 Shiki
    Minor clean up.

    3     4/24/02 11:20 Shiki
    Revised IPAutoConfig() to use the last IP address once again if it is
    called twice or more.

    2     3/18/02 14:36 Shiki
    Added WIN32 code for testing.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <dolphin/os.h>
#include <dolphin/ip.h>
#include "IPPrivate.h"

#include <string.h>

extern BOOL IPAutoConfig(void);

// Rand48: Y = (a * X + c) mod m
#ifndef _MSC_VER
#define A 0x0005deece66dLL
#define C 0xb
#define M (1LL << 48)
#else
#define A 0x0005deece66di64
#define C 0xb
#define M (1i64 << 48)
#endif
static u64 Seed;

static IPInterfaceConf Conf;
static s32             Collision;

//
// Dynamic Configuration of IPv4 Link-Local Addresses [RFC 3927]
//

// Select from 169.254.1.0 to 169.254.254.255
// The first 256 and last 256 addresses in the 169.254/16 network are
// reserved
static void SelectAddr(u8* addr)
{
    u16 suffix;

    do {
        Seed = (A * Seed + C) % M;
        suffix = (u16) (Seed >> 32);
    } while (suffix < 0x0100 || 0xff00 <= suffix);
    if (addr)
    {
        addr[0] = IPLinkLocal[0];
        addr[1] = IPLinkLocal[1];
        addr[2] = (u8) (suffix >> 8);
        addr[3] = (u8) suffix;
    }
}

static void ClaimHander(IPInterfaceConf* conf, s32 result)
{
    if (result == IP_ERR_NONE)
    {
        // Collision not detected
        IPSetAlias(&__IFDefault, conf->addr);
        // Refresh routing table
        IPRefreshRoute();
        // De-claim
        memset(conf->addr, 0, IP_ALEN);
        ARPClaim(conf->interface, conf);
    }
    else
    {
        // Collision detected
        ++Collision;
        // [MUST] Collisions exceeds ten then the host MUST limit the probe rate.
        if (Collision < 10)
        {
            SelectAddr(conf->addr);
            ARPClaim(conf->interface, conf);
        }
        else
        {
            SelectAddr(NULL);
            memset(conf->addr, 0, IP_ALEN);
            ARPClaim(conf->interface, conf);   // De-claim
            if (IP_ADDR_NE(__IFDefault.alias, IPAddrAny))
            {
                // Halt network
                IPSetAlias(&__IFDefault, IPAddrAny);
                // Refresh routing table
                IPRefreshRoute();
            }
        }
    }
}

BOOL IPAutoConfig(void)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    if (IP_ADDR_EQ(IPAddrAny, Conf.addr))   // Not configuring now
    {
        if (Seed == 0)
        {
            memcpy((u8*) &Seed + 2, &__IFDefault.mac, ETH_ALEN);
            OSCreateAlarm(&Conf.alarm);
            Conf.callback = (IFCallback) ClaimHander;
            SelectAddr(Conf.addr);
        }
        else
        {
            // Use the last one once again
            u16 suffix = (u16) (Seed >> 32);
            Conf.addr[0] = IPLinkLocal[0];
            Conf.addr[1] = IPLinkLocal[1];
            Conf.addr[2] = (u8) (suffix >> 8);
            Conf.addr[3] = (u8) suffix;
            ASSERT(!(suffix < 0x0100 || 0xff00 <= suffix));
        }

        Collision = 0;
        ARPClaim(&__IFDefault, &Conf);  // Note ARPClaim() is reentrant.
    }
    OSRestoreInterrupts(enabled);

    return TRUE;
}

void IPAutoStop(void)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    // De-claim
    memset(Conf.addr, 0, IP_ALEN);
    ARPClaim(&__IFDefault, &Conf);
    // Halt network
    IPSetAlias(&__IFDefault, IPAddrAny);
    // Refresh routing table
    IPRefreshRoute();
    OSRestoreInterrupts(enabled);
}
