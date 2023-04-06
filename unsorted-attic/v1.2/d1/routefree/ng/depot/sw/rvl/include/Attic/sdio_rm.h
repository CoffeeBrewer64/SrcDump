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

#ident "$Id: sdio_rm.h,v 1.1 2006/03/16 19:22:55 gbarnard Exp $"

#define SDIO_ERROR 0x00000001
#define SDIO_DEBUG 0x00000002
#define SDIO_INIT  0x00000004
#define SDIO_OPEN  0x00000008
#define SDIO_CLOSE 0x00000010
#define SDIO_READ  0x00000020
#define SDIO_WRITE 0x00000040
#define SDIO_SEEK  0x00000080
#define SDIO_IOCTL 0x00000100

extern u32 sdio_debug;

#define SDIO_LOG(x, y, ...) if (sdio_debug & x) printf (y, __VA_ARGS__);

IOSError sdio_rm(u32 arg);

/* eof */
