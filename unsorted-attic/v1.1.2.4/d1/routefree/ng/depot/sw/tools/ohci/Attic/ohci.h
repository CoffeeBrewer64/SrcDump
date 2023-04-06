a17 1
#include <ohci_regs.h>
a141 1
#define OHCI_HCCA_NINT               32  /* 32 interrupt head pointers */
a143 23
typedef struct ohci_hhca {
 u32 inttbl[OHCI_HCCA_NINT];
 u32 frmnum; /* includes 2 byte pad */
 u32 donehead; 
 u8 hcrsvd[116]; /* reserved for HC */
 u8 pad[4]; /* undefined bytes in spec */
} ohci_hcca __attribute__((aligned(OHCI_HCCA_ALIGN)));

/* Implementation specific data structures */
typedef struct ohci_hcd {
  struct ohci_opregs *opregs; /* Operational registers in IO space */
  struct ohci_hcca   *hcca;   /* Memory shared with HC */
  
  /* For HCD use */
  u32 frm_int; /* need to save frame interval (section 7.3.1) */
  ohci_ed *blk_head;
  ohci_ed *ctrl_head;
  /*XXX iosc head needed? */
   
  ohci_ed  *free_ed;
  ohci_td  *free_td;
  ohci_itd *free_itd;
};
