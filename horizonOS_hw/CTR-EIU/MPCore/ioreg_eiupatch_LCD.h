/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-EIU/MPCore/ioreg_eiupatch_LCD.h

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
#ifndef NN_HW_CTR_EIU_MPCORE_IOREG_EIUPATCH_LCD_H_
#define NN_HW_CTR_EIU_MPCORE_IOREG_EIUPATCH_LCD_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* LCDC_CNT0 */

#define REG_LCDC_CNT0_OFFSET                               0x202000
#define REG_LCDC_CNT0_ADDR                                 (HW_REG_BASE + REG_LCDC_CNT0_OFFSET)
#define reg_LCD_LCDC_CNT0                                  (*( REGType32v *) REG_LCDC_CNT0_ADDR)

/* LCDC_CNT1 */

#define REG_LCDC_CNT1_OFFSET                               0x202004
#define REG_LCDC_CNT1_ADDR                                 (HW_REG_BASE + REG_LCDC_CNT1_OFFSET)
#define reg_LCD_LCDC_CNT1                                  (*( REGType32v *) REG_LCDC_CNT1_ADDR)

/* LCDC_CNT2 */

#define REG_LCDC_CNT2_OFFSET                               0x202008
#define REG_LCDC_CNT2_ADDR                                 (HW_REG_BASE + REG_LCDC_CNT2_OFFSET)
#define reg_LCD_LCDC_CNT2                                  (*(const REGType32v *) REG_LCDC_CNT2_ADDR)

/* LCDC_CNT2_EIU */

#define REG_LCDC_CNT2_EIU_OFFSET                           0x202008
#define REG_LCDC_CNT2_EIU_ADDR                             (HW_REG_BASE + REG_LCDC_CNT2_EIU_OFFSET)
#define reg_LCD_LCDC_CNT2_EIU                              (*(const REGType32v *) REG_LCDC_CNT2_EIU_ADDR)

/* LCDC_CNT3 */

#define REG_LCDC_CNT3_OFFSET                               0x20200c
#define REG_LCDC_CNT3_ADDR                                 (HW_REG_BASE + REG_LCDC_CNT3_OFFSET)
#define reg_LCD_LCDC_CNT3                                  (*( REGType32v *) REG_LCDC_CNT3_ADDR)

/* LCDC_CNT4 */

#define REG_LCDC_CNT4_OFFSET                               0x202010
#define REG_LCDC_CNT4_ADDR                                 (HW_REG_BASE + REG_LCDC_CNT4_OFFSET)
#define reg_LCD_LCDC_CNT4                                  (*( REGType32v *) REG_LCDC_CNT4_ADDR)

/* LCDC_CNT5 */

#define REG_LCDC_CNT5_OFFSET                               0x202014
#define REG_LCDC_CNT5_ADDR                                 (HW_REG_BASE + REG_LCDC_CNT5_OFFSET)
#define reg_LCD_LCDC_CNT5                                  (*( REGType32v *) REG_LCDC_CNT5_ADDR)

/* LCDC_CNT6 */

#define REG_LCDC_CNT6_OFFSET                               0x202018
#define REG_LCDC_CNT6_ADDR                                 (HW_REG_BASE + REG_LCDC_CNT6_OFFSET)
#define reg_LCD_LCDC_CNT6                                  (*( REGType32v *) REG_LCDC_CNT6_ADDR)

/* ABL0_CNT */

#define REG_ABL0_CNT_OFFSET                                0x202200
#define REG_ABL0_CNT_ADDR                                  (HW_REG_BASE + REG_ABL0_CNT_OFFSET)
#define reg_LCD_ABL0_CNT                                   (*( REGType32v *) REG_ABL0_CNT_ADDR)

/* ABL0_FCOLOR */

#define REG_ABL0_FCOLOR_OFFSET                             0x202204
#define REG_ABL0_FCOLOR_ADDR                               (HW_REG_BASE + REG_ABL0_FCOLOR_OFFSET)
#define reg_LCD_ABL0_FCOLOR                                (*( REGType32v *) REG_ABL0_FCOLOR_ADDR)

/* ABL0_HST_SX */

#define REG_ABL0_HST_SX_OFFSET                             0x202210
#define REG_ABL0_HST_SX_ADDR                               (HW_REG_BASE + REG_ABL0_HST_SX_OFFSET)
#define reg_LCD_ABL0_HST_SX                                (*( REGType32v *) REG_ABL0_HST_SX_ADDR)

/* ABL0_HST_EX */

#define REG_ABL0_HST_EX_OFFSET                             0x202214
#define REG_ABL0_HST_EX_ADDR                               (HW_REG_BASE + REG_ABL0_HST_EX_OFFSET)
#define reg_LCD_ABL0_HST_EX                                (*( REGType32v *) REG_ABL0_HST_EX_ADDR)

/* ABL0_HST_SY */

#define REG_ABL0_HST_SY_OFFSET                             0x202218
#define REG_ABL0_HST_SY_ADDR                               (HW_REG_BASE + REG_ABL0_HST_SY_OFFSET)
#define reg_LCD_ABL0_HST_SY                                (*( REGType32v *) REG_ABL0_HST_SY_ADDR)

/* ABL0_HST_EY */

#define REG_ABL0_HST_EY_OFFSET                             0x20221c
#define REG_ABL0_HST_EY_ADDR                               (HW_REG_BASE + REG_ABL0_HST_EY_OFFSET)
#define reg_LCD_ABL0_HST_EY                                (*( REGType32v *) REG_ABL0_HST_EY_ADDR)

/* ABL0_GTHP */

#define REG_ABL0_GTHP_OFFSET                               0x202220
#define REG_ABL0_GTHP_ADDR                                 (HW_REG_BASE + REG_ABL0_GTHP_OFFSET)
#define reg_LCD_ABL0_GTHP                                  (*( REGType32v *) REG_ABL0_GTHP_ADDR)

/* ABL0_GTHMIN */

#define REG_ABL0_GTHMIN_OFFSET                             0x202224
#define REG_ABL0_GTHMIN_ADDR                               (HW_REG_BASE + REG_ABL0_GTHMIN_OFFSET)
#define reg_LCD_ABL0_GTHMIN                                (*( REGType32v *) REG_ABL0_GTHMIN_ADDR)

/* ABL0_GTHMAX */

#define REG_ABL0_GTHMAX_OFFSET                             0x202228
#define REG_ABL0_GTHMAX_ADDR                               (HW_REG_BASE + REG_ABL0_GTHMAX_OFFSET)
#define reg_LCD_ABL0_GTHMAX                                (*( REGType32v *) REG_ABL0_GTHMAX_ADDR)

/* ABL0_GTHMAXEX */

#define REG_ABL0_GTHMAXEX_OFFSET                           0x20222c
#define REG_ABL0_GTHMAXEX_ADDR                             (HW_REG_BASE + REG_ABL0_GTHMAXEX_OFFSET)
#define reg_LCD_ABL0_GTHMAXEX                              (*( REGType32v *) REG_ABL0_GTHMAXEX_ADDR)

/* ABL0_INERTIA */

#define REG_ABL0_INERTIA_OFFSET                            0x202230
#define REG_ABL0_INERTIA_ADDR                              (HW_REG_BASE + REG_ABL0_INERTIA_OFFSET)
#define reg_LCD_ABL0_INERTIA                               (*( REGType32v *) REG_ABL0_INERTIA_ADDR)

/* ABL0_INERTIA_EIU */

#define REG_ABL0_INERTIA_EIU_OFFSET                        0x202230
#define REG_ABL0_INERTIA_EIU_ADDR                          (HW_REG_BASE + REG_ABL0_INERTIA_EIU_OFFSET)
#define reg_LCD_ABL0_INERTIA_EIU                           (*( REGType32v *) REG_ABL0_INERTIA_EIU_ADDR)

/* ABL0_RSMIN */

#define REG_ABL0_RSMIN_OFFSET                              0x202238
#define REG_ABL0_RSMIN_ADDR                                (HW_REG_BASE + REG_ABL0_RSMIN_OFFSET)
#define reg_LCD_ABL0_RSMIN                                 (*( REGType32v *) REG_ABL0_RSMIN_ADDR)

/* ABL0_RSMAX */

#define REG_ABL0_RSMAX_OFFSET                              0x20223c
#define REG_ABL0_RSMAX_ADDR                                (HW_REG_BASE + REG_ABL0_RSMAX_OFFSET)
#define reg_LCD_ABL0_RSMAX                                 (*( REGType32v *) REG_ABL0_RSMAX_ADDR)

/* ABL0_LMAX */

#define REG_ABL0_LMAX_OFFSET                               0x202240
#define REG_ABL0_LMAX_ADDR                                 (HW_REG_BASE + REG_ABL0_LMAX_OFFSET)
#define reg_LCD_ABL0_LMAX                                  (*( REGType32v *) REG_ABL0_LMAX_ADDR)

/* ABL0_PWMCNT */

#define REG_ABL0_PWMCNT_OFFSET                             0x202244
#define REG_ABL0_PWMCNT_ADDR                               (HW_REG_BASE + REG_ABL0_PWMCNT_OFFSET)
#define reg_LCD_ABL0_PWMCNT                                (*( REGType32v *) REG_ABL0_PWMCNT_ADDR)

/* ABL0_PWMCNT_EIU */

#define REG_ABL0_PWMCNT_EIU_OFFSET                         0x202244
#define REG_ABL0_PWMCNT_EIU_ADDR                           (HW_REG_BASE + REG_ABL0_PWMCNT_EIU_OFFSET)
#define reg_LCD_ABL0_PWMCNT_EIU                            (*( REGType32v *) REG_ABL0_PWMCNT_EIU_ADDR)

/* ABL0_HST1 */

#define REG_ABL0_HST1_OFFSET                               0x202250
#define REG_ABL0_HST1_ADDR                                 (HW_REG_BASE + REG_ABL0_HST1_OFFSET)
#define reg_LCD_ABL0_HST1                                  (*( REGType32v *) REG_ABL0_HST1_ADDR)

/* ABL0_HST2 */

#define REG_ABL0_HST2_OFFSET                               0x202254
#define REG_ABL0_HST2_ADDR                                 (HW_REG_BASE + REG_ABL0_HST2_OFFSET)
#define reg_LCD_ABL0_HST2                                  (*( REGType32v *) REG_ABL0_HST2_ADDR)

/* ABL0_DITPAT0 */

#define REG_ABL0_DITPAT0_OFFSET                            0x202260
#define REG_ABL0_DITPAT0_ADDR                              (HW_REG_BASE + REG_ABL0_DITPAT0_OFFSET)
#define reg_LCD_ABL0_DITPAT0                               (*( REGType32v *) REG_ABL0_DITPAT0_ADDR)

/* ABL0_RSLUT0 */

#define REG_ABL0_RSLUT0_OFFSET                             0x202280
#define REG_ABL0_RSLUT0_ADDR                               (HW_REG_BASE + REG_ABL0_RSLUT0_OFFSET)
#define reg_LCD_ABL0_RSLUT0                                (*( REGType32v *) REG_ABL0_RSLUT0_ADDR)

/* ABL0_CMAX */

#define REG_ABL0_CMAX_OFFSET                               0x2022f0
#define REG_ABL0_CMAX_ADDR                                 (HW_REG_BASE + REG_ABL0_CMAX_OFFSET)
#define reg_LCD_ABL0_CMAX                                  (*(const REGType32v *) REG_ABL0_CMAX_ADDR)

/* ABL0_CGTH */

#define REG_ABL0_CGTH_OFFSET                               0x2022f4
#define REG_ABL0_CGTH_ADDR                                 (HW_REG_BASE + REG_ABL0_CGTH_OFFSET)
#define reg_LCD_ABL0_CGTH                                  (*(const REGType32v *) REG_ABL0_CGTH_ADDR)

/* ABL0_CRS */

#define REG_ABL0_CRS_OFFSET                                0x2022f8
#define REG_ABL0_CRS_ADDR                                  (HW_REG_BASE + REG_ABL0_CRS_OFFSET)
#define reg_LCD_ABL0_CRS                                   (*(const REGType32v *) REG_ABL0_CRS_ADDR)

/* ABL0_ADJCOE0 */

#define REG_ABL0_ADJCOE0_OFFSET                            0x202300
#define REG_ABL0_ADJCOE0_ADDR                              (HW_REG_BASE + REG_ABL0_ADJCOE0_OFFSET)
#define reg_LCD_ABL0_ADJCOE0                               (*( REGType32v *) REG_ABL0_ADJCOE0_ADDR)

/* ABL0_RDLUT0 */

#define REG_ABL0_RDLUT0_OFFSET                             0x202400
#define REG_ABL0_RDLUT0_ADDR                               (HW_REG_BASE + REG_ABL0_RDLUT0_OFFSET)
#define reg_LCD_ABL0_RDLUT0                                (*(const REGType32v *) REG_ABL0_RDLUT0_ADDR)

/* ABL1_CNT */

#define REG_ABL1_CNT_OFFSET                                0x202a00
#define REG_ABL1_CNT_ADDR                                  (HW_REG_BASE + REG_ABL1_CNT_OFFSET)
#define reg_LCD_ABL1_CNT                                   (*( REGType32v *) REG_ABL1_CNT_ADDR)

/* ABL1_FCOLOR */

#define REG_ABL1_FCOLOR_OFFSET                             0x202a04
#define REG_ABL1_FCOLOR_ADDR                               (HW_REG_BASE + REG_ABL1_FCOLOR_OFFSET)
#define reg_LCD_ABL1_FCOLOR                                (*( REGType32v *) REG_ABL1_FCOLOR_ADDR)

/* ABL1_HST_SX */

#define REG_ABL1_HST_SX_OFFSET                             0x202a10
#define REG_ABL1_HST_SX_ADDR                               (HW_REG_BASE + REG_ABL1_HST_SX_OFFSET)
#define reg_LCD_ABL1_HST_SX                                (*( REGType32v *) REG_ABL1_HST_SX_ADDR)

/* ABL1_HST_EX */

#define REG_ABL1_HST_EX_OFFSET                             0x202a14
#define REG_ABL1_HST_EX_ADDR                               (HW_REG_BASE + REG_ABL1_HST_EX_OFFSET)
#define reg_LCD_ABL1_HST_EX                                (*( REGType32v *) REG_ABL1_HST_EX_ADDR)

/* ABL1_HST_SY */

#define REG_ABL1_HST_SY_OFFSET                             0x202a18
#define REG_ABL1_HST_SY_ADDR                               (HW_REG_BASE + REG_ABL1_HST_SY_OFFSET)
#define reg_LCD_ABL1_HST_SY                                (*( REGType32v *) REG_ABL1_HST_SY_ADDR)

/* ABL1_HST_EY */

#define REG_ABL1_HST_EY_OFFSET                             0x202a1c
#define REG_ABL1_HST_EY_ADDR                               (HW_REG_BASE + REG_ABL1_HST_EY_OFFSET)
#define reg_LCD_ABL1_HST_EY                                (*( REGType32v *) REG_ABL1_HST_EY_ADDR)

/* ABL1_GTHP */

#define REG_ABL1_GTHP_OFFSET                               0x202a20
#define REG_ABL1_GTHP_ADDR                                 (HW_REG_BASE + REG_ABL1_GTHP_OFFSET)
#define reg_LCD_ABL1_GTHP                                  (*( REGType32v *) REG_ABL1_GTHP_ADDR)

/* ABL1_GTHMIN */

#define REG_ABL1_GTHMIN_OFFSET                             0x202a24
#define REG_ABL1_GTHMIN_ADDR                               (HW_REG_BASE + REG_ABL1_GTHMIN_OFFSET)
#define reg_LCD_ABL1_GTHMIN                                (*( REGType32v *) REG_ABL1_GTHMIN_ADDR)

/* ABL1_GTHMAX */

#define REG_ABL1_GTHMAX_OFFSET                             0x202a28
#define REG_ABL1_GTHMAX_ADDR                               (HW_REG_BASE + REG_ABL1_GTHMAX_OFFSET)
#define reg_LCD_ABL1_GTHMAX                                (*( REGType32v *) REG_ABL1_GTHMAX_ADDR)

/* ABL1_GTHMAXEX */

#define REG_ABL1_GTHMAXEX_OFFSET                           0x202a2c
#define REG_ABL1_GTHMAXEX_ADDR                             (HW_REG_BASE + REG_ABL1_GTHMAXEX_OFFSET)
#define reg_LCD_ABL1_GTHMAXEX                              (*( REGType32v *) REG_ABL1_GTHMAXEX_ADDR)

/* ABL1_INERTIA */

#define REG_ABL1_INERTIA_OFFSET                            0x202a30
#define REG_ABL1_INERTIA_ADDR                              (HW_REG_BASE + REG_ABL1_INERTIA_OFFSET)
#define reg_LCD_ABL1_INERTIA                               (*( REGType32v *) REG_ABL1_INERTIA_ADDR)

/* ABL1_INERTIA_EIU */

#define REG_ABL1_INERTIA_EIU_OFFSET                        0x202a30
#define REG_ABL1_INERTIA_EIU_ADDR                          (HW_REG_BASE + REG_ABL1_INERTIA_EIU_OFFSET)
#define reg_LCD_ABL1_INERTIA_EIU                           (*( REGType32v *) REG_ABL1_INERTIA_EIU_ADDR)

/* ABL1_RSMIN */

#define REG_ABL1_RSMIN_OFFSET                              0x202a38
#define REG_ABL1_RSMIN_ADDR                                (HW_REG_BASE + REG_ABL1_RSMIN_OFFSET)
#define reg_LCD_ABL1_RSMIN                                 (*( REGType32v *) REG_ABL1_RSMIN_ADDR)

/* ABL1_RSMAX */

#define REG_ABL1_RSMAX_OFFSET                              0x202a3c
#define REG_ABL1_RSMAX_ADDR                                (HW_REG_BASE + REG_ABL1_RSMAX_OFFSET)
#define reg_LCD_ABL1_RSMAX                                 (*( REGType32v *) REG_ABL1_RSMAX_ADDR)

/* ABL1_LMAX */

#define REG_ABL1_LMAX_OFFSET                               0x202a40
#define REG_ABL1_LMAX_ADDR                                 (HW_REG_BASE + REG_ABL1_LMAX_OFFSET)
#define reg_LCD_ABL1_LMAX                                  (*( REGType32v *) REG_ABL1_LMAX_ADDR)

/* ABL1_PWMCNT */

#define REG_ABL1_PWMCNT_OFFSET                             0x202a44
#define REG_ABL1_PWMCNT_ADDR                               (HW_REG_BASE + REG_ABL1_PWMCNT_OFFSET)
#define reg_LCD_ABL1_PWMCNT                                (*( REGType32v *) REG_ABL1_PWMCNT_ADDR)

/* ABL1_PWMCNT_EIU */

#define REG_ABL1_PWMCNT_EIU_OFFSET                         0x202a44
#define REG_ABL1_PWMCNT_EIU_ADDR                           (HW_REG_BASE + REG_ABL1_PWMCNT_EIU_OFFSET)
#define reg_LCD_ABL1_PWMCNT_EIU                            (*( REGType32v *) REG_ABL1_PWMCNT_EIU_ADDR)

/* ABL1_HST1 */

#define REG_ABL1_HST1_OFFSET                               0x202a50
#define REG_ABL1_HST1_ADDR                                 (HW_REG_BASE + REG_ABL1_HST1_OFFSET)
#define reg_LCD_ABL1_HST1                                  (*( REGType32v *) REG_ABL1_HST1_ADDR)

/* ABL1_HST2 */

#define REG_ABL1_HST2_OFFSET                               0x202a54
#define REG_ABL1_HST2_ADDR                                 (HW_REG_BASE + REG_ABL1_HST2_OFFSET)
#define reg_LCD_ABL1_HST2                                  (*( REGType32v *) REG_ABL1_HST2_ADDR)

/* ABL1_DITPAT0 */

#define REG_ABL1_DITPAT0_OFFSET                            0x202a60
#define REG_ABL1_DITPAT0_ADDR                              (HW_REG_BASE + REG_ABL1_DITPAT0_OFFSET)
#define reg_LCD_ABL1_DITPAT0                               (*( REGType32v *) REG_ABL1_DITPAT0_ADDR)

/* ABL1_DITPAT1 */

