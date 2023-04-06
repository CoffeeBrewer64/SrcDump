/* 
 * integer_math.c
 * implementations for integer math routines needed for the 
 * ECDSA algorithm. implemented using the array of half words big 
 * integer notation
 * 
 */

#include <stdio.h>
#include "integer_math_rsa.h"

/*
 * BSL_error 
 * bigint_null()
 * Purpose : set to zero a bigint
 * input: pointer to allocated bigint
 * */

BSL_error 
bigint_null(bigint *a, int int_max)
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
 * bigint_copy() 
 * Purpose: to copy one big integer to another: copy a into b
 * inputs: pointer to allocated bigint a and bigint b
 */

BSL_error 
bigint_copy(bigint *a, bigint *b, int int_max)
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
 * bigint_add() 
 * Purpose: to add two big integers.  c = a + b
 * Restrictions: none: can add in place and over-write input 
 */

BSL_error 
bigint_add(bigint *a, bigint *b, bigint *c, int int_max)
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
 * bigint_neg(a)  
 * Purpose: negate in place. a= -a
 * inputs: allocated bigint a
*/

BSL_error 
bigint_neg(bigint *a, int int_max)
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
 * bigint_sub(a,b,c) 
 * Purpose: to perform  a-b = c
 * inputs: allocated bignums a,b
*/
BSL_error 
bigint_sub(bigint *a, bigint *b, bigint *c, int int_max)
{
    bigint minusb;
    if((a == NULL) || (b == NULL) || (c == NULL)){
        return BSL_NULL_POINTER;
    }
    bigint_copy(b, &minusb, int_max);
    bigint_neg(&minusb, int_max);
    bigint_add(a, &minusb, c, int_max);
    return BSL_OK;
}


