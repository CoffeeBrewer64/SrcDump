d1 2
a2 2
/* this has implementation of ECDSA and EC Shared key computation
- has to work with AES to do ecnryption
a4 2
#include "binaryfield.h"
#include "poly_math.h"
d6 1
d8 2
a10 2
#if 0
extern field_2n poly_prime;
d14 13
a26 2
BSL_error generate_public_key(POINT *base_point, CURVE *E, field_2n *my_private, POINT *my_public){
	return poly_elliptic_multiply(my_private, base_point, my_public, E);
d29 1
a29 1
/* generate shared key for DH */
d31 13
a43 5
BSL_error generate_shared_key(POINT *base_point, CURVE *E, POINT *recipient_public, field_2n *my_private, field_2n *shared_secret){
	POINT tmp;
	poly_elliptic_multiply(my_private, recipient_public, &tmp, E);
	copy(&tmp.x, shared_secret);
	return BSL_OK;
d46 1
d58 1
a58 1
	integer_to_field(&remainder, &Key->private_key);
d60 1
a60 1
	poly_elliptic_multiply(&Key->private_key, &Base->point, &Key->public_key, &Base->curve);
d65 2
d68 2
a69 2
BSL_error hash_to_integer(char *message, unsigned long length, big_integer *hash_value){
	unsigned long MessageDigest[5]; /*from SHA*/
d71 15
a85 1
	short int i, count;
d88 1
d90 3
a92 1
	null(&tmp);
d95 1
a95 2
	/* convert to integer :CHECK THIS HARD CODED 4!*/
	for(i=0; i< MAXLONG; i++){
d100 3
a102 2
	tmp.e[0] &= UPRMASK;
	field_to_integer(&tmp, hash_value);
d110 3
a112 3
	big_integer hash_value, x_value, k_value, sig_value;
	big_integer c_value, temp, quotient;
	big_integer key_value, point_order, u_value;
d114 1
a114 1
	short int i, count;
d119 4
a122 4
	field_to_integer(&public_curve->point_order, &point_order);
	field_to_integer(&random_key.public_key.x, &x_value);
	integer_div(&x_value, &point_order, &quotient, &c_value);
	integer_to_field(&c_value, &signature->c);
d125 4
a128 4
	field_to_integer(&private_key, &key_value);
	integer_multiply(&key_value, &c_value, &temp);
	integer_add(&temp, &hash_value, &temp);
	integer_divide(&temp, &point_order, &quotient, &k_value);
d131 7
a137 5
	field_to_integer(&random_key.private_key, &temp);
	mod_inv(&temp, &point_order, &u_value);
	integer_multiply(&u_value, &k_value, &temp);
	integer_divide(&temp, &point_order, &quotient, &sig_value);
	integer_to_field(&sig_value, &signature->d);
d141 1
a141 1
BSL_error poly_DSA_verify(char *message, unsigned long length, EC_PARAMETER *public_curve, POINT *signer_point, SIGNATURE *signature, bool *result){
d146 1
a146 1
	short int i, count;
d150 3
a152 3
	field_to_int(&public_curve->point_order, &point_order);
	field_to_int(&signature->d, &temp);
	mod_inv(&temp, &point_order, &d_value);
d155 1
a155 1
	hash_to_int(message, length, &hash_value);
d158 7
a164 7
	integer_multiply(&hash_value, &d_value, &temp);
	integer_div(&temp, &point_order, &quotient, &h1);
	integer_to_field(&h1, &h1_field);
	field_to_integer(&signature->c, &c_value);
	integer_multiply(&d_value, &c_value, &temp);
	integer_divide(&temp, &point_order, &quotient, &h2);
	integer_to_field(&h2, &h2_field);
d172 2
a173 2
	field_to_integer(&Verify.x, &temp);
	integer_div(&temp, &point_order, &quotient, &check_value);
d176 1
a176 1
	integer_sub(&c_value, &check_value, &temp);
d178 1
a178 1
		integer_add(&point_order, &temp, &temp);
d182 1
a182 1
		if(temp.half_word[i]) *result = false;
