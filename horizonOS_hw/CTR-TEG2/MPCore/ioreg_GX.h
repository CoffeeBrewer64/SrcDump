/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/MPCore/ioreg_GX.h

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
#ifndef NN_HW_CTR_TEG2_MPCORE_IOREG_GX_H_
#define NN_HW_CTR_TEG2_MPCORE_IOREG_GX_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* Y2R_CNT */

#define REG_Y2R_CNT_OFFSET                                 0x102000
#define REG_Y2R_CNT_ADDR                                   (HW_REG_BASE + REG_Y2R_CNT_OFFSET)
#define reg_GX_Y2R_CNT                                     (*( REGType32v *) REG_Y2R_CNT_ADDR)

/* Y2R_HDOT */

#define REG_Y2R_HDOT_OFFSET                                0x102004
#define REG_Y2R_HDOT_ADDR                                  (HW_REG_BASE + REG_Y2R_HDOT_OFFSET)
#define reg_GX_Y2R_HDOT                                    (*( REGType16v *) REG_Y2R_HDOT_ADDR)

/* Y2R_VLINE */

#define REG_Y2R_VLINE_OFFSET                               0x102006
#define REG_Y2R_VLINE_ADDR                                 (HW_REG_BASE + REG_Y2R_VLINE_OFFSET)
#define reg_GX_Y2R_VLINE                                   (*( REGType16v *) REG_Y2R_VLINE_ADDR)

/* Y2R_FLUSH */

#define REG_Y2R_FLUSH_OFFSET                               0x102008
#define REG_Y2R_FLUSH_ADDR                                 (HW_REG_BASE + REG_Y2R_FLUSH_OFFSET)
#define reg_GX_Y2R_FLUSH                                   (*( REGType16v *) REG_Y2R_FLUSH_ADDR)

/* Y2R_YA */

#define REG_Y2R_YA_OFFSET                                  0x102010
#define REG_Y2R_YA_ADDR                                    (HW_REG_BASE + REG_Y2R_YA_OFFSET)
#define reg_GX_Y2R_YA                                      (*( REGType16v *) REG_Y2R_YA_ADDR)

/* Y2R_RV */

#define REG_Y2R_RV_OFFSET                                  0x102012
#define REG_Y2R_RV_ADDR                                    (HW_REG_BASE + REG_Y2R_RV_OFFSET)
#define reg_GX_Y2R_RV                                      (*( REGType16v *) REG_Y2R_RV_ADDR)

/* Y2R_GV */

#define REG_Y2R_GV_OFFSET                                  0x102014
#define REG_Y2R_GV_ADDR                                    (HW_REG_BASE + REG_Y2R_GV_OFFSET)
#define reg_GX_Y2R_GV                                      (*( REGType16v *) REG_Y2R_GV_ADDR)

/* Y2R_GU */

#define REG_Y2R_GU_OFFSET                                  0x102016
#define REG_Y2R_GU_ADDR                                    (HW_REG_BASE + REG_Y2R_GU_OFFSET)
#define reg_GX_Y2R_GU                                      (*( REGType16v *) REG_Y2R_GU_ADDR)

/* Y2R_BU */

#define REG_Y2R_BU_OFFSET                                  0x102018
#define REG_Y2R_BU_ADDR                                    (HW_REG_BASE + REG_Y2R_BU_OFFSET)
#define reg_GX_Y2R_BU                                      (*( REGType16v *) REG_Y2R_BU_ADDR)

/* Y2R_RO */

#define REG_Y2R_RO_OFFSET                                  0x10201a
#define REG_Y2R_RO_ADDR                                    (HW_REG_BASE + REG_Y2R_RO_OFFSET)
#define reg_GX_Y2R_RO                                      (*( REGType16v *) REG_Y2R_RO_ADDR)

/* Y2R_GO */

#define REG_Y2R_GO_OFFSET                                  0x10201c
#define REG_Y2R_GO_ADDR                                    (HW_REG_BASE + REG_Y2R_GO_OFFSET)
#define reg_GX_Y2R_GO                                      (*( REGType16v *) REG_Y2R_GO_ADDR)

/* Y2R_BO */

#define REG_Y2R_BO_OFFSET                                  0x10201e
#define REG_Y2R_BO_ADDR                                    (HW_REG_BASE + REG_Y2R_BO_OFFSET)
#define reg_GX_Y2R_BO                                      (*( REGType16v *) REG_Y2R_BO_ADDR)

/* Y2R_ALPHA */

#define REG_Y2R_ALPHA_OFFSET                               0x102020
#define REG_Y2R_ALPHA_ADDR                                 (HW_REG_BASE + REG_Y2R_ALPHA_OFFSET)
#define reg_GX_Y2R_ALPHA                                   (*( REGType16v *) REG_Y2R_ALPHA_ADDR)

/* Y2R_DITPAT0 */

#define REG_Y2R_DITPAT0_OFFSET                             0x102100
#define REG_Y2R_DITPAT0_ADDR                               (HW_REG_BASE + REG_Y2R_DITPAT0_OFFSET)
#define reg_GX_Y2R_DITPAT0                                 (*( REGType16v *) REG_Y2R_DITPAT0_ADDR)

/* Y2R_DITPAT1 */

#define REG_Y2R_DITPAT1_OFFSET                             0x102108
#define REG_Y2R_DITPAT1_ADDR                               (HW_REG_BASE + REG_Y2R_DITPAT1_OFFSET)
#define reg_GX_Y2R_DITPAT1                                 (*( REGType16v *) REG_Y2R_DITPAT1_ADDR)

/* Y2R_DITPAT2 */

#define REG_Y2R_DITPAT2_OFFSET                             0x102110
#define REG_Y2R_DITPAT2_ADDR                               (HW_REG_BASE + REG_Y2R_DITPAT2_OFFSET)
#define reg_GX_Y2R_DITPAT2                                 (*( REGType16v *) REG_Y2R_DITPAT2_ADDR)

/* Y2R_DITPAT3 */

#define REG_Y2R_DITPAT3_OFFSET                             0x102118
#define REG_Y2R_DITPAT3_ADDR                               (HW_REG_BASE + REG_Y2R_DITPAT3_OFFSET)
#define reg_GX_Y2R_DITPAT3                                 (*( REGType16v *) REG_Y2R_DITPAT3_ADDR)

/* Y2R_Y0 */

#define REG_Y2R_Y0_OFFSET                                  0x302000
#define REG_Y2R_Y0_ADDR                                    (HW_REG_BASE + REG_Y2R_Y0_OFFSET)
#define reg_GX_Y2R_Y0                                      (*( REGType32v *) REG_Y2R_Y0_ADDR)

/* Y2R_U0 */

#define REG_Y2R_U0_OFFSET                                  0x302080
#define REG_Y2R_U0_ADDR                                    (HW_REG_BASE + REG_Y2R_U0_OFFSET)
#define reg_GX_Y2R_U0                                      (*( REGType32v *) REG_Y2R_U0_ADDR)

/* Y2R_V0 */

#define REG_Y2R_V0_OFFSET                                  0x302100
#define REG_Y2R_V0_ADDR                                    (HW_REG_BASE + REG_Y2R_V0_OFFSET)
#define reg_GX_Y2R_V0                                      (*( REGType32v *) REG_Y2R_V0_ADDR)

/* Y2R_YUV0 */

#define REG_Y2R_YUV0_OFFSET                                0x302180
#define REG_Y2R_YUV0_ADDR                                  (HW_REG_BASE + REG_Y2R_YUV0_OFFSET)
#define reg_GX_Y2R_YUV0                                    (*( REGType32v *) REG_Y2R_YUV0_ADDR)

/* Y2R_RGB0 */

#define REG_Y2R_RGB0_OFFSET                                0x302200
#define REG_Y2R_RGB0_ADDR                                  (HW_REG_BASE + REG_Y2R_RGB0_OFFSET)
#define reg_GX_Y2R_RGB0                                    (*( REGType32v *) REG_Y2R_RGB0_ADDR)

/* PSC_ID */

#define REG_PSC_ID_OFFSET                                  0x400000
#define REG_PSC_ID_ADDR                                    (HW_REG_BASE + REG_PSC_ID_OFFSET)
#define reg_GX_PSC_ID                                      (*(const REGType32v *) REG_PSC_ID_ADDR)

/* PSC_CLK */

#define REG_PSC_CLK_OFFSET                                 0x400004
#define REG_PSC_CLK_ADDR                                   (HW_REG_BASE + REG_PSC_CLK_OFFSET)
#define reg_GX_PSC_CLK                                     (*( REGType32v *) REG_PSC_CLK_ADDR)