#define REG_ABL1_DITPAT1_OFFSET                            0x202a68
#define REG_ABL1_DITPAT1_ADDR                              (HW_REG_BASE + REG_ABL1_DITPAT1_OFFSET)
#define reg_LCD_ABL1_DITPAT1                               (*( REGType32v *) REG_ABL1_DITPAT1_ADDR)

/* ABL1_RSLUT0 */

#define REG_ABL1_RSLUT0_OFFSET                             0x202a80
#define REG_ABL1_RSLUT0_ADDR                               (HW_REG_BASE + REG_ABL1_RSLUT0_OFFSET)
#define reg_LCD_ABL1_RSLUT0                                (*( REGType32v *) REG_ABL1_RSLUT0_ADDR)

/* ABL1_CMAX */

#define REG_ABL1_CMAX_OFFSET                               0x202af0
#define REG_ABL1_CMAX_ADDR                                 (HW_REG_BASE + REG_ABL1_CMAX_OFFSET)
#define reg_LCD_ABL1_CMAX                                  (*(const REGType32v *) REG_ABL1_CMAX_ADDR)

/* ABL1_CGTH */

#define REG_ABL1_CGTH_OFFSET                               0x202af4
#define REG_ABL1_CGTH_ADDR                                 (HW_REG_BASE + REG_ABL1_CGTH_OFFSET)
#define reg_LCD_ABL1_CGTH                                  (*(const REGType32v *) REG_ABL1_CGTH_ADDR)

/* ABL1_CRS */

#define REG_ABL1_CRS_OFFSET                                0x202af8
#define REG_ABL1_CRS_ADDR                                  (HW_REG_BASE + REG_ABL1_CRS_OFFSET)
#define reg_LCD_ABL1_CRS                                   (*(const REGType32v *) REG_ABL1_CRS_ADDR)

/* ABL1_ADJCOE0 */

#define REG_ABL1_ADJCOE0_OFFSET                            0x202b00
#define REG_ABL1_ADJCOE0_ADDR                              (HW_REG_BASE + REG_ABL1_ADJCOE0_OFFSET)
#define reg_LCD_ABL1_ADJCOE0                               (*( REGType32v *) REG_ABL1_ADJCOE0_ADDR)

/* ABL1_RDLUT0 */

#define REG_ABL1_RDLUT0_OFFSET                             0x202c00
#define REG_ABL1_RDLUT0_ADDR                               (HW_REG_BASE + REG_ABL1_RDLUT0_OFFSET)
#define reg_LCD_ABL1_RDLUT0                                (*(const REGType32v *) REG_ABL1_RDLUT0_ADDR)

/* PDC0_H_COUNT_SIZE */

#define REG_PDC0_H_COUNT_SIZE_OFFSET                       0x400400
#define REG_PDC0_H_COUNT_SIZE_ADDR                         (HW_REG_BASE + REG_PDC0_H_COUNT_SIZE_OFFSET)
#define reg_LCD_PDC0_H_COUNT_SIZE                          (*( REGType32v *) REG_PDC0_H_COUNT_SIZE_ADDR)

/* PDC0_H_DISP_S */

#define REG_PDC0_H_DISP_S_OFFSET                           0x400404
#define REG_PDC0_H_DISP_S_ADDR                             (HW_REG_BASE + REG_PDC0_H_DISP_S_OFFSET)
#define reg_LCD_PDC0_H_DISP_S                              (*( REGType32v *) REG_PDC0_H_DISP_S_ADDR)

/* PDC0_H_RBORDER_S */

#define REG_PDC0_H_RBORDER_S_OFFSET                        0x400408
#define REG_PDC0_H_RBORDER_S_ADDR                          (HW_REG_BASE + REG_PDC0_H_RBORDER_S_OFFSET)
#define reg_LCD_PDC0_H_RBORDER_S                           (*( REGType32v *) REG_PDC0_H_RBORDER_S_ADDR)

/* PDC0_H_BLANK_S */

#define REG_PDC0_H_BLANK_S_OFFSET                          0x40040c
#define REG_PDC0_H_BLANK_S_ADDR                            (HW_REG_BASE + REG_PDC0_H_BLANK_S_OFFSET)
#define reg_LCD_PDC0_H_BLANK_S                             (*( REGType32v *) REG_PDC0_H_BLANK_S_ADDR)

/* PDC0_H_SYNC_S */

#define REG_PDC0_H_SYNC_S_OFFSET                           0x400410
#define REG_PDC0_H_SYNC_S_ADDR                             (HW_REG_BASE + REG_PDC0_H_SYNC_S_OFFSET)
#define reg_LCD_PDC0_H_SYNC_S                              (*( REGType32v *) REG_PDC0_H_SYNC_S_ADDR)

/* PDC0_H_BPORTCH_S */

#define REG_PDC0_H_BPORTCH_S_OFFSET                        0x400414
#define REG_PDC0_H_BPORTCH_S_ADDR                          (HW_REG_BASE + REG_PDC0_H_BPORTCH_S_OFFSET)
#define reg_LCD_PDC0_H_BPORTCH_S                           (*( REGType32v *) REG_PDC0_H_BPORTCH_S_ADDR)

/* PDC0_H_LBORDER_S */

#define REG_PDC0_H_LBORDER_S_OFFSET                        0x400418
#define REG_PDC0_H_LBORDER_S_ADDR                          (HW_REG_BASE + REG_PDC0_H_LBORDER_S_OFFSET)
#define reg_LCD_PDC0_H_LBORDER_S                           (*( REGType32v *) REG_PDC0_H_LBORDER_S_ADDR)

/* PDC0_H_INTR_POS */

#define REG_PDC0_H_INTR_POS_OFFSET                         0x40041c
#define REG_PDC0_H_INTR_POS_ADDR                           (HW_REG_BASE + REG_PDC0_H_INTR_POS_OFFSET)
#define reg_LCD_PDC0_H_INTR_POS                            (*( REGType32v *) REG_PDC0_H_INTR_POS_ADDR)

/* PDC0_H_DMA_POS */

#define REG_PDC0_H_DMA_POS_OFFSET                          0x400420
#define REG_PDC0_H_DMA_POS_ADDR                            (HW_REG_BASE + REG_PDC0_H_DMA_POS_OFFSET)
#define reg_LCD_PDC0_H_DMA_POS                             (*( REGType32v *) REG_PDC0_H_DMA_POS_ADDR)

/* PDC0_V_COUNT_SIZE */

#define REG_PDC0_V_COUNT_SIZE_OFFSET                       0x400424
#define REG_PDC0_V_COUNT_SIZE_ADDR                         (HW_REG_BASE + REG_PDC0_V_COUNT_SIZE_OFFSET)
#define reg_LCD_PDC0_V_COUNT_SIZE                          (*( REGType32v *) REG_PDC0_V_COUNT_SIZE_ADDR)

/* PDC0_V_DISP_S */

#define REG_PDC0_V_DISP_S_OFFSET                           0x400428
#define REG_PDC0_V_DISP_S_ADDR                             (HW_REG_BASE + REG_PDC0_V_DISP_S_OFFSET)
#define reg_LCD_PDC0_V_DISP_S                              (*( REGType32v *) REG_PDC0_V_DISP_S_ADDR)

/* PDC0_V_BBORDER_S */

#define REG_PDC0_V_BBORDER_S_OFFSET                        0x40042c
#define REG_PDC0_V_BBORDER_S_ADDR                          (HW_REG_BASE + REG_PDC0_V_BBORDER_S_OFFSET)
#define reg_LCD_PDC0_V_BBORDER_S                           (*( REGType32v *) REG_PDC0_V_BBORDER_S_ADDR)

/* PDC0_V_BLANK_S */

#define REG_PDC0_V_BLANK_S_OFFSET                          0x400430
#define REG_PDC0_V_BLANK_S_ADDR                            (HW_REG_BASE + REG_PDC0_V_BLANK_S_OFFSET)
#define reg_LCD_PDC0_V_BLANK_S                             (*( REGType32v *) REG_PDC0_V_BLANK_S_ADDR)

/* PDC0_V_SYNC_S */

#define REG_PDC0_V_SYNC_S_OFFSET                           0x400434
#define REG_PDC0_V_SYNC_S_ADDR                             (HW_REG_BASE + REG_PDC0_V_SYNC_S_OFFSET)
#define reg_LCD_PDC0_V_SYNC_S                              (*( REGType32v *) REG_PDC0_V_SYNC_S_ADDR)

/* PDC0_V_BPORTCH_S */

#define REG_PDC0_V_BPORTCH_S_OFFSET                        0x400438
#define REG_PDC0_V_BPORTCH_S_ADDR                          (HW_REG_BASE + REG_PDC0_V_BPORTCH_S_OFFSET)
#define reg_LCD_PDC0_V_BPORTCH_S                           (*( REGType32v *) REG_PDC0_V_BPORTCH_S_ADDR)

/* PDC0_V_TBORDER_S */

#define REG_PDC0_V_TBORDER_S_OFFSET                        0x40043c
#define REG_PDC0_V_TBORDER_S_ADDR                          (HW_REG_BASE + REG_PDC0_V_TBORDER_S_OFFSET)
#define reg_LCD_PDC0_V_TBORDER_S                           (*( REGType32v *) REG_PDC0_V_TBORDER_S_ADDR)

/* PDC0_V_INTR_POS */

#define REG_PDC0_V_INTR_POS_OFFSET                         0x400440
#define REG_PDC0_V_INTR_POS_ADDR                           (HW_REG_BASE + REG_PDC0_V_INTR_POS_OFFSET)
#define reg_LCD_PDC0_V_INTR_POS                            (*( REGType32v *) REG_PDC0_V_INTR_POS_ADDR)

/* PDC0_V_INC_H_POS */

#define REG_PDC0_V_INC_H_POS_OFFSET                        0x400444
#define REG_PDC0_V_INC_H_POS_ADDR                          (HW_REG_BASE + REG_PDC0_V_INC_H_POS_OFFSET)
#define reg_LCD_PDC0_V_INC_H_POS                           (*( REGType32v *) REG_PDC0_V_INC_H_POS_ADDR)

/* PDC0_SIGNAL_POL */

#define REG_PDC0_SIGNAL_POL_OFFSET                         0x400448
#define REG_PDC0_SIGNAL_POL_ADDR                           (HW_REG_BASE + REG_PDC0_SIGNAL_POL_OFFSET)
#define reg_LCD_PDC0_SIGNAL_POL                            (*( REGType32v *) REG_PDC0_SIGNAL_POL_ADDR)

/* PDC0_BORDER_COL */

#define REG_PDC0_BORDER_COL_OFFSET                         0x40044c
#define REG_PDC0_BORDER_COL_ADDR                           (HW_REG_BASE + REG_PDC0_BORDER_COL_OFFSET)
#define reg_LCD_PDC0_BORDER_COL                            (*( REGType32v *) REG_PDC0_BORDER_COL_ADDR)

/* PDC0_H_COUNT */

#define REG_PDC0_H_COUNT_OFFSET                            0x400450
#define REG_PDC0_H_COUNT_ADDR                              (HW_REG_BASE + REG_PDC0_H_COUNT_OFFSET)
#define reg_LCD_PDC0_H_COUNT                               (*(const REGType32v *) REG_PDC0_H_COUNT_ADDR)

/* PDC0_V_COUNT */

#define REG_PDC0_V_COUNT_OFFSET                            0x400454
#define REG_PDC0_V_COUNT_ADDR                              (HW_REG_BASE + REG_PDC0_V_COUNT_OFFSET)
#define reg_LCD_PDC0_V_COUNT                               (*(const REGType32v *) REG_PDC0_V_COUNT_ADDR)

/* PDC0_OUT_SIZE */

#define REG_PDC0_OUT_SIZE_OFFSET                           0x40045c
#define REG_PDC0_OUT_SIZE_ADDR                             (HW_REG_BASE + REG_PDC0_OUT_SIZE_OFFSET)
#define reg_LCD_PDC0_OUT_SIZE                              (*( REGType32v *) REG_PDC0_OUT_SIZE_ADDR)

/* PDC0_PIC_BORDER_H */

#define REG_PDC0_PIC_BORDER_H_OFFSET                       0x400460
#define REG_PDC0_PIC_BORDER_H_ADDR                         (HW_REG_BASE + REG_PDC0_PIC_BORDER_H_OFFSET)
#define reg_LCD_PDC0_PIC_BORDER_H                          (*( REGType32v *) REG_PDC0_PIC_BORDER_H_ADDR)

/* PDC0_PIC_BORDER_V */

#define REG_PDC0_PIC_BORDER_V_OFFSET                       0x400464
#define REG_PDC0_PIC_BORDER_V_ADDR                         (HW_REG_BASE + REG_PDC0_PIC_BORDER_V_OFFSET)
#define reg_LCD_PDC0_PIC_BORDER_V                          (*( REGType32v *) REG_PDC0_PIC_BORDER_V_ADDR)

/* PDC0_FB0_ADR */

#define REG_PDC0_FB0_ADR_OFFSET                            0x400468
#define REG_PDC0_FB0_ADR_ADDR                              (HW_REG_BASE + REG_PDC0_FB0_ADR_OFFSET)
#define reg_LCD_PDC0_FB0_ADR                               (*( REGType32v *) REG_PDC0_FB0_ADR_ADDR)

/* PDC0_FB1_ADR */

#define REG_PDC0_FB1_ADR_OFFSET                            0x40046C
#define REG_PDC0_FB1_ADR_ADDR                              (HW_REG_BASE + REG_PDC0_FB1_ADR_OFFSET)
#define reg_LCD_PDC0_FB1_ADR                               (*( REGType32v *) REG_PDC0_FB1_ADR_ADDR)

/* PDC0_MODE */

#define REG_PDC0_MODE_OFFSET                               0x400470
#define REG_PDC0_MODE_ADDR                                 (HW_REG_BASE + REG_PDC0_MODE_OFFSET)
#define reg_LCD_PDC0_MODE                                  (*( REGType32v *) REG_PDC0_MODE_ADDR)

/* PDC0_START */

#define REG_PDC0_START_OFFSET                              0x400474
#define REG_PDC0_START_ADDR                                (HW_REG_BASE + REG_PDC0_START_OFFSET)
#define reg_LCD_PDC0_START                                 (*( REGType32v *) REG_PDC0_START_ADDR)

/* PDC0_SWAP */

#define REG_PDC0_SWAP_OFFSET                               0x400478
#define REG_PDC0_SWAP_ADDR                                 (HW_REG_BASE + REG_PDC0_SWAP_OFFSET)
#define reg_LCD_PDC0_SWAP                                  (*( REGType32v *) REG_PDC0_SWAP_ADDR)

/* PDC0_STAT */

#define REG_PDC0_STAT_OFFSET                               0x40047c
#define REG_PDC0_STAT_ADDR                                 (HW_REG_BASE + REG_PDC0_STAT_OFFSET)
#define reg_LCD_PDC0_STAT                                  (*(const REGType32v *) REG_PDC0_STAT_ADDR)

/* PDC0_GTBL_ADR */

#define REG_PDC0_GTBL_ADR_OFFSET                           0x400480
#define REG_PDC0_GTBL_ADR_ADDR                             (HW_REG_BASE + REG_PDC0_GTBL_ADR_OFFSET)
#define reg_LCD_PDC0_GTBL_ADR                              (*( REGType32v *) REG_PDC0_GTBL_ADR_ADDR)

/* PDC0_GTBL_DATA */

#define REG_PDC0_GTBL_DATA_OFFSET                          0x400484
#define REG_PDC0_GTBL_DATA_ADDR                            (HW_REG_BASE + REG_PDC0_GTBL_DATA_OFFSET)
#define reg_LCD_PDC0_GTBL_DATA                             (*( REGType32v *) REG_PDC0_GTBL_DATA_ADDR)

/* PDC0_FB_SIZE */

#define REG_PDC0_FB_SIZE_OFFSET                            0x400490
#define REG_PDC0_FB_SIZE_ADDR                              (HW_REG_BASE + REG_PDC0_FB_SIZE_OFFSET)
#define reg_LCD_PDC0_FB_SIZE                               (*( REGType32v *) REG_PDC0_FB_SIZE_ADDR)

/* PDC0_FB0_B_ADR */

#define REG_PDC0_FB0_B_ADR_OFFSET                          0x400494
#define REG_PDC0_FB0_B_ADR_ADDR                            (HW_REG_BASE + REG_PDC0_FB0_B_ADR_OFFSET)
#define reg_LCD_PDC0_FB0_B_ADR                             (*( REGType32v *) REG_PDC0_FB0_B_ADR_ADDR)

/* PDC0_FB1_B_ADR */

#define REG_PDC0_FB1_B_ADR_OFFSET                          0x400498
#define REG_PDC0_FB1_B_ADR_ADDR                            (HW_REG_BASE + REG_PDC0_FB1_B_ADR_OFFSET)
#define reg_LCD_PDC0_FB1_B_ADR                             (*( REGType32v *) REG_PDC0_FB1_B_ADR_ADDR)

/* PDC0_UPDATE */

#define REG_PDC0_UPDATE_OFFSET                             0x40049c
#define REG_PDC0_UPDATE_ADDR                               (HW_REG_BASE + REG_PDC0_UPDATE_OFFSET)
#define reg_LCD_PDC0_UPDATE                                (*( REGType32v *) REG_PDC0_UPDATE_ADDR)

/* PDC1_H_COUNT_SIZE */

#define REG_PDC1_H_COUNT_SIZE_OFFSET                       0x400500
#define REG_PDC1_H_COUNT_SIZE_ADDR                         (HW_REG_BASE + REG_PDC1_H_COUNT_SIZE_OFFSET)
#define reg_LCD_PDC1_H_COUNT_SIZE                          (*( REGType32v *) REG_PDC1_H_COUNT_SIZE_ADDR)

/* PDC1_H_DISP_S */

#define REG_PDC1_H_DISP_S_OFFSET                           0x400504
#define REG_PDC1_H_DISP_S_ADDR                             (HW_REG_BASE + REG_PDC1_H_DISP_S_OFFSET)
#define reg_LCD_PDC1_H_DISP_S                              (*( REGType32v *) REG_PDC1_H_DISP_S_ADDR)

/* PDC1_H_RBORDER_S */

#define REG_PDC1_H_RBORDER_S_OFFSET                        0x400508
#define REG_PDC1_H_RBORDER_S_ADDR                          (HW_REG_BASE + REG_PDC1_H_RBORDER_S_OFFSET)
#define reg_LCD_PDC1_H_RBORDER_S                           (*( REGType32v *) REG_PDC1_H_RBORDER_S_ADDR)

/* PDC1_H_BLANK_S */

#define REG_PDC1_H_BLANK_S_OFFSET                          0x40050c
#define REG_PDC1_H_BLANK_S_ADDR                            (HW_REG_BASE + REG_PDC1_H_BLANK_S_OFFSET)
#define reg_LCD_PDC1_H_BLANK_S                             (*( REGType32v *) REG_PDC1_H_BLANK_S_ADDR)

/* PDC1_H_SYNC_S */

#define REG_PDC1_H_SYNC_S_OFFSET                           0x400510
#define REG_PDC1_H_SYNC_S_ADDR                             (HW_REG_BASE + REG_PDC1_H_SYNC_S_OFFSET)
#define reg_LCD_PDC1_H_SYNC_S                              (*( REGType32v *) REG_PDC1_H_SYNC_S_ADDR)

/* PDC1_H_BPORTCH_S */

#define REG_PDC1_H_BPORTCH_S_OFFSET                        0x400514
#define REG_PDC1_H_BPORTCH_S_ADDR                          (HW_REG_BASE + REG_PDC1_H_BPORTCH_S_OFFSET)
#define reg_LCD_PDC1_H_BPORTCH_S                           (*( REGType32v *) REG_PDC1_H_BPORTCH_S_ADDR)

/* PDC1_H_LBORDER_S */

#define REG_PDC1_H_LBORDER_S_OFFSET                        0x400518
#define REG_PDC1_H_LBORDER_S_ADDR                          (HW_REG_BASE + REG_PDC1_H_LBORDER_S_OFFSET)
#define reg_LCD_PDC1_H_LBORDER_S                           (*( REGType32v *) REG_PDC1_H_LBORDER_S_ADDR)

/* PDC1_H_INTR_POS */

#define REG_PDC1_H_INTR_POS_OFFSET                         0x40051c
#define REG_PDC1_H_INTR_POS_ADDR                           (HW_REG_BASE + REG_PDC1_H_INTR_POS_OFFSET)
#define reg_LCD_PDC1_H_INTR_POS                            (*( REGType32v *) REG_PDC1_H_INTR_POS_ADDR)

