d12 1
a12 1
#ident "$Id: sdio_util.c,v 1.1 2006/03/02 19:02:05 gbarnard Exp $"
d234 1
a234 1
	    	u32* bp32 = (u32*)(absolute&0xFFFFFFFE);
d236 1
a236 1
	    	int byte = (absolute&0x00000001);
d242 1
a242 1
	    	else if (byte==1)
d268 1
a268 1
	    	u32* bp32 = (u32*)(absolute&0xFFFFFFFE);
d270 1
a270 1
	    	int byte = (absolute&0x00000001);
d276 1
a276 1
	    	else if (byte==1)
d449 1
a449 2
    SER_DEBUG (DEBUG_SER_REG_MWRITE, "%s: dma %d blk %d auto12 %d rw %d m %d\n",
               __FUNCTION__, dma, blk_cnt, auto12, rw, multi);
d458 3
d481 2
a482 1
        msleep (10);
d486 1
d497 1
a497 1
	    	msleep (100); /* 1ms replace with sleep ... message queue block or schedule timeout */
d523 1
d625 4
a628 3
	/* Turn OFF power and clock */	       
    WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_CLOCKCTRL, 0x0);
    WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_PWRCTRLREG, 0);
d637 2
a638 1
    WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_CLOCKCTRL, pslot->m_wRegClockControl);
d642 1
a642 1
    msleep (100);   
d649 4
a652 4
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_ERRINTRSGEN,0xff);      
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_ERRINTRSEN,0xff);                    
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSGEN,0xC3);
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSEN,0xC3);
d655 1
a655 1
	msleep (100);
d674 1
a674 1
    printf("RCA=%04X\n",rca);
d1341 1
a1341 1
					msleep (20);
d1385 1
a1385 1
        while ((gp_sd_req->norint & NISR_DATA_TRAN_COMPLETE) == 0) 
d1468 1
a1468 1
	#if 1
d1488 1
d1549 1
a1549 1
        while ((gp_sd_req->norint & NISR_DATA_TRAN_COMPLETE) == 0) 
d1762 1
a1762 47
    struct sd_slot_base *pslot;
    unsigned int timeout, clock_control;

    if (!sdh) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null sdh\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    pslot = &sdh->m_sdslot[slot];

    if (!pslot->m_base) {
        SER_DEBUG (DEBUG_SER_ERR, "%s: null m_base\n",
                __FUNCTION__);
        return IOS_ERROR_ACCESS;
    }

    /*
     * We called SetClockRate() previously to init m_wRegClockControl.
     * We separate clock divisor calculation from ClockOn, so we can
     * call ClockOn without recalculating the divisor.
     */
    clock_control = pslot->m_wRegClockControl;

    SER_DEBUG (DEBUG_SER_SD_SETUP, "%s: clock_control 0x%x\n",
            __FUNCTION__, clock_control);

    timeout = 0;
    WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_CLOCKCTRL, clock_control);
    while (!(READ_HOST_U32((u32)pslot->m_base, SDHC_CLOCK_CONTROL) 
             & SDCLK_INTERNAL_STABLE)) {
        msleep(4);
        timeout += 5;
        if (timeout >= DEFAULT_TIMOUT_MS) {
            SER_DEBUG (DEBUG_SER_ERR, "%s: timeout during clock stabilization\n",
                    __FUNCTION__);
            return -1;
        }
    }
    WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_CLOCKCTRL, 
                   clock_control | SDCLK_ENABLE);

    READ_HOST_U32((u32)pslot->m_base, SDHC_CLOCK_CONTROL);

    SER_DEBUG (DEBUG_SER_SD_SETUP, "%s: wrote clock 0x%x timeout %d\n",
               __FUNCTION__, clock_control | CLOCK_ENABLE, timeout);

d1802 1
a1802 1
               __FUNCTION__, clock_control | CLOCK_ENABLE);
d1894 1
a1894 1
	if (pslot->m_cardtype==0)	// or SD_TYPE_UNKNOWN
