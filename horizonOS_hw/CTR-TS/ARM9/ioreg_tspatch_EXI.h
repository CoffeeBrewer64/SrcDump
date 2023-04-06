/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TS/ARM9/ioreg_tspatch_EXI.h

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
#ifndef NN_HW_CTR_TS_ARM9_IOREG_TSPATCH_EXI_H_
#define NN_HW_CTR_TS_ARM9_IOREG_TSPATCH_EXI_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* GPIO1_DAT */

#define REG_GPIO1_DAT_OFFSET                               0x147000
#define REG_GPIO1_DAT_ADDR                                 (HW_REG_BASE + REG_GPIO1_DAT_OFFSET)
#define reg_EXI_GPIO1_DAT                                  (*(const REGType8v *) REG_GPIO1_DAT_ADDR)

/* GPIO2_DAT */

#define REG_GPIO2_DAT_OFFSET                               0x147010
#define REG_GPIO2_DAT_ADDR                                 (HW_REG_BASE + REG_GPIO2_DAT_OFFSET)
#define reg_EXI_GPIO2_DAT                                  (*( REGType8v *) REG_GPIO2_DAT_ADDR)

/* GPIO2_DIR */

#define REG_GPIO2_DIR_OFFSET                               0x147011
#define REG_GPIO2_DIR_ADDR                                 (HW_REG_BASE + REG_GPIO2_DIR_OFFSET)
#define reg_EXI_GPIO2_DIR                                  (*( REGType8v *) REG_GPIO2_DIR_ADDR)

/* GPIO2_IM */

#define REG_GPIO2_IM_OFFSET                                0x147012
#define REG_GPIO2_IM_ADDR                                  (HW_REG_BASE + REG_GPIO2_IM_OFFSET)
#define reg_EXI_GPIO2_IM                                   (*( REGType8v *) REG_GPIO2_IM_ADDR)

/* GPIO2_IE */

#define REG_GPIO2_IE_OFFSET                                0x147013
#define REG_GPIO2_IE_ADDR                                  (HW_REG_BASE + REG_GPIO2_IE_OFFSET)
#define reg_EXI_GPIO2_IE                                   (*( REGType8v *) REG_GPIO2_IE_ADDR)

/* GPIO2_CNT2 */

#define REG_GPIO2_CNT2_OFFSET                              0x147014
#define REG_GPIO2_CNT2_ADDR                                (HW_REG_BASE + REG_GPIO2_CNT2_OFFSET)
#define reg_EXI_GPIO2_CNT2                                 (*( REGType16v *) REG_GPIO2_CNT2_ADDR)

/* GPIO3_CNT */

#define REG_GPIO3_CNT_OFFSET                               0x147020
#define REG_GPIO3_CNT_ADDR                                 (HW_REG_BASE + REG_GPIO3_CNT_OFFSET)
#define reg_EXI_GPIO3_CNT                                  (*( REGType32v *) REG_GPIO3_CNT_ADDR)

/* GPIO3_DAT */

#define REG_GPIO3_DAT_OFFSET                               0x147020
#define REG_GPIO3_DAT_ADDR                                 (HW_REG_BASE + REG_GPIO3_DAT_OFFSET)
#define reg_EXI_GPIO3_DAT                                  (*( REGType16v *) REG_GPIO3_DAT_ADDR)

/* GPIO3_DIR */

#define REG_GPIO3_DIR_OFFSET                               0x147022
#define REG_GPIO3_DIR_ADDR                                 (HW_REG_BASE + REG_GPIO3_DIR_OFFSET)
#define reg_EXI_GPIO3_DIR                                  (*( REGType16v *) REG_GPIO3_DIR_ADDR)

/* GPIO3_CNT2 */

#define REG_GPIO3_CNT2_OFFSET                              0x147024
#define REG_GPIO3_CNT2_ADDR                                (HW_REG_BASE + REG_GPIO3_CNT2_OFFSET)
#define reg_EXI_GPIO3_CNT2                                 (*( REGType32v *) REG_GPIO3_CNT2_ADDR)

/* GPIO3_IM */

#define REG_GPIO3_IM_OFFSET                                0x147024
#define REG_GPIO3_IM_ADDR                                  (HW_REG_BASE + REG_GPIO3_IM_OFFSET)
#define reg_EXI_GPIO3_IM                                   (*( REGType16v *) REG_GPIO3_IM_ADDR)

/* GPIO3_IE */

#define REG_GPIO3_IE_OFFSET                                0x147026
#define REG_GPIO3_IE_ADDR                                  (HW_REG_BASE + REG_GPIO3_IE_OFFSET)
#define reg_EXI_GPIO3_IE                                   (*( REGType16v *) REG_GPIO3_IE_ADDR)

/* GPIO3_OCNT */

#define REG_GPIO3_OCNT_OFFSET                              0x147028
#define REG_GPIO3_OCNT_ADDR                                (HW_REG_BASE + REG_GPIO3_OCNT_OFFSET)
#define reg_EXI_GPIO3_OCNT                                 (*( REGType16v *) REG_GPIO3_OCNT_ADDR)


/*
 * Definitions of Register fields
 */


/* GPIO1_DAT */

#define REG_EXI_GPIO1_DAT_COVER_SHIFT                      2
#define REG_EXI_GPIO1_DAT_COVER_SIZE                       1
#define REG_EXI_GPIO1_DAT_COVER_MASK                       0x04

#define REG_EXI_GPIO1_DAT_TP_SHIFT                         1
#define REG_EXI_GPIO1_DAT_TP_SIZE                          1
#define REG_EXI_GPIO1_DAT_TP_MASK                          0x02

#define REG_EXI_GPIO1_DAT_DEBUG_SHIFT                      0
#define REG_EXI_GPIO1_DAT_DEBUG_SIZE                       1
#define REG_EXI_GPIO1_DAT_DEBUG_MASK                       0x01

#define REG_EXI_GPIO1_DAT_R7_SHIFT                         2
#define REG_EXI_GPIO1_DAT_R7_SIZE                          1
#define REG_EXI_GPIO1_DAT_R7_MASK                          0x04

#define REG_EXI_GPIO1_DAT_R6_SHIFT                         1
#define REG_EXI_GPIO1_DAT_R6_SIZE                          1
#define REG_EXI_GPIO1_DAT_R6_MASK                          0x02

#define REG_EXI_GPIO1_DAT_R3_SHIFT                         0
#define REG_EXI_GPIO1_DAT_R3_SIZE                          1
#define REG_EXI_GPIO1_DAT_R3_MASK                          0x01

#ifndef SDK_ASM
#define REG_EXI_GPIO1_DAT_FIELD( cover, tp, debug, r7, r6, r3 ) \
    (u8)( \
    ((u32)(cover) << REG_EXI_GPIO1_DAT_COVER_SHIFT) | \
    ((u32)(tp) << REG_EXI_GPIO1_DAT_TP_SHIFT) | \
    ((u32)(debug) << REG_EXI_GPIO1_DAT_DEBUG_SHIFT) | \
    ((u32)(r7) << REG_EXI_GPIO1_DAT_R7_SHIFT) | \
    ((u32)(r6) << REG_EXI_GPIO1_DAT_R6_SHIFT) | \
    ((u32)(r3) << REG_EXI_GPIO1_DAT_R3_SHIFT))
#endif


/* GPIO2_DAT */

#define REG_EXI_GPIO2_DAT_TWL_DEPOP_SHIFT                  1
#define REG_EXI_GPIO2_DAT_TWL_DEPOP_SIZE                   1
#define REG_EXI_GPIO2_DAT_TWL_DEPOP_MASK                   0x02

#define REG_EXI_GPIO2_DAT_HP_SHIFT                         0
#define REG_EXI_GPIO2_DAT_HP_SIZE                          1
#define REG_EXI_GPIO2_DAT_HP_MASK                          0x01

