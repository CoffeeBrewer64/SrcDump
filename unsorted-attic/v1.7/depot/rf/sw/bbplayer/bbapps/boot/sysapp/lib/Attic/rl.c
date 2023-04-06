a56 4
        case BB_CRL_TYPE_CT:
            if(fillCrlBundle(rl,certFile,&rls->crl) != BB_SYSAPP_PASS)
               return SARL_ERR;
            break;
