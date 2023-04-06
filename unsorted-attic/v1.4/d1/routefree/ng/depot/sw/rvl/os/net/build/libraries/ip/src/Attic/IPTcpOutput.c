/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPTcpOutput.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPTcpOutput.c,v $
  Revision 1.3  2006/04/11 01:40:35  mxu
  update to Nintendo's April 05 release

  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    48    4/03/06 19:21 Shiki
    Modified IP6GetPathMTU() not to increase PMTU less than 1 min after the
    previous attempted increase.

    47    3/20/06 18:05 Shiki
    Fixed TCPCalcSendSize() not to send data only segment until connection
    is established.

    46    2/15/06 9:13 Shiki
    Fixed TCPOutput().

    45    2/14/06 18:47 Shiki
    Revised to collect interface statistics.

    44    2/08/06 10:53 Shiki
    Added support for SO_TCP_STDURG.
    Fixed DoSwsAvoidance() to avoid SWS even if URG bit is set.

    43    2/07/06 13:07 Shiki
    Fixed TCPOutput().

    42    2/06/06 15:08 Shiki
    Modified TCPOutput() to keep the current next-hop in IPInfo.

    41    2/03/06 16:34 Shiki
    Fixed TCPOutput() not to set sendMax out of window.

    40    2/03/06 9:43 Shiki
    Fixed TCPOutput() for making ip.a.

    39    2/02/06 15:58 Shiki
    Fixed DoSwsAvoidance() not to perform delayed ACK if recvWin is less
    than effSendMss to avoid remote sender's SWS.

    38    2/02/06 15:33 Shiki
    Modified delayed ACK implementation.

    37    2/01/06 16:24 Shiki
    Added full support of IPv6 PMTU discovery.
    Fixed DoSwsAvoidance() to send a window update correctly.

    36    12/20/05 10:40 Shiki
    Revised the transition from SYN_RECEIVED to FINWAIT1.

    35    12/09/05 15:50 Shiki
    Fixed TCPOutput() following RFC 3390.

    34    12/09/05 15:19 Shiki
    Implemented the limited transmit algorithm (RFC 3042).

    33    12/08/05 21:46 Shiki
    Implemented RFC 3517.

    32    12/08/05 20:25 Shiki
    Revised to test fast recovery mode by counting dupAcks.

    31    12/08/05 17:56 Shiki
    Fixed the fast recovery procedure.

    30    12/08/05 13:09 Shiki
    Updated a comment about persist timer.

    29    12/07/05 22:00 Shiki
    Implemented RFC 3782 (The NewReno Modification to TCP's Fast Recovery
    Algorithm).

    28    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    32    04/10/21 16:59 Ueno_kyu
    Enclosed IPv6 specific codes in #ifdef IP_INET6... #endif blocks.

    31    6/14/04 11:32 Shiki
    Added two more assertions to TCPOutput().

    30    6/14/04 10:19 Shiki
    Revised __TCPCalcSendSize().

    29    6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    27    3/03/04 14:28 Shiki
    Modified to use a TCP initial cwnd of 2 segments as allowed in RFC
    2581.

    26    3/03/04 9:28 Shiki
    Fixed not to send window update ACK in TCP_STATE_SYN_SENT and
    TCP_STATE_SYN_RECEIVED state.

    25    3/01/04 11:15 Shiki
    Revised DoSwsAvoidance() to send a window update every time it receives
    2*RMSS bytes [RFC 2581].

    24    2/25/04 14:51 Shiki
    Added support for delayed ACK.

    23    12/02/03 13:22 Shiki
    Fixed __TCPCalcSendSize() to use IFInitDatagram().

    22    10/29/03 21:59 Shiki
    Revised using IFInitDatagram().

    21    8/25/03 9:31 Shiki
    Fixed TCPMakeOption() to align SACK edges to 4 byte boundaries.

    20    8/21/03 20:58 Shiki
    Added support for SACK/FACK.

    19    8/04/03 9:07 Shiki
    Modified to goes back to slow start after TCP phase change. See
    "Congestion Avoidance and Control," V. Jacobson, ACM SIGCOMM-88, August
    1988.

    18    7/29/03 18:23 Shiki
    Fixed TCPOutput() not to blindly set retransmission timer while
    sendBusy.

    17    5/15/03 15:54 Shiki
    Modified to clear the IF_DATAGRAM_FLAG_DROP bit in IFDatagram.flag
    before sending a Ethernet packet.

    16    5/13/03 12:50 Shiki
    Clean up.

    15    8/05/02 11:04 Shiki
    Minor fix.

    14    7/18/02 10:18 Shiki
    Added supoprt for TCPStat.

    13    7/17/02 18:26 Shiki
    Added __TCPOutputs.

    12    7/10/02 17:13 Shiki
    Modified TCPCalcSendSize() to set TCP_SO_PERSIST flag if TCPInfo enters
    in persist state.

    11    4/24/02 11:19 Shiki
    Fixed TCPOutputCallback() to use callback result code as a hit.

    10    4/15/02 12:53 Shiki
    Revised for better interoperability around the SYN segment handling.

    9     4/10/02 18:35 Shiki
    Revised IFRingGet() interface.

    8     4/09/02 19:57 Shiki
    Revised assertions.

    7     4/08/02 16:46 Shiki
    Fixed TCP flag bug against the bogus flag probe.

    6     4/02/02 13:23 Shiki
    Added support for half-close and urgent mode.

    5     3/18/02 14:35 Shiki
    Fixed a TCPOutput() bug that prevents sending a new TCP segment after
    IPOut() failure. Also fixed the ACK response code to sync with IPTcp.c.

    4     3/14/02 16:07 Shiki
    Renamed TCPInfo.template to TCPInfo.header.

    3     3/13/02 18:30 Shiki
    Revised TCPSend() so it can directly transfer user data from the user
    space to the link layer.

    2     3/12/02 12:48 Shiki
    Fixed persist state management code bugs.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifdef IOP_OS