/* PSC_FILL0_ADR_S */

#define REG_PSC_FILL0_ADR_S_OFFSET                         0x400010
#define REG_PSC_FILL0_ADR_S_ADDR                           (HW_REG_BASE + REG_PSC_FILL0_ADR_S_OFFSET)
#define reg_GX_PSC_FILL0_ADR_S                             (*( REGType32v *) REG_PSC_FILL0_ADR_S_ADDR)

/* PSC_FILL0_ADR_E */

#define REG_PSC_FILL0_ADR_E_OFFSET                         0x400014
#define REG_PSC_FILL0_ADR_E_ADDR                           (HW_REG_BASE + REG_PSC_FILL0_ADR_E_OFFSET)
#define reg_GX_PSC_FILL0_ADR_E                             (*( REGType32v *) REG_PSC_FILL0_ADR_E_ADDR)

/* PSC_FILL0_DATA */

#define REG_PSC_FILL0_DATA_OFFSET                          0x400018
#define REG_PSC_FILL0_DATA_ADDR                            (HW_REG_BASE + REG_PSC_FILL0_DATA_OFFSET)
#define reg_GX_PSC_FILL0_DATA                              (*( REGType32v *) REG_PSC_FILL0_DATA_ADDR)

/* PSC_FILL0_CNT */

#define REG_PSC_FILL0_CNT_OFFSET                           0x40001c
#define REG_PSC_FILL0_CNT_ADDR                             (HW_REG_BASE + REG_PSC_FILL0_CNT_OFFSET)
#define reg_GX_PSC_FILL0_CNT                               (*( REGType32v *) REG_PSC_FILL0_CNT_ADDR)

/* PSC_FILL1_ADR_S */

#define REG_PSC_FILL1_ADR_S_OFFSET                         0x400020
#define REG_PSC_FILL1_ADR_S_ADDR                           (HW_REG_BASE + REG_PSC_FILL1_ADR_S_OFFSET)
#define reg_GX_PSC_FILL1_ADR_S                             (*( REGType32v *) REG_PSC_FILL1_ADR_S_ADDR)

/* PSC_FILL1_ADR_E */

#define REG_PSC_FILL1_ADR_E_OFFSET                         0x400024
#define REG_PSC_FILL1_ADR_E_ADDR                           (HW_REG_BASE + REG_PSC_FILL1_ADR_E_OFFSET)
#define reg_GX_PSC_FILL1_ADR_E                             (*( REGType32v *) REG_PSC_FILL1_ADR_E_ADDR)

/* PSC_FILL1_DATA */

#define REG_PSC_FILL1_DATA_OFFSET                          0x400028
#define REG_PSC_FILL1_DATA_ADDR                            (HW_REG_BASE + REG_PSC_FILL1_DATA_OFFSET)
#define reg_GX_PSC_FILL1_DATA                              (*( REGType32v *) REG_PSC_FILL1_DATA_ADDR)

/* PSC_FILL1_CNT */

#define REG_PSC_FILL1_CNT_OFFSET                           0x40002c
#define REG_PSC_FILL1_CNT_ADDR                             (HW_REG_BASE + REG_PSC_FILL1_CNT_OFFSET)
#define reg_GX_PSC_FILL1_CNT                               (*( REGType32v *) REG_PSC_FILL1_CNT_ADDR)

/* PSC_SRAM_MODE */

#define REG_PSC_SRAM_MODE_OFFSET                           0x400030
#define REG_PSC_SRAM_MODE_ADDR                             (HW_REG_BASE + REG_PSC_SRAM_MODE_OFFSET)
#define reg_GX_PSC_SRAM_MODE                               (*( REGType32v *) REG_PSC_SRAM_MODE_ADDR)

/* PSC_INT_STATUS */

#define REG_PSC_INT_STATUS_OFFSET                          0x400034
#define REG_PSC_INT_STATUS_ADDR                            (HW_REG_BASE + REG_PSC_INT_STATUS_OFFSET)
#define reg_GX_PSC_INT_STATUS                              (*(const REGType32v *) REG_PSC_INT_STATUS_ADDR)

/* PSC_PMI_PRIORITY0 */

#define REG_PSC_PMI_PRIORITY0_OFFSET                       0x400050
#define REG_PSC_PMI_PRIORITY0_ADDR                         (HW_REG_BASE + REG_PSC_PMI_PRIORITY0_OFFSET)
#define reg_GX_PSC_PMI_PRIORITY0                           (*( REGType32v *) REG_PSC_PMI_PRIORITY0_ADDR)

/* PSC_PMI_PRIORITY1 */

#define REG_PSC_PMI_PRIORITY1_OFFSET                       0x400054
#define REG_PSC_PMI_PRIORITY1_ADDR                         (HW_REG_BASE + REG_PSC_PMI_PRIORITY1_OFFSET)
#define reg_GX_PSC_PMI_PRIORITY1                           (*( REGType32v *) REG_PSC_PMI_PRIORITY1_ADDR)

/* PSC_DEBUG */

#define REG_PSC_DEBUG_OFFSET                               0x400058
#define REG_PSC_DEBUG_ADDR                                 (HW_REG_BASE + REG_PSC_DEBUG_OFFSET)
#define reg_GX_PSC_DEBUG                                   (*(const REGType32v *) REG_PSC_DEBUG_ADDR)

/* PPF_SRC_ADR */

#define REG_PPF_SRC_ADR_OFFSET                             0x400c00
#define REG_PPF_SRC_ADR_ADDR                               (HW_REG_BASE + REG_PPF_SRC_ADR_OFFSET)
#define reg_GX_PPF_SRC_ADR                                 (*( REGType32v *) REG_PPF_SRC_ADR_ADDR)

/* PPF_DST_ADR */

#define REG_PPF_DST_ADR_OFFSET                             0x400c04
#define REG_PPF_DST_ADR_ADDR                               (HW_REG_BASE + REG_PPF_DST_ADR_OFFSET)
#define reg_GX_PPF_DST_ADR                                 (*( REGType32v *) REG_PPF_DST_ADR_ADDR)

/* PPF_SIZE */

#define REG_PPF_SIZE_OFFSET                                0x400c08
#define REG_PPF_SIZE_ADDR                                  (HW_REG_BASE + REG_PPF_SIZE_OFFSET)
#define reg_GX_PPF_SIZE                                    (*( REGType32v *) REG_PPF_SIZE_ADDR)

/* PPF_VSIZE */

#define REG_PPF_VSIZE_OFFSET                               0x400c0c
#define REG_PPF_VSIZE_ADDR                                 (HW_REG_BASE + REG_PPF_VSIZE_OFFSET)
#define reg_GX_PPF_VSIZE                                   (*( REGType32v *) REG_PPF_VSIZE_ADDR)

/* PPF_MODE */

#define REG_PPF_MODE_OFFSET                                0x400c10
#define REG_PPF_MODE_ADDR                                  (HW_REG_BASE + REG_PPF_MODE_OFFSET)
#define reg_GX_PPF_MODE                                    (*( REGType32v *) REG_PPF_MODE_ADDR)

/* PPF_INTERVAL */

#define REG_PPF_INTERVAL_OFFSET                            0x400c14
#define REG_PPF_INTERVAL_ADDR                              (HW_REG_BASE + REG_PPF_INTERVAL_OFFSET)
#define reg_GX_PPF_INTERVAL                                (*( REGType32v *) REG_PPF_INTERVAL_ADDR)

/* PPF_START */

#define REG_PPF_START_OFFSET                               0x400c18
#define REG_PPF_START_ADDR                                 (HW_REG_BASE + REG_PPF_START_OFFSET)
#define reg_GX_PPF_START                                   (*( REGType32v *) REG_PPF_START_ADDR)

/* PPF_WORK_LINE */

#define REG_PPF_WORK_LINE_OFFSET                           0x400c1c
#define REG_PPF_WORK_LINE_ADDR                             (HW_REG_BASE + REG_PPF_WORK_LINE_OFFSET)
#define reg_GX_PPF_WORK_LINE                               (*( REGType32v *) REG_PPF_WORK_LINE_ADDR)

/* PPF_DMA_SIZE */

#define REG_PPF_DMA_SIZE_OFFSET                            0x400c20
#define REG_PPF_DMA_SIZE_ADDR                              (HW_REG_BASE + REG_PPF_DMA_SIZE_OFFSET)
#define reg_GX_PPF_DMA_SIZE                                (*( REGType32v *) REG_PPF_DMA_SIZE_ADDR)

/* PPF_DMA_SRC_INTERVAL */

