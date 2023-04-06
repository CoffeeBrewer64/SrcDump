/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-EIU/MPCore/ioreg_eiupatch_SPM.h

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
#ifndef NN_HW_CTR_EIU_MPCORE_IOREG_EIUPATCH_SPM_H_
#define NN_HW_CTR_EIU_MPCORE_IOREG_EIUPATCH_SPM_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* MCNT */

#define REG_MCNT_OFFSET                                    0x205000
#define REG_MCNT_ADDR                                      (HW_REG_BASE + REG_MCNT_OFFSET)
#define reg_SPM_MCNT                                       (*( REGType32v *) REG_MCNT_ADDR)

/* MTIM */

#define REG_MTIM_OFFSET                                    0x205008
#define REG_MTIM_ADDR                                      (HW_REG_BASE + REG_MTIM_OFFSET)
#define reg_SPM_MTIM                                       (*( REGType32v *) REG_MTIM_ADDR)

/* MSTRG */

#define REG_MSTRG_OFFSET                                   0x20500c
#define REG_MSTRG_ADDR                                     (HW_REG_BASE + REG_MSTRG_OFFSET)
#define reg_SPM_MSTRG                                      (*( REGType32v *) REG_MSTRG_ADDR)

/* MSAVE */

#define REG_MSAVE_OFFSET                                   0x205010
#define REG_MSAVE_ADDR                                     (HW_REG_BASE + REG_MSAVE_OFFSET)
#define reg_SPM_MSAVE                                      (*( REGType32v *) REG_MSAVE_ADDR)

/* MIF */

#define REG_MIF_OFFSET                                     0x205020
#define REG_MIF_ADDR                                       (HW_REG_BASE + REG_MIF_OFFSET)
#define reg_SPM_MIF                                        (*( REGType32v *) REG_MIF_ADDR)

/* WPRIO */

#define REG_WPRIO_OFFSET                                   0x205080
#define REG_WPRIO_ADDR                                     (HW_REG_BASE + REG_WPRIO_OFFSET)
#define reg_SPM_WPRIO                                      (*( REGType32v *) REG_WPRIO_ADDR)

/* C00CNT */

#define REG_C00CNT_OFFSET                                  0x205100
#define REG_C00CNT_ADDR                                    (HW_REG_BASE + REG_C00CNT_OFFSET)
#define reg_SPM_C00CNT                                     (*( REGType32v *) REG_C00CNT_ADDR)

/* C00STAT */

#define REG_C00STAT_OFFSET                                 0x205200
#define REG_C00STAT_ADDR                                   (HW_REG_BASE + REG_C00STAT_OFFSET)
#define reg_SPM_C00STAT                                    (*( REGType32v *) REG_C00STAT_ADDR)

/* C00CDT0 */

#define REG_C00CDT0_OFFSET                                 0x205400
#define REG_C00CDT0_ADDR                                   (HW_REG_BASE + REG_C00CDT0_OFFSET)
#define reg_SPM_C00CDT0                                    (*( REGType32v *) REG_C00CDT0_ADDR)

/* C00CDT1 */

#define REG_C00CDT1_OFFSET                                 0x205404
#define REG_C00CDT1_ADDR                                   (HW_REG_BASE + REG_C00CDT1_OFFSET)
#define reg_SPM_C00CDT1                                    (*( REGType32v *) REG_C00CDT1_ADDR)

/* C00CDT2 */

#define REG_C00CDT2_OFFSET                                 0x205408
#define REG_C00CDT2_ADDR                                   (HW_REG_BASE + REG_C00CDT2_OFFSET)
#define reg_SPM_C00CDT2                                    (*( REGType32v *) REG_C00CDT2_ADDR)

/* C00CDT3 */

#define REG_C00CDT3_OFFSET                                 0x20540c
#define REG_C00CDT3_ADDR                                   (HW_REG_BASE + REG_C00CDT3_OFFSET)
#define reg_SPM_C00CDT3                                    (*( REGType32v *) REG_C00CDT3_ADDR)


/*
 * Definitions of Register fields
 */


/* MCNT */

#define REG_SPM_MCNT_ST_SHIFT                              31
#define REG_SPM_MCNT_ST_SIZE                               1
#define REG_SPM_MCNT_ST_MASK                               0x80000000

#define REG_SPM_MCNT_DREQ_EN_SHIFT                         28
#define REG_SPM_MCNT_DREQ_EN_SIZE                          2
#define REG_SPM_MCNT_DREQ_EN_MASK                          0x30000000

#define REG_SPM_MCNT_AIE_SHIFT                             18
#define REG_SPM_MCNT_AIE_SIZE                              1
#define REG_SPM_MCNT_AIE_MASK                              0x00040000

