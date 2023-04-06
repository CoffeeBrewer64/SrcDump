d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.24 2006/02/18 00:39:41 craig Exp $"
d33 1
d440 1
a440 1
    printf ("(handleDiCommand) Command is: 0x%x\n", diCommand->theCommand);
d619 1
a619 1
        printf ("READ RVL result: 0x%x\n", commandResult);
d728 1
a728 1
        printf ("(handleDiCommand) Calling IOS_ReceiveMessage\n");
d732 1
a732 1
        printf ("(handleDiCommand) IOS_ReceiveMessage returns.\n");
d738 1
a738 1
            printf ("(handleDiCommand) Stopping timer %u\n", commandTimeoutId);
d747 1
a747 1
                printf ("(handleDiCommand) Current command timed out\n");
d751 1
a751 1
                printf ("(handleDiCommand) Received time out for previous command\n");
d763 1
a763 1
                printf ("Received cover interrupt message!\n");
d788 1
a788 1
        printf ("(handleDiCommand) TC received\n");
d793 1
a793 1
        printf ("(handleDiCommand) Error received\n");
d799 1
a799 1
        printf ("(handleDiCommand) Timeout\n");
d812 1
a812 1
    printf ("(handleDiCommand) Returning 0x%x\n", commandResult);
d838 2
a839 2
    printf ("doRawDiskRead: Reading %u bytes from byte address 0x%x/%u\n",
             length, wordOffset << 2, wordOffset << 2);
d882 1
a882 1
    printf ("(**** doWaitForCoverClose) entry\n");
d887 1
a887 1
        printf ("(doWaitForCoverClose) Received message\n");
d892 1
a892 1
            printf ("(**** doWaitForCoverClose) exit 1\n");
d896 1
a896 1
    printf ("(**** doWaitForCoverClose) exit 2\n");
d919 1
a919 1
    printf ("(startTimedTransfer) Setting timer: time = %d, queue ID = %d\n",
