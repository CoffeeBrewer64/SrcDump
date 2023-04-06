d58 4
a61 3
#define AES_MAXBC			(256/32)
#define AES_MAXKC			(256/32)
#define AES_MAXROUNDS			14
d63 1
d69 8
a76 8
#define     AES_DIR_ENCRYPT     0    /*  Are we encrpyting?  */
#define     AES_DIR_DECRYPT     1    /*  Are we decrpyting?  */
#define     AES_MODE_ECB        1    /*  Are we ciphering in ECB mode?   */
#define     AES_MODE_CBC        2    /*  Are we ciphering in CBC mode?   */
#define     AES_MODE_CFB1       3    /*  Are we ciphering in 1-bit CFB mode? */
#define     AES_TRUE            1
#define     AES_FALSE           0
#define	AES_BITSPERBLOCK		128		/* Default number of bits in a cipher block */
d79 1
a79 1
#define     AES_BAD_KEY_DIR        -1  /*  Key direction is invalid, e.g.,
d81 1
a81 1
#define     AES_BAD_KEY_MAT        -2  /*  Key material not of correct 
d83 2
a84 2
#define     AES_BAD_KEY_INSTANCE   -3  /*  Key passed is not valid  */
#define     AES_BAD_CIPHER_MODE    -4  /*  Params struct passed to 
d86 1
a86 1
#define     AES_BAD_CIPHER_STATE   -5  /*  Cipher in wrong state (e.g., not 
d88 1
a88 3
#define     AES_BAD_CIPHER_INSTANCE -7 

#define     AES_BAD_INPUT	    -8 /* input length is bad */
d92 1
a92 1
#define     AES_MAX_KEY_SIZE	64  /* # of ASCII char's needed to
d94 1
a94 1
#define     AES_MAX_IV_SIZE		AES_BITSPERBLOCK/8  /* # bytes needed to
d103 1
a103 1
typedef    unsigned char    AES_BYTE;
d107 1
a107 1
      AES_BYTE  direction;	/*  Key used for encrypting or decrypting? */
a108 2
      char  keyMaterial[AES_MAX_KEY_SIZE+1];  /*  Raw key data in ASCII,
                                    e.g., user input or KAT values */
d112 2
a113 2
      AES_BYTE keySched[AES_MAXROUNDS+1][4][AES_MAXBC];	/* key schedule		*/
      } aes_keyInstance;
d117 2
a118 2
      AES_BYTE  mode;            /* MODE_ECB, MODE_CBC, or MODE_CFB1 */
      AES_BYTE  IV[AES_MAX_IV_SIZE]; /* A possible Initialization Vector for 
d123 1
a123 2
      AES_BYTE	tmp[AES_MAX_IV_SIZE];
      } aes_cipherInstance;
d127 1
a127 1
/*  CHANGED: aes_makeKey(): parameter blockLen added
d130 1
a130 1
	     aes_cipherInit(): parameter blockLen added (for obvious reasons)		
d132 1
a132 1
int aes_makeKey(aes_keyInstance *key, AES_BYTE direction, int keyLen, int blockLen, char *keyMaterial);
d134 1
a134 1
int aes_makeKeyEqvtInv(aes_keyInstance *key, AES_BYTE direction, int keyLen, int blockLen, char *keyMaterial);
d136 1
a136 1
int aes_cipherInit(aes_cipherInstance *cipher, AES_BYTE mode, char *IV, int blockLen);
d138 2
a139 2
int aes_blockEncrypt(aes_cipherInstance *cipher, aes_keyInstance *key, AES_BYTE *input, 
			int inputLen, AES_BYTE *outBuffer);
d141 4
a144 14
int aes_blockDecrypt(aes_cipherInstance *cipher, aes_keyInstance *key, AES_BYTE *input,
			int inputLen, AES_BYTE *outBuffer);
int aes_blockDecryptEqvtInv(aes_cipherInstance *cipher, aes_keyInstance *key, AES_BYTE *input,
			int inputLen, AES_BYTE *outBuffer);

/* internal routines */
int __rijndaelKeySched (AES_BYTE k[4][AES_MAXKC], int keyBits, int blockBits, 
		AES_BYTE rk[AES_MAXROUNDS+1][4][AES_MAXBC]);
int __rijndaelEncrypt (AES_BYTE a[4][AES_MAXBC], int keyBits, int blockBits, 
		AES_BYTE rk[AES_MAXROUNDS+1][4][AES_MAXBC]);
int __rijndaelDecrypt (AES_BYTE a[4][AES_MAXBC], int keyBits, int blockBits, 
		AES_BYTE rk[AES_MAXROUNDS+1][4][AES_MAXBC]);
int __rijndaelDecryptEqvtInv (AES_BYTE a[4][AES_MAXBC], int keyBits, int blockBits, 
		AES_BYTE rk[AES_MAXROUNDS+1][4][AES_MAXBC]);
d146 2
