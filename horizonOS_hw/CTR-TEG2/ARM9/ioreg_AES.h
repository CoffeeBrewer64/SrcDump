/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/ARM9/ioreg_AES.h

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
#ifndef NN_HW_CTR_TEG2_ARM9_IOREG_AES_H_
#define NN_HW_CTR_TEG2_ARM9_IOREG_AES_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* AES_CNT */

#define REG_AES_CNT_OFFSET                                 0x9000
#define REG_AES_CNT_ADDR                                   (HW_REG_BASE + REG_AES_CNT_OFFSET)
#define reg_AES_AES_CNT                                    (*( REGType32v *) REG_AES_CNT_ADDR)

/* AES_LEN */

#define REG_AES_LEN_OFFSET                                 0x9004
#define REG_AES_LEN_ADDR                                   (HW_REG_BASE + REG_AES_LEN_OFFSET)
#define reg_AES_AES_LEN                                    (*( REGType32v *) REG_AES_LEN_ADDR)

/* AES_ALEN */

#define REG_AES_ALEN_OFFSET                                0x9004
#define REG_AES_ALEN_ADDR                                  (HW_REG_BASE + REG_AES_ALEN_OFFSET)
#define reg_AES_AES_ALEN                                   (*( REGType16v *) REG_AES_ALEN_ADDR)

/* AES_PLEN */

#define REG_AES_PLEN_OFFSET                                0x9006
#define REG_AES_PLEN_ADDR                                  (HW_REG_BASE + REG_AES_PLEN_OFFSET)
#define reg_AES_AES_PLEN                                   (*( REGType16v *) REG_AES_PLEN_ADDR)

/* AES_IFIFO */

#define REG_AES_IFIFO_OFFSET                               0x9008
#define REG_AES_IFIFO_ADDR                                 (HW_REG_BASE + REG_AES_IFIFO_OFFSET)
#define reg_AES_AES_IFIFO                                  (*( REGType32v *) REG_AES_IFIFO_ADDR)

/* AES_OFIFO */

#define REG_AES_OFIFO_OFFSET                               0x900c
#define REG_AES_OFIFO_ADDR                                 (HW_REG_BASE + REG_AES_OFIFO_OFFSET)
#define reg_AES_AES_OFIFO                                  (*(const REGType32v *) REG_AES_OFIFO_ADDR)

/* AES_KEYSEL */

#define REG_AES_KEYSEL_OFFSET                              0x9010
#define REG_AES_KEYSEL_ADDR                                (HW_REG_BASE + REG_AES_KEYSEL_OFFSET)
#define reg_AES_AES_KEYSEL                                 (*( REGType16v *) REG_AES_KEYSEL_ADDR)

/* AES_USEKEY */

#define REG_AES_USEKEY_OFFSET                              0x9010
#define REG_AES_USEKEY_ADDR                                (HW_REG_BASE + REG_AES_USEKEY_OFFSET)
#define reg_AES_AES_USEKEY                                 (*( REGType8v *) REG_AES_USEKEY_ADDR)

/* AES_STRKEY */

#define REG_AES_STRKEY_OFFSET                              0x9011
#define REG_AES_STRKEY_ADDR                                (HW_REG_BASE + REG_AES_STRKEY_OFFSET)
#define reg_AES_AES_STRKEY                                 (*( REGType8v *) REG_AES_STRKEY_ADDR)

/* AES_NONCE0 */

#define REG_AES_NONCE0_OFFSET                              0x9020
#define REG_AES_NONCE0_ADDR                                (HW_REG_BASE + REG_AES_NONCE0_OFFSET)
#define reg_AES_AES_NONCE0                                 (*( REGType32v *) REG_AES_NONCE0_ADDR)

/* AES_NONCE1 */

#define REG_AES_NONCE1_OFFSET                              0x9024
#define REG_AES_NONCE1_ADDR                                (HW_REG_BASE + REG_AES_NONCE1_OFFSET)
#define reg_AES_AES_NONCE1                                 (*( REGType32v *) REG_AES_NONCE1_ADDR)

/* AES_NONCE2 */

#define REG_AES_NONCE2_OFFSET                              0x9028
#define REG_AES_NONCE2_ADDR                                (HW_REG_BASE + REG_AES_NONCE2_OFFSET)
#define reg_AES_AES_NONCE2                                 (*( REGType32v *) REG_AES_NONCE2_ADDR)

/* AES_NONCE3 */

#define REG_AES_NONCE3_OFFSET                              0x902c
#define REG_AES_NONCE3_ADDR                                (HW_REG_BASE + REG_AES_NONCE3_OFFSET)
#define reg_AES_AES_NONCE3                                 (*( REGType32v *) REG_AES_NONCE3_ADDR)

