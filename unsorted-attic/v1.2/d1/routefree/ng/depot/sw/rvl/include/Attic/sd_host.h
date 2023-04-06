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

#ident "$Id: sd_host.h,v 1.1 2006/03/16 19:22:55 gbarnard Exp $"

/*
 * This file contains constants and macros used in the SD/SDIO bus
 * protocol.
 */

/*
 * Defines
 */
#define   SDHOST_MAX_CLOCK              25000000

#define   ENABLE_INTERRUPT              1
#define   DISABLE_INTERRUPT             0

#define SD_DEFAULT_CARD_ID_CLOCK_RATE 100000


/*
 * These are standard host bit registers 
 */
#define   HOSTREG_SYSADDRL      0x00  /* System Address Low */
#define   HOSTREG_SYSADDRH      0x02  /* System Address High */

#define   HOSTREG_BLOCKSZ       0x04  /* Block Size */
#define   HOSTREG_BLOCKCNT      0x06  /* Block Count */

#define   HOSTREG_ARG           0x08  /* Argument 0 */

#define   HOSTREG_TRANSMODE     0x0C  /* Transfer mode */
#define   HOSTREG_COMMAND       0x0E  /* Command */

#define   HOSTREG_RES0          0x10  /* Response 0 */
#define   HOSTREG_RES1          0x12  /* Response 1 */
#define   HOSTREG_RES2          0x14  /* Response 2 */
#define   HOSTREG_RES3          0x16  /* Response 3 */
#define   HOSTREG_RES4          0x18  /* Response 4 */
#define   HOSTREG_RES5          0x1A  /* Response 5 */
#define   HOSTREG_RES6          0x1C  /* Response 6 */
#define   HOSTREG_RES7          0x1E  /* Response 7 */
#define   HOSTREG_BUFFDP        0x20  /* Buffer Data port */
#define   HOSTREG_PSTATE        0x24  /* Present State low */
#define   HOSTREG_HOSTCTRLREG   0x28  /* Host Control Reg */
#define   HOSTREG_PWRCTRLREG    0x29  /* Power Control Reg*/
#define   HOSTREG_BLOCKGAPREG   0x2A  /* Block Gap Reg */
#define   HOSTREG_WAKEUPREG     0x2B  /* wake up Reg*/
#define   HOSTREG_CLOCKCTRL     0x2C  /* Clock Control */
#define   HOSTREG_TIMEOUTCTRL   0x2E  /* Timout Control */
#define   HOSTREG_SOFTRESET     0x2F  /* Software Reset */

#define   HOSTREG_NORMINTRSTAT  0x30  /* Normal Interrupt Status */
#define   HOSTREG_ERRINTRSTAT   0x32  /* Error Interrupt Status */

#define   HOSTREG_NORINTRSEN    0x34  /* Normal Interrupt Status Enable */
#define   HOSTREG_ERRINTRSEN    0x36  /* Error Interrupt Status Enable */

#define   HOSTREG_NORINTRSGEN   0x38  /* Normal Interrupt Signal Enable */

#define   HOSTREG_ERRINTRSGEN   0x3A  /* Error Interrupt Signal Enable */

#define   HOSTREG_CAPABILITY    0x40  /* Capabilities */
#define   HOSTREG_CAPBILITYR    0x44  /* Reserved capability (unused) */
#define   HOSTREG_MAXCURR       0x48  /* Max Curr Capabilities  */
#define   HOSTREG_SLOTINTRS     0xFC  /* Slot Interrput Status */
#define   HOSTREG_HOSTVER       0xFE  /* Host version */


/*
 * Command Argument Register 0x8
 */
#define CMD_ARG_WRITE           0x80000000

/*
 * Transfer Mode Register 0x0c
 */
#define DMA_ENABLE              0x0001
#define DMA_DISABLE             ~(0x0001)

#define BLOCK_COUNT_ENABLE      0x0002
#define BLOCK_COUNT_DISABLE     0x0000

#define AUTOCMD12_ENABLE        0x0004
#define AUTOCMD12_DISABLE       ~(0x0004)

#define DATA_READ               0x0018
#define DATA_WRITE              0x0000

#define MULTI_BLOCK             0x0020
#define SINGLE_BLOCK            0x0000

/*
 * Comand Register 0x0e
 */
#define CMD_CRC_CHECK_ENABLE    0x0008
#define CMD_CRC_CHECK_DISABLE   ~(0x8)

#define CMD_INDEX_CHECK_ENABLE  0x0010
#define CMD_INDEX_CHECK_DISABLE ~(0x10)

#define CMD_DATA_PRESENT_SEL    0x0020
#define CMD_DATA_PRESENT_UNSEL  ~(0x20)

#define CMD_ABORT               0x00C0
#define CMD_RESUME              0x0080
#define CMD_SUSPAND             0x0040
#define CMD_NORMAL              0x0000

#define RES_TYPE_SEL_NO         0x00
#define RES_TYPE_SEL_136        0x01
#define RES_TYPE_SEL_48         0x02
#define RES_TYPE_SEL_48b        0x03

#define CMD_INDEX_SHIFT                 8
#define CMD_INDEX_MASK                  0x3F00
#define CMD_RESPONSE_R2                 (RES_TYPE_SEL_136 | CMD_CRC_CHECK_ENABLE)
#define CMD_RESPONSE_R3_R4              RES_TYPE_SEL_48
#define CMD_RESPONSE_R1_R5_R6           (RES_TYPE_SEL_48 | CMD_CRC_CHECK_ENABLE | CMD_INDEX_CHECK_ENABLE)
#define CMD_RESPONSE_R1B_R5B            (RES_TYPE_SEL_48b | CMD_CRC_CHECK_ENABLE | CMD_INDEX_CHECK_ENABLE)

