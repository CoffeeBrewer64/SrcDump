/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/MPCore/ioreg_SD.h

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
#ifndef NN_HW_CTR_TEG2_MPCORE_IOREG_SD_H_
#define NN_HW_CTR_TEG2_MPCORE_IOREG_SD_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* SD2_CMD */

#define REG_SD2_CMD_OFFSET                                 0x122000
#define REG_SD2_CMD_ADDR                                   (HW_REG_BASE + REG_SD2_CMD_OFFSET)
#define reg_SD_SD2_CMD                                     (*( REGType16v *) REG_SD2_CMD_ADDR)

/* SD2_PORTSEL */

#define REG_SD2_PORTSEL_OFFSET                             0x122002
#define REG_SD2_PORTSEL_ADDR                               (HW_REG_BASE + REG_SD2_PORTSEL_OFFSET)
#define reg_SD_SD2_PORTSEL                                 (*( REGType16v *) REG_SD2_PORTSEL_ADDR)

/* SD2_ARG0 */

#define REG_SD2_ARG0_OFFSET                                0x122004
#define REG_SD2_ARG0_ADDR                                  (HW_REG_BASE + REG_SD2_ARG0_OFFSET)
#define reg_SD_SD2_ARG0                                    (*( REGType16v *) REG_SD2_ARG0_ADDR)

/* SD2_ARG1 */

#define REG_SD2_ARG1_OFFSET                                0x122006
#define REG_SD2_ARG1_ADDR                                  (HW_REG_BASE + REG_SD2_ARG1_OFFSET)
#define reg_SD_SD2_ARG1                                    (*( REGType16v *) REG_SD2_ARG1_ADDR)

/* SD2_STOP */

#define REG_SD2_STOP_OFFSET                                0x122008
#define REG_SD2_STOP_ADDR                                  (HW_REG_BASE + REG_SD2_STOP_OFFSET)
#define reg_SD_SD2_STOP                                    (*( REGType16v *) REG_SD2_STOP_ADDR)

/* SD2_SECCNT */

#define REG_SD2_SECCNT_OFFSET                              0x12200a
#define REG_SD2_SECCNT_ADDR                                (HW_REG_BASE + REG_SD2_SECCNT_OFFSET)
#define reg_SD_SD2_SECCNT                                  (*( REGType16v *) REG_SD2_SECCNT_ADDR)

/* SD2_RSP0 */

#define REG_SD2_RSP0_OFFSET                                0x12200c
#define REG_SD2_RSP0_ADDR                                  (HW_REG_BASE + REG_SD2_RSP0_OFFSET)
#define reg_SD_SD2_RSP0                                    (*(const REGType16v *) REG_SD2_RSP0_ADDR)

/* SD2_RSP1 */

#define REG_SD2_RSP1_OFFSET                                0x12200e
#define REG_SD2_RSP1_ADDR                                  (HW_REG_BASE + REG_SD2_RSP1_OFFSET)
#define reg_SD_SD2_RSP1                                    (*(const REGType16v *) REG_SD2_RSP1_ADDR)

/* SD2_RSP2 */

#define REG_SD2_RSP2_OFFSET                                0x122010
#define REG_SD2_RSP2_ADDR                                  (HW_REG_BASE + REG_SD2_RSP2_OFFSET)
#define reg_SD_SD2_RSP2                                    (*(const REGType16v *) REG_SD2_RSP2_ADDR)

/* SD2_RSP3 */

#define REG_SD2_RSP3_OFFSET                                0x122012
#define REG_SD2_RSP3_ADDR                                  (HW_REG_BASE + REG_SD2_RSP3_OFFSET)
#define reg_SD_SD2_RSP3                                    (*(const REGType16v *) REG_SD2_RSP3_ADDR)

/* SD2_RSP4 */

#define REG_SD2_RSP4_OFFSET                                0x122014
#define REG_SD2_RSP4_ADDR                                  (HW_REG_BASE + REG_SD2_RSP4_OFFSET)
#define reg_SD_SD2_RSP4                                    (*(const REGType16v *) REG_SD2_RSP4_ADDR)

/* SD2_RSP5 */

#define REG_SD2_RSP5_OFFSET                                0x122016
#define REG_SD2_RSP5_ADDR                                  (HW_REG_BASE + REG_SD2_RSP5_OFFSET)
#define reg_SD_SD2_RSP5                                    (*(const REGType16v *) REG_SD2_RSP5_ADDR)

