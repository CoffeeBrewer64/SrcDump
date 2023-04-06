/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPDns.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPDns.c,v $
  Revision 1.5  2006/04/12 02:42:05  mxu
  change stricmp to strnicmp

  Revision 1.4  2006/04/12 01:45:05  mxu
  change sprintf to snprintf

  Revision 1.3  2006/04/11 01:40:35  mxu
  update to Nintendo's April 05 release

  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    44    3/30/06 18:17 Shiki
    Fixed label handling functions.
    Disabled RFC 2782 (DNS SRV).
    Changed MIN_WAIT to two seconds following RFC 1035.
    Added CheckName().

    43    06/03/29 18:22 Ueno_kyu
    Modified so that a port and retransmission number are not configurable.

    42    06/03/22 11:56 Ueno_kyu
    Modified GetAddrInfoCallback() to check SRV priority and weight.

    41    3/20/06 18:22 Shiki
    Fixed ReceiveCallbackTCP() to call ReceiveCallback() not before
    connection is closed by the peer.
    Modified SendQuery() to shutdown TCP just after the request is sent.
    Fixed GetAddrInfoCallback().

    40    06/03/20 17:34 Ueno_kyu
    Removed LookupAdditionalRecords().

    39    06/03/20 15:45 Ueno_kyu
    Modified LookupAdditionalRecords() to support message compression.

    38    06/03/17 16:53 Ueno_kyu
    Modified LookupAdditionalRecords() to check RR TYPE code.

    37    06/03/17 15:12 Ueno_kyu
    Modified GetAddrInfoCallback() to look up the IP address of a SRV
    target in additional records.

    36    3/15/06 17:03 Shiki
    Fixed TimeoutCallback().

    35    3/15/06 13:48 Shiki
    Fixed SendQuery() and SwitchServer() to cancel info->alarm no matter
    what.

    34    3/15/06 13:23 Shiki
    Fixed ReceiveCallback() to check error code in case OPT is in use.

    33    3/09/06 14:12 Shiki
    Fixed PreGetAddr() and PreGetAddrInfo().

    32    3/08/06 17:07 Shiki
    Revised to support TAHI DNS test.

    31    3/02/06 15:42 Shiki
    Fixed ReceiveCallback() to update __SOResolver.name for
    SOGetHostByName() in case a domain suffix is used.

    30    2/22/06 10:45 Shiki
    Fixed TimeoutCallback().

    29    2/20/06 19:02 Shiki
    Implemented EDNS0.

    28    2/20/06 18:12 Shiki
    Revised to support TCP transport for DNS.
    Modified GetNameInfoCallback() to support for SOHostEnt.aliases.

    27    1/18/06 16:47 Shiki
    Added support for domain name suffix.

    26    2/28/05 18:45 Shiki
    Incorporated Oku-san's bug fix report detected by addrinfo test.

    25    04/12/20 20:00 Ueno_kyu
    Enclosed IPv6 specific codes in #ifdef IP_INET6... #endif blocks.

    24    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    30    04/10/21 16:59 Ueno_kyu
    Enclosed IPv6 specific codes in #ifdef IP_INET6... #endif blocks.

    29    04/10/12 15:21 Ueno_kyu
    Replaced IP6_ALEN as sizeof(SOin6Addr).

    28    04/09/27 17:44 Ueno_kyu
    Fixed IPv6 address length in SOGetAddrInfoAsync() and SOGetAddrInfo().

    27    7/01/04 17:00 Shiki
    Fixed DNSOpen2() to accept NULL parameters.

    26    6/23/04 17:05 Shiki
    Fixed bugs that do not clear cmd->callback when the DNS command is
    processed. DNSGetAddrAsync(), DNSGetNameAsync(), and DNSLookupAsync()
    succeeded only for the first call because of the bugs.

    25    6/21/04 12:04 Shiki
    Revised to support AAAA.

    23    1/13/04 9:12 Shiki
    Fixed SOGetAddrInfoAsync() semantics.

    22    12/10/03 14:20 Shiki
    Fixed CancelAll() to prevent any further cmd from being executed.

    21    12/10/03 11:41 Shiki
    Fixed DNSGo() to check the return value from UDPSendAsync(). If the
    return value is IP_ERR_BUSY, the query must be transmitted later.

    20    12/10/03 11:03 Shiki
    Added support for sips.
    Added more ASSERT()s for debugging.

    19    11/19/03 20:13 Shiki
    Added SOGetAddrInfoAsync().

    18    11/14/03 17:48 Shiki
    Revised SOGetAddrInfo() to retrieve multiple SOAddrInfo{}.

    17    11/14/03 13:10 Shiki
    Added support for SOGetAddrInfo(), SOFreeAddrInfo(), and
    SOGetNameInfo().

    16    10/29/03 4:51p Ueno_kyu
    Modified the dump formats of NAPTR and SRV.

    15    10/29/03 11:49a Ueno_kyu
    Modified DumpResource and added DumpString to dump NAPTR and SRV
    records.

    14    10/29/03 10:35 Shiki
    Fixed DNSLookupAsync() to overwrite dns->id.

    13    5/14/03 15:08 Shiki
    Fixed retransmission timer management bugs.

    12    4/26/02 15:31 Shiki
    Fixed to clear info->callback upon UDPSendAsync() failure.

    11    4/23/02 12:52 Shiki
    Modified Async functions to update *result even if the function failed.

    10    4/17/02 20:15 Shiki
    Defined IP_ERR_SOURCE_QUENCH.

    9     4/17/02 11:04 Shiki
    Fixed RecvCallback() to check the result code strictly.

    8     4/17/02 10:03 Shiki
    Fixed SendCallback() to abort query if the send operation was failed.
    Implemented SOMakeHostent() for the name lookup in socket layer.

    7     4/15/02 13:06 Shiki
    Fixed not to set RD bit in a query if using broadcast or multicast
    address.

    6     4/08/02 16:37 Shiki
    Fixed DNSGetName(),DNSGetAddr() and DNSLookup() to make them return the
    correct return values upon success.

    5     4/08/02 13:50 Shiki
    Revised using new IPSocket{} type.

    4     3/25/02 16:43 Shiki
    Changed DNSGetNameAsync() interface.

    3     3/25/02 15:08 Shiki
    Revised.

    2     3/13/02 9:14 Shiki
    Clean up with IP_ALEN and ETH_ALEN.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifdef IOP_OS
#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h> 
#include <stddef.h>
#include <dolphin/iop_libc.h>
#else
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#endif // IOP_OS

#include <dolphin/socket.h>
#ifdef IOP_OS
#include <dolphin/iop_sock.h>
#endif // IOP_OS

#include "IPPrivate.h"
#ifdef IP_INET6
#include "IP6Private.h"
#endif // IP_INET6

// Define RFC_2782 to enable DNS SRV.
// #define RFC_2782

extern SOResolver  __SOResolver;

// the minimum retransmission interval should be 2-5 seconds [RFC 1035]
#define MIN_WAIT        2    // [sec]
#define MAX_WAIT        17   // [sec]
#define MAX_QUERY       3

static void ReceiveCallbackUDP( UDPInfo* udp, s32 result );
static void ReceiveCallbackTCP( TCPInfo* udp, s32 result );
static void ReceiveCallback( DNSInfo* info, s32 result );
static void TimeoutCallback( OSAlarm* alarm, OSContext* context );

static void SOMakeHostent( SOResolver* res, DNSHeader* dns, s32 result );

static char* TypeStrings[] =
{
    "",
    "A",        // a host address
    "NS",       // an authoritative name server
    "MD",       // a mail destination (Obsolete - use MX)
    "MF",       // a mail forwarder (Obsolete - use MX)
    "CNAME",    // the canonical name for an alias
    "SOA",      // marks the start of a zone of authority
    "MB",       // a mailbox domain name (EXPERIMENTAL)
    "MG",       // a mail group member (EXPERIMENTAL)
    "MR",       // a mail rename domain name (EXPERIMENTAL)
    "NULL",     // a null RR (EXPERIMENTAL)
    "WKS",      // a well known service description
    "PTR",      // a domain name pointer
    "HINFO",    // host information
    "MINFO",    // mailbox or mail list information
    "MX",       // mail exchange
    "TXT",      // text strings
    "RP",
    "AFSDB",
    "X25",
    "ISDN",
    "RT",
    "NSAP",
    "NSAP_PTR",
    "SIG",
    "KEY",
    "PX",
    "GPOS",
    "AAAA",
    "LOC",
    "NXT",
    "EID",
    "NIMLOC",   // "NB"
    "SRV",      // "NBSTAT"
    "ATMA",
    "NAPTR",
    "KX",
    "CERT",
    "A6",
    "DNAME",
    "SINK",
    "OPT",
    "APL"
};

#ifndef IOP_OS
static char* ClassStrings[] =
{
    "",
    "IN",       // the Internet
    "CS",       // the CSNET class (Obsolete)
    "CH",       // the CHAOS class
    "HS",       // Hesiod [Dyer 87]
};
#endif // IOP_OS

static void NullCallback(DNSCommand* cmd, s32 result)
{
#ifdef IOP_OS
    DNSCallback callback = NULL;
#else
    DNSCallback callback;
#endif // IOP_OS

    ASSERT(cmd);
    switch (cmd->func)
    {
      case DNS_FUNC_GET_ADDR:
        callback = cmd->data.ga.callback;
        break;
      case DNS_FUNC_GET_NAME:
        callback = cmd->data.gn.callback;
        break;
      case DNS_FUNC_LOOKUP:
        callback = cmd->data.lu.callback;
        break;
      default:
        break;
    }
    if (callback)
    {
        ASSERT(cmd->info);
        callback(cmd->info, result);
    }
}

static void SyncCallback(DNSInfo* info, s32 result)
{
#ifdef IOP_OS
    TCPIP_UNUSED(result);
#else
    #pragma unused(result)
#endif // IOP_OS

    OSWakeupThread(&info->queueThread);
}

static u8* DumpName(DNSHeader* dns, u8* ptr)
{
    int count;
    u8* ret = 0;

    while (*ptr)
    {
        count = *ptr;
        if (count & 0xc0)
        {
            if (ret == 0)
            {
                ret = ptr + 2;
            }
            ptr = (u8*) dns + (*(u16*) ptr & ~0xc000);
            continue;
        }
        OSReport("%.*s", count, ++ptr);
        ptr += count;
        if (*ptr != 0)
        {
            OSReport(".");
        }
    }
    OSReport(".");
    if (ret == 0)
    {
        ret = ptr + 1;
    }

    return ret;
}

static u8* DumpString(u8* ptr)
{
    int count;
    u8  i;

    count = *ptr++;
    for (i = 0; i < count; i++)
    {
        OSReport("%c", *ptr++);
    }

    return ptr;
}

static u8* DumpQuestion(DNSHeader* dns, u8* ptr)
{
    u16 type;

    // QNAME
    ptr = DumpName(dns, ptr);

    // QTYPE
    type = *(u16*) ptr;
    if (type < sizeof TypeStrings / sizeof TypeStrings[0])
    {
        OSReport("\t%s\t", TypeStrings[type]);
    }
    ptr += 2;

    // QCLASS
    // OSReport("\t%s", ClassStrings[*(u16*) ptr]);
    ptr += 2;

    OSReport("\n");
    return ptr;
}