d1896 1
d1901 2
a1902 1
    if (pslot->m_fCardPresent) {
d1904 3
a1906 1
    } else {
d2010 1
a2010 1
void show_command_setup(struct sd_slot_base *pslot, u32 command)
a2019 2
	/* 5 Set Transfer Mode */
	u16 transfer_mode = READ_HOST_U16((u32)pslot->m_base, HOSTREG_TRANSMODE);
d2043 1
a2043 1
			SER_DEBUG (DEBUG_SER_SD_CMD, "%s PIO Transfer\n"," >");
d2045 9
a2053 7
			SER_DEBUG (DEBUG_SER_SD_CMD, "%s SysAddr:0x%08X\n", " >", sysaddr);
			SER_DEBUG (DEBUG_SER_SD_CMD, "%s BlkSize:0x%04X Cnt:%d\n", " >",blk_size,blk_count);
			SER_DEBUG (DEBUG_SER_SD_CMD, "%s CmdArg :0x%08X\n", " >",cmd_arg);
			
			SER_DEBUG (DEBUG_SER_SD_CMD, "%s NINTSts:0x%04X Signal:0x%04X\n", " >",
				READ_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSEN),
				READ_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSGEN));
d2055 1
d2070 1
d2073 1
a2073 1
            __FUNCTION__, (u32)slot, (u32)cmd, (u32)cmd_arg, (u32)sys_addr, dma);
d2132 2
a2133 1
        command |= CMD_RESPONSE_R1B_R5B;   
d2171 1
d2184 2
a2185 2
		        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSEN,0xC3|NISR_BUFF_READ_RDY|NISR_DMA_INTR);
		        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSGEN,0xC3|NISR_BUFF_READ_RDY|NISR_DMA_INTR);
d2201 2
a2202 2
		        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSEN,0xC3|NISR_BUFF_WRITE_RDY|NISR_DMA_INTR);
		        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSGEN,0xC3|NISR_BUFF_WRITE_RDY|NISR_DMA_INTR);
d2225 2
d2239 2
d2251 8
a2258 1
    if (set_clock_on(sdh, slot)<0) return -1;
d2277 1
a2277 1
     		sysaddr = sys_addr | 0x50000000;
d2282 13
a2294 7
     
     	/* can we issue a data command? */
     	if ( READ_HOST_U32((u32)pslot->m_base,HOSTREG_PSTATE) & PS_CMD_INHIBIT_DATA)
     	{
     		SER_DEBUG (DEBUG_SER_ERR, "%s: DAT BUSY!\n", __FUNCTION__);
     		msleep(100);
     	}
d2297 7
a2305 7

	/* 2 Set Block Size */
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_BLOCKSZ, blk_size);
	
	/* 3 Set Block Count */
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_BLOCKCNT, blk_count);

d2314 1
a2314 1
	show_command_setup(pslot,command);
d2504 4
d2509 30
a2538 24

    timeout = 0;
    //printf("\n(0x%X %d %d)", gp_sd_req, gp_sd_req->status, gp_sd_req->cmd_wait);
    do 
    {
    	//printf("{%x}",gp_sd_req->status);
        msleep(10);
        timeout += 1;
        if (timeout++ >= DEFAULT_TIMOUT_MS) 
        {
            //SER_DEBUG (DEBUG_SER_ERR, "%s: timeout during command execution\n",
            //        __FUNCTION__);
            printf("|TimeOut|");
            if (gp_sd_req->status == SD_STATUS_SUCCESS)
            {
            	gp_sd_req->status = SD_STATUS_CMD_TIMEOUT; // c00000022
            }
            break;
        }
    } while (gp_sd_req->cmd_wait == 0);
	
    //printf("{0x%x 0x%x}", gp_sd_req->status, gp_sd_req->cmd_wait);
	
	// gp_sd_req->status = SD_STATUS_SUCCESS;
a2539 5
    if (gp_sd_req->status != SD_STATUS_SUCCESS)
        SER_DEBUG (DEBUG_SER_ERR, "\n %s(%d) Failed:0x%x\n",
                __FUNCTION__, 
                (command>>8),gp_sd_req->status);

d2544 1
a2544 1
        msleep (10);
d2548 1
a2548 1
            msleep (10);
d2565 27
a2591 7
    SER_DEBUG (DEBUG_SER_REG_MREAD, "   %s:response %04X %04X %s\n.......\n",__FUNCTION__, 
    	gp_sd_req->response[1],
    	gp_sd_req->response[0],
    	status[((gp_sd_req->response[0] & 0x1e00) >> 9)]
    	/*,(gp_sd_req->response[0] & 0x0020)?"ACMD"," "*/
    	);

d2594 5
a2598 5
    	resp[0] = gp_sd_req->response[0];
	   	resp[1] = gp_sd_req->response[1];
	   	resp[2] = gp_sd_req->response[2];
	   	resp[3] = gp_sd_req->response[3];
        //memcpy(resp, &gp_sd_req->response[0], 8 * sizeof(unsigned short));