#define REG_PPF_DMA_SRC_INTERVAL_OFFSET                    0x400c24
#define REG_PPF_DMA_SRC_INTERVAL_ADDR                      (HW_REG_BASE + REG_PPF_DMA_SRC_INTERVAL_OFFSET)
#define reg_GX_PPF_DMA_SRC_INTERVAL                        (*( REGType32v *) REG_PPF_DMA_SRC_INTERVAL_ADDR)

/* PPF_DMA_DST_INTERVAL */

#define REG_PPF_DMA_DST_INTERVAL_OFFSET                    0x400c28
#define REG_PPF_DMA_DST_INTERVAL_ADDR                      (HW_REG_BASE + REG_PPF_DMA_DST_INTERVAL_OFFSET)
#define reg_GX_PPF_DMA_DST_INTERVAL                        (*( REGType32v *) REG_PPF_DMA_DST_INTERVAL_ADDR)

/* P3D_REG_B0 */

#define REG_P3D_REG_B0_OFFSET                              0x401000
#define REG_P3D_REG_B0_ADDR                                (HW_REG_BASE + REG_P3D_REG_B0_OFFSET)
#define reg_GX_P3D_REG_B0                                  (*( REGType32v *) REG_P3D_REG_B0_ADDR)

/* P3D_REG_F0 */

#define REG_P3D_REG_F0_OFFSET                              0x401040
#define REG_P3D_REG_F0_ADDR                                (HW_REG_BASE + REG_P3D_REG_F0_OFFSET)
#define reg_GX_P3D_REG_F0                                  (*( REGType32v *) REG_P3D_REG_F0_ADDR)

/* P3D_REG_IV0 */

#define REG_P3D_REG_IV0_OFFSET                             0x401080
#define REG_P3D_REG_IV0_ADDR                               (HW_REG_BASE + REG_P3D_REG_IV0_OFFSET)
#define reg_GX_P3D_REG_IV0                                 (*( REGType32v *) REG_P3D_REG_IV0_ADDR)

/* P3D_REG_MASK0 */

#define REG_P3D_REG_MASK0_OFFSET                           0x4010C0
#define REG_P3D_REG_MASK0_ADDR                             (HW_REG_BASE + REG_P3D_REG_MASK0_OFFSET)
#define reg_GX_P3D_REG_MASK0                               (*( REGType32v *) REG_P3D_REG_MASK0_ADDR)

/* P3D_INT_CLK */

#define REG_P3D_INT_CLK_OFFSET                             0x4010D0
#define REG_P3D_INT_CLK_ADDR                               (HW_REG_BASE + REG_P3D_INT_CLK_OFFSET)
#define reg_GX_P3D_INT_CLK                                 (*( REGType32v *) REG_P3D_INT_CLK_ADDR)

/* P3D_TB_GAS_ACC_MAX */

#define REG_P3D_TB_GAS_ACC_MAX_OFFSET                      0x401394
#define REG_P3D_TB_GAS_ACC_MAX_ADDR                        (HW_REG_BASE + REG_P3D_TB_GAS_ACC_MAX_OFFSET)
#define reg_GX_P3D_TB_GAS_ACC_MAX                          (*( REGType32v *) REG_P3D_TB_GAS_ACC_MAX_ADDR)

/* P3D_GAS_ACC_MAX_RESULT_INT */

#define REG_P3D_GAS_ACC_MAX_RESULT_INT_OFFSET              0x401494
#define REG_P3D_GAS_ACC_MAX_RESULT_INT_ADDR                (HW_REG_BASE + REG_P3D_GAS_ACC_MAX_RESULT_INT_OFFSET)
#define reg_GX_P3D_GAS_ACC_MAX_RESULT_INT                  (*( REGType32v *) REG_P3D_GAS_ACC_MAX_RESULT_INT_ADDR)

/* P3D_CMDLIST0_LEN */

#define REG_P3D_CMDLIST0_LEN_OFFSET                        0x4018E0
#define REG_P3D_CMDLIST0_LEN_ADDR                          (HW_REG_BASE + REG_P3D_CMDLIST0_LEN_OFFSET)
#define reg_GX_P3D_CMDLIST0_LEN                            (*( REGType32v *) REG_P3D_CMDLIST0_LEN_ADDR)

/* P3D_CMDLIST0_ADDR */

#define REG_P3D_CMDLIST0_ADDR_OFFSET                       0x4018E8
#define REG_P3D_CMDLIST0_ADDR_ADDR                         (HW_REG_BASE + REG_P3D_CMDLIST0_ADDR_OFFSET)
#define reg_GX_P3D_CMDLIST0_ADDR                           (*( REGType32v *) REG_P3D_CMDLIST0_ADDR_ADDR)

/* P3D_CMDLIST0_RUN */

#define REG_P3D_CMDLIST0_RUN_OFFSET                        0x4018F0
#define REG_P3D_CMDLIST0_RUN_ADDR                          (HW_REG_BASE + REG_P3D_CMDLIST0_RUN_OFFSET)
#define reg_GX_P3D_CMDLIST0_RUN                            (*( REGType32v *) REG_P3D_CMDLIST0_RUN_ADDR)


/*
 * Definitions of Register fields
 */


/* Y2R_CNT */

#define REG_GX_Y2R_CNT_E_SHIFT                             31
#define REG_GX_Y2R_CNT_E_SIZE                              1
#define REG_GX_Y2R_CNT_E_MASK                              0x80000000

#define REG_GX_Y2R_CNT_I_END_SHIFT                         30
#define REG_GX_Y2R_CNT_I_END_SIZE                          1
#define REG_GX_Y2R_CNT_I_END_MASK                          0x40000000

#define REG_GX_Y2R_CNT_I_DT_SHIFT                          29
#define REG_GX_Y2R_CNT_I_DT_SIZE                           1
#define REG_GX_Y2R_CNT_I_DT_MASK                           0x20000000

#define REG_GX_Y2R_CNT_RE_SHIFT                            28
#define REG_GX_Y2R_CNT_RE_SIZE                             1
#define REG_GX_Y2R_CNT_RE_MASK                             0x10000000

#define REG_GX_Y2R_CNT_YUV_SHIFT                           27
#define REG_GX_Y2R_CNT_YUV_SIZE                            1
#define REG_GX_Y2R_CNT_YUV_MASK                            0x08000000

#define REG_GX_Y2R_CNT_V_SHIFT                             26
#define REG_GX_Y2R_CNT_V_SIZE                              1
#define REG_GX_Y2R_CNT_V_MASK                              0x04000000

#define REG_GX_Y2R_CNT_U_SHIFT                             25
#define REG_GX_Y2R_CNT_U_SIZE                              1
#define REG_GX_Y2R_CNT_U_MASK                              0x02000000

#define REG_GX_Y2R_CNT_Y_SHIFT                             24
#define REG_GX_Y2R_CNT_Y_SIZE                              1
#define REG_GX_Y2R_CNT_Y_MASK                              0x01000000

#define REG_GX_Y2R_CNT_RDRQ_E_SHIFT                        23
#define REG_GX_Y2R_CNT_RDRQ_E_SIZE                         1
#define REG_GX_Y2R_CNT_RDRQ_E_MASK                         0x00800000

#define REG_GX_Y2R_CNT_WDRQ_E_SHIFT                        22
#define REG_GX_Y2R_CNT_WDRQ_E_SIZE                         1
#define REG_GX_Y2R_CNT_WDRQ_E_MASK                         0x00400000

#define REG_GX_Y2R_CNT_TD_E_SHIFT                          17
#define REG_GX_Y2R_CNT_TD_E_SIZE                           1
#define REG_GX_Y2R_CNT_TD_E_MASK                           0x00020000

#define REG_GX_Y2R_CNT_SD_E_SHIFT                          16
#define REG_GX_Y2R_CNT_SD_E_SIZE                           1
#define REG_GX_Y2R_CNT_SD_E_MASK                           0x00010000

#define REG_GX_Y2R_CNT_BLK_SHIFT                           12
#define REG_GX_Y2R_CNT_BLK_SIZE                            1
#define REG_GX_Y2R_CNT_BLK_MASK                            0x00001000

#define REG_GX_Y2R_CNT_ROT_SHIFT                           10
#define REG_GX_Y2R_CNT_ROT_SIZE                            2
#define REG_GX_Y2R_CNT_ROT_MASK                            0x00000c00

#define REG_GX_Y2R_CNT_OFMT_SHIFT                          8
#define REG_GX_Y2R_CNT_OFMT_SIZE                           2
#define REG_GX_Y2R_CNT_OFMT_MASK                           0x00000300