static u8* DumpResource(DNSHeader* dns, u8* ptr)
{
    int  count;
    u16  type;
#ifdef IP_INET6
    char ascii[SO_INET6_ADDRSTRLEN];
#endif

    // NAME
    ptr = DumpName(dns, ptr);

    // TYPE
    type = *(u16*) ptr;
    if (type < sizeof TypeStrings / sizeof TypeStrings[0])
    {
        OSReport("\t%s\t", TypeStrings[type]);
    }
    ptr += 2;

    // CLASS
    // OSReport("\t%s\t", ClassStrings[*(u16*) ptr]);
    ptr += 2;

    // TTL
    // OSReport("\t%d\t", *(s32*) ptr);
    ptr += 4;

    // RDLENGTH
    count = *(u16*) ptr;
    ptr += 2;

    // RDATA
    switch (type)
    {
      case DNS_TYPE_CNAME:      // the canonical name for an alias
      case DNS_TYPE_MB:         // a mailbox domain name (EXPERIMENTAL)
      case DNS_TYPE_MD:         // a mail destination (Obsolete - use MX)
      case DNS_TYPE_MF:         // a mail forwarder (Obsolete - use MX)
      case DNS_TYPE_MG:         // a mail group member (EXPERIMENTAL)
      case DNS_TYPE_MR:         // a mail rename domain name (EXPERIMENTAL)
      case DNS_TYPE_NS:         // an authoritative name server
      case DNS_TYPE_PTR:        // a domain name pointer
        ptr = DumpName(dns, ptr);
        break;

      case DNS_TYPE_HINFO:      // host information
      case DNS_TYPE_TXT:        // text strings
        OSReport("%*.s", count, ptr);
        ptr += count;
        break;

      case DNS_TYPE_MINFO:      // mailbox or mail list information
        ptr = DumpName(dns, ptr);
        OSReport(" ");
        ptr = DumpName(dns, ptr);
        break;

      case DNS_TYPE_MX:         // mail exchange
        OSReport("%u ", *(u16*) ptr);
        ptr += 2;
        ptr = DumpName(dns, ptr);
        break;

      case DNS_TYPE_SOA:        // marks the start of a zone of authority
        ptr = DumpName(dns, ptr);
        OSReport(" ");
        ptr = DumpName(dns, ptr);
        OSReport(" (\n\t\t\t");
        OSReport("%u ;serial\n\t\t\t",   *(u32*) ptr);
        ptr += 4;
        OSReport("%u ;refresh\n\t\t\t",  *(u32*) ptr);
        ptr += 4;
        OSReport("%u ;retry\n\t\t\t",    *(u32*) ptr);
        ptr += 4;
        OSReport("%u ;expire\n\t\t\t",   *(u32*) ptr);
        ptr += 4;
        OSReport("%u ;minimum\n\t\t\t)", *(u32*) ptr);
        ptr += 4;
        break;

      case DNS_TYPE_A:          // a host address
        OSReport("%d.%d.%d.%d", ptr[0], ptr[1], ptr[2], ptr[3]);
        ptr += 4;
        break;

      case DNS_TYPE_WKS:        // a well known service description
        OSReport("%d.%d.%d.%d", ptr[0], ptr[1], ptr[2], ptr[3]);
        ptr += 4;
        OSReport(":%d", *(u16*) ptr);
        ptr += 2;
        count -= 6;
        IFDump(ptr, count);
        ptr += count;
        break;

#ifdef IP_INET6
      case DNS_TYPE_AAAA:
#ifdef IOP_OS
        OSReport("%s", IP6NtoA((const SOIn6Addr*) ptr, ascii, SO_INET6_ADDRSTRLEN));
#else
        OSReport("%s", IP6NtoA((const SOIn6Addr*) ptr, ascii));
#endif // IOP_OS
        ptr += 16;
        break;
#endif // IP_INET6

      case DNS_TYPE_SRV:        // service location
        OSReport("%d", *(u16*) ptr);
        ptr += 2;
        OSReport(" %d", *(u16*) ptr);
        ptr += 2;
        OSReport(" %d ", *(u16*) ptr);
        ptr += 2;
        ptr = DumpName(dns, ptr);
        break;

      case DNS_TYPE_NAPTR:      // naming authority pointer
        OSReport("%d", *(u16*) ptr);
        ptr += 2;
        OSReport(" %d ", *(u16*) ptr);
        ptr += 2;
        OSReport(" \"");
        ptr = DumpString(ptr);
        OSReport("\" \"");
        ptr = DumpString(ptr);
        OSReport("\" \"");
        ptr = DumpString(ptr);
        OSReport("\" ");
        ptr = DumpName(dns, ptr);
        break;

      case DNS_TYPE_NULL:       // a null RR (EXPERIMENTAL)
      default:
        IFDump(ptr, count);
        ptr += count;
        break;
    }

    OSReport("\n");
    return ptr;
}

void DNSDumpPacket(DNSHeader* dns)
{
    u8* opt;
    int i;

    opt = &((u8*) dns)[DNS_HLEN];
    OSReport("qdcount: %d\n", dns->qdcount);
    for (i = 0; i < dns->qdcount; ++i)
    {
        opt = DumpQuestion(dns, opt);
    }
    OSReport("ancount: %d\n", dns->ancount);
    for (i = 0; i < dns->ancount; ++i)
    {
        opt = DumpResource(dns, opt);
    }
    OSReport("nscount: %d\n", dns->nscount);
    for (i = 0; i < dns->nscount; ++i)
    {
        opt = DumpResource(dns, opt);
    }
    OSReport("arcount: %d\n", dns->arcount);
    for (i = 0; i < dns->arcount; ++i)
    {
        opt = DumpResource(dns, opt);
    }
}

static u8* SkipName(const u8* ptr, const u8* end)
{
    int count;

    while (ptr < end)
    {
        if (*ptr == 0)
        {
            ++ptr;
            return (ptr <= end) ? (u8*) ptr : NULL;
            // NOT REACHED HERE
        }
        count = *ptr;
        if (count & 0xc0)
        {
            if ((count & 0xc0) != 0xc0)
            {
                return NULL;
            }
            ptr += 2;
            return (ptr <= end) ? (u8*) ptr : NULL;
            // NOT REACHED HERE
        }
        ptr += 1 + count;
    }
    return NULL;
}

static char* CopyName(const DNSHeader* dns, const u8* end, const u8* ptr,
                      char* name, s32 namelen)
{
    s32 count;

    if (SO_MAXDNAME < namelen)
    {
        namelen = SO_MAXDNAME;
    }
    while ((u8*) dns <= ptr && ptr < end)
    {
        count = *ptr;
        if (count & 0xc0)
        {
            if ((count & 0xc0) != 0xc0)
            {
                return NULL;
            }
            ptr = (u8*) dns + (*(u16*) ptr & ~0xc000);
            continue;
        }
        if (end <= ptr + count)
        {
            return NULL;
        }
        if (namelen < count + 1)
        {
            return NULL;
        }
        namelen -= count + 1;

        memmove(name, ++ptr, (size_t) count);
        ptr += count;
        name += count;
        if (*ptr != 0)
        {
            *name++ = '.';
        }
        else
        {
            *name = '\0';
            return name;
        }
    }
    return NULL;
}

static u8* DupName(const DNSHeader* dns, const u8* end, const u8* ptr, u8* opt)
{
    u8  count;
    int len = 0;

    while ((u8*) dns <= ptr && ptr < end)
    {
        count = *ptr;
        if (count & 0xc0)
        {
            ptr = (u8*) dns + (*(u16*) ptr & ~0xc000);
            continue;
        }
        if (end <= ptr + count)
        {
            return NULL;
        }
        len += count + 1;
        if (DNS_NAME_MAX < len)
        {
            return NULL;
        }
        *opt++ = count;
        if (count == 0)
        {
            return opt;
        }
        memmove(opt, ++ptr, count);
        ptr += count;
        opt += count;
    }
    return NULL;
}

static BOOL CmpName(const DNSHeader* dns0, const u8* end0, const u8* name0,
                    const DNSHeader* dns1, const u8* end1, const u8* name1)
{
    u8  count0;
    u8  count1;
#ifndef IOP_OS
    int len0 = 0;
    int len1 = 0;
#endif // IOP_OS
    
    while ((u8*) dns0 <= name0 && name0 < end0 &&
           (u8*) dns1 <= name1 && name1 < end1)
    {
        count0 = *name0;
        if (count0 & 0xc0)
        {
            name0 = (u8*) dns0 + (*(u16*) name0 & ~0xc000);
            continue;
        }
        if (end0 <= name0 + count0)
        {
#ifdef IOP_OS
            return FALSE;
#else
            return NULL;
#endif // IOP_OS
        }

        count1 = *name1;
        if (count1 & 0xc0)
        {
            name1 = (u8*) dns1 + (*(u16*) name1 & ~0xc000);
            continue;
        }
        if (end1 <= name1 + count1)
        {
#ifdef IOP_OS
            return FALSE;
#else
            return NULL;
#endif // IOP_OS
        }

        if (count0 != count1)
        {
            return FALSE;
        }
        if (count0 == 0)
        {
            return TRUE;
        }
        ++name0;
        ++name1;
        if (strnicmp((const char*) name0, (const char*) name1, count0) != 0)
        {
            return FALSE;
        }
        name0 += count0;
        name1 += count1;
    }
    return FALSE;
}

static u8* CheckName(const DNSHeader* dns, const u8* end, const u8* ptr)
{
    s32 count;
    int len = 0;
    const u8* next = 0;

    while ((u8*) dns <= ptr && ptr < end)
    {
        count = *ptr;
        if (count & 0xc0)
        {
            if ((count & 0xc0) != 0xc0)
            {
                break;
            }
            if (next == 0)
            {
                next = ptr + 2;
                if (next < (u8*) dns || end < next)
                {
                    break;
                }
            }
            ptr = (u8*) dns + (*(u16*) ptr & ~0xc000);
            continue;
        }
        if (end <= ptr + count)
        {
            break;
        }
        len += count + 1;
        if (DNS_NAME_MAX < len)
        {
            break;
        }
        if (0 < count)
        {
            char c;

            ++ptr;
            c = (char) *ptr++;
            if (!(isalnum)(c))
            {
                break;
            }
            while (0 < --count)
            {
                c = (char) *ptr++;
                if (!(isalnum)(c) && c != '-')
                {
                    break;
                }
            }
        }
        if (*ptr == 0)
        {
            if (next)
            {
                return (u8*) next;
            }
            ++ptr;
            return ((u8*) dns <= ptr && ptr <= end) ? (u8*) ptr : NULL;
            // NOT REACHED HERE
        }
    }
    return NULL;
}

static u8* CheckResource(DNSHeader* dns, u8* end, u8* ptr)
{
#ifdef IOP_OS
    TCPIP_UNUSED(dns);
#else
    #pragma unused(dns)
#endif // IOP_OS

    u16 type;
    u16 class;
    int count;

    // NAME
    ptr = CheckName(dns, end, ptr);
    if (ptr == NULL || end < ptr + DNS_OFFSET_DATA)
    {
        return NULL;
    }

    // TYPE
    type = *(u16*) ptr;
    ptr += 2;

    // CLASS
    class = *(u16*) ptr;
    ptr += 2;

    // TTL
    ptr += 4;

    // RDLENGTH
    count = *(u16*) ptr;
    ptr += 2;

    if (type < DNS_TYPE_A)
    {
        return NULL;
    }

    end = ptr + count;

    // RDATA
    switch (type)
    {
      case DNS_TYPE_CNAME:      // the canonical name for an alias
      case DNS_TYPE_MB:         // a mailbox domain name (EXPERIMENTAL)
      case DNS_TYPE_MD:         // a mail destination (Obsolete - use MX)
      case DNS_TYPE_MF:         // a mail forwarder (Obsolete - use MX)
      case DNS_TYPE_MG:         // a mail group member (EXPERIMENTAL)
      case DNS_TYPE_MR:         // a mail rename domain name (EXPERIMENTAL)
      case DNS_TYPE_NS:         // an authoritative name server
      case DNS_TYPE_PTR:        // a domain name pointer
        ptr = CheckName(dns, end, ptr);
        break;

      case DNS_TYPE_HINFO:      // host information
      case DNS_TYPE_TXT:        // text strings
        ptr += count;
        break;

      case DNS_TYPE_MINFO:      // mailbox or mail list information
        ptr = CheckName(dns, end, ptr);
        if (ptr == NULL)
        {
            break;
        }
        ptr = CheckName(dns, end, ptr);
        break;

      case DNS_TYPE_MX:         // mail exchange
        ptr += 2;
        ptr = CheckName(dns, end, ptr);
        break;

      case DNS_TYPE_SOA:        // marks the start of a zone of authority
        ptr = CheckName(dns, end, ptr);
        if (ptr == NULL)
        {
            break;
        }
        ptr = CheckName(dns, end, ptr);
        if (ptr == NULL)
        {
            break;
        }
        ptr += 20;
        break;

      case DNS_TYPE_A:          // a host address
        ptr += 4;
        break;

      case DNS_TYPE_WKS:        // a well known service description
        ptr += count;
        break;

      case DNS_TYPE_AAAA:
        ptr += 16;
        break;

      case DNS_TYPE_OPT:
        ptr += count;
        break;

      case DNS_TYPE_NULL:       // a null RR (EXPERIMENTAL)
      default:
        ptr += count;
        break;
    }

    return (ptr == end) ? ptr : NULL;
}

