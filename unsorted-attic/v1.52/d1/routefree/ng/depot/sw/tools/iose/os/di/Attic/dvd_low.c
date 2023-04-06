d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.51 2006/03/10 23:45:53 craig Exp $"
d466 4
d473 4
a968 2
	printf ("(b4 receive) IOP DI Kernel interrupt enabled: %d\n",
                 IOPDiIntrEnabled());
a972 2
	printf ("(after receive) IOP DI Kernel interrupt enabled: %d\n",
                 IOPDiIntrEnabled());
d1039 1
a1039 1
                disableErrorIntr();