#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <stddef.h>
#else
#include <stddef.h>
#include <string.h>
#endif // IOP_OS

#include <dolphin/os.h>
#include <dolphin/socket.h>
#include "IPPrivate.h"
#ifdef IP_INET6
#include "IP6Private.h"
#endif // IP_INET6

// Returns TCPSackHole for the oldest pending retransmission.
TCPSackHole* TCPSackOutput(const TCPObj* info)
{
    const TCPSackHole* hole;
    const TCPSackHole* holeEnd;

    ASSERT(TCP_RXMIT_THRESH <= info->dupAcks);
    holeEnd = &info->scoreboard[info->sendHoles];
    for (hole = info->scoreboard; hole < holeEnd; ++hole)
    {
        if (TCP_SEQ_GT(hole->rxmit, hole->end) &&
            ((info->flag & TCP_SO_FAST_RXMIT) || TCP_RXMIT_THRESH <= hole->dupAcks))
        {
            if (TCP_SEQ_GT(hole->rxmit, info->sendUna))    // Stale SACK hole
            {
                continue;
            }
            return (TCPSackHole*) hole;
        }
    }
    return NULL;
}

int TCPMakeOption(TCPHeader* tcp, TCPObj* info, u16 flag)
{
    int optlen;
    int padding;
    u8* opt;

    if (info == NULL)
    {
        tcp->flag &= ~TCP_FLAG_DATAOFFSET;
        tcp->flag |= TCP_MIN_HLEN << 10;
        return 0;
    }

    opt = (u8*) tcp + TCP_MIN_HLEN;
    if (flag & TCP_FLAG_SYN)
    {
        *opt++ = TCP_OPT_MSS;
        *opt++ = 4;
        *((u16*) opt) = (u16) info->mss;
        opt += 2;

#ifdef TCP_SACK
        *opt++ = TCP_OPT_SACKP;
        *opt++ = 2;
#endif // TCP_SACK
    }

#ifdef TCP_SACK
    // Include SACK options if necessary
    if ((info->flag & TCP_SO_SACK) && info->asb[0].ptr != NULL)
    {
        IFBlock* block;
        s32*     edge;

        ASSERT(TCP_MIN_HLEN % 4 == 0);
        while ((opt - (u8*) tcp) % 4 != 2)
        {
            *opt++ = TCP_OPT_NOP;
        }
        opt[0] = TCP_OPT_SACK;
        edge = (s32*) &opt[2];
        for (block = &info->asb[TCP_ASB - 1]; info->asb <= block; --block)
        {
            if (block->ptr == NULL)
            {
                continue;
            }
            // Left edge
            if (info->recvPtr <= block->ptr)
            {
                edge[0] = block->ptr - info->recvPtr;   // XXX SYN case
            }
            else
            {
                edge[0] = block->ptr + info->recvBuff - info->recvPtr;
            }
            edge[0] += info->recvNext - info->recvUser;
            // Right edge
            edge[1] = edge[0] + block->len;
            edge[0] = (s32) (SOHtoNl(edge[0]));
            edge[1] = (s32) (SOHtoNl(edge[1]));
            edge += 2;
        }
        ASSERT((u8*) edge - opt <= 4 * 2 * sizeof(s32) + 2);
        opt[1] = (u8) ((u8*) edge - opt);
        opt = (u8*) edge;
    }
#endif // TCP_SACK

    optlen = opt - ((u8*) tcp + TCP_MIN_HLEN);
    if (optlen % 4 != 0)
    {
        padding = 4 - (optlen % 4);
        *opt++ = TCP_OPT_EOL;
        memset(opt, TCP_OPT_NOP, (size_t) (padding - 1));
        optlen += padding;
    }
    ASSERT(optlen % 4 == 0);
    ASSERT(TCP_MIN_HLEN + optlen <= TCP_MAX_HLEN);

    tcp->flag &= ~TCP_FLAG_DATAOFFSET;
    tcp->flag |= (TCP_MIN_HLEN + optlen) << 10;

    return optlen;
}

