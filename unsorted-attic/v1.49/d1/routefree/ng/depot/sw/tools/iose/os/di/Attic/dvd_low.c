d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.48 2006/03/08 22:57:54 craig Exp $"
d876 1
a876 1
        printf("Unhandled case (0x%x) in handleDiCommand",
d878 2
a879 1
        diFatalError("Unhandled case in handleDiCommand");
a892 1
        uint32_t accessReg;
d895 1
a895 1
        DPRINT2 ("(handleDiCommand) Calling IOS_ReceiveMessage (queueId = %d\n",
d898 2
a899 4
        accessReg = busRd32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK);
        /* Disable control over PI_IO */
        AIPPROT_SET_ENAHBIOPI(accessReg, 0);

d904 2
d995 4
a998 2
        case DI_MESG_COMMAND:
            DPRINT ("(handleDiCommand) Got DI_MESG_COMMAND - buffering message.\n");
d1000 1
d1003 2
d1013 1
a1013 1
                printf ("(handleDiCommand) Unhandled message case (message = 0x%x)\n",
