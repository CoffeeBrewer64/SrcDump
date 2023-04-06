#ident "$Id: debug.c,v 1.3 2006/03/29 18:57:49 craig Exp $"
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
 * Functions used only for debugging
 * 
 */

#include "hw.h"
#include "ioslibc.h"
#include "ios.h"
#include "debug.h"

extern  IOSMessageQueueId      dvdDriverSleepQueue;

/* ------------------------------------------------------------------------ */
void
doSleep(const int numSecs)
{
    IOSError            receiveError;
    IOSMessage          inMesg;
    IOSTimerId          sleepId;
    IOSMessage          timeoutMesg;


    timeoutMesg = 0xdeaddead;	// Compiler fodder - value isn't actually used
    sleepId = IOS_CreateTimer(numSecs * 1000 * 1000, 0,
                              dvdDriverSleepQueue, timeoutMesg);

    DPRINT2("(doSleep) Sleeping for %u seconds.\n", time);
    receiveError = IOS_ReceiveMessage(dvdDriverSleepQueue,
                                      (IOSMessage *) &inMesg,
                                      IOS_MESSAGE_BLOCK);
    DPRINT("(doSleep) Done sleeping.\n");
    IOS_DestroyTimer(sleepId);
}

/* ------------------------------------------------------------------------ */

void
printMD5sum(const void* const ptr, const uint32_t numBytes)
{
    md5_state_t state;
    md5_byte_t digest[16];

    md5_init(&state);
    md5_append(&state, ptr, numBytes);
    md5_finish(&state, digest);

    for (int idx = 0; idx < 16; idx++) {
        printf("%02x", digest[idx]);
    }
}
/* ------------------------------------------------------------------------ */
