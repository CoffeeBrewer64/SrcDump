/* poly_math.c
 * implementation of GF 2^m arithmetic 
 * needed for elliptic math
 */

#include "integer_math.h"
#include "binary_field.h"
#include "poly_math.h"

/*
field_2n poly_prime = {0x00008000,0x00000000,0x00000000,0x00000401};
*/
field_2n poly_prime = {0x00000200,0x00000000,0x00000000,0x00000000,0x00000000,0x00000400, 0x00000000, 0x00000001};  
 
/*
 * BSL_error 
 * multiply_shift()
 * Purpose : shift one bit to do partial multiply: double field.
 * input: pointer to allocated field_double, can do in place
 * 
 */

BSL_error 
multiply_shift(field_double *a)
{
  element *eptr, temp, bit;
  short int i;

  if(a == NULL){
    return BSL_NULL_POINTER;
  }
  /* this is bigendian representation
   */
  eptr = &a->e[DOUBLE_WORD];
  bit =0;

  for(i =0; i< MAX_DOUBLE; i++){
    temp = (*eptr << 1) | bit;
    bit = (*eptr & MSB) ? 1L: 0L;
    *eptr-- = temp;
  }
  return BSL_OK;
}


/*
 * BSL_error 
 * null()
 * Purpose : null a field_2n variable
 * input: pointer to allocated field_2n, can do in place
 * 
 */

BSL_error 
null(field_2n *a)
{
  short int i;
  if(a == NULL){
    return BSL_NULL_POINTER;
  }
  for(i =0; i < MAX_LONG; i++){
    a->e[i] = 0L;
  }
  return BSL_OK;
}


/*
 * BSL_error 
 * double_null()
 * Purpose : null a double variable
 * input: pointer to allocated double, can do in place
 * 
 */

BSL_error
double_null(field_double *a)
{
  short int i;
  if(a == NULL){
    return BSL_NULL_POINTER;
  }
  for(i =0; i< MAX_DOUBLE; i++){
    a->e[i] = 0L;
  }
  return BSL_OK;
}



/*
 * BSL_error
 * double_add()
 * Purpose : add double variable
 * input: pointer to allocated doubles, cannot do in place
 * 
 */

BSL_error
double_add(field_double *a, field_double *b, field_double *c)
{
  short int i;
  if (( a == NULL)||(b == NULL)||(c == NULL)){
    return BSL_NULL_POINTER;
  }

  for(i =0; i< MAX_DOUBLE; i++){
    c->e[i] = a->e[i] ^ b->e[i];
  }
  return BSL_OK;
}



/*
 * BSL_error 
 * double_swap()
 * Purpose : swap doubles
 * input: pointer to allocated doubles, cannot do in place
 * 
 */

BSL_error 
double_swap(field_double *a, field_double *b)
{
  BSL_error err;
  field_double temp;
  if (( a == NULL)||(b == NULL)){
    return BSL_NULL_POINTER;
  }
  err = double_null(&temp);
  if(err != BSL_OK){
    return err;
  }

  err = double_copy(a, &temp);
  if(err != BSL_OK){
    return err;
  }

  err = double_copy(b, a);
  if(err != BSL_OK){
    return err;
  }
  
  err = double_copy(&temp, b);
  if(err != BSL_OK){
    return err;
  }

  return BSL_OK;
}



/*
 * BSL_error 
 * copy()
 * Purpose : copy field_2n variables
 * input: pointer to allocated field_2n, cannot do in place
 * 
 */

BSL_error
copy(field_2n *from, field_2n *to)
{
  short int i;
  if ((from == NULL)||(to == NULL)){
    return BSL_NULL_POINTER;
  }
  for(i =0 ; i < MAX_LONG; i++){
    to->e[i] = from->e[i];
  }
  return BSL_OK;
}



/*
 * BSL_error 
 * double_copy()
 * Purpose : copy double variables
 * input: pointers to allocated double, cannot do in place
 * 
 */

BSL_error 
double_copy(field_double *from, field_double *to)
{
  short int i;
  if ((from == NULL)||(to == NULL)){
    return BSL_NULL_POINTER;
  }
  for(i =0 ; i < MAX_DOUBLE; i++){
    to->e[i] = from->e[i];
  }
  return BSL_OK;
}


