d1 914
a914 843
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API -- PPP LCP
  File:     IPLcp.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip6/src/IPLcp.c $
    
    19    2/22/06 14:13 Shiki
    Fixed to check LTPOpt.len.

    18    12/16/05 17:21 Shiki
    Fixed ReceiveConfigureRequest() to check duplicated options.

    17    12/16/05 16:03 Shiki
    Fixed ReceiveConfigureRequest() to verify multiple Auth options are not
    included in the request.

    16    12/16/05 14:54 Shiki
    Fixed ReceiveConfigureReject() to check rejected options first.

    15    12/16/05 13:53 Shiki
    Fixed ReceiveConfigureRequest().

    14    12/16/05 11:51 Shiki
    Fixed ReceiveConfigureReject().

    13    12/15/05 18:58 Shiki
    Added support for LCP Magic-Number option.

    12    12/15/05 11:57 Shiki
    Fixed PPPInitLCP() to initialize magic to zero.

    10    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    17    04/07/08 16:41 Ueno_kyu
    Revised  IPResetAccm() and IPSetAccm().

    16    04/07/02 17:41 Ueno_kyu
    Bug fixes.

    15    04/07/02 16:01 Ueno_kyu
    Modified ReceiveConfigureRequest() to set accm for encoding a packet.

    14    04/07/02 13:36 Ueno_kyu
    Added support for ACCM negotiation.

    13    6/23/04 14:55 Shiki
    Revised to support Ethernet and other network devices in a uniform way.

    12    04/06/17 9:05 Ueno_kyu
    Fixed ReceiveConfigureRequest().

    11    04/06/15 15:02 Ueno_kyu
    Added support for modem.

    9     10/23/03 20:31 Shiki
    Added support for PPPoE service name.

    8     9/25/03 10:15 Shiki
    Fixed Down() to remove the auth protocol from the PPP stack. Some ISP's
    PPPoE AC aborts the CHAP authentication in the middle and restarts the
    LCP configuration for the PAP authentication. Therefore, both CHAP and
    PAP protocols are activated in a single session.

    7     7/01/03 14:03 Shiki
    Restructured the PPP layer structure.

    6     10/07/02 10:27 Shiki
    Added support for IPGetConfigError().

    5     10/01/02 9:59 Shiki
    Added const keywords to relevant function prototypes.

    4     8/05/02 10:07 Shiki
    Added support for CHAP.

    3     8/01/02 17:05 Shiki
    Fixed ReceiveConfigureRequest() to correctly nack options.
    Implemented PPPDumpLCP().

    2     8/01/02 11:28 Shiki
    Fixed to set interface MTU to PPP MRU.

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

#define MIN_MRU         128 // pppd

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

// LCP Configuration Options
enum
{
    MaximumReceiveUnit                  = 1,    // 1454
    AsyncControlCharacterMap            = 2,    // RFC 1662
    AuthenticationProtocol              = 3,    // use
    QualityProtocol                     = 4,    // don't use
    MagicNumber                         = 5,    // use
    ProtocolFieldCompression            = 7,    // don't use
    AddressandControlFieldCompression   = 8,    // don't use
    FCSAlternative                      = 9     // don't use
};

static const LCPOptPAP  OptPAP  =
{
    AuthenticationProtocol,
    4,
    PPP_PAP
};

static const LCPOptCHAP OptCHAP =
{
    AuthenticationProtocol,
    5,
    PPP_CHAP,
    PPP_CHAP_MD5
};

void PPPDumpLCP(LCPHeader* lcp)
{
    u8*     data = ((u8*) lcp + LCP_HLEN);
    u16     len = (u16) (lcp->len - LCP_HLEN);
    LCPOpt* opt;

    OSReport("LCP: code=%d id=%d len=%d\n", lcp->code, lcp->id, lcp->len);
    switch (lcp->code)
    {
      case ConfigureRequest:
      case ConfigureAck:
      case ConfigureNak:
      case ConfigureReject:
        break;
      default:
        return;
        break;
    }
    for (opt = (LCPOpt*) data;
         opt < (LCPOpt*) (data + len);
         (u8*) opt += opt->len)
    {
        switch (opt->type)
        {
          case MaximumReceiveUnit:
            OSReport(" MaximumReceiveUnit(%d)", opt->type);
            break;
          case AsyncControlCharacterMap:
            OSReport(" AsyncControlCharacterMap(%d)", opt->type);
            break;
          case AuthenticationProtocol:
            OSReport(" AuthenticationProtocol(%d)", opt->type);
            break;
          case QualityProtocol:
            OSReport(" QualityProtocol(%d)", opt->type);
            break;
          case MagicNumber:
            OSReport(" MagicNumber(%d)", opt->type);
            break;
          case ProtocolFieldCompression:
            OSReport(" ProtocolFieldCompression(%d)", opt->type);
            break;
          case AddressandControlFieldCompression:
            OSReport(" AddressandControlFieldCompression(%d)", opt->type);
            break;
          case FCSAlternative:
            OSReport(" FCSAlternative(%d)", opt->type);
            break;
          default:
            OSReport(" Unknown(%d)", opt->type);
            break;
        }
    }
}

