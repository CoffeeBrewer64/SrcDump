#include <iostypes.h>
#include <ios.h>
#include <iop.h>
#include <ioslibc.h>

#include <ahb_fdl_defs.h>
#include <mem_reg.h>
#include "sys_int.h"
#include <sys.h>

void
resetNapa(void)
{
    // Assert pi_memrstb (NAPA reset)
    u32 reg = busRd32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET);
    ACRRSTCTRL_SET_RSTB_MEMRSTB(reg, 0);
    busWrt32(ACR_PROT_REGS_BASE + ACRRSTCTRL_OFFSET, reg);
}
void
initNapa(void)
{
    resetMem();
    resetNapa();
    enableMem();
}

