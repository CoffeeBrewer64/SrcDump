/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TS/MPCore/ioreg_tspatch_CAM.h

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
#ifndef NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_CAM_H_
#define NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_CAM_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* CAM1_CNT */

#define REG_CAM1_CNT_OFFSET                                0x120000
#define REG_CAM1_CNT_ADDR                                  (HW_REG_BASE + REG_CAM1_CNT_OFFSET)
#define reg_CAM_CAM1_CNT                                   (*( REGType16v *) REG_CAM1_CNT_ADDR)

/* CAM1_FCNT */

#define REG_CAM1_FCNT_OFFSET                               0x120004
#define REG_CAM1_FCNT_ADDR                                 (HW_REG_BASE + REG_CAM1_FCNT_OFFSET)
#define reg_CAM_CAM1_FCNT                                  (*( REGType32v *) REG_CAM1_FCNT_ADDR)

/* CAM1_SOFS */

#define REG_CAM1_SOFS_OFFSET                               0x120010
#define REG_CAM1_SOFS_ADDR                                 (HW_REG_BASE + REG_CAM1_SOFS_OFFSET)
#define reg_CAM_CAM1_SOFS                                  (*( REGType32v *) REG_CAM1_SOFS_ADDR)

/* CAM1_EOFS */

#define REG_CAM1_EOFS_OFFSET                               0x120014
#define REG_CAM1_EOFS_ADDR                                 (HW_REG_BASE + REG_CAM1_EOFS_OFFSET)
#define reg_CAM_CAM1_EOFS                                  (*( REGType32v *) REG_CAM1_EOFS_ADDR)

/* CAM1_DAT */

#define REG_CAM1_DAT_OFFSET                                0x320000
#define REG_CAM1_DAT_ADDR                                  (HW_REG_BASE + REG_CAM1_DAT_OFFSET)
#define reg_CAM_CAM1_DAT                                   (*( REGType64v *) REG_CAM1_DAT_ADDR)

/* CAM2_CNT */

#define REG_CAM2_CNT_OFFSET                                0x121000
#define REG_CAM2_CNT_ADDR                                  (HW_REG_BASE + REG_CAM2_CNT_OFFSET)
#define reg_CAM_CAM2_CNT                                   (*( REGType16v *) REG_CAM2_CNT_ADDR)

/* CAM2_FCNT */

#define REG_CAM2_FCNT_OFFSET                               0x121004
#define REG_CAM2_FCNT_ADDR                                 (HW_REG_BASE + REG_CAM2_FCNT_OFFSET)
#define reg_CAM_CAM2_FCNT                                  (*( REGType32v *) REG_CAM2_FCNT_ADDR)

/* CAM2_SOFS */

#define REG_CAM2_SOFS_OFFSET                               0x121010
#define REG_CAM2_SOFS_ADDR                                 (HW_REG_BASE + REG_CAM2_SOFS_OFFSET)
#define reg_CAM_CAM2_SOFS                                  (*( REGType32v *) REG_CAM2_SOFS_ADDR)

/* CAM2_EOFS */

#define REG_CAM2_EOFS_OFFSET                               0x121014
#define REG_CAM2_EOFS_ADDR                                 (HW_REG_BASE + REG_CAM2_EOFS_OFFSET)
#define reg_CAM_CAM2_EOFS                                  (*( REGType32v *) REG_CAM2_EOFS_ADDR)

/* CAM2_DAT */

#define REG_CAM2_DAT_OFFSET                                0x321000
#define REG_CAM2_DAT_ADDR                                  (HW_REG_BASE + REG_CAM2_DAT_OFFSET)
#define reg_CAM_CAM2_DAT                                   (*( REGType64v *) REG_CAM2_DAT_ADDR)


/*
 * Definitions of Register fields
 */


/* CAM1_CNT */

#define REG_CAM_CAM1_CNT_E_SHIFT                           15
#define REG_CAM_CAM1_CNT_E_SIZE                            1
#define REG_CAM_CAM1_CNT_E_MASK                            0x8000

