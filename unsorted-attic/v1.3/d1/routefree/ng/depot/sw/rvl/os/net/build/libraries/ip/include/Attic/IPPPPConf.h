/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:

  Copyright 2002, 2003 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPPPPConf.h,v $
  Revision 1.2  2006/04/08 01:27:42  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:42:55  mxu
  initial network stack code base

    
    12    2/22/06 14:10 Shiki
    Added LCPOptQualityProtocol, LCPOptPFC and LCPOptACFC.

    11    12/15/05 18:42 Shiki
    Added support for LCP Magic-Number option.

    10    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    17    04/07/02 13:36 Ueno_kyu
    Added support for ACCM negotiation.

    16    04/07/01 12:01 Ueno_kyu
    Added support for AOL.

    15    6/29/04 11:03 Shiki
    Moved PPPFcs16() to <dolphin/ip.h>

    14    04/06/24 15:00 Ueno_kyu
    Cleanup.

    13    04/06/24 14:52 Ueno_kyu
    Added definitions for FCS.

    12    6/23/04 14:54 Shiki
    Revised to support Ethernet and other network devices in a uniform way.

    11    04/06/15 15:02 Ueno_kyu
    Added support for modem.

    9     10/23/03 20:31 Shiki
    Added support for PPPoE service name.

    8     10/22/03 14:27 Shiki
    Added support for PPPGetMessage().

    7     7/01/03 14:55 Shiki
    Fixed to set IP_ERR_PPPoE_TIMEOUT upon PPPTimeout (TO-).

    6     7/01/03 14:03 Shiki
    Restructured the PPP layer structure.

    5     10/07/02 10:26 Shiki
    Added const keywords for peerid and passwd.

    4     8/05/02 10:06 Shiki
    Added support for CHAP.

    3     8/01/02 17:05 Shiki
    Added PPPDumpLCP().

    2     8/01/02 10:21 Shiki
    Added PPPConf and PPPIpcpConf; for debugging.

    1     7/31/02 16:21 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef __IPPPPCONF_H__
#define __IPPPPCONF_H__

/* State Transition Table from RFC 1661

      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 Up   |    2     irc,scr/6     -         -         -         -         -         -         -           -
 Down |    -         -         0       tls/1       0         1         1         1         1         tld/1
 Open |  tls/1       1     irc,scr/6     3r        5r        5r        6         7         8           9r
 Close|    0       tlf/0       2         2         4         4     irc,str/4 irc,str/4 irc,str/4 tld,irc,str/4
      |
  TO+ |    -         -         -         -       str/4     str/5     scr/6     scr/6     scr/8         -
  TO- |    -         -         -         -       tlf/2     tlf/3     tlf/3p    tlf/3p    tlf/3p        -
      |
 RCR+ |    -         -       sta/2 irc,scr,sca/8   4         5       sca/8   sca,tlu/9   sca/8   tld,scr,sca/8
 RCR- |    -         -       sta/2 irc,scr,scn/6   4         5       scn/6     scn/7     scn/6   tld,scr,scn/6
 RCA  |    -         -       sta/2     sta/3       4         5       irc/7     scr/6x  irc,tlu/9   tld,scr/6x
 RCN  |    -         -       sta/2     sta/3       4         5     irc,scr/6   scr/6x  irc,scr/8   tld,scr/6x
      |
 RTR  |    -         -       sta/2     sta/3     sta/4     sta/5     sta/6     sta/6     sta/6   tld,zrc,sta/5
 RTA  |    -         -         2         3       tlf/2     tlf/3       6         6         8       tld,scr/6
      |
 RUC  |    -         -       scj/2     scj/3     scj/4     scj/5     scj/6     scj/7     scj/8       scj/9
 RXJ+ |    -         -         2         3         4         5         6         6         8           9
 RXJ- |    -         -       tlf/2     tlf/3     tlf/2     tlf/3     tlf/3     tlf/3     tlf/3   tld,irc,str/5
      |
 RXR  |    -         -         2         3         4         5         6         7         8         ser/9

   Events                                   Actions

   Up   = lower layer is Up                 tlu = This-Layer-Up
   Down = lower layer is Down               tld = This-Layer-Down
   Open = administrative Open               tls = This-Layer-Started
   Close= administrative Close              tlf = This-Layer-Finished

   TO+  = Timeout with counter > 0          irc = Initialize-Restart-Count
   TO-  = Timeout with counter expired      zrc = Zero-Restart-Count

   RCR+ = Receive-Configure-Request (Good)  scr = Send-Configure-Request
   RCR- = Receive-Configure-Request (Bad)
   RCA  = Receive-Configure-Ack             sca = Send-Configure-Ack
   RCN  = Receive-Configure-Nak/Rej         scn = Send-Configure-Nak/Rej

   RTR  = Receive-Terminate-Request         str = Send-Terminate-Request
   RTA  = Receive-Terminate-Ack             sta = Send-Terminate-Ack

   RUC  = Receive-Unknown-Code              scj = Send-Code-Reject
   RXJ+ = Receive-Code-Reject (permitted)
       or Receive-Protocol-Reject
   RXJ- = Receive-Code-Reject (catastrophic)
       or Receive-Protocol-Reject
   RXR  = Receive-Echo-Request              ser = Send-Echo-Reply
       or Receive-Echo-Reply
       or Receive-Discard-Request

   [p]   Passive option; see Stopped state discussion.
   [r]   Restart option; see Open event discussion.
   [x]   Crossed connection; see RCA event discussion.

 */