/*
 * BSL_error 
 * double_is_one()
 * Purpose : check if one
 * input: pointers to allocated double, result
 * 
 */
BSL_error 
double_is_one(field_double *a, boolean *result)
{
  short int i;
  field_double one;
  if (( a == NULL)||(result == NULL)){
    return BSL_NULL_POINTER;
  }
  *result = TRUE;
  
  double_null(&one);
  /* big endian representation
   */
  one.e[DOUBLE_WORD] = 1;
  for(i =0; i < MAX_DOUBLE; i++){
    if(one.e[i] != a->e[i]){
      *result = FALSE;
    }
  }
  return BSL_OK;
}


/*
 * BSL_error 
 * single_to_double()
 * Purpose : copy single to double
 * input: pointers to allocated double, cannot do in place
 * 
 */

BSL_error 
single_to_double(field_2n *from, field_double *to)
{
  short int i;
  if (( from == NULL)||(to == NULL)){
    return BSL_NULL_POINTER;
  }
  double_null(to);
  for(i =0 ; i < MAX_LONG; i++){
    to->e[DOUBLE_WORD - NUM_WORD + i] = from->e[i];
  }
  return BSL_OK;
}


/*
 * BSL_error 
 * double_to_single()
 * Purpose : copy bottom of double to single
 * input: pointers to allocated double, cannot do in place
 * 
 */
BSL_error 
double_to_single(field_double *from, field_2n *to)
{
  short int i;
  if (( from == NULL)||(to == NULL)){
    return BSL_NULL_POINTER;
  }
  for(i =0; i <MAX_LONG; i++){
    to->e[i] = from->e[DOUBLE_WORD - NUM_WORD + i];
  }
  return BSL_OK;
}


/*
 * BSL_error 
 * poly_mul_partial()
 * Purpose : multiply two field_2n variables and obtain double
 * input: pointers to allocated field_2n and double
 * 
 */
BSL_error 
poly_mul_partial(field_2n *a, field_2n *b, field_double *c)
{
  short int i, bit_count, word;
  element mask;
  field_double local_b;

  if (( a == NULL)||(b == NULL)||(c == NULL)){
    return BSL_NULL_POINTER;
  }

  /*clear bits in the result */
  double_null(c);
  /* initialize local b */
  single_to_double(b, &local_b);

  /*
   * for every bit in a that is set, add local_b to the
   * result 
   */
  mask = 1;
  for(bit_count =0; bit_count < NUM_BITS; bit_count++){
    word = NUM_WORD - bit_count / WORD_SIZE;
    if(mask & a->e[word]){
      for(i =0; i< MAX_DOUBLE; i++){
	c->e[i] ^= local_b.e[i];
      }
    }
    multiply_shift(&local_b);
    mask <<= 1;
    if (!mask) mask = 1; /*re-initialise if zero */
  }
  return BSL_OK;
}

#if 0
/* shift right one bit 
later use this for poly_mul too with prime polynomial 
shifting is in place
*/


BSL_error divide_shift(field_double *a){
	element *eptr, temp, bit;
	short int  i;
	eptr = (element *) &a->e[0];
	bit = 0;
	for(i =0; i< MAX_DOUBLE; i++){
		temp = (*eptr >> 1) | bit;
		bit = (*eptr & 1) ? MSB : 0L;
		*eptr++ = temp;
	}
	return BSL_OK;
}

/* shift right n bits: use for poly_mul, rewrite using
barrel shifter and word wise shifting */

BSL_error shift_bit_n(field_double *a, int n){
	element *eptr, temp, bit;
	short int  i,k;
	eptr = (element *) &a->e[0];
	bit =0;

	for(k=0; k<n;k++){
		for(i =0; i< MAX_DOUBLE; i++){
			temp = (*eptr >> 1) | bit;
			bit = (*eptr & 1) ? MSB : 0L;
			*eptr++ = temp;
		}
	}
	return BSL_OK;
}

/*supporting functions for poly_mul later */
/* extract bits of the double field corresponding to mask*/
BSL_error extract_mask(field_double * a, field_double *mask, field_double *result){
	short int i;
	for(i =0; i< MAX_DOUBLE; i++){
		result->e[i] = a->e[i] & mask->e[i];
	}
	return BSL_OK;
}

