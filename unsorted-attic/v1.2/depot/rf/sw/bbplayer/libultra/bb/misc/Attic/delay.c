#include <os.h>
#include <bbint.h>

void
__osBbDelay(u32 usec) {
    u32 count;
    u32 endCount;

    count = osGetCount();
    endCount = count + OS_USEC_TO_CYCLES(usec);
    
    /* 
     * Let count wrap if it needs to
     */
    while (endCount < count) {
        count = osGetCount();
    }
    do {
        count = osGetCount();
    } while (count < endCount);

}

