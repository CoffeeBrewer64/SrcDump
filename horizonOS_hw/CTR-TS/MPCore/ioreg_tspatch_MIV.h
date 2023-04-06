/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TS/MPCore/ioreg_tspatch_MIV.h

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
#ifndef NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_MIV_H_
#define NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_MIV_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* XDMAV_DS */

#define REG_XDMAV_DS_OFFSET                                0x0000
#define REG_XDMAV_DS_ADDR                                  (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_DS_OFFSET)
#define reg_MIV_XDMAV_DS                                   (*(const REGType32v *) REG_XDMAV_DS_ADDR)

/* XDMAV_DPC */

#define REG_XDMAV_DPC_OFFSET                               0x0004
#define REG_XDMAV_DPC_ADDR                                 (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_DPC_OFFSET)
#define reg_MIV_XDMAV_DPC                                  (*(const REGType32v *) REG_XDMAV_DPC_ADDR)

/* XDMAV_IE */

#define REG_XDMAV_IE_OFFSET                                0x0020
#define REG_XDMAV_IE_ADDR                                  (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_IE_OFFSET)
#define reg_MIV_XDMAV_IE                                   (*( REGType32v *) REG_XDMAV_IE_ADDR)

/* XDMAV_ES */

#define REG_XDMAV_ES_OFFSET                                0x0024
#define REG_XDMAV_ES_ADDR                                  (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_ES_OFFSET)
#define reg_MIV_XDMAV_ES                                   (*(const REGType32v *) REG_XDMAV_ES_ADDR)

/* XDMAV_ISTAT */

#define REG_XDMAV_ISTAT_OFFSET                             0x0028
#define REG_XDMAV_ISTAT_ADDR                               (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_ISTAT_OFFSET)
#define reg_MIV_XDMAV_ISTAT                                (*(const REGType32v *) REG_XDMAV_ISTAT_ADDR)

/* XDMAV_ICLR */

#define REG_XDMAV_ICLR_OFFSET                              0x002c
#define REG_XDMAV_ICLR_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_ICLR_OFFSET)
#define reg_MIV_XDMAV_ICLR                                 (*( REGType32v *) REG_XDMAV_ICLR_ADDR)

/* XDMAV_FSM */

#define REG_XDMAV_FSM_OFFSET                               0x0030
#define REG_XDMAV_FSM_ADDR                                 (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_FSM_OFFSET)
#define reg_MIV_XDMAV_FSM                                  (*(const REGType32v *) REG_XDMAV_FSM_ADDR)

/* XDMAV_FSC */

#define REG_XDMAV_FSC_OFFSET                               0x0034
#define REG_XDMAV_FSC_ADDR                                 (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_FSC_OFFSET)
#define reg_MIV_XDMAV_FSC                                  (*(const REGType32v *) REG_XDMAV_FSC_ADDR)

/* XDMAV_FTM */

#define REG_XDMAV_FTM_OFFSET                               0x0038
#define REG_XDMAV_FTM_ADDR                                 (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_FTM_OFFSET)
#define reg_MIV_XDMAV_FTM                                  (*(const REGType32v *) REG_XDMAV_FTM_ADDR)

/* XDMAV_FTC0 */

#define REG_XDMAV_FTC0_OFFSET                              0x0040
#define REG_XDMAV_FTC0_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_FTC0_OFFSET)
#define reg_MIV_XDMAV_FTC0                                 (*(const REGType32v *) REG_XDMAV_FTC0_ADDR)

/* XDMAV_FTC1 */

#define REG_XDMAV_FTC1_OFFSET                              0x0044
#define REG_XDMAV_FTC1_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_FTC1_OFFSET)
#define reg_MIV_XDMAV_FTC1                                 (*(const REGType32v *) REG_XDMAV_FTC1_ADDR)

/* XDMAV_CS0 */

#define REG_XDMAV_CS0_OFFSET                               0x0100
#define REG_XDMAV_CS0_ADDR                                 (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_CS0_OFFSET)
#define reg_MIV_XDMAV_CS0                                  (*(const REGType32v *) REG_XDMAV_CS0_ADDR)

/* XDMAV_CPC0 */

#define REG_XDMAV_CPC0_OFFSET                              0x0104
#define REG_XDMAV_CPC0_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_CPC0_OFFSET)
#define reg_MIV_XDMAV_CPC0                                 (*(const REGType32v *) REG_XDMAV_CPC0_ADDR)

/* XDMAV_CS1 */

#define REG_XDMAV_CS1_OFFSET                               0x0108
#define REG_XDMAV_CS1_ADDR                                 (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_CS1_OFFSET)
#define reg_MIV_XDMAV_CS1                                  (*(const REGType32v *) REG_XDMAV_CS1_ADDR)

/* XDMAV_CPC1 */

#define REG_XDMAV_CPC1_OFFSET                              0x010c
#define REG_XDMAV_CPC1_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_CPC1_OFFSET)
#define reg_MIV_XDMAV_CPC1                                 (*(const REGType32v *) REG_XDMAV_CPC1_ADDR)

/* XDMAV_SA0 */

#define REG_XDMAV_SA0_OFFSET                               0x0400
#define REG_XDMAV_SA0_ADDR                                 (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_SA0_OFFSET)
#define reg_MIV_XDMAV_SA0                                  (*(const REGType32v *) REG_XDMAV_SA0_ADDR)

/* XDMAV_DA0 */

#define REG_XDMAV_DA0_OFFSET                               0x0404
#define REG_XDMAV_DA0_ADDR                                 (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_DA0_OFFSET)
#define reg_MIV_XDMAV_DA0                                  (*(const REGType32v *) REG_XDMAV_DA0_ADDR)

/* XDMAV_CC0 */

#define REG_XDMAV_CC0_OFFSET                               0x0408
#define REG_XDMAV_CC0_ADDR                                 (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_CC0_OFFSET)
#define reg_MIV_XDMAV_CC0                                  (*(const REGType32v *) REG_XDMAV_CC0_ADDR)

