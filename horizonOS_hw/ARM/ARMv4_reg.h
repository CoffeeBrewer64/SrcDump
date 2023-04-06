/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     ARMv4_reg.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50823 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_ARM_ARMV4_REG_H_
#define NN_HW_ARM_ARMV4_REG_H_

#include <nn/hw/ARM/reg_common.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SDK_TWL
#define HW_SYSTEM_CLOCK             (33514 * 1000) // Typical値は 33513982（1/200万＝23日で1秒の誤差）
#else // SDK_AGB
#define HW_SYSTEM_CLOCK             (16778 * 1000) // Typical値は 16777216（1/2万＝5時間30分で1秒の誤差）
#endif // SDK_AGB
#define HW_CPU_CLOCK                HW_SYSTEM_CLOCK

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_ARM_ARMV4_REG_H_ */
#endif