/* AES_MAC0 */

#define REG_AES_MAC0_OFFSET                                0x9030
#define REG_AES_MAC0_ADDR                                  (HW_REG_BASE + REG_AES_MAC0_OFFSET)
#define reg_AES_AES_MAC0                                   (*( REGType32v *) REG_AES_MAC0_ADDR)

/* AES_MAC1 */

#define REG_AES_MAC1_OFFSET                                0x9034
#define REG_AES_MAC1_ADDR                                  (HW_REG_BASE + REG_AES_MAC1_OFFSET)
#define reg_AES_AES_MAC1                                   (*( REGType32v *) REG_AES_MAC1_ADDR)

/* AES_MAC2 */

#define REG_AES_MAC2_OFFSET                                0x9038
#define REG_AES_MAC2_ADDR                                  (HW_REG_BASE + REG_AES_MAC2_OFFSET)
#define reg_AES_AES_MAC2                                   (*( REGType32v *) REG_AES_MAC2_ADDR)

/* AES_MAC3 */

#define REG_AES_MAC3_OFFSET                                0x903c
#define REG_AES_MAC3_ADDR                                  (HW_REG_BASE + REG_AES_MAC3_OFFSET)
#define reg_AES_AES_MAC3                                   (*( REGType32v *) REG_AES_MAC3_ADDR)

/* AES_KEY_A0 */

#define REG_AES_KEY_A0_OFFSET                              0x9040
#define REG_AES_KEY_A0_ADDR                                (HW_REG_BASE + REG_AES_KEY_A0_OFFSET)
#define reg_AES_AES_KEY_A0                                 (*( REGType32v *) REG_AES_KEY_A0_ADDR)

/* AES_KEY_A1 */

#define REG_AES_KEY_A1_OFFSET                              0x9044
#define REG_AES_KEY_A1_ADDR                                (HW_REG_BASE + REG_AES_KEY_A1_OFFSET)
#define reg_AES_AES_KEY_A1                                 (*( REGType32v *) REG_AES_KEY_A1_ADDR)

/* AES_KEY_A2 */

#define REG_AES_KEY_A2_OFFSET                              0x9048
#define REG_AES_KEY_A2_ADDR                                (HW_REG_BASE + REG_AES_KEY_A2_OFFSET)
#define reg_AES_AES_KEY_A2                                 (*( REGType32v *) REG_AES_KEY_A2_ADDR)

/* AES_KEY_A3 */

#define REG_AES_KEY_A3_OFFSET                              0x904c
#define REG_AES_KEY_A3_ADDR                                (HW_REG_BASE + REG_AES_KEY_A3_OFFSET)
#define reg_AES_AES_KEY_A3                                 (*( REGType32v *) REG_AES_KEY_A3_ADDR)

/* AES_ID_A0 */

#define REG_AES_ID_A0_OFFSET                               0x9050
#define REG_AES_ID_A0_ADDR                                 (HW_REG_BASE + REG_AES_ID_A0_OFFSET)
#define reg_AES_AES_ID_A0                                  (*( REGType32v *) REG_AES_ID_A0_ADDR)

/* AES_ID_A1 */

#define REG_AES_ID_A1_OFFSET                               0x9054
#define REG_AES_ID_A1_ADDR                                 (HW_REG_BASE + REG_AES_ID_A1_OFFSET)
#define reg_AES_AES_ID_A1                                  (*( REGType32v *) REG_AES_ID_A1_ADDR)

/* AES_ID_A2 */

#define REG_AES_ID_A2_OFFSET                               0x9058
#define REG_AES_ID_A2_ADDR                                 (HW_REG_BASE + REG_AES_ID_A2_OFFSET)
#define reg_AES_AES_ID_A2                                  (*( REGType32v *) REG_AES_ID_A2_ADDR)

/* AES_ID_A3 */

#define REG_AES_ID_A3_OFFSET                               0x905c
#define REG_AES_ID_A3_ADDR                                 (HW_REG_BASE + REG_AES_ID_A3_OFFSET)
#define reg_AES_AES_ID_A3                                  (*( REGType32v *) REG_AES_ID_A3_ADDR)

/* AES_SEED_A0 */

#define REG_AES_SEED_A0_OFFSET                             0x9060
#define REG_AES_SEED_A0_ADDR                               (HW_REG_BASE + REG_AES_SEED_A0_OFFSET)
#define reg_AES_AES_SEED_A0                                (*( REGType32v *) REG_AES_SEED_A0_ADDR)

/* AES_SEED_A1 */

