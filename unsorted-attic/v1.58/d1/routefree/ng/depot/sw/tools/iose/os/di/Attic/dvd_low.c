d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.57 2006/03/16 06:11:21 craig Exp $"
d661 1
a661 1
    DPRINT2("(handleDICommand) DIStatus(1): 0x%x\n", readDIStatus());
d672 1
a672 1
    DPRINT2("(handleDiCommand) Writing 0x%x to AIPPROT\n", reg);
d867 1
a867 1
        DPRINT2 ("READ RVL result: 0x%x\n", commandResult);
d985 1
a985 1
        DPRINT2("(handleDICommand) DIStatus(2): 0x%x\n", readDIStatus());
d993 1
a993 1
        DPRINT2("(handleDICommand) DIStatus(3): 0x%x\n", readDIStatus());
d1077 2
a1078 2
            DPRINT("(handleDiCommand): Starting ClearAndEnableDiIntr\n");  
	    DPRINT2("(handleDICommand) DIStatus before clear and enable: 0x%x\n", readDIStatus());
d1080 1
a1080 1
            DPRINT("(handleDiCommand) : Done ClearAndEnableDiIntr\n");  
d1126 1
a1126 1
            DPRINT ("(handleDiCommand) Found REVOLUTION disk\n");
