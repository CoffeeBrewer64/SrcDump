/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-NE1TB/MPCore/ioreg_ne1patch_NE1SYS.h

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
#ifndef NN_HW_CTR_NE1TB_MPCORE_IOREG_NE1PATCH_NE1SYS_H_
#define NN_HW_CTR_NE1TB_MPCORE_IOREG_NE1PATCH_NE1SYS_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* SYS_BOOT_ID */

#define REG_SYS_BOOT_ID_OFFSET                             0x004
#define REG_SYS_BOOT_ID_ADDR                               (HW_NE1SYS_REG + REG_SYS_BOOT_ID_OFFSET)
#define reg_NE1SYS_SYS_BOOT_ID                             (*( REGType32v *) REG_SYS_BOOT_ID_ADDR)

/* SYS_RESET_STATUS */

#define REG_SYS_RESET_STATUS_OFFSET                        0x00c
#define REG_SYS_RESET_STATUS_ADDR                          (HW_NE1SYS_REG + REG_SYS_RESET_STATUS_OFFSET)
#define reg_NE1SYS_SYS_RESET_STATUS                        (*( REGType32v *) REG_SYS_RESET_STATUS_ADDR)

/* SYS_VERSION */

#define REG_SYS_VERSION_OFFSET                             0x01c
#define REG_SYS_VERSION_ADDR                               (HW_NE1SYS_REG + REG_SYS_VERSION_OFFSET)
#define reg_NE1SYS_SYS_VERSION                             (*( REGType32v *) REG_SYS_VERSION_ADDR)

/* SYS_MPCORE_STATUS */

#define REG_SYS_MPCORE_STATUS_OFFSET                       0x108
#define REG_SYS_MPCORE_STATUS_ADDR                         (HW_NE1SYS_REG + REG_SYS_MPCORE_STATUS_OFFSET)
#define reg_NE1SYS_SYS_MPCORE_STATUS                       (*( REGType32v *) REG_SYS_MPCORE_STATUS_ADDR)

/* SYS_MPCORE_STATUS_MONITOR */

#define REG_SYS_MPCORE_STATUS_MONITOR_OFFSET               0x10c
#define REG_SYS_MPCORE_STATUS_MONITOR_ADDR                 (HW_NE1SYS_REG + REG_SYS_MPCORE_STATUS_MONITOR_OFFSET)
#define reg_NE1SYS_SYS_MPCORE_STATUS_MONITOR               (*(const REGType32v *) REG_SYS_MPCORE_STATUS_MONITOR_ADDR)

/* SYS_WTOP_MODE */

#define REG_SYS_WTOP_MODE_OFFSET                           0x11c
#define REG_SYS_WTOP_MODE_ADDR                             (HW_NE1SYS_REG + REG_SYS_WTOP_MODE_OFFSET)
#define reg_NE1SYS_SYS_WTOP_MODE                           (*( REGType32v *) REG_SYS_WTOP_MODE_ADDR)


/*
 * Definitions of Register fields
 */


/* SYS_BOOT_ID */

#define REG_NE1SYS_SYS_BOOT_ID_MODE_SHIFT                  12
#define REG_NE1SYS_SYS_BOOT_ID_MODE_SIZE                   1
#define REG_NE1SYS_SYS_BOOT_ID_MODE_MASK                   0x00001000

#ifndef SDK_ASM
#define REG_NE1SYS_SYS_BOOT_ID_FIELD( mode ) \
    (u32)( \
    ((u32)(mode) << REG_NE1SYS_SYS_BOOT_ID_MODE_SHIFT))
#endif


/* SYS_RESET_STATUS */

#define REG_NE1SYS_SYS_RESET_STATUS_RST_STAT_SHIFT         17
#define REG_NE1SYS_SYS_RESET_STATUS_RST_STAT_SIZE          1
#define REG_NE1SYS_SYS_RESET_STATUS_RST_STAT_MASK          0x00020000

