/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-NE1TB/MPCore/ioreg_ne1patch_SD.h

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
#ifndef NN_HW_CTR_NE1TB_MPCORE_IOREG_NE1PATCH_SD_H_
#define NN_HW_CTR_NE1TB_MPCORE_IOREG_NE1PATCH_SD_H_

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

#define REG_SD2_CMD_OFFSET                                 0x30000
#define REG_SD2_CMD_ADDR                                   (HW_NE1IOP_REG + REG_SD2_CMD_OFFSET)
#define reg_SD_SD2_CMD                                     (*( REGType16v *) REG_SD2_CMD_ADDR)

/* SD2_PORTSEL */

#define REG_SD2_PORTSEL_OFFSET                             0x30002
#define REG_SD2_PORTSEL_ADDR                               (HW_NE1IOP_REG + REG_SD2_PORTSEL_OFFSET)
#define reg_SD_SD2_PORTSEL                                 (*( REGType16v *) REG_SD2_PORTSEL_ADDR)

/* SD2_ARG0 */

#define REG_SD2_ARG0_OFFSET                                0x30004
#define REG_SD2_ARG0_ADDR                                  (HW_NE1IOP_REG + REG_SD2_ARG0_OFFSET)
#define reg_SD_SD2_ARG0                                    (*( REGType16v *) REG_SD2_ARG0_ADDR)

/* SD2_ARG1 */

#define REG_SD2_ARG1_OFFSET                                0x30006
#define REG_SD2_ARG1_ADDR                                  (HW_NE1IOP_REG + REG_SD2_ARG1_OFFSET)
#define reg_SD_SD2_ARG1                                    (*( REGType16v *) REG_SD2_ARG1_ADDR)

/* SD2_STOP */

#define REG_SD2_STOP_OFFSET                                0x30008
#define REG_SD2_STOP_ADDR                                  (HW_NE1IOP_REG + REG_SD2_STOP_OFFSET)
#define reg_SD_SD2_STOP                                    (*( REGType16v *) REG_SD2_STOP_ADDR)

/* SD2_SECCNT */

#define REG_SD2_SECCNT_OFFSET                              0x3000a
#define REG_SD2_SECCNT_ADDR                                (HW_NE1IOP_REG + REG_SD2_SECCNT_OFFSET)
#define reg_SD_SD2_SECCNT                                  (*( REGType16v *) REG_SD2_SECCNT_ADDR)

/* SD2_RSP0 */

#define REG_SD2_RSP0_OFFSET                                0x3000c
#define REG_SD2_RSP0_ADDR                                  (HW_NE1IOP_REG + REG_SD2_RSP0_OFFSET)
#define reg_SD_SD2_RSP0                                    (*(const REGType16v *) REG_SD2_RSP0_ADDR)

/* SD2_RSP1 */

#define REG_SD2_RSP1_OFFSET                                0x3000e
#define REG_SD2_RSP1_ADDR                                  (HW_NE1IOP_REG + REG_SD2_RSP1_OFFSET)
#define reg_SD_SD2_RSP1                                    (*(const REGType16v *) REG_SD2_RSP1_ADDR)

/* SD2_RSP2 */

#define REG_SD2_RSP2_OFFSET                                0x30010
#define REG_SD2_RSP2_ADDR                                  (HW_NE1IOP_REG + REG_SD2_RSP2_OFFSET)
#define reg_SD_SD2_RSP2                                    (*(const REGType16v *) REG_SD2_RSP2_ADDR)

/* SD2_RSP3 */

#define REG_SD2_RSP3_OFFSET                                0x30012
#define REG_SD2_RSP3_ADDR                                  (HW_NE1IOP_REG + REG_SD2_RSP3_OFFSET)
#define reg_SD_SD2_RSP3                                    (*(const REGType16v *) REG_SD2_RSP3_ADDR)

/* SD2_RSP4 */

#define REG_SD2_RSP4_OFFSET                                0x30014
#define REG_SD2_RSP4_ADDR                                  (HW_NE1IOP_REG + REG_SD2_RSP4_OFFSET)
#define reg_SD_SD2_RSP4                                    (*(const REGType16v *) REG_SD2_RSP4_ADDR)