#define REG_AES_SEED_A1_OFFSET                             0x9064
#define REG_AES_SEED_A1_ADDR                               (HW_REG_BASE + REG_AES_SEED_A1_OFFSET)
#define reg_AES_AES_SEED_A1                                (*( REGType32v *) REG_AES_SEED_A1_ADDR)

/* AES_SEED_A2 */

#define REG_AES_SEED_A2_OFFSET                             0x9068
#define REG_AES_SEED_A2_ADDR                               (HW_REG_BASE + REG_AES_SEED_A2_OFFSET)
#define reg_AES_AES_SEED_A2                                (*( REGType32v *) REG_AES_SEED_A2_ADDR)

/* AES_SEED_A3 */

#define REG_AES_SEED_A3_OFFSET                             0x906c
#define REG_AES_SEED_A3_ADDR                               (HW_REG_BASE + REG_AES_SEED_A3_OFFSET)
#define reg_AES_AES_SEED_A3                                (*( REGType32v *) REG_AES_SEED_A3_ADDR)

/* AES_KEY_B0 */

#define REG_AES_KEY_B0_OFFSET                              0x9070
#define REG_AES_KEY_B0_ADDR                                (HW_REG_BASE + REG_AES_KEY_B0_OFFSET)
#define reg_AES_AES_KEY_B0                                 (*( REGType32v *) REG_AES_KEY_B0_ADDR)

/* AES_KEY_B1 */

#define REG_AES_KEY_B1_OFFSET                              0x9074
#define REG_AES_KEY_B1_ADDR                                (HW_REG_BASE + REG_AES_KEY_B1_OFFSET)
#define reg_AES_AES_KEY_B1                                 (*( REGType32v *) REG_AES_KEY_B1_ADDR)

/* AES_KEY_B2 */

#define REG_AES_KEY_B2_OFFSET                              0x9078
#define REG_AES_KEY_B2_ADDR                                (HW_REG_BASE + REG_AES_KEY_B2_OFFSET)
#define reg_AES_AES_KEY_B2                                 (*( REGType32v *) REG_AES_KEY_B2_ADDR)

/* AES_KEY_B3 */

#define REG_AES_KEY_B3_OFFSET                              0x907c
#define REG_AES_KEY_B3_ADDR                                (HW_REG_BASE + REG_AES_KEY_B3_OFFSET)
#define reg_AES_AES_KEY_B3                                 (*( REGType32v *) REG_AES_KEY_B3_ADDR)

/* AES_ID_B0 */

#define REG_AES_ID_B0_OFFSET                               0x9080
#define REG_AES_ID_B0_ADDR                                 (HW_REG_BASE + REG_AES_ID_B0_OFFSET)
#define reg_AES_AES_ID_B0                                  (*( REGType32v *) REG_AES_ID_B0_ADDR)

/* AES_ID_B1 */

#define REG_AES_ID_B1_OFFSET                               0x9084
#define REG_AES_ID_B1_ADDR                                 (HW_REG_BASE + REG_AES_ID_B1_OFFSET)
#define reg_AES_AES_ID_B1                                  (*( REGType32v *) REG_AES_ID_B1_ADDR)

/* AES_ID_B2 */

#define REG_AES_ID_B2_OFFSET                               0x9088
#define REG_AES_ID_B2_ADDR                                 (HW_REG_BASE + REG_AES_ID_B2_OFFSET)
#define reg_AES_AES_ID_B2                                  (*( REGType32v *) REG_AES_ID_B2_ADDR)

/* AES_ID_B3 */

#define REG_AES_ID_B3_OFFSET                               0x908c
#define REG_AES_ID_B3_ADDR                                 (HW_REG_BASE + REG_AES_ID_B3_OFFSET)
#define reg_AES_AES_ID_B3                                  (*( REGType32v *) REG_AES_ID_B3_ADDR)

/* AES_SEED_B0 */

#define REG_AES_SEED_B0_OFFSET                             0x9090
#define REG_AES_SEED_B0_ADDR                               (HW_REG_BASE + REG_AES_SEED_B0_OFFSET)
#define reg_AES_AES_SEED_B0                                (*( REGType32v *) REG_AES_SEED_B0_ADDR)

/* AES_SEED_B1 */

#define REG_AES_SEED_B1_OFFSET                             0x9094
#define REG_AES_SEED_B1_ADDR                               (HW_REG_BASE + REG_AES_SEED_B1_OFFSET)
#define reg_AES_AES_SEED_B1                                (*( REGType32v *) REG_AES_SEED_B1_ADDR)

/* AES_SEED_B2 */

#define REG_AES_SEED_B2_OFFSET                             0x9098
#define REG_AES_SEED_B2_ADDR                               (HW_REG_BASE + REG_AES_SEED_B2_OFFSET)
#define reg_AES_AES_SEED_B2                                (*( REGType32v *) REG_AES_SEED_B2_ADDR)

