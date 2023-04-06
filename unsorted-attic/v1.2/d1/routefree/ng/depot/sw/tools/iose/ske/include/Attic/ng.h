/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

/* XXX horti - this is a template, for now */

#ifndef __NG_H__
#define __NG_H__

#ifndef IO_READ
#define IO_READ(addr)           (*(volatile u32 *)(addr))
#endif
#ifndef IO_WRITE
#define IO_WRITE(addr, val)     (*(volatile u32 *)(addr)) = (val)
#endif

#define BOOT_START              0x00000000
#define BOOT_END                0x00010000

#define KMEM_START              0x00010000
#define KMEM_END                0x00020000

#define REGS_START              0x00030000
#define REGS_END                0x00040000

#define MEM0_START              0x08000000
#define MEM0_END                0x0a000000
#define MEM1_START              0x0a000000
#define MEM1_END                0x0c000000
#define MEM2_START              0x0c000000
#define MEM2_END                0x0e000000
#define MEMU_START              0x0e000000
#define MEMU_END                0x10000000

#define DA_START                0x10000000
#define DA_END                  0x20000000

#define CPS_START               0x20000000
#define CPS_END                 0x40000000
#define CPS_CACHE_MASK          0x18000000
#define CPS_CACHE_SHIFT         27
#define CPS_CACHE(v)            (((v) & CPS_CACHE_MASK) >> CPS_CACHE_SHIFT)
#define CPS_CACHE_CC            0
#define CPS_CACHE_SC            1
#define CPS_CACHE_DA            2
#define CPS_CACHE_PT            3
#define CPS_OP_MASK             0x06000000
#define CPS_OP_SHIFT            25
#define CPS_OP(v)               (((v) & CPS_OP_MASK) >> CPS_OP_SHIFT)
#define CPS_OP_SET              0
#define CPS_OP_INV              1
#define CPS_OP_WB               2
#define CPS_OP_WBINV            3

#define CC_START                0x20000000
#define CC_END                  0x28000000  

#define SC_START                0x28000000  
#define SC_END                  0x30000000

#define DAX_START               0x30000000
#define DAX_END                 0x38000000

#define PT_START                0x38000000
#define PT_END                  0x40000000
#define PT_ENTRY_MASK           0x03ff0000
#define PT_ENTRY_SHIFT          16
#define PT_ENTRY(v)             (((v) & PT_ENTRY_MASK) >> PT_ENTRY_SHIFT)
#define PT_SC_PROT_MASK         0x00000180
#define PT_SC_PROT_SHIFT        7
#define PT_SC_PROT(v)           (((v) & PT_SC_PROT_MASK) >> PT_SC_PROT_SHIFT)
#define PT_ACCESS_NONE          0
#define PT_ACCESS_READ          1
#define PT_ACCESS_RW            2
#define PT_ACCESS_EXEC          3
#define PT_CC_PROT_MASK         0x00000600
#define PT_CC_PROT_SHIFT        9
#define PT_CC_PROT(v)           (((v) & PT_CC_PROT_MASK) >> PT_CC_PROT_SHIFT)
#define PT_TID_MASK             0x0000007f
#define PT_TID_SHIFT            0
#define PT_TID(v)               (((v) & PT_TID_MASK) >> PT_TID_SHIFT)

#define CPU_TO_BUS_ADDR(a)      (((a) & DA_START) ?                     \
                                    ((1 << 25) | ((a) & 0xffffff)) :    \
                                    ((a) & 0xffffff))
#define BUS_TO_CPU_ADDR(a)      (((a) & (1 << 25)) ?                    \
                                    (((a) & ~(1 << 25)) | DA_START) :   \
                                    ((a) | MEM0_START))
 
#define DEVID_RTID_SHIFT        16
#define DEVID_RTID_MASK         0x007f0000
#define DEVID_RTID(v)           (((v) & DEVID_RTID_MASK) >> DEVID_RTID_SHIFT)
#define DEVID_DTID_SHIFT        0
#define DEVID_DTID_MASK         0x0000007f
#define DEVID_DTID(v)           (((v) & DEVID_DTID_MASK) >> DEVID_DTID_SHIFT)

#define SC_REG_BASE             0x00030000

/* SHA Unit */
#define SHA_BASE_REG            (SC_REG_BASE+0x6000)

#define SHA_ID_REG              (SHA_BASE_REG+0x0)
#define SHA_ID_RTID_MASK        DEVID_RTID_MASK
#define SHA_ID_RTID_SHIFT       DEVID_RTID_SHIFT
#define SHA_ID_RTID(v)          DEVID_RTID(v)
#define SHA_ID_DTID_MASK        DEVID_DTID_MASK
#define SHA_ID_DTID_SHIFT       DEVID_DTID_SHIFT
#define SHA_ID_DTID(v)          DEVID_DTID(v)

#define SHA_CTRL_REG            (SHA_BASE_REG+0x4)
#define SHA_CTRL_EXEC           0x80000000
#define SHA_CTRL_MASK           0x40000000
#define SHA_CTRL_MVIOL          0x20000000
#define SHA_CTRL_BUF_PTR_MASK   0x001f0000
#define SHA_CTRL_BUF_PTR_SHIFT  16
#define SHA_CTRL_BUF_PTR(v)     (((v) & SHA_CTRL_BUF_PTR_MASK) >> SHA_CTRL_BUF_PTR_SHIFT)
#define SHA_CTRL_SIZE_MASK      0x0000ffc0
#define SHA_CTRL_SIZE_SHIFT     6
#define SHA_CTRL_SIZE(v)        (((v) & SHA_CTRL_SIZE_MASK) >> SHA_CTRL_SIZE_SHIFT)

