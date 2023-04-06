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

#ifndef NN_HW_TWL_ARM7_MMAP_WRAM_H_
#define NN_HW_TWL_ARM7_MMAP_WRAM_H_
#ifdef  __cplusplus
extern  "C" {
#endif
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
    Size definition in WRAM
 *---------------------------------------------------------------------------*/
//---- system reserved work buffer size
#define HW_PRV_WRAM_SYSRV_SIZE          0x40    // 64 bytes

/*---------------------------------------------------------------------------*
    MEMORY MAP of WRAM
 *---------------------------------------------------------------------------*/
//---- stack address ( for initial stack pointer )
#define HW_SYS_STACK_END                (HW_IRQ_STACK)
#define HW_IRQ_STACK                    (HW_IRQ_STACK_END - HW_IRQ_STACK_SIZE)
#define HW_IRQ_STACK_END                (HW_SVC_STACK)
#define HW_IRQ_STACK_SIZE               0x100
#define HW_SVC_STACK                    (HW_SVC_STACK_END - HW_SVC_STACK_SIZE)
#define HW_SVC_STACK_END                (HW_PRV_WRAM_END - HW_PRV_WRAM_SYSRV_SIZE)
#define HW_SVC_STACK_SIZE               0x40

//---- parameter delivery buffer ( for secure ARM7 components )
#define HW_LAUNCHER_DELIVER_PARAM_BUF_OFFSET 0xf000
#define HW_LAUNCHER_DELIVER_PARAM_BUF_SIZE   0x40    // 64 bytes
#define HW_LAUNCHER_DELIVER_PARAM_BUF        (HW_PRV_WRAM + HW_LAUNCHER_DELIVER_PARAM_BUF_OFFSET)
#define HW_LAUNCHER_DELIVER_PARAM_BUF_END    (HW_LAUNCHER_DELIVER_PARAM_BUF + HW_LAUNCHER_DELIVER_PARAM_BUF_SIZE)
/* 注意: セキュア ARM7 コンポーネントとランチャー間でセキュアに扱う必要のある
   データの受け渡しの為に用いられるバッファです。*/
   
//---- RED reserved for DS-IPL
//#define HW_PRV_WRAM_RED_RESERVED          (HW_PRV_WRAM + 0xfc00)  // 64byte
//#define HW_PRV_WRAM_RED_RESERVED_END      (HW_PRV_WRAM + 0xfc40)

//---- system reserved area
#define HW_PRV_WRAM_SYSRV                   (HW_PRV_WRAM_END - HW_PRV_WRAM_SYSRV_SIZE)
/* 注意: sysytem reserved area に含まれる INTR VECTOR は実際は ROM からは 0x03FFFFFC
   のミラー領域のアドレスが参照されます。ですので、そのミラー領域のアドレスに WRAM-A
   などを上書きでマップしないように注意する必要があります。 */

//---- offset in system reserved area
#define HW_PRV_WRAM_SYSRV_OFS_INTR_CHECK2    0x00    // intr check (2)
#define HW_PRV_WRAM_SYSRV_OFS_SYS_CONF       0x04
#define HW_PRV_WRAM_SYSRV_OFS_SYS_CONF_END   0x0a
#define HW_PRV_WRAM_SYSRV_OFS_RESERVE        0x0a
#define HW_PRV_WRAM_SYSRV_OFS_RESERVE_END    0x10
#define HW_PRV_WRAM_SYSRV_OFS_EXCP_STACK     0x10
#define HW_PRV_WRAM_SYSRV_OFS_EXCP_STACK_END 0x1c
#define HW_PRV_WRAM_SYSRV_OFS_EXCP_VECTOR    0x1c
#define HW_PRV_WRAM_SYSRV_OFS_DMA_CLEAR_BUF  0x20    // 16 bytes
#define HW_PRV_WRAM_SYSRV_OFS_WM_RESERVED_0  0x30
#define HW_PRV_WRAM_SYSRV_OFS_WM_RESERVED_1  0x34
#define HW_PRV_WRAM_SYSRV_OFS_INTR_CHECK     0x38    // intr check (1)
#define HW_PRV_WRAM_SYSRV_OFS_INTR_VECTOR    0x3c

//---- system reserved area 1
#define HW_EXCP_VECTOR_BUF                  (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_EXCP_VECTOR)

//---- DMA clear data buffer for ARM7
#define HW_PRV_WRAM_DMA_CLEAR_DATA_BUF      (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_DMA_CLEAR_BUF)

//---- MITSUMI reserved
#define HW_PRV_WRAM_MITSUMI_RESERVED_0      (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_WM_RESERVED_0)
#define HW_PRV_WRAM_MITSUMI_RESERVED_1      (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_WM_RESERVED_1)

//---- system reserved area 2
#define HW_PRV_WRAM_SYS_CONF_BUF            (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_SYS_CONF)
#define HW_INTR_CHECK2_BUF                  (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_INTR_CHECK2)
#define HW_INTR_CHECK_BUF                   (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_INTR_CHECK)
#define HW_INTR_VECTOR_BUF                  (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_INTR_VECTOR)

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}   /* extern "C" */
#endif
#endif  /* NN_HW_TWL_ARM7_MMAP_WRAM_H_ */