/* XDMAV_LC00 */

#define REG_XDMAV_LC00_OFFSET                              0x040c
#define REG_XDMAV_LC00_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_LC00_OFFSET)
#define reg_MIV_XDMAV_LC00                                 (*(const REGType32v *) REG_XDMAV_LC00_ADDR)

/* XDMAV_LC10 */

#define REG_XDMAV_LC10_OFFSET                              0x0410
#define REG_XDMAV_LC10_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_LC10_OFFSET)
#define reg_MIV_XDMAV_LC10                                 (*(const REGType32v *) REG_XDMAV_LC10_ADDR)

/* XDMAV_SA1 */

#define REG_XDMAV_SA1_OFFSET                               0x0420
#define REG_XDMAV_SA1_ADDR                                 (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_SA1_OFFSET)
#define reg_MIV_XDMAV_SA1                                  (*(const REGType32v *) REG_XDMAV_SA1_ADDR)

/* XDMAV_DA1 */

#define REG_XDMAV_DA1_OFFSET                               0x0424
#define REG_XDMAV_DA1_ADDR                                 (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_DA1_OFFSET)
#define reg_MIV_XDMAV_DA1                                  (*(const REGType32v *) REG_XDMAV_DA1_ADDR)

/* XDMAV_CC1 */

#define REG_XDMAV_CC1_OFFSET                               0x0428
#define REG_XDMAV_CC1_ADDR                                 (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_CC1_OFFSET)
#define reg_MIV_XDMAV_CC1                                  (*(const REGType32v *) REG_XDMAV_CC1_ADDR)

/* XDMAV_LC01 */

#define REG_XDMAV_LC01_OFFSET                              0x042c
#define REG_XDMAV_LC01_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_LC01_OFFSET)
#define reg_MIV_XDMAV_LC01                                 (*(const REGType32v *) REG_XDMAV_LC01_ADDR)

/* XDMAV_LC11 */

#define REG_XDMAV_LC11_OFFSET                              0x0430
#define REG_XDMAV_LC11_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_LC11_OFFSET)
#define reg_MIV_XDMAV_LC11                                 (*(const REGType32v *) REG_XDMAV_LC11_ADDR)

/* XDMAV_DBGSTAT */

#define REG_XDMAV_DBGSTAT_OFFSET                           0x0d00
#define REG_XDMAV_DBGSTAT_ADDR                             (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_DBGSTAT_OFFSET)
#define reg_MIV_XDMAV_DBGSTAT                              (*(const REGType32v *) REG_XDMAV_DBGSTAT_ADDR)

/* XDMAV_DBGCMD */

#define REG_XDMAV_DBGCMD_OFFSET                            0x0d04
#define REG_XDMAV_DBGCMD_ADDR                              (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_DBGCMD_OFFSET)
#define reg_MIV_XDMAV_DBGCMD                               (*( REGType32v *) REG_XDMAV_DBGCMD_ADDR)

/* XDMAV_DBGINST0 */

#define REG_XDMAV_DBGINST0_OFFSET                          0x0d08
#define REG_XDMAV_DBGINST0_ADDR                            (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_DBGINST0_OFFSET)
#define reg_MIV_XDMAV_DBGINST0                             (*( REGType32v *) REG_XDMAV_DBGINST0_ADDR)

/* XDMAV_DBGINST1 */

#define REG_XDMAV_DBGINST1_OFFSET                          0x0d0c
#define REG_XDMAV_DBGINST1_ADDR                            (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_DBGINST1_OFFSET)
#define reg_MIV_XDMAV_DBGINST1                             (*( REGType32v *) REG_XDMAV_DBGINST1_ADDR)

/* XDMAV_CFG0 */

#define REG_XDMAV_CFG0_OFFSET                              0x0e00
#define REG_XDMAV_CFG0_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_CFG0_OFFSET)
#define reg_MIV_XDMAV_CFG0                                 (*(const REGType32v *) REG_XDMAV_CFG0_ADDR)

/* XDMAV_CFG1 */

#define REG_XDMAV_CFG1_OFFSET                              0x0e04
#define REG_XDMAV_CFG1_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_CFG1_OFFSET)
#define reg_MIV_XDMAV_CFG1                                 (*(const REGType32v *) REG_XDMAV_CFG1_ADDR)

/* XDMAV_CFG2 */

#define REG_XDMAV_CFG2_OFFSET                              0x0e08
#define REG_XDMAV_CFG2_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_CFG2_OFFSET)
#define reg_MIV_XDMAV_CFG2                                 (*(const REGType32v *) REG_XDMAV_CFG2_ADDR)

/* XDMAV_CFG3 */

#define REG_XDMAV_CFG3_OFFSET                              0x0e0c
#define REG_XDMAV_CFG3_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_CFG3_OFFSET)
#define reg_MIV_XDMAV_CFG3                                 (*(const REGType32v *) REG_XDMAV_CFG3_ADDR)

/* XDMAV_CFG4 */

#define REG_XDMAV_CFG4_OFFSET                              0x0e10
#define REG_XDMAV_CFG4_ADDR                                (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_CFG4_OFFSET)
#define reg_MIV_XDMAV_CFG4                                 (*(const REGType32v *) REG_XDMAV_CFG4_ADDR)

/* XDMAV_CFGDN */

#define REG_XDMAV_CFGDN_OFFSET                             0x0e14
#define REG_XDMAV_CFGDN_ADDR                               (NN_KERN_V_ADDR_DMAC_REGISTER + REG_XDMAV_CFGDN_OFFSET)
#define reg_MIV_XDMAV_CFGDN                                (*(const REGType32v *) REG_XDMAV_CFGDN_ADDR)


/*
 * Definitions of Register fields
 */


/* XDMAV_DS */

#define REG_MIV_XDMAV_DS_DNS_SHIFT                         9
#define REG_MIV_XDMAV_DS_DNS_SIZE                          1
#define REG_MIV_XDMAV_DS_DNS_MASK                          0x00000200

