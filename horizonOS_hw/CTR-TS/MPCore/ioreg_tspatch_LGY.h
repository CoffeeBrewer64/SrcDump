/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TS/MPCore/ioreg_tspatch_LGY.h

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
#ifndef NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_LGY_H_
#define NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_LGY_H_

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
#define reg_LGY_LIE                                        (*(const REGType16v *) REG_LIE_ADDR)

/* LKEYCNT */

#define REG_LKEYCNT_OFFSET                                 0x14110a
#define REG_LKEYCNT_ADDR                                   (HW_REG_BASE + REG_LKEYCNT_OFFSET)
#define reg_LGY_LKEYCNT                                    (*(const REGType16v *) REG_LKEYCNT_ADDR)

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

/* LDETMSEL */

#define REG_LDETMSEL_OFFSET                                0x141118
#define REG_LDETMSEL_ADDR                                  (HW_REG_BASE + REG_LDETMSEL_OFFSET)
#define reg_LGY_LDETMSEL                                   (*( REGType8v *) REG_LDETMSEL_ADDR)

/* LDETMVAL */

#define REG_LDETMVAL_OFFSET                                0x141119
#define REG_LDETMVAL_ADDR                                  (HW_REG_BASE + REG_LDETMVAL_OFFSET)
#define reg_LGY_LDETMVAL                                   (*( REGType8v *) REG_LDETMVAL_ADDR)

/* LSTAT */

#define REG_LSTAT_OFFSET                                   0x141120
#define REG_LSTAT_ADDR                                     (HW_REG_BASE + REG_LSTAT_OFFSET)
#define reg_LGY_LSTAT                                      (*(const REGType8v *) REG_LSTAT_ADDR)

/* RTC_CNT */

#define REG_RTC_CNT_OFFSET                                 0x147100
#define REG_RTC_CNT_ADDR                                   (HW_REG_BASE + REG_RTC_CNT_OFFSET)
#define reg_LGY_RTC_CNT                                    (*( REGType16v *) REG_RTC_CNT_ADDR)

/* RTC_STATUS1 */

#define REG_RTC_STATUS1_OFFSET                             0x147110
#define REG_RTC_STATUS1_ADDR                               (HW_REG_BASE + REG_RTC_STATUS1_OFFSET)
#define reg_LGY_RTC_STATUS1                                (*( REGType8v *) REG_RTC_STATUS1_ADDR)

/* RTC_STATUS2 */

#define REG_RTC_STATUS2_OFFSET                             0x147111
#define REG_RTC_STATUS2_ADDR                               (HW_REG_BASE + REG_RTC_STATUS2_OFFSET)
#define reg_LGY_RTC_STATUS2                                (*( REGType8v *) REG_RTC_STATUS2_ADDR)

/* RTC_ADJ */

#define REG_RTC_ADJ_OFFSET                                 0x147112
#define REG_RTC_ADJ_ADDR                                   (HW_REG_BASE + REG_RTC_ADJ_OFFSET)
#define reg_LGY_RTC_ADJ                                    (*( REGType8v *) REG_RTC_ADJ_ADDR)

/* RTC_FREE */

#define REG_RTC_FREE_OFFSET                                0x147113
#define REG_RTC_FREE_ADDR                                  (HW_REG_BASE + REG_RTC_FREE_OFFSET)
#define reg_LGY_RTC_FREE                                   (*( REGType8v *) REG_RTC_FREE_ADDR)

/* RTC_DATA1 */

#define REG_RTC_DATA1_OFFSET                               0x147120
#define REG_RTC_DATA1_ADDR                                 (HW_REG_BASE + REG_RTC_DATA1_OFFSET)
#define reg_LGY_RTC_DATA1                                  (*( REGType32v *) REG_RTC_DATA1_ADDR)

/* RTC_DATA2 */

#define REG_RTC_DATA2_OFFSET                               0x147124
#define REG_RTC_DATA2_ADDR                                 (HW_REG_BASE + REG_RTC_DATA2_OFFSET)
#define reg_LGY_RTC_DATA2                                  (*( REGType32v *) REG_RTC_DATA2_ADDR)

/* RTC_ALM1 */

#define REG_RTC_ALM1_OFFSET                                0x147130
#define REG_RTC_ALM1_ADDR                                  (HW_REG_BASE + REG_RTC_ALM1_OFFSET)
#define reg_LGY_RTC_ALM1                                   (*( REGType32v *) REG_RTC_ALM1_ADDR)

/* RTC_ALM2 */

#define REG_RTC_ALM2_OFFSET                                0x147134
#define REG_RTC_ALM2_ADDR                                  (HW_REG_BASE + REG_RTC_ALM2_OFFSET)
#define reg_LGY_RTC_ALM2                                   (*( REGType32v *) REG_RTC_ALM2_ADDR)

/* RTC_UPCOUNT */

#define REG_RTC_UPCOUNT_OFFSET                             0x147140
#define REG_RTC_UPCOUNT_ADDR                               (HW_REG_BASE + REG_RTC_UPCOUNT_OFFSET)
#define reg_LGY_RTC_UPCOUNT                                (*( REGType32v *) REG_RTC_UPCOUNT_ADDR)

/* RTC_FOUT1 */

#define REG_RTC_FOUT1_OFFSET                               0x147150
#define REG_RTC_FOUT1_ADDR                                 (HW_REG_BASE + REG_RTC_FOUT1_OFFSET)
#define reg_LGY_RTC_FOUT1                                  (*( REGType8v *) REG_RTC_FOUT1_ADDR)

/* RTC_FOUT2 */

#define REG_RTC_FOUT2_OFFSET                               0x147151
#define REG_RTC_FOUT2_ADDR                                 (HW_REG_BASE + REG_RTC_FOUT2_OFFSET)
#define reg_LGY_RTC_FOUT2                                  (*( REGType8v *) REG_RTC_FOUT2_ADDR)

