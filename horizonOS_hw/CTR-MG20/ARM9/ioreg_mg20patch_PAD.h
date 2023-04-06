/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-MG20/ARM9/ioreg_mg20patch_PAD.h

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
#ifndef NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_PAD_H_
#define NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_PAD_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* KEYINPUT */

#define REG_KEYINPUT_OFFSET                                0x110000
#define REG_KEYINPUT_ADDR                                  (HW_MG20IOP_REG + REG_KEYINPUT_OFFSET)
#define reg_PAD_KEYINPUT                                   (*( REGType16v *) REG_KEYINPUT_ADDR)

/* KEYCNT */

#define REG_KEYCNT_OFFSET                                  0x110004
#define REG_KEYCNT_ADDR                                    (HW_MG20IOP_REG + REG_KEYCNT_OFFSET)
#define reg_PAD_KEYCNT                                     (*( REGType32v *) REG_KEYCNT_ADDR)


/*
 * Definitions of Register fields
 */


/* KEYINPUT */

#define REG_PAD_KEYINPUT_X_SHIFT                           11
#define REG_PAD_KEYINPUT_X_SIZE                            1
#define REG_PAD_KEYINPUT_X_MASK                            0x0800

#define REG_PAD_KEYINPUT_Y_SHIFT                           10
#define REG_PAD_KEYINPUT_Y_SIZE                            1
#define REG_PAD_KEYINPUT_Y_MASK                            0x0400

#define REG_PAD_KEYINPUT_L_SHIFT                           9
#define REG_PAD_KEYINPUT_L_SIZE                            1
#define REG_PAD_KEYINPUT_L_MASK                            0x0200

#define REG_PAD_KEYINPUT_R_SHIFT                           8
#define REG_PAD_KEYINPUT_R_SIZE                            1
#define REG_PAD_KEYINPUT_R_MASK                            0x0100

#define REG_PAD_KEYINPUT_DOWN_SHIFT                        7
#define REG_PAD_KEYINPUT_DOWN_SIZE                         1
#define REG_PAD_KEYINPUT_DOWN_MASK                         0x0080

#define REG_PAD_KEYINPUT_UP_SHIFT                          6
#define REG_PAD_KEYINPUT_UP_SIZE                           1
#define REG_PAD_KEYINPUT_UP_MASK                           0x0040

#define REG_PAD_KEYINPUT_LEFT_SHIFT                        5
#define REG_PAD_KEYINPUT_LEFT_SIZE                         1
#define REG_PAD_KEYINPUT_LEFT_MASK                         0x0020

#define REG_PAD_KEYINPUT_RIGHT_SHIFT                       4
#define REG_PAD_KEYINPUT_RIGHT_SIZE                        1
#define REG_PAD_KEYINPUT_RIGHT_MASK                        0x0010

#define REG_PAD_KEYINPUT_START_SHIFT                       3
#define REG_PAD_KEYINPUT_START_SIZE                        1
#define REG_PAD_KEYINPUT_START_MASK                        0x0008

#define REG_PAD_KEYINPUT_SEL_SHIFT                         2
#define REG_PAD_KEYINPUT_SEL_SIZE                          1
#define REG_PAD_KEYINPUT_SEL_MASK                          0x0004

#define REG_PAD_KEYINPUT_B_SHIFT                           1
#define REG_PAD_KEYINPUT_B_SIZE                            1
#define REG_PAD_KEYINPUT_B_MASK                            0x0002

#define REG_PAD_KEYINPUT_A_SHIFT                           0
#define REG_PAD_KEYINPUT_A_SIZE                            1
#define REG_PAD_KEYINPUT_A_MASK                            0x0001

#ifndef SDK_ASM
#define REG_PAD_KEYINPUT_FIELD( x, y, l, r, down, up, left, right, start, sel, b, a ) \
    (u16)( \
    ((u32)(x) << REG_PAD_KEYINPUT_X_SHIFT) | \
    ((u32)(y) << REG_PAD_KEYINPUT_Y_SHIFT) | \
    ((u32)(l) << REG_PAD_KEYINPUT_L_SHIFT) | \
    ((u32)(r) << REG_PAD_KEYINPUT_R_SHIFT) | \
    ((u32)(down) << REG_PAD_KEYINPUT_DOWN_SHIFT) | \
    ((u32)(up) << REG_PAD_KEYINPUT_UP_SHIFT) | \
    ((u32)(left) << REG_PAD_KEYINPUT_LEFT_SHIFT) | \
    ((u32)(right) << REG_PAD_KEYINPUT_RIGHT_SHIFT) | \
    ((u32)(start) << REG_PAD_KEYINPUT_START_SHIFT) | \
    ((u32)(sel) << REG_PAD_KEYINPUT_SEL_SHIFT) | \
    ((u32)(b) << REG_PAD_KEYINPUT_B_SHIFT) | \
    ((u32)(a) << REG_PAD_KEYINPUT_A_SHIFT))
#endif