static BOOL IsAccmAcceptable(u32 accm)
{
    u32 diff;

    diff =  (PPP_ACCM_ACCEPTABLE ^ accm);

    if (diff & (u32) PPP_ACCM_ACCEPTABLE)
    {
        return FALSE;
    }

    return TRUE;
}

static int ReceiveConfigureRequest(PPPConf* conf, LCPHeader* lcp)
{
    u8*     data = ((u8*) lcp + LCP_HLEN);
    u16     len = (u16) (lcp->len - LCP_HLEN);
    LCPOpt* req;
    BOOL    reject = FALSE;
    BOOL    nack   = FALSE;
    u16     mru    = conf->mru;
    u16     auth   = 0;
    u8      algorithm;  // CHAP algorithm
    u32     accm   = conf->accm;
    u32     magic  = 0;
    u32     dupCheck = 0;

    // 1st pass: Set reject and/or nack
    for (req = (LCPOpt*) data;
         req < (LCPOpt*) (data + len);
         (u8*) req += req->len)
    {
        if (data + len < (u8*) req + req->len || req->len < 2)
        {
            return PPP_RCR_INVALID; // Invalid
        }

        switch (req->type)
        {
          case MaximumReceiveUnit:
            if (req->len != 4)
            {
                return PPP_RCR_INVALID; // Invalid
            }
            if (dupCheck & (1u << MaximumReceiveUnit))
            {
                return PPP_RCR_INVALID;
            }
            dupCheck |= (1u << MaximumReceiveUnit);
            mru = *(u16*) ((u8*) req + 2);
            if (mru < MIN_MRU || conf->mru != mru)
            {
                nack = TRUE;
            }
            break;
          case AuthenticationProtocol:
            if (req->len < 4)
            {
                return PPP_RCR_INVALID; // Invalid
            }
            if (dupCheck & (1u << AuthenticationProtocol))
            {
                // An implementation MUST NOT include multiple Authentication-
                // Protocol Configuration Options in its Configure-Request packets.
                // [RFC 1661]
                return PPP_RCR_INVALID;
            }
            dupCheck |= (1u << AuthenticationProtocol);
            auth = *(u16*) ((u8*) req + 2);
            switch (auth)
            {
              case PPP_PAP:  // PAP
                if (req->len != 4)
                {
                    return PPP_RCR_INVALID; // Invalid
                }
                break;
              case PPP_CHAP:
                if (req->len != 5)
                {
                    return PPP_RCR_INVALID; // Invalid
                }
                algorithm = *((u8*) req + 4);
                if (algorithm != PPP_CHAP_MD5)
                {
                    nack = TRUE;
                }
                break;
              default:
                nack = TRUE;
                break;
            }
            break;
          case AsyncControlCharacterMap:
            if (req->len != 6)
            {
                return PPP_RCR_INVALID; // Invalid
            }
            accm = *(u32*) ((u8*) req + 2);
            if (!IsAccmAcceptable(accm))
            {
                nack = TRUE;
            }
            break;
          case MagicNumber:
            if (req->len != 6)
            {
                return PPP_RCR_INVALID; // Invalid
            }
            if (dupCheck & (1u << MagicNumber))
            {
                return PPP_RCR_INVALID;
            }
            dupCheck |= (1u << MagicNumber);
            magic = *(u32*) ((u8*) req + 2);
            if (magic == 0)
            {
                // A Magic-Number of zero is illegal and MUST always be
                // Nak'd, if it is not Rejected outright. [RFC 1661]
                nack = TRUE;
            }
            else if (magic == conf->magic)
            {
                // Is the link looped-back?
                nack = TRUE;
            }
            break;

          case QualityProtocol:
            if (req->len < 4)
            {
                return PPP_RCR_INVALID; // Invalid
            }
            if (dupCheck & (1u << QualityProtocol))
            {
                return PPP_RCR_INVALID;
            }
            dupCheck |= (1u << QualityProtocol);
            // Reject it
            reject = TRUE;
            break;
          case ProtocolFieldCompression:
            if (req->len != 2)
            {
                return PPP_RCR_INVALID; // Invalid
            }
            if (dupCheck & (1u << ProtocolFieldCompression))
            {
                return PPP_RCR_INVALID;
            }
            dupCheck |= (1u << ProtocolFieldCompression);
            // Reject it
            reject = TRUE;
            break;
          case AddressandControlFieldCompression:
            if (req->len != 2)
            {
                return PPP_RCR_INVALID; // Invalid
            }
            if (dupCheck & (1u << AddressandControlFieldCompression))
            {
                return PPP_RCR_INVALID;
            }
            dupCheck |= (1u << AddressandControlFieldCompression);
            // Reject it
            reject = TRUE;
            break;

          default:
            // Reject it
            reject = TRUE;
            break;
        }
    }

    // 2nd pass: process reject or nack in order
    if (reject)
    {
        req = (LCPOpt*) data;
        while (req < (LCPOpt*) (data + len))
        {
            switch (req->type)
            {
              case MaximumReceiveUnit:
              case AuthenticationProtocol:
              case MagicNumber:
              case AsyncControlCharacterMap:
                // Delete req as not to reject
                len = PPPDeleteOpt(data, len, req);
                continue;
                break;
            }
            // Keep req to reject
            (u8*) req += req->len;
        }
        lcp->len = (u16) (LCP_HLEN + len);
        return PPP_RCR_REJECT;
        // NOT REACHED HERE
    }
    else if (nack && conf->failure <= 0)
    {
        req = (LCPOpt*) data;
        while (req < (LCPOpt*) (data + len))
        {
            switch (req->type)
            {
              case MaximumReceiveUnit:
                if (MIN_MRU <= mru)
                {
                    // Delete req as not to reject
                    len = PPPDeleteOpt(data, len, req);
                    continue;
                }
                break;
              case AuthenticationProtocol:
                switch (auth)
                {
                  case PPP_PAP:
                    // Delete req as not to reject
                    len = PPPDeleteOpt(data, len, req);
                    continue;
                    break;
                  case PPP_CHAP:
                    if (algorithm == PPP_CHAP_MD5)
                    {
                        // Delete req as not to reject
                        len = PPPDeleteOpt(data, len, req);
                        continue;
                    }
                    break;
                }
                break;
              case MagicNumber:
                // Delete req as not to reject
                len = PPPDeleteOpt(data, len, req);
                continue;
                break;
              case AsyncControlCharacterMap:
                if (IsAccmAcceptable(accm))
                {
                    // Delete req as not to reject
                    len = PPPDeleteOpt(data, len, req);
                    continue;
                }
                break;
            }
            // Keep req to reject
            (u8*) req += req->len;
        }
        lcp->len = (u16) (LCP_HLEN + len);
        return PPP_RCR_REJECT;
        // NOT REACHED HERE
    }
    else if (nack)
    {
        req = (LCPOpt*) data;
        while (req < (LCPOpt*) (data + len))
        {
            switch (req->type)
            {
              case MaximumReceiveUnit:
                if (mru < MIN_MRU || conf->mru != mru)
                {
                    mru = (u16) (MAX(MIN_MRU, MIN(mru, conf->mru)));
                    *(u16*) ((u8*) req + 2) = mru;
                    conf->mru = mru;
                    // Keep to nack
                    (u8*) req += req->len;
                    continue;
                }
                break;
              case AuthenticationProtocol:
                switch (auth)
                {
                  case PPP_PAP:
                    break;
                  case PPP_CHAP:
                    if (algorithm != PPP_CHAP_MD5)
                    {
                        *((u8*) req + 4) = PPP_CHAP_MD5;
                        // Keep to nack
                        (u8*) req += req->len;
                        continue;
                    }
                    break;
                  default:
                    len = PPPDeleteOpt(data, len, req);
                    len = PPPInsertOpt(data, len, req, (LCPOpt*) &OptPAP);
                    // Keep to nack
                    (u8*) req += req->len;
                    continue;
                    break;
                }
                break;
              case MagicNumber:
                if (magic == 0 || magic == conf->magic)
                {
                    do {
                        magic = (u32) IPRand48(conf->interface);
                    } while (magic == 0 || magic == conf->magic);
                    conf->magicPeer = magic;
                    // Keep to nack
                    *((u32*) ((u8*) req + 2)) = magic;
                    (u8*) req += req->len;
                    continue;
                }
                break;
              case AsyncControlCharacterMap:
                if (!IsAccmAcceptable(accm))
                {
                    // Keep to nack
                    *((u32*) ((u8*) req + 2)) = accm | (u32) PPP_ACCM_ACCEPTABLE;
                    (u8*) req += req->len;
                    continue;
                }
                break;
            }
            // Delete option to accept
            len = PPPDeleteOpt(data, len, req);
        }
        lcp->len = (u16) (LCP_HLEN + len);
        return PPP_RCR_NACK;
        // NOT REACHED HERE
    }
    else
    {
        conf->mru = mru;
        conf->auth = auth;
        conf->magicPeer = magic;
        if (conf->accm != accm)
        {
            conf->accm = accm;
            IPSetAccm(&conf->interface->hdlc, conf->accm, IP_HDLC_ACCM_RECV);
        }
        return PPP_RCR_ACCEPT;
        // NOT REACHED HERE
    }
}

