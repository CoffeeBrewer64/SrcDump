d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.20 2006/02/07 19:26:48 craig Exp $"
d32 1
a41 3
uint32_t        doRvlRead(uint8_t *dest_addr, uint32_t byteLength,
                          uint32_t virtWordOffset);

a45 1
extern void             resetDriverState(void);
d305 8
d389 1
d697 7
d711 7
a717 1
 * 
d722 1
a722 1
doDiskRead(uint8_t* const destAddr, const uint32_t length,
d728 3
a730 1
    printf ("doDiskRead: Reading %u bytes from address %u\n",
d739 1
a739 1
} // doDiskRead
