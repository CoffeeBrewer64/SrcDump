
/**********************************************
 *
 * eTicket.h
 *
 * Definition of eTicket (or content license) for client and server
 *
 **********************************************/

#ifndef _BBP_ETICKET_H_
#define _BBP_ETICKET_H_

typedef struct eTicket {

  /***********************************************
   * Content information or Content MetaData CMD(unencrypted)
   **********************************************/
  u32 contentID;   /* store in network byte order in DB */
  u32 contentSize; /* store in network byte order in DB */
  u8 contentType;
  u8 contentDesc[512]; /* ascii description of content */
  u8 contentImage[000000];

  /***********************************************
   * Owner Information (unencrypted)
   **********************************************/
  u32 BBID; /* store in network byte order in DB */
  
  /***********************************************
   * CRL information (unencrypted)
   **********************************************/
  u8 LSCRLVer; /*zero implies no CRL */
  u8 CACRLVer; /*zero implies no CRL */

  /***********************************************
   * Content security CS (encrypted)
   **********************************************/
  u8 contentKey[16]; /* common content key */
  u8 contentHash[20]; /* SHA hash of content */
  u8 contentAESIV[16]; /* initialization vector */
  u8 contentMetaDataSign[256]; /*RSA 2048 bit sign on (CMD, CS)*/
  
  /***********************************************
   * Content execution information CE (encrypted)
   **********************************************/
  u32 loadAddress; /* store in network byte order */
  u32 bootLength; /* boot partition length*/
  u8 compressEncryptFlag; /* b1: 0/1 boot uncompressed/compressed,
			     b0: 0/1 reencrypt/no-reencrypt
			  */
  u32 sizeState; /* allocate bytes for state */
  u32 HWAccessRights; /* ???????????????????? */
  
  /***********************************************
   * Decryption/verification related information (unencrypted)
   **********************************************/
  u8 serverECCPublicKey[32]; /* ephemeral public key */
  u8 eTicketSign[256];  /*RSA 2048 bit sign on all content*/
  
} eTicket;

/**********************************************
 *
 * Generic Cert with RSA key: 
 * License Server Cert, License Server CA Cert, Content Publisher Cert
 *
 *
 **********************************************/


typedef struct GenericCert{
  u8 stuff;
}GenericCert;

/**********************************************
 *
 * Custom CRL for
 * License Server CRL, License Server CA CRL, Content CRL
 *
 **********************************************/


typedef struct CustomCRL{
  u32 CRLVer; /* store in network byte order */
  u8 timestamp[32]; /* some ascii identifier: for human browsing*/
  u32 numberEntries; /* store in network byte order */
  u32 serialNumbers[MAX_CERTS]; /* store in network byte order */
  u8 signature[512]; /* CA or root signature */
}

#endif 