#define REG_MIV_XDMAV_DS_WEV_SHIFT                         4
#define REG_MIV_XDMAV_DS_WEV_SIZE                          5
#define REG_MIV_XDMAV_DS_WEV_MASK                          0x000001f0

#define REG_MIV_XDMAV_DS_STAT_SHIFT                        0
#define REG_MIV_XDMAV_DS_STAT_SIZE                         4
#define REG_MIV_XDMAV_DS_STAT_MASK                         0x0000000f

#ifndef SDK_ASM
#define REG_MIV_XDMAV_DS_FIELD( dns, wev, stat ) \
    (u32)( \
    ((u32)(dns) << REG_MIV_XDMAV_DS_DNS_SHIFT) | \
    ((u32)(wev) << REG_MIV_XDMAV_DS_WEV_SHIFT) | \
    ((u32)(stat) << REG_MIV_XDMAV_DS_STAT_SHIFT))
#endif


/* XDMAV_DPC */

/* XDMAV_IE */

/* XDMAV_ES */

/* XDMAV_ISTAT */

/* XDMAV_ICLR */

/* XDMAV_FSM */

#define REG_MIV_XDMAV_FSM_FS_MGR_SHIFT                     0
#define REG_MIV_XDMAV_FSM_FS_MGR_SIZE                      1
#define REG_MIV_XDMAV_FSM_FS_MGR_MASK                      0x00000001

#ifndef SDK_ASM
#define REG_MIV_XDMAV_FSM_FIELD( fs_mgr ) \
    (u32)( \
    ((u32)(fs_mgr) << REG_MIV_XDMAV_FSM_FS_MGR_SHIFT))
#endif


/* XDMAV_FSC */

#define REG_MIV_XDMAV_FSC_FS_CH_SHIFT                      0
#define REG_MIV_XDMAV_FSC_FS_CH_SIZE                       8
#define REG_MIV_XDMAV_FSC_FS_CH_MASK                       0x000000ff

#ifndef SDK_ASM
#define REG_MIV_XDMAV_FSC_FIELD( fs_ch ) \
    (u32)( \
    ((u32)(fs_ch) << REG_MIV_XDMAV_FSC_FS_CH_SHIFT))
#endif


/* XDMAV_FTM */

#define REG_MIV_XDMAV_FTM_DBG_INST_SHIFT                   30
#define REG_MIV_XDMAV_FTM_DBG_INST_SIZE                    1
#define REG_MIV_XDMAV_FTM_DBG_INST_MASK                    0x40000000

#define REG_MIV_XDMAV_FTM_FETCH_ERR_SHIFT                  16
#define REG_MIV_XDMAV_FTM_FETCH_ERR_SIZE                   1
#define REG_MIV_XDMAV_FTM_FETCH_ERR_MASK                   0x00010000

#define REG_MIV_XDMAV_FTM_EVENT_ERR_SHIFT                  5
#define REG_MIV_XDMAV_FTM_EVENT_ERR_SIZE                   1
#define REG_MIV_XDMAV_FTM_EVENT_ERR_MASK                   0x00000020

#define REG_MIV_XDMAV_FTM_DMAGO_ERR_SHIFT                  4
#define REG_MIV_XDMAV_FTM_DMAGO_ERR_SIZE                   1
#define REG_MIV_XDMAV_FTM_DMAGO_ERR_MASK                   0x00000010

#define REG_MIV_XDMAV_FTM_OP_INVALID_SHIFT                 1
#define REG_MIV_XDMAV_FTM_OP_INVALID_SIZE                  1
#define REG_MIV_XDMAV_FTM_OP_INVALID_MASK                  0x00000002

#define REG_MIV_XDMAV_FTM_UNDEF_INST_SHIFT                 0
#define REG_MIV_XDMAV_FTM_UNDEF_INST_SIZE                  1
#define REG_MIV_XDMAV_FTM_UNDEF_INST_MASK                  0x00000001

#ifndef SDK_ASM
#define REG_MIV_XDMAV_FTM_FIELD( dbg_inst, fetch_err, event_err, dmago_err, op_invalid, undef_inst ) \
    (u32)( \
    ((u32)(dbg_inst) << REG_MIV_XDMAV_FTM_DBG_INST_SHIFT) | \
    ((u32)(fetch_err) << REG_MIV_XDMAV_FTM_FETCH_ERR_SHIFT) | \
    ((u32)(event_err) << REG_MIV_XDMAV_FTM_EVENT_ERR_SHIFT) | \
    ((u32)(dmago_err) << REG_MIV_XDMAV_FTM_DMAGO_ERR_SHIFT) | \
    ((u32)(op_invalid) << REG_MIV_XDMAV_FTM_OP_INVALID_SHIFT) | \
    ((u32)(undef_inst) << REG_MIV_XDMAV_FTM_UNDEF_INST_SHIFT))
#endif


/* XDMAV_FTC0 */

#define REG_MIV_XDMAV_FTC0_LOCKUP_ERR_SHIFT                31
#define REG_MIV_XDMAV_FTC0_LOCKUP_ERR_SIZE                 1
#define REG_MIV_XDMAV_FTC0_LOCKUP_ERR_MASK                 0x80000000

#define REG_MIV_XDMAV_FTC0_DBG_INST_SHIFT                  30
#define REG_MIV_XDMAV_FTC0_DBG_INST_SIZE                   1
#define REG_MIV_XDMAV_FTC0_DBG_INST_MASK                   0x40000000

#define REG_MIV_XDMAV_FTC0_READ_ERR_SHIFT                  18
#define REG_MIV_XDMAV_FTC0_READ_ERR_SIZE                   1
#define REG_MIV_XDMAV_FTC0_READ_ERR_MASK                   0x00040000

#define REG_MIV_XDMAV_FTC0_WRITE_ERR_SHIFT                 17
#define REG_MIV_XDMAV_FTC0_WRITE_ERR_SIZE                  1
#define REG_MIV_XDMAV_FTC0_WRITE_ERR_MASK                  0x00020000

