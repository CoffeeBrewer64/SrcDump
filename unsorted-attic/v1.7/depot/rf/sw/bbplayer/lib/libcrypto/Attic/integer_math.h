d54 3
d59 4
a62 4
/*
BSL_error field_to_bigint(int num_bits);
BSL_error bigint_to_field();
*/
d68 2
a69 2
BSL_error ascii_to_bigint(char *instring, bigint *outhex);
BSL_error bigint_to_ascii(bigint *inhex, char *outstring);
d75 3
a80 3
void bigint_to_certint(unsigned long *certfmt, int certfmtwords, bigint *b, int int_max);
void certint_to_bigint( bigint *b, int int_max, unsigned long *certfmt, int certfmtwords);

