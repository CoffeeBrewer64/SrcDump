d43 1
a43 1
#include <stdio.h>
d47 1
a47 1
int aes_makeKey(aes_keyInstance *key, AES_BYTE direction, int keyLen, int blockLen, char *keyMaterial)
d49 36
a84 5
  /*for debugging*/
  
	AES_BYTE k[4][AES_MAXKC];
	int i, j, t;

d86 12
a97 9
	if (key == NULL) {
		return AES_BAD_KEY_INSTANCE;
	}

	if ((direction == AES_DIR_ENCRYPT) || (direction == AES_DIR_DECRYPT)) {
		key->direction = direction;
	} else {
		return AES_BAD_KEY_DIR;
	}
a98 34
	if ((keyLen == 128) || (keyLen == 192) || (keyLen == 256)) { 
		key->keyLen = keyLen;
	} else {
		return AES_BAD_KEY_MAT;
	}

	if ( keyMaterial ) {
		strncpy(key->keyMaterial, keyMaterial, keyLen/4);
	}

	/* initialize key schedule: */ 
 	for(i = 0; i < key->keyLen/8; i++) {
		t = key->keyMaterial[2*i];
		if ((t >= '0') && (t <= '9')) j = (t - '0') << 4;
		else if ((t >= 'a') && (t <= 'f')) j = (t - 'a' + 10) << 4; 
		else if ((t >= 'A') && (t <= 'F')) j = (t - 'A' + 10) << 4; 
		else return AES_BAD_KEY_MAT;
		
		t = key->keyMaterial[2*i+1];
		if ((t >= '0') && (t <= '9')) j ^= (t - '0');
		else if ((t >= 'a') && (t <= 'f')) j ^= (t - 'a' + 10); 
		else if ((t >= 'A') && (t <= 'F')) j ^= (t - 'A' + 10); 
		else return AES_BAD_KEY_MAT;
		
		k[i % 4][i / 4] = (AES_BYTE) j; 
	}	
	
	
	key->blockLen = blockLen;
	
	__rijndaelKeySched (k, key->keyLen, key->blockLen, key->keySched);
	/*
	{
	int x,y,z;
a106 1
	}
d108 1
a108 1
	return AES_TRUE;
d111 13
a123 13
static int mult(int x, int y){
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
d126 1
a126 1
int aes_makeKeyEqvtInv(aes_keyInstance *key, AES_BYTE direction, int keyLen, int blockLen, char *keyMaterial)
a127 1
  /*for debugging*/
d129 38
a166 4
	AES_BYTE k[4][AES_MAXKC];
	int i, j, t;
	int a,b,c,d,m;

d168 5
a172 39
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

	if ( keyMaterial ) {
		strncpy(key->keyMaterial, keyMaterial, keyLen/4);
	}

	/* initialize key schedule: */ 
 	for(i = 0; i < key->keyLen/8; i++) {
		t = key->keyMaterial[2*i];
		if ((t >= '0') && (t <= '9')) j = (t - '0') << 4;
		else if ((t >= 'a') && (t <= 'f')) j = (t - 'a' + 10) << 4; 
		else if ((t >= 'A') && (t <= 'F')) j = (t - 'A' + 10) << 4; 
		else return AES_BAD_KEY_MAT;
		
		t = key->keyMaterial[2*i+1];
		if ((t >= '0') && (t <= '9')) j ^= (t - '0');
		else if ((t >= 'a') && (t <= 'f')) j ^= (t - 'a' + 10); 
		else if ((t >= 'A') && (t <= 'F')) j ^= (t - 'A' + 10); 
		else return AES_BAD_KEY_MAT;
		
		k[i % 4][i / 4] = (AES_BYTE) j; 
	}	
	/*
	{
	int x,y,z;
a177 1
	}
d179 1
a179 1
	key->blockLen = blockLen;
d181 1
a181 1
	__rijndaelKeySched (k, key->keyLen, key->blockLen, key->keySched);
d185 2
a186 2
	for(m=1;m<10;m++)
	  for(i=0;i<4;i++){
d195 2
a196 2
	  }
	/*
d206 1
a206 1
	return AES_TRUE;
d211 1
a211 1
int aes_cipherInit(aes_cipherInstance *cipher, AES_BYTE mode, char *IV, int blockLen)
d213 1
a213 1
	int i, j, t;
d215 21
a235 20
	if ((mode == AES_MODE_ECB) || (mode == AES_MODE_CBC) || (mode == AES_MODE_CFB1)) {
		cipher->mode = mode;
	} else {
		return AES_BAD_CIPHER_MODE;
	}
	cipher->blockLen = blockLen;
	
	if (IV != NULL) {
 		for(i = 0; i < cipher->blockLen/8; i++) {		
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
d237 5
a241 3
			cipher->IV[i] = (AES_BYTE) j;
		} 
	}
d243 1
a243 1
	return AES_TRUE;
d247 2
a248 2
int aes_blockEncrypt(aes_cipherInstance *cipher,
	aes_keyInstance *key, AES_BYTE *input, int inputLen, AES_BYTE *outBuffer)
d250 2
a251 2
	int i, j, t, numBlocks;
	AES_BYTE block[4][AES_MAXBC];
d254 20
a273 22
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


	if (inputLen % cipher->blockLen != 0)
	    	return AES_BAD_INPUT;
	numBlocks = inputLen/cipher->blockLen;
	
	switch (cipher->mode) {
	case AES_MODE_ECB: 
		for (i = 0; i < numBlocks; i++) {
			for (j = 0; j < cipher->blockLen/32; j++) {
				for(t = 0; t < 4; t++)
d275 1
a275 1
					block[t][j] = input[4*j+t] & 0xFF;
d277 3
a279 3
			}
			__rijndaelEncrypt (block, key->keyLen, cipher->blockLen, key->keySched);
			for (j = 0; j < cipher->blockLen/32; j++) {
d281 16
a296 16
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
d299 2
a300 2
				  /*block[t][j] ^= input[4*j+t] & 0xFF;*/
