
/* Adapted from ATI's sys.c */

#include <iostypes.h>
#include <ios.h>
#include <iop.h>
#include <ioslibc.h>

#include <ahb_fdl_defs.h>
#include <mem_reg.h>
#include "sys_int.h"
#include <sys.h>

static selCfg ddrSelCfg = {6, 4, 2};
pllCfg ddrPllCfg = {pllCfg_972_R, pllCfg_972_F, pllCfg_972_O}; // Default to 972 MHz settings
void
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
        enableARAMEmu();
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

inline void
setDDRPllCfg(pllCfg newCfg)
{
    ddrPllCfg = newCfg;
}

inline void
setDDRSelCfg(selCfg newCfg)
{
    ddrSelCfg = newCfg;
}