/* PDC1_H_DMA_POS */

#define REG_PDC1_H_DMA_POS_OFFSET                          0x400520
#define REG_PDC1_H_DMA_POS_ADDR                            (HW_REG_BASE + REG_PDC1_H_DMA_POS_OFFSET)
#define reg_LCD_PDC1_H_DMA_POS                             (*( REGType32v *) REG_PDC1_H_DMA_POS_ADDR)

/* PDC1_V_COUNT_SIZE */

#define REG_PDC1_V_COUNT_SIZE_OFFSET                       0x400524
#define REG_PDC1_V_COUNT_SIZE_ADDR                         (HW_REG_BASE + REG_PDC1_V_COUNT_SIZE_OFFSET)
#define reg_LCD_PDC1_V_COUNT_SIZE                          (*( REGType32v *) REG_PDC1_V_COUNT_SIZE_ADDR)

/* PDC1_V_DISP_S */

#define REG_PDC1_V_DISP_S_OFFSET                           0x400528
#define REG_PDC1_V_DISP_S_ADDR                             (HW_REG_BASE + REG_PDC1_V_DISP_S_OFFSET)
#define reg_LCD_PDC1_V_DISP_S                              (*( REGType32v *) REG_PDC1_V_DISP_S_ADDR)

/* PDC1_V_BBORDER_S */

#define REG_PDC1_V_BBORDER_S_OFFSET                        0x40052c
#define REG_PDC1_V_BBORDER_S_ADDR                          (HW_REG_BASE + REG_PDC1_V_BBORDER_S_OFFSET)
#define reg_LCD_PDC1_V_BBORDER_S                           (*( REGType32v *) REG_PDC1_V_BBORDER_S_ADDR)

/* PDC1_V_BLANK_S */

#define REG_PDC1_V_BLANK_S_OFFSET                          0x400530
#define REG_PDC1_V_BLANK_S_ADDR                            (HW_REG_BASE + REG_PDC1_V_BLANK_S_OFFSET)
#define reg_LCD_PDC1_V_BLANK_S                             (*( REGType32v *) REG_PDC1_V_BLANK_S_ADDR)

/* PDC1_V_SYNC_S */

#define REG_PDC1_V_SYNC_S_OFFSET                           0x400534
#define REG_PDC1_V_SYNC_S_ADDR                             (HW_REG_BASE + REG_PDC1_V_SYNC_S_OFFSET)
#define reg_LCD_PDC1_V_SYNC_S                              (*( REGType32v *) REG_PDC1_V_SYNC_S_ADDR)

/* PDC1_V_BPORTCH_S */

#define REG_PDC1_V_BPORTCH_S_OFFSET                        0x400538
#define REG_PDC1_V_BPORTCH_S_ADDR                          (HW_REG_BASE + REG_PDC1_V_BPORTCH_S_OFFSET)
#define reg_LCD_PDC1_V_BPORTCH_S                           (*( REGType32v *) REG_PDC1_V_BPORTCH_S_ADDR)

/* PDC1_V_TBORDER_S */

#define REG_PDC1_V_TBORDER_S_OFFSET                        0x40053c
#define REG_PDC1_V_TBORDER_S_ADDR                          (HW_REG_BASE + REG_PDC1_V_TBORDER_S_OFFSET)
#define reg_LCD_PDC1_V_TBORDER_S                           (*( REGType32v *) REG_PDC1_V_TBORDER_S_ADDR)

/* PDC1_V_INTR_POS */

#define REG_PDC1_V_INTR_POS_OFFSET                         0x400540
#define REG_PDC1_V_INTR_POS_ADDR                           (HW_REG_BASE + REG_PDC1_V_INTR_POS_OFFSET)
#define reg_LCD_PDC1_V_INTR_POS                            (*( REGType32v *) REG_PDC1_V_INTR_POS_ADDR)

/* PDC1_V_INC_H_POS */

#define REG_PDC1_V_INC_H_POS_OFFSET                        0x400544
#define REG_PDC1_V_INC_H_POS_ADDR                          (HW_REG_BASE + REG_PDC1_V_INC_H_POS_OFFSET)
#define reg_LCD_PDC1_V_INC_H_POS                           (*( REGType32v *) REG_PDC1_V_INC_H_POS_ADDR)

/* PDC1_SIGNAL_POL */

#define REG_PDC1_SIGNAL_POL_OFFSET                         0x400548
#define REG_PDC1_SIGNAL_POL_ADDR                           (HW_REG_BASE + REG_PDC1_SIGNAL_POL_OFFSET)
#define reg_LCD_PDC1_SIGNAL_POL                            (*( REGType32v *) REG_PDC1_SIGNAL_POL_ADDR)

/* PDC1_BORDER_COL */

#define REG_PDC1_BORDER_COL_OFFSET                         0x40054c
#define REG_PDC1_BORDER_COL_ADDR                           (HW_REG_BASE + REG_PDC1_BORDER_COL_OFFSET)
#define reg_LCD_PDC1_BORDER_COL                            (*( REGType32v *) REG_PDC1_BORDER_COL_ADDR)

/* PDC1_H_COUNT */

#define REG_PDC1_H_COUNT_OFFSET                            0x400550
#define REG_PDC1_H_COUNT_ADDR                              (HW_REG_BASE + REG_PDC1_H_COUNT_OFFSET)
#define reg_LCD_PDC1_H_COUNT                               (*(const REGType32v *) REG_PDC1_H_COUNT_ADDR)

/* PDC1_V_COUNT */

#define REG_PDC1_V_COUNT_OFFSET                            0x400554
#define REG_PDC1_V_COUNT_ADDR                              (HW_REG_BASE + REG_PDC1_V_COUNT_OFFSET)
#define reg_LCD_PDC1_V_COUNT                               (*(const REGType32v *) REG_PDC1_V_COUNT_ADDR)

/* PDC1_OUT_SIZE */

#define REG_PDC1_OUT_SIZE_OFFSET                           0x40055c
#define REG_PDC1_OUT_SIZE_ADDR                             (HW_REG_BASE + REG_PDC1_OUT_SIZE_OFFSET)
#define reg_LCD_PDC1_OUT_SIZE                              (*( REGType32v *) REG_PDC1_OUT_SIZE_ADDR)

/* PDC1_PIC_BORDER_H */

#define REG_PDC1_PIC_BORDER_H_OFFSET                       0x400560
#define REG_PDC1_PIC_BORDER_H_ADDR                         (HW_REG_BASE + REG_PDC1_PIC_BORDER_H_OFFSET)
#define reg_LCD_PDC1_PIC_BORDER_H                          (*( REGType32v *) REG_PDC1_PIC_BORDER_H_ADDR)

/* PDC1_PIC_BORDER_V */

#define REG_PDC1_PIC_BORDER_V_OFFSET                       0x400564
#define REG_PDC1_PIC_BORDER_V_ADDR                         (HW_REG_BASE + REG_PDC1_PIC_BORDER_V_OFFSET)
#define reg_LCD_PDC1_PIC_BORDER_V                          (*( REGType32v *) REG_PDC1_PIC_BORDER_V_ADDR)

/* PDC1_FB0_ADR */

#define REG_PDC1_FB0_ADR_OFFSET                            0x400568
#define REG_PDC1_FB0_ADR_ADDR                              (HW_REG_BASE + REG_PDC1_FB0_ADR_OFFSET)
#define reg_LCD_PDC1_FB0_ADR                               (*( REGType32v *) REG_PDC1_FB0_ADR_ADDR)

/* PDC1_FB1_ADR */

#define REG_PDC1_FB1_ADR_OFFSET                            0x40056C
#define REG_PDC1_FB1_ADR_ADDR                              (HW_REG_BASE + REG_PDC1_FB1_ADR_OFFSET)
#define reg_LCD_PDC1_FB1_ADR                               (*( REGType32v *) REG_PDC1_FB1_ADR_ADDR)

/* PDC1_MODE */

#define REG_PDC1_MODE_OFFSET                               0x400570
#define REG_PDC1_MODE_ADDR                                 (HW_REG_BASE + REG_PDC1_MODE_OFFSET)
#define reg_LCD_PDC1_MODE                                  (*( REGType32v *) REG_PDC1_MODE_ADDR)

/* PDC1_START */

#define REG_PDC1_START_OFFSET                              0x400574
#define REG_PDC1_START_ADDR                                (HW_REG_BASE + REG_PDC1_START_OFFSET)
#define reg_LCD_PDC1_START                                 (*( REGType32v *) REG_PDC1_START_ADDR)

/* PDC1_SWAP */

#define REG_PDC1_SWAP_OFFSET                               0x400578
#define REG_PDC1_SWAP_ADDR                                 (HW_REG_BASE + REG_PDC1_SWAP_OFFSET)
#define reg_LCD_PDC1_SWAP                                  (*( REGType32v *) REG_PDC1_SWAP_ADDR)

/* PDC1_STAT */

#define REG_PDC1_STAT_OFFSET                               0x40057c
#define REG_PDC1_STAT_ADDR                                 (HW_REG_BASE + REG_PDC1_STAT_OFFSET)
#define reg_LCD_PDC1_STAT                                  (*(const REGType32v *) REG_PDC1_STAT_ADDR)

/* PDC1_GTBL_ADR */

#define REG_PDC1_GTBL_ADR_OFFSET                           0x400580
#define REG_PDC1_GTBL_ADR_ADDR                             (HW_REG_BASE + REG_PDC1_GTBL_ADR_OFFSET)
#define reg_LCD_PDC1_GTBL_ADR                              (*( REGType32v *) REG_PDC1_GTBL_ADR_ADDR)

/* PDC1_GTBL_DATA */

#define REG_PDC1_GTBL_DATA_OFFSET                          0x400584
#define REG_PDC1_GTBL_DATA_ADDR                            (HW_REG_BASE + REG_PDC1_GTBL_DATA_OFFSET)
#define reg_LCD_PDC1_GTBL_DATA                             (*( REGType32v *) REG_PDC1_GTBL_DATA_ADDR)

/* PDC1_FB_SIZE */

#define REG_PDC1_FB_SIZE_OFFSET                            0x400590
#define REG_PDC1_FB_SIZE_ADDR                              (HW_REG_BASE + REG_PDC1_FB_SIZE_OFFSET)
#define reg_LCD_PDC1_FB_SIZE                               (*( REGType32v *) REG_PDC1_FB_SIZE_ADDR)

/* PDC1_FB0_B_ADR */

#define REG_PDC1_FB0_B_ADR_OFFSET                          0x400594
#define REG_PDC1_FB0_B_ADR_ADDR                            (HW_REG_BASE + REG_PDC1_FB0_B_ADR_OFFSET)
#define reg_LCD_PDC1_FB0_B_ADR                             (*( REGType32v *) REG_PDC1_FB0_B_ADR_ADDR)

/* PDC1_FB1_B_ADR */

#define REG_PDC1_FB1_B_ADR_OFFSET                          0x400598
#define REG_PDC1_FB1_B_ADR_ADDR                            (HW_REG_BASE + REG_PDC1_FB1_B_ADR_OFFSET)
#define reg_LCD_PDC1_FB1_B_ADR                             (*( REGType32v *) REG_PDC1_FB1_B_ADR_ADDR)

/* PDC1_UPDATE */

#define REG_PDC1_UPDATE_OFFSET                             0x40059c
#define REG_PDC1_UPDATE_ADDR                               (HW_REG_BASE + REG_PDC1_UPDATE_OFFSET)
#define reg_LCD_PDC1_UPDATE                                (*( REGType32v *) REG_PDC1_UPDATE_ADDR)


/*
 * Definitions of Register fields
 */


/* LCDC_CNT0 */

#define REG_LCD_LCDC_CNT0_SEL_INV_SHIFT                    18
#define REG_LCD_LCDC_CNT0_SEL_INV_SIZE                     1
#define REG_LCD_LCDC_CNT0_SEL_INV_MASK                     0x00040000

#define REG_LCD_LCDC_CNT0_SEL_AUTO_SHIFT                   17
#define REG_LCD_LCDC_CNT0_SEL_AUTO_SIZE                    1
#define REG_LCD_LCDC_CNT0_SEL_AUTO_MASK                    0x00020000

#define REG_LCD_LCDC_CNT0_SEL_EN_SHIFT                     16
#define REG_LCD_LCDC_CNT0_SEL_EN_SIZE                      1
#define REG_LCD_LCDC_CNT0_SEL_EN_MASK                      0x00010000

#define REG_LCD_LCDC_CNT0_PWM_INV_SHIFT                    2
#define REG_LCD_LCDC_CNT0_PWM_INV_SIZE                     1
#define REG_LCD_LCDC_CNT0_PWM_INV_MASK                     0x00000004

#define REG_LCD_LCDC_CNT0_PWM_AUTO_SHIFT                   1
#define REG_LCD_LCDC_CNT0_PWM_AUTO_SIZE                    1
#define REG_LCD_LCDC_CNT0_PWM_AUTO_MASK                    0x00000002

#define REG_LCD_LCDC_CNT0_PWM_EN_SHIFT                     0
#define REG_LCD_LCDC_CNT0_PWM_EN_SIZE                      1
#define REG_LCD_LCDC_CNT0_PWM_EN_MASK                      0x00000001

#ifndef SDK_ASM
#define REG_LCD_LCDC_CNT0_FIELD( sel_inv, sel_auto, sel_en, pwm_inv, pwm_auto, pwm_en ) \
    (u32)( \
    ((u32)(sel_inv) << REG_LCD_LCDC_CNT0_SEL_INV_SHIFT) | \
    ((u32)(sel_auto) << REG_LCD_LCDC_CNT0_SEL_AUTO_SHIFT) | \
    ((u32)(sel_en) << REG_LCD_LCDC_CNT0_SEL_EN_SHIFT) | \
    ((u32)(pwm_inv) << REG_LCD_LCDC_CNT0_PWM_INV_SHIFT) | \
    ((u32)(pwm_auto) << REG_LCD_LCDC_CNT0_PWM_AUTO_SHIFT) | \
    ((u32)(pwm_en) << REG_LCD_LCDC_CNT0_PWM_EN_SHIFT))
#endif


/* LCDC_CNT1 */

#define REG_LCD_LCDC_CNT1_MP_SHIFT                         16
#define REG_LCD_LCDC_CNT1_MP_SIZE                          16
#define REG_LCD_LCDC_CNT1_MP_MASK                          0xffff0000

#define REG_LCD_LCDC_CNT1_SP_SHIFT                         0
#define REG_LCD_LCDC_CNT1_SP_SIZE                          16
#define REG_LCD_LCDC_CNT1_SP_MASK                          0x0000ffff

#ifndef SDK_ASM
#define REG_LCD_LCDC_CNT1_FIELD( mp, sp ) \
    (u32)( \
    ((u32)(mp) << REG_LCD_LCDC_CNT1_MP_SHIFT) | \
    ((u32)(sp) << REG_LCD_LCDC_CNT1_SP_SHIFT))
#endif


/* LCDC_CNT2 */

#define REG_LCD_LCDC_CNT2_X2_SHIFT                         9
#define REG_LCD_LCDC_CNT2_X2_SIZE                          1
#define REG_LCD_LCDC_CNT2_X2_MASK                          0x00000200

#define REG_LCD_LCDC_CNT2_MODE_SHIFT                       8
#define REG_LCD_LCDC_CNT2_MODE_SIZE                        1
#define REG_LCD_LCDC_CNT2_MODE_MASK                        0x00000100

#define REG_LCD_LCDC_CNT2_SEL_SHIFT                        1
#define REG_LCD_LCDC_CNT2_SEL_SIZE                         1
#define REG_LCD_LCDC_CNT2_SEL_MASK                         0x00000002

#define REG_LCD_LCDC_CNT2_EN_SHIFT                         0
#define REG_LCD_LCDC_CNT2_EN_SIZE                          1
#define REG_LCD_LCDC_CNT2_EN_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_LCD_LCDC_CNT2_FIELD( x2, mode, sel, en ) \
    (u32)( \
    ((u32)(x2) << REG_LCD_LCDC_CNT2_X2_SHIFT) | \
    ((u32)(mode) << REG_LCD_LCDC_CNT2_MODE_SHIFT) | \
    ((u32)(sel) << REG_LCD_LCDC_CNT2_SEL_SHIFT) | \
    ((u32)(en) << REG_LCD_LCDC_CNT2_EN_SHIFT))
#endif


/* LCDC_CNT2_EIU */

#define REG_LCD_LCDC_CNT2_EIU_GHR1_SHIFT                   26
#define REG_LCD_LCDC_CNT2_EIU_GHR1_SIZE                    1
#define REG_LCD_LCDC_CNT2_EIU_GHR1_MASK                    0x04000000

#define REG_LCD_LCDC_CNT2_EIU_GHR0_SHIFT                   10
#define REG_LCD_LCDC_CNT2_EIU_GHR0_SIZE                    1
#define REG_LCD_LCDC_CNT2_EIU_GHR0_MASK                    0x00000400

#define REG_LCD_LCDC_CNT2_EIU_X2_SHIFT                     9
#define REG_LCD_LCDC_CNT2_EIU_X2_SIZE                      1
#define REG_LCD_LCDC_CNT2_EIU_X2_MASK                      0x00000200

#define REG_LCD_LCDC_CNT2_EIU_MODE_SHIFT                   8
#define REG_LCD_LCDC_CNT2_EIU_MODE_SIZE                    1
#define REG_LCD_LCDC_CNT2_EIU_MODE_MASK                    0x00000100

#define REG_LCD_LCDC_CNT2_EIU_SEL_SHIFT                    1
#define REG_LCD_LCDC_CNT2_EIU_SEL_SIZE                     1
#define REG_LCD_LCDC_CNT2_EIU_SEL_MASK                     0x00000002

#define REG_LCD_LCDC_CNT2_EIU_EN_SHIFT                     0
#define REG_LCD_LCDC_CNT2_EIU_EN_SIZE                      1
#define REG_LCD_LCDC_CNT2_EIU_EN_MASK                      0x00000001

#ifndef SDK_ASM
#define REG_LCD_LCDC_CNT2_EIU_FIELD( ghr1, ghr0, x2, mode, sel, en ) \
    (u32)( \
    ((u32)(ghr1) << REG_LCD_LCDC_CNT2_EIU_GHR1_SHIFT) | \
    ((u32)(ghr0) << REG_LCD_LCDC_CNT2_EIU_GHR0_SHIFT) | \
    ((u32)(x2) << REG_LCD_LCDC_CNT2_EIU_X2_SHIFT) | \
    ((u32)(mode) << REG_LCD_LCDC_CNT2_EIU_MODE_SHIFT) | \
    ((u32)(sel) << REG_LCD_LCDC_CNT2_EIU_SEL_SHIFT) | \
    ((u32)(en) << REG_LCD_LCDC_CNT2_EIU_EN_SHIFT))
#endif


/* LCDC_CNT3 */

#define REG_LCD_LCDC_CNT3_FIX2_SHIFT                       16
#define REG_LCD_LCDC_CNT3_FIX2_SIZE                        1
#define REG_LCD_LCDC_CNT3_FIX2_MASK                        0x00010000

#define REG_LCD_LCDC_CNT3_FIX1_SHIFT                       0
#define REG_LCD_LCDC_CNT3_FIX1_SIZE                        1
#define REG_LCD_LCDC_CNT3_FIX1_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_LCD_LCDC_CNT3_FIELD( fix2, fix1 ) \
    (u32)( \
    ((u32)(fix2) << REG_LCD_LCDC_CNT3_FIX2_SHIFT) | \
    ((u32)(fix1) << REG_LCD_LCDC_CNT3_FIX1_SHIFT))
#endif


/* LCDC_CNT4 */

#define REG_LCD_LCDC_CNT4_LVDS1_SHIFT                      8
#define REG_LCD_LCDC_CNT4_LVDS1_SIZE                       5
#define REG_LCD_LCDC_CNT4_LVDS1_MASK                       0x00001f00

#define REG_LCD_LCDC_CNT4_LVDS0_SHIFT                      0
#define REG_LCD_LCDC_CNT4_LVDS0_SIZE                       4
#define REG_LCD_LCDC_CNT4_LVDS0_MASK                       0x0000000f

