/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/MPCore/ioreg_SND.h

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
#ifndef NN_HW_CTR_TEG2_MPCORE_IOREG_SND_H_
#define NN_HW_CTR_TEG2_MPCORE_IOREG_SND_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* I2S1_CNT */

#define REG_I2S1_CNT_OFFSET                                0x145000
#define REG_I2S1_CNT_ADDR                                  (HW_REG_BASE + REG_I2S1_CNT_OFFSET)
#define reg_SND_I2S1_CNT                                   (*( REGType16v *) REG_I2S1_CNT_ADDR)

/* I2S2_CNT */

#define REG_I2S2_CNT_OFFSET                                0x145002
#define REG_I2S2_CNT_ADDR                                  (HW_REG_BASE + REG_I2S2_CNT_OFFSET)
#define reg_SND_I2S2_CNT                                   (*( REGType16v *) REG_I2S2_CNT_ADDR)

/* MIC_CNT */

#define REG_MIC_CNT_OFFSET                                 0x162000
#define REG_MIC_CNT_ADDR                                   (HW_REG_BASE + REG_MIC_CNT_OFFSET)
#define reg_SND_MIC_CNT                                    (*( REGType16v *) REG_MIC_CNT_ADDR)

/* MIC_DAT */

#define REG_MIC_DAT_OFFSET                                 0x162004
#define REG_MIC_DAT_ADDR                                   (HW_REG_BASE + REG_MIC_DAT_OFFSET)
#define reg_SND_MIC_DAT                                    (*(const REGType32v *) REG_MIC_DAT_ADDR)

/* SND_CAPVOL */

#define REG_SND_CAPVOL_OFFSET                              0x103000
#define REG_SND_CAPVOL_ADDR                                (HW_REG_BASE + REG_SND_CAPVOL_OFFSET)
#define reg_SND_SND_CAPVOL                                 (*( REGType8v *) REG_SND_CAPVOL_ADDR)

/* SND_VOL */

#define REG_SND_VOL_OFFSET                                 0x103002
#define REG_SND_VOL_ADDR                                   (HW_REG_BASE + REG_SND_VOL_OFFSET)
#define reg_SND_SND_VOL                                    (*( REGType8v *) REG_SND_VOL_ADDR)

/* SND_CNT */

#define REG_SND_CNT_OFFSET                                 0x103003
#define REG_SND_CNT_ADDR                                   (HW_REG_BASE + REG_SND_CNT_OFFSET)
#define reg_SND_SND_CNT                                    (*( REGType8v *) REG_SND_CNT_ADDR)

/* SND0_CNT */

#define REG_SND0_CNT_OFFSET                                0x103400
#define REG_SND0_CNT_ADDR                                  (HW_REG_BASE + REG_SND0_CNT_OFFSET)
#define reg_SND_SND0_CNT                                   (*( REGType16v *) REG_SND0_CNT_ADDR)

/* SND0_CAP0VOL */

#define REG_SND0_CAP0VOL_OFFSET                            0x103404
#define REG_SND0_CAP0VOL_ADDR                              (HW_REG_BASE + REG_SND0_CAP0VOL_OFFSET)
#define reg_SND_SND0_CAP0VOL                               (*( REGType8v *) REG_SND0_CAP0VOL_ADDR)

/* SND0_CAP1VOL */

#define REG_SND0_CAP1VOL_OFFSET                            0x103405
#define REG_SND0_CAP1VOL_ADDR                              (HW_REG_BASE + REG_SND0_CAP1VOL_OFFSET)
#define reg_SND_SND0_CAP1VOL                               (*( REGType8v *) REG_SND0_CAP1VOL_ADDR)

/* SND0_RVOL */

#define REG_SND0_RVOL_OFFSET                               0x103406
#define REG_SND0_RVOL_ADDR                                 (HW_REG_BASE + REG_SND0_RVOL_OFFSET)
#define reg_SND_SND0_RVOL                                  (*( REGType8v *) REG_SND0_RVOL_ADDR)

/* SND0_LVOL */

#define REG_SND0_LVOL_OFFSET                               0x103407
#define REG_SND0_LVOL_ADDR                                 (HW_REG_BASE + REG_SND0_LVOL_OFFSET)
#define reg_SND_SND0_LVOL                                  (*( REGType8v *) REG_SND0_LVOL_ADDR)

/* SND0_TMR */

