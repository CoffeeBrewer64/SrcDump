d1 7
a7 2

/* implementation of integer math functions */
d12 70
a81 39
/*BSL_error bigint_null() to set to zero a bigint */

BSL_error bigint_null(bigint *a){
  short int i;
  for(i=INT_MAX; i>= 0; i--){
    a->half_word[i] =0;
  }
  return BSL_OK;
}


/* BSL_error bigint_copy() to copy one big integer to another:
copy a into b*/

BSL_error bigint_copy(bigint *a, bigint *b){
  short int i;
  for(i=INT_MAX; i>=0; i--){
    b->half_word[i] = a->half_word[i];
  }
  return BSL_OK;
}



/* BSL_error bigint_add() to add two big integers. can add
in place and over-write input */

BSL_error bigint_add(bigint *a, bigint *b, bigint *c){
	short int i;
	element temp =0;
	for(i=INT_MAX; i>=0; i--){
		temp = a->half_word[i] + b->half_word[i] +(temp >>HALF_SIZE);
		c->half_word[i] = temp & LO_MASK;
	}
	return BSL_OK;
}

/* negate input, used in subtraction 
BSL_error bigint_neg(a,b)  b= -a
d84 26
a109 17
BSL_error bigint_neg(bigint *a){
	short int i;
	for(i=INT_MAX; i>= 0; i--){
		a->half_word[i] = ~a->half_word[i] & LO_MASK;
	}
	for(i=INT_MAX; i >= 0; i--){
		a->half_word[i]++;
		if(a->half_word[i] & LO_MASK) break;
		/* the last word was 1111, in which case it generated 
		a carry in half_word++ */
		a->half_word[i] &= LO_MASK;
	}
	return BSL_OK;
}

/* subtraction, using negation and addition
BSL_error bigint_sub(a,b,c) to perform  a-b = c
d111 124
a234 81
BSL_error bigint_sub(bigint *a, bigint *b, bigint *c){
	bigint minusb;
	bigint_copy(b, &minusb);
	bigint_neg(&minusb);
	bigint_add(a, &minusb, c);
	return BSL_OK;
}


/*c has to be different from a or b, dont overwrite
dont call twice in a row
*/

BSL_error bigint_mul(bigint *a, bigint *b, bigint *c){
	element tempa, tempb, cumsum;
	short int i,j,k;
	bigint sum;
	bigint_null(c);
	/*check input sizes, the sizes should be half
	check if any lower half bits are non zero 
	lower half is more significant bits
	*/
	for(i = INT_MAX/2 ; i>=0; i--){
		if (a->half_word[i] & (HI_MASK | LO_MASK)){
			return BSL_OVERFLOW;
		}
		if (b->half_word[i] & (HI_MASK | LO_MASK)){
			return BSL_OVERFLOW;
		}
	}
	/*overflow check complete*/
	for (i= INT_MAX; i > INT_MAX/2; i--){
		tempa = a->half_word[i];
		bigint_null(&sum);
		for (j= INT_MAX; j > INT_MAX/2; j--){
			tempb = b->half_word[j];
			k = i + j - INT_MAX;
			cumsum = tempa *tempb + sum.half_word[k];
			sum.half_word[k] = cumsum & LO_MASK;
			sum.half_word[k-1] = cumsum >> HALF_SIZE;
		}
		bigint_add(&sum,c,c);
	}
		return BSL_OK;
}

/*unsigned division. input full sized num, half sized den.
outputs are half sized */