/* AES_SEED_B3 */

#define REG_AES_SEED_B3_OFFSET                             0x909c
#define REG_AES_SEED_B3_ADDR                               (HW_REG_BASE + REG_AES_SEED_B3_OFFSET)
#define reg_AES_AES_SEED_B3                                (*( REGType32v *) REG_AES_SEED_B3_ADDR)

/* AES_KEY_C0 */

#define REG_AES_KEY_C0_OFFSET                              0x90a0
#define REG_AES_KEY_C0_ADDR                                (HW_REG_BASE + REG_AES_KEY_C0_OFFSET)
#define reg_AES_AES_KEY_C0                                 (*( REGType32v *) REG_AES_KEY_C0_ADDR)

/* AES_KEY_C1 */

#define REG_AES_KEY_C1_OFFSET                              0x90a4
#define REG_AES_KEY_C1_ADDR                                (HW_REG_BASE + REG_AES_KEY_C1_OFFSET)
#define reg_AES_AES_KEY_C1                                 (*( REGType32v *) REG_AES_KEY_C1_ADDR)

/* AES_KEY_C2 */

#define REG_AES_KEY_C2_OFFSET                              0x90a8
#define REG_AES_KEY_C2_ADDR                                (HW_REG_BASE + REG_AES_KEY_C2_OFFSET)
#define reg_AES_AES_KEY_C2                                 (*( REGType32v *) REG_AES_KEY_C2_ADDR)

/* AES_KEY_C3 */

#define REG_AES_KEY_C3_OFFSET                              0x90ac
#define REG_AES_KEY_C3_ADDR                                (HW_REG_BASE + REG_AES_KEY_C3_OFFSET)
#define reg_AES_AES_KEY_C3                                 (*( REGType32v *) REG_AES_KEY_C3_ADDR)

/* AES_ID_C0 */

#define REG_AES_ID_C0_OFFSET                               0x90b0
#define REG_AES_ID_C0_ADDR                                 (HW_REG_BASE + REG_AES_ID_C0_OFFSET)
#define reg_AES_AES_ID_C0                                  (*( REGType32v *) REG_AES_ID_C0_ADDR)

/* AES_ID_C1 */

#define REG_AES_ID_C1_OFFSET                               0x90b4
#define REG_AES_ID_C1_ADDR                                 (HW_REG_BASE + REG_AES_ID_C1_OFFSET)
#define reg_AES_AES_ID_C1                                  (*( REGType32v *) REG_AES_ID_C1_ADDR)

/* AES_ID_C2 */

#define REG_AES_ID_C2_OFFSET                               0x90b8
#define REG_AES_ID_C2_ADDR                                 (HW_REG_BASE + REG_AES_ID_C2_OFFSET)
#define reg_AES_AES_ID_C2                                  (*( REGType32v *) REG_AES_ID_C2_ADDR)

/* AES_ID_C3 */

#define REG_AES_ID_C3_OFFSET                               0x90bc
#define REG_AES_ID_C3_ADDR                                 (HW_REG_BASE + REG_AES_ID_C3_OFFSET)
#define reg_AES_AES_ID_C3                                  (*( REGType32v *) REG_AES_ID_C3_ADDR)

/* AES_SEED_C0 */

#define REG_AES_SEED_C0_OFFSET                             0x90c0
#define REG_AES_SEED_C0_ADDR                               (HW_REG_BASE + REG_AES_SEED_C0_OFFSET)
#define reg_AES_AES_SEED_C0                                (*( REGType32v *) REG_AES_SEED_C0_ADDR)

/* AES_SEED_C1 */

#define REG_AES_SEED_C1_OFFSET                             0x90c4
#define REG_AES_SEED_C1_ADDR                               (HW_REG_BASE + REG_AES_SEED_C1_OFFSET)
#define reg_AES_AES_SEED_C1                                (*( REGType32v *) REG_AES_SEED_C1_ADDR)

/* AES_SEED_C2 */

#define REG_AES_SEED_C2_OFFSET                             0x90c8
#define REG_AES_SEED_C2_ADDR                               (HW_REG_BASE + REG_AES_SEED_C2_OFFSET)
#define reg_AES_AES_SEED_C2                                (*( REGType32v *) REG_AES_SEED_C2_ADDR)

/* AES_SEED_C3 */

#define REG_AES_SEED_C3_OFFSET                             0x90cc
#define REG_AES_SEED_C3_ADDR                               (HW_REG_BASE + REG_AES_SEED_C3_OFFSET)
#define reg_AES_AES_SEED_C3                                (*( REGType32v *) REG_AES_SEED_C3_ADDR)

