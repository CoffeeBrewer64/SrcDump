d12 1
a12 1
#ident "$Id: sdio_serial.c,v 1.2 2006/03/15 01:10:15 gbarnard Exp $"
d426 1
d428 2
a429 1
    printf("IRQ: Thread Started Id:%d mq:%d\n",id,sdiQid);	
d439 1
a439 3
	
    
    sdusleep(30000,slpQid,"+"); 
d442 1
a448 1
	
a450 1

a452 8
		//WRITE_HOST_U16((u32)sdh_global->m_sdslot[0].m_base, HOSTREG_NORMINTRSTAT, 0x1FF);
		//WRITE_HOST_U16((u32)sdh_global->m_sdslot[0].m_base, HOSTREG_ERRINTRSTAT, 0x1FF);            
		//WRITE_HOST_U16((u32)sdh_global->m_sdslot[1].m_base, HOSTREG_NORMINTRSTAT, 0x1FF);
		//WRITE_HOST_U16((u32)sdh_global->m_sdslot[1].m_base, HOSTREG_ERRINTRSTAT, 0x1FF);            	
   		//IOS_ClearAndEnableSDIntr(0);
    	//IOS_ClearAndEnableSDIntr(1);				
		//addr = (u32*)(ACR_PROT_REGS_BASE + 0x03C); printf("IOP_Ena");printf("[%08X]:%08X\n",addr,*addr );
		//addr = (u32*)(ACR_PROT_REGS_BASE + 0x038); printf("IOP_Sta");printf("[%08X]:%08X\n",addr,*addr );
d454 1
d566 1
a566 1
	printf("--- sdioIrqThread Starting ---\n");
