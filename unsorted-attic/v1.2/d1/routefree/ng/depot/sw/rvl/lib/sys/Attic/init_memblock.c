
/* Adapted from ATI's sys.c */

#include <iostypes.h>
#include <ios.h>
#include <iop.h>
#include <ioslibc.h>

#include <ahb_fdl_defs.h>
#include <mem_reg.h>
#include "sys_int.h"
#include <sys.h>

void
initMemBlock()
{
    resetMem();
    resetNapa();
    enableMem();
    __initDDR();
}