/* RTC_ALMEX1 */

#define REG_RTC_ALMEX1_OFFSET                              0x147160
#define REG_RTC_ALMEX1_ADDR                                (HW_REG_BASE + REG_RTC_ALMEX1_OFFSET)
#define reg_LGY_RTC_ALMEX1                                 (*( REGType32v *) REG_RTC_ALMEX1_ADDR)

/* RTC_ALMEX2 */

#define REG_RTC_ALMEX2_OFFSET                              0x147164
#define REG_RTC_ALMEX2_ADDR                                (HW_REG_BASE + REG_RTC_ALMEX2_OFFSET)
#define reg_LGY_RTC_ALMEX2                                 (*( REGType32v *) REG_RTC_ALMEX2_ADDR)

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

/* SCL2_VADVPAT */

#define REG_SCL2_VADVPAT_OFFSET                            0x111204
#define REG_SCL2_VADVPAT_ADDR                              (HW_REG_BASE + REG_SCL2_VADVPAT_OFFSET)
#define reg_LGY_SCL2_VADVPAT                               (*( REGType32v *) REG_SCL2_VADVPAT_ADDR)

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


/* LKEYCNT */

#define REG_LGY_LKEYCNT_LOGIC_SHIFT                        15
#define REG_LGY_LKEYCNT_LOGIC_SIZE                         1
#define REG_LGY_LKEYCNT_LOGIC_MASK                         0x8000

#define REG_LGY_LKEYCNT_INTR_SHIFT                         14
#define REG_LGY_LKEYCNT_INTR_SIZE                          1
#define REG_LGY_LKEYCNT_INTR_MASK                          0x4000

#define REG_LGY_LKEYCNT_L_SHIFT                            9
#define REG_LGY_LKEYCNT_L_SIZE                             1
#define REG_LGY_LKEYCNT_L_MASK                             0x0200

#define REG_LGY_LKEYCNT_R_SHIFT                            8
#define REG_LGY_LKEYCNT_R_SIZE                             1
#define REG_LGY_LKEYCNT_R_MASK                             0x0100

#define REG_LGY_LKEYCNT_DOWN_SHIFT                         7
#define REG_LGY_LKEYCNT_DOWN_SIZE                          1
#define REG_LGY_LKEYCNT_DOWN_MASK                          0x0080

#define REG_LGY_LKEYCNT_UP_SHIFT                           6
#define REG_LGY_LKEYCNT_UP_SIZE                            1
#define REG_LGY_LKEYCNT_UP_MASK                            0x0040

#define REG_LGY_LKEYCNT_LEFT_SHIFT                         5
#define REG_LGY_LKEYCNT_LEFT_SIZE                          1
#define REG_LGY_LKEYCNT_LEFT_MASK                          0x0020

#define REG_LGY_LKEYCNT_RIGHT_SHIFT                        4
#define REG_LGY_LKEYCNT_RIGHT_SIZE                         1
#define REG_LGY_LKEYCNT_RIGHT_MASK                         0x0010

#define REG_LGY_LKEYCNT_START_SHIFT                        3
#define REG_LGY_LKEYCNT_START_SIZE                         1
#define REG_LGY_LKEYCNT_START_MASK                         0x0008

#define REG_LGY_LKEYCNT_SEL_SHIFT                          2
#define REG_LGY_LKEYCNT_SEL_SIZE                           1
#define REG_LGY_LKEYCNT_SEL_MASK                           0x0004

#define REG_LGY_LKEYCNT_B_SHIFT                            1
#define REG_LGY_LKEYCNT_B_SIZE                             1
#define REG_LGY_LKEYCNT_B_MASK                             0x0002

#define REG_LGY_LKEYCNT_A_SHIFT                            0
#define REG_LGY_LKEYCNT_A_SIZE                             1
#define REG_LGY_LKEYCNT_A_MASK                             0x0001

#ifndef SDK_ASM
#define REG_LGY_LKEYCNT_FIELD( logic, intr, l, r, down, up, left, right, start, sel, b, a ) \
    (u16)( \
    ((u32)(logic) << REG_LGY_LKEYCNT_LOGIC_SHIFT) | \
    ((u32)(intr) << REG_LGY_LKEYCNT_INTR_SHIFT) | \
    ((u32)(l) << REG_LGY_LKEYCNT_L_SHIFT) | \
    ((u32)(r) << REG_LGY_LKEYCNT_R_SHIFT) | \
    ((u32)(down) << REG_LGY_LKEYCNT_DOWN_SHIFT) | \
    ((u32)(up) << REG_LGY_LKEYCNT_UP_SHIFT) | \
    ((u32)(left) << REG_LGY_LKEYCNT_LEFT_SHIFT) | \
    ((u32)(right) << REG_LGY_LKEYCNT_RIGHT_SHIFT) | \
    ((u32)(start) << REG_LGY_LKEYCNT_START_SHIFT) | \
    ((u32)(sel) << REG_LGY_LKEYCNT_SEL_SHIFT) | \
    ((u32)(b) << REG_LGY_LKEYCNT_B_SHIFT) | \
    ((u32)(a) << REG_LGY_LKEYCNT_A_SHIFT))
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


/* LDETMSEL */

#define REG_LGY_LDETMSEL_DET_SHIFT                         0
#define REG_LGY_LDETMSEL_DET_SIZE                          1
#define REG_LGY_LDETMSEL_DET_MASK                          0x01

#ifndef SDK_ASM
#define REG_LGY_LDETMSEL_FIELD( det ) \
    (u8)( \
    ((u32)(det) << REG_LGY_LDETMSEL_DET_SHIFT))
#endif


/* LDETMVAL */

