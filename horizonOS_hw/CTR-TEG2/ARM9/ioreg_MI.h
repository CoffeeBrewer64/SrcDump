/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/ARM9/ioreg_MI.h

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
#ifndef NN_HW_CTR_TEG2_ARM9_IOREG_MI_H_
#define NN_HW_CTR_TEG2_ARM9_IOREG_MI_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* CGC1_CNT1 */

#define REG_CGC1_CNT1_OFFSET                               0x4000
#define REG_CGC1_CNT1_ADDR                                 (HW_REG_BASE + REG_CGC1_CNT1_OFFSET)
#define reg_MI_CGC1_CNT1                                   (*( REGType32v *) REG_CGC1_CNT1_ADDR)

/* CGC1_CNT2 */

#define REG_CGC1_CNT2_OFFSET                               0x4004
#define REG_CGC1_CNT2_ADDR                                 (HW_REG_BASE + REG_CGC1_CNT2_OFFSET)
#define reg_MI_CGC1_CNT2                                   (*( REGType32v *) REG_CGC1_CNT2_ADDR)

/* CGC1_SC */

#define REG_CGC1_SC_OFFSET                                 0x4008
#define REG_CGC1_SC_ADDR                                   (HW_REG_BASE + REG_CGC1_SC_OFFSET)
#define reg_MI_CGC1_SC                                     (*( REGType32v *) REG_CGC1_SC_ADDR)

/* CGC1_PROT */

#define REG_CGC1_PROT_OFFSET                               0x400c
#define REG_CGC1_PROT_ADDR                                 (HW_REG_BASE + REG_CGC1_PROT_OFFSET)
#define reg_MI_CGC1_PROT                                   (*( REGType32v *) REG_CGC1_PROT_ADDR)

/* CGC1_KEY1 */

#define REG_CGC1_KEY1_OFFSET                               0x4010
#define REG_CGC1_KEY1_ADDR                                 (HW_REG_BASE + REG_CGC1_KEY1_OFFSET)
#define reg_MI_CGC1_KEY1                                   (*( REGType32v *) REG_CGC1_KEY1_ADDR)

/* CGC1_KEY2 */

#define REG_CGC1_KEY2_OFFSET                               0x4014
#define REG_CGC1_KEY2_ADDR                                 (HW_REG_BASE + REG_CGC1_KEY2_OFFSET)
#define reg_MI_CGC1_KEY2                                   (*( REGType32v *) REG_CGC1_KEY2_ADDR)

/* CGC1_CMD0 */

#define REG_CGC1_CMD0_OFFSET                               0x4020
#define REG_CGC1_CMD0_ADDR                                 (HW_REG_BASE + REG_CGC1_CMD0_OFFSET)
#define reg_MI_CGC1_CMD0                                   (*( REGType32v *) REG_CGC1_CMD0_ADDR)

/* CGC1_CMD1 */

#define REG_CGC1_CMD1_OFFSET                               0x4024
#define REG_CGC1_CMD1_ADDR                                 (HW_REG_BASE + REG_CGC1_CMD1_OFFSET)
#define reg_MI_CGC1_CMD1                                   (*( REGType32v *) REG_CGC1_CMD1_ADDR)

/* CGC1_CMD2 */

#define REG_CGC1_CMD2_OFFSET                               0x4028
#define REG_CGC1_CMD2_ADDR                                 (HW_REG_BASE + REG_CGC1_CMD2_OFFSET)
#define reg_MI_CGC1_CMD2                                   (*( REGType32v *) REG_CGC1_CMD2_ADDR)

/* CGC1_CMD3 */

#define REG_CGC1_CMD3_OFFSET                               0x402c
#define REG_CGC1_CMD3_ADDR                                 (HW_REG_BASE + REG_CGC1_CMD3_OFFSET)
#define reg_MI_CGC1_CMD3                                   (*( REGType32v *) REG_CGC1_CMD3_ADDR)

/* CGC1_DATA */

#define REG_CGC1_DATA_OFFSET                               0x4030
#define REG_CGC1_DATA_ADDR                                 (HW_REG_BASE + REG_CGC1_DATA_OFFSET)
#define reg_MI_CGC1_DATA                                   (*( REGType32v *) REG_CGC1_DATA_ADDR)

/* CGC2_CNT1 */

#define REG_CGC2_CNT1_OFFSET                               0x5000
#define REG_CGC2_CNT1_ADDR                                 (HW_REG_BASE + REG_CGC2_CNT1_OFFSET)
#define reg_MI_CGC2_CNT1                                   (*( REGType32v *) REG_CGC2_CNT1_ADDR)

/* CGC2_CNT2 */

#define REG_CGC2_CNT2_OFFSET                               0x5004
#define REG_CGC2_CNT2_ADDR                                 (HW_REG_BASE + REG_CGC2_CNT2_OFFSET)
#define reg_MI_CGC2_CNT2                                   (*( REGType32v *) REG_CGC2_CNT2_ADDR)

/* CGC2_AUTH */

#define REG_CGC2_AUTH_OFFSET                               0x5008
#define REG_CGC2_AUTH_ADDR                                 (HW_REG_BASE + REG_CGC2_AUTH_OFFSET)
#define reg_MI_CGC2_AUTH                                   (*( REGType32v *) REG_CGC2_AUTH_ADDR)

/* CGC2_PROT */

#define REG_CGC2_PROT_OFFSET                               0x500c
#define REG_CGC2_PROT_ADDR                                 (HW_REG_BASE + REG_CGC2_PROT_OFFSET)
#define reg_MI_CGC2_PROT                                   (*( REGType32v *) REG_CGC2_PROT_ADDR)

/* CGC2_CMD0 */

#define REG_CGC2_CMD0_OFFSET                               0x5020
#define REG_CGC2_CMD0_ADDR                                 (HW_REG_BASE + REG_CGC2_CMD0_OFFSET)
#define reg_MI_CGC2_CMD0                                   (*( REGType32v *) REG_CGC2_CMD0_ADDR)

/* CGC2_CMD1 */

#define REG_CGC2_CMD1_OFFSET                               0x5024
#define REG_CGC2_CMD1_ADDR                                 (HW_REG_BASE + REG_CGC2_CMD1_OFFSET)
#define reg_MI_CGC2_CMD1                                   (*( REGType32v *) REG_CGC2_CMD1_ADDR)

/* CGC2_CMD2 */

#define REG_CGC2_CMD2_OFFSET                               0x5028
#define REG_CGC2_CMD2_ADDR                                 (HW_REG_BASE + REG_CGC2_CMD2_OFFSET)
#define reg_MI_CGC2_CMD2                                   (*( REGType32v *) REG_CGC2_CMD2_ADDR)

/* CGC2_CMD3 */

#define REG_CGC2_CMD3_OFFSET                               0x502c
#define REG_CGC2_CMD3_ADDR                                 (HW_REG_BASE + REG_CGC2_CMD3_OFFSET)
#define reg_MI_CGC2_CMD3                                   (*( REGType32v *) REG_CGC2_CMD3_ADDR)

/* CGC2_DATA */

#define REG_CGC2_DATA_OFFSET                               0x5030
#define REG_CGC2_DATA_ADDR                                 (HW_REG_BASE + REG_CGC2_DATA_OFFSET)
#define reg_MI_CGC2_DATA                                   (*( REGType32v *) REG_CGC2_DATA_ADDR)

/* NDMAGCNT */

#define REG_NDMAGCNT_OFFSET                                0x2000
#define REG_NDMAGCNT_ADDR                                  (HW_REG_BASE + REG_NDMAGCNT_OFFSET)
#define reg_MI_NDMAGCNT                                    (*( REGType32v *) REG_NDMAGCNT_ADDR)

/* NDMA0SAD */

#define REG_NDMA0SAD_OFFSET                                0x2004
#define REG_NDMA0SAD_ADDR                                  (HW_REG_BASE + REG_NDMA0SAD_OFFSET)
#define reg_MI_NDMA0SAD                                    (*( REGType32v *) REG_NDMA0SAD_ADDR)

/* NDMA0DAD */

#define REG_NDMA0DAD_OFFSET                                0x2008
#define REG_NDMA0DAD_ADDR                                  (HW_REG_BASE + REG_NDMA0DAD_OFFSET)
#define reg_MI_NDMA0DAD                                    (*( REGType32v *) REG_NDMA0DAD_ADDR)

/* NDMA0TCNT */

#define REG_NDMA0TCNT_OFFSET                               0x200c
#define REG_NDMA0TCNT_ADDR                                 (HW_REG_BASE + REG_NDMA0TCNT_OFFSET)
#define reg_MI_NDMA0TCNT                                   (*( REGType32v *) REG_NDMA0TCNT_ADDR)

/* NDMA0WCNT */

#define REG_NDMA0WCNT_OFFSET                               0x2010
#define REG_NDMA0WCNT_ADDR                                 (HW_REG_BASE + REG_NDMA0WCNT_OFFSET)
#define reg_MI_NDMA0WCNT                                   (*( REGType32v *) REG_NDMA0WCNT_ADDR)

/* NDMA0BCNT */

#define REG_NDMA0BCNT_OFFSET                               0x2014
#define REG_NDMA0BCNT_ADDR                                 (HW_REG_BASE + REG_NDMA0BCNT_OFFSET)
#define reg_MI_NDMA0BCNT                                   (*( REGType32v *) REG_NDMA0BCNT_ADDR)

/* NDMA0FDATA */

#define REG_NDMA0FDATA_OFFSET                              0x2018
#define REG_NDMA0FDATA_ADDR                                (HW_REG_BASE + REG_NDMA0FDATA_OFFSET)
#define reg_MI_NDMA0FDATA                                  (*( REGType32v *) REG_NDMA0FDATA_ADDR)

/* NDMA0CNT */

#define REG_NDMA0CNT_OFFSET                                0x201c
#define REG_NDMA0CNT_ADDR                                  (HW_REG_BASE + REG_NDMA0CNT_OFFSET)
#define reg_MI_NDMA0CNT                                    (*( REGType32v *) REG_NDMA0CNT_ADDR)

/* NDMA1SAD */

#define REG_NDMA1SAD_OFFSET                                0x2020
#define REG_NDMA1SAD_ADDR                                  (HW_REG_BASE + REG_NDMA1SAD_OFFSET)
#define reg_MI_NDMA1SAD                                    (*( REGType32v *) REG_NDMA1SAD_ADDR)

/* NDMA1DAD */

#define REG_NDMA1DAD_OFFSET                                0x2024
#define REG_NDMA1DAD_ADDR                                  (HW_REG_BASE + REG_NDMA1DAD_OFFSET)
#define reg_MI_NDMA1DAD                                    (*( REGType32v *) REG_NDMA1DAD_ADDR)

/* NDMA1TCNT */

#define REG_NDMA1TCNT_OFFSET                               0x2028
#define REG_NDMA1TCNT_ADDR                                 (HW_REG_BASE + REG_NDMA1TCNT_OFFSET)
#define reg_MI_NDMA1TCNT                                   (*( REGType32v *) REG_NDMA1TCNT_ADDR)

/* NDMA1WCNT */

#define REG_NDMA1WCNT_OFFSET                               0x202c
#define REG_NDMA1WCNT_ADDR                                 (HW_REG_BASE + REG_NDMA1WCNT_OFFSET)
#define reg_MI_NDMA1WCNT                                   (*( REGType32v *) REG_NDMA1WCNT_ADDR)

/* NDMA1BCNT */

#define REG_NDMA1BCNT_OFFSET                               0x2030
#define REG_NDMA1BCNT_ADDR                                 (HW_REG_BASE + REG_NDMA1BCNT_OFFSET)
#define reg_MI_NDMA1BCNT                                   (*( REGType32v *) REG_NDMA1BCNT_ADDR)

/* NDMA1FDATA */

#define REG_NDMA1FDATA_OFFSET                              0x2034
#define REG_NDMA1FDATA_ADDR                                (HW_REG_BASE + REG_NDMA1FDATA_OFFSET)
#define reg_MI_NDMA1FDATA                                  (*( REGType32v *) REG_NDMA1FDATA_ADDR)

/* NDMA1CNT */

#define REG_NDMA1CNT_OFFSET                                0x2038
#define REG_NDMA1CNT_ADDR                                  (HW_REG_BASE + REG_NDMA1CNT_OFFSET)
#define reg_MI_NDMA1CNT                                    (*( REGType32v *) REG_NDMA1CNT_ADDR)

/* XDMA_DS */

#define REG_XDMA_DS_OFFSET                                 0xc000
#define REG_XDMA_DS_ADDR                                   (HW_REG_BASE + REG_XDMA_DS_OFFSET)
#define reg_MI_XDMA_DS                                     (*(const REGType32v *) REG_XDMA_DS_ADDR)

/* XDMA_DPC */

#define REG_XDMA_DPC_OFFSET                                0xc004
#define REG_XDMA_DPC_ADDR                                  (HW_REG_BASE + REG_XDMA_DPC_OFFSET)
#define reg_MI_XDMA_DPC                                    (*(const REGType32v *) REG_XDMA_DPC_ADDR)

/* XDMA_IE */

#define REG_XDMA_IE_OFFSET                                 0xc020
#define REG_XDMA_IE_ADDR                                   (HW_REG_BASE + REG_XDMA_IE_OFFSET)
#define reg_MI_XDMA_IE                                     (*( REGType32v *) REG_XDMA_IE_ADDR)

/* XDMA_ES */

#define REG_XDMA_ES_OFFSET                                 0xc024
#define REG_XDMA_ES_ADDR                                   (HW_REG_BASE + REG_XDMA_ES_OFFSET)
#define reg_MI_XDMA_ES                                     (*(const REGType32v *) REG_XDMA_ES_ADDR)

/* XDMA_ISTAT */

#define REG_XDMA_ISTAT_OFFSET                              0xc028
#define REG_XDMA_ISTAT_ADDR                                (HW_REG_BASE + REG_XDMA_ISTAT_OFFSET)
#define reg_MI_XDMA_ISTAT                                  (*(const REGType32v *) REG_XDMA_ISTAT_ADDR)

/* XDMA_ICLR */

#define REG_XDMA_ICLR_OFFSET                               0xc02c
#define REG_XDMA_ICLR_ADDR                                 (HW_REG_BASE + REG_XDMA_ICLR_OFFSET)
#define reg_MI_XDMA_ICLR                                   (*( REGType32v *) REG_XDMA_ICLR_ADDR)

