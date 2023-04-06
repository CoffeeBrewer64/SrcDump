/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/ARM9/ioreg_SD.h

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
#ifndef NN_HW_CTR_TEG2_ARM9_IOREG_SD_H_
#define NN_HW_CTR_TEG2_ARM9_IOREG_SD_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* SD1_CMD */

#define REG_SD1_CMD_OFFSET                                 0x6000
#define REG_SD1_CMD_ADDR                                   (HW_REG_BASE + REG_SD1_CMD_OFFSET)
#define reg_SD_SD1_CMD                                     (*( REGType16v *) REG_SD1_CMD_ADDR)

/* SD1_PORTSEL */

#define REG_SD1_PORTSEL_OFFSET                             0x6002
#define REG_SD1_PORTSEL_ADDR                               (HW_REG_BASE + REG_SD1_PORTSEL_OFFSET)
#define reg_SD_SD1_PORTSEL                                 (*( REGType16v *) REG_SD1_PORTSEL_ADDR)

/* SD1_ARG0 */

#define REG_SD1_ARG0_OFFSET                                0x6004
#define REG_SD1_ARG0_ADDR                                  (HW_REG_BASE + REG_SD1_ARG0_OFFSET)
#define reg_SD_SD1_ARG0                                    (*( REGType16v *) REG_SD1_ARG0_ADDR)

/* SD1_ARG1 */

#define REG_SD1_ARG1_OFFSET                                0x6006
#define REG_SD1_ARG1_ADDR                                  (HW_REG_BASE + REG_SD1_ARG1_OFFSET)
#define reg_SD_SD1_ARG1                                    (*( REGType16v *) REG_SD1_ARG1_ADDR)

/* SD1_STOP */

#define REG_SD1_STOP_OFFSET                                0x6008
#define REG_SD1_STOP_ADDR                                  (HW_REG_BASE + REG_SD1_STOP_OFFSET)
#define reg_SD_SD1_STOP                                    (*( REGType16v *) REG_SD1_STOP_ADDR)

/* SD1_SECCNT */

#define REG_SD1_SECCNT_OFFSET                              0x600a
#define REG_SD1_SECCNT_ADDR                                (HW_REG_BASE + REG_SD1_SECCNT_OFFSET)
#define reg_SD_SD1_SECCNT                                  (*( REGType16v *) REG_SD1_SECCNT_ADDR)

/* SD1_RSP0 */

#define REG_SD1_RSP0_OFFSET                                0x600c
#define REG_SD1_RSP0_ADDR                                  (HW_REG_BASE + REG_SD1_RSP0_OFFSET)
#define reg_SD_SD1_RSP0                                    (*(const REGType16v *) REG_SD1_RSP0_ADDR)

/* SD1_RSP1 */

#define REG_SD1_RSP1_OFFSET                                0x600e
#define REG_SD1_RSP1_ADDR                                  (HW_REG_BASE + REG_SD1_RSP1_OFFSET)
#define reg_SD_SD1_RSP1                                    (*(const REGType16v *) REG_SD1_RSP1_ADDR)

/* SD1_RSP2 */

#define REG_SD1_RSP2_OFFSET                                0x6010
#define REG_SD1_RSP2_ADDR                                  (HW_REG_BASE + REG_SD1_RSP2_OFFSET)
#define reg_SD_SD1_RSP2                                    (*(const REGType16v *) REG_SD1_RSP2_ADDR)

/* SD1_RSP3 */

#define REG_SD1_RSP3_OFFSET                                0x6012
#define REG_SD1_RSP3_ADDR                                  (HW_REG_BASE + REG_SD1_RSP3_OFFSET)
#define reg_SD_SD1_RSP3                                    (*(const REGType16v *) REG_SD1_RSP3_ADDR)

/* SD1_RSP4 */

#define REG_SD1_RSP4_OFFSET                                0x6014
#define REG_SD1_RSP4_ADDR                                  (HW_REG_BASE + REG_SD1_RSP4_OFFSET)
#define reg_SD_SD1_RSP4                                    (*(const REGType16v *) REG_SD1_RSP4_ADDR)

/* SD1_RSP5 */

#define REG_SD1_RSP5_OFFSET                                0x6016
#define REG_SD1_RSP5_ADDR                                  (HW_REG_BASE + REG_SD1_RSP5_OFFSET)
#define reg_SD_SD1_RSP5                                    (*(const REGType16v *) REG_SD1_RSP5_ADDR)

/* SD1_RSP6 */

#define REG_SD1_RSP6_OFFSET                                0x6018
#define REG_SD1_RSP6_ADDR                                  (HW_REG_BASE + REG_SD1_RSP6_OFFSET)
#define reg_SD_SD1_RSP6                                    (*(const REGType16v *) REG_SD1_RSP6_ADDR)

/* SD1_RSP7 */

