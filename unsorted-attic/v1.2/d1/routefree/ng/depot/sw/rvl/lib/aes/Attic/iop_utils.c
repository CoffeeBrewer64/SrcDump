/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished proprietary information of BroadOn Communications Corp.,
 *  and are protected by federal copyright law. They may not be disclosed
 *  to third parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 *  Description:
 *      This file implements the common functions used by all tests
 *
 */

#include "diag.h"
#include "iop_utils.h"
#include "iop.h"
#include "ioslibc.h"

#define AHMRDBI_TRUSTED ((AHM_BASE+AHMRDBI)|AHB_TRUSTED_OFFSET)


void 
IOP_InvalidateRDB(u32 invalidatedBit)
{
    u32 val;

    /* Invalidate IOP read buffer */
    val = busRd32((u32)AHMRDBI_TRUSTED) | invalidatedBit;
#ifdef DEBUG_PRINT
    busDbg("IOP: Invalidate AHM RDB: Reg(0x%08x) <- 0x%08x\n", 
        (AHMRDBI_TRUSTED), val);
#endif
    busWrt32((u32)(AHMRDBI_TRUSTED), val);
    busWrt32((u32)(AHMRDBI_TRUSTED), (val & (~invalidatedBit)));

}


/* 
 * To enable interrupt, software must set the corresponding bit in the 
 * ACR Interrupt Register
 */
void
IOP_EnableIntr(u32 intrMask)
{
    busWrt32(ACR_REGS_BASE+ACRIOPIRQINTEN_OFFSET+AHB_TRUSTED_OFFSET, intrMask);

#ifdef DEBUG_PRINT
    busDbg("IOP: Set Interrupt Mask=0x%x", intrMask);
    busPrintf("%s: IOP Interrupt Enable Reg(0x%08x)=0x%08x", 
        __FILE__, (ACR_REGS_BASE+ACRIOPIRQINTEN_OFFSET+AHB_TRUSTED_OFFSET),
    busRd32(ACR_REGS_BASE+ACRIOPIRQINTEN_OFFSET+AHB_TRUSTED_OFFSET));
#endif
}


/* 
 * Since ACR Interrupt Status Register contains sticky bit for each
 * interrupt mask, software must write a 1 to clear the bit
 */
void
IOP_ClearIntr(u32 intrMask)
{
#ifdef DEBUG_PRINT
    busDbg("IOP: Clear Interrupt Mask=0x%x", intrMask);
#endif
    busWrt32(ACR_REGS_BASE+ACRIOPINTSTS_OFFSET+AHB_TRUSTED_OFFSET, intrMask);
}


int
IOP_CheckIntr(u32 intrMask)
{
    u32 intr;

    intr = busRd32(ACR_REGS_BASE+ACRIOPINTSTS_OFFSET+AHB_TRUSTED_OFFSET);
    if (intr & intrMask)
        return intr;

    return 0;
}


int
IOP_WaitIntr(u32 intrMask, u32 timeout)
{
    u32 i, val;
    u32 fail, done = 0;

    i = 0; fail = 0;
#ifdef DEBUG_PRINT
    busPrintf("%s: Polling IntrReg(0x%08x): Intr=0x%08x timeout=%d...", 
        __FILE__, (ACR_REGS_BASE+ACRIOPINTSTS_OFFSET+AHB_TRUSTED_OFFSET), 
        intrMask, timeout);
#endif
    while (!done) {
        val = IO_READ(ACR_REGS_BASE+ACRIOPINTSTS_OFFSET+AHB_TRUSTED_OFFSET);
        if (val & intrMask) {
#ifdef DEBUG_PRINT
            busDbg("IOP: Got Interrupt: Count=%d Reg=0x%08x", i, val);
#endif
            val = 0;
            done = 1;
        }
        if (i >= timeout) {
            busPrintf("\n%s: Wait for Interrupt -> FAIL: TIMEOUT Reg=0x%08x\n", 
                __FILE__, val);
            done = 1;
            fail++;
        }
        i++;
    }

    return(val);
}