#define REG_CAM_CAM1_CNT_DREQ_EN_SHIFT                     14
#define REG_CAM_CAM1_CNT_DREQ_EN_SIZE                      1
#define REG_CAM_CAM1_CNT_DREQ_EN_MASK                      0x4000

#define REG_CAM_CAM1_CNT_T_SHIFT                           13
#define REG_CAM_CAM1_CNT_T_SIZE                            1
#define REG_CAM_CAM1_CNT_T_MASK                            0x2000

#define REG_CAM_CAM1_CNT_IREQDT_SHIFT                      11
#define REG_CAM_CAM1_CNT_IREQDT_SIZE                       1
#define REG_CAM_CAM1_CNT_IREQDT_MASK                       0x0800

#define REG_CAM_CAM1_CNT_IREQBE_SHIFT                      10
#define REG_CAM_CAM1_CNT_IREQBE_SIZE                       1
#define REG_CAM_CAM1_CNT_IREQBE_MASK                       0x0400

#define REG_CAM_CAM1_CNT_IREQVS_SHIFT                      8
#define REG_CAM_CAM1_CNT_IREQVS_SIZE                       2
#define REG_CAM_CAM1_CNT_IREQVS_MASK                       0x0300

#define REG_CAM_CAM1_CNT_VIO_ON_SHIFT                      4
#define REG_CAM_CAM1_CNT_VIO_ON_SIZE                       1
#define REG_CAM_CAM1_CNT_VIO_ON_MASK                       0x0010

#define REG_CAM_CAM1_CNT_POL_RCLK_SHIFT                    3
#define REG_CAM_CAM1_CNT_POL_RCLK_SIZE                     1
#define REG_CAM_CAM1_CNT_POL_RCLK_MASK                     0x0008

#define REG_CAM_CAM1_CNT_POL_HV_SHIFT                      2
#define REG_CAM_CAM1_CNT_POL_HV_SIZE                       1
#define REG_CAM_CAM1_CNT_POL_HV_MASK                       0x0004

#define REG_CAM_CAM1_CNT_VSY_SHIFT                         1
#define REG_CAM_CAM1_CNT_VSY_SIZE                          1
#define REG_CAM_CAM1_CNT_VSY_MASK                          0x0002

#define REG_CAM_CAM1_CNT_HSY_SHIFT                         0
#define REG_CAM_CAM1_CNT_HSY_SIZE                          1
#define REG_CAM_CAM1_CNT_HSY_MASK                          0x0001

#ifndef SDK_ASM
#define REG_CAM_CAM1_CNT_FIELD( e, dreq_en, t, ireqdt, ireqbe, ireqvs, vio_on, pol_rclk, pol_hv, vsy, hsy ) \
    (u16)( \
    ((u32)(e) << REG_CAM_CAM1_CNT_E_SHIFT) | \
    ((u32)(dreq_en) << REG_CAM_CAM1_CNT_DREQ_EN_SHIFT) | \
    ((u32)(t) << REG_CAM_CAM1_CNT_T_SHIFT) | \
    ((u32)(ireqdt) << REG_CAM_CAM1_CNT_IREQDT_SHIFT) | \
    ((u32)(ireqbe) << REG_CAM_CAM1_CNT_IREQBE_SHIFT) | \
    ((u32)(ireqvs) << REG_CAM_CAM1_CNT_IREQVS_SHIFT) | \
    ((u32)(vio_on) << REG_CAM_CAM1_CNT_VIO_ON_SHIFT) | \
    ((u32)(pol_rclk) << REG_CAM_CAM1_CNT_POL_RCLK_SHIFT) | \
    ((u32)(pol_hv) << REG_CAM_CAM1_CNT_POL_HV_SHIFT) | \
    ((u32)(vsy) << REG_CAM_CAM1_CNT_VSY_SHIFT) | \
    ((u32)(hsy) << REG_CAM_CAM1_CNT_HSY_SHIFT))
#endif


/* CAM1_FCNT */

#define REG_CAM_CAM1_FCNT_CLR_SHIFT                        31
#define REG_CAM_CAM1_FCNT_CLR_SIZE                         1
#define REG_CAM_CAM1_FCNT_CLR_MASK                         0x80000000

