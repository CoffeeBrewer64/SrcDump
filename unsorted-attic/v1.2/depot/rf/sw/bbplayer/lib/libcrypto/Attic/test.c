#include <stdlib.h>
#include "integer_math.h"
#include "poly_math.h"
#include "elliptic_math.h"



#define DEV_CNSLE_TX_INTR            0x01 /* intr enable / state bits */
#define DEV_CNSLE_RX_INTR            0x02
 
typedef unsigned int DevRegister;
typedef struct DevConsoleRegisters {
	DevRegister intr_status;      /* r: intr state / w: intr enable */
	DevRegister data;             /* r: current char / w: send char */
} DevConsoleRegisters;

#define K1BASE	(0xA0000000)



unsigned int myrand(unsigned int seed);
void random_field(field_2n *value, unsigned int seed);

extern curve named_curve;
extern point named_point;

main(int argc, char* argv) {
    volatile DevConsoleRegisters* console = (DevConsoleRegisters*)(K1BASE+0x01e01000);
    int i, iter = 0;
    int result = 0;
    int same = 0;
    BSL_error err;
    const char* ps = "pass\r\n";
    const char* fs = "fail\r\n";
    const char* ts = "terminated\r\n";
    char* p;

    bigint a, b, c, d, dummy;
    field_2n temp;
    field_2n field_a, field_b, field_c, field_d;
    field_2n private_key1, private_key2, shared_secret1, shared_secret2; 
    point public_key1, public_key2;

/* 
 * test code for integer functions
 */

    bigint_null(&a);
    bigint_null(&b);
    bigint_null(&c);
    bigint_null(&d);
    /* initialize from random fields */
    random_field(&temp, 1234);
    field_to_bigint(&temp, &a);
    random_field(&temp, 4567);
    field_to_bigint(&temp, &b);
        
    if(bigint_add(&a, &b, &c) != BSL_OK){
        for(p = ts; *p; p++) {
            console->data = *p;
        }
    }
    if(bigint_sub(&c, &a, &d) != BSL_OK){
        for(p = ts; *p; p++) {
            console->data = *p;
        }
    }


    result = 1;
    for(i = INT_MAX; i >= 0; i--){
        if(b.half_word[i] != d.half_word[i]){
            result = 0;
        }
    }
    if(result == 1){
        for(p = ps; *p; p++) {
            console->data = *p;
        }
    }

    else{
        for(p = fs; *p; p++) {
            console->data = *p;
        }
    }
    
    if(bigint_mul(&a, &b, &c) != BSL_OK){
        for(p = ts; *p; p++) {
            console->data = *p;
        }
    }
    bigint_null(&d);
    bigint_null(&dummy);
    if(bigint_div(&c, &a, &d, &dummy) != BSL_OK){
        for(p = ts; *p; p++) {
            console->data = *p;
        }
    }

    
    result = 1;
    
    for(i = INT_MAX; i >= 0; i--){
        if(b.half_word[i] != d.half_word[i]){
            result = 0;
        }
    }
    if(result == 1){
        for(p = ps; *p; p++) {
            console->data = *p;
        }
    }

    else{
        for(p = fs; *p; p++) {
            console->data = *p;
        }
    }


/* 
 * test code for poly functions 
 */
    
    null(&field_a);
    null(&field_b);
    null(&field_c);
    null(&field_d);
    
    /* init a and b */
    random_field(&field_a, 4523 + iter);
    random_field(&field_b, 9058 + iter);
  
    
    if(poly_inv(&field_a, &field_b) != BSL_OK){
        for(p = ts; *p; p++) {
            console->data = *p;
        }
    }

    if(poly_mul(&field_a, &field_b, &field_c) != BSL_OK){
        for(p = ts; *p; p++){
            console->data = *p;
        }
    }

    field_is_one(&field_c, &result);
    /* check if new a is equal to b */
    

    if(result == TRUE){
        for(p = ps; *p; p++) {
            console->data = *p;
        }
    }
    
    else{
        for(p = fs; *p; p++) {
            console->data = *p;
        }
    }

/* 
 * test code for algorithms
 */
    Init_233_bit();

    /* init private keys
     */
    random_field(&private_key1, 8768 + iter);
    random_field(&private_key2, 3759 + iter);
  
        
  /* Generate public keys */
    err = generate_public_key(&named_point, &named_curve, &private_key1, &public_key1);
     
    err = generate_public_key(&named_point, &named_curve, &private_key2, &public_key2);
    
      /* Generate shared secret on both sides */
    err = generate_shared_key(&named_point, &named_curve, &public_key2, &private_key1, &shared_secret1);
    

    err = generate_shared_key(&named_point, &named_curve, &public_key1, &private_key2, &shared_secret2);

    same = 0;
    for(i =0 ; i < MAX_LONG; i++){
      if(shared_secret1.e[i] != shared_secret2.e[i]){
	same = 1;
      }
    }
    if(same ==0){
      for(p = ps; *p; p++) {
            console->data = *p;
        }
    }
    else{
      for(p = fs; *p; p++) {
            console->data = *p;
        }
    }
    
    
    for(;;) ;

}


unsigned int myrand(unsigned int seed){
    seed = 0x343fd * seed + 0x269ec3;
    return ((seed )& 0xffffffff);
            }

/* to get a random field for testing */

void random_field(field_2n *value, unsigned int seed)
{
    short int i;
    for(i = 0; i< MAX_LONG; i++){
        value->e[i] = myrand(seed);
        seed = value->e[i];
    }
    value->e[0] &= UPR_MASK;
}