#define REG_SND0_TMR_OFFSET                                0x103408
#define REG_SND0_TMR_ADDR                                  (HW_REG_BASE + REG_SND0_TMR_OFFSET)
#define reg_SND_SND0_TMR                                   (*( REGType16v *) REG_SND0_TMR_ADDR)

/* SND0_SAD */

#define REG_SND0_SAD_OFFSET                                0x10340c
#define REG_SND0_SAD_ADDR                                  (HW_REG_BASE + REG_SND0_SAD_OFFSET)
#define reg_SND_SND0_SAD                                   (*( REGType32v *) REG_SND0_SAD_ADDR)

/* SND0_RPT_LEN */

#define REG_SND0_RPT_LEN_OFFSET                            0x103410
#define REG_SND0_RPT_LEN_ADDR                              (HW_REG_BASE + REG_SND0_RPT_LEN_OFFSET)
#define reg_SND_SND0_RPT_LEN                               (*( REGType32v *) REG_SND0_RPT_LEN_ADDR)

/* SND0_RPT_PT */

#define REG_SND0_RPT_PT_OFFSET                             0x103414
#define REG_SND0_RPT_PT_ADDR                               (HW_REG_BASE + REG_SND0_RPT_PT_OFFSET)
#define reg_SND_SND0_RPT_PT                                (*( REGType32v *) REG_SND0_RPT_PT_ADDR)

/* SND0_IDX1 */

#define REG_SND0_IDX1_OFFSET                               0x103418
#define REG_SND0_IDX1_ADDR                                 (HW_REG_BASE + REG_SND0_IDX1_OFFSET)
#define reg_SND_SND0_IDX1                                  (*( REGType16v *) REG_SND0_IDX1_ADDR)

/* SND0_IDX2 */

#define REG_SND0_IDX2_OFFSET                               0x10341c
#define REG_SND0_IDX2_ADDR                                 (HW_REG_BASE + REG_SND0_IDX2_OFFSET)
#define reg_SND_SND0_IDX2                                  (*( REGType32v *) REG_SND0_IDX2_ADDR)

/* SND1_CNT */

#define REG_SND1_CNT_OFFSET                                0x103420
#define REG_SND1_CNT_ADDR                                  (HW_REG_BASE + REG_SND1_CNT_OFFSET)
#define reg_SND_SND1_CNT                                   (*( REGType16v *) REG_SND1_CNT_ADDR)

/* SND1_CAP0VOL */

#define REG_SND1_CAP0VOL_OFFSET                            0x103424
#define REG_SND1_CAP0VOL_ADDR                              (HW_REG_BASE + REG_SND1_CAP0VOL_OFFSET)
#define reg_SND_SND1_CAP0VOL                               (*( REGType8v *) REG_SND1_CAP0VOL_ADDR)

/* SND1_CAP1VOL */

#define REG_SND1_CAP1VOL_OFFSET                            0x103425
#define REG_SND1_CAP1VOL_ADDR                              (HW_REG_BASE + REG_SND1_CAP1VOL_OFFSET)
#define reg_SND_SND1_CAP1VOL                               (*( REGType8v *) REG_SND1_CAP1VOL_ADDR)

/* SND1_RVOL */

#define REG_SND1_RVOL_OFFSET                               0x103426
#define REG_SND1_RVOL_ADDR                                 (HW_REG_BASE + REG_SND1_RVOL_OFFSET)
#define reg_SND_SND1_RVOL                                  (*( REGType8v *) REG_SND1_RVOL_ADDR)

/* SND1_LVOL */

#define REG_SND1_LVOL_OFFSET                               0x103427
#define REG_SND1_LVOL_ADDR                                 (HW_REG_BASE + REG_SND1_LVOL_OFFSET)
#define reg_SND_SND1_LVOL                                  (*( REGType8v *) REG_SND1_LVOL_ADDR)

/* SND1_TMR */

#define REG_SND1_TMR_OFFSET                                0x103428
#define REG_SND1_TMR_ADDR                                  (HW_REG_BASE + REG_SND1_TMR_OFFSET)
#define reg_SND_SND1_TMR                                   (*( REGType16v *) REG_SND1_TMR_ADDR)

/* SND1_SAD */

#define REG_SND1_SAD_OFFSET                                0x10342c
#define REG_SND1_SAD_ADDR                                  (HW_REG_BASE + REG_SND1_SAD_OFFSET)
#define reg_SND_SND1_SAD                                   (*( REGType32v *) REG_SND1_SAD_ADDR)

/* SND1_RPT_LEN */

