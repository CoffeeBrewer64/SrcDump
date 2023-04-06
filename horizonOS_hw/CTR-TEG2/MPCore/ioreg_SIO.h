/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/MPCore/ioreg_SIO.h

  Copyright 2008 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
//
//  I was generated automatically, don't edit me directly!!!
//
#ifndef NN_HW_CTR_TEG2_MPCORE_IOREG_SIO_H_
#define NN_HW_CTR_TEG2_MPCORE_IOREG_SIO_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* SPI1CNT */

#define REG_SPI1CNT_OFFSET                                 0x160000
#define REG_SPI1CNT_ADDR                                   (HW_REG_BASE + REG_SPI1CNT_OFFSET)
#define reg_SIO_SPI1CNT                                    (*( REGType16v *) REG_SPI1CNT_ADDR)

/* SPI1D */

#define REG_SPI1D_OFFSET                                   0x160002
#define REG_SPI1D_ADDR                                     (HW_REG_BASE + REG_SPI1D_OFFSET)
#define reg_SIO_SPI1D                                      (*( REGType8v *) REG_SPI1D_ADDR)

/* SPI2CNT */

#define REG_SPI2CNT_OFFSET                                 0x142000
#define REG_SPI2CNT_ADDR                                   (HW_REG_BASE + REG_SPI2CNT_OFFSET)
#define reg_SIO_SPI2CNT                                    (*( REGType16v *) REG_SPI2CNT_ADDR)

/* SPI2D */

#define REG_SPI2D_OFFSET                                   0x142002
#define REG_SPI2D_ADDR                                     (HW_REG_BASE + REG_SPI2D_OFFSET)
#define reg_SIO_SPI2D                                      (*( REGType8v *) REG_SPI2D_ADDR)

/* SPI3CNT */

#define REG_SPI3CNT_OFFSET                                 0x143000
#define REG_SPI3CNT_ADDR                                   (HW_REG_BASE + REG_SPI3CNT_OFFSET)
#define reg_SIO_SPI3CNT                                    (*( REGType16v *) REG_SPI3CNT_ADDR)

/* SPI3D */

#define REG_SPI3D_OFFSET                                   0x143002
#define REG_SPI3D_ADDR                                     (HW_REG_BASE + REG_SPI3D_OFFSET)
#define reg_SIO_SPI3D                                      (*( REGType8v *) REG_SPI3D_ADDR)

/* I2C1_DAT */

#define REG_I2C1_DAT_OFFSET                                0x161000
#define REG_I2C1_DAT_ADDR                                  (HW_REG_BASE + REG_I2C1_DAT_OFFSET)
#define reg_SIO_I2C1_DAT                                   (*( REGType8v *) REG_I2C1_DAT_ADDR)

/* I2C1_CNT */

#define REG_I2C1_CNT_OFFSET                                0x161001
#define REG_I2C1_CNT_ADDR                                  (HW_REG_BASE + REG_I2C1_CNT_OFFSET)
#define reg_SIO_I2C1_CNT                                   (*( REGType8v *) REG_I2C1_CNT_ADDR)

/* I2C1_CNT_EX */

#define REG_I2C1_CNT_EX_OFFSET                             0x161002
#define REG_I2C1_CNT_EX_ADDR                               (HW_REG_BASE + REG_I2C1_CNT_EX_OFFSET)
#define reg_SIO_I2C1_CNT_EX                                (*( REGType16v *) REG_I2C1_CNT_EX_ADDR)

/* I2C1_SCL */

#define REG_I2C1_SCL_OFFSET                                0x161004
#define REG_I2C1_SCL_ADDR                                  (HW_REG_BASE + REG_I2C1_SCL_OFFSET)
#define reg_SIO_I2C1_SCL                                   (*( REGType16v *) REG_I2C1_SCL_ADDR)

/* I2C2_DAT */

#define REG_I2C2_DAT_OFFSET                                0x144000
#define REG_I2C2_DAT_ADDR                                  (HW_REG_BASE + REG_I2C2_DAT_OFFSET)
#define reg_SIO_I2C2_DAT                                   (*( REGType8v *) REG_I2C2_DAT_ADDR)

/* I2C2_CNT */

#define REG_I2C2_CNT_OFFSET                                0x144001
#define REG_I2C2_CNT_ADDR                                  (HW_REG_BASE + REG_I2C2_CNT_OFFSET)
#define reg_SIO_I2C2_CNT                                   (*( REGType8v *) REG_I2C2_CNT_ADDR)

/* I2C2_CNT_EX */