/* SD2_RSP6 */

#define REG_SD2_RSP6_OFFSET                                0x122018
#define REG_SD2_RSP6_ADDR                                  (HW_REG_BASE + REG_SD2_RSP6_OFFSET)
#define reg_SD_SD2_RSP6                                    (*(const REGType16v *) REG_SD2_RSP6_ADDR)

/* SD2_RSP7 */

#define REG_SD2_RSP7_OFFSET                                0x12201a
#define REG_SD2_RSP7_ADDR                                  (HW_REG_BASE + REG_SD2_RSP7_OFFSET)
#define reg_SD_SD2_RSP7                                    (*(const REGType16v *) REG_SD2_RSP7_ADDR)

/* SD2_INFO1 */

#define REG_SD2_INFO1_OFFSET                               0x12201c
#define REG_SD2_INFO1_ADDR                                 (HW_REG_BASE + REG_SD2_INFO1_OFFSET)
#define reg_SD_SD2_INFO1                                   (*( REGType16v *) REG_SD2_INFO1_ADDR)

/* SD2_INFO2 */

#define REG_SD2_INFO2_OFFSET                               0x12201e
#define REG_SD2_INFO2_ADDR                                 (HW_REG_BASE + REG_SD2_INFO2_OFFSET)
#define reg_SD_SD2_INFO2                                   (*( REGType16v *) REG_SD2_INFO2_ADDR)

/* SD2_INFO1_MASK */

#define REG_SD2_INFO1_MASK_OFFSET                          0x122020
#define REG_SD2_INFO1_MASK_ADDR                            (HW_REG_BASE + REG_SD2_INFO1_MASK_OFFSET)
#define reg_SD_SD2_INFO1_MASK                              (*( REGType16v *) REG_SD2_INFO1_MASK_ADDR)

/* SD2_INFO2_MASK */

#define REG_SD2_INFO2_MASK_OFFSET                          0x122022
#define REG_SD2_INFO2_MASK_ADDR                            (HW_REG_BASE + REG_SD2_INFO2_MASK_OFFSET)
#define reg_SD_SD2_INFO2_MASK                              (*( REGType16v *) REG_SD2_INFO2_MASK_ADDR)

/* SD2_CLK_CTRL */

#define REG_SD2_CLK_CTRL_OFFSET                            0x122024
#define REG_SD2_CLK_CTRL_ADDR                              (HW_REG_BASE + REG_SD2_CLK_CTRL_OFFSET)
#define reg_SD_SD2_CLK_CTRL                                (*( REGType16v *) REG_SD2_CLK_CTRL_ADDR)

/* SD2_SIZE */

#define REG_SD2_SIZE_OFFSET                                0x122026
#define REG_SD2_SIZE_ADDR                                  (HW_REG_BASE + REG_SD2_SIZE_OFFSET)
#define reg_SD_SD2_SIZE                                    (*( REGType16v *) REG_SD2_SIZE_ADDR)

/* SD2_OPTION */

#define REG_SD2_OPTION_OFFSET                              0x122028
#define REG_SD2_OPTION_ADDR                                (HW_REG_BASE + REG_SD2_OPTION_OFFSET)
#define reg_SD_SD2_OPTION                                  (*( REGType16v *) REG_SD2_OPTION_ADDR)

/* SD2_ERR_STS1 */

#define REG_SD2_ERR_STS1_OFFSET                            0x12202a
#define REG_SD2_ERR_STS1_ADDR                              (HW_REG_BASE + REG_SD2_ERR_STS1_OFFSET)
#define reg_SD_SD2_ERR_STS1                                (*(const REGType16v *) REG_SD2_ERR_STS1_ADDR)

/* SD2_ERR_STS2 */

#define REG_SD2_ERR_STS2_OFFSET                            0x12202c
#define REG_SD2_ERR_STS2_ADDR                              (HW_REG_BASE + REG_SD2_ERR_STS2_OFFSET)
#define reg_SD_SD2_ERR_STS2                                (*(const REGType16v *) REG_SD2_ERR_STS2_ADDR)

/* SD2_BUF0 */

#define REG_SD2_BUF0_OFFSET                                0x12202e
#define REG_SD2_BUF0_ADDR                                  (HW_REG_BASE + REG_SD2_BUF0_OFFSET)
#define reg_SD_SD2_BUF0                                    (*( REGType16v *) REG_SD2_BUF0_ADDR)

