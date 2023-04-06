/* 
 * integer_math.c
 * implementations for integer math routines needed for the 
 * ECDSA algorithm. implemented using the array of half words big 
 * integer notation
 * 
 */


#include "integer_math_ecc.h"
#include "integer_math.h"
#include "binary_field.h"
#include "poly_math.h"


/*
 * BSL_error 
 * bigint_ecc_null()
 * Purpose : set to zero a bigint
 * input: pointer to allocated bigint
 * */

BSL_error 
bigint_ecc_null(bigint_ecc *a, int int_max)
{
    short int i;
    
    if(a == NULL){
        return BSL_NULL_POINTER;
    }
    for(i = int_max; i >= 0; i--){
        a->half_word[i] =0L;
    }
    return BSL_OK;
}


/* 
 * BSL_error 
 * bigint_ecc_copy() 
 * Purpose: to copy one big integer to another: copy a into b
 * inputs: pointer to allocated bigint a and bigint b
 */

BSL_error 
bigint_ecc_copy(bigint_ecc *a, bigint_ecc *b, int int_max)
{
    short int i;
    if((a == NULL) || (b == NULL)){
        return BSL_NULL_POINTER;
    }
    for(i = int_max; i >= 0; i--){
        b->half_word[i] = a->half_word[i];
    }
    return BSL_OK;
}


/* 
 * BSL_error 
 * bigint_ecc_add() 
 * Purpose: to add two big integers.  c = a + b
 * Restrictions: none: can add in place and over-write input 
 */

BSL_error 
bigint_ecc_add(bigint_ecc *a, bigint_ecc *b, bigint_ecc *c, int int_max)
{
    short int i;
    element temp = 0;
    if((a == NULL) || (b == NULL) || (c == NULL)){
        return BSL_NULL_POINTER;
    }
    for(i = int_max; i >= 0; i--){
        temp = a->half_word[i] + b->half_word[i] + (temp >> HALF_SIZE);
        c->half_word[i] = temp & LO_MASK;
    }
    return BSL_OK;
}

/* 
 * BSL_error 
 * bigint_ecc_neg(a)  
 * Purpose: negate in place. a= -a
 * inputs: allocated bigint a
*/

BSL_error 
bigint_ecc_neg(bigint_ecc *a, int int_max)
{
    short int i;
    if (a == NULL){
        return BSL_NULL_POINTER;
    }
    for(i = int_max; i >= 0; i--){
        a->half_word[i] = ~a->half_word[i] & LO_MASK;
    }
    for(i = int_max; i >= 0; i--){
        a->half_word[i]++;
        /* if the addition resulted in all zeroes, proceed,
         * to propogate carry, otherwise, all done
         */
        if(a->half_word[i] & LO_MASK) break;
        a->half_word[i] &= LO_MASK;
    }
    return BSL_OK;
}

/* 
 * BSL_error 
 * bigint_ecc_sub(a,b,c) 
 * Purpose: to perform  a-b = c
 * inputs: allocated bignums a,b
*/
BSL_error 
bigint_ecc_sub(bigint_ecc *a, bigint_ecc *b, bigint_ecc *c, int int_max)
{
    bigint_ecc minusb;
    if((a == NULL) || (b == NULL) || (c == NULL)){
        return BSL_NULL_POINTER;
    }
    bigint_ecc_copy(b, &minusb, int_max);
    bigint_ecc_neg(&minusb, int_max);
    bigint_ecc_add(a, &minusb, c, int_max);
    return BSL_OK;
}


BSL_error
bigint_ecc_mul( bigint_ecc *a, bigint_ecc *b, bigint_ecc *c, int int_max)
{
	element 		ea, eb, mul;
	short int 	i, j, k;
	bigint_ecc	sum;
	bigint_ecc_null(c, 4*MAX_LONG_ECC-1);
        bigint_ecc_null(&sum, 4*MAX_LONG_ECC-1);
 	
 	
	for ( i = int_max; i > int_max/2; i--)
	{
		ea = a->half_word[i];
		bigint_ecc_null( &sum, int_max);
		for ( j = int_max; j > int_max/2; j--)
		{
			eb = b->half_word[j];
			k = i + j - int_max;
			mul = ea * eb + sum.half_word[k];
			sum.half_word[k] = mul & LO_MASK;
			sum.half_word[k-1] = mul >> HALF_SIZE;
		}
		bigint_ecc_add( &sum, c, c, int_max);
	}
        return BSL_OK;
}


