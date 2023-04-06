/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/MPCore/ioreg_CAM.h

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
#ifndef NN_HW_CTR_TEG2_MPCORE_IOREG_CAM_H_
#define NN_HW_CTR_TEG2_MPCORE_IOREG_CAM_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* CAM1_MCNT */

#define REG_CAM1_MCNT_OFFSET                               0x120000
#define REG_CAM1_MCNT_ADDR                                 (HW_REG_BASE + REG_CAM1_MCNT_OFFSET)
#define reg_CAM_CAM1_MCNT                                  (*( REGType16v *) REG_CAM1_MCNT_ADDR)

/* CAM1_CNT */

#define REG_CAM1_CNT_OFFSET                                0x120002
#define REG_CAM1_CNT_ADDR                                  (HW_REG_BASE + REG_CAM1_CNT_OFFSET)
#define reg_CAM_CAM1_CNT                                   (*( REGType16v *) REG_CAM1_CNT_ADDR)

/* CAM1_RPNT */

#define REG_CAM1_RPNT_OFFSET                               0x120008
#define REG_CAM1_RPNT_ADDR                                 (HW_REG_BASE + REG_CAM1_RPNT_OFFSET)
#define reg_CAM_CAM1_RPNT                                  (*(const REGType32v *) REG_CAM1_RPNT_ADDR)

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
#define reg_CAM_CAM1_DAT                                   (*( REGType32v *) REG_CAM1_DAT_ADDR)

/* CAM2_MCNT */

#define REG_CAM2_MCNT_OFFSET                               0x121000
#define REG_CAM2_MCNT_ADDR                                 (HW_REG_BASE + REG_CAM2_MCNT_OFFSET)
#define reg_CAM_CAM2_MCNT                                  (*( REGType16v *) REG_CAM2_MCNT_ADDR)

/* CAM2_CNT */

#define REG_CAM2_CNT_OFFSET                                0x121002
#define REG_CAM2_CNT_ADDR                                  (HW_REG_BASE + REG_CAM2_CNT_OFFSET)
#define reg_CAM_CAM2_CNT                                   (*( REGType16v *) REG_CAM2_CNT_ADDR)

/* CAM2_RPNT */

#define REG_CAM2_RPNT_OFFSET                               0x121008
#define REG_CAM2_RPNT_ADDR                                 (HW_REG_BASE + REG_CAM2_RPNT_OFFSET)
#define reg_CAM_CAM2_RPNT                                  (*(const REGType32v *) REG_CAM2_RPNT_ADDR)

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
#define reg_CAM_CAM2_DAT                                   (*( REGType32v *) REG_CAM2_DAT_ADDR)


/*
 * Definitions of Register fields
 */


/* CAM1_MCNT */

#define REG_CAM_CAM1_MCNT_VSY_SHIFT                        15
#define REG_CAM_CAM1_MCNT_VSY_SIZE                         1
#define REG_CAM_CAM1_MCNT_VSY_MASK                         0x8000

#define REG_CAM_CAM1_MCNT_HSY_SHIFT                        14
#define REG_CAM_CAM1_MCNT_HSY_SIZE                         1
#define REG_CAM_CAM1_MCNT_HSY_MASK                         0x4000

#define REG_CAM_CAM1_MCNT_INI_SHIFT                        7
#define REG_CAM_CAM1_MCNT_INI_SIZE                         1
#define REG_CAM_CAM1_MCNT_INI_MASK                         0x0080

#define REG_CAM_CAM1_MCNT_V28_SHIFT                        6
#define REG_CAM_CAM1_MCNT_V28_SIZE                         1
#define REG_CAM_CAM1_MCNT_V28_MASK                         0x0040

#define REG_CAM_CAM1_MCNT_VIO_SHIFT                        5
#define REG_CAM_CAM1_MCNT_VIO_SIZE                         1
#define REG_CAM_CAM1_MCNT_VIO_MASK                         0x0020

#define REG_CAM_CAM1_MCNT_STBY2_SHIFT                      4
#define REG_CAM_CAM1_MCNT_STBY2_SIZE                       1
#define REG_CAM_CAM1_MCNT_STBY2_MASK                       0x0010

