a236 28

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
} ohci_opregs __attribute__((aligned(32))); /* XXX align needed? */

