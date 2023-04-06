d7 1
a7 1
  u8 certType; /* 0 = ECC public key signed by RSA 2048, 
d12 1
a12 1
  u8 Date[16]; /* for browsing, ascii date or timestamp */
d27 2
a28 2
  u8 PublicKey[256]; /* 256 for RSA2048, padded with zeros*/
  u8  Exponent[4]; /* exponent */