#ifndef SDK_ASM
#define REG_LCD_LCDC_CNT4_FIELD( lvds1, lvds0 ) \
    (u32)( \
    ((u32)(lvds1) << REG_LCD_LCDC_CNT4_LVDS1_SHIFT) | \
    ((u32)(lvds0) << REG_LCD_LCDC_CNT4_LVDS0_SHIFT))
#endif


/* LCDC_CNT5 */

#define REG_LCD_LCDC_CNT5_RST_SHIFT                        0
#define REG_LCD_LCDC_CNT5_RST_SIZE                         1
#define REG_LCD_LCDC_CNT5_RST_MASK                         0x00000001

#ifndef SDK_ASM
#define REG_LCD_LCDC_CNT5_FIELD( rst ) \
    (u32)( \
    ((u32)(rst) << REG_LCD_LCDC_CNT5_RST_SHIFT))
#endif


/* LCDC_CNT6 */

#define REG_LCD_LCDC_CNT6_HR2_SHIFT                        16
#define REG_LCD_LCDC_CNT6_HR2_SIZE                         1
#define REG_LCD_LCDC_CNT6_HR2_MASK                         0x00010000

#define REG_LCD_LCDC_CNT6_HR1_SHIFT                        0
#define REG_LCD_LCDC_CNT6_HR1_SIZE                         1
#define REG_LCD_LCDC_CNT6_HR1_MASK                         0x00000001

#ifndef SDK_ASM
#define REG_LCD_LCDC_CNT6_FIELD( hr2, hr1 ) \
    (u32)( \
    ((u32)(hr2) << REG_LCD_LCDC_CNT6_HR2_SHIFT) | \
    ((u32)(hr1) << REG_LCD_LCDC_CNT6_HR1_SHIFT))
#endif


/* ABL0_CNT */

#define REG_LCD_ABL0_CNT_TD_E_SHIFT                        9
#define REG_LCD_ABL0_CNT_TD_E_SIZE                         1
#define REG_LCD_ABL0_CNT_TD_E_MASK                         0x00000200

#define REG_LCD_ABL0_CNT_SD_E_SHIFT                        8
#define REG_LCD_ABL0_CNT_SD_E_SIZE                         1
#define REG_LCD_ABL0_CNT_SD_E_MASK                         0x00000100

#define REG_LCD_ABL0_CNT_ABL_E_SHIFT                       0
#define REG_LCD_ABL0_CNT_ABL_E_SIZE                        1
#define REG_LCD_ABL0_CNT_ABL_E_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_LCD_ABL0_CNT_FIELD( td_e, sd_e, abl_e ) \
    (u32)( \
    ((u32)(td_e) << REG_LCD_ABL0_CNT_TD_E_SHIFT) | \
    ((u32)(sd_e) << REG_LCD_ABL0_CNT_SD_E_SHIFT) | \
    ((u32)(abl_e) << REG_LCD_ABL0_CNT_ABL_E_SHIFT))
#endif


/* ABL0_FCOLOR */

#define REG_LCD_ABL0_FCOLOR_E_SHIFT                        24
#define REG_LCD_ABL0_FCOLOR_E_SIZE                         1
#define REG_LCD_ABL0_FCOLOR_E_MASK                         0x01000000

#define REG_LCD_ABL0_FCOLOR_B_SHIFT                        16
#define REG_LCD_ABL0_FCOLOR_B_SIZE                         8
#define REG_LCD_ABL0_FCOLOR_B_MASK                         0x00ff0000

#define REG_LCD_ABL0_FCOLOR_G_SHIFT                        8
#define REG_LCD_ABL0_FCOLOR_G_SIZE                         8
#define REG_LCD_ABL0_FCOLOR_G_MASK                         0x0000ff00

#define REG_LCD_ABL0_FCOLOR_R_SHIFT                        0
#define REG_LCD_ABL0_FCOLOR_R_SIZE                         8
#define REG_LCD_ABL0_FCOLOR_R_MASK                         0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_FCOLOR_FIELD( e, b, g, r ) \
    (u32)( \
    ((u32)(e) << REG_LCD_ABL0_FCOLOR_E_SHIFT) | \
    ((u32)(b) << REG_LCD_ABL0_FCOLOR_B_SHIFT) | \
    ((u32)(g) << REG_LCD_ABL0_FCOLOR_G_SHIFT) | \
    ((u32)(r) << REG_LCD_ABL0_FCOLOR_R_SHIFT))
#endif


/* ABL0_HST_SX */

#define REG_LCD_ABL0_HST_SX_SX_SHIFT                       0
#define REG_LCD_ABL0_HST_SX_SX_SIZE                        10
#define REG_LCD_ABL0_HST_SX_SX_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_HST_SX_FIELD( sx ) \
    (u32)( \
    ((u32)(sx) << REG_LCD_ABL0_HST_SX_SX_SHIFT))
#endif


/* ABL0_HST_EX */

#define REG_LCD_ABL0_HST_EX_EX_SHIFT                       0
#define REG_LCD_ABL0_HST_EX_EX_SIZE                        10
#define REG_LCD_ABL0_HST_EX_EX_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_HST_EX_FIELD( ex ) \
    (u32)( \
    ((u32)(ex) << REG_LCD_ABL0_HST_EX_EX_SHIFT))
#endif


/* ABL0_HST_SY */

#define REG_LCD_ABL0_HST_SY_SY_SHIFT                       0
#define REG_LCD_ABL0_HST_SY_SY_SIZE                        10
#define REG_LCD_ABL0_HST_SY_SY_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_HST_SY_FIELD( sy ) \
    (u32)( \
    ((u32)(sy) << REG_LCD_ABL0_HST_SY_SY_SHIFT))
#endif


/* ABL0_HST_EY */

#define REG_LCD_ABL0_HST_EY_EY_SHIFT                       0
#define REG_LCD_ABL0_HST_EY_EY_SIZE                        10
#define REG_LCD_ABL0_HST_EY_EY_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_HST_EY_FIELD( ey ) \
    (u32)( \
    ((u32)(ey) << REG_LCD_ABL0_HST_EY_EY_SHIFT))
#endif


/* ABL0_GTHP */

#define REG_LCD_ABL0_GTHP_GTHP_SHIFT                       0
#define REG_LCD_ABL0_GTHP_GTHP_SIZE                        9
#define REG_LCD_ABL0_GTHP_GTHP_MASK                        0x000001ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_GTHP_FIELD( gthp ) \
    (u32)( \
    ((u32)(gthp) << REG_LCD_ABL0_GTHP_GTHP_SHIFT))
#endif


/* ABL0_GTHMIN */

#define REG_LCD_ABL0_GTHMIN_GTHMIN_SHIFT                   0
#define REG_LCD_ABL0_GTHMIN_GTHMIN_SIZE                    8
#define REG_LCD_ABL0_GTHMIN_GTHMIN_MASK                    0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_GTHMIN_FIELD( gthmin ) \
    (u32)( \
    ((u32)(gthmin) << REG_LCD_ABL0_GTHMIN_GTHMIN_SHIFT))
#endif


/* ABL0_GTHMAX */

#define REG_LCD_ABL0_GTHMAX_GTHMAX_SHIFT                   0
#define REG_LCD_ABL0_GTHMAX_GTHMAX_SIZE                    8
#define REG_LCD_ABL0_GTHMAX_GTHMAX_MASK                    0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_GTHMAX_FIELD( gthmax ) \
    (u32)( \
    ((u32)(gthmax) << REG_LCD_ABL0_GTHMAX_GTHMAX_SHIFT))
#endif


/* ABL0_GTHMAXEX */

#define REG_LCD_ABL0_GTHMAXEX_GTHMAXEX_SHIFT               0
#define REG_LCD_ABL0_GTHMAXEX_GTHMAXEX_SIZE                8
#define REG_LCD_ABL0_GTHMAXEX_GTHMAXEX_MASK                0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_GTHMAXEX_FIELD( gthmaxex ) \
    (u32)( \
    ((u32)(gthmaxex) << REG_LCD_ABL0_GTHMAXEX_GTHMAXEX_SHIFT))
#endif


/* ABL0_INERTIA */

#define REG_LCD_ABL0_INERTIA_FRM_SHIFT                     0
#define REG_LCD_ABL0_INERTIA_FRM_SIZE                      4
#define REG_LCD_ABL0_INERTIA_FRM_MASK                      0x0000000f

#ifndef SDK_ASM
#define REG_LCD_ABL0_INERTIA_FIELD( frm ) \
    (u32)( \
    ((u32)(frm) << REG_LCD_ABL0_INERTIA_FRM_SHIFT))
#endif


/* ABL0_INERTIA_EIU */

#define REG_LCD_ABL0_INERTIA_EIU_SP_SHIFT                  20
#define REG_LCD_ABL0_INERTIA_EIU_SP_SIZE                   1
#define REG_LCD_ABL0_INERTIA_EIU_SP_MASK                   0x00100000

#define REG_LCD_ABL0_INERTIA_EIU_MI_SHIFT                  16
#define REG_LCD_ABL0_INERTIA_EIU_MI_SIZE                   4
#define REG_LCD_ABL0_INERTIA_EIU_MI_MASK                   0x000f0000

#define REG_LCD_ABL0_INERTIA_EIU_GI_SHIFT                  0
#define REG_LCD_ABL0_INERTIA_EIU_GI_SIZE                   4
#define REG_LCD_ABL0_INERTIA_EIU_GI_MASK                   0x0000000f

#ifndef SDK_ASM
#define REG_LCD_ABL0_INERTIA_EIU_FIELD( sp, mi, gi ) \
    (u32)( \
    ((u32)(sp) << REG_LCD_ABL0_INERTIA_EIU_SP_SHIFT) | \
    ((u32)(mi) << REG_LCD_ABL0_INERTIA_EIU_MI_SHIFT) | \
    ((u32)(gi) << REG_LCD_ABL0_INERTIA_EIU_GI_SHIFT))
#endif


/* ABL0_RSMIN */

#define REG_LCD_ABL0_RSMIN_RSMIN_SHIFT                     0
#define REG_LCD_ABL0_RSMIN_RSMIN_SIZE                      8
#define REG_LCD_ABL0_RSMIN_RSMIN_MASK                      0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_RSMIN_FIELD( rsmin ) \
    (u32)( \
    ((u32)(rsmin) << REG_LCD_ABL0_RSMIN_RSMIN_SHIFT))
#endif


/* ABL0_RSMAX */

#define REG_LCD_ABL0_RSMAX_RSMAX_SHIFT                     0
#define REG_LCD_ABL0_RSMAX_RSMAX_SIZE                      8
#define REG_LCD_ABL0_RSMAX_RSMAX_MASK                      0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_RSMAX_FIELD( rsmax ) \
    (u32)( \
    ((u32)(rsmax) << REG_LCD_ABL0_RSMAX_RSMAX_SHIFT))
#endif


/* ABL0_LMAX */

#define REG_LCD_ABL0_LMAX_LMAX_SHIFT                       0
#define REG_LCD_ABL0_LMAX_LMAX_SIZE                        10
#define REG_LCD_ABL0_LMAX_LMAX_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_LMAX_FIELD( lmax ) \
    (u32)( \
    ((u32)(lmax) << REG_LCD_ABL0_LMAX_LMAX_SHIFT))
#endif


/* ABL0_PWMCNT */

#define REG_LCD_ABL0_PWMCNT_PC_SHIFT                       16
#define REG_LCD_ABL0_PWMCNT_PC_SIZE                        3
#define REG_LCD_ABL0_PWMCNT_PC_MASK                        0x00070000

#define REG_LCD_ABL0_PWMCNT_PS_SHIFT                       12
#define REG_LCD_ABL0_PWMCNT_PS_SIZE                        4
#define REG_LCD_ABL0_PWMCNT_PS_MASK                        0x0000f000

#define REG_LCD_ABL0_PWMCNT_PD_SHIFT                       0
#define REG_LCD_ABL0_PWMCNT_PD_SIZE                        10
#define REG_LCD_ABL0_PWMCNT_PD_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_PWMCNT_FIELD( pc, ps, pd ) \
    (u32)( \
    ((u32)(pc) << REG_LCD_ABL0_PWMCNT_PC_SHIFT) | \
    ((u32)(ps) << REG_LCD_ABL0_PWMCNT_PS_SHIFT) | \
    ((u32)(pd) << REG_LCD_ABL0_PWMCNT_PD_SHIFT))
#endif


/* ABL0_PWMCNT_EIU */

#define REG_LCD_ABL0_PWMCNT_EIU_PS134_SHIFT                31
#define REG_LCD_ABL0_PWMCNT_EIU_PS134_SIZE                 1
#define REG_LCD_ABL0_PWMCNT_EIU_PS134_MASK                 0x80000000

#define REG_LCD_ABL0_PWMCNT_EIU_SD_SHIFT                   24
#define REG_LCD_ABL0_PWMCNT_EIU_SD_SIZE                    7
#define REG_LCD_ABL0_PWMCNT_EIU_SD_MASK                    0x7f000000

#define REG_LCD_ABL0_PWMCNT_EIU_PI_SHIFT                   20
#define REG_LCD_ABL0_PWMCNT_EIU_PI_SIZE                    4
#define REG_LCD_ABL0_PWMCNT_EIU_PI_MASK                    0x00f00000

#define REG_LCD_ABL0_PWMCNT_EIU_FE_SHIFT                   19
#define REG_LCD_ABL0_PWMCNT_EIU_FE_SIZE                    1
#define REG_LCD_ABL0_PWMCNT_EIU_FE_MASK                    0x00080000

#define REG_LCD_ABL0_PWMCNT_EIU_PC_SHIFT                   16
#define REG_LCD_ABL0_PWMCNT_EIU_PC_SIZE                    3
#define REG_LCD_ABL0_PWMCNT_EIU_PC_MASK                    0x00070000

#define REG_LCD_ABL0_PWMCNT_EIU_PS_SHIFT                   12
#define REG_LCD_ABL0_PWMCNT_EIU_PS_SIZE                    4
#define REG_LCD_ABL0_PWMCNT_EIU_PS_MASK                    0x0000f000

#define REG_LCD_ABL0_PWMCNT_EIU_PD_SHIFT                   0
#define REG_LCD_ABL0_PWMCNT_EIU_PD_SIZE                    10
#define REG_LCD_ABL0_PWMCNT_EIU_PD_MASK                    0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_PWMCNT_EIU_FIELD( ps134, sd, pi, fe, pc, ps, pd ) \
    (u32)( \
    ((u32)(ps134) << REG_LCD_ABL0_PWMCNT_EIU_PS134_SHIFT) | \
    ((u32)(sd) << REG_LCD_ABL0_PWMCNT_EIU_SD_SHIFT) | \
    ((u32)(pi) << REG_LCD_ABL0_PWMCNT_EIU_PI_SHIFT) | \
    ((u32)(fe) << REG_LCD_ABL0_PWMCNT_EIU_FE_SHIFT) | \
    ((u32)(pc) << REG_LCD_ABL0_PWMCNT_EIU_PC_SHIFT) | \
    ((u32)(ps) << REG_LCD_ABL0_PWMCNT_EIU_PS_SHIFT) | \
    ((u32)(pd) << REG_LCD_ABL0_PWMCNT_EIU_PD_SHIFT))
#endif


/* ABL0_HST1 */

#define REG_LCD_ABL0_HST1_IB_B_SHIFT                       16
#define REG_LCD_ABL0_HST1_IB_B_SIZE                        8
#define REG_LCD_ABL0_HST1_IB_B_MASK                        0x00ff0000

#define REG_LCD_ABL0_HST1_IB_G_SHIFT                       8
#define REG_LCD_ABL0_HST1_IB_G_SIZE                        8
#define REG_LCD_ABL0_HST1_IB_G_MASK                        0x0000ff00

#define REG_LCD_ABL0_HST1_IB_R_SHIFT                       0
#define REG_LCD_ABL0_HST1_IB_R_SIZE                        8
#define REG_LCD_ABL0_HST1_IB_R_MASK                        0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_HST1_FIELD( ib_b, ib_g, ib_r ) \
    (u32)( \
    ((u32)(ib_b) << REG_LCD_ABL0_HST1_IB_B_SHIFT) | \
    ((u32)(ib_g) << REG_LCD_ABL0_HST1_IB_G_SHIFT) | \
    ((u32)(ib_r) << REG_LCD_ABL0_HST1_IB_R_SHIFT))
#endif


/* ABL0_HST2 */

#define REG_LCD_ABL0_HST2_C_B_SHIFT                        16
#define REG_LCD_ABL0_HST2_C_B_SIZE                         8
#define REG_LCD_ABL0_HST2_C_B_MASK                         0x00ff0000

#define REG_LCD_ABL0_HST2_C_G_SHIFT                        8
#define REG_LCD_ABL0_HST2_C_G_SIZE                         8
#define REG_LCD_ABL0_HST2_C_G_MASK                         0x0000ff00

#define REG_LCD_ABL0_HST2_C_R_SHIFT                        0
#define REG_LCD_ABL0_HST2_C_R_SIZE                         8
#define REG_LCD_ABL0_HST2_C_R_MASK                         0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_HST2_FIELD( c_b, c_g, c_r ) \
    (u32)( \
    ((u32)(c_b) << REG_LCD_ABL0_HST2_C_B_SHIFT) | \
    ((u32)(c_g) << REG_LCD_ABL0_HST2_C_G_SHIFT) | \
    ((u32)(c_r) << REG_LCD_ABL0_HST2_C_R_SHIFT))
#endif


/* ABL0_DITPAT0 */

#define REG_LCD_ABL0_DITPAT0_W3_SHIFT                      14
#define REG_LCD_ABL0_DITPAT0_W3_SIZE                       2
#define REG_LCD_ABL0_DITPAT0_W3_MASK                       0x0000c000

#define REG_LCD_ABL0_DITPAT0_W2_SHIFT                      10
#define REG_LCD_ABL0_DITPAT0_W2_SIZE                       2
#define REG_LCD_ABL0_DITPAT0_W2_MASK                       0x00000c00

#define REG_LCD_ABL0_DITPAT0_W1_SHIFT                      6
#define REG_LCD_ABL0_DITPAT0_W1_SIZE                       2
#define REG_LCD_ABL0_DITPAT0_W1_MASK                       0x000000c0

#define REG_LCD_ABL0_DITPAT0_W0_SHIFT                      2
#define REG_LCD_ABL0_DITPAT0_W0_SIZE                       2
#define REG_LCD_ABL0_DITPAT0_W0_MASK                       0x0000000c

#ifndef SDK_ASM
#define REG_LCD_ABL0_DITPAT0_FIELD( w3, w2, w1, w0 ) \
    (u32)( \
    ((u32)(w3) << REG_LCD_ABL0_DITPAT0_W3_SHIFT) | \
    ((u32)(w2) << REG_LCD_ABL0_DITPAT0_W2_SHIFT) | \
    ((u32)(w1) << REG_LCD_ABL0_DITPAT0_W1_SHIFT) | \
    ((u32)(w0) << REG_LCD_ABL0_DITPAT0_W0_SHIFT))
#endif


/* ABL0_RSLUT0 */

#define REG_LCD_ABL0_RSLUT0_RSLUT_SHIFT                    0
#define REG_LCD_ABL0_RSLUT0_RSLUT_SIZE                     8
#define REG_LCD_ABL0_RSLUT0_RSLUT_MASK                     0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_RSLUT0_FIELD( rslut ) \
    (u32)( \
    ((u32)(rslut) << REG_LCD_ABL0_RSLUT0_RSLUT_SHIFT))
#endif


/* ABL0_CMAX */

#define REG_LCD_ABL0_CMAX_CMAX_SHIFT                       0
#define REG_LCD_ABL0_CMAX_CMAX_SIZE                        8
#define REG_LCD_ABL0_CMAX_CMAX_MASK                        0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_CMAX_FIELD( cmax ) \
    (u32)( \
    ((u32)(cmax) << REG_LCD_ABL0_CMAX_CMAX_SHIFT))
#endif


/* ABL0_CGTH */

#define REG_LCD_ABL0_CGTH_CGTH_SHIFT                       0
#define REG_LCD_ABL0_CGTH_CGTH_SIZE                        8
#define REG_LCD_ABL0_CGTH_CGTH_MASK                        0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_CGTH_FIELD( cgth ) \
    (u32)( \
    ((u32)(cgth) << REG_LCD_ABL0_CGTH_CGTH_SHIFT))
#endif


/* ABL0_CRS */