/* 
 * BSL_error 
 * bigint_ecc_div() 
 * Purpose: unsigned divide two big integers.  quotient = num/den
 * remainder = top % bottom
 * RESTRICTIONS: cannot over-write inputs
 * RESTRICTIONS: top is full size, bottom is half size, quot half size
 * Will return zero if top is zero and divide_by_zero if bottom is zero
 */

BSL_error 
bigint_ecc_div(bigint_ecc *num, bigint_ecc *den, bigint_ecc *quotient, bigint_ecc *remainder, int int_max)
{
    /*check for divide by zero */
    bigint_ecc d,e;
    element mask;
    short int l,m,n,i,j;
    boolean iszero = BSL_TRUE;
    bigint_ecc_null(quotient, 4*MAX_LONG_ECC -1);
    bigint_ecc_null(remainder, 4*MAX_LONG_ECC-1);


    /* check all pointers */
    if ((num ==0) ||(den ==0)|| (quotient ==0 )||(remainder ==0)){
        return BSL_NULL_POINTER;
    }
    
    for(i=int_max; i>= int_max/2; i--){
        if(den->half_word[i] != 0){
            iszero = BSL_FALSE;
        }
    }
    if(iszero == BSL_TRUE){
        return BSL_DIVIDE_BY_ZERO;
    }

    /* denominator is ok 
     * set counters to msb in numerator and denominator 
     */
    bigint_ecc_copy(num, &d, int_max);
    bigint_ecc_copy(den, &e, int_max);

    l = (int_max + 1) * HALF_SIZE;
    for(i = 0; i <= int_max; i++){
        if(!d.half_word[i]) l -= HALF_SIZE;
        else break;
    }
    mask = 1L << (HALF_SIZE - 1);
    for( j=0; j < HALF_SIZE; j++){
        if(!(d.half_word[i] & mask)){
            l--;
            mask >>= 1;
        }
        else break;
    }

    /*repeat for denominator*/
    m = (int_max + 1) * HALF_SIZE;
    for(i = 0; i <= int_max; i++){
        if(!e.half_word[i]) m -= HALF_SIZE;
		else break;
    } 
    mask = 1L << (HALF_SIZE -1);
    for(j=0; j < HALF_SIZE; j++){
        if(!(e.half_word[i] & mask)){
            m--;
            mask >>= 1;
        }
        else break;
    }

    /*check for error , is it divide by one?*/
    if (!m){
        bigint_ecc_copy(num, quotient, int_max);
        bigint_ecc_null(remainder, int_max);
        return BSL_OK;
    }

    /* if denominator is greater, set quotient 
     * zero, return remainder 
     */

    if(!l | (l<m)){
        bigint_ecc_null(quotient, int_max);
        bigint_ecc_copy(num, remainder, int_max);
        return BSL_OK;
    }

    /* shift to align before subtracting */
    n = l - m ;
    i = n;
    while(i > HALF_SIZE){
        for(j = 0; j < int_max; j++){
            e.half_word[j] = e.half_word[j+1];
        }
        i -= HALF_SIZE;
        e.half_word[int_max] = 0;
    }
    mask = 0;
    while(i > 0){
        for(j = int_max; j >= 0; j--){
            e.half_word[j] = (e.half_word[j] << 1) | mask;
            mask = e.half_word[j] & CARRY ? 1 :0;
            e.half_word[j] &= LO_MASK;
        }
        i--;
    }

    bigint_ecc_null(quotient, int_max);

    while(n >= 0){
        i = int_max - l/HALF_SIZE;
        j = int_max - n/HALF_SIZE;
        while((d.half_word[i] == e.half_word[i]) &&(i < int_max)) i++;
        if(d.half_word[i] >= e.half_word[i]){
            bigint_ecc_sub(&d, &e, &d, int_max);
            mask = 1L << (n % HALF_SIZE);
            quotient->half_word[j] |= mask;
        }
        for(j= int_max; j >=0; j--){
            if(j) mask = (e.half_word[j-1] & 1)? CARRY :0;
            else mask =0;
            e.half_word[j] = (e.half_word[j] | mask) >> 1;
        }
        n--;
        l--;
    }
    bigint_ecc_copy( &d, remainder, int_max);
    return BSL_OK;
}