#define REG_EXI_GPIO2_DAT_R7_SHIFT                         1
#define REG_EXI_GPIO2_DAT_R7_SIZE                          1
#define REG_EXI_GPIO2_DAT_R7_MASK                          0x02

#define REG_EXI_GPIO2_DAT_R5_SHIFT                         0
#define REG_EXI_GPIO2_DAT_R5_SIZE                          1
#define REG_EXI_GPIO2_DAT_R5_MASK                          0x01

#ifndef SDK_ASM
#define REG_EXI_GPIO2_DAT_FIELD( twl_depop, hp, r7, r5 ) \
    (u8)( \
    ((u32)(twl_depop) << REG_EXI_GPIO2_DAT_TWL_DEPOP_SHIFT) | \
    ((u32)(hp) << REG_EXI_GPIO2_DAT_HP_SHIFT) | \
    ((u32)(r7) << REG_EXI_GPIO2_DAT_R7_SHIFT) | \
    ((u32)(r5) << REG_EXI_GPIO2_DAT_R5_SHIFT))
#endif


/* GPIO2_DIR */

#define REG_EXI_GPIO2_DIR_TWL_DEPOP_SHIFT                  1
#define REG_EXI_GPIO2_DIR_TWL_DEPOP_SIZE                   1
#define REG_EXI_GPIO2_DIR_TWL_DEPOP_MASK                   0x02

#define REG_EXI_GPIO2_DIR_HP_SHIFT                         0
#define REG_EXI_GPIO2_DIR_HP_SIZE                          1
#define REG_EXI_GPIO2_DIR_HP_MASK                          0x01

#define REG_EXI_GPIO2_DIR_DR7_SHIFT                        1
#define REG_EXI_GPIO2_DIR_DR7_SIZE                         1
#define REG_EXI_GPIO2_DIR_DR7_MASK                         0x02

#define REG_EXI_GPIO2_DIR_DR5_SHIFT                        0
#define REG_EXI_GPIO2_DIR_DR5_SIZE                         1
#define REG_EXI_GPIO2_DIR_DR5_MASK                         0x01

#ifndef SDK_ASM
#define REG_EXI_GPIO2_DIR_FIELD( twl_depop, hp, dr7, dr5 ) \
    (u8)( \
    ((u32)(twl_depop) << REG_EXI_GPIO2_DIR_TWL_DEPOP_SHIFT) | \
    ((u32)(hp) << REG_EXI_GPIO2_DIR_HP_SHIFT) | \
    ((u32)(dr7) << REG_EXI_GPIO2_DIR_DR7_SHIFT) | \
    ((u32)(dr5) << REG_EXI_GPIO2_DIR_DR5_SHIFT))
#endif


/* GPIO2_IM */

#define REG_EXI_GPIO2_IM_TWL_DEPOP_SHIFT                   1
#define REG_EXI_GPIO2_IM_TWL_DEPOP_SIZE                    1
#define REG_EXI_GPIO2_IM_TWL_DEPOP_MASK                    0x02

#define REG_EXI_GPIO2_IM_HP_SHIFT                          0
#define REG_EXI_GPIO2_IM_HP_SIZE                           1
#define REG_EXI_GPIO2_IM_HP_MASK                           0x01

#define REG_EXI_GPIO2_IM_IM7_SHIFT                         1
#define REG_EXI_GPIO2_IM_IM7_SIZE                          1
#define REG_EXI_GPIO2_IM_IM7_MASK                          0x02

#define REG_EXI_GPIO2_IM_IM5_SHIFT                         0
#define REG_EXI_GPIO2_IM_IM5_SIZE                          1
#define REG_EXI_GPIO2_IM_IM5_MASK                          0x01

#ifndef SDK_ASM
#define REG_EXI_GPIO2_IM_FIELD( twl_depop, hp, im7, im5 ) \
    (u8)( \
    ((u32)(twl_depop) << REG_EXI_GPIO2_IM_TWL_DEPOP_SHIFT) | \
    ((u32)(hp) << REG_EXI_GPIO2_IM_HP_SHIFT) | \
    ((u32)(im7) << REG_EXI_GPIO2_IM_IM7_SHIFT) | \
    ((u32)(im5) << REG_EXI_GPIO2_IM_IM5_SHIFT))
#endif


/* GPIO2_IE */

#define REG_EXI_GPIO2_IE_TWL_DEPOP_SHIFT                   1
#define REG_EXI_GPIO2_IE_TWL_DEPOP_SIZE                    1
#define REG_EXI_GPIO2_IE_TWL_DEPOP_MASK                    0x02

#define REG_EXI_GPIO2_IE_HP_SHIFT                          0
#define REG_EXI_GPIO2_IE_HP_SIZE                           1
#define REG_EXI_GPIO2_IE_HP_MASK                           0x01

#define REG_EXI_GPIO2_IE_IE7_SHIFT                         1
#define REG_EXI_GPIO2_IE_IE7_SIZE                          1
#define REG_EXI_GPIO2_IE_IE7_MASK                          0x02

#define REG_EXI_GPIO2_IE_IE5_SHIFT                         0
#define REG_EXI_GPIO2_IE_IE5_SIZE                          1
#define REG_EXI_GPIO2_IE_IE5_MASK                          0x01

#ifndef SDK_ASM
#define REG_EXI_GPIO2_IE_FIELD( twl_depop, hp, ie7, ie5 ) \
    (u8)( \
    ((u32)(twl_depop) << REG_EXI_GPIO2_IE_TWL_DEPOP_SHIFT) | \
    ((u32)(hp) << REG_EXI_GPIO2_IE_HP_SHIFT) | \
    ((u32)(ie7) << REG_EXI_GPIO2_IE_IE7_SHIFT) | \
    ((u32)(ie5) << REG_EXI_GPIO2_IE_IE5_SHIFT))
#endif


/* GPIO2_CNT2 */

#define REG_EXI_GPIO2_CNT2_RF_SEL_SHIFT                    0
#define REG_EXI_GPIO2_CNT2_RF_SEL_SIZE                     1
#define REG_EXI_GPIO2_CNT2_RF_SEL_MASK                     0x0001

#ifndef SDK_ASM
#define REG_EXI_GPIO2_CNT2_FIELD( rf_sel ) \
    (u16)( \
    ((u32)(rf_sel) << REG_EXI_GPIO2_CNT2_RF_SEL_SHIFT))
#endif


/* GPIO3_CNT */

#define REG_EXI_GPIO3_CNT_DR11_SHIFT                       27
#define REG_EXI_GPIO3_CNT_DR11_SIZE                        1
#define REG_EXI_GPIO3_CNT_DR11_MASK                        0x08000000

#define REG_EXI_GPIO3_CNT_DR10_SHIFT                       26
#define REG_EXI_GPIO3_CNT_DR10_SIZE                        1
#define REG_EXI_GPIO3_CNT_DR10_MASK                        0x04000000

#define REG_EXI_GPIO3_CNT_DR9_SHIFT                        25
#define REG_EXI_GPIO3_CNT_DR9_SIZE                         1
#define REG_EXI_GPIO3_CNT_DR9_MASK                         0x02000000

#define REG_EXI_GPIO3_CNT_DR8_SHIFT                        24
#define REG_EXI_GPIO3_CNT_DR8_SIZE                         1
#define REG_EXI_GPIO3_CNT_DR8_MASK                         0x01000000

#define REG_EXI_GPIO3_CNT_DR7_SHIFT                        23
#define REG_EXI_GPIO3_CNT_DR7_SIZE                         1
#define REG_EXI_GPIO3_CNT_DR7_MASK                         0x00800000

#define REG_EXI_GPIO3_CNT_DR6_SHIFT                        22
#define REG_EXI_GPIO3_CNT_DR6_SIZE                         1
#define REG_EXI_GPIO3_CNT_DR6_MASK                         0x00400000

#define REG_EXI_GPIO3_CNT_DR5_SHIFT                        21
#define REG_EXI_GPIO3_CNT_DR5_SIZE                         1
#define REG_EXI_GPIO3_CNT_DR5_MASK                         0x00200000

