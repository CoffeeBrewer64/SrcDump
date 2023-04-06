/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-NE1TB/MPCore/ioreg_ne1patch_NE1DDR2.h

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
#ifndef NN_HW_CTR_NE1TB_MPCORE_IOREG_NE1PATCH_NE1DDR2_H_
#define NN_HW_CTR_NE1TB_MPCORE_IOREG_NE1PATCH_NE1DDR2_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* MIF_INIT */

#define REG_MIF_INIT_OFFSET                                0x08
#define REG_MIF_INIT_ADDR                                  (HW_NE1DDR2_REG + REG_MIF_INIT_OFFSET)
#define reg_NE1DDR2_MIF_INIT                               (*( REGType32v *) REG_MIF_INIT_ADDR)

/* MIF_REF_CFG */

#define REG_MIF_REF_CFG_OFFSET                             0x34
#define REG_MIF_REF_CFG_ADDR                               (HW_NE1DDR2_REG + REG_MIF_REF_CFG_OFFSET)
#define reg_NE1DDR2_MIF_REF_CFG                            (*( REGType32v *) REG_MIF_REF_CFG_ADDR)

/* MIF_SDC_CFG1 */

#define REG_MIF_SDC_CFG1_OFFSET                            0x40
#define REG_MIF_SDC_CFG1_ADDR                              (HW_NE1DDR2_REG + REG_MIF_SDC_CFG1_OFFSET)
#define reg_NE1DDR2_MIF_SDC_CFG1                           (*( REGType32v *) REG_MIF_SDC_CFG1_ADDR)

/* MIF_SDC_CFG2 */

#define REG_MIF_SDC_CFG2_OFFSET                            0x44
#define REG_MIF_SDC_CFG2_ADDR                              (HW_NE1DDR2_REG + REG_MIF_SDC_CFG2_OFFSET)
#define reg_NE1DDR2_MIF_SDC_CFG2                           (*( REGType32v *) REG_MIF_SDC_CFG2_ADDR)

/* MIF_SDC_CFG3 */

#define REG_MIF_SDC_CFG3_OFFSET                            0x48
#define REG_MIF_SDC_CFG3_ADDR                              (HW_NE1DDR2_REG + REG_MIF_SDC_CFG3_OFFSET)
#define reg_NE1DDR2_MIF_SDC_CFG3                           (*( REGType32v *) REG_MIF_SDC_CFG3_ADDR)

/* MIF_DLL_CFG */

#define REG_MIF_DLL_CFG_OFFSET                             0x58
#define REG_MIF_DLL_CFG_ADDR                               (HW_NE1DDR2_REG + REG_MIF_DLL_CFG_OFFSET)
#define reg_NE1DDR2_MIF_DLL_CFG                            (*( REGType32v *) REG_MIF_DLL_CFG_ADDR)


/*
 * Definitions of Register fields
 */


/* MIF_INIT */

#define REG_NE1DDR2_MIF_INIT_ADR_SHIFT                     15
#define REG_NE1DDR2_MIF_INIT_ADR_SIZE                      17
#define REG_NE1DDR2_MIF_INIT_ADR_MASK                      0xffff8000

#define REG_NE1DDR2_MIF_INIT_IE_SHIFT                      8
#define REG_NE1DDR2_MIF_INIT_IE_SIZE                       1
#define REG_NE1DDR2_MIF_INIT_IE_MASK                       0x00000100

#define REG_NE1DDR2_MIF_INIT_EPS_SHIFT                     5
#define REG_NE1DDR2_MIF_INIT_EPS_SIZE                      1
#define REG_NE1DDR2_MIF_INIT_EPS_MASK                      0x00000020

#define REG_NE1DDR2_MIF_INIT_PDN_SHIFT                     4
#define REG_NE1DDR2_MIF_INIT_PDN_SIZE                      1
#define REG_NE1DDR2_MIF_INIT_PDN_MASK                      0x00000010

#define REG_NE1DDR2_MIF_INIT_SRF_SHIFT                     3
#define REG_NE1DDR2_MIF_INIT_SRF_SIZE                      1
#define REG_NE1DDR2_MIF_INIT_SRF_MASK                      0x00000008

#define REG_NE1DDR2_MIF_INIT_PRE_SHIFT                     2
#define REG_NE1DDR2_MIF_INIT_PRE_SIZE                      1
#define REG_NE1DDR2_MIF_INIT_PRE_MASK                      0x00000004

#define REG_NE1DDR2_MIF_INIT_MRS_SHIFT                     1
#define REG_NE1DDR2_MIF_INIT_MRS_SIZE                      1
#define REG_NE1DDR2_MIF_INIT_MRS_MASK                      0x00000002

