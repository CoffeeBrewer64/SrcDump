/***
 *
 *  Trade secret of ATI Technologies Inc.
 *  Unpublished work, Copyright 2005 ATI Technologies Inc.
 *
 *  All rights reserved.  This notice is intended as a precaution against
 *  inadvertent publication and does not imply publication or any waiver
 *  of confidentiality.  The year included in the foregoing notice is the
 *  year of creation of the work.
 *
 ***/
#include <iostypes.h>
#include <ios.h>
#include <iop.h>
#include <ioslibc.h>

#include <ahb_fdl_defs.h>
#include <mem_reg.h>
#include "sys.h"

#define PHYS_TO_PROTECTED(a) ((a) | AHB_TRUSTED_OFFSET)
#define ACR_PROT_REGS_BASE PHYS_TO_PROTECTED(ACR_REGS_BASE)

#define MAX_FLUSH_COUNT 100
#define PROT_MEM_REG(i) (PHYS_TO_PROTECTED(MEM_REGS_BASE + i*2))

enum sysClkSpeed_e sysSpeed = enhancedclockspeed;
enum sysMode_e sysMode = enhancedmode;

u32 chipid_major, chipid_minor;

#define pllCfg_243_R 0x1a
#define pllCfg_243_F 0x3cb
#define pllCfg_243_O 0x8
#define pllCfg_162_R 0x1a
#define pllCfg_162_F 0x287
#define pllCfg_162_O 0x8
pllCfg sysPllCfg = {pllCfg_243_R, pllCfg_243_F, pllCfg_243_O}; // Default to 243 MHz (enhanced mode) settings
#define pllCfg_972_R 0x0
#define pllCfg_972_F 0x47
#define pllCfg_972_O 0x04
pllCfg ddrPllCfg = {pllCfg_972_R, pllCfg_972_F, pllCfg_972_O}; // Default to 972 MHz settings

static selCfg ddrSelCfg = {6, 4, 2};

// Add defines for software workarounds here
#define WORKAROUND_CF12_DELAY_AHMREG 0
#define WORKAROUND_523_CF12_STOP_PREFETCH 1
#define WORKAROUND_ENABLE_530_HSPLIT_FORCE 0
#define WORKAROUND_CF12_1CYC_INTER_DMA 0

#if WORKAROUND_CF12_DELAY_AHMREG
//
// CF 1.2 workaround.  All AHM register accesses delayed by 
// 40 clocks to make sure previous write finished
// real system would also disable interrupts
//
static void
safe2AccessAHMReg(void)
{
    if (chipid_major == 0) {
        busDelay(40);
    }
}
#endif // WORKAROUND_CF12_DELAY_AHMREG

/* It is OK to call initSWWorkArounds() many times */
void
initSWWorkArounds(void)
{

#if WORKAROUND_ENABLE_530_HSPLIT_FORCE
    u32 val;

    val = busRd32(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRSPARE1_OFFSET));
    // NOTE: Always leave HSPLIT bit (cpu[1]) for AHP off (to talk to AIP)
    // Need defines for bits!!
    ACRSPARE1_SET_CPU_FRC_HSPLIT(val, 0xd);
    ACRSPARE1_SET_DMA_FRC_HSPLIT(val, 0xfff);
    busWrt32(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRSPARE1_OFFSET), val);
#endif // WORKAROUND_ENABLE_530_HSPLIT_FORCE


#if WORKAROUND_523_CF12_STOP_PREFETCH

    // Turn off prefetch for all DMA_AHB clients.  No FDL defines for this!!!
    // Turn down prefetch for all CPU_DMA clients
    if (chipid_major == 0) {
        busWrt32(PHYS_TO_PROTECTED(AHM_BASE + AHMPREFC), 0x0);
    }
#endif // WORKAROUND_523_CF12_STOP_DMA_PREFETCH

#if WORKAROUND_CF12_1CYC_INTER_DMA
    if (chipid_major == 0) {
        u32 arb_dma_cfg = busRd32(ACR_PROT_REGS_BASE + ACRARBCFGDMA_OFFSET);
        if (!ACRARBCFGDMA_GET_DELAYEN(arb_dma_cfg)) { /* if it set then OK */
            ACRARBCFGDMA_SET_DELAYEN(arb_dma_cfg, 1); /* else set it to 1 */
            ACRARBCFGDMA_SET_DELAYCNT(arb_dma_cfg, 0); /* 1 cycle delay */
            busWrt32(ACR_PROT_REGS_BASE + ACRARBCFGDMA_OFFSET, arb_dma_cfg);
        }
    }
#endif
}

/*
 * Flush one of 4 memory clients on AHB side
 */
void ahbMemFlush(enum memAhbFlushGroup_e client)
{
    u16 bits = 0, ack;
    int i, gotack;

    // First map the client into one of 4 group clients
    switch (client) {
        case wb_iop:
        case wb_iod:
        case wb_bmc:
            client = wb_cpu;
            break;
        case wb_aes:
        case wb_sha:
        case wb_bmd:
            client = wb_dmaA;
            break;
        case wb_aim:
        case wb_ehc:
            client = wb_dmaB;
            break;
        case wb_fla:
        case wb_oh0:
        case wb_oh1:
        case wb_sd0:
        case wb_sd1:
            client = wb_dmaC;
            break;
        default:
            break;
    }

    switch (client) {
        case wb_cpu:
            bits = DDR_AHMFLUSH_S_CPU_MASK;
            break;
        case wb_dmaA:
            bits = DDR_AHMFLUSH_S_DMA_MASK;
            break;
        case wb_dmaB:
            bits = DDR_AHMFLUSH_S_DMA0_MASK;
            break;
        case wb_dmaC:
            bits = DDR_AHMFLUSH_S_DMA1_MASK;
            break;
        case wb_all:
            bits = DDR_AHMFLUSH_S_CPU_MASK | DDR_AHMFLUSH_S_DMA_MASK | DDR_AHMFLUSH_S_DMA0_MASK | DDR_AHMFLUSH_S_DMA1_MASK;
            break;
        default:
            break;
    }

    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_AHMFLUSH*2), bits);

    gotack = 0;
    for (i = 0; i < MAX_FLUSH_COUNT; i++) {
        ack = busRd16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_AHMFLUSH_ACK*2));
        if ((ack ^ bits) == 0) {
            gotack = 1;
            break;
        }
        busDelay(10);
    }
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_AHMFLUSH*2), 0);
    if (gotack == 0) {
        busDbg("ERROR: ahbDDRFlush(0x%x) did not ack!!", bits);
    }
}