/* SDIO2_MODE */

#define REG_SDIO2_MODE_OFFSET                              0x122030
#define REG_SDIO2_MODE_ADDR                                (HW_REG_BASE + REG_SDIO2_MODE_OFFSET)
#define reg_SD_SDIO2_MODE                                  (*( REGType16v *) REG_SDIO2_MODE_ADDR)

/* SDIO2_INFO1 */

#define REG_SDIO2_INFO1_OFFSET                             0x122034
#define REG_SDIO2_INFO1_ADDR                               (HW_REG_BASE + REG_SDIO2_INFO1_OFFSET)
#define reg_SD_SDIO2_INFO1                                 (*( REGType16v *) REG_SDIO2_INFO1_ADDR)

/* SDIO2_INF1_MASK */

#define REG_SDIO2_INF1_MASK_OFFSET                         0x122038
#define REG_SDIO2_INF1_MASK_ADDR                           (HW_REG_BASE + REG_SDIO2_INF1_MASK_OFFSET)
#define reg_SD_SDIO2_INF1_MASK                             (*( REGType16v *) REG_SDIO2_INF1_MASK_ADDR)

/* SD2_CC_EXT_MODE */

#define REG_SD2_CC_EXT_MODE_OFFSET                         0x1220d8
#define REG_SD2_CC_EXT_MODE_ADDR                           (HW_REG_BASE + REG_SD2_CC_EXT_MODE_OFFSET)
#define reg_SD_SD2_CC_EXT_MODE                             (*( REGType16v *) REG_SD2_CC_EXT_MODE_ADDR)

/* SD2_SOFT_RST */

#define REG_SD2_SOFT_RST_OFFSET                            0x1220e0
#define REG_SD2_SOFT_RST_ADDR                              (HW_REG_BASE + REG_SD2_SOFT_RST_OFFSET)
#define reg_SD_SD2_SOFT_RST                                (*( REGType16v *) REG_SD2_SOFT_RST_ADDR)

/* SD2_VERSION */

#define REG_SD2_VERSION_OFFSET                             0x1220e2
#define REG_SD2_VERSION_ADDR                               (HW_REG_BASE + REG_SD2_VERSION_OFFSET)
#define reg_SD_SD2_VERSION                                 (*(const REGType16v *) REG_SD2_VERSION_ADDR)

/* DS2_PWR */

#define REG_DS2_PWR_OFFSET                                 0x1220f2
#define REG_DS2_PWR_ADDR                                   (HW_REG_BASE + REG_DS2_PWR_OFFSET)
#define reg_SD_DS2_PWR                                     (*( REGType16v *) REG_DS2_PWR_ADDR)

/* SD2_EXT_SDIO */

#define REG_SD2_EXT_SDIO_OFFSET                            0x1220f4
#define REG_SD2_EXT_SDIO_ADDR                              (HW_REG_BASE + REG_SD2_EXT_SDIO_OFFSET)
#define reg_SD_SD2_EXT_SDIO                                (*( REGType16v *) REG_SD2_EXT_SDIO_ADDR)

/* SD2_EXT_WP */

#define REG_SD2_EXT_WP_OFFSET                              0x1220f6
#define REG_SD2_EXT_WP_ADDR                                (HW_REG_BASE + REG_SD2_EXT_WP_OFFSET)
#define reg_SD_SD2_EXT_WP                                  (*(const REGType16v *) REG_SD2_EXT_WP_ADDR)

/* SD2_EXT_CD */

#define REG_SD2_EXT_CD_OFFSET                              0x1220f8
#define REG_SD2_EXT_CD_ADDR                                (HW_REG_BASE + REG_SD2_EXT_CD_OFFSET)
#define reg_SD_SD2_EXT_CD                                  (*( REGType16v *) REG_SD2_EXT_CD_ADDR)

/* SD2_EXT_CD_DAT3 */

#define REG_SD2_EXT_CD_DAT3_OFFSET                         0x1220fa
#define REG_SD2_EXT_CD_DAT3_ADDR                           (HW_REG_BASE + REG_SD2_EXT_CD_DAT3_OFFSET)
#define reg_SD_SD2_EXT_CD_DAT3                             (*( REGType16v *) REG_SD2_EXT_CD_DAT3_ADDR)

/* SD2_EXT_CD_MASK */

