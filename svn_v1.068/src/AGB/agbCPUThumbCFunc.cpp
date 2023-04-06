/**

* @file agbCPUThumbCFuncMacro.cpp

* @author zhfang

* @date 2009.12.16

* @brief AGB Emulate For CTR - Macro to create fucntion for Thumb instruction

*/
 #include "agbCPUThumbCFunc.h"
void agbCpuThumbCFunc_0x00_0x07()
{
 // LSL Rd, Rm, #Imm5
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7; g_nAgbCPUImm5 = (g_nAgbInst>>6)&0x1f;
  if(g_nAgbCPUImm5 == 0)
  {
   g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURm];
  }
  else
  {
   g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[g_nAgbCPURm]>>(32-g_nAgbCPUImm5))&0x1; g_nAgbCPUReg[g_nAgbCPURd] = (g_nAgbCPUReg[g_nAgbCPURm]<<g_nAgbCPUImm5);
  }
  g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
}


void agbCpuThumbCFunc_0x08_0x0f()
{
 // LSR Rd, Rm, #Imm5
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7; g_nAgbCPUImm5 = (g_nAgbInst>>6)&0x1f;
  if(g_nAgbCPUImm5 == 0)
  {
   g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1;
   g_nAgbCPUReg[g_nAgbCPURd] = 0;
  }
  else
  {
   g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[g_nAgbCPURm]>>(g_nAgbCPUImm5-1))&0x1; g_nAgbCPUReg[g_nAgbCPURd] = (g_nAgbCPUReg[g_nAgbCPURm]>>g_nAgbCPUImm5);
  }
  g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
}


void agbCpuThumbCFunc_0x10_0x17()
{
 // ASR Rd, Rm, #Imm5
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7; g_nAgbCPUImm5 = (g_nAgbInst>>6)&0x1f;
  if(g_nAgbCPUImm5 == 0)
  {
   g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1;
   g_nAgbCPUReg[g_nAgbCPURd] = 0;
  }
  else
  {
   g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[g_nAgbCPURm] >>(g_nAgbCPUImm5-1))&0x1; g_nAgbCPUReg[g_nAgbCPURd] = ((s32)g_nAgbCPUReg[g_nAgbCPURm])>>g_nAgbCPUImm5;
  }
  g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
}

void agbCpuThumbCFunc_0x18_0x19()
{
 // ADD Rd, Rn, Rm
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPURm = (g_nAgbInst>>6)&0x7;
  g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm];
 g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
  g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm]) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURm]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;;
 g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURn])) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;;
 g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[REG_CPUVALUE];
}

void agbCpuThumbCFunc_0x1a_0x1b()
{
 // SUB Rd, Rs, Rn
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPURm = (g_nAgbInst>>6)&0x7;
  g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURn] - g_nAgbCPUReg[g_nAgbCPURm];
 g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
  g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;;
 g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURn])) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm]) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;;
 g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[REG_CPUVALUE];
}

void agbCpuThumbCFunc_0x1c_0x1d()
{
 // ADD Rd, Rn, #g_nAgbCPUImm3
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPUImm3 = (g_nAgbInst>>6)&0x7;
  g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUImm3;
 g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
  g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((g_nAgbCPUImm3) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((g_nAgbCPUImm3) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;;
 g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((g_nAgbCPUImm3) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURn])) >> 31) & ((~(g_nAgbCPUImm3)) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;;
 g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[REG_CPUVALUE];
}

void agbCpuThumbCFunc_0x1e_0x1f()
{
 // SUB Rd, Rn, #g_nAgbCPUImm3
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPUImm3 = (g_nAgbInst>>6)&0x7;
  g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURn] - g_nAgbCPUImm3;
 g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
  g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUImm3)) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUImm3)) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;;
 g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUImm3)) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURn])) >> 31) & ((g_nAgbCPUImm3) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;;
 g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[REG_CPUVALUE];
}

void agbCpuThumbCFunc_0x20_0x27()
{
 //MOV Rd, #g_nAgbCPUImm8
 g_nAgbCPUImm8 = (g_nAgbInst &0xff); g_nAgbCPURd = (g_nAgbInst>>8)&7;
  g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUImm8;
 g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
}

void agbCpuThumbCFunc_0x28_0x2f()
{
 // CMP Rd, #g_nAgbCPUImm8
 g_nAgbCPUImm8 = (g_nAgbInst &0xff); g_nAgbCPURd = (g_nAgbInst>>8)&7;
  g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURd] - g_nAgbCPUImm8;
 g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
  g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((~(g_nAgbCPUImm8)) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUImm8)) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;;
 g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((~(g_nAgbCPUImm8)) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURd])) >> 31) & ((g_nAgbCPUImm8) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;;
}

void agbCpuThumbCFunc_0x30_0x37()
{
 // ADD Rd, #g_nAgbCPUImm8
 g_nAgbCPUImm8 = (g_nAgbInst &0xff); g_nAgbCPURd = (g_nAgbInst>>8)&7;
  g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURd] + g_nAgbCPUImm8;
 g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
  g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((g_nAgbCPUImm8) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((g_nAgbCPUImm8) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;;
 g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((g_nAgbCPUImm8) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURd])) >> 31) & ((~(g_nAgbCPUImm8)) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;;
 g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[REG_CPUVALUE];
}

void agbCpuThumbCFunc_0x38_0x3f()
{
 // SUB Rd, #g_nAgbCPUImm8
 g_nAgbCPUImm8 = (g_nAgbInst &0xff); g_nAgbCPURd = (g_nAgbInst>>8)&7;
  g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURd] - g_nAgbCPUImm8;
 g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
  g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((~(g_nAgbCPUImm8)) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUImm8)) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;;
 g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((~(g_nAgbCPUImm8)) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURd])) >> 31) & ((g_nAgbCPUImm8) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;;
 g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[REG_CPUVALUE];
}