// Calc send size in sequence count
static s32 TCPCalcSendSize(TCPObj* info, s32 effSendMss, u16* pflag, s32* poffset,
                           TCPSackHole* hole)
{
    u16 flag = *pflag;
    s32 win;
    s32 useable;
    s32 offset;
    s32 dataLen;
    s32 end;
    s32 sendSize;

    ASSERT(0 <= info->sendLen);

Redo:
    // Calc the current offset in the send buffer
    dataLen = 0;
    switch (info->state)
    {
      case TCP_STATE_SYN_SENT:
      case TCP_STATE_SYN_RECEIVED:
        if (info->iss == info->sendNext)
        {
            ASSERT(info->iss == info->sendUna);
            flag |= TCP_FLAG_SYN;
            dataLen = 1;
        }
        else if (info->sendUna == info->iss)
        {
            offset = info->sendNext - info->sendUna - 1;  // -1 for SYN
            break;
        }
        // FALL THROUGH
      default:
        offset = info->sendNext - info->sendUna;
        break;
    }

    // Calc the total seqence count, including SYN and FIN, to send
    dataLen += info->sendLen;
    if (info->sendCallback && 0 < info->userSendLen)
    {
        dataLen += info->userSendLen;
    }
    end = info->sendUna + dataLen;
    dataLen -= offset;
#ifdef TCP_SACK
    // (SACK-2) Adjust dataLen
    if (hole)
    {
        ASSERT(hole->rxmit == info->sendNext);
        dataLen = MIN(dataLen, hole->end - hole->rxmit);
    }
#endif  // TCP_SACK

    switch (info->state)
    {
      case TCP_STATE_SYN_SENT:
      case TCP_STATE_SYN_RECEIVED:
        if (!info->closeCallback && !(info->flag & TCP_SO_SH_SEND))
        {
            break;
        }
        // TCPClose(info) or TCPShutdown(info, TCP_SHUTDOWN_SEND) has
        // been called. Technically, we are now in TCP_STATE_FINWAIT1.
        // FALL THROUGH
      case TCP_STATE_FINWAIT1:
      case TCP_STATE_LAST_ACK:
      case TCP_STATE_CLOSING:   // In case FIN was lost, we still have to send FIN.
        // If dataLen is negative, FIN has been sent and
        // the retransmission timer has not expired yet.
        if (0 <= dataLen && hole == NULL)
        {
            flag |= TCP_FLAG_FIN;
            ++dataLen;
            ++end;
        }
        break;
    }

    // To prevent interoperability problems,
    // we do not send data and/or FIN on SYN segments
    if (flag & TCP_FLAG_SYN)
    {
        flag &= ~TCP_FLAG_FIN;
        offset = 0;
        dataLen = 1;
        end = info->sendUna + dataLen;
    }

    // Do not send data only segment until connection is established.
    switch (info->state)
    {
      case TCP_STATE_SYN_SENT:
      case TCP_STATE_SYN_RECEIVED:
        if (!(flag & TCP_FLAG_SYN))
        {
            *pflag &= ~(TCP_FLAG_FIN | TCP_FLAG_SYN | TCP_FLAG_PSH);
            return 0;
        }
        break;
    }

    // Calc window size
    win = MIN(info->sendWin, info->cWin);
    if (TCP_RXMIT_THRESH <= info->dupAcks)
    {
#ifdef TCP_SACK
        //
        // (SACK-1) During SACK loss recovery period, cWin is checked later.
        //
        if (info->flag & TCP_SO_SACK)
        {
            win = info->sendWin;
        }
#endif  // TCP_SACK
    }
#ifdef TCP_LIMITED_TRANSMIT
    if (TCP_LIMITED_THRESH == info->dupAcks)
    {
        // the sender can only send two segments beyond the congestion window
        // (cwnd). [RFC 3042]
        win = info->sendWin;
    }
#endif  // TCP_LIMITED_TRANSMIT

    // If the window size is zero and the persist timer has been expired,
    // send a window probe.
    if (win == 0 && TCP_SEQ_GT(info->sendUna, end) &&
        info->rxmitAlarm.handler == NULL)
    {
        if (info->sendNext != info->sendUna)
        {
            info->sendNext = info->sendUna;

            // Cancel RTT estimators. [Karn's algorithm]
            info->rttTiming = FALSE;

            // RFC 3782
            info->sendRecover = info->sendMax;
            info->dupAcks = 0;  // Exit the fast recovery

            hole = NULL;
            info->sendHoles = 0;
            info->sendFack = info->sendUna;
            info->rxmitData = 0;
            info->sendAwin = 0;

            goto Redo;
        }
        flag |= TCP_FLAG_ACK;   // persist timer SWS override
        info->flag |= TCP_SO_PERSIST;
        win = 1;
    }

    // Calc useable size
    useable = info->sendUna + win - info->sendNext;

#ifdef VERBOSE
    OSReport("win %d, dataLen %d, offset %d, useable %d\n",
             win, dataLen, offset, useable);
#endif

#ifdef TCP_SACK
    if (info->flag & TCP_SO_SACK)
    {
        //
        // (SACK-3) If cwnd - pipe >= 1 SMSS the sender SHOULD transmit one or more
        //          segments [RFC 3517]
        //
        if (TCP_RXMIT_THRESH <= info->dupAcks &&
            !(info->flag & TCP_SO_FAST_RXMIT))
        {
            if (info->cWin - info->sendAwin < info->mss)
            {
                useable = 0;
            }
        }
    }
#endif  // TCP_SACK

#ifdef TCP_LIMITED_TRANSMIT
    if (TCP_LIMITED_THRESH == info->dupAcks)
    {
        // The amount of outstanding data would remain less than or equal
        // to the congestion window plus 2 segments. [RFC 3042]
        useable = MIN(useable, MAX(0, info->cWin + 2 * info->mss - info->sendAwin));
    }
#endif  // TCP_LIMITED_TRANSMIT

    // Calc send size
    sendSize = MIN(effSendMss, MIN(dataLen, useable));
    if (sendSize == dataLen && hole == NULL)
    {
        if (0 < sendSize &&
            (flag & (TCP_FLAG_SYN | TCP_FLAG_RST | TCP_FLAG_FIN)) == 0)
        {
            // Set PSH flag if no more data to send
            flag |= TCP_FLAG_PSH;
        }
    }
    if ((flag & TCP_FLAG_FIN) &&
        TCP_SEQ_GT(info->sendNext + sendSize, end))
    {
        // We have more data to send.
        flag &= ~TCP_FLAG_FIN;
        --dataLen;
    }
    if (sendSize <= 0)
    {
        *pflag &= ~(TCP_FLAG_FIN | TCP_FLAG_SYN | TCP_FLAG_PSH);
        return 0;
    }

    *pflag = flag;
    *poffset = offset;
    return sendSize;
}

