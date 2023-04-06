/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-MG20/ARM9/ioreg_mg20patch_PDN.h

  Copyright 2008 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
//
//  I was generated automatically, don't edit me directly!!!
//
#ifndef NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_PDN_H_
#define NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_PDN_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* SPM_CLK */

#define REG_SPM_CLK_OFFSET                                 0x00004
#define REG_SPM_CLK_ADDR                                   (HW_MG20IOP_REG + REG_SPM_CLK_OFFSET)
#define reg_PDN_SPM_CLK                                    (*( REGType16v *) REG_SPM_CLK_ADDR)


/*
 * Definitions of Register fields
 */


/* SPM_CLK */

#define REG_PDN_SPM_CLK_SND_SHIFT                          10
#define REG_PDN_SPM_CLK_SND_SIZE                           1
#define REG_PDN_SPM_CLK_SND_MASK                           0x0400

#define REG_PDN_SPM_CLK_CKI_SHIFT                          9
#define REG_PDN_SPM_CLK_CKI_SIZE                           1
#define REG_PDN_SPM_CLK_CKI_MASK                           0x0200

#define REG_PDN_SPM_CLK_XTAL_SHIFT                         8
#define REG_PDN_SPM_CLK_XTAL_SIZE                          1
#define REG_PDN_SPM_CLK_XTAL_MASK                          0x0100

#define REG_PDN_SPM_CLK_I2S_SHIFT                          5
#define REG_PDN_SPM_CLK_I2S_SIZE                           1
#define REG_PDN_SPM_CLK_I2S_MASK                           0x0020

#define REG_PDN_SPM_CLK_NS_SHIFT                           4
#define REG_PDN_SPM_CLK_NS_SIZE                            1
#define REG_PDN_SPM_CLK_NS_MASK                            0x0010

#define REG_PDN_SPM_CLK_AES_SHIFT                          3
#define REG_PDN_SPM_CLK_AES_SIZE                           1
#define REG_PDN_SPM_CLK_AES_MASK                           0x0008

#define REG_PDN_SPM_CLK_SD_SHIFT                           2
#define REG_PDN_SPM_CLK_SD_SIZE                            1
#define REG_PDN_SPM_CLK_SD_MASK                            0x0004

#define REG_PDN_SPM_CLK_CAM_SHIFT                          1
#define REG_PDN_SPM_CLK_CAM_SIZE                           1
#define REG_PDN_SPM_CLK_CAM_MASK                           0x0002

#define REG_PDN_SPM_CLK_USB_SHIFT                          1
#define REG_PDN_SPM_CLK_USB_SIZE                           1
#define REG_PDN_SPM_CLK_USB_MASK                           0x0002

#ifndef SDK_ASM
#define REG_PDN_SPM_CLK_FIELD( snd, cki, xtal, i2s, ns, aes, sd, cam, usb ) \
    (u16)( \
    ((u32)(snd) << REG_PDN_SPM_CLK_SND_SHIFT) | \
    ((u32)(cki) << REG_PDN_SPM_CLK_CKI_SHIFT) | \
    ((u32)(xtal) << REG_PDN_SPM_CLK_XTAL_SHIFT) | \
    ((u32)(i2s) << REG_PDN_SPM_CLK_I2S_SHIFT) | \
    ((u32)(ns) << REG_PDN_SPM_CLK_NS_SHIFT) | \
    ((u32)(aes) << REG_PDN_SPM_CLK_AES_SHIFT) | \
    ((u32)(sd) << REG_PDN_SPM_CLK_SD_SHIFT) | \
    ((u32)(cam) << REG_PDN_SPM_CLK_CAM_SHIFT) | \
    ((u32)(usb) << REG_PDN_SPM_CLK_USB_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_PDN_H_ */
#endif
