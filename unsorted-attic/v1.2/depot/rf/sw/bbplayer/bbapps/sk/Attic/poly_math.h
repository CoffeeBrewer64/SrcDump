d1 64
a64 19
/* declarations for polynomial math. This is not a comprehensive 
library, it defines the minimum required set for ECDSA and 
EC-DH. */

#ifndef POLY_MATH_H
#define POLY_MATH_H

#define DOUBLE_BITS 2*NUM_BITS /* again that is degree of 
primitive polynomial times two */
#define DOUBLE_WORD (DOUBLE_BITS / WORD_SIZE)
#define DOUBLE_SHIFT (DOUBLE_BITS % WORD_SIZE)
#define MAX_DOUBLE (DOUBLE_WORD + 1)

/* structure for convenience in FG 2^m arithmetic operations */
typedef struct {
	element e[MAX_DOUBLE];
} field_double;

#endif