/* KEYCNT */

#define REG_PAD_KEYCNT_INTR_SHIFT                          31
#define REG_PAD_KEYCNT_INTR_SIZE                           1
#define REG_PAD_KEYCNT_INTR_MASK                           0x80000000

#define REG_PAD_KEYCNT_LOGIC_SHIFT                         30
#define REG_PAD_KEYCNT_LOGIC_SIZE                          1
#define REG_PAD_KEYCNT_LOGIC_MASK                          0x40000000

#define REG_PAD_KEYCNT_EDGE_SHIFT                          29
#define REG_PAD_KEYCNT_EDGE_SIZE                           1
#define REG_PAD_KEYCNT_EDGE_MASK                           0x20000000

#define REG_PAD_KEYCNT_X_SHIFT                             11
#define REG_PAD_KEYCNT_X_SIZE                              1
#define REG_PAD_KEYCNT_X_MASK                              0x00000800

#define REG_PAD_KEYCNT_Y_SHIFT                             10
#define REG_PAD_KEYCNT_Y_SIZE                              1
#define REG_PAD_KEYCNT_Y_MASK                              0x00000400

#define REG_PAD_KEYCNT_L_SHIFT                             9
#define REG_PAD_KEYCNT_L_SIZE                              1
#define REG_PAD_KEYCNT_L_MASK                              0x00000200

#define REG_PAD_KEYCNT_R_SHIFT                             8
#define REG_PAD_KEYCNT_R_SIZE                              1
#define REG_PAD_KEYCNT_R_MASK                              0x00000100

#define REG_PAD_KEYCNT_DOWN_SHIFT                          7
#define REG_PAD_KEYCNT_DOWN_SIZE                           1
#define REG_PAD_KEYCNT_DOWN_MASK                           0x00000080

#define REG_PAD_KEYCNT_UP_SHIFT                            6
#define REG_PAD_KEYCNT_UP_SIZE                             1
#define REG_PAD_KEYCNT_UP_MASK                             0x00000040

#define REG_PAD_KEYCNT_LEFT_SHIFT                          5
#define REG_PAD_KEYCNT_LEFT_SIZE                           1
#define REG_PAD_KEYCNT_LEFT_MASK                           0x00000020

#define REG_PAD_KEYCNT_RIGHT_SHIFT                         4
#define REG_PAD_KEYCNT_RIGHT_SIZE                          1
#define REG_PAD_KEYCNT_RIGHT_MASK                          0x00000010

#define REG_PAD_KEYCNT_START_SHIFT                         3
#define REG_PAD_KEYCNT_START_SIZE                          1
#define REG_PAD_KEYCNT_START_MASK                          0x00000008

#define REG_PAD_KEYCNT_SEL_SHIFT                           2
#define REG_PAD_KEYCNT_SEL_SIZE                            1
#define REG_PAD_KEYCNT_SEL_MASK                            0x00000004

#define REG_PAD_KEYCNT_B_SHIFT                             1
#define REG_PAD_KEYCNT_B_SIZE                              1
#define REG_PAD_KEYCNT_B_MASK                              0x00000002

#define REG_PAD_KEYCNT_A_SHIFT                             0
#define REG_PAD_KEYCNT_A_SIZE                              1
#define REG_PAD_KEYCNT_A_MASK                              0x00000001

#ifndef SDK_ASM
#define REG_PAD_KEYCNT_FIELD( intr, logic, edge, x, y, l, r, down, up, left, right, start, sel, b, a ) \
    (u32)( \
    ((u32)(intr) << REG_PAD_KEYCNT_INTR_SHIFT) | \
    ((u32)(logic) << REG_PAD_KEYCNT_LOGIC_SHIFT) | \
    ((u32)(edge) << REG_PAD_KEYCNT_EDGE_SHIFT) | \
    ((u32)(x) << REG_PAD_KEYCNT_X_SHIFT) | \
    ((u32)(y) << REG_PAD_KEYCNT_Y_SHIFT) | \
    ((u32)(l) << REG_PAD_KEYCNT_L_SHIFT) | \
    ((u32)(r) << REG_PAD_KEYCNT_R_SHIFT) | \
    ((u32)(down) << REG_PAD_KEYCNT_DOWN_SHIFT) | \
    ((u32)(up) << REG_PAD_KEYCNT_UP_SHIFT) | \
    ((u32)(left) << REG_PAD_KEYCNT_LEFT_SHIFT) | \
    ((u32)(right) << REG_PAD_KEYCNT_RIGHT_SHIFT) | \
    ((u32)(start) << REG_PAD_KEYCNT_START_SHIFT) | \
    ((u32)(sel) << REG_PAD_KEYCNT_SEL_SHIFT) | \
    ((u32)(b) << REG_PAD_KEYCNT_B_SHIFT) | \
    ((u32)(a) << REG_PAD_KEYCNT_A_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_MG20_ARM9_IOREG_MG20PATCH_PAD_H_ */
#endif