#define REG_LCD_ABL0_CRS_CRS_SHIFT                         0
#define REG_LCD_ABL0_CRS_CRS_SIZE                          8
#define REG_LCD_ABL0_CRS_CRS_MASK                          0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_CRS_FIELD( crs ) \
    (u32)( \
    ((u32)(crs) << REG_LCD_ABL0_CRS_CRS_SHIFT))
#endif


/* ABL0_ADJCOE0 */

#define REG_LCD_ABL0_ADJCOE0_C_B_SHIFT                     16
#define REG_LCD_ABL0_ADJCOE0_C_B_SIZE                      8
#define REG_LCD_ABL0_ADJCOE0_C_B_MASK                      0x00ff0000

#define REG_LCD_ABL0_ADJCOE0_C_G_SHIFT                     8
#define REG_LCD_ABL0_ADJCOE0_C_G_SIZE                      8
#define REG_LCD_ABL0_ADJCOE0_C_G_MASK                      0x0000ff00

#define REG_LCD_ABL0_ADJCOE0_C_R_SHIFT                     0
#define REG_LCD_ABL0_ADJCOE0_C_R_SIZE                      8
#define REG_LCD_ABL0_ADJCOE0_C_R_MASK                      0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_ADJCOE0_FIELD( c_b, c_g, c_r ) \
    (u32)( \
    ((u32)(c_b) << REG_LCD_ABL0_ADJCOE0_C_B_SHIFT) | \
    ((u32)(c_g) << REG_LCD_ABL0_ADJCOE0_C_G_SHIFT) | \
    ((u32)(c_r) << REG_LCD_ABL0_ADJCOE0_C_R_SHIFT))
#endif


/* ABL0_RDLUT0 */

#define REG_LCD_ABL0_RDLUT0_RDLUT_SHIFT                    0
#define REG_LCD_ABL0_RDLUT0_RDLUT_SIZE                     10
#define REG_LCD_ABL0_RDLUT0_RDLUT_MASK                     0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL0_RDLUT0_FIELD( rdlut ) \
    (u32)( \
    ((u32)(rdlut) << REG_LCD_ABL0_RDLUT0_RDLUT_SHIFT))
#endif


/* ABL1_CNT */

#define REG_LCD_ABL1_CNT_TD_E_SHIFT                        9
#define REG_LCD_ABL1_CNT_TD_E_SIZE                         1
#define REG_LCD_ABL1_CNT_TD_E_MASK                         0x00000200

#define REG_LCD_ABL1_CNT_SD_E_SHIFT                        8
#define REG_LCD_ABL1_CNT_SD_E_SIZE                         1
#define REG_LCD_ABL1_CNT_SD_E_MASK                         0x00000100

#define REG_LCD_ABL1_CNT_ABL_E_SHIFT                       0
#define REG_LCD_ABL1_CNT_ABL_E_SIZE                        1
#define REG_LCD_ABL1_CNT_ABL_E_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_LCD_ABL1_CNT_FIELD( td_e, sd_e, abl_e ) \
    (u32)( \
    ((u32)(td_e) << REG_LCD_ABL1_CNT_TD_E_SHIFT) | \
    ((u32)(sd_e) << REG_LCD_ABL1_CNT_SD_E_SHIFT) | \
    ((u32)(abl_e) << REG_LCD_ABL1_CNT_ABL_E_SHIFT))
#endif


/* ABL1_FCOLOR */

#define REG_LCD_ABL1_FCOLOR_E_SHIFT                        24
#define REG_LCD_ABL1_FCOLOR_E_SIZE                         1
#define REG_LCD_ABL1_FCOLOR_E_MASK                         0x01000000

#define REG_LCD_ABL1_FCOLOR_B_SHIFT                        16
#define REG_LCD_ABL1_FCOLOR_B_SIZE                         8
#define REG_LCD_ABL1_FCOLOR_B_MASK                         0x00ff0000

#define REG_LCD_ABL1_FCOLOR_G_SHIFT                        8
#define REG_LCD_ABL1_FCOLOR_G_SIZE                         8
#define REG_LCD_ABL1_FCOLOR_G_MASK                         0x0000ff00

#define REG_LCD_ABL1_FCOLOR_R_SHIFT                        0
#define REG_LCD_ABL1_FCOLOR_R_SIZE                         8
#define REG_LCD_ABL1_FCOLOR_R_MASK                         0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_FCOLOR_FIELD( e, b, g, r ) \
    (u32)( \
    ((u32)(e) << REG_LCD_ABL1_FCOLOR_E_SHIFT) | \
    ((u32)(b) << REG_LCD_ABL1_FCOLOR_B_SHIFT) | \
    ((u32)(g) << REG_LCD_ABL1_FCOLOR_G_SHIFT) | \
    ((u32)(r) << REG_LCD_ABL1_FCOLOR_R_SHIFT))
#endif


/* ABL1_HST_SX */

#define REG_LCD_ABL1_HST_SX_SX_SHIFT                       0
#define REG_LCD_ABL1_HST_SX_SX_SIZE                        10
#define REG_LCD_ABL1_HST_SX_SX_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_HST_SX_FIELD( sx ) \
    (u32)( \
    ((u32)(sx) << REG_LCD_ABL1_HST_SX_SX_SHIFT))
#endif


/* ABL1_HST_EX */

#define REG_LCD_ABL1_HST_EX_EX_SHIFT                       0
#define REG_LCD_ABL1_HST_EX_EX_SIZE                        10
#define REG_LCD_ABL1_HST_EX_EX_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_HST_EX_FIELD( ex ) \
    (u32)( \
    ((u32)(ex) << REG_LCD_ABL1_HST_EX_EX_SHIFT))
#endif


/* ABL1_HST_SY */

#define REG_LCD_ABL1_HST_SY_SY_SHIFT                       0
#define REG_LCD_ABL1_HST_SY_SY_SIZE                        10
#define REG_LCD_ABL1_HST_SY_SY_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_HST_SY_FIELD( sy ) \
    (u32)( \
    ((u32)(sy) << REG_LCD_ABL1_HST_SY_SY_SHIFT))
#endif


/* ABL1_HST_EY */

#define REG_LCD_ABL1_HST_EY_EY_SHIFT                       0
#define REG_LCD_ABL1_HST_EY_EY_SIZE                        10
#define REG_LCD_ABL1_HST_EY_EY_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_HST_EY_FIELD( ey ) \
    (u32)( \
    ((u32)(ey) << REG_LCD_ABL1_HST_EY_EY_SHIFT))
#endif


/* ABL1_GTHP */

#define REG_LCD_ABL1_GTHP_GTHP_SHIFT                       0
#define REG_LCD_ABL1_GTHP_GTHP_SIZE                        9
#define REG_LCD_ABL1_GTHP_GTHP_MASK                        0x000001ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_GTHP_FIELD( gthp ) \
    (u32)( \
    ((u32)(gthp) << REG_LCD_ABL1_GTHP_GTHP_SHIFT))
#endif


/* ABL1_GTHMIN */

#define REG_LCD_ABL1_GTHMIN_GTHMIN_SHIFT                   0
#define REG_LCD_ABL1_GTHMIN_GTHMIN_SIZE                    8
#define REG_LCD_ABL1_GTHMIN_GTHMIN_MASK                    0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_GTHMIN_FIELD( gthmin ) \
    (u32)( \
    ((u32)(gthmin) << REG_LCD_ABL1_GTHMIN_GTHMIN_SHIFT))
#endif


/* ABL1_GTHMAX */

#define REG_LCD_ABL1_GTHMAX_GTHMAX_SHIFT                   0
#define REG_LCD_ABL1_GTHMAX_GTHMAX_SIZE                    8
#define REG_LCD_ABL1_GTHMAX_GTHMAX_MASK                    0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_GTHMAX_FIELD( gthmax ) \
    (u32)( \
    ((u32)(gthmax) << REG_LCD_ABL1_GTHMAX_GTHMAX_SHIFT))
#endif


/* ABL1_GTHMAXEX */

#define REG_LCD_ABL1_GTHMAXEX_GTHMAXEX_SHIFT               0
#define REG_LCD_ABL1_GTHMAXEX_GTHMAXEX_SIZE                8
#define REG_LCD_ABL1_GTHMAXEX_GTHMAXEX_MASK                0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_GTHMAXEX_FIELD( gthmaxex ) \
    (u32)( \
    ((u32)(gthmaxex) << REG_LCD_ABL1_GTHMAXEX_GTHMAXEX_SHIFT))
#endif


/* ABL1_INERTIA */

#define REG_LCD_ABL1_INERTIA_FRM_SHIFT                     0
#define REG_LCD_ABL1_INERTIA_FRM_SIZE                      4
#define REG_LCD_ABL1_INERTIA_FRM_MASK                      0x0000000f

#ifndef SDK_ASM
#define REG_LCD_ABL1_INERTIA_FIELD( frm ) \
    (u32)( \
    ((u32)(frm) << REG_LCD_ABL1_INERTIA_FRM_SHIFT))
#endif


/* ABL1_INERTIA_EIU */

#define REG_LCD_ABL1_INERTIA_EIU_SP_SHIFT                  20
#define REG_LCD_ABL1_INERTIA_EIU_SP_SIZE                   1
#define REG_LCD_ABL1_INERTIA_EIU_SP_MASK                   0x00100000

#define REG_LCD_ABL1_INERTIA_EIU_MI_SHIFT                  16
#define REG_LCD_ABL1_INERTIA_EIU_MI_SIZE                   4
#define REG_LCD_ABL1_INERTIA_EIU_MI_MASK                   0x000f0000

#define REG_LCD_ABL1_INERTIA_EIU_GI_SHIFT                  0
#define REG_LCD_ABL1_INERTIA_EIU_GI_SIZE                   4
#define REG_LCD_ABL1_INERTIA_EIU_GI_MASK                   0x0000000f

#ifndef SDK_ASM
#define REG_LCD_ABL1_INERTIA_EIU_FIELD( sp, mi, gi ) \
    (u32)( \
    ((u32)(sp) << REG_LCD_ABL1_INERTIA_EIU_SP_SHIFT) | \
    ((u32)(mi) << REG_LCD_ABL1_INERTIA_EIU_MI_SHIFT) | \
    ((u32)(gi) << REG_LCD_ABL1_INERTIA_EIU_GI_SHIFT))
#endif


/* ABL1_RSMIN */

#define REG_LCD_ABL1_RSMIN_RSMIN_SHIFT                     0
#define REG_LCD_ABL1_RSMIN_RSMIN_SIZE                      8
#define REG_LCD_ABL1_RSMIN_RSMIN_MASK                      0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_RSMIN_FIELD( rsmin ) \
    (u32)( \
    ((u32)(rsmin) << REG_LCD_ABL1_RSMIN_RSMIN_SHIFT))
#endif


/* ABL1_RSMAX */

#define REG_LCD_ABL1_RSMAX_RSMAX_SHIFT                     0
#define REG_LCD_ABL1_RSMAX_RSMAX_SIZE                      8
#define REG_LCD_ABL1_RSMAX_RSMAX_MASK                      0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_RSMAX_FIELD( rsmax ) \
    (u32)( \
    ((u32)(rsmax) << REG_LCD_ABL1_RSMAX_RSMAX_SHIFT))
#endif


/* ABL1_LMAX */

#define REG_LCD_ABL1_LMAX_LMAX_SHIFT                       0
#define REG_LCD_ABL1_LMAX_LMAX_SIZE                        10
#define REG_LCD_ABL1_LMAX_LMAX_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_LMAX_FIELD( lmax ) \
    (u32)( \
    ((u32)(lmax) << REG_LCD_ABL1_LMAX_LMAX_SHIFT))
#endif


/* ABL1_PWMCNT */

#define REG_LCD_ABL1_PWMCNT_PC_SHIFT                       16
#define REG_LCD_ABL1_PWMCNT_PC_SIZE                        3
#define REG_LCD_ABL1_PWMCNT_PC_MASK                        0x00070000

#define REG_LCD_ABL1_PWMCNT_PS_SHIFT                       12
#define REG_LCD_ABL1_PWMCNT_PS_SIZE                        4
#define REG_LCD_ABL1_PWMCNT_PS_MASK                        0x0000f000

#define REG_LCD_ABL1_PWMCNT_PD_SHIFT                       0
#define REG_LCD_ABL1_PWMCNT_PD_SIZE                        10
#define REG_LCD_ABL1_PWMCNT_PD_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_PWMCNT_FIELD( pc, ps, pd ) \
    (u32)( \
    ((u32)(pc) << REG_LCD_ABL1_PWMCNT_PC_SHIFT) | \
    ((u32)(ps) << REG_LCD_ABL1_PWMCNT_PS_SHIFT) | \
    ((u32)(pd) << REG_LCD_ABL1_PWMCNT_PD_SHIFT))
#endif


/* ABL1_PWMCNT_EIU */

#define REG_LCD_ABL1_PWMCNT_EIU_PS134_SHIFT                31
#define REG_LCD_ABL1_PWMCNT_EIU_PS134_SIZE                 1
#define REG_LCD_ABL1_PWMCNT_EIU_PS134_MASK                 0x80000000

#define REG_LCD_ABL1_PWMCNT_EIU_SD_SHIFT                   24
#define REG_LCD_ABL1_PWMCNT_EIU_SD_SIZE                    7
#define REG_LCD_ABL1_PWMCNT_EIU_SD_MASK                    0x7f000000

#define REG_LCD_ABL1_PWMCNT_EIU_PI_SHIFT                   20
#define REG_LCD_ABL1_PWMCNT_EIU_PI_SIZE                    4
#define REG_LCD_ABL1_PWMCNT_EIU_PI_MASK                    0x00f00000

#define REG_LCD_ABL1_PWMCNT_EIU_FE_SHIFT                   19
#define REG_LCD_ABL1_PWMCNT_EIU_FE_SIZE                    1
#define REG_LCD_ABL1_PWMCNT_EIU_FE_MASK                    0x00080000

#define REG_LCD_ABL1_PWMCNT_EIU_PC_SHIFT                   16
#define REG_LCD_ABL1_PWMCNT_EIU_PC_SIZE                    3
#define REG_LCD_ABL1_PWMCNT_EIU_PC_MASK                    0x00070000

#define REG_LCD_ABL1_PWMCNT_EIU_PS_SHIFT                   12
#define REG_LCD_ABL1_PWMCNT_EIU_PS_SIZE                    4
#define REG_LCD_ABL1_PWMCNT_EIU_PS_MASK                    0x0000f000

#define REG_LCD_ABL1_PWMCNT_EIU_PD_SHIFT                   0
#define REG_LCD_ABL1_PWMCNT_EIU_PD_SIZE                    10
#define REG_LCD_ABL1_PWMCNT_EIU_PD_MASK                    0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_PWMCNT_EIU_FIELD( ps134, sd, pi, fe, pc, ps, pd ) \
    (u32)( \
    ((u32)(ps134) << REG_LCD_ABL1_PWMCNT_EIU_PS134_SHIFT) | \
    ((u32)(sd) << REG_LCD_ABL1_PWMCNT_EIU_SD_SHIFT) | \
    ((u32)(pi) << REG_LCD_ABL1_PWMCNT_EIU_PI_SHIFT) | \
    ((u32)(fe) << REG_LCD_ABL1_PWMCNT_EIU_FE_SHIFT) | \
    ((u32)(pc) << REG_LCD_ABL1_PWMCNT_EIU_PC_SHIFT) | \
    ((u32)(ps) << REG_LCD_ABL1_PWMCNT_EIU_PS_SHIFT) | \
    ((u32)(pd) << REG_LCD_ABL1_PWMCNT_EIU_PD_SHIFT))
#endif


/* ABL1_HST1 */

#define REG_LCD_ABL1_HST1_IB_B_SHIFT                       16
#define REG_LCD_ABL1_HST1_IB_B_SIZE                        8
#define REG_LCD_ABL1_HST1_IB_B_MASK                        0x00ff0000

#define REG_LCD_ABL1_HST1_IB_G_SHIFT                       8
#define REG_LCD_ABL1_HST1_IB_G_SIZE                        8
#define REG_LCD_ABL1_HST1_IB_G_MASK                        0x0000ff00

#define REG_LCD_ABL1_HST1_IB_R_SHIFT                       0
#define REG_LCD_ABL1_HST1_IB_R_SIZE                        8
#define REG_LCD_ABL1_HST1_IB_R_MASK                        0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_HST1_FIELD( ib_b, ib_g, ib_r ) \
    (u32)( \
    ((u32)(ib_b) << REG_LCD_ABL1_HST1_IB_B_SHIFT) | \
    ((u32)(ib_g) << REG_LCD_ABL1_HST1_IB_G_SHIFT) | \
    ((u32)(ib_r) << REG_LCD_ABL1_HST1_IB_R_SHIFT))
#endif


/* ABL1_HST2 */

#define REG_LCD_ABL1_HST2_C_B_SHIFT                        16
#define REG_LCD_ABL1_HST2_C_B_SIZE                         8
#define REG_LCD_ABL1_HST2_C_B_MASK                         0x00ff0000

#define REG_LCD_ABL1_HST2_C_G_SHIFT                        8
#define REG_LCD_ABL1_HST2_C_G_SIZE                         8
#define REG_LCD_ABL1_HST2_C_G_MASK                         0x0000ff00

#define REG_LCD_ABL1_HST2_C_R_SHIFT                        0
#define REG_LCD_ABL1_HST2_C_R_SIZE                         8
#define REG_LCD_ABL1_HST2_C_R_MASK                         0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_HST2_FIELD( c_b, c_g, c_r ) \
    (u32)( \
    ((u32)(c_b) << REG_LCD_ABL1_HST2_C_B_SHIFT) | \
    ((u32)(c_g) << REG_LCD_ABL1_HST2_C_G_SHIFT) | \
    ((u32)(c_r) << REG_LCD_ABL1_HST2_C_R_SHIFT))
#endif


/* ABL1_DITPAT0 */

#define REG_LCD_ABL1_DITPAT0_W3_SHIFT                      14
#define REG_LCD_ABL1_DITPAT0_W3_SIZE                       2
#define REG_LCD_ABL1_DITPAT0_W3_MASK                       0x0000c000

#define REG_LCD_ABL1_DITPAT0_W2_SHIFT                      10
#define REG_LCD_ABL1_DITPAT0_W2_SIZE                       2
#define REG_LCD_ABL1_DITPAT0_W2_MASK                       0x00000c00

#define REG_LCD_ABL1_DITPAT0_W1_SHIFT                      6
#define REG_LCD_ABL1_DITPAT0_W1_SIZE                       2
#define REG_LCD_ABL1_DITPAT0_W1_MASK                       0x000000c0

#define REG_LCD_ABL1_DITPAT0_W0_SHIFT                      2
#define REG_LCD_ABL1_DITPAT0_W0_SIZE                       2
#define REG_LCD_ABL1_DITPAT0_W0_MASK                       0x0000000c

#ifndef SDK_ASM
#define REG_LCD_ABL1_DITPAT0_FIELD( w3, w2, w1, w0 ) \
    (u32)( \
    ((u32)(w3) << REG_LCD_ABL1_DITPAT0_W3_SHIFT) | \
    ((u32)(w2) << REG_LCD_ABL1_DITPAT0_W2_SHIFT) | \
    ((u32)(w1) << REG_LCD_ABL1_DITPAT0_W1_SHIFT) | \
    ((u32)(w0) << REG_LCD_ABL1_DITPAT0_W0_SHIFT))
#endif


/* ABL1_DITPAT1 */

#define REG_LCD_ABL1_DITPAT1_W3_SHIFT                      14
#define REG_LCD_ABL1_DITPAT1_W3_SIZE                       2
#define REG_LCD_ABL1_DITPAT1_W3_MASK                       0x0000c000

#define REG_LCD_ABL1_DITPAT1_W2_SHIFT                      10
#define REG_LCD_ABL1_DITPAT1_W2_SIZE                       2
#define REG_LCD_ABL1_DITPAT1_W2_MASK                       0x00000c00

#define REG_LCD_ABL1_DITPAT1_W1_SHIFT                      6
#define REG_LCD_ABL1_DITPAT1_W1_SIZE                       2
#define REG_LCD_ABL1_DITPAT1_W1_MASK                       0x000000c0

#define REG_LCD_ABL1_DITPAT1_W0_SHIFT                      2
#define REG_LCD_ABL1_DITPAT1_W0_SIZE                       2
#define REG_LCD_ABL1_DITPAT1_W0_MASK                       0x0000000c

