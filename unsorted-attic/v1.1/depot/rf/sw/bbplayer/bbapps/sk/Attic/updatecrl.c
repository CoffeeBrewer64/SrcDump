d58 1
a58 1
        dataChain[1].size = sizeofcrl;
d147 1
a147 1
            if(strcmp((crls->cprl->head).issuer, crls->cprl->certChain->issuer)!= 0){
d165 1
a165 1
            result = TESTverifyRsaSig(dataChain, ((BbRsaCert *)crls->cprl->certChain)->publicKey, ((BbRsaCert *) crls->cprl->certChain)->exponent, BB_SIG_TYPE_RSA4096, (crls->cprl->head).signature);
d217 1
a217 1
            if(strcmp((crls->tsrl->head).issuer, crls->tsrl->certChain->issuer)!= 0){
d235 1
a235 1
            result = TESTverifyRsaSig(dataChain, ((BbRsaCert *)crls->tsrl->certChain)->publicKey, ((BbRsaCert *) crls->tsrl->certChain)->exponent, BB_SIG_TYPE_RSA4096, (crls->tsrl->head).signature);
d284 1
a284 1
            if(strcmp((crls->crl->head).issuer, crls->crl->certChain->issuer)!= 0){
d292 1
a292 1
            nextcert = crls->crl->certChain + sizeof(BbRsaCert);
d311 1
a311 1
            result = TESTverifyRsaSig(dataChain, ((BbRsaCert *)crls->crl->certChain)->publicKey, ((BbRsaCert *) crls->crl->certChain)->exponent, BB_SIG_TYPE_RSA4096, (crls->crl->head).signature);
