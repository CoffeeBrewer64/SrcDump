/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/MPCore/ioreg_LGY.h

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
#ifndef NN_HW_CTR_TEG2_MPCORE_IOREG_LGY_H_
#define NN_HW_CTR_TEG2_MPCORE_IOREG_LGY_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* LMOD */

#define REG_LMOD_OFFSET                                    0x141100
#define REG_LMOD_ADDR                                      (HW_REG_BASE + REG_LMOD_OFFSET)
#define reg_LGY_LMOD                                       (*( REGType16v *) REG_LMOD_ADDR)

/* LSCNT */

#define REG_LSCNT_OFFSET                                   0x141104
#define REG_LSCNT_ADDR                                     (HW_REG_BASE + REG_LSCNT_OFFSET)
#define reg_LGY_LSCNT                                      (*( REGType16v *) REG_LSCNT_ADDR)

/* LIE */

#define REG_LIE_OFFSET                                     0x141108
#define REG_LIE_ADDR                                       (HW_REG_BASE + REG_LIE_OFFSET)
#define reg_LGY_LIE                                        (*( REGType16v *) REG_LIE_ADDR)

/* KEYMSEL */

#define REG_KEYMSEL_OFFSET                                 0x141110
#define REG_KEYMSEL_ADDR                                   (HW_REG_BASE + REG_KEYMSEL_OFFSET)
#define reg_LGY_KEYMSEL                                    (*( REGType16v *) REG_KEYMSEL_ADDR)

/* KEYMVAL */

#define REG_KEYMVAL_OFFSET                                 0x141112
#define REG_KEYMVAL_ADDR                                   (HW_REG_BASE + REG_KEYMVAL_OFFSET)
#define reg_LGY_KEYMVAL                                    (*( REGType16v *) REG_KEYMVAL_ADDR)

/* GPIOMSEL */

#define REG_GPIOMSEL_OFFSET                                0x141114
#define REG_GPIOMSEL_ADDR                                  (HW_REG_BASE + REG_GPIOMSEL_OFFSET)
#define reg_LGY_GPIOMSEL                                   (*( REGType16v *) REG_GPIOMSEL_ADDR)

/* GPIOMVAL */

#define REG_GPIOMVAL_OFFSET                                0x141116
#define REG_GPIOMVAL_ADDR                                  (HW_REG_BASE + REG_GPIOMVAL_OFFSET)
#define reg_LGY_GPIOMVAL                                   (*( REGType16v *) REG_GPIOMVAL_ADDR)

/* SCL1_CNT */

#define REG_SCL1_CNT_OFFSET                                0x110000
#define REG_SCL1_CNT_ADDR                                  (HW_REG_BASE + REG_SCL1_CNT_OFFSET)
#define reg_LGY_SCL1_CNT                                   (*( REGType32v *) REG_SCL1_CNT_ADDR)

/* SCL1_SIZE */

#define REG_SCL1_SIZE_OFFSET                               0x110004
#define REG_SCL1_SIZE_ADDR                                 (HW_REG_BASE + REG_SCL1_SIZE_OFFSET)
#define reg_LGY_SCL1_SIZE                                  (*( REGType32v *) REG_SCL1_SIZE_ADDR)

/* SCL1_STAT */

#define REG_SCL1_STAT_OFFSET                               0x110008
#define REG_SCL1_STAT_ADDR                                 (HW_REG_BASE + REG_SCL1_STAT_OFFSET)
#define reg_LGY_SCL1_STAT                                  (*( REGType32v *) REG_SCL1_STAT_ADDR)

/* SCL1_IFE */

#define REG_SCL1_IFE_OFFSET                                0x11000c
#define REG_SCL1_IFE_ADDR                                  (HW_REG_BASE + REG_SCL1_IFE_OFFSET)
#define reg_LGY_SCL1_IFE                                   (*( REGType32v *) REG_SCL1_IFE_ADDR)

/* SCL1_FLH */

#define REG_SCL1_FLH_OFFSET                                0x110010
#define REG_SCL1_FLH_ADDR                                  (HW_REG_BASE + REG_SCL1_FLH_OFFSET)
#define reg_LGY_SCL1_FLH                                   (*( REGType32v *) REG_SCL1_FLH_ADDR)

/* SCL1_ALPHA */

#define REG_SCL1_ALPHA_OFFSET                              0x110020
#define REG_SCL1_ALPHA_ADDR                                (HW_REG_BASE + REG_SCL1_ALPHA_OFFSET)
#define reg_LGY_SCL1_ALPHA                                 (*( REGType32v *) REG_SCL1_ALPHA_ADDR)

/* SCL1_DITPAT0 */

#define REG_SCL1_DITPAT0_OFFSET                            0x110100
#define REG_SCL1_DITPAT0_ADDR                              (HW_REG_BASE + REG_SCL1_DITPAT0_OFFSET)
#define reg_LGY_SCL1_DITPAT0                               (*( REGType32v *) REG_SCL1_DITPAT0_ADDR)

/* SCL1_DITPAT1 */

#define REG_SCL1_DITPAT1_OFFSET                            0x110108
#define REG_SCL1_DITPAT1_ADDR                              (HW_REG_BASE + REG_SCL1_DITPAT1_OFFSET)
#define reg_LGY_SCL1_DITPAT1                               (*( REGType32v *) REG_SCL1_DITPAT1_ADDR)

/* SCL1_VCYC */

#define REG_SCL1_VCYC_OFFSET                               0x110200
#define REG_SCL1_VCYC_ADDR                                 (HW_REG_BASE + REG_SCL1_VCYC_OFFSET)
#define reg_LGY_SCL1_VCYC                                  (*( REGType32v *) REG_SCL1_VCYC_ADDR)

/* SCL1_VADVPAT */

#define REG_SCL1_VADVPAT_OFFSET                            0x110204
#define REG_SCL1_VADVPAT_ADDR                              (HW_REG_BASE + REG_SCL1_VADVPAT_OFFSET)
#define reg_LGY_SCL1_VADVPAT                               (*( REGType32v *) REG_SCL1_VADVPAT_ADDR)

/* SCL1_VC00 */

#define REG_SCL1_VC00_OFFSET                               0x110240
#define REG_SCL1_VC00_ADDR                                 (HW_REG_BASE + REG_SCL1_VC00_OFFSET)
#define reg_LGY_SCL1_VC00                                  (*( REGType32v *) REG_SCL1_VC00_ADDR)

/* SCL1_VC10 */

#define REG_SCL1_VC10_OFFSET                               0x110260
#define REG_SCL1_VC10_ADDR                                 (HW_REG_BASE + REG_SCL1_VC10_OFFSET)
#define reg_LGY_SCL1_VC10                                  (*( REGType32v *) REG_SCL1_VC10_ADDR)

/* SCL1_VC20 */

#define REG_SCL1_VC20_OFFSET                               0x110280
#define REG_SCL1_VC20_ADDR                                 (HW_REG_BASE + REG_SCL1_VC20_OFFSET)
#define reg_LGY_SCL1_VC20                                  (*( REGType32v *) REG_SCL1_VC20_ADDR)

/* SCL1_VC30 */

#define REG_SCL1_VC30_OFFSET                               0x1102a0
#define REG_SCL1_VC30_ADDR                                 (HW_REG_BASE + REG_SCL1_VC30_OFFSET)
#define reg_LGY_SCL1_VC30                                  (*( REGType32v *) REG_SCL1_VC30_ADDR)

/* SCL1_VC40 */

#define REG_SCL1_VC40_OFFSET                               0x1102c0
#define REG_SCL1_VC40_ADDR                                 (HW_REG_BASE + REG_SCL1_VC40_OFFSET)
#define reg_LGY_SCL1_VC40                                  (*( REGType32v *) REG_SCL1_VC40_ADDR)

/* SCL1_VC50 */

#define REG_SCL1_VC50_OFFSET                               0x1102e0
#define REG_SCL1_VC50_ADDR                                 (HW_REG_BASE + REG_SCL1_VC50_OFFSET)
#define reg_LGY_SCL1_VC50                                  (*( REGType32v *) REG_SCL1_VC50_ADDR)

/* SCL1_HCYC */

#define REG_SCL1_HCYC_OFFSET                               0x110300
#define REG_SCL1_HCYC_ADDR                                 (HW_REG_BASE + REG_SCL1_HCYC_OFFSET)
#define reg_LGY_SCL1_HCYC                                  (*( REGType32v *) REG_SCL1_HCYC_ADDR)

/* SCL1_HADPAT */

#define REG_SCL1_HADPAT_OFFSET                             0x110304
#define REG_SCL1_HADPAT_ADDR                               (HW_REG_BASE + REG_SCL1_HADPAT_OFFSET)
#define reg_LGY_SCL1_HADPAT                                (*( REGType32v *) REG_SCL1_HADPAT_ADDR)

/* SCL1_HC00 */

#define REG_SCL1_HC00_OFFSET                               0x110340
#define REG_SCL1_HC00_ADDR                                 (HW_REG_BASE + REG_SCL1_HC00_OFFSET)
#define reg_LGY_SCL1_HC00                                  (*( REGType32v *) REG_SCL1_HC00_ADDR)

/* SCL1_HC10 */

#define REG_SCL1_HC10_OFFSET                               0x110360
#define REG_SCL1_HC10_ADDR                                 (HW_REG_BASE + REG_SCL1_HC10_OFFSET)
#define reg_LGY_SCL1_HC10                                  (*( REGType32v *) REG_SCL1_HC10_ADDR)

/* SCL1_HC20 */

#define REG_SCL1_HC20_OFFSET                               0x110380
#define REG_SCL1_HC20_ADDR                                 (HW_REG_BASE + REG_SCL1_HC20_OFFSET)
#define reg_LGY_SCL1_HC20                                  (*( REGType32v *) REG_SCL1_HC20_ADDR)

/* SCL1_HC30 */

#define REG_SCL1_HC30_OFFSET                               0x1103a0
#define REG_SCL1_HC30_ADDR                                 (HW_REG_BASE + REG_SCL1_HC30_OFFSET)
#define reg_LGY_SCL1_HC30                                  (*( REGType32v *) REG_SCL1_HC30_ADDR)

/* SCL1_HC40 */

#define REG_SCL1_HC40_OFFSET                               0x1103c0
#define REG_SCL1_HC40_ADDR                                 (HW_REG_BASE + REG_SCL1_HC40_OFFSET)
#define reg_LGY_SCL1_HC40                                  (*( REGType32v *) REG_SCL1_HC40_ADDR)

/* SCL1_HC50 */