/* XDMA_FSM */

#define REG_XDMA_FSM_OFFSET                                0xc030
#define REG_XDMA_FSM_ADDR                                  (HW_REG_BASE + REG_XDMA_FSM_OFFSET)
#define reg_MI_XDMA_FSM                                    (*(const REGType32v *) REG_XDMA_FSM_ADDR)

/* XDMA_FSC */

#define REG_XDMA_FSC_OFFSET                                0xc034
#define REG_XDMA_FSC_ADDR                                  (HW_REG_BASE + REG_XDMA_FSC_OFFSET)
#define reg_MI_XDMA_FSC                                    (*(const REGType32v *) REG_XDMA_FSC_ADDR)

/* XDMA_FTM */

#define REG_XDMA_FTM_OFFSET                                0xc038
#define REG_XDMA_FTM_ADDR                                  (HW_REG_BASE + REG_XDMA_FTM_OFFSET)
#define reg_MI_XDMA_FTM                                    (*(const REGType32v *) REG_XDMA_FTM_ADDR)

/* XDMA_FTC0 */

#define REG_XDMA_FTC0_OFFSET                               0xc040
#define REG_XDMA_FTC0_ADDR                                 (HW_REG_BASE + REG_XDMA_FTC0_OFFSET)
#define reg_MI_XDMA_FTC0                                   (*(const REGType32v *) REG_XDMA_FTC0_ADDR)

/* XDMA_FTC1 */

#define REG_XDMA_FTC1_OFFSET                               0xc044
#define REG_XDMA_FTC1_ADDR                                 (HW_REG_BASE + REG_XDMA_FTC1_OFFSET)
#define reg_MI_XDMA_FTC1                                   (*(const REGType32v *) REG_XDMA_FTC1_ADDR)

/* XDMA_CS0 */

#define REG_XDMA_CS0_OFFSET                                0xc100
#define REG_XDMA_CS0_ADDR                                  (HW_REG_BASE + REG_XDMA_CS0_OFFSET)
#define reg_MI_XDMA_CS0                                    (*(const REGType32v *) REG_XDMA_CS0_ADDR)

/* XDMA_CPC0 */

#define REG_XDMA_CPC0_OFFSET                               0xc104
#define REG_XDMA_CPC0_ADDR                                 (HW_REG_BASE + REG_XDMA_CPC0_OFFSET)
#define reg_MI_XDMA_CPC0                                   (*(const REGType32v *) REG_XDMA_CPC0_ADDR)

/* XDMA_CS1 */

#define REG_XDMA_CS1_OFFSET                                0xc108
#define REG_XDMA_CS1_ADDR                                  (HW_REG_BASE + REG_XDMA_CS1_OFFSET)
#define reg_MI_XDMA_CS1                                    (*(const REGType32v *) REG_XDMA_CS1_ADDR)

/* XDMA_CPC1 */

#define REG_XDMA_CPC1_OFFSET                               0xc10c
#define REG_XDMA_CPC1_ADDR                                 (HW_REG_BASE + REG_XDMA_CPC1_OFFSET)
#define reg_MI_XDMA_CPC1                                   (*(const REGType32v *) REG_XDMA_CPC1_ADDR)

/* XDMA_SA0 */

#define REG_XDMA_SA0_OFFSET                                0xc400
#define REG_XDMA_SA0_ADDR                                  (HW_REG_BASE + REG_XDMA_SA0_OFFSET)
#define reg_MI_XDMA_SA0                                    (*(const REGType32v *) REG_XDMA_SA0_ADDR)

/* XDMA_DA0 */

#define REG_XDMA_DA0_OFFSET                                0xc404
#define REG_XDMA_DA0_ADDR                                  (HW_REG_BASE + REG_XDMA_DA0_OFFSET)
#define reg_MI_XDMA_DA0                                    (*(const REGType32v *) REG_XDMA_DA0_ADDR)

/* XDMA_CC0 */

#define REG_XDMA_CC0_OFFSET                                0xc408
#define REG_XDMA_CC0_ADDR                                  (HW_REG_BASE + REG_XDMA_CC0_OFFSET)
#define reg_MI_XDMA_CC0                                    (*(const REGType32v *) REG_XDMA_CC0_ADDR)

/* XDMA_LC00 */

#define REG_XDMA_LC00_OFFSET                               0xc40c
#define REG_XDMA_LC00_ADDR                                 (HW_REG_BASE + REG_XDMA_LC00_OFFSET)
#define reg_MI_XDMA_LC00                                   (*(const REGType32v *) REG_XDMA_LC00_ADDR)

/* XDMA_LC10 */

#define REG_XDMA_LC10_OFFSET                               0xc410
#define REG_XDMA_LC10_ADDR                                 (HW_REG_BASE + REG_XDMA_LC10_OFFSET)
#define reg_MI_XDMA_LC10                                   (*(const REGType32v *) REG_XDMA_LC10_ADDR)

/* XDMA_SA1 */

#define REG_XDMA_SA1_OFFSET                                0xc420
#define REG_XDMA_SA1_ADDR                                  (HW_REG_BASE + REG_XDMA_SA1_OFFSET)
#define reg_MI_XDMA_SA1                                    (*(const REGType32v *) REG_XDMA_SA1_ADDR)

/* XDMA_DA1 */

#define REG_XDMA_DA1_OFFSET                                0xc424
#define REG_XDMA_DA1_ADDR                                  (HW_REG_BASE + REG_XDMA_DA1_OFFSET)
#define reg_MI_XDMA_DA1                                    (*(const REGType32v *) REG_XDMA_DA1_ADDR)

/* XDMA_CC1 */

#define REG_XDMA_CC1_OFFSET                                0xc428
#define REG_XDMA_CC1_ADDR                                  (HW_REG_BASE + REG_XDMA_CC1_OFFSET)
#define reg_MI_XDMA_CC1                                    (*(const REGType32v *) REG_XDMA_CC1_ADDR)

/* XDMA_LC01 */

#define REG_XDMA_LC01_OFFSET                               0xc42c
#define REG_XDMA_LC01_ADDR                                 (HW_REG_BASE + REG_XDMA_LC01_OFFSET)
#define reg_MI_XDMA_LC01                                   (*(const REGType32v *) REG_XDMA_LC01_ADDR)

/* XDMA_LC11 */

#define REG_XDMA_LC11_OFFSET                               0xc430
#define REG_XDMA_LC11_ADDR                                 (HW_REG_BASE + REG_XDMA_LC11_OFFSET)
#define reg_MI_XDMA_LC11                                   (*(const REGType32v *) REG_XDMA_LC11_ADDR)

/* XDMA_DBGSTAT */

#define REG_XDMA_DBGSTAT_OFFSET                            0xcd00
#define REG_XDMA_DBGSTAT_ADDR                              (HW_REG_BASE + REG_XDMA_DBGSTAT_OFFSET)
#define reg_MI_XDMA_DBGSTAT                                (*(const REGType32v *) REG_XDMA_DBGSTAT_ADDR)

/* XDMA_DBGCMD */

#define REG_XDMA_DBGCMD_OFFSET                             0xcd04
#define REG_XDMA_DBGCMD_ADDR                               (HW_REG_BASE + REG_XDMA_DBGCMD_OFFSET)
#define reg_MI_XDMA_DBGCMD                                 (*( REGType32v *) REG_XDMA_DBGCMD_ADDR)

/* XDMA_DBGINST0 */

#define REG_XDMA_DBGINST0_OFFSET                           0xcd08
#define REG_XDMA_DBGINST0_ADDR                             (HW_REG_BASE + REG_XDMA_DBGINST0_OFFSET)
#define reg_MI_XDMA_DBGINST0                               (*( REGType32v *) REG_XDMA_DBGINST0_ADDR)

/* XDMA_DBGINST1 */

#define REG_XDMA_DBGINST1_OFFSET                           0xcd0c
#define REG_XDMA_DBGINST1_ADDR                             (HW_REG_BASE + REG_XDMA_DBGINST1_OFFSET)
#define reg_MI_XDMA_DBGINST1                               (*( REGType32v *) REG_XDMA_DBGINST1_ADDR)

/* XDMA_CFG0 */

#define REG_XDMA_CFG0_OFFSET                               0xce00
#define REG_XDMA_CFG0_ADDR                                 (HW_REG_BASE + REG_XDMA_CFG0_OFFSET)
#define reg_MI_XDMA_CFG0                                   (*(const REGType32v *) REG_XDMA_CFG0_ADDR)

/* XDMA_CFG1 */

#define REG_XDMA_CFG1_OFFSET                               0xce04
#define REG_XDMA_CFG1_ADDR                                 (HW_REG_BASE + REG_XDMA_CFG1_OFFSET)
#define reg_MI_XDMA_CFG1                                   (*(const REGType32v *) REG_XDMA_CFG1_ADDR)

/* XDMA_CFG2 */

#define REG_XDMA_CFG2_OFFSET                               0xce08
#define REG_XDMA_CFG2_ADDR                                 (HW_REG_BASE + REG_XDMA_CFG2_OFFSET)
#define reg_MI_XDMA_CFG2                                   (*(const REGType32v *) REG_XDMA_CFG2_ADDR)

/* XDMA_CFG3 */

#define REG_XDMA_CFG3_OFFSET                               0xce0c
#define REG_XDMA_CFG3_ADDR                                 (HW_REG_BASE + REG_XDMA_CFG3_OFFSET)
#define reg_MI_XDMA_CFG3                                   (*(const REGType32v *) REG_XDMA_CFG3_ADDR)

/* XDMA_CFG4 */

#define REG_XDMA_CFG4_OFFSET                               0xce10
#define REG_XDMA_CFG4_ADDR                                 (HW_REG_BASE + REG_XDMA_CFG4_OFFSET)
#define reg_MI_XDMA_CFG4                                   (*(const REGType32v *) REG_XDMA_CFG4_ADDR)

/* XDMA_CFGDN */

#define REG_XDMA_CFGDN_OFFSET                              0xce14
#define REG_XDMA_CFGDN_ADDR                                (HW_REG_BASE + REG_XDMA_CFGDN_OFFSET)
#define reg_MI_XDMA_CFGDN                                  (*(const REGType32v *) REG_XDMA_CFGDN_ADDR)

/* MCCNT0 */

#define REG_MCCNT0_OFFSET                                  0x164000
#define REG_MCCNT0_ADDR                                    (HW_REG_BASE + REG_MCCNT0_OFFSET)
#define reg_MI_MCCNT0                                      (*( REGType16v *) REG_MCCNT0_ADDR)

/* MCD0 */

#define REG_MCD0_OFFSET                                    0x164002
#define REG_MCD0_ADDR                                      (HW_REG_BASE + REG_MCD0_OFFSET)
#define reg_MI_MCD0                                        (*( REGType16v *) REG_MCD0_ADDR)

/* MCCNT1 */

#define REG_MCCNT1_OFFSET                                  0x164004
#define REG_MCCNT1_ADDR                                    (HW_REG_BASE + REG_MCCNT1_OFFSET)
#define reg_MI_MCCNT1                                      (*( REGType32v *) REG_MCCNT1_ADDR)

/* MCCMD0 */

#define REG_MCCMD0_OFFSET                                  0x164008
#define REG_MCCMD0_ADDR                                    (HW_REG_BASE + REG_MCCMD0_OFFSET)
#define reg_MI_MCCMD0                                      (*( REGType32v *) REG_MCCMD0_ADDR)

/* MCCMD1 */

#define REG_MCCMD1_OFFSET                                  0x16400c
#define REG_MCCMD1_ADDR                                    (HW_REG_BASE + REG_MCCMD1_OFFSET)
#define reg_MI_MCCMD1                                      (*( REGType32v *) REG_MCCMD1_ADDR)

/* MCSCRA_L */

#define REG_MCSCRA_L_OFFSET                                0x164010
#define REG_MCSCRA_L_ADDR                                  (HW_REG_BASE + REG_MCSCRA_L_OFFSET)
#define reg_MI_MCSCRA_L                                    (*( REGType32v *) REG_MCSCRA_L_ADDR)

/* MCSCRB_L */

#define REG_MCSCRB_L_OFFSET                                0x164014
#define REG_MCSCRB_L_ADDR                                  (HW_REG_BASE + REG_MCSCRB_L_OFFSET)
#define reg_MI_MCSCRB_L                                    (*( REGType32v *) REG_MCSCRB_L_ADDR)

/* MCSCRA_H */

#define REG_MCSCRA_H_OFFSET                                0x164018
#define REG_MCSCRA_H_ADDR                                  (HW_REG_BASE + REG_MCSCRA_H_OFFSET)
#define reg_MI_MCSCRA_H                                    (*( REGType8v *) REG_MCSCRA_H_ADDR)

/* MCSCRB_H */

#define REG_MCSCRB_H_OFFSET                                0x16401a
#define REG_MCSCRB_H_ADDR                                  (HW_REG_BASE + REG_MCSCRB_H_OFFSET)
#define reg_MI_MCSCRB_H                                    (*( REGType8v *) REG_MCSCRB_H_ADDR)

/* MCD1 */

#define REG_MCD1_OFFSET                                    0x16401c
#define REG_MCD1_ADDR                                      (HW_REG_BASE + REG_MCD1_OFFSET)
#define reg_MI_MCD1                                        (*( REGType32v *) REG_MCD1_ADDR)

/* CGC_NSPI_CNT1 */

#define REG_CGC_NSPI_CNT1_OFFSET                           0xd800
#define REG_CGC_NSPI_CNT1_ADDR                             (HW_REG_BASE + REG_CGC_NSPI_CNT1_OFFSET)
#define reg_MI_CGC_NSPI_CNT1                               (*( REGType32v *) REG_CGC_NSPI_CNT1_ADDR)

/* CGC_NSPI_CNT2 */

#define REG_CGC_NSPI_CNT2_OFFSET                           0xd804
#define REG_CGC_NSPI_CNT2_ADDR                             (HW_REG_BASE + REG_CGC_NSPI_CNT2_OFFSET)
#define reg_MI_CGC_NSPI_CNT2                               (*( REGType32v *) REG_CGC_NSPI_CNT2_ADDR)

/* CGC_NSPI_CNT3 */

