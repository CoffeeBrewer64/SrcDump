/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-MG20/ARM9/ioreg_mg20patch_OS.h

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
#ifndef NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_OS_H_
#define NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_OS_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* SE */

#define REG_SE_OFFSET                                      0x10000
#define REG_SE_ADDR                                        (HW_MG20IOP_REG + REG_SE_OFFSET)
#define reg_OS_SE                                          (*( REGType32v *) REG_SE_ADDR)

/* IE */

#define REG_IE_OFFSET                                      0x10004
#define REG_IE_ADDR                                        (HW_MG20IOP_REG + REG_IE_OFFSET)
#define reg_OS_IE                                          (*( REGType32v *) REG_IE_ADDR)

/* IF */

#define REG_IF_OFFSET                                      0x10008
#define REG_IF_ADDR                                        (HW_MG20IOP_REG + REG_IF_OFFSET)
#define reg_OS_IF                                          (*( REGType32v *) REG_IF_ADDR)

/* TM0CNT_L */

#define REG_TM0CNT_L_OFFSET                                0x30000
#define REG_TM0CNT_L_ADDR                                  (HW_MG20IOP_REG + REG_TM0CNT_L_OFFSET)
#define reg_OS_TM0CNT_L                                    (*( REGType16v *) REG_TM0CNT_L_ADDR)

/* TM0CNT_H */

#define REG_TM0CNT_H_OFFSET                                0x30002
#define REG_TM0CNT_H_ADDR                                  (HW_MG20IOP_REG + REG_TM0CNT_H_OFFSET)
#define reg_OS_TM0CNT_H                                    (*( REGType16v *) REG_TM0CNT_H_ADDR)

/* TM1CNT_L */

#define REG_TM1CNT_L_OFFSET                                0x30004
#define REG_TM1CNT_L_ADDR                                  (HW_MG20IOP_REG + REG_TM1CNT_L_OFFSET)
#define reg_OS_TM1CNT_L                                    (*( REGType16v *) REG_TM1CNT_L_ADDR)

/* TM1CNT_H */

#define REG_TM1CNT_H_OFFSET                                0x30006
#define REG_TM1CNT_H_ADDR                                  (HW_MG20IOP_REG + REG_TM1CNT_H_OFFSET)
#define reg_OS_TM1CNT_H                                    (*( REGType16v *) REG_TM1CNT_H_ADDR)

/* TM2CNT_L */

#define REG_TM2CNT_L_OFFSET                                0x30008
#define REG_TM2CNT_L_ADDR                                  (HW_MG20IOP_REG + REG_TM2CNT_L_OFFSET)
#define reg_OS_TM2CNT_L                                    (*( REGType16v *) REG_TM2CNT_L_ADDR)

/* TM2CNT_H */

#define REG_TM2CNT_H_OFFSET                                0x3000a
#define REG_TM2CNT_H_ADDR                                  (HW_MG20IOP_REG + REG_TM2CNT_H_OFFSET)
#define reg_OS_TM2CNT_H                                    (*( REGType16v *) REG_TM2CNT_H_ADDR)

/* TM3CNT_L */

#define REG_TM3CNT_L_OFFSET                                0x3000c
#define REG_TM3CNT_L_ADDR                                  (HW_MG20IOP_REG + REG_TM3CNT_L_OFFSET)
#define reg_OS_TM3CNT_L                                    (*( REGType16v *) REG_TM3CNT_L_ADDR)

/* TM3CNT_H */

#define REG_TM3CNT_H_OFFSET                                0x3000e
#define REG_TM3CNT_H_ADDR                                  (HW_MG20IOP_REG + REG_TM3CNT_H_OFFSET)
#define reg_OS_TM3CNT_H                                    (*( REGType16v *) REG_TM3CNT_H_ADDR)


/*
 * Definitions of Register fields
 */


/* SE */

/* IE */

#define REG_OS_IE_XD_ABT_SHIFT                             31
#define REG_OS_IE_XD_ABT_SIZE                              1
#define REG_OS_IE_XD_ABT_MASK                              0x80000000

#define REG_OS_IE_XD_SHIFT                                 31
#define REG_OS_IE_XD_SIZE                                  1
#define REG_OS_IE_XD_MASK                                  0x80000000

