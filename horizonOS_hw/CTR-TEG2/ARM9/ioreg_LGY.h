/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/ARM9/ioreg_LGY.h

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
#ifndef NN_HW_CTR_TEG2_ARM9_IOREG_LGY_H_
#define NN_HW_CTR_TEG2_ARM9_IOREG_LGY_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* LMOD_A11 */

#define REG_LMOD_A11_OFFSET                                0x141100
#define REG_LMOD_A11_ADDR                                  (HW_REG_BASE + REG_LMOD_A11_OFFSET)
#define reg_LGY_LMOD_A11                                   (*( REGType16v *) REG_LMOD_A11_ADDR)

/* LMOD */

#define REG_LMOD_OFFSET                                    0x18000
#define REG_LMOD_ADDR                                      (HW_REG_BASE + REG_LMOD_OFFSET)
#define reg_LGY_LMOD                                       (*( REGType8v *) REG_LMOD_ADDR)

/* VEC0 */

#define REG_VEC0_OFFSET                                    0x18080
#define REG_VEC0_ADDR                                      (HW_REG_BASE + REG_VEC0_OFFSET)
#define reg_LGY_VEC0                                       (*( REGType32v *) REG_VEC0_ADDR)

/* VEC1 */

#define REG_VEC1_OFFSET                                    0x18084
#define REG_VEC1_ADDR                                      (HW_REG_BASE + REG_VEC1_OFFSET)
#define reg_LGY_VEC1                                       (*( REGType32v *) REG_VEC1_ADDR)

/* AGB_BKSEL */

#define REG_AGB_BKSEL_OFFSET                               0x18100
#define REG_AGB_BKSEL_ADDR                                 (HW_REG_BASE + REG_AGB_BKSEL_OFFSET)
#define reg_LGY_AGB_BKSEL                                  (*( REGType8v *) REG_AGB_BKSEL_ADDR)

/* AGB_BKCNT */

#define REG_AGB_BKCNT_OFFSET                               0x18104
#define REG_AGB_BKCNT_ADDR                                 (HW_REG_BASE + REG_AGB_BKCNT_OFFSET)
#define reg_LGY_AGB_BKCNT                                  (*( REGType8v *) REG_AGB_BKCNT_ADDR)

/* AGB_RTCCNT */

#define REG_AGB_RTCCNT_OFFSET                              0x18108
#define REG_AGB_RTCCNT_ADDR                                (HW_REG_BASE + REG_AGB_RTCCNT_OFFSET)
#define reg_LGY_AGB_RTCCNT                                 (*( REGType16v *) REG_AGB_RTCCNT_ADDR)

/* AGB_RTCD0 */

#define REG_AGB_RTCD0_OFFSET                               0x18110
#define REG_AGB_RTCD0_ADDR                                 (HW_REG_BASE + REG_AGB_RTCD0_OFFSET)
#define reg_LGY_AGB_RTCD0                                  (*( REGType32v *) REG_AGB_RTCD0_ADDR)

/* AGB_RTCD1 */

#define REG_AGB_RTCD1_OFFSET                               0x18114
#define REG_AGB_RTCD1_ADDR                                 (HW_REG_BASE + REG_AGB_RTCD1_OFFSET)
#define reg_LGY_AGB_RTCD1                                  (*( REGType32v *) REG_AGB_RTCD1_ADDR)

/* AGB_RTCSTAT */

#define REG_AGB_RTCSTAT_OFFSET                             0x18118
#define REG_AGB_RTCSTAT_ADDR                               (HW_REG_BASE + REG_AGB_RTCSTAT_OFFSET)
#define reg_LGY_AGB_RTCSTAT                                (*( REGType32v *) REG_AGB_RTCSTAT_ADDR)

/* AGB_RTCD_DF */

#define REG_AGB_RTCD_DF_OFFSET                             0x1811c
#define REG_AGB_RTCD_DF_ADDR                               (HW_REG_BASE + REG_AGB_RTCD_DF_OFFSET)
#define reg_LGY_AGB_RTCD_DF                                (*( REGType16v *) REG_AGB_RTCD_DF_ADDR)

/* AGB_RTCINT */

#define REG_AGB_RTCINT_OFFSET                              0x1811e
#define REG_AGB_RTCINT_ADDR                                (HW_REG_BASE + REG_AGB_RTCINT_OFFSET)
#define reg_LGY_AGB_RTCINT                                 (*( REGType16v *) REG_AGB_RTCINT_ADDR)

/* AGB_FLHCC */

#define REG_AGB_FLHCC_OFFSET                               0x18120
#define REG_AGB_FLHCC_ADDR                                 (HW_REG_BASE + REG_AGB_FLHCC_OFFSET)
#define reg_LGY_AGB_FLHCC                                  (*( REGType32v *) REG_AGB_FLHCC_ADDR)

