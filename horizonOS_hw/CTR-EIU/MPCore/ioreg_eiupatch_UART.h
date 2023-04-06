/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-EIU/MPCore/ioreg_eiupatch_UART.h

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
#ifndef NN_HW_CTR_EIU_MPCORE_IOREG_EIUPATCH_UART_H_
#define NN_HW_CTR_EIU_MPCORE_IOREG_EIUPATCH_UART_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* CR */

#define REG_CR_OFFSET                                      0x204000
#define REG_CR_ADDR                                        (HW_REG_BASE + REG_CR_OFFSET)
#define reg_UART_CR                                        (*( REGType32v *) REG_CR_ADDR)

/* SR */

#define REG_SR_OFFSET                                      0x204004
#define REG_SR_ADDR                                        (HW_REG_BASE + REG_SR_OFFSET)
#define reg_UART_SR                                        (*(const REGType32v *) REG_SR_ADDR)

/* TCR */

#define REG_TCR_OFFSET                                     0x204008
#define REG_TCR_ADDR                                       (HW_REG_BASE + REG_TCR_OFFSET)
#define reg_UART_TCR                                       (*( REGType32v *) REG_TCR_ADDR)

/* RCR */

#define REG_RCR_OFFSET                                     0x20400c
#define REG_RCR_ADDR                                       (HW_REG_BASE + REG_RCR_OFFSET)
#define reg_UART_RCR                                       (*( REGType32v *) REG_RCR_ADDR)

/* DR */

#define REG_DR_OFFSET                                      0x204010
#define REG_DR_ADDR                                        (HW_REG_BASE + REG_DR_OFFSET)
#define reg_UART_DR                                        (*( REGType32v *) REG_DR_ADDR)

/* QDR */

#define REG_QDR_OFFSET                                     0x204014
#define REG_QDR_ADDR                                       (HW_REG_BASE + REG_QDR_OFFSET)
#define reg_UART_QDR                                       (*( REGType32v *) REG_QDR_ADDR)

/* ISR */

#define REG_ISR_OFFSET                                     0x204020
#define REG_ISR_ADDR                                       (HW_REG_BASE + REG_ISR_OFFSET)
#define reg_UART_ISR                                       (*( REGType32v *) REG_ISR_ADDR)

/* IER */

#define REG_IER_OFFSET                                     0x204024
#define REG_IER_ADDR                                       (HW_REG_BASE + REG_IER_OFFSET)
#define reg_UART_IER                                       (*( REGType32v *) REG_IER_ADDR)

/* CLKNUME */

#define REG_CLKNUME_OFFSET                                 0x204030
#define REG_CLKNUME_ADDR                                   (HW_REG_BASE + REG_CLKNUME_OFFSET)
#define reg_UART_CLKNUME                                   (*( REGType32v *) REG_CLKNUME_ADDR)

/* CLKDENO */

#define REG_CLKDENO_OFFSET                                 0x204034
#define REG_CLKDENO_ADDR                                   (HW_REG_BASE + REG_CLKDENO_OFFSET)
#define reg_UART_CLKDENO                                   (*( REGType32v *) REG_CLKDENO_ADDR)

/* RTO */

#define REG_RTO_OFFSET                                     0x204038
#define REG_RTO_ADDR                                       (HW_REG_BASE + REG_RTO_OFFSET)
#define reg_UART_RTO                                       (*( REGType32v *) REG_RTO_ADDR)


/*
 * Definitions of Register fields
 */


/* CR */

#define REG_UART_CR_INCTS_SHIFT                            7
#define REG_UART_CR_INCTS_SIZE                             1
#define REG_UART_CR_INCTS_MASK                             0x00000080

#define REG_UART_CR_ITXD_SHIFT                             6
#define REG_UART_CR_ITXD_SIZE                              1
#define REG_UART_CR_ITXD_MASK                              0x00000040

#define REG_UART_CR_INRTS_SHIFT                            5
#define REG_UART_CR_INRTS_SIZE                             1
#define REG_UART_CR_INRTS_MASK                             0x00000020

#define REG_UART_CR_IRXD_SHIFT                             4
#define REG_UART_CR_IRXD_SIZE                              1
#define REG_UART_CR_IRXD_MASK                              0x00000010

