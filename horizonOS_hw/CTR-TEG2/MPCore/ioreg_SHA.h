/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/MPCore/ioreg_SHA.h

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
#ifndef NN_HW_CTR_TEG2_MPCORE_IOREG_SHA_H_
#define NN_HW_CTR_TEG2_MPCORE_IOREG_SHA_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* SHA_CNT */

#define REG_SHA_CNT_OFFSET                                 0x101000
#define REG_SHA_CNT_ADDR                                   (HW_REG_BASE + REG_SHA_CNT_OFFSET)
#define reg_SHA_SHA_CNT                                    (*( REGType32v *) REG_SHA_CNT_ADDR)

/* SHA_LEN */

#define REG_SHA_LEN_OFFSET                                 0x101004
#define REG_SHA_LEN_ADDR                                   (HW_REG_BASE + REG_SHA_LEN_OFFSET)
#define reg_SHA_SHA_LEN                                    (*( REGType32v *) REG_SHA_LEN_ADDR)

/* SHA_H0 */

#define REG_SHA_H0_OFFSET                                  0x101040
#define REG_SHA_H0_ADDR                                    (HW_REG_BASE + REG_SHA_H0_OFFSET)
#define reg_SHA_SHA_H0                                     (*( REGType32v *) REG_SHA_H0_ADDR)

/* SHA_MSG0 */

#define REG_SHA_MSG0_OFFSET                                0x301000
#define REG_SHA_MSG0_ADDR                                  (HW_REG_BASE + REG_SHA_MSG0_OFFSET)
#define reg_SHA_SHA_MSG0                                   (*( REGType32v *) REG_SHA_MSG0_ADDR)


/*
 * Definitions of Register fields
 */


/* SHA_CNT */

#define REG_SHA_SHA_CNT_ODMA_E_SHIFT                       10
#define REG_SHA_SHA_CNT_ODMA_E_SIZE                        1
#define REG_SHA_SHA_CNT_ODMA_E_MASK                        0x00000400

#define REG_SHA_SHA_CNT_RBNE_SHIFT                         9
#define REG_SHA_SHA_CNT_RBNE_SIZE                          1
#define REG_SHA_SHA_CNT_RBNE_MASK                          0x00000200

#define REG_SHA_SHA_CNT_REF_E_SHIFT                        8
#define REG_SHA_SHA_CNT_REF_E_SIZE                         1
#define REG_SHA_SHA_CNT_REF_E_MASK                         0x00000100

#define REG_SHA_SHA_CNT_MODE_SHIFT                         4
#define REG_SHA_SHA_CNT_MODE_SIZE                          2
#define REG_SHA_SHA_CNT_MODE_MASK                          0x00000030

#define REG_SHA_SHA_CNT_BSWAP_SHIFT                        3
#define REG_SHA_SHA_CNT_BSWAP_SIZE                         1
#define REG_SHA_SHA_CNT_BSWAP_MASK                         0x00000008

#define REG_SHA_SHA_CNT_IDMA_E_SHIFT                       2
#define REG_SHA_SHA_CNT_IDMA_E_SIZE                        1
#define REG_SHA_SHA_CNT_IDMA_E_MASK                        0x00000004

#define REG_SHA_SHA_CNT_PAD_SHIFT                          1
#define REG_SHA_SHA_CNT_PAD_SIZE                           1
#define REG_SHA_SHA_CNT_PAD_MASK                           0x00000002

#define REG_SHA_SHA_CNT_BUSY_SHIFT                         0
#define REG_SHA_SHA_CNT_BUSY_SIZE                          1
#define REG_SHA_SHA_CNT_BUSY_MASK                          0x00000001

#define REG_SHA_SHA_CNT_INIT_SHIFT                         0
#define REG_SHA_SHA_CNT_INIT_SIZE                          1
#define REG_SHA_SHA_CNT_INIT_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_SHA_SHA_CNT_FIELD( odma_e, rbne, ref_e, mode, bswap, idma_e, pad, busy, init ) \
    (u32)( \
    ((u32)(odma_e) << REG_SHA_SHA_CNT_ODMA_E_SHIFT) | \
    ((u32)(rbne) << REG_SHA_SHA_CNT_RBNE_SHIFT) | \
    ((u32)(ref_e) << REG_SHA_SHA_CNT_REF_E_SHIFT) | \
    ((u32)(mode) << REG_SHA_SHA_CNT_MODE_SHIFT) | \
    ((u32)(bswap) << REG_SHA_SHA_CNT_BSWAP_SHIFT) | \
    ((u32)(idma_e) << REG_SHA_SHA_CNT_IDMA_E_SHIFT) | \
    ((u32)(pad) << REG_SHA_SHA_CNT_PAD_SHIFT) | \
    ((u32)(busy) << REG_SHA_SHA_CNT_BUSY_SHIFT) | \
    ((u32)(init) << REG_SHA_SHA_CNT_INIT_SHIFT))
#endif


/* SHA_LEN */

/* SHA_H0 */

/* SHA_MSG0 */

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_MPCORE_IOREG_SHA_H_ */
#endif
