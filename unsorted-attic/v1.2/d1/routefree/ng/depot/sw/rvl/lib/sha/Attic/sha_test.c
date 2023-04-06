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
#include "sha1.h"
#include "sha_test.h"
#include "iop_utils.h"
#include "ioslibc.h"

u32 SHARefData[16] = {
        0x61626380, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x00000018 };

u32 SHARefHash[5] = {
        0xa9993e36, 0x4706816a, 0xba3e2571, 0x7850c26c, 0x9cd0d89d };

u32 SHAMultiBlockRefData[32] = {
    0x61626364, 0x62636465, 0x63646566, 0x64656667,
    0x65666768, 0x66676869, 0x6768696a, 0x68696a6b,
    0x696a6b6c, 0x6a6b6c6d, 0x6b6c6d6e, 0x6c6d6e6f,
    0x6d6e6f70, 0x6e6f7071, 0x80000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000001c0
};

u32 SHAMultiBlockRefHash1[5] = {
    0xf4286818, 0xc37b27ae, 0x0408f581, 0x84677148, 0x4a566572
};

u32 SHAMultiBlockRefHash2[5] = {
    0x84983e44, 0x1c3bd26e, 0xbaae4aa1, 0xf95129e5, 0xe54670f1
};


u32 shaSwInput[MAX_SHA_SIZE];
u32 shaHwInput[MAX_SHA_SIZE];

static u32 inBuf[1024];


/*
 * shaCheckRegValues
 *
 * This function checks the values of the Read Ptr Reg and the size field
 * of the Control Reg for correctness after an operation. 
 */
int 
shaCheckRegValues(u32 addr, u32 numBlocks)
{
    int rc = SHA_ERROR_OK;
    u32 read, expect;

    /* Checking SHA_RPTR_REG */
    rc = SHA_ERROR_OK;

    read = IO_READ(SHA_RPTR_REG);

    expect = (addr + (numBlocks * 64)) & SHA_RPTR_ADDR_MASK;
    if (expect != read) {
        busPrintf("\n%s: RegCheck: ERROR: blocks=%d rptr=0x%08x exp=0x%08x\n", 
            __FILE__, numBlocks, read, expect);
        rc = SHA_ERROR_UNKNOWN;
    }
  
    /* Checking SHA_CTRL_REG size field */
    read = (IO_READ(SHA_CTRL_REG) & SHA_CTRL_SIZE_MASK);

    expect = SHA_CTRL_SIZE_MASK; /* Size=0x3ff when operation is done */
    if (read != expect) {
        busPrintf("\n%s: RegCheck: ERROR: size=0x%08x exp=0x%08x\n", 
            __FILE__, read, expect);
        rc = SHA_ERROR_UNKNOWN;
    }
  
    return rc;

}  /* shaCheckRegValues */
  

/*
 * This function simply reads and dumps out the memory 
 */
void
shaDumpMemory(u32 addr, u32 numBlocks)
{
    int i;

    busPrintf("\n%s: Dumping memory: addr=0x0%8x, blocks=%d", 
        __FILE__, addr, numBlocks);
    for (i = 0; i < (numBlocks*16); i += 2) {
        busPrintf("\t0x%08x: 0x%08x\t0x0%08x: 0x%08x", 
            addr+(i*4), IO_READ(addr+(i*4)),
            addr+((i+1)*4), IO_READ(addr+((i+1)*4)));
    }
}


/* 
 * This routine performs the SHA hash using software algorithm
 * The "input" data is a 32-bit array (big endian format).
 * The reurned hash value will be stored in the byte array "swHash".
 */
void 
shaSwHash(SHA1Context *sha, u32 *input, u32 numBlocks, u8 *swHash)
{
    int i;

    /* Convert input data to little endian for software SHA */
    for (i=0; i < numBlocks*16; i++) {
        shaSwInput[i] = ntohl(input[i]); 
    }

    SHA1Reset(sha);
    SHA1SetNoPadding(sha);
    SHA1Input(sha, (u8 *)shaSwInput, 64*numBlocks);
    SHA1Result(sha, swHash);
}