#define REG_EXI_GPIO3_CNT_DR4_SHIFT                        20
#define REG_EXI_GPIO3_CNT_DR4_SIZE                         1
#define REG_EXI_GPIO3_CNT_DR4_MASK                         0x00100000

#define REG_EXI_GPIO3_CNT_DR3_SHIFT                        19
#define REG_EXI_GPIO3_CNT_DR3_SIZE                         1
#define REG_EXI_GPIO3_CNT_DR3_MASK                         0x00080000

#define REG_EXI_GPIO3_CNT_DR2_SHIFT                        18
#define REG_EXI_GPIO3_CNT_DR2_SIZE                         1
#define REG_EXI_GPIO3_CNT_DR2_MASK                         0x00040000

#define REG_EXI_GPIO3_CNT_DR1_SHIFT                        17
#define REG_EXI_GPIO3_CNT_DR1_SIZE                         1
#define REG_EXI_GPIO3_CNT_DR1_MASK                         0x00020000

#define REG_EXI_GPIO3_CNT_DR0_SHIFT                        16
#define REG_EXI_GPIO3_CNT_DR0_SIZE                         1
#define REG_EXI_GPIO3_CNT_DR0_MASK                         0x00010000

#define REG_EXI_GPIO3_CNT_R11_SHIFT                        11
#define REG_EXI_GPIO3_CNT_R11_SIZE                         1
#define REG_EXI_GPIO3_CNT_R11_MASK                         0x00000800

#define REG_EXI_GPIO3_CNT_R10_SHIFT                        10
#define REG_EXI_GPIO3_CNT_R10_SIZE                         1
#define REG_EXI_GPIO3_CNT_R10_MASK                         0x00000400

#define REG_EXI_GPIO3_CNT_R9_SHIFT                         9
#define REG_EXI_GPIO3_CNT_R9_SIZE                          1
#define REG_EXI_GPIO3_CNT_R9_MASK                          0x00000200

#define REG_EXI_GPIO3_CNT_R8_SHIFT                         8
#define REG_EXI_GPIO3_CNT_R8_SIZE                          1
#define REG_EXI_GPIO3_CNT_R8_MASK                          0x00000100

#define REG_EXI_GPIO3_CNT_R7_SHIFT                         7
#define REG_EXI_GPIO3_CNT_R7_SIZE                          1
#define REG_EXI_GPIO3_CNT_R7_MASK                          0x00000080

#define REG_EXI_GPIO3_CNT_R6_SHIFT                         6
#define REG_EXI_GPIO3_CNT_R6_SIZE                          1
#define REG_EXI_GPIO3_CNT_R6_MASK                          0x00000040

#define REG_EXI_GPIO3_CNT_R5_SHIFT                         5
#define REG_EXI_GPIO3_CNT_R5_SIZE                          1
#define REG_EXI_GPIO3_CNT_R5_MASK                          0x00000020

#define REG_EXI_GPIO3_CNT_R4_SHIFT                         4
#define REG_EXI_GPIO3_CNT_R4_SIZE                          1
#define REG_EXI_GPIO3_CNT_R4_MASK                          0x00000010

#define REG_EXI_GPIO3_CNT_R3_SHIFT                         3
#define REG_EXI_GPIO3_CNT_R3_SIZE                          1
#define REG_EXI_GPIO3_CNT_R3_MASK                          0x00000008

#define REG_EXI_GPIO3_CNT_R2_SHIFT                         2
#define REG_EXI_GPIO3_CNT_R2_SIZE                          1
#define REG_EXI_GPIO3_CNT_R2_MASK                          0x00000004

#define REG_EXI_GPIO3_CNT_R1_SHIFT                         1
#define REG_EXI_GPIO3_CNT_R1_SIZE                          1
#define REG_EXI_GPIO3_CNT_R1_MASK                          0x00000002

#define REG_EXI_GPIO3_CNT_R0_SHIFT                         0
#define REG_EXI_GPIO3_CNT_R0_SIZE                          1
#define REG_EXI_GPIO3_CNT_R0_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_EXI_GPIO3_CNT_FIELD( dr11, dr10, dr9, dr8, dr7, dr6, dr5, dr4, dr3, dr2, dr1, dr0, r11, r10, r9, r8, r7, r6, r5, r4, r3, r2, r1, r0 ) \
    (u32)( \
    ((u32)(dr11) << REG_EXI_GPIO3_CNT_DR11_SHIFT) | \
    ((u32)(dr10) << REG_EXI_GPIO3_CNT_DR10_SHIFT) | \
    ((u32)(dr9) << REG_EXI_GPIO3_CNT_DR9_SHIFT) | \
    ((u32)(dr8) << REG_EXI_GPIO3_CNT_DR8_SHIFT) | \
    ((u32)(dr7) << REG_EXI_GPIO3_CNT_DR7_SHIFT) | \
    ((u32)(dr6) << REG_EXI_GPIO3_CNT_DR6_SHIFT) | \
    ((u32)(dr5) << REG_EXI_GPIO3_CNT_DR5_SHIFT) | \
    ((u32)(dr4) << REG_EXI_GPIO3_CNT_DR4_SHIFT) | \
    ((u32)(dr3) << REG_EXI_GPIO3_CNT_DR3_SHIFT) | \
    ((u32)(dr2) << REG_EXI_GPIO3_CNT_DR2_SHIFT) | \
    ((u32)(dr1) << REG_EXI_GPIO3_CNT_DR1_SHIFT) | \
    ((u32)(dr0) << REG_EXI_GPIO3_CNT_DR0_SHIFT) | \
    ((u32)(r11) << REG_EXI_GPIO3_CNT_R11_SHIFT) | \
    ((u32)(r10) << REG_EXI_GPIO3_CNT_R10_SHIFT) | \
    ((u32)(r9) << REG_EXI_GPIO3_CNT_R9_SHIFT) | \
    ((u32)(r8) << REG_EXI_GPIO3_CNT_R8_SHIFT) | \
    ((u32)(r7) << REG_EXI_GPIO3_CNT_R7_SHIFT) | \
    ((u32)(r6) << REG_EXI_GPIO3_CNT_R6_SHIFT) | \
    ((u32)(r5) << REG_EXI_GPIO3_CNT_R5_SHIFT) | \
    ((u32)(r4) << REG_EXI_GPIO3_CNT_R4_SHIFT) | \
    ((u32)(r3) << REG_EXI_GPIO3_CNT_R3_SHIFT) | \
    ((u32)(r2) << REG_EXI_GPIO3_CNT_R2_SHIFT) | \
    ((u32)(r1) << REG_EXI_GPIO3_CNT_R1_SHIFT) | \
    ((u32)(r0) << REG_EXI_GPIO3_CNT_R0_SHIFT))
#endif


/* GPIO3_DAT */

#define REG_EXI_GPIO3_DAT_LCD_RST_TEG2_SHIFT               10
#define REG_EXI_GPIO3_DAT_LCD_RST_TEG2_SIZE                1
#define REG_EXI_GPIO3_DAT_LCD_RST_TEG2_MASK                0x0400

#define REG_EXI_GPIO3_DAT_CTR_MCU_SHIFT                    9
#define REG_EXI_GPIO3_DAT_CTR_MCU_SIZE                     1
#define REG_EXI_GPIO3_DAT_CTR_MCU_MASK                     0x0200

#define REG_EXI_GPIO3_DAT_RMC_SHIFT                        8
#define REG_EXI_GPIO3_DAT_RMC_SIZE                         1
#define REG_EXI_GPIO3_DAT_RMC_MASK                         0x0100

#define REG_EXI_GPIO3_DAT_PWM_SEL_TEG2_SHIFT               7
#define REG_EXI_GPIO3_DAT_PWM_SEL_TEG2_SIZE                1
#define REG_EXI_GPIO3_DAT_PWM_SEL_TEG2_MASK                0x0080

