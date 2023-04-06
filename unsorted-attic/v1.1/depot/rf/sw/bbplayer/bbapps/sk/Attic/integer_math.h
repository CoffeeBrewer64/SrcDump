d1 7
a7 3
/* declarations for integer math routines needed for the 
ECDSA algorithm. This is not a comprehensive big integer 
library */
d13 1
a13 1
#include "binaryfield.h"
d23 6
d34 10
a43 4
typedef enum{BSL_OK, BSL_OVERFLOW, BSL_DIVIDE_BY_ZERO} BSL_error;
typedef enum{TRUE, FALSE}boolean;
/* allocate for 2 half words, and two of those to accomodate 
results of multiplication */
d46 2
a47 2
BSL_error bigint_null();
BSL_error bigint_copy();
d50 8
a57 8
BSL_error bigint_neg();
BSL_error bigint_add();
BSL_error bigint_sub();
BSL_error bigint_mul();
BSL_error bigint_div();
BSL_error ascii_to_bigint();
BSL_error bigint_to_ascii();
BSL_error bigint_mod_inv();
d59 1
d61 1
a61 1
#endif /* for the ifndef in the first line */
