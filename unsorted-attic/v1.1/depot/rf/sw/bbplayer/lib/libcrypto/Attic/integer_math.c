d1 574
a574 573
/* 
 * integer_math.c
 * implementations for integer math routines needed for the 
 * ECDSA algorithm. implemented using the array of half words big 
 * integer notation
 * 
 */


#include "integer_math.h"

/*
 * BSL_error 
 * bigint_null()
 * Purpose : set to zero a bigint
 * input: pointer to allocated bigint
 * */

BSL_error 
bigint_null(bigint *a)
{
    short int i;
    if(a == NULL){
        return BSL_NULL_POINTER;
    }
    for(i = INT_MAX; i >= 0; i--){
        a->half_word[i] =0L;
    }
    return BSL_OK;
}


/* 
 * BSL_error 
 * bigint_copy() 
 * Purpose: to copy one big integer to another: copy a into b
 * inputs: pointer to allocated bigint a and bigint b
 */

BSL_error 
bigint_copy(bigint *a, bigint *b)
{
    short int i;
    if((a == NULL) || (b == NULL)){
        return BSL_NULL_POINTER;
    }
    for(i = INT_MAX; i >= 0; i--){
        b->half_word[i] = a->half_word[i];
    }
    return BSL_OK;
}



/* 
 * BSL_error 
 * bigint_add() 
 * Purpose: to add two big integers.  c = a + b
 * Restrictions: none: can add in place and over-write input 
 */

BSL_error 
bigint_add(bigint *a, bigint *b, bigint *c)
{
    short int i;
    element temp = 0;
    if((a == NULL) || (b == NULL) || (c == NULL)){
        return BSL_NULL_POINTER;
    }
    for(i = INT_MAX; i >= 0; i--){
        temp = a->half_word[i] + b->half_word[i] + (temp >> HALF_SIZE);
        c->half_word[i] = temp & LO_MASK;
    }
    return BSL_OK;
}

/* 
 * BSL_error 
 * bigint_neg(a)  
 * Purpose: negate in place. a= -a
 * inputs: allocated bigint a
*/