#define SHA_MPTR_REG            (SHA_BASE_REG+0x8)
#define SHA_MPTR_MPTR_MASK      0x03fffff0

#define SHA_DATA_REG            (SHA_BASE_REG+0xc)

/* AES Unit */
#define AES_BASE_REG            (SC_REG_BASE+0x5000)

#define AES_ID_REG              (AES_BASE_REG+0x0)
#define AES_ID_RTID_MASK        DEVID_RTID_MASK
#define AES_ID_RTID_SHIFT       DEVID_RTID_SHIFT
#define AES_ID_RTID(v)          DEVID_RTID(v)
#define AES_ID_DTID_MASK        DEVID_DTID_MASK
#define AES_ID_DTID_SHIFT       DEVID_DTID_SHIFT
#define AES_ID_DTID(v)          DEVID_DTID(v)

#define AES_CTRL_REG            (AES_BASE_REG+0x4)
#define AES_CTRL_EXEC           0x80000000
#define AES_CTRL_MASK           0x40000000
#define AES_CTRL_VIOL_MASK      0x00180000
#define AES_CTRL_VIOL_SHIFT     19
#define AES_CTRL_VIOL(v)        (((v) & AES_CTRL_VIOL_MASK) >> AES_CTRL_VIOL_SHIFT)
#define AES_CTRL_CMD_MASK       0x00060000
#define AES_CTRL_CMD_SHIFT      17
#define AES_CTRL_CMD(v)      (((v) & AES_CTRL_CMD_MASK) >> AES_CTRL_CMD_SHIFT)
#define AES_CTRL_CHAIN          0x00010000
#define AES_CTRL_SIZE_MASK      0x0000fff0
#define AES_CTRL_SIZE_SHIFT     4
#define AES_CTRL_SIZE(v)     (((v) & AES_CTRL_SIZE_MASK) >> AES_CTRL_SIZE_SHIFT)

#define AES_DMA_CMD             0
#define AES_ENCRYPT_CMD         1
#define AES_DECRYPT_CMD         2
#define AES_KEYEXPAND_CMD       3

#define AES_NO_VIOL             0
#define AES_READ_VIOL           1
#define AES_WRITE_VIOL          2
#define AES_IV_VIOL             3

#define AES_RPTR_REG            (AES_BASE_REG+0x8)
#define AES_RPTR_PTR_MASK       0x03fffff0

#define AES_WPTR_REG            (AES_BASE_REG+0xc)
#define AES_WPTR_PTR_MASK       0x03fffff0

#define AES_IVPTR_REG           (AES_BASE_REG+0x10)
#define AES_IVPTR_PTR_MASK      0x03fffff0

#define AES_KEY_REG             (AES_BASE_REG+0x14)

/* AUD Unit */
#define AUD_BASE_REG            (SC_REG_BASE+0x4000)

#define AUD_ID_REG              (AUD_BASE_REG+0x0)
#define AUD_ID_RTID_MASK        DEVID_RTID_MASK
#define AUD_ID_RTID_SHIFT       DEVID_RTID_SHIFT
#define AUD_ID_RTID(v)          DEVID_RTID(v)
#define AUD_ID_DTID_MASK        DEVID_DTID_MASK
#define AUD_ID_DTID_SHIFT       DEVID_DTID_SHIFT
#define AUD_ID_DTID(v)          DEVID_DTID(v)

#define AUD_DAC_CTRL_REG        (AUD_BASE_REG+0x4)
#define AUD_DAC_CTRL_ENA        0x80000000
#define AUD_DAC_CTRL_MASK       0x40000000
#define AUD_DAC_CTRL_INTR       0x20000000
#define AUD_DAC_CTRL_EMPTY      0x10000000
#define AUD_DAC_CTRL_FULL       0x08000000
#define AUD_DAC_CTRL_MVIOL      0x04000000
#define AUD_DAC_CTRL_UNDER      0x02000000
#define AUD_DAC_CTRL_WE         0x00010000

#define AUD_ADC_CTRL_REG        (AUD_BASE_REG+0x8)
#define AUD_ADC_CTRL_ENA        0x80000000
#define AUD_ADC_CTRL_MASK       0x40000000
#define AUD_ADC_CTRL_INTR       0x20000000
#define AUD_ADC_CTRL_EMPTY      0x10000000
#define AUD_ADC_CTRL_FULL       0x08000000
#define AUD_ADC_CTRL_MVIOL      0x04000000
#define AUD_ADC_CTRL_OVER       0x02000000
#define AUD_ADC_CTRL_WE         0x00010000

#define AUD_DAC_PTR_REG         (AUD_BASE_REG+0xc)
#define AUD_DAC_PTR_SIZE_MASK   0xe0000000
#define AUD_DAC_PTR_SIZE_SHIFT  29
#define AUD_DAC_PTR_SIZE(v)     (((v) & AUD_DAC_PTR_SIZE_MASK) >> AUD_DAC_PTR_SIZE_SHIFT)
#define AUD_DAC_PTR_PTR_MASK    0x03fffff0
#define AUD_DAC_PTR_PTR_SHIFT   4
#define AUD_DAC_PTR_PTR(v)      (((v) & AUD_DAC_PTR_PTR_MASK) >> AUD_DAC_PTR_PTR_SHIFT)