#define REG_SD2_EXT_CD_MASK_OFFSET                         0x1220fc
#define REG_SD2_EXT_CD_MASK_ADDR                           (HW_REG_BASE + REG_SD2_EXT_CD_MASK_OFFSET)
#define reg_SD_SD2_EXT_CD_MASK                             (*( REGType16v *) REG_SD2_EXT_CD_MASK_ADDR)

/* SD2_EXT_CD_DAT3_MASK */

#define REG_SD2_EXT_CD_DAT3_MASK_OFFSET                    0x1220fe
#define REG_SD2_EXT_CD_DAT3_MASK_ADDR                      (HW_REG_BASE + REG_SD2_EXT_CD_DAT3_MASK_OFFSET)
#define reg_SD_SD2_EXT_CD_DAT3_MASK                        (*( REGType16v *) REG_SD2_EXT_CD_DAT3_MASK_ADDR)

/* SD2_CNT */

#define REG_SD2_CNT_OFFSET                                 0x122100
#define REG_SD2_CNT_ADDR                                   (HW_REG_BASE + REG_SD2_CNT_OFFSET)
#define reg_SD_SD2_CNT                                     (*( REGType16v *) REG_SD2_CNT_ADDR)

/* SD2_FDS */

#define REG_SD2_FDS_OFFSET                                 0x122104
#define REG_SD2_FDS_ADDR                                   (HW_REG_BASE + REG_SD2_FDS_OFFSET)
#define reg_SD_SD2_FDS                                     (*( REGType16v *) REG_SD2_FDS_ADDR)

/* SD2_FSC */

#define REG_SD2_FSC_OFFSET                                 0x122108
#define REG_SD2_FSC_ADDR                                   (HW_REG_BASE + REG_SD2_FSC_OFFSET)
#define reg_SD_SD2_FSC                                     (*( REGType16v *) REG_SD2_FSC_ADDR)

/* SD2_FI */

#define REG_SD2_FI_OFFSET                                  0x322000
#define REG_SD2_FI_ADDR                                    (HW_REG_BASE + REG_SD2_FI_OFFSET)
#define reg_SD_SD2_FI                                      (*( REGType32v *) REG_SD2_FI_ADDR)

/* SD3_CMD */

#define REG_SD3_CMD_OFFSET                                 0x100000
#define REG_SD3_CMD_ADDR                                   (HW_REG_BASE + REG_SD3_CMD_OFFSET)
#define reg_SD_SD3_CMD                                     (*( REGType16v *) REG_SD3_CMD_ADDR)

/* SD3_PORTSEL */

#define REG_SD3_PORTSEL_OFFSET                             0x100002
#define REG_SD3_PORTSEL_ADDR                               (HW_REG_BASE + REG_SD3_PORTSEL_OFFSET)
#define reg_SD_SD3_PORTSEL                                 (*( REGType16v *) REG_SD3_PORTSEL_ADDR)

/* SD3_ARG0 */

#define REG_SD3_ARG0_OFFSET                                0x100004
#define REG_SD3_ARG0_ADDR                                  (HW_REG_BASE + REG_SD3_ARG0_OFFSET)
#define reg_SD_SD3_ARG0                                    (*( REGType16v *) REG_SD3_ARG0_ADDR)

/* SD3_ARG1 */

#define REG_SD3_ARG1_OFFSET                                0x100006
#define REG_SD3_ARG1_ADDR                                  (HW_REG_BASE + REG_SD3_ARG1_OFFSET)
#define reg_SD_SD3_ARG1                                    (*( REGType16v *) REG_SD3_ARG1_ADDR)

/* SD3_STOP */

#define REG_SD3_STOP_OFFSET                                0x100008
#define REG_SD3_STOP_ADDR                                  (HW_REG_BASE + REG_SD3_STOP_OFFSET)
#define reg_SD_SD3_STOP                                    (*( REGType16v *) REG_SD3_STOP_ADDR)

/* SD3_SECCNT */

#define REG_SD3_SECCNT_OFFSET                              0x10000a
#define REG_SD3_SECCNT_ADDR                                (HW_REG_BASE + REG_SD3_SECCNT_OFFSET)
#define reg_SD_SD3_SECCNT                                  (*( REGType16v *) REG_SD3_SECCNT_ADDR)

/* SD3_RSP0 */

