d69 8
a76 8
#define     DIR_ENCRYPT     0    /*  Are we encrpyting?  */
#define     DIR_DECRYPT     1    /*  Are we decrpyting?  */
#define     MODE_ECB        1    /*  Are we ciphering in ECB mode?   */
#define     MODE_CBC        2    /*  Are we ciphering in CBC mode?   */
#define     MODE_CFB1       3    /*  Are we ciphering in 1-bit CFB mode? */
#define     TRUE            1
#define     FALSE           0
#define	BITSPERBLOCK		128		/* Default number of bits in a cipher block */
d79 1
a79 1
#define     BAD_KEY_DIR        -1  /*  Key direction is invalid, e.g.,
d81 1
a81 1
#define     BAD_KEY_MAT        -2  /*  Key material not of correct 
d83 2
a84 2
#define     BAD_KEY_INSTANCE   -3  /*  Key passed is not valid  */
#define     BAD_CIPHER_MODE    -4  /*  Params struct passed to 
d86 1
a86 1
#define     BAD_CIPHER_STATE   -5  /*  Cipher in wrong state (e.g., not 
d88 1
a88 1
#define     BAD_CIPHER_INSTANCE   -7 
d92 1
a92 1
#define     MAX_KEY_SIZE	64  /* # of ASCII char's needed to
d94 1
a94 1
#define     MAX_IV_SIZE		BITSPERBLOCK/8  /* # bytes needed to
d103 1
a103 1
typedef    unsigned char    BYTE;
d107 1
a107 1
      BYTE  direction;	/*  Key used for encrypting or decrypting? */
d113 1
a113 1
      } keyInstance;
d117 2
a118 2
      BYTE  mode;            /* MODE_ECB, MODE_CBC, or MODE_CFB1 */
      BYTE  IV[MAX_IV_SIZE]; /* A possible Initialization Vector for 
d123 1
a123 1
      } cipherInstance;
d132 1
a132 1
int aes_BlockMakeKey(keyInstance *key, BYTE direction, int keyLen, int blockLen, unsigned char *keyMaterial, int isAscii);
d134 1
a134 1
int aes_BlockMakeKeyEqvtInv(keyInstance *key, BYTE direction, int keyLen, int blockLen, unsigned char *keyMaterial, int isAscii);
d136 1
a136 1
int aes_BlockCipherInit(cipherInstance *cipher, BYTE mode, unsigned char *IV, int blockLen, int isAscii);
d138 2
a139 2
int aes_BlockEncrypt(cipherInstance *cipher, keyInstance *key, BYTE *input, 
			int inputLen, BYTE *outBuffer);
d141 4
a144 4
int aes_BlockDecrypt(cipherInstance *cipher, keyInstance *key, BYTE *input,
			int inputLen, BYTE *outBuffer);
int aes_BlockDecryptEqvtInv(cipherInstance *cipher, keyInstance *key, BYTE *input,
			int inputLen, BYTE *outBuffer);
d146 2
a147 2
int aes_BlockCipherUpdateRounds(cipherInstance *cipher, keyInstance *key, BYTE *input, 
                        int inputLen, BYTE *outBuffer, int Rounds);