#define REG_SND1_RPT_LEN_OFFSET                            0x103430
#define REG_SND1_RPT_LEN_ADDR                              (HW_REG_BASE + REG_SND1_RPT_LEN_OFFSET)
#define reg_SND_SND1_RPT_LEN                               (*( REGType32v *) REG_SND1_RPT_LEN_ADDR)

/* SND1_RPT_PT */

#define REG_SND1_RPT_PT_OFFSET                             0x103434
#define REG_SND1_RPT_PT_ADDR                               (HW_REG_BASE + REG_SND1_RPT_PT_OFFSET)
#define reg_SND_SND1_RPT_PT                                (*( REGType32v *) REG_SND1_RPT_PT_ADDR)

/* SND1_IDX1 */

#define REG_SND1_IDX1_OFFSET                               0x103438
#define REG_SND1_IDX1_ADDR                                 (HW_REG_BASE + REG_SND1_IDX1_OFFSET)
#define reg_SND_SND1_IDX1                                  (*( REGType16v *) REG_SND1_IDX1_ADDR)

/* SND1_IDX2 */

#define REG_SND1_IDX2_OFFSET                               0x10343c
#define REG_SND1_IDX2_ADDR                                 (HW_REG_BASE + REG_SND1_IDX2_OFFSET)
#define reg_SND_SND1_IDX2                                  (*( REGType32v *) REG_SND1_IDX2_ADDR)

/* SND_CAP0CNT */

#define REG_SND_CAP0CNT_OFFSET                             0x103800
#define REG_SND_CAP0CNT_ADDR                               (HW_REG_BASE + REG_SND_CAP0CNT_OFFSET)
#define reg_SND_SND_CAP0CNT                                (*( REGType16v *) REG_SND_CAP0CNT_ADDR)

/* SND_CAP0TMR */

#define REG_SND_CAP0TMR_OFFSET                             0x103804
#define REG_SND_CAP0TMR_ADDR                               (HW_REG_BASE + REG_SND_CAP0TMR_OFFSET)
#define reg_SND_SND_CAP0TMR                                (*( REGType16v *) REG_SND_CAP0TMR_ADDR)

/* SND_CAP0LEN */

#define REG_SND_CAP0LEN_OFFSET                             0x103808
#define REG_SND_CAP0LEN_ADDR                               (HW_REG_BASE + REG_SND_CAP0LEN_OFFSET)
#define reg_SND_SND_CAP0LEN                                (*( REGType32v *) REG_SND_CAP0LEN_ADDR)

/* SND_CAP0DAD */

#define REG_SND_CAP0DAD_OFFSET                             0x10380c
#define REG_SND_CAP0DAD_ADDR                               (HW_REG_BASE + REG_SND_CAP0DAD_OFFSET)
#define reg_SND_SND_CAP0DAD                                (*( REGType16v *) REG_SND_CAP0DAD_ADDR)

/* SND_CAP1CNT */

#define REG_SND_CAP1CNT_OFFSET                             0x103810
#define REG_SND_CAP1CNT_ADDR                               (HW_REG_BASE + REG_SND_CAP1CNT_OFFSET)
#define reg_SND_SND_CAP1CNT                                (*( REGType16v *) REG_SND_CAP1CNT_ADDR)

/* SND_CAP1TMR */

#define REG_SND_CAP1TMR_OFFSET                             0x103814
#define REG_SND_CAP1TMR_ADDR                               (HW_REG_BASE + REG_SND_CAP1TMR_OFFSET)
#define reg_SND_SND_CAP1TMR                                (*( REGType16v *) REG_SND_CAP1TMR_ADDR)

/* SND_CAP1LEN */

#define REG_SND_CAP1LEN_OFFSET                             0x103818
#define REG_SND_CAP1LEN_ADDR                               (HW_REG_BASE + REG_SND_CAP1LEN_OFFSET)
#define reg_SND_SND_CAP1LEN                                (*( REGType32v *) REG_SND_CAP1LEN_ADDR)

/* SND_CAP1DAD */

#define REG_SND_CAP1DAD_OFFSET                             0x10381c
#define REG_SND_CAP1DAD_ADDR                               (HW_REG_BASE + REG_SND_CAP1DAD_OFFSET)
#define reg_SND_SND_CAP1DAD                                (*( REGType16v *) REG_SND_CAP1DAD_ADDR)


/*
 * Definitions of Register fields
 */


/* I2S1_CNT */