static BOOL ReceiveConfigureAck(PPPConf* conf, LCPHeader* lcp)
{
    // Check configuration options exactly match those of the last transmitted Configure-Request.
    if (lcp->len != LCP_HLEN + conf->len ||
        memcmp(((u8*) lcp + LCP_HLEN), conf->data, conf->len) != 0)
    {
        return FALSE;
    }
    return TRUE;
}

static BOOL ReceiveConfigureNak(PPPConf* conf, LCPHeader* lcp)
{
    u8*     data = ((u8*) lcp + LCP_HLEN);
    u16     len = (u16) (lcp->len - LCP_HLEN);
    LCPOpt* cur = (LCPOpt*) conf->data;
    LCPOpt* nak;
    LCPOpt* end;
    u16     mru;
    u32     magic;

    // Verify nak
    for (nak = (LCPOpt*) data;
         nak < (LCPOpt*) (data + len);
         (u8*) nak += nak->len)
    {
        if (data + len < (u8*) nak + nak->len || nak->len < 2)
        {
            return PPP_RCR_INVALID; // Invalid
        }

        switch (nak->type)
        {
          case MaximumReceiveUnit:
            if (nak->len != 4)
            {
                return FALSE;   // Invalid
            }
            mru = *(u16*) ((u8*) nak + 2);
            if (mru < MIN_MRU)
            {
                return FALSE;   // Invalid
            }
            break;
          case MagicNumber:
            if (nak->len != 6)
            {
                return FALSE;   // Invalid
            }
            break;
          default:
            // Ignore
            break;
        }
    }

    // Replace cur with nak
    for (nak = (LCPOpt*) data;
         nak < (LCPOpt*) (data + len);
         (u8*) nak += nak->len)
    {
        switch (nak->type)
        {
          case MaximumReceiveUnit:
            break;
          case MagicNumber:
            if (conf->magic)
            {
                break;
            }
            // FALL THROUGH
          default:
            // Ignore
            continue;
            break;
        }

        end = (LCPOpt*) (conf->data + conf->len);
        for (cur = (LCPOpt*) conf->data; cur < end; (u8*) cur += cur->len)
        {
            if (nak->type == cur->type)
            {
                // Replace cur with nak
                switch (cur->type)
                {
                  case MaximumReceiveUnit:
                    mru = *(u16*) ((u8*) nak + 2);
                    mru = (u16) (MAX(MIN_MRU, MIN(mru, conf->mru)));
                    conf->mru = mru;
                    *(u16*) ((u8*) cur + 2) = mru;
                    break;
                  case MagicNumber:
                    magic = *(u32*) ((u8*) nak + 2);
                    while (magic == 0 || conf->magic == magic || conf->magicPeer == magic)
                    {
                        magic = (u32) IPRand48(conf->interface);
                    }
                    *(u32*) ((u8*) cur + 2) = magic;
                    if (conf->magic)
                    {
                        conf->magic = magic;
                    }
                    break;
                  default:
                    break;
                }
                break;
            }
        }
        if (end <= cur)
        {
            // Append nak
            memmove(end, nak, nak->len);
            conf->len += nak->len;
        }
    }

    return TRUE;
}