#define REG_CGC_NSPI_CNT3_OFFSET                           0xd808
#define REG_CGC_NSPI_CNT3_ADDR                             (HW_REG_BASE + REG_CGC_NSPI_CNT3_OFFSET)
#define reg_MI_CGC_NSPI_CNT3                               (*( REGType32v *) REG_CGC_NSPI_CNT3_ADDR)

/* CGC_NSPI_DATA */

#define REG_CGC_NSPI_DATA_OFFSET                           0xd80c
#define REG_CGC_NSPI_DATA_ADDR                             (HW_REG_BASE + REG_CGC_NSPI_DATA_OFFSET)
#define reg_MI_CGC_NSPI_DATA                               (*( REGType32v *) REG_CGC_NSPI_DATA_ADDR)

/* CGC_NSPI_DTST */

#define REG_CGC_NSPI_DTST_OFFSET                           0xd810
#define REG_CGC_NSPI_DTST_ADDR                             (HW_REG_BASE + REG_CGC_NSPI_DTST_OFFSET)
#define reg_MI_CGC_NSPI_DTST                               (*(const REGType32v *) REG_CGC_NSPI_DTST_ADDR)

/* CGC_NSPI_AP */

#define REG_CGC_NSPI_AP_OFFSET                             0xd814
#define REG_CGC_NSPI_AP_ADDR                               (HW_REG_BASE + REG_CGC_NSPI_AP_OFFSET)
#define reg_MI_CGC_NSPI_AP                                 (*( REGType32v *) REG_CGC_NSPI_AP_ADDR)

/* CGC_NSPI_INT */

#define REG_CGC_NSPI_INT_OFFSET                            0xd818
#define REG_CGC_NSPI_INT_ADDR                              (HW_REG_BASE + REG_CGC_NSPI_INT_OFFSET)
#define reg_MI_CGC_NSPI_INT                                (*( REGType32v *) REG_CGC_NSPI_INT_ADDR)

/* CGC_NSPI_INTC */

#define REG_CGC_NSPI_INTC_OFFSET                           0xd81c
#define REG_CGC_NSPI_INTC_ADDR                             (HW_REG_BASE + REG_CGC_NSPI_INTC_OFFSET)
#define reg_MI_CGC_NSPI_INTC                               (*( REGType32v *) REG_CGC_NSPI_INTC_ADDR)


/*
 * Definitions of Register fields
 */


/* CGC1_CNT1 */

#define REG_MI_CGC1_CNT1_E_SHIFT                           31
#define REG_MI_CGC1_CNT1_E_SIZE                            1
#define REG_MI_CGC1_CNT1_E_MASK                            0x80000000

#define REG_MI_CGC1_CNT1_I_SHIFT                           30
#define REG_MI_CGC1_CNT1_I_SIZE                            1
#define REG_MI_CGC1_CNT1_I_MASK                            0x40000000

#define REG_MI_CGC1_CNT1_WR_SHIFT                          29
#define REG_MI_CGC1_CNT1_WR_SIZE                           1
#define REG_MI_CGC1_CNT1_WR_MASK                           0x20000000

#define REG_MI_CGC1_CNT1_RESB_SHIFT                        28
#define REG_MI_CGC1_CNT1_RESB_SIZE                         1
#define REG_MI_CGC1_CNT1_RESB_MASK                         0x10000000

#define REG_MI_CGC1_CNT1_RDY_SHIFT                         27
#define REG_MI_CGC1_CNT1_RDY_SIZE                          1
#define REG_MI_CGC1_CNT1_RDY_MASK                          0x08000000

#define REG_MI_CGC1_CNT1_MS_SHIFT                          24
#define REG_MI_CGC1_CNT1_MS_SIZE                           3
#define REG_MI_CGC1_CNT1_MS_MASK                           0x07000000

#define REG_MI_CGC1_CNT1_PG_SZ_SHIFT                       16
#define REG_MI_CGC1_CNT1_PG_SZ_SIZE                        4
#define REG_MI_CGC1_CNT1_PG_SZ_MASK                        0x000f0000

#define REG_MI_CGC1_CNT1_DRQ_E_SHIFT                       15
#define REG_MI_CGC1_CNT1_DRQ_E_SIZE                        1
#define REG_MI_CGC1_CNT1_DRQ_E_MASK                        0x00008000

#define REG_MI_CGC1_CNT1_CRC_E_SHIFT                       9
#define REG_MI_CGC1_CNT1_CRC_E_SIZE                        1
#define REG_MI_CGC1_CNT1_CRC_E_MASK                        0x00000200

#define REG_MI_CGC1_CNT1_CRC_ERR_SHIFT                     8
#define REG_MI_CGC1_CNT1_CRC_ERR_SIZE                      1
#define REG_MI_CGC1_CNT1_CRC_ERR_MASK                      0x00000100

#define REG_MI_CGC1_CNT1_TO_E_SHIFT                        5
#define REG_MI_CGC1_CNT1_TO_E_SIZE                         1
#define REG_MI_CGC1_CNT1_TO_E_MASK                         0x00000020

#define REG_MI_CGC1_CNT1_TO_ERR_SHIFT                      4
#define REG_MI_CGC1_CNT1_TO_ERR_SIZE                       1
#define REG_MI_CGC1_CNT1_TO_ERR_MASK                       0x00000010

#define REG_MI_CGC1_CNT1_TO_TM_SHIFT                       0
#define REG_MI_CGC1_CNT1_TO_TM_SIZE                        4
#define REG_MI_CGC1_CNT1_TO_TM_MASK                        0x0000000f

#ifndef SDK_ASM
#define REG_MI_CGC1_CNT1_FIELD( e, i, wr, resb, rdy, ms, pg_sz, drq_e, crc_e, crc_err, to_e, to_err, to_tm ) \
    (u32)( \
    ((u32)(e) << REG_MI_CGC1_CNT1_E_SHIFT) | \
    ((u32)(i) << REG_MI_CGC1_CNT1_I_SHIFT) | \
    ((u32)(wr) << REG_MI_CGC1_CNT1_WR_SHIFT) | \
    ((u32)(resb) << REG_MI_CGC1_CNT1_RESB_SHIFT) | \
    ((u32)(rdy) << REG_MI_CGC1_CNT1_RDY_SHIFT) | \
    ((u32)(ms) << REG_MI_CGC1_CNT1_MS_SHIFT) | \
    ((u32)(pg_sz) << REG_MI_CGC1_CNT1_PG_SZ_SHIFT) | \
    ((u32)(drq_e) << REG_MI_CGC1_CNT1_DRQ_E_SHIFT) | \
    ((u32)(crc_e) << REG_MI_CGC1_CNT1_CRC_E_SHIFT) | \
    ((u32)(crc_err) << REG_MI_CGC1_CNT1_CRC_ERR_SHIFT) | \
    ((u32)(to_e) << REG_MI_CGC1_CNT1_TO_E_SHIFT) | \
    ((u32)(to_err) << REG_MI_CGC1_CNT1_TO_ERR_SHIFT) | \
    ((u32)(to_tm) << REG_MI_CGC1_CNT1_TO_TM_SHIFT))
#endif


/* CGC1_CNT2 */

#define REG_MI_CGC1_CNT2_W_LT_SHIFT                        16
#define REG_MI_CGC1_CNT2_W_LT_SIZE                         13
#define REG_MI_CGC1_CNT2_W_LT_MASK                         0x1fff0000

#define REG_MI_CGC1_CNT2_PG_CNT_SHIFT                      0
#define REG_MI_CGC1_CNT2_PG_CNT_SIZE                       15
#define REG_MI_CGC1_CNT2_PG_CNT_MASK                       0x00007fff

#ifndef SDK_ASM
#define REG_MI_CGC1_CNT2_FIELD( w_lt, pg_cnt ) \
    (u32)( \
    ((u32)(w_lt) << REG_MI_CGC1_CNT2_W_LT_SHIFT) | \
    ((u32)(pg_cnt) << REG_MI_CGC1_CNT2_PG_CNT_SHIFT))
#endif


/* CGC1_SC */

#define REG_MI_CGC1_SC_INIT_SHIFT                          15
#define REG_MI_CGC1_SC_INIT_SIZE                           1
#define REG_MI_CGC1_SC_INIT_MASK                           0x00008000

#define REG_MI_CGC1_SC_RDY_SHIFT                           14
#define REG_MI_CGC1_SC_RDY_SIZE                            1
#define REG_MI_CGC1_SC_RDY_MASK                            0x00004000

#define REG_MI_CGC1_SC_K_SEL_SHIFT                         8
#define REG_MI_CGC1_SC_K_SEL_SIZE                          2
#define REG_MI_CGC1_SC_K_SEL_MASK                          0x00000300

#define REG_MI_CGC1_SC_E_SHIFT                             2
#define REG_MI_CGC1_SC_E_SIZE                              1
#define REG_MI_CGC1_SC_E_MASK                              0x00000004

#define REG_MI_CGC1_SC_MSEL_SHIFT                          0
#define REG_MI_CGC1_SC_MSEL_SIZE                           2
#define REG_MI_CGC1_SC_MSEL_MASK                           0x00000003

#ifndef SDK_ASM
#define REG_MI_CGC1_SC_FIELD( init, rdy, k_sel, e, msel ) \
    (u32)( \
    ((u32)(init) << REG_MI_CGC1_SC_INIT_SHIFT) | \
    ((u32)(rdy) << REG_MI_CGC1_SC_RDY_SHIFT) | \
    ((u32)(k_sel) << REG_MI_CGC1_SC_K_SEL_SHIFT) | \
    ((u32)(e) << REG_MI_CGC1_SC_E_SHIFT) | \
    ((u32)(msel) << REG_MI_CGC1_SC_MSEL_SHIFT))
#endif


/* CGC1_PROT */

#define REG_MI_CGC1_PROT_E_SHIFT                           0
#define REG_MI_CGC1_PROT_E_SIZE                            1
#define REG_MI_CGC1_PROT_E_MASK                            0x00000001

#ifndef SDK_ASM
#define REG_MI_CGC1_PROT_FIELD( e ) \
    (u32)( \
    ((u32)(e) << REG_MI_CGC1_PROT_E_SHIFT))
#endif


/* CGC1_KEY1 */

/* CGC1_KEY2 */

/* CGC1_CMD0 */

/* CGC1_CMD1 */

/* CGC1_CMD2 */

/* CGC1_CMD3 */

/* CGC1_DATA */

/* CGC2_CNT1 */

#define REG_MI_CGC2_CNT1_E_SHIFT                           31
#define REG_MI_CGC2_CNT1_E_SIZE                            1
#define REG_MI_CGC2_CNT1_E_MASK                            0x80000000

#define REG_MI_CGC2_CNT1_I_SHIFT                           30
#define REG_MI_CGC2_CNT1_I_SIZE                            1
#define REG_MI_CGC2_CNT1_I_MASK                            0x40000000

#define REG_MI_CGC2_CNT1_WR_SHIFT                          29
#define REG_MI_CGC2_CNT1_WR_SIZE                           1
#define REG_MI_CGC2_CNT1_WR_MASK                           0x20000000

#define REG_MI_CGC2_CNT1_RESB_SHIFT                        28
#define REG_MI_CGC2_CNT1_RESB_SIZE                         1
#define REG_MI_CGC2_CNT1_RESB_MASK                         0x10000000

#define REG_MI_CGC2_CNT1_RDY_SHIFT                         27
#define REG_MI_CGC2_CNT1_RDY_SIZE                          1
#define REG_MI_CGC2_CNT1_RDY_MASK                          0x08000000

#define REG_MI_CGC2_CNT1_MS_SHIFT                          24
#define REG_MI_CGC2_CNT1_MS_SIZE                           3
#define REG_MI_CGC2_CNT1_MS_MASK                           0x07000000

#define REG_MI_CGC2_CNT1_PG_SZ_SHIFT                       16
#define REG_MI_CGC2_CNT1_PG_SZ_SIZE                        4
#define REG_MI_CGC2_CNT1_PG_SZ_MASK                        0x000f0000

#define REG_MI_CGC2_CNT1_DRQ_E_SHIFT                       15
#define REG_MI_CGC2_CNT1_DRQ_E_SIZE                        1
#define REG_MI_CGC2_CNT1_DRQ_E_MASK                        0x00008000

#define REG_MI_CGC2_CNT1_CRC_E_SHIFT                       9
#define REG_MI_CGC2_CNT1_CRC_E_SIZE                        1
#define REG_MI_CGC2_CNT1_CRC_E_MASK                        0x00000200

#define REG_MI_CGC2_CNT1_CRC_ERR_SHIFT                     8
#define REG_MI_CGC2_CNT1_CRC_ERR_SIZE                      1
#define REG_MI_CGC2_CNT1_CRC_ERR_MASK                      0x00000100

#define REG_MI_CGC2_CNT1_TO_E_SHIFT                        5
#define REG_MI_CGC2_CNT1_TO_E_SIZE                         1
#define REG_MI_CGC2_CNT1_TO_E_MASK                         0x00000020

#define REG_MI_CGC2_CNT1_TO_ERR_SHIFT                      4
#define REG_MI_CGC2_CNT1_TO_ERR_SIZE                       1
#define REG_MI_CGC2_CNT1_TO_ERR_MASK                       0x00000010

#define REG_MI_CGC2_CNT1_TO_TM_SHIFT                       0
#define REG_MI_CGC2_CNT1_TO_TM_SIZE                        4
#define REG_MI_CGC2_CNT1_TO_TM_MASK                        0x0000000f

#ifndef SDK_ASM
#define REG_MI_CGC2_CNT1_FIELD( e, i, wr, resb, rdy, ms, pg_sz, drq_e, crc_e, crc_err, to_e, to_err, to_tm ) \
    (u32)( \
    ((u32)(e) << REG_MI_CGC2_CNT1_E_SHIFT) | \
    ((u32)(i) << REG_MI_CGC2_CNT1_I_SHIFT) | \
    ((u32)(wr) << REG_MI_CGC2_CNT1_WR_SHIFT) | \
    ((u32)(resb) << REG_MI_CGC2_CNT1_RESB_SHIFT) | \
    ((u32)(rdy) << REG_MI_CGC2_CNT1_RDY_SHIFT) | \
    ((u32)(ms) << REG_MI_CGC2_CNT1_MS_SHIFT) | \
    ((u32)(pg_sz) << REG_MI_CGC2_CNT1_PG_SZ_SHIFT) | \
    ((u32)(drq_e) << REG_MI_CGC2_CNT1_DRQ_E_SHIFT) | \
    ((u32)(crc_e) << REG_MI_CGC2_CNT1_CRC_E_SHIFT) | \
    ((u32)(crc_err) << REG_MI_CGC2_CNT1_CRC_ERR_SHIFT) | \
    ((u32)(to_e) << REG_MI_CGC2_CNT1_TO_E_SHIFT) | \
    ((u32)(to_err) << REG_MI_CGC2_CNT1_TO_ERR_SHIFT) | \
    ((u32)(to_tm) << REG_MI_CGC2_CNT1_TO_TM_SHIFT))
