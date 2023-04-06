d39 1
a39 1
const u8 _initStack[NET_SOCK_STACK_SIZE]  __attribute__((aligned(32)));
d43 1
a43 1
static char __netSockStack[(SO_SOCKET_MAX-1) * NET_SOCK_STACK_SIZE] __attribute__((aligned(32)));
d73 1
d83 1
d92 1
d102 1
d113 1
d123 1
d133 1
d146 1
d159 1
d169 1
d180 1
d193 1
d206 1
d216 1
d227 1
d330 1
a330 1
                OSReport("Network RM got request: UNKNOWN\n");
d394 6
d443 3
d466 5
