/* 
 * elliptic_math.c 
 * common operations for elliptic curve, polynomial basis
 * only, all thats needed for elliptic multiplication
*/
#include <stdio.h>
#include "integer_math.h"
#include "binary_field.h"
#include "poly_math.h"
#include "elliptic_math.h"



/* 
 * BSL_error 
 * copy_point() 
 * Purpose: to copy one big integer to another: copy p1 into p2
 * inputs: pointer to allocated points
 */

BSL_error
copy_point(point *p1, point *p2)
{
  copy(&p1->x, &p2->x); /*field_2n copy*/
  copy(&p1->y, &p2->y); 
  return BSL_OK;
}

/* 
 *debugging printing routines to print field variables and elliptic curves
 */

BSL_error
print_field(char *string, field_2n *field){
  short int i;
  printf("%s : ", string);
  for(i=0; i < MAX_LONG; i++){
    printf(" %08x ", (unsigned int) field->e[i]);
  }
  printf("\n");
  return BSL_OK;
}

BSL_error
print_point(char *string, point *point)
{
  printf("%s\n", string);
  print_field("x", &point->x);
  print_field("y", &point->y);
  printf("\n");
  return BSL_OK;
}

BSL_error
print_curve(char *string, curve *curv)
{
  printf("%s\n", string);
  printf("form = %d\n", curv->form);
  if (curv->form) print_field("a2", &curv->a2);
  print_field("a6", &curv->a6);
  printf("\n");
  return BSL_OK;
}

  

/* 
 * BSL_error 
 * poly_elliptic_sum() 
 * polynomial elliptic sum from schroeppel's paper
 * point at infinity is represented by (0,0) 
 * purpose: p3 = p1 + p2
 */


BSL_error 
poly_elliptic_sum(point *p1, point *p2, point *p3, curve *curv)
{
  short int i;
  field_2n x1, y1, lambda, onex, lambda2;
  element check;

  /*check if either point is at infinity*/
  check = 0;
  for(i = 0; i < MAX_LONG; i++){
    check |= p1->x.e[i] | p1->y.e[i];
  }
  /*point x is at infinity?*/
  if(!check){ 
    copy_point(p2, p3);
    return BSL_OK;
  }
  check =0;
  for(i = 0; i < MAX_LONG; i++){
    check |= p2->x.e[i] | p2->y.e[i];
  }
  /*point y is at infinity? */
  if(!check){
    copy_point(p1, p3);
    return BSL_OK;
  }

  /* check if we are doubling! special equations*/
  check =0;
  for(i = 0; i < MAX_LONG; i++){
    if((p1->x.e[i] != p2->x.e[i])||(p1->y.e[i] != p2->y.e[i])){
      check =1;
    }
  }
  if (check != 1){ /* all equal: call doubling*/
    poly_elliptic_double(p1, p3, curv);
    return BSL_OK;
  }

  /* compute lambda, this is not doubling, so if 
   * denominator is zero, exit now with point at infinity
   */
  null(&x1);
  null(&y1);
  check =0;
  for(i=0; i< MAX_LONG; i++){
    x1.e[i] = p1->x.e[i] ^ p2->x.e[i];
    y1.e[i] = p1->y.e[i] ^ p2->y.e[i];
    /*anyway compute x + y*/
    check |= x1.e[i];
  }
  if(!check) {
    null(&p3->x);
    null(&p3->y);
    return BSL_OK;
  }

  poly_inv(&x1, &onex);
  poly_mul(&onex, &y1, &lambda);
  poly_mul(&lambda, &lambda, &lambda2);

  /* compute x3*/
  if(curv->form){ /*x^3 + ax^2 + b*/
    for(i=0; i< MAX_LONG; i++){
      p3->x.e[i]  = lambda.e[i] ^ lambda2.e[i] ^ x1.e[i] ^ curv->a2.e[i];
    }
  }
  else{
    for(i=0; i< MAX_LONG; i++){
      p3->x.e[i]  = lambda.e[i] ^ lambda2.e[i] ^ x1.e[i]; /* no a*/
    }
  }
  
  /* y3*/
  for(i=0; i< MAX_LONG; i++){
    x1.e[i] = p1->x.e[i] ^ p3->x.e[i];
  }
  poly_mul(&x1, &lambda, &lambda2);
  for(i=0; i< MAX_LONG; i++){
    p3->y.e[i] = lambda2.e[i] ^ p3->x.e[i] ^ p1->y.e[i];
  }
  return BSL_OK;
}