//
// Transport
//

static s32 Connect(DNSInfo* info, u8* addr)
{
    s32        result;
    DNSHeader* dns;

    dns = (DNSHeader*) &info->query[0];
    dns->id = ++info->id;
    info->rxmit = 0;
    info->flag &= ~(DNS_FLAG_BROADCAST | DNS_FLAG_MULTICAST);
    memmove(info->socket.addr, addr, IP_ALEN);

    if (!(info->flag & DNS_FLAG_TCP))
    {
        result = UDPConnect(&info->udp, &info->socket);
        if (result < 0)
        {
            UDPClose(&info->udp);
        }
        else
        {
            IPInterface* interface;

            interface = IPGetRoute(info->socket.addr, NULL);
            ASSERT(interface);
            if (IP_CLASSD(info->socket.addr))
            {
                info->flag |= DNS_FLAG_MULTICAST;
            }
            else if (IPIsBroadcastAddr(interface, info->socket.addr))
            {
                info->flag |= DNS_FLAG_BROADCAST;
            }
        }
    }
    else
    {
        TCPCancel(&info->tcp);
        result = TCPOpen(&info->tcp,
                         info->sendBuff, sizeof info->sendBuff,
                         info->recvBuff, sizeof info->recvBuff);
        if (result < 0)
        {
            info->flag &= ~DNS_FLAG_TCP;
        }
    }
    return result;
}

static s32 ReceiveResponse(DNSInfo* info)
{
    s32 rc;

    if (!(info->flag & DNS_FLAG_TCP))
    {
        rc = UDPReceiveAsync(&info->udp, info->response, sizeof(info->response),
                             NULL, &info->socket,
                             ReceiveCallbackUDP, NULL);
    }
    else
    {
        ASSERT(info->recvedLen < 2 + sizeof(info->response));
        rc = TCPReceiveAsync(&info->tcp,
                             (u8*) &info->recvLen + info->recvedLen,
                             2 + (s32) sizeof(info->response) - info->recvedLen,
                             ReceiveCallbackTCP, NULL);
    }
    if (0 <= rc || rc == IP_ERR_BUSY)
    {
        return IP_ERR_NONE;
    }
    return rc;
}

static void ReceiveCallbackUDP(UDPInfo* udp, s32 result)
{
    DNSInfo* info;

    info = (DNSInfo*) ((u8*) udp - offsetof(DNSInfo, udp));
    ReceiveCallback(info, result);
}

static void ReceiveCallbackTCP(TCPInfo* tcp, s32 result)
{
    DNSInfo* info;

    info = (DNSInfo*) ((u8*) tcp - offsetof(DNSInfo, tcp));
    if (0 < result)
    {
        info->recvedLen += result;
        if (info->recvedLen < 2 ||
            (info->recvedLen <= info->recvLen + 2 &&
             info->recvLen < sizeof(info->response)))
        {
            // Continue to gather response segments.
            result = ReceiveResponse(info);
            if (0 <= result || result == IP_ERR_BUSY)
            {
                return;
                // NOT REACHED HERE
            }
        }
        else
        {
            result = IP_ERR_INVALID;
        }
    }

    if (result < 0)
    {
        TCPCancel(&info->tcp);
    }
    else
    {
        TCPCloseAsync(&info->tcp, NULL, NULL);
        result = info->recvedLen - 2;
    }
    ReceiveCallback(info, result);
    info->flag &= ~DNS_FLAG_TCP;
}

static s32 SendQuery(DNSInfo* info)
{
    s32 rc;

    OSCancelAlarm(&info->alarm);
    info->recvedLen = 0;
    if (!(info->flag & DNS_FLAG_TCP))
    {
        rc = UDPSendAsync(&info->udp, info->query, info->sendLen, NULL,
                          NULL, NULL);
        if (0 <= rc || rc == IP_ERR_BUSY)
        {
            OSSetAlarm(&info->alarm,
                       OSSecondsToTicks((OSTime) (MIN_WAIT << info->rxmit)),
                       TimeoutCallback);
            return ReceiveResponse(info);
        }
    }
    else
    {
        rc = TCPConnectAsync(&info->tcp, &info->socket, NULL, NULL);
        if (0 <= rc || rc == IP_ERR_BUSY)
        {
            rc = TCPSendAsync(&info->tcp, &info->sendLen, 2 + info->sendLen,
                              NULL, NULL);
            if (0 <= rc || rc == IP_ERR_BUSY)
            {
                TCPShutdown(&info->tcp, TCP_SHUTDOWN_SEND);
                OSSetAlarm(&info->alarm, OSSecondsToTicks((OSTime) MAX_WAIT), TimeoutCallback);
                return ReceiveResponse(info);
            }
        }
    }
    return rc;
}

// Attemps to switch to the other DNS server
static s32 SwitchServer(DNSInfo* info)
{
    u8* next;

    OSCancelAlarm(&info->alarm);
    if (info->flag & DNS_FLAG_TCP)
    {
        TCPCancel(&info->tcp);
        info->flag &= ~DNS_FLAG_TCP;
        return IP_ERR_NONE;
    }

    if (2 <= ++info->retry)
    {
        return IP_ERR_NOT_EXIST;
    }

    if (IP_ADDR_EQ(info->socket.addr, info->dns2))
    {
        next = info->dns1;
    }
    else
    {
        next = info->dns2;
    }

    if (IP_ADDR_NE(next, IPAddrAny))
    {
        info->flag &= ~DNS_FLAG_NO_TCP;
        info->flag |= DNS_FLAG_EDNS0;
        return Connect(info, next);
    }
    else
    {
        return IP_ERR_NOT_EXIST;
    }
}

static s32 SwitchTransport(DNSInfo* info)
{
    OSCancelAlarm(&info->alarm);
    if (!(info->flag & (DNS_FLAG_TCP | DNS_FLAG_NO_TCP)))
    {
        info->flag |= DNS_FLAG_TCP;
        return Connect(info, info->socket.addr);
    }
    else
    {
        info->flag &= ~DNS_FLAG_TCP;
        return IP_ERR_UNREACHABLE;
    }
}

static s32 Cancel(DNSInfo* info)
{
    UDPCancel(&info->udp);
    TCPCancel(&info->tcp);
    return IP_ERR_NONE;
}

// Cancel all pending queries. Must prevent any further cmd from being executed.
static s32 CancelAll(DNSInfo* info, s32 rc)
{
    DNSCommand*     cmd;
    DNSPostCallback callback;

    ASSERT(rc != IP_ERR_BUSY);
    info->flag |= DNS_FLAG_CANCELED;
    cmd = info->current;
    info->current = NULL;
    if (cmd)
    {
        if (cmd->result)
        {
            *cmd->result = rc;
        }
        callback = cmd->callback;
        if (callback)
        {
            cmd->callback = NULL;
            callback(cmd, rc);
        }
    }
    while (!IFIsEmptyQueue(&info->queue))
    {
        IFDequeueHead(DNSCommand*, &info->queue, cmd, link);
        if (cmd->result)
        {
            *cmd->result = rc;
        }
        callback = cmd->callback;
        if (callback)
        {
            cmd->callback = NULL;
            callback(cmd, rc);
        }
    }
    Cancel(info);
    info->flag &= ~DNS_FLAG_CANCELED;
    return rc;
}

static void ReceiveCallback(DNSInfo* info, s32 result)
{
    DNSHeader*      dns;
    u16             type;
    u8*             opt;
    u8*             ans;
    u8*             end;
    int             i;
    u16             len;
    DNSCommand*     current;
    DNSPostCallback callback;

    if (info->current == NULL)
    {
        return;
    }
    current = info->current;

    if (result < 0)
    {
        goto Error;
    }

    //
    // Check the response and drop it if it is not a valid one keeping the
    // current alarm.
    //
    dns = (DNSHeader*) info->response;
    if (result < DNS_HLEN ||
        dns->id != info->id ||
        (dns->flags & DNS_FLAG_QR) != DNS_FLAG_R)
    {
        goto Drop;
    }

    opt = info->response + DNS_HLEN;
    end = info->response + result;

    for (i = 0; i < dns->qdcount; ++i)
    {
        opt = SkipName(opt, end);
        if (opt == NULL || end < opt + 4)
        {
            goto Drop;
        }
        opt += 4;
    }
    if (info->queryLen != opt - info->response ||
        memcmp(info->query + DNS_HLEN, info->response + DNS_HLEN,
               (u32) info->queryLen - DNS_HLEN) != 0)
    {
        goto Drop;
    }

    ans = opt;
    for (i = 0; i < dns->ancount; ++i)
    {
        opt = CheckResource(dns, end, opt);
        if (opt == NULL)
        {
            goto Drop;
        }
    }
    for (i = 0; i < dns->nscount; ++i)
    {
        opt = CheckResource(dns, end, opt);
        if (opt == NULL)
        {
            goto Drop;
        }
    }
    for (i = 0; i < dns->arcount; ++i)
    {
        opt = CheckResource(dns, end, opt);
        if (opt == NULL)
        {
            goto Drop;
        }
    }

    //
    // Received a valid response from a DNS server. Cancel the alarm.
    //
#ifdef VERBOSE
    DNSDumpPacket((DNSHeader*) info->response);
#endif

    if (dns->flags & DNS_FLAG_TC)
    {
        // Switch tarnsport from UDP to TCP.
        if (0 <= SwitchTransport(info) && 0 <= SendQuery(info))
        {
            return;
        }
    }

    if ((dns->flags & DNS_ERROR_MASK) == DNS_ERROR_NONE)
    {
        opt = ans;

        switch (current->func)
        {
          case DNS_FUNC_LOOKUP:
            // XXX TRUNC bit
            result = MIN(info->datalen, result);
            memmove(info->data, info->response, (u32) result);
            break;
          case DNS_FUNC_GET_ADDR:
            if (__SOResolver.name == current->data.ga.name)
            {
                CopyName(dns, end, opt, __SOResolver.name, SO_MAXDNAME);
            }
            // FALL THROUGH
          case DNS_FUNC_GET_NAME:
            result = 0;
            for (i = 0; i < dns->ancount; ++i)
            {
                opt = SkipName(opt, end);
                len = *(u16*) (opt + DNS_OFFSET_LEN);
                type = *(u16*) opt;
                switch (type)
                {
                  case DNS_TYPE_A:
                    if (current->func == DNS_FUNC_GET_ADDR &&
                        info->data && IP_ALEN == len)
                    {
                        // ip_addr[IP_ALEN] is from opt + DNS_OFFSET_DATA
                        memmove(info->data, opt + DNS_OFFSET_DATA, IP_ALEN);
                        info->datalen -= IP_ALEN;
                        if (0 < info->datalen)
                        {
                            info->data += IP_ALEN;
                        }
                        else
                        {
                            info->data = NULL;
                        }
                        result += IP_ALEN;
                    }
                    break;
                  case DNS_TYPE_PTR:
                    if (current->func == DNS_FUNC_GET_NAME &&
                        info->data)
                    {
                        char* name;

                        name = CopyName(dns, opt + DNS_OFFSET_DATA + len, opt + DNS_OFFSET_DATA,
                                        (char*) info->data, info->datalen);
                        if (name != NULL)
                        {
                            result = name - (char*) info->data;
                        }
                        info->data = NULL;
                    }
                    break;
                }
                opt += 10 + len;
            }

            if (info->flag & DNS_FLAG_SOCKET)
            {
                SOMakeHostent((SOResolver*) info, dns, end - info->response);
            }
            break;
          default:
            break;
        }
    }
    else if ((info->flag & DNS_FLAG_EDNS0) && !(info->flag & DNS_FLAG_TCP))
    {
        switch (dns->flags & DNS_ERROR_MASK)
        {
          case DNS_ERROR_FORMAT:
          case DNS_ERROR_SERVER:
          case DNS_ERROR_NOTIMP:
            // Rexmit without OPT
            info->flag &= ~DNS_FLAG_EDNS0;          // Not try using EDNS0 again
            info->sendLen = (u16) info->queryLen;   // Cut OPT
            dns = (DNSHeader*) &info->query[0];
            dns->id = ++info->id;
            dns->arcount = 0;
            info->rxmit = 0;                        // reset
            if (0 <= SendQuery(info))
            {
                return;
                // NOT REACHED HERE
            }
            // FALL THROUGH
          default:
            result = IP_ERR_DNS_MAX - (dns->flags & DNS_ERROR_MASK);
            break;
        }
    }
    else
    {
        result = IP_ERR_DNS_MAX - (dns->flags & DNS_ERROR_MASK);
    }

    OSCancelAlarm(&info->alarm);
    if (current->result)
    {
        *current->result = result;
    }
    callback = current->callback;
    if (callback)
    {
        current->callback = NULL;
        callback(current, result);
    }

    DNSGo(info, NULL);
    return;
    // NOT REACHED HERE

Drop:
    if (!(info->flag & DNS_FLAG_TCP))
    {
        ReceiveResponse(info);
        return;
        // NOT REACHED HERE
    }
    result = IP_ERR_DNS_FORMAT;

Error:
    ASSERT(result < 0);

    if (info->flag & DNS_FLAG_TCP)
    {
        // Don't try using TCP anymore
        info->flag |= DNS_FLAG_NO_TCP;
    }

    switch (result)
    {
      case IP_ERR_CLOSING:
        return;
        // NOT REACHED HERE
      case IP_ERR_CANCELED:
      case IP_ERR_NETDOWN:
        ASSERT(current->result == NULL || *current->result != IP_ERR_BUSY);
        return;
        // NOT REACHED HERE
        break;
      case IP_ERR_UNREACHABLE:
      case IP_ERR_SOURCE_QUENCH:
      default:
        if (0 <= SwitchServer(info) && 0 <= SendQuery(info))
        {
            break;
        }
        CancelAll(info, result);
        break;
    }
}