#define AUD_ADC_PTR_REG         (AUD_BASE_REG+0x10)
#define AUD_ADC_PTR_SIZE_MASK   0xe0000000
#define AUD_ADC_PTR_SIZE_SHIFT  29
#define AUD_ADC_PTR_SIZE(v)     (((v) & AUD_ADC_PTR_SIZE_MASK) >> AUD_ADC_PTR_SIZE_SHIFT)
#define AUD_ADC_PTR_PTR_MASK    0x03fffff0
#define AUD_ADC_PTR_PTR_SHIFT   4
#define AUD_ADC_PTR_PTR(v)      (((v) & AUD_ADC_PTR_PTR_MASK) >> AUD_ADC_PTR_PTR_SHIFT)

#define AUD_DAC_CFG_REG         (AUD_BASE_REG+0x14)
#define AUD_DAC_CFG_MCLK2BCLK_EDGE      0x40000000
#define AUD_DAC_CFG_BCLK2LR_EDGE        0x20000000
#define AUD_DAC_CFG_BCLK2DO_EDGE        0x10000000
#define AUD_DAC_CFG_SFS_MODE            0x08000000
#define AUD_DAC_CFG_DO_DLY              0x04000000
#define AUD_DAC_CFG_LR_INV              0x02000000
#define AUD_DAC_CFG_MCLK_COM            0x01000000
#define AUD_DAC_CFG_BCLK_DIV_MASK       0x0000ff00
#define AUD_DAC_CFG_BCLK_DIV_SHIFT      8
#define AUD_DAC_CFG_BCLK_DIV(v)         (((v) & AUD_DAC_CFG_BCLK_DIV_MASK) >> AUD_DAC_CFG_BCLK_DIV_SHIFT)
#define AUD_DAC_CFG_LR_DIV_MASK         0x000000ff
#define AUD_DAC_CFG_LR_DIV_SHIFT        0
#define AUD_DAC_CFG_LR_DIV(v)           (((v) & AUD_DAC_CFG_LR_DIV_MASK) >> AUD_DAC_CFG_LR_DIV_SHIFT)

#define AUD_ADC_CFG_REG         (AUD_BASE_REG+0x18)
#define AUD_ADC_CFG_MCLK2BCLK_EDGE      0x40000000
#define AUD_ADC_CFG_BCLK2LR_EDGE        0x20000000
#define AUD_ADC_CFG_BCLK2DI_EDGE        0x10000000
#define AUD_ADC_CFG_SFS_MODE            0x08000000
#define AUD_ADC_CFG_DI_DLY              0x04000000
#define AUD_ADC_CFG_LR_INV              0x02000000
#define AUD_ADC_CFG_BCLK_DIV_MASK       0x0000ff00
#define AUD_ADC_CFG_BCLK_DIV_SHIFT      8
#define AUD_ADC_CFG_BCLK_DIV(v)         (((v) & AUD_ADC_CFG_BCLK_DIV_MASK) >> AUD_ADC_CFG_BCLK_DIV_SHIFT)
#define AUD_ADC_CFG_LR_DIV_MASK         0x000000ff
#define AUD_ADC_CFG_LR_DIV_SHIFT        0
#define AUD_ADC_CFG_LR_DIV(v)           (((v) & AUD_ADC_CFG_LR_DIV_MASK) >> AUD_ADC_CFG_LR_DIV_SHIFT)
 
#define AUD_PLL_CTL_REG         (AUD_BASE_REG+0x1c)
#define AUD_PLL_CTL_PD          0x80000000
#define AUD_PLL_CTL_BP          0x40000000
#define AUD_PLL_CTL_OD_MASK     0x30000000
#define AUD_PLL_CTL_OD_SHIFT    28
#define AUD_PLL_CTL_OD(v)       (((v & AUD_PLL_CTL_OD_MASK) >> AUD_PLL_CTL_OD_SHIFT)
#define AUD_PLL_CTL_F_MASK     0x0ff00000
#define AUD_PLL_CTL_F_SHIFT    20
#define AUD_PLL_CTL_F(v)       (((v & AUD_PLL_CTL_F_MASK) >> AUD_PLL_CTL_F_SHIFT)
#define AUD_PLL_CTL_R_MASK     0x000f8000
#define AUD_PLL_CTL_R_SHIFT    15
#define AUD_PLL_CTL_R(v)       (((v & AUD_PLL_CTL_R_MASK) >> AUD_PLL_CTL_R_SHIFT)
#define AUD_PLL_CTL_ADC_MRST    0x00004000
#define AUD_PLL_CTL_DAC_MRST    0x00002000

#define AUD_MCLK_DIV_REG         (AUD_BASE_REG+0x20)
#define AUD_MCLK_DIV_ADC_DIV_MASK   0xffff0000
#define AUD_MCLK_DIV_ADC_DIV_SHIFT  16
#define AUD_MCLK_DIV_ADC_DIV(v) (((v) & AUD_MCLK_DIV_ADC_MASK) >> AUD_MCLK_DIV_ADC_DIV_SHIFT)
#define AUD_MCLK_DIV_DAC_DIV_MASK   0x0000ffff
#define AUD_MCLK_DIV_DAC_DIV_SHIFT  0
#define AUD_MCLK_DIV_DAC_DIV(v) (((v) & AUD_MCLK_DIV_DAC_MASK) >> AUD_MCLK_DIV_DAC_DIV_SHIFT)

