d1 833
a833 796
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API -- PPP Over Ethernet (PPPoE) [RFC 2516]
  File:     IPPPPoE.c

  Copyright 2002-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip6/src/IPPPPoE.c $
    
    15    12/15/05 18:42 Shiki
    Clean up.

    14    05/12/07 13:27 Ueno_kyu
    Updated copyright.

    13    05/12/07 13:22 Ueno_kyu
    Modified PPPoEOpen() to add LCP MRU option to an initial LCP configure
    request.

    12    05/12/05 11:16 Ueno_kyu
    Modified PPPoEOpen() to set mru to mtu - PPPoE_HLEN - 2.

    11    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    14    04/10/14 13:11 Ueno_kyu
    Modified PPPoEOut() to set IF_FLAG_UNICAST or IF_FLAG_BROADCAST to
    datagram->flag.

    13    6/29/04 11:06 Shiki
    Modified the use of IF_FLAG_* for better loopback support. Now
    IF_FLAG_* is set to IFDatagram{} before sending the packet.

    12    6/23/04 14:55 Shiki
    Revised to support Ethernet and other network devices in a uniform way.

    10    10/29/03 21:58 Shiki
    Revised using IFInitDatagram().

    9     10/23/03 20:31 Shiki
    Added support for PPPoE service name.

    8     7/31/03 16:21 Shiki
    Revised PPPoEOut () to double the waiting period after each timeout.
    Revised TimeoutCallback() not to retry PADT as the current home
    broadband routers do.

    7     7/01/03 14:03 Shiki
    Restructured the PPP layer structure.

    6     5/15/03 15:54 Shiki
    Modified to clear the IF_DATAGRAM_FLAG_DROP bit in IFDatagram.flag
    before sending a Ethernet packet.

    5     10/07/02 10:45 Shiki
    Added support for IPGetConfigError().
    Fixed PPPoETerminate() to restore interface->out no matter what.

    4     10/01/02 9:59 Shiki
    Added const keywords to relevant function prototypes.

    3     8/01/02 17:07 Shiki
    Refined PPPoEDumpPacket().
    Fixed PPPoEOut() to use constant 3 second timeout.
    Implemented PPPoEGetACName().

    2     8/01/02 11:31 Shiki
    Bug fixes.

    1     7/31/02 16:12 Shiki
    Initial check-in.
  $NoKeywords: $

                                 -------
    +-------------------------->|       |<----------------------+
    |    Terminate (PADT)/      | INIT  |                       |
    |    Send Terminate (PADT)  |       |                       |
    |                            -------                        |
    |                               |                           |
    |                           -/Send Initiation (PADI)        |
    |                               |                           |
    |                               v                           |
    |                          -----------                      |
    |                         |           |                     |
    |                         | SELECTING |<----+               |
    |                         |           |     |Offer (PADO)/  |
    |                          -----------      |Collect        |
    |                               |   |       |  replies      |
    |              +----------------+   +-------+               |
    |              v   Select offer/                            |
    |    ------------  Send Session Request (PADR)              |
    |   |            |                                          |
    |   | REQUESTING |                                          |
    |   |            |                                          |
    |    ------------                                           |
    |              |                                            |
    |        Confirmation (PADS)/Record SESSION_ID              |
    |              |                                            |
    |              v                                            |
    |           -------                                         |
    |          |       |                                        |
    +----------| BOUND |                                        |
               |       |                                        |
                -------                                         |
                   |                                            |
                   |          -------------                     |
                   |         |             |                    |
                   +-------->| TERMINATING |--------------------+
             PPPClose/-      |             |      Send Terminate (PADT)/-
                              -------------

                State-transition diagram for PPPoE clients

 *---------------------------------------------------------------------------*/

#include <stddef.h>
#include <dolphin/os.h>
#include <dolphin/socket.h>
#include <dolphin/ip/IPPpp.h>
#include <private/eth.h>
#include "IPPrivate.h"
#include "IPPPPConf.h"

