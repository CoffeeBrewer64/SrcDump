a0 240
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
 /* Definitions from the OHCI standard. All section references refer to
    "OpenHCI for USB Release 1.0a". */

#ifndef __OHCI_REGS_H__
#define __OHCI_REGS_H__
#include <ios.h>
#include <iosdebug.h>
#include <iostypes.h>
#include <iosusbtypes.h>
#include <iosusb.h>

/* OHCI operational register offsets [Section 7] */
#define OHCI_REV_OFFSET           0x0     /* HcRevision           */
#define OHCI_CTRL_OFFSET          0x4     /* HcControl            */
#define OHCI_CMD_STAT_OFFSET      0x8     /* HcCommandStatus      */
#define OHCI_INT_STAT_OFFSET      0xc     /* HcInterruptStatus    */
#define OHCI_INT_EN_OFFSET        0x10    /* HcInterruptEnable    */
#define OHCI_INT_DIS_OFFSET       0x14    /* HcInterruptDisable   */

#define OHCI_HCCA_OFFSET          0x18    /* HcHCCA               */
#define OHCI_PRD_CURR_OFFSET      0x1c    /* HcPeriodCurrentED    */
#define OHCI_CTRL_HEAD_OFFSET     0x20    /* HcControlHeadED      */
#define OHCI_CTRL_CURR_OFFSET     0x24    /* HcControlCurrentED   */
#define OHCI_BLK_HEAD_OFFSET      0x28    /* HcBulkHeadED         */
#define OHCI_BLK_CURR_OFFSET      0x2c    /* HcBulkCurrentED      */
#define OHCI_DONE_HEAD_OFFSET     0x30    /* HcDoneHead           */

#define OHCI_FRM_INT_OFFSET       0x34    /* HcFmInterval         */
#define OHCI_FRM_REM_OFFSET       0x38    /* HcFmRemaining        */
#define OHCI_FRM_NUM_OFFSET       0x3c    /* HcFmNumber           */
#define OHCI_PRD_START_OFFSET     0x40    /* HcPeriodicStart      */
#define OHCI_LS_THRES_OFFSET      0x44    /* HcLSThreshold        */

#define OHCI_RHUB_DESCA_OFFSET    0x48    /* HcRhDescriptorA      */
#define OHCI_RHUB_DESCB_OFFSET    0x4c    /* HcRhDescriptorB      */
#define OHCI_RHUB_STAT_OFFSET     0x50    /* HcRhStatus           */
#define OHCI_RHUB_PSTAT_OFFSET    0x54    /* HcRhPortStatus[1]    */
/* Number of Port Status registers  == NDP (number of downstream ports)
 * RHUB_PSTAT_OFFSET[i] = RHUB_PSTAT_OFFSET + 4* (i -1)
 * i in { 1, 2, 3, ... , NDP}
 * XXX horti:  need getNDP
 */

/* Register descriptions:
 * *_RSVD_MASK  - masks out reserved bits (to 0)
 * *_RESET_VAL  - reset value
 * *-<field_name>_MASK - masks out all bits except those in <field_name>.
 */

/* HcRevision [section 7.1.1] */
#define OHCI_REV_RSVD_MASK             0x000000ff   
#define OHCI_REV_RESET_VAL             0x00000010
#define OHCI_REV_REV_MASK              0x000000ff

/* HcControl [section 7.1.2] */
#define OHCI_CTRL_RSVD_MASK            0x000007ff 
#define OHCI_CTRL_RESET_VAL            0x00000000
#define OHCI_CTRL_CBSR_MASK            0x00000003
#define OHCI_CTRL_PLE_MASK             0x00000004
#define OHCI_CTRL_IE_MASK              0x00000008
#define OHCI_CTRL_CLE_MASK             0x00000010
#define OHCI_CTRL_BLE_MASK             0x00000020
#define OHCI_CTRL_HCFS_MASK            0x000000c0
#define OHCI_CTRL_IR_MASK              0x00000100
#define OHCI_CTRL_RWC_MASK             0x00000200
#define OHCI_CTRL_RWE_MASK             0x00000400

#define OHCI_CTRL_CBSR_11              0x0
#define OHCI_CTRL_CBSR_21              0x1
#define OHCI_CTRL_CBSR_31              0x2
#define OHCI_CTRL_CBSR_41              0x3

#define OHCI_CTRL_HCFS_USBRESET        0x0
#define OHCI_CTRL_HCFS_USBRESUME       0x1
#define OHCI_CTRL_HCFS_USBOPERL        0x2
#define OHCI_CTRL_HCFS_USBSUSP         0x3

