/*
 * bbrsacert.h 
 * use this for RSA certificates, fixed length accomodates upto 4096 RSA
 * signature
 */
typedef struct {
    u32 certType;	/* 0 = ECC public key signed by RSA 2048, 
			   1 = RSA2048 public key, signed by RSA 2048
			   2 = RSA 2048 public key, signed by RSA4096
			   In this case it is 1 or 2.
		         */
    u32 date;		/* for server, timestamp */
    u32 serialNumber;	/* unique serial number of certificate, 
		       	   unique in each issuer */
  
    /*variable length fields */
    u8 issuerName[64];	/* list heirarchy like this: null appended ascii 
		         * string with xxxxxxxx representing 
		         * numbers in hex eg LS0000000f is 
		         * license server 15. pad with nulls.
		         * Root-LSCAxxxxxxxx-LSxxxxxxxx or
		         * Root-MSCAxxxxxxxx-MSxxxxxxxx
		         */
    u8 subjectName[16];	/* suffix only: in case of LS
		         *  LSxxxxxxxx or LSCAxxxxxxxx
		         */
    u8 publicKey[256];	/* 256 for RSA2048, padded with zeros in MSB*/
    u32 exponent;	/* exponent */
    u8 signature[512];	/* could be 512 for RSA4096 
			 * or 256 for RSA2048 
			 * depending on certType
			 * certificate is over all contents upto here
			 * padded as specified by SHA-1 and
			 * padded again for RSA
			 */
} BbRsaCert;
