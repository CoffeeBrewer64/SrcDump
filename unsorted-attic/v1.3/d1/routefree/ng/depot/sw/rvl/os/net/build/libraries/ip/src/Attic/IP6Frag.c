/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IP6Frag.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IP6Frag.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    31    3/06/06 16:07 Shiki
    Enabled IPv6 by default by globally defining IP_INET6.

    30    2/14/06 18:47 Shiki
    Revised to collect interface statistics.

    29    2/07/06 11:19 Shiki
    Modified Reassemble() to check fragment plen to send ICMP6_PARAM_PROB
    message.

    28    1/26/06 16:28 Shiki
    Revised IP6Fragment() to support Packet Size Issues in RFC 2460.

    27    1/26/06 11:30 Shiki
    Modified IP6Fragment () to support PMTU.

    26    1/23/06 9:07 Shiki
    Fixed IP6Reassemble().

    25    1/13/06 13:02 Shiki
    Revised ICMP6SendError() to check received packet before sending an
    error message.

    24    1/11/06 14:42 Shiki
    Fixed IPv6 to use interface->linkMTU instead of interface->mtu.

    23    1/11/06 9:50 Shiki
    Clean up.

    22    1/11/06 9:13 Shiki
    Fixed TimeoutHandler().

    21    1/10/06 19:00 Shiki
    Revised IP6Reassemble() implementation.

    19    04/10/12 20:23 Ueno_kyu
    Enclosed IPv6 specific codes in #ifdef IP_INET6... #endif blocks.

    18    04/10/12 15:29 Ueno_kyu
    Replaced IP6_HLEN as sizeof(IP6Hdr).
    Replaced SO_IN6_ARE_ADDR_NOT_EQUAL() as !SO_IN6_ARE_ADDR_EQUAL().

    17    04/09/30 14:29 Ueno_kyu
    Modified SetFragmentHeader() to initialize 2-bit reserved field of
    fragment heaeder.

    16    04/09/28 20:18 Ueno_kyu
    Modified IP6Fragment() to use the IPv6 minimum link MTU to send a
    multicast datagram or a UDP unicast datagram.

    15    04/09/22 10:42 Ueno_kyu
    Cleanup.

    14    04/09/21 16:19 Ueno_kyu
    Cleanup.

    13    04/09/21 14:20 Ueno_kyu
    Added support for IPv6.

    2     04/09/02 8:56 Ueno_kyu
    Modified TimeoutHandler() not to send an ICMPv6 Time Exceeded message
    as a result of receiving a packet destined to an IPv6 multicast
    address.

    1     04/08/31 19:24 Ueno_kyu
    Initial checkin.

  $NoKeywords: $

   [RFC 2460]

   original packet:

   +------------------+----------------------//-----------------------+
   |  Unfragmentable  |                 Fragmentable                  |
   |       Part       |                     Part                      |
   +------------------+----------------------//-----------------------+

    The Unfragmentable Part consists of the IPv6 header plus any
    extension headers that must be processed by nodes en route to the
    destination, that is, all headers up to and including the Routing
    header if present, else the Hop-by-Hop Options header if present,
    else no extension headers.


   fragment packets:

   +------------------+--------+--------------+
   |  Unfragmentable  |Fragment|    first     |
   |       Part       | Header |   fragment   |
   +------------------+--------+--------------+

   +------------------+--------+--------------+
   |  Unfragmentable  |Fragment|    second    |
   |       Part       | Header |   fragment   |
   +------------------+--------+--------------+
                         o
                         o
                         o
   +------------------+--------+----------+
   |  Unfragmentable  |Fragment|   last   |
   |       Part       | Header | fragment |
   +------------------+--------+----------+

 *---------------------------------------------------------------------------*/

#include <dolphin/os.h>
#include <dolphin/ip.h>
#include "IPPrivate.h"
#include "IP6Private.h"

#define IP6_FRAG_OFFSET(fragHeader)    ((u16) ((fragHeader)->offlg & 0xfff8))
#define IP6_MFRAG(fragHeader)          ((fragHeader)->offlg & 0x0001)
#define IP6_FRAG_HLEN                  8

//
// IP Datagram Reassembly
//

#define HOLE_LEN    8   // Minimum size of a hole is eight bytes
#define EOH         1   // end-of-hole mark (EOH % HOLE_LEN != 0)
#define SPACE       ((s32) (sizeof(IP6Reassembled) - sizeof(IP6Hdr)))

