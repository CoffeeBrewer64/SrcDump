
/**********************************************
 *
 * customECCCert.h
 *
 * custom ECC Cert for < 256 bit ECC key data, signed by RSA
 *
 **********************************************/


#ifndef _BBP_CUST_ECC_CERT_H_
#define _BBP_CUST_ECC_CERT_H_

typedef struct customECCCert {
  u8 versionNumber;
  u32 serialNumber;
  u8 signatureAlgorithm; /* RSA 1024 or 2048 bit or ECDSA  */
  u8 issuerName[16];
  u8 validity[32]; /* string not used by software */
  u8 subject[2]; /* server identifier */
  u8 publicKeyAlgorithm; /* hardcode to ECDH-233 */
  u8 publicKey[64]; /* leading zeros, 233*2 bits */
  
  /* 
   * Parameters 
   */
  u8 fieldID; /* hardcode to characteristic-two */
  u8 curve[64]; /* b parameter only, no Koblitz curve */
  u8 basePoint_x[64];
  u8 basePoint_y[64]; /* assume 256 bits each, no point compression*/
  u8 order[64]; /* check this...approx !!!*/

  /*
   * Signature 
   */
  u8 signature[256]; /* leading zeros if less than RSA 2048 bit*/
} customECCCert;

#endif
