d26 2
d169 1
a169 1
       printf("adding = %08x\n", H2BE4(virage2.bootAppKey[i]));
d176 1
a176 1
       printf("adding = %08x\n", H2BE4(virage2.privateKey[i]));
d183 1
a183 1
       printf("adding = %08x\n", H2BE4(virage2.publicKey[i]));
d219 1
a219 1
       printf("adding = %08x\n", H2BE4(*(u32 *)(messageDigest + i)));
d228 1
a228 1
    printf("adding = %08x\n",MIPS_JR_T0);
d230 1
a230 1
    printf("adding = %08x\n",MIPS_NOP);
d235 2
a236 2
    printf("adding = %08x\n", MIPS_JR_T0);
    printf("adding = %08x\n", MIPS_NOP);