#define REG_OS_IE_LMC_SHIFT                                12
#define REG_OS_IE_LMC_SIZE                                 1
#define REG_OS_IE_LMC_MASK                                 0x00001000

#define REG_OS_IE_CGC_DET_SHIFT                            31
#define REG_OS_IE_CGC_DET_SIZE                             1
#define REG_OS_IE_CGC_DET_MASK                             0x80000000

#define REG_OS_IE_CGC_I_SHIFT                              29
#define REG_OS_IE_CGC_I_SIZE                               1
#define REG_OS_IE_CGC_I_MASK                               0x20000000

#define REG_OS_IE_CMC2_SHIFT                               31
#define REG_OS_IE_CMC2_SIZE                                1
#define REG_OS_IE_CMC2_MASK                                0x80000000

#define REG_OS_IE_CMC1_SHIFT                               31
#define REG_OS_IE_CMC1_SIZE                                1
#define REG_OS_IE_CMC1_MASK                                0x80000000

#define REG_OS_IE_RSA_SHIFT                                31
#define REG_OS_IE_RSA_SIZE                                 1
#define REG_OS_IE_RSA_MASK                                 0x80000000

#define REG_OS_IE_J_TX_SHIFT                               31
#define REG_OS_IE_J_TX_SIZE                                1
#define REG_OS_IE_J_TX_MASK                                0x80000000

#define REG_OS_IE_J_RX_SHIFT                               31
#define REG_OS_IE_J_RX_SIZE                                1
#define REG_OS_IE_J_RX_MASK                                0x80000000

#define REG_OS_IE_SD3_A_SHIFT                              31
#define REG_OS_IE_SD3_A_SIZE                               1
#define REG_OS_IE_SD3_A_MASK                               0x80000000

#define REG_OS_IE_SD3_SHIFT                                31
#define REG_OS_IE_SD3_SIZE                                 1
#define REG_OS_IE_SD3_MASK                                 0x80000000

#define REG_OS_IE_SD1_A_SHIFT                              23
#define REG_OS_IE_SD1_A_SIZE                               1
#define REG_OS_IE_SD1_A_MASK                               0x00800000

#define REG_OS_IE_SD1_SHIFT                                13
#define REG_OS_IE_SD1_SIZE                                 1
#define REG_OS_IE_SD1_MASK                                 0x00002000

#define REG_OS_IE_CAM1_SHIFT                               21
#define REG_OS_IE_CAM1_SIZE                                1
#define REG_OS_IE_CAM1_MASK                                0x00200000

#define REG_OS_IE_AES_SHIFT                                16
#define REG_OS_IE_AES_SIZE                                 1
#define REG_OS_IE_AES_MASK                                 0x00010000

#define REG_OS_IE_PXI_RX_SHIFT                             10
#define REG_OS_IE_PXI_RX_SIZE                              1
#define REG_OS_IE_PXI_RX_MASK                              0x00000400

#define REG_OS_IE_PXI_TX_SHIFT                             11
#define REG_OS_IE_PXI_TX_SIZE                              1
#define REG_OS_IE_PXI_TX_MASK                              0x00000800

#define REG_OS_IE_A11_SHIFT                                31
#define REG_OS_IE_A11_SIZE                                 1
#define REG_OS_IE_A11_MASK                                 0x80000000

#define REG_OS_IE_T3_SHIFT                                 7
#define REG_OS_IE_T3_SIZE                                  1
#define REG_OS_IE_T3_MASK                                  0x00000080

#define REG_OS_IE_T2_SHIFT                                 6
#define REG_OS_IE_T2_SIZE                                  1
#define REG_OS_IE_T2_MASK                                  0x00000040

#define REG_OS_IE_T1_SHIFT                                 5
#define REG_OS_IE_T1_SIZE                                  1
#define REG_OS_IE_T1_MASK                                  0x00000020

#define REG_OS_IE_T0_SHIFT                                 4
#define REG_OS_IE_T0_SIZE                                  1
#define REG_OS_IE_T0_MASK                                  0x00000010

