d132 1
a132 1
int makeKey(keyInstance *key, BYTE direction, int keyLen, int blockLen, unsigned char *keyMaterial, int isAscii);
d134 1
a134 1
int makeKeyEqvtInv(keyInstance *key, BYTE direction, int keyLen, int blockLen, unsigned char *keyMaterial, int isAscii);
d136 1
a136 1
int cipherInit(cipherInstance *cipher, BYTE mode, unsigned char *IV, int blockLen, int isAscii);
d138 1
a138 1
int blockEncrypt(cipherInstance *cipher, keyInstance *key, BYTE *input, 
d141 1
a141 1
int blockDecrypt(cipherInstance *cipher, keyInstance *key, BYTE *input,
d143 1
a143 1
int blockDecryptEqvtInv(cipherInstance *cipher, keyInstance *key, BYTE *input,
d146 1
a146 1
int cipherUpdateRounds(cipherInstance *cipher, keyInstance *key, BYTE *input, 
