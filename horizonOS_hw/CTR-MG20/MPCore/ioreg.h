/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR/ARM9/ioreg.h

  Copyright 2008 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/

#ifndef NN_HW_CTR_MG20_MPCORE_IOREG_H_
#define NN_HW_CTR_MG20_MPCORE_IOREG_H_

#ifdef NN_SYSTEM_KERNEL
#define HW_MG20_APB_BAR0_REG            0x44100000
#else
#define HW_MG20_APB_BAR0_REG            0x1eb00000  // for process
#endif

#define HW_APBDEV_GPIO_REG              (HW_MG20_APB_BAR0_REG + 0x3000)

#define REG_GPIO_GROUP0_MODE_0          (HW_APBDEV_GPIO_REG + 0x0000)
#define REG_GPIO1_GROUP0_SET_STATE_0    (HW_APBDEV_GPIO_REG + 0x0020)
#define REG_GPIO2_GROUP0a_IRQ_MODE_0    (HW_APBDEV_GPIO_REG + 0x0040)
#define REG_GPIO3_GROUP0_READ_STATE_0   (HW_APBDEV_GPIO_REG + 0x0080)
#define REG_GPIO4_GROUP0_CLEAR_IRQ_0    (HW_APBDEV_GPIO_REG + 0x00a0)
#define REG_GPIO5_DEBOUNCE_CONTROL_0    (HW_APBDEV_GPIO_REG + 0x00c0)
#define REG_GPIO6_INTERRUPT_RAW_0       (HW_APBDEV_GPIO_REG + 0x00d0)
#define REG_GPIO6_INTERRUPT_MASK_0      (HW_APBDEV_GPIO_REG + 0x00d4)
#define REG_GPIO6_INTERRUPT_PENDING_0   (HW_APBDEV_GPIO_REG + 0x00d8)
#define REG_GPIO6_INTERRUPT_ACK_0       (HW_APBDEV_GPIO_REG + 0x00dc)


#define reg_GPIO_GROUP0_MODE_0          *(vu32*)REG_GPIO_GROUP0_MODE_0
#define reg_GPIO1_GROUP0_SET_STATE_0    *(vu32*)REG_GPIO1_GROUP0_SET_STATE_0
#define reg_GPIO2_GROUP0a_IRQ_MODE_0    *(vu32*)REG_GPIO2_GROUP0a_IRQ_MODE_0
#define reg_GPIO3_GROUP0_READ_STATE_0   *(vu32*)REG_GPIO3_GROUP0_READ_STATE_0
#define reg_GPIO5_DEBOUNCE_CONTROL_0    *(vu32*)REG_GPIO5_DEBOUNCE_CONTROL_0

#define REG_CLKCR_MPCORECTL_0           (HW_APBDEV_GPIO_REG + 0x00f0)
/* NN_HW_CTR_MG20_ARM9_IOREG_H_ */
#endif