#define RXMIT_INIT  3   // [sec]
#define RXMIT_MAX   4   // [times]

// TAG_TYPES and TAG_VALUES
enum
{
   EndOfList =        0x0000,
   ServiceName =      0x0101,
   ACName =           0x0102,
   HostUniq =         0x0103,
   ACCookie =         0x0104,
   VendorSpecific =   0x0105,
   RelaySessionId =   0x0110,
   ServiceNameError = 0x0201,
   ACSystemError =    0x0202,
   GenericError =     0x0203
};

typedef struct PPPoEConf
{
    u8           code;
    u16          session;
    u16          last;          // last session number
    u8           lastmac[ETH_ALEN];

    OSAlarm      alarm;
    u8           mac[ETH_ALEN];
    u8           pppoe[1500];
    u16          len;
    u16          rxmit;

    IPInterface* interface;
    void       (*out)( IPInterface* interface, IFDatagram* datagram );
} PPPoEConf;

static PPPoEConf Conf =
{
    0x00,       // code
    0xffff,     // sessoin
    0xffff      // last
};

PPPConf   PPPLcpConf;
PPPConf   PPPIpcpConf;
PPPConf   PPPAuthConf;

static void TimeoutCallback(OSAlarm* alarm, OSContext* context);

static void DumpTags(PPPoEHeader* pppoe)
{
    PPPoETag* tag;

    for (tag = (PPPoETag*) ((u8*) pppoe + PPPoE_HLEN);
         (u8*) tag < (u8*) pppoe + pppoe->len && tag->type != EndOfList;
         (u8*) tag += PPPoE_TAGLEN(tag))
    {
        switch (tag->type)
        {
          case EndOfList:
            OSReport(" EndOfList(%x)", tag->type);
            break;
          case ServiceName:
            OSReport(" ServiceName(%x)", tag->type);
            break;
          case ACName:
            OSReport(" ACName(%x:%*.*s)", tag->type, tag->len, tag->len, (u8*) tag + 4);
            break;
          case HostUniq:
            OSReport(" HostUniq(%x)", tag->type);
            break;
          case ACCookie:
            OSReport(" ACCookie(%x)", tag->type);
            break;
          case VendorSpecific:
            OSReport(" VendorSpecific(%x)", tag->type);
            break;
          case RelaySessionId:
            OSReport(" RelaySessionId(%x)", tag->type);
            break;
          case ServiceNameError:
            OSReport(" ServiceNameError(%x:%*.*s)", tag->type, tag->len, tag->len, (u8*) tag + 4);
            break;
          case ACSystemError:
            OSReport(" ACSystemError(%x:%*.*s)", tag->type, tag->len, tag->len, (u8*) tag + 4);
            break;
          case GenericError:
            OSReport(" GenericError(%x:%*.*s)", tag->type, tag->len, tag->len, (u8*) tag + 4);
            break;
          default:
            OSReport(" Unknown(%x)", tag->type);
            break;
        }
    }
}

void PPPoEDumpPacket(PPPoEHeader* pppoe)
{
    // u8* tag;
    u16 proto;

    OSReport("pppoe: ver=%d type=%d code=%04x session=%d len=%d: ",
             (pppoe->vertype & 0xf0) >> 4,
             pppoe->vertype & 0x0f,
             pppoe->code,
             pppoe->session,
             pppoe->len);

    switch (pppoe->code)
    {
      case PPPoE_SESS:
        proto = *(u16*) ((u8*) pppoe + PPPoE_HLEN);
        switch (proto)
        {
          case PPP_LCP:
            PPPDumpLCP((LCPHeader*) ((u8*) pppoe + PPPoE_HLEN + 2));
            break;
          default:
            OSReport("SESS: proto=%x", proto);
            break;
        }
        break;
      case PPPoE_PADI:
        OSReport("PADI: ");
        DumpTags(pppoe);
        break;
      case PPPoE_PADO:
        OSReport("PADO: ");
        DumpTags(pppoe);
        break;
      case PPPoE_PADR:
        OSReport("PADR: ");
        DumpTags(pppoe);
        break;
      case PPPoE_PADS:
        OSReport("PADS: ");
        DumpTags(pppoe);
        break;
      case PPPoE_PADT:
        OSReport("PADT: ");
        DumpTags(pppoe);
        break;
      default:
        OSReport("Unknown(%x): ", pppoe->code);
        break;
    }

    OSReport("\n");
}