#define AUD_GPIO_DIR_REG        (AUD_BASE_REG+0x24)
#define AUD_GPIO_DIR_DIR_MASK   0x000000ff
#define AUD_GPIO_DIR_DIR_SHIFT  0
#define AUD_GPIO_DIR_DIR(v)     (((v) & AUD_GPIO_DIR_DIR_MASK) >> AUD_GPIO_DIR_DIR_SHIFT)

#define AUD_GPIO_DATA_REG       (AUD_BASE_REG+0x28)
#define AUD_GPIO_DATA_DATA_MASK 0x000000ff
#define AUD_GPIO_DATA_DATA_SHIFT 0
#define AUD_GPIO_DATA_DATA(v)   (((v) & AUD_GPIO_DATA_DATA_MASK) >> AUD_GPIO_DATA_DATA_SHIFT)

/* USB Unit */
#define USB_BASE_REG            (SC_REG_BASE+0x3000)

#define USB_ID_REG              (USB_BASE_REG+0x0)
#define USB_ID_RTID_MASK        DEVID_RTID_MASK
#define USB_ID_RTID_SHIFT       DEVID_RTID_SHIFT
#define USB_ID_RTID(v)          DEVID_RTID(v)
#define USB_ID_DTID_MASK        DEVID_DTID_MASK
#define USB_ID_DTID_SHIFT       DEVID_DTID_SHIFT
#define USB_ID_DTID(v)          DEVID_DTID(v)

#define USB_CTRL_REG            (USB_BASE_REG+0x4)
#define USB_CTRL_ENA            0x80000000
#define USB_CTRL_MASK           0x40000000
#define USB_CTRL_INT_MASK       0x3c000000
#define USB_CTRL_INT_SHIFT      26
#define USB_CTRL_INT(v)         (((v) & USB_CTRL_INT_MASK) >> USB_CTRL_INT_SHIFT)
#define USB_CTRL_RST_INT        0x02000000
#define USB_CTRL_WE             0x01000000
#define USB_CTRL_USB_ADDR_MASK  0x01ff0000
#define USB_CTRL_USB_ADDR_SHIFT 16
#define USB_CTRL_USB_ADDR(v)    (((v) & USB_CTRL_USB_ADDR_MASK) >> USB_CTRL_USB_ADDR_SHIFT)
#define USB_CTRL_IN_ISO         0x00008000
#define USB_CTRL_OUT_ISO        0x00004000
#define USB_CTRL_SUSP           0x00002000
#define USB_CTRL_WAKEUP         0x00001000
#define USB_CTRL_CFG_DONE       0x00000800
#define USB_CTRL_RESET          0x00000400
#define USB_CTRL_PULLUP         0x00000200
#define USB_CTRL_I_WE           0x00000100
#define USB_CTRL_A_WE           0x00000080   
#define USB_CTRL_SUSP_INT       0x00000040
#define USB_CTRL_BUF_PTR_MASK   0x0000000f
#define USB_CTRL_BUF_PTR_SHIFT  0
#define USB_CTRL_BUF_PTR(v)     (((v) & USB_CTRL_BUF_PTR_MASK) >> USB_CTRL_BUF_PTR_SHIFT)

#define USB_DATA_REG            (USB_BASE_REG+0x8)

#define USB_IN0_PTR             (USB_BASE_REG+0x10)  
#define USB_IN0_PTR_VALID       0x80000000
#define USB_IN0_PTR_ST_SET      0x40000000
#define USB_IN0_PTR_ST_CLR      0x20000000
#define USB_IN0_PTR_UF          0x10000000
#define USB_IN0_PTR_VIOL        0x08000000
#define USB_IN0_PTR_REWIND      0x04000000
#define USB_IN0_PTR_PTR_MASK    0x03fffff0
#define USB_IN0_PTR_PTR_SHIFT   4
#define USB_IN0_PTR_PTR(v)      (((v) & USB_IN0_PTR_PTR_MASK) >> USB_IN0_PTR_PTR_SHIFT)
#define USB_IN0_PTR_INT         0x00000008
#define USB_IN0_PTR_WE          0x00000004
#define USB_IN0_PTR_SETUP       0x00000002
#define USB_IN0_PTR_ZERO        0x00000001

#define USB_IN0_LEN             (USB_BASE_REG+0x14)  
#define USB_IN0_LEN_RUN_LEN_MASK  0x07ff0000
#define USB_IN0_LEN_RUN_LEN_SHIFT 16
#define USB_IN0_LEN_RUN_LEN(v)  (((v) & USB_IN0_LEN_RUN_LEN_MASK) >> USB_IN0_LEN_RUN_LEN_SHIFT)
#define USB_IN0_LEN_LEN_MASK    0x0000000f
#define USB_IN0_LEN_LEN_SHIFT   0
#define USB_IN0_LEN_LEN(v)      (((v) & USB_IN0_LEN_LEN_MASK) >> USB_IN0_LEN_LEN_SHIFT)

