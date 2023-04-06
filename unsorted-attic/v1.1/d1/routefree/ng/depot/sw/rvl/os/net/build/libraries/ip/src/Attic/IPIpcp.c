d1 536
a536 474
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API -- PPP IPCP [RFC 1332, RFC 1877]
  File:     IPIpcp.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip6/src/IPIpcp.c $
    
    12    2/22/06 16:12 Shiki
    Fixed PPPInitIPCP().

    11    2/22/06 14:13 Shiki
    Fixed to check LTPOpt.len.

    10    2/14/06 9:56 Shiki
    Modified PPPInitIPCP() to use interface->boot address if specified.

    9     1/05/06 17:31 Shiki
    Added comment.

    8     1/05/06 17:10 Shiki
    Modified PPPInitIPCP().

    7     12/19/05 13:45 Shiki
    Revised to check received packets more strictly.

    6     04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    11    04/07/08 16:41 Ueno_kyu
    Revised  IPResetAccm() and IPSetAccm().

    10    04/07/02 17:40 Ueno_kyu
    Bug fix.

    9     04/07/02 15:59 Ueno_kyu
    Modified Up() to set accm for decoding a packet.

    8     04/06/15 16:34 Ueno_kyu
    Cleanup.

    7     04/06/15 15:02 Ueno_kyu
    Added support for modem.

    5     10/07/02 10:26 Shiki
    Revised SOSetResolver()/SOGetResolver() prototypes.

    4     8/05/02 10:09 Shiki
    Revised Up().

    3     8/01/02 11:47 Shiki
    Fixed Up().

    2     8/01/02 11:46 Shiki
    Modified to call SOSetResolver() if possible.

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

// IPCP Configuration Options
enum
{
    IPAddresses             = 1,
    IPCompressionProtocol   = 2,
    IPAddress               = 3,        // Used
    PrimaryDNSAddress       = 129,      // Useable
    PrimaryNBNSAddress      = 130,
    SecondaryDNSAddress     = 131,      // Useable
    SecondaryNBNSAddress    = 132
};

