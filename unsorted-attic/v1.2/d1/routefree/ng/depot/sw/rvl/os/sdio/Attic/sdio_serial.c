d12 1
a12 1
#ident "$Id: sdio_serial.c,v 1.1 2006/03/02 19:02:05 gbarnard Exp $"
d76 1
a76 1
		    printf("   waiting TmrNo=%d ",rv);
d78 1
a78 1
			printf("   timed %x",slpQ);
d81 1
a81 1
			if (ids[0]!=0) printf("%s\n",ids);
d84 14
a97 2
	    	testthr(usec*2);	
	    	return 0;
d355 1
a355 1
initSDIO(void)
d400 1
a400 1
				sdh_global->m_sdslot[i].m_base = (void*)0x0d070000;
d404 1
a404 1
				sdh_global->m_sdslot[i].m_base = (void*)0x0d070100;			
d489 1
a489 1
sdio_init_module (void)
d527 1
a527 1
	 	initSDIO();
d682 67
a748 1

d768 2
a769 2
    SER_DEBUG (DEBUG_SER_ERR, "%s (cmd %d  arg 0x%x)\n", 
               __FUNCTION__, (unsigned int)cmd&0xFF, (unsigned int)arg);
a832 1
        printf("RESET\n");
d943 9
d972 5
a976 2
            /*SER_DEBUG (DEBUG_SER_ERR, "%s:cresp %04X %04X %04X %04X\n",__FUNCTION__,
            	cmd_op.buffer[0],cmd_op.buffer[1],cmd_op.buffer[2],cmd_op.buffer[3]);*/