//
// Each AHB memory client has a read buffer that must be invalidated
// to maintain coherency between clients.  Just set the bit.  If it is
// set from a previous request, there is no race condition (HW).
// The bit gets cleared when next read associated with the buffer occurs
//
void
ahbMemRBInvalidate(enum memAhbReadBuffer_e buffer)
{
    u32 bit = 0, val;

    switch (buffer) {
        case rb_iod:
            bit = AHMRDBI_REG_IOPD_RDBI_MASK;
            break;

        case rb_ioi:
            bit = AHMRDBI_REG_IOPI_RDBI_MASK;
            break;

        case rb_aim:
            bit = AHMRDBI_REG_AHBEXIDI_RDBI_MASK;
            break;

        case rb_fla:
            bit = AHMRDBI_REG_FLASH_RDBI_MASK;
            break;

        case rb_aes:
            bit = AHMRDBI_REG_AES_RDBI_MASK;
            break;

        case rb_sha:
            bit = AHMRDBI_REG_SHA_RDBI_MASK;
            break;

        case rb_ehc:
            bit = AHMRDBI_REG_EHCI_RDBI_MASK;
            break;

        case rb_oh0:
            bit = AHMRDBI_REG_OHCI0_RDBI_MASK;
            break;

        case rb_oh1:
            bit = AHMRDBI_REG_OHCI1_RDBI_MASK;
            break;

        case rb_sd0:
            bit = AHMRDBI_REG_SDIO0_RDBI_MASK;
            break;

        case rb_sd1:
            bit = AHMRDBI_REG_SDIO1_RDBI_MASK;
            break;

        case rb_bmd:
            bit = AHMRDBI_REG_BMD_RDBI_MASK;
            break;

        case rb_bmc:
            bit = AHMRDBI_REG_BMC_RDBI_MASK;
            break;
    }

#if WORKAROUND_CF12_DELAY_AHMREG
    safe2AccessAHMReg();
#endif // WORKAROUND_CF12_DELAY_AHMREG
    val = busRd32(PHYS_TO_PROTECTED(AHM_BASE + AHMRDBI));
    busWrt32(PHYS_TO_PROTECTED(AHM_BASE + AHMRDBI), (val | bit));
}

/*
 * Bring the PPC out of reset.  Assumes protection bits and other
 * reset bits have already been configured to state needed by tests
 */
void
bootPPC()
{
    u32 rstReg, sysReg;
    u32 cycles;

    busDbg("Releasing PPC from RESET");
    // grab current reset bits, assert cpu HRESET and deassert SRESET, don't
    // assert the vegas reset bits
    rstReg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    ACRRSTCTRL_SET_CPURSTB(rstReg, 0);
    ACRRSTCTRL_SET_RSTB(rstReg, 1);
    ACRRSTCTRL_SET_CRSTB(rstReg, 1);
    ACRRSTCTRL_SET_RSTINB(rstReg, 1);

    // Sequence is:
    //    on vegas reset HRESET is asserted SRESET is deasserted
    //    assert SRESET
    //    wait for some time (PLL reset time to settle down)
    //    deassert SRESET and wait for PLL lock time
    //    deassert HRESET to allow Broadway to boot
    //
    //    for compatible booting, the sequence is slightly different:
    //    assert SRESET
    //    wait for some time (PLL reset time to settle down)
    //    switch vegas to FXCLK, delay for some number of cycles
    //    Set system-pll to compat (162)
    //    deassert SRESET
    //    reset deskew pll and wait for deskew pll lock time
    //    (this is really max of deskew and broadway pll lock times
    //    switch away from FXCLK
    //    deassert HRESET to allow Broadway to boot
    if (sysMode == enhancedmode) {
        ACRRSTCTRL_SET_CPUSRSTB(rstReg, 0);
        busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, rstReg);
        if (sysSpeed == enhancedclockspeed) {
            cycles = PPC_PLL_RESET_TIME / SYS_CLOCK_FAST_TIME;
        } else {
            cycles = PPC_PLL_RESET_TIME / SYS_CLOCK_SLOW_TIME;
        }
        busDelay(cycles);

        ACRRSTCTRL_SET_CPUSRSTB(rstReg, 1);
        busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, rstReg);
        if (sysSpeed == enhancedclockspeed) {
            cycles = PPC_PLL_LOCK_TIME / SYS_CLOCK_FAST_TIME;
        } else {
            cycles = PPC_PLL_LOCK_TIME / SYS_CLOCK_SLOW_TIME;
        }
        busDelay(cycles);

        ACRRSTCTRL_SET_CPURSTB(rstReg, 1);
        busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, rstReg);
    } else {
        /* compat mode */
        ACRRSTCTRL_SET_CPUSRSTB(rstReg, 0);
        busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, rstReg);
        cycles = PPC_PLL_RESET_TIME / SYS_CLOCK_SLOW_TIME;
        busDelay(cycles);

        sysReg = busRd32(ACR_PROT_REGS_BASE + ACRSYSCTRL_OFFSET);
        ACRSYSCTRL_SET_USE_FXCLK(sysReg, 1);
        busWrt32(ACR_PROT_REGS_BASE + ACRSYSCTRL_OFFSET, sysReg);
        busDelay(FXCLK_SWITCH_DELAY_CYCLES);

        ACRRSTCTRL_SET_RSTB_DSKPLL(rstReg, 0);
        busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, rstReg);
        busDelay(DSK_RESET_DELAY_CYCLES);

        ACRSYSCTRL_SET_SYSPLL_CMPTBL(sysReg, 1);
        busWrt32(ACR_PROT_REGS_BASE + ACRSYSCTRL_OFFSET, sysReg);

        ACRRSTCTRL_SET_CPUSRSTB(rstReg, 1);
        busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, rstReg);

        ACRRSTCTRL_SET_RSTB_DSKPLL(rstReg, 1);
        busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, rstReg);
        cycles = DSK_PLL_LOCK_TIME / SYS_CLOCK_SLOW_TIME;
        busDelay(cycles);

        ACRSYSCTRL_SET_USE_FXCLK(sysReg, 0);
        busWrt32(ACR_PROT_REGS_BASE + ACRSYSCTRL_OFFSET, sysReg);

        initMemBlock();

        ACRRSTCTRL_SET_CPURSTB(rstReg, 1);
        busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, rstReg);
    }

}