void agbCpuThumbCFunc_0x40()
{
 switch( (g_nAgbInst>>6)&3)
 {
 case 0x00:
  {
   // AND Rd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURd] & g_nAgbCPUReg[g_nAgbCPURm];
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
  }
  break;
 case 0x01:
  {
   // EOR Rd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURd]^g_nAgbCPUReg[g_nAgbCPURm];
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
  }
  break;
 case 0x02:
  {
   // LSL Rd, Rs
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURs = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURs]&0xff;
   if(g_nAgbCPUReg[REG_CPUVALUE] == 0)
   {}
   else if(g_nAgbCPUReg[REG_CPUVALUE] > 0 && g_nAgbCPUReg[REG_CPUVALUE]<32)
   {
    g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>(32-g_nAgbCPUReg[g_nAgbCPURs]))&0x1; g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURd]<<g_nAgbCPUReg[g_nAgbCPURs];
   }
   else if(g_nAgbCPUReg[REG_CPUVALUE] == 32)
   {
    g_nAgbCPUReg[REG_CFLAG] = g_nAgbCPUReg[g_nAgbCPURd]&0x1;
    g_nAgbCPUReg[g_nAgbCPURd] = 0;
   }
   else
   {
    g_nAgbCPUReg[REG_CFLAG] = 0;
    g_nAgbCPUReg[g_nAgbCPURd] = 0;
   }
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
  }
  break;
 case 0x03:
  {
   // LSR Rd, Rs
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURs = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURs]&0xff;
   if(g_nAgbCPUReg[REG_CPUVALUE] == 0)
   {}
   else if(g_nAgbCPUReg[REG_CPUVALUE] > 0 && g_nAgbCPUReg[REG_CPUVALUE]<32)
   {
    g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>(g_nAgbCPUReg[g_nAgbCPURs]-1))&0x1; g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURd]>>g_nAgbCPUReg[g_nAgbCPURs];
   }
   else if(g_nAgbCPUReg[REG_CPUVALUE] == 32)
   {
    g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1;
    g_nAgbCPUReg[g_nAgbCPURd] = 0;
   }
   else
   {
    g_nAgbCPUReg[REG_CFLAG] = 0;
    g_nAgbCPUReg[g_nAgbCPURd] = 0;
   }
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
  }
  break;
 }

}

void agbCpuThumbCFunc_0x41()
{
 switch((g_nAgbInst >> 6) & 3)
 {
 case 0x00:
  {
   // ASR Rd, Rs
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURs = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURs]&0xff;
   if(g_nAgbCPUReg[REG_CPUVALUE] == 0)
   {}
   else if(g_nAgbCPUReg[REG_CPUVALUE] > 0 && g_nAgbCPUReg[REG_CPUVALUE]<32)
   {
    g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>(g_nAgbCPUReg[g_nAgbCPURs]-1))&0x1; g_nAgbCPUReg[g_nAgbCPURd] = ((s32)g_nAgbCPUReg[g_nAgbCPURd])>>g_nAgbCPUReg[g_nAgbCPURs];
   }
   else if(g_nAgbCPUReg[REG_CPUVALUE] == 32)
   {
    g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1;
    if(g_nAgbCPUReg[REG_CFLAG])
     g_nAgbCPUReg[g_nAgbCPURd] = 0xffffffff;
    else
     g_nAgbCPUReg[g_nAgbCPURd] = 0;
   }
   else
   {
    g_nAgbCPUReg[REG_CFLAG] = 0;
    g_nAgbCPUReg[g_nAgbCPURd] = 0;
   }
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
  }
  break;
 case 0x01:
  {
   // ADC Rd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURd] + g_nAgbCPUReg[g_nAgbCPURm] + g_nAgbCPUReg[REG_CFLAG];
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
    g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm]) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURm]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;
    g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURd])) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;
  }
  break;
 case 0x02:
  {
   // SBC Rd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURd] - g_nAgbCPUReg[g_nAgbCPURm] - (!g_nAgbCPUReg[REG_CFLAG]);
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
    g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;;
   g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURd]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURd])) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm]) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;;
  }
  break;
 case 0x03:
  {
   // ROR Rd, Rs
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURs = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURs]&0xff;
   if(g_nAgbCPUReg[REG_CPUVALUE] == 0)
   {}
   else if((g_nAgbCPUReg[REG_CPUVALUE]&0xf) == 0)
   {
    g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1;
   }
   else
   {
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[REG_CPUVALUE]&0xf;
    g_nAgbCPUReg[REG_CFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>(g_nAgbCPUReg[REG_CPUVALUE]-1))&0x1; g_nAgbCPUReg[g_nAgbCPURd] = ((g_nAgbCPUReg[g_nAgbCPURd]<<(32-g_nAgbCPUReg[REG_CPUVALUE])) | (g_nAgbCPUReg[g_nAgbCPURd]>>g_nAgbCPUReg[REG_CPUVALUE]));
   }
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
  }
  break;
 }

}

void agbCpuThumbCFunc_0x42()
{
 switch((g_nAgbInst >> 6) & 3)
 {
 case 0x00:
  {
   // TST Rd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = (g_nAgbCPUReg[g_nAgbCPURd] & g_nAgbCPUReg[g_nAgbCPURm]);
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
  }
  break;
 case 0x01:
  {
   // NEG Rd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = (u32)0 - g_nAgbCPUReg[g_nAgbCPURm];
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
    g_nAgbCPUReg[REG_CFLAG] = (((((u32)0) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31)) | ((((u32)0) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;
    g_nAgbCPUReg[REG_VFLAG] = (((((u32)0) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~((u32)0)) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm]) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;
    g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[REG_CPUVALUE];
  }
  break;
 case 0x02:
  {
   //CMP Rn, Rm
   g_nAgbCPURn = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURn] - g_nAgbCPUReg[g_nAgbCPURm];
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
    g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;
    g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURn])) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm]) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;
  }
  break;
 case 0x03:
  {
   //CMN Rn, Rm
   g_nAgbCPURn = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm];
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
    g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm]) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURm]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;
    g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURn])) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;
  }
  break;
 }
}

void agbCpuThumbCFunc_0x43()
{
 switch((g_nAgbInst >> 6) & 3)
 {
 case 0x00:
  {
   // ORR Rd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURd] | g_nAgbCPUReg[g_nAgbCPURm];
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
  }
  break;
 case 0x01:
  {
   // MUL Rd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd] = (g_nAgbCPUReg[g_nAgbCPURm] * g_nAgbCPUReg[g_nAgbCPURd]);
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
  }
  break;
 case 0x02:
  {
   //Bic Rd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURd] & (~g_nAgbCPUReg[g_nAgbCPURm]);
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
  }
  break;
 case 0x03:
  {
   //MVN Rd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd] = (~g_nAgbCPUReg[g_nAgbCPURm]);
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[g_nAgbCPURd]>>31)&0x1; g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[g_nAgbCPURd] == 0);
  }
  break;
 }
}

