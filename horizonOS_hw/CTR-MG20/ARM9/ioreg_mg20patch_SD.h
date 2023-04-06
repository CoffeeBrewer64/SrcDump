/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-MG20/ARM9/ioreg_mg20patch_SD.h

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
#ifndef NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_SD_H_
#define NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_SD_H_

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

#define REG_SD1_CMD_OFFSET                                 0xb0000
#define REG_SD1_CMD_ADDR                                   (HW_MG20IOP_REG + REG_SD1_CMD_OFFSET)
#define reg_SD_SD1_CMD                                     (*( REGType16v *) REG_SD1_CMD_ADDR)

/* SD1_PORTSEL */

#define REG_SD1_PORTSEL_OFFSET                             0xb0002
#define REG_SD1_PORTSEL_ADDR                               (HW_MG20IOP_REG + REG_SD1_PORTSEL_OFFSET)
#define reg_SD_SD1_PORTSEL                                 (*( REGType16v *) REG_SD1_PORTSEL_ADDR)

/* SD1_ARG0 */

#define REG_SD1_ARG0_OFFSET                                0xb0004
#define REG_SD1_ARG0_ADDR                                  (HW_MG20IOP_REG + REG_SD1_ARG0_OFFSET)
#define reg_SD_SD1_ARG0                                    (*( REGType16v *) REG_SD1_ARG0_ADDR)

/* SD1_ARG1 */

#define REG_SD1_ARG1_OFFSET                                0xb0006
#define REG_SD1_ARG1_ADDR                                  (HW_MG20IOP_REG + REG_SD1_ARG1_OFFSET)
#define reg_SD_SD1_ARG1                                    (*( REGType16v *) REG_SD1_ARG1_ADDR)

/* SD1_STOP */

#define REG_SD1_STOP_OFFSET                                0xb0008
#define REG_SD1_STOP_ADDR                                  (HW_MG20IOP_REG + REG_SD1_STOP_OFFSET)
#define reg_SD_SD1_STOP                                    (*( REGType16v *) REG_SD1_STOP_ADDR)

/* SD1_SECCNT */

#define REG_SD1_SECCNT_OFFSET                              0xb000a
#define REG_SD1_SECCNT_ADDR                                (HW_MG20IOP_REG + REG_SD1_SECCNT_OFFSET)
#define reg_SD_SD1_SECCNT                                  (*( REGType16v *) REG_SD1_SECCNT_ADDR)

/* SD1_RSP0 */

#define REG_SD1_RSP0_OFFSET                                0xb000c
#define REG_SD1_RSP0_ADDR                                  (HW_MG20IOP_REG + REG_SD1_RSP0_OFFSET)
#define reg_SD_SD1_RSP0                                    (*(const REGType16v *) REG_SD1_RSP0_ADDR)

/* SD1_RSP1 */

#define REG_SD1_RSP1_OFFSET                                0xb000e
#define REG_SD1_RSP1_ADDR                                  (HW_MG20IOP_REG + REG_SD1_RSP1_OFFSET)
#define reg_SD_SD1_RSP1                                    (*(const REGType16v *) REG_SD1_RSP1_ADDR)

/* SD1_RSP2 */

#define REG_SD1_RSP2_OFFSET                                0xb0010
#define REG_SD1_RSP2_ADDR                                  (HW_MG20IOP_REG + REG_SD1_RSP2_OFFSET)
#define reg_SD_SD1_RSP2                                    (*(const REGType16v *) REG_SD1_RSP2_ADDR)

/* SD1_RSP3 */

#define REG_SD1_RSP3_OFFSET                                0xb0012
#define REG_SD1_RSP3_ADDR                                  (HW_MG20IOP_REG + REG_SD1_RSP3_OFFSET)
#define reg_SD_SD1_RSP3                                    (*(const REGType16v *) REG_SD1_RSP3_ADDR)

/* SD1_RSP4 */

