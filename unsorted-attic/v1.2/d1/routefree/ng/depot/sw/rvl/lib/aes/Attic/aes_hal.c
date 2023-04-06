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

//#include "dv.h"
#include "iop.h"
#include "aes_hal.h"
#include "iop_utils.h"
#include "ioslibc.h"
#include "diag.h"

int AES_ProgramKey(u32 *key)
{
    int i;

    /* Store the key data */
    busDbg("AES Key: 0x%x 0x%x 0x%x 0x%x 0x%x\n",
            key[0], key[1], key[2], key[3], key[4]);

    for (i = 0; i < 4; i++) {
        busWrt32(AES_KEY_REG, key[i]);
    }

    return 0;
}


int AES_ProgramIV(u32 *iv)
{

    int i;

    /* Program the actual IV data */
    busDbg("AES IV: 0x%x 0x%x 0x%x 0x%x 0x%x\n",
            iv[0], iv[1], iv[2], iv[3], iv[4]);

    for(i = 0; i < 4; i++) {
        busWrt32(AES_IVPTR_REG, iv[i]);
    }

    return 0;
}
  

int _AES_Setup(u32 srcAddr, u32 dstAddr)
{
    /* Clear interrupt and reset control register */
    // busWrt32(AES_CTRL_REG, 0x0); 

    busDbg("AES Setup: RPtrReg=0x%08x, WPtrReg=0x%08x\n", 
        srcAddr, dstAddr); 

    busWrt32(AES_RPTR_REG, srcAddr);
    busWrt32(AES_WPTR_REG, dstAddr);

    return 0;
}


int _AES_StartEncryption(u32 numBlocks, u32 chain, u32 intrEnable)
{
    u32 tempChain = 0;
    u32 tempMask = 0;
    u32 val;


    assert((numBlocks >= 0) && (numBlocks <= (AES_CTRL_SIZE_MASK+1)));

    if (chain == 1) {
        tempChain = AES_CTRL_CHAIN;
    }
    if (intrEnable == 1) {
        IOP_EnableIntr(ACRINTSTS_AESINT_MASK);
        tempMask = AES_CTRL_MASK;
    }

    val = AES_CTRL_EXEC | AES_CTRL_CMD(AES_ENCRYPT_CMD) | 
          tempChain | tempMask | ((numBlocks-1) & AES_CTRL_SIZE_MASK); 

    busDbg("AES Encrypt: CtrlReg=0x%08x\n", val); 
    busWrt32(AES_CTRL_REG, val);

    return 0;
}


int  _AES_Wait4Done(u32 timeout, u32 pollOnly)
{
    int i, done, rc, intr;
    u32 val, intrEnable;

    i = 0; 
    done = 0;
    rc = AES_ERROR_OK;

    busPrintf("%s: Wait: Polling CtrlReg(0x%08x) timeout=%d...", 
        __FILE__, AES_CTRL_REG, timeout);

    /* Check to see if interrupt is enabled */
    val = busRd32(AES_CTRL_REG);

    if (!(val & AES_CTRL_EXEC)) {
        busPrintf("\n%s: Wait: AES is not busy!\n", __FILE__);
        rc = AES_ERROR_UNKNOWN;
        goto _AES_Wait4Done_out;
    }

    if (!pollOnly) {
        intrEnable = val & AES_CTRL_MASK;
        if (intrEnable) {
            intr = IOP_WaitIntr(ACRINTSTS_AESINT_MASK, timeout);
            if (intr != 0) {
                busPrintf("\n%s: Wait: Wrong Intr (0x%08x)!\n", 
                    __FILE__, intr);
                rc = AES_ERROR_INTR;
                goto _AES_Wait4Done_out;
            }
            else {
                val = (busRd32(AES_CTRL_REG) & ~AES_CTRL_EXEC);
                busWrt32(AES_CTRL_REG, val);
                IOP_ClearIntr(ACRINTSTS_AESINT_MASK);
            }
            done = 1;
        }
    }  /* if */
         
    while (!done) {
        val = busRd32(AES_CTRL_REG);
        if ((val & AES_CTRL_EXEC) == 0) {
            done = 1;
            busPrintf("%s: Wait: Returned count=%d, CtrlReg(0x%08x)=0x%08x\n", 
                __FILE__, i, AES_CTRL_REG, val);
        }
        else {
            i++;
            if (i >= timeout) {
                done = 1;
                rc = AES_ERROR_TIMEOUT;
                busPrintf("\n%s: Wait: TIMEOUT [%d] CtrlReg=0x%08x\n", 
                    __FILE__, i, val);
                goto _AES_Wait4Done_out;
            }
        }
    }

    /* Check for memory violation */
    val = busRd32(AES_CTRL_REG);
    if (val & AES_CTRL_MVIOL) {
        busPrintf("\n%s: Wait: Memory access violation: 0x%08x\n", 
            __FILE__, val);
        rc = AES_ERROR_ACCESS;
        goto _AES_Wait4Done_out;
    }

    /* Check SIZE field - should be 0xfff after operation */
    if ((val & AES_CTRL_SIZE_MASK) != AES_CTRL_SIZE_MASK) {
        busPrintf("\n%s: Wait: Unexpected SIZE: 0x%08x, mask=0x%08x\n", 
            __FILE__, val, AES_CTRL_SIZE_MASK);
        rc = AES_ERROR_SIZE;
        goto _AES_Wait4Done_out;
    }

    /* Flush memory */
    ahbMemFlush(wb_aes);

    /* Invalidate AHM IOPD RDB */
    IOP_InvalidateRDB(AHMRDBI_REG_IOPD_RDBI_MASK);

    /* Invalidate AHM AES RDB */
    IOP_InvalidateRDB(AHMRDBI_REG_AES_RDBI_MASK);

_AES_Wait4Done_out:

    return rc;

}