void agbCpuThumbCFunc_0x44()
{
 switch((g_nAgbInst >> 6) & 3)
 {
 case 0x00:
  {
   //zhfang test
   //unknown thumb
   TRL_ERROR("unknown thumb instruction");
  }
  break;
 case 0x01:
  {
   // ADD Rd, Hm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd] = (g_nAgbCPUReg[g_nAgbCPURd] + g_nAgbCPUReg[g_nAgbCPURm+8]);
  }
  break;
 case 0x02:
  {
   // ADD Hd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd +8] = (g_nAgbCPUReg[g_nAgbCPURd + 8] + g_nAgbCPUReg[g_nAgbCPURm]);
   if(g_nAgbCPURd == 7){ g_nAgbCPUReg[15] &= 0xfffffffe; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;}
  }
  break;
 case 0x03:
  {
   // ADD Hd, Hm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd + 8] = (g_nAgbCPUReg[g_nAgbCPURd + 8] + g_nAgbCPUReg[g_nAgbCPURm +8]);
   if(g_nAgbCPURd == 7){ g_nAgbCPUReg[15] &= 0xfffffffe; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;}
  }
  break;
 }
}

void agbCpuThumbCFunc_0x45()
{
 switch((g_nAgbInst >> 6) & 3)
 {
 case 0x00:
  {
   //CMP Rn, Rm
   g_nAgbCPURn = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURn] - g_nAgbCPUReg[g_nAgbCPURm];
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
    g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;
    g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURn])) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm]) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;
  }
  break;
 case 0x01:
  {
   //CMP Rn, Hm
   g_nAgbCPURn = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURn] - g_nAgbCPUReg[g_nAgbCPURm +8];
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
    g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm+8])) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURm+8])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;
    g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm+8])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURn])) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm+8]) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;
  }
  break;
 case 0x02:
  {
   //CMP Hn, Rm
   g_nAgbCPURn = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURn +8] - g_nAgbCPUReg[g_nAgbCPURm];
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
    g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn+8]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURn+8]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;
    g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn+8]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURn+8])) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm]) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;
  }
  break;
 case 0x03:
  {
   //CMP Hn, Hm
   g_nAgbCPURn = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[REG_CPUVALUE] = g_nAgbCPUReg[g_nAgbCPURn +8] - g_nAgbCPUReg[g_nAgbCPURm +8];
   g_nAgbCPUReg[REG_NFLAG] = (g_nAgbCPUReg[REG_CPUVALUE]>>31); g_nAgbCPUReg[REG_ZFLAG] = (g_nAgbCPUReg[REG_CPUVALUE] == 0);
    g_nAgbCPUReg[REG_CFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn+8]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm+8])) >> 31)) | (((g_nAgbCPUReg[g_nAgbCPURn+8]) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURm+8])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31))) ? true : false;
    g_nAgbCPUReg[REG_VFLAG] = ((((g_nAgbCPUReg[g_nAgbCPURn+8]) >> 31) & ((~(g_nAgbCPUReg[g_nAgbCPURm+8])) >> 31) & ((~(g_nAgbCPUReg[REG_CPUVALUE])) >> 31)) | (((~(g_nAgbCPUReg[g_nAgbCPURn+8])) >> 31) & ((g_nAgbCPUReg[g_nAgbCPURm+8]) >> 31) & ((g_nAgbCPUReg[REG_CPUVALUE]) >> 31))) ? true : false;
  }
  break;
 }
}

void agbCpuThumbCFunc_0x46()
{
 switch((g_nAgbInst >> 6) & 3)
 {
 case 0x00:
  {
   //Mov Rd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURm];
  }
  break;
 case 0x01:
  {
   //Mov Rd, Hm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd] = g_nAgbCPUReg[g_nAgbCPURm + 8];
  }
  break;
 case 0x02:
  {
   //Mov Hd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd + 8] = g_nAgbCPUReg[g_nAgbCPURm];
   if(g_nAgbCPURd == 7){ g_nAgbCPUReg[15] &= 0xfffffffe; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;}
  }
  break;
 case 0x03:
  {
   //Mov Hd, Rm
   g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[g_nAgbCPURd + 8] = g_nAgbCPUReg[g_nAgbCPURm + 8];
   if(g_nAgbCPURd == 7){ g_nAgbCPUReg[15] &= 0xfffffffe; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;}
  }
  break;
 }
}

void agbCpuThumbCFunc_0x47()
{
 switch((g_nAgbInst >> 6) & 3)
 {
 case 0x00:
  {
   //BX Rm
   g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[15] = g_nAgbCPUReg[g_nAgbCPURm]&0xfffffffe;
   if(g_nAgbCPUReg[g_nAgbCPURm]&0x1)
   {
    g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
   }
   else
   {
    g_nAgbThumbState = 0;
    g_nAgbCPUReg[15] &= 0xfffffffc;
    g_nAgbInsta = agbMemRead32(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead32(g_nAgbCPUReg[15] + 4); g_nAgbCPUReg[15] += 4;
   }
  }
  break;
 case 0x01:
  {
   //BX Hm
   g_nAgbCPURm = (g_nAgbInst>>3)&0x7;
    g_nAgbCPUReg[15] = g_nAgbCPUReg[g_nAgbCPURm + 8]&0xfffffffe;
   if(g_nAgbCPUReg[g_nAgbCPURm + 8]&0x1)
   {
    g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
   }
   else
   {
    g_nAgbThumbState = 0;
    g_nAgbCPUReg[15] &= 0xfffffffc;
    g_nAgbInsta = agbMemRead32(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead32(g_nAgbCPUReg[15] + 4); g_nAgbCPUReg[15] += 4;
   }
  }
  break;
 default:
  //zhfang test
  //unknown thumb
  TRL_ERROR("unknown thumb instruction");
  break;
 }
}

void agbCpuThumbCFunc_0x48_0x4f()
{
 // LDR Rd, [PC, #g_nAgbCPUImm8*4]
 g_nAgbCPUImm8 = (g_nAgbInst &0xff); g_nAgbCPURd = (g_nAgbInst>>8)&7;
  g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead32((g_nAgbCPUReg[15]&0xfffffffc) + (g_nAgbCPUImm8<<2));
}

void agbCpuThumbCFunc_0x50_0x51()
{
 // STR Rd, [Rn, Rm]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPURm = (g_nAgbInst>>6)&0x7;
  agbMemWrite32(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUReg[g_nAgbCPURd]);
}

void agbCpuThumbCFunc_0x52_0x53()
{
 // STRH Rd, [Rn, Rm]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPURm = (g_nAgbInst>>6)&0x7;
  agbMemWrite16(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUReg[g_nAgbCPURd]&0xffff);
}

void agbCpuThumbCFunc_0x54_0x55()
{
 // STRB Rd, [Rn, Rm]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPURm = (g_nAgbInst>>6)&0x7;
  agbMemWrite8(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm], g_nAgbCPUReg[g_nAgbCPURd]&0xff);
}

void agbCpuThumbCFunc_0x56_0x57()
{
 // LDRSB Rd, [Rn, Rm]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPURm = (g_nAgbInst>>6)&0x7;
  g_nAgbCPUReg[g_nAgbCPURd] = (s8)agbMemRead8(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm]);
}

