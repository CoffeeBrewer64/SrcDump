/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API -- PPP [RFC 1661]
  File:     IPPPP.c

  Copyright 2002-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPPPP.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    21    12/19/05 13:45 Shiki
    Added IPCPIn().

    20    12/16/05 13:53 Shiki
    Fixed SendProtocolReject().

    19    12/16/05 13:21 Shiki
    Fixed ReceiveProtocolReject() to accept the protocol reject for LCP.
    (Note which is not recommended in "PPP Design, Implementation, and
    Debugging, Second Edition" by J. Carlson.)

    18    12/15/05 18:43 Shiki
    Added support for LCP Magic-Number option.

    17    12/15/05 11:59 Shiki
    Fixed ReceiveEchoRequest() to check packet length.
    Fixed SendEchoReply() to set local magic number to the reply.

    16    12/15/05 10:48 Shiki
    Revised PPPTimeout() to increment conf->id to ignore delayed responses.

    15    12/15/05 9:55 Shiki
    Fixed ReceiveProtocolReject() to check the rejected protocol is
    actually being used.

    14    12/01/05 10:00 Shiki
    Revised to use the PPP configurable parameters in to IPInterface{}.

    13    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    18    04/07/22 9:54 Ueno_kyu
    Enclosed AOL specific codes with "#ifdef IP_AOL".

    17    04/07/01 12:00 Ueno_kyu
    Added support for AOL.

    16    6/29/04 11:05 Shiki
    Moved PPPFcs16[] to IPHdlc.c

    15    6/23/04 14:55 Shiki
    Added PPPFcs16().

    14    04/06/15 15:02 Ueno_kyu
    Added support for modem.

    12    10/29/03 21:58 Shiki
    Revised using IFInitDatagram().

    11    10/22/03 14:27 Shiki
    Added support for PPPGetMessage().

    10    9/25/03 10:16 Shiki
    Fixed PPPLayerDown() to call PPPDown() for the upper layer before
    calling down() of the current layer.

    9     7/01/03 16:42 Shiki
    Fixed PPPIn() to process IP packets.

    8     7/01/03 14:55 Shiki
    Fixed to set IP_ERR_PPPoE_TIMEOUT upon PPPTimeout (TO-).

    7     7/01/03 14:03 Shiki
    Restructured the PPP layer structure.

    6     5/15/03 15:54 Shiki
    Modified to clear the IF_DATAGRAM_FLAG_DROP bit in IFDatagram.flag
    before sending a Ethernet packet.

    5     10/01/02 9:59 Shiki
    Added const keywords to relevant function prototypes.

    4     8/05/02 10:06 Shiki
    Added support for CHAP.

    3     8/01/02 17:07 Shiki
    Fixed LCPOut () to use constant 3 second timeout.

    2     8/01/02 11:31 Shiki
    Fixed LCPOut(), etc.

    1     7/31/02 16:12 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifdef IOP_OS
#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <dolphin/iop_libc.h>
#endif // IOP_OS

#include <stddef.h>
#include <dolphin/os.h>
#include <dolphin/socket.h>
#include <dolphin/ip/IPPpp.h>
#include <private/eth.h>
#include "IPPrivate.h"
#include "IPPPPConf.h"
#ifdef IP_AOL
#include  "IPAol.h"
#endif // IP_AOL

// LCP Code
enum
{
    ConfigureRequest = 1,
    ConfigureAck,
    ConfigureNak,
    ConfigureReject,
    TerminateRequest,
    TerminateAck,
    CodeReject,
    ProtocolReject,
    EchoRequest,
    EchoReply,
    DiscardRequest
};

// PPP State Machine
enum
{
    // LCP/NCP State
    Initial         = 0,
    Starting        = 1,
    Closed          = 2,
    Stopped         = 3,
    Closing         = 4,
    Stopping        = 5,
    RequestSent     = 6,
    AckReceived     = 7,
    AckSent         = 8,
    Opened          = 9
};

PPPAuth __PPPAuth;

#ifdef VERBOSE

static const char* GetProtocolString(u16 protocol)
{
    switch (protocol)
    {
      case PPP_LCP:
        return "LCP";
      case PPP_PAP:
        return "PAP";
      case PPP_LQR:
        return "LQR";
      case PPP_CHAP:
        return "CHAP";
      case PPP_IPCP:
        return "IPCP";
      case PPP_IP:
        return "IP";
      default:
        return "Unknown";
    }
}

static const char* GetStateString(int state)
{
    switch (state)
    {
      case Initial:
        return "Initial";
      case Starting:
        return "Starting";
      case Closed:
        return "Closed";
      case Stopped:
        return "Stopped";
      case Closing:
        return "Closing";
      case Stopping:
        return "Stopping";
      case RequestSent:
        return "RequestSent";
      case AckReceived:
        return "AckReceived";
      case AckSent:
        return "AckSent";
      case Opened:
        return "Opened";
      default:
        return "Unknown";
    }
}

#endif  // VERBOSE

//
// Note the following layer functions must be called *AFTER*
// the call to PPPSetState() as the layer functions could modify
// modify the state of current PPP FSM. So if PPPSetState() is
// called afterwards, a wrong state transition could be taken
// base on the state before the call to the lay function.
//

// This-Layer-Up
//
// Signals the Up event to the upper layer.
BOOL PPPLayerUp(PPPConf* conf)
{
    BOOL     rc;
    PPPConf* upper;

    rc = conf->up(conf);
    if (rc)
    {
        upper = (PPPConf*) IFQueryLinkNext(conf, link);
        if (!IFIsQueueEnd(&conf->interface->ppp, upper))
        {
            PPPUp(upper);
        }
    }
    return rc;
}

// This-Layer-Down
//
// Signals the Down event to the upper layer.
BOOL PPPLayerDown(PPPConf* conf)
{
    PPPConf* upper;

    upper = (PPPConf*) IFQueryLinkNext(conf, link);
    if (!IFIsQueueEnd(&conf->interface->ppp, upper))
    {
        PPPDown(upper);
    }
    return conf->down(conf);
}

// This-Layer-Started
//
// Signals the Open event to the lower layer.
BOOL PPPLayerStarted(PPPConf* conf)
{
    BOOL     rc;
    PPPConf* lower;

    rc = conf->started(conf);
    if (rc)
    {
        lower = (PPPConf*) IFQueryLinkPrev(conf, link);
        if (!IFIsQueueEnd(&conf->interface->ppp, lower))
        {
            PPPOpen(lower);
        }
    }
    return rc;
}

// This-Layer-Finished
//
// Signals the Close event to the lower layer (if required).
BOOL PPPLayerFinished(PPPConf* conf)
{
    BOOL     rc;
    PPPConf* lower;

    rc = conf->finished(conf);
    if (rc)
    {
        lower = (PPPConf*) IFQueryLinkPrev(conf, link);
        if (!IFIsQueueEnd(&conf->interface->ppp, lower))
        {
            PPPClose(lower);    // XXX if required
        }
    }
    return rc;
}

void PPPInitializeRestartCount(PPPConf* conf)
{
    IPInterface* interface = conf->interface;

    conf->rxmit     = 0;

    conf->configure = interface->pppMaxConfigure;
    conf->terminate = interface->pppMaxTerminate;
    conf->failure   = interface->pppMaxFailure;

    ++conf->id;

    OSCancelAlarm(&conf->alarm);
}

void PPPZeroRestartCount(PPPConf* conf)
{
    conf->rxmit     = 0;

    conf->configure = 0;
    conf->terminate = 0;
    conf->failure   = 0;

    OSCancelAlarm(&conf->alarm);
}

void PPPSetState(PPPConf* conf, int state)
{
#ifdef VERBOSE
    OSReport("PPPSetState(%s: %s -> %s)\n",
             GetProtocolString(conf->protocol),
             GetStateString(conf->state),
             GetStateString(state));
#endif  // VERBOSE

    conf->state = state;
    if (conf->callback)
    {
        conf->callback(conf);
    }

    switch (conf->state)
    {
      case Initial:
      case Starting:
      case Closed:
      case Opened:
        OSCancelAlarm(&conf->alarm);
        break;
    }
}

int PPPGetState(PPPConf* conf)
{
    return conf->state;
}

// len -- only for data
static void LCPOut(PPPConf* conf, u8 code, u8 id, s32 len, void* data)
{
    IPInterface* interface;
    IFDatagram*  datagram;
    u16*         proto;
    LCPHeader*   lcp;
    BOOL         enabled;

    enabled = OSDisableInterrupts();

    interface = conf->interface;

    // Set alarm here so we can retry even if alloc() is failed.
    if (code == ConfigureRequest || code == TerminateRequest)
    {
        OSCancelAlarm(&conf->alarm);
        OSSetAlarm(&conf->alarm,
                   OSSecondsToTicks((OSTime) interface->pppRestartTimer),
                   PPPTimeout);
    }

    // MRU trunc
    if (interface->mtu < LCP_HLEN + len)
    {
        len = interface->mtu - LCP_HLEN;
    }
    datagram = interface->alloc(interface, (s32) sizeof(IFDatagram) + 2 + LCP_HLEN + len);
    if (datagram)
    {
        IFInitDatagram(datagram, ETH_PPPoE_SESSION, 1);

        proto = (u16*) ((u8*) datagram + sizeof(IFDatagram));
        *proto = conf->protocol;

        lcp = (LCPHeader*) ((u8*) proto + 2);
        lcp->code = code;
        lcp->id   = id;
        lcp->len  = (u16) (LCP_HLEN + len);

        memmove((u8*) lcp + LCP_HLEN, data, (u32) len);

        datagram->vec[0].data = proto;
        datagram->vec[0].len  = 2 + LCP_HLEN + len;

        interface->out(interface, datagram);
    }

    OSRestoreInterrupts(enabled);
}

static BOOL SendConfigureRequest(PPPConf* conf)
{
    if (0 < conf->configure)
    {
        --conf->configure;
        LCPOut(conf, ConfigureRequest, conf->id, conf->len, conf->data);
        return TRUE;
    }
    return FALSE;
}

static void SendConfigureAck(PPPConf* conf, LCPHeader* lcp)
{
    conf->failure = conf->interface->pppMaxFailure;
    LCPOut(conf, ConfigureAck,    lcp->id, lcp->len - LCP_HLEN, (u8*) lcp + LCP_HLEN);
}

static void SendConfigureNak(PPPConf* conf, LCPHeader* lcp)
{
    ASSERT(0 < conf->failure);
    --conf->failure;
    LCPOut(conf, ConfigureNak,    lcp->id, lcp->len - LCP_HLEN, (u8*) lcp + LCP_HLEN);
}

static void SendConfigureReject(PPPConf* conf, LCPHeader* lcp)
{
    LCPOut(conf, ConfigureReject, lcp->id, lcp->len - LCP_HLEN, (u8*) lcp + LCP_HLEN);
}

static BOOL SendTerminateRequest(PPPConf* conf)
{
    if (0 < conf->terminate)
    {
        --conf->terminate;
        LCPOut(conf, TerminateRequest, conf->id, 0, NULL);
        return TRUE;
    }
    return FALSE;
}

static void SendTerminateAck(PPPConf* conf)
{
    LCPOut(conf, TerminateAck, conf->idTerminate, 0, NULL);
}

static void SendCodeReject(PPPConf* conf, LCPHeader* lcp)
{
    ++conf->idReject;
    LCPOut(conf, CodeReject,     conf->idReject, lcp->len, lcp);
}

static void SendProtocolReject(PPPConf* conf, s32 len, void* data)
{
    ++conf->idReject;
    LCPOut(conf, ProtocolReject, conf->idReject, len, data);
}

static void SendEchoReply(PPPConf* conf, LCPHeader* lcp)
{
    *((u32*) ((u8*) lcp + LCP_HLEN)) = conf->magic;
    LCPOut(conf, EchoReply, conf->idEcho, lcp->len - LCP_HLEN, (u8*) lcp + LCP_HLEN);
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 RCR+ |    -         -       sta/2 irc,scr,sca/8   4         5       sca/8   sca,tlu/9   sca/8   tld,scr,sca/8
 RCR- |    -         -       sta/2 irc,scr,scn/6   4         5       scn/6     scn/7     scn/6   tld,scr,scn/6
 */
static void ReceiveConfigureRequest(PPPConf* conf, LCPHeader* lcp)
{
    int rc;
#ifndef IOP_OS
    u8* data = ((u8*) lcp + LCP_HLEN);
#endif // IOP_OS
    
    rc = conf->receiveConfigureRequest(conf, lcp);
    switch (rc)
    {
      case PPP_RCR_ACCEPT:
        switch (conf->state)
        {
          case Closed:
            SendTerminateAck(conf);
            break;
          case Stopped:
            PPPInitializeRestartCount(conf);
            SendConfigureRequest(conf);
            SendConfigureAck(conf, lcp);
            PPPSetState(conf, AckSent);
            break;
          case RequestSent:
            SendConfigureAck(conf, lcp);
            PPPSetState(conf, AckSent);
            break;
          case AckReceived:
            SendConfigureAck(conf, lcp);
            PPPSetState(conf, Opened);
            PPPLayerUp(conf);
            break;
          case AckSent:
            SendConfigureAck(conf, lcp);
            break;
          case Opened:
            SendConfigureRequest(conf);
            SendConfigureAck(conf, lcp);
            PPPSetState(conf, AckSent);
            PPPLayerDown(conf);
            break;
        }
        break;
      case PPP_RCR_REJECT:
        switch (conf->state)
        {
          case Closed:
            SendTerminateAck(conf);
            break;
          case Stopped:
            PPPInitializeRestartCount(conf);
            SendConfigureRequest(conf);
            SendConfigureReject(conf, lcp);
            PPPSetState(conf, RequestSent);
            break;
          case RequestSent:
            SendConfigureReject(conf, lcp);
            break;
          case AckReceived:
            SendConfigureReject(conf, lcp);
            break;
          case AckSent:
            SendConfigureReject(conf, lcp);
            PPPSetState(conf, RequestSent);
            break;
          case Opened:
            SendConfigureRequest(conf);
            SendConfigureReject(conf, lcp);
            PPPSetState(conf, RequestSent);
            PPPLayerDown(conf);
            break;
        }
        break;
      case PPP_RCR_NACK:
        switch (conf->state)
        {
          case Closed:
            SendTerminateAck(conf);
            break;
          case Stopped:
            PPPInitializeRestartCount(conf);
            SendConfigureRequest(conf);
            SendConfigureNak(conf, lcp);
            PPPSetState(conf, RequestSent);
            break;
          case RequestSent:
            SendConfigureNak(conf, lcp);
            break;
          case AckReceived:
            SendConfigureNak(conf, lcp);
            break;
          case AckSent:
            SendConfigureNak(conf, lcp);
            PPPSetState(conf, RequestSent);
            break;
          case Opened:
            SendConfigureRequest(conf);
            SendConfigureNak(conf, lcp);
            PPPSetState(conf, RequestSent);
            PPPLayerDown(conf);
            break;
        }
        break;
      case PPP_RCR_INVALID:
      default:
        break;
    }
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 RCA  |    -         -       sta/2     sta/3       4         5       irc/7     scr/6x  irc,tlu/9   tld,scr/6x
 */
static void ReceiveConfigureAck(PPPConf* conf, LCPHeader* lcp)
{
    BOOL rc;

    rc = conf->receiveConfigureAck(conf, lcp);
    if (!rc)
    {
        return;
        // NOT REACHED HERE
    }

    switch (conf->state)
    {
      case Closed:
        SendTerminateAck(conf);
        break;
      case Stopped:
        SendTerminateAck(conf);
        break;
      case RequestSent:
        PPPInitializeRestartCount(conf);
        PPPSetState(conf, AckReceived);
        break;
      case AckReceived:
        SendConfigureRequest(conf);
        break;
      case AckSent:
        PPPInitializeRestartCount(conf);
        PPPSetState(conf, Opened);
        PPPLayerUp(conf);
        break;
      case Opened:
        SendConfigureRequest(conf);
        PPPSetState(conf, RequestSent);
        PPPLayerDown(conf);
        break;
    }
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 RCN  |    -         -       sta/2     sta/3       4         5     irc,scr/6   scr/6x  irc,scr/8   tld,scr/6x
 */
static void ReceiveConfigureNak(PPPConf* conf, LCPHeader* lcp)
{
    BOOL rc;

    rc = conf->receiveConfigureNak(conf, lcp);
    if (!rc)
    {
        return;
        // NOT REACHED HERE
    }

    switch (conf->state)
    {
      case Closed:
        SendTerminateAck(conf);
        break;
      case Stopped:
        SendTerminateAck(conf);
        break;
      case RequestSent:
        PPPInitializeRestartCount(conf);
        SendConfigureRequest(conf);
        break;
      case AckReceived:
        SendConfigureRequest(conf);
        break;
      case AckSent:
        PPPInitializeRestartCount(conf);
        SendConfigureRequest(conf);
        break;
      case Opened:
        SendConfigureRequest(conf);
        PPPSetState(conf, RequestSent);
        PPPLayerDown(conf);
        break;
    }
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 RCN  |    -         -       sta/2     sta/3       4         5     irc,scr/6   scr/6x  irc,scr/8   tld,scr/6x
 */
static void ReceiveConfigureReject(PPPConf* conf, LCPHeader* lcp)
{
    BOOL rc;

    rc = conf->receiveConfigureReject(conf, lcp);
    if (!rc)
    {
        return;
        // NOT REACHED HERE
    }

    switch (conf->state)
    {
      case Closed:
        SendTerminateAck(conf);
        break;
      case Stopped:
        SendTerminateAck(conf);
        break;
      case RequestSent:
        PPPInitializeRestartCount(conf);
        SendConfigureRequest(conf);
        break;
      case AckReceived:
        SendConfigureRequest(conf);
        break;
      case AckSent:
        PPPInitializeRestartCount(conf);
        SendConfigureRequest(conf);
        break;
      case Opened:
        SendConfigureRequest(conf);
        PPPSetState(conf, RequestSent);
        PPPLayerDown(conf);
        break;
    }
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 RTR  |    -         -       sta/2     sta/3     sta/4     sta/5     sta/6     sta/6     sta/6   tld,zrc,sta/5
 */
static void ReceiveTerminateRequest(PPPConf* conf, LCPHeader* lcp)
{
    conf->idTerminate = lcp->id;    // Save id for retransmission.
    switch (conf->state)
    {
      case Closed:
        SendTerminateAck(conf);
        break;
      case Stopped:
        SendTerminateAck(conf);
        break;
      case Closing:
        SendTerminateAck(conf);
        break;
      case Stopping:
        SendTerminateAck(conf);
        break;
      case RequestSent:
        SendTerminateAck(conf);
        break;
      case AckReceived:
        SendTerminateAck(conf);
        PPPSetState(conf, RequestSent);
        break;
      case AckSent:
        SendTerminateAck(conf);
        PPPSetState(conf, RequestSent);
        break;
      case Opened:
        PPPZeroRestartCount(conf);
        SendTerminateAck(conf);
        PPPSetState(conf, Stopping);
        PPPLayerDown(conf);
        break;
    }
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 RTA  |    -         -         2         3       tlf/2     tlf/3       6         6         8       tld,scr/6
 */
static void ReceiveTerminateAck(PPPConf* conf, LCPHeader* lcp)
{
#ifdef IOP_OS
    TCPIP_UNUSED(lcp);
#else
    #pragma unused( lcp )
#endif // IOP_OS

    switch (conf->state)
    {
      case Closing:
        PPPSetState(conf, Closed);
        PPPLayerFinished(conf);
        break;
      case Stopping:
        PPPSetState(conf, Stopped);
        PPPLayerFinished(conf);
        break;
      case RequestSent:
        break;
      case AckReceived:
        PPPSetState(conf, RequestSent);
        break;
      case AckSent:
        break;
      case Opened:
        SendConfigureRequest(conf);
        PPPSetState(conf, RequestSent);
        PPPLayerDown(conf);
        break;
    }
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 RUC  |    -         -       scj/2     scj/3     scj/4     scj/5     scj/6     scj/7     scj/8       scj/9
 */
static void ReceiveUnknownCode(PPPConf* conf, LCPHeader* lcp)
{
    switch (conf->state)
    {
      case Closed:
        SendCodeReject(conf, lcp);
        break;
      case Stopped:
        SendCodeReject(conf, lcp);
        break;
      case Closing:
        SendCodeReject(conf, lcp);
        break;
      case Stopping:
        SendCodeReject(conf, lcp);
        break;
      case RequestSent:
        SendCodeReject(conf, lcp);
        break;
      case AckReceived:
        SendCodeReject(conf, lcp);
        break;
      case AckSent:
        SendCodeReject(conf, lcp);
        break;
      case Opened:
        SendCodeReject(conf, lcp);
        break;
    }
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 RXJ+ |    -         -         2         3         4         5         6         6         8           9
 RXJ- |    -         -       tlf/2     tlf/3     tlf/2     tlf/3     tlf/3     tlf/3     tlf/3   tld,irc,str/5
 */
static void ReceiveCodeReject(PPPConf* conf, LCPHeader* lcp)
{
#ifdef IOP_OS
    TCPIP_UNUSED(lcp);
#else
    #pragma unused( lcp )
#endif // IOP_OS

    BOOL plus = FALSE;  // Always fatal...

    if (plus)
    {
        switch (conf->state)
        {
          case AckReceived:
            PPPSetState(conf, RequestSent);
            break;
        }
    }
    else
    {
        switch (conf->state)
        {
          case Closed:
            PPPLayerFinished(conf);
            break;
          case Stopped:
            PPPLayerFinished(conf);
            break;
          case Closing:
            PPPSetState(conf, Closed);
            PPPLayerFinished(conf);
            break;
          case Stopping:
            PPPSetState(conf, Stopped);
            PPPLayerFinished(conf);
            break;
          case RequestSent:
            PPPSetState(conf, Stopped);
            PPPLayerFinished(conf);
            break;
          case AckReceived:
            PPPSetState(conf, Stopped);
            PPPLayerFinished(conf);
            break;
          case AckSent:
            PPPSetState(conf, Stopped);
            PPPLayerFinished(conf);
            break;
          case Opened:
            PPPInitializeRestartCount(conf);
            PPPSetState(conf, Stopping);
            PPPLayerDown(conf);
            break;
        }
    }
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 RXJ+ |    -         -         2         3         4         5         6         6         8           9
 RXJ- |    -         -       tlf/2     tlf/3     tlf/2     tlf/3     tlf/3     tlf/3     tlf/3   tld,irc,str/5
 */
static void ReceiveProtocolReject(PPPConf* conf, LCPHeader* lcp)
{
#ifdef IOP_OS
    TCPIP_UNUSED(lcp);
#else
    #pragma unused( lcp )
#endif // IOP_OS

    BOOL plus = FALSE;  // Always fatal...
    u16 protocol;
    PPPConf* upper;

    if (lcp->len < LCP_HLEN + 2)
    {
        return;
    }
    protocol = *(u16*) ((u8*) lcp + LCP_HLEN);

    // Check protocol is currently being used.
    for (upper = conf;
         !IFIsQueueEnd(&conf->interface->ppp, upper);
         upper = (PPPConf*) IFQueryLinkNext(upper, link))
    {
        if (upper->protocol == protocol)
        {
            break;
        }
    }
    if (IFIsQueueEnd(&conf->interface->ppp, upper))
    {
        return;
    }

    if (plus)
    {
        switch (conf->state)
        {
          case AckReceived:
            PPPSetState(conf, RequestSent);
            break;
        }
    }
    else
    {
        switch (conf->state)
        {
          case Closed:
            PPPLayerFinished(conf);
            break;
          case Stopped:
            PPPLayerFinished(conf);
            break;
          case Closing:
            PPPSetState(conf, Closed);
            PPPLayerFinished(conf);
            break;
          case Stopping:
            PPPSetState(conf, Stopped);
            PPPLayerFinished(conf);
            break;
          case RequestSent:
            PPPSetState(conf, Stopped);
            PPPLayerFinished(conf);
            break;
          case AckReceived:
            PPPSetState(conf, Stopped);
            PPPLayerFinished(conf);
            break;
          case AckSent:
            PPPSetState(conf, Stopped);
            PPPLayerFinished(conf);
            break;
          case Opened:
            PPPInitializeRestartCount(conf);
            PPPSetState(conf, Stopping);
            PPPLayerDown(conf);
            break;
        }
    }
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 RXR  |    -         -         2         3         4         5         6         7         8         ser/9
 */
static void ReceiveEchoRequest(PPPConf* conf, LCPHeader* lcp)
{
    u32 magic;

    if (lcp->len < LCP_HLEN + 4)
    {
        return;
    }

    magic = *(u32*) ((u8*) lcp + LCP_HLEN);
    if (magic != conf->magicPeer)
    {
        return;
    }

    conf->idEcho = lcp->id;
    switch (conf->state)
    {
      case Opened:
        SendEchoReply(conf, lcp);
        break;
    }
}

// LCP Input
static void LCPIn(PPPConf* conf, LCPHeader* lcp, s32 len, u32 flag)
{
#ifdef IOP_OS
    TCPIP_UNUSED(flag);
#else
    #pragma unused( flag )
#endif // IOP_OS

    if (conf == NULL || len < LCP_HLEN || len < lcp->len || lcp->len < LCP_HLEN)
    {
        return;
    }

    switch (lcp->code)
    {
      case ConfigureRequest:
        ReceiveConfigureRequest(conf, lcp);
        break;
      case ConfigureAck:
        if (lcp->id == conf->id)
        {
            ReceiveConfigureAck(conf, lcp);
        }
        break;
      case ConfigureNak:
        if (lcp->id == conf->id)
        {
            ReceiveConfigureNak(conf, lcp);
        }
        break;
      case ConfigureReject:
        if (lcp->id == conf->id)
        {
            ReceiveConfigureReject(conf, lcp);
        }
        break;
      case TerminateRequest:
        ReceiveTerminateRequest(conf, lcp);
        break;
      case TerminateAck:
        if (lcp->id == conf->id)
        {
            ReceiveTerminateAck(conf, lcp);
        }
        break;
      case CodeReject:
        ReceiveCodeReject(conf, lcp);
        break;
      case ProtocolReject:
        ReceiveProtocolReject(conf, lcp);
        break;
      case EchoRequest:
        ReceiveEchoRequest(conf, lcp);
        break;
      case EchoReply:
      case DiscardRequest:
        // Silently discard the packet
        break;
      default:
        ReceiveUnknownCode(conf, lcp);
        break;
    }
}

// IPCP Input
static void IPCPIn(PPPConf* conf, IPCPHeader* ipcp, s32 len, u32 flag)
{
#ifdef IOP_OS
    TCPIP_UNUSED(flag);
#else
    #pragma unused( flag )
#endif // IOP_OS

    if (conf == NULL || len < IPCP_HLEN || len < ipcp->len || ipcp->len < IPCP_HLEN)
    {
        return;
    }

    switch (ipcp->code)
    {
      case ConfigureRequest:
      case ConfigureAck:
      case ConfigureNak:
      case ConfigureReject:
      case TerminateRequest:
      case TerminateAck:
      case CodeReject:
        LCPIn(conf, ipcp, len, flag);
        break;
      case ProtocolReject:
      case EchoRequest:
      case EchoReply:
      case DiscardRequest:
      default:
        ReceiveUnknownCode(conf, ipcp);
        break;
    }
}

void PPPIn(IPInterface* interface, u8* ppp, s32 len, u32 flag)
{
    u16      protocol;
    PPPConf* conf;
    PPPConf* next;
    PPPConf* lcp;
    PPPConf* ipcp;

    if (len < 2)
    {
        return;
    }
    len -= 2;

    protocol = *(u16*) ppp; ppp += 2;
    if (protocol == PPP_IP)
    {
        // Select IPCP
        ipcp = (PPPConf*) IFQueryQueueTail(&interface->ppp);
        ASSERT(ipcp->protocol == PPP_IPCP);
        // Before any IP packets may be communicated, PPP must reach the
        // Network-Layer Protocol phase, and the IP Control Protocol must reach
        // the Opened state. [RFC 1332]
        if (ipcp->state == Opened)
        {
            IPIn(interface, (IPHeader*) ppp, len, flag);
        }
        return;
        // NOT REACHED HERE
    }

    // Lookup PPP stacks of the specified protocol
    IFIterateQueue(PPPConf*, &interface->ppp, conf, next, link)
    {
        if (protocol == conf->protocol)
        {
            break;
        }
    }
    if (IFIsQueueEnd(&interface->ppp, conf))
    {
        // Select LCP for SendProtocolReject()
        lcp = (PPPConf*) IFQueryQueueHead(&interface->ppp);
        ASSERT(lcp->protocol == PPP_LCP);
        if (lcp->state == Opened)
        {
            SendProtocolReject(lcp, len + 2, ppp - 2);
        }
        return;
        // NOT REACHED HERE
    }

    // Call corresponding input function
    switch (protocol)
    {
      case PPP_LCP:
        LCPIn(conf, (LCPHeader*) ppp, len, flag);
        break;
      case PPP_IPCP:
        // IPCP packets received before the Network-Layer Protocol phase
        // is reached should be silently discarded.
        lcp = (PPPConf*) IFQueryQueueHead(&interface->ppp);
        ASSERT(lcp->protocol == PPP_LCP);
        if (lcp->state == Opened)
        {
            IPCPIn(conf, (IPCPHeader*) ppp, len, flag);
        }
        break;
      case PPP_PAP:
        PAPIn(conf, (PAPHeader*) ppp, len, flag);
        break;
      case PPP_CHAP:
        CHAPIn(conf, (CHAPHeader*) ppp, len, flag);
        break;
    }
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 Open |  tls/1       1     irc,scr/6     3r        5r        5r        6         7         8           9r
 */
void PPPOpen(PPPConf* conf)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    switch (conf->protocol)
    {
      case PPP_PAP:
        PAPOpen(conf);
        break;
      case PPP_CHAP:
        CHAPOpen(conf);
        break;
      default:
        switch (conf->state)
        {
          case Initial:
            PPPSetState(conf, Starting);
            PPPLayerStarted(conf);
            break;
          case Starting:
            break;
          case Closed:
            PPPInitializeRestartCount(conf);
            SendConfigureRequest(conf);
            PPPSetState(conf, RequestSent);
            break;
          case Stopped:
            break;
          case Closing:
            PPPSetState(conf, Stopping);
            break;
          case Stopping:
            break;
          case RequestSent:
            break;
          case AckReceived:
            break;
          case AckSent:
            break;
          case Opened:
            break;
        }
    }
    OSRestoreInterrupts(enabled);
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 Up   |    2     irc,scr/6     -         -         -         -         -         -         -           -
 */
void PPPUp(PPPConf* conf)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    switch (conf->protocol)
    {
      case PPP_PAP:
        PAPUp(conf);
        break;
      case PPP_CHAP:
        CHAPUp(conf);
        break;
      default:
        switch (conf->state)
        {
          case Initial:
            PPPSetState(conf, Closed);
            break;
          case Starting:
            PPPInitializeRestartCount(conf);
            SendConfigureRequest(conf);
            PPPSetState(conf, RequestSent);
            break;
        }
    }
    OSRestoreInterrupts(enabled);
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 Down |    -         -         0       tls/1       0         1         1         1         1         tld/1
 */
void PPPDown(PPPConf* conf)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    switch (conf->protocol)
    {
      case PPP_PAP:
        PAPDown(conf);
        break;
      case PPP_CHAP:
        CHAPDown(conf);
        break;
      default:
        switch (conf->state)
        {
          case Closed:
            PPPSetState(conf, Initial);
            break;
          case Stopped:
            PPPSetState(conf, Starting);
            PPPLayerStarted(conf);
            break;
          case Closing:
            PPPSetState(conf, Initial);
            break;
          case Stopping:
            PPPSetState(conf, Starting);
            break;
          case RequestSent:
            PPPSetState(conf, Starting);
            break;
          case AckReceived:
            PPPSetState(conf, Starting);
            break;
          case AckSent:
            PPPSetState(conf, Starting);
            break;
          case Opened:
            PPPSetState(conf, Starting);
            PPPLayerDown(conf);
            break;
        }
    }
    OSRestoreInterrupts(enabled);
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
 Close|    0       tlf/0       2         2         4         4     irc,str/4 irc,str/4 irc,str/4 tld,irc,str/4
 */
void PPPClose(PPPConf* conf)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    switch (conf->protocol)
    {
      case PPP_PAP:
        PAPClose(conf);
        break;
      case PPP_CHAP:
        CHAPClose(conf);
        break;
      default:
        switch (conf->state)
        {
          case Initial:
            break;
          case Starting:
            PPPSetState(conf, Initial);
            PPPLayerFinished(conf);
            break;
          case Closed:
            break;
          case Stopped:
            PPPSetState(conf, Closed);
            break;
          case Closing:
            break;
          case Stopping:
            PPPSetState(conf, Closing);
            break;
          case RequestSent:
            PPPInitializeRestartCount(conf);
            SendTerminateRequest(conf);
            PPPSetState(conf, Closing);
            break;
          case AckReceived:
            PPPInitializeRestartCount(conf);
            SendTerminateRequest(conf);
            PPPSetState(conf, Closing);
            break;
          case AckSent:
            PPPInitializeRestartCount(conf);
            SendTerminateRequest(conf);
            PPPSetState(conf, Closing);
            break;
          case Opened:
            PPPInitializeRestartCount(conf);
            SendTerminateRequest(conf);
            PPPSetState(conf, Closing);
            PPPLayerDown(conf);
            break;
        }
        break;
    }
    OSRestoreInterrupts(enabled);
}

/*
      | State
      |    0         1         2         3         4         5         6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping  Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+-----------------------------------------------------------------------------------------------------
  TO+ |    -         -         -         -       str/4     str/5     scr/6     scr/6     scr/8         -
  TO- |    -         -         -         -       tlf/2     tlf/3     tlf/3p    tlf/3p    tlf/3p        -
 */
void PPPTimeout(OSAlarm* alarm, OSContext* context)
{
#ifdef IOP_OS
    TCPIP_UNUSED(context);
#else
    #pragma unused( context )
#endif // IOP_OS

    PPPConf* conf;

#ifdef IOP_OS
    BOOL     expired = FALSE;
#else
    BOOL     expired;
#endif // IOP_OS

    conf = (PPPConf*) ((u8*) alarm - offsetof(PPPConf, alarm));
    ++conf->rxmit;

    switch (conf->protocol)
    {
      case PPP_PAP:
        expired = !PAPTimeout(conf);
        break;
      case PPP_CHAP:
        expired = !CHAPTimeout(conf);
        break;
      default:
        switch (conf->state)
        {
          case Closing:
            ++conf->id;
            expired = !SendTerminateRequest(conf);
            if (expired)
            {
                PPPSetState(conf, Closed);
                PPPLayerFinished(conf);
            }
            break;
          case Stopping:
            ++conf->id;
            expired = !SendTerminateRequest(conf);
            if (expired)
            {
                PPPSetState(conf, Stopped);
                PPPLayerFinished(conf);
            }
            break;
          case RequestSent:
            ++conf->id;
            expired = !SendConfigureRequest(conf);
            if (expired)
            {
                PPPSetState(conf, Stopped);
                PPPLayerFinished(conf);
            }
            break;
          case AckReceived:
            ++conf->id;
            expired = !SendConfigureRequest(conf);
            if (expired)
            {
                PPPSetState(conf, Stopped);
                PPPLayerFinished(conf);
            }
            else
            {
                PPPSetState(conf, RequestSent);
            }
            break;
          case AckSent:
            ++conf->id;
            expired = !SendConfigureRequest(conf);
            if (expired)
            {
                PPPSetState(conf, Stopped);
                PPPLayerFinished(conf);
            }
            break;
        }
        break;
    }

    if (expired)
    {
        IPSetConfigError(conf->interface, IP_ERR_PPPoE_TIMEOUT);
    }
}

u16 PPPDeleteOpt(u8* data, u16 len, LCPOpt* opt)
{
    u16 optlen;
    u8* next;

    optlen = opt->len;
    next = (u8*) opt + optlen;
    memmove(opt, next, (u32) (data + len - next));
    return (u16) (len - optlen);
}

u16 PPPInsertOpt(u8* data, u16 len, LCPOpt* at, LCPOpt* opt)
{
    u8* to;

    to = (u8*) at + opt->len;
    memmove(to, at, (u32) (data + len - (u8*) at));
    memmove(at, opt, opt->len);
    return (u16) (len + opt->len);
}

BOOL PPPInit(IPInterface* interface, PPPConf* lcp, PPPConf* ipcp,
             const char* peerid, const char* password,
             const char* dial, s32 dialMode, u8 ispCode)
{
    unsigned len;

    PPPInitLCP(lcp, interface);
    PPPInitIPCP(ipcp, interface);

    IFInitQueue(&interface->ppp);
    IFEnqueueTail(PPPConf*, &interface->ppp, lcp, link);
    IFEnqueueTail(PPPConf*, &interface->ppp, ipcp, link);

    if (peerid)
    {
        len = strlen(peerid);
        if (255 < len)
        {
            IPSetConfigError(NULL, IP_ERR_AUTH);
            return FALSE;
        }

#ifdef IP_AOL
        if (ispCode == SO_ISP_CODE_AOL)
        {
            if (!IPAOLGetID(peerid, __PPPAuth.peerId, sizeof(__PPPAuth.peerId)))
            {
                return FALSE;
            }
            __PPPAuth.peerIdLen = (u8) strlen(__PPPAuth.peerId);
#ifdef VERBOSE
            OSReport("%s => %s\n", peerid, __PPPAuth.peerId);
#endif // VERBOSE
        }
        else
        {
            __PPPAuth.peerIdLen = (u8) len;
            strncpy(__PPPAuth.peerId, peerid, 256);
        }
#endif // IP_AOL

#ifndef IP_AOL
        if (ispCode != SO_ISP_CODE_GENERIC)
        {
            return FALSE;
        }
        __PPPAuth.peerIdLen = (u8) len;
        strncpy(__PPPAuth.peerId, peerid, 256);
#endif
    }

    if (password)
    {
        len = strlen(password);
        if (255 < len)
        {
            IPSetConfigError(NULL, IP_ERR_AUTH);
            return FALSE;
        }

#ifdef IP_AOL
        if (ispCode == SO_ISP_CODE_AOL)
        {
            if (!IPAOLGetPassword(password,__PPPAuth.password,
                                  sizeof(__PPPAuth.password)))
            {
                return FALSE;
            }
            __PPPAuth.passwordLen = (u8) strlen(__PPPAuth.password);
#ifdef VERBOSE
            OSReport("%s => %s\n", password, __PPPAuth.password);
#endif // VERBOSE
        }
        else
        {
            __PPPAuth.passwordLen = (u8) len;
            strncpy(__PPPAuth.password, password, 256);
        }
#endif // IP_AOL

#ifndef IP_AOL
        if (ispCode != SO_ISP_CODE_GENERIC)
        {
            return FALSE;
        }
        __PPPAuth.passwordLen = (u8) len;
        strncpy(__PPPAuth.password, password, 256);
#endif
    }

    if (dial)
    {
        lcp->dial = dial;
    }

    if (dialMode == MDM_DIAL_TONE     ||
        dialMode == MDM_DIAL_PULSE_10 ||
        dialMode == MDM_DIAL_PULSE_20)
    {
        lcp->dialMode = dialMode;
    }

    __PPPAuth.messageLen = 0;
    __PPPAuth.message[0] = '\0';

    PPPOpen(ipcp);

    return TRUE;
}

const char* PPPGetMessage(void)
{
    return __PPPAuth.message;
}