#define REG_UART_CR_EN_SHIFT                               0
#define REG_UART_CR_EN_SIZE                                1
#define REG_UART_CR_EN_MASK                                0x00000001

#ifndef SDK_ASM
#define REG_UART_CR_FIELD( incts, itxd, inrts, irxd, en ) \
    (u32)( \
    ((u32)(incts) << REG_UART_CR_INCTS_SHIFT) | \
    ((u32)(itxd) << REG_UART_CR_ITXD_SHIFT) | \
    ((u32)(inrts) << REG_UART_CR_INRTS_SHIFT) | \
    ((u32)(irxd) << REG_UART_CR_IRXD_SHIFT) | \
    ((u32)(en) << REG_UART_CR_EN_SHIFT))
#endif


/* SR */

#define REG_UART_SR_TXFIFO_BR_SHIFT                        23
#define REG_UART_SR_TXFIFO_BR_SIZE                         1
#define REG_UART_SR_TXFIFO_BR_MASK                         0x00800000

#define REG_UART_SR_TXFIFO_QR_SHIFT                        22
#define REG_UART_SR_TXFIFO_QR_SIZE                         1
#define REG_UART_SR_TXFIFO_QR_MASK                         0x00400000

#define REG_UART_SR_TXFIFO_FULL_SHIFT                      21
#define REG_UART_SR_TXFIFO_FULL_SIZE                       1
#define REG_UART_SR_TXFIFO_FULL_MASK                       0x00200000

#define REG_UART_SR_TXFIFO_NEMP_SHIFT                      20
#define REG_UART_SR_TXFIFO_NEMP_SIZE                       1
#define REG_UART_SR_TXFIFO_NEMP_MASK                       0x00100000

#define REG_UART_SR_TXBUSY_SHIFT                           17
#define REG_UART_SR_TXBUSY_SIZE                            1
#define REG_UART_SR_TXBUSY_MASK                            0x00020000

#define REG_UART_SR_CTS_SHIFT                              16
#define REG_UART_SR_CTS_SIZE                               1
#define REG_UART_SR_CTS_MASK                               0x00010000

#define REG_UART_SR_RXEE_SHIFT                             12
#define REG_UART_SR_RXEE_SIZE                              1
#define REG_UART_SR_RXEE_MASK                              0x00001000

#define REG_UART_SR_RXDATA_OE_SHIFT                        11
#define REG_UART_SR_RXDATA_OE_SIZE                         1
#define REG_UART_SR_RXDATA_OE_MASK                         0x00000800

#define REG_UART_SR_RXDATA_BE_SHIFT                        10
#define REG_UART_SR_RXDATA_BE_SIZE                         1
#define REG_UART_SR_RXDATA_BE_MASK                         0x00000400

#define REG_UART_SR_RXDATA_PE_SHIFT                        9
#define REG_UART_SR_RXDATA_PE_SIZE                         1
#define REG_UART_SR_RXDATA_PE_MASK                         0x00000200

#define REG_UART_SR_RXDATA_FE_SHIFT                        8
#define REG_UART_SR_RXDATA_FE_SIZE                         1
#define REG_UART_SR_RXDATA_FE_MASK                         0x00000100

#define REG_UART_SR_RXFIFO_BR_SHIFT                        7
#define REG_UART_SR_RXFIFO_BR_SIZE                         1
#define REG_UART_SR_RXFIFO_BR_MASK                         0x00000080

#define REG_UART_SR_RXFIFO_QR_SHIFT                        6
#define REG_UART_SR_RXFIFO_QR_SIZE                         1
#define REG_UART_SR_RXFIFO_QR_MASK                         0x00000040

#define REG_UART_SR_RXFIFO_FULL_SHIFT                      5
#define REG_UART_SR_RXFIFO_FULL_SIZE                       1
#define REG_UART_SR_RXFIFO_FULL_MASK                       0x00000020

#define REG_UART_SR_RXFIFO_NEMP_SHIFT                      4
#define REG_UART_SR_RXFIFO_NEMP_SIZE                       1
#define REG_UART_SR_RXFIFO_NEMP_MASK                       0x00000010