#define REG_I2C2_CNT_EX_OFFSET                             0x144002
#define REG_I2C2_CNT_EX_ADDR                               (HW_REG_BASE + REG_I2C2_CNT_EX_OFFSET)
#define reg_SIO_I2C2_CNT_EX                                (*( REGType16v *) REG_I2C2_CNT_EX_ADDR)

/* I2C2_SCL */

#define REG_I2C2_SCL_OFFSET                                0x144004
#define REG_I2C2_SCL_ADDR                                  (HW_REG_BASE + REG_I2C2_SCL_OFFSET)
#define reg_SIO_I2C2_SCL                                   (*( REGType16v *) REG_I2C2_SCL_ADDR)


/*
 * Definitions of Register fields
 */


/* SPI1CNT */

#define REG_SIO_SPI1CNT_E_SHIFT                            15
#define REG_SIO_SPI1CNT_E_SIZE                             1
#define REG_SIO_SPI1CNT_E_MASK                             0x8000

#define REG_SIO_SPI1CNT_I_SHIFT                            14
#define REG_SIO_SPI1CNT_I_SIZE                             1
#define REG_SIO_SPI1CNT_I_MASK                             0x4000

#define REG_SIO_SPI1CNT_MODE_SHIFT                         11
#define REG_SIO_SPI1CNT_MODE_SIZE                          1
#define REG_SIO_SPI1CNT_MODE_MASK                          0x0800

#define REG_SIO_SPI1CNT_CLKMODE_SHIFT                      10
#define REG_SIO_SPI1CNT_CLKMODE_SIZE                       1
#define REG_SIO_SPI1CNT_CLKMODE_MASK                       0x0400

#define REG_SIO_SPI1CNT_SEL_SHIFT                          8
#define REG_SIO_SPI1CNT_SEL_SIZE                           2
#define REG_SIO_SPI1CNT_SEL_MASK                           0x0300

#define REG_SIO_SPI1CNT_BUSY_SHIFT                         7
#define REG_SIO_SPI1CNT_BUSY_SIZE                          1
#define REG_SIO_SPI1CNT_BUSY_MASK                          0x0080

#define REG_SIO_SPI1CNT_BAUDRATE_SHIFT                     0
#define REG_SIO_SPI1CNT_BAUDRATE_SIZE                      3
#define REG_SIO_SPI1CNT_BAUDRATE_MASK                      0x0007

#ifndef SDK_ASM
#define REG_SIO_SPI1CNT_FIELD( e, i, mode, clkmode, sel, busy, baudrate ) \
    (u16)( \
    ((u32)(e) << REG_SIO_SPI1CNT_E_SHIFT) | \
    ((u32)(i) << REG_SIO_SPI1CNT_I_SHIFT) | \
    ((u32)(mode) << REG_SIO_SPI1CNT_MODE_SHIFT) | \
    ((u32)(clkmode) << REG_SIO_SPI1CNT_CLKMODE_SHIFT) | \
    ((u32)(sel) << REG_SIO_SPI1CNT_SEL_SHIFT) | \
    ((u32)(busy) << REG_SIO_SPI1CNT_BUSY_SHIFT) | \
    ((u32)(baudrate) << REG_SIO_SPI1CNT_BAUDRATE_SHIFT))
#endif


/* SPI1D */

/* SPI2CNT */

#define REG_SIO_SPI2CNT_E_SHIFT                            15
#define REG_SIO_SPI2CNT_E_SIZE                             1
#define REG_SIO_SPI2CNT_E_MASK                             0x8000

#define REG_SIO_SPI2CNT_I_SHIFT                            14
#define REG_SIO_SPI2CNT_I_SIZE                             1
#define REG_SIO_SPI2CNT_I_MASK                             0x4000

#define REG_SIO_SPI2CNT_MODE_SHIFT                         11
#define REG_SIO_SPI2CNT_MODE_SIZE                          1
#define REG_SIO_SPI2CNT_MODE_MASK                          0x0800

#define REG_SIO_SPI2CNT_CLKMODE_SHIFT                      10
#define REG_SIO_SPI2CNT_CLKMODE_SIZE                       1
#define REG_SIO_SPI2CNT_CLKMODE_MASK                       0x0400

#define REG_SIO_SPI2CNT_SEL_SHIFT                          8
#define REG_SIO_SPI2CNT_SEL_SIZE                           2
#define REG_SIO_SPI2CNT_SEL_MASK                           0x0300

