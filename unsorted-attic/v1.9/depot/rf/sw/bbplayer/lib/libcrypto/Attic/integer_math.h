/* 
 * integer_math.h
 * declarations for integer math routines needed for the 
 * ECDSA algorithm. implemented using the array of half words big 
 * integer notation
 * 
 */

#ifndef INTEGER_MATH_RSA_H
#define INTEGER_MATH_RSA_H


#include "binary_field.h"

#define HALF_SIZE  (WORD_SIZE/2)
#define HI_MASK (-1L << HALF_SIZE)
#define LO_MASK (~HI_MASK)
#define CARRY (1L << HALF_SIZE)
#define MSB_HW (CARRY >> 1)
/*
#define INT_MAX (4* MAX_LONG -1)
#define MAX_STRING (MAX_LONG * WORD_SIZE/3)
*/

#define NULL 0

/* this is to avoid a malloc: this is MAX_LONG for 4096 bits
 */
#define MAX_MAX_LONG 129

/* element is unsigned long in binary_field.h
 * always make sure size of this (unsigned long)=WORD_SIZE/8
 * allocate for 2 half words, and two of those to accomodate 
 * results of multiplication 
 */
typedef struct {
	element half_word[4* MAX_MAX_LONG];
}bigint;

/*errors */
typedef enum { BSL_OK = 0, 
               BSL_OVERFLOW, 
               BSL_DIVIDE_BY_ZERO, 
               BSL_SHA_ERROR,
               BSL_BAD_KEY,
               BSL_NULL_POINTER
} BSL_error;
typedef enum { BSL_TRUE = 0, 
               BSL_FALSE
}boolean;


/* functions needed */

void random_field(field_2n *value, unsigned int seed);

BSL_error bigint_null(bigint *a, int int_max);
BSL_error bigint_copy(bigint *a, bigint *b, int int_max);

BSL_error field_to_bigint(field_2n *a, bigint *b, int num_bits);
BSL_error bigint_to_field(bigint *a, field_2n *b, int num_bits);

BSL_error bigint_neg(bigint *a, int int_max);
BSL_error bigint_add(bigint *a, bigint *b, bigint *c, int int_max);
BSL_error bigint_sub(bigint *a, bigint *b, bigint *c, int int_max);
BSL_error bigint_mul(bigint *a, bigint *b, bigint *c, int int_max);
BSL_error bigint_div(bigint *num, bigint *den, bigint *quotient, bigint *remainder, int int_max);
BSL_error ascii_to_bigint(char *instring, bigint *outhex, int int_max);
BSL_error bigint_to_ascii(bigint *inhex, char *outstring, int int_max, int size);
BSL_error bigint_mod_inv(bigint *a, bigint *b, bigint *x, int int_max);
BSL_error bigint_div2(bigint *x, int int_max);
BSL_error mod_exp(bigint *x, bigint *n, bigint *q, bigint *z, int int_max);
void charstring_to_bigint (bigint *a, unsigned char *b, unsigned int len, int int_max);
void bigint_to_charstring(unsigned char  *a, unsigned int len, bigint *b, int int_max);
void bigint_to_certint(unsigned long *certfmt, int certfmtwords, bigint *b, int int_max);
void certint_to_bigint( bigint *b, int int_max, unsigned long *certfmt, int certfmtwords);

/*
BSL_error bsl_rsa_verify(char *result, char * e_string, int e_size, char *n_string, int n_size, char *sign, int sign_size, int num_bits);
*/
BSL_error bsl_rsa_verify(char *result, unsigned long *certsign, unsigned long *certpublickey, unsigned long *exponent,  int num_bits);

#endif /* for ifndef integer_math_h*/

