#include <stdlib.h>
#include <stdio.h>

#include "aes.h"
#include "test_utils.h"


main(int argc,char *argv[])
{
    u8 key[16],iv[16],*inData,*outData;
    int fsize,och,firstFileIndx=2;
    FILE *pFile;

    if(argc<5){
        printf(
            "usage: \n"
            "test_pi_encrypt -a <key_file> <vect_file> <data_in_file> <data_out_file>\n");
        printf(" + where optional -a specifies ascii i/o for data_*_file.\n");
        printf("   if no -a option, data_*_file are binary.\n");
        printf(" + <key_file> and <vect_file> are ascii, like key_ex.dat\n");
        printf("   and iv_ex.dat\n");
        return;
    }

    och=getopt(argc,argv,"a");
    if((char)och=='?'){
        printf("bad option\n");
        exit(1);
    }
    else if(och==-1){
        /* no options */
        firstFileIndx = 1;
    }

    if(och=='a'){
        fsize = getFileSizeAscii(argv[firstFileIndx+2]);
    }
    else{
        fsize = getFileSize(argv[firstFileIndx+2]);
    }
    printf("Bytes of input data: %d\n",fsize);
    if(fsize&0xf){
        printf("  input file size must be multiple of 16 bytes\n");
        return;
    }
    inData=malloc(fsize);
    outData=malloc(fsize);

    readAsciiBinaryData(argv[firstFileIndx++],key,16);
    readAsciiBinaryData(argv[firstFileIndx++],iv,16);
    
    if((char)och=='a'){
        readAsciiBinaryData(argv[firstFileIndx++],inData,fsize);
    }
    else{
        pFile=fopen(argv[firstFileIndx++],"r");
        fread(inData,1,fsize,pFile);
        fclose(pFile);
    }

    aes_SwEncrypt(key,iv,inData,fsize,outData, AES_RAW_INPUT);

    if((char)och=='a'){
        writeAsciiBinaryData(argv[firstFileIndx++],outData,fsize);
    }
    else{
        pFile=fopen(argv[firstFileIndx++],"w");
        fwrite(outData,1,fsize,pFile);
        fclose(pFile);
    }

    free(inData);
    free(outData);
}