#define REG_CAM_CAM1_MCNT_IRCLK_SHIFT                      3
#define REG_CAM_CAM1_MCNT_IRCLK_SIZE                       1
#define REG_CAM_CAM1_MCNT_IRCLK_MASK                       0x0008

#define REG_CAM_CAM1_MCNT_SYNC_SHIFT                       2
#define REG_CAM_CAM1_MCNT_SYNC_SIZE                        1
#define REG_CAM_CAM1_MCNT_SYNC_MASK                        0x0004

#define REG_CAM_CAM1_MCNT_RST_SHIFT                        1
#define REG_CAM_CAM1_MCNT_RST_SIZE                         1
#define REG_CAM_CAM1_MCNT_RST_MASK                         0x0002

#define REG_CAM_CAM1_MCNT_STBY_SHIFT                       0
#define REG_CAM_CAM1_MCNT_STBY_SIZE                        1
#define REG_CAM_CAM1_MCNT_STBY_MASK                        0x0001

#ifndef SDK_ASM
#define REG_CAM_CAM1_MCNT_FIELD( vsy, hsy, ini, v28, vio, stby2, irclk, sync, rst, stby ) \
    (u16)( \
    ((u32)(vsy) << REG_CAM_CAM1_MCNT_VSY_SHIFT) | \
    ((u32)(hsy) << REG_CAM_CAM1_MCNT_HSY_SHIFT) | \
    ((u32)(ini) << REG_CAM_CAM1_MCNT_INI_SHIFT) | \
    ((u32)(v28) << REG_CAM_CAM1_MCNT_V28_SHIFT) | \
    ((u32)(vio) << REG_CAM_CAM1_MCNT_VIO_SHIFT) | \
    ((u32)(stby2) << REG_CAM_CAM1_MCNT_STBY2_SHIFT) | \
    ((u32)(irclk) << REG_CAM_CAM1_MCNT_IRCLK_SHIFT) | \
    ((u32)(sync) << REG_CAM_CAM1_MCNT_SYNC_SHIFT) | \
    ((u32)(rst) << REG_CAM_CAM1_MCNT_RST_SHIFT) | \
    ((u32)(stby) << REG_CAM_CAM1_MCNT_STBY_SHIFT))
#endif


/* CAM1_CNT */

#define REG_CAM_CAM1_CNT_E_SHIFT                           15
#define REG_CAM_CAM1_CNT_E_SIZE                            1
#define REG_CAM_CAM1_CNT_E_MASK                            0x8000

#define REG_CAM_CAM1_CNT_T_SHIFT                           14
#define REG_CAM_CAM1_CNT_T_SIZE                            1
#define REG_CAM_CAM1_CNT_T_MASK                            0x4000

#define REG_CAM_CAM1_CNT_F_SHIFT                           13
#define REG_CAM_CAM1_CNT_F_SIZE                            1
#define REG_CAM_CAM1_CNT_F_MASK                            0x2000

#define REG_CAM_CAM1_CNT_IREQDT_SHIFT                      12
#define REG_CAM_CAM1_CNT_IREQDT_SIZE                       1
#define REG_CAM_CAM1_CNT_IREQDT_MASK                       0x1000

#define REG_CAM_CAM1_CNT_IREQI_SHIFT                       11
#define REG_CAM_CAM1_CNT_IREQI_SIZE                        1
#define REG_CAM_CAM1_CNT_IREQI_MASK                        0x0800

#define REG_CAM_CAM1_CNT_IREQBE_SHIFT                      10
#define REG_CAM_CAM1_CNT_IREQBE_SIZE                       1
#define REG_CAM_CAM1_CNT_IREQBE_MASK                       0x0400

#define REG_CAM_CAM1_CNT_IREQVS_SHIFT                      8
#define REG_CAM_CAM1_CNT_IREQVS_SIZE                       2
#define REG_CAM_CAM1_CNT_IREQVS_MASK                       0x0300