/* SD2_RSP5 */

#define REG_SD2_RSP5_OFFSET                                0x30016
#define REG_SD2_RSP5_ADDR                                  (HW_NE1IOP_REG + REG_SD2_RSP5_OFFSET)
#define reg_SD_SD2_RSP5                                    (*(const REGType16v *) REG_SD2_RSP5_ADDR)

/* SD2_RSP6 */

#define REG_SD2_RSP6_OFFSET                                0x30018
#define REG_SD2_RSP6_ADDR                                  (HW_NE1IOP_REG + REG_SD2_RSP6_OFFSET)
#define reg_SD_SD2_RSP6                                    (*(const REGType16v *) REG_SD2_RSP6_ADDR)

/* SD2_RSP7 */

#define REG_SD2_RSP7_OFFSET                                0x3001a
#define REG_SD2_RSP7_ADDR                                  (HW_NE1IOP_REG + REG_SD2_RSP7_OFFSET)
#define reg_SD_SD2_RSP7                                    (*(const REGType16v *) REG_SD2_RSP7_ADDR)

/* SD2_INFO1 */

#define REG_SD2_INFO1_OFFSET                               0x3001c
#define REG_SD2_INFO1_ADDR                                 (HW_NE1IOP_REG + REG_SD2_INFO1_OFFSET)
#define reg_SD_SD2_INFO1                                   (*( REGType16v *) REG_SD2_INFO1_ADDR)

/* SD2_INFO2 */

#define REG_SD2_INFO2_OFFSET                               0x3001e
#define REG_SD2_INFO2_ADDR                                 (HW_NE1IOP_REG + REG_SD2_INFO2_OFFSET)
#define reg_SD_SD2_INFO2                                   (*( REGType16v *) REG_SD2_INFO2_ADDR)

/* SD2_INFO1_MASK */

#define REG_SD2_INFO1_MASK_OFFSET                          0x30020
#define REG_SD2_INFO1_MASK_ADDR                            (HW_NE1IOP_REG + REG_SD2_INFO1_MASK_OFFSET)
#define reg_SD_SD2_INFO1_MASK                              (*( REGType16v *) REG_SD2_INFO1_MASK_ADDR)

/* SD2_INFO2_MASK */

#define REG_SD2_INFO2_MASK_OFFSET                          0x30022
#define REG_SD2_INFO2_MASK_ADDR                            (HW_NE1IOP_REG + REG_SD2_INFO2_MASK_OFFSET)
#define reg_SD_SD2_INFO2_MASK                              (*( REGType16v *) REG_SD2_INFO2_MASK_ADDR)

/* SD2_CLK_CTRL */

#define REG_SD2_CLK_CTRL_OFFSET                            0x30024
#define REG_SD2_CLK_CTRL_ADDR                              (HW_NE1IOP_REG + REG_SD2_CLK_CTRL_OFFSET)
#define reg_SD_SD2_CLK_CTRL                                (*( REGType16v *) REG_SD2_CLK_CTRL_ADDR)

/* SD2_SIZE */

#define REG_SD2_SIZE_OFFSET                                0x30026
#define REG_SD2_SIZE_ADDR                                  (HW_NE1IOP_REG + REG_SD2_SIZE_OFFSET)
#define reg_SD_SD2_SIZE                                    (*( REGType16v *) REG_SD2_SIZE_ADDR)

/* SD2_OPTION */

#define REG_SD2_OPTION_OFFSET                              0x30028
#define REG_SD2_OPTION_ADDR                                (HW_NE1IOP_REG + REG_SD2_OPTION_OFFSET)
#define reg_SD_SD2_OPTION                                  (*( REGType16v *) REG_SD2_OPTION_ADDR)

/* SD2_ERR_STS1 */

#define REG_SD2_ERR_STS1_OFFSET                            0x3002a
#define REG_SD2_ERR_STS1_ADDR                              (HW_NE1IOP_REG + REG_SD2_ERR_STS1_OFFSET)
#define reg_SD_SD2_ERR_STS1                                (*(const REGType16v *) REG_SD2_ERR_STS1_ADDR)

