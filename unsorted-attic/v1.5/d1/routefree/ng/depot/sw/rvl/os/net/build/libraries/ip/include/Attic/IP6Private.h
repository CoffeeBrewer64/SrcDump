/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IP6Private.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IP6Private.h,v $
  Revision 1.4  2006/04/19 01:16:14  mxu
  update the value of OS_TIME_INFINITE based on u32

  Revision 1.3  2006/04/11 01:41:29  mxu
  update to Nintendo's April 05 release

  Revision 1.2  2006/04/08 01:27:42  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:42:55  mxu
  initial network stack code base

    
    36    4/03/06 19:20 Shiki
    Modified IP6GetPathMTU() not to increase PMTU less than 1 min after the
    previous attempted increase.

    35    3/02/06 9:48 Shiki
    Modified ICMP6In() to check the router alert value.

    34    2/28/06 14:14 Shiki
    Added lastTooBig to IP6Entry{} again.
    Added ND_FLAG_REDIRECT.
    Removed IP6ReportPrefixTable().
    Modified IP6Claim() prototype.

    33    2/28/06 9:06 Shiki
    Added IP6ReportEntryTable().
    Modified IP6Entry.

    32    2/27/06 15:05 Shiki
    Added TCP6ReportTimeWaitNumber().
    Declared UDP6Number and TCP6Number.

    31    2/23/06 11:17 Shiki
    Fixed comments.

    30    2/23/06 11:11 Shiki
    Synchronized with IP6_PREFIX_STATE_*.

    29    2/15/06 14:47 Shiki
    Added TCP6ReportTimeWait.

    28    2/14/06 10:01 Shiki
    Added IP6ReportPrefixTable().

    27    2/09/06 17:31 Shiki
    Revised ICMPv6 error handling code.

    26    2/06/06 15:07 Shiki
    Added IP6Shuffle().

    25    2/01/06 16:25 Shiki
    Added full support of IPv6 PMTU discovery.
    Supported ND_STATE_NON_LISTENER state.

    24    1/26/06 18:44 Shiki
    Restored IP6Neighbor for backward compatibility.

    23    1/26/06 18:41 Shiki
    Renamed IP6Neighbor to IP6Entry.

    22    1/26/06 10:27 Shiki
    Added IP6GetNextNeighborWithDestination().

    21    1/25/06 17:19 Shiki
    Fixed to revoke every neighbor cache associated to a prefix which is
    being invalidated.

    20    1/25/06 15:54 Shiki
    Integrated IP6Destination{} and IP6Neighbor{}.

    19    1/24/06 18:43 Shiki
    Renamed IP6Route to IP6Destination as it was misleading.

    18    1/24/06 10:29 Shiki
    Clean up.

    17    1/20/06 16:01 Shiki
    Fixed IP6LeaveLocalGroup() prototype.

    16    1/20/06 10:34 Shiki
    Added IP6SwitchToHost() and IP6SwitchToRouter().

    15    1/19/06 18:38 Shiki
    Fixed IP6Claim() to get neighbor by using IP6GetNeighbor() not
    IP6GetNextNeighbor().

    14    1/19/06 18:25 Shiki
    Renamed IP6GetNeighbor() to IP6GetNextNeighbor().

    13    1/19/06 17:46 Shiki
    Fixed to send MLD listener done messages during cleanup and before
    reset.

    12    1/18/06 18:19 Shiki
    Revised the reference count management of IP6Neighbor{}.

    11    1/13/06 9:46 Shiki
    Added ND_STATE_INIT state.

    10    1/11/06 17:01 Shiki
    Fixed to clean up MLDTable[] from SOCleanup().

    8     10/12/04 10:36 Shiki
    Added IP6Cleanup().

    7     04/09/28 16:45 Ueno_kyu
    Revised IPv6 ping program.

    6     04/09/27 17:48 Ueno_kyu
    Added IP6EnumAddresses().

    5     04/09/24 11:20 Ueno_kyu
    Added support for IPv6 ping program.

    4     04/09/10 15:34 Ueno_kyu
    Modified IP6Neighbor{} to keep Router Lifetime.

    3     04/08/31 19:24 Ueno_kyu
    Added support for IPv6 fragmentation and reassembly.

    2     6/21/04 12:03 Shiki
    Revised to support AAAA.

    1     6/09/04 15:55 Shiki
    Pilot implementation
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __IP6PRIVATE_H__
#define __IP6PRIVATE_H__

