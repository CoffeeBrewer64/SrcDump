#ident "$Id: dvd_main.c,v 1.10 2006/03/31 20:00:04 craig Exp $"
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

/*
 * Program comments here
 * 
 */

#include "arm_stdint.h"

#include "ios.h"
#include "ioslibc.h"
// #include "rvl_iop.h" #include "ahb_fdl_defs.h"

#include "dvd_hw_reg.i"
#include "dvd_hw.h"
#include "dvd_command.h"

#define STACK_SIZE (128 * 1024)
const uint8_t  _initStack[STACK_SIZE];
const uint32_t _initStackSize = sizeof(_initStack);
const uint32_t _initPriority = 11;

void     dvd_driver();
uint32_t handleDiCommand(const diCommand_t* const diCommand, void *outputPtr);
uint32_t doRawDiskRead(uint8_t* const destAddr, const uint32_t length,
                       const uint32_t wordOffset);

#define BUS_ENABLE_MASK 0x00800000

static uint8_t guardBuf1[128];
static uint8_t transBuf[1024] __attribute__((aligned(32)));
static uint8_t guardBuf2[128];

int
main(int argc, char *argv[])
{
    DVDDiskID           diskId;
    diCommand_t         diCommand;
    uint32_t            retVal;

    printf ("Stack variable addr: 0x%x\n", (uint32_t) &diskId);

    guardBuf1[0] = (uint8_t) 'c';
    guardBuf2[0] = (uint8_t) 1;
    
#ifdef not_used
    uint32_t            reg;

    /* Code moved to driver */
    reg = busRd32(ACR_REGS_BASE + ACRCOMPAT_OFFSET + BUS_ENABLE_MASK);
    ACRCOMPAT_SET_PI_DIRSTB_EN(reg, 0);
    busWrt32(ACR_PROT_REGS_BASE + ACRCOMPAT_OFFSET + BUS_ENABLE_MASK, reg);

    /* Take needed blocks out of reset */
    reg = busRd32(ACR_REGS_BASE + ACRRSTCTRL_OFFSET + BUS_ENABLE_MASK);
    ACRRSTCTRL_SET_RSTB_IOPI(reg, 1);
    ACRRSTCTRL_SET_RSTB_IODI(reg, 1);
    busWrt32(ACR_REGS_BASE + ACRRSTCTRL_OFFSET + BUS_ENABLE_MASK, reg);


    /* Enable control over PI_IO */
    reg = busRd32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK);
    AIPPROT_SET_ENAHBIOPI(reg, 1);
    busWrt32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK, reg);
#endif
    
    IOS_FlushMem(IOS_WB_IOD);
    IOS_InvalidateRdb(IOS_RB_IOD);

    printf ("Initializing DVD driver\n");
    dvd_driver();
    printf ("Done initing DVD driver\n");

    printf ("Before read disk id; Status reg is: 0x%x\n", readDIStatus());

    diCommand.theCommand = DI_READ_DISK_ID_CMD;
    retVal = handleDiCommand(&diCommand, transBuf);
    printf ("Read disk ID command return val is: 0x%x\n", retVal);

    if (retVal != DI_ERR_NO_ERROR) {
        printf ("(dvd_main) Read disk ID failed - exiting\n");
        exit(1);
    }
    /*
    */


    retVal = doRawDiskRead(transBuf, 128, 0);
    printf ("doRawDiskRead  command return val is: 0x%x\n", retVal);
    if (retVal != DI_ERR_NO_ERROR) {
        printf ("(dvd_main) Read failed - exiting\n");
        exit(1);
    }

    printf ("Bytes read:\n");
    for (int i = 0; i < 16; i++) {
        printf (" 0x%x", transBuf[i]);
    }
    printf ("(dvd_main) Exiting normally (PASSED)\n");
    IOS_DestroyThread(0, NULL);
    exit(0);
}
