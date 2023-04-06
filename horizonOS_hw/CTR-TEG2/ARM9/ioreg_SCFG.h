/*---------------------------------------------------------------------------*
  Project:  Horizon - IO Register List
  File:     nn/hw/CTR-TEG2/ARM9/ioreg_SCFG.h

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
#ifndef NN_HW_CTR_TEG2_ARM9_IOREG_SCFG_H_
#define NN_HW_CTR_TEG2_ARM9_IOREG_SCFG_H_

#ifndef SDK_ASM
#include <nn/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* ROM */

#define REG_ROM_OFFSET                                     0x000
#define REG_ROM_ADDR                                       (HW_REG_BASE + REG_ROM_OFFSET)
#define reg_SCFG_ROM                                       (*( REGType32v *) REG_ROM_ADDR)

/* A9ROM */

#define REG_A9ROM_OFFSET                                   0x000
#define REG_A9ROM_ADDR                                     (HW_REG_BASE + REG_A9ROM_OFFSET)
#define reg_SCFG_A9ROM                                     (*( REGType8v *) REG_A9ROM_ADDR)

/* A11ROM */

#define REG_A11ROM_OFFSET                                  0x001
#define REG_A11ROM_ADDR                                    (HW_REG_BASE + REG_A11ROM_OFFSET)
#define reg_SCFG_A11ROM                                    (*( REGType8v *) REG_A11ROM_ADDR)

/* ROMWE */

#define REG_ROMWE_OFFSET                                   0x002
#define REG_ROMWE_ADDR                                     (HW_REG_BASE + REG_ROMWE_OFFSET)
#define reg_SCFG_ROMWE                                     (*( REGType8v *) REG_ROMWE_ADDR)

/* JTAG */

#define REG_JTAG_OFFSET                                    0x004
#define REG_JTAG_ADDR                                      (HW_REG_BASE + REG_JTAG_OFFSET)
#define reg_SCFG_JTAG                                      (*( REGType16v *) REG_JTAG_ADDR)

/* DMAC2_DREQ */

#define REG_DMAC2_DREQ_OFFSET                              0x008
#define REG_DMAC2_DREQ_ADDR                                (HW_REG_BASE + REG_DMAC2_DREQ_OFFSET)
#define reg_SCFG_DMAC2_DREQ                                (*( REGType8v *) REG_DMAC2_DREQ_ADDR)

/* GC */

#define REG_GC_OFFSET                                      0x00c
#define REG_GC_ADDR                                        (HW_REG_BASE + REG_GC_OFFSET)
#define reg_SCFG_GC                                        (*( REGType8v *) REG_GC_ADDR)

/* CGC_MD */

#define REG_CGC_MD_OFFSET                                  0x010
#define REG_CGC_MD_ADDR                                    (HW_REG_BASE + REG_CGC_MD_OFFSET)
#define reg_SCFG_CGC_MD                                    (*( REGType8v *) REG_CGC_MD_ADDR)

/* CGC_CC */

#define REG_CGC_CC_OFFSET                                  0x012
#define REG_CGC_CC_ADDR                                    (HW_REG_BASE + REG_CGC_CC_OFFSET)
#define reg_SCFG_CGC_CC                                    (*( REGType16v *) REG_CGC_CC_ADDR)

/* CGC_CA */

#define REG_CGC_CA_OFFSET                                  0x014
#define REG_CGC_CA_ADDR                                    (HW_REG_BASE + REG_CGC_CA_OFFSET)
#define reg_SCFG_CGC_CA                                    (*( REGType16v *) REG_CGC_CA_ADDR)

/* SCFG_SD */

#define REG_SCFG_SD_OFFSET                                 0x020
#define REG_SCFG_SD_ADDR                                   (HW_REG_BASE + REG_SCFG_SD_OFFSET)
#define reg_SCFG_SCFG_SD                                   (*( REGType16v *) REG_SCFG_SD_ADDR)

/* SCFG_PROT */