#define REG_LGY_LDETMVAL_DET_SHIFT                         0
#define REG_LGY_LDETMVAL_DET_SIZE                          1
#define REG_LGY_LDETMVAL_DET_MASK                          0x01

#ifndef SDK_ASM
#define REG_LGY_LDETMVAL_FIELD( det ) \
    (u8)( \
    ((u32)(det) << REG_LGY_LDETMVAL_DET_SHIFT))
#endif


/* LSTAT */

#define REG_LGY_LSTAT_LCD_CAP_SHIFT                        7
#define REG_LGY_LSTAT_LCD_CAP_SIZE                         1
#define REG_LGY_LSTAT_LCD_CAP_MASK                         0x80

#define REG_LGY_LSTAT_LCD_SWAP_SHIFT                       6
#define REG_LGY_LSTAT_LCD_SWAP_SIZE                        1
#define REG_LGY_LSTAT_LCD_SWAP_MASK                        0x40

#define REG_LGY_LSTAT_VRAM_D_SHIFT                         3
#define REG_LGY_LSTAT_VRAM_D_SIZE                          3
#define REG_LGY_LSTAT_VRAM_D_MASK                          0x38

#define REG_LGY_LSTAT_VRAM_C_SHIFT                         0
#define REG_LGY_LSTAT_VRAM_C_SIZE                          3
#define REG_LGY_LSTAT_VRAM_C_MASK                          0x07

#ifndef SDK_ASM
#define REG_LGY_LSTAT_FIELD( lcd_cap, lcd_swap, vram_d, vram_c ) \
    (u8)( \
    ((u32)(lcd_cap) << REG_LGY_LSTAT_LCD_CAP_SHIFT) | \
    ((u32)(lcd_swap) << REG_LGY_LSTAT_LCD_SWAP_SHIFT) | \
    ((u32)(vram_d) << REG_LGY_LSTAT_VRAM_D_SHIFT) | \
    ((u32)(vram_c) << REG_LGY_LSTAT_VRAM_C_SHIFT))
#endif


/* RTC_CNT */

#define REG_LGY_RTC_CNT_DS_SI_SHIFT                        15
#define REG_LGY_RTC_CNT_DS_SI_SIZE                         1
#define REG_LGY_RTC_CNT_DS_SI_MASK                         0x8000

#define REG_LGY_RTC_CNT_A7_W1_SHIFT                        14
#define REG_LGY_RTC_CNT_A7_W1_SIZE                         1
#define REG_LGY_RTC_CNT_A7_W1_MASK                         0x4000

#define REG_LGY_RTC_CNT_A7_W0_SHIFT                        13
#define REG_LGY_RTC_CNT_A7_W0_SIZE                         1
#define REG_LGY_RTC_CNT_A7_W0_MASK                         0x2000

#define REG_LGY_RTC_CNT_A7_BUSY_SHIFT                      12
#define REG_LGY_RTC_CNT_A7_BUSY_SIZE                       1
#define REG_LGY_RTC_CNT_A7_BUSY_MASK                       0x1000

#define REG_LGY_RTC_CNT_UP_EA2_SHIFT                       11
#define REG_LGY_RTC_CNT_UP_EA2_SIZE                        1
#define REG_LGY_RTC_CNT_UP_EA2_MASK                        0x0800

#define REG_LGY_RTC_CNT_UP_EA1_SHIFT                       10
#define REG_LGY_RTC_CNT_UP_EA1_SIZE                        1
#define REG_LGY_RTC_CNT_UP_EA1_MASK                        0x0400

#define REG_LGY_RTC_CNT_UP_FO2_SHIFT                       9
#define REG_LGY_RTC_CNT_UP_FO2_SIZE                        1
#define REG_LGY_RTC_CNT_UP_FO2_MASK                        0x0200

#define REG_LGY_RTC_CNT_UP_FO1_SHIFT                       8
#define REG_LGY_RTC_CNT_UP_FO1_SIZE                        1
#define REG_LGY_RTC_CNT_UP_FO1_MASK                        0x0100

#define REG_LGY_RTC_CNT_UP_UPC_SHIFT                       7
#define REG_LGY_RTC_CNT_UP_UPC_SIZE                        1
#define REG_LGY_RTC_CNT_UP_UPC_MASK                        0x0080

#define REG_LGY_RTC_CNT_UP_INT2_SHIFT                      6
#define REG_LGY_RTC_CNT_UP_INT2_SIZE                       1
#define REG_LGY_RTC_CNT_UP_INT2_MASK                       0x0040

#define REG_LGY_RTC_CNT_UP_INT1_SHIFT                      5
#define REG_LGY_RTC_CNT_UP_INT1_SIZE                       1
#define REG_LGY_RTC_CNT_UP_INT1_MASK                       0x0020

#define REG_LGY_RTC_CNT_UP_RTC_SHIFT                       4
#define REG_LGY_RTC_CNT_UP_RTC_SIZE                        1
#define REG_LGY_RTC_CNT_UP_RTC_MASK                        0x0010

#define REG_LGY_RTC_CNT_UP_FREE_SHIFT                      3
#define REG_LGY_RTC_CNT_UP_FREE_SIZE                       1
#define REG_LGY_RTC_CNT_UP_FREE_MASK                       0x0008

#define REG_LGY_RTC_CNT_UP_ADJ_SHIFT                       2
#define REG_LGY_RTC_CNT_UP_ADJ_SIZE                        1
#define REG_LGY_RTC_CNT_UP_ADJ_MASK                        0x0004

#define REG_LGY_RTC_CNT_UP_ST2_SHIFT                       1
#define REG_LGY_RTC_CNT_UP_ST2_SIZE                        1
#define REG_LGY_RTC_CNT_UP_ST2_MASK                        0x0002

