/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mmap_shared.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50823 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_CTR_MMAP_SHARED_H_
#define NN_HW_CTR_MMAP_SHARED_H_

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------
// MEMORY MAP of SYSTEM SHARED AREA
//----------------------------------------------------------------------

//---- AXI-WRAMシステム領域（最上位）

#define HW_AXI_WRAM_SHARED              (HW_AXI_WRAM_SHARED_END - HW_AXI_WRAM_SHARED_SIZE)
#define HW_AXI_WRAM_SHARED_END          (HW_AXI_WRAM_END)
#define HW_AXI_WRAM_SHARED_SIZE         (HW_AXI_WRAM_SHARED_SYS_SIZE + HW_AXI_WRAM_SHARED_GBL_SIZE) // 8KB

// コア毎に独立したシステム領域（コア１は HW_AXI_WRAM_SHARED_GBL からリマップ）
#define HW_AXI_WRAM_SHARED_SYS          (HW_AXI_WRAM_SHARED_SYS_END - HW_AXI_WRAM_SHARED_SYS_SIZE)
#define HW_AXI_WRAM_SHARED_SYS_END      HW_AXI_WRAM_SHARED_END
#define HW_AXI_WRAM_SHARED_SYS_SIZE     0x1000 // 4KB

#define HW_AXI_WRAM_SHARED_SYS_A11      (HW_AXI_WRAM_SHARED_SYS_A11_END - HW_AXI_WRAM_SHARED_SYS_A11_SIZE)
#define HW_AXI_WRAM_SHARED_SYS_A11_END  HW_AXI_WRAM_SHARED_SYS_END
#define HW_AXI_WRAM_SHARED_SYS_A11_SIZE 0x60 // 96B

// 両コアで共通したシステム領域
#define HW_AXI_WRAM_SHARED_GBL          (HW_AXI_WRAM_SHARED_GBL_END - HW_AXI_WRAM_SHARED_GBL_SIZE)
#define HW_AXI_WRAM_SHARED_GBL_END      HW_AXI_WRAM_SHARED_SYS
#define HW_AXI_WRAM_SHARED_GBL_SIZE     0x1000 // 4KB


//---- メインメモリ・システム領域（最下位）

#define HW_MAIN_MEM_SHARED              HW_MAIN_MEM
#define HW_MAIN_MEM_SHARED_END          (HW_MAIN_MEM_SHARED + HW_MAIN_MEM_SHARED_SIZE)
#define HW_MAIN_MEM_SHARED_SIZE         (HW_MAIN_MEM_SHARED_PUB_SIZE + HW_MAIN_MEM_SHARED_PRV_SIZE) // 128KB

// ユーザへ公開するシステム領域（ROMヘッダ等。TWL互換時は16KB*(64/16)=64KBのアプリジャンプパラメータ領域になる）
#define HW_MAIN_MEM_SHARED_PUB          HW_MAIN_MEM_SHARED
#define HW_MAIN_MEM_SHARED_PUB_END      (HW_MAIN_MEM_SHARED_PUB + HW_MAIN_MEM_SHARED_PUB_SIZE)
#define HW_MAIN_MEM_SHARED_PUB_SIZE     0x10000 // 64KB

// ユーザ非公開のシステム領域（コア間共有データ等）
#define HW_MAIN_MEM_SHARED_PRV          HW_MAIN_MEM_SHARED_PUB_END
#define HW_MAIN_MEM_SHARED_PRV_END      (HW_MAIN_MEM_SHARED_PRV + HW_MAIN_MEM_SHARED_PRV_SIZE)
#define HW_MAIN_MEM_SHARED_PRV_SIZE     0x10000 // 64KB


//----------------------------------------------------------------------
// MEMORY MAP of KERNEL AREA
//----------------------------------------------------------------------

#define HW_MAIN_MEM_KERNEL              HW_MAIN_MEM_SHARED_END
#define HW_MAIN_MEM_KERNEL_END          (HW_MAIN_MEM_KERNEL + HW_MAIN_MEM_KERNEL_SIZE)
#define HW_MAIN_MEM_KERNEL_SIZE         (0x1000000 - HW_MAIN_MEM_SHARED_SIZE) // 16MB-128KB


//----------------------------------------------------------------------
// MEMORY MAP of DEBUGGER AREA
//----------------------------------------------------------------------

#define HW_MAIN_MEM_DEBUGGER            (HW_MAIN_MEM_DEBUGGER_END - HW_MAIN_MEM_DEBUGGER_SIZE)
#define HW_MAIN_MEM_DEBUGGER_END        HW_MAIN_MEM_EX_END
#define HW_MAIN_MEM_DEBUGGER_SIZE       0x100000 // 1MB


#ifdef __cplusplus
} /* extern "C" */
#endif
/* NN_HW_CTR_MMAP_SHARED_H_ */
#endif