static s32 TCPPrepareData(TCPObj* info, IFDatagram* datagram,
                          s32 sendSize, s32 offset, u16 flag)
{
    s32 dataLen;
    s32 len;

    // Prepare data portion (without SYN and FIN)
    dataLen = sendSize;
    if (flag & TCP_FLAG_SYN)
    {
        --dataLen;
        ASSERT(offset == 0);
    }
    if (flag & TCP_FLAG_FIN)
    {
        --dataLen;
    }
    if (0 < dataLen)
    {
        if (0 < info->sendLen && offset < info->sendLen)
        {
            len = info->sendLen - offset;
            len = MIN(len, dataLen);
            datagram->nVec += IFRingGet(info->sendData, info->sendBuff,
                                        info->sendPtr + offset,
                                        info->sendLen - offset,
                                        &datagram->vec[1], len);
            dataLen -= len;
            offset  += len;
        }
        if (0 < dataLen)
        {
            // Use user buffer as send buffer
            ASSERT(info->sendCallback && 0 < info->userSendLen);
            offset -= info->sendLen;
            ASSERT(offset + dataLen <= info->userSendLen);
            datagram->vec[datagram->nVec].data = info->userSendData + offset;
            datagram->vec[datagram->nVec].len  = dataLen;
            datagram->nVec += 1;
        }
    }

    return dataLen;
}

/*---------------------------------------------------------------------------*
  Name:         DoSwsAvoidance -- Perform silly window avoidance algorithm

  Description:  Silly window avoidance [RFC1122 4.2.3.4 MUST]

                Set initial RTT and RTO to 0 sec and 3 sec, respectively
                [RFC1122]. Lower bound SHOULD be measured in fractions of a
                second (to accomodate high speed LANs). Upper bound SHOULD be
                2 * MSL (i.e., 240 sec).

                As GC protocol stack implementation *intentionally* removes
                'delayed ACK' mechanisim, rttMin field can be set reasonably
                small.

                To avoid a resulting deadlock, it is necessary to
                have a timeout to force transmission of data. It may
                be convenient to combine this timer with the timer
                used to probe zero windows.

  Arguments:    info        Pointer to TCP information block
                sendSize    MIN(SendMSS+20, MMS_S) - TCPhdrsize - IPoptionsize
                            Note MMS_S = the maximum transport-layer message size
                effSendMss  info->mss - optlen
                flag

  Returns:      TRUE if packet should not be sent to avoid SWS.
 *---------------------------------------------------------------------------*/
