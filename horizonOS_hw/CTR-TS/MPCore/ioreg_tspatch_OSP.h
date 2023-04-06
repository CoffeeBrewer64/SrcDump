/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TS/MPCore/ioreg_tspatch_OSP.h

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
#ifndef NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_OSP_H_
#define NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_OSP_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* SCUP_CNT */

#define REG_SCUP_CNT_OFFSET                                0x00000
#define REG_SCUP_CNT_ADDR                                  (HW_MPCORE_REG + REG_SCUP_CNT_OFFSET)
#define reg_OSP_SCUP_CNT                                   (*( REGType32v *) REG_SCUP_CNT_ADDR)

/* SCUP_CFG */

#define REG_SCUP_CFG_OFFSET                                0x00004
#define REG_SCUP_CFG_ADDR                                  (HW_MPCORE_REG + REG_SCUP_CFG_OFFSET)
#define reg_OSP_SCUP_CFG                                   (*(const REGType32v *) REG_SCUP_CFG_ADDR)

/* SCUP_STAT */

#define REG_SCUP_STAT_OFFSET                               0x00008
#define REG_SCUP_STAT_ADDR                                 (HW_MPCORE_REG + REG_SCUP_STAT_OFFSET)
#define reg_OSP_SCUP_STAT                                  (*( REGType32v *) REG_SCUP_STAT_ADDR)

/* SCUP_INVLD_WAY */

#define REG_SCUP_INVLD_WAY_OFFSET                          0x0000c
#define REG_SCUP_INVLD_WAY_ADDR                            (HW_MPCORE_REG + REG_SCUP_INVLD_WAY_OFFSET)
#define reg_OSP_SCUP_INVLD_WAY                             (*( REGType32v *) REG_SCUP_INVLD_WAY_ADDR)

/* SCUP_PMON_CNT */

#define REG_SCUP_PMON_CNT_OFFSET                           0x00010
#define REG_SCUP_PMON_CNT_ADDR                             (HW_MPCORE_REG + REG_SCUP_PMON_CNT_OFFSET)
#define reg_OSP_SCUP_PMON_CNT                              (*( REGType32v *) REG_SCUP_PMON_CNT_ADDR)

/* SCUP_PMON_EVENT0 */

#define REG_SCUP_PMON_EVENT0_OFFSET                        0x00014
#define REG_SCUP_PMON_EVENT0_ADDR                          (HW_MPCORE_REG + REG_SCUP_PMON_EVENT0_OFFSET)
#define reg_OSP_SCUP_PMON_EVENT0                           (*( REGType32v *) REG_SCUP_PMON_EVENT0_ADDR)

/* SCUP_PMON_EVENT1 */

#define REG_SCUP_PMON_EVENT1_OFFSET                        0x00018
#define REG_SCUP_PMON_EVENT1_ADDR                          (HW_MPCORE_REG + REG_SCUP_PMON_EVENT1_OFFSET)
#define reg_OSP_SCUP_PMON_EVENT1                           (*( REGType32v *) REG_SCUP_PMON_EVENT1_ADDR)

/* SCUP_PMON_COUNT0 */

#define REG_SCUP_PMON_COUNT0_OFFSET                        0x0001c
#define REG_SCUP_PMON_COUNT0_ADDR                          (HW_MPCORE_REG + REG_SCUP_PMON_COUNT0_OFFSET)
#define reg_OSP_SCUP_PMON_COUNT0                           (*( REGType32v *) REG_SCUP_PMON_COUNT0_ADDR)

/* SCUP_PMON_COUNT1 */

#define REG_SCUP_PMON_COUNT1_OFFSET                        0x00020
#define REG_SCUP_PMON_COUNT1_ADDR                          (HW_MPCORE_REG + REG_SCUP_PMON_COUNT1_OFFSET)
#define reg_OSP_SCUP_PMON_COUNT1                           (*( REGType32v *) REG_SCUP_PMON_COUNT1_ADDR)

/* CPUIP_CNT */

#define REG_CPUIP_CNT_OFFSET                               0x0100
#define REG_CPUIP_CNT_ADDR                                 (HW_MPCORE_REG + REG_CPUIP_CNT_OFFSET)
#define reg_OSP_CPUIP_CNT                                  (*( REGType32v *) REG_CPUIP_CNT_ADDR)

/* CPUIP_PRIO */

#define REG_CPUIP_PRIO_OFFSET                              0x0104
#define REG_CPUIP_PRIO_ADDR                                (HW_MPCORE_REG + REG_CPUIP_PRIO_OFFSET)
#define reg_OSP_CPUIP_PRIO                                 (*( REGType32v *) REG_CPUIP_PRIO_ADDR)

/* CPUIP_BP */

#define REG_CPUIP_BP_OFFSET                                0x0108
#define REG_CPUIP_BP_ADDR                                  (HW_MPCORE_REG + REG_CPUIP_BP_OFFSET)
#define reg_OSP_CPUIP_BP                                   (*( REGType32v *) REG_CPUIP_BP_ADDR)

/* CPUIP_ACK */

#define REG_CPUIP_ACK_OFFSET                               0x010c
#define REG_CPUIP_ACK_ADDR                                 (HW_MPCORE_REG + REG_CPUIP_ACK_OFFSET)
#define reg_OSP_CPUIP_ACK                                  (*( REGType32v *) REG_CPUIP_ACK_ADDR)

/* CPUIP_EOI */

#define REG_CPUIP_EOI_OFFSET                               0x0110
#define REG_CPUIP_EOI_ADDR                                 (HW_MPCORE_REG + REG_CPUIP_EOI_OFFSET)
#define reg_OSP_CPUIP_EOI                                  (*( REGType32v *) REG_CPUIP_EOI_ADDR)

/* CPUIP_RUN_INTR */

#define REG_CPUIP_RUN_INTR_OFFSET                          0x0114
#define REG_CPUIP_RUN_INTR_ADDR                            (HW_MPCORE_REG + REG_CPUIP_RUN_INTR_OFFSET)
#define reg_OSP_CPUIP_RUN_INTR                             (*( REGType32v *) REG_CPUIP_RUN_INTR_ADDR)

/* CPUIP_HI_PND */

#define REG_CPUIP_HI_PND_OFFSET                            0x0118
#define REG_CPUIP_HI_PND_ADDR                              (HW_MPCORE_REG + REG_CPUIP_HI_PND_OFFSET)
#define reg_OSP_CPUIP_HI_PND                               (*( REGType32v *) REG_CPUIP_HI_PND_ADDR)

/* IDRP_CNT */

#define REG_IDRP_CNT_OFFSET                                0x1000
#define REG_IDRP_CNT_ADDR                                  (HW_MPCORE_REG + REG_IDRP_CNT_OFFSET)
#define reg_OSP_IDRP_CNT                                   (*( REGType32v *) REG_IDRP_CNT_ADDR)

/* IDRP_TYPE */

#define REG_IDRP_TYPE_OFFSET                               0x1004
#define REG_IDRP_TYPE_ADDR                                 (HW_MPCORE_REG + REG_IDRP_TYPE_OFFSET)
#define reg_OSP_IDRP_TYPE                                  (*(const REGType32v *) REG_IDRP_TYPE_ADDR)

/* IDRP_SET_IE0 */

#define REG_IDRP_SET_IE0_OFFSET                            0x1100
#define REG_IDRP_SET_IE0_ADDR                              (HW_MPCORE_REG + REG_IDRP_SET_IE0_OFFSET)
#define reg_OSP_IDRP_SET_IE0                               (*( REGType32v *) REG_IDRP_SET_IE0_ADDR)

/* IDRP_SET_IE1 */

#define REG_IDRP_SET_IE1_OFFSET                            0x1104
#define REG_IDRP_SET_IE1_ADDR                              (HW_MPCORE_REG + REG_IDRP_SET_IE1_OFFSET)
#define reg_OSP_IDRP_SET_IE1                               (*( REGType32v *) REG_IDRP_SET_IE1_ADDR)

/* IDRP_SET_IE2 */

#define REG_IDRP_SET_IE2_OFFSET                            0x1108
#define REG_IDRP_SET_IE2_ADDR                              (HW_MPCORE_REG + REG_IDRP_SET_IE2_OFFSET)
#define reg_OSP_IDRP_SET_IE2                               (*( REGType32v *) REG_IDRP_SET_IE2_ADDR)

/* IDRP_SET_IE3 */

#define REG_IDRP_SET_IE3_OFFSET                            0x110c
#define REG_IDRP_SET_IE3_ADDR                              (HW_MPCORE_REG + REG_IDRP_SET_IE3_OFFSET)
#define reg_OSP_IDRP_SET_IE3                               (*( REGType32v *) REG_IDRP_SET_IE3_ADDR)

/* IDRP_CLR_IE0 */

#define REG_IDRP_CLR_IE0_OFFSET                            0x1180
#define REG_IDRP_CLR_IE0_ADDR                              (HW_MPCORE_REG + REG_IDRP_CLR_IE0_OFFSET)
#define reg_OSP_IDRP_CLR_IE0                               (*( REGType32v *) REG_IDRP_CLR_IE0_ADDR)

/* IDRP_CLR_IE1 */

#define REG_IDRP_CLR_IE1_OFFSET                            0x1184
#define REG_IDRP_CLR_IE1_ADDR                              (HW_MPCORE_REG + REG_IDRP_CLR_IE1_OFFSET)
#define reg_OSP_IDRP_CLR_IE1                               (*( REGType32v *) REG_IDRP_CLR_IE1_ADDR)

/* IDRP_CLR_IE2 */

#define REG_IDRP_CLR_IE2_OFFSET                            0x1188
#define REG_IDRP_CLR_IE2_ADDR                              (HW_MPCORE_REG + REG_IDRP_CLR_IE2_OFFSET)
#define reg_OSP_IDRP_CLR_IE2                               (*( REGType32v *) REG_IDRP_CLR_IE2_ADDR)

/* IDRP_CLR_IE3 */

#define REG_IDRP_CLR_IE3_OFFSET                            0x118c
#define REG_IDRP_CLR_IE3_ADDR                              (HW_MPCORE_REG + REG_IDRP_CLR_IE3_OFFSET)
#define reg_OSP_IDRP_CLR_IE3                               (*( REGType32v *) REG_IDRP_CLR_IE3_ADDR)

/* IDRP_SET_PND0 */

#define REG_IDRP_SET_PND0_OFFSET                           0x1200
#define REG_IDRP_SET_PND0_ADDR                             (HW_MPCORE_REG + REG_IDRP_SET_PND0_OFFSET)
#define reg_OSP_IDRP_SET_PND0                              (*( REGType32v *) REG_IDRP_SET_PND0_ADDR)

/* IDRP_SET_PND1 */

#define REG_IDRP_SET_PND1_OFFSET                           0x1204
#define REG_IDRP_SET_PND1_ADDR                             (HW_MPCORE_REG + REG_IDRP_SET_PND1_OFFSET)
#define reg_OSP_IDRP_SET_PND1                              (*( REGType32v *) REG_IDRP_SET_PND1_ADDR)

/* IDRP_SET_PND2 */

#define REG_IDRP_SET_PND2_OFFSET                           0x1208
#define REG_IDRP_SET_PND2_ADDR                             (HW_MPCORE_REG + REG_IDRP_SET_PND2_OFFSET)
#define reg_OSP_IDRP_SET_PND2                              (*( REGType32v *) REG_IDRP_SET_PND2_ADDR)

/* IDRP_SET_PND3 */

#define REG_IDRP_SET_PND3_OFFSET                           0x120c
#define REG_IDRP_SET_PND3_ADDR                             (HW_MPCORE_REG + REG_IDRP_SET_PND3_OFFSET)
#define reg_OSP_IDRP_SET_PND3                              (*( REGType32v *) REG_IDRP_SET_PND3_ADDR)

/* IDRP_CLR_PND0 */

#define REG_IDRP_CLR_PND0_OFFSET                           0x1280
#define REG_IDRP_CLR_PND0_ADDR                             (HW_MPCORE_REG + REG_IDRP_CLR_PND0_OFFSET)
#define reg_OSP_IDRP_CLR_PND0                              (*( REGType32v *) REG_IDRP_CLR_PND0_ADDR)

/* IDRP_CLR_PND1 */

#define REG_IDRP_CLR_PND1_OFFSET                           0x1284
#define REG_IDRP_CLR_PND1_ADDR                             (HW_MPCORE_REG + REG_IDRP_CLR_PND1_OFFSET)
#define reg_OSP_IDRP_CLR_PND1                              (*( REGType32v *) REG_IDRP_CLR_PND1_ADDR)

/* IDRP_CLR_PND2 */

#define REG_IDRP_CLR_PND2_OFFSET                           0x1288
#define REG_IDRP_CLR_PND2_ADDR                             (HW_MPCORE_REG + REG_IDRP_CLR_PND2_OFFSET)
#define reg_OSP_IDRP_CLR_PND2                              (*( REGType32v *) REG_IDRP_CLR_PND2_ADDR)

/* IDRP_CLR_PND3 */

#define REG_IDRP_CLR_PND3_OFFSET                           0x128c
#define REG_IDRP_CLR_PND3_ADDR                             (HW_MPCORE_REG + REG_IDRP_CLR_PND3_OFFSET)
#define reg_OSP_IDRP_CLR_PND3                              (*( REGType32v *) REG_IDRP_CLR_PND3_ADDR)

/* IDRP_ACT0 */

#define REG_IDRP_ACT0_OFFSET                               0x1300
#define REG_IDRP_ACT0_ADDR                                 (HW_MPCORE_REG + REG_IDRP_ACT0_OFFSET)
#define reg_OSP_IDRP_ACT0                                  (*( REGType32v *) REG_IDRP_ACT0_ADDR)

/* IDRP_ACT1 */

#define REG_IDRP_ACT1_OFFSET                               0x1304
#define REG_IDRP_ACT1_ADDR                                 (HW_MPCORE_REG + REG_IDRP_ACT1_OFFSET)
#define reg_OSP_IDRP_ACT1                                  (*( REGType32v *) REG_IDRP_ACT1_ADDR)

/* IDRP_ACT2 */

#define REG_IDRP_ACT2_OFFSET                               0x1308
#define REG_IDRP_ACT2_ADDR                                 (HW_MPCORE_REG + REG_IDRP_ACT2_OFFSET)
#define reg_OSP_IDRP_ACT2                                  (*( REGType32v *) REG_IDRP_ACT2_ADDR)

/* IDRP_ACT3 */

#define REG_IDRP_ACT3_OFFSET                               0x130c
#define REG_IDRP_ACT3_ADDR                                 (HW_MPCORE_REG + REG_IDRP_ACT3_OFFSET)
#define reg_OSP_IDRP_ACT3                                  (*( REGType32v *) REG_IDRP_ACT3_ADDR)

/* IDRP_PRIO0 */

#define REG_IDRP_PRIO0_OFFSET                              0x1400
#define REG_IDRP_PRIO0_ADDR                                (HW_MPCORE_REG + REG_IDRP_PRIO0_OFFSET)
#define reg_OSP_IDRP_PRIO0                                 (*( REGType8v *) REG_IDRP_PRIO0_ADDR)

/* IDRP_TGT0 */

#define REG_IDRP_TGT0_OFFSET                               0x1800
#define REG_IDRP_TGT0_ADDR                                 (HW_MPCORE_REG + REG_IDRP_TGT0_OFFSET)
#define reg_OSP_IDRP_TGT0                                  (*( REGType8v *) REG_IDRP_TGT0_ADDR)

/* IDRP_CFG0 */

#define REG_IDRP_CFG0_OFFSET                               0x1c00
#define REG_IDRP_CFG0_ADDR                                 (HW_MPCORE_REG + REG_IDRP_CFG0_OFFSET)
#define reg_OSP_IDRP_CFG0                                  (*( REGType32v *) REG_IDRP_CFG0_ADDR)

/* IDRP_CFG1 */

#define REG_IDRP_CFG1_OFFSET                               0x1c04
#define REG_IDRP_CFG1_ADDR                                 (HW_MPCORE_REG + REG_IDRP_CFG1_OFFSET)
#define reg_OSP_IDRP_CFG1                                  (*( REGType32v *) REG_IDRP_CFG1_ADDR)

/* IDRP_CFG2 */

#define REG_IDRP_CFG2_OFFSET                               0x1c08
#define REG_IDRP_CFG2_ADDR                                 (HW_MPCORE_REG + REG_IDRP_CFG2_OFFSET)
#define reg_OSP_IDRP_CFG2                                  (*( REGType32v *) REG_IDRP_CFG2_ADDR)

/* IDRP_CFG3 */

#define REG_IDRP_CFG3_OFFSET                               0x1c0c
#define REG_IDRP_CFG3_ADDR                                 (HW_MPCORE_REG + REG_IDRP_CFG3_OFFSET)
#define reg_OSP_IDRP_CFG3                                  (*( REGType32v *) REG_IDRP_CFG3_ADDR)

/* IDRP_CFG4 */

#define REG_IDRP_CFG4_OFFSET                               0x1c10
#define REG_IDRP_CFG4_ADDR                                 (HW_MPCORE_REG + REG_IDRP_CFG4_OFFSET)
#define reg_OSP_IDRP_CFG4                                  (*( REGType32v *) REG_IDRP_CFG4_ADDR)

/* IDRP_CFG5 */

#define REG_IDRP_CFG5_OFFSET                               0x1c14
#define REG_IDRP_CFG5_ADDR                                 (HW_MPCORE_REG + REG_IDRP_CFG5_OFFSET)
#define reg_OSP_IDRP_CFG5                                  (*( REGType32v *) REG_IDRP_CFG5_ADDR)

/* IDRP_CFG6 */

#define REG_IDRP_CFG6_OFFSET                               0x1c18
#define REG_IDRP_CFG6_ADDR                                 (HW_MPCORE_REG + REG_IDRP_CFG6_OFFSET)
#define reg_OSP_IDRP_CFG6                                  (*( REGType32v *) REG_IDRP_CFG6_ADDR)

/* IDRP_CFG7 */

#define REG_IDRP_CFG7_OFFSET                               0x1c1c
#define REG_IDRP_CFG7_ADDR                                 (HW_MPCORE_REG + REG_IDRP_CFG7_OFFSET)
#define reg_OSP_IDRP_CFG7                                  (*( REGType32v *) REG_IDRP_CFG7_ADDR)

/* IDRP_SW */

#define REG_IDRP_SW_OFFSET                                 0x1f00
#define REG_IDRP_SW_ADDR                                   (HW_MPCORE_REG + REG_IDRP_SW_OFFSET)
#define reg_OSP_IDRP_SW                                    (*( REGType32v *) REG_IDRP_SW_ADDR)


/*
 * Definitions of Register fields
 */


/* SCUP_CNT */

#define REG_OSP_SCUP_CNT_E_SHIFT                           0
#define REG_OSP_SCUP_CNT_E_SIZE                            1
#define REG_OSP_SCUP_CNT_E_MASK                            0x00000001

#ifndef SDK_ASM
#define REG_OSP_SCUP_CNT_FIELD( e ) \
    (u32)( \
    ((u32)(e) << REG_OSP_SCUP_CNT_E_SHIFT))
#endif


/* SCUP_CFG */

#define REG_OSP_SCUP_CFG_C3_CACHE_SIZE_SHIFT               14
#define REG_OSP_SCUP_CFG_C3_CACHE_SIZE_SIZE                2
#define REG_OSP_SCUP_CFG_C3_CACHE_SIZE_MASK                0x0000c000

#define REG_OSP_SCUP_CFG_C2_CACHE_SIZE_SHIFT               12
#define REG_OSP_SCUP_CFG_C2_CACHE_SIZE_SIZE                2
#define REG_OSP_SCUP_CFG_C2_CACHE_SIZE_MASK                0x00003000

#define REG_OSP_SCUP_CFG_C1_CACHE_SIZE_SHIFT               10
#define REG_OSP_SCUP_CFG_C1_CACHE_SIZE_SIZE                2
#define REG_OSP_SCUP_CFG_C1_CACHE_SIZE_MASK                0x00000c00

#define REG_OSP_SCUP_CFG_C0_CACHE_SIZE_SHIFT               8
#define REG_OSP_SCUP_CFG_C0_CACHE_SIZE_SIZE                2
#define REG_OSP_SCUP_CFG_C0_CACHE_SIZE_MASK                0x00000300

#define REG_OSP_SCUP_CFG_C3_SMP_SHIFT                      7
#define REG_OSP_SCUP_CFG_C3_SMP_SIZE                       1
#define REG_OSP_SCUP_CFG_C3_SMP_MASK                       0x00000080

#define REG_OSP_SCUP_CFG_C2_SMP_SHIFT                      6
#define REG_OSP_SCUP_CFG_C2_SMP_SIZE                       1
#define REG_OSP_SCUP_CFG_C2_SMP_MASK                       0x00000040

#define REG_OSP_SCUP_CFG_C1_SMP_SHIFT                      5
#define REG_OSP_SCUP_CFG_C1_SMP_SIZE                       1
#define REG_OSP_SCUP_CFG_C1_SMP_MASK                       0x00000020

#define REG_OSP_SCUP_CFG_C0_SMP_SHIFT                      4
#define REG_OSP_SCUP_CFG_C0_SMP_SIZE                       1
#define REG_OSP_SCUP_CFG_C0_SMP_MASK                       0x00000010

#define REG_OSP_SCUP_CFG_CPU_NUM_SHIFT                     0
#define REG_OSP_SCUP_CFG_CPU_NUM_SIZE                      2
#define REG_OSP_SCUP_CFG_CPU_NUM_MASK                      0x00000003

#ifndef SDK_ASM
#define REG_OSP_SCUP_CFG_FIELD( c3_cache_size, c2_cache_size, c1_cache_size, c0_cache_size, c3_smp, c2_smp, c1_smp, c0_smp, cpu_num ) \
    (u32)( \
    ((u32)(c3_cache_size) << REG_OSP_SCUP_CFG_C3_CACHE_SIZE_SHIFT) | \
    ((u32)(c2_cache_size) << REG_OSP_SCUP_CFG_C2_CACHE_SIZE_SHIFT) | \
    ((u32)(c1_cache_size) << REG_OSP_SCUP_CFG_C1_CACHE_SIZE_SHIFT) | \
    ((u32)(c0_cache_size) << REG_OSP_SCUP_CFG_C0_CACHE_SIZE_SHIFT) | \
    ((u32)(c3_smp) << REG_OSP_SCUP_CFG_C3_SMP_SHIFT) | \
    ((u32)(c2_smp) << REG_OSP_SCUP_CFG_C2_SMP_SHIFT) | \
    ((u32)(c1_smp) << REG_OSP_SCUP_CFG_C1_SMP_SHIFT) | \
    ((u32)(c0_smp) << REG_OSP_SCUP_CFG_C0_SMP_SHIFT) | \
    ((u32)(cpu_num) << REG_OSP_SCUP_CFG_CPU_NUM_SHIFT))
#endif


/* SCUP_STAT */

#define REG_OSP_SCUP_STAT_C3_SHIFT                         6
#define REG_OSP_SCUP_STAT_C3_SIZE                          2
#define REG_OSP_SCUP_STAT_C3_MASK                          0x000000c0

#define REG_OSP_SCUP_STAT_C2_SHIFT                         4
#define REG_OSP_SCUP_STAT_C2_SIZE                          2
#define REG_OSP_SCUP_STAT_C2_MASK                          0x00000030

#define REG_OSP_SCUP_STAT_C1_SHIFT                         2
#define REG_OSP_SCUP_STAT_C1_SIZE                          2
#define REG_OSP_SCUP_STAT_C1_MASK                          0x0000000c

#define REG_OSP_SCUP_STAT_C0_SHIFT                         0
#define REG_OSP_SCUP_STAT_C0_SIZE                          2
#define REG_OSP_SCUP_STAT_C0_MASK                          0x00000003

#ifndef SDK_ASM
#define REG_OSP_SCUP_STAT_FIELD( c3, c2, c1, c0 ) \
    (u32)( \
    ((u32)(c3) << REG_OSP_SCUP_STAT_C3_SHIFT) | \
    ((u32)(c2) << REG_OSP_SCUP_STAT_C2_SHIFT) | \
    ((u32)(c1) << REG_OSP_SCUP_STAT_C1_SHIFT) | \
    ((u32)(c0) << REG_OSP_SCUP_STAT_C0_SHIFT))
#endif


/* SCUP_INVLD_WAY */

#define REG_OSP_SCUP_INVLD_WAY_C3_SHIFT                    12
#define REG_OSP_SCUP_INVLD_WAY_C3_SIZE                     4
#define REG_OSP_SCUP_INVLD_WAY_C3_MASK                     0x0000f000

#define REG_OSP_SCUP_INVLD_WAY_C2_SHIFT                    8
#define REG_OSP_SCUP_INVLD_WAY_C2_SIZE                     4
#define REG_OSP_SCUP_INVLD_WAY_C2_MASK                     0x00000f00

#define REG_OSP_SCUP_INVLD_WAY_C1_SHIFT                    4
#define REG_OSP_SCUP_INVLD_WAY_C1_SIZE                     4
#define REG_OSP_SCUP_INVLD_WAY_C1_MASK                     0x000000f0

#define REG_OSP_SCUP_INVLD_WAY_C0_SHIFT                    0
#define REG_OSP_SCUP_INVLD_WAY_C0_SIZE                     4
#define REG_OSP_SCUP_INVLD_WAY_C0_MASK                     0x0000000f

#ifndef SDK_ASM
#define REG_OSP_SCUP_INVLD_WAY_FIELD( c3, c2, c1, c0 ) \
    (u32)( \
    ((u32)(c3) << REG_OSP_SCUP_INVLD_WAY_C3_SHIFT) | \
    ((u32)(c2) << REG_OSP_SCUP_INVLD_WAY_C2_SHIFT) | \
    ((u32)(c1) << REG_OSP_SCUP_INVLD_WAY_C1_SHIFT) | \
    ((u32)(c0) << REG_OSP_SCUP_INVLD_WAY_C0_SHIFT))
#endif


/* SCUP_PMON_CNT */

#define REG_OSP_SCUP_PMON_CNT_MN7_OV_SHIFT                 23
#define REG_OSP_SCUP_PMON_CNT_MN7_OV_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN7_OV_MASK                  0x00800000

#define REG_OSP_SCUP_PMON_CNT_MN6_OV_SHIFT                 22
#define REG_OSP_SCUP_PMON_CNT_MN6_OV_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN6_OV_MASK                  0x00400000

#define REG_OSP_SCUP_PMON_CNT_MN5_OV_SHIFT                 21
#define REG_OSP_SCUP_PMON_CNT_MN5_OV_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN5_OV_MASK                  0x00200000

#define REG_OSP_SCUP_PMON_CNT_MN4_OV_SHIFT                 20
#define REG_OSP_SCUP_PMON_CNT_MN4_OV_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN4_OV_MASK                  0x00100000

#define REG_OSP_SCUP_PMON_CNT_MN3_OV_SHIFT                 19
#define REG_OSP_SCUP_PMON_CNT_MN3_OV_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN3_OV_MASK                  0x00080000

#define REG_OSP_SCUP_PMON_CNT_MN2_OV_SHIFT                 18
#define REG_OSP_SCUP_PMON_CNT_MN2_OV_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN2_OV_MASK                  0x00040000

#define REG_OSP_SCUP_PMON_CNT_MN1_OV_SHIFT                 17
#define REG_OSP_SCUP_PMON_CNT_MN1_OV_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN1_OV_MASK                  0x00020000

#define REG_OSP_SCUP_PMON_CNT_MN0_OV_SHIFT                 16
#define REG_OSP_SCUP_PMON_CNT_MN0_OV_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN0_OV_MASK                  0x00010000

#define REG_OSP_SCUP_PMON_CNT_MN7_IE_SHIFT                 15
#define REG_OSP_SCUP_PMON_CNT_MN7_IE_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN7_IE_MASK                  0x00008000

#define REG_OSP_SCUP_PMON_CNT_MN6_IE_SHIFT                 14
#define REG_OSP_SCUP_PMON_CNT_MN6_IE_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN6_IE_MASK                  0x00004000

#define REG_OSP_SCUP_PMON_CNT_MN5_IE_SHIFT                 13
#define REG_OSP_SCUP_PMON_CNT_MN5_IE_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN5_IE_MASK                  0x00002000

#define REG_OSP_SCUP_PMON_CNT_MN4_IE_SHIFT                 12
#define REG_OSP_SCUP_PMON_CNT_MN4_IE_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN4_IE_MASK                  0x00001000

#define REG_OSP_SCUP_PMON_CNT_MN3_IE_SHIFT                 11
#define REG_OSP_SCUP_PMON_CNT_MN3_IE_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN3_IE_MASK                  0x00000800

#define REG_OSP_SCUP_PMON_CNT_MN2_IE_SHIFT                 10
#define REG_OSP_SCUP_PMON_CNT_MN2_IE_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN2_IE_MASK                  0x00000400

#define REG_OSP_SCUP_PMON_CNT_MN1_IE_SHIFT                 9
#define REG_OSP_SCUP_PMON_CNT_MN1_IE_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN1_IE_MASK                  0x00000200

#define REG_OSP_SCUP_PMON_CNT_MN0_IE_SHIFT                 8
#define REG_OSP_SCUP_PMON_CNT_MN0_IE_SIZE                  1
#define REG_OSP_SCUP_PMON_CNT_MN0_IE_MASK                  0x00000100

#define REG_OSP_SCUP_PMON_CNT_RST_SHIFT                    1
#define REG_OSP_SCUP_PMON_CNT_RST_SIZE                     1
#define REG_OSP_SCUP_PMON_CNT_RST_MASK                     0x00000002

#define REG_OSP_SCUP_PMON_CNT_E_SHIFT                      0
#define REG_OSP_SCUP_PMON_CNT_E_SIZE                       1
#define REG_OSP_SCUP_PMON_CNT_E_MASK                       0x00000001

#ifndef SDK_ASM
#define REG_OSP_SCUP_PMON_CNT_FIELD( mn7_ov, mn6_ov, mn5_ov, mn4_ov, mn3_ov, mn2_ov, mn1_ov, mn0_ov, mn7_ie, mn6_ie, mn5_ie, mn4_ie, mn3_ie, mn2_ie, mn1_ie, mn0_ie, rst, e ) \
    (u32)( \
    ((u32)(mn7_ov) << REG_OSP_SCUP_PMON_CNT_MN7_OV_SHIFT) | \
    ((u32)(mn6_ov) << REG_OSP_SCUP_PMON_CNT_MN6_OV_SHIFT) | \
    ((u32)(mn5_ov) << REG_OSP_SCUP_PMON_CNT_MN5_OV_SHIFT) | \
    ((u32)(mn4_ov) << REG_OSP_SCUP_PMON_CNT_MN4_OV_SHIFT) | \
    ((u32)(mn3_ov) << REG_OSP_SCUP_PMON_CNT_MN3_OV_SHIFT) | \
    ((u32)(mn2_ov) << REG_OSP_SCUP_PMON_CNT_MN2_OV_SHIFT) | \
    ((u32)(mn1_ov) << REG_OSP_SCUP_PMON_CNT_MN1_OV_SHIFT) | \
    ((u32)(mn0_ov) << REG_OSP_SCUP_PMON_CNT_MN0_OV_SHIFT) | \
    ((u32)(mn7_ie) << REG_OSP_SCUP_PMON_CNT_MN7_IE_SHIFT) | \
    ((u32)(mn6_ie) << REG_OSP_SCUP_PMON_CNT_MN6_IE_SHIFT) | \
    ((u32)(mn5_ie) << REG_OSP_SCUP_PMON_CNT_MN5_IE_SHIFT) | \
    ((u32)(mn4_ie) << REG_OSP_SCUP_PMON_CNT_MN4_IE_SHIFT) | \
    ((u32)(mn3_ie) << REG_OSP_SCUP_PMON_CNT_MN3_IE_SHIFT) | \
    ((u32)(mn2_ie) << REG_OSP_SCUP_PMON_CNT_MN2_IE_SHIFT) | \
    ((u32)(mn1_ie) << REG_OSP_SCUP_PMON_CNT_MN1_IE_SHIFT) | \
    ((u32)(mn0_ie) << REG_OSP_SCUP_PMON_CNT_MN0_IE_SHIFT) | \
    ((u32)(rst) << REG_OSP_SCUP_PMON_CNT_RST_SHIFT) | \
    ((u32)(e) << REG_OSP_SCUP_PMON_CNT_E_SHIFT))
#endif


/* SCUP_PMON_EVENT0 */

#define REG_OSP_SCUP_PMON_EVENT0_EV3_SHIFT                 24
#define REG_OSP_SCUP_PMON_EVENT0_EV3_SIZE                  8
#define REG_OSP_SCUP_PMON_EVENT0_EV3_MASK                  0xff000000

#define REG_OSP_SCUP_PMON_EVENT0_EV2_SHIFT                 16
#define REG_OSP_SCUP_PMON_EVENT0_EV2_SIZE                  8
#define REG_OSP_SCUP_PMON_EVENT0_EV2_MASK                  0x00ff0000

#define REG_OSP_SCUP_PMON_EVENT0_EV1_SHIFT                 8
#define REG_OSP_SCUP_PMON_EVENT0_EV1_SIZE                  8
#define REG_OSP_SCUP_PMON_EVENT0_EV1_MASK                  0x0000ff00

#define REG_OSP_SCUP_PMON_EVENT0_EV0_SHIFT                 0
#define REG_OSP_SCUP_PMON_EVENT0_EV0_SIZE                  8
#define REG_OSP_SCUP_PMON_EVENT0_EV0_MASK                  0x000000ff

#ifndef SDK_ASM
#define REG_OSP_SCUP_PMON_EVENT0_FIELD( ev3, ev2, ev1, ev0 ) \
    (u32)( \
    ((u32)(ev3) << REG_OSP_SCUP_PMON_EVENT0_EV3_SHIFT) | \
    ((u32)(ev2) << REG_OSP_SCUP_PMON_EVENT0_EV2_SHIFT) | \
    ((u32)(ev1) << REG_OSP_SCUP_PMON_EVENT0_EV1_SHIFT) | \
    ((u32)(ev0) << REG_OSP_SCUP_PMON_EVENT0_EV0_SHIFT))
#endif


/* SCUP_PMON_EVENT1 */

#define REG_OSP_SCUP_PMON_EVENT1_EV7_SHIFT                 24
#define REG_OSP_SCUP_PMON_EVENT1_EV7_SIZE                  8
#define REG_OSP_SCUP_PMON_EVENT1_EV7_MASK                  0xff000000

#define REG_OSP_SCUP_PMON_EVENT1_EV6_SHIFT                 16
#define REG_OSP_SCUP_PMON_EVENT1_EV6_SIZE                  8
#define REG_OSP_SCUP_PMON_EVENT1_EV6_MASK                  0x00ff0000

#define REG_OSP_SCUP_PMON_EVENT1_EV5_SHIFT                 8
#define REG_OSP_SCUP_PMON_EVENT1_EV5_SIZE                  8
#define REG_OSP_SCUP_PMON_EVENT1_EV5_MASK                  0x0000ff00

#define REG_OSP_SCUP_PMON_EVENT1_EV4_SHIFT                 0
#define REG_OSP_SCUP_PMON_EVENT1_EV4_SIZE                  8
#define REG_OSP_SCUP_PMON_EVENT1_EV4_MASK                  0x000000ff

#ifndef SDK_ASM
#define REG_OSP_SCUP_PMON_EVENT1_FIELD( ev7, ev6, ev5, ev4 ) \
    (u32)( \
    ((u32)(ev7) << REG_OSP_SCUP_PMON_EVENT1_EV7_SHIFT) | \
    ((u32)(ev6) << REG_OSP_SCUP_PMON_EVENT1_EV6_SHIFT) | \
    ((u32)(ev5) << REG_OSP_SCUP_PMON_EVENT1_EV5_SHIFT) | \
    ((u32)(ev4) << REG_OSP_SCUP_PMON_EVENT1_EV4_SHIFT))
#endif


/* SCUP_PMON_COUNT0 */

/* SCUP_PMON_COUNT1 */

/* CPUIP_CNT */

#define REG_OSP_CPUIP_CNT_E_SHIFT                          0
#define REG_OSP_CPUIP_CNT_E_SIZE                           1
#define REG_OSP_CPUIP_CNT_E_MASK                           0x00000001

#ifndef SDK_ASM
#define REG_OSP_CPUIP_CNT_FIELD( e ) \
    (u32)( \
    ((u32)(e) << REG_OSP_CPUIP_CNT_E_SHIFT))
#endif


/* CPUIP_PRIO */

#define REG_OSP_CPUIP_PRIO_THLD_SHIFT                      4
#define REG_OSP_CPUIP_PRIO_THLD_SIZE                       4
#define REG_OSP_CPUIP_PRIO_THLD_MASK                       0x000000f0

#ifndef SDK_ASM
#define REG_OSP_CPUIP_PRIO_FIELD( thld ) \
    (u32)( \
    ((u32)(thld) << REG_OSP_CPUIP_PRIO_THLD_SHIFT))
#endif


/* CPUIP_BP */

#define REG_OSP_CPUIP_BP_DECI_SHIFT                        0
#define REG_OSP_CPUIP_BP_DECI_SIZE                         3
#define REG_OSP_CPUIP_BP_DECI_MASK                         0x00000007

#ifndef SDK_ASM
#define REG_OSP_CPUIP_BP_FIELD( deci ) \
    (u32)( \
    ((u32)(deci) << REG_OSP_CPUIP_BP_DECI_SHIFT))
#endif


/* CPUIP_ACK */

#define REG_OSP_CPUIP_ACK_CPU_SRC_SHIFT                    10
#define REG_OSP_CPUIP_ACK_CPU_SRC_SIZE                     3
#define REG_OSP_CPUIP_ACK_CPU_SRC_MASK                     0x00001c00

#define REG_OSP_CPUIP_ACK_ID_SHIFT                         0
#define REG_OSP_CPUIP_ACK_ID_SIZE                          10
#define REG_OSP_CPUIP_ACK_ID_MASK                          0x000003ff

#ifndef SDK_ASM
#define REG_OSP_CPUIP_ACK_FIELD( cpu_src, id ) \
    (u32)( \
    ((u32)(cpu_src) << REG_OSP_CPUIP_ACK_CPU_SRC_SHIFT) | \
    ((u32)(id) << REG_OSP_CPUIP_ACK_ID_SHIFT))
#endif


/* CPUIP_EOI */

#define REG_OSP_CPUIP_EOI_CPU_SRC_SHIFT                    10
#define REG_OSP_CPUIP_EOI_CPU_SRC_SIZE                     3
#define REG_OSP_CPUIP_EOI_CPU_SRC_MASK                     0x00001c00

#define REG_OSP_CPUIP_EOI_ID_SHIFT                         0
#define REG_OSP_CPUIP_EOI_ID_SIZE                          10
#define REG_OSP_CPUIP_EOI_ID_MASK                          0x000003ff

