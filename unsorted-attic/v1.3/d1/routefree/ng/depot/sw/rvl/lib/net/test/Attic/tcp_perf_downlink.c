
#include <ios.h>
#include <iostypes.h>
#include <ioslibc.h>
#include <socket.h>

#define STACK_SIZE          (4 * 1024)
const u8 _initStack[STACK_SIZE] __attribute__ ((aligned (4)));
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = 10;

#define OSReport            printf

//const u8 Host[4]        = {  10,   0,   0,  33 };
const u8 Server[4]      = {  10,   0,   0, 177 };
const u8 Netmask[4]     = { 255, 255, 255,   0 };
const u8 Gateway[4]     = {  10,   0,   0,   6 };

#define TCP_PORT            8000
#define BUF_SIZE            1024
#define TEST_NUM            10000
char buf[BUF_SIZE] __attribute__((aligned(32))) __attribute__((section(".data")));

IPSocket socket __attribute__((aligned(32))) __attribute__((section(".data")));

SOConfig Config __attribute__((aligned(32))) __attribute__((section(".data"))) =
{
    SO_VENDOR_NINTENDO,
    SO_VERSION,

    0,
    0,

    SO_FLAG_DHCP,
    { SO_INADDR_ANY },
    { SO_INADDR_ANY },
    { SO_INADDR_ANY },
    { SO_INADDR_ANY },
    { SO_INADDR_ANY },

    4096,
    4096
};

static void sleep( void )
{
    int tick = 10000000;
    IOSMessage msgQ[1], msg;
    IOSMessageQueueId qid;
    IOSTimerId timerId;

    /* Create a message queue for timer management */
    if ((qid = IOS_CreateMessageQueue(msgQ, sizeof(msgQ))) < 0 ) {
        printf("Creating message queue failed\n");
        return;
    }
	timerId=IOS_CreateTimer((IOSTime)tick, 0, qid, (IOSMessage)0);
	IOS_ReceiveMessage(qid, &msg, IOS_MESSAGE_BLOCK);
    IOS_DestroyTimer(timerId);
    IOS_DestroyMessageQueue(qid);
}

static void waitForStart(void)
{
}

#define OSTicksToSeconds(x)             ((x) >> 21)
static unsigned getCurrTime(void)
{
    return OSTicksToSeconds(IOS_GetTimer());
}

void main(void)
{
    s32      rc;
    int      fd;
    u32      i;
    int      ret;
    int      nbytes;
    unsigned startTime, endTime;

    waitForStart();

    //memcpy(&Config.addr,    Host,     4);
    memcpy(&Config.netmask, Netmask,    4);
    memcpy(&Config.router,  Gateway,    4);
    ret = SOStartup(&Config);
    OSReport("%s: SOStartup return = %d\n", __FUNCTION__, ret);
    if (ret < 0)
        return;

    while (SOGetHostID() == 0) {
        sleep();
    }

    fd = SOSocket(SO_PF_INET, SO_SOCK_STREAM, 0);
    OSReport("SOSocket return: %d\n", fd);
    if (fd < 0)
        goto cleanup;

    socket.len    = IP_SOCKLEN;
    socket.family = IP_INET;
    memcpy(socket.addr, Server, IP_ALEN);
    socket.port   = TCP_PORT;

    rc = SOConnect(fd, &socket);
    OSReport("SOConnect return : %d\n", rc);
    if (rc < 0)
        goto error;

    OSReport("Start downlink performance test\n");
    startTime = getCurrTime();

    for (i=0; i<TEST_NUM; i++)
    {
        nbytes = 0;
        while (nbytes < BUF_SIZE)
        {
            if ((rc = SORecv(fd, buf+nbytes, BUF_SIZE-nbytes, 0)) == -1) {
                OSReport("SORecv error\n");
                goto error;
            }
            nbytes += rc;
            // OSReport("nbytes = %d, rc = %d\n", nbytes, rc);
        }
    }

    endTime = getCurrTime();
    OSReport("End downlink performance test\n");
    OSReport("Total KBytes received %d\n", TEST_NUM * BUF_SIZE / 1024);
    OSReport("Total time spent %d seconds\n", endTime - startTime);
    OSReport("Throughput = %d Kbps\n", 
        (TEST_NUM * BUF_SIZE / 1024) / (endTime - startTime) * 8);

error:
    rc = SOClose(fd);
    OSReport("SOClose return: %d\n", rc);

cleanup:
    SOCleanup();

    OSReport("Done.");
    return;
}
