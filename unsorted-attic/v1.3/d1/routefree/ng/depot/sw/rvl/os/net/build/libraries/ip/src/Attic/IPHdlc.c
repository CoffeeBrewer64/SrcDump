/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API -- PPP [RFC 1661]
  File:     IPHdlc.c

  Copyright 2004 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPHdlc.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    1     04/11/02 11:01 Ueno_kyu
    Added support for IPv6 Core Protocol.
    
    6     04/07/08 16:41 Ueno_kyu
    Revised  IPResetAccm() and IPSetAccm().
    
    5     04/07/02 17:41 Ueno_kyu
    Bug fixes.
    
    4     04/07/02 16:03 Ueno_kyu
    Added IPSetAccm() and IPResetAccm().
    Cleanup.
    
    3     04/07/02 13:36 Ueno_kyu
    Added support for ACCM negotiation.
    
    2     04/06/29 16:52 Ueno_kyu
    Fixed IPHdlcEncode().
    
    1     6/29/04 11:05 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#include <stddef.h>
#include <dolphin/os.h>
#include <dolphin/ip.h>
#include "IPPrivate.h"
#include "IPPPPConf.h"

//
// FCS lookup table from RFC 1549
//
const u16 IPFcsTable[256] =
{
   0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
   0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
   0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
   0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
   0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
   0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
   0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
   0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
   0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
   0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
   0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
   0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
   0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
   0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
   0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
   0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
   0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
   0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
   0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
   0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
   0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
   0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
   0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
   0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
   0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
   0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
   0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
   0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
   0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
   0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
   0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
   0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};

// Calculate a new fcs given the current fcs and the new data. [RFC 1549]
u16 IPFcs16(u16 fcs, const u8* cp, int len)
{
    ASSERT(0 < ((u16) -1));
    while (len--)
    {
        fcs = (u16) ((fcs >> 8) ^ IPFcsTable[(fcs ^ *cp++) & 0xff]);
    }
    return fcs;
}

void IPHdlcReset(IPHdlc* frame, u8* buf)
{
    frame->buf = frame->ppp = buf;
    frame->fcs = IP_FCS16_INIT;
    frame->escaped = FALSE;
}


static BOOL IsAsyncronousControlCharacter(u8 octet, u32 accm)
{
    if (octet < 0x20)
    {
        if (accm & (u32) (1 << octet))
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         IPHdlcDecode

  Description:  Restores escaped data and writes the restored data to frame->ppp.

  Arguments:    frame   Pointer to initialized IPHdlc structure.
                octet   Pointer to escaped data.

  Returns:      IP_HDLC_CONT, if the restoration is continued.
                IP_HDLC_ERROR, if CRC is not correct.
                The number of bytes resotred, if one packet is successfully
                restored.
 *---------------------------------------------------------------------------*/
int IPHdlcDecode(IPHdlc* frame, u8 octet)
{
    if (IsAsyncronousControlCharacter(octet, frame->recvAccm))
    {
        return IP_HDLC_CONT;
    }
    else if (frame->escaped)
    {
        frame->escaped = FALSE;
        if (octet == 0x7e)
        {
            return IP_HDLC_DROP;
        }
        octet ^= 0x20;
    }
    else if (octet == 0x7e)     // Flag sequence?
    {
        if (frame->fcs == IP_FCS16_GOOD)
        {
            return (s32) (frame->ppp - frame->buf) - 2; // excluding CRC
        }
        else if (frame->ppp == frame->buf)
        {
            return IP_HDLC_CONT;
        }
        else
        {
            return IP_HDLC_ERROR;
        }
    }
    else if (octet == 0x7d)
    {
        frame->escaped = TRUE;
        return IP_HDLC_CONT;
    }

    if (frame->buf + IP_IF_RECVBUFSIZE < frame->ppp)
    {
        return IP_HDLC_ERROR;
    }
    *frame->ppp++ = octet;
    frame->fcs = (u16) ((frame->fcs >> 8) ^ IPFcsTable[(frame->fcs ^ octet) & 0xff]);
    return IP_HDLC_CONT;
}

int IPHdlcEncode(IPHdlc* frame, const u8* src, s32 len, u8* dst)
{
    u8  octet;
    u16 fcs = IP_FCS16_INIT;
    u8* buf = dst;

    *dst++ = 0x7e;

    while (0 < len--)
    {
        octet = *src++;
        fcs = (u16) ((fcs >> 8) ^ IPFcsTable[(fcs ^ octet) & 0xff]);
        if (IsAsyncronousControlCharacter(octet, frame->sendAccm) ||
            octet == 0x7D || octet == 0x7E)
        {
            *dst++ = 0x7d;
            octet ^= 0x20;
        }
        *dst++ = (u8) octet;
    }

    fcs ^= 0xffff;
    octet = (u8) fcs;

    if (IsAsyncronousControlCharacter(octet, frame->sendAccm) ||
        octet == 0x7D || octet == 0x7E)
    {
        *dst++ = 0x7d;
        octet ^= 0x20;
    }
    *dst++ = (u8) octet;

    octet = (u8) (fcs >> 8);
    if (IsAsyncronousControlCharacter(octet, frame->sendAccm) ||
        octet == 0x7D || octet == 0x7E)
    {
        *dst++ = 0x7d;
        octet ^= 0x20;
    }
    *dst++ = (u8) octet;

    *dst++ = 0x7e;

    return dst - buf;
}

void IPSetAccm(IPHdlc* frame, u32 srcAccm, u8 flag)
{
    switch (flag)
    {
      case IP_HDLC_ACCM_SEND:
        frame->sendAccm = srcAccm;
#ifdef VERBOSE
        OSReport("Set SEND ACCM 0x%08x\n", frame->sendAccm);
#endif
        break;

      case IP_HDLC_ACCM_RECV:
        frame->recvAccm = srcAccm;
#ifdef VERBOSE
        OSReport("Set RECV ACCM 0x%08x\n", frame->recvAccm);
#endif
        break;

      default:
        // should not be reached here.
        break;
    }
}

void IPResetAccm(IPHdlc* frame, u8 flag)
{
    switch (flag)
    {
      case IP_HDLC_ACCM_SEND:
        frame->sendAccm = PPP_ACCM_DEFAULT;
#ifdef VERBOSE
        OSReport("=== Reset SEND ACCM (0x%08x) ===\n", frame->sendAccm);
#endif
        break;

      case IP_HDLC_ACCM_RECV:
        frame->recvAccm = PPP_ACCM_DEFAULT;
#ifdef VERBOSE
        OSReport("=== Reset RECV ACCM (0x%08x) ===\n", frame->recvAccm);
#endif
        break;

      default:
        // should not be reached here.
        break;
    }
}