#define REG_UART_SR_RXBUSY_SHIFT                           1
#define REG_UART_SR_RXBUSY_SIZE                            1
#define REG_UART_SR_RXBUSY_MASK                            0x00000002

#define REG_UART_SR_RXD_SHIFT                              0
#define REG_UART_SR_RXD_SIZE                               1
#define REG_UART_SR_RXD_MASK                               0x00000001

#ifndef SDK_ASM
#define REG_UART_SR_FIELD( txfifo_br, txfifo_qr, txfifo_full, txfifo_nemp, txbusy, cts, rxee, rxdata_oe, rxdata_be, rxdata_pe, rxdata_fe, rxfifo_br, rxfifo_qr, rxfifo_full, rxfifo_nemp, rxbusy, rxd ) \
    (u32)( \
    ((u32)(txfifo_br) << REG_UART_SR_TXFIFO_BR_SHIFT) | \
    ((u32)(txfifo_qr) << REG_UART_SR_TXFIFO_QR_SHIFT) | \
    ((u32)(txfifo_full) << REG_UART_SR_TXFIFO_FULL_SHIFT) | \
    ((u32)(txfifo_nemp) << REG_UART_SR_TXFIFO_NEMP_SHIFT) | \
    ((u32)(txbusy) << REG_UART_SR_TXBUSY_SHIFT) | \
    ((u32)(cts) << REG_UART_SR_CTS_SHIFT) | \
    ((u32)(rxee) << REG_UART_SR_RXEE_SHIFT) | \
    ((u32)(rxdata_oe) << REG_UART_SR_RXDATA_OE_SHIFT) | \
    ((u32)(rxdata_be) << REG_UART_SR_RXDATA_BE_SHIFT) | \
    ((u32)(rxdata_pe) << REG_UART_SR_RXDATA_PE_SHIFT) | \
    ((u32)(rxdata_fe) << REG_UART_SR_RXDATA_FE_SHIFT) | \
    ((u32)(rxfifo_br) << REG_UART_SR_RXFIFO_BR_SHIFT) | \
    ((u32)(rxfifo_qr) << REG_UART_SR_RXFIFO_QR_SHIFT) | \
    ((u32)(rxfifo_full) << REG_UART_SR_RXFIFO_FULL_SHIFT) | \
    ((u32)(rxfifo_nemp) << REG_UART_SR_RXFIFO_NEMP_SHIFT) | \
    ((u32)(rxbusy) << REG_UART_SR_RXBUSY_SHIFT) | \
    ((u32)(rxd) << REG_UART_SR_RXD_SHIFT))
#endif


/* TCR */

#define REG_UART_TCR_CCTS_SHIFT                            31
#define REG_UART_TCR_CCTS_SIZE                             1
#define REG_UART_TCR_CCTS_MASK                             0x80000000

#define REG_UART_TCR_CMSPAR_SHIFT                          30
#define REG_UART_TCR_CMSPAR_SIZE                           1
#define REG_UART_TCR_CMSPAR_MASK                           0x40000000

#define REG_UART_TCR_RST_SHIFT                             23
#define REG_UART_TCR_RST_SIZE                              1
#define REG_UART_TCR_RST_MASK                              0x00800000

#define REG_UART_TCR_THR_SHIFT                             17
#define REG_UART_TCR_THR_SIZE                              3
#define REG_UART_TCR_THR_MASK                              0x000e0000

#define REG_UART_TCR_DEN_SHIFT                             16
#define REG_UART_TCR_DEN_SIZE                              1
#define REG_UART_TCR_DEN_MASK                              0x00010000

#define REG_UART_TCR_PARODD_SHIFT                          9
#define REG_UART_TCR_PARODD_SIZE                           1
#define REG_UART_TCR_PARODD_MASK                           0x00000200

#define REG_UART_TCR_PARENB_SHIFT                          8
#define REG_UART_TCR_PARENB_SIZE                           1
#define REG_UART_TCR_PARENB_MASK                           0x00000100

#define REG_UART_TCR_TEN_SHIFT                             7
#define REG_UART_TCR_TEN_SIZE                              1
#define REG_UART_TCR_TEN_MASK                              0x00000080

