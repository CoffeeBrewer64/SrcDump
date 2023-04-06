d12 1
a12 1
#ident "$Id: sdio_util.c,v 1.1 2006/01/30 23:41:45 gbarnard Exp $"
d46 5
a50 5
	#include "../../include/sd.h"
	#include "../../include/sd_card.h"
	#include "../../include/sd_host.h"
	#include "../../include/sd_ioctl.h"
	#include "../../include/sd_debug.h"
d68 1
a68 2
extern sd_request *request_global;
extern sd_request sd_req;
d145 28
a172 2
    	u8* bp = (u8*)(base + reg);
    	ret = *bp;
d194 1
a194 1
	    	u32* bp32 = (u32*)(absolute&0xFFFFFFFE);
d198 1
a198 1
	    	if (byte==3)
d202 1
a202 1
	    	else if (byte==2)
d206 1
a206 1
	    	else if (byte==1)
d210 1
a210 1
	    	else if (byte==0)
d214 1
a214 1
	    	//printf(", dat=%08x\n",data);
d216 1
d232 19
a250 2
 		u16* bp = (u16*)(base + reg);
    	ret = *bp;
d270 3
a272 2
	    	//printf("abs=%08x, bp32=%08x, d32=%08x",absolute,bp32,data);
	    	if ((absolute&0x00000001)==1)
d276 1
a276 1
	    	else
d469 1
a469 1
    unsigned short regs[8];
d498 1
a498 1
    	while (((regs[1]&(unsigned int)0x8000)==0)&&(i>0));
d507 1
a507 1
   	    ocr = (regs[0]) | (regs[1] << 16);
d535 1
a535 1
    while (((regs[1]&(unsigned int)0x8000)==0)&&(i>0));
d547 1
a547 1
	    ocr = (regs[0]) | (regs[1] << 16);
d599 1
a599 1
    unsigned short regs[8];
a626 1
	printf("(1)");
a627 1
    printf("(2)");
d630 1
a630 1
    pslot->m_wRegClockControl = 0x8001;
d642 2
a643 2
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_ERRINTRSGEN,0x1f);      
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_ERRINTRSEN,0x1f);                    
d649 1
d662 1
a662 1
        SER_DEBUG (DEBUG_SER_ERR, "%s: Bad do_command 0x%x\n", 
d666 2
a667 1
    rca = regs[1];
d671 1
a671 1
        SER_DEBUG (DEBUG_SER_ERR, "%s: Bad do_command 0x%x\n", 
d771 1
a771 1
    unsigned short response[8];
d821 1
a821 1
    unsigned short response[8];
d881 1
a881 1
    unsigned short response[8];
d967 1
a967 1
    unsigned short response[8];
d1176 1
a1176 1
		sd_req.callback_on_irq,
d1198 1
a1198 1
	if (sd_req.norint&NISR_DATA_TRAN_COMPLETE)
d1200 1
a1200 1
		sd_req.callback_on_irq = 0;
d1206 1
a1206 1
	if (sd_req.norint&NISR_BUFF_READ_RDY)
d1220 1
a1220 1
	     sd_req.callback_on_irq=0; //|=NISR_DATA_TRAN_COMPLETE;
d1224 1
a1224 1
	if (sd_req.norint&NISR_BUFF_WRITE_RDY)
d1243 1
a1243 1
	   sd_req.callback_on_irq=0; //|=NISR_DATA_TRAN_COMPLETE;
d1246 1
a1246 1
	sd_req.norint = 0;
d1271 1
a1271 1
    unsigned short response[8];
d1297 2
a1298 2
	sd_req.callback = (void*)callback; //myCallback;
    sd_req.callback_on_irq = NISR_BUFF_READ_RDY;
d1328 1
a1328 1
			while (sd_req.req_size)	
d1332 1
a1332 1
				while (((sd_req.norint&NISR_BUFF_READ_RDY)==0)&&(timeout))
d1344 1
a1344 1
				if (sd_req.norint&NISR_BUFF_READ_RDY)
d1347 1
a1347 1
					sd_req.norint &=~NISR_BUFF_READ_RDY;
d1370 1
a1370 1
				     sd_req.req_size--;
d1378 1
a1378 1
        while ((sd_req.norint & NISR_DATA_TRAN_COMPLETE) == 0) 
d1385 2
a1386 2
                if (sd_req.status == SD_STATUS_SUCCESS)
                    sd_req.status = SD_STATUS_DATA_TIMEOUT;
d1398 1
a1398 1
	 sd_req.callback_on_irq=0; //|=NISR_DATA_TRAN_COMPLETE;
d1421 1
a1421 1
    unsigned short response[8];
d1447 2
a1448 2
	sd_req.callback = (void*)callback; //myCallback;
    sd_req.callback_on_irq = NISR_BUFF_WRITE_RDY; /*|NISR_BUFF_READ_RDY|NISR_DATA_TRAN_COMPLETE;*/
d1492 1
a1492 1
			while (sd_req.req_size)	
d1496 1
a1496 1
				while (((sd_req.norint&NISR_BUFF_WRITE_RDY)==0)&&(timeout))
d1508 1
a1508 1
				if (sd_req.norint&NISR_BUFF_WRITE_RDY)
d1511 1
a1511 1
					sd_req.norint &=~NISR_BUFF_WRITE_RDY;
d1533 1
a1533 1
				     sd_req.req_size--;
d1541 1
a1541 1
        while ((sd_req.norint & NISR_DATA_TRAN_COMPLETE) == 0) 
d1548 2
a1549 2
                if (sd_req.status == SD_STATUS_SUCCESS)
                    sd_req.status = SD_STATUS_DATA_TIMEOUT;
d1557 1
a1557 1
	sd_req.callback_on_irq=0; //|=NISR_DATA_TRAN_COMPLETE;
d2097 1
a2097 1
            int blk_count, int blk_size, int dma, unsigned short *resp)
d2100 3
a2102 2
    unsigned short command, transfer_mode = 0;
    unsigned int timeout, multi_data_count, p_state = 0;
d2121 10
a2130 10
    sd_req.command = cmd;
    sd_req.cmd_type = cmd_type;
    sd_req.resp_type = resp_type;
    sd_req.cmd_arg = cmd_arg;
    sd_req.norint = 0;
    sd_req.status = 0;
    sd_req.cmd_wait = 0;
    sd_req.callback = 0; //myCallback;
    sd_req.heartbeat = 0;
    sd_req.req_size = blk_count;
a2131 2
    request_global = &sd_req;

d2171 3
a2173 2
    SER_DEBUG (DEBUG_SER_CMD, "%s: command 0x%x\n",
               __FUNCTION__, command);
d2176 1
a2176 1
     * Wait until command_inhibit is not set.
d2178 2
a2179 3
    timeout = 0;
	while((p_state = READ_HOST_U32((u32)pslot->m_base,HOSTREG_PSTATE)) 
            & PS_CMD_INHIBIT_CMD);
d2181 6
a2186 17
		if(++timeout < DEFAULT_TIMOUT_MS) 
		{
			msleep(1);
            //WRITE_HOST_U8((u32)pslot->m_base, HOSTREG_SOFTRESET, 0x2);
		} 
		else 
		{
            SER_DEBUG (DEBUG_SER_ERR, "%s: timeout out on inhibit p_state 0x%x\n",
                    __FUNCTION__, p_state);
			return 1;
        }
	} 

    SER_DEBUG (DEBUG_SER_REG_MWRITE, "%s: sys_addr 0x%08x bus 0x%08x\n",
               __FUNCTION__, sys_addr, (u32)virt_to_bus((void *)sys_addr));
               