#endif


/* CGC2_CNT2 */

#define REG_MI_CGC2_CNT2_W_LT_SHIFT                        16
#define REG_MI_CGC2_CNT2_W_LT_SIZE                         13
#define REG_MI_CGC2_CNT2_W_LT_MASK                         0x1fff0000

#define REG_MI_CGC2_CNT2_PG_CNT_SHIFT                      0
#define REG_MI_CGC2_CNT2_PG_CNT_SIZE                       15
#define REG_MI_CGC2_CNT2_PG_CNT_MASK                       0x00007fff

#ifndef SDK_ASM
#define REG_MI_CGC2_CNT2_FIELD( w_lt, pg_cnt ) \
    (u32)( \
    ((u32)(w_lt) << REG_MI_CGC2_CNT2_W_LT_SHIFT) | \
    ((u32)(pg_cnt) << REG_MI_CGC2_CNT2_PG_CNT_SHIFT))
#endif


/* CGC2_AUTH */

#define REG_MI_CGC2_AUTH_A_ST_SHIFT                        15
#define REG_MI_CGC2_AUTH_A_ST_SIZE                         1
#define REG_MI_CGC2_AUTH_A_ST_MASK                         0x00008000

#define REG_MI_CGC2_AUTH_A_RDY_SHIFT                       14
#define REG_MI_CGC2_AUTH_A_RDY_SIZE                        1
#define REG_MI_CGC2_AUTH_A_RDY_MASK                        0x00004000

#define REG_MI_CGC2_AUTH_A_ERR_SHIFT                       13
#define REG_MI_CGC2_AUTH_A_ERR_SIZE                        1
#define REG_MI_CGC2_AUTH_A_ERR_MASK                        0x00002000

#define REG_MI_CGC2_AUTH_K_ST_SHIFT                        12
#define REG_MI_CGC2_AUTH_K_ST_SIZE                         1
#define REG_MI_CGC2_AUTH_K_ST_MASK                         0x00001000

#define REG_MI_CGC2_AUTH_K_RDY_SHIFT                       11
#define REG_MI_CGC2_AUTH_K_RDY_SIZE                        1
#define REG_MI_CGC2_AUTH_K_RDY_MASK                        0x00000800

#define REG_MI_CGC2_AUTH_K_ERR_SHIFT                       10
#define REG_MI_CGC2_AUTH_K_ERR_SIZE                        1
#define REG_MI_CGC2_AUTH_K_ERR_MASK                        0x00000400

#define REG_MI_CGC2_AUTH_K_SEL_SHIFT                       8
#define REG_MI_CGC2_AUTH_K_SEL_SIZE                        2
#define REG_MI_CGC2_AUTH_K_SEL_MASK                        0x00000300

#ifndef SDK_ASM
#define REG_MI_CGC2_AUTH_FIELD( a_st, a_rdy, a_err, k_st, k_rdy, k_err, k_sel ) \
    (u32)( \
    ((u32)(a_st) << REG_MI_CGC2_AUTH_A_ST_SHIFT) | \
    ((u32)(a_rdy) << REG_MI_CGC2_AUTH_A_RDY_SHIFT) | \
    ((u32)(a_err) << REG_MI_CGC2_AUTH_A_ERR_SHIFT) | \
    ((u32)(k_st) << REG_MI_CGC2_AUTH_K_ST_SHIFT) | \
    ((u32)(k_rdy) << REG_MI_CGC2_AUTH_K_RDY_SHIFT) | \
    ((u32)(k_err) << REG_MI_CGC2_AUTH_K_ERR_SHIFT) | \
    ((u32)(k_sel) << REG_MI_CGC2_AUTH_K_SEL_SHIFT))
#endif


/* CGC2_PROT */

#define REG_MI_CGC2_PROT_E_SHIFT                           0
#define REG_MI_CGC2_PROT_E_SIZE                            1
#define REG_MI_CGC2_PROT_E_MASK                            0x00000001

#ifndef SDK_ASM
#define REG_MI_CGC2_PROT_FIELD( e ) \
    (u32)( \
    ((u32)(e) << REG_MI_CGC2_PROT_E_SHIFT))
#endif


/* CGC2_CMD0 */

/* CGC2_CMD1 */

/* CGC2_CMD2 */

/* CGC2_CMD3 */

/* CGC2_DATA */

/* NDMAGCNT */

#define REG_MI_NDMAGCNT_ARBITER_SHIFT                      31
#define REG_MI_NDMAGCNT_ARBITER_SIZE                       1
#define REG_MI_NDMAGCNT_ARBITER_MASK                       0x80000000

#define REG_MI_NDMAGCNT_CPUCYCLE_SHIFT                     16
#define REG_MI_NDMAGCNT_CPUCYCLE_SIZE                      4
#define REG_MI_NDMAGCNT_CPUCYCLE_MASK                      0x000f0000

#define REG_MI_NDMAGCNT_RDBK_SHIFT                         0
#define REG_MI_NDMAGCNT_RDBK_SIZE                          1
#define REG_MI_NDMAGCNT_RDBK_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_MI_NDMAGCNT_FIELD( arbiter, cpucycle, rdbk ) \
    (u32)( \
    ((u32)(arbiter) << REG_MI_NDMAGCNT_ARBITER_SHIFT) | \
    ((u32)(cpucycle) << REG_MI_NDMAGCNT_CPUCYCLE_SHIFT) | \
    ((u32)(rdbk) << REG_MI_NDMAGCNT_RDBK_SHIFT))
#endif


/* NDMA0SAD */

#define REG_MI_NDMA0SAD_DMASRC_SHIFT                       2
#define REG_MI_NDMA0SAD_DMASRC_SIZE                        30
#define REG_MI_NDMA0SAD_DMASRC_MASK                        0xfffffffc

#ifndef SDK_ASM
#define REG_MI_NDMA0SAD_FIELD( dmasrc ) \
    (u32)( \
    ((u32)(dmasrc) << REG_MI_NDMA0SAD_DMASRC_SHIFT))
#endif


/* NDMA0DAD */

#define REG_MI_NDMA0DAD_DMADEST_SHIFT                      2
#define REG_MI_NDMA0DAD_DMADEST_SIZE                       30
#define REG_MI_NDMA0DAD_DMADEST_MASK                       0xfffffffc

#ifndef SDK_ASM
#define REG_MI_NDMA0DAD_FIELD( dmadest ) \
    (u32)( \
    ((u32)(dmadest) << REG_MI_NDMA0DAD_DMADEST_SHIFT))
#endif


/* NDMA0TCNT */

#define REG_MI_NDMA0TCNT_TOTALCNT_SHIFT                    0
#define REG_MI_NDMA0TCNT_TOTALCNT_SIZE                     28
#define REG_MI_NDMA0TCNT_TOTALCNT_MASK                     0x0fffffff

#ifndef SDK_ASM
#define REG_MI_NDMA0TCNT_FIELD( totalcnt ) \
    (u32)( \
    ((u32)(totalcnt) << REG_MI_NDMA0TCNT_TOTALCNT_SHIFT))
#endif


/* NDMA0WCNT */

#define REG_MI_NDMA0WCNT_WORDCNT_SHIFT                     0
#define REG_MI_NDMA0WCNT_WORDCNT_SIZE                      24
#define REG_MI_NDMA0WCNT_WORDCNT_MASK                      0x00ffffff

#ifndef SDK_ASM
#define REG_MI_NDMA0WCNT_FIELD( wordcnt ) \
    (u32)( \
    ((u32)(wordcnt) << REG_MI_NDMA0WCNT_WORDCNT_SHIFT))
#endif


/* NDMA0BCNT */

#define REG_MI_NDMA0BCNT_PS_SHIFT                          16
#define REG_MI_NDMA0BCNT_PS_SIZE                           2
#define REG_MI_NDMA0BCNT_PS_MASK                           0x00030000

#define REG_MI_NDMA0BCNT_ICNT_SHIFT                        0
#define REG_MI_NDMA0BCNT_ICNT_SIZE                         16
#define REG_MI_NDMA0BCNT_ICNT_MASK                         0x0000ffff

#ifndef SDK_ASM
#define REG_MI_NDMA0BCNT_FIELD( ps, icnt ) \
    (u32)( \
    ((u32)(ps) << REG_MI_NDMA0BCNT_PS_SHIFT) | \
    ((u32)(icnt) << REG_MI_NDMA0BCNT_ICNT_SHIFT))
#endif


/* NDMA0FDATA */

#define REG_MI_NDMA0FDATA_FDATA_SHIFT                      0
#define REG_MI_NDMA0FDATA_FDATA_SIZE                       32
#define REG_MI_NDMA0FDATA_FDATA_MASK                       0xffffffff

#ifndef SDK_ASM
#define REG_MI_NDMA0FDATA_FIELD( fdata ) \
    (u32)( \
    ((u32)(fdata) << REG_MI_NDMA0FDATA_FDATA_SHIFT))
#endif


/* NDMA0CNT */

#define REG_MI_NDMA0CNT_E_SHIFT                            31
#define REG_MI_NDMA0CNT_E_SIZE                             1
#define REG_MI_NDMA0CNT_E_MASK                             0x80000000

#define REG_MI_NDMA0CNT_I_SHIFT                            30
#define REG_MI_NDMA0CNT_I_SIZE                             1
#define REG_MI_NDMA0CNT_I_MASK                             0x40000000

#define REG_MI_NDMA0CNT_CM_SHIFT                           29
#define REG_MI_NDMA0CNT_CM_SIZE                            1
#define REG_MI_NDMA0CNT_CM_MASK                            0x20000000

#define REG_MI_NDMA0CNT_IM_SHIFT                           28
#define REG_MI_NDMA0CNT_IM_SIZE                            1
#define REG_MI_NDMA0CNT_IM_MASK                            0x10000000

#define REG_MI_NDMA0CNT_MODE_SHIFT                         24
#define REG_MI_NDMA0CNT_MODE_SIZE                          4
#define REG_MI_NDMA0CNT_MODE_MASK                          0x0f000000

#define REG_MI_NDMA0CNT_WORDCNT_SHIFT                      16
#define REG_MI_NDMA0CNT_WORDCNT_SIZE                       4
#define REG_MI_NDMA0CNT_WORDCNT_MASK                       0x000f0000

#define REG_MI_NDMA0CNT_SRL_SHIFT                          15
#define REG_MI_NDMA0CNT_SRL_SIZE                           1
#define REG_MI_NDMA0CNT_SRL_MASK                           0x00008000

#define REG_MI_NDMA0CNT_SAR_SHIFT                          13
#define REG_MI_NDMA0CNT_SAR_SIZE                           2
#define REG_MI_NDMA0CNT_SAR_MASK                           0x00006000

#define REG_MI_NDMA0CNT_DRL_SHIFT                          12
#define REG_MI_NDMA0CNT_DRL_SIZE                           1
#define REG_MI_NDMA0CNT_DRL_MASK                           0x00001000

#define REG_MI_NDMA0CNT_DAR_SHIFT                          10
#define REG_MI_NDMA0CNT_DAR_SIZE                           2
#define REG_MI_NDMA0CNT_DAR_MASK                           0x00000c00

#define REG_MI_NDMA0CNT_DM_SHIFT                           0
#define REG_MI_NDMA0CNT_DM_SIZE                            5
#define REG_MI_NDMA0CNT_DM_MASK                            0x0000001f

#ifndef SDK_ASM
#define REG_MI_NDMA0CNT_FIELD( e, i, cm, im, mode, wordcnt, srl, sar, drl, dar, dm ) \
    (u32)( \
    ((u32)(e) << REG_MI_NDMA0CNT_E_SHIFT) | \
    ((u32)(i) << REG_MI_NDMA0CNT_I_SHIFT) | \
    ((u32)(cm) << REG_MI_NDMA0CNT_CM_SHIFT) | \
    ((u32)(im) << REG_MI_NDMA0CNT_IM_SHIFT) | \
    ((u32)(mode) << REG_MI_NDMA0CNT_MODE_SHIFT) | \
    ((u32)(wordcnt) << REG_MI_NDMA0CNT_WORDCNT_SHIFT) | \
    ((u32)(srl) << REG_MI_NDMA0CNT_SRL_SHIFT) | \
    ((u32)(sar) << REG_MI_NDMA0CNT_SAR_SHIFT) | \
    ((u32)(drl) << REG_MI_NDMA0CNT_DRL_SHIFT) | \
    ((u32)(dar) << REG_MI_NDMA0CNT_DAR_SHIFT) | \
    ((u32)(dm) << REG_MI_NDMA0CNT_DM_SHIFT))
#endif


/* NDMA1SAD */

#define REG_MI_NDMA1SAD_DMASRC_SHIFT                       2
#define REG_MI_NDMA1SAD_DMASRC_SIZE                        30
#define REG_MI_NDMA1SAD_DMASRC_MASK                        0xfffffffc

#ifndef SDK_ASM
#define REG_MI_NDMA1SAD_FIELD( dmasrc ) \
    (u32)( \
    ((u32)(dmasrc) << REG_MI_NDMA1SAD_DMASRC_SHIFT))
#endif


/* NDMA1DAD */

#define REG_MI_NDMA1DAD_DMADEST_SHIFT                      2
#define REG_MI_NDMA1DAD_DMADEST_SIZE                       30
#define REG_MI_NDMA1DAD_DMADEST_MASK                       0xfffffffc

#ifndef SDK_ASM
#define REG_MI_NDMA1DAD_FIELD( dmadest ) \
    (u32)( \
    ((u32)(dmadest) << REG_MI_NDMA1DAD_DMADEST_SHIFT))
#endif


/* NDMA1TCNT */

