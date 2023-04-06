#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <netinet/in.h>

#include <sha1.h>

#include <PR/bcp.h>
#include <PR/bbvirage.h>
#include <PR/bbnand.h>
#include "../../lib/bbboot/boot.h"
#include <algorithms.h>

#define H2BE4(a) (htonl((a)))
#define BE2H4(a) (ntohl((a)))

#define MIPS_JR_T0 0x01000008
#define MIPS_NOP   0x00000000

#ifndef u32
#define u32 unsigned int
#endif

#define OPTARG      "k:hne"
#define MAXERRS 128

#define VERBOSE(x)


/* note: priv and pub are layed out big endian on input */
extern curve named_curve;
extern point named_point;
int genEccPubKey(BbEccPrivateKey priv,BbEccPublicKey pub)
{
    field_2n privField;
    point pubPoint;
    static int init=0;
    int i;

    if(init==0){
        Init_233_bit();
        init=1;
    }

    /* convert priv to privField */
    for(i = 0; i< MAX_LONG; i++){
        privField.e[i] = BE2H4(priv[i]);
    }
    privField.e[0] &= UPR_MASK;

    if( BSL_OK != generate_public_key(&named_point, &named_curve, 
                                      &privField, &pubPoint)){
        return -1;
    }

    /* convert pubPoint to pub */
    for(i=0;i<8;i++){
        pub[i] = H2BE4(pubPoint.x.e[i]);
        pub[i+8] = H2BE4(pubPoint.y.e[i]);
    }

    return 0;
}


int asciiToBin(char *str,int bytes,u8 *buf)
{
    int i,j;
    char t;

    for(i=0;i<bytes;i++){
        t = str[2*i];
        if ((t >= '0') && (t <= '9')) 
            j = (t - '0') << 4;
        else if ((t >= 'a') && (t <= 'f')) 
            j = (t - 'a' + 10) << 4;
        else if ((t >= 'A') && (t <= 'F')) 
            j = (t - 'A' + 10) << 4;
        else return -1;
        
        t = str[2*i+1];
        if ((t >= '0') && (t <= '9')) 
            j ^= (t - '0');
        else if ((t >= 'a') && (t <= 'f')) 
            j ^= (t - 'a' + 10);
        else if ((t >= 'A') && (t <= 'F')) 
            j ^= (t - 'A' + 10);
        else return -1;

        buf[i]=j;
    }
    
    return 0;
}


void usage()
{
    printf("Usage:\n");
    printf("  writeV2 [opts] <skBinaryIN> <ascii-hexPlayerPrivKey> " 
           "<v2ConstOUT>\n");
    printf("where opts are:\n");
    printf("   -k <16 bytes of ascii-represented hex> \n");
    printf("   -n patch boot code to skip SHA compare\n");
    printf("   -e put enable code bb2002fb\n");
    printf("   -h This message.\n");
} 


