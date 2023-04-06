/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-EIU/MPCore/ioreg_eiupatch_PDN.h

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
#ifndef NN_HW_CTR_EIU_MPCORE_IOREG_EIUPATCH_PDN_H_
#define NN_HW_CTR_EIU_MPCORE_IOREG_EIUPATCH_PDN_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* CNT */

#define REG_CNT_OFFSET                                     0x141000
#define REG_CNT_ADDR                                       (HW_REG_BASE + REG_CNT_OFFSET)
#define reg_PDN_CNT                                        (*( REGType16v *) REG_CNT_ADDR)

/* WE */

#define REG_WE_OFFSET                                      0x141008
#define REG_WE_ADDR                                        (HW_REG_BASE + REG_WE_OFFSET)
#define reg_PDN_WE                                         (*( REGType32v *) REG_WE_ADDR)

/* WRS */

#define REG_WRS_OFFSET                                     0x14100c
#define REG_WRS_ADDR                                       (HW_REG_BASE + REG_WRS_OFFSET)
#define reg_PDN_WRS                                        (*( REGType32v *) REG_WRS_ADDR)

/* GPU */

#define REG_GPU_OFFSET                                     0x141200
#define REG_GPU_ADDR                                       (HW_REG_BASE + REG_GPU_OFFSET)
#define reg_PDN_GPU                                        (*( REGType32v *) REG_GPU_ADDR)

/* VRAM */

#define REG_VRAM_OFFSET                                    0x141204
#define REG_VRAM_ADDR                                      (HW_REG_BASE + REG_VRAM_OFFSET)
#define reg_PDN_VRAM                                       (*( REGType8v *) REG_VRAM_ADDR)

/* LCD */

#define REG_LCD_OFFSET                                     0x141208
#define REG_LCD_ADDR                                       (HW_REG_BASE + REG_LCD_OFFSET)
#define reg_PDN_LCD                                        (*( REGType8v *) REG_LCD_ADDR)

/* FCRAM */

#define REG_FCRAM_OFFSET                                   0x141210
#define REG_FCRAM_ADDR                                     (HW_REG_BASE + REG_FCRAM_OFFSET)
#define reg_PDN_FCRAM                                      (*( REGType8v *) REG_FCRAM_ADDR)

/* I2S */

#define REG_I2S_OFFSET                                     0x141220
#define REG_I2S_ADDR                                       (HW_REG_BASE + REG_I2S_OFFSET)
#define reg_PDN_I2S                                        (*( REGType8v *) REG_I2S_ADDR)

/* CAM */

#define REG_CAM_OFFSET                                     0x141224
#define REG_CAM_ADDR                                       (HW_REG_BASE + REG_CAM_OFFSET)
#define reg_PDN_CAM                                        (*( REGType8v *) REG_CAM_ADDR)

/* DSP */

#define REG_DSP_OFFSET                                     0x141230
#define REG_DSP_ADDR                                       (HW_REG_BASE + REG_DSP_OFFSET)
#define reg_PDN_DSP                                        (*( REGType8v *) REG_DSP_ADDR)

/* GS1 */

#define REG_GS1_OFFSET                                     0x141240
#define REG_GS1_ADDR                                       (HW_REG_BASE + REG_GS1_OFFSET)
#define reg_PDN_GS1                                        (*( REGType8v *) REG_GS1_ADDR)

/* LGR1 */

#define REG_LGR1_OFFSET                                    0x141300
#define REG_LGR1_ADDR                                      (HW_REG_BASE + REG_LGR1_OFFSET)
#define reg_PDN_LGR1                                       (*( REGType16v *) REG_LGR1_ADDR)

/* LGR2 */

#define REG_LGR2_OFFSET                                    0x141304
#define REG_LGR2_ADDR                                      (HW_REG_BASE + REG_LGR2_OFFSET)
#define reg_PDN_LGR2                                       (*( REGType8v *) REG_LGR2_ADDR)

/* LGR_CPU0 */

#define REG_LGR_CPU0_OFFSET                                0x141310
#define REG_LGR_CPU0_ADDR                                  (HW_REG_BASE + REG_LGR_CPU0_OFFSET)
#define reg_PDN_LGR_CPU0                                   (*( REGType8v *) REG_LGR_CPU0_ADDR)

/* LGR_CPU1 */

#define REG_LGR_CPU1_OFFSET                                0x141311
#define REG_LGR_CPU1_ADDR                                  (HW_REG_BASE + REG_LGR_CPU1_OFFSET)
#define reg_PDN_LGR_CPU1                                   (*( REGType8v *) REG_LGR_CPU1_ADDR)

/* LGR_CPU2 */

#define REG_LGR_CPU2_OFFSET                                0x141312
#define REG_LGR_CPU2_ADDR                                  (HW_REG_BASE + REG_LGR_CPU2_OFFSET)
#define reg_PDN_LGR_CPU2                                   (*( REGType8v *) REG_LGR_CPU2_ADDR)