static BOOL DoSwsAvoidance(TCPObj* info, s32 sendSize, s32 effSendMss, u16 flag)
{
    BOOL       acked;     // for Nagle algorithm
    s32        win;
    s32        reduction;

    // Receiver silly window avoidance algorithm with delayed ACK
    win = info->recvBuff - info->recvUser;
    reduction = win - info->recvWin;
    if (MIN(info->recvBuff / 2, 2 * effSendMss) <= reduction)
    {
        info->recvWin = win;
        return FALSE;   // Send a window update
    }

    if (effSendMss <= reduction && info->recvWin < effSendMss)  // To avoid sender's SWS
    {
        info->recvWin = win;
        return FALSE;   // Send a window update
    }

    // Do not delay
    if (flag & (TCP_FLAG_RST | TCP_FLAG_ACK | TCP_FLAG_FIN | TCP_FLAG_SYN))
    {
        return FALSE;
    }

    if (sendSize <= 0)
    {
        return TRUE;
    }

    //
    // The sender's SWS avoidance algorithm
    //
    // (1) A maximum-sized segment can be sent.
    if (effSendMss <= sendSize)
    {
        return FALSE;
    }
    if (info->flag & TCP_SO_NAGLE)
    {
        acked = (info->sendNext == info->sendUna);
    }
    else
    {
        acked = TRUE;
    }
    if (acked)
    {
        // (2) The data is pushed and all queued data can be sent now.
        if (flag & TCP_FLAG_PSH)    // PSH is set if we have no more data to send.
        {
            return FALSE;
        }
        // (3) At least a fraction of the maximum window can be sent.
        if (info->sendMaxWin / 2 <= sendSize)
        {
            return FALSE;
        }
    }
    // (4) The override timeout occurs (retransmission)
    if (TCP_SEQ_GT(info->sendNext, info->sendMax))
    {
        return FALSE;
    }

    //
    // (SACK-4) Bypass sender silly window avoidance for fast retransmit
    //
    if (info->flag & TCP_SO_FAST_RXMIT)
    {
        return FALSE;
    }

    return TRUE;
}

// Handles delayed ACK timer (200 msec)
static void DackHandler(OSAlarm* alarm, OSContext* context)
{
#ifdef IOP_OS
    TCPIP_UNUSED(context);
#else
    #pragma unused(context)
#endif // IOP_OS
    
    TCPObj* info;

    info = (TCPObj*) ((u8*) alarm - offsetof(TCPObj, dackAlarm));
    if (TCP_SEQ_GT(info->recvAcked, info->recvNext))
    {
        TCPOutput(info, TCP_FLAG_ACK);
    }
}

static void TCPOutputCallback(TCPObj* info, s32 result)
{
    ASSERT(info->datagram.interface == NULL);
    ASSERT(info->datagram.queue == NULL);

    info->sendBusy = FALSE;
    if (result < 0)
    {
        info->err = result;     // Use just as a hint
    }
    TCPOutput(info, 0);
}