#define REG_CAM_CAM1_FCNT_DIREQ_THR_SHIFT                  16
#define REG_CAM_CAM1_FCNT_DIREQ_THR_SIZE                   6
#define REG_CAM_CAM1_FCNT_DIREQ_THR_MASK                   0x003f0000

#define REG_CAM_CAM1_FCNT_ERR_SHIFT                        15
#define REG_CAM_CAM1_FCNT_ERR_SIZE                         1
#define REG_CAM_CAM1_FCNT_ERR_MASK                         0x00008000

#define REG_CAM_CAM1_FCNT_COUNT_SHIFT                      0
#define REG_CAM_CAM1_FCNT_COUNT_SIZE                       11
#define REG_CAM_CAM1_FCNT_COUNT_MASK                       0x000007ff

#ifndef SDK_ASM
#define REG_CAM_CAM1_FCNT_FIELD( clr, direq_thr, err, count ) \
    (u32)( \
    ((u32)(clr) << REG_CAM_CAM1_FCNT_CLR_SHIFT) | \
    ((u32)(direq_thr) << REG_CAM_CAM1_FCNT_DIREQ_THR_SHIFT) | \
    ((u32)(err) << REG_CAM_CAM1_FCNT_ERR_SHIFT) | \
    ((u32)(count) << REG_CAM_CAM1_FCNT_COUNT_SHIFT))
#endif


/* CAM1_SOFS */

#define REG_CAM_CAM1_SOFS_VOFS_SHIFT                       16
#define REG_CAM_CAM1_SOFS_VOFS_SIZE                        9
#define REG_CAM_CAM1_SOFS_VOFS_MASK                        0x01ff0000

#define REG_CAM_CAM1_SOFS_HOFS_SHIFT                       0
#define REG_CAM_CAM1_SOFS_HOFS_SIZE                        10
#define REG_CAM_CAM1_SOFS_HOFS_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_CAM_CAM1_SOFS_FIELD( vofs, hofs ) \
    (u32)( \
    ((u32)(vofs) << REG_CAM_CAM1_SOFS_VOFS_SHIFT) | \
    ((u32)(hofs) << REG_CAM_CAM1_SOFS_HOFS_SHIFT))
#endif


/* CAM1_EOFS */

#define REG_CAM_CAM1_EOFS_VOFS_SHIFT                       16
#define REG_CAM_CAM1_EOFS_VOFS_SIZE                        9
#define REG_CAM_CAM1_EOFS_VOFS_MASK                        0x01ff0000

#define REG_CAM_CAM1_EOFS_HOFS_SHIFT                       0
#define REG_CAM_CAM1_EOFS_HOFS_SIZE                        10
#define REG_CAM_CAM1_EOFS_HOFS_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_CAM_CAM1_EOFS_FIELD( vofs, hofs ) \
    (u32)( \
    ((u32)(vofs) << REG_CAM_CAM1_EOFS_VOFS_SHIFT) | \
    ((u32)(hofs) << REG_CAM_CAM1_EOFS_HOFS_SHIFT))
#endif


/* CAM1_DAT */

#define REG_CAM_CAM1_DAT_H_SHIFT                           32
#define REG_CAM_CAM1_DAT_H_SIZE                            32
#define REG_CAM_CAM1_DAT_H_MASK                            0xffffffff00000000

#define REG_CAM_CAM1_DAT_L_SHIFT                           0
#define REG_CAM_CAM1_DAT_L_SIZE                            32
#define REG_CAM_CAM1_DAT_L_MASK                            0x00000000ffffffff

#ifndef SDK_ASM
#define REG_CAM_CAM1_DAT_FIELD( h, l ) \
    (u64)( \
    ((u32)(h) << REG_CAM_CAM1_DAT_H_SHIFT) | \
    ((u32)(l) << REG_CAM_CAM1_DAT_L_SHIFT))
#endif


/* CAM2_CNT */

#define REG_CAM_CAM2_CNT_E_SHIFT                           15
#define REG_CAM_CAM2_CNT_E_SIZE                            1
#define REG_CAM_CAM2_CNT_E_MASK                            0x8000

