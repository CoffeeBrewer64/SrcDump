#include <PR/bcp.h>
#include <PR/bbsim.h>

#define NIBBLE_TO_ASCII(v) ((v)<10?('0'+(v)):('a'+(v)-10))

#ifdef LOG_MEM 

#define LOG_START_ADDR 0xa0200000
#define LOG_LENGTH     0x00010000
static u8 *pLogOut = (u8 *)LOG_START_ADDR;
#define DEBUG_OUT_CHAR(c)  \
       if( (u32)(pLogOut-LOG_START_ADDR) < (u32)LOG_LENGTH ) *(pLogOut++)=(c)

#else

#define BACKDOOR_PRINT		0x046fffe0
#define DEBUG_OUT_CHAR(c)  \
        IDE_WRITE(BACKDOOR_PRINT, (c))

#endif

void message(const char* s) {
    while(*s) {
        DEBUG_OUT_CHAR(*(s++));
    }
}

void output_int32_hex(u32 val)
{
    DEBUG_OUT_CHAR('0');
    DEBUG_OUT_CHAR('x');
    DEBUG_OUT_CHAR(NIBBLE_TO_ASCII((val>>28)&0xf));
    DEBUG_OUT_CHAR(NIBBLE_TO_ASCII((val>>24)&0xf));
    DEBUG_OUT_CHAR(NIBBLE_TO_ASCII((val>>20)&0xf));
    DEBUG_OUT_CHAR(NIBBLE_TO_ASCII((val>>16)&0xf));
    DEBUG_OUT_CHAR(NIBBLE_TO_ASCII((val>>12)&0xf));
    DEBUG_OUT_CHAR(NIBBLE_TO_ASCII((val>>8)&0xf));
    DEBUG_OUT_CHAR(NIBBLE_TO_ASCII((val>>4)&0xf));
    DEBUG_OUT_CHAR(NIBBLE_TO_ASCII((val>>0)&0xf));
}