#define REG_MIV_XDMAV_FTC0_FETCH_ERR_SHIFT                 16
#define REG_MIV_XDMAV_FTC0_FETCH_ERR_SIZE                  1
#define REG_MIV_XDMAV_FTC0_FETCH_ERR_MASK                  0x00010000

#define REG_MIV_XDMAV_FTC0_MFIFO_ERR_SHIFT                 12
#define REG_MIV_XDMAV_FTC0_MFIFO_ERR_SIZE                  1
#define REG_MIV_XDMAV_FTC0_MFIFO_ERR_MASK                  0x00001000

#define REG_MIV_XDMAV_FTC0_CH_RW_ERR_SHIFT                 7
#define REG_MIV_XDMAV_FTC0_CH_RW_ERR_SIZE                  1
#define REG_MIV_XDMAV_FTC0_CH_RW_ERR_MASK                  0x00000080

#define REG_MIV_XDMAV_FTC0_CH_PERIPH_ERR_SHIFT             6
#define REG_MIV_XDMAV_FTC0_CH_PERIPH_ERR_SIZE              1
#define REG_MIV_XDMAV_FTC0_CH_PERIPH_ERR_MASK              0x00000040

#define REG_MIV_XDMAV_FTC0_CH_EVENT_ERR_SHIFT              5
#define REG_MIV_XDMAV_FTC0_CH_EVENT_ERR_SIZE               1
#define REG_MIV_XDMAV_FTC0_CH_EVENT_ERR_MASK               0x00000020

#define REG_MIV_XDMAV_FTC0_OP_INVALID_SHIFT                1
#define REG_MIV_XDMAV_FTC0_OP_INVALID_SIZE                 1
#define REG_MIV_XDMAV_FTC0_OP_INVALID_MASK                 0x00000002

#define REG_MIV_XDMAV_FTC0_UNDEF_INST_SHIFT                0
#define REG_MIV_XDMAV_FTC0_UNDEF_INST_SIZE                 1
#define REG_MIV_XDMAV_FTC0_UNDEF_INST_MASK                 0x00000001

#ifndef SDK_ASM
#define REG_MIV_XDMAV_FTC0_FIELD( lockup_err, dbg_inst, read_err, write_err, fetch_err, mfifo_err, ch_rw_err, ch_periph_err, ch_event_err, op_invalid, undef_inst ) \
    (u32)( \
    ((u32)(lockup_err) << REG_MIV_XDMAV_FTC0_LOCKUP_ERR_SHIFT) | \
    ((u32)(dbg_inst) << REG_MIV_XDMAV_FTC0_DBG_INST_SHIFT) | \
    ((u32)(read_err) << REG_MIV_XDMAV_FTC0_READ_ERR_SHIFT) | \
    ((u32)(write_err) << REG_MIV_XDMAV_FTC0_WRITE_ERR_SHIFT) | \
    ((u32)(fetch_err) << REG_MIV_XDMAV_FTC0_FETCH_ERR_SHIFT) | \
    ((u32)(mfifo_err) << REG_MIV_XDMAV_FTC0_MFIFO_ERR_SHIFT) | \
    ((u32)(ch_rw_err) << REG_MIV_XDMAV_FTC0_CH_RW_ERR_SHIFT) | \
    ((u32)(ch_periph_err) << REG_MIV_XDMAV_FTC0_CH_PERIPH_ERR_SHIFT) | \
    ((u32)(ch_event_err) << REG_MIV_XDMAV_FTC0_CH_EVENT_ERR_SHIFT) | \
    ((u32)(op_invalid) << REG_MIV_XDMAV_FTC0_OP_INVALID_SHIFT) | \
    ((u32)(undef_inst) << REG_MIV_XDMAV_FTC0_UNDEF_INST_SHIFT))
#endif


/* XDMAV_FTC1 */

/* XDMAV_CS0 */

#define REG_MIV_XDMAV_CS0_CNS_SHIFT                        21
#define REG_MIV_XDMAV_CS0_CNS_SIZE                         1
#define REG_MIV_XDMAV_CS0_CNS_MASK                         0x00200000

#define REG_MIV_XDMAV_CS0_WFP_P_SHIFT                      15
#define REG_MIV_XDMAV_CS0_WFP_P_SIZE                       1
#define REG_MIV_XDMAV_CS0_WFP_P_MASK                       0x00008000

#define REG_MIV_XDMAV_CS0_WFP_B_SHIFT                      14
#define REG_MIV_XDMAV_CS0_WFP_B_SIZE                       1
#define REG_MIV_XDMAV_CS0_WFP_B_MASK                       0x00004000

#define REG_MIV_XDMAV_CS0_WAKE_NUM_SHIFT                   4
#define REG_MIV_XDMAV_CS0_WAKE_NUM_SIZE                    5
#define REG_MIV_XDMAV_CS0_WAKE_NUM_MASK                    0x000001f0

#define REG_MIV_XDMAV_CS0_CS_SHIFT                         0
#define REG_MIV_XDMAV_CS0_CS_SIZE                          4
#define REG_MIV_XDMAV_CS0_CS_MASK                          0x0000000f

#ifndef SDK_ASM
#define REG_MIV_XDMAV_CS0_FIELD( cns, wfp_p, wfp_b, wake_num, cs ) \
    (u32)( \
    ((u32)(cns) << REG_MIV_XDMAV_CS0_CNS_SHIFT) | \
    ((u32)(wfp_p) << REG_MIV_XDMAV_CS0_WFP_P_SHIFT) | \
    ((u32)(wfp_b) << REG_MIV_XDMAV_CS0_WFP_B_SHIFT) | \
    ((u32)(wake_num) << REG_MIV_XDMAV_CS0_WAKE_NUM_SHIFT) | \
    ((u32)(cs) << REG_MIV_XDMAV_CS0_CS_SHIFT))
