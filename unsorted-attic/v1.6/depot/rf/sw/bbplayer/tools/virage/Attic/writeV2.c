d23 1
a23 1
#define OPTARG      "k:h"
d104 1
d126 1
a126 1
    int c;
d154 3
d227 10
d238 22
a259 13
    *(viragePatch++) = H2BE4(MIPS_JR_T0);
    
    *(viragePatch++) = H2BE4(MIPS_NOP);
    virage2Sum += MIPS_JR_T0;
    VERBOSE(printf("adding = %08x\n",MIPS_JR_T0));
    virage2Sum += MIPS_NOP;
    VERBOSE(printf("adding = %08x\n",MIPS_NOP));
    *(viragePatch++) = H2BE4(MIPS_JR_T0);
    *(viragePatch++) = H2BE4(MIPS_NOP);
    virage2Sum += MIPS_JR_T0;
    virage2Sum += MIPS_NOP;
    VERBOSE(printf("adding = %08x\n", MIPS_JR_T0));
    VERBOSE(printf("adding = %08x\n", MIPS_NOP));