#define REG_SND_I2S1_CNT_E_SHIFT                           15
#define REG_SND_I2S1_CNT_E_SIZE                            1
#define REG_SND_I2S1_CNT_E_MASK                            0x8000

#define REG_SND_I2S1_CNT_FSEL_SHIFT                        13
#define REG_SND_I2S1_CNT_FSEL_SIZE                         2
#define REG_SND_I2S1_CNT_FSEL_MASK                         0x6000

#define REG_SND_I2S1_CNT_SDI_SEL_SHIFT                     12
#define REG_SND_I2S1_CNT_SDI_SEL_SIZE                      1
#define REG_SND_I2S1_CNT_SDI_SEL_MASK                      0x1000

#define REG_SND_I2S1_CNT_AGB_VOL_SHIFT                     6
#define REG_SND_I2S1_CNT_AGB_VOL_SIZE                      6
#define REG_SND_I2S1_CNT_AGB_VOL_MASK                      0x0fc0

#define REG_SND_I2S1_CNT_DSP_VOL_SHIFT                     0
#define REG_SND_I2S1_CNT_DSP_VOL_SIZE                      6
#define REG_SND_I2S1_CNT_DSP_VOL_MASK                      0x003f

#ifndef SDK_ASM
#define REG_SND_I2S1_CNT_FIELD( e, fsel, sdi_sel, agb_vol, dsp_vol ) \
    (u16)( \
    ((u32)(e) << REG_SND_I2S1_CNT_E_SHIFT) | \
    ((u32)(fsel) << REG_SND_I2S1_CNT_FSEL_SHIFT) | \
    ((u32)(sdi_sel) << REG_SND_I2S1_CNT_SDI_SEL_SHIFT) | \
    ((u32)(agb_vol) << REG_SND_I2S1_CNT_AGB_VOL_SHIFT) | \
    ((u32)(dsp_vol) << REG_SND_I2S1_CNT_DSP_VOL_SHIFT))
#endif


/* I2S2_CNT */

#define REG_SND_I2S2_CNT_E_SHIFT                           15
#define REG_SND_I2S2_CNT_E_SIZE                            1
#define REG_SND_I2S2_CNT_E_MASK                            0x8000

#define REG_SND_I2S2_CNT_FSEL_SHIFT                        13
#define REG_SND_I2S2_CNT_FSEL_SIZE                         2
#define REG_SND_I2S2_CNT_FSEL_MASK                         0x6000

#ifndef SDK_ASM
#define REG_SND_I2S2_CNT_FIELD( e, fsel ) \
    (u16)( \
    ((u32)(e) << REG_SND_I2S2_CNT_E_SHIFT) | \
    ((u32)(fsel) << REG_SND_I2S2_CNT_FSEL_SHIFT))
#endif


/* MIC_CNT */

#define REG_SND_MIC_CNT_E_SHIFT                            15
#define REG_SND_MIC_CNT_E_SIZE                             1
#define REG_SND_MIC_CNT_E_MASK                             0x8000

#define REG_SND_MIC_CNT_I_SHIFT                            13
#define REG_SND_MIC_CNT_I_SIZE                             2
#define REG_SND_MIC_CNT_I_MASK                             0x6000

#define REG_SND_MIC_CNT_CL_SHIFT                           12
#define REG_SND_MIC_CNT_CL_SIZE                            1
#define REG_SND_MIC_CNT_CL_MASK                            0x1000

#define REG_SND_MIC_CNT_STATUS_SHIFT                       8
#define REG_SND_MIC_CNT_STATUS_SIZE                        4
#define REG_SND_MIC_CNT_STATUS_MASK                        0x0f00

#define REG_SND_MIC_CNT_ERR_SHIFT                          11
#define REG_SND_MIC_CNT_ERR_SIZE                           1
#define REG_SND_MIC_CNT_ERR_MASK                           0x0800

#define REG_SND_MIC_CNT_FULL_SHIFT                         10
#define REG_SND_MIC_CNT_FULL_SIZE                          1
#define REG_SND_MIC_CNT_FULL_MASK                          0x0400

#define REG_SND_MIC_CNT_HALF_SHIFT                         9
#define REG_SND_MIC_CNT_HALF_SIZE                          1
#define REG_SND_MIC_CNT_HALF_MASK                          0x0200

#define REG_SND_MIC_CNT_EMP_SHIFT                          8
#define REG_SND_MIC_CNT_EMP_SIZE                           1
#define REG_SND_MIC_CNT_EMP_MASK                           0x0100