#define REG_SCFG_PROT_OFFSET                               0x100
#define REG_SCFG_PROT_ADDR                                 (HW_REG_BASE + REG_SCFG_PROT_OFFSET)
#define reg_SCFG_SCFG_PROT                                 (*( REGType16v *) REG_SCFG_PROT_ADDR)

/* VER */

#define REG_VER_OFFSET                                     0xffc
#define REG_VER_ADDR                                       (HW_REG_BASE + REG_VER_OFFSET)
#define reg_SCFG_VER                                       (*( REGType16v *) REG_VER_ADDR)

/* RST_STAT */

#define REG_RST_STAT_OFFSET                                0x10000
#define REG_RST_STAT_ADDR                                  (HW_REG_BASE + REG_RST_STAT_OFFSET)
#define reg_SCFG_RST_STAT                                  (*( REGType32v *) REG_RST_STAT_ADDR)

/* OP */

#define REG_OP_OFFSET                                      0x10010
#define REG_OP_ADDR                                        (HW_REG_BASE + REG_OP_OFFSET)
#define reg_SCFG_OP                                        (*(const REGType8v *) REG_OP_ADDR)

/* PROM_DL */

#define REG_PROM_DL_OFFSET                                 0x10020
#define REG_PROM_DL_ADDR                                   (HW_REG_BASE + REG_PROM_DL_OFFSET)
#define reg_SCFG_PROM_DL                                   (*( REGType8v *) REG_PROM_DL_ADDR)

/* FUSE0 */

#define REG_FUSE0_OFFSET                                   0x12000
#define REG_FUSE0_ADDR                                     (HW_REG_BASE + REG_FUSE0_OFFSET)
#define reg_SCFG_FUSE0                                     (*(const REGType32v *) REG_FUSE0_ADDR)


/*
 * Definitions of Register fields
 */


/* ROM */

#define REG_SCFG_ROM_WE_SHIFT                              16
#define REG_SCFG_ROM_WE_SIZE                               1
#define REG_SCFG_ROM_WE_MASK                               0x00010000

#define REG_SCFG_ROM_A11SEC_SHIFT                          8
#define REG_SCFG_ROM_A11SEC_SIZE                           1
#define REG_SCFG_ROM_A11SEC_MASK                           0x00000100

#define REG_SCFG_ROM_A9FUSE_SHIFT                          1
#define REG_SCFG_ROM_A9FUSE_SIZE                           1
#define REG_SCFG_ROM_A9FUSE_MASK                           0x00000002

#define REG_SCFG_ROM_A9SEC_SHIFT                           0
#define REG_SCFG_ROM_A9SEC_SIZE                            1
#define REG_SCFG_ROM_A9SEC_MASK                            0x00000001

#ifndef SDK_ASM
#define REG_SCFG_ROM_FIELD( we, a11sec, a9fuse, a9sec ) \
    (u32)( \
    ((u32)(we) << REG_SCFG_ROM_WE_SHIFT) | \
    ((u32)(a11sec) << REG_SCFG_ROM_A11SEC_SHIFT) | \
    ((u32)(a9fuse) << REG_SCFG_ROM_A9FUSE_SHIFT) | \
    ((u32)(a9sec) << REG_SCFG_ROM_A9SEC_SHIFT))
#endif


/* A9ROM */

#define REG_SCFG_A9ROM_FUSE_SHIFT                          1
#define REG_SCFG_A9ROM_FUSE_SIZE                           1
#define REG_SCFG_A9ROM_FUSE_MASK                           0x02

#define REG_SCFG_A9ROM_SEC_SHIFT                           0
#define REG_SCFG_A9ROM_SEC_SIZE                            1
#define REG_SCFG_A9ROM_SEC_MASK                            0x01

#ifndef SDK_ASM
#define REG_SCFG_A9ROM_FIELD( fuse, sec ) \
    (u8)( \
    ((u32)(fuse) << REG_SCFG_A9ROM_FUSE_SHIFT) | \
    ((u32)(sec) << REG_SCFG_A9ROM_SEC_SHIFT))