#define REG_OS_IE_D7_SHIFT                                 31
#define REG_OS_IE_D7_SIZE                                  1
#define REG_OS_IE_D7_MASK                                  0x80000000

#define REG_OS_IE_D6_SHIFT                                 31
#define REG_OS_IE_D6_SIZE                                  1
#define REG_OS_IE_D6_MASK                                  0x80000000

#define REG_OS_IE_D5_SHIFT                                 31
#define REG_OS_IE_D5_SIZE                                  1
#define REG_OS_IE_D5_MASK                                  0x80000000

#define REG_OS_IE_D4_SHIFT                                 31
#define REG_OS_IE_D4_SIZE                                  1
#define REG_OS_IE_D4_MASK                                  0x80000000

#define REG_OS_IE_D3_SHIFT                                 3
#define REG_OS_IE_D3_SIZE                                  1
#define REG_OS_IE_D3_MASK                                  0x00000008

#define REG_OS_IE_D2_SHIFT                                 2
#define REG_OS_IE_D2_SIZE                                  1
#define REG_OS_IE_D2_MASK                                  0x00000004

#define REG_OS_IE_D1_SHIFT                                 1
#define REG_OS_IE_D1_SIZE                                  1
#define REG_OS_IE_D1_MASK                                  0x00000002

#define REG_OS_IE_D0_SHIFT                                 0
#define REG_OS_IE_D0_SIZE                                  1
#define REG_OS_IE_D0_MASK                                  0x00000001

#ifndef SDK_ASM
#define REG_OS_IE_FIELD( xd_abt, xd, lmc, cgc_det, cgc_i, cmc2, cmc1, rsa, j_tx, j_rx, sd3_a, sd3, sd1_a, sd1, cam1, aes, pxi_rx, pxi_tx, a11, t3, t2, t1, t0, d7, d6, d5, d4, d3, d2, d1, d0 ) \
    (u32)( \
    ((u32)(xd_abt) << REG_OS_IE_XD_ABT_SHIFT) | \
    ((u32)(xd) << REG_OS_IE_XD_SHIFT) | \
    ((u32)(lmc) << REG_OS_IE_LMC_SHIFT) | \
    ((u32)(cgc_det) << REG_OS_IE_CGC_DET_SHIFT) | \
    ((u32)(cgc_i) << REG_OS_IE_CGC_I_SHIFT) | \
    ((u32)(cmc2) << REG_OS_IE_CMC2_SHIFT) | \
    ((u32)(cmc1) << REG_OS_IE_CMC1_SHIFT) | \
    ((u32)(rsa) << REG_OS_IE_RSA_SHIFT) | \
    ((u32)(j_tx) << REG_OS_IE_J_TX_SHIFT) | \
    ((u32)(j_rx) << REG_OS_IE_J_RX_SHIFT) | \
    ((u32)(sd3_a) << REG_OS_IE_SD3_A_SHIFT) | \
    ((u32)(sd3) << REG_OS_IE_SD3_SHIFT) | \
    ((u32)(sd1_a) << REG_OS_IE_SD1_A_SHIFT) | \
    ((u32)(sd1) << REG_OS_IE_SD1_SHIFT) | \
    ((u32)(cam1) << REG_OS_IE_CAM1_SHIFT) | \
    ((u32)(aes) << REG_OS_IE_AES_SHIFT) | \
    ((u32)(pxi_rx) << REG_OS_IE_PXI_RX_SHIFT) | \
    ((u32)(pxi_tx) << REG_OS_IE_PXI_TX_SHIFT) | \
    ((u32)(a11) << REG_OS_IE_A11_SHIFT) | \
    ((u32)(t3) << REG_OS_IE_T3_SHIFT) | \
    ((u32)(t2) << REG_OS_IE_T2_SHIFT) | \
    ((u32)(t1) << REG_OS_IE_T1_SHIFT) | \
    ((u32)(t0) << REG_OS_IE_T0_SHIFT) | \
    ((u32)(d7) << REG_OS_IE_D7_SHIFT) | \
    ((u32)(d6) << REG_OS_IE_D6_SHIFT) | \
    ((u32)(d5) << REG_OS_IE_D5_SHIFT) | \
    ((u32)(d4) << REG_OS_IE_D4_SHIFT) | \
    ((u32)(d3) << REG_OS_IE_D3_SHIFT) | \
    ((u32)(d2) << REG_OS_IE_D2_SHIFT) | \
    ((u32)(d1) << REG_OS_IE_D1_SHIFT) | \
    ((u32)(d0) << REG_OS_IE_D0_SHIFT))