/* put zeros in nonzero locations of mask in the input*/
BSL_error zero_masked_bits(field_double *a, field_double *mask, field_double *result){
	short int i;
	for(i =0; i< MAX_DOUBLE; i++){
		/* a - mask = a intersection (mask)complement */
		a->e[i] = a->e[i] & (!mask->e[i]);
	}
	return BSL_OK;
}


/*this is polynomial multiplication modulo a primitive
polynomial. The primitive polynomial is 233 bits
u^233 + u^74 + 1. defined in the header field
generally this will work for any trinomials changing the
shift numbers, check word
size. Need to generalise for pentanomials.
field_2n poly_prime = {0x00080000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000400, 0x00000000, 0x00000001};  
233 bit u^233 + u^74 + 1

  this is derived from the method in "fast key exchange with 
  elliptic curve systems"
 by schroeppel, orman, malley
*/

BSL_error poly_mul( field_2n *a, field_2n *b, field_2n *c){
	field_double temp, temp_masked;
	field_double extract_mask; /* check if this is 16*32=512 bits!*/
/* bits 464-306 */
	double_null(extract_mask);
	/*MSB is in 0*/
	extract_mask.e[1] = 0x0001ffff;
	extract_mask.e[2] = 0xffffffff;
	extract_mask.e[3] = 0xffffffff;
	extract_mask.e[4] = 0xffffffff;
	extract_mask.e[5] = 0xffffffff;
	extract_mask.e[6] = 0xfffc0000;
	poly_mul_partial(a,b, &temp);

	/* extract first 159 bits and shift it by 159, and 233
	and add to temp.
	*/
	/*first 159 bits */
	extract_masked_bits(&temp, &extract_mask, &temp_masked);
	zero_masked_bits(&temp, &extract_mask);
	shift_bit_n(temp_masked, 159);
	double_add(temp, temp_masked); /* result in temp*/
	/* then 233, ie 233-159 more*/
	shift_bit_n(temp_masked, 74);
	double_add(temp, temp_masked);

	/* temp has first 159 bits reduced*/
	/* second iteration */
	/* repeat only for 74 points 306-234 inclusive */
	double_null(extract_mask);
	/*MSB is in 0*/
	extract_mask.e[3] = 0x0007ffff;
	extract_mask.e[4] = 0xffffffff;
	extract_mask.e[5] = 0xffffffff;
	extract_mask.e[6] = 0xffffffff;
	extract_mask.e[7] = 0xffffffff;
	extract_mask.e[8] = 0xfffffc00;

	/*first 74 bits*/
	extract_masked_bits(&temp, &extract_mask, &temp_masked);
	zero_masked_bits(&temp, &extract_mask);
	/* shift by 159 */
	shift_bit_n(temp_masked, 159);
	double_add(temp, temp_masked);
	/* then 74 more */
	shift_bit_n(temp_masked, 74);
	double_add(temp, temp_masked);

	double_to_single(&temp, c);

	return BSL_OK;
}



/* this is implementation of the modified almost inverse 
algorithm for inversion in F(2^m) in the paper: software 
implementation of elliptic curve cryptography over binary fields
by Hankerson, Hernandez, and Menezes

  uses multiply_shift and divide_shift above
b = inv (a) mod poly_prime
  */

BSL_error poly_inv(field_2n *a, field_2n *b){
  field_double U, V;
  field_double temp, temp1;
  bool res;
  field_double B, C; /* later copy to single field b */
  null(&U);
  null(&V);
  null(&B);
  /* check this */

  B.e[0] =1;

  null(&C);
  /* u = a*/
  single_to_double(a, &U);
  /*v = f*/
  single_to_double(&V, &poly_prime);
  for(;;){ /* infinite loop, quits from inside : check this!*/
    /* while u is even do */
    while((U.e[0] & 1)== 0){
      divide_shift(&U);
      /* if B is even do */
      if((B.e[0] & 1) ==0){
	divide_shift(&B);
      }
      else{
	/*b = b + f*/
	single_to_double(&temp, &poly_prime);
	double_add(&B, &temp, &temp1);
	double_copy(&temp1, &B);
      }
    }
    double_is_one(&U, &res);
    if (res == true){
      double_to_single(&B, b);
      return BSL_OK;
    }
	
    /* degree of U < degree of V */
    double_is_less(&U, &V, &res);
    if (res == true){
      double_swap(&U, &V);
      double_swap(&B, &C);
    }
    /*u = u + v */
    double_add(&U, &V, &temp);
    double_copy(&temp, &U);
    /*b = b + c */
    double_add(&B, &C, &temp);
    double_copy(&temp, &B);
  }/* for infinite loop*/
}