#define REG_SPM_MCNT_TERM_SHIFT                            17
#define REG_SPM_MCNT_TERM_SIZE                             1
#define REG_SPM_MCNT_TERM_MASK                             0x00020000

#define REG_SPM_MCNT_MODE_SHIFT                            16
#define REG_SPM_MCNT_MODE_SIZE                             1
#define REG_SPM_MCNT_MODE_MASK                             0x00010000

#define REG_SPM_MCNT_IREQ_EN_SHIFT                         12
#define REG_SPM_MCNT_IREQ_EN_SIZE                          2
#define REG_SPM_MCNT_IREQ_EN_MASK                          0x00003000

#define REG_SPM_MCNT_RT_SHIFT                              0
#define REG_SPM_MCNT_RT_SIZE                               6
#define REG_SPM_MCNT_RT_MASK                               0x0000003f

#ifndef SDK_ASM
#define REG_SPM_MCNT_FIELD( st, dreq_en, aie, term, mode, ireq_en, rt ) \
    (u32)( \
    ((u32)(st) << REG_SPM_MCNT_ST_SHIFT) | \
    ((u32)(dreq_en) << REG_SPM_MCNT_DREQ_EN_SHIFT) | \
    ((u32)(aie) << REG_SPM_MCNT_AIE_SHIFT) | \
    ((u32)(term) << REG_SPM_MCNT_TERM_SHIFT) | \
    ((u32)(mode) << REG_SPM_MCNT_MODE_SHIFT) | \
    ((u32)(ireq_en) << REG_SPM_MCNT_IREQ_EN_SHIFT) | \
    ((u32)(rt) << REG_SPM_MCNT_RT_SHIFT))
#endif


/* MTIM */

#define REG_SPM_MTIM_T_SHIFT                               0
#define REG_SPM_MTIM_T_SIZE                                24
#define REG_SPM_MTIM_T_MASK                                0x00ffffff

#ifndef SDK_ASM
#define REG_SPM_MTIM_FIELD( t ) \
    (u32)( \
    ((u32)(t) << REG_SPM_MTIM_T_SHIFT))
#endif


/* MSTRG */

/* MSAVE */

#define REG_SPM_MSAVE_FULL_SHIFT                           31
#define REG_SPM_MSAVE_FULL_SIZE                            1
#define REG_SPM_MSAVE_FULL_MASK                            0x80000000

#define REG_SPM_MSAVE_E_SHIFT                              16
#define REG_SPM_MSAVE_E_SIZE                               6
#define REG_SPM_MSAVE_E_MASK                               0x003f0000

#define REG_SPM_MSAVE_S_SHIFT                              0
#define REG_SPM_MSAVE_S_SIZE                               6
#define REG_SPM_MSAVE_S_MASK                               0x0000003f

#ifndef SDK_ASM
#define REG_SPM_MSAVE_FIELD( full, e, s ) \
    (u32)( \
    ((u32)(full) << REG_SPM_MSAVE_FULL_SHIFT) | \
    ((u32)(e) << REG_SPM_MSAVE_E_SHIFT) | \
    ((u32)(s) << REG_SPM_MSAVE_S_SHIFT))
#endif


/* MIF */

#define REG_SPM_MIF_AIF_SHIFT                              1
#define REG_SPM_MIF_AIF_SIZE                               1
#define REG_SPM_MIF_AIF_MASK                               0x00000002

#define REG_SPM_MIF_DIF_SHIFT                              0
#define REG_SPM_MIF_DIF_SIZE                               1
#define REG_SPM_MIF_DIF_MASK                               0x00000001

#ifndef SDK_ASM
#define REG_SPM_MIF_FIELD( aif, dif ) \
    (u32)( \
    ((u32)(aif) << REG_SPM_MIF_AIF_SHIFT) | \
    ((u32)(dif) << REG_SPM_MIF_DIF_SHIFT))
#endif


/* WPRIO */

#define REG_SPM_WPRIO_WP_SHIFT                             0
#define REG_SPM_WPRIO_WP_SIZE                              20
#define REG_SPM_WPRIO_WP_MASK                              0x000fffff

#ifndef SDK_ASM
#define REG_SPM_WPRIO_FIELD( wp ) \
    (u32)( \
    ((u32)(wp) << REG_SPM_WPRIO_WP_SHIFT))
#endif


/* C00CNT */

#define REG_SPM_C00CNT_E_SHIFT                             31
#define REG_SPM_C00CNT_E_SIZE                              1
#define REG_SPM_C00CNT_E_MASK                              0x80000000

#define REG_SPM_C00CNT_IE_SHIFT                            30
#define REG_SPM_C00CNT_IE_SIZE                             1
#define REG_SPM_C00CNT_IE_MASK                             0x40000000