// Fragment hole descriptor
typedef struct IPHole
{
    u16 first;
    u16 last;
    u16 next;
    u16 _unused;
} IPHole;

// Partially reassembled datagram
typedef struct IP6Reassembled
{
    IPInterface* interface;
    u32          flag;

    // If insufficient fragments are received to complete reassembly of a
    // packet within 60 seconds of the reception of the first-arriving
    // fragment of that packet, reassembly of that packet must be
    // abandoned and all the fragments that have been received for that
    // packet must be discarded.  If the first fragment (i.e., the one
    // with a Fragment Offset of zero) has been received, an ICMP Time
    // Exceeded -- Fragment Reassembly Time Exceeded message should be
    // sent to the source of that fragment. [RFC 2460]
    IP6Hdr       first;
    IP6Frag      frag;

    s32          unfragmentableLen; // length of the unfragmentable part
    u16          head;              // the head of the IPHole list

    // Partially reassembled datagram followed by data (total Control.mtu byte)
    IP6Hdr       header;
} IP6Reassembled;

#define INITIALIZED 0x01

// Reassemble buffer control
typedef struct IPReassembleControl
{
    u32     flag;
    u8*     buffer;
    s32     len;        // size of buffer
    s32     mtu;
    s32     size;       // size of each IP6Reassembled chunk
    OSAlarm alarm;
} IPReassembleControl;

static IPReassembleControl Control;

static void TimeoutHandler(OSAlarm* alarm, OSContext* context)
{
#ifndef IOP_OS
    #pragma unused( alarm, context )
#endif // IOP_OS
    IP6Reassembled* packet;
    IP6Hdr*      header;
    IP6Hdr*      first;

#ifdef IOP_OS
    TCPIP_UNUSED(alarm);
    TCPIP_UNUSED(context);
#endif // IOP_OS
    
    if (Control.buffer == NULL)
    {
        return;
    }

    for (packet = (IP6Reassembled*) Control.buffer;
         packet < (IP6Reassembled*) (Control.buffer + Control.len);
         packet = (IP6Reassembled*) ((u8*) packet + Control.size))
    {
        header = &packet->header;

        // Time-to-live check (60 sec)
        if (header->flow != 0)
        {
            if (header->hops <= 1)
            {
                // Expired. The partially-reassembled datagram MUST be discarded.

                // Send ICMP Time Exceeded -- Fragment Reassembly Time Exceeded message.
                // [RFC 2460 SHOULD]
                first = &packet->first;
                if (first->flow != 0)
                {
                    // Restore the original first fragment.
                    memmove(header, first, sizeof(IP6Hdr));
                    memmove((u8*) header + packet->unfragmentableLen + IP6_FRAG_HLEN,
                            (u8*) header + packet->unfragmentableLen,
                            sizeof(IP6Hdr) + first->plen - packet->unfragmentableLen - IP6_FRAG_HLEN);
                    memmove((u8*) header + packet->unfragmentableLen, &packet->frag,
                            sizeof(IP6Frag));
                    ICMP6SendError(packet->interface, ICMP6_TIME_EXCEEDED,
                                   ICMP6_TIME_EXCEED_REASSEMBLY, header, packet->flag, 0);
                }

                header->flow = 0;
                ++packet->interface->ipv6Stat.reasmFails;
            }
            else
            {
                --header->hops;
            }
        }
    }
}

s32 IP6SetReassemblyBuffer(void* buffer, s32 len, s32 mtu)
{
    BOOL enabled;
    s32  size;      // size of IP6Reassembled block

    mtu = MAX(mtu, IP6_MIN_MTU);
    mtu = MIN(mtu, 65535);
    size = SPACE + mtu + HOLE_LEN;
    size = (s32) OSRoundUp32B(size);
    if (buffer == NULL || len < size)
    {
        if (Control.flag & INITIALIZED)
        {
            OSCancelAlarm(&Control.alarm);
            Control.flag &= ~INITIALIZED;
        }
        return IP_ERR_INVALID;
    }

    len -= len % size;
    memset(buffer, 0, (u32) len);

    enabled = OSDisableInterrupts();

    Control.buffer = buffer;
    Control.len    = len;
    Control.mtu    = mtu;
    Control.size   = size;

    if ((Control.flag & INITIALIZED) == 0)
    {
        Control.flag |= INITIALIZED;
        OSCreateAlarm(&Control.alarm);
        OSSetPeriodicAlarm(&Control.alarm, OSGetTime(), OSSecondsToTicks(1), TimeoutHandler);
    }

    OSRestoreInterrupts(enabled);
    return IP_ERR_NONE;
}