#define REG_NE1DDR2_MIF_INIT_REF_SHIFT                     0
#define REG_NE1DDR2_MIF_INIT_REF_SIZE                      1
#define REG_NE1DDR2_MIF_INIT_REF_MASK                      0x00000001

#ifndef SDK_ASM
#define REG_NE1DDR2_MIF_INIT_FIELD( adr, ie, eps, pdn, srf, pre, mrs, ref ) \
    (u32)( \
    ((u32)(adr) << REG_NE1DDR2_MIF_INIT_ADR_SHIFT) | \
    ((u32)(ie) << REG_NE1DDR2_MIF_INIT_IE_SHIFT) | \
    ((u32)(eps) << REG_NE1DDR2_MIF_INIT_EPS_SHIFT) | \
    ((u32)(pdn) << REG_NE1DDR2_MIF_INIT_PDN_SHIFT) | \
    ((u32)(srf) << REG_NE1DDR2_MIF_INIT_SRF_SHIFT) | \
    ((u32)(pre) << REG_NE1DDR2_MIF_INIT_PRE_SHIFT) | \
    ((u32)(mrs) << REG_NE1DDR2_MIF_INIT_MRS_SHIFT) | \
    ((u32)(ref) << REG_NE1DDR2_MIF_INIT_REF_SHIFT))
#endif


/* MIF_REF_CFG */

#define REG_NE1DDR2_MIF_REF_CFG_E_SHIFT                    8
#define REG_NE1DDR2_MIF_REF_CFG_E_SIZE                     1
#define REG_NE1DDR2_MIF_REF_CFG_E_MASK                     0x00000100

#define REG_NE1DDR2_MIF_REF_CFG_RCNT_SHIFT                 0
#define REG_NE1DDR2_MIF_REF_CFG_RCNT_SIZE                  8
#define REG_NE1DDR2_MIF_REF_CFG_RCNT_MASK                  0x000000ff

#ifndef SDK_ASM
#define REG_NE1DDR2_MIF_REF_CFG_FIELD( e, rcnt ) \
    (u32)( \
    ((u32)(e) << REG_NE1DDR2_MIF_REF_CFG_E_SHIFT) | \
    ((u32)(rcnt) << REG_NE1DDR2_MIF_REF_CFG_RCNT_SHIFT))
#endif


/* MIF_SDC_CFG1 */

#define REG_NE1DDR2_MIF_SDC_CFG1_RTP_SHIFT                 29
#define REG_NE1DDR2_MIF_SDC_CFG1_RTP_SIZE                  1
#define REG_NE1DDR2_MIF_SDC_CFG1_RTP_MASK                  0x20000000

#define REG_NE1DDR2_MIF_SDC_CFG1_CL_SHIFT                  26
#define REG_NE1DDR2_MIF_SDC_CFG1_CL_SIZE                   3
#define REG_NE1DDR2_MIF_SDC_CFG1_CL_MASK                   0x1c000000

#define REG_NE1DDR2_MIF_SDC_CFG1_RAS_SHIFT                 20
#define REG_NE1DDR2_MIF_SDC_CFG1_RAS_SIZE                  4
#define REG_NE1DDR2_MIF_SDC_CFG1_RAS_MASK                  0x00f00000

#define REG_NE1DDR2_MIF_SDC_CFG1_WTR_SHIFT                 18
#define REG_NE1DDR2_MIF_SDC_CFG1_WTR_SIZE                  2
#define REG_NE1DDR2_MIF_SDC_CFG1_WTR_MASK                  0x000c0000

#define REG_NE1DDR2_MIF_SDC_CFG1_RFC_SHIFT                 12
#define REG_NE1DDR2_MIF_SDC_CFG1_RFC_SIZE                  6
#define REG_NE1DDR2_MIF_SDC_CFG1_RFC_MASK                  0x0003f000

#define REG_NE1DDR2_MIF_SDC_CFG1_WR_SHIFT                  9
#define REG_NE1DDR2_MIF_SDC_CFG1_WR_SIZE                   3
#define REG_NE1DDR2_MIF_SDC_CFG1_WR_MASK                   0x00000e00

#define REG_NE1DDR2_MIF_SDC_CFG1_RP_SHIFT                  6
#define REG_NE1DDR2_MIF_SDC_CFG1_RP_SIZE                   3
#define REG_NE1DDR2_MIF_SDC_CFG1_RP_MASK                   0x000001c0

#define REG_NE1DDR2_MIF_SDC_CFG1_RCD_SHIFT                 4
#define REG_NE1DDR2_MIF_SDC_CFG1_RCD_SIZE                  2
#define REG_NE1DDR2_MIF_SDC_CFG1_RCD_MASK                  0x00000030

