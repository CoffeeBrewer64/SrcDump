/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPPrivate.h

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPPrivate.h,v $
  Revision 1.3  2006/04/11 01:41:29  mxu
  update to Nintendo's April 05 release

  Revision 1.2  2006/04/08 01:27:42  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:42:55  mxu
  initial network stack code base

    
    50    3/30/06 18:15 Shiki
    Added more DNS unit test functions.

    49    06/03/20 17:34 Ueno_kyu
    Added DNS unit test functions.

    48    2/27/06 15:04 Shiki
    Added IP_ROUTING_NUMBER.
    Added TCPReportTimeWaitNumber().
    Declared UDPNumber and TCPNumber.

    47    2/23/06 15:10 Shiki
    Added SOReportResolverTable().

    46    2/23/06 13:59 Shiki
    Added IPReportAddrTable().

    45    2/20/06 18:49 Shiki
    Added IPGetReassembleMaxSize().

    44    2/15/06 14:47 Shiki
    Added TCPReportTimeWait.

    43    2/10/06 17:48 Shiki
    Removed TCPSourceQuench().

    42    2/10/06 13:57 Shiki
    Revised TCPNotify().

    41    1/06/06 17:44 Shiki
    Revised ICMP packet buffer management code.

    40    06/01/06 14:01 Ueno_kyu
    Cleanup.

    39    06/01/06 13:26 Ueno_kyu
    Added ICMPAllocDatagram() and ICMPReleaseDatagramBuffer() to save ICMP
    datagram.

    38    12/22/05 14:31 Shiki
    Added IPAnvl.

    37    12/22/05 11:02 Shiki
    Modified TCPTestTimeWait() interface.

    36    12/22/05 9:31 Shiki
    Fixed TIME-WAIT TCB abort/RST operations.

    35    12/21/05 17:26 Shiki
    Added TCPDeleteTimeWaitInfo().

    34    12/13/05 19:51 Shiki
    Modified the return value type of IPSetOption().

    33    12/13/05 18:45 Shiki
    Added IP4SelectSourceAddress() and IPIsLinkLocalAddr().

    32    12/08/05 20:26 Shiki
    Removed TCPIsInFastRecovery().

    31    12/08/05 17:53 Shiki
    Added TCPIsInFastRecovery().

    30    11/30/05 11:36 Shiki
    Revised to maintain cWin in units of bytes.

    29    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    35    04/09/28 16:46 Ueno_kyu
    Added ICMPGetObj().

    34    04/09/22 10:27 Ueno_kyu
    Added  ICMPReset().

    33    6/23/04 14:54 Shiki
    Revised to support Ethernet and other network devices in a uniform way.

    32    04/06/21 13:49 Ueno_kyu
    Modified MDMIFInit() to take a country code as an argument.
    Added MDMLinkInit().

    31    04/06/17 9:07 Ueno_kyu
    Added mdm.h.
    Cleanup.

    30    04/06/15 15:02 Ueno_kyu
    Added support for modem.

    29    6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    27    2/25/04 14:48 Shiki
    Added support for delayed ACK.

    26    11/14/03 13:10 Shiki
    Added support for SOGetAddrInfo(), SOFreeAddrInfo(), and
    SOGetNameInfo().

    25    10/29/03 21:52 Shiki
    Added support for fragmenting outgoing datagrams.
    Declared IFInitDatagram().

    24    10/20/03 15:01 Shiki
    Added support for SO_SO_SNDLOWAT and SO_SO_RCVLOWAT.

    23    8/21/03 20:59 Shiki
    Added support for SACK/FACK.

    22    4/01/03 10:19 Shiki
    Modified IP multicast logic so that a socket receives multicast
    datagrams only from the joined group.

    21    3/27/03 17:43 Shiki
    Added support for multicast.

    20    3/25/03 13:50 Shiki
    Declared __TCPPoll().

    19    1/22/03 18:09 Shiki
    Added SOPoll() interface.

    18    11/11/02 21:06 Shiki
    Added TCPPeekOut().

    17    10/07/02 10:26 Shiki
    Declared ETHIn() and ETHOut().

    16    9/19/02 10:58 Shiki
    Added IPIsLocalAddr().

    15    7/31/02 16:13 Shiki
    Added support for PPP.

    14    7/29/02 10:24 Shiki
    Implemented Ethernet packet length check code.

    13    7/19/02 16:12 Shiki
    Added support for non-blocking I/O.

    12    4/26/02 17:14 Shiki
    Added UDPOnReset and TCPOnReset.

    11    4/12/02 13:10 Shiki
    Implemented initial sequence number randomizing for TCPIsn()

    10    4/08/02 13:27 Shiki
    Added IPGetSockOpt() and IPSetSockOpt().

    9     4/05/02 14:08 Shiki
    Refined using 'const'.

    8     4/04/02 17:13 Shiki
    Added ICMPSendError().

    7     3/28/02 14:27 Shiki
    Clean up.

    6     3/27/02 17:43 Shiki
    Implemented IPProcessSourceRoute().

    5     3/27/02 16:45 Shiki
    Added UDPNotify(), TCPNotify() and TCPSourceQuench().

    4     3/25/02 17:09 Shiki
    Added IP option functions.

    3     3/18/02 20:38 Shiki
    Added __IPIsMember().

    2     3/13/02 18:30 Shiki
    Revised TCPSend() so it can directly transfer user data from the user
    space to the link layer.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __IPPRIVATE_H__