/* SD2_ERR_STS2 */

#define REG_SD2_ERR_STS2_OFFSET                            0x3002c
#define REG_SD2_ERR_STS2_ADDR                              (HW_NE1IOP_REG + REG_SD2_ERR_STS2_OFFSET)
#define reg_SD_SD2_ERR_STS2                                (*(const REGType16v *) REG_SD2_ERR_STS2_ADDR)

/* SD2_BUF0 */

#define REG_SD2_BUF0_OFFSET                                0x3002e
#define REG_SD2_BUF0_ADDR                                  (HW_NE1IOP_REG + REG_SD2_BUF0_OFFSET)
#define reg_SD_SD2_BUF0                                    (*( REGType16v *) REG_SD2_BUF0_ADDR)

/* SDIO2_MODE */

#define REG_SDIO2_MODE_OFFSET                              0x30030
#define REG_SDIO2_MODE_ADDR                                (HW_NE1IOP_REG + REG_SDIO2_MODE_OFFSET)
#define reg_SD_SDIO2_MODE                                  (*( REGType16v *) REG_SDIO2_MODE_ADDR)

/* SDIO2_INFO1 */

#define REG_SDIO2_INFO1_OFFSET                             0x30034
#define REG_SDIO2_INFO1_ADDR                               (HW_NE1IOP_REG + REG_SDIO2_INFO1_OFFSET)
#define reg_SD_SDIO2_INFO1                                 (*( REGType16v *) REG_SDIO2_INFO1_ADDR)

/* SDIO2_INF1_MASK */

#define REG_SDIO2_INF1_MASK_OFFSET                         0x30038
#define REG_SDIO2_INF1_MASK_ADDR                           (HW_NE1IOP_REG + REG_SDIO2_INF1_MASK_OFFSET)
#define reg_SD_SDIO2_INF1_MASK                             (*( REGType16v *) REG_SDIO2_INF1_MASK_ADDR)

/* SD2_CC_EXT_MODE */

#define REG_SD2_CC_EXT_MODE_OFFSET                         0x300d8
#define REG_SD2_CC_EXT_MODE_ADDR                           (HW_NE1IOP_REG + REG_SD2_CC_EXT_MODE_OFFSET)
#define reg_SD_SD2_CC_EXT_MODE                             (*( REGType16v *) REG_SD2_CC_EXT_MODE_ADDR)

/* SD2_SOFT_RST */

#define REG_SD2_SOFT_RST_OFFSET                            0x300e0
#define REG_SD2_SOFT_RST_ADDR                              (HW_NE1IOP_REG + REG_SD2_SOFT_RST_OFFSET)
#define reg_SD_SD2_SOFT_RST                                (*( REGType16v *) REG_SD2_SOFT_RST_ADDR)

/* SD2_VERSION */

#define REG_SD2_VERSION_OFFSET                             0x300e2
#define REG_SD2_VERSION_ADDR                               (HW_NE1IOP_REG + REG_SD2_VERSION_OFFSET)
#define reg_SD_SD2_VERSION                                 (*(const REGType16v *) REG_SD2_VERSION_ADDR)

/* DS2_PWR */

#define REG_DS2_PWR_OFFSET                                 0x300f2
#define REG_DS2_PWR_ADDR                                   (HW_NE1IOP_REG + REG_DS2_PWR_OFFSET)
#define reg_SD_DS2_PWR                                     (*( REGType16v *) REG_DS2_PWR_ADDR)

/* SD2_EXT_SDIO */

#define REG_SD2_EXT_SDIO_OFFSET                            0x300f4
#define REG_SD2_EXT_SDIO_ADDR                              (HW_NE1IOP_REG + REG_SD2_EXT_SDIO_OFFSET)
#define reg_SD_SD2_EXT_SDIO                                (*( REGType16v *) REG_SD2_EXT_SDIO_ADDR)

/* SD2_EXT_WP */

