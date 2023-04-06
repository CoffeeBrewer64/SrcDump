d50 1
a50 1
        if (strcmp((carl->head).issuer, BB_CERT_STR_ROOT) != 0) {
d55 1
a55 1
        sizeofcrl = sizeofcrl + ((carl->head).numberRevoked) * sizeof(u32);
d59 1
a59 1
        result = TESTverifyRsaSig(dataChain, (u32 *)gRootKey, gRootExp, BB_SIG_TYPE_RSA4096, &((carl->head).signature));
d68 2
a69 2
            if(((carl->head).revocationType == CPCA_REV) ||
               ((carl->head).revocationType == CPLSCA_REV)){
d73 2
a74 2
            else if(((carl->head).revocationType == LSCA_REV) ||
                    ((carl->head).revocationType == CPLSCA_REV)){
d137 2
a138 2
        for (i =0; i< ((crls->carl)->head).numberRevoked; i++){
            result = isMatch((crls->cprl->head).issuer, (crls->carl)->list[i], "Root-CPCA");
d147 1
a147 1
            if(strcmp((crls->cprl->head).issuer, crls->cprl->certChain[1]->issuer)!= 0){
d161 1
a161 1
            sizeofcrl = sizeofcrl + ((crls->cprl->head).numberRevoked) * sizeof(BbServerName);
d165 1
a165 1
            result = TESTverifyRsaSig(dataChain, ((BbRsaCert *)crls->cprl->certChain[0])->publicKey, ((BbRsaCert *) crls->cprl->certChain[0])->exponent, BB_SIG_TYPE_RSA4096, (crls->cprl->head).signature);
d207 2
a208 2
        for (i =0; i< ((crls->carl)->head).numberRevoked; i++){
            result = isMatch((crls->tsrl->head).issuer, (crls->carl)->list[i], "Root-TSCA");
d217 1
a217 1
            if(strcmp((crls->tsrl->head).issuer, crls->tsrl->certChain[0]->issuer)!= 0){
d231 1
a231 1
            sizeofcrl = sizeofcrl + ((crls->tsrl->head).numberRevoked) * sizeof(BbServerName);
d235 1
a235 1
            result = TESTverifyRsaSig(dataChain, ((BbRsaCert *)crls->tsrl->certChain[0])->publicKey, ((BbRsaCert *) crls->tsrl->certChain[0])->exponent, BB_SIG_TYPE_RSA4096, (crls->tsrl->head).signature);
d274 2
a275 2
        for (i =0; i< ((crls->cprl)->head).numberRevoked; i++){
            result = isMatch((crls->crl->head).issuer, (crls->cprl)->list[i], "Root-CPCA");
d284 1
a284 1
            if(strcmp((crls->crl->head).issuer, crls->crl->certChain[0]->issuer)!= 0){
d293 1
a293 1
            for(i =0; i < ((crls->carl)->head).numberRevoked; i++){
d307 1
a307 1
            sizeofcrl = sizeofcrl + ((crls->crl->head).numberRevoked) * sizeof(BbServerName);
d311 1
a311 1
            result = TESTverifyRsaSig(dataChain, ((BbRsaCert *)crls->crl->certChain[0])->publicKey, ((BbRsaCert *) crls->crl->certChain[0])->exponent, BB_SIG_TYPE_RSA4096, (crls->crl->head).signature);
