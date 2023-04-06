d23 1
a23 1
#include <socket.h>
a24 3
//#include <dolphin/os.h>
//#include <dolphin/ip/IFEther.h>
//#include <dolphin/os/OSAlarm.h>
d38 5
a42 1
static char __netSockStack[SO_SOCKET_MAX * NET_SOCK_STACK_SIZE] __attribute__((aligned(32)));
d341 1
a341 1
    for (i = 0; i < SO_SOCKET_MAX; i++)
d367 70