#define REG_SND_MIC_CNT_CONTROL_SHIFT                      0
#define REG_SND_MIC_CNT_CONTROL_SIZE                       4
#define REG_SND_MIC_CNT_CONTROL_MASK                       0x000f

#define REG_SND_MIC_CNT_F_SHIFT                            2
#define REG_SND_MIC_CNT_F_SIZE                             2
#define REG_SND_MIC_CNT_F_MASK                             0x000c

#define REG_SND_MIC_CNT_R_SHIFT                            1
#define REG_SND_MIC_CNT_R_SIZE                             1
#define REG_SND_MIC_CNT_R_MASK                             0x0002

#define REG_SND_MIC_CNT_L_SHIFT                            0
#define REG_SND_MIC_CNT_L_SIZE                             1
#define REG_SND_MIC_CNT_L_MASK                             0x0001

#ifndef SDK_ASM
#define REG_SND_MIC_CNT_FIELD( e, i, cl, status, err, full, half, emp, control, f, r, l ) \
    (u16)( \
    ((u32)(e) << REG_SND_MIC_CNT_E_SHIFT) | \
    ((u32)(i) << REG_SND_MIC_CNT_I_SHIFT) | \
    ((u32)(cl) << REG_SND_MIC_CNT_CL_SHIFT) | \
    ((u32)(status) << REG_SND_MIC_CNT_STATUS_SHIFT) | \
    ((u32)(err) << REG_SND_MIC_CNT_ERR_SHIFT) | \
    ((u32)(full) << REG_SND_MIC_CNT_FULL_SHIFT) | \
    ((u32)(half) << REG_SND_MIC_CNT_HALF_SHIFT) | \
    ((u32)(emp) << REG_SND_MIC_CNT_EMP_SHIFT) | \
    ((u32)(control) << REG_SND_MIC_CNT_CONTROL_SHIFT) | \
    ((u32)(f) << REG_SND_MIC_CNT_F_SHIFT) | \
    ((u32)(r) << REG_SND_MIC_CNT_R_SHIFT) | \
    ((u32)(l) << REG_SND_MIC_CNT_L_SHIFT))
#endif


/* MIC_DAT */

#define REG_SND_MIC_DAT_SECOND_SHIFT                       16
#define REG_SND_MIC_DAT_SECOND_SIZE                        16
#define REG_SND_MIC_DAT_SECOND_MASK                        0xffff0000

#define REG_SND_MIC_DAT_FIRST_SHIFT                        0
#define REG_SND_MIC_DAT_FIRST_SIZE                         16
#define REG_SND_MIC_DAT_FIRST_MASK                         0x0000ffff

#ifndef SDK_ASM
#define REG_SND_MIC_DAT_FIELD( second, first ) \
    (u32)( \
    ((u32)(second) << REG_SND_MIC_DAT_SECOND_SHIFT) | \
    ((u32)(first) << REG_SND_MIC_DAT_FIRST_SHIFT))
#endif


/* SND_CAPVOL */

/* SND_VOL */

/* SND_CNT */

#define REG_SND_SND_CNT_E_SHIFT                            7
#define REG_SND_SND_CNT_E_SIZE                             1
#define REG_SND_SND_CNT_E_MASK                             0x80

#define REG_SND_SND_CNT_FRS_SHIFT                          6
#define REG_SND_SND_CNT_FRS_SIZE                           1
#define REG_SND_SND_CNT_FRS_MASK                           0x40

#ifndef SDK_ASM
#define REG_SND_SND_CNT_FIELD( e, frs ) \
    (u8)( \
    ((u32)(e) << REG_SND_SND_CNT_E_SHIFT) | \
    ((u32)(frs) << REG_SND_SND_CNT_FRS_SHIFT))
#endif


/* SND0_CNT */

#define REG_SND_SND0_CNT_E_SHIFT                           15
#define REG_SND_SND0_CNT_E_SIZE                            1
#define REG_SND_SND0_CNT_E_MASK                            0x8000

#define REG_SND_SND0_CNT_ST_SHIFT                          14
#define REG_SND_SND0_CNT_ST_SIZE                           1
#define REG_SND_SND0_CNT_ST_MASK                           0x4000

#define REG_SND_SND0_CNT_FMT_SHIFT                         12
#define REG_SND_SND0_CNT_FMT_SIZE                          2
#define REG_SND_SND0_CNT_FMT_MASK                          0x3000

#define REG_SND_SND0_CNT_RPT_SHIFT                         10
#define REG_SND_SND0_CNT_RPT_SIZE                          2
#define REG_SND_SND0_CNT_RPT_MASK                          0x0c00

