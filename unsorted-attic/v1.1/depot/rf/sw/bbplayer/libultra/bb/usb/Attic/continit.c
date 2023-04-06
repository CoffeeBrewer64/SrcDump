d10 4
d15 4
a18 1
static char __osUsbMgrStacks[OS_USB_MGR_STACKSIZE * OS_USB_MAX_CONTROLLERS] __attribute__ ((aligned (8)));
d68 1
d81 1
a81 1
osUsbContInit(s32 ctlr, OSMesgQueue *mq)
d91 3
d95 5
a99 5
			3141+ctlr, 
			(void(*)(void *))__osUsbMgrProc,
			(void *)mq,
			(void *)&__osUsbMgrStacks[OS_USB_MGR_STACKSIZE * ctlr],
			16);
