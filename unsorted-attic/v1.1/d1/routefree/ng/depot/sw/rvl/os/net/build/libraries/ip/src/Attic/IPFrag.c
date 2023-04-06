d1 672
a672 663
/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPFrag.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: /Dolphin/build/libraries/ip6/src/IPFrag.c $
    
    12    2/20/06 18:50 Shiki
    Added IPGetReassembleMaxSize().

    11    2/14/06 18:47 Shiki
    Revised to collect interface statistics.

    10    11/04/03 15:33 Shiki
    Fixed IPReassemble() to clear the IP_DF bit in a reassembled datagram.

    9     10/29/03 22:02 Shiki
    Added support for fragmenting outgoing datagrams.

    8     9/29/03 17:52 Shiki
    Modified IPSetReassemblyBuffer() to release the reassembly buffer when
    NULL buffer pointer is specified.

    7     8/05/03 10:31 Shiki
    Fixed the problem that IP fragments with IP header option collapse the
    stack.

    6     8/05/02 9:26 Shiki
    Modified IPSetReassemblyBuffer() to auto-adjust MTU size.

    5     4/30/02 14:50 Shiki
    Minor clean up.

    4     4/24/02 11:25 Shiki
    Clean up.

    2     4/04/02 17:24 Shiki
    Just completed unimplemented routines.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $

   STD 5, RFC 791 states:

      Every internet module must be able to forward a datagram of 68
      octets without further fragmentation.  This is because an internet
      header may be up to 60 octets, and the minimum fragment is 8
      octets.

    RFC 1858
         IF FO=1 and PROTOCOL=TCP then
                 DROP PACKET

 *---------------------------------------------------------------------------*/

#include <dolphin/os.h>
#include <dolphin/ip.h>
#include "IPPrivate.h"

//
// IP Datagram Reassembly [RFC 791, RFC 815, RFC 1858]
//

//
// [ IP_MAX_HLEN ] [ data (mtu - IP_MIN_HLEN) ] [ IP_MAX_HLEN + 8 ] [ interface ] [ flag ]
//

#define HOLE_LEN    8   // Minimum size of a hole is eight bytes
#define EOH         1   // end-of-hole mark (EOH % HOLE_LEN != 0)
#define SPACE       ((s32) (sizeof(IPReassembled) - IP_MIN_HLEN))

// Fragment hole descriptor
typedef struct IPHole
{
    u16 first;
    u16 last;
    u16 next;
    u16 _unused;
} IPHole;

// Partially reassembled datagram
typedef struct IPReassembled
{
    IPInterface* interface;
    u32          flag;

    // The first fragment header needs to be saved for inclusion in a
    // possible ICMP Time Exceeded (Reassembly Timeout) message. [RFC 1122]
    IPHeader     first;
    u8           option[IP_MAX_HLEN - IP_MIN_HLEN];
    u8           data[8];

    // Partially reassembled datagram followed by data (total Control.mtu byte)
    IPHeader     header;
} IPReassembled;

#define INITIALIZED 0x01

// Reassemble buffer control
typedef struct IPReassembleControl
{
    u32     flag;
    u8*     buffer;
    s32     len;        // size of buffer
    s32     mtu;
    s32     size;       // size of each IPReassembled chunk
    OSAlarm alarm;
} IPReassembleControl;

static IPReassembleControl Control;

