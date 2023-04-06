a0 6
SECTIONS
{
    .text : AT(@@WFS_PHYS_START@@) {}
    .data : AT((LOADADDR(.text)+SIZEOF(.text)+4095)&0xfffff000) {}
    .bss : AT((LOADADDR(.data)+SIZEOF(.data)+0x00000fff)&0xfffff000) {}
}