#define REG_SD1_RSP4_OFFSET                                0xb0014
#define REG_SD1_RSP4_ADDR                                  (HW_MG20IOP_REG + REG_SD1_RSP4_OFFSET)
#define reg_SD_SD1_RSP4                                    (*(const REGType16v *) REG_SD1_RSP4_ADDR)

/* SD1_RSP5 */

#define REG_SD1_RSP5_OFFSET                                0xb0016
#define REG_SD1_RSP5_ADDR                                  (HW_MG20IOP_REG + REG_SD1_RSP5_OFFSET)
#define reg_SD_SD1_RSP5                                    (*(const REGType16v *) REG_SD1_RSP5_ADDR)

/* SD1_RSP6 */

#define REG_SD1_RSP6_OFFSET                                0xb0018
#define REG_SD1_RSP6_ADDR                                  (HW_MG20IOP_REG + REG_SD1_RSP6_OFFSET)
#define reg_SD_SD1_RSP6                                    (*(const REGType16v *) REG_SD1_RSP6_ADDR)

/* SD1_RSP7 */

#define REG_SD1_RSP7_OFFSET                                0xb001a
#define REG_SD1_RSP7_ADDR                                  (HW_MG20IOP_REG + REG_SD1_RSP7_OFFSET)
#define reg_SD_SD1_RSP7                                    (*(const REGType16v *) REG_SD1_RSP7_ADDR)

/* SD1_INFO1 */

#define REG_SD1_INFO1_OFFSET                               0xb001c
#define REG_SD1_INFO1_ADDR                                 (HW_MG20IOP_REG + REG_SD1_INFO1_OFFSET)
#define reg_SD_SD1_INFO1                                   (*( REGType16v *) REG_SD1_INFO1_ADDR)

/* SD1_INFO2 */

#define REG_SD1_INFO2_OFFSET                               0xb001e
#define REG_SD1_INFO2_ADDR                                 (HW_MG20IOP_REG + REG_SD1_INFO2_OFFSET)
#define reg_SD_SD1_INFO2                                   (*( REGType16v *) REG_SD1_INFO2_ADDR)

/* SD1_INFO1_MASK */

#define REG_SD1_INFO1_MASK_OFFSET                          0xb0020
#define REG_SD1_INFO1_MASK_ADDR                            (HW_MG20IOP_REG + REG_SD1_INFO1_MASK_OFFSET)
#define reg_SD_SD1_INFO1_MASK                              (*( REGType16v *) REG_SD1_INFO1_MASK_ADDR)

/* SD1_INFO2_MASK */

#define REG_SD1_INFO2_MASK_OFFSET                          0xb0022
#define REG_SD1_INFO2_MASK_ADDR                            (HW_MG20IOP_REG + REG_SD1_INFO2_MASK_OFFSET)
#define reg_SD_SD1_INFO2_MASK                              (*( REGType16v *) REG_SD1_INFO2_MASK_ADDR)

/* SD1_CLK_CTRL */

#define REG_SD1_CLK_CTRL_OFFSET                            0xb0024
#define REG_SD1_CLK_CTRL_ADDR                              (HW_MG20IOP_REG + REG_SD1_CLK_CTRL_OFFSET)
#define reg_SD_SD1_CLK_CTRL                                (*( REGType16v *) REG_SD1_CLK_CTRL_ADDR)

/* SD1_SIZE */

#define REG_SD1_SIZE_OFFSET                                0xb0026
#define REG_SD1_SIZE_ADDR                                  (HW_MG20IOP_REG + REG_SD1_SIZE_OFFSET)
#define reg_SD_SD1_SIZE                                    (*( REGType16v *) REG_SD1_SIZE_ADDR)

/* SD1_OPTION */

#define REG_SD1_OPTION_OFFSET                              0xb0028
#define REG_SD1_OPTION_ADDR                                (HW_MG20IOP_REG + REG_SD1_OPTION_OFFSET)
#define reg_SD_SD1_OPTION                                  (*( REGType16v *) REG_SD1_OPTION_ADDR)

