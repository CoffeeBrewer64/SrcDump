d24 26
a49 1
static OSMutex __mutex; // use this mutex to map Nintendo's disable/enable/restore interrupt
d57 1
d60 1
a60 1
    	OSPanic(__FUNCTION__, 1, "failed\n");
d65 1
a65 1
    	OSPanic(__FUNCTION__, 1, "failed\n");
d73 11
a83 1
    ++mutex->count;
d86 1
a86 1
    	OSPanic(__FUNCTION__, 1, "failed\n");
d88 5
d99 10
d110 1
a110 1
    if ((IOS_SendMessage(mutex->mqid, msg, 0)) <0 )
d112 8
a119 1
    	OSPanic(__FUNCTION__, 1, "failed\n");
d121 2
d128 14
a164 1