#define REG_SND_SND0_CNT_SFT_SHIFT                         8
#define REG_SND_SND0_CNT_SFT_SIZE                          2
#define REG_SND_SND0_CNT_SFT_MASK                          0x0300

#define REG_SND_SND0_CNT_HOLD_SHIFT                        7
#define REG_SND_SND0_CNT_HOLD_SIZE                         1
#define REG_SND_SND0_CNT_HOLD_MASK                         0x0080

#define REG_SND_SND0_CNT_FLI_SHIFT                         6
#define REG_SND_SND0_CNT_FLI_SIZE                          1
#define REG_SND_SND0_CNT_FLI_MASK                          0x0040

#define REG_SND_SND0_CNT_DUTY_SHIFT                        0
#define REG_SND_SND0_CNT_DUTY_SIZE                         3
#define REG_SND_SND0_CNT_DUTY_MASK                         0x0007

#ifndef SDK_ASM
#define REG_SND_SND0_CNT_FIELD( e, st, fmt, rpt, sft, hold, fli, duty ) \
    (u16)( \
    ((u32)(e) << REG_SND_SND0_CNT_E_SHIFT) | \
    ((u32)(st) << REG_SND_SND0_CNT_ST_SHIFT) | \
    ((u32)(fmt) << REG_SND_SND0_CNT_FMT_SHIFT) | \
    ((u32)(rpt) << REG_SND_SND0_CNT_RPT_SHIFT) | \
    ((u32)(sft) << REG_SND_SND0_CNT_SFT_SHIFT) | \
    ((u32)(hold) << REG_SND_SND0_CNT_HOLD_SHIFT) | \
    ((u32)(fli) << REG_SND_SND0_CNT_FLI_SHIFT) | \
    ((u32)(duty) << REG_SND_SND0_CNT_DUTY_SHIFT))
#endif


/* SND0_CAP0VOL */

/* SND0_CAP1VOL */

/* SND0_RVOL */

/* SND0_LVOL */

/* SND0_TMR */

/* SND0_SAD */

/* SND0_RPT_LEN */

#define REG_SND_SND0_RPT_LEN_LEN_SHIFT                     0
#define REG_SND_SND0_RPT_LEN_LEN_SIZE                      24
#define REG_SND_SND0_RPT_LEN_LEN_MASK                      0x00ffffff

#ifndef SDK_ASM
#define REG_SND_SND0_RPT_LEN_FIELD( len ) \
    (u32)( \
    ((u32)(len) << REG_SND_SND0_RPT_LEN_LEN_SHIFT))
#endif


/* SND0_RPT_PT */

#define REG_SND_SND0_RPT_PT_PT_SHIFT                       0
#define REG_SND_SND0_RPT_PT_PT_SIZE                        24
#define REG_SND_SND0_RPT_PT_PT_MASK                        0x00ffffff

#ifndef SDK_ASM
#define REG_SND_SND0_RPT_PT_FIELD( pt ) \
    (u32)( \
    ((u32)(pt) << REG_SND_SND0_RPT_PT_PT_SHIFT))
#endif


/* SND0_IDX1 */

#define REG_SND_SND0_IDX1_IDX_SHIFT                        0
#define REG_SND_SND0_IDX1_IDX_SIZE                         23
#define REG_SND_SND0_IDX1_IDX_MASK                         0x7fffff

#ifndef SDK_ASM
#define REG_SND_SND0_IDX1_FIELD( idx ) \
    (u16)( \
    ((u32)(idx) << REG_SND_SND0_IDX1_IDX_SHIFT))
#endif


/* SND0_IDX2 */

#define REG_SND_SND0_IDX2_IDX_SHIFT                        0
#define REG_SND_SND0_IDX2_IDX_SIZE                         23
#define REG_SND_SND0_IDX2_IDX_MASK                         0x007fffff

#ifndef SDK_ASM
#define REG_SND_SND0_IDX2_FIELD( idx ) \
    (u32)( \
    ((u32)(idx) << REG_SND_SND0_IDX2_IDX_SHIFT))
#endif


/* SND1_CNT */

#define REG_SND_SND1_CNT_E_SHIFT                           15
#define REG_SND_SND1_CNT_E_SIZE                            1
#define REG_SND_SND1_CNT_E_MASK                            0x8000

