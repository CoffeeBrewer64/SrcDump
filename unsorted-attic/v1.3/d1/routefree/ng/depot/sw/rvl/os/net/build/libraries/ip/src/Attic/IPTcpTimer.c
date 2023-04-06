/*---------------------------------------------------------------------------*
  Project:  Dolphin OS IP API
  File:     IPTcpTimer.c

  Copyright 2002-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: IPTcpTimer.c,v $
  Revision 1.2  2006/04/07 22:44:39  mxu
  fix compiling and linking issues

  Revision 1.1  2006/04/05 23:41:22  mxu
  initial network stack code base

    
    33    2/28/06 9:08 Shiki
    Modified TCPRxmitTimeOut() to use modified IP6Entry{}.

    32    2/14/06 18:42 Shiki
    Removed TCPStat.

    31    2/14/06 9:58 Shiki
    Modified TCPInitRtt() to use interface-> defaultRtt, etc.

    30    2/09/06 17:49 Shiki
    Clean up.

    29    2/06/06 15:20 Shiki
    Fixed TCPRxmitTimeOut() to support IPv6.

    28    1/23/06 10:21 Shiki
    Fixed MSS management of IPv6.

    27    12/28/05 12:41 Shiki
    Updated function description.

    26    12/09/05 15:19 Shiki
    Implemented the limited transmit algorithm (RFC 3042).

    25    12/08/05 20:18 Shiki
    Revised comments.

    24    12/07/05 22:00 Shiki
    Implemented RFC 3782 (The NewReno Modification to TCP's Fast Recovery
    Algorithm).

    23    11/30/05 11:41 Shiki
    Revised to maintain cWin in units of bytes.

    22    11/24/05 14:06 Shiki
    Fixed TCPRxmitTimeOut() to set cwnd to 1 full-sized segment regardless
    of the value of IW. Otherwise, multiple TCP packets are transmitted
    upon each timeout, which is totally wrong.

    21    04/11/02 11:03 Ueno_kyu
    Added support for IPv6 Core Protocol.

    22    6/09/04 15:53 Shiki
    IPv6 Pilot implementation

    20    3/03/04 14:28 Shiki
    Modified to use a TCP initial cwnd of 2 segments as allowed in RFC
    2581.

    19    3/01/04 11:17 Shiki
    Fixed TCPRxmitTimeOut() to set RTO <- RTO * 2 as specified in RFC 2988.

    18    8/21/03 20:58 Shiki
    Added support for SACK/FACK.

    17    8/04/03 9:05 Shiki
    Clean up.

    16    5/28/03 15:48 Shiki
    Revised using the __TCPMaxPersist global variable for testing.

    15    5/28/03 15:22 Shiki
    Fixed persist timer management code so that a persist timer expires
    when no ACKs are received for TCP_MAX_PERSIST period of time. Note R2
    can be smaller than the probe interval and thus the previous code did
    not work correctly.

    14    5/14/03 8:59 Shiki
    Modified TCPRxmitTimeOut() to check info->sendBusy before recalculating
    IP check sum.

    13    5/13/03 18:26 Shiki
    Fixed TCPRxmitTimeOut() to recalculate IP checksum at the time the
    IP_DF bit is turned off.

    12    4/18/03 22:06 Shiki
    Modified to revalidate ARP upon local timeout.  XXX not fully checked
    yet.

    11    8/05/02 11:06 Shiki
    Implemented simple path MTU blackhole detection code.
    Removed congestion control code from TCPStopRxmitTimer() [Moved to
    TCPControlCongestion() in IPTcp.c].

    10    7/18/02 15:25 Shiki
    Revised TCP R2 management code.

    9     7/18/02 10:18 Shiki
    Added supoprt for TCPStat.

    8     7/17/02 18:26 Shiki
    Fixed TCPStopRxmitTimer() to extend rxmit timer properly if there is
    additional data not acknowledged yet.

    7     7/11/02 13:15 Shiki
    Fixed that persist timer management code so that a persist timer
    expires when no ACKs are received for R2 period of time.

    6     7/10/02 17:16 Shiki
    Added TCP_SO_PERSIST flag management code (still testing).

    5     4/15/02 12:46 Shiki
    Modified to call IPRecoverGateway() after R1 restransmits.

    4     4/10/02 18:21 Shiki
    Fixed TCPStopRxmitTimer() not to cancel alarm if there is additional
    data not acknowledged yet.

    3     3/13/02 18:30 Shiki
    Revised TCPSend() so it can directly transfer user data from the user
    space to the link layer.

    2     3/12/02 12:48 Shiki
    Fixed persist state management code bugs.

    1     3/11/02 19:36 Shiki
    Initial check-in.
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*
    Retransmittion timer [RFC 2988 except minimum 1 sec RTO. No one cares!]
    Slow start
    Congestion avoidance
    Retransmission timeout (RTO)
    Time wait timer (2MSL)
    Persist timer (RFC-793 Section 3.7, page 42)
 */

