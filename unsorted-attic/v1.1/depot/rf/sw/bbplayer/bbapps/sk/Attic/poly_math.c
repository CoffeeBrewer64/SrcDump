d6 3
d34 1
a34 1
    bit = (*eptr & MSB) ? IL: 0L;
d71 2
a72 2
BSL_error 
double_null(double_field * a)
d87 1
a87 1
 * BSL_error 
d94 2
a95 2
BSL_error 
double_add(double_field *a, double_field *b, double_field *c)
d119 1
a119 1
double_swap(double_field *a, double_field *b)
d121 2
a122 1
  double_field temp;
d126 19
a144 4
  double_null(&temp);
  double_copy(a, &temp);
  double_copy(b, a);
  double_copy(&temp, b);
d159 1
a159 1
BSL_error 
d183 1
a183 1
double_copy(double_field *from, double_field *to)
d204 1
a204 1
double_is_one(double_field *a, bool *result)
d207 1
d211 2
a212 2
  *result =true;
  double_field one;
d219 1
a219 1
      *result = false;
d235 1
a235 1
single_to_double(field_2n *from, double_field *to)
d245 1
d257 1
a257 1
double_to_single(double_field *from, field_2n *to)
d266 1
d278 1
a278 1
poly_mul_partial(field_2n *a, field_2n *b, double_field *c)
d282 1
a282 1
  double_field local_b;
d309 1
d312 1
d319 1
a319 1
BSL_error divide_shift(double_field *a){
d335 1
a335 1
BSL_error shift_bit_n(double_field *a, int n){
d353 1
a353 1
BSL_error extract_mask(double_field * a, double_field *mask, double_field *result){
d362 1
a362 1
BSL_error zero_masked_bits(double_field *a, double_field *mask, double_field *result){
d451 36
a486 34
	double_field U, V;
	double_field temp, temp1;
	bool res;
	double_field B, C; /* later copy to single field b */
	null(&U);
	null(&V);
	null(&B);
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
				else{
					/*b = b + f*/
					single_to_double(&temp, &poly_prime);
					double_add(&B, &temp, &temp1);
					double_copy(&temp1, &B);
				}
			}
		}
		double_is_one(&U, &res);
		if (res == true){
			double_to_single(&B, b);
		return BSL_OK;
		}
d488 242
a729 13
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
d733 67