#endif


/* IF */

#define REG_OS_IF_XD_ABT_SHIFT                             31
#define REG_OS_IF_XD_ABT_SIZE                              1
#define REG_OS_IF_XD_ABT_MASK                              0x80000000

#define REG_OS_IF_XD_SHIFT                                 31
#define REG_OS_IF_XD_SIZE                                  1
#define REG_OS_IF_XD_MASK                                  0x80000000

#define REG_OS_IF_LMC_SHIFT                                12
#define REG_OS_IF_LMC_SIZE                                 1
#define REG_OS_IF_LMC_MASK                                 0x00001000

#define REG_OS_IF_CGC_DET_SHIFT                            31
#define REG_OS_IF_CGC_DET_SIZE                             1
#define REG_OS_IF_CGC_DET_MASK                             0x80000000

#define REG_OS_IF_CGC_I_SHIFT                              29
#define REG_OS_IF_CGC_I_SIZE                               1
#define REG_OS_IF_CGC_I_MASK                               0x20000000

#define REG_OS_IF_CMC2_SHIFT                               31
#define REG_OS_IF_CMC2_SIZE                                1
#define REG_OS_IF_CMC2_MASK                                0x80000000

#define REG_OS_IF_CMC1_SHIFT                               31
#define REG_OS_IF_CMC1_SIZE                                1
#define REG_OS_IF_CMC1_MASK                                0x80000000

#define REG_OS_IF_RSA_SHIFT                                31
#define REG_OS_IF_RSA_SIZE                                 1
#define REG_OS_IF_RSA_MASK                                 0x80000000

#define REG_OS_IF_J_TX_SHIFT                               31
#define REG_OS_IF_J_TX_SIZE                                1
#define REG_OS_IF_J_TX_MASK                                0x80000000

#define REG_OS_IF_J_RX_SHIFT                               31
#define REG_OS_IF_J_RX_SIZE                                1
#define REG_OS_IF_J_RX_MASK                                0x80000000

#define REG_OS_IF_SD3_A_SHIFT                              31
#define REG_OS_IF_SD3_A_SIZE                               1
#define REG_OS_IF_SD3_A_MASK                               0x80000000

#define REG_OS_IF_SD3_SHIFT                                31
#define REG_OS_IF_SD3_SIZE                                 1
#define REG_OS_IF_SD3_MASK                                 0x80000000

#define REG_OS_IF_SD1_A_SHIFT                              23
#define REG_OS_IF_SD1_A_SIZE                               1
#define REG_OS_IF_SD1_A_MASK                               0x00800000

#define REG_OS_IF_SD1_SHIFT                                13
#define REG_OS_IF_SD1_SIZE                                 1
#define REG_OS_IF_SD1_MASK                                 0x00002000

#define REG_OS_IF_CAM1_SHIFT                               21
#define REG_OS_IF_CAM1_SIZE                                1
#define REG_OS_IF_CAM1_MASK                                0x00200000

#define REG_OS_IF_AES_SHIFT                                16
#define REG_OS_IF_AES_SIZE                                 1
#define REG_OS_IF_AES_MASK                                 0x00010000

#define REG_OS_IF_PXI_RX_SHIFT                             10
#define REG_OS_IF_PXI_RX_SIZE                              1
#define REG_OS_IF_PXI_RX_MASK                              0x00000400

#define REG_OS_IF_PXI_TX_SHIFT                             11
#define REG_OS_IF_PXI_TX_SIZE                              1
#define REG_OS_IF_PXI_TX_MASK                              0x00000800

#define REG_OS_IF_A11_SHIFT                                31
#define REG_OS_IF_A11_SIZE                                 1
#define REG_OS_IF_A11_MASK                                 0x80000000

#define REG_OS_IF_T3_SHIFT                                 7
#define REG_OS_IF_T3_SIZE                                  1
#define REG_OS_IF_T3_MASK                                  0x00000080

