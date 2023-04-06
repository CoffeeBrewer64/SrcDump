d12 1
a12 1
#ident "$Id: sdio_serial.c,v 1.3 2006/03/16 19:27:55 gbarnard Exp $"
d760 1
d763 2
a764 1

d939 1
a939 1
        	printf("(CMD:%d %s)\n",cmd_op.command,sd_cmd_str[cmd_op.command]);
d943 1
a943 1
        	printf("(CMD:%d)\n",cmd_op.command);
d968 1
a968 1
	            printf("   Resp %08X %08X %08X %08X\n",
d1137 1
a1137 1
		SER_DEBUG (DEBUG_SER_ERR, "%s: new debug levels:%X\n\n",
