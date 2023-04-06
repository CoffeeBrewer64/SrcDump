d100 2
a101 2
    printf("  writeV2 [opts] <skBinaryIN> <ascii-hexPlayerPrivKey> \n" 
           "    \n");
a128 5
    v2ConstantsPtr = fopen("virage2.in", "w");
    if(v2ConstantsPtr == NULL){
        fprintf(stderr, " couldnt create v2 constants file\n");
        exit(1);
    }
d164 1
a164 1
    if( (argc-optind)!=2){
d182 6
d272 2
a273 1
    printf("sum = %08x\n", virage2Sum);