#ifndef SDK_ASM
#define REG_OSP_CPUIP_EOI_FIELD( cpu_src, id ) \
    (u32)( \
    ((u32)(cpu_src) << REG_OSP_CPUIP_EOI_CPU_SRC_SHIFT) | \
    ((u32)(id) << REG_OSP_CPUIP_EOI_ID_SHIFT))
#endif


/* CPUIP_RUN_INTR */

#define REG_OSP_CPUIP_RUN_INTR_PRIO_SHIFT                  4
#define REG_OSP_CPUIP_RUN_INTR_PRIO_SIZE                   4
#define REG_OSP_CPUIP_RUN_INTR_PRIO_MASK                   0x000000f0

#ifndef SDK_ASM
#define REG_OSP_CPUIP_RUN_INTR_FIELD( prio ) \
    (u32)( \
    ((u32)(prio) << REG_OSP_CPUIP_RUN_INTR_PRIO_SHIFT))
#endif


/* CPUIP_HI_PND */

#define REG_OSP_CPUIP_HI_PND_CPU_SRC_SHIFT                 10
#define REG_OSP_CPUIP_HI_PND_CPU_SRC_SIZE                  3
#define REG_OSP_CPUIP_HI_PND_CPU_SRC_MASK                  0x00001c00

#define REG_OSP_CPUIP_HI_PND_ID_SHIFT                      0
#define REG_OSP_CPUIP_HI_PND_ID_SIZE                       10
#define REG_OSP_CPUIP_HI_PND_ID_MASK                       0x000003ff

#ifndef SDK_ASM
#define REG_OSP_CPUIP_HI_PND_FIELD( cpu_src, id ) \
    (u32)( \
    ((u32)(cpu_src) << REG_OSP_CPUIP_HI_PND_CPU_SRC_SHIFT) | \
    ((u32)(id) << REG_OSP_CPUIP_HI_PND_ID_SHIFT))
#endif


/* IDRP_CNT */

#define REG_OSP_IDRP_CNT_E_SHIFT                           0
#define REG_OSP_IDRP_CNT_E_SIZE                            1
#define REG_OSP_IDRP_CNT_E_MASK                            0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CNT_FIELD( e ) \
    (u32)( \
    ((u32)(e) << REG_OSP_IDRP_CNT_E_SHIFT))
#endif


/* IDRP_TYPE */

#define REG_OSP_IDRP_TYPE_CPU_NUM_SHIFT                    5
#define REG_OSP_IDRP_TYPE_CPU_NUM_SIZE                     3
#define REG_OSP_IDRP_TYPE_CPU_NUM_MASK                     0x000000e0

#define REG_OSP_IDRP_TYPE_IT_LINE_NUM_SHIFT                0
#define REG_OSP_IDRP_TYPE_IT_LINE_NUM_SIZE                 5
#define REG_OSP_IDRP_TYPE_IT_LINE_NUM_MASK                 0x0000001f

#ifndef SDK_ASM
#define REG_OSP_IDRP_TYPE_FIELD( cpu_num, it_line_num ) \
    (u32)( \
    ((u32)(cpu_num) << REG_OSP_IDRP_TYPE_CPU_NUM_SHIFT) | \
    ((u32)(it_line_num) << REG_OSP_IDRP_TYPE_IT_LINE_NUM_SHIFT))
#endif


/* IDRP_SET_IE0 */

#define REG_OSP_IDRP_SET_IE0_WDOG_SHIFT                    30
#define REG_OSP_IDRP_SET_IE0_WDOG_SIZE                     1
#define REG_OSP_IDRP_SET_IE0_WDOG_MASK                     0x40000000

#define REG_OSP_IDRP_SET_IE0_TM_SHIFT                      29
#define REG_OSP_IDRP_SET_IE0_TM_SIZE                       1
#define REG_OSP_IDRP_SET_IE0_TM_MASK                       0x20000000

#define REG_OSP_IDRP_SET_IE0_IPI15_SHIFT                   15
#define REG_OSP_IDRP_SET_IE0_IPI15_SIZE                    1
#define REG_OSP_IDRP_SET_IE0_IPI15_MASK                    0x00008000

#define REG_OSP_IDRP_SET_IE0_IPI14_SHIFT                   14
#define REG_OSP_IDRP_SET_IE0_IPI14_SIZE                    1
#define REG_OSP_IDRP_SET_IE0_IPI14_MASK                    0x00004000

#define REG_OSP_IDRP_SET_IE0_IPI13_SHIFT                   13
#define REG_OSP_IDRP_SET_IE0_IPI13_SIZE                    1
#define REG_OSP_IDRP_SET_IE0_IPI13_MASK                    0x00002000

#define REG_OSP_IDRP_SET_IE0_IPI12_SHIFT                   12
#define REG_OSP_IDRP_SET_IE0_IPI12_SIZE                    1
#define REG_OSP_IDRP_SET_IE0_IPI12_MASK                    0x00001000

#define REG_OSP_IDRP_SET_IE0_IPI11_SHIFT                   11
#define REG_OSP_IDRP_SET_IE0_IPI11_SIZE                    1
#define REG_OSP_IDRP_SET_IE0_IPI11_MASK                    0x00000800

#define REG_OSP_IDRP_SET_IE0_IPI10_SHIFT                   10
#define REG_OSP_IDRP_SET_IE0_IPI10_SIZE                    1
#define REG_OSP_IDRP_SET_IE0_IPI10_MASK                    0x00000400

#define REG_OSP_IDRP_SET_IE0_IPI9_SHIFT                    9
#define REG_OSP_IDRP_SET_IE0_IPI9_SIZE                     1
#define REG_OSP_IDRP_SET_IE0_IPI9_MASK                     0x00000200

#define REG_OSP_IDRP_SET_IE0_IPI8_SHIFT                    8
#define REG_OSP_IDRP_SET_IE0_IPI8_SIZE                     1
#define REG_OSP_IDRP_SET_IE0_IPI8_MASK                     0x00000100

#define REG_OSP_IDRP_SET_IE0_IPI7_SHIFT                    7
#define REG_OSP_IDRP_SET_IE0_IPI7_SIZE                     1
#define REG_OSP_IDRP_SET_IE0_IPI7_MASK                     0x00000080

#define REG_OSP_IDRP_SET_IE0_IPI6_SHIFT                    6
#define REG_OSP_IDRP_SET_IE0_IPI6_SIZE                     1
#define REG_OSP_IDRP_SET_IE0_IPI6_MASK                     0x00000040

#define REG_OSP_IDRP_SET_IE0_IPI5_SHIFT                    5
#define REG_OSP_IDRP_SET_IE0_IPI5_SIZE                     1
#define REG_OSP_IDRP_SET_IE0_IPI5_MASK                     0x00000020

#define REG_OSP_IDRP_SET_IE0_IPI4_SHIFT                    4
#define REG_OSP_IDRP_SET_IE0_IPI4_SIZE                     1
#define REG_OSP_IDRP_SET_IE0_IPI4_MASK                     0x00000010

#define REG_OSP_IDRP_SET_IE0_IPI3_SHIFT                    3
#define REG_OSP_IDRP_SET_IE0_IPI3_SIZE                     1
#define REG_OSP_IDRP_SET_IE0_IPI3_MASK                     0x00000008

#define REG_OSP_IDRP_SET_IE0_IPI2_SHIFT                    2
#define REG_OSP_IDRP_SET_IE0_IPI2_SIZE                     1
#define REG_OSP_IDRP_SET_IE0_IPI2_MASK                     0x00000004

#define REG_OSP_IDRP_SET_IE0_IPI1_SHIFT                    1
#define REG_OSP_IDRP_SET_IE0_IPI1_SIZE                     1
#define REG_OSP_IDRP_SET_IE0_IPI1_MASK                     0x00000002

#define REG_OSP_IDRP_SET_IE0_IPI0_SHIFT                    0
#define REG_OSP_IDRP_SET_IE0_IPI0_SIZE                     1
#define REG_OSP_IDRP_SET_IE0_IPI0_MASK                     0x00000001

#define REG_OSP_IDRP_SET_IE0_IPI_ALL_SHIFT                 0
#define REG_OSP_IDRP_SET_IE0_IPI_ALL_SIZE                  16
#define REG_OSP_IDRP_SET_IE0_IPI_ALL_MASK                  0x0000ffff

#ifndef SDK_ASM
#define REG_OSP_IDRP_SET_IE0_FIELD( wdog, tm, ipi15, ipi14, ipi13, ipi12, ipi11, ipi10, ipi9, ipi8, ipi7, ipi6, ipi5, ipi4, ipi3, ipi2, ipi1, ipi0, ipi_all ) \
    (u32)( \
    ((u32)(wdog) << REG_OSP_IDRP_SET_IE0_WDOG_SHIFT) | \
    ((u32)(tm) << REG_OSP_IDRP_SET_IE0_TM_SHIFT) | \
    ((u32)(ipi15) << REG_OSP_IDRP_SET_IE0_IPI15_SHIFT) | \
    ((u32)(ipi14) << REG_OSP_IDRP_SET_IE0_IPI14_SHIFT) | \
    ((u32)(ipi13) << REG_OSP_IDRP_SET_IE0_IPI13_SHIFT) | \
    ((u32)(ipi12) << REG_OSP_IDRP_SET_IE0_IPI12_SHIFT) | \
    ((u32)(ipi11) << REG_OSP_IDRP_SET_IE0_IPI11_SHIFT) | \
    ((u32)(ipi10) << REG_OSP_IDRP_SET_IE0_IPI10_SHIFT) | \
    ((u32)(ipi9) << REG_OSP_IDRP_SET_IE0_IPI9_SHIFT) | \
    ((u32)(ipi8) << REG_OSP_IDRP_SET_IE0_IPI8_SHIFT) | \
    ((u32)(ipi7) << REG_OSP_IDRP_SET_IE0_IPI7_SHIFT) | \
    ((u32)(ipi6) << REG_OSP_IDRP_SET_IE0_IPI6_SHIFT) | \
    ((u32)(ipi5) << REG_OSP_IDRP_SET_IE0_IPI5_SHIFT) | \
    ((u32)(ipi4) << REG_OSP_IDRP_SET_IE0_IPI4_SHIFT) | \
    ((u32)(ipi3) << REG_OSP_IDRP_SET_IE0_IPI3_SHIFT) | \
    ((u32)(ipi2) << REG_OSP_IDRP_SET_IE0_IPI2_SHIFT) | \
    ((u32)(ipi1) << REG_OSP_IDRP_SET_IE0_IPI1_SHIFT) | \
    ((u32)(ipi0) << REG_OSP_IDRP_SET_IE0_IPI0_SHIFT) | \
    ((u32)(ipi_all) << REG_OSP_IDRP_SET_IE0_IPI_ALL_SHIFT))
#endif


/* IDRP_SET_IE1 */

#define REG_OSP_IDRP_SET_IE1_XDMA_ABT_SHIFT                25
#define REG_OSP_IDRP_SET_IE1_XDMA_ABT_SIZE                 1
#define REG_OSP_IDRP_SET_IE1_XDMA_ABT_MASK                 0x02000000

#define REG_OSP_IDRP_SET_IE1_XDMA7_SHIFT                   24
#define REG_OSP_IDRP_SET_IE1_XDMA7_SIZE                    1
#define REG_OSP_IDRP_SET_IE1_XDMA7_MASK                    0x01000000

#define REG_OSP_IDRP_SET_IE1_XDMA6_SHIFT                   22
#define REG_OSP_IDRP_SET_IE1_XDMA6_SIZE                    1
#define REG_OSP_IDRP_SET_IE1_XDMA6_MASK                    0x00400000

#define REG_OSP_IDRP_SET_IE1_XDMA5_SHIFT                   21
#define REG_OSP_IDRP_SET_IE1_XDMA5_SIZE                    1
#define REG_OSP_IDRP_SET_IE1_XDMA5_MASK                    0x00200000

#define REG_OSP_IDRP_SET_IE1_XDMA4_SHIFT                   20
#define REG_OSP_IDRP_SET_IE1_XDMA4_SIZE                    1
#define REG_OSP_IDRP_SET_IE1_XDMA4_MASK                    0x00100000

#define REG_OSP_IDRP_SET_IE1_XDMA3_SHIFT                   19
#define REG_OSP_IDRP_SET_IE1_XDMA3_SIZE                    1
#define REG_OSP_IDRP_SET_IE1_XDMA3_MASK                    0x00080000

#define REG_OSP_IDRP_SET_IE1_XDMA2_SHIFT                   18
#define REG_OSP_IDRP_SET_IE1_XDMA2_SIZE                    1
#define REG_OSP_IDRP_SET_IE1_XDMA2_MASK                    0x00040000

#define REG_OSP_IDRP_SET_IE1_XDMA1_SHIFT                   17
#define REG_OSP_IDRP_SET_IE1_XDMA1_SIZE                    1
#define REG_OSP_IDRP_SET_IE1_XDMA1_MASK                    0x00020000

#define REG_OSP_IDRP_SET_IE1_XDMA0_SHIFT                   16
#define REG_OSP_IDRP_SET_IE1_XDMA0_SIZE                    1
#define REG_OSP_IDRP_SET_IE1_XDMA0_MASK                    0x00010000

#define REG_OSP_IDRP_SET_IE1_GPU_P3D_SHIFT                 13
#define REG_OSP_IDRP_SET_IE1_GPU_P3D_SIZE                  1
#define REG_OSP_IDRP_SET_IE1_GPU_P3D_MASK                  0x00002000

#define REG_OSP_IDRP_SET_IE1_GPU_PPF_SHIFT                 12
#define REG_OSP_IDRP_SET_IE1_GPU_PPF_SIZE                  1
#define REG_OSP_IDRP_SET_IE1_GPU_PPF_MASK                  0x00001000

#define REG_OSP_IDRP_SET_IE1_GPU_PDC1_SHIFT                11
#define REG_OSP_IDRP_SET_IE1_GPU_PDC1_SIZE                 1
#define REG_OSP_IDRP_SET_IE1_GPU_PDC1_MASK                 0x00000800

#define REG_OSP_IDRP_SET_IE1_GPU_PDC0_SHIFT                10
#define REG_OSP_IDRP_SET_IE1_GPU_PDC0_SIZE                 1
#define REG_OSP_IDRP_SET_IE1_GPU_PDC0_MASK                 0x00000400

#define REG_OSP_IDRP_SET_IE1_GPU_PSC1_SHIFT                9
#define REG_OSP_IDRP_SET_IE1_GPU_PSC1_SIZE                 1
#define REG_OSP_IDRP_SET_IE1_GPU_PSC1_MASK                 0x00000200

#define REG_OSP_IDRP_SET_IE1_GPU_PSC0_SHIFT                8
#define REG_OSP_IDRP_SET_IE1_GPU_PSC0_SIZE                 1
#define REG_OSP_IDRP_SET_IE1_GPU_PSC0_MASK                 0x00000100

#define REG_OSP_IDRP_SET_IE1_DBG_SPI_SHIFT                 4
#define REG_OSP_IDRP_SET_IE1_DBG_SPI_SIZE                  1
#define REG_OSP_IDRP_SET_IE1_DBG_SPI_MASK                  0x00000010

#define REG_OSP_IDRP_SET_IE1_J1_TX_SHIFT                   3
#define REG_OSP_IDRP_SET_IE1_J1_TX_SIZE                    1
#define REG_OSP_IDRP_SET_IE1_J1_TX_MASK                    0x00000008

#define REG_OSP_IDRP_SET_IE1_J1_RX_SHIFT                   2
#define REG_OSP_IDRP_SET_IE1_J1_RX_SIZE                    1
#define REG_OSP_IDRP_SET_IE1_J1_RX_MASK                    0x00000004

#define REG_OSP_IDRP_SET_IE1_J0_TX_SHIFT                   1
#define REG_OSP_IDRP_SET_IE1_J0_TX_SIZE                    1
#define REG_OSP_IDRP_SET_IE1_J0_TX_MASK                    0x00000002

#define REG_OSP_IDRP_SET_IE1_J0_RX_SHIFT                   0
#define REG_OSP_IDRP_SET_IE1_J0_RX_SIZE                    1
#define REG_OSP_IDRP_SET_IE1_J0_RX_MASK                    0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_SET_IE1_FIELD( xdma_abt, xdma7, xdma6, xdma5, xdma4, xdma3, xdma2, xdma1, xdma0, gpu_p3d, gpu_ppf, gpu_pdc1, gpu_pdc0, gpu_psc1, gpu_psc0, dbg_spi, j1_tx, j1_rx, j0_tx, j0_rx ) \
    (u32)( \
    ((u32)(xdma_abt) << REG_OSP_IDRP_SET_IE1_XDMA_ABT_SHIFT) | \
    ((u32)(xdma7) << REG_OSP_IDRP_SET_IE1_XDMA7_SHIFT) | \
    ((u32)(xdma6) << REG_OSP_IDRP_SET_IE1_XDMA6_SHIFT) | \
    ((u32)(xdma5) << REG_OSP_IDRP_SET_IE1_XDMA5_SHIFT) | \
    ((u32)(xdma4) << REG_OSP_IDRP_SET_IE1_XDMA4_SHIFT) | \
    ((u32)(xdma3) << REG_OSP_IDRP_SET_IE1_XDMA3_SHIFT) | \
    ((u32)(xdma2) << REG_OSP_IDRP_SET_IE1_XDMA2_SHIFT) | \
    ((u32)(xdma1) << REG_OSP_IDRP_SET_IE1_XDMA1_SHIFT) | \
    ((u32)(xdma0) << REG_OSP_IDRP_SET_IE1_XDMA0_SHIFT) | \
    ((u32)(gpu_p3d) << REG_OSP_IDRP_SET_IE1_GPU_P3D_SHIFT) | \
    ((u32)(gpu_ppf) << REG_OSP_IDRP_SET_IE1_GPU_PPF_SHIFT) | \
    ((u32)(gpu_pdc1) << REG_OSP_IDRP_SET_IE1_GPU_PDC1_SHIFT) | \
    ((u32)(gpu_pdc0) << REG_OSP_IDRP_SET_IE1_GPU_PDC0_SHIFT) | \
    ((u32)(gpu_psc1) << REG_OSP_IDRP_SET_IE1_GPU_PSC1_SHIFT) | \
    ((u32)(gpu_psc0) << REG_OSP_IDRP_SET_IE1_GPU_PSC0_SHIFT) | \
    ((u32)(dbg_spi) << REG_OSP_IDRP_SET_IE1_DBG_SPI_SHIFT) | \
    ((u32)(j1_tx) << REG_OSP_IDRP_SET_IE1_J1_TX_SHIFT) | \
    ((u32)(j1_rx) << REG_OSP_IDRP_SET_IE1_J1_RX_SHIFT) | \
    ((u32)(j0_tx) << REG_OSP_IDRP_SET_IE1_J0_TX_SHIFT) | \
    ((u32)(j0_rx) << REG_OSP_IDRP_SET_IE1_J0_RX_SHIFT))
#endif


/* IDRP_SET_IE2 */

#define REG_OSP_IDRP_SET_IE2_DS_WL_SHIFT                   31
#define REG_OSP_IDRP_SET_IE2_DS_WL_SIZE                    1
#define REG_OSP_IDRP_SET_IE2_DS_WL_MASK                    0x80000000

#define REG_OSP_IDRP_SET_IE2_I2C3_SHIFT                    28
#define REG_OSP_IDRP_SET_IE2_I2C3_SIZE                     1
#define REG_OSP_IDRP_SET_IE2_I2C3_MASK                     0x10000000

#define REG_OSP_IDRP_SET_IE2_KEY_SHIFT                     27
#define REG_OSP_IDRP_SET_IE2_KEY_SIZE                      1
#define REG_OSP_IDRP_SET_IE2_KEY_MASK                      0x08000000

#define REG_OSP_IDRP_SET_IE2_MIC_SHIFT                     26
#define REG_OSP_IDRP_SET_IE2_MIC_SIZE                      1
#define REG_OSP_IDRP_SET_IE2_MIC_MASK                      0x04000000

#define REG_OSP_IDRP_SET_IE2_PDN_LGY_SHIFT                 25
#define REG_OSP_IDRP_SET_IE2_PDN_LGY_SIZE                  1
#define REG_OSP_IDRP_SET_IE2_PDN_LGY_MASK                  0x02000000

#define REG_OSP_IDRP_SET_IE2_PDN_WAKE_SHIFT                24
#define REG_OSP_IDRP_SET_IE2_PDN_WAKE_SIZE                 1
#define REG_OSP_IDRP_SET_IE2_PDN_WAKE_MASK                 0x01000000

#define REG_OSP_IDRP_SET_IE2_SPI2_SHIFT                    23
#define REG_OSP_IDRP_SET_IE2_SPI2_SIZE                     1
#define REG_OSP_IDRP_SET_IE2_SPI2_MASK                     0x00800000

#define REG_OSP_IDRP_SET_IE2_SPI1_SHIFT                    22
#define REG_OSP_IDRP_SET_IE2_SPI1_SIZE                     1
#define REG_OSP_IDRP_SET_IE2_SPI1_MASK                     0x00400000

#define REG_OSP_IDRP_SET_IE2_I2C2_SHIFT                    21
#define REG_OSP_IDRP_SET_IE2_I2C2_SIZE                     1
#define REG_OSP_IDRP_SET_IE2_I2C2_MASK                     0x00200000

#define REG_OSP_IDRP_SET_IE2_I2C1_SHIFT                    20
#define REG_OSP_IDRP_SET_IE2_I2C1_SIZE                     1
#define REG_OSP_IDRP_SET_IE2_I2C1_MASK                     0x00100000

#define REG_OSP_IDRP_SET_IE2_PXI_RX_SHIFT                  19
#define REG_OSP_IDRP_SET_IE2_PXI_RX_SIZE                   1
#define REG_OSP_IDRP_SET_IE2_PXI_RX_MASK                   0x00080000

#define REG_OSP_IDRP_SET_IE2_PXI_TX_SHIFT                  18
#define REG_OSP_IDRP_SET_IE2_PXI_TX_SIZE                   1
#define REG_OSP_IDRP_SET_IE2_PXI_TX_MASK                   0x00040000

#define REG_OSP_IDRP_SET_IE2_CPU1_SHIFT                    17
#define REG_OSP_IDRP_SET_IE2_CPU1_SIZE                     1
#define REG_OSP_IDRP_SET_IE2_CPU1_MASK                     0x00020000

#define REG_OSP_IDRP_SET_IE2_CPU0_SHIFT                    16
#define REG_OSP_IDRP_SET_IE2_CPU0_SIZE                     1
#define REG_OSP_IDRP_SET_IE2_CPU0_MASK                     0x00010000

#define REG_OSP_IDRP_SET_IE2_SCLR2_SHIFT                   13
#define REG_OSP_IDRP_SET_IE2_SCLR2_SIZE                    1
#define REG_OSP_IDRP_SET_IE2_SCLR2_MASK                    0x00002000

#define REG_OSP_IDRP_SET_IE2_SCLR1_SHIFT                   12
#define REG_OSP_IDRP_SET_IE2_SCLR1_SIZE                    1
#define REG_OSP_IDRP_SET_IE2_SCLR1_MASK                    0x00001000

#define REG_OSP_IDRP_SET_IE2_YUV2RGB_SHIFT                 11
#define REG_OSP_IDRP_SET_IE2_YUV2RGB_SIZE                  1
#define REG_OSP_IDRP_SET_IE2_YUV2RGB_MASK                  0x00000800

#define REG_OSP_IDRP_SET_IE2_DSP_SHIFT                     10
#define REG_OSP_IDRP_SET_IE2_DSP_SIZE                      1
#define REG_OSP_IDRP_SET_IE2_DSP_MASK                      0x00000400

#define REG_OSP_IDRP_SET_IE2_CAM2_SHIFT                    9
#define REG_OSP_IDRP_SET_IE2_CAM2_SIZE                     1
#define REG_OSP_IDRP_SET_IE2_CAM2_MASK                     0x00000200

#define REG_OSP_IDRP_SET_IE2_CAM1_SHIFT                    8
#define REG_OSP_IDRP_SET_IE2_CAM1_SIZE                     1
#define REG_OSP_IDRP_SET_IE2_CAM1_MASK                     0x00000100

#define REG_OSP_IDRP_SET_IE2_LGC_DET_SHIFT                 6
#define REG_OSP_IDRP_SET_IE2_LGC_DET_SIZE                  1
#define REG_OSP_IDRP_SET_IE2_LGC_DET_MASK                  0x00000040

#define REG_OSP_IDRP_SET_IE2_LGC_I_SHIFT                   5
#define REG_OSP_IDRP_SET_IE2_LGC_I_SIZE                    1
#define REG_OSP_IDRP_SET_IE2_LGC_I_MASK                    0x00000020

#define REG_OSP_IDRP_SET_IE2_LMC_SHIFT                     4
#define REG_OSP_IDRP_SET_IE2_LMC_SIZE                      1
#define REG_OSP_IDRP_SET_IE2_LMC_MASK                      0x00000010

#define REG_OSP_IDRP_SET_IE2_SD3_A_SHIFT                   3
#define REG_OSP_IDRP_SET_IE2_SD3_A_SIZE                    1
#define REG_OSP_IDRP_SET_IE2_SD3_A_MASK                    0x00000008

#define REG_OSP_IDRP_SET_IE2_SD3_SHIFT                     2
#define REG_OSP_IDRP_SET_IE2_SD3_SIZE                      1
#define REG_OSP_IDRP_SET_IE2_SD3_MASK                      0x00000004

#define REG_OSP_IDRP_SET_IE2_SD2_A_SHIFT                   1
#define REG_OSP_IDRP_SET_IE2_SD2_A_SIZE                    1
#define REG_OSP_IDRP_SET_IE2_SD2_A_MASK                    0x00000002

#define REG_OSP_IDRP_SET_IE2_SD2_SHIFT                     0
#define REG_OSP_IDRP_SET_IE2_SD2_SIZE                      1
#define REG_OSP_IDRP_SET_IE2_SD2_MASK                      0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_SET_IE2_FIELD( ds_wl, i2c3, key, mic, pdn_lgy, pdn_wake, spi2, spi1, i2c2, i2c1, pxi_rx, pxi_tx, cpu1, cpu0, sclr2, sclr1, yuv2rgb, dsp, cam2, cam1, lgc_det, lgc_i, lmc, sd3_a, sd3, sd2_a, sd2 ) \
    (u32)( \
    ((u32)(ds_wl) << REG_OSP_IDRP_SET_IE2_DS_WL_SHIFT) | \
    ((u32)(i2c3) << REG_OSP_IDRP_SET_IE2_I2C3_SHIFT) | \
    ((u32)(key) << REG_OSP_IDRP_SET_IE2_KEY_SHIFT) | \
    ((u32)(mic) << REG_OSP_IDRP_SET_IE2_MIC_SHIFT) | \
    ((u32)(pdn_lgy) << REG_OSP_IDRP_SET_IE2_PDN_LGY_SHIFT) | \
    ((u32)(pdn_wake) << REG_OSP_IDRP_SET_IE2_PDN_WAKE_SHIFT) | \
    ((u32)(spi2) << REG_OSP_IDRP_SET_IE2_SPI2_SHIFT) | \
    ((u32)(spi1) << REG_OSP_IDRP_SET_IE2_SPI1_SHIFT) | \
    ((u32)(i2c2) << REG_OSP_IDRP_SET_IE2_I2C2_SHIFT) | \
    ((u32)(i2c1) << REG_OSP_IDRP_SET_IE2_I2C1_SHIFT) | \
    ((u32)(pxi_rx) << REG_OSP_IDRP_SET_IE2_PXI_RX_SHIFT) | \
    ((u32)(pxi_tx) << REG_OSP_IDRP_SET_IE2_PXI_TX_SHIFT) | \
    ((u32)(cpu1) << REG_OSP_IDRP_SET_IE2_CPU1_SHIFT) | \
    ((u32)(cpu0) << REG_OSP_IDRP_SET_IE2_CPU0_SHIFT) | \
    ((u32)(sclr2) << REG_OSP_IDRP_SET_IE2_SCLR2_SHIFT) | \
    ((u32)(sclr1) << REG_OSP_IDRP_SET_IE2_SCLR1_SHIFT) | \
    ((u32)(yuv2rgb) << REG_OSP_IDRP_SET_IE2_YUV2RGB_SHIFT) | \
    ((u32)(dsp) << REG_OSP_IDRP_SET_IE2_DSP_SHIFT) | \
    ((u32)(cam2) << REG_OSP_IDRP_SET_IE2_CAM2_SHIFT) | \
    ((u32)(cam1) << REG_OSP_IDRP_SET_IE2_CAM1_SHIFT) | \
    ((u32)(lgc_det) << REG_OSP_IDRP_SET_IE2_LGC_DET_SHIFT) | \
    ((u32)(lgc_i) << REG_OSP_IDRP_SET_IE2_LGC_I_SHIFT) | \
    ((u32)(lmc) << REG_OSP_IDRP_SET_IE2_LMC_SHIFT) | \
    ((u32)(sd3_a) << REG_OSP_IDRP_SET_IE2_SD3_A_SHIFT) | \
    ((u32)(sd3) << REG_OSP_IDRP_SET_IE2_SD3_SHIFT) | \
    ((u32)(sd2_a) << REG_OSP_IDRP_SET_IE2_SD2_A_SHIFT) | \
    ((u32)(sd2) << REG_OSP_IDRP_SET_IE2_SD2_SHIFT))
#endif


/* IDRP_SET_IE3 */

#define REG_OSP_IDRP_SET_IE3_PMUIRQ7_SHIFT                 29
#define REG_OSP_IDRP_SET_IE3_PMUIRQ7_SIZE                  1
#define REG_OSP_IDRP_SET_IE3_PMUIRQ7_MASK                  0x20000000

#define REG_OSP_IDRP_SET_IE3_PMUIRQ6_SHIFT                 28
#define REG_OSP_IDRP_SET_IE3_PMUIRQ6_SIZE                  1
#define REG_OSP_IDRP_SET_IE3_PMUIRQ6_MASK                  0x10000000

#define REG_OSP_IDRP_SET_IE3_PMUIRQ5_SHIFT                 27
#define REG_OSP_IDRP_SET_IE3_PMUIRQ5_SIZE                  1
#define REG_OSP_IDRP_SET_IE3_PMUIRQ5_MASK                  0x08000000

#define REG_OSP_IDRP_SET_IE3_PMUIRQ4_SHIFT                 26
#define REG_OSP_IDRP_SET_IE3_PMUIRQ4_SIZE                  1
#define REG_OSP_IDRP_SET_IE3_PMUIRQ4_MASK                  0x04000000

#define REG_OSP_IDRP_SET_IE3_PMUIRQ1_SHIFT                 25
#define REG_OSP_IDRP_SET_IE3_PMUIRQ1_SIZE                  1
#define REG_OSP_IDRP_SET_IE3_PMUIRQ1_MASK                  0x02000000

#define REG_OSP_IDRP_SET_IE3_PMUIRQ0_SHIFT                 24
#define REG_OSP_IDRP_SET_IE3_PMUIRQ0_SIZE                  1
#define REG_OSP_IDRP_SET_IE3_PMUIRQ0_MASK                  0x01000000

#define REG_OSP_IDRP_SET_IE3_CGC_DET_SHIFT                 21
#define REG_OSP_IDRP_SET_IE3_CGC_DET_SIZE                  1
#define REG_OSP_IDRP_SET_IE3_CGC_DET_MASK                  0x00200000

#define REG_OSP_IDRP_SET_IE3_CGC_I_SHIFT                   20
#define REG_OSP_IDRP_SET_IE3_CGC_I_SIZE                    1
#define REG_OSP_IDRP_SET_IE3_CGC_I_MASK                    0x00100000

#define REG_OSP_IDRP_SET_IE3_GPIO3_18_5_SHIFT              19
#define REG_OSP_IDRP_SET_IE3_GPIO3_18_5_SIZE               1
#define REG_OSP_IDRP_SET_IE3_GPIO3_18_5_MASK               0x00080000

#define REG_OSP_IDRP_SET_IE3_GPIO3_18_4_SHIFT              18
#define REG_OSP_IDRP_SET_IE3_GPIO3_18_4_SIZE               1
#define REG_OSP_IDRP_SET_IE3_GPIO3_18_4_MASK               0x00040000

#define REG_OSP_IDRP_SET_IE3_GPIO3_18_3_SHIFT              17
#define REG_OSP_IDRP_SET_IE3_GPIO3_18_3_SIZE               1
#define REG_OSP_IDRP_SET_IE3_GPIO3_18_3_MASK               0x00020000

#define REG_OSP_IDRP_SET_IE3_GPIO3_18_2_SHIFT              16
#define REG_OSP_IDRP_SET_IE3_GPIO3_18_2_SIZE               1
#define REG_OSP_IDRP_SET_IE3_GPIO3_18_2_MASK               0x00010000

#define REG_OSP_IDRP_SET_IE3_GPIO3_18_1_SHIFT              15
#define REG_OSP_IDRP_SET_IE3_GPIO3_18_1_SIZE               1
#define REG_OSP_IDRP_SET_IE3_GPIO3_18_1_MASK               0x00008000

#define REG_OSP_IDRP_SET_IE3_GPIO3_18_0_SHIFT              14
#define REG_OSP_IDRP_SET_IE3_GPIO3_18_0_SIZE               1
#define REG_OSP_IDRP_SET_IE3_GPIO3_18_0_MASK               0x00004000

#define REG_OSP_IDRP_SET_IE3_GPIO3_33_5_SHIFT              13
#define REG_OSP_IDRP_SET_IE3_GPIO3_33_5_SIZE               1
#define REG_OSP_IDRP_SET_IE3_GPIO3_33_5_MASK               0x00002000

#define REG_OSP_IDRP_SET_IE3_GPIO3_33_4_SHIFT              12
#define REG_OSP_IDRP_SET_IE3_GPIO3_33_4_SIZE               1
#define REG_OSP_IDRP_SET_IE3_GPIO3_33_4_MASK               0x00001000

#define REG_OSP_IDRP_SET_IE3_GPIO3_33_3_SHIFT              11
#define REG_OSP_IDRP_SET_IE3_GPIO3_33_3_SIZE               1
#define REG_OSP_IDRP_SET_IE3_GPIO3_33_3_MASK               0x00000800

#define REG_OSP_IDRP_SET_IE3_GPIO3_33_2_SHIFT              10
#define REG_OSP_IDRP_SET_IE3_GPIO3_33_2_SIZE               1
#define REG_OSP_IDRP_SET_IE3_GPIO3_33_2_MASK               0x00000400

#define REG_OSP_IDRP_SET_IE3_GPIO3_33_1_SHIFT              9
#define REG_OSP_IDRP_SET_IE3_GPIO3_33_1_SIZE               1
#define REG_OSP_IDRP_SET_IE3_GPIO3_33_1_MASK               0x00000200

#define REG_OSP_IDRP_SET_IE3_GPIO3_33_0_SHIFT              8
#define REG_OSP_IDRP_SET_IE3_GPIO3_33_0_SIZE               1
#define REG_OSP_IDRP_SET_IE3_GPIO3_33_0_MASK               0x00000100

#define REG_OSP_IDRP_SET_IE3_CTR_MCU_SHIFT                 17
#define REG_OSP_IDRP_SET_IE3_CTR_MCU_SIZE                  1
#define REG_OSP_IDRP_SET_IE3_CTR_MCU_MASK                  0x00020000

#define REG_OSP_IDRP_SET_IE3_RMC_SHIFT                     16
#define REG_OSP_IDRP_SET_IE3_RMC_SIZE                      1
#define REG_OSP_IDRP_SET_IE3_RMC_MASK                      0x00010000

#define REG_OSP_IDRP_SET_IE3_IR_SHIFT                      10
#define REG_OSP_IDRP_SET_IE3_IR_SIZE                       1
#define REG_OSP_IDRP_SET_IE3_IR_MASK                       0x00000400

#define REG_OSP_IDRP_SET_IE3_SP_SEL_SHIFT                  8
#define REG_OSP_IDRP_SET_IE3_SP_SEL_SIZE                   1
#define REG_OSP_IDRP_SET_IE3_SP_SEL_MASK                   0x00000100

#define REG_OSP_IDRP_SET_IE3_TWL_DEPOP_SHIFT               6
#define REG_OSP_IDRP_SET_IE3_TWL_DEPOP_SIZE                1
#define REG_OSP_IDRP_SET_IE3_TWL_DEPOP_MASK                0x00000040

#define REG_OSP_IDRP_SET_IE3_TWL_MCU_SHIFT                 5
#define REG_OSP_IDRP_SET_IE3_TWL_MCU_SIZE                  1
#define REG_OSP_IDRP_SET_IE3_TWL_MCU_MASK                  0x00000020

#define REG_OSP_IDRP_SET_IE3_HP_SHIFT                      4
#define REG_OSP_IDRP_SET_IE3_HP_SIZE                       1
#define REG_OSP_IDRP_SET_IE3_HP_MASK                       0x00000010

#define REG_OSP_IDRP_SET_IE3_TP_SHIFT                      3
#define REG_OSP_IDRP_SET_IE3_TP_SIZE                       1
#define REG_OSP_IDRP_SET_IE3_TP_MASK                       0x00000008

#define REG_OSP_IDRP_SET_IE3_COVER_R_SHIFT                 2
#define REG_OSP_IDRP_SET_IE3_COVER_R_SIZE                  1
#define REG_OSP_IDRP_SET_IE3_COVER_R_MASK                  0x00000004

