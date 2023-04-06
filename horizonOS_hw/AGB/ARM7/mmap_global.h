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

#ifndef NN_HW_AGB_ARM7_MMAP_GLOBAL_H_
#define NN_HW_AGB_ARM7_MMAP_GLOBAL_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// GLOBAL MEMORY MAP
//---------------------------------------------------------------------------

//------------------------------------------------
//  Physical Address
//
//----------------------------- MAIN
#define HW_MAIN_MEM             0x02000000
#define HW_MAIN_MEM_END         (HW_MAIN_MEM + HW_MAIN_MEM_SIZE)
#define HW_MAIN_MEM_SIZE        0x40000 // 256KB

//----------------------------- WRAM
#define HW_WRAM                 0x03000000
#define HW_WRAM_END             (HW_WRAM + HW_WRAM_SIZE)
#define HW_WRAM_SIZE            0x8000 // 32KB

//----------------------------- IOs
#define HW_IOREG                0x04000000
#define HW_IOREG_END            0x05000000
#define HW_REG_BASE             HW_IOREG        // alias

//----------------------------- VRAMs
#define HW_BG_PLTT              0x05000000
#define HW_BG_PLTT_END          (HW_BG_PLTT + HW_BG_PLTT_SIZE)
#define HW_BG_PLTT_SIZE         0x200 // 512B
#define HW_OBJ_PLTT             HW_BG_PLTT_END
#define HW_OBJ_PLTT_END         (HW_OBJ_PLTT + HW_OBJ_PLTT_SIZE)
#define HW_OBJ_PLTT_SIZE        0x200 // 512B
#define HW_PLTT                 HW_BG_PLTT
#define HW_PLTT_END             (HW_PLTT + HW_PLTT_SIZE)
#define HW_PLTT_SIZE            (HW_BG_PLTT_SIZE + HW_OBJ_PLTT_SIZE) // 1KB
#define HW_BG_VRAM              0x06000000
#define HW_BG_VRAM_END          (HW_BG_VRAM + HW_BG_VRAM_SIZE)
#define HW_BG_VRAM_SIZE         0x10000 // 64KB
#define HW_OBJ_VRAM             HW_BG_VRAM_END
#define HW_OBJ_VRAM_END         (HW_OBJ_VRAM + HW_OBJ_VRAM_SIZE)
#define HW_OBJ_VRAM_SIZE        0x8000 // 32KB
#define HW_OAM                  0x07000000
#define HW_OAM_END              (HW_OAM + HW_OAM_SIZE)
#define HW_OAM_SIZE             0x400 // 1KB

//----------------------------- Cartridge Bus
#define HW_CTRDG_ROM            0x08000000
#define HW_CTRDG_ROM_END        0x0e000000
#define HW_CTRDG_RAM            0x0e000000
#define HW_CTRDG_RAM_END        0x0e010000

//----------------------------- System ROM
#define HW_BIOS                 0x00000000
#define HW_BIOS_END             (HW_BIOS + HW_BIOS_SIZE)
#define HW_BIOS_SIZE            0x4000 // 16KB

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_AGB_ARM7_MMAP_GLOBAL_H_ */
#endif
