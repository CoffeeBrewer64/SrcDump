/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mmap_vm.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50823 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_CTR_MPCORE_MMAP_VM_H_
#define NN_HW_CTR_MPCORE_MMAP_VM_H_

#include <nn/hw/CTR/MPCore/mmap_common.h>

#ifdef  __cplusplus
extern  "C" {
#endif
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
    GLOBAL MEMORY MAP
 *---------------------------------------------------------------------------*/

//----------------------------- VM
#define VM_PROCESS_MAIN_MEM     0x00100000
#define VM_PROCESS_MAIN_SIZE    (HW_VM_BOUNDARY - VM_PROCESS_MAIN_MEM) 


/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}   /* extern "C" */
#endif
#endif  /* NN_HW_CTR_MPCORE_MMAP_VM_H_ */
