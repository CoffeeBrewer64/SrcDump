d12 1
a12 1
#ident "$Id: sd_slot.c,v 1.1 2006/01/30 23:41:45 gbarnard Exp $"
d39 5
a43 5
	#include "../../include/sd.h"
	#include "../../include/sd_card.h"
	#include "../../include/sd_host.h"
	#include "../../include/sd_ioctl.h"
	#include "../../include/sd_debug.h"
d45 1
a45 1
	extern void kfree (const void* objp);
d84 2
a85 3
		IOSError rv = sdusleep((u32)usecs,sdQid,"");
		//udelay(usecs);
		if (rv!=IOS_ERROR_OK)
d87 1
a87 1
			printf("%s Error. Status = 0x%x\n",__FUNCTION__,rv);
d89 1
d99 35
a133 35
  { HOSTREG_SYSADDRL, "HOSTREG_SYSADDRL", 2 },
  { HOSTREG_SYSADDRH, "HOSTREG_SYSADDRH", 2 },
  { HOSTREG_BLOCKSZ, "HOSTREG_BLOCKSZ", 2 },
  { HOSTREG_BLOCKCNT, "HOSTREG_BLOCKCNT", 2 },
  { HOSTREG_ARG, "HOSTREG_ARG", 2 },
  { HOSTREG_TRANSMODE, "HOSTREG_TRANSMODE", 2 },
  { HOSTREG_COMMAND, "HOSTREG_COMMAND", 2 },
  { HOSTREG_RES0, "HOSTREG_RES0", 2 },
  { HOSTREG_RES1, "HOSTREG_RES1", 2 },
  { HOSTREG_RES2, "HOSTREG_RES2", 2 },
  { HOSTREG_RES3, "HOSTREG_RES3", 2 },
  { HOSTREG_RES4, "HOSTREG_RES4", 2 },
  { HOSTREG_RES5, "HOSTREG_RES5", 2 },
  { HOSTREG_RES6, "HOSTREG_RES6", 2 },
  { HOSTREG_RES7, "HOSTREG_RES7", 2 },
  { HOSTREG_BUFFDP, "HOSTREG_BUFFDP", 2 },
  { HOSTREG_PSTATE, "HOSTREG_PSTATE", 2 },
  { HOSTREG_HOSTCTRLREG, "HOSTREG_HOSTCTRLREG", 1 },
  { HOSTREG_PWRCTRLREG, "HOSTREG_PWRCTRLREG", 1 },
  { HOSTREG_BLOCKGAPREG, "HOSTREG_BLOCKGAPREG", 1 },
  { HOSTREG_WAKEUPREG, "HOSTREG_WAKEUPREG", 1 },
  { HOSTREG_CLOCKCTRL, "HOSTREG_CLOCKCTRL", 2 },
  { HOSTREG_TIMEOUTCTRL, "HOSTREG_TIMEOUTCTRL", 2 },
  { HOSTREG_SOFTRESET, "HOSTREG_SOFTRESET", 2 },
  { HOSTREG_NORMINTRSTAT, "HOSTREG_NORMINTRSTAT", 2 },
  { HOSTREG_ERRINTRSTAT, "HOSTREG_ERRINTRSTAT", 2 },
  { HOSTREG_NORINTRSEN, "HOSTREG_NORINTRSEN", 2 },
  { HOSTREG_ERRINTRSEN, "HOSTREG_ERRINTRSEN", 2 },
  { HOSTREG_NORINTRSGEN, "HOSTREG_NORINTRSGEN", 2 },
  { HOSTREG_ERRINTRSGEN, "HOSTREG_ERRINTRSGEN", 2 },
  { HOSTREG_CAPABILITY, "HOSTREG_CAPABILITY", 4 },
  { HOSTREG_CAPBILITYR, "HOSTREG_CAPBILITYR", 2 },
  { HOSTREG_MAXCURR, "HOSTREG_MAXCURR", 2 },
  { HOSTREG_SLOTINTRS, "HOSTREG_SLOTINTRS", 2 },
  { HOSTREG_HOSTVER, "HOSTREG_HOSTVER", 2 },