#define REG_LGY_RTC_CNT_UP_ST1_SHIFT                       0
#define REG_LGY_RTC_CNT_UP_ST1_SIZE                        1
#define REG_LGY_RTC_CNT_UP_ST1_MASK                        0x0001

#ifndef SDK_ASM
#define REG_LGY_RTC_CNT_FIELD( ds_si, a7_w1, a7_w0, a7_busy, up_ea2, up_ea1, up_fo2, up_fo1, up_upc, up_int2, up_int1, up_rtc, up_free, up_adj, up_st2, up_st1 ) \
    (u16)( \
    ((u32)(ds_si) << REG_LGY_RTC_CNT_DS_SI_SHIFT) | \
    ((u32)(a7_w1) << REG_LGY_RTC_CNT_A7_W1_SHIFT) | \
    ((u32)(a7_w0) << REG_LGY_RTC_CNT_A7_W0_SHIFT) | \
    ((u32)(a7_busy) << REG_LGY_RTC_CNT_A7_BUSY_SHIFT) | \
    ((u32)(up_ea2) << REG_LGY_RTC_CNT_UP_EA2_SHIFT) | \
    ((u32)(up_ea1) << REG_LGY_RTC_CNT_UP_EA1_SHIFT) | \
    ((u32)(up_fo2) << REG_LGY_RTC_CNT_UP_FO2_SHIFT) | \
    ((u32)(up_fo1) << REG_LGY_RTC_CNT_UP_FO1_SHIFT) | \
    ((u32)(up_upc) << REG_LGY_RTC_CNT_UP_UPC_SHIFT) | \
    ((u32)(up_int2) << REG_LGY_RTC_CNT_UP_INT2_SHIFT) | \
    ((u32)(up_int1) << REG_LGY_RTC_CNT_UP_INT1_SHIFT) | \
    ((u32)(up_rtc) << REG_LGY_RTC_CNT_UP_RTC_SHIFT) | \
    ((u32)(up_free) << REG_LGY_RTC_CNT_UP_FREE_SHIFT) | \
    ((u32)(up_adj) << REG_LGY_RTC_CNT_UP_ADJ_SHIFT) | \
    ((u32)(up_st2) << REG_LGY_RTC_CNT_UP_ST2_SHIFT) | \
    ((u32)(up_st1) << REG_LGY_RTC_CNT_UP_ST1_SHIFT))
#endif


/* RTC_STATUS1 */

#define REG_LGY_RTC_STATUS1_RESET_SHIFT                    7
#define REG_LGY_RTC_STATUS1_RESET_SIZE                     1
#define REG_LGY_RTC_STATUS1_RESET_MASK                     0x80

#define REG_LGY_RTC_STATUS1_FORMAT_SHIFT                   6
#define REG_LGY_RTC_STATUS1_FORMAT_SIZE                    1
#define REG_LGY_RTC_STATUS1_FORMAT_MASK                    0x40

#define REG_LGY_RTC_STATUS1_INT1_SHIFT                     3
#define REG_LGY_RTC_STATUS1_INT1_SIZE                      1
#define REG_LGY_RTC_STATUS1_INT1_MASK                      0x08

#define REG_LGY_RTC_STATUS1_INT2_SHIFT                     2
#define REG_LGY_RTC_STATUS1_INT2_SIZE                      1
#define REG_LGY_RTC_STATUS1_INT2_MASK                      0x04

#define REG_LGY_RTC_STATUS1_BLD_SHIFT                      1
#define REG_LGY_RTC_STATUS1_BLD_SIZE                       1
#define REG_LGY_RTC_STATUS1_BLD_MASK                       0x02

#define REG_LGY_RTC_STATUS1_POC_SHIFT                      0
#define REG_LGY_RTC_STATUS1_POC_SIZE                       1
#define REG_LGY_RTC_STATUS1_POC_MASK                       0x01

#ifndef SDK_ASM
#define REG_LGY_RTC_STATUS1_FIELD( reset, format, int1, int2, bld, poc ) \
    (u8)( \
    ((u32)(reset) << REG_LGY_RTC_STATUS1_RESET_SHIFT) | \
    ((u32)(format) << REG_LGY_RTC_STATUS1_FORMAT_SHIFT) | \
    ((u32)(int1) << REG_LGY_RTC_STATUS1_INT1_SHIFT) | \
    ((u32)(int2) << REG_LGY_RTC_STATUS1_INT2_SHIFT) | \
    ((u32)(bld) << REG_LGY_RTC_STATUS1_BLD_SHIFT) | \
    ((u32)(poc) << REG_LGY_RTC_STATUS1_POC_SHIFT))
#endif


/* RTC_STATUS2 */

#define REG_LGY_RTC_STATUS2_INT1FE_SHIFT                   7
#define REG_LGY_RTC_STATUS2_INT1FE_SIZE                    1
#define REG_LGY_RTC_STATUS2_INT1FE_MASK                    0x80

#define REG_LGY_RTC_STATUS2_INT2ME_SHIFT                   6
#define REG_LGY_RTC_STATUS2_INT2ME_SIZE                    1
#define REG_LGY_RTC_STATUS2_INT2ME_MASK                    0x40

#define REG_LGY_RTC_STATUS2_INT1AE_SHIFT                   5
#define REG_LGY_RTC_STATUS2_INT1AE_SIZE                    1
#define REG_LGY_RTC_STATUS2_INT1AE_MASK                    0x20

#define REG_LGY_RTC_STATUS2_F_32KHZ_SHIFT                  4
#define REG_LGY_RTC_STATUS2_F_32KHZ_SIZE                   1
#define REG_LGY_RTC_STATUS2_F_32KHZ_MASK                   0x10

#define REG_LGY_RTC_STATUS2_SC2_SHIFT                      3
#define REG_LGY_RTC_STATUS2_SC2_SIZE                       1
#define REG_LGY_RTC_STATUS2_SC2_MASK                       0x08

