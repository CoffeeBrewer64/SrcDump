#include <nglibc.h>
#ifndef __SK_EMULATOR__
#include <stdarg.h>
#define PUTC(c) putc(c, stdout)

static void
_putsring(const char *s)
{
    while (*s) {
        PUTC(*s);
        ++s;
    }
}

int
putchar(int c)
{
    PUTC(c);
    return (unsigned char)c;
}

int
puts(const char *s)
{
    _putsring(s);
    PUTC('\n');
    return 0;
}

void putx(unsigned int v, int upper) {
    int i;
    static char s[] = "0123456789abcdef";
    static char S[] = "0123456789ABCDEF";
    char *p = upper ? S : s;
    int leading0 = 1;
    for (i = 28; i >= 0; i-=4) {
        unsigned char b = (v >> i) & 0xf;
        if (!b && leading0) continue;
        leading0 = 0;
        PUTC(p[b]);
    }
    if (leading0) PUTC('0');
}

void puti(int d)
{
    char t[16];
    char *p = t + 16;
    int neg = 0;
    if (d < 0) {
       neg = 1;
       d = -d;
    }
    *--p = 0;
    do {
        *--p = '0' + d % 10;
    }while ((d /= 10) != 0);
    if (neg) *--p = '-';
    _putsring(p);
}

int
printf(const char *fmt, ...)
{
    char c;
    va_list ap;
    char *s;
    unsigned int x;

    va_start(ap, fmt);
    while ((c = *fmt++)) {
        if (c == '%') {
            switch ((c = *fmt++)) {
            case 'c':
                c = (char) va_arg(ap, int);
                PUTC(c);
                break;
            case 's':
                s = va_arg(ap, char *);               
                _putsring(s);
                break;
            case 'x':
                x = va_arg(ap, unsigned int);               
                putx(x, 0);
                break;
            case 'X':
                x = va_arg(ap, unsigned int);               
                putx(x, 1);
                break;
            case 'd':
                x = va_arg(ap, unsigned int);               
                puti(x);
                break;
            case '%':
            default:
                PUTC(c);
                break;
            }
        } else {
            PUTC(c);
        }
    }
    va_end(ap);
    return 0;
}

#endif /* ! __SK_EMULATOR__ */