#endif


/* XDMAV_CPC0 */

/* XDMAV_CS1 */

#define REG_MIV_XDMAV_CS1_CNS_SHIFT                        21
#define REG_MIV_XDMAV_CS1_CNS_SIZE                         1
#define REG_MIV_XDMAV_CS1_CNS_MASK                         0x00200000

#define REG_MIV_XDMAV_CS1_WFP_P_SHIFT                      15
#define REG_MIV_XDMAV_CS1_WFP_P_SIZE                       1
#define REG_MIV_XDMAV_CS1_WFP_P_MASK                       0x00008000

#define REG_MIV_XDMAV_CS1_WFP_B_SHIFT                      14
#define REG_MIV_XDMAV_CS1_WFP_B_SIZE                       1
#define REG_MIV_XDMAV_CS1_WFP_B_MASK                       0x00004000

#define REG_MIV_XDMAV_CS1_WAKE_NUM_SHIFT                   4
#define REG_MIV_XDMAV_CS1_WAKE_NUM_SIZE                    5
#define REG_MIV_XDMAV_CS1_WAKE_NUM_MASK                    0x000001f0

#define REG_MIV_XDMAV_CS1_CS_SHIFT                         0
#define REG_MIV_XDMAV_CS1_CS_SIZE                          4
#define REG_MIV_XDMAV_CS1_CS_MASK                          0x0000000f

#ifndef SDK_ASM
#define REG_MIV_XDMAV_CS1_FIELD( cns, wfp_p, wfp_b, wake_num, cs ) \
    (u32)( \
    ((u32)(cns) << REG_MIV_XDMAV_CS1_CNS_SHIFT) | \
    ((u32)(wfp_p) << REG_MIV_XDMAV_CS1_WFP_P_SHIFT) | \
    ((u32)(wfp_b) << REG_MIV_XDMAV_CS1_WFP_B_SHIFT) | \
    ((u32)(wake_num) << REG_MIV_XDMAV_CS1_WAKE_NUM_SHIFT) | \
    ((u32)(cs) << REG_MIV_XDMAV_CS1_CS_SHIFT))
#endif


/* XDMAV_CPC1 */

/* XDMAV_SA0 */

/* XDMAV_DA0 */

/* XDMAV_CC0 */

#define REG_MIV_XDMAV_CC0_SWP_SZ_SHIFT                     28
#define REG_MIV_XDMAV_CC0_SWP_SZ_SIZE                      3
#define REG_MIV_XDMAV_CC0_SWP_SZ_MASK                      0x70000000

#define REG_MIV_XDMAV_CC0_DCACHE_SHIFT                     25
#define REG_MIV_XDMAV_CC0_DCACHE_SIZE                      3
#define REG_MIV_XDMAV_CC0_DCACHE_MASK                      0x0e000000

#define REG_MIV_XDMAV_CC0_DPROT_SHIFT                      22
#define REG_MIV_XDMAV_CC0_DPROT_SIZE                       3
#define REG_MIV_XDMAV_CC0_DPROT_MASK                       0x01c00000

#define REG_MIV_XDMAV_CC0_DBST_LEN_SHIFT                   18
#define REG_MIV_XDMAV_CC0_DBST_LEN_SIZE                    4
#define REG_MIV_XDMAV_CC0_DBST_LEN_MASK                    0x003c0000

#define REG_MIV_XDMAV_CC0_DBST_SZ_SHIFT                    15
#define REG_MIV_XDMAV_CC0_DBST_SZ_SIZE                     3
#define REG_MIV_XDMAV_CC0_DBST_SZ_MASK                     0x00038000

#define REG_MIV_XDMAV_CC0_DINC_SHIFT                       14
#define REG_MIV_XDMAV_CC0_DINC_SIZE                        1
#define REG_MIV_XDMAV_CC0_DINC_MASK                        0x00004000

#define REG_MIV_XDMAV_CC0_SCACHE_SHIFT                     11
#define REG_MIV_XDMAV_CC0_SCACHE_SIZE                      3
#define REG_MIV_XDMAV_CC0_SCACHE_MASK                      0x00003800

#define REG_MIV_XDMAV_CC0_SPROT_SHIFT                      8
#define REG_MIV_XDMAV_CC0_SPROT_SIZE                       3
#define REG_MIV_XDMAV_CC0_SPROT_MASK                       0x00000700

#define REG_MIV_XDMAV_CC0_SBST_LEN_SHIFT                   4
#define REG_MIV_XDMAV_CC0_SBST_LEN_SIZE                    4
#define REG_MIV_XDMAV_CC0_SBST_LEN_MASK                    0x000000f0

#define REG_MIV_XDMAV_CC0_SBST_SZ_SHIFT                    1
#define REG_MIV_XDMAV_CC0_SBST_SZ_SIZE                     3
#define REG_MIV_XDMAV_CC0_SBST_SZ_MASK                     0x0000000e

#define REG_MIV_XDMAV_CC0_SINC_SHIFT                       0
#define REG_MIV_XDMAV_CC0_SINC_SIZE                        1
#define REG_MIV_XDMAV_CC0_SINC_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_MIV_XDMAV_CC0_FIELD( swp_sz, dcache, dprot, dbst_len, dbst_sz, dinc, scache, sprot, sbst_len, sbst_sz, sinc ) \
    (u32)( \
    ((u32)(swp_sz) << REG_MIV_XDMAV_CC0_SWP_SZ_SHIFT) | \
    ((u32)(dcache) << REG_MIV_XDMAV_CC0_DCACHE_SHIFT) | \
    ((u32)(dprot) << REG_MIV_XDMAV_CC0_DPROT_SHIFT) | \
    ((u32)(dbst_len) << REG_MIV_XDMAV_CC0_DBST_LEN_SHIFT) | \
    ((u32)(dbst_sz) << REG_MIV_XDMAV_CC0_DBST_SZ_SHIFT) | \
    ((u32)(dinc) << REG_MIV_XDMAV_CC0_DINC_SHIFT) | \
    ((u32)(scache) << REG_MIV_XDMAV_CC0_SCACHE_SHIFT) | \
    ((u32)(sprot) << REG_MIV_XDMAV_CC0_SPROT_SHIFT) | \
    ((u32)(sbst_len) << REG_MIV_XDMAV_CC0_SBST_LEN_SHIFT) | \
    ((u32)(sbst_sz) << REG_MIV_XDMAV_CC0_SBST_SZ_SHIFT) | \
    ((u32)(sinc) << REG_MIV_XDMAV_CC0_SINC_SHIFT))