BSL_error 
bigint_neg(bigint *a)
{
    short int i;
    if (a == NULL){
        return BSL_NULL_POINTER;
    }
    for(i = INT_MAX; i >= 0; i--){
        a->half_word[i] = ~a->half_word[i] & LO_MASK;
    }
    for(i = INT_MAX; i >= 0; i--){
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
 * bigint_sub(a,b,c) 
 * Purpose: to perform  a-b = c
 * inputs: allocated bignums a,b
*/
BSL_error 
bigint_sub(bigint *a, bigint *b, bigint *c)
{
    bigint minusb;
    if((a == NULL) || (b == NULL) || (c == NULL)){
        return BSL_NULL_POINTER;
    }
    bigint_copy(b, &minusb);
    bigint_neg(&minusb);
    bigint_add(a, &minusb, c);
    return BSL_OK;
}



/* 
 * BSL_error 
 * bigint_mul() 
 * Purpose: to multiply two big integers.  c = a * b
 * RESTRICTIONS: cannot over-write input: no a = a * b or b = a * b
 * RESTRICTIONS: cannot call twice in a row!!!!!!!!!!!!!!!!!!!!!!
 * RESTRICTIONS: because inputs are strictly half the size of output
 * RESTRICTIONS: you'd have to do a division in between
 * Will return overflow error if inputs are not 
 * right size (INT_MAX/2 to INT_MAX)
 */

BSL_error 
bigint_mul(bigint *a, bigint *b, bigint *c)
{
    element tempa, tempb, cumsum;
    short int i,j,k;
    bigint sum;
    bigint_null(c);
    /* check input sizes, the sizes should be half
     * check if any lower half bits are non zero 
     * lower half is more significant bits
     */
    
    for(i = 0; i <= INT_MAX/2; i++){
        if (a->half_word[i] & (HI_MASK | LO_MASK)){
            return BSL_OVERFLOW;
        }
        if (b->half_word[i] & (HI_MASK | LO_MASK)){
            return BSL_OVERFLOW;
        }
    }
    
    /* overflow check complete */
    for (i = INT_MAX; i > INT_MAX/2; i--){
        tempa = a->half_word[i];
        bigint_null(&sum);
        for (j = INT_MAX; j > INT_MAX/2; j--){
            tempb = b->half_word[j];
            k = i + j - INT_MAX;
            cumsum = tempa * tempb + sum.half_word[k];
            sum.half_word[k] = cumsum & LO_MASK;
            sum.half_word[k-1] = cumsum >> HALF_SIZE;
        }
        /* add it to the result */
        bigint_add(&sum, c, c);
    }
    return BSL_OK;
}

/* 
 * BSL_error 
 * bigint_div() 
 * Purpose: unsigned divide two big integers.  quotient = num/den
 * remainder = top % bottom
 * RESTRICTIONS: cannot over-write inputs
 * RESTRICTIONS: top is full size, bottom is half size, quot half size
 * Will return zero if top is zero and divide_by_zero if bottom is zero
 */

BSL_error 
bigint_div(bigint *num, bigint *den, bigint *quotient, bigint *remainder)
{
    /*check for divide by zero */
    bigint d,e;
    element mask;
    short int l,m,n,i,j;
    boolean iszero = TRUE;

    /* check all pointers */
    if ((num ==0) ||(den ==0)|| (quotient ==0 )||(remainder ==0)){
        return BSL_NULL_POINTER;
    }
    
    for(i=INT_MAX; i>= INT_MAX/2; i--){
        if(den->half_word[i] != 0){
            iszero = FALSE;
        }
    }
    if(iszero == TRUE){
        return BSL_DIVIDE_BY_ZERO;
    }
    
    /* denominator is ok 
     * set counters to msb in numerator and denominator 
     */
    bigint_copy(num, &d);
    bigint_copy(den, &e);

    l = (INT_MAX + 1) * HALF_SIZE;
    for(i = 0; i <= INT_MAX; i++){
        if(!d.half_word[i]) l -= HALF_SIZE;
        else break;
    }
    mask = MSB_HW;
    for( j=0; j < HALF_SIZE; j++){
        if(!(d.half_word[i] & mask)){
            l--;
            mask >>= 1;
        }
        else break;
    }

    /*repeat for denominator*/
    m = (INT_MAX + 1) * HALF_SIZE;
    for(i = 0; i <= INT_MAX; i++){
        if(!e.half_word[i]) m -= HALF_SIZE;
		else break;
    } 
    mask = MSB_HW;
    for(j=0; j < HALF_SIZE; j++){
        if(!(e.half_word[i] & mask)){
            m--;
            mask >>= 1;
        }
        else break;
    }

    /*check for error , is it divide by one?*/
    if (!m){
        bigint_copy(num, quotient);
        bigint_null(remainder);
        return BSL_OK;
    }

    /* if denominator is greater, set quotient 
     * zero, return remainder 
     */

    if(!l | (l<m)){
        bigint_null(quotient);
        bigint_copy(num, remainder);
        return BSL_OK;
    }

    /* shift to align before subtracting */
    n = l - m ;
    i = n;
    while(i > HALF_SIZE){
        for(j = 0; j < INT_MAX; j++){
            e.half_word[j] = e.half_word[j+1];
        }
        i -= HALF_SIZE;
        e.half_word[INT_MAX] = 0;
    }
    mask = 0;
    while(i > 0){
        for(j = INT_MAX; j >= 0; j--){
            e.half_word[j] = (e.half_word[j] << 1) | mask;
            mask = e.half_word[j] & CARRY ? 1 :0;
            e.half_word[j] &= LO_MASK;
        }
        i--;
    }

    bigint_null(quotient);

    while(n >= 0){
        i = INT_MAX - l/HALF_SIZE;
        j = INT_MAX - n/HALF_SIZE;
        while((d.half_word[i] == e.half_word[i]) &&(i < INT_MAX)) i++;
        if(d.half_word[i] >= e.half_word[i]){
            bigint_sub(&d, &e, &d);
            mask = 1L << (n % HALF_SIZE);
            quotient->half_word[j] |= mask;
        }
        for(j= INT_MAX; j >=0; j--){
            if(j) mask = (e.half_word[j-1] & 1)? CARRY :0;
            else mask =0;
            e.half_word[j] = (e.half_word[j] | mask) >> 1;
        }
        n--;
        l--;
    }
    bigint_copy( &d, remainder);
    return BSL_OK;
}

#if 0
/* 
 * BSL_error 
 * ascii_to_bigint() 
 * Purpose: to input ascii numbers into the bigint structure
 * RESTRICTIONS: use decimal input, doesnt check for >9.
 */


BSL_error 
ascii_to_bigint(char *instring, bigint *outhex)
{
    element ch;
    bigint ten, digit, temp;
    if((instring == NULL) || (outhex == NULL)){
        return BSL_NULL_POINTER;
    }
    bigint_null(&ten);
    ten.half_word[INT_MAX] = 0xA;
    bigint_null(&digit);
    bigint_null(outhex);

    while ( ch = *instring++){
        digit.half_word[INT_MAX] = ch & 0xF;
        bigint_mul(outhex, &ten, &temp);
        if(digit.half_word[INT_MAX] > 9) continue;
        bigint_add(&temp, &digit, outhex);
    }
    return BSL_OK;
}



/* 
 * BSL_error 
 * bigint_to_ascii() 
 * Purpose: to return ascii from a big int for debugging
 * RESTRICTIONS: outstring should be allocated to be size 
 * log2*4*HALF_SIZE*MAXLONG
 */


BSL_error 
bigint_to_ascii(bigint *inhex, char *outstring)
{
    bigint top, ten, quotient, remainder;
    element check;
    short int i;
    if((inhex == NULL) ||(outstring == NULL)){
        return BSL_NULL_POINTER;
    }
    bigint_copy(inhex, &top);
    /* create constant 10
     */
    bigint_null(&ten);
    ten.half_word[INT_MAX] = 0xA;
    /*blank fill and null terminate
     */
    for(i = 0; i< MAX_STRING; i++){ 
        /* blank */
        *outstring++ = ' ';
    }
    *outstring-- = 0;

    check = 1;
    while(check){
        bigint_div(&top, &ten, &quotient, &remainder);
        *outstring-- = remainder.half_word[INT_MAX] | '0';
        check =0;
        for(i=INT_MAX; i>=0; i--){
            check |= quotient.half_word[i];
        }
        bigint_copy(&quotient, &top);
    }
    return BSL_OK;
}

#endif

/* 
 * BSL_error 
 * bigint_div2() 
 * Purpose: to divide a bigint by 2
 */

BSL_error 
bigint_div2(bigint *x)
{
	short int j;
	element mask;
        if(x == NULL){
            return BSL_NULL_POINTER;
        }
	for(j = INT_MAX; j >= 0; j--){
            if (j){
                mask = (x->half_word[j-1] & 1 ) ? CARRY : 0;
            }
            else mask =0;
            x->half_word[j] = (x->half_word[j]  | mask) >> 1;	
	}
	return BSL_OK;
}


/* 
 * BSL_error 
 * mod_exp() 
 * Purpose: from Knuth binary exponentiation, converted to mod 462 page, vol2
 * z = x^n mod q
 * 
 */

BSL_error 
mod_exp(bigint *x, bigint *n, bigint *q, bigint *z)
{
    bigint N, Y, Z, temp, dummy;
    element check;
    short int i;

    /* Check error
     */
    if((x == NULL) || (n == NULL) || (q == NULL) || (z == NULL)){
        return BSL_NULL_POINTER;
    }

    /* Initialise before the loop 
     */

    /* N <- n */
    bigint_copy(n, &N);
    /* Y <- 1 */
    bigint_null(&Y);
    Y.half_word[INT_MAX] =1;
    /* Z <- x  */
    bigint_copy(x, &Z);

    /* 
     * This is to check if N is 0. This is checked each time to
     * determine whether to quit the loop 
     */
    check =0;
    for(i = INT_MAX; i >= 0; i--){
        /* or all the bits to see if anything is set 
         */
        check |= N.half_word[i];
    }
    while(check){
        /* if N is odd */
        if(N.half_word[INT_MAX] & 1){
            /* Y <- Y * Z mod q */
            /* Y <- Y * Z */
            bigint_mul(&Y, &Z, &temp);
            /* Y <- Y mod q */
            bigint_div(&temp, q, &dummy, &Y);
        }
        /* N <- floor(N/2) */
        bigint_div2(&N); 
        /* Z <- Z * Z mod q */
        bigint_mul(&Z, &Z, &temp);
        bigint_div(&temp, q, &dummy, &Z);
        /* again see if any bit is set in N, or it is zero.
         * If it is zero this loop will not execute again
         */
        check =0;
        for(i = INT_MAX; i>=0; i--){
            check |= N.half_word[i];
        }
    }
    bigint_copy(&Y, z);
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
bigint_mod_inv(bigint *a, bigint *b, bigint *x)
{
    bigint m, n, p0, p1, p2, q, r, temp, dummy;
    element check;
    short int sw, i;

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
    bigint_copy(b, &m);
    bigint_copy(a, &n);
    bigint_null(&p0);
    p0.half_word[INT_MAX] = 1;
    bigint_div(&m, &n, &p1, &r);
    bigint_copy(&p1, &q);

    /*loop */
    check  =0;
    for(i=INT_MAX; i>=0; i--){
        check |= r.half_word[i];
    }
    while(check){
        /* sw = -sw */
        sw = -sw;
        /* m = n */
        bigint_copy(&n, &m);
        /* n = r */
        bigint_copy(&r, &n);
        /* q = m/n, r = m % n */
        bigint_div(&m, &n, &q, &r);
        /* p2 = q * p1 + p0 % b */
        bigint_mul(&q, &p1, &temp);
        bigint_add(&temp, &p0, &temp);
        bigint_div(&temp, b, &dummy, &p2);
        /* p0 = p1 */
        bigint_copy(&p1, &p0);
        /* p1 = p2 */
        bigint_copy(&p2, &p1);
        check =0;
        for(i = INT_MAX; i>=0; i--){
            check |= r.half_word[i];
        }
    }
    if(sw < 0) bigint_sub(b, &p0, x);
    else bigint_copy(&p0, x);
    return BSL_OK;
}


BSL_error 
field_to_bigint(field_2n *a, bigint *b)
{
  short int i,j;
  bigint_null(b);
  for(i= NUM_WORD; i >=0; i--){
    j = INT_MAX - ((NUM_WORD -i) <<1);
    b->half_word[j] = a->e[i] & LO_MASK;
    j--;
    b->half_word[j] = (a->e[i] & HI_MASK)>>HALF_SIZE;
  }
}

#if 0

BSL_error bigint_to_field(bigint *a, field_2n *b){
	short int i,j;
	for(i=INT_MAX; i>=0; i--){
		j = (i + MAX_LONG)<<1;
		b->e[i] = a->half_word[j+1] | (a->half_word[j] << HALF_SIZE);
	}
}


#endif