#endif


/* A11ROM */

#define REG_SCFG_A11ROM_SEC_SHIFT                          0
#define REG_SCFG_A11ROM_SEC_SIZE                           1
#define REG_SCFG_A11ROM_SEC_MASK                           0x01

#ifndef SDK_ASM
#define REG_SCFG_A11ROM_FIELD( sec ) \
    (u8)( \
    ((u32)(sec) << REG_SCFG_A11ROM_SEC_SHIFT))
#endif


/* ROMWE */

#define REG_SCFG_ROMWE_WE_SHIFT                            0
#define REG_SCFG_ROMWE_WE_SIZE                             1
#define REG_SCFG_ROMWE_WE_MASK                             0x01

#ifndef SDK_ASM
#define REG_SCFG_ROMWE_FIELD( we ) \
    (u8)( \
    ((u32)(we) << REG_SCFG_ROMWE_WE_SHIFT))
#endif


/* JTAG */

#define REG_SCFG_JTAG_DSPJE_SHIFT                          8
#define REG_SCFG_JTAG_DSPJE_SIZE                           1
#define REG_SCFG_JTAG_DSPJE_MASK                           0x0100

#define REG_SCFG_JTAG_A11JE_SHIFT                          2
#define REG_SCFG_JTAG_A11JE_SIZE                           1
#define REG_SCFG_JTAG_A11JE_MASK                           0x0004

#define REG_SCFG_JTAG_A9JE_SHIFT                           1
#define REG_SCFG_JTAG_A9JE_SIZE                            1
#define REG_SCFG_JTAG_A9JE_MASK                            0x0002

#define REG_SCFG_JTAG_A7SEL_SHIFT                          0
#define REG_SCFG_JTAG_A7SEL_SIZE                           1
#define REG_SCFG_JTAG_A7SEL_MASK                           0x0001

#ifndef SDK_ASM
#define REG_SCFG_JTAG_FIELD( dspje, a11je, a9je, a7sel ) \
    (u16)( \
    ((u32)(dspje) << REG_SCFG_JTAG_DSPJE_SHIFT) | \
    ((u32)(a11je) << REG_SCFG_JTAG_A11JE_SHIFT) | \
    ((u32)(a9je) << REG_SCFG_JTAG_A9JE_SHIFT) | \
    ((u32)(a7sel) << REG_SCFG_JTAG_A7SEL_SHIFT))
#endif


/* DMAC2_DREQ */

#define REG_SCFG_DMAC2_DREQ_AES_O_SHIFT                    3
#define REG_SCFG_DMAC2_DREQ_AES_O_SIZE                     1
#define REG_SCFG_DMAC2_DREQ_AES_O_MASK                     0x08

#define REG_SCFG_DMAC2_DREQ_AES_I_SHIFT                    2
#define REG_SCFG_DMAC2_DREQ_AES_I_SIZE                     1
#define REG_SCFG_DMAC2_DREQ_AES_I_MASK                     0x04

#define REG_SCFG_DMAC2_DREQ_SD3_SHIFT                      1
#define REG_SCFG_DMAC2_DREQ_SD3_SIZE                       1
#define REG_SCFG_DMAC2_DREQ_SD3_MASK                       0x02

#define REG_SCFG_DMAC2_DREQ_SD1_SHIFT                      0
#define REG_SCFG_DMAC2_DREQ_SD1_SIZE                       1
#define REG_SCFG_DMAC2_DREQ_SD1_MASK                       0x01

#ifndef SDK_ASM
#define REG_SCFG_DMAC2_DREQ_FIELD( aes_o, aes_i, sd3, sd1 ) \
    (u8)( \
    ((u32)(aes_o) << REG_SCFG_DMAC2_DREQ_AES_O_SHIFT) | \
    ((u32)(aes_i) << REG_SCFG_DMAC2_DREQ_AES_I_SHIFT) | \
    ((u32)(sd3) << REG_SCFG_DMAC2_DREQ_SD3_SHIFT) | \
    ((u32)(sd1) << REG_SCFG_DMAC2_DREQ_SD1_SHIFT))