#define REG_MI_NDMA1TCNT_TOTALCNT_SHIFT                    0
#define REG_MI_NDMA1TCNT_TOTALCNT_SIZE                     28
#define REG_MI_NDMA1TCNT_TOTALCNT_MASK                     0x0fffffff

#ifndef SDK_ASM
#define REG_MI_NDMA1TCNT_FIELD( totalcnt ) \
    (u32)( \
    ((u32)(totalcnt) << REG_MI_NDMA1TCNT_TOTALCNT_SHIFT))
#endif


/* NDMA1WCNT */

#define REG_MI_NDMA1WCNT_WORDCNT_SHIFT                     0
#define REG_MI_NDMA1WCNT_WORDCNT_SIZE                      24
#define REG_MI_NDMA1WCNT_WORDCNT_MASK                      0x00ffffff

#ifndef SDK_ASM
#define REG_MI_NDMA1WCNT_FIELD( wordcnt ) \
    (u32)( \
    ((u32)(wordcnt) << REG_MI_NDMA1WCNT_WORDCNT_SHIFT))
#endif


/* NDMA1BCNT */

#define REG_MI_NDMA1BCNT_PS_SHIFT                          16
#define REG_MI_NDMA1BCNT_PS_SIZE                           2
#define REG_MI_NDMA1BCNT_PS_MASK                           0x00030000

#define REG_MI_NDMA1BCNT_ICNT_SHIFT                        0
#define REG_MI_NDMA1BCNT_ICNT_SIZE                         16
#define REG_MI_NDMA1BCNT_ICNT_MASK                         0x0000ffff

#ifndef SDK_ASM
#define REG_MI_NDMA1BCNT_FIELD( ps, icnt ) \
    (u32)( \
    ((u32)(ps) << REG_MI_NDMA1BCNT_PS_SHIFT) | \
    ((u32)(icnt) << REG_MI_NDMA1BCNT_ICNT_SHIFT))
#endif


/* NDMA1FDATA */

#define REG_MI_NDMA1FDATA_FDATA_SHIFT                      0
#define REG_MI_NDMA1FDATA_FDATA_SIZE                       32
#define REG_MI_NDMA1FDATA_FDATA_MASK                       0xffffffff

#ifndef SDK_ASM
#define REG_MI_NDMA1FDATA_FIELD( fdata ) \
    (u32)( \
    ((u32)(fdata) << REG_MI_NDMA1FDATA_FDATA_SHIFT))
#endif


/* NDMA1CNT */

#define REG_MI_NDMA1CNT_E_SHIFT                            31
#define REG_MI_NDMA1CNT_E_SIZE                             1
#define REG_MI_NDMA1CNT_E_MASK                             0x80000000

#define REG_MI_NDMA1CNT_I_SHIFT                            30
#define REG_MI_NDMA1CNT_I_SIZE                             1
#define REG_MI_NDMA1CNT_I_MASK                             0x40000000

#define REG_MI_NDMA1CNT_CM_SHIFT                           29
#define REG_MI_NDMA1CNT_CM_SIZE                            1
#define REG_MI_NDMA1CNT_CM_MASK                            0x20000000

#define REG_MI_NDMA1CNT_IM_SHIFT                           28
#define REG_MI_NDMA1CNT_IM_SIZE                            1
#define REG_MI_NDMA1CNT_IM_MASK                            0x10000000

#define REG_MI_NDMA1CNT_MODE_SHIFT                         24
#define REG_MI_NDMA1CNT_MODE_SIZE                          4
#define REG_MI_NDMA1CNT_MODE_MASK                          0x0f000000

#define REG_MI_NDMA1CNT_WORDCNT_SHIFT                      16
#define REG_MI_NDMA1CNT_WORDCNT_SIZE                       4
#define REG_MI_NDMA1CNT_WORDCNT_MASK                       0x000f0000

#define REG_MI_NDMA1CNT_SRL_SHIFT                          15
#define REG_MI_NDMA1CNT_SRL_SIZE                           1
#define REG_MI_NDMA1CNT_SRL_MASK                           0x00008000

#define REG_MI_NDMA1CNT_SAR_SHIFT                          13
#define REG_MI_NDMA1CNT_SAR_SIZE                           2
#define REG_MI_NDMA1CNT_SAR_MASK                           0x00006000

#define REG_MI_NDMA1CNT_DRL_SHIFT                          12
#define REG_MI_NDMA1CNT_DRL_SIZE                           1
#define REG_MI_NDMA1CNT_DRL_MASK                           0x00001000

#define REG_MI_NDMA1CNT_DAR_SHIFT                          10
#define REG_MI_NDMA1CNT_DAR_SIZE                           2
#define REG_MI_NDMA1CNT_DAR_MASK                           0x00000c00

#define REG_MI_NDMA1CNT_DM_SHIFT                           0
#define REG_MI_NDMA1CNT_DM_SIZE                            5
#define REG_MI_NDMA1CNT_DM_MASK                            0x0000001f

#ifndef SDK_ASM
#define REG_MI_NDMA1CNT_FIELD( e, i, cm, im, mode, wordcnt, srl, sar, drl, dar, dm ) \
    (u32)( \
    ((u32)(e) << REG_MI_NDMA1CNT_E_SHIFT) | \
    ((u32)(i) << REG_MI_NDMA1CNT_I_SHIFT) | \
    ((u32)(cm) << REG_MI_NDMA1CNT_CM_SHIFT) | \
    ((u32)(im) << REG_MI_NDMA1CNT_IM_SHIFT) | \
    ((u32)(mode) << REG_MI_NDMA1CNT_MODE_SHIFT) | \
    ((u32)(wordcnt) << REG_MI_NDMA1CNT_WORDCNT_SHIFT) | \
    ((u32)(srl) << REG_MI_NDMA1CNT_SRL_SHIFT) | \
    ((u32)(sar) << REG_MI_NDMA1CNT_SAR_SHIFT) | \
    ((u32)(drl) << REG_MI_NDMA1CNT_DRL_SHIFT) | \
    ((u32)(dar) << REG_MI_NDMA1CNT_DAR_SHIFT) | \
    ((u32)(dm) << REG_MI_NDMA1CNT_DM_SHIFT))
#endif


/* XDMA_DS */

#define REG_MI_XDMA_DS_DNS_SHIFT                           9
#define REG_MI_XDMA_DS_DNS_SIZE                            1
#define REG_MI_XDMA_DS_DNS_MASK                            0x00000200

#define REG_MI_XDMA_DS_WEV_SHIFT                           4
#define REG_MI_XDMA_DS_WEV_SIZE                            5
#define REG_MI_XDMA_DS_WEV_MASK                            0x000001f0

#define REG_MI_XDMA_DS_STAT_SHIFT                          0
#define REG_MI_XDMA_DS_STAT_SIZE                           4
#define REG_MI_XDMA_DS_STAT_MASK                           0x0000000f

#ifndef SDK_ASM
#define REG_MI_XDMA_DS_FIELD( dns, wev, stat ) \
    (u32)( \
    ((u32)(dns) << REG_MI_XDMA_DS_DNS_SHIFT) | \
    ((u32)(wev) << REG_MI_XDMA_DS_WEV_SHIFT) | \
    ((u32)(stat) << REG_MI_XDMA_DS_STAT_SHIFT))
#endif


/* XDMA_DPC */

/* XDMA_IE */

#define REG_MI_XDMA_IE_IRQ_SHIFT                           0
#define REG_MI_XDMA_IE_IRQ_SIZE                            4
#define REG_MI_XDMA_IE_IRQ_MASK                            0x0000000f

#ifndef SDK_ASM
#define REG_MI_XDMA_IE_FIELD( irq ) \
    (u32)( \
    ((u32)(irq) << REG_MI_XDMA_IE_IRQ_SHIFT))
#endif


/* XDMA_ES */

/* XDMA_ISTAT */

#define REG_MI_XDMA_ISTAT_IRQ_SHIFT                        0
#define REG_MI_XDMA_ISTAT_IRQ_SIZE                         4
#define REG_MI_XDMA_ISTAT_IRQ_MASK                         0x0000000f

#ifndef SDK_ASM
#define REG_MI_XDMA_ISTAT_FIELD( irq ) \
    (u32)( \
    ((u32)(irq) << REG_MI_XDMA_ISTAT_IRQ_SHIFT))
#endif


/* XDMA_ICLR */

#define REG_MI_XDMA_ICLR_IRQ_SHIFT                         0
#define REG_MI_XDMA_ICLR_IRQ_SIZE                          4
#define REG_MI_XDMA_ICLR_IRQ_MASK                          0x0000000f

#ifndef SDK_ASM
#define REG_MI_XDMA_ICLR_FIELD( irq ) \
    (u32)( \
    ((u32)(irq) << REG_MI_XDMA_ICLR_IRQ_SHIFT))
#endif


/* XDMA_FSM */

#define REG_MI_XDMA_FSM_FS_MGR_SHIFT                       0
#define REG_MI_XDMA_FSM_FS_MGR_SIZE                        1
#define REG_MI_XDMA_FSM_FS_MGR_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_MI_XDMA_FSM_FIELD( fs_mgr ) \
    (u32)( \
    ((u32)(fs_mgr) << REG_MI_XDMA_FSM_FS_MGR_SHIFT))
#endif


/* XDMA_FSC */

#define REG_MI_XDMA_FSC_FS_CH_SHIFT                        0
#define REG_MI_XDMA_FSC_FS_CH_SIZE                         8
#define REG_MI_XDMA_FSC_FS_CH_MASK                         0x000000ff

#ifndef SDK_ASM
#define REG_MI_XDMA_FSC_FIELD( fs_ch ) \
    (u32)( \
    ((u32)(fs_ch) << REG_MI_XDMA_FSC_FS_CH_SHIFT))
#endif


/* XDMA_FTM */

#define REG_MI_XDMA_FTM_DBG_INST_SHIFT                     30
#define REG_MI_XDMA_FTM_DBG_INST_SIZE                      1
#define REG_MI_XDMA_FTM_DBG_INST_MASK                      0x40000000

#define REG_MI_XDMA_FTM_FETCH_ERR_SHIFT                    16
#define REG_MI_XDMA_FTM_FETCH_ERR_SIZE                     1
#define REG_MI_XDMA_FTM_FETCH_ERR_MASK                     0x00010000

#define REG_MI_XDMA_FTM_EVENT_ERR_SHIFT                    5
#define REG_MI_XDMA_FTM_EVENT_ERR_SIZE                     1
#define REG_MI_XDMA_FTM_EVENT_ERR_MASK                     0x00000020

#define REG_MI_XDMA_FTM_DMAGO_ERR_SHIFT                    4
#define REG_MI_XDMA_FTM_DMAGO_ERR_SIZE                     1
#define REG_MI_XDMA_FTM_DMAGO_ERR_MASK                     0x00000010

#define REG_MI_XDMA_FTM_OP_INVALID_SHIFT                   1
#define REG_MI_XDMA_FTM_OP_INVALID_SIZE                    1
#define REG_MI_XDMA_FTM_OP_INVALID_MASK                    0x00000002

#define REG_MI_XDMA_FTM_UNDEF_INST_SHIFT                   0
#define REG_MI_XDMA_FTM_UNDEF_INST_SIZE                    1
#define REG_MI_XDMA_FTM_UNDEF_INST_MASK                    0x00000001

#ifndef SDK_ASM
#define REG_MI_XDMA_FTM_FIELD( dbg_inst, fetch_err, event_err, dmago_err, op_invalid, undef_inst ) \
    (u32)( \
    ((u32)(dbg_inst) << REG_MI_XDMA_FTM_DBG_INST_SHIFT) | \
    ((u32)(fetch_err) << REG_MI_XDMA_FTM_FETCH_ERR_SHIFT) | \
    ((u32)(event_err) << REG_MI_XDMA_FTM_EVENT_ERR_SHIFT) | \
    ((u32)(dmago_err) << REG_MI_XDMA_FTM_DMAGO_ERR_SHIFT) | \
    ((u32)(op_invalid) << REG_MI_XDMA_FTM_OP_INVALID_SHIFT) | \
    ((u32)(undef_inst) << REG_MI_XDMA_FTM_UNDEF_INST_SHIFT))
#endif


/* XDMA_FTC0 */

#define REG_MI_XDMA_FTC0_LOCKUP_ERR_SHIFT                  31
#define REG_MI_XDMA_FTC0_LOCKUP_ERR_SIZE                   1
#define REG_MI_XDMA_FTC0_LOCKUP_ERR_MASK                   0x80000000

#define REG_MI_XDMA_FTC0_DBG_INST_SHIFT                    30
#define REG_MI_XDMA_FTC0_DBG_INST_SIZE                     1
#define REG_MI_XDMA_FTC0_DBG_INST_MASK                     0x40000000

#define REG_MI_XDMA_FTC0_READ_ERR_SHIFT                    18
#define REG_MI_XDMA_FTC0_READ_ERR_SIZE                     1
#define REG_MI_XDMA_FTC0_READ_ERR_MASK                     0x00040000

#define REG_MI_XDMA_FTC0_WRITE_ERR_SHIFT                   17
#define REG_MI_XDMA_FTC0_WRITE_ERR_SIZE                    1
#define REG_MI_XDMA_FTC0_WRITE_ERR_MASK                    0x00020000

#define REG_MI_XDMA_FTC0_FETCH_ERR_SHIFT                   16
#define REG_MI_XDMA_FTC0_FETCH_ERR_SIZE                    1
#define REG_MI_XDMA_FTC0_FETCH_ERR_MASK                    0x00010000

#define REG_MI_XDMA_FTC0_MFIFO_ERR_SHIFT                   12
#define REG_MI_XDMA_FTC0_MFIFO_ERR_SIZE                    1
#define REG_MI_XDMA_FTC0_MFIFO_ERR_MASK                    0x00001000

#define REG_MI_XDMA_FTC0_CH_RW_ERR_SHIFT                   7
#define REG_MI_XDMA_FTC0_CH_RW_ERR_SIZE                    1
#define REG_MI_XDMA_FTC0_CH_RW_ERR_MASK                    0x00000080

#define REG_MI_XDMA_FTC0_CH_PERIPH_ERR_SHIFT               6
#define REG_MI_XDMA_FTC0_CH_PERIPH_ERR_SIZE                1
#define REG_MI_XDMA_FTC0_CH_PERIPH_ERR_MASK                0x00000040

