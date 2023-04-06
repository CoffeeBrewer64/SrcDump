#include <PR/bcp.h>
#include <PR/bbboot.h>
#include <PR/bbnand.h>
#include <PR/bbticket.h>
#include <PR/bbvirage.h>
#include <PR/bbfs.h>
#include <PR/bbcert.h>
#include <PR/bbskapi.h>
#include <sha1.h>
#include "util.h"
#include "skerror.h"
#include "cert.h"
#include "cert.h"


extern BbRsaPublicKey4096 gRootKey;
extern BbRsaExponent gRootExp;
/*
int 
isMatch(BbServerName 
*/
/* update ca crl version number for revocation of either CPCRL or TSCRL
 */
int updateCACRL(BbContentMetaDataHead *cmdh, BbCrlBundle *carl, BbVirage01 *viragedata){
    SkDataChain dataChain[1];
    int sizeofcrl;
    int result;
    /* check internal virage number wrt cmdh */
    if(cmdh->caCrlVersion == (u32) ( viragedata->caCrlVersion)){
        /* no need to update, quit */
        return SK_API_SUCCESS;
    }
    else if (cmdh->caCrlVersion < (u32) (viragedata->caCrlVersion)){
        /* come back with more recent cacrl */
        return SK_API_INVALID_CRL;
    }
    else{
        /* check later if we need to check for version number ++ or 
         *  any greater number 
         */
        /* update cacrl number in flash */
        /* check if issuer is root */
        if (strcmp(carl->head->issuer, BB_CERT_STR_ROOT) != 0) {
            return SK_API_INVALID_CRL;
        }
        /* verify root signature on crl is good */
        sizeofcrl = sizeof(BbCrlHead) - sizeof(u32) -sizeof(BbGenericSig);
        sizeofcrl = sizeofcrl + (carl->head->numberRevoked) * sizeof(u32);
        /* skip initial signature type and signature */
        dataChain[0].data = (u8 *) (carl + sizeof(u32) +sizeof(BbGenericSig));
        dataChain[0].size = sizeofcrl;
        result = verifyRsaSigMult(dataChain, 1, (u32 *)gRootKey, gRootExp, BB_SIG_TYPE_RSA4096, &(carl->head->signature));
        if (result != SK_SUCCESS){
            return SK_API_INVALID_CRL;
        }
        else if(result == SK_SUCCESS){
            /* reset to zero down the hierarchy depending on which tree 
             * is revoked this time: LS or CP or both
             */
            viragedata->caCrlVersion = (u8) cmdh->caCrlVersion;
            if((carl->head->revocationType == CPCA_REV) ||
               (carl->head->revocationType == CPLSCA_REV)){
                viragedata->cpCrlVersion = 0;
                viragedata->contentRlVersion = 0;
            }
            else if((carl->head->revocationType == LSCA_REV) ||
                    (carl->head->revocationType == CPLSCA_REV)){
                viragedata->tsCrlVersion = 0;
            }
            result = v01Update(viragedata);
        }
        return result;
    }

}

/* see if the binary 32 bits matches the last 8 characters of the Server Name
 * skip the string supplied in the server name
 */
int isMatch(BbServerName name, BbServerName entry, BbServerName skip){
    int skiplen = 0;
    /*
      u32 word_read= 0x0;
      u8 buffer[4];
      if(strncmp(name, skip, sizeof(skip)) !=0 ){
      return SK_API_FAIL;
      }
      
      asciiToBin(name + strlen(skip), 4, buffer);
      word_read = (buffer[0] << 24)|(buffer[1] <<16)|(buffer[2] <<8)|(buffer[3]);
    */
    skiplen = strlen(skip);
    if(strcmp(entry, name + skiplen)==0){
        return SK_API_SUCCESS;
        /* its on revocation list! */
    }
    else{
        return SK_API_FAIL;
    }
/*
    if(word_read == entry){
        return SK_API_SUCCESS; 
    }
    else{
        return SK_API_FAIL;
    }
*/
}