#endif


/* XDMAV_LC00 */

/* XDMAV_LC10 */

/* XDMAV_SA1 */

/* XDMAV_DA1 */

/* XDMAV_CC1 */

#define REG_MIV_XDMAV_CC1_SWP_SZ_SHIFT                     28
#define REG_MIV_XDMAV_CC1_SWP_SZ_SIZE                      3
#define REG_MIV_XDMAV_CC1_SWP_SZ_MASK                      0x70000000

#define REG_MIV_XDMAV_CC1_DCACHE_SHIFT                     25
#define REG_MIV_XDMAV_CC1_DCACHE_SIZE                      3
#define REG_MIV_XDMAV_CC1_DCACHE_MASK                      0x0e000000

#define REG_MIV_XDMAV_CC1_DPROT_SHIFT                      22
#define REG_MIV_XDMAV_CC1_DPROT_SIZE                       3
#define REG_MIV_XDMAV_CC1_DPROT_MASK                       0x01c00000

#define REG_MIV_XDMAV_CC1_DBST_LEN_SHIFT                   18
#define REG_MIV_XDMAV_CC1_DBST_LEN_SIZE                    4
#define REG_MIV_XDMAV_CC1_DBST_LEN_MASK                    0x003c0000

#define REG_MIV_XDMAV_CC1_DBST_SZ_SHIFT                    15
#define REG_MIV_XDMAV_CC1_DBST_SZ_SIZE                     3
#define REG_MIV_XDMAV_CC1_DBST_SZ_MASK                     0x00038000

#define REG_MIV_XDMAV_CC1_DINC_SHIFT                       14
#define REG_MIV_XDMAV_CC1_DINC_SIZE                        1
#define REG_MIV_XDMAV_CC1_DINC_MASK                        0x00004000

#define REG_MIV_XDMAV_CC1_SCACHE_SHIFT                     11
#define REG_MIV_XDMAV_CC1_SCACHE_SIZE                      3
#define REG_MIV_XDMAV_CC1_SCACHE_MASK                      0x00003800

#define REG_MIV_XDMAV_CC1_SPROT_SHIFT                      8
#define REG_MIV_XDMAV_CC1_SPROT_SIZE                       3
#define REG_MIV_XDMAV_CC1_SPROT_MASK                       0x00000700

#define REG_MIV_XDMAV_CC1_SBST_LEN_SHIFT                   4
#define REG_MIV_XDMAV_CC1_SBST_LEN_SIZE                    4
#define REG_MIV_XDMAV_CC1_SBST_LEN_MASK                    0x000000f0

#define REG_MIV_XDMAV_CC1_SBST_SZ_SHIFT                    1
#define REG_MIV_XDMAV_CC1_SBST_SZ_SIZE                     3
#define REG_MIV_XDMAV_CC1_SBST_SZ_MASK                     0x0000000e

#define REG_MIV_XDMAV_CC1_SINC_SHIFT                       0
#define REG_MIV_XDMAV_CC1_SINC_SIZE                        1
#define REG_MIV_XDMAV_CC1_SINC_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_MIV_XDMAV_CC1_FIELD( swp_sz, dcache, dprot, dbst_len, dbst_sz, dinc, scache, sprot, sbst_len, sbst_sz, sinc ) \
    (u32)( \
    ((u32)(swp_sz) << REG_MIV_XDMAV_CC1_SWP_SZ_SHIFT) | \
    ((u32)(dcache) << REG_MIV_XDMAV_CC1_DCACHE_SHIFT) | \
    ((u32)(dprot) << REG_MIV_XDMAV_CC1_DPROT_SHIFT) | \
    ((u32)(dbst_len) << REG_MIV_XDMAV_CC1_DBST_LEN_SHIFT) | \
    ((u32)(dbst_sz) << REG_MIV_XDMAV_CC1_DBST_SZ_SHIFT) | \
    ((u32)(dinc) << REG_MIV_XDMAV_CC1_DINC_SHIFT) | \
    ((u32)(scache) << REG_MIV_XDMAV_CC1_SCACHE_SHIFT) | \
    ((u32)(sprot) << REG_MIV_XDMAV_CC1_SPROT_SHIFT) | \
    ((u32)(sbst_len) << REG_MIV_XDMAV_CC1_SBST_LEN_SHIFT) | \
    ((u32)(sbst_sz) << REG_MIV_XDMAV_CC1_SBST_SZ_SHIFT) | \
    ((u32)(sinc) << REG_MIV_XDMAV_CC1_SINC_SHIFT))
#endif


/* XDMAV_LC01 */

/* XDMAV_LC11 */

/* XDMAV_DBGSTAT */

#define REG_MIV_XDMAV_DBGSTAT_BUSY_SHIFT                   0
#define REG_MIV_XDMAV_DBGSTAT_BUSY_SIZE                    1
#define REG_MIV_XDMAV_DBGSTAT_BUSY_MASK                    0x00000001

#ifndef SDK_ASM
#define REG_MIV_XDMAV_DBGSTAT_FIELD( busy ) \
    (u32)( \
    ((u32)(busy) << REG_MIV_XDMAV_DBGSTAT_BUSY_SHIFT))
#endif


/* XDMAV_DBGCMD */