#define REG_GX_Y2R_CNT_IFMT_SHIFT                          0
#define REG_GX_Y2R_CNT_IFMT_SIZE                           3
#define REG_GX_Y2R_CNT_IFMT_MASK                           0x00000007

#ifndef SDK_ASM
#define REG_GX_Y2R_CNT_FIELD( e, i_end, i_dt, re, yuv, v, u, y, rdrq_e, wdrq_e, td_e, sd_e, blk, rot, ofmt, ifmt ) \
    (u32)( \
    ((u32)(e) << REG_GX_Y2R_CNT_E_SHIFT) | \
    ((u32)(i_end) << REG_GX_Y2R_CNT_I_END_SHIFT) | \
    ((u32)(i_dt) << REG_GX_Y2R_CNT_I_DT_SHIFT) | \
    ((u32)(re) << REG_GX_Y2R_CNT_RE_SHIFT) | \
    ((u32)(yuv) << REG_GX_Y2R_CNT_YUV_SHIFT) | \
    ((u32)(v) << REG_GX_Y2R_CNT_V_SHIFT) | \
    ((u32)(u) << REG_GX_Y2R_CNT_U_SHIFT) | \
    ((u32)(y) << REG_GX_Y2R_CNT_Y_SHIFT) | \
    ((u32)(rdrq_e) << REG_GX_Y2R_CNT_RDRQ_E_SHIFT) | \
    ((u32)(wdrq_e) << REG_GX_Y2R_CNT_WDRQ_E_SHIFT) | \
    ((u32)(td_e) << REG_GX_Y2R_CNT_TD_E_SHIFT) | \
    ((u32)(sd_e) << REG_GX_Y2R_CNT_SD_E_SHIFT) | \
    ((u32)(blk) << REG_GX_Y2R_CNT_BLK_SHIFT) | \
    ((u32)(rot) << REG_GX_Y2R_CNT_ROT_SHIFT) | \
    ((u32)(ofmt) << REG_GX_Y2R_CNT_OFMT_SHIFT) | \
    ((u32)(ifmt) << REG_GX_Y2R_CNT_IFMT_SHIFT))
#endif


/* Y2R_HDOT */

#define REG_GX_Y2R_HDOT_H_SHIFT                            3
#define REG_GX_Y2R_HDOT_H_SIZE                             7
#define REG_GX_Y2R_HDOT_H_MASK                             0x03f8

#ifndef SDK_ASM
#define REG_GX_Y2R_HDOT_FIELD( h ) \
    (u16)( \
    ((u32)(h) << REG_GX_Y2R_HDOT_H_SHIFT))
#endif


/* Y2R_VLINE */

#define REG_GX_Y2R_VLINE_V_SHIFT                           0
#define REG_GX_Y2R_VLINE_V_SIZE                            10
#define REG_GX_Y2R_VLINE_V_MASK                            0x03ff

#ifndef SDK_ASM
#define REG_GX_Y2R_VLINE_FIELD( v ) \
    (u16)( \
    ((u32)(v) << REG_GX_Y2R_VLINE_V_SHIFT))
#endif


/* Y2R_FLUSH */

/* Y2R_YA */

#define REG_GX_Y2R_YA_YA_SHIFT                             0
#define REG_GX_Y2R_YA_YA_SIZE                              10
#define REG_GX_Y2R_YA_YA_MASK                              0x03ff

#ifndef SDK_ASM
#define REG_GX_Y2R_YA_FIELD( ya ) \
    (u16)( \
    ((u32)(ya) << REG_GX_Y2R_YA_YA_SHIFT))
#endif


/* Y2R_RV */

#define REG_GX_Y2R_RV_RV_SHIFT                             0
#define REG_GX_Y2R_RV_RV_SIZE                              10
#define REG_GX_Y2R_RV_RV_MASK                              0x03ff

#ifndef SDK_ASM
#define REG_GX_Y2R_RV_FIELD( rv ) \
    (u16)( \
    ((u32)(rv) << REG_GX_Y2R_RV_RV_SHIFT))
#endif


/* Y2R_GV */

#define REG_GX_Y2R_GV_GV_SHIFT                             0
#define REG_GX_Y2R_GV_GV_SIZE                              10
#define REG_GX_Y2R_GV_GV_MASK                              0x03ff

#ifndef SDK_ASM
#define REG_GX_Y2R_GV_FIELD( gv ) \
    (u16)( \
    ((u32)(gv) << REG_GX_Y2R_GV_GV_SHIFT))
#endif


/* Y2R_GU */

#define REG_GX_Y2R_GU_GU_SHIFT                             0
#define REG_GX_Y2R_GU_GU_SIZE                              10
#define REG_GX_Y2R_GU_GU_MASK                              0x03ff

#ifndef SDK_ASM
#define REG_GX_Y2R_GU_FIELD( gu ) \
    (u16)( \
    ((u32)(gu) << REG_GX_Y2R_GU_GU_SHIFT))
#endif


/* Y2R_BU */

#define REG_GX_Y2R_BU_BU_SHIFT                             0
#define REG_GX_Y2R_BU_BU_SIZE                              10
#define REG_GX_Y2R_BU_BU_MASK                              0x03ff

#ifndef SDK_ASM
#define REG_GX_Y2R_BU_FIELD( bu ) \
    (u16)( \
    ((u32)(bu) << REG_GX_Y2R_BU_BU_SHIFT))
#endif


/* Y2R_RO */

/* Y2R_GO */

/* Y2R_BO */

/* Y2R_ALPHA */

#define REG_GX_Y2R_ALPHA_ALPHA_SHIFT                       0
#define REG_GX_Y2R_ALPHA_ALPHA_SIZE                        8
#define REG_GX_Y2R_ALPHA_ALPHA_MASK                        0x00ff

#ifndef SDK_ASM
#define REG_GX_Y2R_ALPHA_FIELD( alpha ) \
    (u16)( \
    ((u32)(alpha) << REG_GX_Y2R_ALPHA_ALPHA_SHIFT))
#endif


/* Y2R_DITPAT0 */

#define REG_GX_Y2R_DITPAT0_W3_SHIFT                        14
#define REG_GX_Y2R_DITPAT0_W3_SIZE                         2
#define REG_GX_Y2R_DITPAT0_W3_MASK                         0xc000

#define REG_GX_Y2R_DITPAT0_W2_SHIFT                        10
#define REG_GX_Y2R_DITPAT0_W2_SIZE                         2
#define REG_GX_Y2R_DITPAT0_W2_MASK                         0x0c00

#define REG_GX_Y2R_DITPAT0_W1_SHIFT                        6
#define REG_GX_Y2R_DITPAT0_W1_SIZE                         2
#define REG_GX_Y2R_DITPAT0_W1_MASK                         0x00c0

#define REG_GX_Y2R_DITPAT0_W0_SHIFT                        2
#define REG_GX_Y2R_DITPAT0_W0_SIZE                         2
#define REG_GX_Y2R_DITPAT0_W0_MASK                         0x000c

#ifndef SDK_ASM
#define REG_GX_Y2R_DITPAT0_FIELD( w3, w2, w1, w0 ) \
    (u16)( \
    ((u32)(w3) << REG_GX_Y2R_DITPAT0_W3_SHIFT) | \
    ((u32)(w2) << REG_GX_Y2R_DITPAT0_W2_SHIFT) | \
    ((u32)(w1) << REG_GX_Y2R_DITPAT0_W1_SHIFT) | \
    ((u32)(w0) << REG_GX_Y2R_DITPAT0_W0_SHIFT))
#endif


/* Y2R_DITPAT1 */

#define REG_GX_Y2R_DITPAT1_W3_SHIFT                        14
#define REG_GX_Y2R_DITPAT1_W3_SIZE                         2
#define REG_GX_Y2R_DITPAT1_W3_MASK                         0xc000

#define REG_GX_Y2R_DITPAT1_W2_SHIFT                        10
#define REG_GX_Y2R_DITPAT1_W2_SIZE                         2
#define REG_GX_Y2R_DITPAT1_W2_MASK                         0x0c00

#define REG_GX_Y2R_DITPAT1_W1_SHIFT                        6
#define REG_GX_Y2R_DITPAT1_W1_SIZE                         2
#define REG_GX_Y2R_DITPAT1_W1_MASK                         0x00c0

#define REG_GX_Y2R_DITPAT1_W0_SHIFT                        2
#define REG_GX_Y2R_DITPAT1_W0_SIZE                         2
#define REG_GX_Y2R_DITPAT1_W0_MASK                         0x000c

