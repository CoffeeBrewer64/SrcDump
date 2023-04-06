/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/ARM9/ioreg_PXI.h

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
#ifndef NN_HW_CTR_TEG2_ARM9_IOREG_PXI_H_
#define NN_HW_CTR_TEG2_ARM9_IOREG_PXI_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* MAINPINTF */

#define REG_MAINPINTF_OFFSET                               0x8000
#define REG_MAINPINTF_ADDR                                 (HW_REG_BASE + REG_MAINPINTF_OFFSET)
#define reg_PXI_MAINPINTF                                  (*( REGType32v *) REG_MAINPINTF_ADDR)

/* MAINP_FIFO_CNT */

#define REG_MAINP_FIFO_CNT_OFFSET                          0x8004
#define REG_MAINP_FIFO_CNT_ADDR                            (HW_REG_BASE + REG_MAINP_FIFO_CNT_OFFSET)
#define reg_PXI_MAINP_FIFO_CNT                             (*( REGType16v *) REG_MAINP_FIFO_CNT_ADDR)

/* SEND_FIFO */

#define REG_SEND_FIFO_OFFSET                               0x8008
#define REG_SEND_FIFO_ADDR                                 (HW_REG_BASE + REG_SEND_FIFO_OFFSET)
#define reg_PXI_SEND_FIFO                                  (*( REGType32v *) REG_SEND_FIFO_ADDR)

/* RECV_FIFO */

#define REG_RECV_FIFO_OFFSET                               0x800c
#define REG_RECV_FIFO_ADDR                                 (HW_REG_BASE + REG_RECV_FIFO_OFFSET)
#define reg_PXI_RECV_FIFO                                  (*( REGType32v *) REG_RECV_FIFO_ADDR)

/* MAINPINTF_RECV */

#define REG_MAINPINTF_RECV_OFFSET                          0x8000
#define REG_MAINPINTF_RECV_ADDR                            (HW_REG_BASE + REG_MAINPINTF_RECV_OFFSET)
#define reg_PXI_MAINPINTF_RECV                             (*(const REGType8v *) REG_MAINPINTF_RECV_ADDR)

/* MAINPINTF_SEND */

#define REG_MAINPINTF_SEND_OFFSET                          0x8001
#define REG_MAINPINTF_SEND_ADDR                            (HW_REG_BASE + REG_MAINPINTF_SEND_OFFSET)
#define reg_PXI_MAINPINTF_SEND                             (*( REGType8v *) REG_MAINPINTF_SEND_ADDR)

/* MAINPINTF_CNT */

#define REG_MAINPINTF_CNT_OFFSET                           0x8003
#define REG_MAINPINTF_CNT_ADDR                             (HW_REG_BASE + REG_MAINPINTF_CNT_OFFSET)
#define reg_PXI_MAINPINTF_CNT                              (*( REGType8v *) REG_MAINPINTF_CNT_ADDR)


/*
 * Definitions of Register fields
 */


/* MAINPINTF */

#define REG_PXI_MAINPINTF_I_SHIFT                          31
#define REG_PXI_MAINPINTF_I_SIZE                           1
#define REG_PXI_MAINPINTF_I_MASK                           0x80000000

#define REG_PXI_MAINPINTF_IREQ1_SHIFT                      30
#define REG_PXI_MAINPINTF_IREQ1_SIZE                       1
#define REG_PXI_MAINPINTF_IREQ1_MASK                       0x40000000

#define REG_PXI_MAINPINTF_IREQ0_SHIFT                      29
#define REG_PXI_MAINPINTF_IREQ0_SIZE                       1
#define REG_PXI_MAINPINTF_IREQ0_MASK                       0x20000000

#define REG_PXI_MAINPINTF_A9STATUS_SHIFT                   8
#define REG_PXI_MAINPINTF_A9STATUS_SIZE                    8
#define REG_PXI_MAINPINTF_A9STATUS_MASK                    0x0000ff00

#define REG_PXI_MAINPINTF_A11STATUS_SHIFT                  0
#define REG_PXI_MAINPINTF_A11STATUS_SIZE                   8
#define REG_PXI_MAINPINTF_A11STATUS_MASK                   0x000000ff

#ifndef SDK_ASM
#define REG_PXI_MAINPINTF_FIELD( i, ireq1, ireq0, a9status, a11status ) \
    (u32)( \
    ((u32)(i) << REG_PXI_MAINPINTF_I_SHIFT) | \
    ((u32)(ireq1) << REG_PXI_MAINPINTF_IREQ1_SHIFT) | \
    ((u32)(ireq0) << REG_PXI_MAINPINTF_IREQ0_SHIFT) | \
    ((u32)(a9status) << REG_PXI_MAINPINTF_A9STATUS_SHIFT) | \
    ((u32)(a11status) << REG_PXI_MAINPINTF_A11STATUS_SHIFT))
#endif


/* MAINP_FIFO_CNT */

#define REG_PXI_MAINP_FIFO_CNT_E_SHIFT                     15
#define REG_PXI_MAINP_FIFO_CNT_E_SIZE                      1
#define REG_PXI_MAINP_FIFO_CNT_E_MASK                      0x8000