#define REG_UART_TCR_CST_OPB_SHIFT                         6
#define REG_UART_TCR_CST_OPB_SIZE                          1
#define REG_UART_TCR_CST_OPB_MASK                          0x00000040

#define REG_UART_TCR_CSIZE_SHIFT                           4
#define REG_UART_TCR_CSIZE_SIZE                            2
#define REG_UART_TCR_CSIZE_MASK                            0x00000030

#define REG_UART_TCR_FEN_SHIFT                             1
#define REG_UART_TCR_FEN_SIZE                              1
#define REG_UART_TCR_FEN_MASK                              0x00000002

#define REG_UART_TCR_BRK_SHIFT                             0
#define REG_UART_TCR_BRK_SIZE                              1
#define REG_UART_TCR_BRK_MASK                              0x00000001

#ifndef SDK_ASM
#define REG_UART_TCR_FIELD( ccts, cmspar, rst, thr, den, parodd, parenb, ten, cst_opb, csize, fen, brk ) \
    (u32)( \
    ((u32)(ccts) << REG_UART_TCR_CCTS_SHIFT) | \
    ((u32)(cmspar) << REG_UART_TCR_CMSPAR_SHIFT) | \
    ((u32)(rst) << REG_UART_TCR_RST_SHIFT) | \
    ((u32)(thr) << REG_UART_TCR_THR_SHIFT) | \
    ((u32)(den) << REG_UART_TCR_DEN_SHIFT) | \
    ((u32)(parodd) << REG_UART_TCR_PARODD_SHIFT) | \
    ((u32)(parenb) << REG_UART_TCR_PARENB_SHIFT) | \
    ((u32)(ten) << REG_UART_TCR_TEN_SHIFT) | \
    ((u32)(cst_opb) << REG_UART_TCR_CST_OPB_SHIFT) | \
    ((u32)(csize) << REG_UART_TCR_CSIZE_SHIFT) | \
    ((u32)(fen) << REG_UART_TCR_FEN_SHIFT) | \
    ((u32)(brk) << REG_UART_TCR_BRK_SHIFT))
#endif


/* RCR */

#define REG_UART_RCR_CRTS_SHIFT                            31
#define REG_UART_RCR_CRTS_SIZE                             1
#define REG_UART_RCR_CRTS_MASK                             0x80000000

#define REG_UART_RCR_CMSPAR_SHIFT                          30
#define REG_UART_RCR_CMSPAR_SIZE                           1
#define REG_UART_RCR_CMSPAR_MASK                           0x40000000

#define REG_UART_RCR_RST_SHIFT                             23
#define REG_UART_RCR_RST_SIZE                              1
#define REG_UART_RCR_RST_MASK                              0x00800000

#define REG_UART_RCR_LRTS_SHIFT                            22
#define REG_UART_RCR_LRTS_SIZE                             1
#define REG_UART_RCR_LRTS_MASK                             0x00400000

#define REG_UART_RCR_RBD_SHIFT                             21
#define REG_UART_RCR_RBD_SIZE                              1
#define REG_UART_RCR_RBD_MASK                              0x00200000

#define REG_UART_RCR_DOE_SHIFT                             20
#define REG_UART_RCR_DOE_SIZE                              1
#define REG_UART_RCR_DOE_MASK                              0x00100000

#define REG_UART_RCR_THR_SHIFT                             17
#define REG_UART_RCR_THR_SIZE                              3
#define REG_UART_RCR_THR_MASK                              0x000e0000

#define REG_UART_RCR_DEN_SHIFT                             16
#define REG_UART_RCR_DEN_SIZE                              1
#define REG_UART_RCR_DEN_MASK                              0x00010000

#define REG_UART_RCR_PARODD_SHIFT                          9
#define REG_UART_RCR_PARODD_SIZE                           1
#define REG_UART_RCR_PARODD_MASK                           0x00000200

#define REG_UART_RCR_PARENB_SHIFT                          8
#define REG_UART_RCR_PARENB_SIZE                           1
#define REG_UART_RCR_PARENB_MASK                           0x00000100

