
/**********************************************
 *
 * privateData.h
 *
 * Definition of data structure that gets burnt in the chip
 *
 **********************************************/


#ifndef _BBP_PRIV_DATA_H_
#define _BBP_PRIV_DATA_H_

typedef struct privateData {

  u32 BBID; /* stored as network order, from database */
  u8 privateKey[32]; /* stored as network order with leading zeros, 
			from key generation program */
  u8 recryptKeyListKey[16]; /* 128 bit AES key from RNG */
  u8 firstAppKey[16]; /* 128 bit AES key from RNG */
  u8 hashSecureKernel[20]; /* 160 bit SHA hash from RNG */
  u8 stateSavingKey[16]; /* AES key for persistent state from RNG */
  u8 BBSelfMessages[16]; /* AES key for secret messages/data 
			    stored in flash from RNG*/

} privateData;

/*************************************************
 *
 * parameters, used in all servers and client dealing with ECC
 *
 *************************************************/

typedef struct ECCParams {
  u8 fieldID; /* hardcode to characteristic-two */
  u8 curve[64]; /* b parameter only, no Koblitz curve */
  u8 basePoint_x[64];
  u8 basePoint_y[64]; /* assume 256 bits each, no point compression*/
  u8 order[64]; /* check this...approx !!!*/
  u8 primitive_poly[64]; /* ones in non zero coefficients, 
			    each bit is a coefficient of polynomial */
}ECCParams;

#endif