/* 
 * BSL_error 
 * ascii_to_bigint() 
 * Purpose: to input ascii numbers into the bigint structure
 * RESTRICTIONS: use decimal input, doesnt check for >9.
 * the int_max refers to the bigint
 */


BSL_error 
ascii_to_bigint_ecc(char *instring, bigint_ecc *outhex, int int_max)
{
    element ch;
    bigint_ecc ten, digit, temp;
    if((instring == NULL) || (outhex == NULL)){
        return BSL_NULL_POINTER;
    }
    bigint_ecc_null(&ten, int_max);
    ten.half_word[int_max] = 0xA;
    bigint_ecc_null(&digit, int_max);
    bigint_ecc_null(outhex, int_max);

    while ( ch = *instring++){
        digit.half_word[int_max] = ch & 0xF;
        bigint_ecc_mul(outhex, &ten, &temp, int_max);
        if(digit.half_word[int_max] > 9) continue;
        bigint_ecc_add(&temp, &digit, outhex, int_max);
    }
    return BSL_OK;
}



/* 
 * BSL_error 
 * bigint_ecc_to_ascii() 
 * Purpose: to return ascii from a big int for debugging
 * RESTRICTIONS: outstring should be allocated to be size 
 * log2*4*HALF_SIZE*MAXLONG
 */


BSL_error 
bigint_ecc_to_ascii(bigint_ecc *inhex, char *outstring, int int_max, int size)
{
    bigint_ecc top, ten, quotient, remainder;
    element check;
    short int i;
    if((inhex == NULL) ||(outstring == NULL)){
        return BSL_NULL_POINTER;
    }
    bigint_ecc_copy(inhex, &top, int_max);
    /* create constant 10
     */
    bigint_ecc_null(&ten, int_max);
    ten.half_word[int_max] = 0xA;
    /*blank fill and null terminate
     */
    for(i = 0; i< size; i++){ 
        /* blank */
        *outstring++ = ' ';
    }
    outstring--;
    *outstring-- = 0;

    check = 1;
    while(check){
        bigint_ecc_div(&top, &ten, &quotient, &remainder, int_max);
        *outstring-- = remainder.half_word[int_max] | '0';
        check =0;
        for(i=int_max; i>=0; i--){
            check |= quotient.half_word[i];
        }
        bigint_ecc_copy(&quotient, &top, int_max);
    }
    return BSL_OK;
}



/* 
 * BSL_error 
 * bigint_ecc_div2() 
 * Purpose: to divide a bigint by 2
 */

BSL_error 
bigint_ecc_div2(bigint_ecc *x, int int_max)
{
	short int j;
	element mask;
        if(x == NULL){
            return BSL_NULL_POINTER;
        }
	for(j = int_max; j >= 0; j--){
            if (j) mask = (x->half_word[j-1] & 1 ) ? CARRY : 0;
            else mask =0;
            x->half_word[j] = (x->half_word[j]  | mask) >> 1;	
	}
	return BSL_OK;
}


/* 
 * BSL_error 
 * mod_inv()
 * this is a corollary of extended euclidean algorithm 
 * euclidean algorithm gives p,q where gcd(a,b) = a + qb.
 * for relative primes, gcd =1, so 1 = pa + qb. So p = inv(a) mod b.
 * To find x = inv(a) mod b where a and b are relatively prime
*/