#define REG_SND_SND1_CNT_ST_SHIFT                          14
#define REG_SND_SND1_CNT_ST_SIZE                           1
#define REG_SND_SND1_CNT_ST_MASK                           0x4000

#define REG_SND_SND1_CNT_FMT_SHIFT                         12
#define REG_SND_SND1_CNT_FMT_SIZE                          2
#define REG_SND_SND1_CNT_FMT_MASK                          0x3000

#define REG_SND_SND1_CNT_RPT_SHIFT                         10
#define REG_SND_SND1_CNT_RPT_SIZE                          2
#define REG_SND_SND1_CNT_RPT_MASK                          0x0c00

#define REG_SND_SND1_CNT_SFT_SHIFT                         8
#define REG_SND_SND1_CNT_SFT_SIZE                          2
#define REG_SND_SND1_CNT_SFT_MASK                          0x0300

#define REG_SND_SND1_CNT_HOLD_SHIFT                        7
#define REG_SND_SND1_CNT_HOLD_SIZE                         1
#define REG_SND_SND1_CNT_HOLD_MASK                         0x0080

#define REG_SND_SND1_CNT_FLI_SHIFT                         6
#define REG_SND_SND1_CNT_FLI_SIZE                          1
#define REG_SND_SND1_CNT_FLI_MASK                          0x0040

#define REG_SND_SND1_CNT_DUTY_SHIFT                        0
#define REG_SND_SND1_CNT_DUTY_SIZE                         3
#define REG_SND_SND1_CNT_DUTY_MASK                         0x0007

#ifndef SDK_ASM
#define REG_SND_SND1_CNT_FIELD( e, st, fmt, rpt, sft, hold, fli, duty ) \
    (u16)( \
    ((u32)(e) << REG_SND_SND1_CNT_E_SHIFT) | \
    ((u32)(st) << REG_SND_SND1_CNT_ST_SHIFT) | \
    ((u32)(fmt) << REG_SND_SND1_CNT_FMT_SHIFT) | \
    ((u32)(rpt) << REG_SND_SND1_CNT_RPT_SHIFT) | \
    ((u32)(sft) << REG_SND_SND1_CNT_SFT_SHIFT) | \
    ((u32)(hold) << REG_SND_SND1_CNT_HOLD_SHIFT) | \
    ((u32)(fli) << REG_SND_SND1_CNT_FLI_SHIFT) | \
    ((u32)(duty) << REG_SND_SND1_CNT_DUTY_SHIFT))
#endif


/* SND1_CAP0VOL */

/* SND1_CAP1VOL */

/* SND1_RVOL */

/* SND1_LVOL */

/* SND1_TMR */

/* SND1_SAD */

/* SND1_RPT_LEN */

#define REG_SND_SND1_RPT_LEN_LEN_SHIFT                     0
#define REG_SND_SND1_RPT_LEN_LEN_SIZE                      24
#define REG_SND_SND1_RPT_LEN_LEN_MASK                      0x00ffffff

#ifndef SDK_ASM
#define REG_SND_SND1_RPT_LEN_FIELD( len ) \
    (u32)( \
    ((u32)(len) << REG_SND_SND1_RPT_LEN_LEN_SHIFT))
#endif


/* SND1_RPT_PT */

#define REG_SND_SND1_RPT_PT_PT_SHIFT                       0
#define REG_SND_SND1_RPT_PT_PT_SIZE                        24
#define REG_SND_SND1_RPT_PT_PT_MASK                        0x00ffffff

#ifndef SDK_ASM
#define REG_SND_SND1_RPT_PT_FIELD( pt ) \
    (u32)( \
    ((u32)(pt) << REG_SND_SND1_RPT_PT_PT_SHIFT))
#endif


/* SND1_IDX1 */

#define REG_SND_SND1_IDX1_IDX_SHIFT                        0
#define REG_SND_SND1_IDX1_IDX_SIZE                         23
#define REG_SND_SND1_IDX1_IDX_MASK                         0x7fffff

#ifndef SDK_ASM
#define REG_SND_SND1_IDX1_FIELD( idx ) \
    (u16)( \
    ((u32)(idx) << REG_SND_SND1_IDX1_IDX_SHIFT))
#endif


/* SND1_IDX2 */

#define REG_SND_SND1_IDX2_IDX_SHIFT                        0
#define REG_SND_SND1_IDX2_IDX_SIZE                         23
#define REG_SND_SND1_IDX2_IDX_MASK                         0x007fffff

