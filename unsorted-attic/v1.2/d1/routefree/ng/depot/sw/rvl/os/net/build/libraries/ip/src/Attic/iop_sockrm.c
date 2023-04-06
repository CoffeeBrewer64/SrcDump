d25 1
d342 1
a342 1
    for (i = 0; i < SO_SOCKET_MAX-1; i++)
d344 1
a344 1
        rmThreadId = IOS_CreateThread(sockRM, NULL, __netSockStack + i* NET_SOCK_STACK_SIZE,
d425 11
d439 2
a440 1
    SOStartup(&Config);
d443 2
d447 1
a447 1
    printf ("****** This should never be printed *******\n");
