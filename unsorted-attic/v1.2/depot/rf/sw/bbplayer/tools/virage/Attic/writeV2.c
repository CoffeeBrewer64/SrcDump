d11 1
d14 1
d27 37
d98 2
a99 1
    printf("  writeV2 [opts] <skBinaryIN> <v2BinaryOUT> \n");
d102 1
a102 2
    printf("   -h \n");
    printf("      This message.\n");
a112 1
    char *skfile,*vFlashFilename;
d139 1
a139 1
	    argc--; argv++;
d149 6
d159 4
a162 3
    if((skfile=argv[argc-2]) == NULL){
        printf("Error: SK input filename required.\n");
        return 1;
d164 5
a168 3
    if((vFlashFilename=argv[argc-1]) == NULL){
        printf("Error: virage2 output filename required.\n");
        return 1;
d171 2
a172 2
    if( (fpIn = fopen(skfile,"r"))==NULL ){
        printf("Error: failed to open input file %s\n",skfile);
d221 2
a222 2
    if( (fpOut = fopen(vFlashFilename,"w"))==NULL ){
        printf("Error: failed to open output file %s\n",vFlashFilename);
