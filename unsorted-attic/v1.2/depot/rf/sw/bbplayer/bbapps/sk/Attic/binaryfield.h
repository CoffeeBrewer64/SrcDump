/* definitions for binary arithmetic: characteristic two,
vector length n: field2n.*/

#ifndef BINARYFIELD_H
#define BINARYFIELD_H
#define NUM_BITS 233 /* polynomial arithmetic is done using this 
number of bits. Make sure the irreducible polynomial has this
degree */
#define WORD_SIZE (sizeof(int) *8) /* number of bits in machine
word: make sure this is right */


#define NUM_WORD (NUM_BITS/WORD_SIZE) /* to index into
polynomial array */
#define UPR_SHIFT (NUM_BITS % WORD_SIZE) /* number of shifts
needed to get to MSB of zero offset of polynomial coeff list */

#define MAX_LONG (NUM_WORD + 1) /* number of machine words to 
hold polynomial */
#define MAX_BITS (MAX_LONG *WORD_SIZE) 
#define MAX_SHIFT (WORD_SIZE -1)

#define MSB (1L << MAX_SHIFT) /* mask for most 
significant bit */

#define UPR_BIT  (1L << (UPR_SHIFT -1))
#define UPR_MASK (~ (-1L << UPR_SHIFT))

typedef unsigned long element; /* single word*/

/* the binary field representation */
typedef struct {
	element e[MAX_LONG];
} field_2n;

field_2n poly_prime = {0x00080000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000400, 0x00000000, 0x00000001};  
/*233 bit u^233 + u^74 + 1*/
#endif BINARYFIELD_H
