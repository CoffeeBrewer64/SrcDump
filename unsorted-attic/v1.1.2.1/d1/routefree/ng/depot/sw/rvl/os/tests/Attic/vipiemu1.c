a0 50
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

#include "hw.h"
#include "ios.h"
#include "ioslibc.h"

#define STACK_SIZE 1024
const u8 _initStack[STACK_SIZE];
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = 10;

#define MY_IO_WRITE(offset, val) \
                  { IOSError rc; \
                    rc = IOS_ACRRegWrite((offset)-ACR_PROT_REGS_BASE, val); \
                    if (rc != IOS_ERROR_OK) printf("Write to %08x failed", offset); }

static void
__acr_reg_test(void)
{
    u32 reg = busRd32(ACR_PROT_REGS_BASE + GPIIOPEN_OFFSET);

    printf("Test to write VI_SDA (0x%08x) and VI_SCL(0x%08x) bits to offset: 0x%08x\n", GPIO_VI_SDA, GPIO_VI_SCL, GPIIOPEN_OFFSET);

    printf("gpiiopen register before clear = 0x%08x\n", reg);
    reg &= ~(GPIO_VI_SDA | GPIO_VI_SCL);
    MY_IO_WRITE(ACR_PROT_REGS_BASE + GPIIOPEN_OFFSET, reg);
    reg = busRd32(ACR_PROT_REGS_BASE + GPIIOPEN_OFFSET);
    printf("gpiiopen register after clear = 0x%08x\n", reg);
    
    reg |= (GPIO_VI_SDA | GPIO_VI_SCL);
    MY_IO_WRITE(ACR_PROT_REGS_BASE + GPIIOPEN_OFFSET, reg);
    reg = busRd32(ACR_PROT_REGS_BASE + GPIIOPEN_OFFSET);
    printf("gpiiopen register after set = 0x%08x\n", reg);
}

void
main(u32 arg)
{
    __acr_reg_test();
    return;
}