#define REG_CAM_CAM2_CNT_DREQ_EN_SHIFT                     14
#define REG_CAM_CAM2_CNT_DREQ_EN_SIZE                      1
#define REG_CAM_CAM2_CNT_DREQ_EN_MASK                      0x4000

#define REG_CAM_CAM2_CNT_T_SHIFT                           13
#define REG_CAM_CAM2_CNT_T_SIZE                            1
#define REG_CAM_CAM2_CNT_T_MASK                            0x2000

#define REG_CAM_CAM2_CNT_IREQDT_SHIFT                      11
#define REG_CAM_CAM2_CNT_IREQDT_SIZE                       1
#define REG_CAM_CAM2_CNT_IREQDT_MASK                       0x0800

#define REG_CAM_CAM2_CNT_IREQBE_SHIFT                      10
#define REG_CAM_CAM2_CNT_IREQBE_SIZE                       1
#define REG_CAM_CAM2_CNT_IREQBE_MASK                       0x0400

#define REG_CAM_CAM2_CNT_IREQVS_SHIFT                      8
#define REG_CAM_CAM2_CNT_IREQVS_SIZE                       2
#define REG_CAM_CAM2_CNT_IREQVS_MASK                       0x0300

#define REG_CAM_CAM2_CNT_VIO_ON_SHIFT                      4
#define REG_CAM_CAM2_CNT_VIO_ON_SIZE                       1
#define REG_CAM_CAM2_CNT_VIO_ON_MASK                       0x0010

#define REG_CAM_CAM2_CNT_POL_RCLK_SHIFT                    3
#define REG_CAM_CAM2_CNT_POL_RCLK_SIZE                     1
#define REG_CAM_CAM2_CNT_POL_RCLK_MASK                     0x0008

#define REG_CAM_CAM2_CNT_POL_HV_SHIFT                      2
#define REG_CAM_CAM2_CNT_POL_HV_SIZE                       1
#define REG_CAM_CAM2_CNT_POL_HV_MASK                       0x0004

#define REG_CAM_CAM2_CNT_VSY_SHIFT                         1
#define REG_CAM_CAM2_CNT_VSY_SIZE                          1
#define REG_CAM_CAM2_CNT_VSY_MASK                          0x0002

#define REG_CAM_CAM2_CNT_HSY_SHIFT                         0
#define REG_CAM_CAM2_CNT_HSY_SIZE                          1
#define REG_CAM_CAM2_CNT_HSY_MASK                          0x0001

#ifndef SDK_ASM
#define REG_CAM_CAM2_CNT_FIELD( e, dreq_en, t, ireqdt, ireqbe, ireqvs, vio_on, pol_rclk, pol_hv, vsy, hsy ) \
    (u16)( \
    ((u32)(e) << REG_CAM_CAM2_CNT_E_SHIFT) | \
    ((u32)(dreq_en) << REG_CAM_CAM2_CNT_DREQ_EN_SHIFT) | \
    ((u32)(t) << REG_CAM_CAM2_CNT_T_SHIFT) | \
    ((u32)(ireqdt) << REG_CAM_CAM2_CNT_IREQDT_SHIFT) | \
    ((u32)(ireqbe) << REG_CAM_CAM2_CNT_IREQBE_SHIFT) | \
    ((u32)(ireqvs) << REG_CAM_CAM2_CNT_IREQVS_SHIFT) | \
    ((u32)(vio_on) << REG_CAM_CAM2_CNT_VIO_ON_SHIFT) | \
    ((u32)(pol_rclk) << REG_CAM_CAM2_CNT_POL_RCLK_SHIFT) | \
    ((u32)(pol_hv) << REG_CAM_CAM2_CNT_POL_HV_SHIFT) | \
    ((u32)(vsy) << REG_CAM_CAM2_CNT_VSY_SHIFT) | \
    ((u32)(hsy) << REG_CAM_CAM2_CNT_HSY_SHIFT))
#endif


/* CAM2_FCNT */

#define REG_CAM_CAM2_FCNT_CLR_SHIFT                        31
#define REG_CAM_CAM2_FCNT_CLR_SIZE                         1
#define REG_CAM_CAM2_FCNT_CLR_MASK                         0x80000000

