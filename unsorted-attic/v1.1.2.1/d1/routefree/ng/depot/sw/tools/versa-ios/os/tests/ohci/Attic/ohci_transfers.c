a0 89
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
#include <ios.h>
#include <versaios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <ohci.h>
#include <ohci_regs.h>
#include <usb11.h>

#include "ohci_core.h"
#include "ohci_ed.h"
#include "ohci_td.h"

extern struct ohci_device __ohci_dev[OHCI_DEV_MAX]; 
extern struct ohci_ed __ohci_edpool[OHCI_ED_MAX];
extern struct ohci_td __ohci_tdpool[OHCI_TD_MAX];

IOSError 
ohci_CtrlMsg (struct ohci_hcd *hcd, u16 devnum, struct USB_CtrlReq *req, u8 ep, u8 addr)
{
   struct ohci_ed *ed;
   struct ohci_td *td;
   struct ohci_td *td_dummy;
   u32 flags;
    /* Get ed0 for device */
   ed =  __ohci_edpool + __ohci_dev[devnum].dev.dev.ed0;
   td = __ohci_tdpool + allocTD();
   td_dummy = __ohci_tdpool + allocTD();
   if ( NULL == td || NULL == td_dummy) {
       OHCI_DBG("allocTD failed\n");
       return IOS_ERROR_MAX;
   }
   
   ed->headP = CPU_TO_OHCI32(td);
   ed->tailP = CPU_TO_OHCI32(td_dummy);
   ed->nextED = 0;
   /* Setup ED flags */
   {
   flags = (req->bmRequestType & USB_REQ_HOST2DEV)? OHCI_ED_DIR_OUT: OHCI_ED_DIR_IN; 
   flags |=  ((addr << OHCI_ED_FA_SHIFT) & OHCI_ED_FA_MASK) 
                | ((ep << OHCI_ED_EN_SHIFT) & OHCI_ED_EN_MASK)
                | ((__ohci_dev[devnum].dev.dev.spd << OHCI_ED_SPD_SHIFT) & OHCI_ED_SPD_MASK)
                | ((__ohci_dev[devnum].dev.dev.maxP << OHCI_ED_MPS_SHIFT) & OHCI_ED_MPS_MASK);
   flags &= OHCI_ED_RSVD_MASK;
   ed->flags = CPU_TO_OHCI32(flags);
   }
    /* Fill TD */   
   td->cbp = CPU_TO_OHCI32(&req);
   td->nextTD = CPU_TO_OHCI32(td_dummy);
   td->be = CPU_TO_OHCI32(&req + sizeof(req) - 1);
   td->flags = 2<<OHCI_TD_T_SHIFT;

   /* Enqueue ED */
   {
    ohci_ed *tmp = (ohci_ed *) OHCI_READ(hcd->opregs->ctrl_head);
    OHCI_DBG("ed head = %p\n", tmp);
    if ( NULL != tmp ) {
        while (tmp->nextED != NULL) tmp = (ohci_ed *)tmp->nextED;
        tmp->nextED = CPU_TO_OHCI32(ed);
    }
    else {
        OHCI_WRITE(hcd->opregs->ctrl_head, CPU_TO_OHCI32(ed));
    }
    OHCI_DBG("enqueued ed = %p\n", ed);
   } 
   OHCI_DBG(" before xfer: td->flags = 0x%08x\n", td->flags);
   /* Enable processing of control lists */
   { 
       u32 reg = OHCI_READ(hcd->opregs->ctrl) | OHCI_CTRL_CLE_MASK;
       if (0 == (OHCI_READ(hcd->opregs->ctrl) & OHCI_CTRL_CLE_MASK)) {
           OHCI_DBG("Enabling control list processing\n");
           OHCI_WRITE(hcd->opregs->ctrl, reg);
       }
       OHCI_WRITE(hcd->opregs->cmd_stat, OHCI_CMDSTAT_CLF_MASK);
   }
   usleep(50000);
   OHCI_DBG("td->flags = 0x%08x\n", td->flags);
   OHCI_DBG("cmd_stat = 0x%08x\n", OHCI_READ(hcd->opregs->cmd_stat));
   return IOS_ERROR_OK;
}
