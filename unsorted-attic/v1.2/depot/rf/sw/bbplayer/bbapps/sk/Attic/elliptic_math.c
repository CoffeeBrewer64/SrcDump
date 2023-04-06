d103 1
a103 1
      check ==1;
d136 1
a136 1
      p3->x.e[i]  = lambda.e[i] ^ lambda2.e[i] ^ p1->x.e[i] ^ p2->x.e[i] ^ curv->a2.e[i];
d141 1
a141 1
      p3->x.e[i]  = lambda.e[i] ^ lambda2.e[i] ^ p1->x.e[i] ^ p2->x.e[i]; /* no a*/
d153 1
d183 1
d186 1
d188 2
d265 1
d307 1
d309 1
d311 1
d314 2
a315 1
    case 1: poly_elliptic_sum(p, &temp, r, curv); 
d317 2
a318 1
    case -1: poly_elliptic_sub(&temp, p, r, curv); 
d324 3
