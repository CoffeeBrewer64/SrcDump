#include "cert.h"

static BbCertId* gsCertList[SA_MAX_NUM_CERTS];
static int gsNumCerts = 0;

int saCertInit(u8 *certs,u32 bytes)
{
    int i;

    gsNumCerts = *(u32 *)certs;
    if(gsNumCerts >= SA_MAX_NUM_CERTS)
        return SACERT_ERR;

    gsCertList[0] = (BbCertId *)(certs+sizeof(u32));
    for(i=1;i<gsNumCerts;i++){
        switch(gsCertList[i-1]->certType){
        case BB_CERT_TYPE_SERVER:
            gsCertList[i] = (BbCertId *)(((u8 *)gsCertList[i-1]) + 
                                         sizeof(BbRsaCert));
            break;
        case BB_CERT_TYPE_BB:
            gsCertList[i] = (BbCertId *)(((u8 *)gsCertList[i-1]) + 
                                         sizeof(BbEccCert));
            break;
        default:
            return SACERT_ERR;
        }
    }
    gsCertList[i] = NULL;

    return BB_SYSAPP_PASS;
}

int saCertCreateChain(u8 *certs,const char *name,BbCertBase **chain)
{
    int i,j,indx,chainIndx=0;
    char *delims[SA_MAX_NUM_CERTS], *issuer;

    if(name==NULL)
        /* name required to be non-null */
        return SACERT_ERR;

    /* use string following last delimiter, if present */
    for(indx=strlen(name)-1; indx>=0; indx--)
        if(name[indx]=='-')
            break;
    indx++;

    for(i=0; 
        (i<gsNumCerts) && strcmp(gsCertList[i]->name.server,&(name[indx])); 
        i++){}

    if(i==gsNumCerts)
        return SACERT_ERR;

    chain[chainIndx++]=gsCertList[i];
    issuer=(char *)gsCertList[i]->issuer;

    /* find name delimeters */
    indx=0;
    for(i=0;i<sizeof(BbServerName);i++){
        if(issuer[i]=='\0')
            break;
        else if(issuer[i]=='-'){
            if(indx==BB_CERT_CHAIN_MAXLEN)
                /* too many certs in chain */
                return SACERT_ERR;
            delims[indx++]=&issuer[i];
        }
    }
    if(i==sizeof(BbServerName))
        /* chain improperly terminated */
        return SACERT_ERR;

    for(i=indx-1;i>=0;i--){
        for(j=0;j<gsNumCerts;j++){
            if(strncmp(gsCertList[j]->name.server,delims[i]+1,
                       i==(indx-1) ? strlen(delims[i]+1) : 
                       delims[i+1]-delims[i]-1)==0){
                chain[chainIndx++]=gsCertList[j];
                break;
            }
        }
        if(j==gsNumCerts)
            /* could not find cert specified in chain */
            return SACERT_ERR;
    }

    return BB_SYSAPP_PASS;
}