#define REG_SPM_C00CNT_OVF_SHIFT                           16
#define REG_SPM_C00CNT_OVF_SIZE                            5
#define REG_SPM_C00CNT_OVF_MASK                            0x001f0000

#define REG_SPM_C00CNT_C_SEL_SHIFT                         12
#define REG_SPM_C00CNT_C_SEL_SIZE                          2
#define REG_SPM_C00CNT_C_SEL_MASK                          0x00003000

#define REG_SPM_C00CNT_MP_SHIFT                            8
#define REG_SPM_C00CNT_MP_SIZE                             3
#define REG_SPM_C00CNT_MP_MASK                             0x00000700

#define REG_SPM_C00CNT_M_SEL_SHIFT                         0
#define REG_SPM_C00CNT_M_SEL_SIZE                          5
#define REG_SPM_C00CNT_M_SEL_MASK                          0x0000001f

#ifndef SDK_ASM
#define REG_SPM_C00CNT_FIELD( e, ie, ovf, c_sel, mp, m_sel ) \
    (u32)( \
    ((u32)(e) << REG_SPM_C00CNT_E_SHIFT) | \
    ((u32)(ie) << REG_SPM_C00CNT_IE_SHIFT) | \
    ((u32)(ovf) << REG_SPM_C00CNT_OVF_SHIFT) | \
    ((u32)(c_sel) << REG_SPM_C00CNT_C_SEL_SHIFT) | \
    ((u32)(mp) << REG_SPM_C00CNT_MP_SHIFT) | \
    ((u32)(m_sel) << REG_SPM_C00CNT_M_SEL_SHIFT))
#endif


/* C00STAT */

#define REG_SPM_C00STAT_ERR_SHIFT                          0
#define REG_SPM_C00STAT_ERR_SIZE                           1
#define REG_SPM_C00STAT_ERR_MASK                           0x00000001

#ifndef SDK_ASM
#define REG_SPM_C00STAT_FIELD( err ) \
    (u32)( \
    ((u32)(err) << REG_SPM_C00STAT_ERR_SHIFT))
#endif


/* C00CDT0 */

#define REG_SPM_C00CDT0_ADDR_SHIFT                         12
#define REG_SPM_C00CDT0_ADDR_SIZE                          20
#define REG_SPM_C00CDT0_ADDR_MASK                          0xfffff000

#ifndef SDK_ASM
#define REG_SPM_C00CDT0_FIELD( addr ) \
    (u32)( \
    ((u32)(addr) << REG_SPM_C00CDT0_ADDR_SHIFT))
#endif


/* C00CDT1 */

#define REG_SPM_C00CDT1_ADDR_SHIFT                         12
#define REG_SPM_C00CDT1_ADDR_SIZE                          20
#define REG_SPM_C00CDT1_ADDR_MASK                          0xfffff000

#ifndef SDK_ASM
#define REG_SPM_C00CDT1_FIELD( addr ) \
    (u32)( \
    ((u32)(addr) << REG_SPM_C00CDT1_ADDR_SHIFT))
#endif


/* C00CDT2 */

#define REG_SPM_C00CDT2_SIZE64_SHIFT                       27
#define REG_SPM_C00CDT2_SIZE64_SIZE                        1
#define REG_SPM_C00CDT2_SIZE64_MASK                        0x08000000

#define REG_SPM_C00CDT2_SIZE32_SHIFT                       26
#define REG_SPM_C00CDT2_SIZE32_SIZE                        1
#define REG_SPM_C00CDT2_SIZE32_MASK                        0x04000000

#define REG_SPM_C00CDT2_SIZE16_SHIFT                       25
#define REG_SPM_C00CDT2_SIZE16_SIZE                        1
#define REG_SPM_C00CDT2_SIZE16_MASK                        0x02000000

#define REG_SPM_C00CDT2_SIZE8_SHIFT                        24
#define REG_SPM_C00CDT2_SIZE8_SIZE                         1
#define REG_SPM_C00CDT2_SIZE8_MASK                         0x01000000

#define REG_SPM_C00CDT2_WRAP_SHIFT                         22
#define REG_SPM_C00CDT2_WRAP_SIZE                          1
#define REG_SPM_C00CDT2_WRAP_MASK                          0x00400000

#define REG_SPM_C00CDT2_INC_SHIFT                          21
#define REG_SPM_C00CDT2_INC_SIZE                           1
#define REG_SPM_C00CDT2_INC_MASK                           0x00200000

#define REG_SPM_C00CDT2_FIX_SHIFT                          20
#define REG_SPM_C00CDT2_FIX_SIZE                           1
#define REG_SPM_C00CDT2_FIX_MASK                           0x00100000