void agbCpuThumbCFunc_0x58_0x59()
{
 // LDR Rd, [Rn, Rm]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPURm = (g_nAgbInst>>6)&0x7;
  g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead32(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm]);
}

void agbCpuThumbCFunc_0x5a_0x5b()
{
 // LDRH Rd, [Rn, Rm]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPURm = (g_nAgbInst>>6)&0x7;
  g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead16(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm]);
}

void agbCpuThumbCFunc_0x5c_0x5d()
{
 // LDRB Rd, [Rn, Rm]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPURm = (g_nAgbInst>>6)&0x7;
  g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead8(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm]);
}

void agbCpuThumbCFunc_0x5e_0x5f()
{
 // LDRSH Rd, [Rn, Rm]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPURm = (g_nAgbInst>>6)&0x7;
  g_nAgbCPUReg[g_nAgbCPURd] = (s16)agbMemRead16(g_nAgbCPUReg[g_nAgbCPURn] + g_nAgbCPUReg[g_nAgbCPURm]);
}

void agbCpuThumbCFunc_0x60_0x67()
{
 // STR Rd, [Rn, IMM5*4]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPUImm5 = (g_nAgbInst>>6)&0x1f;
  agbMemWrite32(g_nAgbCPUReg[g_nAgbCPURn] + (g_nAgbCPUImm5<<2), g_nAgbCPUReg[g_nAgbCPURd]);
}

void agbCpuThumbCFunc_0x68_0x6f()
{
 // LDR Rd, [Rn, IMM5*4]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPUImm5 = (g_nAgbInst>>6)&0x1f;
  g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead32( g_nAgbCPUReg[g_nAgbCPURn] + (g_nAgbCPUImm5<<2));
}

void agbCpuThumbCFunc_0x70_0x77()
{
 // STRB Rd, [Rn, IMM5]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPUImm5 = (g_nAgbInst>>6)&0x1f;
  agbMemWrite8(g_nAgbCPUReg[g_nAgbCPURn] + (g_nAgbCPUImm5), g_nAgbCPUReg[g_nAgbCPURd]);
}

void agbCpuThumbCFunc_0x78_0x7f()
{
 // LDRB Rd, [Rn, IMM5]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPUImm5 = (g_nAgbInst>>6)&0x1f;
  g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead8( g_nAgbCPUReg[g_nAgbCPURn] + (g_nAgbCPUImm5));
}

void agbCpuThumbCFunc_0x80_0x87()
{
 // STRH Rd, [Rn, IMM5*2]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPUImm5 = (g_nAgbInst>>6)&0x1f;
  agbMemWrite16(g_nAgbCPUReg[g_nAgbCPURn] + (g_nAgbCPUImm5<<1), g_nAgbCPUReg[g_nAgbCPURd]);
}

void agbCpuThumbCFunc_0x88_0x8f()
{
 // LDRH Rd, [Rn, IMM5*2]
 g_nAgbCPURd = (g_nAgbInst &0x7); g_nAgbCPURn = (g_nAgbInst>>3)&0x7; g_nAgbCPUImm5 = (g_nAgbInst>>6)&0x1f;
  g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead16( g_nAgbCPUReg[g_nAgbCPURn] + (g_nAgbCPUImm5<<1));
}

void agbCpuThumbCFunc_0x90_0x97()
{
 // STR Rd, [SP, IMM8*4]
 g_nAgbCPUImm8 = (g_nAgbInst &0xff); g_nAgbCPURd = (g_nAgbInst>>8)&7;
  agbMemWrite32(g_nAgbCPUReg[13] + (g_nAgbCPUImm8<<2), g_nAgbCPUReg[g_nAgbCPURd]);
}

void agbCpuThumbCFunc_0x98_0x9f()
{
 // LDR Rd, SP, IMM8*4]
 g_nAgbCPUImm8 = (g_nAgbInst &0xff); g_nAgbCPURd = (g_nAgbInst>>8)&7;
  g_nAgbCPUReg[g_nAgbCPURd] = agbMemRead32( g_nAgbCPUReg[13] + (g_nAgbCPUImm8<<2));
}

void agbCpuThumbCFunc_0xa0_0xa7()
{
 // ADD Rd, PC, IMM8
 g_nAgbCPUImm8 = (g_nAgbInst &0xff); g_nAgbCPURd = (g_nAgbInst>>8)&7;
  g_nAgbCPUReg[g_nAgbCPURd] = (g_nAgbCPUReg[15]&0xfffffffc) + (g_nAgbCPUImm8<<2);
}

void agbCpuThumbCFunc_0xa8_0xaf()
{
 // ADD Rd, SP, IMM8
 g_nAgbCPUImm8 = (g_nAgbInst &0xff); g_nAgbCPURd = (g_nAgbInst>>8)&7;
  g_nAgbCPUReg[g_nAgbCPURd] = (g_nAgbCPUReg[13]) + (g_nAgbCPUImm8<<2);
}

void agbCpuThumbCFunc_0xb0()
{
 // ADD SP, Imm7*4
 s32 imm7 = (g_nAgbInst&0x7f)<<2;
 if(g_nAgbInst &0x80)
  imm7 = - imm7;
 g_nAgbCPUReg[13] += (imm7);
}

void agbCpuThumbCFunc_0xb4()
{
 //PUSH {Rlist}
 g_nAgbCPUReg[REG_CPUTEMP] =g_nAgbCPUReg[13] - g_nAgbCpuBitsSet[g_nAgbInst &0xff]*4;
 g_nAgbCPUReg[REG_CPUADDRESS] = g_nAgbCPUReg[REG_CPUTEMP] &0xfffffffc;
 if(g_nAgbInst &(0x1)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(0)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x2)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(1)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x4)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(2)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x8)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(3)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x10)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(4)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x20)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(5)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x40)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(6)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x80)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(7)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 g_nAgbCPUReg[13] = g_nAgbCPUReg[REG_CPUTEMP];
}