#define REG_SD3_RSP0_OFFSET                                0x10000c
#define REG_SD3_RSP0_ADDR                                  (HW_REG_BASE + REG_SD3_RSP0_OFFSET)
#define reg_SD_SD3_RSP0                                    (*(const REGType16v *) REG_SD3_RSP0_ADDR)

/* SD3_RSP1 */

#define REG_SD3_RSP1_OFFSET                                0x10000e
#define REG_SD3_RSP1_ADDR                                  (HW_REG_BASE + REG_SD3_RSP1_OFFSET)
#define reg_SD_SD3_RSP1                                    (*(const REGType16v *) REG_SD3_RSP1_ADDR)

/* SD3_RSP2 */

#define REG_SD3_RSP2_OFFSET                                0x100010
#define REG_SD3_RSP2_ADDR                                  (HW_REG_BASE + REG_SD3_RSP2_OFFSET)
#define reg_SD_SD3_RSP2                                    (*(const REGType16v *) REG_SD3_RSP2_ADDR)

/* SD3_RSP3 */

#define REG_SD3_RSP3_OFFSET                                0x100012
#define REG_SD3_RSP3_ADDR                                  (HW_REG_BASE + REG_SD3_RSP3_OFFSET)
#define reg_SD_SD3_RSP3                                    (*(const REGType16v *) REG_SD3_RSP3_ADDR)

/* SD3_RSP4 */

#define REG_SD3_RSP4_OFFSET                                0x100014
#define REG_SD3_RSP4_ADDR                                  (HW_REG_BASE + REG_SD3_RSP4_OFFSET)
#define reg_SD_SD3_RSP4                                    (*(const REGType16v *) REG_SD3_RSP4_ADDR)

/* SD3_RSP5 */

#define REG_SD3_RSP5_OFFSET                                0x100016
#define REG_SD3_RSP5_ADDR                                  (HW_REG_BASE + REG_SD3_RSP5_OFFSET)
#define reg_SD_SD3_RSP5                                    (*(const REGType16v *) REG_SD3_RSP5_ADDR)

/* SD3_RSP6 */

#define REG_SD3_RSP6_OFFSET                                0x100018
#define REG_SD3_RSP6_ADDR                                  (HW_REG_BASE + REG_SD3_RSP6_OFFSET)
#define reg_SD_SD3_RSP6                                    (*(const REGType16v *) REG_SD3_RSP6_ADDR)

/* SD3_RSP7 */

#define REG_SD3_RSP7_OFFSET                                0x10001a
#define REG_SD3_RSP7_ADDR                                  (HW_REG_BASE + REG_SD3_RSP7_OFFSET)
#define reg_SD_SD3_RSP7                                    (*(const REGType16v *) REG_SD3_RSP7_ADDR)

/* SD3_INFO1 */

#define REG_SD3_INFO1_OFFSET                               0x10001c
#define REG_SD3_INFO1_ADDR                                 (HW_REG_BASE + REG_SD3_INFO1_OFFSET)
#define reg_SD_SD3_INFO1                                   (*( REGType16v *) REG_SD3_INFO1_ADDR)

/* SD3_INFO2 */

#define REG_SD3_INFO2_OFFSET                               0x10001e
#define REG_SD3_INFO2_ADDR                                 (HW_REG_BASE + REG_SD3_INFO2_OFFSET)
#define reg_SD_SD3_INFO2                                   (*( REGType16v *) REG_SD3_INFO2_ADDR)

/* SD3_INFO1_MASK */

#define REG_SD3_INFO1_MASK_OFFSET                          0x100020
#define REG_SD3_INFO1_MASK_ADDR                            (HW_REG_BASE + REG_SD3_INFO1_MASK_OFFSET)
#define reg_SD_SD3_INFO1_MASK                              (*( REGType16v *) REG_SD3_INFO1_MASK_ADDR)

/* SD3_INFO2_MASK */

#define REG_SD3_INFO2_MASK_OFFSET                          0x100022
#define REG_SD3_INFO2_MASK_ADDR                            (HW_REG_BASE + REG_SD3_INFO2_MASK_OFFSET)
#define reg_SD_SD3_INFO2_MASK                              (*( REGType16v *) REG_SD3_INFO2_MASK_ADDR)

/* SD3_CLK_CTRL */