/* SD1_ERR_STS1 */

#define REG_SD1_ERR_STS1_OFFSET                            0xb002a
#define REG_SD1_ERR_STS1_ADDR                              (HW_MG20IOP_REG + REG_SD1_ERR_STS1_OFFSET)
#define reg_SD_SD1_ERR_STS1                                (*(const REGType16v *) REG_SD1_ERR_STS1_ADDR)

/* SD1_ERR_STS2 */

#define REG_SD1_ERR_STS2_OFFSET                            0xb002c
#define REG_SD1_ERR_STS2_ADDR                              (HW_MG20IOP_REG + REG_SD1_ERR_STS2_OFFSET)
#define reg_SD_SD1_ERR_STS2                                (*(const REGType16v *) REG_SD1_ERR_STS2_ADDR)

/* SD1_BUF0 */

#define REG_SD1_BUF0_OFFSET                                0xb002e
#define REG_SD1_BUF0_ADDR                                  (HW_MG20IOP_REG + REG_SD1_BUF0_OFFSET)
#define reg_SD_SD1_BUF0                                    (*( REGType16v *) REG_SD1_BUF0_ADDR)

/* SDIO1_MODE */

#define REG_SDIO1_MODE_OFFSET                              0xb0030
#define REG_SDIO1_MODE_ADDR                                (HW_MG20IOP_REG + REG_SDIO1_MODE_OFFSET)
#define reg_SD_SDIO1_MODE                                  (*( REGType16v *) REG_SDIO1_MODE_ADDR)

/* SDIO1_INFO1 */

#define REG_SDIO1_INFO1_OFFSET                             0xb0034
#define REG_SDIO1_INFO1_ADDR                               (HW_MG20IOP_REG + REG_SDIO1_INFO1_OFFSET)
#define reg_SD_SDIO1_INFO1                                 (*( REGType16v *) REG_SDIO1_INFO1_ADDR)

/* SDIO1_INF1_MASK */

#define REG_SDIO1_INF1_MASK_OFFSET                         0xb0038
#define REG_SDIO1_INF1_MASK_ADDR                           (HW_MG20IOP_REG + REG_SDIO1_INF1_MASK_OFFSET)
#define reg_SD_SDIO1_INF1_MASK                             (*( REGType16v *) REG_SDIO1_INF1_MASK_ADDR)

/* SD1_CC_EXT_MODE */

#define REG_SD1_CC_EXT_MODE_OFFSET                         0xb00d8
#define REG_SD1_CC_EXT_MODE_ADDR                           (HW_MG20IOP_REG + REG_SD1_CC_EXT_MODE_OFFSET)
#define reg_SD_SD1_CC_EXT_MODE                             (*( REGType16v *) REG_SD1_CC_EXT_MODE_ADDR)

/* SD1_SOFT_RST */

#define REG_SD1_SOFT_RST_OFFSET                            0xb00e0
#define REG_SD1_SOFT_RST_ADDR                              (HW_MG20IOP_REG + REG_SD1_SOFT_RST_OFFSET)
#define reg_SD_SD1_SOFT_RST                                (*( REGType16v *) REG_SD1_SOFT_RST_ADDR)

/* SD1_VERSION */

#define REG_SD1_VERSION_OFFSET                             0xb00e2
#define REG_SD1_VERSION_ADDR                               (HW_MG20IOP_REG + REG_SD1_VERSION_OFFSET)
#define reg_SD_SD1_VERSION                                 (*(const REGType16v *) REG_SD1_VERSION_ADDR)

/* SD1_PWR */

#define REG_SD1_PWR_OFFSET                                 0xb00f2
#define REG_SD1_PWR_ADDR                                   (HW_MG20IOP_REG + REG_SD1_PWR_OFFSET)
#define reg_SD_SD1_PWR                                     (*( REGType16v *) REG_SD1_PWR_ADDR)

/* SD1_EXT_SDIO */