#ifndef SDK_ASM
#define REG_GX_Y2R_DITPAT1_FIELD( w3, w2, w1, w0 ) \
    (u16)( \
    ((u32)(w3) << REG_GX_Y2R_DITPAT1_W3_SHIFT) | \
    ((u32)(w2) << REG_GX_Y2R_DITPAT1_W2_SHIFT) | \
    ((u32)(w1) << REG_GX_Y2R_DITPAT1_W1_SHIFT) | \
    ((u32)(w0) << REG_GX_Y2R_DITPAT1_W0_SHIFT))
#endif


/* Y2R_DITPAT2 */

#define REG_GX_Y2R_DITPAT2_W3_SHIFT                        14
#define REG_GX_Y2R_DITPAT2_W3_SIZE                         2
#define REG_GX_Y2R_DITPAT2_W3_MASK                         0xc000

#define REG_GX_Y2R_DITPAT2_W2_SHIFT                        10
#define REG_GX_Y2R_DITPAT2_W2_SIZE                         2
#define REG_GX_Y2R_DITPAT2_W2_MASK                         0x0c00

#define REG_GX_Y2R_DITPAT2_W1_SHIFT                        6
#define REG_GX_Y2R_DITPAT2_W1_SIZE                         2
#define REG_GX_Y2R_DITPAT2_W1_MASK                         0x00c0

#define REG_GX_Y2R_DITPAT2_W0_SHIFT                        2
#define REG_GX_Y2R_DITPAT2_W0_SIZE                         2
#define REG_GX_Y2R_DITPAT2_W0_MASK                         0x000c

#ifndef SDK_ASM
#define REG_GX_Y2R_DITPAT2_FIELD( w3, w2, w1, w0 ) \
    (u16)( \
    ((u32)(w3) << REG_GX_Y2R_DITPAT2_W3_SHIFT) | \
    ((u32)(w2) << REG_GX_Y2R_DITPAT2_W2_SHIFT) | \
    ((u32)(w1) << REG_GX_Y2R_DITPAT2_W1_SHIFT) | \
    ((u32)(w0) << REG_GX_Y2R_DITPAT2_W0_SHIFT))
#endif


/* Y2R_DITPAT3 */

#define REG_GX_Y2R_DITPAT3_W3_SHIFT                        14
#define REG_GX_Y2R_DITPAT3_W3_SIZE                         2
#define REG_GX_Y2R_DITPAT3_W3_MASK                         0xc000

#define REG_GX_Y2R_DITPAT3_W2_SHIFT                        10
#define REG_GX_Y2R_DITPAT3_W2_SIZE                         2
#define REG_GX_Y2R_DITPAT3_W2_MASK                         0x0c00

#define REG_GX_Y2R_DITPAT3_W1_SHIFT                        6
#define REG_GX_Y2R_DITPAT3_W1_SIZE                         2
#define REG_GX_Y2R_DITPAT3_W1_MASK                         0x00c0

#define REG_GX_Y2R_DITPAT3_W0_SHIFT                        2
#define REG_GX_Y2R_DITPAT3_W0_SIZE                         2
#define REG_GX_Y2R_DITPAT3_W0_MASK                         0x000c

#ifndef SDK_ASM
#define REG_GX_Y2R_DITPAT3_FIELD( w3, w2, w1, w0 ) \
    (u16)( \
    ((u32)(w3) << REG_GX_Y2R_DITPAT3_W3_SHIFT) | \
    ((u32)(w2) << REG_GX_Y2R_DITPAT3_W2_SHIFT) | \
    ((u32)(w1) << REG_GX_Y2R_DITPAT3_W1_SHIFT) | \
    ((u32)(w0) << REG_GX_Y2R_DITPAT3_W0_SHIFT))
#endif


/* Y2R_Y0 */

/* Y2R_U0 */

/* Y2R_V0 */

/* Y2R_YUV0 */

/* Y2R_RGB0 */

/* PSC_ID */

/* PSC_CLK */

#define REG_GX_PSC_CLK_P3D_GEO_SHIFT                       18
#define REG_GX_PSC_CLK_P3D_GEO_SIZE                        1
#define REG_GX_PSC_CLK_P3D_GEO_MASK                        0x00040000

#define REG_GX_PSC_CLK_P3D_RAS1_SHIFT                      17
#define REG_GX_PSC_CLK_P3D_RAS1_SIZE                       1
#define REG_GX_PSC_CLK_P3D_RAS1_MASK                       0x00020000

#define REG_GX_PSC_CLK_P3D_RAS2_SHIFT                      16
#define REG_GX_PSC_CLK_P3D_RAS2_SIZE                       1
#define REG_GX_PSC_CLK_P3D_RAS2_MASK                       0x00010000

#define REG_GX_PSC_CLK_PPF_SHIFT                           9
#define REG_GX_PSC_CLK_PPF_SIZE                            1
#define REG_GX_PSC_CLK_PPF_MASK                            0x00000200

#define REG_GX_PSC_CLK_P3D_SHIFT                           8
#define REG_GX_PSC_CLK_P3D_SIZE                            1
#define REG_GX_PSC_CLK_P3D_MASK                            0x00000100

#define REG_GX_PSC_CLK_M_SHIFT                             0
#define REG_GX_PSC_CLK_M_SIZE                              1
#define REG_GX_PSC_CLK_M_MASK                              0x00000001

#ifndef SDK_ASM
#define REG_GX_PSC_CLK_FIELD( p3d_geo, p3d_ras1, p3d_ras2, ppf, p3d, m ) \
    (u32)( \
    ((u32)(p3d_geo) << REG_GX_PSC_CLK_P3D_GEO_SHIFT) | \
    ((u32)(p3d_ras1) << REG_GX_PSC_CLK_P3D_RAS1_SHIFT) | \
    ((u32)(p3d_ras2) << REG_GX_PSC_CLK_P3D_RAS2_SHIFT) | \
    ((u32)(ppf) << REG_GX_PSC_CLK_PPF_SHIFT) | \
    ((u32)(p3d) << REG_GX_PSC_CLK_P3D_SHIFT) | \
    ((u32)(m) << REG_GX_PSC_CLK_M_SHIFT))
#endif


/* PSC_FILL0_ADR_S */

#define REG_GX_PSC_FILL0_ADR_S_ADR_SHIFT                   1
#define REG_GX_PSC_FILL0_ADR_S_ADR_SIZE                    28
#define REG_GX_PSC_FILL0_ADR_S_ADR_MASK                    0x1ffffffe

#ifndef SDK_ASM
#define REG_GX_PSC_FILL0_ADR_S_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_GX_PSC_FILL0_ADR_S_ADR_SHIFT))
#endif


/* PSC_FILL0_ADR_E */

#define REG_GX_PSC_FILL0_ADR_E_ADR_SHIFT                   1
#define REG_GX_PSC_FILL0_ADR_E_ADR_SIZE                    28
#define REG_GX_PSC_FILL0_ADR_E_ADR_MASK                    0x1ffffffe

#ifndef SDK_ASM
#define REG_GX_PSC_FILL0_ADR_E_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_GX_PSC_FILL0_ADR_E_ADR_SHIFT))
#endif


/* PSC_FILL0_DATA */

/* PSC_FILL0_CNT */

#define REG_GX_PSC_FILL0_CNT_BLEN_SHIFT                    16
#define REG_GX_PSC_FILL0_CNT_BLEN_SIZE                     5
#define REG_GX_PSC_FILL0_CNT_BLEN_MASK                     0x001f0000

#define REG_GX_PSC_FILL0_CNT_FMT_SHIFT                     8
#define REG_GX_PSC_FILL0_CNT_FMT_SIZE                      2
#define REG_GX_PSC_FILL0_CNT_FMT_MASK                      0x00000300

#define REG_GX_PSC_FILL0_CNT_FIN_SHIFT                     1
#define REG_GX_PSC_FILL0_CNT_FIN_SIZE                      1
#define REG_GX_PSC_FILL0_CNT_FIN_MASK                      0x00000002

#define REG_GX_PSC_FILL0_CNT_ST_SHIFT                      0
#define REG_GX_PSC_FILL0_CNT_ST_SIZE                       1
#define REG_GX_PSC_FILL0_CNT_ST_MASK                       0x00000001

#ifndef SDK_ASM
#define REG_GX_PSC_FILL0_CNT_FIELD( blen, fmt, fin, st ) \
    (u32)( \
    ((u32)(blen) << REG_GX_PSC_FILL0_CNT_BLEN_SHIFT) | \
    ((u32)(fmt) << REG_GX_PSC_FILL0_CNT_FMT_SHIFT) | \
    ((u32)(fin) << REG_GX_PSC_FILL0_CNT_FIN_SHIFT) | \
    ((u32)(st) << REG_GX_PSC_FILL0_CNT_ST_SHIFT))
