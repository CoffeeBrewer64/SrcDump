#include "os_usb.h"
#include "osint.h"

#ifdef DEBUG
#define	PRINTF	osSyncPrintf
#else
#define	PRINTF(format, args...)
#endif


/*
 * osUsbDevQuery
 *
 * Description:
 *	Find out what devices are present on one of the USB controllers.
 *
 * Returns:
 * 	Number of devices found (0 if none)
 */
s32
osUsbDevQuery(s32 ctlr, OSUsbInfo *ip, s32 nip)
{
	__OSUsbMesg um;
	OSMesg msg = (OSMesg)&um;
	OSMesg rmsg;
	OSMesgQueue rq;

	if (ctlr < 0 || ctlr >= OS_USB_MAX_CONTROLLERS) {
		PRINTF("osUsbDevQuery called with bad arg %d\n", ctlr);
		/* osError() */
		return(-1);
	}

	/*
	 * Formulate query message
	 */
	bzero(&um, sizeof um);
	um.um_type = OS_USB_MESG_QUERY;
	um.u.umq.umq_info = ip;
	um.u.umq.umq_ninfo = nip;
	um.um_rq = &rq;

	bzero((void *)ip, nip * sizeof (*ip));

	/*
	 * Initialize the private queue to receive the reply
	 */
	osCreateMesgQueue(&rq, &rmsg, 1);

	/*
	 * Send message to the manager thread and wait for the response
	 */
	PRINTF("osUsbDevQuery: send msg\n");
	(void) osSendMesg(&__osUsbCtlrQ[ctlr], msg, OS_MESG_BLOCK);

	(void) osRecvMesg(&rq, &msg, OS_MESG_BLOCK);

	/*
	 * Validate the response message
	 */
	if (msg != &um) {
		PRINTF("osUsbDevQuery: reply msg not the same (0x%x)\n", msg);
	}
	if (um.um_type != OS_USB_REPLY_QUERY) {
		PRINTF("osUsbDevQuery: reply msg type wrong (0x%x)\n", um.um_type);
	}

	PRINTF("osUsbDevQuery: returns %d devices\n", um.u.umq.umq_ninfo);
	return(um.u.umq.umq_ninfo);
}
