/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TS/MPCore/ioreg_tspatch_SIO.h

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
#ifndef NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_SIO_H_
#define NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_SIO_H_

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

/* NSPI1_CNT */

#define REG_NSPI1_CNT_OFFSET                               0x160800
#define REG_NSPI1_CNT_ADDR                                 (HW_REG_BASE + REG_NSPI1_CNT_OFFSET)
#define reg_SIO_NSPI1_CNT                                  (*( REGType32v *) REG_NSPI1_CNT_ADDR)

/* NSPI1_CS */

#define REG_NSPI1_CS_OFFSET                                0x160804
#define REG_NSPI1_CS_ADDR                                  (HW_REG_BASE + REG_NSPI1_CS_OFFSET)
#define reg_SIO_NSPI1_CS                                   (*( REGType32v *) REG_NSPI1_CS_ADDR)

/* NSPI1_LEN */

#define REG_NSPI1_LEN_OFFSET                               0x160808
#define REG_NSPI1_LEN_ADDR                                 (HW_REG_BASE + REG_NSPI1_LEN_OFFSET)
#define reg_SIO_NSPI1_LEN                                  (*( REGType32v *) REG_NSPI1_LEN_ADDR)

/* NSPI1_DT */

#define REG_NSPI1_DT_OFFSET                                0x16080c
#define REG_NSPI1_DT_ADDR                                  (HW_REG_BASE + REG_NSPI1_DT_OFFSET)
#define reg_SIO_NSPI1_DT                                   (*( REGType32v *) REG_NSPI1_DT_ADDR)

/* NSPI1_DS */

#define REG_NSPI1_DS_OFFSET                                0x160810
#define REG_NSPI1_DS_ADDR                                  (HW_REG_BASE + REG_NSPI1_DS_OFFSET)
#define reg_SIO_NSPI1_DS                                   (*(const REGType32v *) REG_NSPI1_DS_ADDR)

/* NSPI1_AP */

#define REG_NSPI1_AP_OFFSET                                0x160814
#define REG_NSPI1_AP_ADDR                                  (HW_REG_BASE + REG_NSPI1_AP_OFFSET)
#define reg_SIO_NSPI1_AP                                   (*( REGType32v *) REG_NSPI1_AP_ADDR)

/* NSPI1_MASK */

#define REG_NSPI1_MASK_OFFSET                              0x160818
#define REG_NSPI1_MASK_ADDR                                (HW_REG_BASE + REG_NSPI1_MASK_OFFSET)
#define reg_SIO_NSPI1_MASK                                 (*( REGType32v *) REG_NSPI1_MASK_ADDR)

/* NSPI1_INTRS */

#define REG_NSPI1_INTRS_OFFSET                             0x16081c
#define REG_NSPI1_INTRS_ADDR                               (HW_REG_BASE + REG_NSPI1_INTRS_OFFSET)
#define reg_SIO_NSPI1_INTRS                                (*( REGType32v *) REG_NSPI1_INTRS_ADDR)

/* NSPI2_CNT */

#define REG_NSPI2_CNT_OFFSET                               0x142800
#define REG_NSPI2_CNT_ADDR                                 (HW_REG_BASE + REG_NSPI2_CNT_OFFSET)
#define reg_SIO_NSPI2_CNT                                  (*( REGType32v *) REG_NSPI2_CNT_ADDR)

/* NSPI2_CS */

#define REG_NSPI2_CS_OFFSET                                0x142804
#define REG_NSPI2_CS_ADDR                                  (HW_REG_BASE + REG_NSPI2_CS_OFFSET)
#define reg_SIO_NSPI2_CS                                   (*( REGType32v *) REG_NSPI2_CS_ADDR)

/* NSPI2_LEN */

#define REG_NSPI2_LEN_OFFSET                               0x142808
#define REG_NSPI2_LEN_ADDR                                 (HW_REG_BASE + REG_NSPI2_LEN_OFFSET)
#define reg_SIO_NSPI2_LEN                                  (*( REGType32v *) REG_NSPI2_LEN_ADDR)

/* NSPI2_DT */

#define REG_NSPI2_DT_OFFSET                                0x14280c
#define REG_NSPI2_DT_ADDR                                  (HW_REG_BASE + REG_NSPI2_DT_OFFSET)
#define reg_SIO_NSPI2_DT                                   (*( REGType32v *) REG_NSPI2_DT_ADDR)

/* NSPI2_DS */

#define REG_NSPI2_DS_OFFSET                                0x142810
#define REG_NSPI2_DS_ADDR                                  (HW_REG_BASE + REG_NSPI2_DS_OFFSET)
#define reg_SIO_NSPI2_DS                                   (*(const REGType32v *) REG_NSPI2_DS_ADDR)

