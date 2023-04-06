/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/ARM9/ioreg_RSA.h

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
#ifndef NN_HW_CTR_TEG2_ARM9_IOREG_RSA_H_
#define NN_HW_CTR_TEG2_ARM9_IOREG_RSA_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* RSA_CNT */

#define REG_RSA_CNT_OFFSET                                 0xb000
#define REG_RSA_CNT_ADDR                                   (HW_REG_BASE + REG_RSA_CNT_OFFSET)
#define reg_RSA_RSA_CNT                                    (*( REGType32v *) REG_RSA_CNT_ADDR)

/* RSA_DIAG */

#define REG_RSA_DIAG_OFFSET                                0xb0f0
#define REG_RSA_DIAG_ADDR                                  (HW_REG_BASE + REG_RSA_DIAG_OFFSET)
#define reg_RSA_RSA_DIAG                                   (*( REGType32v *) REG_RSA_DIAG_ADDR)

/* RSA_PROT0 */

#define REG_RSA_PROT0_OFFSET                               0xb100
#define REG_RSA_PROT0_ADDR                                 (HW_REG_BASE + REG_RSA_PROT0_OFFSET)
#define reg_RSA_RSA_PROT0                                  (*( REGType32v *) REG_RSA_PROT0_ADDR)

/* RSA_WLEN */

#define REG_RSA_WLEN_OFFSET                                0xb104
#define REG_RSA_WLEN_ADDR                                  (HW_REG_BASE + REG_RSA_WLEN_OFFSET)
#define reg_RSA_RSA_WLEN                                   (*(const REGType32v *) REG_RSA_WLEN_ADDR)

/* RSA_EXP0 */

#define REG_RSA_EXP0_OFFSET                                0xb200
#define REG_RSA_EXP0_ADDR                                  (HW_REG_BASE + REG_RSA_EXP0_OFFSET)
#define reg_RSA_RSA_EXP0                                   (*( REGType32v *) REG_RSA_EXP0_ADDR)

/* RSA_MOD0 */

#define REG_RSA_MOD0_OFFSET                                0xb400
#define REG_RSA_MOD0_ADDR                                  (HW_REG_BASE + REG_RSA_MOD0_OFFSET)
#define reg_RSA_RSA_MOD0                                   (*( REGType32v *) REG_RSA_MOD0_ADDR)

/* RSA_TEXT0 */

#define REG_RSA_TEXT0_OFFSET                               0xb800
#define REG_RSA_TEXT0_ADDR                                 (HW_REG_BASE + REG_RSA_TEXT0_OFFSET)
#define reg_RSA_RSA_TEXT0                                  (*( REGType32v *) REG_RSA_TEXT0_ADDR)


/*
 * Definitions of Register fields
 */


/* RSA_CNT */

#define REG_RSA_RSA_CNT_KEYSEL_SHIFT                       4
#define REG_RSA_RSA_CNT_KEYSEL_SIZE                        2
#define REG_RSA_RSA_CNT_KEYSEL_MASK                        0x00000030

#define REG_RSA_RSA_CNT_I_SHIFT                            1
#define REG_RSA_RSA_CNT_I_SIZE                             1
#define REG_RSA_RSA_CNT_I_MASK                             0x00000002

#define REG_RSA_RSA_CNT_START_SHIFT                        0
#define REG_RSA_RSA_CNT_START_SIZE                         1
#define REG_RSA_RSA_CNT_START_MASK                         0x00000001

#ifndef SDK_ASM
#define REG_RSA_RSA_CNT_FIELD( keysel, i, start ) \
    (u32)( \
    ((u32)(keysel) << REG_RSA_RSA_CNT_KEYSEL_SHIFT) | \
    ((u32)(i) << REG_RSA_RSA_CNT_I_SHIFT) | \
    ((u32)(start) << REG_RSA_RSA_CNT_START_SHIFT))
#endif


/* RSA_DIAG */

#define REG_RSA_RSA_DIAG_W_E_SHIFT                         31
#define REG_RSA_RSA_DIAG_W_E_SIZE                          1
#define REG_RSA_RSA_DIAG_W_E_MASK                          0x80000000

#define REG_RSA_RSA_DIAG_FUNC_SHIFT                        8
#define REG_RSA_RSA_DIAG_FUNC_SIZE                         4
#define REG_RSA_RSA_DIAG_FUNC_MASK                         0x00000f00

#define REG_RSA_RSA_DIAG_MMAP_SHIFT                        0
#define REG_RSA_RSA_DIAG_MMAP_SIZE                         4
#define REG_RSA_RSA_DIAG_MMAP_MASK                         0x0000000f

#ifndef SDK_ASM
#define REG_RSA_RSA_DIAG_FIELD( w_e, func, mmap ) \
    (u32)( \
    ((u32)(w_e) << REG_RSA_RSA_DIAG_W_E_SHIFT) | \
    ((u32)(func) << REG_RSA_RSA_DIAG_FUNC_SHIFT) | \
    ((u32)(mmap) << REG_RSA_RSA_DIAG_MMAP_SHIFT))
#endif


/* RSA_PROT0 */

#define REG_RSA_RSA_PROT0_E_SHIFT                          31
#define REG_RSA_RSA_PROT0_E_SIZE                           1
#define REG_RSA_RSA_PROT0_E_MASK                           0x80000000

#define REG_RSA_RSA_PROT0_RP_SHIFT                         2
#define REG_RSA_RSA_PROT0_RP_SIZE                          4
#define REG_RSA_RSA_PROT0_RP_MASK                          0x0000003c

#define REG_RSA_RSA_PROT0_WP_SHIFT                         1
#define REG_RSA_RSA_PROT0_WP_SIZE                          1
#define REG_RSA_RSA_PROT0_WP_MASK                          0x00000002

#define REG_RSA_RSA_PROT0_KV_SHIFT                         0
#define REG_RSA_RSA_PROT0_KV_SIZE                          1
#define REG_RSA_RSA_PROT0_KV_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_RSA_RSA_PROT0_FIELD( e, rp, wp, kv ) \
    (u32)( \
    ((u32)(e) << REG_RSA_RSA_PROT0_E_SHIFT) | \
    ((u32)(rp) << REG_RSA_RSA_PROT0_RP_SHIFT) | \
    ((u32)(wp) << REG_RSA_RSA_PROT0_WP_SHIFT) | \
    ((u32)(kv) << REG_RSA_RSA_PROT0_KV_SHIFT))
#endif


/* RSA_WLEN */

#define REG_RSA_RSA_WLEN_WLEN_SHIFT                        0
#define REG_RSA_RSA_WLEN_WLEN_SIZE                         7
#define REG_RSA_RSA_WLEN_WLEN_MASK                         0x0000007f

#ifndef SDK_ASM
#define REG_RSA_RSA_WLEN_FIELD( wlen ) \
    (u32)( \
    ((u32)(wlen) << REG_RSA_RSA_WLEN_WLEN_SHIFT))
#endif


/* RSA_EXP0 */

/* RSA_MOD0 */

/* RSA_TEXT0 */

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_ARM9_IOREG_RSA_H_ */
#endif