#ifndef SDK_ASM
#define REG_LCD_ABL1_DITPAT1_FIELD( w3, w2, w1, w0 ) \
    (u32)( \
    ((u32)(w3) << REG_LCD_ABL1_DITPAT1_W3_SHIFT) | \
    ((u32)(w2) << REG_LCD_ABL1_DITPAT1_W2_SHIFT) | \
    ((u32)(w1) << REG_LCD_ABL1_DITPAT1_W1_SHIFT) | \
    ((u32)(w0) << REG_LCD_ABL1_DITPAT1_W0_SHIFT))
#endif


/* ABL1_RSLUT0 */

#define REG_LCD_ABL1_RSLUT0_RSLUT_SHIFT                    0
#define REG_LCD_ABL1_RSLUT0_RSLUT_SIZE                     8
#define REG_LCD_ABL1_RSLUT0_RSLUT_MASK                     0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_RSLUT0_FIELD( rslut ) \
    (u32)( \
    ((u32)(rslut) << REG_LCD_ABL1_RSLUT0_RSLUT_SHIFT))
#endif


/* ABL1_CMAX */

#define REG_LCD_ABL1_CMAX_CMAX_SHIFT                       0
#define REG_LCD_ABL1_CMAX_CMAX_SIZE                        8
#define REG_LCD_ABL1_CMAX_CMAX_MASK                        0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_CMAX_FIELD( cmax ) \
    (u32)( \
    ((u32)(cmax) << REG_LCD_ABL1_CMAX_CMAX_SHIFT))
#endif


/* ABL1_CGTH */

#define REG_LCD_ABL1_CGTH_CGTH_SHIFT                       0
#define REG_LCD_ABL1_CGTH_CGTH_SIZE                        8
#define REG_LCD_ABL1_CGTH_CGTH_MASK                        0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_CGTH_FIELD( cgth ) \
    (u32)( \
    ((u32)(cgth) << REG_LCD_ABL1_CGTH_CGTH_SHIFT))
#endif


/* ABL1_CRS */

#define REG_LCD_ABL1_CRS_CRS_SHIFT                         0
#define REG_LCD_ABL1_CRS_CRS_SIZE                          8
#define REG_LCD_ABL1_CRS_CRS_MASK                          0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_CRS_FIELD( crs ) \
    (u32)( \
    ((u32)(crs) << REG_LCD_ABL1_CRS_CRS_SHIFT))
#endif


/* ABL1_ADJCOE0 */

#define REG_LCD_ABL1_ADJCOE0_C_B_SHIFT                     16
#define REG_LCD_ABL1_ADJCOE0_C_B_SIZE                      8
#define REG_LCD_ABL1_ADJCOE0_C_B_MASK                      0x00ff0000

#define REG_LCD_ABL1_ADJCOE0_C_G_SHIFT                     8
#define REG_LCD_ABL1_ADJCOE0_C_G_SIZE                      8
#define REG_LCD_ABL1_ADJCOE0_C_G_MASK                      0x0000ff00

#define REG_LCD_ABL1_ADJCOE0_C_R_SHIFT                     0
#define REG_LCD_ABL1_ADJCOE0_C_R_SIZE                      8
#define REG_LCD_ABL1_ADJCOE0_C_R_MASK                      0x000000ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_ADJCOE0_FIELD( c_b, c_g, c_r ) \
    (u32)( \
    ((u32)(c_b) << REG_LCD_ABL1_ADJCOE0_C_B_SHIFT) | \
    ((u32)(c_g) << REG_LCD_ABL1_ADJCOE0_C_G_SHIFT) | \
    ((u32)(c_r) << REG_LCD_ABL1_ADJCOE0_C_R_SHIFT))
#endif


/* ABL1_RDLUT0 */

#define REG_LCD_ABL1_RDLUT0_RDLUT_SHIFT                    0
#define REG_LCD_ABL1_RDLUT0_RDLUT_SIZE                     10
#define REG_LCD_ABL1_RDLUT0_RDLUT_MASK                     0x000003ff

#ifndef SDK_ASM
#define REG_LCD_ABL1_RDLUT0_FIELD( rdlut ) \
    (u32)( \
    ((u32)(rdlut) << REG_LCD_ABL1_RDLUT0_RDLUT_SHIFT))
#endif


/* PDC0_H_COUNT_SIZE */

#define REG_LCD_PDC0_H_COUNT_SIZE_SZ_SHIFT                 0
#define REG_LCD_PDC0_H_COUNT_SIZE_SZ_SIZE                  12
#define REG_LCD_PDC0_H_COUNT_SIZE_SZ_MASK                  0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_H_COUNT_SIZE_FIELD( sz ) \
    (u32)( \
    ((u32)(sz) << REG_LCD_PDC0_H_COUNT_SIZE_SZ_SHIFT))
#endif


/* PDC0_H_DISP_S */

#define REG_LCD_PDC0_H_DISP_S_S_SHIFT                      0
#define REG_LCD_PDC0_H_DISP_S_S_SIZE                       12
#define REG_LCD_PDC0_H_DISP_S_S_MASK                       0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_H_DISP_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_H_DISP_S_S_SHIFT))
#endif


/* PDC0_H_RBORDER_S */

#define REG_LCD_PDC0_H_RBORDER_S_S_SHIFT                   0
#define REG_LCD_PDC0_H_RBORDER_S_S_SIZE                    12
#define REG_LCD_PDC0_H_RBORDER_S_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_H_RBORDER_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_H_RBORDER_S_S_SHIFT))
#endif


/* PDC0_H_BLANK_S */

#define REG_LCD_PDC0_H_BLANK_S_S_SHIFT                     0
#define REG_LCD_PDC0_H_BLANK_S_S_SIZE                      12
#define REG_LCD_PDC0_H_BLANK_S_S_MASK                      0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_H_BLANK_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_H_BLANK_S_S_SHIFT))
#endif


/* PDC0_H_SYNC_S */

#define REG_LCD_PDC0_H_SYNC_S_S_SHIFT                      0
#define REG_LCD_PDC0_H_SYNC_S_S_SIZE                       12
#define REG_LCD_PDC0_H_SYNC_S_S_MASK                       0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_H_SYNC_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_H_SYNC_S_S_SHIFT))
#endif


/* PDC0_H_BPORTCH_S */

#define REG_LCD_PDC0_H_BPORTCH_S_S_SHIFT                   0
#define REG_LCD_PDC0_H_BPORTCH_S_S_SIZE                    12
#define REG_LCD_PDC0_H_BPORTCH_S_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_H_BPORTCH_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_H_BPORTCH_S_S_SHIFT))
#endif


/* PDC0_H_LBORDER_S */

#define REG_LCD_PDC0_H_LBORDER_S_S_SHIFT                   0
#define REG_LCD_PDC0_H_LBORDER_S_S_SIZE                    12
#define REG_LCD_PDC0_H_LBORDER_S_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_H_LBORDER_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_H_LBORDER_S_S_SHIFT))
#endif


/* PDC0_H_INTR_POS */

#define REG_LCD_PDC0_H_INTR_POS_E_SHIFT                    16
#define REG_LCD_PDC0_H_INTR_POS_E_SIZE                     12
#define REG_LCD_PDC0_H_INTR_POS_E_MASK                     0x0fff0000

#define REG_LCD_PDC0_H_INTR_POS_S_SHIFT                    0
#define REG_LCD_PDC0_H_INTR_POS_S_SIZE                     12
#define REG_LCD_PDC0_H_INTR_POS_S_MASK                     0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_H_INTR_POS_FIELD( e, s ) \
    (u32)( \
    ((u32)(e) << REG_LCD_PDC0_H_INTR_POS_E_SHIFT) | \
    ((u32)(s) << REG_LCD_PDC0_H_INTR_POS_S_SHIFT))
#endif


/* PDC0_H_DMA_POS */

#define REG_LCD_PDC0_H_DMA_POS_E_SHIFT                     16
#define REG_LCD_PDC0_H_DMA_POS_E_SIZE                      12
#define REG_LCD_PDC0_H_DMA_POS_E_MASK                      0x0fff0000

#define REG_LCD_PDC0_H_DMA_POS_S_SHIFT                     0
#define REG_LCD_PDC0_H_DMA_POS_S_SIZE                      12
#define REG_LCD_PDC0_H_DMA_POS_S_MASK                      0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_H_DMA_POS_FIELD( e, s ) \
    (u32)( \
    ((u32)(e) << REG_LCD_PDC0_H_DMA_POS_E_SHIFT) | \
    ((u32)(s) << REG_LCD_PDC0_H_DMA_POS_S_SHIFT))
#endif


/* PDC0_V_COUNT_SIZE */

#define REG_LCD_PDC0_V_COUNT_SIZE_SZ_SHIFT                 0
#define REG_LCD_PDC0_V_COUNT_SIZE_SZ_SIZE                  12
#define REG_LCD_PDC0_V_COUNT_SIZE_SZ_MASK                  0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_V_COUNT_SIZE_FIELD( sz ) \
    (u32)( \
    ((u32)(sz) << REG_LCD_PDC0_V_COUNT_SIZE_SZ_SHIFT))
#endif


/* PDC0_V_DISP_S */

#define REG_LCD_PDC0_V_DISP_S_S_SHIFT                      0
#define REG_LCD_PDC0_V_DISP_S_S_SIZE                       12
#define REG_LCD_PDC0_V_DISP_S_S_MASK                       0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_V_DISP_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_V_DISP_S_S_SHIFT))
#endif


/* PDC0_V_BBORDER_S */

#define REG_LCD_PDC0_V_BBORDER_S_S_SHIFT                   0
#define REG_LCD_PDC0_V_BBORDER_S_S_SIZE                    12
#define REG_LCD_PDC0_V_BBORDER_S_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_V_BBORDER_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_V_BBORDER_S_S_SHIFT))
#endif


/* PDC0_V_BLANK_S */

#define REG_LCD_PDC0_V_BLANK_S_S_SHIFT                     0
#define REG_LCD_PDC0_V_BLANK_S_S_SIZE                      12
#define REG_LCD_PDC0_V_BLANK_S_S_MASK                      0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_V_BLANK_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_V_BLANK_S_S_SHIFT))
#endif


/* PDC0_V_SYNC_S */

#define REG_LCD_PDC0_V_SYNC_S_S_SHIFT                      0
#define REG_LCD_PDC0_V_SYNC_S_S_SIZE                       12
#define REG_LCD_PDC0_V_SYNC_S_S_MASK                       0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_V_SYNC_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_V_SYNC_S_S_SHIFT))
#endif


/* PDC0_V_BPORTCH_S */

#define REG_LCD_PDC0_V_BPORTCH_S_S_SHIFT                   0
#define REG_LCD_PDC0_V_BPORTCH_S_S_SIZE                    12
#define REG_LCD_PDC0_V_BPORTCH_S_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_V_BPORTCH_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_V_BPORTCH_S_S_SHIFT))
#endif


/* PDC0_V_TBORDER_S */

#define REG_LCD_PDC0_V_TBORDER_S_S_SHIFT                   0
#define REG_LCD_PDC0_V_TBORDER_S_S_SIZE                    12
#define REG_LCD_PDC0_V_TBORDER_S_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_V_TBORDER_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_V_TBORDER_S_S_SHIFT))
#endif


/* PDC0_V_INTR_POS */

#define REG_LCD_PDC0_V_INTR_POS_E_SHIFT                    16
#define REG_LCD_PDC0_V_INTR_POS_E_SIZE                     12
#define REG_LCD_PDC0_V_INTR_POS_E_MASK                     0x0fff0000

#define REG_LCD_PDC0_V_INTR_POS_S_SHIFT                    0
#define REG_LCD_PDC0_V_INTR_POS_S_SIZE                     12
#define REG_LCD_PDC0_V_INTR_POS_S_MASK                     0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_V_INTR_POS_FIELD( e, s ) \
    (u32)( \
    ((u32)(e) << REG_LCD_PDC0_V_INTR_POS_E_SHIFT) | \
    ((u32)(s) << REG_LCD_PDC0_V_INTR_POS_S_SHIFT))
#endif


/* PDC0_V_INC_H_POS */

#define REG_LCD_PDC0_V_INC_H_POS_S_SHIFT                   0
#define REG_LCD_PDC0_V_INC_H_POS_S_SIZE                    12
#define REG_LCD_PDC0_V_INC_H_POS_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_V_INC_H_POS_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC0_V_INC_H_POS_S_SHIFT))
#endif


/* PDC0_SIGNAL_POL */

#define REG_LCD_PDC0_SIGNAL_POL_V_SHIFT                    4
#define REG_LCD_PDC0_SIGNAL_POL_V_SIZE                     1
#define REG_LCD_PDC0_SIGNAL_POL_V_MASK                     0x00000010

#define REG_LCD_PDC0_SIGNAL_POL_H_SHIFT                    0
#define REG_LCD_PDC0_SIGNAL_POL_H_SIZE                     1
#define REG_LCD_PDC0_SIGNAL_POL_H_MASK                     0x00000001

#ifndef SDK_ASM
#define REG_LCD_PDC0_SIGNAL_POL_FIELD( v, h ) \
    (u32)( \
    ((u32)(v) << REG_LCD_PDC0_SIGNAL_POL_V_SHIFT) | \
    ((u32)(h) << REG_LCD_PDC0_SIGNAL_POL_H_SHIFT))
#endif


/* PDC0_BORDER_COL */

#define REG_LCD_PDC0_BORDER_COL_B_SHIFT                    16
#define REG_LCD_PDC0_BORDER_COL_B_SIZE                     8
#define REG_LCD_PDC0_BORDER_COL_B_MASK                     0x00ff0000

#define REG_LCD_PDC0_BORDER_COL_G_SHIFT                    8
#define REG_LCD_PDC0_BORDER_COL_G_SIZE                     8
#define REG_LCD_PDC0_BORDER_COL_G_MASK                     0x0000ff00

#define REG_LCD_PDC0_BORDER_COL_R_SHIFT                    0
#define REG_LCD_PDC0_BORDER_COL_R_SIZE                     8
#define REG_LCD_PDC0_BORDER_COL_R_MASK                     0x000000ff

#ifndef SDK_ASM
#define REG_LCD_PDC0_BORDER_COL_FIELD( b, g, r ) \
    (u32)( \
    ((u32)(b) << REG_LCD_PDC0_BORDER_COL_B_SHIFT) | \
    ((u32)(g) << REG_LCD_PDC0_BORDER_COL_G_SHIFT) | \
    ((u32)(r) << REG_LCD_PDC0_BORDER_COL_R_SHIFT))
#endif


/* PDC0_H_COUNT */

#define REG_LCD_PDC0_H_COUNT_COUNT_SHIFT                   0
#define REG_LCD_PDC0_H_COUNT_COUNT_SIZE                    12
#define REG_LCD_PDC0_H_COUNT_COUNT_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_H_COUNT_FIELD( count ) \
    (u32)( \
    ((u32)(count) << REG_LCD_PDC0_H_COUNT_COUNT_SHIFT))
#endif


/* PDC0_V_COUNT */

#define REG_LCD_PDC0_V_COUNT_COUNT_SHIFT                   0
#define REG_LCD_PDC0_V_COUNT_COUNT_SIZE                    12
#define REG_LCD_PDC0_V_COUNT_COUNT_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_V_COUNT_FIELD( count ) \
    (u32)( \
    ((u32)(count) << REG_LCD_PDC0_V_COUNT_COUNT_SHIFT))
#endif


/* PDC0_OUT_SIZE */

#define REG_LCD_PDC0_OUT_SIZE_V_SHIFT                      16
#define REG_LCD_PDC0_OUT_SIZE_V_SIZE                       12
#define REG_LCD_PDC0_OUT_SIZE_V_MASK                       0x0fff0000

#define REG_LCD_PDC0_OUT_SIZE_H_SHIFT                      0
#define REG_LCD_PDC0_OUT_SIZE_H_SIZE                       12
#define REG_LCD_PDC0_OUT_SIZE_H_MASK                       0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_OUT_SIZE_FIELD( v, h ) \
    (u32)( \
    ((u32)(v) << REG_LCD_PDC0_OUT_SIZE_V_SHIFT) | \
    ((u32)(h) << REG_LCD_PDC0_OUT_SIZE_H_SHIFT))
#endif


/* PDC0_PIC_BORDER_H */

#define REG_LCD_PDC0_PIC_BORDER_H_E_SHIFT                  16
#define REG_LCD_PDC0_PIC_BORDER_H_E_SIZE                   12
#define REG_LCD_PDC0_PIC_BORDER_H_E_MASK                   0x0fff0000

#define REG_LCD_PDC0_PIC_BORDER_H_S_SHIFT                  0
#define REG_LCD_PDC0_PIC_BORDER_H_S_SIZE                   12
#define REG_LCD_PDC0_PIC_BORDER_H_S_MASK                   0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_PIC_BORDER_H_FIELD( e, s ) \
    (u32)( \
    ((u32)(e) << REG_LCD_PDC0_PIC_BORDER_H_E_SHIFT) | \
    ((u32)(s) << REG_LCD_PDC0_PIC_BORDER_H_S_SHIFT))
#endif


/* PDC0_PIC_BORDER_V */

#define REG_LCD_PDC0_PIC_BORDER_V_E_SHIFT                  16
#define REG_LCD_PDC0_PIC_BORDER_V_E_SIZE                   12
#define REG_LCD_PDC0_PIC_BORDER_V_E_MASK                   0x0fff0000

#define REG_LCD_PDC0_PIC_BORDER_V_S_SHIFT                  0
#define REG_LCD_PDC0_PIC_BORDER_V_S_SIZE                   12
#define REG_LCD_PDC0_PIC_BORDER_V_S_MASK                   0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_PIC_BORDER_V_FIELD( e, s ) \
    (u32)( \
    ((u32)(e) << REG_LCD_PDC0_PIC_BORDER_V_E_SHIFT) | \
    ((u32)(s) << REG_LCD_PDC0_PIC_BORDER_V_S_SHIFT))
#endif


/* PDC0_FB0_ADR */

#define REG_LCD_PDC0_FB0_ADR_ADR_SHIFT                     4
#define REG_LCD_PDC0_FB0_ADR_ADR_SIZE                      28
#define REG_LCD_PDC0_FB0_ADR_ADR_MASK                      0xfffffff0

#ifndef SDK_ASM
#define REG_LCD_PDC0_FB0_ADR_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_LCD_PDC0_FB0_ADR_ADR_SHIFT))
#endif


/* PDC0_FB1_ADR */

#define REG_LCD_PDC0_FB1_ADR_ADR_SHIFT                     4
#define REG_LCD_PDC0_FB1_ADR_ADR_SIZE                      28
#define REG_LCD_PDC0_FB1_ADR_ADR_MASK                      0xfffffff0

#ifndef SDK_ASM
#define REG_LCD_PDC0_FB1_ADR_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_LCD_PDC0_FB1_ADR_ADR_SHIFT))
#endif


/* PDC0_MODE */

#define REG_LCD_PDC0_MODE_INTERVAL_SHIFT                   16
#define REG_LCD_PDC0_MODE_INTERVAL_SIZE                    16
#define REG_LCD_PDC0_MODE_INTERVAL_MASK                    0xffff0000

#define REG_LCD_PDC0_MODE_BLEN_SHIFT                       8
#define REG_LCD_PDC0_MODE_BLEN_SIZE                        2
#define REG_LCD_PDC0_MODE_BLEN_MASK                        0x00000300

#define REG_LCD_PDC0_MODE_CLK_MODE_SHIFT                   6
#define REG_LCD_PDC0_MODE_CLK_MODE_SIZE                    1
#define REG_LCD_PDC0_MODE_CLK_MODE_MASK                    0x00000040

#define REG_LCD_PDC0_MODE_OUT_MODE_SHIFT                   4
#define REG_LCD_PDC0_MODE_OUT_MODE_SIZE                    2
#define REG_LCD_PDC0_MODE_OUT_MODE_MASK                    0x00000030

#define REG_LCD_PDC0_MODE_FMT_SHIFT                        0
#define REG_LCD_PDC0_MODE_FMT_SIZE                         3
#define REG_LCD_PDC0_MODE_FMT_MASK                         0x00000007