static void TimeoutCallback(OSAlarm* alarm, OSContext* context)
{
#ifdef IOP_OS
    TCPIP_UNUSED(context);
#else
    #pragma unused(context)
#endif // IOP_OS

    DNSInfo*    info;
    DNSCommand* current;
    DNSHeader*  dns;

    info = (DNSInfo*) ((u8*) alarm - offsetof(DNSInfo, alarm));
    ASSERT(info->current);
    current = info->current;

    if (info->flag & DNS_FLAG_TCP)
    {
        TCPCancel(&info->tcp);
        return;     // Note following operation shall be handled by ReceiveCallback
    }

    // Rexmit
    ++info->rxmit;
    if ((info->flag & DNS_FLAG_EDNS0) && MAX_QUERY <= info->rxmit)
    {
        info->flag &= ~DNS_FLAG_EDNS0;          // Not try using EDNS0 again
        info->sendLen = (u16) info->queryLen;   // Cut OPT
        dns = (DNSHeader*) &info->query[0];
        dns->id = ++info->id;
        dns->arcount = 0;
        info->rxmit = 0;                        // reset
    }

    if ((info->rxmit < MAX_QUERY || 0 <= SwitchServer(info)) &&
        0 <= SendQuery(info))
    {
        return;
        // NOT REACHED HERE
    }
    CancelAll(info, IP_ERR_TIMEOUT);
}

s32 DNSOpen(DNSInfo* info, const u8* addr)
{
    return DNSOpen2(info, addr, NULL);
}

s32 DNSOpen2(DNSInfo* info, const u8* dns1, const u8* dns2)
{
    s32  result;
    BOOL enabled;

    enabled = OSDisableInterrupts();

    memset(info, 0, sizeof(DNSInfo));

    info->flag |= DNS_FLAG_EDNS0;

    info->id = (u16) (OSGetTime() / (OS_TIMER_CLOCK / TCP_IIS_CLOCK));
    OSCreateAlarm(&info->alarm);
    OSInitThreadQueue(&info->queueThread);

    info->socket.len = IP_SOCKLEN;
    info->socket.family = IP_INET;
    info->socket.port = DNS_PORT;

    if (dns1 == NULL)
    {
        dns1 = IPAddrAny;
    }
    if (dns2 == NULL)
    {
        dns2 = IPAddrAny;
    }
    memmove(info->dns1, dns1, IP_ALEN);
    memmove(info->dns2, dns2, IP_ALEN);
    if (IP_ADDR_EQ(info->dns1, IPAddrAny))
    {
        memmove(info->dns1, dns2, IP_ALEN);
    }
    if (IP_ADDR_EQ(info->dns1, IPAddrAny))
    {
        OSRestoreInterrupts(enabled);
        return IP_ERR_NOT_EXIST;
    }
    if (IP_ADDR_EQ(info->dns1, info->dns2))
    {
        memmove(info->dns2, IPAddrAny, IP_ALEN);
    }

    TCPOpen(&info->tcp,
            info->sendBuff, sizeof info->sendBuff,
            info->recvBuff, sizeof info->recvBuff);

    result = UDPOpen(&info->udp, NULL, 0);
    if (0 <= result)
    {
        result = Connect(info, info->dns1);
    }
    OSRestoreInterrupts(enabled);
    return result;
}

s32 DNSClose(DNSInfo* info)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    CancelAll(info, IP_ERR_NETDOWN);    // Cancel all pending request.
    UDPClose(&info->udp);
    OSCancelAlarm(&info->alarm);
    OSRestoreInterrupts(enabled);
    return 0;
}

// cmd -- Set NULL to execute the next command in the queue.
void DNSGo(DNSInfo* info, DNSCommand* cmd)
{
    BOOL            enabled;
#ifdef IOP_OS
    s32             rc = 0;
#else
    s32             rc;
#endif // IOP_OS
    DNSHeader*      dns;
    DNSPostCallback callback;

    enabled = OSDisableInterrupts();
Next:
    if (cmd == NULL)
    {
        if (IFIsEmptyQueue(&info->queue))
        {
            ASSERT(info->current == NULL ||
                   info->current->result == NULL ||
                   *info->current->result != IP_ERR_BUSY);
            info->current = NULL;
            UDPCancel(&info->udp);  // must not cancel TCP here
            OSRestoreInterrupts(enabled);
            return;
            // NOT REACHED HERE
        }
        IFDequeueHead(DNSCommand*, &info->queue, cmd, link);
    }
    else if (info->flag & DNS_FLAG_CANCELED)
    {
        if (cmd->result)
        {
            *cmd->result = IP_ERR_NETDOWN;
        }
        callback = cmd->callback;
        if (callback)
        {
            cmd->callback = NULL;
            callback(cmd, IP_ERR_NETDOWN);
        }
        OSRestoreInterrupts(enabled);
        return;
        // NOT REACHED HERE
    }
    else
    {
        cmd->info = info;
        if (cmd->result)
        {
            *cmd->result = IP_ERR_BUSY;
        }
        if (info->current)
        {
            IFEnqueueTail(DNSCommand*, &info->queue, cmd, link);
            OSRestoreInterrupts(enabled);
            return;
            // NOT REACHED HERE
        }
    }

    info->current = cmd;

    if (cmd->precallback)
    {
        rc = cmd->precallback(info, cmd);
        if (rc < 0)
        {
            if (cmd->result)
            {
                *cmd->result = rc;
            }
            callback = cmd->callback;
            if (callback)
            {
                cmd->callback = NULL;
                callback(cmd, rc);
            }
            cmd = NULL;
            goto Next;
        }
    }

    dns = (DNSHeader*) &info->query[0];
    dns->id = ++info->id;

    if (cmd->result)
    {
        *cmd->result = IP_ERR_BUSY;
    }

    info->retry = 0;
Retry:
    info->rxmit = 0;
    ASSERT(offsetof(DNSInfo, sendLen) + sizeof(u16) == offsetof(DNSInfo, query));
    if (0 <= SendQuery(info))
    {
        OSRestoreInterrupts(enabled);
        return;
        // NOT REACHED HERE
    }
    if (0 <= SwitchServer(info))
    {
        goto Retry;
    }
    CancelAll(info, rc);
    OSRestoreInterrupts(enabled);
}

static u8* AppendOpt(DNSHeader* dns, u8* opt)
{
    u16 max = (u16) (IPGetReassembleMaxSize() - 64);

    if (512 < max)
    {
        ++dns->arcount;
        *opt++ = 0;                     // NAME = empty

        *(u16*) opt = DNS_TYPE_OPT;     // Type = OPT pseudo-RR
        opt += 2;

        *(u16*) opt = max;              // Class = sender's UDP payload size
        opt += 2;

        *(u32*) opt = 0;                // TTL = extended RCODE and flags
        opt += 4;

        *(u16*) opt = 0;                // RDLEN = 0
        opt += 2;
    }
    return opt;
}

static s32 PreGetAddr(DNSInfo* info, DNSCommand* cmd)
{
    const char* name = cmd->data.ga.name;
    u8*         addr = cmd->data.ga.addr;
    s32         addrLen = cmd->data.ga.addrLen;

    DNSHeader*  dns;
    u8*         opt;
    u8*         count;
    int         i;
    BOOL        dot = FALSE;
    u8*         queryName;

    // Form the request
    dns = (DNSHeader*) &info->query[0];
    dns->flags = DNS_FLAG_Q | DNS_OP_QUERY;
    if ((info->flag & (DNS_FLAG_BROADCAST | DNS_FLAG_MULTICAST)) == 0)
    {
        dns->flags |= DNS_FLAG_RD;
    }
    dns->qdcount = 1;
    dns->ancount = 0;
    dns->nscount = 0;
    dns->arcount = 0;

    // Put name into DNS name format
    opt = info->query + DNS_HLEN;
    queryName = opt;
    while (*name)
    {
        if (DNS_NAME_MAX - 1 <= opt - queryName)
        {
            return IP_ERR_INVALID;
            // NOT REACHED HERE
        }
        count = opt++;
        for (i = 0; *name && *name != '.'; ++i)
        {
            if (DNS_LABEL_MAX <= i ||
                DNS_NAME_MAX - 1 <= opt - queryName)
            {
                return IP_ERR_INVALID;
                // NOT REACHED HERE
            }
            *opt++ = (u8) *name++;
        }
        *count = (u8) i;
        if (*name == '.')
        {
            dot = TRUE;
            ++name;
        }
        else if (!dot && __SOResolver.suffix[0])
        {
            dot = TRUE;
            name = __SOResolver.suffix;
        }
    }
    *opt++ = 0;

    *(u16*) opt = DNS_TYPE_A;       // Type = IPv4 address
    opt += 2;

    *(u16*) opt = DNS_CLASS_IN;     // Class = Internet
    opt += 2;

    info->queryLen = opt - info->query;

    if ((info->flag & DNS_FLAG_EDNS0) && !(info->flag & DNS_FLAG_TCP))
    {
        opt = AppendOpt(dns, opt);
    }
    info->sendLen = (u16) (opt - info->query);

    info->data = addr;
    memset(info->data, 0, (u32) addrLen);
    info->datalen = addrLen & ~3;
    return 0;
}

