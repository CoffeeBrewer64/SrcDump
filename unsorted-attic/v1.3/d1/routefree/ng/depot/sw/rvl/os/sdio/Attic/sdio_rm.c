d20 1
a20 1
#ident "$Id: sdio_rm.c,v 1.2 2006/03/15 01:10:15 gbarnard Exp $"
d393 1
a393 1
u8				heapArea[16 * 1024] __attribute__((aligned(32)));
d450 1
a450 1
		u32 pri = 20; //IOS_GetThreadPriority(0)+1;