/*
 * After reset (in non-debug mode), many blocks are held in reset.  Enable
 * all the blocks except the PPC's HRESET and SRESET.  The "|=" is a hack
 * but with new resets being added, this code doesn't have to change.
 */
void
enableChipBlocks()
{
    u32 reg; 

    reg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    reg |= ~(ACRRSTCTRL_PAD0_MASK | ACRRSTCTRL_CPUSRSTB_MASK |
            ACRRSTCTRL_CPURSTB_MASK);
    busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, reg);
}

/* 
 * Reset the PLLs.  For most PLLs the sequence is to de-assert 
 * RSTB, wait some, and then de-assert NCKLB.  Batch them 
 * all together to only wait once.  Also set FASTEN and ENSAT
 * for some unknown reason (secret of TCI).
 */
void
initPLLs()
{
    u32 reg; 
    u32 cycles;

    // Reset the PLLs and also make the ENSAT and FASTEN 1 for faster sims
    //SYSPLL
    reg = busRd32(ACR_PROT_REGS_BASE + ACRPLLSYSEXT_OFFSET);
    ACRPLLSYSEXT_SET_SYSPLL_FASTEN(reg, 1);
    ACRPLLSYSEXT_SET_SYSPLL_ENSAT(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRPLLSYSEXT_OFFSET, reg);

    // Select fixed clock before switching SYSPLL frequency
    reg = busRd32(ACR_PROT_REGS_BASE + ACRSYSCTRL_OFFSET);
    ACRSYSCTRL_SET_USE_FXCLK(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRSYSCTRL_OFFSET, reg);
    busDelay(50);
    reg = busRd32(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRRSTCTRL_OFFSET));
    ACRRSTCTRL_SET_RSTB_DSKPLL(reg, 0);
    busWrt32(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRRSTCTRL_OFFSET), reg);
    busDelay(50);
    reg = busRd32(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRRSTCTRL_OFFSET));
    ACRRSTCTRL_SET_NLCKB_SYSPLL(reg, 0);
    busWrt32(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRRSTCTRL_OFFSET), reg);
    busDelay(150);
    reg = busRd32(ACR_PROT_REGS_BASE + ACRPLLSYS_OFFSET);
    ACRPLLSYS_SET_SYSPLL_CLKR(reg, sysPllCfg.clkR);
    ACRPLLSYS_SET_SYSPLL_CLKF(reg, sysPllCfg.clkF);
    ACRPLLSYS_SET_SYSPLL_CLKO_0(reg, sysPllCfg.clkO);
    busWrt32(ACR_PROT_REGS_BASE + ACRPLLSYS_OFFSET, reg);
    reg = busRd32(ACR_PROT_REGS_BASE + ACRPLLSYSEXT_OFFSET);
    ACRPLLSYSEXT_SET_SYSPLL_CLKO_1(reg, sysPllCfg.clkO);
    busWrt32(ACR_PROT_REGS_BASE + ACRPLLSYSEXT_OFFSET, reg);
    // Need to reset the SYSPLL in order to change the Feedback, Reference and Output divider value
    busDelay(150);
    reg = busRd32(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRRSTCTRL_OFFSET));
    ACRRSTCTRL_SET_RSTB_SYSPLL(reg, 0);
    busWrt32(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRRSTCTRL_OFFSET), reg);
    busDelay(100);
    ACRRSTCTRL_SET_RSTB_SYSPLL(reg, 1);
    busWrt32(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRRSTCTRL_OFFSET), reg);
    busDelay(50);
    ACRRSTCTRL_SET_NLCKB_SYSPLL(reg, 1);
    busWrt32(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRRSTCTRL_OFFSET), reg);
    busDelay(50);
    ACRRSTCTRL_SET_RSTB_DSKPLL(reg, 1);
    busWrt32(PHYS_TO_PROTECTED(ACR_REGS_BASE + ACRRSTCTRL_OFFSET), reg);

    // Insert this register write here to take advantage of the 2 busDelays before enabling the DDR PLL.
    reg = busRd32(ACR_PROT_REGS_BASE + ACRPLLDDR_OFFSET);
    ACRPLLDDR_SET_DDRPLL_CLKR(reg, ddrPllCfg.clkR);
    ACRPLLDDR_SET_DDRPLL_CLKF(reg, ddrPllCfg.clkF);
    ACRPLLDDR_SET_DDRPLL_CLKO_0(reg, ddrPllCfg.clkO);
    busWrt32(ACR_PROT_REGS_BASE + ACRPLLDDR_OFFSET, reg);

    busDelay(50);
    // Select SYSPLL clock
    reg = busRd32(ACR_PROT_REGS_BASE + ACRSYSCTRL_OFFSET);
    ACRSYSCTRL_SET_USE_FXCLK(reg, 0);
    ACRSYSCTRL_SET_SYSPLL_CMPTBL(reg, 0);
    busWrt32(ACR_PROT_REGS_BASE + ACRSYSCTRL_OFFSET, reg);
    busDelay(50);

    //DDRPLL
    reg = busRd32(ACR_PROT_REGS_BASE + ACRPLLDDREXT_OFFSET);
    ACRPLLDDREXT_SET_DDRPLL_NLCKB(reg, 0);
    ACRPLLDDREXT_SET_DDRPLL_RSTB(reg, 1);
    ACRPLLDDREXT_SET_DDRPLL_FASTEN(reg, 1);
    ACRPLLDDREXT_SET_DDRPLL_ENSAT(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRPLLDDREXT_OFFSET, reg);

    //VIPLL
    reg = busRd32(ACR_PROT_REGS_BASE + ACRPLLVIEXT_OFFSET);
    ACRPLLVIEXT_SET_VIPLL_NLCKB(reg, 0);
    ACRPLLVIEXT_SET_VIPLL_RSTB(reg, 1);
    ACRPLLVIEXT_SET_VIPLL_FASTEN(reg, 1);
    ACRPLLVIEXT_SET_VIPLL_ENSAT(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRPLLVIEXT_OFFSET, reg);

    //AIPLL
    reg = busRd32(ACR_PROT_REGS_BASE + ACRPLLAIEXT_OFFSET);
    ACRPLLAIEXT_SET_AIPLL_NLCKB(reg, 0);
    ACRPLLAIEXT_SET_AIPLL_RSTB(reg, 1);
    ACRPLLAIEXT_SET_AIPLL_FASTEN(reg, 1);
    ACRPLLAIEXT_SET_AIPLL_ENSAT(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRPLLAIEXT_OFFSET, reg);

    //USBPLL
    reg = busRd32(ACR_PROT_REGS_BASE + ACRPLLUSBEXT_OFFSET);
    ACRPLLUSBEXT_SET_USBPLL_NLCKB(reg, 0);
    ACRPLLUSBEXT_SET_USBPLL_RSTB(reg, 1);
    ACRPLLUSBEXT_SET_USBPLL_FASTEN(reg, 1);
    ACRPLLUSBEXT_SET_USBPLL_ENSAT(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRPLLUSBEXT_OFFSET, reg);

    // Wait for the PLLs to lock.
    // This is set to a very small value. We may need to increase this delay to get the PLLs to work.
    // The spec is 500 divided reference clocks. Usually, this value would be 500 reference clocks.
    cycles = 50;
    busDelay(cycles);

    // Now switch to using the output of the PLL
    //DDRPLL
    reg = busRd32(ACR_PROT_REGS_BASE + ACRPLLDDREXT_OFFSET);
    ACRPLLDDREXT_SET_DDRPLL_NLCKB(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRPLLDDREXT_OFFSET, reg);

    //VIPLL
    reg = busRd32(ACR_PROT_REGS_BASE + ACRPLLVIEXT_OFFSET);
    ACRPLLVIEXT_SET_VIPLL_NLCKB(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRPLLVIEXT_OFFSET, reg);

    //AIPLL
    reg = busRd32(ACR_PROT_REGS_BASE + ACRPLLAIEXT_OFFSET);
    ACRPLLAIEXT_SET_AIPLL_NLCKB(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRPLLAIEXT_OFFSET, reg);

    //USBPLL
    reg = busRd32(ACR_PROT_REGS_BASE + ACRPLLUSBEXT_OFFSET);
    ACRPLLUSBEXT_SET_USBPLL_NLCKB(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRPLLUSBEXT_OFFSET, reg);

}