#define REG_SD2_EXT_WP_OFFSET                              0x300f6
#define REG_SD2_EXT_WP_ADDR                                (HW_NE1IOP_REG + REG_SD2_EXT_WP_OFFSET)
#define reg_SD_SD2_EXT_WP                                  (*(const REGType16v *) REG_SD2_EXT_WP_ADDR)

/* SD2_EXT_CD */

#define REG_SD2_EXT_CD_OFFSET                              0x300f8
#define REG_SD2_EXT_CD_ADDR                                (HW_NE1IOP_REG + REG_SD2_EXT_CD_OFFSET)
#define reg_SD_SD2_EXT_CD                                  (*( REGType16v *) REG_SD2_EXT_CD_ADDR)

/* SD2_EXT_CD_DAT3 */

#define REG_SD2_EXT_CD_DAT3_OFFSET                         0x300fa
#define REG_SD2_EXT_CD_DAT3_ADDR                           (HW_NE1IOP_REG + REG_SD2_EXT_CD_DAT3_OFFSET)
#define reg_SD_SD2_EXT_CD_DAT3                             (*( REGType16v *) REG_SD2_EXT_CD_DAT3_ADDR)

/* SD2_EXT_CD_MASK */

#define REG_SD2_EXT_CD_MASK_OFFSET                         0x300fc
#define REG_SD2_EXT_CD_MASK_ADDR                           (HW_NE1IOP_REG + REG_SD2_EXT_CD_MASK_OFFSET)
#define reg_SD_SD2_EXT_CD_MASK                             (*( REGType16v *) REG_SD2_EXT_CD_MASK_ADDR)

/* SD2_EXT_CD_DAT3_MASK */

#define REG_SD2_EXT_CD_DAT3_MASK_OFFSET                    0x300fe
#define REG_SD2_EXT_CD_DAT3_MASK_ADDR                      (HW_NE1IOP_REG + REG_SD2_EXT_CD_DAT3_MASK_OFFSET)
#define reg_SD_SD2_EXT_CD_DAT3_MASK                        (*( REGType16v *) REG_SD2_EXT_CD_DAT3_MASK_ADDR)

/* SD3_CMD */

#define REG_SD3_CMD_OFFSET                                 0x30000
#define REG_SD3_CMD_ADDR                                   (HW_NE1IOP_REG + REG_SD3_CMD_OFFSET)
#define reg_SD_SD3_CMD                                     (*( REGType16v *) REG_SD3_CMD_ADDR)

/* SD3_PORTSEL */

#define REG_SD3_PORTSEL_OFFSET                             0x30002
#define REG_SD3_PORTSEL_ADDR                               (HW_NE1IOP_REG + REG_SD3_PORTSEL_OFFSET)
#define reg_SD_SD3_PORTSEL                                 (*( REGType16v *) REG_SD3_PORTSEL_ADDR)

/* SD3_ARG0 */

#define REG_SD3_ARG0_OFFSET                                0x30004
#define REG_SD3_ARG0_ADDR                                  (HW_NE1IOP_REG + REG_SD3_ARG0_OFFSET)
#define reg_SD_SD3_ARG0                                    (*( REGType16v *) REG_SD3_ARG0_ADDR)

/* SD3_ARG1 */

#define REG_SD3_ARG1_OFFSET                                0x30006
#define REG_SD3_ARG1_ADDR                                  (HW_NE1IOP_REG + REG_SD3_ARG1_OFFSET)
#define reg_SD_SD3_ARG1                                    (*( REGType16v *) REG_SD3_ARG1_ADDR)

/* SD3_STOP */

#define REG_SD3_STOP_OFFSET                                0x30008
#define REG_SD3_STOP_ADDR                                  (HW_NE1IOP_REG + REG_SD3_STOP_OFFSET)
#define reg_SD_SD3_STOP                                    (*( REGType16v *) REG_SD3_STOP_ADDR)

/* SD3_SECCNT */

