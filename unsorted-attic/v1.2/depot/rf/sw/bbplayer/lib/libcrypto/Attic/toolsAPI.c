#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "toolsAPI.h"
#include "../bbboot/boot.h"

#include <PR/bcp.h>
#include <PR/bbvirage.h>
#include <PR/bbnand.h>
#include "../../lib/bbboot/boot.h"



/*
 * these are constants for the FIPS curve : to create public key
 */
/*
extern curve named_curve;
extern point named_point;
*/

/* 
 * to get virage2 data blob send an open file ptr and 
 * data from RNG and bbid from database
 */

int 
getVirage2Data(FILE *constantsFilePtr, u32 bbid, u32 privateKey[8], u32 rand[12], void *virage2data){
    BbVirage2 virage;
    BbShaHash hash;
    int i;
    u32 romPatch[64];
    u32 key[4];
    u32 temp = 0x0;
    if(constantsFilePtr == NULL){
        fprintf(stderr, "get a virage input file first eg, virage.in\n");
        return -1;
    }
    
    
    /*load hash from file and write in */
    if(fread(hash, 4, 5, constantsFilePtr) != 20){
        return -1;
    }
    for(i = 0; i < 5; i++){
        virage.skHash[i] = htonl(hash[i]);
        temp += virage.skHash[i];
    }
    
    /*load rom patch and write in */
    if(fread(romPatch, 4, 64, constantsFilePtr ) != (64*4)){
        return -1;
    }

    for(i = 0; i < 64; i ++){
        virage.romPatch[i] = htonl(romPatch[i]);
        temp += virage.romPatch[i];
    }
    
    /* skip public key for now */
    for(i = 0; i < 16; i ++){
        virage.publicKey[i] = 0x00000000;
        temp += virage.publicKey[i];
    }
    
    virage.bbId = htonl(bbid);
    temp += virage.bbId;
    /* write private key */
    for(i = 0; i < 8; i++){
        virage.privateKey[i] = htonl(privateKey[i]);
        temp += virage.privateKey[i];
    }

    /* write boot app key from file */
    if(fread(key, 4, 4, constantsFilePtr) != 16){
        return -1;
    }
    for(i = 0; i < 4; i++){
        virage.bootAppKey[i] = htonl(key[i]);
        temp += virage.bootAppKey[i];
    }
    
    /* assign the random numbers to the AES keys */
    for(i = 0; i < 4; i++){
        virage.recryptListKey[i] = htonl(rand[i]);
        temp += virage.recryptListKey[i];
    }

    for(i = 0; i < 4; i++){
        virage.appStateKey[i] = htonl(rand[i+4]);
        temp += virage.appStateKey[i];
    }
    
    for(i = 0; i < 4; i++){
        virage.selfMsgKey[i] = htonl(rand[i+8]);
        temp += virage.selfMsgKey[i];
    }

    /* compute checksum*/
    virage.csumAdjust = VIRAGE2_CHECKSUM - ((int)temp);
    
    if( fread(&temp, 4, 1, constantsFilePtr) != 4){
        return -1;
    }
    virage.jtagEnable = temp;

    virage2data = (void *) &virage;
    return 0;
}

    


    
    
                                