#ifndef SDK_ASM
#define REG_LCD_PDC0_MODE_FIELD( interval, blen, clk_mode, out_mode, fmt ) \
    (u32)( \
    ((u32)(interval) << REG_LCD_PDC0_MODE_INTERVAL_SHIFT) | \
    ((u32)(blen) << REG_LCD_PDC0_MODE_BLEN_SHIFT) | \
    ((u32)(clk_mode) << REG_LCD_PDC0_MODE_CLK_MODE_SHIFT) | \
    ((u32)(out_mode) << REG_LCD_PDC0_MODE_OUT_MODE_SHIFT) | \
    ((u32)(fmt) << REG_LCD_PDC0_MODE_FMT_SHIFT))
#endif


/* PDC0_START */

#define REG_LCD_PDC0_START_O_E_SHIFT                       16
#define REG_LCD_PDC0_START_O_E_SIZE                        1
#define REG_LCD_PDC0_START_O_E_MASK                        0x00010000

#define REG_LCD_PDC0_START_IM_ERR_SHIFT                    10
#define REG_LCD_PDC0_START_IM_ERR_SIZE                     1
#define REG_LCD_PDC0_START_IM_ERR_MASK                     0x00000400

#define REG_LCD_PDC0_START_IM_V_SHIFT                      9
#define REG_LCD_PDC0_START_IM_V_SIZE                       1
#define REG_LCD_PDC0_START_IM_V_MASK                       0x00000200

#define REG_LCD_PDC0_START_IM_H_SHIFT                      8
#define REG_LCD_PDC0_START_IM_H_SIZE                       1
#define REG_LCD_PDC0_START_IM_H_MASK                       0x00000100

#define REG_LCD_PDC0_START_E_SHIFT                         0
#define REG_LCD_PDC0_START_E_SIZE                          1
#define REG_LCD_PDC0_START_E_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_LCD_PDC0_START_FIELD( o_e, im_err, im_v, im_h, e ) \
    (u32)( \
    ((u32)(o_e) << REG_LCD_PDC0_START_O_E_SHIFT) | \
    ((u32)(im_err) << REG_LCD_PDC0_START_IM_ERR_SHIFT) | \
    ((u32)(im_v) << REG_LCD_PDC0_START_IM_V_SHIFT) | \
    ((u32)(im_h) << REG_LCD_PDC0_START_IM_H_SHIFT) | \
    ((u32)(e) << REG_LCD_PDC0_START_E_SHIFT))
#endif


/* PDC0_SWAP */

#define REG_LCD_PDC0_SWAP_ICLR_ERR_SHIFT                   18
#define REG_LCD_PDC0_SWAP_ICLR_ERR_SIZE                    1
#define REG_LCD_PDC0_SWAP_ICLR_ERR_MASK                    0x00040000

#define REG_LCD_PDC0_SWAP_ICLR_V_SHIFT                     17
#define REG_LCD_PDC0_SWAP_ICLR_V_SIZE                      1
#define REG_LCD_PDC0_SWAP_ICLR_V_MASK                      0x00020000

#define REG_LCD_PDC0_SWAP_ICLR_H_SHIFT                     16
#define REG_LCD_PDC0_SWAP_ICLR_H_SIZE                      1
#define REG_LCD_PDC0_SWAP_ICLR_H_MASK                      0x00010000

#define REG_LCD_PDC0_SWAP_RST_FIFO_SHIFT                   8
#define REG_LCD_PDC0_SWAP_RST_FIFO_SIZE                    1
#define REG_LCD_PDC0_SWAP_RST_FIFO_MASK                    0x00000100

#define REG_LCD_PDC0_SWAP_AT_SWAP_SHIFT                    4
#define REG_LCD_PDC0_SWAP_AT_SWAP_SIZE                     1
#define REG_LCD_PDC0_SWAP_AT_SWAP_MASK                     0x00000010

#define REG_LCD_PDC0_SWAP_NEXT_SHIFT                       0
#define REG_LCD_PDC0_SWAP_NEXT_SIZE                        1
#define REG_LCD_PDC0_SWAP_NEXT_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_LCD_PDC0_SWAP_FIELD( iclr_err, iclr_v, iclr_h, rst_fifo, at_swap, next ) \
    (u32)( \
    ((u32)(iclr_err) << REG_LCD_PDC0_SWAP_ICLR_ERR_SHIFT) | \
    ((u32)(iclr_v) << REG_LCD_PDC0_SWAP_ICLR_V_SHIFT) | \
    ((u32)(iclr_h) << REG_LCD_PDC0_SWAP_ICLR_H_SHIFT) | \
    ((u32)(rst_fifo) << REG_LCD_PDC0_SWAP_RST_FIFO_SHIFT) | \
    ((u32)(at_swap) << REG_LCD_PDC0_SWAP_AT_SWAP_SHIFT) | \
    ((u32)(next) << REG_LCD_PDC0_SWAP_NEXT_SHIFT))
#endif


/* PDC0_STAT */

#define REG_LCD_PDC0_STAT_ERR_SHIFT                        15
#define REG_LCD_PDC0_STAT_ERR_SIZE                         1
#define REG_LCD_PDC0_STAT_ERR_MASK                         0x00008000

#define REG_LCD_PDC0_STAT_H_ACTIVE_SHIFT                   14
#define REG_LCD_PDC0_STAT_H_ACTIVE_SIZE                    1
#define REG_LCD_PDC0_STAT_H_ACTIVE_MASK                    0x00004000

#define REG_LCD_PDC0_STAT_H_BLANK_SHIFT                    13
#define REG_LCD_PDC0_STAT_H_BLANK_SIZE                     1
#define REG_LCD_PDC0_STAT_H_BLANK_MASK                     0x00002000

#define REG_LCD_PDC0_STAT_H_SYNC_SHIFT                     12
#define REG_LCD_PDC0_STAT_H_SYNC_SIZE                      1
#define REG_LCD_PDC0_STAT_H_SYNC_MASK                      0x00001000

#define REG_LCD_PDC0_STAT_V_ACTIVE_SHIFT                   10
#define REG_LCD_PDC0_STAT_V_ACTIVE_SIZE                    1
#define REG_LCD_PDC0_STAT_V_ACTIVE_MASK                    0x00000400

#define REG_LCD_PDC0_STAT_V_BLANK_SHIFT                    9
#define REG_LCD_PDC0_STAT_V_BLANK_SIZE                     1
#define REG_LCD_PDC0_STAT_V_BLANK_MASK                     0x00000200

#define REG_LCD_PDC0_STAT_V_SYNC_SHIFT                     8
#define REG_LCD_PDC0_STAT_V_SYNC_SIZE                      1
#define REG_LCD_PDC0_STAT_V_SYNC_MASK                      0x00000100

#define REG_LCD_PDC0_STAT_CUR_BANK_SHIFT                   4
#define REG_LCD_PDC0_STAT_CUR_BANK_SIZE                    1
#define REG_LCD_PDC0_STAT_CUR_BANK_MASK                    0x00000010

#define REG_LCD_PDC0_STAT_H_INT_SHIFT                      1
#define REG_LCD_PDC0_STAT_H_INT_SIZE                       1
#define REG_LCD_PDC0_STAT_H_INT_MASK                       0x00000002

#define REG_LCD_PDC0_STAT_V_INT_SHIFT                      0
#define REG_LCD_PDC0_STAT_V_INT_SIZE                       1
#define REG_LCD_PDC0_STAT_V_INT_MASK                       0x00000001

#ifndef SDK_ASM
#define REG_LCD_PDC0_STAT_FIELD( err, h_active, h_blank, h_sync, v_active, v_blank, v_sync, cur_bank, h_int, v_int ) \
    (u32)( \
    ((u32)(err) << REG_LCD_PDC0_STAT_ERR_SHIFT) | \
    ((u32)(h_active) << REG_LCD_PDC0_STAT_H_ACTIVE_SHIFT) | \
    ((u32)(h_blank) << REG_LCD_PDC0_STAT_H_BLANK_SHIFT) | \
    ((u32)(h_sync) << REG_LCD_PDC0_STAT_H_SYNC_SHIFT) | \
    ((u32)(v_active) << REG_LCD_PDC0_STAT_V_ACTIVE_SHIFT) | \
    ((u32)(v_blank) << REG_LCD_PDC0_STAT_V_BLANK_SHIFT) | \
    ((u32)(v_sync) << REG_LCD_PDC0_STAT_V_SYNC_SHIFT) | \
    ((u32)(cur_bank) << REG_LCD_PDC0_STAT_CUR_BANK_SHIFT) | \
    ((u32)(h_int) << REG_LCD_PDC0_STAT_H_INT_SHIFT) | \
    ((u32)(v_int) << REG_LCD_PDC0_STAT_V_INT_SHIFT))
#endif


/* PDC0_GTBL_ADR */

#define REG_LCD_PDC0_GTBL_ADR_ADR_SHIFT                    0
#define REG_LCD_PDC0_GTBL_ADR_ADR_SIZE                     8
#define REG_LCD_PDC0_GTBL_ADR_ADR_MASK                     0x000000ff

#ifndef SDK_ASM
#define REG_LCD_PDC0_GTBL_ADR_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_LCD_PDC0_GTBL_ADR_ADR_SHIFT))
#endif


/* PDC0_GTBL_DATA */

#define REG_LCD_PDC0_GTBL_DATA_B_SHIFT                     16
#define REG_LCD_PDC0_GTBL_DATA_B_SIZE                      8
#define REG_LCD_PDC0_GTBL_DATA_B_MASK                      0x00ff0000

#define REG_LCD_PDC0_GTBL_DATA_G_SHIFT                     8
#define REG_LCD_PDC0_GTBL_DATA_G_SIZE                      8
#define REG_LCD_PDC0_GTBL_DATA_G_MASK                      0x0000ff00

#define REG_LCD_PDC0_GTBL_DATA_R_SHIFT                     0
#define REG_LCD_PDC0_GTBL_DATA_R_SIZE                      8
#define REG_LCD_PDC0_GTBL_DATA_R_MASK                      0x000000ff

#ifndef SDK_ASM
#define REG_LCD_PDC0_GTBL_DATA_FIELD( b, g, r ) \
    (u32)( \
    ((u32)(b) << REG_LCD_PDC0_GTBL_DATA_B_SHIFT) | \
    ((u32)(g) << REG_LCD_PDC0_GTBL_DATA_G_SHIFT) | \
    ((u32)(r) << REG_LCD_PDC0_GTBL_DATA_R_SHIFT))
#endif


/* PDC0_FB_SIZE */

/* PDC0_FB0_B_ADR */

#define REG_LCD_PDC0_FB0_B_ADR_ADR_SHIFT                   4
#define REG_LCD_PDC0_FB0_B_ADR_ADR_SIZE                    28
#define REG_LCD_PDC0_FB0_B_ADR_ADR_MASK                    0xfffffff0

#ifndef SDK_ASM
#define REG_LCD_PDC0_FB0_B_ADR_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_LCD_PDC0_FB0_B_ADR_ADR_SHIFT))
#endif


/* PDC0_FB1_B_ADR */

#define REG_LCD_PDC0_FB1_B_ADR_ADR_SHIFT                   4
#define REG_LCD_PDC0_FB1_B_ADR_ADR_SIZE                    28
#define REG_LCD_PDC0_FB1_B_ADR_ADR_MASK                    0xfffffff0

#ifndef SDK_ASM
#define REG_LCD_PDC0_FB1_B_ADR_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_LCD_PDC0_FB1_B_ADR_ADR_SHIFT))
#endif


/* PDC0_UPDATE */

#define REG_LCD_PDC0_UPDATE_V_COUNT_SHIFT                  16
#define REG_LCD_PDC0_UPDATE_V_COUNT_SIZE                   12
#define REG_LCD_PDC0_UPDATE_V_COUNT_MASK                   0x0fff0000

#define REG_LCD_PDC0_UPDATE_H_COUNT_SHIFT                  0
#define REG_LCD_PDC0_UPDATE_H_COUNT_SIZE                   12
#define REG_LCD_PDC0_UPDATE_H_COUNT_MASK                   0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC0_UPDATE_FIELD( v_count, h_count ) \
    (u32)( \
    ((u32)(v_count) << REG_LCD_PDC0_UPDATE_V_COUNT_SHIFT) | \
    ((u32)(h_count) << REG_LCD_PDC0_UPDATE_H_COUNT_SHIFT))
#endif


/* PDC1_H_COUNT_SIZE */

#define REG_LCD_PDC1_H_COUNT_SIZE_SZ_SHIFT                 0
#define REG_LCD_PDC1_H_COUNT_SIZE_SZ_SIZE                  12
#define REG_LCD_PDC1_H_COUNT_SIZE_SZ_MASK                  0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_H_COUNT_SIZE_FIELD( sz ) \
    (u32)( \
    ((u32)(sz) << REG_LCD_PDC1_H_COUNT_SIZE_SZ_SHIFT))
#endif


/* PDC1_H_DISP_S */

#define REG_LCD_PDC1_H_DISP_S_S_SHIFT                      0
#define REG_LCD_PDC1_H_DISP_S_S_SIZE                       12
#define REG_LCD_PDC1_H_DISP_S_S_MASK                       0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_H_DISP_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_H_DISP_S_S_SHIFT))
#endif


/* PDC1_H_RBORDER_S */

#define REG_LCD_PDC1_H_RBORDER_S_S_SHIFT                   0
#define REG_LCD_PDC1_H_RBORDER_S_S_SIZE                    12
#define REG_LCD_PDC1_H_RBORDER_S_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_H_RBORDER_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_H_RBORDER_S_S_SHIFT))
#endif


/* PDC1_H_BLANK_S */

#define REG_LCD_PDC1_H_BLANK_S_S_SHIFT                     0
#define REG_LCD_PDC1_H_BLANK_S_S_SIZE                      12
#define REG_LCD_PDC1_H_BLANK_S_S_MASK                      0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_H_BLANK_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_H_BLANK_S_S_SHIFT))
#endif


/* PDC1_H_SYNC_S */

#define REG_LCD_PDC1_H_SYNC_S_S_SHIFT                      0
#define REG_LCD_PDC1_H_SYNC_S_S_SIZE                       12
#define REG_LCD_PDC1_H_SYNC_S_S_MASK                       0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_H_SYNC_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_H_SYNC_S_S_SHIFT))
#endif


/* PDC1_H_BPORTCH_S */

#define REG_LCD_PDC1_H_BPORTCH_S_S_SHIFT                   0
#define REG_LCD_PDC1_H_BPORTCH_S_S_SIZE                    12
#define REG_LCD_PDC1_H_BPORTCH_S_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_H_BPORTCH_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_H_BPORTCH_S_S_SHIFT))
#endif


/* PDC1_H_LBORDER_S */

#define REG_LCD_PDC1_H_LBORDER_S_S_SHIFT                   0
#define REG_LCD_PDC1_H_LBORDER_S_S_SIZE                    12
#define REG_LCD_PDC1_H_LBORDER_S_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_H_LBORDER_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_H_LBORDER_S_S_SHIFT))
#endif


/* PDC1_H_INTR_POS */

#define REG_LCD_PDC1_H_INTR_POS_E_SHIFT                    16
#define REG_LCD_PDC1_H_INTR_POS_E_SIZE                     12
#define REG_LCD_PDC1_H_INTR_POS_E_MASK                     0x0fff0000

#define REG_LCD_PDC1_H_INTR_POS_S_SHIFT                    0
#define REG_LCD_PDC1_H_INTR_POS_S_SIZE                     12
#define REG_LCD_PDC1_H_INTR_POS_S_MASK                     0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_H_INTR_POS_FIELD( e, s ) \
    (u32)( \
    ((u32)(e) << REG_LCD_PDC1_H_INTR_POS_E_SHIFT) | \
    ((u32)(s) << REG_LCD_PDC1_H_INTR_POS_S_SHIFT))
#endif


/* PDC1_H_DMA_POS */

#define REG_LCD_PDC1_H_DMA_POS_E_SHIFT                     16
#define REG_LCD_PDC1_H_DMA_POS_E_SIZE                      12
#define REG_LCD_PDC1_H_DMA_POS_E_MASK                      0x0fff0000

#define REG_LCD_PDC1_H_DMA_POS_S_SHIFT                     0
#define REG_LCD_PDC1_H_DMA_POS_S_SIZE                      12
#define REG_LCD_PDC1_H_DMA_POS_S_MASK                      0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_H_DMA_POS_FIELD( e, s ) \
    (u32)( \
    ((u32)(e) << REG_LCD_PDC1_H_DMA_POS_E_SHIFT) | \
    ((u32)(s) << REG_LCD_PDC1_H_DMA_POS_S_SHIFT))
#endif


/* PDC1_V_COUNT_SIZE */

#define REG_LCD_PDC1_V_COUNT_SIZE_SZ_SHIFT                 0
#define REG_LCD_PDC1_V_COUNT_SIZE_SZ_SIZE                  12
#define REG_LCD_PDC1_V_COUNT_SIZE_SZ_MASK                  0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_V_COUNT_SIZE_FIELD( sz ) \
    (u32)( \
    ((u32)(sz) << REG_LCD_PDC1_V_COUNT_SIZE_SZ_SHIFT))
#endif


/* PDC1_V_DISP_S */

#define REG_LCD_PDC1_V_DISP_S_S_SHIFT                      0
#define REG_LCD_PDC1_V_DISP_S_S_SIZE                       12
#define REG_LCD_PDC1_V_DISP_S_S_MASK                       0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_V_DISP_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_V_DISP_S_S_SHIFT))
#endif


/* PDC1_V_BBORDER_S */

#define REG_LCD_PDC1_V_BBORDER_S_S_SHIFT                   0
#define REG_LCD_PDC1_V_BBORDER_S_S_SIZE                    12
#define REG_LCD_PDC1_V_BBORDER_S_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_V_BBORDER_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_V_BBORDER_S_S_SHIFT))
#endif


/* PDC1_V_BLANK_S */

#define REG_LCD_PDC1_V_BLANK_S_S_SHIFT                     0
#define REG_LCD_PDC1_V_BLANK_S_S_SIZE                      12
#define REG_LCD_PDC1_V_BLANK_S_S_MASK                      0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_V_BLANK_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_V_BLANK_S_S_SHIFT))
#endif


/* PDC1_V_SYNC_S */

#define REG_LCD_PDC1_V_SYNC_S_S_SHIFT                      0
#define REG_LCD_PDC1_V_SYNC_S_S_SIZE                       12
#define REG_LCD_PDC1_V_SYNC_S_S_MASK                       0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_V_SYNC_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_V_SYNC_S_S_SHIFT))
#endif


/* PDC1_V_BPORTCH_S */

#define REG_LCD_PDC1_V_BPORTCH_S_S_SHIFT                   0
#define REG_LCD_PDC1_V_BPORTCH_S_S_SIZE                    12
#define REG_LCD_PDC1_V_BPORTCH_S_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_V_BPORTCH_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_V_BPORTCH_S_S_SHIFT))
#endif


/* PDC1_V_TBORDER_S */

#define REG_LCD_PDC1_V_TBORDER_S_S_SHIFT                   0
#define REG_LCD_PDC1_V_TBORDER_S_S_SIZE                    12
#define REG_LCD_PDC1_V_TBORDER_S_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_V_TBORDER_S_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_V_TBORDER_S_S_SHIFT))
#endif


/* PDC1_V_INTR_POS */

#define REG_LCD_PDC1_V_INTR_POS_E_SHIFT                    16
#define REG_LCD_PDC1_V_INTR_POS_E_SIZE                     12
#define REG_LCD_PDC1_V_INTR_POS_E_MASK                     0x0fff0000

#define REG_LCD_PDC1_V_INTR_POS_S_SHIFT                    0
#define REG_LCD_PDC1_V_INTR_POS_S_SIZE                     12
#define REG_LCD_PDC1_V_INTR_POS_S_MASK                     0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_V_INTR_POS_FIELD( e, s ) \
    (u32)( \
    ((u32)(e) << REG_LCD_PDC1_V_INTR_POS_E_SHIFT) | \
    ((u32)(s) << REG_LCD_PDC1_V_INTR_POS_S_SHIFT))
#endif


/* PDC1_V_INC_H_POS */

#define REG_LCD_PDC1_V_INC_H_POS_S_SHIFT                   0
#define REG_LCD_PDC1_V_INC_H_POS_S_SIZE                    12
#define REG_LCD_PDC1_V_INC_H_POS_S_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_V_INC_H_POS_FIELD( s ) \
    (u32)( \
    ((u32)(s) << REG_LCD_PDC1_V_INC_H_POS_S_SHIFT))
#endif


/* PDC1_SIGNAL_POL */