#define REG_OSP_IDRP_SET_IE3_COVER_SHIFT                   0
#define REG_OSP_IDRP_SET_IE3_COVER_SIZE                    1
#define REG_OSP_IDRP_SET_IE3_COVER_MASK                    0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_SET_IE3_FIELD( pmuirq7, pmuirq6, pmuirq5, pmuirq4, pmuirq1, pmuirq0, cgc_det, cgc_i, gpio3_18_5, gpio3_18_4, gpio3_18_3, gpio3_18_2, gpio3_18_1, gpio3_18_0, gpio3_33_5, gpio3_33_4, gpio3_33_3, gpio3_33_2, gpio3_33_1, gpio3_33_0, ctr_mcu, rmc, ir, sp_sel, twl_depop, twl_mcu, hp, tp, cover_r, cover ) \
    (u32)( \
    ((u32)(pmuirq7) << REG_OSP_IDRP_SET_IE3_PMUIRQ7_SHIFT) | \
    ((u32)(pmuirq6) << REG_OSP_IDRP_SET_IE3_PMUIRQ6_SHIFT) | \
    ((u32)(pmuirq5) << REG_OSP_IDRP_SET_IE3_PMUIRQ5_SHIFT) | \
    ((u32)(pmuirq4) << REG_OSP_IDRP_SET_IE3_PMUIRQ4_SHIFT) | \
    ((u32)(pmuirq1) << REG_OSP_IDRP_SET_IE3_PMUIRQ1_SHIFT) | \
    ((u32)(pmuirq0) << REG_OSP_IDRP_SET_IE3_PMUIRQ0_SHIFT) | \
    ((u32)(cgc_det) << REG_OSP_IDRP_SET_IE3_CGC_DET_SHIFT) | \
    ((u32)(cgc_i) << REG_OSP_IDRP_SET_IE3_CGC_I_SHIFT) | \
    ((u32)(gpio3_18_5) << REG_OSP_IDRP_SET_IE3_GPIO3_18_5_SHIFT) | \
    ((u32)(gpio3_18_4) << REG_OSP_IDRP_SET_IE3_GPIO3_18_4_SHIFT) | \
    ((u32)(gpio3_18_3) << REG_OSP_IDRP_SET_IE3_GPIO3_18_3_SHIFT) | \
    ((u32)(gpio3_18_2) << REG_OSP_IDRP_SET_IE3_GPIO3_18_2_SHIFT) | \
    ((u32)(gpio3_18_1) << REG_OSP_IDRP_SET_IE3_GPIO3_18_1_SHIFT) | \
    ((u32)(gpio3_18_0) << REG_OSP_IDRP_SET_IE3_GPIO3_18_0_SHIFT) | \
    ((u32)(gpio3_33_5) << REG_OSP_IDRP_SET_IE3_GPIO3_33_5_SHIFT) | \
    ((u32)(gpio3_33_4) << REG_OSP_IDRP_SET_IE3_GPIO3_33_4_SHIFT) | \
    ((u32)(gpio3_33_3) << REG_OSP_IDRP_SET_IE3_GPIO3_33_3_SHIFT) | \
    ((u32)(gpio3_33_2) << REG_OSP_IDRP_SET_IE3_GPIO3_33_2_SHIFT) | \
    ((u32)(gpio3_33_1) << REG_OSP_IDRP_SET_IE3_GPIO3_33_1_SHIFT) | \
    ((u32)(gpio3_33_0) << REG_OSP_IDRP_SET_IE3_GPIO3_33_0_SHIFT) | \
    ((u32)(ctr_mcu) << REG_OSP_IDRP_SET_IE3_CTR_MCU_SHIFT) | \
    ((u32)(rmc) << REG_OSP_IDRP_SET_IE3_RMC_SHIFT) | \
    ((u32)(ir) << REG_OSP_IDRP_SET_IE3_IR_SHIFT) | \
    ((u32)(sp_sel) << REG_OSP_IDRP_SET_IE3_SP_SEL_SHIFT) | \
    ((u32)(twl_depop) << REG_OSP_IDRP_SET_IE3_TWL_DEPOP_SHIFT) | \
    ((u32)(twl_mcu) << REG_OSP_IDRP_SET_IE3_TWL_MCU_SHIFT) | \
    ((u32)(hp) << REG_OSP_IDRP_SET_IE3_HP_SHIFT) | \
    ((u32)(tp) << REG_OSP_IDRP_SET_IE3_TP_SHIFT) | \
    ((u32)(cover_r) << REG_OSP_IDRP_SET_IE3_COVER_R_SHIFT) | \
    ((u32)(cover) << REG_OSP_IDRP_SET_IE3_COVER_SHIFT))
#endif


/* IDRP_CLR_IE0 */

#define REG_OSP_IDRP_CLR_IE0_WDOG_SHIFT                    30
#define REG_OSP_IDRP_CLR_IE0_WDOG_SIZE                     1
#define REG_OSP_IDRP_CLR_IE0_WDOG_MASK                     0x40000000

#define REG_OSP_IDRP_CLR_IE0_TM_SHIFT                      29
#define REG_OSP_IDRP_CLR_IE0_TM_SIZE                       1
#define REG_OSP_IDRP_CLR_IE0_TM_MASK                       0x20000000

#define REG_OSP_IDRP_CLR_IE0_IPI15_SHIFT                   15
#define REG_OSP_IDRP_CLR_IE0_IPI15_SIZE                    1
#define REG_OSP_IDRP_CLR_IE0_IPI15_MASK                    0x00008000

#define REG_OSP_IDRP_CLR_IE0_IPI14_SHIFT                   14
#define REG_OSP_IDRP_CLR_IE0_IPI14_SIZE                    1
#define REG_OSP_IDRP_CLR_IE0_IPI14_MASK                    0x00004000

#define REG_OSP_IDRP_CLR_IE0_IPI13_SHIFT                   13
#define REG_OSP_IDRP_CLR_IE0_IPI13_SIZE                    1
#define REG_OSP_IDRP_CLR_IE0_IPI13_MASK                    0x00002000

#define REG_OSP_IDRP_CLR_IE0_IPI12_SHIFT                   12
#define REG_OSP_IDRP_CLR_IE0_IPI12_SIZE                    1
#define REG_OSP_IDRP_CLR_IE0_IPI12_MASK                    0x00001000

#define REG_OSP_IDRP_CLR_IE0_IPI11_SHIFT                   11
#define REG_OSP_IDRP_CLR_IE0_IPI11_SIZE                    1
#define REG_OSP_IDRP_CLR_IE0_IPI11_MASK                    0x00000800

#define REG_OSP_IDRP_CLR_IE0_IPI10_SHIFT                   10
#define REG_OSP_IDRP_CLR_IE0_IPI10_SIZE                    1
#define REG_OSP_IDRP_CLR_IE0_IPI10_MASK                    0x00000400

#define REG_OSP_IDRP_CLR_IE0_IPI9_SHIFT                    9
#define REG_OSP_IDRP_CLR_IE0_IPI9_SIZE                     1
#define REG_OSP_IDRP_CLR_IE0_IPI9_MASK                     0x00000200

#define REG_OSP_IDRP_CLR_IE0_IPI8_SHIFT                    8
#define REG_OSP_IDRP_CLR_IE0_IPI8_SIZE                     1
#define REG_OSP_IDRP_CLR_IE0_IPI8_MASK                     0x00000100

#define REG_OSP_IDRP_CLR_IE0_IPI7_SHIFT                    7
#define REG_OSP_IDRP_CLR_IE0_IPI7_SIZE                     1
#define REG_OSP_IDRP_CLR_IE0_IPI7_MASK                     0x00000080

#define REG_OSP_IDRP_CLR_IE0_IPI6_SHIFT                    6
#define REG_OSP_IDRP_CLR_IE0_IPI6_SIZE                     1
#define REG_OSP_IDRP_CLR_IE0_IPI6_MASK                     0x00000040

#define REG_OSP_IDRP_CLR_IE0_IPI5_SHIFT                    5
#define REG_OSP_IDRP_CLR_IE0_IPI5_SIZE                     1
#define REG_OSP_IDRP_CLR_IE0_IPI5_MASK                     0x00000020

#define REG_OSP_IDRP_CLR_IE0_IPI4_SHIFT                    4
#define REG_OSP_IDRP_CLR_IE0_IPI4_SIZE                     1
#define REG_OSP_IDRP_CLR_IE0_IPI4_MASK                     0x00000010

#define REG_OSP_IDRP_CLR_IE0_IPI3_SHIFT                    3
#define REG_OSP_IDRP_CLR_IE0_IPI3_SIZE                     1
#define REG_OSP_IDRP_CLR_IE0_IPI3_MASK                     0x00000008

#define REG_OSP_IDRP_CLR_IE0_IPI2_SHIFT                    2
#define REG_OSP_IDRP_CLR_IE0_IPI2_SIZE                     1
#define REG_OSP_IDRP_CLR_IE0_IPI2_MASK                     0x00000004

#define REG_OSP_IDRP_CLR_IE0_IPI1_SHIFT                    1
#define REG_OSP_IDRP_CLR_IE0_IPI1_SIZE                     1
#define REG_OSP_IDRP_CLR_IE0_IPI1_MASK                     0x00000002

#define REG_OSP_IDRP_CLR_IE0_IPI0_SHIFT                    0
#define REG_OSP_IDRP_CLR_IE0_IPI0_SIZE                     1
#define REG_OSP_IDRP_CLR_IE0_IPI0_MASK                     0x00000001

#define REG_OSP_IDRP_CLR_IE0_IPI_ALL_SHIFT                 0
#define REG_OSP_IDRP_CLR_IE0_IPI_ALL_SIZE                  16
#define REG_OSP_IDRP_CLR_IE0_IPI_ALL_MASK                  0x0000ffff

#ifndef SDK_ASM
#define REG_OSP_IDRP_CLR_IE0_FIELD( wdog, tm, ipi15, ipi14, ipi13, ipi12, ipi11, ipi10, ipi9, ipi8, ipi7, ipi6, ipi5, ipi4, ipi3, ipi2, ipi1, ipi0, ipi_all ) \
    (u32)( \
    ((u32)(wdog) << REG_OSP_IDRP_CLR_IE0_WDOG_SHIFT) | \
    ((u32)(tm) << REG_OSP_IDRP_CLR_IE0_TM_SHIFT) | \
    ((u32)(ipi15) << REG_OSP_IDRP_CLR_IE0_IPI15_SHIFT) | \
    ((u32)(ipi14) << REG_OSP_IDRP_CLR_IE0_IPI14_SHIFT) | \
    ((u32)(ipi13) << REG_OSP_IDRP_CLR_IE0_IPI13_SHIFT) | \
    ((u32)(ipi12) << REG_OSP_IDRP_CLR_IE0_IPI12_SHIFT) | \
    ((u32)(ipi11) << REG_OSP_IDRP_CLR_IE0_IPI11_SHIFT) | \
    ((u32)(ipi10) << REG_OSP_IDRP_CLR_IE0_IPI10_SHIFT) | \
    ((u32)(ipi9) << REG_OSP_IDRP_CLR_IE0_IPI9_SHIFT) | \
    ((u32)(ipi8) << REG_OSP_IDRP_CLR_IE0_IPI8_SHIFT) | \
    ((u32)(ipi7) << REG_OSP_IDRP_CLR_IE0_IPI7_SHIFT) | \
    ((u32)(ipi6) << REG_OSP_IDRP_CLR_IE0_IPI6_SHIFT) | \
    ((u32)(ipi5) << REG_OSP_IDRP_CLR_IE0_IPI5_SHIFT) | \
    ((u32)(ipi4) << REG_OSP_IDRP_CLR_IE0_IPI4_SHIFT) | \
    ((u32)(ipi3) << REG_OSP_IDRP_CLR_IE0_IPI3_SHIFT) | \
    ((u32)(ipi2) << REG_OSP_IDRP_CLR_IE0_IPI2_SHIFT) | \
    ((u32)(ipi1) << REG_OSP_IDRP_CLR_IE0_IPI1_SHIFT) | \
    ((u32)(ipi0) << REG_OSP_IDRP_CLR_IE0_IPI0_SHIFT) | \
    ((u32)(ipi_all) << REG_OSP_IDRP_CLR_IE0_IPI_ALL_SHIFT))
#endif


/* IDRP_CLR_IE1 */

#define REG_OSP_IDRP_CLR_IE1_XDMA_ABT_SHIFT                25
#define REG_OSP_IDRP_CLR_IE1_XDMA_ABT_SIZE                 1
#define REG_OSP_IDRP_CLR_IE1_XDMA_ABT_MASK                 0x02000000

#define REG_OSP_IDRP_CLR_IE1_XDMA7_SHIFT                   24
#define REG_OSP_IDRP_CLR_IE1_XDMA7_SIZE                    1
#define REG_OSP_IDRP_CLR_IE1_XDMA7_MASK                    0x01000000

#define REG_OSP_IDRP_CLR_IE1_XDMA6_SHIFT                   22
#define REG_OSP_IDRP_CLR_IE1_XDMA6_SIZE                    1
#define REG_OSP_IDRP_CLR_IE1_XDMA6_MASK                    0x00400000

#define REG_OSP_IDRP_CLR_IE1_XDMA5_SHIFT                   21
#define REG_OSP_IDRP_CLR_IE1_XDMA5_SIZE                    1
#define REG_OSP_IDRP_CLR_IE1_XDMA5_MASK                    0x00200000

#define REG_OSP_IDRP_CLR_IE1_XDMA4_SHIFT                   20
#define REG_OSP_IDRP_CLR_IE1_XDMA4_SIZE                    1
#define REG_OSP_IDRP_CLR_IE1_XDMA4_MASK                    0x00100000

#define REG_OSP_IDRP_CLR_IE1_XDMA3_SHIFT                   19
#define REG_OSP_IDRP_CLR_IE1_XDMA3_SIZE                    1
#define REG_OSP_IDRP_CLR_IE1_XDMA3_MASK                    0x00080000

#define REG_OSP_IDRP_CLR_IE1_XDMA2_SHIFT                   18
#define REG_OSP_IDRP_CLR_IE1_XDMA2_SIZE                    1
#define REG_OSP_IDRP_CLR_IE1_XDMA2_MASK                    0x00040000

#define REG_OSP_IDRP_CLR_IE1_XDMA1_SHIFT                   17
#define REG_OSP_IDRP_CLR_IE1_XDMA1_SIZE                    1
#define REG_OSP_IDRP_CLR_IE1_XDMA1_MASK                    0x00020000

#define REG_OSP_IDRP_CLR_IE1_XDMA0_SHIFT                   16
#define REG_OSP_IDRP_CLR_IE1_XDMA0_SIZE                    1
#define REG_OSP_IDRP_CLR_IE1_XDMA0_MASK                    0x00010000

#define REG_OSP_IDRP_CLR_IE1_GPU_P3D_SHIFT                 13
#define REG_OSP_IDRP_CLR_IE1_GPU_P3D_SIZE                  1
#define REG_OSP_IDRP_CLR_IE1_GPU_P3D_MASK                  0x00002000

#define REG_OSP_IDRP_CLR_IE1_GPU_PPF_SHIFT                 12
#define REG_OSP_IDRP_CLR_IE1_GPU_PPF_SIZE                  1
#define REG_OSP_IDRP_CLR_IE1_GPU_PPF_MASK                  0x00001000

#define REG_OSP_IDRP_CLR_IE1_GPU_PDC1_SHIFT                11
#define REG_OSP_IDRP_CLR_IE1_GPU_PDC1_SIZE                 1
#define REG_OSP_IDRP_CLR_IE1_GPU_PDC1_MASK                 0x00000800

#define REG_OSP_IDRP_CLR_IE1_GPU_PDC0_SHIFT                10
#define REG_OSP_IDRP_CLR_IE1_GPU_PDC0_SIZE                 1
#define REG_OSP_IDRP_CLR_IE1_GPU_PDC0_MASK                 0x00000400

#define REG_OSP_IDRP_CLR_IE1_GPU_PSC1_SHIFT                9
#define REG_OSP_IDRP_CLR_IE1_GPU_PSC1_SIZE                 1
#define REG_OSP_IDRP_CLR_IE1_GPU_PSC1_MASK                 0x00000200

#define REG_OSP_IDRP_CLR_IE1_GPU_PSC0_SHIFT                8
#define REG_OSP_IDRP_CLR_IE1_GPU_PSC0_SIZE                 1
#define REG_OSP_IDRP_CLR_IE1_GPU_PSC0_MASK                 0x00000100

#define REG_OSP_IDRP_CLR_IE1_DBG_SPI_SHIFT                 4
#define REG_OSP_IDRP_CLR_IE1_DBG_SPI_SIZE                  1
#define REG_OSP_IDRP_CLR_IE1_DBG_SPI_MASK                  0x00000010

#define REG_OSP_IDRP_CLR_IE1_J1_TX_SHIFT                   3
#define REG_OSP_IDRP_CLR_IE1_J1_TX_SIZE                    1
#define REG_OSP_IDRP_CLR_IE1_J1_TX_MASK                    0x00000008

#define REG_OSP_IDRP_CLR_IE1_J1_RX_SHIFT                   2
#define REG_OSP_IDRP_CLR_IE1_J1_RX_SIZE                    1
#define REG_OSP_IDRP_CLR_IE1_J1_RX_MASK                    0x00000004

#define REG_OSP_IDRP_CLR_IE1_J0_TX_SHIFT                   1
#define REG_OSP_IDRP_CLR_IE1_J0_TX_SIZE                    1
#define REG_OSP_IDRP_CLR_IE1_J0_TX_MASK                    0x00000002

#define REG_OSP_IDRP_CLR_IE1_J0_RX_SHIFT                   0
#define REG_OSP_IDRP_CLR_IE1_J0_RX_SIZE                    1
#define REG_OSP_IDRP_CLR_IE1_J0_RX_MASK                    0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CLR_IE1_FIELD( xdma_abt, xdma7, xdma6, xdma5, xdma4, xdma3, xdma2, xdma1, xdma0, gpu_p3d, gpu_ppf, gpu_pdc1, gpu_pdc0, gpu_psc1, gpu_psc0, dbg_spi, j1_tx, j1_rx, j0_tx, j0_rx ) \
    (u32)( \
    ((u32)(xdma_abt) << REG_OSP_IDRP_CLR_IE1_XDMA_ABT_SHIFT) | \
    ((u32)(xdma7) << REG_OSP_IDRP_CLR_IE1_XDMA7_SHIFT) | \
    ((u32)(xdma6) << REG_OSP_IDRP_CLR_IE1_XDMA6_SHIFT) | \
    ((u32)(xdma5) << REG_OSP_IDRP_CLR_IE1_XDMA5_SHIFT) | \
    ((u32)(xdma4) << REG_OSP_IDRP_CLR_IE1_XDMA4_SHIFT) | \
    ((u32)(xdma3) << REG_OSP_IDRP_CLR_IE1_XDMA3_SHIFT) | \
    ((u32)(xdma2) << REG_OSP_IDRP_CLR_IE1_XDMA2_SHIFT) | \
    ((u32)(xdma1) << REG_OSP_IDRP_CLR_IE1_XDMA1_SHIFT) | \
    ((u32)(xdma0) << REG_OSP_IDRP_CLR_IE1_XDMA0_SHIFT) | \
    ((u32)(gpu_p3d) << REG_OSP_IDRP_CLR_IE1_GPU_P3D_SHIFT) | \
    ((u32)(gpu_ppf) << REG_OSP_IDRP_CLR_IE1_GPU_PPF_SHIFT) | \
    ((u32)(gpu_pdc1) << REG_OSP_IDRP_CLR_IE1_GPU_PDC1_SHIFT) | \
    ((u32)(gpu_pdc0) << REG_OSP_IDRP_CLR_IE1_GPU_PDC0_SHIFT) | \
    ((u32)(gpu_psc1) << REG_OSP_IDRP_CLR_IE1_GPU_PSC1_SHIFT) | \
    ((u32)(gpu_psc0) << REG_OSP_IDRP_CLR_IE1_GPU_PSC0_SHIFT) | \
    ((u32)(dbg_spi) << REG_OSP_IDRP_CLR_IE1_DBG_SPI_SHIFT) | \
    ((u32)(j1_tx) << REG_OSP_IDRP_CLR_IE1_J1_TX_SHIFT) | \
    ((u32)(j1_rx) << REG_OSP_IDRP_CLR_IE1_J1_RX_SHIFT) | \
    ((u32)(j0_tx) << REG_OSP_IDRP_CLR_IE1_J0_TX_SHIFT) | \
    ((u32)(j0_rx) << REG_OSP_IDRP_CLR_IE1_J0_RX_SHIFT))
#endif


/* IDRP_CLR_IE2 */

#define REG_OSP_IDRP_CLR_IE2_DS_WL_SHIFT                   31
#define REG_OSP_IDRP_CLR_IE2_DS_WL_SIZE                    1
#define REG_OSP_IDRP_CLR_IE2_DS_WL_MASK                    0x80000000

#define REG_OSP_IDRP_CLR_IE2_I2C3_SHIFT                    28
#define REG_OSP_IDRP_CLR_IE2_I2C3_SIZE                     1
#define REG_OSP_IDRP_CLR_IE2_I2C3_MASK                     0x10000000

#define REG_OSP_IDRP_CLR_IE2_KEY_SHIFT                     27
#define REG_OSP_IDRP_CLR_IE2_KEY_SIZE                      1
#define REG_OSP_IDRP_CLR_IE2_KEY_MASK                      0x08000000

#define REG_OSP_IDRP_CLR_IE2_MIC_SHIFT                     26
#define REG_OSP_IDRP_CLR_IE2_MIC_SIZE                      1
#define REG_OSP_IDRP_CLR_IE2_MIC_MASK                      0x04000000

#define REG_OSP_IDRP_CLR_IE2_PDN_LGY_SHIFT                 25
#define REG_OSP_IDRP_CLR_IE2_PDN_LGY_SIZE                  1
#define REG_OSP_IDRP_CLR_IE2_PDN_LGY_MASK                  0x02000000

#define REG_OSP_IDRP_CLR_IE2_PDN_WAKE_SHIFT                24
#define REG_OSP_IDRP_CLR_IE2_PDN_WAKE_SIZE                 1
#define REG_OSP_IDRP_CLR_IE2_PDN_WAKE_MASK                 0x01000000

#define REG_OSP_IDRP_CLR_IE2_SPI2_SHIFT                    23
#define REG_OSP_IDRP_CLR_IE2_SPI2_SIZE                     1
#define REG_OSP_IDRP_CLR_IE2_SPI2_MASK                     0x00800000

#define REG_OSP_IDRP_CLR_IE2_SPI1_SHIFT                    22
#define REG_OSP_IDRP_CLR_IE2_SPI1_SIZE                     1
#define REG_OSP_IDRP_CLR_IE2_SPI1_MASK                     0x00400000

#define REG_OSP_IDRP_CLR_IE2_I2C2_SHIFT                    21
#define REG_OSP_IDRP_CLR_IE2_I2C2_SIZE                     1
#define REG_OSP_IDRP_CLR_IE2_I2C2_MASK                     0x00200000

#define REG_OSP_IDRP_CLR_IE2_I2C1_SHIFT                    20
#define REG_OSP_IDRP_CLR_IE2_I2C1_SIZE                     1
#define REG_OSP_IDRP_CLR_IE2_I2C1_MASK                     0x00100000

#define REG_OSP_IDRP_CLR_IE2_PXI_RX_SHIFT                  19
#define REG_OSP_IDRP_CLR_IE2_PXI_RX_SIZE                   1
#define REG_OSP_IDRP_CLR_IE2_PXI_RX_MASK                   0x00080000

#define REG_OSP_IDRP_CLR_IE2_PXI_TX_SHIFT                  18
#define REG_OSP_IDRP_CLR_IE2_PXI_TX_SIZE                   1
#define REG_OSP_IDRP_CLR_IE2_PXI_TX_MASK                   0x00040000

#define REG_OSP_IDRP_CLR_IE2_CPU1_SHIFT                    17
#define REG_OSP_IDRP_CLR_IE2_CPU1_SIZE                     1
#define REG_OSP_IDRP_CLR_IE2_CPU1_MASK                     0x00020000

#define REG_OSP_IDRP_CLR_IE2_CPU0_SHIFT                    16
#define REG_OSP_IDRP_CLR_IE2_CPU0_SIZE                     1
#define REG_OSP_IDRP_CLR_IE2_CPU0_MASK                     0x00010000

#define REG_OSP_IDRP_CLR_IE2_SCLR2_SHIFT                   13
#define REG_OSP_IDRP_CLR_IE2_SCLR2_SIZE                    1
#define REG_OSP_IDRP_CLR_IE2_SCLR2_MASK                    0x00002000

#define REG_OSP_IDRP_CLR_IE2_SCLR1_SHIFT                   12
#define REG_OSP_IDRP_CLR_IE2_SCLR1_SIZE                    1
#define REG_OSP_IDRP_CLR_IE2_SCLR1_MASK                    0x00001000

#define REG_OSP_IDRP_CLR_IE2_YUV2RGB_SHIFT                 11
#define REG_OSP_IDRP_CLR_IE2_YUV2RGB_SIZE                  1
#define REG_OSP_IDRP_CLR_IE2_YUV2RGB_MASK                  0x00000800

#define REG_OSP_IDRP_CLR_IE2_DSP_SHIFT                     10
#define REG_OSP_IDRP_CLR_IE2_DSP_SIZE                      1
#define REG_OSP_IDRP_CLR_IE2_DSP_MASK                      0x00000400

#define REG_OSP_IDRP_CLR_IE2_CAM2_SHIFT                    9
#define REG_OSP_IDRP_CLR_IE2_CAM2_SIZE                     1
#define REG_OSP_IDRP_CLR_IE2_CAM2_MASK                     0x00000200

#define REG_OSP_IDRP_CLR_IE2_CAM1_SHIFT                    8
#define REG_OSP_IDRP_CLR_IE2_CAM1_SIZE                     1
#define REG_OSP_IDRP_CLR_IE2_CAM1_MASK                     0x00000100

#define REG_OSP_IDRP_CLR_IE2_LGC_DET_SHIFT                 6
#define REG_OSP_IDRP_CLR_IE2_LGC_DET_SIZE                  1
#define REG_OSP_IDRP_CLR_IE2_LGC_DET_MASK                  0x00000040

#define REG_OSP_IDRP_CLR_IE2_LGC_I_SHIFT                   5
#define REG_OSP_IDRP_CLR_IE2_LGC_I_SIZE                    1
#define REG_OSP_IDRP_CLR_IE2_LGC_I_MASK                    0x00000020

#define REG_OSP_IDRP_CLR_IE2_LMC_SHIFT                     4
#define REG_OSP_IDRP_CLR_IE2_LMC_SIZE                      1
#define REG_OSP_IDRP_CLR_IE2_LMC_MASK                      0x00000010

#define REG_OSP_IDRP_CLR_IE2_SD3_A_SHIFT                   3
#define REG_OSP_IDRP_CLR_IE2_SD3_A_SIZE                    1
#define REG_OSP_IDRP_CLR_IE2_SD3_A_MASK                    0x00000008

#define REG_OSP_IDRP_CLR_IE2_SD3_SHIFT                     2
#define REG_OSP_IDRP_CLR_IE2_SD3_SIZE                      1
#define REG_OSP_IDRP_CLR_IE2_SD3_MASK                      0x00000004

#define REG_OSP_IDRP_CLR_IE2_SD2_A_SHIFT                   1
#define REG_OSP_IDRP_CLR_IE2_SD2_A_SIZE                    1
#define REG_OSP_IDRP_CLR_IE2_SD2_A_MASK                    0x00000002

#define REG_OSP_IDRP_CLR_IE2_SD2_SHIFT                     0
#define REG_OSP_IDRP_CLR_IE2_SD2_SIZE                      1
#define REG_OSP_IDRP_CLR_IE2_SD2_MASK                      0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CLR_IE2_FIELD( ds_wl, i2c3, key, mic, pdn_lgy, pdn_wake, spi2, spi1, i2c2, i2c1, pxi_rx, pxi_tx, cpu1, cpu0, sclr2, sclr1, yuv2rgb, dsp, cam2, cam1, lgc_det, lgc_i, lmc, sd3_a, sd3, sd2_a, sd2 ) \
    (u32)( \
    ((u32)(ds_wl) << REG_OSP_IDRP_CLR_IE2_DS_WL_SHIFT) | \
    ((u32)(i2c3) << REG_OSP_IDRP_CLR_IE2_I2C3_SHIFT) | \
    ((u32)(key) << REG_OSP_IDRP_CLR_IE2_KEY_SHIFT) | \
    ((u32)(mic) << REG_OSP_IDRP_CLR_IE2_MIC_SHIFT) | \
    ((u32)(pdn_lgy) << REG_OSP_IDRP_CLR_IE2_PDN_LGY_SHIFT) | \
    ((u32)(pdn_wake) << REG_OSP_IDRP_CLR_IE2_PDN_WAKE_SHIFT) | \
    ((u32)(spi2) << REG_OSP_IDRP_CLR_IE2_SPI2_SHIFT) | \
    ((u32)(spi1) << REG_OSP_IDRP_CLR_IE2_SPI1_SHIFT) | \
    ((u32)(i2c2) << REG_OSP_IDRP_CLR_IE2_I2C2_SHIFT) | \
    ((u32)(i2c1) << REG_OSP_IDRP_CLR_IE2_I2C1_SHIFT) | \
    ((u32)(pxi_rx) << REG_OSP_IDRP_CLR_IE2_PXI_RX_SHIFT) | \
    ((u32)(pxi_tx) << REG_OSP_IDRP_CLR_IE2_PXI_TX_SHIFT) | \
    ((u32)(cpu1) << REG_OSP_IDRP_CLR_IE2_CPU1_SHIFT) | \
    ((u32)(cpu0) << REG_OSP_IDRP_CLR_IE2_CPU0_SHIFT) | \
    ((u32)(sclr2) << REG_OSP_IDRP_CLR_IE2_SCLR2_SHIFT) | \
    ((u32)(sclr1) << REG_OSP_IDRP_CLR_IE2_SCLR1_SHIFT) | \
    ((u32)(yuv2rgb) << REG_OSP_IDRP_CLR_IE2_YUV2RGB_SHIFT) | \
    ((u32)(dsp) << REG_OSP_IDRP_CLR_IE2_DSP_SHIFT) | \
    ((u32)(cam2) << REG_OSP_IDRP_CLR_IE2_CAM2_SHIFT) | \
    ((u32)(cam1) << REG_OSP_IDRP_CLR_IE2_CAM1_SHIFT) | \
    ((u32)(lgc_det) << REG_OSP_IDRP_CLR_IE2_LGC_DET_SHIFT) | \
    ((u32)(lgc_i) << REG_OSP_IDRP_CLR_IE2_LGC_I_SHIFT) | \
    ((u32)(lmc) << REG_OSP_IDRP_CLR_IE2_LMC_SHIFT) | \
    ((u32)(sd3_a) << REG_OSP_IDRP_CLR_IE2_SD3_A_SHIFT) | \
    ((u32)(sd3) << REG_OSP_IDRP_CLR_IE2_SD3_SHIFT) | \
    ((u32)(sd2_a) << REG_OSP_IDRP_CLR_IE2_SD2_A_SHIFT) | \
    ((u32)(sd2) << REG_OSP_IDRP_CLR_IE2_SD2_SHIFT))
#endif


/* IDRP_CLR_IE3 */

#define REG_OSP_IDRP_CLR_IE3_PMUIRQ7_SHIFT                 29
#define REG_OSP_IDRP_CLR_IE3_PMUIRQ7_SIZE                  1
#define REG_OSP_IDRP_CLR_IE3_PMUIRQ7_MASK                  0x20000000

#define REG_OSP_IDRP_CLR_IE3_PMUIRQ6_SHIFT                 28
#define REG_OSP_IDRP_CLR_IE3_PMUIRQ6_SIZE                  1
#define REG_OSP_IDRP_CLR_IE3_PMUIRQ6_MASK                  0x10000000

#define REG_OSP_IDRP_CLR_IE3_PMUIRQ5_SHIFT                 27
#define REG_OSP_IDRP_CLR_IE3_PMUIRQ5_SIZE                  1
#define REG_OSP_IDRP_CLR_IE3_PMUIRQ5_MASK                  0x08000000

#define REG_OSP_IDRP_CLR_IE3_PMUIRQ4_SHIFT                 26
#define REG_OSP_IDRP_CLR_IE3_PMUIRQ4_SIZE                  1
#define REG_OSP_IDRP_CLR_IE3_PMUIRQ4_MASK                  0x04000000

#define REG_OSP_IDRP_CLR_IE3_PMUIRQ1_SHIFT                 25
#define REG_OSP_IDRP_CLR_IE3_PMUIRQ1_SIZE                  1
#define REG_OSP_IDRP_CLR_IE3_PMUIRQ1_MASK                  0x02000000

#define REG_OSP_IDRP_CLR_IE3_PMUIRQ0_SHIFT                 24
#define REG_OSP_IDRP_CLR_IE3_PMUIRQ0_SIZE                  1
#define REG_OSP_IDRP_CLR_IE3_PMUIRQ0_MASK                  0x01000000

#define REG_OSP_IDRP_CLR_IE3_CGC_DET_SHIFT                 21
#define REG_OSP_IDRP_CLR_IE3_CGC_DET_SIZE                  1
#define REG_OSP_IDRP_CLR_IE3_CGC_DET_MASK                  0x00200000

#define REG_OSP_IDRP_CLR_IE3_CGC_I_SHIFT                   20
#define REG_OSP_IDRP_CLR_IE3_CGC_I_SIZE                    1
#define REG_OSP_IDRP_CLR_IE3_CGC_I_MASK                    0x00100000

#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_5_SHIFT              19
#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_5_SIZE               1
#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_5_MASK               0x00080000

#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_4_SHIFT              18
#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_4_SIZE               1
#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_4_MASK               0x00040000

#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_3_SHIFT              17
#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_3_SIZE               1
#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_3_MASK               0x00020000

#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_2_SHIFT              16
#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_2_SIZE               1
#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_2_MASK               0x00010000

#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_1_SHIFT              15
#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_1_SIZE               1
#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_1_MASK               0x00008000

#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_0_SHIFT              14
#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_0_SIZE               1
#define REG_OSP_IDRP_CLR_IE3_GPIO3_18_0_MASK               0x00004000

#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_5_SHIFT              13
#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_5_SIZE               1
#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_5_MASK               0x00002000

#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_4_SHIFT              12
#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_4_SIZE               1
#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_4_MASK               0x00001000

#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_3_SHIFT              11
#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_3_SIZE               1
#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_3_MASK               0x00000800

#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_2_SHIFT              10
#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_2_SIZE               1
#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_2_MASK               0x00000400

#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_1_SHIFT              9
#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_1_SIZE               1
#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_1_MASK               0x00000200

#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_0_SHIFT              8
#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_0_SIZE               1
#define REG_OSP_IDRP_CLR_IE3_GPIO3_33_0_MASK               0x00000100

#define REG_OSP_IDRP_CLR_IE3_CTR_MCU_SHIFT                 17
#define REG_OSP_IDRP_CLR_IE3_CTR_MCU_SIZE                  1
#define REG_OSP_IDRP_CLR_IE3_CTR_MCU_MASK                  0x00020000

#define REG_OSP_IDRP_CLR_IE3_RMC_SHIFT                     16
#define REG_OSP_IDRP_CLR_IE3_RMC_SIZE                      1
#define REG_OSP_IDRP_CLR_IE3_RMC_MASK                      0x00010000

#define REG_OSP_IDRP_CLR_IE3_IR_SHIFT                      10
#define REG_OSP_IDRP_CLR_IE3_IR_SIZE                       1
#define REG_OSP_IDRP_CLR_IE3_IR_MASK                       0x00000400

#define REG_OSP_IDRP_CLR_IE3_SP_SEL_SHIFT                  8
#define REG_OSP_IDRP_CLR_IE3_SP_SEL_SIZE                   1
#define REG_OSP_IDRP_CLR_IE3_SP_SEL_MASK                   0x00000100

#define REG_OSP_IDRP_CLR_IE3_TWL_DEPOP_SHIFT               6
#define REG_OSP_IDRP_CLR_IE3_TWL_DEPOP_SIZE                1
#define REG_OSP_IDRP_CLR_IE3_TWL_DEPOP_MASK                0x00000040

#define REG_OSP_IDRP_CLR_IE3_TWL_MCU_SHIFT                 5
#define REG_OSP_IDRP_CLR_IE3_TWL_MCU_SIZE                  1
#define REG_OSP_IDRP_CLR_IE3_TWL_MCU_MASK                  0x00000020

#define REG_OSP_IDRP_CLR_IE3_HP_SHIFT                      4
#define REG_OSP_IDRP_CLR_IE3_HP_SIZE                       1
#define REG_OSP_IDRP_CLR_IE3_HP_MASK                       0x00000010

#define REG_OSP_IDRP_CLR_IE3_TP_SHIFT                      3
#define REG_OSP_IDRP_CLR_IE3_TP_SIZE                       1
#define REG_OSP_IDRP_CLR_IE3_TP_MASK                       0x00000008

#define REG_OSP_IDRP_CLR_IE3_COVER_R_SHIFT                 2
#define REG_OSP_IDRP_CLR_IE3_COVER_R_SIZE                  1
#define REG_OSP_IDRP_CLR_IE3_COVER_R_MASK                  0x00000004

#define REG_OSP_IDRP_CLR_IE3_COVER_SHIFT                   0
#define REG_OSP_IDRP_CLR_IE3_COVER_SIZE                    1
#define REG_OSP_IDRP_CLR_IE3_COVER_MASK                    0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CLR_IE3_FIELD( pmuirq7, pmuirq6, pmuirq5, pmuirq4, pmuirq1, pmuirq0, cgc_det, cgc_i, gpio3_18_5, gpio3_18_4, gpio3_18_3, gpio3_18_2, gpio3_18_1, gpio3_18_0, gpio3_33_5, gpio3_33_4, gpio3_33_3, gpio3_33_2, gpio3_33_1, gpio3_33_0, ctr_mcu, rmc, ir, sp_sel, twl_depop, twl_mcu, hp, tp, cover_r, cover ) \
    (u32)( \
    ((u32)(pmuirq7) << REG_OSP_IDRP_CLR_IE3_PMUIRQ7_SHIFT) | \
    ((u32)(pmuirq6) << REG_OSP_IDRP_CLR_IE3_PMUIRQ6_SHIFT) | \
    ((u32)(pmuirq5) << REG_OSP_IDRP_CLR_IE3_PMUIRQ5_SHIFT) | \
    ((u32)(pmuirq4) << REG_OSP_IDRP_CLR_IE3_PMUIRQ4_SHIFT) | \
    ((u32)(pmuirq1) << REG_OSP_IDRP_CLR_IE3_PMUIRQ1_SHIFT) | \
    ((u32)(pmuirq0) << REG_OSP_IDRP_CLR_IE3_PMUIRQ0_SHIFT) | \
    ((u32)(cgc_det) << REG_OSP_IDRP_CLR_IE3_CGC_DET_SHIFT) | \
    ((u32)(cgc_i) << REG_OSP_IDRP_CLR_IE3_CGC_I_SHIFT) | \
    ((u32)(gpio3_18_5) << REG_OSP_IDRP_CLR_IE3_GPIO3_18_5_SHIFT) | \
    ((u32)(gpio3_18_4) << REG_OSP_IDRP_CLR_IE3_GPIO3_18_4_SHIFT) | \
    ((u32)(gpio3_18_3) << REG_OSP_IDRP_CLR_IE3_GPIO3_18_3_SHIFT) | \
    ((u32)(gpio3_18_2) << REG_OSP_IDRP_CLR_IE3_GPIO3_18_2_SHIFT) | \
    ((u32)(gpio3_18_1) << REG_OSP_IDRP_CLR_IE3_GPIO3_18_1_SHIFT) | \
    ((u32)(gpio3_18_0) << REG_OSP_IDRP_CLR_IE3_GPIO3_18_0_SHIFT) | \
    ((u32)(gpio3_33_5) << REG_OSP_IDRP_CLR_IE3_GPIO3_33_5_SHIFT) | \
    ((u32)(gpio3_33_4) << REG_OSP_IDRP_CLR_IE3_GPIO3_33_4_SHIFT) | \
    ((u32)(gpio3_33_3) << REG_OSP_IDRP_CLR_IE3_GPIO3_33_3_SHIFT) | \
    ((u32)(gpio3_33_2) << REG_OSP_IDRP_CLR_IE3_GPIO3_33_2_SHIFT) | \
    ((u32)(gpio3_33_1) << REG_OSP_IDRP_CLR_IE3_GPIO3_33_1_SHIFT) | \
    ((u32)(gpio3_33_0) << REG_OSP_IDRP_CLR_IE3_GPIO3_33_0_SHIFT) | \
    ((u32)(ctr_mcu) << REG_OSP_IDRP_CLR_IE3_CTR_MCU_SHIFT) | \
    ((u32)(rmc) << REG_OSP_IDRP_CLR_IE3_RMC_SHIFT) | \
    ((u32)(ir) << REG_OSP_IDRP_CLR_IE3_IR_SHIFT) | \
    ((u32)(sp_sel) << REG_OSP_IDRP_CLR_IE3_SP_SEL_SHIFT) | \
    ((u32)(twl_depop) << REG_OSP_IDRP_CLR_IE3_TWL_DEPOP_SHIFT) | \
    ((u32)(twl_mcu) << REG_OSP_IDRP_CLR_IE3_TWL_MCU_SHIFT) | \
    ((u32)(hp) << REG_OSP_IDRP_CLR_IE3_HP_SHIFT) | \
    ((u32)(tp) << REG_OSP_IDRP_CLR_IE3_TP_SHIFT) | \
    ((u32)(cover_r) << REG_OSP_IDRP_CLR_IE3_COVER_R_SHIFT) | \
    ((u32)(cover) << REG_OSP_IDRP_CLR_IE3_COVER_SHIFT))
