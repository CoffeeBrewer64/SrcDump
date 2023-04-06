#include <stdlib.h>
#include <stdio.h>
#include "test_utils.h"


int getFileSize(char *filename)
{
    FILE *fdata;
    int j;

    if ((fdata=fopen(filename,"r"))==0) {
        printf("cannot open %s\n",filename);
        exit(1);
    }
    fseek(fdata,0,SEEK_END);
    j=ftell(fdata);
    fclose(fdata);
    return j;
}

int getFileSizeAscii(char *filename)
{
    int bytes,j;
    FILE *fdata;

    if ((fdata=fopen(filename,"r"))==0) {
        printf("cannot open %s\n",filename);
        exit(1);
    }
    for(bytes=0;fscanf(fdata,"%x",&j)!=EOF;bytes++){}
    fclose(fdata);
    return bytes;
}

void readAsciiBinaryData(char *filename,u8 *data,int bytes)
{
    int i,j;
    FILE *fdata;

    if ((fdata=fopen(filename,"r"))==0) {
        printf("cannot open %s\n",filename);
        exit(1);
    }
    for(i=0; i<bytes; ++i){
        fscanf(fdata,"%x",&j);
        data[i]=(unsigned char)j;
    }
    fclose(fdata);
}

void writeAsciiBinaryData(char *filename,u8 *data,int bytes)
{
    int i,j;
    FILE *fdata;

    if ((fdata=fopen(filename,"w"))==0) {
        printf("cannot open %s\n",filename);
        exit(0);
    }
    for(i=0; i<bytes/16; ++i) {
        for(j=0; j<16; ++j)
            fprintf(fdata,"%02x ",data[i*16+j]);
        fprintf(fdata,"\n");
    }

    fclose(fdata);
}
