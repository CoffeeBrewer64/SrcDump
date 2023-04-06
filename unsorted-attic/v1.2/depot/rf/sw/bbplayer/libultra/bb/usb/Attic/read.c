#include "os_usb.h"
#include "osint.h"

#ifdef DEBUG
#define	PRINTF	osSyncPrintf
#else
#define	PRINTF(format, args...)
#endif


/*
 * osUsbDevRead
 *
 * Description:
 *	Read data from a USB device
 *
 * Returns:
 * 	Number of characters read
 * 	< 0 for failure
 */
s32
osUsbDevRead(OSUsbHandle *hp, u8 *buf, s32 len, u64 offset)
{
	__OSUsbMesg um;
	OSMesg msg = (OSMesg)&um;
	OSMesg rmsg;
	OSMesgQueue rq;

	/*
	 * Formulate query message
	 */
	bzero(&um, sizeof um);
	um.um_type = OS_USB_MESG_READ;
	um.u.umrw.umrw_handle = hp;
	um.u.umrw.umrw_buffer = buf;
	um.u.umrw.umrw_len = len;
	um.u.umrw.umrw_offset = offset;
	um.um_rq = &rq;

	/*
	 * Initialize the private queue to receive the reply
	 */
	osCreateMesgQueue(&rq, &rmsg, 1);

	/*
	 * Send message to the manager thread and wait for the response
	 */
	PRINTF("osUsbDevRead: send msg\n");
	(void) osSendMesg(hp->uh_mq, msg, OS_MESG_BLOCK);

	(void) osRecvMesg(&rq, &msg, OS_MESG_BLOCK);

	/*
	 * Validate the response message
	 */
	if (msg != &um) {
		PRINTF("osUsbDevRead: reply msg not the same (0x%x)\n", msg);
	}
	if (um.um_type != OS_USB_REPLY_READ) {
		PRINTF("osUsbDevRead: reply msg type wrong (0x%x)\n", um.um_type);
	}

	PRINTF("osUsbDevRead: returns %d\n", um.um_ret);
	return(um.um_ret);
}