#define REG_SCL1_HC50_OFFSET                               0x1103e0
#define REG_SCL1_HC50_ADDR                                 (HW_REG_BASE + REG_SCL1_HC50_OFFSET)
#define reg_LGY_SCL1_HC50                                  (*( REGType32v *) REG_SCL1_HC50_ADDR)

/* SCL1_DATA0 */

#define REG_SCL1_DATA0_OFFSET                              0x310000
#define REG_SCL1_DATA0_ADDR                                (HW_REG_BASE + REG_SCL1_DATA0_OFFSET)
#define reg_LGY_SCL1_DATA0                                 (*(const REGType32v *) REG_SCL1_DATA0_ADDR)

/* SCL2_CNT */

#define REG_SCL2_CNT_OFFSET                                0x111000
#define REG_SCL2_CNT_ADDR                                  (HW_REG_BASE + REG_SCL2_CNT_OFFSET)
#define reg_LGY_SCL2_CNT                                   (*( REGType32v *) REG_SCL2_CNT_ADDR)

/* SCL2_SIZE */

#define REG_SCL2_SIZE_OFFSET                               0x111004
#define REG_SCL2_SIZE_ADDR                                 (HW_REG_BASE + REG_SCL2_SIZE_OFFSET)
#define reg_LGY_SCL2_SIZE                                  (*( REGType32v *) REG_SCL2_SIZE_ADDR)

/* SCL2_STAT */

#define REG_SCL2_STAT_OFFSET                               0x111008
#define REG_SCL2_STAT_ADDR                                 (HW_REG_BASE + REG_SCL2_STAT_OFFSET)
#define reg_LGY_SCL2_STAT                                  (*( REGType32v *) REG_SCL2_STAT_ADDR)

/* SCL2_IFE */

#define REG_SCL2_IFE_OFFSET                                0x11100c
#define REG_SCL2_IFE_ADDR                                  (HW_REG_BASE + REG_SCL2_IFE_OFFSET)
#define reg_LGY_SCL2_IFE                                   (*( REGType32v *) REG_SCL2_IFE_ADDR)

/* SCL2_FLH */

#define REG_SCL2_FLH_OFFSET                                0x111010
#define REG_SCL2_FLH_ADDR                                  (HW_REG_BASE + REG_SCL2_FLH_OFFSET)
#define reg_LGY_SCL2_FLH                                   (*( REGType32v *) REG_SCL2_FLH_ADDR)

/* SCL2_ALPHA */

#define REG_SCL2_ALPHA_OFFSET                              0x111020
#define REG_SCL2_ALPHA_ADDR                                (HW_REG_BASE + REG_SCL2_ALPHA_OFFSET)
#define reg_LGY_SCL2_ALPHA                                 (*( REGType32v *) REG_SCL2_ALPHA_ADDR)

/* SCL2_DITPAT0 */

#define REG_SCL2_DITPAT0_OFFSET                            0x111100
#define REG_SCL2_DITPAT0_ADDR                              (HW_REG_BASE + REG_SCL2_DITPAT0_OFFSET)
#define reg_LGY_SCL2_DITPAT0                               (*( REGType32v *) REG_SCL2_DITPAT0_ADDR)

/* SCL2_DITPAT1 */

#define REG_SCL2_DITPAT1_OFFSET                            0x111108
#define REG_SCL2_DITPAT1_ADDR                              (HW_REG_BASE + REG_SCL2_DITPAT1_OFFSET)
#define reg_LGY_SCL2_DITPAT1                               (*( REGType32v *) REG_SCL2_DITPAT1_ADDR)

/* SCL2_VCYC */

#define REG_SCL2_VCYC_OFFSET                               0x111200
#define REG_SCL2_VCYC_ADDR                                 (HW_REG_BASE + REG_SCL2_VCYC_OFFSET)
#define reg_LGY_SCL2_VCYC                                  (*( REGType32v *) REG_SCL2_VCYC_ADDR)

/* SCL2_VADPAT */

#define REG_SCL2_VADPAT_OFFSET                             0x111204
#define REG_SCL2_VADPAT_ADDR                               (HW_REG_BASE + REG_SCL2_VADPAT_OFFSET)
#define reg_LGY_SCL2_VADPAT                                (*( REGType32v *) REG_SCL2_VADPAT_ADDR)

/* SCL2_VC00 */

#define REG_SCL2_VC00_OFFSET                               0x111240
#define REG_SCL2_VC00_ADDR                                 (HW_REG_BASE + REG_SCL2_VC00_OFFSET)
#define reg_LGY_SCL2_VC00                                  (*( REGType32v *) REG_SCL2_VC00_ADDR)

/* SCL2_VC10 */

#define REG_SCL2_VC10_OFFSET                               0x111260
#define REG_SCL2_VC10_ADDR                                 (HW_REG_BASE + REG_SCL2_VC10_OFFSET)
#define reg_LGY_SCL2_VC10                                  (*( REGType32v *) REG_SCL2_VC10_ADDR)

/* SCL2_VC20 */

#define REG_SCL2_VC20_OFFSET                               0x111280
#define REG_SCL2_VC20_ADDR                                 (HW_REG_BASE + REG_SCL2_VC20_OFFSET)
#define reg_LGY_SCL2_VC20                                  (*( REGType32v *) REG_SCL2_VC20_ADDR)

/* SCL2_VC30 */

#define REG_SCL2_VC30_OFFSET                               0x1112a0
#define REG_SCL2_VC30_ADDR                                 (HW_REG_BASE + REG_SCL2_VC30_OFFSET)
#define reg_LGY_SCL2_VC30                                  (*( REGType32v *) REG_SCL2_VC30_ADDR)

/* SCL2_VC40 */

#define REG_SCL2_VC40_OFFSET                               0x1112c0
#define REG_SCL2_VC40_ADDR                                 (HW_REG_BASE + REG_SCL2_VC40_OFFSET)
#define reg_LGY_SCL2_VC40                                  (*( REGType32v *) REG_SCL2_VC40_ADDR)

/* SCL2_VC50 */

#define REG_SCL2_VC50_OFFSET                               0x1112e0
#define REG_SCL2_VC50_ADDR                                 (HW_REG_BASE + REG_SCL2_VC50_OFFSET)
#define reg_LGY_SCL2_VC50                                  (*( REGType32v *) REG_SCL2_VC50_ADDR)

/* SCL2_HCYC */

#define REG_SCL2_HCYC_OFFSET                               0x111300
#define REG_SCL2_HCYC_ADDR                                 (HW_REG_BASE + REG_SCL2_HCYC_OFFSET)
#define reg_LGY_SCL2_HCYC                                  (*( REGType32v *) REG_SCL2_HCYC_ADDR)

/* SCL2_HADVPAT */

#define REG_SCL2_HADVPAT_OFFSET                            0x111304
#define REG_SCL2_HADVPAT_ADDR                              (HW_REG_BASE + REG_SCL2_HADVPAT_OFFSET)
#define reg_LGY_SCL2_HADVPAT                               (*( REGType32v *) REG_SCL2_HADVPAT_ADDR)

/* SCL2_HC00 */

#define REG_SCL2_HC00_OFFSET                               0x111340
#define REG_SCL2_HC00_ADDR                                 (HW_REG_BASE + REG_SCL2_HC00_OFFSET)
#define reg_LGY_SCL2_HC00                                  (*( REGType32v *) REG_SCL2_HC00_ADDR)

/* SCL2_HC10 */

#define REG_SCL2_HC10_OFFSET                               0x111360
#define REG_SCL2_HC10_ADDR                                 (HW_REG_BASE + REG_SCL2_HC10_OFFSET)
#define reg_LGY_SCL2_HC10                                  (*( REGType32v *) REG_SCL2_HC10_ADDR)

/* SCL2_HC20 */

#define REG_SCL2_HC20_OFFSET                               0x111380
#define REG_SCL2_HC20_ADDR                                 (HW_REG_BASE + REG_SCL2_HC20_OFFSET)
#define reg_LGY_SCL2_HC20                                  (*( REGType32v *) REG_SCL2_HC20_ADDR)

/* SCL2_HC30 */

#define REG_SCL2_HC30_OFFSET                               0x1113a0
#define REG_SCL2_HC30_ADDR                                 (HW_REG_BASE + REG_SCL2_HC30_OFFSET)
#define reg_LGY_SCL2_HC30                                  (*( REGType32v *) REG_SCL2_HC30_ADDR)

/* SCL2_HC40 */

#define REG_SCL2_HC40_OFFSET                               0x1113c0
#define REG_SCL2_HC40_ADDR                                 (HW_REG_BASE + REG_SCL2_HC40_OFFSET)
#define reg_LGY_SCL2_HC40                                  (*( REGType32v *) REG_SCL2_HC40_ADDR)

/* SCL2_HC50 */

#define REG_SCL2_HC50_OFFSET                               0x1113e0
#define REG_SCL2_HC50_ADDR                                 (HW_REG_BASE + REG_SCL2_HC50_OFFSET)
#define reg_LGY_SCL2_HC50                                  (*( REGType32v *) REG_SCL2_HC50_ADDR)

/* SCL2_DATA0 */

#define REG_SCL2_DATA0_OFFSET                              0x311000
#define REG_SCL2_DATA0_ADDR                                (HW_REG_BASE + REG_SCL2_DATA0_OFFSET)
#define reg_LGY_SCL2_DATA0                                 (*(const REGType32v *) REG_SCL2_DATA0_ADDR)


/*
 * Definitions of Register fields
 */


/* LMOD */

#define REG_LGY_LMOD_E_SHIFT                               15
#define REG_LGY_LMOD_E_SIZE                                1
#define REG_LGY_LMOD_E_MASK                                0x8000

#define REG_LGY_LMOD_M_SHIFT                               0
#define REG_LGY_LMOD_M_SIZE                                2
#define REG_LGY_LMOD_M_MASK                                0x0003

#ifndef SDK_ASM
#define REG_LGY_LMOD_FIELD( e, m ) \
    (u16)( \
    ((u32)(e) << REG_LGY_LMOD_E_SHIFT) | \
    ((u32)(m) << REG_LGY_LMOD_M_SHIFT))
#endif


/* LSCNT */

#define REG_LGY_LSCNT_I_SHIFT                              15
#define REG_LGY_LSCNT_I_SIZE                               1
#define REG_LGY_LSCNT_I_MASK                               0x8000

#define REG_LGY_LSCNT_R10_SHIFT                            2
#define REG_LGY_LSCNT_R10_SIZE                             1
#define REG_LGY_LSCNT_R10_MASK                             0x0004

