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
#include <iostypes.h>

/* OHCI operational register offsets [Section 7] */
#define OHCI_REV_OFFSET           0x0     /* HcRevision           */
#define OHCI_CTRL_OFFSET          0x4     /* HcControl            */
#define OHCI_CMDSTAT_OFFSET      0x8     /* HcCommandStatus      */
#define OHCI_INTSTAT_OFFSET      0xc     /* HcInterruptStatus    */
#define OHCI_INTEN_OFFSET        0x10    /* HcInterruptEnable    */
#define OHCI_INTDIS_OFFSET       0x14    /* HcInterruptDisable   */

#define OHCI_HCCA_OFFSET          0x18    /* HcHCCA               */
#define OHCI_PRD_CURR_OFFSET      0x1c    /* HcPeriodCurrentED    */
#define OHCI_CTRL_HEAD_OFFSET     0x20    /* HcControlHeadED      */
#define OHCI_CTRL_CURR_OFFSET     0x24    /* HcControlCurrentED   */
#define OHCI_BLK_HEAD_OFFSET      0x28    /* HcBulkHeadED         */
#define OHCI_BLK_CURR_OFFSET      0x2c    /* HcBulkCurrentED      */
#define OHCI_DONE_HEAD_OFFSET     0x30    /* HcDoneHead           */

#define OHCI_FRMINT_OFFSET       0x34    /* HcFmInterval         */
#define OHCI_FRMREM_OFFSET       0x38    /* HcFmRemaining        */
#define OHCI_FRMNUM_OFFSET       0x3c    /* HcFmNumber           */
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
#define OHCI_CTRL_CBSR_SHIFT           0

#define OHCI_CTRL_PLE_MASK             0x00000004

#define OHCI_CTRL_IE_MASK              0x00000008

#define OHCI_CTRL_CLE_MASK             0x00000010

#define OHCI_CTRL_BLE_MASK             0x00000020

#define OHCI_CTRL_HCFS_MASK            0x000000c0
#define OHCI_CTRL_HCFS_SHIFT           6

#define OHCI_CTRL_IR_MASK              0x00000100

#define OHCI_CTRL_RWC_MASK             0x00000200

#define OHCI_CTRL_RWE_MASK             0x00000400

#define OHCI_CTRL_CBSR_11              (0 << OHCI_CTRL_CBSR_SHIFT)
#define OHCI_CTRL_CBSR_21              (1 << OHCI_CTRL_CBSR_SHIFT)
#define OHCI_CTRL_CBSR_31              (2 << OHCI_CTRL_CBSR_SHIFT)
#define OHCI_CTRL_CBSR_41              (3 << OHCI_CTRL_CBSR_SHIFT)

#define OHCI_CTRL_HCFS_USBRESET        (0 << OHCI_CTRL_HCFS_SHIFT)
#define OHCI_CTRL_HCFS_USBRESUME       (1 << OHCI_CTRL_HCFS_SHIFT)
#define OHCI_CTRL_HCFS_USBOPER         (2 << OHCI_CTRL_HCFS_SHIFT)
#define OHCI_CTRL_HCFS_USBSUSP         (3 << OHCI_CTRL_HCFS_SHIFT)

/* HcCommandStatus [section 7.1.3] */
#define OHCI_CMDSTAT_RSVD_MASK  0x0003000f
#define OHCI_CMDSTAT_RESET_VAL  0x00000000
#define OHCI_CMDSTAT_HCR_MASK   0x00000001
#define OHCI_CMDSTAT_CLF_MASK   0x00000002 
#define OHCI_CMDSTAT_BLF_MASK   0x00000004
#define OHCI_CMDSTAT_OCR_MASK   0x00000008
#define OHCI_CMDSTAT_SOC_MASK   0x00030000

