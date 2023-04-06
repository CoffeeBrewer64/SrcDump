﻿/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     itcm_end.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50823 $
 *---------------------------------------------------------------------------*/

//
// include this instead of using C99 pragma extensions for compatibility
//
#if	defined(__CC_ARM)
#pragma arm section code, rwdata, rodata, zidata

#elif	defined(__MWERKS__)
#pragma section ITCM end

#elif	defined(__GNUC__)
TO BE   DEFINED
#endif