void
setSysClockSpeed(enum sysClkSpeed_e speed)
{
    sysSpeed = speed;
    if (sysSpeed == compatclockspeed) {
        sysPllCfg.clkR = pllCfg_162_R;
        sysPllCfg.clkF = pllCfg_162_F;
        sysPllCfg.clkO = pllCfg_162_O;
    } else if (sysSpeed == enhancedclockspeed) {
        sysPllCfg.clkR = pllCfg_243_R;
        sysPllCfg.clkF = pllCfg_243_F;
        sysPllCfg.clkO = pllCfg_243_O;
    }
}

void
setSysMode(enum sysMode_e mode)
{
    sysMode = mode;
    if (mode == compatmode) {
        setSysClockSpeed(compatclockspeed);
    }
}

void
setSysPllCfg(pllCfg newCfg)
{
    sysPllCfg = newCfg;
}

void
setDDRPllCfg(pllCfg newCfg)
{
    ddrPllCfg = newCfg;
}

void
setDDRSelCfg(selCfg newCfg)
{
    ddrSelCfg = newCfg;
}

/* 
 * initialize ACRCOMPAT
 */
void
initCompatSettings()
{
    u32 reg;

    if (sysMode == enhancedmode) {
        reg = busRd32(ACR_PROT_REGS_BASE + ACRCOMPAT_OFFSET);
        ACRCOMPAT_SET_EXI_USE_BOOTREG(reg, 0);
        ACRCOMPAT_SET_EXI_NEW_DIV_EN(reg, 0);
        busWrt32(ACR_PROT_REGS_BASE + ACRCOMPAT_OFFSET, reg);
    } else {
        reg = busRd32(ACR_PROT_REGS_BASE + ACRCOMPAT_OFFSET);
        ACRCOMPAT_SET_PI_DEEP3(reg, 0);
        ACRCOMPAT_SET_PI_AHB_DEC_EN(reg, 0);
        ACRCOMPAT_SET_PI_AHB_INT_EN(reg, 0);
        ACRCOMPAT_SET_PI_EXP_ADDR(reg, 0);
        ACRCOMPAT_SET_PI_STR_EN(reg, 1);
        ACRCOMPAT_SET_PI_MEMRSTB_EN(reg, 1);
        ACRCOMPAT_SET_PI_DIRSTB_EN(reg, 1);
        ACRCOMPAT_SET_AI_48K_CLK(reg, 0);
        ACRCOMPAT_SET_AI_CLK_FIX(reg, 0);
        ACRCOMPAT_SET_SI_PRG_DIV_EN(reg, 0);
        ACRCOMPAT_SET_EXI_NEW_DIV_EN(reg, 0);
        ACRCOMPAT_SET_EXI_EXP_ADDR(reg, 0);
        ACRCOMPAT_SET_DI_EXP_ADDR(reg, 0);
        ACRCOMPAT_SET_CP_EXP_ADDR(reg, 0);
        ACRCOMPAT_SET_TC_EXP_ADDR(reg, 0);
        ACRCOMPAT_SET_DSP_NEW_MEM(reg, 0);
        ACRCOMPAT_SET_DSP_EXP_ADDR(reg, 0);
        ACRCOMPAT_SET_PE_EXP_ADDR(reg, 0);
        ACRCOMPAT_SET_VI_EXP_ADDR(reg, 0);
        ACRCOMPAT_SET_EXI_BOOTREG_RWEN(reg, 0);
        ACRCOMPAT_SET_EXI_USE_BOOTREG(reg, 0);
        ACRCOMPAT_SET_DI_NODVDRD_EN(reg, 0);
        ACRCOMPAT_SET_PAD0(reg, 0);
        busWrt32(ACR_PROT_REGS_BASE + ACRCOMPAT_OFFSET, reg);
    }
}