// Host name to host address translation
s32 DNSGetAddrAsync(DNSInfo* info, const char* name, u8* addr, s32 addrLen,
                    DNSCallback callback, s32* result)
{
    static DNSCommand cmd;
    s32    rc;

    ASSERT(addr == NULL || IP_ALEN <= addrLen);
    if (name == NULL || (addr && (addrLen < IP_ALEN)))
    {
        rc = IP_ERR_INVALID;
        goto Error;
    }

    if (cmd.callback)
    {
        rc = IP_ERR_BUSY;
        goto Error;
    }

    cmd.func = DNS_FUNC_GET_ADDR;
    cmd.precallback = PreGetAddr;
    cmd.callback = NullCallback;
    cmd.result = result;
    cmd.data.ga.name = name;
    cmd.data.ga.addr = addr;
    cmd.data.ga.addrLen = addrLen;
    cmd.data.ga.callback = callback;
    DNSGo(info, &cmd);
    return 0;
    // NOT REACHED HERE

Error:
    if (result)
    {
        *result = rc;
    }
    return rc;
}

s32 DNSGetAddr(DNSInfo* info, const char* name, u8* addr, s32 addrLen)
{
    vs32 result;
    s32  rc;
    BOOL enabled;

    rc = DNSGetAddrAsync(info, name, addr, addrLen,
                         SyncCallback, (s32*) &result);
    if (rc < 0)
    {
        return rc;
    }

    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&info->queueThread);
    }
    OSRestoreInterrupts(enabled);
    return result;
}

static s32 PreGetName(DNSInfo* info, DNSCommand* cmd)
{
    const u8*  addr = cmd->data.gn.addr;
    char*      name = cmd->data.gn.name;

    DNSHeader* dns;
    u8*        opt;
    u8*        count;
    int        i;

    // Form the request
    dns = (DNSHeader*) &info->query[0];
    dns->flags = DNS_FLAG_Q | DNS_OP_QUERY;
    if ((info->flag & (DNS_FLAG_BROADCAST | DNS_FLAG_MULTICAST)) == 0)
    {
        dns->flags |= DNS_FLAG_RD;
    }
    dns->qdcount = 1;
    dns->ancount = 0;
    dns->nscount = 0;
    dns->arcount = 0;

    // Put name into DNS name format
    opt = info->query + DNS_HLEN;
    for (i = 3; 0 <= i; --i)
    {
        count = opt++;
#ifdef IOP_OS
        *count = (u8) snprintf((char*) opt, 
            (sizeof(info->query) - ((u8*) opt - (u8*) info->query)), 
            "%d", addr[i]);
#else
        *count = (u8) sprintf((char*) opt, "%d", addr[i]);
#endif // IOP_OS
        opt += *count;
    }
    *opt++ = 7;
    memmove(opt, "in-addr", 7);
    opt += 7;
    *opt++ = 4;
    memmove(opt, "arpa", 4);
    opt += 4;
    *opt++ = 0;

    *(u16*) opt = DNS_TYPE_PTR;     // Type = Domain name pointer
    opt += 2;

    *(u16*) opt = DNS_CLASS_IN;     // Class = Internet
    opt += 2;

    info->queryLen = opt - info->query;

    if ((info->flag & DNS_FLAG_EDNS0) && !(info->flag & DNS_FLAG_TCP))
    {
        opt = AppendOpt(dns, opt);
    }
    info->sendLen = (u16) (opt - info->query);

    info->data = (u8*) name;
    if (name)
    {
        *name = '\0';
        info->datalen = DNS_NAME_MAX;
    }
    else
    {
        info->datalen = 0;
    }

    return 0;
}

// Host address to host name translation
s32 DNSGetNameAsync(DNSInfo* info, const u8* addr, char* name,
                    DNSCallback callback, s32* result)
{
    static DNSCommand cmd;
    s32    rc;

    ASSERT(addr != NULL);
    if (addr == NULL)
    {
        rc = IP_ERR_INVALID;
        goto Error;
    }

    if (cmd.callback)
    {
        rc = IP_ERR_BUSY;
        goto Error;
    }

    cmd.func = DNS_FUNC_GET_NAME;
    cmd.precallback = PreGetName;
    cmd.callback = NullCallback;
    cmd.result = result;
    cmd.data.gn.addr = addr;
    cmd.data.gn.name = name;
    cmd.data.gn.callback = callback;
    DNSGo(info, &cmd);
    return 0;
    // NOT REACHED HERE

Error:
    if (result)
    {
        *result = rc;
    }
    return rc;
}

s32 DNSGetName(DNSInfo* info, const u8* addr, char* name)
{
    vs32 result;
    s32  rc;
    BOOL enabled;

    rc = DNSGetNameAsync(info, addr, name,
                         SyncCallback, (s32*) &result);
    if (rc < 0)
    {
        return rc;
    }

    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&info->queueThread);
    }
    OSRestoreInterrupts(enabled);
    return result;
}

static s32 PreLookup(DNSInfo* info, DNSCommand* cmd)
{
    const u8* query = cmd->data.lu.query;
    s32       queryLen = cmd->data.lu.queryLen;
    u8*       response = cmd->data.lu.response;
    s32       responseLen = cmd->data.lu.responseLen;

    // Form the request
    memmove(info->query, query, (u32) queryLen);
    info->queryLen = queryLen;
    info->sendLen = (u16) queryLen;
    info->data = response;
    info->datalen = responseLen;

    return queryLen;
}

s32 DNSLookupAsync(DNSInfo* info,
                   const u8* query, s32 queryLen, u8* response, s32 responseLen,
                   DNSCallback callback, s32* result)
{
    static DNSCommand cmd;
    s32    rc;

    if (query == NULL || DNS_UDP_MAX < queryLen ||
        (response && (responseLen < 0)))
    {
        rc = IP_ERR_INVALID;
        goto Error;
    }

    if (cmd.callback)
    {
        rc = IP_ERR_BUSY;
        goto Error;
    }

    cmd.func = DNS_FUNC_LOOKUP;
    cmd.precallback = PreLookup;
    cmd.callback = NullCallback;
    cmd.result = result;
    cmd.data.lu.query = query;
    cmd.data.lu.queryLen = queryLen;
    cmd.data.lu.response = response;
    cmd.data.lu.responseLen = responseLen;
    cmd.data.lu.callback = callback;
    DNSGo(info, &cmd);
    return 0;
    // NOT REACHED HERE

Error:
    if (result)
    {
        *result = rc;
    }
    return rc;
}

s32 DNSLookup(DNSInfo* info,
              const u8* query, s32 queryLen, u8* response, s32 responseLen)
{
    vs32 result;
    s32  rc;
    BOOL enabled;

    rc = DNSLookupAsync(info, query, queryLen, response, responseLen,
                        SyncCallback, (s32*) &result);
    if (rc < 0)
    {
        return rc;
    }

    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&info->queueThread);
    }
    OSRestoreInterrupts(enabled);
    return result;
}

/*---------------------------------------------------------------------------*
                               Socket Layer
 *---------------------------------------------------------------------------*/

static void SOMakeHostent(SOResolver* res, DNSHeader* dns, s32 result)
{
    DNSInfo*    info = &res->info;
    DNSCommand* current = info->current;
    u8*         opt;
    u8*         end;
    u16         len;
    u16         type;
    int         i;

    opt = (u8*) dns + DNS_HLEN;
    end = info->response + result;
    for (i = 0; i < dns->qdcount; ++i)
    {
        opt = SkipName(opt, end);
        opt += 4;
    }

    if (current->func == DNS_FUNC_GET_NAME)
    {
        info->data = res->addrList;
        info->datalen = sizeof res->addrList;
    }

    result = 0;
    for (i = 0; i < dns->ancount; ++i)
    {
        opt = SkipName(opt, end);
        len = *(u16*) (opt + DNS_OFFSET_LEN);
        type = *(u16*) opt;
        switch (type)
        {
          case DNS_TYPE_A:
            if (current->func == DNS_FUNC_GET_NAME &&
                info->data && IP_ALEN == len)
            {
                // ip_addr[IP_ALEN] is from opt + DNS_OFFSET_DATA
                memmove(info->data, opt + DNS_OFFSET_DATA, IP_ALEN);
                info->datalen -= IP_ALEN;
                if (0 < info->datalen)
                {
                    info->data += IP_ALEN;
                }
                else
                {
                    info->data = NULL;
                }
                result += IP_ALEN;
            }
            break;
          case DNS_TYPE_CNAME:
            if (current->func == DNS_FUNC_GET_ADDR)
            {
                CopyName(dns, opt + DNS_OFFSET_DATA + len, opt + DNS_OFFSET_DATA,
                         res->name, SO_MAXDNAME);
            }
            break;
        }
        opt += 10 + len;
    }

    if (current->func == DNS_FUNC_GET_NAME && 0 < result)
    {
        u8** ptr;
        u8*  addr;

        for (ptr = res->ptrList, addr = res->addrList;
             0 < result;
             result -= IP_ALEN, ++ptr, addr += IP_ALEN)
        {
            *ptr = addr;
        }
        *ptr = NULL;
    }
}

/*---------------------------------------------------------------------------*
                                SOGetNameInfo
 *---------------------------------------------------------------------------*/

static s32 PreGetAddrInfo(DNSInfo* info, DNSCommand* cmd)
{
    const char* nodeName = cmd->data.ai.nodeName;
#ifndef IOP_OS
    const char* servName = cmd->data.ai.servName;
#endif // IOP_OS
    u16         type = cmd->data.ai.type;
    DNSHeader*  dns;
    u8*         opt;
    u8*         count;
    int         i;
    BOOL        dot = FALSE;
    u8*         queryName;

    // Form the request
    dns = (DNSHeader*) &info->query[0];
    dns->flags = DNS_FLAG_Q | DNS_OP_QUERY;
    if ((info->flag & (DNS_FLAG_BROADCAST | DNS_FLAG_MULTICAST)) == 0)
    {
        dns->flags |= DNS_FLAG_RD;
    }
    dns->qdcount = 1;
    dns->ancount = 0;
    dns->nscount = 0;
    dns->arcount = 0;

    // Put NodeName into DNS name format
    opt = info->query + DNS_HLEN;

#ifdef RFC_2782
    if (type == DNS_TYPE_SRV)
    {
        u8 len;

        len = (u8) strlen(servName);
        *opt++ = (u8) (len + 1);    // count
        *opt++ = '_';
        memmove(opt, servName, len);
        opt += len;

        *opt++ = 4;                 // count
        *opt++ = '_';
        memmove(opt, (cmd->data.ai.sockType == SO_SOCK_DGRAM) ? "udp" : "tcp", 3);
        opt += 3;
    }
#endif // RFC_2782

    queryName = opt;
    while (*nodeName)
    {
        if (DNS_NAME_MAX - 1 <= opt - queryName)
        {
            return IP_ERR_INVALID;
            // NOT REACHED HERE
        }
        count = opt++;
        for (i = 0; *nodeName && *nodeName != '.'; ++i)
        {
            if (DNS_LABEL_MAX <= i ||
                DNS_NAME_MAX - 1 <= opt - queryName)
            {
                return IP_ERR_INVALID;
                // NOT REACHED HERE
            }
            *opt++ = (u8) *nodeName++;
        }
        *count = (u8) i;
        if (*nodeName == '.')
        {
            dot = TRUE;
            ++nodeName;
        }
        else if (!dot && __SOResolver.suffix[0])
        {
            dot = TRUE;
            nodeName = __SOResolver.suffix;
        }
    }
    *opt++ = 0;

    *(u16*) opt = type;
    opt += 2;

    *(u16*) opt = DNS_CLASS_IN;     // Class = Internet
    opt += 2;

    info->queryLen = opt - info->query;

    if ((info->flag & DNS_FLAG_EDNS0) && !(info->flag & DNS_FLAG_TCP))
    {
        opt = AppendOpt(dns, opt);
    }
    info->sendLen = (u16) (opt - info->query);

    info->data = cmd->data.ai.addrList;
    info->datalen = 0;
    return 0;
}

