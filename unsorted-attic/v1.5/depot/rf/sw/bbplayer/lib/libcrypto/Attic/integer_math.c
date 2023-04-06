d9 1
d11 23
d154 3
a156 3
	bigint_null(c, int_max);
 
	
d193 2
d307 1
a307 1
#if 0
d313 1
d318 1
a318 1
ascii_to_bigint(char *instring, bigint *outhex)
d325 1
a325 1
    bigint_null(&ten);
d327 2
a328 2
    bigint_null(&digit);
    bigint_null(outhex);
d332 1
a332 1
        bigint_mul(outhex, &ten, &temp);
d334 1
a334 1
        bigint_add(&temp, &digit, outhex);
d351 1
a351 1
bigint_to_ascii(bigint *inhex, char *outstring)
d359 1
a359 1
    bigint_copy(inhex, &top);
d362 1
a362 1
    bigint_null(&ten);
d366 1
a366 1
    for(i = 0; i< MAX_STRING; i++){ 
d370 1
d375 1
a375 1
        bigint_div(&top, &ten, &quotient, &remainder);
d381 1
a381 1
        bigint_copy(&quotient, &top);
d386 1
a386 1
#endif
d570 9
a578 1

d634 1
a634 1
#if 0
d642 1
a642 1
  bigint_null(b, int_max);
a652 1
#endif
d654 14
a667 7
#if 0
BSL_error bigint_to_field(bigint *a, field_2n *b){
	short int i,j;
	for(i=INT_MAX; i>=0; i--){
		j = (i + MAX_LONG)<<1;
		b->e[i] = a->half_word[j+1] | (a->half_word[j] << HALF_SIZE);
	}
a670 1
#endif
d808 1
a809 6

#if 0
/* high level function for RSA verify 
 * n and e are modulus and exponent, sign is input, result is output, 
 * num_bits is bit length for RSA operations 
 */
a814 1
    int i;
a818 2


a945 19



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