/*
 * For verification and bringup, the system should allow access by PPC and
 * iop user access.  The POR values do this except for a few special areas.
 */
void
initSecuritySettings()
{
    u32 reg; 

    reg = busRd32(ACR_PROT_REGS_BASE + ACRSRNPROT_OFFSET);
    ACRSRNPROT_SET_AHPEN(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRSRNPROT_OFFSET, reg);
}

void
bistRegWrite(u16 addr, u16 val)
{
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_BIST_ADDR*2), addr);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_BIST_DATA*2), val);
}

void
seqRegWrite(u16 addr, u16 val)
{
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_SEQ_ADDR*2), addr);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_SEQ_DATA*2), val);
}

/* 
 * initialize mem
 */
static void 
resetMem(void)
{
    u32 reg;
    // Check to see if mem is already out of reset (and this is a reinitialization)
    reg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    if (ACRRSTCTRL_GET_RSTB_MEM(reg)) {
        // Disable CKE.
        seqRegWrite(DDR_SEQ_CKEEN, 0);
        // Put GDDR back into reset, wait for much longer in real world
        seqRegWrite(DDR_SEQ_RSTB, 0);
        busDelay(15);
    }
    // (re)assert reset to mem block
    reg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    ACRRSTCTRL_SET_RSTB_MEM(reg, 0);
    busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, reg);

    // Take control over pi_mem_memrstb, mux set to ACR control not PI
    reg = busRd32(ACR_PROT_REGS_BASE + ACRCOMPAT_OFFSET);
    ACRCOMPAT_SET_PI_MEMRSTB_EN(reg, 0);
    busWrt32(ACR_PROT_REGS_BASE + ACRCOMPAT_OFFSET, reg);
}

static void
resetNapa(void)
{
    // Assert pi_memrstb (NAPA reset)
    u32 reg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    ACRRSTCTRL_SET_RSTB_MEMRSTB(reg, 0);
    busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, reg);
}

static void
enableMem(void)
{
    u32 reg;
    // Disable reset to the mem block so it can be programmed
    reg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    ACRRSTCTRL_SET_RSTB_MEM(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, reg);
    busDelay(100);
}

void
initNapa(void)
{
    resetMem();
    resetNapa();
    enableMem();
}