/* NSPI2_AP */

#define REG_NSPI2_AP_OFFSET                                0x142814
#define REG_NSPI2_AP_ADDR                                  (HW_REG_BASE + REG_NSPI2_AP_OFFSET)
#define reg_SIO_NSPI2_AP                                   (*( REGType32v *) REG_NSPI2_AP_ADDR)

/* NSPI2_MASK */

#define REG_NSPI2_MASK_OFFSET                              0x142818
#define REG_NSPI2_MASK_ADDR                                (HW_REG_BASE + REG_NSPI2_MASK_OFFSET)
#define reg_SIO_NSPI2_MASK                                 (*( REGType32v *) REG_NSPI2_MASK_ADDR)

/* NSPI2_INTRS */

#define REG_NSPI2_INTRS_OFFSET                             0x14281c
#define REG_NSPI2_INTRS_ADDR                               (HW_REG_BASE + REG_NSPI2_INTRS_OFFSET)
#define reg_SIO_NSPI2_INTRS                                (*( REGType32v *) REG_NSPI2_INTRS_ADDR)

/* NSPI3_CNT */

#define REG_NSPI3_CNT_OFFSET                               0x143800
#define REG_NSPI3_CNT_ADDR                                 (HW_REG_BASE + REG_NSPI3_CNT_OFFSET)
#define reg_SIO_NSPI3_CNT                                  (*( REGType32v *) REG_NSPI3_CNT_ADDR)

/* NSPI3_CS */

#define REG_NSPI3_CS_OFFSET                                0x143804
#define REG_NSPI3_CS_ADDR                                  (HW_REG_BASE + REG_NSPI3_CS_OFFSET)
#define reg_SIO_NSPI3_CS                                   (*( REGType32v *) REG_NSPI3_CS_ADDR)

/* NSPI3_LEN */

#define REG_NSPI3_LEN_OFFSET                               0x143808
#define REG_NSPI3_LEN_ADDR                                 (HW_REG_BASE + REG_NSPI3_LEN_OFFSET)
#define reg_SIO_NSPI3_LEN                                  (*( REGType32v *) REG_NSPI3_LEN_ADDR)

/* NSPI3_DT */

#define REG_NSPI3_DT_OFFSET                                0x14380c
#define REG_NSPI3_DT_ADDR                                  (HW_REG_BASE + REG_NSPI3_DT_OFFSET)
#define reg_SIO_NSPI3_DT                                   (*( REGType32v *) REG_NSPI3_DT_ADDR)

/* NSPI3_DS */

#define REG_NSPI3_DS_OFFSET                                0x143810
#define REG_NSPI3_DS_ADDR                                  (HW_REG_BASE + REG_NSPI3_DS_OFFSET)
#define reg_SIO_NSPI3_DS                                   (*(const REGType32v *) REG_NSPI3_DS_ADDR)

/* NSPI3_AP */

#define REG_NSPI3_AP_OFFSET                                0x143814
#define REG_NSPI3_AP_ADDR                                  (HW_REG_BASE + REG_NSPI3_AP_OFFSET)
#define reg_SIO_NSPI3_AP                                   (*( REGType32v *) REG_NSPI3_AP_ADDR)

/* NSPI3_MASK */

#define REG_NSPI3_MASK_OFFSET                              0x143818
#define REG_NSPI3_MASK_ADDR                                (HW_REG_BASE + REG_NSPI3_MASK_OFFSET)
#define reg_SIO_NSPI3_MASK                                 (*( REGType32v *) REG_NSPI3_MASK_ADDR)

/* NSPI3_INTRS */

#define REG_NSPI3_INTRS_OFFSET                             0x14381c
#define REG_NSPI3_INTRS_ADDR                               (HW_REG_BASE + REG_NSPI3_INTRS_OFFSET)
#define reg_SIO_NSPI3_INTRS                                (*( REGType32v *) REG_NSPI3_INTRS_ADDR)

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

/* I2C3_DAT */

#define REG_I2C3_DAT_OFFSET                                0x148000
#define REG_I2C3_DAT_ADDR                                  (HW_REG_BASE + REG_I2C3_DAT_OFFSET)
#define reg_SIO_I2C3_DAT                                   (*( REGType8v *) REG_I2C3_DAT_ADDR)

/* I2C3_CNT */

#define REG_I2C3_CNT_OFFSET                                0x148001
#define REG_I2C3_CNT_ADDR                                  (HW_REG_BASE + REG_I2C3_CNT_OFFSET)
#define reg_SIO_I2C3_CNT                                   (*( REGType8v *) REG_I2C3_CNT_ADDR)

