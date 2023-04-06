d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.13 2006/01/21 02:52:23 craig Exp $"
d309 1
a309 1
handleDiCommand(const diCommand_t* const diCommand)
d370 1
a370 1
        DIDmaDestAddr = diCommand->arg[0];
d398 1
a398 1
        DIDmaDestAddr = diCommand->arg[0];
d409 1
a409 1
        DIDmaDestAddr = diCommand->arg[0];
d421 1
a421 1
        DIDmaDestAddr = diCommand->arg[0];
d433 1
a433 1
        DIDmaDestAddr = diCommand->arg[2];
d460 1
a460 1
        DIDmaDestAddr = diCommand->arg[0];
d474 1
a474 1
        DIDmaDestAddr = diCommand->arg[0];
d488 1
a488 1
        DIDmaDestAddr = diCommand->arg[0];
d513 1
a513 1
        DIDmaDestAddr = diCommand->arg[0];
d564 1
a564 1
        DIDmaDestAddr = diCommand->arg[0];
d576 1
a576 3
        while (1) {
            printf ("Implement me!!!\n");
        }
d663 7
a669 2
        default:
            diFatalError ("(handleDiCommand) Unhandled message case\n");
d718 1
a718 1
    commandResult = handleDiCommand(&diCommand);
d739 1
a739 1
    commandResult = handleDiCommand(&diCommand);
d746 1
a746 1
 * Loop repeatedly until we receive an interrupt message corresponding
a747 1
 * FIXME - handle dummy interrupts
