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

#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include "diag.h"
#include "iop.h"
#include "aes_hal.h"
#include <ahb_fdl_defs.h>
#include <mem_reg.h>
#include <sys.h>



// #define DEBUG_PRINT  1

#ifdef DEBUG_PRINT
#define debugPrint(s, args...)     { printf(s, ## args); }
#else
#define debugPrint(s, ...)  (void)(0)
#endif

#define IS_SRAM_BASE(addr)   ((addr & 0xFFFF0000) == SRN_SRAM_BASE)

#if defined(USE_SRAM)
#define SRAM_SOURCE_ADDRESS	(SRN_SRAM_BASE+0xE000)
#else
#define SRAM_SOURCE_ADDRESS	(SRN_SRAM_BASE+0x0400)
#endif

#define NAPA_SOURCE_ADDRESS	(SPLASH_BASE+0x00000)
#define DDR_SOURCE_ADDRESS	(DDR_BASE+0x100000)


/* LED trace codes */
#define REASON_DMA_PASS		0x25
#define REASON_DMA_FAIL		0x26

#define SRAM_LOG_ADDR           (SRN_SRAM_BASE+0xFF80)


#ifdef STDALONE
#define STACK_SIZE              2048
const u8   _initStack[STACK_SIZE];
const u32  _initStackSize = sizeof(_initStack);
#endif


/* Test using different combinations of memory for src and dst addresses 
 *   0) SRAM,
 *   1) Napa,
 *   2) DDR,
 *
 *   0 -> 0, 0 -> 1, 0 -> 2
 *   1 -> 1, 1 -> 0, 1 -> 2
 *   2 -> 2, 2 -> 0, 2 -> 1
*/
#define SRAM_ID         0
#define NAPA_ID         1
#define DDR_ID          2

#define NUM_OF_TESTS	9
static u32 testSeq[NUM_OF_TESTS][2] = { /* {src, dst} */
    /* 0 */ {SRAM_ID, SRAM_ID},
            {SRAM_ID, NAPA_ID}, 
            {SRAM_ID, DDR_ID}, 
    /* 3 */ {NAPA_ID, NAPA_ID}, 
            {NAPA_ID, SRAM_ID}, 
            {NAPA_ID, DDR_ID}, 
    /* 6 */ {DDR_ID , DDR_ID}, 
            {DDR_ID , SRAM_ID}, 
            {DDR_ID , NAPA_ID}};


/* Each block contains 16 bytes - Test 64, 512, and 1024 blocks */
static u32 blockSize[3] = {64, 512, 1024};

/* This mask contains 0xFFFF0000 when the IOUEN bit is set in ACRSRNPROT reg */
static u32 sramFlipMask = 0;

/* Max time to wait = MAX_FLUSH_WAIT * 1 usec = 1 sec */
#define MAX_FLUSH_WAIT	1000000	


static unsigned int
readMemReg(unsigned int a)
{
    u32 v;
    v = busRd16(PHYS_TO_PROTECTED(MEM_REGS_BASE | a));

    // rdbf(IOS_RB_IOD); // bug692 workaround (IOD RDBI after AHM/MEM reg read)
    /* Do implicit invlidation */
    memcmp((u32 *)SPLASH_BASE, (u32 *)DDR_BASE, 256);

    return v;
}


/*
 * Flush one of 4 memory clients on AHB side
 */
