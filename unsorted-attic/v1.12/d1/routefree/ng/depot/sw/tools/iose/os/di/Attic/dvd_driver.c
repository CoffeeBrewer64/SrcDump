d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.11 2006/01/19 22:57:05 craig Exp $"
d75 10
d86 1
d120 1
d145 4
a148 1
        printf ("(dvd_driver) Doing IOS_ReceiveMessage\n");
d155 1
a155 1
        printf ("(dvd_driver) Done IOS_ReceiveMessage\n");
a172 1
            printf ("In length is: %d\n", inMesg.resourceMesg->args.ioctl.inLen);
d174 1
d182 4
d190 5
a194 1
            diFatalError("Note: Transaction error message in main DVD loop.\n");
d207 6
a212 1
            printf ("Received cover interrupt message!\n");
a360 2
static uint32_t     lastCommandResult;

d365 3
a367 1
    uint32_t            ioctlReturn;
d378 6
d389 22
d413 11
a423 2
        lastCommandResult = handleDiCommand(command);
        switch (lastCommandResult) {
d437 4
d442 1
a442 1
            ioctlReturn = DVD_INTTYPE_DE;
d445 4
a448 1

d453 1
a453 1
}
d466 39
