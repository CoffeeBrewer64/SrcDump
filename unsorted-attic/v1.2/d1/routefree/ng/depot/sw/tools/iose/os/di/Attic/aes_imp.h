#ifndef __AES_IMP_H__
#define __AES_IMP_H__

#define __AES_MAXKC	(256/32)
#define __AES_MAXKB	(256/8)
#define __AES_MAXNR	14

#include <stdint.h>

int rijndaelKeySetupEnc(uint32_t rk[/*4*(Nr + 1)*/], const uint8_t cipherKey[], int keyBits);
int rijndaelKeySetupDec(uint32_t rk[/*4*(Nr + 1)*/], const uint8_t cipherKey[], int keyBits);
void rijndaelEncrypt(const uint32_t rk[/*4*(Nr + 1)*/], int Nr, const uint8_t pt[16], uint8_t ct[16]);
void rijndaelDecrypt(const uint32_t rk[/*4*(Nr + 1)*/], int Nr, const uint8_t ct[16], uint8_t pt[16]);

#endif /* __AES_IMP_H__ */