/* HcCommandStatus [section 7.1.3] */
#define OHCI_CMD_STAT_RSVD_MASK  0x0003000f
#define OHCI_CMD_STAT_RESET_VAL  0x00000000
#define OHCI_CMD_STAT_HCR_MASK   0x00000001
#define OHCI_CMD_STAT_CLF_MASK   0x00000002 
#define OHCI_CMD_STAT_BLF_MASK   0x00000004
#define OHCI_CMD_STAT_OCR_MASK   0x00000008
#define OHCI_CMD_STAT_SOC_MASK   0x00030000

/* HcInterruptStatus [section 7.1.4] */
#define OHCI_INT_STAT_RSVD_MASK  0x4000007f
#define OHCI_INT_STAT_RESET_VAL  0x00000000
#define OHCI_INT_STAT_SO_MASK    0x00000001
#define OHCI_INT_STAT_WDH_MASK   0x00000002
#define OHCI_INT_STAT_SF_MASK    0x00000004
#define OHCI_INT_STAT_RD_MASK    0x00000008
#define OHCI_INT_STAT_UE_MASK    0x00000010
#define OHCI_INT_STAT_FNO_MASK   0x00000020
#define OHCI_INT_STAT_RHSC_MASK  0x00000040
#define OHCI_INT_STAT_OC_MASK    0x40000000

/* HcInterruptEnable [section 7.1.5] */
#define OHCI_INT_EN_RSVD_MASK    0xc000007f
#define OHCI_INT_EN_RESET_VAL    0x00000000
#define OHCI_INT_EN_SO_MASK      0x00000001
#define OHCI_INT_EN_WDH_MASK     0x00000002
#define OHCI_INT_EN_SF_MASK      0x00000004
#define OHCI_INT_EN_RD_MASK      0x00000008
#define OHCI_INT_EN_UE_MASK      0x00000010
#define OHCI_INT_EN_FNO_MASK     0x00000020
#define OHCI_INT_EN_RHSC_MASK    0x00000040
#define OHCI_INT_EN_OC_MASK      0x40000000
#define OHCI_INT_EN_MIE_MASK     0x80000000

/* HcInterruptDisable [section 7.1.6] */
#define OHCI_INT_DIS_RSVD_MASK    0xc000007f
#define OHCI_INT_DIS_RESET_VAL    0x00000000
#define OHCI_INT_DIS_SO_MASK      0x00000001
#define OHCI_INT_DIS_WDH_MASK     0x00000002
#define OHCI_INT_DIS_SF_MASK      0x00000004
#define OHCI_INT_DIS_RD_MASK      0x00000008
#define OHCI_INT_DIS_UE_MASK      0x00000010
#define OHCI_INT_DIS_FNO_MASK     0x00000020
#define OHCI_INT_DIS_RHSC_MASK    0x00000040
#define OHCI_INT_DIS_OC_MASK      0x40000000
#define OHCI_INT_DIS_MIE_MASK     0x80000000

/* HcHCCA [section 7.2.1] */
#define OHCI_HCCA_RSVD_MASK    0xffffff00
#define OHCI_HCCA_RESET_VAL    0x00000000
#define OHCI_HCCA_HCCA_MASK    0xffffff00

/* HcPeriodCurrentED [section 7.2.2] */ 
#define OHCI_PRD_CURR_RSVD_MASK 0xfffffff0
#define OHCI_PRD_CURR_RESET_VAL 0x00000000
#define OHCI_PRD_CURR_PCED_MASK 0xfffffff0

/* HcControlHeadED [section 7.2.3] */ 
#define OHCI_CTRL_HEAD_RSVD_MASK 0xfffffff0
#define OHCI_CTRL_HEAD_RESET_VAL 0x00000000
#define OHCI_CTRL_HEAD_CHED_MASK 0xfffffff0

/* HcControlCurrentED [section 7.2.4] */ 
#define OHCI_CTRL_CURR_RSVD_MASK 0xfffffff0
#define OHCI_CTRL_CURR_RESET_VAL 0x00000000
#define OHCI_CTRL_CURR_CCED_MASK 0xfffffff0

/* HcBulkHeadED [section 7.2.5] */ 
#define OHCI_BLK_HEAD_RSVD_MASK 0xfffffff0
#define OHCI_BLK_HEAD_RESET_VAL 0x00000000
#define OHCI_BLK_HEAD_BHED_MASK 0xfffffff0

/* HcBulkCurrentED [section 7.2.6] */ 
#define OHCI_BLK_CURR_RSVD_MASK 0xfffffff0
#define OHCI_BLK_CURR_RESET_VAL 0x00000000
#define OHCI_BLK_CURR_BCED_MASK 0xfffffff0

/* HcDoneHead [section 7.2.7] */ 
#define OHCI_DONE_HEAD_RSVD_MASK 0xfffffff0
#define OHCI_DONE_HEAD_RESET_VAL 0x00000000
#define OHCI_DONE_HEAD_DH_MASK   0xfffffff0

