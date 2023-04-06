d12 1
a12 1
#ident "$Id: sdio_util.c,v 1.2 2006/03/15 01:10:15 gbarnard Exp $"
a1323 1
	 dma = 1;
d1384 2
a1385 1
        while ((READ_HOST_U16((u32)pslot->m_base, HOSTREG_NORMINTRSTAT) & NISR_DATA_TRAN_COMPLETE) == 0) 
d1397 3
a1399 6
	{
   printf("   %s: sysaddr now 0x%08x\n",
            __FUNCTION__, READ_HOST_U32((u32)pslot->m_base, HOSTREG_SYSADDRL));
	}        
		SER_DEBUG (DEBUG_SER_SD_CMD, "%s: DONE\n",
		       __FUNCTION__);      		
d1427 1
a1427 1
    SER_DEBUG (DEBUG_SER_ERR, 
d1448 1
a1448 1
    SER_DEBUG (DEBUG_SER_ERR, "%s: length 0x%x\n",
a1484 1
	 dma = 1;
d1545 2
a1546 1
        while ((READ_HOST_U16((u32)pslot->m_base, HOSTREG_NORMINTRSTAT) & NISR_DATA_TRAN_COMPLETE) == 0) 
d2168 1
a2168 3
	    		//cmd12=0;
    			//SER_DEBUG (DEBUG_SER_SD_CMD, 
    			printf("%s ---CMD READ--- %04X %04X\n",__FUNCTION__,
d2503 2
a2504 1
out: 
d2506 1
a2506 1
	if ((7 == (command>>8)) && ( 0 == cmd_arg))
d2519 2
a2520 2
	            SER_DEBUG (DEBUG_SER_ERR, "%s: timeout during command execution\n",
	                    __FUNCTION__);
d2530 3
a2532 4
	    if (gp_sd_req->status != SD_STATUS_SUCCESS)
	        SER_DEBUG (DEBUG_SER_ERR, "\n %s(%d) Failed:0x%x\n",
	                __FUNCTION__, 
	                (command>>8),gp_sd_req->status);