#include <dolphin/os.h>
#include <dolphin/socket.h>
#include "IPPrivate.h"
#ifdef IP_INET6
#include "IP6Private.h"
#endif

#include <stddef.h> // for offsetof()

int __TCPMaxPersist = TCP_MAX_PERSIST;  // in sec.

void TCPCutThresh(TCPObj* info)
{
    info->ssThresh = (info->sendMax - info->sendUna) / 2;
    info->ssThresh = MAX(info->ssThresh, 2 * info->mss);
}

// Handles retransmission/persist timer time-out
static void TCPRxmitTimeOut(OSAlarm* alarm, OSContext* context)
{
#ifdef IOP_OS
    TCPIP_UNUSED(context);
#else
    #pragma unused(context)
#endif // IOP_OS
    
    TCPObj*   info;
    IPSocket* dst;
#ifdef IP_INET6
    IP6Entry* nextHop;
#endif

    info = (TCPObj*) ((u8*) alarm - offsetof(TCPObj, rxmitAlarm));

    ++info->rxmitCount;
    if (TCP_MAX_BACKOFF <= info->rxmitCount)
    {
        info->rxmitCount = TCP_MAX_BACKOFF;
    }
    info->rto *= 2;
    if (info->rttMax < info->rto)
    {
        info->rto = info->rttMax;
    }

    if (!(info->flag & TCP_SO_PERSIST)) // Not in persist state
    {
        // Path MTU discovery blackhole detection [RFC 2923]
        if (TCP_PMTUD_BACKOFF == info->rxmitCount &&
            TCP_STATE_ESTABLISHED <= info->state)
        {
            IPHeader* header = (IPHeader*) info->header;

            // Turn off don't fragment bit to disable path MTU discovery.
            header->frag &= ~IP_DF;

            // If the header is used for a packet in the output queue,
            // the IP check sum must be recalculated.
            if (info->sendBusy)
            {
                header->sum = 0;
                header->sum = IPCheckSum(header);
            }

            // Reduce mss to TCP default minimal
            switch (info->pair->family)
            {
              case SO_PF_INET:
                info->mss = MIN(576 - IP_MIN_HLEN - TCP_MIN_HLEN, info->mss);
                break;
#ifdef IP_INET6
              case SO_PF_INET6:
                info->mss = MIN(IP6_MIN_MTU - (s32) sizeof(IP6Hdr) - TCP_MIN_HLEN, info->mss);
                break;
#endif
            }
        }

        if (TCP_R1 == info->rxmitCount)
        {
            switch (info->pair->family)
            {
              case SO_PF_INET:
                if (IPIsLocalAddr(NULL, info->datagram.dst))
                {
                    // Failure to ARP or to re-validate ARP mappings may
                    // be used as negative advice for the corresponding
                    // IP address. [RFC 1122]
                    ARPRevalidate(info->datagram.dst);

                    // Attemps a triggered-gateway-reselection [RFC 816]
                    dst = IPGetRemoteSockAddr(info->pair);
                    IPRecoverGateway(dst->addr);
                }
                break;
#ifdef IP_INET6
              case SO_PF_INET6:
                nextHop = IP6GetNextHop(info->pair, IPGetRemoteSockAddr(info->pair), NULL);
                if (nextHop)
                {
                    if (nextHop->state == ND_STATE_REACHABLE)
                    {
                        IP6SetNeighborState(nextHop, ND_STATE_STALE);
                    }
                    if (nextHop->flags & ND_FLAG_IS_ROUTER)
                    {
                        IP6Shuffle(nextHop);
                        IP6SetNextHop(info->pair, NULL);
                    }
                }
                break;
#endif
            }
        }
        else if (TCP_R1 < info->rxmitCount)  // R1 < R2
        {
            OSTime r2;

            // R2 timeout test
            switch (info->state)
            {
              case TCP_STATE_SYN_SENT:
              case TCP_STATE_SYN_RECEIVED:
                // R2 for a SYN segment MUST be at least 3 minutes. [RFC 1122]
                r2 = OSSecondsToTicks((OSTime) 180);    // R2 for SYN
                if (info->iss == info->sendUna && info->r2 < r2)
                {
                    break;
                }
                // FALL THROUGH
              default:
                r2 = info->r2;
                break;
            }
            if (r2 <= OSGetTime() - info->r0) // Reach R2
            {
                if (info->err == 0)
                {
                    info->err = IP_ERR_TIMEOUT;
                }
                TCPAbort(info);
                return;
                // NOT REACHED HERE
            }
        }
    }
    else    // In persist state
    {
        // r0 is updated everytime ACK is received by TCPStopRxmitTimer().
        if (OSSecondsToTicks((OSTime) __TCPMaxPersist) <= OSGetTime() - info->r0)
        {
            if (info->err == 0)
            {
                info->err = IP_ERR_TIMEOUT;
            }
            TCPAbort(info);
            return;
            // NOT REACHED HERE
        }
    }

#ifdef VERBOSE
    OSReport("TCPRxmitTimeOut: %p (%d times: %llu.%03llu sec) %u\n",
             info,
             info->rxmitCount,
             OSTicksToSeconds(OSGetTime() - info->r0),
             OSTicksToMilliseconds(OSGetTime() - info->r0) % 1000,
             info->sendNext);
#endif

    info->sendNext = info->sendUna;

    // Cancel RTT estimators. [Karn's algorithm]
    info->rttTiming = FALSE;

    // Goes back to slow start
    TCPCutThresh(info);

    // RFC 2581 3.1 Slow Start and Congestion Avoidance
    //
    //  Furthermore, upon a timeout cwnd MUST be set to no more than the loss
    //  window, LW, which equals 1 full-sized segment (regardless of the
    //  value of IW).  Therefore, after retransmitting the dropped segment
    //  the TCP sender uses the slow start algorithm to increase the window
    //  from 1 full-sized segment to the new value of ssthresh, at which
    //  point congestion avoidance again takes over.
    //
    // We must *NOT* set info->cWin to TCP_IW(info).
    info->cWin = info->mss;

    // RFC 3782
    // After a retransmit timeout, record the highest sequence number
    // transmitted in the variable "recover" and exit the Fast Recovery
    // procedure if applicable.

    // RFC 3571
    // Further, the new value of RecoveryPoint MUST be preserved and the
    // loss recovery algorithm outlined in this document MUST be
    // terminated.

    info->dupAcks = 0;  // Exit the Fast Recovery procedure
    info->sendRecover = info->sendMax;

    // After a retransmit timeout the data sender SHOULD turn off all of
    // the SACKed bits [RFC 2018]
    info->sendHoles = 0;
    info->sendFack = info->sendUna;
    info->rxmitData = 0;
    info->sendAwin = 0;

    TCPOutput(info, TCP_FLAG_ACK);
}

