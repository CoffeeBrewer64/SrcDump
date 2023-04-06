
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <time.h>

#include <algorithms.h>
#include <poly_math.h>

extern field_2n poly_prime;
extern curve named_curve;
extern point named_point;

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

#if 0
void 
Init_111_bit()
{
    named_curve.form = 0;
                                                            
 
    named_curve.a6.e[0] = 0x00007965;
    named_curve.a6.e[1] = 0x63323eab;
    named_curve.a6.e[2] = 0x10fc68f8;
    named_curve.a6.e[3] = 0x254d4d11;

    named_point.x.e[0] = 0x000018f2;
    named_point.x.e[1] = 0x9979dd24;
    named_point.x.e[2] = 0xf3814df5;
    named_point.x.e[3] = 0x5d0be8bc;

    named_point.y.e[0] = 0x000064f6;
    named_point.y.e[1] = 0xfbf7a265;
    named_point.y.e[2] = 0x37c3941b;
    named_point.y.e[3] = 0x71891f66;
    print_point("named point x ", &named_point);
}
#endif


int main(){
    field_2n private_key1, private_key2, shared_secret1, shared_secret2; 
    point public_key1, public_key2;
    field_double test;
    BbEccPrivateKey private_keyS;
    BbEccPublicKey public_keyS;
    BbEccSig eccsign;
    ec_keypair keypair;
    boolean res;
    char  input_string[1024];
    BSL_error err;
    unsigned int seed;
    unsigned long rand_input[10]; /*input for the field*/
    int i, j, same, num_bits;
    ec_parameter base;
    struct timeb tp1, tp2;
    bsl_signature sign;

    seed = getpid();
    srand(seed);

#if 0
    Init_233_bit();

    (void) ftime(&tp1);

    for(j=0; j < 1; j++){
        random_field( &private_key1, j);
        random_field( &private_key2, j+1);
    
        print_field("Private key 1", &private_key1);
        print_field("Private key 2", &private_key2);
    
  /* Generate public keys */
        err = generate_public_key(&named_point, &named_curve, &private_key1, &public_key1, 0);
    
        print_point("Public Key 1 ", &public_key1);
    
        if(err != BSL_OK){
            printf("invalid key\n");
        }

        err = generate_public_key(&named_point, &named_curve, &private_key2, &public_key2, 1);
    
        print_point("Public Key 2 ", &public_key2);
        
        if(err != BSL_OK){
            printf("invalid key\n");
        }


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

    (void) ftime(&tp2);
    printf("time for keys (s)= %d \n", tp2.time - tp1.time);

#endif

    /* test the ECDSA part */

    for(i = 0; i < 1024; i++){
        input_string[i] = rand() &0x000000ff;
    }
    /*

    num_bits = 233;
    Init_233_bit_ECDSA(&base, num_bits);
    
    rand_input[0] = 0x7d;
    rand_input[1] = 0xbaf7930d;
    rand_input[2] = 0x3c21e169;
    rand_input[3] = 0xa860ceee;
    rand_input[4] = 0xb095e685;
    rand_input[5] = 0x43c6fffc;
    rand_input[6] = 0xdfd321ae;
    rand_input[7] = 0x7f26cc47;
        
    poly_key_gen_primitive(&base, &keypair, rand_input);

    rand_input[0]=0x00000054;
    rand_input[1]=0x168840de;
    rand_input[2]=0x1eed3f73;
    rand_input[3]=0x72a39b78;
    rand_input[4]=0x02215231;
    rand_input[5]=0x31421fb8;
    rand_input[6]=0x8790e1be;
    rand_input[7]=0xe5f8a4e5;

    poly_ECDSA_signature(input_string, 1024, &base, &(keypair.private_key), &sign, rand_input);

    print_field("Sign c ", &(sign.c));
    print_field("Sign d ", &(sign.d));

    poly_DSA_verify(input_string, 1024, &base, &(keypair.public_key), &sign, &res);
    
    */
    
     
    private_keyS[0] = 0x7d;
    private_keyS[1] = 0xbaf7930d;
    private_keyS[2] = 0x3c21e169;
    private_keyS[3] = 0xa860ceee;
    private_keyS[4] = 0xb095e685;
    private_keyS[5] = 0x43c6fffc;
    private_keyS[6] = 0xdfd321ae;
    private_keyS[7] = 0x7f26cc47;
        
       
    rand_input[0]=0x00000054;
    rand_input[1]=0x168840de;
    rand_input[2]=0x1eed3f73;
    rand_input[3]=0x72a39b78;
    rand_input[4]=0x02215231;
    rand_input[5]=0x31421fb8;
    rand_input[6]=0x8790e1be;
    rand_input[7]=0xe5f8a4e5;

    computeEccSig(input_string, 1024, private_keyS, rand_input, eccsign, 0);
    
    for(i =0; i< 16; i++){
        printf(" sign = %08x\n", eccsign[i]);
    }

    eccGenPublicKey(public_keyS, private_keyS);
    verifyEccSig(input_string, 1024, public_keyS, eccsign, &res, 0);
    

    if(res == BSL_TRUE){
        printf("sign verified\n");
    }
    else{
        printf("sign not verified\n");
    }
        

    return 0;
}


