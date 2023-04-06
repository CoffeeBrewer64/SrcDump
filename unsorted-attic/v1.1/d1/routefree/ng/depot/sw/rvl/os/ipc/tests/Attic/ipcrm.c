d14 1
a14 3

#include <stdio.h>
#include <string.h>
d34 2
a35 4
#define RM_LOG(...)
// printf("RM: " __VA_ARGS__)
#define RM_ERROR(msg, rv) 
// printf("RM: Error: %s failed: %d\n", msg, rv)
d281 2
a282 1
ipcRm(u32 arg)