#define REG_SD1_RSP7_OFFSET                                0x601a
#define REG_SD1_RSP7_ADDR                                  (HW_REG_BASE + REG_SD1_RSP7_OFFSET)
#define reg_SD_SD1_RSP7                                    (*(const REGType16v *) REG_SD1_RSP7_ADDR)

/* SD1_INFO1 */

#define REG_SD1_INFO1_OFFSET                               0x601c
#define REG_SD1_INFO1_ADDR                                 (HW_REG_BASE + REG_SD1_INFO1_OFFSET)
#define reg_SD_SD1_INFO1                                   (*( REGType16v *) REG_SD1_INFO1_ADDR)

/* SD1_INFO2 */

#define REG_SD1_INFO2_OFFSET                               0x601e
#define REG_SD1_INFO2_ADDR                                 (HW_REG_BASE + REG_SD1_INFO2_OFFSET)
#define reg_SD_SD1_INFO2                                   (*( REGType16v *) REG_SD1_INFO2_ADDR)

/* SD1_INFO1_MASK */

#define REG_SD1_INFO1_MASK_OFFSET                          0x6020
#define REG_SD1_INFO1_MASK_ADDR                            (HW_REG_BASE + REG_SD1_INFO1_MASK_OFFSET)
#define reg_SD_SD1_INFO1_MASK                              (*( REGType16v *) REG_SD1_INFO1_MASK_ADDR)

/* SD1_INFO2_MASK */

#define REG_SD1_INFO2_MASK_OFFSET                          0x6022
#define REG_SD1_INFO2_MASK_ADDR                            (HW_REG_BASE + REG_SD1_INFO2_MASK_OFFSET)
#define reg_SD_SD1_INFO2_MASK                              (*( REGType16v *) REG_SD1_INFO2_MASK_ADDR)

/* SD1_CLK_CTRL */

#define REG_SD1_CLK_CTRL_OFFSET                            0x6024
#define REG_SD1_CLK_CTRL_ADDR                              (HW_REG_BASE + REG_SD1_CLK_CTRL_OFFSET)
#define reg_SD_SD1_CLK_CTRL                                (*( REGType16v *) REG_SD1_CLK_CTRL_ADDR)

/* SD1_SIZE */

#define REG_SD1_SIZE_OFFSET                                0x6026
#define REG_SD1_SIZE_ADDR                                  (HW_REG_BASE + REG_SD1_SIZE_OFFSET)
#define reg_SD_SD1_SIZE                                    (*( REGType16v *) REG_SD1_SIZE_ADDR)

/* SD1_OPTION */

#define REG_SD1_OPTION_OFFSET                              0x6028
#define REG_SD1_OPTION_ADDR                                (HW_REG_BASE + REG_SD1_OPTION_OFFSET)
#define reg_SD_SD1_OPTION                                  (*( REGType16v *) REG_SD1_OPTION_ADDR)

/* SD1_ERR_STS1 */

#define REG_SD1_ERR_STS1_OFFSET                            0x602a
#define REG_SD1_ERR_STS1_ADDR                              (HW_REG_BASE + REG_SD1_ERR_STS1_OFFSET)
#define reg_SD_SD1_ERR_STS1                                (*(const REGType16v *) REG_SD1_ERR_STS1_ADDR)

/* SD1_ERR_STS2 */

#define REG_SD1_ERR_STS2_OFFSET                            0x602c
#define REG_SD1_ERR_STS2_ADDR                              (HW_REG_BASE + REG_SD1_ERR_STS2_OFFSET)
#define reg_SD_SD1_ERR_STS2                                (*(const REGType16v *) REG_SD1_ERR_STS2_ADDR)

/* SD1_BUF0 */

#define REG_SD1_BUF0_OFFSET                                0x602e
#define REG_SD1_BUF0_ADDR                                  (HW_REG_BASE + REG_SD1_BUF0_OFFSET)
#define reg_SD_SD1_BUF0                                    (*( REGType16v *) REG_SD1_BUF0_ADDR)

/* SDIO1_MODE */

#define REG_SDIO1_MODE_OFFSET                              0x6030
#define REG_SDIO1_MODE_ADDR                                (HW_REG_BASE + REG_SDIO1_MODE_OFFSET)
#define reg_SD_SDIO1_MODE                                  (*( REGType16v *) REG_SDIO1_MODE_ADDR)

/* SDIO1_INFO1 */

#define REG_SDIO1_INFO1_OFFSET                             0x6034
#define REG_SDIO1_INFO1_ADDR                               (HW_REG_BASE + REG_SDIO1_INFO1_OFFSET)
#define reg_SD_SDIO1_INFO1                                 (*( REGType16v *) REG_SDIO1_INFO1_ADDR)

/* SDIO1_INF1_MASK */

#define REG_SDIO1_INF1_MASK_OFFSET                         0x6038
#define REG_SDIO1_INF1_MASK_ADDR                           (HW_REG_BASE + REG_SDIO1_INF1_MASK_OFFSET)
#define reg_SD_SDIO1_INF1_MASK                             (*( REGType16v *) REG_SDIO1_INF1_MASK_ADDR)