static void
__initDDR(void)
{
    u32 reg;
    u32 ddr_compat;
    // Force a sequencer reset, but leave output pins in force
    // power-up condition
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_COMPAT*2), 
            DDR_COMPAT_S_SEQFORCE_MASK | 
            DDR_COMPAT_S_SEQRESET_MASK);
    busDelay(10);
    ddr_compat = DDR_COMPAT_S_SEQFORCE_MASK;
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_COMPAT*2), ddr_compat);
    busDelay(10);

    if (sysMode == compatmode) {
        ddr_compat |= DDR_COMPAT_S_COMPAT_MASK;
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_COMPAT*2), ddr_compat);
    }

    // Force a manual npl sync
    seqRegWrite(DDR_SEQ_SYNC, 0x0); 

    // For TCINECUX6DDRDLLA1
    //
    // 0 <= f0 <= f2
    // 0 <= f1 <= f2
    // 40 <= f2 <= 255
    // rdqs_delay0 = 65ps + ddr_clk_per * ( (f0 + 34)/(f2) )
    // rdqs_delay1 = 65ps + ddr_clk_per * ( (f1 + 34)/(f2) )
    //
    // f0==0, f1=156 500ps delay with 2ns ddr_clk
    //
    // SADJ0 SADJ1 (f0 and f1 reset to 0)
    // 
    // RDQS DLL delay madj (f2)
    seqRegWrite(DDR_SEQ_MADJL, (156 << 8) | (156));
    seqRegWrite(DDR_SEQ_MADJH, (156 << 8) | (156));

    // Reset RDQS DLLs bit-10
    // unistr for gddr bit-8
    // data write on falling yclk bit-2
    //
    seqRegWrite(DDR_SEQ_PAD1, 0x0504); 
    // supposed to wait 1000ns min for DLL reset
    busDelay(10);
    seqRegWrite(DDR_SEQ_PAD1, 0x0104); 
    busDelay(10);

    // Force another manual npl sync now that sync clocks are running
    seqRegWrite(DDR_SEQ_SYNC, 0x0); 

    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_COLMSK*2), 0x01FF);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ROWMSK*2), 0x0FFF);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_BANKMSK*2), 0x0007);
    if (sysMode == compatmode) {
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_RANKSEL*2), 7);
    } else {
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_RANKSEL*2), 1);
    }
    busWrt16(PROT_MEM_REG(DDR_COLSEL),  ddrSelCfg.colSel);
    busWrt16(PROT_MEM_REG(DDR_ROWSEL),  ddrSelCfg.rowSel);
    busWrt16(PROT_MEM_REG(DDR_BANKSEL), ddrSelCfg.bankSel);

    // Turn on read coherency check for PI, CPUAHM, ACC, and three
    // DMAAHM quques.  Turn on low and high priority writes.
    // Turn on low and high priority read queues, and enable wrmux
    // to bank queues.
    //
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_MISC*2), 0xeff);

    // sequencer FIFOs high water marks
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_SEQRD_HWM*2), 8);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_SEQWR_HWM*2), 12);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_SEQCMD_HWM*2), 24);

    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_MAXWR*2), 6);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_MINRD*2), 6);

    // threshold for write FIFOs to become a priority write source
    // for arbitration.  These FIFOs hold 8 entries.
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_CPUAHM_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_DMAAHM_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_DMAAHM0_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_DMAAHM1_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_PI_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_PE_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_IO_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_DSP_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ACC_WR_T*2), 5);

    seqRegWrite(DDR_SEQ_TRCDR, 7);
    seqRegWrite(DDR_SEQ_TRCDW, 4);
    seqRegWrite(DDR_SEQ_TCL, 7);        // 6 for s
    seqRegWrite(DDR_SEQ_TRRD, 4);
    seqRegWrite(DDR_SEQ_TFAW, 23);
    seqRegWrite(DDR_SEQ_TRFC, 26);
    seqRegWrite(DDR_SEQ_TRC, 21);

    seqRegWrite(DDR_SEQ_TRDWR, 10);
    seqRegWrite(DDR_SEQ_TWRRD, 11);     // 10 for s
    seqRegWrite(DDR_SEQ_TR2R, 6);

    seqRegWrite(DDR_SEQ_RDPR, 19);
    seqRegWrite(DDR_SEQ_WRPR, 25);

    seqRegWrite(DDR_SEQ_QSOE0, 0xfc00); // f000 for s
    seqRegWrite(DDR_SEQ_QSOE1, 0x001f); // 007f for s
    seqRegWrite(DDR_SEQ_QSOE2, 0);
    seqRegWrite(DDR_SEQ_QSOE3, 0);

    seqRegWrite(DDR_SEQ_ODTDYN, 0);
    seqRegWrite(DDR_SEQ_ODTON, 0);

    seqRegWrite(DDR_SEQ_TWL, 2);        // 3 for s
    seqRegWrite(DDR_SEQ_RRL, 12);
    seqRegWrite(DDR_SEQ_NPLRD, 10);     // RRL-2

    // seqRegWrite(DDR_SEQ_NPLCONF, 4);    // Enable NPL sync on refresh
    // Enable bit to holdoff cke deassertion in refresh period is met
    //
    seqRegWrite(DDR_SEQ_NPLCONF, 0xc);  // Enable NPL sync on refresh
    seqRegWrite(DDR_SEQ_BANK4, 0);

    // Write some NPL registers
    //
    seqRegWrite(DDR_SEQ_RECEN0, 0x0fe0);    // receiver enable during reads
    // These are sloppy wrong, slamming on most of the pterm nterm pdrv and 
    // ndrv bits.
    seqRegWrite(DDR_SEQ_QSDEF, 1);
    seqRegWrite(DDR_SEQ_STR0, 0x7fff);
    seqRegWrite(DDR_SEQ_STR1, 0x7fff);
    seqRegWrite(DDR_SEQ_STR2, 0x7fff);
    seqRegWrite(DDR_SEQ_STR3, 0x01ff);
    seqRegWrite(DDR_SEQ_APAD0, 0xffff);
    seqRegWrite(DDR_SEQ_APAD1, 0xf);
    seqRegWrite(DDR_SEQ_CKPAD0, 0xffff);
    seqRegWrite(DDR_SEQ_CKPAD1, 0xf);
    seqRegWrite(DDR_SEQ_CMDPAD0, 0xffff);
    seqRegWrite(DDR_SEQ_CMDPAD1, 0xf);
    seqRegWrite(DDR_SEQ_DQPAD0, 0xf3cf);    // pterm nterm off for dq to see oe
    seqRegWrite(DDR_SEQ_DQPAD1, 0xf);
    seqRegWrite(DDR_SEQ_QSPAD0, 0xffff);
    seqRegWrite(DDR_SEQ_QSPAD1, 0xf);

    seqRegWrite(DDR_SEQ_BL4, 0);

    if (sysMode == compatmode) {
        seqRegWrite(DDR_SEQ_RANK2, 0);
    } else {
        seqRegWrite(DDR_SEQ_RANK2, 1);
    }
    seqRegWrite(DDR_SEQ_DDR2, 0);

    // Stop forcing pins in forced power-up condition, this will
    // start DDR reset
    //
    ddr_compat &= ~DDR_COMPAT_S_SEQFORCE_MASK;
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_COMPAT*2), ddr_compat);
    busDelay(10);

    // Take GDDR out of reset, wait for much longer in real world
    seqRegWrite(DDR_SEQ_RSTB, 1);
    busDelay(50);

    // Turn on CKE, ordering of reset deassertion and CKE assertion 
    // sets termination value in GDDR3 part, reorder as appropriate
    //
    seqRegWrite(DDR_SEQ_CKEEN, 1);

    busDelay(200);

    // precharge all
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXADDR*2), 0xFFFF);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0020);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0021);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0020);

    // EMRS
    // 20bb -> 20b3 
    // 2083 tWR = 7
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXADDR*2), 0x2083);

    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x22);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x23);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x22);

    if (sysMode != compatmode) {
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x24);
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x25);
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x24);
    }

    // for s reg = 0x0B00 | 0x0070;
    reg = 0x0900 | 0x0000;
    reg |= 0x0003;
    // MRS
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXADDR*2), reg);

    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x22);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x23);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x22);

    if (sysMode != compatmode) {
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x24);
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x25);
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x24);
    }

    busDelay(200);

    // precharge all
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXADDR*2), 0xFFFF);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0020);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0021);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0020);

    // refresh
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXADDR*2), 0xFFFF);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0002);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0003);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0002);

    // refresh
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXADDR*2), 0xFFFF);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0002);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0003);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0002);

    seqRegWrite(DDR_SEQ_IDLEST, 11);
    seqRegWrite(DDR_SEQ_CKEDYN, 1);
    seqRegWrite(DDR_SEQ_CKEEN, 0);

    // Turn on refresh
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_RFSH*2), 900);

    // deassert pi_memrstb
    reg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    ACRRSTCTRL_SET_RSTB_MEMRSTB(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, reg);

    if (sysMode == compatmode) {
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_REFRESH_IDX*2), 0x0000);
        EnableARAMEmu();
    } else {
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_REFRESH_IDX*2), 0x0080);
    }

}
void
initDDR(void)
{
    resetMem();
    enableMem();
    __initDDR();
}