/*
 * command types
 */
#define SD_READ                         0
#define SD_WRITE                        1
#define SD_COMMAND                      2
#define SD_WRITE_REG                    3
#define SD_READ_REG                     4

/*
 * Present State Register 0x24
 */
#define STATE_CARD_INSERTED             0x00010000
#define BUFFER_READ_ENABLE              0x00000800
#define BUFFER_WRITE_ENABLE             0x00000400
#define PS_CMD_INHIBIT_DATA				0x00000002
#define PS_CMD_INHIBIT_CMD              0x00000001

/*
 * Host Control Reg 0x28
 */
#define HC_LED_ON                       0x01
#define HC_TRANSFER_WIDTH_4BIT          0x02
#define HC_TRANSFER_WIDTH_1BIT          0x00

/*
 * Power Control Reg 0x29
 */
#define PW_CTRL_33V                     0x0E
#define PW_CTRL_30V                     0x0C
#define PW_CTRL_18V                     0x0A
#define PW_CTRL_BUSPW_ON                0x01
#define PW_CTRL_BUSPW_OFF               ~(0x1)

/*
 * Clock Control Reg 0x2C
 */
#define SDCLK_INTERNAL_STABLE   0x0002
#define SDCLK_ENABLE                    0x0004
#define SDCLK_DISABLE                   ~(0x0004)

/* 
 * Normal Interrupt Status Reg 0x30 
 */
#define NISR_ERR_INTR                   0x8000

#define NISR_INTR_STATUS_ENABLE			0x0100
#define NISR_CARD_REMOVAL               0x0080
#define NISR_CARD_INSERT                0x0040
#define NISR_BUFF_READ_RDY				0x0020
#define NISR_BUFF_WRITE_RDY				0x0010
#define NISR_DMA_INTR                   0x0008
#define NISR_BG_TR_STOP					0x0004
#define NISR_DATA_TRAN_COMPLETE         0x0002
#define NISR_CMD_COMPLETE               0x0001

#define NISR_NO_ERROR                   0x0000

/* 
 * Error Interrupt Status Reg 0x32 
 */
#define EISR_VENDOR_ERROR               0xF000
#define EISR_NO_ERROR                   0x0000

#define IS_CMD_LINE_ERROR(y)            (((y) & 0x0F) != 0)
#define IS_DAT_LINE_ERROR(y)            (((y) & 0x70) != 0)

/*
 * Clock Control Reg 0x2C
 */
#define SDCLK_INTERNAL_ENABLE           0x0001

/* 
 * Wake up register 0x2B 
*/
#define WU_EVENT_CR_ENABLE              0x04
#define WU_EVENT_CI_ENABLE              0x02
#define WU_EVENT_INTR_ENABLE            0x01

/* 
 * Timeout Control Reg 0x2F 
 */
#define SR_DAT_LINE                     0x04
#define SR_CMD_LINE                     0x02
#define SR_RESET_ALL                    0x01

/* 
 * Error Interrupt Status Reg 0x32 
 */
#define EISR_AUTOCMD12_ERR              0x0100
#define EISR_DATA_CRC_ERR               0x0020
#define EISR_DATA_TIMEOUT               0x0010
#define EISR_CMD_INDEX_ERR              0x0008
#define EISR_CMD_ENDBIT_ERR             0x0004
#define EISR_CMD_CRC_ERR                0x0002
#define EISR_RESPONSE_TIMEOUT           0x0001

#define DEFAULT_TIMOUT_MS               2000

/* 
 * Normal Interrupt Status enable Reg 0x34
 * Normal Interrupt Signal enable Reg 0x38 
*/
#define ENABLE_NIS_CARDINTRS            0x0100

/* 
 * Capabilites reg 0x4A 
 */
#define CCAP_VOLTAGE_SUPPORT(y)   ((y & 0x7000000) >> 24)
#define CCAP_18V_SUPPORT                        0x4
#define CCAP_30V_SUPPORT                        0x2
#define CCAP_33V_SUPPORT                        0x1
#define CCAP_SUSRES_SUPPORT_MASK                0x800000
#define CCAP_DMA_SUPPORT_MASK                   0x400000
#define CCAP_HIGHSPD_SUPPORT_MASK               0x200000


#define CCAP_MAX_BLK_LEN(y)       ((y&0x30000) >> 16)
#define CCAP_MAX_BLK_2048                       0x2
#define CCAP_MAX_BLK_1024                       0x1
#define CCAP_MAX_BLK_512                        0x0

#define CCAP_BASECLOCK(y)         ((y & 0x3F00) >> 8)

/*
 * Standard Max Block Len Support for Host 
 */

#define SD_HOST_MXBLOCK_LEN_512                 512
#define SD_HOST_MXBLOCK_LEN_1024                1024
#define SD_HOST_MXBLOCK_LEN_2048                2048

#define SD_VDD_17_18            0x00000020      /** VDD voltage 1.7 - 1.8 */
#define SD_VDD_18_19            0x00000040      /** VDD voltage 1.8 - 1.9 */
#define SD_VDD_29_30            0x00020000      /** VDD voltage 2.9 ~ 3.0 */
#define SD_VDD_30_31            0x00040000      /** VDD voltage 3.0 ~ 3.1 */
#define SD_VDD_32_33            0x00100000      /** VDD voltage 3.2 ~ 3.3 */
#define SD_VDD_33_34            0x00200000      /** VDD voltage 3.3 ~ 3.4 */

/*
 * Macros
 */

/*
 * Structs
 */

/*
 * Inlines
 */

/*
 * Prototypes
 */

/* eof */