/* SD1_CC_EXT_MODE */

#define REG_SD1_CC_EXT_MODE_OFFSET                         0x60d8
#define REG_SD1_CC_EXT_MODE_ADDR                           (HW_REG_BASE + REG_SD1_CC_EXT_MODE_OFFSET)
#define reg_SD_SD1_CC_EXT_MODE                             (*( REGType16v *) REG_SD1_CC_EXT_MODE_ADDR)

/* SD1_SOFT_RST */

#define REG_SD1_SOFT_RST_OFFSET                            0x60e0
#define REG_SD1_SOFT_RST_ADDR                              (HW_REG_BASE + REG_SD1_SOFT_RST_OFFSET)
#define reg_SD_SD1_SOFT_RST                                (*( REGType16v *) REG_SD1_SOFT_RST_ADDR)

/* SD1_VERSION */

#define REG_SD1_VERSION_OFFSET                             0x60e2
#define REG_SD1_VERSION_ADDR                               (HW_REG_BASE + REG_SD1_VERSION_OFFSET)
#define reg_SD_SD1_VERSION                                 (*(const REGType16v *) REG_SD1_VERSION_ADDR)

/* SD1_PWR */

#define REG_SD1_PWR_OFFSET                                 0x60f2
#define REG_SD1_PWR_ADDR                                   (HW_REG_BASE + REG_SD1_PWR_OFFSET)
#define reg_SD_SD1_PWR                                     (*( REGType16v *) REG_SD1_PWR_ADDR)

/* SD1_EXT_SDIO */

#define REG_SD1_EXT_SDIO_OFFSET                            0x60f4
#define REG_SD1_EXT_SDIO_ADDR                              (HW_REG_BASE + REG_SD1_EXT_SDIO_OFFSET)
#define reg_SD_SD1_EXT_SDIO                                (*( REGType16v *) REG_SD1_EXT_SDIO_ADDR)

/* SD1_EXT_WP */

#define REG_SD1_EXT_WP_OFFSET                              0x60f6
#define REG_SD1_EXT_WP_ADDR                                (HW_REG_BASE + REG_SD1_EXT_WP_OFFSET)
#define reg_SD_SD1_EXT_WP                                  (*(const REGType16v *) REG_SD1_EXT_WP_ADDR)

/* SD1_EXT_CD */

#define REG_SD1_EXT_CD_OFFSET                              0x60f8
#define REG_SD1_EXT_CD_ADDR                                (HW_REG_BASE + REG_SD1_EXT_CD_OFFSET)
#define reg_SD_SD1_EXT_CD                                  (*( REGType16v *) REG_SD1_EXT_CD_ADDR)

/* SD1_EXT_CD_DAT3 */

#define REG_SD1_EXT_CD_DAT3_OFFSET                         0x60fa
#define REG_SD1_EXT_CD_DAT3_ADDR                           (HW_REG_BASE + REG_SD1_EXT_CD_DAT3_OFFSET)
#define reg_SD_SD1_EXT_CD_DAT3                             (*( REGType16v *) REG_SD1_EXT_CD_DAT3_ADDR)

/* SD1_EXT_CD_MASK */

#define REG_SD1_EXT_CD_MASK_OFFSET                         0x60fc
#define REG_SD1_EXT_CD_MASK_ADDR                           (HW_REG_BASE + REG_SD1_EXT_CD_MASK_OFFSET)
#define reg_SD_SD1_EXT_CD_MASK                             (*( REGType16v *) REG_SD1_EXT_CD_MASK_ADDR)

/* SD1_EXT_CD_DAT3_MASK */

#define REG_SD1_EXT_CD_DAT3_MASK_OFFSET                    0x60fe
#define REG_SD1_EXT_CD_DAT3_MASK_ADDR                      (HW_REG_BASE + REG_SD1_EXT_CD_DAT3_MASK_OFFSET)
#define reg_SD_SD1_EXT_CD_DAT3_MASK                        (*( REGType16v *) REG_SD1_EXT_CD_DAT3_MASK_ADDR)

/* SD1_CNT */

#define REG_SD1_CNT_OFFSET                                 0x6100
#define REG_SD1_CNT_ADDR                                   (HW_REG_BASE + REG_SD1_CNT_OFFSET)
#define reg_SD_SD1_CNT                                     (*( REGType16v *) REG_SD1_CNT_ADDR)

/* SD1_FDS */

#define REG_SD1_FDS_OFFSET                                 0x6104
#define REG_SD1_FDS_ADDR                                   (HW_REG_BASE + REG_SD1_FDS_OFFSET)
#define reg_SD_SD1_FDS                                     (*( REGType16v *) REG_SD1_FDS_ADDR)

/* SD1_FSC */