/* LGR_CPU3 */

#define REG_LGR_CPU3_OFFSET                                0x141313
#define REG_LGR_CPU3_ADDR                                  (HW_REG_BASE + REG_LGR_CPU3_OFFSET)
#define reg_PDN_LGR_CPU3                                   (*( REGType8v *) REG_LGR_CPU3_ADDR)


/*
 * Definitions of Register fields
 */


/* CNT */

#define REG_PDN_CNT_VRAM_SHIFT                             15
#define REG_PDN_CNT_VRAM_SIZE                              1
#define REG_PDN_CNT_VRAM_MASK                              0x8000

#define REG_PDN_CNT_SLP_SHIFT                              0
#define REG_PDN_CNT_SLP_SIZE                               1
#define REG_PDN_CNT_SLP_MASK                               0x0001

#ifndef SDK_ASM
#define REG_PDN_CNT_FIELD( vram, slp ) \
    (u16)( \
    ((u32)(vram) << REG_PDN_CNT_VRAM_SHIFT) | \
    ((u32)(slp) << REG_PDN_CNT_SLP_SHIFT))
#endif


/* WE */

#define REG_PDN_WE_COVERB_SHIFT                            31
#define REG_PDN_WE_COVERB_SIZE                             1
#define REG_PDN_WE_COVERB_MASK                             0x80000000

#define REG_PDN_WE_TP_SHIFT                                30
#define REG_PDN_WE_TP_SIZE                                 1
#define REG_PDN_WE_TP_MASK                                 0x40000000

#define REG_PDN_WE_CGC_SHIFT                               29
#define REG_PDN_WE_CGC_SIZE                                1
#define REG_PDN_WE_CGC_MASK                                0x20000000

#define REG_PDN_WE_CTR_MCU_SHIFT                           26
#define REG_PDN_WE_CTR_MCU_SIZE                            1
#define REG_PDN_WE_CTR_MCU_MASK                            0x04000000

#define REG_PDN_WE_RMC_SHIFT                               25
#define REG_PDN_WE_RMC_SIZE                                1
#define REG_PDN_WE_RMC_MASK                                0x02000000

#define REG_PDN_WE_WL_RST_SHIFT                            18
#define REG_PDN_WE_WL_RST_SIZE                             1
#define REG_PDN_WE_WL_RST_MASK                             0x00040000

#define REG_PDN_WE_SP_SEL_SHIFT                            17
#define REG_PDN_WE_SP_SEL_SIZE                             1
#define REG_PDN_WE_SP_SEL_MASK                             0x00020000

#define REG_PDN_WE_GPIO3_18_3_SHIFT                        28
#define REG_PDN_WE_GPIO3_18_3_SIZE                         1
#define REG_PDN_WE_GPIO3_18_3_MASK                         0x10000000

#define REG_PDN_WE_GPIO3_18_2_SHIFT                        27
#define REG_PDN_WE_GPIO3_18_2_SIZE                         1
#define REG_PDN_WE_GPIO3_18_2_MASK                         0x08000000

#define REG_PDN_WE_GPIO3_18_1_SHIFT                        26
#define REG_PDN_WE_GPIO3_18_1_SIZE                         1
#define REG_PDN_WE_GPIO3_18_1_MASK                         0x04000000

#define REG_PDN_WE_GPIO3_18_0_SHIFT                        25
#define REG_PDN_WE_GPIO3_18_0_SIZE                         1
#define REG_PDN_WE_GPIO3_18_0_MASK                         0x02000000

#define REG_PDN_WE_GPIO3_33_7_SHIFT                        24
#define REG_PDN_WE_GPIO3_33_7_SIZE                         1
#define REG_PDN_WE_GPIO3_33_7_MASK                         0x01000000

#define REG_PDN_WE_GPIO3_33_6_SHIFT                        23
#define REG_PDN_WE_GPIO3_33_6_SIZE                         1
#define REG_PDN_WE_GPIO3_33_6_MASK                         0x00800000

#define REG_PDN_WE_GPIO3_33_5_SHIFT                        22
#define REG_PDN_WE_GPIO3_33_5_SIZE                         1
#define REG_PDN_WE_GPIO3_33_5_MASK                         0x00400000

#define REG_PDN_WE_GPIO3_33_4_SHIFT                        21
#define REG_PDN_WE_GPIO3_33_4_SIZE                         1
#define REG_PDN_WE_GPIO3_33_4_MASK                         0x00200000

#define REG_PDN_WE_GPIO3_33_3_SHIFT                        20
#define REG_PDN_WE_GPIO3_33_3_SIZE                         1
#define REG_PDN_WE_GPIO3_33_3_MASK                         0x00100000