/* HcFmInterval [section 7.3.1] */
#define OHCI_FRM_INT_RSVD_MASK   0xffff3fff
#define OHCI_FRM_INT_RESET_VAL   0x00002edf /* XXX FSMPS TBD? */
#define OHCI_FRM_INT_FI_MASK     0x00003fff
#define OHCI_FRM_INT_FSMPS_MASK  0x7fff0000
#define OHCI_FRM_INT_FIT_MASK    0x80000000

/* HcFmRemaining [section 7.3.2] */
#define OHCI_FRM_REM_RSVD_MASK   0x80003fff
#define OHCI_FRM_REM_RESET_VAL   0x00000000
#define OHCI_FRM_REM_FR_MASK     0x00003fff
#define OHCI_FRM_REM_FRT_MASK    0x80000000

/* HcFmNumber [section 7.3.3] */
#define OHCI_FRM_NUM_RSVD_MASK   0x0000ffff
#define OHCI_FRM_NUM_RESET_VAL   0x00000000
#define OHCI_FRM_NUM_FN_MASK     0x0000ffff

/* HcPeriodicStart [section 7.3.4] */
#define OHCI_PRD_START_RSVD_MASK 0x00003fff
#define OHCI_PRD_START_RESET_VAL 0x00000000
#define OHCI_PRD_START_PS_MASK   0x00003fff

/* HcLSThreshold [section 7.3.5] */
#define OHCI_LS_THRES_RSVD_MASK  0x00000fff
#define OHCI_LS_THRES_RESET_VAL  0x00000628
#define OHCI_LS_THRES_LST_MASK   0x00000fff

/* HcRhDescriptorA [section 7.4.1] */
#define OHCI_RHUB_DESCA_RSVD_MASK 0xff001fff
#define OHCI_RHUB_DESCA_RESET_VAL 0xff001fff /* XXX Implementation specific */
#define OHCI_RHUB_DESCA_NDP_MASK  0x000000ff
#define OHCI_RHUB_DESCA_PSM_MASK  0x00000100
#define OHCI_RHUB_DESCA_NPS_MASK  0x00000200
#define OHCI_RHUB_DESCA_DT_MASK   0x00000400
#define OHCI_RHUB_DESCA_OCPM_MASK 0x00000800
#define OHCI_RHUB_DESCA_NOCP_MASK 0x00001000
#define OHCI_RHUB_DESCA_POTPGT_MASK 0xff000000

/* HcRhDescriptorB [section 7.4.2] */
#define OHCI_RHUB_DESCB_RSVD_MASK  0xffffffff
#define OHCI_RHUB_DESCB_RESET_VAL  0xffffffff /* XXX Implementation specific */
#define OHCI_RHUB_DESCA_DR_MASK    0x0000ffff
#define OHCI_RHUB_DESCA_PPCM_MASK  0xffff0000

/* HcRhStatus [section 7.4.3] */
#define OHCI_RHUB_STAT_RSVD_MASK 0x80038003
#define OHCI_RHUB_STAT_RESET_VAL 0x00000000
#define OHCI_RHUB_STAT_LPS_MASK  0x00000001
#define OHCI_RHUB_STAT_OCI_MASK  0x00000002
#define OHCI_RHUB_STAT_DRWE_MASK 0x00001000
#define OHCI_RHUB_STAT_LPSC_MASK 0x00010000
#define OHCI_RHUB_STAT_OCIC_MASK 0x00020000
#define OHCI_RHUB_STAT_CRWE_MASK 0x80000000

/* HcRhPortStatus [section 7.4.4] */
#define OHCI_RHUB_PSTAT_RSVD_MASK 0x001f031f
#define OHCI_RHUB_PSTAT_RESET_VAL 0x00000000 /* bit 9 is dont-care */
#define OHCI_RHUB_PSTAT_CCS_MASK  0x00000001
#define OHCI_RHUB_PSTAT_PES_MASK  0x00000002
#define OHCI_RHUB_PSTAT_PSS_MASK  0x00000004
#define OHCI_RHUB_PSTAT_POCI_MASK 0x00000008
#define OHCI_RHUB_PSTAT_PRS_MASK  0x00000010
#define OHCI_RHUB_PSTAT_PPS_MASK  0x00000100
#define OHCI_RHUB_PSTAT_LSDA_MASK 0x00000200
#define OHCI_RHUB_PSTAT_CSC_MASK  0x00010000
#define OHCI_RHUB_PSTAT_PESC_MASK 0x00020000
#define OHCI_RHUB_PSTAT_PSSC_MASK 0x00040000
#define OHCI_RHUB_PSTAT_OCIC_MASK 0x00080000
#define OHCI_RHUB_PSTAT_PRSC_MASK 0x00100000
#endif /* __OHCI_REGS_H__ */
