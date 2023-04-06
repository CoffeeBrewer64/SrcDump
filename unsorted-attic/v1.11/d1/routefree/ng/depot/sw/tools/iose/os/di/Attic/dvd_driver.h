#ident "$Id: dvd_driver.h,v 1.10 2006/02/26 02:14:53 craig Exp $"
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

#ifndef DVD_DRIVER_H
#define DVD_DRIVER_H

#ifdef RVL
#include "stdint.h"
#include "stdbool.h"
#else
#include <stdint.h>
#endif // ifdef RVL

#include "iostypes.h"

enum dvdDisk {dvdDiskTypeError = 0, dvdNoDisk, dvdVideo, dvdGcDisk, dvdRvlDisk};
typedef enum dvdDisk            dvdDisk_t;

/* Values are from section 5.1.1 of the drive manual */
enum dvdStatus {dvdStatusReady         = 0x0,
                dvdStatusCoverOpen     = 0x1,
                dvdStatusDiscChange    = 0x2,
                dvdStatusNoDisk        = 0x3, /* and cover is closed...*/
                dvdStatusMotorStop     = 0x4,
                dvdStatusNoDiscId      = 0x5,
                dvdStatusUnknown       = 0x6,
                dvdStatusBogus         = 0xFF
                };
typedef enum dvdStatus dvdStatus_t;

enum dvdCommand {dvdNoCommand,
                 dvdInquiry,
                 dvdReadDiskId,
                 dvdNormalRead,
                 dvdRequestError
                };
typedef enum dvdCommand dvdCommand_t;

#define IOS_IOB_POOLNUM         0
extern IOSMessageQueueId        dvdDiscEventQueue, dvdTimeoutQueue;
extern uint8_t                  h3HashArray[];
extern bool                     coverWasClosed;
/****************** Function declarations ***************************/
void diFatalError (const char *err_string) __attribute__((noreturn));
bool withinResetTime(const uint32_t timeInMilliSecs);

#endif