static BOOL ReceiveConfigureReject(PPPConf* conf, LCPHeader* lcp)
{
    u8*     data = ((u8*) lcp + LCP_HLEN);
    u16     len = (u16) (lcp->len - LCP_HLEN);
    LCPOpt* cur;
    LCPOpt* rej;
    LCPOpt* end;

    // Verify reject options (quotes from [RFC 1661]):
    //
    // 1. the Configuration Options MUST NOT be reordered or modified in any
    //    way.
    // 2. the Configuration Options in a Configure-Reject MUST
    //    be a proper subset of those in the last transmitted Configure-
    //    Request.
    cur = (LCPOpt*) conf->data;
    end = (LCPOpt*) (conf->data + conf->len);
    for (rej = (LCPOpt*) data;
         rej <= (LCPOpt*) (data + len);
         (u8*) rej += rej->len)
    {
        if (data + len < (u8*) rej + rej->len || rej->len < 2)
        {
            return PPP_RCR_INVALID; // Invalid
        }

        while (rej->type != cur->type)
        {
            (u8*) cur += cur->len;
            if (end <= cur)
            {
                return FALSE;
            }
        }
        if (rej->len != cur->len)
        {
            return FALSE;
        }
    }
    if (rej < (LCPOpt*) (data + len))
    {
        return FALSE;
    }

    // Update request options
    cur = (LCPOpt*) conf->data;
    for (rej = (LCPOpt*) data;
         rej < (LCPOpt*) (data + len);
         (u8*) rej += rej->len)
    {
        end = (LCPOpt*) (conf->data + conf->len);
        while (rej->type != cur->type)
        {
            (u8*) cur += cur->len;
            ASSERT(cur < end);
        }

        ASSERT(rej->len == cur->len);

        if (cur->type == MagicNumber)
        {
            conf->magic = 0;
        }

        // Delete cur
        conf->len = PPPDeleteOpt(conf->data, conf->len, cur);
    }
    return TRUE;
}

