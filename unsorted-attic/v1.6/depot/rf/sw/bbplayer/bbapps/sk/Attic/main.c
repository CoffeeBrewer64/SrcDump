#include <stdio.h>
#include <unistd.h>
#include "algorithms.h"
#include "poly_math.h"

extern field_2n poly_prime;
void random_field(field_2n *value)
{
	short int i;
	for(i = 0; i< MAX_LONG; i++){
	 	value->e[i] = rand();
	}
	value->e[0] &= UPR_MASK;
}

curve named_curve;
point named_point;

void 
Init_111_bit()
{
named_curve.form = 0;
  /*
  named_curve.a6 = {0x00007965, 0x63323eab, 0x10fc68f8, 0x254d4d11};
  */
  named_curve.a6.e[0] = 0x00007965;
  named_curve.a6.e[1] = 0x63323eab;
  named_curve.a6.e[2] = 0x10fc68f8;
  named_curve.a6.e[3] = 0x254d4d11;

  
  /*
  named_point.x = {0x000018f2, 0x9979dd24, 0xf3814df5, 0x5d0be8bc};
  */
  named_point.x.e[0] = 0x000018f2;
  named_point.x.e[1] = 0x9979dd24;
  named_point.x.e[2] = 0xf3814df5;
  named_point.x.e[3] = 0x5d0be8bc;
  /*
  named_point.y = {0x000064f6, 0xfbf7a265, 0x37c3941b, 0x71891f66};
  */
  named_point.y.e[0] = 0x000064f6;
  named_point.y.e[1] = 0xfbf7a265;
  named_point.y.e[2] = 0x37c3941b;
  named_point.y.e[3] = 0x71891f66;
  print_point("named point x ", &named_point);
}

void 
Init_233_bit()
{
named_curve.form = 0;
  /*
  named_curve.a6 = {0x66, 0x647ede6c, 0x332c7f8c, 0x0923bb58, 0x213b333b, 20e9ce42, 0x81fe115f, 0x7d8f90ad};
  */
  named_curve.a6.e[0] = 0x66;
  named_curve.a6.e[1] = 0x647ede6c;
  named_curve.a6.e[2] = 0x332c7f8c;
  named_curve.a6.e[3] = 0x0923bb58;
  named_curve.a6.e[4] = 0x213b333b;
  named_curve.a6.e[5] = 0x20e9ce42;
  named_curve.a6.e[6] = 0x81fe115f;
  named_curve.a6.e[7] = 0x7d8f90ad;

  /*
  named_point.x = {0x0fa, 0xc9dfcbac, 0x8313bb21, 0x39f1bb75, 0x5fef65bc, 0x391f8b36, 0xf8f8eb73, 0x71fd558b};
  */
  named_point.x.e[0] = 0x0fa;
  named_point.x.e[1] = 0xc9dfcbac;
  named_point.x.e[2] = 0x8313bb21;
  named_point.x.e[3] = 0x39f1bb75;
  named_point.x.e[4] = 0x5fef65bc;
  named_point.x.e[5] = 0x391f8b36;
  named_point.x.e[6] = 0xf8f8eb73;
  named_point.x.e[7] = 0x71fd558b;
  /*
  named_point.y = {0x100, 0x6a08a419, 0x03350678, 0xe58528be, 0xbf8a0bef, 0xf867a7ca, 0x36716f7e, 0x01f81052};
  */
  named_point.y.e[0] = 0x100;
  named_point.y.e[1] = 0x6a08a419;
  named_point.y.e[2] = 0x03350678;
  named_point.y.e[3] = 0xe58528be;
  named_point.y.e[4] = 0xbf8a0bef;
  named_point.y.e[5] = 0xf867a7ca;
  named_point.y.e[6] = 0x36716f7e;
  named_point.y.e[7] = 0x01f81052;

  
}


int main(){
  field_2n private_key1, private_key2, shared_secret1, shared_secret2; 
  point public_key1, public_key2;
  BSL_error err;
  unsigned int seed;
  int i, j, same;
  seed = getpid();
  srand(seed);

  print_field("poly_prime   ", &poly_prime);
  /*
  Init_111_bit();
  */
  Init_233_bit();
  for(j=0; j < 10; j++){
    random_field( &private_key1);
    random_field( &private_key2);
  /*
  print_curve("curve  ", &named_curve);
  print_point("point ", &named_point);
  */
  /*
  private_key1.e[0] = 0x00007cdb;
  private_key1.e[1] = 0x91edee60;
  private_key1.e[2] = 0x4da6d486;
  private_key1.e[3] = 0x295d85ac;

  private_key2.e[0] = 0x00003edd;
  private_key2.e[1] = 0x3a0f94f6;
  private_key2.e[2] = 0xe0caf9a7;
  private_key2.e[3] = 0x2d189f04;
  */
    print_field("Private key 1", &private_key1);
    print_field("Private key 2", &private_key2);

  /* Generate public keys */
    err = generate_public_key(&named_point, &named_curve, &private_key1, &public_key1);
  
    print_point("Public Key 1 ", &public_key1);
  
    err = generate_public_key(&named_point, &named_curve, &private_key2, &public_key2);
  
    print_point("Public Key 2 ", &public_key2);
  
  
  /* Generate shared secret on both sides */
    err = generate_shared_key(&named_point, &named_curve, &public_key2, &private_key1, &shared_secret1);
    print_field("Shared Key 1 ", &shared_secret1);

    err = generate_shared_key(&named_point, &named_curve, &public_key1, &private_key2, &shared_secret2);
    print_field("Shared Key 2 ", &shared_secret2);

    same = 0;
    for(i =0 ; i <MAX_LONG; i++){
      if(shared_secret1.e[i] != shared_secret2.e[i]){
	same = 1;
      }
    }
    if(same ==0){
      printf("OK %d\n", j);
    }
    else{
    printf("NOT OK %d\n", j);
    }
  }
  return 0;
}
