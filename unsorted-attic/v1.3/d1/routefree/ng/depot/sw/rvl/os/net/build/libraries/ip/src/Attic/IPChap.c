/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API -- PPP CHAP [RFC 1994]
  File:     IPChap.c

  Copyright 2002-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPChap.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    8     12/16/05 10:43 Shiki
    Revised CHAPIn() to check packet format more strictly.

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

    2     10/07/02 10:40 Shiki
    Added support for IPGetConfigError().

    1     8/05/02 10:05 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <stddef.h>
#include <dolphin/os.h>
#include <dolphin/md5.h>
#include <dolphin/socket.h>
#include <dolphin/ip/IPPpp.h>
#include <private/eth.h>
#include "IPPrivate.h"
#include "IPPPPConf.h"

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

// CHAPHeader.code
enum
{
    Challenge = 1,
    Response,
    Success,
    Failure
};

static void CHAPOut(IPInterface* interface, CHAPHeader* chap)
{
    BOOL        enabled;
    IFDatagram* datagram;

    enabled = OSDisableInterrupts();

    datagram = interface->alloc(interface, (s32) sizeof(IFDatagram) + 2 + chap->len);
    if (datagram)
    {
        IFInitDatagram(datagram, ETH_PPPoE_SESSION, 1);

        // PPP protocol field
        *(u16*) ((u8*) datagram + sizeof(IFDatagram)) = PPP_CHAP;

        // CHAP packet
        memmove((u8*) datagram + sizeof(IFDatagram) + 2, chap, chap->len);

        datagram->vec[0].data = (u8*) datagram + sizeof(IFDatagram);
        datagram->vec[0].len  = 2 + chap->len;

        interface->out(interface, datagram);
    }

    OSRestoreInterrupts(enabled);
}

static BOOL ReceiveChallenge(PPPConf* conf, CHAPHeader* chap)
{
    //
    // Transmit a Response CHAP packet
    //
    u32         challengelen;
    MD5Context  context;

    conf->id = chap->id;

    challengelen = *((u8*) chap + 4);
    if (chap->len < CHAP_HLEN + 1 + challengelen)
    {
        return FALSE;
    }

    //
    // Make Response
    //
    // code
    chap->code = Response;
    // len
    chap->len  = (u16) (CHAP_HLEN + 1 + 16 + __PPPAuth.peerIdLen);
    // value-size
    *((u8*) chap + 4) = 16;
    // value
    MD5Init(&context);
    // Identifier (The second byte of the packet)
    MD5Update(&context, &chap->id, 1);
    // Secret
    MD5Update(&context, (u8*) __PPPAuth.password, __PPPAuth.passwordLen);
    // Challenge Value
    MD5Update(&context, (u8*) chap + 5, challengelen);
    // save digest
    MD5Final((u8*) chap + 5, &context);
    // name
    memmove((u8*) chap + 5 + 16, __PPPAuth.peerId, __PPPAuth.peerIdLen);

    CHAPOut(conf->interface, chap);

    return TRUE;
}

static BOOL ReceiveResponse(PPPConf* conf, CHAPHeader* chap)
{
#ifdef IOP_OS
    TCPIP_UNUSED(conf);
    TCPIP_UNUSED(chap);
#else
    #pragma unused( conf, chap )
#endif // IOP_OS
    
    return TRUE;
}

static void GetAuthenticateMessage(CHAPHeader* chap)
{
    char* msg = (char*) chap + CHAP_HLEN;

    __PPPAuth.messageLen = (u8) MIN(255, chap->len - CHAP_HLEN);
    memcpy(__PPPAuth.message, msg, __PPPAuth.messageLen);
    __PPPAuth.message[__PPPAuth.messageLen] = '\0';
}

static BOOL ReceiveSuccess(PPPConf* conf, CHAPHeader* chap)
{
    GetAuthenticateMessage(chap);
    PPPSetState(conf, Opened);
    PPPLayerUp(conf);
    return TRUE;
}

static BOOL ReceiveFailure(PPPConf* conf, CHAPHeader* chap)
{
    GetAuthenticateMessage(chap);
    IPSetConfigError(NULL, IP_ERR_AUTH);
    PPPSetState(conf, Closed);
    PPPLayerFinished(conf);
    return TRUE;
}

void CHAPOpen(PPPConf* conf)
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
        PPPSetState(conf, AckSent);
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

void CHAPUp(PPPConf* conf)
{
    switch (conf->state)
    {
      case Initial:
        break;
      case Starting:
        PPPInitializeRestartCount(conf);
        PPPSetState(conf, AckSent);
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

void CHAPDown(PPPConf* conf)
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

void CHAPClose(PPPConf* conf)
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
BOOL CHAPTimeout(PPPConf* conf)
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
      /*
        if (!SendChallenge(conf))
        {
            expired = TRUE;
            PPPLayerFinished(conf);
            PPPSetState(conf, Closed);
        }
       */
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
        if (conf->configure <= 0)
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

void CHAPIn(PPPConf* conf, CHAPHeader* chap, s32 len, u32 flag)
{
#ifdef IOP_OS
    TCPIP_UNUSED(flag);
#else
    #pragma unused(flag)
#endif // IOP_OS
    
    u8 valueSize;

    if (len < CHAP_HLEN || len < chap->len || chap->len < CHAP_HLEN)
    {
        return;
    }

    switch (chap->code)
    {
      case Challenge:
      case Response:
        if (chap->len < CHAP_HLEN + 1)
        {
            return;
        }
        valueSize = *((u8*) chap + CHAP_HLEN);
        if (valueSize < 1 ||    //  The Value field is one or more octets. [RFC 1994]
            chap->len < CHAP_HLEN + 1 + valueSize + 1)  // The Name field is one or more octets [RFC 1994]
        {
            return;
        }
        break;
      case Success:
      case Failure:
      default:
        break;
    }

    switch (chap->code)
    {
      case Challenge:
        ReceiveChallenge(conf, chap);
        break;
      case Response:
        if (conf->id == chap->id)
        {
            ReceiveResponse(conf, chap);
        }
        break;
      case Success:
        if (conf->id == chap->id)
        {
            ReceiveSuccess(conf, chap);
        }
        break;
      case Failure:
        if (conf->id == chap->id)
        {
            ReceiveFailure(conf, chap);
        }
        break;
    }
}

static BOOL Up(PPPConf* conf)
{
#ifdef IOP_OS
    TCPIP_UNUSED(conf);
#else
    #pragma unused(conf)
#endif // IOP_OS
    return TRUE;
}

static BOOL Down(PPPConf* conf)
{
#ifdef IOP_OS
    TCPIP_UNUSED(conf);
#else
    #pragma unused(conf)
#endif // IOP_OS

    __PPPAuth.messageLen = 0;
    __PPPAuth.message[0] = '\0';
    return TRUE;
}

static BOOL Started(PPPConf* conf)
{
#ifdef IOP_OS
    TCPIP_UNUSED(conf);
#else
    #pragma unused(conf)
#endif // IOP_OS
    return TRUE;
}

static BOOL Finished(PPPConf* conf)
{
#ifdef IOP_OS
    TCPIP_UNUSED(conf);
#else
    #pragma unused(conf)
#endif // IOP_OS
    return TRUE;
}

void CHAPInit(PPPConf* conf, IPInterface* interface)
{
    memset(conf, 0, sizeof(PPPConf));
    conf->protocol = PPP_CHAP;
    OSCreateAlarm(&conf->alarm);
    conf->interface = interface;

    conf->state = Initial;

    conf->up       = Up;
    conf->down     = Down;
    conf->started  = Started;
    conf->finished = Finished;
}