static void OutPADT(IPInterface* interface, u8* mac, u16 session)
{
    BOOL         enabled;
    IFDatagram*  datagram;
    PPPoEHeader* pppoe;
    PPPoEConf*   conf = &Conf;

    enabled = OSDisableInterrupts();
    datagram = interface->alloc(interface, sizeof(IFDatagram) + sizeof(PPPoEHeader));
    pppoe = (PPPoEHeader*) ((u8*) datagram + sizeof(IFDatagram));
    if (datagram)
    {
        IFInitDatagram(datagram, ETH_PPPoE_DISCOVERY, 1);

        pppoe->vertype = PPPoE_VERTYPE;
        pppoe->code = PPPoE_PADT;
        pppoe->session = session;
        pppoe->len = 0;

        datagram->vec[0].data = pppoe;
        datagram->vec[0].len  = PPPoE_HLEN;

        memmove(datagram->hwAddr, mac, ETH_ALEN);
        conf->out(interface, datagram);
    }
    OSRestoreInterrupts(enabled);
}

static void PPPoEOut(IPInterface* interface, PPPoEConf* conf)
{
    BOOL         enabled;
    IFDatagram*  datagram;
    PPPoEHeader* pppoe;

    enabled = OSDisableInterrupts();

    // Set alarm here so we can retry even if alloc() is failed.
    OSCancelAlarm(&conf->alarm);
    OSSetAlarm(&conf->alarm,
               OSSecondsToTicks((OSTime) (RXMIT_INIT << conf->rxmit)),
               TimeoutCallback);

    if (conf->code == PPPoE_PADT)
    {
        OutPADT(interface, conf->mac, conf->session);
    }
    else
    {
        datagram = interface->alloc(interface, sizeof(IFDatagram));
        pppoe = (PPPoEHeader*) conf->pppoe;
        pppoe->code    = conf->code;
        pppoe->session = conf->session;
        pppoe->len     = conf->len;
        if (datagram)
        {
            IFInitDatagram(datagram, ETH_PPPoE_DISCOVERY, 1);

            datagram->vec[0].data = pppoe;
            datagram->vec[0].len  = PPPoE_HLEN + conf->len;

            memmove(datagram->hwAddr, conf->mac, ETH_ALEN);

            if (datagram->hwAddr[0] & 0x01)
            {
                datagram->flag |= IF_FLAG_BROADCAST;
            }
            else
            {
                datagram->flag |= IF_FLAG_UNICAST;
            }

            conf->out(interface, datagram);
        }
    }

    OSRestoreInterrupts(enabled);
}

static void PPPoEQuit(PPPoEConf* conf, u16 last)
{
    PPPConf* lcp;

    OSCancelAlarm(&conf->alarm);
    conf->code = 0;
    conf->session = 0xffff;
    conf->last = last;
    if (last != 0xffff)
    {
        memmove(conf->lastmac, conf->mac, ETH_ALEN);
    }
    conf->interface->mtu = 1500;

    // Select LCP
    lcp = (PPPConf*) IFQueryQueueHead(&conf->interface->ppp);
    if (lcp)
    {
        PPPDown(lcp);
    }
}

