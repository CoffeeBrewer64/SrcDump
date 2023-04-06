#include "os_usb.h"
#include "osint.h"

#ifdef DEBUG
#define	PRINTF	osSyncPrintf
#else
#define	PRINTF(format, args...)
#endif


/*
 * osUsbDevGetHandle
 *
 * Description:
 *	Open or attach to a particular USB device.
 *
 * Returns:
 * 	0 for success
 * 	< 0 for failure
 */
s32
osUsbDevGetHandle(s32 ctlr, OSUsbInfo *ip, OSUsbHandle *hp)
{
	__OSUsbMesg um;
	OSMesg msg = (OSMesg)&um;
	OSMesg rmsg;
	OSMesgQueue rq;

	if (ctlr < 0 || ctlr >= OS_USB_MAX_CONTROLLERS) {
		PRINTF("osUsbDevGetHandle called with bad arg %d\n", ctlr);
		/* osError() */
		return(-1);
	}

	/*
	 * Formulate query message
	 */
	bzero(&um, sizeof um);
	um.um_type = OS_USB_MESG_HANDLE;
	um.u.umh.umh_info = ip;
	um.u.umh.umh_handle = hp;
	um.um_rq = &rq;

	bzero((void *)hp, sizeof (*hp));

	/*
	 * Initialize the private queue to receive the reply
	 */
	osCreateMesgQueue(&rq, &rmsg, 1);

	/*
	 * Send message to the manager thread and wait for the response
	 */
	PRINTF("osUsbDevGetHandle: send msg\n");
	(void) osSendMesg(&__osUsbCtlrQ[ctlr], msg, OS_MESG_BLOCK);

	(void) osRecvMesg(&rq, &msg, OS_MESG_BLOCK);

	/*
	 * Validate the response message
	 */
	if (msg != &um) {
		PRINTF("osUsbDevGetHandle: reply msg not the same (0x%x)\n", msg);
	}
	if (um.um_type != OS_USB_REPLY_HANDLE) {
		PRINTF("osUsbDevGetHandle: reply msg type wrong (0x%x)\n", um.um_type);
	}

	PRINTF("osUsbDevGetHandle: returns %d\n", um.um_ret);
	return(um.um_ret);
}
