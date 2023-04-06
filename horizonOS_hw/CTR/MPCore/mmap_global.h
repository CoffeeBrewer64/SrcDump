/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mmap_global.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 52435 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_CTR_MPCORE_MMAP_GLOBAL_H_
#define NN_HW_CTR_MPCORE_MMAP_GLOBAL_H_

#include <nn/hw/CTR/MPCore/mmap_common.h>

#ifdef  __cplusplus
extern  "C" {
#endif
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
    GLOBAL MEMORY MAP
 *---------------------------------------------------------------------------*/

//----------------------------- MAIN
#ifndef SDK_NE1EMU
#define HW_MAIN_MEM                 0x20000000
#define HW_MAIN_MEM_MG20EMU_SIZE    0x04000000 // 64MB
#else // SDK_NE1EMU
#define HW_MAIN_MEM                 0x80000000
#define HW_MAIN_MEM_NE1EMU_SIZE     0x10000000 // 256MB
#endif // SDK_NE1EMU

#define HW_MAIN_MEM_END         (HW_MAIN_MEM + HW_MAIN_MEM_SIZE)

#define HW_MAIN_MEM_EIU         HW_MAIN_MEM
#define HW_MAIN_MEM_EIU_END     (HW_MAIN_MEM_EIU + HW_MAIN_MEM_EIU_SIZE)

#define HW_MAIN_MEM_EX          HW_MAIN_MEM_END
#define HW_MAIN_MEM_EX_END      (HW_MAIN_MEM + HW_MAIN_MEM_EX_SIZE)

#define HW_MAIN_MEM_EX_EIU      HW_MAIN_MEM_EIU_END
#define HW_MAIN_MEM_EX_EIU_END  (HW_MAIN_MEM_EIU + HW_MAIN_MEM_EX_EIU_SIZE)

#ifdef SDK_MG20EMU
#define HW_MAIN_MEM_SIZE        0x02000000 // 32MB
#define HW_MAIN_MEM_EX_SIZE     0x03E00000 // 62MB
#else // SDK_NE1EMU or SDK_Palladium
#define HW_MAIN_MEM_SIZE        0x04000000 // 64MB
#define HW_MAIN_MEM_EX_SIZE     0x08000000 // 128MB

#define HW_MAIN_MEM_EIU_SIZE    0x08000000 // 128MB
#define HW_MAIN_MEM_EX_EIU_SIZE 0x10000000 // 256MB
#endif

#define HW_MAIN_MEM_NE1DDR      0x90000000
#define HW_MAIN_MEM_NE1DDR_SIZE 0x30000000
#define HW_MAIN_MEM_NE1DDR_END  (HW_MAIN_MEM_NE1DDR + HW_MAIN_MEM_NE1DDR_SIZE)

//----------------------------- DSP-WRAM
#define HW_DSP_WRAM             (HW_DSP_WRAM_END - HW_DSP_WRAM_SIZE) // 0x1ff00000
#define HW_DSP_WRAM_END         HW_AXI_WRAM
#define HW_DSP_WRAM_SIZE        0x80000 // 512KB

#define HW_DSP_PRAM             HW_DSP_WRAM
#define HW_DSP_DRAM             HW_DSP_PRAM_END
#define HW_DSP_PRAM_END         (HW_DSP_PRAM + HW_DSP_PRAM_SIZE)
#define HW_DSP_DRAM_END         (HW_DSP_DRAM + HW_DSP_DRAM_SIZE)
#define HW_DSP_PRAM_SIZE        0x40000 // 256KB
#define HW_DSP_DRAM_SIZE        0x40000 // 256KB

//----------------------------- AXI-WRAM
#define HW_AXI_WRAM             (HW_AXI_WRAM_END - HW_AXI_WRAM_SIZE) // 0x1ff80000
#if !defined(SDK_MG20EMU) && !defined(SDK_NE1EMU)
#define HW_AXI_WRAM_END         HW_MAIN_MEM
#else // SDK_MG20EMU || SDK_NE1EMU
#ifdef SDK_MG20EMU
#define HW_AXI_WRAM_END         (HW_MAIN_MEM + HW_MAIN_MEM_MG20EMU_SIZE)
#else // SDK_NE1EMU
#define HW_AXI_WRAM_END         (HW_MAIN_MEM + HW_MAIN_MEM_NE1EMU_SIZE)
#endif // SDK_NE1EMU
#endif // SDK_MG20EMU || SDK_NE1EMU
#define HW_AXI_WRAM_SIZE        0x80000 // 512KB

#define HW_AXI_WRAM_EX          0x1F000000
#define HW_AXI_WRAM_EX_SIZE     0x200000    // 2MB
#define HW_AXI_WRAM_EX_END      (HW_AXI_WRAM_EX + HW_AXI_WRAM_EX_SIZE)

#define HW_AXI_WRAM_EX_LO       HW_AXI_WRAM_EX
#define HW_AXI_WRAM_EX_LO_END   (HW_AXI_WRAM_EX_LO + HW_AXI_WRAM_EX_LO_SIZE)
#define HW_AXI_WRAM_EX_HI       HW_AXI_WRAM_EX_LO_END
#define HW_AXI_WRAM_EX_HI_END   (HW_AXI_WRAM_EX_HI + HW_AXI_WRAM_EX_HI_SIZE)
#define HW_AXI_WRAM_EX_LO_SIZE  (HW_AXI_WRAM_EX_SIZE/2)
#define HW_AXI_WRAM_EX_HI_SIZE  (HW_AXI_WRAM_EX_SIZE/2)

//----------------------------- VRAM
#if !defined(SDK_MG20EMU) && !defined(SDK_NE1EMU)
#define HW_VRAM                 HW_VM_BOUNDARY
#else // SDK_MG20EMU || SDK_NE1EMU
#ifdef SDK_MG20EMU
#define HW_VRAM                 0x1e000000
#else // SDK_NE1EMU
#define HW_VRAM                 HW_IOREG_END
#endif // SDK_NE1EMU
#endif // SDK_MG20EMU || SDK_NE1EMU
#if defined(SDK_TS) || defined(NN_HARDWARE_CTR_TS)
#define HW_VRAM_SIZE            0x600000 // 6MB
#else // SDK_TEG
#define HW_VRAM_SIZE            0x400000 // 4MB
#endif // SDK_TEG
#define HW_VRAM_END             (HW_VRAM + HW_VRAM_SIZE)

#define HW_VRAM_LO              HW_VRAM
#define HW_VRAM_LO_END          (HW_VRAM_LO + HW_VRAM_LO_SIZE)
#define HW_VRAM_HI              HW_VRAM_LO_END
#define HW_VRAM_HI_END          (HW_VRAM_HI + HW_VRAM_HI_SIZE)
#define HW_VRAM_LO_SIZE         (HW_VRAM_SIZE/2)
#define HW_VRAM_HI_SIZE         (HW_VRAM_SIZE/2)

//----------------------------- IOs
#ifndef SDK_NE1EMU
#ifdef SDK_MG20EMU
#define HW_IOREG                0x48000000
#else // SDK_Palladium
#define HW_IOREG                0x10000000
#endif
#else // SDK_NE1EMU
#define HW_IOREG                HW_MAIN_MEM_EX_END
#endif // SDK_NE1EMU
#define HW_IOREG_END            (HW_IOREG + HW_IOREG_SIZE)
#define HW_IOREG_SIZE           0x01000000  // 16MB
#ifndef NN_SYSTEM_PROCESS
#define HW_REG_BASE             HW_IOREG    // alias
#else
#define HW_REG_BASE             0x1eb00000  // for process
#endif

#define HW_AHBP_REG             (HW_IOREG + 0x00100000)
#define HW_APB_REG              (HW_IOREG + 0x00200000)
#define HW_AHBML_REG            (HW_IOREG + 0x00300000)
#define HW_GPU_REG              (HW_IOREG + 0x00400000)
#if !defined(SDK_MG20EMU) && !defined(SDK_NE1EMU)
#define HW_MPCORE_REG           (HW_IOREG + 0x07e00000)
#else // SDK_MG20EMU || SDK_NE1EMU
#ifdef SDK_MG20EMU
#define HW_MPCORE_REG           0xff000000
#else // SDK_NE1EMU
#define HW_MPCORE_REG           0xc0000000
#define HW_NE1IOP_REG           0x18000000
#define HW_NE1SYS_REG           0x18037c00
#define HW_NE1EXBUS_REG         0x1801a000
#define HW_NE1DDR2_REG          0x18021000
#endif // SDK_NE1EMU
#endif // SDK_MG20EMU || SDK_NE1EMU
#define HW_AHBP_REG_END         (HW_AHBP_REG + HW_AHBP_REG_SIZE)
#define HW_APB_REG_END          (HW_APB_REG + HW_APB_REG_SIZE)
#define HW_AHBML_REG_END        (HW_AHBML_REG + HW_AHBML_REG_SIZE)
#define HW_GPU_REG_END          (HW_GPU_REG + HW_GPU_REG_SIZE)
#define HW_MPCORE_REG_END       (HW_MPCORE_REG + HW_MPCORE_REG_SIZE)
#define HW_AHBP_REG_SIZE        0x80000  // 512KB
#define HW_APB_REG_SIZE         0x100000 // 1MB
#define HW_AHBML_REG_SIZE       0x40000  // 256KB
#define HW_GPU_REG_SIZE         0x100000 // 1MB
#define HW_MPCORE_REG_SIZE      0x2000   // 8KB
#ifdef NN_SYSTEM_KERNEL
//#define HW_VIRTUAL_MPCORE_REG   NN_KERN_V_ADDR_MPCORE_PRIVATE_REGION
// TORIAEZU
#define HW_VIRTUAL_MPCORE_REG   0xFFFEE000
#else   // ifdef NN_SYSTEM_KERNEL
#define HW_VIRTUAL_MPCORE_REG   HW_MPCORE_REG
#endif  // ifdef NN_SYSTEM_KERNEL else

//----------------------------- System ROM
#ifdef SDK_MG20EMU
#define HW_BIOS_IMAGE           0xfffe0000
#define HW_BIOS                 0xffff0000
#else // include SDK_NE1EMU
#define HW_BIOS_IMAGE           0x00000000
#define HW_BIOS                 0x00010000
#endif // include SDK_NE1EMU
#define HW_BIOS_END             (HW_BIOS + HW_BIOS_SIZE)
#define HW_BIOS_SIZE            0x8000  // 32KB

#ifdef SDK_MG20EMU
#define HW_BIOS_A9_RSV          (HW_BIOS_A9_RSV_END - HW_BIOS_A9_RSV_SIZE)
#define HW_BIOS_A9_RSV_END      HW_DSP_WRAM
#define HW_BIOS_A9_RSV_SIZE     0x8000  // 32KB
#endif // SDK_MG20EMU

// ブートROMリビジョン情報
#define HW_BIOS_REVISION        (HW_BIOS + 0x20)

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}   /* extern "C" */
#endif
#endif  /* NN_HW_CTR_MPCORE_MMAP_GLOBAL_H_ */