int _AES_StartDecryption(u32 numBlocks, u32 chain, u32 intrEnable)
{
    u32 val;
    u32 tempChain = 0;
    u32 tempMask = 0;


    assert((numBlocks >= 0) && (numBlocks <= (AES_CTRL_SIZE_MASK+1)));

    if (chain == 1) {
        tempChain = AES_CTRL_CHAIN;
    }

    if (intrEnable == 1) {
        IOP_EnableIntr(ACRINTSTS_AESINT_MASK);
        tempMask = AES_CTRL_MASK;
    }

    /* Do the decryption */
    val = AES_CTRL_EXEC | AES_CTRL_CMD(AES_DECRYPT_CMD) |
          tempChain | tempMask | ((numBlocks-1) & AES_CTRL_SIZE_MASK); 

    busDbg("AES Decrypt: CtrlReg=0x%08x\n", val); 
    busWrt32(AES_CTRL_REG, val);

    return 0;
}


int _AES_StartDma(u32 numBlocks, u32 intrEnable)
{
    u32 val;
    u32 tempMask = 0;


    assert((numBlocks >= 0) && (numBlocks <= (AES_CTRL_SIZE_MASK+1)));

    if (intrEnable == 1) {
        IOP_EnableIntr(ACRINTSTS_AESINT_MASK);
        tempMask = AES_CTRL_MASK;
    }

    val = AES_CTRL_EXEC | (AES_CTRL_CMD(AES_DMA_CMD));
    val |= tempMask | ((numBlocks-1) & AES_CTRL_SIZE_MASK);

    busDbg("AES Dma: CtrlReg=0x%08x\n", val); 
    busWrt32(AES_CTRL_REG, val); 

    return 0;
}


int AES_Encrypt(u32 srcAddr, u32 dstAddr, u32 numBlocks, 
                    u32 chain, u32 intrEnable)
{

    _AES_Setup(srcAddr, dstAddr);
    _AES_StartEncryption(numBlocks, chain, intrEnable);

     return( _AES_Wait4Done(numBlocks*AES_OP_TIME, 0));
}


int AES_Decrypt(u32 srcAddr, u32 dstAddr, u32 numBlocks, 
                    u32 chain, u32 intrEnable)
{
  
    _AES_Setup(srcAddr, dstAddr);
    _AES_StartDecryption(numBlocks, chain, intrEnable);

     return( _AES_Wait4Done(numBlocks*AES_OP_TIME, 0));
}


int AES_Dma(u32 srcAddr, u32 dstAddr, u32 numBlocks, u32 intrEnable)
{

    _AES_Setup(srcAddr, dstAddr);
    _AES_StartDma(numBlocks, intrEnable);

     return( _AES_Wait4Done(numBlocks*AES_DMA_TIME, 0));

}

