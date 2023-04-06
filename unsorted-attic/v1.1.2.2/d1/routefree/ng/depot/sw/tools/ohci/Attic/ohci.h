d31 1
a62 84

/* General transfer descriptor [section 4.3.1] */
#define OHCI_TD_ALIGN 16
typedef struct ohci_td {
 u32 flags;  
 u32 cbp;    /* Current buffer pointer */
 u32 nextTD; /* Next TD */
 u32 be;     /* Buffer end */
} ohci_td __attribute((aligned(OHCI_TD_ALIGN)));

/* Fields in ohci_td.flags */
#define OHCI_TD_RSVD_MASK 0xfffc0000
#define OHCI_TD_R_MASK    0x00040000

#define OHCI_TD_DP_MASK   0x00180000
#define OHCI_TD_DP_SETUP  0x00000000
#define OHCI_TD_DP_OUT    0x00080000
#define OHCI_TD_DP_IN     0x00100000

#define OHCI_TD_DI_MASK   0x00e00000
#define OHCI_TD_T_MASK    0x03000000
#define OHCI_TD_EC_MASK   0x0e000000
#define OHCI_TD_CC_MASK   0xf0000000

/* Valid bits in ohci_td.nextTD */
#define OHCI_TD_NEXTTD_MASK

/* Isochronous transfer descriptor [section 4.3.2] */
#define OHCI_ITD_ALIGN 16
typedef struct ohci_itd {
   u32 flags; 
   u32 bp0;     /* Buffer page 0           */
   u32 nextTD;  /* NextTD                  */
   u32 be;      /* Buffer End              */
   u32 psw01;   /* Packet status words 0,1 */
   u32 psw23;   /* Packet status words 2,3 */
   u32 psw45;   /* Packet status words 4,5 */
   u32 psw67;   /* Packet status words 6,7 */
} ohci_itd  __attribute((aligned(OHCI_ITD_ALIGN)));

/* Fields in ohci_itd.flags */
#define OHCI_ITD_RSVD_MASK 0xf7e0ffff
#define OHCI_ITD_SF_MASK   0x0000ffff
#define OHCI_ITD_DI_MASK   0x00e00000
#define OHCI_ITD_FC_MASK   0x07000000
#define OHCI_ITD_CC_MASK   0xf0000000
#define OHCI_ITD_BPO_MASK  0xfffff000
/* Valid bits in ohci_itd.nextTD */
#define OHCI_NEXTTD_MASK  0xfffffff0
#define OHCI_PSWHI_MASK   0xffff0000
#define OHCI_PSWLO_MASK   0x0000ffff

/* Fields in ohci_itd.pswN */
#define OHCI_ITD_PSW_SIZE_MASK 0x000007ff
#define OHCI_ITD_PSW_CC_MASK   0x0000f000

/* Condition codes [section 4.3.3] */
#define OHCI_ITD_CC_NOERROR    0x00000000  /* No error            */
#define OHCI_ITD_CC_CRC        0x00001000  /* CRC                 */
#define OHCI_ITD_CC_BITSTUFF   0x00002000  /* Bitstuffing         */
#define OHCI_ITD_CC_DTMISMATCH 0x00003000  /* DataToggleMismatch  */
#define OHCI_ITD_CC_STALL      0x00004000  /* Stall               */
#define OHCI_ITD_CC_DEVNOTRESP 0x00005000  /* DeviceNotResponding */
#define OHCI_ITD_CC_PIDCHK     0x00006000  /* PidCheckFailure     */
#define OHCI_ITD_CC_PID        0x00007000  /* UnexpectedPid       */
#define OHCI_ITD_CC_DOVERRUN   0x00008000  /* DataOverrun         */
#define OHCI_ITD_CC_DUNDERRUN  0x00009000  /* DataUnderrun        */
/* 0xa, 0xb reserved */
#define OHCI_ITD_CC_BOVERRUN   0x0000c000  /* BufferOverrun       */
#define OHCI_ITD_CC_BUNDERRUN  0x0000d000  /* BufferUnderrun      */
#define OHCI_ITD_CC_NOTACC     0x0000e000  /* Not accessed       */
#define OHCI_ITD_CC_NOTACC2    0x0000f000  /* Not accessed       */


/* HCCA format [section 4.4.1] */
#define OHCI_HHCA_ALIGN    256
#define OHCI_HCCA_INTTBL_OFFSET     0x0
#define OHCI_HCCA_FRMNUM_OFFSET     0x80
#define OHCI_HCCA_PAD1_OFFSET       0x82
#define OHCI_HHCA_DONEHEAD_OFFSET   0x84 
#define OHCI_HCCA_HCRSVD_OFFSET     0x88

#define OHCI_HCCA_INTTBL_SIZE       128  /* bytes */
#define OHCI_HCCA_HCRSVD_SIZE       116  /*  bytes */
