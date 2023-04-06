a13 13
// Interface family
#define IP_INET             2       // Internet protocol

typedef struct IPSocket
{
    u8              len;        // IP_SOCKLEN
    u8              family;     // IP_INET
    u16             port;
    u8              addr[IP_ALEN];
} IPSocket;

#define IP_SOCKLEN          sizeof(IPSocket)

a83 2
    SOOpenLib();

a141 2
    SOCloseLib();