#define REG_CAM_CAM1_CNT_CL_SHIFT                          5
#define REG_CAM_CAM1_CNT_CL_SIZE                           1
#define REG_CAM_CAM1_CNT_CL_MASK                           0x0020

#define REG_CAM_CAM1_CNT_ERR_SHIFT                         4
#define REG_CAM_CAM1_CNT_ERR_SIZE                          1
#define REG_CAM_CAM1_CNT_ERR_MASK                          0x0010

#define REG_CAM_CAM1_CNT_TL_SHIFT                          0
#define REG_CAM_CAM1_CNT_TL_SIZE                           4
#define REG_CAM_CAM1_CNT_TL_MASK                           0x000f

#ifndef SDK_ASM
#define REG_CAM_CAM1_CNT_FIELD( e, t, f, ireqdt, ireqi, ireqbe, ireqvs, cl, err, tl ) \
    (u16)( \
    ((u32)(e) << REG_CAM_CAM1_CNT_E_SHIFT) | \
    ((u32)(t) << REG_CAM_CAM1_CNT_T_SHIFT) | \
    ((u32)(f) << REG_CAM_CAM1_CNT_F_SHIFT) | \
    ((u32)(ireqdt) << REG_CAM_CAM1_CNT_IREQDT_SHIFT) | \
    ((u32)(ireqi) << REG_CAM_CAM1_CNT_IREQI_SHIFT) | \
    ((u32)(ireqbe) << REG_CAM_CAM1_CNT_IREQBE_SHIFT) | \
    ((u32)(ireqvs) << REG_CAM_CAM1_CNT_IREQVS_SHIFT) | \
    ((u32)(cl) << REG_CAM_CAM1_CNT_CL_SHIFT) | \
    ((u32)(err) << REG_CAM_CAM1_CNT_ERR_SHIFT) | \
    ((u32)(tl) << REG_CAM_CAM1_CNT_TL_SHIFT))
#endif


/* CAM1_RPNT */

#define REG_CAM_CAM1_RPNT_RP_SHIFT                         0
#define REG_CAM_CAM1_RPNT_RP_SIZE                          10
#define REG_CAM_CAM1_RPNT_RP_MASK                          0x000003ff

#ifndef SDK_ASM
#define REG_CAM_CAM1_RPNT_FIELD( rp ) \
    (u32)( \
    ((u32)(rp) << REG_CAM_CAM1_RPNT_RP_SHIFT))
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

/* CAM2_MCNT */

#define REG_CAM_CAM2_MCNT_VSY_SHIFT                        15
#define REG_CAM_CAM2_MCNT_VSY_SIZE                         1
#define REG_CAM_CAM2_MCNT_VSY_MASK                         0x8000

#define REG_CAM_CAM2_MCNT_HSY_SHIFT                        14
#define REG_CAM_CAM2_MCNT_HSY_SIZE                         1
#define REG_CAM_CAM2_MCNT_HSY_MASK                         0x4000

#define REG_CAM_CAM2_MCNT_IRCLK_SHIFT                      3
#define REG_CAM_CAM2_MCNT_IRCLK_SIZE                       1
#define REG_CAM_CAM2_MCNT_IRCLK_MASK                       0x0008

#define REG_CAM_CAM2_MCNT_SYNC_SHIFT                       2
#define REG_CAM_CAM2_MCNT_SYNC_SIZE                        1
#define REG_CAM_CAM2_MCNT_SYNC_MASK                        0x0004

#ifndef SDK_ASM
#define REG_CAM_CAM2_MCNT_FIELD( vsy, hsy, irclk, sync ) \
    (u16)( \
    ((u32)(vsy) << REG_CAM_CAM2_MCNT_VSY_SHIFT) | \
    ((u32)(hsy) << REG_CAM_CAM2_MCNT_HSY_SHIFT) | \
    ((u32)(irclk) << REG_CAM_CAM2_MCNT_IRCLK_SHIFT) | \
    ((u32)(sync) << REG_CAM_CAM2_MCNT_SYNC_SHIFT))
#endif


/* CAM2_CNT */