static void flushAhbMem(int client)
{
    u32 bits = 0, ack;
    u32 i, gotack;

    // First map the client into one of 4 group clients
    switch (client) {
        case IOS_WB_IOP:
        case IOS_WB_IOD:
        case IOS_WB_BMC:
            client = IOS_WB_CPU;
            break;
        case IOS_WB_AES:
        case IOS_WB_SHA:
        case IOS_WB_BMD:
            client = IOS_WB_DMAA;
            break;
        case IOS_WB_AIM:
        case IOS_WB_EHCI:
            client = IOS_WB_DMAB;
            break;
        case IOS_WB_FLA:
        case IOS_WB_OHCI0:
        case IOS_WB_OHCI1:
        case IOS_WB_SD0:
        case IOS_WB_SD1:
            client = IOS_WB_DMAC;
            break;
        default:
            break;
    }

    switch (client) {
        case IOS_WB_CPU:
            bits = DDR_AHMFLUSH_S_CPU_MASK;
            break;
        case IOS_WB_DMAA:
            bits = DDR_AHMFLUSH_S_DMA_MASK;
            break;
        case IOS_WB_DMAB:
            bits = DDR_AHMFLUSH_S_DMA0_MASK;
            break;
        case IOS_WB_DMAC:
            bits = DDR_AHMFLUSH_S_DMA1_MASK;
            break;
        case IOS_WB_ALL:
            bits = DDR_AHMFLUSH_S_CPU_MASK | DDR_AHMFLUSH_S_DMA_MASK | DDR_AHMFLUSH_S_DMA0_MASK | DDR_AHMFLUSH_S_DMA1_MASK;
            break;
        default:
            break;
    }

    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_AHMFLUSH*2), bits);

    /* Wait for max of 1 sec and break out if ack bit is not set */
    gotack = 0;
    for (i = 0; i < MAX_FLUSH_WAIT; i++) {
	ack = readMemReg(DDR_AHMFLUSH_ACK*2);
        if ((ack ^ bits) == 0) {
            gotack = 1;
            break;
        }
        udelay(1);   /* Wait for 1 usec */
    }
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_AHMFLUSH*2), 0);
    if (gotack == 0) {
        // debugPrint("ERROR: ahbMemFlush(0x%x) did not ack!\n", bits);
    }
}


/* Assuming we're using ES 2.11 chips only */
static void enableSramAccess()
{

#if 0
    u32 reg;

    /* Enable access for SRON */
    reg = *(u32 *)((u32)(ACR_REGS_BASE+ACRSRNPROT_OFFSET+AHB_TRUSTED_OFFSET)); 
    reg = reg | (ACRSRNPROT_AESEN_MASK | ACRSRNPROT_SHAEN_MASK |
          ACRSRNPROT_FLAEN_MASK | ACRSRNPROT_IOUEN_MASK);
    *(u32 *)((u32)(ACR_REGS_BASE+ACRSRNPROT_OFFSET+AHB_TRUSTED_OFFSET)) = reg;
#endif

}


static int wait4Done(u32 timeout)
{
    int i, done, rc;
    u32 val;


    i = 0; 
    done = 0;
    rc = AES_ERROR_OK;


    /* Check to see if interrupt is enabled */
    val = busRd32(AES_CTRL_REG);

    while (!done) {
        val = busRd32(AES_CTRL_REG);
        if ((val & AES_CTRL_EXEC) == 0) {
            done = 1;
            debugPrint("Wait: Returned count=%d, CtrlReg(0x%08x)=0x%08x\n", 
                i, AES_CTRL_REG, val);
        }
        else {
            i++;
            if (i >= timeout) {
                done = 1;
                rc = AES_ERROR_TIMEOUT;
                debugPrint("\nWait: TIMEOUT [%d] CtrlReg=0x%08x\n", 
                    i, val);
                goto wait4Done_out;
            }
        }
    }

    /* Check for memory violation */
    val = busRd32(AES_CTRL_REG);
    if (val & AES_CTRL_MVIOL) {
        debugPrint("\nWait: Memory access violation: 0x%08x\n", 
            val);
        rc = AES_ERROR_ACCESS;
        goto wait4Done_out;
    }

    /* Check SIZE field - should be 0xfff after operation */
    if ((val & AES_CTRL_SIZE_MASK) != AES_CTRL_SIZE_MASK) {
        debugPrint("\nWait: Unexpected SIZE: 0x%08x, mask=0x%08x\n", 
            val, AES_CTRL_SIZE_MASK);
        rc = AES_ERROR_SIZE;
        goto wait4Done_out;
    }

    /* Flush memory */
    flushAhbMem(IOS_WB_AES);

#if 0
    /* Flush memory */
    ahbMemFlush(IOS_WB_AES);

    /* Invalidate AHM IOPD RDB */
    ahbMemRBInvalidate(IOS_RB_IOD);

    /* Invalidate AHM AES RDB */
    ahbMemRBInvalidate(IOS_RB_AES);
#endif

wait4Done_out:

    return rc;

}