#endif


/* PSC_FILL1_ADR_S */

#define REG_GX_PSC_FILL1_ADR_S_ADR_SHIFT                   1
#define REG_GX_PSC_FILL1_ADR_S_ADR_SIZE                    28
#define REG_GX_PSC_FILL1_ADR_S_ADR_MASK                    0x1ffffffe

#ifndef SDK_ASM
#define REG_GX_PSC_FILL1_ADR_S_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_GX_PSC_FILL1_ADR_S_ADR_SHIFT))
#endif


/* PSC_FILL1_ADR_E */

#define REG_GX_PSC_FILL1_ADR_E_ADR_SHIFT                   1
#define REG_GX_PSC_FILL1_ADR_E_ADR_SIZE                    28
#define REG_GX_PSC_FILL1_ADR_E_ADR_MASK                    0x1ffffffe

#ifndef SDK_ASM
#define REG_GX_PSC_FILL1_ADR_E_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_GX_PSC_FILL1_ADR_E_ADR_SHIFT))
#endif


/* PSC_FILL1_DATA */

/* PSC_FILL1_CNT */

#define REG_GX_PSC_FILL1_CNT_BLEN_SHIFT                    16
#define REG_GX_PSC_FILL1_CNT_BLEN_SIZE                     5
#define REG_GX_PSC_FILL1_CNT_BLEN_MASK                     0x001f0000

#define REG_GX_PSC_FILL1_CNT_FMT_SHIFT                     8
#define REG_GX_PSC_FILL1_CNT_FMT_SIZE                      2
#define REG_GX_PSC_FILL1_CNT_FMT_MASK                      0x00000300

#define REG_GX_PSC_FILL1_CNT_FIN_SHIFT                     1
#define REG_GX_PSC_FILL1_CNT_FIN_SIZE                      1
#define REG_GX_PSC_FILL1_CNT_FIN_MASK                      0x00000002

#define REG_GX_PSC_FILL1_CNT_ST_SHIFT                      0
#define REG_GX_PSC_FILL1_CNT_ST_SIZE                       1
#define REG_GX_PSC_FILL1_CNT_ST_MASK                       0x00000001

#ifndef SDK_ASM
#define REG_GX_PSC_FILL1_CNT_FIELD( blen, fmt, fin, st ) \
    (u32)( \
    ((u32)(blen) << REG_GX_PSC_FILL1_CNT_BLEN_SHIFT) | \
    ((u32)(fmt) << REG_GX_PSC_FILL1_CNT_FMT_SHIFT) | \
    ((u32)(fin) << REG_GX_PSC_FILL1_CNT_FIN_SHIFT) | \
    ((u32)(st) << REG_GX_PSC_FILL1_CNT_ST_SHIFT))
#endif


/* PSC_SRAM_MODE */

#define REG_GX_PSC_SRAM_MODE_BANK_SHIFT                    16
#define REG_GX_PSC_SRAM_MODE_BANK_SIZE                     2
#define REG_GX_PSC_SRAM_MODE_BANK_MASK                     0x00030000

#define REG_GX_PSC_SRAM_MODE_STOP_B3_SHIFT                 11
#define REG_GX_PSC_SRAM_MODE_STOP_B3_SIZE                  1
#define REG_GX_PSC_SRAM_MODE_STOP_B3_MASK                  0x00000800

#define REG_GX_PSC_SRAM_MODE_STOP_B2_SHIFT                 10
#define REG_GX_PSC_SRAM_MODE_STOP_B2_SIZE                  1
#define REG_GX_PSC_SRAM_MODE_STOP_B2_MASK                  0x00000400

#define REG_GX_PSC_SRAM_MODE_STOP_B1_SHIFT                 9
#define REG_GX_PSC_SRAM_MODE_STOP_B1_SIZE                  1
#define REG_GX_PSC_SRAM_MODE_STOP_B1_MASK                  0x00000200

#define REG_GX_PSC_SRAM_MODE_STOP_B0_SHIFT                 8
#define REG_GX_PSC_SRAM_MODE_STOP_B0_SIZE                  1
#define REG_GX_PSC_SRAM_MODE_STOP_B0_MASK                  0x00000100

#define REG_GX_PSC_SRAM_MODE_REF_SHIFT                     0
#define REG_GX_PSC_SRAM_MODE_REF_SIZE                      1
#define REG_GX_PSC_SRAM_MODE_REF_MASK                      0x00000001

#ifndef SDK_ASM
#define REG_GX_PSC_SRAM_MODE_FIELD( bank, stop_b3, stop_b2, stop_b1, stop_b0, ref ) \
    (u32)( \
    ((u32)(bank) << REG_GX_PSC_SRAM_MODE_BANK_SHIFT) | \
    ((u32)(stop_b3) << REG_GX_PSC_SRAM_MODE_STOP_B3_SHIFT) | \
    ((u32)(stop_b2) << REG_GX_PSC_SRAM_MODE_STOP_B2_SHIFT) | \
    ((u32)(stop_b1) << REG_GX_PSC_SRAM_MODE_STOP_B1_SHIFT) | \
    ((u32)(stop_b0) << REG_GX_PSC_SRAM_MODE_STOP_B0_SHIFT) | \
    ((u32)(ref) << REG_GX_PSC_SRAM_MODE_REF_SHIFT))
#endif


/* PSC_INT_STATUS */

#define REG_GX_PSC_INT_STATUS_P3D_SHIFT                    31
#define REG_GX_PSC_INT_STATUS_P3D_SIZE                     1
#define REG_GX_PSC_INT_STATUS_P3D_MASK                     0x80000000

#define REG_GX_PSC_INT_STATUS_PPF_SHIFT                    30
#define REG_GX_PSC_INT_STATUS_PPF_SIZE                     1
#define REG_GX_PSC_INT_STATUS_PPF_MASK                     0x40000000

#define REG_GX_PSC_INT_STATUS_PDC1_SHIFT                   29
#define REG_GX_PSC_INT_STATUS_PDC1_SIZE                    1
#define REG_GX_PSC_INT_STATUS_PDC1_MASK                    0x20000000

#define REG_GX_PSC_INT_STATUS_PDC0_SHIFT                   28
#define REG_GX_PSC_INT_STATUS_PDC0_SIZE                    1
#define REG_GX_PSC_INT_STATUS_PDC0_MASK                    0x10000000

#define REG_GX_PSC_INT_STATUS_PSC1_SHIFT                   27
#define REG_GX_PSC_INT_STATUS_PSC1_SIZE                    1
#define REG_GX_PSC_INT_STATUS_PSC1_MASK                    0x08000000

#define REG_GX_PSC_INT_STATUS_PSC0_SHIFT                   26
#define REG_GX_PSC_INT_STATUS_PSC0_SIZE                    1
#define REG_GX_PSC_INT_STATUS_PSC0_MASK                    0x04000000

#ifndef SDK_ASM
#define REG_GX_PSC_INT_STATUS_FIELD( p3d, ppf, pdc1, pdc0, psc1, psc0 ) \
    (u32)( \
    ((u32)(p3d) << REG_GX_PSC_INT_STATUS_P3D_SHIFT) | \
    ((u32)(ppf) << REG_GX_PSC_INT_STATUS_PPF_SHIFT) | \
    ((u32)(pdc1) << REG_GX_PSC_INT_STATUS_PDC1_SHIFT) | \
    ((u32)(pdc0) << REG_GX_PSC_INT_STATUS_PDC0_SHIFT) | \
    ((u32)(psc1) << REG_GX_PSC_INT_STATUS_PSC1_SHIFT) | \
    ((u32)(psc0) << REG_GX_PSC_INT_STATUS_PSC0_SHIFT))
#endif


/* PSC_PMI_PRIORITY0 */

#define REG_GX_PSC_PMI_PRIORITY0_CU1_SHIFT                 28
#define REG_GX_PSC_PMI_PRIORITY0_CU1_SIZE                  4
#define REG_GX_PSC_PMI_PRIORITY0_CU1_MASK                  0xf0000000

#define REG_GX_PSC_PMI_PRIORITY0_CU0_SHIFT                 24
#define REG_GX_PSC_PMI_PRIORITY0_CU0_SIZE                  4
#define REG_GX_PSC_PMI_PRIORITY0_CU0_MASK                  0x0f000000

#define REG_GX_PSC_PMI_PRIORITY0_TEX_SHIFT                 20
#define REG_GX_PSC_PMI_PRIORITY0_TEX_SIZE                  4
#define REG_GX_PSC_PMI_PRIORITY0_TEX_MASK                  0x00f00000

