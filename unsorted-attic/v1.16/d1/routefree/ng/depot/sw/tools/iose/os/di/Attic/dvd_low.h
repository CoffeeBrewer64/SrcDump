#ident "$Id: dvd_low.h,v 1.15 2006/03/14 04:35:24 craig Exp $"
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

#ifndef DVD_LOW_H
#define DVD_LOW_H

#include <stdint.h>

#include "dvd.h"
#include "dvd_command.h"

enum dvdDiscEventMesgType{DVD_EVENT_BOGUS, DVD_EVENT_BREAK,
                          DVD_EVENT_TRANS_DONE,
                          DVD_EVENT_ERROR, DVD_EVENT_COVER,
                          DVD_EVENT_TIMEOUT};

uint32_t handleDiCommand(const diCommand_t* const command, void *outputPtr);
void     enableTransferCompleteIntr(void);
void     enableErrorIntr(void);
void     disableCoverInterrupt(void);
void     enableCoverInterrupt(void);
void     doWaitForCoverClose(void);

bool     isTransCompInterruptSet(void);
bool     isErrorInterruptSet(void);
bool     isCoverInterruptSet(void);

void     diClearTransCompStatus(void);
uint32_t clearDriveErrorInterrupt();
void     diClearCoverIntr(void);
void     initializeDriveRegisters();

extern uint32_t driverLengthReg;

/* Timeout is 10 seconds */
/* #define DI_COMMAND_TIMEOUT      (10 * 1000) */
/*
 * FIXME - longer timeout is needed for hudson emu.  Change 
 * it back to 10 seconds for production.
 */
#define DI_COMMAND_TIMEOUT      (100 * 1000000)
// #define DI_COMMAND_TIMEOUT      1


#endif