static void TimeoutCallback(OSAlarm* alarm, OSContext* context)
{
    #pragma unused(context)
    PPPoEConf* conf;

    conf = (PPPoEConf*) ((u8*) alarm - offsetof(PPPoEConf, alarm));
    ++conf->rxmit;

    if (conf->code == PPPoE_PADT)
    {
        PPPoEQuit(conf, 0xffff);
    }
    else if (RXMIT_MAX <= conf->rxmit)
    {
        IPSetConfigError(conf->interface, IP_ERR_PPPoE_TIMEOUT);
        PPPoEQuit(conf, 0xffff);
    }
    else
    {
        PPPoEOut(conf->interface, conf);
    }
}

static void Out(IPInterface* interface, IFDatagram* datagram)
{
    BOOL         enabled;
    PPPoEConf*   conf = &Conf;
    PPPoEHeader* pppoe;
    IFVec*       vec;
    IFVec*       end;

    enabled = OSDisableInterrupts();
    pppoe = (PPPoEHeader*) datagram->prefix;
    // Prepare PPPoE Header
    pppoe->vertype = PPPoE_VERTYPE;
    pppoe->code    = conf->code;
    pppoe->session = conf->session;
    pppoe->len     = 0;
    for (vec = datagram->vec, end = &datagram->vec[datagram->nVec];
         vec < end;
         ++vec)
    {
        pppoe->len += (u16) vec->len;
    }
    switch (datagram->type)
    {
      case ETH_IP:
        // Insert PPPoE Header and PPP Protocol field for IP
        *(u16*) &datagram->prefix[PPPoE_HLEN] = PPP_IP;
        pppoe->len += 2;
        datagram->prefixLen = PPPoE_HLEN + 2;
        datagram->type = ETH_PPPoE_SESSION;
        break;
      case ETH_PPPoE_SESSION:
        // Insert PPPoE Header only
        datagram->prefixLen = PPPoE_HLEN;
        break;
      default:
        datagram->prefixLen = 0;
        break;
    }
    if (datagram->type == ETH_PPPoE_SESSION)
    {
        memmove(datagram->hwAddr, conf->mac, ETH_ALEN);
    }

    if (memcmp(datagram->hwAddr, ETHAddrBroadcast, ETH_ALEN) == 0)
    {
        datagram->flag |= IF_FLAG_BROADCAST;
    }
    else
    {
        datagram->flag |= IF_FLAG_UNICAST;
    }

    conf->out(interface, datagram);
    OSRestoreInterrupts(enabled);
}

void PPPoEInit(IPInterface* interface, const char* serviceName)
{
    interface->serviceName = serviceName;
}

BOOL PPPoEOpen(IPInterface* interface)
{
    PPPoEHeader* pppoe;
    PPPoETag*    tag;
    PPPoEConf*   conf = &Conf;
    size_t       len;
    LCPOptMRU*   opt;

    if (conf->session != 0xffff)
    {
        return FALSE;
    }

    interface = interface ? interface : &__IFDefault;
    if (interface->serviceName)
    {
        len = strlen(interface->serviceName);
        if (interface->mtu - PPPoE_HLEN - 4 < len)
        {
            return FALSE;
        }
    }
    else
    {
        len = 0;    // Indicates that any service is acceptable.
    }

    conf->code = PPPoE_PADI;
    conf->len = (u16) (2 + 2 + len);    // for Service-Name
    conf->session = 0x0000;
    memset(conf->mac, 0xff, ETH_ALEN);  // broadcast
    OSCreateAlarm(&conf->alarm);
    conf->rxmit = 0;                    // 5 [sec]

    pppoe = (PPPoEHeader*) conf->pppoe;
    pppoe->vertype = PPPoE_VERTYPE;
    pppoe->code = conf->code;
    pppoe->session = conf->session;
    pppoe->len = conf->len;

    tag = (PPPoETag*) ((u8*) pppoe + PPPoE_HLEN);
    tag->type = ServiceName;
    tag->len = (u16) len;
    if (0 < len)
    {
        memmove(&tag[1], interface->serviceName, len);
        // NOT NULL terminated [RFC 2516]
    }

    conf->interface = interface;
    conf->out = interface->out;
    interface->out = Out;

    PPPLcpConf.mru = (u16) (interface->mtu - PPPoE_HLEN - 2);  // 2 for PPP protocol number size
    if (PPPLcpConf.mru != 1500)
    {
        opt = (LCPOptMRU*) ((u8*) PPPLcpConf.data + PPPLcpConf.len);
        opt->type = 1; // MaximumReceiveUnit
        opt->len = 4;
        opt->mru = PPPLcpConf.mru;
        PPPLcpConf.len += opt->len;
    }
    PPPoEOut(interface, conf);

    return TRUE;
}

