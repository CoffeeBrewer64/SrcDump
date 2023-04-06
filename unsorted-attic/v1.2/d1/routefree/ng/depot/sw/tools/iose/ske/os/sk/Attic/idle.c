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
#include <sk.h>
#include <sktypes.h>
#include <stdio.h>
#include <unistd.h>
#include "idle.h"
#include "thread.h"
#include "emu_startprog.h"
#include <stdlib.h>

u32 __skIdleStack[IDLE_STACK_SIZE]; /* used in thread.c */

void
__idleThread(u32 arg)
{
    skEmuStartProg("usb_core", EMU_SHELL_PRIORITY + 1);
    while(1) {
        DBG_PRINTF((dbg_fp,"Idle thread starting shell...\n"));
        skEmuStartProg("sksh", EMU_SHELL_PRIORITY);
        skSetThreadPriority(0,0);
    }
}
