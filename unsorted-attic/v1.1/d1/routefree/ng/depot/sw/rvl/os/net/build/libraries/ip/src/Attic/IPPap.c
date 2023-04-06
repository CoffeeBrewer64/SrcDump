d1 445
a445 412
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API -- PPP Authenticatio Protocol - PAP [RFC 1334]
  File:     IPPap.c

  Copyright 2002-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip6/src/IPPap.c $
    
    8     12/16/05 10:45 Shiki
    Revised PAPIn() to check packet format more strictly.
    Fixed SendAuthenticateRequest() to increment conf->id every time.

    7     10/29/03 21:57 Shiki
    Revised using IFInitDatagram().

    6     10/22/03 14:30 Shiki
    Added support for PPPGetMessage().

    5     7/01/03 14:55 Shiki
    Fixed to set IP_ERR_PPPoE_TIMEOUT upon PPPTimeout (TO-).

    4     7/01/03 14:03 Shiki
    Restructured the PPP layer structure.

    3     5/15/03 15:54 Shiki
    Modified to clear the IF_DATAGRAM_FLAG_DROP bit in IFDatagram.flag
    before sending a Ethernet packet.

    2     10/07/02 10:27 Shiki
    Added support for IPGetConfigError().

    1     7/31/02 16:12 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <stddef.h>
#include <dolphin/os.h>
#include <dolphin/socket.h>
#include <dolphin/ip/IPPpp.h>
#include <private/eth.h>
#include "IPPrivate.h"
#include "IPPPPConf.h"

#define RXMIT_INIT      3   // [sec]

// PPP State Machine
enum
{
    // PAP/CHAP State
    Initial     = 0,
    Starting    = 1,
    Closed      = 2,
    RequestSent = 6,    // NOT USED
    AckReceived = 7,    // NOT USED
    AckSent     = 8,
    Opened      = 9
};

enum
{
    AuthenticateRequest = 1,
    AuthenticateAck     = 2,
    AuthenticateNak     = 3
};

static void PAPOut(PPPConf* conf)
{
    IPInterface* interface;
    BOOL         enabled;
    PAPHeader*   pap;
    IFDatagram*  datagram;
    s32          len;
    u8*          data;

    enabled = OSDisableInterrupts();

    interface = conf->interface;

    len = (s32) (1 + __PPPAuth.peerIdLen + 1 + __PPPAuth.passwordLen);

    // Set alarm here so we can retry even if alloc() is failed.
    OSCancelAlarm(&conf->alarm);
    OSSetAlarm(&conf->alarm,
               OSSecondsToTicks((OSTime) RXMIT_INIT), // XXX check backoff
               PPPTimeout);

    datagram = interface->alloc(interface, (s32) sizeof(IFDatagram) + 2 + PAP_HLEN + len);
    if (datagram)
    {
        IFInitDatagram(datagram, ETH_PPPoE_SESSION, 1);

        // PPP protocol field
        *(u16*) ((u8*) datagram + sizeof(IFDatagram)) = PPP_PAP;

        // PAP header
        pap = (PAPHeader*) ((u8*) datagram + sizeof(IFDatagram) + 2);
        pap->code = AuthenticateRequest;
        pap->id   = conf->id;
        pap->len  = (u16) (PAP_HLEN + len);

        // data
        data = (u8*) datagram + sizeof(IFDatagram) + 2 + PAP_HLEN;
        *data++ = __PPPAuth.peerIdLen;
        memmove(data, __PPPAuth.peerId, __PPPAuth.peerIdLen);
        data += __PPPAuth.peerIdLen;
        *data++ = __PPPAuth.passwordLen;
        memmove(data, __PPPAuth.password, __PPPAuth.passwordLen);
        data += __PPPAuth.passwordLen;

        datagram->vec[0].data = (u8*) datagram + sizeof(IFDatagram);
        datagram->vec[0].len  = 2 + PAP_HLEN + len;
        interface->out(interface, datagram);
    }

    OSRestoreInterrupts(enabled);
}

static BOOL SendAuthenticateRequest(PPPConf* conf)
{
    if (0 < conf->configure)
    {
        // The Identifier field MUST be changed each time an
        // Authenticate-Request packet is issued. [RFC 1334]
        ++conf->id;

        --conf->configure;
        PAPOut(conf);
        return TRUE;
    }
    return FALSE;
}

static BOOL ReceiveAuthenticateRequest(PPPConf* conf, PAPHeader* pap)
{
    #pragma unused( conf, pap )
    return TRUE;
}

static void GetAuthenticateMessage(PAPHeader* pap)
{
    char* msg = (char*) pap + PAP_HLEN;

    __PPPAuth.messageLen = *((u8*) msg);
    ++msg;
    memcpy(__PPPAuth.message, msg, __PPPAuth.messageLen);
    __PPPAuth.message[__PPPAuth.messageLen] = '\0';
}