#define REG_LGY_LSCNT_SLP_SHIFT                            1
#define REG_LGY_LSCNT_SLP_SIZE                             1
#define REG_LGY_LSCNT_SLP_MASK                             0x0002

#define REG_LGY_LSCNT_WUP_SHIFT                            0
#define REG_LGY_LSCNT_WUP_SIZE                             1
#define REG_LGY_LSCNT_WUP_MASK                             0x0001

#ifndef SDK_ASM
#define REG_LGY_LSCNT_FIELD( i, r10, slp, wup ) \
    (u16)( \
    ((u32)(i) << REG_LGY_LSCNT_I_SHIFT) | \
    ((u32)(r10) << REG_LGY_LSCNT_R10_SHIFT) | \
    ((u32)(slp) << REG_LGY_LSCNT_SLP_SHIFT) | \
    ((u32)(wup) << REG_LGY_LSCNT_WUP_SHIFT))
#endif


/* LIE */

#define REG_LGY_LIE_SD2_SHIFT                              8
#define REG_LGY_LIE_SD2_SIZE                               1
#define REG_LGY_LIE_SD2_MASK                               0x0100

#define REG_LGY_LIE_SD1_SHIFT                              7
#define REG_LGY_LIE_SD1_SIZE                               1
#define REG_LGY_LIE_SD1_MASK                               0x0080

#define REG_LGY_LIE_TWL_DEPOP_SHIFT                        6
#define REG_LGY_LIE_TWL_DEPOP_SIZE                         1
#define REG_LGY_LIE_TWL_DEPOP_MASK                         0x0040

#define REG_LGY_LIE_TWL_MCU_SHIFT                          5
#define REG_LGY_LIE_TWL_MCU_SIZE                           1
#define REG_LGY_LIE_TWL_MCU_MASK                           0x0020

#define REG_LGY_LIE_HP_SHIFT                               4
#define REG_LGY_LIE_HP_SIZE                                1
#define REG_LGY_LIE_HP_MASK                                0x0010

#define REG_LGY_LIE_COVER_SHIFT                            3
#define REG_LGY_LIE_COVER_SIZE                             1
#define REG_LGY_LIE_COVER_MASK                             0x0008

#define REG_LGY_LIE_LMC_SHIFT                              2
#define REG_LGY_LIE_LMC_SIZE                               1
#define REG_LGY_LIE_LMC_MASK                               0x0004

#define REG_LGY_LIE_KEY_SHIFT                              1
#define REG_LGY_LIE_KEY_SIZE                               1
#define REG_LGY_LIE_KEY_MASK                               0x0002

#define REG_LGY_LIE_RTC_SHIFT                              0
#define REG_LGY_LIE_RTC_SIZE                               1
#define REG_LGY_LIE_RTC_MASK                               0x0001

#ifndef SDK_ASM
#define REG_LGY_LIE_FIELD( sd2, sd1, twl_depop, twl_mcu, hp, cover, lmc, key, rtc ) \
    (u16)( \
    ((u32)(sd2) << REG_LGY_LIE_SD2_SHIFT) | \
    ((u32)(sd1) << REG_LGY_LIE_SD1_SHIFT) | \
    ((u32)(twl_depop) << REG_LGY_LIE_TWL_DEPOP_SHIFT) | \
    ((u32)(twl_mcu) << REG_LGY_LIE_TWL_MCU_SHIFT) | \
    ((u32)(hp) << REG_LGY_LIE_HP_SHIFT) | \
    ((u32)(cover) << REG_LGY_LIE_COVER_SHIFT) | \
    ((u32)(lmc) << REG_LGY_LIE_LMC_SHIFT) | \
    ((u32)(key) << REG_LGY_LIE_KEY_SHIFT) | \
    ((u32)(rtc) << REG_LGY_LIE_RTC_SHIFT))
#endif


/* KEYMSEL */

#define REG_LGY_KEYMSEL_X_SHIFT                            11
#define REG_LGY_KEYMSEL_X_SIZE                             1
#define REG_LGY_KEYMSEL_X_MASK                             0x0800

#define REG_LGY_KEYMSEL_Y_SHIFT                            10
#define REG_LGY_KEYMSEL_Y_SIZE                             1
#define REG_LGY_KEYMSEL_Y_MASK                             0x0400

#define REG_LGY_KEYMSEL_L_SHIFT                            9
#define REG_LGY_KEYMSEL_L_SIZE                             1
#define REG_LGY_KEYMSEL_L_MASK                             0x0200

#define REG_LGY_KEYMSEL_R_SHIFT                            8
#define REG_LGY_KEYMSEL_R_SIZE                             1
#define REG_LGY_KEYMSEL_R_MASK                             0x0100

#define REG_LGY_KEYMSEL_DOWN_SHIFT                         7
#define REG_LGY_KEYMSEL_DOWN_SIZE                          1
#define REG_LGY_KEYMSEL_DOWN_MASK                          0x0080

#define REG_LGY_KEYMSEL_UP_SHIFT                           6
#define REG_LGY_KEYMSEL_UP_SIZE                            1
#define REG_LGY_KEYMSEL_UP_MASK                            0x0040

#define REG_LGY_KEYMSEL_LEFT_SHIFT                         5
#define REG_LGY_KEYMSEL_LEFT_SIZE                          1
#define REG_LGY_KEYMSEL_LEFT_MASK                          0x0020

#define REG_LGY_KEYMSEL_RIGHT_SHIFT                        4
#define REG_LGY_KEYMSEL_RIGHT_SIZE                         1
#define REG_LGY_KEYMSEL_RIGHT_MASK                         0x0010

#define REG_LGY_KEYMSEL_START_SHIFT                        3
#define REG_LGY_KEYMSEL_START_SIZE                         1
#define REG_LGY_KEYMSEL_START_MASK                         0x0008

#define REG_LGY_KEYMSEL_SEL_SHIFT                          2
#define REG_LGY_KEYMSEL_SEL_SIZE                           1
#define REG_LGY_KEYMSEL_SEL_MASK                           0x0004

#define REG_LGY_KEYMSEL_B_SHIFT                            1
#define REG_LGY_KEYMSEL_B_SIZE                             1
#define REG_LGY_KEYMSEL_B_MASK                             0x0002

#define REG_LGY_KEYMSEL_A_SHIFT                            0
#define REG_LGY_KEYMSEL_A_SIZE                             1
#define REG_LGY_KEYMSEL_A_MASK                             0x0001

#ifndef SDK_ASM
#define REG_LGY_KEYMSEL_FIELD( x, y, l, r, down, up, left, right, start, sel, b, a ) \
    (u16)( \
    ((u32)(x) << REG_LGY_KEYMSEL_X_SHIFT) | \
    ((u32)(y) << REG_LGY_KEYMSEL_Y_SHIFT) | \
    ((u32)(l) << REG_LGY_KEYMSEL_L_SHIFT) | \
    ((u32)(r) << REG_LGY_KEYMSEL_R_SHIFT) | \
    ((u32)(down) << REG_LGY_KEYMSEL_DOWN_SHIFT) | \
    ((u32)(up) << REG_LGY_KEYMSEL_UP_SHIFT) | \
    ((u32)(left) << REG_LGY_KEYMSEL_LEFT_SHIFT) | \
    ((u32)(right) << REG_LGY_KEYMSEL_RIGHT_SHIFT) | \
    ((u32)(start) << REG_LGY_KEYMSEL_START_SHIFT) | \
    ((u32)(sel) << REG_LGY_KEYMSEL_SEL_SHIFT) | \
    ((u32)(b) << REG_LGY_KEYMSEL_B_SHIFT) | \
    ((u32)(a) << REG_LGY_KEYMSEL_A_SHIFT))
#endif


/* KEYMVAL */

#define REG_LGY_KEYMVAL_X_SHIFT                            11
#define REG_LGY_KEYMVAL_X_SIZE                             1
#define REG_LGY_KEYMVAL_X_MASK                             0x0800

#define REG_LGY_KEYMVAL_Y_SHIFT                            10
#define REG_LGY_KEYMVAL_Y_SIZE                             1
#define REG_LGY_KEYMVAL_Y_MASK                             0x0400

#define REG_LGY_KEYMVAL_L_SHIFT                            9
#define REG_LGY_KEYMVAL_L_SIZE                             1
#define REG_LGY_KEYMVAL_L_MASK                             0x0200

#define REG_LGY_KEYMVAL_R_SHIFT                            8
#define REG_LGY_KEYMVAL_R_SIZE                             1
#define REG_LGY_KEYMVAL_R_MASK                             0x0100

#define REG_LGY_KEYMVAL_DOWN_SHIFT                         7
#define REG_LGY_KEYMVAL_DOWN_SIZE                          1
#define REG_LGY_KEYMVAL_DOWN_MASK                          0x0080

#define REG_LGY_KEYMVAL_UP_SHIFT                           6
#define REG_LGY_KEYMVAL_UP_SIZE                            1
#define REG_LGY_KEYMVAL_UP_MASK                            0x0040

#define REG_LGY_KEYMVAL_LEFT_SHIFT                         5
#define REG_LGY_KEYMVAL_LEFT_SIZE                          1
#define REG_LGY_KEYMVAL_LEFT_MASK                          0x0020

#define REG_LGY_KEYMVAL_RIGHT_SHIFT                        4
#define REG_LGY_KEYMVAL_RIGHT_SIZE                         1
#define REG_LGY_KEYMVAL_RIGHT_MASK                         0x0010

#define REG_LGY_KEYMVAL_START_SHIFT                        3
#define REG_LGY_KEYMVAL_START_SIZE                         1
#define REG_LGY_KEYMVAL_START_MASK                         0x0008

#define REG_LGY_KEYMVAL_SEL_SHIFT                          2
#define REG_LGY_KEYMVAL_SEL_SIZE                           1
#define REG_LGY_KEYMVAL_SEL_MASK                           0x0004

#define REG_LGY_KEYMVAL_B_SHIFT                            1
#define REG_LGY_KEYMVAL_B_SIZE                             1
#define REG_LGY_KEYMVAL_B_MASK                             0x0002

#define REG_LGY_KEYMVAL_A_SHIFT                            0
#define REG_LGY_KEYMVAL_A_SIZE                             1
#define REG_LGY_KEYMVAL_A_MASK                             0x0001

