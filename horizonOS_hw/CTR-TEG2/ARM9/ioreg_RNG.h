/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/ARM9/ioreg_RNG.h

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
#ifndef NN_HW_CTR_TEG2_ARM9_IOREG_RNG_H_
#define NN_HW_CTR_TEG2_ARM9_IOREG_RNG_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* COLD_DT */

#define REG_COLD_DT_OFFSET                                 0x11000
#define REG_COLD_DT_ADDR                                   (HW_REG_BASE + REG_COLD_DT_OFFSET)
#define reg_RNG_COLD_DT                                    (*(const REGType32v *) REG_COLD_DT_ADDR)

/* HOT_DT */

#define REG_HOT_DT_OFFSET                                  0x11010
#define REG_HOT_DT_ADDR                                    (HW_REG_BASE + REG_HOT_DT_OFFSET)
#define reg_RNG_HOT_DT                                     (*(const REGType32v *) REG_HOT_DT_ADDR)

/* COLD_SEED */

#define REG_COLD_SEED_OFFSET                               0x11020
#define REG_COLD_SEED_ADDR                                 (HW_REG_BASE + REG_COLD_SEED_OFFSET)
#define reg_RNG_COLD_SEED                                  (*(const REGType16v *) REG_COLD_SEED_ADDR)

/* HOT_SEED */

#define REG_HOT_SEED_OFFSET                                0x11022
#define REG_HOT_SEED_ADDR                                  (HW_REG_BASE + REG_HOT_SEED_OFFSET)
#define reg_RNG_HOT_SEED                                   (*(const REGType16v *) REG_HOT_SEED_ADDR)


/*
 * Definitions of Register fields
 */


/* COLD_DT */

/* HOT_DT */

/* COLD_SEED */

/* HOT_SEED */

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_ARM9_IOREG_RNG_H_ */
#endif
