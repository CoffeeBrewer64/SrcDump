d10 1
a10 1
 * $Id: sd_app.c,v 1.1 2006/06/02 18:05:12 jprincen Exp $
d48 1
a48 5
    u32 reg;

    reg = busRd32(GPIIOPOUT_REG);
    reg = (reg & ~GPIIO_PIO_ENABLE) | ((value & 0xff) << GPIIO_PIO_SHIFT);
    busWrt32(GPIIOPOUT_REG, reg);
d164 3
d213 4
