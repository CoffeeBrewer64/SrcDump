#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <PR/bbtypes.h>
#include <PR/bbmetadata.h>
#include <PR/bbticket.h>
#include <algorithms.h>


unsigned int myrand(unsigned int seed);
void random_field(field_2n *value, unsigned int seed);
void input_field(FILE *keyfileptr, field_2n *value);
extern curve named_curve;
extern point named_point;


/* 
 *debugging printing routines to print field variables
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

int
main(int argc, char** argv) {

    int same = 0;
    int i;
    BSL_error err;
    int start_offset, bytes;
    u32 aesKey[4];
    u32 cmdiv[4];
    BbContentMetaDataHead cmdhead;
    int iter;
    FILE *infileptr;
#if 0
    FILE *outfileptr;
    FILE *keyfileptr;
    int result = 0;
    BbTicketHead tickethead;
    bigint a, b, c, d, dummy;
    field_2n temp;
    field_2n field_a, field_b, field_c, field_d;
#endif
    field_2n private_key1, private_key2, shared_secret1, shared_secret2; 
    point public_key1, public_key2;

    /* read in arguments */
    if (argc != 6){
        fprintf(stderr,"Usage: test inputcmdfile pvtkeyfile outputticketfile  offset num_bytes\n");
        fprintf(stderr,"input is content meta data file name\n");
        fprintf(stderr,"pvt key file is binary file\n");
        fprintf(stderr,"output is output ticket file\n");
        fprintf(stderr, "start of encryption from this byte\n");
        fprintf(stderr, "number of bytes to encrypt, multiple of 16 bytes\n");
        exit(1);
    } 
    
    start_offset = atoi(argv[4]);
    bytes = atoi(argv[5]);
    if((bytes % 16) != 0){
        fprintf(stderr,"number of bytes to encrypt must be 16 byte multiple\n");
        exit(1);
    }
#if 0
    infileptr = fopen(argv[1], "rb");
    keyfileptr = fopen(argv[2], "rb");
    outfileptr = fopen(argv[3], "wb");

    if((infileptr == NULL) ||(outfileptr == NULL)  || (keyfileptr == NULL)){
        fprintf(stderr,"file open error\n");
    }
   
#endif
    /* 
     * test code for algorithms
     */
    Init_233_bit();
    
    /* init private keys
     */
/*
    input_field(keyfileptr, &private_key1);
*/
    for(iter = 0; iter < 30; iter++){
    random_field(&private_key1, 5345 +iter);
    random_field(&private_key2, 3759 +iter);
  
    print_field("Private key 1", &private_key1);
    print_field("Private key 2", &private_key2);
        
  /* Generate public keys */
    err = generate_public_key(&named_point, &named_curve, &private_key1, &public_key1);
     
    if( err != BSL_OK){
        printf("error generating public key\n");
    }
    err = generate_public_key(&named_point, &named_curve, &private_key2, &public_key2);
    
    if( err != BSL_OK){
        printf("error generating public key\n");
    }
    print_point("Public Key 1", &public_key1);
    print_point("Public Key 2", &public_key2);
    
      /* Generate shared secret on both sides */
    err = generate_shared_key(&named_point, &named_curve, &public_key2, &private_key1, &shared_secret1);
    

    err = generate_shared_key(&named_point, &named_curve, &public_key1, &private_key2, &shared_secret2);

    print_field("Shared Key 1", &shared_secret1);
    print_field("Shared Key 2", &shared_secret2);
    
    same = 0;
    for(i =0 ; i < MAX_LONG; i++){
      if(shared_secret1.e[i] != shared_secret2.e[i]){
	same = 1;
      }
    }
    if(same ==0){
        printf("PASS shared secret equal test \n");
    }
    else{
      printf("FAIL shared secret equal test \n");
    }
    }
    printf("AES key->\n");
    printf("%08lx\n", shared_secret1.e[1]);
    printf("%08lx\n", shared_secret1.e[2]);
    printf("%08lx\n", shared_secret1.e[3]);
    printf("%08lx\n", shared_secret1.e[4]);
    
    /* this should be the same key that gets generated in the player */
    
    for(i = 0; i < 4; i++){
        aesKey[i] = shared_secret1.e[i];
    }
    
    for(i =0; i < 4; i++){
        cmdiv[i] = (u32) i;
    }
    
    /* load the data from the file: is this head only or entire cmd? */
    fread(&cmdhead, sizeof(BbContentMetaDataHead), 1, infileptr);
    
    /* encrypt portion starting from start_offset, bytes number of bytes,
       using key and iv above 
    */
    

    /* remaining fields */
/*
    tickethead.bbId = 0x01010101;
    tickethead.tsCrlVersion = 0;
    for(i = 0; i < 4;  i++){
        tickethead.cmdIv[0] = cmdiv[i];
    }
    for(i = 0; i < 8; i++){
        tickethead.serverKey[i] = public_key2.x.e[i];
    }
    for(i = 0; i < 8; i++){
        tickethead.serverKey[i+8] = public_key2.y.e[i];
    }

    strcpy(tickethead.issuer, "Root-LSCA00010203-LS00000001");
*/
    /* fwrite here */
    
    

    return 0;
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


void input_field(FILE *inputptr, field_2n *value)
{
    short int i;
    u32 key[8];
    fread(key, 4, 8, inputptr);
    for(i = 0; i< MAX_LONG; i++){
        value->e[i] = ntohl(key[i]);
    }
    value->e[0] &= UPR_MASK;
}
