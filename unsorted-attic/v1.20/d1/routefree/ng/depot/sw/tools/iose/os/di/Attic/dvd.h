#ident "$Id: dvd.h,v 1.19 2006/03/25 02:41:01 craig Exp $"
/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

/*
 * Contains definitions used in multiple files and that don't
 * particularly belong anywhere else
 */

#ifndef DVD_H
#define DVD_H

/*
 * Include either iostypes.h or types.h before including this
 * file.
 */

#ifdef RVL
#include "stdint.h"
#else
#include <stdint.h>
#include <stdbool.h>
#endif


typedef struct dvdState {
    uint32_t    savedDmaAddressRegister;
    uint32_t    savedDmaTransferRegister;
} dvdState_t;

extern dvdState_t       dvdState;

/*
 * The following are the values that struct diOtherMesg.mesgType takes
 */
#define DI_MESG_TIMEOUT                 (MAX_RM_MESG_NUM + 1)
#define DI_MESG_INTR                    (MAX_RM_MESG_NUM + 2)
#define DI_MESG_COMMAND                 (MAX_RM_MESG_NUM + 3)


typedef struct diOtherMesg {
    uint32_t    mesgType;       /* DI_MESG_TIMEOUT, DI_MESG_TRANS_COMPLETE... */
    bool        inUse;
    /*
     * Used to match timeouts to the command which caused the timeout
     * Starts at 0, then goes to 1, 2, etc.
     */
    uint8_t     commandNum;    
} diOtherMesg_t;

typedef union diInQueueMesg {
    IOSResourceRequest  *resourceMesg;
    diOtherMesg_t       *otherMesg;
} diInQueueMesg_t;

#define MAX_COMMAND_NUM         255
extern uint8_t  currentCommandNum;

#define DVD_IN_QUEUE_LEN        8
#define DVD_OUT_QUEUE_LEN       8
#define DVD_SLEEP_QUEUE_LEN     1
#define MAX_H3_HASH_SIZE        96 * 1024

/* Values returned by the DVDLowGetCoverStatus call */
#define DVD_COVER_UNKNOWN       0x0
#define DVD_COVER_OPEN          0x1
#define DVD_COVER_CLOSED        0x2
/*
 * Assumes:
 *              Clock rate of 243 MHz
 *              128 cycles/tick
 */
#define SYSTEM_TICKS_PER_MILLISEC       1898
/* Time is in microseconds */
#define DUMMY_COVER_INTR_TIME            200
#define COVER_STATUS_UNKNOWN_TIME        100
#define RESET_HOLD_TIME_MICRO_SEC        12
extern uint32_t         lastResetTime;
extern bool             resetTimeValid;

extern  IOSMessageQueueId      dvdDriverInQueue, dvdDriverOutQueue;
extern  IOSMessageQueueId      dvdDriverSleepQueue;

#endif /* DVD_H */