#define REG_PDN_WE_GPIO3_33_2_SHIFT                        19
#define REG_PDN_WE_GPIO3_33_2_SIZE                         1
#define REG_PDN_WE_GPIO3_33_2_MASK                         0x00080000

#define REG_PDN_WE_GPIO3_33_1_SHIFT                        18
#define REG_PDN_WE_GPIO3_33_1_SIZE                         1
#define REG_PDN_WE_GPIO3_33_1_MASK                         0x00040000

#define REG_PDN_WE_GPIO3_33_0_SHIFT                        17
#define REG_PDN_WE_GPIO3_33_0_SIZE                         1
#define REG_PDN_WE_GPIO3_33_0_MASK                         0x00020000

#define REG_PDN_WE_SD3_SHIFT                               16
#define REG_PDN_WE_SD3_SIZE                                1
#define REG_PDN_WE_SD3_MASK                                0x00010000

#define REG_PDN_WE_SD2_SHIFT                               8
#define REG_PDN_WE_SD2_SIZE                                1
#define REG_PDN_WE_SD2_MASK                                0x00000100

#define REG_PDN_WE_SD1_SHIFT                               7
#define REG_PDN_WE_SD1_SIZE                                1
#define REG_PDN_WE_SD1_MASK                                0x00000080

#define REG_PDN_WE_TWL_DEPOP_SHIFT                         6
#define REG_PDN_WE_TWL_DEPOP_SIZE                          1
#define REG_PDN_WE_TWL_DEPOP_MASK                          0x00000040

#define REG_PDN_WE_HP_SHIFT                                4
#define REG_PDN_WE_HP_SIZE                                 1
#define REG_PDN_WE_HP_MASK                                 0x00000010

#define REG_PDN_WE_COVER_SHIFT                             3
#define REG_PDN_WE_COVER_SIZE                              1
#define REG_PDN_WE_COVER_MASK                              0x00000008

#define REG_PDN_WE_KEY_SHIFT                               1
#define REG_PDN_WE_KEY_SIZE                                1
#define REG_PDN_WE_KEY_MASK                                0x00000002

#ifndef SDK_ASM
#define REG_PDN_WE_FIELD( coverb, tp, cgc, ctr_mcu, rmc, wl_rst, sp_sel, gpio3_18_3, gpio3_18_2, gpio3_18_1, gpio3_18_0, gpio3_33_7, gpio3_33_6, gpio3_33_5, gpio3_33_4, gpio3_33_3, gpio3_33_2, gpio3_33_1, gpio3_33_0, sd3, sd2, sd1, twl_depop, hp, cover, key ) \
    (u32)( \
    ((u32)(coverb) << REG_PDN_WE_COVERB_SHIFT) | \
    ((u32)(tp) << REG_PDN_WE_TP_SHIFT) | \
    ((u32)(cgc) << REG_PDN_WE_CGC_SHIFT) | \
    ((u32)(ctr_mcu) << REG_PDN_WE_CTR_MCU_SHIFT) | \
    ((u32)(rmc) << REG_PDN_WE_RMC_SHIFT) | \
    ((u32)(wl_rst) << REG_PDN_WE_WL_RST_SHIFT) | \
    ((u32)(sp_sel) << REG_PDN_WE_SP_SEL_SHIFT) | \
    ((u32)(gpio3_18_3) << REG_PDN_WE_GPIO3_18_3_SHIFT) | \
    ((u32)(gpio3_18_2) << REG_PDN_WE_GPIO3_18_2_SHIFT) | \
    ((u32)(gpio3_18_1) << REG_PDN_WE_GPIO3_18_1_SHIFT) | \
    ((u32)(gpio3_18_0) << REG_PDN_WE_GPIO3_18_0_SHIFT) | \
    ((u32)(gpio3_33_7) << REG_PDN_WE_GPIO3_33_7_SHIFT) | \
    ((u32)(gpio3_33_6) << REG_PDN_WE_GPIO3_33_6_SHIFT) | \
    ((u32)(gpio3_33_5) << REG_PDN_WE_GPIO3_33_5_SHIFT) | \
    ((u32)(gpio3_33_4) << REG_PDN_WE_GPIO3_33_4_SHIFT) | \
    ((u32)(gpio3_33_3) << REG_PDN_WE_GPIO3_33_3_SHIFT) | \
    ((u32)(gpio3_33_2) << REG_PDN_WE_GPIO3_33_2_SHIFT) | \
    ((u32)(gpio3_33_1) << REG_PDN_WE_GPIO3_33_1_SHIFT) | \
    ((u32)(gpio3_33_0) << REG_PDN_WE_GPIO3_33_0_SHIFT) | \
    ((u32)(sd3) << REG_PDN_WE_SD3_SHIFT) | \
    ((u32)(sd2) << REG_PDN_WE_SD2_SHIFT) | \
    ((u32)(sd1) << REG_PDN_WE_SD1_SHIFT) | \
    ((u32)(twl_depop) << REG_PDN_WE_TWL_DEPOP_SHIFT) | \
    ((u32)(hp) << REG_PDN_WE_HP_SHIFT) | \
    ((u32)(cover) << REG_PDN_WE_COVER_SHIFT) | \
    ((u32)(key) << REG_PDN_WE_KEY_SHIFT))