void agbCpuThumbCFunc_0xb5()
{
 //PUSH {Rlist, LR}
 g_nAgbCPUReg[REG_CPUTEMP] =g_nAgbCPUReg[13] - g_nAgbCpuBitsSet[g_nAgbInst &0xff]*4 -4;
 g_nAgbCPUReg[REG_CPUADDRESS] = g_nAgbCPUReg[REG_CPUTEMP] & 0xfffffffc;
 if(g_nAgbInst &(0x1)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(0)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x2)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(1)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x4)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(2)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x8)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(3)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x10)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(4)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x20)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(5)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x40)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(6)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x80)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(7)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x100)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(14)]); g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 g_nAgbCPUReg[13] = g_nAgbCPUReg[REG_CPUTEMP];
}

void agbCpuThumbCFunc_0xbc()
{
 //POP {Rlist}
 g_nAgbCPUReg[REG_CPUTEMP] =g_nAgbCPUReg[13] + g_nAgbCpuBitsSet[g_nAgbInst &0xff]*4;
 g_nAgbCPUReg[REG_CPUADDRESS] = g_nAgbCPUReg[13]&0xfffffffc;
 if(g_nAgbInst &(0x1)){ g_nAgbCPUReg[(0)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x2)){ g_nAgbCPUReg[(1)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x4)){ g_nAgbCPUReg[(2)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x8)){ g_nAgbCPUReg[(3)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x10)){ g_nAgbCPUReg[(4)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x20)){ g_nAgbCPUReg[(5)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x40)){ g_nAgbCPUReg[(6)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x80)){ g_nAgbCPUReg[(7)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 g_nAgbCPUReg[13] = g_nAgbCPUReg[REG_CPUTEMP];
}

void agbCpuThumbCFunc_0xbd()
{
 //POP {Rlist, PC}
 g_nAgbCPUReg[REG_CPUTEMP] =g_nAgbCPUReg[13] + g_nAgbCpuBitsSet[g_nAgbInst &0xff]*4 + 4;
 g_nAgbCPUReg[REG_CPUADDRESS] = g_nAgbCPUReg[13]&0xfffffffc;
 if(g_nAgbInst &(0x1)){ g_nAgbCPUReg[(0)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x2)){ g_nAgbCPUReg[(1)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x4)){ g_nAgbCPUReg[(2)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x8)){ g_nAgbCPUReg[(3)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x10)){ g_nAgbCPUReg[(4)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x20)){ g_nAgbCPUReg[(5)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x40)){ g_nAgbCPUReg[(6)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 if(g_nAgbInst &(0x80)){ g_nAgbCPUReg[(7)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS] += 4;};
 g_nAgbCPUReg[15] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS])&0xFFFFFFFE;
 g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
  g_nAgbCPUReg[13] = g_nAgbCPUReg[REG_CPUTEMP];
}

void agbCpuThumbCFunc_0xc0_0xc7()
{
 // STMIA Rn, {Rlist}
 u32 g_nAgbCPURn =(g_nAgbInst>>8)&7;
 g_nAgbCPUReg[REG_CPUADDRESS] = g_nAgbCPUReg[g_nAgbCPURn] & 0xfffffffc;
 g_nAgbCPUReg[REG_CPUTEMP] = g_nAgbCPUReg[g_nAgbCPURn] + 4*g_nAgbCpuBitsSet[g_nAgbInst &0xff];
 g_nAgbCPUReg[REG_CPUOFFSET] = 0;
 if(g_nAgbInst &(0x1)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(0)]); if(!(s32)g_nAgbCPUReg[REG_CPUOFFSET]){ g_nAgbCPUReg[(g_nAgbCPURn)] = g_nAgbCPUReg[REG_CPUTEMP];} g_nAgbCPUReg[REG_CPUOFFSET] = 1; g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x2)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(1)]); if(!(s32)g_nAgbCPUReg[REG_CPUOFFSET]){ g_nAgbCPUReg[(g_nAgbCPURn)] = g_nAgbCPUReg[REG_CPUTEMP];} g_nAgbCPUReg[REG_CPUOFFSET] = 1; g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x4)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(2)]); if(!(s32)g_nAgbCPUReg[REG_CPUOFFSET]){ g_nAgbCPUReg[(g_nAgbCPURn)] = g_nAgbCPUReg[REG_CPUTEMP];} g_nAgbCPUReg[REG_CPUOFFSET] = 1; g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x8)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(3)]); if(!(s32)g_nAgbCPUReg[REG_CPUOFFSET]){ g_nAgbCPUReg[(g_nAgbCPURn)] = g_nAgbCPUReg[REG_CPUTEMP];} g_nAgbCPUReg[REG_CPUOFFSET] = 1; g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x10)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(4)]); if(!(s32)g_nAgbCPUReg[REG_CPUOFFSET]){ g_nAgbCPUReg[(g_nAgbCPURn)] = g_nAgbCPUReg[REG_CPUTEMP];} g_nAgbCPUReg[REG_CPUOFFSET] = 1; g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x20)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(5)]); if(!(s32)g_nAgbCPUReg[REG_CPUOFFSET]){ g_nAgbCPUReg[(g_nAgbCPURn)] = g_nAgbCPUReg[REG_CPUTEMP];} g_nAgbCPUReg[REG_CPUOFFSET] = 1; g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x40)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(6)]); if(!(s32)g_nAgbCPUReg[REG_CPUOFFSET]){ g_nAgbCPUReg[(g_nAgbCPURn)] = g_nAgbCPUReg[REG_CPUTEMP];} g_nAgbCPUReg[REG_CPUOFFSET] = 1; g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
 if(g_nAgbInst &(0x80)){ agbMemWrite32(g_nAgbCPUReg[REG_CPUADDRESS], g_nAgbCPUReg[(7)]); if(!(s32)g_nAgbCPUReg[REG_CPUOFFSET]){ g_nAgbCPUReg[(g_nAgbCPURn)] = g_nAgbCPUReg[REG_CPUTEMP];} g_nAgbCPUReg[REG_CPUOFFSET] = 1; g_nAgbCPUReg[REG_CPUADDRESS] +=4;};
}

