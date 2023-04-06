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
#ifndef __IOS_LIBC_H__
#define __IOS_LIBC_H__

#include <stdarg.h>
#include <iosiobuf.h>

typedef unsigned long int size_t;

void *memcpy(void *dst, const void *src, size_t n) ;
void *memmove(void *dst, const void *src, size_t n) ;
void *memset(void *s, int c, size_t n) ;
int memcmp(const void *s1, const void *s2, size_t n) ;

size_t strnlen(const char *str, size_t n) ;
char *strncpy(char *dst, const char *src, size_t n) ;
int strncmp(const char *a, const char *b, size_t n) ;
char *strchr(const char *s, int c) ;
char *strrchr(const char *s, int c) ;
char *strstr (const char *haystack, const char *needle) ;

typedef int FILE;
#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2

FILE *fopen(const char *filename, const char *mode) ;
int flen(FILE *) ;
int fclose(FILE *) ;
int fread(void *ptr, int size, int nmemb, FILE *fp) ;
int fwrite(void *ptr, int size, int nmemb, FILE *fp) ;
int fseek(FILE *fp, long offset, int whence) ;

int scanf(const char *fmt, ...) ;
int busPrintf(const char *fmt, ...) ;
int printf(const char *fmt, ...) ;
int vprintf(const char *fmt, va_list ap) ;
int puts(const char *s) ;
char *gets(char *s) ;
int putchar(int c) ;
int getchar(void) ;

char *tmpnam(char *s) ;
int unlink(const char *pathname) ;
int rename(const char *oldpath, const char *newpath) ;
int time(int *t) ;

void exit(int status) ;

void get_cmdline(char *buf, unsigned long bufLen) ;

void IOS_DebugDumpIobQueue(IOSIobuf *iob) ;
void IOS_DebugDumpIobChain(IOSIobuf *iob) ;

IOSError usleep(u32 usec) ;

#define busDbg     busPrintf
#define busClose()   /* nothing */
#define busInit(...) /* nothing */
#define _ahb_busInit(...) /* nothing */

#define busRd32(addr)  IO_READ(addr)
#define busWrt32(addr, val) IO_WRITE(addr, val)
#define busRd16(addr)  IO_READ16(addr)
#define busWrt16(addr, val) IO_WRITE16(addr, val)

void busDelay(u32 cycles) ;

#endif /* __IOS_LIBC_H__ */