#define REG_SD1_EXT_SDIO_OFFSET                            0xb00f4
#define REG_SD1_EXT_SDIO_ADDR                              (HW_MG20IOP_REG + REG_SD1_EXT_SDIO_OFFSET)
#define reg_SD_SD1_EXT_SDIO                                (*( REGType16v *) REG_SD1_EXT_SDIO_ADDR)

/* SD1_EXT_WP */

#define REG_SD1_EXT_WP_OFFSET                              0xb00f6
#define REG_SD1_EXT_WP_ADDR                                (HW_MG20IOP_REG + REG_SD1_EXT_WP_OFFSET)
#define reg_SD_SD1_EXT_WP                                  (*(const REGType16v *) REG_SD1_EXT_WP_ADDR)

/* SD1_EXT_CD */

#define REG_SD1_EXT_CD_OFFSET                              0xb00f8
#define REG_SD1_EXT_CD_ADDR                                (HW_MG20IOP_REG + REG_SD1_EXT_CD_OFFSET)
#define reg_SD_SD1_EXT_CD                                  (*( REGType16v *) REG_SD1_EXT_CD_ADDR)

/* SD1_EXT_CD_DAT3 */

#define REG_SD1_EXT_CD_DAT3_OFFSET                         0xb00fa
#define REG_SD1_EXT_CD_DAT3_ADDR                           (HW_MG20IOP_REG + REG_SD1_EXT_CD_DAT3_OFFSET)
#define reg_SD_SD1_EXT_CD_DAT3                             (*( REGType16v *) REG_SD1_EXT_CD_DAT3_ADDR)

/* SD1_EXT_CD_MASK */

#define REG_SD1_EXT_CD_MASK_OFFSET                         0xb00fc
#define REG_SD1_EXT_CD_MASK_ADDR                           (HW_MG20IOP_REG + REG_SD1_EXT_CD_MASK_OFFSET)
#define reg_SD_SD1_EXT_CD_MASK                             (*( REGType16v *) REG_SD1_EXT_CD_MASK_ADDR)

/* SD1_EXT_CD_DAT3_MASK */

#define REG_SD1_EXT_CD_DAT3_MASK_OFFSET                    0xb00fe
#define REG_SD1_EXT_CD_DAT3_MASK_ADDR                      (HW_MG20IOP_REG + REG_SD1_EXT_CD_DAT3_MASK_OFFSET)
#define reg_SD_SD1_EXT_CD_DAT3_MASK                        (*( REGType16v *) REG_SD1_EXT_CD_DAT3_MASK_ADDR)

/* SD1_CNT */

#define REG_SD1_CNT_OFFSET                                 0xb0100
#define REG_SD1_CNT_ADDR                                   (HW_MG20IOP_REG + REG_SD1_CNT_OFFSET)
#define reg_SD_SD1_CNT                                     (*( REGType16v *) REG_SD1_CNT_ADDR)

/* SD1_FDS */

#define REG_SD1_FDS_OFFSET                                 0xb0104
#define REG_SD1_FDS_ADDR                                   (HW_MG20IOP_REG + REG_SD1_FDS_OFFSET)
#define reg_SD_SD1_FDS                                     (*( REGType16v *) REG_SD1_FDS_ADDR)

/* SD1_FSC */

#define REG_SD1_FSC_OFFSET                                 0xb0108
#define REG_SD1_FSC_ADDR                                   (HW_MG20IOP_REG + REG_SD1_FSC_OFFSET)
#define reg_SD_SD1_FSC                                     (*( REGType16v *) REG_SD1_FSC_ADDR)

/* SD1_FI */

#define REG_SD1_FI_OFFSET                                  0xb010c
#define REG_SD1_FI_ADDR                                    (HW_MG20IOP_REG + REG_SD1_FI_OFFSET)
#define reg_SD_SD1_FI                                      (*( REGType32v *) REG_SD1_FI_ADDR)


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

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_SD_H_ */
#endif