d136 1
a136 1
int sdpci_debug = DEBUG_PCI_ERR|DEBUG_PCI_IRQN; //|DEBUG_PCI_IRQ
d162 5
a166 2
    for (i = 0; i < (sizeof(slot_regs) / sizeof (struct _slot_regs)); i++) {
        switch (slot_regs[i].reg_width) {
d170 1
a170 1
            PCI_DEBUG (DEBUG_PCI_ERR, "%s 0x%x\n",
d176 1
a176 1
            PCI_DEBUG (DEBUG_PCI_ERR,"%s 0x%x\n",
d182 1
a182 1
            PCI_DEBUG (DEBUG_PCI_ERR,"%s 0x%x\n",
d186 1
a186 2
            PCI_DEBUG (DEBUG_PCI_ERR, "%s: bad reg width %d\n",
                    __FUNCTION__, slot_regs[i].reg_width);
d189 1
d283 3
d287 1
d302 1
a302 1

d565 2
a566 1
    if(SDHostslot_SoftwareReset(slot, SR_RESET_ALL)) {
d580 35
a614 1

d651 10
a660 11
    if (SDHostslot_SoftwareReset(slot, SR_RESET_ALL)) {
        PCI_DEBUG (DEBUG_PCI_INIT, "%s: timeout control and enable interrupts\n",
                __FUNCTION__);
        /* timeout control */
        WRITE_HOST_U8((u32)slot->m_base, HOSTREG_TIMEOUTCTRL,
                      slot->m_TimeoutControl);
#if 0
        /* 
         * Enable error interrupt status and signals for all but the vendor
         * errors. This allows any normal error to generate an interrupt.
         */
d662 14
a675 21
        WRITE_HOST_U16((u32)slot->m_base, HOSTREG_ERRINTRSEN, 
                       ~EISR_NO_ERROR & EISR_VENDOR_ERROR);
        WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSGEN, 
                       ~NISR_NO_ERROR & EISR_VENDOR_ERROR);

        /* 
         * Enable all interrupt signals. 
         */
        WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSGEN, 0x1FF);
        
        /* 
         * Enable card insert and remove status. During execution, we will enable
         * and disable interrupt statuses as desired.
         */        
        WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSEN, 
                       NISR_CARD_INSERT | NISR_CARD_REMOVAL );
#else
       /* 
         * Enable error interrupt status and signals for all but the vendor
         * errors. This allows any normal error to generate an interrupt.
         */
a676 17
        WRITE_HOST_U16((u32)slot->m_base, HOSTREG_ERRINTRSEN, 0);
        WRITE_HOST_U16((u32)slot->m_base, HOSTREG_ERRINTRSGEN, 0);
        
        /* 
         * Enable card insert and remove status. During execution, we will enable
         * and disable interrupt statuses as desired.
         */        
        WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSGEN, NISR_CARD_INSERT | NISR_CARD_REMOVAL);
        WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSEN,NISR_CARD_INSERT | NISR_CARD_REMOVAL);
        
#endif                                              
        status = SD_STATUS_SUCCESS;
    } else {
        PCI_DEBUG (DEBUG_PCI_ERR, "%s: device not responding\n",
                __FUNCTION__);
        status = SD_STATUS_DEVICE_NOT_RESPONDING;
    }
d678 1
d748 1
a748 2
extern struct _sd_request *request_global;

d818 3
d843 3
a845 2
    //PCI_DEBUG (DEBUG_PCI_IRQN, "%s NormIntStatus(%d):0x%04x Cmd:%d",
    //           "   ------->", (u32)slot->m_slotindex, wIntStatus, command);
d859 14
a872 5
            if (request_global) 
            {
                request_global->norint = 0;
                request_global->status = status;
            }
d875 4
a878 1
 		if (request_global) 
d880 17
a896 27
	        /*
	         * Command Complete handling.
	         */
	        if ( wIntStatus & NISR_CMD_COMPLETE ) 
	        {
	            request_global->norint |= NISR_CMD_COMPLETE; /* polling feedback */
	            //command = READ_HOST_U16((u32)slot->m_base, HOSTREG_COMMAND);
	            //PCI_DEBUG (DEBUG_PCI_IRQN, "%s[Command]\n", ":");
	            slot->m_fCommandCompleteOccurred = 1;
	        }

	        /*
	         * DMA data transfer complete handling.
	         */
	        if ( wIntStatus & NISR_DATA_TRAN_COMPLETE ) 
	        {
	            request_global->norint |= NISR_DATA_TRAN_COMPLETE;
	            //command = READ_HOST_U16((u32)slot->m_base, HOSTREG_COMMAND);
	            //PCI_DEBUG (DEBUG_PCI_IRQN, "%s[Transfer]\n", ":");
	            printf("[Transfer]");
	        }	
	        
	        if ( wIntStatus & NISR_DMA_INTR)
			{
				request_global->norint |= NISR_DMA_INTR;
				printf("[DMA Boundary]");
			}
d898 16
a913 5
	        if ( wIntStatus & NISR_BUFF_READ_RDY)
			{
				request_global->norint |= NISR_BUFF_READ_RDY;
				printf("[Read]");
			}
d915 2
a916 20
	        if ( wIntStatus & NISR_BUFF_WRITE_RDY)
			{
				request_global->norint |= NISR_BUFF_WRITE_RDY;
				printf("[Write]");
			}
	        
	        /* Async functionality I.e. : (NISR_BUFF_R_RDY|... NISR_DATA_TRAN_COMPLETE) */	 
	        if (wIntStatus & request_global->callback_on_irq)
	        {
	        	/* for polling feedback */
	        	request_global->norint |= wIntStatus & request_global->callback_on_irq;
	        	
	            //request_global->norint |= NISR_DATA_TRAN_COMPLETE;
	            //command = READ_HOST_U16((u32)slot->m_base, HOSTREG_COMMAND);
	            //PCI_DEBUG (DEBUG_PCI_IRQN, 
	            ///printf("[Data Ready]");

			   /* clear slot callback interrupts */
			    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORMINTRSTAT, wIntStatus & request_global->callback_on_irq);				
	        } 
