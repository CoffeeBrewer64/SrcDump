/* rijndael-api-ref.c   v2.0   August '99
 * Reference ANSI C code
 * authors: Paulo Barreto
 *          Vincent Rijmen
 */
/*
                        ------------------------------
                        Rijndael ANSI C Reference Code
                        ------------------------------

                                October 24, 2000

                                  Disclaimer


This software package was submitted to the National Institute of Standards and
Technology (NIST) during the Advanced Encryption Standard (AES) development
effort by Joan Daemen and Vincent Rijmen, the developers of the Rijndael algorithm.

This software is distributed in compliance with export regulations (see below), and
it is intended for non-commercial use, only.   NIST does not support this software 
and does not provide any guarantees or warranties as to its performance, fitness 
for any particular application, or validation under the Cryptographic Module
Validation Program (CMVP) <http://csrc.nist.gov/cryptval/>.  NIST does not accept 
any liability associated with its use or misuse.  This software is provided as-is. 
By accepting this software the user agrees to the terms stated herein.

                            -----------------------

                              Export Restrictions


Implementations of cryptography are subject to United States Federal
Government export controls.  Export controls on commercial encryption products 
are administered by the Bureau of Export Administration (BXA) 
<http://www.bxa.doc.gov/Encryption/> in the U.S. Department of Commerce. 
Regulations governing exports of encryption are found in the Export 
Administration Regulations (EAR), 15 C.F.R. Parts 730-774.
*/

#include <stdlib.h>
#include <string.h>
#include "rijndael-alg-ref.h"
#include "rijndael-api-ref.h"


int aes_BlockMakeKey(aes_keyInstance *key, AES_BYTE direction, int keyLen, int blockLen, unsigned char *keyMaterial, int isAscii)
{
    word8 k[4][MAXKC];
    int i, j, t;
/*
    int x,y,z;
*/
		
    if (key == NULL) {
        return AES_BAD_KEY_INSTANCE;
    }

    if ((direction == AES_DIR_ENCRYPT) || (direction == AES_DIR_DECRYPT)) {
        key->direction = direction;
    } else {
        return AES_BAD_KEY_DIR;
    }

    if ((keyLen == 128) || (keyLen == 192) || (keyLen == 256)) { 
        key->keyLen = keyLen;
    } else {
        return AES_BAD_KEY_MAT;
    }

    /* initialize key schedule: */ 
    for(i = 0; i < key->keyLen/8; i++) {
        if(isAscii){
          t = keyMaterial[2*i];
          if ((t >= '0') && (t <= '9')) j = (t - '0') << 4;
          else if ((t >= 'a') && (t <= 'f')) j = (t - 'a' + 10) << 4; 
          else if ((t >= 'A') && (t <= 'F')) j = (t - 'A' + 10) << 4; 
          else return AES_BAD_KEY_MAT;
		
          t = keyMaterial[2*i+1];
          if ((t >= '0') && (t <= '9')) j ^= (t - '0');
          else if ((t >= 'a') && (t <= 'f')) j ^= (t - 'a' + 10); 
          else if ((t >= 'A') && (t <= 'F')) j ^= (t - 'A' + 10); 
          else return AES_BAD_KEY_MAT;
		
          k[i % 4][i / 4] = (word8) j;
        }
        else{
            k[i % 4][i / 4] = keyMaterial[i];
        }
        k[i % 4][i / 4] = keyMaterial[i];
    }	
	
	
    key->blockLen = blockLen;
	
    rijndaelKeySched (k, key->keyLen, key->blockLen, key->keySched);
    /*

	for (x=0; x < 11; x++){
	  for(y=0; y < 4; y++){
	    for(z=0; z < 4; z++){
	      printf(" %02x", key->keySched[x][z][y]);
	    }
	    printf("\n");
	  }
	}
	*/
    return AES_TRUE;
}

int mult(int x, int y){
    int xt, r;
    r=0;
    xt=x;
    for(;y>0;y>>=1){
        if(y&1)
            r^=xt;
        if(xt & 0x80)
            xt = (xt<<1) ^ 0x1b;
        else
            xt <<= 1;
    }
    return r&0xff;
}