static void GetAddrInfoCallback(DNSCommand* cmd, s32 result)
{
    DNSInfo*    info;
    u16         type;
    DNSHeader*  dns;
    u8*         res;
    u8*         end;
    u8*         ans;
    u8*         req;
    int         i;
    u16         len;
#ifndef IOP_OS
    u8*         ar = NULL;
#endif // IOP_OS

#ifdef RFC_2782
    u8*         srv;
    u16         arcount;
    u8*         srvAns;
    u16         priority;
    u16         weight;
    u16         ansPriority;
    u16         ansWeight;
#endif // RFC_2782

    ASSERT(cmd);
    info = cmd->info;
    type = cmd->data.ai.type;
    if (cmd->result)
    {
        *cmd->result = IP_ERR_BUSY;
    }
    if (result < 0)
    {
        goto Error;
    }

    // Form the request
    ASSERT(info);
    dns = (DNSHeader*) &info->query[0];
    dns->flags = DNS_FLAG_Q | DNS_OP_QUERY;
    if ((info->flag & (DNS_FLAG_BROADCAST | DNS_FLAG_MULTICAST)) == 0)
    {
        dns->flags |= DNS_FLAG_RD;
    }
    dns->qdcount = 1;
    dns->ancount = 0;
    dns->nscount = 0;
    dns->arcount = 0;
    req = info->query + DNS_HLEN;

    // Parse the response
    dns = (DNSHeader*) info->response;
    end = info->response + result;
    ans = info->response + DNS_HLEN;
    for (i = 0; i < dns->qdcount; ++i)
    {
        ans = SkipName(ans, end);
        ans += 4;
    }

    switch (type)
    {
#ifdef RFC_2782
      case DNS_TYPE_NAPTR:
        break;
      case DNS_TYPE_SRV:
        result = 0;
        res = ans;

        // get additional record.
        if (0 < dns->arcount)
        {
            ar = ans;
            for (i = 0; i < dns->ancount + dns->nscount; ++i)
            {
                ar = SkipName(ar, end);
                if (ar)
                {
                    len = *(u16*) (ar + DNS_OFFSET_LEN);
                    ar += DNS_OFFSET_DATA + len;
                    if (end <= ar)
                    {
                        ar = NULL;
                    }
                }
            }
        }

        // The resolver must attempt to contact the target host
        // with the lowest-numbered priority it can reach.
        // The weight field specifies a relative weight for entries with the same priority.
        // Larger weights should be given a proportionately higher probability of being selected. [RFC2782]
        srvAns = NULL;
        priority = 0xffff;
        weight = 0;
        for (i = 0; i < dns->ancount; ++i, res += DNS_OFFSET_DATA + len)
        {
            res = SkipName(res, end);
            len = *(u16*) (res + DNS_OFFSET_LEN);

            if (*((u16*) res) != DNS_TYPE_SRV)
            {
                continue;
            }

            ansPriority = *(u16*) (res + DNS_OFFSET_SRV_PRIO);
            ansWeight = *(u16*) (res + DNS_OFFSET_SRV_WEIGHT);

            if (priority < ansPriority ||
                (priority == ansPriority && ansWeight <= weight))
            {
                continue;
            }

            srvAns = res;
            priority = ansPriority;
            weight = ansWeight;
        }

        if (!srvAns)
        {
            break;
        }
        res = srvAns;
        len = *(u16*) (res + DNS_OFFSET_LEN);

        arcount = dns->arcount; // save arcount.
        srv = res + DNS_OFFSET_SRV_TARGET;

        // Record srv->port.
        cmd->data.ai.port = *(u16*) (res + DNS_OFFSET_SRV_PORT);
        cmd->precallback = NULL;
        switch (cmd->data.ai.hints->family)
        {
          case SO_PF_INET:
            cmd->data.ai.type = DNS_TYPE_A;
            break;
#ifdef IP_INET6
          case SO_PF_INET6:
            cmd->data.ai.type = DNS_TYPE_AAAA;
            break;
#endif // IP_INET6
        }
        cmd->callback = GetAddrInfoCallback;

        req = DupName(dns, end, res + DNS_OFFSET_SRV_TARGET, req);
        *(u16*) req = cmd->data.ai.type;
        req += 2;
        *(u16*) req = DNS_CLASS_IN;     // Class = Internet
        req += 2;

        info->queryLen = req - info->query;

        if ((info->flag & DNS_FLAG_EDNS0) && !(info->flag & DNS_FLAG_TCP))
        {
            req = AppendOpt(dns, req);
        }
        info->sendLen = (u16) (req - info->query);

        type = cmd->data.ai.type;
        result = 0;
        res = ar;
        for (i = 0; i < arcount; ++i)
        {
            BOOL hit;
            hit = CmpName(dns, end, res, dns, end, srv);
            res = SkipName(res, end);
            len = *(u16*) (res + DNS_OFFSET_LEN);

            if (hit)
            {
                switch (*(u16*) res)
                {
                  case DNS_TYPE_A:
                    // ip_addr[4] is from res + DNS_OFFSET_DATA
                    if (type == DNS_TYPE_A && info->datalen < IP_ALEN * 35)
                    {
                        memmove(info->data, res + DNS_OFFSET_DATA, IP_ALEN);
                        info->data += IP_ALEN;
                        info->datalen += IP_ALEN;
                        result += IP_ALEN;
                    }
                    break;
                  case DNS_TYPE_AAAA:
                    // ip_addr[16] is from res + DNS_OFFSET_DATA
                    if (type == DNS_TYPE_AAAA && info->datalen < 16 * 8)
                    {
                        memmove(info->data, res + DNS_OFFSET_DATA, 16);
                        info->data += 16;
                        info->datalen += 16;
                        result += 16;
                    }
                    break;
                  default:
                    break;
                }
            }
            res += DNS_OFFSET_DATA + len;
            ans = res;
        }

        if (result == 0)
        {
            IFEnqueueHead(DNSCommand*, &info->queue, cmd, link);
            return;
            // NOT REACHED HERE
        }

        res += DNS_OFFSET_DATA + len;
        ans = res;
        break;
#endif // RFC_2782
      case DNS_TYPE_A:
      case DNS_TYPE_AAAA:
        result = 0;
        res = ans;
        for (i = 0; i < dns->ancount; ++i)
        {
            res = SkipName(res, end);
            len = *(u16*) (res + DNS_OFFSET_LEN);
            switch (*(u16*) res)
            {
              case DNS_TYPE_A:
                // ip_addr[4] is from res + DNS_OFFSET_DATA
                if (type == DNS_TYPE_A && info->datalen < IP_ALEN * 35)
                {
                    memmove(info->data, res + DNS_OFFSET_DATA, IP_ALEN);
                    info->data += IP_ALEN;
                    info->datalen += IP_ALEN;
                    result += IP_ALEN;
                }
                break;
              case DNS_TYPE_AAAA:
                // ip_addr[16] is from res + DNS_OFFSET_DATA
                if (type == DNS_TYPE_AAAA && info->datalen < 16 * 8)
                {
                    memmove(info->data, res + DNS_OFFSET_DATA, 16);
                    info->data += 16;
                    info->datalen += 16;
                    result += 16;
                }
                break;
              case DNS_TYPE_CNAME:
                if (cmd->data.ai.cname)
                {
                    CopyName(dns, res + DNS_OFFSET_DATA + len, res + DNS_OFFSET_DATA,
                             cmd->data.ai.cname, SO_MAXDNAME);
                }
                break;
              default:
                break;
            }
            res += DNS_OFFSET_DATA + len;
            ans = res;
        }
        break;
      default:
        break;
    }

Error:

#ifdef RFC_2782
    if (type == DNS_TYPE_SRV)   // should check result
    {
        // If no SRV records were found, the client performs an A or AAAA record
        // lookup of the domain name. [RFC 3263]
        switch (cmd->data.ai.hints->family)
        {
          case SO_PF_INET:
            cmd->data.ai.type = DNS_TYPE_A;
            break;
#ifdef IP_INET6
          case SO_PF_INET6:
            cmd->data.ai.type = DNS_TYPE_AAAA;
            break;
#endif // IP_INET6
        }

        if (cmd->data.ai.port == 0)
        {
            if (cmd->data.ai.servName)
            {
#ifdef IOP_OS
                if (strnicmp(cmd->data.ai.servName, "sip", sizeof("sip")) == 0)
#else
                if (stricmp(cmd->data.ai.servName, "sip") == 0)
#endif // IOP_OS
                {
                    cmd->data.ai.port = 5060;
                }
#ifdef IOP_OS
                else if (strnicmp(cmd->data.ai.servName, "sips", sizeof("sips")) == 0)
#else
                else if (stricmp(cmd->data.ai.servName, "sips") == 0)
#endif // IOP_OS
                {
                    cmd->data.ai.port = 5061;
                }
            }
        }
        cmd->callback = GetAddrInfoCallback;
        IFEnqueueHead(DNSCommand*, &info->queue, cmd, link);
        return;
        // NOT REACHED HERE
    }
#endif // RFC_2782

    if (cmd->result)
    {
        *cmd->result = result;
    }

    if (cmd->data.ai.callback)
    {
        cmd->data.ai.callback(cmd->info, result);
    }
}

