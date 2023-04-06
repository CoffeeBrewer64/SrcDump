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
#ifndef __NGLIBC_H__
#define __NGLIBC_H__
#define __SK_EMULATOR__

#include <ngtypes.h>
#include <sktypes.h>
void SK_Perror(const char *s, SKError errno);

#ifndef __SK_EMULATOR__
typedef unsigned long int size_t;

void *memcpy(void *dst, const void *src, size_t n);
void *memmove(void *dst, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

size_t strnlen(const char *str, size_t n);
char *strncpy(char *dst, const char *src, size_t n);
int strncmp(const char *a, const char *b, size_t n);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);

int printf(const char *fmt, ...);
int puts(const char *s);
int putchar(int c);

void exit(int status);
#endif

#endif /* __NGLIBC_H__ */