#endif


/* IDRP_SET_PND0 */

#define REG_OSP_IDRP_SET_PND0_WDOG_SHIFT                   30
#define REG_OSP_IDRP_SET_PND0_WDOG_SIZE                    1
#define REG_OSP_IDRP_SET_PND0_WDOG_MASK                    0x40000000

#define REG_OSP_IDRP_SET_PND0_TM_SHIFT                     29
#define REG_OSP_IDRP_SET_PND0_TM_SIZE                      1
#define REG_OSP_IDRP_SET_PND0_TM_MASK                      0x20000000

#define REG_OSP_IDRP_SET_PND0_IPI15_SHIFT                  15
#define REG_OSP_IDRP_SET_PND0_IPI15_SIZE                   1
#define REG_OSP_IDRP_SET_PND0_IPI15_MASK                   0x00008000

#define REG_OSP_IDRP_SET_PND0_IPI14_SHIFT                  14
#define REG_OSP_IDRP_SET_PND0_IPI14_SIZE                   1
#define REG_OSP_IDRP_SET_PND0_IPI14_MASK                   0x00004000

#define REG_OSP_IDRP_SET_PND0_IPI13_SHIFT                  13
#define REG_OSP_IDRP_SET_PND0_IPI13_SIZE                   1
#define REG_OSP_IDRP_SET_PND0_IPI13_MASK                   0x00002000

#define REG_OSP_IDRP_SET_PND0_IPI12_SHIFT                  12
#define REG_OSP_IDRP_SET_PND0_IPI12_SIZE                   1
#define REG_OSP_IDRP_SET_PND0_IPI12_MASK                   0x00001000

#define REG_OSP_IDRP_SET_PND0_IPI11_SHIFT                  11
#define REG_OSP_IDRP_SET_PND0_IPI11_SIZE                   1
#define REG_OSP_IDRP_SET_PND0_IPI11_MASK                   0x00000800

#define REG_OSP_IDRP_SET_PND0_IPI10_SHIFT                  10
#define REG_OSP_IDRP_SET_PND0_IPI10_SIZE                   1
#define REG_OSP_IDRP_SET_PND0_IPI10_MASK                   0x00000400

#define REG_OSP_IDRP_SET_PND0_IPI9_SHIFT                   9
#define REG_OSP_IDRP_SET_PND0_IPI9_SIZE                    1
#define REG_OSP_IDRP_SET_PND0_IPI9_MASK                    0x00000200

#define REG_OSP_IDRP_SET_PND0_IPI8_SHIFT                   8
#define REG_OSP_IDRP_SET_PND0_IPI8_SIZE                    1
#define REG_OSP_IDRP_SET_PND0_IPI8_MASK                    0x00000100

#define REG_OSP_IDRP_SET_PND0_IPI7_SHIFT                   7
#define REG_OSP_IDRP_SET_PND0_IPI7_SIZE                    1
#define REG_OSP_IDRP_SET_PND0_IPI7_MASK                    0x00000080

#define REG_OSP_IDRP_SET_PND0_IPI6_SHIFT                   6
#define REG_OSP_IDRP_SET_PND0_IPI6_SIZE                    1
#define REG_OSP_IDRP_SET_PND0_IPI6_MASK                    0x00000040

#define REG_OSP_IDRP_SET_PND0_IPI5_SHIFT                   5
#define REG_OSP_IDRP_SET_PND0_IPI5_SIZE                    1
#define REG_OSP_IDRP_SET_PND0_IPI5_MASK                    0x00000020

#define REG_OSP_IDRP_SET_PND0_IPI4_SHIFT                   4
#define REG_OSP_IDRP_SET_PND0_IPI4_SIZE                    1
#define REG_OSP_IDRP_SET_PND0_IPI4_MASK                    0x00000010

#define REG_OSP_IDRP_SET_PND0_IPI3_SHIFT                   3
#define REG_OSP_IDRP_SET_PND0_IPI3_SIZE                    1
#define REG_OSP_IDRP_SET_PND0_IPI3_MASK                    0x00000008

#define REG_OSP_IDRP_SET_PND0_IPI2_SHIFT                   2
#define REG_OSP_IDRP_SET_PND0_IPI2_SIZE                    1
#define REG_OSP_IDRP_SET_PND0_IPI2_MASK                    0x00000004

#define REG_OSP_IDRP_SET_PND0_IPI1_SHIFT                   1
#define REG_OSP_IDRP_SET_PND0_IPI1_SIZE                    1
#define REG_OSP_IDRP_SET_PND0_IPI1_MASK                    0x00000002

#define REG_OSP_IDRP_SET_PND0_IPI0_SHIFT                   0
#define REG_OSP_IDRP_SET_PND0_IPI0_SIZE                    1
#define REG_OSP_IDRP_SET_PND0_IPI0_MASK                    0x00000001

#define REG_OSP_IDRP_SET_PND0_IPI_ALL_SHIFT                0
#define REG_OSP_IDRP_SET_PND0_IPI_ALL_SIZE                 16
#define REG_OSP_IDRP_SET_PND0_IPI_ALL_MASK                 0x0000ffff

#ifndef SDK_ASM
#define REG_OSP_IDRP_SET_PND0_FIELD( wdog, tm, ipi15, ipi14, ipi13, ipi12, ipi11, ipi10, ipi9, ipi8, ipi7, ipi6, ipi5, ipi4, ipi3, ipi2, ipi1, ipi0, ipi_all ) \
    (u32)( \
    ((u32)(wdog) << REG_OSP_IDRP_SET_PND0_WDOG_SHIFT) | \
    ((u32)(tm) << REG_OSP_IDRP_SET_PND0_TM_SHIFT) | \
    ((u32)(ipi15) << REG_OSP_IDRP_SET_PND0_IPI15_SHIFT) | \
    ((u32)(ipi14) << REG_OSP_IDRP_SET_PND0_IPI14_SHIFT) | \
    ((u32)(ipi13) << REG_OSP_IDRP_SET_PND0_IPI13_SHIFT) | \
    ((u32)(ipi12) << REG_OSP_IDRP_SET_PND0_IPI12_SHIFT) | \
    ((u32)(ipi11) << REG_OSP_IDRP_SET_PND0_IPI11_SHIFT) | \
    ((u32)(ipi10) << REG_OSP_IDRP_SET_PND0_IPI10_SHIFT) | \
    ((u32)(ipi9) << REG_OSP_IDRP_SET_PND0_IPI9_SHIFT) | \
    ((u32)(ipi8) << REG_OSP_IDRP_SET_PND0_IPI8_SHIFT) | \
    ((u32)(ipi7) << REG_OSP_IDRP_SET_PND0_IPI7_SHIFT) | \
    ((u32)(ipi6) << REG_OSP_IDRP_SET_PND0_IPI6_SHIFT) | \
    ((u32)(ipi5) << REG_OSP_IDRP_SET_PND0_IPI5_SHIFT) | \
    ((u32)(ipi4) << REG_OSP_IDRP_SET_PND0_IPI4_SHIFT) | \
    ((u32)(ipi3) << REG_OSP_IDRP_SET_PND0_IPI3_SHIFT) | \
    ((u32)(ipi2) << REG_OSP_IDRP_SET_PND0_IPI2_SHIFT) | \
    ((u32)(ipi1) << REG_OSP_IDRP_SET_PND0_IPI1_SHIFT) | \
    ((u32)(ipi0) << REG_OSP_IDRP_SET_PND0_IPI0_SHIFT) | \
    ((u32)(ipi_all) << REG_OSP_IDRP_SET_PND0_IPI_ALL_SHIFT))
#endif


/* IDRP_SET_PND1 */

#define REG_OSP_IDRP_SET_PND1_XDMA_ABT_SHIFT               25
#define REG_OSP_IDRP_SET_PND1_XDMA_ABT_SIZE                1
#define REG_OSP_IDRP_SET_PND1_XDMA_ABT_MASK                0x02000000

#define REG_OSP_IDRP_SET_PND1_XDMA7_SHIFT                  24
#define REG_OSP_IDRP_SET_PND1_XDMA7_SIZE                   1
#define REG_OSP_IDRP_SET_PND1_XDMA7_MASK                   0x01000000

#define REG_OSP_IDRP_SET_PND1_XDMA6_SHIFT                  22
#define REG_OSP_IDRP_SET_PND1_XDMA6_SIZE                   1
#define REG_OSP_IDRP_SET_PND1_XDMA6_MASK                   0x00400000

#define REG_OSP_IDRP_SET_PND1_XDMA5_SHIFT                  21
#define REG_OSP_IDRP_SET_PND1_XDMA5_SIZE                   1
#define REG_OSP_IDRP_SET_PND1_XDMA5_MASK                   0x00200000

#define REG_OSP_IDRP_SET_PND1_XDMA4_SHIFT                  20
#define REG_OSP_IDRP_SET_PND1_XDMA4_SIZE                   1
#define REG_OSP_IDRP_SET_PND1_XDMA4_MASK                   0x00100000

#define REG_OSP_IDRP_SET_PND1_XDMA3_SHIFT                  19
#define REG_OSP_IDRP_SET_PND1_XDMA3_SIZE                   1
#define REG_OSP_IDRP_SET_PND1_XDMA3_MASK                   0x00080000

#define REG_OSP_IDRP_SET_PND1_XDMA2_SHIFT                  18
#define REG_OSP_IDRP_SET_PND1_XDMA2_SIZE                   1
#define REG_OSP_IDRP_SET_PND1_XDMA2_MASK                   0x00040000

#define REG_OSP_IDRP_SET_PND1_XDMA1_SHIFT                  17
#define REG_OSP_IDRP_SET_PND1_XDMA1_SIZE                   1
#define REG_OSP_IDRP_SET_PND1_XDMA1_MASK                   0x00020000

#define REG_OSP_IDRP_SET_PND1_XDMA0_SHIFT                  16
#define REG_OSP_IDRP_SET_PND1_XDMA0_SIZE                   1
#define REG_OSP_IDRP_SET_PND1_XDMA0_MASK                   0x00010000

#define REG_OSP_IDRP_SET_PND1_GPU_P3D_SHIFT                13
#define REG_OSP_IDRP_SET_PND1_GPU_P3D_SIZE                 1
#define REG_OSP_IDRP_SET_PND1_GPU_P3D_MASK                 0x00002000

#define REG_OSP_IDRP_SET_PND1_GPU_PPF_SHIFT                12
#define REG_OSP_IDRP_SET_PND1_GPU_PPF_SIZE                 1
#define REG_OSP_IDRP_SET_PND1_GPU_PPF_MASK                 0x00001000

#define REG_OSP_IDRP_SET_PND1_GPU_PDC1_SHIFT               11
#define REG_OSP_IDRP_SET_PND1_GPU_PDC1_SIZE                1
#define REG_OSP_IDRP_SET_PND1_GPU_PDC1_MASK                0x00000800

#define REG_OSP_IDRP_SET_PND1_GPU_PDC0_SHIFT               10
#define REG_OSP_IDRP_SET_PND1_GPU_PDC0_SIZE                1
#define REG_OSP_IDRP_SET_PND1_GPU_PDC0_MASK                0x00000400

#define REG_OSP_IDRP_SET_PND1_GPU_PSC1_SHIFT               9
#define REG_OSP_IDRP_SET_PND1_GPU_PSC1_SIZE                1
#define REG_OSP_IDRP_SET_PND1_GPU_PSC1_MASK                0x00000200

#define REG_OSP_IDRP_SET_PND1_GPU_PSC0_SHIFT               8
#define REG_OSP_IDRP_SET_PND1_GPU_PSC0_SIZE                1
#define REG_OSP_IDRP_SET_PND1_GPU_PSC0_MASK                0x00000100

#define REG_OSP_IDRP_SET_PND1_DBG_SPI_SHIFT                4
#define REG_OSP_IDRP_SET_PND1_DBG_SPI_SIZE                 1
#define REG_OSP_IDRP_SET_PND1_DBG_SPI_MASK                 0x00000010

#define REG_OSP_IDRP_SET_PND1_J1_TX_SHIFT                  3
#define REG_OSP_IDRP_SET_PND1_J1_TX_SIZE                   1
#define REG_OSP_IDRP_SET_PND1_J1_TX_MASK                   0x00000008

#define REG_OSP_IDRP_SET_PND1_J1_RX_SHIFT                  2
#define REG_OSP_IDRP_SET_PND1_J1_RX_SIZE                   1
#define REG_OSP_IDRP_SET_PND1_J1_RX_MASK                   0x00000004

#define REG_OSP_IDRP_SET_PND1_J0_TX_SHIFT                  1
#define REG_OSP_IDRP_SET_PND1_J0_TX_SIZE                   1
#define REG_OSP_IDRP_SET_PND1_J0_TX_MASK                   0x00000002

#define REG_OSP_IDRP_SET_PND1_J0_RX_SHIFT                  0
#define REG_OSP_IDRP_SET_PND1_J0_RX_SIZE                   1
#define REG_OSP_IDRP_SET_PND1_J0_RX_MASK                   0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_SET_PND1_FIELD( xdma_abt, xdma7, xdma6, xdma5, xdma4, xdma3, xdma2, xdma1, xdma0, gpu_p3d, gpu_ppf, gpu_pdc1, gpu_pdc0, gpu_psc1, gpu_psc0, dbg_spi, j1_tx, j1_rx, j0_tx, j0_rx ) \
    (u32)( \
    ((u32)(xdma_abt) << REG_OSP_IDRP_SET_PND1_XDMA_ABT_SHIFT) | \
    ((u32)(xdma7) << REG_OSP_IDRP_SET_PND1_XDMA7_SHIFT) | \
    ((u32)(xdma6) << REG_OSP_IDRP_SET_PND1_XDMA6_SHIFT) | \
    ((u32)(xdma5) << REG_OSP_IDRP_SET_PND1_XDMA5_SHIFT) | \
    ((u32)(xdma4) << REG_OSP_IDRP_SET_PND1_XDMA4_SHIFT) | \
    ((u32)(xdma3) << REG_OSP_IDRP_SET_PND1_XDMA3_SHIFT) | \
    ((u32)(xdma2) << REG_OSP_IDRP_SET_PND1_XDMA2_SHIFT) | \
    ((u32)(xdma1) << REG_OSP_IDRP_SET_PND1_XDMA1_SHIFT) | \
    ((u32)(xdma0) << REG_OSP_IDRP_SET_PND1_XDMA0_SHIFT) | \
    ((u32)(gpu_p3d) << REG_OSP_IDRP_SET_PND1_GPU_P3D_SHIFT) | \
    ((u32)(gpu_ppf) << REG_OSP_IDRP_SET_PND1_GPU_PPF_SHIFT) | \
    ((u32)(gpu_pdc1) << REG_OSP_IDRP_SET_PND1_GPU_PDC1_SHIFT) | \
    ((u32)(gpu_pdc0) << REG_OSP_IDRP_SET_PND1_GPU_PDC0_SHIFT) | \
    ((u32)(gpu_psc1) << REG_OSP_IDRP_SET_PND1_GPU_PSC1_SHIFT) | \
    ((u32)(gpu_psc0) << REG_OSP_IDRP_SET_PND1_GPU_PSC0_SHIFT) | \
    ((u32)(dbg_spi) << REG_OSP_IDRP_SET_PND1_DBG_SPI_SHIFT) | \
    ((u32)(j1_tx) << REG_OSP_IDRP_SET_PND1_J1_TX_SHIFT) | \
    ((u32)(j1_rx) << REG_OSP_IDRP_SET_PND1_J1_RX_SHIFT) | \
    ((u32)(j0_tx) << REG_OSP_IDRP_SET_PND1_J0_TX_SHIFT) | \
    ((u32)(j0_rx) << REG_OSP_IDRP_SET_PND1_J0_RX_SHIFT))
#endif


/* IDRP_SET_PND2 */

#define REG_OSP_IDRP_SET_PND2_DS_WL_SHIFT                  31
#define REG_OSP_IDRP_SET_PND2_DS_WL_SIZE                   1
#define REG_OSP_IDRP_SET_PND2_DS_WL_MASK                   0x80000000

#define REG_OSP_IDRP_SET_PND2_I2C3_SHIFT                   28
#define REG_OSP_IDRP_SET_PND2_I2C3_SIZE                    1
#define REG_OSP_IDRP_SET_PND2_I2C3_MASK                    0x10000000

#define REG_OSP_IDRP_SET_PND2_KEY_SHIFT                    27
#define REG_OSP_IDRP_SET_PND2_KEY_SIZE                     1
#define REG_OSP_IDRP_SET_PND2_KEY_MASK                     0x08000000

#define REG_OSP_IDRP_SET_PND2_MIC_SHIFT                    26
#define REG_OSP_IDRP_SET_PND2_MIC_SIZE                     1
#define REG_OSP_IDRP_SET_PND2_MIC_MASK                     0x04000000

#define REG_OSP_IDRP_SET_PND2_PDN_LGY_SHIFT                25
#define REG_OSP_IDRP_SET_PND2_PDN_LGY_SIZE                 1
#define REG_OSP_IDRP_SET_PND2_PDN_LGY_MASK                 0x02000000

#define REG_OSP_IDRP_SET_PND2_PDN_WAKE_SHIFT               24
#define REG_OSP_IDRP_SET_PND2_PDN_WAKE_SIZE                1
#define REG_OSP_IDRP_SET_PND2_PDN_WAKE_MASK                0x01000000

#define REG_OSP_IDRP_SET_PND2_SPI2_SHIFT                   23
#define REG_OSP_IDRP_SET_PND2_SPI2_SIZE                    1
#define REG_OSP_IDRP_SET_PND2_SPI2_MASK                    0x00800000

#define REG_OSP_IDRP_SET_PND2_SPI1_SHIFT                   22
#define REG_OSP_IDRP_SET_PND2_SPI1_SIZE                    1
#define REG_OSP_IDRP_SET_PND2_SPI1_MASK                    0x00400000

#define REG_OSP_IDRP_SET_PND2_I2C2_SHIFT                   21
#define REG_OSP_IDRP_SET_PND2_I2C2_SIZE                    1
#define REG_OSP_IDRP_SET_PND2_I2C2_MASK                    0x00200000

#define REG_OSP_IDRP_SET_PND2_I2C1_SHIFT                   20
#define REG_OSP_IDRP_SET_PND2_I2C1_SIZE                    1
#define REG_OSP_IDRP_SET_PND2_I2C1_MASK                    0x00100000

#define REG_OSP_IDRP_SET_PND2_PXI_RX_SHIFT                 19
#define REG_OSP_IDRP_SET_PND2_PXI_RX_SIZE                  1
#define REG_OSP_IDRP_SET_PND2_PXI_RX_MASK                  0x00080000

#define REG_OSP_IDRP_SET_PND2_PXI_TX_SHIFT                 18
#define REG_OSP_IDRP_SET_PND2_PXI_TX_SIZE                  1
#define REG_OSP_IDRP_SET_PND2_PXI_TX_MASK                  0x00040000

#define REG_OSP_IDRP_SET_PND2_CPU1_SHIFT                   17
#define REG_OSP_IDRP_SET_PND2_CPU1_SIZE                    1
#define REG_OSP_IDRP_SET_PND2_CPU1_MASK                    0x00020000

#define REG_OSP_IDRP_SET_PND2_CPU0_SHIFT                   16
#define REG_OSP_IDRP_SET_PND2_CPU0_SIZE                    1
#define REG_OSP_IDRP_SET_PND2_CPU0_MASK                    0x00010000

#define REG_OSP_IDRP_SET_PND2_SCLR2_SHIFT                  13
#define REG_OSP_IDRP_SET_PND2_SCLR2_SIZE                   1
#define REG_OSP_IDRP_SET_PND2_SCLR2_MASK                   0x00002000

#define REG_OSP_IDRP_SET_PND2_SCLR1_SHIFT                  12
#define REG_OSP_IDRP_SET_PND2_SCLR1_SIZE                   1
#define REG_OSP_IDRP_SET_PND2_SCLR1_MASK                   0x00001000

#define REG_OSP_IDRP_SET_PND2_YUV2RGB_SHIFT                11
#define REG_OSP_IDRP_SET_PND2_YUV2RGB_SIZE                 1
#define REG_OSP_IDRP_SET_PND2_YUV2RGB_MASK                 0x00000800

#define REG_OSP_IDRP_SET_PND2_DSP_SHIFT                    10
#define REG_OSP_IDRP_SET_PND2_DSP_SIZE                     1
#define REG_OSP_IDRP_SET_PND2_DSP_MASK                     0x00000400

#define REG_OSP_IDRP_SET_PND2_CAM2_SHIFT                   9
#define REG_OSP_IDRP_SET_PND2_CAM2_SIZE                    1
#define REG_OSP_IDRP_SET_PND2_CAM2_MASK                    0x00000200

#define REG_OSP_IDRP_SET_PND2_CAM1_SHIFT                   8
#define REG_OSP_IDRP_SET_PND2_CAM1_SIZE                    1
#define REG_OSP_IDRP_SET_PND2_CAM1_MASK                    0x00000100

#define REG_OSP_IDRP_SET_PND2_LGC_DET_SHIFT                6
#define REG_OSP_IDRP_SET_PND2_LGC_DET_SIZE                 1
#define REG_OSP_IDRP_SET_PND2_LGC_DET_MASK                 0x00000040

#define REG_OSP_IDRP_SET_PND2_LGC_I_SHIFT                  5
#define REG_OSP_IDRP_SET_PND2_LGC_I_SIZE                   1
#define REG_OSP_IDRP_SET_PND2_LGC_I_MASK                   0x00000020

#define REG_OSP_IDRP_SET_PND2_LMC_SHIFT                    4
#define REG_OSP_IDRP_SET_PND2_LMC_SIZE                     1
#define REG_OSP_IDRP_SET_PND2_LMC_MASK                     0x00000010

#define REG_OSP_IDRP_SET_PND2_SD3_A_SHIFT                  3
#define REG_OSP_IDRP_SET_PND2_SD3_A_SIZE                   1
#define REG_OSP_IDRP_SET_PND2_SD3_A_MASK                   0x00000008

#define REG_OSP_IDRP_SET_PND2_SD3_SHIFT                    2
#define REG_OSP_IDRP_SET_PND2_SD3_SIZE                     1
#define REG_OSP_IDRP_SET_PND2_SD3_MASK                     0x00000004

#define REG_OSP_IDRP_SET_PND2_SD2_A_SHIFT                  1
#define REG_OSP_IDRP_SET_PND2_SD2_A_SIZE                   1
#define REG_OSP_IDRP_SET_PND2_SD2_A_MASK                   0x00000002

#define REG_OSP_IDRP_SET_PND2_SD2_SHIFT                    0
#define REG_OSP_IDRP_SET_PND2_SD2_SIZE                     1
#define REG_OSP_IDRP_SET_PND2_SD2_MASK                     0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_SET_PND2_FIELD( ds_wl, i2c3, key, mic, pdn_lgy, pdn_wake, spi2, spi1, i2c2, i2c1, pxi_rx, pxi_tx, cpu1, cpu0, sclr2, sclr1, yuv2rgb, dsp, cam2, cam1, lgc_det, lgc_i, lmc, sd3_a, sd3, sd2_a, sd2 ) \
    (u32)( \
    ((u32)(ds_wl) << REG_OSP_IDRP_SET_PND2_DS_WL_SHIFT) | \
    ((u32)(i2c3) << REG_OSP_IDRP_SET_PND2_I2C3_SHIFT) | \
    ((u32)(key) << REG_OSP_IDRP_SET_PND2_KEY_SHIFT) | \
    ((u32)(mic) << REG_OSP_IDRP_SET_PND2_MIC_SHIFT) | \
    ((u32)(pdn_lgy) << REG_OSP_IDRP_SET_PND2_PDN_LGY_SHIFT) | \
    ((u32)(pdn_wake) << REG_OSP_IDRP_SET_PND2_PDN_WAKE_SHIFT) | \
    ((u32)(spi2) << REG_OSP_IDRP_SET_PND2_SPI2_SHIFT) | \
    ((u32)(spi1) << REG_OSP_IDRP_SET_PND2_SPI1_SHIFT) | \
    ((u32)(i2c2) << REG_OSP_IDRP_SET_PND2_I2C2_SHIFT) | \
    ((u32)(i2c1) << REG_OSP_IDRP_SET_PND2_I2C1_SHIFT) | \
    ((u32)(pxi_rx) << REG_OSP_IDRP_SET_PND2_PXI_RX_SHIFT) | \
    ((u32)(pxi_tx) << REG_OSP_IDRP_SET_PND2_PXI_TX_SHIFT) | \
    ((u32)(cpu1) << REG_OSP_IDRP_SET_PND2_CPU1_SHIFT) | \
    ((u32)(cpu0) << REG_OSP_IDRP_SET_PND2_CPU0_SHIFT) | \
    ((u32)(sclr2) << REG_OSP_IDRP_SET_PND2_SCLR2_SHIFT) | \
    ((u32)(sclr1) << REG_OSP_IDRP_SET_PND2_SCLR1_SHIFT) | \
    ((u32)(yuv2rgb) << REG_OSP_IDRP_SET_PND2_YUV2RGB_SHIFT) | \
    ((u32)(dsp) << REG_OSP_IDRP_SET_PND2_DSP_SHIFT) | \
    ((u32)(cam2) << REG_OSP_IDRP_SET_PND2_CAM2_SHIFT) | \
    ((u32)(cam1) << REG_OSP_IDRP_SET_PND2_CAM1_SHIFT) | \
    ((u32)(lgc_det) << REG_OSP_IDRP_SET_PND2_LGC_DET_SHIFT) | \
    ((u32)(lgc_i) << REG_OSP_IDRP_SET_PND2_LGC_I_SHIFT) | \
    ((u32)(lmc) << REG_OSP_IDRP_SET_PND2_LMC_SHIFT) | \
    ((u32)(sd3_a) << REG_OSP_IDRP_SET_PND2_SD3_A_SHIFT) | \
    ((u32)(sd3) << REG_OSP_IDRP_SET_PND2_SD3_SHIFT) | \
    ((u32)(sd2_a) << REG_OSP_IDRP_SET_PND2_SD2_A_SHIFT) | \
    ((u32)(sd2) << REG_OSP_IDRP_SET_PND2_SD2_SHIFT))
#endif


/* IDRP_SET_PND3 */

#define REG_OSP_IDRP_SET_PND3_PMUIRQ7_SHIFT                29
#define REG_OSP_IDRP_SET_PND3_PMUIRQ7_SIZE                 1
#define REG_OSP_IDRP_SET_PND3_PMUIRQ7_MASK                 0x20000000

#define REG_OSP_IDRP_SET_PND3_PMUIRQ6_SHIFT                28
#define REG_OSP_IDRP_SET_PND3_PMUIRQ6_SIZE                 1
#define REG_OSP_IDRP_SET_PND3_PMUIRQ6_MASK                 0x10000000

#define REG_OSP_IDRP_SET_PND3_PMUIRQ5_SHIFT                27
#define REG_OSP_IDRP_SET_PND3_PMUIRQ5_SIZE                 1
#define REG_OSP_IDRP_SET_PND3_PMUIRQ5_MASK                 0x08000000

#define REG_OSP_IDRP_SET_PND3_PMUIRQ4_SHIFT                26
#define REG_OSP_IDRP_SET_PND3_PMUIRQ4_SIZE                 1
#define REG_OSP_IDRP_SET_PND3_PMUIRQ4_MASK                 0x04000000

#define REG_OSP_IDRP_SET_PND3_PMUIRQ1_SHIFT                25
#define REG_OSP_IDRP_SET_PND3_PMUIRQ1_SIZE                 1
#define REG_OSP_IDRP_SET_PND3_PMUIRQ1_MASK                 0x02000000

#define REG_OSP_IDRP_SET_PND3_PMUIRQ0_SHIFT                24
#define REG_OSP_IDRP_SET_PND3_PMUIRQ0_SIZE                 1
#define REG_OSP_IDRP_SET_PND3_PMUIRQ0_MASK                 0x01000000

#define REG_OSP_IDRP_SET_PND3_CGC_DET_SHIFT                21
#define REG_OSP_IDRP_SET_PND3_CGC_DET_SIZE                 1
#define REG_OSP_IDRP_SET_PND3_CGC_DET_MASK                 0x00200000

#define REG_OSP_IDRP_SET_PND3_CGC_I_SHIFT                  20
#define REG_OSP_IDRP_SET_PND3_CGC_I_SIZE                   1
#define REG_OSP_IDRP_SET_PND3_CGC_I_MASK                   0x00100000

#define REG_OSP_IDRP_SET_PND3_GPIO3_18_5_SHIFT             19
#define REG_OSP_IDRP_SET_PND3_GPIO3_18_5_SIZE              1
#define REG_OSP_IDRP_SET_PND3_GPIO3_18_5_MASK              0x00080000

#define REG_OSP_IDRP_SET_PND3_GPIO3_18_4_SHIFT             18
#define REG_OSP_IDRP_SET_PND3_GPIO3_18_4_SIZE              1
#define REG_OSP_IDRP_SET_PND3_GPIO3_18_4_MASK              0x00040000

#define REG_OSP_IDRP_SET_PND3_GPIO3_18_3_SHIFT             17
#define REG_OSP_IDRP_SET_PND3_GPIO3_18_3_SIZE              1
#define REG_OSP_IDRP_SET_PND3_GPIO3_18_3_MASK              0x00020000

#define REG_OSP_IDRP_SET_PND3_GPIO3_18_2_SHIFT             16
#define REG_OSP_IDRP_SET_PND3_GPIO3_18_2_SIZE              1
#define REG_OSP_IDRP_SET_PND3_GPIO3_18_2_MASK              0x00010000

#define REG_OSP_IDRP_SET_PND3_GPIO3_18_1_SHIFT             15
#define REG_OSP_IDRP_SET_PND3_GPIO3_18_1_SIZE              1
#define REG_OSP_IDRP_SET_PND3_GPIO3_18_1_MASK              0x00008000

#define REG_OSP_IDRP_SET_PND3_GPIO3_18_0_SHIFT             14
#define REG_OSP_IDRP_SET_PND3_GPIO3_18_0_SIZE              1
#define REG_OSP_IDRP_SET_PND3_GPIO3_18_0_MASK              0x00004000

#define REG_OSP_IDRP_SET_PND3_GPIO3_33_5_SHIFT             13
#define REG_OSP_IDRP_SET_PND3_GPIO3_33_5_SIZE              1
#define REG_OSP_IDRP_SET_PND3_GPIO3_33_5_MASK              0x00002000

#define REG_OSP_IDRP_SET_PND3_GPIO3_33_4_SHIFT             12
#define REG_OSP_IDRP_SET_PND3_GPIO3_33_4_SIZE              1
#define REG_OSP_IDRP_SET_PND3_GPIO3_33_4_MASK              0x00001000

#define REG_OSP_IDRP_SET_PND3_GPIO3_33_3_SHIFT             11
#define REG_OSP_IDRP_SET_PND3_GPIO3_33_3_SIZE              1
#define REG_OSP_IDRP_SET_PND3_GPIO3_33_3_MASK              0x00000800

#define REG_OSP_IDRP_SET_PND3_GPIO3_33_2_SHIFT             10
#define REG_OSP_IDRP_SET_PND3_GPIO3_33_2_SIZE              1
#define REG_OSP_IDRP_SET_PND3_GPIO3_33_2_MASK              0x00000400

#define REG_OSP_IDRP_SET_PND3_GPIO3_33_1_SHIFT             9
#define REG_OSP_IDRP_SET_PND3_GPIO3_33_1_SIZE              1
#define REG_OSP_IDRP_SET_PND3_GPIO3_33_1_MASK              0x00000200

#define REG_OSP_IDRP_SET_PND3_GPIO3_33_0_SHIFT             8
#define REG_OSP_IDRP_SET_PND3_GPIO3_33_0_SIZE              1
#define REG_OSP_IDRP_SET_PND3_GPIO3_33_0_MASK              0x00000100

#define REG_OSP_IDRP_SET_PND3_CTR_MCU_SHIFT                17
#define REG_OSP_IDRP_SET_PND3_CTR_MCU_SIZE                 1
#define REG_OSP_IDRP_SET_PND3_CTR_MCU_MASK                 0x00020000

#define REG_OSP_IDRP_SET_PND3_RMC_SHIFT                    16
#define REG_OSP_IDRP_SET_PND3_RMC_SIZE                     1
#define REG_OSP_IDRP_SET_PND3_RMC_MASK                     0x00010000

#define REG_OSP_IDRP_SET_PND3_IR_SHIFT                     10
#define REG_OSP_IDRP_SET_PND3_IR_SIZE                      1
#define REG_OSP_IDRP_SET_PND3_IR_MASK                      0x00000400

#define REG_OSP_IDRP_SET_PND3_SP_SEL_SHIFT                 8
#define REG_OSP_IDRP_SET_PND3_SP_SEL_SIZE                  1
#define REG_OSP_IDRP_SET_PND3_SP_SEL_MASK                  0x00000100

#define REG_OSP_IDRP_SET_PND3_TWL_DEPOP_SHIFT              6
#define REG_OSP_IDRP_SET_PND3_TWL_DEPOP_SIZE               1
#define REG_OSP_IDRP_SET_PND3_TWL_DEPOP_MASK               0x00000040

#define REG_OSP_IDRP_SET_PND3_TWL_MCU_SHIFT                5
#define REG_OSP_IDRP_SET_PND3_TWL_MCU_SIZE                 1
#define REG_OSP_IDRP_SET_PND3_TWL_MCU_MASK                 0x00000020

#define REG_OSP_IDRP_SET_PND3_HP_SHIFT                     4
#define REG_OSP_IDRP_SET_PND3_HP_SIZE                      1
#define REG_OSP_IDRP_SET_PND3_HP_MASK                      0x00000010

#define REG_OSP_IDRP_SET_PND3_TP_SHIFT                     3
#define REG_OSP_IDRP_SET_PND3_TP_SIZE                      1
#define REG_OSP_IDRP_SET_PND3_TP_MASK                      0x00000008

#define REG_OSP_IDRP_SET_PND3_COVER_R_SHIFT                2
#define REG_OSP_IDRP_SET_PND3_COVER_R_SIZE                 1
#define REG_OSP_IDRP_SET_PND3_COVER_R_MASK                 0x00000004

#define REG_OSP_IDRP_SET_PND3_COVER_SHIFT                  0
#define REG_OSP_IDRP_SET_PND3_COVER_SIZE                   1
#define REG_OSP_IDRP_SET_PND3_COVER_MASK                   0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_SET_PND3_FIELD( pmuirq7, pmuirq6, pmuirq5, pmuirq4, pmuirq1, pmuirq0, cgc_det, cgc_i, gpio3_18_5, gpio3_18_4, gpio3_18_3, gpio3_18_2, gpio3_18_1, gpio3_18_0, gpio3_33_5, gpio3_33_4, gpio3_33_3, gpio3_33_2, gpio3_33_1, gpio3_33_0, ctr_mcu, rmc, ir, sp_sel, twl_depop, twl_mcu, hp, tp, cover_r, cover ) \
    (u32)( \
    ((u32)(pmuirq7) << REG_OSP_IDRP_SET_PND3_PMUIRQ7_SHIFT) | \
    ((u32)(pmuirq6) << REG_OSP_IDRP_SET_PND3_PMUIRQ6_SHIFT) | \
    ((u32)(pmuirq5) << REG_OSP_IDRP_SET_PND3_PMUIRQ5_SHIFT) | \
    ((u32)(pmuirq4) << REG_OSP_IDRP_SET_PND3_PMUIRQ4_SHIFT) | \
    ((u32)(pmuirq1) << REG_OSP_IDRP_SET_PND3_PMUIRQ1_SHIFT) | \
    ((u32)(pmuirq0) << REG_OSP_IDRP_SET_PND3_PMUIRQ0_SHIFT) | \
    ((u32)(cgc_det) << REG_OSP_IDRP_SET_PND3_CGC_DET_SHIFT) | \
    ((u32)(cgc_i) << REG_OSP_IDRP_SET_PND3_CGC_I_SHIFT) | \
    ((u32)(gpio3_18_5) << REG_OSP_IDRP_SET_PND3_GPIO3_18_5_SHIFT) | \
    ((u32)(gpio3_18_4) << REG_OSP_IDRP_SET_PND3_GPIO3_18_4_SHIFT) | \
    ((u32)(gpio3_18_3) << REG_OSP_IDRP_SET_PND3_GPIO3_18_3_SHIFT) | \
    ((u32)(gpio3_18_2) << REG_OSP_IDRP_SET_PND3_GPIO3_18_2_SHIFT) | \
    ((u32)(gpio3_18_1) << REG_OSP_IDRP_SET_PND3_GPIO3_18_1_SHIFT) | \
    ((u32)(gpio3_18_0) << REG_OSP_IDRP_SET_PND3_GPIO3_18_0_SHIFT) | \
    ((u32)(gpio3_33_5) << REG_OSP_IDRP_SET_PND3_GPIO3_33_5_SHIFT) | \
    ((u32)(gpio3_33_4) << REG_OSP_IDRP_SET_PND3_GPIO3_33_4_SHIFT) | \
    ((u32)(gpio3_33_3) << REG_OSP_IDRP_SET_PND3_GPIO3_33_3_SHIFT) | \
    ((u32)(gpio3_33_2) << REG_OSP_IDRP_SET_PND3_GPIO3_33_2_SHIFT) | \
    ((u32)(gpio3_33_1) << REG_OSP_IDRP_SET_PND3_GPIO3_33_1_SHIFT) | \
    ((u32)(gpio3_33_0) << REG_OSP_IDRP_SET_PND3_GPIO3_33_0_SHIFT) | \
    ((u32)(ctr_mcu) << REG_OSP_IDRP_SET_PND3_CTR_MCU_SHIFT) | \
    ((u32)(rmc) << REG_OSP_IDRP_SET_PND3_RMC_SHIFT) | \
    ((u32)(ir) << REG_OSP_IDRP_SET_PND3_IR_SHIFT) | \
    ((u32)(sp_sel) << REG_OSP_IDRP_SET_PND3_SP_SEL_SHIFT) | \
    ((u32)(twl_depop) << REG_OSP_IDRP_SET_PND3_TWL_DEPOP_SHIFT) | \
    ((u32)(twl_mcu) << REG_OSP_IDRP_SET_PND3_TWL_MCU_SHIFT) | \
    ((u32)(hp) << REG_OSP_IDRP_SET_PND3_HP_SHIFT) | \
    ((u32)(tp) << REG_OSP_IDRP_SET_PND3_TP_SHIFT) | \
    ((u32)(cover_r) << REG_OSP_IDRP_SET_PND3_COVER_R_SHIFT) | \
    ((u32)(cover) << REG_OSP_IDRP_SET_PND3_COVER_SHIFT))