#define USB_IN1_PTR             (USB_BASE_REG+0x18)  
#define USB_IN1_PTR_VALID       0x80000000
#define USB_IN1_PTR_ST_SET      0x40000000
#define USB_IN1_PTR_ST_CLR      0x20000000
#define USB_IN1_PTR_UF          0x10000000
#define USB_IN1_PTR_VIOL        0x08000000
#define USB_IN1_PTR_REWIND      0x04000000
#define USB_IN1_PTR_PTR_MASK    0x03fffff0
#define USB_IN1_PTR_PTR_SHIFT   4
#define USB_IN1_PTR_PTR(v)      (((v) & USB_IN1_PTR_PTR_MASK) >> USB_IN1_PTR_PTR_SHIFT)
#define USB_IN1_PTR_INT         0x00000008
#define USB_IN1_PTR_WE          0x00000004
#define USB_IN1_PTR_SETUP       0x00000002
#define USB_IN1_PTR_ZERO        0x00000001

#define USB_IN1_LEN             (USB_BASE_REG+0x1c)  
#define USB_IN1_LEN_RUN_LEN_MASK  0x07ff0000
#define USB_IN1_LEN_RUN_LEN_SHIFT 16
#define USB_IN1_LEN_RUN_LEN(v)  (((v) & USB_IN1_LEN_RUN_LEN_MASK) >> USB_IN1_LEN_RUN_LEN_SHIFT)
#define USB_IN1_LEN_LEN_MASK    0x0000000f
#define USB_IN1_LEN_LEN_SHIFT   0
#define USB_IN1_LEN_LEN(v)      (((v) & USB_IN1_LEN_LEN_MASK) >> USB_IN1_LEN_LEN_SHIFT)

#define USB_IN2_PTR             (USB_BASE_REG+0x20)  
#define USB_IN2_PTR_VALID       0x80000000
#define USB_IN2_PTR_ST_SET      0x40000000
#define USB_IN2_PTR_ST_CLR      0x20000000
#define USB_IN2_PTR_UF          0x10000000
#define USB_IN2_PTR_VIOL        0x08000000
#define USB_IN2_PTR_REWIND      0x04000000
#define USB_IN2_PTR_PTR_MASK    0x03fffff0
#define USB_IN2_PTR_PTR_SHIFT   4
#define USB_IN2_PTR_PTR(v)     (((v) & USB_IN2_PTR_PTR_MASK) >> USB_IN2_PTR_PTR_SHIFT)
#define USB_IN2_PTR_INT         0x00000008
#define USB_IN2_PTR_WE          0x00000004
#define USB_IN2_PTR_SETUP       0x00000002
#define USB_IN2_PTR_ZERO        0x00000001

#define USB_IN2_LEN             (USB_BASE_REG+0x24)  
#define USB_IN2_LEN_RUN_LEN_MASK  0x07ff0000
#define USB_IN2_LEN_RUN_LEN_SHIFT 16
#define USB_IN2_LEN_RUN_LEN(v)  (((v) & USB_IN2_LEN_RUN_LEN_MASK) >> USB_IN2_LEN_RUN_LEN_SHIFT)
#define USB_IN2_LEN_LEN_MASK    0x000007ff
#define USB_IN2_LEN_LEN_SHIFT   0
#define USB_IN2_LEN_LEN(v)      (((v) & USB_IN2_LEN_LEN_MASK) >> USB_IN2_LEN_LEN_SHIFT)

#define USB_OUT0_PTR             (USB_BASE_REG+0x28)  
#define USB_OUT0_PTR_VALID       0x80000000
#define USB_OUT0_PTR_ST_SET      0x40000000
#define USB_OUT0_PTR_ST_CLR      0x20000000
#define USB_OUT0_PTR_OF          0x10000000
#define USB_OUT0_PTR_VIOL        0x08000000
#define USB_OUT0_PTR_REWIND      0x04000000
#define USB_OUT0_PTR_PTR_MASK    0x03fffff0
#define USB_OUT0_PTR_PTR_SHIFT   4
#define USB_OUT0_PTR_PTR(v)     (((v) & USB_OUT0_PTR_PTR_MASK) >> USB_OUT0_PTR_PTR_SHIFT)
#define USB_OUT0_PTR_INT         0x00000008
#define USB_OUT0_PTR_WE          0x00000004
#define USB_OUT0_PTR_SETUP       0x00000002
#define USB_OUT0_PTR_ZERO        0x00000001

#define USB_OUT0_LEN             (USB_BASE_REG+0x2c)  
#define USB_OUT0_LEN_RUN_LEN_MASK  0x07ff0000
#define USB_OUT0_LEN_RUN_LEN_SHIFT 16
#define USB_OUT0_LEN_RUN_LEN(v)  (((v) & USB_OUT0_LEN_RUN_LEN_MASK) >> USB_OUT0_LEN_RUN_LEN_SHIFT)
#define USB_OUT0_LEN_LEN_MASK    0x0000000f
#define USB_OUT0_LEN_LEN_SHIFT   0
#define USB_OUT0_LEN_LEN(v)      (((v) & USB_OUT0_LEN_LEN_MASK) >> USB_OUT0_LEN_LEN_SHIFT)

