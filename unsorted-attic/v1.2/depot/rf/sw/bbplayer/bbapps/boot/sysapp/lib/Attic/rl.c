a14 1
#if 0
d20 1
a20 1
    rlBundle->list = (BbCrlEntry *)(((u8 *)rl) + sizeof(BbCrlHead));
d50 1
a50 1
            if(fillCrlBundle(rl,certFile,&rls->tsrl) != BB_SYSAPP_PASS)
d54 1
a54 1
            if(fillCrlBundle(rl,certFile,&rls->cprl) != BB_SYSAPP_PASS)
d58 1
a58 1
            if(fillCrlBundle(rl,certFile,&rls->crl) != BB_SYSAPP_PASS)
d62 1
a62 1
            if(fillCrlBundle(rl,certFile,&rls->carl) != BB_SYSAPP_PASS)
a76 1
#endif
