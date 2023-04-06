d8 9
a16 9
  /* fixed length fields */
  u32 certType; /* 0 = ECC public key signed by RSA 2048, 
		  1 = RSA2048 public key, signed by RSA 2048
		  2 = RSA 2048 public key, signed by RSA4096
		  In this case it is zero
	       */
  u32 Date; /* for server, unix style timestamp */
  u32 SerialNumber; /* unique serial number of certificate, 
		       unique in each issuer */
d18 1
a18 1
  u8 IssuerName[64]; /* list heirarchy like this: ascii 
d25 3
a27 3
  u32 BBID; /* this is eqvt to subject name, BBID    */
  u8 PublicKey[64]; /* 512 bits for two co-ordinates for ECC*/
  u8 CertificateSignature[256]; /* RSA 2048 signature */
a28 2