#define REG_MI_XDMA_FTC0_CH_EVENT_ERR_SHIFT                5
#define REG_MI_XDMA_FTC0_CH_EVENT_ERR_SIZE                 1
#define REG_MI_XDMA_FTC0_CH_EVENT_ERR_MASK                 0x00000020

#define REG_MI_XDMA_FTC0_OP_INVALID_SHIFT                  1
#define REG_MI_XDMA_FTC0_OP_INVALID_SIZE                   1
#define REG_MI_XDMA_FTC0_OP_INVALID_MASK                   0x00000002

#define REG_MI_XDMA_FTC0_UNDEF_INST_SHIFT                  0
#define REG_MI_XDMA_FTC0_UNDEF_INST_SIZE                   1
#define REG_MI_XDMA_FTC0_UNDEF_INST_MASK                   0x00000001

#ifndef SDK_ASM
#define REG_MI_XDMA_FTC0_FIELD( lockup_err, dbg_inst, read_err, write_err, fetch_err, mfifo_err, ch_rw_err, ch_periph_err, ch_event_err, op_invalid, undef_inst ) \
    (u32)( \
    ((u32)(lockup_err) << REG_MI_XDMA_FTC0_LOCKUP_ERR_SHIFT) | \
    ((u32)(dbg_inst) << REG_MI_XDMA_FTC0_DBG_INST_SHIFT) | \
    ((u32)(read_err) << REG_MI_XDMA_FTC0_READ_ERR_SHIFT) | \
    ((u32)(write_err) << REG_MI_XDMA_FTC0_WRITE_ERR_SHIFT) | \
    ((u32)(fetch_err) << REG_MI_XDMA_FTC0_FETCH_ERR_SHIFT) | \
    ((u32)(mfifo_err) << REG_MI_XDMA_FTC0_MFIFO_ERR_SHIFT) | \
    ((u32)(ch_rw_err) << REG_MI_XDMA_FTC0_CH_RW_ERR_SHIFT) | \
    ((u32)(ch_periph_err) << REG_MI_XDMA_FTC0_CH_PERIPH_ERR_SHIFT) | \
    ((u32)(ch_event_err) << REG_MI_XDMA_FTC0_CH_EVENT_ERR_SHIFT) | \
    ((u32)(op_invalid) << REG_MI_XDMA_FTC0_OP_INVALID_SHIFT) | \
    ((u32)(undef_inst) << REG_MI_XDMA_FTC0_UNDEF_INST_SHIFT))
#endif


/* XDMA_FTC1 */

/* XDMA_CS0 */

#define REG_MI_XDMA_CS0_CNS_SHIFT                          21
#define REG_MI_XDMA_CS0_CNS_SIZE                           1
#define REG_MI_XDMA_CS0_CNS_MASK                           0x00200000

#define REG_MI_XDMA_CS0_WFP_P_SHIFT                        15
#define REG_MI_XDMA_CS0_WFP_P_SIZE                         1
#define REG_MI_XDMA_CS0_WFP_P_MASK                         0x00008000

#define REG_MI_XDMA_CS0_WFP_B_SHIFT                        14
#define REG_MI_XDMA_CS0_WFP_B_SIZE                         1
#define REG_MI_XDMA_CS0_WFP_B_MASK                         0x00004000

#define REG_MI_XDMA_CS0_WAKE_NUM_SHIFT                     4
#define REG_MI_XDMA_CS0_WAKE_NUM_SIZE                      5
#define REG_MI_XDMA_CS0_WAKE_NUM_MASK                      0x000001f0

#define REG_MI_XDMA_CS0_CS_SHIFT                           0
#define REG_MI_XDMA_CS0_CS_SIZE                            4
#define REG_MI_XDMA_CS0_CS_MASK                            0x0000000f

#ifndef SDK_ASM
#define REG_MI_XDMA_CS0_FIELD( cns, wfp_p, wfp_b, wake_num, cs ) \
    (u32)( \
    ((u32)(cns) << REG_MI_XDMA_CS0_CNS_SHIFT) | \
    ((u32)(wfp_p) << REG_MI_XDMA_CS0_WFP_P_SHIFT) | \
    ((u32)(wfp_b) << REG_MI_XDMA_CS0_WFP_B_SHIFT) | \
    ((u32)(wake_num) << REG_MI_XDMA_CS0_WAKE_NUM_SHIFT) | \
    ((u32)(cs) << REG_MI_XDMA_CS0_CS_SHIFT))
#endif


/* XDMA_CPC0 */

/* XDMA_CS1 */

#define REG_MI_XDMA_CS1_CNS_SHIFT                          21
#define REG_MI_XDMA_CS1_CNS_SIZE                           1
#define REG_MI_XDMA_CS1_CNS_MASK                           0x00200000

#define REG_MI_XDMA_CS1_WFP_P_SHIFT                        15
#define REG_MI_XDMA_CS1_WFP_P_SIZE                         1
#define REG_MI_XDMA_CS1_WFP_P_MASK                         0x00008000

#define REG_MI_XDMA_CS1_WFP_B_SHIFT                        14
#define REG_MI_XDMA_CS1_WFP_B_SIZE                         1
#define REG_MI_XDMA_CS1_WFP_B_MASK                         0x00004000

#define REG_MI_XDMA_CS1_WAKE_NUM_SHIFT                     4
#define REG_MI_XDMA_CS1_WAKE_NUM_SIZE                      5
#define REG_MI_XDMA_CS1_WAKE_NUM_MASK                      0x000001f0

#define REG_MI_XDMA_CS1_CS_SHIFT                           0
#define REG_MI_XDMA_CS1_CS_SIZE                            4
#define REG_MI_XDMA_CS1_CS_MASK                            0x0000000f

#ifndef SDK_ASM
#define REG_MI_XDMA_CS1_FIELD( cns, wfp_p, wfp_b, wake_num, cs ) \
    (u32)( \
    ((u32)(cns) << REG_MI_XDMA_CS1_CNS_SHIFT) | \
    ((u32)(wfp_p) << REG_MI_XDMA_CS1_WFP_P_SHIFT) | \
    ((u32)(wfp_b) << REG_MI_XDMA_CS1_WFP_B_SHIFT) | \
    ((u32)(wake_num) << REG_MI_XDMA_CS1_WAKE_NUM_SHIFT) | \
    ((u32)(cs) << REG_MI_XDMA_CS1_CS_SHIFT))
#endif


/* XDMA_CPC1 */

/* XDMA_SA0 */

/* XDMA_DA0 */

/* XDMA_CC0 */

#define REG_MI_XDMA_CC0_SWP_SZ_SHIFT                       28
#define REG_MI_XDMA_CC0_SWP_SZ_SIZE                        3
#define REG_MI_XDMA_CC0_SWP_SZ_MASK                        0x70000000

#define REG_MI_XDMA_CC0_DCACHE_SHIFT                       25
#define REG_MI_XDMA_CC0_DCACHE_SIZE                        3
#define REG_MI_XDMA_CC0_DCACHE_MASK                        0x0e000000

#define REG_MI_XDMA_CC0_DPROT_SHIFT                        22
#define REG_MI_XDMA_CC0_DPROT_SIZE                         3
#define REG_MI_XDMA_CC0_DPROT_MASK                         0x01c00000

#define REG_MI_XDMA_CC0_DBST_LEN_SHIFT                     18
#define REG_MI_XDMA_CC0_DBST_LEN_SIZE                      4
#define REG_MI_XDMA_CC0_DBST_LEN_MASK                      0x003c0000

#define REG_MI_XDMA_CC0_DBST_SZ_SHIFT                      15
#define REG_MI_XDMA_CC0_DBST_SZ_SIZE                       3
#define REG_MI_XDMA_CC0_DBST_SZ_MASK                       0x00038000

#define REG_MI_XDMA_CC0_DINC_SHIFT                         14
#define REG_MI_XDMA_CC0_DINC_SIZE                          1
#define REG_MI_XDMA_CC0_DINC_MASK                          0x00004000

#define REG_MI_XDMA_CC0_SCACHE_SHIFT                       11
#define REG_MI_XDMA_CC0_SCACHE_SIZE                        3
#define REG_MI_XDMA_CC0_SCACHE_MASK                        0x00003800

#define REG_MI_XDMA_CC0_SPROT_SHIFT                        8
#define REG_MI_XDMA_CC0_SPROT_SIZE                         3
#define REG_MI_XDMA_CC0_SPROT_MASK                         0x00000700

#define REG_MI_XDMA_CC0_SBST_LEN_SHIFT                     4
#define REG_MI_XDMA_CC0_SBST_LEN_SIZE                      4
#define REG_MI_XDMA_CC0_SBST_LEN_MASK                      0x000000f0

#define REG_MI_XDMA_CC0_SBST_SZ_SHIFT                      1
#define REG_MI_XDMA_CC0_SBST_SZ_SIZE                       3
#define REG_MI_XDMA_CC0_SBST_SZ_MASK                       0x0000000e

#define REG_MI_XDMA_CC0_SINC_SHIFT                         0
#define REG_MI_XDMA_CC0_SINC_SIZE                          1
#define REG_MI_XDMA_CC0_SINC_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_MI_XDMA_CC0_FIELD( swp_sz, dcache, dprot, dbst_len, dbst_sz, dinc, scache, sprot, sbst_len, sbst_sz, sinc ) \
    (u32)( \
    ((u32)(swp_sz) << REG_MI_XDMA_CC0_SWP_SZ_SHIFT) | \
    ((u32)(dcache) << REG_MI_XDMA_CC0_DCACHE_SHIFT) | \
    ((u32)(dprot) << REG_MI_XDMA_CC0_DPROT_SHIFT) | \
    ((u32)(dbst_len) << REG_MI_XDMA_CC0_DBST_LEN_SHIFT) | \
    ((u32)(dbst_sz) << REG_MI_XDMA_CC0_DBST_SZ_SHIFT) | \
    ((u32)(dinc) << REG_MI_XDMA_CC0_DINC_SHIFT) | \
    ((u32)(scache) << REG_MI_XDMA_CC0_SCACHE_SHIFT) | \
    ((u32)(sprot) << REG_MI_XDMA_CC0_SPROT_SHIFT) | \
    ((u32)(sbst_len) << REG_MI_XDMA_CC0_SBST_LEN_SHIFT) | \
    ((u32)(sbst_sz) << REG_MI_XDMA_CC0_SBST_SZ_SHIFT) | \
    ((u32)(sinc) << REG_MI_XDMA_CC0_SINC_SHIFT))
#endif


/* XDMA_LC00 */

/* XDMA_LC10 */

/* XDMA_SA1 */

/* XDMA_DA1 */

/* XDMA_CC1 */

#define REG_MI_XDMA_CC1_SWP_SZ_SHIFT                       28
#define REG_MI_XDMA_CC1_SWP_SZ_SIZE                        3
#define REG_MI_XDMA_CC1_SWP_SZ_MASK                        0x70000000

#define REG_MI_XDMA_CC1_DCACHE_SHIFT                       25
#define REG_MI_XDMA_CC1_DCACHE_SIZE                        3
#define REG_MI_XDMA_CC1_DCACHE_MASK                        0x0e000000

#define REG_MI_XDMA_CC1_DPROT_SHIFT                        22
#define REG_MI_XDMA_CC1_DPROT_SIZE                         3
#define REG_MI_XDMA_CC1_DPROT_MASK                         0x01c00000

#define REG_MI_XDMA_CC1_DBST_LEN_SHIFT                     18
#define REG_MI_XDMA_CC1_DBST_LEN_SIZE                      4
#define REG_MI_XDMA_CC1_DBST_LEN_MASK                      0x003c0000

#define REG_MI_XDMA_CC1_DBST_SZ_SHIFT                      15
#define REG_MI_XDMA_CC1_DBST_SZ_SIZE                       3
#define REG_MI_XDMA_CC1_DBST_SZ_MASK                       0x00038000

#define REG_MI_XDMA_CC1_DINC_SHIFT                         14
#define REG_MI_XDMA_CC1_DINC_SIZE                          1
#define REG_MI_XDMA_CC1_DINC_MASK                          0x00004000

#define REG_MI_XDMA_CC1_SCACHE_SHIFT                       11
#define REG_MI_XDMA_CC1_SCACHE_SIZE                        3
#define REG_MI_XDMA_CC1_SCACHE_MASK                        0x00003800

#define REG_MI_XDMA_CC1_SPROT_SHIFT                        8
#define REG_MI_XDMA_CC1_SPROT_SIZE                         3
#define REG_MI_XDMA_CC1_SPROT_MASK                         0x00000700

#define REG_MI_XDMA_CC1_SBST_LEN_SHIFT                     4
#define REG_MI_XDMA_CC1_SBST_LEN_SIZE                      4
#define REG_MI_XDMA_CC1_SBST_LEN_MASK                      0x000000f0

#define REG_MI_XDMA_CC1_SBST_SZ_SHIFT                      1
#define REG_MI_XDMA_CC1_SBST_SZ_SIZE                       3
#define REG_MI_XDMA_CC1_SBST_SZ_MASK                       0x0000000e

#define REG_MI_XDMA_CC1_SINC_SHIFT                         0
#define REG_MI_XDMA_CC1_SINC_SIZE                          1
#define REG_MI_XDMA_CC1_SINC_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_MI_XDMA_CC1_FIELD( swp_sz, dcache, dprot, dbst_len, dbst_sz, dinc, scache, sprot, sbst_len, sbst_sz, sinc ) \
    (u32)( \
    ((u32)(swp_sz) << REG_MI_XDMA_CC1_SWP_SZ_SHIFT) | \
    ((u32)(dcache) << REG_MI_XDMA_CC1_DCACHE_SHIFT) | \
    ((u32)(dprot) << REG_MI_XDMA_CC1_DPROT_SHIFT) | \
    ((u32)(dbst_len) << REG_MI_XDMA_CC1_DBST_LEN_SHIFT) | \
    ((u32)(dbst_sz) << REG_MI_XDMA_CC1_DBST_SZ_SHIFT) | \
    ((u32)(dinc) << REG_MI_XDMA_CC1_DINC_SHIFT) | \
    ((u32)(scache) << REG_MI_XDMA_CC1_SCACHE_SHIFT) | \
    ((u32)(sprot) << REG_MI_XDMA_CC1_SPROT_SHIFT) | \
    ((u32)(sbst_len) << REG_MI_XDMA_CC1_SBST_LEN_SHIFT) | \
    ((u32)(sbst_sz) << REG_MI_XDMA_CC1_SBST_SZ_SHIFT) | \
    ((u32)(sinc) << REG_MI_XDMA_CC1_SINC_SHIFT))