#define REG_SIO_SPI2CNT_BUSY_SHIFT                         7
#define REG_SIO_SPI2CNT_BUSY_SIZE                          1
#define REG_SIO_SPI2CNT_BUSY_MASK                          0x0080

#define REG_SIO_SPI2CNT_BAUDRATE_SHIFT                     0
#define REG_SIO_SPI2CNT_BAUDRATE_SIZE                      3
#define REG_SIO_SPI2CNT_BAUDRATE_MASK                      0x0007

#ifndef SDK_ASM
#define REG_SIO_SPI2CNT_FIELD( e, i, mode, clkmode, sel, busy, baudrate ) \
    (u16)( \
    ((u32)(e) << REG_SIO_SPI2CNT_E_SHIFT) | \
    ((u32)(i) << REG_SIO_SPI2CNT_I_SHIFT) | \
    ((u32)(mode) << REG_SIO_SPI2CNT_MODE_SHIFT) | \
    ((u32)(clkmode) << REG_SIO_SPI2CNT_CLKMODE_SHIFT) | \
    ((u32)(sel) << REG_SIO_SPI2CNT_SEL_SHIFT) | \
    ((u32)(busy) << REG_SIO_SPI2CNT_BUSY_SHIFT) | \
    ((u32)(baudrate) << REG_SIO_SPI2CNT_BAUDRATE_SHIFT))
#endif


/* SPI2D */

/* SPI3CNT */

#define REG_SIO_SPI3CNT_E_SHIFT                            15
#define REG_SIO_SPI3CNT_E_SIZE                             1
#define REG_SIO_SPI3CNT_E_MASK                             0x8000

#define REG_SIO_SPI3CNT_I_SHIFT                            14
#define REG_SIO_SPI3CNT_I_SIZE                             1
#define REG_SIO_SPI3CNT_I_MASK                             0x4000

#define REG_SIO_SPI3CNT_MODE_SHIFT                         11
#define REG_SIO_SPI3CNT_MODE_SIZE                          1
#define REG_SIO_SPI3CNT_MODE_MASK                          0x0800

#define REG_SIO_SPI3CNT_CLKMODE_SHIFT                      10
#define REG_SIO_SPI3CNT_CLKMODE_SIZE                       1
#define REG_SIO_SPI3CNT_CLKMODE_MASK                       0x0400

#define REG_SIO_SPI3CNT_BUSY_SHIFT                         7
#define REG_SIO_SPI3CNT_BUSY_SIZE                          1
#define REG_SIO_SPI3CNT_BUSY_MASK                          0x0080

#define REG_SIO_SPI3CNT_BAUDRATE_SHIFT                     0
#define REG_SIO_SPI3CNT_BAUDRATE_SIZE                      3
#define REG_SIO_SPI3CNT_BAUDRATE_MASK                      0x0007

#ifndef SDK_ASM
#define REG_SIO_SPI3CNT_FIELD( e, i, mode, clkmode, busy, baudrate ) \
    (u16)( \
    ((u32)(e) << REG_SIO_SPI3CNT_E_SHIFT) | \
    ((u32)(i) << REG_SIO_SPI3CNT_I_SHIFT) | \
    ((u32)(mode) << REG_SIO_SPI3CNT_MODE_SHIFT) | \
    ((u32)(clkmode) << REG_SIO_SPI3CNT_CLKMODE_SHIFT) | \
    ((u32)(busy) << REG_SIO_SPI3CNT_BUSY_SHIFT) | \
    ((u32)(baudrate) << REG_SIO_SPI3CNT_BAUDRATE_SHIFT))
#endif


/* SPI3D */

/* I2C1_DAT */

/* I2C1_CNT */

#define REG_SIO_I2C1_CNT_E_SHIFT                           7
#define REG_SIO_I2C1_CNT_E_SIZE                            1
#define REG_SIO_I2C1_CNT_E_MASK                            0x80

#define REG_SIO_I2C1_CNT_I_SHIFT                           6
#define REG_SIO_I2C1_CNT_I_SIZE                            1
#define REG_SIO_I2C1_CNT_I_MASK                            0x40

#define REG_SIO_I2C1_CNT_RW_SHIFT                          5
#define REG_SIO_I2C1_CNT_RW_SIZE                           1
#define REG_SIO_I2C1_CNT_RW_MASK                           0x20

#define REG_SIO_I2C1_CNT_ACK_SHIFT                         4
#define REG_SIO_I2C1_CNT_ACK_SIZE                          1
#define REG_SIO_I2C1_CNT_ACK_MASK                          0x10