#define USB_OUT1_PTR             (USB_BASE_REG+0x30)  
#define USB_OUT1_PTR_VALID       0x80000000
#define USB_OUT1_PTR_ST_SET      0x40000000
#define USB_OUT1_PTR_ST_CLR      0x20000000
#define USB_OUT1_PTR_OF          0x10000000
#define USB_OUT1_PTR_VIOL        0x08000000
#define USB_OUT1_PTR_REWIND      0x04000000
#define USB_OUT1_PTR_PTR_MASK    0x03fffff0
#define USB_OUT1_PTR_PTR_SHIFT   4
#define USB_OUT1_PTR_PTR(v)     (((v) & USB_OUT1_PTR_PTR_MASK) >> USB_OUT1_PTR_PTR_SHIFT)
#define USB_OUT1_PTR_INT         0x00000008
#define USB_OUT1_PTR_WE          0x00000004
#define USB_OUT1_PTR_SETUP       0x00000002
#define USB_OUT1_PTR_ZERO        0x00000001

#define USB_OUT1_LEN             (USB_BASE_REG+0x34)  
#define USB_OUT1_LEN_RUN_LEN_MASK  0x07ff0000
#define USB_OUT1_LEN_RUN_LEN_SHIFT 16
#define USB_OUT1_LEN_RUN_LEN(v)  (((v) & USB_OUT1_LEN_RUN_LEN_MASK) >> USB_OUT1_LEN_RUN_LEN_SHIFT)
#define USB_OUT1_LEN_LEN_MASK    0x0000000f
#define USB_OUT1_LEN_LEN_SHIFT   0
#define USB_OUT1_LEN_LEN(v)      (((v) & USB_OUT1_LEN_LEN_MASK) >> USB_OUT1_LEN_LEN_SHIFT)

#define USB_OUT3_PTR             (USB_BASE_REG+0x38)  
#define USB_OUT3_PTR_VALID       0x80000000
#define USB_OUT3_PTR_ST_SET      0x40000000
#define USB_OUT3_PTR_ST_CLR      0x20000000
#define USB_OUT3_PTR_OF          0x10000000
#define USB_OUT3_PTR_VIOL        0x08000000
#define USB_OUT3_PTR_REWIND      0x04000000
#define USB_OUT3_PTR_PTR_MASK    0x03fffff0
#define USB_OUT3_PTR_PTR_SHIFT   4
#define USB_OUT3_PTR_PTR(v)     (((v) & USB_OUT3_PTR_PTR_MASK) >> USB_OUT3_PTR_PTR_SHIFT)
#define USB_OUT3_PTR_INT         0x00000008
#define USB_OUT3_PTR_WE          0x00000004
#define USB_OUT3_PTR_SETUP       0x00000002
#define USB_OUT3_PTR_ZERO        0x00000001

#define USB_OUT3_LEN             (USB_BASE_REG+0x3c)  
#define USB_OUT3_LEN_RUN_LEN_MASK  0x07ff0000
#define USB_OUT3_LEN_RUN_LEN_SHIFT 16
#define USB_OUT3_LEN_RUN_LEN(v)  (((v) & USB_OUT3_LEN_RUN_LEN_MASK) >> USB_OUT3_LEN_RUN_LEN_SHIFT)
#define USB_OUT3_LEN_LEN_MASK    0x000007ff
#define USB_OUT3_LEN_LEN_SHIFT   0
#define USB_OUT3_LEN_LEN(v)      (((v) & USB_OUT3_LEN_LEN_MASK) >> USB_OUT3_LEN_LEN_SHIFT)

/* FLC Unit */
#define FL_BASE_REG             (SC_REG_BASE+0x2000)

#define FL_ID_REG               (FL_BASE_REG+0x0)
#define FL_ID_RTID_MASK         DEVID_RTID_MASK
#define FL_ID_RTID_SHIFT        DEVID_RTID_SHIFT
#define FL_ID_RTID(v)           DEVID_RTID(v)
#define FL_ID_DTID_MASK         DEVID_DTID_MASK
#define FL_ID_DTID_SHIFT        DEVID_DTID_SHIFT
#define FL_ID_DTID(v)           DEVID_DTID(v)

#define FL_CTRL_REG             (FL_BASE_REG+0x4)
#define FL_CTRL_EXEC            0x80000000
#define FL_CTRL_MASK            0x40000000
#define FL_CTRL_MVIOL           0x20000000
#define FL_CTRL_ADP_MASK        0x1f000000
#define FL_CTRL_ADP_SHIFT       24
#define FL_CTRL_ADP(v)          (((v) & FL_CTRL_ADP_MASK) >> FL_CTRL_ADP_SHIFT)
#define FL_CTRL_CMD_MASK        0x00ff0000
#define FL_CTRL_CMD_SHIFT       16
#define FL_CTRL_CMD(v)          (((v) & FL_CTRL_CMD_MASK) >> FL_CTRL_CMD_SHIFT)
#define FL_CTRL_RDY             0x00008000
#define FL_CTRL_WDP             0x00004000
#define FL_CTRL_RDP             0x00002000
#define FL_CTRL_ECC             0x00001000
#define FL_CTRL_SIZE_MASK       0x00000fff
#define FL_CTRL_SIZE_SHIFT      0
#define FL_CTRL_SIZE(v)         (((v) & FL_CTRL_SIZE_MASK) >> FL_CTRL_SIZE_SHIFT)

