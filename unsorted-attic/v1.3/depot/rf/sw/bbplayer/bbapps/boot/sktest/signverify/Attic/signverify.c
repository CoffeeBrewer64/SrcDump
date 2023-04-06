#include <PR/bcp.h>
#include <PR/R4300.h>
#include <PR/bbsim.h>
#include <PR/bbskapi.h>

#include <PR/os.h>
#include <PR/os_bbfs.h>
#include <PR/os_bbatb.h>

#include "../../sysapp/lib/common.h"
#include "../../sysapp/lib/cert.h"
#include "../../sysapp/lib/rl.h"



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
    BbSignedDataDesc desc;
    int i;
    char input_data[1024];
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

    for(i = 0; i < 1024; i++){
        input_data[i] = i & 0x000000ff;
    }
    message("input array\n");
    desc.data = &input_data[0];
    message("data pointer set\n");
    desc.datasize = 1024;
    message("data size set\n");

    message("signing...\n");
    *(u32 *)0xa0200004 = 0xf0f0f0f0;
    if(skSignStateBlob(&desc, 0x00000000) != SK_API_SUCCESS){
        message("signing failed!!!\n");
        *(u32 *)0xa0200004 = 0xffffffff;
    }
    message("signed\n");

    desc.sigType = BB_SIG_TYPE_ECC;
    *(u32 *)0xa0200008 = 0xf0f0f0f0;
    if(skVerifyStateBlob(&desc, 0x00000000) != SK_API_SUCCESS){
        message("verify failed!!!\n");
        *(u32 *)0xa0200008 = 0xffffffff;
    }
    message("verified\n");
    
#if 0
    message("calling sk_entry2\n");
    val = skTest2(3,3);
    message("   return value = ");
    output_int32_hex((u32)val);
    message("\n");

    message("sk_entry1,2\n");
    val = skTest1(20,4);
    message("   return value = ");
    output_int32_hex((u32)val);
    message("\n");
#endif
    asm("j __timer_test");

    while(1){}
}