// Reassemble() implements RFC 815 algorithm.
static IP6Hdr* Reassemble(IP6Reassembled* packet, IP6Hdr* frag, IP6Frag* fragHdr, s32 mtu)
{
    IPHole* hole;
    IPHole* newHole;
    s32     first;
    s32     last;
    u16*    next;
    s32     len;
    s32     offset;
    s32     plen;

    u16     holeFirst;
    u16     holeLast;
    IP6Hdr* header = &packet->header;

    ASSERT(packet->frag.ident == fragHdr->ident);
    ASSERT(SO_IN6_ARE_ADDR_EQUAL(&header->src, &frag->src));
    ASSERT(SO_IN6_ARE_ADDR_EQUAL(&header->dst, &frag->dst));
    ASSERT(header->flow != 0);
    ASSERT((u8*) frag + sizeof(IP6Hdr) <= (u8*) fragHdr);

    first = IP6_FRAG_OFFSET(fragHdr);
    len   = (s32) sizeof(IP6Hdr) + frag->plen - ((u8*) fragHdr - (u8*) frag) - IP6_FRAG_HLEN;
    last  = first + len - 1;

    // Update packet->plen. Note a Fragment Offset containing the offset of the fragment,
    // in 8-octet units, relative to the start of the Fragmentable Part of the original packet.
    plen = (s32) (packet->unfragmentableLen - sizeof(IP6Hdr) + last + 1);
    if (IP6_MFRAG(fragHdr) && len % 8 != 0)
    {
        ICMP6SendError(packet->interface, ICMP6_PARAM_PROB, ICMP6_PARAMPROB_HEADER,
                       frag, packet->flag, (u16) ((u8*) &frag->plen - (u8*) frag));
        header->flow = 0;
        return NULL;
    }

    if (65535 < plen)
    {
        ICMP6SendError(packet->interface, ICMP6_PARAM_PROB, ICMP6_PARAMPROB_HEADER,
                       frag, packet->flag, (u16) ((u8*) &fragHdr->offlg - (u8*) frag));
        header->flow = 0;
        return NULL;
    }

    if (mtu < sizeof(IP6Hdr) + plen || len <= 0)
    {
        header->flow = 0;
        return NULL;
    }
    header->plen = (u16) MAX(header->plen, plen);

    next = &packet->head;
    while (*next != EOH)
    {
        hole = (IPHole*) ((u8*) header + packet->unfragmentableLen + *next);

        if (hole->last < first || last < hole->first)
        {
            next = &hole->next;
            continue;
        }

        holeFirst = hole->first;
        holeLast  = hole->last;
        *next = hole->next; // Delete current hole

#if 0
        // Discard a packet whose fragmented part overlaps
        // the partially reassembled datagram.
        if (first < holeFirst || holeLast < last)
        {
            return NULL;
        }
#endif

        if (holeFirst < first)
        {
            newHole = hole;
            newHole->last = (u16) (first - 1);

            *next = newHole->first;
            next = &newHole->next;

            offset = 0;
        }
        else // if (first <= holeFirst)
        {
            offset = holeFirst - first;
        }

        if (last < holeLast)
        {
            if (IP6_MFRAG(fragHdr))
            {
                newHole = (IPHole*) ((u8*) header + packet->unfragmentableLen + last + 1);
                newHole->first = (u16) (last + 1);
                newHole->last = holeLast;
                newHole->next = *next;

                *next = newHole->first;
                next = &newHole->next;
            }
            else
            {
                *next = EOH;
            }
        }

        ASSERT(0 <= last - first + 1);   // Teardrop check
        memmove((u8*) header + packet->unfragmentableLen + first + offset,
                (u8*) fragHdr + IP6_FRAG_HLEN + offset,
                (u32) (last - first + 1));
    }

    if (packet->head == EOH)
    {
        return header;
    }
    else
    {
        return NULL;
    }
}