void TCPStartRxmitTimer(TCPObj* info)
{
    if (info->rxmitAlarm.handler != NULL)
    {
        // Retransmission timer has been started already.
        return;
        // NOT REACHED HERE
    }

    if (info->rxmitCount == 0)
    {
        info->r0 = OSGetTime();
    }

#ifdef VERBOSE
    OSReport("TCPStartRxmitTimer: %p (%d times: %llu.%03llu sec)\n",
             info,
             info->rxmitCount,
             OSTicksToSeconds(info->rto),
             OSTicksToMilliseconds(info->rto) % 1000);
#endif
    OSSetAlarm(&info->rxmitAlarm, info->rto, TCPRxmitTimeOut);
}

/*---------------------------------------------------------------------------*
  Name:         TCPStopRxmitTimer

  Description:  TCPStopRxmitTimer() controls the retransmission/persist
                timer and the congestion window size.

                Both info->sendWin and info->sendLen must be updated before
                calling TCPStopRxmitTimer().

  Arguments:    info    Pointer to TCPObj
                tcp     Pointer to TCPHeader

  Returns:      None.
 *---------------------------------------------------------------------------*/
void TCPStopRxmitTimer(TCPObj* info, TCPHeader* tcp)
{
#ifdef IOP_OS
    TCPIP_UNUSED(tcp);
#else
    #pragma unused( tcp )
#endif // IOP_OS
    
    s32 sendLen;

    sendLen = info->sendLen;
    if (info->sendCallback && 0 < info->userSendLen)
    {
        sendLen += info->userSendLen;
    }

    if (info->sendWin == 0 && 0 < sendLen)
    {
        // Entered persist state. To send window probes, just return
        // without canceling the current rxmit timer.
        info->flag |= TCP_SO_PERSIST;
        info->r0 = OSGetTime(); // So as not to timeout.
        TCPStartRxmitTimer(info);
        return;
    }
    else if (info->flag & TCP_SO_PERSIST)
    {
        // Moved out of persist state. Clear rxmit count.
        info->flag &= ~TCP_SO_PERSIST;
        info->rxmitCount = 0;
        OSCancelAlarm(&info->rxmitAlarm);
    }

    if (info->sendUna == info->sendMax)  // All outstanding data is acked
    {
        info->flag &= ~TCP_SO_PERSIST;
        info->rxmitCount = 0;
        OSCancelAlarm(&info->rxmitAlarm);
    }
    else
    {
        // There is additional data not acknowledged yet.
        // Start (i.e., extend) timer using the current rxmit count.
        TCPStartRxmitTimer(info);
    }
}