int updateCPCRL(BbContentMetaDataHead *cmdh, BbAppLaunchCrls *crls, BbVirage01 *viragedata){
    /* check if CPCRL update is needed */
    SkDataChain dataChain[1];
    
    int sizeofcrl;
    int result, i;
   
    /* check internal virage number wrt cmdh */
    if(cmdh->cpCrlVersion == (u32) ( viragedata->cpCrlVersion)){
        /* no need to update, quit */
        return SK_API_SUCCESS;
    }
    else if (cmdh->cpCrlVersion < (u32) (viragedata->cpCrlVersion)){
        /* come back with more recent cacrl */
        return SK_API_INVALID_CRL;
    }
    else{
        /* possible update if signatures match and signer not revoked */
        
        for (i =0; i< (crls->carl)->head->numberRevoked; i++){
            result = isMatch(crls->cprl->head->issuer, (crls->carl)->list[i], "Root-CPCA");
            if(result == SK_API_SUCCESS) break;
        }
        if (result == SK_API_SUCCESS){
            /* if CA was revoked */
            return SK_API_INVALID_CRL;
        }
        else{
            /* check CA cert sign */
            if(strcmp(crls->cprl->head->issuer, crls->cprl->certChain[1]->issuer)!= 0){
                /* the CA that issued the cprl's name is not on his own
                       certificate
                */
                return SK_API_INVALID_CRL;
            }
            /* check the cert now */
            result = verifyCertChain(crls->cprl->certChain);
            if(result != SK_SUCCESS){
                return result;
            }
            /* check the sign on the CRL itself */
                   
            sizeofcrl = sizeof(BbCrlHead) - sizeof(u32) -sizeof(BbGenericSig);
            sizeofcrl = sizeofcrl + (crls->cprl->head->numberRevoked) * sizeof(BbServerName);
            /* skip initial signature type and signature */
            dataChain[0].data = (u8 *) (crls->cprl + sizeof(u32) +sizeof(BbGenericSig));
            dataChain[0].size = sizeofcrl;
            result = verifyRsaSigMult(dataChain,1, ((BbRsaCert *)crls->cprl->certChain[0])->publicKey, ((BbRsaCert *) crls->cprl->certChain[0])->exponent, BB_SIG_TYPE_RSA4096, &crls->cprl->head->signature);
            if (result != SK_SUCCESS){
                return SK_API_INVALID_CRL;
            }
            /* now update the numbers in virage */
            if (result != SK_SUCCESS){
                return SK_API_INVALID_CRL;
            }
            else if(result == SK_SUCCESS){
                /* reset to zero down the hierarchy depending on which tree 
                 * is revoked this time: LS or CP or both
                 */
                viragedata->cpCrlVersion = (u8) cmdh->cpCrlVersion;
                /* if the cp is revoked, any contentRL should also be reset*/
                viragedata->contentRlVersion = 0;
            }
            result = v01Update(viragedata);
            return result;     
        }
    }
}


int updateTSCRL(BbTicketBundle *ticketBundle, BbAppLaunchCrls *crls, BbVirage01 *viragedata){
    /* check if TSCRL update is needed */
    SkDataChain dataChain[1];
    
    int sizeofcrl;
    int result, i;
   
    /* check internal virage number wrt cmdh */
    if(ticketBundle->ticket->head.tsCrlVersion == (u32) ( viragedata->tsCrlVersion)){
        /* no need to update, quit */
        return SK_API_SUCCESS;
    }
    else if ((ticketBundle->ticket->head).tsCrlVersion < (u32) (viragedata->tsCrlVersion)){
        /* come back with more recent cacrl */
        return SK_API_INVALID_CRL;
    }
    else{
        /* possible update if signatures match and signer not revoked */
        /* check if issuer is in CACRL */
        for (i =0; i< (crls->carl)->head->numberRevoked; i++){
            result = isMatch(crls->tsrl->head->issuer, (crls->carl)->list[i], "Root-TSCA");
            if(result == SK_API_SUCCESS) break;
        }
        if (result == SK_API_SUCCESS){
            /* if CA was revoked */
            return SK_API_INVALID_CRL;
        }
        else{
            /* check CA cert sign */
            if(strcmp(crls->tsrl->head->issuer, crls->tsrl->certChain[0]->issuer)!= 0){
                /* the CA that issued the tsrl's name is not on his own
                       certificate
                */
                return SK_API_INVALID_CRL;
            }
            /* check the cert now */
            result = verifyCertChain(crls->tsrl->certChain);
            if(result != SK_SUCCESS){
                return result;
            }
            /* check the sign on the CRL itself */
                   
            sizeofcrl = sizeof(BbCrlHead) - sizeof(u32) -sizeof(BbGenericSig);
            sizeofcrl = sizeofcrl + (crls->tsrl->head->numberRevoked) * sizeof(BbServerName);
            /* skip initial signature type and signature */
            dataChain[0].data = (u8 *) (crls->tsrl + sizeof(u32) +sizeof(BbGenericSig));
            dataChain[0].size = sizeofcrl;
            result = verifyRsaSigMult(dataChain,1,  ((BbRsaCert *)crls->tsrl->certChain[0])->publicKey, ((BbRsaCert *) crls->tsrl->certChain[0])->exponent, BB_SIG_TYPE_RSA4096, &(crls->tsrl->head->signature));
            if (result != SK_SUCCESS){
                return SK_API_INVALID_CRL;
            }
            /* now update the numbers in virage */
            if (result != SK_SUCCESS){
                return SK_API_INVALID_CRL;
            }
            else if(result == SK_SUCCESS){
                viragedata->tsCrlVersion = (u8)(ticketBundle->ticket->head).tsCrlVersion;
                
            }
            result = v01Update(viragedata);
            return result;     
        }
    }
}