#define REG_OS_IF_T2_SHIFT                                 6
#define REG_OS_IF_T2_SIZE                                  1
#define REG_OS_IF_T2_MASK                                  0x00000040

#define REG_OS_IF_T1_SHIFT                                 5
#define REG_OS_IF_T1_SIZE                                  1
#define REG_OS_IF_T1_MASK                                  0x00000020

#define REG_OS_IF_T0_SHIFT                                 4
#define REG_OS_IF_T0_SIZE                                  1
#define REG_OS_IF_T0_MASK                                  0x00000010

#define REG_OS_IF_D7_SHIFT                                 31
#define REG_OS_IF_D7_SIZE                                  1
#define REG_OS_IF_D7_MASK                                  0x80000000

#define REG_OS_IF_D6_SHIFT                                 31
#define REG_OS_IF_D6_SIZE                                  1
#define REG_OS_IF_D6_MASK                                  0x80000000

#define REG_OS_IF_D5_SHIFT                                 31
#define REG_OS_IF_D5_SIZE                                  1
#define REG_OS_IF_D5_MASK                                  0x80000000

#define REG_OS_IF_D4_SHIFT                                 31
#define REG_OS_IF_D4_SIZE                                  1
#define REG_OS_IF_D4_MASK                                  0x80000000

#define REG_OS_IF_D3_SHIFT                                 3
#define REG_OS_IF_D3_SIZE                                  1
#define REG_OS_IF_D3_MASK                                  0x00000008

#define REG_OS_IF_D2_SHIFT                                 2
#define REG_OS_IF_D2_SIZE                                  1
#define REG_OS_IF_D2_MASK                                  0x00000004

#define REG_OS_IF_D1_SHIFT                                 1
#define REG_OS_IF_D1_SIZE                                  1
#define REG_OS_IF_D1_MASK                                  0x00000002

#define REG_OS_IF_D0_SHIFT                                 0
#define REG_OS_IF_D0_SIZE                                  1
#define REG_OS_IF_D0_MASK                                  0x00000001

#ifndef SDK_ASM
#define REG_OS_IF_FIELD( xd_abt, xd, lmc, cgc_det, cgc_i, cmc2, cmc1, rsa, j_tx, j_rx, sd3_a, sd3, sd1_a, sd1, cam1, aes, pxi_rx, pxi_tx, a11, t3, t2, t1, t0, d7, d6, d5, d4, d3, d2, d1, d0 ) \
    (u32)( \
    ((u32)(xd_abt) << REG_OS_IF_XD_ABT_SHIFT) | \
    ((u32)(xd) << REG_OS_IF_XD_SHIFT) | \
    ((u32)(lmc) << REG_OS_IF_LMC_SHIFT) | \
    ((u32)(cgc_det) << REG_OS_IF_CGC_DET_SHIFT) | \
    ((u32)(cgc_i) << REG_OS_IF_CGC_I_SHIFT) | \
    ((u32)(cmc2) << REG_OS_IF_CMC2_SHIFT) | \
    ((u32)(cmc1) << REG_OS_IF_CMC1_SHIFT) | \
    ((u32)(rsa) << REG_OS_IF_RSA_SHIFT) | \
    ((u32)(j_tx) << REG_OS_IF_J_TX_SHIFT) | \
    ((u32)(j_rx) << REG_OS_IF_J_RX_SHIFT) | \
    ((u32)(sd3_a) << REG_OS_IF_SD3_A_SHIFT) | \
    ((u32)(sd3) << REG_OS_IF_SD3_SHIFT) | \
    ((u32)(sd1_a) << REG_OS_IF_SD1_A_SHIFT) | \
    ((u32)(sd1) << REG_OS_IF_SD1_SHIFT) | \
    ((u32)(cam1) << REG_OS_IF_CAM1_SHIFT) | \
    ((u32)(aes) << REG_OS_IF_AES_SHIFT) | \
    ((u32)(pxi_rx) << REG_OS_IF_PXI_RX_SHIFT) | \
    ((u32)(pxi_tx) << REG_OS_IF_PXI_TX_SHIFT) | \
    ((u32)(a11) << REG_OS_IF_A11_SHIFT) | \
    ((u32)(t3) << REG_OS_IF_T3_SHIFT) | \
    ((u32)(t2) << REG_OS_IF_T2_SHIFT) | \
    ((u32)(t1) << REG_OS_IF_T1_SHIFT) | \
    ((u32)(t0) << REG_OS_IF_T0_SHIFT) | \
    ((u32)(d7) << REG_OS_IF_D7_SHIFT) | \
    ((u32)(d6) << REG_OS_IF_D6_SHIFT) | \
    ((u32)(d5) << REG_OS_IF_D5_SHIFT) | \
    ((u32)(d4) << REG_OS_IF_D4_SHIFT) | \
    ((u32)(d3) << REG_OS_IF_D3_SHIFT) | \
    ((u32)(d2) << REG_OS_IF_D2_SHIFT) | \
    ((u32)(d1) << REG_OS_IF_D1_SHIFT) | \
    ((u32)(d0) << REG_OS_IF_D0_SHIFT))