#define REG_NE1DDR2_MIF_SDC_CFG1_MT_SHIFT                  0
#define REG_NE1DDR2_MIF_SDC_CFG1_MT_SIZE                   3
#define REG_NE1DDR2_MIF_SDC_CFG1_MT_MASK                   0x00000007

#ifndef SDK_ASM
#define REG_NE1DDR2_MIF_SDC_CFG1_FIELD( rtp, cl, ras, wtr, rfc, wr, rp, rcd, mt ) \
    (u32)( \
    ((u32)(rtp) << REG_NE1DDR2_MIF_SDC_CFG1_RTP_SHIFT) | \
    ((u32)(cl) << REG_NE1DDR2_MIF_SDC_CFG1_CL_SHIFT) | \
    ((u32)(ras) << REG_NE1DDR2_MIF_SDC_CFG1_RAS_SHIFT) | \
    ((u32)(wtr) << REG_NE1DDR2_MIF_SDC_CFG1_WTR_SHIFT) | \
    ((u32)(rfc) << REG_NE1DDR2_MIF_SDC_CFG1_RFC_SHIFT) | \
    ((u32)(wr) << REG_NE1DDR2_MIF_SDC_CFG1_WR_SHIFT) | \
    ((u32)(rp) << REG_NE1DDR2_MIF_SDC_CFG1_RP_SHIFT) | \
    ((u32)(rcd) << REG_NE1DDR2_MIF_SDC_CFG1_RCD_SHIFT) | \
    ((u32)(mt) << REG_NE1DDR2_MIF_SDC_CFG1_MT_SHIFT))
#endif


/* MIF_SDC_CFG2 */

#define REG_NE1DDR2_MIF_SDC_CFG2_DIEN_SHIFT                31
#define REG_NE1DDR2_MIF_SDC_CFG2_DIEN_SIZE                 1
#define REG_NE1DDR2_MIF_SDC_CFG2_DIEN_MASK                 0x80000000

#define REG_NE1DDR2_MIF_SDC_CFG2_PREAD_SHIFT               30
#define REG_NE1DDR2_MIF_SDC_CFG2_PREAD_SIZE                1
#define REG_NE1DDR2_MIF_SDC_CFG2_PREAD_MASK                0x40000000

#define REG_NE1DDR2_MIF_SDC_CFG2_ODTEN_SHIFT               28
#define REG_NE1DDR2_MIF_SDC_CFG2_ODTEN_SIZE                2
#define REG_NE1DDR2_MIF_SDC_CFG2_ODTEN_MASK                0x30000000

#define REG_NE1DDR2_MIF_SDC_CFG2_RDLD1_SHIFT               26
#define REG_NE1DDR2_MIF_SDC_CFG2_RDLD1_SIZE                2
#define REG_NE1DDR2_MIF_SDC_CFG2_RDLD1_MASK                0x0c000000

#define REG_NE1DDR2_MIF_SDC_CFG2_RDLD0_SHIFT               24
#define REG_NE1DDR2_MIF_SDC_CFG2_RDLD0_SIZE                2
#define REG_NE1DDR2_MIF_SDC_CFG2_RDLD0_MASK                0x03000000

#define REG_NE1DDR2_MIF_SDC_CFG2_TFAW_SHIFT                21
#define REG_NE1DDR2_MIF_SDC_CFG2_TFAW_SIZE                 3
#define REG_NE1DDR2_MIF_SDC_CFG2_TFAW_MASK                 0x00e00000

#define REG_NE1DDR2_MIF_SDC_CFG2_R2WD_SHIFT                16
#define REG_NE1DDR2_MIF_SDC_CFG2_R2WD_SIZE                 2
#define REG_NE1DDR2_MIF_SDC_CFG2_R2WD_MASK                 0x00030000

#define REG_NE1DDR2_MIF_SDC_CFG2_W2WDCS_SHIFT              12
#define REG_NE1DDR2_MIF_SDC_CFG2_W2WDCS_SIZE               2
#define REG_NE1DDR2_MIF_SDC_CFG2_W2WDCS_MASK               0x00003000

#define REG_NE1DDR2_MIF_SDC_CFG2_W2RDCS_SHIFT              4
#define REG_NE1DDR2_MIF_SDC_CFG2_W2RDCS_SIZE               3
#define REG_NE1DDR2_MIF_SDC_CFG2_W2RDCS_MASK               0x00000070

#define REG_NE1DDR2_MIF_SDC_CFG2_R2RDCS_SHIFT              0
#define REG_NE1DDR2_MIF_SDC_CFG2_R2RDCS_SIZE               3
#define REG_NE1DDR2_MIF_SDC_CFG2_R2RDCS_MASK               0x00000007

