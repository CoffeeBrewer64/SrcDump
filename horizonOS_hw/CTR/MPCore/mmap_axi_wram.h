/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mmap_axi_wram.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50823 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_CTR_MPCORE_MMAP_AXI_WRAM_H_
#define NN_HW_CTR_MPCORE_MMAP_AXI_WRAM_H_

#include <nn/hw/CTR/mmap_shared.h>

#ifdef __cplusplus
extern "C" {
#endif

//---- system reserved area
// bootrom/firmwareではコア毎に異なる物理アドレスをマッピング
#define HW_AXI_WRAM_SYSRV                   HW_AXI_WRAM_SHARED_SYS_A11
#define HW_AXI_WRAM_SYSRV_END               HW_AXI_WRAM_SHARED_SYS_A11_END
#define HW_AXI_WRAM_SYSRV_SIZE              HW_AXI_WRAM_SHARED_SYS_A11_SIZE

//---- offset in system reserved area
#if     defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6)
// FCRAMまで命令プリフェッチしないように配置（MPCoreは8段パイプライン）
#define HW_AXI_WRAM_SYSRV_OFS_INTR_VENEER   0x00
#define HW_AXI_WRAM_SYSRV_OFS_FIQ_VENEER    0x08
#define HW_AXI_WRAM_SYSRV_OFS_SWI_VENEER    0x10
#define HW_AXI_WRAM_SYSRV_OFS_UNDEF_VENEER  0x18
#define HW_AXI_WRAM_SYSRV_OFS_IABT_VENEER   0x20
#define HW_AXI_WRAM_SYSRV_OFS_DABT_VENEER   0x28
#endif // SDK_ARM11
// PXIコールバック登録チェックバッファをMPCore-1からアクセスできない物理アドレスへマッピング
#define HW_AXI_WRAM_SYSRV_OFS_PXI_CB_A11_0  0x30
#define HW_AXI_WRAM_SYSRV_OFS_PXI_CB_A9     0x34
// ロックバッファはコア間で共通の物理アドレス
#define HW_AXI_WRAM_SYSRV_OFS_INIT_LOCK_BUF ((u32)(0x38 - HW_AXI_WRAM_SHARED_SYS_SIZE))  // 2 bytes for firmware
#define HW_AXI_WRAM_SYSRV_OFS_CARD_LOCK_BUF ((u32)(0x3a - HW_AXI_WRAM_SHARED_SYS_SIZE))  // 2 bytes for firmware
#if     defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6)
#define HW_AXI_WRAM_SYSRV_OFS_START_VECTOR1 0x3c
#define HW_AXI_WRAM_SYSRV_OFS_INTR_CHECK1   0x40
#define HW_AXI_WRAM_SYSRV_OFS_INTR_CHECK0   0x50
#endif // SDK_ARM11

//---- system reserved area
#if     defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6)
#define HW_EXCP_VENEER_BUF                  (HW_INTR_VENEER_BUF)
#define HW_EXCP_VENEER_BUF_END              (HW_EXCP_VENEER_BUF + HW_EXCP_VENEER_BUF_SIZE)
#define HW_EXCP_VENEER_BUF_SIZE             (8 * 6)
#define HW_INTR_VENEER_BUF                  (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_INTR_VENEER)
#define HW_FIQ_VENEER_BUF                   (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_FIQ_VENEER)
#define HW_SWI_VENEER_BUF                   (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_SWI_VENEER)
#define HW_UNDEF_VENEER_BUF                 (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_UNDEF_VENEER)
#define HW_IABT_VENEER_BUF                  (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_IABT_VENEER)
#define HW_DABT_VENEER_BUF                  (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_DABT_VENEER)
// Errata 720247 (Speculative Instruction fetches) scenario2 対策のため
// B/BL/BX/BLX命令と一致する 0x*A******/0x*B******/0x*1****** 番地は指定しないこと
// 具体的には唯一該当する FCRAM 16MB-32MB の間だけは例外ハンドラを配置しない
#define HW_INTR_VECTOR_BUF                  (HW_INTR_VENEER_BUF + 4)
#define HW_FIQ_VECTOR_BUF                   (HW_FIQ_VENEER_BUF + 4)
#define HW_SWI_VECTOR_BUF                   (HW_SWI_VENEER_BUF + 4)
#define HW_UNDEF_VECTOR_BUF                 (HW_UNDEF_VENEER_BUF + 4)
#define HW_IABT_VECTOR_BUF                  (HW_IABT_VENEER_BUF + 4)
#define HW_DABT_VECTOR_BUF                  (HW_DABT_VENEER_BUF + 4)
#endif // SDK_ARM11
#define HW_PXI_CB_CHECK_BUF                 (HW_PXI_CB_A11_0_BUF)
#define HW_PXI_CB_A11_0_BUF                 (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_PXI_CB_A11_0)
#define HW_PXI_CB_A9_BUF                    (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_PXI_CB_A9)
#define HW_INIT_LOCK_BUF                    (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_INIT_LOCK_BUF)
#define HW_CARD_LOCK_BUF                    (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_CARD_LOCK_BUF)
#if     defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6)
#define HW_START_VECTOR1_BUF                (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_START_VECTOR1)
#define HW_INTR_CHECK1_BUF                  (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_INTR_CHECK1)
#define HW_INTR_CHECK0_BUF                  (HW_AXI_WRAM_SYSRV + HW_AXI_WRAM_SYSRV_OFS_INTR_CHECK0)
#endif // SDK_ARM11


#ifdef __cplusplus
} /* extern "C" */
#endif
/* NN_HW_CTR_MPCORE_MMAP_AXI_WRAM_H_ */
#endif
