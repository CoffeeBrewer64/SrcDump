d12 1
a12 1
#ident "$Id: sdio_serial.c,v 1.4 2006/03/17 00:47:40 gbarnard Exp $"
d215 1
a216 1
struct sd_host *sdh_global = &g_sdh;
d300 2
a301 2
void 
sdio_init_irq(void)
d305 1
a305 2
    //dbgStartTimer();
    /* === Create a message queue and register for PCI0 events === */
d308 2
a309 2
        printf("Unable to create PCI message queue: %d\n", sdiQid);
        goto done;
d311 1
a311 1
    printf("--- SD IRQ QID:%d ---\n",sdiQid);
d313 2
a314 8
    printf("--- Register SD0 Event Handler ---\n");
    #ifdef VERSA
	    if ((rv = IOS_HandleEvent(IOS_EVENT_PCI0, sdiQid, 0)) != IOS_ERROR_OK) 
	    {
	        printf("Unable to register PCI0 event handler: %d\n", rv);
	        goto done;
	    }
	#else
d318 5
a322 4
	        goto done;
	    }	  	
	    /*
		printf("---> Register SD1 Event Handler to same queue! <---\n");
d326 3
a328 4
	        goto done;
	    }	
	    */    
	#endif
d330 1
a330 13
	#ifdef VERSA
		/* Initialize actual PCI card in slot 0*/
    	IOS_EnablePCIIntr(0); /* Enable PCI0 interrupts */
    	printf("---> Ready for PCI0 event <---\n");
    #else
	   	//printf("--- Enable SD0 event ---\n");    
    	
    	///IOS_ClearAndEnableSDIntr(1);
    #endif


done:
    return;
d336 1
a336 1
initSDIO(u32 base)
d339 1
a339 1
    
d342 9
a350 10
    u32 pri = 100; /* max prioroty for irq */ //IOS_GetThreadPriority(0);
        
    #ifdef VERSA
    	u32 pci_cfg_addr;
		pci_cfg_addr = IOS_pci_find(ARASAN_PCI_VENDORID, ARASAN_PCI_DEVICEID);
		if ( pci_cfg_addr == 0 ) {
			printf("Error finding PCI Configuration Address\n");
	        rv = IOS_ERROR_NOEXISTS;
	        goto done;
		}
d352 21
a372 1
	//printf("PCI_SDIO Configuration address = 0x%08x\n", pci_cfg_addr);
d374 1
a374 10
	/* a) Read number of slots on host controller */
	sdh_global->m_slotcount = 1; //((io(pci_cfg_addr+0x40)& 0x70)>>4)+1;
	//printf("Slot Count = %d\n",sdh_global->m_slotcount);
	/*
	if (sdh_global->m_slotcount!=2)
	{
		printf("Error reading slot register!\n");
		
	}
	*/
d376 1
a376 1
	/* b) Get Base Address for each slot */
d379 8
a386 19
		#if 0
		int k;		// debug
		u32*	dp32;	// debug
		u16*	dp16;
		u8*		dp8;
		#endif
		
		#ifdef VERSA
			sdh_global->m_sdslot[i].m_base = (void*)IOS_pci_base_address(pci_cfg_addr,i);
		#else
			if (i==0)
			{
				sdh_global->m_sdslot[i].m_base = (void*)base;
			}
			else
			{
				sdh_global->m_sdslot[i].m_base = (void*)base+0x100;			
			}
		#endif
d390 3
a392 3
		SER_DEBUG (DEBUG_SER_INIT, "%s:Base Address(%d) = %x\n",
				__FUNCTION__, i,
				(u32)sdh_global->m_sdslot[i].m_base);
d395 1
a395 1
	/* c) === Add irq handling to process host interrupts ===*/
d397 1
a397 1
	sdio_init_irq();
a399 1
	gp_sd_req = (struct _sd_request*)malloc (sizeof(struct _sd_request));
a407 1
    	
d418 1
a418 1
	IOS_ClearAndEnableSDIntr(0);
d420 1
a420 1
	#if 0
d423 1
a423 1
		printf("--- IRQ0 slot 0x%04X\n",(u32)dwIntStatus);
d496 1
a496 1
	 	/* SD Base-Address / PCI Interfacing */
d572 2
a573 6
		#ifdef VERSA
			IOS_EnablePCIIntr(0);
		#else
			IOS_ClearAndEnableSDIntr(0);
		#endif
  		//IOS_YieldThread(); 
