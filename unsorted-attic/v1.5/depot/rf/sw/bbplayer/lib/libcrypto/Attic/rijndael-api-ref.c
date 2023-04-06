d47 1
a47 1
int aes_BlockMakeKey(keyInstance *key, BYTE direction, int keyLen, int blockLen, unsigned char *keyMaterial, int isAscii)
d56 1
a56 1
        return BAD_KEY_INSTANCE;
d59 1
a59 1
    if ((direction == DIR_ENCRYPT) || (direction == DIR_DECRYPT)) {
d62 1
a62 1
        return BAD_KEY_DIR;
d68 1
a68 1
        return BAD_KEY_MAT;
d78 1
a78 1
          else return BAD_KEY_MAT;
d84 1
a84 1
          else return BAD_KEY_MAT;
d109 1
a109 1
    return TRUE;
d127 1
a127 1
int aes_BlockMakeKeyEqvtInv(keyInstance *key, BYTE direction, int keyLen, int blockLen, unsigned char *keyMaterial, int isAscii)
d139 1
a139 1
        return BAD_KEY_INSTANCE;
d142 1
a142 1
    if ((direction == DIR_ENCRYPT) || (direction == DIR_DECRYPT)) {
d145 1
a145 1
        return BAD_KEY_DIR;
d151 1
a151 1
        return BAD_KEY_MAT;
d161 1
a161 1
          else return BAD_KEY_MAT;
d167 1
a167 1
          else return BAD_KEY_MAT;
d209 1
a209 1
    return TRUE;
d214 1
a214 1
int aes_BlockCipherInit(cipherInstance *cipher, BYTE mode, unsigned char *IV, int blockLen, int isAscii)
d218 1
a218 1
    if ((mode == MODE_ECB) || (mode == MODE_CBC) || (mode == MODE_CFB1)) {
d221 1
a221 1
        return BAD_CIPHER_MODE;
d232 1
a232 1
                else return BAD_CIPHER_INSTANCE;
d238 1
a238 1
                else return BAD_CIPHER_INSTANCE;
d240 1
a240 1
                cipher->IV[i] = (BYTE) j;
d248 1
a248 1
    return TRUE;
d252 2
a253 2
int aes_BlockEncrypt(cipherInstance *cipher,
                 keyInstance *key, BYTE *input, int inputLen, BYTE *outBuffer)
d261 1
a261 1
        key->direction != DIR_ENCRYPT ||
d263 1
a263 1
        return BAD_KEY_MAT;
d266 1
a266 1
        (cipher->mode != MODE_ECB && cipher->mode != MODE_CBC && cipher->mode != MODE_CFB1) ||
d268 1
a268 1
        return BAD_CIPHER_STATE;
d275 1
a275 1
    case MODE_ECB: 
d287 1
a287 1
                    outBuffer[4*j+t] = (BYTE) block[t][j];
d292 1
a292 1
    case MODE_CBC:
d315 2
a316 2
                    /*outBuffer[4*j+t] = (BYTE) block[t][j];*/
                    outBuffer[4*j+t +i*cipher->blockLen/8] = (BYTE) block[t][j];
d328 1
a328 1
    default: return BAD_CIPHER_STATE;
d334 2
a335 2
int aes_BlockDecrypt(cipherInstance *cipher,
                 keyInstance *key, BYTE *input, int inputLen, BYTE *outBuffer)
d342 1
a342 1
        key->direction == DIR_ENCRYPT /* ||
d348 1
a348 1
            return BAD_CIPHER_STATE;
d354 1
a354 1
            return BAD_CIPHER_STATE;
d363 1
a363 1
            return BAD_CIPHER_STATE;
d366 1
a366 1
        return BAD_CIPHER_STATE;
d371 1
a371 1
        key->direction != DIR_DECRYPT ||
d376 1
a376 1
        return BAD_KEY_MAT;
d379 1
a379 1
        (cipher->mode != MODE_ECB && cipher->mode != MODE_CBC && cipher->mode != MODE_CFB1) ||
d384 1
a384 1
        return BAD_CIPHER_STATE;
d391 1
a391 1
    case MODE_ECB: 
d403 1
a403 1
                    outBuffer[4*j+t] = (BYTE) block[t][j];
d408 1
a408 1
    case MODE_CBC:
d423 1
a423 1
                outBuffer[4*j+t] = (BYTE) (block[t][j] ^ cipher->IV[t+4*j]);
d443 1
a443 1
                    /*outBuffer[cipher->blockLen/8+4*j+t] = (BYTE) (block[t][j] ^ 
d445 1
a445 1
                    outBuffer[4*j+t +i*cipher->blockLen/8] = (BYTE) block[t][j] ^input[4*j+t +(i-1)*cipher->blockLen/8];
d453 1
a453 1
    default: return BAD_CIPHER_STATE;
d459 2
a460 2
int aes_BlockDecryptEqvtInv(cipherInstance *cipher,
                        keyInstance *key, BYTE *input, int inputLen, BYTE *outBuffer)
d467 1
a467 1
        key->direction == DIR_ENCRYPT /* ||
d483 1
a483 1
        return BAD_CIPHER_STATE;
d488 1
a488 1
        key->direction != DIR_DECRYPT ||
d493 1
a493 1
        return BAD_KEY_MAT;
d496 1
a496 1
        (cipher->mode != MODE_ECB && cipher->mode != MODE_CBC && cipher->mode != MODE_CFB1) ||
d501 1
a501 1
        return BAD_CIPHER_STATE;
d508 1
a508 1
    case MODE_ECB: 
d520 1
a520 1
                    outBuffer[4*j+t] = (BYTE) block[t][j];
d525 1
a525 1
    case MODE_CBC:
d540 1
a540 1
                outBuffer[4*j+t] = (BYTE) (block[t][j] ^ cipher->IV[t+4*j]);
d562 1
a562 1
                    /*outBuffer[cipher->blockLen/8+4*j+t] = (BYTE) (block[t][j] ^ 
d564 1
a564 1
                    outBuffer[4*j+t +i*cipher->blockLen/8] = (BYTE) block[t][j] ^input[4*j+t +(i-1)*cipher->blockLen/8];
d572 1
a572 1
    default: return BAD_CIPHER_STATE;
