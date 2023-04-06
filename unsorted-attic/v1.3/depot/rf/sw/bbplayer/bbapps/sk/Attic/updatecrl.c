d59 1
a59 1
        result = TESTverifyRsaSig(dataChain, (u32 *)gRootKey, gRootExp, BB_SIG_TYPE_RSA4096, &(carl->head->signature));
d165 1
a165 1
            result = TESTverifyRsaSig(dataChain, ((BbRsaCert *)crls->cprl->certChain[0])->publicKey, ((BbRsaCert *) crls->cprl->certChain[0])->exponent, BB_SIG_TYPE_RSA4096, crls->cprl->head->signature);
d235 1
a235 1
            result = TESTverifyRsaSig(dataChain, ((BbRsaCert *)crls->tsrl->certChain[0])->publicKey, ((BbRsaCert *) crls->tsrl->certChain[0])->exponent, BB_SIG_TYPE_RSA4096, crls->tsrl->head->signature);
d311 1
a311 1
            result = TESTverifyRsaSig(dataChain, ((BbRsaCert *)crls->crl->certChain[0])->publicKey, ((BbRsaCert *) crls->crl->certChain[0])->exponent, BB_SIG_TYPE_RSA4096, crls->crl->head->signature);