static int doDma(u32 srcAddr, u32 dstAddr, u32 numBlocks)
{

    int rc;
    u32 val;


    val = 0;
    rc = AES_ERROR_OK;

    /* Setup up address registers */
    *(u32 *)(AES_RPTR_REG) = srcAddr;
    *(u32 *)(AES_WPTR_REG) = dstAddr;

    /* Program DMA */
    val = AES_CTRL_EXEC | (AES_CTRL_CMD(AES_DMA_CMD));
    val |= ((numBlocks-1) & AES_CTRL_SIZE_MASK);
    *(u32 *)(AES_CTRL_REG) = val;

    rc = wait4Done(numBlocks*AES_DMA_TIME);

    return rc;

}


static int dmaTest(u32 srcAddr, u32 dstAddr, u32 numBlocks)
{
    /* Block is number of 16-byte block */
    int i, len, rc = AES_ERROR_OK;
    u32 *src, *dst;


    len = numBlocks * 4;

    /* Initialize srcAddr with random data */
    /* We need to convert the SRAM address to 0xFFFF000 range since we
     * flip the IOUEN bit in the ACRSRNPROT register
     */
    src = (IS_SRAM_BASE(srcAddr))?(u32 *)(srcAddr|sramFlipMask):(u32 *)srcAddr;
    dst = (IS_SRAM_BASE(dstAddr))?(u32 *)(dstAddr|sramFlipMask):(u32 *)dstAddr;

    debugPrint("InitMem: src=0x%08x dst=0x%08x len=%d\n", src, dst, len);

    for (i=0; i < len; i++) {
        *src++ = (((i+1) << 16) | i);
        *dst++ = 0xdeadbeef;
    }

    /* Flush memory */
    flushAhbMem(IOS_WB_IOP);

#if 0
    /* Flush memory */
    ahbMemFlush(IOS_WB_IOP);

    /* Invalidate AHM AES RDB */
    ahbMemRBInvalidate(IOS_RB_AES);
#endif

    debugPrint("DMA: src=0x%08x dst=0x%08x numBlocks=%d\n",
        srcAddr, dstAddr, numBlocks);

    rc = doDma(srcAddr, dstAddr, numBlocks);
    if (rc != AES_ERROR_OK) {
        goto dmaTest_out;
    }

    /* We need to convert the SRAM address to 0xFFFF000 range since we
     * flip the IOUEN bit in the ACRSRNPROT register
     */
    src = (IS_SRAM_BASE(srcAddr))?(u32 *)(srcAddr|sramFlipMask):(u32 *)srcAddr;
    dst = (IS_SRAM_BASE(dstAddr))?(u32 *)(dstAddr|sramFlipMask):(u32 *)dstAddr;

    debugPrint("memcmp: src=0x%08x dst=0x%08x len=%d\n", src, dst, len);

    if (memcmp((u32 *)src, (u32 *)dst, len) != 0) {
        rc = AES_ERROR_UNKNOWN;
    }

dmaTest_out:

    return(rc);

}  /* dmaTest */