#ifndef SDK_ASM
#define REG_NE1DDR2_MIF_SDC_CFG2_FIELD( dien, pread, odten, rdld1, rdld0, tfaw, r2wd, w2wdcs, w2rdcs, r2rdcs ) \
    (u32)( \
    ((u32)(dien) << REG_NE1DDR2_MIF_SDC_CFG2_DIEN_SHIFT) | \
    ((u32)(pread) << REG_NE1DDR2_MIF_SDC_CFG2_PREAD_SHIFT) | \
    ((u32)(odten) << REG_NE1DDR2_MIF_SDC_CFG2_ODTEN_SHIFT) | \
    ((u32)(rdld1) << REG_NE1DDR2_MIF_SDC_CFG2_RDLD1_SHIFT) | \
    ((u32)(rdld0) << REG_NE1DDR2_MIF_SDC_CFG2_RDLD0_SHIFT) | \
    ((u32)(tfaw) << REG_NE1DDR2_MIF_SDC_CFG2_TFAW_SHIFT) | \
    ((u32)(r2wd) << REG_NE1DDR2_MIF_SDC_CFG2_R2WD_SHIFT) | \
    ((u32)(w2wdcs) << REG_NE1DDR2_MIF_SDC_CFG2_W2WDCS_SHIFT) | \
    ((u32)(w2rdcs) << REG_NE1DDR2_MIF_SDC_CFG2_W2RDCS_SHIFT) | \
    ((u32)(r2rdcs) << REG_NE1DDR2_MIF_SDC_CFG2_R2RDCS_SHIFT))
#endif


/* MIF_SDC_CFG3 */

#define REG_NE1DDR2_MIF_SDC_CFG3_ODTMODE_SHIFT             16
#define REG_NE1DDR2_MIF_SDC_CFG3_ODTMODE_SIZE              1
#define REG_NE1DDR2_MIF_SDC_CFG3_ODTMODE_MASK              0x00010000

#define REG_NE1DDR2_MIF_SDC_CFG3_WODTSEL_SHIFT             12
#define REG_NE1DDR2_MIF_SDC_CFG3_WODTSEL_SIZE              2
#define REG_NE1DDR2_MIF_SDC_CFG3_WODTSEL_MASK              0x00003000

#define REG_NE1DDR2_MIF_SDC_CFG3_WODT_SHIFT                8
#define REG_NE1DDR2_MIF_SDC_CFG3_WODT_SIZE                 2
#define REG_NE1DDR2_MIF_SDC_CFG3_WODT_MASK                 0x00000300

#define REG_NE1DDR2_MIF_SDC_CFG3_RODTSEL_SHIFT             4
#define REG_NE1DDR2_MIF_SDC_CFG3_RODTSEL_SIZE              2
#define REG_NE1DDR2_MIF_SDC_CFG3_RODTSEL_MASK              0x00000030

#define REG_NE1DDR2_MIF_SDC_CFG3_RODT_SHIFT                0
#define REG_NE1DDR2_MIF_SDC_CFG3_RODT_SIZE                 2
#define REG_NE1DDR2_MIF_SDC_CFG3_RODT_MASK                 0x00000003

#ifndef SDK_ASM
#define REG_NE1DDR2_MIF_SDC_CFG3_FIELD( odtmode, wodtsel, wodt, rodtsel, rodt ) \
    (u32)( \
    ((u32)(odtmode) << REG_NE1DDR2_MIF_SDC_CFG3_ODTMODE_SHIFT) | \
    ((u32)(wodtsel) << REG_NE1DDR2_MIF_SDC_CFG3_WODTSEL_SHIFT) | \
    ((u32)(wodt) << REG_NE1DDR2_MIF_SDC_CFG3_WODT_SHIFT) | \
    ((u32)(rodtsel) << REG_NE1DDR2_MIF_SDC_CFG3_RODTSEL_SHIFT) | \
    ((u32)(rodt) << REG_NE1DDR2_MIF_SDC_CFG3_RODT_SHIFT))
#endif


/* MIF_DLL_CFG */

#define REG_NE1DDR2_MIF_DLL_CFG_DLLFSL_SHIFT               0
#define REG_NE1DDR2_MIF_DLL_CFG_DLLFSL_SIZE                3
#define REG_NE1DDR2_MIF_DLL_CFG_DLLFSL_MASK                0x00000007

#ifndef SDK_ASM
#define REG_NE1DDR2_MIF_DLL_CFG_FIELD( dllfsl ) \
    (u32)( \
    ((u32)(dllfsl) << REG_NE1DDR2_MIF_DLL_CFG_DLLFSL_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_NE1TB_MPCORE_IOREG_NE1PATCH_NE1DDR2_H_ */
#endif
