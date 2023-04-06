#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

#include <PR/bbtypes.h>
#include <PR/bcp.h>
#include <PR/bbvirage.h>
#include <PR/bbmetadata.h>
#include <PR/bbcert.h>
#include <PR/bbnand.h>


/* 
 * to get virage2 data blob 
 */

int getVirage2Data(FILE *constantsFilePtr, 
                   u32 bbID, 
                   u32 privateKey[8],   
                   u32 rand[12], 
                   void *virage2data);

/* to get eTicket or ticket data structure
 */
int getUnsignedTicket(BbContentMetaData *metadata, 
                      u32 *bbID, 
                      BbEccCert *bbCert, 
                      u32 crlVersions[4], 
                      BbEccPrivateKey serverPrivateKey,
                      void *ticket);

/* 
 * get Certificate for BB 
 */
int generateUnsignedBBCert(u32 timestamp, 
                           u32 serialNumber, 
                           u8 *name, u32 bbID, 
                           u8 privateKey[32],
                           void *bbcert);

/*
 * get Unsigned CRL
 */

int generateUnsignedCRL(u32 version, 
                        u32 date, 
                        u8 *issuername, 
                        u32 numberRevoked, 
                        u32 *serialNumbers,
                        void *crl,
                        int *crlsize);

/* 
 * get RSA certs
 */

int generateUnsignedRSACert(u32 certificateType, 
                            u32 timestamp, 
                            u32 serialNumber, 
                            u8 *issuername, 
                            u8 *subjectnamesuffix, 
                            u8 publicKey[256], 
                            u32 exponent,
                            void *rsacert);

/* 
 * create content meta data blob
 */
int generateUnsignedContentMetaData(u8 *contentDesc, 
                                    u32 contentDescSize, 
                                    u32 contentID, 
                                    u32 contentSize, 
                                    u32 contentTypeandKey, 
                                    BbAesKey contentKey, 
                                    FILE *contentFileptr, 
                                    u32 initVector[4], 
                                    u32 loadAddress, 
                                    u32 bootLength, 
                                    u32 compressRecrypt, 
                                    u32 sizeState, 
                                    u32 hwAccessRights, 
                                    u32 secureKernelRights,
                                    void *metadata);