#ifdef STDALONE
int main(int argc, char *argv[])
#else
int doDmaTest()
#endif
{
    int i, j, rc = AES_ERROR_OK;
    u32 numBlocks, srcAddr, dstAddr;
    u32 srcIndx, dstIndx, dstBaseAddr;
    u32 t1, t2, failCount, baseAddr[3];


    debugPrint("\nStarting AES DMA tests...\n");
    t1 = *(u32 *)(SYS_TIMER_REG);

    /* Init defaults */
    failCount = 0;
    srcIndx = SRAM_ID;
    baseAddr[SRAM_ID] = SRAM_SOURCE_ADDRESS;
    baseAddr[NAPA_ID] = NAPA_SOURCE_ADDRESS;
    baseAddr[DDR_ID] = DDR_SOURCE_ADDRESS;

    /* Need to enabble the SRAM split fix bit in ES 2.11 */
    u32 val = *(u32 *)(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRSPARE1_OFFSET));
    val |= ACRSPARE1_SRAM_SPLIT_FIX_ENABLE_MASK;
    *(u32 *)(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRSPARE1_OFFSET)) = val;
 
    /* Allow AES, SHA, and Flash to access SRAM */
    enableSramAccess();
  
    val = *(u32 *)(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRSRNPROT_OFFSET));
    sramFlipMask = 0;
    if (val & ACRSRNPROT_IOUEN_MASK)
        sramFlipMask = 0xFFFF0000;

    for (j = 0; j < (u32)(sizeof(testSeq)/sizeof(testSeq[0])); j++) {
        /* Test size from 1-9 blocks first */
        srcIndx = testSeq[j][0];
        dstIndx = testSeq[j][1];

        srcAddr = baseAddr[srcIndx];
        dstBaseAddr = baseAddr[dstIndx];

        debugPrint("***** AES DMA: %d: Idx=(src=%d dst=%d), srcAddr=0x%08x, "
               "dstBase=0x%08x\n", j, srcIndx, dstIndx, srcAddr, dstBaseAddr);

        for (i = 0; i < (u32)(sizeof(blockSize)/sizeof(blockSize[0])); i++) {
            numBlocks = blockSize[i];

            if ((srcIndx != SRAM_ID) && (dstIndx == SRAM_ID))
                dstAddr = dstBaseAddr;
            else
                dstAddr = dstBaseAddr + (numBlocks*16);

            debugPrint("AES DMA: src=0x%08x dst=0x%08x blocks=%d\n", 
                      srcAddr, dstAddr, numBlocks);

            rc = dmaTest(srcAddr, dstAddr, numBlocks);
    
            if (rc != AES_ERROR_OK) {
                debugPrint("**** [%2d] Test -> FAIL (blocks=%d)\n", 
                    i, numBlocks);
                failCount++;
                outputLed(REASON_DMA_FAIL);
                *(u32 *)(SRAM_LOG_ADDR|sramFlipMask) = 0xDEADBEEF;
                *(u32 *)((SRAM_LOG_ADDR|sramFlipMask)+4) = REASON_DMA_FAIL;
                *(u32 *)((SRAM_LOG_ADDR|sramFlipMask)+8) = 0xDEADBEEF;
                while (1) {};
            }
            else {
                debugPrint("[%2d] Test -> PASS (blocks=%d)\n",i,numBlocks);
            }
        }  /* for */

    }  /* for */

    t2 = *(u32 *)(SYS_TIMER_REG);

    outputLed(REASON_DMA_PASS);
    *(u32 *)(SRAM_LOG_ADDR|sramFlipMask) = 0xDEADBEEF;
    *(u32 *)((SRAM_LOG_ADDR|sramFlipMask)+4) = REASON_DMA_PASS;
    *(u32 *)((SRAM_LOG_ADDR|sramFlipMask)+8) = t2-t1;
    *(u32 *)((SRAM_LOG_ADDR|sramFlipMask)+12) = 0xDEADBEEF;

    debugPrint("\nTotal ticks=%d, (start=%d, end=%d)", t2-t1, t1, t2);
    debugPrint("\n***** There are %d failed tests out of %d tests *****\n\n", 
        failCount, i*j);

    return rc;

}