#define REG_LGY_RTC_STATUS2_SC3_SHIFT                      2
#define REG_LGY_RTC_STATUS2_SC3_SIZE                       1
#define REG_LGY_RTC_STATUS2_SC3_MASK                       0x04

#define REG_LGY_RTC_STATUS2_INT2AE_SHIFT                   1
#define REG_LGY_RTC_STATUS2_INT2AE_SIZE                    1
#define REG_LGY_RTC_STATUS2_INT2AE_MASK                    0x02

#define REG_LGY_RTC_STATUS2_TEST_SHIFT                     0
#define REG_LGY_RTC_STATUS2_TEST_SIZE                      1
#define REG_LGY_RTC_STATUS2_TEST_MASK                      0x01

#ifndef SDK_ASM
#define REG_LGY_RTC_STATUS2_FIELD( int1fe, int2me, int1ae, f_32khz, sc2, sc3, int2ae, test ) \
    (u8)( \
    ((u32)(int1fe) << REG_LGY_RTC_STATUS2_INT1FE_SHIFT) | \
    ((u32)(int2me) << REG_LGY_RTC_STATUS2_INT2ME_SHIFT) | \
    ((u32)(int1ae) << REG_LGY_RTC_STATUS2_INT1AE_SHIFT) | \
    ((u32)(f_32khz) << REG_LGY_RTC_STATUS2_F_32KHZ_SHIFT) | \
    ((u32)(sc2) << REG_LGY_RTC_STATUS2_SC2_SHIFT) | \
    ((u32)(sc3) << REG_LGY_RTC_STATUS2_SC3_SHIFT) | \
    ((u32)(int2ae) << REG_LGY_RTC_STATUS2_INT2AE_SHIFT) | \
    ((u32)(test) << REG_LGY_RTC_STATUS2_TEST_SHIFT))
#endif


/* RTC_ADJ */

/* RTC_FREE */

/* RTC_DATA1 */

#define REG_LGY_RTC_DATA1_WEEK_SHIFT                       29
#define REG_LGY_RTC_DATA1_WEEK_SIZE                        3
#define REG_LGY_RTC_DATA1_WEEK_MASK                        0xe0000000

#define REG_LGY_RTC_DATA1_HOUR_SHIFT                       18
#define REG_LGY_RTC_DATA1_HOUR_SIZE                        6
#define REG_LGY_RTC_DATA1_HOUR_MASK                        0x00fc0000

#define REG_LGY_RTC_DATA1_PM_SHIFT                         17
#define REG_LGY_RTC_DATA1_PM_SIZE                          1
#define REG_LGY_RTC_DATA1_PM_MASK                          0x00020000

#define REG_LGY_RTC_DATA1_MINITE_SHIFT                     9
#define REG_LGY_RTC_DATA1_MINITE_SIZE                      7
#define REG_LGY_RTC_DATA1_MINITE_MASK                      0x0000fe00

#define REG_LGY_RTC_DATA1_SECOND_SHIFT                     1
#define REG_LGY_RTC_DATA1_SECOND_SIZE                      7
#define REG_LGY_RTC_DATA1_SECOND_MASK                      0x000000fe

#ifndef SDK_ASM
#define REG_LGY_RTC_DATA1_FIELD( week, hour, pm, minite, second ) \
    (u32)( \
    ((u32)(week) << REG_LGY_RTC_DATA1_WEEK_SHIFT) | \
    ((u32)(hour) << REG_LGY_RTC_DATA1_HOUR_SHIFT) | \
    ((u32)(pm) << REG_LGY_RTC_DATA1_PM_SHIFT) | \
    ((u32)(minite) << REG_LGY_RTC_DATA1_MINITE_SHIFT) | \
    ((u32)(second) << REG_LGY_RTC_DATA1_SECOND_SHIFT))
#endif


/* RTC_DATA2 */

#define REG_LGY_RTC_DATA2_YEAR_SHIFT                       16
#define REG_LGY_RTC_DATA2_YEAR_SIZE                        8
#define REG_LGY_RTC_DATA2_YEAR_MASK                        0x00ff0000

#define REG_LGY_RTC_DATA2_MONTH_SHIFT                      11
#define REG_LGY_RTC_DATA2_MONTH_SIZE                       5
#define REG_LGY_RTC_DATA2_MONTH_MASK                       0x0000f800

#define REG_LGY_RTC_DATA2_DAY_SHIFT                        2
#define REG_LGY_RTC_DATA2_DAY_SIZE                         6
#define REG_LGY_RTC_DATA2_DAY_MASK                         0x000000fc

#ifndef SDK_ASM
#define REG_LGY_RTC_DATA2_FIELD( year, month, day ) \
    (u32)( \
    ((u32)(year) << REG_LGY_RTC_DATA2_YEAR_SHIFT) | \
    ((u32)(month) << REG_LGY_RTC_DATA2_MONTH_SHIFT) | \
    ((u32)(day) << REG_LGY_RTC_DATA2_DAY_SHIFT))
#endif


/* RTC_ALM1 */

#define REG_LGY_RTC_ALM1_WEEK_SHIFT                        21
#define REG_LGY_RTC_ALM1_WEEK_SIZE                         3
#define REG_LGY_RTC_ALM1_WEEK_MASK                         0x00e00000

#define REG_LGY_RTC_ALM1_WE_SHIFT                          16
#define REG_LGY_RTC_ALM1_WE_SIZE                           1
#define REG_LGY_RTC_ALM1_WE_MASK                           0x00010000

#define REG_LGY_RTC_ALM1_HOUR_SHIFT                        10
#define REG_LGY_RTC_ALM1_HOUR_SIZE                         6
#define REG_LGY_RTC_ALM1_HOUR_MASK                         0x0000fc00