#define FL_CONF_REG             (FL_BASE_REG+0x8)
#define FL_CONF_WP              0x80000000
#define FL_CONF_EOC_MASK        0x70000000
#define FL_CONF_EOC_SHIFT       28
#define FL_CONF_EOC(v)          (((v) & FL_CONF_EOC_MASK) >> FL_CONF_EOC_SHIFT)
#define FL_CONF_DEV             0x08000000
#define FL_CONF_RSA_MASK        0x07000000
#define FL_CONF_RSA_SHIFT       24
#define FL_CONF_RSA(v)          (((v) & FL_CONF_RSA_MASK) >> FL_CONF_RSA_SHIFT)
#define FL_CONF_REA_MASK        0x00ff0000
#define FL_CONF_REA_SHIFT       16
#define FL_CONF_REA(v)          (((v) & FL_CONF_REA_MASK) >> FL_CONF_REA_SHIFT)
#define FL_CONF_WEA_MASK        0x0000ff00
#define FL_CONF_WEA_SHIFT       8
#define FL_CONF_WEA(v)          (((v) & FL_CONF_WEA_MASK) >> FL_CONF_WEA_SHIFT)
#define FL_CONF_CAA_MASK        0x000000ff
#define FL_CONF_CAA_SHIFT       0
#define FL_CONF_CAA(v)          (((v) & FL_CONF_CAA_MASK) >> FL_CONF_CAA_SHIFT)
 
#define FL_AD0_REG              (FL_BASE_REG+0xc)
#define FL_AD0_PTR_MASK         0x0000ffff

#define FL_AD1_REG              (FL_BASE_REG+0x10)
#define FL_AD1_PTR_MASK         0x00ffffff

#define FL_MA0_REG              (FL_BASE_REG+0x14)
#define FL_MA0_PTR_MASK         0x03fffff0

#define FL_MA1_REG              (FL_BASE_REG+0x18)
#define FL_MA1_PTR_MASK         0x03fffff0

/* CIF Unit */
#define CIF_BASE_REG            (SC_REG_BASE+0x1000)

#define CIF_CTRL_REG            (CIF_BASE_REG+0x0)
#define CIF_CTRL_EMU            0x80000000
#define CIF_CTRL_EMU_GPIO       0x10000000
#define CIF_CTRL_EMU_FLASH      0x08000000
#define CIF_CTRL_EMU_EEROM      0x04000000
#define CIF_CTRL_EMU_SRAM       0x02000000
#define CIF_CTRL_EMU_ROM        0x01000000
#define CIF_CTRL_STATE          0x00800000
#define CIF_CTRL_INTR_ROM       0x00000100
#define CIF_CTRL_INTR_IPC       0x00000080
#define CIF_CTRL_INTR_FLASH     0x00000040
#define CIF_CTRL_INTR_EEROM     0x00000020
#define CIF_CTRL_SRAM_TIMER     0x00000010
#define CIF_CTRL_SRAM_VIOL      0x00000008
#define CIF_CTRL_ROM_VIOL       0x00000004
#define CIF_CTRL_BUS_INV        0x00000002
#define CIF_CTRL_BUS_VAL        0x00000001

#define ROM_CFG1_REG            (CIF_BASE_REG+0x4)
#define ROM_CFG1_MASK_VIOL      0x80000000
#define ROM_CFG1_MASK_INTR      0x40000000
#define ROM_CFG1_IPC_EN         0x20000000
#define ROM_CFG1_WIN_EN         0x10000000
#define ROM_CFG1_TYPE           0x08000000
#define ROM_CFG1_INTR_POL       0x04000000
#define ROM_CFG1_BASE_MASK      0x01fffff0
#define ROM_CFG1_BASE_SHIFT     4
#define ROM_CFG1_BASE(v)        (((v) & ROM_CFG1_BASE_MASK) >> ROM_CFG1_BASE_SHIFT)

#define ROM_CFG2_REG            (CIF_BASE_REG+0x8)
#define ROM_CFG2_SIZE_MASK      0x00f00000
#define ROM_CFG2_SIZE_SHIFT     20
#define ROM_CFG2_SIZE(v)        (((v) & ROM_CFG2_SIZE_MASK) >> ROM_CFG2_SIZE_SHIFT)
#define ROM_CFG2_DA_MASK        0x0007fff0
#define ROM_CFG2_DA_SHIFT       4
#define ROM_CFG2_DA(v)          (((v) & ROM_CFG2_DA_MASK) >> ROM_CFG2_DA_SHIFT)

#define IPC_OUT_REG             (CIF_BASE_REG+0x10)

#define IPC_IN_REG              (CIF_BASE_REG+0x14)

#define IPC_CTRL_REG            (CIF_BASE_REG+0xc)
#define IPC_CTRL_MASK_WE        0x00008000
#define IPC_CTRL_MASK_SRAM      0x00000800
#define IPC_CTRL_MASK_ROM       0x00000400
#define IPC_CTRL_MASK_ACK       0x00000200
#define IPC_CTRL_MASK_MSG       0x00000100
#define IPC_CTRL_SRAM_VIOL      0x00000080
#define IPC_CTRL_ROM_VIOL       0x00000040
#define IPC_CTRL_IN_ACK         0x00000008
#define IPC_CTRL_IN_MSG         0x00000004
#define IPC_CTRL_OUT_ACK        0x00000002
#define IPC_CTRL_OUT_MSG        0x00000001