#define REG_SD3_CLK_CTRL_OFFSET                            0x100024
#define REG_SD3_CLK_CTRL_ADDR                              (HW_REG_BASE + REG_SD3_CLK_CTRL_OFFSET)
#define reg_SD_SD3_CLK_CTRL                                (*( REGType16v *) REG_SD3_CLK_CTRL_ADDR)

/* SD3_SIZE */

#define REG_SD3_SIZE_OFFSET                                0x100026
#define REG_SD3_SIZE_ADDR                                  (HW_REG_BASE + REG_SD3_SIZE_OFFSET)
#define reg_SD_SD3_SIZE                                    (*( REGType16v *) REG_SD3_SIZE_ADDR)

/* SD3_OPTION */

#define REG_SD3_OPTION_OFFSET                              0x100028
#define REG_SD3_OPTION_ADDR                                (HW_REG_BASE + REG_SD3_OPTION_OFFSET)
#define reg_SD_SD3_OPTION                                  (*( REGType16v *) REG_SD3_OPTION_ADDR)

/* SD3_ERR_STS1 */

#define REG_SD3_ERR_STS1_OFFSET                            0x10002a
#define REG_SD3_ERR_STS1_ADDR                              (HW_REG_BASE + REG_SD3_ERR_STS1_OFFSET)
#define reg_SD_SD3_ERR_STS1                                (*(const REGType16v *) REG_SD3_ERR_STS1_ADDR)

/* SD3_ERR_STS2 */

#define REG_SD3_ERR_STS2_OFFSET                            0x10002c
#define REG_SD3_ERR_STS2_ADDR                              (HW_REG_BASE + REG_SD3_ERR_STS2_OFFSET)
#define reg_SD_SD3_ERR_STS2                                (*(const REGType16v *) REG_SD3_ERR_STS2_ADDR)

/* SD3_BUF0 */

#define REG_SD3_BUF0_OFFSET                                0x10002e
#define REG_SD3_BUF0_ADDR                                  (HW_REG_BASE + REG_SD3_BUF0_OFFSET)
#define reg_SD_SD3_BUF0                                    (*( REGType16v *) REG_SD3_BUF0_ADDR)

/* SDIO3_MODE */

#define REG_SDIO3_MODE_OFFSET                              0x100030
#define REG_SDIO3_MODE_ADDR                                (HW_REG_BASE + REG_SDIO3_MODE_OFFSET)
#define reg_SD_SDIO3_MODE                                  (*( REGType16v *) REG_SDIO3_MODE_ADDR)

/* SDIO3_INFO1 */

#define REG_SDIO3_INFO1_OFFSET                             0x100034
#define REG_SDIO3_INFO1_ADDR                               (HW_REG_BASE + REG_SDIO3_INFO1_OFFSET)
#define reg_SD_SDIO3_INFO1                                 (*( REGType16v *) REG_SDIO3_INFO1_ADDR)

/* SDIO3_INF1_MASK */

#define REG_SDIO3_INF1_MASK_OFFSET                         0x100038
#define REG_SDIO3_INF1_MASK_ADDR                           (HW_REG_BASE + REG_SDIO3_INF1_MASK_OFFSET)
#define reg_SD_SDIO3_INF1_MASK                             (*( REGType16v *) REG_SDIO3_INF1_MASK_ADDR)

/* SD3_CC_EXT_MODE */

#define REG_SD3_CC_EXT_MODE_OFFSET                         0x1000d8
#define REG_SD3_CC_EXT_MODE_ADDR                           (HW_REG_BASE + REG_SD3_CC_EXT_MODE_OFFSET)
#define reg_SD_SD3_CC_EXT_MODE                             (*( REGType16v *) REG_SD3_CC_EXT_MODE_ADDR)

/* SD3_SOFT_RST */

#define REG_SD3_SOFT_RST_OFFSET                            0x1000e0
#define REG_SD3_SOFT_RST_ADDR                              (HW_REG_BASE + REG_SD3_SOFT_RST_OFFSET)
#define reg_SD_SD3_SOFT_RST                                (*( REGType16v *) REG_SD3_SOFT_RST_ADDR)

/* SD3_VERSION */

#define REG_SD3_VERSION_OFFSET                             0x1000e2
#define REG_SD3_VERSION_ADDR                               (HW_REG_BASE + REG_SD3_VERSION_OFFSET)
#define reg_SD_SD3_VERSION                                 (*(const REGType16v *) REG_SD3_VERSION_ADDR)

/* SD3_PWR */