#ifndef SDK_ASM
#define REG_LGY_KEYMVAL_FIELD( x, y, l, r, down, up, left, right, start, sel, b, a ) \
    (u16)( \
    ((u32)(x) << REG_LGY_KEYMVAL_X_SHIFT) | \
    ((u32)(y) << REG_LGY_KEYMVAL_Y_SHIFT) | \
    ((u32)(l) << REG_LGY_KEYMVAL_L_SHIFT) | \
    ((u32)(r) << REG_LGY_KEYMVAL_R_SHIFT) | \
    ((u32)(down) << REG_LGY_KEYMVAL_DOWN_SHIFT) | \
    ((u32)(up) << REG_LGY_KEYMVAL_UP_SHIFT) | \
    ((u32)(left) << REG_LGY_KEYMVAL_LEFT_SHIFT) | \
    ((u32)(right) << REG_LGY_KEYMVAL_RIGHT_SHIFT) | \
    ((u32)(start) << REG_LGY_KEYMVAL_START_SHIFT) | \
    ((u32)(sel) << REG_LGY_KEYMVAL_SEL_SHIFT) | \
    ((u32)(b) << REG_LGY_KEYMVAL_B_SHIFT) | \
    ((u32)(a) << REG_LGY_KEYMVAL_A_SHIFT))
#endif


/* GPIOMSEL */

#define REG_LGY_GPIOMSEL_TWL_DEPOP_SHIFT                   9
#define REG_LGY_GPIOMSEL_TWL_DEPOP_SIZE                    1
#define REG_LGY_GPIOMSEL_TWL_DEPOP_MASK                    0x0200

#define REG_LGY_GPIOMSEL_TWL_MCU_SHIFT                     8
#define REG_LGY_GPIOMSEL_TWL_MCU_SIZE                      1
#define REG_LGY_GPIOMSEL_TWL_MCU_MASK                      0x0100

#define REG_LGY_GPIOMSEL_HP_SHIFT                          7
#define REG_LGY_GPIOMSEL_HP_SIZE                           1
#define REG_LGY_GPIOMSEL_HP_MASK                           0x0080

#define REG_LGY_GPIOMSEL_RTC_INT_SHIFT                     6
#define REG_LGY_GPIOMSEL_RTC_INT_SIZE                      1
#define REG_LGY_GPIOMSEL_RTC_INT_MASK                      0x0040

#define REG_LGY_GPIOMSEL_RTC_CS_SHIFT                      5
#define REG_LGY_GPIOMSEL_RTC_CS_SIZE                       1
#define REG_LGY_GPIOMSEL_RTC_CS_MASK                       0x0020

#define REG_LGY_GPIOMSEL_RTC_CK_SHIFT                      4
#define REG_LGY_GPIOMSEL_RTC_CK_SIZE                       1
#define REG_LGY_GPIOMSEL_RTC_CK_MASK                       0x0010

#define REG_LGY_GPIOMSEL_RTC_DT_SHIFT                      3
#define REG_LGY_GPIOMSEL_RTC_DT_SIZE                       1
#define REG_LGY_GPIOMSEL_RTC_DT_MASK                       0x0008

#define REG_LGY_GPIOMSEL_COVER_SHIFT                       2
#define REG_LGY_GPIOMSEL_COVER_SIZE                        1
#define REG_LGY_GPIOMSEL_COVER_MASK                        0x0004

#define REG_LGY_GPIOMSEL_TP_SHIFT                          1
#define REG_LGY_GPIOMSEL_TP_SIZE                           1
#define REG_LGY_GPIOMSEL_TP_MASK                           0x0002

#define REG_LGY_GPIOMSEL_DBG_KEY_SHIFT                     0
#define REG_LGY_GPIOMSEL_DBG_KEY_SIZE                      1
#define REG_LGY_GPIOMSEL_DBG_KEY_MASK                      0x0001

#ifndef SDK_ASM
#define REG_LGY_GPIOMSEL_FIELD( twl_depop, twl_mcu, hp, rtc_int, rtc_cs, rtc_ck, rtc_dt, cover, tp, dbg_key ) \
    (u16)( \
    ((u32)(twl_depop) << REG_LGY_GPIOMSEL_TWL_DEPOP_SHIFT) | \
    ((u32)(twl_mcu) << REG_LGY_GPIOMSEL_TWL_MCU_SHIFT) | \
    ((u32)(hp) << REG_LGY_GPIOMSEL_HP_SHIFT) | \
    ((u32)(rtc_int) << REG_LGY_GPIOMSEL_RTC_INT_SHIFT) | \
    ((u32)(rtc_cs) << REG_LGY_GPIOMSEL_RTC_CS_SHIFT) | \
    ((u32)(rtc_ck) << REG_LGY_GPIOMSEL_RTC_CK_SHIFT) | \
    ((u32)(rtc_dt) << REG_LGY_GPIOMSEL_RTC_DT_SHIFT) | \
    ((u32)(cover) << REG_LGY_GPIOMSEL_COVER_SHIFT) | \
    ((u32)(tp) << REG_LGY_GPIOMSEL_TP_SHIFT) | \
    ((u32)(dbg_key) << REG_LGY_GPIOMSEL_DBG_KEY_SHIFT))
#endif


/* GPIOMVAL */

#define REG_LGY_GPIOMVAL_TWL_DEPOP_SHIFT                   9
#define REG_LGY_GPIOMVAL_TWL_DEPOP_SIZE                    1
#define REG_LGY_GPIOMVAL_TWL_DEPOP_MASK                    0x0200

#define REG_LGY_GPIOMVAL_TWL_MCU_SHIFT                     8
#define REG_LGY_GPIOMVAL_TWL_MCU_SIZE                      1
#define REG_LGY_GPIOMVAL_TWL_MCU_MASK                      0x0100

#define REG_LGY_GPIOMVAL_HP_SHIFT                          7
#define REG_LGY_GPIOMVAL_HP_SIZE                           1
#define REG_LGY_GPIOMVAL_HP_MASK                           0x0080

#define REG_LGY_GPIOMVAL_RTC_INT_SHIFT                     6
#define REG_LGY_GPIOMVAL_RTC_INT_SIZE                      1
#define REG_LGY_GPIOMVAL_RTC_INT_MASK                      0x0040

#define REG_LGY_GPIOMVAL_RTC_CS_SHIFT                      5
#define REG_LGY_GPIOMVAL_RTC_CS_SIZE                       1
#define REG_LGY_GPIOMVAL_RTC_CS_MASK                       0x0020

#define REG_LGY_GPIOMVAL_RTC_CK_SHIFT                      4
#define REG_LGY_GPIOMVAL_RTC_CK_SIZE                       1
#define REG_LGY_GPIOMVAL_RTC_CK_MASK                       0x0010

#define REG_LGY_GPIOMVAL_RTC_DT_SHIFT                      3
#define REG_LGY_GPIOMVAL_RTC_DT_SIZE                       1
#define REG_LGY_GPIOMVAL_RTC_DT_MASK                       0x0008

#define REG_LGY_GPIOMVAL_COVER_SHIFT                       2
#define REG_LGY_GPIOMVAL_COVER_SIZE                        1
#define REG_LGY_GPIOMVAL_COVER_MASK                        0x0004

#define REG_LGY_GPIOMVAL_TP_SHIFT                          1
#define REG_LGY_GPIOMVAL_TP_SIZE                           1
#define REG_LGY_GPIOMVAL_TP_MASK                           0x0002

#define REG_LGY_GPIOMVAL_DBG_KEY_SHIFT                     0
#define REG_LGY_GPIOMVAL_DBG_KEY_SIZE                      1
#define REG_LGY_GPIOMVAL_DBG_KEY_MASK                      0x0001

#ifndef SDK_ASM
#define REG_LGY_GPIOMVAL_FIELD( twl_depop, twl_mcu, hp, rtc_int, rtc_cs, rtc_ck, rtc_dt, cover, tp, dbg_key ) \
    (u16)( \
    ((u32)(twl_depop) << REG_LGY_GPIOMVAL_TWL_DEPOP_SHIFT) | \
    ((u32)(twl_mcu) << REG_LGY_GPIOMVAL_TWL_MCU_SHIFT) | \
    ((u32)(hp) << REG_LGY_GPIOMVAL_HP_SHIFT) | \
    ((u32)(rtc_int) << REG_LGY_GPIOMVAL_RTC_INT_SHIFT) | \
    ((u32)(rtc_cs) << REG_LGY_GPIOMVAL_RTC_CS_SHIFT) | \
    ((u32)(rtc_ck) << REG_LGY_GPIOMVAL_RTC_CK_SHIFT) | \
    ((u32)(rtc_dt) << REG_LGY_GPIOMVAL_RTC_DT_SHIFT) | \
    ((u32)(cover) << REG_LGY_GPIOMVAL_COVER_SHIFT) | \
    ((u32)(tp) << REG_LGY_GPIOMVAL_TP_SHIFT) | \
    ((u32)(dbg_key) << REG_LGY_GPIOMVAL_DBG_KEY_SHIFT))
#endif


/* SCL1_CNT */

#define REG_LGY_SCL1_CNT_DREQ_E_SHIFT                      15
#define REG_LGY_SCL1_CNT_DREQ_E_SIZE                       1
#define REG_LGY_SCL1_CNT_DREQ_E_MASK                       0x00008000

#define REG_LGY_SCL1_CNT_BF_SHIFT                          12
#define REG_LGY_SCL1_CNT_BF_SIZE                           1
#define REG_LGY_SCL1_CNT_BF_MASK                           0x00001000

#define REG_LGY_SCL1_CNT_ROT_SHIFT                         10
#define REG_LGY_SCL1_CNT_ROT_SIZE                          2
#define REG_LGY_SCL1_CNT_ROT_MASK                          0x00000c00

#define REG_LGY_SCL1_CNT_PF_SHIFT                          8
#define REG_LGY_SCL1_CNT_PF_SIZE                           2
#define REG_LGY_SCL1_CNT_PF_MASK                           0x00000300

#define REG_LGY_SCL1_CNT_TD_E_SHIFT                        5
#define REG_LGY_SCL1_CNT_TD_E_SIZE                         1
#define REG_LGY_SCL1_CNT_TD_E_MASK                         0x00000020

#define REG_LGY_SCL1_CNT_SD_E_SHIFT                        4
#define REG_LGY_SCL1_CNT_SD_E_SIZE                         1
#define REG_LGY_SCL1_CNT_SD_E_MASK                         0x00000010

#define REG_LGY_SCL1_CNT_H_E_SHIFT                         2
#define REG_LGY_SCL1_CNT_H_E_SIZE                          1
#define REG_LGY_SCL1_CNT_H_E_MASK                          0x00000004