#define REG_LGY_RTC_ALM1_PM_SHIFT                          9
#define REG_LGY_RTC_ALM1_PM_SIZE                           1
#define REG_LGY_RTC_ALM1_PM_MASK                           0x00000200

#define REG_LGY_RTC_ALM1_HE_SHIFT                          8
#define REG_LGY_RTC_ALM1_HE_SIZE                           1
#define REG_LGY_RTC_ALM1_HE_MASK                           0x00000100

#define REG_LGY_RTC_ALM1_MINITE_SHIFT                      1
#define REG_LGY_RTC_ALM1_MINITE_SIZE                       7
#define REG_LGY_RTC_ALM1_MINITE_MASK                       0x000000fe

#define REG_LGY_RTC_ALM1_ME_SHIFT                          0
#define REG_LGY_RTC_ALM1_ME_SIZE                           1
#define REG_LGY_RTC_ALM1_ME_MASK                           0x00000001

#ifndef SDK_ASM
#define REG_LGY_RTC_ALM1_FIELD( week, we, hour, pm, he, minite, me ) \
    (u32)( \
    ((u32)(week) << REG_LGY_RTC_ALM1_WEEK_SHIFT) | \
    ((u32)(we) << REG_LGY_RTC_ALM1_WE_SHIFT) | \
    ((u32)(hour) << REG_LGY_RTC_ALM1_HOUR_SHIFT) | \
    ((u32)(pm) << REG_LGY_RTC_ALM1_PM_SHIFT) | \
    ((u32)(he) << REG_LGY_RTC_ALM1_HE_SHIFT) | \
    ((u32)(minite) << REG_LGY_RTC_ALM1_MINITE_SHIFT) | \
    ((u32)(me) << REG_LGY_RTC_ALM1_ME_SHIFT))
#endif


/* RTC_ALM2 */

#define REG_LGY_RTC_ALM2_WEEK_SHIFT                        21
#define REG_LGY_RTC_ALM2_WEEK_SIZE                         3
#define REG_LGY_RTC_ALM2_WEEK_MASK                         0x00e00000

#define REG_LGY_RTC_ALM2_WE_SHIFT                          16
#define REG_LGY_RTC_ALM2_WE_SIZE                           1
#define REG_LGY_RTC_ALM2_WE_MASK                           0x00010000

#define REG_LGY_RTC_ALM2_HOUR_SHIFT                        10
#define REG_LGY_RTC_ALM2_HOUR_SIZE                         6
#define REG_LGY_RTC_ALM2_HOUR_MASK                         0x0000fc00

#define REG_LGY_RTC_ALM2_PM_SHIFT                          9
#define REG_LGY_RTC_ALM2_PM_SIZE                           1
#define REG_LGY_RTC_ALM2_PM_MASK                           0x00000200

#define REG_LGY_RTC_ALM2_HE_SHIFT                          8
#define REG_LGY_RTC_ALM2_HE_SIZE                           1
#define REG_LGY_RTC_ALM2_HE_MASK                           0x00000100

#define REG_LGY_RTC_ALM2_MINITE_SHIFT                      1
#define REG_LGY_RTC_ALM2_MINITE_SIZE                       7
#define REG_LGY_RTC_ALM2_MINITE_MASK                       0x000000fe

#define REG_LGY_RTC_ALM2_ME_SHIFT                          0
#define REG_LGY_RTC_ALM2_ME_SIZE                           1
#define REG_LGY_RTC_ALM2_ME_MASK                           0x00000001

#ifndef SDK_ASM
#define REG_LGY_RTC_ALM2_FIELD( week, we, hour, pm, he, minite, me ) \
    (u32)( \
    ((u32)(week) << REG_LGY_RTC_ALM2_WEEK_SHIFT) | \
    ((u32)(we) << REG_LGY_RTC_ALM2_WE_SHIFT) | \
    ((u32)(hour) << REG_LGY_RTC_ALM2_HOUR_SHIFT) | \
    ((u32)(pm) << REG_LGY_RTC_ALM2_PM_SHIFT) | \
    ((u32)(he) << REG_LGY_RTC_ALM2_HE_SHIFT) | \
    ((u32)(minite) << REG_LGY_RTC_ALM2_MINITE_SHIFT) | \
    ((u32)(me) << REG_LGY_RTC_ALM2_ME_SHIFT))
#endif


/* RTC_UPCOUNT */

/* RTC_FOUT1 */

#define REG_LGY_RTC_FOUT1_F_256HZ_SHIFT                    7
#define REG_LGY_RTC_FOUT1_F_256HZ_SIZE                     1
#define REG_LGY_RTC_FOUT1_F_256HZ_MASK                     0x80

#define REG_LGY_RTC_FOUT1_F_512HZ_SHIFT                    6
#define REG_LGY_RTC_FOUT1_F_512HZ_SIZE                     1
#define REG_LGY_RTC_FOUT1_F_512HZ_MASK                     0x40

#define REG_LGY_RTC_FOUT1_F_1KHZ_SHIFT                     5
#define REG_LGY_RTC_FOUT1_F_1KHZ_SIZE                      1
#define REG_LGY_RTC_FOUT1_F_1KHZ_MASK                      0x20

#define REG_LGY_RTC_FOUT1_F_2KHZ_SHIFT                     4
#define REG_LGY_RTC_FOUT1_F_2KHZ_SIZE                      1
#define REG_LGY_RTC_FOUT1_F_2KHZ_MASK                      0x10

#define REG_LGY_RTC_FOUT1_F_4KHZ_SHIFT                     3
#define REG_LGY_RTC_FOUT1_F_4KHZ_SIZE                      1
#define REG_LGY_RTC_FOUT1_F_4KHZ_MASK                      0x08