int aes_BlockMakeKeyEqvtInv(aes_keyInstance *key, AES_BYTE direction, int keyLen, int blockLen, unsigned char *keyMaterial, int isAscii)
{
  
    word8 k[4][MAXKC];
    int i, j, t;
/*
    int x,y,z;
*/
    int a,b,c,d,m;

		
    if (key == NULL) {
        return AES_BAD_KEY_INSTANCE;
    }

    if ((direction == AES_DIR_ENCRYPT) || (direction == AES_DIR_DECRYPT)) {
        key->direction = direction;
    } else {
        return AES_BAD_KEY_DIR;
    }

    if ((keyLen == 128) || (keyLen == 192) || (keyLen == 256)) { 
        key->keyLen = keyLen;
    } else {
        return AES_BAD_KEY_MAT;
    }

    /* initialize key schedule: */ 
    for(i = 0; i < key->keyLen/8; i++) {
        if(isAscii){
          t = keyMaterial[2*i];
          if ((t >= '0') && (t <= '9')) j = (t - '0') << 4;
          else if ((t >= 'a') && (t <= 'f')) j = (t - 'a' + 10) << 4; 
          else if ((t >= 'A') && (t <= 'F')) j = (t - 'A' + 10) << 4; 
          else return AES_BAD_KEY_MAT;
		
          t = keyMaterial[2*i+1];
          if ((t >= '0') && (t <= '9')) j ^= (t - '0');
          else if ((t >= 'a') && (t <= 'f')) j ^= (t - 'a' + 10); 
          else if ((t >= 'A') && (t <= 'F')) j ^= (t - 'A' + 10); 
          else return AES_BAD_KEY_MAT;
		
          k[i % 4][i / 4] = (word8) j; 
        }
        else{
            k[i % 4][i / 4] = keyMaterial[i];      
        }      
    }	
    /*
	for (x=0; x< 4; x++){
	  for(y=0; y< 4;y++){
	    printf("key [%d][%d] = %02x\n", y,x, k[y][x]);
	  }
	}
	*/
    key->blockLen = blockLen;
	
    rijndaelKeySched (k, key->keyLen, key->blockLen, key->keySched);
	
	/* extra step for eqvt inv */

    for(m=1;m<10;m++)
        for(i=0;i<4;i++){
	    a=key->keySched[m][0][i]; 
	    b=key->keySched[m][1][i]; 
	    c=key->keySched[m][2][i]; 
	    d=key->keySched[m][3][i];
	    key->keySched[m][0][i]=mult(a,0xe)^mult(b,0xb)^mult(c,0xd)^mult(d,0x9);
	    key->keySched[m][1][i]=mult(a,0x9)^mult(b,0xe)^mult(c,0xb)^mult(d,0xd);
	    key->keySched[m][2][i]=mult(a,0xd)^mult(b,0x9)^mult(c,0xe)^mult(d,0xb);
	    key->keySched[m][3][i]=mult(a,0xb)^mult(b,0xd)^mult(c,0x9)^mult(d,0xe);
        }
    /*
	for (x=0; x < 11; x++){
	  for(y=0; y < 4; y++){
	    for(z=0; z < 4; z++){
	      printf(" %02x", key->keySched[x][z][y]);
	    }
	    printf("\n");
	  }
	}
	*/
    return AES_TRUE;
}



int aes_BlockCipherInit(aes_cipherInstance *cipher, AES_BYTE mode, unsigned char *IV, int blockLen, int isAscii)
{
    int i, j, t;
	
    if ((mode == AES_MODE_ECB) || (mode == AES_MODE_CBC) || (mode == AES_MODE_CFB1)) {
        cipher->mode = mode;
    } else {
        return AES_BAD_CIPHER_MODE;
    }
    cipher->blockLen = blockLen;
	
    if (IV != NULL) {
        for(i = 0; i < cipher->blockLen/8; i++) {		
            if(isAscii){
                t = IV[2*i];
                if ((t >= '0') && (t <= '9')) j = (t - '0') << 4;
                else if ((t >= 'a') && (t <= 'f')) j = (t - 'a' + 10) << 4; 
                else if ((t >= 'A') && (t <= 'F')) j = (t - 'A' + 10) << 4; 
                else return AES_BAD_CIPHER_INSTANCE;
		
                t = IV[2*i+1];
                if ((t >= '0') && (t <= '9')) j ^= (t - '0');
                else if ((t >= 'a') && (t <= 'f')) j ^= (t - 'a' + 10); 
                else if ((t >= 'A') && (t <= 'F')) j ^= (t - 'A' + 10); 
                else return AES_BAD_CIPHER_INSTANCE;
			
                cipher->IV[i] = (AES_BYTE) j;
            }
            else{
                cipher->IV[i] = IV[i];
            }
        } 
    }

    return AES_TRUE;
}