void
initMemBlock()
{
    u32 reg;
    u32 ddr_compat;

    // Check to see if mem is already out of reset (and this is a reinitialization)
    reg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    if (ACRRSTCTRL_GET_RSTB_MEM(reg)) {
        // Disable CKE.
        seqRegWrite(DDR_SEQ_CKEEN, 0);
        // Put GDDR back into reset, wait for much longer in real world
        seqRegWrite(DDR_SEQ_RSTB, 0);
        busDelay(15);
    }
    // (re)assert reset to mem block
    reg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    ACRRSTCTRL_SET_RSTB_MEM(reg, 0);
    busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, reg);


    // Take control over pi_mem_memrstb, mux set to ACR control not PI
    reg = busRd32(ACR_PROT_REGS_BASE + ACRCOMPAT_OFFSET);
    ACRCOMPAT_SET_PI_MEMRSTB_EN(reg, 0);
    busWrt32(ACR_PROT_REGS_BASE + ACRCOMPAT_OFFSET, reg);

    // Assert pi_memrstb (NAPA reset)
    reg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    ACRRSTCTRL_SET_RSTB_MEMRSTB(reg, 0);
    busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, reg);

    // Disable reset to the mem block so it can be programmed
    reg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    ACRRSTCTRL_SET_RSTB_MEM(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, reg);

    busDelay(100);

    // Force a sequencer reset, but leave output pins in force
    // power-up condition
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_COMPAT*2), 
            DDR_COMPAT_S_SEQFORCE_MASK | 
            DDR_COMPAT_S_SEQRESET_MASK);
    busDelay(10);
    ddr_compat = DDR_COMPAT_S_SEQFORCE_MASK;
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_COMPAT*2), ddr_compat);
    busDelay(10);

    if (sysMode == compatmode) {
        ddr_compat |= DDR_COMPAT_S_COMPAT_MASK;
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_COMPAT*2), ddr_compat);
    }

    // Force a manual npl sync
    seqRegWrite(DDR_SEQ_SYNC, 0x0); 

    // For TCINECUX6DDRDLLA1
    //
    // 0 <= f0 <= f2
    // 0 <= f1 <= f2
    // 40 <= f2 <= 255
    // rdqs_delay0 = 65ps + ddr_clk_per * ( (f0 + 34)/(f2) )
    // rdqs_delay1 = 65ps + ddr_clk_per * ( (f1 + 34)/(f2) )
    //
    // f0==0, f1=156 500ps delay with 2ns ddr_clk
    //
    // SADJ0 SADJ1 (f0 and f1 reset to 0)
    // 
    // RDQS DLL delay madj (f2)
    seqRegWrite(DDR_SEQ_MADJL, (156 << 8) | (156));
    seqRegWrite(DDR_SEQ_MADJH, (156 << 8) | (156));

    // Reset RDQS DLLs bit-10
    // unistr for gddr bit-8
    // data write on falling yclk bit-2
    //
    seqRegWrite(DDR_SEQ_PAD1, 0x0504); 
    // supposed to wait 1000ns min for DLL reset
    busDelay(10);
    seqRegWrite(DDR_SEQ_PAD1, 0x0104); 
    busDelay(10);

    // Force another manual npl sync now that sync clocks are running
    seqRegWrite(DDR_SEQ_SYNC, 0x0); 

    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_COLMSK*2), 0x01FF);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ROWMSK*2), 0x0FFF);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_BANKMSK*2), 0x0007);
    if (sysMode == compatmode) {
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_RANKSEL*2), 7);
    } else {
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_RANKSEL*2), 1);
    }
    busWrt16(PROT_MEM_REG(DDR_COLSEL),  ddrSelCfg.colSel);
    busWrt16(PROT_MEM_REG(DDR_ROWSEL),  ddrSelCfg.rowSel);
    busWrt16(PROT_MEM_REG(DDR_BANKSEL), ddrSelCfg.bankSel);

    // Turn on read coherency check for PI, CPUAHM, ACC, and three
    // DMAAHM quques.  Turn on low and high priority writes.
    // Turn on low and high priority read queues, and enable wrmux
    // to bank queues.
    //
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_MISC*2), 0xeff);

    // sequencer FIFOs high water marks
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_SEQRD_HWM*2), 8);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_SEQWR_HWM*2), 12);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_SEQCMD_HWM*2), 24);

    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_MAXWR*2), 6);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_MINRD*2), 6);

    // threshold for write FIFOs to become a priority write source
    // for arbitration.  These FIFOs hold 8 entries.
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_CPUAHM_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_DMAAHM_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_DMAAHM0_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_DMAAHM1_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_PI_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_PE_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_IO_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_DSP_WR_T*2), 5);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ACC_WR_T*2), 5);

    seqRegWrite(DDR_SEQ_TRCDR, 7);
    seqRegWrite(DDR_SEQ_TRCDW, 4);
    seqRegWrite(DDR_SEQ_TCL, 7);        // 6 for s
    seqRegWrite(DDR_SEQ_TRRD, 4);
    seqRegWrite(DDR_SEQ_TFAW, 23);
    seqRegWrite(DDR_SEQ_TRFC, 26);
    seqRegWrite(DDR_SEQ_TRC, 21);

    seqRegWrite(DDR_SEQ_TRDWR, 10);
    seqRegWrite(DDR_SEQ_TWRRD, 11);     // 10 for s
    seqRegWrite(DDR_SEQ_TR2R, 6);

    seqRegWrite(DDR_SEQ_RDPR, 19);
    seqRegWrite(DDR_SEQ_WRPR, 25);

    seqRegWrite(DDR_SEQ_QSOE0, 0xfc00); // f000 for s
    seqRegWrite(DDR_SEQ_QSOE1, 0x001f); // 007f for s
    seqRegWrite(DDR_SEQ_QSOE2, 0);
    seqRegWrite(DDR_SEQ_QSOE3, 0);

    seqRegWrite(DDR_SEQ_ODTDYN, 0);
    seqRegWrite(DDR_SEQ_ODTON, 0);

    seqRegWrite(DDR_SEQ_TWL, 2);        // 3 for s
    seqRegWrite(DDR_SEQ_RRL, 12);
    seqRegWrite(DDR_SEQ_NPLRD, 10);     // RRL-2

    // seqRegWrite(DDR_SEQ_NPLCONF, 4);    // Enable NPL sync on refresh
    // Enable bit to holdoff cke deassertion in refresh period is met
    //
    seqRegWrite(DDR_SEQ_NPLCONF, 0xc);  // Enable NPL sync on refresh
    seqRegWrite(DDR_SEQ_BANK4, 0);

    // Write some NPL registers
    //
    seqRegWrite(DDR_SEQ_RECEN0, 0x0fe0);    // receiver enable during reads
    // These are sloppy wrong, slamming on most of the pterm nterm pdrv and 
    // ndrv bits.
    seqRegWrite(DDR_SEQ_QSDEF, 1);
    seqRegWrite(DDR_SEQ_STR0, 0x7fff);
    seqRegWrite(DDR_SEQ_STR1, 0x7fff);
    seqRegWrite(DDR_SEQ_STR2, 0x7fff);
    seqRegWrite(DDR_SEQ_STR3, 0x01ff);
    seqRegWrite(DDR_SEQ_APAD0, 0xffff);
    seqRegWrite(DDR_SEQ_APAD1, 0xf);
    seqRegWrite(DDR_SEQ_CKPAD0, 0xffff);
    seqRegWrite(DDR_SEQ_CKPAD1, 0xf);
    seqRegWrite(DDR_SEQ_CMDPAD0, 0xffff);
    seqRegWrite(DDR_SEQ_CMDPAD1, 0xf);
    seqRegWrite(DDR_SEQ_DQPAD0, 0xf3cf);    // pterm nterm off for dq to see oe
    seqRegWrite(DDR_SEQ_DQPAD1, 0xf);
    seqRegWrite(DDR_SEQ_QSPAD0, 0xffff);
    seqRegWrite(DDR_SEQ_QSPAD1, 0xf);

    seqRegWrite(DDR_SEQ_BL4, 0);

    if (sysMode == compatmode) {
        seqRegWrite(DDR_SEQ_RANK2, 0);
    } else {
        seqRegWrite(DDR_SEQ_RANK2, 1);
    }
    seqRegWrite(DDR_SEQ_DDR2, 0);

    // Stop forcing pins in forced power-up condition, this will
    // start DDR reset
    //
    ddr_compat &= ~DDR_COMPAT_S_SEQFORCE_MASK;
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_COMPAT*2), ddr_compat);
    busDelay(10);

    // Take GDDR out of reset, wait for much longer in real world
    seqRegWrite(DDR_SEQ_RSTB, 1);
    busDelay(50);

    // Turn on CKE, ordering of reset deassertion and CKE assertion 
    // sets termination value in GDDR3 part, reorder as appropriate
    //
    seqRegWrite(DDR_SEQ_CKEEN, 1);

    busDelay(200);

    // precharge all
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXADDR*2), 0xFFFF);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0020);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0021);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0020);

    // EMRS
    // 20bb -> 20b3 
    // 2083 tWR = 7
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXADDR*2), 0x2083);

    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x22);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x23);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x22);

    if (sysMode != compatmode) {
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x24);
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x25);
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x24);
    }

    // for s reg = 0x0B00 | 0x0070;
    reg = 0x0900 | 0x0000;
    reg |= 0x0003;
    // MRS
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXADDR*2), reg);

    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x22);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x23);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x22);

    if (sysMode != compatmode) {
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x24);
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x25);
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x24);
    }

    busDelay(200);

    // precharge all
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXADDR*2), 0xFFFF);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0020);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0021);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0020);

    // refresh
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXADDR*2), 0xFFFF);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0002);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0003);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0002);

    // refresh
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXADDR*2), 0xFFFF);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0002);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0003);
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_ARB_EXCMD*2), 0x0002);

    seqRegWrite(DDR_SEQ_IDLEST, 11);
    seqRegWrite(DDR_SEQ_CKEDYN, 1);
    seqRegWrite(DDR_SEQ_CKEEN, 0);

    // Turn on refresh
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_RFSH*2), 900);

    // deassert pi_memrstb
    reg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    ACRRSTCTRL_SET_RSTB_MEMRSTB(reg, 1);
    busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, reg);

    if (sysMode == compatmode) {
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_REFRESH_IDX*2), 0x0000);
        EnableARAMEmu();
    } else {
        busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_REFRESH_IDX*2), 0x0080);
    }

}