// Returns the pointer to the next header entry before the len octets from ip6.
static u8* GetNextHeaderBefore(IP6Hdr* ip6, s32 len)
{
    u8* hdr;
    s32 hlen;
    u8  next;

    ASSERT(sizeof(IP6Hdr) <= len);
    if (len == sizeof(IP6Hdr))
    {
        return &ip6->next;
    }
    next = ip6->next;
    hdr = (u8*) ip6 + sizeof(IP6Hdr);
    hlen = 0;
    len -= sizeof(IP6Hdr);
    while (0 < len)
    {
        hdr += hlen;
        switch (next)
        {
          case SO_IPPROTO_HOPOPTS:
          case SO_IPPROTO_DSTOPTS:
          case SO_IPPROTO_ROUTING:
            hlen = (1 + hdr[1]) << 3;
            next = hdr[0];
            len -= hlen;
            break;

          case SO_IPPROTO_FRAGMENT:
            hlen = IP6_FRAG_HLEN;
            next = hdr[0];
            len -= hlen;
            break;

          default:
            return NULL;
            break;
        }
    }
    ASSERT(len == 0);
    return hdr;
}

static IP6Hdr* RestoreOriginalPacket(IP6Hdr* header, IP6Reassembled* packet)
{
    u8* next = GetNextHeaderBefore(header, packet->unfragmentableLen);
    ASSERT(next && *next == SO_IPPROTO_FRAGMENT);
    *next = packet->frag.next;
    header->hops = packet->first.hops;
    return header;
}

// Saves the first fragment header for a possible ICMP time exceeded message
// Returns FALSE if frag appears to be too large or forged.
// Be careful. frag might have been retransmitted
static BOOL SaveFirstFragment(IP6Reassembled* packet, IP6Hdr* frag, IP6Frag* fragHdr)
{
    IP6Hdr* header;
    s32     unfragmentableLen;

    ASSERT(sizeof(IP6Hdr) <= (u8*) fragHdr - (u8*) frag);

    if (IP6_FRAG_OFFSET(fragHdr) != 0)
    {
        return TRUE;
    }
    unfragmentableLen = (u8*) fragHdr - (u8*) frag;
    if (frag->plen < unfragmentableLen - sizeof(IP6Hdr) + IP6_FRAG_HLEN + 8)
    {
        return FALSE;
    }
    if (packet->first.flow != 0)
    {
        return (unfragmentableLen == packet->unfragmentableLen) ? TRUE : FALSE;
    }

    memmove(&packet->first, frag, sizeof(IP6Hdr));
    memmove(&packet->frag, fragHdr, sizeof(IP6Frag));

    header = &packet->header;
    if (unfragmentableLen == packet->unfragmentableLen)
    {
        return TRUE;
    }

    // Make sure the datagram does not become too large (over 65535 byte)
    if (Control.mtu < sizeof(IP6Hdr) + header->plen - IP6_FRAG_HLEN)
    {
        // Fragment is too large or could be forged.
        return FALSE;
    }

    // Insert the IP Extension headers to the partially reassembled datagram
    memmove((u8*) header + unfragmentableLen, (u8*) header + sizeof(IP6Hdr),
            (u32) (header->plen + HOLE_LEN));
    memmove((u8*) header + sizeof(IP6Hdr), (u8*) frag + sizeof(IP6Hdr),
            (u32) unfragmentableLen - sizeof(IP6Hdr));
    header->plen += (unfragmentableLen - sizeof(IP6Hdr));
    packet->unfragmentableLen = unfragmentableLen;
    return TRUE;
}