static void TimeoutHandler(OSAlarm* alarm, OSContext* context)
{
    #pragma unused( alarm, context )
    IPReassembled* packet;
    IPHeader*      header;
    IPHeader*      first;

    if (Control.buffer == NULL)
    {
        return;
    }

    for (packet = (IPReassembled*) Control.buffer;
         packet < (IPReassembled*) (Control.buffer + Control.len);
         packet = (IPReassembled*) ((u8*) packet + Control.size))
    {
        header = &packet->header;

        // Time-to-live check (60 sec)
        if (header->verlen != 0)
        {
            if (header->ttl <= 1)
            {
                // Expired. The partially-reassembled datagram MUST be discarded.
                ASSERT(packet->interface);
                ++packet->interface->ipStat.reasmTimeout;
                ++packet->interface->ipStat.reasmFails;

                header->verlen = 0;

                // Send ICMP time exceeded on reassembly timeout [RFC 1122 MUST]
                first = &packet->first;
                if (first->verlen != 0) // Is the first fragment saved?
                {
                    ICMPTimeExceeded te;

                    te.type   = ICMP_TIME_EXCEEDED;
                    te.code   = 1;  // fragment timeout
                    te.unused = 0;

                    ICMPSendError((ICMPHeader*) &te, packet->interface, first, packet->flag);
                }
            }
            else
            {
                --header->ttl;
            }
        }
    }
}