/* 
 * BSL_error 
 * poly_elliptic_double() 
 * polynomial elliptic double from schroeppel's paper
 * point at infinity is represented by (0,0) 
 * purpose: p3 = p1 + p1
 */

BSL_error 
poly_elliptic_double(point *p1, point *p3, curve *curv)
{
  field_2n x1, y1, lambda, lambda2, t1;
  short int i;
  element check;

  check =0; 
  /* check if input is zero*/
  for(i=0; i< MAX_LONG; i++){
    check |= p1->x.e[i];
  }
  if(!check){
    null(&p3->x);
    null(&p3->y);
    return BSL_OK;
  }
  
  
  /*lambda = x + y/x*/
  poly_inv(&p1->x, &x1);
  
  poly_mul(&x1, &p1->y, &y1);
  

  /*add to x*/
  for(i =0; i< MAX_LONG; i++){
    lambda.e[i] = p1->x.e[i] ^ y1.e[i];
  }
  
  /* x3*/
  poly_mul(&lambda, &lambda, &lambda2);
  if(curv->form){
    for(i = 0; i< MAX_LONG; i++){
      p3->x.e[i] = lambda.e[i] ^ lambda2.e[i] ^ curv->a2.e[i];
    }
  }
  else{
    for(i = 0; i< MAX_LONG; i++){
      p3->x.e[i] = lambda.e[i] ^ lambda2.e[i];
    }
  }
  /*y3*/
  lambda.e[NUM_WORD] ^= 1; /*add 1*/
  poly_mul(&lambda, &p3->x, &t1);
  poly_mul(&p1->x, &p1->x, &x1);
  for(i =0; i< MAX_LONG; i++){
    p3->y.e[i] = x1.e[i] ^ t1.e[i];
  }
  return BSL_OK;
}



/* 
 * BSL_error 
 * poly_elliptic_sub() 
 * 
 * point at infinity is represented by (0,0) 
 * purpose: p3 = p1 - p2
 * subtracting two points by negate and add
 * rule for negating: -1(x, y) = (x, x+y)
 */

BSL_error 
poly_elliptic_sub(point  *p1, point *p2, point *p3, curve *curv){
  point temp;
  short int i;
  copy(&p2->x, &temp.x);
  null(&temp.y);
  for(i=0; i < MAX_LONG; i++){
    temp.y.e[i] = p2->x.e[i] ^ p2->y.e[i];
  }
  poly_elliptic_sum(p1, &temp, p3, curv);
  return BSL_OK;
}




/* 
 * BSL_error 
 * poly_elliptic_mul() 
 * 
 * point at infinity is represented by (0,0) 
 * purpose: p3 = k * p2 where k is an integer
 * multiplication using balanced representation: check Solinas
 * paper: an improved algorithm for arithmetic on a family of 
 * elliptic curves
 */

BSL_error 
poly_elliptic_mul(field_2n *k, point *p, point *r, curve *curv)
{
  char balanced[NUM_BITS + 1];
  short int i, bit_count;
  element notzero;
  field_2n number;
  point temp;

  
  /* check for multiplier zero, if so return point at inf */
  copy (k, &number);
  notzero =0;
  for(i=0; i< MAX_LONG; i++){
    notzero |= number.e[i];
  }
  if(!notzero){
    null(&r->x);
    null(&r->y);
    return BSL_OK;
  }
  /* find balanced representation: need reference */

  bit_count =0;
  while(notzero){
    /* if number odd, create 1 or -1 from last two bits */
    if(number.e[NUM_WORD] & 1){
      balanced[bit_count] = 2  - (number.e[NUM_WORD] & 3);
      /* if -1, add 1 and propogate carry bit */
      if(balanced[bit_count] < 0){
	for(i= NUM_WORD; i >= 0; i--){
	  number.e[i]++;
	  if(number.e[i]) break;
	}
      }
    }
    else{
      balanced[bit_count] = 0;
    }
    number.e[NUM_WORD] &= ~0 << 1;
    poly_rot_right(&number);
    bit_count++;
    notzero =0; 
    for(i =0; i< MAX_LONG; i++){
	notzero |= number.e[i];
    }
  }

  /* now compute kP*/
  bit_count--;
  copy_point(p, r);
  
  while(bit_count >0){
    
    poly_elliptic_double(r, &temp, curv);
    
    bit_count--;
    switch(balanced[bit_count]){
    case 1:   
      poly_elliptic_sum(p, &temp, r, curv); 
      break;
    case -1: 
      poly_elliptic_sub(&temp, p, r, curv); 
      break;
    case 0: copy_point(&temp, r);

    }
  }

  
  return BSL_OK;
}


	


	