#endif


/* GC */

#define REG_SCFG_GC_INT_SEL_SHIFT                          12
#define REG_SCFG_GC_INT_SEL_SIZE                           1
#define REG_SCFG_GC_INT_SEL_MASK                           0x1000

#define REG_SCFG_GC_MEDIA_SEL_SHIFT                        8
#define REG_SCFG_GC_MEDIA_SEL_SIZE                         1
#define REG_SCFG_GC_MEDIA_SEL_MASK                         0x100

#define REG_SCFG_GC_SPI_SEL_SHIFT                          4
#define REG_SCFG_GC_SPI_SEL_SIZE                           1
#define REG_SCFG_GC_SPI_SEL_MASK                           0x10

#define REG_SCFG_GC_GC_SEL_SHIFT                           0
#define REG_SCFG_GC_GC_SEL_SIZE                            3
#define REG_SCFG_GC_GC_SEL_MASK                            0x07

#ifndef SDK_ASM
#define REG_SCFG_GC_FIELD( int_sel, media_sel, spi_sel, gc_sel ) \
    (u8)( \
    ((u32)(int_sel) << REG_SCFG_GC_INT_SEL_SHIFT) | \
    ((u32)(media_sel) << REG_SCFG_GC_MEDIA_SEL_SHIFT) | \
    ((u32)(spi_sel) << REG_SCFG_GC_SPI_SEL_SHIFT) | \
    ((u32)(gc_sel) << REG_SCFG_GC_GC_SEL_SHIFT))
#endif


/* CGC_MD */

#define REG_SCFG_CGC_MD_M_SHIFT                            2
#define REG_SCFG_CGC_MD_M_SIZE                             2
#define REG_SCFG_CGC_MD_M_MASK                             0x0c

#define REG_SCFG_CGC_MD_CDET_SHIFT                         0
#define REG_SCFG_CGC_MD_CDET_SIZE                          1
#define REG_SCFG_CGC_MD_CDET_MASK                          0x01

#ifndef SDK_ASM
#define REG_SCFG_CGC_MD_FIELD( m, cdet ) \
    (u8)( \
    ((u32)(m) << REG_SCFG_CGC_MD_M_SHIFT) | \
    ((u32)(cdet) << REG_SCFG_CGC_MD_CDET_SHIFT))
#endif


/* CGC_CC */

#define REG_SCFG_CGC_CC_CC_SHIFT                           0
#define REG_SCFG_CGC_CC_CC_SIZE                            16
#define REG_SCFG_CGC_CC_CC_MASK                            0xffff

#ifndef SDK_ASM
#define REG_SCFG_CGC_CC_FIELD( cc ) \
    (u16)( \
    ((u32)(cc) << REG_SCFG_CGC_CC_CC_SHIFT))
#endif


/* CGC_CA */

#define REG_SCFG_CGC_CA_CA_SHIFT                           0
#define REG_SCFG_CGC_CA_CA_SIZE                            16
#define REG_SCFG_CGC_CA_CA_MASK                            0xffff

#ifndef SDK_ASM
#define REG_SCFG_CGC_CA_FIELD( ca ) \
    (u16)( \
    ((u32)(ca) << REG_SCFG_CGC_CA_CA_SHIFT))
#endif


/* SCFG_SD */

#define REG_SCFG_SCFG_SD_SD10SEL_SHIFT                     9
#define REG_SCFG_SCFG_SD_SD10SEL_SIZE                      1
#define REG_SCFG_SCFG_SD_SD10SEL_MASK                      0x0200

#define REG_SCFG_SCFG_SD_SD3SEL_SHIFT                      8
#define REG_SCFG_SCFG_SD_SD3SEL_SIZE                       1
#define REG_SCFG_SCFG_SD_SD3SEL_MASK                       0x0100

