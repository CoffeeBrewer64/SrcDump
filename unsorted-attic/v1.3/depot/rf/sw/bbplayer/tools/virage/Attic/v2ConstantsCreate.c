/* use this for creating input file for calling virage2 data
 * creation file in toolsAPI
 * deliver result to manufacturing server 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <PR/bcp.h>
#include <PR/bbvirage.h>
#include <PR/bbnand.h>


int main(int argc, char ** argv){
    int i;
    BbShaHash hash;
    BbAesKey key;
    u32 jtagEnable;
    u32 romPatch[16]; /* this is so total adds to 256 bytes */
    FILE *fptr;
    char *fname;

    if(argc ==2 ){
        fname = strdup(argv[1]);
    }
    else if(argc ==1){
        fname = strdup("virage.in");
    }
    else{
        fprintf(stderr,"usage: program filename");
        exit(1);
    }
    fptr = fopen(fname, "wb");
    if(fptr == NULL){
        fprintf(stderr,"file could not open\n");
        exit(1);
    }

    /* init */
    for (i = 0; i < 5; i++){
        hash[i] = htonl(0x01020304);
    }
    
    /* decryption key for boot application license: fixed
       0x84983e36 0x4706816a 0xba3e2571 0x7850c26c
    */
    key[0] = htonl(0x84983e36);
    key[1] = htonl(0x4706816a);
    key[2] = htonl(0xba3e2571);
    key[3] = htonl(0x7850c26c);

    jtagEnable = htonl(0x00000000);

    for(i =0 ;i < 16; i++){
        romPatch[i] = htonl(0xf0f0f0f0);
    }

    fwrite(hash, 4, 5, fptr);
    fwrite(romPatch, 4, 16, fptr);
    fwrite(key, 4, 4, fptr);
    fwrite(&jtagEnable, 4, 1, fptr);
    

    fclose(fptr);

}
    