#define REG_EXI_GPIO3_DAT_WL_OFF_TEG2_SHIFT                6
#define REG_EXI_GPIO3_DAT_WL_OFF_TEG2_SIZE                 1
#define REG_EXI_GPIO3_DAT_WL_OFF_TEG2_MASK                 0x0040

#define REG_EXI_GPIO3_DAT_MIC_SEL_TEG2_SHIFT               5
#define REG_EXI_GPIO3_DAT_MIC_SEL_TEG2_SIZE                1
#define REG_EXI_GPIO3_DAT_MIC_SEL_TEG2_MASK                0x0020

#define REG_EXI_GPIO3_DAT_TP_SEL_TEG2_SHIFT                4
#define REG_EXI_GPIO3_DAT_TP_SEL_TEG2_SIZE                 1
#define REG_EXI_GPIO3_DAT_TP_SEL_TEG2_MASK                 0x0010

#define REG_EXI_GPIO3_DAT_WL_RST_TEG2_SHIFT                1
#define REG_EXI_GPIO3_DAT_WL_RST_TEG2_SIZE                 1
#define REG_EXI_GPIO3_DAT_WL_RST_TEG2_MASK                 0x0002

#define REG_EXI_GPIO3_DAT_SP_SEL_SHIFT                     0
#define REG_EXI_GPIO3_DAT_SP_SEL_SIZE                      1
#define REG_EXI_GPIO3_DAT_SP_SEL_MASK                      0x0001

#define REG_EXI_GPIO3_DAT_R11_SHIFT                        11
#define REG_EXI_GPIO3_DAT_R11_SIZE                         1
#define REG_EXI_GPIO3_DAT_R11_MASK                         0x0800

#define REG_EXI_GPIO3_DAT_R10_SHIFT                        10
#define REG_EXI_GPIO3_DAT_R10_SIZE                         1
#define REG_EXI_GPIO3_DAT_R10_MASK                         0x0400

#define REG_EXI_GPIO3_DAT_R9_SHIFT                         9
#define REG_EXI_GPIO3_DAT_R9_SIZE                          1
#define REG_EXI_GPIO3_DAT_R9_MASK                          0x0200

#define REG_EXI_GPIO3_DAT_R8_SHIFT                         8
#define REG_EXI_GPIO3_DAT_R8_SIZE                          1
#define REG_EXI_GPIO3_DAT_R8_MASK                          0x0100

#define REG_EXI_GPIO3_DAT_R7_SHIFT                         7
#define REG_EXI_GPIO3_DAT_R7_SIZE                          1
#define REG_EXI_GPIO3_DAT_R7_MASK                          0x0080

#define REG_EXI_GPIO3_DAT_R6_SHIFT                         6
#define REG_EXI_GPIO3_DAT_R6_SIZE                          1
#define REG_EXI_GPIO3_DAT_R6_MASK                          0x0040

#define REG_EXI_GPIO3_DAT_R5_SHIFT                         5
#define REG_EXI_GPIO3_DAT_R5_SIZE                          1
#define REG_EXI_GPIO3_DAT_R5_MASK                          0x0020

#define REG_EXI_GPIO3_DAT_R4_SHIFT                         4
#define REG_EXI_GPIO3_DAT_R4_SIZE                          1
#define REG_EXI_GPIO3_DAT_R4_MASK                          0x0010

#define REG_EXI_GPIO3_DAT_R3_SHIFT                         3
#define REG_EXI_GPIO3_DAT_R3_SIZE                          1
#define REG_EXI_GPIO3_DAT_R3_MASK                          0x0008

#define REG_EXI_GPIO3_DAT_R2_SHIFT                         2
#define REG_EXI_GPIO3_DAT_R2_SIZE                          1
#define REG_EXI_GPIO3_DAT_R2_MASK                          0x0004

#define REG_EXI_GPIO3_DAT_R1_SHIFT                         1
#define REG_EXI_GPIO3_DAT_R1_SIZE                          1
#define REG_EXI_GPIO3_DAT_R1_MASK                          0x0002

#define REG_EXI_GPIO3_DAT_R0_SHIFT                         0
#define REG_EXI_GPIO3_DAT_R0_SIZE                          1
#define REG_EXI_GPIO3_DAT_R0_MASK                          0x0001

#ifndef SDK_ASM
#define REG_EXI_GPIO3_DAT_FIELD( lcd_rst_teg2, ctr_mcu, rmc, pwm_sel_teg2, wl_off_teg2, mic_sel_teg2, tp_sel_teg2, wl_rst_teg2, sp_sel, r11, r10, r9, r8, r7, r6, r5, r4, r3, r2, r1, r0 ) \
    (u16)( \
    ((u32)(lcd_rst_teg2) << REG_EXI_GPIO3_DAT_LCD_RST_TEG2_SHIFT) | \
    ((u32)(ctr_mcu) << REG_EXI_GPIO3_DAT_CTR_MCU_SHIFT) | \
    ((u32)(rmc) << REG_EXI_GPIO3_DAT_RMC_SHIFT) | \
    ((u32)(pwm_sel_teg2) << REG_EXI_GPIO3_DAT_PWM_SEL_TEG2_SHIFT) | \
    ((u32)(wl_off_teg2) << REG_EXI_GPIO3_DAT_WL_OFF_TEG2_SHIFT) | \
    ((u32)(mic_sel_teg2) << REG_EXI_GPIO3_DAT_MIC_SEL_TEG2_SHIFT) | \
    ((u32)(tp_sel_teg2) << REG_EXI_GPIO3_DAT_TP_SEL_TEG2_SHIFT) | \
    ((u32)(wl_rst_teg2) << REG_EXI_GPIO3_DAT_WL_RST_TEG2_SHIFT) | \
    ((u32)(sp_sel) << REG_EXI_GPIO3_DAT_SP_SEL_SHIFT) | \
    ((u32)(r11) << REG_EXI_GPIO3_DAT_R11_SHIFT) | \
    ((u32)(r10) << REG_EXI_GPIO3_DAT_R10_SHIFT) | \
    ((u32)(r9) << REG_EXI_GPIO3_DAT_R9_SHIFT) | \
    ((u32)(r8) << REG_EXI_GPIO3_DAT_R8_SHIFT) | \
    ((u32)(r7) << REG_EXI_GPIO3_DAT_R7_SHIFT) | \
    ((u32)(r6) << REG_EXI_GPIO3_DAT_R6_SHIFT) | \
    ((u32)(r5) << REG_EXI_GPIO3_DAT_R5_SHIFT) | \
    ((u32)(r4) << REG_EXI_GPIO3_DAT_R4_SHIFT) | \
    ((u32)(r3) << REG_EXI_GPIO3_DAT_R3_SHIFT) | \
    ((u32)(r2) << REG_EXI_GPIO3_DAT_R2_SHIFT) | \
    ((u32)(r1) << REG_EXI_GPIO3_DAT_R1_SHIFT) | \
    ((u32)(r0) << REG_EXI_GPIO3_DAT_R0_SHIFT))
#endif


/* GPIO3_DIR */

#define REG_EXI_GPIO3_DIR_LCD_RST_TEG2_SHIFT               10
#define REG_EXI_GPIO3_DIR_LCD_RST_TEG2_SIZE                1
#define REG_EXI_GPIO3_DIR_LCD_RST_TEG2_MASK                0x0400

#define REG_EXI_GPIO3_DIR_CTR_MCU_SHIFT                    9
#define REG_EXI_GPIO3_DIR_CTR_MCU_SIZE                     1
#define REG_EXI_GPIO3_DIR_CTR_MCU_MASK                     0x0200

#define REG_EXI_GPIO3_DIR_RMC_SHIFT                        8
#define REG_EXI_GPIO3_DIR_RMC_SIZE                         1
#define REG_EXI_GPIO3_DIR_RMC_MASK                         0x0100