#define REG_SD3_SECCNT_OFFSET                              0x3000a
#define REG_SD3_SECCNT_ADDR                                (HW_NE1IOP_REG + REG_SD3_SECCNT_OFFSET)
#define reg_SD_SD3_SECCNT                                  (*( REGType16v *) REG_SD3_SECCNT_ADDR)

/* SD3_RSP0 */

#define REG_SD3_RSP0_OFFSET                                0x3000c
#define REG_SD3_RSP0_ADDR                                  (HW_NE1IOP_REG + REG_SD3_RSP0_OFFSET)
#define reg_SD_SD3_RSP0                                    (*(const REGType16v *) REG_SD3_RSP0_ADDR)

/* SD3_RSP1 */

#define REG_SD3_RSP1_OFFSET                                0x3000e
#define REG_SD3_RSP1_ADDR                                  (HW_NE1IOP_REG + REG_SD3_RSP1_OFFSET)
#define reg_SD_SD3_RSP1                                    (*(const REGType16v *) REG_SD3_RSP1_ADDR)

/* SD3_RSP2 */

#define REG_SD3_RSP2_OFFSET                                0x30010
#define REG_SD3_RSP2_ADDR                                  (HW_NE1IOP_REG + REG_SD3_RSP2_OFFSET)
#define reg_SD_SD3_RSP2                                    (*(const REGType16v *) REG_SD3_RSP2_ADDR)

/* SD3_RSP3 */

#define REG_SD3_RSP3_OFFSET                                0x30012
#define REG_SD3_RSP3_ADDR                                  (HW_NE1IOP_REG + REG_SD3_RSP3_OFFSET)
#define reg_SD_SD3_RSP3                                    (*(const REGType16v *) REG_SD3_RSP3_ADDR)

/* SD3_RSP4 */

#define REG_SD3_RSP4_OFFSET                                0x30014
#define REG_SD3_RSP4_ADDR                                  (HW_NE1IOP_REG + REG_SD3_RSP4_OFFSET)
#define reg_SD_SD3_RSP4                                    (*(const REGType16v *) REG_SD3_RSP4_ADDR)

/* SD3_RSP5 */

#define REG_SD3_RSP5_OFFSET                                0x30016
#define REG_SD3_RSP5_ADDR                                  (HW_NE1IOP_REG + REG_SD3_RSP5_OFFSET)
#define reg_SD_SD3_RSP5                                    (*(const REGType16v *) REG_SD3_RSP5_ADDR)

/* SD3_RSP6 */

#define REG_SD3_RSP6_OFFSET                                0x30018
#define REG_SD3_RSP6_ADDR                                  (HW_NE1IOP_REG + REG_SD3_RSP6_OFFSET)
#define reg_SD_SD3_RSP6                                    (*(const REGType16v *) REG_SD3_RSP6_ADDR)

/* SD3_RSP7 */

#define REG_SD3_RSP7_OFFSET                                0x3001a
#define REG_SD3_RSP7_ADDR                                  (HW_NE1IOP_REG + REG_SD3_RSP7_OFFSET)
#define reg_SD_SD3_RSP7                                    (*(const REGType16v *) REG_SD3_RSP7_ADDR)

/* SD3_INFO1 */

#define REG_SD3_INFO1_OFFSET                               0x3001c
#define REG_SD3_INFO1_ADDR                                 (HW_NE1IOP_REG + REG_SD3_INFO1_OFFSET)
#define reg_SD_SD3_INFO1                                   (*( REGType16v *) REG_SD3_INFO1_ADDR)

/* SD3_INFO2 */

#define REG_SD3_INFO2_OFFSET                               0x3001e
#define REG_SD3_INFO2_ADDR                                 (HW_NE1IOP_REG + REG_SD3_INFO2_OFFSET)
#define reg_SD_SD3_INFO2                                   (*( REGType16v *) REG_SD3_INFO2_ADDR)

/* SD3_INFO1_MASK */

#define REG_SD3_INFO1_MASK_OFFSET                          0x30020
#define REG_SD3_INFO1_MASK_ADDR                            (HW_NE1IOP_REG + REG_SD3_INFO1_MASK_OFFSET)
#define reg_SD_SD3_INFO1_MASK                              (*( REGType16v *) REG_SD3_INFO1_MASK_ADDR)