#endif


/* XDMA_LC01 */

/* XDMA_LC11 */

/* XDMA_DBGSTAT */

#define REG_MI_XDMA_DBGSTAT_BUSY_SHIFT                     0
#define REG_MI_XDMA_DBGSTAT_BUSY_SIZE                      1
#define REG_MI_XDMA_DBGSTAT_BUSY_MASK                      0x00000001

#ifndef SDK_ASM
#define REG_MI_XDMA_DBGSTAT_FIELD( busy ) \
    (u32)( \
    ((u32)(busy) << REG_MI_XDMA_DBGSTAT_BUSY_SHIFT))
#endif


/* XDMA_DBGCMD */

#define REG_MI_XDMA_DBGCMD_CMD_SHIFT                       0
#define REG_MI_XDMA_DBGCMD_CMD_SIZE                        2
#define REG_MI_XDMA_DBGCMD_CMD_MASK                        0x00000003

#ifndef SDK_ASM
#define REG_MI_XDMA_DBGCMD_FIELD( cmd ) \
    (u32)( \
    ((u32)(cmd) << REG_MI_XDMA_DBGCMD_CMD_SHIFT))
#endif


/* XDMA_DBGINST0 */

#define REG_MI_XDMA_DBGINST0_INST1_SHIFT                   24
#define REG_MI_XDMA_DBGINST0_INST1_SIZE                    8
#define REG_MI_XDMA_DBGINST0_INST1_MASK                    0xff000000

#define REG_MI_XDMA_DBGINST0_INST0_SHIFT                   16
#define REG_MI_XDMA_DBGINST0_INST0_SIZE                    8
#define REG_MI_XDMA_DBGINST0_INST0_MASK                    0x00ff0000

#define REG_MI_XDMA_DBGINST0_CH_SHIFT                      8
#define REG_MI_XDMA_DBGINST0_CH_SIZE                       3
#define REG_MI_XDMA_DBGINST0_CH_MASK                       0x00000700

#define REG_MI_XDMA_DBGINST0_DBG_TH_SHIFT                  0
#define REG_MI_XDMA_DBGINST0_DBG_TH_SIZE                   1
#define REG_MI_XDMA_DBGINST0_DBG_TH_MASK                   0x00000001

#ifndef SDK_ASM
#define REG_MI_XDMA_DBGINST0_FIELD( inst1, inst0, ch, dbg_th ) \
    (u32)( \
    ((u32)(inst1) << REG_MI_XDMA_DBGINST0_INST1_SHIFT) | \
    ((u32)(inst0) << REG_MI_XDMA_DBGINST0_INST0_SHIFT) | \
    ((u32)(ch) << REG_MI_XDMA_DBGINST0_CH_SHIFT) | \
    ((u32)(dbg_th) << REG_MI_XDMA_DBGINST0_DBG_TH_SHIFT))
#endif


/* XDMA_DBGINST1 */

#define REG_MI_XDMA_DBGINST1_INST5_SHIFT                   24
#define REG_MI_XDMA_DBGINST1_INST5_SIZE                    8
#define REG_MI_XDMA_DBGINST1_INST5_MASK                    0xff000000

#define REG_MI_XDMA_DBGINST1_INST4_SHIFT                   16
#define REG_MI_XDMA_DBGINST1_INST4_SIZE                    8
#define REG_MI_XDMA_DBGINST1_INST4_MASK                    0x00ff0000

#define REG_MI_XDMA_DBGINST1_INST3_SHIFT                   8
#define REG_MI_XDMA_DBGINST1_INST3_SIZE                    8
#define REG_MI_XDMA_DBGINST1_INST3_MASK                    0x0000ff00

#define REG_MI_XDMA_DBGINST1_INST2_SHIFT                   0
#define REG_MI_XDMA_DBGINST1_INST2_SIZE                    8
#define REG_MI_XDMA_DBGINST1_INST2_MASK                    0x000000ff

#ifndef SDK_ASM
#define REG_MI_XDMA_DBGINST1_FIELD( inst5, inst4, inst3, inst2 ) \
    (u32)( \
    ((u32)(inst5) << REG_MI_XDMA_DBGINST1_INST5_SHIFT) | \
    ((u32)(inst4) << REG_MI_XDMA_DBGINST1_INST4_SHIFT) | \
    ((u32)(inst3) << REG_MI_XDMA_DBGINST1_INST3_SHIFT) | \
    ((u32)(inst2) << REG_MI_XDMA_DBGINST1_INST2_SHIFT))
#endif


/* XDMA_CFG0 */

#define REG_MI_XDMA_CFG0_NUM_EV_SHIFT                      17
#define REG_MI_XDMA_CFG0_NUM_EV_SIZE                       5
#define REG_MI_XDMA_CFG0_NUM_EV_MASK                       0x003e0000

#define REG_MI_XDMA_CFG0_NUM_PRH_SHIFT                     12
#define REG_MI_XDMA_CFG0_NUM_PRH_SIZE                      5
#define REG_MI_XDMA_CFG0_NUM_PRH_MASK                      0x0001f000

#define REG_MI_XDMA_CFG0_NUM_CH_SHIFT                      4
#define REG_MI_XDMA_CFG0_NUM_CH_SIZE                       3
#define REG_MI_XDMA_CFG0_NUM_CH_MASK                       0x00000070

#define REG_MI_XDMA_CFG0_RST_NS_SHIFT                      2
#define REG_MI_XDMA_CFG0_RST_NS_SIZE                       1
#define REG_MI_XDMA_CFG0_RST_NS_MASK                       0x00000004

#define REG_MI_XDMA_CFG0_BOOT_E_SHIFT                      1
#define REG_MI_XDMA_CFG0_BOOT_E_SIZE                       1
#define REG_MI_XDMA_CFG0_BOOT_E_MASK                       0x00000002

#define REG_MI_XDMA_CFG0_PRH_REQ_SHIFT                     0
#define REG_MI_XDMA_CFG0_PRH_REQ_SIZE                      1
#define REG_MI_XDMA_CFG0_PRH_REQ_MASK                      0x00000001

#ifndef SDK_ASM
#define REG_MI_XDMA_CFG0_FIELD( num_ev, num_prh, num_ch, rst_ns, boot_e, prh_req ) \
    (u32)( \
    ((u32)(num_ev) << REG_MI_XDMA_CFG0_NUM_EV_SHIFT) | \
    ((u32)(num_prh) << REG_MI_XDMA_CFG0_NUM_PRH_SHIFT) | \
    ((u32)(num_ch) << REG_MI_XDMA_CFG0_NUM_CH_SHIFT) | \
    ((u32)(rst_ns) << REG_MI_XDMA_CFG0_RST_NS_SHIFT) | \
    ((u32)(boot_e) << REG_MI_XDMA_CFG0_BOOT_E_SHIFT) | \
    ((u32)(prh_req) << REG_MI_XDMA_CFG0_PRH_REQ_SHIFT))
#endif


/* XDMA_CFG1 */

#define REG_MI_XDMA_CFG1_IC_LINES_SHIFT                    4
#define REG_MI_XDMA_CFG1_IC_LINES_SIZE                     3
#define REG_MI_XDMA_CFG1_IC_LINES_MASK                     0x00000070

#define REG_MI_XDMA_CFG1_IC_LEN_SHIFT                      0
#define REG_MI_XDMA_CFG1_IC_LEN_SIZE                       3
#define REG_MI_XDMA_CFG1_IC_LEN_MASK                       0x00000007

#ifndef SDK_ASM
#define REG_MI_XDMA_CFG1_FIELD( ic_lines, ic_len ) \
    (u32)( \
    ((u32)(ic_lines) << REG_MI_XDMA_CFG1_IC_LINES_SHIFT) | \
    ((u32)(ic_len) << REG_MI_XDMA_CFG1_IC_LEN_SHIFT))
#endif


/* XDMA_CFG2 */

#define REG_MI_XDMA_CFG2_BOOT_ADR_SHIFT                    0
#define REG_MI_XDMA_CFG2_BOOT_ADR_SIZE                     32
#define REG_MI_XDMA_CFG2_BOOT_ADR_MASK                     0xffffffff

#ifndef SDK_ASM
#define REG_MI_XDMA_CFG2_FIELD( boot_adr ) \
    (u32)( \
    ((u32)(boot_adr) << REG_MI_XDMA_CFG2_BOOT_ADR_SHIFT))
#endif


/* XDMA_CFG3 */

#define REG_MI_XDMA_CFG3_INS0_SHIFT                        0
#define REG_MI_XDMA_CFG3_INS0_SIZE                         1
#define REG_MI_XDMA_CFG3_INS0_MASK                         0x00000001

#ifndef SDK_ASM
#define REG_MI_XDMA_CFG3_FIELD( ins0 ) \
    (u32)( \
    ((u32)(ins0) << REG_MI_XDMA_CFG3_INS0_SHIFT))
#endif


/* XDMA_CFG4 */

#define REG_MI_XDMA_CFG4_PNS0_SHIFT                        0
#define REG_MI_XDMA_CFG4_PNS0_SIZE                         1
#define REG_MI_XDMA_CFG4_PNS0_MASK                         0x00000001

#ifndef SDK_ASM
#define REG_MI_XDMA_CFG4_FIELD( pns0 ) \
    (u32)( \
    ((u32)(pns0) << REG_MI_XDMA_CFG4_PNS0_SHIFT))
#endif


/* XDMA_CFGDN */

#define REG_MI_XDMA_CFGDN_DBF_LINES_SHIFT                  20
#define REG_MI_XDMA_CFGDN_DBF_LINES_SIZE                   10
#define REG_MI_XDMA_CFGDN_DBF_LINES_MASK                   0x3ff00000

#define REG_MI_XDMA_CFGDN_RQ_LINES_SHIFT                   16
#define REG_MI_XDMA_CFGDN_RQ_LINES_SIZE                    4
#define REG_MI_XDMA_CFGDN_RQ_LINES_MASK                    0x000f0000

#define REG_MI_XDMA_CFGDN_R_CAP_SHIFT                      12
#define REG_MI_XDMA_CFGDN_R_CAP_SIZE                       3
#define REG_MI_XDMA_CFGDN_R_CAP_MASK                       0x00007000

#define REG_MI_XDMA_CFGDN_WQ_LINES_SHIFT                   8
#define REG_MI_XDMA_CFGDN_WQ_LINES_SIZE                    4
#define REG_MI_XDMA_CFGDN_WQ_LINES_MASK                    0x00000f00

#define REG_MI_XDMA_CFGDN_W_CAP_SHIFT                      4
#define REG_MI_XDMA_CFGDN_W_CAP_SIZE                       3
#define REG_MI_XDMA_CFGDN_W_CAP_MASK                       0x00000070

#define REG_MI_XDMA_CFGDN_AXI_WDH_SHIFT                    0
#define REG_MI_XDMA_CFGDN_AXI_WDH_SIZE                     3
#define REG_MI_XDMA_CFGDN_AXI_WDH_MASK                     0x00000007

#ifndef SDK_ASM
#define REG_MI_XDMA_CFGDN_FIELD( dbf_lines, rq_lines, r_cap, wq_lines, w_cap, axi_wdh ) \
    (u32)( \
    ((u32)(dbf_lines) << REG_MI_XDMA_CFGDN_DBF_LINES_SHIFT) | \
    ((u32)(rq_lines) << REG_MI_XDMA_CFGDN_RQ_LINES_SHIFT) | \
    ((u32)(r_cap) << REG_MI_XDMA_CFGDN_R_CAP_SHIFT) | \
    ((u32)(wq_lines) << REG_MI_XDMA_CFGDN_WQ_LINES_SHIFT) | \
    ((u32)(w_cap) << REG_MI_XDMA_CFGDN_W_CAP_SHIFT) | \
    ((u32)(axi_wdh) << REG_MI_XDMA_CFGDN_AXI_WDH_SHIFT))
#endif


/* MCCNT0 */

#define REG_MI_MCCNT0_E_SHIFT                              15
#define REG_MI_MCCNT0_E_SIZE                               1
#define REG_MI_MCCNT0_E_MASK                               0x8000

#define REG_MI_MCCNT0_I_SHIFT                              14
#define REG_MI_MCCNT0_I_SIZE                               1
#define REG_MI_MCCNT0_I_MASK                               0x4000

#define REG_MI_MCCNT0_SEL_SHIFT                            13
#define REG_MI_MCCNT0_SEL_SIZE                             1
#define REG_MI_MCCNT0_SEL_MASK                             0x2000

#define REG_MI_MCCNT0_BUSY_SHIFT                           7
#define REG_MI_MCCNT0_BUSY_SIZE                            1
#define REG_MI_MCCNT0_BUSY_MASK                            0x0080

#define REG_MI_MCCNT0_MODE_SHIFT                           6
#define REG_MI_MCCNT0_MODE_SIZE                            1
#define REG_MI_MCCNT0_MODE_MASK                            0x0040

#define REG_MI_MCCNT0_BAUDRATE_SHIFT                       0
#define REG_MI_MCCNT0_BAUDRATE_SIZE                        2
#define REG_MI_MCCNT0_BAUDRATE_MASK                        0x0003

#ifndef SDK_ASM
#define REG_MI_MCCNT0_FIELD( e, i, sel, busy, mode, baudrate ) \
    (u16)( \
    ((u32)(e) << REG_MI_MCCNT0_E_SHIFT) | \
    ((u32)(i) << REG_MI_MCCNT0_I_SHIFT) | \
    ((u32)(sel) << REG_MI_MCCNT0_SEL_SHIFT) | \
    ((u32)(busy) << REG_MI_MCCNT0_BUSY_SHIFT) | \
    ((u32)(mode) << REG_MI_MCCNT0_MODE_SHIFT) | \
    ((u32)(baudrate) << REG_MI_MCCNT0_BAUDRATE_SHIFT))
#endif


/* MCD0 */

#define REG_MI_MCD0_DATA_SHIFT                             0
#define REG_MI_MCD0_DATA_SIZE                              8
#define REG_MI_MCD0_DATA_MASK                              0x00ff