BSL_error bigint_div(bigint *num, bigint *den, bigint *quotient, bigint *remainder){
	/*check for divide by zero */

	bigint d,e;
	element mask;
	short int l,m,n,i,j;
	boolean iszero = TRUE;
	for(i=INT_MAX; i>= INT_MAX/2; i--){
		if(den->half_word[i] != 0){
		iszero = FALSE;
		}
	}
	if(iszero == TRUE){
		return BSL_DIVIDE_BY_ZERO;
	}
	/* denominator is ok */
	
	/*set counters to msb in numerator and denominator */
	bigint_copy(num, &d);
	bigint_copy(den, &e);

	l = (INT_MAX +1)*HALF_SIZE;
	for(i =0; i<= INT_MAX; i++){
		if(!d.half_word[i]) l -= HALF_SIZE;
		else break;
	}
	mask = MSB_HW;
	for( j=0; j < HALF_SIZE; j++){
		if(!(d.half_word[i] & mask)){
			l--;
			mask >>= 1;
		}
d236 158
a393 120
	}
	/*repeat for denominator*/
	m = (INT_MAX + 1) *HALF_SIZE;
	for(i=0; i <= INT_MAX; i++){
		if(!e.half_word[i]) m -= HALF_SIZE;
		else break;
	}
	mask = MSB_HW;
	for(j=0; j < HALF_SIZE; j++){
		if(!e.half_word[i] & mask){
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
	zero, return remainder */

	if(!l | (l<m)){
		bigint_null(quotient);
		bigint_copy(num, remainder);
		return BSL_OK;
	}

	/* shift to align before subtracting */
	n = l -m ;
	i = n;
	while(i > HALF_SIZE){
		for(j=0; j<INT_MAX; j++){
			e.half_word[j] = e.half_word[j+1];
		}
		i -= HALF_SIZE;
		e.half_word[INT_MAX] =0;
	}
	mask =0;
	while(i >0){
		for(j=INT_MAX; j>=0; j--){
			e.half_word[j] = (e.half_word[j] << 1) | mask;
			mask = e.half_word[j] & CARRY ? 1 :0;
			e.half_word[j] &= LO_MASK;
		}
		i--;
	}

	bigint_null(quotient);

	while(n >= 0){
		i = INT_MAX - 1/HALF_SIZE;
		j = INT_MAX - n/HALF_SIZE;
		while((d.half_word[i] == e.half_word[i]) &&(i < INT_MAX)) i++;
		if(d.half_word[i] >= e.half_word[i]){
			bigint_sub(&d, &e, &d);
			mask = 1L << (n % HALF_SIZE);
			quotient->half_word[j] |= mask;
		}
		for(j=INT_MAX; j>=0; j--){
			if(j) mask = (e.half_word[j-1] & 1)? CARRY :0;
			else mask =0;
			e.half_word[j] = (e.half_word[j] | mask) >> 1;
		}
		n--;
		l--;

	}
	bigint_copy( &d, remainder);
}
#if 0

BSL_error ascii_to_bigint(char *instring, bigint *outhex){
	element ch;
	bigint ten, digit, temp;

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


BSL_error bigint_to_ascii(bigint *inhex, char *outstring){
	bigint top, ten, quotient, remainder;
	element check;
	short int i;
	bigint_copy(inhex, &top);
	bigint_null(&ten); /* create constant */
	ten.half_word[INT_MAX] = 0xA;
	/*blank fill and null terminate*/
	for(i =0; i< MAX_STRING; i++){ *outstring++ = ' ';}
	*outstring-- = 0;

	check = 1;
	while(check){
		bigint_div(&top, &ten, &quotient, &remainder);
		*outstring--= remainder.half_word[INT_MAX] | '0';
		check =0;
		for(i=INT_MAX; i>=0; i--){
			check |= quotient.half_word[i];
		}
		bigint_copy(&quotient, &top);
	}
}
#endif

BSL_error bigint_div2(bigint *x){
d396 9
a404 5
	for(j=INT_MAX; j>=0; j--){
		if (j){mask = (x->half_word[j-1]&1)?CARRY:0;}
		else mask =0;
		x->half_word[j] = (x->half_word[j]  | mask) >> 1;
		
a407 5
/*
from Knuth binary exponentiation, converted to mod
 462 page, vol2
z = x^n mod q
*/
a408 33
BSL_error mod_exp(bigint *x, bigint *n, bigint *q, bigint *z){
	bigint N, Y, Z, temp, dummy;
	element check;
	short int i;

	bigint_copy(n, &N);
	bigint_null(&Y);
	Y.half_word[INT_MAX] =1;
	bigint_copy(x, &Z);

	/*repeated divide N by two in each step */
	check =0;
	for(i=INT_MAX; i>=0; i--){
		check |= N.half_word[i];
	}
	while(check){
		/* if N is odd multiply by extra factor of Y*/
		if(N.half_word[INT_MAX] & 1){
			/* Y= Y*Z mod q */
			bigint_mul(&Y, &Z, &temp);
			bigint_div(&temp, q, &dummy, &Y);
		}
		bigint_div2(&N); /*N/2*/
		/*square Z, mod n*/
		bigint_mul(&Z, &Z, &temp);
		bigint_div(&temp, q, &dummy, &Z);
		check =0;
		for(i = INT_MAX; i>=0; i--){
			check |= N.half_word[i];
		}
	}
	bigint_copy(&Y, z);
}
d410 75
a484 4
/* this is a corollary of extended euclidean algorithm 
euclidean algorithm gives p,q where gcd(a,b) = pa + qb.
for inverse, gcd =1, so 1 = pa + qb. So p = inv(a) mod b.
To find a = inv(a) mod b
d487 21
a507 13
BSL_error bigint_mod_inv(bigint *a, bigint *b, bigint *x){
	bigint m, n, p0, p1, p2, q, r, temp, dummy;
	element check;
	short int sw, i;

	/*initialise for extended euclidean
	sw = 1;
	m = b;
	n = a;
	p0 = 1;
	p1 = m/n;
	q = p1;
	r = m%n; */
d509 37
a545 31
	sw =1;
	bigint_copy(b, &m);
	bigint_copy(a, &n);
	bigint_null(&p0);
	p0.half_word[INT_MAX] =1;
	bigint_div(&m, &n, &p1, &r);
	bigint_copy(&p1, &q);

	/*loop */
	check  =0;
	for(i=INT_MAX; i>=0; i--){
		check |= r.half_word[i];
	}
	while(check){
		sw = -sw;
		bigint_copy(&n, &m);
		bigint_copy(&r, &n);
		bigint_div(&m, &n, &q, &r);
		/*p2 = q * p1 + p0 % b */
		bigint_mul(&q, &p1, &temp);
		bigint_add(&temp, &p0, &temp);
		bigint_div(&temp, b, &dummy, &p2);
		bigint_copy(&p1, &p0);
		bigint_copy(&p2, &p1);
		check =0;
		for(i = INT_MAX; i>=0; i--){
			check |= r.half_word[i];
		}
	}
	if(sw <0) bigint_sub(b, &p0, x);
	else bigint_copy(&p0, x);
d548 12
a559 10

BSL_error field_to_bigint(field_2n *a, bigint *b){
	short int i,j;
	bigint_null(b);
	for(i= NUM_WORD; i >=0; i--){
		j = INT_MAX - ((NUM_WORD -i) <<1);
		b->half_word[j] = a->e[i] & LO_MASK;
		j--;
		b->half_word[j] = (a->e[i] & HI_MASK)>>HALF_SIZE;
	}
d571 1
d573 50
a622 2
int main(int argc, char **argv){
bigint test1, test2, test3, test4;
d624 1
a624 6
bigint_null(&test1);
bigint_null(&test2);
bigint_null(&test3);
bigint_null(&test4);

return 0;
a625 4




