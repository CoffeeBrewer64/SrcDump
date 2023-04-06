/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

/*
 * $Id: sdio_test.h,v 1.1 2006/03/30 16:50:23 gbarnard Exp $
 */

#ifndef _SDIO_TEST_H_
#define _SDIO_TEST_H_

#ifdef LINUX
#ifndef bool
typedef int bool;
#define true 1
#define false 0
#endif
#endif

#define DEBUG_FATAL    0
#define DEBUG_ERR      1
#define DEBUG_CHATTY   2

#define SDIO_DEVICE "/dev/sdio"
#define SDIO_DEVICE0 "/dev/sdio0"
#define SDIO_DEVICE1 "/dev/sdio1"
#define SDIO_DEVICE2 "/dev/sdio2"
#define SDIO_DEVICE3 "/dev/sdio3"

typedef enum {
    ACTION_ILLEGAL,
    ACTION_QUIT,
    ACTION_OPEN,
    ACTION_CLOSE,
    ACTION_READ,
    ACTION_WRITE,
    ACTION_POLL,
    ACTION_IOCTL,
    ACTION_HELP,
    ACTION_USAGE,
    ACTION_GET,
    ACTION_SET,
    ACTION_READREG,
    ACTION_WRITEREG,
    ACTION_READCREG,
    ACTION_WRITECREG,
    ACTION_RESET,
    ACTION_RESET_CARD,
    ACTION_SLEEP,
    ACTION_INTEN,
    ACTION_INTDIS,
    ACTION_CMD,
    ACTION_SENDRCA,
    ACTION_GETCLOCK,
    ACTION_GETVOLT,
    ACTION_SETCLOCK,
    ACTION_SETVOLT,
    ACTION_CLOCKON,
    ACTION_CLOCKOFF,
    ACTION_WIDTH,
    ACTION_POWER,
    ACTION_OCR,
    ACTION_READCIS,
    ACTION_MULTREAD,
    ACTION_MULTWRITE,
    ACTION_HISTORY,
    ACTION_FUNCON,
    ACTION_FUNCOFF,
    ACTION_READCCCR,
    ACTION_WRITECCCR,
    ACTION_READFBR,
    ACTION_INSERT,
    ACTION_REINIT,
    ACTION_RESETCMD,
    ACTION_RESETDAT,
    ACTION_RESETALL,
    ACTION_TOGGLE,
    ACTION_INST_CALLBACK,
    ACTION_DEINST_CALLBACK,
    ACTION_STATUS,
    ACTION_WAIT_INSERT,
    ACTION_WAIT_ERROR,
    ACTION_WAIT_INTERRUPT,
    ACTION_TEST_DEBUG,
    ACTION_DRIVER_DEBUG,
} action_t;

/*
 * Prototypes.
 */
extern char *tuple_name (int tuple);
extern char *decode_device_status (int device_status);
#ifndef LINUX
#define ssize_t u32
#define FILE void
#endif
extern ssize_t getline(char **lineptr, size_t *n, FILE *stream);

extern void mem_dump (char *buf, int len);

#endif /* _SDIO_TEST_H_ */

/* eof */