int aes_BlockEncrypt(aes_cipherInstance *cipher,
                 aes_keyInstance *key, AES_BYTE *input, int inputLen, AES_BYTE *outBuffer)
{
    int i, j, t, numBlocks;
    word8 block[4][MAXBC];

	
    /* check parameter consistency: */
    if (key == NULL ||
        key->direction != AES_DIR_ENCRYPT ||
        (key->keyLen != 128 && key->keyLen != 192 && key->keyLen != 256)) {
        return AES_BAD_KEY_MAT;
    }
    if (cipher == NULL ||
        (cipher->mode != AES_MODE_ECB && cipher->mode != AES_MODE_CBC && cipher->mode != AES_MODE_CFB1) ||
        (cipher->blockLen != 128 && cipher->blockLen != 192 && cipher->blockLen != 256)) {
        return AES_BAD_CIPHER_STATE;
    }


    numBlocks = inputLen/cipher->blockLen;
	
    switch (cipher->mode) {
    case AES_MODE_ECB: 
        for (i = 0; i < numBlocks; i++) {
            for (j = 0; j < cipher->blockLen/32; j++) {
                for(t = 0; t < 4; t++)
				/* parse input stream into rectangular array */
                    block[t][j] = input[4*j+t] & 0xFF;
				
            }
            rijndaelEncrypt (block, key->keyLen, cipher->blockLen, key->keySched);
            for (j = 0; j < cipher->blockLen/32; j++) {
				/* parse rectangular array into output ciphertext bytes */
                for(t = 0; t < 4; t++)
                    outBuffer[4*j+t] = (AES_BYTE) block[t][j];
            }
        }
        break;
		
    case AES_MODE_CBC:
        for (j = 0; j < cipher->blockLen/32; j++) {
            for(t = 0; t < 4; t++)
                /* parse initial value into rectangular array */
                block[t][j] = cipher->IV[t+4*j] & 0xFF;
        }
		
        for (i = 0; i < numBlocks; i++) {
            for (j = 0; j < cipher->blockLen/32; j++) {
                for(t = 0; t < 4; t++){
				/* parse input stream into rectangular array and exor with 
				   IV or the previous ciphertext */
                    /*block[t][j] ^= input[4*j+t] & 0xFF;*/
                    block[t][j] ^= input[4*j+t + (i*cipher->blockLen/8)] & 0xFF;
/*printf("block data = %d %d =%d from %d\n", t,j, block[t][j], 4*j+t +(i*cipher->blockLen/8));*/
                }
            }
						
            rijndaelEncrypt (block, key->keyLen, cipher->blockLen, key->keySched);
			
            for (j = 0; j < cipher->blockLen/32; j++) {
				/* parse rectangular array into output ciphertext bytes */
                for(t = 0; t < 4; t++){
                    /*outBuffer[4*j+t] = (AES_BYTE) block[t][j];*/
                    outBuffer[4*j+t +i*cipher->blockLen/8] = (AES_BYTE) block[t][j];
                }
            }
        }

        /* fix for streaming calls */
        for(i=0;i<cipher->blockLen/8;i++){
            cipher->IV[i]=outBuffer[(inputLen/8)-(cipher->blockLen/8)+i];
        }

        break;
	
    default: return AES_BAD_CIPHER_STATE;
    }
	
    return numBlocks*cipher->blockLen;
}