#define REG_GX_PSC_PMI_PRIORITY0_GEO_SHIFT                 16
#define REG_GX_PSC_PMI_PRIORITY0_GEO_SIZE                  4
#define REG_GX_PSC_PMI_PRIORITY0_GEO_MASK                  0x000f0000

#define REG_GX_PSC_PMI_PRIORITY0_PPF_D_SHIFT               12
#define REG_GX_PSC_PMI_PRIORITY0_PPF_D_SIZE                4
#define REG_GX_PSC_PMI_PRIORITY0_PPF_D_MASK                0x0000f000

#define REG_GX_PSC_PMI_PRIORITY0_PPF_S_SHIFT               8
#define REG_GX_PSC_PMI_PRIORITY0_PPF_S_SIZE                4
#define REG_GX_PSC_PMI_PRIORITY0_PPF_S_MASK                0x00000f00

#define REG_GX_PSC_PMI_PRIORITY0_LCD1_SHIFT                4
#define REG_GX_PSC_PMI_PRIORITY0_LCD1_SIZE                 4
#define REG_GX_PSC_PMI_PRIORITY0_LCD1_MASK                 0x000000f0

#define REG_GX_PSC_PMI_PRIORITY0_LCD0_SHIFT                0
#define REG_GX_PSC_PMI_PRIORITY0_LCD0_SIZE                 4
#define REG_GX_PSC_PMI_PRIORITY0_LCD0_MASK                 0x0000000f

#ifndef SDK_ASM
#define REG_GX_PSC_PMI_PRIORITY0_FIELD( cu1, cu0, tex, geo, ppf_d, ppf_s, lcd1, lcd0 ) \
    (u32)( \
    ((u32)(cu1) << REG_GX_PSC_PMI_PRIORITY0_CU1_SHIFT) | \
    ((u32)(cu0) << REG_GX_PSC_PMI_PRIORITY0_CU0_SHIFT) | \
    ((u32)(tex) << REG_GX_PSC_PMI_PRIORITY0_TEX_SHIFT) | \
    ((u32)(geo) << REG_GX_PSC_PMI_PRIORITY0_GEO_SHIFT) | \
    ((u32)(ppf_d) << REG_GX_PSC_PMI_PRIORITY0_PPF_D_SHIFT) | \
    ((u32)(ppf_s) << REG_GX_PSC_PMI_PRIORITY0_PPF_S_SHIFT) | \
    ((u32)(lcd1) << REG_GX_PSC_PMI_PRIORITY0_LCD1_SHIFT) | \
    ((u32)(lcd0) << REG_GX_PSC_PMI_PRIORITY0_LCD0_SHIFT))
#endif


/* PSC_PMI_PRIORITY1 */

#define REG_GX_PSC_PMI_PRIORITY1_PMF_1_SHIFT               8
#define REG_GX_PSC_PMI_PRIORITY1_PMF_1_SIZE                4
#define REG_GX_PSC_PMI_PRIORITY1_PMF_1_MASK                0x00000f00

#define REG_GX_PSC_PMI_PRIORITY1_PMF_0_SHIFT               4
#define REG_GX_PSC_PMI_PRIORITY1_PMF_0_SIZE                4
#define REG_GX_PSC_PMI_PRIORITY1_PMF_0_MASK                0x000000f0

#define REG_GX_PSC_PMI_PRIORITY1_PHI_SHIFT                 0
#define REG_GX_PSC_PMI_PRIORITY1_PHI_SIZE                  4
#define REG_GX_PSC_PMI_PRIORITY1_PHI_MASK                  0x0000000f

#ifndef SDK_ASM
#define REG_GX_PSC_PMI_PRIORITY1_FIELD( pmf_1, pmf_0, phi ) \
    (u32)( \
    ((u32)(pmf_1) << REG_GX_PSC_PMI_PRIORITY1_PMF_1_SHIFT) | \
    ((u32)(pmf_0) << REG_GX_PSC_PMI_PRIORITY1_PMF_0_SHIFT) | \
    ((u32)(phi) << REG_GX_PSC_PMI_PRIORITY1_PHI_SHIFT))
#endif


/* PSC_DEBUG */

/* PPF_SRC_ADR */

#define REG_GX_PPF_SRC_ADR_ADR_SHIFT                       1
#define REG_GX_PPF_SRC_ADR_ADR_SIZE                        28
#define REG_GX_PPF_SRC_ADR_ADR_MASK                        0x1ffffffe

#ifndef SDK_ASM
#define REG_GX_PPF_SRC_ADR_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_GX_PPF_SRC_ADR_ADR_SHIFT))
#endif


/* PPF_DST_ADR */

#define REG_GX_PPF_DST_ADR_ADR_SHIFT                       1
#define REG_GX_PPF_DST_ADR_ADR_SIZE                        28
#define REG_GX_PPF_DST_ADR_ADR_MASK                        0x1ffffffe

#ifndef SDK_ASM
#define REG_GX_PPF_DST_ADR_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_GX_PPF_DST_ADR_ADR_SHIFT))
#endif


/* PPF_SIZE */

#define REG_GX_PPF_SIZE_H_SHIFT                            16
#define REG_GX_PPF_SIZE_H_SIZE                             16
#define REG_GX_PPF_SIZE_H_MASK                             0xffff0000

#define REG_GX_PPF_SIZE_W_SHIFT                            0
#define REG_GX_PPF_SIZE_W_SIZE                             16
#define REG_GX_PPF_SIZE_W_MASK                             0x0000ffff

#ifndef SDK_ASM
#define REG_GX_PPF_SIZE_FIELD( h, w ) \
    (u32)( \
    ((u32)(h) << REG_GX_PPF_SIZE_H_SHIFT) | \
    ((u32)(w) << REG_GX_PPF_SIZE_W_SHIFT))
#endif


/* PPF_VSIZE */

#define REG_GX_PPF_VSIZE_H_SHIFT                           16
#define REG_GX_PPF_VSIZE_H_SIZE                            16
#define REG_GX_PPF_VSIZE_H_MASK                            0xffff0000

#define REG_GX_PPF_VSIZE_W_SHIFT                           0
#define REG_GX_PPF_VSIZE_W_SIZE                            16
#define REG_GX_PPF_VSIZE_W_MASK                            0x0000ffff

#ifndef SDK_ASM
#define REG_GX_PPF_VSIZE_FIELD( h, w ) \
    (u32)( \
    ((u32)(h) << REG_GX_PPF_VSIZE_H_SHIFT) | \
    ((u32)(w) << REG_GX_PPF_VSIZE_W_SHIFT))
#endif


/* PPF_MODE */

#define REG_GX_PPF_MODE_AAM_SHIFT                          24
#define REG_GX_PPF_MODE_AAM_SIZE                           2
#define REG_GX_PPF_MODE_AAM_MASK                           0x03000000

#define REG_GX_PPF_MODE_BSZ_SHIFT                          16
#define REG_GX_PPF_MODE_BSZ_SIZE                           1
#define REG_GX_PPF_MODE_BSZ_MASK                           0x00010000

#define REG_GX_PPF_MODE_DFMT_SHIFT                         12
#define REG_GX_PPF_MODE_DFMT_SIZE                          3
#define REG_GX_PPF_MODE_DFMT_MASK                          0x00007000

#define REG_GX_PPF_MODE_SFMT_SHIFT                         8
#define REG_GX_PPF_MODE_SFMT_SIZE                          3
#define REG_GX_PPF_MODE_SFMT_MASK                          0x00000700

#define REG_GX_PPF_MODE_CROP_E_SHIFT                       2
#define REG_GX_PPF_MODE_CROP_E_SIZE                        1
#define REG_GX_PPF_MODE_CROP_E_MASK                        0x00000004

#define REG_GX_PPF_MODE_BLM_SHIFT                          1
#define REG_GX_PPF_MODE_BLM_SIZE                           1
#define REG_GX_PPF_MODE_BLM_MASK                           0x00000002

#define REG_GX_PPF_MODE_FLIP_E_SHIFT                       0
#define REG_GX_PPF_MODE_FLIP_E_SIZE                        1
#define REG_GX_PPF_MODE_FLIP_E_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_GX_PPF_MODE_FIELD( aam, bsz, dfmt, sfmt, crop_e, blm, flip_e ) \
    (u32)( \
    ((u32)(aam) << REG_GX_PPF_MODE_AAM_SHIFT) | \
    ((u32)(bsz) << REG_GX_PPF_MODE_BSZ_SHIFT) | \
    ((u32)(dfmt) << REG_GX_PPF_MODE_DFMT_SHIFT) | \
    ((u32)(sfmt) << REG_GX_PPF_MODE_SFMT_SHIFT) | \
    ((u32)(crop_e) << REG_GX_PPF_MODE_CROP_E_SHIFT) | \
    ((u32)(blm) << REG_GX_PPF_MODE_BLM_SHIFT) | \
    ((u32)(flip_e) << REG_GX_PPF_MODE_FLIP_E_SHIFT))
