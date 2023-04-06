/* 
 * poly_math.h
 * definitions for binary arithmetic: characteristic two,
 * vector length n: field2n.
 * number of bits for field fixed here
 */


#ifndef POLY_MATH_H
#define POLY_MATH_H

#include "binary_field.h"
#define DOUBLE_BITS ( 2 * NUM_BITS)
#define DOUBLE_WORD (DOUBLE_BITS / WORD_SIZE)
#define DOUBLE_SHIFT (DOUBLE_BITS % WORD_SIZE)
#define MAX_DOUBLE (DOUBLE_WORD + 1)

/* structure for convenience in FG 2^m arithmetic operations */
typedef struct {
	element e[MAX_DOUBLE];
} field_double;

/* 
this is for NUMBITS 233 
*/
/* field_2n poly_prime = {0x00080000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000400, 0x00000000, 0x00000001};  
*/
/*233 bit u^233 + u^74 + 1*/
/* field_2n poly_prime;

poly_prime.e[0] = 0x00080000;
poly_prime.e[1] = 0x00000000;
poly_prime.e[2] = 0x00000000;
poly_prime.e[3] = 0x00000000;
poly_prime.e[4] = 0x00000000;
poly_prime.e[5] = 0x00000400;
poly_prime.e[6] = 0x00000000;
poly_prime.e[7] = 0x00000001; 
*/

/* this is for NUMBITS 93
 */
/* field_2n poly_prime = {0x20000000, 0x00000000, 0x00000005};
 */
/* NUMBITS 111 */

/*field_2n poly_prime = {0x00008000,0x00000000,0x00000000,0x00000401}; */
/* 
field_2n poly_prime;
poly_prime.e[0] = 0x00008000;
poly_prime.e[1] = 0x00000000;
poly_prime.e[2] = 0x00000000;
poly_prime.e[3] = 0x00000401;  
*/
/* function prototypes */
BSL_error multiply_shift(field_double *a);
BSL_error null(field_2n *a);
BSL_error double_add(field_double *a, field_double *b, field_double *c);
BSL_error double_swap(field_double *a, field_double *b);
BSL_error copy(field_2n *from, field_2n *to);
BSL_error double_copy(field_double *from, field_double *to);
BSL_error double_is_one(field_double *a, boolean *result);
BSL_error single_to_double(field_2n *from, field_double *to);
BSL_error double_to_single(field_double *from, field_2n *to);
BSL_error poly_mul_partial(field_2n *a, field_2n *b, field_double *c);
BSL_error poly_div_shift(field_double *a);
BSL_error poly_log2(element x, short int *result);
BSL_error poly_degree_of(element *t, short int dim, short int *result);
BSL_error poly_div(field_double *top, field_2n *bottom, field_2n *quotient, field_2n *remainder);
BSL_error poly_mul(field_2n *a, field_2n *b, field_2n *c);
BSL_error poly_inv(field_2n *a, field_2n *inverse);
BSL_error poly_rot_right(field_2n *a);
#endif
