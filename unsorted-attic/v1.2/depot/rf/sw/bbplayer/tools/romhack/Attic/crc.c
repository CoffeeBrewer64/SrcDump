#include "romhack.h"

#define DO1(buf) crc = crc_table[((int)crc ^ (*buf++)) & 0xff] ^ (crc >> 8);
#define DO2(buf)  DO1(buf); DO1(buf);
#define DO4(buf)  DO2(buf); DO2(buf);
#define DO8(buf)  DO4(buf); DO4(buf);

u32 crc_table[256];
void make_crc_table()
{
    u32 c;
    int n, k;
    u32 poly;            /* polynomial exclusive-or pattern */
    /* terms of polynomial defining this crc (except x^32): */
    static u8 p[] = {0,1,2,4,5,7,8,10,11,12,16,22,23,26};
        
    /* make exclusive-or pattern from polynomial (0xedb88320L) */
    poly = 0L;
    for (n = 0; n < sizeof(p)/sizeof(u8); n++)
        poly |= 1L << (31 - p[n]);
        
    for (n = 0; n < 256; n++) {
        c = (u32)n;
        for (k = 0; k < 8; k++)
            c = c & 1 ? poly ^ (c >> 1) : c >> 1;
        crc_table[n] = c;
    }
}


u32 crc32(u32 crc, u8* buf, u32 len)
{
    crc = crc ^ 0xffffffffL;

    while (len >= 8) {
        DO8(buf);
        len -= 8;
    }

    if (len) do {
        DO1(buf);
    } while (--len);

    return crc ^ 0xffffffffL;
}