BOOL PPPoETerminate(IPInterface* interface)
{
    PPPoEConf* conf = &Conf;
    PPPConf*   lcp;

    interface = interface ? interface : &__IFDefault;

    // Select LCP
    lcp = (PPPConf*) IFQueryQueueHead(&interface->ppp);

    if (lcp != NULL &&
        conf->session != 0xffff &&
        conf->code == PPPoE_SESS) // In session stage
    {
        conf->code  = PPPoE_PADT;
        conf->rxmit = 0;
        PPPoEOut(interface, conf);
    }

    if (interface->out == Out)
    {
        interface->out = conf->out;
    }

    return TRUE;
}

// XXX check len
static s32 ParseTags(PPPoEConf* conf, PPPoEHeader* pppoe)
{
    BOOL      result;
    PPPoETag* tag;
    BOOL      cookie;
    BOOL      acname;
    u16       confLen;

    result = IP_ERR_NONE;
    acname = cookie = FALSE;
    confLen = conf->len;
    for (tag = (PPPoETag*) ((u8*) pppoe + PPPoE_HLEN);
         (u8*) tag < (u8*) pppoe + pppoe->len && tag->type != EndOfList;
         (u8*) tag += PPPoE_TAGLEN(tag))
    {
        switch (tag->type)
        {
          case EndOfList:
            break;
          case ServiceName:
            break;
          case ACName:
            if (!acname && conf->code == PPPoE_PADI)
            {
                // Save ACname
                acname = TRUE;
                memmove(conf->pppoe + PPPoE_HLEN + confLen,
                        tag,
                        PPPoE_TAGLEN(tag));
                confLen += PPPoE_TAGLEN(tag);
            }
            break;
          case HostUniq:
            break;
          case ACCookie:
            if (!cookie && conf->code == PPPoE_PADI)
            {
                // Save cookie
                cookie = TRUE;
                memmove(conf->pppoe + PPPoE_HLEN + confLen,
                        tag,
                        PPPoE_TAGLEN(tag));
                confLen += PPPoE_TAGLEN(tag);
            }
            break;
          case VendorSpecific:
            break;
          case RelaySessionId:
            break;
          case ServiceNameError:
            result = IP_ERR_PPPoE_SERVICE_NAME;
            break;
          case ACSystemError:
            result = IP_ERR_PPPoE_AC_SYSTEM;
            break;
          case GenericError:
            result = IP_ERR_PPPoE_GENERIC;
            break;
          default:
            break;
        }
    }
    if (result == IP_ERR_NONE)
    {
        conf->len = confLen;
    }
    return result;
}