BSL_error
bigint_mul( bigint *a, bigint *b, bigint *c, int int_max)
{
	element 		ea, eb, mul;
	short int 	i, j, k;
	bigint	sum;
	bigint_null(c, int_max);
 
	
	for ( i = int_max; i > int_max/2; i--)
	{
		ea = a->half_word[i];
		bigint_null( &sum, int_max);
		for ( j = int_max; j > int_max/2; j--)
		{
			eb = b->half_word[j];
			k = i + j - int_max;
			mul = ea * eb + sum.half_word[k];
			sum.half_word[k] = mul & LO_MASK;
			sum.half_word[k-1] = mul >> HALF_SIZE;
		}
		bigint_add( &sum, c, c, int_max);
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
bigint_div(bigint *num, bigint *den, bigint *quotient, bigint *remainder, int int_max)
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
    
    for(i=int_max; i>= int_max/2; i--){
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
    bigint_copy(num, &d, int_max);
    bigint_copy(den, &e, int_max);

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
        bigint_copy(num, quotient, int_max);
        bigint_null(remainder, int_max);
        return BSL_OK;
    }

    /* if denominator is greater, set quotient 
     * zero, return remainder 
     */

    if(!l | (l<m)){
        bigint_null(quotient, int_max);
        bigint_copy(num, remainder, int_max);
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

    bigint_null(quotient, int_max);

    while(n >= 0){
        i = int_max - l/HALF_SIZE;
        j = int_max - n/HALF_SIZE;
        while((d.half_word[i] == e.half_word[i]) &&(i < int_max)) i++;
        if(d.half_word[i] >= e.half_word[i]){
            bigint_sub(&d, &e, &d, int_max);
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
    bigint_copy( &d, remainder, int_max);
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
    ten.half_word[int_max] = 0xA;
    bigint_null(&digit);
    bigint_null(outhex);

    while ( ch = *instring++){
        digit.half_word[int_max] = ch & 0xF;
        bigint_mul(outhex, &ten, &temp);
        if(digit.half_word[int_max] > 9) continue;
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
    ten.half_word[int_max] = 0xA;
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
        *outstring-- = remainder.half_word[int_max] | '0';
        check =0;
        for(i=int_max; i>=0; i--){
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
bigint_div2(bigint *x, int int_max)
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
 * mod_exp() 
 * Purpose: from Knuth binary exponentiation, converted to mod 462 page, vol2
 * z = x^n mod q
 * 
 */

BSL_error 
mod_exp(bigint *x, bigint *n, bigint *q, bigint *z, int int_max)
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
    bigint_copy(n, &N, int_max);
    
    /* Y <- 1 */
    bigint_null(&Y, int_max);
    Y.half_word[int_max] =1;
    /* Z <- x  */
    bigint_copy(x, &Z, int_max);
    
    
    /* 
     * This is to check if N is 0. This is checked each time to
     * determine whether to quit the loop 
     */
    check =0;
    for(i = int_max; i >= 0; i--){
        /* or all the bits to see if anything is set 
         */
        check |= N.half_word[i];
    }
    while(check){
        
        /* if N is odd */
        if(N.half_word[int_max] & 1){
            /* Y <- Y * Z mod q */
            /* Y <- Y * Z */
            bigint_mul(&Y, &Z, &temp, int_max);
            /* Y <- Y mod q */
            bigint_div(&temp, q, &dummy, &Y, int_max);
        }
        /* N <- floor(N/2) */
        
        bigint_div2(&N, int_max);
        
        /* Z <- Z * Z mod q */
        bigint_mul(&Z, &Z, &temp, int_max);
        bigint_div(&temp, q, &dummy, &Z, int_max);
        /* again see if any bit is set in N, or it is zero.
         * If it is zero this loop will not execute again
         */
        check =0;
        for(i = int_max; i>=0; i--){
            check |= N.half_word[i];
        }
    }
    bigint_copy(&Y, z, int_max);
    return BSL_OK;
}


#if 0
/* z = x^n mod q */

BSL_error 
mod_exp(bigint *x, bigint *n, bigint *q, bigint *z){
    bigint N, Y, Z, temp, dummy;
    element check;
    short int i;

    /* Check error
     */
    if((x == NULL) || (n == NULL) || (q == NULL) || (z == NULL)){
        return BSL_NULL_POINTER;
    }
    bigint_copy(n, &N);

    bigint_null(&Y);
    Y.half_word[int_max] = 0x1;
    
    bigint_copy(x, &Z);

    /* start  the loop */
    
 loop: 
    if(N.half_word[int_max] & 0x1){
        bigint_div2(&N);
        if(bigint_mul(&Y, &Z, &temp) != BSL_OK){
            fprintf(stderr,"ERROR FROM MUL\n");
        }
        if(bigint_div(&temp, q, &dummy, &Y) != BSL_OK){
            fprintf(stderr, "ERROR IN DIV\n");
        }
        
        check = 0;
        for(i = int_max; i >=0; i--){
            check |= N.half_word[i];
        }
        if(!check){
            /*N is zero */
            goto terminate;
        }
        else{
            if(bigint_mul(&Z, &Z, &temp) != BSL_OK){
                fprintf(stderr, "ERROR MULT\n");
            }
            if(bigint_div(&temp, q, &dummy, &Z) != BSL_OK){
                fprintf(stderr, "DIV ERROR\n");
            }
        }
    }
    else{
        if(bigint_div2(&N) != BSL_OK){
            fprintf(stderr, "DIV2 ERROR\n");
        }
        if(bigint_mul(&Z, &Z, &temp) != BSL_OK){
            fprintf(stderr, "MULTIPLY LAST ERROR\n");
        }
        if(bigint_div(&temp, q, &dummy, &Z) != BSL_OK){
            fprintf(stderr, "DIVIDE ERROR\n");
        }
    }
    goto loop;
            
    terminate: bigint_copy(&Y, z);
        return BSL_OK;
    
}
#endif


/* 
 * BSL_error 
 * mod_inv()
 * this is a corollary of extended euclidean algorithm 
 * euclidean algorithm gives p,q where gcd(a,b) = a + qb.
 * for relative primes, gcd =1, so 1 = pa + qb. So p = inv(a) mod b.
 * To find x = inv(a) mod b where a and b are relatively prime
*/

BSL_error 
bigint_mod_inv(bigint *a, bigint *b, bigint *x, int int_max)
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
    bigint_copy(b, &m, int_max);
    bigint_copy(a, &n, int_max);
    bigint_null(&p0, int_max);
    p0.half_word[int_max] = 1;
    bigint_div(&m, &n, &p1, &r, int_max);
    bigint_copy(&p1, &q, int_max);

    /*loop */
    check  =0;
    for(i=int_max; i>=0; i--){
        check |= r.half_word[i];
    }
    while(check){
        /* sw = -sw */
        sw = -sw;
        /* m = n */
        bigint_copy(&n, &m, int_max);
        /* n = r */
        bigint_copy(&r, &n, int_max);
        /* q = m/n, r = m % n */
        bigint_div(&m, &n, &q, &r, int_max);
        /* p2 = q * p1 + p0 % b */
        bigint_mul(&q, &p1, &temp, int_max);
        bigint_add(&temp, &p0, &temp, int_max);
        bigint_div(&temp, b, &dummy, &p2, int_max);
        /* p0 = p1 */
        bigint_copy(&p1, &p0, int_max);
        /* p1 = p2 */
        bigint_copy(&p2, &p1, int_max);
        check =0;
        for(i = int_max; i>=0; i--){
            check |= r.half_word[i];
        }
    }
    if(sw < 0) bigint_sub(b, &p0, x, int_max);
    else bigint_copy(&p0, x, int_max);
    return BSL_OK;
}

#if 0
BSL_error 
field_to_bigint(field_2n *a, bigint *b, int num_bits)
{
  short int i,j;
  int num_word = num_bits/WORD_SIZE;
  int max_long = num_word + 1;
  int int_max = (4 * max_long ) - 1;
  bigint_null(b, int_max);
  for(i= num_word; i >=0; i--){
    j = int_max - ((num_word -i) <<1);
    b->half_word[j] = a->e[i] & LO_MASK;
    
    j--;
    b->half_word[j] = (a->e[i] & HI_MASK)>>HALF_SIZE;
    
  }
  return BSL_OK;
}
#endif

#if 0
BSL_error bigint_to_field(bigint *a, field_2n *b){
	short int i,j;
	for(i=INT_MAX; i>=0; i--){
		j = (i + MAX_LONG)<<1;
		b->e[i] = a->half_word[j+1] | (a->half_word[j] << HALF_SIZE);
	}
}


#endif

#if 0
void random_field(field_2n *value)
{
	short int i;
	for(i = 0; i< MAX_LONG; i++){
	 	value->e[i] = rand();
	}
	value->e[0] &= UPR_MASK;
}
#endif

void bigint_swap(bigint *a, bigint *b, int int_max){
    bigint temp;
    int i;
    for(i =0; i<= int_max; i++){
        temp.half_word[i]  = a->half_word[int_max-i];
    }
    bigint_copy(&temp, b, int_max);
}
/* Decodes character string b into a, where character string is ordered
   from most to least significant.

   Lengths: a[digits], b[len].
   Assumes b[i] = 0 for i < len - digits * MAX_LONG. (Otherwise most
   significant bytes are truncated.)
 */
void charstring_to_bigint (bigint *a, unsigned char *b, unsigned int len, int int_max)
{
  element t;
  int j;
  unsigned int i, u;
  bigint temp;
  int digits = int_max;
  
  
  bigint_null(a, int_max);
  bigint_null(&temp, int_max);
  for (i = 0, j = len - 1; i <= digits && j >= 0; i= i+2) {
    t = 0;
    for (u = 0; j >= 0 && u < WORD_SIZE; j--, u += 8)
      t |= ((element)b[j]) << u;
    a->half_word[i+1] = (t & HI_MASK) >> HALF_SIZE;
    a->half_word[i] = (t & LO_MASK);
    
  }
  /*
  for (; i <= digits; i++)
    a->half_word[i] = 0;
  */

  bigint_swap(a, &temp, int_max);
  bigint_copy(&temp, a, int_max);

}


/* Encodes b into character string a, where character string is ordered
   from most to least significant.

   Lengths: a[len], b[digits].
   Assumes NN_Bits (b, digits) <= 8 * len. (Otherwise most significant
   digits are truncated.)
 */
void bigint_to_charstring(unsigned char  *a, unsigned int len, bigint *b, int int_max){
  int j;
  unsigned int i;


  bigint_swap(b, b, int_max);

  j = len - 2;
  for(i= 0; i < int_max; i++){
      a[j] = ((b->half_word[i]) >> 8) &0xff;
      a[j + 1] = b->half_word[i] & 0xff;
      j -= 2;
      if (j < 0){
          break;
      }
  }
}


/* high level function for RSA verify 
 * n and e are modulus and exponent, sign is input, result is output, 
 * num_bits is bit length for RSA operations 
 */
BSL_error 
bsl_rsa_verify(char *result, char * e_string, int e_size, char *n_string, int n_size, char *sign, int sign_size, int num_bits){
    BSL_error err = BSL_OK;
    int num_word, max_long, int_max;
    bigint m, n, e, o;

    num_word = num_bits/WORD_SIZE;
    max_long = num_word + 1;
    int_max = (4*max_long) - 1;
    charstring_to_bigint(&m, sign, sign_size, int_max);
    charstring_to_bigint(&n, n_string, n_size, int_max);
    charstring_to_bigint(&e, e_string, e_size, int_max);

    /* compute o = m^e mod n */
    err = mod_exp(&m, &e, &n, &o, int_max);
    
    /* go back to string*/
    bigint_to_charstring(result, sign_size, &o, int_max);
    return  err;
}



#if 0
unsigned int myrand(unsigned int seed);
void random_field(field_2n *value, unsigned int seed);




/* 
 * test code for integer functions
 */
int 
main(int argc, char ** argv)
{
    int i,j;
    int result = 0;
    bigint a, b, c, d, dummy;
    field_2n temp;
    bigint_null(&a);
    bigint_null(&b);
    bigint_null(&c);
    bigint_null(&d);
    
/*     
    for(i = INT_MAX; i > INT_MAX/2; i--){
        a.half_word[i] = 0x45673254 & 0x0000ffff;
	b.half_word[i] = 0x09876543 & 0x0000ffff;
    }
*/
    for(j = 0; j < 1; j++){
        /* do this way to ensure only 233 bits worth of bigint is filled*/
        random_field(&temp, 1234);
        field_to_bigint(&temp, &a);
        random_field(&temp, 2345);
        field_to_bigint(&temp, &b);
        
        for(i = int_max; i >=0; i--){
            printf("init a.half_word[%d] = %08x\n", i, a.half_word[i]);
            printf("init b.half_word[%d] = %08x\n", i, b.half_word[i]);
        }
        

#if 0
        bigint_add(&a, &b, &c);
        bigint_sub(&c, &a, &d);
    
        printf("Result of add and subtract\n");
        for(i = int_max; i >= 0; i--){
            printf("b.half_word[%d] = %08x\n", i, b.half_word[i]);
            printf("d.half_word[%d] = %08x\n", i, d.half_word[i]);
        }
#endif
        bigint_mul(&a, &b, &c);
/*
        printf("Result of multiply\n");
        for(i = INT_MAX; i >= 0; i--){
            printf("c.half_word[%d] = %08x\n", i, c.half_word[i]);
        }
*/
    
        bigint_div(&c, &a, &d, &dummy);
        result =0;
        /* d should be equal to b */
/*
        printf("Result of divide\n");

  for(i = INT_MAX; i >= 0; i--){
  printf("d.half_word[%d] = %08x\n", i, d.half_word[i]);
  printf("b.half_word[%d] = %08x\n", i, b.half_word[i]);
  }
*/
        for(i = INT_MAX; i >= 0; i--){
            if (b.half_word[i] != d.half_word[i]){
                printf("b.half_word[%d] = %08x\n, d.half_word[%d] = %08x\n",i, b.half_word[i], i, d.half_word[i]);
                result = 1;            }
        }
    
        if(result == 0){
            printf("PASS\n");
        }
        else{
            printf("FAIL\n");
        }
    }

    bigint_mod_inv(&a, &b, &c);
    /* result c is inv(a) mod b */
    bigint_mul(&a, &c, &d);
    /* d should be multiple of b */
    printf("Result of mod inv, d should be mult of b\n");
    for(i = INT_MAX; i >= 0; i--){
        printf("d.half_word[%d] = %08x\n", i, d.half_word[i]);
	printf("b.half_word[%d] = %08x\n", i, b.half_word[i]);
    }

    for(j= 0; j< 11; j++){
    bigint_null(&a);
    bigint_null(&b);
    bigint_null(&c);
    bigint_null(&d);
    a.half_word[INT_MAX] = 0x7;
    b.half_word[INT_MAX] = j;
    c.half_word[INT_MAX] = 0xb;

    mod_exp(&a, &b, &c, &d);
     printf("Result of bogus mod exp\n");
    for(i = INT_MAX; i >= 0; i--){
        printf("d.half_word[%d] = %08x\n", i, d.half_word[i]);
    }
    }

    return 0;
}




unsigned int myrand(unsigned int seed){
    seed = 0x343fd * seed + 0x269ec3;
    return ((seed )& 0xffffffff);
            }

/* to get a random field for testing */

void random_field(field_2n *value, unsigned int seed)
{
    short int i;
    for(i = 0; i< MAX_LONG; i++){
        value->e[i] = myrand(seed);
        seed = value->e[i];
    }
    value->e[0] &= UPR_MASK;
}

#endif








