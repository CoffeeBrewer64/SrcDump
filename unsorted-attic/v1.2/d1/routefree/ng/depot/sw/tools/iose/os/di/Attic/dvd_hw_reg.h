#ident "$Id: dvd_hw_reg.h,v 1.1 2006/02/07 19:26:48 craig Exp $"
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

#ifndef DVD_HW_REG_H
#define DVD_HW_REG_H

#include <stdint.h>

/*
 * Declarations for the DVD hardware interface registers
 */

/*
 * The base address of the DI registers is 0x0C006000.
 * (IO Specification p. 14)
 */
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
#endif