#define REG_UART_RCR_REN_SHIFT                             7
#define REG_UART_RCR_REN_SIZE                              1
#define REG_UART_RCR_REN_MASK                              0x00000080

#define REG_UART_RCR_CST_OPB_SHIFT                         6
#define REG_UART_RCR_CST_OPB_SIZE                          1
#define REG_UART_RCR_CST_OPB_MASK                          0x00000040

#define REG_UART_RCR_CSIZE_SHIFT                           4
#define REG_UART_RCR_CSIZE_SIZE                            2
#define REG_UART_RCR_CSIZE_MASK                            0x00000030

#define REG_UART_RCR_FEN_SHIFT                             1
#define REG_UART_RCR_FEN_SIZE                              1
#define REG_UART_RCR_FEN_MASK                              0x00000002

#define REG_UART_RCR_RTS_SHIFT                             0
#define REG_UART_RCR_RTS_SIZE                              1
#define REG_UART_RCR_RTS_MASK                              0x00000001

#ifndef SDK_ASM
#define REG_UART_RCR_FIELD( crts, cmspar, rst, lrts, rbd, doe, thr, den, parodd, parenb, ren, cst_opb, csize, fen, rts ) \
    (u32)( \
    ((u32)(crts) << REG_UART_RCR_CRTS_SHIFT) | \
    ((u32)(cmspar) << REG_UART_RCR_CMSPAR_SHIFT) | \
    ((u32)(rst) << REG_UART_RCR_RST_SHIFT) | \
    ((u32)(lrts) << REG_UART_RCR_LRTS_SHIFT) | \
    ((u32)(rbd) << REG_UART_RCR_RBD_SHIFT) | \
    ((u32)(doe) << REG_UART_RCR_DOE_SHIFT) | \
    ((u32)(thr) << REG_UART_RCR_THR_SHIFT) | \
    ((u32)(den) << REG_UART_RCR_DEN_SHIFT) | \
    ((u32)(parodd) << REG_UART_RCR_PARODD_SHIFT) | \
    ((u32)(parenb) << REG_UART_RCR_PARENB_SHIFT) | \
    ((u32)(ren) << REG_UART_RCR_REN_SHIFT) | \
    ((u32)(cst_opb) << REG_UART_RCR_CST_OPB_SHIFT) | \
    ((u32)(csize) << REG_UART_RCR_CSIZE_SHIFT) | \
    ((u32)(fen) << REG_UART_RCR_FEN_SHIFT) | \
    ((u32)(rts) << REG_UART_RCR_RTS_SHIFT))
#endif


/* DR */

#define REG_UART_DR_V_SHIFT                                31
#define REG_UART_DR_V_SIZE                                 1
#define REG_UART_DR_V_MASK                                 0x80000000

#define REG_UART_DR_OE_SHIFT                               11
#define REG_UART_DR_OE_SIZE                                1
#define REG_UART_DR_OE_MASK                                0x00000800

#define REG_UART_DR_BE_SHIFT                               10
#define REG_UART_DR_BE_SIZE                                1
#define REG_UART_DR_BE_MASK                                0x00000400

#define REG_UART_DR_PE_SHIFT                               9
#define REG_UART_DR_PE_SIZE                                1
#define REG_UART_DR_PE_MASK                                0x00000200

#define REG_UART_DR_FE_SHIFT                               8
#define REG_UART_DR_FE_SIZE                                1
#define REG_UART_DR_FE_MASK                                0x00000100

#define REG_UART_DR_DATA_SHIFT                             0
#define REG_UART_DR_DATA_SIZE                              8
#define REG_UART_DR_DATA_MASK                              0x000000ff

#ifndef SDK_ASM
#define REG_UART_DR_FIELD( v, oe, be, pe, fe, data ) \
    (u32)( \
    ((u32)(v) << REG_UART_DR_V_SHIFT) | \
    ((u32)(oe) << REG_UART_DR_OE_SHIFT) | \
    ((u32)(be) << REG_UART_DR_BE_SHIFT) | \
    ((u32)(pe) << REG_UART_DR_PE_SHIFT) | \
    ((u32)(fe) << REG_UART_DR_FE_SHIFT) | \
    ((u32)(data) << REG_UART_DR_DATA_SHIFT))
