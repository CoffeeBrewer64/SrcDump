/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR/MPCore/ioreg_OSP.h

  Copyright 2008 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/

#if defined(SDK_TS) || defined(NN_HARDWARE_CTR_TS)
#include <nn/hw/CTR-EIU/MPCore/ioreg_eiupatch_OSP.h>

#elif defined(SDK_NE1EMU)
#include <nn/hw/CTR-NE1TB/MPCore/ioreg_ne1patch_OSP.h>

#else
#include <nn/hw/CTR-TEG2/MPCore/ioreg_OSP.h>

#endif

