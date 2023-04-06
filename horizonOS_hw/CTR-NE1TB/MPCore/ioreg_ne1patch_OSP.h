/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-NE1TB/MPCore/ioreg_ne1patch_OSP.h

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
#ifndef NN_HW_CTR_NE1TB_MPCORE_IOREG_NE1PATCH_OSP_H_
#define NN_HW_CTR_NE1TB_MPCORE_IOREG_NE1PATCH_OSP_H_

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

#define REG_OSP_CPUIP_ACK_CPU_SRC_SHIFT                    3
#define REG_OSP_CPUIP_ACK_CPU_SRC_SIZE                     10
#define REG_OSP_CPUIP_ACK_CPU_SRC_MASK                     0x00001ff8

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

#define REG_OSP_CPUIP_EOI_CPU_SRC_SHIFT                    3
#define REG_OSP_CPUIP_EOI_CPU_SRC_SIZE                     10
#define REG_OSP_CPUIP_EOI_CPU_SRC_MASK                     0x00001ff8

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

#define REG_OSP_CPUIP_HI_PND_CPU_SRC_SHIFT                 3
#define REG_OSP_CPUIP_HI_PND_CPU_SRC_SIZE                  10
#define REG_OSP_CPUIP_HI_PND_CPU_SRC_MASK                  0x00001ff8

#define REG_OSP_CPUIP_HI_PND_ID_SHIFT                      0
#define REG_OSP_CPUIP_HI_PND_ID_SIZE                       10
#define REG_OSP_CPUIP_HI_PND_ID_MASK                       0x000003ff

#ifndef SDK_ASM
#define REG_OSP_CPUIP_HI_PND_FIELD( cpu_src, id ) \
    (u32)( \
    ((u32)(cpu_src) << REG_OSP_CPUIP_HI_PND_CPU_SRC_SHIFT) | \
    ((u32)(id) << REG_OSP_CPUIP_HI_PND_ID_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_NE1TB_MPCORE_IOREG_NE1PATCH_OSP_H_ */
#endif
