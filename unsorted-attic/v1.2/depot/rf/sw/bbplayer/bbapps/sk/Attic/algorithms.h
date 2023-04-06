/* 
 *
 * algorithms.h
 * algorithm prototypes.
 *
 */

#include "binary_field.h"
#include "integer_math.h"
#include "poly_math.h"
#include "elliptic_math.h"

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#if 0
typedef struct {
  field_2n c;
  field_2n d;
}SIGNATURE;


typedef struct {
  field_2n private_key;
  POINT public_key;
}EC_KEYPAIR;

typedef struct {
  CURVE curve;
  POINT point;
  field_2n point_order;
  field_2n cofactor;
}EC_PARAMETER;
  
BSL_error poly_ECDSA_signature(char *, unsigned long, EC_PARAMETER *, field_2n *, SIGNATURE *);
#endif


BSL_error generate_public_key(point *base_point, curve *E, field_2n *my_private, point *my_public);


BSL_error generate_shared_key(point *base_point, curve *E, point *recipient_public, field_2n *my_private, field_2n *shared_secret);

#endif
