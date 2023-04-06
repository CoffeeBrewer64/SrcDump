/*
 * bbecccert.h
 * use this for ECC certificates for BB 
 * ECC public key, signed RSA 2048 
 * all big endian representation when stored or transmitted
 */
typedef struct {
    /* fixed length fields */
    u32 certType;	/* 0 = ECC public key signed by RSA 2048, 
			   1 = RSA2048 public key, signed by RSA 2048
			   2 = RSA 2048 public key, signed by RSA4096
			   In this case it is zero
			 */
    u32 date;		/* for server, unix style timestamp */
    u32 serialNumber;	/* unique serial number of certificate, 
		           unique in each issuer */
  
    u8 issuerName[64];	/* list heirarchy like this: ascii 
				  * string with xxxxxxxx representing 
				  * numbers in hex eg LS0000000f is 
				  * license server 15. pad with nulls.
				  * Root-LSCAxxxxxxxx-LSxxxxxxxx or
				  * Root-MSCAxxxxxxxx-MSxxxxxxxx
				  */
    u32 bbId;		/* this is eqvt to subject name, BBID    */
    u8 publicKey[64];	/* 512 bits for two co-ordinates for ECC*/
    u8 signature[256];	/* RSA 2048 signature */
} BbEccCert;
