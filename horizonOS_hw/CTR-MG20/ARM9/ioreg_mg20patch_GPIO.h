/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-MG20/ARM9/ioreg_mg20patch_GPIO.h

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
#ifndef NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_GPIO_H_
#define NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_GPIO_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* GPIO_CNT */

#define REG_GPIO_CNT_OFFSET                                0x120000
#define REG_GPIO_CNT_ADDR                                  (HW_REG_BASE + REG_GPIO_CNT_OFFSET)
#define reg_GPIO_GPIO_CNT                                  (*( REGType32v *) REG_GPIO_CNT_ADDR)

/* GPIO_CNT_L */

#define REG_GPIO_CNT_L_OFFSET                              0x120000
#define REG_GPIO_CNT_L_ADDR                                (HW_REG_BASE + REG_GPIO_CNT_L_OFFSET)
#define reg_GPIO_GPIO_CNT_L                                (*( REGType16v *) REG_GPIO_CNT_L_ADDR)

/* GPIO_CNT_H */

#define REG_GPIO_CNT_H_OFFSET                              0x120002
#define REG_GPIO_CNT_H_ADDR                                (HW_REG_BASE + REG_GPIO_CNT_H_OFFSET)
#define reg_GPIO_GPIO_CNT_H                                (*( REGType16v *) REG_GPIO_CNT_H_ADDR)


/*
 * Definitions of Register fields
 */


/* GPIO_CNT */

/* GPIO_CNT_L */

/* GPIO_CNT_H */

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_GPIO_H_ */
#endif
