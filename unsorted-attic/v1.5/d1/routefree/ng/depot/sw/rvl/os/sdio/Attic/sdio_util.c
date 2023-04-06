d12 1
a12 1
#ident "$Id: sdio_util.c,v 1.4 2006/03/17 01:49:31 gbarnard Exp $"
d488 2
a489 2
    	//status = do_command(sdh, dev, 0, SD_COMMAND, NoResponse, 0,    0, 0, 0, 0, 0, &regs[0]);
    	//msleep (10000);
d492 5
a496 1
    	if (status!=0) return false;
d505 1
a505 1
	    	msleep (10000); /* 1ms replace with sleep ... message queue block or schedule timeout */
d644 1
a644 1
    msleep(10000);
d651 1
a651 1
    msleep (10000);
d664 1
a664 1
	msleep (10000);
d666 1
d668 3
a670 2
	//status = do_command(sdh, slot, 0, SD_COMMAND, NoResponse, 0,    0, 0, 0, 0, 0, &regs[0]);
	msleep (10000);            
d790 1
a790 1
    int status = 0, timeout = MAX_TIMEOUT;
d811 3
a813 1
    msleep (100);
d815 15
a829 9
    while (timeout-- >= 0) {
        status = do_command(sdh, slot, CMD_IO_RW_DIRECT, SD_READ_REG, 
                        ResponseR5, 1, arg, 0, 0, 0, 0, &response[0]);
        if (status == 0) break;
        SER_DEBUG (DEBUG_SER_ERR, 
                   "%s: command timeout reg 0x%x status 0x%x %d\n",
                   __FUNCTION__, reg, status, timeout);
        msleep (10);
    }
d831 2
a832 2
    //SER_DEBUG (DEBUG_SER_ERR, "%s() slot %d reg 0x%x width %d data=0x%X\n",
    //        __FUNCTION__, (u32)slot, (u32)reg, (u32)width, response[0] & 0xff);
d848 1
a848 1
    int status = 0, timeout = MAX_TIMEOUT;
d868 17
a884 11

    msleep (10);

    while (timeout-- >= 0) {
        status = do_command(sdh, slot, CMD_IO_RW_DIRECT, SD_WRITE_REG, 
                            ResponseR5, 1, arg, 0, 0, 0, 0, &response[0]);
        if (status == 0) break;
        SER_DEBUG (DEBUG_SER_ERR, 
                   "%s: command timeout reg 0x%x status 0x%x data 0x%x %d\n",
                   __FUNCTION__, reg, status, data, timeout);
        msleep (10);
d886 1
a886 1

d911 1
a911 1
    int status = 0, length, timeout = MAX_TIMEOUT;
d939 1
a939 1
{
d941 1
a941 1
    *dp = 0xeeeeeeee;
d947 16
a962 16
/*
 *    31  30  28  27    26 25               9 8              0
 * +-----+------+-----+---+------------------+----------------+
 * | R/W | Func | Blk |Op | Register Address |  Data Length   |
 * +-----+------+-----+---+------------------+----------------+
 *    1     3      1    1          17                9   
 *
 * pslot: slot base address.
 * rw:    read/write flag
 * func:  function address on card.   0 is common function.
 * blk:   block mode
 * op:    op-code (0 - r/w fixed address, 1 - r/w incrementing address)
 * reg:   address of eight-bit register.
 */
   //	blk_size = 4;
   	//blk_cnt = 1;
d965 3
a967 10
    while (timeout-- >= 0) {
        status = do_command(sdh, slot, CMD_IO_RW_EXTENDED, SD_READ, 
                            ResponseR5, 1, arg, sysaddr, blk_cnt, 
                            blk_size, dma, &response[0]);
        if (status == 0) break;
        SER_DEBUG (DEBUG_SER_ERR, 
                   "%s: command timeout reg 0x%x status 0x%x %d\n",
                   __FUNCTION__, reg, status, timeout);
        msleep (10);
    }
d969 16
d987 2
a988 2
    //SER_DEBUG (DEBUG_SER_REG_MREAD, 
    printf("   %s: reg %04X data 0x%08x\n",
d2254 2
a2255 2
	        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSEN,0xC3);
	        WRITE_HOST_U16((u32)pslot->m_base, HOSTREG_NORINTRSGEN,0xC3);
d2261 1
a2261 1
		        transfer_mode = rw_transfer_mode (dma, 0, 0, 0, 1);
d2353 2
a2354 43
	#if 0
	{
		#if 0
		/* Big Endian, 32bit workaround-test */
		cmd32 = 0x44332211;
		WRITE_HOST_U32((u32)pslot->m_base, 0,cmd32); 
		printf("[cmd32:0x%08X 0x%04X %04X 0x%02X %02X %02X %02X]\n",
			READ_HOST_U32((u32)pslot->m_base, 0),
			READ_HOST_U16((u32)pslot->m_base, 2),
			READ_HOST_U16((u32)pslot->m_base, 0),
			READ_HOST_U8((u32)pslot->m_base, 3),
			READ_HOST_U8((u32)pslot->m_base, 2),
			READ_HOST_U8((u32)pslot->m_base, 1),
			READ_HOST_U8((u32)pslot->m_base, 0)
		);
		
		WRITE_HOST_U16((u32)pslot->m_base, 0,0x2211);
		WRITE_HOST_U16((u32)pslot->m_base, 2,0x4433);
		
		WRITE_HOST_U32((u32)pslot->m_base, 0,cmd32); 
		printf("[cmd32:0x%08X]\n",
			READ_HOST_U32((u32)pslot->m_base, 0));


		WRITE_HOST_U8((u32)pslot->m_base, 0,0x11);
		WRITE_HOST_U8((u32)pslot->m_base, 1,0x22);
		WRITE_HOST_U8((u32)pslot->m_base, 3,0x33);
		WRITE_HOST_U8((u32)pslot->m_base, 4,0x44);
		

		#endif
		
		WRITE_HOST_U32((u32)pslot->m_base, 0,cmd32); 
		printf("[cmd32:0x%08X 0x%04X]\n",
			READ_HOST_U32((u32)pslot->m_base, 0),transfer_mode
			);


			msleep(1000);
	}
	#else
		msleep(100);
	#endif
a2356 15
	#if 1
	{
		//u32 d32 = READ_HOST_U32((u32)pslot->m_base,HOSTREG_PSTATE);
		//printf("cmd=%08X\n",cmd32);
		//DumpSlotRegs(pslot);
		//printf("{%x}",gp_sd_req->status);
		WRITE_HOST_U32((u32)pslot->m_base, HOSTREG_TRANSMODE, cmd32);
		//printf("{%x}",gp_sd_req->status);
		//printf("<%08x>\n",READ_HOST_U32((u32)pslot->m_base, HOSTREG_TRANSMODE) );
	}
	#endif
    
    
    //msleep(100);

d2376 1
a2376 1
                msleep (2000);
d2439 1
a2439 1
                msleep (2000);
d2493 2
a2494 2
	        msleep(10);
	        timeout += 1;
d2517 1
a2517 1
        msleep (100);
d2521 1
a2521 1
            msleep (100);
