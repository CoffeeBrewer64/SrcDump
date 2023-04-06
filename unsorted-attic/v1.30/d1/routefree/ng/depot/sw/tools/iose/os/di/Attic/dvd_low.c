d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.29 2006/02/27 21:38:00 craig Exp $"
d57 1
d857 1
a857 1
                DPRINT ("(handleDiCommand) Received time out for previous command\n");
d862 1
d873 2
d877 2
a878 1
                DPRINT2 ("(handleDiCommand) Stopping timer %u\n", commandTimeoutId);
d895 1
d905 3
d909 2
a910 1
            break;
d930 2
a931 1
        commandResult = doReadHashEncryptedState();
d933 1
d939 6
d966 2
a967 2
    DPRINT4 ("doRawDiskRead: Reading %u bytes from byte address 0x%x/%u\n",
              length, wordOffset << 2, wordOffset << 2);
d974 1
d1094 1
d1100 10
d1113 1
d1117 1
d1122 8
d1136 1
d1139 1