/* AGB_FLHSC */

#define REG_AGB_FLHSC_OFFSET                               0x18124
#define REG_AGB_FLHSC_ADDR                                 (HW_REG_BASE + REG_AGB_FLHSC_OFFSET)
#define reg_LGY_AGB_FLHSC                                  (*( REGType32v *) REG_AGB_FLHSC_ADDR)

/* AGB_FLHPRG */

#define REG_AGB_FLHPRG_OFFSET                              0x18128
#define REG_AGB_FLHPRG_ADDR                                (HW_REG_BASE + REG_AGB_FLHPRG_OFFSET)
#define reg_LGY_AGB_FLHPRG                                 (*( REGType32v *) REG_AGB_FLHPRG_ADDR)

/* AGB_EEPROM_W */

#define REG_AGB_EEPROM_W_OFFSET                            0x1812c
#define REG_AGB_EEPROM_W_ADDR                              (HW_REG_BASE + REG_AGB_EEPROM_W_OFFSET)
#define reg_LGY_AGB_EEPROM_W                               (*( REGType32v *) REG_AGB_EEPROM_W_ADDR)


/*
 * Definitions of Register fields
 */


/* LMOD_A11 */

#define REG_LGY_LMOD_A11_E_SHIFT                           15
#define REG_LGY_LMOD_A11_E_SIZE                            1
#define REG_LGY_LMOD_A11_E_MASK                            0x8000

#define REG_LGY_LMOD_A11_M_SHIFT                           0
#define REG_LGY_LMOD_A11_M_SIZE                            2
#define REG_LGY_LMOD_A11_M_MASK                            0x0003

#ifndef SDK_ASM
#define REG_LGY_LMOD_A11_FIELD( e, m ) \
    (u16)( \
    ((u32)(e) << REG_LGY_LMOD_A11_E_SHIFT) | \
    ((u32)(m) << REG_LGY_LMOD_A11_M_SHIFT))
#endif


/* LMOD */

#define REG_LGY_LMOD_M_SHIFT                               0
#define REG_LGY_LMOD_M_SIZE                                2
#define REG_LGY_LMOD_M_MASK                                0x03

#ifndef SDK_ASM
#define REG_LGY_LMOD_FIELD( m ) \
    (u8)( \
    ((u32)(m) << REG_LGY_LMOD_M_SHIFT))
#endif


/* VEC0 */

/* VEC1 */

/* AGB_BKSEL */

#define REG_LGY_AGB_BKSEL_TYPE_SHIFT                       0
#define REG_LGY_AGB_BKSEL_TYPE_SIZE                        4
#define REG_LGY_AGB_BKSEL_TYPE_MASK                        0x0f

#ifndef SDK_ASM
#define REG_LGY_AGB_BKSEL_FIELD( type ) \
    (u8)( \
    ((u32)(type) << REG_LGY_AGB_BKSEL_TYPE_SHIFT))
#endif


/* AGB_BKCNT */

#define REG_LGY_AGB_BKCNT_MST_SHIFT                        0
#define REG_LGY_AGB_BKCNT_MST_SIZE                         1
#define REG_LGY_AGB_BKCNT_MST_MASK                         0x01

#ifndef SDK_ASM
#define REG_LGY_AGB_BKCNT_FIELD( mst ) \
    (u8)( \
    ((u32)(mst) << REG_LGY_AGB_BKCNT_MST_SHIFT))
#endif


/* AGB_RTCCNT */

#define REG_LGY_AGB_RTCCNT_DF_BUSY_SHIFT                   15
#define REG_LGY_AGB_RTCCNT_DF_BUSY_SIZE                    1
#define REG_LGY_AGB_RTCCNT_DF_BUSY_MASK                    0x8000

#define REG_LGY_AGB_RTCCNT_DF_ERR_SHIFT                    14
#define REG_LGY_AGB_RTCCNT_DF_ERR_SIZE                     1
#define REG_LGY_AGB_RTCCNT_DF_ERR_MASK                     0x4000

#define REG_LGY_AGB_RTCCNT_DF_ST_SHIFT                     1
#define REG_LGY_AGB_RTCCNT_DF_ST_SIZE                      1
#define REG_LGY_AGB_RTCCNT_DF_ST_MASK                      0x0002

#define REG_LGY_AGB_RTCCNT_SET_SHIFT                       0
#define REG_LGY_AGB_RTCCNT_SET_SIZE                        1
#define REG_LGY_AGB_RTCCNT_SET_MASK                        0x0001

