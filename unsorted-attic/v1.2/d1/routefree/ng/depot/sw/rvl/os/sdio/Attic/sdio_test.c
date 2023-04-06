d12 1
a12 1
#ident "$Id: sdio_test.c,v 1.1 2006/03/02 19:02:05 gbarnard Exp $"
d32 7
a38 6
#define PI_REG_CONFIG	0x024
#define PI_REGSP_CP	0x0c000000
#define PI_REGSP_PE	0x0c001000
#define PI_REGSP_DSP	0x0c005000
#define PI_GFXSP	0x0c008000
#define PI_REGSP_PI	0x0c003000
d41 1
d45 2
a46 2
#define STACK_SIZE 1024
const u8 _initStack[STACK_SIZE];
d50 1
a50 6
/* Thread created by idle process */
u8 testthrStack[1024]; /* 1024 is hardwired as stack size for this thread
                        * when the idle thread starts it. Please change
                        * it if you change this.
                        */
extern u32 timerIntrCnt;
d57 1
a57 2
    int i = 0;
    IOSTimerId  t2; //, t3, t1;
d62 4
a65 16
    /*
    printf("Set one-time timer [0xbabecafe]\n");
    t1 = IOS_CreateTimer(300, 0, mq, 0xbabecafe);
    printf("Set periodic timer [0xdeadbeef]\n");
    t2 = IOS_CreateTimer(0, 1000, mq, 0xdeadbeef);
    printf("Set one-time timer [0xbeeff00d]\n");
    t3 = IOS_CreateTimer(10000, 0, mq, 0xbeeff00d);

    do {
        printf("waiting for timer: %d @ %u\n", i++, IOS_GetTimer());
        IOS_ReceiveMessage(mq, &m, IOS_MESSAGE_BLOCK);
        printf("Received timer message %x @ %u\n", m, IOS_GetTimer());
        if (m == 0xbeeff00d) break;
    } while (1);
    printf("Destroy all timers\n");
    IOS_DestroyTimer(t1);
d67 1
a67 33
    IOS_DestroyTimer(t3);
    printf("Allocate new timer and see if we re-use ID\n");
    t2 = IOS_CreateTimer(30, 0, mq, 0xbabecafe);
    if (t1 != t2) {
        printf("Expected timer ID: %d, got %d\n", t1, t2);
        exit(-1);
    }
    IOS_DestroyTimer(t2);
    printf("pass\n");

    t1 = IOS_CreateTimer(5000, 0, mq, 0xbabecafe);
    t2 = IOS_CreateTimer(5000, 0, mq, 0xbabecafe);
    t3 = IOS_CreateTimer(5000, 0, mq, 0xdeadbeef);
    IOS_DestroyTimer(t3);
    t3 = IOS_CreateTimer(5000, 0, mq, 0xdeadbeef);
    if (t3 == t1 || t3 == t2) {
        printf("timer ID %d was re-used\n", t3);
        exit(-1);
    }
	*/
	
    i = 1;
    //printf("Test sleep timer [0xbabababa]\n");
    do 
    {

	    t2 = IOS_CreateTimer(arg, 0, mq, 0xbabababa);
        //printf("Waiting(%d) %08X", i, IOS_GetTimer());
        IOS_ReceiveMessage(mq, &m, IOS_MESSAGE_BLOCK);
        //printf("Rx Msg[%x] @ %08X\n", m, IOS_GetTimer());
        IOS_DestroyTimer(t2);
        i--;
    } while (i);
a72 1

d86 1
a86 1
	
d113 3
a115 3
	// Writing to PI config register for deasserting the soft reset 
	///busWrt32(PI_REGSP_PI + PI_REG_CONFIG,
	///	 PI_CONFIG_REG_SYSRSTB_MASK | PI_CONFIG_REG_MEMRSTB_MASK);		
d118 1
d121 1
a121 1
    printf("\n=== SDIO Init Module 2 ===\n");
