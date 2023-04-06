/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     mmap_parameter.h

  Copyright (C)2009-2013 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 50823 $
 *---------------------------------------------------------------------------*/

#ifndef NN_HW_TWL_COMMON_MMAP_PARAMETER_H_
#define NN_HW_TWL_COMMON_MMAP_PARAMETER_H_
#ifdef  __cplusplus
extern  "C" {
#endif

#ifdef SDK_TWL

//--------------------------------------------------------------------------------
//---- deliver argument area            0x02000000 - 0x02000300
#define HW_PARAM_DELIVER_ARG_OFS           0x000
#define HW_PARAM_DELIVER_ARG_SIZE          0x300
#define HW_PARAM_DELIVER_ARG               (HW_TWL_MAIN_MEM_PARAMETER_BUF + HW_PARAM_DELIVER_ARG_OFS)
#define HW_PARAM_DELIVER_ARG_END           (HW_PARAM_DELIVER_ARG + HW_PARAM_DELIVER_ARG_SIZE)

//---- deliver argument
#define HW_PARAM_DELIVER_ARG_TITLEID_OFS   0x0
#define HW_PARAM_DELIVER_ARG_GAMECODE_OFS  0x8
#define HW_PARAM_DELIVER_ARG_MAKERCODE_OFS 0xc
#define HW_PARAM_DELIVER_ARG_DATASIZE_OFS  0xe
#define HW_PARAM_DELIVER_ARG_FLAG_OFS      0x10
#define HW_PARAM_DELIVER_ARG_DATA_OFS      0x11

#define HW_PARAM_DELIVER_ARG_TITLEID       (HW_TWL_MAIN_MEM_PARAMETER_BUF + HW_PARAM_DELIVER_ARG_TITLEID_OFS)
#define HW_PARAM_DELIVER_ARG_GAMECODE      (HW_TWL_MAIN_MEM_PARAMETER_BUF + HW_PARAM_DELIVER_ARG_GAMECODE_OFS)
#define HW_PARAM_DELIVER_ARG_MAKERCODE     (HW_TWL_MAIN_MEM_PARAMETER_BUF + HW_PARAM_DELIVER_ARG_MAKERCODE_OFS)
#define HW_PARAM_DELIVER_ARG_DATASIZE      (HW_TWL_MAIN_MEM_PARAMETER_BUF + HW_PARAM_DELIVER_ARG_DATASIZE_OFS)
#define HW_PARAM_DELIVER_ARG_FLAG          (HW_TWL_MAIN_MEM_PARAMETER_BUF + HW_PARAM_DELIVER_ARG_FLAG_OFS)
#define HW_PARAM_DELIVER_ARG_DATA          (HW_TWL_MAIN_MEM_PARAMETER_BUF + HW_PARAM_DELIVER_ARG_DATA_OFS)

//----------------------------------------------------------------
//---- launcher parameter area          0x02000300 - 0x02000400
#define HW_PARAM_LAUNCH_PARAM_OFS          0x300
#define HW_PARAM_LAUNCH_PARAM_SIZE         0x100
#define HW_PARAM_LAUNCH_PARAM              (HW_TWL_MAIN_MEM_PARAMETER_BUF + HW_PARAM_LAUNCH_PARAM_OFS)
#define HW_PARAM_LAUNCH_PARAM_END          (HW_PARAM_LAUNCH_PARAM + HW_PARAM_LAUNCH_PARAM_SIZE)

#endif // SDK_TWL

//----------------------------------------------------------------
//---- launcher parameter area          0x02000300 - 0x02000400
#define HW_PARAM_TWL_LAUNCH_PARAM_OFS      0x300
#define HW_PARAM_TWL_LAUNCH_PARAM_SIZE     0x100
#define HW_PARAM_TWL_LAUNCH_PARAM          (HW_TWL_MAIN_MEM_PARAMETER_BUF + HW_PARAM_TWL_LAUNCH_PARAM_OFS)
#define HW_PARAM_TWL_LAUNCH_PARAM_END      (HW_PARAM_TWL_LAUNCH_PARAM + HW_PARAM_TWL_LAUNCH_PARAM_SIZE)

//----------------------------------------------------------------
//---- TWLSettingsData                  0x02000400 - 0x02005e0
#define HW_PARAM_TWL_SETTINGS_DATA_DEFAULT      HW_PARAM_TWL_LAUNCH_PARAM_END
#define HW_PARAM_TWL_SETTINGS_DATA_POINTER      0x02fffdfc
#ifdef SDK_TWL
#define HW_PARAM_TWL_SETTINGS_DATA              (*(u32*)HW_PARAM_TWL_SETTINGS_DATA_POINTER) // ( OS_GetSystemWork()->preloadParameterAddr )
#else // SDK_TWL
#define HW_PARAM_TWL_SETTINGS_DATA              HW_PARAM_TWL_SETTINGS_DATA_DEFAULT
#endif // SDK_TWL
#define HW_PARAM_TWL_SETTINGS_DATA_SIZE         0x1e0
#define HW_PARAM_TWL_SETTINGS_DATA_END          ( HW_PARAM_TWL_SETTINGS_DATA + HW_PARAM_TWL_SETTINGS_DATA_SIZE )

//---- wireless firmware initial data   0x020005e0 - 0x02000600
#define HW_PARAM_TWL_WL_FIRMWARE_DATA           HW_PARAM_TWL_SETTINGS_DATA_END
#define HW_PARAM_TWL_WL_FIRMWARE_DATA_SIZE      0x20
#define HW_PARAM_TWL_WL_FIRMWARE_DATA_END       ( HW_PARAM_TWL_WL_FIRMWARE_DATA + HW_PARAM_TWL_WL_FIRMWARE_DATA_SIZE )

//---- TWL-HW-NormalInfo                0x02000600 - 0x0200620
#define HW_PARAM_TWL_HW_NORMAL_INFO             HW_PARAM_TWL_WL_FIRMWARE_DATA_END
#define HW_PARAM_TWL_HW_NORMAL_INFO_SIZE        0x20
#define HW_PARAM_TWL_HW_NORMAL_INFO_END         ( HW_PARAM_TWL_HW_NORMAL_INFO + HW_PARAM_TWL_HW_NORMAL_INFO_SIZE )

//---- reserved area                    0x02000620 - 0x02004000
#define HW_PARAM_TWL_RESERVED_AREA              0x02000620 // HW_PARAM_TWL_HW_NORMAL_INFO_END
#define HW_PARAM_TWL_RESERVED_AREA_SIZE         0x39e0
#define HW_PARAM_TWL_RESERVED_AREA_END          ( HW_PARAM_TWL_RESERVED + HW_PARAM_TWL_RESERVED_SIZE )

//--------------------------------------------------------------------------------
#ifdef __cplusplus
}   /* extern "C" */
#endif
#endif  /* NN_HW_TWL_COMMON_MMAP_PARAMETER_H_ */
