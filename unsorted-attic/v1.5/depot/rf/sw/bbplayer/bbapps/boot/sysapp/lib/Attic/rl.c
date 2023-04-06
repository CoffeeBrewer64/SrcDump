d50 1
a50 1
            if(fillCrlBundle(rl,certFile,rls->tsrl) != BB_SYSAPP_PASS)
d54 1
a54 1
            if(fillCrlBundle(rl,certFile,rls->cprl) != BB_SYSAPP_PASS)
d58 1
a58 1
            if(fillCrlBundle(rl,certFile,rls->crl) != BB_SYSAPP_PASS)
d62 1
a62 1
            if(fillCrlBundle(rl,certFile,rls->carl) != BB_SYSAPP_PASS)