#endif


/* WRS */

#define REG_PDN_WRS_COVERB_SHIFT                           31
#define REG_PDN_WRS_COVERB_SIZE                            1
#define REG_PDN_WRS_COVERB_MASK                            0x80000000

#define REG_PDN_WRS_TP_SHIFT                               30
#define REG_PDN_WRS_TP_SIZE                                1
#define REG_PDN_WRS_TP_MASK                                0x40000000

#define REG_PDN_WRS_CGC_SHIFT                              29
#define REG_PDN_WRS_CGC_SIZE                               1
#define REG_PDN_WRS_CGC_MASK                               0x20000000

#define REG_PDN_WRS_CTR_MCU_SHIFT                          26
#define REG_PDN_WRS_CTR_MCU_SIZE                           1
#define REG_PDN_WRS_CTR_MCU_MASK                           0x04000000

#define REG_PDN_WRS_RMC_SHIFT                              25
#define REG_PDN_WRS_RMC_SIZE                               1
#define REG_PDN_WRS_RMC_MASK                               0x02000000

#define REG_PDN_WRS_WL_RST_SHIFT                           18
#define REG_PDN_WRS_WL_RST_SIZE                            1
#define REG_PDN_WRS_WL_RST_MASK                            0x00040000

#define REG_PDN_WRS_SP_SEL_SHIFT                           17
#define REG_PDN_WRS_SP_SEL_SIZE                            1
#define REG_PDN_WRS_SP_SEL_MASK                            0x00020000

#define REG_PDN_WRS_GPIO3_18_3_SHIFT                       28
#define REG_PDN_WRS_GPIO3_18_3_SIZE                        1
#define REG_PDN_WRS_GPIO3_18_3_MASK                        0x10000000

#define REG_PDN_WRS_GPIO3_18_2_SHIFT                       27
#define REG_PDN_WRS_GPIO3_18_2_SIZE                        1
#define REG_PDN_WRS_GPIO3_18_2_MASK                        0x08000000

#define REG_PDN_WRS_GPIO3_18_1_SHIFT                       26
#define REG_PDN_WRS_GPIO3_18_1_SIZE                        1
#define REG_PDN_WRS_GPIO3_18_1_MASK                        0x04000000

#define REG_PDN_WRS_GPIO3_18_0_SHIFT                       25
#define REG_PDN_WRS_GPIO3_18_0_SIZE                        1
#define REG_PDN_WRS_GPIO3_18_0_MASK                        0x02000000

#define REG_PDN_WRS_GPIO3_33_7_SHIFT                       24
#define REG_PDN_WRS_GPIO3_33_7_SIZE                        1
#define REG_PDN_WRS_GPIO3_33_7_MASK                        0x01000000

#define REG_PDN_WRS_GPIO3_33_6_SHIFT                       23
#define REG_PDN_WRS_GPIO3_33_6_SIZE                        1
#define REG_PDN_WRS_GPIO3_33_6_MASK                        0x00800000

#define REG_PDN_WRS_GPIO3_33_5_SHIFT                       22
#define REG_PDN_WRS_GPIO3_33_5_SIZE                        1
#define REG_PDN_WRS_GPIO3_33_5_MASK                        0x00400000

#define REG_PDN_WRS_GPIO3_33_4_SHIFT                       21
#define REG_PDN_WRS_GPIO3_33_4_SIZE                        1
#define REG_PDN_WRS_GPIO3_33_4_MASK                        0x00200000

#define REG_PDN_WRS_GPIO3_33_3_SHIFT                       20
#define REG_PDN_WRS_GPIO3_33_3_SIZE                        1
#define REG_PDN_WRS_GPIO3_33_3_MASK                        0x00100000

#define REG_PDN_WRS_GPIO3_33_2_SHIFT                       19
#define REG_PDN_WRS_GPIO3_33_2_SIZE                        1
#define REG_PDN_WRS_GPIO3_33_2_MASK                        0x00080000

#define REG_PDN_WRS_GPIO3_33_1_SHIFT                       18
#define REG_PDN_WRS_GPIO3_33_1_SIZE                        1
#define REG_PDN_WRS_GPIO3_33_1_MASK                        0x00040000

#define REG_PDN_WRS_GPIO3_33_0_SHIFT                       17
#define REG_PDN_WRS_GPIO3_33_0_SIZE                        1
#define REG_PDN_WRS_GPIO3_33_0_MASK                        0x00020000