/* AES_KEY_D0 */

#define REG_AES_KEY_D0_OFFSET                              0x90d0
#define REG_AES_KEY_D0_ADDR                                (HW_REG_BASE + REG_AES_KEY_D0_OFFSET)
#define reg_AES_AES_KEY_D0                                 (*( REGType32v *) REG_AES_KEY_D0_ADDR)

/* AES_KEY_D1 */

#define REG_AES_KEY_D1_OFFSET                              0x90d4
#define REG_AES_KEY_D1_ADDR                                (HW_REG_BASE + REG_AES_KEY_D1_OFFSET)
#define reg_AES_AES_KEY_D1                                 (*( REGType32v *) REG_AES_KEY_D1_ADDR)

/* AES_KEY_D2 */

#define REG_AES_KEY_D2_OFFSET                              0x90d8
#define REG_AES_KEY_D2_ADDR                                (HW_REG_BASE + REG_AES_KEY_D2_OFFSET)
#define reg_AES_AES_KEY_D2                                 (*( REGType32v *) REG_AES_KEY_D2_ADDR)

/* AES_KEY_D3 */

#define REG_AES_KEY_D3_OFFSET                              0x90dc
#define REG_AES_KEY_D3_ADDR                                (HW_REG_BASE + REG_AES_KEY_D3_OFFSET)
#define reg_AES_AES_KEY_D3                                 (*( REGType32v *) REG_AES_KEY_D3_ADDR)

/* AES_ID_D0 */

#define REG_AES_ID_D0_OFFSET                               0x90e0
#define REG_AES_ID_D0_ADDR                                 (HW_REG_BASE + REG_AES_ID_D0_OFFSET)
#define reg_AES_AES_ID_D0                                  (*( REGType32v *) REG_AES_ID_D0_ADDR)

/* AES_ID_D1 */

#define REG_AES_ID_D1_OFFSET                               0x90e4
#define REG_AES_ID_D1_ADDR                                 (HW_REG_BASE + REG_AES_ID_D1_OFFSET)
#define reg_AES_AES_ID_D1                                  (*( REGType32v *) REG_AES_ID_D1_ADDR)

/* AES_ID_D2 */

#define REG_AES_ID_D2_OFFSET                               0x90e8
#define REG_AES_ID_D2_ADDR                                 (HW_REG_BASE + REG_AES_ID_D2_OFFSET)
#define reg_AES_AES_ID_D2                                  (*( REGType32v *) REG_AES_ID_D2_ADDR)

/* AES_ID_D3 */

#define REG_AES_ID_D3_OFFSET                               0x90ec
#define REG_AES_ID_D3_ADDR                                 (HW_REG_BASE + REG_AES_ID_D3_OFFSET)
#define reg_AES_AES_ID_D3                                  (*( REGType32v *) REG_AES_ID_D3_ADDR)

/* AES_SEED_D0 */

#define REG_AES_SEED_D0_OFFSET                             0x90f0
#define REG_AES_SEED_D0_ADDR                               (HW_REG_BASE + REG_AES_SEED_D0_OFFSET)
#define reg_AES_AES_SEED_D0                                (*( REGType32v *) REG_AES_SEED_D0_ADDR)

/* AES_SEED_D1 */

#define REG_AES_SEED_D1_OFFSET                             0x90f4
#define REG_AES_SEED_D1_ADDR                               (HW_REG_BASE + REG_AES_SEED_D1_OFFSET)
#define reg_AES_AES_SEED_D1                                (*( REGType32v *) REG_AES_SEED_D1_ADDR)

/* AES_SEED_D2 */

#define REG_AES_SEED_D2_OFFSET                             0x90f8
#define REG_AES_SEED_D2_ADDR                               (HW_REG_BASE + REG_AES_SEED_D2_OFFSET)
#define reg_AES_AES_SEED_D2                                (*( REGType32v *) REG_AES_SEED_D2_ADDR)

/* AES_SEED_D3 */

#define REG_AES_SEED_D3_OFFSET                             0x90fc
#define REG_AES_SEED_D3_ADDR                               (HW_REG_BASE + REG_AES_SEED_D3_OFFSET)
#define reg_AES_AES_SEED_D3                                (*( REGType32v *) REG_AES_SEED_D3_ADDR)

/* AES_KEY_E */

#define REG_AES_KEY_E_OFFSET                               0x9100
#define REG_AES_KEY_E_ADDR                                 (HW_REG_BASE + REG_AES_KEY_E_OFFSET)
#define reg_AES_AES_KEY_E                                  (*( REGType32v *) REG_AES_KEY_E_ADDR)

