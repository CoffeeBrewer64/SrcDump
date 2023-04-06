d12 14
a25 1
/* USB HIDBP mouse driver */
a32 3
#include <stdio.h>   /* for printf */
#include <stdlib.h>  /* for getenv */
#include <string.h>  /* for memcpy */
d45 1
d67 1
a67 1
  u32 *progStack = (void *) IOS_Alloc(STACK_SIZE/4096);