#define REG_PDN_WRS_SD3_SHIFT                              16
#define REG_PDN_WRS_SD3_SIZE                               1
#define REG_PDN_WRS_SD3_MASK                               0x00010000

#define REG_PDN_WRS_SD2_SHIFT                              8
#define REG_PDN_WRS_SD2_SIZE                               1
#define REG_PDN_WRS_SD2_MASK                               0x00000100

#define REG_PDN_WRS_SD1_SHIFT                              7
#define REG_PDN_WRS_SD1_SIZE                               1
#define REG_PDN_WRS_SD1_MASK                               0x00000080

#define REG_PDN_WRS_TWL_DEPOP_SHIFT                        6
#define REG_PDN_WRS_TWL_DEPOP_SIZE                         1
#define REG_PDN_WRS_TWL_DEPOP_MASK                         0x00000040

#define REG_PDN_WRS_HP_SHIFT                               4
#define REG_PDN_WRS_HP_SIZE                                1
#define REG_PDN_WRS_HP_MASK                                0x00000010

#define REG_PDN_WRS_COVER_SHIFT                            3
#define REG_PDN_WRS_COVER_SIZE                             1
#define REG_PDN_WRS_COVER_MASK                             0x00000008

#define REG_PDN_WRS_KEY_SHIFT                              1
#define REG_PDN_WRS_KEY_SIZE                               1
#define REG_PDN_WRS_KEY_MASK                               0x00000002

#ifndef SDK_ASM
#define REG_PDN_WRS_FIELD( coverb, tp, cgc, ctr_mcu, rmc, wl_rst, sp_sel, gpio3_18_3, gpio3_18_2, gpio3_18_1, gpio3_18_0, gpio3_33_7, gpio3_33_6, gpio3_33_5, gpio3_33_4, gpio3_33_3, gpio3_33_2, gpio3_33_1, gpio3_33_0, sd3, sd2, sd1, twl_depop, hp, cover, key ) \
    (u32)( \
    ((u32)(coverb) << REG_PDN_WRS_COVERB_SHIFT) | \
    ((u32)(tp) << REG_PDN_WRS_TP_SHIFT) | \
    ((u32)(cgc) << REG_PDN_WRS_CGC_SHIFT) | \
    ((u32)(ctr_mcu) << REG_PDN_WRS_CTR_MCU_SHIFT) | \
    ((u32)(rmc) << REG_PDN_WRS_RMC_SHIFT) | \
    ((u32)(wl_rst) << REG_PDN_WRS_WL_RST_SHIFT) | \
    ((u32)(sp_sel) << REG_PDN_WRS_SP_SEL_SHIFT) | \
    ((u32)(gpio3_18_3) << REG_PDN_WRS_GPIO3_18_3_SHIFT) | \
    ((u32)(gpio3_18_2) << REG_PDN_WRS_GPIO3_18_2_SHIFT) | \
    ((u32)(gpio3_18_1) << REG_PDN_WRS_GPIO3_18_1_SHIFT) | \
    ((u32)(gpio3_18_0) << REG_PDN_WRS_GPIO3_18_0_SHIFT) | \
    ((u32)(gpio3_33_7) << REG_PDN_WRS_GPIO3_33_7_SHIFT) | \
    ((u32)(gpio3_33_6) << REG_PDN_WRS_GPIO3_33_6_SHIFT) | \
    ((u32)(gpio3_33_5) << REG_PDN_WRS_GPIO3_33_5_SHIFT) | \
    ((u32)(gpio3_33_4) << REG_PDN_WRS_GPIO3_33_4_SHIFT) | \
    ((u32)(gpio3_33_3) << REG_PDN_WRS_GPIO3_33_3_SHIFT) | \
    ((u32)(gpio3_33_2) << REG_PDN_WRS_GPIO3_33_2_SHIFT) | \
    ((u32)(gpio3_33_1) << REG_PDN_WRS_GPIO3_33_1_SHIFT) | \
    ((u32)(gpio3_33_0) << REG_PDN_WRS_GPIO3_33_0_SHIFT) | \
    ((u32)(sd3) << REG_PDN_WRS_SD3_SHIFT) | \
    ((u32)(sd2) << REG_PDN_WRS_SD2_SHIFT) | \
    ((u32)(sd1) << REG_PDN_WRS_SD1_SHIFT) | \
    ((u32)(twl_depop) << REG_PDN_WRS_TWL_DEPOP_SHIFT) | \
    ((u32)(hp) << REG_PDN_WRS_HP_SHIFT) | \
    ((u32)(cover) << REG_PDN_WRS_COVER_SHIFT) | \
    ((u32)(key) << REG_PDN_WRS_KEY_SHIFT))
#endif


/* GPU */