#endif


/* PPF_INTERVAL */

#define REG_GX_PPF_INTERVAL_W_SHIFT                        8
#define REG_GX_PPF_INTERVAL_W_SIZE                         8
#define REG_GX_PPF_INTERVAL_W_MASK                         0x0000ff00

#define REG_GX_PPF_INTERVAL_R_SHIFT                        0
#define REG_GX_PPF_INTERVAL_R_SIZE                         8
#define REG_GX_PPF_INTERVAL_R_MASK                         0x000000ff

#ifndef SDK_ASM
#define REG_GX_PPF_INTERVAL_FIELD( w, r ) \
    (u32)( \
    ((u32)(w) << REG_GX_PPF_INTERVAL_W_SHIFT) | \
    ((u32)(r) << REG_GX_PPF_INTERVAL_R_SHIFT))
#endif


/* PPF_START */

#define REG_GX_PPF_START_IF_SHIFT                          8
#define REG_GX_PPF_START_IF_SIZE                           1
#define REG_GX_PPF_START_IF_MASK                           0x00000100

#define REG_GX_PPF_START_ST_SHIFT                          0
#define REG_GX_PPF_START_ST_SIZE                           1
#define REG_GX_PPF_START_ST_MASK                           0x00000001

#ifndef SDK_ASM
#define REG_GX_PPF_START_FIELD( if, st ) \
    (u32)( \
    ((u32)(if) << REG_GX_PPF_START_IF_SHIFT) | \
    ((u32)(st) << REG_GX_PPF_START_ST_SHIFT))
#endif


/* PPF_WORK_LINE */

/* PPF_DMA_SIZE */

#define REG_GX_PPF_DMA_SIZE_SIZE_SHIFT                     0
#define REG_GX_PPF_DMA_SIZE_SIZE_SIZE                      32
#define REG_GX_PPF_DMA_SIZE_SIZE_MASK                      0xffffffff

#ifndef SDK_ASM
#define REG_GX_PPF_DMA_SIZE_FIELD( size ) \
    (u32)( \
    ((u32)(size) << REG_GX_PPF_DMA_SIZE_SIZE_SHIFT))
#endif


/* PPF_DMA_SRC_INTERVAL */

#define REG_GX_PPF_DMA_SRC_INTERVAL_IV_SHIFT               16
#define REG_GX_PPF_DMA_SRC_INTERVAL_IV_SIZE                16
#define REG_GX_PPF_DMA_SRC_INTERVAL_IV_MASK                0xffff0000

#define REG_GX_PPF_DMA_SRC_INTERVAL_V_SHIFT                0
#define REG_GX_PPF_DMA_SRC_INTERVAL_V_SIZE                 16
#define REG_GX_PPF_DMA_SRC_INTERVAL_V_MASK                 0x0000ffff

#ifndef SDK_ASM
#define REG_GX_PPF_DMA_SRC_INTERVAL_FIELD( iv, v ) \
    (u32)( \
    ((u32)(iv) << REG_GX_PPF_DMA_SRC_INTERVAL_IV_SHIFT) | \
    ((u32)(v) << REG_GX_PPF_DMA_SRC_INTERVAL_V_SHIFT))
#endif


/* PPF_DMA_DST_INTERVAL */

#define REG_GX_PPF_DMA_DST_INTERVAL_IV_SHIFT               16
#define REG_GX_PPF_DMA_DST_INTERVAL_IV_SIZE                16
#define REG_GX_PPF_DMA_DST_INTERVAL_IV_MASK                0xffff0000

#define REG_GX_PPF_DMA_DST_INTERVAL_V_SHIFT                0
#define REG_GX_PPF_DMA_DST_INTERVAL_V_SIZE                 16
#define REG_GX_PPF_DMA_DST_INTERVAL_V_MASK                 0x0000ffff

#ifndef SDK_ASM
#define REG_GX_PPF_DMA_DST_INTERVAL_FIELD( iv, v ) \
    (u32)( \
    ((u32)(iv) << REG_GX_PPF_DMA_DST_INTERVAL_IV_SHIFT) | \
    ((u32)(v) << REG_GX_PPF_DMA_DST_INTERVAL_V_SHIFT))
#endif


/* P3D_REG_B0 */

/* P3D_REG_F0 */

/* P3D_REG_IV0 */

/* P3D_REG_MASK0 */

#define REG_GX_P3D_REG_MASK0_M7_SHIFT                      28
#define REG_GX_P3D_REG_MASK0_M7_SIZE                       4
#define REG_GX_P3D_REG_MASK0_M7_MASK                       0xf0000000

#define REG_GX_P3D_REG_MASK0_M6_SHIFT                      24
#define REG_GX_P3D_REG_MASK0_M6_SIZE                       4
#define REG_GX_P3D_REG_MASK0_M6_MASK                       0x0f000000

#define REG_GX_P3D_REG_MASK0_M5_SHIFT                      20
#define REG_GX_P3D_REG_MASK0_M5_SIZE                       4
#define REG_GX_P3D_REG_MASK0_M5_MASK                       0x00f00000

#define REG_GX_P3D_REG_MASK0_M4_SHIFT                      16
#define REG_GX_P3D_REG_MASK0_M4_SIZE                       4
#define REG_GX_P3D_REG_MASK0_M4_MASK                       0x000f0000

#define REG_GX_P3D_REG_MASK0_M3_SHIFT                      12
#define REG_GX_P3D_REG_MASK0_M3_SIZE                       4
#define REG_GX_P3D_REG_MASK0_M3_MASK                       0x0000f000

#define REG_GX_P3D_REG_MASK0_M2_SHIFT                      8
#define REG_GX_P3D_REG_MASK0_M2_SIZE                       4
#define REG_GX_P3D_REG_MASK0_M2_MASK                       0x00000f00

#define REG_GX_P3D_REG_MASK0_M1_SHIFT                      4
#define REG_GX_P3D_REG_MASK0_M1_SIZE                       4
#define REG_GX_P3D_REG_MASK0_M1_MASK                       0x000000f0

#define REG_GX_P3D_REG_MASK0_M0_SHIFT                      0
#define REG_GX_P3D_REG_MASK0_M0_SIZE                       4
#define REG_GX_P3D_REG_MASK0_M0_MASK                       0x0000000f

#ifndef SDK_ASM
#define REG_GX_P3D_REG_MASK0_FIELD( m7, m6, m5, m4, m3, m2, m1, m0 ) \
    (u32)( \
    ((u32)(m7) << REG_GX_P3D_REG_MASK0_M7_SHIFT) | \
    ((u32)(m6) << REG_GX_P3D_REG_MASK0_M6_SHIFT) | \
    ((u32)(m5) << REG_GX_P3D_REG_MASK0_M5_SHIFT) | \
    ((u32)(m4) << REG_GX_P3D_REG_MASK0_M4_SHIFT) | \
    ((u32)(m3) << REG_GX_P3D_REG_MASK0_M3_SHIFT) | \
    ((u32)(m2) << REG_GX_P3D_REG_MASK0_M2_SHIFT) | \
    ((u32)(m1) << REG_GX_P3D_REG_MASK0_M1_SHIFT) | \
    ((u32)(m0) << REG_GX_P3D_REG_MASK0_M0_SHIFT))
#endif


/* P3D_INT_CLK */

#define REG_GX_P3D_INT_CLK_INT_CLK_SHIFT                   0
#define REG_GX_P3D_INT_CLK_INT_CLK_SIZE                    1
#define REG_GX_P3D_INT_CLK_INT_CLK_MASK                    0x00000001

#ifndef SDK_ASM
#define REG_GX_P3D_INT_CLK_FIELD( int_clk ) \
    (u32)( \
    ((u32)(int_clk) << REG_GX_P3D_INT_CLK_INT_CLK_SHIFT))
#endif


/* P3D_TB_GAS_ACC_MAX */

/* P3D_GAS_ACC_MAX_RESULT_INT */

/* P3D_CMDLIST0_LEN */

/* P3D_CMDLIST0_ADDR */

/* P3D_CMDLIST0_RUN */

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_MPCORE_IOREG_GX_H_ */
#endif
