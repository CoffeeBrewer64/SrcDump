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
#include "nglibc.h"
#ifndef __SK_EMULATOR__
#include <sktypes.h>

void *
memcpy(void *dst, const void *src, size_t n)
{
    char *d = dst;
    const char *s = src;
    while (n--) {
        *d++ = *s++;
    }
    return dst;
}

void *
memmove(void *dst, const void *src, size_t n)
{
    char *d = dst;
    const char *s = src;
    if (src < dst && dst < (src + n)) {
        /* Copy overlapping regions backwards */
        d += n;
        s += n;
        while (n--) {
            *--d = *--s;
        }
    } else {
        /* Copy non-overlapping regions just like memcpy */
        while (n--) {
            *d++ = *s++;
        }
    }
    return dst;
}

void *
memset(void *s, int c, size_t n)
{
    u8 *p = s;

    while (n--) {
        *p++ = (u8) c;
    }
    return s;
}

int
memcmp(const void *s1, const void *s2, size_t n)
{
    const u8 *a = s1;
    const u8 *b = s2;

    if (n == 0) {
        return 0;
    }
    while (--n && (*a == *b)) {
        ++a;
        ++b;
    }
    return (*a - *b);
}

size_t
strnlen(const char *str, size_t n)
{
    const char *s = str;
    while (*s && n-- > 0)
        ++s;
    return s - str;
}

char *
strncpy(char *dst, const char *src, size_t n)
{
    char *d = dst;
    const char *s = src;
    while (n > 0) {
        --n;
        if ((*d++ = *s++) == '\0') {
            break;
        }
    }
    while (n-- > 0)
        *d++ = '\0';
    return dst;
}

int
strncmp(const char *a, const char *b, size_t n)
{
    if (n == 0) {
        return 0;
    }
    while (n-- && (*a == *b)) {
        if (n == 0 || *a == '\0') {
            break;
        }
        ++a;
        ++b;
    }
    return (*(u8 *)a - *(u8 *)b);
}

char *
strchr(const char *s, int c)
{
    const char *p = s;

    while (*p && (*p != c)) {
        ++p;
    }
    return (*p == c) ? (char *)p : NULL;
}

char *
strrchr(const char *s, int c)
{
    const char *p = s;

    while (*p) {
        ++p;
    }

    while ((p != s )&& (*p != c)) {
        --p;
    }
    return (*p == c) ? (char *)p : NULL;
}
#endif /* ! __SK_EMULATOR__ */