#define SRAM_CFG_REG            (CIF_BASE_REG+0x18)
#define SRAM_CFG_MASK_VIOL      0x80000000
#define SRAM_CFG_MASK_TMR       0x40000000
#define SRAM_CFG_TMR_ENA        0x10000000
#define SRAM_CFG_BASE_MASK      0x00078000
#define SRAM_CFG_BASE_SHIFT     15
#define SRAM_CFG_BASE(v)        (((v) & SRAM_CFG_BASE_MASK) >> SRAM_CFG_BASE_SHIFT)
#define SRAM_CFG_TIMER_MASK     0x00000fff
#define SRAM_CFG_TIMER_SHIFT    0
#define SRAM_CFG_TIMER(v)       (((v) & SRAM_CFG_TIMER_MASK) >> SRAM_CFG_TIMER_SHIFT)

/* SYS Unit */
#define SYS_BASE_REG            (SC_REG_BASE+0x0000)

#define SYS_SMP_REG             (SYS_BASE_REG+0x0)
#define SYS_SMP_CPU_ID          0x80000000
#define SYS_SMP_SMP_IN          0x20000000
#define SYS_SMP_SMP_OUT         0x10000000
#define SYS_SMP_SMP_RST_MASK    0x0c000000
#define SYS_SMP_SMP_RST_SHIFT   26
#define SYS_SMP_SMP_RST(v)      (((v) & SYS_SMP_SMP_RST_MASK) >> SYS_SMP_SMP_RST_SHIFT)
#define SYS_SMP_SET_IMASK       0x02000000
#define SYS_SMP_SET_TID         0x01000000
#define SYS_SMP_IMASK_MASK      0x00ff0000
#define SYS_SMP_IMASK_SHIFT     16
#define SYS_SMP_IMASK(v)        (((v) & SYS_SMP_IMASK_MASK) >> SYS_SMP_IMASK_SHIFT)
#define SYS_SMP_IPEND_MASK      0x0000ff00
#define SYS_SMP_IPEND_SHIFT     8
#define SYS_SMP_IPEND(v)        (((v) & SYS_SMP_IPEND_MASK) >> SYS_SMP_IPEND_SHIFT)
#define SYS_SMP_TID_MASK        0x0000007f
#define SYS_SMP_TID_SHIFT       0
#define SYS_SMP_TID(v)          (((v) & SYS_SMP_TID_MASK) >> SYS_SMP_TID_SHIFT)

#define SYS_SYS_INTR            0x01
#define SYS_CIF_INTR            0x02
#define SYS_FLASH_INTR          0x04
#define SYS_USB_INTR            0x08
#define SYS_AUD_INTR            0x10
#define SYS_AES_INTR            0x20
#define SYS_SHA_INTR            0x40

#define SYS_CTRL_REG            (SYS_BASE_REG + 0x4)
#define SYS_CTRL_SOFT_RST       0x80000000
#define SYS_CTRL_MEM_FLIP       0x00000010
#define SYS_CTRL_P8K            0x00000008
#define SYS_CTRL_CACHE_CONF_MASK 0x00000007
#define SYS_CTRL_CACHE_CONF_SHIFT 0
#define SYS_CTRL_CACHE_CONF(v)  (((v) & SYS_CTRL_CACHE_CONF_MASK) >> SYS_CTRL_CACHE_CONF_SHIFT)
#define SYS_CACHE_CONF_DA       0
#define SYS_CACHE_CONF_SC       1
#define SYS_CACHE_CONF_CC       2
#define SYS_CACHE_CONF_DA_CC    3
#define SYS_CACHE_CONF_SC_CC    4
#define SYS_CACHE_CONF_DA_SC_CC 5
#define SYS_CACHE_CONF_SC_DA_CC 6
#define SYS_CACHE_CONF_CC_DA_SC 7

#define KP_CTRL_REG             (SYS_BASE_REG + 0x8)
#define KP_CTRL_EXEC            0x80000000
#define KP_CTRL_WR              0x40000000
#define KP_CTRL_RT              0x08000000
#define KP_CTRL_SRST            0x04000000
#define KP_CTRL_TVAL_MASK       0x03f00000
#define KP_CTRL_TVAL_SHIFT      20
#define KP_CTRL_TVAL(v)         (((v) & KP_CTRL_TVAL_MASK) >> KP_CTRL_TVAL_SHIFT)
#define KP_CTRL_R               0x00020000
#define KP_CTRL_W               0x00010000
#define KP_CTRL_ADDR_MASK       0x0000ffff
#define KP_CTRL_ADDR_SHIFT      0
#define KP_CTRL_ADDR(v)         (((v) & KP_CTRL_ADDR_MASK) >> KP_CTRL_ADDR_SHIFT)

/* XXX horti Move to debug.h later */
#define __SK_EMU_DBG__ 0

#if __SK_EMU_DBG__
#include <stdio.h>
extern FILE *dbg_fp;
#define DBG_PRINTF(x) fprintf x; fflush(dbg_fp);
#define DBG_ENTRY  \
  fprintf(dbg_fp,"Entering: %s\n", __FUNCTION__);
#define DBG_EXIT  \
  fprintf(dbg_fp,"Leaving: %s\n", __FUNCTION__);

#else

#define DBG_PRINTF(x) /* Debug is off */
#define DBG_ENTRY   /* Debug is off */
#define DBG_EXIT   /* Debug is off */

#endif 

#endif /*__NG_H__*/