#define REG_SD3_PWR_OFFSET                                 0x1000f2
#define REG_SD3_PWR_ADDR                                   (HW_REG_BASE + REG_SD3_PWR_OFFSET)
#define reg_SD_SD3_PWR                                     (*( REGType16v *) REG_SD3_PWR_ADDR)

/* SD3_EXT_SDIO */

#define REG_SD3_EXT_SDIO_OFFSET                            0x1000f4
#define REG_SD3_EXT_SDIO_ADDR                              (HW_REG_BASE + REG_SD3_EXT_SDIO_OFFSET)
#define reg_SD_SD3_EXT_SDIO                                (*( REGType16v *) REG_SD3_EXT_SDIO_ADDR)

/* SD3_EXT_WP */

#define REG_SD3_EXT_WP_OFFSET                              0x1000f6
#define REG_SD3_EXT_WP_ADDR                                (HW_REG_BASE + REG_SD3_EXT_WP_OFFSET)
#define reg_SD_SD3_EXT_WP                                  (*(const REGType16v *) REG_SD3_EXT_WP_ADDR)

/* SD3_EXT_CD */

#define REG_SD3_EXT_CD_OFFSET                              0x1000f8
#define REG_SD3_EXT_CD_ADDR                                (HW_REG_BASE + REG_SD3_EXT_CD_OFFSET)
#define reg_SD_SD3_EXT_CD                                  (*( REGType16v *) REG_SD3_EXT_CD_ADDR)

/* SD3_EXT_CD_DAT3 */

#define REG_SD3_EXT_CD_DAT3_OFFSET                         0x1000fa
#define REG_SD3_EXT_CD_DAT3_ADDR                           (HW_REG_BASE + REG_SD3_EXT_CD_DAT3_OFFSET)
#define reg_SD_SD3_EXT_CD_DAT3                             (*( REGType16v *) REG_SD3_EXT_CD_DAT3_ADDR)

/* SD3_EXT_CD_MASK */

#define REG_SD3_EXT_CD_MASK_OFFSET                         0x1000fc
#define REG_SD3_EXT_CD_MASK_ADDR                           (HW_REG_BASE + REG_SD3_EXT_CD_MASK_OFFSET)
#define reg_SD_SD3_EXT_CD_MASK                             (*( REGType16v *) REG_SD3_EXT_CD_MASK_ADDR)

/* SD3_EXT_CD_DAT3_MASK */

#define REG_SD3_EXT_CD_DAT3_MASK_OFFSET                    0x1000fe
#define REG_SD3_EXT_CD_DAT3_MASK_ADDR                      (HW_REG_BASE + REG_SD3_EXT_CD_DAT3_MASK_OFFSET)
#define reg_SD_SD3_EXT_CD_DAT3_MASK                        (*( REGType16v *) REG_SD3_EXT_CD_DAT3_MASK_ADDR)

/* SD3_CNT */

#define REG_SD3_CNT_OFFSET                                 0x100100
#define REG_SD3_CNT_ADDR                                   (HW_REG_BASE + REG_SD3_CNT_OFFSET)
#define reg_SD_SD3_CNT                                     (*( REGType16v *) REG_SD3_CNT_ADDR)

/* SD3_FDS */

#define REG_SD3_FDS_OFFSET                                 0x100104
#define REG_SD3_FDS_ADDR                                   (HW_REG_BASE + REG_SD3_FDS_OFFSET)
#define reg_SD_SD3_FDS                                     (*( REGType16v *) REG_SD3_FDS_ADDR)

/* SD3_FSC */

#define REG_SD3_FSC_OFFSET                                 0x100108
#define REG_SD3_FSC_ADDR                                   (HW_REG_BASE + REG_SD3_FSC_OFFSET)
#define reg_SD_SD3_FSC                                     (*( REGType16v *) REG_SD3_FSC_ADDR)

/* SD3_FI */

#define REG_SD3_FI_OFFSET                                  0x300000
#define REG_SD3_FI_ADDR                                    (HW_REG_BASE + REG_SD3_FI_OFFSET)
#define reg_SD_SD3_FI                                      (*( REGType32v *) REG_SD3_FI_ADDR)


/*
 * Definitions of Register fields
 */


/* SD2_CMD */

/* SD2_PORTSEL */

/* SD2_ARG0 */

/* SD2_ARG1 */

/* SD2_STOP */

/* SD2_SECCNT */

