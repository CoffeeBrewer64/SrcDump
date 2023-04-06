/* Adapted from ATI's sys.c */

#include <iostypes.h>
#include <ios.h>
#include <iop.h>
#include <ioslibc.h>

#include <ahb_fdl_defs.h>
#include <mem_reg.h>
#include "sys_int.h"
#include <sys.h>

pllCfg sysPllCfg = {pllCfg_243_R, pllCfg_243_F, pllCfg_243_O}; // Default to 243 MHz (enhanced mode) settings
pllCfg ddrPllCfg = {pllCfg_972_R, pllCfg_972_F, pllCfg_972_O}; // Default to 972 MHz settings

inline void
setSysPllCfg(pllCfg newCfg)
{
    sysPllCfg = newCfg;
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