#define REG_LGY_RTC_FOUT1_F_8KHZ_SHIFT                     2
#define REG_LGY_RTC_FOUT1_F_8KHZ_SIZE                      1
#define REG_LGY_RTC_FOUT1_F_8KHZ_MASK                      0x04

#define REG_LGY_RTC_FOUT1_F_16KHZ_SHIFT                    1
#define REG_LGY_RTC_FOUT1_F_16KHZ_SIZE                     1
#define REG_LGY_RTC_FOUT1_F_16KHZ_MASK                     0x02

#define REG_LGY_RTC_FOUT1_F_32KHZ_SHIFT                    0
#define REG_LGY_RTC_FOUT1_F_32KHZ_SIZE                     1
#define REG_LGY_RTC_FOUT1_F_32KHZ_MASK                     0x01

#ifndef SDK_ASM
#define REG_LGY_RTC_FOUT1_FIELD( f_256hz, f_512hz, f_1khz, f_2khz, f_4khz, f_8khz, f_16khz, f_32khz ) \
    (u8)( \
    ((u32)(f_256hz) << REG_LGY_RTC_FOUT1_F_256HZ_SHIFT) | \
    ((u32)(f_512hz) << REG_LGY_RTC_FOUT1_F_512HZ_SHIFT) | \
    ((u32)(f_1khz) << REG_LGY_RTC_FOUT1_F_1KHZ_SHIFT) | \
    ((u32)(f_2khz) << REG_LGY_RTC_FOUT1_F_2KHZ_SHIFT) | \
    ((u32)(f_4khz) << REG_LGY_RTC_FOUT1_F_4KHZ_SHIFT) | \
    ((u32)(f_8khz) << REG_LGY_RTC_FOUT1_F_8KHZ_SHIFT) | \
    ((u32)(f_16khz) << REG_LGY_RTC_FOUT1_F_16KHZ_SHIFT) | \
    ((u32)(f_32khz) << REG_LGY_RTC_FOUT1_F_32KHZ_SHIFT))
#endif


/* RTC_FOUT2 */

#define REG_LGY_RTC_FOUT2_F_1HZ_SHIFT                      7
#define REG_LGY_RTC_FOUT2_F_1HZ_SIZE                       1
#define REG_LGY_RTC_FOUT2_F_1HZ_MASK                       0x80

#define REG_LGY_RTC_FOUT2_F_2HZ_SHIFT                      6
#define REG_LGY_RTC_FOUT2_F_2HZ_SIZE                       1
#define REG_LGY_RTC_FOUT2_F_2HZ_MASK                       0x40

#define REG_LGY_RTC_FOUT2_F_4KHZ_SHIFT                     5
#define REG_LGY_RTC_FOUT2_F_4KHZ_SIZE                      1
#define REG_LGY_RTC_FOUT2_F_4KHZ_MASK                      0x20

#define REG_LGY_RTC_FOUT2_F_8HZ_SHIFT                      4
#define REG_LGY_RTC_FOUT2_F_8HZ_SIZE                       1
#define REG_LGY_RTC_FOUT2_F_8HZ_MASK                       0x10

#define REG_LGY_RTC_FOUT2_F_16HZ_SHIFT                     3
#define REG_LGY_RTC_FOUT2_F_16HZ_SIZE                      1
#define REG_LGY_RTC_FOUT2_F_16HZ_MASK                      0x08

#define REG_LGY_RTC_FOUT2_F_32HZ_SHIFT                     2
#define REG_LGY_RTC_FOUT2_F_32HZ_SIZE                      1
#define REG_LGY_RTC_FOUT2_F_32HZ_MASK                      0x04

#define REG_LGY_RTC_FOUT2_F_64HZ_SHIFT                     1
#define REG_LGY_RTC_FOUT2_F_64HZ_SIZE                      1
#define REG_LGY_RTC_FOUT2_F_64HZ_MASK                      0x02

#define REG_LGY_RTC_FOUT2_F_128HZ_SHIFT                    0
#define REG_LGY_RTC_FOUT2_F_128HZ_SIZE                     1
#define REG_LGY_RTC_FOUT2_F_128HZ_MASK                     0x01

#ifndef SDK_ASM
#define REG_LGY_RTC_FOUT2_FIELD( f_1hz, f_2hz, f_4khz, f_8hz, f_16hz, f_32hz, f_64hz, f_128hz ) \
    (u8)( \
    ((u32)(f_1hz) << REG_LGY_RTC_FOUT2_F_1HZ_SHIFT) | \
    ((u32)(f_2hz) << REG_LGY_RTC_FOUT2_F_2HZ_SHIFT) | \
    ((u32)(f_4khz) << REG_LGY_RTC_FOUT2_F_4KHZ_SHIFT) | \
    ((u32)(f_8hz) << REG_LGY_RTC_FOUT2_F_8HZ_SHIFT) | \
    ((u32)(f_16hz) << REG_LGY_RTC_FOUT2_F_16HZ_SHIFT) | \
    ((u32)(f_32hz) << REG_LGY_RTC_FOUT2_F_32HZ_SHIFT) | \
    ((u32)(f_64hz) << REG_LGY_RTC_FOUT2_F_64HZ_SHIFT) | \
    ((u32)(f_128hz) << REG_LGY_RTC_FOUT2_F_128HZ_SHIFT))
#endif


/* RTC_ALMEX1 */

#define REG_LGY_RTC_ALMEX1_YEAR_SHIFT                      16
#define REG_LGY_RTC_ALMEX1_YEAR_SIZE                       8
#define REG_LGY_RTC_ALMEX1_YEAR_MASK                       0x00ff0000

#define REG_LGY_RTC_ALMEX1_MONTH_SHIFT                     11
#define REG_LGY_RTC_ALMEX1_MONTH_SIZE                      5
#define REG_LGY_RTC_ALMEX1_MONTH_MASK                      0x0000f800