#ifndef SDK_ASM
#define REG_SND_SND1_IDX2_FIELD( idx ) \
    (u32)( \
    ((u32)(idx) << REG_SND_SND1_IDX2_IDX_SHIFT))
#endif


/* SND_CAP0CNT */

#define REG_SND_SND_CAP0CNT_E_SHIFT                        15
#define REG_SND_SND_CAP0CNT_E_SIZE                         1
#define REG_SND_SND_CAP0CNT_E_MASK                         0x8000

#define REG_SND_SND_CAP0CNT_FRS_SHIFT                      2
#define REG_SND_SND_CAP0CNT_FRS_SIZE                       1
#define REG_SND_SND_CAP0CNT_FRS_MASK                       0x0004

#define REG_SND_SND_CAP0CNT_FMT_SHIFT                      1
#define REG_SND_SND_CAP0CNT_FMT_SIZE                       1
#define REG_SND_SND_CAP0CNT_FMT_MASK                       0x0002

#define REG_SND_SND_CAP0CNT_RPT_SHIFT                      0
#define REG_SND_SND_CAP0CNT_RPT_SIZE                       1
#define REG_SND_SND_CAP0CNT_RPT_MASK                       0x0001

#ifndef SDK_ASM
#define REG_SND_SND_CAP0CNT_FIELD( e, frs, fmt, rpt ) \
    (u16)( \
    ((u32)(e) << REG_SND_SND_CAP0CNT_E_SHIFT) | \
    ((u32)(frs) << REG_SND_SND_CAP0CNT_FRS_SHIFT) | \
    ((u32)(fmt) << REG_SND_SND_CAP0CNT_FMT_SHIFT) | \
    ((u32)(rpt) << REG_SND_SND_CAP0CNT_RPT_SHIFT))
#endif


/* SND_CAP0TMR */

/* SND_CAP0LEN */

#define REG_SND_SND_CAP0LEN_LEN_SHIFT                      0
#define REG_SND_SND_CAP0LEN_LEN_SIZE                       24
#define REG_SND_SND_CAP0LEN_LEN_MASK                       0x00ffffff

#ifndef SDK_ASM
#define REG_SND_SND_CAP0LEN_FIELD( len ) \
    (u32)( \
    ((u32)(len) << REG_SND_SND_CAP0LEN_LEN_SHIFT))
#endif


/* SND_CAP0DAD */

/* SND_CAP1CNT */

#define REG_SND_SND_CAP1CNT_E_SHIFT                        15
#define REG_SND_SND_CAP1CNT_E_SIZE                         1
#define REG_SND_SND_CAP1CNT_E_MASK                         0x8000

#define REG_SND_SND_CAP1CNT_FRS_SHIFT                      2
#define REG_SND_SND_CAP1CNT_FRS_SIZE                       1
#define REG_SND_SND_CAP1CNT_FRS_MASK                       0x0004

#define REG_SND_SND_CAP1CNT_FMT_SHIFT                      1
#define REG_SND_SND_CAP1CNT_FMT_SIZE                       1
#define REG_SND_SND_CAP1CNT_FMT_MASK                       0x0002

#define REG_SND_SND_CAP1CNT_RPT_SHIFT                      0
#define REG_SND_SND_CAP1CNT_RPT_SIZE                       1
#define REG_SND_SND_CAP1CNT_RPT_MASK                       0x0001

#ifndef SDK_ASM
#define REG_SND_SND_CAP1CNT_FIELD( e, frs, fmt, rpt ) \
    (u16)( \
    ((u32)(e) << REG_SND_SND_CAP1CNT_E_SHIFT) | \
    ((u32)(frs) << REG_SND_SND_CAP1CNT_FRS_SHIFT) | \
    ((u32)(fmt) << REG_SND_SND_CAP1CNT_FMT_SHIFT) | \
    ((u32)(rpt) << REG_SND_SND_CAP1CNT_RPT_SHIFT))
#endif


/* SND_CAP1TMR */

/* SND_CAP1LEN */

#define REG_SND_SND_CAP1LEN_LEN_SHIFT                      0
#define REG_SND_SND_CAP1LEN_LEN_SIZE                       24
#define REG_SND_SND_CAP1LEN_LEN_MASK                       0x00ffffff

#ifndef SDK_ASM
#define REG_SND_SND_CAP1LEN_FIELD( len ) \
    (u32)( \
    ((u32)(len) << REG_SND_SND_CAP1LEN_LEN_SHIFT))
#endif


/* SND_CAP1DAD */

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_MPCORE_IOREG_SND_H_ */
#endif