// Note TCPOutput does not process RSTs.
void TCPOutput(TCPObj* info, u16 flag)
{
#ifdef IOP_OS
    IPHeader*    ip = NULL;
#ifdef IP_INET6
    IP6Hdr*      ip6 = NULL;
#endif  // IP_INET6
#else
    IPHeader*    ip;
#ifdef IP_INET6
    IP6Hdr*      ip6;
#endif  // IP_INET6
#endif  // IOP_OS
    
    TCPHeader*   tcp;
    int          optlen;
    s32          sendSize;
    s32          result;
    IFVec*       vec;
    TCPSackHole* hole = NULL;
    s32          onxt;

#ifdef IOP_OS
    IFDatagram*  datagram = NULL;
    u8           header[TCP_MAX_HLEN];
    s32          offset;
#ifdef IP_INET6
    IP6Entry*    nextHop = NULL;
    IP6Entry*    destination;
#endif  // IP_INET6
    IPInterface* interface = NULL;
#else
    IFDatagram*  datagram;
    u8           header[TCP_MAX_HLEN];
    s32          offset;
#ifdef IP_INET6
    IP6Entry*    nextHop;
    IP6Entry*    destination;
#endif  // IP_INET6
    IPInterface* interface;
#endif  // IOP_OS

    s32          plen;

    if (info->state == TCP_STATE_CLOSED)
    {
        return;
    }

#ifdef VERBOSE
    OSReport("TCPOutput: TCPInfo (%p: %s %u)\n",
             info, TCPStateNames[info->state], info->sendNext - info->iss);
#endif

    onxt = info->sendNext;
    if (TCP_RXMIT_THRESH <= info->dupAcks)
    {
#ifdef TCP_SACK
        if (info->flag & TCP_SO_SACK)
        {
            //
            // (SACK-2) Override sendNext if any SACK-generated retransmissions.
            //
            hole = TCPSackOutput(info);
            if (hole)
            {
                info->sendNext = hole->rxmit;
            }
        }
        else
#endif  // TCP_SACK
        {
            // NewReno
            if (info->flag & TCP_SO_FAST_RXMIT)
            {
                // Retransmit the lost segment
                info->sendNext = info->sendUna;
            }
        }
    }

    switch (info->state)
    {
      case TCP_STATE_SYN_SENT:
        // Clear ACK
        flag &= ~TCP_FLAG_ACK;
        break;
      case TCP_STATE_SYN_RECEIVED:
        // In SYN-RECEIVED state, do not ack other than our SYN.
        if (TCP_SEQ_GT(info->recvAcked, info->irs + 1))
        {
            flag |= TCP_FLAG_ACK;
        }
        break;
    }

    // SYN must be set *before* TCPMakeOption() so it can get the correct
    // effective send mss.
    switch (info->state)
    {
      case TCP_STATE_SYN_SENT:
      case TCP_STATE_SYN_RECEIVED:
        if (info->iss == info->sendNext)
        {
            flag |= TCP_FLAG_SYN;
        }
        break;
    }

    if (info->sendUna == info->sendMax &&   // Idle?
        info->lastSend + info->rto < OSGetTime())
    {
        // Phase changed. Goes back to slow start. See "Congestion
        // Avoidance and Control" by Van Jacobson, et al. November, 1988.
        //
        // TCP MAY set the restart window to the minimum of the value
        // used for the initial window and the current value of cwnd
        // (in other words, using a larger value for the restart
        // window should never increase the size of cwnd).  [RFC 3390]
        info->cWin = MIN(TCP_IW(info), info->cWin);
    }

    // Get send size in sequence count
    tcp = (TCPHeader*) header;
    tcp->flag = 0;
    optlen = TCPMakeOption(tcp, info, flag);
    sendSize = TCPCalcSendSize(info, info->mss - optlen, &flag, &offset, hole);
#ifdef TCP_SACK
    if (hole && info->sendNext != hole->rxmit)
    {
        // Zero window probe
        onxt = info->sendNext;
        hole = NULL;
        info->flag &= ~TCP_SO_FAST_RXMIT;
    }
#endif  // TCP_SACK

    // Perform silly window avoidance
    if (DoSwsAvoidance(info, sendSize, info->mss - optlen, flag))
    {
        goto Wait;  // wait for override timer time-out
    }

    switch (info->pair->family)
    {
      case SO_PF_INET:
        ASSERT(info->interface);
        interface = info->interface;
        if (!info->sendBusy)
        {
            datagram = &info->datagram;
            IFInitDatagram(datagram, ETH_IP, 1);    // Initialize datagram.nVec
            ip = (IPHeader*) info->header;

            datagram->callback = (IFCallback) TCPOutputCallback;
            datagram->param = info;
        }
        else
        {
            datagram = interface->alloc(interface, (s32) (sizeof(IFDatagram) + 3 * sizeof(IFVec) +
                                        IP_MIN_HLEN + TCP_MIN_HLEN + optlen));
            if (datagram == NULL)
            {
                ++interface->ipStat.outDiscards;
                goto Wait;  // wait for override timer time-out
            }
            IFInitDatagram(datagram, ETH_IP, 4);    // Initialize datagram->nVec
            datagram->nVec = 1;
            ip = (IPHeader*) ((u8*) datagram + sizeof(IFDatagram) + 3 * sizeof(IFVec));
            memcpy(ip, info->header, (size_t) IP_HLEN((IPHeader*) info->header));
        }
        tcp = (TCPHeader*) ((u8*) ip + IP_HLEN(ip));
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        ip = NULL;

        // Determine next-hop
        nextHop = IP6GetNextHop(info->pair,
                                &((SOSockAddrIn6*) IPGetRemoteSockAddr(info->pair))->addr,
                                &destination);
        if (nextHop == 0)
        {
            info->err = IP_ERR_UNREACHABLE;
            goto Wait;  // wait for override timer time-out
        }
        IP6SetNextHop(info->pair, nextHop);
        ASSERT(nextHop->interface);
        interface = nextHop->interface;

        if (!info->sendBusy)
        {
            datagram = &info->datagram;
            IFInitDatagram(datagram, ETH_IPv6, 1);  // Initialize datagram.nVec
            ip6 = (IP6Hdr*) info->header;

            datagram->callback = (IFCallback) TCPOutputCallback;
            datagram->param = info;
        }
        else
        {
            datagram = interface->alloc(interface, (s32) (sizeof(IFDatagram) + 3 * sizeof(IFVec) +
                                        sizeof(IP6Hdr) + TCP_MIN_HLEN + optlen));
            if (datagram == NULL)
            {
                ++interface->ipv6Stat.outDiscards;
                goto Wait;  // wait for override timer time-out
            }
            IFInitDatagram(datagram, ETH_IPv6, 4);  // Initialize datagram->nVec
            datagram->nVec = 1;
            ip6 = (IP6Hdr*) ((u8*) datagram + sizeof(IFDatagram) + 3 * sizeof(IFVec));
            memcpy(ip6, info->header, sizeof(IP6Hdr));
        }
        tcp = (TCPHeader*) ((u8*) ip6 + sizeof(IP6Hdr));
        break;
#endif  // IP_INET6
    }

    if (0 < sendSize)
    {
        TCPPrepareData(info, datagram, sendSize, offset, flag);
    }

    OSCancelAlarm(&info->dackAlarm);
    if (info->state != TCP_STATE_SYN_SENT)
    {
        flag |= TCP_FLAG_ACK;
    }
    ASSERT(flag & TCP_FLAG_793);

    // Make TCP header
    tcp->flag = ((TCPHeader*) header)->flag;
    memcpy((u8*) tcp + TCP_MIN_HLEN, header + TCP_MIN_HLEN, (size_t) optlen);
    if (info->state != TCP_STATE_SYN_RECEIVED)
    {
        tcp->ack = info->recvAcked = info->recvNext;
    }
    else
    {
        tcp->ack = info->recvAcked = info->irs + 1;  // Just for SYN
    }
    tcp->src = ((IPSocket*) IPGetLocalSockAddr(info->pair))->port;
    tcp->dst = ((IPSocket*) IPGetRemoteSockAddr(info->pair))->port;
    ASSERT(tcp->src != 0);
    ASSERT(tcp->dst != 0);
    if (0 < sendSize)
    {
        tcp->seq = info->sendNext;
    }
    else
    {
        tcp->seq = info->sendMax;
    }
    if (TCP_SEQ_GT(tcp->seq, info->sendUp))
    {
        // Set urgent offset
        flag |= TCP_FLAG_URG;
        offset = info->sendUp - tcp->seq;
        tcp->urg = (u16) ((65495 < offset) ? 65535 : offset);
        if (info->flag & TCP_SO_STD_URG)
        {
            --tcp->urg;
        }
    }
    else
    {
        tcp->urg = 0;
        info->sendUp = info->sendUna;
    }
    if (info->state != TCP_STATE_SYN_SENT)
    {
        flag |= TCP_FLAG_ACK;
    }
    tcp->flag &= ~TCP_FLAG_793;
    tcp->flag |= (flag & TCP_FLAG_793);
    tcp->win = (u16) info->recvWin;
    tcp->sum = 0;

    plen = TCP_HLEN(tcp);
    for (vec = &datagram->vec[1]; vec < &datagram->vec[datagram->nVec]; ++vec)
    {
        plen += vec->len;
    }
    ASSERT(TCP_HLEN(tcp) <= plen);

    info->sendNext += sendSize;
    if (TCP_SEQ_GT(info->sendMax, info->sendNext))  // Not a retransmission?
    {
        // In case sending a window probe, sendNext is out of window and
        // must no be reflected to sendMax. Otherwise, DoAck() sends back
        // a wrong ACK number.
        if (TCP_SEQ_GE(info->sendNext, info->sendUna + info->sendWin))
        {
            ++interface->tcpStat.outSegs;
            info->sendMax = info->sendNext;
        }
        else
        {
            ++interface->tcpStat.retransSegs;
        }

        // If round trip timer isn't running, start it
        if (!info->rttTiming)
        {
            info->rttTiming = TRUE;
            info->rttSeq = tcp->seq;
            info->rtt = OSGetTime();
        }
    }
    else if (0 < sendSize)
    {
        ++interface->tcpStat.retransSegs;
    }

    // Start retransmission timer
    if (info->sendNext != info->sendUna)  // Not for an ACK-only segment
    {
        TCPStartRxmitTimer(info);
    }

#ifdef VERBOSE2
    OSReport("\n>>> ");
    TCPDumpHeader(ip, tcp);
    OSReport("TCPOut: TCPInfo (%p: %s %u)\n",
             info, TCPStateNames[info->state], info->sendNext - info->iss);
#endif

#ifdef TCP_SACK
    if (hole)
    {
        //
        // (SACK-5) Update scoreboard rxmit pointer and rxmitData size.
        //
        hole->rxmit += sendSize;
        info->rxmitData += sendSize;
    }
#endif  // TCP_SACK

    //
    // (SACK-6) Update aWin
    //
    // Update sendAwin to reflect the new data that was sent.
    info->sendAwin = (info->sendMax - info->sendFack) + info->rxmitData;

    //
    // (SACK-7) Turn off TCP_SO_FAST_RXMIT bit
    //
    info->flag &= ~TCP_SO_FAST_RXMIT;

    //
    // (SACK-8) Restore sendNext
    //
    if (TCP_SEQ_GT(info->sendNext, onxt))
    {
        info->sendNext = onxt;
    }

    if (!info->sendBusy)
    {
        info->sendBusy = TRUE;
    }
    else
    {
        datagram->nVec = 4; // To release fifo memory correctly.
    }
    switch (info->pair->family)
    {
      case SO_PF_INET:
        ip->len = (u16) (IP_HLEN(ip) + plen);
        datagram->vec[0].data = ip;
        datagram->vec[0].len  = IP_HLEN(ip) + TCP_HLEN(tcp);
        result = IPOut(datagram);
        if (result < 0)
        {
            // If result is ins. resource, do source quech and back to slow start.
            // However, the current IPOut() does not fail due to ins. resource.
            if (interface)
            {
                // datagram has not been sent out. Must release memory
                ASSERT(datagram->callback == NULL);
                interface->free(interface, datagram, (s32) (sizeof(IFDatagram) + 3 * sizeof(IFVec) +
                                IP_MIN_HLEN + TCP_MIN_HLEN + optlen));
            }
            else
            {
                ASSERT(datagram->callback);
                TCPOutputCallback(info, result);
            }
            return;
            // NOT REACHED HERE
        }
        break;
#ifdef IP_INET6
      case SO_PF_INET6:
        ip6->plen = (u16) plen;
        datagram->vec[0].data = ip6;
        datagram->vec[0].len  = (s32) (sizeof(IP6Hdr) + TCP_HLEN(tcp));
        tcp->sum = IP6CheckSum(IP_PROTO_TCP, datagram->vec, datagram->nVec, tcp, plen);
        datagram->mtu = (u16) IP6GetPathMTU(destination, (s32) sizeof(IP6Hdr) + plen);
        result = IP6Out(interface, datagram, nextHop);
        if (result < 0)
        {
            // If result is ins. resource, do source quech and back to slow start.
            // However, the current IPOut() does not fail due to ins. resource.
            if (interface)
            {
                // datagram has not been sent out. Must release memory
                ASSERT(datagram->callback == NULL);
                interface->free(interface, datagram, (s32) (sizeof(IFDatagram) + 3 * sizeof(IFVec) +
                                sizeof(IP6Hdr) + TCP_MIN_HLEN + optlen));
            }
            else
            {
                ASSERT(datagram->callback);
                TCPOutputCallback(info, result);    // XXX shoud wait...
            }
            return;
            // NOT REACHED HERE
        }
        break;
#endif  // IP_INET6
    }

    info->lastSend = OSGetTime();  // For re-starting the idle connection.
    return;

Wait:
    // Wait for override timer time-out
    if (TCP_SEQ_GT(info->sendNext, onxt))
    {
        info->sendNext = onxt;
    }
    if (0 < sendSize)
    {
        // Set persist/SWS override timer. Note SWS avoidance does not
        // apply for packet retransmission.
        TCPStartRxmitTimer(info);
    }
    if (TCP_SEQ_GT(info->recvAcked, info->recvNext))
    {
        // Delayed ACK
        // 4.2 Generating Acknowledgments [RFC 2581]
        // 4.2.3.2  When to Send an ACK Segment [RFC 1122]
        OSCancelAlarm(&info->dackAlarm);
        OSSetAlarm(&info->dackAlarm,
                   OSMillisecondsToTicks((OSTime) TCP_DACK_TIME),
                   DackHandler);
    }
    return;
}


//
// TCP unit test functions
//

s32 __TCPCalcSendSize(TCPInfo* info, s32 effSendMss, u16* pflag)
{
    int size;
    s32 offset;

    ASSERT(info->info.family = SO_PF_INET);

    // Initialize datagram.nVec
    IFInitDatagram(&info->obj.datagram, ETH_IP, 1);
    size = TCPCalcSendSize(&info->obj, effSendMss, pflag, &offset, NULL);
    if (0 < size)
    {
        TCPPrepareData(&info->obj, &info->obj.datagram, size, offset, *pflag);
    }
    if (info->obj.datagram.nVec < 2)
    {
        info->obj.datagram.vec[1].data = NULL;
        info->obj.datagram.vec[1].len = 0;
    }
    return size;
}