#endif


/* IDRP_CLR_PND0 */

#define REG_OSP_IDRP_CLR_PND0_WDOG_SHIFT                   30
#define REG_OSP_IDRP_CLR_PND0_WDOG_SIZE                    1
#define REG_OSP_IDRP_CLR_PND0_WDOG_MASK                    0x40000000

#define REG_OSP_IDRP_CLR_PND0_TM_SHIFT                     29
#define REG_OSP_IDRP_CLR_PND0_TM_SIZE                      1
#define REG_OSP_IDRP_CLR_PND0_TM_MASK                      0x20000000

#define REG_OSP_IDRP_CLR_PND0_IPI15_SHIFT                  15
#define REG_OSP_IDRP_CLR_PND0_IPI15_SIZE                   1
#define REG_OSP_IDRP_CLR_PND0_IPI15_MASK                   0x00008000

#define REG_OSP_IDRP_CLR_PND0_IPI14_SHIFT                  14
#define REG_OSP_IDRP_CLR_PND0_IPI14_SIZE                   1
#define REG_OSP_IDRP_CLR_PND0_IPI14_MASK                   0x00004000

#define REG_OSP_IDRP_CLR_PND0_IPI13_SHIFT                  13
#define REG_OSP_IDRP_CLR_PND0_IPI13_SIZE                   1
#define REG_OSP_IDRP_CLR_PND0_IPI13_MASK                   0x00002000

#define REG_OSP_IDRP_CLR_PND0_IPI12_SHIFT                  12
#define REG_OSP_IDRP_CLR_PND0_IPI12_SIZE                   1
#define REG_OSP_IDRP_CLR_PND0_IPI12_MASK                   0x00001000

#define REG_OSP_IDRP_CLR_PND0_IPI11_SHIFT                  11
#define REG_OSP_IDRP_CLR_PND0_IPI11_SIZE                   1
#define REG_OSP_IDRP_CLR_PND0_IPI11_MASK                   0x00000800

#define REG_OSP_IDRP_CLR_PND0_IPI10_SHIFT                  10
#define REG_OSP_IDRP_CLR_PND0_IPI10_SIZE                   1
#define REG_OSP_IDRP_CLR_PND0_IPI10_MASK                   0x00000400

#define REG_OSP_IDRP_CLR_PND0_IPI9_SHIFT                   9
#define REG_OSP_IDRP_CLR_PND0_IPI9_SIZE                    1
#define REG_OSP_IDRP_CLR_PND0_IPI9_MASK                    0x00000200

#define REG_OSP_IDRP_CLR_PND0_IPI8_SHIFT                   8
#define REG_OSP_IDRP_CLR_PND0_IPI8_SIZE                    1
#define REG_OSP_IDRP_CLR_PND0_IPI8_MASK                    0x00000100

#define REG_OSP_IDRP_CLR_PND0_IPI7_SHIFT                   7
#define REG_OSP_IDRP_CLR_PND0_IPI7_SIZE                    1
#define REG_OSP_IDRP_CLR_PND0_IPI7_MASK                    0x00000080

#define REG_OSP_IDRP_CLR_PND0_IPI6_SHIFT                   6
#define REG_OSP_IDRP_CLR_PND0_IPI6_SIZE                    1
#define REG_OSP_IDRP_CLR_PND0_IPI6_MASK                    0x00000040

#define REG_OSP_IDRP_CLR_PND0_IPI5_SHIFT                   5
#define REG_OSP_IDRP_CLR_PND0_IPI5_SIZE                    1
#define REG_OSP_IDRP_CLR_PND0_IPI5_MASK                    0x00000020

#define REG_OSP_IDRP_CLR_PND0_IPI4_SHIFT                   4
#define REG_OSP_IDRP_CLR_PND0_IPI4_SIZE                    1
#define REG_OSP_IDRP_CLR_PND0_IPI4_MASK                    0x00000010

#define REG_OSP_IDRP_CLR_PND0_IPI3_SHIFT                   3
#define REG_OSP_IDRP_CLR_PND0_IPI3_SIZE                    1
#define REG_OSP_IDRP_CLR_PND0_IPI3_MASK                    0x00000008

#define REG_OSP_IDRP_CLR_PND0_IPI2_SHIFT                   2
#define REG_OSP_IDRP_CLR_PND0_IPI2_SIZE                    1
#define REG_OSP_IDRP_CLR_PND0_IPI2_MASK                    0x00000004

#define REG_OSP_IDRP_CLR_PND0_IPI1_SHIFT                   1
#define REG_OSP_IDRP_CLR_PND0_IPI1_SIZE                    1
#define REG_OSP_IDRP_CLR_PND0_IPI1_MASK                    0x00000002

#define REG_OSP_IDRP_CLR_PND0_IPI0_SHIFT                   0
#define REG_OSP_IDRP_CLR_PND0_IPI0_SIZE                    1
#define REG_OSP_IDRP_CLR_PND0_IPI0_MASK                    0x00000001

#define REG_OSP_IDRP_CLR_PND0_IPI_ALL_SHIFT                0
#define REG_OSP_IDRP_CLR_PND0_IPI_ALL_SIZE                 16
#define REG_OSP_IDRP_CLR_PND0_IPI_ALL_MASK                 0x0000ffff

#ifndef SDK_ASM
#define REG_OSP_IDRP_CLR_PND0_FIELD( wdog, tm, ipi15, ipi14, ipi13, ipi12, ipi11, ipi10, ipi9, ipi8, ipi7, ipi6, ipi5, ipi4, ipi3, ipi2, ipi1, ipi0, ipi_all ) \
    (u32)( \
    ((u32)(wdog) << REG_OSP_IDRP_CLR_PND0_WDOG_SHIFT) | \
    ((u32)(tm) << REG_OSP_IDRP_CLR_PND0_TM_SHIFT) | \
    ((u32)(ipi15) << REG_OSP_IDRP_CLR_PND0_IPI15_SHIFT) | \
    ((u32)(ipi14) << REG_OSP_IDRP_CLR_PND0_IPI14_SHIFT) | \
    ((u32)(ipi13) << REG_OSP_IDRP_CLR_PND0_IPI13_SHIFT) | \
    ((u32)(ipi12) << REG_OSP_IDRP_CLR_PND0_IPI12_SHIFT) | \
    ((u32)(ipi11) << REG_OSP_IDRP_CLR_PND0_IPI11_SHIFT) | \
    ((u32)(ipi10) << REG_OSP_IDRP_CLR_PND0_IPI10_SHIFT) | \
    ((u32)(ipi9) << REG_OSP_IDRP_CLR_PND0_IPI9_SHIFT) | \
    ((u32)(ipi8) << REG_OSP_IDRP_CLR_PND0_IPI8_SHIFT) | \
    ((u32)(ipi7) << REG_OSP_IDRP_CLR_PND0_IPI7_SHIFT) | \
    ((u32)(ipi6) << REG_OSP_IDRP_CLR_PND0_IPI6_SHIFT) | \
    ((u32)(ipi5) << REG_OSP_IDRP_CLR_PND0_IPI5_SHIFT) | \
    ((u32)(ipi4) << REG_OSP_IDRP_CLR_PND0_IPI4_SHIFT) | \
    ((u32)(ipi3) << REG_OSP_IDRP_CLR_PND0_IPI3_SHIFT) | \
    ((u32)(ipi2) << REG_OSP_IDRP_CLR_PND0_IPI2_SHIFT) | \
    ((u32)(ipi1) << REG_OSP_IDRP_CLR_PND0_IPI1_SHIFT) | \
    ((u32)(ipi0) << REG_OSP_IDRP_CLR_PND0_IPI0_SHIFT) | \
    ((u32)(ipi_all) << REG_OSP_IDRP_CLR_PND0_IPI_ALL_SHIFT))
#endif


/* IDRP_CLR_PND1 */

#define REG_OSP_IDRP_CLR_PND1_XDMA_ABT_SHIFT               25
#define REG_OSP_IDRP_CLR_PND1_XDMA_ABT_SIZE                1
#define REG_OSP_IDRP_CLR_PND1_XDMA_ABT_MASK                0x02000000

#define REG_OSP_IDRP_CLR_PND1_XDMA7_SHIFT                  24
#define REG_OSP_IDRP_CLR_PND1_XDMA7_SIZE                   1
#define REG_OSP_IDRP_CLR_PND1_XDMA7_MASK                   0x01000000

#define REG_OSP_IDRP_CLR_PND1_XDMA6_SHIFT                  22
#define REG_OSP_IDRP_CLR_PND1_XDMA6_SIZE                   1
#define REG_OSP_IDRP_CLR_PND1_XDMA6_MASK                   0x00400000

#define REG_OSP_IDRP_CLR_PND1_XDMA5_SHIFT                  21
#define REG_OSP_IDRP_CLR_PND1_XDMA5_SIZE                   1
#define REG_OSP_IDRP_CLR_PND1_XDMA5_MASK                   0x00200000

#define REG_OSP_IDRP_CLR_PND1_XDMA4_SHIFT                  20
#define REG_OSP_IDRP_CLR_PND1_XDMA4_SIZE                   1
#define REG_OSP_IDRP_CLR_PND1_XDMA4_MASK                   0x00100000

#define REG_OSP_IDRP_CLR_PND1_XDMA3_SHIFT                  19
#define REG_OSP_IDRP_CLR_PND1_XDMA3_SIZE                   1
#define REG_OSP_IDRP_CLR_PND1_XDMA3_MASK                   0x00080000

#define REG_OSP_IDRP_CLR_PND1_XDMA2_SHIFT                  18
#define REG_OSP_IDRP_CLR_PND1_XDMA2_SIZE                   1
#define REG_OSP_IDRP_CLR_PND1_XDMA2_MASK                   0x00040000

#define REG_OSP_IDRP_CLR_PND1_XDMA1_SHIFT                  17
#define REG_OSP_IDRP_CLR_PND1_XDMA1_SIZE                   1
#define REG_OSP_IDRP_CLR_PND1_XDMA1_MASK                   0x00020000

#define REG_OSP_IDRP_CLR_PND1_XDMA0_SHIFT                  16
#define REG_OSP_IDRP_CLR_PND1_XDMA0_SIZE                   1
#define REG_OSP_IDRP_CLR_PND1_XDMA0_MASK                   0x00010000

#define REG_OSP_IDRP_CLR_PND1_GPU_P3D_SHIFT                13
#define REG_OSP_IDRP_CLR_PND1_GPU_P3D_SIZE                 1
#define REG_OSP_IDRP_CLR_PND1_GPU_P3D_MASK                 0x00002000

#define REG_OSP_IDRP_CLR_PND1_GPU_PPF_SHIFT                12
#define REG_OSP_IDRP_CLR_PND1_GPU_PPF_SIZE                 1
#define REG_OSP_IDRP_CLR_PND1_GPU_PPF_MASK                 0x00001000

#define REG_OSP_IDRP_CLR_PND1_GPU_PDC1_SHIFT               11
#define REG_OSP_IDRP_CLR_PND1_GPU_PDC1_SIZE                1
#define REG_OSP_IDRP_CLR_PND1_GPU_PDC1_MASK                0x00000800

#define REG_OSP_IDRP_CLR_PND1_GPU_PDC0_SHIFT               10
#define REG_OSP_IDRP_CLR_PND1_GPU_PDC0_SIZE                1
#define REG_OSP_IDRP_CLR_PND1_GPU_PDC0_MASK                0x00000400

#define REG_OSP_IDRP_CLR_PND1_GPU_PSC1_SHIFT               9
#define REG_OSP_IDRP_CLR_PND1_GPU_PSC1_SIZE                1
#define REG_OSP_IDRP_CLR_PND1_GPU_PSC1_MASK                0x00000200

#define REG_OSP_IDRP_CLR_PND1_GPU_PSC0_SHIFT               8
#define REG_OSP_IDRP_CLR_PND1_GPU_PSC0_SIZE                1
#define REG_OSP_IDRP_CLR_PND1_GPU_PSC0_MASK                0x00000100

#define REG_OSP_IDRP_CLR_PND1_DBG_SPI_SHIFT                4
#define REG_OSP_IDRP_CLR_PND1_DBG_SPI_SIZE                 1
#define REG_OSP_IDRP_CLR_PND1_DBG_SPI_MASK                 0x00000010

#define REG_OSP_IDRP_CLR_PND1_J1_TX_SHIFT                  3
#define REG_OSP_IDRP_CLR_PND1_J1_TX_SIZE                   1
#define REG_OSP_IDRP_CLR_PND1_J1_TX_MASK                   0x00000008

#define REG_OSP_IDRP_CLR_PND1_J1_RX_SHIFT                  2
#define REG_OSP_IDRP_CLR_PND1_J1_RX_SIZE                   1
#define REG_OSP_IDRP_CLR_PND1_J1_RX_MASK                   0x00000004

#define REG_OSP_IDRP_CLR_PND1_J0_TX_SHIFT                  1
#define REG_OSP_IDRP_CLR_PND1_J0_TX_SIZE                   1
#define REG_OSP_IDRP_CLR_PND1_J0_TX_MASK                   0x00000002

#define REG_OSP_IDRP_CLR_PND1_J0_RX_SHIFT                  0
#define REG_OSP_IDRP_CLR_PND1_J0_RX_SIZE                   1
#define REG_OSP_IDRP_CLR_PND1_J0_RX_MASK                   0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CLR_PND1_FIELD( xdma_abt, xdma7, xdma6, xdma5, xdma4, xdma3, xdma2, xdma1, xdma0, gpu_p3d, gpu_ppf, gpu_pdc1, gpu_pdc0, gpu_psc1, gpu_psc0, dbg_spi, j1_tx, j1_rx, j0_tx, j0_rx ) \
    (u32)( \
    ((u32)(xdma_abt) << REG_OSP_IDRP_CLR_PND1_XDMA_ABT_SHIFT) | \
    ((u32)(xdma7) << REG_OSP_IDRP_CLR_PND1_XDMA7_SHIFT) | \
    ((u32)(xdma6) << REG_OSP_IDRP_CLR_PND1_XDMA6_SHIFT) | \
    ((u32)(xdma5) << REG_OSP_IDRP_CLR_PND1_XDMA5_SHIFT) | \
    ((u32)(xdma4) << REG_OSP_IDRP_CLR_PND1_XDMA4_SHIFT) | \
    ((u32)(xdma3) << REG_OSP_IDRP_CLR_PND1_XDMA3_SHIFT) | \
    ((u32)(xdma2) << REG_OSP_IDRP_CLR_PND1_XDMA2_SHIFT) | \
    ((u32)(xdma1) << REG_OSP_IDRP_CLR_PND1_XDMA1_SHIFT) | \
    ((u32)(xdma0) << REG_OSP_IDRP_CLR_PND1_XDMA0_SHIFT) | \
    ((u32)(gpu_p3d) << REG_OSP_IDRP_CLR_PND1_GPU_P3D_SHIFT) | \
    ((u32)(gpu_ppf) << REG_OSP_IDRP_CLR_PND1_GPU_PPF_SHIFT) | \
    ((u32)(gpu_pdc1) << REG_OSP_IDRP_CLR_PND1_GPU_PDC1_SHIFT) | \
    ((u32)(gpu_pdc0) << REG_OSP_IDRP_CLR_PND1_GPU_PDC0_SHIFT) | \
    ((u32)(gpu_psc1) << REG_OSP_IDRP_CLR_PND1_GPU_PSC1_SHIFT) | \
    ((u32)(gpu_psc0) << REG_OSP_IDRP_CLR_PND1_GPU_PSC0_SHIFT) | \
    ((u32)(dbg_spi) << REG_OSP_IDRP_CLR_PND1_DBG_SPI_SHIFT) | \
    ((u32)(j1_tx) << REG_OSP_IDRP_CLR_PND1_J1_TX_SHIFT) | \
    ((u32)(j1_rx) << REG_OSP_IDRP_CLR_PND1_J1_RX_SHIFT) | \
    ((u32)(j0_tx) << REG_OSP_IDRP_CLR_PND1_J0_TX_SHIFT) | \
    ((u32)(j0_rx) << REG_OSP_IDRP_CLR_PND1_J0_RX_SHIFT))
#endif


/* IDRP_CLR_PND2 */

#define REG_OSP_IDRP_CLR_PND2_DS_WL_SHIFT                  31
#define REG_OSP_IDRP_CLR_PND2_DS_WL_SIZE                   1
#define REG_OSP_IDRP_CLR_PND2_DS_WL_MASK                   0x80000000

#define REG_OSP_IDRP_CLR_PND2_I2C3_SHIFT                   28
#define REG_OSP_IDRP_CLR_PND2_I2C3_SIZE                    1
#define REG_OSP_IDRP_CLR_PND2_I2C3_MASK                    0x10000000

#define REG_OSP_IDRP_CLR_PND2_KEY_SHIFT                    27
#define REG_OSP_IDRP_CLR_PND2_KEY_SIZE                     1
#define REG_OSP_IDRP_CLR_PND2_KEY_MASK                     0x08000000

#define REG_OSP_IDRP_CLR_PND2_MIC_SHIFT                    26
#define REG_OSP_IDRP_CLR_PND2_MIC_SIZE                     1
#define REG_OSP_IDRP_CLR_PND2_MIC_MASK                     0x04000000

#define REG_OSP_IDRP_CLR_PND2_PDN_LGY_SHIFT                25
#define REG_OSP_IDRP_CLR_PND2_PDN_LGY_SIZE                 1
#define REG_OSP_IDRP_CLR_PND2_PDN_LGY_MASK                 0x02000000

#define REG_OSP_IDRP_CLR_PND2_PDN_WAKE_SHIFT               24
#define REG_OSP_IDRP_CLR_PND2_PDN_WAKE_SIZE                1
#define REG_OSP_IDRP_CLR_PND2_PDN_WAKE_MASK                0x01000000

#define REG_OSP_IDRP_CLR_PND2_SPI2_SHIFT                   23
#define REG_OSP_IDRP_CLR_PND2_SPI2_SIZE                    1
#define REG_OSP_IDRP_CLR_PND2_SPI2_MASK                    0x00800000

#define REG_OSP_IDRP_CLR_PND2_SPI1_SHIFT                   22
#define REG_OSP_IDRP_CLR_PND2_SPI1_SIZE                    1
#define REG_OSP_IDRP_CLR_PND2_SPI1_MASK                    0x00400000

#define REG_OSP_IDRP_CLR_PND2_I2C2_SHIFT                   21
#define REG_OSP_IDRP_CLR_PND2_I2C2_SIZE                    1
#define REG_OSP_IDRP_CLR_PND2_I2C2_MASK                    0x00200000

#define REG_OSP_IDRP_CLR_PND2_I2C1_SHIFT                   20
#define REG_OSP_IDRP_CLR_PND2_I2C1_SIZE                    1
#define REG_OSP_IDRP_CLR_PND2_I2C1_MASK                    0x00100000

#define REG_OSP_IDRP_CLR_PND2_PXI_RX_SHIFT                 19
#define REG_OSP_IDRP_CLR_PND2_PXI_RX_SIZE                  1
#define REG_OSP_IDRP_CLR_PND2_PXI_RX_MASK                  0x00080000

#define REG_OSP_IDRP_CLR_PND2_PXI_TX_SHIFT                 18
#define REG_OSP_IDRP_CLR_PND2_PXI_TX_SIZE                  1
#define REG_OSP_IDRP_CLR_PND2_PXI_TX_MASK                  0x00040000

#define REG_OSP_IDRP_CLR_PND2_CPU1_SHIFT                   17
#define REG_OSP_IDRP_CLR_PND2_CPU1_SIZE                    1
#define REG_OSP_IDRP_CLR_PND2_CPU1_MASK                    0x00020000

#define REG_OSP_IDRP_CLR_PND2_CPU0_SHIFT                   16
#define REG_OSP_IDRP_CLR_PND2_CPU0_SIZE                    1
#define REG_OSP_IDRP_CLR_PND2_CPU0_MASK                    0x00010000

#define REG_OSP_IDRP_CLR_PND2_SCLR2_SHIFT                  13
#define REG_OSP_IDRP_CLR_PND2_SCLR2_SIZE                   1
#define REG_OSP_IDRP_CLR_PND2_SCLR2_MASK                   0x00002000

#define REG_OSP_IDRP_CLR_PND2_SCLR1_SHIFT                  12
#define REG_OSP_IDRP_CLR_PND2_SCLR1_SIZE                   1
#define REG_OSP_IDRP_CLR_PND2_SCLR1_MASK                   0x00001000

#define REG_OSP_IDRP_CLR_PND2_YUV2RGB_SHIFT                11
#define REG_OSP_IDRP_CLR_PND2_YUV2RGB_SIZE                 1
#define REG_OSP_IDRP_CLR_PND2_YUV2RGB_MASK                 0x00000800

#define REG_OSP_IDRP_CLR_PND2_DSP_SHIFT                    10
#define REG_OSP_IDRP_CLR_PND2_DSP_SIZE                     1
#define REG_OSP_IDRP_CLR_PND2_DSP_MASK                     0x00000400

#define REG_OSP_IDRP_CLR_PND2_CAM2_SHIFT                   9
#define REG_OSP_IDRP_CLR_PND2_CAM2_SIZE                    1
#define REG_OSP_IDRP_CLR_PND2_CAM2_MASK                    0x00000200

#define REG_OSP_IDRP_CLR_PND2_CAM1_SHIFT                   8
#define REG_OSP_IDRP_CLR_PND2_CAM1_SIZE                    1
#define REG_OSP_IDRP_CLR_PND2_CAM1_MASK                    0x00000100

#define REG_OSP_IDRP_CLR_PND2_LGC_DET_SHIFT                6
#define REG_OSP_IDRP_CLR_PND2_LGC_DET_SIZE                 1
#define REG_OSP_IDRP_CLR_PND2_LGC_DET_MASK                 0x00000040

#define REG_OSP_IDRP_CLR_PND2_LGC_I_SHIFT                  5
#define REG_OSP_IDRP_CLR_PND2_LGC_I_SIZE                   1
#define REG_OSP_IDRP_CLR_PND2_LGC_I_MASK                   0x00000020

#define REG_OSP_IDRP_CLR_PND2_LMC_SHIFT                    4
#define REG_OSP_IDRP_CLR_PND2_LMC_SIZE                     1
#define REG_OSP_IDRP_CLR_PND2_LMC_MASK                     0x00000010

#define REG_OSP_IDRP_CLR_PND2_SD3_A_SHIFT                  3
#define REG_OSP_IDRP_CLR_PND2_SD3_A_SIZE                   1
#define REG_OSP_IDRP_CLR_PND2_SD3_A_MASK                   0x00000008

#define REG_OSP_IDRP_CLR_PND2_SD3_SHIFT                    2
#define REG_OSP_IDRP_CLR_PND2_SD3_SIZE                     1
#define REG_OSP_IDRP_CLR_PND2_SD3_MASK                     0x00000004

#define REG_OSP_IDRP_CLR_PND2_SD2_A_SHIFT                  1
#define REG_OSP_IDRP_CLR_PND2_SD2_A_SIZE                   1
#define REG_OSP_IDRP_CLR_PND2_SD2_A_MASK                   0x00000002

#define REG_OSP_IDRP_CLR_PND2_SD2_SHIFT                    0
#define REG_OSP_IDRP_CLR_PND2_SD2_SIZE                     1
#define REG_OSP_IDRP_CLR_PND2_SD2_MASK                     0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CLR_PND2_FIELD( ds_wl, i2c3, key, mic, pdn_lgy, pdn_wake, spi2, spi1, i2c2, i2c1, pxi_rx, pxi_tx, cpu1, cpu0, sclr2, sclr1, yuv2rgb, dsp, cam2, cam1, lgc_det, lgc_i, lmc, sd3_a, sd3, sd2_a, sd2 ) \
    (u32)( \
    ((u32)(ds_wl) << REG_OSP_IDRP_CLR_PND2_DS_WL_SHIFT) | \
    ((u32)(i2c3) << REG_OSP_IDRP_CLR_PND2_I2C3_SHIFT) | \
    ((u32)(key) << REG_OSP_IDRP_CLR_PND2_KEY_SHIFT) | \
    ((u32)(mic) << REG_OSP_IDRP_CLR_PND2_MIC_SHIFT) | \
    ((u32)(pdn_lgy) << REG_OSP_IDRP_CLR_PND2_PDN_LGY_SHIFT) | \
    ((u32)(pdn_wake) << REG_OSP_IDRP_CLR_PND2_PDN_WAKE_SHIFT) | \
    ((u32)(spi2) << REG_OSP_IDRP_CLR_PND2_SPI2_SHIFT) | \
    ((u32)(spi1) << REG_OSP_IDRP_CLR_PND2_SPI1_SHIFT) | \
    ((u32)(i2c2) << REG_OSP_IDRP_CLR_PND2_I2C2_SHIFT) | \
    ((u32)(i2c1) << REG_OSP_IDRP_CLR_PND2_I2C1_SHIFT) | \
    ((u32)(pxi_rx) << REG_OSP_IDRP_CLR_PND2_PXI_RX_SHIFT) | \
    ((u32)(pxi_tx) << REG_OSP_IDRP_CLR_PND2_PXI_TX_SHIFT) | \
    ((u32)(cpu1) << REG_OSP_IDRP_CLR_PND2_CPU1_SHIFT) | \
    ((u32)(cpu0) << REG_OSP_IDRP_CLR_PND2_CPU0_SHIFT) | \
    ((u32)(sclr2) << REG_OSP_IDRP_CLR_PND2_SCLR2_SHIFT) | \
    ((u32)(sclr1) << REG_OSP_IDRP_CLR_PND2_SCLR1_SHIFT) | \
    ((u32)(yuv2rgb) << REG_OSP_IDRP_CLR_PND2_YUV2RGB_SHIFT) | \
    ((u32)(dsp) << REG_OSP_IDRP_CLR_PND2_DSP_SHIFT) | \
    ((u32)(cam2) << REG_OSP_IDRP_CLR_PND2_CAM2_SHIFT) | \
    ((u32)(cam1) << REG_OSP_IDRP_CLR_PND2_CAM1_SHIFT) | \
    ((u32)(lgc_det) << REG_OSP_IDRP_CLR_PND2_LGC_DET_SHIFT) | \
    ((u32)(lgc_i) << REG_OSP_IDRP_CLR_PND2_LGC_I_SHIFT) | \
    ((u32)(lmc) << REG_OSP_IDRP_CLR_PND2_LMC_SHIFT) | \
    ((u32)(sd3_a) << REG_OSP_IDRP_CLR_PND2_SD3_A_SHIFT) | \
    ((u32)(sd3) << REG_OSP_IDRP_CLR_PND2_SD3_SHIFT) | \
    ((u32)(sd2_a) << REG_OSP_IDRP_CLR_PND2_SD2_A_SHIFT) | \
    ((u32)(sd2) << REG_OSP_IDRP_CLR_PND2_SD2_SHIFT))
#endif


/* IDRP_CLR_PND3 */

#define REG_OSP_IDRP_CLR_PND3_PMUIRQ7_SHIFT                29
#define REG_OSP_IDRP_CLR_PND3_PMUIRQ7_SIZE                 1
#define REG_OSP_IDRP_CLR_PND3_PMUIRQ7_MASK                 0x20000000

#define REG_OSP_IDRP_CLR_PND3_PMUIRQ6_SHIFT                28
#define REG_OSP_IDRP_CLR_PND3_PMUIRQ6_SIZE                 1
#define REG_OSP_IDRP_CLR_PND3_PMUIRQ6_MASK                 0x10000000

#define REG_OSP_IDRP_CLR_PND3_PMUIRQ5_SHIFT                27
#define REG_OSP_IDRP_CLR_PND3_PMUIRQ5_SIZE                 1
#define REG_OSP_IDRP_CLR_PND3_PMUIRQ5_MASK                 0x08000000

#define REG_OSP_IDRP_CLR_PND3_PMUIRQ4_SHIFT                26
#define REG_OSP_IDRP_CLR_PND3_PMUIRQ4_SIZE                 1
#define REG_OSP_IDRP_CLR_PND3_PMUIRQ4_MASK                 0x04000000

#define REG_OSP_IDRP_CLR_PND3_PMUIRQ1_SHIFT                25
#define REG_OSP_IDRP_CLR_PND3_PMUIRQ1_SIZE                 1
#define REG_OSP_IDRP_CLR_PND3_PMUIRQ1_MASK                 0x02000000

#define REG_OSP_IDRP_CLR_PND3_PMUIRQ0_SHIFT                24
#define REG_OSP_IDRP_CLR_PND3_PMUIRQ0_SIZE                 1
#define REG_OSP_IDRP_CLR_PND3_PMUIRQ0_MASK                 0x01000000

#define REG_OSP_IDRP_CLR_PND3_CGC_DET_SHIFT                21
#define REG_OSP_IDRP_CLR_PND3_CGC_DET_SIZE                 1
#define REG_OSP_IDRP_CLR_PND3_CGC_DET_MASK                 0x00200000

#define REG_OSP_IDRP_CLR_PND3_CGC_I_SHIFT                  20
#define REG_OSP_IDRP_CLR_PND3_CGC_I_SIZE                   1
#define REG_OSP_IDRP_CLR_PND3_CGC_I_MASK                   0x00100000

#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_5_SHIFT             19
#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_5_SIZE              1
#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_5_MASK              0x00080000

#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_4_SHIFT             18
#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_4_SIZE              1
#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_4_MASK              0x00040000

#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_3_SHIFT             17
#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_3_SIZE              1
#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_3_MASK              0x00020000

#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_2_SHIFT             16
#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_2_SIZE              1
#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_2_MASK              0x00010000

#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_1_SHIFT             15
#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_1_SIZE              1
#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_1_MASK              0x00008000

#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_0_SHIFT             14
#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_0_SIZE              1
#define REG_OSP_IDRP_CLR_PND3_GPIO3_18_0_MASK              0x00004000

#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_5_SHIFT             13
#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_5_SIZE              1
#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_5_MASK              0x00002000

#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_4_SHIFT             12
#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_4_SIZE              1
#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_4_MASK              0x00001000

#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_3_SHIFT             11
#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_3_SIZE              1
#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_3_MASK              0x00000800

#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_2_SHIFT             10
#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_2_SIZE              1
#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_2_MASK              0x00000400

#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_1_SHIFT             9
#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_1_SIZE              1
#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_1_MASK              0x00000200

#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_0_SHIFT             8
#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_0_SIZE              1
#define REG_OSP_IDRP_CLR_PND3_GPIO3_33_0_MASK              0x00000100

#define REG_OSP_IDRP_CLR_PND3_CTR_MCU_SHIFT                17
#define REG_OSP_IDRP_CLR_PND3_CTR_MCU_SIZE                 1
#define REG_OSP_IDRP_CLR_PND3_CTR_MCU_MASK                 0x00020000

#define REG_OSP_IDRP_CLR_PND3_RMC_SHIFT                    16
#define REG_OSP_IDRP_CLR_PND3_RMC_SIZE                     1
#define REG_OSP_IDRP_CLR_PND3_RMC_MASK                     0x00010000

#define REG_OSP_IDRP_CLR_PND3_IR_SHIFT                     10
#define REG_OSP_IDRP_CLR_PND3_IR_SIZE                      1
#define REG_OSP_IDRP_CLR_PND3_IR_MASK                      0x00000400

#define REG_OSP_IDRP_CLR_PND3_SP_SEL_SHIFT                 8
#define REG_OSP_IDRP_CLR_PND3_SP_SEL_SIZE                  1
#define REG_OSP_IDRP_CLR_PND3_SP_SEL_MASK                  0x00000100

#define REG_OSP_IDRP_CLR_PND3_TWL_DEPOP_SHIFT              6
#define REG_OSP_IDRP_CLR_PND3_TWL_DEPOP_SIZE               1
#define REG_OSP_IDRP_CLR_PND3_TWL_DEPOP_MASK               0x00000040

#define REG_OSP_IDRP_CLR_PND3_TWL_MCU_SHIFT                5
#define REG_OSP_IDRP_CLR_PND3_TWL_MCU_SIZE                 1
#define REG_OSP_IDRP_CLR_PND3_TWL_MCU_MASK                 0x00000020

#define REG_OSP_IDRP_CLR_PND3_HP_SHIFT                     4
#define REG_OSP_IDRP_CLR_PND3_HP_SIZE                      1
#define REG_OSP_IDRP_CLR_PND3_HP_MASK                      0x00000010

#define REG_OSP_IDRP_CLR_PND3_TP_SHIFT                     3
#define REG_OSP_IDRP_CLR_PND3_TP_SIZE                      1
#define REG_OSP_IDRP_CLR_PND3_TP_MASK                      0x00000008

#define REG_OSP_IDRP_CLR_PND3_COVER_R_SHIFT                2
#define REG_OSP_IDRP_CLR_PND3_COVER_R_SIZE                 1
#define REG_OSP_IDRP_CLR_PND3_COVER_R_MASK                 0x00000004

#define REG_OSP_IDRP_CLR_PND3_COVER_SHIFT                  0
#define REG_OSP_IDRP_CLR_PND3_COVER_SIZE                   1
#define REG_OSP_IDRP_CLR_PND3_COVER_MASK                   0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CLR_PND3_FIELD( pmuirq7, pmuirq6, pmuirq5, pmuirq4, pmuirq1, pmuirq0, cgc_det, cgc_i, gpio3_18_5, gpio3_18_4, gpio3_18_3, gpio3_18_2, gpio3_18_1, gpio3_18_0, gpio3_33_5, gpio3_33_4, gpio3_33_3, gpio3_33_2, gpio3_33_1, gpio3_33_0, ctr_mcu, rmc, ir, sp_sel, twl_depop, twl_mcu, hp, tp, cover_r, cover ) \
    (u32)( \
    ((u32)(pmuirq7) << REG_OSP_IDRP_CLR_PND3_PMUIRQ7_SHIFT) | \
    ((u32)(pmuirq6) << REG_OSP_IDRP_CLR_PND3_PMUIRQ6_SHIFT) | \
    ((u32)(pmuirq5) << REG_OSP_IDRP_CLR_PND3_PMUIRQ5_SHIFT) | \
    ((u32)(pmuirq4) << REG_OSP_IDRP_CLR_PND3_PMUIRQ4_SHIFT) | \
    ((u32)(pmuirq1) << REG_OSP_IDRP_CLR_PND3_PMUIRQ1_SHIFT) | \
    ((u32)(pmuirq0) << REG_OSP_IDRP_CLR_PND3_PMUIRQ0_SHIFT) | \
    ((u32)(cgc_det) << REG_OSP_IDRP_CLR_PND3_CGC_DET_SHIFT) | \
    ((u32)(cgc_i) << REG_OSP_IDRP_CLR_PND3_CGC_I_SHIFT) | \
    ((u32)(gpio3_18_5) << REG_OSP_IDRP_CLR_PND3_GPIO3_18_5_SHIFT) | \
    ((u32)(gpio3_18_4) << REG_OSP_IDRP_CLR_PND3_GPIO3_18_4_SHIFT) | \
    ((u32)(gpio3_18_3) << REG_OSP_IDRP_CLR_PND3_GPIO3_18_3_SHIFT) | \
    ((u32)(gpio3_18_2) << REG_OSP_IDRP_CLR_PND3_GPIO3_18_2_SHIFT) | \
    ((u32)(gpio3_18_1) << REG_OSP_IDRP_CLR_PND3_GPIO3_18_1_SHIFT) | \
    ((u32)(gpio3_18_0) << REG_OSP_IDRP_CLR_PND3_GPIO3_18_0_SHIFT) | \
    ((u32)(gpio3_33_5) << REG_OSP_IDRP_CLR_PND3_GPIO3_33_5_SHIFT) | \
    ((u32)(gpio3_33_4) << REG_OSP_IDRP_CLR_PND3_GPIO3_33_4_SHIFT) | \
    ((u32)(gpio3_33_3) << REG_OSP_IDRP_CLR_PND3_GPIO3_33_3_SHIFT) | \
    ((u32)(gpio3_33_2) << REG_OSP_IDRP_CLR_PND3_GPIO3_33_2_SHIFT) | \
    ((u32)(gpio3_33_1) << REG_OSP_IDRP_CLR_PND3_GPIO3_33_1_SHIFT) | \
    ((u32)(gpio3_33_0) << REG_OSP_IDRP_CLR_PND3_GPIO3_33_0_SHIFT) | \
    ((u32)(ctr_mcu) << REG_OSP_IDRP_CLR_PND3_CTR_MCU_SHIFT) | \
    ((u32)(rmc) << REG_OSP_IDRP_CLR_PND3_RMC_SHIFT) | \
    ((u32)(ir) << REG_OSP_IDRP_CLR_PND3_IR_SHIFT) | \
    ((u32)(sp_sel) << REG_OSP_IDRP_CLR_PND3_SP_SEL_SHIFT) | \
    ((u32)(twl_depop) << REG_OSP_IDRP_CLR_PND3_TWL_DEPOP_SHIFT) | \
    ((u32)(twl_mcu) << REG_OSP_IDRP_CLR_PND3_TWL_MCU_SHIFT) | \
    ((u32)(hp) << REG_OSP_IDRP_CLR_PND3_HP_SHIFT) | \
    ((u32)(tp) << REG_OSP_IDRP_CLR_PND3_TP_SHIFT) | \
    ((u32)(cover_r) << REG_OSP_IDRP_CLR_PND3_COVER_R_SHIFT) | \
    ((u32)(cover) << REG_OSP_IDRP_CLR_PND3_COVER_SHIFT))
