d12 1
a12 1
#ident "$Id: sd_slot.c,v 1.2 2006/03/15 01:11:03 gbarnard Exp $"
d838 1
a838 1
	
d867 1
a867 1
            //printf("[Command %02d Done]", command);
d1185 3
a1187 3
    printf("    Clock 0x%04x timeout %d\n",
           		READ_HOST_U16((u32)slot->m_base, HOSTREG_CLOCKCTRL),
                uTO);