/* I2C3_CNT_EX */

#define REG_I2C3_CNT_EX_OFFSET                             0x148002
#define REG_I2C3_CNT_EX_ADDR                               (HW_REG_BASE + REG_I2C3_CNT_EX_OFFSET)
#define reg_SIO_I2C3_CNT_EX                                (*( REGType16v *) REG_I2C3_CNT_EX_ADDR)

/* I2C3_SCL */

#define REG_I2C3_SCL_OFFSET                                0x148004
#define REG_I2C3_SCL_ADDR                                  (HW_REG_BASE + REG_I2C3_SCL_OFFSET)
#define reg_SIO_I2C3_SCL                                   (*( REGType16v *) REG_I2C3_SCL_ADDR)


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

/* NSPI1_CNT */

#define REG_SIO_NSPI1_CNT_E_SHIFT                          15
#define REG_SIO_NSPI1_CNT_E_SIZE                           1
#define REG_SIO_NSPI1_CNT_E_MASK                           0x00008000

#define REG_SIO_NSPI1_CNT_STREAM_SHIFT                     13
#define REG_SIO_NSPI1_CNT_STREAM_SIZE                      1
#define REG_SIO_NSPI1_CNT_STREAM_MASK                      0x00002000

#define REG_SIO_NSPI1_CNT_MODE_SHIFT                       12
#define REG_SIO_NSPI1_CNT_MODE_SIZE                        1
#define REG_SIO_NSPI1_CNT_MODE_MASK                        0x00001000

#define REG_SIO_NSPI1_CNT_SEL_SHIFT                        6
#define REG_SIO_NSPI1_CNT_SEL_SIZE                         2
#define REG_SIO_NSPI1_CNT_SEL_MASK                         0x000000c0

#define REG_SIO_NSPI1_CNT_BAUDRATE_SHIFT                   0
#define REG_SIO_NSPI1_CNT_BAUDRATE_SIZE                    3
#define REG_SIO_NSPI1_CNT_BAUDRATE_MASK                    0x00000007

#ifndef SDK_ASM
#define REG_SIO_NSPI1_CNT_FIELD( e, stream, mode, sel, baudrate ) \
    (u32)( \
    ((u32)(e) << REG_SIO_NSPI1_CNT_E_SHIFT) | \
    ((u32)(stream) << REG_SIO_NSPI1_CNT_STREAM_SHIFT) | \
    ((u32)(mode) << REG_SIO_NSPI1_CNT_MODE_SHIFT) | \
    ((u32)(sel) << REG_SIO_NSPI1_CNT_SEL_SHIFT) | \
    ((u32)(baudrate) << REG_SIO_NSPI1_CNT_BAUDRATE_SHIFT))
#endif


/* NSPI1_CS */

#define REG_SIO_NSPI1_CS_CSB_SHIFT                         0
#define REG_SIO_NSPI1_CS_CSB_SIZE                          1
#define REG_SIO_NSPI1_CS_CSB_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_SIO_NSPI1_CS_FIELD( csb ) \
    (u32)( \
    ((u32)(csb) << REG_SIO_NSPI1_CS_CSB_SHIFT))
#endif


/* NSPI1_LEN */

#define REG_SIO_NSPI1_LEN_LEN_SHIFT                        0
#define REG_SIO_NSPI1_LEN_LEN_SIZE                         21
#define REG_SIO_NSPI1_LEN_LEN_MASK                         0x001fffff

#ifndef SDK_ASM
#define REG_SIO_NSPI1_LEN_FIELD( len ) \
    (u32)( \
    ((u32)(len) << REG_SIO_NSPI1_LEN_LEN_SHIFT))
#endif


/* NSPI1_DT */

#define REG_SIO_NSPI1_DT_DATA_SHIFT                        0
#define REG_SIO_NSPI1_DT_DATA_SIZE                         32
#define REG_SIO_NSPI1_DT_DATA_MASK                         0xffffffff

#ifndef SDK_ASM
#define REG_SIO_NSPI1_DT_FIELD( data ) \
    (u32)( \
    ((u32)(data) << REG_SIO_NSPI1_DT_DATA_SHIFT))
#endif


/* NSPI1_DS */

#define REG_SIO_NSPI1_DS_DBUSY_SHIFT                       0
#define REG_SIO_NSPI1_DS_DBUSY_SIZE                        1
#define REG_SIO_NSPI1_DS_DBUSY_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_SIO_NSPI1_DS_FIELD( dbusy ) \
    (u32)( \
    ((u32)(dbusy) << REG_SIO_NSPI1_DS_DBUSY_SHIFT))
