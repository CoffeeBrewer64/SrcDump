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
 /* Data structures for the OHCI HCD. All section references refer to
    "OpenHCI for USB Release 1.0a". */

#ifndef __OHCI_H__
#define __OHCI_H__
#include <iostypes.h>
#include "ohci_types.h"
/* Endpoint descriptor [section 4.2] */
#define OHCI_ED_ALIGN 16
typedef struct ohci_ed {
 u32 flags;  
 u32 tailP;
 u32 headP;
 u32 nextED;
}  ohci_ed __attribute__((aligned(OHCI_ED_ALIGN)));

/* Flag defined by HCD. Have bits 27-31 free, as
 * specified in std. 
 */
#define OHCI_ED_USED_MASK  0x80000000

/* Fields in ohci_ed.flags */
#define OHCI_ED_RSVD_MASK   0x07ffffff 
#define OHCI_ED_FA_MASK     0x0000007f
#define OHCI_ED_FA_SHIFT    0
#define OHCI_ED_EN_MASK     0x00000780
#define OHCI_ED_EN_SHIFT    7

#define OHCI_ED_DIR_MASK    0x00001800
#define OHCI_ED_DIR_TD1     0x00000000  /* Get dir from TD */
#define OHCI_ED_DIR_OUT     0x00000800
#define OHCI_ED_DIR_IN      0x00001000 
#define OHCI_ED_DIR_TD2     0x00001800 /* Get dir from TD */

#define OHCI_ED_SPD_MASK    0x00002000
#define OHCI_ED_SPD_SHIFT   13
#define OHCI_ED_SKIP_MASK   0x00004000

#define OHCI_ED_FRMT_MASK   0x00008000
#define OHCI_ED_FRMT_GEN    0x00000000
#define OHCI_ED_FRMT_ISO    0x00008000

#define OHCI_ED_MPS_MASK    0x07ff0000
#define OHCI_ED_MPS_SHIFT   16
#define OHCI_ED_GETMPS(t)   ((t & OHCI_ED_MPS_MASK) >> 16)

/* Valid bits in ochi_ed.tailP */
#define OHCI_ED_TAILP_MASK 0xfffffff0

/* Bits in ochi_ed.headP */
#define OHCI_ED_HEADP_MASK 0xfffffff3
#define OHCI_ED_HLT_MASK   0x00000001
#define OHCI_ED_TGL_MASK   0x00000002

/* Valid bits in ochi_ed.nextED */
#define OHCI_ED_NEXTED_MASK 0xfffffff0

/* General transfer descriptor [section 4.3.1] */
#define OHCI_TD_ALIGN 32   /* at least 16 for general td, 32 for itd */
typedef struct ohci_td {
 u32 flags;  
 u32 cbp;    /* Current buffer pointer or bp0*/
 u32 nextTD; /* Next TD */
 u32 be;     /* Buffer end */

#if OH0
 u32 psw[4];  /* For iTD only */
#endif

 /* Stuff for HCD's use */
 OHCIrp *irp;
 u16 len;
} ohci_td __attribute((aligned(OHCI_TD_ALIGN)));

/* Fields in ohci_td.flags */
#define OHCI_TD_RSVD_MASK 0xfffc0000
#define OHCI_TD_R_MASK    0x00040000

#define OHCI_TD_DP_MASK   0x00180000
#define OHCI_TD_DP_SETUP  0x00000000
#define OHCI_TD_DP_OUT    0x00080000
#define OHCI_TD_DP_IN     0x00100000
#define OHCI_GET_TD_DIR(ep) (((ep) & 0x80)? OHCI_TD_DP_IN:OHCI_TD_DP_OUT)

#define OHCI_TD_DI_MASK   0x00e00000
#define OHCI_TD_DI_SHIFT  21 
#define OHCI_TD_T_MASK    0x03000000
#define OHCI_TD_T_DATA0   0x02000000
#define OHCI_TD_T_DATA1   0x03000000
#define OHCI_TD_T_SHIFT   24
#define OHCI_TD_EC_MASK   0x0e000000
#define OHCI_TD_CC_MASK   0xf0000000
#define OHCI_TD_CC_SHIFT     28 
/* Valid bits in ohci_td.nextTD */
#define OHCI_TD_NEXTTD_MASK

/* Isochronous transfer descriptor [section 4.3.2] */
#define OHCI_ITD_ALIGN 32
/* Struct same as ohci_td */

/* Fields in ohci_itd.flags */
#define OHCI_ITD_RSVD_MASK 0xf7e0ffff
#define OHCI_ITD_SF_MASK   0x0000ffff
#define OHCI_ITD_SF_SHIFT  0

#define OHCI_ITD_DI_MASK   0x00e00000
#define OHCI_ITD_DI_SHIFT  21

#define OHCI_ITD_FC_MASK   0x07000000
#define OHCI_ITD_FC_SHIFT  24

#define OHCI_ITD_CC_MASK   0xf0000000
#define OHCI_ITD_CC_SHIFT  28

#define OHCI_ITD_BP0_MASK  0xfffff000

/* Valid bits in ohci_itd.nextTD */
#define OHCI_NEXTTD_MASK  0xfffffff0
#define OHCI_PSWHI_MASK   0xffff0000
#define OHCI_PSWHI_SHIFT  12
#define OHCI_PSWLO_MASK   0x0000ffff

/* Fields in ohci_itd.pswN */
#define OHCI_ITD_PSW_SIZE_MASK 0x000007ff
#define OHCI_ITD_PSW_CC_MASK   0x0000f000

