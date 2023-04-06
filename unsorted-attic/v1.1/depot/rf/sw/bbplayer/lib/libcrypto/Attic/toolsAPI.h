d1 10
a11 1
#include "algorithms.h"
d17 5
a21 5
int 
returnCode = getVirage2Data(u32 bbID, 
			    u32 privateKey[8], 
			    u32 rand[12], 
			    void *virage2data);
d25 6
a30 6
returnCode = getUnsignedTicket(BbContentMetaData *metadata, 
			       u32 *bbID, 
			       BbEccCert *bbCert, 
			       u32 crlVersions[4], 
			       BbEccPrivateKey serverPrivateKey,
			       void *ticket);
d35 5
a39 6
int 
returnCode = generateUnsignedBBCert(u32 timestamp, 
				    u32 serialNumber, 
				    u8 *name, u32 bbID, 
				    u8 privateKey[32],
				    void *bbcert);
d45 7
a51 8
int
returnCode = generateUnsignedCRL(u32 version, 
				 u32 date, 
				 u8 *issuername, 
				 u32 numberRevoked, 
				 u32 *serialNumbers,
				 void *crl,
				 int *crlsize);
d57 8
a64 9
int 
returnCode = generateUnsignedRSACert(u32 certificateType, 
				     u32 timestamp, 
				     u32 serialNumber, 
				     u8 *issuername, 
				     u8 *subjectnamesuffix, 
				     u8 publicKey[256], 
				     u32 exponent,
				     void *rsacert);
d69 15
a83 16
int 
returnCode = generateUnsignedContentMetaData(u8 *contentDesc, 
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