// PPPoEIn
void PPPoEIn(IPInterface* interface, ETHHeader* eh, s32 len, u32 flag)
{
    #pragma unused(flag)
    PPPoEConf*   conf = &Conf;
    PPPoEHeader* pppoe = (PPPoEHeader*) ((u8*) eh + ETH_HLEN);
    s32          result;
    PPPConf*     lcp;   // XXX

    // Check length
    if (len < ETH_HLEN + PPPoE_HLEN ||
        len < ETH_HLEN + PPPoE_HLEN + pppoe->len)
    {
        return;
    }

    // Check type and version
    if (pppoe->vertype != PPPoE_VERTYPE)
    {
        return;
    }

    // Select LCP
    lcp = (PPPConf*) IFQueryQueueHead(&interface->ppp);
    if (lcp == NULL)
    {
        return;
    }
    ASSERT(lcp->protocol == PPP_LCP);

    switch (eh->type)
    {
      case ETH_PPPoE_DISCOVERY:
        switch (pppoe->code)
        {
          case PPPoE_PADO:
            if (conf->code != PPPoE_PADI ||   // Not initiating PPPoE session?
                pppoe->session != 0x0000)
            {
                break;
            }

            result = ParseTags(conf, pppoe);
            if (result == IP_ERR_NONE)
            {
                conf->code = PPPoE_PADR;
                conf->rxmit = 0;
                memmove(conf->mac, eh->src, ETH_ALEN);
                PPPoEOut(interface, conf);
            }
            else    // any error
            {
                IPSetConfigError(conf->interface, result);
                PPPoEQuit(conf, 0xffff);
            }
            break;
          case PPPoE_PADS:
            if (conf->code != PPPoE_PADR ||   //  Not requesting PPPoE session?
                memcmp(conf->mac, eh->src, ETH_ALEN) != 0)
            {
                break;
            }

            result = ParseTags(conf, pppoe);
            if (result == IP_ERR_NONE && pppoe->session != 0xffff)
            {
                conf->code = PPPoE_SESS;  // Session stage.
                conf->rxmit = 0;
                conf->session = pppoe->session;

                OSCancelAlarm(&conf->alarm);

                // Signal the Up event to the LCP
                PPPUp(lcp);
            }
            else    // any error
            {
                IPSetConfigError(conf->interface, result);
                PPPoEQuit(conf, 0xffff);
            }
            break;
          case PPPoE_PADT:
            if (pppoe->session == 0xffff)
            {
                break;
            }

            if (pppoe->session == conf->session &&
                memcmp(conf->mac, eh->src, ETH_ALEN) == 0)
            {
                if (conf->code == PPPoE_PADT)
                {
                    // PADT completed.
                    PPPoEQuit(conf, 0xffff);
                    break;
                    // NOT REACHED RERE
                }
                else if (conf->code == PPPoE_SESS)
                {
                    // PADT requested.
                    PPPDown(lcp);
                    PPPoETerminate(interface);
                    IPSetConfigError(conf->interface, IP_ERR_PPP_TERMINATED);
                    PPPoEQuit(conf, conf->session);
                    break;
                    // NOT REACHED RERE
                }
            }

            // PATD replay for possible packet loss
            if (pppoe->session == conf->last &&
                memcmp(conf->lastmac, eh->src, ETH_ALEN) == 0)
            {
                OutPADT(interface, eh->src, pppoe->session);
            }
            break;
        }
        break;
      case ETH_PPPoE_SESSION:
        if (pppoe->session == 0xffff)
        {
            break;
        }

        if (conf->code == PPPoE_SESS && pppoe->code == PPPoE_SESS &&
            memcmp(conf->mac, eh->src, ETH_ALEN) == 0 &&
            pppoe->session == conf->session)
        {
            PPPIn(interface, (u8*) pppoe + PPPoE_HLEN, pppoe->len, flag);
        }
        break;
    }
}

int PPPoEGetACName(IPInterface* interface, char* acname)
{
    #pragma unused(interface)
    BOOL       enabled;
    PPPoEConf* conf = &Conf;
    PPPoETag*  tag;
    int        rc;

    *acname = '\0';

    enabled = OSDisableInterrupts();
    if (conf->session == 0xffff)
    {
        rc = -1;
    }
    else
    {
        rc = 0;
        for (tag = (PPPoETag*) (conf->pppoe + PPPoE_HLEN);
             (u8*) tag < conf->pppoe + conf->len && tag->type != EndOfList;
             (u8*) tag += PPPoE_TAGLEN(tag))
        {
            switch (tag->type)
            {
              case ACName:
                memmove(acname, (u8*) tag + 4, tag->len);
                acname[tag->len] = '\0';
                rc = tag->len;
                goto Done;
                break;
            }
        }
    }
Done:
    OSRestoreInterrupts(enabled);
    return rc;
}