void
EnableARAMEmu( void )
{
    int     aram_delaycnt = 2;

    busPrintf(" RUNNING ARAM EMU CODE ");
    busWrt16(PHYS_TO_PROTECTED(MEM_REGS_BASE + DDR_RFSH*2), 0x0000);


    // Speed up read return a little bit for aram emulation
    seqRegWrite(DDR_SEQ_RRL, 9);
    seqRegWrite(DDR_SEQ_NPLRD, 7);     // RRL-2

    seqRegWrite( DDR_SEQ_CKEEN, 1 );
    seqRegWrite( DDR_SEQ_CKEDYN, 0 );
    seqRegWrite( DDR_SEQ_WRPR, 6 );
    seqRegWrite( DDR_SEQ_WR2PR, 10 );
    seqRegWrite( DDR_SEQ_TRAS, 14 );
    seqRegWrite( DDR_SEQ_ARAM, 2 | (aram_delaycnt << 2) );
    seqRegWrite( DDR_SEQ_ARAM, 3 | (aram_delaycnt << 2) );
}

// Enable the Hardware to be able to run tests
void initChip()
{
    u32 val;

    // Set the clocks a running
    initPLLs();

    // now grab the revision id
    val = busRd32(ACR_PROT_REGS_BASE + ACRCHIPREVID_OFFSET);
    chipid_major = (val & 0x00f0) >> 4;
    chipid_minor = val & 0x000f;

    // Initialize mem block
    initMemBlock();

    enableChipBlocks();
    initCompatSettings();
    initSecuritySettings();
    initSWWorkArounds();
}
