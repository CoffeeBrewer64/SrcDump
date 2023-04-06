/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished proprietary information of BroadOn Communications Corp.,
 *  and are protected by federal copyright law. They may not be disclosed
 *  to third parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 *  Description:
 *      This file implements standard IO functions using semi-hosting
 *
 */


#include <stdarg.h>

#include "ioslibc.h"
#include "../vio.h"

#define BUF_SIZE 16

typedef struct {
    char buf[BUF_SIZE];
    unsigned int pos;
} Context;

static void __writec(Context *ctx, char c)
{
    ctx->buf[ctx->pos++] = c;
    if (ctx->pos == BUF_SIZE-1) {
        ctx->buf[ctx->pos] = 0;
        ctx->pos = 0;
        __sys_write0(ctx->buf);
    }
}

static void __writes(Context *ctx, char *s)
{
    if (ctx->pos) {
        ctx->buf[ctx->pos] = 0;
        ctx->pos = 0;
        __sys_write0(ctx->buf);
    }
    if (*s) __sys_write0(s);
}

static void PAD(Context *ctx, int n, char c) {
    while (n--) {
        __writec(ctx, c); 
    } 
}

/*
 *  Function: printf
 *
 *  Description:
 *      Print a string to the console using semi-hosting.
 *      Currently %c, %s, %x, %X, and %d are supported
 *
 *  Inputs:
 *      fmt - Format string
 *      ... - Variable number of arguments
 *
 *  Outputs:
 *      A string printed to the console
 *
 *  Return values:
 *      0 - Successful completion
 *
 */
int
vprintf(const char *fmt, va_list ap)
{
    char                c = '\0';
    char                scratch[24], *str, *ptr;
    unsigned int        leading0 = 0, neg = 0;
    unsigned int        value = 0, value2 = 0;
    int                 svalue = 0;
    int                 count = 0;
    int                 showLeading0s = 0;
    int                 width = 0;
    int                 left = 0;
    int                 alternate = 0;
    int                 len;
    int                 sign = 0;
    char                t, base;
    int                 length = 0;
    Context             ctx;

    ctx.pos = 0;
    while ((c = *fmt++)) {
        if (c == '%') {
            /* flags */
            width = alternate = left = sign = showLeading0s = 0;
            while ((c = *fmt++)) {
                switch (c) {
                case '#':
                    alternate = 1;
                    break;
                case '+':
                    sign = 1;
                    break;
                case '-':
                    left = 1;
                    break;
                case '0':
                    showLeading0s = 1;
                    break;
                default:
                    goto end_flags;
                }
            }
end_flags:
            /* field width */
            while (c >= '0' && c <= '9') {
                width = width * 10 + (c - '0');
                c = *fmt++;
            }
        
            /* length modifier */
            length = 0;
            while (c == 'l') {
                ++length;
                c = *fmt++;
            }

            /* process format */
            switch (c) {
            case 'c':
                c = (char) va_arg(ap, int);
                if (width > 1 && !left) {
                    PAD(&ctx, width-1, ' ');
                }   
                __writec(&ctx, c);
                if (width > 1 && left) {
                    PAD(&ctx, width-1, ' ');
                }   
                break;

            case 's':
                str = va_arg(ap, char *);
                if (!str) {
                    str = "(null)";
                }
string:
                len = strnlen(str, 1024);
                if (width > len && !left) {
                    PAD(&ctx, width-len, ' ');
                }   
                __writes(&ctx, str);
                if (width > len && left) {
                    PAD(&ctx, width-len, ' ');
                }   
                break;

            case 'p':
            case 'x':
            case 'X':
                value = va_arg(ap, unsigned int);
                if (length == 2) {
                    value2 = va_arg(ap, unsigned int);
                }

                if (c == 'p') {
                    if (value) {
                        c = 'x';
                        alternate = 1;
                    } else {
                        str = "(nil)";
                        goto string;
                    }
                }

                if (c == 'x') {
                    base = 'a'-10;
                } else {
                    base = 'A'-10;
                }

                ptr = scratch;

                leading0 = 1;
                for (count = length == 2 ? 60 : 28; count >= 0; count -= 4) {
                    unsigned char b;
                    if (count > 28) {
                        b = (value2 >> (count-32)) & 0xf;
                    } else {
                        b = (value >> count) & 0xf;
                    }

                    if (!b && leading0) {
                        continue;
                    } else {
                        leading0 = 0;
                        *ptr++ = b < 10 ? '0' + b : base + b;
                    }
                }

                if (leading0) {
                    *ptr++ = '0';
                }
                *ptr = 0;
                len = strnlen(scratch, sizeof(scratch));
                if (value && alternate) len+=2;
                if (width > len && !left) {
                    if (showLeading0s) {
                        if (value && alternate) {
                            PAD(&ctx, 1, '0');
                            PAD(&ctx, 1, c);
                        }
                        PAD(&ctx, width-len, '0');
                    } else {
                        PAD(&ctx, width-len, ' ');
                        if (value && alternate) {
                            PAD(&ctx, 1, '0');
                            PAD(&ctx, 1, c);
                        }
                    }
                } else if (value && alternate) {
                    PAD(&ctx, 1, '0');
                    PAD(&ctx, 1, c);
                } 
                __writes(&ctx, scratch);
                if (width > len && left) {
                    PAD(&ctx, width-len, ' ');
                }
                break;

            case 'u':
            case 'd':
                svalue = va_arg(ap, int);

                ptr = scratch + sizeof(scratch);
                neg = 0;

                if (svalue < 0) {
                    neg = 1;
                    svalue = -svalue;   
                }

                *--ptr = '\0';
                do {
                    *--ptr = '0' + (svalue % 10);
                } while ((svalue /= 10) != 0);

                if (neg) {
                    t = '-';
                } else if (sign) {
                    t = '+';
                } else {
                    t = 0;
                }

                len = strnlen(ptr, sizeof(scratch));
                if (t) ++len;
                if (width > len && !left) {
                    if (showLeading0s) {
                        if (t) {
                            PAD(&ctx, 1, t);
                        }
                        PAD(&ctx, width-len, '0');
                    } else {
                        PAD(&ctx, width-len, ' ');
                        if (t) {
                            PAD(&ctx, 1, t);
                        }
                    }
                } else if (t) {
                    PAD(&ctx, 1, t);
                }  
                __writes(&ctx, ptr);
                if (width > len && left) {
                    PAD(&ctx, width-len, ' ');
                }
                break;

            case '%':
            default:
                __writec(&ctx, c);
                break;
            }
        } else {
            __writec(&ctx, c);
        }
    }

    __writes(&ctx, "");

    return (0);
}

int
printf(const char *fmt, ...)
{
    va_list ap;
    int rv;

    va_start(ap, fmt);
    rv = vprintf(fmt, ap);
    va_end(ap);

    return rv;
}