#define REG_SD1_FSC_OFFSET                                 0x6108
#define REG_SD1_FSC_ADDR                                   (HW_REG_BASE + REG_SD1_FSC_OFFSET)
#define reg_SD_SD1_FSC                                     (*( REGType16v *) REG_SD1_FSC_ADDR)

/* SD1_FI */

#define REG_SD1_FI_OFFSET                                  0x610c
#define REG_SD1_FI_ADDR                                    (HW_REG_BASE + REG_SD1_FI_OFFSET)
#define reg_SD_SD1_FI                                      (*( REGType32v *) REG_SD1_FI_ADDR)

/* SD3_CMD */

#define REG_SD3_CMD_OFFSET                                 0x7000
#define REG_SD3_CMD_ADDR                                   (HW_REG_BASE + REG_SD3_CMD_OFFSET)
#define reg_SD_SD3_CMD                                     (*( REGType16v *) REG_SD3_CMD_ADDR)

/* SD3_PORTSEL */

#define REG_SD3_PORTSEL_OFFSET                             0x7002
#define REG_SD3_PORTSEL_ADDR                               (HW_REG_BASE + REG_SD3_PORTSEL_OFFSET)
#define reg_SD_SD3_PORTSEL                                 (*( REGType16v *) REG_SD3_PORTSEL_ADDR)

/* SD3_ARG0 */

#define REG_SD3_ARG0_OFFSET                                0x7004
#define REG_SD3_ARG0_ADDR                                  (HW_REG_BASE + REG_SD3_ARG0_OFFSET)
#define reg_SD_SD3_ARG0                                    (*( REGType16v *) REG_SD3_ARG0_ADDR)

/* SD3_ARG1 */

#define REG_SD3_ARG1_OFFSET                                0x7006
#define REG_SD3_ARG1_ADDR                                  (HW_REG_BASE + REG_SD3_ARG1_OFFSET)
#define reg_SD_SD3_ARG1                                    (*( REGType16v *) REG_SD3_ARG1_ADDR)

/* SD3_STOP */

#define REG_SD3_STOP_OFFSET                                0x7008
#define REG_SD3_STOP_ADDR                                  (HW_REG_BASE + REG_SD3_STOP_OFFSET)
#define reg_SD_SD3_STOP                                    (*( REGType16v *) REG_SD3_STOP_ADDR)

/* SD3_SECCNT */

#define REG_SD3_SECCNT_OFFSET                              0x700a
#define REG_SD3_SECCNT_ADDR                                (HW_REG_BASE + REG_SD3_SECCNT_OFFSET)
#define reg_SD_SD3_SECCNT                                  (*( REGType16v *) REG_SD3_SECCNT_ADDR)

/* SD3_RSP0 */

#define REG_SD3_RSP0_OFFSET                                0x700c
#define REG_SD3_RSP0_ADDR                                  (HW_REG_BASE + REG_SD3_RSP0_OFFSET)
#define reg_SD_SD3_RSP0                                    (*(const REGType16v *) REG_SD3_RSP0_ADDR)

/* SD3_RSP1 */

#define REG_SD3_RSP1_OFFSET                                0x700e
#define REG_SD3_RSP1_ADDR                                  (HW_REG_BASE + REG_SD3_RSP1_OFFSET)
#define reg_SD_SD3_RSP1                                    (*(const REGType16v *) REG_SD3_RSP1_ADDR)

/* SD3_RSP2 */

#define REG_SD3_RSP2_OFFSET                                0x7010
#define REG_SD3_RSP2_ADDR                                  (HW_REG_BASE + REG_SD3_RSP2_OFFSET)
#define reg_SD_SD3_RSP2                                    (*(const REGType16v *) REG_SD3_RSP2_ADDR)

/* SD3_RSP3 */

#define REG_SD3_RSP3_OFFSET                                0x7012
#define REG_SD3_RSP3_ADDR                                  (HW_REG_BASE + REG_SD3_RSP3_OFFSET)
#define reg_SD_SD3_RSP3                                    (*(const REGType16v *) REG_SD3_RSP3_ADDR)

/* SD3_RSP4 */

#define REG_SD3_RSP4_OFFSET                                0x7014
#define REG_SD3_RSP4_ADDR                                  (HW_REG_BASE + REG_SD3_RSP4_OFFSET)
#define reg_SD_SD3_RSP4                                    (*(const REGType16v *) REG_SD3_RSP4_ADDR)

/* SD3_RSP5 */

#define REG_SD3_RSP5_OFFSET                                0x7016
#define REG_SD3_RSP5_ADDR                                  (HW_REG_BASE + REG_SD3_RSP5_OFFSET)
#define reg_SD_SD3_RSP5                                    (*(const REGType16v *) REG_SD3_RSP5_ADDR)

/* SD3_RSP6 */

#define REG_SD3_RSP6_OFFSET                                0x7018
#define REG_SD3_RSP6_ADDR                                  (HW_REG_BASE + REG_SD3_RSP6_OFFSET)
#define reg_SD_SD3_RSP6                                    (*(const REGType16v *) REG_SD3_RSP6_ADDR)