static BOOL ReceiveAuthenticateAck(PPPConf* conf, PAPHeader* pap)
{
    GetAuthenticateMessage(pap);
    PPPInitializeRestartCount(conf);
    PPPSetState(conf, Opened);
    PPPLayerUp(conf);
    return TRUE;
}

static BOOL ReceiveAuthenticateNak(PPPConf* conf, PAPHeader* pap)
{
    GetAuthenticateMessage(pap);
    IPSetConfigError(NULL, IP_ERR_AUTH);
    PPPSetState(conf, Closed);
    PPPLayerFinished(conf);
    return TRUE;
}

void PAPOpen(PPPConf* conf)
{
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
        SendAuthenticateRequest(conf);
        PPPSetState(conf, RequestSent);
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

void PAPUp(PPPConf* conf)
{
    switch (conf->state)
    {
      case Initial:
        break;
      case Starting:
        PPPInitializeRestartCount(conf);
        SendAuthenticateRequest(conf);
        PPPSetState(conf, RequestSent);
        break;
      case Closed:
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

void PAPDown(PPPConf* conf)
{
    switch (conf->state)
    {
      case Initial:
        break;
      case Starting:
        break;
      case Closed:
        PPPSetState(conf, Initial);
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

void PAPClose(PPPConf* conf)
{
    switch (conf->state)
    {
      case Initial:
        break;
      case Starting:
        PPPSetState(conf, Closed);
        PPPLayerFinished(conf);
        break;
      case Closed:
        break;
      case RequestSent:
        PPPSetState(conf, Closed);
        PPPLayerFinished(conf);
        break;
      case AckReceived:
        PPPSetState(conf, Closed);
        PPPLayerFinished(conf);
        break;
      case AckSent:
        PPPSetState(conf, Closed);
        PPPLayerFinished(conf);
        break;
      case Opened:
        PPPSetState(conf, Closed);
        PPPLayerDown(conf);
        PPPLayerFinished(conf);
        break;
    }
}

// Return FALSE if expired (TO-)
BOOL PAPTimeout(PPPConf* conf)
{
    BOOL expired = FALSE;

    switch (conf->state)
    {
      case Initial:
        break;
      case Starting:
        break;
      case Closed:
        break;
      case RequestSent:
        if (!SendAuthenticateRequest(conf))
        {
            expired = TRUE;
            PPPSetState(conf, Closed);
            PPPLayerFinished(conf);
        }
        break;
      case AckReceived:
        if (conf->configure <= 0)
        {
            expired = TRUE;
            PPPSetState(conf, Closed);
            PPPLayerFinished(conf);
        }
        break;
      case AckSent:
        if (!SendAuthenticateRequest(conf))
        {
            expired = TRUE;
            PPPSetState(conf, Closed);
            PPPLayerFinished(conf);
        }
        break;
      case Opened:
        break;
    }
    return !expired;
}

void PAPIn(PPPConf* conf, PAPHeader* pap, s32 len, u32 flag)
{
    #pragma unused(flag)
    u8 msgLen;

    if (len < PAP_HLEN || len < pap->len || pap->len < PAP_HLEN)
    {
        return;
    }

    switch (pap->code)
    {
      case AuthenticateAck:
      case AuthenticateNak:
        if (pap->len < PAP_HLEN + 1)
        {
            return;
        }
        msgLen = *((u8*) pap + PAP_HLEN);
        if (pap->len < PAP_HLEN + 1 + msgLen)
        {
            return;
        }
        break;
    }

    switch (pap->code)
    {
      case AuthenticateRequest:
        ReceiveAuthenticateRequest(conf, pap);
        break;
      case AuthenticateAck:
        if (pap->id == conf->id)
        {
            ReceiveAuthenticateAck(conf, pap);
        }
        break;
      case AuthenticateNak:
        if (pap->id == conf->id)
        {
            ReceiveAuthenticateNak(conf, pap);
        }
        break;
    }
}

static BOOL Up(PPPConf* conf)
{
    #pragma unused(conf)
    return TRUE;
}

static BOOL Down(PPPConf* conf)
{
    #pragma unused(conf)

    __PPPAuth.messageLen = 0;
    __PPPAuth.message[0] = '\0';
    return TRUE;
}

static BOOL Started(PPPConf* conf)
{
    #pragma unused(conf)
    return TRUE;
}

static BOOL Finished(PPPConf* conf)
{
    #pragma unused(conf)
    return TRUE;
}

void PAPInit(PPPConf* conf, IPInterface* interface)
{
    memset(conf, 0, sizeof(PPPConf));
    conf->protocol = PPP_PAP;
    OSCreateAlarm(&conf->alarm);
    conf->interface = interface;

    conf->state = Initial;

    conf->up       = Up;
    conf->down     = Down;
    conf->started  = Started;
    conf->finished = Finished;
}
