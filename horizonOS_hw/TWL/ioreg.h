/*---------------------------------------------------------------------------*
  Project:  CtrFirm - IO Register List - 
  File:     TWL/ioreg.h

  Copyright 2009 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Date:: 2010-03-15#$
  $Rev: 12449 $
  $Author: hatamoto_minoru $
 *---------------------------------------------------------------------------*/
// CTR/ioreg.hを無効化
#ifndef NN_HW_IOREG_H_
#define NN_HW_IOREG_H_

#ifdef	SDK_ARM9
#include <nn/hw/TWL/ARM9/ioreg.h>
#else  //SDK_ARM7
#include <nn/hw/TWL/ARM7/ioreg.h>
#endif

#endif //NN_HW_IOREG_H_