#ifndef SDK_ASM
#define REG_LGY_AGB_RTCCNT_FIELD( df_busy, df_err, df_st, set ) \
    (u16)( \
    ((u32)(df_busy) << REG_LGY_AGB_RTCCNT_DF_BUSY_SHIFT) | \
    ((u32)(df_err) << REG_LGY_AGB_RTCCNT_DF_ERR_SHIFT) | \
    ((u32)(df_st) << REG_LGY_AGB_RTCCNT_DF_ST_SHIFT) | \
    ((u32)(set) << REG_LGY_AGB_RTCCNT_SET_SHIFT))
#endif


/* AGB_RTCD0 */

#define REG_LGY_AGB_RTCD0_W_SHIFT                          24
#define REG_LGY_AGB_RTCD0_W_SIZE                           3
#define REG_LGY_AGB_RTCD0_W_MASK                           0x07000000

#define REG_LGY_AGB_RTCD0_D_SHIFT                          16
#define REG_LGY_AGB_RTCD0_D_SIZE                           6
#define REG_LGY_AGB_RTCD0_D_MASK                           0x003f0000

#define REG_LGY_AGB_RTCD0_MON_SHIFT                        8
#define REG_LGY_AGB_RTCD0_MON_SIZE                         5
#define REG_LGY_AGB_RTCD0_MON_MASK                         0x00001f00

#define REG_LGY_AGB_RTCD0_Y_SHIFT                          0
#define REG_LGY_AGB_RTCD0_Y_SIZE                           8
#define REG_LGY_AGB_RTCD0_Y_MASK                           0x000000ff

#ifndef SDK_ASM
#define REG_LGY_AGB_RTCD0_FIELD( w, d, mon, y ) \
    (u32)( \
    ((u32)(w) << REG_LGY_AGB_RTCD0_W_SHIFT) | \
    ((u32)(d) << REG_LGY_AGB_RTCD0_D_SHIFT) | \
    ((u32)(mon) << REG_LGY_AGB_RTCD0_MON_SHIFT) | \
    ((u32)(y) << REG_LGY_AGB_RTCD0_Y_SHIFT))
#endif


/* AGB_RTCD1 */

#define REG_LGY_AGB_RTCD1_S_SHIFT                          16
#define REG_LGY_AGB_RTCD1_S_SIZE                           7
#define REG_LGY_AGB_RTCD1_S_MASK                           0x007f0000

#define REG_LGY_AGB_RTCD1_MIN_SHIFT                        8
#define REG_LGY_AGB_RTCD1_MIN_SIZE                         7
#define REG_LGY_AGB_RTCD1_MIN_MASK                         0x00007f00

#define REG_LGY_AGB_RTCD1_H_SHIFT                          0
#define REG_LGY_AGB_RTCD1_H_SIZE                           6
#define REG_LGY_AGB_RTCD1_H_MASK                           0x0000003f

#ifndef SDK_ASM
#define REG_LGY_AGB_RTCD1_FIELD( s, min, h ) \
    (u32)( \
    ((u32)(s) << REG_LGY_AGB_RTCD1_S_SHIFT) | \
    ((u32)(min) << REG_LGY_AGB_RTCD1_MIN_SHIFT) | \
    ((u32)(h) << REG_LGY_AGB_RTCD1_H_SHIFT))
#endif


/* AGB_RTCSTAT */

#define REG_LGY_AGB_RTCSTAT_D_DF_16_SHIFT                  31
#define REG_LGY_AGB_RTCSTAT_D_DF_16_SIZE                   1
#define REG_LGY_AGB_RTCSTAT_D_DF_16_MASK                   0x80000000

#define REG_LGY_AGB_RTCSTAT_INT_AE_SHIFT                   30
#define REG_LGY_AGB_RTCSTAT_INT_AE_SIZE                    1
#define REG_LGY_AGB_RTCSTAT_INT_AE_MASK                    0x40000000

#define REG_LGY_AGB_RTCSTAT_INT_ME_SHIFT                   29
#define REG_LGY_AGB_RTCSTAT_INT_ME_SIZE                    1
#define REG_LGY_AGB_RTCSTAT_INT_ME_MASK                    0x20000000

#define REG_LGY_AGB_RTCSTAT_INT_FE_SHIFT                   28
#define REG_LGY_AGB_RTCSTAT_INT_FE_SIZE                    1
#define REG_LGY_AGB_RTCSTAT_INT_FE_MASK                    0x10000000

#define REG_LGY_AGB_RTCSTAT_W_DF_SHIFT                     24
#define REG_LGY_AGB_RTCSTAT_W_DF_SIZE                      4
#define REG_LGY_AGB_RTCSTAT_W_DF_MASK                      0x0f000000

#define REG_LGY_AGB_RTCSTAT_H_DF_SHIFT                     16
#define REG_LGY_AGB_RTCSTAT_H_DF_SIZE                      6
#define REG_LGY_AGB_RTCSTAT_H_DF_MASK                      0x003f0000