#define REG_LGY_SCL1_CNT_V_E_SHIFT                         1
#define REG_LGY_SCL1_CNT_V_E_SIZE                          1
#define REG_LGY_SCL1_CNT_V_E_MASK                          0x00000002

#define REG_LGY_SCL1_CNT_E_SHIFT                           0
#define REG_LGY_SCL1_CNT_E_SIZE                            1
#define REG_LGY_SCL1_CNT_E_MASK                            0x00000001

#ifndef SDK_ASM
#define REG_LGY_SCL1_CNT_FIELD( dreq_e, bf, rot, pf, td_e, sd_e, h_e, v_e, e ) \
    (u32)( \
    ((u32)(dreq_e) << REG_LGY_SCL1_CNT_DREQ_E_SHIFT) | \
    ((u32)(bf) << REG_LGY_SCL1_CNT_BF_SHIFT) | \
    ((u32)(rot) << REG_LGY_SCL1_CNT_ROT_SHIFT) | \
    ((u32)(pf) << REG_LGY_SCL1_CNT_PF_SHIFT) | \
    ((u32)(td_e) << REG_LGY_SCL1_CNT_TD_E_SHIFT) | \
    ((u32)(sd_e) << REG_LGY_SCL1_CNT_SD_E_SHIFT) | \
    ((u32)(h_e) << REG_LGY_SCL1_CNT_H_E_SHIFT) | \
    ((u32)(v_e) << REG_LGY_SCL1_CNT_V_E_SHIFT) | \
    ((u32)(e) << REG_LGY_SCL1_CNT_E_SHIFT))
#endif


/* SCL1_SIZE */

#define REG_LGY_SCL1_SIZE_V_SHIFT                          16
#define REG_LGY_SCL1_SIZE_V_SIZE                           9
#define REG_LGY_SCL1_SIZE_V_MASK                           0x01ff0000

#define REG_LGY_SCL1_SIZE_H_SHIFT                          0
#define REG_LGY_SCL1_SIZE_H_SIZE                           9
#define REG_LGY_SCL1_SIZE_H_MASK                           0x000001ff

#ifndef SDK_ASM
#define REG_LGY_SCL1_SIZE_FIELD( v, h ) \
    (u32)( \
    ((u32)(v) << REG_LGY_SCL1_SIZE_V_SHIFT) | \
    ((u32)(h) << REG_LGY_SCL1_SIZE_H_SHIFT))
#endif


/* SCL1_STAT */

#define REG_LGY_SCL1_STAT_IF_VDET_SHIFT                    2
#define REG_LGY_SCL1_STAT_IF_VDET_SIZE                     1
#define REG_LGY_SCL1_STAT_IF_VDET_MASK                     0x00000004

#define REG_LGY_SCL1_STAT_IF_BERR_SHIFT                    1
#define REG_LGY_SCL1_STAT_IF_BERR_SIZE                     1
#define REG_LGY_SCL1_STAT_IF_BERR_MASK                     0x00000002

#define REG_LGY_SCL1_STAT_IF_DREQ_SHIFT                    0
#define REG_LGY_SCL1_STAT_IF_DREQ_SIZE                     1
#define REG_LGY_SCL1_STAT_IF_DREQ_MASK                     0x00000001

#ifndef SDK_ASM
#define REG_LGY_SCL1_STAT_FIELD( if_vdet, if_berr, if_dreq ) \
    (u32)( \
    ((u32)(if_vdet) << REG_LGY_SCL1_STAT_IF_VDET_SHIFT) | \
    ((u32)(if_berr) << REG_LGY_SCL1_STAT_IF_BERR_SHIFT) | \
    ((u32)(if_dreq) << REG_LGY_SCL1_STAT_IF_DREQ_SHIFT))
#endif


/* SCL1_IFE */

#define REG_LGY_SCL1_IFE_IFE_VDET_SHIFT                    2
#define REG_LGY_SCL1_IFE_IFE_VDET_SIZE                     1
#define REG_LGY_SCL1_IFE_IFE_VDET_MASK                     0x00000004

#define REG_LGY_SCL1_IFE_IFE_BERR_SHIFT                    1
#define REG_LGY_SCL1_IFE_IFE_BERR_SIZE                     1
#define REG_LGY_SCL1_IFE_IFE_BERR_MASK                     0x00000002

#define REG_LGY_SCL1_IFE_IFE_DREQ_SHIFT                    0
#define REG_LGY_SCL1_IFE_IFE_DREQ_SIZE                     1
#define REG_LGY_SCL1_IFE_IFE_DREQ_MASK                     0x00000001

#ifndef SDK_ASM
#define REG_LGY_SCL1_IFE_FIELD( ife_vdet, ife_berr, ife_dreq ) \
    (u32)( \
    ((u32)(ife_vdet) << REG_LGY_SCL1_IFE_IFE_VDET_SHIFT) | \
    ((u32)(ife_berr) << REG_LGY_SCL1_IFE_IFE_BERR_SHIFT) | \
    ((u32)(ife_dreq) << REG_LGY_SCL1_IFE_IFE_DREQ_SHIFT))
#endif


/* SCL1_FLH */

/* SCL1_ALPHA */

#define REG_LGY_SCL1_ALPHA_ALPHA_SHIFT                     0
#define REG_LGY_SCL1_ALPHA_ALPHA_SIZE                      8
#define REG_LGY_SCL1_ALPHA_ALPHA_MASK                      0x000000ff

#ifndef SDK_ASM
#define REG_LGY_SCL1_ALPHA_FIELD( alpha ) \
    (u32)( \
    ((u32)(alpha) << REG_LGY_SCL1_ALPHA_ALPHA_SHIFT))
#endif


/* SCL1_DITPAT0 */

#define REG_LGY_SCL1_DITPAT0_W3_SHIFT                      14
#define REG_LGY_SCL1_DITPAT0_W3_SIZE                       2
#define REG_LGY_SCL1_DITPAT0_W3_MASK                       0x0000c000

#define REG_LGY_SCL1_DITPAT0_W2_SHIFT                      10
#define REG_LGY_SCL1_DITPAT0_W2_SIZE                       2
#define REG_LGY_SCL1_DITPAT0_W2_MASK                       0x00000c00

#define REG_LGY_SCL1_DITPAT0_W1_SHIFT                      6
#define REG_LGY_SCL1_DITPAT0_W1_SIZE                       2
#define REG_LGY_SCL1_DITPAT0_W1_MASK                       0x000000c0

#define REG_LGY_SCL1_DITPAT0_W0_SHIFT                      2
#define REG_LGY_SCL1_DITPAT0_W0_SIZE                       2
#define REG_LGY_SCL1_DITPAT0_W0_MASK                       0x0000000c

#ifndef SDK_ASM
#define REG_LGY_SCL1_DITPAT0_FIELD( w3, w2, w1, w0 ) \
    (u32)( \
    ((u32)(w3) << REG_LGY_SCL1_DITPAT0_W3_SHIFT) | \
    ((u32)(w2) << REG_LGY_SCL1_DITPAT0_W2_SHIFT) | \
    ((u32)(w1) << REG_LGY_SCL1_DITPAT0_W1_SHIFT) | \
    ((u32)(w0) << REG_LGY_SCL1_DITPAT0_W0_SHIFT))
#endif


/* SCL1_DITPAT1 */

#define REG_LGY_SCL1_DITPAT1_W3_SHIFT                      14
#define REG_LGY_SCL1_DITPAT1_W3_SIZE                       2
#define REG_LGY_SCL1_DITPAT1_W3_MASK                       0x0000c000

#define REG_LGY_SCL1_DITPAT1_W2_SHIFT                      10
#define REG_LGY_SCL1_DITPAT1_W2_SIZE                       2
#define REG_LGY_SCL1_DITPAT1_W2_MASK                       0x00000c00

#define REG_LGY_SCL1_DITPAT1_W1_SHIFT                      6
#define REG_LGY_SCL1_DITPAT1_W1_SIZE                       2
#define REG_LGY_SCL1_DITPAT1_W1_MASK                       0x000000c0

#define REG_LGY_SCL1_DITPAT1_W0_SHIFT                      2
#define REG_LGY_SCL1_DITPAT1_W0_SIZE                       2
#define REG_LGY_SCL1_DITPAT1_W0_MASK                       0x0000000c

#ifndef SDK_ASM
#define REG_LGY_SCL1_DITPAT1_FIELD( w3, w2, w1, w0 ) \
    (u32)( \
    ((u32)(w3) << REG_LGY_SCL1_DITPAT1_W3_SHIFT) | \
    ((u32)(w2) << REG_LGY_SCL1_DITPAT1_W2_SHIFT) | \
    ((u32)(w1) << REG_LGY_SCL1_DITPAT1_W1_SHIFT) | \
    ((u32)(w0) << REG_LGY_SCL1_DITPAT1_W0_SHIFT))
#endif


/* SCL1_VCYC */

#define REG_LGY_SCL1_VCYC_CYC_SHIFT                        0
#define REG_LGY_SCL1_VCYC_CYC_SIZE                         3
#define REG_LGY_SCL1_VCYC_CYC_MASK                         0x00000007

#ifndef SDK_ASM
#define REG_LGY_SCL1_VCYC_FIELD( cyc ) \
    (u32)( \
    ((u32)(cyc) << REG_LGY_SCL1_VCYC_CYC_SHIFT))
#endif


/* SCL1_VADVPAT */

#define REG_LGY_SCL1_VADVPAT_AP_SHIFT                      0
#define REG_LGY_SCL1_VADVPAT_AP_SIZE                       8
#define REG_LGY_SCL1_VADVPAT_AP_MASK                       0x000000ff

#ifndef SDK_ASM
#define REG_LGY_SCL1_VADVPAT_FIELD( ap ) \
    (u32)( \
    ((u32)(ap) << REG_LGY_SCL1_VADVPAT_AP_SHIFT))
#endif


/* SCL1_VC00 */

#define REG_LGY_SCL1_VC00_SGN_SHIFT                        15
#define REG_LGY_SCL1_VC00_SGN_SIZE                         1
#define REG_LGY_SCL1_VC00_SGN_MASK                         0x00008000

#define REG_LGY_SCL1_VC00_DECI_SHIFT                       4
#define REG_LGY_SCL1_VC00_DECI_SIZE                        6
#define REG_LGY_SCL1_VC00_DECI_MASK                        0x000003f0

#ifndef SDK_ASM
#define REG_LGY_SCL1_VC00_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL1_VC00_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL1_VC00_DECI_SHIFT))
#endif


/* SCL1_VC10 */