#define REG_EXI_GPIO3_DIR_PWM_SEL_TEG2_SHIFT               7
#define REG_EXI_GPIO3_DIR_PWM_SEL_TEG2_SIZE                1
#define REG_EXI_GPIO3_DIR_PWM_SEL_TEG2_MASK                0x0080

#define REG_EXI_GPIO3_DIR_WL_OFF_TEG2_SHIFT                6
#define REG_EXI_GPIO3_DIR_WL_OFF_TEG2_SIZE                 1
#define REG_EXI_GPIO3_DIR_WL_OFF_TEG2_MASK                 0x0040

#define REG_EXI_GPIO3_DIR_MIC_SEL_TEG2_SHIFT               5
#define REG_EXI_GPIO3_DIR_MIC_SEL_TEG2_SIZE                1
#define REG_EXI_GPIO3_DIR_MIC_SEL_TEG2_MASK                0x0020

#define REG_EXI_GPIO3_DIR_TP_SEL_TEG2_SHIFT                4
#define REG_EXI_GPIO3_DIR_TP_SEL_TEG2_SIZE                 1
#define REG_EXI_GPIO3_DIR_TP_SEL_TEG2_MASK                 0x0010

#define REG_EXI_GPIO3_DIR_WL_RST_TEG2_SHIFT                1
#define REG_EXI_GPIO3_DIR_WL_RST_TEG2_SIZE                 1
#define REG_EXI_GPIO3_DIR_WL_RST_TEG2_MASK                 0x0002

#define REG_EXI_GPIO3_DIR_SP_SEL_SHIFT                     0
#define REG_EXI_GPIO3_DIR_SP_SEL_SIZE                      1
#define REG_EXI_GPIO3_DIR_SP_SEL_MASK                      0x0001

#define REG_EXI_GPIO3_DIR_DR11_SHIFT                       11
#define REG_EXI_GPIO3_DIR_DR11_SIZE                        1
#define REG_EXI_GPIO3_DIR_DR11_MASK                        0x0800

#define REG_EXI_GPIO3_DIR_DR10_SHIFT                       10
#define REG_EXI_GPIO3_DIR_DR10_SIZE                        1
#define REG_EXI_GPIO3_DIR_DR10_MASK                        0x0400

#define REG_EXI_GPIO3_DIR_DR9_SHIFT                        9
#define REG_EXI_GPIO3_DIR_DR9_SIZE                         1
#define REG_EXI_GPIO3_DIR_DR9_MASK                         0x0200

#define REG_EXI_GPIO3_DIR_DR8_SHIFT                        8
#define REG_EXI_GPIO3_DIR_DR8_SIZE                         1
#define REG_EXI_GPIO3_DIR_DR8_MASK                         0x0100

#define REG_EXI_GPIO3_DIR_DR7_SHIFT                        7
#define REG_EXI_GPIO3_DIR_DR7_SIZE                         1
#define REG_EXI_GPIO3_DIR_DR7_MASK                         0x0080

#define REG_EXI_GPIO3_DIR_DR6_SHIFT                        6
#define REG_EXI_GPIO3_DIR_DR6_SIZE                         1
#define REG_EXI_GPIO3_DIR_DR6_MASK                         0x0040

#define REG_EXI_GPIO3_DIR_DR5_SHIFT                        5
#define REG_EXI_GPIO3_DIR_DR5_SIZE                         1
#define REG_EXI_GPIO3_DIR_DR5_MASK                         0x0020

#define REG_EXI_GPIO3_DIR_DR4_SHIFT                        4
#define REG_EXI_GPIO3_DIR_DR4_SIZE                         1
#define REG_EXI_GPIO3_DIR_DR4_MASK                         0x0010

#define REG_EXI_GPIO3_DIR_DR3_SHIFT                        3
#define REG_EXI_GPIO3_DIR_DR3_SIZE                         1
#define REG_EXI_GPIO3_DIR_DR3_MASK                         0x0008

#define REG_EXI_GPIO3_DIR_DR2_SHIFT                        2
#define REG_EXI_GPIO3_DIR_DR2_SIZE                         1
#define REG_EXI_GPIO3_DIR_DR2_MASK                         0x0004

#define REG_EXI_GPIO3_DIR_DR1_SHIFT                        1
#define REG_EXI_GPIO3_DIR_DR1_SIZE                         1
#define REG_EXI_GPIO3_DIR_DR1_MASK                         0x0002

#define REG_EXI_GPIO3_DIR_DR0_SHIFT                        0
#define REG_EXI_GPIO3_DIR_DR0_SIZE                         1
#define REG_EXI_GPIO3_DIR_DR0_MASK                         0x0001

#ifndef SDK_ASM
#define REG_EXI_GPIO3_DIR_FIELD( lcd_rst_teg2, ctr_mcu, rmc, pwm_sel_teg2, wl_off_teg2, mic_sel_teg2, tp_sel_teg2, wl_rst_teg2, sp_sel, dr11, dr10, dr9, dr8, dr7, dr6, dr5, dr4, dr3, dr2, dr1, dr0 ) \
    (u16)( \
    ((u32)(lcd_rst_teg2) << REG_EXI_GPIO3_DIR_LCD_RST_TEG2_SHIFT) | \
    ((u32)(ctr_mcu) << REG_EXI_GPIO3_DIR_CTR_MCU_SHIFT) | \
    ((u32)(rmc) << REG_EXI_GPIO3_DIR_RMC_SHIFT) | \
    ((u32)(pwm_sel_teg2) << REG_EXI_GPIO3_DIR_PWM_SEL_TEG2_SHIFT) | \
    ((u32)(wl_off_teg2) << REG_EXI_GPIO3_DIR_WL_OFF_TEG2_SHIFT) | \
    ((u32)(mic_sel_teg2) << REG_EXI_GPIO3_DIR_MIC_SEL_TEG2_SHIFT) | \
    ((u32)(tp_sel_teg2) << REG_EXI_GPIO3_DIR_TP_SEL_TEG2_SHIFT) | \
    ((u32)(wl_rst_teg2) << REG_EXI_GPIO3_DIR_WL_RST_TEG2_SHIFT) | \
    ((u32)(sp_sel) << REG_EXI_GPIO3_DIR_SP_SEL_SHIFT) | \
    ((u32)(dr11) << REG_EXI_GPIO3_DIR_DR11_SHIFT) | \
    ((u32)(dr10) << REG_EXI_GPIO3_DIR_DR10_SHIFT) | \
    ((u32)(dr9) << REG_EXI_GPIO3_DIR_DR9_SHIFT) | \
    ((u32)(dr8) << REG_EXI_GPIO3_DIR_DR8_SHIFT) | \
    ((u32)(dr7) << REG_EXI_GPIO3_DIR_DR7_SHIFT) | \
    ((u32)(dr6) << REG_EXI_GPIO3_DIR_DR6_SHIFT) | \
    ((u32)(dr5) << REG_EXI_GPIO3_DIR_DR5_SHIFT) | \
    ((u32)(dr4) << REG_EXI_GPIO3_DIR_DR4_SHIFT) | \
    ((u32)(dr3) << REG_EXI_GPIO3_DIR_DR3_SHIFT) | \
    ((u32)(dr2) << REG_EXI_GPIO3_DIR_DR2_SHIFT) | \
    ((u32)(dr1) << REG_EXI_GPIO3_DIR_DR1_SHIFT) | \
    ((u32)(dr0) << REG_EXI_GPIO3_DIR_DR0_SHIFT))
#endif


/* GPIO3_CNT2 */

#define REG_EXI_GPIO3_CNT2_IE11_SHIFT                      27
#define REG_EXI_GPIO3_CNT2_IE11_SIZE                       1
#define REG_EXI_GPIO3_CNT2_IE11_MASK                       0x08000000

#define REG_EXI_GPIO3_CNT2_IE10_SHIFT                      26
#define REG_EXI_GPIO3_CNT2_IE10_SIZE                       1
#define REG_EXI_GPIO3_CNT2_IE10_MASK                       0x04000000

