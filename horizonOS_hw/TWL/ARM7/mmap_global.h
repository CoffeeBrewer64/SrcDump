/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mmap_global.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50823 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_TWL_ARM7_MMAP_GLOBAL_H_
#define NN_HW_TWL_ARM7_MMAP_GLOBAL_H_
#ifdef  __cplusplus
extern  "C" {
#endif
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
    GLOBAL MEMORY MAP
 *---------------------------------------------------------------------------*/

#ifdef SDK_TWL

//----------------------------- MAIN on NITRO hardware
#define HW_MAIN_MEM             0x02000000
#define HW_MAIN_MEM_SIZE        0x00400000
#define HW_MAIN_MEM_EX_SIZE     0x00800000
#define HW_MAIN_MEM_END         (HW_MAIN_MEM + HW_MAIN_MEM_SIZE)
#define HW_MAIN_MEM_EX_END      (HW_MAIN_MEM + HW_MAIN_MEM_EX_SIZE)

#endif // SDK_TWL

//----------------------------- MAIN on TWL hardware
#define HW_TWL_MAIN_MEM_SIZE        0x01000000
#define HW_TWL_MAIN_MEM_EX_SIZE     0x01000000

#define HW_TWL_MAIN_MEM             0x02000000
#define HW_TWL_MAIN_MEM_END         (HW_TWL_MAIN_MEM + HW_TWL_MAIN_MEM_SIZE)
#define HW_TWL_MAIN_MEM_IMAGE       0x0c000000
#define HW_TWL_MAIN_MEM_IMAGE_END   (HW_TWL_MAIN_MEM_IMAGE + HW_TWL_MAIN_MEM_SIZE)
#define HW_TWL_MAIN_MEM_EX          0x0d000000
#define HW_TWL_MAIN_MEM_EX_END      (HW_TWL_MAIN_MEM_EX + HW_TWL_MAIN_MEM_EX_SIZE)

//----------------------------- WRAM_AREA
#define HW_TWL_WRAM_AREA            0x03000000
#define HW_TWL_WRAM_AREA_HALF       (HW_TWL_WRAM_AREA+(HW_TWL_WRAM_AREA_SIZE/2))
#define HW_TWL_WRAM_AREA_END        0x04000000
#define HW_TWL_WRAM_AREA_SIZE       (HW_TWL_WRAM_AREA_END-HW_TWL_WRAM_AREA)

#ifdef SDK_TWL

//----------------------------- WRAM_AREA
#define HW_WRAM_AREA            0x03000000
#define HW_WRAM_AREA_HALF       (HW_WRAM_AREA+(HW_WRAM_AREA_SIZE/2))
#define HW_WRAM_AREA_END        0x04000000
#define HW_WRAM_AREA_SIZE       (HW_WRAM_AREA_END-HW_WRAM_AREA)

//----------------------------- WRAM
#define HW_WRAM                 0x037f8000
#define HW_WRAM_END             0x03800000

//----------------------------- Shared WRAMs
#define HW_WRAM_BASE            0x03000000
#define HW_WRAM_0_SIZE          0x4000
#define HW_WRAM_1_SIZE          0x4000
#define HW_WRAM_SIZE            (HW_WRAM_0_SIZE + HW_WRAM_1_SIZE)

#define HW_WRAM_A_SIZE          0x40000
#define HW_WRAM_B_SIZE          0x40000
#define HW_WRAM_C_SIZE          0x40000
#define HW_WRAM_A_SLOT_SIZE     0x10000
#define HW_WRAM_B_SLOT_SIZE     0x8000
#define HW_WRAM_C_SLOT_SIZE     0x8000
#define HW_WRAM_A_SLOT_NUM      4
#define HW_WRAM_B_SLOT_NUM      8
#define HW_WRAM_C_SLOT_NUM      8

/* ハイブリッド対応コンポーネントでの配置 */
#define HW_WRAM_0_HYB           (HW_WRAM_0_HYB_END - HW_WRAM_0_SIZE)
#define HW_WRAM_0_HYB_END       HW_WRAM_1_HYB
#define HW_WRAM_1_HYB           (HW_WRAM_1_HYB_END - HW_WRAM_1_SIZE)
#define HW_WRAM_1_HYB_END       0x03800000
#define HW_WRAM_HYB             HW_WRAM_0_HYB
#define HW_WRAM_HYB_END         HW_WRAM_1_HYB_END

#define HW_WRAM_A_HYB           0x03000000
#define HW_WRAM_A_HYB_END       (HW_WRAM_A_HYB + HW_WRAM_A_SIZE)

/* TWL限定コンポーネントでの配置 */
#define HW_WRAM_0_LTD           (HW_WRAM_BASE + HW_WRAM_A_SIZE)
#define HW_WRAM_0_LTD_END       (HW_WRAM_0_LTD + HW_WRAM_0_SIZE)
#define HW_WRAM_1_LTD           HW_WRAM_0_LTD_END
#define HW_WRAM_1_LTD_END       (HW_WRAM_1_LTD + HW_WRAM_1_SIZE)
#define HW_WRAM_LTD             HW_WRAM_0_LTD
#define HW_WRAM_LTD_END         HW_WRAM_1_LTD_END

#define HW_WRAM_A_LTD           (HW_WRAM_A_LTD_END - HW_WRAM_A_SIZE)
#define HW_WRAM_A_LTD_END       HW_PRV_WRAM

/* ハイブリッド/TWL限定の両方で共通の定義 */
#define HW_WRAM_B                   (HW_PRV_WRAM - HW_WRAM_A_SIZE - HW_WRAM_B_SIZE - HW_WRAM_C_SIZE)
#define HW_WRAM_B_END               (HW_WRAM_B + HW_WRAM_B_SIZE)
#define HW_WRAM_C                   (HW_WRAM_C_END - HW_WRAM_C_SIZE)
#define HW_WRAM_C_END               HW_WRAM_B
#define HW_WRAM_B_OR_C_MIRROR       HW_WRAM_B_END
#define HW_WRAM_B_OR_C_MIRROR_END   (HW_PRV_WRAM - HW_WRAM_A_SIZE)

//----------------------------- Private WRAMs
#define HW_PRV_WRAM             0x03800000
#define HW_PRV_WRAM_END         (HW_PRV_WRAM + HW_PRV_WRAM_SIZE)
#define HW_PRV_WRAM_SIZE        0x10000

#define HW_TWL_PRVWRAM          HW_PRV_WRAM
#define HW_TWL_PRVWRAM_END      HW_PRV_WRAM_END
#define HW_TWL_PRVWRAM_SIZE     HW_PRV_WRAM_SIZE

//----------------------------- IOs
#define HW_IOREG                0x04000000
#define HW_IOREG_END            0x05000000
#define HW_REG_BASE             HW_IOREG        // alias

//----------------------------- Extra WRAMs (VRAM C/D for ARM9)
#define HW_EXT_WRAM_SIZE        0x40000

#define HW_EXT_WRAM             0x06000000
#define HW_EXT_WRAM_END         (HW_EXT_WRAM + HW_EXT_WRAM_SIZE)

//----------------------------- Cartridge Bus
#define HW_CTRDG_ROM            0x08000000
#define HW_CTRDG_ROM_END        0x0a000000
#define HW_CTRDG_RAM            0x0a000000
#define HW_CTRDG_RAM_END        0x0a010000

//----------------------------- System ROM
#define HW_BIOS_SIZE            0x00004000
#define HW_BIOS                 0x00000000
#define HW_BIOS_END             (HW_BIOS + HW_BIOS_SIZE)
#define HW_TWL_BIOS_SIZE        0x00010000
#define HW_TWL_BIOS             HW_BIOS
#define HW_TWL_BIOS_END         (HW_TWL_BIOS + HW_TWL_BIOS_SIZE)

#define HW_RESET_VECTOR         HW_BIOS

#endif // SDK_TWL

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}   /* extern "C" */
#endif
#endif  /* NN_HW_TWL_ARM7_MMAP_GLOBAL_H_ */