/* AES_ID_E */

#define REG_AES_ID_E_OFFSET                                0x9104
#define REG_AES_ID_E_ADDR                                  (HW_REG_BASE + REG_AES_ID_E_OFFSET)
#define reg_AES_AES_ID_E                                   (*( REGType32v *) REG_AES_ID_E_ADDR)

/* AES_SEED_E */

#define REG_AES_SEED_E_OFFSET                              0x9108
#define REG_AES_SEED_E_ADDR                                (HW_REG_BASE + REG_AES_SEED_E_OFFSET)
#define reg_AES_AES_SEED_E                                 (*( REGType32v *) REG_AES_SEED_E_ADDR)


/*
 * Definitions of Register fields
 */


/* AES_CNT */

#define REG_AES_AES_CNT_E_SHIFT                            31
#define REG_AES_AES_CNT_E_SIZE                             1
#define REG_AES_AES_CNT_E_MASK                             0x80000000

#define REG_AES_AES_CNT_I_SHIFT                            30
#define REG_AES_AES_CNT_I_SIZE                             1
#define REG_AES_AES_CNT_I_MASK                             0x40000000

#define REG_AES_AES_CNT_MODE_SHIFT                         27
#define REG_AES_AES_CNT_MODE_SIZE                          3
#define REG_AES_AES_CNT_MODE_MASK                          0x38000000

#define REG_AES_AES_CNT_KEYSET_SHIFT                       26
#define REG_AES_AES_CNT_KEYSET_SIZE                        1
#define REG_AES_AES_CNT_KEYSET_MASK                        0x04000000

#define REG_AES_AES_CNT_WSFT_SHIFT                         25
#define REG_AES_AES_CNT_WSFT_SIZE                          1
#define REG_AES_AES_CNT_WSFT_MASK                          0x02000000

#define REG_AES_AES_CNT_RSFT_SHIFT                         24
#define REG_AES_AES_CNT_RSFT_SIZE                          1
#define REG_AES_AES_CNT_RSFT_MASK                          0x01000000

#define REG_AES_AES_CNT_WEND_SHIFT                         23
#define REG_AES_AES_CNT_WEND_SIZE                          1
#define REG_AES_AES_CNT_WEND_MASK                          0x00800000

#define REG_AES_AES_CNT_REND_SHIFT                         22
#define REG_AES_AES_CNT_REND_SIZE                          1
#define REG_AES_AES_CNT_REND_MASK                          0x00400000

#define REG_AES_AES_CNT_CCM_DEC_SHIFT                      20
#define REG_AES_AES_CNT_CCM_DEC_SIZE                       2
#define REG_AES_AES_CNT_CCM_DEC_MASK                       0x00300000

#define REG_AES_AES_CNT_VALID_SHIFT                        21
#define REG_AES_AES_CNT_VALID_SIZE                         1
#define REG_AES_AES_CNT_VALID_MASK                         0x00200000

#define REG_AES_AES_CNT_MSEL_SHIFT                         20
#define REG_AES_AES_CNT_MSEL_SIZE                          1
#define REG_AES_AES_CNT_MSEL_MASK                          0x00100000

#define REG_AES_AES_CNT_ADE_SHIFT                          19
#define REG_AES_AES_CNT_ADE_SIZE                           1
#define REG_AES_AES_CNT_ADE_MASK                           0x00080000

#define REG_AES_AES_CNT_MAC_LEN_SHIFT                      16
#define REG_AES_AES_CNT_MAC_LEN_SIZE                       3
#define REG_AES_AES_CNT_MAC_LEN_MASK                       0x00070000

#define REG_AES_AES_CNT_OFIFO_DREQ_SHIFT                   14
#define REG_AES_AES_CNT_OFIFO_DREQ_SIZE                    2
#define REG_AES_AES_CNT_OFIFO_DREQ_MASK                    0x0000c000

#define REG_AES_AES_CNT_IFIFO_DREQ_SHIFT                   12
#define REG_AES_AES_CNT_IFIFO_DREQ_SIZE                    2
#define REG_AES_AES_CNT_IFIFO_DREQ_MASK                    0x00003000

#define REG_AES_AES_CNT_FIFO_CLR_SHIFT                     10
#define REG_AES_AES_CNT_FIFO_CLR_SIZE                      2
#define REG_AES_AES_CNT_FIFO_CLR_MASK                      0x00000c00

#define REG_AES_AES_CNT_OFIFO_CLR_SHIFT                    11
#define REG_AES_AES_CNT_OFIFO_CLR_SIZE                     1
#define REG_AES_AES_CNT_OFIFO_CLR_MASK                     0x00000800