#endif


/* NSPI1_AP */

#define REG_SIO_NSPI1_AP_CMD_SHIFT                         0
#define REG_SIO_NSPI1_AP_CMD_SIZE                          8
#define REG_SIO_NSPI1_AP_CMD_MASK                          0x000000ff

#define REG_SIO_NSPI1_AP_TIME_OUT_SHIFT                    16
#define REG_SIO_NSPI1_AP_TIME_OUT_SIZE                     4
#define REG_SIO_NSPI1_AP_TIME_OUT_MASK                     0x000f0000

#define REG_SIO_NSPI1_AP_RBFLAG_POS_SHIFT                  24
#define REG_SIO_NSPI1_AP_RBFLAG_POS_SIZE                   3
#define REG_SIO_NSPI1_AP_RBFLAG_POS_MASK                   0x07000000

#define REG_SIO_NSPI1_AP_SET_RBL_SHIFT                     30
#define REG_SIO_NSPI1_AP_SET_RBL_SIZE                      1
#define REG_SIO_NSPI1_AP_SET_RBL_MASK                      0x40000000

#define REG_SIO_NSPI1_AP_E_SHIFT                           31
#define REG_SIO_NSPI1_AP_E_SIZE                            1
#define REG_SIO_NSPI1_AP_E_MASK                            0x80000000

#ifndef SDK_ASM
#define REG_SIO_NSPI1_AP_FIELD( cmd, time_out, rbflag_pos, set_rbl, e ) \
    (u32)( \
    ((u32)(cmd) << REG_SIO_NSPI1_AP_CMD_SHIFT) | \
    ((u32)(time_out) << REG_SIO_NSPI1_AP_TIME_OUT_SHIFT) | \
    ((u32)(rbflag_pos) << REG_SIO_NSPI1_AP_RBFLAG_POS_SHIFT) | \
    ((u32)(set_rbl) << REG_SIO_NSPI1_AP_SET_RBL_SHIFT) | \
    ((u32)(e) << REG_SIO_NSPI1_AP_E_SHIFT))
#endif


/* NSPI1_MASK */

#define REG_SIO_NSPI1_MASK_INTR_SHIFT                      0
#define REG_SIO_NSPI1_MASK_INTR_SIZE                       3
#define REG_SIO_NSPI1_MASK_INTR_MASK                       0x00000007

#define REG_SIO_NSPI1_MASK_DREQ_SHIFT                      3
#define REG_SIO_NSPI1_MASK_DREQ_SIZE                       1
#define REG_SIO_NSPI1_MASK_DREQ_MASK                       0x00000008

#ifndef SDK_ASM
#define REG_SIO_NSPI1_MASK_FIELD( intr, dreq ) \
    (u32)( \
    ((u32)(intr) << REG_SIO_NSPI1_MASK_INTR_SHIFT) | \
    ((u32)(dreq) << REG_SIO_NSPI1_MASK_DREQ_SHIFT))
#endif


/* NSPI1_INTRS */

#define REG_SIO_NSPI1_INTRS_CAUSE_SHIFT                    0
#define REG_SIO_NSPI1_INTRS_CAUSE_SIZE                     3
#define REG_SIO_NSPI1_INTRS_CAUSE_MASK                     0x00000007

#ifndef SDK_ASM
#define REG_SIO_NSPI1_INTRS_FIELD( cause ) \
    (u32)( \
    ((u32)(cause) << REG_SIO_NSPI1_INTRS_CAUSE_SHIFT))
#endif


/* NSPI2_CNT */

#define REG_SIO_NSPI2_CNT_E_SHIFT                          15
#define REG_SIO_NSPI2_CNT_E_SIZE                           1
#define REG_SIO_NSPI2_CNT_E_MASK                           0x00008000

#define REG_SIO_NSPI2_CNT_STREAM_SHIFT                     13
#define REG_SIO_NSPI2_CNT_STREAM_SIZE                      1
#define REG_SIO_NSPI2_CNT_STREAM_MASK                      0x00002000

#define REG_SIO_NSPI2_CNT_MODE_SHIFT                       12
#define REG_SIO_NSPI2_CNT_MODE_SIZE                        1
#define REG_SIO_NSPI2_CNT_MODE_MASK                        0x00001000

#define REG_SIO_NSPI2_CNT_SEL_SHIFT                        6
#define REG_SIO_NSPI2_CNT_SEL_SIZE                         2
#define REG_SIO_NSPI2_CNT_SEL_MASK                         0x000000c0

#define REG_SIO_NSPI2_CNT_BAUDRATE_SHIFT                   0
#define REG_SIO_NSPI2_CNT_BAUDRATE_SIZE                    3
#define REG_SIO_NSPI2_CNT_BAUDRATE_MASK                    0x00000007

