#include "rl.h"

#define LAUNCH_CRLS 4

static char* getServerNameStr(char *in)
{
    int indx=strlen(in)-1;
    while(indx>0){
        if(in[indx--]=='-')
            return &in[indx+2];
    }
    return NULL;
}

static int fillCrlBundle(BbCrlHead *rl,u8 *certFile,BbCrlBundle *rlBundle)
{
    char *serverName;

    rlBundle->head = rl;
    rlBundle->list = (BbServerName *)(((u8 *)rl) + sizeof(BbCrlHead));
    serverName = getServerNameStr(rl->issuer);
    if(serverName==NULL){
        if(strcmp("Root",rl->issuer)==0)
            rlBundle->certChain[0]=NULL;
        else
            /* bad issuer string */
            return SARL_ERR;
    } else{
        if(saCertCreateChain(certFile,serverName,rlBundle->certChain)<0)
            /* couldn't construct cert chain */
            return SARL_ERR;
    }
    
    return BB_SYSAPP_PASS;
}

int saRlBundle(u8 *rlFile,u8 *certFile,BbAppLaunchCrls *rls)
{
    int i;
    int numFileRls = *(u32 *)rlFile;
    int numAppRls = LAUNCH_CRLS;
    BbCrlHead *rl = (BbCrlHead *)(rlFile+sizeof(u32));

    memset((void *)rls,0,sizeof(BbAppLaunchCrls));

    for(i=0;i<numFileRls;i++){

        switch(rl->type){
        case BB_CRL_TYPE_XS:
            if(fillCrlBundle(rl,certFile,&rls->tsrl) != BB_SYSAPP_PASS)
               return SARL_ERR;
            break;
        case BB_CRL_TYPE_CP:
            if(fillCrlBundle(rl,certFile,&rls->cprl) != BB_SYSAPP_PASS)
               return SARL_ERR;
            break;
        case BB_CRL_TYPE_CA:
            if(fillCrlBundle(rl,certFile,&rls->carl) != BB_SYSAPP_PASS)
               return SARL_ERR;
            break;
        default:
            return SARL_ERR;
        }
        numAppRls--;
        if(numAppRls==0)
            break;
        rl = (BbCrlHead *)(((u8 *)rl) + sizeof(BbCrlHead) + 
                           sizeof(BbCrlEntry)*rl->numberRevoked);
    }

    return BB_SYSAPP_PASS;
}
