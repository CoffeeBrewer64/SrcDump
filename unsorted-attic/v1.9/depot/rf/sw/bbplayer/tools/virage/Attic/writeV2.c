d194 3
a196 3
    if( (fpIn = fopen(argv[optind],"r"))==NULL ){
        printf("Error: failed to open input file %s\n",argv[optind]);
        return 1;
d198 5
d204 14
a217 7
    aesbytes = LOAD_SK_PAGES*PI_FLASH_PAGE_DATA_SIZE;
    if( (indata = (u8 *)malloc(aesbytes))==NULL ){
        printf("Error: failed to allocate %d bytes.\n",aesbytes);
        return 1;
    }
    fbytes = fread(indata,1,aesbytes,fpIn);
    fclose(fpIn);
d219 4
a222 5
    if(fbytes != aesbytes){
        free(indata);
        printf("SK size wrong (according to LOAD_SK_PAGES define):\n");
        printf("  expected %08x bytes, read %08x bytes.\n",aesbytes,fbytes);
        return 1;
a223 5

    /* compute hash on input extended to 16B multiple, prepended by length */
    SHA1Reset(&sha);
    SHA1Input(&sha,indata,aesbytes);
    SHA1Result(&sha,messageDigest);
