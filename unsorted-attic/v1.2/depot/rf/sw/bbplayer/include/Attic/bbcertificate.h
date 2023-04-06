/*
 * bbcertificate.h (wont compile!!)
 * use this for RSA or ECC certificates for BB or servers
 */
typedef struct {
  /* fixed length fields */
  u32 SerialNumber; /* unique serial number of certificate, 
		       unique in each issuer */
  u8 SignatureAlgorithmID; /* 0=RSA 4096, 1 = RSA 2048, 
			    * 2 = ECC 233 private key size 
			    */
  u8 PublicKeyAlgorithmID; /* same as before, remember ECC233 
 			    * public key size is 466, store as 512 
			    */
  u8 IssuerNameSize; /* size of later field, max 256 bytes */
  u8 SubjectNameSize; /* size of later field, max 256 bytes*/
  u16 ExponentSize; /* in bytes, size of exponent: 
		     * could be zero if public key is ECC 
		     */


  /*variable length fields */
  u8 IssuerName[IssuerNameSize]; /* list heirarchy like this: ascii 
				  * string with xxxxxxxx representing 
				  * numbers in hex eg LS0000000f is 
				  * license server 15. pad with nulls.
				  * Root-LSCAxxxxxxxx-LSxxxxxxxx or
				  * Root-MSCAxxxxxxxx-MSxxxxxxxx
				  */
  u8 SubjectName[SubjectNameSize]; /* suffix only: in case of 
				    *  BBID: BBxxxxxxxx
				    */
  u8 PublicKey[PublicKeySize]; /* this could be 256 for RSA2048 or 64 for ECC*/
  u8 CertificateSignature[SignatureSize]; /* could be 512 for RSA4096 
					   * or 256 for RSA2048 
					   */
  u8  Exponent[ExponentSize]; /* optional field if RSA is present */
} bBCertificate;