#define REG_PDN_GPU_CLK_E_SHIFT                            16
#define REG_PDN_GPU_CLK_E_SIZE                             1
#define REG_PDN_GPU_CLK_E_MASK                             0x00010000

#define REG_PDN_GPU_RSTB_PDP_SHIFT                         6
#define REG_PDN_GPU_RSTB_PDP_SIZE                          1
#define REG_PDN_GPU_RSTB_PDP_MASK                          0x00000040

#define REG_PDN_GPU_RSTB_PDC_SHIFT                         5
#define REG_PDN_GPU_RSTB_PDC_SIZE                          1
#define REG_PDN_GPU_RSTB_PDC_MASK                          0x00000020

#define REG_PDN_GPU_RSTB_PPF_SHIFT                         4
#define REG_PDN_GPU_RSTB_PPF_SIZE                          1
#define REG_PDN_GPU_RSTB_PPF_MASK                          0x00000010

#define REG_PDN_GPU_RSTB_P3R_SHIFT                         3
#define REG_PDN_GPU_RSTB_P3R_SIZE                          1
#define REG_PDN_GPU_RSTB_P3R_MASK                          0x00000008

#define REG_PDN_GPU_RSTB_P3G_SHIFT                         2
#define REG_PDN_GPU_RSTB_P3G_SIZE                          1
#define REG_PDN_GPU_RSTB_P3G_MASK                          0x00000004

#define REG_PDN_GPU_RSTB_P3D_SHIFT                         1
#define REG_PDN_GPU_RSTB_P3D_SIZE                          1
#define REG_PDN_GPU_RSTB_P3D_MASK                          0x00000002

#define REG_PDN_GPU_RSTB_SYS_SHIFT                         0
#define REG_PDN_GPU_RSTB_SYS_SIZE                          1
#define REG_PDN_GPU_RSTB_SYS_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_PDN_GPU_FIELD( clk_e, rstb_pdp, rstb_pdc, rstb_ppf, rstb_p3r, rstb_p3g, rstb_p3d, rstb_sys ) \
    (u32)( \
    ((u32)(clk_e) << REG_PDN_GPU_CLK_E_SHIFT) | \
    ((u32)(rstb_pdp) << REG_PDN_GPU_RSTB_PDP_SHIFT) | \
    ((u32)(rstb_pdc) << REG_PDN_GPU_RSTB_PDC_SHIFT) | \
    ((u32)(rstb_ppf) << REG_PDN_GPU_RSTB_PPF_SHIFT) | \
    ((u32)(rstb_p3r) << REG_PDN_GPU_RSTB_P3R_SHIFT) | \
    ((u32)(rstb_p3g) << REG_PDN_GPU_RSTB_P3G_SHIFT) | \
    ((u32)(rstb_p3d) << REG_PDN_GPU_RSTB_P3D_SHIFT) | \
    ((u32)(rstb_sys) << REG_PDN_GPU_RSTB_SYS_SHIFT))
#endif


/* VRAM */

#define REG_PDN_VRAM_CLK_E_SHIFT                           0
#define REG_PDN_VRAM_CLK_E_SIZE                            1
#define REG_PDN_VRAM_CLK_E_MASK                            0x01

#ifndef SDK_ASM
#define REG_PDN_VRAM_FIELD( clk_e ) \
    (u8)( \
    ((u32)(clk_e) << REG_PDN_VRAM_CLK_E_SHIFT))
#endif


/* LCD */

#define REG_PDN_LCD_PM_LCDOFF_SHIFT                        0
#define REG_PDN_LCD_PM_LCDOFF_SIZE                         1
#define REG_PDN_LCD_PM_LCDOFF_MASK                         0x01

#ifndef SDK_ASM
#define REG_PDN_LCD_FIELD( pm_lcdoff ) \
    (u8)( \
    ((u32)(pm_lcdoff) << REG_PDN_LCD_PM_LCDOFF_SHIFT))
#endif


/* FCRAM */

#define REG_PDN_FCRAM_CLK_E_ACK_SHIFT                      2
#define REG_PDN_FCRAM_CLK_E_ACK_SIZE                       1
#define REG_PDN_FCRAM_CLK_E_ACK_MASK                       0x04

#define REG_PDN_FCRAM_CLK_E_REQ_SHIFT                      1
#define REG_PDN_FCRAM_CLK_E_REQ_SIZE                       1
#define REG_PDN_FCRAM_CLK_E_REQ_MASK                       0x02

#define REG_PDN_FCRAM_RSTB_SHIFT                           0
#define REG_PDN_FCRAM_RSTB_SIZE                            1
#define REG_PDN_FCRAM_RSTB_MASK                            0x01