static int ReceiveConfigureRequest(PPPConf* conf, LCPHeader* lcp)
{
    u8*     data = ((u8*) lcp + LCP_HLEN);
    u16     len = (u16) (lcp->len - LCP_HLEN);
    LCPOpt* req;
    BOOL    reject = FALSE;
    BOOL    nack   = FALSE;
    u32     addr   = 0;

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
          case IPAddress:
            if (req->len != 6)
            {
                return PPP_RCR_INVALID; // Invalid
            }
            addr = *(u32*) ((u8*) req + 2);
            if (addr == 0)
            {
                // If all four octets are set to
                // zero, it indicates a request that the peer provide the IP-Address
                // information. [RFC 1332]
                reject = TRUE;
            }
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
              case IPAddress:
                if (addr != 0)
                {
                    // Delete req not to reject
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
    else if (nack && conf->failure <= 0)
    {
        req = (LCPOpt*) data;
        while (req < (LCPOpt*) (data + len))
        {
            switch (req->type)
            {
              case IPAddress:
                if (addr != 0)
                {
                    // Delete req not to reject
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
              default:
                break;
            }
            // Delete to accept
            len = PPPDeleteOpt(data, len, req);
        }
        lcp->len = (u16) (LCP_HLEN + len);
        return PPP_RCR_NACK;
        // NOT REACHED HERE
    }
    else
    {
        conf->remote = addr;
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
    u8*     data = ((u8*) lcp + IPCP_HLEN);
    u16     len = (u16) (lcp->len - LCP_HLEN);
    LCPOpt* cur = (LCPOpt*) conf->data;
    LCPOpt* nak;
    LCPOpt* end;
    u32     addr;

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
          case IPAddress:
          case PrimaryDNSAddress:
          case SecondaryDNSAddress:
            if (nak->len != 6)
            {
                return FALSE;   // Invalid
            }
            break;
          default:
            // Ignore
            continue;
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
          case IPAddress:
          case PrimaryDNSAddress:
          case SecondaryDNSAddress:
            break;
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
                switch (cur->type)
                {
                  case IPAddress:
                  case PrimaryDNSAddress:
                  case SecondaryDNSAddress:
                    addr = *(u32*) ((u8*) nak + 2);
                    *(u32*) ((u8*) cur + 2) = addr;
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

        // Delete cur
        conf->len = PPPDeleteOpt(conf->data, conf->len, cur);
    }
    return TRUE;
}

static BOOL Up(PPPConf* conf)
{
    LCPOpt* opt;
    LCPOpt* end;
    u8* addr = NULL;
    u8* dns1 = NULL;
    u8* dns2 = NULL;
    u8  prev1[IP_ALEN];
    u8  prev2[IP_ALEN];
    PPPConf*     lcp;
    IPInterface* interface = conf->interface;

    end = (LCPOpt*) (conf->data + conf->len);
    for (opt = (LCPOpt*) conf->data; opt < end; (u8*) opt += opt->len)
    {
        switch (opt->type)
        {
          case IPAddress:
            addr = (u8*) opt + 2;
            break;
          case PrimaryDNSAddress:
            dns1 = (u8*) opt + 2;
            break;
          case SecondaryDNSAddress:
            dns2 = (u8*) opt + 2;
            break;
        }
    }

    IPInitRoute(addr, IPLimited, conf->remote ? ((u8*) &conf->remote) : IPLimited);

    if (SOGetResolver((SOInAddr*) prev1, (SOInAddr*) prev2) == 0)
    {
        if (IP_ADDR_EQ(prev1, IPAddrAny) && IP_ADDR_EQ(prev2, IPAddrAny))
        {
            SOSetResolver((SOInAddr*) dns1, (SOInAddr*) dns2);
        }
        else
        {
            // Since the inteface may not have been initialized when
            // SOSetResolver() is called for the 1st time, we call
            // SOSetResolver() again.
            SOSetResolver((SOInAddr*) prev1, (SOInAddr*) prev2);
        }
    }

    // Select LCP
    lcp = (PPPConf*) IFQueryQueueHead(&interface->ppp);
    IPSetAccm(&interface->hdlc, lcp->accm, IP_HDLC_ACCM_SEND);

    return TRUE;
}

static BOOL Down(PPPConf* conf)
{
    #pragma unused( conf )
    IPInitRoute(NULL, NULL, NULL);
    return TRUE;
}

static BOOL Started(PPPConf* conf)
{
    #pragma unused( conf )
    return TRUE;
}

static BOOL Finished(PPPConf* conf)
{
    #pragma unused( conf )
    return TRUE;
}

void PPPInitIPCP(PPPConf* ipcp, IPInterface* interface)
{
    IPCPOpt* opt;

    memset(ipcp, 0, sizeof(PPPConf));
    ipcp->protocol = PPP_IPCP;
    OSCreateAlarm(&ipcp->alarm);
    ipcp->interface = interface;

    ipcp->receiveConfigureRequest = ReceiveConfigureRequest;
    ipcp->receiveConfigureAck     = ReceiveConfigureAck;
    ipcp->receiveConfigureNak     = ReceiveConfigureNak;
    ipcp->receiveConfigureReject  = ReceiveConfigureReject;

    ipcp->up       = Up;
    ipcp->down     = Down;
    ipcp->started  = Started;
    ipcp->finished = Finished;

    // Request IP address
    opt = (IPCPOpt*) &ipcp->data[ipcp->len];
    opt->type = IPAddress;
    opt->len  = 6;
    *(u32*) ((u8*) opt + 2) = 0x00000000;
    if (IP_ADDR_NE(interface->boot, IPAddrAny))
    {
        memcpy((u8*) opt + 2, interface->boot, IP_ALEN);
    }
    ipcp->len += 6;

    // Request primary DNS address
    opt = (IPCPOpt*) &ipcp->data[ipcp->len];
    opt->type = PrimaryDNSAddress;
    opt->len  = 6;
    *(u32*) ((u8*) opt + 2) = 0x00000000;
    ipcp->len += 6;

    // Request secondary DNS address
    opt = (IPCPOpt*) &ipcp->data[ipcp->len];
    opt->type = SecondaryDNSAddress;
    opt->len  = 6;
    *(u32*) ((u8*) opt + 2) = 0x00000000;
    ipcp->len += 6;
}