d922 1
a922 1
        if (wIntStatus & (NISR_CARD_INSERT | NISR_CARD_REMOVAL)) 
d924 2
a925 1
        	PCI_DEBUG (DEBUG_PCI_IRQN, "%s Insert/Remove\n", ":");
d928 9
d942 8
a949 36
    if (slot->m_fCommandCompleteOccurred) {
        if (request_global) {
            PCI_DEBUG (DEBUG_PCI_IRQ, "%s: request_global 0x%x\n",
                       __FUNCTION__, (u32)request_global);
            request_global->response[0] = READ_HOST_U16((u32)slot->m_base,
                                                       HOSTREG_RES0);
            request_global->response[1] = READ_HOST_U16((u32)slot->m_base,
                                                       HOSTREG_RES1);
            request_global->response[2] = READ_HOST_U16((u32)slot->m_base,
                                                       HOSTREG_RES2);
            request_global->response[3] = READ_HOST_U16((u32)slot->m_base,
                                                       HOSTREG_RES3);
            request_global->response[4] = READ_HOST_U16((u32)slot->m_base,
                                                       HOSTREG_RES4);
            request_global->response[5] = READ_HOST_U16((u32)slot->m_base,
                                                       HOSTREG_RES5);
            request_global->response[6] = READ_HOST_U16((u32)slot->m_base,
                                                       HOSTREG_RES6);
            request_global->response[7] = READ_HOST_U16((u32)slot->m_base,
                                                       HOSTREG_RES7);
            if (request_global->status == 0) {
                request_global->status = SD_STATUS_SUCCESS;
            }
            PCI_DEBUG (DEBUG_PCI_IRQ, "%s: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
                    __FUNCTION__,
                    request_global->response[0],
                    request_global->response[1],
                    request_global->response[2],
                    request_global->response[3],
                    request_global->response[4],
                    request_global->response[5],
                    request_global->response[6],
                    request_global->response[7]);

            request_global->cmd_wait++;
        }
d951 1
a951 1

d960 2
a961 1
        if (dwPresentState & STATE_CARD_INSERTED) {
d964 2
a965 1
            if (slot->m_fCardPresent == 0 ) {
d971 3
a973 1
        } else {
d976 2
a977 1
            if (slot->m_fCardPresent) {
d986 2
d998 2
a999 2
    if (request_global)
    	request_global->heartbeat++; 
d1002 1
d1284 1
a1284 1
                   __FUNCTION__. request_global, request_global->commandcode);
d1293 1
d1298 1