#define REG_LGY_SCL1_VC10_SGN_SHIFT                        15
#define REG_LGY_SCL1_VC10_SGN_SIZE                         1
#define REG_LGY_SCL1_VC10_SGN_MASK                         0x00008000

#define REG_LGY_SCL1_VC10_DECI_SHIFT                       4
#define REG_LGY_SCL1_VC10_DECI_SIZE                        8
#define REG_LGY_SCL1_VC10_DECI_MASK                        0x00000ff0

#ifndef SDK_ASM
#define REG_LGY_SCL1_VC10_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL1_VC10_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL1_VC10_DECI_SHIFT))
#endif


/* SCL1_VC20 */

#define REG_LGY_SCL1_VC20_SGN_SHIFT                        15
#define REG_LGY_SCL1_VC20_SGN_SIZE                         1
#define REG_LGY_SCL1_VC20_SGN_MASK                         0x00008000

#define REG_LGY_SCL1_VC20_INT_SHIFT                        14
#define REG_LGY_SCL1_VC20_INT_SIZE                         1
#define REG_LGY_SCL1_VC20_INT_MASK                         0x00004000

#define REG_LGY_SCL1_VC20_DECI_SHIFT                       4
#define REG_LGY_SCL1_VC20_DECI_SIZE                        10
#define REG_LGY_SCL1_VC20_DECI_MASK                        0x00003ff0

#ifndef SDK_ASM
#define REG_LGY_SCL1_VC20_FIELD( sgn, int, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL1_VC20_SGN_SHIFT) | \
    ((u32)(int) << REG_LGY_SCL1_VC20_INT_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL1_VC20_DECI_SHIFT))
#endif


/* SCL1_VC30 */

#define REG_LGY_SCL1_VC30_SGN_SHIFT                        15
#define REG_LGY_SCL1_VC30_SGN_SIZE                         1
#define REG_LGY_SCL1_VC30_SGN_MASK                         0x00008000

#define REG_LGY_SCL1_VC30_INT_SHIFT                        14
#define REG_LGY_SCL1_VC30_INT_SIZE                         1
#define REG_LGY_SCL1_VC30_INT_MASK                         0x00004000

#define REG_LGY_SCL1_VC30_DECI_SHIFT                       4
#define REG_LGY_SCL1_VC30_DECI_SIZE                        10
#define REG_LGY_SCL1_VC30_DECI_MASK                        0x00003ff0

#ifndef SDK_ASM
#define REG_LGY_SCL1_VC30_FIELD( sgn, int, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL1_VC30_SGN_SHIFT) | \
    ((u32)(int) << REG_LGY_SCL1_VC30_INT_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL1_VC30_DECI_SHIFT))
#endif


/* SCL1_VC40 */

#define REG_LGY_SCL1_VC40_SGN_SHIFT                        15
#define REG_LGY_SCL1_VC40_SGN_SIZE                         1
#define REG_LGY_SCL1_VC40_SGN_MASK                         0x00008000

#define REG_LGY_SCL1_VC40_DECI_SHIFT                       4
#define REG_LGY_SCL1_VC40_DECI_SIZE                        8
#define REG_LGY_SCL1_VC40_DECI_MASK                        0x00000ff0

#ifndef SDK_ASM
#define REG_LGY_SCL1_VC40_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL1_VC40_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL1_VC40_DECI_SHIFT))
#endif


/* SCL1_VC50 */

#define REG_LGY_SCL1_VC50_SGN_SHIFT                        15
#define REG_LGY_SCL1_VC50_SGN_SIZE                         1
#define REG_LGY_SCL1_VC50_SGN_MASK                         0x00008000

#define REG_LGY_SCL1_VC50_DECI_SHIFT                       4
#define REG_LGY_SCL1_VC50_DECI_SIZE                        6
#define REG_LGY_SCL1_VC50_DECI_MASK                        0x000003f0

#ifndef SDK_ASM
#define REG_LGY_SCL1_VC50_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL1_VC50_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL1_VC50_DECI_SHIFT))
#endif


/* SCL1_HCYC */

#define REG_LGY_SCL1_HCYC_CYC_SHIFT                        0
#define REG_LGY_SCL1_HCYC_CYC_SIZE                         3
#define REG_LGY_SCL1_HCYC_CYC_MASK                         0x00000007

#ifndef SDK_ASM
#define REG_LGY_SCL1_HCYC_FIELD( cyc ) \
    (u32)( \
    ((u32)(cyc) << REG_LGY_SCL1_HCYC_CYC_SHIFT))
#endif


/* SCL1_HADPAT */

#define REG_LGY_SCL1_HADPAT_AP_SHIFT                       0
#define REG_LGY_SCL1_HADPAT_AP_SIZE                        8
#define REG_LGY_SCL1_HADPAT_AP_MASK                        0x000000ff

#ifndef SDK_ASM
#define REG_LGY_SCL1_HADPAT_FIELD( ap ) \
    (u32)( \
    ((u32)(ap) << REG_LGY_SCL1_HADPAT_AP_SHIFT))
#endif


/* SCL1_HC00 */

#define REG_LGY_SCL1_HC00_SGN_SHIFT                        15
#define REG_LGY_SCL1_HC00_SGN_SIZE                         1
#define REG_LGY_SCL1_HC00_SGN_MASK                         0x00008000

#define REG_LGY_SCL1_HC00_DECI_SHIFT                       4
#define REG_LGY_SCL1_HC00_DECI_SIZE                        6
#define REG_LGY_SCL1_HC00_DECI_MASK                        0x000003f0

#ifndef SDK_ASM
#define REG_LGY_SCL1_HC00_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL1_HC00_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL1_HC00_DECI_SHIFT))
#endif


/* SCL1_HC10 */

#define REG_LGY_SCL1_HC10_SGN_SHIFT                        15
#define REG_LGY_SCL1_HC10_SGN_SIZE                         1
#define REG_LGY_SCL1_HC10_SGN_MASK                         0x00008000

#define REG_LGY_SCL1_HC10_DECI_SHIFT                       4
#define REG_LGY_SCL1_HC10_DECI_SIZE                        8
#define REG_LGY_SCL1_HC10_DECI_MASK                        0x00000ff0

#ifndef SDK_ASM
#define REG_LGY_SCL1_HC10_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL1_HC10_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL1_HC10_DECI_SHIFT))
#endif


/* SCL1_HC20 */

#define REG_LGY_SCL1_HC20_SGN_SHIFT                        15
#define REG_LGY_SCL1_HC20_SGN_SIZE                         1
#define REG_LGY_SCL1_HC20_SGN_MASK                         0x00008000

#define REG_LGY_SCL1_HC20_INT_SHIFT                        14
#define REG_LGY_SCL1_HC20_INT_SIZE                         1
#define REG_LGY_SCL1_HC20_INT_MASK                         0x00004000

#define REG_LGY_SCL1_HC20_DECI_SHIFT                       4
#define REG_LGY_SCL1_HC20_DECI_SIZE                        10
#define REG_LGY_SCL1_HC20_DECI_MASK                        0x00003ff0

#ifndef SDK_ASM
#define REG_LGY_SCL1_HC20_FIELD( sgn, int, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL1_HC20_SGN_SHIFT) | \
    ((u32)(int) << REG_LGY_SCL1_HC20_INT_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL1_HC20_DECI_SHIFT))
#endif


/* SCL1_HC30 */

#define REG_LGY_SCL1_HC30_SGN_SHIFT                        15
#define REG_LGY_SCL1_HC30_SGN_SIZE                         1
#define REG_LGY_SCL1_HC30_SGN_MASK                         0x00008000

#define REG_LGY_SCL1_HC30_INT_SHIFT                        14
#define REG_LGY_SCL1_HC30_INT_SIZE                         1
#define REG_LGY_SCL1_HC30_INT_MASK                         0x00004000

#define REG_LGY_SCL1_HC30_DECI_SHIFT                       4
#define REG_LGY_SCL1_HC30_DECI_SIZE                        10
#define REG_LGY_SCL1_HC30_DECI_MASK                        0x00003ff0

#ifndef SDK_ASM
#define REG_LGY_SCL1_HC30_FIELD( sgn, int, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL1_HC30_SGN_SHIFT) | \
    ((u32)(int) << REG_LGY_SCL1_HC30_INT_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL1_HC30_DECI_SHIFT))
#endif


/* SCL1_HC40 */

#define REG_LGY_SCL1_HC40_SGN_SHIFT                        15
#define REG_LGY_SCL1_HC40_SGN_SIZE                         1
#define REG_LGY_SCL1_HC40_SGN_MASK                         0x00008000

#define REG_LGY_SCL1_HC40_DECI_SHIFT                       4
#define REG_LGY_SCL1_HC40_DECI_SIZE                        8
#define REG_LGY_SCL1_HC40_DECI_MASK                        0x00000ff0

#ifndef SDK_ASM
#define REG_LGY_SCL1_HC40_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL1_HC40_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL1_HC40_DECI_SHIFT))
#endif


/* SCL1_HC50 */

#define REG_LGY_SCL1_HC50_SGN_SHIFT                        15
#define REG_LGY_SCL1_HC50_SGN_SIZE                         1
#define REG_LGY_SCL1_HC50_SGN_MASK                         0x00008000

#define REG_LGY_SCL1_HC50_DECI_SHIFT                       4
#define REG_LGY_SCL1_HC50_DECI_SIZE                        6
#define REG_LGY_SCL1_HC50_DECI_MASK                        0x000003f0

#ifndef SDK_ASM
#define REG_LGY_SCL1_HC50_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL1_HC50_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL1_HC50_DECI_SHIFT))
#endif


/* SCL1_DATA0 */

/* SCL2_CNT */

#define REG_LGY_SCL2_CNT_DREQ_E_SHIFT                      15
#define REG_LGY_SCL2_CNT_DREQ_E_SIZE                       1
#define REG_LGY_SCL2_CNT_DREQ_E_MASK                       0x00008000

#define REG_LGY_SCL2_CNT_BF_SHIFT                          12
#define REG_LGY_SCL2_CNT_BF_SIZE                           1
#define REG_LGY_SCL2_CNT_BF_MASK                           0x00001000

#define REG_LGY_SCL2_CNT_ROT_SHIFT                         10
#define REG_LGY_SCL2_CNT_ROT_SIZE                          2
#define REG_LGY_SCL2_CNT_ROT_MASK                          0x00000c00

#define REG_LGY_SCL2_CNT_PF_SHIFT                          8
#define REG_LGY_SCL2_CNT_PF_SIZE                           2
#define REG_LGY_SCL2_CNT_PF_MASK                           0x00000300