#include <dolphin/ip.h>

#ifdef __cplusplus
extern "C" {
#endif

//
// LCP/IPCP
//

#define LCP_HLEN            4
#define IPCP_HLEN           4

#define PPP_CHAP_MD5        5   // LCPOptCHAP.algorithm

typedef struct LCPHeader    LCPHeader;
typedef struct LCPHeader    IPCPHeader;
struct LCPHeader
{
    u8  code;
    u8  id;
    u16 len;            // including the code, id, len and data fields
};

typedef struct LCPOpt       LCPOpt;
typedef struct LCPOpt       IPCPOpt;
struct LCPOpt
{
    u8      type;
    u8      len;
    //      data
};

typedef struct LCPOptMRU
{
    u8      type;       // 1 (MaximumReceiveUnit)
    u8      len;        // 4
    u16     mru;        //
} LCPOptMRU;

typedef struct LCPOptPAP
{
    u8      type;       // 3 (AuthenticationProtocol)
    u8      len;        // 4
    u16     auth;       // 0xc023 (PPP_PAP)
} LCPOptPAP;

typedef struct LCPOptCHAP
{
    u8      type;       // 3 (AuthenticationProtocol)
    u8      len;        // 5
    u16     auth;       // 0xc223 (PPP_CHAP)
    u8      algorithm;  // 5 (PPP_CHAP_MD5)
} LCPOptCHAP;

typedef struct LCPOptQualityProtocol
{
    u8      type;               // 4 (QualityProtocol)
    u8      len;                // >= 4
    u16     qualityProtocol;
} LCPOptQualityProtocol;

typedef struct LCPOptPFC
{
    u8      type;               // 7 (ProtocolFieldCompression)
    u8      len;                // 2
} LCPOptPFC;

typedef struct LCPOptACFC
{
    u8      type;               // 8 (AddressandControlFieldCompression)
    u8      len;                // 2
} LCPOptACFC;

//
// PAP
//

#define PAP_HLEN        4

typedef struct PAPHeader
{
    u8  code;
    u8  id;
    u16 len;        // including the code, id, len and data fields
} PAPHeader;

//
// CHAP
//

#define CHAP_HLEN       4

typedef struct CHAPHeader
{
    u8  code;
    u8  id;
    u16 len;        // including the code, id, len and data fields.
} CHAPHeader;


//
// PPPConf{}
//

typedef struct PPPConf      PPPConf;
struct PPPConf
{
    u16          protocol;  // PPP_LCP, PPP_IPCP, etc.

    int          state;
    u8           id;
    u8           idTerminate;
    u8           idReject;
    u8           idEcho;

    int          rxmit;
    int          configure;
    int          terminate;
    int          failure;

    // LCPOpt data: PPP_IPCP requires 18[ADDR,DNS1,DNS2] bytes.
    //              PPP_LCP  requires 15[4(MRU) + 5(PAP/CHAP) + 6(Magic)] bytes
    u8           data[20];
    u16          len;

    OSAlarm      alarm;

    IPInterface* interface;

    int        (*receiveConfigureRequest)(PPPConf* conf, LCPHeader* lcp);
    BOOL       (*receiveConfigureAck)    (PPPConf* conf, LCPHeader* lcp);
    BOOL       (*receiveConfigureNak)    (PPPConf* conf, LCPHeader* lcp);
    BOOL       (*receiveConfigureReject) (PPPConf* conf, LCPHeader* lcp);

    BOOL       (*up)      (PPPConf* conf);
    BOOL       (*down)    (PPPConf* conf);
    BOOL       (*started) (PPPConf* conf);
    BOOL       (*finished)(PPPConf* conf);

    void       (*callback)(PPPConf* conf);

    IFLink       link;      // link for IPInterface.ppp queue

    // LCP specific
    u16          mru;
    u16          auth;
    u32          magic;
    u32          magicPeer;
    u32          accm;
    const char*  dial;
    s32          dialMode;

    // IPCP specific
    u32          remote;    // remote IP address
};

typedef struct PPPAuth
{
    u8           peerIdLen;
    u8           passwordLen;
    u8           messageLen;
    char         peerId[256];
    char         password[256];
    char         message[256];
} PPPAuth;

// ReceiveConfigureRequest() return values
#define PPP_RCR_ACCEPT      0
#define PPP_RCR_REJECT      -1
#define PPP_RCR_NACK        -2
#define PPP_RCR_INVALID     -3

// AsyncronousControlCharacterMap
#define PPP_ACCM_DEFAULT     0xffffffff
#define PPP_ACCM_ACCEPTABLE  0x00000000


void PPPSetState              ( PPPConf* conf, int state );
int  PPPGetState              ( PPPConf* conf );

BOOL PPPLayerUp               ( PPPConf* conf );
BOOL PPPLayerDown             ( PPPConf* conf );
BOOL PPPLayerStarted          ( PPPConf* conf );
BOOL PPPLayerFinished         ( PPPConf* conf );
void PPPInitializeRestartCount( PPPConf* conf );
void PPPZeroRestartCount      ( PPPConf* conf );

BOOL PPPInit ( IPInterface* interface, PPPConf* lcp, PPPConf* ipcp,
               const char* peerid, const char* passwd,
               const char* dial, s32 dialMode, u8 ispCode );

void PPPOpen   ( PPPConf* conf );
void PPPUp     ( PPPConf* conf );
void PPPDown   ( PPPConf* conf );
void PPPClose  ( PPPConf* conf );
void PPPTimeout( OSAlarm* alarm, OSContext* context );

BOOL PPPInitLCP  ( PPPConf* conf, IPInterface* interface );
void PPPInitIPCP ( PPPConf* ipcp, IPInterface* interface );

u16  PPPDeleteOpt( u8* data, u16 len, LCPOpt* opt );
u16  PPPInsertOpt( u8* data, u16 len, LCPOpt* at, LCPOpt* opt );
void PPPDumpLCP  ( LCPHeader* lcp );

// PAP
void PAPOpen    ( PPPConf* conf );
void PAPUp      ( PPPConf* conf );
void PAPDown    ( PPPConf* conf );
void PAPClose   ( PPPConf* conf );
BOOL PAPTimeout ( PPPConf* conf );
void PAPIn      ( PPPConf* conf, PAPHeader* pap, s32 len, u32 flag );
void PAPInit    ( PPPConf* conf, IPInterface* interface );

// CHAP
void CHAPOpen   ( PPPConf* conf );
void CHAPUp     ( PPPConf* conf );
void CHAPDown   ( PPPConf* conf );
void CHAPClose  ( PPPConf* conf );
BOOL CHAPTimeout( PPPConf* conf );
void CHAPIn     ( PPPConf* conf, CHAPHeader* chap, s32 len, u32 flag );
void CHAPInit   ( PPPConf* conf, IPInterface* interface );

// PPPoE
void PPPoEInit     ( IPInterface* interface, const char* serviceName );
BOOL PPPoEOpen     ( IPInterface* interface );
BOOL PPPoETerminate( IPInterface* interface );

// PPP Stack
extern PPPConf   PPPLcpConf;
extern PPPConf   PPPAuthConf;
extern PPPConf   PPPIpcpConf;

extern PPPAuth   __PPPAuth;

#ifdef __cplusplus
}
#endif

#endif // __IPPPPCONF_H__