#define REG_EXI_GPIO3_CNT2_IE9_SHIFT                       25
#define REG_EXI_GPIO3_CNT2_IE9_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IE9_MASK                        0x02000000

#define REG_EXI_GPIO3_CNT2_IE8_SHIFT                       24
#define REG_EXI_GPIO3_CNT2_IE8_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IE8_MASK                        0x01000000

#define REG_EXI_GPIO3_CNT2_IE7_SHIFT                       23
#define REG_EXI_GPIO3_CNT2_IE7_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IE7_MASK                        0x00800000

#define REG_EXI_GPIO3_CNT2_IE6_SHIFT                       22
#define REG_EXI_GPIO3_CNT2_IE6_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IE6_MASK                        0x00400000

#define REG_EXI_GPIO3_CNT2_IE5_SHIFT                       21
#define REG_EXI_GPIO3_CNT2_IE5_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IE5_MASK                        0x00200000

#define REG_EXI_GPIO3_CNT2_IE4_SHIFT                       20
#define REG_EXI_GPIO3_CNT2_IE4_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IE4_MASK                        0x00100000

#define REG_EXI_GPIO3_CNT2_IE3_SHIFT                       19
#define REG_EXI_GPIO3_CNT2_IE3_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IE3_MASK                        0x00080000

#define REG_EXI_GPIO3_CNT2_IE2_SHIFT                       18
#define REG_EXI_GPIO3_CNT2_IE2_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IE2_MASK                        0x00040000

#define REG_EXI_GPIO3_CNT2_IE1_SHIFT                       17
#define REG_EXI_GPIO3_CNT2_IE1_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IE1_MASK                        0x00020000

#define REG_EXI_GPIO3_CNT2_IE0_SHIFT                       16
#define REG_EXI_GPIO3_CNT2_IE0_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IE0_MASK                        0x00010000

#define REG_EXI_GPIO3_CNT2_IM11_SHIFT                      11
#define REG_EXI_GPIO3_CNT2_IM11_SIZE                       1
#define REG_EXI_GPIO3_CNT2_IM11_MASK                       0x00000800

#define REG_EXI_GPIO3_CNT2_IM10_SHIFT                      10
#define REG_EXI_GPIO3_CNT2_IM10_SIZE                       1
#define REG_EXI_GPIO3_CNT2_IM10_MASK                       0x00000400

#define REG_EXI_GPIO3_CNT2_IM9_SHIFT                       9
#define REG_EXI_GPIO3_CNT2_IM9_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IM9_MASK                        0x00000200

#define REG_EXI_GPIO3_CNT2_IM8_SHIFT                       8
#define REG_EXI_GPIO3_CNT2_IM8_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IM8_MASK                        0x00000100

#define REG_EXI_GPIO3_CNT2_IM7_SHIFT                       7
#define REG_EXI_GPIO3_CNT2_IM7_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IM7_MASK                        0x00000080

#define REG_EXI_GPIO3_CNT2_IM6_SHIFT                       6
#define REG_EXI_GPIO3_CNT2_IM6_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IM6_MASK                        0x00000040

#define REG_EXI_GPIO3_CNT2_IM5_SHIFT                       5
#define REG_EXI_GPIO3_CNT2_IM5_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IM5_MASK                        0x00000020

#define REG_EXI_GPIO3_CNT2_IM4_SHIFT                       4
#define REG_EXI_GPIO3_CNT2_IM4_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IM4_MASK                        0x00000010

#define REG_EXI_GPIO3_CNT2_IM3_SHIFT                       3
#define REG_EXI_GPIO3_CNT2_IM3_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IM3_MASK                        0x00000008

#define REG_EXI_GPIO3_CNT2_IM2_SHIFT                       2
#define REG_EXI_GPIO3_CNT2_IM2_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IM2_MASK                        0x00000004

#define REG_EXI_GPIO3_CNT2_IM1_SHIFT                       1
#define REG_EXI_GPIO3_CNT2_IM1_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IM1_MASK                        0x00000002

#define REG_EXI_GPIO3_CNT2_IM0_SHIFT                       0
#define REG_EXI_GPIO3_CNT2_IM0_SIZE                        1
#define REG_EXI_GPIO3_CNT2_IM0_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_EXI_GPIO3_CNT2_FIELD( ie11, ie10, ie9, ie8, ie7, ie6, ie5, ie4, ie3, ie2, ie1, ie0, im11, im10, im9, im8, im7, im6, im5, im4, im3, im2, im1, im0 ) \
    (u32)( \
    ((u32)(ie11) << REG_EXI_GPIO3_CNT2_IE11_SHIFT) | \
    ((u32)(ie10) << REG_EXI_GPIO3_CNT2_IE10_SHIFT) | \
    ((u32)(ie9) << REG_EXI_GPIO3_CNT2_IE9_SHIFT) | \
    ((u32)(ie8) << REG_EXI_GPIO3_CNT2_IE8_SHIFT) | \
    ((u32)(ie7) << REG_EXI_GPIO3_CNT2_IE7_SHIFT) | \
    ((u32)(ie6) << REG_EXI_GPIO3_CNT2_IE6_SHIFT) | \
    ((u32)(ie5) << REG_EXI_GPIO3_CNT2_IE5_SHIFT) | \
    ((u32)(ie4) << REG_EXI_GPIO3_CNT2_IE4_SHIFT) | \
    ((u32)(ie3) << REG_EXI_GPIO3_CNT2_IE3_SHIFT) | \
    ((u32)(ie2) << REG_EXI_GPIO3_CNT2_IE2_SHIFT) | \
    ((u32)(ie1) << REG_EXI_GPIO3_CNT2_IE1_SHIFT) | \
    ((u32)(ie0) << REG_EXI_GPIO3_CNT2_IE0_SHIFT) | \
    ((u32)(im11) << REG_EXI_GPIO3_CNT2_IM11_SHIFT) | \
    ((u32)(im10) << REG_EXI_GPIO3_CNT2_IM10_SHIFT) | \
    ((u32)(im9) << REG_EXI_GPIO3_CNT2_IM9_SHIFT) | \
    ((u32)(im8) << REG_EXI_GPIO3_CNT2_IM8_SHIFT) | \
    ((u32)(im7) << REG_EXI_GPIO3_CNT2_IM7_SHIFT) | \
    ((u32)(im6) << REG_EXI_GPIO3_CNT2_IM6_SHIFT) | \
    ((u32)(im5) << REG_EXI_GPIO3_CNT2_IM5_SHIFT) | \
    ((u32)(im4) << REG_EXI_GPIO3_CNT2_IM4_SHIFT) | \
    ((u32)(im3) << REG_EXI_GPIO3_CNT2_IM3_SHIFT) | \
    ((u32)(im2) << REG_EXI_GPIO3_CNT2_IM2_SHIFT) | \
    ((u32)(im1) << REG_EXI_GPIO3_CNT2_IM1_SHIFT) | \
    ((u32)(im0) << REG_EXI_GPIO3_CNT2_IM0_SHIFT))
#endif


/* GPIO3_IM */

#define REG_EXI_GPIO3_IM_LCD_RST_TEG2_SHIFT                10
#define REG_EXI_GPIO3_IM_LCD_RST_TEG2_SIZE                 1
#define REG_EXI_GPIO3_IM_LCD_RST_TEG2_MASK                 0x0400

#define REG_EXI_GPIO3_IM_CTR_MCU_SHIFT                     9
#define REG_EXI_GPIO3_IM_CTR_MCU_SIZE                      1
#define REG_EXI_GPIO3_IM_CTR_MCU_MASK                      0x0200

#define REG_EXI_GPIO3_IM_RMC_SHIFT                         8
#define REG_EXI_GPIO3_IM_RMC_SIZE                          1
#define REG_EXI_GPIO3_IM_RMC_MASK                          0x0100