#define REG_CAM_CAM2_FCNT_DIREQ_THR_SHIFT                  16
#define REG_CAM_CAM2_FCNT_DIREQ_THR_SIZE                   6
#define REG_CAM_CAM2_FCNT_DIREQ_THR_MASK                   0x003f0000

#define REG_CAM_CAM2_FCNT_ERR_SHIFT                        15
#define REG_CAM_CAM2_FCNT_ERR_SIZE                         1
#define REG_CAM_CAM2_FCNT_ERR_MASK                         0x00008000

#define REG_CAM_CAM2_FCNT_COUNT_SHIFT                      0
#define REG_CAM_CAM2_FCNT_COUNT_SIZE                       11
#define REG_CAM_CAM2_FCNT_COUNT_MASK                       0x000007ff

#ifndef SDK_ASM
#define REG_CAM_CAM2_FCNT_FIELD( clr, direq_thr, err, count ) \
    (u32)( \
    ((u32)(clr) << REG_CAM_CAM2_FCNT_CLR_SHIFT) | \
    ((u32)(direq_thr) << REG_CAM_CAM2_FCNT_DIREQ_THR_SHIFT) | \
    ((u32)(err) << REG_CAM_CAM2_FCNT_ERR_SHIFT) | \
    ((u32)(count) << REG_CAM_CAM2_FCNT_COUNT_SHIFT))
#endif


/* CAM2_SOFS */

#define REG_CAM_CAM2_SOFS_VOFS_SHIFT                       16
#define REG_CAM_CAM2_SOFS_VOFS_SIZE                        9
#define REG_CAM_CAM2_SOFS_VOFS_MASK                        0x01ff0000

#define REG_CAM_CAM2_SOFS_HOFS_SHIFT                       0
#define REG_CAM_CAM2_SOFS_HOFS_SIZE                        10
#define REG_CAM_CAM2_SOFS_HOFS_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_CAM_CAM2_SOFS_FIELD( vofs, hofs ) \
    (u32)( \
    ((u32)(vofs) << REG_CAM_CAM2_SOFS_VOFS_SHIFT) | \
    ((u32)(hofs) << REG_CAM_CAM2_SOFS_HOFS_SHIFT))
#endif


/* CAM2_EOFS */

#define REG_CAM_CAM2_EOFS_VOFS_SHIFT                       16
#define REG_CAM_CAM2_EOFS_VOFS_SIZE                        9
#define REG_CAM_CAM2_EOFS_VOFS_MASK                        0x01ff0000

#define REG_CAM_CAM2_EOFS_HOFS_SHIFT                       0
#define REG_CAM_CAM2_EOFS_HOFS_SIZE                        10
#define REG_CAM_CAM2_EOFS_HOFS_MASK                        0x000003ff

#ifndef SDK_ASM
#define REG_CAM_CAM2_EOFS_FIELD( vofs, hofs ) \
    (u32)( \
    ((u32)(vofs) << REG_CAM_CAM2_EOFS_VOFS_SHIFT) | \
    ((u32)(hofs) << REG_CAM_CAM2_EOFS_HOFS_SHIFT))
#endif


/* CAM2_DAT */

#define REG_CAM_CAM2_DAT_H_SHIFT                           32
#define REG_CAM_CAM2_DAT_H_SIZE                            32
#define REG_CAM_CAM2_DAT_H_MASK                            0xffffffff00000000

#define REG_CAM_CAM2_DAT_L_SHIFT                           0
#define REG_CAM_CAM2_DAT_L_SIZE                            32
#define REG_CAM_CAM2_DAT_L_MASK                            0x00000000ffffffff

#ifndef SDK_ASM
#define REG_CAM_CAM2_DAT_FIELD( h, l ) \
    (u64)( \
    ((u32)(h) << REG_CAM_CAM2_DAT_H_SHIFT) | \
    ((u32)(l) << REG_CAM_CAM2_DAT_L_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TS_MPCORE_IOREG_TSPATCH_CAM_H_ */
#endif