#endif


/* IDRP_ACT0 */

#define REG_OSP_IDRP_ACT0_WDOG_SHIFT                       30
#define REG_OSP_IDRP_ACT0_WDOG_SIZE                        1
#define REG_OSP_IDRP_ACT0_WDOG_MASK                        0x40000000

#define REG_OSP_IDRP_ACT0_TM_SHIFT                         29
#define REG_OSP_IDRP_ACT0_TM_SIZE                          1
#define REG_OSP_IDRP_ACT0_TM_MASK                          0x20000000

#define REG_OSP_IDRP_ACT0_IPI15_SHIFT                      15
#define REG_OSP_IDRP_ACT0_IPI15_SIZE                       1
#define REG_OSP_IDRP_ACT0_IPI15_MASK                       0x00008000

#define REG_OSP_IDRP_ACT0_IPI14_SHIFT                      14
#define REG_OSP_IDRP_ACT0_IPI14_SIZE                       1
#define REG_OSP_IDRP_ACT0_IPI14_MASK                       0x00004000

#define REG_OSP_IDRP_ACT0_IPI13_SHIFT                      13
#define REG_OSP_IDRP_ACT0_IPI13_SIZE                       1
#define REG_OSP_IDRP_ACT0_IPI13_MASK                       0x00002000

#define REG_OSP_IDRP_ACT0_IPI12_SHIFT                      12
#define REG_OSP_IDRP_ACT0_IPI12_SIZE                       1
#define REG_OSP_IDRP_ACT0_IPI12_MASK                       0x00001000

#define REG_OSP_IDRP_ACT0_IPI11_SHIFT                      11
#define REG_OSP_IDRP_ACT0_IPI11_SIZE                       1
#define REG_OSP_IDRP_ACT0_IPI11_MASK                       0x00000800

#define REG_OSP_IDRP_ACT0_IPI10_SHIFT                      10
#define REG_OSP_IDRP_ACT0_IPI10_SIZE                       1
#define REG_OSP_IDRP_ACT0_IPI10_MASK                       0x00000400

#define REG_OSP_IDRP_ACT0_IPI9_SHIFT                       9
#define REG_OSP_IDRP_ACT0_IPI9_SIZE                        1
#define REG_OSP_IDRP_ACT0_IPI9_MASK                        0x00000200

#define REG_OSP_IDRP_ACT0_IPI8_SHIFT                       8
#define REG_OSP_IDRP_ACT0_IPI8_SIZE                        1
#define REG_OSP_IDRP_ACT0_IPI8_MASK                        0x00000100

#define REG_OSP_IDRP_ACT0_IPI7_SHIFT                       7
#define REG_OSP_IDRP_ACT0_IPI7_SIZE                        1
#define REG_OSP_IDRP_ACT0_IPI7_MASK                        0x00000080

#define REG_OSP_IDRP_ACT0_IPI6_SHIFT                       6
#define REG_OSP_IDRP_ACT0_IPI6_SIZE                        1
#define REG_OSP_IDRP_ACT0_IPI6_MASK                        0x00000040

#define REG_OSP_IDRP_ACT0_IPI5_SHIFT                       5
#define REG_OSP_IDRP_ACT0_IPI5_SIZE                        1
#define REG_OSP_IDRP_ACT0_IPI5_MASK                        0x00000020

#define REG_OSP_IDRP_ACT0_IPI4_SHIFT                       4
#define REG_OSP_IDRP_ACT0_IPI4_SIZE                        1
#define REG_OSP_IDRP_ACT0_IPI4_MASK                        0x00000010

#define REG_OSP_IDRP_ACT0_IPI3_SHIFT                       3
#define REG_OSP_IDRP_ACT0_IPI3_SIZE                        1
#define REG_OSP_IDRP_ACT0_IPI3_MASK                        0x00000008

#define REG_OSP_IDRP_ACT0_IPI2_SHIFT                       2
#define REG_OSP_IDRP_ACT0_IPI2_SIZE                        1
#define REG_OSP_IDRP_ACT0_IPI2_MASK                        0x00000004

#define REG_OSP_IDRP_ACT0_IPI1_SHIFT                       1
#define REG_OSP_IDRP_ACT0_IPI1_SIZE                        1
#define REG_OSP_IDRP_ACT0_IPI1_MASK                        0x00000002

#define REG_OSP_IDRP_ACT0_IPI0_SHIFT                       0
#define REG_OSP_IDRP_ACT0_IPI0_SIZE                        1
#define REG_OSP_IDRP_ACT0_IPI0_MASK                        0x00000001

#define REG_OSP_IDRP_ACT0_IPI_ALL_SHIFT                    0
#define REG_OSP_IDRP_ACT0_IPI_ALL_SIZE                     16
#define REG_OSP_IDRP_ACT0_IPI_ALL_MASK                     0x0000ffff

#ifndef SDK_ASM
#define REG_OSP_IDRP_ACT0_FIELD( wdog, tm, ipi15, ipi14, ipi13, ipi12, ipi11, ipi10, ipi9, ipi8, ipi7, ipi6, ipi5, ipi4, ipi3, ipi2, ipi1, ipi0, ipi_all ) \
    (u32)( \
    ((u32)(wdog) << REG_OSP_IDRP_ACT0_WDOG_SHIFT) | \
    ((u32)(tm) << REG_OSP_IDRP_ACT0_TM_SHIFT) | \
    ((u32)(ipi15) << REG_OSP_IDRP_ACT0_IPI15_SHIFT) | \
    ((u32)(ipi14) << REG_OSP_IDRP_ACT0_IPI14_SHIFT) | \
    ((u32)(ipi13) << REG_OSP_IDRP_ACT0_IPI13_SHIFT) | \
    ((u32)(ipi12) << REG_OSP_IDRP_ACT0_IPI12_SHIFT) | \
    ((u32)(ipi11) << REG_OSP_IDRP_ACT0_IPI11_SHIFT) | \
    ((u32)(ipi10) << REG_OSP_IDRP_ACT0_IPI10_SHIFT) | \
    ((u32)(ipi9) << REG_OSP_IDRP_ACT0_IPI9_SHIFT) | \
    ((u32)(ipi8) << REG_OSP_IDRP_ACT0_IPI8_SHIFT) | \
    ((u32)(ipi7) << REG_OSP_IDRP_ACT0_IPI7_SHIFT) | \
    ((u32)(ipi6) << REG_OSP_IDRP_ACT0_IPI6_SHIFT) | \
    ((u32)(ipi5) << REG_OSP_IDRP_ACT0_IPI5_SHIFT) | \
    ((u32)(ipi4) << REG_OSP_IDRP_ACT0_IPI4_SHIFT) | \
    ((u32)(ipi3) << REG_OSP_IDRP_ACT0_IPI3_SHIFT) | \
    ((u32)(ipi2) << REG_OSP_IDRP_ACT0_IPI2_SHIFT) | \
    ((u32)(ipi1) << REG_OSP_IDRP_ACT0_IPI1_SHIFT) | \
    ((u32)(ipi0) << REG_OSP_IDRP_ACT0_IPI0_SHIFT) | \
    ((u32)(ipi_all) << REG_OSP_IDRP_ACT0_IPI_ALL_SHIFT))
#endif


/* IDRP_ACT1 */

#define REG_OSP_IDRP_ACT1_XDMA_ABT_SHIFT                   25
#define REG_OSP_IDRP_ACT1_XDMA_ABT_SIZE                    1
#define REG_OSP_IDRP_ACT1_XDMA_ABT_MASK                    0x02000000

#define REG_OSP_IDRP_ACT1_XDMA7_SHIFT                      24
#define REG_OSP_IDRP_ACT1_XDMA7_SIZE                       1
#define REG_OSP_IDRP_ACT1_XDMA7_MASK                       0x01000000

#define REG_OSP_IDRP_ACT1_XDMA6_SHIFT                      22
#define REG_OSP_IDRP_ACT1_XDMA6_SIZE                       1
#define REG_OSP_IDRP_ACT1_XDMA6_MASK                       0x00400000

#define REG_OSP_IDRP_ACT1_XDMA5_SHIFT                      21
#define REG_OSP_IDRP_ACT1_XDMA5_SIZE                       1
#define REG_OSP_IDRP_ACT1_XDMA5_MASK                       0x00200000

#define REG_OSP_IDRP_ACT1_XDMA4_SHIFT                      20
#define REG_OSP_IDRP_ACT1_XDMA4_SIZE                       1
#define REG_OSP_IDRP_ACT1_XDMA4_MASK                       0x00100000

#define REG_OSP_IDRP_ACT1_XDMA3_SHIFT                      19
#define REG_OSP_IDRP_ACT1_XDMA3_SIZE                       1
#define REG_OSP_IDRP_ACT1_XDMA3_MASK                       0x00080000

#define REG_OSP_IDRP_ACT1_XDMA2_SHIFT                      18
#define REG_OSP_IDRP_ACT1_XDMA2_SIZE                       1
#define REG_OSP_IDRP_ACT1_XDMA2_MASK                       0x00040000

#define REG_OSP_IDRP_ACT1_XDMA1_SHIFT                      17
#define REG_OSP_IDRP_ACT1_XDMA1_SIZE                       1
#define REG_OSP_IDRP_ACT1_XDMA1_MASK                       0x00020000

#define REG_OSP_IDRP_ACT1_XDMA0_SHIFT                      16
#define REG_OSP_IDRP_ACT1_XDMA0_SIZE                       1
#define REG_OSP_IDRP_ACT1_XDMA0_MASK                       0x00010000

#define REG_OSP_IDRP_ACT1_GPU_P3D_SHIFT                    13
#define REG_OSP_IDRP_ACT1_GPU_P3D_SIZE                     1
#define REG_OSP_IDRP_ACT1_GPU_P3D_MASK                     0x00002000

#define REG_OSP_IDRP_ACT1_GPU_PPF_SHIFT                    12
#define REG_OSP_IDRP_ACT1_GPU_PPF_SIZE                     1
#define REG_OSP_IDRP_ACT1_GPU_PPF_MASK                     0x00001000

#define REG_OSP_IDRP_ACT1_GPU_PDC1_SHIFT                   11
#define REG_OSP_IDRP_ACT1_GPU_PDC1_SIZE                    1
#define REG_OSP_IDRP_ACT1_GPU_PDC1_MASK                    0x00000800

#define REG_OSP_IDRP_ACT1_GPU_PDC0_SHIFT                   10
#define REG_OSP_IDRP_ACT1_GPU_PDC0_SIZE                    1
#define REG_OSP_IDRP_ACT1_GPU_PDC0_MASK                    0x00000400

#define REG_OSP_IDRP_ACT1_GPU_PSC1_SHIFT                   9
#define REG_OSP_IDRP_ACT1_GPU_PSC1_SIZE                    1
#define REG_OSP_IDRP_ACT1_GPU_PSC1_MASK                    0x00000200

#define REG_OSP_IDRP_ACT1_GPU_PSC0_SHIFT                   8
#define REG_OSP_IDRP_ACT1_GPU_PSC0_SIZE                    1
#define REG_OSP_IDRP_ACT1_GPU_PSC0_MASK                    0x00000100

#define REG_OSP_IDRP_ACT1_DBG_SPI_SHIFT                    4
#define REG_OSP_IDRP_ACT1_DBG_SPI_SIZE                     1
#define REG_OSP_IDRP_ACT1_DBG_SPI_MASK                     0x00000010

#define REG_OSP_IDRP_ACT1_J1_TX_SHIFT                      3
#define REG_OSP_IDRP_ACT1_J1_TX_SIZE                       1
#define REG_OSP_IDRP_ACT1_J1_TX_MASK                       0x00000008

#define REG_OSP_IDRP_ACT1_J1_RX_SHIFT                      2
#define REG_OSP_IDRP_ACT1_J1_RX_SIZE                       1
#define REG_OSP_IDRP_ACT1_J1_RX_MASK                       0x00000004

#define REG_OSP_IDRP_ACT1_J0_TX_SHIFT                      1
#define REG_OSP_IDRP_ACT1_J0_TX_SIZE                       1
#define REG_OSP_IDRP_ACT1_J0_TX_MASK                       0x00000002

#define REG_OSP_IDRP_ACT1_J0_RX_SHIFT                      0
#define REG_OSP_IDRP_ACT1_J0_RX_SIZE                       1
#define REG_OSP_IDRP_ACT1_J0_RX_MASK                       0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_ACT1_FIELD( xdma_abt, xdma7, xdma6, xdma5, xdma4, xdma3, xdma2, xdma1, xdma0, gpu_p3d, gpu_ppf, gpu_pdc1, gpu_pdc0, gpu_psc1, gpu_psc0, dbg_spi, j1_tx, j1_rx, j0_tx, j0_rx ) \
    (u32)( \
    ((u32)(xdma_abt) << REG_OSP_IDRP_ACT1_XDMA_ABT_SHIFT) | \
    ((u32)(xdma7) << REG_OSP_IDRP_ACT1_XDMA7_SHIFT) | \
    ((u32)(xdma6) << REG_OSP_IDRP_ACT1_XDMA6_SHIFT) | \
    ((u32)(xdma5) << REG_OSP_IDRP_ACT1_XDMA5_SHIFT) | \
    ((u32)(xdma4) << REG_OSP_IDRP_ACT1_XDMA4_SHIFT) | \
    ((u32)(xdma3) << REG_OSP_IDRP_ACT1_XDMA3_SHIFT) | \
    ((u32)(xdma2) << REG_OSP_IDRP_ACT1_XDMA2_SHIFT) | \
    ((u32)(xdma1) << REG_OSP_IDRP_ACT1_XDMA1_SHIFT) | \
    ((u32)(xdma0) << REG_OSP_IDRP_ACT1_XDMA0_SHIFT) | \
    ((u32)(gpu_p3d) << REG_OSP_IDRP_ACT1_GPU_P3D_SHIFT) | \
    ((u32)(gpu_ppf) << REG_OSP_IDRP_ACT1_GPU_PPF_SHIFT) | \
    ((u32)(gpu_pdc1) << REG_OSP_IDRP_ACT1_GPU_PDC1_SHIFT) | \
    ((u32)(gpu_pdc0) << REG_OSP_IDRP_ACT1_GPU_PDC0_SHIFT) | \
    ((u32)(gpu_psc1) << REG_OSP_IDRP_ACT1_GPU_PSC1_SHIFT) | \
    ((u32)(gpu_psc0) << REG_OSP_IDRP_ACT1_GPU_PSC0_SHIFT) | \
    ((u32)(dbg_spi) << REG_OSP_IDRP_ACT1_DBG_SPI_SHIFT) | \
    ((u32)(j1_tx) << REG_OSP_IDRP_ACT1_J1_TX_SHIFT) | \
    ((u32)(j1_rx) << REG_OSP_IDRP_ACT1_J1_RX_SHIFT) | \
    ((u32)(j0_tx) << REG_OSP_IDRP_ACT1_J0_TX_SHIFT) | \
    ((u32)(j0_rx) << REG_OSP_IDRP_ACT1_J0_RX_SHIFT))
#endif


/* IDRP_ACT2 */

#define REG_OSP_IDRP_ACT2_DS_WL_SHIFT                      31
#define REG_OSP_IDRP_ACT2_DS_WL_SIZE                       1
#define REG_OSP_IDRP_ACT2_DS_WL_MASK                       0x80000000

#define REG_OSP_IDRP_ACT2_I2C3_SHIFT                       28
#define REG_OSP_IDRP_ACT2_I2C3_SIZE                        1
#define REG_OSP_IDRP_ACT2_I2C3_MASK                        0x10000000

#define REG_OSP_IDRP_ACT2_KEY_SHIFT                        27
#define REG_OSP_IDRP_ACT2_KEY_SIZE                         1
#define REG_OSP_IDRP_ACT2_KEY_MASK                         0x08000000

#define REG_OSP_IDRP_ACT2_MIC_SHIFT                        26
#define REG_OSP_IDRP_ACT2_MIC_SIZE                         1
#define REG_OSP_IDRP_ACT2_MIC_MASK                         0x04000000

#define REG_OSP_IDRP_ACT2_PDN_LGY_SHIFT                    25
#define REG_OSP_IDRP_ACT2_PDN_LGY_SIZE                     1
#define REG_OSP_IDRP_ACT2_PDN_LGY_MASK                     0x02000000

#define REG_OSP_IDRP_ACT2_PDN_WAKE_SHIFT                   24
#define REG_OSP_IDRP_ACT2_PDN_WAKE_SIZE                    1
#define REG_OSP_IDRP_ACT2_PDN_WAKE_MASK                    0x01000000

#define REG_OSP_IDRP_ACT2_SPI2_SHIFT                       23
#define REG_OSP_IDRP_ACT2_SPI2_SIZE                        1
#define REG_OSP_IDRP_ACT2_SPI2_MASK                        0x00800000

#define REG_OSP_IDRP_ACT2_SPI1_SHIFT                       22
#define REG_OSP_IDRP_ACT2_SPI1_SIZE                        1
#define REG_OSP_IDRP_ACT2_SPI1_MASK                        0x00400000

#define REG_OSP_IDRP_ACT2_I2C2_SHIFT                       21
#define REG_OSP_IDRP_ACT2_I2C2_SIZE                        1
#define REG_OSP_IDRP_ACT2_I2C2_MASK                        0x00200000

#define REG_OSP_IDRP_ACT2_I2C1_SHIFT                       20
#define REG_OSP_IDRP_ACT2_I2C1_SIZE                        1
#define REG_OSP_IDRP_ACT2_I2C1_MASK                        0x00100000

#define REG_OSP_IDRP_ACT2_PXI_RX_SHIFT                     19
#define REG_OSP_IDRP_ACT2_PXI_RX_SIZE                      1
#define REG_OSP_IDRP_ACT2_PXI_RX_MASK                      0x00080000

#define REG_OSP_IDRP_ACT2_PXI_TX_SHIFT                     18
#define REG_OSP_IDRP_ACT2_PXI_TX_SIZE                      1
#define REG_OSP_IDRP_ACT2_PXI_TX_MASK                      0x00040000

#define REG_OSP_IDRP_ACT2_CPU1_SHIFT                       17
#define REG_OSP_IDRP_ACT2_CPU1_SIZE                        1
#define REG_OSP_IDRP_ACT2_CPU1_MASK                        0x00020000

#define REG_OSP_IDRP_ACT2_CPU0_SHIFT                       16
#define REG_OSP_IDRP_ACT2_CPU0_SIZE                        1
#define REG_OSP_IDRP_ACT2_CPU0_MASK                        0x00010000

#define REG_OSP_IDRP_ACT2_SCLR2_SHIFT                      13
#define REG_OSP_IDRP_ACT2_SCLR2_SIZE                       1
#define REG_OSP_IDRP_ACT2_SCLR2_MASK                       0x00002000

#define REG_OSP_IDRP_ACT2_SCLR1_SHIFT                      12
#define REG_OSP_IDRP_ACT2_SCLR1_SIZE                       1
#define REG_OSP_IDRP_ACT2_SCLR1_MASK                       0x00001000

#define REG_OSP_IDRP_ACT2_YUV2RGB_SHIFT                    11
#define REG_OSP_IDRP_ACT2_YUV2RGB_SIZE                     1
#define REG_OSP_IDRP_ACT2_YUV2RGB_MASK                     0x00000800

#define REG_OSP_IDRP_ACT2_DSP_SHIFT                        10
#define REG_OSP_IDRP_ACT2_DSP_SIZE                         1
#define REG_OSP_IDRP_ACT2_DSP_MASK                         0x00000400

#define REG_OSP_IDRP_ACT2_CAM2_SHIFT                       9
#define REG_OSP_IDRP_ACT2_CAM2_SIZE                        1
#define REG_OSP_IDRP_ACT2_CAM2_MASK                        0x00000200

#define REG_OSP_IDRP_ACT2_CAM1_SHIFT                       8
#define REG_OSP_IDRP_ACT2_CAM1_SIZE                        1
#define REG_OSP_IDRP_ACT2_CAM1_MASK                        0x00000100

#define REG_OSP_IDRP_ACT2_LGC_DET_SHIFT                    6
#define REG_OSP_IDRP_ACT2_LGC_DET_SIZE                     1
#define REG_OSP_IDRP_ACT2_LGC_DET_MASK                     0x00000040

#define REG_OSP_IDRP_ACT2_LGC_I_SHIFT                      5
#define REG_OSP_IDRP_ACT2_LGC_I_SIZE                       1
#define REG_OSP_IDRP_ACT2_LGC_I_MASK                       0x00000020

#define REG_OSP_IDRP_ACT2_LMC_SHIFT                        4
#define REG_OSP_IDRP_ACT2_LMC_SIZE                         1
#define REG_OSP_IDRP_ACT2_LMC_MASK                         0x00000010

#define REG_OSP_IDRP_ACT2_SD3_A_SHIFT                      3
#define REG_OSP_IDRP_ACT2_SD3_A_SIZE                       1
#define REG_OSP_IDRP_ACT2_SD3_A_MASK                       0x00000008

#define REG_OSP_IDRP_ACT2_SD3_SHIFT                        2
#define REG_OSP_IDRP_ACT2_SD3_SIZE                         1
#define REG_OSP_IDRP_ACT2_SD3_MASK                         0x00000004

#define REG_OSP_IDRP_ACT2_SD2_A_SHIFT                      1
#define REG_OSP_IDRP_ACT2_SD2_A_SIZE                       1
#define REG_OSP_IDRP_ACT2_SD2_A_MASK                       0x00000002

#define REG_OSP_IDRP_ACT2_SD2_SHIFT                        0
#define REG_OSP_IDRP_ACT2_SD2_SIZE                         1
#define REG_OSP_IDRP_ACT2_SD2_MASK                         0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_ACT2_FIELD( ds_wl, i2c3, key, mic, pdn_lgy, pdn_wake, spi2, spi1, i2c2, i2c1, pxi_rx, pxi_tx, cpu1, cpu0, sclr2, sclr1, yuv2rgb, dsp, cam2, cam1, lgc_det, lgc_i, lmc, sd3_a, sd3, sd2_a, sd2 ) \
    (u32)( \
    ((u32)(ds_wl) << REG_OSP_IDRP_ACT2_DS_WL_SHIFT) | \
    ((u32)(i2c3) << REG_OSP_IDRP_ACT2_I2C3_SHIFT) | \
    ((u32)(key) << REG_OSP_IDRP_ACT2_KEY_SHIFT) | \
    ((u32)(mic) << REG_OSP_IDRP_ACT2_MIC_SHIFT) | \
    ((u32)(pdn_lgy) << REG_OSP_IDRP_ACT2_PDN_LGY_SHIFT) | \
    ((u32)(pdn_wake) << REG_OSP_IDRP_ACT2_PDN_WAKE_SHIFT) | \
    ((u32)(spi2) << REG_OSP_IDRP_ACT2_SPI2_SHIFT) | \
    ((u32)(spi1) << REG_OSP_IDRP_ACT2_SPI1_SHIFT) | \
    ((u32)(i2c2) << REG_OSP_IDRP_ACT2_I2C2_SHIFT) | \
    ((u32)(i2c1) << REG_OSP_IDRP_ACT2_I2C1_SHIFT) | \
    ((u32)(pxi_rx) << REG_OSP_IDRP_ACT2_PXI_RX_SHIFT) | \
    ((u32)(pxi_tx) << REG_OSP_IDRP_ACT2_PXI_TX_SHIFT) | \
    ((u32)(cpu1) << REG_OSP_IDRP_ACT2_CPU1_SHIFT) | \
    ((u32)(cpu0) << REG_OSP_IDRP_ACT2_CPU0_SHIFT) | \
    ((u32)(sclr2) << REG_OSP_IDRP_ACT2_SCLR2_SHIFT) | \
    ((u32)(sclr1) << REG_OSP_IDRP_ACT2_SCLR1_SHIFT) | \
    ((u32)(yuv2rgb) << REG_OSP_IDRP_ACT2_YUV2RGB_SHIFT) | \
    ((u32)(dsp) << REG_OSP_IDRP_ACT2_DSP_SHIFT) | \
    ((u32)(cam2) << REG_OSP_IDRP_ACT2_CAM2_SHIFT) | \
    ((u32)(cam1) << REG_OSP_IDRP_ACT2_CAM1_SHIFT) | \
    ((u32)(lgc_det) << REG_OSP_IDRP_ACT2_LGC_DET_SHIFT) | \
    ((u32)(lgc_i) << REG_OSP_IDRP_ACT2_LGC_I_SHIFT) | \
    ((u32)(lmc) << REG_OSP_IDRP_ACT2_LMC_SHIFT) | \
    ((u32)(sd3_a) << REG_OSP_IDRP_ACT2_SD3_A_SHIFT) | \
    ((u32)(sd3) << REG_OSP_IDRP_ACT2_SD3_SHIFT) | \
    ((u32)(sd2_a) << REG_OSP_IDRP_ACT2_SD2_A_SHIFT) | \
    ((u32)(sd2) << REG_OSP_IDRP_ACT2_SD2_SHIFT))
#endif


/* IDRP_ACT3 */

#define REG_OSP_IDRP_ACT3_PMUIRQ7_SHIFT                    29
#define REG_OSP_IDRP_ACT3_PMUIRQ7_SIZE                     1
#define REG_OSP_IDRP_ACT3_PMUIRQ7_MASK                     0x20000000

#define REG_OSP_IDRP_ACT3_PMUIRQ6_SHIFT                    28
#define REG_OSP_IDRP_ACT3_PMUIRQ6_SIZE                     1
#define REG_OSP_IDRP_ACT3_PMUIRQ6_MASK                     0x10000000

#define REG_OSP_IDRP_ACT3_PMUIRQ5_SHIFT                    27
#define REG_OSP_IDRP_ACT3_PMUIRQ5_SIZE                     1
#define REG_OSP_IDRP_ACT3_PMUIRQ5_MASK                     0x08000000

#define REG_OSP_IDRP_ACT3_PMUIRQ4_SHIFT                    26
#define REG_OSP_IDRP_ACT3_PMUIRQ4_SIZE                     1
#define REG_OSP_IDRP_ACT3_PMUIRQ4_MASK                     0x04000000

#define REG_OSP_IDRP_ACT3_PMUIRQ1_SHIFT                    25
#define REG_OSP_IDRP_ACT3_PMUIRQ1_SIZE                     1
#define REG_OSP_IDRP_ACT3_PMUIRQ1_MASK                     0x02000000

#define REG_OSP_IDRP_ACT3_PMUIRQ0_SHIFT                    24
#define REG_OSP_IDRP_ACT3_PMUIRQ0_SIZE                     1
#define REG_OSP_IDRP_ACT3_PMUIRQ0_MASK                     0x01000000

#define REG_OSP_IDRP_ACT3_CGC_DET_SHIFT                    21
#define REG_OSP_IDRP_ACT3_CGC_DET_SIZE                     1
#define REG_OSP_IDRP_ACT3_CGC_DET_MASK                     0x00200000

#define REG_OSP_IDRP_ACT3_CGC_I_SHIFT                      20
#define REG_OSP_IDRP_ACT3_CGC_I_SIZE                       1
#define REG_OSP_IDRP_ACT3_CGC_I_MASK                       0x00100000

#define REG_OSP_IDRP_ACT3_GPIO3_18_5_SHIFT                 19
#define REG_OSP_IDRP_ACT3_GPIO3_18_5_SIZE                  1
#define REG_OSP_IDRP_ACT3_GPIO3_18_5_MASK                  0x00080000

#define REG_OSP_IDRP_ACT3_GPIO3_18_4_SHIFT                 18
#define REG_OSP_IDRP_ACT3_GPIO3_18_4_SIZE                  1
#define REG_OSP_IDRP_ACT3_GPIO3_18_4_MASK                  0x00040000

#define REG_OSP_IDRP_ACT3_GPIO3_18_3_SHIFT                 17
#define REG_OSP_IDRP_ACT3_GPIO3_18_3_SIZE                  1
#define REG_OSP_IDRP_ACT3_GPIO3_18_3_MASK                  0x00020000

#define REG_OSP_IDRP_ACT3_GPIO3_18_2_SHIFT                 16
#define REG_OSP_IDRP_ACT3_GPIO3_18_2_SIZE                  1
#define REG_OSP_IDRP_ACT3_GPIO3_18_2_MASK                  0x00010000

#define REG_OSP_IDRP_ACT3_GPIO3_18_1_SHIFT                 15
#define REG_OSP_IDRP_ACT3_GPIO3_18_1_SIZE                  1
#define REG_OSP_IDRP_ACT3_GPIO3_18_1_MASK                  0x00008000

#define REG_OSP_IDRP_ACT3_GPIO3_18_0_SHIFT                 14
#define REG_OSP_IDRP_ACT3_GPIO3_18_0_SIZE                  1
#define REG_OSP_IDRP_ACT3_GPIO3_18_0_MASK                  0x00004000

#define REG_OSP_IDRP_ACT3_GPIO3_33_5_SHIFT                 13
#define REG_OSP_IDRP_ACT3_GPIO3_33_5_SIZE                  1
#define REG_OSP_IDRP_ACT3_GPIO3_33_5_MASK                  0x00002000

#define REG_OSP_IDRP_ACT3_GPIO3_33_4_SHIFT                 12
#define REG_OSP_IDRP_ACT3_GPIO3_33_4_SIZE                  1
#define REG_OSP_IDRP_ACT3_GPIO3_33_4_MASK                  0x00001000

#define REG_OSP_IDRP_ACT3_GPIO3_33_3_SHIFT                 11
#define REG_OSP_IDRP_ACT3_GPIO3_33_3_SIZE                  1
#define REG_OSP_IDRP_ACT3_GPIO3_33_3_MASK                  0x00000800

#define REG_OSP_IDRP_ACT3_GPIO3_33_2_SHIFT                 10
#define REG_OSP_IDRP_ACT3_GPIO3_33_2_SIZE                  1
#define REG_OSP_IDRP_ACT3_GPIO3_33_2_MASK                  0x00000400

#define REG_OSP_IDRP_ACT3_GPIO3_33_1_SHIFT                 9
#define REG_OSP_IDRP_ACT3_GPIO3_33_1_SIZE                  1
#define REG_OSP_IDRP_ACT3_GPIO3_33_1_MASK                  0x00000200

#define REG_OSP_IDRP_ACT3_GPIO3_33_0_SHIFT                 8
#define REG_OSP_IDRP_ACT3_GPIO3_33_0_SIZE                  1
#define REG_OSP_IDRP_ACT3_GPIO3_33_0_MASK                  0x00000100

#define REG_OSP_IDRP_ACT3_CTR_MCU_SHIFT                    17
#define REG_OSP_IDRP_ACT3_CTR_MCU_SIZE                     1
#define REG_OSP_IDRP_ACT3_CTR_MCU_MASK                     0x00020000

#define REG_OSP_IDRP_ACT3_RMC_SHIFT                        16
#define REG_OSP_IDRP_ACT3_RMC_SIZE                         1
#define REG_OSP_IDRP_ACT3_RMC_MASK                         0x00010000

#define REG_OSP_IDRP_ACT3_IR_SHIFT                         10
#define REG_OSP_IDRP_ACT3_IR_SIZE                          1
#define REG_OSP_IDRP_ACT3_IR_MASK                          0x00000400

#define REG_OSP_IDRP_ACT3_SP_SEL_SHIFT                     8
#define REG_OSP_IDRP_ACT3_SP_SEL_SIZE                      1
#define REG_OSP_IDRP_ACT3_SP_SEL_MASK                      0x00000100

#define REG_OSP_IDRP_ACT3_TWL_DEPOP_SHIFT                  6
#define REG_OSP_IDRP_ACT3_TWL_DEPOP_SIZE                   1
#define REG_OSP_IDRP_ACT3_TWL_DEPOP_MASK                   0x00000040

#define REG_OSP_IDRP_ACT3_TWL_MCU_SHIFT                    5
#define REG_OSP_IDRP_ACT3_TWL_MCU_SIZE                     1
#define REG_OSP_IDRP_ACT3_TWL_MCU_MASK                     0x00000020

#define REG_OSP_IDRP_ACT3_HP_SHIFT                         4
#define REG_OSP_IDRP_ACT3_HP_SIZE                          1
#define REG_OSP_IDRP_ACT3_HP_MASK                          0x00000010

#define REG_OSP_IDRP_ACT3_TP_SHIFT                         3
#define REG_OSP_IDRP_ACT3_TP_SIZE                          1
#define REG_OSP_IDRP_ACT3_TP_MASK                          0x00000008

#define REG_OSP_IDRP_ACT3_COVER_R_SHIFT                    2
#define REG_OSP_IDRP_ACT3_COVER_R_SIZE                     1
#define REG_OSP_IDRP_ACT3_COVER_R_MASK                     0x00000004

#define REG_OSP_IDRP_ACT3_COVER_SHIFT                      0
#define REG_OSP_IDRP_ACT3_COVER_SIZE                       1
#define REG_OSP_IDRP_ACT3_COVER_MASK                       0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_ACT3_FIELD( pmuirq7, pmuirq6, pmuirq5, pmuirq4, pmuirq1, pmuirq0, cgc_det, cgc_i, gpio3_18_5, gpio3_18_4, gpio3_18_3, gpio3_18_2, gpio3_18_1, gpio3_18_0, gpio3_33_5, gpio3_33_4, gpio3_33_3, gpio3_33_2, gpio3_33_1, gpio3_33_0, ctr_mcu, rmc, ir, sp_sel, twl_depop, twl_mcu, hp, tp, cover_r, cover ) \
    (u32)( \
    ((u32)(pmuirq7) << REG_OSP_IDRP_ACT3_PMUIRQ7_SHIFT) | \
    ((u32)(pmuirq6) << REG_OSP_IDRP_ACT3_PMUIRQ6_SHIFT) | \
    ((u32)(pmuirq5) << REG_OSP_IDRP_ACT3_PMUIRQ5_SHIFT) | \
    ((u32)(pmuirq4) << REG_OSP_IDRP_ACT3_PMUIRQ4_SHIFT) | \
    ((u32)(pmuirq1) << REG_OSP_IDRP_ACT3_PMUIRQ1_SHIFT) | \
    ((u32)(pmuirq0) << REG_OSP_IDRP_ACT3_PMUIRQ0_SHIFT) | \
    ((u32)(cgc_det) << REG_OSP_IDRP_ACT3_CGC_DET_SHIFT) | \
    ((u32)(cgc_i) << REG_OSP_IDRP_ACT3_CGC_I_SHIFT) | \
    ((u32)(gpio3_18_5) << REG_OSP_IDRP_ACT3_GPIO3_18_5_SHIFT) | \
    ((u32)(gpio3_18_4) << REG_OSP_IDRP_ACT3_GPIO3_18_4_SHIFT) | \
    ((u32)(gpio3_18_3) << REG_OSP_IDRP_ACT3_GPIO3_18_3_SHIFT) | \
    ((u32)(gpio3_18_2) << REG_OSP_IDRP_ACT3_GPIO3_18_2_SHIFT) | \
    ((u32)(gpio3_18_1) << REG_OSP_IDRP_ACT3_GPIO3_18_1_SHIFT) | \
    ((u32)(gpio3_18_0) << REG_OSP_IDRP_ACT3_GPIO3_18_0_SHIFT) | \
    ((u32)(gpio3_33_5) << REG_OSP_IDRP_ACT3_GPIO3_33_5_SHIFT) | \
    ((u32)(gpio3_33_4) << REG_OSP_IDRP_ACT3_GPIO3_33_4_SHIFT) | \
    ((u32)(gpio3_33_3) << REG_OSP_IDRP_ACT3_GPIO3_33_3_SHIFT) | \
    ((u32)(gpio3_33_2) << REG_OSP_IDRP_ACT3_GPIO3_33_2_SHIFT) | \
    ((u32)(gpio3_33_1) << REG_OSP_IDRP_ACT3_GPIO3_33_1_SHIFT) | \
    ((u32)(gpio3_33_0) << REG_OSP_IDRP_ACT3_GPIO3_33_0_SHIFT) | \
    ((u32)(ctr_mcu) << REG_OSP_IDRP_ACT3_CTR_MCU_SHIFT) | \
    ((u32)(rmc) << REG_OSP_IDRP_ACT3_RMC_SHIFT) | \
    ((u32)(ir) << REG_OSP_IDRP_ACT3_IR_SHIFT) | \
    ((u32)(sp_sel) << REG_OSP_IDRP_ACT3_SP_SEL_SHIFT) | \
    ((u32)(twl_depop) << REG_OSP_IDRP_ACT3_TWL_DEPOP_SHIFT) | \
    ((u32)(twl_mcu) << REG_OSP_IDRP_ACT3_TWL_MCU_SHIFT) | \
    ((u32)(hp) << REG_OSP_IDRP_ACT3_HP_SHIFT) | \
    ((u32)(tp) << REG_OSP_IDRP_ACT3_TP_SHIFT) | \
    ((u32)(cover_r) << REG_OSP_IDRP_ACT3_COVER_R_SHIFT) | \
    ((u32)(cover) << REG_OSP_IDRP_ACT3_COVER_SHIFT))
#endif


/* IDRP_PRIO0 */

#define REG_OSP_IDRP_PRIO0_PRIO_SHIFT                      4
#define REG_OSP_IDRP_PRIO0_PRIO_SIZE                       4
#define REG_OSP_IDRP_PRIO0_PRIO_MASK                       0xf0

#ifndef SDK_ASM
#define REG_OSP_IDRP_PRIO0_FIELD( prio ) \
    (u8)( \
    ((u32)(prio) << REG_OSP_IDRP_PRIO0_PRIO_SHIFT))
#endif


/* IDRP_TGT0 */

#define REG_OSP_IDRP_TGT0_C3_SHIFT                         3
#define REG_OSP_IDRP_TGT0_C3_SIZE                          1
#define REG_OSP_IDRP_TGT0_C3_MASK                          0x08

#define REG_OSP_IDRP_TGT0_C2_SHIFT                         2
#define REG_OSP_IDRP_TGT0_C2_SIZE                          1
#define REG_OSP_IDRP_TGT0_C2_MASK                          0x04

#define REG_OSP_IDRP_TGT0_C1_SHIFT                         1
#define REG_OSP_IDRP_TGT0_C1_SIZE                          1
#define REG_OSP_IDRP_TGT0_C1_MASK                          0x02

#define REG_OSP_IDRP_TGT0_C0_SHIFT                         0
#define REG_OSP_IDRP_TGT0_C0_SIZE                          1
#define REG_OSP_IDRP_TGT0_C0_MASK                          0x01