int updateContentRL(BbContentMetaDataHead *cmdh, BbAppLaunchCrls *crls, BbVirage01 *viragedata){
    /* check if CPCRL update is needed */
    SkDataChain dataChain[1];
    BbRsaCert *nextcert;
    int sizeofcrl;
    int result, i;
   
    /* check internal virage number wrt cmdh */
    if(cmdh->contentRlVersion == (u32) ( viragedata->contentRlVersion)){
        /* no need to update, quit */
        return SK_API_SUCCESS;
    }
    else if (cmdh->contentRlVersion < (u32) (viragedata->contentRlVersion)){
        /* come back with more recent cacrl */
        return SK_API_INVALID_CRL;
    }
    else{
        /* possible update if signatures match and signer not revoked */
        /* check if CP is revoked */
        for (i =0; i< (crls->cprl)->head->numberRevoked; i++){
            result = isMatch(crls->crl->head->issuer, (crls->cprl)->list[i], "Root-CPCA");
            if(result == SK_API_SUCCESS) break;
        }
        if (result == SK_API_SUCCESS){
            /* if CA was revoked */
            return SK_API_INVALID_CRL;
        }
        else{
            /* check CP is the same */
            if(strcmp(crls->crl->head->issuer, crls->crl->certChain[0]->issuer)!= 0){
                /* the CA that issued the cprl's name is not on his own
                       certificate
                */
                return SK_API_INVALID_CRL;
            }
            /* check the name of the CPCA if that is on revocation list */
            /* get to the next cert*/
            nextcert = (BbRsaCert *)crls->crl->certChain[1];
            for(i =0; i < (crls->carl)->head->numberRevoked; i++){
                result = strcmp((nextcert->certId).name.server, (crls->carl)->list[i]);
            }
            if(result == 0){
                return SK_API_INVALID_CRL;
            }
            /* check the cert now */
            result = verifyCertChain(crls->crl->certChain);
            if(result != SK_SUCCESS){
                return result;
            }
            /* check the sign on the CRL itself */
                   
            sizeofcrl = sizeof(BbCrlHead) - sizeof(u32) -sizeof(BbGenericSig);
            sizeofcrl = sizeofcrl + (crls->crl->head->numberRevoked) * sizeof(BbServerName);
            /* skip initial signature type and signature */
            dataChain[0].data = (u8 *) (crls->crl + sizeof(u32) +sizeof(BbGenericSig));
            dataChain[0].size = sizeofcrl;
            result = verifyRsaSigMult(dataChain, 1, ((BbRsaCert *)crls->crl->certChain[0])->publicKey, ((BbRsaCert *) crls->crl->certChain[0])->exponent, BB_SIG_TYPE_RSA4096, &(crls->crl->head->signature));
            if (result != SK_SUCCESS){
                return SK_API_INVALID_CRL;
            }
            /* now update the numbers in virage */
            if (result != SK_SUCCESS){
                return SK_API_INVALID_CRL;
            }
            else if(result == SK_SUCCESS){
                /* reset to zero down the hierarchy depending on which tree 
                 * is revoked this time: LS or CP or both
                 */
                viragedata->contentRlVersion = (u8) cmdh->contentRlVersion;
            }
            result = v01Update(viragedata);
            return result;     
        }
    }
    return SK_API_SUCCESS;
}



    
/* update crls in virage with correct version number based
 * on inputs 
 * ticket and cmd related
 * takes input of r/w virage in viragedata structure
 */
int updateCrl(BbTicketBundle *ticketBundle, BbAppLaunchCrls *crls, BbVirage01 *viragedata){
    BbContentMetaDataHead *cmdh = &(ticketBundle->ticket->cmd.head);
    int error;
    /* take care of crls in cmd first
     */

    error = updateCACRL(cmdh, crls->carl, viragedata);
    if(error != 0){
        return error;
    }

    /* if it comes here it has good CACRL
     */
    error = updateCPCRL(cmdh, crls, viragedata);
    if(error != 0){
        return error;
    }
    error = updateContentRL(cmdh, crls, viragedata);
    if(error != 0){
        return error;
    }

    /* next take care of ticket server revocation
     */
    error = updateTSCRL(ticketBundle, crls, viragedata);
    if(error != 0){
        return error;
    }
}
