d12 1
a12 1
#ident "$Id: sd_slot.c,v 1.1 2006/03/02 19:02:05 gbarnard Exp $"
d87 1
a87 1
			sdusleep((u32)100,sdQid,"+");
a262 18
    if (mask==SR_CMD_LINE)
    {
    	PCI_DEBUG (DEBUG_PCI_INIT, "%s: CMD Reset PS:0x%X\n", __FUNCTION__,prev_state);
    }
    else if (mask==SR_DAT_LINE)
    {
   		PCI_DEBUG (DEBUG_PCI_INIT, "%s: DAT Reset PS:0x%X\n", __FUNCTION__,prev_state);
    }
    else if (mask==SR_RESET_ALL)
    {
    	PCI_DEBUG (DEBUG_PCI_INIT, "%s: ALL Reset PS:0x%X\n", __FUNCTION__,prev_state);
    }
    else
    {
    	PCI_DEBUG (DEBUG_PCI_ERR, "%s: ERROR Reset Mask:0x%X\n", __FUNCTION__,mask);
    	return 0;
    }
    
d265 1
a265 1
	//WRITE_HOST_U32((u32)slot->m_base, 0x2C, 0x07000000);
d547 1
a547 1
    if (SDHostslot_SoftwareReset(slot, SR_RESET_ALL)) 
d568 8
d577 8
a584 2
    //DumpSlotRegs(slot);
    
d867 1
a867 1
            printf("[Command %02d Done]", command);
d909 1
a909 1
            ///printf("[Data Ready]");
d1166 1
d1168 3
a1170 2
    while (!(READ_HOST_U32((u32)slot->m_base, SDHC_CLOCK_CONTROL) 
             & (SDCLK_INTERNAL_STABLE & SDCLK_INTERNAL_STABLE))) {
d1179 1
d1182 6
a1187 2
                HOSTREG_CLOCKCTRL, slot->m_wRegClockControl | CLOCK_ENABLE);