#define REG_SIO_I2C1_CNT_CNT_SHIFT                         3
#define REG_SIO_I2C1_CNT_CNT_SIZE                          3
#define REG_SIO_I2C1_CNT_CNT_MASK                          0x38

#define REG_SIO_I2C1_CNT_NT_SHIFT                          2
#define REG_SIO_I2C1_CNT_NT_SIZE                           1
#define REG_SIO_I2C1_CNT_NT_MASK                           0x04

#define REG_SIO_I2C1_CNT_START_SHIFT                       1
#define REG_SIO_I2C1_CNT_START_SIZE                        1
#define REG_SIO_I2C1_CNT_START_MASK                        0x02

#define REG_SIO_I2C1_CNT_STOP_SHIFT                        0
#define REG_SIO_I2C1_CNT_STOP_SIZE                         1
#define REG_SIO_I2C1_CNT_STOP_MASK                         0x01

#ifndef SDK_ASM
#define REG_SIO_I2C1_CNT_FIELD( e, i, rw, ack, cnt, nt, start, stop ) \
    (u8)( \
    ((u32)(e) << REG_SIO_I2C1_CNT_E_SHIFT) | \
    ((u32)(i) << REG_SIO_I2C1_CNT_I_SHIFT) | \
    ((u32)(rw) << REG_SIO_I2C1_CNT_RW_SHIFT) | \
    ((u32)(ack) << REG_SIO_I2C1_CNT_ACK_SHIFT) | \
    ((u32)(cnt) << REG_SIO_I2C1_CNT_CNT_SHIFT) | \
    ((u32)(nt) << REG_SIO_I2C1_CNT_NT_SHIFT) | \
    ((u32)(start) << REG_SIO_I2C1_CNT_START_SHIFT) | \
    ((u32)(stop) << REG_SIO_I2C1_CNT_STOP_SHIFT))
#endif


/* I2C1_CNT_EX */

#define REG_SIO_I2C1_CNT_EX_LGCY_SHIFT                     15
#define REG_SIO_I2C1_CNT_EX_LGCY_SIZE                      1
#define REG_SIO_I2C1_CNT_EX_LGCY_MASK                      0x8000

#define REG_SIO_I2C1_CNT_EX_WT_SHIFT                       1
#define REG_SIO_I2C1_CNT_EX_WT_SIZE                        1
#define REG_SIO_I2C1_CNT_EX_WT_MASK                        0x0002

#define REG_SIO_I2C1_CNT_EX_SCL_SHIFT                      0
#define REG_SIO_I2C1_CNT_EX_SCL_SIZE                       1
#define REG_SIO_I2C1_CNT_EX_SCL_MASK                       0x0001

#ifndef SDK_ASM
#define REG_SIO_I2C1_CNT_EX_FIELD( lgcy, wt, scl ) \
    (u16)( \
    ((u32)(lgcy) << REG_SIO_I2C1_CNT_EX_LGCY_SHIFT) | \
    ((u32)(wt) << REG_SIO_I2C1_CNT_EX_WT_SHIFT) | \
    ((u32)(scl) << REG_SIO_I2C1_CNT_EX_SCL_SHIFT))
#endif


/* I2C1_SCL */

#define REG_SIO_I2C1_SCL_HI_PRD_SHIFT                      8
#define REG_SIO_I2C1_SCL_HI_PRD_SIZE                       5
#define REG_SIO_I2C1_SCL_HI_PRD_MASK                       0x1f00

#define REG_SIO_I2C1_SCL_LO_PRD_SHIFT                      0
#define REG_SIO_I2C1_SCL_LO_PRD_SIZE                       6
#define REG_SIO_I2C1_SCL_LO_PRD_MASK                       0x003f

#ifndef SDK_ASM
#define REG_SIO_I2C1_SCL_FIELD( hi_prd, lo_prd ) \
    (u16)( \
    ((u32)(hi_prd) << REG_SIO_I2C1_SCL_HI_PRD_SHIFT) | \
    ((u32)(lo_prd) << REG_SIO_I2C1_SCL_LO_PRD_SHIFT))
#endif


/* I2C2_DAT */

/* I2C2_CNT */

#define REG_SIO_I2C2_CNT_E_SHIFT                           7
#define REG_SIO_I2C2_CNT_E_SIZE                            1
#define REG_SIO_I2C2_CNT_E_MASK                            0x80

#define REG_SIO_I2C2_CNT_I_SHIFT                           6
#define REG_SIO_I2C2_CNT_I_SIZE                            1
#define REG_SIO_I2C2_CNT_I_MASK                            0x40