/* SD3_INFO2_MASK */

#define REG_SD3_INFO2_MASK_OFFSET                          0x30022
#define REG_SD3_INFO2_MASK_ADDR                            (HW_NE1IOP_REG + REG_SD3_INFO2_MASK_OFFSET)
#define reg_SD_SD3_INFO2_MASK                              (*( REGType16v *) REG_SD3_INFO2_MASK_ADDR)

/* SD3_CLK_CTRL */

#define REG_SD3_CLK_CTRL_OFFSET                            0x30024
#define REG_SD3_CLK_CTRL_ADDR                              (HW_NE1IOP_REG + REG_SD3_CLK_CTRL_OFFSET)
#define reg_SD_SD3_CLK_CTRL                                (*( REGType16v *) REG_SD3_CLK_CTRL_ADDR)

/* SD3_SIZE */

#define REG_SD3_SIZE_OFFSET                                0x30026
#define REG_SD3_SIZE_ADDR                                  (HW_NE1IOP_REG + REG_SD3_SIZE_OFFSET)
#define reg_SD_SD3_SIZE                                    (*( REGType16v *) REG_SD3_SIZE_ADDR)

/* SD3_OPTION */

#define REG_SD3_OPTION_OFFSET                              0x30028
#define REG_SD3_OPTION_ADDR                                (HW_NE1IOP_REG + REG_SD3_OPTION_OFFSET)
#define reg_SD_SD3_OPTION                                  (*( REGType16v *) REG_SD3_OPTION_ADDR)

/* SD3_ERR_STS1 */

#define REG_SD3_ERR_STS1_OFFSET                            0x3002a
#define REG_SD3_ERR_STS1_ADDR                              (HW_NE1IOP_REG + REG_SD3_ERR_STS1_OFFSET)
#define reg_SD_SD3_ERR_STS1                                (*(const REGType16v *) REG_SD3_ERR_STS1_ADDR)

/* SD3_ERR_STS2 */

#define REG_SD3_ERR_STS2_OFFSET                            0x3002c
#define REG_SD3_ERR_STS2_ADDR                              (HW_NE1IOP_REG + REG_SD3_ERR_STS2_OFFSET)
#define reg_SD_SD3_ERR_STS2                                (*(const REGType16v *) REG_SD3_ERR_STS2_ADDR)

/* SD3_BUF0 */

#define REG_SD3_BUF0_OFFSET                                0x3002e
#define REG_SD3_BUF0_ADDR                                  (HW_NE1IOP_REG + REG_SD3_BUF0_OFFSET)
#define reg_SD_SD3_BUF0                                    (*( REGType16v *) REG_SD3_BUF0_ADDR)

/* SDIO3_MODE */

#define REG_SDIO3_MODE_OFFSET                              0x30030
#define REG_SDIO3_MODE_ADDR                                (HW_NE1IOP_REG + REG_SDIO3_MODE_OFFSET)
#define reg_SD_SDIO3_MODE                                  (*( REGType16v *) REG_SDIO3_MODE_ADDR)

/* SDIO3_INFO1 */

#define REG_SDIO3_INFO1_OFFSET                             0x30034
#define REG_SDIO3_INFO1_ADDR                               (HW_NE1IOP_REG + REG_SDIO3_INFO1_OFFSET)
#define reg_SD_SDIO3_INFO1                                 (*( REGType16v *) REG_SDIO3_INFO1_ADDR)

/* SDIO3_INF1_MASK */

#define REG_SDIO3_INF1_MASK_OFFSET                         0x30038
#define REG_SDIO3_INF1_MASK_ADDR                           (HW_NE1IOP_REG + REG_SDIO3_INF1_MASK_OFFSET)
#define reg_SD_SDIO3_INF1_MASK                             (*( REGType16v *) REG_SDIO3_INF1_MASK_ADDR)

/* SD3_CC_EXT_MODE */

