d12 1
a12 1
#ident "$Id: sdio_util.c,v 1.3 2006/03/16 19:31:58 gbarnard Exp $"
d111 1
d113 1
a113 1
	"idle",
d116 6
a121 6
	"stby",
	"tran",
	"data",
	"rcv",
	"prg",
	"dis"
d123 1
d469 1
a469 1
unsigned int
d478 1
d485 1
a485 1
        msleep (1000);
d488 3
a490 2
    	status = do_command(sdh, dev, 0, SD_COMMAND, NoResponse, 0,    0, 0, 0, 0, 0, &regs[0]);
    	msleep (1000);
d501 1
a501 1
	    	msleep (1000); /* 1ms replace with sleep ... message queue block or schedule timeout */
d507 1
d528 2
a529 1
	    printf("Setting Card Type\n");
d577 2
a578 1
    if (write_slot_register(sdh, dev, reg, 1, (7 << 1)) != 0) {
d583 1
a583 1

d631 1
a631 1
	SER_DEBUG (DEBUG_SER_SD_CMD, "------- %s() ------- \n", __FUNCTION__);
d634 2
a635 2
    //WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_CLOCKCTRL, 0x0);
    //WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_PWRCTRLREG, 0);
d640 2
a641 1
    msleep(100);
d645 1
a645 2
    if (set_clock_on(sdh, slot)<0) return -1;
    //WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_CLOCKCTRL, pslot->m_wRegClockControl);
d647 1
a647 3
    
    /* wait a bit, could be replaced with clock stable ... */
    //msleep (100);   
d660 1
a660 1
	//msleep (100);
d662 1
a662 1
	
d664 1
a664 1
	            
a2073 3
    SER_DEBUG (DEBUG_SER_REG_MREAD, "%s: slot 0x%x cmd %d arg:0x%08x maddr:0x%08x dma=%d\n",
	            __FUNCTION__, (u32)slot, (u32)cmd, (u32)cmd_arg, (u32)sys_addr, dma);

d2087 3
d2232 1
a2232 1
		        transfer_mode = rw_transfer_mode (dma, 0, 0, 0, 0);
d2289 1
a2289 1
	    	printf("<soft reset pstate: 0x%08X ~ ",p_state);
d2385 1
a2385 1
     * If this is a multi-write, we should start writing the data
d2508 1
a2508 1
out: // ======= Command Done =======
d2535 1
a2535 1
	    if ((gp_sd_req->status != SD_STATUS_SUCCESS)&&(command!=5))
d2540 1
a2540 1
	/* For CMD53 with dma, check if dma is done */
d2568 2
a2569 8
    	printf("   pstate: 0x%08X ~ ",p_state);		
    	//SER_DEBUG (DEBUG_SER_REG_MREAD, 
    	printf("   respon: 0x%08X %s\n", 
    		gp_sd_req->response[0],
    		status[((gp_sd_req->response[0] & 0x1e00) >> 9)]
	    	/*,(gp_sd_req->response[0] & 0x0020)?"ACMD"," "*/
	    	);
        msleep (10);