int SOGetAddrInfoAsync(const char* nodeName, const char* servName,
                       const SOAddrInfo* hints,
                       DNSCommand* cmd, u8* addrList,
                       DNSCallback callback, int* result)
{
#ifdef IOP_OS
    int  rc = 0;
#else
    int  rc;
#endif // IOP_OS
    BOOL doNode;
    BOOL doServ;
    BOOL numeric;
    u16  type = 0;
    int  sockType = 0;

    cmd->data.ai.cname = NULL;

    ASSERT(hints);
    switch (hints->family)
    {
      case SO_PF_INET:
#ifdef IP_INET6
      case SO_PF_INET6:
#endif // IP_INET6
        break;
      case SO_PF_UNSPEC:
      default:
        rc = SO_EAI_FAMILY;
        goto Error;
        break;
    }

    switch (hints->sockType)
    {
      case 0:
        break;
      case SO_SOCK_DGRAM:
      case SO_SOCK_STREAM:
        sockType = hints->sockType;
        break;
      default:
        rc = SO_EAI_SOCKTYPE;
        goto Error;
        break;
    }

    switch (hints->protocol)
    {
      case 0:
        break;
      case SO_IPPROTO_TCP:
        sockType = SO_SOCK_STREAM;
        break;
      case SO_IPPROTO_UDP:
        sockType = SO_SOCK_DGRAM;
        break;
      default:
        rc = SO_EAI_SOCKTYPE;
        goto Error;
        break;
    }

    doNode = (nodeName && nodeName[0]);
    doServ = (servName && servName[0]);

    if (!doNode)
    {
        if (hints->flags & SO_AI_NUMERICHOST)
        {
            rc = SO_EAI_NONAME;
            goto Error;
        }

        switch (hints->family)
        {
          case SO_PF_INET:
            if (hints->flags & SO_AI_PASSIVE)
            {
                nodeName = "0.0.0.0";       // SO_INADDR_ANY
            }
            else
            {
                nodeName = "127.0.0.1";     // SO_INADDR_LOOPBACK
            }
            break;
#ifdef IP_INET6
          case SO_PF_INET6:
            if (hints->flags & SO_AI_PASSIVE)
            {
                nodeName = "::";            // SO_IN6ADDR_ANY_INIT
            }
            else
            {
                nodeName = "::1";           // SO_IN6ADDR_LOOPBACK_INIT
            }
            break;
#endif // IP_INET6
       }
    }
    else if (SO_MAXDNAME <= strlen(nodeName))
    {
        rc = SO_EAI_NONAME;
        goto Error;
    }

    if (SOInetPtoN(hints->family, nodeName, addrList) == 1)
    {
        numeric = TRUE;
        switch (hints->family)
        {
          case SO_PF_INET:
            rc = IP_ALEN;
            break;
#ifdef IP_INET6
          case SO_PF_INET6:
            rc = sizeof(SOIn6Addr);
            break;
#endif // IP_INET6
        }
    }
    else
    {
        numeric = FALSE;
        if (hints->flags & SO_AI_NUMERICHOST)
        {
            rc = SO_EAI_NONAME;
            goto Error;
        }
    }

    if (!doServ)
    {
        if (hints->flags & SO_AI_NUMERICSERV)
        {
            rc = SO_EAI_NONAME;
            goto Error;
        }

        if (!numeric)
        {
            switch (hints->family)
            {
              case SO_PF_INET:
                type = DNS_TYPE_A;
                break;
#ifdef IP_INET6
              case SO_PF_INET6:
                type = DNS_TYPE_AAAA;
                break;
#endif // IP_INET6
            }
        }

        cmd->data.ai.port = 0;
    }
    else
    {
        if ((isdigit)(servName[0]))
        {
            cmd->data.ai.port = (u16) atoi(servName);
        }
        else
        {
            cmd->data.ai.port = 0;
            if (hints->flags & SO_AI_NUMERICSERV)
            {
                rc = SO_EAI_NONAME;
                goto Error;
            }
        }

        // Select a transport protocol
        if (sockType == 0)
        {
#ifdef RFC_2782
            if (!numeric && cmd->data.ai.port == 0)  // no protocol or port is specified
            {
                type = DNS_TYPE_NAPTR;      // Perform a NAPTR query
            }
            else if (stricmp(servName, "sip") == 0)
            {
                sockType = SO_SOCK_DGRAM;   // UDP for sip
            }
            else if (stricmp(servName, "sips") == 0)
            {
                sockType = SO_SOCK_STREAM;  // TCP for sips
            }
            else
#endif // RFC_2782
            {
                rc = SO_EAI_SERVICE;
                goto Error;
            }
        }

        // determine the IP address and port.
        if (numeric)
        {
            if (cmd->data.ai.port == 0)
            {
#ifdef RFC_2782
                if (stricmp(servName, "sip") == 0)
                {
                    cmd->data.ai.port = 5060;
                }
                else if (stricmp(servName, "sips") == 0)
                {
                    cmd->data.ai.port = 5061;
                }
                else
#endif // RFC_2782
                {
                    rc = SO_EAI_SERVICE;
                    goto Error;
                }
            }
        }
        else if (cmd->data.ai.port)
        {
            // Performs an A or AAAA record lookup if a port is present.
            switch (hints->family)
            {
              case SO_PF_INET:
                type = DNS_TYPE_A;
                break;
#ifdef IP_INET6
              case SO_PF_INET6:
                type = DNS_TYPE_AAAA;
                break;
#endif // IP_INET6
            }
        }
#ifdef RFC_2782
        else if (type == 0)
        {
            // performs an SRV query
            type = DNS_TYPE_SRV;
        }
#endif // RFC_2782
    }

    if (type == 0)
    {
        goto Error; // No DNS lookup is required.
    }

    cmd->func = DNS_FUNC_ADDR_INFO;
    cmd->precallback = PreGetAddrInfo;
    cmd->callback = GetAddrInfoCallback;
#ifdef IOP_OS
    cmd->result = (s32*) result;   // XXX
#else
    cmd->result = (long*) result;   // XXX
#endif // IOP_OS

    cmd->data.ai.nodeName = nodeName;
    cmd->data.ai.servName = servName;
    cmd->data.ai.hints = hints;
    cmd->data.ai.type = type;
    cmd->data.ai.sockType = sockType;
    cmd->data.ai.addrList = addrList;
    cmd->data.ai.callback = callback;

    if (doNode && hints && (hints->flags & SO_AI_CANONNAME))
    {
        cmd->data.ai.cname = SOAlloc(SO_MEM_CANONNAME, SO_MAXDNAME);
        if (cmd->data.ai.cname == NULL)
        {
            rc = SO_EAI_MEMORY;
            goto Error;
        }
#ifdef IOP_OS
        strncpy(cmd->data.ai.cname, nodeName, strnlen(nodeName, SO_MAXDNAME));
#else
        strcpy(cmd->data.ai.cname, nodeName);
#endif // IOP_OS
    }
    else
    {
        cmd->data.ai.cname = NULL;
    }

    DNSGo(&__SOResolver.info, cmd);
    return 0;
    // NOT REACHED HERE

Error:
    if (result)
    {
        *result = rc;
    }
    return rc;
}

/*---------------------------------------------------------------------------*
  Name:         SOGetAddrInfo

  Description:  Translate a node name and/or a service name to a set
                of socket addresses.

  Arguments:

  Returns:
 *---------------------------------------------------------------------------*/
static int GetAddrInfo(const char* nodeName, const char* servName,
                       const SOAddrInfo* hints, SOAddrInfo** res)
{
    volatile int result;
    DNSCommand   cmd;
    u8           addrList[IP_ALEN * 35];
    BOOL         enabled;

    int          offset;
#ifdef IOP_OS
    SOAddrInfo*  ai = NULL;
    SOAddrInfo*  next;

    int          alen = 0;
#else
    SOAddrInfo*  ai;
    SOAddrInfo*  next;

    int          alen;
#endif // IOP_OS

    ASSERT(hints);
    if (res == NULL)
    {
        return SO_EAI_SYSTEM;
    }
    *res = NULL;

    SOGetAddrInfoAsync(nodeName, servName, hints,
                       &cmd, addrList,
                       SyncCallback, (int*) &result);

    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&__SOResolver.info.queueThread);
    }
    OSRestoreInterrupts(enabled);

    if (result <= 0)
    {
        if (cmd.data.ai.cname)
        {
            SOFree(SO_MEM_CANONNAME, cmd.data.ai.cname, SO_MAXDNAME);
        }
        switch (result)
        {
          case 0:
          case IP_ERR_DNS_NAME:
            return SO_EAI_NONAME;
          case IP_ERR_DNS_FORMAT:
          case IP_ERR_DNS_SERVER:
          case IP_ERR_DNS_NOTIMP:
          case IP_ERR_DNS_REFUSED:
          default:
            return SO_EAI_FAIL;
        }
    }

    // Form response
    switch (hints->family)
    {
      case SO_PF_INET:
        alen = 4;
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        alen = 16;
        break;
#endif // IP_INET6
    }
    for (offset = result - alen, result = 0, next = NULL;
         0 <= offset;
         offset -= alen, next = ai)
    {
        ai = SOAlloc(SO_MEM_ADDRINFO, sizeof(SOAddrInfo));
        if (ai)
        {
            ai->flags = 0;  // Undefined in Posix
            ai->family = hints->family;
            ai->sockType = cmd.data.ai.sockType;
            ai->protocol = 0;
            switch (ai->family)
            {
              case SO_PF_INET:
                ai->addrLen = sizeof(SOSockAddrIn);
                break;
#ifdef IP_INET6
              case SO_PF_INET6:
                ai->addrLen = sizeof(SOSockAddrIn6);
                break;
#endif // IP_INET6
            }
            if (offset == 0)
            {
                ai->canonName = cmd.data.ai.cname;
                cmd.data.ai.cname = NULL;
            }
            else
            {
                ai->canonName = NULL;
            }
            ai->next = next;
            switch (hints->family)
            {
              case SO_PF_INET:
                if (!(hints->flags & SO_AI_V4MAPPED))
                {
                    ai->addr = SOAlloc(SO_MEM_SOCKADDR, sizeof(SOSockAddrIn));
                    if (ai->addr)
                    {
                        SOSockAddrIn* sockAddr = ai->addr;

                        memset(sockAddr, 0, sizeof(SOSockAddrIn));
                        sockAddr->len = sizeof(SOSockAddrIn);
                        sockAddr->family = SO_PF_INET;
                        sockAddr->port = cmd.data.ai.port;
                        memmove(&sockAddr->addr, &addrList[offset], (size_t) alen);
                    }
                }
#ifdef IP_INET6
                else
                {
                    ai->addr = SOAlloc(SO_MEM_SOCKADDR, sizeof(SOSockAddrIn6));
                    if (ai->addr)
                    {
                        SOSockAddrIn6* sockAddr6 = ai->addr;

                        memset(sockAddr6, 0, sizeof(SOSockAddrIn6));
                        sockAddr6->len = sizeof(SOSockAddrIn6);
                        sockAddr6->family = SO_PF_INET6;
                        sockAddr6->port = cmd.data.ai.port;
                        sockAddr6->addr.addr[10] = sockAddr6->addr.addr[11] = 0xff;
                        memmove(&sockAddr6->addr.addr[12], &addrList[offset], (size_t) alen);
                    }
                }
#endif // IP_INET6
                break;
#ifdef IP_INET6
              case SO_PF_INET6:
                ai->addr = SOAlloc(SO_MEM_SOCKADDR, sizeof(SOSockAddrIn6));
                if (ai->addr)
                {
                    SOSockAddrIn6* sockAddr6 = ai->addr;

                    memset(sockAddr6, 0, sizeof(SOSockAddrIn6));
                    sockAddr6->len = sizeof(SOSockAddrIn6);
                    sockAddr6->family = SO_PF_INET6;
                    sockAddr6->port = cmd.data.ai.port;
                    memmove(&sockAddr6->addr, &addrList[offset], (size_t) alen);
                }
                break;
#endif // IP_INET6
            }
            if (ai->addr == NULL)
            {
                result = SO_EAI_MEMORY;
                SOFreeAddrInfo(ai);
                ai = NULL;
                if (cmd.data.ai.cname)
                {
                    SOFree(SO_MEM_CANONNAME, cmd.data.ai.cname, SO_MAXDNAME);
                }
                break;
            }
        }
        else
        {
            result = SO_EAI_MEMORY;
            SOFreeAddrInfo(next);
            ai = NULL;
            if (cmd.data.ai.cname)
            {
                SOFree(SO_MEM_CANONNAME, cmd.data.ai.cname, SO_MAXDNAME);
            }
            break;
        }
    }
    *res = ai;
    return result;
}

int SOGetAddrInfo(const char* nodeName, const char* servName,
                  const SOAddrInfo* hints, SOAddrInfo** res)
{
    SOAddrInfo  h;
    int         result;
    int         result2;
    SOAddrInfo* res2;
    SOAddrInfo* ai;

    if (hints == NULL)
    {
        memset(&h, 0, sizeof(SOAddrInfo));
    }
    else
    {
        memcpy(&h, hints, sizeof(SOAddrInfo));
    }
    switch (h.family)
    {
      case SO_PF_INET:
        h.flags &= ~(SO_AI_V4MAPPED | SO_AI_ALL);
        return GetAddrInfo(nodeName, servName, &h, res);
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        result = GetAddrInfo(nodeName, servName, &h, res);
        if (!(h.flags & SO_AI_V4MAPPED) ||
            (result == 0 && !(h.flags & SO_AI_ALL)))
        {
            return result;
        }
        h.family = SO_PF_INET;
        break;
      case SO_PF_UNSPEC:
        h.family = SO_PF_INET;
        result = GetAddrInfo(nodeName, servName, &h, res);
        if (result < 0 && result != SO_EAI_NONAME)
        {
            return result;
        }
        h.family = SO_PF_INET6;
        break;
#endif // IP_INET6
      default:
        return SO_EAI_FAMILY;
    }

    if (result == 0)
    {
        h.flags &= ~SO_AI_CANONNAME;
    }
    result2 = GetAddrInfo(nodeName, servName, &h, &res2);
    if (result2 < 0)
    {
        return result;
    }
    if (result < 0)
    {
        *res = res2;
        return result2;
    }
    for (ai = *res; ai->next; ai = ai->next)
    {
        ;
    }
    ai->next = res2;
    return 0;
}