/* SD2_RSP0 */

/* SD2_RSP1 */

/* SD2_RSP2 */

/* SD2_RSP3 */

/* SD2_RSP4 */

/* SD2_RSP5 */

/* SD2_RSP6 */

/* SD2_RSP7 */

/* SD2_INFO1 */

/* SD2_INFO2 */

/* SD2_INFO1_MASK */

/* SD2_INFO2_MASK */

/* SD2_CLK_CTRL */

/* SD2_SIZE */

/* SD2_OPTION */

/* SD2_ERR_STS1 */

/* SD2_ERR_STS2 */

/* SD2_BUF0 */

/* SDIO2_MODE */

/* SDIO2_INFO1 */

/* SDIO2_INF1_MASK */

/* SD2_CC_EXT_MODE */

/* SD2_SOFT_RST */

/* SD2_VERSION */

/* DS2_PWR */

/* SD2_EXT_SDIO */

/* SD2_EXT_WP */

/* SD2_EXT_CD */

/* SD2_EXT_CD_DAT3 */

/* SD2_EXT_CD_MASK */

/* SD2_EXT_CD_DAT3_MASK */

/* SD2_CNT */

#define REG_SD_SD2_CNT_FEIE_SHIFT                          12
#define REG_SD_SD2_CNT_FEIE_SIZE                           1
#define REG_SD_SD2_CNT_FEIE_MASK                           0x1000

#define REG_SD_SD2_CNT_FFIE_SHIFT                          11
#define REG_SD_SD2_CNT_FFIE_SIZE                           1
#define REG_SD_SD2_CNT_FFIE_MASK                           0x0800

#define REG_SD_SD2_CNT_FCLR_SHIFT                          10
#define REG_SD_SD2_CNT_FCLR_SIZE                           1
#define REG_SD_SD2_CNT_FCLR_MASK                           0x0400

#define REG_SD_SD2_CNT_NEMP_SHIFT                          9
#define REG_SD_SD2_CNT_NEMP_SIZE                           1
#define REG_SD_SD2_CNT_NEMP_MASK                           0x0200

#define REG_SD_SD2_CNT_FULL_SHIFT                          8
#define REG_SD_SD2_CNT_FULL_SIZE                           1
#define REG_SD_SD2_CNT_FULL_MASK                           0x0100

#define REG_SD_SD2_CNT_FIFO_SHIFT                          1
#define REG_SD_SD2_CNT_FIFO_SIZE                           1
#define REG_SD_SD2_CNT_FIFO_MASK                           0x0002

#ifndef SDK_ASM
#define REG_SD_SD2_CNT_FIELD( feie, ffie, fclr, nemp, full, fifo ) \
    (u16)( \
    ((u32)(feie) << REG_SD_SD2_CNT_FEIE_SHIFT) | \
    ((u32)(ffie) << REG_SD_SD2_CNT_FFIE_SHIFT) | \
    ((u32)(fclr) << REG_SD_SD2_CNT_FCLR_SHIFT) | \
    ((u32)(nemp) << REG_SD_SD2_CNT_NEMP_SHIFT) | \
    ((u32)(full) << REG_SD_SD2_CNT_FULL_SHIFT) | \
    ((u32)(fifo) << REG_SD_SD2_CNT_FIFO_SHIFT))
#endif


/* SD2_FDS */

#define REG_SD_SD2_FDS_SIZE_SHIFT                          0
#define REG_SD_SD2_FDS_SIZE_SIZE                           10
#define REG_SD_SD2_FDS_SIZE_MASK                           0x03ff

#ifndef SDK_ASM
#define REG_SD_SD2_FDS_FIELD( size ) \
    (u16)( \
    ((u32)(size) << REG_SD_SD2_FDS_SIZE_SHIFT))
#endif


/* SD2_FSC */

#define REG_SD_SD2_FSC_COUNT_SHIFT                         0
#define REG_SD_SD2_FSC_COUNT_SIZE                          16
#define REG_SD_SD2_FSC_COUNT_MASK                          0xffff

#ifndef SDK_ASM
#define REG_SD_SD2_FSC_FIELD( count ) \
    (u16)( \
    ((u32)(count) << REG_SD_SD2_FSC_COUNT_SHIFT))
#endif


/* SD2_FI */

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

/* NN_HW_CTR_TEG2_MPCORE_IOREG_SD_H_ */
#endif