#define REG_PXI_MAINP_FIFO_CNT_ERR_SHIFT                   14
#define REG_PXI_MAINP_FIFO_CNT_ERR_SIZE                    1
#define REG_PXI_MAINP_FIFO_CNT_ERR_MASK                    0x4000

#define REG_PXI_MAINP_FIFO_CNT_RECV_RI_SHIFT               10
#define REG_PXI_MAINP_FIFO_CNT_RECV_RI_SIZE                1
#define REG_PXI_MAINP_FIFO_CNT_RECV_RI_MASK                0x0400

#define REG_PXI_MAINP_FIFO_CNT_RECV_FULL_SHIFT             9
#define REG_PXI_MAINP_FIFO_CNT_RECV_FULL_SIZE              1
#define REG_PXI_MAINP_FIFO_CNT_RECV_FULL_MASK              0x0200

#define REG_PXI_MAINP_FIFO_CNT_RECV_EMP_SHIFT              8
#define REG_PXI_MAINP_FIFO_CNT_RECV_EMP_SIZE               1
#define REG_PXI_MAINP_FIFO_CNT_RECV_EMP_MASK               0x0100

#define REG_PXI_MAINP_FIFO_CNT_SEND_CL_SHIFT               3
#define REG_PXI_MAINP_FIFO_CNT_SEND_CL_SIZE                1
#define REG_PXI_MAINP_FIFO_CNT_SEND_CL_MASK                0x0008

#define REG_PXI_MAINP_FIFO_CNT_SEND_TI_SHIFT               2
#define REG_PXI_MAINP_FIFO_CNT_SEND_TI_SIZE                1
#define REG_PXI_MAINP_FIFO_CNT_SEND_TI_MASK                0x0004

#define REG_PXI_MAINP_FIFO_CNT_SEND_FULL_SHIFT             1
#define REG_PXI_MAINP_FIFO_CNT_SEND_FULL_SIZE              1
#define REG_PXI_MAINP_FIFO_CNT_SEND_FULL_MASK              0x0002

#define REG_PXI_MAINP_FIFO_CNT_SEND_EMP_SHIFT              0
#define REG_PXI_MAINP_FIFO_CNT_SEND_EMP_SIZE               1
#define REG_PXI_MAINP_FIFO_CNT_SEND_EMP_MASK               0x0001

#ifndef SDK_ASM
#define REG_PXI_MAINP_FIFO_CNT_FIELD( e, err, recv_ri, recv_full, recv_emp, send_cl, send_ti, send_full, send_emp ) \
    (u16)( \
    ((u32)(e) << REG_PXI_MAINP_FIFO_CNT_E_SHIFT) | \
    ((u32)(err) << REG_PXI_MAINP_FIFO_CNT_ERR_SHIFT) | \
    ((u32)(recv_ri) << REG_PXI_MAINP_FIFO_CNT_RECV_RI_SHIFT) | \
    ((u32)(recv_full) << REG_PXI_MAINP_FIFO_CNT_RECV_FULL_SHIFT) | \
    ((u32)(recv_emp) << REG_PXI_MAINP_FIFO_CNT_RECV_EMP_SHIFT) | \
    ((u32)(send_cl) << REG_PXI_MAINP_FIFO_CNT_SEND_CL_SHIFT) | \
    ((u32)(send_ti) << REG_PXI_MAINP_FIFO_CNT_SEND_TI_SHIFT) | \
    ((u32)(send_full) << REG_PXI_MAINP_FIFO_CNT_SEND_FULL_SHIFT) | \
    ((u32)(send_emp) << REG_PXI_MAINP_FIFO_CNT_SEND_EMP_SHIFT))
#endif


/* SEND_FIFO */

/* RECV_FIFO */

/* MAINPINTF_RECV */

/* MAINPINTF_SEND */

/* MAINPINTF_CNT */

#define REG_PXI_MAINPINTF_CNT_I_SHIFT                      7
#define REG_PXI_MAINPINTF_CNT_I_SIZE                       1
#define REG_PXI_MAINPINTF_CNT_I_MASK                       0x80

#define REG_PXI_MAINPINTF_CNT_IREQ1_SHIFT                  6
#define REG_PXI_MAINPINTF_CNT_IREQ1_SIZE                   1
#define REG_PXI_MAINPINTF_CNT_IREQ1_MASK                   0x40

#define REG_PXI_MAINPINTF_CNT_IREQ0_SHIFT                  5
#define REG_PXI_MAINPINTF_CNT_IREQ0_SIZE                   1
#define REG_PXI_MAINPINTF_CNT_IREQ0_MASK                   0x20

#ifndef SDK_ASM
#define REG_PXI_MAINPINTF_CNT_FIELD( i, ireq1, ireq0 ) \
    (u8)( \
    ((u32)(i) << REG_PXI_MAINPINTF_CNT_I_SHIFT) | \
    ((u32)(ireq1) << REG_PXI_MAINPINTF_CNT_IREQ1_SHIFT) | \
    ((u32)(ireq0) << REG_PXI_MAINPINTF_CNT_IREQ0_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_ARM9_IOREG_PXI_H_ */
#endif
