/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPArp.h

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPArp.h,v $
  Revision 1.3  2006/04/14 22:14:20  mxu
  make prAddr (ip address) 32bits aligned in ARPCache

  Revision 1.2  2006/04/08 01:27:42  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:42:55  mxu
  initial network stack code base

    
    14    2/23/06 11:02 Shiki
    Synchronized with ARP_STATE_*.

    13    2/14/06 10:01 Shiki
    Added ARPReport() and ARPRemove().

    12    2/09/06 18:17 Shiki
    Clean up.

    11    8/20/03 16:32 Shiki
    Declared ARPAdd().

    9     4/28/03 15:56 Shiki
    Declared ARPRefresh().

    8     4/18/03 21:57 Shiki
    Declared ARPRevalidate().

    7     7/29/02 10:24 Shiki
    Implemented Ethernet packet length check code.

    6     4/23/02 15:17 Shiki
    Added ARP_TEST for testing.

    5     4/17/02 19:49 Shiki
    Added datagram and arp field to ARPCache{}.

    4     3/27/02 18:55 Shiki
    Added ARP_MULTICAST.

    3     3/18/02 14:36 Shiki
    Clean up.

    2     3/13/02 18:13 Shiki
    Clean up with ETH_ALEN and IP_ALEN.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __IPARP_H__
#define __IPARP_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ARPCache
{
    IFLink          link;
    OSAlarm         alarm;
    int             rxmit;

    int             state;
    u8              hwAddr[ETH_ALEN];   // Ether specific

#ifdef IOP_OS
    u8              prAddr[IP_ALEN] ATTRIBUTE_ALIGN(4);
                                        // IP v4 specific
#else
    u8              prAddr[IP_ALEN]     // IP v4 specific
#endif // IOP_OS

    IPInterface*    interface;
    IFDatagram      datagram;
    u8              arp[ARP_HLEN + 2 * (ETH_ALEN + IP_ALEN)];

    IFQueue         queue;      // ARP packet save queue [RFC1122]
} ARPCache;

#define ARP_MIN_WAIT        1       // [sec] Minimal interval between two ARP request [RFC1122]
#define ARP_MAX_WAIT        32      // [sec]
#define ARP_TIMEOUT         (20*60) // [sec] Cache entrie timeout [RFC1122, or via DHCP]

// Note ARP cache should not become full.
#define NARP                64      // size of ARP cache

// Return value of ARPLookup()
#define ARP_NOT_FOUND       -1
#define ARP_FOUND           0
#define ARP_LOOPBACK        1
#define ARP_BROADCAST       2
#define ARP_MULTICAST       3

#define ARP_CACHE_FREE      0
#define ARP_CACHE_PENDING   ARP_STATE_INCOMPLETE    // asked
#define ARP_CACHE_RESOLVED  ARP_STATE_REACHABLE     // ok
#define ARP_CACHE_POLLING   ARP_STATE_PROBE         // unicast polling

// Define ARP_TEST for testing
// #define ARP_TEST
#ifdef  ARP_TEST
#undef  ARP_TIMEOUT
#define ARP_TIMEOUT         60      // [sec]
#undef  NARP
#define NARP                2       // size of ARP cache
#endif  // ARP_TEST

void ARPDumpPacket( const ETHHeader* eth, s32 len );

void ARPInit      ( void );
s32  ARPAdd       ( IPInterface* interface, const u8* prAddr, const u8* hwAddr );
s32  ARPRemove    ( IPInterface* interface, const u8* prAddr, const u8* hwAddr );
s32  ARPLookup    ( IPInterface* info, const u8* prAddr, u8* hwAddr );
void ARPHold      ( IPInterface* info, IFDatagram* datagram );
void ARPIn        ( IPInterface* info, ETHHeader* eh, s32 len, u32 flag );
void ARPOut       ( IPInterface* interface,
                    u16 opCode,
                    const u8* dstPrAddr, const u8* dstHwAddr,
                    const u8* srcPrAddr,
                    ARPCache* cache);
void ARPRevalidate( const u8* prAddr );

s32  ARPRefresh   ( void );

void ARPProbe     ( IPInterface* interface, const u8* prAddr );
void ARPGratuitous( IPInterface* interface );
void ARPClaim     ( IPInterface* interface, IPInterfaceConf* conf );

s32  ARPReport    ( IPInterface* interface, void* optval, int* optlen );

#ifdef __cplusplus
}
#endif

#endif // __IPARP_H__