#ifndef SDK_ASM
#define REG_SIO_NSPI2_CNT_FIELD( e, stream, mode, sel, baudrate ) \
    (u32)( \
    ((u32)(e) << REG_SIO_NSPI2_CNT_E_SHIFT) | \
    ((u32)(stream) << REG_SIO_NSPI2_CNT_STREAM_SHIFT) | \
    ((u32)(mode) << REG_SIO_NSPI2_CNT_MODE_SHIFT) | \
    ((u32)(sel) << REG_SIO_NSPI2_CNT_SEL_SHIFT) | \
    ((u32)(baudrate) << REG_SIO_NSPI2_CNT_BAUDRATE_SHIFT))
#endif


/* NSPI2_CS */

#define REG_SIO_NSPI2_CS_CSB_SHIFT                         0
#define REG_SIO_NSPI2_CS_CSB_SIZE                          1
#define REG_SIO_NSPI2_CS_CSB_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_SIO_NSPI2_CS_FIELD( csb ) \
    (u32)( \
    ((u32)(csb) << REG_SIO_NSPI2_CS_CSB_SHIFT))
#endif


/* NSPI2_LEN */

#define REG_SIO_NSPI2_LEN_LEN_SHIFT                        0
#define REG_SIO_NSPI2_LEN_LEN_SIZE                         21
#define REG_SIO_NSPI2_LEN_LEN_MASK                         0x001fffff

#ifndef SDK_ASM
#define REG_SIO_NSPI2_LEN_FIELD( len ) \
    (u32)( \
    ((u32)(len) << REG_SIO_NSPI2_LEN_LEN_SHIFT))
#endif


/* NSPI2_DT */

#define REG_SIO_NSPI2_DT_DATA_SHIFT                        0
#define REG_SIO_NSPI2_DT_DATA_SIZE                         32
#define REG_SIO_NSPI2_DT_DATA_MASK                         0xffffffff

#ifndef SDK_ASM
#define REG_SIO_NSPI2_DT_FIELD( data ) \
    (u32)( \
    ((u32)(data) << REG_SIO_NSPI2_DT_DATA_SHIFT))
#endif


/* NSPI2_DS */

#define REG_SIO_NSPI2_DS_DBUSY_SHIFT                       0
#define REG_SIO_NSPI2_DS_DBUSY_SIZE                        1
#define REG_SIO_NSPI2_DS_DBUSY_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_SIO_NSPI2_DS_FIELD( dbusy ) \
    (u32)( \
    ((u32)(dbusy) << REG_SIO_NSPI2_DS_DBUSY_SHIFT))
#endif


/* NSPI2_AP */

#define REG_SIO_NSPI2_AP_CMD_SHIFT                         0
#define REG_SIO_NSPI2_AP_CMD_SIZE                          8
#define REG_SIO_NSPI2_AP_CMD_MASK                          0x000000ff

#define REG_SIO_NSPI2_AP_TIME_OUT_SHIFT                    16
#define REG_SIO_NSPI2_AP_TIME_OUT_SIZE                     4
#define REG_SIO_NSPI2_AP_TIME_OUT_MASK                     0x000f0000

#define REG_SIO_NSPI2_AP_RBFLAG_POS_SHIFT                  24
#define REG_SIO_NSPI2_AP_RBFLAG_POS_SIZE                   3
#define REG_SIO_NSPI2_AP_RBFLAG_POS_MASK                   0x07000000

#define REG_SIO_NSPI2_AP_SET_RBL_SHIFT                     30
#define REG_SIO_NSPI2_AP_SET_RBL_SIZE                      1
#define REG_SIO_NSPI2_AP_SET_RBL_MASK                      0x40000000

#define REG_SIO_NSPI2_AP_E_SHIFT                           31
#define REG_SIO_NSPI2_AP_E_SIZE                            1
#define REG_SIO_NSPI2_AP_E_MASK                            0x80000000

#ifndef SDK_ASM
#define REG_SIO_NSPI2_AP_FIELD( cmd, time_out, rbflag_pos, set_rbl, e ) \
    (u32)( \
    ((u32)(cmd) << REG_SIO_NSPI2_AP_CMD_SHIFT) | \
    ((u32)(time_out) << REG_SIO_NSPI2_AP_TIME_OUT_SHIFT) | \
    ((u32)(rbflag_pos) << REG_SIO_NSPI2_AP_RBFLAG_POS_SHIFT) | \
    ((u32)(set_rbl) << REG_SIO_NSPI2_AP_SET_RBL_SHIFT) | \
    ((u32)(e) << REG_SIO_NSPI2_AP_E_SHIFT))