/* Condition codes [section 4.3.3] */
#define OHCI_CC_NOERROR    0x00000000  /* No error            */
#define OHCI_CC_CRC        0x00001000  /* CRC                 */
#define OHCI_CC_BITSTUFF   0x00002000  /* Bitstuffing         */
#define OHCI_CC_DTMISMATCH 0x00003000  /* DataToggleMismatch  */
#define OHCI_CC_STALL      0x00004000  /* Stall               */
#define OHCI_CC_DEVNOTRESP 0x00005000  /* DeviceNotResponding */
#define OHCI_CC_PIDCHK     0x00006000  /* PidCheckFailure     */
#define OHCI_CC_PID        0x00007000  /* UnexpectedPid       */
#define OHCI_CC_DOVERRUN   0x00008000  /* DataOverrun         */
#define OHCI_CC_DUNDERRUN  0x00009000  /* DataUnderrun        */
/* 0xa, 0xb reserved */
#define OHCI_CC_BOVERRUN   0x0000c000  /* BufferOverrun       */
#define OHCI_CC_BUNDERRUN  0x0000d000  /* BufferUnderrun      */
#define OHCI_CC_NOTACC     0x0000e000  /* Not accessed       */
#define OHCI_CC_NOTACC2    0x0000f000  /* Not accessed       */


/* HCCA format [section 4.4.1] */
#define OHCI_HCCA_ALIGN    256
#define OHCI_HCCA_INTTBL_OFFSET     0x0
#define OHCI_HCCA_FRMNUM_OFFSET     0x80
#define OHCI_HCCA_PAD1_OFFSET       0x82
#define OHCI_HHCA_DONEHEAD_OFFSET   0x84 
#define OHCI_HCCA_HCRSVD_OFFSET     0x88

#define OHCI_HCCA_INTTBL_SIZE       128  /* bytes */
#define OHCI_HCCA_NINT               32  /* 32 interrupt head pointers */
#define OHCI_HCCA_HCRSVD_SIZE       116  /*  bytes */

typedef struct ohci_hcca {
 u32 inttbl[OHCI_HCCA_NINT];
 u32 frmnum; /* includes 2 byte pad */
 u32 donehead; 
 u8 hcrsvd[116]; /* reserved for HC */
 u8 pad[4]; /* undefined bytes in spec */
} ohci_hcca __attribute__((aligned(OHCI_HCCA_ALIGN)));

/* Implementation specific data structures */
#define HCD_RHUB_INIT_MASK 0x1  /* RHUB initialized */
#define HCD_RM_INIT_MASK   0x2  /* RM initialized */
#define HCD_RHUB_EVENT     0xcafef00d

#define DBG_LINES_MAX 32
#define DBG_LINE_SIZE 24 /* bytes */

#define HOST_DELAY 1000L /* ns */  /* XXX is this correct? */
#define HUB_LS_SETUP 333L /* ns */ 
#define OHCI_FRAME_TIME_US 1000L /* us */
#define OHCI_FRAME_TIME_BITS 12000L /* us */
#define OHCI_FRAME_TIME_PERIODIC_BITS (900L * OHCI_FRAME_TIME_BITS)/1000L
#define OHCI_FRAME_TIME_PERIODIC_US (900L * OHCI_FRAME_TIME_US)/1000L

typedef struct ohci_hcd {
  struct ohci_opregs *opregs; /* Operational registers in IO space */
  struct ohci_hcca   *hcca;   /* Memory shared with HC */
  
  /* For HCD use */
  u32 frm_int; /* need to save frame interval (section 7.3.1) */
  ohci_ed *blk_head;
  ohci_ed *blk_tail;
  ohci_ed *ctrl_head;
  ohci_ed *ctrl_tail;
  ohci_ed *intr_list;
  u8 rwc; /* remote wakeup connected bit */

  IOSTimerId tmr;
  IOSTimerId tmrEv;
  IOSMessageQueueId qid;
  IOSMessageQueueId qidEv;
  IOSMessageQueueId rm_qid;
  IOSMessage mq[1];
  IOSMessage mqEv[1];
  IOSEvent event;
  OHCIrp *irp_head;
  OHCIrp *irp_tail;
  u8 ndp;
  u32 flags;
  u8 hc_rdb;
  u8 hc_wb;
  u32 load_ns;
  u32 openid;
  OHCCtrlReq *req;
  IOSThreadId rmId;
} ohci_hcd;


/* Utils */
#define OHCI_READ(regfield) \
        IO_READ(&(regfield))
#define OHCI_WRITE(regfield,value) \
        IO_WRITE(&(regfield), (value))

#define CPU_TO_OHCI32(val) \
	((u32)( \
		(((u32)(val) & (u32)0x000000ffUL) << 24) | \
		(((u32)(val) & (u32)0x0000ff00UL) <<  8) | \
		(((u32)(val) & (u32)0x00ff0000UL) >>  8) | \
		(((u32)(val) & (u32)0xff000000UL) >> 24) ))
   
#define OHCI_TO_CPU32(val) \
	((u32)( \
		(((u32)(val) & (u32)0x000000ffUL) << 24) | \
		(((u32)(val) & (u32)0x0000ff00UL) <<  8) | \
		(((u32)(val) & (u32)0x00ff0000UL) >>  8) | \
		(((u32)(val) & (u32)0xff000000UL) >> 24) ))

#define OHCI_TO_CPU16(val) \
	((u16)( \
		(((u16)(val) & (u16)0x00ffUL) << 8) | \
		(((u16)(val) & (u16)0xff00) >> 8) ))
#define CPU_TO_OHCI16(val) \
	((u16)( \
		(((u16)(val) & (u16)0x00ffUL) << 8) | \
		(((u16)(val) & (u16)0xff00) >> 8) ))
#endif /* __OHCI_H__ */