#define REG_NE1SYS_SYS_RESET_STATUS_RST_SHIFT              0
#define REG_NE1SYS_SYS_RESET_STATUS_RST_SIZE               1
#define REG_NE1SYS_SYS_RESET_STATUS_RST_MASK               0x00000001

#ifndef SDK_ASM
#define REG_NE1SYS_SYS_RESET_STATUS_FIELD( rst_stat, rst ) \
    (u32)( \
    ((u32)(rst_stat) << REG_NE1SYS_SYS_RESET_STATUS_RST_STAT_SHIFT) | \
    ((u32)(rst) << REG_NE1SYS_SYS_RESET_STATUS_RST_SHIFT))
#endif


/* SYS_VERSION */

/* SYS_MPCORE_STATUS */

#define REG_NE1SYS_SYS_MPCORE_STATUS_EVENTIN_SHIFT         16
#define REG_NE1SYS_SYS_MPCORE_STATUS_EVENTIN_SIZE          1
#define REG_NE1SYS_SYS_MPCORE_STATUS_EVENTIN_MASK          0x00010000

#define REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI3_SHIFT        12
#define REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI3_SIZE         2
#define REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI3_MASK         0x00003000

#define REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI2_SHIFT        8
#define REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI2_SIZE         2
#define REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI2_MASK         0x00000300

#define REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI1_SHIFT        4
#define REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI1_SIZE         2
#define REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI1_MASK         0x00000030

#define REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI0_SHIFT        0
#define REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI0_SIZE         2
#define REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI0_MASK         0x00000003

#ifndef SDK_ASM
#define REG_NE1SYS_SYS_MPCORE_STATUS_FIELD( eventin, pwrctli3, pwrctli2, pwrctli1, pwrctli0 ) \
    (u32)( \
    ((u32)(eventin) << REG_NE1SYS_SYS_MPCORE_STATUS_EVENTIN_SHIFT) | \
    ((u32)(pwrctli3) << REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI3_SHIFT) | \
    ((u32)(pwrctli2) << REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI2_SHIFT) | \
    ((u32)(pwrctli1) << REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI1_SHIFT) | \
    ((u32)(pwrctli0) << REG_NE1SYS_SYS_MPCORE_STATUS_PWRCTLI0_SHIFT))
#endif


/* SYS_MPCORE_STATUS_MONITOR */

#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_STANDBYWFI_SHIFT 24
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_STANDBYWFI_SIZE 4
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_STANDBYWFI_MASK 0x0f000000

#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_STANDBYWFE_SHIFT 16
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_STANDBYWFE_SIZE 4
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_STANDBYWFE_MASK 0x000f0000

#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO3_SHIFT 12
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO3_SIZE 2
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO3_MASK 0x00003000

#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO2_SHIFT 8
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO2_SIZE 2
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO2_MASK 0x00000300

#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO1_SHIFT 4
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO1_SIZE 2
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO1_MASK 0x00000030

#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO0_SHIFT 0
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO0_SIZE 2
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO0_MASK 0x00000003

#ifndef SDK_ASM
#define REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_FIELD( standbywfi, standbywfe, pwrctlo3, pwrctlo2, pwrctlo1, pwrctlo0 ) \
    (u32)( \
    ((u32)(standbywfi) << REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_STANDBYWFI_SHIFT) | \
    ((u32)(standbywfe) << REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_STANDBYWFE_SHIFT) | \
    ((u32)(pwrctlo3) << REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO3_SHIFT) | \
    ((u32)(pwrctlo2) << REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO2_SHIFT) | \
    ((u32)(pwrctlo1) << REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO1_SHIFT) | \
    ((u32)(pwrctlo0) << REG_NE1SYS_SYS_MPCORE_STATUS_MONITOR_PWRCTLO0_SHIFT))
#endif


/* SYS_WTOP_MODE */

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_NE1TB_MPCORE_IOREG_NE1PATCH_NE1SYS_H_ */
#endif