#ifdef IP_INET6

#ifdef IOP_OS
#include <dolphin/ip/IP6.h>
#else
#include <dolphin/ip/ip6.h>
#endif // IOP_OS

#ifdef __cplusplus
extern "C" {
#endif

// IP6Entry is used as Neighbor Cache entry, as Destination Cache entry,
// as Default Router List entry, and as Prefix List entry described in
// RFC 2461.
typedef struct IP6Entry IP6Entry;
struct IP6Entry
{
    IFLink          link;

    SOIn6Addr       addr;               // IPv6 address
    u8              prefixLen;
    u8              linkAddr[ETH_ALEN]; // Link-layer address
    IFQueue         queue;              // Any queued packets waiting
                                        // for address resolution to complete

    IP6Entry*       network;
    IFLink          linkNetwork;        // for queueNetwork

    int             state;              // Reachability state
    u32             flags;
    int             count;              // Number of unanswered probes
    OSAlarm         alarm;

    OSTime          lastUpdated;
    OSTime          routerLifetime;     // valid if isRouter is TRUE
    OSTime          validTime;          // for ND_STATE_TENTATIVE to ND_STATE_DEPRECATED and ND_STATE_PREFIX
    OSTime          preferredTime;      // for ND_STATE_TENTATIVE to ND_STATE_DEPRECATED and ND_STATE_PREFIX

    IPInterface*    interface;

    int             ref;                // Reference count
    IFQueue         queueNext;          // list of IPInfo{} that uses IP6Entry as next-hop
    IFQueue         queueFrom;          // list of IPInfo{} that uses IP6Entry as sock name
    IFQueue         queueTo;            // list of IPInfo{} that uses IP6Entry as peer name
    IFQueue         queueNetwork;       // list of IP6Entry{} which is a member of this network

    // PMTU related
    s32             mtu;
    OSTime          lastTooBig;
};

//
// ND_STATE_*: State for IP6Entry{}. A single IP6Entry{} structure is used
// for various purpose in the GameCube IPv6 implementation including neighbor
// discovery, address configuration, and listener discovery.
//

// An ND_STATE_INVALID entry is not used for any purpose.
#define ND_STATE_INVALID                0

// The following six states are used for "Neighbor Cache". [RFC 2461]
// Unless an entry is not for a router, it can be reused provided that ref is zero.
#define ND_STATE_INIT                   IP6_PREFIX_STATE_INIT
#define ND_STATE_INCOMPLETE             IP6_PREFIX_STATE_INCOMPLETE
#define ND_STATE_REACHABLE              IP6_PREFIX_STATE_REACHABLE
#define ND_STATE_STALE                  IP6_PREFIX_STATE_STALE
#define ND_STATE_DELAY                  IP6_PREFIX_STATE_DELAY
#define ND_STATE_PROBE                  IP6_PREFIX_STATE_PROBE

// The following three states are used for address configuration. [RFC 2462]
// Entries must not be reused until the state moves back to ND_STATE_INVALID.
#define ND_STATE_TENTATIVE              IP6_PREFIX_STATE_TENTATIVE
#define ND_STATE_PREFERRED              IP6_PREFIX_STATE_PREFERRED
#define ND_STATE_DEPRECATED             IP6_PREFIX_STATE_DEPRECATED

// The following three states are used for "Multicast Listener". [RFC 2710]
// Entries must not be reused until the state moves back to ND_STATE_INVALID.
#define ND_STATE_NON_LISTENER           IP6_PREFIX_STATE_NON_LISTENER
#define ND_STATE_DELAYING_LISTENER      IP6_PREFIX_STATE_DELAYING_LISTENER
#define ND_STATE_IDLE_LISTENER          IP6_PREFIX_STATE_IDLE_LISTENER

// The following state is used for "Destination Cache".  [RFC 2461]
#define ND_STATE_DESTINATION            IP6_PREFIX_STATE_DESTINATION

// The following state is used for on-link "Prefix List".  [RFC 2461]
#define ND_STATE_PREFIX                 IP6_PREFIX_STATE_PREFIX

#define ND_FLAG_IS_ROUTER               IP6_PREFIX_FLAG_IS_ROUTER
#define ND_FLAG_LAST_HOST               IP6_PREFIX_FLAG_LAST_HOST
#define ND_FLAG_STATIC                  IP6_PREFIX_FLAG_STATIC
#define ND_FLAG_ANYCAST                 IP6_PREFIX_FLAG_ANYCAST
#define ND_FLAG_ON_LINK                 IP6_PREFIX_FLAG_ON_LINK
#define ND_FLAG_AUTONOMOUS              IP6_PREFIX_FLAG_AUTONOMOUS
#define ND_FLAG_REDIRECT                IP6_PREFIX_FLAG_REDIRECT

#define MAX_NEIGHBORS                   128

// Router constants
#define MAX_INITIAL_RTR_ADVERT_INTERVAL 16      // [sec]
#define MAX_INITIAL_RTR_ADVERTISEMENTS  3       // transmissions
#define MAX_FINAL_RTR_ADVERTISEMENTS    3       // transmissions
#define MIN_DELAY_BETWEEN_RAS           3       // [sec]
#define MAX_RA_DELAY_TIME               500     // [msec]

// Host constants
#define MAX_RTR_SOLICITATION_DELAY      1       // [sec]
#define RTR_SOLICITATION_INTERVAL       4       // [sec]
#define MAX_RTR_SOLICITATIONS           3       // transmissions

// Node constants
#define MAX_MULTICAST_SOLICIT           3       // transmissions
#define MAX_UNICAST_SOLICIT             3       // transmissions
#define MAX_ANYCAST_DELAY_TIME          1       // [sec]
#define MAX_NEIGHBOR_ADVERTISEMENT      3       // transmissions
#define REACHABLE_TIME                  30000   // [msec]
#define RETRANS_TIMER                   1000    // [msec]
#define DELAY_FIRST_PROBE_TIME          5       // [sec]
#define MIN_RANDOM_FACTOR(t)            ((t) / 2)       // 0.5
#define MAX_RANDOM_FACTOR(t)            (3 * (t) / 2)   // 1.5

#ifndef OS_TIME_INFINITE

#ifdef IOP_OS
#define OS_TIME_INFINITE                2147483647
#else
#define OS_TIME_INFINITE                9223372036854775807LL
#endif // IOP_OS

#endif  // OS_TIME_INFINITE


// IP6.c
void IP6In( IPInterface* info, IP6Hdr* ip, s32 len, u32 flag );
s32  IP6Out( IPInterface* interface, IFDatagram* datagram, IP6Entry* neighbor );
void IP6Cancel( IFDatagram* datagram );

SOIn6Addr* IP6GetSolicited(const SOIn6Addr* addr, SOIn6Addr* solicited);
BOOL IP6IsSolicited(const SOIn6Addr* addr);

IPInfo* IP6LookupInfo(IFQueue* queue,
                      const SOIn6Addr* src, const SOIn6Addr* dst,
                      u16 srcPort, u16 dstPort,
                      u32 flag);

void IP6ReceiveSocket(SOSockAddrIn6* sockAddr6, SOIn6Addr* addr, u16 port);

u16 IP6CheckSum(u8 proto, IFVec* vec, int nVec, void* payload, s32 plen);

IP6Entry* IP6GetNextHop(IPInfo* info, const SOIn6Addr* addr, IP6Entry** destination);

void IP6SetNextHop(IPInfo* info, IP6Entry* entry);
void IP6SetSource(IPInfo* info, IP6Entry* entry);
void IP6SetDestination(IPInfo* info, IP6Entry* entry);

IP6Entry* IP6SelectSourceAddress(IPInterface* interface, const SOIn6Addr* dst, SOIn6Addr* src);

s32 IP6GetSockOpt(IPInfo* info, int level, int optname,
                  void* optval, int* optlen);
s32 IP6SetSockOpt(IPInfo* info, int level, int optname,
                  const void* optval, int optlen);

IPInfo* IP6LookupInfo( IFQueue* queue,
                       const SOIn6Addr* srcAddr, const SOIn6Addr* dstAddr,
                       u16 src, u16 dst,
                       u32 flag);
s32     IP6Bind      ( IFQueue* queue, IPInfo* info, const SOSockAddrIn6* socket, BOOL reuse );
s32     IP6Connect   ( IFQueue* queue, IPInfo* info, const SOSockAddrIn6* socket, u16* last );

// IP6Icmp.c
void ICMP6In(IPInterface* interface, IP6Hdr* ip6, ICMP6Hdr* icmp6, s32 len, u32 flag, int routerAlert);
void ICMP6Out(IP6Entry* neighbor, u8 type, const SOIn6Addr* dst);
IP6Entry* IP6GetNeighbor(IPInterface* interface, const SOIn6Addr* addr);
IP6Entry* IP6GetNextNeighbor(IPInterface* interface, const SOIn6Addr* addr, IP6Entry** dst);

void IP6PutNeighbor   (IP6Entry* neighbor);
void IP6RefNeighbor   (IP6Entry* neighbor);
void IP6SwitchToHost  (IP6Entry* neighbor);
void IP6SwitchToRouter(IP6Entry* neighbor, OSTime routerLifetime);
void IP6Shuffle       (IP6Entry* router);

IP6Entry* IP6SearchNeighbor(const SOIn6Addr* addr);

void IP6SetNeighborState(IP6Entry* neighbor, int state);
void IP6NeighborTimeout(OSAlarm* alarm, OSContext* context);

void IP6Startup(IPInterface* interface);
void IP6Cleanup(IPInterface* interface);

void ICMP6SendError(IPInterface* interface, u8 type, u8 code, IP6Hdr* org, u32 flag, u32 pointer);

void NDHold(IP6Entry* neighbor, IFDatagram* datagram);

s32  ICMP6Ping(ICMP6Info* info, const void* data, s32 len,
               const void* remote, ICMPCallback callback, s32* result);

void IP6EnumAddresses ( IPInterface* interface,
                        BOOL (*callback)(int af, const void* addr) );

s32 IP6GetPathMTU(IP6Entry* dest, s32 est);

s32 IP6ReportEntryTable(IPInterface* interface, int level, int optname, void* optval, int* optlen);

extern IFQueue ICMPInfoQueue;

// IP6Mld.c
void MLDDoListenerQuery(IPInterface* interface, ICMP6MldHder* mld);
void MLDDoListenerReport(IPInterface* interface, ICMP6MldHder* mld);
s32 IP6MulticastLookup(IPInterface* interface, const SOIn6Addr* groupAddr);
s32 IP6MulticastJoin(IPInterface* interface, const SOIn6Addr* groupAddr);
s32 IP6MulticastLeave(IPInterface* interface, const SOIn6Addr* groupAddr);
BOOL IP6JoinLocalGroup(IPInterface* interface, const SOIn6Addr* groupAddr);
BOOL IP6LeaveLocalGroup(IPInterface* interface, const SOIn6Addr* groupAddr);
BOOL MLDOnReset(BOOL final);

// IP6Zero.c
s32 IP6Claim(IPInterface* interface, const SOIn6Addr* addr,
             u32 validTime, u32 preferredTime, u32 flags);
OSTime NDTime(OSTime now, u32 sec);

// IPUdp.c
void UDP6In(IPInterface* interface, IP6Hdr* ip6, UDPHeader* udp, s32 len, u32 flag);
void UDP6Notify     ( const IP6Hdr* ip6, const UDPHeader* udp, s32 err);

extern IFQueue NDCache; // list of IP6Entry

// IPTcp.c
void TCP6In(IPInterface* interface, IP6Hdr* ip6, TCPHeader* tcp, s32 len, u32 flag);
void TCP6Notify(const IP6Hdr* ip6, const TCPHeader* tcp, s32 err, BOOL abort);
void TCP6Respond(IPInterface* interface, TCPObj* info,
                 const SOIn6Addr* dstAddr, u16 dst,
                 const SOIn6Addr* srcAddr, u16 src,
                 s32 seq, s32 ack, u16 flag, u16 win);
BOOL TCP6LookupTimeWaitInfo(const SOIn6Addr* src, u16 srcPort, const SOIn6Addr* dst, u16 dstPort);
s32  TCP6ReportTimeWait(IPInterface* interface, void* optval, int* optlen);
int  TCP6ReportTimeWaitNumber( IPInterface* interface );

// IP6Frag.c
s32       IP6SetReassemblyBuffer ( void* buffer, s32 len, s32 mtu );
IP6Hdr*   IP6Reassemble          ( IPInterface* interface, IP6Hdr* frag, IP6Frag* fragHdr, u32 flag );
int       IP6Fragment            ( IFDatagram* datagram, u8* ptr, BOOL* discard );

// Library global variables

extern IP6Entry* MLDTabel[IGMP_MAXGROUP];
extern int       MLDCount;

extern int       UDP6Number;
extern int       TCP6Number;

#ifdef __cplusplus
}
#endif

#endif  // IP_INET6

#endif  // __IP6PRIVATE_H__
