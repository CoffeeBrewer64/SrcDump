#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <stdlib.h>
#include <integer_math.h>
#include <sha1.h>



BSL_error 
bigint_print(bigint *a, int int_max){
    short int i;
    
    for(i =0; i <= int_max; i++){
        printf("%d = %08lx\n ", i, a->half_word[i]);
    }
    return BSL_OK;
}

int main(int argc, char **argv){
    RSA *prsa;
    int equal = 0;
    bigint n, m, e;
    bigint a;
    int iter;
    int size, newsize, i, e_size, n_size;
    int num_bits, num_bytes, num_word, max_long, int_max, data_size;
    unsigned char e_string[4096];
    unsigned char n_string[4096];
    unsigned char hash_data[20];
    unsigned char *data;
    unsigned char *padded_data;
    unsigned char customResult[4096];
    unsigned char *sign;
    unsigned char *verify;
    unsigned char input_string[2048];
    int inputLen = 20;
    SHA1Context sha;
    /* cert types */
    unsigned long certpublickey[128];
    unsigned long certsign[128];
    unsigned long certexponent;
    
    int j;
    
    prsa = RSA_new();
    
    num_bits = 2048;
    num_bytes = num_bits/8;
    data_size = 256;
    prsa = RSA_generate_key(num_bits, 3, NULL, NULL);
    
    size = RSA_size(prsa);
    sign = (unsigned char *) malloc(4096);
    verify = (unsigned char *) malloc(4096);
    
    data = (unsigned char *)malloc(4096);
    padded_data = (unsigned char *) malloc(4096);
    for(iter = 0; iter < 10; iter++){
        for (i =0; i < data_size; i+=4){
            *((unsigned long *) (data + i)) = (unsigned long) rand();
        }

        /* compute SHA-1 */
        SHA1Reset(&sha);
        SHA1Input(&sha, data, data_size);
        SHA1Result(&sha, hash_data);
    
        for( i = 0; i < 20; i++){
            printf("hash = %02x\n", hash_data[i]);
        }
        RSA_padding_add_PKCS1_type_2(padded_data, data_size, hash_data, 20);
        
        /*print padded data */
        for(i = 0; i < data_size; i++){
            printf("padded = %02x\n", padded_data[i]);
        } 

            
        /* zero the sign */
        for (i = 0; i <  size; i++){
            sign[i] = 0;
        }
        size = RSA_private_encrypt(data_size, padded_data, sign, prsa, RSA_NO_PADDING);
        printf("size of encrypted = %d\n", size);
        /* zero the result */
        for(i = 0; i < size; i++){
            verify[i]  = 0;
        }
        newsize = RSA_public_decrypt(RSA_size(prsa), sign, verify, prsa, RSA_NO_PADDING);
        printf("size of decrypted = %d\n", newsize);
        for(i =0; i< data_size; i++){
            printf("verify [%d] = %02x padded_data = %02x\n", i, verify[i], padded_data[i]);
        }

        /* call mod_exp from integer_math.h */
    
        /* initialise bigint */

        e_size = BN_bn2bin(prsa->e, e_string);

        for( i =0 ; i< e_size; i++){
            printf("e[%d] = %02x\n", i, e_string[i]);
        }


        n_size = BN_bn2bin(prsa->n, n_string);

        for( i =0 ; i< n_size; i++){
            printf("n[%d] = %02x\n", i, n_string[i]);
        }

        num_word = num_bits/WORD_SIZE;
        max_long = num_word + 1;
        int_max = (4*max_long) - 1;
        charstring_to_bigint(&m, sign, data_size, int_max);
        charstring_to_bigint(&n, n_string, n_size, int_max);
        charstring_to_bigint(&e, e_string, e_size, int_max);
/*
        printf("m\n");
        bigint_print(&m, int_max);
        printf("n\n");
        bigint_print(&n, int_max);
        printf("e\n");
        bigint_print(&e, int_max);
    
*/
        bigint_to_certint(certsign, num_word, &m, int_max);
        bigint_to_certint(certpublickey, num_word, &n, int_max);
        bigint_to_certint(&certexponent, 1, &e, int_max);

        bsl_rsa_verify(customResult, certsign, certpublickey, &certexponent, num_bits);
        /* print custom result of decryption */
        equal = 0;
        j= 0;
        /* print output*/
        for(i=data_size- 20; i < data_size; i++){
            printf(" input = %02x custom = %02x\n", padded_data[i], customResult[i]);
            if(hash_data[j] != customResult[i]){
                equal = 1;
            }
            j++;
        }
        if(equal ==0){
            printf("OK PASS test %d\n", iter);
        }
        else {
            printf("NOT OK FAIL test %d\n", iter);
        }
    }

    for(i =0 ; i< inputLen; i++){
        input_string[i] = i;
    }



    charstring_to_bigint(&a, input_string, inputLen, int_max);
    bigint_print(&a, int_max);
    RSA_free(prsa);
    free(sign);
    free(verify);
    free(data);
    free(padded_data);
    return 0;
}
    