#define REG_EXI_GPIO3_IM_PWM_SEL_TEG2_SHIFT                7
#define REG_EXI_GPIO3_IM_PWM_SEL_TEG2_SIZE                 1
#define REG_EXI_GPIO3_IM_PWM_SEL_TEG2_MASK                 0x0080

#define REG_EXI_GPIO3_IM_WL_OFF_TEG2_SHIFT                 6
#define REG_EXI_GPIO3_IM_WL_OFF_TEG2_SIZE                  1
#define REG_EXI_GPIO3_IM_WL_OFF_TEG2_MASK                  0x0040

#define REG_EXI_GPIO3_IM_MIC_SEL_TEG2_SHIFT                5
#define REG_EXI_GPIO3_IM_MIC_SEL_TEG2_SIZE                 1
#define REG_EXI_GPIO3_IM_MIC_SEL_TEG2_MASK                 0x0020

#define REG_EXI_GPIO3_IM_TP_SEL_TEG2_SHIFT                 4
#define REG_EXI_GPIO3_IM_TP_SEL_TEG2_SIZE                  1
#define REG_EXI_GPIO3_IM_TP_SEL_TEG2_MASK                  0x0010

#define REG_EXI_GPIO3_IM_WL_RST_TEG2_SHIFT                 1
#define REG_EXI_GPIO3_IM_WL_RST_TEG2_SIZE                  1
#define REG_EXI_GPIO3_IM_WL_RST_TEG2_MASK                  0x0002

#define REG_EXI_GPIO3_IM_SP_SEL_SHIFT                      0
#define REG_EXI_GPIO3_IM_SP_SEL_SIZE                       1
#define REG_EXI_GPIO3_IM_SP_SEL_MASK                       0x0001

#define REG_EXI_GPIO3_IM_IM11_SHIFT                        11
#define REG_EXI_GPIO3_IM_IM11_SIZE                         1
#define REG_EXI_GPIO3_IM_IM11_MASK                         0x0800

#define REG_EXI_GPIO3_IM_IM10_SHIFT                        10
#define REG_EXI_GPIO3_IM_IM10_SIZE                         1
#define REG_EXI_GPIO3_IM_IM10_MASK                         0x0400

#define REG_EXI_GPIO3_IM_IM9_SHIFT                         9
#define REG_EXI_GPIO3_IM_IM9_SIZE                          1
#define REG_EXI_GPIO3_IM_IM9_MASK                          0x0200

#define REG_EXI_GPIO3_IM_IM8_SHIFT                         8
#define REG_EXI_GPIO3_IM_IM8_SIZE                          1
#define REG_EXI_GPIO3_IM_IM8_MASK                          0x0100

#define REG_EXI_GPIO3_IM_IM7_SHIFT                         7
#define REG_EXI_GPIO3_IM_IM7_SIZE                          1
#define REG_EXI_GPIO3_IM_IM7_MASK                          0x0080

#define REG_EXI_GPIO3_IM_IM6_SHIFT                         6
#define REG_EXI_GPIO3_IM_IM6_SIZE                          1
#define REG_EXI_GPIO3_IM_IM6_MASK                          0x0040

#define REG_EXI_GPIO3_IM_IM5_SHIFT                         5
#define REG_EXI_GPIO3_IM_IM5_SIZE                          1
#define REG_EXI_GPIO3_IM_IM5_MASK                          0x0020

#define REG_EXI_GPIO3_IM_IM4_SHIFT                         4
#define REG_EXI_GPIO3_IM_IM4_SIZE                          1
#define REG_EXI_GPIO3_IM_IM4_MASK                          0x0010

#define REG_EXI_GPIO3_IM_IM3_SHIFT                         3
#define REG_EXI_GPIO3_IM_IM3_SIZE                          1
#define REG_EXI_GPIO3_IM_IM3_MASK                          0x0008

#define REG_EXI_GPIO3_IM_IM2_SHIFT                         2
#define REG_EXI_GPIO3_IM_IM2_SIZE                          1
#define REG_EXI_GPIO3_IM_IM2_MASK                          0x0004

#define REG_EXI_GPIO3_IM_IM1_SHIFT                         1
#define REG_EXI_GPIO3_IM_IM1_SIZE                          1
#define REG_EXI_GPIO3_IM_IM1_MASK                          0x0002

#define REG_EXI_GPIO3_IM_IM0_SHIFT                         0
#define REG_EXI_GPIO3_IM_IM0_SIZE                          1
#define REG_EXI_GPIO3_IM_IM0_MASK                          0x0001

#ifndef SDK_ASM
#define REG_EXI_GPIO3_IM_FIELD( lcd_rst_teg2, ctr_mcu, rmc, pwm_sel_teg2, wl_off_teg2, mic_sel_teg2, tp_sel_teg2, wl_rst_teg2, sp_sel, im11, im10, im9, im8, im7, im6, im5, im4, im3, im2, im1, im0 ) \
    (u16)( \
    ((u32)(lcd_rst_teg2) << REG_EXI_GPIO3_IM_LCD_RST_TEG2_SHIFT) | \
    ((u32)(ctr_mcu) << REG_EXI_GPIO3_IM_CTR_MCU_SHIFT) | \
    ((u32)(rmc) << REG_EXI_GPIO3_IM_RMC_SHIFT) | \
    ((u32)(pwm_sel_teg2) << REG_EXI_GPIO3_IM_PWM_SEL_TEG2_SHIFT) | \
    ((u32)(wl_off_teg2) << REG_EXI_GPIO3_IM_WL_OFF_TEG2_SHIFT) | \
    ((u32)(mic_sel_teg2) << REG_EXI_GPIO3_IM_MIC_SEL_TEG2_SHIFT) | \
    ((u32)(tp_sel_teg2) << REG_EXI_GPIO3_IM_TP_SEL_TEG2_SHIFT) | \
    ((u32)(wl_rst_teg2) << REG_EXI_GPIO3_IM_WL_RST_TEG2_SHIFT) | \
    ((u32)(sp_sel) << REG_EXI_GPIO3_IM_SP_SEL_SHIFT) | \
    ((u32)(im11) << REG_EXI_GPIO3_IM_IM11_SHIFT) | \
    ((u32)(im10) << REG_EXI_GPIO3_IM_IM10_SHIFT) | \
    ((u32)(im9) << REG_EXI_GPIO3_IM_IM9_SHIFT) | \
    ((u32)(im8) << REG_EXI_GPIO3_IM_IM8_SHIFT) | \
    ((u32)(im7) << REG_EXI_GPIO3_IM_IM7_SHIFT) | \
    ((u32)(im6) << REG_EXI_GPIO3_IM_IM6_SHIFT) | \
    ((u32)(im5) << REG_EXI_GPIO3_IM_IM5_SHIFT) | \
    ((u32)(im4) << REG_EXI_GPIO3_IM_IM4_SHIFT) | \
    ((u32)(im3) << REG_EXI_GPIO3_IM_IM3_SHIFT) | \
    ((u32)(im2) << REG_EXI_GPIO3_IM_IM2_SHIFT) | \
    ((u32)(im1) << REG_EXI_GPIO3_IM_IM1_SHIFT) | \
    ((u32)(im0) << REG_EXI_GPIO3_IM_IM0_SHIFT))
#endif


/* GPIO3_IE */

#define REG_EXI_GPIO3_IE_LCD_RST_TEG2_SHIFT                10
#define REG_EXI_GPIO3_IE_LCD_RST_TEG2_SIZE                 1
#define REG_EXI_GPIO3_IE_LCD_RST_TEG2_MASK                 0x0400

#define REG_EXI_GPIO3_IE_CTR_MCU_SHIFT                     9
#define REG_EXI_GPIO3_IE_CTR_MCU_SIZE                      1
#define REG_EXI_GPIO3_IE_CTR_MCU_MASK                      0x0200

#define REG_EXI_GPIO3_IE_RMC_SHIFT                         8
#define REG_EXI_GPIO3_IE_RMC_SIZE                          1
#define REG_EXI_GPIO3_IE_RMC_MASK                          0x0100

