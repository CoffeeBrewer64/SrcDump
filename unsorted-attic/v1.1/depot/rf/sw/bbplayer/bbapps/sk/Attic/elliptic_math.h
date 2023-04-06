d1 7
a7 5
/* elliptic curve operations
only deals with polynomial basis and support for 
DH and ECDSA
equation: y^2 + xy = x^3 + a x^2 + b
no point compression
d9 1
d13 3
a15 3
	field_2n a;
	field_2n b;
}CURVE;
a17 1
/*point*/
d21 1
a21 1
}POINT;
d24 7
a30 4
BSL_error poly_elliptic_mul(field_2n *k, POINT *p, POINT *r, CURVE *curv);
BSL_error poly_elliptic_sum(POINT *p1, POINT *p2, POINT *p3, CURVE *curv);
BSL_error poly_elliptic_double(POINT *p1, POINT *p2, POINT *p3, CURVE *curv);
BSL_error poly_elliptic_sub(POINT *p1, POINT *p2, POINT *p3, CURVE *curv);