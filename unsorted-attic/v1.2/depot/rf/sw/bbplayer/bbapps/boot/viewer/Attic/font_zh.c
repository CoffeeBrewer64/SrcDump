#include "ultra64.h"

void gen_glyph(u8* font_map, u8* out_glyph, u8 b1, u8 b2)
{
    u8  gb_offset = 0xa1;
    u8  unit_len  = 94;
    u8  byte;
    u8 *ptr;
    int i, j;

    int idx = (b1 - gb_offset) * unit_len + (b2 - gb_offset);

    ptr = font_map + idx*32; 
    for (i=0; i<32; i++) {
	byte = ptr[i]; 
        for (j=0; j<8; j++) 
	    out_glyph[i*8+j] = (byte & (0x80>>j)) == 0 ? 0 : 0xff;
    }
}