int aes_BlockDecrypt(aes_cipherInstance *cipher,
                 aes_keyInstance *key, AES_BYTE *input, int inputLen, AES_BYTE *outBuffer)
{
    int i, j, t, numBlocks;
    word8 block[4][MAXBC];

    if (cipher == NULL ||
        key == NULL ||
        key->direction == AES_DIR_ENCRYPT /* ||
                                         cipher->blockLen != key->blockLen */) {
        if(cipher == NULL){
            /*
	    fprintf(stderr," bad state here: cipher null\n");
            */
            return AES_BAD_CIPHER_STATE;
        }
        if(key  == NULL){
            /*
	    fprintf(stderr," key null\n");
            */
            return AES_BAD_CIPHER_STATE;
        }
	  
        if(cipher->blockLen != key->blockLen){
/*
	    fprintf(stderr," cipher->blockLen = %d\n", cipher->blockLen);
	    fprintf(stderr," key->blockLen = %d\n", key->blockLen);
	    fprintf(stderr,"lengths dont match\n");
*/
            return AES_BAD_CIPHER_STATE;

        }
        return AES_BAD_CIPHER_STATE;
    }

    /* check parameter consistency: */
    if (key == NULL ||
        key->direction != AES_DIR_DECRYPT ||
        (key->keyLen != 128 && key->keyLen != 192 && key->keyLen != 256)) {
/*
        fprintf(stderr,"key matrix bad\n");
*/
        return AES_BAD_KEY_MAT;
    }
    if (cipher == NULL ||
        (cipher->mode != AES_MODE_ECB && cipher->mode != AES_MODE_CBC && cipher->mode != AES_MODE_CFB1) ||
        (cipher->blockLen != 128 && cipher->blockLen != 192 && cipher->blockLen != 256)) {
/*
        fprintf(stderr,"mode or block length incorrect\n");
*/
        return AES_BAD_CIPHER_STATE;
    }
	

    numBlocks = inputLen/cipher->blockLen;
	
    switch (cipher->mode) {
    case AES_MODE_ECB: 
        for (i = 0; i < numBlocks; i++) {
            for (j = 0; j < cipher->blockLen/32; j++) {
                for(t = 0; t < 4; t++){
				/* parse input stream into rectangular array */
                    block[t][j] = input[4*j+t] & 0xFF;
                }
            }
            rijndaelDecrypt (block, key->keyLen, cipher->blockLen, key->keySched);
            for (j = 0; j < cipher->blockLen/32; j++) {
				/* parse rectangular array into output ciphertext bytes */
                for(t = 0; t < 4; t++)
                    outBuffer[4*j+t] = (AES_BYTE) block[t][j];
            }
        }
        break;
		
    case AES_MODE_CBC:
        /* first block */
        for (j = 0; j < cipher->blockLen/32; j++) {
            for(t = 0; t < 4; t++){
                /* parse input stream into rectangular array */
                block[t][j] = input[4*j+t] & 0xFF;
			
            }
        }
		
        rijndaelDecrypt (block, key->keyLen, cipher->blockLen, key->keySched);
		
        for (j = 0; j < cipher->blockLen/32; j++) {
            /* exor the IV and parse rectangular array into output ciphertext bytes */
            for(t = 0; t < 4; t++){
                outBuffer[4*j+t] = (AES_BYTE) (block[t][j] ^ cipher->IV[t+4*j]);
            }
        }
		
        /* next blocks */
        for (i = 1; i < numBlocks; i++) {
            for (j = 0; j < cipher->blockLen/32; j++) {
                for(t = 0; t < 4; t++){
				/* parse input stream into rectangular array */
                    /*block[t][j] = input[cipher->blockLen/8+4*j+t] & 0xFF;
                     */
                    block[t][j] = input[4*j+t + i*cipher->blockLen/8] & 0xFF;
                }
            }
            rijndaelDecrypt (block, key->keyLen, cipher->blockLen, key->keySched);
			
            for (j = 0; j < cipher->blockLen/32; j++) {
				/* exor previous ciphertext block and parse rectangular array 
                                   into output ciphertext bytes */
                for(t = 0; t < 4; t++){
                    /*outBuffer[cipher->blockLen/8+4*j+t] = (AES_BYTE) (block[t][j] ^ 
                      input[4*j+t-4*cipher->blockLen/32]);*/
                    outBuffer[4*j+t +i*cipher->blockLen/8] = (AES_BYTE) block[t][j] ^input[4*j+t +(i-1)*cipher->blockLen/8];
                }


            }
        }

        /* fix for streaming calls */
        for(i=0;i<cipher->blockLen/8;i++){
            cipher->IV[i]=input[(inputLen/8)-(cipher->blockLen/8)+i];
        }

        break;
	
    default: return AES_BAD_CIPHER_STATE;
    }
	
    return numBlocks*cipher->blockLen;
}