/* HcInterruptStatus [section 7.1.4] */
#define OHCI_INTSTAT_RSVD_MASK  0x4000007f
#define OHCI_INTSTAT_RESET_VAL  0x00000000
#define OHCI_INTSTAT_SO_MASK    0x00000001
#define OHCI_INTSTAT_WDH_MASK   0x00000002
#define OHCI_INTSTAT_SF_MASK    0x00000004
#define OHCI_INTSTAT_RD_MASK    0x00000008
#define OHCI_INTSTAT_UE_MASK    0x00000010
#define OHCI_INTSTAT_FNO_MASK   0x00000020
#define OHCI_INTSTAT_RHSC_MASK  0x00000040
#define OHCI_INTSTAT_OC_MASK    0x40000000

/* HcInterruptEnable [section 7.1.5] */
#define OHCI_INTEN_RSVD_MASK    0xc000007f
#define OHCI_INTEN_ENALL_MASK   0xc000007f
#define OHCI_INTEN_RESET_VAL    0x00000000
#define OHCI_INTEN_SO_MASK      0x00000001
#define OHCI_INTEN_WDH_MASK     0x00000002
#define OHCI_INTEN_SF_MASK      0x00000004
#define OHCI_INTEN_RD_MASK      0x00000008
#define OHCI_INTEN_UE_MASK      0x00000010
#define OHCI_INTEN_FNO_MASK     0x00000020
#define OHCI_INTEN_RHSC_MASK    0x00000040
#define OHCI_INTEN_OC_MASK      0x40000000
#define OHCI_INTEN_MIE_MASK     0x80000000

/* HcInterruptDisable [section 7.1.6] */
#define OHCI_INTDIS_RSVD_MASK    0xc000007f
#define OHCI_INTDIS_RESET_VAL    0x00000000
#define OHCI_INTDIS_SO_MASK      0x00000001
#define OHCI_INTDIS_WDH_MASK     0x00000002
#define OHCI_INTDIS_SF_MASK      0x00000004
#define OHCI_INTDIS_RD_MASK      0x00000008
#define OHCI_INTDIS_UE_MASK      0x00000010
#define OHCI_INTDIS_FNO_MASK     0x00000020
#define OHCI_INTDIS_RHSC_MASK    0x00000040
#define OHCI_INTDIS_OC_MASK      0x40000000
#define OHCI_INTDIS_MIE_MASK     0x80000000

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
#define OHCI_FRMINT_RSVD_MASK   0xffff3fff
#define OHCI_FRMINT_RESET_VAL   0x00002edf /* XXX FSMPS TBD? */
#define OHCI_FRMINT_FI_MASK     0x00003fff
#define OHCI_FRMINT_FSMPS_MASK  0x7fff0000
#define OHCI_FRMINT_FIT_MASK    0x80000000

/* HcFmRemaining [section 7.3.2] */
#define OHCI_FRMREM_RSVD_MASK   0x80003fff
#define OHCI_FRMREM_RESET_VAL   0x00000000
#define OHCI_FRMREM_FR_MASK     0x00003fff
#define OHCI_FRMREM_FRT_MASK    0x80000000

/* HcFmNumber [section 7.3.3] */
#define OHCI_FRMNUM_RSVD_MASK   0x0000ffff
#define OHCI_FRMNUM_RESET_VAL   0x00000000
#define OHCI_FRMNUM_FN_MASK     0x0000ffff

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

#define OHCI_RHUB_DESCA_NDP_SHIFT  0
#define OHCI_RHUB_DESCA_PSM_SHIFT  8
#define OHCI_RHUB_DESCA_NPS_SHIFT  9
#define OHCI_RHUB_DESCA_DT_SHIFT   10
#define OHCI_RHUB_DESCA_OCPM_SHIFT 11
#define OHCI_RHUB_DESCA_NOCP_SHIFT 12
#define OHCI_RHUB_DESCA_POTPGT_SHIFT 24

/* HcRhDescriptorB [section 7.4.2] */
#define OHCI_RHUB_DESCB_RSVD_MASK  0xffffffff
#define OHCI_RHUB_DESCB_RESET_VAL  0xffffffff /* XXX Implementation specific */
#define OHCI_RHUB_DESCB_DR_MASK    0x0000ffff
#define OHCI_RHUB_DESCB_PPCM_MASK  0xffff0000

