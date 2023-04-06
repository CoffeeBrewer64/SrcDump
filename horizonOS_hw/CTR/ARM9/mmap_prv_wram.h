/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mmap_prv_wram.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50823 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_CTR_ARM9_MMAP_PRV_WRAM_H_
#define NN_HW_CTR_ARM9_MMAP_PRV_WRAM_H_

#include <nn/hw/CTR/mmap_shared.h>

#ifdef __cplusplus
extern "C" {
#endif

//---- system reserved area
#define HW_PRV_WRAM_SYSRV                   HW_PRV_WRAM
#define HW_PRV_WRAM_SYSRV_END               (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_SIZE)
#define HW_PRV_WRAM_SYSRV_SIZE              0x40 // 64B

//---- offset in system reserved area
#define HW_PRV_WRAM_SYSRV_OFS_INTR_VENEER   0x00
#define HW_PRV_WRAM_SYSRV_OFS_FIQ_VENEER    0x08
#define HW_PRV_WRAM_SYSRV_OFS_SWI_VENEER    0x10
#define HW_PRV_WRAM_SYSRV_OFS_UNDEF_VENEER  0x18
#define HW_PRV_WRAM_SYSRV_OFS_IABT_VENEER   0x20
#define HW_PRV_WRAM_SYSRV_OFS_DABT_VENEER   0x28
#ifndef SDK_TS
#define HW_PRV_WRAM_SYSRV_OFS_SCFG_OP_TMP   0x30
#endif // SDK_TS
#define HW_PRV_WRAM_SYSRV_OFS_INTR_CHECK    0x3c

//---- system reserved area
#define HW_EXCP_VENEER_BUF                  (HW_INTR_VENEER_BUF)
#define HW_EXCP_VENEER_BUF_END              (HW_EXCP_VENEER_BUF + HW_EXCP_VENEER_BUF_SIZE)
#define HW_EXCP_VENEER_BUF_SIZE             (8 * 6)
#define HW_INTR_VENEER_BUF                  (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_INTR_VENEER)
#define HW_FIQ_VENEER_BUF                   (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_FIQ_VENEER)
#define HW_SWI_VENEER_BUF                   (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_SWI_VENEER)
#define HW_UNDEF_VENEER_BUF                 (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_UNDEF_VENEER)
#define HW_IABT_VENEER_BUF                  (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_IABT_VENEER)
#define HW_DABT_VENEER_BUF                  (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_DABT_VENEER)
#define HW_INTR_VECTOR_BUF                  (HW_INTR_VENEER_BUF + 4)
#define HW_FIQ_VECTOR_BUF                   (HW_FIQ_VENEER_BUF + 4)
#define HW_SWI_VECTOR_BUF                   (HW_SWI_VENEER_BUF + 4)
#define HW_UNDEF_VECTOR_BUF                 (HW_UNDEF_VENEER_BUF + 4)
#define HW_IABT_VECTOR_BUF                  (HW_IABT_VENEER_BUF + 4)
#define HW_DABT_VECTOR_BUF                  (HW_DABT_VENEER_BUF + 4)
#define HW_SCFG_OP_TMP_BUF                  (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_SCFG_OP_TMP)
#define HW_INTR_CHECK_BUF                   (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_INTR_CHECK)


// for TWL mode on CTR mode
#define HW_TWL_VRAM_A               HW_PRV_WRAM
#define HW_TWL_VRAM_A_END           (HW_TWL_VRAM_A + HW_TWL_VRAM_A_SIZE)
#define HW_TWL_VRAM_A_SIZE          0x20000  // 128KB
#define HW_TWL_VRAM_B               HW_TWL_VRAM_A_END
#define HW_TWL_VRAM_B_END           (HW_TWL_VRAM_B + HW_TWL_VRAM_B_SIZE)
#define HW_TWL_VRAM_B_SIZE          0x20000  // 128KB
#define HW_TWL_VRAM_C               HW_TWL_VRAM_B_END
#define HW_TWL_VRAM_C_END           (HW_TWL_VRAM_C + HW_TWL_VRAM_C_SIZE)
#define HW_TWL_VRAM_C_SIZE          0x20000  // 128KB
#define HW_TWL_PRVWRAM              HW_TWL_VRAM_C_END
#define HW_TWL_PRVWRAM_END          (HW_TWL_PRVWRAM + HW_TWL_PRVWRAM_SIZE)
#define HW_TWL_PRVWRAM_SIZE         0x10000  // 64KB
#define HW_TWL_VRAM_H               HW_TWL_PRVWRAM_END
#define HW_TWL_VRAM_H_END           (HW_TWL_VRAM_H + HW_TWL_VRAM_H_SIZE)
#define HW_TWL_VRAM_H_SIZE          0x8000  // 32KB
#define HW_TWL_VRAM_I               HW_TWL_VRAM_H_END
#define HW_TWL_VRAM_I_END           (HW_TWL_VRAM_I + HW_TWL_VRAM_I_SIZE)
#define HW_TWL_VRAM_I_SIZE          0x4000  // 16KB
#define HW_TWL_PADRAM               HW_TWL_VRAM_I_END
#define HW_TWL_PADRAM_END           (HW_TWL_PADRAM + HW_TWL_PADRAM_SIZE)
#define HW_TWL_PADRAM_SIZE          0x4000  // 16KB
#define HW_TWL_VRAM_D               HW_TWL_PADRAM_END
#define HW_TWL_VRAM_D_END           (HW_TWL_VRAM_D + HW_TWL_VRAM_D_SIZE)
#define HW_TWL_VRAM_D_SIZE          0x20000  // 128KB
#define HW_TWL_VRAM_E               HW_TWL_VRAM_D_END
#define HW_TWL_VRAM_E_END           (HW_TWL_VRAM_E + HW_TWL_VRAM_E_SIZE)
#define HW_TWL_VRAM_E_SIZE          0x10000  // 64KB
#define HW_TWL_VRAM_F               HW_TWL_VRAM_E_END
#define HW_TWL_VRAM_F_END           (HW_TWL_VRAM_F + HW_TWL_VRAM_F_SIZE)
#define HW_TWL_VRAM_F_SIZE          0x4000  // 16KB
#define HW_TWL_VRAM_G               HW_TWL_VRAM_F_END
#define HW_TWL_VRAM_G_END           (HW_TWL_VRAM_G + HW_TWL_VRAM_G_SIZE)
#define HW_TWL_VRAM_G_SIZE          0x4000  // 16KB
#define HW_TWL_WRAM_0               HW_TWL_VRAM_G_END
#define HW_TWL_WRAM_0_END           (HW_TWL_WRAM_0 + HW_TWL_WRAM_0_SIZE)
#define HW_TWL_WRAM_0_SIZE          0x4000  // 16KB
#define HW_TWL_WRAM_1               HW_TWL_WRAM_0_END
#define HW_TWL_WRAM_1_END           (HW_TWL_WRAM_1 + HW_TWL_WRAM_1_SIZE)
#define HW_TWL_WRAM_1_SIZE          0x4000  // 16KB
#define HW_TWL_WRAM_A               HW_TWL_WRAM_1_END
#define HW_TWL_WRAM_A_END           (HW_TWL_WRAM_A + HW_TWL_WRAM_A_SIZE)
#define HW_TWL_WRAM_A_SIZE          0x40000  // 256KB
#define HW_TWL_WRAM_B_SIZE          0x40000  // 256KB
#define HW_TWL_WRAM_C_SIZE          0x40000  // 256KB
#define HW_TWL_WRAM_A_SLOT_SIZE     0x10000  // 64KB
#define HW_TWL_WRAM_B_SLOT_SIZE     0x8000   // 32KB
#define HW_TWL_WRAM_C_SLOT_SIZE     0x8000   // 32KB
#define HW_TWL_WRAM_A_SLOT_NUM      4
#define HW_TWL_WRAM_B_SLOT_NUM      8
#define HW_TWL_WRAM_C_SLOT_NUM      8


// for AGB mode on CTR mode
#define HW_AGB9_WRAM                HW_PRV_WRAM
#define HW_AGB9_WRAM_END            (HW_AGB9_WRAM + HW_AGB9_WRAM_SIZE)
#define HW_AGB9_WRAM_SIZE           0x80000  // 512KB
#define HW_AGB9_BKRAM               HW_AGB9_WRAM_END
#define HW_AGB9_BKRAM_END           (HW_AGB9_BKRAM + HW_AGB9_BKRAM_SIZE)
#define HW_AGB9_BKRAM_SIZE          0x20000  // 128KB
#define HW_AGB_VRAM                 HW_AGB9_BKRAM_END
#define HW_AGB_VRAM_END             (HW_AGB_VRAM + HW_AGB_VRAM_SIZE)
#define HW_AGB_VRAM_SIZE            0x18000  // 96KB
#define HW_AGB_WRAM                 HW_AGB_VRAM_END
#define HW_AGB_WRAM_END             (HW_AGB_WRAM + HW_AGB_WRAM_SIZE)
#define HW_AGB_WRAM_SIZE            0x8000  // 32KB
#define HW_AGB_EXRAM                HW_AGB_WRAM_END
#define HW_AGB_EXRAM_END            (HW_AGB_EXRAM + HW_AGB_EXRAM_SIZE)
#define HW_AGB_EXRAM_SIZE           0x40000  // 256KB


#ifdef __cplusplus
} /* extern "C" */
#endif
/* NN_HW_CTR_ARM9_MMAP_PRV_WRAM_H_ */
#endif