#define REG_LGY_RTC_ALMEX1_YE_SHIFT                        9
#define REG_LGY_RTC_ALMEX1_YE_SIZE                         1
#define REG_LGY_RTC_ALMEX1_YE_MASK                         0x00000200

#define REG_LGY_RTC_ALMEX1_ME_SHIFT                        8
#define REG_LGY_RTC_ALMEX1_ME_SIZE                         1
#define REG_LGY_RTC_ALMEX1_ME_MASK                         0x00000100

#define REG_LGY_RTC_ALMEX1_DAY_SHIFT                       2
#define REG_LGY_RTC_ALMEX1_DAY_SIZE                        6
#define REG_LGY_RTC_ALMEX1_DAY_MASK                        0x000000fc

#define REG_LGY_RTC_ALMEX1_DE_SHIFT                        0
#define REG_LGY_RTC_ALMEX1_DE_SIZE                         1
#define REG_LGY_RTC_ALMEX1_DE_MASK                         0x00000001

#ifndef SDK_ASM
#define REG_LGY_RTC_ALMEX1_FIELD( year, month, ye, me, day, de ) \
    (u32)( \
    ((u32)(year) << REG_LGY_RTC_ALMEX1_YEAR_SHIFT) | \
    ((u32)(month) << REG_LGY_RTC_ALMEX1_MONTH_SHIFT) | \
    ((u32)(ye) << REG_LGY_RTC_ALMEX1_YE_SHIFT) | \
    ((u32)(me) << REG_LGY_RTC_ALMEX1_ME_SHIFT) | \
    ((u32)(day) << REG_LGY_RTC_ALMEX1_DAY_SHIFT) | \
    ((u32)(de) << REG_LGY_RTC_ALMEX1_DE_SHIFT))
#endif


/* RTC_ALMEX2 */

#define REG_LGY_RTC_ALMEX2_YEAR_SHIFT                      16
#define REG_LGY_RTC_ALMEX2_YEAR_SIZE                       8
#define REG_LGY_RTC_ALMEX2_YEAR_MASK                       0x00ff0000

#define REG_LGY_RTC_ALMEX2_MONTH_SHIFT                     11
#define REG_LGY_RTC_ALMEX2_MONTH_SIZE                      5
#define REG_LGY_RTC_ALMEX2_MONTH_MASK                      0x0000f800

#define REG_LGY_RTC_ALMEX2_YE_SHIFT                        9
#define REG_LGY_RTC_ALMEX2_YE_SIZE                         1
#define REG_LGY_RTC_ALMEX2_YE_MASK                         0x00000200

#define REG_LGY_RTC_ALMEX2_ME_SHIFT                        8
#define REG_LGY_RTC_ALMEX2_ME_SIZE                         1
#define REG_LGY_RTC_ALMEX2_ME_MASK                         0x00000100

#define REG_LGY_RTC_ALMEX2_DAY_SHIFT                       2
#define REG_LGY_RTC_ALMEX2_DAY_SIZE                        6
#define REG_LGY_RTC_ALMEX2_DAY_MASK                        0x000000fc

#define REG_LGY_RTC_ALMEX2_DE_SHIFT                        0
#define REG_LGY_RTC_ALMEX2_DE_SIZE                         1
#define REG_LGY_RTC_ALMEX2_DE_MASK                         0x00000001

#ifndef SDK_ASM
#define REG_LGY_RTC_ALMEX2_FIELD( year, month, ye, me, day, de ) \
    (u32)( \
    ((u32)(year) << REG_LGY_RTC_ALMEX2_YEAR_SHIFT) | \
    ((u32)(month) << REG_LGY_RTC_ALMEX2_MONTH_SHIFT) | \
    ((u32)(ye) << REG_LGY_RTC_ALMEX2_YE_SHIFT) | \
    ((u32)(me) << REG_LGY_RTC_ALMEX2_ME_SHIFT) | \
    ((u32)(day) << REG_LGY_RTC_ALMEX2_DAY_SHIFT) | \
    ((u32)(de) << REG_LGY_RTC_ALMEX2_DE_SHIFT))
#endif


/* SCL1_CNT */

#define REG_LGY_SCL1_CNT_IFMT_SHIFT                        16
#define REG_LGY_SCL1_CNT_IFMT_SIZE                         1
#define REG_LGY_SCL1_CNT_IFMT_MASK                         0x00010000

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
#define REG_LGY_SCL1_CNT_FIELD( ifmt, dreq_e, bf, rot, pf, td_e, sd_e, h_e, v_e, e ) \
    (u32)( \
    ((u32)(ifmt) << REG_LGY_SCL1_CNT_IFMT_SHIFT) | \
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

#define REG_LGY_SCL2_CNT_IFMT_SHIFT                        16
#define REG_LGY_SCL2_CNT_IFMT_SIZE                         1
#define REG_LGY_SCL2_CNT_IFMT_MASK                         0x00010000

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
#define REG_LGY_SCL2_CNT_FIELD( ifmt, dreq_e, bf, rot, pf, td_e, sd_e, h_e, v_e, e ) \
    (u32)( \
    ((u32)(ifmt) << REG_LGY_SCL2_CNT_IFMT_SHIFT) | \
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


/* SCL2_VADVPAT */

#define REG_LGY_SCL2_VADVPAT_AP_SHIFT                      0
#define REG_LGY_SCL2_VADVPAT_AP_SIZE                       8
#define REG_LGY_SCL2_VADVPAT_AP_MASK                       0x000000ff

#ifndef SDK_ASM
#define REG_LGY_SCL2_VADVPAT_FIELD( ap ) \
    (u32)( \
    ((u32)(ap) << REG_LGY_SCL2_VADVPAT_AP_SHIFT))
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

/* NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_LGY_H_ */
#endif