d2216 1
a2216 1
		        if (dma==0) sd_req.callback_on_irq = NISR_BUFF_READ_RDY;	    			    	
d2233 1
a2233 1
		       if (dma==0) sd_req.callback_on_irq = NISR_BUFF_WRITE_RDY;	    			    	
d2323 2
a2324 1
	WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_TRANSMODE, transfer_mode);
d2338 39
a2376 1
		printf("=>\n");
d2378 1
a2378 1
		msleep(10000);
d2385 6
a2390 2
		WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_COMMAND, command);
		//printf("<%x>",d32);
d2420 1
a2420 1
                    sd_req.status = SD_STATUS_DATA_TIMEOUT;
d2463 2
a2464 2
    if ((cmd == CMD_IO_RW_EXTENDED) && ((cmd_arg & CMD_ARG_WRITE) == 0) 
        && (!dma)) {
d2483 1
a2483 1
                    sd_req.status = SD_STATUS_DATA_TIMEOUT;
d2520 1
d2523 1
d2525 1
a2525 1
        timeout += 5;
d2528 7
a2534 4
            SER_DEBUG (DEBUG_SER_ERR, "%s: timeout during command execution\n",
                    __FUNCTION__);
            if (sd_req.status == SD_STATUS_SUCCESS)
                sd_req.status = SD_STATUS_CMD_TIMEOUT;
d2537 10
a2546 6
    } while (sd_req.cmd_wait == 0);

    if (sd_req.status != SD_STATUS_SUCCESS)
        SER_DEBUG (DEBUG_SER_ERR, "%s: cmd_status 0x%x %s\n",
                __FUNCTION__, sd_req.status, 
                sd_status_decode(sd_req.status));
d2554 1
a2554 1
        while ((sd_req.norint & NISR_DATA_TRAN_COMPLETE) == 0) 
d2562 2
a2563 2
                if (sd_req.status == SD_STATUS_SUCCESS)
                    sd_req.status = SD_STATUS_DATA_TIMEOUT;
d2570 1
a2570 1
                   sd_req.response[0]);
d2574 4
a2577 4
    	sd_req.response[1],
    	sd_req.response[0],
    	status[((sd_req.response[0] & 0x1e00) >> 9)]
    	/*,(sd_req.response[0] & 0x0020)?"ACMD"," "*/
d2580 7
a2586 2
    if (resp) {
        memcpy(resp, &sd_req.response[0], 8 * sizeof(unsigned short));
d2590 1
a2590 1
    return sd_req.status;
