d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.45 2006/03/05 06:11:22 craig Exp $"
a903 5
	DPRINT2("The IOP DI enable value is: %d\n", IOPDiIntrEnabled());

        accessReg = busRd32(ACR_REGS_BASE + AIPPROT_OFFSET + BUS_ENABLE_MASK);
        /* Disable control over PI_IO */
        AIPPROT_SET_ENAHBIOPI(accessReg, 1);
d1007 1
a1007 1
                printf ("(handleDiCommand) Unhandled message case (%d)\n",
d1023 15
a1037 5
    if (   diCommand->theCommand == DI_READ_DISK_ID_CMD
        && diskState.hashEncryptedValid == false
        && commandResult == DI_ERR_NO_ERROR) {
        DPRINT("(handleDiCommand) Note! not reading hash and encrypted state\n");
        // commandResult = doReadHashEncryptedState();
d1043 1
a1043 1
        sendError = IOS_SendMessage(dvdDriverInQueue,