BSL_error 
bigint_ecc_mod_inv(bigint_ecc *a, bigint_ecc *b, bigint_ecc *x, int int_max)
{
    bigint_ecc m, n, p0, p1, p2, q, r, temp, dummy;
    element check;
    short int sw, i;

    bigint_ecc_null(&m, 4* MAX_LONG_ECC-1);
    bigint_ecc_null(&n, 4*MAX_LONG_ECC-1);
    bigint_ecc_null(&p0, 4*MAX_LONG_ECC-1);
    bigint_ecc_null(&p1, 4*MAX_LONG_ECC-1);
    bigint_ecc_null(&p2, 4*MAX_LONG_ECC-1);
    bigint_ecc_null(&q, 4*MAX_LONG_ECC-1);
    bigint_ecc_null(&r, 4*MAX_LONG_ECC-1);
    bigint_ecc_null(&temp, 4*MAX_LONG_ECC-1);
    bigint_ecc_null(&dummy, 4*MAX_LONG_ECC-1);

    /* check errors */
    if((a == NULL) || (b == NULL) || (x == NULL)){
        return BSL_NULL_POINTER;
    }
    /*
     * initialize for extended euclidean
     * sw = 1;
     * m = b;
     * n = a;
     * p0 = 1;
     * p1 = m / n;
     * q = p1;
     * r = m % n; 
     */
	
    sw = 1;
    bigint_ecc_copy( b,  &m, int_max);
    bigint_ecc_copy( a,  &n, int_max);
    bigint_ecc_null(  &p0, int_max);
    p0.half_word[int_max] = 1;
    bigint_ecc_div(  &m,  &n,  &p1,  &r, int_max);
    bigint_ecc_copy( &p1,  &q, int_max);

    /*loop */
    check  =0;
    for(i=int_max; i>=0; i--){
        check |= r.half_word[i];
    }
    while(check){
        /* sw = -sw */
        sw = -sw;
        /* m = n */
        bigint_ecc_copy( &n,  &m, int_max);
        /* n = r */
        bigint_ecc_copy( &r,  &n, int_max);
        /* q = m/n, r = m % n */
        bigint_ecc_div( &m,  &n,  &q,  &r, int_max);
        /* p2 = q * p1 + p0 % b */
        bigint_ecc_mul( &q,  &p1,  &temp, int_max);
        bigint_ecc_add( &temp,  &p0,  &temp, int_max);
        bigint_ecc_div( &temp,  b,  &dummy,  &p2, int_max);
        /* p0 = p1 */
        bigint_ecc_copy( &p1,  &p0, int_max);
        /* p1 = p2 */
        bigint_ecc_copy( &p2,  &p1, int_max);
        check =0;
        for(i = int_max; i>=0; i--){
            check |= r.half_word[i];
        }
    }
    if(sw < 0) bigint_ecc_sub( b,  &p0,  x, int_max);
    else bigint_ecc_copy( &p0,   x, int_max);
    return BSL_OK;
}


BSL_error 
field_to_bigint_ecc(field_2n *a, bigint_ecc *b, int num_bits)
{
  short int i,j;
  int num_word = num_bits/WORD_SIZE;
  int max_long = num_word + 1;
  int int_max = (4 * max_long ) - 1;

  bigint_ecc_null(b, 4*MAX_LONG_ECC -1);

  for(i= num_word; i >=0; i--){
    j = int_max - ((num_word -i) <<1);
    b->half_word[j] = a->e[i] & LO_MASK;
    
    j--;
    b->half_word[j] = (a->e[i] & HI_MASK)>>HALF_SIZE;
    
  }
  return BSL_OK;
}



BSL_error bigint_ecc_to_field(bigint_ecc *a, field_2n *b, int num_bits){
    short int i,j;
    int num_word, max_long, int_max;
    num_word = num_bits/WORD_SIZE;
    max_long = num_word + 1;
    int_max = (4 * max_long ) - 1;
    null(b);
    for(i= 0; i < max_long; i++){
        j = (i + max_long)<<1;
        b->e[i] = a->half_word[j+1] | (a->half_word[j] << HALF_SIZE);
    }
    return BSL_OK;
}

