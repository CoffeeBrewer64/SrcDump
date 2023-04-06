#ident "$Id: dvd_hw_reg.h,v 1.2 2006/07/28 21:26:04 craig Exp $"
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

/*
 * Declarations for the DVD hardware interface registers
 */

/*
 * The base address of the DI registers is 0x0C006000.
 * (IO Specification p. 14)
 */
extern volatile u32        DIStatus;               /* Offset 0x00 */
extern volatile u32        DICoverReg;             /* Offset 0x04 */
extern volatile u32        DICmdBuf[3];            /* Offset 0x08 */
extern volatile u32        DIDmaDestAddr;          /* Offset 0x14 */
extern volatile u32        DILength;               /* Offset 0x18 */
extern volatile u32        DIControl;              /* Offset 0x1C */
extern volatile u32        DIImmData;              /* Offset 0x20 */
/*
 * The DI Configuration Register is at offset 0x24.
 * It isn't used in the driver
 */
#endif
