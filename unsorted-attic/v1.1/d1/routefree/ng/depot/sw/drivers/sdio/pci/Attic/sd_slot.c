d12 1
a12 1
#ident "$Id: sd_slot.c,v 1.70 2005/11/17 16:51:34 jlivesey Exp jlivesey $"
d141 1
d191 1
d193 19
d221 1
a221 1
    } while (READ_HOST_U8((u32)slot->m_base, HOSTREG_SOFTRESET));
d227 1
d548 1
a548 1

d560 6
a565 1
         * Enable all interrupt signals. During execution, we will enable
d567 14
d582 10
a591 4
        WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSGEN, 
                       0xFFFF);
        WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORINTRSEN, 
                       NISR_CARD_INSERT | NISR_CARD_REMOVAL);
d667 5
a707 1
extern struct _sd_request *request_global;
d725 1
d744 4
d749 1
a749 1
    PCI_DEBUG (DEBUG_PCI_IRQ, "%s: wIntStatus 0x%x\n",
d751 3
d755 2
a756 1
    if (wIntStatus != 0) {
d760 2
a761 1
        if ( wIntStatus & NISR_ERR_INTR ) {
d763 2
a764 1
            if (request_global) {
d770 35
a804 105

        /*
         * Command Complete handling.
         */
        if ( wIntStatus & NISR_CMD_COMPLETE ) {
            request_global->norint |= NISR_CMD_COMPLETE;
            command = READ_HOST_U16((u32)slot->m_base, HOSTREG_COMMAND);
            PCI_DEBUG (DEBUG_PCI_IRQ, "%s: command complete 0x%x\n",
                    __FUNCTION__, command);
            slot->m_fCommandCompleteOccurred = 1;
            WRITE_HOST_U16((u32)slot->m_base, 
                           HOSTREG_NORMINTRSTAT, NISR_CMD_COMPLETE);

        }

        /*
         * DMA data transfer complete handling.
         */
        if ( wIntStatus & NISR_DATA_TRAN_COMPLETE ) {
            request_global->norint |= NISR_DATA_TRAN_COMPLETE;
        }

#if 0
        /*
        * Sometimes at the lowest clock rate, the
        * Read/WriteBufferReady interrupt actually occurs before the
        * CommandComplete interrupt.  This confuses our debug
        * validation code and could potentially cause problems. This
        * is why we will verify that the CommandComplete occurred
        * before processing any data transfer interrupts.
        */

        if (slot->m_fCommandCompleteOccurred) {
            if (wIntStatus & NORMAL_INT_STATUS_DMA) {
                WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORMINTRSTAT,
                               NISR_DMA_INTR);
                SDHostslot_HandleDMA(slot);
            }

            /*
             * Buffer Read Ready handling
             */
            if (wIntStatus & NISR_BUFF_READ_RDY ) {
                /*
                 * Clear status
                 */
                WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORMINTRSTAT, 
                               NISR_BUFF_READ_RDY);
                SDHostslot_Handlereadready(slot); 
                /*
                 * do not break here. Continue to check TransferComplete.
                 */
            }

            /* Buffer Write Ready handling */
            if (wIntStatus & NISR_BUFF_WRITE_RDY ) {
                /*
                 * Clear status
                 */
                WRITE_HOST_U16((u32)slot->m_base,HOSTREG_NORMINTRSTAT, 
                               NISR_BUFF_WRITE_RDY);
                SDHostslot_Handlewriteready(slot);
                /*
                 * do not break here. Continue to check TransferComplete.
                 */
            }
        } else {
            /*
             * We received data transfer interrupt before command
             * complete interrupt. Wait for the command complete before
             * processing the data interrupt.
             */
        }

        /*
         * Transfer Complete handling
         */
        if ( wIntStatus & NISR_DATA_TRAN_COMPLETE ) {
            /*
             * Clear status
             */
            WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORMINTRSTAT, 
                           NISR_DATA_TRAN_COMPLETE | NISR_DMA_INTR);
            SDHostslot_Handletransferdone(slot);
        }

        /*
         * SDIO Interrupt Handling
         */
        if ( wIntStatus & NISR_CARD_INSERT ) {
            /*
             * Because SDIO Interrupt is level triggered, we are not
             * able to clear the status. The status should be cleared
             * by the card we just disable the interrupt from Interrupt
             * Signal Register and Interrupt Status Enable register,
             * and indicate that the card is interrupting
             */
            SDHostslot_Enableinterrupt(slot, DISABLE_INTERRUPT);
            /*
             * We have to put way to inform bus that card is found and
             * ready to initilize
             */
            SDHostslot_reportslotstatechange(slot, DeviceInterrupting);
        }
#endif
d809 2
a810 3
        if (wIntStatus & (NISR_CARD_INSERT | NISR_CARD_REMOVAL)) {
            WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORMINTRSTAT, 
                           NISR_CARD_INSERT | NISR_CARD_REMOVAL);
d813 1
a813 1
    }
d815 3
d856 2
a857 1
    if (slot->m_fCheckSlot) {
d886 11
d988 1
d1162 1
d1194 1
a1194 1
        struct sd_request * pRequest; /* = GetAndLockCurrentRequest(); */
d1196 1
a1196 1
        if (pRequest != NULL) {
d1198 1
a1198 1
                   __FUNCTION__. pRequest, pRequest->commandcode);
d1200 1
a1200 1
             * DumpRequest(pRequest, SDHC_SEND_ZONE || SDHC_RECEIVE_ZONE); 
d1202 1
a1202 1
            SDHostslot_IndicateBusRequestComplete(slot, pRequest, SD_STATUS_DEVICE_REMOVED);
a1236 3
    PCI_DEBUG (DEBUG_PCI_IRQ, "%s: slot 0x%x\n",
            __FUNCTION__, (u32)slot);

d1247 4
a1309 5
        /* Perform basic error recovery */
        uErrIntSignal = READ_HOST_U16((u32)slot->m_base, 
                                      HOSTREG_ERRINTRSGEN);

        WRITE_HOST_U16((u32)slot->m_base, HOSTREG_ERRINTRSGEN, 0);
d1317 1
