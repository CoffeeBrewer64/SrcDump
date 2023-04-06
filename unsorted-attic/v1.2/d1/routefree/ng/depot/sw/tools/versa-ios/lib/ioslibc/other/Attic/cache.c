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

#include <sktypes.h>
#include <sc.h>
#include "sclibc.h"

#define CACHE_LINE_SIZE 16
#define CACHE_LINE_MASK (CACHE_LINE_SIZE-1)

static void
__cacheOp(void *ptr, size_t bytes, u32 cache, u32 op)
{
    u32 start, end, off;

    /* Compute requested start and end of region */
    start = (u32)ptr;
    end = (u32)ptr + bytes;

    /* If region is not completely contained in SDRAM, then return */
    if (start < MEM0_START || end >= MEM3_END) {
        return;
    }

    /* Align start and end on cache line boundaries */
    start &= ~CACHE_LINE_MASK;
    end = ((end + CACHE_LINE_MASK) & ~CACHE_LINE_MASK) - 1;

    /* Get 32MB offset into SDRAM */
    start &= 0x03ffffff;
    end &= 0x03ffffff;

    /* For each cache line in 'cache' perform 'op' */
    for (off = start; off < end; off += CACHE_LINE_SIZE) {
        u32 addr = CPS_START | (cache << CPS_CACHE_SHIFT) | (op << CPS_OP_SHIFT) | off;
        IO_WRITE(addr, 1);
    }
}

void
SCInvalidate(void *ptr, size_t bytes)
{
    __cacheOp(ptr, bytes, CPS_CACHE_SC, CPS_OP_INV);
}

void
SCWriteback(void *ptr, size_t bytes)
{
    __cacheOp(ptr, bytes, CPS_CACHE_SC, CPS_OP_WB);
}

void
SCWritebackInvalidate(void *ptr, size_t bytes)
{
    __cacheOp(ptr, bytes, CPS_CACHE_SC, CPS_OP_WBINV);
}

void
CCInvalidate(void *ptr, size_t bytes)
{
    __cacheOp(ptr, bytes, CPS_CACHE_CC, CPS_OP_INV);
}

void
CCWriteback(void *ptr, size_t bytes)
{
    __cacheOp(ptr, bytes, CPS_CACHE_CC, CPS_OP_WB);
}

void
CCWritebackInvalidate(void *ptr, size_t bytes)
{
    __cacheOp(ptr, bytes, CPS_CACHE_CC, CPS_OP_WBINV);
}