void agbCpuThumbCFunc_0xc8_0xcf()
{
 // LDMIA Rn, {Rlist}
 g_nAgbCPURn =(g_nAgbInst>>8)&7;
 g_nAgbCPUReg[REG_CPUADDRESS] = g_nAgbCPUReg[g_nAgbCPURn] & 0xfffffffc;
 g_nAgbCPUReg[REG_CPUTEMP] = g_nAgbCPUReg[g_nAgbCPURn] + 4*g_nAgbCpuBitsSet[g_nAgbInst &0xff];
 if(g_nAgbInst &(0x1)){ g_nAgbCPUReg[(0)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS]+=4;};
 if(g_nAgbInst &(0x2)){ g_nAgbCPUReg[(1)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS]+=4;};
 if(g_nAgbInst &(0x4)){ g_nAgbCPUReg[(2)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS]+=4;};
 if(g_nAgbInst &(0x8)){ g_nAgbCPUReg[(3)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS]+=4;};
 if(g_nAgbInst &(0x10)){ g_nAgbCPUReg[(4)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS]+=4;};
 if(g_nAgbInst &(0x20)){ g_nAgbCPUReg[(5)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS]+=4;};
 if(g_nAgbInst &(0x40)){ g_nAgbCPUReg[(6)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS]+=4;};
 if(g_nAgbInst &(0x80)){ g_nAgbCPUReg[(7)] = agbMemRead32(g_nAgbCPUReg[REG_CPUADDRESS]); g_nAgbCPUReg[REG_CPUADDRESS]+=4;};
 if(!(g_nAgbInst &(1<<g_nAgbCPURn)))
  g_nAgbCPUReg[g_nAgbCPURn] = g_nAgbCPUReg[REG_CPUTEMP];
}