#endif


/*
 * BSL_error 
 * poly_div_shift()
 * Purpose : shift right once for polynomial division
 * input: pointers to allocated double, in place
 * 
 */

BSL_error 
poly_div_shift(field_double *a)
{
  element *eptr, temp, bit;
  short int i;

  if(a == NULL){
    return BSL_NULL_POINTER;
  }

  eptr = (element *) &a->e[0];
  bit = 0;
  
  for(i =0; i < MAX_DOUBLE; i++){
    temp = (*eptr >> 1) | bit;

    bit = (*eptr & 1) ? MSB:0L;

    *eptr++ = temp;
  }
  return BSL_OK;
}


/*
 * BSL_error 
 * poly_log2(short int *result)
 * Purpose : find first bit set
 * input: pointers to allocated double, in place, returns index
 * 
 */

BSL_error
poly_log2(element x, short int *result)
{
  element ebit, bitsave, bitmask;
  short int k, lg2;

  if(x == 0){
    return BSL_NULL_POINTER;
  }

  lg2 = 0;
  bitsave = x;

  k = WORD_SIZE/2;

  bitmask = -1L << k;

  while(k){
    ebit = bitsave & bitmask;
    if (ebit){
      lg2 += k;
      /* increment degree */
      bitsave = ebit;
    }
    /* binary searching */
    k /= 2; 
    bitmask ^= (bitmask >> k);
  }

  *result = lg2;
  return BSL_OK;
}




/*
 * BSL_error 
 * poly_degree_of(element *t, short int *result)
 * Purpose : find first bit set in array of elements
 * input: pointers to allocated double, in place, returns index
 * 
 */
  
BSL_error
poly_degree_of(element *t, short int dim, short int *result)
{
  short int degree, k;
  short int temp;
  BSL_error err;
  if(t == 0){
    return BSL_NULL_POINTER;
  }

  /* first non zero element */
  degree = dim * WORD_SIZE;
  for (k = 0; k < dim; k++){
    if( *t) break;
    degree -= WORD_SIZE;
    t++;
  }

  /* are all bits zero */
  if(!*t){
    *result = -1;
    return BSL_DIVIDE_BY_ZERO;
  }
  
  err = poly_log2(*t, &temp);
  if( err != BSL_OK){
    return BSL_OK;
  }
  degree += temp;
  *result = degree;
  return BSL_OK;
}



/*
 * BSL_error 
 * poly_div(field_double *top, field_2n *bottom, field_2n *quotient, field_2n *remainder)
 * Purpose : divide, get remainder
 * input: pointers to allocated double, field_2n variables
 * 
 */
BSL_error
poly_div(field_double *top, field_2n *bottom, field_2n *quotient, field_2n *remainder)
{
  short int degree_top, degree_bottom, degree_quotient;
  short int bit_count;
  short int temp;
  short int i;
  BSL_error err;

  short int equot;
  element top_bit; /* mask for top to see if bit is set*/
  element *tptr;
  field_double shift;

  /* find degrees */
  err = poly_degree_of((element *) top, DOUBLE_WORD, &temp);
  /*
  if (err != BSL_OK){
    return err;
  }
  */
  degree_top = temp;
  err = poly_degree_of((element *)bottom, NUM_WORD, &temp);
  /*
  if(err != BSL_OK){
    return err;
  }
  */
  degree_bottom = temp;

  /* if top is smaller than bottom return remainder */
  null(quotient);
  if(degree_top < degree_bottom){
    double_to_single(top, remainder);
    return BSL_OK;
  }

  /* shift bottom to align with top */
  degree_quotient = degree_top - degree_bottom;
  bit_count = degree_quotient + 1;
  single_to_double(bottom, &shift);
  for(i = 0; i < degree_quotient; i++){
    multiply_shift(&shift);
  }

  /* check if MSB of top is set */
  top_bit = 1L << (degree_top % WORD_SIZE);
  tptr = (element *) top + DOUBLE_WORD - degree_top/WORD_SIZE;
  
  /* for each quotient bit if bottom can be subtracted, subtract 
   * and set bit*/

  while(bit_count){
    if(*tptr & top_bit){
      for( i=0; i< MAX_DOUBLE; i++){
	top->e[i] ^= shift.e[i];
      }

      /* find word and bit to set */
      equot = NUM_WORD - degree_quotient/WORD_SIZE;
      quotient->e[equot] |= 1L << (degree_quotient % WORD_SIZE);
    }

    /* next quotient bit */
    bit_count--;
    degree_quotient--;
    poly_div_shift(&shift);
    top_bit >>= 1;
    if(!top_bit){
      top_bit = MSB;
      tptr++;
    }
  }

  /* remainder in top */
  double_to_single(top, remainder);
  return BSL_OK;
}
  