int aes_BlockDecryptEqvtInv(aes_cipherInstance *cipher,
                        aes_keyInstance *key, AES_BYTE *input, int inputLen, AES_BYTE *outBuffer)
{
    int i, j, t, numBlocks;
    word8 block[4][MAXBC];

    if (cipher == NULL ||
        key == NULL ||
        key->direction == AES_DIR_ENCRYPT /* ||
                                         cipher->blockLen != key->blockLen */) {
        /*
        if(cipher == NULL){
	    fprintf(stderr," bad state here: cipher null\n");
        }
        if(key  == NULL){
	    fprintf(stderr," key null\n");
        }
	  
        if(cipher->blockLen != key->blockLen){
	    fprintf(stderr," cipher->blockLen = %d\n", cipher->blockLen);
	    fprintf(stderr," key->blockLen = %d\n", key->blockLen);
	    fprintf(stderr,"lengths dont match\n");
        }
        */
        return AES_BAD_CIPHER_STATE;
    }

    /* check parameter consistency: */
    if (key == NULL ||
        key->direction != AES_DIR_DECRYPT ||
        (key->keyLen != 128 && key->keyLen != 192 && key->keyLen != 256)) {
/*
        fprintf(stderr,"key matrix bad\n");
*/
        return AES_BAD_KEY_MAT;
    }
    if (cipher == NULL ||
        (cipher->mode != AES_MODE_ECB && cipher->mode != AES_MODE_CBC && cipher->mode != AES_MODE_CFB1) ||
        (cipher->blockLen != 128 && cipher->blockLen != 192 && cipher->blockLen != 256)) {
/*
        fprintf(stderr,"mode or block length incorrect\n");
*/
        return AES_BAD_CIPHER_STATE;
    }
	

    numBlocks = inputLen/cipher->blockLen;
	
    switch (cipher->mode) {
    case AES_MODE_ECB: 
        for (i = 0; i < numBlocks; i++) {
            for (j = 0; j < cipher->blockLen/32; j++) {
                for(t = 0; t < 4; t++){
				/* parse input stream into rectangular array */
                    block[t][j] = input[4*j+t] & 0xFF;
                }
            }
            rijndaelDecryptEqvtInv (block, key->keyLen, cipher->blockLen, key->keySched);
            for (j = 0; j < cipher->blockLen/32; j++) {
				/* parse rectangular array into output ciphertext bytes */
                for(t = 0; t < 4; t++)
                    outBuffer[4*j+t] = (AES_BYTE) block[t][j];
            }
        }
        break;
		
    case AES_MODE_CBC:
        /* first block */
        for (j = 0; j < cipher->blockLen/32; j++) {
            for(t = 0; t < 4; t++){
                /* parse input stream into rectangular array */
                block[t][j] = input[4*j+t] & 0xFF;
			
            }
        }
		
        rijndaelDecryptEqvtInv (block, key->keyLen, cipher->blockLen, key->keySched);
		
        for (j = 0; j < cipher->blockLen/32; j++) {
            /* exor the IV and parse rectangular array into output ciphertext bytes */
            for(t = 0; t < 4; t++){
                outBuffer[4*j+t] = (AES_BYTE) (block[t][j] ^ cipher->IV[t+4*j]);
            }
        }
		
        /* next blocks */
        for (i = 1; i < numBlocks; i++) {
		  
            for (j = 0; j < cipher->blockLen/32; j++) {
                for(t = 0; t < 4; t++){
				/* parse input stream into rectangular array */
                    /*block[t][j] = input[cipher->blockLen/8+4*j+t] & 0xFF;
                     */
                    block[t][j] = input[4*j+t + i*cipher->blockLen/8] & 0xFF;
                }
            }
			
            rijndaelDecryptEqvtInv (block, key->keyLen, cipher->blockLen, key->keySched);
			
            for (j = 0; j < cipher->blockLen/32; j++) {
				/* exor previous ciphertext block and parse rectangular array 
                                   into output ciphertext bytes */
                for(t = 0; t < 4; t++){
                    /*outBuffer[cipher->blockLen/8+4*j+t] = (AES_BYTE) (block[t][j] ^ 
                      input[4*j+t-4*cipher->blockLen/32]);*/
                    outBuffer[4*j+t +i*cipher->blockLen/8] = (AES_BYTE) block[t][j] ^input[4*j+t +(i-1)*cipher->blockLen/8];
                }


            }
        }

        /* fix for streaming calls */
        for(i=0;i<cipher->blockLen/8;i++){
            cipher->IV[i]=input[(inputLen/8)-(cipher->blockLen/8)+i];
        }

        break;
	
    default: return AES_BAD_CIPHER_STATE;
    }
	
    return numBlocks*cipher->blockLen;
}

