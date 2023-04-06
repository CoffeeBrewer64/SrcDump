#include "os_usb.h"
#include "osint.h"

#ifdef DEBUG
#define	PRINTF	osSyncPrintf
#else
#define	PRINTF(format, args...)
#endif

/*
 * Static data structures to support the manager threads for
 * the USB controllers (one thread and message queue per controller).
 */
static OSThread	__osUsbMgr[OS_USB_MAX_CONTROLLERS];
static char	__osUsbMgrStacks[OS_USB_MGR_STACKSIZE * OS_USB_MAX_CONTROLLERS]
		__attribute__ ((aligned (8)));
OSMesgQueue	__osUsbCtlrQ[OS_USB_MAX_CONTROLLERS];
static OSMesg	__osUsbMesgs[OS_USB_QUEUE_SIZE * OS_USB_MAX_CONTROLLERS];


/*
 * Manager Thread process for each USB controller
 */
static void
__osUsbMgrProc(char *arg)
{
	OSMesgQueue *mq;
	OSMesg msg;
	__OSUsbMesg *up;
	OSId myid;

	mq = (OSMesgQueue *)arg;
	myid = osGetThreadId(NULL);

	/*
	 * Loop forever processing messages on the input queue
	 */
	while (1) {
		PRINTF("USBMgr%d: wait on q\n", myid);
		(void)osRecvMesg(mq, &msg, OS_MESG_BLOCK);
		up = msg;
		PRINTF("USBMgr%d: received mesg type ", myid);
		switch (up->um_type) {
		case OS_USB_MESG_QUERY:
			PRINTF("QY\n");
			break;
		case OS_USB_MESG_READ:
			PRINTF("RD\n");
			break;
		case OS_USB_MESG_WRITE:
			PRINTF("WR\n");
			break;
		default:
			PRINTF("unknown\n");
			break;
		}

		/*
		 * Send reply
		 */
		up->um_type |= OS_USB_REPLY_MASK;
		if (osSendMesg(up->um_rq, (void *)up, OS_MESG_NOBLOCK) < 0) {
			PRINTF("USBMgr%d: reply queue full!\n", myid);
		}
	}
}


/*
 * osContUsbInit
 *
 * Description:
 *	Must be called to start the manager thread for each
 *	USB controller.
 *
 * Returns:
 * 	0 for success
 * 	-1 for failure (sets error code?)
 */
s32
osUsbContInit(s32 ctlr)
{
	/*
	 * Just create the thread for now
	 */
	if (ctlr < 0 || ctlr >= OS_USB_MAX_CONTROLLERS) {
		osSyncPrintf("osUsbContInit called with bad arg %d\n", ctlr);
		/* osError() */
		return(-1);
	}
	osCreateMesgQueue(&__osUsbCtlrQ[ctlr],
		&__osUsbMesgs[OS_USB_QUEUE_SIZE * ctlr],
		OS_USB_QUEUE_SIZE);
	osCreateThread(&__osUsbMgr[ctlr], 
		3141+ctlr, 
		(void(*)(void *))__osUsbMgrProc,
		(void *)&__osUsbCtlrQ[ctlr],
		(void *)&__osUsbMgrStacks[OS_USB_MGR_STACKSIZE*(ctlr+1)],
		16);
	osStartThread(&__osUsbMgr[ctlr]);

	return(0);
}