#ifndef SDK_ASM
#define REG_PDN_FCRAM_FIELD( clk_e_ack, clk_e_req, rstb ) \
    (u8)( \
    ((u32)(clk_e_ack) << REG_PDN_FCRAM_CLK_E_ACK_SHIFT) | \
    ((u32)(clk_e_req) << REG_PDN_FCRAM_CLK_E_REQ_SHIFT) | \
    ((u32)(rstb) << REG_PDN_FCRAM_RSTB_SHIFT))
#endif


/* I2S */

#define REG_PDN_I2S_CLK2_E_SHIFT                           1
#define REG_PDN_I2S_CLK2_E_SIZE                            1
#define REG_PDN_I2S_CLK2_E_MASK                            0x02

#define REG_PDN_I2S_CLK1_E_SHIFT                           0
#define REG_PDN_I2S_CLK1_E_SIZE                            1
#define REG_PDN_I2S_CLK1_E_MASK                            0x01

#ifndef SDK_ASM
#define REG_PDN_I2S_FIELD( clk2_e, clk1_e ) \
    (u8)( \
    ((u32)(clk2_e) << REG_PDN_I2S_CLK2_E_SHIFT) | \
    ((u32)(clk1_e) << REG_PDN_I2S_CLK1_E_SHIFT))
#endif


/* CAM */

#define REG_PDN_CAM_CLK_E_SHIFT                            0
#define REG_PDN_CAM_CLK_E_SIZE                             1
#define REG_PDN_CAM_CLK_E_MASK                             0x01

#ifndef SDK_ASM
#define REG_PDN_CAM_FIELD( clk_e ) \
    (u8)( \
    ((u32)(clk_e) << REG_PDN_CAM_CLK_E_SHIFT))
#endif


/* DSP */

#define REG_PDN_DSP_CLK_E_SHIFT                            1
#define REG_PDN_DSP_CLK_E_SIZE                             1
#define REG_PDN_DSP_CLK_E_MASK                             0x02

#define REG_PDN_DSP_RSTB_SHIFT                             0
#define REG_PDN_DSP_RSTB_SIZE                              1
#define REG_PDN_DSP_RSTB_MASK                              0x01

#ifndef SDK_ASM
#define REG_PDN_DSP_FIELD( clk_e, rstb ) \
    (u8)( \
    ((u32)(clk_e) << REG_PDN_DSP_CLK_E_SHIFT) | \
    ((u32)(rstb) << REG_PDN_DSP_RSTB_SHIFT))
#endif


/* GS1 */

#define REG_PDN_GS1_RSTN_SHIFT                             0
#define REG_PDN_GS1_RSTN_SIZE                              1
#define REG_PDN_GS1_RSTN_MASK                              0x01

#ifndef SDK_ASM
#define REG_PDN_GS1_FIELD( rstn ) \
    (u8)( \
    ((u32)(rstn) << REG_PDN_GS1_RSTN_SHIFT))
#endif


/* LGR1 */

#define REG_PDN_LGR1_IF_SHIFT                              15
#define REG_PDN_LGR1_IF_SIZE                               1
#define REG_PDN_LGR1_IF_MASK                               0x8000

#define REG_PDN_LGR1_MODE_SEL_SHIFT                        0
#define REG_PDN_LGR1_MODE_SEL_SIZE                         3
#define REG_PDN_LGR1_MODE_SEL_MASK                         0x0007

#ifndef SDK_ASM
#define REG_PDN_LGR1_FIELD( if, mode_sel ) \
    (u16)( \
    ((u32)(if) << REG_PDN_LGR1_IF_SHIFT) | \
    ((u32)(mode_sel) << REG_PDN_LGR1_MODE_SEL_SHIFT))
#endif


/* LGR2 */

#define REG_PDN_LGR2_L2RAM_PDN_SHIFT                       8
#define REG_PDN_LGR2_L2RAM_PDN_SIZE                        1
#define REG_PDN_LGR2_L2RAM_PDN_MASK                        0x100

#define REG_PDN_LGR2_WRAM_PDN_SHIFT                        0
#define REG_PDN_LGR2_WRAM_PDN_SIZE                         1
#define REG_PDN_LGR2_WRAM_PDN_MASK                         0x01

#ifndef SDK_ASM
#define REG_PDN_LGR2_FIELD( l2ram_pdn, wram_pdn ) \
    (u8)( \
    ((u32)(l2ram_pdn) << REG_PDN_LGR2_L2RAM_PDN_SHIFT) | \
    ((u32)(wram_pdn) << REG_PDN_LGR2_WRAM_PDN_SHIFT))
#endif


/* LGR_CPU0 */

#define REG_PDN_LGR_CPU0_NLP_RDY_SHIFT                     5
#define REG_PDN_LGR_CPU0_NLP_RDY_SIZE                      1
#define REG_PDN_LGR_CPU0_NLP_RDY_MASK                      0x20

