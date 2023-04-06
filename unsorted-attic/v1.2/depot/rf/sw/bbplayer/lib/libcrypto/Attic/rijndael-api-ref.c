d47 1
a47 1
int makeKey(keyInstance *key, BYTE direction, int keyLen, int blockLen, unsigned char *keyMaterial, int isAscii)
d126 1
a126 1
int makeKeyEqvtInv(keyInstance *key, BYTE direction, int keyLen, int blockLen, unsigned char *keyMaterial, int isAscii)
d211 1
a211 1
int cipherInit(cipherInstance *cipher, BYTE mode, unsigned char *IV, int blockLen, int isAscii)
d247 1
a247 1
int blockEncrypt(cipherInstance *cipher,
d323 1
a323 1
int blockDecrypt(cipherInstance *cipher,
d448 1
a448 1
int blockDecryptEqvtInv(cipherInstance *cipher,
