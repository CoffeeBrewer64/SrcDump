d1 1
a1 1
#ident "$Id: dvd_low_rvl.c,v 1.1 2006/03/31 20:00:04 craig Exp $"
a18 8
#ifdef RVL
#include "arm_stdint.h"
#include "stdbool.h"
#include "hw.h"
#include "ioslibc.h"
#include "endian_macros.h"
#include "es.h"            // WARNING! defines ntohl as nothing - even on X86!
#else  // ! RVL
a24 1
#endif // ifdef RVL
a98 1
// #define RVL_DEBUG   1
d113 1
d198 1
a198 1
    result = IOS_GenerateHash(&hashContext, hashArray, hashArrayLength,
d210 1
a210 1
    result = IOS_GenerateHash(&hashContext, NULL,
d361 1
a361 1
            IOS_GenerateHash(&hashContext, dataPtr,
d364 1
a364 1
            IOS_GenerateHash(&hashContext, NULL,
a517 15
#ifdef RVL
    if (eTicketServicesInited == false) {
        ESError         error;

        eTicketServicesInited = true;
        error = ES_InitLib();
        if (error < 0) {
            void printIOS_OpenError(const ESError error);

            printIOS_OpenError(error);
            ERR_DPRINT2("ES_InitLib returned %d\n", error);
            diFatalError("E-ticket services initialize failed\n");
        }
    }
#endif