/*
 * BSL_error 
 * poly_mul(field_2n *a, field_2n *b, field_2n *c)
 * Purpose : polynomial multiplication modulo poly_prime
 * input: pointers to field_2n variables
 * 
 */

BSL_error
poly_mul(field_2n *a, field_2n *b, field_2n *c)
{
  field_double temp;
  field_2n dummy;
  
  if((a==NULL) ||(b == NULL) || (c == NULL)){
    return BSL_NULL_POINTER;
  }

  poly_mul_partial(a, b, &temp);
  poly_div(&temp, &poly_prime, &dummy, c);

  return BSL_OK;
}



/*
 * BSL_error 
 * poly_inv(field_2n *a, field_2n *inverse)
 * Purpose : polynomial inverse
 * input: pointers to field_2n variables
 * 
 */
BSL_error
poly_inv(field_2n *a, field_2n *inverse)
{
  field_2n pk, pk1, pk2;
  field_2n rk, rk1;
  field_2n qk, qk1, qk2;
  short int i;
  field_double rk2;
  short int temp;
  BSL_error err;

  /* init*/
  single_to_double(&poly_prime, &rk2);
  
  copy(a, &rk1);
  null(&pk2);
  null(&pk1);
  pk1.e[NUM_WORD] = 1L;
  null(&qk2);
  null(&qk1);
  qk1.e[NUM_WORD] = 1L;
  
  /* compute quotient and remainder. when degree of remainder is
   * less than 0, there is no remainder, stop 
   */
  null(&pk);

  pk.e[NUM_WORD] = 1L;
	
  poly_div(&rk2, &rk1, &qk, &rk);
  
  
  err = poly_degree_of((element *) &rk, NUM_WORD, &temp);
  /*
  if(err != BSL_OK){
    return err;
  }
  */
  while(temp >= 0){ /*degree of remainder is >0 */
    poly_mul_partial(&qk, &pk1, &rk2);
    
  
    for(i =0 ; i< MAX_LONG; i++){
      pk.e[i] = rk2.e[i + DOUBLE_WORD - NUM_WORD] ^ pk2.e[i];
    }

    /* set up for next iteration*/
    single_to_double(&rk1, &rk2);
    copy(&rk, &rk1);
    copy(&qk1,&qk2);
    copy(&qk, &qk1);
    copy(&pk1, &pk2);
    copy(&pk, &pk1);
    poly_div(&rk2, &rk1, &qk, &rk);
 
    err = poly_degree_of((element *)&rk, NUM_WORD, &temp);
    /*
    if(err != BSL_OK){
      return err;
    }
    */
  }
  copy(&pk, inverse);
  return BSL_OK;
}
    


/*
 * BSL_error 
 * poly_rot_right(field_2n *a)
 * Purpose : polynomial rotate right once
 * input: pointers to field_2n variable
 * 
 */
    

BSL_error
poly_rot_right(field_2n *a)
{
  short int i;
  element bit, temp;
  bit = (a->e[NUM_WORD] & 1)? UPR_BIT : 0L;
  for(i = 0; i< MAX_LONG; i++){
    temp = (a->e[i] >> 1) | bit;
    bit = (a->e[i] & 1) ? MSB : 0L;
    a->e[i] = temp;
  }
  a->e[0] &= UPR_MASK;
  return BSL_OK;
}