#define REG_AES_AES_CNT_IFIFO_CLR_SHIFT                    10
#define REG_AES_AES_CNT_IFIFO_CLR_SIZE                     1
#define REG_AES_AES_CNT_IFIFO_CLR_MASK                     0x00000400

#define REG_AES_AES_CNT_OFIFO_CNT_SHIFT                    5
#define REG_AES_AES_CNT_OFIFO_CNT_SIZE                     5
#define REG_AES_AES_CNT_OFIFO_CNT_MASK                     0x000003e0

#define REG_AES_AES_CNT_IFIFO_CNT_SHIFT                    0
#define REG_AES_AES_CNT_IFIFO_CNT_SIZE                     5
#define REG_AES_AES_CNT_IFIFO_CNT_MASK                     0x0000001f

#ifndef SDK_ASM
#define REG_AES_AES_CNT_FIELD( e, i, mode, keyset, wsft, rsft, wend, rend, ccm_dec, valid, msel, ade, mac_len, ofifo_dreq, ififo_dreq, fifo_clr, ofifo_clr, ififo_clr, ofifo_cnt, ififo_cnt ) \
    (u32)( \
    ((u32)(e) << REG_AES_AES_CNT_E_SHIFT) | \
    ((u32)(i) << REG_AES_AES_CNT_I_SHIFT) | \
    ((u32)(mode) << REG_AES_AES_CNT_MODE_SHIFT) | \
    ((u32)(keyset) << REG_AES_AES_CNT_KEYSET_SHIFT) | \
    ((u32)(wsft) << REG_AES_AES_CNT_WSFT_SHIFT) | \
    ((u32)(rsft) << REG_AES_AES_CNT_RSFT_SHIFT) | \
    ((u32)(wend) << REG_AES_AES_CNT_WEND_SHIFT) | \
    ((u32)(rend) << REG_AES_AES_CNT_REND_SHIFT) | \
    ((u32)(ccm_dec) << REG_AES_AES_CNT_CCM_DEC_SHIFT) | \
    ((u32)(valid) << REG_AES_AES_CNT_VALID_SHIFT) | \
    ((u32)(msel) << REG_AES_AES_CNT_MSEL_SHIFT) | \
    ((u32)(ade) << REG_AES_AES_CNT_ADE_SHIFT) | \
    ((u32)(mac_len) << REG_AES_AES_CNT_MAC_LEN_SHIFT) | \
    ((u32)(ofifo_dreq) << REG_AES_AES_CNT_OFIFO_DREQ_SHIFT) | \
    ((u32)(ififo_dreq) << REG_AES_AES_CNT_IFIFO_DREQ_SHIFT) | \
    ((u32)(fifo_clr) << REG_AES_AES_CNT_FIFO_CLR_SHIFT) | \
    ((u32)(ofifo_clr) << REG_AES_AES_CNT_OFIFO_CLR_SHIFT) | \
    ((u32)(ififo_clr) << REG_AES_AES_CNT_IFIFO_CLR_SHIFT) | \
    ((u32)(ofifo_cnt) << REG_AES_AES_CNT_OFIFO_CNT_SHIFT) | \
    ((u32)(ififo_cnt) << REG_AES_AES_CNT_IFIFO_CNT_SHIFT))
#endif


/* AES_LEN */

#define REG_AES_AES_LEN_PL_SHIFT                           16
#define REG_AES_AES_LEN_PL_SIZE                            16
#define REG_AES_AES_LEN_PL_MASK                            0xffff0000

#define REG_AES_AES_LEN_AL_SHIFT                           0
#define REG_AES_AES_LEN_AL_SIZE                            16
#define REG_AES_AES_LEN_AL_MASK                            0x0000ffff

#ifndef SDK_ASM
#define REG_AES_AES_LEN_FIELD( pl, al ) \
    (u32)( \
    ((u32)(pl) << REG_AES_AES_LEN_PL_SHIFT) | \
    ((u32)(al) << REG_AES_AES_LEN_AL_SHIFT))
#endif


/* AES_ALEN */

/* AES_PLEN */

/* AES_IFIFO */

/* AES_OFIFO */

/* AES_KEYSEL */

#define REG_AES_AES_KEYSEL_CCLR_SHIFT                      15
#define REG_AES_AES_KEYSEL_CCLR_SIZE                       1
#define REG_AES_AES_KEYSEL_CCLR_MASK                       0x8000

#define REG_AES_AES_KEYSEL_CALR_SHIFT                      14
#define REG_AES_AES_KEYSEL_CALR_SIZE                       1
#define REG_AES_AES_KEYSEL_CALR_MASK                       0x4000