IP6Hdr* IP6Reassemble(IPInterface* interface, IP6Hdr* frag, IP6Frag* fragHdr, u32 flag)
{
    IP6Reassembled* free;
    IP6Reassembled* packet;
    IP6Hdr*         header;

    ASSERT(sizeof(IPHole) == 8);

    if (Control.buffer == NULL)
    {
        ++interface->ipv6Stat.reasmFails;
        return NULL;
    }

    // Lookup reassembly buffer associated with the fragment
    // by foreign and local addresses, protocol ID, and packet ID.
    free = NULL;
    for (packet = (IP6Reassembled*) Control.buffer;
         packet < (IP6Reassembled*) (Control.buffer + Control.len);
         packet = (IP6Reassembled*) ((u8*) packet + Control.size))
    {
        header = &packet->header;
        if (header->flow == 0)
        {
            if (free == NULL)
            {
                free = packet;
            }
            continue;
        }

        if (packet->frag.ident != fragHdr->ident ||
            !SO_IN6_ARE_ADDR_EQUAL(&header->src, &frag->src) ||
            !SO_IN6_ARE_ADDR_EQUAL(&header->dst, &frag->dst))
        {
            // frag is not a fragment of packet
            continue;
        }

        if (packet->interface != interface || packet->flag != flag)
        {
            // Something weird is going on. Just discard the fragmented packet.
            header->flow = 0;
            ++interface->ipv6Stat.reasmFails;
            return NULL;
        }

        // RFC 1858 XXX
        // if (frag->proto == IP_PROTO_TCP && IP_FRAG(frag) == 8)
        // {
        //    header->verlen = 0;
        //    return NULL;
        // }

        if (!SaveFirstFragment(packet, frag, fragHdr))
        {
            header->flow = 0;
            ++interface->ipv6Stat.reasmFails;
            return NULL;
        }

        header = Reassemble(packet, frag, fragHdr, Control.mtu);
        if (header)
        {
            return RestoreOriginalPacket(header, packet);
        }

        return header;
    }

    // RFC 1858 XXX
    // if (frag->proto == IP_PROTO_TCP && IP_FRAG(frag) == 8)
    // {
    //    header->verlen = 0;
    //    return NULL;
    // }

    if (free)
    {
        IPHole* hole;

        free->interface = interface;
        free->flag = flag;
        free->first.flow = 0;
        free->head = 0;
        free->unfragmentableLen = (s32) sizeof(IP6Hdr);

        header = &free->header;
        memmove(header, frag, sizeof(IP6Hdr));
        memmove(&free->frag, fragHdr, sizeof(IP6Frag));

        header->hops = 60;  // reassembly timeout within 60 seconds
        header->plen = 0;

        hole = (IPHole*) ((u8*) header + sizeof(IP6Hdr));
        hole->first = 0;
        hole->last  = (u16) (Control.mtu - sizeof(IP6Hdr));
        hole->next  = EOH;

        if (!SaveFirstFragment(free, frag, fragHdr))
        {
            header->flow = 0;
            ++interface->ipv6Stat.reasmFails;
            return NULL;
        }

        header = Reassemble(free, frag, fragHdr, Control.mtu);
        if (header /* && !IP6_MFRAG(fragHdr) && IP6_FRAG_OFFSET(fragHdr) == 0 */)
        {
            return RestoreOriginalPacket(header, free);
        }
    }
    else
    {
        ++interface->ipv6Stat.reasmFails;
    }
    return NULL;
}

/*---------------------------------------------------------------------------*
  Name:         SetLastNextHeader

  Description:  Sets next to the next header just befor len octets

  Arguments:    header  Pointer to IPv6 Header.
                len     length of unfragmentable part.
                next    header type to set

  Returns:      original next header type.
 *---------------------------------------------------------------------------*/
static u8 SetLastNextHeader(IP6Hdr* header, s32 len, u8 next)
{
    u8  prev;
    u8* hdr;

    hdr = GetNextHeaderBefore(header, len);
    ASSERT(hdr);
    prev = *hdr;
    *hdr = next;
    return prev;
}

static void SetFragmentHeader(IPInterface* interface, IP6Frag* fragHdr,
                              u8 next, s32 offset, BOOL mfrag)
{
    ASSERT(offset % 8 == 0);
    fragHdr->next = next;
    fragHdr->reserved = 0;
    fragHdr->offlg  = (u16) (offset & ~3);
    fragHdr->offlg |= mfrag ? 1 : 0;
    if (offset == 0)
    {
        ++interface->fragId;
    }
    fragHdr->ident = interface->fragId;
}