#endif


/* TM0CNT_L */

#define REG_OS_TM0CNT_L_CTR_SHIFT                          0
#define REG_OS_TM0CNT_L_CTR_SIZE                           16
#define REG_OS_TM0CNT_L_CTR_MASK                           0xffff

#ifndef SDK_ASM
#define REG_OS_TM0CNT_L_FIELD( ctr ) \
    (u16)( \
    ((u32)(ctr) << REG_OS_TM0CNT_L_CTR_SHIFT))
#endif


/* TM0CNT_H */

#define REG_OS_TM0CNT_H_E_SHIFT                            7
#define REG_OS_TM0CNT_H_E_SIZE                             1
#define REG_OS_TM0CNT_H_E_MASK                             0x0080

#define REG_OS_TM0CNT_H_I_SHIFT                            6
#define REG_OS_TM0CNT_H_I_SIZE                             1
#define REG_OS_TM0CNT_H_I_MASK                             0x0040

#define REG_OS_TM0CNT_H_PS_SHIFT                           0
#define REG_OS_TM0CNT_H_PS_SIZE                            2
#define REG_OS_TM0CNT_H_PS_MASK                            0x0003

#ifndef SDK_ASM
#define REG_OS_TM0CNT_H_FIELD( e, i, ps ) \
    (u16)( \
    ((u32)(e) << REG_OS_TM0CNT_H_E_SHIFT) | \
    ((u32)(i) << REG_OS_TM0CNT_H_I_SHIFT) | \
    ((u32)(ps) << REG_OS_TM0CNT_H_PS_SHIFT))
#endif


/* TM1CNT_L */

#define REG_OS_TM1CNT_L_CTR_SHIFT                          0
#define REG_OS_TM1CNT_L_CTR_SIZE                           16
#define REG_OS_TM1CNT_L_CTR_MASK                           0xffff

#ifndef SDK_ASM
#define REG_OS_TM1CNT_L_FIELD( ctr ) \
    (u16)( \
    ((u32)(ctr) << REG_OS_TM1CNT_L_CTR_SHIFT))
#endif


/* TM1CNT_H */

#define REG_OS_TM1CNT_H_E_SHIFT                            7
#define REG_OS_TM1CNT_H_E_SIZE                             1
#define REG_OS_TM1CNT_H_E_MASK                             0x0080

#define REG_OS_TM1CNT_H_I_SHIFT                            6
#define REG_OS_TM1CNT_H_I_SIZE                             1
#define REG_OS_TM1CNT_H_I_MASK                             0x0040

#define REG_OS_TM1CNT_H_CH_SHIFT                           2
#define REG_OS_TM1CNT_H_CH_SIZE                            1
#define REG_OS_TM1CNT_H_CH_MASK                            0x0004

#define REG_OS_TM1CNT_H_PS_SHIFT                           0
#define REG_OS_TM1CNT_H_PS_SIZE                            2
#define REG_OS_TM1CNT_H_PS_MASK                            0x0003