#define __IPPRIVATE_H__

#include <dolphin/ip.h>
#include <private/mdm.h>

#ifdef __cplusplus
extern "C" {
#endif

OSTime __OSGetSystemTime   ( void );

#define MIN(a, b)   (((a) < (b)) ? (a) : (b))
#define MAX(a, b)   (((a) > (b)) ? (a) : (b))

// Return value of ARPLookup()
#define ARP_NOT_FOUND   -1
#define ARP_FOUND       0
#define ARP_LOOPBACK    1
#define ARP_BROADCAST   2

//
// Interface
//

#define IP_IF_RECVBUFSIZE   (ETH_HLEN + 1500 + 4 /* CRC */)
#define IP_IF_SENDBUFSIZE   ((1500 + 4 /* HDLC & PPP Frames */ + 2 /* CRC */) * 2 + 2 /* 0x7E x 2 */)
#define IP_IF_SENDHEAPSIZE  (16 * 1024)

// interface->sending will be IP_IF_CANCELED if it has been canceled.
#define IP_DG_CANCELED      ((IFDatagram*) 0xffffffff)

void IFInitDatagram(IFDatagram* datagram, u16 type, int nVec);

//
// Ether
//
void IFSendRaw(u16 type, u8* hwAddr,
               IFVec* vec, s32 nVec,
               /* void* data, s32 len, */
               IFCallback callback, void* param);
// for IP
void IFSendAsync(u8* dst, IFVec* vec, s32 nVec,
                 IFCallback callback, void* param);

BOOL ETHInitInterface( IPInterface* interface, s32 type );
void ETHIn           ( IPInterface* interface, ETHHeader* eh, s32 len );
void ETHOut          ( IPInterface* interface, IFDatagram* datagram );


//
// Modem
//
BOOL MDMInitInterface( IPInterface* interface, s32 type );


//
// PPPoE
//
void PPPIn  ( IPInterface* interface, u8* ppp,       s32 len, u32 flag );
void PPPoEIn( IPInterface* interface, ETHHeader* eh, s32 len, u32 flag );


//
// IP
//

void* IPGetLocalSockAddr(IPInfo* info);
void* IPGetRemoteSockAddr(IPInfo* info);

u16     IPGetAnonPort( IFQueue* queue, u16* last );

IPInfo* IP4LookupInfo( IFQueue* queue,
                       const u8* srcAddr, const u8* dstAddr, u16 src, u16 dst,
                       u32 flag );
s32     IP4Bind      ( IFQueue* queue, IPInfo* info, const IPSocket* socket, BOOL reuse );
s32     IP4Connect   ( IFQueue* queue, IPInfo* info, const IPSocket* socket, u16* last );

void IP4SelectSourceAddress(IPInterface* interface, const u8* dst, u8* src);

void IPReceiveSocket ( IPSocket* sockAddr, u8* addr, u16 port );

s32 IPGetRemoteSocket( IPInfo* info, void* sockAddr );
s32 IPGetLocalSocket ( IPInfo* info, void* sockAddr );

s32 IPGetSockOpt(IPInfo* info, int level, int optname,
                 void* optval, int* optlen);
s32 IPSetSockOpt(IPInfo* info, int level, int optname,
                 const void* optval, int optlen);

s32 IPClose(IPInfo* info);

s32 IPSetOption(IPInfo* info, u8 ttl, u8 tos);

s32  IPOut   ( IFDatagram* datagram );
void IPCancel( IFDatagram* datagram );
void IPIn    ( IPInterface* info, IPHeader* ip, s32 len, u32 flag );
BOOL IPRedirect( const u8* dst, const u8* gateway, const u8* router );

u16 IPCheckSum(IPHeader* ip);
u16 IP4CheckSum(u8 proto, IFVec* vec, int nVec);

BOOL __IPIsMember(IFQueue* queue, IPInfo* info);

void __IPWakeupPollingThreads(void);

// IPFrag.c
IPHeader* IPReassemble(IPInterface* interface, IPHeader* ip, u32 flag);
int       IPFragment(IFDatagram* datagram, u8* ptr, BOOL* discard);
s32       IPGetReassembleMaxSize(void);

//
// Routing
//

#define IP_ROUTING_NUMBER   32  // Note at least eight entries are necessary

IPInterface* IPGetRoute( const u8* addr, u8* dst );

s32  IPReportAddrTable(IPInterface* interface, void* optval, int* optlen);
BOOL IPIsBroadcastAddr(IPInterface* interface, const u8* addr);
BOOL IPIsLoopbackAddr (IPInterface* interface, const u8* addr);
BOOL IPIsLinkLocalAddr(IPInterface* interface, const u8* addr);
BOOL IPIsLocalAddr    (IPInterface* interface, const u8* addr);
//
// IP option
//
s32 IPSetSourceRoute(u8* opt, u8 type, const u8* addr, s32 addrlen);
s32 IPGetSourceRoute(u8* opt, u8* type, u8* addr, s32 addrlen);
s32 IPSetRecordRoute(u8* opt, s32 addrlen);
s32 IPGetRecordRoute(u8* opt, u8* addr, s32 addrlen);

s32 IPProcessSourceRoute( IPHeader* ip );
s32 IPReverseSourceRoute( IPHeader* ip );
s32 IPUpdateRecordRoute ( IPHeader* ip, u8* addr );

void IPSwapAddr(u8* a, u8* b);

//
// ICMP
//
void ICMPIn(IPInterface* interface, IPHeader* ip, u32 flag);
s32  ICMPSendError( ICMPHeader* icmp, IPInterface* interface, IPHeader* ip, u32 flag );
BOOL ICMPReset(BOOL final);
ICMPObj* ICMPGetObj(ICMPInfo* info);
IFDatagram* ICMPAllocDatagram(IPInterface* interface, s32 len);
void ICMPFreeDatagram(IFDatagram* datagram);

//
// UDP
//
void UDP4In         ( IPInterface* interface, IPHeader* ip, UDPHeader* udp, u32 flag );
void UDPNotify      ( const IPHeader* ip, s32 err );
BOOL UDPOnReset     ( BOOL final );
short __UDPPoll     ( UDPInfo* info );
UDPObj* UDPGetObj   ( UDPInfo* info );
BOOL UDPAbort       ( UDPInfo* info, s32 rc );

//
// TCP
//
void TCP4In         ( IPInterface* interface, IPHeader* ip, TCPHeader* tcp, u32 flag );
void TCPNotify      ( const IPHeader* ip, s32 err, BOOL abort );
BOOL TCPOnReset     ( BOOL final );
short __TCPPoll     ( TCPInfo* info );
TCPObj* TCPGetObj   ( TCPInfo* info );

s32 TCPIsn( IPInfo* info );

void TCPRespond(IPInterface* interface, TCPObj* info,
                const void* ip, const TCPHeader* tcp,
                s32 seq, s32 ack, u16 flag, u16 win);
void TCP4Respond(IPInterface* interface, TCPObj* info,
                 const u8* dstAddr, u16 dst,
                 const u8* srcAddr, u16 src,
                 s32 seq, s32 ack, u16 flag, u16 win);

BOOL TCPAbort(TCPObj* info);
BOOL TCPAbortAs(TCPObj* info, s32 nextState);

s32 TCPSendIn(TCPObj* info, BOOL nonblock);
s32 TCPPeekOut(TCPObj* info, void* ptr, s32 len, BOOL peek, BOOL* urgent);
s32 TCPRecvOut(TCPObj* info, BOOL* urgent);

s32 TCPGetSegmentLength(TCPHeader* tcp, s32 plen);

void TCPDelayedAckHandler(OSAlarm* alarm, OSContext* context);

void TCPOutput(TCPObj* info, u16 flag);
TCPSackHole* TCPSackOutput(const TCPObj* info);

int TCPMakeOption(TCPHeader* tcp, TCPObj* info, u16 flag);

// TCP User

// TCP Timer
void TCPStartRxmitTimer   ( TCPObj* info );
void TCPStopRxmitTimer    ( TCPObj* info, TCPHeader* tcp );
void TCPCancelRxmitTimer  ( TCPObj* info );
void TCPInitRtt           ( TCPObj* info );
void TCPUpdateRtt         ( TCPObj* info, OSTime rtt );
void TCPCutThresh         ( TCPObj* info );

// TCP Time-wait
BOOL TCP4LookupTimeWaitInfo (const u8* src, u16 srcPort, const u8* dst, u16 dstPort);
s32  TCPTestTimeWait        ( IPInterface* interface, void* ip, TCPHeader* tcp, s32 len );
void TCPStartTimeWait       ( IPInterface* interface, TCPObj* info, void* ip, TCPHeader* tcp );
void TCPDeleteTimeWaitInfo  ( TCPInfo* tcp );
s32  TCPReportTimeWait      ( IPInterface* interface, void* optval, int* optlen );
int  TCPReportTimeWaitNumber( IPInterface* interface );

// TCP unit test functions
BOOL __TCPTrimSegment(TCPInfo* info, IPHeader* ip, u16* flag);
s32  __TCPCalcSendSize(TCPInfo* info, s32 effSendMss, u16* pflag);

// Socket
void* SOAlloc(u32 name, s32 size);
void  SOFree (u32 name, void* ptr, s32 size);
s32   SOReportResolverTable(IPInterface* interface, void* optval, int* optlen);

// Misc.
u64 IPRand48(IPInterface* interface);
OSTime IPRandTime(IPInterface* interface, OSTime min, OSTime max);

// DNS unit test functions
u8*   __DNSSkipName ( const u8* ptr, const u8* end );
char* __DNSCopyName ( const DNSHeader* dns, const u8* end, const u8* ptr,
                      char* name, s32 namelen );
u8*   __DNSDupName  ( const DNSHeader* dns, const u8* end, const u8* ptr, u8* opt );
BOOL  __DNSCmpName  ( const DNSHeader* dns0, const u8* end0, const u8* name0,
                      const DNSHeader* dns1, const u8* end1, const u8* name1 );
BOOL  __DNSCompName ( const DNSHeader* dns, const u8* end, u8* name1, u8* name2 );
u8*   __DNSCheckName( const DNSHeader* dns, const u8* end, const u8* ptr );

// Library global variables

extern IPInterface __IFDefault;
extern IFDatagram* __IFCurrent;
extern char*       TCPStateNames[];
extern IFQueue     TCPInfoQueue;
extern IFQueue     UDPInfoQueue;
extern u32         IPAnvl;

extern int         UDPNumber;
extern int         TCPNumber;

#include "IPArp.h"

#ifdef __cplusplus
}
#endif

#endif // __IPPRIVATE_H__
