/* 
 * binary_field.h
 * definitions for binary arithmetic: characteristic two,
 * vector length n: field2n.
 * number of bits for field fixed here
 */

#ifndef BINARY_FIELD_H
#define BINARY_FIELD_H


/* 
 * polynomial arithmetic is done using this 
 * number of bits. Make sure the irreducible polynomial has this
 * degree 
 */
/*change later to 233 */

#define NUM_BITS 233 
/*
#define NUM_BITS 111
*/
/* number of bits in machine
 * word: make sure this is right = 32 bits = sizeof (element) 
 * later
 */
#define WORD_SIZE (sizeof(int) *8) 

/* to determine size of array of big int structure
 */
#define NUM_WORD (NUM_BITS/WORD_SIZE) 

/* number of shifts needed to get to MSB of zero 
 * offset of polynomial coeff list 
 */
#define UPR_SHIFT (NUM_BITS % WORD_SIZE) 

/* number of machine words to 
 * hold polynomial or large int 
 */
#define MAX_LONG (NUM_WORD + 1) 

#define MAX_BITS (MAX_LONG *WORD_SIZE) 

#define MAX_SHIFT (WORD_SIZE -1)

/* mask for most significant bit */
#define MSB (1L << MAX_SHIFT) 

#define UPR_BIT  (1L << (UPR_SHIFT -1))
#define UPR_MASK (~ (-1L << UPR_SHIFT))

typedef unsigned long element; /* single word*/

/* the binary field representation */
typedef struct {
	element e[MAX_LONG];
} field_2n;


#endif /* for ifndef binary_field_h */

