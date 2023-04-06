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
#include "aes_hal.h"
#include "aes_sw.h"
#include "aes_test.h"
#include "iop_utils.h"
#include "iop.h"
#include "ioslibc.h"
#include "diag.h"

// #define DEBUG_PRINT
// int rand();  /* This added for call for MultiBlockTest */

/* Globals */
/* Reference data in 32-bit big-endian arrays */
u32 AESRefKey[4] = {
        0x2b7e1516,	/* Key is already in big endian */
        0x28aed2a6,
        0xabf71588,
        0x09cf4f3c};

u32 AESRefIV[4] = {
        0x0, 0x0, 0x0, 0x0};

u32 AESRefData[4] = {
        0x3243f6a8,	/* Data is already in big endian */
        0x885a308d,
        0x313198a2,
        0xe0370734};

u32 AESRefEncData[4] = {
        0x3925841d, 
        0x02dc09fb, 
        0xdc118597, 
        0x196a0b32};


/* Reference data in byte arrays */
static u8 refData[16] = {
	0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 
	0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};

static u8 refKey[16] = { 
	0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 
	0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

static u8 refIv[16] = { 
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};


static u32 hwDecData[4*AES_MAX_BLOCKS], 
       hwEncData[4*AES_MAX_BLOCKS], 
       swEncData[4*AES_MAX_BLOCKS], 
       swDecData[4*AES_MAX_BLOCKS],
       hwData[4*AES_MAX_BLOCKS],
       swData[4*AES_MAX_BLOCKS];

static u32 dmaBuf[4*AES_MAX_BLOCKS],
           tmpBuf1[4*AES_MAX_BLOCKS],
           tmpBuf2[4*AES_MAX_BLOCKS];
    

int aesMemWrite(u32 addr, u32 data[], u32 len, u32 readNVerify)
{
    /* Block is number of 16-byte block */
    int i, rc = AES_ERROR_OK;
    u32 d = 0;


    /* Initialize addr with data */

    busPrintf("%s: Writing addr(0x%08x - 0x%08x) <- data", 
        __FILE__, addr, addr+((len-1)*4));
    for (i=0; i < len; i++) {
        busWrt32((u32)(addr+(i*4)), data[i]);
    }

    /* Read and verify data */
    if (readNVerify) {
        for (i=0; i < len; i++) {
            d = busRd32((u32)(addr+(i*4)));
            if (d != data[i]) {
                busPrintf("%s: FAIL: [%02d] addr:0x%08x=0x%08x, exp=0x%08x",
                    __FILE__, i, addr+(i*4), d, data[i]);
                rc = AES_ERROR_UNKNOWN;
                goto aesMemWrite_out;
            }
        }
     }

aesMemWrite_out:

    return rc;

}


int aesMemFill(u32 addr, u32 pattern, u32 len, u32 readNVerify)
{
    /* Block is number of 16-byte block */
    int i, rc = AES_ERROR_OK;
    u32 d = 0;


    /* Initialize addr with pattern */
    busPrintf("%s: Writing addr(0x%08x - 0x%08x) <- 0x%08x", __FILE__, 
        addr, addr+((len-1)*4), pattern);
    for (i=0; i < len; i++) {
        busWrt32((u32)(addr+(i*4)), pattern);
    }

    if (readNVerify) {
        /* Read and verify data */
        for (i=0; i < len; i++) {
            d = busRd32((u32)(addr+(i*4)));
            if (d != pattern) {
                busPrintf("%s: FAIL: [%02d] addr:0x%08x=0x%08x, exp=0x%08x",
                    __FILE__, i, addr+(i*4), d, pattern);
                rc = AES_ERROR_UNKNOWN;
                goto aesMemFill_out;
            }
        }  /* for */
    }  /* if */

aesMemFill_out:

    return rc;

}  /* aesMemFill */



int aesCompareBlocks(u32 dataBuf1[], u32 dataBuf2[], s32 numBlocks, s32 little)
{
    /* Note: data1 is always in big endian and data2 is in little endian if 
       little is set */
    u32 equal = 0;
    u32 data;
    int i;
  
    for (i = 0; i < numBlocks*4; i++) {
        if (little) 
            data = htonl(dataBuf2[i]);
        else
            data = dataBuf2[i];
        if (dataBuf1[i] != data) {
            busPrintf("%s: Compare: D1(0x%08x) D2(0x%08x) -> FAIL", 
                __FILE__, dataBuf1[i], data);
            equal++;
        }
    }
    return equal;
}


/* 
 * Compare memory content with data buffer content
 */
int aesCompareMemBlocks(u32 addr, u32 data[], u32 numBlocks)
{
    /* Block is number of 16-byte block */
    int i, len, rc = AES_ERROR_OK;
    u32 d;


    len = numBlocks * 4;

    /* Read and verify data at destination */
    for (i=0; i < len; i++) {
        d = busRd32((u32)(addr+(i*4)));

        if (i < (4*AES_MAX_BLOCKS)) {
            tmpBuf1[i] = d;
        }

        if (d != data[i]) {
            rc = AES_ERROR_UNKNOWN;
            busPrintf("%s: [%d]: FAIL: addr:0x%08x=0x%08x, exp=0x%08x",
                  __FILE__, i, addr+(i*4), d, data[i]);
        }
    }

    /* If found error, dump the data */
    if (rc == AES_ERROR_UNKNOWN) {
        busPrintf("\n%s: Dumping memory: addr=0x%08x", __FILE__, addr);
        for (i = 0; i < len; i++) {
            if (i < (4*AES_MAX_BLOCKS)) 
                busPrintf("%s:[%3d]: 0x%08x=0x%08x,  exp=0x%08x", __FILE__, 
                    i, addr+(i*4), tmpBuf1[i], data[i]);
            else
                break;
        }
    }

    return(rc);

}  /* aesCompareMemBlocks */


/* 
 * Compare "len" words of content at two different memory locations
 */
int aesCompareMem(u32 addr1, u32 addr2, u32 len)
{
    int i, rc = AES_ERROR_OK;
    u32 d1, d2;

    /* Read and verify data at destination */
    for (i = 0; i < len; i++) {
        d1 = busRd32((u32)(addr1+(i*4)));
        // busDelay(15);
        d2 = busRd32((u32)(addr2+(i*4)));
        if (i < (4*AES_MAX_BLOCKS)) {
            tmpBuf1[i] = d1;
            tmpBuf2[i] = d2;
        }

#ifdef DEBUG_PRINT
        if (i < 128) {
            busPrintf("%s:[%3d]: 0x%08x=0x%08x,  0x%08x=0x%08x",
                  __FILE__, i, addr1+(i*4), d1, addr2+(i*4), d2);
        }
#endif
        if (d1 != d2) {
            rc = AES_ERROR_UNKNOWN;
            busPrintf("%s: [%d]: FAIL: 0x%08x=0x%08x != 0x%08x=0x%08x",
                  __FILE__, i, addr1+(i*4), d1, addr2+(i*4), d2);
        }
    }

    /* If found error, dump the data */
    if (rc == AES_ERROR_UNKNOWN) {
        busPrintf("\n%s: Dumping memory: addr1=0x%08x  addr2=0x%08x", __FILE__, 
            addr1, addr2);
        for (i = 0; i < len; i++) {
            if (i < (4*AES_MAX_BLOCKS)) 
                busPrintf("%s:[%3d]: 0x%08x=0x%08x,  0x%08x=0x%08x", __FILE__, 
                    i, addr1+(i*4), tmpBuf1[i], addr2+(i*4), tmpBuf2[i]);
            else
                break;
        }
    }

    return(rc);

}  /* aesCompareMem */


int aesDoEncryptDecryptTest(
    u32 srcAddr1, 
    u32 dstAddr, 
    u32 srcAddr2, 
    s32 numBlocks, 
    s32 chain, 
    u32 hwEncData[],	/* Returned hw data is in big endian */ 
    u32 key[], 		/* Big endian */
    u32 iv[], 		/* Big endian */
    u32 data[], 	/* Big endian */
    u32 swEncData[], 
    u32 hwDecData[], 
    u32 swDecData[])
{

    u32 swKey[4], swIv[4];
    int i, rc;


    rc = AES_ERROR_OK;

    /* Convert key, iv, and data to host little endian */
    for (i=0; i < 4; i++) {
        swKey[i] = ntohl(key[i]);
        swIv[i]  = ntohl(iv[i]);
    }

    for (i=0; i < numBlocks*4; i++) {
        swData[i] = ntohl(data[i]);
    }

    /* Perform hw aes encryption without chaining but use interrupt */
    AES_Encrypt(srcAddr1, dstAddr, numBlocks, chain, 1);
    
    /* Read out encrypted data to compare with software encryption */
    for (i=0; i < numBlocks*4; i++) {
        hwEncData[i] = busRd32(dstAddr + (4*i));
#ifdef DEBUG_PRINT
        busPrintf("%s: HW enc: dst(0x%x) -> 0x%08x", __FILE__,
            dstAddr+4*i, hwEncData[i]);
#endif
    }
    
    /* Perform software encryption */
    /* Get key and IV */
    aes_sw_encrypt((u8 *)swKey, (u8 *)swIv, (u8 *)swData, 
        numBlocks*AES_BLOCK_SIZE, (u8 *) swEncData);

#ifdef DEBUG_PRINT
    for (i=0; i < 4*numBlocks; i++) {
        busPrintf("%s: SW enc: BE(0x%08x)", __FILE__, htonl(swEncData[i]));
    }
#endif
      
    /* Compare against software data */
    if (aesCompareBlocks(hwEncData, swEncData, numBlocks, LE_ON) !=0) {
        busPrintf("\n%s: Comparing HW & SW Encryption -> FAIL\n", __FILE__);
        rc = AES_ERROR_UNKNOWN;
        goto aesDoEncryptDecrypt_out;
    }

    /***** Hardware Decryption ****/
    /* Perform hw aes decryption without chaining but use interrupt */
    AES_Decrypt(dstAddr, srcAddr2, numBlocks, chain, 1);
    
    /* Check results */
    /* Read out hardware decrypted data */
    for (i=0; i < numBlocks*4; i++) {
        hwDecData[i] = busRd32(srcAddr2 + 4*i);
#ifdef DEBUG_PRINT
        busPrintf("%s: HW dec: src2(0x%x) -> 0x%08x", __FILE__,
            srcAddr2+4*i, hwDecData[i]);
#endif
    }

    /* Compare against original data */
    if (aesCompareBlocks(hwDecData, data, numBlocks, 0) !=0) {
        busPrintf("\n%s: Comparing HW Decryption -> FAIL\n", __FILE__);
        rc = AES_ERROR_UNKNOWN;
        goto aesDoEncryptDecrypt_out;
    }

    /* Perform software decrypt: to check decrypt software */
    aes_sw_decrypt((u8 *)swKey, (u8 *)swIv, (u8 *)swEncData, 
        numBlocks*AES_BLOCK_SIZE, (u8 *)swDecData);
	
#ifdef DEBUG_PRINT
    for (i = 0; i < numBlocks*4; i++) {
        busPrintf("%s: SW dec: BE(0x%08x)", __FILE__, htonl(swDecData[i]));
    }
#endif

    if (aesCompareBlocks(hwDecData, swDecData, numBlocks, LE_ON) !=0) {
        busPrintf("\n%s: Comparing HW & SW Decryption -> FAIL\n", __FILE__);
        rc = AES_ERROR_UNKNOWN;
    }

aesDoEncryptDecrypt_out:

    return rc;

}  /* aesDoEncryptDecryptTest */


void aesConfigMemAccessForTest()
{

    u32 reg;

    /* Enable AES access for SRON */
    busPrintf("%s: Enable AES access for SRON: Reg 0x%x <- 0x%x", __FILE__, 
        (ACR_REGS_BASE+ACRSRNPROT_OFFSET+AHB_TRUSTED_OFFSET), 
         ACRSRNPROT_AESEN_MASK);
    busWrt32((u32)(ACR_REGS_BASE+ACRSRNPROT_OFFSET+AHB_TRUSTED_OFFSET), 
         ACRSRNPROT_AESEN_MASK);

    /* After reset wait for 256 cycles before programming AHMPROTF */
    // busDelay(256);
    reg = (busRd32(AHM_BASE+AHMSECSPL+AHB_TRUSTED_OFFSET) & 
           ~AHMSECSPL_REG_FINE_EN_SPL_MASK);
    busPrintf("%s: Disable AHM Fine Grain Access (Napa): Reg 0x%x <- 0x%x", 
        __FILE__, (AHM_BASE+AHMSECSPL+AHB_TRUSTED_OFFSET), reg);
    busWrt32((u32)(AHM_BASE+AHMSECSPL+AHB_TRUSTED_OFFSET), reg);

    reg = (busRd32(AHM_BASE+AHMSECDDR+AHB_TRUSTED_OFFSET) & 
           ~AHMSECDDR_REG_FINE_EN_DDR_MASK);
    busPrintf("%s: Disable AHM Fine Grain Access (DDR): Reg 0x%x <- 0x%x", 
        __FILE__, (AHM_BASE+AHMSECDDR+AHB_TRUSTED_OFFSET), reg);
    busWrt32((u32)(AHM_BASE+AHMSECDDR+AHB_TRUSTED_OFFSET), reg);

}


int aesDoRefTest(u32 testAddr)
{
    int i, rc, numBlocks;
    u32 srcAddr1, srcAddr2, dstAddr;


    /* Initialization */
    rc = AES_ERROR_OK;

    /* Verify software encryption against known reference data */
    aes_sw_encrypt((u8 *)refKey, (u8 *)refIv, (u8 *)refData, 
        AES_BLOCK_SIZE, (u8 *)swEncData);

    if (aesCompareBlocks(AESRefEncData, swEncData, 1, LE_ON) != 0) {
	busPrintf( "\n%s: AES SW Encrypt -> FAIL\n", __FILE__);
        rc = AES_ERROR_UNKNOWN;
        goto aesDoRefTest_out; 
    }
     
    /* Init addresses */
    numBlocks = 1;
    srcAddr1 = testAddr & 0xfffffff0;
    dstAddr = srcAddr1 + (numBlocks *4*4);
    srcAddr2 = dstAddr + (numBlocks *4*4);
      
    busPrintf("%s: src1=0x%08x, src2=0x%08x, dst=0x%08x\n\t\tnumBlocks=%d",
        __FILE__, srcAddr1, srcAddr2, dstAddr, numBlocks);

    /* Program key & iv */
    AES_ProgramKey(AESRefKey);
    AES_ProgramIV(AESRefIV);

    /***** Hardware Encryption *****/
    /* Write test data to source address */
    for (i=0; i < numBlocks*4; i++) {
        busWrt32(srcAddr1+(4*i), AESRefData[i]);
#ifdef DEBUG_PRINT
        busPrintf("%s: Writing  src1(0x%x) <- 0x%08x", __FILE__,
            srcAddr1+(4*i), AESRefData[i]);
#endif
    }

    /* Initialize destination with fixed pattern */
#ifdef DEBUG_PRINT
    busPrintf("%s: Writing dst: 0x%08x - 0x%08x <- 0x%08x", __FILE__,
            dstAddr, dstAddr+(4*numBlocks), 0xdeadbeef);
#endif
    for (i=0; i < (numBlocks*4); i++) {
        busWrt32(dstAddr + (4*i), 0xdeadbeef);
        busWrt32(srcAddr2+ (4*i), 0x12345678);
    }
      
    /* Flush memory */
    ahbMemFlush(wb_iop);

    /* Invalidate AHM AES RDB */
    IOP_InvalidateRDB(AHMRDBI_REG_AES_RDBI_MASK);

    rc = aesDoEncryptDecryptTest(srcAddr1, dstAddr, srcAddr2, numBlocks, 0,
                 hwEncData, AESRefKey, AESRefIV, AESRefData, swEncData, 
                 hwDecData, swDecData);
    if (rc != AES_ERROR_OK) {
        busPrintf( "\n%s: AES HW Block Reference Test -> FAIL\n", 
            __FILE__);
    }

aesDoRefTest_out: 

    return rc;

}  /* aesDoRefTest */


int aesDoMultiBlockTest(u32 srcAddr, u32 dstAddr, u32 numBlocks)
{
    int i, rc;
    u32 srcAddr1, srcAddr2;


    /* Initialization */
    rc = AES_ERROR_OK;

    /* Init addresses */
    srcAddr1 = srcAddr & 0xfffffff0;
    // dstAddr = srcAddr1 + (numBlocks *4*4);
    srcAddr2 = dstAddr + (numBlocks *4*4);
      
    busPrintf("%s: src1=0x%08x, src2=0x%08x, dst=0x%08x\n\t\tnumBlocks=%d",
        __FILE__, srcAddr1, srcAddr2, dstAddr, numBlocks);

    /* Program key & iv */
    AES_ProgramKey(AESRefKey);
    AES_ProgramIV(AESRefIV);

    /***** Hardware Encryption *****/
    /* Write test data to source address */
    for (i=0; i < numBlocks*4; i++) {
//        hwData[i] = rand();
	hwData[i] = i<<4;
        busWrt32(srcAddr1+(4*i), hwData[i]);
#ifdef DEBUG_PRINT
        busPrintf("%s: Writing  src1(0x%x) <- 0x%08x", __FILE__,
            srcAddr1+(4*i), hwData[i]);
#endif
    }

    /* Initialize destination with fixed pattern */
#ifdef DEBUG_PRINT
    busPrintf("%s: Writing dst: 0x%08x - 0x%08x <- 0x%08x", __FILE__,
            dstAddr, dstAddr+(4*numBlocks), 0xdeadbeef);
#endif
    for (i=0; i < (numBlocks*4); i++) {
        busWrt32(dstAddr + (4*i), 0xdeadbeef);
        busWrt32(srcAddr2 + (4*i), 0x12345678);
    }
 
    /* Flush memory */
    ahbMemFlush(wb_iop);

    /* Invalidate AHM AES RDB */
    IOP_InvalidateRDB(AHMRDBI_REG_AES_RDBI_MASK);

    rc = aesDoEncryptDecryptTest(srcAddr1, dstAddr, srcAddr2, numBlocks, 0,
                 hwEncData, AESRefKey, AESRefIV, hwData, swEncData, 
                 hwDecData, swDecData);
    if (rc != AES_ERROR_OK) {
        busPrintf( "\n%s: AES HW Block Reference Test -> FAIL\n", 
            __FILE__);
    }

    return rc;

}  /* aesDoMultiBlockTest */


/* 
 * This test performs 2 DMA from source to destination1 and from
 * destination1 to destination2 and compares with source
 *    - DMA number of blocks from source to destination1 
 *    - Compare data between destination1 and source
 *    - DMA number of blocks from destination1 to destination2
 *    - Compare data between destination2 and source
 */
int aesDoDmaTest(u32 srcAddr, u32 dstAddr, u32 numBlocks, u32 skipMemInit, 
                 u32 oneDmaOnly)
{
    /* Block is number of 16-byte block */
    int i, len, rc = AES_ERROR_OK;
    u32 dstAddr2;

    if (numBlocks > AES_MAX_BLOCKS) {
        rc = AES_ERROR_UNKNOWN;
        goto aesDoDmaTest_out;
    }
    len = numBlocks * 4;

    if (!skipMemInit) {
        /* Initialize srcAddr with random data */
        for (i=0; i < len; i++) {
            // dmaBuf[i] = rand();
            dmaBuf[i] = (((i+1) << 16) | i);
        }
        rc = aesMemWrite(srcAddr, dmaBuf, len, 1);
        if (rc != AES_ERROR_OK) {
            goto aesDoDmaTest_out;
        }

        rc = aesMemFill(dstAddr, 0xdeadbeef, len, 1);
        if (rc != AES_ERROR_OK) {
            goto aesDoDmaTest_out;
        }

        /* Flush memory */
        ahbMemFlush(wb_iop);

    }  /* if */

    /* Invalidate AHM AES RDB */
    IOP_InvalidateRDB(AHMRDBI_REG_AES_RDBI_MASK);

    busPrintf("\n%s: DMA #1: src=0x%08x dst=0x%08x numBlocks=%d",
        __FILE__, srcAddr, dstAddr, numBlocks);
    rc = AES_Dma(srcAddr, dstAddr, numBlocks, 1);
    if (rc != AES_ERROR_OK) {
        goto aesDoDmaTest_out;
    }

    /* Read and verify data at destination */
    /*
    if (skipMemInit) 
        rc = aesCompareMem(srcAddr, dstAddr, len);
    else
        rc = aesCompareMemBlocks(dstAddr, dmaBuf, numBlocks);
    */
    rc = aesCompareMem(srcAddr, dstAddr, len);
    if (rc != AES_ERROR_OK) {
        goto aesDoDmaTest_out;
    }

    if (oneDmaOnly) {
        goto aesDoDmaTest_out;
    }

    /* DMA from destination1 to destination2 */
    dstAddr2 = dstAddr + (numBlocks*16);
    busPrintf("\n%s: DMA #2: src=0x%08x dst=0x%08x numBlocks=%d",
        __FILE__, dstAddr, dstAddr2, numBlocks);
    rc = AES_Dma(dstAddr, dstAddr2, numBlocks, 0);
    if (rc != AES_ERROR_OK) {
        goto aesDoDmaTest_out;
    }

    /* Read and verify data at destination2 */
    /*
    if (skipMemInit) 
        rc = aesCompareMem(dstAddr, dstAddr2, len);
    else
        rc = aesCompareMemBlocks(dstAddr2, dmaBuf, numBlocks);
    */
    rc = aesCompareMem(dstAddr, dstAddr2, len);
    if (rc != AES_ERROR_OK) {
        goto aesDoDmaTest_out;
    }

aesDoDmaTest_out:

    return(rc);

}  /* aesDoDmaTest */

