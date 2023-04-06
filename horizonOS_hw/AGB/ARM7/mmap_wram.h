/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mmap_wram.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50823 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_AGB_ARM7_MMAP_WRAM_H_
#define NN_HW_AGB_ARM7_MMAP_WRAM_H_

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------
//  MEMORY MAP of WRAM
//----------------------------------------------------------------------
//----------------------------------------------------------------
//---- stack address ( for initial stack pointer )
#define HW_SYS_STACK_END                (HW_IRQ_STACK)
#define HW_IRQ_STACK                    (HW_IRQ_STACK_END - HW_IRQ_STACK_SIZE)
#define HW_IRQ_STACK_END                (HW_SVC_STACK)
#define HW_IRQ_STACK_SIZE               0x20 // 元は0x100
#define HW_SVC_STACK                    (HW_SVC_STACK_END - HW_SVC_STACK_SIZE)
#define HW_SVC_STACK_END                (HW_FIQ_STACK)
#define HW_SVC_STACK_SIZE               0x60
#define HW_FIQ_STACK                    (HW_FIQ_STACK_END - HW_FIQ_STACK_SIZE)
#define HW_FIQ_STACK_END                (HW_WRAM_END)
#define HW_FIQ_STACK_SIZE               0 // 元は0x20

#ifdef __cplusplus
} /* extern "C" */
#endif
/* NN_HW_AGB_ARM7_MMAP_WRAM_H_ */
#endif