#endif


/* NSPI2_MASK */

#define REG_SIO_NSPI2_MASK_INTR_SHIFT                      0
#define REG_SIO_NSPI2_MASK_INTR_SIZE                       3
#define REG_SIO_NSPI2_MASK_INTR_MASK                       0x00000007

#define REG_SIO_NSPI2_MASK_DREQ_SHIFT                      3
#define REG_SIO_NSPI2_MASK_DREQ_SIZE                       1
#define REG_SIO_NSPI2_MASK_DREQ_MASK                       0x00000008

#ifndef SDK_ASM
#define REG_SIO_NSPI2_MASK_FIELD( intr, dreq ) \
    (u32)( \
    ((u32)(intr) << REG_SIO_NSPI2_MASK_INTR_SHIFT) | \
    ((u32)(dreq) << REG_SIO_NSPI2_MASK_DREQ_SHIFT))
#endif


/* NSPI2_INTRS */

#define REG_SIO_NSPI2_INTRS_CAUSE_SHIFT                    0
#define REG_SIO_NSPI2_INTRS_CAUSE_SIZE                     3
#define REG_SIO_NSPI2_INTRS_CAUSE_MASK                     0x00000007

#ifndef SDK_ASM
#define REG_SIO_NSPI2_INTRS_FIELD( cause ) \
    (u32)( \
    ((u32)(cause) << REG_SIO_NSPI2_INTRS_CAUSE_SHIFT))
#endif


/* NSPI3_CNT */

#define REG_SIO_NSPI3_CNT_E_SHIFT                          15
#define REG_SIO_NSPI3_CNT_E_SIZE                           1
#define REG_SIO_NSPI3_CNT_E_MASK                           0x00008000

#define REG_SIO_NSPI3_CNT_STREAM_SHIFT                     13
#define REG_SIO_NSPI3_CNT_STREAM_SIZE                      1
#define REG_SIO_NSPI3_CNT_STREAM_MASK                      0x00002000

#define REG_SIO_NSPI3_CNT_MODE_SHIFT                       12
#define REG_SIO_NSPI3_CNT_MODE_SIZE                        1
#define REG_SIO_NSPI3_CNT_MODE_MASK                        0x00001000

#define REG_SIO_NSPI3_CNT_SEL_SHIFT                        6
#define REG_SIO_NSPI3_CNT_SEL_SIZE                         2
#define REG_SIO_NSPI3_CNT_SEL_MASK                         0x000000c0

#define REG_SIO_NSPI3_CNT_BAUDRATE_SHIFT                   0
#define REG_SIO_NSPI3_CNT_BAUDRATE_SIZE                    3
#define REG_SIO_NSPI3_CNT_BAUDRATE_MASK                    0x00000007

#ifndef SDK_ASM
#define REG_SIO_NSPI3_CNT_FIELD( e, stream, mode, sel, baudrate ) \
    (u32)( \
    ((u32)(e) << REG_SIO_NSPI3_CNT_E_SHIFT) | \
    ((u32)(stream) << REG_SIO_NSPI3_CNT_STREAM_SHIFT) | \
    ((u32)(mode) << REG_SIO_NSPI3_CNT_MODE_SHIFT) | \
    ((u32)(sel) << REG_SIO_NSPI3_CNT_SEL_SHIFT) | \
    ((u32)(baudrate) << REG_SIO_NSPI3_CNT_BAUDRATE_SHIFT))
#endif


/* NSPI3_CS */

#define REG_SIO_NSPI3_CS_CSB_SHIFT                         0
#define REG_SIO_NSPI3_CS_CSB_SIZE                          1
#define REG_SIO_NSPI3_CS_CSB_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_SIO_NSPI3_CS_FIELD( csb ) \
    (u32)( \
    ((u32)(csb) << REG_SIO_NSPI3_CS_CSB_SHIFT))
#endif


/* NSPI3_LEN */

#define REG_SIO_NSPI3_LEN_LEN_SHIFT                        0
#define REG_SIO_NSPI3_LEN_LEN_SIZE                         21
#define REG_SIO_NSPI3_LEN_LEN_MASK                         0x001fffff

#ifndef SDK_ASM
#define REG_SIO_NSPI3_LEN_FIELD( len ) \
    (u32)( \
    ((u32)(len) << REG_SIO_NSPI3_LEN_LEN_SHIFT))
#endif


/* NSPI3_DT */

#define REG_SIO_NSPI3_DT_DATA_SHIFT                        0
#define REG_SIO_NSPI3_DT_DATA_SIZE                         32
#define REG_SIO_NSPI3_DT_DATA_MASK                         0xffffffff