#define REG_MIV_XDMAV_DBGCMD_CMD_SHIFT                     0
#define REG_MIV_XDMAV_DBGCMD_CMD_SIZE                      2
#define REG_MIV_XDMAV_DBGCMD_CMD_MASK                      0x00000003

#ifndef SDK_ASM
#define REG_MIV_XDMAV_DBGCMD_FIELD( cmd ) \
    (u32)( \
    ((u32)(cmd) << REG_MIV_XDMAV_DBGCMD_CMD_SHIFT))
#endif


/* XDMAV_DBGINST0 */

#define REG_MIV_XDMAV_DBGINST0_INST1_SHIFT                 24
#define REG_MIV_XDMAV_DBGINST0_INST1_SIZE                  8
#define REG_MIV_XDMAV_DBGINST0_INST1_MASK                  0xff000000

#define REG_MIV_XDMAV_DBGINST0_INST0_SHIFT                 16
#define REG_MIV_XDMAV_DBGINST0_INST0_SIZE                  8
#define REG_MIV_XDMAV_DBGINST0_INST0_MASK                  0x00ff0000

#define REG_MIV_XDMAV_DBGINST0_CH_SHIFT                    8
#define REG_MIV_XDMAV_DBGINST0_CH_SIZE                     3
#define REG_MIV_XDMAV_DBGINST0_CH_MASK                     0x00000700

#define REG_MIV_XDMAV_DBGINST0_DBG_TH_SHIFT                0
#define REG_MIV_XDMAV_DBGINST0_DBG_TH_SIZE                 1
#define REG_MIV_XDMAV_DBGINST0_DBG_TH_MASK                 0x00000001

#ifndef SDK_ASM
#define REG_MIV_XDMAV_DBGINST0_FIELD( inst1, inst0, ch, dbg_th ) \
    (u32)( \
    ((u32)(inst1) << REG_MIV_XDMAV_DBGINST0_INST1_SHIFT) | \
    ((u32)(inst0) << REG_MIV_XDMAV_DBGINST0_INST0_SHIFT) | \
    ((u32)(ch) << REG_MIV_XDMAV_DBGINST0_CH_SHIFT) | \
    ((u32)(dbg_th) << REG_MIV_XDMAV_DBGINST0_DBG_TH_SHIFT))
#endif


/* XDMAV_DBGINST1 */

#define REG_MIV_XDMAV_DBGINST1_INST5_SHIFT                 24
#define REG_MIV_XDMAV_DBGINST1_INST5_SIZE                  8
#define REG_MIV_XDMAV_DBGINST1_INST5_MASK                  0xff000000

#define REG_MIV_XDMAV_DBGINST1_INST4_SHIFT                 16
#define REG_MIV_XDMAV_DBGINST1_INST4_SIZE                  8
#define REG_MIV_XDMAV_DBGINST1_INST4_MASK                  0x00ff0000

#define REG_MIV_XDMAV_DBGINST1_INST3_SHIFT                 8
#define REG_MIV_XDMAV_DBGINST1_INST3_SIZE                  8
#define REG_MIV_XDMAV_DBGINST1_INST3_MASK                  0x0000ff00

#define REG_MIV_XDMAV_DBGINST1_INST2_SHIFT                 0
#define REG_MIV_XDMAV_DBGINST1_INST2_SIZE                  8
#define REG_MIV_XDMAV_DBGINST1_INST2_MASK                  0x000000ff

#ifndef SDK_ASM
#define REG_MIV_XDMAV_DBGINST1_FIELD( inst5, inst4, inst3, inst2 ) \
    (u32)( \
    ((u32)(inst5) << REG_MIV_XDMAV_DBGINST1_INST5_SHIFT) | \
    ((u32)(inst4) << REG_MIV_XDMAV_DBGINST1_INST4_SHIFT) | \
    ((u32)(inst3) << REG_MIV_XDMAV_DBGINST1_INST3_SHIFT) | \
    ((u32)(inst2) << REG_MIV_XDMAV_DBGINST1_INST2_SHIFT))
#endif


/* XDMAV_CFG0 */

#define REG_MIV_XDMAV_CFG0_NUM_EV_SHIFT                    17
#define REG_MIV_XDMAV_CFG0_NUM_EV_SIZE                     5
#define REG_MIV_XDMAV_CFG0_NUM_EV_MASK                     0x003e0000

#define REG_MIV_XDMAV_CFG0_NUM_PRH_SHIFT                   12
#define REG_MIV_XDMAV_CFG0_NUM_PRH_SIZE                    5
#define REG_MIV_XDMAV_CFG0_NUM_PRH_MASK                    0x0001f000

#define REG_MIV_XDMAV_CFG0_NUM_CH_SHIFT                    4
#define REG_MIV_XDMAV_CFG0_NUM_CH_SIZE                     3
#define REG_MIV_XDMAV_CFG0_NUM_CH_MASK                     0x00000070

#define REG_MIV_XDMAV_CFG0_RST_NS_SHIFT                    2
#define REG_MIV_XDMAV_CFG0_RST_NS_SIZE                     1
#define REG_MIV_XDMAV_CFG0_RST_NS_MASK                     0x00000004

#define REG_MIV_XDMAV_CFG0_BOOT_E_SHIFT                    1
#define REG_MIV_XDMAV_CFG0_BOOT_E_SIZE                     1
#define REG_MIV_XDMAV_CFG0_BOOT_E_MASK                     0x00000002

#define REG_MIV_XDMAV_CFG0_PRH_REQ_SHIFT                   0
#define REG_MIV_XDMAV_CFG0_PRH_REQ_SIZE                    1
#define REG_MIV_XDMAV_CFG0_PRH_REQ_MASK                    0x00000001