#define REG_SPM_C00CDT2_LOCK_SHIFT                         18
#define REG_SPM_C00CDT2_LOCK_SIZE                          1
#define REG_SPM_C00CDT2_LOCK_MASK                          0x00040000

#define REG_SPM_C00CDT2_EX_SHIFT                           17
#define REG_SPM_C00CDT2_EX_SIZE                            1
#define REG_SPM_C00CDT2_EX_MASK                            0x00020000

#define REG_SPM_C00CDT2_NML_SHIFT                          16
#define REG_SPM_C00CDT2_NML_SIZE                           1
#define REG_SPM_C00CDT2_NML_MASK                           0x00010000

#define REG_SPM_C00CDT2_LEN_SHIFT                          0
#define REG_SPM_C00CDT2_LEN_SIZE                           16
#define REG_SPM_C00CDT2_LEN_MASK                           0x0000ffff

#ifndef SDK_ASM
#define REG_SPM_C00CDT2_FIELD( size64, size32, size16, size8, wrap, inc, fix, lock, ex, nml, len ) \
    (u32)( \
    ((u32)(size64) << REG_SPM_C00CDT2_SIZE64_SHIFT) | \
    ((u32)(size32) << REG_SPM_C00CDT2_SIZE32_SHIFT) | \
    ((u32)(size16) << REG_SPM_C00CDT2_SIZE16_SHIFT) | \
    ((u32)(size8) << REG_SPM_C00CDT2_SIZE8_SHIFT) | \
    ((u32)(wrap) << REG_SPM_C00CDT2_WRAP_SHIFT) | \
    ((u32)(inc) << REG_SPM_C00CDT2_INC_SHIFT) | \
    ((u32)(fix) << REG_SPM_C00CDT2_FIX_SHIFT) | \
    ((u32)(lock) << REG_SPM_C00CDT2_LOCK_SHIFT) | \
    ((u32)(ex) << REG_SPM_C00CDT2_EX_SHIFT) | \
    ((u32)(nml) << REG_SPM_C00CDT2_NML_SHIFT) | \
    ((u32)(len) << REG_SPM_C00CDT2_LEN_SHIFT))
#endif


/* C00CDT3 */

#define REG_SPM_C00CDT3_TB_MAX_SHIFT                       25
#define REG_SPM_C00CDT3_TB_MAX_SIZE                        7
#define REG_SPM_C00CDT3_TB_MAX_MASK                        0xfe000000

#define REG_SPM_C00CDT3_TL_MAX_M_SHIFT                     19
#define REG_SPM_C00CDT3_TL_MAX_M_SIZE                      6
#define REG_SPM_C00CDT3_TL_MAX_M_MASK                      0x01f80000

#define REG_SPM_C00CDT3_TL_MAX_E_SHIFT                     16
#define REG_SPM_C00CDT3_TL_MAX_E_SIZE                      3
#define REG_SPM_C00CDT3_TL_MAX_E_MASK                      0x00070000

#define REG_SPM_C00CDT3_TB_MIN_SHIFT                       9
#define REG_SPM_C00CDT3_TB_MIN_SIZE                        7
#define REG_SPM_C00CDT3_TB_MIN_MASK                        0x0000fe00

#define REG_SPM_C00CDT3_TL_MIN_M_SHIFT                     3
#define REG_SPM_C00CDT3_TL_MIN_M_SIZE                      6
#define REG_SPM_C00CDT3_TL_MIN_M_MASK                      0x000001f8

#define REG_SPM_C00CDT3_TL_MIN_E_SHIFT                     0
#define REG_SPM_C00CDT3_TL_MIN_E_SIZE                      3
#define REG_SPM_C00CDT3_TL_MIN_E_MASK                      0x00000007

#ifndef SDK_ASM
#define REG_SPM_C00CDT3_FIELD( tb_max, tl_max_m, tl_max_e, tb_min, tl_min_m, tl_min_e ) \
    (u32)( \
    ((u32)(tb_max) << REG_SPM_C00CDT3_TB_MAX_SHIFT) | \
    ((u32)(tl_max_m) << REG_SPM_C00CDT3_TL_MAX_M_SHIFT) | \
    ((u32)(tl_max_e) << REG_SPM_C00CDT3_TL_MAX_E_SHIFT) | \
    ((u32)(tb_min) << REG_SPM_C00CDT3_TB_MIN_SHIFT) | \
    ((u32)(tl_min_m) << REG_SPM_C00CDT3_TL_MIN_M_SHIFT) | \
    ((u32)(tl_min_e) << REG_SPM_C00CDT3_TL_MIN_E_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_EIU_MPCORE_IOREG_EIUPATCH_SPM_H_ */
#endif