// voffset - offset in vec
static u8* VecMove(IFDatagram* datagram, int voffset, u8* ptr, int len)
{
    IFVec* vec;
    IFVec* end;
    int    offset = 0;
    int    gap;
    int    vlen;
    int    vend = voffset + len;

    for (vec = datagram->vec, end = &datagram->vec[datagram->nVec];
         0 < len && vec < end;
         ++vec)
    {
        if (voffset < offset + vec->len && offset < vend)
        {
            //           voffset  vend (= voffset + len)
            //           |        |
            //  XXXXXXXXX---------XXXXXXXXX
            //   |<-gap->|   |
            //   |           |
            //   offset      offset + vec->len
            //     ^
            //     |
            //   vec->data

            gap = voffset - offset;
            if (gap < 0)
            {
                gap = 0;
            }

            vlen = vend - offset;
            vlen = MIN(vlen, vec->len);
            vlen -= gap;
            len -= vlen;

            memmove(ptr, (u8*) vec->data + gap, (u32) vlen);
            ptr += vlen;
        }
        offset += vec->len;
    }
    return ptr;
}

static s32 GetUnfragmentablePartLen(IP6Hdr* ip6)
{
    u8*  hdr;
    u8   next;
    s32  len;

    len = sizeof(IP6Hdr);
    hdr = (u8*) ip6 + sizeof(IP6Hdr);
    next = ip6->next;

    while (next == SO_IPPROTO_HOPOPTS ||
           next == SO_IPPROTO_DSTOPTS ||
           next == SO_IPPROTO_ROUTING)
    {
        ASSERT(len < ip6->plen);
        len += (1 + hdr[1]) << 3;
        next = hdr[0];
        hdr += len;
    }

    return len;
}

int IP6Fragment(IFDatagram* datagram, u8* ptr, BOOL* discard)
{
    IPInterface* interface = datagram->interface;
    IP6Hdr*      org;
    IP6Hdr*      frag;
    IFVec*       vec;
    IFVec*       end;
    int          len;
    s32          unfragmentableLen;
    u8           originalNext;
    s32          mtu;
    BOOL         mfrag;

    *discard = TRUE;

    org = (IP6Hdr*) datagram->vec->data;
    ASSERT(datagram->type == ETH_IPv6);
    ASSERT(interface);

    mtu = datagram->mtu ? datagram->mtu : interface->linkMTU;
    if (org->plen + sizeof(IP6Hdr) <= mtu)
    {
        len = 0;
        for (vec = datagram->vec, end = &datagram->vec[datagram->nVec];
             vec < end;
             ++vec)
        {
            memmove(ptr, vec->data, (u32) vec->len);
            len += vec->len;
            ptr += vec->len;
        }
        return (s32) (org->plen + sizeof(IP6Hdr));
        // NOT REACHED HERE
    }

    // In response to an IPv6 packet that is sent to an IPv4 destination
    // (i.e., a packet that undergoes translation from IPv6 to IPv4), the
    // originating IPv6 node may receive an ICMP Packet Too Big message
    // reporting a Next-Hop MTU less than 1280.  [RFC 2460 5. Packet Size Issues]
    if (mtu < IP6_MIN_MTU)
    {
        mtu = IP6_MIN_MTU;
    }

    //
    // Fragmentation Procedure [RFC 2460]
    //
    ++interface->ipv6Stat.outFragCreates;

    frag = (IP6Hdr*) ptr;
    unfragmentableLen = GetUnfragmentablePartLen(org);

    // Copy the original internet header
    memmove(ptr, org, (u32) unfragmentableLen);
    originalNext = SetLastNextHeader((IP6Hdr*) ptr, unfragmentableLen, SO_IPPROTO_FRAGMENT);
    ptr += unfragmentableLen;

    // Attach len octets of data
    len = (mtu - unfragmentableLen - IP6_FRAG_HLEN) & ~7;
    len = MIN(len, (s32) sizeof(IP6Hdr) + org->plen - unfragmentableLen - datagram->offset);
    if (datagram->offset + len < org->plen)
    {
        mfrag = TRUE;
        *discard = FALSE;
    }
    else
    {
        ++interface->ipv6Stat.outFragOKs;
        mfrag = FALSE;
        *discard = TRUE;
    }
    SetFragmentHeader(interface, (IP6Frag*) ptr, originalNext, datagram->offset, mfrag);
    ptr += IP6_FRAG_HLEN;
    VecMove(datagram, datagram->offset + unfragmentableLen, ptr, len);

    // Fix plen
    frag->plen = (u16) (unfragmentableLen + IP6_FRAG_HLEN + len - sizeof(IP6Hdr));

    datagram->offset += len;

    return unfragmentableLen + IP6_FRAG_HLEN + len;
}
