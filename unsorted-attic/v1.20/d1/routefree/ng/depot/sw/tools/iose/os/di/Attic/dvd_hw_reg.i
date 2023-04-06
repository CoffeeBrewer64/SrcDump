#ident "$Id: dvd_hw_reg.i,v 1.19 2006/03/26 22:43:16 jprincen Exp $"
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
 * These functions provide a level of indirection to accessing the
 * DI registers.  This will probably be useful when migrating from
 * the IOS emulator to real hardware.
 */

#include <stdbool.h>
#include <stdlib.h>

#ifdef RVL
#include "stdint.h"
#include "ioslibc.h"
#include "iop.h"
#else
#include <stdio.h>
#include <stdint.h>
#endif

#include "debug.h"
#include "dvd_hw.h"

/*
 * Declarations for the DVD hardware interface registers
 */

/*
 * The base address of the DI registers is 0x0C006000.
 * (IO Specification p. 14)
 */
#ifdef EMULATOR
extern volatile uint32_t        DIStatus;               /* Offset 0x00 */
extern volatile uint32_t        DICoverReg;             /* Offset 0x04 */
extern volatile uint32_t        DICmdBuf[3];            /* Offset 0x08 */
extern volatile uint32_t        DIDmaDestAddr;          /* Offset 0x14 */
extern volatile uint32_t        DILength;               /* Offset 0x18 */
extern volatile uint32_t        DIControl;              /* Offset 0x1C */
extern volatile uint32_t        DIImmData;              /* Offset 0x20 */
/*
 * The DI Configuration Register is at offset 0x24.
 * It isn't used in the driver
 */
#else
#include "ahb_fdl_defs.h"
#define         DI_REG_BASE           0x0D006000  + AHB_TRUSTED_OFFSET
#define         DI_STATUS_ADDR        DI_REG_BASE + 0x0
#define         DI_COVER_ADDR         DI_REG_BASE + 0x4
#define         DI_CMD_BUF_0_ADDR     DI_REG_BASE + 0x8
#define         DI_CMD_BUF_1_ADDR     DI_REG_BASE + 0xC
#define         DI_CMD_BUF_2_ADDR     DI_REG_BASE + 0x10
#define         DI_DMA_DEST_ADDR      DI_REG_BASE + 0x14
#define         DI_LENGTH_ADDR        DI_REG_BASE + 0x18
#define         DI_CONTROL_ADDR       DI_REG_BASE + 0x1C
#define         DI_IMM_DATA_ADDR      DI_REG_BASE + 0x20

#define         BUS_ENABLE_MASK       0x00800000
#endif


/* -------------------------------------------------------------------- */

void diFatalError (const char *err_string) __attribute__((noreturn));

static inline uint32_t
readDIRegister(const uint32_t address )
{
    uint32_t    regValue;


    IOS_InvalidateRdb(IOS_RB_IOD);
    regValue = busRd32(address);

    return(regValue);

}
/* -------------------------------------------------------------------- */
static inline uint32_t
readDIStatus(void)
{
#ifdef EMULATOR
    return(DIStatus);
#else
    return (readDIRegister(DI_STATUS_ADDR));
#endif
}
/* -------------------------------------------------------------------- */
// Used only for debugging, because it never exits.
static inline uint32_t
readGoodDIStatus(void)
{
    uint32_t old_value, count, value;

    count = 0;
    value = (readDIRegister(DI_STATUS_ADDR));
    printf ("(readGoodDIStatus) Value is: 0x%x\n", value);
    old_value = value;
    IOS_SetThreadPriority(0, 1);
    while (1) {
        /*
        printf (".");
        if ((++count % 80) == 0) {
           printf ("\n");
        }
        */
        count++;
	value = (readDIRegister(DI_STATUS_ADDR));
        if ((value & DI_TRANS_COMPLETE_INTR_MASK) == 0) {
	    printf ("(readGoodDIStatus) Bad Value is: 0x%x\n", value);
            diFatalError("Bad Value");
        }
        /*
        if (old_value != value) {
	    printf ("(readGoodDIStatus) New Value is: 0x%x\n", value);
            old_value = value;
	}
	else {
            IOS_YieldThread();
	}
        */

    }
    return (value);
}
#ifdef notdef
#endif
/* -------------------------------------------------------------------- */
static inline uint32_t
readDICoverReg(void)
{
#ifdef EMULATOR
    return(DICoverReg);
#else
    return (readDIRegister(DI_COVER_ADDR));
#endif
}
/* -------------------------------------------------------------------- */
static inline uint32_t
readDICmdBuf0(void)
{
#ifdef EMULATOR
    return(DICmdBuf[0]);
#else
    return (readDIRegister(DI_CMD_BUF_0_ADDR));
#endif
}
/* -------------------------------------------------------------------- */
static inline uint32_t
readDICmdBuf1(void)
{
#ifdef EMULATOR
    return(DICmdBuf[1]);
#else
    return (readDIRegister(DI_CMD_BUF_1_ADDR));
#endif
}
/* -------------------------------------------------------------------- */
static inline uint32_t
readDICmdBuf2(void)
{
#ifdef EMULATOR
    return(DICmdBuf[2]);
#else
    return (readDIRegister(DI_CMD_BUF_2_ADDR));
#endif
}
/* -------------------------------------------------------------------- */
static inline uint32_t
readDIImmData(void)
{
#ifdef EMULATOR
    return(DIImmData);
#else
    return (readDIRegister(DI_IMM_DATA_ADDR));
#endif
}
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */

#define BUS_ENABLE_MASK 0x00800000
void diFatalError (const char *err_string) __attribute__((noreturn));

static inline void
writeDIRegister(const uint32_t address, const uint32_t value)
{
    uint32_t    regValue;

    busWrt32(address, value);
    IOS_FlushMem(IOS_WB_IOD);

    IOS_InvalidateRdb(IOS_RB_IOD);
    regValue = readDIRegister(address);

    if (regValue != value) {
        DPRINT4 (
        "(writeDIRegister) Warning: wrote value 0x%x to register addr %x, but value read is 0x%x\n",
         value, address, regValue);
        // diFatalError("DI register write failed");
    }
}
/* -------------------------------------------------------------------- */

static inline void
writeDIStatus(const uint32_t value)
{
#ifdef EMULATOR
    DIStatus = value;
#else
    writeDIRegister(DI_STATUS_ADDR, value);
#endif
}

/* -------------------------------------------------------------------- */

static inline void
writeDICoverReg(const uint32_t value)
{
#ifdef EMULATOR
    DICoverReg = value;
#else
    writeDIRegister(DI_COVER_ADDR, value);
#endif
}

/* -------------------------------------------------------------------- */
static inline void
writeDICmdBuf0(const uint32_t value)
{
#ifdef EMULATOR
    DICmdBuf[0] = value;
#else
    writeDIRegister(DI_CMD_BUF_0_ADDR, value);
#endif
}
/* -------------------------------------------------------------------- */
static inline void
writeDICmdBuf1(const uint32_t value)
{
#ifdef EMULATOR
    DICmdBuf[1] = value;
#else
    writeDIRegister(DI_CMD_BUF_1_ADDR, value);
#endif
}
/* -------------------------------------------------------------------- */

static inline void
writeDICmdBuf2(const uint32_t value)
{
#ifdef EMULATOR
    DICmdBuf[2] = value;
#else
    writeDIRegister(DI_CMD_BUF_2_ADDR, value);
#endif
}
/* -------------------------------------------------------------------- */

static inline void
writeDIDmaDestAddr(const uint32_t value)
{
#ifdef EMULATOR
    DIDmaDestAddr = value;
#else
    if ((value & 0x1f) != 0) {
        printf ("(writeDIDmaDestAddr) Writing non-32 byte aligned address to DMA dest register - exiting\n");
        exit(-1);
    }
    writeDIRegister(DI_DMA_DEST_ADDR, value);
#endif
}
/* -------------------------------------------------------------------- */

static inline void
writeDILength(const uint32_t value)
{
#ifdef EMULATOR
    DILength = value;
#else
    writeDIRegister(DI_LENGTH_ADDR, value);
#endif
}
/* -------------------------------------------------------------------- */

static inline void
writeDIControl(const uint32_t value)
{
#ifdef EMULATOR
    DIControl = value;
#else
    writeDIRegister(DI_CONTROL_ADDR, value);
#endif
}
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */

/*
 * ReadForWrite functions read the value from the register, then
 * mask to 0 the interrupt bits so that when written, the interrupt
 * is not inadvertently cleared
 */
static inline uint32_t
readDIStatusForWrite(void)
{
#ifdef EMULATOR
    return(DIStatus);
#else
    uint32_t    diStatus;

    diStatus = readDIRegister(DI_STATUS_ADDR);
    diStatus &= ~DI_STATUS_INTRS;
    return (diStatus);
#endif
}
/* -------------------------------------------------------------------- */
static inline uint32_t
readDICoverRegForWrite(void)
{
#ifdef EMULATOR
    return(DICoverReg);
#else
    uint32_t    diCover;
    diCover = readDIRegister(DI_COVER_ADDR);
    diCover &= ~DI_COVER_INTR;
    return (diCover);
#endif
}
/* -------------------------------------------------------------------- */
