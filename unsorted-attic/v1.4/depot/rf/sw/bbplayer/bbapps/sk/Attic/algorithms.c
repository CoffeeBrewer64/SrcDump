/* 

*/

#include "elliptic_math.h"

#include "integer_math.h"
#include "algorithms.h"



/* generate public key: need to move to server code */

BSL_error 
generate_public_key(point *base_point, curve *E, field_2n *my_private, point *my_public)
{
  BSL_error err;
  err = poly_elliptic_mul(my_private, base_point, my_public, E);
  if(err != BSL_OK){
    return err;
  }
  /*
  print_point("public = ", my_public);
  */
  /* do validation here */
  return BSL_OK;
}

/* generate ECDH shared key */

BSL_error 
generate_shared_key(point *base_point, curve *E, point *recipient_public, field_2n *my_private, field_2n *shared_secret)
{
  point tmp;
  BSL_error err;
  err = poly_elliptic_mul(my_private, recipient_public, &tmp, E);
  if (err != BSL_OK){
    return err;
  }
  copy(&tmp.x, shared_secret);
  /* print_field("shared = ",  shared_secret);
   */
  return BSL_OK;
}

#if 0
/* generate random key pair, needed for ECDSA*/
/* inputs random number: replace with one from hardware*/
BSL_error poly_key_gen_primitive(EC_PARAMETER *Base, EC_KEY_PAIR *key){
	bigint key_num, point_order, quotient, remainder;
	field_2n random_key;

	/* make sure random is less than point order */
	random_field(&random_key); /* this gets from hardware. simulate for now */
	field_to_int(&random_key, &key_num);
	field_to_int(&Base->point_order, &point_order);
	integer_div(&key_num, &point_order, &quotient, &remainder);
	integer_to_field(&remainder, &key->private_key);

	poly_elliptic_multiply(&key->private_key, &Base->point, &Key->public_key, &Base->curve);
	return BSL_OK;

}



/* SHA hash to integer */
BSL_error hash_to_integer(char *message, unsigned long length, bigint *hash_value){
	unsigned char MessageDigest[5]; /*from SHA*/
	field_2n tmp;
	short int i, count, err;
	SHA1Context sha;

	err = SHA1Reset(&sha);
	if(err){
	  return BSL_SHA_ERROR;
	}
	err = SHA1Input(&sha, (const unsigned char *)message, strlen(message));
	if(err){
	  return BSL_SHA_ERROR;
	}
	err = SHA1Result(&sha, MessageDigest);
	if(err){
	  return BSL_SHA_ERROR;
	}

	/* replace with uppermost sha call */
	/*
	sha_memory(message, length, MessageDigest);
	*/
	
	bigint_null(&tmp);
	count=0;

	for(i=0; i< MAX_LONG; i++){
		tmp.e[NUM_WORD-i]= MessageDigest[4-i];
		count++;
		if(count >4) break;
	}
	tmp.e[0] &= UPR_MASK;
	field_to_bigint(&tmp, hash_value);
	return BSL_OK;
}

/* this is algorithm for ECDSA, enter with message pointer, size, 
private key, and get signature: two points */

BSL_error poly_ECDSA_signature(char *message, unsigned long length, EC_PARAMETER *public_curve, field_2n *private_key, SIGNATURE *signature){

	bigint hash_value, x_value, k_value, sig_value;
	bigint c_value, temp, quotient;
	bigint key_value, point_order, u_value;
	EC_KEYPAIR random_key;


	hash_to_integer(message, length, &hash_value);
	poly_key_gen_primitive(public_curve, &random_key);

	field_to_bigint(&public_curve->point_order, &point_order);
	field_to_bigint(&random_key.public_key.x, &x_value);
	bigint_div(&x_value, &point_order, &quotient, &c_value);
	bigint_to_field(&c_value, &signature->c);

	/* hash + priv key *c_value*/
	field_to_bigint(&private_key, &key_value);
	bigint_mul(&key_value, &c_value, &temp);
	bigint_add(&temp, &hash_value, &temp);
	bigint_div(&temp, &point_order, &quotient, &k_value);

	/* multiply by inv of random key mod order of base point */
	field_to_bigint(&random_key.private_key, &temp);
	bigint_mod_inv(&temp, &point_order, &u_value);
	bigint_mul(&u_value, &k_value, &temp);
	bigint_div(&temp, &point_order, &quotient, &sig_value);
	bigint_to_field(&sig_value, &signature->d);

	return BSL_OK;
}

/*verify ECDSA 1:verifies, 0: not verifies*/
BSL_error poly_DSA_verify(char *message, unsigned long length, EC_PARAMETER *public_curve, POINT *signer_point, SIGNATURE *signature, boolean *result){

	bigint hash_value, c_value, d_value;
	bigint temp, quotient, h1, h2, check_value, point_order;
	POINT Temp1, Temp2, Verify;
	short int i;
	field_2n h1_field, h2_field;

	/*compute inv of second value */
	field_to_bigint(&public_curve->point_order, &point_order);
	field_to_bigint(&signature->d, &temp);
	bigint_mod_inv(&temp, &point_order, &d_value);

	/*generate hash */
	hash_to_integer(message, length, &hash_value);

	/*compute h1, h2*/
	bigint_mul(&hash_value, &d_value, &temp);
	bigint_div(&temp, &point_order, &quotient, &h1);
	bigint_to_field(&h1, &h1_field);
	field_to_bigint(&signature->c, &c_value);
	bigint_mul(&d_value, &c_value, &temp);
	bigint_div(&temp, &point_order, &quotient, &h2);
	bigint_to_field(&h2, &h2_field);

	/*find hidden  point from public data */
	poly_elliptic_multiply(&h1_field, &public_curve->point, &Temp1, &public_curve->curve);
	poly_elliptic_multiply(&h2_field, signer_point, &Temp2, &public_curve->curve);
	poly_elliptic_sum(&Temp1, &Temp2, &Verify, &public_curve->curve);

	/*convert x value */
	field_to_bigint(&Verify.x, &temp);
	bigint_div(&temp, &point_order, &quotient, &check_value);

	/*compare */
	bigint_sub(&c_value, &check_value, &temp);
	while(temp.half_word[0] & 0x8000)
		bigint_add(&point_order, &temp, &temp);

	*result = TRUE;
	for(i= INT_MAX; i>=0; i--){
		if(temp.half_word[i]) *result = FALSE;
	}

	return BSL_OK;
}
	
#endif
