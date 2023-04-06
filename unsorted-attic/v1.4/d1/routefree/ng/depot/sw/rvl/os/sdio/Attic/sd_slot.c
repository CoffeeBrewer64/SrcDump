d12 1
a12 1
#ident "$Id: sd_slot.c,v 1.3 2006/03/16 19:31:58 gbarnard Exp $"
d835 9
a843 1

d846 1
a846 1
	printf(" ");
d875 1
a875 1
            //if (command<14) printf("[Command %02d Done]", command);
d992 1
a992 8
    /* 
     * Determine which status bits are interrupt (signal) enabled, 
     * some status signals may be polled.
     */
    wIntStatus = wIntStatus & wIntSignal;
    
    /* clear slot interrupts - also any ones not handled! */
    WRITE_HOST_U16((u32)slot->m_base, HOSTREG_NORMINTRSTAT, wIntStatus);