#define REG_SD3_CC_EXT_MODE_OFFSET                         0x300d8
#define REG_SD3_CC_EXT_MODE_ADDR                           (HW_NE1IOP_REG + REG_SD3_CC_EXT_MODE_OFFSET)
#define reg_SD_SD3_CC_EXT_MODE                             (*( REGType16v *) REG_SD3_CC_EXT_MODE_ADDR)

/* SD3_SOFT_RST */

#define REG_SD3_SOFT_RST_OFFSET                            0x300e0
#define REG_SD3_SOFT_RST_ADDR                              (HW_NE1IOP_REG + REG_SD3_SOFT_RST_OFFSET)
#define reg_SD_SD3_SOFT_RST                                (*( REGType16v *) REG_SD3_SOFT_RST_ADDR)

/* SD3_VERSION */

#define REG_SD3_VERSION_OFFSET                             0x300e2
#define REG_SD3_VERSION_ADDR                               (HW_NE1IOP_REG + REG_SD3_VERSION_OFFSET)
#define reg_SD_SD3_VERSION                                 (*(const REGType16v *) REG_SD3_VERSION_ADDR)

/* SD3_PWR */

#define REG_SD3_PWR_OFFSET                                 0x300f2
#define REG_SD3_PWR_ADDR                                   (HW_NE1IOP_REG + REG_SD3_PWR_OFFSET)
#define reg_SD_SD3_PWR                                     (*( REGType16v *) REG_SD3_PWR_ADDR)

/* SD3_EXT_SDIO */

#define REG_SD3_EXT_SDIO_OFFSET                            0x300f4
#define REG_SD3_EXT_SDIO_ADDR                              (HW_NE1IOP_REG + REG_SD3_EXT_SDIO_OFFSET)
#define reg_SD_SD3_EXT_SDIO                                (*( REGType16v *) REG_SD3_EXT_SDIO_ADDR)

/* SD3_EXT_WP */

#define REG_SD3_EXT_WP_OFFSET                              0x300f6
#define REG_SD3_EXT_WP_ADDR                                (HW_NE1IOP_REG + REG_SD3_EXT_WP_OFFSET)
#define reg_SD_SD3_EXT_WP                                  (*(const REGType16v *) REG_SD3_EXT_WP_ADDR)

/* SD3_EXT_CD */

#define REG_SD3_EXT_CD_OFFSET                              0x300f8
#define REG_SD3_EXT_CD_ADDR                                (HW_NE1IOP_REG + REG_SD3_EXT_CD_OFFSET)
#define reg_SD_SD3_EXT_CD                                  (*( REGType16v *) REG_SD3_EXT_CD_ADDR)

/* SD3_EXT_CD_DAT3 */

#define REG_SD3_EXT_CD_DAT3_OFFSET                         0x300fa
#define REG_SD3_EXT_CD_DAT3_ADDR                           (HW_NE1IOP_REG + REG_SD3_EXT_CD_DAT3_OFFSET)
#define reg_SD_SD3_EXT_CD_DAT3                             (*( REGType16v *) REG_SD3_EXT_CD_DAT3_ADDR)

/* SD3_EXT_CD_MASK */

#define REG_SD3_EXT_CD_MASK_OFFSET                         0x300fc
#define REG_SD3_EXT_CD_MASK_ADDR                           (HW_NE1IOP_REG + REG_SD3_EXT_CD_MASK_OFFSET)
#define reg_SD_SD3_EXT_CD_MASK                             (*( REGType16v *) REG_SD3_EXT_CD_MASK_ADDR)

/* SD3_EXT_CD_DAT3_MASK */

#define REG_SD3_EXT_CD_DAT3_MASK_OFFSET                    0x300fe
#define REG_SD3_EXT_CD_DAT3_MASK_ADDR                      (HW_NE1IOP_REG + REG_SD3_EXT_CD_DAT3_MASK_OFFSET)
#define reg_SD_SD3_EXT_CD_DAT3_MASK                        (*( REGType16v *) REG_SD3_EXT_CD_DAT3_MASK_ADDR)


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

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_NE1TB_MPCORE_IOREG_NE1PATCH_SD_H_ */
#endif
