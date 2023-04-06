a12 1
    PRINTF("Number certs: %d\n",gsNumCerts);
d51 1
a51 4
        i++){

        PRINTF("not %s\n",gsCertList[i]->name.server);
    }
a55 1
    PRINTF("Found cert at index %d\n",i);
a74 1
    PRINTF("Chain needs %d cert pointers.\n",indx);