#ifndef SDK_ASM
#define REG_OS_TM1CNT_H_FIELD( e, i, ch, ps ) \
    (u16)( \
    ((u32)(e) << REG_OS_TM1CNT_H_E_SHIFT) | \
    ((u32)(i) << REG_OS_TM1CNT_H_I_SHIFT) | \
    ((u32)(ch) << REG_OS_TM1CNT_H_CH_SHIFT) | \
    ((u32)(ps) << REG_OS_TM1CNT_H_PS_SHIFT))
#endif


/* TM2CNT_L */

#define REG_OS_TM2CNT_L_CTR_SHIFT                          0
#define REG_OS_TM2CNT_L_CTR_SIZE                           16
#define REG_OS_TM2CNT_L_CTR_MASK                           0xffff

#ifndef SDK_ASM
#define REG_OS_TM2CNT_L_FIELD( ctr ) \
    (u16)( \
    ((u32)(ctr) << REG_OS_TM2CNT_L_CTR_SHIFT))
#endif


/* TM2CNT_H */

#define REG_OS_TM2CNT_H_E_SHIFT                            7
#define REG_OS_TM2CNT_H_E_SIZE                             1
#define REG_OS_TM2CNT_H_E_MASK                             0x0080

#define REG_OS_TM2CNT_H_I_SHIFT                            6
#define REG_OS_TM2CNT_H_I_SIZE                             1
#define REG_OS_TM2CNT_H_I_MASK                             0x0040

#define REG_OS_TM2CNT_H_CH_SHIFT                           2
#define REG_OS_TM2CNT_H_CH_SIZE                            1
#define REG_OS_TM2CNT_H_CH_MASK                            0x0004

#define REG_OS_TM2CNT_H_PS_SHIFT                           0
#define REG_OS_TM2CNT_H_PS_SIZE                            2
#define REG_OS_TM2CNT_H_PS_MASK                            0x0003

#ifndef SDK_ASM
#define REG_OS_TM2CNT_H_FIELD( e, i, ch, ps ) \
    (u16)( \
    ((u32)(e) << REG_OS_TM2CNT_H_E_SHIFT) | \
    ((u32)(i) << REG_OS_TM2CNT_H_I_SHIFT) | \
    ((u32)(ch) << REG_OS_TM2CNT_H_CH_SHIFT) | \
    ((u32)(ps) << REG_OS_TM2CNT_H_PS_SHIFT))
#endif


/* TM3CNT_L */

#define REG_OS_TM3CNT_L_CTR_SHIFT                          0
#define REG_OS_TM3CNT_L_CTR_SIZE                           16
#define REG_OS_TM3CNT_L_CTR_MASK                           0xffff

#ifndef SDK_ASM
#define REG_OS_TM3CNT_L_FIELD( ctr ) \
    (u16)( \
    ((u32)(ctr) << REG_OS_TM3CNT_L_CTR_SHIFT))
#endif


/* TM3CNT_H */

#define REG_OS_TM3CNT_H_E_SHIFT                            7
#define REG_OS_TM3CNT_H_E_SIZE                             1
#define REG_OS_TM3CNT_H_E_MASK                             0x0080

#define REG_OS_TM3CNT_H_I_SHIFT                            6
#define REG_OS_TM3CNT_H_I_SIZE                             1
#define REG_OS_TM3CNT_H_I_MASK                             0x0040

#define REG_OS_TM3CNT_H_CH_SHIFT                           2
#define REG_OS_TM3CNT_H_CH_SIZE                            1
#define REG_OS_TM3CNT_H_CH_MASK                            0x0004

#define REG_OS_TM3CNT_H_PS_SHIFT                           0
#define REG_OS_TM3CNT_H_PS_SIZE                            2
#define REG_OS_TM3CNT_H_PS_MASK                            0x0003

#ifndef SDK_ASM
#define REG_OS_TM3CNT_H_FIELD( e, i, ch, ps ) \
    (u16)( \
    ((u32)(e) << REG_OS_TM3CNT_H_E_SHIFT) | \
    ((u32)(i) << REG_OS_TM3CNT_H_I_SHIFT) | \
    ((u32)(ch) << REG_OS_TM3CNT_H_CH_SHIFT) | \
    ((u32)(ps) << REG_OS_TM3CNT_H_PS_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_OS_H_ */
#endif
