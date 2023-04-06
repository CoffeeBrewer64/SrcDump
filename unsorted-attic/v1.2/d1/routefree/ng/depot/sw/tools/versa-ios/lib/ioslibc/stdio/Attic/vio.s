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

#include <asm.h>
#include "semihost.h"

    .text

#define SEMIHOST_FUNC(f, F) \
    BEGIN_THUMB_PROC(__sys_##f); \
        mov r2, lr; \
        mov r1, r0; \
        mov r0, #SYS_##F; \
        swi 0xab; \
        bx  r2; \
    END_PROC(__sys_##f)

SEMIHOST_FUNC(open, OPEN);
SEMIHOST_FUNC(close, CLOSE);
SEMIHOST_FUNC(writec, WRITEC);
SEMIHOST_FUNC(write0, WRITE0);
SEMIHOST_FUNC(write, WRITE);
SEMIHOST_FUNC(read, READ);
SEMIHOST_FUNC(readc, READC);
SEMIHOST_FUNC(iserror, ISERROR);
SEMIHOST_FUNC(istty, ISTTY);
SEMIHOST_FUNC(seek, SEEK);
SEMIHOST_FUNC(flen, FLEN);
SEMIHOST_FUNC(tmpnam, TMPNAM);
SEMIHOST_FUNC(remove, REMOVE);
SEMIHOST_FUNC(rename, RENAME);
SEMIHOST_FUNC(clocK, CLOCK);
SEMIHOST_FUNC(time, TIME);
SEMIHOST_FUNC(system, SYSTEM);
SEMIHOST_FUNC(errno, ERRNO);
SEMIHOST_FUNC(get_cmdline, GET_CMDLINE);
SEMIHOST_FUNC(heapinfo, HEAPINFO);
SEMIHOST_FUNC(elapsed, ELAPSED);
SEMIHOST_FUNC(tickfreq, TICKFREQ);