#ifndef SDK_ASM
#define REG_SIO_NSPI3_DT_FIELD( data ) \
    (u32)( \
    ((u32)(data) << REG_SIO_NSPI3_DT_DATA_SHIFT))
#endif


/* NSPI3_DS */

#define REG_SIO_NSPI3_DS_DBUSY_SHIFT                       0
#define REG_SIO_NSPI3_DS_DBUSY_SIZE                        1
#define REG_SIO_NSPI3_DS_DBUSY_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_SIO_NSPI3_DS_FIELD( dbusy ) \
    (u32)( \
    ((u32)(dbusy) << REG_SIO_NSPI3_DS_DBUSY_SHIFT))
#endif


/* NSPI3_AP */

#define REG_SIO_NSPI3_AP_CMD_SHIFT                         0
#define REG_SIO_NSPI3_AP_CMD_SIZE                          8
#define REG_SIO_NSPI3_AP_CMD_MASK                          0x000000ff

#define REG_SIO_NSPI3_AP_TIME_OUT_SHIFT                    16
#define REG_SIO_NSPI3_AP_TIME_OUT_SIZE                     4
#define REG_SIO_NSPI3_AP_TIME_OUT_MASK                     0x000f0000

#define REG_SIO_NSPI3_AP_RBFLAG_POS_SHIFT                  24
#define REG_SIO_NSPI3_AP_RBFLAG_POS_SIZE                   3
#define REG_SIO_NSPI3_AP_RBFLAG_POS_MASK                   0x07000000

#define REG_SIO_NSPI3_AP_SET_RBL_SHIFT                     30
#define REG_SIO_NSPI3_AP_SET_RBL_SIZE                      1
#define REG_SIO_NSPI3_AP_SET_RBL_MASK                      0x40000000

#define REG_SIO_NSPI3_AP_E_SHIFT                           31
#define REG_SIO_NSPI3_AP_E_SIZE                            1
#define REG_SIO_NSPI3_AP_E_MASK                            0x80000000

#ifndef SDK_ASM
#define REG_SIO_NSPI3_AP_FIELD( cmd, time_out, rbflag_pos, set_rbl, e ) \
    (u32)( \
    ((u32)(cmd) << REG_SIO_NSPI3_AP_CMD_SHIFT) | \
    ((u32)(time_out) << REG_SIO_NSPI3_AP_TIME_OUT_SHIFT) | \
    ((u32)(rbflag_pos) << REG_SIO_NSPI3_AP_RBFLAG_POS_SHIFT) | \
    ((u32)(set_rbl) << REG_SIO_NSPI3_AP_SET_RBL_SHIFT) | \
    ((u32)(e) << REG_SIO_NSPI3_AP_E_SHIFT))
#endif


/* NSPI3_MASK */

#define REG_SIO_NSPI3_MASK_INTR_SHIFT                      0
#define REG_SIO_NSPI3_MASK_INTR_SIZE                       3
#define REG_SIO_NSPI3_MASK_INTR_MASK                       0x00000007

#define REG_SIO_NSPI3_MASK_DREQ_SHIFT                      3
#define REG_SIO_NSPI3_MASK_DREQ_SIZE                       1
#define REG_SIO_NSPI3_MASK_DREQ_MASK                       0x00000008

#ifndef SDK_ASM
#define REG_SIO_NSPI3_MASK_FIELD( intr, dreq ) \
    (u32)( \
    ((u32)(intr) << REG_SIO_NSPI3_MASK_INTR_SHIFT) | \
    ((u32)(dreq) << REG_SIO_NSPI3_MASK_DREQ_SHIFT))
#endif


/* NSPI3_INTRS */

#define REG_SIO_NSPI3_INTRS_CAUSE_SHIFT                    0
#define REG_SIO_NSPI3_INTRS_CAUSE_SIZE                     3
#define REG_SIO_NSPI3_INTRS_CAUSE_MASK                     0x00000007

#ifndef SDK_ASM
#define REG_SIO_NSPI3_INTRS_FIELD( cause ) \
    (u32)( \
    ((u32)(cause) << REG_SIO_NSPI3_INTRS_CAUSE_SHIFT))
#endif


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


/* I2C3_DAT */

/* I2C3_CNT */

#define REG_SIO_I2C3_CNT_E_SHIFT                           7
#define REG_SIO_I2C3_CNT_E_SIZE                            1
#define REG_SIO_I2C3_CNT_E_MASK                            0x80

#define REG_SIO_I2C3_CNT_I_SHIFT                           6
#define REG_SIO_I2C3_CNT_I_SIZE                            1
#define REG_SIO_I2C3_CNT_I_MASK                            0x40

