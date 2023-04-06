d1 1
a1 1
#ident "$Id: dvd_hw_reg.i,v 1.9 2006/03/02 06:09:54 craig Exp $"
d31 1
d197 2
a198 2
        printf (
        "Error: wrote value 0x%x to register addr %x, but value is %x\n",
d200 1
a200 1
        diFatalError("DI register write failed");