#define REG_LCD_PDC1_SIGNAL_POL_V_SHIFT                    4
#define REG_LCD_PDC1_SIGNAL_POL_V_SIZE                     1
#define REG_LCD_PDC1_SIGNAL_POL_V_MASK                     0x00000010

#define REG_LCD_PDC1_SIGNAL_POL_H_SHIFT                    0
#define REG_LCD_PDC1_SIGNAL_POL_H_SIZE                     1
#define REG_LCD_PDC1_SIGNAL_POL_H_MASK                     0x00000001

#ifndef SDK_ASM
#define REG_LCD_PDC1_SIGNAL_POL_FIELD( v, h ) \
    (u32)( \
    ((u32)(v) << REG_LCD_PDC1_SIGNAL_POL_V_SHIFT) | \
    ((u32)(h) << REG_LCD_PDC1_SIGNAL_POL_H_SHIFT))
#endif


/* PDC1_BORDER_COL */

#define REG_LCD_PDC1_BORDER_COL_B_SHIFT                    16
#define REG_LCD_PDC1_BORDER_COL_B_SIZE                     8
#define REG_LCD_PDC1_BORDER_COL_B_MASK                     0x00ff0000

#define REG_LCD_PDC1_BORDER_COL_G_SHIFT                    8
#define REG_LCD_PDC1_BORDER_COL_G_SIZE                     8
#define REG_LCD_PDC1_BORDER_COL_G_MASK                     0x0000ff00

#define REG_LCD_PDC1_BORDER_COL_R_SHIFT                    0
#define REG_LCD_PDC1_BORDER_COL_R_SIZE                     8
#define REG_LCD_PDC1_BORDER_COL_R_MASK                     0x000000ff

#ifndef SDK_ASM
#define REG_LCD_PDC1_BORDER_COL_FIELD( b, g, r ) \
    (u32)( \
    ((u32)(b) << REG_LCD_PDC1_BORDER_COL_B_SHIFT) | \
    ((u32)(g) << REG_LCD_PDC1_BORDER_COL_G_SHIFT) | \
    ((u32)(r) << REG_LCD_PDC1_BORDER_COL_R_SHIFT))
#endif


/* PDC1_H_COUNT */

#define REG_LCD_PDC1_H_COUNT_COUNT_SHIFT                   0
#define REG_LCD_PDC1_H_COUNT_COUNT_SIZE                    12
#define REG_LCD_PDC1_H_COUNT_COUNT_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_H_COUNT_FIELD( count ) \
    (u32)( \
    ((u32)(count) << REG_LCD_PDC1_H_COUNT_COUNT_SHIFT))
#endif


/* PDC1_V_COUNT */

#define REG_LCD_PDC1_V_COUNT_COUNT_SHIFT                   0
#define REG_LCD_PDC1_V_COUNT_COUNT_SIZE                    12
#define REG_LCD_PDC1_V_COUNT_COUNT_MASK                    0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_V_COUNT_FIELD( count ) \
    (u32)( \
    ((u32)(count) << REG_LCD_PDC1_V_COUNT_COUNT_SHIFT))
#endif


/* PDC1_OUT_SIZE */

#define REG_LCD_PDC1_OUT_SIZE_V_SHIFT                      16
#define REG_LCD_PDC1_OUT_SIZE_V_SIZE                       12
#define REG_LCD_PDC1_OUT_SIZE_V_MASK                       0x0fff0000

#define REG_LCD_PDC1_OUT_SIZE_H_SHIFT                      0
#define REG_LCD_PDC1_OUT_SIZE_H_SIZE                       12
#define REG_LCD_PDC1_OUT_SIZE_H_MASK                       0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_OUT_SIZE_FIELD( v, h ) \
    (u32)( \
    ((u32)(v) << REG_LCD_PDC1_OUT_SIZE_V_SHIFT) | \
    ((u32)(h) << REG_LCD_PDC1_OUT_SIZE_H_SHIFT))
#endif


/* PDC1_PIC_BORDER_H */

#define REG_LCD_PDC1_PIC_BORDER_H_E_SHIFT                  16
#define REG_LCD_PDC1_PIC_BORDER_H_E_SIZE                   12
#define REG_LCD_PDC1_PIC_BORDER_H_E_MASK                   0x0fff0000

#define REG_LCD_PDC1_PIC_BORDER_H_S_SHIFT                  0
#define REG_LCD_PDC1_PIC_BORDER_H_S_SIZE                   12
#define REG_LCD_PDC1_PIC_BORDER_H_S_MASK                   0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_PIC_BORDER_H_FIELD( e, s ) \
    (u32)( \
    ((u32)(e) << REG_LCD_PDC1_PIC_BORDER_H_E_SHIFT) | \
    ((u32)(s) << REG_LCD_PDC1_PIC_BORDER_H_S_SHIFT))
#endif


/* PDC1_PIC_BORDER_V */

#define REG_LCD_PDC1_PIC_BORDER_V_E_SHIFT                  16
#define REG_LCD_PDC1_PIC_BORDER_V_E_SIZE                   12
#define REG_LCD_PDC1_PIC_BORDER_V_E_MASK                   0x0fff0000

#define REG_LCD_PDC1_PIC_BORDER_V_S_SHIFT                  0
#define REG_LCD_PDC1_PIC_BORDER_V_S_SIZE                   12
#define REG_LCD_PDC1_PIC_BORDER_V_S_MASK                   0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_PIC_BORDER_V_FIELD( e, s ) \
    (u32)( \
    ((u32)(e) << REG_LCD_PDC1_PIC_BORDER_V_E_SHIFT) | \
    ((u32)(s) << REG_LCD_PDC1_PIC_BORDER_V_S_SHIFT))
#endif


/* PDC1_FB0_ADR */

#define REG_LCD_PDC1_FB0_ADR_ADR_SHIFT                     4
#define REG_LCD_PDC1_FB0_ADR_ADR_SIZE                      28
#define REG_LCD_PDC1_FB0_ADR_ADR_MASK                      0xfffffff0

#ifndef SDK_ASM
#define REG_LCD_PDC1_FB0_ADR_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_LCD_PDC1_FB0_ADR_ADR_SHIFT))
#endif


/* PDC1_FB1_ADR */

#define REG_LCD_PDC1_FB1_ADR_ADR_SHIFT                     4
#define REG_LCD_PDC1_FB1_ADR_ADR_SIZE                      28
#define REG_LCD_PDC1_FB1_ADR_ADR_MASK                      0xfffffff0

#ifndef SDK_ASM
#define REG_LCD_PDC1_FB1_ADR_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_LCD_PDC1_FB1_ADR_ADR_SHIFT))
#endif


/* PDC1_MODE */

#define REG_LCD_PDC1_MODE_INTERVAL_SHIFT                   16
#define REG_LCD_PDC1_MODE_INTERVAL_SIZE                    16
#define REG_LCD_PDC1_MODE_INTERVAL_MASK                    0xffff0000

#define REG_LCD_PDC1_MODE_BLEN_SHIFT                       8
#define REG_LCD_PDC1_MODE_BLEN_SIZE                        2
#define REG_LCD_PDC1_MODE_BLEN_MASK                        0x00000300

#define REG_LCD_PDC1_MODE_CLK_MODE_SHIFT                   6
#define REG_LCD_PDC1_MODE_CLK_MODE_SIZE                    1
#define REG_LCD_PDC1_MODE_CLK_MODE_MASK                    0x00000040

#define REG_LCD_PDC1_MODE_OUT_MODE_SHIFT                   4
#define REG_LCD_PDC1_MODE_OUT_MODE_SIZE                    2
#define REG_LCD_PDC1_MODE_OUT_MODE_MASK                    0x00000030

#define REG_LCD_PDC1_MODE_FMT_SHIFT                        0
#define REG_LCD_PDC1_MODE_FMT_SIZE                         3
#define REG_LCD_PDC1_MODE_FMT_MASK                         0x00000007

#ifndef SDK_ASM
#define REG_LCD_PDC1_MODE_FIELD( interval, blen, clk_mode, out_mode, fmt ) \
    (u32)( \
    ((u32)(interval) << REG_LCD_PDC1_MODE_INTERVAL_SHIFT) | \
    ((u32)(blen) << REG_LCD_PDC1_MODE_BLEN_SHIFT) | \
    ((u32)(clk_mode) << REG_LCD_PDC1_MODE_CLK_MODE_SHIFT) | \
    ((u32)(out_mode) << REG_LCD_PDC1_MODE_OUT_MODE_SHIFT) | \
    ((u32)(fmt) << REG_LCD_PDC1_MODE_FMT_SHIFT))
#endif


/* PDC1_START */

#define REG_LCD_PDC1_START_O_E_SHIFT                       16
#define REG_LCD_PDC1_START_O_E_SIZE                        1
#define REG_LCD_PDC1_START_O_E_MASK                        0x00010000

#define REG_LCD_PDC1_START_IM_ERR_SHIFT                    10
#define REG_LCD_PDC1_START_IM_ERR_SIZE                     1
#define REG_LCD_PDC1_START_IM_ERR_MASK                     0x00000400

#define REG_LCD_PDC1_START_IM_V_SHIFT                      9
#define REG_LCD_PDC1_START_IM_V_SIZE                       1
#define REG_LCD_PDC1_START_IM_V_MASK                       0x00000200

#define REG_LCD_PDC1_START_IM_H_SHIFT                      8
#define REG_LCD_PDC1_START_IM_H_SIZE                       1
#define REG_LCD_PDC1_START_IM_H_MASK                       0x00000100

#define REG_LCD_PDC1_START_E_SHIFT                         0
#define REG_LCD_PDC1_START_E_SIZE                          1
#define REG_LCD_PDC1_START_E_MASK                          0x00000001

#ifndef SDK_ASM
#define REG_LCD_PDC1_START_FIELD( o_e, im_err, im_v, im_h, e ) \
    (u32)( \
    ((u32)(o_e) << REG_LCD_PDC1_START_O_E_SHIFT) | \
    ((u32)(im_err) << REG_LCD_PDC1_START_IM_ERR_SHIFT) | \
    ((u32)(im_v) << REG_LCD_PDC1_START_IM_V_SHIFT) | \
    ((u32)(im_h) << REG_LCD_PDC1_START_IM_H_SHIFT) | \
    ((u32)(e) << REG_LCD_PDC1_START_E_SHIFT))
#endif


/* PDC1_SWAP */

#define REG_LCD_PDC1_SWAP_ICLR_ERR_SHIFT                   18
#define REG_LCD_PDC1_SWAP_ICLR_ERR_SIZE                    1
#define REG_LCD_PDC1_SWAP_ICLR_ERR_MASK                    0x00040000

#define REG_LCD_PDC1_SWAP_ICLR_V_SHIFT                     17
#define REG_LCD_PDC1_SWAP_ICLR_V_SIZE                      1
#define REG_LCD_PDC1_SWAP_ICLR_V_MASK                      0x00020000

#define REG_LCD_PDC1_SWAP_ICLR_H_SHIFT                     16
#define REG_LCD_PDC1_SWAP_ICLR_H_SIZE                      1
#define REG_LCD_PDC1_SWAP_ICLR_H_MASK                      0x00010000

#define REG_LCD_PDC1_SWAP_RST_FIFO_SHIFT                   8
#define REG_LCD_PDC1_SWAP_RST_FIFO_SIZE                    1
#define REG_LCD_PDC1_SWAP_RST_FIFO_MASK                    0x00000100

#define REG_LCD_PDC1_SWAP_AT_SWAP_SHIFT                    4
#define REG_LCD_PDC1_SWAP_AT_SWAP_SIZE                     1
#define REG_LCD_PDC1_SWAP_AT_SWAP_MASK                     0x00000010

#define REG_LCD_PDC1_SWAP_NEXT_SHIFT                       0
#define REG_LCD_PDC1_SWAP_NEXT_SIZE                        1
#define REG_LCD_PDC1_SWAP_NEXT_MASK                        0x00000001

#ifndef SDK_ASM
#define REG_LCD_PDC1_SWAP_FIELD( iclr_err, iclr_v, iclr_h, rst_fifo, at_swap, next ) \
    (u32)( \
    ((u32)(iclr_err) << REG_LCD_PDC1_SWAP_ICLR_ERR_SHIFT) | \
    ((u32)(iclr_v) << REG_LCD_PDC1_SWAP_ICLR_V_SHIFT) | \
    ((u32)(iclr_h) << REG_LCD_PDC1_SWAP_ICLR_H_SHIFT) | \
    ((u32)(rst_fifo) << REG_LCD_PDC1_SWAP_RST_FIFO_SHIFT) | \
    ((u32)(at_swap) << REG_LCD_PDC1_SWAP_AT_SWAP_SHIFT) | \
    ((u32)(next) << REG_LCD_PDC1_SWAP_NEXT_SHIFT))
#endif


/* PDC1_STAT */

#define REG_LCD_PDC1_STAT_ERR_SHIFT                        15
#define REG_LCD_PDC1_STAT_ERR_SIZE                         1
#define REG_LCD_PDC1_STAT_ERR_MASK                         0x00008000

#define REG_LCD_PDC1_STAT_H_ACTIVE_SHIFT                   14
#define REG_LCD_PDC1_STAT_H_ACTIVE_SIZE                    1
#define REG_LCD_PDC1_STAT_H_ACTIVE_MASK                    0x00004000

#define REG_LCD_PDC1_STAT_H_BLANK_SHIFT                    13
#define REG_LCD_PDC1_STAT_H_BLANK_SIZE                     1
#define REG_LCD_PDC1_STAT_H_BLANK_MASK                     0x00002000

#define REG_LCD_PDC1_STAT_H_SYNC_SHIFT                     12
#define REG_LCD_PDC1_STAT_H_SYNC_SIZE                      1
#define REG_LCD_PDC1_STAT_H_SYNC_MASK                      0x00001000

#define REG_LCD_PDC1_STAT_V_ACTIVE_SHIFT                   10
#define REG_LCD_PDC1_STAT_V_ACTIVE_SIZE                    1
#define REG_LCD_PDC1_STAT_V_ACTIVE_MASK                    0x00000400

#define REG_LCD_PDC1_STAT_V_BLANK_SHIFT                    9
#define REG_LCD_PDC1_STAT_V_BLANK_SIZE                     1
#define REG_LCD_PDC1_STAT_V_BLANK_MASK                     0x00000200

#define REG_LCD_PDC1_STAT_V_SYNC_SHIFT                     8
#define REG_LCD_PDC1_STAT_V_SYNC_SIZE                      1
#define REG_LCD_PDC1_STAT_V_SYNC_MASK                      0x00000100

#define REG_LCD_PDC1_STAT_CUR_BANK_SHIFT                   4
#define REG_LCD_PDC1_STAT_CUR_BANK_SIZE                    1
#define REG_LCD_PDC1_STAT_CUR_BANK_MASK                    0x00000010

#define REG_LCD_PDC1_STAT_H_INT_SHIFT                      1
#define REG_LCD_PDC1_STAT_H_INT_SIZE                       1
#define REG_LCD_PDC1_STAT_H_INT_MASK                       0x00000002

#define REG_LCD_PDC1_STAT_V_INT_SHIFT                      0
#define REG_LCD_PDC1_STAT_V_INT_SIZE                       1
#define REG_LCD_PDC1_STAT_V_INT_MASK                       0x00000001

#ifndef SDK_ASM
#define REG_LCD_PDC1_STAT_FIELD( err, h_active, h_blank, h_sync, v_active, v_blank, v_sync, cur_bank, h_int, v_int ) \
    (u32)( \
    ((u32)(err) << REG_LCD_PDC1_STAT_ERR_SHIFT) | \
    ((u32)(h_active) << REG_LCD_PDC1_STAT_H_ACTIVE_SHIFT) | \
    ((u32)(h_blank) << REG_LCD_PDC1_STAT_H_BLANK_SHIFT) | \
    ((u32)(h_sync) << REG_LCD_PDC1_STAT_H_SYNC_SHIFT) | \
    ((u32)(v_active) << REG_LCD_PDC1_STAT_V_ACTIVE_SHIFT) | \
    ((u32)(v_blank) << REG_LCD_PDC1_STAT_V_BLANK_SHIFT) | \
    ((u32)(v_sync) << REG_LCD_PDC1_STAT_V_SYNC_SHIFT) | \
    ((u32)(cur_bank) << REG_LCD_PDC1_STAT_CUR_BANK_SHIFT) | \
    ((u32)(h_int) << REG_LCD_PDC1_STAT_H_INT_SHIFT) | \
    ((u32)(v_int) << REG_LCD_PDC1_STAT_V_INT_SHIFT))
#endif


/* PDC1_GTBL_ADR */

#define REG_LCD_PDC1_GTBL_ADR_ADR_SHIFT                    0
#define REG_LCD_PDC1_GTBL_ADR_ADR_SIZE                     8
#define REG_LCD_PDC1_GTBL_ADR_ADR_MASK                     0x000000ff

#ifndef SDK_ASM
#define REG_LCD_PDC1_GTBL_ADR_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_LCD_PDC1_GTBL_ADR_ADR_SHIFT))
#endif


/* PDC1_GTBL_DATA */

#define REG_LCD_PDC1_GTBL_DATA_B_SHIFT                     16
#define REG_LCD_PDC1_GTBL_DATA_B_SIZE                      8
#define REG_LCD_PDC1_GTBL_DATA_B_MASK                      0x00ff0000

#define REG_LCD_PDC1_GTBL_DATA_G_SHIFT                     8
#define REG_LCD_PDC1_GTBL_DATA_G_SIZE                      8
#define REG_LCD_PDC1_GTBL_DATA_G_MASK                      0x0000ff00

#define REG_LCD_PDC1_GTBL_DATA_R_SHIFT                     0
#define REG_LCD_PDC1_GTBL_DATA_R_SIZE                      8
#define REG_LCD_PDC1_GTBL_DATA_R_MASK                      0x000000ff

#ifndef SDK_ASM
#define REG_LCD_PDC1_GTBL_DATA_FIELD( b, g, r ) \
    (u32)( \
    ((u32)(b) << REG_LCD_PDC1_GTBL_DATA_B_SHIFT) | \
    ((u32)(g) << REG_LCD_PDC1_GTBL_DATA_G_SHIFT) | \
    ((u32)(r) << REG_LCD_PDC1_GTBL_DATA_R_SHIFT))
#endif


/* PDC1_FB_SIZE */

/* PDC1_FB0_B_ADR */

#define REG_LCD_PDC1_FB0_B_ADR_ADR_SHIFT                   4
#define REG_LCD_PDC1_FB0_B_ADR_ADR_SIZE                    28
#define REG_LCD_PDC1_FB0_B_ADR_ADR_MASK                    0xfffffff0

#ifndef SDK_ASM
#define REG_LCD_PDC1_FB0_B_ADR_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_LCD_PDC1_FB0_B_ADR_ADR_SHIFT))
#endif


/* PDC1_FB1_B_ADR */

#define REG_LCD_PDC1_FB1_B_ADR_ADR_SHIFT                   4
#define REG_LCD_PDC1_FB1_B_ADR_ADR_SIZE                    28
#define REG_LCD_PDC1_FB1_B_ADR_ADR_MASK                    0xfffffff0

#ifndef SDK_ASM
#define REG_LCD_PDC1_FB1_B_ADR_FIELD( adr ) \
    (u32)( \
    ((u32)(adr) << REG_LCD_PDC1_FB1_B_ADR_ADR_SHIFT))
#endif


/* PDC1_UPDATE */

#define REG_LCD_PDC1_UPDATE_V_COUNT_SHIFT                  16
#define REG_LCD_PDC1_UPDATE_V_COUNT_SIZE                   12
#define REG_LCD_PDC1_UPDATE_V_COUNT_MASK                   0x0fff0000

#define REG_LCD_PDC1_UPDATE_H_COUNT_SHIFT                  0
#define REG_LCD_PDC1_UPDATE_H_COUNT_SIZE                   12
#define REG_LCD_PDC1_UPDATE_H_COUNT_MASK                   0x00000fff

#ifndef SDK_ASM
#define REG_LCD_PDC1_UPDATE_FIELD( v_count, h_count ) \
    (u32)( \
    ((u32)(v_count) << REG_LCD_PDC1_UPDATE_V_COUNT_SHIFT) | \
    ((u32)(h_count) << REG_LCD_PDC1_UPDATE_H_COUNT_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_EIU_MPCORE_IOREG_EIUPATCH_LCD_H_ */
#endif
