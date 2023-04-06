d29 1
a29 1
static char __alarmStack[NET_ALARM_STACK_SIZE] __attribute__((aligned(32)));
d65 3
a67 1
        sizeof(__alarmStack), NET_ALARM_PRIORITY, IOS_THREAD_CREATE_DETACHED);
d85 2
a86 1
	alarm->fire     = OSTicksToMilliseconds(tick);