#ifndef SDK_ASM
#define REG_MIV_XDMAV_CFG0_FIELD( num_ev, num_prh, num_ch, rst_ns, boot_e, prh_req ) \
    (u32)( \
    ((u32)(num_ev) << REG_MIV_XDMAV_CFG0_NUM_EV_SHIFT) | \
    ((u32)(num_prh) << REG_MIV_XDMAV_CFG0_NUM_PRH_SHIFT) | \
    ((u32)(num_ch) << REG_MIV_XDMAV_CFG0_NUM_CH_SHIFT) | \
    ((u32)(rst_ns) << REG_MIV_XDMAV_CFG0_RST_NS_SHIFT) | \
    ((u32)(boot_e) << REG_MIV_XDMAV_CFG0_BOOT_E_SHIFT) | \
    ((u32)(prh_req) << REG_MIV_XDMAV_CFG0_PRH_REQ_SHIFT))
#endif


/* XDMAV_CFG1 */

#define REG_MIV_XDMAV_CFG1_IC_LINES_SHIFT                  4
#define REG_MIV_XDMAV_CFG1_IC_LINES_SIZE                   3
#define REG_MIV_XDMAV_CFG1_IC_LINES_MASK                   0x00000070

#define REG_MIV_XDMAV_CFG1_IC_LEN_SHIFT                    0
#define REG_MIV_XDMAV_CFG1_IC_LEN_SIZE                     3
#define REG_MIV_XDMAV_CFG1_IC_LEN_MASK                     0x00000007

#ifndef SDK_ASM
#define REG_MIV_XDMAV_CFG1_FIELD( ic_lines, ic_len ) \
    (u32)( \
    ((u32)(ic_lines) << REG_MIV_XDMAV_CFG1_IC_LINES_SHIFT) | \
    ((u32)(ic_len) << REG_MIV_XDMAV_CFG1_IC_LEN_SHIFT))
#endif


/* XDMAV_CFG2 */

#define REG_MIV_XDMAV_CFG2_BOOT_ADR_SHIFT                  0
#define REG_MIV_XDMAV_CFG2_BOOT_ADR_SIZE                   32
#define REG_MIV_XDMAV_CFG2_BOOT_ADR_MASK                   0xffffffff

#ifndef SDK_ASM
#define REG_MIV_XDMAV_CFG2_FIELD( boot_adr ) \
    (u32)( \
    ((u32)(boot_adr) << REG_MIV_XDMAV_CFG2_BOOT_ADR_SHIFT))
#endif


/* XDMAV_CFG3 */

#define REG_MIV_XDMAV_CFG3_INS0_SHIFT                      0
#define REG_MIV_XDMAV_CFG3_INS0_SIZE                       1
#define REG_MIV_XDMAV_CFG3_INS0_MASK                       0x00000001

#ifndef SDK_ASM
#define REG_MIV_XDMAV_CFG3_FIELD( ins0 ) \
    (u32)( \
    ((u32)(ins0) << REG_MIV_XDMAV_CFG3_INS0_SHIFT))
#endif


/* XDMAV_CFG4 */

#define REG_MIV_XDMAV_CFG4_PNS0_SHIFT                      0
#define REG_MIV_XDMAV_CFG4_PNS0_SIZE                       1
#define REG_MIV_XDMAV_CFG4_PNS0_MASK                       0x00000001

#ifndef SDK_ASM
#define REG_MIV_XDMAV_CFG4_FIELD( pns0 ) \
    (u32)( \
    ((u32)(pns0) << REG_MIV_XDMAV_CFG4_PNS0_SHIFT))
#endif


/* XDMAV_CFGDN */

#define REG_MIV_XDMAV_CFGDN_DBF_LINES_SHIFT                20
#define REG_MIV_XDMAV_CFGDN_DBF_LINES_SIZE                 10
#define REG_MIV_XDMAV_CFGDN_DBF_LINES_MASK                 0x3ff00000

#define REG_MIV_XDMAV_CFGDN_RQ_LINES_SHIFT                 16
#define REG_MIV_XDMAV_CFGDN_RQ_LINES_SIZE                  4
#define REG_MIV_XDMAV_CFGDN_RQ_LINES_MASK                  0x000f0000

#define REG_MIV_XDMAV_CFGDN_R_CAP_SHIFT                    12
#define REG_MIV_XDMAV_CFGDN_R_CAP_SIZE                     3
#define REG_MIV_XDMAV_CFGDN_R_CAP_MASK                     0x00007000

#define REG_MIV_XDMAV_CFGDN_WQ_LINES_SHIFT                 8
#define REG_MIV_XDMAV_CFGDN_WQ_LINES_SIZE                  4
#define REG_MIV_XDMAV_CFGDN_WQ_LINES_MASK                  0x00000f00

#define REG_MIV_XDMAV_CFGDN_W_CAP_SHIFT                    4
#define REG_MIV_XDMAV_CFGDN_W_CAP_SIZE                     3
#define REG_MIV_XDMAV_CFGDN_W_CAP_MASK                     0x00000070

#define REG_MIV_XDMAV_CFGDN_AXI_WDH_SHIFT                  0
#define REG_MIV_XDMAV_CFGDN_AXI_WDH_SIZE                   3
#define REG_MIV_XDMAV_CFGDN_AXI_WDH_MASK                   0x00000007

#ifndef SDK_ASM
#define REG_MIV_XDMAV_CFGDN_FIELD( dbf_lines, rq_lines, r_cap, wq_lines, w_cap, axi_wdh ) \
    (u32)( \
    ((u32)(dbf_lines) << REG_MIV_XDMAV_CFGDN_DBF_LINES_SHIFT) | \
    ((u32)(rq_lines) << REG_MIV_XDMAV_CFGDN_RQ_LINES_SHIFT) | \
    ((u32)(r_cap) << REG_MIV_XDMAV_CFGDN_R_CAP_SHIFT) | \
    ((u32)(wq_lines) << REG_MIV_XDMAV_CFGDN_WQ_LINES_SHIFT) | \
    ((u32)(w_cap) << REG_MIV_XDMAV_CFGDN_W_CAP_SHIFT) | \
    ((u32)(axi_wdh) << REG_MIV_XDMAV_CFGDN_AXI_WDH_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_MIV_H_ */
#endif
