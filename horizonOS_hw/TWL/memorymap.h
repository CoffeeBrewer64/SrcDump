/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     memorymap.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50823 $
 *---------------------------------------------------------------------------*/

// CTR/memorymap.hを無効化
#ifndef NN_HW_MEMORYMAP_H_
#define NN_HW_MEMORYMAP_H_

#undef  SDK_TWL
#define	SDK_TWL

#ifdef	SDK_ARM9
#include    <nn/hw/TWL/ARM9/mmap_global.h>
#include    <nn/hw/TWL/ARM9/mmap_main.h>
#include    <nn/hw/TWL/ARM9/mmap_tcm.h>

#else  //SDK_ARM7
#include    <nn/hw/TWL/ARM7/mmap_global.h>
#include    <nn/hw/TWL/ARM7/mmap_main.h>
#include    <nn/hw/TWL/ARM7/mmap_wram.h>
#endif

#include    <nn/hw/TWL/common/mmap_shared.h>
#include    <nn/hw/TWL/common/mmap_parameter.h>
#include    <nn/hw/TWL/common/mmap_wramEnv.h>
#include    <nn/hw/TWL/common/mmap_sysmenu.h>
#include    <nn/hw/TWL/ioreg.h>

/* NN_HW_MEMORYMAP_H_ */
#endif