#define REG_LGY_SCL2_CNT_TD_E_SHIFT                        5
#define REG_LGY_SCL2_CNT_TD_E_SIZE                         1
#define REG_LGY_SCL2_CNT_TD_E_MASK                         0x00000020

#define REG_LGY_SCL2_CNT_SD_E_SHIFT                        4
#define REG_LGY_SCL2_CNT_SD_E_SIZE                         1
#define REG_LGY_SCL2_CNT_SD_E_MASK                         0x00000010

#define REG_LGY_SCL2_CNT_H_E_SHIFT                         2
#define REG_LGY_SCL2_CNT_H_E_SIZE                          1
#define REG_LGY_SCL2_CNT_H_E_MASK                          0x00000004

#define REG_LGY_SCL2_CNT_V_E_SHIFT                         1
#define REG_LGY_SCL2_CNT_V_E_SIZE                          1
#define REG_LGY_SCL2_CNT_V_E_MASK                          0x00000002

#define REG_LGY_SCL2_CNT_E_SHIFT                           0
#define REG_LGY_SCL2_CNT_E_SIZE                            1
#define REG_LGY_SCL2_CNT_E_MASK                            0x00000001

#ifndef SDK_ASM
#define REG_LGY_SCL2_CNT_FIELD( dreq_e, bf, rot, pf, td_e, sd_e, h_e, v_e, e ) \
    (u32)( \
    ((u32)(dreq_e) << REG_LGY_SCL2_CNT_DREQ_E_SHIFT) | \
    ((u32)(bf) << REG_LGY_SCL2_CNT_BF_SHIFT) | \
    ((u32)(rot) << REG_LGY_SCL2_CNT_ROT_SHIFT) | \
    ((u32)(pf) << REG_LGY_SCL2_CNT_PF_SHIFT) | \
    ((u32)(td_e) << REG_LGY_SCL2_CNT_TD_E_SHIFT) | \
    ((u32)(sd_e) << REG_LGY_SCL2_CNT_SD_E_SHIFT) | \
    ((u32)(h_e) << REG_LGY_SCL2_CNT_H_E_SHIFT) | \
    ((u32)(v_e) << REG_LGY_SCL2_CNT_V_E_SHIFT) | \
    ((u32)(e) << REG_LGY_SCL2_CNT_E_SHIFT))
#endif


/* SCL2_SIZE */

#define REG_LGY_SCL2_SIZE_V_SHIFT                          16
#define REG_LGY_SCL2_SIZE_V_SIZE                           9
#define REG_LGY_SCL2_SIZE_V_MASK                           0x01ff0000

#define REG_LGY_SCL2_SIZE_H_SHIFT                          0
#define REG_LGY_SCL2_SIZE_H_SIZE                           9
#define REG_LGY_SCL2_SIZE_H_MASK                           0x000001ff

#ifndef SDK_ASM
#define REG_LGY_SCL2_SIZE_FIELD( v, h ) \
    (u32)( \
    ((u32)(v) << REG_LGY_SCL2_SIZE_V_SHIFT) | \
    ((u32)(h) << REG_LGY_SCL2_SIZE_H_SHIFT))
#endif


/* SCL2_STAT */

#define REG_LGY_SCL2_STAT_IF_VDET_SHIFT                    2
#define REG_LGY_SCL2_STAT_IF_VDET_SIZE                     1
#define REG_LGY_SCL2_STAT_IF_VDET_MASK                     0x00000004

#define REG_LGY_SCL2_STAT_IF_BERR_SHIFT                    1
#define REG_LGY_SCL2_STAT_IF_BERR_SIZE                     1
#define REG_LGY_SCL2_STAT_IF_BERR_MASK                     0x00000002

#define REG_LGY_SCL2_STAT_IF_DREQ_SHIFT                    0
#define REG_LGY_SCL2_STAT_IF_DREQ_SIZE                     1
#define REG_LGY_SCL2_STAT_IF_DREQ_MASK                     0x00000001

#ifndef SDK_ASM
#define REG_LGY_SCL2_STAT_FIELD( if_vdet, if_berr, if_dreq ) \
    (u32)( \
    ((u32)(if_vdet) << REG_LGY_SCL2_STAT_IF_VDET_SHIFT) | \
    ((u32)(if_berr) << REG_LGY_SCL2_STAT_IF_BERR_SHIFT) | \
    ((u32)(if_dreq) << REG_LGY_SCL2_STAT_IF_DREQ_SHIFT))
#endif


/* SCL2_IFE */

#define REG_LGY_SCL2_IFE_IFE_VDET_SHIFT                    2
#define REG_LGY_SCL2_IFE_IFE_VDET_SIZE                     1
#define REG_LGY_SCL2_IFE_IFE_VDET_MASK                     0x00000004

#define REG_LGY_SCL2_IFE_IFE_BERR_SHIFT                    1
#define REG_LGY_SCL2_IFE_IFE_BERR_SIZE                     1
#define REG_LGY_SCL2_IFE_IFE_BERR_MASK                     0x00000002

#define REG_LGY_SCL2_IFE_IFE_DREQ_SHIFT                    0
#define REG_LGY_SCL2_IFE_IFE_DREQ_SIZE                     1
#define REG_LGY_SCL2_IFE_IFE_DREQ_MASK                     0x00000001

#ifndef SDK_ASM
#define REG_LGY_SCL2_IFE_FIELD( ife_vdet, ife_berr, ife_dreq ) \
    (u32)( \
    ((u32)(ife_vdet) << REG_LGY_SCL2_IFE_IFE_VDET_SHIFT) | \
    ((u32)(ife_berr) << REG_LGY_SCL2_IFE_IFE_BERR_SHIFT) | \
    ((u32)(ife_dreq) << REG_LGY_SCL2_IFE_IFE_DREQ_SHIFT))
#endif


/* SCL2_FLH */

/* SCL2_ALPHA */

#define REG_LGY_SCL2_ALPHA_ALPHA_SHIFT                     0
#define REG_LGY_SCL2_ALPHA_ALPHA_SIZE                      8
#define REG_LGY_SCL2_ALPHA_ALPHA_MASK                      0x000000ff

#ifndef SDK_ASM
#define REG_LGY_SCL2_ALPHA_FIELD( alpha ) \
    (u32)( \
    ((u32)(alpha) << REG_LGY_SCL2_ALPHA_ALPHA_SHIFT))
#endif


/* SCL2_DITPAT0 */

#define REG_LGY_SCL2_DITPAT0_W3_SHIFT                      14
#define REG_LGY_SCL2_DITPAT0_W3_SIZE                       2
#define REG_LGY_SCL2_DITPAT0_W3_MASK                       0x0000c000

#define REG_LGY_SCL2_DITPAT0_W2_SHIFT                      10
#define REG_LGY_SCL2_DITPAT0_W2_SIZE                       2
#define REG_LGY_SCL2_DITPAT0_W2_MASK                       0x00000c00

#define REG_LGY_SCL2_DITPAT0_W1_SHIFT                      6
#define REG_LGY_SCL2_DITPAT0_W1_SIZE                       2
#define REG_LGY_SCL2_DITPAT0_W1_MASK                       0x000000c0

#define REG_LGY_SCL2_DITPAT0_W0_SHIFT                      2
#define REG_LGY_SCL2_DITPAT0_W0_SIZE                       2
#define REG_LGY_SCL2_DITPAT0_W0_MASK                       0x0000000c

#ifndef SDK_ASM
#define REG_LGY_SCL2_DITPAT0_FIELD( w3, w2, w1, w0 ) \
    (u32)( \
    ((u32)(w3) << REG_LGY_SCL2_DITPAT0_W3_SHIFT) | \
    ((u32)(w2) << REG_LGY_SCL2_DITPAT0_W2_SHIFT) | \
    ((u32)(w1) << REG_LGY_SCL2_DITPAT0_W1_SHIFT) | \
    ((u32)(w0) << REG_LGY_SCL2_DITPAT0_W0_SHIFT))
#endif


/* SCL2_DITPAT1 */

#define REG_LGY_SCL2_DITPAT1_W3_SHIFT                      14
#define REG_LGY_SCL2_DITPAT1_W3_SIZE                       2
#define REG_LGY_SCL2_DITPAT1_W3_MASK                       0x0000c000

#define REG_LGY_SCL2_DITPAT1_W2_SHIFT                      10
#define REG_LGY_SCL2_DITPAT1_W2_SIZE                       2
#define REG_LGY_SCL2_DITPAT1_W2_MASK                       0x00000c00

#define REG_LGY_SCL2_DITPAT1_W1_SHIFT                      6
#define REG_LGY_SCL2_DITPAT1_W1_SIZE                       2
#define REG_LGY_SCL2_DITPAT1_W1_MASK                       0x000000c0

#define REG_LGY_SCL2_DITPAT1_W0_SHIFT                      2
#define REG_LGY_SCL2_DITPAT1_W0_SIZE                       2
#define REG_LGY_SCL2_DITPAT1_W0_MASK                       0x0000000c

#ifndef SDK_ASM
#define REG_LGY_SCL2_DITPAT1_FIELD( w3, w2, w1, w0 ) \
    (u32)( \
    ((u32)(w3) << REG_LGY_SCL2_DITPAT1_W3_SHIFT) | \
    ((u32)(w2) << REG_LGY_SCL2_DITPAT1_W2_SHIFT) | \
    ((u32)(w1) << REG_LGY_SCL2_DITPAT1_W1_SHIFT) | \
    ((u32)(w0) << REG_LGY_SCL2_DITPAT1_W0_SHIFT))
#endif


/* SCL2_VCYC */

#define REG_LGY_SCL2_VCYC_CYC_SHIFT                        0
#define REG_LGY_SCL2_VCYC_CYC_SIZE                         3
#define REG_LGY_SCL2_VCYC_CYC_MASK                         0x00000007

#ifndef SDK_ASM
#define REG_LGY_SCL2_VCYC_FIELD( cyc ) \
    (u32)( \
    ((u32)(cyc) << REG_LGY_SCL2_VCYC_CYC_SHIFT))
#endif


/* SCL2_VADPAT */

#define REG_LGY_SCL2_VADPAT_AP_SHIFT                       0
#define REG_LGY_SCL2_VADPAT_AP_SIZE                        8
#define REG_LGY_SCL2_VADPAT_AP_MASK                        0x000000ff

#ifndef SDK_ASM
#define REG_LGY_SCL2_VADPAT_FIELD( ap ) \
    (u32)( \
    ((u32)(ap) << REG_LGY_SCL2_VADPAT_AP_SHIFT))
#endif


/* SCL2_VC00 */