#define REG_EXI_GPIO3_IE_PWM_SEL_TEG2_SHIFT                7
#define REG_EXI_GPIO3_IE_PWM_SEL_TEG2_SIZE                 1
#define REG_EXI_GPIO3_IE_PWM_SEL_TEG2_MASK                 0x0080

#define REG_EXI_GPIO3_IE_WL_OFF_TEG2_SHIFT                 6
#define REG_EXI_GPIO3_IE_WL_OFF_TEG2_SIZE                  1
#define REG_EXI_GPIO3_IE_WL_OFF_TEG2_MASK                  0x0040

#define REG_EXI_GPIO3_IE_MIC_SEL_TEG2_SHIFT                5
#define REG_EXI_GPIO3_IE_MIC_SEL_TEG2_SIZE                 1
#define REG_EXI_GPIO3_IE_MIC_SEL_TEG2_MASK                 0x0020

#define REG_EXI_GPIO3_IE_TP_SEL_TEG2_SHIFT                 4
#define REG_EXI_GPIO3_IE_TP_SEL_TEG2_SIZE                  1
#define REG_EXI_GPIO3_IE_TP_SEL_TEG2_MASK                  0x0010

#define REG_EXI_GPIO3_IE_WL_RST_TEG2_SHIFT                 1
#define REG_EXI_GPIO3_IE_WL_RST_TEG2_SIZE                  1
#define REG_EXI_GPIO3_IE_WL_RST_TEG2_MASK                  0x0002

#define REG_EXI_GPIO3_IE_SP_SEL_SHIFT                      0
#define REG_EXI_GPIO3_IE_SP_SEL_SIZE                       1
#define REG_EXI_GPIO3_IE_SP_SEL_MASK                       0x0001

#define REG_EXI_GPIO3_IE_IE11_SHIFT                        11
#define REG_EXI_GPIO3_IE_IE11_SIZE                         1
#define REG_EXI_GPIO3_IE_IE11_MASK                         0x0800

#define REG_EXI_GPIO3_IE_IE10_SHIFT                        10
#define REG_EXI_GPIO3_IE_IE10_SIZE                         1
#define REG_EXI_GPIO3_IE_IE10_MASK                         0x0400

#define REG_EXI_GPIO3_IE_IE9_SHIFT                         9
#define REG_EXI_GPIO3_IE_IE9_SIZE                          1
#define REG_EXI_GPIO3_IE_IE9_MASK                          0x0200

#define REG_EXI_GPIO3_IE_IE8_SHIFT                         8
#define REG_EXI_GPIO3_IE_IE8_SIZE                          1
#define REG_EXI_GPIO3_IE_IE8_MASK                          0x0100

#define REG_EXI_GPIO3_IE_IE7_SHIFT                         7
#define REG_EXI_GPIO3_IE_IE7_SIZE                          1
#define REG_EXI_GPIO3_IE_IE7_MASK                          0x0080

#define REG_EXI_GPIO3_IE_IE6_SHIFT                         6
#define REG_EXI_GPIO3_IE_IE6_SIZE                          1
#define REG_EXI_GPIO3_IE_IE6_MASK                          0x0040

#define REG_EXI_GPIO3_IE_IE5_SHIFT                         5
#define REG_EXI_GPIO3_IE_IE5_SIZE                          1
#define REG_EXI_GPIO3_IE_IE5_MASK                          0x0020

#define REG_EXI_GPIO3_IE_IE4_SHIFT                         4
#define REG_EXI_GPIO3_IE_IE4_SIZE                          1
#define REG_EXI_GPIO3_IE_IE4_MASK                          0x0010

#define REG_EXI_GPIO3_IE_IE3_SHIFT                         3
#define REG_EXI_GPIO3_IE_IE3_SIZE                          1
#define REG_EXI_GPIO3_IE_IE3_MASK                          0x0008

#define REG_EXI_GPIO3_IE_IE2_SHIFT                         2
#define REG_EXI_GPIO3_IE_IE2_SIZE                          1
#define REG_EXI_GPIO3_IE_IE2_MASK                          0x0004

#define REG_EXI_GPIO3_IE_IE1_SHIFT                         1
#define REG_EXI_GPIO3_IE_IE1_SIZE                          1
#define REG_EXI_GPIO3_IE_IE1_MASK                          0x0002

#define REG_EXI_GPIO3_IE_IE0_SHIFT                         0
#define REG_EXI_GPIO3_IE_IE0_SIZE                          1
#define REG_EXI_GPIO3_IE_IE0_MASK                          0x0001

#ifndef SDK_ASM
#define REG_EXI_GPIO3_IE_FIELD( lcd_rst_teg2, ctr_mcu, rmc, pwm_sel_teg2, wl_off_teg2, mic_sel_teg2, tp_sel_teg2, wl_rst_teg2, sp_sel, ie11, ie10, ie9, ie8, ie7, ie6, ie5, ie4, ie3, ie2, ie1, ie0 ) \
    (u16)( \
    ((u32)(lcd_rst_teg2) << REG_EXI_GPIO3_IE_LCD_RST_TEG2_SHIFT) | \
    ((u32)(ctr_mcu) << REG_EXI_GPIO3_IE_CTR_MCU_SHIFT) | \
    ((u32)(rmc) << REG_EXI_GPIO3_IE_RMC_SHIFT) | \
    ((u32)(pwm_sel_teg2) << REG_EXI_GPIO3_IE_PWM_SEL_TEG2_SHIFT) | \
    ((u32)(wl_off_teg2) << REG_EXI_GPIO3_IE_WL_OFF_TEG2_SHIFT) | \
    ((u32)(mic_sel_teg2) << REG_EXI_GPIO3_IE_MIC_SEL_TEG2_SHIFT) | \
    ((u32)(tp_sel_teg2) << REG_EXI_GPIO3_IE_TP_SEL_TEG2_SHIFT) | \
    ((u32)(wl_rst_teg2) << REG_EXI_GPIO3_IE_WL_RST_TEG2_SHIFT) | \
    ((u32)(sp_sel) << REG_EXI_GPIO3_IE_SP_SEL_SHIFT) | \
    ((u32)(ie11) << REG_EXI_GPIO3_IE_IE11_SHIFT) | \
    ((u32)(ie10) << REG_EXI_GPIO3_IE_IE10_SHIFT) | \
    ((u32)(ie9) << REG_EXI_GPIO3_IE_IE9_SHIFT) | \
    ((u32)(ie8) << REG_EXI_GPIO3_IE_IE8_SHIFT) | \
    ((u32)(ie7) << REG_EXI_GPIO3_IE_IE7_SHIFT) | \
    ((u32)(ie6) << REG_EXI_GPIO3_IE_IE6_SHIFT) | \
    ((u32)(ie5) << REG_EXI_GPIO3_IE_IE5_SHIFT) | \
    ((u32)(ie4) << REG_EXI_GPIO3_IE_IE4_SHIFT) | \
    ((u32)(ie3) << REG_EXI_GPIO3_IE_IE3_SHIFT) | \
    ((u32)(ie2) << REG_EXI_GPIO3_IE_IE2_SHIFT) | \
    ((u32)(ie1) << REG_EXI_GPIO3_IE_IE1_SHIFT) | \
    ((u32)(ie0) << REG_EXI_GPIO3_IE_IE0_SHIFT))
#endif


/* GPIO3_OCNT */

#define REG_EXI_GPIO3_OCNT_WL_RST_SHIFT                    0
#define REG_EXI_GPIO3_OCNT_WL_RST_SIZE                     1
#define REG_EXI_GPIO3_OCNT_WL_RST_MASK                     0x0001

#ifndef SDK_ASM
#define REG_EXI_GPIO3_OCNT_FIELD( wl_rst ) \
    (u16)( \
    ((u32)(wl_rst) << REG_EXI_GPIO3_OCNT_WL_RST_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TS_ARM9_IOREG_TSPATCH_EXI_H_ */
#endif