s32 IPSetReassemblyBuffer(void* buffer, s32 len, s32 mtu)
{
    BOOL enabled;
    s32  size;      // size of IPReassembled block

    mtu = MAX(mtu, 576);
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
static IPHeader* Reassemble(IPHeader* packet, IPHeader* frag, s32 mtu)
{
    IPHole* hole;
    IPHole* newHole;
    s32     first;
    s32     last;
    u16*    next;
    s32     len;
    s32     offset;
    s32     packetLen;

    u16     holeFirst;
    u16     holeLast;

    ASSERT(packet->id == frag->id &&
           packet->proto == frag->proto &&
           IP_ADDR_EQ(packet->src, frag->src) &&
           IP_ADDR_EQ(packet->dst, frag->dst));
    ASSERT((frag->frag & IP_MF) || IP_FRAG(frag) != 0);
    ASSERT(packet->verlen != 0);

    first = IP_FRAG(frag);
    len   = frag->len - IP_HLEN(frag);
    last  = first + len - 1;

    // Update packet->len
    packetLen = IP_HLEN(packet) + last + 1;
    if (mtu < packetLen || len <= 0 ||
        ((frag->frag & IP_MF) && len % 8 != 0))
    {
        packet->verlen = 0;
        return NULL;
    }
    packet->len = (u16) MAX(packet->len, packetLen);

    next = &packet->sum;  // sum field has the head of the list
    while (*next != EOH)
    {
        hole = (IPHole*) ((u8*) packet + IP_HLEN(packet) + *next);

        if (hole->last < first || last < hole->first)
        {
            next = &hole->next;
            continue;
        }

        holeFirst = hole->first;
        holeLast  = hole->last;
        *next = hole->next; // Delete current hole

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
            if (frag->frag & IP_MF)
            {
                newHole = (IPHole*) ((u8*) packet + IP_HLEN(packet) + last + 1);
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
        else // if (holeLast <= last)
        {
            last = holeLast;
        }

        ASSERT(0 <= last - (first + offset) + 1);   // Teardrop check
        memmove((u8*) packet + IP_HLEN(packet) + first + offset,
                (u8*) frag + IP_HLEN(frag) + offset,
                (u32) (last - (first + offset) + 1));
    }

    if (packet->sum == EOH)
    {
        return packet;
    }
    else
    {
        return NULL;
    }
}

// Saves the first fragment header for a possible ICMP time exceeded message
// Returns FALSE if frag appears to be too large or forged.
// Be careful. frag might have been retransmitted
static BOOL SaveFirstFragment(IPReassembled* packet, IPHeader* frag)
{
    IPHeader* header;
    s32       optlen;

    if (IP_FRAG(frag) != 0)
    {
        return TRUE;
    }
    if (frag->len < IP_HLEN(frag) + 8)
    {
        return FALSE;
    }
    if (packet->first.verlen != 0)
    {
        return (IP_HLEN(frag) == IP_HLEN(&packet->first)) ? TRUE : FALSE;
    }

    memmove(&packet->first, frag, (u32) (IP_HLEN(frag) + 8));

    header = &packet->header;
    if (IP_HLEN(header) == IP_HLEN(frag))
    {
        return TRUE;
    }

    // Make sure the datagram does not become too large (over 65535 byte)
    ASSERT(IP_HLEN(header) == IP_MIN_HLEN);
    optlen = IP_HLEN(frag) - IP_MIN_HLEN;
    ASSERT(0 < optlen);
    if (Control.mtu < header->len + optlen)
    {
        // Fragment is too large or could be forged.
        return FALSE;
    }

    // Insert the IP header options to the partially reassembled datagram
    memmove((u8*) header + IP_HLEN(frag), (u8*) header + IP_MIN_HLEN,
            (u32) (header->len - IP_MIN_HLEN + HOLE_LEN));
    memmove((u8*) header + IP_MIN_HLEN, (u8*) frag + IP_MIN_HLEN,
            (u32) optlen);
    header->verlen = frag->verlen;
    header->len += optlen;
    return TRUE;
}

IPHeader* IPReassemble(IPInterface* interface, IPHeader* frag, u32 flag)
{
    IPReassembled* free;
    IPReassembled* packet;
    IPHeader*      header;

    ASSERT(sizeof(IPHole) == 8);

    if (Control.buffer == NULL)
    {
        ++interface->ipStat.reasmFails;
        return NULL;
    }

    // Lookup reassembly buffer associated with the fragment
    // by foreign and local addresses, protocol ID, and packet ID.
    free = NULL;
    for (packet = (IPReassembled*) Control.buffer;
         packet < (IPReassembled*) (Control.buffer + Control.len);
         packet = (IPReassembled*) ((u8*) packet + Control.size))
    {
        header = &packet->header;
        if (header->verlen == 0)
        {
            if (free == NULL)
            {
                free = packet;
            }
            continue;
        }

        if (header->id != frag->id ||
            header->proto != frag->proto ||
            IP_ADDR_NE(header->src, frag->src) ||
            IP_ADDR_NE(header->dst, frag->dst))
        {
            // frag is not a fragment of packet
            continue;
        }

        if (packet->interface != interface || packet->flag != flag)
        {
            // Something weird is going on. Just discard the fragmented packet.
            header->verlen = 0;
            ++interface->ipStat.reasmFails;
            return NULL;
        }

        // RFC 1858
        if (frag->proto == IP_PROTO_TCP && IP_FRAG(frag) == 8)
        {
            header->verlen = 0;
            ++interface->ipStat.reasmFails;
            return NULL;
        }

        if (!SaveFirstFragment(packet, frag))
        {
            header->verlen = 0;
            ++interface->ipStat.reasmFails;
            return NULL;
        }
        header = Reassemble(header, frag, Control.mtu);
        if (header)
        {
            // Restore the original first IP header
            header->frag &= ~(IP_DF | IP_MF | IP_FO);
            header->tos = packet->first.tos;
            header->ttl = packet->first.ttl;
            header->sum = 0;
            header->sum = IPCheckSum(header);
        }

        return header;
    }

    // RFC 1858
    if (frag->proto == IP_PROTO_TCP && IP_FRAG(frag) == 8)
    {
        ++interface->ipStat.reasmFails;
        return NULL;
    }

    if (free)
    {
        IPHole* hole;

        free->interface = interface;
        free->flag = flag;
        free->first.verlen = 0;

        header = &free->header;
        memmove(header, frag, IP_MIN_HLEN);
        header->verlen = IP_VERHLEN;
        header->ttl = 60; // The reassembly timeout value SHOULD be a fixed value [RFC 1122]
        header->sum = 0;  // sum field has the head of the list
        header->len = IP_MIN_HLEN;

        hole = (IPHole*) ((u8*) header + IP_HLEN(header));
        hole->first = 0;
        hole->last  = (u16) (Control.mtu - IP_HLEN(header));
        hole->next  = EOH;

        if (!SaveFirstFragment(free, frag))
        {
            header->verlen = 0;
            ++interface->ipStat.reasmFails;
            return NULL;
        }
        Reassemble(header, frag, Control.mtu);
    }
    else
    {
        ++interface->ipStat.reasmFails;
    }

    return NULL;
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

int IPFragment(IFDatagram* datagram, u8* ptr, BOOL* discard)
{
    IPInterface* interface = datagram->interface;
    IPHeader*    org;
    IPHeader*    frag;
    IFVec*       vec;
    IFVec*       end;
    int          len;
    int          hlen;

    *discard = TRUE;

    org = (IPHeader*) datagram->vec->data;
    ASSERT(datagram->type == ETH_IP || datagram->type == ETH_PPPoE_SESSION);
    ASSERT(IPCheckSum(org) == 0);
    ASSERT(interface);

    if (org->len <= interface->mtu)
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
        return org->len;
        // NOT REACHED HERE
    }

    //
    // Fragmentation Procedure [RFC 791]
    //
    ASSERT((org->frag & IP_DF) == 0);
    *discard = FALSE;

    ++interface->ipStat.fragCreates;
    frag = (IPHeader*) ptr;
    if (datagram->offset == 0)
    {
        hlen = IP_HLEN(org);

        // Copy the original internet header
        memmove(ptr, org, (u32) hlen);
        ptr += hlen;

        // Attach the first NFB*8 data octets
        len = (interface->mtu - hlen) & ~7;
        VecMove(datagram, datagram->offset + hlen, ptr, len);

        // Correct the header:
        //   MF <- 1;  TL <- (IHL*4)+(NFB*8);
        frag->verlen = (u8) ((IP_VER << 4) | (hlen >> 2));
        frag->len = (u16) (hlen + len);
        frag->frag = IP_MF;
    }
    else
    {
        // Selectively copy the internet header (some options
        // are not copied, see option definitions);
        u8* opt;
        int optlen;
        int i;

        memmove(ptr, org, (u32) IP_MIN_HLEN);
        ptr += IP_MIN_HLEN;

        optlen = IP_HLEN(org) - IP_MIN_HLEN;
        ASSERT(0 <= optlen);

        opt = (u8*) org + IP_MIN_HLEN;
        for (i = 0;
             i < optlen && opt[i] != IP_OPT_EOOL;
             i += len)
        {
            switch (opt[i])
            {
              case IP_OPT_EOOL:
              case IP_OPT_NOP:
                len = 1;
                break;
              default:
                len = opt[i + 1];
                break;
            }
            if (opt[i] & 0x80)  // Copied flag?
            {
                memmove(ptr, opt, (u32) len);
                ptr += len;
            }
        }
        hlen = (u8*) ptr - (u8*) frag;
        while (hlen % 4)
        {
            *ptr++ = IP_OPT_EOOL;
            ++hlen;
        }

        // Append the remaining data;
        len = (interface->mtu - hlen) & ~7;
        len = MIN(len, org->len - IP_HLEN(org) - datagram->offset);
        VecMove(datagram, datagram->offset + IP_HLEN(org), ptr, len);

        // Correct the header:
        // IHL <- (((OIHL*4)-(length of options not copied))+3)/4;
        // TL <- OTL - NFB*8 - (OIHL-IHL)*4);
        // FO <- OFO + NFB;  MF <- OMF;
        frag->verlen = (u8) ((IP_VER << 4) | (hlen >> 2));
        frag->len = (u16) (hlen + len);
        frag->frag = (u16) (datagram->offset >> 3);
        if (IP_HLEN(org) + datagram->offset + len < org->len)
        {
            frag->frag |= IP_MF;
        }
        else
        {
            ++interface->ipStat.fragOKs;
            *discard = TRUE;
        }
    }

    // Recompute Checksum
    frag->sum = 0;
    frag->sum = IPCheckSum(frag);

    datagram->offset += len;

    return hlen + len;
}

s32 IPGetReassembleMaxSize(void)
{
    return (Control.buffer == NULL) ? 576 : Control.mtu;
}