int main(int argc,char *argv[])
{
    int i;
    u32 fbytes,aesbytes,virage2Bytes,virage2Sum,*viragePatch;
    u8 *indata=NULL;
    /*
    FILE *fpOut=NULL;
    */
    FILE *fpIn=NULL;
    FILE *v2ConstantsPtr;
    SHA1Context sha;
    BbVirage2 virage2;
    u8 *messageDigest;
        
    /* for getopt usage */
    extern int optind;
    extern char *optarg;
    int c, noSHA = 0;
    int enable = 0;

    messageDigest = (u8 *)(virage2.skHash);

    virage2Bytes = sizeof(virage2);
    virage2Sum = 0;
    memset(&virage2,0,virage2Bytes);

    /* default bootAppKey, changed by -k arg */
    virage2.bootAppKey[0] = H2BE4(0x84983e36);
    virage2.bootAppKey[1] = H2BE4(0x4706816a);
    virage2.bootAppKey[2] = H2BE4(0xba3e2571);
    virage2.bootAppKey[3] = H2BE4(0x7850c26c);

    optind = 1;
    while ((c = getopt(argc, argv, OPTARG)) != EOF) {
        switch (c) {
	case 'k':
	    if (argc <= 2) goto usage;
            asciiToBin(optarg,sizeof(BbAesKey),(u8 *)(virage2.bootAppKey));
	    //argc--; argv++;
	    break;
        case 'n':
            noSHA = 1;
            break;
        case 'e':
            enable = 1;
            break;
        case 'h':  /* Help */
        default:
        usage:
            usage();
            return 1;
        }
    }  /* while */

    if( (argc-optind)!=3){
        printf("incorrect number of args!\n\n");
        usage();
        return 1;
    }

    for(i=0;i<sizeof(BbAesKey)/4;i++){
       virage2Sum += H2BE4(virage2.bootAppKey[i]);
       VERBOSE(printf("adding = %08x\n", H2BE4(virage2.bootAppKey[i])));
    }

    asciiToBin(argv[optind+1],sizeof(BbEccPrivateKey),
               (u8 *)(virage2.privateKey));
    for(i=0;i<sizeof(BbEccPrivateKey)/4;i++){
       virage2Sum += H2BE4(virage2.privateKey[i]);
       VERBOSE(printf("adding = %08x\n", H2BE4(virage2.privateKey[i])));
    }

    v2ConstantsPtr = fopen(argv[optind+2], "w");
    if(v2ConstantsPtr == NULL){
        fprintf(stderr, " couldnt create v2 constants file\n");
        exit(1);
    }

    /* generate bb public key */
    genEccPubKey(virage2.privateKey,virage2.publicKey);
    for(i=0;i<sizeof(BbEccPublicKey)/4;i++){
       virage2Sum += H2BE4(virage2.publicKey[i]);
       VERBOSE(printf("adding = %08x\n", H2BE4(virage2.publicKey[i])));
    }

    if(noSHA){
        for(i=0;i<20;i++)
           messageDigest[i]=0;
    }
    else{
        if( (fpIn = fopen(argv[optind],"r"))==NULL ){
            printf("Error: failed to open input file %s\n",argv[optind]);
            return 1;
        }

        aesbytes = LOAD_SK_PAGES*PI_FLASH_PAGE_DATA_SIZE;
        if( (indata = (u8 *)malloc(aesbytes))==NULL ){
            printf("Error: failed to allocate %d bytes.\n",aesbytes);
            return 1;
        }
        fbytes = fread(indata,1,aesbytes,fpIn);
        fclose(fpIn);

        if(fbytes != aesbytes){
            free(indata);
            printf("SK size wrong (according to LOAD_SK_PAGES define):\n");
            printf("  expected %08x bytes, read %08x bytes.\n",aesbytes,fbytes);
            return 1;
        }

        /* hash input extended to 16B multiple, prepended by length */
        SHA1Reset(&sha);
        SHA1Input(&sha,indata,aesbytes);
        SHA1Result(&sha,messageDigest);
    }

    /* 
     * write virage2 file with hash value, bootcode patches,
     * and checksum.
     */

    /* hash value */
    for(i=0;i<20;i+=4){
       virage2Sum += H2BE4(*(u32 *)(messageDigest + i));
       VERBOSE(printf("adding = %08x\n", H2BE4(*(u32 *)(messageDigest + i))));
    }

    /* patch codes */
#define PATCH_INSTRUCTION(I) \
        *(viragePatch++) = H2BE4((I)); \
        virage2Sum += (I); \
        VERBOSE(printf("adding = %08x\n",(I)))

#define MIPS_B          0x10000000
#define MIPS_LUI_A3     0x3c070000
#define MIPS_LUI_T1     0x3c090000
#define MIPS_ORI_T1     0x35290000
#define MIPS_SW_T1_A3   0xace90000
    viragePatch = (u32 *)(virage2.romPatch);
    if (noSHA) {
        /* Jump over patch 2 */
        PATCH_INSTRUCTION(MIPS_B|0x3);
        PATCH_INSTRUCTION(MIPS_NOP);
        /*  Patch 2 goes here
            PATCH_INSTRUCTION(MIPS_JR_TO);
            PATCH_INSTRUCTION(MIPS_JR_NOP);
         */
        viragePatch += 2;
	/* patch a j 0xfc40854 @ 0xbfc40770 */
        PATCH_INSTRUCTION(MIPS_LUI_T1|0x0bf1);
        PATCH_INSTRUCTION(MIPS_ORI_T1|0x0215);
        PATCH_INSTRUCTION(MIPS_LUI_A3|0xbfc4);
        PATCH_INSTRUCTION(MIPS_SW_T1_A3|0x0770);
        PATCH_INSTRUCTION(MIPS_JR_T0);
        PATCH_INSTRUCTION(MIPS_NOP);
        viragePatch = (u32 *)(virage2.romPatch) + 2;
    } else {
        PATCH_INSTRUCTION(MIPS_JR_T0);
        PATCH_INSTRUCTION(MIPS_NOP);
    }
    PATCH_INSTRUCTION(MIPS_JR_T0);
    PATCH_INSTRUCTION(MIPS_NOP);
    VERBOSE(printf("sum = %08x\n", virage2Sum));

    /* checksum value */
    virage2.csumAdjust = H2BE4(VIRAGE2_CHECKSUM-((int)virage2Sum));
/*
    if( (fpOut = fopen(argv[optind+2],"w"))==NULL ){
        printf("Error: failed to open output file %s\n",argv[optind+2]);
        if(indata)
            goto exit_cleanup;
        return 1;
    }
    fbytes = fwrite((u8 *)(&virage2),1,virage2Bytes,fpOut);
    fclose(fpOut);
*/
    /* 
     *write constants to virage constants file 
     */

    if(enable == 0){
        virage2.jtagEnable = htonl(0x01234567);
    }
    else{
        virage2.jtagEnable = htonl(0xbb2002fb);
    }

    fwrite(virage2.skHash, 4, 5, v2ConstantsPtr);
    fwrite(virage2.romPatch, 4, 16, v2ConstantsPtr);
    fwrite(virage2.bootAppKey, 4, 4, v2ConstantsPtr);
    fwrite(&(virage2.jtagEnable), 4, 1, v2ConstantsPtr);
    

/*exit_cleanup:*/
    if(indata)
        free(indata);

    return 0;
}