void
shaConfigMemAccessForTest()
{
    u32 reg;

    /* Enable SHA access for SRON */
    busPrintf("%s: Enable SHA access for SRON: Reg 0x%x <- 0x%x", __FILE__, 
        (ACR_REGS_BASE+ACRSRNPROT_OFFSET+AHB_TRUSTED_OFFSET), 
         ACRSRNPROT_SHAEN_MASK);
    busWrt32((u32)(ACR_REGS_BASE+ACRSRNPROT_OFFSET+AHB_TRUSTED_OFFSET), 
         ACRSRNPROT_SHAEN_MASK);

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


/*
 * shaInterleaveTest
 *
 * This test does the followings:
 *   1) Perform HW hash and SW hash
 *   2) Compare the two results
 *   3) Check the register values for expected data
 */
int 
shaInterleaveTest(u32 input[], u32 addr, u32 numBlocks) {
  
    SHA1Context sha;
    u8 swHash[20];
    u32 result[5];
    int i, rc = SHA_ERROR_OK;

  
    /* Issue HW SHA transaction with no interrupt enable */
    rc = SHA_Hash(addr, numBlocks, 0, result);
    if (rc != SHA_ERROR_OK) {
        goto shaInterleaveTest_out;
    }

    /* Calculate result from software */
    shaSwHash(&sha, input, numBlocks, swHash);

    for (i=0; i < 5; i++) {
        if ( result[i] != htonl(*((u32 *)(swHash+4*i)))) {
            rc = SHA_ERROR_UNKNOWN;
            busPrintf("%s: ILT: ERROR: [%d] HW=0x%08x != SW=BE(0x%08x)", 
                __FILE__, i, result[i], htonl(*((u32 *)(swHash+4*i))));
        }
    }

    if (rc != SHA_ERROR_OK) {
        goto shaInterleaveTest_out;
    }

    rc = shaCheckRegValues(addr, numBlocks);

shaInterleaveTest_out:

    return rc;

}  /* shaInterleaveTest */


/*
 * This basic test performs SHA hash using the hardware module and compares
 * the result against the software-generated hash value.
 * The "input" data is a 32-bit array in big endian.
 * The "addr" contains the memory location where the "input" data
 * is stored. "numBlocks" contains the number of 64-byte block that
 * is stored at "addr" location.
 */
int shaBasicTest(u32 input[], u32 addr, u32 numBlocks, u32 intrEnable)
{
  
    SHA1Context sha;
    u8 swHash[20];
    u32 result[5];
 
    int i, rc = SHA_ERROR_OK;


    /* Note: input data is in big endian */
    /* Initialize data in memory for hardware SHA engine */
    for (i = 0; i < (numBlocks*16); i++) {
        busWrt32(addr + (4*i), input[i]);
    }

    /* Flush memory */
    ahbMemFlush(wb_iop);

    /* Invalidate AHM SHA RDB */
    IOP_InvalidateRDB(AHMRDBI_REG_SHA_RDBI_MASK);

    /* Issue SHA transaction */
    rc = SHA_Hash(addr, numBlocks, intrEnable, result);
    if (rc != SHA_ERROR_OK) {
        goto shaBasicTest_out ;
    }

    /* Calculate result from software */
    shaSwHash(&sha, input, numBlocks, swHash);

    for (i=0; i < 5; i++) {
        if ( htonl(*((u32 *)(swHash+4*i))) != result[i]) {
            rc = SHA_ERROR_UNKNOWN;
            busPrintf("%s: BT: ERROR: [%d] HW=0x%08x != SW=BE(0x%08x)", 
                __FILE__, i, result[i], htonl(*((u32 *)(swHash+4*i))));
        }
    }

shaBasicTest_out:

    return rc;

}  /* shaBasicTest */


/*
 * This test performs SHA hash using the hardware module and compares
 * the result against the software-generated hash value.
 * However, it uses the reference data (1 block) for input so that the 
 * hash result is known. The test first compares the software-generated
 * result against the known SHA result to validate the correctness
 * of the software SHA engine. Then, the test calls "shaBasicTest"
 * to generate and compare the hash value from the hardware engine 
 * against the software result.
 * The "testAddr" contains the memory location where the "input" data
 * is stored.
 */
int shaRefTest(u32 testAddr)
{
    u32 i;
    SHA1Context sha;
    u8 swHash[20];
    int rc = SHA_ERROR_OK;


    /* Make sure s/w gave expected answer */
    shaSwHash(&sha, SHARefData, 1, swHash);

    /* Compare software result (in little endian) */
    for (i=0; i < 5; i++) {
#ifdef DEBUG_PRINT
	busPrintf("%s: RT: Comparing [%02d]: SW=0x%08x EXP=0x%08x", 
                __FILE__, i, ntohl(*((u32 *)(swHash+4*i))), SHARefHash[i]);
#endif
        if ( ntohl(*((u32 *)(swHash+4*i))) != SHARefHash[i]) {
	    rc = SHA_ERROR_UNKNOWN;
	    busPrintf("%s: RT: ERROR: [%d] SW=0x%08x != EXP=0x%08x", 
                __FILE__, i, ntohl(*((u32 *)(swHash+4*i))), SHARefHash[i]);
        }    
    }
    if (rc != SHA_ERROR_OK) {
        goto shaRefTest_out;
    }

    /* Stop and clear interrupt mask */
    busWrt32(SHA_CTRL_REG, 0x0);
    
    rc = shaBasicTest(SHARefData, testAddr, 1, 0);

shaRefTest_out:

    return rc;

}  /* shaRefTest */


int
shaChainHash(u32 m1Addr, u32 m1Blocks, u32 m2Addr, u32 m2Blocks, u32 result[], 
             u32 reset)
{

    SHA1Context sha;
    u8 swHash[20];
    u32 m1Result[5];

    int i, j, rc = SHA_ERROR_OK;


    busPrintf("%s: ChainHash: m1: 0x%08x, %d    m2: 0x%08x, %d",
        __FILE__, m1Addr, m1Blocks, m2Addr, m2Blocks);

    /* Merge two messages into one inBuf buffer for sofware hash */
    for (i=0; i < (m1Blocks*16); i++) {
        inBuf[i] = IO_READ(m1Addr+(i*4));
    }
    for (j=0; j < (m2Blocks*16); j++) {
        inBuf[i+j] = IO_READ(m2Addr+(j*4));
    }

#ifdef DEBUG_PRINT
    shaDumpMemory(m1Addr, m1Blocks);
    shaDumpMemory(m2Addr, m2Blocks);

    busPrintf("\n%s: Dumping input buffer:", __FILE__);
    for (i = 0; i < ((m1Blocks+m2Blocks)*16); i += 2) {
        busPrintf("\t[%3d]: 0x%08x\t[%3d]: 0x%08x", 
            i, inBuf[i], i+1, inBuf[i+1]);
    }
#endif
   
    /* Perform SHA operation with interrupt enabled */
    _SHA_Init(NULL);
    _SHA_Setup(m1Addr);
    _SHA_Hash(m1Blocks, 1);

    rc = _SHA_Wait4Done(m1Blocks*SHA_OP_TIME, 0);
    if (rc != SHA_ERROR_OK) {
        busPrintf("\n%s: (1) ERROR: Can't wait, rc=%d\n", __FILE__, rc);
        goto shaChainHash_out;
    }

    /* Fetch result for message */
    _SHA_GetResult(m1Result);

    /* Perform SW Hash */
    shaSwHash(&sha, inBuf, m1Blocks, swHash);

    for (i=0; i < 5; i++) {
        if (m1Result[i] != htonl(*((u32 *)(swHash+4*i)))) {
            rc = SHA_ERROR_UNKNOWN;
	    busPrintf("%s: (1) ERROR: HW=0x%08x != SW=BE(0x%08x)", 
                __FILE__, m1Result[i], htonl(*((u32 *)(swHash+4*i))));
	}
    }
      
    if (rc != SHA_ERROR_OK) {
        busPrintf("\n%s: SHA Chain Intermediate Test -> FAIL\n", __FILE__);
        goto shaChainHash_out;
    }
    
    if (reset) {
        _SHA_Init(m1Result);
    }

    busPrintf("\n%s: Continuing at addr(0x%08x) with numBlocks=%d", 
        __FILE__, m2Addr, m2Blocks);

    /* Setup SHA read pointer with second half of numBlocks and 
     * perform another SHA operation */
    _SHA_Setup(m2Addr);
    _SHA_Hash(m2Blocks, 1);

    rc = _SHA_Wait4Done(m2Blocks*SHA_OP_TIME, 0);
    if (rc != SHA_ERROR_OK) {
        busPrintf("\n%s: (2) ERROR: Can't wait, rc=%d\n", __FILE__, rc);
        goto shaChainHash_out;
    }

    /* Fetch result for 2nd half of numBlocks */
    _SHA_GetResult(result);

    rc = shaCheckRegValues(m2Addr, m2Blocks);
    if (rc != SHA_ERROR_OK) {
        goto shaChainHash_out;
    }

    /* Hash over both messages using software */
    shaSwHash(&sha, inBuf, m1Blocks+m2Blocks, swHash);

    for (i=0; i < 5; i++) {
        if (result[i] != htonl(*((u32 *)(swHash+4*i)))) {
	    rc = SHA_ERROR_UNKNOWN;
	    busPrintf("%s: (2) ERROR: HW=0x%08x != SW=BE(0x%08x)", 
                __FILE__, result[i], htonl(*((u32 *)(swHash+4*i))));
	}
    }

shaChainHash_out:

    return rc;

}  /* shaChainHash */


int
shaMultiBlockRefTest(u32 addr, u32 reset)
{
    u32 result[5], numBlocks;
    int i, rc = SHA_ERROR_OK;


    numBlocks = 2;

    /* Init memory with random data */
    for (i =0; i < 16*numBlocks; i++) {
        inBuf[i] = SHAMultiBlockRefData[i];
    }
    for (i = 0; i < 16*numBlocks; i++) {
         busWrt32(addr + 4*i, inBuf[i] );
    }

    /* Flush memory */
    ahbMemFlush(wb_iop);

    /* Invalidate AHM SHA RDB */
    IOP_InvalidateRDB(AHMRDBI_REG_SHA_RDBI_MASK);

    rc = shaChainHash(addr, 1, addr+64, 1, result, reset);
    if (rc != SHA_ERROR_OK) {
        goto shaMultiBlockRefTest_out;
    }

    for (i = 0; i < 5; i++) {
        if (result[i] != SHAMultiBlockRefHash2[i]) {
            rc = SHA_ERROR_UNKNOWN;
	    busPrintf("%s: MBRT: ERROR: HW=0x%08x != REF=0x%08x", 
                __FILE__, result[i], SHAMultiBlockRefHash2[i]);
        } 
    }

shaMultiBlockRefTest_out:

    return rc;

}  /* shaMultiBlockRefTest */

    