#define REG_SIO_I2C2_CNT_RW_SHIFT                          5
#define REG_SIO_I2C2_CNT_RW_SIZE                           1
#define REG_SIO_I2C2_CNT_RW_MASK                           0x20

#define REG_SIO_I2C2_CNT_ACK_SHIFT                         4
#define REG_SIO_I2C2_CNT_ACK_SIZE                          1
#define REG_SIO_I2C2_CNT_ACK_MASK                          0x10

#define REG_SIO_I2C2_CNT_CNT_SHIFT                         3
#define REG_SIO_I2C2_CNT_CNT_SIZE                          3
#define REG_SIO_I2C2_CNT_CNT_MASK                          0x38

#define REG_SIO_I2C2_CNT_NT_SHIFT                          2
#define REG_SIO_I2C2_CNT_NT_SIZE                           1
#define REG_SIO_I2C2_CNT_NT_MASK                           0x04

#define REG_SIO_I2C2_CNT_START_SHIFT                       1
#define REG_SIO_I2C2_CNT_START_SIZE                        1
#define REG_SIO_I2C2_CNT_START_MASK                        0x02

#define REG_SIO_I2C2_CNT_STOP_SHIFT                        0
#define REG_SIO_I2C2_CNT_STOP_SIZE                         1
#define REG_SIO_I2C2_CNT_STOP_MASK                         0x01

#ifndef SDK_ASM
#define REG_SIO_I2C2_CNT_FIELD( e, i, rw, ack, cnt, nt, start, stop ) \
    (u8)( \
    ((u32)(e) << REG_SIO_I2C2_CNT_E_SHIFT) | \
    ((u32)(i) << REG_SIO_I2C2_CNT_I_SHIFT) | \
    ((u32)(rw) << REG_SIO_I2C2_CNT_RW_SHIFT) | \
    ((u32)(ack) << REG_SIO_I2C2_CNT_ACK_SHIFT) | \
    ((u32)(cnt) << REG_SIO_I2C2_CNT_CNT_SHIFT) | \
    ((u32)(nt) << REG_SIO_I2C2_CNT_NT_SHIFT) | \
    ((u32)(start) << REG_SIO_I2C2_CNT_START_SHIFT) | \
    ((u32)(stop) << REG_SIO_I2C2_CNT_STOP_SHIFT))
#endif


/* I2C2_CNT_EX */

#define REG_SIO_I2C2_CNT_EX_LGCY_SHIFT                     15
#define REG_SIO_I2C2_CNT_EX_LGCY_SIZE                      1
#define REG_SIO_I2C2_CNT_EX_LGCY_MASK                      0x8000

#define REG_SIO_I2C2_CNT_EX_WT_SHIFT                       1
#define REG_SIO_I2C2_CNT_EX_WT_SIZE                        1
#define REG_SIO_I2C2_CNT_EX_WT_MASK                        0x0002

#define REG_SIO_I2C2_CNT_EX_SCL_SHIFT                      0
#define REG_SIO_I2C2_CNT_EX_SCL_SIZE                       1
#define REG_SIO_I2C2_CNT_EX_SCL_MASK                       0x0001

#ifndef SDK_ASM
#define REG_SIO_I2C2_CNT_EX_FIELD( lgcy, wt, scl ) \
    (u16)( \
    ((u32)(lgcy) << REG_SIO_I2C2_CNT_EX_LGCY_SHIFT) | \
    ((u32)(wt) << REG_SIO_I2C2_CNT_EX_WT_SHIFT) | \
    ((u32)(scl) << REG_SIO_I2C2_CNT_EX_SCL_SHIFT))
#endif


/* I2C2_SCL */

#define REG_SIO_I2C2_SCL_HI_PRD_SHIFT                      8
#define REG_SIO_I2C2_SCL_HI_PRD_SIZE                       5
#define REG_SIO_I2C2_SCL_HI_PRD_MASK                       0x1f00

#define REG_SIO_I2C2_SCL_LO_PRD_SHIFT                      0
#define REG_SIO_I2C2_SCL_LO_PRD_SIZE                       6
#define REG_SIO_I2C2_SCL_LO_PRD_MASK                       0x003f

#ifndef SDK_ASM
#define REG_SIO_I2C2_SCL_FIELD( hi_prd, lo_prd ) \
    (u16)( \
    ((u32)(hi_prd) << REG_SIO_I2C2_SCL_HI_PRD_SHIFT) | \
    ((u32)(lo_prd) << REG_SIO_I2C2_SCL_LO_PRD_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_MPCORE_IOREG_SIO_H_ */
#endif