#define REG_CAM_CAM2_CNT_E_SHIFT                           15
#define REG_CAM_CAM2_CNT_E_SIZE                            1
#define REG_CAM_CAM2_CNT_E_MASK                            0x8000

#define REG_CAM_CAM2_CNT_T_SHIFT                           14
#define REG_CAM_CAM2_CNT_T_SIZE                            1
#define REG_CAM_CAM2_CNT_T_MASK                            0x4000

#define REG_CAM_CAM2_CNT_F_SHIFT                           13
#define REG_CAM_CAM2_CNT_F_SIZE                            1
#define REG_CAM_CAM2_CNT_F_MASK                            0x2000

#define REG_CAM_CAM2_CNT_IREQDT_SHIFT                      12
#define REG_CAM_CAM2_CNT_IREQDT_SIZE                       1
#define REG_CAM_CAM2_CNT_IREQDT_MASK                       0x1000

#define REG_CAM_CAM2_CNT_IREQI_SHIFT                       11
#define REG_CAM_CAM2_CNT_IREQI_SIZE                        1
#define REG_CAM_CAM2_CNT_IREQI_MASK                        0x0800

#define REG_CAM_CAM2_CNT_IREQBE_SHIFT                      10
#define REG_CAM_CAM2_CNT_IREQBE_SIZE                       1
#define REG_CAM_CAM2_CNT_IREQBE_MASK                       0x0400

#define REG_CAM_CAM2_CNT_IREQVS_SHIFT                      8
#define REG_CAM_CAM2_CNT_IREQVS_SIZE                       2
#define REG_CAM_CAM2_CNT_IREQVS_MASK                       0x0300

#define REG_CAM_CAM2_CNT_CL_SHIFT                          5
#define REG_CAM_CAM2_CNT_CL_SIZE                           1
#define REG_CAM_CAM2_CNT_CL_MASK                           0x0020

#define REG_CAM_CAM2_CNT_ERR_SHIFT                         4
#define REG_CAM_CAM2_CNT_ERR_SIZE                          1
#define REG_CAM_CAM2_CNT_ERR_MASK                          0x0010

#define REG_CAM_CAM2_CNT_TL_SHIFT                          0
#define REG_CAM_CAM2_CNT_TL_SIZE                           4
#define REG_CAM_CAM2_CNT_TL_MASK                           0x000f

#ifndef SDK_ASM
#define REG_CAM_CAM2_CNT_FIELD( e, t, f, ireqdt, ireqi, ireqbe, ireqvs, cl, err, tl ) \
    (u16)( \
    ((u32)(e) << REG_CAM_CAM2_CNT_E_SHIFT) | \
    ((u32)(t) << REG_CAM_CAM2_CNT_T_SHIFT) | \
    ((u32)(f) << REG_CAM_CAM2_CNT_F_SHIFT) | \
    ((u32)(ireqdt) << REG_CAM_CAM2_CNT_IREQDT_SHIFT) | \
    ((u32)(ireqi) << REG_CAM_CAM2_CNT_IREQI_SHIFT) | \
    ((u32)(ireqbe) << REG_CAM_CAM2_CNT_IREQBE_SHIFT) | \
    ((u32)(ireqvs) << REG_CAM_CAM2_CNT_IREQVS_SHIFT) | \
    ((u32)(cl) << REG_CAM_CAM2_CNT_CL_SHIFT) | \
    ((u32)(err) << REG_CAM_CAM2_CNT_ERR_SHIFT) | \
    ((u32)(tl) << REG_CAM_CAM2_CNT_TL_SHIFT))
#endif


/* CAM2_RPNT */

#define REG_CAM_CAM2_RPNT_RP_SHIFT                         0
#define REG_CAM_CAM2_RPNT_RP_SIZE                          10
#define REG_CAM_CAM2_RPNT_RP_MASK                          0x000003ff

#ifndef SDK_ASM
#define REG_CAM_CAM2_RPNT_FIELD( rp ) \
    (u32)( \
    ((u32)(rp) << REG_CAM_CAM2_RPNT_RP_SHIFT))
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

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_MPCORE_IOREG_CAM_H_ */
#endif