#ifndef SDK_ASM
#define REG_OSP_IDRP_TGT0_FIELD( c3, c2, c1, c0 ) \
    (u8)( \
    ((u32)(c3) << REG_OSP_IDRP_TGT0_C3_SHIFT) | \
    ((u32)(c2) << REG_OSP_IDRP_TGT0_C2_SHIFT) | \
    ((u32)(c1) << REG_OSP_IDRP_TGT0_C1_SHIFT) | \
    ((u32)(c0) << REG_OSP_IDRP_TGT0_C0_SHIFT))
#endif


/* IDRP_CFG0 */

#define REG_OSP_IDRP_CFG0_IPI15_1N_SHIFT                   31
#define REG_OSP_IDRP_CFG0_IPI15_1N_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI15_1N_MASK                    0x80000000

#define REG_OSP_IDRP_CFG0_IPI15_TRG_SHIFT                  30
#define REG_OSP_IDRP_CFG0_IPI15_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG0_IPI15_TRG_MASK                   0x40000000

#define REG_OSP_IDRP_CFG0_IPI14_1N_SHIFT                   29
#define REG_OSP_IDRP_CFG0_IPI14_1N_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI14_1N_MASK                    0x20000000

#define REG_OSP_IDRP_CFG0_IPI14_TRG_SHIFT                  28
#define REG_OSP_IDRP_CFG0_IPI14_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG0_IPI14_TRG_MASK                   0x10000000

#define REG_OSP_IDRP_CFG0_IPI13_1N_SHIFT                   27
#define REG_OSP_IDRP_CFG0_IPI13_1N_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI13_1N_MASK                    0x08000000

#define REG_OSP_IDRP_CFG0_IPI13_TRG_SHIFT                  26
#define REG_OSP_IDRP_CFG0_IPI13_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG0_IPI13_TRG_MASK                   0x04000000

#define REG_OSP_IDRP_CFG0_IPI12_1N_SHIFT                   25
#define REG_OSP_IDRP_CFG0_IPI12_1N_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI12_1N_MASK                    0x02000000

#define REG_OSP_IDRP_CFG0_IPI12_TRG_SHIFT                  24
#define REG_OSP_IDRP_CFG0_IPI12_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG0_IPI12_TRG_MASK                   0x01000000

#define REG_OSP_IDRP_CFG0_IPI11_1N_SHIFT                   23
#define REG_OSP_IDRP_CFG0_IPI11_1N_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI11_1N_MASK                    0x00800000

#define REG_OSP_IDRP_CFG0_IPI11_TRG_SHIFT                  22
#define REG_OSP_IDRP_CFG0_IPI11_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG0_IPI11_TRG_MASK                   0x00400000

#define REG_OSP_IDRP_CFG0_IPI10_1N_SHIFT                   21
#define REG_OSP_IDRP_CFG0_IPI10_1N_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI10_1N_MASK                    0x00200000

#define REG_OSP_IDRP_CFG0_IPI10_TRG_SHIFT                  20
#define REG_OSP_IDRP_CFG0_IPI10_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG0_IPI10_TRG_MASK                   0x00100000

#define REG_OSP_IDRP_CFG0_IPI9_1N_SHIFT                    19
#define REG_OSP_IDRP_CFG0_IPI9_1N_SIZE                     1
#define REG_OSP_IDRP_CFG0_IPI9_1N_MASK                     0x00080000

#define REG_OSP_IDRP_CFG0_IPI9_TRG_SHIFT                   18
#define REG_OSP_IDRP_CFG0_IPI9_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI9_TRG_MASK                    0x00040000

#define REG_OSP_IDRP_CFG0_IPI8_1N_SHIFT                    17
#define REG_OSP_IDRP_CFG0_IPI8_1N_SIZE                     1
#define REG_OSP_IDRP_CFG0_IPI8_1N_MASK                     0x00020000

#define REG_OSP_IDRP_CFG0_IPI8_TRG_SHIFT                   16
#define REG_OSP_IDRP_CFG0_IPI8_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI8_TRG_MASK                    0x00010000

#define REG_OSP_IDRP_CFG0_IPI7_1N_SHIFT                    15
#define REG_OSP_IDRP_CFG0_IPI7_1N_SIZE                     1
#define REG_OSP_IDRP_CFG0_IPI7_1N_MASK                     0x00008000

#define REG_OSP_IDRP_CFG0_IPI7_TRG_SHIFT                   14
#define REG_OSP_IDRP_CFG0_IPI7_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI7_TRG_MASK                    0x00004000

#define REG_OSP_IDRP_CFG0_IPI6_1N_SHIFT                    13
#define REG_OSP_IDRP_CFG0_IPI6_1N_SIZE                     1
#define REG_OSP_IDRP_CFG0_IPI6_1N_MASK                     0x00002000

#define REG_OSP_IDRP_CFG0_IPI6_TRG_SHIFT                   12
#define REG_OSP_IDRP_CFG0_IPI6_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI6_TRG_MASK                    0x00001000

#define REG_OSP_IDRP_CFG0_IPI5_1N_SHIFT                    11
#define REG_OSP_IDRP_CFG0_IPI5_1N_SIZE                     1
#define REG_OSP_IDRP_CFG0_IPI5_1N_MASK                     0x00000800

#define REG_OSP_IDRP_CFG0_IPI5_TRG_SHIFT                   10
#define REG_OSP_IDRP_CFG0_IPI5_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI5_TRG_MASK                    0x00000400

#define REG_OSP_IDRP_CFG0_IPI4_1N_SHIFT                    9
#define REG_OSP_IDRP_CFG0_IPI4_1N_SIZE                     1
#define REG_OSP_IDRP_CFG0_IPI4_1N_MASK                     0x00000200

#define REG_OSP_IDRP_CFG0_IPI4_TRG_SHIFT                   8
#define REG_OSP_IDRP_CFG0_IPI4_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI4_TRG_MASK                    0x00000100

#define REG_OSP_IDRP_CFG0_IPI3_1N_SHIFT                    7
#define REG_OSP_IDRP_CFG0_IPI3_1N_SIZE                     1
#define REG_OSP_IDRP_CFG0_IPI3_1N_MASK                     0x00000080

#define REG_OSP_IDRP_CFG0_IPI3_TRG_SHIFT                   6
#define REG_OSP_IDRP_CFG0_IPI3_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI3_TRG_MASK                    0x00000040

#define REG_OSP_IDRP_CFG0_IPI2_1N_SHIFT                    5
#define REG_OSP_IDRP_CFG0_IPI2_1N_SIZE                     1
#define REG_OSP_IDRP_CFG0_IPI2_1N_MASK                     0x00000020

#define REG_OSP_IDRP_CFG0_IPI2_TRG_SHIFT                   4
#define REG_OSP_IDRP_CFG0_IPI2_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI2_TRG_MASK                    0x00000010

#define REG_OSP_IDRP_CFG0_IPI1_1N_SHIFT                    3
#define REG_OSP_IDRP_CFG0_IPI1_1N_SIZE                     1
#define REG_OSP_IDRP_CFG0_IPI1_1N_MASK                     0x00000008

#define REG_OSP_IDRP_CFG0_IPI1_TRG_SHIFT                   2
#define REG_OSP_IDRP_CFG0_IPI1_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI1_TRG_MASK                    0x00000004

#define REG_OSP_IDRP_CFG0_IPI0_1N_SHIFT                    1
#define REG_OSP_IDRP_CFG0_IPI0_1N_SIZE                     1
#define REG_OSP_IDRP_CFG0_IPI0_1N_MASK                     0x00000002

#define REG_OSP_IDRP_CFG0_IPI0_TRG_SHIFT                   0
#define REG_OSP_IDRP_CFG0_IPI0_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG0_IPI0_TRG_MASK                    0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CFG0_FIELD( ipi15_1n, ipi15_trg, ipi14_1n, ipi14_trg, ipi13_1n, ipi13_trg, ipi12_1n, ipi12_trg, ipi11_1n, ipi11_trg, ipi10_1n, ipi10_trg, ipi9_1n, ipi9_trg, ipi8_1n, ipi8_trg, ipi7_1n, ipi7_trg, ipi6_1n, ipi6_trg, ipi5_1n, ipi5_trg, ipi4_1n, ipi4_trg, ipi3_1n, ipi3_trg, ipi2_1n, ipi2_trg, ipi1_1n, ipi1_trg, ipi0_1n, ipi0_trg ) \
    (u32)( \
    ((u32)(ipi15_1n) << REG_OSP_IDRP_CFG0_IPI15_1N_SHIFT) | \
    ((u32)(ipi15_trg) << REG_OSP_IDRP_CFG0_IPI15_TRG_SHIFT) | \
    ((u32)(ipi14_1n) << REG_OSP_IDRP_CFG0_IPI14_1N_SHIFT) | \
    ((u32)(ipi14_trg) << REG_OSP_IDRP_CFG0_IPI14_TRG_SHIFT) | \
    ((u32)(ipi13_1n) << REG_OSP_IDRP_CFG0_IPI13_1N_SHIFT) | \
    ((u32)(ipi13_trg) << REG_OSP_IDRP_CFG0_IPI13_TRG_SHIFT) | \
    ((u32)(ipi12_1n) << REG_OSP_IDRP_CFG0_IPI12_1N_SHIFT) | \
    ((u32)(ipi12_trg) << REG_OSP_IDRP_CFG0_IPI12_TRG_SHIFT) | \
    ((u32)(ipi11_1n) << REG_OSP_IDRP_CFG0_IPI11_1N_SHIFT) | \
    ((u32)(ipi11_trg) << REG_OSP_IDRP_CFG0_IPI11_TRG_SHIFT) | \
    ((u32)(ipi10_1n) << REG_OSP_IDRP_CFG0_IPI10_1N_SHIFT) | \
    ((u32)(ipi10_trg) << REG_OSP_IDRP_CFG0_IPI10_TRG_SHIFT) | \
    ((u32)(ipi9_1n) << REG_OSP_IDRP_CFG0_IPI9_1N_SHIFT) | \
    ((u32)(ipi9_trg) << REG_OSP_IDRP_CFG0_IPI9_TRG_SHIFT) | \
    ((u32)(ipi8_1n) << REG_OSP_IDRP_CFG0_IPI8_1N_SHIFT) | \
    ((u32)(ipi8_trg) << REG_OSP_IDRP_CFG0_IPI8_TRG_SHIFT) | \
    ((u32)(ipi7_1n) << REG_OSP_IDRP_CFG0_IPI7_1N_SHIFT) | \
    ((u32)(ipi7_trg) << REG_OSP_IDRP_CFG0_IPI7_TRG_SHIFT) | \
    ((u32)(ipi6_1n) << REG_OSP_IDRP_CFG0_IPI6_1N_SHIFT) | \
    ((u32)(ipi6_trg) << REG_OSP_IDRP_CFG0_IPI6_TRG_SHIFT) | \
    ((u32)(ipi5_1n) << REG_OSP_IDRP_CFG0_IPI5_1N_SHIFT) | \
    ((u32)(ipi5_trg) << REG_OSP_IDRP_CFG0_IPI5_TRG_SHIFT) | \
    ((u32)(ipi4_1n) << REG_OSP_IDRP_CFG0_IPI4_1N_SHIFT) | \
    ((u32)(ipi4_trg) << REG_OSP_IDRP_CFG0_IPI4_TRG_SHIFT) | \
    ((u32)(ipi3_1n) << REG_OSP_IDRP_CFG0_IPI3_1N_SHIFT) | \
    ((u32)(ipi3_trg) << REG_OSP_IDRP_CFG0_IPI3_TRG_SHIFT) | \
    ((u32)(ipi2_1n) << REG_OSP_IDRP_CFG0_IPI2_1N_SHIFT) | \
    ((u32)(ipi2_trg) << REG_OSP_IDRP_CFG0_IPI2_TRG_SHIFT) | \
    ((u32)(ipi1_1n) << REG_OSP_IDRP_CFG0_IPI1_1N_SHIFT) | \
    ((u32)(ipi1_trg) << REG_OSP_IDRP_CFG0_IPI1_TRG_SHIFT) | \
    ((u32)(ipi0_1n) << REG_OSP_IDRP_CFG0_IPI0_1N_SHIFT) | \
    ((u32)(ipi0_trg) << REG_OSP_IDRP_CFG0_IPI0_TRG_SHIFT))
#endif


/* IDRP_CFG1 */

#define REG_OSP_IDRP_CFG1_WDOG_1N_SHIFT                    29
#define REG_OSP_IDRP_CFG1_WDOG_1N_SIZE                     1
#define REG_OSP_IDRP_CFG1_WDOG_1N_MASK                     0x20000000

#define REG_OSP_IDRP_CFG1_WDOG_TRG_SHIFT                   28
#define REG_OSP_IDRP_CFG1_WDOG_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG1_WDOG_TRG_MASK                    0x10000000

#define REG_OSP_IDRP_CFG1_TM_1N_SHIFT                      29
#define REG_OSP_IDRP_CFG1_TM_1N_SIZE                       1
#define REG_OSP_IDRP_CFG1_TM_1N_MASK                       0x20000000

#define REG_OSP_IDRP_CFG1_TM_TRG_SHIFT                     29
#define REG_OSP_IDRP_CFG1_TM_TRG_SIZE                      1
#define REG_OSP_IDRP_CFG1_TM_TRG_MASK                      0x20000000

#ifndef SDK_ASM
#define REG_OSP_IDRP_CFG1_FIELD( wdog_1n, wdog_trg, tm_1n, tm_trg ) \
    (u32)( \
    ((u32)(wdog_1n) << REG_OSP_IDRP_CFG1_WDOG_1N_SHIFT) | \
    ((u32)(wdog_trg) << REG_OSP_IDRP_CFG1_WDOG_TRG_SHIFT) | \
    ((u32)(tm_1n) << REG_OSP_IDRP_CFG1_TM_1N_SHIFT) | \
    ((u32)(tm_trg) << REG_OSP_IDRP_CFG1_TM_TRG_SHIFT))
#endif


/* IDRP_CFG2 */

#define REG_OSP_IDRP_CFG2_GPU_P3D_1N_SHIFT                 27
#define REG_OSP_IDRP_CFG2_GPU_P3D_1N_SIZE                  1
#define REG_OSP_IDRP_CFG2_GPU_P3D_1N_MASK                  0x08000000

#define REG_OSP_IDRP_CFG2_GPU_P3D_TRG_SHIFT                26
#define REG_OSP_IDRP_CFG2_GPU_P3D_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG2_GPU_P3D_TRG_MASK                 0x04000000

#define REG_OSP_IDRP_CFG2_GPU_PPF_1N_SHIFT                 25
#define REG_OSP_IDRP_CFG2_GPU_PPF_1N_SIZE                  1
#define REG_OSP_IDRP_CFG2_GPU_PPF_1N_MASK                  0x02000000

#define REG_OSP_IDRP_CFG2_GPU_PPF_TRG_SHIFT                24
#define REG_OSP_IDRP_CFG2_GPU_PPF_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG2_GPU_PPF_TRG_MASK                 0x01000000

#define REG_OSP_IDRP_CFG2_GPU_PDC1_1N_SHIFT                23
#define REG_OSP_IDRP_CFG2_GPU_PDC1_1N_SIZE                 1
#define REG_OSP_IDRP_CFG2_GPU_PDC1_1N_MASK                 0x00800000

#define REG_OSP_IDRP_CFG2_GPU_PDC1_TRG_SHIFT               22
#define REG_OSP_IDRP_CFG2_GPU_PDC1_TRG_SIZE                1
#define REG_OSP_IDRP_CFG2_GPU_PDC1_TRG_MASK                0x00400000

#define REG_OSP_IDRP_CFG2_GPU_PDC0_1N_SHIFT                21
#define REG_OSP_IDRP_CFG2_GPU_PDC0_1N_SIZE                 1
#define REG_OSP_IDRP_CFG2_GPU_PDC0_1N_MASK                 0x00200000

#define REG_OSP_IDRP_CFG2_GPU_PDC0_TRG_SHIFT               20
#define REG_OSP_IDRP_CFG2_GPU_PDC0_TRG_SIZE                1
#define REG_OSP_IDRP_CFG2_GPU_PDC0_TRG_MASK                0x00100000

#define REG_OSP_IDRP_CFG2_GPU_PSC1_1N_SHIFT                19
#define REG_OSP_IDRP_CFG2_GPU_PSC1_1N_SIZE                 1
#define REG_OSP_IDRP_CFG2_GPU_PSC1_1N_MASK                 0x00080000

#define REG_OSP_IDRP_CFG2_GPU_PSC1_TRG_SHIFT               18
#define REG_OSP_IDRP_CFG2_GPU_PSC1_TRG_SIZE                1
#define REG_OSP_IDRP_CFG2_GPU_PSC1_TRG_MASK                0x00040000

#define REG_OSP_IDRP_CFG2_GPU_PSC0_1N_SHIFT                17
#define REG_OSP_IDRP_CFG2_GPU_PSC0_1N_SIZE                 1
#define REG_OSP_IDRP_CFG2_GPU_PSC0_1N_MASK                 0x00020000

#define REG_OSP_IDRP_CFG2_GPU_PSC0_TRG_SHIFT               16
#define REG_OSP_IDRP_CFG2_GPU_PSC0_TRG_SIZE                1
#define REG_OSP_IDRP_CFG2_GPU_PSC0_TRG_MASK                0x00010000

#define REG_OSP_IDRP_CFG2_DBG_SPI_1N_SHIFT                 9
#define REG_OSP_IDRP_CFG2_DBG_SPI_1N_SIZE                  1
#define REG_OSP_IDRP_CFG2_DBG_SPI_1N_MASK                  0x00000200

#define REG_OSP_IDRP_CFG2_DBG_SPI_TRG_SHIFT                8
#define REG_OSP_IDRP_CFG2_DBG_SPI_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG2_DBG_SPI_TRG_MASK                 0x00000100

#define REG_OSP_IDRP_CFG2_J1_TX_1N_SHIFT                   7
#define REG_OSP_IDRP_CFG2_J1_TX_1N_SIZE                    1
#define REG_OSP_IDRP_CFG2_J1_TX_1N_MASK                    0x00000080

#define REG_OSP_IDRP_CFG2_J1_TX_TRG_SHIFT                  6
#define REG_OSP_IDRP_CFG2_J1_TX_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG2_J1_TX_TRG_MASK                   0x00000040

#define REG_OSP_IDRP_CFG2_J1_RX_1N_SHIFT                   5
#define REG_OSP_IDRP_CFG2_J1_RX_1N_SIZE                    1
#define REG_OSP_IDRP_CFG2_J1_RX_1N_MASK                    0x00000020

#define REG_OSP_IDRP_CFG2_J1_RX_TRG_SHIFT                  4
#define REG_OSP_IDRP_CFG2_J1_RX_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG2_J1_RX_TRG_MASK                   0x00000010

#define REG_OSP_IDRP_CFG2_J0_TX_1N_SHIFT                   3
#define REG_OSP_IDRP_CFG2_J0_TX_1N_SIZE                    1
#define REG_OSP_IDRP_CFG2_J0_TX_1N_MASK                    0x00000008

#define REG_OSP_IDRP_CFG2_J0_TX_TRG_SHIFT                  2
#define REG_OSP_IDRP_CFG2_J0_TX_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG2_J0_TX_TRG_MASK                   0x00000004

#define REG_OSP_IDRP_CFG2_J0_RX_1N_SHIFT                   1
#define REG_OSP_IDRP_CFG2_J0_RX_1N_SIZE                    1
#define REG_OSP_IDRP_CFG2_J0_RX_1N_MASK                    0x00000002

#define REG_OSP_IDRP_CFG2_J0_RX_TRG_SHIFT                  0
#define REG_OSP_IDRP_CFG2_J0_RX_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG2_J0_RX_TRG_MASK                   0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CFG2_FIELD( gpu_p3d_1n, gpu_p3d_trg, gpu_ppf_1n, gpu_ppf_trg, gpu_pdc1_1n, gpu_pdc1_trg, gpu_pdc0_1n, gpu_pdc0_trg, gpu_psc1_1n, gpu_psc1_trg, gpu_psc0_1n, gpu_psc0_trg, dbg_spi_1n, dbg_spi_trg, j1_tx_1n, j1_tx_trg, j1_rx_1n, j1_rx_trg, j0_tx_1n, j0_tx_trg, j0_rx_1n, j0_rx_trg ) \
    (u32)( \
    ((u32)(gpu_p3d_1n) << REG_OSP_IDRP_CFG2_GPU_P3D_1N_SHIFT) | \
    ((u32)(gpu_p3d_trg) << REG_OSP_IDRP_CFG2_GPU_P3D_TRG_SHIFT) | \
    ((u32)(gpu_ppf_1n) << REG_OSP_IDRP_CFG2_GPU_PPF_1N_SHIFT) | \
    ((u32)(gpu_ppf_trg) << REG_OSP_IDRP_CFG2_GPU_PPF_TRG_SHIFT) | \
    ((u32)(gpu_pdc1_1n) << REG_OSP_IDRP_CFG2_GPU_PDC1_1N_SHIFT) | \
    ((u32)(gpu_pdc1_trg) << REG_OSP_IDRP_CFG2_GPU_PDC1_TRG_SHIFT) | \
    ((u32)(gpu_pdc0_1n) << REG_OSP_IDRP_CFG2_GPU_PDC0_1N_SHIFT) | \
    ((u32)(gpu_pdc0_trg) << REG_OSP_IDRP_CFG2_GPU_PDC0_TRG_SHIFT) | \
    ((u32)(gpu_psc1_1n) << REG_OSP_IDRP_CFG2_GPU_PSC1_1N_SHIFT) | \
    ((u32)(gpu_psc1_trg) << REG_OSP_IDRP_CFG2_GPU_PSC1_TRG_SHIFT) | \
    ((u32)(gpu_psc0_1n) << REG_OSP_IDRP_CFG2_GPU_PSC0_1N_SHIFT) | \
    ((u32)(gpu_psc0_trg) << REG_OSP_IDRP_CFG2_GPU_PSC0_TRG_SHIFT) | \
    ((u32)(dbg_spi_1n) << REG_OSP_IDRP_CFG2_DBG_SPI_1N_SHIFT) | \
    ((u32)(dbg_spi_trg) << REG_OSP_IDRP_CFG2_DBG_SPI_TRG_SHIFT) | \
    ((u32)(j1_tx_1n) << REG_OSP_IDRP_CFG2_J1_TX_1N_SHIFT) | \
    ((u32)(j1_tx_trg) << REG_OSP_IDRP_CFG2_J1_TX_TRG_SHIFT) | \
    ((u32)(j1_rx_1n) << REG_OSP_IDRP_CFG2_J1_RX_1N_SHIFT) | \
    ((u32)(j1_rx_trg) << REG_OSP_IDRP_CFG2_J1_RX_TRG_SHIFT) | \
    ((u32)(j0_tx_1n) << REG_OSP_IDRP_CFG2_J0_TX_1N_SHIFT) | \
    ((u32)(j0_tx_trg) << REG_OSP_IDRP_CFG2_J0_TX_TRG_SHIFT) | \
    ((u32)(j0_rx_1n) << REG_OSP_IDRP_CFG2_J0_RX_1N_SHIFT) | \
    ((u32)(j0_rx_trg) << REG_OSP_IDRP_CFG2_J0_RX_TRG_SHIFT))
#endif


/* IDRP_CFG3 */

#define REG_OSP_IDRP_CFG3_XDMA_ABT_1N_SHIFT                17
#define REG_OSP_IDRP_CFG3_XDMA_ABT_1N_SIZE                 1
#define REG_OSP_IDRP_CFG3_XDMA_ABT_1N_MASK                 0x00020000

#define REG_OSP_IDRP_CFG3_XDMA_ADT_TRG_SHIFT               16
#define REG_OSP_IDRP_CFG3_XDMA_ADT_TRG_SIZE                1
#define REG_OSP_IDRP_CFG3_XDMA_ADT_TRG_MASK                0x00010000

#define REG_OSP_IDRP_CFG3_XDMA7_1N_SHIFT                   15
#define REG_OSP_IDRP_CFG3_XDMA7_1N_SIZE                    1
#define REG_OSP_IDRP_CFG3_XDMA7_1N_MASK                    0x00008000

#define REG_OSP_IDRP_CFG3_XDMA7_TRG_SHIFT                  14
#define REG_OSP_IDRP_CFG3_XDMA7_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG3_XDMA7_TRG_MASK                   0x00004000

#define REG_OSP_IDRP_CFG3_XDMA6_1N_SHIFT                   13
#define REG_OSP_IDRP_CFG3_XDMA6_1N_SIZE                    1
#define REG_OSP_IDRP_CFG3_XDMA6_1N_MASK                    0x00002000

#define REG_OSP_IDRP_CFG3_XDMA6_TRG_SHIFT                  12
#define REG_OSP_IDRP_CFG3_XDMA6_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG3_XDMA6_TRG_MASK                   0x00001000

#define REG_OSP_IDRP_CFG3_XDMA5_1N_SHIFT                   11
#define REG_OSP_IDRP_CFG3_XDMA5_1N_SIZE                    1
#define REG_OSP_IDRP_CFG3_XDMA5_1N_MASK                    0x00000800

#define REG_OSP_IDRP_CFG3_XDMA5_TRG_SHIFT                  10
#define REG_OSP_IDRP_CFG3_XDMA5_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG3_XDMA5_TRG_MASK                   0x00000400

#define REG_OSP_IDRP_CFG3_XDMA4_1N_SHIFT                   9
#define REG_OSP_IDRP_CFG3_XDMA4_1N_SIZE                    1
#define REG_OSP_IDRP_CFG3_XDMA4_1N_MASK                    0x00000200

#define REG_OSP_IDRP_CFG3_XDMA4_TRG_SHIFT                  8
#define REG_OSP_IDRP_CFG3_XDMA4_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG3_XDMA4_TRG_MASK                   0x00000100

#define REG_OSP_IDRP_CFG3_XDMA3_1N_SHIFT                   7
#define REG_OSP_IDRP_CFG3_XDMA3_1N_SIZE                    1
#define REG_OSP_IDRP_CFG3_XDMA3_1N_MASK                    0x00000080

#define REG_OSP_IDRP_CFG3_XDMA3_TRG_SHIFT                  6
#define REG_OSP_IDRP_CFG3_XDMA3_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG3_XDMA3_TRG_MASK                   0x00000040

#define REG_OSP_IDRP_CFG3_XDMA2_1N_SHIFT                   5
#define REG_OSP_IDRP_CFG3_XDMA2_1N_SIZE                    1
#define REG_OSP_IDRP_CFG3_XDMA2_1N_MASK                    0x00000020

#define REG_OSP_IDRP_CFG3_XDMA2_TRG_SHIFT                  4
#define REG_OSP_IDRP_CFG3_XDMA2_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG3_XDMA2_TRG_MASK                   0x00000010

#define REG_OSP_IDRP_CFG3_XDMA1_1N_SHIFT                   3
#define REG_OSP_IDRP_CFG3_XDMA1_1N_SIZE                    1
#define REG_OSP_IDRP_CFG3_XDMA1_1N_MASK                    0x00000008

#define REG_OSP_IDRP_CFG3_XDMA1_TRG_SHIFT                  2
#define REG_OSP_IDRP_CFG3_XDMA1_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG3_XDMA1_TRG_MASK                   0x00000004

#define REG_OSP_IDRP_CFG3_XDMA0_1N_SHIFT                   1
#define REG_OSP_IDRP_CFG3_XDMA0_1N_SIZE                    1
#define REG_OSP_IDRP_CFG3_XDMA0_1N_MASK                    0x00000002

#define REG_OSP_IDRP_CFG3_XDMA0_TRG_SHIFT                  0
#define REG_OSP_IDRP_CFG3_XDMA0_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG3_XDMA0_TRG_MASK                   0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CFG3_FIELD( xdma_abt_1n, xdma_adt_trg, xdma7_1n, xdma7_trg, xdma6_1n, xdma6_trg, xdma5_1n, xdma5_trg, xdma4_1n, xdma4_trg, xdma3_1n, xdma3_trg, xdma2_1n, xdma2_trg, xdma1_1n, xdma1_trg, xdma0_1n, xdma0_trg ) \
    (u32)( \
    ((u32)(xdma_abt_1n) << REG_OSP_IDRP_CFG3_XDMA_ABT_1N_SHIFT) | \
    ((u32)(xdma_adt_trg) << REG_OSP_IDRP_CFG3_XDMA_ADT_TRG_SHIFT) | \
    ((u32)(xdma7_1n) << REG_OSP_IDRP_CFG3_XDMA7_1N_SHIFT) | \
    ((u32)(xdma7_trg) << REG_OSP_IDRP_CFG3_XDMA7_TRG_SHIFT) | \
    ((u32)(xdma6_1n) << REG_OSP_IDRP_CFG3_XDMA6_1N_SHIFT) | \
    ((u32)(xdma6_trg) << REG_OSP_IDRP_CFG3_XDMA6_TRG_SHIFT) | \
    ((u32)(xdma5_1n) << REG_OSP_IDRP_CFG3_XDMA5_1N_SHIFT) | \
    ((u32)(xdma5_trg) << REG_OSP_IDRP_CFG3_XDMA5_TRG_SHIFT) | \
    ((u32)(xdma4_1n) << REG_OSP_IDRP_CFG3_XDMA4_1N_SHIFT) | \
    ((u32)(xdma4_trg) << REG_OSP_IDRP_CFG3_XDMA4_TRG_SHIFT) | \
    ((u32)(xdma3_1n) << REG_OSP_IDRP_CFG3_XDMA3_1N_SHIFT) | \
    ((u32)(xdma3_trg) << REG_OSP_IDRP_CFG3_XDMA3_TRG_SHIFT) | \
    ((u32)(xdma2_1n) << REG_OSP_IDRP_CFG3_XDMA2_1N_SHIFT) | \
    ((u32)(xdma2_trg) << REG_OSP_IDRP_CFG3_XDMA2_TRG_SHIFT) | \
    ((u32)(xdma1_1n) << REG_OSP_IDRP_CFG3_XDMA1_1N_SHIFT) | \
    ((u32)(xdma1_trg) << REG_OSP_IDRP_CFG3_XDMA1_TRG_SHIFT) | \
    ((u32)(xdma0_1n) << REG_OSP_IDRP_CFG3_XDMA0_1N_SHIFT) | \
    ((u32)(xdma0_trg) << REG_OSP_IDRP_CFG3_XDMA0_TRG_SHIFT))
#endif


/* IDRP_CFG4 */

#define REG_OSP_IDRP_CFG4_SCLR2_1N_SHIFT                   27
#define REG_OSP_IDRP_CFG4_SCLR2_1N_SIZE                    1
#define REG_OSP_IDRP_CFG4_SCLR2_1N_MASK                    0x08000000

#define REG_OSP_IDRP_CFG4_SCLR2_TRG_SHIFT                  26
#define REG_OSP_IDRP_CFG4_SCLR2_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG4_SCLR2_TRG_MASK                   0x04000000

#define REG_OSP_IDRP_CFG4_SCLR1_1N_SHIFT                   25
#define REG_OSP_IDRP_CFG4_SCLR1_1N_SIZE                    1
#define REG_OSP_IDRP_CFG4_SCLR1_1N_MASK                    0x02000000

#define REG_OSP_IDRP_CFG4_SCLR1_TRG_SHIFT                  24
#define REG_OSP_IDRP_CFG4_SCLR1_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG4_SCLR1_TRG_MASK                   0x01000000

#define REG_OSP_IDRP_CFG4_YUV2RGB_1N_SHIFT                 23
#define REG_OSP_IDRP_CFG4_YUV2RGB_1N_SIZE                  1
#define REG_OSP_IDRP_CFG4_YUV2RGB_1N_MASK                  0x00800000

#define REG_OSP_IDRP_CFG4_YUV2RGB_TRG_SHIFT                22
#define REG_OSP_IDRP_CFG4_YUV2RGB_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG4_YUV2RGB_TRG_MASK                 0x00400000

#define REG_OSP_IDRP_CFG4_DSP_1N_SHIFT                     21
#define REG_OSP_IDRP_CFG4_DSP_1N_SIZE                      1
#define REG_OSP_IDRP_CFG4_DSP_1N_MASK                      0x00200000

#define REG_OSP_IDRP_CFG4_DSP_TRG_SHIFT                    20
#define REG_OSP_IDRP_CFG4_DSP_TRG_SIZE                     1
#define REG_OSP_IDRP_CFG4_DSP_TRG_MASK                     0x00100000

#define REG_OSP_IDRP_CFG4_CAM2_1N_SHIFT                    19
#define REG_OSP_IDRP_CFG4_CAM2_1N_SIZE                     1
#define REG_OSP_IDRP_CFG4_CAM2_1N_MASK                     0x00080000

#define REG_OSP_IDRP_CFG4_CAM2_TRG_SHIFT                   18
#define REG_OSP_IDRP_CFG4_CAM2_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG4_CAM2_TRG_MASK                    0x00040000

#define REG_OSP_IDRP_CFG4_CAM1_1N_SHIFT                    17
#define REG_OSP_IDRP_CFG4_CAM1_1N_SIZE                     1
#define REG_OSP_IDRP_CFG4_CAM1_1N_MASK                     0x00020000

#define REG_OSP_IDRP_CFG4_CAM1_TRG_SHIFT                   16
#define REG_OSP_IDRP_CFG4_CAM1_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG4_CAM1_TRG_MASK                    0x00010000

#define REG_OSP_IDRP_CFG4_LGC_DET_1N_SHIFT                 13
#define REG_OSP_IDRP_CFG4_LGC_DET_1N_SIZE                  1
#define REG_OSP_IDRP_CFG4_LGC_DET_1N_MASK                  0x00002000

#define REG_OSP_IDRP_CFG4_LGC_DET_TRG_SHIFT                12
#define REG_OSP_IDRP_CFG4_LGC_DET_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG4_LGC_DET_TRG_MASK                 0x00001000

#define REG_OSP_IDRP_CFG4_LGC_I_1N_SHIFT                   11
#define REG_OSP_IDRP_CFG4_LGC_I_1N_SIZE                    1
#define REG_OSP_IDRP_CFG4_LGC_I_1N_MASK                    0x00000800

#define REG_OSP_IDRP_CFG4_LGC_I_TRG_SHIFT                  10
#define REG_OSP_IDRP_CFG4_LGC_I_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG4_LGC_I_TRG_MASK                   0x00000400

#define REG_OSP_IDRP_CFG4_LMC_1N_SHIFT                     9
#define REG_OSP_IDRP_CFG4_LMC_1N_SIZE                      1
#define REG_OSP_IDRP_CFG4_LMC_1N_MASK                      0x00000200

#define REG_OSP_IDRP_CFG4_LMC_TRG_SHIFT                    8
#define REG_OSP_IDRP_CFG4_LMC_TRG_SIZE                     1
#define REG_OSP_IDRP_CFG4_LMC_TRG_MASK                     0x00000100

#define REG_OSP_IDRP_CFG4_SD3_A_1N_SHIFT                   7
#define REG_OSP_IDRP_CFG4_SD3_A_1N_SIZE                    1
#define REG_OSP_IDRP_CFG4_SD3_A_1N_MASK                    0x00000080

#define REG_OSP_IDRP_CFG4_SD3_A_TRG_SHIFT                  6
#define REG_OSP_IDRP_CFG4_SD3_A_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG4_SD3_A_TRG_MASK                   0x00000040

#define REG_OSP_IDRP_CFG4_SD3_1N_SHIFT                     5
#define REG_OSP_IDRP_CFG4_SD3_1N_SIZE                      1
#define REG_OSP_IDRP_CFG4_SD3_1N_MASK                      0x00000020

#define REG_OSP_IDRP_CFG4_SD3_TRG_SHIFT                    4
#define REG_OSP_IDRP_CFG4_SD3_TRG_SIZE                     1
#define REG_OSP_IDRP_CFG4_SD3_TRG_MASK                     0x00000010

#define REG_OSP_IDRP_CFG4_SD2_A_1N_SHIFT                   3
#define REG_OSP_IDRP_CFG4_SD2_A_1N_SIZE                    1
#define REG_OSP_IDRP_CFG4_SD2_A_1N_MASK                    0x00000008

#define REG_OSP_IDRP_CFG4_SD2_A_TRG_SHIFT                  2
#define REG_OSP_IDRP_CFG4_SD2_A_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG4_SD2_A_TRG_MASK                   0x00000004

#define REG_OSP_IDRP_CFG4_SD2_1N_SHIFT                     1
#define REG_OSP_IDRP_CFG4_SD2_1N_SIZE                      1
#define REG_OSP_IDRP_CFG4_SD2_1N_MASK                      0x00000002

#define REG_OSP_IDRP_CFG4_SD2_TRG_SHIFT                    0
#define REG_OSP_IDRP_CFG4_SD2_TRG_SIZE                     1
#define REG_OSP_IDRP_CFG4_SD2_TRG_MASK                     0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CFG4_FIELD( sclr2_1n, sclr2_trg, sclr1_1n, sclr1_trg, yuv2rgb_1n, yuv2rgb_trg, dsp_1n, dsp_trg, cam2_1n, cam2_trg, cam1_1n, cam1_trg, lgc_det_1n, lgc_det_trg, lgc_i_1n, lgc_i_trg, lmc_1n, lmc_trg, sd3_a_1n, sd3_a_trg, sd3_1n, sd3_trg, sd2_a_1n, sd2_a_trg, sd2_1n, sd2_trg ) \
    (u32)( \
    ((u32)(sclr2_1n) << REG_OSP_IDRP_CFG4_SCLR2_1N_SHIFT) | \
    ((u32)(sclr2_trg) << REG_OSP_IDRP_CFG4_SCLR2_TRG_SHIFT) | \
    ((u32)(sclr1_1n) << REG_OSP_IDRP_CFG4_SCLR1_1N_SHIFT) | \
    ((u32)(sclr1_trg) << REG_OSP_IDRP_CFG4_SCLR1_TRG_SHIFT) | \
    ((u32)(yuv2rgb_1n) << REG_OSP_IDRP_CFG4_YUV2RGB_1N_SHIFT) | \
    ((u32)(yuv2rgb_trg) << REG_OSP_IDRP_CFG4_YUV2RGB_TRG_SHIFT) | \
    ((u32)(dsp_1n) << REG_OSP_IDRP_CFG4_DSP_1N_SHIFT) | \
    ((u32)(dsp_trg) << REG_OSP_IDRP_CFG4_DSP_TRG_SHIFT) | \
    ((u32)(cam2_1n) << REG_OSP_IDRP_CFG4_CAM2_1N_SHIFT) | \
    ((u32)(cam2_trg) << REG_OSP_IDRP_CFG4_CAM2_TRG_SHIFT) | \
    ((u32)(cam1_1n) << REG_OSP_IDRP_CFG4_CAM1_1N_SHIFT) | \
    ((u32)(cam1_trg) << REG_OSP_IDRP_CFG4_CAM1_TRG_SHIFT) | \
    ((u32)(lgc_det_1n) << REG_OSP_IDRP_CFG4_LGC_DET_1N_SHIFT) | \
    ((u32)(lgc_det_trg) << REG_OSP_IDRP_CFG4_LGC_DET_TRG_SHIFT) | \
    ((u32)(lgc_i_1n) << REG_OSP_IDRP_CFG4_LGC_I_1N_SHIFT) | \
    ((u32)(lgc_i_trg) << REG_OSP_IDRP_CFG4_LGC_I_TRG_SHIFT) | \
    ((u32)(lmc_1n) << REG_OSP_IDRP_CFG4_LMC_1N_SHIFT) | \
    ((u32)(lmc_trg) << REG_OSP_IDRP_CFG4_LMC_TRG_SHIFT) | \
    ((u32)(sd3_a_1n) << REG_OSP_IDRP_CFG4_SD3_A_1N_SHIFT) | \
    ((u32)(sd3_a_trg) << REG_OSP_IDRP_CFG4_SD3_A_TRG_SHIFT) | \
    ((u32)(sd3_1n) << REG_OSP_IDRP_CFG4_SD3_1N_SHIFT) | \
    ((u32)(sd3_trg) << REG_OSP_IDRP_CFG4_SD3_TRG_SHIFT) | \
    ((u32)(sd2_a_1n) << REG_OSP_IDRP_CFG4_SD2_A_1N_SHIFT) | \
    ((u32)(sd2_a_trg) << REG_OSP_IDRP_CFG4_SD2_A_TRG_SHIFT) | \
    ((u32)(sd2_1n) << REG_OSP_IDRP_CFG4_SD2_1N_SHIFT) | \
    ((u32)(sd2_trg) << REG_OSP_IDRP_CFG4_SD2_TRG_SHIFT))
