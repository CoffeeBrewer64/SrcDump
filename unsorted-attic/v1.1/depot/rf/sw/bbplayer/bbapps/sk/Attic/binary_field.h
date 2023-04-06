d11 1
d21 1
a21 1
#define NUM_BITS 93
a59 38

/* 
polynomial related for holding result of multiply
*/

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
/*
field_2n poly_prime = {0x00080000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000400, 0x00000000, 0x00000001};  
*/
/*233 bit u^233 + u^74 + 1*/
/*
field_2n poly_prime;

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
field_2n poly_prime = {0x20000000, 0x00000000, 0x00000005};