#endif


/* QDR */

#define REG_UART_QDR_DATA3_SHIFT                           24
#define REG_UART_QDR_DATA3_SIZE                            8
#define REG_UART_QDR_DATA3_MASK                            0xff000000

#define REG_UART_QDR_DATA2_SHIFT                           16
#define REG_UART_QDR_DATA2_SIZE                            8
#define REG_UART_QDR_DATA2_MASK                            0x00ff0000

#define REG_UART_QDR_DATA1_SHIFT                           8
#define REG_UART_QDR_DATA1_SIZE                            8
#define REG_UART_QDR_DATA1_MASK                            0x0000ff00

#define REG_UART_QDR_DATA0_SHIFT                           0
#define REG_UART_QDR_DATA0_SIZE                            8
#define REG_UART_QDR_DATA0_MASK                            0x000000ff

#ifndef SDK_ASM
#define REG_UART_QDR_FIELD( data3, data2, data1, data0 ) \
    (u32)( \
    ((u32)(data3) << REG_UART_QDR_DATA3_SHIFT) | \
    ((u32)(data2) << REG_UART_QDR_DATA2_SHIFT) | \
    ((u32)(data1) << REG_UART_QDR_DATA1_SHIFT) | \
    ((u32)(data0) << REG_UART_QDR_DATA0_SHIFT))
#endif


/* ISR */

#define REG_UART_ISR_OEIS_SHIFT                            11
#define REG_UART_ISR_OEIS_SIZE                             1
#define REG_UART_ISR_OEIS_MASK                             0x00000800

#define REG_UART_ISR_BEIS_SHIFT                            10
#define REG_UART_ISR_BEIS_SIZE                             1
#define REG_UART_ISR_BEIS_MASK                             0x00000400

#define REG_UART_ISR_PEIS_SHIFT                            9
#define REG_UART_ISR_PEIS_SIZE                             1
#define REG_UART_ISR_PEIS_MASK                             0x00000200

#define REG_UART_ISR_FEIS_SHIFT                            8
#define REG_UART_ISR_FEIS_SIZE                             1
#define REG_UART_ISR_FEIS_MASK                             0x00000100

#define REG_UART_ISR_RTIS_SHIFT                            7
#define REG_UART_ISR_RTIS_SIZE                             1
#define REG_UART_ISR_RTIS_MASK                             0x00000080

#define REG_UART_ISR_CTIS_SHIFT                            6
#define REG_UART_ISR_CTIS_SIZE                             1
#define REG_UART_ISR_CTIS_MASK                             0x00000040

#define REG_UART_ISR_TXIS_SHIFT                            5
#define REG_UART_ISR_TXIS_SIZE                             1
#define REG_UART_ISR_TXIS_MASK                             0x00000020

#define REG_UART_ISR_RXIS_SHIFT                            4
#define REG_UART_ISR_RXIS_SIZE                             1
#define REG_UART_ISR_RXIS_MASK                             0x00000010

#define REG_UART_ISR_CTSIS_SHIFT                           1
#define REG_UART_ISR_CTSIS_SIZE                            1
#define REG_UART_ISR_CTSIS_MASK                            0x00000002

#ifndef SDK_ASM
#define REG_UART_ISR_FIELD( oeis, beis, peis, feis, rtis, ctis, txis, rxis, ctsis ) \
    (u32)( \
    ((u32)(oeis) << REG_UART_ISR_OEIS_SHIFT) | \
    ((u32)(beis) << REG_UART_ISR_BEIS_SHIFT) | \
    ((u32)(peis) << REG_UART_ISR_PEIS_SHIFT) | \
    ((u32)(feis) << REG_UART_ISR_FEIS_SHIFT) | \
    ((u32)(rtis) << REG_UART_ISR_RTIS_SHIFT) | \
    ((u32)(ctis) << REG_UART_ISR_CTIS_SHIFT) | \
    ((u32)(txis) << REG_UART_ISR_TXIS_SHIFT) | \
    ((u32)(rxis) << REG_UART_ISR_RXIS_SHIFT) | \
    ((u32)(ctsis) << REG_UART_ISR_CTSIS_SHIFT))
