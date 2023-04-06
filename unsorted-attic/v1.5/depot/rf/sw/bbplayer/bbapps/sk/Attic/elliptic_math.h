/* 
 * elliptic_math.h
 * elliptic curve operations
 * only deals with polynomial basis and support for 
 * DH and ECDSA
 * equation: y^2 + xy = x^3 + a x^2 + b
 * no point compression
*/
#include "integer_math.h"
#include "binary_field.h"

#ifndef ELLIPTIC_MATH_H
#define ELLIPTIC_MATH_H

typedef struct {
	short int form;
	field_2n a2;
	field_2n a6;
}curve;


typedef struct {
	field_2n x;
	field_2n y;
}point;


BSL_error copy_point(point *p1, point *p2);
BSL_error print_field(char *string, field_2n *field);
BSL_error print_point(char *string, point *point);
BSL_error poly_elliptic_mul(field_2n *k, point *p, point *r, curve *curv);
BSL_error poly_elliptic_sum(point *p1, point *p2, point *p3, curve *curv);
BSL_error poly_elliptic_double(point *p1, point *p3, curve *curv);
BSL_error poly_elliptic_sub(point *p1, point *p2, point *p3, curve *curv);

#endif
