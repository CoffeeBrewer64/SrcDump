#include <PR/bcp.h>
#include <PR/bbsim.h>
#include <PR/bbskapi.h>

#define BACKDOOR_PRINT          0x046fffe0
void message(const char* s) 
{
    while(*s) {
        IDE_WRITE(BACKDOOR_PRINT, *s);
        s++;
    }
}

#define NIBBLE_TO_ASCII(val) ((val)<10?('0'+(val)):('a'+(val)-10))

void output_int32_hex(u32 val)
{
    IDE_WRITE(BACKDOOR_PRINT, '0');
    IDE_WRITE(BACKDOOR_PRINT, 'x');
    IDE_WRITE(BACKDOOR_PRINT, NIBBLE_TO_ASCII((val>>28)&0xf));
    IDE_WRITE(BACKDOOR_PRINT, NIBBLE_TO_ASCII((val>>24)&0xf));
    IDE_WRITE(BACKDOOR_PRINT, NIBBLE_TO_ASCII((val>>20)&0xf));
    IDE_WRITE(BACKDOOR_PRINT, NIBBLE_TO_ASCII((val>>16)&0xf));
    IDE_WRITE(BACKDOOR_PRINT, NIBBLE_TO_ASCII((val>>12)&0xf));
    IDE_WRITE(BACKDOOR_PRINT, NIBBLE_TO_ASCII((val>>8)&0xf));
    IDE_WRITE(BACKDOOR_PRINT, NIBBLE_TO_ASCII((val>>4)&0xf));
    IDE_WRITE(BACKDOOR_PRINT, NIBBLE_TO_ASCII((val>>0)&0xf));
}


boot()
{
    u32 val;
    char outstr[32];
#if 0
    /* reset IDE */
    val = IO_READ(PI_IDE_CONFIG_REG);
    val &= ~PI_IDE_CONFIG_RESET;
    IO_WRITE(PI_IDE_CONFIG_REG,val);
#endif
    message("sk_entry1,1\n");
    val = skTest1(14,4);
    /* cause writeback of line used in SK */
    *(u32 *)0x80000c40 = 10;
    message("   return value = ");
    output_int32_hex((u32)val);
    message("\n");

#if 0
    message("calling sk_entry2\n");
    val = skTest2(3,3);
    message("   return value = ");
    output_int32_hex((u32)val);
    message("\n");
#endif
#if 0
    message("sk_entry1,2\n");
    val = skTest1(20,4);
    message("   return value = ");
    output_int32_hex((u32)val);
    message("\n");

    asm("j __timer_test");
#endif

    while(1){}
}