void TCPCancelRxmitTimer(TCPObj* info)
{
    info->flag &= ~TCP_SO_PERSIST;
    info->rxmitCount = 0;
    OSCancelAlarm(&info->rxmitAlarm);
}

// Calculate the retransmission timeout (rto)
static OSTime CalcRto(TCPObj* info)
{
    info->rxmitCount = 0;

    info->rto = info->srtt + 4 * info->rttDe;
    if (info->rto < info->rttMin)
    {
        info->rto = info->rttMin;
    }
    else if (info->rttMax < info->rto)
    {
        info->rto = info->rttMax;
    }
    return info->rto;
}

void TCPUpdateRtt(TCPObj* info, OSTime rtt)
{
    info->rtt = rtt;
    if (info->srtt)
    {
        OSTime delta = info->rtt - info->srtt;
        info->srtt += delta / 8;    // g = 1/8
        if (delta < 0)
        {
            delta = -delta;
        }
        info->rttDe += (delta - info->rttDe) / 4;    // h = 1/4
    }
    else
    {
        info->srtt = info->rtt;
        info->rttDe = info->rtt / 2;
    }
    CalcRto(info);
}

/*---------------------------------------------------------------------------*
  Name:         TCPInitRtt

  Description:  Set initial RTT and RTO to 0 sec and 3 sec, respectively
                [RFC1122]. Lower bound SHOULD be measured in fractions of a
                second (to accommodate high speed LANs). Upper bound SHOULD be
                2 * MSL (i.e., 240 sec).

  Arguments:    info    Pointer to TCP information block

  Returns:      None.
 *---------------------------------------------------------------------------*/
void TCPInitRtt(TCPObj* info)
{
    IPInterface* interface = info->interface;
    ASSERT(info->interface);

    info->rtt    = 0;
    info->srtt   = 0;
    info->rttDe  = interface->defaultRtt / 4;

    info->rttMin = interface->minRtt;
    info->rttMax = interface->maxRtt;

    CalcRto(info);
}