/*---------------------------------------------------------------------------*
                                SOFreeAddrInfo
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
  Name:         SOFreeAddrInfo

  Description:  Frees SOAddrInfo structures returned by SOGetAddrInfo().

  Arguments:    head    Pointer to SOAddrInfo returned by SOGetAddrInfo().

  Returns:      None.
 *---------------------------------------------------------------------------*/
void SOFreeAddrInfo(SOAddrInfo* head)
{
    SOAddrInfo* ai;
    SOAddrInfo* next;

    if (head == NULL)
    {
        return;
    }
    for (ai = head; ai != NULL; ai = next)
    {
        if (ai->addr)
        {
            SOFree(SO_MEM_SOCKADDR, ai->addr, ((SOSockAddr*) ai->addr)->len);
        }
        if (ai->canonName)
        {
            SOFree(SO_MEM_CANONNAME, ai->canonName, SO_MAXDNAME);
        }
        next = ai->next;
        SOFree(SO_MEM_ADDRINFO, ai, sizeof(SOAddrInfo));
    }
}

/*---------------------------------------------------------------------------*
                                GetNameInfo
 *---------------------------------------------------------------------------*/

static s32 PreGetNameInfo(DNSInfo* info, DNSCommand* cmd)
{
    const SOSockAddrIn*  sockAddr = cmd->data.ni.sa;
#ifdef IP_INET6
    const SOSockAddrIn6* sockAddr6 = cmd->data.ni.sa;
#endif // IP_INET6
    const u8*            addr;
    DNSHeader*           dns;
    u8*                  opt;
    u8*                  count;
    int                  i;

    // Form the request
    dns = (DNSHeader*) &info->query[0];
    dns->flags = DNS_FLAG_Q | DNS_OP_QUERY;
    if ((info->flag & (DNS_FLAG_BROADCAST | DNS_FLAG_MULTICAST)) == 0)
    {
        dns->flags |= DNS_FLAG_RD;
    }
    dns->qdcount = 1;
    dns->ancount = 0;
    dns->nscount = 0;
    dns->arcount = 0;

    // Put name into DNS name format
    opt = info->query + DNS_HLEN;
    switch (sockAddr->family)
    {
      case SO_PF_INET:
        addr = (u8*) &sockAddr->addr;
        for (i = 3; 0 <= i; --i)
        {
            count = opt++;
#ifdef IOP_OS
            *count = (u8) snprintf((char*) opt, 
                (sizeof(info->query) - ((u8*) opt - (u8*) info->query)), 
                "%d", addr[i]);
#else
            *count = (u8) sprintf((char*) opt, "%d", addr[i]);
#endif // IOP_OS
            opt += *count;
        }
        *opt++ = 7;
        memmove(opt, "in-addr", 7);
        opt += 7;
        *opt++ = 4;
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        addr = (u8*) &sockAddr6->addr;
        for (i = 15; 0 <= i; --i)
        {
            *opt++ = 1;
#ifdef IOP_OS
            snprintf((char*) opt, 
                (sizeof(info->query) - ((u8*) opt - (u8*) info->query)), 
                "%x", addr[i] & 0x0f);
            ++opt;
            *opt++ = 1;
            snprintf((char*) opt,
                (sizeof(info->query) - ((u8*) opt - (u8*) info->query)), 
                "%x", addr[i] >> 4);
#else
            sprintf((char*) opt, "%x", addr[i] & 0x0f);
            ++opt;
            *opt++ = 1;
            sprintf((char*) opt, "%x", addr[i] >> 4);
#endif
            ++opt;
        }
        *opt++ = 3;
        memmove(opt, "ip6", 3);
        opt += 3;
        *opt++ = 4;
        break;
#endif // IP_INET6
    }
    memmove(opt, "arpa", 4);
    opt += 4;
    *opt++ = 0;

    *(u16*) opt = DNS_TYPE_PTR;     // Type = Domain name pointer
    opt += 2;

    *(u16*) opt = DNS_CLASS_IN;     // Class = Internet
    opt += 2;

    info->queryLen = opt - info->query;

    if ((info->flag & DNS_FLAG_EDNS0) && !(info->flag & DNS_FLAG_TCP))
    {
        opt = AppendOpt(dns, opt);
    }
    info->sendLen = (u16) (opt - info->query);

    info->data = NULL;
    info->datalen = 0;
    return 0;
}

static void GetNameInfoCallback(DNSCommand* cmd, s32 result)
{
    DNSInfo*    info;
    DNSHeader*  dns;
    u8*         res;
    u8*         end;
    u8*         ans;
    int         i;
    u16         len;
    u16         type;
    char*       name;
    char**      aliases;
    char*       alias;

    ASSERT(cmd);
    info = cmd->info;
    if (result < 0)
    {
        goto Error;
    }

    if (__SOResolver.name == cmd->data.ni.node)
    {
        // SOGetNameInfo() is called from SOGetHostByAddr(). Update alases.
        alias = __SOResolver.buf;
        aliases = (char**) &__SOResolver.ptrList[2];
    }
    else
    {
        alias = NULL;
        aliases = NULL;
    }

    // Parse the response
    ASSERT(info);
    dns = (DNSHeader*) info->response;
    end = info->response + result;
    ans = info->response + DNS_HLEN;
    for (i = 0; i < dns->qdcount; ++i)
    {
        ans = SkipName(ans, end);
        ans += 4;
    }

    result = 0;
    name = 0;
    res = ans;
    for (i = 0; i < dns->ancount; ++i)
    {
        res = SkipName(res, end);
        len = *(u16*) (res + DNS_OFFSET_LEN);
        type = *(u16*) res;
        switch (type)
        {
          case DNS_TYPE_PTR:
            if (name == NULL)
            {
                name = CopyName(dns, res + DNS_OFFSET_DATA + len, res + DNS_OFFSET_DATA,
                                cmd->data.ni.node, (s32) cmd->data.ni.nodeLen);
                if (name != NULL)
                {
                    result = name - cmd->data.ni.node;
                }
            }
            else if (alias && (aliases - (char**) __SOResolver.ptrList < 72))
            {
                char* next;

                next = CopyName(dns, res + DNS_OFFSET_DATA + len, res + DNS_OFFSET_DATA,
                                alias, (s32) sizeof(__SOResolver.buf) - 1 - (alias - __SOResolver.buf));
                if (next)
                {
                    *aliases++ = alias;
                    alias = next;
                    *alias++ = '\0';
                }
            }
            break;
          default:
            break;
        }
        res += 10 + len;
        ans = res;
    }

    if (alias)
    {
        *aliases = NULL;
        __SOResolver.ent.aliases =  (char**) &__SOResolver.ptrList[2];
    }

Error:
    if (cmd->result)
    {
        *cmd->result = result;
    }
    OSWakeupThread(&info->queueThread);
}

/*---------------------------------------------------------------------------*
  Name:         SOGetNameInfo

  Description:  Translate a socket address to a node and service name.

  Arguments:

  Returns:
 *---------------------------------------------------------------------------*/
int SOGetNameInfo(const void* sa,
                  char* node, unsigned nodeLen,
                  char* service, unsigned serviceLen,
                  int flags)
{
    DNSCommand           cmd;
    vs32                 result;
    BOOL                 doService;
    BOOL                 doNode;
    BOOL                 enabled;
    const SOSockAddrIn*  sockAddr = sa;
#ifdef IP_INET6
    const SOSockAddrIn6* sockAddr6 = sa;

    if (sockAddr->family != SO_PF_INET &&
        sockAddr->family != SO_PF_INET6)
#else // IP_INET6
    if (sockAddr->family != SO_PF_INET)
#endif // IP_INET6
    {
        return SO_EAI_FAMILY;
    }

    doService = (0 < serviceLen && service);
    doNode = (0 < nodeLen && node);

    if (!doService && !doNode)
    {
        return SO_EAI_NONAME;
    }

#ifndef IOP_OS // MX TODO
    if (doService)
    {
        u16 port = SONtoHs(sockAddr->port);

        if (flags & SO_NI_NUMERICSERV)
        {
            snprintf(service, serviceLen, "%d", port);
        }
#ifdef RFC_2782
        else if (port == 5060)
        {
            snprintf(service, serviceLen, "sip");
        }
#endif // RFC_2782
        else
        {
            snprintf(service, serviceLen, "%d", port);
        }
    }
#endif // IOP_OS

    if (!doNode)
    {
        return 0;
    }

    if (flags & SO_NI_NUMERICHOST)
    {
        goto Numeric;
    }

    cmd.func = DNS_FUNC_NAME_INFO;
    cmd.precallback = PreGetNameInfo;
    cmd.callback = GetNameInfoCallback;
#ifdef IOP_OS
    cmd.result = (s32*) &result;
#else
    cmd.result = (long*) &result;
#endif // IOP_OS

    cmd.data.ni.sa = sa;
    cmd.data.ni.node = node;
    cmd.data.ni.nodeLen = nodeLen;

    DNSGo(&__SOResolver.info, &cmd);
    enabled = OSDisableInterrupts();
    while (result == IP_ERR_BUSY)
    {
        OSSleepThread(&__SOResolver.info.queueThread);
    }
    OSRestoreInterrupts(enabled);

    if (0 < result)
    {
        if (flags & SO_NI_NOFQDN)
        {
            char* dot;

            if ((dot = strchr(node, '.')) != NULL)
            {
                *dot = '\0';
            }
        }
        return 0;
    }
    else if (flags & SO_NI_NAMEREQD)
    {
        return SO_EAI_NONAME;
    }

Numeric:
    if (sockAddr->family == SO_PF_INET &&
        SOInetNtoP(sockAddr->family, &sockAddr->addr, node, nodeLen))
    {
        return 0;
    }
#ifdef IP_INET6
    if (sockAddr6->family == SO_PF_INET6 &&
        SOInetNtoP(sockAddr6->family, &sockAddr6->addr, node, nodeLen))
    {
        return 0;
    }
#endif // IP_INET6
    return SO_EAI_FAMILY;
}


//
// DNS unit test functions
//

u8* __DNSSkipName(const u8* ptr, const u8* end)
{
    return SkipName(ptr, end);
}

char* __DNSCopyName(const DNSHeader* dns, const u8* end, const u8* ptr,
                    char* name, s32 namelen)
{
    return CopyName(dns, end, ptr, name, namelen);
}

u8* __DNSDupName(const DNSHeader* dns, const u8* end, const u8* ptr, u8* opt)
{
    return DupName(dns, end, ptr, opt);
}

BOOL __DNSCmpName(const DNSHeader* dns0, const u8* end0, const u8* name0,
                  const DNSHeader* dns1, const u8* end1, const u8* name1)
{
    return CmpName(dns0, end0, name0, dns1, end1, name1);
}

BOOL __DNSCompName(const DNSHeader* dns, const u8* end, u8* name1, u8* name2)
{
    return CmpName(dns, end, name1, dns, end, name2);
}

u8* __DNSCheckName(const DNSHeader* dns, const u8* end, const u8* ptr)
{
    return CheckName(dns, end, ptr);
}