/* SD3_RSP7 */

#define REG_SD3_RSP7_OFFSET                                0x701a
#define REG_SD3_RSP7_ADDR                                  (HW_REG_BASE + REG_SD3_RSP7_OFFSET)
#define reg_SD_SD3_RSP7                                    (*(const REGType16v *) REG_SD3_RSP7_ADDR)

/* SD3_INFO1 */

#define REG_SD3_INFO1_OFFSET                               0x701c
#define REG_SD3_INFO1_ADDR                                 (HW_REG_BASE + REG_SD3_INFO1_OFFSET)
#define reg_SD_SD3_INFO1                                   (*( REGType16v *) REG_SD3_INFO1_ADDR)

/* SD3_INFO2 */

#define REG_SD3_INFO2_OFFSET                               0x701e
#define REG_SD3_INFO2_ADDR                                 (HW_REG_BASE + REG_SD3_INFO2_OFFSET)
#define reg_SD_SD3_INFO2                                   (*( REGType16v *) REG_SD3_INFO2_ADDR)

/* SD3_INFO1_MASK */

#define REG_SD3_INFO1_MASK_OFFSET                          0x7020
#define REG_SD3_INFO1_MASK_ADDR                            (HW_REG_BASE + REG_SD3_INFO1_MASK_OFFSET)
#define reg_SD_SD3_INFO1_MASK                              (*( REGType16v *) REG_SD3_INFO1_MASK_ADDR)

/* SD3_INFO2_MASK */

#define REG_SD3_INFO2_MASK_OFFSET                          0x7022
#define REG_SD3_INFO2_MASK_ADDR                            (HW_REG_BASE + REG_SD3_INFO2_MASK_OFFSET)
#define reg_SD_SD3_INFO2_MASK                              (*( REGType16v *) REG_SD3_INFO2_MASK_ADDR)

/* SD3_CLK_CTRL */

#define REG_SD3_CLK_CTRL_OFFSET                            0x7024
#define REG_SD3_CLK_CTRL_ADDR                              (HW_REG_BASE + REG_SD3_CLK_CTRL_OFFSET)
#define reg_SD_SD3_CLK_CTRL                                (*( REGType16v *) REG_SD3_CLK_CTRL_ADDR)

/* SD3_SIZE */

#define REG_SD3_SIZE_OFFSET                                0x7026
#define REG_SD3_SIZE_ADDR                                  (HW_REG_BASE + REG_SD3_SIZE_OFFSET)
#define reg_SD_SD3_SIZE                                    (*( REGType16v *) REG_SD3_SIZE_ADDR)

/* SD3_OPTION */

#define REG_SD3_OPTION_OFFSET                              0x7028
#define REG_SD3_OPTION_ADDR                                (HW_REG_BASE + REG_SD3_OPTION_OFFSET)
#define reg_SD_SD3_OPTION                                  (*( REGType16v *) REG_SD3_OPTION_ADDR)

/* SD3_ERR_STS1 */

#define REG_SD3_ERR_STS1_OFFSET                            0x702a
#define REG_SD3_ERR_STS1_ADDR                              (HW_REG_BASE + REG_SD3_ERR_STS1_OFFSET)
#define reg_SD_SD3_ERR_STS1                                (*(const REGType16v *) REG_SD3_ERR_STS1_ADDR)

/* SD3_ERR_STS2 */

#define REG_SD3_ERR_STS2_OFFSET                            0x702c
#define REG_SD3_ERR_STS2_ADDR                              (HW_REG_BASE + REG_SD3_ERR_STS2_OFFSET)
#define reg_SD_SD3_ERR_STS2                                (*(const REGType16v *) REG_SD3_ERR_STS2_ADDR)

/* SD3_BUF0 */

#define REG_SD3_BUF0_OFFSET                                0x702e
#define REG_SD3_BUF0_ADDR                                  (HW_REG_BASE + REG_SD3_BUF0_OFFSET)
#define reg_SD_SD3_BUF0                                    (*( REGType16v *) REG_SD3_BUF0_ADDR)

/* SDIO3_MODE */

#define REG_SDIO3_MODE_OFFSET                              0x7030
#define REG_SDIO3_MODE_ADDR                                (HW_REG_BASE + REG_SDIO3_MODE_OFFSET)
#define reg_SD_SDIO3_MODE                                  (*( REGType16v *) REG_SDIO3_MODE_ADDR)

/* SDIO3_INFO1 */

#define REG_SDIO3_INFO1_OFFSET                             0x7034
#define REG_SDIO3_INFO1_ADDR                               (HW_REG_BASE + REG_SDIO3_INFO1_OFFSET)
#define reg_SD_SDIO3_INFO1                                 (*( REGType16v *) REG_SDIO3_INFO1_ADDR)

