d1 1
a1 1
#ident "$Id: dvd_high_emu.c,v 1.4 2005/12/30 23:28:16 craig Exp $"
d36 2
d51 3
a53 1
    diskInfo.dataWordOffset = (96 * 1024) / 4;
d72 1
d76 3
a78 2
    interfaceDiCommand.arg[1] = 127;
    interfaceDiCommand.arg[2] = (32 * 1024) - 32;
d97 25