#define REG_SCFG_SCFG_SD_SD20PU_SHIFT                      6
#define REG_SCFG_SCFG_SD_SD20PU_SIZE                       1
#define REG_SCFG_SCFG_SD_SD20PU_MASK                       0x0040

#define REG_SCFG_SCFG_SD_SD31OFF_SHIFT                     3
#define REG_SCFG_SCFG_SD_SD31OFF_SIZE                      1
#define REG_SCFG_SCFG_SD_SD31OFF_MASK                      0x0008

#define REG_SCFG_SCFG_SD_SD20OFF_SHIFT                     2
#define REG_SCFG_SCFG_SD_SD20OFF_SIZE                      1
#define REG_SCFG_SCFG_SD_SD20OFF_MASK                      0x0004

#define REG_SCFG_SCFG_SD_SD11OFF_SHIFT                     1
#define REG_SCFG_SCFG_SD_SD11OFF_SIZE                      1
#define REG_SCFG_SCFG_SD_SD11OFF_MASK                      0x0002

#define REG_SCFG_SCFG_SD_SD10OFF_SHIFT                     0
#define REG_SCFG_SCFG_SD_SD10OFF_SIZE                      1
#define REG_SCFG_SCFG_SD_SD10OFF_MASK                      0x0001

#ifndef SDK_ASM
#define REG_SCFG_SCFG_SD_FIELD( sd10sel, sd3sel, sd20pu, sd31off, sd20off, sd11off, sd10off ) \
    (u16)( \
    ((u32)(sd10sel) << REG_SCFG_SCFG_SD_SD10SEL_SHIFT) | \
    ((u32)(sd3sel) << REG_SCFG_SCFG_SD_SD3SEL_SHIFT) | \
    ((u32)(sd20pu) << REG_SCFG_SCFG_SD_SD20PU_SHIFT) | \
    ((u32)(sd31off) << REG_SCFG_SCFG_SD_SD31OFF_SHIFT) | \
    ((u32)(sd20off) << REG_SCFG_SCFG_SD_SD20OFF_SHIFT) | \
    ((u32)(sd11off) << REG_SCFG_SCFG_SD_SD11OFF_SHIFT) | \
    ((u32)(sd10off) << REG_SCFG_SCFG_SD_SD10OFF_SHIFT))
#endif


/* SCFG_PROT */

#define REG_SCFG_SCFG_PROT_SD10SEL_SHIFT                   13
#define REG_SCFG_SCFG_PROT_SD10SEL_SIZE                    1
#define REG_SCFG_SCFG_PROT_SD10SEL_MASK                    0x2000

#define REG_SCFG_SCFG_PROT_SD3SEL_SHIFT                    12
#define REG_SCFG_SCFG_PROT_SD3SEL_SIZE                     1
#define REG_SCFG_SCFG_PROT_SD3SEL_MASK                     0x1000

#define REG_SCFG_SCFG_PROT_SD31OFF_SHIFT                   11
#define REG_SCFG_SCFG_PROT_SD31OFF_SIZE                    1
#define REG_SCFG_SCFG_PROT_SD31OFF_MASK                    0x0800

#define REG_SCFG_SCFG_PROT_SD20OFF_SHIFT                   10
#define REG_SCFG_SCFG_PROT_SD20OFF_SIZE                    1
#define REG_SCFG_SCFG_PROT_SD20OFF_MASK                    0x0400

#define REG_SCFG_SCFG_PROT_SD11OFF_SHIFT                   9
#define REG_SCFG_SCFG_PROT_SD11OFF_SIZE                    1
#define REG_SCFG_SCFG_PROT_SD11OFF_MASK                    0x0200

#define REG_SCFG_SCFG_PROT_SD10OFF_SHIFT                   8
#define REG_SCFG_SCFG_PROT_SD10OFF_SIZE                    1
#define REG_SCFG_SCFG_PROT_SD10OFF_MASK                    0x0100