#define REG_LGY_AGB_RTCSTAT_AM_PM_SHIFT                    15
#define REG_LGY_AGB_RTCSTAT_AM_PM_SIZE                     1
#define REG_LGY_AGB_RTCSTAT_AM_PM_MASK                     0x00008000

#define REG_LGY_AGB_RTCSTAT_MIN_DF_SHIFT                   8
#define REG_LGY_AGB_RTCSTAT_MIN_DF_SIZE                    7
#define REG_LGY_AGB_RTCSTAT_MIN_DF_MASK                    0x00007f00

#define REG_LGY_AGB_RTCSTAT_POW_SHIFT                      7
#define REG_LGY_AGB_RTCSTAT_POW_SIZE                       1
#define REG_LGY_AGB_RTCSTAT_POW_MASK                       0x00000080

#define REG_LGY_AGB_RTCSTAT_S_DF_SHIFT                     8
#define REG_LGY_AGB_RTCSTAT_S_DF_SIZE                      7
#define REG_LGY_AGB_RTCSTAT_S_DF_MASK                      0x00007f00

#ifndef SDK_ASM
#define REG_LGY_AGB_RTCSTAT_FIELD( d_df_16, int_ae, int_me, int_fe, w_df, h_df, am_pm, min_df, pow, s_df ) \
    (u32)( \
    ((u32)(d_df_16) << REG_LGY_AGB_RTCSTAT_D_DF_16_SHIFT) | \
    ((u32)(int_ae) << REG_LGY_AGB_RTCSTAT_INT_AE_SHIFT) | \
    ((u32)(int_me) << REG_LGY_AGB_RTCSTAT_INT_ME_SHIFT) | \
    ((u32)(int_fe) << REG_LGY_AGB_RTCSTAT_INT_FE_SHIFT) | \
    ((u32)(w_df) << REG_LGY_AGB_RTCSTAT_W_DF_SHIFT) | \
    ((u32)(h_df) << REG_LGY_AGB_RTCSTAT_H_DF_SHIFT) | \
    ((u32)(am_pm) << REG_LGY_AGB_RTCSTAT_AM_PM_SHIFT) | \
    ((u32)(min_df) << REG_LGY_AGB_RTCSTAT_MIN_DF_SHIFT) | \
    ((u32)(pow) << REG_LGY_AGB_RTCSTAT_POW_SHIFT) | \
    ((u32)(s_df) << REG_LGY_AGB_RTCSTAT_S_DF_SHIFT))
#endif


/* AGB_RTCD_DF */

/* AGB_RTCINT */

/* AGB_FLHCC */

#define REG_LGY_AGB_FLHCC_TM_SHIFT                         0
#define REG_LGY_AGB_FLHCC_TM_SIZE                          24
#define REG_LGY_AGB_FLHCC_TM_MASK                          0x00ffffff

#ifndef SDK_ASM
#define REG_LGY_AGB_FLHCC_FIELD( tm ) \
    (u32)( \
    ((u32)(tm) << REG_LGY_AGB_FLHCC_TM_SHIFT))
#endif


/* AGB_FLHSC */

#define REG_LGY_AGB_FLHSC_TM_SHIFT                         0
#define REG_LGY_AGB_FLHSC_TM_SIZE                          24
#define REG_LGY_AGB_FLHSC_TM_MASK                          0x00ffffff

#ifndef SDK_ASM
#define REG_LGY_AGB_FLHSC_FIELD( tm ) \
    (u32)( \
    ((u32)(tm) << REG_LGY_AGB_FLHSC_TM_SHIFT))
#endif


/* AGB_FLHPRG */

#define REG_LGY_AGB_FLHPRG_TM_SHIFT                        0
#define REG_LGY_AGB_FLHPRG_TM_SIZE                         20
#define REG_LGY_AGB_FLHPRG_TM_MASK                         0x000fffff

#ifndef SDK_ASM
#define REG_LGY_AGB_FLHPRG_FIELD( tm ) \
    (u32)( \
    ((u32)(tm) << REG_LGY_AGB_FLHPRG_TM_SHIFT))
#endif


/* AGB_EEPROM_W */

#define REG_LGY_AGB_EEPROM_W_TM_SHIFT                      0
#define REG_LGY_AGB_EEPROM_W_TM_SIZE                       20
#define REG_LGY_AGB_EEPROM_W_TM_MASK                       0x000fffff

#ifndef SDK_ASM
#define REG_LGY_AGB_EEPROM_W_FIELD( tm ) \
    (u32)( \
    ((u32)(tm) << REG_LGY_AGB_EEPROM_W_TM_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_ARM9_IOREG_LGY_H_ */
#endif