/* SDIO3_INF1_MASK */

#define REG_SDIO3_INF1_MASK_OFFSET                         0x7038
#define REG_SDIO3_INF1_MASK_ADDR                           (HW_REG_BASE + REG_SDIO3_INF1_MASK_OFFSET)
#define reg_SD_SDIO3_INF1_MASK                             (*( REGType16v *) REG_SDIO3_INF1_MASK_ADDR)

/* SD3_CC_EXT_MODE */

#define REG_SD3_CC_EXT_MODE_OFFSET                         0x70d8
#define REG_SD3_CC_EXT_MODE_ADDR                           (HW_REG_BASE + REG_SD3_CC_EXT_MODE_OFFSET)
#define reg_SD_SD3_CC_EXT_MODE                             (*( REGType16v *) REG_SD3_CC_EXT_MODE_ADDR)

/* SD3_SOFT_RST */

#define REG_SD3_SOFT_RST_OFFSET                            0x70e0
#define REG_SD3_SOFT_RST_ADDR                              (HW_REG_BASE + REG_SD3_SOFT_RST_OFFSET)
#define reg_SD_SD3_SOFT_RST                                (*( REGType16v *) REG_SD3_SOFT_RST_ADDR)

/* SD3_VERSION */

#define REG_SD3_VERSION_OFFSET                             0x70e2
#define REG_SD3_VERSION_ADDR                               (HW_REG_BASE + REG_SD3_VERSION_OFFSET)
#define reg_SD_SD3_VERSION                                 (*(const REGType16v *) REG_SD3_VERSION_ADDR)

/* SD3_PWR */

#define REG_SD3_PWR_OFFSET                                 0x70f2
#define REG_SD3_PWR_ADDR                                   (HW_REG_BASE + REG_SD3_PWR_OFFSET)
#define reg_SD_SD3_PWR                                     (*( REGType16v *) REG_SD3_PWR_ADDR)

/* SD3_EXT_SDIO */

#define REG_SD3_EXT_SDIO_OFFSET                            0x70f4
#define REG_SD3_EXT_SDIO_ADDR                              (HW_REG_BASE + REG_SD3_EXT_SDIO_OFFSET)
#define reg_SD_SD3_EXT_SDIO                                (*( REGType16v *) REG_SD3_EXT_SDIO_ADDR)

/* SD3_EXT_WP */

#define REG_SD3_EXT_WP_OFFSET                              0x70f6
#define REG_SD3_EXT_WP_ADDR                                (HW_REG_BASE + REG_SD3_EXT_WP_OFFSET)
#define reg_SD_SD3_EXT_WP                                  (*(const REGType16v *) REG_SD3_EXT_WP_ADDR)

/* SD3_EXT_CD */

#define REG_SD3_EXT_CD_OFFSET                              0x70f8
#define REG_SD3_EXT_CD_ADDR                                (HW_REG_BASE + REG_SD3_EXT_CD_OFFSET)
#define reg_SD_SD3_EXT_CD                                  (*( REGType16v *) REG_SD3_EXT_CD_ADDR)

/* SD3_EXT_CD_DAT3 */

#define REG_SD3_EXT_CD_DAT3_OFFSET                         0x70fa
#define REG_SD3_EXT_CD_DAT3_ADDR                           (HW_REG_BASE + REG_SD3_EXT_CD_DAT3_OFFSET)
#define reg_SD_SD3_EXT_CD_DAT3                             (*( REGType16v *) REG_SD3_EXT_CD_DAT3_ADDR)

/* SD3_EXT_CD_MASK */

#define REG_SD3_EXT_CD_MASK_OFFSET                         0x70fc
#define REG_SD3_EXT_CD_MASK_ADDR                           (HW_REG_BASE + REG_SD3_EXT_CD_MASK_OFFSET)
#define reg_SD_SD3_EXT_CD_MASK                             (*( REGType16v *) REG_SD3_EXT_CD_MASK_ADDR)

/* SD3_EXT_CD_DAT3_MASK */

#define REG_SD3_EXT_CD_DAT3_MASK_OFFSET                    0x70fe
#define REG_SD3_EXT_CD_DAT3_MASK_ADDR                      (HW_REG_BASE + REG_SD3_EXT_CD_DAT3_MASK_OFFSET)
#define reg_SD_SD3_EXT_CD_DAT3_MASK                        (*( REGType16v *) REG_SD3_EXT_CD_DAT3_MASK_ADDR)

/* SD3_CNT */

#define REG_SD3_CNT_OFFSET                                 0x7100
#define REG_SD3_CNT_ADDR                                   (HW_REG_BASE + REG_SD3_CNT_OFFSET)
#define reg_SD_SD3_CNT                                     (*( REGType16v *) REG_SD3_CNT_ADDR)

/* SD3_FDS */

