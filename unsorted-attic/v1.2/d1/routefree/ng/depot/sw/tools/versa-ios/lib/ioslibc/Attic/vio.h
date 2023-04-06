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

#ifndef __VIO_H__
#define __VIO_H__

int __sys_open(unsigned long *args);
int __sys_close(unsigned long *args);
int __sys_writec(const char *c);
int __sys_write0(const char *s);
int __sys_write(unsigned long *args);
int __sys_read(unsigned long *args);
int __sys_readc(int);
int __sys_iserror(unsigned long *args);
int __sys_istty(unsigned long *args);
int __sys_seek(unsigned long *args);
int __sys_flen(unsigned long *args);
int __sys_tmpnam(unsigned long *args);
int __sys_remove(unsigned long *args);
int __sys_rename(unsigned long *args);
int __sys_clocK(unsigned long *args);
int __sys_time(void);
int __sys_system(unsigned long *args);
int __sys_errno(unsigned long *args);
int __sys_get_cmdline(unsigned long *args);
int __sys_heapinfo(unsigned long *args);
int __sys_elapsed(unsigned long *args);
int __sys_tickfreq(unsigned long *args);

#endif /* __VIO_H__ */