#endif


/* IER */

#define REG_UART_IER_OEIE_SHIFT                            11
#define REG_UART_IER_OEIE_SIZE                             1
#define REG_UART_IER_OEIE_MASK                             0x00000800

#define REG_UART_IER_BEIE_SHIFT                            10
#define REG_UART_IER_BEIE_SIZE                             1
#define REG_UART_IER_BEIE_MASK                             0x00000400

#define REG_UART_IER_PEIE_SHIFT                            9
#define REG_UART_IER_PEIE_SIZE                             1
#define REG_UART_IER_PEIE_MASK                             0x00000200

#define REG_UART_IER_FEIE_SHIFT                            8
#define REG_UART_IER_FEIE_SIZE                             1
#define REG_UART_IER_FEIE_MASK                             0x00000100

#define REG_UART_IER_RTIE_SHIFT                            7
#define REG_UART_IER_RTIE_SIZE                             1
#define REG_UART_IER_RTIE_MASK                             0x00000080

#define REG_UART_IER_CTIE_SHIFT                            6
#define REG_UART_IER_CTIE_SIZE                             1
#define REG_UART_IER_CTIE_MASK                             0x00000040

#define REG_UART_IER_TXIE_SHIFT                            5
#define REG_UART_IER_TXIE_SIZE                             1
#define REG_UART_IER_TXIE_MASK                             0x00000020

#define REG_UART_IER_RXIE_SHIFT                            4
#define REG_UART_IER_RXIE_SIZE                             1
#define REG_UART_IER_RXIE_MASK                             0x00000010

#define REG_UART_IER_CTSIE_SHIFT                           1
#define REG_UART_IER_CTSIE_SIZE                            1
#define REG_UART_IER_CTSIE_MASK                            0x00000002

#ifndef SDK_ASM
#define REG_UART_IER_FIELD( oeie, beie, peie, feie, rtie, ctie, txie, rxie, ctsie ) \
    (u32)( \
    ((u32)(oeie) << REG_UART_IER_OEIE_SHIFT) | \
    ((u32)(beie) << REG_UART_IER_BEIE_SHIFT) | \
    ((u32)(peie) << REG_UART_IER_PEIE_SHIFT) | \
    ((u32)(feie) << REG_UART_IER_FEIE_SHIFT) | \
    ((u32)(rtie) << REG_UART_IER_RTIE_SHIFT) | \
    ((u32)(ctie) << REG_UART_IER_CTIE_SHIFT) | \
    ((u32)(txie) << REG_UART_IER_TXIE_SHIFT) | \
    ((u32)(rxie) << REG_UART_IER_RXIE_SHIFT) | \
    ((u32)(ctsie) << REG_UART_IER_CTSIE_SHIFT))
#endif


/* CLKNUME */

#define REG_UART_CLKNUME_N_SHIFT                           0
#define REG_UART_CLKNUME_N_SIZE                            24
#define REG_UART_CLKNUME_N_MASK                            0x00ffffff

#ifndef SDK_ASM
#define REG_UART_CLKNUME_FIELD( n ) \
    (u32)( \
    ((u32)(n) << REG_UART_CLKNUME_N_SHIFT))
#endif


/* CLKDENO */

#define REG_UART_CLKDENO_D_SHIFT                           0
#define REG_UART_CLKDENO_D_SIZE                            24
#define REG_UART_CLKDENO_D_MASK                            0x00ffffff

#ifndef SDK_ASM
#define REG_UART_CLKDENO_FIELD( d ) \
    (u32)( \
    ((u32)(d) << REG_UART_CLKDENO_D_SHIFT))
#endif


/* RTO */

#define REG_UART_RTO_T_SHIFT                               0
#define REG_UART_RTO_T_SIZE                                24
#define REG_UART_RTO_T_MASK                                0x00ffffff

#ifndef SDK_ASM
#define REG_UART_RTO_FIELD( t ) \
    (u32)( \
    ((u32)(t) << REG_UART_RTO_T_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_EIU_MPCORE_IOREG_EIUPATCH_UART_H_ */
#endif