#define REG_SD3_FDS_OFFSET                                 0x7104
#define REG_SD3_FDS_ADDR                                   (HW_REG_BASE + REG_SD3_FDS_OFFSET)
#define reg_SD_SD3_FDS                                     (*( REGType16v *) REG_SD3_FDS_ADDR)

/* SD3_FSC */

#define REG_SD3_FSC_OFFSET                                 0x7108
#define REG_SD3_FSC_ADDR                                   (HW_REG_BASE + REG_SD3_FSC_OFFSET)
#define reg_SD_SD3_FSC                                     (*( REGType16v *) REG_SD3_FSC_ADDR)

/* SD3_FI */

#define REG_SD3_FI_OFFSET                                  0x710c
#define REG_SD3_FI_ADDR                                    (HW_REG_BASE + REG_SD3_FI_OFFSET)
#define reg_SD_SD3_FI                                      (*( REGType32v *) REG_SD3_FI_ADDR)


/*
 * Definitions of Register fields
 */


/* SD1_CMD */

/* SD1_PORTSEL */

/* SD1_ARG0 */

/* SD1_ARG1 */

/* SD1_STOP */

/* SD1_SECCNT */

/* SD1_RSP0 */

/* SD1_RSP1 */

/* SD1_RSP2 */

/* SD1_RSP3 */

/* SD1_RSP4 */

/* SD1_RSP5 */

/* SD1_RSP6 */

/* SD1_RSP7 */

/* SD1_INFO1 */

/* SD1_INFO2 */

/* SD1_INFO1_MASK */

/* SD1_INFO2_MASK */

/* SD1_CLK_CTRL */

/* SD1_SIZE */

/* SD1_OPTION */

/* SD1_ERR_STS1 */

/* SD1_ERR_STS2 */

/* SD1_BUF0 */

/* SDIO1_MODE */

/* SDIO1_INFO1 */

/* SDIO1_INF1_MASK */

/* SD1_CC_EXT_MODE */

/* SD1_SOFT_RST */

/* SD1_VERSION */

/* SD1_PWR */

/* SD1_EXT_SDIO */

/* SD1_EXT_WP */

/* SD1_EXT_CD */

/* SD1_EXT_CD_DAT3 */

/* SD1_EXT_CD_MASK */

/* SD1_EXT_CD_DAT3_MASK */

/* SD1_CNT */

#define REG_SD_SD1_CNT_FEIE_SHIFT                          12
#define REG_SD_SD1_CNT_FEIE_SIZE                           1
#define REG_SD_SD1_CNT_FEIE_MASK                           0x1000

#define REG_SD_SD1_CNT_FFIE_SHIFT                          11
#define REG_SD_SD1_CNT_FFIE_SIZE                           1
#define REG_SD_SD1_CNT_FFIE_MASK                           0x0800

#define REG_SD_SD1_CNT_FCLR_SHIFT                          10
#define REG_SD_SD1_CNT_FCLR_SIZE                           1
#define REG_SD_SD1_CNT_FCLR_MASK                           0x0400

#define REG_SD_SD1_CNT_NEMP_SHIFT                          9
#define REG_SD_SD1_CNT_NEMP_SIZE                           1
#define REG_SD_SD1_CNT_NEMP_MASK                           0x0200

#define REG_SD_SD1_CNT_FULL_SHIFT                          8
#define REG_SD_SD1_CNT_FULL_SIZE                           1
#define REG_SD_SD1_CNT_FULL_MASK                           0x0100

#define REG_SD_SD1_CNT_FIFO_SHIFT                          1
#define REG_SD_SD1_CNT_FIFO_SIZE                           1
#define REG_SD_SD1_CNT_FIFO_MASK                           0x0002

#ifndef SDK_ASM
#define REG_SD_SD1_CNT_FIELD( feie, ffie, fclr, nemp, full, fifo ) \
    (u16)( \
    ((u32)(feie) << REG_SD_SD1_CNT_FEIE_SHIFT) | \
    ((u32)(ffie) << REG_SD_SD1_CNT_FFIE_SHIFT) | \
    ((u32)(fclr) << REG_SD_SD1_CNT_FCLR_SHIFT) | \
    ((u32)(nemp) << REG_SD_SD1_CNT_NEMP_SHIFT) | \
    ((u32)(full) << REG_SD_SD1_CNT_FULL_SHIFT) | \
    ((u32)(fifo) << REG_SD_SD1_CNT_FIFO_SHIFT))
#endif


/* SD1_FDS */

#define REG_SD_SD1_FDS_SIZE_SHIFT                          0
#define REG_SD_SD1_FDS_SIZE_SIZE                           10
#define REG_SD_SD1_FDS_SIZE_MASK                           0x03ff

#ifndef SDK_ASM
#define REG_SD_SD1_FDS_FIELD( size ) \
    (u16)( \
    ((u32)(size) << REG_SD_SD1_FDS_SIZE_SHIFT))
#endif


/* SD1_FSC */

