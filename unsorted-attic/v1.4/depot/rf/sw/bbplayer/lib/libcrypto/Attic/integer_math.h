d1 74
a74 66
/* 
 * integer_math.h
 * declarations for integer math routines needed for the 
 * ECDSA algorithm. implemented using the array of half words big 
 * integer notation
 * 
 */

#ifndef INTEGER_MATH_H
#define INTEGER_MATH_H


#include "binary_field.h"

#define HALF_SIZE  (WORD_SIZE/2)
#define HI_MASK (-1L << HALF_SIZE)
#define LO_MASK (~HI_MASK)
#define CARRY (1L << HALF_SIZE)
#define MSB_HW (CARRY >> 1)
#define INT_MAX (4* MAX_LONG -1)
#define MAX_STRING (MAX_LONG * WORD_SIZE/3)


#define NULL 0

/* element is unsigned long in binary_field.h
 * always make sure size of this (unsigned long)=WORD_SIZE/8
 * allocate for 2 half words, and two of those to accomodate 
 * results of multiplication 
 */
typedef struct {
	element half_word[4* MAX_LONG];
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
BSL_error bigint_null(bigint *a);
BSL_error bigint_copy(bigint *a, bigint *b);
BSL_error field_to_bigint();
BSL_error bigint_to_field();
BSL_error bigint_neg(bigint *a);
BSL_error bigint_add(bigint *a, bigint *b, bigint *c);
BSL_error bigint_sub(bigint *a, bigint *b, bigint *c);
BSL_error bigint_mul(bigint *a, bigint *b, bigint *c);
BSL_error bigint_div(bigint *num, bigint *den, bigint *quotient, bigint *remainder);
BSL_error ascii_to_bigint(char *instring, bigint *outhex);
BSL_error bigint_to_ascii(bigint *inhex, char *outstring);
BSL_error bigint_mod_inv(bigint *a, bigint *b, bigint *x);
BSL_error bigint_div2();
BSL_error mod_exp(bigint *x, bigint *n, bigint *q, bigint *z);

#endif /* for ifndef integer_math_h*/