#define REG_SCFG_SCFG_PROT_CGC_M_SHIFT                     3
#define REG_SCFG_SCFG_PROT_CGC_M_SIZE                      1
#define REG_SCFG_SCFG_PROT_CGC_M_MASK                      0x0008

#define REG_SCFG_SCFG_PROT_CGC_SEL2_SHIFT                  2
#define REG_SCFG_SCFG_PROT_CGC_SEL2_SIZE                   1
#define REG_SCFG_SCFG_PROT_CGC_SEL2_MASK                   0x0004

#define REG_SCFG_SCFG_PROT_CGC_SEL1_SHIFT                  1
#define REG_SCFG_SCFG_PROT_CGC_SEL1_SIZE                   1
#define REG_SCFG_SCFG_PROT_CGC_SEL1_MASK                   0x0002

#define REG_SCFG_SCFG_PROT_CGC_SEL0_SHIFT                  0
#define REG_SCFG_SCFG_PROT_CGC_SEL0_SIZE                   1
#define REG_SCFG_SCFG_PROT_CGC_SEL0_MASK                   0x0001

#ifndef SDK_ASM
#define REG_SCFG_SCFG_PROT_FIELD( sd10sel, sd3sel, sd31off, sd20off, sd11off, sd10off, cgc_m, cgc_sel2, cgc_sel1, cgc_sel0 ) \
    (u16)( \
    ((u32)(sd10sel) << REG_SCFG_SCFG_PROT_SD10SEL_SHIFT) | \
    ((u32)(sd3sel) << REG_SCFG_SCFG_PROT_SD3SEL_SHIFT) | \
    ((u32)(sd31off) << REG_SCFG_SCFG_PROT_SD31OFF_SHIFT) | \
    ((u32)(sd20off) << REG_SCFG_SCFG_PROT_SD20OFF_SHIFT) | \
    ((u32)(sd11off) << REG_SCFG_SCFG_PROT_SD11OFF_SHIFT) | \
    ((u32)(sd10off) << REG_SCFG_SCFG_PROT_SD10OFF_SHIFT) | \
    ((u32)(cgc_m) << REG_SCFG_SCFG_PROT_CGC_M_SHIFT) | \
    ((u32)(cgc_sel2) << REG_SCFG_SCFG_PROT_CGC_SEL2_SHIFT) | \
    ((u32)(cgc_sel1) << REG_SCFG_SCFG_PROT_CGC_SEL1_SHIFT) | \
    ((u32)(cgc_sel0) << REG_SCFG_SCFG_PROT_CGC_SEL0_SHIFT))
#endif


/* VER */

#define REG_SCFG_VER_TS_SHIFT                              0
#define REG_SCFG_VER_TS_SIZE                               1
#define REG_SCFG_VER_TS_MASK                               0x0001

#ifndef SDK_ASM
#define REG_SCFG_VER_FIELD( ts ) \
    (u16)( \
    ((u32)(ts) << REG_SCFG_VER_TS_SHIFT))
#endif


/* RST_STAT */

/* OP */

#define REG_SCFG_OP_TYPE_SHIFT                             0
#define REG_SCFG_OP_TYPE_SIZE                              2
#define REG_SCFG_OP_TYPE_MASK                              0x03

#ifndef SDK_ASM
#define REG_SCFG_OP_FIELD( type ) \
    (u8)( \
    ((u32)(type) << REG_SCFG_OP_TYPE_SHIFT))
#endif


/* PROM_DL */

#define REG_SCFG_PROM_DL_E_SHIFT                           0
#define REG_SCFG_PROM_DL_E_SIZE                            1
#define REG_SCFG_PROM_DL_E_MASK                            0x01

#ifndef SDK_ASM
#define REG_SCFG_PROM_DL_FIELD( e ) \
    (u8)( \
    ((u32)(e) << REG_SCFG_PROM_DL_E_SHIFT))
#endif


/* FUSE0 */

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NN_HW_CTR_TEG2_ARM9_IOREG_SCFG_H_ */
#endif