#define REG_AES_AES_KEYSEL_STRSEL_SHIFT                    8
#define REG_AES_AES_KEYSEL_STRSEL_SIZE                     6
#define REG_AES_AES_KEYSEL_STRSEL_MASK                     0x3f00

#define REG_AES_AES_KEYSEL_USESEL_SHIFT                    0
#define REG_AES_AES_KEYSEL_USESEL_SIZE                     6
#define REG_AES_AES_KEYSEL_USESEL_MASK                     0x003f

#ifndef SDK_ASM
#define REG_AES_AES_KEYSEL_FIELD( cclr, calr, strsel, usesel ) \
    (u16)( \
    ((u32)(cclr) << REG_AES_AES_KEYSEL_CCLR_SHIFT) | \
    ((u32)(calr) << REG_AES_AES_KEYSEL_CALR_SHIFT) | \
    ((u32)(strsel) << REG_AES_AES_KEYSEL_STRSEL_SHIFT) | \
    ((u32)(usesel) << REG_AES_AES_KEYSEL_USESEL_SHIFT))
#endif


/* AES_USEKEY */

#define REG_AES_AES_USEKEY_SEL_SHIFT                       0
#define REG_AES_AES_USEKEY_SEL_SIZE                        6
#define REG_AES_AES_USEKEY_SEL_MASK                        0x3f

#ifndef SDK_ASM
#define REG_AES_AES_USEKEY_FIELD( sel ) \
    (u8)( \
    ((u32)(sel) << REG_AES_AES_USEKEY_SEL_SHIFT))
#endif


/* AES_STRKEY */

#define REG_AES_AES_STRKEY_CCLR_SHIFT                      7
#define REG_AES_AES_STRKEY_CCLR_SIZE                       1
#define REG_AES_AES_STRKEY_CCLR_MASK                       0x80

#define REG_AES_AES_STRKEY_CALR_SHIFT                      6
#define REG_AES_AES_STRKEY_CALR_SIZE                       1
#define REG_AES_AES_STRKEY_CALR_MASK                       0x40

#define REG_AES_AES_STRKEY_SEL_SHIFT                       0
#define REG_AES_AES_STRKEY_SEL_SIZE                        6
#define REG_AES_AES_STRKEY_SEL_MASK                        0x3f

#ifndef SDK_ASM
#define REG_AES_AES_STRKEY_FIELD( cclr, calr, sel ) \
    (u8)( \
    ((u32)(cclr) << REG_AES_AES_STRKEY_CCLR_SHIFT) | \
    ((u32)(calr) << REG_AES_AES_STRKEY_CALR_SHIFT) | \
    ((u32)(sel) << REG_AES_AES_STRKEY_SEL_SHIFT))
#endif


/* AES_NONCE0 */

/* AES_NONCE1 */

/* AES_NONCE2 */

/* AES_NONCE3 */

/* AES_MAC0 */

/* AES_MAC1 */

/* AES_MAC2 */

/* AES_MAC3 */

/* AES_KEY_A0 */

/* AES_KEY_A1 */

/* AES_KEY_A2 */

/* AES_KEY_A3 */

/* AES_ID_A0 */

/* AES_ID_A1 */

/* AES_ID_A2 */

/* AES_ID_A3 */

/* AES_SEED_A0 */

/* AES_SEED_A1 */

/* AES_SEED_A2 */

/* AES_SEED_A3 */

/* AES_KEY_B0 */

/* AES_KEY_B1 */

/* AES_KEY_B2 */

/* AES_KEY_B3 */

/* AES_ID_B0 */

/* AES_ID_B1 */

/* AES_ID_B2 */

/* AES_ID_B3 */

/* AES_SEED_B0 */

/* AES_SEED_B1 */

/* AES_SEED_B2 */

/* AES_SEED_B3 */

/* AES_KEY_C0 */

/* AES_KEY_C1 */

/* AES_KEY_C2 */

/* AES_KEY_C3 */

/* AES_ID_C0 */

/* AES_ID_C1 */

/* AES_ID_C2 */

/* AES_ID_C3 */

/* AES_SEED_C0 */

/* AES_SEED_C1 */

/* AES_SEED_C2 */

/* AES_SEED_C3 */

/* AES_KEY_D0 */

/* AES_KEY_D1 */

/* AES_KEY_D2 */

/* AES_KEY_D3 */

/* AES_ID_D0 */

/* AES_ID_D1 */

/* AES_ID_D2 */

/* AES_ID_D3 */

/* AES_SEED_D0 */

/* AES_SEED_D1 */

/* AES_SEED_D2 */

/* AES_SEED_D3 */

/* AES_KEY_E */

/* AES_ID_E */

/* AES_SEED_E */

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_ARM9_IOREG_AES_H_ */
#endif