#define REG_PDN_LGR_CPU0_NRSTS_SHIFT                       4
#define REG_PDN_LGR_CPU0_NRSTS_SIZE                        1
#define REG_PDN_LGR_CPU0_NRSTS_MASK                        0x10

#ifndef SDK_ASM
#define REG_PDN_LGR_CPU0_FIELD( nlp_rdy, nrsts ) \
    (u8)( \
    ((u32)(nlp_rdy) << REG_PDN_LGR_CPU0_NLP_RDY_SHIFT) | \
    ((u32)(nrsts) << REG_PDN_LGR_CPU0_NRSTS_SHIFT))
#endif


/* LGR_CPU1 */

#define REG_PDN_LGR_CPU1_NLP_RDY_SHIFT                     5
#define REG_PDN_LGR_CPU1_NLP_RDY_SIZE                      1
#define REG_PDN_LGR_CPU1_NLP_RDY_MASK                      0x20

#define REG_PDN_LGR_CPU1_NRSTS_SHIFT                       4
#define REG_PDN_LGR_CPU1_NRSTS_SIZE                        1
#define REG_PDN_LGR_CPU1_NRSTS_MASK                        0x10

#ifndef SDK_ASM
#define REG_PDN_LGR_CPU1_FIELD( nlp_rdy, nrsts ) \
    (u8)( \
    ((u32)(nlp_rdy) << REG_PDN_LGR_CPU1_NLP_RDY_SHIFT) | \
    ((u32)(nrsts) << REG_PDN_LGR_CPU1_NRSTS_SHIFT))
#endif


/* LGR_CPU2 */

#define REG_PDN_LGR_CPU2_NLP_RDY_SHIFT                     5
#define REG_PDN_LGR_CPU2_NLP_RDY_SIZE                      1
#define REG_PDN_LGR_CPU2_NLP_RDY_MASK                      0x20

#define REG_PDN_LGR_CPU2_NRSTS_SHIFT                       4
#define REG_PDN_LGR_CPU2_NRSTS_SIZE                        1
#define REG_PDN_LGR_CPU2_NRSTS_MASK                        0x10

#define REG_PDN_LGR_CPU2_HI_SHIFT                          1
#define REG_PDN_LGR_CPU2_HI_SIZE                           1
#define REG_PDN_LGR_CPU2_HI_MASK                           0x02

#define REG_PDN_LGR_CPU2_NRST_SHIFT                        0
#define REG_PDN_LGR_CPU2_NRST_SIZE                         1
#define REG_PDN_LGR_CPU2_NRST_MASK                         0x01

#ifndef SDK_ASM
#define REG_PDN_LGR_CPU2_FIELD( nlp_rdy, nrsts, hi, nrst ) \
    (u8)( \
    ((u32)(nlp_rdy) << REG_PDN_LGR_CPU2_NLP_RDY_SHIFT) | \
    ((u32)(nrsts) << REG_PDN_LGR_CPU2_NRSTS_SHIFT) | \
    ((u32)(hi) << REG_PDN_LGR_CPU2_HI_SHIFT) | \
    ((u32)(nrst) << REG_PDN_LGR_CPU2_NRST_SHIFT))
#endif


/* LGR_CPU3 */

#define REG_PDN_LGR_CPU3_NLP_RDY_SHIFT                     5
#define REG_PDN_LGR_CPU3_NLP_RDY_SIZE                      1
#define REG_PDN_LGR_CPU3_NLP_RDY_MASK                      0x20

#define REG_PDN_LGR_CPU3_NRSTS_SHIFT                       4
#define REG_PDN_LGR_CPU3_NRSTS_SIZE                        1
#define REG_PDN_LGR_CPU3_NRSTS_MASK                        0x10

#define REG_PDN_LGR_CPU3_HI_SHIFT                          1
#define REG_PDN_LGR_CPU3_HI_SIZE                           1
#define REG_PDN_LGR_CPU3_HI_MASK                           0x02

#define REG_PDN_LGR_CPU3_NRST_SHIFT                        0
#define REG_PDN_LGR_CPU3_NRST_SIZE                         1
#define REG_PDN_LGR_CPU3_NRST_MASK                         0x01

#ifndef SDK_ASM
#define REG_PDN_LGR_CPU3_FIELD( nlp_rdy, nrsts, hi, nrst ) \
    (u8)( \
    ((u32)(nlp_rdy) << REG_PDN_LGR_CPU3_NLP_RDY_SHIFT) | \
    ((u32)(nrsts) << REG_PDN_LGR_CPU3_NRSTS_SHIFT) | \
    ((u32)(hi) << REG_PDN_LGR_CPU3_HI_SHIFT) | \
    ((u32)(nrst) << REG_PDN_LGR_CPU3_NRST_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_EIU_MPCORE_IOREG_EIUPATCH_PDN_H_ */
#endif
