/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mmap_tcm.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50823 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_TWL_ARM9_MMAP_TCM_H_
#define NN_HW_TWL_ARM9_MMAP_TCM_H_
#ifdef  __cplusplus
extern  "C" {
#endif
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
    Size definition in DTCM
 *---------------------------------------------------------------------------*/
//---- system reserved work buffer size
#define HW_DTCM_SYSRV_SIZE              0x40    // 64 bytes

/*---------------------------------------------------------------------------*
    Other definition
 *---------------------------------------------------------------------------*/
//---- stack address ( for initial stack pointer )
#define HW_SYS_STACK_END                (HW_IRQ_STACK)
#define HW_IRQ_STACK                    (HW_IRQ_STACK_END - HW_IRQ_STACK_SIZE)
#define HW_IRQ_STACK_END                (HW_SVC_STACK)
#define HW_IRQ_STACK_SIZE               0x100
#define HW_SVC_STACK                    (HW_SVC_STACK_END - HW_SVC_STACK_SIZE)
#define HW_SVC_STACK_END                (HW_DTCM_END - HW_DTCM_SYSRV_SIZE)
#define HW_SVC_STACK_SIZE               0x40

//---- system reserved area
#define HW_DTCM_SYSRV                   (HW_DTCM + HW_DTCM_SIZE - HW_DTCM_SYSRV_SIZE)
#define HW_INTR_CHECK_BUF               (HW_DTCM_SYSRV + HW_DTCM_SYSRV_OFS_INTR_CHECK)
#define HW_INTR_VECTOR_BUF              (HW_DTCM_SYSRV + HW_DTCM_SYSRV_OFS_INTR_VECTOR)

//---- offset in system reserved area
#define HW_DTCM_SYSRV_OFS_DEBUGGER      0x00
#define HW_DTCM_SYSRV_OFS_RESERVED2     0x1c
#define HW_DTCM_SYSRV_OFS_RESERVED      0x20
#define HW_DTCM_SYSRV_OFS_INTR_CHECK    0x38
#define HW_DTCM_SYSRV_OFS_INTR_VECTOR   0x3c

/*---------------------------------------------------------------------------*
    Definition for Arena
 *---------------------------------------------------------------------------*/
//---- default address for DTCM Arena
#define HW_DTCM_ARENA_LO_DEFAULT        HW_DTCM
#define HW_DTCM_ARENA_HI_DEFAULT        HW_DTCM

//---- default address for ITCM Arena
#define HW_ITCM_ARENA_LO_DEFAULT        HW_ITCM
#define HW_ITCM_ARENA_HI_DEFAULT        HW_ITCM_END

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}   /* extern "C" */
#endif
#endif  /* NN_HW_TWL_ARM9_MMAP_TCM_H_ */