static BOOL Up(PPPConf* conf)
{
    IPInterface* interface;
    PPPConf* auth;

    // Set interface MTU to PPP MRU
    interface = conf->interface;
    if (conf->mru < interface->mtu)
    {
        interface->mtu = conf->mru;
    }

    // PPPConf is used for PAP and CHAP as well.
    // Here, intert auth conf between NCP and IPCP and open it.
    switch (conf->auth)
    {
      case PPP_PAP:
        auth = &PPPAuthConf;
        PAPInit(auth, interface);
        break;
      case PPP_CHAP:
        auth = &PPPAuthConf;
        CHAPInit(auth, interface);
        break;
      default:
        auth = NULL;
        break;
    }

    if (auth)
    {
        IFEnqueueAfter(PPPConf*, &interface->ppp, conf, auth, link);
        PPPOpen(auth);
    }

    return TRUE;
}

static BOOL Down(PPPConf* conf)
{
    PPPConf* auth;
    IPInterface* interface = conf->interface;

    auth = (PPPConf*) IFQueryLinkNext(conf, link);
    if (auth == &PPPAuthConf)
    {
        // Do not call PPPClose() for auth as it closes the
        // entire PPP stack.
        IFDequeueItem(PPPConf*, &interface->ppp, auth, link);
    }

    IPResetAccm(&interface->hdlc, IP_HDLC_ACCM_SEND);
    return TRUE;
}

static BOOL Started(PPPConf* conf)
{
    IPInterface* interface;

    interface = conf->interface;
    return interface->started(interface);
}

static BOOL Finished(PPPConf* conf)
{
    IPInterface* interface;

    interface = conf->interface;
    conf->magic = (u32) IPRand48(interface);    // set 0 if not negotiate
    conf->magicPeer = 0;
    conf->accm = PPP_ACCM_DEFAULT;
    IPResetAccm(&interface->hdlc, IP_HDLC_ACCM_RECV);
    IPResetAccm(&interface->hdlc, IP_HDLC_ACCM_SEND);
    return interface->finished(interface);
}

BOOL PPPInitLCP(PPPConf* conf, IPInterface* interface)
{
    memset(conf, 0, sizeof(PPPConf));
    conf->protocol = PPP_LCP;
    OSCreateAlarm(&conf->alarm);
    conf->interface = interface;

    conf->receiveConfigureRequest = ReceiveConfigureRequest;
    conf->receiveConfigureAck     = ReceiveConfigureAck;
    conf->receiveConfigureNak     = ReceiveConfigureNak;
    conf->receiveConfigureReject  = ReceiveConfigureReject;

    conf->up       = Up;
    conf->down     = Down;
    conf->started  = Started;
    conf->finished = Finished;

    conf->mru      = 1500;  // default
    conf->magic    = (u32) IPRand48(interface); // set 0 if not negotiate
    conf->accm     = PPP_ACCM_DEFAULT;

    if (conf->magic != 0)
    {
        LCPOpt* opt = (LCPOpt*) ((u8*) conf->data + conf->len);
        opt->type = MagicNumber;
        opt->len = 6;
        *(u32*) ((u8*) opt + 2) = conf->magic;
        conf->len += opt->len;
    }

    return TRUE;
}
