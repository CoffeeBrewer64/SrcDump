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

#ifndef NN_HW_CTR_ARM9_MMAP_GLOBAL_H_
#define NN_HW_CTR_ARM9_MMAP_GLOBAL_H_

#ifdef  __cplusplus
extern  "C" {
#endif
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
    GLOBAL MEMORY MAP
 *---------------------------------------------------------------------------*/

//----------------------------- ITCM
#define HW_ITCM_IMAGE           0x00000000
#ifdef NN_HARDWARE_CTR
#define HW_ITCM                 0x01ff8000
#else // FIRM_TARGET_FIRM
#define HW_ITCM                 0x07ff8000
#endif // FIRM_TARGET_FIRM
#define HW_ITCM_SIZE            0x8000 // 32KB
#define HW_ITCM_END             (HW_ITCM + HW_ITCM_SIZE)

//----------------------------- DTCM
#define HW_DTCM                 0xfff00000
#define HW_DTCM_END             (HW_DTCM + HW_DTCM_SIZE)
#define HW_DTCM_SIZE            0x4000 // 16KB

//----------------------------- MAIN
#define HW_MAIN_MEM                 0x20000000
#ifdef SDK_MG20EMU
#define HW_MAIN_MEM_MG20EMU_SIZE    0x04000000 // 64MB
#endif

#define HW_MAIN_MEM_END         (HW_MAIN_MEM + HW_MAIN_MEM_SIZE)

#define HW_MAIN_MEM_EIU         HW_MAIN_MEM
#define HW_MAIN_MEM_EIU_END     (HW_MAIN_MEM_EIU + HW_MAIN_MEM_EIU_SIZE)

#define HW_MAIN_MEM_EX          HW_MAIN_MEM_END
#define HW_MAIN_MEM_EX_END      (HW_MAIN_MEM + HW_MAIN_MEM_EX_SIZE)

#define HW_MAIN_MEM_EX_EIU      HW_MAIN_MEM_EIU_END
#define HW_MAIN_MEM_EX_EIU_END  (HW_MAIN_MEM_EIU + HW_MAIN_MEM_EX_EIU_SIZE)


#define HW_PROCESS_FIX_SIZE     0x00100000 // 1MB

#ifdef SDK_MG20EMU
#define HW_MAIN_MEM_SIZE        0x02000000 // 32MB
#define HW_MAIN_MEM_EX_SIZE     0x03E00000 // 62MB
#else
#define HW_MAIN_MEM_SIZE        0x04000000 // 64MB
#define HW_MAIN_MEM_EX_SIZE     0x08000000 // 128MB

#define HW_MAIN_MEM_EIU_SIZE    0x08000000 // 128MB
#define HW_MAIN_MEM_EX_EIU_SIZE 0x10000000 // 256MB
#endif

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
#ifndef SDK_MG20EMU
#define HW_AXI_WRAM_END         HW_MAIN_MEM
#else // SDK_MG20EMU
#define HW_AXI_WRAM_END         (HW_MAIN_MEM + HW_MAIN_MEM_MG20EMU_SIZE)
#endif // SDK_MG20EMU
#define HW_AXI_WRAM_SIZE        0x80000 // 512KB

#define HW_AXI_WRAM_EX          0x1F000000
#define HW_AXI_WRAM_EX_SIZE     0x400000    // 4MB
#define HW_AXI_WRAM_EX_END      (HW_AXI_WRAM_EX + HW_AXI_WRAM_EX_SIZE)

#define HW_AXI_WRAM_EX_LO       HW_AXI_WRAM_EX
#define HW_AXI_WRAM_EX_LO_END   (HW_AXI_WRAM_EX_LO + HW_AXI_WRAM_EX_LO_SIZE)
#define HW_AXI_WRAM_EX_HI       HW_AXI_WRAM_EX_LO_END
#define HW_AXI_WRAM_EX_HI_END   (HW_AXI_WRAM_EX_HI + HW_AXI_WRAM_EX_HI_SIZE)
#define HW_AXI_WRAM_EX_LO_SIZE  (HW_AXI_WRAM_EX_SIZE/2)
#define HW_AXI_WRAM_EX_HI_SIZE  (HW_AXI_WRAM_EX_SIZE/2)

//----------------------------- VRAM
#ifndef SDK_MG20EMU
#define HW_VRAM                 0x18000000
#else // SDK_MG20EMU
#define HW_VRAM                 0x1e000000
#endif // SDK_MG20EMU
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

#define VM_PROCESS_MAIN_MEM     0x20000000
#define VM_PROCESS_MAIN_SIZE    (0x20040000 - VM_PROCESS_MAIN_MEM)

//----------------------------- A11 System Memory (include MAIN,AXI-WRAM,DSP,VRAM)
#define HW_A11_SYS_MEM          HW_VRAM
#define HW_A11_SYS_MEM_END      HW_MAIN_MEM_EX_END

//----------------------------- Private WRAM
#ifndef SDK_MG20EMU
#define HW_PRV_WRAM             0x08000000
#define HW_PRV_WRAM_SIZE        0x100000 // 1MB
#define HW_PRV_WRAM_END         (HW_PRV_WRAM + HW_PRV_WRAM_SIZE)

#define HW_PRV_WRAM_EIU         HW_PRV_WRAM
#define HW_PRV_WRAM_EIU_SIZE    0x180000 // 1.5MB
#define HW_PRV_WRAM_EIU_END     (HW_PRV_WRAM + HW_PRV_WRAM_EIU_SIZE)
#else // SDK_MG20EMU
#define HW_PRV_WRAM             0x10038000
#define HW_PRV_WRAM_SIZE        0xc8000 // 800KB
#define HW_PRV_WRAM_END         (HW_PRV_WRAM + HW_PRV_WRAM_SIZE)
#endif // SDK_MG20EMU

//----------------------------- IOs
#ifndef SDK_MG20EMU
#define HW_IOREG                0x10000000
#define HW_IOREG_END            0x18000000
#define HW_REG_BASE             HW_IOREG        // alias

#else // SDK_MG20EMU
#define HW_IOREG                0x08000000
#define HW_IOREG_END            0x10000000

#if defined(NN_HARDWARE_CTR_MG20) && defined(NN_PROCESSOR_ARM946ES)
#define HW_REG_BASE             HW_MG20IOP_REG  // alias
#else
#define HW_REG_BASE             HW_IOREG        // alias
#endif

#define HW_MG20IOP_REG          0x40000000
#define HW_MG20IOP_REG_END      0x40200000

#endif // SDK_MG20EMU

#define HW_PRV_REG              (HW_IOREG + 0)
#define HW_AHBP_REG             (HW_IOREG + 0x00100000)
#define HW_PRV_REG_END          (HW_PRV_REG + HW_PRV_REG_SIZE)
#define HW_AHBP_REG_END         (HW_AHBP_REG + HW_AHBP_REG_SIZE)
#define HW_PRV_REG_SIZE         0x20000 // 128MB
#define HW_AHBP_REG_SIZE        0x80000 // 512MB

//----------------------------- System ROM
#ifdef SDK_MG20EMU
#define HW_BIOS                 0x00000000
#else // SDK_MG20EMU
#define HW_BIOS                 0xffff0000
#endif // SDK_MG20EMU
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
#endif  /* NN_HW_CTR_ARM9_MMAP_GLOBAL_H_ */