#endif


/* IDRP_CFG5 */

#define REG_OSP_IDRP_CFG5_DS_WL_1N_SHIFT                   31
#define REG_OSP_IDRP_CFG5_DS_WL_1N_SIZE                    1
#define REG_OSP_IDRP_CFG5_DS_WL_1N_MASK                    0x80000000

#define REG_OSP_IDRP_CFG5_DS_WL_TRG_SHIFT                  30
#define REG_OSP_IDRP_CFG5_DS_WL_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG5_DS_WL_TRG_MASK                   0x40000000

#define REG_OSP_IDRP_CFG5_KEY_1N_SHIFT                     23
#define REG_OSP_IDRP_CFG5_KEY_1N_SIZE                      1
#define REG_OSP_IDRP_CFG5_KEY_1N_MASK                      0x00800000

#define REG_OSP_IDRP_CFG5_KEY_TRG_SHIFT                    22
#define REG_OSP_IDRP_CFG5_KEY_TRG_SIZE                     1
#define REG_OSP_IDRP_CFG5_KEY_TRG_MASK                     0x00400000

#define REG_OSP_IDRP_CFG5_MIC_1N_SHIFT                     21
#define REG_OSP_IDRP_CFG5_MIC_1N_SIZE                      1
#define REG_OSP_IDRP_CFG5_MIC_1N_MASK                      0x00200000

#define REG_OSP_IDRP_CFG5_MIC_TRG_SHIFT                    20
#define REG_OSP_IDRP_CFG5_MIC_TRG_SIZE                     1
#define REG_OSP_IDRP_CFG5_MIC_TRG_MASK                     0x00100000

#define REG_OSP_IDRP_CFG5_PDN_LGY_1N_SHIFT                 19
#define REG_OSP_IDRP_CFG5_PDN_LGY_1N_SIZE                  1
#define REG_OSP_IDRP_CFG5_PDN_LGY_1N_MASK                  0x00080000

#define REG_OSP_IDRP_CFG5_PDN_LGY_TRG_SHIFT                18
#define REG_OSP_IDRP_CFG5_PDN_LGY_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG5_PDN_LGY_TRG_MASK                 0x00040000

#define REG_OSP_IDRP_CFG5_PDN_WAKE_1N_SHIFT                17
#define REG_OSP_IDRP_CFG5_PDN_WAKE_1N_SIZE                 1
#define REG_OSP_IDRP_CFG5_PDN_WAKE_1N_MASK                 0x00020000

#define REG_OSP_IDRP_CFG5_PDN_WAKE_TRG_SHIFT               16
#define REG_OSP_IDRP_CFG5_PDN_WAKE_TRG_SIZE                1
#define REG_OSP_IDRP_CFG5_PDN_WAKE_TRG_MASK                0x00010000

#define REG_OSP_IDRP_CFG5_SPI2_1N_SHIFT                    15
#define REG_OSP_IDRP_CFG5_SPI2_1N_SIZE                     1
#define REG_OSP_IDRP_CFG5_SPI2_1N_MASK                     0x00008000

#define REG_OSP_IDRP_CFG5_SPI2_TRG_SHIFT                   14
#define REG_OSP_IDRP_CFG5_SPI2_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG5_SPI2_TRG_MASK                    0x00004000

#define REG_OSP_IDRP_CFG5_SPI1_1N_SHIFT                    13
#define REG_OSP_IDRP_CFG5_SPI1_1N_SIZE                     1
#define REG_OSP_IDRP_CFG5_SPI1_1N_MASK                     0x00002000

#define REG_OSP_IDRP_CFG5_SPI1_TRG_SHIFT                   12
#define REG_OSP_IDRP_CFG5_SPI1_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG5_SPI1_TRG_MASK                    0x00001000

#define REG_OSP_IDRP_CFG5_I2C2_1N_SHIFT                    11
#define REG_OSP_IDRP_CFG5_I2C2_1N_SIZE                     1
#define REG_OSP_IDRP_CFG5_I2C2_1N_MASK                     0x00000800

#define REG_OSP_IDRP_CFG5_I2C2_TRG_SHIFT                   10
#define REG_OSP_IDRP_CFG5_I2C2_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG5_I2C2_TRG_MASK                    0x00000400

#define REG_OSP_IDRP_CFG5_I2C1_1N_SHIFT                    9
#define REG_OSP_IDRP_CFG5_I2C1_1N_SIZE                     1
#define REG_OSP_IDRP_CFG5_I2C1_1N_MASK                     0x00000200

#define REG_OSP_IDRP_CFG5_I2C1_TRG_SHIFT                   8
#define REG_OSP_IDRP_CFG5_I2C1_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG5_I2C1_TRG_MASK                    0x00000100

#define REG_OSP_IDRP_CFG5_PXI_RX_1N_SHIFT                  7
#define REG_OSP_IDRP_CFG5_PXI_RX_1N_SIZE                   1
#define REG_OSP_IDRP_CFG5_PXI_RX_1N_MASK                   0x00000080

#define REG_OSP_IDRP_CFG5_PXI_RX_TRG_SHIFT                 6
#define REG_OSP_IDRP_CFG5_PXI_RX_TRG_SIZE                  1
#define REG_OSP_IDRP_CFG5_PXI_RX_TRG_MASK                  0x00000040

#define REG_OSP_IDRP_CFG5_PXI_TX_1N_SHIFT                  5
#define REG_OSP_IDRP_CFG5_PXI_TX_1N_SIZE                   1
#define REG_OSP_IDRP_CFG5_PXI_TX_1N_MASK                   0x00000020

#define REG_OSP_IDRP_CFG5_PXI_TX_TRG_SHIFT                 4
#define REG_OSP_IDRP_CFG5_PXI_TX_TRG_SIZE                  1
#define REG_OSP_IDRP_CFG5_PXI_TX_TRG_MASK                  0x00000010

#define REG_OSP_IDRP_CFG5_CPU1_1N_SHIFT                    3
#define REG_OSP_IDRP_CFG5_CPU1_1N_SIZE                     1
#define REG_OSP_IDRP_CFG5_CPU1_1N_MASK                     0x00000008

#define REG_OSP_IDRP_CFG5_CPU1_TRG_SHIFT                   2
#define REG_OSP_IDRP_CFG5_CPU1_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG5_CPU1_TRG_MASK                    0x00000004

#define REG_OSP_IDRP_CFG5_CPU0_1N_SHIFT                    1
#define REG_OSP_IDRP_CFG5_CPU0_1N_SIZE                     1
#define REG_OSP_IDRP_CFG5_CPU0_1N_MASK                     0x00000002

#define REG_OSP_IDRP_CFG5_CPU0_TRG_SHIFT                   0
#define REG_OSP_IDRP_CFG5_CPU0_TRG_SIZE                    1
#define REG_OSP_IDRP_CFG5_CPU0_TRG_MASK                    0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CFG5_FIELD( ds_wl_1n, ds_wl_trg, key_1n, key_trg, mic_1n, mic_trg, pdn_lgy_1n, pdn_lgy_trg, pdn_wake_1n, pdn_wake_trg, spi2_1n, spi2_trg, spi1_1n, spi1_trg, i2c2_1n, i2c2_trg, i2c1_1n, i2c1_trg, pxi_rx_1n, pxi_rx_trg, pxi_tx_1n, pxi_tx_trg, cpu1_1n, cpu1_trg, cpu0_1n, cpu0_trg ) \
    (u32)( \
    ((u32)(ds_wl_1n) << REG_OSP_IDRP_CFG5_DS_WL_1N_SHIFT) | \
    ((u32)(ds_wl_trg) << REG_OSP_IDRP_CFG5_DS_WL_TRG_SHIFT) | \
    ((u32)(key_1n) << REG_OSP_IDRP_CFG5_KEY_1N_SHIFT) | \
    ((u32)(key_trg) << REG_OSP_IDRP_CFG5_KEY_TRG_SHIFT) | \
    ((u32)(mic_1n) << REG_OSP_IDRP_CFG5_MIC_1N_SHIFT) | \
    ((u32)(mic_trg) << REG_OSP_IDRP_CFG5_MIC_TRG_SHIFT) | \
    ((u32)(pdn_lgy_1n) << REG_OSP_IDRP_CFG5_PDN_LGY_1N_SHIFT) | \
    ((u32)(pdn_lgy_trg) << REG_OSP_IDRP_CFG5_PDN_LGY_TRG_SHIFT) | \
    ((u32)(pdn_wake_1n) << REG_OSP_IDRP_CFG5_PDN_WAKE_1N_SHIFT) | \
    ((u32)(pdn_wake_trg) << REG_OSP_IDRP_CFG5_PDN_WAKE_TRG_SHIFT) | \
    ((u32)(spi2_1n) << REG_OSP_IDRP_CFG5_SPI2_1N_SHIFT) | \
    ((u32)(spi2_trg) << REG_OSP_IDRP_CFG5_SPI2_TRG_SHIFT) | \
    ((u32)(spi1_1n) << REG_OSP_IDRP_CFG5_SPI1_1N_SHIFT) | \
    ((u32)(spi1_trg) << REG_OSP_IDRP_CFG5_SPI1_TRG_SHIFT) | \
    ((u32)(i2c2_1n) << REG_OSP_IDRP_CFG5_I2C2_1N_SHIFT) | \
    ((u32)(i2c2_trg) << REG_OSP_IDRP_CFG5_I2C2_TRG_SHIFT) | \
    ((u32)(i2c1_1n) << REG_OSP_IDRP_CFG5_I2C1_1N_SHIFT) | \
    ((u32)(i2c1_trg) << REG_OSP_IDRP_CFG5_I2C1_TRG_SHIFT) | \
    ((u32)(pxi_rx_1n) << REG_OSP_IDRP_CFG5_PXI_RX_1N_SHIFT) | \
    ((u32)(pxi_rx_trg) << REG_OSP_IDRP_CFG5_PXI_RX_TRG_SHIFT) | \
    ((u32)(pxi_tx_1n) << REG_OSP_IDRP_CFG5_PXI_TX_1N_SHIFT) | \
    ((u32)(pxi_tx_trg) << REG_OSP_IDRP_CFG5_PXI_TX_TRG_SHIFT) | \
    ((u32)(cpu1_1n) << REG_OSP_IDRP_CFG5_CPU1_1N_SHIFT) | \
    ((u32)(cpu1_trg) << REG_OSP_IDRP_CFG5_CPU1_TRG_SHIFT) | \
    ((u32)(cpu0_1n) << REG_OSP_IDRP_CFG5_CPU0_1N_SHIFT) | \
    ((u32)(cpu0_trg) << REG_OSP_IDRP_CFG5_CPU0_TRG_SHIFT))
#endif


/* IDRP_CFG6 */

#define REG_OSP_IDRP_CFG6_GPIO3_33_7_1N_SHIFT              31
#define REG_OSP_IDRP_CFG6_GPIO3_33_7_1N_SIZE               1
#define REG_OSP_IDRP_CFG6_GPIO3_33_7_1N_MASK               0x80000000

#define REG_OSP_IDRP_CFG6_GPIO3_33_7_TRG_SHIFT             30
#define REG_OSP_IDRP_CFG6_GPIO3_33_7_TRG_SIZE              1
#define REG_OSP_IDRP_CFG6_GPIO3_33_7_TRG_MASK              0x40000000

#define REG_OSP_IDRP_CFG6_GPIO3_33_6_1N_SHIFT              29
#define REG_OSP_IDRP_CFG6_GPIO3_33_6_1N_SIZE               1
#define REG_OSP_IDRP_CFG6_GPIO3_33_6_1N_MASK               0x20000000

#define REG_OSP_IDRP_CFG6_GPIO3_33_6_TRG_SHIFT             28
#define REG_OSP_IDRP_CFG6_GPIO3_33_6_TRG_SIZE              1
#define REG_OSP_IDRP_CFG6_GPIO3_33_6_TRG_MASK              0x10000000

#define REG_OSP_IDRP_CFG6_GPIO3_33_5_1N_SHIFT              27
#define REG_OSP_IDRP_CFG6_GPIO3_33_5_1N_SIZE               1
#define REG_OSP_IDRP_CFG6_GPIO3_33_5_1N_MASK               0x08000000

#define REG_OSP_IDRP_CFG6_GPIO3_33_5_TRG_SHIFT             26
#define REG_OSP_IDRP_CFG6_GPIO3_33_5_TRG_SIZE              1
#define REG_OSP_IDRP_CFG6_GPIO3_33_5_TRG_MASK              0x04000000

#define REG_OSP_IDRP_CFG6_GPIO3_33_4_1N_SHIFT              25
#define REG_OSP_IDRP_CFG6_GPIO3_33_4_1N_SIZE               1
#define REG_OSP_IDRP_CFG6_GPIO3_33_4_1N_MASK               0x02000000

#define REG_OSP_IDRP_CFG6_GPIO3_33_4_TRG_SHIFT             24
#define REG_OSP_IDRP_CFG6_GPIO3_33_4_TRG_SIZE              1
#define REG_OSP_IDRP_CFG6_GPIO3_33_4_TRG_MASK              0x01000000

#define REG_OSP_IDRP_CFG6_GPIO3_33_3_1N_SHIFT              23
#define REG_OSP_IDRP_CFG6_GPIO3_33_3_1N_SIZE               1
#define REG_OSP_IDRP_CFG6_GPIO3_33_3_1N_MASK               0x00800000

#define REG_OSP_IDRP_CFG6_GPIO3_33_3_TRG_SHIFT             22
#define REG_OSP_IDRP_CFG6_GPIO3_33_3_TRG_SIZE              1
#define REG_OSP_IDRP_CFG6_GPIO3_33_3_TRG_MASK              0x00400000

#define REG_OSP_IDRP_CFG6_GPIO3_33_2_1N_SHIFT              21
#define REG_OSP_IDRP_CFG6_GPIO3_33_2_1N_SIZE               1
#define REG_OSP_IDRP_CFG6_GPIO3_33_2_1N_MASK               0x00200000

#define REG_OSP_IDRP_CFG6_GPIO3_33_2_TRG_SHIFT             20
#define REG_OSP_IDRP_CFG6_GPIO3_33_2_TRG_SIZE              1
#define REG_OSP_IDRP_CFG6_GPIO3_33_2_TRG_MASK              0x00100000

#define REG_OSP_IDRP_CFG6_GPIO3_33_1_1N_SHIFT              19
#define REG_OSP_IDRP_CFG6_GPIO3_33_1_1N_SIZE               1
#define REG_OSP_IDRP_CFG6_GPIO3_33_1_1N_MASK               0x00080000

#define REG_OSP_IDRP_CFG6_GPIO3_33_1_TRG_SHIFT             18
#define REG_OSP_IDRP_CFG6_GPIO3_33_1_TRG_SIZE              1
#define REG_OSP_IDRP_CFG6_GPIO3_33_1_TRG_MASK              0x00040000

#define REG_OSP_IDRP_CFG6_GPIO3_33_0_1N_SHIFT              17
#define REG_OSP_IDRP_CFG6_GPIO3_33_0_1N_SIZE               1
#define REG_OSP_IDRP_CFG6_GPIO3_33_0_1N_MASK               0x00020000

#define REG_OSP_IDRP_CFG6_GPIO3_33_0_TRG_SHIFT             16
#define REG_OSP_IDRP_CFG6_GPIO3_33_0_TRG_SIZE              1
#define REG_OSP_IDRP_CFG6_GPIO3_33_0_TRG_MASK              0x00010000

#define REG_OSP_IDRP_CFG6_IR_1N_SHIFT                      21
#define REG_OSP_IDRP_CFG6_IR_1N_SIZE                       1
#define REG_OSP_IDRP_CFG6_IR_1N_MASK                       0x00200000

#define REG_OSP_IDRP_CFG6_IR_TRG_SHIFT                     20
#define REG_OSP_IDRP_CFG6_IR_TRG_SIZE                      1
#define REG_OSP_IDRP_CFG6_IR_TRG_MASK                      0x00100000

#define REG_OSP_IDRP_CFG6_SP_SEL_1N_SHIFT                  17
#define REG_OSP_IDRP_CFG6_SP_SEL_1N_SIZE                   1
#define REG_OSP_IDRP_CFG6_SP_SEL_1N_MASK                   0x00020000

#define REG_OSP_IDRP_CFG6_SP_SEL_TRG_SHIFT                 16
#define REG_OSP_IDRP_CFG6_SP_SEL_TRG_SIZE                  1
#define REG_OSP_IDRP_CFG6_SP_SEL_TRG_MASK                  0x00010000

#define REG_OSP_IDRP_CFG6_TWL_DEPOP_1N_SHIFT               13
#define REG_OSP_IDRP_CFG6_TWL_DEPOP_1N_SIZE                1
#define REG_OSP_IDRP_CFG6_TWL_DEPOP_1N_MASK                0x00002000

#define REG_OSP_IDRP_CFG6_TWL_DEPOP_TRG_SHIFT              12
#define REG_OSP_IDRP_CFG6_TWL_DEPOP_TRG_SIZE               1
#define REG_OSP_IDRP_CFG6_TWL_DEPOP_TRG_MASK               0x00001000

#define REG_OSP_IDRP_CFG6_TWL_MCU_1N_SHIFT                 11
#define REG_OSP_IDRP_CFG6_TWL_MCU_1N_SIZE                  1
#define REG_OSP_IDRP_CFG6_TWL_MCU_1N_MASK                  0x00000800

#define REG_OSP_IDRP_CFG6_TWL_MCU_TRG_SHIFT                10
#define REG_OSP_IDRP_CFG6_TWL_MCU_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG6_TWL_MCU_TRG_MASK                 0x00000400

#define REG_OSP_IDRP_CFG6_HP_1N_SHIFT                      9
#define REG_OSP_IDRP_CFG6_HP_1N_SIZE                       1
#define REG_OSP_IDRP_CFG6_HP_1N_MASK                       0x00000200

#define REG_OSP_IDRP_CFG6_HP_TRG_SHIFT                     8
#define REG_OSP_IDRP_CFG6_HP_TRG_SIZE                      1
#define REG_OSP_IDRP_CFG6_HP_TRG_MASK                      0x00000100

#define REG_OSP_IDRP_CFG6_RTC_1N_SHIFT                     3
#define REG_OSP_IDRP_CFG6_RTC_1N_SIZE                      1
#define REG_OSP_IDRP_CFG6_RTC_1N_MASK                      0x00000008

#define REG_OSP_IDRP_CFG6_RTC_TRG_SHIFT                    2
#define REG_OSP_IDRP_CFG6_RTC_TRG_SIZE                     1
#define REG_OSP_IDRP_CFG6_RTC_TRG_MASK                     0x00000004

#define REG_OSP_IDRP_CFG6_COVER_1N_SHIFT                   1
#define REG_OSP_IDRP_CFG6_COVER_1N_SIZE                    1
#define REG_OSP_IDRP_CFG6_COVER_1N_MASK                    0x00000002

#define REG_OSP_IDRP_CFG6_COVER_TRG_SHIFT                  0
#define REG_OSP_IDRP_CFG6_COVER_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG6_COVER_TRG_MASK                   0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CFG6_FIELD( gpio3_33_7_1n, gpio3_33_7_trg, gpio3_33_6_1n, gpio3_33_6_trg, gpio3_33_5_1n, gpio3_33_5_trg, gpio3_33_4_1n, gpio3_33_4_trg, gpio3_33_3_1n, gpio3_33_3_trg, gpio3_33_2_1n, gpio3_33_2_trg, gpio3_33_1_1n, gpio3_33_1_trg, gpio3_33_0_1n, gpio3_33_0_trg, ir_1n, ir_trg, sp_sel_1n, sp_sel_trg, twl_depop_1n, twl_depop_trg, twl_mcu_1n, twl_mcu_trg, hp_1n, hp_trg, rtc_1n, rtc_trg, cover_1n, cover_trg ) \
    (u32)( \
    ((u32)(gpio3_33_7_1n) << REG_OSP_IDRP_CFG6_GPIO3_33_7_1N_SHIFT) | \
    ((u32)(gpio3_33_7_trg) << REG_OSP_IDRP_CFG6_GPIO3_33_7_TRG_SHIFT) | \
    ((u32)(gpio3_33_6_1n) << REG_OSP_IDRP_CFG6_GPIO3_33_6_1N_SHIFT) | \
    ((u32)(gpio3_33_6_trg) << REG_OSP_IDRP_CFG6_GPIO3_33_6_TRG_SHIFT) | \
    ((u32)(gpio3_33_5_1n) << REG_OSP_IDRP_CFG6_GPIO3_33_5_1N_SHIFT) | \
    ((u32)(gpio3_33_5_trg) << REG_OSP_IDRP_CFG6_GPIO3_33_5_TRG_SHIFT) | \
    ((u32)(gpio3_33_4_1n) << REG_OSP_IDRP_CFG6_GPIO3_33_4_1N_SHIFT) | \
    ((u32)(gpio3_33_4_trg) << REG_OSP_IDRP_CFG6_GPIO3_33_4_TRG_SHIFT) | \
    ((u32)(gpio3_33_3_1n) << REG_OSP_IDRP_CFG6_GPIO3_33_3_1N_SHIFT) | \
    ((u32)(gpio3_33_3_trg) << REG_OSP_IDRP_CFG6_GPIO3_33_3_TRG_SHIFT) | \
    ((u32)(gpio3_33_2_1n) << REG_OSP_IDRP_CFG6_GPIO3_33_2_1N_SHIFT) | \
    ((u32)(gpio3_33_2_trg) << REG_OSP_IDRP_CFG6_GPIO3_33_2_TRG_SHIFT) | \
    ((u32)(gpio3_33_1_1n) << REG_OSP_IDRP_CFG6_GPIO3_33_1_1N_SHIFT) | \
    ((u32)(gpio3_33_1_trg) << REG_OSP_IDRP_CFG6_GPIO3_33_1_TRG_SHIFT) | \
    ((u32)(gpio3_33_0_1n) << REG_OSP_IDRP_CFG6_GPIO3_33_0_1N_SHIFT) | \
    ((u32)(gpio3_33_0_trg) << REG_OSP_IDRP_CFG6_GPIO3_33_0_TRG_SHIFT) | \
    ((u32)(ir_1n) << REG_OSP_IDRP_CFG6_IR_1N_SHIFT) | \
    ((u32)(ir_trg) << REG_OSP_IDRP_CFG6_IR_TRG_SHIFT) | \
    ((u32)(sp_sel_1n) << REG_OSP_IDRP_CFG6_SP_SEL_1N_SHIFT) | \
    ((u32)(sp_sel_trg) << REG_OSP_IDRP_CFG6_SP_SEL_TRG_SHIFT) | \
    ((u32)(twl_depop_1n) << REG_OSP_IDRP_CFG6_TWL_DEPOP_1N_SHIFT) | \
    ((u32)(twl_depop_trg) << REG_OSP_IDRP_CFG6_TWL_DEPOP_TRG_SHIFT) | \
    ((u32)(twl_mcu_1n) << REG_OSP_IDRP_CFG6_TWL_MCU_1N_SHIFT) | \
    ((u32)(twl_mcu_trg) << REG_OSP_IDRP_CFG6_TWL_MCU_TRG_SHIFT) | \
    ((u32)(hp_1n) << REG_OSP_IDRP_CFG6_HP_1N_SHIFT) | \
    ((u32)(hp_trg) << REG_OSP_IDRP_CFG6_HP_TRG_SHIFT) | \
    ((u32)(rtc_1n) << REG_OSP_IDRP_CFG6_RTC_1N_SHIFT) | \
    ((u32)(rtc_trg) << REG_OSP_IDRP_CFG6_RTC_TRG_SHIFT) | \
    ((u32)(cover_1n) << REG_OSP_IDRP_CFG6_COVER_1N_SHIFT) | \
    ((u32)(cover_trg) << REG_OSP_IDRP_CFG6_COVER_TRG_SHIFT))
#endif


/* IDRP_CFG7 */

#define REG_OSP_IDRP_CFG7_PMUIRQ7_1N_SHIFT                 27
#define REG_OSP_IDRP_CFG7_PMUIRQ7_1N_SIZE                  1
#define REG_OSP_IDRP_CFG7_PMUIRQ7_1N_MASK                  0x08000000

#define REG_OSP_IDRP_CFG7_PMUIRQ7_TRG_SHIFT                26
#define REG_OSP_IDRP_CFG7_PMUIRQ7_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG7_PMUIRQ7_TRG_MASK                 0x04000000

#define REG_OSP_IDRP_CFG7_PMUIRQ6_1N_SHIFT                 25
#define REG_OSP_IDRP_CFG7_PMUIRQ6_1N_SIZE                  1
#define REG_OSP_IDRP_CFG7_PMUIRQ6_1N_MASK                  0x02000000

#define REG_OSP_IDRP_CFG7_PMUIRQ6_TRG_SHIFT                24
#define REG_OSP_IDRP_CFG7_PMUIRQ6_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG7_PMUIRQ6_TRG_MASK                 0x01000000

#define REG_OSP_IDRP_CFG7_PMUIRQ5_1N_SHIFT                 23
#define REG_OSP_IDRP_CFG7_PMUIRQ5_1N_SIZE                  1
#define REG_OSP_IDRP_CFG7_PMUIRQ5_1N_MASK                  0x00800000

#define REG_OSP_IDRP_CFG7_PMUIRQ5_TRG_SHIFT                22
#define REG_OSP_IDRP_CFG7_PMUIRQ5_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG7_PMUIRQ5_TRG_MASK                 0x00400000

#define REG_OSP_IDRP_CFG7_PMUIRQ4_1N_SHIFT                 21
#define REG_OSP_IDRP_CFG7_PMUIRQ4_1N_SIZE                  1
#define REG_OSP_IDRP_CFG7_PMUIRQ4_1N_MASK                  0x00200000

#define REG_OSP_IDRP_CFG7_PMUIRQ4_TRG_SHIFT                20
#define REG_OSP_IDRP_CFG7_PMUIRQ4_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG7_PMUIRQ4_TRG_MASK                 0x00100000

#define REG_OSP_IDRP_CFG7_PMUIRQ1_1N_SHIFT                 19
#define REG_OSP_IDRP_CFG7_PMUIRQ1_1N_SIZE                  1
#define REG_OSP_IDRP_CFG7_PMUIRQ1_1N_MASK                  0x00080000

#define REG_OSP_IDRP_CFG7_PMUIRQ1_TRG_SHIFT                18
#define REG_OSP_IDRP_CFG7_PMUIRQ1_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG7_PMUIRQ1_TRG_MASK                 0x00040000

#define REG_OSP_IDRP_CFG7_PMUIRQ0_1N_SHIFT                 17
#define REG_OSP_IDRP_CFG7_PMUIRQ0_1N_SIZE                  1
#define REG_OSP_IDRP_CFG7_PMUIRQ0_1N_MASK                  0x00020000

#define REG_OSP_IDRP_CFG7_PMUIRQ0_TRG_SHIFT                16
#define REG_OSP_IDRP_CFG7_PMUIRQ0_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG7_PMUIRQ0_TRG_MASK                 0x00010000

#define REG_OSP_IDRP_CFG7_CGC_DET_1N_SHIFT                 11
#define REG_OSP_IDRP_CFG7_CGC_DET_1N_SIZE                  1
#define REG_OSP_IDRP_CFG7_CGC_DET_1N_MASK                  0x00000800

#define REG_OSP_IDRP_CFG7_CGC_DET_TRG_SHIFT                11
#define REG_OSP_IDRP_CFG7_CGC_DET_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG7_CGC_DET_TRG_MASK                 0x00000800

#define REG_OSP_IDRP_CFG7_CGC_I_1N_SHIFT                   8
#define REG_OSP_IDRP_CFG7_CGC_I_1N_SIZE                    1
#define REG_OSP_IDRP_CFG7_CGC_I_1N_MASK                    0x00000100

#define REG_OSP_IDRP_CFG7_CGC_I_TRG_SHIFT                  8
#define REG_OSP_IDRP_CFG7_CGC_I_TRG_SIZE                   1
#define REG_OSP_IDRP_CFG7_CGC_I_TRG_MASK                   0x00000100

#define REG_OSP_IDRP_CFG7_GPIO3_18_3_1N_SHIFT              7
#define REG_OSP_IDRP_CFG7_GPIO3_18_3_1N_SIZE               1
#define REG_OSP_IDRP_CFG7_GPIO3_18_3_1N_MASK               0x00000080

#define REG_OSP_IDRP_CFG7_GPIO3_18_3_TRG_SHIFT             6
#define REG_OSP_IDRP_CFG7_GPIO3_18_3_TRG_SIZE              1
#define REG_OSP_IDRP_CFG7_GPIO3_18_3_TRG_MASK              0x00000040

#define REG_OSP_IDRP_CFG7_GPIO3_18_2_1N_SHIFT              5
#define REG_OSP_IDRP_CFG7_GPIO3_18_2_1N_SIZE               1
#define REG_OSP_IDRP_CFG7_GPIO3_18_2_1N_MASK               0x00000020

#define REG_OSP_IDRP_CFG7_GPIO3_18_2_TRG_SHIFT             4
#define REG_OSP_IDRP_CFG7_GPIO3_18_2_TRG_SIZE              1
#define REG_OSP_IDRP_CFG7_GPIO3_18_2_TRG_MASK              0x00000010

#define REG_OSP_IDRP_CFG7_GPIO3_18_1_1N_SHIFT              3
#define REG_OSP_IDRP_CFG7_GPIO3_18_1_1N_SIZE               1
#define REG_OSP_IDRP_CFG7_GPIO3_18_1_1N_MASK               0x00000008

#define REG_OSP_IDRP_CFG7_GPIO3_18_1_TRG_SHIFT             2
#define REG_OSP_IDRP_CFG7_GPIO3_18_1_TRG_SIZE              1
#define REG_OSP_IDRP_CFG7_GPIO3_18_1_TRG_MASK              0x00000004

#define REG_OSP_IDRP_CFG7_GPIO3_18_0_1N_SHIFT              1
#define REG_OSP_IDRP_CFG7_GPIO3_18_0_1N_SIZE               1
#define REG_OSP_IDRP_CFG7_GPIO3_18_0_1N_MASK               0x00000002

#define REG_OSP_IDRP_CFG7_GPIO3_18_0_TRG_SHIFT             0
#define REG_OSP_IDRP_CFG7_GPIO3_18_0_TRG_SIZE              1
#define REG_OSP_IDRP_CFG7_GPIO3_18_0_TRG_MASK              0x00000001

#define REG_OSP_IDRP_CFG7_CTR_MCU_1N_SHIFT                 3
#define REG_OSP_IDRP_CFG7_CTR_MCU_1N_SIZE                  1
#define REG_OSP_IDRP_CFG7_CTR_MCU_1N_MASK                  0x00000008

#define REG_OSP_IDRP_CFG7_CTR_MCU_TRG_SHIFT                2
#define REG_OSP_IDRP_CFG7_CTR_MCU_TRG_SIZE                 1
#define REG_OSP_IDRP_CFG7_CTR_MCU_TRG_MASK                 0x00000004

#define REG_OSP_IDRP_CFG7_RMC_1N_SHIFT                     1
#define REG_OSP_IDRP_CFG7_RMC_1N_SIZE                      1
#define REG_OSP_IDRP_CFG7_RMC_1N_MASK                      0x00000002

#define REG_OSP_IDRP_CFG7_RMC_TRG_SHIFT                    0
#define REG_OSP_IDRP_CFG7_RMC_TRG_SIZE                     1
#define REG_OSP_IDRP_CFG7_RMC_TRG_MASK                     0x00000001

#ifndef SDK_ASM
#define REG_OSP_IDRP_CFG7_FIELD( pmuirq7_1n, pmuirq7_trg, pmuirq6_1n, pmuirq6_trg, pmuirq5_1n, pmuirq5_trg, pmuirq4_1n, pmuirq4_trg, pmuirq1_1n, pmuirq1_trg, pmuirq0_1n, pmuirq0_trg, cgc_det_1n, cgc_det_trg, cgc_i_1n, cgc_i_trg, gpio3_18_3_1n, gpio3_18_3_trg, gpio3_18_2_1n, gpio3_18_2_trg, gpio3_18_1_1n, gpio3_18_1_trg, gpio3_18_0_1n, gpio3_18_0_trg, ctr_mcu_1n, ctr_mcu_trg, rmc_1n, rmc_trg ) \
    (u32)( \
    ((u32)(pmuirq7_1n) << REG_OSP_IDRP_CFG7_PMUIRQ7_1N_SHIFT) | \
    ((u32)(pmuirq7_trg) << REG_OSP_IDRP_CFG7_PMUIRQ7_TRG_SHIFT) | \
    ((u32)(pmuirq6_1n) << REG_OSP_IDRP_CFG7_PMUIRQ6_1N_SHIFT) | \
    ((u32)(pmuirq6_trg) << REG_OSP_IDRP_CFG7_PMUIRQ6_TRG_SHIFT) | \
    ((u32)(pmuirq5_1n) << REG_OSP_IDRP_CFG7_PMUIRQ5_1N_SHIFT) | \
    ((u32)(pmuirq5_trg) << REG_OSP_IDRP_CFG7_PMUIRQ5_TRG_SHIFT) | \
    ((u32)(pmuirq4_1n) << REG_OSP_IDRP_CFG7_PMUIRQ4_1N_SHIFT) | \
    ((u32)(pmuirq4_trg) << REG_OSP_IDRP_CFG7_PMUIRQ4_TRG_SHIFT) | \
    ((u32)(pmuirq1_1n) << REG_OSP_IDRP_CFG7_PMUIRQ1_1N_SHIFT) | \
    ((u32)(pmuirq1_trg) << REG_OSP_IDRP_CFG7_PMUIRQ1_TRG_SHIFT) | \
    ((u32)(pmuirq0_1n) << REG_OSP_IDRP_CFG7_PMUIRQ0_1N_SHIFT) | \
    ((u32)(pmuirq0_trg) << REG_OSP_IDRP_CFG7_PMUIRQ0_TRG_SHIFT) | \
    ((u32)(cgc_det_1n) << REG_OSP_IDRP_CFG7_CGC_DET_1N_SHIFT) | \
    ((u32)(cgc_det_trg) << REG_OSP_IDRP_CFG7_CGC_DET_TRG_SHIFT) | \
    ((u32)(cgc_i_1n) << REG_OSP_IDRP_CFG7_CGC_I_1N_SHIFT) | \
    ((u32)(cgc_i_trg) << REG_OSP_IDRP_CFG7_CGC_I_TRG_SHIFT) | \
    ((u32)(gpio3_18_3_1n) << REG_OSP_IDRP_CFG7_GPIO3_18_3_1N_SHIFT) | \
    ((u32)(gpio3_18_3_trg) << REG_OSP_IDRP_CFG7_GPIO3_18_3_TRG_SHIFT) | \
    ((u32)(gpio3_18_2_1n) << REG_OSP_IDRP_CFG7_GPIO3_18_2_1N_SHIFT) | \
    ((u32)(gpio3_18_2_trg) << REG_OSP_IDRP_CFG7_GPIO3_18_2_TRG_SHIFT) | \
    ((u32)(gpio3_18_1_1n) << REG_OSP_IDRP_CFG7_GPIO3_18_1_1N_SHIFT) | \
    ((u32)(gpio3_18_1_trg) << REG_OSP_IDRP_CFG7_GPIO3_18_1_TRG_SHIFT) | \
    ((u32)(gpio3_18_0_1n) << REG_OSP_IDRP_CFG7_GPIO3_18_0_1N_SHIFT) | \
    ((u32)(gpio3_18_0_trg) << REG_OSP_IDRP_CFG7_GPIO3_18_0_TRG_SHIFT) | \
    ((u32)(ctr_mcu_1n) << REG_OSP_IDRP_CFG7_CTR_MCU_1N_SHIFT) | \
    ((u32)(ctr_mcu_trg) << REG_OSP_IDRP_CFG7_CTR_MCU_TRG_SHIFT) | \
    ((u32)(rmc_1n) << REG_OSP_IDRP_CFG7_RMC_1N_SHIFT) | \
    ((u32)(rmc_trg) << REG_OSP_IDRP_CFG7_RMC_TRG_SHIFT))
#endif


/* IDRP_SW */

#define REG_OSP_IDRP_SW_FT_SHIFT                           24
#define REG_OSP_IDRP_SW_FT_SIZE                            2
#define REG_OSP_IDRP_SW_FT_MASK                            0x03000000

#define REG_OSP_IDRP_SW_LIST_SHIFT                         16
#define REG_OSP_IDRP_SW_LIST_SIZE                          8
#define REG_OSP_IDRP_SW_LIST_MASK                          0x00ff0000

#define REG_OSP_IDRP_SW_ID_SHIFT                           0
#define REG_OSP_IDRP_SW_ID_SIZE                            10
#define REG_OSP_IDRP_SW_ID_MASK                            0x000003ff

#ifndef SDK_ASM
#define REG_OSP_IDRP_SW_FIELD( ft, list, id ) \
    (u32)( \
    ((u32)(ft) << REG_OSP_IDRP_SW_FT_SHIFT) | \
    ((u32)(list) << REG_OSP_IDRP_SW_LIST_SHIFT) | \
    ((u32)(id) << REG_OSP_IDRP_SW_ID_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_OSP_H_ */
#endif
