#include <nglibc.h>

void *memcpy(void *dst, const void *src, size_t n);
void *memmove(void *dst, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

int test_strchr(void)
{
    char a[] = "hayNstack";

    /* find the same character */
    if (strchr(a, 'N') != (a+3)) return 1;
    if (strrchr(a, 'N') != (a+3)) return 2;
    /* find different instances of the same character */
    if (strchr(a, 'a') != (a+1)) return 3;
    if (strrchr(a, 'a') != (a+6)) return 4;
    /* find first/last characters */
    if (strchr(a, 'h') != (a)) return 5;
    if (strrchr(a, 'h') != (a)) return 6;
    if (strchr(a, 'k') != (a+8)) return 7;
    if (strrchr(a, 'k') != (a+8)) return 8;
    /* find non-existent character */
    if (strchr(a, 'z') != 0) return 9;
    if (strrchr(a, 'z') != 0) return 10;

    return 0;
}

int test_strnlen(void)
{
    char *a = "longstring";
  
    if (strnlen(a, 16) != 10) return 20;
    if (strnlen(a, 3) != 3) return 21;
    if (strnlen(a, 0) != 0) return 22;

    a = "";
    if (strnlen(a, 16) != 0) return 23;
    if (strnlen(a, 0) != 0) return 24;

    return 0;
}

int test_strncmp(void)
{
    char *a = "string1";
    char *b = "string2";

    if (strncmp(a, b, 0) != 0) return 30;
    if (strncmp(a, b, 3) != 0) return 31;
    if (strncmp(a, b, 6) != 0) return 32;
    if (strncmp(b, a, 0) != 0) return 33;
    if (strncmp(b, a, 3) != 0) return 34;
    if (strncmp(b, a, 6) != 0) return 35;

    if (strncmp(a, b, 7) >= 0) return 36;
    if (strncmp(a, b, 16) >= 0) return 37;
    if (strncmp(b, a, 7) < 0) return 38;
    if (strncmp(b, a, 16) < 0) return 39;

    b = "string1longer";
    if (strncmp(a, b, 16) >= 0) return 40;
    if (strncmp(b, a, 16) < 0) return 41;

    b = "";
    if (strncmp(a, b, 16) < 0) return 42;
    if (strncmp(b, a, 16) >= 0) return 43;

    return 0;
}

int test_strncpy(void)
{
    char o[] = "abc456";
    char d[] = "abc456";
    char s[] = "123def";
    char dlong[] = "This is a long string";
    char *t = "123456";
    char *tlong = "123defs a long string";

    if (strncmp(strncpy(d, s, 0), o, 16) != 0) return 50;
    if (strncmp(strncpy(d, s, 3), t, 16) != 0) return 51;
    if (strncmp(strncpy(d, s, 16), s, 16) != 0) return 52;
    if (strncmp(strncpy(dlong, s, 6), tlong, 32) != 0) return 53;
    if (strncmp(strncpy(dlong, s, 16), s, 32) != 0) return 54;

    return 0;
}

int test_memcmp(void)
{
    char *a = "string1";
    char *b = "string2";

    if (strncmp(a, b, 0) != 0) return 60;
    if (strncmp(a, b, 3) != 0) return 61;
    if (strncmp(a, b, 6) != 0) return 62;
    if (strncmp(b, a, 0) != 0) return 63;
    if (strncmp(b, a, 3) != 0) return 64;
    if (strncmp(b, a, 6) != 0) return 65;

    if (strncmp(a, b, 7) >= 0) return 66;
    if (strncmp(b, a, 7) < 0) return 67;

    return 0;
}

int test_memset(void)
{
    char *o = "abcdef";
    char *t = "XXcdef";
    char d[] = "abcdef";

    if (strncmp(memset(d, 'X', 0), o, 16) != 0) return 70;
    if (strncmp(memset(d, 'X', 2), t, 16) != 0) return 71;

    return 0;
}

int test_memcpy(void)
{
    char o[] = "abc456";
    char d[] = "abc456";
    char s[] = "123def";
    char *t = "123456";

    if (strncmp(memcpy(d, s, 0), o, 16) != 0) return 80;
    if (strncmp(memcpy(d, s, 3), t, 16) != 0) return 81;
    if (strncmp(memcpy(d, s, strnlen(s, 16)), s, 16) != 0) return 82;

    return 0;
}

int test_memmove(void)
{
    char o[] = "abc456";
    char d[] = "abc456";
    char s[] = "123def";
    char *t = "123456";
    char big[] = "bigdogrun";
    char *tbig = "bigbigdog";
    char *tbig2 = "igbbigdog";

    if (strncmp(memmove(d, s, 0), o, 16) != 0) return 90;
    if (strncmp(memmove(d, s, 3), t, 16) != 0) return 91;
    if (strncmp(memmove(d, s, strnlen(s, 16)), s, 16) != 0) return 92;
    if (strncmp(memmove(big+3, big, 6)-3, tbig, 16) != 0) return 93;
    if (strncmp(memmove(big, big+1, 3), tbig2, 16) != 0) return 94;

    return 0;
}

int main(void)
{
    int rv = 0;

    if ((rv = test_strchr())) goto end;
    if ((rv = test_strnlen())) goto end;
    if ((rv = test_strncmp())) goto end;
    if ((rv = test_strncpy())) goto end;

    if ((rv = test_memcmp())) goto end;
    if ((rv = test_memset())) goto end;
    if ((rv = test_memcpy())) goto end;
    if ((rv = test_memmove())) goto end;

end:
    return rv;
}
