d29 1
a29 1
#define MAX_MAX_LONG 129
a53 3

void random_field(field_2n *value, unsigned int seed);

d56 4
a59 4

BSL_error field_to_bigint(field_2n *a, bigint *b, int num_bits);
BSL_error bigint_to_field(bigint *a, field_2n *b, int num_bits);

d65 2
a66 2
BSL_error ascii_to_bigint(char *instring, bigint *outhex, int int_max);
BSL_error bigint_to_ascii(bigint *inhex, char *outstring, int int_max, int size);
a71 4
void bigint_to_certint(unsigned long *certfmt, int certfmtwords, bigint *b, int int_max);
void certint_to_bigint( bigint *b, int int_max, unsigned long *certfmt, int certfmtwords);

/*
a72 3
*/
BSL_error bsl_rsa_verify(char *result, unsigned long *certsign, unsigned long *certpublickey, unsigned long *exponent,  int num_bits);