#ifndef SDK_ASM
#define REG_MI_MCD0_FIELD( data ) \
    (u16)( \
    ((u32)(data) << REG_MI_MCD0_DATA_SHIFT))
#endif


/* MCCNT1 */

#define REG_MI_MCCNT1_START_SHIFT                          31
#define REG_MI_MCCNT1_START_SIZE                           1
#define REG_MI_MCCNT1_START_MASK                           0x80000000

#define REG_MI_MCCNT1_WR_SHIFT                             30
#define REG_MI_MCCNT1_WR_SIZE                              1
#define REG_MI_MCCNT1_WR_MASK                              0x40000000

#define REG_MI_MCCNT1_RESB_SHIFT                           29
#define REG_MI_MCCNT1_RESB_SIZE                            1
#define REG_MI_MCCNT1_RESB_MASK                            0x20000000

#define REG_MI_MCCNT1_TRM_SHIFT                            28
#define REG_MI_MCCNT1_TRM_SIZE                             1
#define REG_MI_MCCNT1_TRM_MASK                             0x10000000

#define REG_MI_MCCNT1_CT_SHIFT                             27
#define REG_MI_MCCNT1_CT_SIZE                              1
#define REG_MI_MCCNT1_CT_MASK                              0x08000000

#define REG_MI_MCCNT1_PC_SHIFT                             24
#define REG_MI_MCCNT1_PC_SIZE                              3
#define REG_MI_MCCNT1_PC_MASK                              0x07000000

#define REG_MI_MCCNT1_RDY_SHIFT                            23
#define REG_MI_MCCNT1_RDY_SIZE                             1
#define REG_MI_MCCNT1_RDY_MASK                             0x00800000

#define REG_MI_MCCNT1_CS_SHIFT                             22
#define REG_MI_MCCNT1_CS_SIZE                              1
#define REG_MI_MCCNT1_CS_MASK                              0x00400000

#define REG_MI_MCCNT1_L2_SHIFT                             16
#define REG_MI_MCCNT1_L2_SIZE                              6
#define REG_MI_MCCNT1_L2_MASK                              0x003f0000

#define REG_MI_MCCNT1_SCR_SHIFT                            15
#define REG_MI_MCCNT1_SCR_SIZE                             1
#define REG_MI_MCCNT1_SCR_MASK                             0x00008000

#define REG_MI_MCCNT1_SE_SHIFT                             14
#define REG_MI_MCCNT1_SE_SIZE                              1
#define REG_MI_MCCNT1_SE_MASK                              0x00004000

#define REG_MI_MCCNT1_DS_SHIFT                             13
#define REG_MI_MCCNT1_DS_SIZE                              1
#define REG_MI_MCCNT1_DS_MASK                              0x00002000

#define REG_MI_MCCNT1_L1_SHIFT                             0
#define REG_MI_MCCNT1_L1_SIZE                              13
#define REG_MI_MCCNT1_L1_MASK                              0x00001fff

#ifndef SDK_ASM
#define REG_MI_MCCNT1_FIELD( start, wr, resb, trm, ct, pc, rdy, cs, l2, scr, se, ds, l1 ) \
    (u32)( \
    ((u32)(start) << REG_MI_MCCNT1_START_SHIFT) | \
    ((u32)(wr) << REG_MI_MCCNT1_WR_SHIFT) | \
    ((u32)(resb) << REG_MI_MCCNT1_RESB_SHIFT) | \
    ((u32)(trm) << REG_MI_MCCNT1_TRM_SHIFT) | \
    ((u32)(ct) << REG_MI_MCCNT1_CT_SHIFT) | \
    ((u32)(pc) << REG_MI_MCCNT1_PC_SHIFT) | \
    ((u32)(rdy) << REG_MI_MCCNT1_RDY_SHIFT) | \
    ((u32)(cs) << REG_MI_MCCNT1_CS_SHIFT) | \
    ((u32)(l2) << REG_MI_MCCNT1_L2_SHIFT) | \
    ((u32)(scr) << REG_MI_MCCNT1_SCR_SHIFT) | \
    ((u32)(se) << REG_MI_MCCNT1_SE_SHIFT) | \
    ((u32)(ds) << REG_MI_MCCNT1_DS_SHIFT) | \
    ((u32)(l1) << REG_MI_MCCNT1_L1_SHIFT))
#endif


/* MCCMD0 */

#define REG_MI_MCCMD0_CMD3_SHIFT                           24
#define REG_MI_MCCMD0_CMD3_SIZE                            8
#define REG_MI_MCCMD0_CMD3_MASK                            0xff000000

#define REG_MI_MCCMD0_CMD2_SHIFT                           16
#define REG_MI_MCCMD0_CMD2_SIZE                            8
#define REG_MI_MCCMD0_CMD2_MASK                            0x00ff0000

#define REG_MI_MCCMD0_CMD1_SHIFT                           8
#define REG_MI_MCCMD0_CMD1_SIZE                            8
#define REG_MI_MCCMD0_CMD1_MASK                            0x0000ff00

#define REG_MI_MCCMD0_CMD0_SHIFT                           0
#define REG_MI_MCCMD0_CMD0_SIZE                            8
#define REG_MI_MCCMD0_CMD0_MASK                            0x000000ff

#ifndef SDK_ASM
#define REG_MI_MCCMD0_FIELD( cmd3, cmd2, cmd1, cmd0 ) \
    (u32)( \
    ((u32)(cmd3) << REG_MI_MCCMD0_CMD3_SHIFT) | \
    ((u32)(cmd2) << REG_MI_MCCMD0_CMD2_SHIFT) | \
    ((u32)(cmd1) << REG_MI_MCCMD0_CMD1_SHIFT) | \
    ((u32)(cmd0) << REG_MI_MCCMD0_CMD0_SHIFT))
#endif


/* MCCMD1 */

#define REG_MI_MCCMD1_CMD7_SHIFT                           24
#define REG_MI_MCCMD1_CMD7_SIZE                            8
#define REG_MI_MCCMD1_CMD7_MASK                            0xff000000

#define REG_MI_MCCMD1_CMD6_SHIFT                           16
#define REG_MI_MCCMD1_CMD6_SIZE                            8
#define REG_MI_MCCMD1_CMD6_MASK                            0x00ff0000

#define REG_MI_MCCMD1_CMD5_SHIFT                           8
#define REG_MI_MCCMD1_CMD5_SIZE                            8
#define REG_MI_MCCMD1_CMD5_MASK                            0x0000ff00

#define REG_MI_MCCMD1_CMD4_SHIFT                           0
#define REG_MI_MCCMD1_CMD4_SIZE                            8
#define REG_MI_MCCMD1_CMD4_MASK                            0x000000ff

#ifndef SDK_ASM
#define REG_MI_MCCMD1_FIELD( cmd7, cmd6, cmd5, cmd4 ) \
    (u32)( \
    ((u32)(cmd7) << REG_MI_MCCMD1_CMD7_SHIFT) | \
    ((u32)(cmd6) << REG_MI_MCCMD1_CMD6_SHIFT) | \
    ((u32)(cmd5) << REG_MI_MCCMD1_CMD5_SHIFT) | \
    ((u32)(cmd4) << REG_MI_MCCMD1_CMD4_SHIFT))
#endif


/* MCSCRA_L */

/* MCSCRB_L */

/* MCSCRA_H */

/* MCSCRB_H */

/* MCD1 */

/* CGC_NSPI_CNT1 */

#define REG_MI_CGC_NSPI_CNT1_TS_SHIFT                      15
#define REG_MI_CGC_NSPI_CNT1_TS_SIZE                       1
#define REG_MI_CGC_NSPI_CNT1_TS_MASK                       0x00008000

#define REG_MI_CGC_NSPI_CNT1_RW_SHIFT                      13
#define REG_MI_CGC_NSPI_CNT1_RW_SIZE                       1
#define REG_MI_CGC_NSPI_CNT1_RW_MASK                       0x00002000

#define REG_MI_CGC_NSPI_CNT1_SB_SHIFT                      12
#define REG_MI_CGC_NSPI_CNT1_SB_SIZE                       1
#define REG_MI_CGC_NSPI_CNT1_SB_MASK                       0x00001000

#define REG_MI_CGC_NSPI_CNT1_SC_SHIFT                      6
#define REG_MI_CGC_NSPI_CNT1_SC_SIZE                       2
#define REG_MI_CGC_NSPI_CNT1_SC_MASK                       0x000000c0

#define REG_MI_CGC_NSPI_CNT1_SR_SHIFT                      0
#define REG_MI_CGC_NSPI_CNT1_SR_SIZE                       3
#define REG_MI_CGC_NSPI_CNT1_SR_MASK                       0x00000007

#ifndef SDK_ASM
#define REG_MI_CGC_NSPI_CNT1_FIELD( ts, rw, sb, sc, sr ) \
    (u32)( \
    ((u32)(ts) << REG_MI_CGC_NSPI_CNT1_TS_SHIFT) | \
    ((u32)(rw) << REG_MI_CGC_NSPI_CNT1_RW_SHIFT) | \
    ((u32)(sb) << REG_MI_CGC_NSPI_CNT1_SB_SHIFT) | \
    ((u32)(sc) << REG_MI_CGC_NSPI_CNT1_SC_SHIFT) | \
    ((u32)(sr) << REG_MI_CGC_NSPI_CNT1_SR_SHIFT))
#endif


/* CGC_NSPI_CNT2 */

#define REG_MI_CGC_NSPI_CNT2_CC_SHIFT                      0
#define REG_MI_CGC_NSPI_CNT2_CC_SIZE                       1
#define REG_MI_CGC_NSPI_CNT2_CC_MASK                       0x00000001

#ifndef SDK_ASM
#define REG_MI_CGC_NSPI_CNT2_FIELD( cc ) \
    (u32)( \
    ((u32)(cc) << REG_MI_CGC_NSPI_CNT2_CC_SHIFT))
#endif


/* CGC_NSPI_CNT3 */

#define REG_MI_CGC_NSPI_CNT3_TN_SHIFT                      0
#define REG_MI_CGC_NSPI_CNT3_TN_SIZE                       21
#define REG_MI_CGC_NSPI_CNT3_TN_MASK                       0x001fffff

#ifndef SDK_ASM
#define REG_MI_CGC_NSPI_CNT3_FIELD( tn ) \
    (u32)( \
    ((u32)(tn) << REG_MI_CGC_NSPI_CNT3_TN_SHIFT))
#endif


/* CGC_NSPI_DATA */

/* CGC_NSPI_DTST */

#define REG_MI_CGC_NSPI_DTST_RDY_SHIFT                     0
#define REG_MI_CGC_NSPI_DTST_RDY_SIZE                      1
#define REG_MI_CGC_NSPI_DTST_RDY_MASK                      0x00000001

#ifndef SDK_ASM
#define REG_MI_CGC_NSPI_DTST_FIELD( rdy ) \
    (u32)( \
    ((u32)(rdy) << REG_MI_CGC_NSPI_DTST_RDY_SHIFT))
#endif


/* CGC_NSPI_AP */

#define REG_MI_CGC_NSPI_AP_CMD_SHIFT                       0
#define REG_MI_CGC_NSPI_AP_CMD_SIZE                        8
#define REG_MI_CGC_NSPI_AP_CMD_MASK                        0x000000ff

#define REG_MI_CGC_NSPI_AP_TO_SHIFT                        16
#define REG_MI_CGC_NSPI_AP_TO_SIZE                         4
#define REG_MI_CGC_NSPI_AP_TO_MASK                         0x000f0000

#define REG_MI_CGC_NSPI_AP_RP_SHIFT                        24
#define REG_MI_CGC_NSPI_AP_RP_SIZE                         3
#define REG_MI_CGC_NSPI_AP_RP_MASK                         0x07000000

#define REG_MI_CGC_NSPI_AP_RBL_SHIFT                       30
#define REG_MI_CGC_NSPI_AP_RBL_SIZE                        1
#define REG_MI_CGC_NSPI_AP_RBL_MASK                        0x40000000

#define REG_MI_CGC_NSPI_AP_ST_SHIFT                        31
#define REG_MI_CGC_NSPI_AP_ST_SIZE                         1
#define REG_MI_CGC_NSPI_AP_ST_MASK                         0x80000000

#ifndef SDK_ASM
#define REG_MI_CGC_NSPI_AP_FIELD( cmd, to, rp, rbl, st ) \
    (u32)( \
    ((u32)(cmd) << REG_MI_CGC_NSPI_AP_CMD_SHIFT) | \
    ((u32)(to) << REG_MI_CGC_NSPI_AP_TO_SHIFT) | \
    ((u32)(rp) << REG_MI_CGC_NSPI_AP_RP_SHIFT) | \
    ((u32)(rbl) << REG_MI_CGC_NSPI_AP_RBL_SHIFT) | \
    ((u32)(st) << REG_MI_CGC_NSPI_AP_ST_SHIFT))
#endif


/* CGC_NSPI_INT */

#define REG_MI_CGC_NSPI_INT_MASK_SHIFT                     0
#define REG_MI_CGC_NSPI_INT_MASK_SIZE                      3
#define REG_MI_CGC_NSPI_INT_MASK_MASK                      0x00000007

#define REG_MI_CGC_NSPI_INT_REQ_SHIFT                      3
#define REG_MI_CGC_NSPI_INT_REQ_SIZE                       1
#define REG_MI_CGC_NSPI_INT_REQ_MASK                       0x00000008

#ifndef SDK_ASM
#define REG_MI_CGC_NSPI_INT_FIELD( mask, req ) \
    (u32)( \
    ((u32)(mask) << REG_MI_CGC_NSPI_INT_MASK_SHIFT) | \
    ((u32)(req) << REG_MI_CGC_NSPI_INT_REQ_SHIFT))
#endif


/* CGC_NSPI_INTC */

#define REG_MI_CGC_NSPI_INTC_CAUSE_SHIFT                   0
#define REG_MI_CGC_NSPI_INTC_CAUSE_SIZE                    3
#define REG_MI_CGC_NSPI_INTC_CAUSE_MASK                    0x00000007

#ifndef SDK_ASM
#define REG_MI_CGC_NSPI_INTC_FIELD( cause ) \
    (u32)( \
    ((u32)(cause) << REG_MI_CGC_NSPI_INTC_CAUSE_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_ARM9_IOREG_MI_H_ */
#endif