#define REG_SD_SD1_FSC_COUNT_SHIFT                         0
#define REG_SD_SD1_FSC_COUNT_SIZE                          16
#define REG_SD_SD1_FSC_COUNT_MASK                          0xffff

#ifndef SDK_ASM
#define REG_SD_SD1_FSC_FIELD( count ) \
    (u16)( \
    ((u32)(count) << REG_SD_SD1_FSC_COUNT_SHIFT))
#endif


/* SD1_FI */

/* SD3_CMD */

/* SD3_PORTSEL */

/* SD3_ARG0 */

/* SD3_ARG1 */

/* SD3_STOP */

/* SD3_SECCNT */

/* SD3_RSP0 */

/* SD3_RSP1 */

/* SD3_RSP2 */

/* SD3_RSP3 */

/* SD3_RSP4 */

/* SD3_RSP5 */

/* SD3_RSP6 */

/* SD3_RSP7 */

/* SD3_INFO1 */

/* SD3_INFO2 */

/* SD3_INFO1_MASK */

/* SD3_INFO2_MASK */

/* SD3_CLK_CTRL */

/* SD3_SIZE */

/* SD3_OPTION */

/* SD3_ERR_STS1 */

/* SD3_ERR_STS2 */

/* SD3_BUF0 */

/* SDIO3_MODE */

/* SDIO3_INFO1 */

/* SDIO3_INF1_MASK */

/* SD3_CC_EXT_MODE */

/* SD3_SOFT_RST */

/* SD3_VERSION */

/* SD3_PWR */

/* SD3_EXT_SDIO */

/* SD3_EXT_WP */

/* SD3_EXT_CD */

/* SD3_EXT_CD_DAT3 */

/* SD3_EXT_CD_MASK */

/* SD3_EXT_CD_DAT3_MASK */

/* SD3_CNT */

#define REG_SD_SD3_CNT_FEIE_SHIFT                          12
#define REG_SD_SD3_CNT_FEIE_SIZE                           1
#define REG_SD_SD3_CNT_FEIE_MASK                           0x1000

#define REG_SD_SD3_CNT_FFIE_SHIFT                          11
#define REG_SD_SD3_CNT_FFIE_SIZE                           1
#define REG_SD_SD3_CNT_FFIE_MASK                           0x0800

#define REG_SD_SD3_CNT_FCLR_SHIFT                          10
#define REG_SD_SD3_CNT_FCLR_SIZE                           1
#define REG_SD_SD3_CNT_FCLR_MASK                           0x0400

#define REG_SD_SD3_CNT_NEMP_SHIFT                          9
#define REG_SD_SD3_CNT_NEMP_SIZE                           1
#define REG_SD_SD3_CNT_NEMP_MASK                           0x0200

#define REG_SD_SD3_CNT_FULL_SHIFT                          8
#define REG_SD_SD3_CNT_FULL_SIZE                           1
#define REG_SD_SD3_CNT_FULL_MASK                           0x0100

#define REG_SD_SD3_CNT_FIFO_SHIFT                          1
#define REG_SD_SD3_CNT_FIFO_SIZE                           1
#define REG_SD_SD3_CNT_FIFO_MASK                           0x0002

#ifndef SDK_ASM
#define REG_SD_SD3_CNT_FIELD( feie, ffie, fclr, nemp, full, fifo ) \
    (u16)( \
    ((u32)(feie) << REG_SD_SD3_CNT_FEIE_SHIFT) | \
    ((u32)(ffie) << REG_SD_SD3_CNT_FFIE_SHIFT) | \
    ((u32)(fclr) << REG_SD_SD3_CNT_FCLR_SHIFT) | \
    ((u32)(nemp) << REG_SD_SD3_CNT_NEMP_SHIFT) | \
    ((u32)(full) << REG_SD_SD3_CNT_FULL_SHIFT) | \
    ((u32)(fifo) << REG_SD_SD3_CNT_FIFO_SHIFT))
#endif


/* SD3_FDS */

#define REG_SD_SD3_FDS_SIZE_SHIFT                          0
#define REG_SD_SD3_FDS_SIZE_SIZE                           10
#define REG_SD_SD3_FDS_SIZE_MASK                           0x03ff

#ifndef SDK_ASM
#define REG_SD_SD3_FDS_FIELD( size ) \
    (u16)( \
    ((u32)(size) << REG_SD_SD3_FDS_SIZE_SHIFT))
#endif


/* SD3_FSC */

#define REG_SD_SD3_FSC_COUNT_SHIFT                         0
#define REG_SD_SD3_FSC_COUNT_SIZE                          16
#define REG_SD_SD3_FSC_COUNT_MASK                          0xffff

#ifndef SDK_ASM
#define REG_SD_SD3_FSC_FIELD( count ) \
    (u16)( \
    ((u32)(count) << REG_SD_SD3_FSC_COUNT_SHIFT))
#endif


/* SD3_FI */

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_ARM9_IOREG_SD_H_ */
#endif