#define REG_LGY_SCL2_VC00_SGN_SHIFT                        15
#define REG_LGY_SCL2_VC00_SGN_SIZE                         1
#define REG_LGY_SCL2_VC00_SGN_MASK                         0x00008000

#define REG_LGY_SCL2_VC00_DECI_SHIFT                       4
#define REG_LGY_SCL2_VC00_DECI_SIZE                        6
#define REG_LGY_SCL2_VC00_DECI_MASK                        0x000003f0

#ifndef SDK_ASM
#define REG_LGY_SCL2_VC00_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL2_VC00_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL2_VC00_DECI_SHIFT))
#endif


/* SCL2_VC10 */

#define REG_LGY_SCL2_VC10_SGN_SHIFT                        15
#define REG_LGY_SCL2_VC10_SGN_SIZE                         1
#define REG_LGY_SCL2_VC10_SGN_MASK                         0x00008000

#define REG_LGY_SCL2_VC10_DECI_SHIFT                       4
#define REG_LGY_SCL2_VC10_DECI_SIZE                        8
#define REG_LGY_SCL2_VC10_DECI_MASK                        0x00000ff0

#ifndef SDK_ASM
#define REG_LGY_SCL2_VC10_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL2_VC10_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL2_VC10_DECI_SHIFT))
#endif


/* SCL2_VC20 */

#define REG_LGY_SCL2_VC20_SGN_SHIFT                        15
#define REG_LGY_SCL2_VC20_SGN_SIZE                         1
#define REG_LGY_SCL2_VC20_SGN_MASK                         0x00008000

#define REG_LGY_SCL2_VC20_INT_SHIFT                        14
#define REG_LGY_SCL2_VC20_INT_SIZE                         1
#define REG_LGY_SCL2_VC20_INT_MASK                         0x00004000

#define REG_LGY_SCL2_VC20_DECI_SHIFT                       4
#define REG_LGY_SCL2_VC20_DECI_SIZE                        10
#define REG_LGY_SCL2_VC20_DECI_MASK                        0x00003ff0

#ifndef SDK_ASM
#define REG_LGY_SCL2_VC20_FIELD( sgn, int, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL2_VC20_SGN_SHIFT) | \
    ((u32)(int) << REG_LGY_SCL2_VC20_INT_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL2_VC20_DECI_SHIFT))
#endif


/* SCL2_VC30 */

#define REG_LGY_SCL2_VC30_SGN_SHIFT                        15
#define REG_LGY_SCL2_VC30_SGN_SIZE                         1
#define REG_LGY_SCL2_VC30_SGN_MASK                         0x00008000

#define REG_LGY_SCL2_VC30_INT_SHIFT                        14
#define REG_LGY_SCL2_VC30_INT_SIZE                         1
#define REG_LGY_SCL2_VC30_INT_MASK                         0x00004000

#define REG_LGY_SCL2_VC30_DECI_SHIFT                       4
#define REG_LGY_SCL2_VC30_DECI_SIZE                        10
#define REG_LGY_SCL2_VC30_DECI_MASK                        0x00003ff0

#ifndef SDK_ASM
#define REG_LGY_SCL2_VC30_FIELD( sgn, int, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL2_VC30_SGN_SHIFT) | \
    ((u32)(int) << REG_LGY_SCL2_VC30_INT_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL2_VC30_DECI_SHIFT))
#endif


/* SCL2_VC40 */

#define REG_LGY_SCL2_VC40_SGN_SHIFT                        15
#define REG_LGY_SCL2_VC40_SGN_SIZE                         1
#define REG_LGY_SCL2_VC40_SGN_MASK                         0x00008000

#define REG_LGY_SCL2_VC40_DECI_SHIFT                       4
#define REG_LGY_SCL2_VC40_DECI_SIZE                        8
#define REG_LGY_SCL2_VC40_DECI_MASK                        0x00000ff0

#ifndef SDK_ASM
#define REG_LGY_SCL2_VC40_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL2_VC40_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL2_VC40_DECI_SHIFT))
#endif


/* SCL2_VC50 */

#define REG_LGY_SCL2_VC50_SGN_SHIFT                        15
#define REG_LGY_SCL2_VC50_SGN_SIZE                         1
#define REG_LGY_SCL2_VC50_SGN_MASK                         0x00008000

#define REG_LGY_SCL2_VC50_DECI_SHIFT                       4
#define REG_LGY_SCL2_VC50_DECI_SIZE                        6
#define REG_LGY_SCL2_VC50_DECI_MASK                        0x000003f0

#ifndef SDK_ASM
#define REG_LGY_SCL2_VC50_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL2_VC50_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL2_VC50_DECI_SHIFT))
#endif


/* SCL2_HCYC */

#define REG_LGY_SCL2_HCYC_CYC_SHIFT                        0
#define REG_LGY_SCL2_HCYC_CYC_SIZE                         3
#define REG_LGY_SCL2_HCYC_CYC_MASK                         0x00000007

#ifndef SDK_ASM
#define REG_LGY_SCL2_HCYC_FIELD( cyc ) \
    (u32)( \
    ((u32)(cyc) << REG_LGY_SCL2_HCYC_CYC_SHIFT))
#endif


/* SCL2_HADVPAT */

#define REG_LGY_SCL2_HADVPAT_AP_SHIFT                      0
#define REG_LGY_SCL2_HADVPAT_AP_SIZE                       8
#define REG_LGY_SCL2_HADVPAT_AP_MASK                       0x000000ff

#ifndef SDK_ASM
#define REG_LGY_SCL2_HADVPAT_FIELD( ap ) \
    (u32)( \
    ((u32)(ap) << REG_LGY_SCL2_HADVPAT_AP_SHIFT))
#endif


/* SCL2_HC00 */

#define REG_LGY_SCL2_HC00_SGN_SHIFT                        15
#define REG_LGY_SCL2_HC00_SGN_SIZE                         1
#define REG_LGY_SCL2_HC00_SGN_MASK                         0x00008000

#define REG_LGY_SCL2_HC00_DECI_SHIFT                       4
#define REG_LGY_SCL2_HC00_DECI_SIZE                        6
#define REG_LGY_SCL2_HC00_DECI_MASK                        0x000003f0

#ifndef SDK_ASM
#define REG_LGY_SCL2_HC00_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL2_HC00_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL2_HC00_DECI_SHIFT))
#endif


/* SCL2_HC10 */

#define REG_LGY_SCL2_HC10_SGN_SHIFT                        15
#define REG_LGY_SCL2_HC10_SGN_SIZE                         1
#define REG_LGY_SCL2_HC10_SGN_MASK                         0x00008000

#define REG_LGY_SCL2_HC10_DECI_SHIFT                       4
#define REG_LGY_SCL2_HC10_DECI_SIZE                        8
#define REG_LGY_SCL2_HC10_DECI_MASK                        0x00000ff0

#ifndef SDK_ASM
#define REG_LGY_SCL2_HC10_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL2_HC10_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL2_HC10_DECI_SHIFT))
#endif


/* SCL2_HC20 */

#define REG_LGY_SCL2_HC20_SGN_SHIFT                        15
#define REG_LGY_SCL2_HC20_SGN_SIZE                         1
#define REG_LGY_SCL2_HC20_SGN_MASK                         0x00008000

#define REG_LGY_SCL2_HC20_INT_SHIFT                        14
#define REG_LGY_SCL2_HC20_INT_SIZE                         1
#define REG_LGY_SCL2_HC20_INT_MASK                         0x00004000

#define REG_LGY_SCL2_HC20_DECI_SHIFT                       4
#define REG_LGY_SCL2_HC20_DECI_SIZE                        10
#define REG_LGY_SCL2_HC20_DECI_MASK                        0x00003ff0

#ifndef SDK_ASM
#define REG_LGY_SCL2_HC20_FIELD( sgn, int, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL2_HC20_SGN_SHIFT) | \
    ((u32)(int) << REG_LGY_SCL2_HC20_INT_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL2_HC20_DECI_SHIFT))
#endif


/* SCL2_HC30 */

#define REG_LGY_SCL2_HC30_SGN_SHIFT                        15
#define REG_LGY_SCL2_HC30_SGN_SIZE                         1
#define REG_LGY_SCL2_HC30_SGN_MASK                         0x00008000

#define REG_LGY_SCL2_HC30_INT_SHIFT                        14
#define REG_LGY_SCL2_HC30_INT_SIZE                         1
#define REG_LGY_SCL2_HC30_INT_MASK                         0x00004000

#define REG_LGY_SCL2_HC30_DECI_SHIFT                       4
#define REG_LGY_SCL2_HC30_DECI_SIZE                        10
#define REG_LGY_SCL2_HC30_DECI_MASK                        0x00003ff0

#ifndef SDK_ASM
#define REG_LGY_SCL2_HC30_FIELD( sgn, int, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL2_HC30_SGN_SHIFT) | \
    ((u32)(int) << REG_LGY_SCL2_HC30_INT_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL2_HC30_DECI_SHIFT))
#endif


/* SCL2_HC40 */

#define REG_LGY_SCL2_HC40_SGN_SHIFT                        15
#define REG_LGY_SCL2_HC40_SGN_SIZE                         1
#define REG_LGY_SCL2_HC40_SGN_MASK                         0x00008000

#define REG_LGY_SCL2_HC40_DECI_SHIFT                       4
#define REG_LGY_SCL2_HC40_DECI_SIZE                        8
#define REG_LGY_SCL2_HC40_DECI_MASK                        0x00000ff0

#ifndef SDK_ASM
#define REG_LGY_SCL2_HC40_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL2_HC40_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL2_HC40_DECI_SHIFT))
#endif


/* SCL2_HC50 */

#define REG_LGY_SCL2_HC50_SGN_SHIFT                        15
#define REG_LGY_SCL2_HC50_SGN_SIZE                         1
#define REG_LGY_SCL2_HC50_SGN_MASK                         0x00008000

#define REG_LGY_SCL2_HC50_DECI_SHIFT                       4
#define REG_LGY_SCL2_HC50_DECI_SIZE                        6
#define REG_LGY_SCL2_HC50_DECI_MASK                        0x000003f0

#ifndef SDK_ASM
#define REG_LGY_SCL2_HC50_FIELD( sgn, deci ) \
    (u32)( \
    ((u32)(sgn) << REG_LGY_SCL2_HC50_SGN_SHIFT) | \
    ((u32)(deci) << REG_LGY_SCL2_HC50_DECI_SHIFT))
#endif


/* SCL2_DATA0 */

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_MPCORE_IOREG_LGY_H_ */
#endif
