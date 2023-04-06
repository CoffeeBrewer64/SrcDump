/* rijndael-api-ref.h   v2.0   August '99
 * Reference ANSI C code
 */
/*
                        ------------------------------
                        Rijndael ANSI C Reference Code
                        ------------------------------

                                October 24, 2000

                                  Disclaimer


This software package was submitted to the National Institute of Standards and
Technology (NIST) during the Advanced Encryption Standard (AES) development
effort by Joan Daemen and Vincent Rijmen, the developers of the Rijndael algorithm.

This software is distributed in compliance with export regulations (see below), and
it is intended for non-commercial use, only.   NIST does not support this software 
and does not provide any guarantees or warranties as to its performance, fitness 
for any particular application, or validation under the Cryptographic Module
Validation Program (CMVP) <http://csrc.nist.gov/cryptval/>.  NIST does not accept 
any liability associated with its use or misuse.  This software is provided as-is. 
By accepting this software the user agrees to the terms stated herein.

                            -----------------------

                              Export Restrictions


Implementations of cryptography are subject to United States Federal
Government export controls.  Export controls on commercial encryption products 
are administered by the Bureau of Export Administration (BXA) 
<http://www.bxa.doc.gov/Encryption/> in the U.S. Department of Commerce. 
Regulations governing exports of encryption are found in the Export 
Administration Regulations (EAR), 15 C.F.R. Parts 730-774.
*/


/*  AES Cipher header file for ANSI C Submissions
      Lawrence E. Bassham III
      Computer Security Division
      National Institute of Standards and Technology

      April 15, 1998

    This sample is to assist implementers developing to the Cryptographic 
API Profile for AES Candidate Algorithm Submissions.  Please consult this 
document as a cross-reference.

    ANY CHANGES, WHERE APPROPRIATE, TO INFORMATION PROVIDED IN THIS FILE
MUST BE DOCUMENTED.  CHANGES ARE ONLY APPROPRIATE WHERE SPECIFIED WITH
THE STRING "CHANGE POSSIBLE".  FUNCTION CALLS AND THEIR PARAMETERS CANNOT 
BE CHANGED.  STRUCTURES CAN BE ALTERED TO ALLOW IMPLEMENTERS TO INCLUDE 
IMPLEMENTATION SPECIFIC INFORMATION.
*/

#define AES_MAXBC			(256/32)
#define AES_MAXKC			(256/32)
#define AES_MAXROUNDS			14


/*  Defines:
	Add any additional defines you need
*/

#define     AES_DIR_ENCRYPT     0    /*  Are we encrpyting?  */
#define     AES_DIR_DECRYPT     1    /*  Are we decrpyting?  */
#define     AES_MODE_ECB        1    /*  Are we ciphering in ECB mode?   */
#define     AES_MODE_CBC        2    /*  Are we ciphering in CBC mode?   */
#define     AES_MODE_CFB1       3    /*  Are we ciphering in 1-bit CFB mode? */
#define     AES_TRUE            1
#define     AES_FALSE           0
#define	AES_BITSPERBLOCK		128		/* Default number of bits in a cipher block */

/*  Error Codes - CHANGE POSSIBLE: inclusion of additional error codes  */
#define     AES_BAD_KEY_DIR        -1  /*  Key direction is invalid, e.g.,
					unknown value */
#define     AES_BAD_KEY_MAT        -2  /*  Key material not of correct 
					length */
#define     AES_BAD_KEY_INSTANCE   -3  /*  Key passed is not valid  */
#define     AES_BAD_CIPHER_MODE    -4  /*  Params struct passed to 
					cipherInit invalid */
#define     AES_BAD_CIPHER_STATE   -5  /*  Cipher in wrong state (e.g., not 
					initialized) */
#define     AES_BAD_CIPHER_INSTANCE -7 

#define     AES_BAD_INPUT	    -8 /* input length is bad */


/*  CHANGE POSSIBLE:  inclusion of algorithm specific defines  */
#define     AES_MAX_KEY_SIZE	64  /* # of ASCII char's needed to
					represent a key */
#define     AES_MAX_IV_SIZE		AES_BITSPERBLOCK/8  /* # bytes needed to
					represent an IV  */

/*  Typedefs:

	Typedef'ed data storage elements.  Add any algorithm specific 
parameters at the bottom of the structs as appropriate.
*/

typedef    unsigned char    AES_BYTE;

/*  The structure for key information */
typedef struct {
      AES_BYTE  direction;	/*  Key used for encrypting or decrypting? */
      int   keyLen;	/*  Length of the key  */
      char  keyMaterial[AES_MAX_KEY_SIZE+1];  /*  Raw key data in ASCII,
                                    e.g., user input or KAT values */
      /*  The following parameters are algorithm dependent, replace or
      		add as necessary  */
      int   blockLen;   /* block length */
      AES_BYTE keySched[AES_MAXROUNDS+1][4][AES_MAXBC];	/* key schedule		*/
      } aes_keyInstance;

/*  The structure for cipher information */
typedef struct {
      AES_BYTE  mode;            /* MODE_ECB, MODE_CBC, or MODE_CFB1 */
      AES_BYTE  IV[AES_MAX_IV_SIZE]; /* A possible Initialization Vector for 
      					ciphering */
      /*  Add any algorithm specific parameters needed here  */
      int   blockLen;    	/* Sample: Handles non-128 bit block sizes
      					(if available) */
      AES_BYTE	tmp[AES_MAX_IV_SIZE];
      } aes_cipherInstance;


/*  Function protoypes  */
/*  CHANGED: aes_makeKey(): parameter blockLen added
                        this parameter is absolutely necessary if you want to
			setup the round keys in a variable block length setting 
	     aes_cipherInit(): parameter blockLen added (for obvious reasons)		
 */
int aes_makeKey(aes_keyInstance *key, AES_BYTE direction, int keyLen, int blockLen, char *keyMaterial);

int aes_makeKeyEqvtInv(aes_keyInstance *key, AES_BYTE direction, int keyLen, int blockLen, char *keyMaterial);

int aes_cipherInit(aes_cipherInstance *cipher, AES_BYTE mode, char *IV, int blockLen);

int aes_blockEncrypt(aes_cipherInstance *cipher, aes_keyInstance *key, AES_BYTE *input, 
			int inputLen, AES_BYTE *outBuffer);

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