block[t][j] ^= input[4*j+t + (i*cipher->blockLen/8)] & 0xFF;
d302 2
a303 2
			  }
			}
d305 1
a305 1
			__rijndaelEncrypt (block, key->keyLen, cipher->blockLen, key->keySched);
d307 1
a307 1
			for (j = 0; j < cipher->blockLen/32; j++) {
d309 7
a315 14
			  for(t = 0; t < 4; t++){
				  /*outBuffer[4*j+t] = (AES_BYTE) block[t][j];*/
				  outBuffer[4*j+t +i*cipher->blockLen/8] = (AES_BYTE) block[t][j];
			  }
			}
		}
		/* copy out IV */
		for (j = 0; j < cipher->blockLen/32; j++) {
			for(t = 0; t < 4; t++)
			/* parse initial value into rectangular array */
					cipher->IV[t+4*j] = block[t][j] & 0xFF;
			}

		break;
d317 2
a318 2
	default: return AES_BAD_CIPHER_STATE;
	}
d320 1
a320 1
	return numBlocks*cipher->blockLen;
d323 2
a324 2
int aes_blockDecrypt(aes_cipherInstance *cipher,
	aes_keyInstance *key, AES_BYTE *input, int inputLen, AES_BYTE *outBuffer)
d326 2
a327 2
	int i, j, t, numBlocks;
	AES_BYTE block[4][AES_MAXBC];
d329 6
a334 5
	if (cipher == NULL ||
		key == NULL ||
		key->direction == AES_DIR_ENCRYPT /* ||
	    cipher->blockLen != key->blockLen */) {
	  if(cipher == NULL){
d336 5
a340 2
	  }
	  if(key  == NULL){
d342 3
a344 1
	  }
d346 2
a347 1
	  if(cipher->blockLen != key->blockLen){
d351 2
a352 3
	  }
		return AES_BAD_CIPHER_STATE;
	}
a353 12
        /* check parameter consistency: */
        if (key == NULL ||
                key->direction != AES_DIR_DECRYPT ||
                (key->keyLen != 128 && key->keyLen != 192 && key->keyLen != 256)) {
	  fprintf(stderr,"key matrix bad\n");
                return AES_BAD_KEY_MAT;
        }
        if (cipher == NULL ||
                (cipher->mode != AES_MODE_ECB && cipher->mode != AES_MODE_CBC && cipher->mode != AES_MODE_CFB1) ||
                (cipher->blockLen != 128 && cipher->blockLen != 192 && cipher->blockLen != 256)) {
	  fprintf(stderr,"mode or block length incorrect\n");
                return AES_BAD_CIPHER_STATE;
d355 2
a356 1
	
d358 26
a383 7
	numBlocks = inputLen/cipher->blockLen;
	
	switch (cipher->mode) {
	case AES_MODE_ECB: 
		for (i = 0; i < numBlocks; i++) {
			for (j = 0; j < cipher->blockLen/32; j++) {
			  for(t = 0; t < 4; t++){
d385 5
a389 5
					block[t][j] = input[4*j+t] & 0xFF;
			  }
			}
			__rijndaelDecrypt (block, key->keyLen, cipher->blockLen, key->keySched);
			for (j = 0; j < cipher->blockLen/32; j++) {
d391 12
a402 12
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
d404 2
a405 2
		  }
		}
d407 1
a407 1
		__rijndaelDecrypt (block, key->keyLen, cipher->blockLen, key->keySched);
d409 11
a419 11
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
d421 6
a426 6
				  /*block[t][j] = input[cipher->blockLen/8+4*j+t] & 0xFF;
				   */
block[t][j] = input[4*j+t + i*cipher->blockLen/8] & 0xFF;
			  }
			}
			__rijndaelDecrypt (block, key->keyLen, cipher->blockLen, key->keySched);
