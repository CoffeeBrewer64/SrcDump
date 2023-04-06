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

#include "diag.h"
#include "iop.h"
#include "sha_hal.h"
#include "iop_utils.h"
#include "ioslibc.h"


/* SHA hardware functions */
void _SHA_Init(u32 initBuf[])
{
    int i;


    busDbg("SHA Init");

    /* CLear interrupt and stop any operation */
    IO_WRITE(SHA_CTRL_REG, 0);

    /* Load the initial hash value (Big endian) */
    if (initBuf == NULL) {
        IO_WRITE(SHA_BUF0_REG, 0x67452301);  /* Data is in big endian */
        IO_WRITE(SHA_BUF1_REG, 0xefcdab89);
        IO_WRITE(SHA_BUF2_REG, 0x98badcfe);
        IO_WRITE(SHA_BUF3_REG, 0x10325476);
        IO_WRITE(SHA_BUF4_REG, 0xc3d2e1f0);
    } else {
        busDbg("SHA Init: 0x%x 0x%x 0x%x 0x%x 0x%x\n",
           initBuf[0], initBuf[1], initBuf[2], initBuf[3], initBuf[4]);
       for (i=0; i < 5; i++) {
           IO_WRITE(SHA_BUF0_REG+(i*4), initBuf[i]);
       } 
    }  /* else */
}


void  _SHA_Setup(u32 addr)
{
    /* Addr must be 64-byte (bit 5:0) aligned */
    assert((addr & 0x3F) == 0);

    busDbg("SHA Setup: RPtrReg=0x%08x\n", addr);

    IO_WRITE(SHA_RPTR_REG, addr);
}


void _SHA_Hash(u32 numBlocks, u32 intr)
{
    u32 val = 0x0;

    assert((numBlocks >= 0) && (numBlocks <= (SHA_CTRL_SIZE_MASK+1)));

    if (intr == 1) {
        IOP_EnableIntr(ACRINTSTS_SHAINT_MASK);
        val = SHA_CTRL_INTR;
    }
    val = val | SHA_CTRL_EXEC | ((numBlocks -1) & SHA_CTRL_SIZE_MASK);

    busDbg("SHA Hash: CtrlReg=0x%08x\n", val);

    IO_WRITE(SHA_CTRL_REG, val);
}

 
int  _SHA_Wait4Done(u32 timeout, u32 pollOnly)
{
    int i, done, rc, intr;
    u32 val, intrEnable;

    i = 0; 
    done = 0;
    rc = SHA_ERROR_OK;

    busPrintf("%s: Wait: Polling CtrlReg(0x%08x) timeout=%d...", 
        __FILE__, SHA_CTRL_REG, timeout);

    /* Check to see if interrupt is enabled */
    val = busRd32(SHA_CTRL_REG);

    if (!(val & SHA_CTRL_EXEC)) {
        busPrintf("\n%s: Wait -> FAIL: SHA is not busy!\n", __FILE__);
        rc = SHA_ERROR_UNKNOWN;
        goto _SHA_Wait4Done_out;
    }

    if (!pollOnly) {
        intrEnable = val & SHA_CTRL_INTR;
        if (intrEnable) {
            intr = IOP_WaitIntr(ACRINTSTS_SHAINT_MASK, timeout);
            if (intr != 0) {
                busPrintf("\n%s: Wait: Wrong Intr (0x%08x)!\n", 
                    __FILE__, intr);
                rc = SHA_ERROR_INTR;
                goto _SHA_Wait4Done_out;
            }
            else {
                val = (busRd32(SHA_CTRL_REG) & ~SHA_CTRL_EXEC);
                busWrt32(SHA_CTRL_REG, val);
                IOP_ClearIntr(ACRINTSTS_SHAINT_MASK);
            }
            done = 1;
        }  /* if */
    }  /* if */

    while (!done) {
        val = busRd32(SHA_CTRL_REG);
        if ((val & SHA_CTRL_EXEC) == 0) {
            done = 1;
            busPrintf("%s: Wait: Returned count=%d, CtrlReg(0x%08x)=0x%08x", 
                __FILE__, i, SHA_CTRL_REG, val);
        }
        else {
            i++;
            if (i >= timeout) {
                done = 1;
                busPrintf("\n%s: Wait: TIMEOUT [%d] CtrlReg=0x%08x\n", 
                    __FILE__, i, val);
                rc = SHA_ERROR_TIMEOUT;
                goto _SHA_Wait4Done_out;
            }
        }
    }

    /* Check for memory violation */
    val = busRd32(SHA_CTRL_REG);
    if (val & SHA_CTRL_MVIOL) {
        busPrintf("\n%s: Wait: Memory access violation: 0x%08x\n",
            __FILE__, val);
        rc = SHA_ERROR_ACCESS;
        goto _SHA_Wait4Done_out;
    }

    /* Check SIZE field */
    if ((val & SHA_CTRL_SIZE_MASK) != SHA_CTRL_SIZE_MASK) {
        busPrintf("\n%s: Wait: Unexpected SIZE: 0x%08x, mask=0x%08x\n",
            __FILE__, val, SHA_CTRL_SIZE_MASK);
        rc = SHA_ERROR_SIZE;
        goto _SHA_Wait4Done_out;
    }

    /* Flush memory */
    ahbMemFlush(wb_sha);

    /* Invalidate AHM IOPD RDB */
    IOP_InvalidateRDB(AHMRDBI_REG_IOPD_RDBI_MASK);

    /* Invalidate AHM SHA RDB */
    IOP_InvalidateRDB(AHMRDBI_REG_SHA_RDBI_MASK);

_SHA_Wait4Done_out:

    return rc;

}


void _SHA_GetResult(u32 *hash)
{   
    int i;
  
    assert(hash != NULL);

    for (i=0; i < 5; i++) {
        hash[i] = IO_READ(SHA_BUF0_REG+(i*4));
        busPrintf("%s: Result: Hash[%d] = 0x%08x", __FILE__,
            i, hash[i]);
    }
}
 

int SHA_Hash(u32 srcAddr, u32 numBlocks, u32 intrEnable, u32 *hash)
{
    int fail = 0;

    _SHA_Init(NULL);

    _SHA_Setup(srcAddr);

    _SHA_Hash(numBlocks, intrEnable);

    fail = _SHA_Wait4Done(numBlocks * SHA_OP_TIME, 0);

    if (!fail)
        _SHA_GetResult(hash);

    return fail;

}