void agbCpuThumbCFunc_0xd0()
{
 //BEQ SImm8
 if(g_nAgbCPUReg[REG_ZFLAG])
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xd1()
{
 //BNE SImm8
 if(g_nAgbCPUReg[REG_ZFLAG] == 0)
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xd2()
{
 //BCS SImm8
 if(g_nAgbCPUReg[REG_CFLAG])
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xd3()
{
 //BCC SImm8
 if(g_nAgbCPUReg[REG_CFLAG] == 0)
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xd4()
{
 //BMI SImm8
 if(g_nAgbCPUReg[REG_NFLAG])
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xd5()
{
 //BPL SImm8
 if(g_nAgbCPUReg[REG_NFLAG] == 0)
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xd6()
{
 //BVS SImm8
 if(g_nAgbCPUReg[REG_VFLAG])
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xd7()
{
 //BVC SImm8
 if(g_nAgbCPUReg[REG_VFLAG] == 0)
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xd8()
{
 //BHI SImm8
 if(g_nAgbCPUReg[REG_CFLAG] && g_nAgbCPUReg[REG_ZFLAG] == 0)
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xd9()
{
 //BLS SImm8
 if(g_nAgbCPUReg[REG_CFLAG] == 0 || g_nAgbCPUReg[REG_ZFLAG])
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xda()
{
 //BGE SImm8
 if(g_nAgbCPUReg[REG_NFLAG] == g_nAgbCPUReg[REG_VFLAG])
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xdb()
{
 //BLT SImm8
 if(g_nAgbCPUReg[REG_NFLAG] != g_nAgbCPUReg[REG_VFLAG])
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xdc()
{
 //BGT SImm8
 if(g_nAgbCPUReg[REG_ZFLAG] == 0 && (g_nAgbCPUReg[REG_NFLAG] == g_nAgbCPUReg[REG_VFLAG]))
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xdd()
{
 //BLE SImm8
 if(g_nAgbCPUReg[REG_ZFLAG] || (g_nAgbCPUReg[REG_NFLAG] != g_nAgbCPUReg[REG_VFLAG]))
 {
  g_nAgbCPUReg[15] += ((s8)(g_nAgbInst &0xff))<<1; g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
 }
}

void agbCpuThumbCFunc_0xdf()
{
 // SWI
 agbCPUSWI(g_nAgbInst &0xff);
}

void agbCpuThumbCFunc_0xe0_0xe7()
{
 //B Imm11
 g_nAgbCPUReg[REG_CPUOFFSET] = (s32)(g_nAgbInst & 0x3ff)<<1;
 if(g_nAgbInst &0x0400)
  g_nAgbCPUReg[REG_CPUOFFSET] |= 0xfffff800;
 g_nAgbCPUReg[15] += (s32)g_nAgbCPUReg[REG_CPUOFFSET];
 g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
}

void agbCpuThumbCFunc_0xf0_0xf3()
{
 // BLL #(s32)g_nAgbCPUReg[REG_CPUOFFSET]
 g_nAgbCPUReg[REG_CPUOFFSET] = (g_nAgbInst & 0x7ff);
 g_nAgbCPUReg[14] = g_nAgbCPUReg[15] + ((s32)g_nAgbCPUReg[REG_CPUOFFSET] << 12);
}

void agbCpuThumbCFunc_0xf4_0xf7()
{
 // BLL #(s32)g_nAgbCPUReg[REG_CPUOFFSET]
 g_nAgbCPUReg[REG_CPUOFFSET] = (g_nAgbInst & 0x7ff);
 g_nAgbCPUReg[14] = g_nAgbCPUReg[15] + (((s32)g_nAgbCPUReg[REG_CPUOFFSET] << 12) | 0xff800000);
}

void agbCpuThumbCFunc_0xf8_0xff()
{
 // BLH
 g_nAgbCPUReg[REG_CPUOFFSET] = (g_nAgbInst &0x7ff);
 g_nAgbCPUReg[REG_CPUTEMP] = g_nAgbCPUReg[15] -2;
 g_nAgbCPUReg[15] = (g_nAgbCPUReg[14] + ((s32)g_nAgbCPUReg[REG_CPUOFFSET]<<1))&0xfffffffe;
 g_nAgbCPUReg[14]= g_nAgbCPUReg[REG_CPUTEMP]|1;
 g_nAgbInsta = agbMemRead16(g_nAgbCPUReg[15]); g_nAgbInstb = agbMemRead16(g_nAgbCPUReg[15] + 2); g_nAgbCPUReg[15] += 2;
}

void agbCpuThumbCFunc_und()
{
 //unknown thumb
 TRL_ERROR("unknown thumb instruction");
}


//========================this is a line ^_^============================
void (*g_pAgbCPUThumbFuncTable[])() =
{
 agbCpuThumbCFunc_0x00_0x07, agbCpuThumbCFunc_0x00_0x07, agbCpuThumbCFunc_0x00_0x07, agbCpuThumbCFunc_0x00_0x07, agbCpuThumbCFunc_0x00_0x07, agbCpuThumbCFunc_0x00_0x07, agbCpuThumbCFunc_0x00_0x07, agbCpuThumbCFunc_0x00_0x07,
 agbCpuThumbCFunc_0x08_0x0f, agbCpuThumbCFunc_0x08_0x0f, agbCpuThumbCFunc_0x08_0x0f, agbCpuThumbCFunc_0x08_0x0f, agbCpuThumbCFunc_0x08_0x0f, agbCpuThumbCFunc_0x08_0x0f, agbCpuThumbCFunc_0x08_0x0f, agbCpuThumbCFunc_0x08_0x0f,
 agbCpuThumbCFunc_0x10_0x17, agbCpuThumbCFunc_0x10_0x17, agbCpuThumbCFunc_0x10_0x17, agbCpuThumbCFunc_0x10_0x17, agbCpuThumbCFunc_0x10_0x17, agbCpuThumbCFunc_0x10_0x17, agbCpuThumbCFunc_0x10_0x17, agbCpuThumbCFunc_0x10_0x17,
 agbCpuThumbCFunc_0x18_0x19, agbCpuThumbCFunc_0x18_0x19,
 agbCpuThumbCFunc_0x1a_0x1b, agbCpuThumbCFunc_0x1a_0x1b,
 agbCpuThumbCFunc_0x1c_0x1d, agbCpuThumbCFunc_0x1c_0x1d,
 agbCpuThumbCFunc_0x1e_0x1f, agbCpuThumbCFunc_0x1e_0x1f,
 agbCpuThumbCFunc_0x20_0x27, agbCpuThumbCFunc_0x20_0x27, agbCpuThumbCFunc_0x20_0x27, agbCpuThumbCFunc_0x20_0x27, agbCpuThumbCFunc_0x20_0x27, agbCpuThumbCFunc_0x20_0x27, agbCpuThumbCFunc_0x20_0x27, agbCpuThumbCFunc_0x20_0x27,
 agbCpuThumbCFunc_0x28_0x2f, agbCpuThumbCFunc_0x28_0x2f, agbCpuThumbCFunc_0x28_0x2f, agbCpuThumbCFunc_0x28_0x2f, agbCpuThumbCFunc_0x28_0x2f, agbCpuThumbCFunc_0x28_0x2f, agbCpuThumbCFunc_0x28_0x2f, agbCpuThumbCFunc_0x28_0x2f,
 agbCpuThumbCFunc_0x30_0x37, agbCpuThumbCFunc_0x30_0x37, agbCpuThumbCFunc_0x30_0x37, agbCpuThumbCFunc_0x30_0x37, agbCpuThumbCFunc_0x30_0x37, agbCpuThumbCFunc_0x30_0x37, agbCpuThumbCFunc_0x30_0x37, agbCpuThumbCFunc_0x30_0x37,
 agbCpuThumbCFunc_0x38_0x3f, agbCpuThumbCFunc_0x38_0x3f, agbCpuThumbCFunc_0x38_0x3f, agbCpuThumbCFunc_0x38_0x3f, agbCpuThumbCFunc_0x38_0x3f, agbCpuThumbCFunc_0x38_0x3f, agbCpuThumbCFunc_0x38_0x3f, agbCpuThumbCFunc_0x38_0x3f,
 agbCpuThumbCFunc_0x40,
 agbCpuThumbCFunc_0x41,
 agbCpuThumbCFunc_0x42,
 agbCpuThumbCFunc_0x43,
 agbCpuThumbCFunc_0x44,
 agbCpuThumbCFunc_0x45,
 agbCpuThumbCFunc_0x46,
 agbCpuThumbCFunc_0x47,
 agbCpuThumbCFunc_0x48_0x4f, agbCpuThumbCFunc_0x48_0x4f, agbCpuThumbCFunc_0x48_0x4f, agbCpuThumbCFunc_0x48_0x4f, agbCpuThumbCFunc_0x48_0x4f, agbCpuThumbCFunc_0x48_0x4f, agbCpuThumbCFunc_0x48_0x4f, agbCpuThumbCFunc_0x48_0x4f,
 agbCpuThumbCFunc_0x50_0x51, agbCpuThumbCFunc_0x50_0x51,
 agbCpuThumbCFunc_0x52_0x53, agbCpuThumbCFunc_0x52_0x53,
 agbCpuThumbCFunc_0x54_0x55, agbCpuThumbCFunc_0x54_0x55,
 agbCpuThumbCFunc_0x56_0x57, agbCpuThumbCFunc_0x56_0x57,
 agbCpuThumbCFunc_0x58_0x59, agbCpuThumbCFunc_0x58_0x59,
 agbCpuThumbCFunc_0x5a_0x5b, agbCpuThumbCFunc_0x5a_0x5b,
 agbCpuThumbCFunc_0x5c_0x5d, agbCpuThumbCFunc_0x5c_0x5d,
 agbCpuThumbCFunc_0x5e_0x5f, agbCpuThumbCFunc_0x5e_0x5f,
 agbCpuThumbCFunc_0x60_0x67, agbCpuThumbCFunc_0x60_0x67, agbCpuThumbCFunc_0x60_0x67, agbCpuThumbCFunc_0x60_0x67, agbCpuThumbCFunc_0x60_0x67, agbCpuThumbCFunc_0x60_0x67, agbCpuThumbCFunc_0x60_0x67, agbCpuThumbCFunc_0x60_0x67,
 agbCpuThumbCFunc_0x68_0x6f, agbCpuThumbCFunc_0x68_0x6f, agbCpuThumbCFunc_0x68_0x6f, agbCpuThumbCFunc_0x68_0x6f, agbCpuThumbCFunc_0x68_0x6f, agbCpuThumbCFunc_0x68_0x6f, agbCpuThumbCFunc_0x68_0x6f, agbCpuThumbCFunc_0x68_0x6f,
 agbCpuThumbCFunc_0x70_0x77, agbCpuThumbCFunc_0x70_0x77, agbCpuThumbCFunc_0x70_0x77, agbCpuThumbCFunc_0x70_0x77, agbCpuThumbCFunc_0x70_0x77, agbCpuThumbCFunc_0x70_0x77, agbCpuThumbCFunc_0x70_0x77, agbCpuThumbCFunc_0x70_0x77,
 agbCpuThumbCFunc_0x78_0x7f, agbCpuThumbCFunc_0x78_0x7f, agbCpuThumbCFunc_0x78_0x7f, agbCpuThumbCFunc_0x78_0x7f, agbCpuThumbCFunc_0x78_0x7f, agbCpuThumbCFunc_0x78_0x7f, agbCpuThumbCFunc_0x78_0x7f, agbCpuThumbCFunc_0x78_0x7f,
 agbCpuThumbCFunc_0x80_0x87, agbCpuThumbCFunc_0x80_0x87, agbCpuThumbCFunc_0x80_0x87, agbCpuThumbCFunc_0x80_0x87, agbCpuThumbCFunc_0x80_0x87, agbCpuThumbCFunc_0x80_0x87, agbCpuThumbCFunc_0x80_0x87, agbCpuThumbCFunc_0x80_0x87,
 agbCpuThumbCFunc_0x88_0x8f, agbCpuThumbCFunc_0x88_0x8f, agbCpuThumbCFunc_0x88_0x8f, agbCpuThumbCFunc_0x88_0x8f, agbCpuThumbCFunc_0x88_0x8f, agbCpuThumbCFunc_0x88_0x8f, agbCpuThumbCFunc_0x88_0x8f, agbCpuThumbCFunc_0x88_0x8f,
 agbCpuThumbCFunc_0x90_0x97, agbCpuThumbCFunc_0x90_0x97, agbCpuThumbCFunc_0x90_0x97, agbCpuThumbCFunc_0x90_0x97, agbCpuThumbCFunc_0x90_0x97, agbCpuThumbCFunc_0x90_0x97, agbCpuThumbCFunc_0x90_0x97, agbCpuThumbCFunc_0x90_0x97,
 agbCpuThumbCFunc_0x98_0x9f, agbCpuThumbCFunc_0x98_0x9f, agbCpuThumbCFunc_0x98_0x9f, agbCpuThumbCFunc_0x98_0x9f, agbCpuThumbCFunc_0x98_0x9f, agbCpuThumbCFunc_0x98_0x9f, agbCpuThumbCFunc_0x98_0x9f, agbCpuThumbCFunc_0x98_0x9f,
 agbCpuThumbCFunc_0xa0_0xa7, agbCpuThumbCFunc_0xa0_0xa7, agbCpuThumbCFunc_0xa0_0xa7, agbCpuThumbCFunc_0xa0_0xa7, agbCpuThumbCFunc_0xa0_0xa7, agbCpuThumbCFunc_0xa0_0xa7, agbCpuThumbCFunc_0xa0_0xa7, agbCpuThumbCFunc_0xa0_0xa7,
 agbCpuThumbCFunc_0xa8_0xaf, agbCpuThumbCFunc_0xa8_0xaf, agbCpuThumbCFunc_0xa8_0xaf, agbCpuThumbCFunc_0xa8_0xaf, agbCpuThumbCFunc_0xa8_0xaf, agbCpuThumbCFunc_0xa8_0xaf, agbCpuThumbCFunc_0xa8_0xaf, agbCpuThumbCFunc_0xa8_0xaf,
 agbCpuThumbCFunc_0xb0,
 agbCpuThumbCFunc_und,
 agbCpuThumbCFunc_und, agbCpuThumbCFunc_und,
 agbCpuThumbCFunc_0xb4,
 agbCpuThumbCFunc_0xb5,
 agbCpuThumbCFunc_und, agbCpuThumbCFunc_und,
 agbCpuThumbCFunc_und, agbCpuThumbCFunc_und, agbCpuThumbCFunc_und, agbCpuThumbCFunc_und,
 agbCpuThumbCFunc_0xbc,
 agbCpuThumbCFunc_0xbd,
 agbCpuThumbCFunc_und, agbCpuThumbCFunc_und,
 agbCpuThumbCFunc_0xc0_0xc7, agbCpuThumbCFunc_0xc0_0xc7, agbCpuThumbCFunc_0xc0_0xc7, agbCpuThumbCFunc_0xc0_0xc7, agbCpuThumbCFunc_0xc0_0xc7, agbCpuThumbCFunc_0xc0_0xc7, agbCpuThumbCFunc_0xc0_0xc7, agbCpuThumbCFunc_0xc0_0xc7,
 agbCpuThumbCFunc_0xc8_0xcf, agbCpuThumbCFunc_0xc8_0xcf, agbCpuThumbCFunc_0xc8_0xcf, agbCpuThumbCFunc_0xc8_0xcf, agbCpuThumbCFunc_0xc8_0xcf, agbCpuThumbCFunc_0xc8_0xcf, agbCpuThumbCFunc_0xc8_0xcf, agbCpuThumbCFunc_0xc8_0xcf,
 agbCpuThumbCFunc_0xd0,
 agbCpuThumbCFunc_0xd1,
 agbCpuThumbCFunc_0xd2,
 agbCpuThumbCFunc_0xd3,
 agbCpuThumbCFunc_0xd4,
 agbCpuThumbCFunc_0xd5,
 agbCpuThumbCFunc_0xd6,
 agbCpuThumbCFunc_0xd7,
 agbCpuThumbCFunc_0xd8,
 agbCpuThumbCFunc_0xd9,
 agbCpuThumbCFunc_0xda,
 agbCpuThumbCFunc_0xdb,
 agbCpuThumbCFunc_0xdc,
 agbCpuThumbCFunc_0xdd,
 agbCpuThumbCFunc_und,
 agbCpuThumbCFunc_0xdf,
 agbCpuThumbCFunc_0xe0_0xe7, agbCpuThumbCFunc_0xe0_0xe7, agbCpuThumbCFunc_0xe0_0xe7, agbCpuThumbCFunc_0xe0_0xe7, agbCpuThumbCFunc_0xe0_0xe7, agbCpuThumbCFunc_0xe0_0xe7, agbCpuThumbCFunc_0xe0_0xe7, agbCpuThumbCFunc_0xe0_0xe7,
 agbCpuThumbCFunc_und, agbCpuThumbCFunc_und, agbCpuThumbCFunc_und, agbCpuThumbCFunc_und, agbCpuThumbCFunc_und, agbCpuThumbCFunc_und, agbCpuThumbCFunc_und, agbCpuThumbCFunc_und,
 agbCpuThumbCFunc_0xf0_0xf3, agbCpuThumbCFunc_0xf0_0xf3, agbCpuThumbCFunc_0xf0_0xf3, agbCpuThumbCFunc_0xf0_0xf3,
 agbCpuThumbCFunc_0xf4_0xf7, agbCpuThumbCFunc_0xf4_0xf7, agbCpuThumbCFunc_0xf4_0xf7, agbCpuThumbCFunc_0xf4_0xf7,
 agbCpuThumbCFunc_0xf8_0xff, agbCpuThumbCFunc_0xf8_0xff, agbCpuThumbCFunc_0xf8_0xff, agbCpuThumbCFunc_0xf8_0xff, agbCpuThumbCFunc_0xf8_0xff, agbCpuThumbCFunc_0xf8_0xff, agbCpuThumbCFunc_0xf8_0xff, agbCpuThumbCFunc_0xf8_0xff,
};