d428 1
a428 1
			for (j = 0; j < cipher->blockLen/32; j++) {
d430 11
a440 17
				       into output ciphertext bytes */
			  for(t = 0; t < 4; t++){
				  /*outBuffer[cipher->blockLen/8+4*j+t] = (AES_BYTE) (block[t][j] ^ 
				    input[4*j+t-4*cipher->blockLen/32]);*/
  outBuffer[4*j+t +i*cipher->blockLen/8] = (AES_BYTE) block[t][j] ^input[4*j+t +(i-1)*cipher->blockLen/8];
			  }


			}
		}
		/* save IV */
		for (j = 0; j < cipher->blockLen/32; j++) {
		  for(t = 0; t < 4; t++){
			     cipher->IV[t+4*j] = (AES_BYTE) input[4*j+t + (i-1)*cipher->blockLen/8];
		  }
		}
		break;
d442 2
a443 2
	default: return AES_BAD_CIPHER_STATE;
	}
d445 1
a445 1
	return numBlocks*cipher->blockLen;
d448 2
a449 2
int aes_blockDecryptEqvtInv(aes_cipherInstance *cipher,
	aes_keyInstance *key, AES_BYTE *input, int inputLen, AES_BYTE *outBuffer)
d451 2
a452 2
	int i, j, t, numBlocks;
	AES_BYTE block[4][AES_MAXBC];
d454 6
a459 5
	if (cipher == NULL ||
		key == NULL ||
		key->direction == AES_DIR_ENCRYPT /* ||
	    cipher->blockLen != key->blockLen */) {
	  if(cipher == NULL){
d461 2
a462 2
	  }
	  if(key  == NULL){
d464 1
a464 1
	  }
d466 1
a466 1
	  if(cipher->blockLen != key->blockLen){
a469 16
	  }
		return AES_BAD_CIPHER_STATE;
	}

        /* check parameter consistency: */
        if (key == NULL ||
                key->direction != AES_DIR_DECRYPT ||
                (key->keyLen != 128 && key->keyLen != 192 && key->keyLen != 256)) {
	  fprintf(stderr,"key matrix bad\n");
                return AES_BAD_KEY_MAT;
        }
        if (cipher == NULL ||
                (cipher->mode != AES_MODE_ECB && cipher->mode != AES_MODE_CBC && cipher->mode != AES_MODE_CFB1) ||
                (cipher->blockLen != 128 && cipher->blockLen != 192 && cipher->blockLen != 256)) {
	  fprintf(stderr,"mode or block length incorrect\n");
                return AES_BAD_CIPHER_STATE;
d471 30
a500 9
	

	numBlocks = inputLen/cipher->blockLen;
	
	switch (cipher->mode) {
	case AES_MODE_ECB: 
		for (i = 0; i < numBlocks; i++) {
			for (j = 0; j < cipher->blockLen/32; j++) {
			  for(t = 0; t < 4; t++){
d502 5
a506 5
					block[t][j] = input[4*j+t] & 0xFF;
			  }
			}
			__rijndaelDecryptEqvtInv (block, key->keyLen, cipher->blockLen, key->keySched);
			for (j = 0; j < cipher->blockLen/32; j++) {
d508 12
a519 12
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
d521 2
a522 2
		  }
		}
d524 1
a524 1
		__rijndaelDecryptEqvtInv (block, key->keyLen, cipher->blockLen, key->keySched);
d526 6
a531 6
		for (j = 0; j < cipher->blockLen/32; j++) {
			/* exor the IV and parse rectangular array into output ciphertext bytes */
		  for(t = 0; t < 4; t++){
				outBuffer[4*j+t] = (AES_BYTE) (block[t][j] ^ cipher->IV[t+4*j]);
		  }
		}
d533 2
a534 2
		/* next blocks */
		for (i = 1; i < numBlocks; i++) {
d536 2
a537 2
		  for (j = 0; j < cipher->blockLen/32; j++) {
		    for(t = 0; t < 4; t++){
d539 5
a543 5
		      /*block[t][j] = input[cipher->blockLen/8+4*j+t] & 0xFF;
		       */
block[t][j] = input[4*j+t + i*cipher->blockLen/8] & 0xFF;
		    }
		  }
d545 1
a545 1
		  __rijndaelDecryptEqvtInv (block, key->keyLen, cipher->blockLen, key->keySched);
d547 1
a547 1
		  for (j = 0; j < cipher->blockLen/32; j++) {
d549 11
a559 17
				       into output ciphertext bytes */
		    for(t = 0; t < 4; t++){
		      /*outBuffer[cipher->blockLen/8+4*j+t] = (AES_BYTE) (block[t][j] ^ 
			input[4*j+t-4*cipher->blockLen/32]);*/
  outBuffer[4*j+t +i*cipher->blockLen/8] = (AES_BYTE) block[t][j] ^input[4*j+t +(i-1)*cipher->blockLen/8];
		    }


		  }
		}
		/* save IV */
		for (j = 0; j < cipher->blockLen/32; j++) {
		  for(t = 0; t < 4; t++){
			     cipher->IV[t+4*j] = (AES_BYTE) input[4*j+t + (i-1)*cipher->blockLen/8];
		  }
		}
		break;
d561 2
a562 2
	default: return AES_BAD_CIPHER_STATE;
	}
d564 1
a564 1
	return numBlocks*cipher->blockLen;