#define REG_SIO_I2C3_CNT_RW_SHIFT                          5
#define REG_SIO_I2C3_CNT_RW_SIZE                           1
#define REG_SIO_I2C3_CNT_RW_MASK                           0x20

#define REG_SIO_I2C3_CNT_ACK_SHIFT                         4
#define REG_SIO_I2C3_CNT_ACK_SIZE                          1
#define REG_SIO_I2C3_CNT_ACK_MASK                          0x10

#define REG_SIO_I2C3_CNT_CNT_SHIFT                         3
#define REG_SIO_I2C3_CNT_CNT_SIZE                          3
#define REG_SIO_I2C3_CNT_CNT_MASK                          0x38

#define REG_SIO_I2C3_CNT_NT_SHIFT                          2
#define REG_SIO_I2C3_CNT_NT_SIZE                           1
#define REG_SIO_I2C3_CNT_NT_MASK                           0x04

#define REG_SIO_I2C3_CNT_START_SHIFT                       1
#define REG_SIO_I2C3_CNT_START_SIZE                        1
#define REG_SIO_I2C3_CNT_START_MASK                        0x02

#define REG_SIO_I2C3_CNT_STOP_SHIFT                        0
#define REG_SIO_I2C3_CNT_STOP_SIZE                         1
#define REG_SIO_I2C3_CNT_STOP_MASK                         0x01

#ifndef SDK_ASM
#define REG_SIO_I2C3_CNT_FIELD( e, i, rw, ack, cnt, nt, start, stop ) \
    (u8)( \
    ((u32)(e) << REG_SIO_I2C3_CNT_E_SHIFT) | \
    ((u32)(i) << REG_SIO_I2C3_CNT_I_SHIFT) | \
    ((u32)(rw) << REG_SIO_I2C3_CNT_RW_SHIFT) | \
    ((u32)(ack) << REG_SIO_I2C3_CNT_ACK_SHIFT) | \
    ((u32)(cnt) << REG_SIO_I2C3_CNT_CNT_SHIFT) | \
    ((u32)(nt) << REG_SIO_I2C3_CNT_NT_SHIFT) | \
    ((u32)(start) << REG_SIO_I2C3_CNT_START_SHIFT) | \
    ((u32)(stop) << REG_SIO_I2C3_CNT_STOP_SHIFT))
#endif


/* I2C3_CNT_EX */

#define REG_SIO_I2C3_CNT_EX_LGCY_SHIFT                     15
#define REG_SIO_I2C3_CNT_EX_LGCY_SIZE                      1
#define REG_SIO_I2C3_CNT_EX_LGCY_MASK                      0x8000

#define REG_SIO_I2C3_CNT_EX_WT_SHIFT                       1
#define REG_SIO_I2C3_CNT_EX_WT_SIZE                        1
#define REG_SIO_I2C3_CNT_EX_WT_MASK                        0x0002

#define REG_SIO_I2C3_CNT_EX_SCL_SHIFT                      0
#define REG_SIO_I2C3_CNT_EX_SCL_SIZE                       1
#define REG_SIO_I2C3_CNT_EX_SCL_MASK                       0x0001

#ifndef SDK_ASM
#define REG_SIO_I2C3_CNT_EX_FIELD( lgcy, wt, scl ) \
    (u16)( \
    ((u32)(lgcy) << REG_SIO_I2C3_CNT_EX_LGCY_SHIFT) | \
    ((u32)(wt) << REG_SIO_I2C3_CNT_EX_WT_SHIFT) | \
    ((u32)(scl) << REG_SIO_I2C3_CNT_EX_SCL_SHIFT))
#endif


/* I2C3_SCL */

#define REG_SIO_I2C3_SCL_HI_PRD_SHIFT                      8
#define REG_SIO_I2C3_SCL_HI_PRD_SIZE                       5
#define REG_SIO_I2C3_SCL_HI_PRD_MASK                       0x1f00

#define REG_SIO_I2C3_SCL_LO_PRD_SHIFT                      0
#define REG_SIO_I2C3_SCL_LO_PRD_SIZE                       6
#define REG_SIO_I2C3_SCL_LO_PRD_MASK                       0x003f

#ifndef SDK_ASM
#define REG_SIO_I2C3_SCL_FIELD( hi_prd, lo_prd ) \
    (u16)( \
    ((u32)(hi_prd) << REG_SIO_I2C3_SCL_HI_PRD_SHIFT) | \
    ((u32)(lo_prd) << REG_SIO_I2C3_SCL_LO_PRD_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_SIO_H_ */
#endif