#define OHCI_RHUB_DESCB_DR_SHIFT   0
#define OHCI_RHUB_DESCB_PPCM_SHIFT  16

/* HcRhStatus [section 7.4.3] */
#define OHCI_RHUB_STAT_RSVD_MASK 0x80038003
#define OHCI_RHUB_STAT_RESET_VAL 0x00000000
#define OHCI_RHUB_STAT_LPS_MASK  0x00000001
#define OHCI_RHUB_STAT_OCI_MASK  0x00000002
#define OHCI_RHUB_STAT_DRWE_MASK 0x00001000
#define OHCI_RHUB_STAT_LPSC_MASK 0x00010000
#define OHCI_RHUB_STAT_OCIC_MASK 0x00020000
#define OHCI_RHUB_STAT_CRWE_MASK 0x80000000

#define OHCI_RHUB_STAT_LPS_SHIFT  0
#define OHCI_RHUB_STAT_OCI_SHIFT  1
#define OHCI_RHUB_STAT_DRWE_SHIFT 15
#define OHCI_RHUB_STAT_LPSC_SHIFT 16
#define OHCI_RHUB_STAT_OCIC_SHIFT 17
#define OHCI_RHUB_STAT_CRWE_SHIFT 30
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

#define OHCI_RHUB_PSTAT_CCS_SHIFT  0
#define OHCI_RHUB_PSTAT_PES_SHIFT  1
#define OHCI_RHUB_PSTAT_PSS_SHIFT  2
#define OHCI_RHUB_PSTAT_POCI_SHIFT 3
#define OHCI_RHUB_PSTAT_PRS_SHIFT  4
#define OHCI_RHUB_PSTAT_PPS_SHIFT  8
#define OHCI_RHUB_PSTAT_LSDA_SHIFT 9
#define OHCI_RHUB_PSTAT_CSC_SHIFT  16
#define OHCI_RHUB_PSTAT_PESC_SHIFT 17
#define OHCI_RHUB_PSTAT_PSSC_SHIFT 18
#define OHCI_RHUB_PSTAT_OCIC_SHIFT 19
#define OHCI_RHUB_PSTAT_PRSC_SHIFT 20

#define OHCI_SPD_LOW  1 /* LSDA = 1 */
#define OHCI_SPD_FULL 0 

/* OHCI operational registers */
#define USB_RHUB_PORT_MAX 4
typedef struct ohci_opregs { 
    u32 rev;                 /* HcRevision           */
    u32 ctrl;                /* HcControl            */
    u32 cmd_stat;            /* HcCommandStatus      */
    u32 int_stat;            /* HcInterruptStatus    */
    u32 int_en;              /* HcInterruptEnable    */
    u32 int_dis;             /* HcInterruptDisable   */
    u32 hcca;                /* HcHCCA               */
    u32 prd_curr;            /* HcPeriodCurrentED    */
    u32 ctrl_head;           /* HcControlHeadED      */
    u32 ctrl_curr;           /* HcControlCurrentED   */
    u32 blk_head;            /* HcBulkHeadED         */
    u32 blk_curr;            /* HcBulkCurrentED      */
    u32 done_head;           /* HcDoneHead           */
    u32 frm_int;             /* HcFmInterval         */
    u32 frm_rem;             /* HcFmRemaining        */
    u32 frm_num;             /* HcFmNumber           */
    u32 prd_start;           /* HcPeriodicStart      */
    u32 ls_thres;            /* HcLSThreshold        */
    u32 rhub_desca;          /* HcRhDescriptorA      */
    u32 rhub_descb;          /* HcRhDescriptorB      */
    u32 rhub_stat;           /* HcRhStatus           */
    u32 rhub_pstat[USB_RHUB_PORT_MAX];  /* HcRhPortStatus    */
} ohci_opregs __attribute__((aligned(32))); /* XXX horti: align needed?  */


/* Official wait times for resets, etc */
#define OHCI_SWRESET_DELAY 10000 /* 10ms section 5.1.1.4 */
#endif /* __OHCI_REGS_H__ */
