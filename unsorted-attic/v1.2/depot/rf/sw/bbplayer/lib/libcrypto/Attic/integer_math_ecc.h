/* 
 * integer_math.h
 * declarations for integer math routines needed for the 
 * ECDSA algorithm. implemented using the array of half words big 
 * integer notation
 * 
 */

#ifndef INTEGER_MATH_ECC_H
#define INTEGER_MATH_ECC_H

#include "integer_math.h"
#include "binary_field.h"

#define HALF_SIZE  (WORD_SIZE/2)
#define HI_MASK (-1L << HALF_SIZE)
#define LO_MASK (~HI_MASK)
#define CARRY (1L << HALF_SIZE)
#define MSB_HW (CARRY >> 1)


#define NULL 0

/* this is to avoid a malloc: this is MAX_LONG for 4096 bits
 */


/* element is unsigned long in binary_field.h
 * always make sure size of this (unsigned long)=WORD_SIZE/8
 * allocate for 2 half words, and two of those to accomodate 
 * results of multiplication 
 */

#define MAX_LONG_ECC 8
typedef struct {
	element half_word[4* MAX_LONG_ECC];
}bigint_ecc;


/* functions needed */

void random_field(field_2n *value, unsigned int seed);

BSL_error bigint_ecc_null(bigint_ecc *a, int int_max);
BSL_error bigint_ecc_copy(bigint_ecc *a, bigint_ecc *b, int int_max);

BSL_error field_to_bigint_ecc(field_2n *a, bigint_ecc *b, int num_bits);
BSL_error bigint_ecc_to_field(bigint_ecc *a, field_2n *b, int num_bits);

BSL_error bigint_ecc_neg(bigint_ecc *a, int int_max);
BSL_error bigint_ecc_add(bigint_ecc *a, bigint_ecc *b, bigint_ecc *c, int int_max);
BSL_error bigint_ecc_sub(bigint_ecc *a, bigint_ecc *b, bigint_ecc *c, int int_max);
BSL_error bigint_ecc_mul(bigint_ecc *a, bigint_ecc *b, bigint_ecc *c, int int_max);
BSL_error bigint_ecc_div(bigint_ecc *num, bigint_ecc *den, bigint_ecc *quotient, bigint_ecc *remainder, int int_max);
BSL_error ascii_to_bigint_ecc(char *instring, bigint_ecc *outhex, int int_max);
BSL_error bigint_ecc_to_ascii(bigint_ecc *inhex, char *outstring, int int_max, int size);
BSL_error bigint_ecc_mod_inv(bigint_ecc *a, bigint_ecc *b, bigint_ecc *x, int int_max);
BSL_error bigint_ecc_div2(bigint_ecc *x, int int_max);

#endif /* for ifndef integer_math_h*/

