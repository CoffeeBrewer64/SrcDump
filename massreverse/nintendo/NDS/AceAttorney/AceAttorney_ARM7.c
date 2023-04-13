/*

PART OF MASSREVERSE BY COFFEEBREWER64

*/

#include "AceAttorney_ARM7.h"



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void _entry_arm7(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  iVar1 = DAT_0238009c;
  _REG_IME = 0x4000000;
  puVar2 = (undefined4 *)PTR_DAT_02380098;
  if (-1 < 0x3800000 - (int)PTR_DAT_02380098) {
    puVar2 = (undefined4 *)&DAT_03800000;
  }
  for (; (int)puVar2 < iVar1; puVar2 = puVar2 + 1) {
    *puVar2 = 0;
  }
  FUN_023800c0();
  puVar3 = *(undefined4 **)(PTR_PTR_DAT_023800ac + 0x10);
  for (puVar2 = *(undefined4 **)(PTR_PTR_DAT_023800ac + 0xc); puVar2 < puVar3; puVar2 = puVar2 + 1)
  {
    *puVar2 = 0;
  }
  FUN_0238011c();
  *(undefined4 *)PTR_NDS7_IRQ_Handler_023800b0 = DAT_023800b4;
                    // WARNING: Could not recover jumptable at 0x02380094. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_023800b8)();
  return;
}



void FUN_023800c0(void)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  
  puVar1 = *(undefined4 **)PTR_PTR_DAT_02380114;
  puVar3 = *(undefined4 **)(PTR_PTR_DAT_02380114 + 4);
  puVar4 = *(undefined4 **)(PTR_PTR_DAT_02380114 + 8);
  do {
    if (puVar1 == puVar3) {
      return;
    }
    puVar5 = (undefined4 *)*puVar1;
    piVar2 = puVar1 + 2;
    iVar6 = (int)puVar5 + puVar1[1];
    for (; (int)puVar5 - iVar6 < 0; puVar5 = puVar5 + 1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
    }
    puVar1 = puVar1 + 3;
    puVar7 = (undefined4 *)((int)puVar5 + *piVar2);
    for (; puVar5 < puVar7; puVar5 = puVar5 + 1) {
      *puVar5 = 0;
    }
  } while (puVar5 == puVar7);
  return;
}



void FUN_0238011c(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  uint uVar3;
  ushort *puVar4;
  
  puVar1 = DAT_02380154;
  uVar2 = 1;
  uVar3 = 0;
  puVar4 = DAT_02380154 + -0x200000;
  do {
    *puVar1 = (short)uVar3;
    if (uVar3 != *puVar4) {
      uVar2 = 2;
      break;
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 != 2);
  *puVar1 = uVar2;
  return;
}



uint FUN_0238019c(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar5 = 0;
  iVar2 = FUN_02380358();
  if (iVar2 == 0) {
    iVar2 = FUN_02380334();
    uVar1 = DAT_02380324;
    if (iVar2 != 0) {
      return 3;
    }
    uVar6 = 0;
    do {
      uVar3 = thunk_EXT_FUN_03803de4(uVar1,param_1 + uVar6 * 0x100,0x70);
      iVar2 = param_1 + uVar6 * 0x100;
      if ((uVar3 == *(ushort *)(iVar2 + 0x72)) && (*(ushort *)(iVar2 + 0x70) < 0x80)) {
        uVar5 = uVar5 | 1 << (uVar6 & 0xff);
      }
      uVar6 = uVar6 + 1 & 0xffff;
    } while (uVar6 < 2);
  }
  else {
    uVar3 = FUN_02380334();
    uVar6 = 0;
    do {
      iVar2 = param_1 + uVar6 * 0x100;
      uVar4 = thunk_EXT_FUN_03803de4(DAT_02380324,iVar2,0x70);
      if (((uVar4 == *(ushort *)(iVar2 + 0x72)) && (*(ushort *)(iVar2 + 0x70) < 0x80)) &&
         (uVar4 = thunk_EXT_FUN_03803de4(DAT_02380324,iVar2 + 0x74,0x8a),
         uVar4 == *(ushort *)(iVar2 + 0xfe))) {
        if ((1 << (ushort)*(byte *)(iVar2 + 0x75) & (uint)*(ushort *)(iVar2 + 0x76)) != 0) {
          if ((uVar3 & *(ushort *)(iVar2 + 0x76)) != 0) {
            *(ushort *)(iVar2 + 100) =
                 *(ushort *)(iVar2 + 100) & 0xfff8 | *(byte *)(iVar2 + 0x75) & 7;
          }
          uVar5 = uVar5 | 1 << (uVar6 & 0xff);
        }
      }
      uVar6 = uVar6 + 1 & 0xffff;
    } while (uVar6 < 2);
  }
  if ((uVar5 != 1) && (uVar5 != 2)) {
    if (uVar5 == 3) {
      if ((*(short *)(param_1 + 0x70) + 1U & 0x7f) == *(ushort *)(param_1 + 0x170)) {
        uVar5 = 2;
      }
      else {
        uVar5 = 1;
      }
    }
    else {
      uVar5 = 0;
    }
  }
  return uVar5;
}



void thunk_EXT_FUN_03803de4(void)

{
                    // WARNING: Could not recover jumptable at 0x0238032c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02380330)();
  return;
}



undefined4 FUN_02380334(void)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*DAT_02380354 == -0x80) {
    uVar1 = 0x40;
  }
  return uVar1;
}



undefined4 FUN_02380358(void)

{
  undefined4 uVar1;
  byte local_8 [8];
  
  func_0x0137d7a4(0x1d,1,local_8);
  if (local_8[0] == 0xff) {
    uVar1 = 0;
  }
  else if ((local_8[0] & 0x40) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



void FUN_02380398(void)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined2 auStack_304 [11];
  undefined2 auStack_2ee [27];
  byte abStack_2b8 [152];
  ushort local_220 [2];
  int local_21c;
  undefined4 auStack_218 [2];
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 auStack_208 [64];
  undefined auStack_108 [256];
  
  func_0x0137d7a4(0x20,2,&local_21c);
  local_21c = local_21c << 3;
  func_0x0137d7a4(local_21c,0x100,auStack_208);
  func_0x0137d7a4(local_21c + 0x100,0x100,auStack_108);
  uVar2 = FUN_0238019c((int)auStack_208);
  if ((int)uVar2 < 3) {
    if (uVar2 == 0) {
      local_20c = 0;
      FUN_023860f4(0,DAT_02380524,0x74);
    }
    else {
      if (*(byte *)((int)local_220 + uVar2 * 0x100 + DAT_02380528) < 10) {
        for (iVar3 = 10; (int)(uint)*(byte *)(auStack_2ee + uVar2 * 0x80) < iVar3;
            iVar3 = iVar3 + -1) {
          auStack_304[uVar2 * 0x80 + iVar3] = 0;
        }
      }
      if (*(byte *)((int)local_220 + uVar2 * 0x100 + DAT_0238052c) < 0x1a) {
        for (iVar3 = 0x1a; (int)(uint)abStack_2b8[uVar2 * 0x100] < iVar3; iVar3 = iVar3 + -1) {
          auStack_2ee[uVar2 * 0x80 + iVar3] = 0;
        }
      }
      FUN_02386108(auStack_208 + (uVar2 - 1) * 0x40,DAT_02380524,0x74);
    }
  }
  else {
    local_210 = 0xffffffff;
    FUN_023860f4(0xffffffff,DAT_02380524,0x74);
  }
  func_0x0137d7a4(0x36,6,auStack_218);
  puVar1 = DAT_02380524;
  FUN_02386200(auStack_218,DAT_02380524 + 0x1d,6);
  func_0x0137d7a4(0x3c,2,local_220);
  uVar2 = FUN_0238f884(((uint)local_220[0] << 0xf) >> 0x10);
  *(short *)((int)puVar1 + 0x7a) = (short)uVar2;
  return;
}



int FUN_02380530(void)

{
  uint uVar1;
  undefined4 *puVar2;
  uint *puVar3;
  int iVar4;
  
  uVar1 = FUN_02384a98(8);
  puVar2 = (undefined4 *)FUN_02384a84(8);
  puVar3 = (uint *)FUN_02384d9c(8,puVar2,uVar1,1);
  iVar4 = FUN_02384a98(8);
  FUN_0238616c(puVar3,0,iVar4 - (int)puVar3);
  FUN_02384994(8,puVar3);
  uVar1 = FUN_02384a98(8);
  iVar4 = FUN_02384a84(8);
  iVar4 = FUN_02384cf4(8,iVar4,uVar1);
  if (iVar4 < 0) {
    FUN_02385ea8();
  }
  FUN_02384e44(8,iVar4);
  FUN_02384b50(8,iVar4);
  return iVar4;
}



void FUN_023805dc(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  short sVar1;
  int iVar2;
  undefined4 extraout_r1;
  
  FUN_0238495c();
  FUN_023842f8();
  FUN_02380398();
  thunk_EXT_FUN_037fe42c();
  iVar2 = FUN_02380530();
  FUN_02387240(6);
  FUN_023866f4();
  FUN_023839d0(1,DAT_02380688);
  FUN_02383918(1);
  *(ushort *)PTR_REG_DISPSTAT_0238068c = *(ushort *)PTR_REG_DISPSTAT_0238068c | 8;
  *(undefined2 *)PTR_REG_IME_02380690 = 1;
  FUN_02385e04();
  FUN_0238ac30(0xffffffff);
  FUN_0238acbc(0xf,extraout_r1,param_3,param_4);
  func_0x0137e294(0xc);
  FUN_0238dc40(iVar2);
  FUN_0238c3b8(2);
  do {
    thunk_EXT_FUN_03803db2();
    sVar1 = FUN_02385f7c();
    if (sVar1 != 0) {
      FUN_02385ebc();
    }
    FUN_0238eb6c();
    FUN_0238bcbc();
  } while( true );
}



void thunk_EXT_FUN_03803db2(void)

{
                    // WARNING: Could not recover jumptable at 0x02380698. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_0238069c)();
  return;
}



void FUN_023806a0(void)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *apiStack_28 [2];
  
  piVar1 = DAT_02380754;
  iVar6 = *DAT_02380754;
  *(undefined2 *)(iVar6 + 0x10) = 0;
  *(undefined2 *)(iVar6 + 0x14) = 0;
  uVar3 = DAT_0238075c;
  uVar2 = DAT_02380758;
  do {
    while( true ) {
      iVar4 = FUN_02384644(*(ushort **)(*piVar1 + 0x2dc),apiStack_28,0);
      if (iVar4 != 0) {
        FUN_023808dc(apiStack_28);
      }
      uVar5 = FUN_023838dc(uVar2);
      *(undefined2 *)(iVar6 + 0x12) = *(undefined2 *)(iVar6 + 0x10);
      if (*(ushort *)(iVar6 + (uint)*(ushort *)(iVar6 + 0x12) * 2) != uVar3) break;
      *(short *)(iVar6 + 0x10) = *(short *)(iVar6 + 0x10) + 1;
      FUN_02383918(uVar5);
    }
    FUN_02383918(uVar5);
    uVar5 = FUN_02380820((uint)*(ushort *)(iVar6 + 0x12));
    *(short *)(iVar6 + 0x14) = (short)uVar5;
    (**(code **)(iVar6 + (uint)*(ushort *)(iVar6 + 0x14) * 8 + 0x94))();
    *(short *)(iVar6 + 0x14) = (short)uVar3;
  } while( true );
}



void FUN_02380760(int param_1,int param_2)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = *DAT_02380814;
  uVar3 = FUN_023838dc(DAT_02380818);
  iVar5 = iVar6 + 0x90 + param_2 * 8;
  if (*(short *)(iVar5 + 2) == 0) {
    *(undefined2 *)(iVar5 + 2) = 1;
    uVar2 = DAT_0238081c;
    *(short *)(iVar6 + 0x90 + param_2 * 8) = (short)DAT_0238081c;
    uVar4 = (uint)*(ushort *)(iVar6 + param_1 * 2 + 8);
    uVar1 = (undefined2)param_2;
    if (uVar4 == uVar2) {
      *(undefined2 *)(iVar6 + param_1 * 2) = uVar1;
    }
    else {
      *(undefined2 *)(iVar6 + uVar4 * 8 + 0x90) = uVar1;
    }
    *(undefined2 *)(iVar6 + param_1 * 2 + 8) = uVar1;
    if (param_1 < (int)(uint)*(ushort *)(iVar6 + 0x10)) {
      *(short *)(iVar6 + 0x10) = (short)param_1;
    }
  }
  FUN_02383918(uVar3);
  if ((param_1 != 3) && (*(short *)(iVar6 + 0x12) == 3)) {
    FUN_023846e4(*(ushort **)(*DAT_02380814 + 0x2dc),0,0);
  }
  return;
}



uint FUN_02380820(int param_1)

{
  int iVar1;
  ushort uVar2;
  undefined2 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = *DAT_0238088c;
  uVar5 = FUN_023838dc(DAT_02380890);
  uVar4 = DAT_02380894;
  iVar1 = param_1 * 2;
  uVar6 = (uint)*(ushort *)(iVar7 + iVar1);
  if (uVar6 != DAT_02380894) {
    iVar8 = iVar7 + 0x90;
    *(undefined2 *)(iVar8 + uVar6 * 8 + 2) = 0;
    uVar2 = *(ushort *)(iVar8 + uVar6 * 8);
    uVar3 = (undefined2)uVar4;
    if (uVar2 == uVar4) {
      *(undefined2 *)(iVar7 + iVar1) = uVar3;
      *(undefined2 *)(iVar7 + iVar1 + 8) = uVar3;
    }
    else {
      *(ushort *)(iVar7 + iVar1) = uVar2;
      *(undefined2 *)(iVar8 + uVar6 * 8) = uVar3;
    }
  }
  FUN_02383918(uVar5);
  return uVar6;
}



void FUN_02380898(void)

{
  int *apiStack_8 [2];
  
  FUN_02384644(*(ushort **)(*DAT_023808d8 + 0x2dc),apiStack_8,1);
  FUN_023808dc(apiStack_8);
  FUN_02380760(3,0xc);
  return;
}



void FUN_023808dc(int **param_1)

{
  if (*param_1 != (int *)0x0) {
    FUN_0238091c((int **)(*DAT_02380918 + 0x1d4),*param_1);
    FUN_02380760(2,0xb);
  }
  return;
}



undefined4 FUN_0238091c(int **param_1,int *param_2)

{
  uint uVar1;
  int *piVar2;
  
  uVar1 = FUN_023838dc(0x1000000);
  if (*(short *)(param_1 + 2) == 0) {
    *param_2 = -1;
    *param_1 = param_2;
  }
  else {
    piVar2 = param_1[1];
    *param_2 = (int)piVar2;
    piVar2[1] = (int)param_2;
  }
  param_2[1] = -1;
  *(undefined2 *)(param_2 + 2) = *(undefined2 *)((int)param_1 + 10);
  *(short *)((int)param_2 + 10) = (short)DAT_02380990;
  param_1[1] = param_2;
  *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
  FUN_02383918(uVar1);
  return 0;
}



undefined4 FUN_02380994(int *param_1,int *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (*(ushort *)((int)param_2 + 10) == DAT_02380a74) {
    if (*(short *)(param_2 + 2) == *(short *)((int)param_1 + 10)) {
      uVar2 = FUN_023838dc(0x1000000);
      *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + -1;
      if (*(short *)(param_1 + 2) == 0) {
        *param_1 = -1;
        param_1[1] = -1;
      }
      else if (param_2 == (int *)*param_1) {
        *param_1 = param_2[1];
        *(undefined4 *)*param_1 = 0xffffffff;
      }
      else if (param_2 == (int *)param_1[1]) {
        param_1[1] = *param_2;
        *(undefined4 *)(param_1[1] + 4) = 0xffffffff;
      }
      else {
        *(int *)param_2[1] = *param_2;
        *(int *)(*param_2 + 4) = param_2[1];
      }
      *(undefined2 *)(param_2 + 2) = 0;
      FUN_02383918(uVar2);
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



int * FUN_02380a78(int **param_1,int param_2)

{
  int iVar1;
  int *unaff_r4;
  
  iVar1 = *DAT_02380b18;
  if (param_2 == 0) {
    unaff_r4 = (int *)0x0;
  }
  else {
    if (*(int *)(iVar1 + 0x150) == 0) {
      unaff_r4 = FUN_02384ef4(*(int *)(iVar1 + 0x154),*(int *)(iVar1 + 0x158),param_2 + 0xc);
    }
    else if (*(int *)(iVar1 + 0x150) == 1) {
      unaff_r4 = (int *)(**(code **)(iVar1 + 0x154))(param_2 + 0xc);
    }
    if (unaff_r4 == (int *)0x0) {
      unaff_r4 = (int *)0x0;
    }
    else {
      *(short *)((int)unaff_r4 + 10) = (short)DAT_02380b1c;
      *(undefined2 *)(unaff_r4 + 2) = 0;
      FUN_02380c18(param_1,unaff_r4);
    }
  }
  return unaff_r4;
}



int FUN_02380b20(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *DAT_02380b9c;
  if (*(ushort *)((int)param_2 + 10) == DAT_02380ba0) {
    iVar1 = FUN_02380994(param_1,param_2);
    if (iVar1 == 0) {
      if (*(int *)(iVar2 + 0x150) == 0) {
        FUN_02384e80(*(int *)(iVar2 + 0x154),*(int *)(iVar2 + 0x158),(int)param_2);
      }
      else if (*(int *)(iVar2 + 0x150) == 1) {
        (**(code **)(iVar2 + 0x158))(param_2);
      }
    }
  }
  else {
    iVar1 = 1;
  }
  return iVar1;
}



int FUN_02380ba4(int *param_1,int **param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  
  if (*(ushort *)((int)param_3 + 10) == DAT_02380c14) {
    uVar2 = FUN_023838dc(0x1000000);
    iVar1 = FUN_02380994(param_1,param_3);
    if (iVar1 == 0) {
      iVar1 = FUN_02380c18(param_2,param_3);
    }
    FUN_02383918(uVar2);
  }
  else {
    iVar1 = 1;
  }
  return iVar1;
}



undefined4 FUN_02380c18(int **param_1,int *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int *piVar3;
  
  if (*(ushort *)((int)param_2 + 10) == DAT_02380ca8) {
    if (*(short *)(param_2 + 2) == 0) {
      uVar2 = FUN_023838dc(0x1000000);
      if (*(short *)(param_1 + 2) == 0) {
        *param_2 = -1;
        *param_1 = param_2;
      }
      else {
        piVar3 = param_1[1];
        *param_2 = (int)piVar3;
        piVar3[1] = (int)param_2;
      }
      param_2[1] = -1;
      *(undefined2 *)(param_2 + 2) = *(undefined2 *)((int)param_1 + 10);
      param_1[1] = param_2;
      *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
      FUN_02383918(uVar2);
      uVar1 = 0;
    }
    else {
      uVar1 = 2;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



void FUN_02380cb4(void)

{
  ushort uVar1;
  short sVar2;
  int *piVar3;
  undefined2 uVar4;
  int *piVar5;
  ushort uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int in_r3;
  ushort uVar10;
  ushort *puVar11;
  int **ppiVar12;
  uint uVar13;
  
  piVar3 = DAT_02380fa4;
  iVar7 = *DAT_02380fa4;
  ppiVar12 = (int **)(iVar7 + 0x3f8);
  uVar6 = 0;
  uVar10 = 0;
  if (*(short *)(iVar7 + 0x3fc) != 0) {
    return;
  }
  *ppiVar12 = *(int **)(iVar7 + 0x1d4);
  piVar5 = *ppiVar12;
  if (piVar5 == (int *)0xffffffff) {
    return;
  }
  uVar1 = *(ushort *)((int)piVar5 + 0xe);
  puVar11 = (ushort *)((int)piVar5 + (uint)uVar1 * 2 + 0x10);
  iVar8 = *piVar3;
  if (*(short *)(iVar8 + 0x312) == 0) {
    uVar13 = (uint)*(ushort *)(piVar5 + 3);
    if (uVar13 == *puVar11) {
      uVar9 = uVar13 & 0xff00;
      if (uVar9 < 0x101) {
        if (uVar9 < 0x100) {
          if ((*(ushort *)(piVar5 + 3) & 0xff00) != 0) goto LAB_02380eb0;
          uVar10 = 1;
          uVar13 = uVar13 & 0xff;
          uVar9 = 0xb;
          in_r3 = DAT_02380fa8;
          if ((*(ushort *)(iVar7 + 0x3fc) & 1) == 0) {
            uVar6 = (ushort)(*(ushort *)(iVar8 + 800) < 0x20);
          }
          else {
            uVar6 = 2;
          }
        }
        else {
          uVar10 = 2;
          uVar13 = uVar13 & 0xff;
          uVar9 = 5;
          uVar6 = (ushort)(*(short *)(iVar8 + 800) != 0x40);
          in_r3 = DAT_02380fac;
        }
      }
      else if (uVar9 < 0x201) {
        if (uVar9 == 0x200) {
          uVar13 = uVar13 & 0xff;
          if (uVar13 < 0x40) {
            uVar6 = (ushort)(*(ushort *)(iVar8 + 800) < 0x10);
            uVar10 = 4;
            uVar9 = 0x16;
            in_r3 = DAT_02380fb0;
          }
          else if (uVar13 < 0x80) {
            uVar6 = (ushort)(*(short *)(iVar8 + 800) != 0x40);
            uVar10 = 8;
            uVar13 = uVar13 - 0x40 & 0xffff;
            uVar9 = 6;
            in_r3 = DAT_02380fb4;
          }
          else if (uVar13 < 0xc0) {
            uVar6 = (ushort)(*(ushort *)(iVar8 + 800) < 0x10);
            uVar10 = 0x10;
            uVar13 = uVar13 - 0x80 & 0xffff;
            uVar9 = 0x16;
            in_r3 = DAT_02380fb8;
          }
          else {
            uVar6 = (ushort)(*(ushort *)(iVar8 + 800) < 0x10);
            uVar10 = 0x20;
            uVar13 = uVar13 - 0xc0 & 0xffff;
            uVar9 = 6;
            in_r3 = DAT_02380fbc;
          }
        }
        else {
LAB_02380eb0:
          uVar13 = 1;
          uVar9 = 0;
          uVar10 = 0;
        }
      }
      else {
        if (uVar9 != 0x300) goto LAB_02380eb0;
        uVar10 = 0x40;
        uVar13 = uVar13 & 0xff;
        uVar9 = 10;
        in_r3 = DAT_02380fc0;
      }
      if (uVar9 < uVar13) {
        uVar6 = 3;
      }
      else if ((*(ushort *)((int)piVar5 + 0xe) < *(ushort *)(in_r3 + uVar13 * 8)) ||
              (*(ushort *)((int)piVar5 + (uint)uVar1 * 2 + 0x12) <
               *(ushort *)(in_r3 + uVar13 * 8 + 2))) {
        uVar6 = 4;
      }
      if (uVar6 == 0) {
        *(ushort *)(iVar7 + 0x3fc) = *(ushort *)(iVar7 + 0x3fc) | uVar10;
        uVar4 = (**(code **)(in_r3 + uVar13 * 8 + 4))(piVar5,puVar11);
        *(undefined2 *)((int)piVar5 + (uint)uVar1 * 2 + 0x14) = uVar4;
        sVar2 = *(short *)((int)piVar5 + (uint)uVar1 * 2 + 0x14);
        if (sVar2 == 0x80) {
          return;
        }
        if (sVar2 == 0x81) {
          *(ushort *)(iVar7 + 0x3fc) = *(ushort *)(iVar7 + 0x3fc) & ~uVar10;
          goto LAB_02380f74;
        }
      }
      else {
        *(undefined2 *)((int)piVar5 + (uint)uVar1 * 2 + 0x12) = 1;
        *(ushort *)((int)piVar5 + (uint)uVar1 * 2 + 0x14) = uVar6;
      }
    }
    else {
      *(undefined2 *)((int)piVar5 + (uint)uVar1 * 2 + 0x14) = 0xd;
    }
  }
  else {
    *(undefined2 *)((int)piVar5 + (uint)uVar1 * 2 + 0x12) = 1;
    *(undefined2 *)((int)piVar5 + (uint)uVar1 * 2 + 0x14) = 6;
  }
  *(ushort *)(iVar7 + 0x3fc) = *(ushort *)(iVar7 + 0x3fc) & ~uVar10;
  FUN_02380fc4((int *)(*DAT_02380fa4 + 0x1d4),*ppiVar12);
LAB_02380f74:
  if (*(short *)(*DAT_02380fa4 + 0x1dc) != 0) {
    FUN_02380760(2,0xb);
  }
  return;
}



void FUN_02380fc4(int *param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *DAT_02381050;
  if (*(short *)(iVar1 + 0x1d0) == 0) {
    iVar1 = FUN_023846e4(*(ushort **)(iVar1 + 0x2d8),param_2,0);
    if (iVar1 == 0) {
      FUN_02380ba4(param_1,(int **)(*DAT_02381050 + 0x1c8),param_2);
    }
    else {
      FUN_02380994(param_1,param_2);
    }
  }
  else {
    FUN_02380ba4(param_1,(int **)(iVar1 + 0x1c8),param_2);
    FUN_02380760(2,0x13);
  }
  return;
}



// WARNING: Could not reconcile some variable overlaps

void FUN_02381054(void)

{
  uint uVar1;
  ushort uVar2;
  longlong lVar3;
  ushort *puVar4;
  undefined2 *puVar5;
  undefined2 *puVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int extraout_r1;
  ushort *puVar10;
  bool bVar11;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar7 = *DAT_02381480;
  FUN_02381518();
  func_0x013708dc((uint)*DAT_02381484 + (uint)*DAT_02381484 * 0x100,*DAT_02381484);
  *(undefined2 *)(iVar7 + 0x394) = 1;
  if ((int)((uint)*(ushort *)(iVar7 + 0x30e) << 0x1d) < 0) {
    *(ushort *)(iVar7 + 0x394) = *(ushort *)(iVar7 + 0x394) | 0x20;
  }
  if (*(short *)(iVar7 + 0x308) != 0) {
    *(ushort *)(iVar7 + 0x394) = *(ushort *)(iVar7 + 0x394) | 0x10;
  }
  *(undefined2 *)(iVar7 + 0x32a) = 0;
  *DAT_02381488 = 0x8000;
  *DAT_02381490 = (short)DAT_0238148c;
  *DAT_02381494 = 0;
  *DAT_02381498 = 0;
  *DAT_0238149c = 0xf;
  func_0x01373158();
  func_0x0137c7bc();
  FUN_023830e0();
  FUN_0238348c();
  *DAT_023814a0 = 0x8000;
  *DAT_023814a4 = (short)DAT_0238148c;
  *DAT_023814ac = (short)DAT_023814a8;
  if ((*(ushort *)(*DAT_02381480 + 0x63c) & 8) == 0) {
    *DAT_023814b0 = 0;
  }
  else {
    *DAT_023814b0 = 0x400;
  }
  puVar5 = DAT_023814b4;
  *DAT_023814b4 = 0;
  puVar6 = DAT_023814b8;
  *DAT_023814b8 = 0;
  puVar10 = DAT_023814bc;
  switch(*(undefined2 *)(iVar7 + 0x324)) {
  case 0:
    *DAT_023814bc = 0x3f;
    *DAT_023814c0 = (short)DAT_0238148c;
    *DAT_023814c4 = 8;
    *puVar5 = 0;
    *puVar6 = 0;
    *DAT_023814c8 = 0;
    *DAT_023814cc = 1;
    FUN_023815d0(0x40);
    break;
  case 1:
    *DAT_023814bc = (ushort)DAT_023814d0;
    *DAT_023814ac = (short)DAT_023814a8;
    *DAT_023814c0 = (short)DAT_023814d4;
    *DAT_023814c4 = 0xd;
    *puVar5 = 0xe000;
    *DAT_023814cc = 1;
    local_20 = CONCAT22(*DAT_023814dc,*DAT_023814d8);
    local_1c = CONCAT22(*DAT_023814e4,*DAT_023814e0);
    uVar2 = *(ushort *)(iVar7 + 0x386);
    uVar1 = (uint)uVar2 * 0x400;
    uVar8 = FUN_0238eed4(local_20,local_1c,uVar1,0);
    lVar3 = (ulonglong)uVar2 * 0x400 * (ulonglong)(uVar8 + 1);
    iVar9 = (extraout_r1 + (uint)(0xfffffffe < uVar8)) * uVar1 + (int)((ulonglong)lVar3 >> 0x20);
    local_1c._2_2_ = (undefined2)((uint)iVar9 >> 0x10);
    *DAT_023814e8 = local_1c._2_2_;
    local_1c._0_2_ = (undefined2)iVar9;
    *DAT_023814ec = (undefined2)local_1c;
    local_20._2_2_ = (undefined2)((ulonglong)lVar3 >> 0x10);
    *DAT_023814f0 = local_20._2_2_;
    local_20._0_2_ = (ushort)lVar3;
    *DAT_023814f4 = (ushort)local_20 | 1;
    *DAT_023814c8 = 1;
    *DAT_023814f8 = 1;
    FUN_023815d0(0x40);
    func_0x013786d4();
    *DAT_023814fc = 2;
    break;
  case 2:
    *DAT_023814bc = (ushort)DAT_02381500;
    if ((*(ushort *)(*DAT_02381480 + 0x63c) & 0x20) != 0) {
      *puVar10 = *puVar10 | 0xc0;
    }
    puVar4 = DAT_023814b0;
    if ((*(ushort *)(*DAT_02381480 + 0x63c) & 0x20) != 0) {
      *DAT_023814b0 = *DAT_023814b0 | 0x68;
      puVar10 = puVar4;
    }
    bVar11 = (*(ushort *)(iVar7 + 0x37c) & 1) != 0;
    if (bVar11) {
      puVar10 = DAT_02381504;
    }
    if (bVar11) {
      *DAT_023814c0 = (short)puVar10;
    }
    else {
      *DAT_023814c0 = (short)DAT_02381508;
    }
    *DAT_023814c4 = 0xb;
    *DAT_023814cc = 1;
    *DAT_023814c8 = 1;
    *DAT_023814f8 = 1;
    FUN_023815d0(0x20);
    break;
  case 3:
    *DAT_023814a4 = (short)DAT_0238148c;
    *DAT_023814bc = (ushort)DAT_0238150c;
    if ((*(ushort *)(iVar7 + 0x37c) & 1) == 0) {
      *DAT_023814c0 = 1;
    }
    else {
      *DAT_023814c0 = (short)DAT_02381510;
    }
    *DAT_023814c4 = 0xb;
    *DAT_023814cc = 1;
    *DAT_023814c8 = 1;
    *DAT_023814f8 = 1;
    *DAT_02381514 = 0;
    FUN_023815d0(0x20);
    break;
  case 4:
    *DAT_023814bc = 0;
    *DAT_023814ac = 0;
    *DAT_023814cc = 1;
    FUN_023815d0(0x20);
  }
  *DAT_02381514 = 0;
  func_0x013717c8();
  *DAT_023814fc = 2;
  if (*(short *)(iVar7 + 0x326) == 1) {
    func_0x013719a0();
  }
  func_0x01373ef8();
  return;
}



void FUN_02381518(void)

{
  undefined2 uVar1;
  int iVar2;
  
  iVar2 = *DAT_023815a8;
  func_0x01370c10();
  func_0x01370a90();
  FUN_023815d0(0x20);
  *(undefined2 *)(iVar2 + 0x3bc) = 0;
  *(undefined2 *)(iVar2 + 0x32a) = 0;
  *DAT_023815ac = 0;
  *DAT_023815b0 = 0;
  *DAT_023815b4 = 0;
  *DAT_023815b8 = 0;
  *DAT_023815bc = 0;
  *DAT_023815c0 = 0;
  if (*(short *)(iVar2 + 0x324) == 1) {
    func_0x013786ac();
  }
  uVar1 = (undefined2)DAT_023815c4;
  *DAT_023815c8 = uVar1;
  *DAT_023815cc = uVar1;
  func_0x013788e8();
  func_0x013702d0();
  return;
}



void FUN_023815d0(uint param_1)

{
  int iVar1;
  
  iVar1 = *DAT_02381664;
  if (*(ushort *)(iVar1 + 800) != param_1) {
    if (*(ushort *)(iVar1 + 800) == 0x40) {
      func_0x01370a90();
    }
    if (param_1 == 0) {
      func_0x01371918();
    }
    else if (param_1 == 0x10) {
      func_0x0137198c(0);
      FUN_02381518();
      func_0x01371884();
    }
    else if (param_1 == 0x40) {
      if (*(short *)(iVar1 + 0x324) == 2) {
        func_0x01371798();
      }
      func_0x01370c2c(100,DAT_02381668);
    }
    *(short *)(iVar1 + 800) = (short)param_1;
  }
  return;
}



void FUN_0238166c(void)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  
  puVar3 = DAT_02381748;
  puVar2 = DAT_02381744;
  while( true ) {
    uVar1 = *puVar2 & *puVar3;
    if (uVar1 == 0) break;
    if ((uVar1 & 0x80) != 0) {
      FUN_0238242c();
    }
    if ((uVar1 & 0x40) != 0) {
      FUN_023824e0();
    }
    if ((uVar1 & 0x8000) != 0) {
      FUN_02381750();
    }
    if ((uVar1 & 0x4000) != 0) {
      FUN_023817dc();
    }
    if ((uVar1 & 0x2000) != 0) {
      FUN_02381ad8();
    }
    if ((uVar1 & 0x800) != 0) {
      func_0x01373060();
    }
    if ((uVar1 & 8) != 0) {
      FUN_02381b90();
    }
    if ((uVar1 & 4) != 0) {
      FUN_02381cb4();
    }
    if ((uVar1 & 1) != 0) {
      FUN_02382098();
    }
    if ((uVar1 & 0x30) != 0) {
      FUN_02381b54();
    }
    if ((uVar1 & 2) != 0) {
      FUN_02381e70();
    }
    if ((uVar1 & 0x1000) != 0) {
      FUN_02382324(1);
    }
  }
  *(uint *)PTR_NDS7_IRQ_IF_Check_Bits_0238174c =
       *(uint *)PTR_NDS7_IRQ_IF_Check_Bits_0238174c | 0x1000000;
  return;
}



void FUN_02381750(void)

{
  int iVar1;
  
  iVar1 = *DAT_023817d4;
  *DAT_023817d8 = 0x8000;
  if ((((*(short *)(iVar1 + 800) == 0x40) && (*(short *)(iVar1 + 0x396) != 0)) &&
      (*(short *)(iVar1 + 0x38a) == *(short *)(iVar1 + 0x388))) &&
     (*(short *)(iVar1 + 0x398) = *(short *)(iVar1 + 0x398) + 1,
     *(ushort *)(iVar1 + 0x396) < *(ushort *)(iVar1 + 0x398))) {
    *(undefined2 *)(iVar1 + 0x398) = 0;
    FUN_02380760(1,0xd);
  }
  *(undefined2 *)(iVar1 + 0x328) = 1;
  return;
}



void FUN_023817dc(void)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;
  
  iVar3 = *DAT_02381ab0;
  *DAT_02381ab4 = 0x4000;
  sVar1 = *(short *)(iVar3 + 0x324);
  if (sVar1 == 1) {
    iVar4 = *(int *)(iVar3 + 0x480) + (uint)*(ushort *)(iVar3 + 0x3ae);
    uVar2 = *DAT_02381ab8;
    func_0x01370938(iVar4 + 0x2c,uVar2 & 0xff);
    func_0x01370938(iVar4 + 0x2d,uVar2 >> 8);
    if (*(short *)(iVar3 + 0x326) == 1) {
      *DAT_02381abc = *(short *)(iVar3 + 0x310) + *DAT_02381abc + 1;
    }
    iVar4 = *DAT_02381ab0;
    *(ushort *)(iVar4 + 0x508) = ~*(ushort *)(iVar4 + 0x506) | *(ushort *)(iVar4 + 0x50a);
    if (((*DAT_02381ac0 & 0x18) == 0) && ((*DAT_02381ac0 & 6) != 2)) {
      *(uint *)(iVar3 + 0x48c) = *(uint *)(iVar3 + 0x48c) | 2;
    }
    else {
      *(uint *)(iVar3 + 0x48c) = *(uint *)(iVar3 + 0x48c) & 0xfffffffd;
      FUN_0238273c();
    }
  }
  else {
    if (sVar1 == 2) {
      if (*(short *)(iVar3 + 0x32a) == 0) {
        *DAT_02381abc = (short)DAT_02381ac4;
      }
      else {
        *DAT_02381abc = *(short *)(iVar3 + 0x310) + *DAT_02381abc + 1;
      }
      if (*(short *)(iVar3 + 0x332) == 2) {
        func_0x013719a0(2);
      }
    }
    else if (sVar1 != 3) {
      return;
    }
    if (*(short *)(iVar3 + 800) == 0x40) {
      bVar6 = *(short *)(iVar3 + 0x38a) == 1;
      if ((*(short *)(iVar3 + 0x32c) != 0) &&
         ((*(short *)(iVar3 + 0x38e) == 1 ||
          ((*(short *)(iVar3 + 0x38e) == 0 && (*(short *)(iVar3 + 0x38c) == 1)))))) {
        bVar6 = true;
      }
    }
    else {
      bVar6 = true;
    }
    if (bVar6) {
      *DAT_02381ac8 = *DAT_02381ac8 | 1;
    }
    else {
      *DAT_02381ac8 = *DAT_02381ac8 & 0xfffe;
    }
    if (10 < *DAT_02381acc) {
      *DAT_02381ad0 = 0;
    }
    *(short *)(iVar3 + 0x38a) = *(short *)(iVar3 + 0x38a) + -1;
    if (*(short *)(iVar3 + 0x38a) == 0) {
      *(undefined2 *)(iVar3 + 0x38a) = *(undefined2 *)(iVar3 + 0x388);
    }
    sVar1 = *(short *)(iVar3 + 0x38e);
    *(short *)(iVar3 + 0x38e) = sVar1 + -1;
    if (sVar1 == 0) {
      *(short *)(iVar3 + 0x38e) = *(short *)(iVar3 + 0x38c) + -1;
    }
    uVar5 = 0;
    do {
      iVar4 = iVar3 + 0x400 + uVar5 * 0x14;
      if ((((*(short *)(iVar3 + 0x400 + uVar5 * 0x14) != 0) &&
           (*(short *)(*(int *)(iVar4 + 0xc) + 8) == 0)) &&
          ((uint)*(ushort *)(iVar3 + 0x3a4) <
           (*(int *)(iVar3 + 0x3c0) - (uint)*(ushort *)(*(int *)(iVar4 + 0xc) + 4) & 0xffff))) &&
         ((((uint)*(ushort *)(*(int *)(iVar4 + 8) + 0xc) << 0x1c) >> 0x1e != 0 ||
          (*(short *)(*(int *)(iVar4 + 8) + 4) != 0)))) {
        func_0x01378b10(uVar5);
        **(undefined2 **)(iVar4 + 8) = 2;
        FUN_02380760(0,0xe);
        *(short *)(iVar3 + 0x4b0) = *(short *)(iVar3 + 0x4b0) + 1;
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < 2);
    *DAT_02381ad4 = 0xd;
  }
  return;
}



void FUN_02381ad8(void)

{
  int iVar1;
  
  iVar1 = *DAT_02381b44;
  *DAT_02381b48 = 0x2000;
  *DAT_02381b4c = 0xd;
  if (*(short *)(iVar1 + 0x332) == 1) {
    *(undefined2 *)(iVar1 + 0x332) = 2;
    return;
  }
  if (*(short *)(iVar1 + 0x332) != 2) {
    if (*(short *)(iVar1 + 0x324) == 2) {
      if (*(short *)(iVar1 + 800) != 0x40) {
        *DAT_02381b50 = 0;
      }
      return;
    }
    return;
  }
  *(undefined2 *)(iVar1 + 0x332) = 0;
  return;
}



void FUN_02381b54(void)

{
  func_0x01371304();
  *DAT_02381b88 = (short)DAT_02381b84;
  *DAT_02381b8c = 0x30;
  return;
}



void FUN_02381b90(void)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  short *psVar5;
  
  *DAT_02381ca0 = 8;
  if (((int)((uint)*(ushort *)(*DAT_02381ca4 + 0x30e) << 0x1b) < 0) && ((*DAT_02381ca8 & 1) == 0)) {
    *DAT_02381cac = *DAT_02381cac ^ 1;
  }
  puVar1 = DAT_02381cb0;
  iVar3 = *DAT_02381ca4;
  if ((*(ushort *)(iVar3 + 0x63c) & 8) != 0) {
    uVar4 = 0;
    do {
      if ((((*(short *)(iVar3 + 0x400 + uVar4 * 0x14) != 0) &&
           (iVar2 = *(int *)(iVar3 + 0x400 + uVar4 * 0x14 + 8),
           (*(ushort *)(iVar2 + 0xc) & 0x4000) != 0)) && ((*(ushort *)(iVar2 + 4) & 0xff) != 0)) &&
         ((psVar5 = (short *)(iVar2 + (uint)*(ushort *)(iVar2 + 10) + 5 & 0xfffffffe), *psVar5 == 0
          && (psVar5[1] == 0)))) {
        *(undefined2 *)(iVar2 + 4) = 0;
        *puVar1 = 0;
        *puVar1 = 0x8000;
        *(short *)(iVar3 + 0x3d2) = *(short *)(iVar3 + 0x3d2) + 1;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < 3);
  }
  return;
}



void FUN_02381cb4(void)

{
  ushort uVar1;
  ushort uVar2;
  int *piVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  
  piVar3 = DAT_02381e38;
  iVar5 = *DAT_02381e38;
  iVar6 = iVar5 + DAT_02381e3c;
  *DAT_02381e40 = 4;
  puVar4 = DAT_02381e50;
  uVar1 = *DAT_02381e44;
  if (((*(ushort *)(*piVar3 + 0x63c) & 8) != 0) && ((uVar1 & 0x400) != 0)) {
    uVar2 = *DAT_02381e48;
    if ((((((uVar2 & 1) == 0) || (*(short *)(iVar5 + 0x400) == 0)) &&
         (((uVar2 & 4) == 0 || (*(short *)(iVar5 + 0x414) == 0)))) &&
        (((uVar2 & 8) == 0 || (*(short *)(iVar5 + 0x428) == 0)))) && ((*DAT_02381e4c & 1) == 0)) {
      *DAT_02381e50 = 0;
      *puVar4 = 0x8000;
      *(undefined2 *)(iVar6 + 2) = 0;
    }
    else {
      uVar2 = *(ushort *)(iVar6 + 2);
      *(ushort *)(iVar6 + 2) = uVar2 + 1;
      if (0xc < uVar2) {
        *(undefined2 *)(iVar6 + 2) = 0;
        puVar4 = DAT_02381e50;
        *DAT_02381e50 = 0;
        *puVar4 = 0x8000;
        *(short *)(*DAT_02381e38 + 0x3d2) = *(short *)(*DAT_02381e38 + 0x3d2) + 1;
      }
    }
  }
  if (((*(ushort *)(*DAT_02381e38 + 0x63c) & 1) != 0) && ((uVar1 & 0x60) != 0)) {
    uVar1 = *DAT_02381e54;
    uVar7 = FUN_0238f0dc(*DAT_02381e58 - 0x4000,2);
    if (((int)uVar7 <= (int)(uint)uVar1) ||
       (uVar7 = FUN_0238f0dc(*DAT_02381e5c - 0x4000,2), (int)(uint)uVar1 < (int)uVar7)) {
      *DAT_02381e64 = *DAT_02381e60;
      uVar7 = CONCAT44(DAT_02381e68,DAT_02381e6c);
      *DAT_02381e6c = (short)DAT_02381e68;
    }
    func_0x013705f0((int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  }
  return;
}



void FUN_02381e70(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  ushort uVar6;
  
  piVar1 = DAT_02382070;
  iVar2 = *DAT_02382070;
  *DAT_02382074 = 2;
  if (*(short *)(*piVar1 + 800) == 0x12) {
    func_0x0137677c();
  }
  else {
    uVar6 = *DAT_02382078 & 0xf00;
    if (uVar6 == 0x300) {
      if ((*(uint *)(iVar2 + 0x48c) & 2) != 0) {
        FUN_0238273c();
      }
      *(int *)(*DAT_02382070 + 0x530) = *(int *)(*DAT_02382070 + 0x530) + 1;
      FUN_02380760(0,8);
    }
    else if (uVar6 == 0x800) {
      if (*(ushort *)(iVar2 + 0x49e) <= (*(ushort *)(*(int *)(iVar2 + 0x444) + 4) & 0xff)) {
        *DAT_0238207c = 2;
        *(short *)(iVar2 + 0x4aa) = *(short *)(iVar2 + 0x4aa) + 1;
      }
      *(short *)(*(int *)(iVar2 + 0x490) + 0x18) = *(short *)(*(int *)(iVar2 + 0x490) + 0x18) + 1;
    }
    else if (uVar6 == 0xb00) {
      uVar5 = (uint)*(ushort *)(iVar2 + 0x498);
      uVar4 = (uint)*(ushort *)(*(int *)(iVar2 + 0x444) + 2);
      iVar3 = *(int *)(iVar2 + 0x490) + 0x1a;
      if (((1 < uVar4) && ((int)((uint)*(ushort *)(*piVar1 + 0x30e) << 0x1b) < 0)) &&
         ((*DAT_02382080 & 1) == 0)) {
        *DAT_02382084 = *DAT_02382084 ^ 1;
      }
      if ((*(ushort *)(*DAT_02382070 + 0x63c) & 0x40) != 0) {
        while (1 < uVar4) {
          uVar4 = (uVar4 << 0xf) >> 0x10;
          if ((uVar4 & 1) != 0) {
            *(short *)(iVar3 + 6) = *(short *)(iVar3 + 6) + 1;
          }
          uVar5 = (uVar5 << 0xf) >> 0x10;
          if ((uVar5 & 1) != 0) {
            iVar3 = iVar3 + (uint)*(ushort *)(*(int *)(iVar2 + 0x490) + 0x16);
          }
        }
      }
    }
    if ((uVar6 != 0x800) && ((*DAT_02382088 & 2) == 0)) {
      if (*(short *)(iVar2 + 0x43c) != 0) {
        *DAT_0238208c = 2;
        *DAT_02382090 = 0;
        if ((*DAT_02382074 & 0x1000) == 0) {
          FUN_02382324(2);
        }
        else {
          *(short *)(iVar2 + 0x4ae) = *(short *)(iVar2 + 0x4ae) + 1;
        }
        *(short *)(iVar2 + 0x4ac) = *(short *)(iVar2 + 0x4ac) + 1;
      }
      *DAT_02382094 = 2;
    }
    FUN_02380760(0,0xe);
  }
  return;
}



void FUN_02382098(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;
  ushort *puVar4;
  ushort *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  ushort *puVar11;
  int iVar12;
  ushort uVar13;
  
  iVar7 = *DAT_023822f4;
  iVar12 = iVar7 + DAT_023822f8;
  uVar1 = *(ushort *)(iVar7 + 0x63c);
  *DAT_023822fc = 1;
  do {
    uVar10 = (uint)*(ushort *)(iVar12 + 4);
    uVar2 = *DAT_02382300;
    uVar9 = (uint)uVar2;
    if (uVar10 == uVar9) {
LAB_02382290:
      if ((uVar1 & 1) != 0) {
        uVar1 = *DAT_02382300;
        iVar7 = FUN_02382870();
        if ((iVar7 != 0) && (uVar1 == *DAT_02382300)) {
          func_0x013705ac(0x20);
        }
      }
      if (*DAT_02382320 != *DAT_02382300) {
        FUN_02380760(0,0xf);
      }
      return;
    }
    if (*DAT_02382304 < *DAT_02382304) {
      uVar13 = *DAT_02382304 >> 4 | *DAT_02382308 << 0xc;
    }
    else {
      uVar13 = *DAT_02382304 >> 4 | *DAT_02382308 << 0xc;
    }
    puVar11 = (ushort *)(DAT_0238230c + uVar10 * 2);
    puVar3 = (ushort *)FUN_02382848((uint)(puVar11 + 1));
    puVar4 = (ushort *)FUN_02382848((uint)(puVar3 + 1));
    puVar5 = (ushort *)FUN_02382848((uint)(puVar4 + 2));
    *(ushort *)(&DAT_04804000 + uVar10 * 2) =
         *(ushort *)(&DAT_04804000 + uVar10 * 2) | (*puVar3 & 0x200) << 1;
    *puVar4 = uVar13;
    uVar8 = (uint)*puVar5;
    uVar10 = (uVar8 + uVar10 * 2 + 0xf >> 2) * 2;
    if (0xfaf < uVar10) {
      uVar10 = uVar10 - (*(ushort *)(iVar7 + 0x3b2) >> 1);
    }
    if (DAT_02382310 < uVar8) {
      *puVar11 = (ushort)DAT_02382314;
      *(short *)(iVar7 + 0x3cc) = *(short *)(iVar7 + 0x3cc) + 1;
      uVar10 = uVar9;
    }
    else if (((uVar1 & 1) != 0) && (uVar10 != uVar9)) {
      uVar9 = DAT_0238230c + uVar10 * 2;
      if (uVar9 < DAT_02382318) {
        uVar13 = *(ushort *)(uVar9 + 6) & 0xff;
      }
      else {
        uVar13 = *(ushort *)((uVar9 - *(ushort *)(iVar7 + 0x3b2)) + 6);
      }
      if (((*(ushort *)(&DAT_04804000 + uVar10 * 2) & 0x7c00) != 0) ||
         (((uVar13 != 10 && (uVar13 != 0x14)) || (DAT_0238231c < uVar8)))) {
        *(short *)(iVar7 + 0x3cc) = *(short *)(iVar7 + 0x3cc) + 1;
        *puVar11 = (ushort)DAT_02382314;
        *(ushort *)(iVar12 + 4) = uVar2;
        *puVar3 = uVar2;
        goto LAB_02382290;
      }
    }
    if (((*puVar11 & 0xf) == 0xc) && (iVar6 = FUN_02382870(), iVar6 == 0)) {
      *(int *)(*DAT_023822f4 + 0x580) = *(int *)(*DAT_023822f4 + 0x580) + 1;
    }
    *(ushort *)(iVar12 + 4) = (ushort)uVar10;
    *puVar3 = (ushort)uVar10;
  } while( true );
}



void FUN_02382324(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  piVar1 = DAT_02382418;
  iVar2 = *DAT_02382418;
  *DAT_0238241c = 0x1000;
  if (*(short *)(iVar2 + 0x43c) != 0) {
    if (((*(ushort *)(*piVar1 + 0x63c) & 0x10) != 0) && (param_1 != 0)) {
      if (((*DAT_02382424 == 3) || (*DAT_02382424 == 5)) && (*DAT_02382420 == 0)) {
        iVar2 = *(int *)(iVar2 + 0x444);
        iVar4 = 0;
        for (uVar3 = (uint)*(ushort *)(iVar2 + 2); uVar3 != 0; uVar3 = (uVar3 << 0xf) >> 0x10) {
          iVar4 = iVar4 + (uVar3 & 1);
        }
        func_0x01370ab4(iVar4 * (*(ushort *)(iVar2 + 0x24) + 10) + 0xc0 +
                        (uint)*(ushort *)(iVar2 + 10) * 4 & 0xffff,DAT_02382428);
        *(short *)(*DAT_02382418 + 0x3d4) = *(short *)(*DAT_02382418 + 0x3d4) + 1;
        return;
      }
    }
    FUN_02380760(0,0x10);
  }
  return;
}



void FUN_0238242c(void)

{
  int *piVar1;
  ushort *puVar2;
  int iVar3;
  
  piVar1 = DAT_023824c8;
  iVar3 = *DAT_023824c8;
  *DAT_023824cc = 0x80;
  puVar2 = DAT_023824dc;
  if ((*(ushort *)(*piVar1 + 0x63c) & 0x20) == 0) {
    return;
  }
  if ((*DAT_023824d0 & 0xff) < 3) {
    return;
  }
  if (5 < (*DAT_023824d0 & 0xff)) {
    return;
  }
  if ((uint)*DAT_023824d4 < (DAT_023824d8 & *(uint *)(iVar3 + 0x458) >> 1)) {
    return;
  }
  if ((DAT_023824d8 & *(uint *)(iVar3 + 0x430) >> 1) < (uint)*DAT_023824d4) {
    return;
  }
  *DAT_023824dc = *DAT_023824dc | 0x80;
  *puVar2 = *puVar2 & 0xff7f;
  return;
}



void FUN_023824e0(void)

{
  short sVar1;
  int *piVar2;
  undefined2 *puVar3;
  int iVar4;
  uint uVar5;
  ushort *puVar6;
  short *psVar7;
  short *psVar8;
  uint uVar9;
  uint uVar10;
  
  piVar2 = DAT_02382700;
  iVar4 = *DAT_02382700;
  *DAT_02382704 = 0x40;
  if ((*(ushort *)(*piVar2 + 0x63c) & 0x20) == 0) {
    return;
  }
  if (*(ushort *)(iVar4 + 0x4a6) != DAT_02382708) {
    return;
  }
  if ((*DAT_0238270c & 3) != 3) {
    return;
  }
  if ((uint)*DAT_02382710 < (DAT_02382718 & *DAT_02382714 >> 1)) {
    return;
  }
  uVar9 = (uint)*DAT_0238271c;
  uVar5 = FUN_02382848(DAT_02382720 + uVar9 * 2 + 8);
  puVar6 = (ushort *)FUN_02382848(uVar5 + 4);
  if ((*puVar6 & DAT_02382724) != 0x228) {
    return;
  }
  uVar5 = FUN_02382848((uint)(puVar6 + 1));
  sVar1 = *DAT_02382728;
  while( true ) {
    uVar10 = *DAT_02382710 - uVar9 & 0xffff;
    if ((*DAT_02382710 - uVar9 & 0x8000) != 0) {
      uVar10 = uVar10 + (*(ushort *)(iVar4 + 0x3b2) >> 1) & 0xffff;
    }
    if (0xe < uVar10) break;
    if (0x40 < (ushort)(*DAT_02382728 - sVar1)) {
      return;
    }
  }
  psVar7 = (short *)(uVar5 + 8);
  uVar5 = 0;
  while( true ) {
    if (2 < uVar5) {
      puVar6 = (ushort *)FUN_02382848((uint)(psVar7 + 5));
      while( true ) {
        uVar5 = *DAT_02382710 - uVar9 & 0xffff;
        if ((*DAT_02382710 - uVar9 & 0x8000) != 0) {
          uVar5 = uVar5 + (*(ushort *)(iVar4 + 0x3b2) >> 1) & 0xffff;
        }
        if (0x14 < uVar5) break;
        if (0x70 < (ushort)(*DAT_02382728 - sVar1)) {
          return;
        }
      }
      if ((*puVar6 & *(ushort *)(iVar4 + 0x4a2)) != 0) {
        return;
      }
      *(undefined2 *)(iVar4 + 0x4a6) = *DAT_0238272c;
      *DAT_02382730 = 0x40;
      *(short *)(iVar4 + 0x3d6) = *(short *)(iVar4 + 0x3d6) + 1;
      puVar6 = DAT_02382734;
      do {
      } while ((*DAT_0238270c & 3) == 3);
      *DAT_02382734 = *DAT_02382734 | 0x40;
      *puVar6 = *puVar6 & 0xffbf;
      puVar3 = DAT_02382738;
      *DAT_02382738 = 8;
      *puVar3 = 0;
      func_0x01372ffc();
      return;
    }
    psVar8 = (short *)FUN_02382848((uint)psVar7);
    psVar7 = psVar8 + 1;
    if (*psVar8 != *(short *)(iVar4 + uVar5 * 2 + 0x37c)) break;
    uVar5 = uVar5 + 1;
  }
  return;
}



void FUN_0238273c(void)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = *DAT_023827d8;
  bVar2 = false;
  func_0x01378b10(1);
  func_0x01378b10(0);
  if ((*(short *)(iVar1 + 0x414) != 0) && (bVar2 = **(short **)(iVar1 + 0x41c) != 0, !bVar2)) {
    *(ushort *)(iVar1 + 0x414) = (ushort)bVar2;
  }
  if (*(short *)(iVar1 + 0x400) != 0) {
    if (**(short **)(iVar1 + 0x408) == 0) {
      *(short *)(iVar1 + 0x400) = 0;
    }
    else {
      bVar2 = true;
    }
  }
  if (bVar2) {
    FUN_02380760(0,0xe);
  }
  FUN_02380760(0,0x14);
  return;
}



void FUN_023827dc(void)

{
  short sVar1;
  short *psVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = FUN_023838dc(0x1000000);
  psVar2 = DAT_02382840;
  sVar1 = *DAT_02382840;
  *DAT_02382844 = 0x1000;
  iVar4 = 100;
  while ((iVar4 != 0 && (sVar1 == *psVar2))) {
    iVar4 = iVar4 + -1;
  }
  *DAT_02382844 = 0;
  FUN_02382324(0);
  FUN_02383918(uVar3);
  return;
}



uint FUN_02382848(uint param_1)

{
  if (DAT_02382868 <= param_1) {
    param_1 = param_1 - *(ushort *)(*DAT_0238286c + 0x3b2);
  }
  return param_1;
}



undefined4 FUN_02382870(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = *DAT_023828b0;
  iVar2 = func_0x01372f94(iVar1 + 0x450);
  if (iVar2 == 0) {
    iVar1 = func_0x01372f94(iVar1 + 0x464);
    if (iVar1 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}



void FUN_023828b4(void)

{
  if (*(short *)(*DAT_02382904 + 0x3bc) != 0) {
    func_0x01378234();
  }
  if ((int)((uint)*(ushort *)(*DAT_02382904 + 0x30e) << 0x19) < 0) {
    func_0x01374114();
  }
  return;
}



void FUN_02382908(void)

{
  ushort uVar1;
  undefined2 *puVar2;
  int iVar3;
  ushort *puVar4;
  short *psVar5;
  int iVar6;
  int iVar7;
  short *psVar8;
  
  iVar3 = *DAT_02382afc;
  iVar7 = 2;
  do {
    psVar5 = (short *)(iVar7 * 0x14 + iVar3 + 0x400);
    puVar4 = (ushort *)(DAT_02382b00 + iVar7 * 4);
    if (((*(ushort *)(&DAT_048080a0 + iVar7 * 4) & 0x8000) == 0) && (*psVar5 != 0)) {
      if (*(int *)(psVar5 + 6) == 0) {
        psVar5[2] = psVar5[2] + 1;
        (**(code **)(psVar5 + 8))(*(undefined4 *)(psVar5 + 4),3);
      }
      else {
        *(undefined2 *)(*(int *)(psVar5 + 6) + 8) = **(undefined2 **)(psVar5 + 4);
        *(undefined2 *)(*(int *)(psVar5 + 6) + 0x14) = *(undefined2 *)(*(int *)(psVar5 + 4) + 0xc);
        puVar2 = DAT_02382b04;
        iVar6 = *(int *)(psVar5 + 4);
        if ((*(ushort *)(iVar6 + 0xc) & 0x4000) == 0) {
          *(ushort *)(*(int *)(psVar5 + 6) + 0xc) = *(ushort *)(iVar6 + 4) & 0xff;
        }
        else {
          if ((((*(ushort *)(*DAT_02382afc + 0x63c) & 8) != 0) &&
              (psVar8 = (short *)(iVar6 + (uint)*(ushort *)(iVar6 + 10) + 5 & 0xfffffffe),
              *psVar8 == 0)) && (psVar8[1] == 0)) {
            iVar6 = *(int *)(iVar3 + 0x3c0);
            uVar1 = *(ushort *)(*(int *)(psVar5 + 6) + 4);
            *DAT_02382b04 = 0;
            *puVar2 = 0x8000;
            *(short *)(iVar3 + 0x3d2) = *(short *)(iVar3 + 0x3d2) + 1;
            if ((uint)*(ushort *)(iVar3 + 0x3a4) < (iVar6 - (uint)uVar1 & 0xffff)) {
              *(undefined2 *)(*(int *)(psVar5 + 6) + 8) = 2;
              psVar5[2] = psVar5[2] + 1;
              *(short *)(iVar3 + 0x4b0) = *(short *)(iVar3 + 0x4b0) + 1;
              (**(code **)(psVar5 + 8))(*(undefined4 *)(psVar5 + 6),1);
            }
            else {
              *(undefined2 *)(*(int *)(psVar5 + 6) + 0xc) = 0;
              *puVar4 = *puVar4 | 0x8000;
            }
            goto LAB_02382ae8;
          }
          *(ushort *)(*(int *)(psVar5 + 6) + 0xc) =
               *(short *)(*(int *)(psVar5 + 6) + 0xc) + (*(ushort *)(iVar6 + 4) & 0xff);
        }
        psVar5[2] = psVar5[2] + 1;
        (**(code **)(psVar5 + 8))(*(undefined4 *)(psVar5 + 6),2);
      }
    }
LAB_02382ae8:
    iVar7 = iVar7 + -1;
    if (iVar7 < 0) {
      return;
    }
  } while( true );
}



void FUN_02382b08(void)

{
  ushort uVar1;
  int *piVar2;
  ushort *puVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  ushort *puVar7;
  int iVar8;
  int iVar9;
  int local_48;
  uint local_2c;
  
  piVar2 = DAT_02382ea8;
  iVar5 = *DAT_02382ea8;
  iVar8 = iVar5 + DAT_02382eac;
  local_48 = 0;
  local_2c = 0;
  do {
    while( true ) {
      while( true ) {
        uVar6 = (uint)*DAT_02382eb0;
        if (uVar6 == *(ushort *)(iVar8 + 4)) {
          return;
        }
        puVar7 = (ushort *)(DAT_02382eb4 + uVar6 * 2);
        puVar3 = (ushort *)FUN_02382848((uint)(puVar7 + 1));
        uVar1 = *puVar3;
        if (*(ushort *)(&DAT_04804000 + uVar6 * 2) != DAT_02382eb8) break;
        *DAT_02382eb0 = uVar1;
      }
      puVar3 = (ushort *)FUN_02382848((uint)(puVar7 + 4));
      piVar4 = FUN_0238306c(puVar7,(uint)*puVar3);
      *DAT_02382eb0 = uVar1;
      if (piVar4 != (int *)0x0) break;
      if ((*puVar7 & 0xf) == 0xc) {
        func_0x013705ac(0x10);
      }
      else {
        func_0x013705ac(8);
      }
    }
    if (((*(ushort *)(*piVar2 + 0x63c) & 8) != 0) && ((*(ushort *)(piVar4 + 5) & 0x4000) != 0)) {
      *(undefined2 *)(iVar8 + 2) = 0;
    }
    iVar9 = 1;
    if ((*(ushort *)(piVar4 + 2) & 0x200) != 0) {
      if (((int)((uint)*(ushort *)(piVar4 + 5) << 0x15) < 0) ||
         ((*(ushort *)((int)piVar4 + 0x2a) & 0xf) != 0)) {
        FUN_02380ba4((int *)(iVar5 + 0x15c),(int **)(iVar5 + 0x1bc),piVar4 + -4);
        FUN_02380760(2,9);
        iVar9 = local_48;
      }
      goto switchD_02382c9c_caseD_10;
    }
    switch(*(ushort *)(piVar4 + 2) & 0xf) {
    case 0:
      if ((*(ushort *)(piVar4 + 5) & 0xf) == 0) {
        iVar9 = 0;
        FUN_02380ba4((int *)(iVar5 + 0x15c),(int **)(iVar5 + 0x1b0),piVar4 + -4);
        FUN_02380760(1,7);
      }
      break;
    case 1:
      if (*(short *)(piVar4 + 5) == 0x80) {
        func_0x0137b930(piVar4);
      }
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      if ((*(ushort *)(piVar4 + 5) & DAT_02382ebc) == 0xa4) {
        iVar9 = 0;
        FUN_02380ba4((int *)(iVar5 + 0x15c),(int **)(iVar5 + 0x1b0),piVar4 + -4);
        FUN_02380760(1,7);
      }
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      if ((*(ushort *)(piVar4 + 5) & 0xf) == 8) {
        iVar9 = 0;
        FUN_02380ba4((int *)(iVar5 + 0x15c),(int **)(iVar5 + 0x198),piVar4 + -4);
        FUN_02380760(2,6);
      }
      break;
    case 9:
      break;
    case 10:
      break;
    case 0xb:
      break;
    case 0xc:
      if ((*(ushort *)(piVar4 + 5) & DAT_02382ebc) == 0x228) {
        if (*(short *)(*piVar2 + 0x328) == 0) {
          *DAT_02382ec4 = 1;
        }
        *(int *)(*piVar2 + 0x584) = *(int *)(*piVar2 + 0x584) + 1;
        iVar9 = func_0x0137c2d0(piVar4);
      }
      break;
    case 0xd:
      if ((*(ushort *)(piVar4 + 5) & DAT_02382ebc) == 0x218) {
        *(int *)(*piVar2 + 0x588) = *(int *)(*piVar2 + 0x588) + 1;
        iVar9 = func_0x0137c024(piVar4);
      }
      break;
    case 0xe:
      goto LAB_02382d98;
    case 0xf:
LAB_02382d98:
      if ((*(ushort *)(piVar4 + 5) & DAT_02382ec0) == 0x118) {
        func_0x0137c108(piVar4);
      }
    }
switchD_02382c9c_caseD_10:
    if (iVar9 != 0) {
      FUN_02380b20((int *)(iVar5 + 0x15c),piVar4 + -4);
    }
    uVar6 = local_2c;
    if ((*(ushort *)(*piVar2 + 0x63c) & 1) != 0) {
      do {
        puVar3 = puVar7;
        if (DAT_02382ec8 <= puVar7) {
          puVar3 = (ushort *)((int)puVar7 - (uint)*(ushort *)(*piVar2 + 0x3b2));
        }
        puVar7 = puVar3 + 1;
        *puVar3 = (ushort)DAT_02382eb8;
        uVar6 = uVar6 + 1;
      } while (uVar6 < 7);
    }
  } while( true );
}



void FUN_02382ecc(void)

{
  ushort uVar1;
  int iVar2;
  
  iVar2 = *DAT_02382fac;
  if (*(short *)(iVar2 + 0x43c) != 0) {
    if (*(short *)(*(int *)(iVar2 + 0x490) + 0x10) != *(short *)(*(int *)(iVar2 + 0x444) + 2)) {
      FUN_02382b08();
    }
    uVar1 = *(ushort *)(*(int *)(iVar2 + 0x444) + 4);
    if ((uVar1 & 0xff) == 0) {
      *(int *)(*DAT_02382fac + 0x578) = *(int *)(*DAT_02382fac + 0x578) + 1;
    }
    else {
      *(uint *)(*DAT_02382fac + 0x578) = *(int *)(*DAT_02382fac + 0x578) + (uVar1 & 0xff);
    }
    *(short *)(iVar2 + 0x440) = *(short *)(iVar2 + 0x440) + 1;
    *(ushort *)(*(int *)(iVar2 + 0x490) + 0x12) =
         *(ushort *)(*(int *)(iVar2 + 0x490) + 0x10) ^ *(ushort *)(*(int *)(iVar2 + 0x444) + 2);
    *(undefined2 *)(iVar2 + 0x4a0) = *(undefined2 *)(*(int *)(iVar2 + 0x490) + 0x10);
    *(undefined2 *)(iVar2 + 0x43c) = 0;
    if (*(short *)(*DAT_02382fac + 0x3be) != 0) {
      func_0x013717c8();
    }
    FUN_02380fc4((int *)(*DAT_02382fac + 0x15c),*(int **)(iVar2 + 0x490));
  }
  return;
}



void FUN_02382fb0(void)

{
  int iVar1;
  
  iVar1 = *DAT_02383060;
  if ((*DAT_02383064 == 0) && (*(short *)(iVar1 + 0x188) != 0)) {
    *DAT_02383068 = 8;
    func_0x013796f8();
  }
  else {
    if ((*(ushort *)(iVar1 + 0x506) & ~*(ushort *)(iVar1 + 0x50a)) == 0) {
      *DAT_02383068 = 8;
      if (*(short *)(iVar1 + 0x188) != 0) {
        func_0x013796f8();
      }
    }
    *DAT_02383068 = 5;
    if (*(short *)(iVar1 + 0x17c) != 0) {
      func_0x013797b8(1);
    }
    if (*(short *)(iVar1 + 0x170) != 0) {
      func_0x013797b8(0);
    }
  }
  return;
}



int * FUN_0238306c(undefined4 param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = FUN_02380a78((int **)(*DAT_023830dc + 0x15c),param_2 + 0x22);
  if (piVar1 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = piVar1 + 4;
    func_0x01370a0c(piVar1 + 6,param_1,param_2 + 0xc);
    *(short *)((int)piVar1 + 0x16) = (short)param_2 + -0x18;
    *(ushort *)((int)piVar1 + 0x1e) =
         *(ushort *)((int)piVar1 + 0x1e) & 0xff |
         (ushort)(((*(ushort *)((int)piVar1 + 0x22) & 0xff) << 0x10) >> 8);
  }
  return piVar2;
}



void FUN_023830e0(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = *DAT_023833d8;
  FUN_023860f4(0,(undefined4 *)(iVar4 + 0x400),0xb4);
  *(undefined2 *)(undefined4 *)(iVar4 + 0x400) = 0;
  *(undefined4 *)(iVar4 + 0x40c) = 0;
  *(undefined2 *)(iVar4 + 0x414) = 0;
  *(undefined4 *)(iVar4 + 0x420) = 0;
  *(undefined2 *)(iVar4 + 0x428) = 0;
  *(undefined4 *)(iVar4 + 0x434) = 0;
  uVar1 = (undefined2)DAT_023833dc;
  *(undefined2 *)(iVar4 + 0x4a4) = uVar1;
  *(undefined2 *)(iVar4 + 0x4a6) = uVar1;
  switch(*(undefined2 *)(iVar4 + 0x324)) {
  case 0:
    *(undefined4 *)(iVar4 + 0x408) = DAT_023833e0;
    *(undefined4 *)(iVar4 + 0x41c) = DAT_023833e4;
    *(undefined4 *)(iVar4 + 0x430) = DAT_023833e8;
    *(undefined4 *)(iVar4 + 0x410) = DAT_023833ec;
    *(undefined4 *)(iVar4 + 0x424) = DAT_023833f0;
    *(undefined4 *)(iVar4 + 0x438) = DAT_023833f4;
    uVar1 = (undefined2)DAT_023833f8;
    *DAT_023833fc = uVar1;
    uVar2 = (undefined2)DAT_02383400;
    *DAT_02383404 = uVar2;
    *DAT_02383408 = uVar1;
    *DAT_0238340c = uVar2;
    *DAT_02383410 = uVar1;
    *DAT_02383414 = uVar2;
    *(undefined2 *)(iVar4 + 0x3a2) = 8;
    *DAT_02383418 = 1;
    break;
  case 1:
    *(undefined4 *)(iVar4 + 0x408) = DAT_0238341c;
    *(undefined4 *)(iVar4 + 0x41c) = DAT_02383420;
    *(undefined4 *)(iVar4 + 0x430) = DAT_02383424;
    *(undefined4 *)(iVar4 + 0x410) = DAT_023833ec;
    *(undefined4 *)(iVar4 + 0x424) = DAT_023833f0;
    *(undefined4 *)(iVar4 + 0x438) = DAT_02383428;
    uVar3 = DAT_0238342c;
    *(undefined4 *)(iVar4 + 0x480) = DAT_0238342c;
    *(undefined4 *)(iVar4 + 0x444) = DAT_023833e8;
    uVar1 = (undefined2)DAT_023833f8;
    *DAT_02383430 = uVar1;
    uVar2 = (undefined2)DAT_02383400;
    *DAT_02383434 = uVar2;
    *DAT_02383438 = uVar1;
    *DAT_0238343c = uVar2;
    *DAT_02383440 = uVar1;
    *DAT_02383444 = uVar2;
    *DAT_02383448 = uVar1;
    *DAT_0238344c = uVar2;
    *DAT_02383450 = uVar1;
    *DAT_02383454 = uVar2;
    *(undefined2 *)(iVar4 + 0x3a2) = 0x208;
    *(undefined4 *)(iVar4 + 0x480) = uVar3;
    func_0x01378340();
    break;
  case 2:
    *(undefined4 *)(iVar4 + 0x408) = DAT_02383458;
    *(undefined4 *)(iVar4 + 0x41c) = DAT_0238345c;
    *(undefined4 *)(iVar4 + 0x430) = DAT_02383460;
    *(undefined4 *)(iVar4 + 0x410) = DAT_023833ec;
    *(undefined4 *)(iVar4 + 0x424) = DAT_023833f0;
    *(undefined4 *)(iVar4 + 0x438) = DAT_023833f4;
    *(undefined4 *)(iVar4 + 0x458) = DAT_023833e8;
    *(undefined2 **)(iVar4 + 0x46c) = DAT_02383430;
    uVar1 = (undefined2)DAT_023833f8;
    *DAT_02383464 = uVar1;
    uVar2 = (undefined2)DAT_02383400;
    *DAT_02383468 = uVar2;
    *DAT_0238346c = uVar1;
    *DAT_02383470 = uVar2;
    *DAT_02383474 = uVar1;
    *DAT_02383478 = uVar2;
    *DAT_0238347c = uVar1;
    *DAT_02383480 = uVar2;
    *DAT_02383484 = uVar1;
    *DAT_02383488 = uVar2;
    *(undefined2 *)(iVar4 + 0x3a2) = 0x108;
    *DAT_02383418 = 0xd;
    break;
  case 3:
    *(undefined4 *)(iVar4 + 0x408) = DAT_023833e0;
    *(undefined4 *)(iVar4 + 0x41c) = DAT_023833e4;
    *(undefined4 *)(iVar4 + 0x430) = DAT_023833e8;
    *(undefined4 *)(iVar4 + 0x410) = DAT_023833ec;
    *(undefined4 *)(iVar4 + 0x424) = DAT_023833f0;
    *(undefined4 *)(iVar4 + 0x438) = DAT_023833f4;
    uVar1 = (undefined2)DAT_023833f8;
    *DAT_023833fc = uVar1;
    uVar2 = (undefined2)DAT_02383400;
    *DAT_02383404 = uVar2;
    *DAT_02383408 = uVar1;
    *DAT_0238340c = uVar2;
    *DAT_02383410 = uVar1;
    *DAT_02383414 = uVar2;
    *(undefined2 *)(iVar4 + 0x3a2) = 0x108;
    *DAT_02383418 = 0xd;
  }
  if (*(short *)(iVar4 + 0x308) != 0) {
    *(ushort *)(iVar4 + 0x3a2) = *(ushort *)(iVar4 + 0x3a2) | 0x4000;
  }
  return;
}



void FUN_0238348c(void)

{
  undefined2 uVar1;
  int iVar2;
  int unaff_r4;
  undefined4 *puVar3;
  
  iVar2 = *DAT_02383584;
  puVar3 = (undefined4 *)(iVar2 + DAT_02383588);
  FUN_023860f4(0,puVar3,0x50);
  *DAT_0238358c = 0x8000;
  switch(*(undefined2 *)(*DAT_02383584 + 0x324)) {
  case 0:
    unaff_r4 = DAT_02383590;
    break;
  case 1:
    unaff_r4 = DAT_02383594;
    break;
  case 2:
    unaff_r4 = DAT_02383598;
    break;
  case 3:
    unaff_r4 = DAT_02383590;
  }
  *DAT_023835a0 = (short)unaff_r4 + (short)DAT_0238359c;
  uVar1 = (undefined2)((uint)(unaff_r4 << 0xf) >> 0x10);
  *DAT_023835a4 = uVar1;
  *DAT_023835ac = (short)DAT_023835a8;
  *DAT_023835b0 = uVar1;
  *(undefined2 *)(puVar3 + 1) = uVar1;
  *(short *)puVar3 = (short)DAT_023835b4;
  *(short *)(iVar2 + 0x3b2) = (short)DAT_023835b8 - (short)unaff_r4;
  *DAT_023835c0 = (short)DAT_023835bc;
  *DAT_0238358c = (short)DAT_023835c4;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_023835c8(void)

{
  uint uVar1;
  uint uVar2;
  
  if (_REG_IME == 0) {
    return;
  }
  uVar2 = _REG_IE & _REG_IF;
  if (uVar2 != 0) {
    for (uVar1 = 0; _REG_IF = uVar2 & 1 << (uVar1 & 0xff), _REG_IF == 0; uVar1 = uVar1 + 1) {
    }
                    // WARNING: Could not recover jumptable at 0x02383610. Too many branches
                    // WARNING: Treating indirect jump as call
    (**(code **)(DAT_02383614 + uVar1 * 4))();
    return;
  }
  return;
}



undefined4 FUN_023838a8(undefined4 param_1)

{
  undefined2 uVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  puVar2 = PTR_REG_IME_023838d4;
  uVar1 = *(undefined2 *)PTR_REG_IME_023838d4;
  *(undefined2 *)PTR_REG_IME_023838d4 = 0;
  uVar3 = *(undefined4 *)PTR_REG_IF_023838d8;
  *(undefined4 *)PTR_REG_IF_023838d8 = param_1;
  *(undefined2 *)puVar2 = uVar1;
  return uVar3;
}



uint FUN_023838dc(uint param_1)

{
  undefined2 uVar1;
  undefined *puVar2;
  uint uVar3;
  
  puVar2 = PTR_REG_IME_02383910;
  uVar1 = *(undefined2 *)PTR_REG_IME_02383910;
  *(undefined2 *)PTR_REG_IME_02383910 = 0;
  uVar3 = *(uint *)PTR_REG_IE_02383914;
  *(uint *)PTR_REG_IE_02383914 = uVar3 & ~param_1;
  *(undefined2 *)puVar2 = uVar1;
  return uVar3;
}



uint FUN_02383918(uint param_1)

{
  undefined2 uVar1;
  undefined *puVar2;
  uint uVar3;
  
  puVar2 = PTR_REG_IME_02383948;
  uVar1 = *(undefined2 *)PTR_REG_IME_02383948;
  *(undefined2 *)PTR_REG_IME_02383948 = 0;
  uVar3 = *(uint *)PTR_REG_IE_0238394c;
  *(uint *)PTR_REG_IE_0238394c = uVar3 | param_1;
  *(undefined2 *)puVar2 = uVar1;
  return uVar3;
}



undefined4 FUN_02383950(undefined4 param_1)

{
  undefined2 uVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  puVar2 = PTR_REG_IME_0238397c;
  uVar1 = *(undefined2 *)PTR_REG_IME_0238397c;
  *(undefined2 *)PTR_REG_IME_0238397c = 0;
  uVar3 = *(undefined4 *)PTR_REG_IE_02383980;
  *(undefined4 *)PTR_REG_IE_02383980 = param_1;
  *(undefined2 *)puVar2 = uVar1;
  return uVar3;
}



void FUN_02383984(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = param_1 * 0xc;
  *(undefined4 *)(DAT_023839c4 + iVar1) = param_2;
  *(undefined4 *)(DAT_023839c8 + iVar1) = param_3;
  FUN_02383918(1 << (param_1 + 3U & 0xff));
  *(undefined4 *)(DAT_023839cc + iVar1) = 1;
  return;
}



void FUN_023839d0(uint param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  
  iVar3 = DAT_02383a74;
  puVar2 = DAT_02383a70;
  iVar1 = DAT_02383a6c;
  iVar5 = 0;
  do {
    if ((param_1 & 1) != 0) {
      if ((iVar5 < 8) || (0xb < iVar5)) {
        if ((iVar5 < 3) || (6 < iVar5)) {
          puVar4 = puVar2;
          if (iVar5 != 0) {
            *(undefined4 *)(iVar1 + iVar5 * 4) = param_2;
            puVar4 = (undefined4 *)0x0;
          }
        }
        else {
          puVar4 = (undefined4 *)((iVar5 + 1) * 0xc + iVar3);
        }
      }
      else {
        puVar4 = (undefined4 *)((iVar5 + -8) * 0xc + iVar3);
      }
      if (puVar4 != (undefined4 *)0x0) {
        *puVar4 = param_2;
        puVar4[2] = 0;
        puVar4[1] = 1;
      }
    }
    param_1 = param_1 >> 1;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x19);
  return;
}



void FUN_02383a78(void)

{
  *DAT_02383a90 = 0;
  *DAT_02383a94 = 0;
  return;
}



void thunk_EXT_FUN_037fba3c(void)

{
                    // WARNING: Could not recover jumptable at 0x02383a9c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02383aa0)();
  return;
}



int FUN_02383aa4(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  
  uVar3 = 0;
  uVar1 = 0x80000000;
  while (((*DAT_02383b34 & uVar1) == 0 && (uVar3 = uVar3 + 1, uVar3 != 0x20))) {
    uVar1 = uVar1 >> 1;
  }
  if (uVar3 == 0x20) {
    puVar4 = DAT_02383b34 + 1;
    uVar3 = 0;
    uVar1 = 0x80000000;
    while (((*puVar4 & uVar1) == 0 && (uVar3 = uVar3 + 1, uVar3 != 0x20))) {
      uVar1 = uVar1 >> 1;
    }
    if (uVar3 == 0x20) {
      return DAT_02383b38;
    }
    iVar2 = 0xa0;
  }
  else {
    iVar2 = 0x80;
    puVar4 = DAT_02383b34;
  }
  *puVar4 = *puVar4 & ~(0x80000000U >> (uVar3 & 0xff));
  return iVar2 + uVar3;
}



void FUN_02383b3c(int param_1)

{
  uint *puVar1;
  uint uVar2;
  
  if (param_1 + -0xa0 < 0) {
    uVar2 = param_1 - 0x80;
    puVar1 = DAT_02383b68;
  }
  else {
    uVar2 = param_1 - 0xa0;
    puVar1 = DAT_02383b68 + 1;
  }
  *puVar1 = *puVar1 | 0x80000000U >> (uVar2 & 0xff);
  return;
}



void FUN_02383b6c(void)

{
                    // WARNING: Could not recover jumptable at 0x02383b74. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02383b78)(0x1000);
  return;
}



undefined2 FUN_02383b7c(int param_1)

{
  return *(undefined2 *)(param_1 + 4);
}



void FUN_02383b8c(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02383b9c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02383ba8)(param_1,DAT_02383ba0,DAT_02383ba4,1);
  return;
}



void FUN_02383bcc(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02383bdc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02383be8)(param_1,DAT_02383be0,DAT_02383be4,1);
  return;
}



int FUN_02383bec(undefined4 param_1,undefined4 *param_2,undefined *param_3,int param_4)

{
  int iVar1;
  
  if (param_4 == 0) {
    FUN_02385e18();
  }
  else {
    FUN_02385e44();
  }
  iVar1 = FUN_02386330(param_1,param_2);
  if (iVar1 == 0) {
    if (param_3 != (undefined *)0x0) {
      (*(code *)param_3)();
    }
    *(short *)(param_2 + 1) = (short)param_1;
  }
  if (param_4 == 0) {
    FUN_02385e2c();
  }
  else {
    FUN_02385e58();
  }
  return iVar1;
}



undefined4 FUN_02383c70(uint param_1,undefined4 *param_2,undefined *param_3,int param_4)

{
  undefined4 uVar1;
  longlong lVar2;
  
  if (param_1 == *(ushort *)(param_2 + 1)) {
    if (param_4 == 0) {
      lVar2 = FUN_02385e18();
      uVar1 = (undefined4)((ulonglong)lVar2 >> 0x20);
    }
    else {
      lVar2 = FUN_02385e44();
      uVar1 = (undefined4)((ulonglong)lVar2 >> 0x20);
    }
    *(undefined2 *)(param_2 + 1) = 0;
    if (param_3 != (undefined *)0x0) {
      (*(code *)param_3)(0,uVar1);
    }
    *param_2 = 0;
    if (param_4 == 0) {
      FUN_02385e2c();
    }
    else {
      FUN_02385e58();
    }
    uVar1 = 0;
  }
  else {
    uVar1 = 0xfffffffe;
  }
  return uVar1;
}



void FUN_02383cfc(undefined4 param_1,undefined4 *param_2,undefined *param_3,int param_4)

{
  int iVar1;
  
  while (iVar1 = FUN_02383bec(param_1,param_2,param_3,param_4), 0 < iVar1) {
    FUN_02383b6c();
  }
  return;
}



void FUN_02383d44(void)

{
  int iVar1;
  
  if (*DAT_02383dac == 0) {
    *DAT_02383dac = 1;
    iVar1 = DAT_02383db0;
    *(undefined2 *)(DAT_02383db0 + 6) = 0;
    while (*(short *)(iVar1 + 4) != 0x7f) {
      FUN_02383b6c();
    }
    *DAT_02383db4 = 0xffffffff;
    *DAT_02383db8 = 0xffff0000;
    *(undefined2 *)(iVar1 + 6) = 0xbf;
  }
  return;
}



int FUN_02383dc0(void)

{
  int iVar1;
  int iVar2;
  
  FUN_02385e18();
  iVar1 = *DAT_02383df4;
  iVar2 = 0;
  if (iVar1 != 0) {
    *DAT_02383df4 = iVar1 + -1;
    iVar2 = iVar1;
  }
  FUN_02385e2c();
  return iVar2;
}



int FUN_02383df8(void)

{
  int iVar1;
  int unaff_r4;
  
  FUN_02385e18();
  iVar1 = *DAT_02383e2c;
  if (iVar1 != -1) {
    *DAT_02383e2c = iVar1 + 1;
    unaff_r4 = iVar1;
  }
  FUN_02385e2c();
  return unaff_r4;
}



undefined4 FUN_02383e30(undefined4 param_1)

{
  undefined4 uVar1;
  
  FUN_02385e18();
  uVar1 = *(undefined4 *)(DAT_02383e60 + 0x10);
  *(undefined4 *)(DAT_02383e60 + 0x10) = param_1;
  FUN_02385e2c();
  return uVar1;
}



void FUN_02383e70(int param_1)

{
  undefined4 extraout_r1;
  uint uVar1;
  int aiStack_3c [12];
  
  FUN_023856bc(aiStack_3c);
  FUN_02385e18();
  uVar1 = 0;
  FUN_02385518(aiStack_3c,(uint)(param_1 * DAT_02383ed8) >> 6,0,DAT_02383edc,**DAT_02383ed4);
  FUN_02384134((ushort *)0x0,extraout_r1,uVar1);
  FUN_02385e2c();
  return;
}



undefined4 FUN_02383ee0(int param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  
  FUN_02385e18();
  iVar2 = 0;
  for (iVar3 = *(int *)(DAT_02383f88 + 0xc); (iVar3 != 0 && (iVar3 != param_1));
      iVar3 = *(int *)(iVar3 + 0x4c)) {
    iVar2 = iVar3;
  }
  if ((iVar3 == 0) || (iVar3 == DAT_02383f8c)) {
    FUN_02385e2c();
    uVar1 = 0;
  }
  else {
    if (*(int *)(iVar3 + 0x54) != param_2) {
      if (iVar2 == 0) {
        *(undefined4 *)(DAT_02383f88 + 0xc) = *(undefined4 *)(param_1 + 0x4c);
      }
      else {
        *(undefined4 *)(iVar2 + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
      }
      *(int *)(param_1 + 0x54) = param_2;
      uVar4 = FUN_0238446c(param_1);
      FUN_02383f90((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),param_3,param_4);
    }
    FUN_02385e2c();
    uVar1 = 1;
  }
  return uVar1;
}



void FUN_02383f90(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined2 *puVar1;
  int iVar2;
  int *piVar3;
  code *pcVar4;
  int *piVar5;
  undefined8 uVar6;
  
  puVar1 = DAT_02384054;
  if (*DAT_02384058 == 0) {
    if ((DAT_02384054[2] == 0) && (iVar2 = FUN_02385e70(), iVar2 != 0x12)) {
      piVar5 = *(int **)*DAT_0238405c;
      uVar6 = FUN_02384064();
      piVar3 = (int *)uVar6;
      if ((piVar5 != piVar3) &&
         ((piVar3 != (int *)0x0 &&
          (iVar2 = FUN_0238456c(piVar5,(int)((ulonglong)uVar6 >> 0x20),param_3,param_4), iVar2 == 0)
          ))) {
        if (*DAT_02384060 != (code *)0x0) {
          (**DAT_02384060)(piVar5,piVar3);
        }
        pcVar4 = *(code **)(puVar1 + 8);
        if (pcVar4 != (code *)0x0) {
          (*pcVar4)(piVar5,piVar3);
        }
        *(int **)(DAT_02384054 + 4) = piVar3;
        FUN_023845a0((int)piVar3);
      }
    }
    else {
      *puVar1 = 1;
    }
  }
  return;
}



void FUN_02384064(void)

{
  int iVar1;
  
  iVar1 = *(int *)(DAT_0238408c + 0xc);
  while( true ) {
    if (iVar1 == 0) {
      return;
    }
    if (*(int *)(iVar1 + 0x48) == 1) break;
    iVar1 = *(int *)(iVar1 + 0x4c);
  }
  return;
}



void FUN_02384090(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  longlong lVar1;
  
  lVar1 = FUN_02385e18();
  *(undefined4 *)(param_1 + 0x48) = 1;
  FUN_02383f90(1,(int)((ulonglong)lVar1 >> 0x20),param_3,param_4);
  FUN_02385e2c();
  return;
}



void FUN_023840c4(ushort *param_1)

{
  int iVar1;
  uint uVar2;
  
  FUN_02385e18();
  uVar2 = (uint)*param_1;
  if (uVar2 != 0) {
    for (iVar1 = *(int *)(DAT_02384130 + 0xc); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x4c)) {
      if ((uVar2 & 1 << (*(uint *)(iVar1 + 0x50) & 0xff)) != 0) {
        *(undefined4 *)(iVar1 + 0x48) = 1;
      }
    }
    *param_1 = 0;
    FUN_02383f90(0,1,0,uVar2);
  }
  FUN_02385e2c();
  return;
}



void FUN_02384134(ushort *param_1,undefined4 param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  longlong lVar3;
  
  lVar3 = FUN_02385e18();
  uVar1 = (undefined4)((ulonglong)lVar3 >> 0x20);
  iVar2 = **DAT_02384198;
  if (param_1 != (ushort *)0x0) {
    param_3 = (uint)*param_1;
    uVar1 = 1;
    *param_1 = *param_1 | (ushort)(1 << (*(uint *)(iVar2 + 0x50) & 0xff));
  }
  *(undefined4 *)(iVar2 + 0x48) = 0;
  FUN_02383f90(0,uVar1,param_3,iVar2);
  FUN_02385e2c();
  return;
}



void FUN_0238419c(void)

{
  undefined4 uVar1;
  int in_r3;
  int iVar2;
  undefined8 uVar3;
  
  FUN_02385e18();
  iVar2 = **DAT_023841f0;
  FUN_0238480c(iVar2);
  FUN_02384424(iVar2);
  uVar1 = 0;
  *(undefined4 *)(DAT_023841f4 + *(int *)(iVar2 + 0x50) * 4) = 0;
  *(undefined4 *)(iVar2 + 0x48) = 2;
  uVar3 = FUN_023840c4((ushort *)(iVar2 + 0x74));
  FUN_02383f90((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),uVar1,in_r3);
  FUN_02385ea8();
  return;
}



void FUN_023841f8(undefined4 *param_1,int param_2,undefined4 param_3,int param_4,int param_5,
                 undefined4 param_6)

{
  int iVar1;
  
  FUN_02385e18();
  iVar1 = FUN_023844d4();
  if (iVar1 < 0) {
    FUN_02385e2c();
  }
  else {
    param_1[0x15] = param_6;
    param_1[0x14] = iVar1;
    param_1[0x12] = 0;
    param_1[0x16] = 0;
    *(undefined4 **)(DAT_023842e8 + iVar1 * 4) = param_1;
    FUN_0238446c((int)param_1);
    param_1[0x1b] = param_4;
    param_1[0x1a] = param_4 - param_5;
    param_1[0x1c] = 0;
    *(undefined4 *)(param_1[0x1b] + -4) = DAT_023842ec;
    *(undefined4 *)param_1[0x1a] = DAT_023842f0;
    *(undefined2 *)(param_1 + 0x1d) = 0;
    FUN_02384508(param_1,param_2,param_4 + -4);
    param_1[1] = param_3;
    param_1[0xf] = DAT_023842f4;
    FUN_023860f4(0,(undefined4 *)((param_4 - param_5) + 4),param_5 + -8);
    param_1[0x17] = 0;
    param_1[0x18] = 0;
    param_1[0x19] = 0;
    FUN_02385e2c();
  }
  return;
}



void FUN_023842f8(void)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (*DAT_023843f4 == 0) {
    *DAT_023843f4 = 1;
    puVar1 = DAT_023843f8;
    iVar2 = 0;
    do {
      *(undefined4 *)(puVar1 + iVar2 * 2 + 10) = 0;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x10);
    *DAT_02384400 = DAT_023843fc;
    iVar2 = DAT_02384404;
    *(undefined4 *)(DAT_02384404 + 0x54) = 0x10;
    *(undefined4 *)(iVar2 + 0x50) = 0;
    *(undefined4 *)(iVar2 + 0x48) = 1;
    *(undefined4 *)(iVar2 + 0x4c) = 0;
    *(undefined4 *)(iVar2 + 0x58) = 0;
    *(int *)(puVar1 + 10) = iVar2;
    *(int *)(puVar1 + 6) = iVar2;
    *(int *)(puVar1 + 4) = iVar2;
    iVar2 = DAT_02384404;
    iVar3 = DAT_0238440c;
    if (DAT_02384408 != 0) {
      iVar3 = (DAT_02384414 - DAT_02384410) - DAT_02384408;
    }
    iVar4 = DAT_02384414 - DAT_02384410;
    *(int *)(DAT_02384404 + 0x6c) = iVar4;
    *(int *)(iVar2 + 0x68) = iVar3;
    *(undefined4 *)(iVar2 + 0x70) = 0;
    *(undefined4 *)(iVar4 + -4) = DAT_02384418;
    **(undefined4 **)(iVar2 + 0x68) = DAT_0238441c;
    *(undefined2 *)(iVar2 + 0x74) = 0;
    puVar1 = DAT_023843f8;
    DAT_023843f8[1] = 0x10;
    *puVar1 = 0;
    puVar1[2] = 0;
    *DAT_02384420 = puVar1;
    FUN_02383e30(0);
  }
  return;
}



void FUN_02384424(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  for (iVar2 = *(int *)(DAT_02384468 + 0xc); (iVar2 != 0 && (iVar2 != param_1));
      iVar2 = *(int *)(iVar2 + 0x4c)) {
    iVar1 = iVar2;
  }
  if (iVar1 == 0) {
    *(undefined4 *)(DAT_02384468 + 0xc) = *(undefined4 *)(param_1 + 0x4c);
  }
  else {
    *(undefined4 *)(iVar1 + 0x4c) = *(undefined4 *)(param_1 + 0x4c);
  }
  return;
}



void FUN_0238446c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  for (iVar2 = *(int *)(DAT_023844d0 + 0xc);
      (iVar2 != 0 && (*(uint *)(iVar2 + 0x54) < *(uint *)(param_1 + 0x54)));
      iVar2 = *(int *)(iVar2 + 0x4c)) {
    iVar1 = iVar2;
  }
  if (iVar1 == 0) {
    *(int *)(param_1 + 0x4c) = *(int *)(DAT_023844d0 + 0xc);
    *(int *)(DAT_023844d0 + 0xc) = param_1;
  }
  else {
    *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar1 + 0x4c);
    *(int *)(iVar1 + 0x4c) = param_1;
  }
  return;
}



int FUN_023844d4(void)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0xf < iVar1) {
      return -1;
    }
    if (*(int *)(DAT_02384504 + iVar1 * 4 + 0x14) == 0) break;
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}



void FUN_02384508(undefined4 *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  param_1[0x10] = param_2 + 4U;
  param_1[0x11] = param_3;
  param_1[0xe] = param_3 + -0x40;
  if ((param_2 + 4U & 1) == 0) {
    uVar1 = 0x1f;
  }
  else {
    uVar1 = 0x3f;
  }
  *param_1 = uVar1;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xf] = 0;
  return;
}



undefined4 FUN_0238456c(int *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int unaff_r4;
  int unaff_r5;
  int unaff_r6;
  int unaff_r7;
  int unaff_r8;
  int unaff_r9;
  int unaff_r10;
  int unaff_r11;
  int in_r12;
  int in_lr;
  char in_NG;
  char in_ZR;
  char in_CY;
  char in_OV;
  byte in_Q;
  
  iVar1 = (uint)(byte)(in_NG << 4 | in_ZR << 3 | in_CY << 2 | in_OV << 1 | in_Q) << 0x1b;
  *param_1 = iVar1;
  param_1[0x11] = (int)register0x00000054;
  param_1[1] = 1;
  param_1[2] = (int)(param_1 + 1);
  param_1[3] = iVar1;
  param_1[4] = param_4;
  param_1[5] = unaff_r4;
  param_1[6] = unaff_r5;
  param_1[7] = unaff_r6;
  param_1[8] = unaff_r7;
  param_1[9] = unaff_r8;
  param_1[10] = unaff_r9;
  param_1[0xb] = unaff_r10;
  param_1[0xc] = unaff_r11;
  param_1[0xd] = in_r12;
  param_1[0xe] = (int)register0x00000054;
  param_1[0xf] = in_lr;
  param_1[0x10] = (int)FUN_023845a0;
  return 0;
}



void FUN_023845a0(int param_1)

{
                    // WARNING: Could not recover jumptable at 0x023845c8. Too many branches
                    // WARNING: Treating indirect jump as call
  (*(code *)(*(int *)(param_1 + 0x3c) + -4))
            (*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 8),
             *(undefined4 *)(param_1 + 0xc),*(undefined4 *)(param_1 + 0x10));
  return;
}



undefined4 FUN_023845cc(int param_1,undefined4 *param_2,uint param_3)

{
  undefined4 uVar1;
  undefined4 extraout_r1;
  uint uVar2;
  longlong lVar3;
  
  uVar2 = param_3;
  lVar3 = FUN_02385e18();
  uVar1 = (undefined4)((ulonglong)lVar3 >> 0x20);
  while( true ) {
    if (*(int *)(param_1 + 0x10) != 0) {
      if (param_2 != (undefined4 *)0x0) {
        *param_2 = *(undefined4 *)(*(int *)(param_1 + 4) + *(int *)(param_1 + 0xc) * 4);
      }
      FUN_02385e2c();
      return 1;
    }
    if ((param_3 & 1) == 0) break;
    FUN_02384134((ushort *)(param_1 + 2),uVar1,uVar2);
    uVar1 = extraout_r1;
  }
  FUN_02385e2c();
  return 0;
}



undefined4 FUN_02384644(ushort *param_1,undefined4 *param_2,uint param_3)

{
  undefined4 uVar1;
  undefined4 extraout_r1;
  uint uVar2;
  longlong lVar3;
  undefined8 uVar4;
  
  uVar2 = param_3;
  lVar3 = FUN_02385e18();
  uVar1 = (undefined4)((ulonglong)lVar3 >> 0x20);
  while( true ) {
    if (*(int *)(param_1 + 8) != 0) {
      if (param_2 != (undefined4 *)0x0) {
        *param_2 = *(undefined4 *)(*(int *)(param_1 + 2) + *(int *)(param_1 + 6) * 4);
      }
      uVar4 = FUN_0238f0dc(*(int *)(param_1 + 6) + 1,*(uint *)(param_1 + 4));
      *(int *)(param_1 + 6) = (int)((ulonglong)uVar4 >> 0x20);
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
      FUN_023840c4(param_1);
      FUN_02385e2c();
      return 1;
    }
    if ((param_3 & 1) == 0) break;
    FUN_02384134(param_1 + 1,uVar1,uVar2);
    uVar1 = extraout_r1;
  }
  FUN_02385e2c();
  return 0;
}



undefined4 FUN_023846e4(ushort *param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  undefined8 uVar3;
  
  FUN_02385e18();
  while( true ) {
    uVar2 = *(uint *)(param_1 + 8);
    uVar1 = *(uint *)(param_1 + 4);
    if ((int)uVar2 < (int)uVar1) {
      uVar3 = FUN_0238f0dc(*(int *)(param_1 + 6) + uVar2,uVar1);
      *(undefined4 *)(*(int *)(param_1 + 2) + (int)((ulonglong)uVar3 >> 0x20) * 4) = param_2;
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
      FUN_023840c4(param_1 + 1);
      FUN_02385e2c();
      return 1;
    }
    if ((param_3 & 1) == 0) break;
    FUN_02384134(param_1,uVar1,uVar2);
  }
  FUN_02385e2c();
  return 0;
}



void FUN_02384778(undefined2 *param_1,undefined4 param_2,undefined4 param_3)

{
  *param_1 = 0;
  param_1[1] = 0;
  *(undefined4 *)(param_1 + 2) = param_2;
  *(undefined4 *)(param_1 + 4) = param_3;
  *(undefined4 *)(param_1 + 6) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}



int FUN_02384798(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x60);
  iVar1 = *(int *)(iVar2 + 0x10);
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 100) = 0;
  }
  else {
    *(undefined4 *)(iVar1 + 0xc) = 0;
  }
  *(int *)(param_1 + 0x60) = iVar1;
  return iVar2;
}



void FUN_023847c0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_2 + 0x10);
  iVar1 = *(int *)(param_2 + 0xc);
  if (iVar2 == 0) {
    *(int *)(param_1 + 100) = iVar1;
  }
  else {
    *(int *)(iVar2 + 0xc) = iVar1;
  }
  if (iVar1 == 0) {
    *(int *)(param_1 + 0x60) = iVar2;
  }
  else {
    *(int *)(iVar1 + 0x10) = iVar2;
  }
  return;
}



void FUN_023847e4(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 100);
  if (iVar1 == 0) {
    *(int *)(param_1 + 0x60) = param_2;
  }
  else {
    *(int *)(*(int *)(param_1 + 0x60) + 0x10) = param_2;
  }
  *(int *)(param_2 + 0xc) = iVar1;
  *(undefined4 *)(param_2 + 0x10) = 0;
  *(int *)(param_1 + 100) = param_2;
  return;
}



void FUN_0238480c(int param_1)

{
  ushort *puVar1;
  
  while (*(int *)(param_1 + 0x60) != 0) {
    puVar1 = (ushort *)FUN_02384798(param_1);
    *(undefined4 *)(puVar1 + 4) = 0;
    *(undefined4 *)(puVar1 + 2) = 0;
    FUN_023840c4(puVar1);
  }
  return;
}



void FUN_0238484c(ushort *param_1)

{
  int iVar1;
  
  FUN_02385e18();
  iVar1 = *(int *)(DAT_023848b8 + 8);
  if ((*(int *)(param_1 + 2) == iVar1) &&
     (*(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1, *(int *)(param_1 + 4) == 0)) {
    FUN_023847c0(iVar1,(int)param_1);
    *(undefined4 *)(param_1 + 2) = 0;
    FUN_023840c4(param_1);
  }
  FUN_02385e2c();
  return;
}



void FUN_023848bc(ushort *param_1,undefined4 param_2,uint param_3)

{
  undefined4 uVar1;
  undefined4 extraout_r1;
  int iVar2;
  longlong lVar3;
  
  lVar3 = FUN_02385e18();
  uVar1 = (undefined4)((ulonglong)lVar3 >> 0x20);
  iVar2 = *(int *)(DAT_02384944 + 8);
  do {
    if (*(int *)(param_1 + 2) == 0) {
      *(int *)(param_1 + 2) = iVar2;
      *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
      FUN_023847e4(iVar2,(int)param_1);
LAB_02384930:
      FUN_02385e2c();
      return;
    }
    if (*(int *)(param_1 + 2) == iVar2) {
      *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
      goto LAB_02384930;
    }
    *(ushort **)(iVar2 + 0x5c) = param_1;
    FUN_02384134(param_1,uVar1,param_3);
    *(undefined4 *)(iVar2 + 0x5c) = 0;
    uVar1 = extraout_r1;
  } while( true );
}



void FUN_0238495c(void)

{
  FUN_02384aac();
  thunk_EXT_FUN_037fe42c();
  FUN_02383d44();
  FUN_02383a78();
  FUN_02385268();
  FUN_023856dc();
  FUN_023842f8();
  FUN_02385f8c();
  FUN_0238ee78();
  return;
}



void FUN_02384994(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 * 4 + 0x27ffda0) = param_2;
  return;
}



void FUN_023849a8(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 * 4 + 0x27ffdc4) = param_2;
  return;
}



uint FUN_023849bc(int param_1)

{
  uint uVar1;
  
  if (param_1 == 1) {
    return DAT_02384a0c;
  }
  if (param_1 != 7) {
    if (param_1 != 8) {
      return 0;
    }
    uVar1 = 0x3800000;
    if (0x3800000 < DAT_02384a10) {
      uVar1 = DAT_02384a10;
    }
    return uVar1;
  }
  uVar1 = DAT_02384a10;
  if (0x3800000 < DAT_02384a10) {
    uVar1 = 0x3800000;
  }
  return uVar1;
}



int FUN_02384a14(int param_1)

{
  int iVar1;
  
  if (param_1 == 1) {
    return DAT_02384a74;
  }
  if (param_1 == 7) {
    return 0x3800000;
  }
  if (param_1 != 8) {
    return 0;
  }
  if (DAT_02384a80 != 0) {
    if (DAT_02384a80 < 0) {
      iVar1 = 0x3800000 - DAT_02384a80;
    }
    else {
      iVar1 = (DAT_02384a7c - DAT_02384a78) - DAT_02384a80;
    }
    return iVar1;
  }
  return 0x3800000;
}



undefined4 FUN_02384a84(int param_1)

{
  return *(undefined4 *)(param_1 * 4 + 0x27ffda0);
}



undefined4 FUN_02384a98(int param_1)

{
  return *(undefined4 *)(param_1 * 4 + 0x27ffdc4);
}



void FUN_02384aac(void)

{
  int iVar1;
  uint uVar2;
  
  if (*DAT_02384b4c == 0) {
    *DAT_02384b4c = 1;
    iVar1 = FUN_02384a14(1);
    FUN_023849a8(1,iVar1);
    uVar2 = FUN_023849bc(1);
    FUN_02384994(1,uVar2);
    iVar1 = FUN_02384a14(7);
    FUN_023849a8(7,iVar1);
    uVar2 = FUN_023849bc(7);
    FUN_02384994(7,uVar2);
    iVar1 = FUN_02384a14(8);
    FUN_023849a8(8,iVar1);
    uVar2 = FUN_023849bc(8);
    FUN_02384994(8,uVar2);
  }
  return;
}



int FUN_02384b50(int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint *puVar9;
  
  iVar6 = 0;
  iVar5 = 0;
  iVar4 = -1;
  FUN_02385e18();
  iVar8 = *(int *)(DAT_02384cf0 + param_1 * 4);
  iVar2 = *(int *)(iVar8 + 0x10);
  if (((iVar2 != 0) && (-1 < param_2)) && (param_2 < *(int *)(iVar8 + 4))) {
    iVar3 = iVar2 + param_2 * 0xc;
    iVar2 = *(int *)(iVar2 + param_2 * 0xc);
    if ((-1 < iVar2) && ((puVar1 = *(uint **)(iVar3 + 8), puVar1 == (uint *)0x0 || (*puVar1 == 0))))
    {
      while (puVar1 != (uint *)0x0) {
        if ((((puVar1 < *(uint **)(iVar8 + 8)) || (*(uint *)(iVar8 + 0xc) <= puVar1)) ||
            ((((uint)puVar1 & 0x1f) != 0 ||
             ((((puVar9 = (uint *)puVar1[1], puVar9 != (uint *)0x0 && ((uint *)*puVar9 != puVar1))
               || (uVar7 = puVar1[2], uVar7 < 0x40)) ||
              (((uVar7 & 0x1f) != 0 || (iVar6 = iVar6 + uVar7, iVar6 < 1)))))))) ||
           (puVar1 = puVar9, iVar2 < iVar6)) goto LAB_02384ce0;
      }
      puVar1 = *(uint **)(iVar3 + 4);
      if ((puVar1 == (uint *)0x0) || (*puVar1 == 0)) goto LAB_02384cd0;
    }
  }
LAB_02384ce0:
  FUN_02385e2c();
  return iVar4;
LAB_02384cd0:
  if (puVar1 == (uint *)0x0) {
    if (iVar6 == iVar2) {
      iVar4 = iVar5;
    }
    goto LAB_02384ce0;
  }
  if (((((puVar1 < *(uint **)(iVar8 + 8)) || (*(uint *)(iVar8 + 0xc) <= puVar1)) ||
       (((uint)puVar1 & 0x1f) != 0)) ||
      (((puVar9 = (uint *)puVar1[1], puVar9 != (uint *)0x0 && ((uint *)*puVar9 != puVar1)) ||
       ((uVar7 = puVar1[2], uVar7 < 0x40 || ((uVar7 & 0x1f) != 0)))))) ||
     ((puVar9 != (uint *)0x0 && (puVar9 <= (uint *)((int)puVar1 + uVar7))))) goto LAB_02384ce0;
  iVar6 = iVar6 + uVar7;
  iVar5 = iVar5 + (uVar7 - 0x20);
  if ((iVar6 < 1) || (puVar1 = puVar9, iVar2 < iVar6)) goto LAB_02384ce0;
  goto LAB_02384cd0;
}



int FUN_02384cf4(int param_1,int param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  
  FUN_02385e18();
  iVar4 = *(int *)(DAT_02384d98 + param_1 * 4);
  puVar3 = (undefined4 *)(param_2 + 0x1fU & 0xffffffe0);
  iVar2 = 0;
  while( true ) {
    if (*(int *)(iVar4 + 4) <= iVar2) {
      FUN_02385e2c();
      return -1;
    }
    iVar1 = *(int *)(iVar4 + 0x10);
    piVar5 = (int *)(iVar1 + iVar2 * 0xc);
    if (*(int *)(iVar1 + iVar2 * 0xc) < 0) break;
    iVar2 = iVar2 + 1;
  }
  *piVar5 = (param_3 & 0xffffffe0) - (int)puVar3;
  *puVar3 = 0;
  puVar3[1] = 0;
  puVar3[2] = *piVar5;
  piVar5[1] = (int)puVar3;
  piVar5[2] = 0;
  FUN_02385e2c();
  return iVar2;
}



undefined4 FUN_02384d9c(int param_1,undefined4 *param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  FUN_02385e18();
  *(undefined4 **)(DAT_02384e40 + param_1 * 4) = param_2;
  param_2[4] = param_2 + 5;
  param_2[1] = param_4;
  for (iVar2 = 0; iVar2 < (int)param_2[1]; iVar2 = iVar2 + 1) {
    iVar1 = param_2[4] + iVar2 * 0xc;
    *(undefined4 *)(param_2[4] + iVar2 * 0xc) = 0xffffffff;
    *(undefined4 *)(iVar1 + 8) = 0;
    *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(iVar1 + 8);
  }
  *param_2 = 0xffffffff;
  param_2[2] = param_2[4] + param_4 * 0xc + 0x1fU & 0xffffffe0;
  param_2[3] = param_3 & 0xffffffe0;
  FUN_02385e2c();
  return param_2[2];
}



undefined4 FUN_02384e44(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  FUN_02385e18();
  puVar1 = *(undefined4 **)(DAT_02384e7c + param_1 * 4);
  uVar2 = *puVar1;
  *puVar1 = param_2;
  FUN_02385e2c();
  return uVar2;
}



void FUN_02384e80(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  uint **ppuVar3;
  int iVar4;
  
  FUN_02385e18();
  piVar1 = *(int **)(DAT_02384ef0 + param_1 * 4);
  if (param_2 < 0) {
    param_2 = *piVar1;
  }
  iVar4 = param_2 * 0xc + piVar1[4];
  iVar2 = FUN_023850c0(*(int *)(iVar4 + 8),(int *)(uint **)(param_3 + -0x20));
  *(int *)(iVar4 + 8) = iVar2;
  ppuVar3 = FUN_0238500c(*(uint ***)(iVar4 + 4),(uint **)(param_3 + -0x20));
  *(uint ***)(iVar4 + 4) = ppuVar3;
  FUN_02385e2c();
  return;
}



int * FUN_02384ef4(int param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  
  FUN_02385e18();
  piVar2 = *(int **)(DAT_02385008 + param_1 * 4);
  if (piVar2 == (int *)0x0) {
    FUN_02385e2c();
    piVar2 = (int *)0x0;
  }
  else {
    if (param_2 < 0) {
      param_2 = *piVar2;
    }
    iVar5 = param_2 * 0xc + piVar2[4];
    uVar6 = param_3 + 0x3fU & 0xffffffe0;
    for (piVar2 = *(int **)(iVar5 + 4); (piVar2 != (int *)0x0 && (piVar2[2] < (int)uVar6));
        piVar2 = (int *)piVar2[1]) {
    }
    if (piVar2 == (int *)0x0) {
      FUN_02385e2c();
      piVar2 = (int *)0x0;
    }
    else {
      iVar3 = piVar2[2];
      if (iVar3 - uVar6 < 0x40) {
        iVar3 = FUN_023850c0((int)*(int **)(iVar5 + 4),piVar2);
        *(int *)(iVar5 + 4) = iVar3;
      }
      else {
        piVar2[2] = uVar6;
        piVar4 = (int *)((int)piVar2 + uVar6);
        piVar4[2] = iVar3 - uVar6;
        *(int *)((int)piVar2 + uVar6) = *piVar2;
        piVar4[1] = piVar2[1];
        if ((int **)piVar4[1] != (int **)0x0) {
          *(int **)piVar4[1] = piVar4;
        }
        if (*piVar4 == 0) {
          *(int **)(iVar5 + 4) = piVar4;
        }
        else {
          *(int **)(*piVar4 + 4) = piVar4;
        }
      }
      puVar1 = FUN_023850e8(*(undefined4 **)(iVar5 + 8),piVar2);
      *(undefined4 **)(iVar5 + 8) = puVar1;
      FUN_02385e2c();
      piVar2 = piVar2 + 8;
    }
  }
  return piVar2;
}



uint ** FUN_0238500c(uint **param_1,uint **param_2)

{
  uint **ppuVar1;
  uint **ppuVar2;
  uint **ppuVar3;
  
  ppuVar1 = param_1;
  ppuVar3 = (uint **)0x0;
  while ((ppuVar2 = ppuVar1, ppuVar2 != (uint **)0x0 && (ppuVar2 < param_2))) {
    ppuVar3 = ppuVar2;
    ppuVar1 = (uint **)ppuVar2[1];
  }
  param_2[1] = (uint *)ppuVar2;
  *param_2 = (uint *)ppuVar3;
  if (ppuVar2 != (uint **)0x0) {
    *ppuVar2 = (uint *)param_2;
    if ((uint **)((int)param_2 + (int)param_2[2]) == ppuVar2) {
      param_2[2] = (uint *)((int)param_2[2] + (int)ppuVar2[2]);
      ppuVar2 = (uint **)ppuVar2[1];
      param_2[1] = (uint *)ppuVar2;
      if (ppuVar2 != (uint **)0x0) {
        *ppuVar2 = (uint *)param_2;
      }
    }
  }
  ppuVar1 = param_2;
  if (ppuVar3 != (uint **)0x0) {
    ppuVar3[1] = (uint *)param_2;
    ppuVar1 = param_1;
    if ((uint **)((int)ppuVar3 + (int)ppuVar3[2]) == param_2) {
      ppuVar3[2] = (uint *)((int)ppuVar3[2] + (int)param_2[2]);
      ppuVar3[1] = (uint *)ppuVar2;
      if (ppuVar2 != (uint **)0x0) {
        *ppuVar2 = (uint *)ppuVar3;
      }
    }
  }
  return ppuVar1;
}



int FUN_023850c0(int param_1,int *param_2)

{
  if ((int *)param_2[1] != (int *)0x0) {
    *(int *)param_2[1] = *param_2;
  }
  if (*param_2 == 0) {
    param_1 = param_2[1];
  }
  else {
    *(int *)(*param_2 + 4) = param_2[1];
  }
  return param_1;
}



undefined4 * FUN_023850e8(undefined4 *param_1,undefined4 *param_2)

{
  param_2[1] = param_1;
  *param_2 = 0;
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = param_2;
  }
  return param_2;
}



void FUN_02385104(uint param_1)

{
  *DAT_0238511c = *DAT_0238511c | (ushort)(1 << (param_1 & 0xff));
  return;
}



undefined8 FUN_02385120(void)

{
  ushort uVar1;
  bool bVar2;
  uint local_c;
  uint local_8;
  
  FUN_02385e18();
  uVar1 = *(ushort *)PTR_Timers_0_to_3_023851c0;
  local_c = *DAT_023851c4;
  local_8 = DAT_023851c4[1] & DAT_023851c8;
  if (((*(uint *)PTR_REG_IF_023851cc & 8) != 0) && ((uVar1 & 0x8000) == 0)) {
    bVar2 = 0xfffffffe < local_c;
    local_c = local_c + 1;
    local_8 = local_8 + bVar2;
  }
  FUN_02385e2c();
  return CONCAT44(local_8 << 0x10 | local_c >> 0x10,(uint)uVar1 | local_c << 0x10);
}



void FUN_023851d0(void)

{
  uint *puVar1;
  uint *puVar2;
  int *piVar3;
  undefined2 *puVar4;
  uint uVar5;
  
  puVar2 = DAT_02385244;
  uVar5 = *DAT_02385244;
  puVar1 = DAT_02385244 + 1;
  *DAT_02385244 = uVar5 + 1;
  puVar2[1] = *puVar1 + (uint)(0xfffffffe < uVar5);
  puVar4 = DAT_0238524c;
  piVar3 = DAT_02385248;
  if (*DAT_02385248 != 0) {
    *DAT_0238524c = 0;
    *(undefined2 *)PTR_Timers_0_to_3_02385250 = 0;
    *puVar4 = 0xc1;
    *piVar3 = 0;
  }
  FUN_02383984(0,DAT_02385254,0);
  return;
}



undefined2 FUN_02385258(void)

{
  return *DAT_02385264;
}



void FUN_02385268(void)

{
  undefined4 *puVar1;
  undefined2 *puVar2;
  
  if (*DAT_023852e4 == 0) {
    *DAT_023852e4 = 1;
    FUN_02385104(0);
    puVar1 = DAT_023852e8;
    *DAT_023852e8 = 0;
    puVar1[1] = 0;
    puVar2 = DAT_023852ec;
    *DAT_023852ec = 0;
    *(undefined2 *)PTR_Timers_0_to_3_023852f0 = 0;
    *puVar2 = 0xc1;
    FUN_023839d0(8,DAT_023852f4);
    FUN_02383918(8);
    *DAT_023852f8 = 0;
  }
  return;
}



void FUN_0238530c(void)

{
  code **ppcVar1;
  code *pcVar2;
  code **ppcVar3;
  bool bVar4;
  undefined8 uVar5;
  
  *DAT_02385400 = 0;
  FUN_023838dc(0x10);
  *(uint *)PTR_NDS7_IRQ_IF_Check_Bits_02385404 = *(uint *)PTR_NDS7_IRQ_IF_Check_Bits_02385404 | 0x10
  ;
  uVar5 = FUN_02385120();
  ppcVar1 = DAT_02385408;
  pcVar2 = (code *)((ulonglong)uVar5 >> 0x20);
  ppcVar3 = (code **)*DAT_02385408;
  if (ppcVar3 != (code **)0x0) {
    bVar4 = ppcVar3[4] <= pcVar2;
    if (pcVar2 == ppcVar3[4]) {
      bVar4 = ppcVar3[3] <= (code *)uVar5;
    }
    if (bVar4) {
      pcVar2 = ppcVar3[6];
      *DAT_02385408 = pcVar2;
      if (pcVar2 == (code *)0x0) {
        ppcVar1[1] = (code *)0x0;
      }
      else {
        *(undefined4 *)(pcVar2 + 0x14) = 0;
      }
      pcVar2 = *ppcVar3;
      if (ppcVar3[8] == (code *)0x0 && ppcVar3[7] == (code *)0x0) {
        *ppcVar3 = (code *)0x0;
      }
      if (pcVar2 != (code *)0x0) {
        (*pcVar2)(ppcVar3[1]);
      }
      if (ppcVar3[8] != (code *)0x0 || ppcVar3[7] != (code *)0x0) {
        *ppcVar3 = pcVar2;
        FUN_0238558c((int)ppcVar3,0,0);
      }
      if (*DAT_02385408 != (code *)0x0) {
        FUN_0238572c((int)*DAT_02385408);
      }
    }
    else {
      FUN_0238572c((int)ppcVar3);
    }
  }
  return;
}



void FUN_0238540c(int *param_1)

{
  int iVar1;
  
  FUN_02385e18();
  if (*param_1 == 0) {
    FUN_02385e2c();
  }
  else {
    iVar1 = param_1[6];
    if (iVar1 == 0) {
      DAT_02385498[1] = param_1[5];
    }
    else {
      *(int *)(iVar1 + 0x14) = param_1[5];
    }
    if (param_1[5] == 0) {
      *DAT_02385498 = iVar1;
      if (iVar1 != 0) {
        FUN_0238572c(iVar1);
      }
    }
    else {
      *(int *)(param_1[5] + 0x18) = iVar1;
    }
    *param_1 = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    FUN_02385e2c();
  }
  return;
}



void FUN_0238549c(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7)

{
  if ((param_1 == (int *)0x0) || (*param_1 != 0)) {
    FUN_02385ea8();
  }
  FUN_02385e18();
  param_1[7] = param_4;
  param_1[8] = param_5;
  param_1[9] = param_2;
  param_1[10] = param_3;
  *param_1 = param_6;
  param_1[1] = param_7;
  FUN_0238558c((int)param_1,0,0);
  FUN_02385e2c();
  return;
}



void FUN_02385518(int *param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  longlong lVar1;
  
  if ((param_1 == (int *)0x0) || (*param_1 != 0)) {
    FUN_02385ea8();
  }
  FUN_02385e18();
  param_1[7] = 0;
  param_1[8] = 0;
  *param_1 = param_4;
  param_1[1] = param_5;
  lVar1 = FUN_02385120();
  lVar1 = lVar1 + CONCAT44(param_3,param_2);
  FUN_0238558c((int)param_1,(uint)lVar1,(uint)((ulonglong)lVar1 >> 0x20));
  FUN_02385e2c();
  return;
}



void FUN_0238558c(int param_1,uint param_2,uint param_3)

{
  longlong lVar1;
  int *piVar2;
  uint uVar3;
  int extraout_r1;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  bool bVar8;
  undefined8 uVar9;
  
  if (*(int *)(param_1 + 0x20) != 0 || *(int *)(param_1 + 0x1c) != 0) {
    uVar9 = FUN_02385120();
    uVar4 = (uint)((ulonglong)uVar9 >> 0x20);
    uVar3 = (uint)uVar9;
    param_2 = *(uint *)(param_1 + 0x24);
    param_3 = *(uint *)(param_1 + 0x28);
    bVar8 = uVar4 <= param_3;
    if (param_3 == uVar4) {
      bVar8 = uVar3 <= param_2;
    }
    if (!bVar8) {
      uVar7 = *(uint *)(param_1 + 0x1c);
      uVar5 = *(uint *)(param_1 + 0x20);
      uVar3 = FUN_0238eed4(uVar3 - param_2,uVar4 - (param_3 + (uVar3 < param_2)),uVar7,uVar5);
      lVar1 = (ulonglong)(uVar3 + 1) * (ulonglong)uVar7;
      uVar4 = (uint)lVar1;
      bVar8 = CARRY4(param_2,uVar4);
      param_2 = param_2 + uVar4;
      param_3 = param_3 + uVar5 * (uVar3 + 1) +
                          uVar7 * (extraout_r1 + (uint)(0xfffffffe < uVar3)) +
                          (int)((ulonglong)lVar1 >> 0x20) + (uint)bVar8;
    }
  }
  *(uint *)(param_1 + 0xc) = param_2;
  *(uint *)(param_1 + 0x10) = param_3;
  iVar6 = *DAT_023856b8;
  while( true ) {
    if (iVar6 == 0) {
      *(undefined4 *)(param_1 + 0x18) = 0;
      piVar2 = DAT_023856b8;
      iVar6 = DAT_023856b8[1];
      DAT_023856b8[1] = param_1;
      *(int *)(param_1 + 0x14) = iVar6;
      if (iVar6 == 0) {
        piVar2[1] = param_1;
        *piVar2 = param_1;
        FUN_0238572c(param_1);
      }
      else {
        *(int *)(iVar6 + 0x18) = param_1;
      }
      return;
    }
    if ((int)(param_3 - (*(int *)(iVar6 + 0x10) + (uint)(param_2 < *(uint *)(iVar6 + 0xc)))) < 0)
    break;
    iVar6 = *(int *)(iVar6 + 0x18);
  }
  *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(iVar6 + 0x14);
  *(int *)(iVar6 + 0x14) = param_1;
  *(int *)(param_1 + 0x18) = iVar6;
  if (*(int *)(param_1 + 0x14) == 0) {
    *DAT_023856b8 = param_1;
    FUN_0238572c(param_1);
    return;
  }
  *(int *)(*(int *)(param_1 + 0x14) + 0x18) = param_1;
  return;
}



void FUN_023856bc(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[2] = 0;
  return;
}



undefined2 FUN_023856cc(void)

{
  return *DAT_023856d8;
}



void FUN_023856dc(void)

{
  undefined4 *puVar1;
  
  if (*DAT_02385724 == 0) {
    *DAT_02385724 = 1;
    FUN_02385104(1);
    puVar1 = DAT_02385728;
    *DAT_02385728 = 0;
    puVar1[1] = 0;
    FUN_023838dc(0x10);
  }
  return;
}



void FUN_0238572c(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  
  uVar4 = FUN_02385120();
  *DAT_023857b8 = 0;
  uVar3 = *(uint *)(param_1 + 0xc) - (uint)uVar4;
  iVar2 = *(int *)(param_1 + 0x10) -
          ((int)((ulonglong)uVar4 >> 0x20) + (uint)(*(uint *)(param_1 + 0xc) < (uint)uVar4));
  FUN_02383984(1,DAT_023857bc,0);
  uVar1 = DAT_023857c0;
  if ((-1 < iVar2) &&
     (uVar1 = 0,
     (int)(iVar2 - (uint)(uVar3 < 0x10000)) < 0 !=
     (SBORROW4(iVar2,(uint)(uVar3 < 0x10000)) != false))) {
    uVar1 = ~uVar3 & 0xffff;
  }
  *DAT_023857c4 = (short)uVar1;
  *DAT_023857b8 = 0xc1;
  FUN_02383918(0x10);
  return;
}



int FUN_023857c8(int param_1)

{
  FUN_02385e18();
  if (param_1 < *DAT_0238580c) {
    *DAT_02385810 = *DAT_02385810 + 1;
  }
  *DAT_0238580c = param_1;
  FUN_02385e2c();
  return *DAT_02385810;
}



undefined4 FUN_02385814(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = param_3 - *(short *)(param_1 + 0x10);
  if ((-1 < param_2 - *(int *)(param_1 + 0xc)) &&
     ((param_2 != *(int *)(param_1 + 0xc) || (-1 < iVar2)))) {
    if (iVar2 < 0) {
      iVar2 = iVar2 + DAT_02385860;
    }
    if (*(short *)(param_1 + 0x12) < iVar2) {
      uVar1 = 2;
    }
    else {
      uVar1 = 1;
    }
    return uVar1;
  }
  return 0;
}



void FUN_02385864(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  code *pcVar4;
  int iVar5;
  uint uVar6;
  code **ppcVar7;
  
  FUN_023838dc(4);
  puVar1 = PTR_REG_DISPSTAT_023859d8;
  *(ushort *)PTR_REG_DISPSTAT_023859d8 = *(ushort *)PTR_REG_DISPSTAT_023859d8 & 0xffdf;
  *(uint *)PTR_NDS7_IRQ_IF_Check_Bits_023859dc = *(uint *)PTR_NDS7_IRQ_IF_Check_Bits_023859dc | 4;
  FUN_023857c8(((int)(uint)*(ushort *)puVar1 >> 8 | (*(ushort *)puVar1 & 0x80) << 1) - 1);
  piVar3 = DAT_023859e4;
  puVar2 = PTR_REG_VCOUNT_023859e0;
  puVar1 = PTR_REG_DISPSTAT_023859d8;
LAB_023859bc:
  do {
    ppcVar7 = (code **)*DAT_023859e8;
    if (ppcVar7 == (code **)0x0) {
      return;
    }
    uVar6 = (uint)*(ushort *)puVar2;
    pcVar4 = (code *)FUN_023857c8(uVar6);
    iVar5 = FUN_02385814((int)ppcVar7,(int)pcVar4,uVar6);
    if (iVar5 == 0) {
      FUN_02385ae8((int)ppcVar7);
      if ((int)*(short *)(ppcVar7 + 4) != (uint)*(ushort *)puVar2) {
        return;
      }
      if (ppcVar7[3] != pcVar4) {
        return;
      }
      FUN_023838dc(4);
      *(ushort *)puVar1 = *(ushort *)puVar1 & 0xffdf;
      FUN_023838a8(4);
    }
    else if (iVar5 != 1) {
      if (iVar5 == 2) {
        FUN_02385c88((int)ppcVar7);
        FUN_02385cc0((int)ppcVar7);
        ppcVar7[3] = (code *)(*piVar3 + 1);
      }
      goto LAB_023859bc;
    }
    pcVar4 = *ppcVar7;
    FUN_02385c88((int)ppcVar7);
    *ppcVar7 = (code *)0x0;
    if (pcVar4 != (code *)0x0) {
      (*pcVar4)(ppcVar7[1]);
    }
    if ((ppcVar7[7] != (code *)0x0) && (ppcVar7[9] == (code *)0x0)) {
      *ppcVar7 = pcVar4;
      ppcVar7[3] = (code *)(*piVar3 + 1);
      FUN_02385cc0((int)ppcVar7);
    }
  } while( true );
}



void FUN_023859ec(int param_1)

{
  int *piVar1;
  int *piVar2;
  
  FUN_02385e18();
  if (param_1 == 0) {
    FUN_02385ea8();
  }
  piVar1 = *DAT_02385a64;
  if (piVar1 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = (int *)piVar1[6];
  }
  while (piVar1 != (int *)0x0) {
    if (piVar1[2] == param_1) {
      FUN_02385a68(piVar1);
    }
    piVar1 = piVar2;
    if (piVar2 == (int *)0x0) {
      piVar2 = (int *)0x0;
    }
    else {
      piVar2 = (int *)piVar2[6];
    }
  }
  FUN_02385e2c();
  return;
}



void FUN_02385a68(int *param_1)

{
  FUN_02385e18();
  param_1[9] = 1;
  if (*param_1 == 0) {
    FUN_02385e2c();
  }
  else {
    FUN_02385c88((int)param_1);
    *param_1 = 0;
    FUN_02385e2c();
  }
  return;
}



void FUN_02385abc(int param_1,int param_2)

{
  if (param_2 == 0) {
    FUN_02385ea8();
  }
  if (param_1 != 0) {
    *(int *)(param_1 + 8) = param_2;
  }
  return;
}



void FUN_02385ae8(int param_1)

{
  undefined *puVar1;
  
  FUN_023839d0(4,DAT_02385b3c);
  puVar1 = PTR_REG_DISPSTAT_02385b40;
  *(ushort *)PTR_REG_DISPSTAT_02385b40 =
       *(ushort *)PTR_REG_DISPSTAT_02385b40 & 0x3f |
       (ushort)(((int)*(short *)(param_1 + 0x10) & 0xffU) << 8) |
       (ushort)((int)((int)*(short *)(param_1 + 0x10) & 0x100U) >> 1);
  *(ushort *)puVar1 = *(ushort *)puVar1 | 0x20;
  FUN_02383918(4);
  return;
}



void FUN_02385b44(int *param_1,int param_2,undefined2 param_3,int param_4,int param_5)

{
  ushort uVar1;
  int iVar2;
  
  FUN_02385e18();
  if ((param_1 == (int *)0x0) || (*param_1 != 0)) {
    FUN_02385ea8();
  }
  uVar1 = *(ushort *)PTR_REG_VCOUNT_02385bd8;
  iVar2 = FUN_023857c8((uint)uVar1);
  param_1[7] = 1;
  *(short *)(param_1 + 4) = (short)param_2;
  if (param_2 <= (int)(uint)uVar1) {
    iVar2 = iVar2 + 1;
  }
  param_1[3] = iVar2;
  *(undefined2 *)((int)param_1 + 0x12) = param_3;
  *param_1 = param_4;
  param_1[1] = param_5;
  param_1[9] = 0;
  FUN_02385d04((int)param_1);
  FUN_02385e2c();
  return;
}



void FUN_02385bdc(int *param_1,int param_2,undefined2 param_3,int param_4,int param_5)

{
  ushort uVar1;
  int iVar2;
  
  FUN_02385e18();
  if ((param_1 == (int *)0x0) || (*param_1 != 0)) {
    FUN_02385ea8();
  }
  uVar1 = *(ushort *)PTR_REG_VCOUNT_02385c70;
  iVar2 = FUN_023857c8((uint)uVar1);
  param_1[7] = 0;
  *(short *)(param_1 + 4) = (short)param_2;
  if (param_2 <= (int)(uint)uVar1) {
    iVar2 = iVar2 + 1;
  }
  param_1[3] = iVar2;
  *(undefined2 *)((int)param_1 + 0x12) = param_3;
  *param_1 = param_4;
  param_1[1] = param_5;
  param_1[9] = 0;
  FUN_02385d04((int)param_1);
  FUN_02385e2c();
  return;
}



void FUN_02385c74(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[2] = 0;
  param_1[8] = 0;
  return;
}



void FUN_02385c88(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 0) {
    iVar2 = *(int *)(param_1 + 0x14);
    iVar1 = *(int *)(param_1 + 0x18);
    if (iVar1 == 0) {
      DAT_02385cbc[1] = iVar2;
    }
    else {
      *(int *)(iVar1 + 0x14) = iVar2;
    }
    if (iVar2 == 0) {
      *DAT_02385cbc = iVar1;
    }
    else {
      *(int *)(iVar2 + 0x18) = iVar1;
    }
    return;
  }
  return;
}



void FUN_02385cc0(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = DAT_02385d00;
  iVar2 = DAT_02385d00[1];
  *(int *)(param_1 + 0x14) = iVar2;
  *(undefined4 *)(param_1 + 0x18) = 0;
  piVar1[1] = param_1;
  if (iVar2 == 0) {
    *piVar1 = param_1;
    FUN_02385ae8(param_1);
  }
  else {
    *(int *)(iVar2 + 0x18) = param_1;
  }
  return;
}



void FUN_02385d04(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *DAT_02385d88;
  while( true ) {
    if (iVar2 == 0) {
      FUN_02385cc0(param_1);
      return;
    }
    if ((*(uint *)(param_1 + 0xc) <= *(uint *)(iVar2 + 0xc)) &&
       ((*(uint *)(iVar2 + 0xc) != *(uint *)(param_1 + 0xc) ||
        (*(short *)(param_1 + 0x10) < *(short *)(iVar2 + 0x10))))) break;
    iVar2 = *(int *)(iVar2 + 0x18);
  }
  iVar1 = *(int *)(iVar2 + 0x14);
  *(int *)(param_1 + 0x14) = iVar1;
  *(int *)(param_1 + 0x18) = iVar2;
  *(int *)(iVar2 + 0x14) = param_1;
  if (iVar1 == 0) {
    *DAT_02385d88 = param_1;
    FUN_02385ae8(param_1);
    return;
  }
  *(int *)(iVar1 + 0x18) = param_1;
  return;
}



undefined2 FUN_02385d8c(void)

{
  return *DAT_02385d98;
}



void FUN_02385d9c(void)

{
  undefined4 *puVar1;
  
  if (*DAT_02385df4 == 0) {
    *DAT_02385df4 = 1;
    puVar1 = DAT_02385df8;
    *DAT_02385df8 = 0;
    puVar1[1] = 0;
    FUN_023838dc(4);
    *DAT_02385dfc = 0;
    *DAT_02385e00 = 0;
  }
  return;
}



longlong FUN_02385e04(void)

{
  char in_NG;
  char in_ZR;
  char in_CY;
  char in_OV;
  byte in_Q;
  
  return (ulonglong)((uint)(byte)(in_NG << 4 | in_ZR << 3 | in_CY << 2 | in_OV << 1 | in_Q) << 0x1b)
         << 0x20;
}



longlong FUN_02385e18(void)

{
  char in_NG;
  char in_ZR;
  char in_CY;
  char in_OV;
  byte in_Q;
  
  return (ulonglong)
         ((uint)(byte)(in_NG << 4 | in_ZR << 3 | in_CY << 2 | in_OV << 1 | in_Q) << 0x1b | 0x80) <<
         0x20;
}



undefined4 FUN_02385e2c(void)

{
  return 0;
}



longlong FUN_02385e44(void)

{
  char in_NG;
  char in_ZR;
  char in_CY;
  char in_OV;
  byte in_Q;
  
  return (ulonglong)
         ((uint)(byte)(in_NG << 4 | in_ZR << 3 | in_CY << 2 | in_OV << 1 | in_Q) << 0x1b | 0xc0) <<
         0x20;
}



undefined4 FUN_02385e58(void)

{
  return 0;
}



undefined4 FUN_02385e70(void)

{
  return 0;
}



void FUN_02385e7c(uint param_1)

{
  undefined8 uVar1;
  
  uVar1 = FUN_0238f0dc(param_1,4);
  thunk_EXT_FUN_03803d98((int)uVar1,(int)((ulonglong)uVar1 >> 0x20));
  return;
}



void thunk_EXT_FUN_03803d98(void)

{
                    // WARNING: Could not recover jumptable at 0x02385ea0. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02385ea4)();
  return;
}



void FUN_02385ea8(void)

{
  longlong lVar1;
  
  do {
    lVar1 = FUN_02385e18();
    thunk_EXT_FUN_03803db2((int)lVar1,(int)((ulonglong)lVar1 >> 0x20));
  } while( true );
}



void FUN_02385ebc(void)

{
  FUN_02385fcc(0);
  FUN_02385fcc(1);
  FUN_02385fcc(2);
  FUN_02385fcc(3);
  FUN_02383950(0x40000);
  FUN_023838a8(0xffffffff);
  FUN_02386880();
  FUN_02385f10(0x10);
  FUN_0238f778();
  return;
}



void FUN_02385f10(int param_1)

{
  int iVar1;
  
  do {
    iVar1 = FUN_02386464(0xc,param_1 << 8,0);
  } while (iVar1 != 0);
  return;
}



void FUN_02385f40(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x7f00) == 0x1000) {
    *DAT_02385f78 = 1;
  }
  else {
    FUN_02385ea8();
  }
  return;
}



undefined2 FUN_02385f7c(void)

{
  return *DAT_02385f88;
}



void FUN_02385f8c(void)

{
  if (*DAT_02385fc4 == 0) {
    *DAT_02385fc4 = 1;
    FUN_02386530(0xc,DAT_02385fc8);
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_02385fcc(int param_1)

{
  int iVar1;
  undefined *puVar2;
  
  FUN_02385e18();
  iVar1 = (param_1 * 6 + 5) * 2;
  *(ushort *)(&DMA_Channels_0_to_3 + iVar1) = *(ushort *)(&DMA_Channels_0_to_3 + iVar1) & 0xcdff;
  *(ushort *)(&DMA_Channels_0_to_3 + iVar1) = *(ushort *)(&DMA_Channels_0_to_3 + iVar1) & 0x7fff;
  puVar2 = PTR_DMA_Channels_0_to_3_02386048;
  if (param_1 == 0) {
    _DMA_Channels_0_to_3 = 0;
    *(undefined4 *)(PTR_DMA_Channels_0_to_3_02386048 + 4) = 0;
    *(undefined4 *)(puVar2 + 8) = DAT_0238604c;
  }
  FUN_02385e2c();
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_02386050(int param_1)

{
  undefined *puVar1;
  
  FUN_02385e18();
  puVar1 = PTR_DMA_Channels_0_to_3_023860b8;
  do {
  } while ((*(uint *)(PTR_DMA_Channels_0_to_3_023860b8 + (param_1 * 3 + 2) * 4) & 0x80000000) != 0);
  if (param_1 == 0) {
    _DMA_Channels_0_to_3 = 0;
    *(undefined4 *)(PTR_DMA_Channels_0_to_3_023860b8 + 4) = 0;
    *(undefined4 *)(puVar1 + 8) = DAT_023860bc;
  }
  FUN_02385e2c();
  return;
}



void FUN_023860f4(undefined4 param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  
  iVar1 = (int)param_2 + param_3;
  for (; (int)param_2 < iVar1; param_2 = param_2 + 1) {
    *param_2 = param_1;
  }
  return;
}



void FUN_02386108(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = (int)param_2 + param_3;
  for (; (int)param_2 < iVar2; param_2 = param_2 + 1) {
    uVar1 = *param_1;
    param_1 = param_1 + 1;
    *param_2 = uVar1;
  }
  return;
}



void FUN_0238616c(uint *param_1,uint param_2,uint param_3)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  
  if (param_3 == 0) {
    return;
  }
  if (((uint)param_1 & 1) != 0) {
    *(ushort *)((int)param_1 + -1) = *(ushort *)((int)param_1 + -1) & 0xff | (ushort)(param_2 << 8);
    param_1 = (uint *)((int)param_1 + 1);
    param_3 = param_3 - 1;
    if (param_3 == 0) {
      return;
    }
  }
  if (1 < param_3) {
    uVar3 = param_2 | param_2 << 8;
    puVar1 = param_1;
    if (((uint)param_1 & 2) != 0) {
      puVar1 = (uint *)((int)param_1 + 2);
      *(ushort *)param_1 = (ushort)uVar3;
      param_3 = param_3 - 2;
      if (param_3 == 0) {
        return;
      }
    }
    param_2 = uVar3 | uVar3 << 0x10;
    if ((param_3 & 0xfffffffc) != 0) {
      puVar4 = (uint *)((param_3 & 0xfffffffc) + (int)puVar1);
      puVar2 = puVar1;
      do {
        puVar1 = puVar2 + 1;
        *puVar2 = param_2;
        puVar2 = puVar1;
      } while (puVar1 < puVar4);
    }
    param_1 = puVar1;
    if ((param_3 & 2) != 0) {
      param_1 = (uint *)((int)puVar1 + 2);
      *(ushort *)puVar1 = (ushort)uVar3;
    }
  }
  if ((param_3 & 1) == 0) {
    return;
  }
  *(ushort *)param_1 = (ushort)param_2 & 0xff | *(ushort *)param_1 & 0xff00;
  return;
}



void FUN_02386200(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  ushort *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  
  if (param_3 == 0) {
    return;
  }
  if (((uint)param_2 & 1) != 0) {
    if (((uint)param_1 & 1) == 0) {
      uVar3 = *(ushort *)param_1;
    }
    else {
      uVar3 = *(ushort *)((int)param_1 + -1) >> 8;
    }
    *(ushort *)((int)param_2 + -1) = *(ushort *)((int)param_2 + -1) & 0xff | uVar3 << 8;
    param_1 = (undefined4 *)((int)param_1 + 1);
    param_2 = (undefined4 *)((int)param_2 + 1);
    param_3 = param_3 - 1;
    if (param_3 == 0) {
      return;
    }
  }
  if ((((uint)param_2 ^ (uint)param_1) & 1) == 0) {
    puVar6 = param_2;
    if ((((uint)param_2 ^ (uint)param_1) & 2) == 0) {
      if (1 < param_3) {
        puVar5 = param_1;
        puVar7 = param_2;
        if (((uint)param_2 & 2) != 0) {
          puVar5 = (undefined4 *)((int)param_1 + 2);
          puVar7 = (undefined4 *)((int)param_2 + 2);
          *(ushort *)param_2 = *(ushort *)param_1;
          param_3 = param_3 - 2;
          if (param_3 == 0) {
            return;
          }
        }
        if ((param_3 & 0xfffffffc) != 0) {
          puVar9 = (undefined4 *)((param_3 & 0xfffffffc) + (int)puVar7);
          puVar6 = puVar5;
          puVar8 = puVar7;
          do {
            puVar5 = puVar6 + 1;
            puVar7 = puVar8 + 1;
            *puVar8 = *puVar6;
            puVar6 = puVar5;
            puVar8 = puVar7;
          } while (puVar7 < puVar9);
        }
        param_1 = puVar5;
        puVar6 = puVar7;
        if ((param_3 & 2) != 0) {
          param_1 = (undefined4 *)((int)puVar5 + 2);
          puVar6 = (undefined4 *)((int)puVar7 + 2);
          *(ushort *)puVar7 = *(ushort *)puVar5;
        }
      }
    }
    else if ((param_3 & 0xfffffffe) != 0) {
      puVar5 = param_1;
      puVar7 = param_2;
      do {
        param_1 = (undefined4 *)((int)puVar5 + 2);
        puVar6 = (undefined4 *)((int)puVar7 + 2);
        *(ushort *)puVar7 = *(ushort *)puVar5;
        puVar5 = param_1;
        puVar7 = puVar6;
      } while (puVar6 < (undefined4 *)((param_3 & 0xfffffffe) + (int)param_2));
    }
    if ((param_3 & 1) != 0) {
      *(ushort *)puVar6 = *(ushort *)puVar6 & 0xff00 | *(ushort *)param_1 & 0xff;
      return;
    }
    return;
  }
  puVar4 = (ushort *)((uint)param_1 & 0xfffffffe);
  uVar3 = *puVar4 >> 8;
  uVar2 = (uint)uVar3;
  while (1 < param_3) {
    puVar4 = puVar4 + 1;
    uVar3 = *puVar4;
    uVar1 = (uint)uVar3 << 8;
    *(ushort *)param_2 = (ushort)uVar2 | (ushort)uVar1;
    uVar2 = uVar1 >> 0x10;
    uVar3 = (ushort)((uint)uVar3 >> 8);
    param_2 = (undefined4 *)((int)param_2 + 2);
    param_3 = param_3 - 2;
  }
  if ((param_3 - 2 & 1) != 0) {
    *(ushort *)param_2 = *(ushort *)param_2 & 0xff00 | uVar3;
    return;
  }
  return;
}



undefined4 FUN_02386330(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = *param_2;
  *param_2 = param_1;
  return uVar1;
}



void thunk_EXT_FUN_037fe42c(void)

{
                    // WARNING: Could not recover jumptable at 0x0238633c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02386340)();
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_02386344(void)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  code *pcVar6;
  uint local_28;
  
  puVar4 = PTR_IPCFIFOSEND_02386460;
  iVar3 = DAT_0238645c;
  puVar2 = PTR_REG_IPCFIFOCNT_02386458;
  while( true ) {
    if ((*(ushort *)puVar2 & 0x4000) == 0) {
      FUN_02385e18();
      if ((*(ushort *)puVar2 & 0x100) == 0) {
        local_28 = _IPCFIFORECV;
        FUN_02385e2c();
        iVar5 = 0;
      }
      else {
        FUN_02385e2c();
        iVar5 = -4;
      }
    }
    else {
      *(ushort *)puVar2 = *(ushort *)puVar2 | 0xc000;
      iVar5 = -3;
    }
    if (iVar5 == -4) break;
    if ((iVar5 != -3) && (uVar1 = local_28 & 0x1f, uVar1 != 0)) {
      pcVar6 = *(code **)(iVar3 + uVar1 * 4);
      if (pcVar6 == (code *)0x0) {
        if (-1 < (int)(local_28 << 0x1a)) {
          local_28 = local_28 | 0x20;
          if ((*(ushort *)puVar2 & 0x4000) == 0) {
            FUN_02385e18();
            if ((*(ushort *)puVar2 & 2) == 0) {
              *(uint *)puVar4 = local_28;
              FUN_02385e2c();
            }
            else {
              FUN_02385e2c();
            }
          }
          else {
            *(ushort *)puVar2 = *(ushort *)puVar2 | 0xc000;
          }
        }
      }
      else {
        (*pcVar6)(uVar1,local_28 >> 6,(local_28 << 0x1a) >> 0x1f);
      }
    }
  }
  return;
}



undefined4 FUN_02386464(uint param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  
  if ((*(ushort *)PTR_REG_IPCFIFOCNT_02386500 & 0x4000) == 0) {
    FUN_02385e18();
    if ((*(ushort *)PTR_REG_IPCFIFOCNT_02386500 & 2) == 0) {
      *(uint *)PTR_IPCFIFOSEND_02386504 = param_1 & 0x1f | (param_3 & 1) << 5 | param_2 << 6;
      FUN_02385e2c();
      uVar1 = 0;
    }
    else {
      FUN_02385e2c();
      uVar1 = 0xfffffffe;
    }
  }
  else {
    *(ushort *)PTR_REG_IPCFIFOCNT_02386500 = *(ushort *)PTR_REG_IPCFIFOCNT_02386500 | 0xc000;
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



bool FUN_02386508(uint param_1,int param_2)

{
  return (1 << (param_1 & 0xff) & *(uint *)(DAT_0238652c + param_2 * 4 + 0x388)) != 0;
}



void FUN_02386530(uint param_1,int param_2)

{
  FUN_02385e18();
  *(int *)(DAT_02386594 + param_1 * 4) = param_2;
  if (param_2 == 0) {
    *(uint *)(DAT_02386598 + 0x38c) = *(uint *)(DAT_02386598 + 0x38c) & ~(1 << (param_1 & 0xff));
  }
  else {
    *(uint *)(DAT_02386598 + 0x38c) = *(uint *)(DAT_02386598 + 0x38c) | 1 << (param_1 & 0xff);
  }
  FUN_02385e2c();
  return;
}



void FUN_0238659c(void)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  
  FUN_02385e18();
  if (*DAT_0238665c == 0) {
    *DAT_0238665c = 1;
    iVar3 = 0;
    *(undefined4 *)(DAT_02386660 + 0x38c) = 0;
    iVar1 = DAT_02386664;
    do {
      *(undefined4 *)(iVar1 + iVar3 * 4) = 0;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x20);
    *(short *)PTR_REG_IPCFIFOCNT_0238666c = (short)DAT_02386668;
    FUN_023838a8(0x40000);
    FUN_023839d0(0x40000,DAT_02386670);
    FUN_02383918(0x40000);
    puVar2 = PTR_REG_IPCSYNC_02386674;
    for (uVar4 = 8; -1 < (int)uVar4; uVar4 = uVar4 - 1) {
      *(short *)puVar2 = (short)(uVar4 << 8);
      FUN_02385e7c(1000);
      if ((*(ushort *)puVar2 & 0xf) != uVar4) {
        uVar4 = 8;
      }
    }
  }
  FUN_02385e2c();
  return;
}



void FUN_02386678(undefined2 param_1)

{
                    // WARNING: Could not recover jumptable at 0x0238668c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02386690)(0xc000,param_1);
  return;
}



void FUN_02386694(ushort param_1,ushort param_2)

{
  *(ushort *)PTR_REG_Debug_RCNT_023866b0 =
       param_2 | ~param_1 & *(ushort *)PTR_REG_Debug_RCNT_023866b0;
  return;
}



void FUN_023866b4(void)

{
  ushort uVar1;
  
  uVar1 = 0;
  FUN_02386678(0x8000);
  if ((*(ushort *)PTR_REG_EXTKEYIN_023866ec & 0x80) != 0) {
    uVar1 = 0x8000;
  }
  *DAT_023866f0 = uVar1 | (ushort)((*(ushort *)PTR_REG_EXTKEYIN_023866ec & 0xb) << 10);
  return;
}



undefined4 FUN_023866f4(void)

{
  short sVar1;
  undefined4 uVar2;
  longlong lVar3;
  
  sVar1 = FUN_02385258();
  if ((sVar1 == 0) || (sVar1 = FUN_023856cc(), sVar1 == 0)) {
    uVar2 = 0;
  }
  else if (*DAT_02386784 == 0) {
    FUN_023856bc(DAT_02386788);
    lVar3 = FUN_02385120();
    FUN_0238549c(DAT_02386788,(int)(lVar3 + (ulonglong)DAT_02386790),
                 (int)(lVar3 + (ulonglong)DAT_02386790 >> 0x20),DAT_02386790,0,DAT_0238678c,0);
    uVar2 = 1;
    *DAT_02386784 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



void FUN_02386794(byte param_1,int param_2,int param_3,int param_4)

{
  *DAT_023867c8 =
       param_1 | ((*DAT_023867c8 & 0x80) != 0) << 7 | (byte)(param_4 << 5) | (byte)(param_3 << 4) |
                 (byte)(param_2 << 2);
  return;
}



void FUN_023867cc(undefined param_1)

{
  *PTR_REG_SOUNDCNT_023867d8 = param_1;
  return;
}



void FUN_023867dc(void)

{
  *(ushort *)PTR_REG_POWCNT2_0238681c = *(ushort *)PTR_REG_POWCNT2_0238681c | 1;
  FUN_0238d554(1);
  thunk_EXT_FUN_03803dbe(0x100);
  FUN_02385e7c(DAT_02386820);
  FUN_023868ec();
  return;
}



void thunk_EXT_FUN_03803dbe(void)

{
                    // WARNING: Could not recover jumptable at 0x02386828. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_0238682c)();
  return;
}



void FUN_02386830(void)

{
  FUN_023868d4();
  thunk_EXT_FUN_03803dc6(0x80);
  FUN_02385e7c(0x40000);
  FUN_0238d528(1);
  *(ushort *)PTR_REG_POWCNT2_02386870 = *(ushort *)PTR_REG_POWCNT2_02386870 & 0xfffe;
  return;
}



void thunk_EXT_FUN_03803dc6(void)

{
                    // WARNING: Could not recover jumptable at 0x02386878. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_0238687c)();
  return;
}



void FUN_02386880(void)

{
  int iVar1;
  
  FUN_023868d4();
  iVar1 = 0;
  do {
    FUN_02386b7c(iVar1,1);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x10);
  *PTR_REG_SNDCAP0CNT_023868cc = 0;
  *PTR_REG_SNDCAP1CNT_023868d0 = 0;
  return;
}



void FUN_023868d4(void)

{
  *DAT_023868e8 = *DAT_023868e8 & 0x7f;
  return;
}



void FUN_023868ec(void)

{
  *DAT_02386900 = *DAT_02386900 | 0x80;
  return;
}



int FUN_02386904(int param_1,int param_2)

{
  if (param_2 < 0x18) {
    return param_1 * (*DAT_02386968 * (param_2 + 0x28) + (DAT_0238696c - *DAT_02386968) * 0x40) >>
           0x15;
  }
  if (param_2 < 0x69) {
    return param_1;
  }
  return param_1 * (-*DAT_02386968 * (param_2 + -0x28) + (*DAT_02386968 + DAT_0238696c) * 0x40) >>
         0x15;
}



void FUN_02386970(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  *DAT_023869c8 = param_1;
  uVar2 = DAT_023869d0;
  iVar1 = DAT_023869cc;
  uVar4 = 0;
  do {
    if ((1 << (uVar4 & 0xff) & uVar2) != 0) {
      iVar3 = FUN_02386904((uint)*(byte *)(iVar1 + uVar4),(uint)(byte)(&DAT_04000402)[uVar4 * 0x10])
      ;
      (&Sound_Channels_0_to_15)[uVar4 * 0x10] = (char)iVar3;
    }
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 0x10);
  return;
}



undefined4 FUN_023869d4(int param_1)

{
  return *(undefined4 *)(&Sound_Channels_0_to_15 + param_1 * 0x10);
}



void FUN_023869e4(int param_1)

{
  int iVar1;
  int iVar2;
  
  *DAT_02386a40 = param_1;
  iVar1 = DAT_02386a44;
  if (-1 < param_1) {
    iVar1 = 0;
    do {
      (&DAT_04000402)[iVar1 * 0x10] = (char)param_1;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x10);
    return;
  }
  iVar2 = 0;
  do {
    (&DAT_04000402)[iVar2 * 0x10] = *(undefined *)(iVar1 + iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  return;
}



bool FUN_02386a48(int param_1)

{
  return (*(byte *)(param_1 * 0x10 + 0x4000403) & 0x80) != 0;
}



void FUN_02386a64(uint param_1,int param_2)

{
  int iVar1;
  
  *(char *)(DAT_02386acc + param_1) = (char)param_2;
  if (-1 < *DAT_02386ad0) {
    param_2 = *DAT_02386ad0;
  }
  (&DAT_04000402)[param_1 * 0x10] = (char)param_2;
  if ((0 < *DAT_02386ad4) && ((1 << (param_1 & 0xff) & DAT_02386ad8) != 0)) {
    iVar1 = FUN_02386904((uint)*(byte *)(DAT_02386adc + param_1),param_2);
    (&Sound_Channels_0_to_15)[param_1 * 0x10] = (char)iVar1;
  }
  return;
}



void FUN_02386ae0(int param_1,short param_2)

{
  *(short *)(param_1 * 0x10 + 0x4000408) = -param_2;
  return;
}



void FUN_02386af8(uint param_1,int param_2,int param_3)

{
  *(char *)(DAT_02386b70 + param_1) = (char)param_2;
  if ((0 < *DAT_02386b74) && ((1 << (param_1 & 0xff) & DAT_02386b78) != 0)) {
    param_2 = FUN_02386904(param_2,(uint)(byte)(&DAT_04000402)[param_1 * 0x10]);
  }
  *(ushort *)(&Sound_Channels_0_to_15 + param_1 * 0x10) = (ushort)param_2 | (ushort)(param_3 << 8);
  return;
}



void FUN_02386b7c(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(&Sound_Channels_0_to_15 + param_1 * 0x10) & 0x7fffffff;
  if ((param_2 & 1) != 0) {
    uVar1 = uVar1 | 0x8000;
  }
  *(uint *)(PTR_Sound_Channels_0_to_15_02386ba4 + param_1 * 0x10) = uVar1;
  return;
}



void FUN_02386ba8(uint param_1,uint param_2,int param_3,short param_4,int param_5)

{
  *(char *)(DAT_02386c44 + param_1) = (char)param_5;
  if (-1 < *DAT_02386c48) {
    param_5 = *DAT_02386c48;
  }
  *(char *)(DAT_02386c4c + param_1) = (char)param_2;
  if ((0 < *DAT_02386c50) && ((1 << (param_1 & 0xff) & DAT_02386c54) != 0)) {
    param_2 = FUN_02386904(param_2,param_5);
  }
  *(uint *)(&Sound_Channels_0_to_15 + param_1 * 0x10) =
       param_2 | param_5 << 0x10 | 0x60000000U | param_3 << 8;
  *(short *)(param_1 * 0x10 + 0x4000408) = -param_4;
  return;
}



void FUN_02386c58(uint param_1,int param_2,uint param_3,int param_4,short param_5,int param_6)

{
  *(char *)(DAT_02386cfc + param_1) = (char)param_6;
  if (-1 < *DAT_02386d00) {
    param_6 = *DAT_02386d00;
  }
  *(char *)(DAT_02386d04 + param_1) = (char)param_3;
  if ((0 < *DAT_02386d08) && ((1 << (param_1 & 0xff) & DAT_02386d0c) != 0)) {
    param_3 = FUN_02386904(param_3,param_6);
  }
  *(uint *)(&Sound_Channels_0_to_15 + param_1 * 0x10) =
       param_3 | param_2 << 0x18 | 0x60000000U | param_6 << 0x10 | param_4 << 8;
  *(short *)(param_1 * 0x10 + 0x4000408) = -param_5;
  return;
}



void FUN_02386d10(uint param_1,undefined4 param_2,int param_3,int param_4,undefined2 param_5,
                 undefined4 param_6,uint param_7,int param_8,short param_9,int param_10)

{
  int iVar1;
  
  iVar1 = param_1 * 0x10;
  *(char *)(DAT_02386dcc + param_1) = (char)param_10;
  if (-1 < *DAT_02386dd0) {
    param_10 = *DAT_02386dd0;
  }
  *(char *)(DAT_02386dd4 + param_1) = (char)param_7;
  if ((0 < *DAT_02386dd8) && ((1 << (param_1 & 0xff) & DAT_02386ddc) != 0)) {
    param_7 = FUN_02386904(param_7,param_10);
  }
  *(uint *)(&Sound_Channels_0_to_15 + iVar1) =
       param_7 | param_3 << 0x1d | param_4 << 0x1b | param_10 << 0x10 | param_8 << 8;
  *(short *)(iVar1 + 0x4000408) = -param_9;
  *(undefined2 *)(iVar1 + 0x400040a) = param_5;
  *(undefined4 *)(iVar1 + 0x400040c) = param_6;
  *(undefined4 *)(iVar1 + 0x4000404) = param_2;
  return;
}



uint FUN_02386de0(void)

{
  uint uVar1;
  
  uVar1 = *DAT_02386e08 * DAT_02386e0c + DAT_02386e10;
  *DAT_02386e08 = uVar1;
  return uVar1 >> 0x10;
}



int FUN_02386e14(int param_1)

{
  if (param_1 < 0x20) {
    return (int)*(char *)(DAT_02386e7c + param_1);
  }
  if (0x3f < param_1) {
    if (0x5f < param_1) {
      return *(char *)(DAT_02386e7c + (0x20 - (param_1 + -0x60))) * -0x1000000 >> 0x18;
    }
    return *(char *)(DAT_02386e7c + param_1 + -0x40) * -0x1000000 >> 0x18;
  }
  return (int)*(char *)(DAT_02386e7c + (0x40 - param_1));
}



uint FUN_02386e80(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = DAT_02386ef0;
  if ((DAT_02386ef0 <= param_1) && (iVar2 = param_1, 0 < param_1)) {
    iVar2 = 0;
  }
  uVar1 = thunk_EXT_FUN_03803e0c(iVar2 + DAT_02386ef4);
  if (iVar2 < -0xf0) {
    iVar2 = 3;
  }
  else if (iVar2 < -0x78) {
    iVar2 = 2;
  }
  else if (iVar2 < -0x3c) {
    iVar2 = 1;
  }
  else {
    iVar2 = 0;
  }
  return uVar1 & 0xffff | iVar2 << 8;
}



void thunk_EXT_FUN_03803e0c(void)

{
                    // WARNING: Could not recover jumptable at 0x02386efc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02386f00)();
  return;
}



uint FUN_02386f04(uint param_1,int param_2)

{
  longlong lVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  
  iVar6 = 0;
  for (iVar2 = -param_2; iVar2 < 0; iVar2 = iVar2 + 0x300) {
    iVar6 = iVar6 + -1;
  }
  for (; 0x2ff < iVar2; iVar2 = iVar2 + -0x300) {
    iVar6 = iVar6 + 1;
  }
  uVar3 = thunk_EXT_FUN_03803e08();
  lVar1 = (ulonglong)param_1 * (ulonglong)(uVar3 + 0x10000);
  uVar5 = (uint)lVar1;
  uVar4 = (0xfffeffff < uVar3) * param_1 +
          (uVar3 + 0x10000) * ((int)param_1 >> 0x1f) + (int)((ulonglong)lVar1 >> 0x20);
  uVar3 = iVar6 - 0x10;
  if ((int)uVar3 < 1) {
    uVar3 = -uVar3;
    uVar7 = uVar4 >> (uVar3 & 0xff);
    uVar8 = uVar5 >> (uVar3 & 0xff) | uVar4 << (iVar6 + 0x10U & 0xff) |
            uVar4 >> (uVar3 - 0x20 & 0xff);
  }
  else {
    if (0x1f < (int)uVar3) {
      return DAT_02387028;
    }
    uVar7 = -uVar3 + 0x20;
    if ((uVar4 & (-1 << (uVar7 & 0xff) | 0xffffffffU >> (0x20 - uVar7 & 0xff) |
                 -1 << (-uVar3 & 0xff))) != 0 || (uVar5 & -1 << (uVar7 & 0xff)) != 0) {
      return DAT_02387028;
    }
    uVar8 = uVar5 << (uVar3 & 0xff);
    uVar7 = uVar4 << (uVar3 & 0xff) | uVar5 >> (uVar7 & 0xff) | uVar5 << (iVar6 - 0x30U & 0xff);
  }
  if (uVar7 == 0 && uVar8 < 0x10) {
    uVar8 = 0x10;
  }
  else if ((uVar7 != 0 || DAT_02387028 <= uVar8) && (uVar7 != 0 || uVar8 != DAT_02387028)) {
    uVar8 = DAT_02387028;
  }
  return uVar8 & 0xffff;
}



void thunk_EXT_FUN_03803e08(void)

{
                    // WARNING: Could not recover jumptable at 0x02387030. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02387034)();
  return;
}



void FUN_02387038(void)

{
  int iVar1;
  
  FUN_023871c0();
  FUN_0238818c();
  FUN_02389dc4();
  FUN_0238a3d4();
  FUN_023868ec();
  FUN_02386794(0,0,0,0);
  FUN_023867cc(0x7f);
  FUN_02387168();
  do {
    iVar1 = FUN_02387128();
    FUN_02387fa0();
    FUN_0238a778();
    FUN_02389d24((uint)(iVar1 == 1));
    FUN_02387c94((uint)(iVar1 == 1));
    FUN_0238a164();
    FUN_02386de0();
  } while( true );
}



void FUN_023870b8(void)

{
  int iVar1;
  
  iVar1 = FUN_023846e4(DAT_023870f8,1,0);
  if (iVar1 == 0) {
    (**DAT_02387100)(DAT_023870fc);
  }
  return;
}



void FUN_02387104(void)

{
  return;
}



void FUN_02387108(void)

{
  return;
}



void FUN_0238710c(void)

{
                    // WARNING: Could not recover jumptable at 0x0238711c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02387124)(DAT_02387120,2,0);
  return;
}



undefined4 FUN_02387128(void)

{
  undefined4 local_8 [2];
  
  FUN_02384644(DAT_02387150,local_8,1);
  return local_8[0];
}



void FUN_02387154(void)

{
                    // WARNING: Could not recover jumptable at 0x0238715c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02387164)(DAT_02387160);
  return;
}



void FUN_02387168(void)

{
  longlong lVar1;
  
  lVar1 = FUN_02385120();
  FUN_0238549c(DAT_023871bc,(int)(lVar1 + 0x10000),(int)((ulonglong)(lVar1 + 0x10000) >> 0x20),
               DAT_023871b8,0,DAT_023871b4,0);
  return;
}



void FUN_023871c0(void)

{
  FUN_02384778(DAT_023871ec,DAT_023871f0,8);
  FUN_023856bc(DAT_023871f4);
  return;
}



void FUN_023871f8(undefined4 param_1)

{
  undefined4 extraout_r1;
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 0;
  iVar2 = DAT_0238723c;
  FUN_023841f8(DAT_02387234,DAT_02387238,0,DAT_0238723c,0x400,param_1);
  FUN_02384090((int)DAT_02387234,extraout_r1,uVar1,iVar2);
  return;
}



void FUN_02387240(undefined4 param_1)

{
  if (*DAT_02387274 == 0) {
    *DAT_02387274 = 1;
    FUN_0238abf0();
    FUN_023871f8(param_1);
  }
  return;
}



bool FUN_02387278(int param_1)

{
  return ((&REG_SNDCAP0CNT)[param_1] & 0x80) != 0;
}



void FUN_02387290(int param_1,int param_2,undefined4 param_3,undefined2 param_4,int param_5,
                 int param_6,byte param_7)

{
  (&REG_SNDCAP0CNT)[param_1] =
       param_7 | (byte)(param_2 << 3) | (param_5 == 0) << 2 | (byte)(param_6 << 1);
  *(undefined4 *)(&REG_SNDCAP0DAD + param_1 * 8) = param_3;
  *(undefined2 *)(&REG_SNDCAP0LEN + param_1 * 8) = param_4;
  return;
}



uint FUN_023872e8(int param_1,int param_2)

{
  char cVar1;
  ulonglong uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = FUN_023875ac(param_1 + 0x28);
  uVar4 = (int)uVar3 >> 0x1f;
  if (uVar3 != 0) {
    cVar1 = *(char *)(param_1 + 0x28);
    if (cVar1 == '\0') {
      uVar4 = uVar4 << 6 | uVar3 >> 0x1a;
      uVar3 = uVar3 << 6;
    }
    else if (cVar1 == '\x01') {
      uVar2 = (ulonglong)uVar3;
      uVar3 = (uint)(uVar2 * 0x3c);
      uVar4 = uVar4 * 0x3c + (int)(uVar2 * 0x3c >> 0x20);
    }
    else if (cVar1 == '\x02') {
      uVar4 = uVar4 << 6 | uVar3 >> 0x1a;
      uVar3 = uVar3 << 6;
    }
    uVar3 = uVar3 >> 0xe | uVar4 << 0x12;
  }
  if (param_2 != 0) {
    FUN_023875fc(param_1 + 0x28);
  }
  return uVar3;
}



undefined8 FUN_02387384(int param_1,int param_2)

{
  longlong lVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  ulonglong uVar5;
  
  iVar3 = param_2;
  if (*(short *)(param_1 + 0x32) == 0) {
    uVar2 = 0;
  }
  else {
    uVar4 = *(uint *)(param_1 + 0x18);
    if (*(int *)(param_1 + 0x14) < (int)uVar4) {
      lVar1 = (longlong)(int)*(short *)(param_1 + 0x32) *
              (longlong)(int)(uVar4 - *(int *)(param_1 + 0x14));
      uVar5 = FUN_0238ef2c((uint)lVar1,(uint)((ulonglong)lVar1 >> 0x20),uVar4,(int)uVar4 >> 0x1f);
      iVar3 = (int)(uVar5 >> 0x20);
      uVar2 = (undefined4)uVar5;
      if ((param_2 != 0) &&
         (iVar3 = -((int)((uint)*(byte *)(param_1 + 3) << 0x1d) >> 0x1f), iVar3 != 0)) {
        iVar3 = *(int *)(param_1 + 0x14) + 1;
        *(int *)(param_1 + 0x14) = iVar3;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return CONCAT44(iVar3,uVar2);
}



undefined4 FUN_023873f4(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = (int)((*(ushort *)(param_1 + 0x24) & 0xff) << 4) >>
          *(sbyte *)(DAT_02387450 + ((int)(uint)*(ushort *)(param_1 + 0x24) >> 8));
  iVar2 = (int)((*(ushort *)(param_2 + 0x24) & 0xff) << 4) >>
          *(sbyte *)(DAT_02387450 + ((int)(uint)*(ushort *)(param_2 + 0x24) >> 8));
  if (iVar1 == iVar2) {
    uVar3 = 0;
  }
  else if (iVar1 < iVar2) {
    uVar3 = 1;
  }
  else {
    uVar3 = 0xffffffff;
  }
  return uVar3;
}



void FUN_02387454(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x10) = DAT_0238749c;
  *(undefined *)(param_1 + 2) = 0;
  *(undefined4 *)(param_1 + 0x34) = param_2;
  FUN_02387660(param_1 + 0x28);
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 2;
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xfe | 1;
  return;
}



void FUN_023874a0(int param_1,undefined4 param_2,undefined4 param_3,undefined param_4)

{
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x48) = param_2;
  *(undefined4 *)(param_1 + 0x4c) = param_3;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined *)(param_1 + 0x22) = param_4;
  *(undefined2 *)(param_1 + 0x24) = 0x7f;
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xfd;
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 4;
  *(undefined *)(param_1 + 8) = 0x3c;
  *(undefined *)(param_1 + 5) = 0x3c;
  *(undefined *)(param_1 + 9) = 0x7f;
  *(undefined *)(param_1 + 10) = 0;
  *(undefined2 *)(param_1 + 0xc) = 0;
  *(undefined2 *)(param_1 + 6) = 0;
  *(undefined2 *)(param_1 + 0xe) = 0;
  *(undefined *)(param_1 + 0xb) = 0;
  *(undefined *)(param_1 + 4) = 0x7f;
  *(undefined2 *)(param_1 + 0x32) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  FUN_02387ae0(param_1,0x7f);
  FUN_02387ac4(param_1,0x7f);
  FUN_02387abc(param_1,0x7f);
  FUN_02387aa0(param_1,0x7f);
  FUN_02387670((undefined *)(param_1 + 0x28));
  return;
}



undefined8 FUN_0238754c(int param_1)

{
  uint uVar1;
  undefined8 uVar2;
  
  uVar1 = DAT_023875a8;
  if (param_1 != 0x7f) {
    if (param_1 == 0x7e) {
      uVar1 = 0x3c00;
    }
    else if (param_1 < 0x32) {
      uVar1 = param_1 * 2 + 1U & 0xffff;
    }
    else {
      uVar2 = FUN_0238f0dc(0x1e00,0x7e - param_1);
      param_1 = (int)((ulonglong)uVar2 >> 0x20);
      uVar1 = (uint)uVar2 & 0xffff;
    }
  }
  return CONCAT44(param_1,uVar1);
}



int FUN_023875ac(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 2) == '\0') {
    iVar1 = 0;
  }
  else if (*(ushort *)(param_1 + 6) < *(ushort *)(param_1 + 4)) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_02386e14((uint)(*(ushort *)(param_1 + 8) >> 8));
    iVar1 = (uint)*(byte *)(param_1 + 3) * (uint)*(byte *)(param_1 + 2) * iVar1;
  }
  return iVar1;
}



void FUN_023875fc(int param_1)

{
  uint uVar1;
  
  if (*(ushort *)(param_1 + 4) <= *(ushort *)(param_1 + 6)) {
    for (uVar1 = (uint)*(ushort *)(param_1 + 8) + (uint)*(byte *)(param_1 + 1) * 0x40 >> 8;
        0x7f < uVar1; uVar1 = uVar1 - 0x80) {
    }
    *(ushort *)(param_1 + 8) = *(short *)(param_1 + 8) + (ushort)*(byte *)(param_1 + 1) * 0x40;
    *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) & 0xff;
    *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) | (ushort)(uVar1 << 8);
    return;
  }
  *(ushort *)(param_1 + 6) = *(ushort *)(param_1 + 6) + 1;
  return;
}



void FUN_02387660(int param_1)

{
  *(undefined2 *)(param_1 + 8) = 0;
  *(undefined2 *)(param_1 + 6) = 0;
  return;
}



void FUN_02387670(undefined *param_1)

{
  *param_1 = 0;
  param_1[2] = 0;
  param_1[3] = 1;
  param_1[1] = 0x10;
  *(undefined2 *)(param_1 + 4) = 0;
  return;
}



void FUN_02387694(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = DAT_02387718;
  uVar3 = 0;
  do {
    iVar2 = uVar3 * 0x54 + iVar1;
    if (((((int)((uint)*(byte *)(iVar2 + 3) << 0x1f) < 0) && (*(char *)(iVar2 + 1) == '\0')) &&
        (param_1 <= *(uint *)(iVar2 + 0x44))) && (*(uint *)(iVar2 + 0x44) <= param_2)) {
      *(byte *)(iVar2 + 3) = *(byte *)(iVar2 + 3) & 0xfd;
      FUN_02386b7c(uVar3,0);
    }
    uVar3 = uVar3 + 1 & 0xff;
  } while (uVar3 < 0x10);
  return;
}



undefined4 FUN_0238771c(uint param_1)

{
  undefined4 uVar1;
  
  if ((param_1 & 1) == 0) {
    uVar1 = *DAT_02387738;
  }
  else {
    uVar1 = *DAT_02387734;
  }
  return uVar1;
}



void FUN_0238773c(uint param_1,uint param_2)

{
  if ((param_2 & 1) != 0) {
    *DAT_02387774 = *DAT_02387774 & ~param_1;
    return;
  }
  *DAT_02387770 = *DAT_02387770 & ~param_1;
  return;
}



void FUN_02387778(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = 0;
  for (uVar2 = param_1; ((int)uVar1 < 0x10 && (uVar2 != 0)); uVar2 = uVar2 >> 1) {
    if (((uVar2 & 1) != 0) &&
       (iVar3 = uVar1 * 0x54 + DAT_02387864, (*DAT_02387868 & 1 << (uVar1 & 0xff)) == 0)) {
      if (*(code **)(iVar3 + 0x48) != (code *)0x0) {
        (**(code **)(iVar3 + 0x48))(iVar3,0,*(undefined4 *)(iVar3 + 0x4c));
      }
      FUN_02386b7c(uVar1,0);
      *(undefined *)(iVar3 + 0x22) = 0;
      FUN_02387938(iVar3);
      *(byte *)(iVar3 + 3) = *(byte *)(iVar3 + 3) & 7;
      *(byte *)(iVar3 + 3) = *(byte *)(iVar3 + 3) & 0xfe;
    }
    uVar1 = uVar1 + 1;
  }
  if ((param_2 & 1) == 0) {
    *DAT_02387868 = *DAT_02387868 | param_1;
  }
  else {
    *DAT_0238786c = *DAT_0238786c | param_1;
  }
  return;
}



void FUN_02387870(uint param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = DAT_02387930;
  uVar2 = 0;
  for (; ((int)uVar2 < 0x10 && (param_1 != 0)); param_1 = param_1 >> 1) {
    if (((param_1 & 1) != 0) &&
       (iVar3 = uVar2 * 0x54 + iVar1, (*DAT_02387934 & 1 << (uVar2 & 0xff)) == 0)) {
      if (*(code **)(iVar3 + 0x48) != (code *)0x0) {
        (**(code **)(iVar3 + 0x48))(iVar3,0,*(undefined4 *)(iVar3 + 0x4c));
      }
      FUN_02386b7c(uVar2,0);
      *(undefined *)(iVar3 + 0x22) = 0;
      FUN_02387938(iVar3);
      *(byte *)(iVar3 + 3) = *(byte *)(iVar3 + 3) & 7;
      *(byte *)(iVar3 + 3) = *(byte *)(iVar3 + 3) & 0xfe;
    }
    uVar2 = uVar2 + 1;
  }
  return;
}



void FUN_02387938(int param_1)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(undefined4 *)(param_1 + 0x4c) = 0;
  }
  return;
}



int FUN_0238794c(uint param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  uVar6 = param_1 & ~*DAT_02387a74;
  if (param_3 == 0) {
    uVar6 = uVar6 & ~*DAT_02387a78;
  }
  iVar4 = 0;
  iVar5 = 0;
  do {
    iVar2 = iVar5;
    if (((uVar6 & 1 << (uint)*(byte *)(DAT_02387a7c + iVar4)) != 0) &&
       (iVar3 = (uint)*(byte *)(DAT_02387a7c + iVar4) * 0x54 + DAT_02387a80, iVar2 = iVar3,
       iVar5 != 0)) {
      iVar2 = iVar5;
      if ((*(byte *)(iVar3 + 0x22) <= *(byte *)(iVar5 + 0x22)) &&
         ((*(byte *)(iVar3 + 0x22) != *(byte *)(iVar5 + 0x22) ||
          (iVar1 = FUN_023873f4(iVar5,iVar3), iVar1 < 0)))) {
        iVar2 = iVar3;
      }
    }
    iVar4 = iVar4 + 1;
    iVar5 = iVar2;
  } while (iVar4 < 0x10);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else if (param_2 < (int)(uint)*(byte *)(iVar2 + 0x22)) {
    iVar2 = 0;
  }
  else {
    if (*(code **)(iVar2 + 0x48) != (code *)0x0) {
      (**(code **)(iVar2 + 0x48))(iVar2,0,*(undefined4 *)(iVar2 + 0x4c));
    }
    *(byte *)(iVar2 + 3) = *(byte *)(iVar2 + 3) & 7 | 0x10;
    *(byte *)(iVar2 + 3) = *(byte *)(iVar2 + 3) & 0xfe;
    FUN_023874a0(iVar2,param_4,param_5,(char)param_2);
  }
  return iVar2;
}



byte FUN_02387a84(int param_1)

{
  return (byte)(((uint)*(byte *)(param_1 + 3) << 0x1f) >> 0x1f);
}



void FUN_02387a94(int param_1)

{
  *(undefined *)(param_1 + 2) = 3;
  return;
}



void FUN_02387aa0(int param_1,int param_2)

{
  undefined8 uVar1;
  
  uVar1 = FUN_0238754c(param_2);
  *(short *)(param_1 + 0x20) = (short)uVar1;
  return;
}



void FUN_02387abc(int param_1,undefined param_2)

{
  *(undefined *)(param_1 + 0x1d) = param_2;
  return;
}



void FUN_02387ac4(int param_1,int param_2)

{
  undefined8 uVar1;
  
  uVar1 = FUN_0238754c(param_2);
  *(short *)(param_1 + 0x1e) = (short)uVar1;
  return;
}



void FUN_02387ae0(int param_1,int param_2)

{
  if (param_2 < 0x6d) {
    *(char *)(param_1 + 0x1c) = -1 - (char)param_2;
  }
  else {
    *(undefined *)(param_1 + 0x1c) = *(undefined *)(DAT_02387b00 + (0x7f - param_2));
  }
  return;
}



int FUN_02387b04(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  
  if (param_2 != 0) {
    switch(*(undefined *)(param_1 + 2)) {
    case 0:
      *(int *)(param_1 + 0x10) =
           -((int)(-*(int *)(param_1 + 0x10) * (uint)*(byte *)(param_1 + 0x1c)) >> 8);
      if (*(int *)(param_1 + 0x10) == 0) {
        *(undefined *)(param_1 + 2) = 1;
      }
      break;
    case 1:
      iVar2 = (int)*(short *)(DAT_02387bb4 + (uint)*(byte *)(param_1 + 0x1d) * 2);
      iVar1 = iVar2 * 0x80;
      *(uint *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) - (uint)*(ushort *)(param_1 + 0x1e);
      iVar3 = *(int *)(param_1 + 0x10);
      bVar6 = SBORROW4(iVar3,iVar1);
      bVar4 = iVar3 + iVar2 * -0x80 < 0;
      bVar5 = iVar3 == iVar1;
      if (bVar5 || bVar4 != bVar6) {
        *(int *)(param_1 + 0x10) = iVar1;
      }
      if (bVar5 || bVar4 != bVar6) {
        iVar3 = 2;
      }
      if (bVar5 || bVar4 != bVar6) {
        *(char *)(param_1 + 2) = (char)iVar3;
      }
      break;
    case 2:
      break;
    case 3:
      *(uint *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) - (uint)*(ushort *)(param_1 + 0x20);
    }
  }
  return *(int *)(param_1 + 0x10) >> 7;
}



undefined4 FUN_02387bb8(byte *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*param_1 < 0xe) {
    uVar1 = 0;
  }
  else if (*param_1 < 0x10) {
    param_1[1] = 2;
    *(short *)(param_1 + 0x3c) = (short)DAT_02387c00;
    FUN_02387454((int)param_1,param_2);
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined4 FUN_02387c04(byte *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if (*param_1 < 8) {
    uVar1 = 0;
  }
  else if (*param_1 < 0xe) {
    param_1[1] = 1;
    *(undefined4 *)(param_1 + 0x44) = param_2;
    *(short *)(param_1 + 0x3c) = (short)DAT_02387c54;
    FUN_02387454((int)param_1,param_3);
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



undefined4 FUN_02387c58(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  *(undefined *)(param_1 + 1) = 0;
  uVar1 = param_2[1];
  uVar2 = param_2[2];
  *(undefined4 *)(param_1 + 0x38) = *param_2;
  *(undefined4 *)(param_1 + 0x3c) = uVar1;
  *(undefined4 *)(param_1 + 0x40) = uVar2;
  *(undefined4 *)(param_1 + 0x44) = param_3;
  FUN_02387454(param_1,param_4);
  return 1;
}



void FUN_02387c94(int param_1)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  short sVar4;
  bool bVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  undefined8 uVar15;
  uint local_40;
  uint local_30;
  
  iVar9 = 0;
  local_30 = 0;
  local_40 = 0;
  do {
    iVar10 = iVar9 * 0x54 + DAT_02387f90;
    uVar8 = (uint)*(byte *)(iVar10 + 3);
    if ((int)(uVar8 << 0x1f) < 0) {
      if ((int)(uVar8 << 0x1e) < 0) {
        *(byte *)(iVar10 + 3) =
             *(byte *)(iVar10 + 3) & 7 | (byte)(((uVar8 << 0x18) >> 0x1b | 1) << 3);
        *(byte *)(iVar10 + 3) = *(byte *)(iVar10 + 3) & 0xfd;
      }
      else {
        bVar5 = FUN_02386a48(iVar9);
        if (!bVar5) {
          if (*(code **)(iVar10 + 0x48) == (code *)0x0) {
            *(undefined *)(iVar10 + 0x22) = 0;
          }
          else {
            (**(code **)(iVar10 + 0x48))(iVar10,1,*(undefined4 *)(iVar10 + 0x4c));
          }
          *(undefined2 *)(iVar10 + 0x24) = 0;
          *(byte *)(iVar10 + 3) = *(byte *)(iVar10 + 3) & 0xfe;
          goto LAB_02387f78;
        }
      }
      sVar4 = *(short *)(DAT_02387f94 + (uint)*(byte *)(iVar10 + 9) * 2);
      bVar1 = *(byte *)(iVar10 + 8);
      bVar2 = *(byte *)(iVar10 + 5);
      iVar6 = FUN_02387b04(iVar10,param_1);
      iVar6 = sVar4 + iVar6;
      uVar15 = FUN_02387384(iVar10,param_1);
      iVar14 = ((uint)bVar1 - (uint)bVar2) * 0x40 + (int)uVar15;
      uVar7 = FUN_023872e8(iVar10,param_1);
      cVar3 = *(char *)(iVar10 + 0x28);
      uVar8 = local_40;
      if (cVar3 == '\0') {
        iVar14 = iVar14 + uVar7;
      }
      else if (cVar3 == '\x01') {
        iVar6 = iVar6 + uVar7;
      }
      else if (cVar3 == '\x02') {
        uVar8 = uVar7;
      }
      iVar11 = uVar8 + (int)*(char *)(iVar10 + 10);
      if (*(byte *)(iVar10 + 4) != 0x7f) {
        iVar11 = (int)(iVar11 * (uint)*(byte *)(iVar10 + 4) + 0x40) >> 7;
      }
      iVar6 = iVar6 + *(short *)(iVar10 + 0xc) + (int)*(short *)(iVar10 + 6);
      sVar4 = *(short *)(iVar10 + 0xe);
      cVar3 = *(char *)(iVar10 + 0xb);
      if ((*(char *)(iVar10 + 2) == '\x03') && (iVar6 <= DAT_02387f98)) {
        *(byte *)(iVar10 + 3) = *(byte *)(iVar10 + 3) & 7 | 0x10;
        if (*(code **)(iVar10 + 0x48) == (code *)0x0) {
          *(undefined *)(iVar10 + 0x22) = 0;
        }
        else {
          (**(code **)(iVar10 + 0x48))(iVar10,1,*(undefined4 *)(iVar10 + 0x4c));
        }
        *(undefined2 *)(iVar10 + 0x24) = 0;
        *(byte *)(iVar10 + 3) = *(byte *)(iVar10 + 3) & 0xfe;
      }
      else {
        uVar7 = FUN_02386e80(iVar6);
        uVar8 = FUN_02386f04((uint)*(ushort *)(iVar10 + 0x3c),iVar14 + sVar4);
        if (*(char *)(iVar10 + 1) == '\x01') {
          uVar8 = uVar8 & DAT_02387f9c & 0xffff;
        }
        uVar12 = iVar11 + cVar3 + 0x40;
        uVar13 = local_30;
        if ((-1 < (int)uVar12) && (uVar13 = uVar12, 0x7f < (int)uVar12)) {
          uVar13 = 0x7f;
        }
        if (uVar7 != *(ushort *)(iVar10 + 0x24)) {
          *(short *)(iVar10 + 0x24) = (short)uVar7;
          *(byte *)(iVar10 + 3) =
               *(byte *)(iVar10 + 3) & 7 |
               (byte)((((uint)*(byte *)(iVar10 + 3) << 0x18) >> 0x1b | 8) << 3);
        }
        if (uVar8 != *(ushort *)(iVar10 + 0x26)) {
          *(short *)(iVar10 + 0x26) = (short)uVar8;
          *(byte *)(iVar10 + 3) =
               *(byte *)(iVar10 + 3) & 7 |
               (byte)((((uint)*(byte *)(iVar10 + 3) << 0x18) >> 0x1b | 4) << 3);
        }
        if (uVar13 != *(byte *)(iVar10 + 0x23)) {
          *(char *)(iVar10 + 0x23) = (char)uVar13;
          *(byte *)(iVar10 + 3) =
               *(byte *)(iVar10 + 3) & 7 |
               (byte)((((uint)*(byte *)(iVar10 + 3) << 0x18) >> 0x1b | 0x10) << 3);
        }
      }
    }
LAB_02387f78:
    iVar9 = iVar9 + 1;
    if (0xf < iVar9) {
      return;
    }
  } while( true );
}



void FUN_02387fa0(void)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  iVar4 = DAT_02388188;
  uVar5 = 0;
  do {
    iVar6 = uVar5 * 0x54 + iVar4;
    uVar1 = ((uint)*(byte *)(iVar6 + 3) << 0x18) >> 0x1b;
    if (uVar1 != 0) {
      if ((uVar1 & 2) != 0) {
        FUN_02386b7c(uVar5,0);
      }
      uVar1 = ((uint)*(byte *)(iVar6 + 3) << 0x18) >> 0x1b;
      if ((uVar1 & 1) == 0) {
        if ((uVar1 & 4) != 0) {
          FUN_02386ae0(uVar5,*(short *)(iVar6 + 0x26));
        }
        if ((((uint)*(byte *)(iVar6 + 3) << 0x18) >> 0x1b & 8) != 0) {
          FUN_02386af8(uVar5,*(ushort *)(iVar6 + 0x24) & 0xff,
                       (int)(uint)*(ushort *)(iVar6 + 0x24) >> 8);
        }
        if ((((uint)*(byte *)(iVar6 + 3) << 0x18) >> 0x1b & 0x10) != 0) {
          FUN_02386a64(uVar5,(uint)*(byte *)(iVar6 + 0x23));
        }
      }
      else {
        cVar2 = *(char *)(iVar6 + 1);
        if (cVar2 == '\0') {
          if (*(char *)(iVar6 + 0x39) == '\0') {
            iVar3 = 2;
          }
          else {
            iVar3 = 1;
          }
          FUN_02386d10(uVar5,*(undefined4 *)(iVar6 + 0x44),(uint)*(byte *)(iVar6 + 0x38),iVar3,
                       *(undefined2 *)(iVar6 + 0x3e),*(undefined4 *)(iVar6 + 0x40),
                       *(ushort *)(iVar6 + 0x24) & 0xff,(int)(uint)*(ushort *)(iVar6 + 0x24) >> 8,
                       *(short *)(iVar6 + 0x26),(uint)*(byte *)(iVar6 + 0x23));
        }
        else if (cVar2 == '\x01') {
          FUN_02386c58(uVar5,*(int *)(iVar6 + 0x44),*(ushort *)(iVar6 + 0x24) & 0xff,
                       (int)(uint)*(ushort *)(iVar6 + 0x24) >> 8,*(short *)(iVar6 + 0x26),
                       (uint)*(byte *)(iVar6 + 0x23));
        }
        else if (cVar2 == '\x02') {
          FUN_02386ba8(uVar5,*(ushort *)(iVar6 + 0x24) & 0xff,
                       (int)(uint)*(ushort *)(iVar6 + 0x24) >> 8,*(short *)(iVar6 + 0x26),
                       (uint)*(byte *)(iVar6 + 0x23));
        }
      }
    }
    iVar6 = DAT_02388188;
    uVar5 = uVar5 + 1;
  } while ((int)uVar5 < 0x10);
  iVar4 = 0;
  do {
    iVar3 = iVar4 * 0x54 + iVar6;
    uVar5 = ((uint)*(byte *)(iVar3 + 3) << 0x18) >> 0x1b;
    if (uVar5 != 0) {
      if ((uVar5 & 1) != 0) {
        *(byte *)(iVar4 * 0x10 + 0x4000403) = *(byte *)(iVar4 * 0x10 + 0x4000403) | 0x80;
      }
      *(byte *)(iVar3 + 3) = *(byte *)(iVar3 + 3) & 7;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x10);
  return;
}



void FUN_0238818c(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = DAT_023881e0;
  iVar3 = 0;
  do {
    iVar2 = iVar1 + iVar3 * 0x54;
    *(char *)(iVar1 + iVar3 * 0x54) = (char)iVar3;
    *(byte *)(iVar2 + 3) = *(byte *)(iVar2 + 3) & 7;
    *(byte *)(iVar2 + 3) = *(byte *)(iVar2 + 3) & 0xfe;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x10);
  *DAT_023881e4 = 0;
  *DAT_023881e8 = 0;
  return;
}



int FUN_023881ec(void)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (0x1f < iVar2) {
      return -1;
    }
    bVar1 = *(byte *)(DAT_0238822c + iVar2 * 0x40);
    if (-1 < (int)((uint)bVar1 << 0x1f)) break;
    iVar2 = iVar2 + 1;
  }
  *(byte *)(DAT_0238822c + iVar2 * 0x40) = bVar1 & 0xfe | 1;
  return iVar2;
}



int FUN_02388230(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *DAT_02388270;
  if (iVar1 == 0) {
    return 0;
  }
  if (param_2 < 0x10) {
    return (uint)*(byte *)(param_1 + 1) * 0x24 + iVar1 + 0x20 + param_2 * 2;
  }
  return iVar1 + 0x260 + (param_2 + -0x10) * 2;
}



bool FUN_02388274(int param_1,int param_2)

{
  bool bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  
  bVar1 = false;
  iVar4 = 0;
  do {
    pbVar2 = (byte *)FUN_02389154(param_1,iVar4);
    if ((pbVar2 != (byte *)0x0) && (*(int *)(pbVar2 + 0x28) != 0)) {
      iVar3 = FUN_023882f4(pbVar2,param_1,iVar4,param_2);
      if (iVar3 == 0) {
        bVar1 = true;
      }
      else {
        FUN_023890e0(param_1,iVar4);
      }
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x10);
  return !bVar1;
}



undefined4 FUN_023882f4(byte *param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined2 uVar1;
  byte bVar2;
  short sVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  short *psVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  bool bVar11;
  bool bVar12;
  undefined8 uVar13;
  undefined4 local_50;
  int local_34;
  uint local_30;
  
  for (iVar8 = *(int *)(param_1 + 0x3c); iVar8 != 0; iVar8 = *(int *)(iVar8 + 0x50)) {
    if (0 < *(int *)(iVar8 + 0x34)) {
      *(int *)(iVar8 + 0x34) = *(int *)(iVar8 + 0x34) + -1;
    }
    if ((-1 < (int)((uint)*(byte *)(iVar8 + 3) << 0x1d)) &&
       (*(int *)(iVar8 + 0x14) < *(int *)(iVar8 + 0x18))) {
      *(int *)(iVar8 + 0x14) = *(int *)(iVar8 + 0x14) + 1;
    }
  }
  if ((int)((uint)*param_1 << 0x1b) < 0) {
    if (*(int *)(param_1 + 0x3c) != 0) {
      return 0;
    }
    *param_1 = *param_1 & 0xef;
  }
  if ((0 < *(int *)(param_1 + 0x20)) &&
     (*(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + -1, 0 < *(int *)(param_1 + 0x20))) {
    return 0;
  }
  FUN_023896ac(*(uint *)(param_1 + 0x28));
  local_34 = 0x7f;
  local_30 = 0xffffffff;
  do {
    while( true ) {
      while( true ) {
        while( true ) {
          if ((*(int *)(param_1 + 0x20) != 0) || ((int)((uint)*param_1 << 0x1b) < 0)) {
            return 0;
          }
          uVar10 = 1;
          uVar4 = FUN_0238965c(*(uint *)(param_1 + 0x28));
          *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
          if (uVar4 == 0xa2) {
            uVar4 = FUN_0238965c(*(uint *)(param_1 + 0x28));
            *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
            uVar10 = ((uint)*param_1 << 0x19) >> 0x1f;
          }
          bVar11 = uVar4 == 0xa0;
          if (bVar11) {
            uVar4 = FUN_0238965c(*(uint *)(param_1 + 0x28));
            *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
            local_50 = 3;
          }
          bVar12 = uVar4 == 0xa1;
          if (bVar12) {
            uVar4 = FUN_0238965c(*(uint *)(param_1 + 0x28));
            *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
            local_50 = 4;
          }
          if ((uVar4 & 0x80) != 0) break;
          bVar2 = FUN_0238965c(*(uint *)(param_1 + 0x28));
          *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
          uVar9 = local_50;
          if (!bVar12 && !bVar11) {
            uVar9 = 2;
          }
          uVar5 = FUN_023894a4((int)param_1,param_2,uVar9);
          iVar8 = uVar4 + (int)(char)param_1[0x13];
          if (uVar10 != 0) {
            if (iVar8 < 0) {
              iVar8 = 0;
            }
            else if (0x7f < iVar8) {
              iVar8 = local_34;
            }
            if ((-1 < (int)((uint)*param_1 << 0x1d)) && (param_4 != 0)) {
              uVar10 = uVar5;
              if ((int)uVar5 < 1) {
                uVar10 = local_30;
              }
              FUN_02388ca8(param_1,param_2,iVar8,bVar2,uVar10);
            }
            param_1[0x14] = (byte)iVar8;
            if (((int)((uint)*param_1 << 0x1e) < 0) &&
               (*(uint *)(param_1 + 0x20) = uVar5, uVar5 == 0)) {
              *param_1 = *param_1 | 0x10;
            }
          }
        }
        uVar5 = uVar4 & 0xf0;
        if (uVar5 < 0xc1) break;
        if (uVar5 < 0xe1) {
          if (uVar5 < 0xe0) {
            if (uVar5 == 0xd0) goto LAB_023886e4;
          }
          else {
            uVar9 = local_50;
            if (!bVar12 && !bVar11) {
              uVar9 = 1;
            }
            uVar5 = FUN_023894a4((int)param_1,param_2,uVar9);
            if (uVar10 != 0) {
              uVar1 = (undefined2)uVar5;
              if (uVar4 == 0xe0) {
                *(undefined2 *)(param_1 + 0x1c) = uVar1;
              }
              else if (uVar4 == 0xe1) {
                *(undefined2 *)(param_2 + 0x18) = uVar1;
              }
              else if (uVar4 == 0xe3) {
                *(undefined2 *)(param_1 + 0x16) = uVar1;
              }
            }
          }
        }
        else if ((uVar5 == 0xf0) && (uVar10 != 0)) {
          switch(uVar4) {
          case 0xfc:
            uVar10 = (uint)param_1[0x3b];
            if (uVar10 != 0) {
              bVar2 = param_1[uVar10 + 0x37];
              if ((bVar2 == 0) || (bVar2 = bVar2 - 1, bVar2 != 0)) {
                param_1[uVar10 + 0x37] = bVar2;
                *(undefined4 *)(param_1 + 0x28) =
                     *(undefined4 *)(param_1 + (param_1[0x3b] - 1) * 4 + 0x2c);
              }
              else {
                param_1[0x3b] = param_1[0x3b] - 1;
              }
            }
            break;
          case 0xfd:
            if (param_1[0x3b] != 0) {
              param_1[0x3b] = param_1[0x3b] - 1;
              *(undefined4 *)(param_1 + 0x28) =
                   *(undefined4 *)(param_1 + (uint)param_1[0x3b] * 4 + 0x2c);
            }
            break;
          case 0xfe:
            break;
          case 0xff:
            return 0xffffffff;
          }
        }
      }
      if (0xbf < uVar5) break;
      if (uVar5 < 0x91) {
        if (uVar5 < 0x90) {
          if (uVar5 == 0x80) {
            uVar9 = local_50;
            if (!bVar12 && !bVar11) {
              uVar9 = 2;
            }
            uVar5 = FUN_023894a4((int)param_1,param_2,uVar9);
            if (uVar10 != 0) {
              if (uVar4 == 0x80) {
                *(uint *)(param_1 + 0x20) = uVar5;
              }
              else if ((uVar4 == 0x81) && ((int)uVar5 < 0x10000)) {
                *(short *)(param_1 + 2) = (short)uVar5;
              }
            }
          }
        }
        else if (uVar4 == 0x93) {
          iVar8 = FUN_0238965c(*(uint *)(param_1 + 0x28));
          *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
          uVar4 = FUN_023895ac((int)param_1);
          if (((uVar10 != 0) &&
              (pbVar6 = (byte *)FUN_02389154(param_2,iVar8), pbVar6 != (byte *)0x0)) &&
             (pbVar6 != param_1)) {
            FUN_02389134((int)pbVar6,param_2);
            FUN_0238939c((int)pbVar6,*(undefined4 *)(param_1 + 0x24),uVar4);
          }
        }
        else if (uVar4 == 0x94) {
          uVar4 = FUN_023895ac((int)param_1);
          if (uVar10 != 0) {
            *(uint *)(param_1 + 0x28) = *(int *)(param_1 + 0x24) + uVar4;
          }
        }
        else if (((uVar4 == 0x95) && (uVar4 = FUN_023895ac((int)param_1), uVar10 != 0)) &&
                (param_1[0x3b] < 3)) {
          *(undefined4 *)(param_1 + (uint)param_1[0x3b] * 4 + 0x2c) =
               *(undefined4 *)(param_1 + 0x28);
          param_1[0x3b] = param_1[0x3b] + 1;
          *(uint *)(param_1 + 0x28) = *(int *)(param_1 + 0x24) + uVar4;
        }
      }
      else if (uVar5 == 0xb0) {
        iVar8 = FUN_0238965c(*(uint *)(param_1 + 0x28));
        *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
        uVar9 = local_50;
        if (!bVar12 && !bVar11) {
          uVar9 = 1;
        }
        uVar5 = FUN_023894a4((int)param_1,param_2,uVar9);
        sVar3 = (short)uVar5;
        uVar5 = (uint)sVar3;
        psVar7 = (short *)FUN_02388230(param_2,iVar8);
        if ((uVar10 != 0) && (psVar7 != (short *)0x0)) {
          switch(uVar4) {
          case 0xb0:
            *psVar7 = sVar3;
            break;
          case 0xb1:
            *psVar7 = *psVar7 + sVar3;
            break;
          case 0xb2:
            *psVar7 = *psVar7 - sVar3;
            break;
          case 0xb3:
            *psVar7 = *psVar7 * sVar3;
            break;
          case 0xb4:
            if (uVar5 != 0) {
              uVar13 = FUN_0238f0dc((int)*psVar7,uVar5);
              *psVar7 = (short)uVar13;
            }
            break;
          case 0xb5:
            if ((int)uVar5 < 0) {
              *psVar7 = (short)((int)*psVar7 >> (-uVar5 & 0xff));
            }
            else {
              *psVar7 = (short)((int)*psVar7 << (uVar5 & 0xff));
            }
            break;
          case 0xb6:
            bVar11 = (int)uVar5 < 0;
            if (bVar11) {
              uVar5 = (int)(uVar5 * -0x10000) >> 0x10;
            }
            uVar10 = FUN_02386de0();
            sVar3 = (short)(uVar10 * (uVar5 + 1) >> 0x10);
            if (bVar11) {
              sVar3 = -sVar3;
            }
            *psVar7 = sVar3;
            break;
          case 0xb7:
            break;
          case 0xb8:
            *param_1 = *param_1 & 0xbf | ((int)*psVar7 == uVar5) << 6;
            break;
          case 0xb9:
            *param_1 = *param_1 & 0xbf | ((int)uVar5 <= (int)*psVar7) << 6;
            break;
          case 0xba:
            *param_1 = *param_1 & 0xbf | ((int)uVar5 < (int)*psVar7) << 6;
            break;
          case 0xbb:
            *param_1 = *param_1 & 0xbf | ((int)*psVar7 <= (int)uVar5) << 6;
            break;
          case 0xbc:
            *param_1 = *param_1 & 0xbf | ((int)*psVar7 < (int)uVar5) << 6;
            break;
          case 0xbd:
            *param_1 = *param_1 & 0xbf | ((int)*psVar7 != uVar5) << 6;
          }
        }
      }
    }
LAB_023886e4:
    uVar9 = local_50;
    if (!bVar12 && !bVar11) {
      uVar9 = 0;
    }
    uVar5 = FUN_023894a4((int)param_1,param_2,uVar9);
    bVar2 = (byte)uVar5;
    if (uVar10 != 0) {
      switch(uVar4) {
      case 0xc0:
        param_1[8] = bVar2 - 0x40;
        break;
      case 0xc1:
        param_1[4] = bVar2;
        break;
      case 0xc2:
        *(byte *)(param_2 + 5) = bVar2;
        break;
      case 0xc3:
        param_1[0x13] = bVar2;
        break;
      case 0xc4:
        param_1[6] = bVar2;
        break;
      case 0xc5:
        param_1[7] = bVar2;
        break;
      case 0xc6:
        param_1[0x12] = bVar2;
        break;
      case 199:
        *param_1 = *param_1 & 0xfd | (byte)((uVar5 & 1) << 1);
        break;
      case 200:
        *param_1 = *param_1 & 0xf7 | (byte)((uVar5 & 1) << 3);
        FUN_0238927c((int)param_1,param_2,0xffffffff);
        FUN_02389240((int)param_1);
        break;
      case 0xc9:
        param_1[0x14] = bVar2 + param_1[0x13];
        *param_1 = *param_1 | 0x20;
        break;
      case 0xca:
        param_1[0x1a] = bVar2;
        break;
      case 0xcb:
        param_1[0x19] = bVar2;
        break;
      case 0xcc:
        param_1[0x18] = bVar2;
        break;
      case 0xcd:
        param_1[0x1b] = bVar2;
        break;
      case 0xce:
        *param_1 = *param_1 & 0xdf | (byte)((uVar5 & 1) << 5);
        break;
      case 0xcf:
        param_1[0x15] = bVar2;
        break;
      case 0xd0:
        param_1[0xe] = bVar2;
        break;
      case 0xd1:
        param_1[0xf] = bVar2;
        break;
      case 0xd2:
        param_1[0x10] = bVar2;
        break;
      case 0xd3:
        param_1[0x11] = bVar2;
        break;
      case 0xd4:
        if (param_1[0x3b] < 3) {
          *(undefined4 *)(param_1 + (uint)param_1[0x3b] * 4 + 0x2c) =
               *(undefined4 *)(param_1 + 0x28);
          param_1[param_1[0x3b] + 0x38] = bVar2;
          param_1[0x3b] = param_1[0x3b] + 1;
        }
        break;
      case 0xd5:
        param_1[5] = bVar2;
        break;
      case 0xd6:
        if (*DAT_02388ca4 != 0) {
          FUN_02388230(param_2,uVar5 & 0xff);
        }
      }
    }
  } while( true );
}



// WARNING: Type propagation algorithm not settling

void FUN_02388ca8(byte *param_1,int param_2,int param_3,byte param_4,undefined4 param_5)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  byte *pbVar5;
  undefined2 local_28 [8];
  
  pbVar5 = (byte *)0x0;
  if (((int)((uint)*param_1 << 0x1c) < 0) &&
     (pbVar5 = *(byte **)(param_1 + 0x3c), pbVar5 != (byte *)0x0)) {
    pbVar5[8] = (byte)param_3;
    pbVar5[9] = param_4;
  }
  if (pbVar5 == (byte *)0x0) {
    iVar2 = FUN_02389fe0(*(int *)(param_2 + 0x20),(uint)*(ushort *)(param_1 + 2),param_3,local_28);
    if (iVar2 == 0) {
      return;
    }
    uVar3 = DAT_02388eac;
    switch((char)local_28[0]) {
    case '\0':
      return;
    case '\x01':
      break;
    case '\x02':
      uVar3 = 0x3f00;
      break;
    case '\x03':
      uVar3 = 0xc000;
      break;
    case '\x04':
      break;
    default:
      return;
    }
    pbVar5 = (byte *)FUN_0238794c(uVar3 & *(ushort *)(param_1 + 0x1e),
                                  (uint)*(byte *)(param_2 + 4) + (uint)param_1[0x12],
                                  ((uint)*param_1 << 0x18) >> 0x1f,DAT_02388eb0,param_1);
    if (pbVar5 == (byte *)0x0) {
      return;
    }
    uVar4 = param_5;
    if ((int)((uint)*param_1 << 0x1c) < 0) {
      uVar4 = 0xffffffff;
    }
    bVar1 = FUN_02389e70(pbVar5,(byte)param_3,param_4,uVar4,*(int *)(param_2 + 0x20),
                         (char *)local_28);
    if (!bVar1) {
      pbVar5[0x22] = 0;
      FUN_02387938((int)pbVar5);
      return;
    }
    *(undefined4 *)(pbVar5 + 0x50) = *(undefined4 *)(param_1 + 0x3c);
    *(byte **)(param_1 + 0x3c) = pbVar5;
  }
  if (param_1[0xe] != 0xff) {
    FUN_02387ae0((int)pbVar5,(uint)param_1[0xe]);
  }
  if (param_1[0xf] != 0xff) {
    FUN_02387ac4((int)pbVar5,(uint)param_1[0xf]);
  }
  if (param_1[0x10] != 0xff) {
    FUN_02387abc((int)pbVar5,param_1[0x10]);
  }
  if (param_1[0x11] != 0xff) {
    FUN_02387aa0((int)pbVar5,(uint)param_1[0x11]);
  }
  *(undefined2 *)(pbVar5 + 0x32) = *(undefined2 *)(param_1 + 0x16);
  if ((int)((uint)*param_1 << 0x1a) < 0) {
    *(short *)(pbVar5 + 0x32) =
         *(short *)(pbVar5 + 0x32) + (short)(((uint)param_1[0x14] - param_3) * 0x400000 >> 0x10);
  }
  uVar3 = (uint)param_1[0x15];
  if (uVar3 == 0) {
    *(undefined4 *)(pbVar5 + 0x18) = param_5;
    pbVar5[3] = pbVar5[3] & 0xfb;
  }
  else {
    iVar2 = (int)*(short *)(pbVar5 + 0x32);
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    *(int *)(pbVar5 + 0x18) = (int)(uVar3 * uVar3 * iVar2) >> 0xb;
  }
  *(undefined4 *)(pbVar5 + 0x14) = 0;
  return;
}



void FUN_02388eb4(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = FUN_02389154(param_1,iVar2);
    if (iVar1 != 0) {
      FUN_02388ef8(iVar1,param_1,1);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  return;
}



void FUN_02388ef8(int param_1,int param_2,int param_3)

{
  byte bVar1;
  char cVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  int iVar9;
  int iVar10;
  
  sVar3 = *(short *)(DAT_02389034 + (uint)*(byte *)(param_2 + 5) * 2);
  sVar4 = *(short *)(DAT_02389034 + (uint)*(byte *)(param_1 + 4) * 2);
  sVar5 = *(short *)(DAT_02389034 + (uint)*(byte *)(param_1 + 5) * 2);
  sVar6 = *(short *)(param_1 + 10);
  sVar7 = *(short *)(param_2 + 6);
  cVar2 = *(char *)(param_1 + 6);
  bVar1 = *(byte *)(param_1 + 7);
  sVar8 = *(short *)(param_1 + 0xc);
  iVar9 = (int)*(char *)(param_1 + 8);
  if (*(byte *)(param_1 + 1) != 0x7f) {
    iVar9 = (int)(iVar9 * (uint)*(byte *)(param_1 + 1) + 0x40) >> 7;
  }
  iVar9 = iVar9 + *(char *)(param_1 + 9);
  if (iVar9 < -0x80) {
    iVar9 = -0x80;
  }
  else if (0x7f < iVar9) {
    iVar9 = 0x7f;
  }
  for (iVar10 = *(int *)(param_1 + 0x3c); iVar10 != 0; iVar10 = *(int *)(iVar10 + 0x50)) {
    *(short *)(iVar10 + 6) = sVar6 + sVar7;
    if (*(char *)(iVar10 + 2) != '\x03') {
      *(short *)(iVar10 + 0xc) = sVar3 + sVar4 + sVar5;
      *(short *)(iVar10 + 0xe) =
           (short)((uint)(((int)sVar8 + ((int)((int)cVar2 * (uint)bVar1 * 0x40) >> 7)) * 0x10000) >>
                  0x10);
      *(char *)(iVar10 + 0xb) = (char)iVar9;
      *(undefined *)(iVar10 + 4) = *(undefined *)(param_1 + 1);
      *(undefined2 *)(iVar10 + 0x28) = *(undefined2 *)(param_1 + 0x18);
      *(undefined2 *)(iVar10 + 0x2a) = *(undefined2 *)(param_1 + 0x1a);
      *(undefined2 *)(iVar10 + 0x2c) = *(undefined2 *)(param_1 + 0x1c);
      if ((*(int *)(iVar10 + 0x34) == 0) && (param_3 != 0)) {
        *(undefined *)(iVar10 + 0x22) = 1;
        FUN_02387a94(iVar10);
      }
    }
  }
  return;
}



void FUN_02389038(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 1) {
    *(undefined *)(param_1 + 0x22) = 0;
    FUN_02387938(param_1);
  }
  iVar1 = *(int *)(param_3 + 0x3c);
  if (*(int *)(param_3 + 0x3c) == param_1) {
    *(undefined4 *)(param_3 + 0x3c) = *(undefined4 *)(param_1 + 0x50);
  }
  else {
    do {
      iVar2 = iVar1;
      iVar1 = *(int *)(iVar2 + 0x50);
      if (iVar1 == 0) {
        return;
      }
    } while (iVar1 != param_1);
    *(undefined4 *)(iVar2 + 0x50) = *(undefined4 *)(param_1 + 0x50);
  }
  return;
}



void FUN_023890a0(byte *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    FUN_023890e0((int)param_1,iVar1);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x10);
  *param_1 = *param_1 & 0xfe;
  return;
}



void FUN_023890e0(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_02389154(param_1,param_2);
  if (iVar1 != 0) {
    FUN_02389134(iVar1,param_1);
    uVar2 = (uint)*(byte *)(param_1 + 8 + param_2);
    *(byte *)(DAT_02389130 + uVar2 * 0x40) = *(byte *)(DAT_02389130 + uVar2 * 0x40) & 0xfe;
    *(undefined *)(param_1 + 8 + param_2) = 0xff;
  }
  return;
}



void FUN_02389134(int param_1,int param_2)

{
  FUN_0238927c(param_1,param_2,0xffffffff);
  FUN_02389240(param_1);
  return;
}



int FUN_02389154(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  if (param_2 < 0x10) {
    uVar2 = (uint)*(byte *)(param_1 + param_2 + 8);
    if (uVar2 == 0xff) {
      iVar1 = 0;
    }
    else {
      iVar1 = DAT_0238917c + uVar2 * 0x40;
    }
    return iVar1;
  }
  return 0;
}



void FUN_02389180(byte *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  while (0xef < *(ushort *)(param_1 + 0x1c)) {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -0xf0;
    iVar3 = iVar3 + 1;
  }
  iVar2 = 0;
  do {
    if (iVar3 <= iVar2) {
LAB_023891ec:
      if (*DAT_0238923c != 0) {
        iVar3 = *DAT_0238923c + 0x40;
        *(int *)(iVar3 + (uint)param_1[1] * 0x24) =
             *(int *)(iVar3 + (uint)param_1[1] * 0x24) + iVar2;
      }
      *(short *)(param_1 + 0x1c) =
           *(short *)(param_1 + 0x1c) +
           (short)((uint)*(ushort *)(param_1 + 0x18) * (uint)*(ushort *)(param_1 + 0x1a) >> 8);
      return;
    }
    bVar1 = FUN_02388274((int)param_1,1);
    if (bVar1) {
      FUN_023890a0(param_1);
      goto LAB_023891ec;
    }
    iVar2 = iVar2 + 1;
  } while( true );
}



void FUN_02389240(int param_1)

{
  int iVar1;
  
  for (iVar1 = *(int *)(param_1 + 0x3c); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x50)) {
    FUN_02387938(iVar1);
  }
  *(undefined4 *)(param_1 + 0x3c) = 0;
  return;
}



void FUN_0238927c(int param_1,int param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  
  FUN_02388ef8(param_1,param_2,0);
  for (iVar2 = *(int *)(param_1 + 0x3c); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x50)) {
    bVar1 = FUN_02387a84(iVar2);
    if (bVar1 != 0) {
      if (-1 < (int)param_3) {
        FUN_02387aa0(iVar2,param_3 & 0xff);
      }
      *(undefined *)(iVar2 + 0x22) = 1;
      FUN_02387a94(iVar2);
    }
  }
  return;
}



void FUN_023892ec(byte *param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  
  *param_1 = *param_1 & 0xfb;
  *(undefined4 *)(param_1 + 0x20) = param_2;
  *(undefined2 *)(param_1 + 0x18) = 0x78;
  *(undefined2 *)(param_1 + 0x1a) = 0x100;
  *(undefined2 *)(param_1 + 0x1c) = 0xf0;
  param_1[5] = 0x7f;
  iVar2 = 0;
  *(undefined2 *)(param_1 + 6) = 0;
  param_1[4] = 0x40;
  do {
    param_1[iVar2 + 8] = 0xff;
    piVar1 = DAT_02389398;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  if (*DAT_02389398 != 0) {
    iVar2 = 0;
    *(undefined4 *)((uint)param_1[1] * 0x24 + *DAT_02389398 + 0x40) = 0;
    do {
      *(undefined2 *)((uint)param_1[1] * 0x24 + *piVar1 + iVar2 * 2 + 0x20) = 0xffff;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x10);
  }
  return;
}



void FUN_0238939c(int param_1,undefined4 param_2,int param_3)

{
  *(undefined4 *)(param_1 + 0x24) = param_2;
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x24) + param_3;
  return;
}



void FUN_023893b0(byte *param_1)

{
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *param_1 = *param_1 | 2;
  *param_1 = *param_1 & 0xfb;
  *param_1 = *param_1 & 0xf7;
  *param_1 = *param_1 & 0xef;
  *param_1 = *param_1 & 0xdf;
  *param_1 = *param_1 | 0x40;
  *param_1 = *param_1 & 0x7f;
  param_1[0x3b] = 0;
  *(undefined2 *)(param_1 + 2) = 0;
  param_1[0x12] = 0x40;
  param_1[4] = 0x7f;
  param_1[5] = 0x7f;
  *(undefined2 *)(param_1 + 10) = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[6] = 0;
  *(undefined2 *)(param_1 + 0xc) = 0;
  param_1[0xe] = 0xff;
  param_1[0xf] = 0xff;
  param_1[0x10] = 0xff;
  param_1[0x11] = 0xff;
  param_1[1] = 0x7f;
  param_1[7] = 2;
  param_1[0x14] = 0x3c;
  param_1[0x15] = 0;
  *(undefined2 *)(param_1 + 0x16) = 0;
  param_1[0x13] = 0;
  *(short *)(param_1 + 0x1e) = (short)DAT_023894a0;
  FUN_02387670(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  return;
}



uint FUN_023894a4(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  short *psVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint unaff_r5;
  
  switch(param_3) {
  case 0:
    unaff_r5 = FUN_0238965c(*(uint *)(param_1 + 0x28));
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
    break;
  case 1:
    unaff_r5 = FUN_0238960c(param_1);
    break;
  case 2:
    unaff_r5 = FUN_0238956c(param_1);
    break;
  case 3:
    uVar3 = FUN_0238960c(param_1);
    uVar4 = FUN_0238960c(param_1);
    uVar5 = FUN_02386de0();
    unaff_r5 = ((int)(uVar5 * (((int)(short)uVar4 - (int)(short)uVar3) + 1)) >> 0x10) +
               (int)(short)uVar3;
    break;
  case 4:
    iVar1 = FUN_0238965c(*(uint *)(param_1 + 0x28));
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
    psVar2 = (short *)FUN_02388230(param_2,iVar1);
    if (psVar2 != (short *)0x0) {
      unaff_r5 = (uint)*psVar2;
    }
  }
  return unaff_r5;
}



uint FUN_0238956c(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  do {
    uVar1 = FUN_0238965c(*(uint *)(param_1 + 0x28));
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
    uVar2 = uVar1 & 0x7f | uVar2 << 7;
  } while ((uVar1 & 0x80) != 0);
  return uVar2;
}



uint FUN_023895ac(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = FUN_0238965c(*(uint *)(param_1 + 0x28));
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
  iVar2 = FUN_0238965c(*(uint *)(param_1 + 0x28));
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
  iVar3 = FUN_0238965c(*(uint *)(param_1 + 0x28));
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
  return uVar1 | iVar2 << 8 | iVar3 << 0x10;
}



uint FUN_0238960c(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_0238965c(*(uint *)(param_1 + 0x28));
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
  iVar2 = FUN_0238965c(*(uint *)(param_1 + 0x28));
  *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
  return (uVar1 | iVar2 << 8) & 0xffff;
}



undefined FUN_0238965c(uint param_1)

{
  if ((param_1 < *DAT_023896a4) || (DAT_023896a4[1] <= param_1)) {
    FUN_023896ac(param_1);
  }
  return *(undefined *)(DAT_023896a8 + (param_1 - *DAT_023896a4));
}



void FUN_023896ac(uint param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = DAT_023896e4;
  puVar2 = (undefined4 *)(param_1 & 0xfffffffc);
  *DAT_023896e4 = puVar2;
  puVar1[1] = puVar2 + 4;
  puVar1[2] = *puVar2;
  puVar1[3] = puVar2[1];
  puVar1[4] = puVar2[2];
  puVar1[5] = puVar2[3];
  return;
}



void FUN_023896e8(int param_1,uint param_2,int param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1 * 0x24 + DAT_02389788;
  iVar2 = 0;
  for (; (iVar2 < 0x10 && (param_2 != 0)); param_2 = param_2 >> 1) {
    if (((param_2 & 1) != 0) && (iVar1 = FUN_02389154(iVar3,iVar2), iVar1 != 0)) {
      if (param_5 == 1) {
        *(char *)(iVar1 + param_3) = (char)param_4;
      }
      else if (param_5 == 2) {
        *(short *)(iVar1 + param_3) = (short)param_4;
      }
      else if (param_5 == 4) {
        *(undefined4 *)(iVar1 + param_3) = param_4;
      }
    }
    iVar2 = iVar2 + 1;
  }
  return;
}



void FUN_0238978c(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  iVar1 = param_1 * 0x24 + DAT_023897d4;
  if (param_4 == 1) {
    *(char *)(iVar1 + param_2) = (char)param_3;
  }
  else if (param_4 == 2) {
    *(short *)(iVar1 + param_2) = (short)param_3;
  }
  else if (param_4 == 4) {
    *(undefined4 *)(iVar1 + param_2) = param_3;
  }
  return;
}



void FUN_023897d8(uint param_1,uint param_2)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  
  iVar1 = DAT_02389834;
  iVar4 = 0;
  do {
    pbVar2 = (byte *)(iVar1 + iVar4 * 0x24);
    if ((((int)((uint)*(byte *)(iVar1 + iVar4 * 0x24) << 0x1f) < 0) &&
        (uVar3 = *(uint *)(pbVar2 + 0x20), param_1 <= uVar3)) && (uVar3 <= param_2)) {
      FUN_023890a0(pbVar2);
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x10);
  return;
}



void FUN_02389838(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  
  iVar1 = DAT_023898d0;
  iVar4 = 0;
  do {
    pbVar5 = (byte *)(iVar1 + iVar4 * 0x24);
    if ((int)((uint)*(byte *)(iVar1 + iVar4 * 0x24) << 0x1f) < 0) {
      for (iVar3 = 0; iVar3 < 0x10; iVar3 = iVar3 + 1) {
        iVar2 = FUN_02389154((int)pbVar5,iVar3);
        if (((iVar2 != 0) && (param_1 <= *(uint *)(iVar2 + 0x28))) &&
           (*(uint *)(iVar2 + 0x28) <= param_2)) {
          FUN_023890a0(pbVar5);
          break;
        }
      }
    }
    iVar4 = iVar4 + 1;
    if (0xf < iVar4) {
      return;
    }
  } while( true );
}



void FUN_023898d4(int param_1,uint param_2,undefined2 param_3)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1 * 0x24 + DAT_02389948;
  iVar2 = 0;
  for (; (iVar2 < 0x10 && (param_2 != 0)); param_2 = param_2 >> 1) {
    if (((param_2 & 1) != 0) && (pbVar1 = (byte *)FUN_02389154(iVar3,iVar2), pbVar1 != (byte *)0x0))
    {
      *(undefined2 *)(pbVar1 + 0x1e) = param_3;
      *pbVar1 = *pbVar1 | 0x80;
    }
    iVar2 = iVar2 + 1;
  }
  return;
}



void FUN_0238994c(int param_1,uint param_2,uint param_3)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1 * 0x24 + DAT_023899e4;
  iVar2 = 0;
  for (; (iVar2 < 0x10 && (param_2 != 0)); param_2 = param_2 >> 1) {
    if (((param_2 & 1) != 0) && (pbVar1 = (byte *)FUN_02389154(iVar3,iVar2), pbVar1 != (byte *)0x0))
    {
      if (param_3 != 0) {
        FUN_0238927c((int)pbVar1,iVar3,0x7f);
        FUN_02389240((int)pbVar1);
      }
      *pbVar1 = *pbVar1 & 0xfb | (byte)((param_3 & 1) << 2);
    }
    iVar2 = iVar2 + 1;
  }
  return;
}



void FUN_023899e8(int param_1,uint param_2)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  int iVar5;
  
  pbVar4 = (byte *)(param_1 * 0x24 + DAT_02389aac);
  iVar5 = 0;
  do {
    iVar2 = FUN_02389154((int)pbVar4,iVar5);
    if (iVar2 != 0) {
      FUN_0238927c(iVar2,(int)pbVar4,0x7f);
      FUN_02389240(iVar2);
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x10);
  FUN_02387154();
  uVar3 = 0;
  do {
    if (param_2 <= uVar3) {
LAB_02389a74:
      FUN_02387168();
      if (*DAT_02389ab0 != 0) {
        iVar5 = *DAT_02389ab0 + 0x40;
        *(uint *)(iVar5 + (uint)pbVar4[1] * 0x24) = *(int *)(iVar5 + (uint)pbVar4[1] * 0x24) + uVar3
        ;
      }
      return;
    }
    bVar1 = FUN_02388274((int)pbVar4,0);
    if (bVar1) {
      FUN_023890a0(pbVar4);
      goto LAB_02389a74;
    }
    uVar3 = uVar3 + 1;
  } while( true );
}



void FUN_02389ab4(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = param_1 * 0x24;
  iVar3 = DAT_02389b34 + iVar2;
  *(byte *)(DAT_02389b34 + iVar2) =
       *(byte *)(DAT_02389b34 + iVar2) & 0xfb | (byte)((param_2 & 1) << 2);
  if (param_2 != 0) {
    iVar2 = 0;
    do {
      iVar1 = FUN_02389154(iVar3,iVar2);
      if (iVar1 != 0) {
        FUN_0238927c(iVar1,iVar3,0x7f);
        FUN_02389240(iVar1);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x10);
  }
  return;
}



void FUN_02389b38(uint param_1)

{
  int iVar1;
  
  if ((int)((uint)*(byte *)(DAT_02389b8c + param_1 * 0x24) << 0x1f) < 0) {
    FUN_023890a0((byte *)(DAT_02389b8c + param_1 * 0x24));
    iVar1 = *DAT_02389b90;
    if (iVar1 != 0) {
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & ~(1 << (param_1 & 0xff));
    }
  }
  return;
}



void FUN_02389b94(uint param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  FUN_02389bd0(param_1,param_2,param_3,param_4);
  FUN_02389bb0(param_1);
  return;
}



void FUN_02389bb0(int param_1)

{
  *(byte *)(DAT_02389bcc + param_1 * 0x24) = *(byte *)(DAT_02389bcc + param_1 * 0x24) | 2;
  return;
}



void FUN_02389bd0(uint param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  
  pbVar6 = (byte *)(DAT_02389d18 + param_1 * 0x24);
  if ((int)((uint)*(byte *)(DAT_02389d18 + param_1 * 0x24) << 0x1f) < 0) {
    FUN_023890a0(pbVar6);
  }
  FUN_023892ec(pbVar6,param_4);
  iVar1 = FUN_023881ec();
  if (-1 < iVar1) {
    pbVar4 = (byte *)(DAT_02389d1c + iVar1 * 0x40);
    FUN_023893b0(pbVar4);
    FUN_0238939c((int)pbVar4,param_2,param_3);
    pbVar6[8] = (byte)iVar1;
    FUN_023896ac(*(uint *)(pbVar4 + 0x28));
    iVar1 = FUN_0238965c(*(uint *)(pbVar4 + 0x28));
    *(int *)(pbVar4 + 0x28) = *(int *)(pbVar4 + 0x28) + 1;
    if (iVar1 == 0xfe) {
      uVar2 = FUN_0238960c((int)pbVar4);
      iVar1 = DAT_02389d1c;
      iVar5 = 1;
      while (uVar2 = (uVar2 << 0xf) >> 0x10, uVar2 != 0) {
        if ((uVar2 & 1) != 0) {
          iVar3 = FUN_023881ec();
          if (iVar3 < 0) break;
          FUN_023893b0((byte *)(iVar1 + iVar3 * 0x40));
          pbVar6[iVar5 + 8] = (byte)iVar3;
        }
        iVar5 = iVar5 + 1;
      }
    }
    else {
      *(int *)(pbVar4 + 0x28) = *(int *)(pbVar4 + 0x28) + -1;
    }
    *pbVar6 = *pbVar6 & 0xfe | 1;
    *pbVar6 = *pbVar6 & 0xfd;
    iVar1 = *DAT_02389d20;
    if (iVar1 != 0) {
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 1 << (param_1 & 0xff);
    }
  }
  return;
}



void FUN_02389d24(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  
  iVar1 = DAT_02389dbc;
  uVar3 = 0;
  uVar4 = 0;
  do {
    pbVar5 = (byte *)(iVar1 + uVar4 * 0x24);
    uVar2 = (uint)*(byte *)(iVar1 + uVar4 * 0x24);
    if ((int)(uVar2 << 0x1f) < 0) {
      if ((int)(uVar2 << 0x1e) < 0) {
        if ((param_1 != 0) && (-1 < (int)(uVar2 << 0x1d))) {
          FUN_02389180(pbVar5);
        }
        FUN_02388eb4((int)pbVar5);
      }
      if ((int)((uint)*pbVar5 << 0x1f) < 0) {
        uVar3 = uVar3 | 1 << (uVar4 & 0xff);
      }
    }
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 0x10);
  if (*DAT_02389dc0 != 0) {
    *(uint *)(*DAT_02389dc0 + 4) = uVar3;
  }
  return;
}



void FUN_02389dc4(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_02389e28;
  iVar3 = 0;
  do {
    iVar1 = iVar3 * 0x24;
    *(byte *)(iVar2 + iVar1) = *(byte *)(iVar2 + iVar1) & 0xfe;
    *(char *)(iVar2 + iVar1 + 1) = (char)iVar3;
    iVar1 = DAT_02389e2c;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x10);
  iVar2 = 0;
  do {
    *(byte *)(iVar1 + iVar2 * 0x40) = *(byte *)(iVar1 + iVar2 * 0x40) & 0xfe;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x20);
  return;
}



void FUN_02389e30(int param_1,int param_2,uint param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + param_2 * 8 + 0x18);
  if ((iVar1 != 0) && (param_3 < *(uint *)(iVar1 + 0x38))) {
    FUN_02389f98(iVar1,param_3);
  }
  return;
}



bool FUN_02389e70(byte *param_1,byte param_2,byte param_3,undefined4 param_4,int param_5,
                 char *param_6)

{
  undefined uVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  
  uVar4 = (uint)(byte)param_6[10];
  if (uVar4 == 0xff) {
    param_4 = 0xffffffff;
    uVar4 = 0;
  }
  switch(*param_6) {
  case '\0':
  default:
    iVar3 = 0;
    break;
  case '\x01':
    goto LAB_02389ec0;
  case '\x02':
    iVar3 = FUN_02387c04(param_1,(uint)*(ushort *)(param_6 + 2),param_4);
    break;
  case '\x03':
    iVar3 = FUN_02387bb8(param_1,param_4);
    break;
  case '\x04':
LAB_02389ec0:
    if (*param_6 == '\x01') {
      puVar2 = (undefined4 *)
               FUN_02389e30(param_5,(uint)*(ushort *)(param_6 + 4),(uint)*(ushort *)(param_6 + 2));
    }
    else {
      puVar2 = *(undefined4 **)(param_6 + 2);
    }
    if (puVar2 == (undefined4 *)0x0) {
      iVar3 = 0;
    }
    else {
      iVar3 = FUN_02387c58((int)param_1,puVar2,puVar2 + 3,param_4);
    }
  }
  bVar5 = iVar3 == 0;
  if (bVar5) {
    iVar3 = 0;
  }
  uVar1 = (undefined)iVar3;
  if (!bVar5) {
    param_1[8] = param_2;
    param_1[5] = param_6[6];
    param_1[9] = param_3;
    FUN_02387ae0((int)param_1,(uint)(byte)param_6[7]);
    FUN_02387ac4((int)param_1,(uint)(byte)param_6[8]);
    FUN_02387abc((int)param_1,param_6[9]);
    FUN_02387aa0((int)param_1,uVar4);
    param_1[10] = param_6[0xb] - 0x40;
    uVar1 = 1;
  }
  return (bool)uVar1;
}



uint FUN_02389f98(int param_1,int param_2)

{
  uint uVar1;
  
  FUN_02387108();
  uVar1 = *(uint *)(param_1 + param_2 * 4 + 0x3c);
  if (uVar1 == 0) {
    uVar1 = 0;
  }
  else if (uVar1 < 0x2000000) {
    uVar1 = param_1 + uVar1;
  }
  FUN_02387104();
  return uVar1;
}



undefined4 FUN_02389fe0(int param_1,uint param_2,int param_3,undefined2 *param_4)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined2 *puVar6;
  
  if ((int)param_2 < 0) {
    return 0;
  }
  FUN_02387108();
  if (*(uint *)(param_1 + 0x38) <= param_2) {
    FUN_02387104();
    return 0;
  }
  uVar5 = *(uint *)(param_1 + param_2 * 4 + 0x3c);
  *(char *)param_4 = (char)uVar5;
  switch(*(undefined *)param_4) {
  case 0:
    break;
  case 1:
    goto LAB_0238a080;
  case 2:
    goto LAB_0238a080;
  case 3:
    goto LAB_0238a080;
  case 4:
    goto LAB_0238a080;
  case 5:
LAB_0238a080:
    iVar2 = 5;
    puVar1 = param_4 + 1;
    puVar6 = (undefined2 *)(param_1 + (uVar5 >> 8));
    do {
      *puVar1 = *puVar6;
      iVar2 = iVar2 + -1;
      puVar1 = puVar1 + 1;
      puVar6 = puVar6 + 1;
    } while (iVar2 != 0);
LAB_0238a150:
    FUN_02387104();
    return 1;
  case 6:
    break;
  case 7:
    break;
  case 8:
    break;
  case 9:
    break;
  case 10:
    break;
  case 0xb:
    break;
  case 0xc:
    break;
  case 0xd:
    break;
  case 0xe:
    break;
  case 0xf:
    break;
  case 0x10:
    iVar2 = param_1 + (uVar5 >> 8);
    uVar5 = (uint)*(byte *)(param_1 + (uVar5 >> 8));
    if ((param_3 < (int)uVar5) || ((int)(uint)*(byte *)(iVar2 + 1) < param_3)) {
      FUN_02387104();
      return 0;
    }
    puVar1 = (undefined2 *)((param_3 - uVar5) * 0xc + iVar2);
    iVar2 = 6;
    do {
      puVar1 = puVar1 + 1;
      *param_4 = *puVar1;
      iVar2 = iVar2 + -1;
      param_4 = param_4 + 1;
    } while (iVar2 != 0);
    goto LAB_0238a150;
  case 0x11:
    iVar4 = 0;
    iVar2 = param_1 + (uVar5 >> 8);
    while ((int)(uint)*(byte *)(iVar2 + iVar4) < param_3) {
      iVar4 = iVar4 + 1;
      if (7 < iVar4) {
        FUN_02387104();
        return 0;
      }
    }
    iVar3 = 6;
    puVar1 = (undefined2 *)(iVar4 * 0xc + iVar2 + 8);
    do {
      *param_4 = *puVar1;
      iVar3 = iVar3 + -1;
      puVar1 = puVar1 + 1;
      param_4 = param_4 + 1;
    } while (iVar3 != 0);
    goto LAB_0238a150;
  }
  FUN_02387104();
  return 0;
}



void FUN_0238a164(void)

{
  int *piVar1;
  bool bVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = 0;
  if (*DAT_0238a200 != 0) {
    uVar5 = 0;
    do {
      bVar2 = FUN_02386a48(uVar5);
      if (bVar2) {
        uVar4 = uVar4 | 1 << (uVar5 & 0xff) & 0xffffU;
      }
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 < 0x10);
    bVar2 = FUN_02387278(0);
    uVar3 = (ushort)bVar2;
    bVar2 = FUN_02387278(1);
    piVar1 = DAT_0238a200;
    if (bVar2) {
      uVar3 = uVar3 | 2;
    }
    *(short *)(*DAT_0238a200 + 8) = (short)uVar4;
    *(ushort *)(*piVar1 + 10) = uVar3;
  }
  return;
}



void FUN_0238a204(int param_1,undefined2 param_2)

{
  *(undefined2 *)(*DAT_0238a21c + param_1 * 2 + 0x260) = param_2;
  return;
}



void FUN_0238a220(int param_1,int param_2,undefined2 param_3)

{
  *(undefined2 *)(param_1 * 0x24 + *DAT_0238a23c + param_2 * 2 + 0x20) = param_3;
  return;
}



void FUN_0238a240(int param_1)

{
  int iVar1;
  
  do {
    iVar1 = FUN_02386464(7,param_1,0);
  } while (iVar1 < 0);
  return;
}



void FUN_0238a270(int param_1)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)(DAT_0238a2ac + param_1 * 0x40);
  if (*(char *)(DAT_0238a2ac + param_1 * 0x40) != '\0') {
    FUN_0238540c((int *)(puVar1 + 0x14));
    puVar1[1] = puVar1[1] + '\x01';
    *puVar1 = 0;
  }
  return;
}



void FUN_0238a2b0(uint param_1)

{
  longlong lVar1;
  uint uVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  longlong lVar8;
  
  puVar3 = (undefined *)(DAT_0238a370 + param_1 * 0x40);
  if (*(char *)(DAT_0238a370 + param_1 * 0x40) != '\0') {
    FUN_0238540c((int *)(puVar3 + 0x14));
    *puVar3 = 0;
  }
  uVar7 = *(undefined4 *)(puVar3 + 4);
  uVar6 = *(undefined4 *)(puVar3 + 8);
  lVar1 = *(longlong *)(puVar3 + 4);
  iVar5 = *(int *)(puVar3 + 0xc);
  iVar4 = *(int *)(puVar3 + 0x10);
  uVar2 = param_1 | (uint)(byte)puVar3[1] << 8;
  FUN_023856bc((undefined4 *)(puVar3 + 0x14));
  if (iVar4 == 0 && iVar5 == 0) {
    FUN_02385518((int *)(puVar3 + 0x14),uVar7,uVar6,DAT_0238a374,uVar2);
  }
  else {
    lVar8 = FUN_02385120();
    lVar8 = lVar8 + lVar1;
    FUN_0238549c((int *)(puVar3 + 0x14),(int)lVar8,(int)((ulonglong)lVar8 >> 0x20),iVar5,iVar4,
                 DAT_0238a374,uVar2);
  }
  *puVar3 = 1;
  return;
}



void FUN_0238a378(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)(DAT_0238a3d0 + param_1 * 0x40);
  if (*(char *)(DAT_0238a3d0 + param_1 * 0x40) != '\0') {
    FUN_0238540c((int *)(puVar1 + 0x14));
    *puVar1 = 0;
  }
  *(undefined4 *)(puVar1 + 4) = param_2;
  *(undefined4 *)(puVar1 + 8) = param_3;
  *(undefined4 *)(puVar1 + 0xc) = param_4;
  *(undefined4 *)(puVar1 + 0x10) = param_5;
  puVar1[1] = (undefined)param_6;
  return;
}



void FUN_0238a3d4(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = DAT_0238a3fc;
  iVar3 = 0;
  do {
    iVar2 = iVar1 + iVar3 * 0x40;
    *(undefined *)(iVar2 + 0xf80) = 0;
    *(undefined *)(iVar2 + 0xf81) = 0;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 8);
  return;
}



void FUN_0238a400(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  FUN_02386108(DAT_0238a468,param_1,0x1180);
  param_1[0x470] = DAT_0238a468;
  iVar2 = 0;
  do {
    uVar1 = FUN_023869d4(iVar2);
    param_1[iVar2 + 0x460] = uVar1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  uVar1 = FUN_0238771c(0);
  param_1[0x471] = uVar1;
  return;
}



void FUN_0238a46c(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  
  FUN_02385e18();
  iVar1 = 0;
  for (; (iVar1 < 8 && (param_3 != 0)); param_3 = param_3 >> 1) {
    if ((param_3 & 1) != 0) {
      FUN_0238a270(iVar1);
    }
    iVar1 = iVar1 + 1;
  }
  iVar1 = 0;
  for (; (iVar1 < 0x10 && (param_1 != 0)); param_1 = param_1 >> 1) {
    if ((param_1 & 1) != 0) {
      FUN_02386b7c(iVar1,param_4);
    }
    iVar1 = iVar1 + 1;
  }
  if ((param_2 & 1) != 0) {
    *PTR_REG_SNDCAP0CNT_0238a528 = 0;
  }
  if ((param_2 & 2) != 0) {
    *PTR_REG_SNDCAP1CNT_0238a52c = 0;
  }
  FUN_02385e2c();
  FUN_0238a164();
  return;
}



void FUN_0238a530(uint param_1,byte param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  
  FUN_02385e18();
  iVar1 = 0;
  for (; (iVar1 < 0x10 && (param_1 != 0)); param_1 = param_1 >> 1) {
    if ((param_1 & 1) != 0) {
      *(byte *)(iVar1 * 0x10 + 0x4000403) = *(byte *)(iVar1 * 0x10 + 0x4000403) | 0x80;
    }
    iVar1 = iVar1 + 1;
  }
  if ((param_2 & 1) == 0) {
    if ((param_2 & 2) != 0) {
      *PTR_REG_SNDCAP1CNT_0238a620 = *PTR_REG_SNDCAP1CNT_0238a620 | 0x80;
    }
  }
  else if ((param_2 & 2) == 0) {
    *PTR_REG_SNDCAP0CNT_0238a618 = *PTR_REG_SNDCAP0CNT_0238a618 | 0x80;
  }
  else {
    *(ushort *)PTR_REG_SNDCAP0CNT_0238a618 =
         *(ushort *)PTR_REG_SNDCAP0CNT_0238a618 | (ushort)DAT_0238a61c;
  }
  uVar2 = 0;
  for (; ((int)uVar2 < 8 && (param_3 != 0)); param_3 = param_3 >> 1) {
    if ((param_3 & 1) != 0) {
      FUN_0238a2b0(uVar2);
    }
    uVar2 = uVar2 + 1;
  }
  FUN_02385e2c();
  FUN_0238a164();
  return;
}



void FUN_0238a624(uint param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = 0;
  for (; ((int)uVar1 < 0x10 && (param_1 != 0)); param_1 = param_1 >> 1) {
    if ((param_1 & 1) != 0) {
      FUN_02386a64(uVar1,param_2);
    }
    uVar1 = uVar1 + 1;
  }
  return;
}



void FUN_0238a66c(uint param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = 0;
  for (; ((int)uVar1 < 0x10 && (param_1 != 0)); param_1 = param_1 >> 1) {
    if ((param_1 & 1) != 0) {
      FUN_02386af8(uVar1,param_2,param_3);
    }
    uVar1 = uVar1 + 1;
  }
  return;
}



void FUN_0238a6c4(uint param_1,short param_2)

{
  int iVar1;
  
  iVar1 = 0;
  for (; (iVar1 < 0x10 && (param_1 != 0)); param_1 = param_1 >> 1) {
    if ((param_1 & 1) != 0) {
      FUN_02386ae0(iVar1,param_2);
    }
    iVar1 = iVar1 + 1;
  }
  return;
}



void FUN_0238a70c(void)

{
                    // WARNING: Could not recover jumptable at 0x0238a718. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_0238a720)(7,DAT_0238a71c);
  return;
}



void FUN_0238a724(undefined4 param_1,uint param_2)

{
  FUN_02385e18();
  if (param_2 < 0x2000000) {
    if (param_2 == 0) {
      FUN_0238710c();
    }
  }
  else {
    FUN_023846e4(DAT_0238a774,param_2,0);
  }
  FUN_02385e2c();
  return;
}



void FUN_0238a778(void)

{
  ushort uVar1;
  ushort uVar2;
  int **ppiVar3;
  ushort *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  short sVar8;
  int *piVar9;
  undefined4 *puVar10;
  undefined4 *local_38;
  undefined4 *local_34;
  uint local_30;
  int *local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  
  uVar6 = DAT_0238abec;
  uVar5 = DAT_0238abe8;
  puVar4 = DAT_0238abe4;
  ppiVar3 = DAT_0238abe0;
  while (iVar7 = FUN_02384644(puVar4,&local_38,0), puVar10 = local_38, iVar7 != 0) {
    while (puVar10 != (undefined4 *)0x0) {
      local_34 = (undefined4 *)*puVar10;
      local_30 = puVar10[1];
      local_2c = (int *)puVar10[2];
      local_28 = puVar10[3];
      local_24 = puVar10[4];
      local_20 = puVar10[5];
      puVar10 = local_34;
      if (local_30 < 0x22) {
        sVar8 = (short)local_28;
        uVar2 = (ushort)(local_24 >> 8);
        uVar1 = (ushort)uVar5;
        switch(local_30) {
        case 0:
          FUN_02389b94((uint)local_2c,local_28,local_24,local_20);
          puVar10 = local_34;
          break;
        case 1:
          FUN_02389b38((uint)local_2c);
          puVar10 = local_34;
          break;
        case 2:
          FUN_02389bd0((uint)local_2c,local_28,local_24,local_20);
          puVar10 = local_34;
          break;
        case 3:
          FUN_02389bb0((int)local_2c);
          puVar10 = local_34;
          break;
        case 4:
          FUN_02389ab4((int)local_2c,local_28);
          puVar10 = local_34;
          break;
        case 5:
          FUN_023899e8((int)local_2c,local_28);
          puVar10 = local_34;
          break;
        case 6:
          FUN_0238978c((int)local_2c,local_28,local_24,local_20);
          puVar10 = local_34;
          break;
        case 7:
          FUN_023896e8((uint)local_2c & 0xffffff,local_28,local_24,local_20,(uint)local_2c >> 0x18);
          puVar10 = local_34;
          break;
        case 8:
          FUN_0238994c((int)local_2c,local_28,local_24);
          puVar10 = local_34;
          break;
        case 9:
          FUN_023898d4((int)local_2c,local_28,(short)local_24);
          puVar10 = local_34;
          break;
        case 10:
          FUN_0238a220((int)local_2c,local_28,(short)local_24);
          puVar10 = local_34;
          break;
        case 0xb:
          FUN_0238a204((int)local_2c,sVar8);
          puVar10 = local_34;
          break;
        case 0xc:
          FUN_0238a530((uint)local_2c,(byte)local_28,local_24);
          puVar10 = local_34;
          break;
        case 0xd:
          FUN_0238a46c((uint)local_2c,local_28,local_24,local_20);
          puVar10 = local_34;
          break;
        case 0xe:
          FUN_02386d10((uint)local_2c & uVar5,local_28 & 0x7ffffff,local_20 >> 0x18 & 3,
                       local_20 >> 0x1a & 3,(ushort)local_20 & uVar1,local_24 & uVar6,
                       local_24 >> 0x18 & 0x7f,local_24 >> 0x16 & 3,
                       uVar1 & (ushort)((uint)local_2c >> 0x10),local_20 >> 0x10 & 0x7f);
          puVar10 = local_34;
          break;
        case 0xf:
          FUN_02386c58((uint)local_2c,local_20,local_28 & 0x7f,local_28 >> 8 & 3,uVar1 & uVar2,
                       local_24 & 0x7f);
          puVar10 = local_34;
          break;
        case 0x10:
          FUN_02386ba8((uint)local_2c,local_28 & 0x7f,local_28 >> 8 & 3,uVar1 & uVar2,
                       local_24 & 0x7f);
          puVar10 = local_34;
          break;
        case 0x11:
          FUN_02387290(local_24 >> 0x1f,local_24 >> 0x1e & 1,local_2c,sVar8,local_24 >> 0x1d & 1,
                       local_24 >> 0x1c & 1,(byte)(local_24 >> 0x1b) & 1);
          puVar10 = local_34;
          break;
        case 0x12:
          FUN_0238a378((int)local_2c,local_28,0,local_24,0,local_20);
          puVar10 = local_34;
          break;
        case 0x13:
          FUN_0238a6c4((uint)local_2c,sVar8);
          puVar10 = local_34;
          break;
        case 0x14:
          FUN_0238a66c((uint)local_2c,local_28,local_24);
          puVar10 = local_34;
          break;
        case 0x15:
          FUN_0238a624((uint)local_2c,local_28);
          puVar10 = local_34;
          break;
        case 0x16:
          FUN_02386970(local_2c);
          puVar10 = local_34;
          break;
        case 0x17:
          FUN_023867cc((byte)local_2c);
          puVar10 = local_34;
          break;
        case 0x18:
          FUN_023869e4((int)local_2c);
          puVar10 = local_34;
          break;
        case 0x19:
          FUN_02386794((byte)local_2c,local_28,local_24,local_20);
          puVar10 = local_34;
          break;
        case 0x1a:
          FUN_02387778((uint)local_2c,local_28);
          puVar10 = local_34;
          break;
        case 0x1b:
          FUN_0238773c((uint)local_2c,local_28);
          puVar10 = local_34;
          break;
        case 0x1c:
          FUN_02387870((uint)local_2c);
          puVar10 = local_34;
          break;
        case 0x1d:
          *ppiVar3 = local_2c;
          break;
        case 0x1e:
          FUN_02389838((uint)local_2c,local_28);
          puVar10 = local_34;
          break;
        case 0x1f:
          FUN_023897d8((uint)local_2c,local_28);
          puVar10 = local_34;
          break;
        case 0x20:
          FUN_02387694((uint)local_2c,local_28);
          puVar10 = local_34;
          break;
        case 0x21:
          FUN_0238a400(local_2c);
          puVar10 = local_34;
        }
      }
    }
    piVar9 = *ppiVar3;
    *piVar9 = *piVar9 + 1;
  }
  return;
}



void FUN_0238abf0(void)

{
  FUN_02384778(DAT_0238ac24,DAT_0238ac28,8);
  FUN_0238a70c();
  *DAT_0238ac2c = 0;
  return;
}



void FUN_0238ac30(undefined4 param_1)

{
  if (*DAT_0238ac60 == 0) {
    *DAT_0238ac60 = 1;
    FUN_0238ac64(param_1);
  }
  return;
}



void FUN_0238ac64(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  *DAT_0238acac = param_1;
  iVar2 = FUN_02383aa4();
  *DAT_0238acb0 = iVar2;
  puVar1 = DAT_0238acb4;
  *DAT_0238acb4 = 0;
  puVar1[1] = 0;
  puVar1 = DAT_0238acb8;
  *DAT_0238acb8 = 0;
  puVar1[1] = 0;
  FUN_0238b708();
  return;
}



undefined4 FUN_0238acbc(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = DAT_0238ad00;
  FUN_02385e18();
  uVar2 = *(undefined4 *)(iVar1 + 0x3c);
  *(undefined4 *)(iVar1 + 0x3c) = param_1;
  FUN_02383ee0(iVar1 + 0x40,*(int *)(iVar1 + 0x3c),param_3,param_4);
  FUN_02385e2c();
  return uVar2;
}



void FUN_0238ad04(undefined4 param_1)

{
  *DAT_0238ad10 = param_1;
  return;
}



void FUN_0238ad14(void)

{
  undefined4 *puVar1;
  undefined4 extraout_r1;
  undefined4 uVar2;
  int iVar3;
  
  puVar1 = DAT_0238ada4;
  DAT_0238ada4[3] = 0xfffffffd;
  uVar2 = 0;
  puVar1[4] = 0;
  puVar1[6] = 0;
  *puVar1 = 0;
  puVar1[2] = 0;
  *(undefined2 *)(puVar1 + 5) = 0;
  *(undefined2 *)(puVar1 + 0x2f) = 0;
  puVar1[0xf] = 4;
  iVar3 = DAT_0238adb0;
  FUN_023841f8(DAT_0238ada8,DAT_0238adac,0,DAT_0238adb0,0x400,puVar1[0xf]);
  FUN_02384090((int)DAT_0238ada8,extraout_r1,uVar2,iVar3);
  FUN_02386530(0xb,DAT_0238adb4);
  if (*DAT_0238adb8 != 2) {
    FUN_0238ad04(1);
  }
  return;
}



void FUN_0238adbc(undefined4 param_1,undefined4 param_2,uint param_3,int param_4)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  uint extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 *puVar4;
  uint *puVar5;
  undefined4 *puVar6;
  longlong lVar7;
  
  puVar2 = DAT_0238aed8;
  puVar4 = DAT_0238aed8 + 0x10;
  puVar5 = DAT_0238aed8 + 0xe;
  puVar6 = DAT_0238aed8 + 0x2f;
LAB_0238ade0:
  bVar1 = false;
  lVar7 = FUN_02385e18();
  do {
    if ((puVar2[0xe] & 4) == 0) {
      if ((puVar2[0xe] & 0x10) != 0) break;
    }
    else if ((puVar2[0xe] & 8) != 0) goto LAB_0238ae40;
    puVar2[0x2e] = puVar4;
    FUN_02384134((ushort *)0x0,(int)((ulonglong)lVar7 >> 0x20),param_3);
    lVar7 = (ulonglong)extraout_r1 << 0x20;
  } while( true );
  *puVar5 = *puVar5 | 4;
  *puVar5 = *puVar5 & 0xffffffef;
  bVar1 = true;
LAB_0238ae40:
  FUN_02385e2c();
  if (bVar1) {
    *(undefined4 *)*puVar2 = 0;
    (**(code **)(DAT_0238aedc + puVar2[1] * 4))(puVar2);
    do {
      param_3 = 1;
      iVar3 = FUN_02386464(0xb,1,1);
    } while (iVar3 < 0);
    FUN_02385e18();
    puVar2[0xe] = puVar2[0xe] & 0xfffffff3;
    FUN_023840c4((ushort *)puVar6);
    if ((puVar2[0xe] & 0x10) != 0) {
      FUN_02384090((int)puVar4,extraout_r1_00,param_3,param_4);
    }
    FUN_02385e2c();
  }
  else {
    (*(code *)puVar2[0xd])(puVar2);
  }
  goto LAB_0238ade0;
}



void FUN_0238aee0(int param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = DAT_0238afc8;
  if (param_1 != 0xb) {
    return;
  }
  if (param_3 == 0) {
    return;
  }
  if (DAT_0238afc8[2] == 0) {
    DAT_0238afc8[1] = param_2;
  }
  iVar2 = puVar1[1];
  switch(iVar2) {
  case 0:
    iVar2 = puVar1[2];
    if ((iVar2 != 0) && (iVar2 == 1)) {
      *puVar1 = param_2;
      puVar1[0xe] = puVar1[0xe] | 0x10;
    }
    goto switchD_0238af10_caseD_d;
  case 1:
    goto switchD_0238af10_caseD_d;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  case 8:
    break;
  case 9:
    break;
  case 10:
    break;
  case 0xb:
    break;
  case 0xc:
    break;
  default:
    goto switchD_0238af10_caseD_d;
  }
  puVar1[0xe] = puVar1[0xe] | 0x10;
switchD_0238af10_caseD_d:
  if ((puVar1[0xe] & 0x10) == 0) {
    puVar1[2] = puVar1[2] + 1;
  }
  else {
    puVar1[2] = 0;
    if ((puVar1[0xe] & 4) == 0) {
      FUN_02384090((int)(puVar1 + 0x10),0,iVar2,param_4);
    }
    else {
      FUN_02384090(puVar1[0x2e],puVar1[0xe] & 4,iVar2,param_4);
    }
  }
  return;
}



void FUN_0238afcc(uint param_1)

{
  FUN_0238b53c();
  FUN_0238b370();
  FUN_0238b634(*(int *)(*DAT_0238b018 + 0x24) + 1);
  FUN_0238b2c4(param_1,0xd8);
  FUN_0238b554(*(int *)(*DAT_0238b018 + 0x38),0);
  return;
}



void FUN_0238b01c(uint param_1,int param_2,int param_3)

{
  FUN_0238b53c();
  *(undefined4 *)(DAT_0238b0b0 + 0xc) = 1;
  FUN_0238b634((*DAT_0238b0b4)[9] + 1 + param_3);
  FUN_0238b2c4(param_1,3);
  FUN_0238b4ac(param_2,0,param_3,DAT_0238b0b8);
  FUN_0238b554(0,0);
  if ((**DAT_0238b0b4 == 0) && (*(int *)(DAT_0238b0b0 + 0xc) == 0)) {
    **DAT_0238b0b4 = 1;
  }
  return;
}



void FUN_0238b0bc(uint param_1,int param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = (*DAT_0238b184)[8];
  FUN_0238b53c();
  while( true ) {
    if (param_3 == 0) {
      return;
    }
    uVar1 = iVar2 - (param_1 & iVar2 - 1U);
    if (param_3 < uVar1) {
      uVar1 = param_3;
    }
    FUN_0238b370();
    FUN_0238b634((*DAT_0238b184)[9] + 1 + uVar1);
    FUN_0238b2c4(param_1,10);
    FUN_0238b4ac(param_2,0,uVar1,DAT_0238b188);
    FUN_0238b554((*DAT_0238b184)[0xb],(*DAT_0238b184)[0xc]);
    if (**DAT_0238b184 != 0) break;
    param_2 = param_2 + uVar1;
    param_1 = param_1 + uVar1;
    param_3 = param_3 - uVar1;
  }
  return;
}



void FUN_0238b18c(uint param_1,int param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = (*DAT_0238b254)[8];
  FUN_0238b53c();
  while( true ) {
    if (param_3 == 0) {
      return;
    }
    uVar1 = iVar2 - (param_1 & iVar2 - 1U);
    if (param_3 < uVar1) {
      uVar1 = param_3;
    }
    FUN_0238b370();
    FUN_0238b634((*DAT_0238b254)[9] + 1 + uVar1);
    FUN_0238b2c4(param_1,2);
    FUN_0238b4ac(param_2,0,uVar1,DAT_0238b258);
    FUN_0238b554((*DAT_0238b254)[10],0);
    if (**DAT_0238b254 != 0) break;
    param_2 = param_2 + uVar1;
    param_1 = param_1 + uVar1;
    param_3 = param_3 - uVar1;
  }
  return;
}



void FUN_0238b25c(uint param_1,int param_2,int param_3)

{
  FUN_0238b53c();
  FUN_0238b634(*(int *)(*DAT_0238b2bc + 0x24) + 1 + param_3);
  FUN_0238b2c4(param_1,3);
  FUN_0238b4ac(0,param_2,param_3,DAT_0238b2c0);
  FUN_0238b554(0,0);
  return;
}



void FUN_0238b2c4(uint param_1,uint param_2)

{
  int iVar1;
  uint local_8 [2];
  
  iVar1 = *(int *)(*DAT_0238b368 + 0x24);
  if (iVar1 == 1) {
    local_8[0] = param_2 | param_1 >> 5 & 8 | (param_1 & 0xff) << 8;
  }
  else if (iVar1 == 2) {
    local_8[0] = param_2 | param_1 & 0xff00 | (param_1 & 0xff) << 0x10;
  }
  else if (iVar1 == 3) {
    local_8[0] = param_2 | param_1 >> 8 & 0xff00 | (param_1 & 0xff00) << 8 | param_1 << 0x18;
  }
  FUN_0238b4ac((int)local_8,0,iVar1 + 1,DAT_0238b36c);
  return;
}



void FUN_0238b370(void)

{
  FUN_0238b634(1);
  FUN_0238b4ac(DAT_0238b3ac,0,1,DAT_0238b3b0);
  FUN_0238b554(0,0);
  return;
}



void FUN_0238b4ac(int param_1,int param_2,int param_3,undefined *param_4)

{
  int *piVar1;
  undefined *puVar2;
  
  piVar1 = DAT_0238b530;
  DAT_0238b530[1] = param_1;
  piVar1[2] = param_2;
  puVar2 = PTR_REG_AUXSPICNT_0238b538;
  *(short *)PTR_REG_AUXSPICNT_0238b538 = (short)DAT_0238b534;
  for (; param_3 != 0; param_3 = param_3 + -1) {
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      *(undefined2 *)puVar2 = 0xa000;
    }
    do {
    } while ((*(ushort *)puVar2 & 0x80) != 0);
    (*(code *)param_4)(piVar1);
  }
  if (*piVar1 == 0) {
    *(undefined2 *)PTR_REG_AUXSPICNT_0238b538 = 0;
  }
  return;
}



void FUN_0238b53c(void)

{
                    // WARNING: Could not recover jumptable at 0x0238b548. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_0238b550)(0,DAT_0238b54c);
  return;
}



void FUN_0238b554(int param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  ushort local_28 [2];
  int local_24;
  ushort local_20 [2];
  int local_1c;
  
  bVar1 = true;
  if (param_1 + param_2 != 0) {
    if (param_1 != 0) {
      local_28[0] = *(ushort *)PTR_REG_VCOUNT_0238b62c;
      local_24 = param_1;
      while (bVar1 = FUN_0238b6b0(local_28), bVar1) {
        FUN_02385e7c(0);
      }
    }
    if (param_2 == 0) {
      bVar1 = FUN_0238b644();
    }
    else {
      local_20[0] = *(ushort *)PTR_REG_VCOUNT_0238b62c;
      local_1c = param_2 - param_1;
      bVar1 = false;
      while ((bVar1 == false && (bVar2 = FUN_0238b6b0(local_20), bVar2))) {
        FUN_02385e7c(0);
        bVar1 = FUN_0238b644();
      }
    }
  }
  if (bVar1 == false) {
    *(undefined4 *)*DAT_0238b630 = 4;
  }
  return;
}



void FUN_0238b634(undefined4 param_1)

{
  *DAT_0238b640 = param_1;
  return;
}



bool FUN_0238b644(void)

{
  byte local_8 [8];
  
  FUN_0238b634(2);
  FUN_0238b4ac(DAT_0238b6a4,0,1,DAT_0238b6a8);
  FUN_0238b4ac(0,(int)local_8,1,DAT_0238b6ac);
  FUN_0238b554(0,0);
  return (local_8[0] & 1) == 0;
}



bool FUN_0238b6b0(ushort *param_1)

{
  undefined uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = (uint)*(ushort *)PTR_REG_VCOUNT_0238b700 - (uint)*param_1;
  if (iVar3 != 0) {
    *param_1 = *(ushort *)PTR_REG_VCOUNT_0238b700;
    *(int *)(param_1 + 2) = *(int *)(param_1 + 2) - iVar3;
    if (iVar3 < 0) {
      *(int *)(param_1 + 2) = *(int *)(param_1 + 2) - DAT_0238b704;
    }
  }
  iVar2 = *(int *)(param_1 + 2);
  iVar3 = iVar2;
  if (0 < iVar2) {
    iVar3 = 1;
  }
  uVar1 = (undefined)iVar3;
  if (iVar2 < 1) {
    uVar1 = 0;
  }
  return (bool)uVar1;
}



void FUN_0238b708(void)

{
  int iVar1;
  
  iVar1 = DAT_0238b778;
  if (*(int *)(DAT_0238b778 + 0x38) == 0) {
    *(undefined4 *)(DAT_0238b778 + 0x38) = 1;
    *(undefined4 *)(iVar1 + 0x24) = 0;
    *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(iVar1 + 0x24);
    *(undefined4 *)(iVar1 + 0x1c) = *(undefined4 *)(iVar1 + 0x20);
    *(undefined4 *)(iVar1 + 0x28) = 0xffffffff;
    *(undefined4 *)(iVar1 + 0x2c) = 0;
    *(undefined4 *)(iVar1 + 0x30) = 0;
    *DAT_0238b77c = 0;
    FUN_0238ad14();
    *DAT_0238b784 = DAT_0238b780;
    FUN_0238bea4();
  }
  return;
}



undefined4 FUN_0238b788(undefined4 param_1,undefined4 param_2,uint param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  longlong lVar3;
  
  iVar1 = DAT_0238b7ec;
  lVar3 = FUN_02385e18();
  uVar2 = (undefined4)((ulonglong)lVar3 >> 0x20);
  while ((*(uint *)(iVar1 + 0x38) & 4) != 0) {
    FUN_02384134((ushort *)(iVar1 + 0xbc),uVar2,param_3);
    uVar2 = extraout_r1;
  }
  *(uint *)(iVar1 + 0x38) = *(uint *)(iVar1 + 0x38) | 4;
  FUN_02385e2c();
  *(undefined4 *)(iVar1 + 0x2c) = 0;
  *(undefined4 *)(iVar1 + 0x30) = 0;
  uVar2 = FUN_0238b868();
  FUN_0238ba64(uVar2,extraout_r1_00,param_3,param_4);
  return uVar2;
}



void FUN_0238b7f0(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_0238b85c;
  iVar1 = DAT_0238b858;
  *(uint *)(DAT_0238b85c + 0x28) = param_1;
  *(undefined4 *)(iVar2 + 0x1c) = param_2;
  *(undefined4 *)(iVar2 + 0x20) = param_3;
  *(undefined4 *)(iVar2 + 0x24) = param_4;
  *(undefined4 *)(iVar2 + 0x2c) = 0;
  *(undefined4 *)(iVar2 + 0x30) = 0;
  if (param_1 < 4) {
    FUN_02385fcc(param_1);
  }
  *(uint *)(iVar1 + 4) = *DAT_0238b860 & 0xf8ffffff | 0xa1000000;
  *(undefined4 *)(DAT_0238b85c + 0xb8) = *(undefined4 *)(DAT_0238b864 + 8);
  FUN_0238b8cc(iVar1);
  return;
}



undefined4 FUN_0238b868(void)

{
  undefined *puVar1;
  
  FUN_0238b9c4(0xb8000000,0);
  puVar1 = PTR_Gamecard_bus_timing_control_0238b8c4;
  *(uint *)PTR_Gamecard_bus_timing_control_0238b8c4 = *DAT_0238b8c0 & 0xf8ffe000 | 0xa7000000;
  do {
  } while ((*(uint *)puVar1 & 0x800000) == 0);
  return *(undefined4 *)PTR_Gamecard_bus_4_byte_data_in_for_manual_or_dma_read_0238b8c8;
}



void FUN_0238b8cc(int param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  puVar3 = PTR_Gamecard_bus_timing_control_0238b9c0;
  puVar2 = PTR_Gamecard_bus_4_byte_data_in_for_manual_or_dma_read_0238b9bc;
  iVar1 = DAT_0238b9b8;
  do {
    while( true ) {
      uVar6 = *(uint *)(iVar1 + 0x1c) & 0xfffffe00;
      if (((uVar6 != *(uint *)(iVar1 + 0x1c)) || ((*(uint *)(iVar1 + 0x20) & 3) != 0)) ||
         (uVar8 = *(uint *)(iVar1 + 0x20), *(uint *)(iVar1 + 0x24) < 0x200)) {
        *(uint *)(param_1 + 8) = uVar6;
        uVar8 = param_1 + 0x20;
      }
      FUN_0238b9c4(uVar6 >> 8 | 0xb7000000,0);
      uVar6 = 0;
      *(undefined4 *)puVar3 = *(undefined4 *)(param_1 + 4);
      do {
        uVar7 = *(uint *)puVar3;
        if (((uVar7 & 0x800000) != 0) && (uVar6 < 0x200)) {
          *(undefined4 *)(uVar8 + uVar6 * 4) = *(undefined4 *)puVar2;
          uVar6 = uVar6 + 1;
        }
      } while ((uVar7 & 0x80000000) != 0);
      if (uVar8 != *(uint *)(iVar1 + 0x20)) break;
      *(int *)(iVar1 + 0x1c) = *(int *)(iVar1 + 0x1c) + 0x200;
      *(int *)(iVar1 + 0x20) = *(int *)(iVar1 + 0x20) + 0x200;
      iVar5 = *(int *)(iVar1 + 0x24) + -0x200;
      *(int *)(iVar1 + 0x24) = iVar5;
      if (iVar5 == 0) {
        return;
      }
    }
    bVar4 = FUN_0238bae0(param_1);
  } while (bVar4);
  return;
}



void FUN_0238b9c4(undefined4 param_1,undefined4 param_2)

{
  do {
  } while ((*(uint *)PTR_Gamecard_bus_timing_control_0238ba3c & 0x80000000) != 0);
  *DAT_0238ba40 = 0xc0;
  *PTR_Gamecard_bus_8_byte_command_out_0238ba44 = (char)((uint)param_1 >> 0x18);
  *DAT_0238ba48 = (char)((uint)param_1 >> 0x10);
  *DAT_0238ba4c = (char)((uint)param_1 >> 8);
  *DAT_0238ba50 = (char)param_1;
  *DAT_0238ba54 = (char)((uint)param_2 >> 0x18);
  *DAT_0238ba58 = (char)((uint)param_2 >> 0x10);
  *DAT_0238ba5c = (char)((uint)param_2 >> 8);
  *DAT_0238ba60 = (char)param_2;
  return;
}



void FUN_0238ba64(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 *puVar1;
  undefined4 extraout_r1;
  undefined4 uVar2;
  code *pcVar3;
  
  puVar1 = DAT_0238badc;
  pcVar3 = (code *)DAT_0238badc[0xb];
  uVar2 = DAT_0238badc[0xc];
  *(undefined4 *)*DAT_0238badc = 0;
  FUN_02385e18();
  puVar1[0xe] = puVar1[0xe] & 0xfffffff3;
  FUN_023840c4((ushort *)(puVar1 + 0x2f));
  if ((puVar1[0xe] & 0x10) != 0) {
    FUN_02384090((int)(puVar1 + 0x10),extraout_r1,param_3,param_4);
  }
  FUN_02385e2c();
  if (pcVar3 != (code *)0x0) {
    (*pcVar3)(uVar2);
  }
  return;
}



bool FUN_0238bae0(int param_1)

{
  undefined uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  
  iVar2 = DAT_0238bb74;
  uVar3 = *(uint *)(DAT_0238bb74 + 0x1c) & 0xfffffe00;
  if (uVar3 == *(uint *)(param_1 + 8)) {
    iVar4 = *(int *)(DAT_0238bb74 + 0x1c) - uVar3;
    uVar3 = 0x200 - iVar4;
    if (*(uint *)(DAT_0238bb74 + 0x24) < uVar3) {
      uVar3 = *(uint *)(DAT_0238bb74 + 0x24);
    }
    FUN_02386200((undefined4 *)(param_1 + 0x20 + iVar4),*(undefined4 **)(DAT_0238bb74 + 0x20),uVar3)
    ;
    *(uint *)(iVar2 + 0x1c) = *(int *)(iVar2 + 0x1c) + uVar3;
    *(uint *)(iVar2 + 0x20) = *(int *)(iVar2 + 0x20) + uVar3;
    *(uint *)(iVar2 + 0x24) = *(int *)(iVar2 + 0x24) - uVar3;
  }
  iVar2 = *(int *)(iVar2 + 0x24);
  bVar5 = iVar2 != 0;
  if (bVar5) {
    iVar2 = 1;
  }
  uVar1 = (undefined)iVar2;
  if (!bVar5) {
    uVar1 = 0;
  }
  return (bool)uVar1;
}



void FUN_0238bc54(int param_1,undefined4 param_2)

{
  int iVar1;
  
  while (iVar1 = FUN_02386464(0xe,param_1,0), iVar1 != 0) {
    thunk_EXT_FUN_03803d98(param_2);
  }
  return;
}



void FUN_0238bc9c(void)

{
  FUN_02386830();
  FUN_0238dc08();
  FUN_02385ea8();
  return;
}



void FUN_0238bcbc(void)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  puVar2 = DAT_0238bd8c;
  puVar1 = DAT_0238bd88;
  if ((*DAT_0238bd80 == 0) && (*DAT_0238bd84 != 2)) {
    uVar5 = *DAT_0238bd88;
    if (uVar5 == 0xffffffff) {
      *DAT_0238bd88 = *DAT_0238bd8c + 10;
    }
    else if (uVar5 <= *DAT_0238bd8c) {
      uVar3 = *DAT_0238bd8c;
      *DAT_0238bd88 = uVar3 + 10;
      iVar4 = FUN_0238be28(uVar3 + 10,puVar1,(uint)puVar2,uVar5);
      if (((iVar4 == 0) || (*DAT_0238bd80 = 1, *DAT_0238bd90 == 0)) &&
         (*DAT_0238bd90 = 0, *DAT_0238bd80 != 0)) {
        FUN_0238bc54(0x11,100);
      }
    }
  }
  return;
}



bool FUN_0238bd94(void)

{
  bool bVar1;
  
  bVar1 = (*(uint *)PTR_REG_IF_0238bdb8 & 0x100000) == 0;
  if (!bVar1) {
    *DAT_0238bdbc = 1;
  }
  return bVar1;
}



void FUN_0238bdc0(undefined4 param_1,undefined4 param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar3;
  int *piVar2;
  
  piVar2 = DAT_0238be1c;
  if (*DAT_0238be18 != 0) {
    piVar2 = DAT_0238be20;
  }
  iVar1 = *piVar2;
  iVar3 = FUN_0238b788(iVar1,param_2,param_3,param_4);
  *DAT_0238be24 = (uint)(iVar3 != iVar1);
  return;
}



int FUN_0238be28(undefined4 param_1,undefined4 param_2,uint param_3,int param_4)

{
  if (*DAT_0238be70 == 0) {
    if ((*DAT_0238be74 & 1) == 0) {
      FUN_0238bd94();
    }
    else {
      FUN_0238bdc0(*DAT_0238be74 & 1,param_2,param_3,param_4);
    }
  }
  return *DAT_0238be70;
}



void FUN_0238be78(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x3f) == 1) {
    FUN_0238bc9c();
  }
  else {
    FUN_02385ea8();
  }
  return;
}



void FUN_0238bea4(void)

{
  bool bVar1;
  
  if (*DAT_0238befc == 0) {
    *DAT_0238befc = 1;
    thunk_EXT_FUN_037fe42c();
    do {
      bVar1 = FUN_02386508(0xe,0);
    } while (!bVar1);
    FUN_02386530(0xe,DAT_0238bf00);
  }
  return;
}



void FUN_0238c034(void)

{
  ushort *puVar1;
  uint *local_18 [2];
  
  puVar1 = DAT_0238c09c;
  do {
    FUN_02384644(puVar1,local_18,1);
    switch(*local_18[0]) {
    case 0:
      FUN_0238c598((int)local_18[0]);
      break;
    case 1:
      func_0x0137cc44();
      break;
    case 2:
      FUN_0238de38((int)local_18[0]);
      break;
    case 3:
      FUN_0238d134((int)local_18[0]);
    }
  } while( true );
}



void FUN_0238c0a0(void)

{
  undefined4 auStack_8 [2];
  
  FUN_023845cc(DAT_0238c0c4,auStack_8,0);
  return;
}



undefined4 FUN_0238c0c8(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  uint local_8;
  uint local_4;
  
  if ((param_3 & 0xffff) < 5) {
    local_8 = param_3;
    local_4 = param_4;
    FUN_02385e18();
    iVar3 = DAT_0238c18c;
    *(undefined4 *)(DAT_0238c190 + *(int *)(DAT_0238c18c + 0x454) * 0x18) = param_1;
    *(undefined4 *)(DAT_0238c194 + *(int *)(iVar3 + 0x454) * 0x18) = param_2;
    puVar2 = &local_8;
    for (iVar4 = 0; puVar2 = puVar2 + 1, iVar4 < (int)(local_8 & 0xffff); iVar4 = iVar4 + 1) {
      *(uint *)(*(int *)(iVar3 + 0x454) * 0x18 + iVar3 + iVar4 * 4 + 0x2dc) = *puVar2;
    }
    iVar3 = *(int *)(DAT_0238c18c + 0x454);
    *(uint *)(DAT_0238c18c + 0x454) = iVar3 + 1U & 0xf;
    FUN_02385e2c();
    uVar1 = FUN_023846e4(DAT_0238c198,iVar3 * 0x18 + DAT_0238c190,0);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



void FUN_0238c19c(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_0238c1d8;
  if (DAT_0238c1d8[1] == param_1) {
    DAT_0238c1d8[1] = 5;
    *puVar1 = 0;
    FUN_023840c4(DAT_0238c1dc);
  }
  return;
}



void FUN_0238c1e0(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_0238c1f4;
  *DAT_0238c1f4 = 1;
  puVar1[1] = param_1;
  return;
}



bool FUN_0238c1f8(void)

{
  undefined uVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = *DAT_0238c210;
  bVar3 = iVar2 == 0;
  if (bVar3) {
    iVar2 = 1;
  }
  uVar1 = (undefined)iVar2;
  if (!bVar3) {
    uVar1 = 0;
  }
  return (bool)uVar1;
}



void FUN_0238c214(uint param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  uint unaff_r4;
  
  uVar2 = param_1 & 0x70;
  if (0x30 < uVar2) {
    if (uVar2 < 0x51) {
      if ((0x4f < uVar2) || (uVar2 == 0x40)) {
        unaff_r4 = 9;
      }
    }
    else {
      if (uVar2 < 0x61) {
        if (uVar2 != 0x60) goto LAB_0238c2ac;
      }
      else if (uVar2 != 0x70) goto LAB_0238c2ac;
      unaff_r4 = 8;
    }
    goto LAB_0238c2ac;
  }
  if (uVar2 < 0x30) {
    if (uVar2 < 0x11) {
      if ((0xf < uVar2) || (uVar2 == 0)) {
        unaff_r4 = 6;
      }
      goto LAB_0238c2ac;
    }
    if (uVar2 != 0x20) goto LAB_0238c2ac;
  }
  unaff_r4 = 4;
LAB_0238c2ac:
  do {
    iVar1 = FUN_02386464(unaff_r4,(param_1 & 0xff | 0x80) << 8 | 0x3000000 | param_2 & 0xff,0);
  } while (iVar1 < 0);
  return;
}



void FUN_0238c2e8(int param_1)

{
  int *piVar1;
  
  if (((*DAT_0238c34c != 0) && (DAT_0238c34c[1] == 4)) && (DAT_0238c34c[0x117] == param_1)) {
    FUN_02385e18();
    piVar1 = DAT_0238c34c;
    DAT_0238c34c[1] = 5;
    *piVar1 = 0;
    piVar1[0x117] = 0;
    FUN_02385e2c();
    FUN_023840c4(DAT_0238c350);
  }
  return;
}



void FUN_0238c354(int param_1,undefined4 param_2,uint param_3)

{
  ushort *puVar1;
  int *piVar2;
  undefined4 extraout_r1;
  
  piVar2 = DAT_0238c3b4;
  puVar1 = DAT_0238c3b0;
  while (FUN_02385e18(), *piVar2 != 0) {
    FUN_02385e2c();
    FUN_02384134(puVar1,extraout_r1,param_3);
  }
  FUN_0238c1e0(4);
  DAT_0238c3b4[0x117] = param_1;
  FUN_02385e2c();
  return;
}



void FUN_0238c3b8(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 extraout_r1;
  undefined4 uVar3;
  undefined2 *puVar4;
  int iVar5;
  
  if (*DAT_0238c4b4 == 0) {
    *DAT_0238c4b4 = 1;
    puVar1 = DAT_0238c4b8;
    *DAT_0238c4b8 = 0;
    puVar1[1] = 5;
    FUN_0238ca80();
    func_0x0137d0c4();
    FUN_0238e40c();
    FUN_0238d490();
    thunk_EXT_FUN_037fe42c();
    FUN_02386530(6,DAT_0238c4bc);
    FUN_02386530(9,DAT_0238c4bc);
    FUN_02386530(8,DAT_0238c4bc);
    FUN_02386530(4,DAT_0238c4bc);
    FUN_02384778(DAT_0238c4c0,DAT_0238c4c4,0x10);
    iVar2 = DAT_0238c4c8;
    iVar5 = 0;
    do {
      FUN_0238616c((uint *)(iVar5 * 0x18 + iVar2),0,0x18);
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x10);
    uVar3 = 0;
    DAT_0238c4b8[0x115] = 0;
    *(undefined2 *)(DAT_0238c4cc + 0x58) = 0;
    puVar4 = DAT_0238c4c0;
    FUN_023841f8(DAT_0238c4d0,DAT_0238c4d4,0,(int)DAT_0238c4c0,0x200,param_1);
    FUN_02384090((int)DAT_0238c4d0,extraout_r1,uVar3,(int)puVar4);
  }
  return;
}



void FUN_0238c4d8(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_0238c51c;
  if (param_1 == 0) {
    FUN_0238c214(3,2);
  }
  else {
    *(int *)(DAT_0238c51c + 0x24) = param_1;
    *(int *)(iVar1 + 0x28) = param_1;
    FUN_0238c214(3,0);
  }
  return;
}



// WARNING: Could not reconcile some variable overlaps

void FUN_0238c520(uint param_1)

{
  int iVar1;
  undefined4 local_10;
  
  iVar1 = FUN_0238c0c8(0,0x10,1,param_1);
  if (iVar1 == 0) {
    local_10._2_2_ = (ushort)((local_10 & 0xf9ffffff) >> 0x10) | 0x600;
    local_10._0_2_ = (undefined2)(local_10 & 0xf9ffffff);
    *DAT_0238c590 = (undefined2)local_10;
    *DAT_0238c594 = local_10._2_2_;
    FUN_0238c214(0x10,param_1 & 0xff);
  }
  return;
}



void FUN_0238c598(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  int iVar6;
  undefined2 extraout_r1;
  uint uVar7;
  ushort local_2c [2];
  undefined2 local_28;
  undefined2 local_26;
  
  iVar4 = DAT_0238c7c4;
  iVar3 = DAT_0238c7c0;
  uVar2 = DAT_0238c7bc;
  iVar1 = DAT_0238c7b0;
  uVar7 = *(uint *)(param_1 + 4);
  if (uVar7 < 3) {
    if (uVar7 != 0) {
      if (uVar7 == 1) {
        if (*(int *)(DAT_0238c7b0 + 0x20) == 1) {
          for (uVar7 = 0; uVar7 < *(uint *)(param_1 + 8); uVar7 = uVar7 + 1) {
            iVar6 = FUN_0238f2e8(uVar7 * uVar2,*(uint *)(param_1 + 8));
            FUN_0238f2e8(*(int *)(param_1 + 0xc) + iVar6,uVar2);
            iVar6 = iVar1 + uVar7 * 2;
            *(undefined2 *)(iVar6 + 0xcc) = extraout_r1;
            FUN_02385b44((int *)(uVar7 * 0x28 + iVar3),(int)*(short *)(iVar6 + 0xcc),10,iVar4,uVar7)
            ;
          }
          FUN_0238c214(*(uint *)(param_1 + 4) & 0xffff,0);
          *(undefined4 *)(DAT_0238c7b0 + 0x20) = 2;
          return;
        }
        FUN_0238c214(1,3);
        return;
      }
      if (uVar7 != 2) {
        return;
      }
      if (*(int *)(DAT_0238c7b0 + 0x20) == 3) {
        FUN_023859ec(DAT_0238c7c8);
        FUN_0238c214(*(uint *)(param_1 + 4) & 0xffff,0);
        *(undefined4 *)(DAT_0238c7b0 + 0x20) = 0;
        return;
      }
      FUN_0238c214(2,3);
      return;
    }
  }
  else {
    if (uVar7 != 0x10) {
      return;
    }
    if (*(int *)(DAT_0238c7b0 + 0x20) != 2) {
      return;
    }
  }
  FUN_02385e18();
  bVar5 = FUN_0238c1f8();
  if (bVar5) {
    FUN_0238c1e0(0);
    FUN_02385e2c();
    FUN_0238cb90((uint *)&local_28,*(int *)(DAT_0238c7b0 + 0x24),local_2c);
    FUN_0238c7cc((int *)&local_28,(uint)local_2c[0]);
    *DAT_0238c7b4 = local_28;
    *DAT_0238c7b8 = local_26;
    if (*(uint *)(param_1 + 4) == 0) {
      FUN_0238c214(0,0);
    }
    else {
      FUN_0238c214(*(uint *)(param_1 + 4) & 0xffff,*(uint *)(param_1 + 8) & 0xff);
    }
    FUN_0238c19c(0);
  }
  else {
    FUN_02385e2c();
    FUN_0238c214(*(uint *)(param_1 + 4) & 0xffff,4);
  }
  return;
}



void FUN_0238c7cc(int *param_1,int param_2)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  
  pbVar1 = DAT_0238c8b4;
  if (*param_1 << 7 < 0) {
    if ((uint)(*param_1 << 5) >> 0x1e == 0) {
      *DAT_0238c8b4 = 0;
      iVar3 = DAT_0238c8bc;
      pbVar2 = DAT_0238c8b8;
      iVar4 = *(int *)(DAT_0238c8bc + 0x24);
      if (param_2 < iVar4 >> 1) {
        *DAT_0238c8b8 = *DAT_0238c8b8 + 1;
        if ((3 < *pbVar2) && (*pbVar2 = 0, *(int *)(iVar3 + 0x28) < iVar4)) {
          *(int *)(iVar3 + 0x24) = iVar4 + -1;
          *pbVar1 = 3;
        }
      }
      else {
        *DAT_0238c8b8 = 0;
      }
    }
    else {
      *DAT_0238c8b8 = 0;
      pbVar1 = DAT_0238c8b4;
      *DAT_0238c8b4 = *DAT_0238c8b4 + 1;
      if (3 < *pbVar1) {
        *pbVar1 = 0;
        if (*(int *)(DAT_0238c8bc + 0x24) < 0x23) {
          *(int *)(DAT_0238c8bc + 0x24) = *(int *)(DAT_0238c8bc + 0x24) + 1;
        }
      }
    }
  }
  else {
    *DAT_0238c8b4 = 0;
    *DAT_0238c8b8 = 0;
  }
  return;
}



void FUN_0238c8c0(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  ushort *puVar2;
  uint uVar3;
  int iVar4;
  
  puVar2 = DAT_0238ca78;
  if ((param_1 & 0x2000000) != 0) {
    iVar4 = 0;
    param_4 = 0;
    do {
      puVar2[iVar4] = 0;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x10);
  }
  puVar2 = DAT_0238ca78;
  DAT_0238ca78[(param_1 & 0xf0000) >> 0x10] = (ushort)param_1;
  if ((param_1 & 0x1000000) != 0) {
    uVar3 = (uint)*puVar2;
    uVar1 = ((uVar3 & 0xff00) << 8) >> 0x10;
    switch(uVar1) {
    case 0:
      iVar4 = FUN_0238c0c8(0,uVar1,0,param_4);
      if (iVar4 == 0) {
        FUN_0238c214(uVar1,4);
      }
      break;
    case 1:
      if (*(int *)(puVar2 + 0x10) == 0) {
        if (((*puVar2 & 0xff) == 0) || (4 < (uVar3 & 0xff))) {
          FUN_0238c214(uVar1,2);
        }
        else if (puVar2[1] < DAT_0238ca7c) {
          iVar4 = FUN_0238c0c8(0,uVar1,2,uVar3 & 0xff);
          if (iVar4 == 0) {
            FUN_0238c214(uVar1,4);
          }
          else {
            *(undefined4 *)(DAT_0238ca78 + 0x10) = 1;
          }
        }
        else {
          FUN_0238c214(uVar1,2);
        }
      }
      else {
        FUN_0238c214(uVar1,3);
      }
      break;
    case 2:
      if (*(int *)(puVar2 + 0x10) == 2) {
        iVar4 = FUN_0238c0c8(0,uVar1,0,param_4);
        if (iVar4 == 0) {
          FUN_0238c214(uVar1,4);
        }
        else {
          *(undefined4 *)(DAT_0238ca78 + 0x10) = 3;
        }
      }
      else {
        FUN_0238c214(uVar1,3);
      }
      break;
    case 3:
      FUN_0238c4d8(uVar3 & 0xff);
      break;
    default:
      FUN_0238c214(uVar1,1);
    }
  }
  return;
}



void FUN_0238ca80(void)

{
  int iVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar1 = DAT_0238cb74;
  iVar3 = 0;
  *(undefined4 *)(DAT_0238cb74 + 0x20) = 0;
  *(undefined4 *)(iVar1 + 0x24) = 0x14;
  *(undefined4 *)(iVar1 + 0x28) = 0x14;
  do {
    *(undefined2 *)(iVar1 + iVar3 * 2) = 0;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x10);
  sVar2 = FUN_02385d8c();
  if (sVar2 == 0) {
    FUN_02385d9c();
  }
  iVar3 = DAT_0238cb7c;
  iVar1 = DAT_0238cb78;
  iVar4 = 0;
  do {
    puVar5 = (undefined4 *)(iVar4 * 0x28 + iVar1);
    FUN_02385c74(puVar5);
    FUN_02385abc((int)puVar5,iVar3);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 4);
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238cb80 & 0x80) != 0);
  *(short *)PTR_SPI_bus_Control_0238cb80 = (short)DAT_0238cb84;
  *(undefined2 *)PTR_SPI_bus_Data_0238cb88 = 0x84;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238cb80 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Data_0238cb88 = 0;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238cb80 & 0x80) != 0);
  *(short *)PTR_SPI_bus_Control_0238cb80 = (short)DAT_0238cb8c;
  *(undefined2 *)PTR_SPI_bus_Data_0238cb88 = 0;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238cb80 & 0x80) != 0);
  return;
}



void FUN_0238cb90(uint *param_1,int param_2,ushort *param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  ushort local_20;
  ushort local_1e;
  ushort local_1c [4];
  
  *param_3 = 0;
  if (param_2 < 0) {
    param_2 = -param_2;
  }
  iVar3 = FUN_0238cfd8();
  if (iVar3 == 0) {
    *param_1 = *param_1 & 0xfffff000;
    *param_1 = *param_1 & DAT_0238cdc4;
    *param_1 = *param_1 & 0xfeffffff;
    *param_1 = *param_1 & 0xf9ffffff | 0x6000000;
    *DAT_0238cdc8 = 0;
  }
  else {
    uVar4 = FUN_0238cde0(&local_20,param_2,0,&local_1e);
    *param_1 = *param_1 & 0xf9ffffff | (uVar4 & 3) << 0x19;
    *param_1 = *param_1 & 0xfffff000 | local_20 & DAT_0238cdcc;
    iVar5 = FUN_0238cde0(&local_20,param_2,1,local_1c);
    if (iVar5 == 2) {
      *param_1 = *param_1 & 0xf9ffffff | ((*param_1 << 5) >> 0x1e | 2) << 0x19;
    }
    *param_1 = *param_1 & DAT_0238cdc4 | (local_20 & DAT_0238cdcc) << 0xc;
    puVar1 = PTR_SPI_bus_Control_0238cdd4;
    *(short *)PTR_SPI_bus_Control_0238cdd4 = (short)DAT_0238cdd0;
    puVar2 = PTR_SPI_bus_Data_0238cdd8;
    iVar5 = 0;
    do {
      *(undefined2 *)puVar2 = 0;
      do {
      } while ((*(ushort *)puVar1 & 0x80) != 0);
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0xc);
    *(short *)puVar1 = (short)DAT_0238cddc;
    *(undefined2 *)PTR_SPI_bus_Data_0238cdd8 = 0;
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_0238cdd4 & 0x80) != 0);
    if (iVar3 == 2) {
      *param_1 = *param_1 & 0xf9ffffff | 0x6000000;
    }
    iVar3 = FUN_0238cfd8();
    if (iVar3 == 0) {
      *param_1 = *param_1 & 0xfeffffff;
      *DAT_0238cdc8 = 0;
    }
    else if (iVar3 == 1) {
      *param_1 = *param_1 | 0x1000000;
      *DAT_0238cdc8 = 1;
      if (local_1e < local_1c[0]) {
        local_1e = local_1c[0];
      }
      *param_3 = local_1e;
    }
    else if (iVar3 == 2) {
      *param_1 = *param_1 | 0x1000000;
      *param_1 = *param_1 & 0xf9ffffff | 0x6000000;
      *DAT_0238cdc8 = 0;
    }
    else {
      FUN_02385ea8();
    }
  }
  return;
}



undefined4 FUN_0238cde0(ushort *param_1,int param_2,int param_3,undefined2 *param_4)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint local_38 [6];
  
  puVar1 = PTR_SPI_bus_Control_0238cfc4;
  if (param_3 == 0) {
    uVar4 = 0xd1;
    uVar5 = 1;
  }
  else {
    uVar4 = 0x91;
    uVar5 = 2;
  }
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238cfc4 & 0x80) != 0);
  *(short *)PTR_SPI_bus_Control_0238cfc4 = (short)DAT_0238cfc8;
  *(undefined2 *)PTR_SPI_bus_Data_0238cfcc = uVar4;
  uVar8 = DAT_0238cfd0;
  puVar3 = PTR_SPI_bus_Data_0238cfcc;
  puVar2 = PTR_SPI_bus_Control_0238cfc4;
  do {
  } while ((*(ushort *)puVar1 & 0x80) != 0);
  iVar6 = 0;
  do {
    *(undefined2 *)puVar3 = 0;
    do {
    } while ((*(ushort *)puVar2 & 0x80) != 0);
    local_38[iVar6] = ((*(ushort *)puVar3 & 0xff) << 0x10) >> 8;
    *(undefined2 *)puVar3 = uVar4;
    do {
    } while ((*(ushort *)puVar2 & 0x80) != 0);
    local_38[iVar6] = local_38[iVar6] | *(ushort *)puVar3 & 0xff;
    local_38[iVar6] = (int)(local_38[iVar6] & uVar8) >> 3;
    iVar6 = iVar6 + 1;
  } while (iVar6 < 5);
  *(short *)puVar2 = (short)DAT_0238cfd4;
  *(undefined2 *)puVar3 = 0;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238cfc4 & 0x80) != 0);
  iVar6 = 0;
  iVar7 = 0;
  do {
    iVar9 = iVar7;
    while (iVar9 = iVar9 + 1, iVar9 < 5) {
      iVar10 = local_38[iVar7] - local_38[iVar9];
      if (iVar10 < 0) {
        iVar10 = -iVar10;
      }
      if (iVar6 < iVar10) {
        iVar6 = iVar10;
      }
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 < 4);
  *param_4 = (short)iVar6;
  iVar6 = 0;
  do {
    if (2 < iVar6) {
      *param_1 = (ushort)((int)(local_38[0] + local_38[4]) >> 1) & 0xfff8;
      return uVar5;
    }
    uVar8 = local_38[iVar6];
    iVar7 = iVar6;
    while (iVar7 = iVar7 + 1, iVar7 < 4) {
      iVar9 = uVar8 - local_38[iVar7];
      if (iVar9 < 0) {
        iVar9 = -iVar9;
      }
      iVar10 = iVar7;
      if (iVar9 <= param_2) {
        while (iVar10 = iVar10 + 1, iVar10 < 5) {
          iVar9 = uVar8 - local_38[iVar10];
          if (iVar9 < 0) {
            iVar9 = -iVar9;
          }
          if (iVar9 <= param_2) {
            *param_1 = (ushort)((int)(local_38[iVar10] + local_38[iVar7] + uVar8 * 2) >> 2) & 0xfff8
            ;
            return 0;
          }
        }
      }
    }
    iVar6 = iVar6 + 1;
  } while( true );
}



undefined FUN_0238cfd8(void)

{
  undefined uVar1;
  
  FUN_02386678(0x8000);
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238d11c & 0x80) != 0);
  *(short *)PTR_SPI_bus_Control_0238d11c = (short)DAT_0238d120;
  *(undefined2 *)PTR_SPI_bus_Data_0238d124 = 0x84;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238d11c & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Data_0238d124 = 0;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238d11c & 0x80) != 0);
  *(short *)PTR_SPI_bus_Control_0238d11c = (short)DAT_0238d128;
  *(undefined2 *)PTR_SPI_bus_Data_0238d124 = 0;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238d11c & 0x80) != 0);
  if (*DAT_0238d12c == 0) {
    uVar1 = (*(ushort *)PTR_REG_EXTKEYIN_0238d130 & 0x40) == 0;
  }
  else if ((*(ushort *)PTR_REG_EXTKEYIN_0238d130 & 0x40) == 0) {
    uVar1 = 1;
  }
  else {
    *(short *)PTR_SPI_bus_Control_0238d11c = (short)DAT_0238d120;
    *(undefined2 *)PTR_SPI_bus_Data_0238d124 = 0x84;
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_0238d11c & 0x80) != 0);
    *(undefined2 *)PTR_SPI_bus_Data_0238d124 = 0;
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_0238d11c & 0x80) != 0);
    *(short *)PTR_SPI_bus_Control_0238d11c = (short)DAT_0238d128;
    *(undefined2 *)PTR_SPI_bus_Data_0238d124 = 0;
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_0238d11c & 0x80) != 0);
    if ((*(ushort *)PTR_REG_EXTKEYIN_0238d130 & 0x40) == 0) {
      uVar1 = 2;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}



void FUN_0238d134(int param_1)

{
  int iVar1;
  bool bVar2;
  ushort uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 uVar6;
  
  FUN_02385e18();
  bVar2 = FUN_0238c1f8();
  if (bVar2) {
    FUN_0238c1e0(3);
    FUN_02385e2c();
    iVar1 = DAT_0238d2b0;
    switch(*(uint *)(param_1 + 4)) {
    case 0x61:
      *(undefined4 *)(DAT_0238d2b0 + 0x20) = 1;
      *DAT_0238d2b4 = (short)*(undefined4 *)(param_1 + 8);
      *DAT_0238d2b8 = (short)*(undefined4 *)(param_1 + 0xc);
      FUN_0238d830();
      break;
    case 0x62:
    default:
      FUN_0238c214(*(uint *)(param_1 + 4) & 0xffff,1);
      break;
    case 99:
      *(undefined4 *)(DAT_0238d2b0 + 0x20) = 2;
      uVar4 = *(undefined4 *)(param_1 + 8);
      *(undefined4 *)(iVar1 + 0x24) = uVar4;
      FUN_0238d6fc(uVar4);
      FUN_0238c214(99,0);
      break;
    case 100:
      *(undefined4 *)(DAT_0238d2b0 + 0x20) = 4;
      uVar6 = *(undefined4 *)(param_1 + 8);
      *(undefined4 *)(iVar1 + 0x28) = uVar6;
      uVar4 = *(undefined4 *)(param_1 + 0xc);
      *(undefined4 *)(iVar1 + 0x24) = uVar4;
      FUN_0238d608((ushort)uVar6,(ushort)uVar4 & 0xff);
      FUN_0238c214(100,0);
      break;
    case 0x65:
      *(undefined4 *)(DAT_0238d2b0 + 0x20) = 3;
      uVar5 = *(uint *)(param_1 + 8);
      *(uint *)(iVar1 + 0x28) = uVar5;
      uVar3 = FUN_0238d578((ushort)uVar5);
      FUN_0238c214((uVar5 & 0xffff) + 0x70 & 0xffff,(uint)uVar3);
      break;
    case 0x66:
      FUN_0238d694(*(int *)(param_1 + 8));
    }
    FUN_0238c19c(3);
  }
  else {
    FUN_02385e2c();
    FUN_0238c214(*(uint *)(param_1 + 4) & 0xffff,4);
  }
  return;
}



void FUN_0238d2bc(uint param_1)

{
  ushort *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  puVar1 = DAT_0238d488;
  if ((param_1 & 0x2000000) != 0) {
    iVar4 = 0;
    do {
      puVar1[iVar4] = 0;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x10);
  }
  puVar1 = DAT_0238d488;
  DAT_0238d488[(param_1 & 0xf0000) >> 0x10] = (ushort)param_1;
  if ((param_1 & 0x1000000) != 0) {
    uVar3 = (uint)*puVar1;
    uVar2 = ((uVar3 & 0xff00) << 8) >> 0x10;
    switch(uVar2) {
    case 0x60:
      FUN_0238c214(0x60,0);
      break;
    case 0x61:
      iVar4 = FUN_0238c0c8(3,uVar2,2,uVar3 & 0xff);
      if (iVar4 == 0) {
        FUN_0238c214(uVar2,4);
      }
      break;
    case 0x62:
    default:
      FUN_0238c214(uVar2,1);
      break;
    case 99:
      iVar4 = FUN_0238c0c8(3,uVar2,1,puVar1[1] & DAT_0238d48c | (uVar3 & 0xff) << 0x10);
      if (iVar4 == 0) {
        FUN_0238c214(uVar2,4);
      }
      break;
    case 100:
      iVar4 = FUN_0238c0c8(3,uVar2,2,uVar3 & 0xff);
      if (iVar4 == 0) {
        FUN_0238c214(uVar2,4);
      }
      break;
    case 0x65:
      iVar4 = FUN_0238c0c8(3,uVar2,1,uVar3 & DAT_0238d48c);
      if (iVar4 == 0) {
        FUN_0238c214(uVar2,4);
      }
      break;
    case 0x66:
      FUN_0238da18(uVar3 & 0xff);
      FUN_0238c214(0x66,0);
      break;
    case 0x67:
      uVar2 = FUN_0238da08();
      FUN_0238c214(0x67,uVar2 & 0xffff);
    }
  }
  return;
}



void FUN_0238d490(void)

{
  int iVar1;
  int iVar2;
  
  *DAT_0238d4c4 = 1;
  iVar1 = DAT_0238d4c8;
  iVar2 = 0;
  *(undefined4 *)(DAT_0238d4c8 + 0x20) = 0;
  do {
    *(undefined2 *)(iVar1 + iVar2 * 2) = 0;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  return;
}



void FUN_0238d4cc(undefined4 param_1,undefined4 param_2,uint param_3)

{
                    // WARNING: Could not recover jumptable at 0x0238d4ec. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_0238d4f4)(param_3 & DAT_0238d4f0);
  return;
}



void FUN_0238d4f8(int param_1)

{
  int iVar1;
  
  do {
    iVar1 = FUN_02386464(8,param_1,0);
  } while (iVar1 != 0);
  return;
}



void FUN_0238d528(ushort param_1)

{
  ushort uVar1;
  
  uVar1 = FUN_0238d578(0);
  FUN_0238d608(0,uVar1 & ~param_1 & 0xff);
  return;
}



void FUN_0238d554(ushort param_1)

{
  ushort uVar1;
  
  uVar1 = FUN_0238d578(0);
  FUN_0238d608(0,uVar1 | param_1);
  return;
}



ushort FUN_0238d578(ushort param_1)

{
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238d600 & 0x80) != 0);
  FUN_0238d678(1);
  *(ushort *)PTR_SPI_bus_Data_0238d604 = param_1 & 0xff | 0x80;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238d600 & 0x80) != 0);
  FUN_0238d678(0);
  *(undefined2 *)PTR_SPI_bus_Data_0238d604 = 0;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238d600 & 0x80) != 0);
  return *(ushort *)PTR_SPI_bus_Data_0238d604 & 0xff;
}



void FUN_0238d608(ushort param_1,ushort param_2)

{
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238d670 & 0x80) != 0);
  FUN_0238d678(1);
  *(ushort *)PTR_SPI_bus_Data_0238d674 = param_1 & 0xff;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238d670 & 0x80) != 0);
  FUN_0238d678(0);
  *(ushort *)PTR_SPI_bus_Data_0238d674 = param_2 & 0xff;
  return;
}



void FUN_0238d678(int param_1)

{
  *(ushort *)PTR_SPI_bus_Control_0238d690 = (ushort)DAT_0238d68c | (ushort)(param_1 << 0xb);
  return;
}



void FUN_0238d694(int param_1)

{
  if (param_1 == 1) {
    FUN_0238d528(0x10);
  }
  else if (param_1 == 2) {
    FUN_0238d528(0x20);
    FUN_0238d554(0x10);
  }
  else if (param_1 == 3) {
    FUN_0238d554(0x30);
  }
  else {
    FUN_02385ea8();
  }
  *DAT_0238d6f8 = param_1;
  return;
}



void FUN_0238d6fc(undefined4 param_1)

{
  switch(param_1) {
  case 0:
    break;
  case 1:
    FUN_0238da18(1);
    FUN_0238d694(1);
    break;
  case 2:
    FUN_0238da18(3);
    FUN_0238d694(3);
    break;
  case 3:
    FUN_0238da18(2);
    FUN_0238d694(2);
    break;
  case 4:
    FUN_0238d554(4);
    break;
  case 5:
    FUN_0238d528(4);
    break;
  case 6:
    FUN_0238d554(8);
    break;
  case 7:
    FUN_0238d528(8);
    break;
  case 8:
    FUN_0238d554(0xc);
    break;
  case 9:
    FUN_0238d528(0xc);
    break;
  case 10:
    FUN_0238d554(1);
    break;
  case 0xb:
    FUN_0238d528(1);
    break;
  case 0xc:
    FUN_0238d554(2);
    break;
  case 0xd:
    FUN_0238d528(2);
    break;
  case 0xe:
    FUN_02386830();
    FUN_0238d528(1);
    FUN_0238d554(0x40);
    break;
  case 0xf:
    FUN_0238d528(0x40);
  }
  return;
}



undefined2 FUN_0238d830(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  ushort uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined2 unaff_r5;
  undefined4 uVar6;
  
  uVar1 = *(undefined2 *)PTR_REG_IME_0238d9e4;
  *(undefined2 *)PTR_REG_IME_0238d9e4 = 0;
  FUN_02385e18();
  uVar4 = FUN_023838dc(0x1ffffff);
  uVar3 = FUN_0238d578(0);
  FUN_0238da18(2);
  FUN_0238d694(2);
  FUN_0238d694(2);
  FUN_02386830();
  FUN_0238d528(1);
  if ((*DAT_0238d9e8 & 1) != 0) {
    *(ushort *)PTR_REG_keycnt_0238d9f0 = *DAT_0238d9ec | 0x4000;
    FUN_02383918(0x1000);
  }
  if ((*DAT_0238d9e8 & 4) != 0) {
    FUN_02383918(0x400000);
  }
  if ((*DAT_0238d9e8 & 2) != 0) {
    unaff_r5 = *(undefined2 *)PTR_REG_Debug_RCNT_0238d9f4;
    FUN_02386678(0x8000);
    FUN_02386694(0x40,0x40);
    FUN_02386694(0x100,0x100);
    FUN_02383918(0x80);
  }
  if ((*DAT_0238d9e8 & 8) != 0) {
    FUN_02383918(0x100000);
  }
  if ((*DAT_0238d9e8 & 0x10) != 0) {
    FUN_02383918(0x2000);
  }
  FUN_02385e2c();
  *(undefined2 *)PTR_REG_IME_0238d9e4 = 1;
  thunk_EXT_FUN_03803db6();
  FUN_0238d608(0,uVar3);
  if ((*DAT_0238d9e8 & 0x20) == 0) {
    uVar5 = 7;
  }
  else {
    uVar5 = 6;
  }
  if ((*DAT_0238d9e8 & 0x40) == 0) {
    uVar6 = 5;
  }
  else {
    uVar6 = 4;
  }
  FUN_0238d6fc(uVar5);
  FUN_0238d6fc(uVar6);
  *(undefined2 *)PTR_REG_Debug_RCNT_0238d9f4 = unaff_r5;
  FUN_0238d554(1);
  FUN_023867dc();
  *(undefined4 *)(DAT_0238d9f8 + 0x20) = 0;
  FUN_0238d4cc(0x62,0,0);
  FUN_02385e18();
  FUN_02383950(uVar4);
  FUN_02385e2c();
  uVar2 = *(undefined2 *)PTR_REG_IME_0238d9e4;
  *(undefined2 *)PTR_REG_IME_0238d9e4 = uVar1;
  return uVar2;
}



void thunk_EXT_FUN_03803db6(void)

{
                    // WARNING: Could not recover jumptable at 0x0238da00. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_0238da04)();
  return;
}



undefined4 FUN_0238da08(void)

{
  return *DAT_0238da14;
}



void FUN_0238da18(int param_1)

{
  if (param_1 < 0x10) {
    *DAT_0238da34 = param_1;
    *DAT_0238da38 = 0;
  }
  return;
}



void FUN_0238da3c(void)

{
  bool bVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  
  iVar3 = DAT_0238db5c;
  uVar5 = *DAT_0238db54;
  if (uVar5 == 0) {
    iVar3 = FUN_0238c0c8(3,0x66,1,1);
    if (iVar3 != 0) {
      FUN_0238da18(1);
    }
  }
  else if ((int)uVar5 < 4) {
    if (uVar5 != *DAT_0238db58) {
      FUN_0238c0c8(3,0x66,1,uVar5);
    }
  }
  else {
    iVar7 = (uVar5 - 4) * 0xc;
    iVar6 = DAT_0238db5c + iVar7;
    uVar5 = FUN_0238f2e8(*DAT_0238db60,(uint)*(ushort *)(iVar6 + 10));
    puVar2 = DAT_0238db60;
    bVar8 = (*(uint *)(iVar6 + 4) & 0x80000000U >> (uVar5 & 0xff)) == 0;
    bVar1 = (*(uint *)(iVar3 + iVar7) &
            (0U >> (uVar5 & 0xff) | -0x80000000 << (0x20 - uVar5 & 0xff) |
            0x80000000U >> (uVar5 - 0x20 & 0xff))) != 0;
    uVar5 = (uint)(!bVar8 || bVar1);
    if (bVar8 && !bVar1) {
      uVar5 = 2;
    }
    uVar4 = *DAT_0238db60;
    *DAT_0238db60 = uVar4 + 1;
    if ((uint)*(ushort *)(iVar6 + 8) * (uint)*(ushort *)(iVar6 + 10) <= uVar4 + 1) {
      *puVar2 = 0;
    }
    if (uVar5 != *DAT_0238db58) {
      FUN_0238c0c8(3,0x66,1,uVar5);
    }
  }
  return;
}



void FUN_0238db64(undefined4 param_1)

{
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_58 = DAT_0238dbfc;
  local_54 = DAT_0238dc00;
  local_50 = 0x600;
  local_4c = 4;
  local_38 = 0;
  local_34 = 8;
  local_2c = DAT_0238dc04;
  local_28 = 0x1c0;
  local_24 = 3;
  local_3c = 0x40;
  local_1c = 3;
  local_c = 4;
  local_14 = 5;
  local_20 = 7;
  local_10 = 8;
  local_18 = 9;
  local_30 = param_1;
  func_0x0136875c(&local_58,&local_24);
  return;
}



void FUN_0238dc08(void)

{
  *(ushort *)PTR_REG_POWCNT2_0238dc3c = *(ushort *)PTR_REG_POWCNT2_0238dc3c & 0xfffd;
  FUN_0238da18(1);
  FUN_0238d694(1);
  return;
}



void FUN_0238dc40(undefined4 param_1)

{
  *DAT_0238dc84 = 0;
  *DAT_0238dc88 = param_1;
  FUN_0238616c(DAT_0238dc8c,0,0x78);
  FUN_0238db64(param_1);
  *DAT_0238dc90 = 3;
  return;
}



void FUN_0238dc94(void)

{
  ushort uVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  ushort *puVar7;
  ushort *puVar8;
  ushort uVar9;
  ushort uVar10;
  
  iVar2 = DAT_0238ddec;
  uVar1 = *(ushort *)(DAT_0238ddec + 0x26);
  uVar9 = *(ushort *)(DAT_0238ddec + 0x38);
  uVar5 = DAT_0238ddf0;
  if ((uVar1 & 4) != 4) {
    uVar5 = (uint)*(ushort *)(DAT_0238ddec + 0x3a);
  }
  iVar4 = FUN_0238c0a0();
  if ((iVar4 == 0) && (bVar3 = FUN_0238c1f8(), bVar3)) {
    if ((uVar1 & 1) == 1) {
      uVar5 = FUN_0238e44c();
      if ((uVar1 & 2) != 0) {
        uVar5 = uVar5 ^ 0x8000;
      }
    }
    else {
      uVar5 = FUN_0238e514();
      if ((uVar1 & 2) != 0) {
        uVar5 = uVar5 ^ 0x80;
      }
    }
  }
  puVar8 = DAT_0238ddf4;
  uVar10 = (ushort)uVar5;
  uVar6 = *(uint *)(iVar2 + 0x2c);
  if ((uVar1 & 1) == 1) {
    puVar7 = (ushort *)(*(int *)(iVar2 + 0x28) + uVar6);
    *puVar7 = uVar10;
    *(ushort **)(puVar8 + 0x1c8) = puVar7;
    puVar8[0x1ca] = uVar10;
    uVar6 = uVar6 + 2;
    puVar8 = puVar8 + 0x1ca;
  }
  else {
    uVar10 = (ushort)(uVar5 & 0xff);
    if ((uVar6 & 1) == 0) {
      uVar6 = uVar6 + 1;
      uVar9 = uVar10;
    }
    else {
      uVar1 = uVar9 | (ushort)((uVar5 & 0xff) << 8);
      puVar7 = (ushort *)(*(int *)(iVar2 + 0x28) + (uVar6 - 1));
      *puVar7 = uVar1;
      *(ushort **)(puVar8 + 0x1c8) = puVar7;
      puVar8 = puVar8 + 0x1ca;
      *puVar8 = uVar1;
      uVar6 = uVar6 + 1;
    }
  }
  *(ushort *)(iVar2 + 0x38) = uVar9;
  *(ushort *)(iVar2 + 0x3a) = uVar10;
  bVar3 = *(uint *)(iVar2 + 0x30) <= uVar6;
  if (bVar3) {
    uVar6 = 0;
  }
  *(uint *)(iVar2 + 0x2c) = uVar6;
  if (bVar3) {
    if ((*(ushort *)(iVar2 + 0x24) & 0x10) == 0x10) {
      FUN_0238c214(0x51,0);
    }
    else {
      iVar4 = FUN_0238c0c8(2,0x42,0,puVar8);
      if (iVar4 == 0) {
        FUN_0238c214(0x51,4);
      }
      else {
        *(undefined4 *)(iVar2 + 0x20) = 4;
        *DAT_0238ddf8 = *DAT_0238ddf8 & 0xff7f;
      }
    }
  }
  return;
}



void FUN_0238ddfc(void)

{
  FUN_0238dc94();
  *(uint *)PTR_NDS7_IRQ_IF_Check_Bits_0238de30 = *(uint *)PTR_NDS7_IRQ_IF_Check_Bits_0238de30 | 0x40
  ;
  *(undefined4 *)PTR_REG_IF_0238de34 = 0x40;
  return;
}



void FUN_0238de38(int param_1)

{
  ushort *puVar1;
  int iVar2;
  bool bVar3;
  ushort uVar4;
  int iVar6;
  uint uVar5;
  
  iVar2 = DAT_0238e084;
  iVar6 = *(int *)(param_1 + 4);
  if (iVar6 == 0x40) {
    FUN_02385e18();
    bVar3 = FUN_0238c1f8();
    if (bVar3) {
      FUN_0238c1e0(2);
      FUN_02385e2c();
      if ((*(uint *)(param_1 + 8) & 1) == 1) {
        uVar5 = FUN_0238e44c();
        puVar1 = DAT_0238e07c;
        uVar4 = (ushort)uVar5;
        if ((*(uint *)(param_1 + 8) & 2) != 0) {
          uVar4 = uVar4 ^ 0x8000;
        }
        *DAT_0238e07c = uVar4;
        *DAT_0238e080 = puVar1;
      }
      else {
        uVar5 = FUN_0238e514();
        puVar1 = DAT_0238e07c;
        uVar4 = (ushort)uVar5;
        if ((*(uint *)(param_1 + 8) & 2) != 0) {
          uVar4 = uVar4 ^ 0x80;
        }
        *DAT_0238e07c = uVar4;
        *DAT_0238e080 = puVar1;
      }
      FUN_0238c214(*(uint *)(param_1 + 4) & 0xffff,0);
      FUN_0238c19c(2);
    }
    else {
      FUN_02385e2c();
      FUN_0238c214(*(uint *)(param_1 + 4) & 0xffff,4);
    }
  }
  else if (iVar6 == 0x41) {
    if (*(int *)(DAT_0238e084 + 0x20) == 1) {
      *(undefined2 *)(DAT_0238e084 + 0x3a) = 0;
      *(undefined2 *)(iVar2 + 0x38) = 0;
      FUN_02385e18();
      FUN_02383918(0x40);
      FUN_0238e818(0x40,DAT_0238e088);
      FUN_0238e7ac();
      iVar2 = DAT_0238e084;
      *DAT_0238e08c = *(undefined2 *)(DAT_0238e084 + 0x34);
      *DAT_0238e090 = *(ushort *)(iVar2 + 0x36) | 0xc0;
      FUN_02385e2c();
      FUN_0238c214(*(uint *)(param_1 + 4) & 0xffff,0);
      *(undefined4 *)(DAT_0238e084 + 0x20) = 2;
    }
    else {
      FUN_0238c214(0x41,3);
    }
  }
  else if (iVar6 == 0x42) {
    if (*(int *)(DAT_0238e084 + 0x20) - 3U < 2) {
      *DAT_0238e090 = *DAT_0238e090 & 0xff7f;
      FUN_02385e18();
      FUN_0238e818(0x40,0);
      FUN_0238e760();
      FUN_02385e2c();
      if (*(int *)(DAT_0238e084 + 0x20) == 3) {
        FUN_0238c214(0x42,0);
      }
      else {
        FUN_0238c214(0x51,0);
      }
      *(undefined4 *)(DAT_0238e084 + 0x20) = 0;
    }
    else if (*(int *)(DAT_0238e084 + 0x20) == 3) {
      FUN_0238c214(0x42,3);
    }
    else {
      FUN_0238c214(0x51,3);
    }
  }
  return;
}



undefined4 FUN_0238e094(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_0238e134;
  if (param_1 < 0x10000) {
    *(undefined2 *)(DAT_0238e134 + 0x36) = 0;
    *(short *)(iVar1 + 0x34) = -(short)param_1;
    return 1;
  }
  if (param_1 < 0x400000) {
    *(undefined2 *)(DAT_0238e134 + 0x36) = 1;
    *(short *)(iVar1 + 0x34) = -(short)(param_1 >> 6);
    return 1;
  }
  if (param_1 < 0x1000000) {
    *(undefined2 *)(DAT_0238e134 + 0x36) = 2;
    *(short *)(iVar1 + 0x34) = -(short)(param_1 >> 8);
    return 1;
  }
  if (param_1 < 0x4000000) {
    *(undefined2 *)(DAT_0238e134 + 0x36) = 3;
    *(short *)(iVar1 + 0x34) = -(short)(param_1 >> 10);
    return 1;
  }
  return 0;
}



void FUN_0238e138(uint param_1)

{
  uint uVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint uVar4;
  int iVar5;
  
  puVar2 = DAT_0238e3f8;
  if ((param_1 & 0x2000000) != 0) {
    iVar5 = 0;
    do {
      puVar2[iVar5] = 0;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x10);
  }
  puVar2 = DAT_0238e3f8;
  DAT_0238e3f8[(param_1 & 0xf0000) >> 0x10] = (ushort)param_1;
  if ((param_1 & 0x1000000) != 0) {
    uVar4 = (uint)*puVar2;
    uVar1 = ((uVar4 & 0xff00) << 8) >> 0x10;
    switch(uVar1) {
    case 0x40:
      iVar5 = FUN_0238c0c8(2,uVar1,1,uVar4 & 0xff);
      if (iVar5 == 0) {
        FUN_0238c214(uVar1,4);
      }
      *DAT_0238e3fc = 0;
      *DAT_0238e400 = 0;
      break;
    case 0x41:
      if (*(int *)(puVar2 + 0x10) == 0) {
        puVar2[0x12] = *puVar2 & 0xff;
        uVar4 = CONCAT22(puVar2[1],puVar2[2]);
        if ((uVar4 < 0x2000000) || (0x23fffff < uVar4)) {
          FUN_0238c214(uVar1,2);
        }
        else {
          *(uint *)(puVar2 + 0x14) = uVar4;
          if (uVar4 + CONCAT22(puVar2[3],puVar2[4]) < 0x2400001) {
            *(int *)(puVar2 + 0x18) = CONCAT22(puVar2[3],puVar2[4]);
            iVar5 = FUN_0238e094(CONCAT22(puVar2[5],puVar2[6]));
            puVar2 = DAT_0238e3f8;
            if (iVar5 == 0) {
              FUN_0238c214(uVar1,2);
            }
            else {
              *(undefined4 *)(DAT_0238e3f8 + 0x16) = 0;
              puVar2[0x13] = puVar2[0x12] & 7;
              iVar5 = FUN_0238c0c8(2,uVar1,0,uVar4);
              if (iVar5 == 0) {
                FUN_0238c214(uVar1,4);
              }
              else {
                *DAT_0238e3fc = 0;
                *DAT_0238e400 = 0;
                *(undefined4 *)(DAT_0238e3f8 + 0x10) = 1;
              }
            }
          }
          else {
            FUN_0238c214(uVar1,2);
          }
        }
      }
      else {
        FUN_0238c214(uVar1,3);
      }
      break;
    case 0x42:
      if (*(int *)(puVar2 + 0x10) == 2) {
        iVar5 = FUN_0238c0c8(2,uVar1,0,uVar4);
        if (iVar5 == 0) {
          FUN_0238c214(uVar1,4);
        }
        else {
          *(undefined4 *)(DAT_0238e3f8 + 0x10) = 3;
          *DAT_0238e404 = *DAT_0238e404 & 0xff7f;
        }
      }
      else {
        FUN_0238c214(uVar1,3);
      }
      break;
    case 0x43:
      if (*(int *)(puVar2 + 0x10) == 2) {
        iVar5 = FUN_0238e094(CONCAT22(puVar2[1],puVar2[2]));
        if (iVar5 == 0) {
          FUN_0238c214(uVar1,2);
        }
        else {
          FUN_02385e18();
          puVar3 = DAT_0238e404;
          *DAT_0238e404 = *DAT_0238e404 & 0xff7f;
          puVar2 = DAT_0238e3f8;
          *DAT_0238e408 = DAT_0238e3f8[0x1a];
          *puVar3 = puVar2[0x1b] | 0xc0;
          FUN_02385e2c();
          FUN_0238c214(uVar1,0);
        }
      }
      else {
        FUN_0238c214(uVar1,3);
      }
      break;
    default:
      FUN_0238c214(uVar1,1);
    }
  }
  return;
}



void FUN_0238e40c(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_0238e444;
  iVar2 = 0;
  *(undefined4 *)(DAT_0238e444 + 0x20) = 0;
  do {
    *(undefined2 *)(iVar1 + iVar2 * 2) = 0;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  *DAT_0238e448 = *DAT_0238e448 & 0xff7f;
  return;
}



uint FUN_0238e44c(void)

{
  ushort uVar1;
  undefined *puVar2;
  
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238e500 & 0x80) != 0);
  *(short *)PTR_SPI_bus_Control_0238e500 = (short)DAT_0238e504;
  *(undefined2 *)PTR_SPI_bus_Data_0238e508 = 0xe4;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238e500 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Data_0238e508 = 0;
  puVar2 = PTR_SPI_bus_Data_0238e508;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238e500 & 0x80) != 0);
  uVar1 = *(ushort *)PTR_SPI_bus_Data_0238e508;
  *(short *)PTR_SPI_bus_Control_0238e500 = (short)DAT_0238e50c;
  *(undefined2 *)puVar2 = 0;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238e500 & 0x80) != 0);
  return ((((uint)uVar1 << 0x18 | (*(ushort *)PTR_SPI_bus_Data_0238e508 & 0xff) << 0x10) >> 0x10 &
          DAT_0238e510) << 0x11) >> 0x10;
}



uint FUN_0238e514(void)

{
  ushort uVar1;
  undefined *puVar2;
  
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238e5c8 & 0x80) != 0);
  *(short *)PTR_SPI_bus_Control_0238e5c8 = (short)DAT_0238e5cc;
  *(undefined2 *)PTR_SPI_bus_Data_0238e5d0 = 0xec;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238e5c8 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Data_0238e5d0 = 0;
  puVar2 = PTR_SPI_bus_Data_0238e5d0;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238e5c8 & 0x80) != 0);
  uVar1 = *(ushort *)PTR_SPI_bus_Data_0238e5d0;
  *(short *)PTR_SPI_bus_Control_0238e5c8 = (short)DAT_0238e5d4;
  *(undefined2 *)puVar2 = 0;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_0238e5c8 & 0x80) != 0);
  return ((((uint)uVar1 << 0x18 | (*(ushort *)PTR_SPI_bus_Data_0238e5d0 & 0xff) << 0x10) >> 0x10 &
          DAT_0238e5d8) << 9) >> 0x10;
}



void FUN_0238e760(void)

{
  if (*(int *)PTR_NDS7_IRQ_Handler_0238e7a0 == DAT_0238e7a4) {
    FUN_02385e18();
    *(undefined4 *)PTR_NDS7_IRQ_Handler_0238e7a0 = *(undefined4 *)(DAT_0238e7a8 + 0xc);
    FUN_02385e2c();
  }
  return;
}



void FUN_0238e7ac(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = DAT_0238e810;
  iVar2 = *(int *)PTR_NDS7_IRQ_Handler_0238e808;
  if (iVar2 != DAT_0238e80c) {
    *DAT_0238e810 = 0;
    puVar1[1] = DAT_0238e814;
    puVar1[2] = 0x40;
    puVar1[3] = iVar2;
    FUN_02385e18();
    *(int *)PTR_NDS7_IRQ_Handler_0238e808 = DAT_0238e80c;
    FUN_02385e2c();
  }
  return;
}



void FUN_0238e818(uint param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_0238e83c;
  iVar2 = 0;
  do {
    if ((param_1 & 1) != 0) {
      *(undefined4 *)(iVar1 + iVar2 * 4) = param_2;
    }
    param_1 = param_1 >> 1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x19);
  return;
}



void FUN_0238e840(int param_1)

{
  int iVar1;
  
  while (iVar1 = FUN_02386464(0xd,param_1,0), iVar1 != 0) {
    thunk_EXT_FUN_03803d98(1);
  }
  return;
}



void FUN_0238e888(undefined4 param_1,int *param_2)

{
  if (*param_2 == 0) {
    thunk_EXT_FUN_037fba3c();
  }
  FUN_02385e2c();
  return;
}



void FUN_0238e8b0(undefined4 param_1,uint *param_2)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  longlong lVar4;
  
  iVar1 = DAT_0238e91c;
  while( true ) {
    lVar4 = FUN_02385e18();
    param_2[1] = (uint)lVar4;
    uVar2 = FUN_02383b7c(iVar1);
    *param_2 = uVar2 & 0x80;
    if ((*param_2 != 0) || (iVar3 = FUN_02383b8c(param_1), iVar3 == 0)) break;
    FUN_02385e2c();
    thunk_EXT_FUN_03803d98(1);
  }
  return;
}



void FUN_0238e920(int *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR_REG_EXMEMSTAT_0238e950;
  *(ushort *)PTR_REG_EXMEMSTAT_0238e950 =
       *(ushort *)PTR_REG_EXMEMSTAT_0238e950 & 0xfff3 | (ushort)(*param_1 << 2);
  *(ushort *)puVar1 = *(ushort *)puVar1 & 0xffef | (ushort)(param_1[1] << 4);
  return;
}



void FUN_0238e954(int *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR_REG_EXMEMSTAT_0238e998;
  *param_1 = (int)(*(ushort *)PTR_REG_EXMEMSTAT_0238e998 & 0xc) >> 2;
  param_1[1] = (int)(*(ushort *)puVar1 & 0x10) >> 4;
  *(ushort *)puVar1 = *(ushort *)puVar1 & 0xfff3 | 0xc;
  *(ushort *)puVar1 = *(ushort *)puVar1 & 0xffef;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_0238e99c(void)

{
  undefined4 uVar1;
  uint auStack_18 [2];
  int aiStack_10 [2];
  
  uVar1 = 1;
  if (*DAT_0238ea98 == DAT_0238ea9c) {
    uVar1 = 0;
  }
  else if ((int)((uint)*(byte *)((int)DAT_0238ea98 + 5) << 0x1e) < 0) {
    uVar1 = 0;
  }
  else {
    FUN_0238e8b0((uint)*(ushort *)(DAT_0238eaa0 + 2),auStack_18);
    FUN_0238e954(aiStack_10);
    if ((((DAT_080000b2 == -0x6a) && (*DAT_0238ea98 != _DAT_080000be)) ||
        ((DAT_080000b2 != -0x6a && (*DAT_0238ea98 != *DAT_0238eaa4)))) ||
       ((*(int *)(DAT_0238ea98 + 4) != _DAT_080000ac &&
        ((int)((uint)*(byte *)((int)DAT_0238ea98 + 5) << 0x1f) < 0)))) {
      *(byte *)((int)DAT_0238ea98 + 5) = *(byte *)((int)DAT_0238ea98 + 5) | 2;
      uVar1 = 0;
    }
    FUN_0238e920(aiStack_10);
    FUN_0238e888((uint)*(ushort *)(DAT_0238eaa0 + 2),(int *)auStack_18);
  }
  return uVar1;
}



uint FUN_0238eaa8(void)

{
  uint uVar1;
  
  if (*DAT_0238eaf8 == DAT_0238eafc) {
    uVar1 = 0;
  }
  else {
    if (-1 < (int)((uint)*(byte *)((int)DAT_0238eaf8 + 5) << 0x1e)) {
      FUN_0238e99c();
    }
    uVar1 = ((uint)*(byte *)((int)DAT_0238eaf8 + 5) << 0x1e) >> 0x1f;
  }
  return uVar1;
}



void FUN_0238eb00(void)

{
  int iVar1;
  undefined4 local_8 [2];
  
  local_8[0] = 0;
  thunk_EXT_FUN_03803dd8(local_8,DAT_0238eb38,DAT_0238eb3c);
  iVar1 = FUN_02383aa4();
  *(short *)(DAT_0238eb38 + 2) = (short)iVar1;
  return;
}



void thunk_EXT_FUN_03803dd8(void)

{
                    // WARNING: Could not recover jumptable at 0x0238eb44. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_0238eb48)();
  return;
}



void FUN_0238eb4c(void)

{
  FUN_02386830();
  FUN_0238dc08();
  FUN_02385ea8();
  return;
}



void FUN_0238eb6c(void)

{
  uint uVar1;
  int iVar2;
  
  if (*DAT_0238ec6c == 0xffffffff) {
    *DAT_0238ec6c = *DAT_0238ec70 + 10;
  }
  else if (((*DAT_0238ec74 == 0) && (*DAT_0238ec78 == 0)) && (*DAT_0238ec6c <= *DAT_0238ec70)) {
    *DAT_0238ec6c = *DAT_0238ec70 + 10;
    uVar1 = FUN_0238eaa8();
    *DAT_0238ec78 = uVar1;
    iVar2 = FUN_0238e99c();
    if (iVar2 == 0) {
      if (*DAT_0238ec7c != 0) {
        *DAT_0238ec74 = 1;
        return;
      }
      *DAT_0238ec78 = 1;
    }
    *DAT_0238ec7c = 0;
    if (*DAT_0238ec78 != 0) {
      while (iVar2 = FUN_02386464(0xd,0x11,0), iVar2 != 0) {
        FUN_02383e70(100);
      }
    }
  }
  return;
}



undefined4 FUN_0238ec80(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar3 = 1;
  uVar1 = FUN_02383aa4();
  uVar1 = uVar1 & 0xffff;
  FUN_02383bcc(uVar1);
  iVar2 = 0;
  do {
    if (0x4d < iVar2) {
LAB_0238ed0c:
      thunk_EXT_FUN_037fba3c(uVar1);
      FUN_02383b3c(uVar1);
      return uVar3;
    }
    uVar4 = (DAT_0238ed28 ^ 0x84) & 0xffff;
    if ((iVar2 != 0x4c) && (uVar4 = DAT_0238ed28, iVar2 == 0x4d)) {
      uVar4 = (DAT_0238ed28 ^ 3) & 0xffff;
    }
    if ((uVar4 & *(ushort *)(param_1 + iVar2 * 2)) != (uint)*(ushort *)(&DAT_08000004 + iVar2 * 2))
    {
      uVar3 = 0;
      goto LAB_0238ed0c;
    }
    iVar2 = iVar2 + 1;
  } while( true );
}



void FUN_0238ed2c(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x3f) == 2) {
    FUN_0238eb4c();
  }
  else {
    FUN_02385ea8();
  }
  return;
}



void FUN_0238ed58(undefined4 param_1,uint param_2)

{
  uint *puVar1;
  
  puVar1 = DAT_0238ed8c;
  if ((param_2 & 0x3f) == 1) {
    *DAT_0238ed8c = param_2;
    puVar1[4] = 1;
  }
  else {
    FUN_02385ea8();
  }
  return;
}



void FUN_0238ed90(void)

{
  undefined2 uVar1;
  uint *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if ((*DAT_0238ee60 == 0) && (*DAT_0238ee60 = 1, (*(ushort *)PTR_REG_POSTFLG_0238ee64 & 1) != 0)) {
    uVar3 = FUN_02383950(0x40000);
    uVar1 = *(undefined2 *)PTR_REG_IME_0238ee68;
    *(undefined2 *)PTR_REG_IME_0238ee68 = 1;
    puVar2 = DAT_0238ee6c;
    while (puVar2[4] != 1) {
      thunk_EXT_FUN_03803d98(0x100);
    }
    uVar4 = FUN_0238ec80(((*puVar2 & DAT_0238ee70) >> 6) * 0x20 + 0x2000004);
    *(byte *)(DAT_0238ee74 + 5) = *(byte *)(DAT_0238ee74 + 5) & 0xfe | (byte)uVar4 & 1;
    FUN_0238e840(1);
    *(undefined2 *)PTR_REG_IME_0238ee68 = uVar1;
    FUN_02383950(uVar3);
  }
  return;
}



void FUN_0238ee78(void)

{
  if (*DAT_0238eec8 == 0) {
    *DAT_0238eec8 = 1;
    FUN_0238eb00();
    thunk_EXT_FUN_037fe42c();
    FUN_02386530(0xd,DAT_0238eecc);
    FUN_0238ed90();
    FUN_02386530(0xd,DAT_0238eed0);
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x0238f07c)
// WARNING: Removing unreachable block (ram,0x0238f080)
// WARNING: Removing unreachable block (ram,0x0238f084)
// WARNING: Removing unreachable block (ram,0x0238f088)
// WARNING: Removing unreachable block (ram,0x0238f0b4)
// WARNING: Removing unreachable block (ram,0x0238ef0c)

uint FUN_0238eed4(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  
  if ((param_4 | param_3) == 0) {
    return param_1;
  }
  if ((param_2 | param_4) == 0) {
    uVar2 = FUN_0238f2f0(param_1,param_3);
    return uVar2;
  }
  if ((param_2 | param_1) == 0) {
    return 0;
  }
  iVar6 = 1;
  iVar7 = 0;
  if (-1 < (int)param_4) {
    do {
      iVar6 = iVar7;
      bVar8 = CARRY4(param_3,param_3);
      param_3 = param_3 * 2;
      param_4 = param_4 * 2 + (uint)bVar8;
      iVar7 = iVar6 + 1;
    } while (-1 < (int)param_4);
    iVar6 = iVar6 + 2;
  }
  if (-1 < (int)param_2) {
    do {
      if (iVar6 == 1) break;
      iVar6 = iVar6 + -1;
      bVar8 = CARRY4(param_1,param_1);
      param_1 = param_1 * 2;
      param_2 = param_2 * 2 + (uint)bVar8;
    } while (-1 < (int)param_2);
  }
  iVar7 = 0;
  uVar2 = 0;
  while( true ) {
    uVar3 = param_1 - param_3;
    uVar4 = param_2 - (param_4 + (param_3 > param_1));
    for (iVar7 = iVar7 - (uint)(param_2 <= param_4 &&
                               (uint)(param_3 <= param_1) <= param_2 - param_4); uVar2 = uVar2 * 2,
        iVar7 < 0;
        iVar7 = iVar7 * 2 + (uint)(bVar8 || CARRY4(uVar1,(uint)bVar9)) +
                (uint)(CARRY4(uVar5,param_4) || CARRY4(uVar5 + param_4,(uint)bVar10))) {
      iVar6 = iVar6 + -1;
      if (iVar6 == 0) {
        return uVar2;
      }
      bVar9 = CARRY4(uVar3,uVar3);
      uVar1 = uVar4 * 2;
      bVar8 = CARRY4(uVar4,uVar4);
      uVar5 = uVar4 * 2 + (uint)bVar9;
      bVar10 = CARRY4(uVar3 * 2,param_3);
      uVar3 = uVar3 * 2 + param_3;
      uVar4 = uVar5 + param_4 + (uint)bVar10;
    }
    uVar2 = uVar2 | 1;
    iVar6 = iVar6 + -1;
    if (iVar6 == 0) break;
    param_1 = uVar3 * 2;
    param_2 = uVar4 * 2 + (uint)CARRY4(uVar3,uVar3);
    iVar7 = iVar7 * 2 + (uint)(CARRY4(uVar4,uVar4) || CARRY4(uVar4 * 2,(uint)CARRY4(uVar3,uVar3)));
  }
  return uVar2;
}



// WARNING: Removing unreachable block (ram,0x0238f07c)
// WARNING: Removing unreachable block (ram,0x0238f080)
// WARNING: Removing unreachable block (ram,0x0238f084)
// WARNING: Removing unreachable block (ram,0x0238f088)
// WARNING: Removing unreachable block (ram,0x0238ef70)

ulonglong FUN_0238ef2c(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  bool bVar10;
  bool bVar11;
  bool bVar12;
  undefined8 uVar13;
  
  iVar1 = ((int)(param_2 ^ param_4) >> 1) * 2;
  if ((param_4 | param_3) == 0) {
    return CONCAT44(param_2,param_1);
  }
  if ((param_2 - ((int)param_1 >> 0x1f) | param_4 - ((int)param_3 >> 0x1f)) == 0) {
    uVar13 = FUN_0238f0dc(param_1,param_3);
    return (ulonglong)(int)uVar13;
  }
  if ((int)param_2 < 0) {
    bVar10 = param_1 != 0;
    param_1 = -param_1;
    param_2 = -(param_2 + bVar10);
  }
  if ((int)param_4 < 0) {
    bVar10 = param_3 != 0;
    param_3 = -param_3;
    param_4 = -(param_4 + bVar10);
  }
  if ((param_2 | param_1) == 0) {
    uVar9 = 0;
    iVar8 = 0;
    if (-1 < iVar1) {
      return 0;
    }
  }
  else {
    iVar6 = 1;
    iVar8 = 0;
    if (-1 < (int)param_4) {
      do {
        iVar6 = iVar8;
        bVar10 = CARRY4(param_3,param_3);
        param_3 = param_3 * 2;
        param_4 = param_4 * 2 + (uint)bVar10;
        iVar8 = iVar6 + 1;
      } while (-1 < (int)param_4);
      iVar6 = iVar6 + 2;
    }
    for (; (-1 < (int)param_2 && (iVar6 != 1)); iVar6 = iVar6 + -1) {
      bVar10 = CARRY4(param_1,param_1);
      param_1 = param_1 * 2;
      param_2 = param_2 * 2 + (uint)bVar10;
    }
    iVar7 = 0;
    uVar9 = 0;
    iVar8 = 0;
    while( true ) {
      uVar3 = param_1 - param_3;
      uVar4 = param_2 - (param_4 + (param_3 > param_1));
      iVar8 = iVar8 * 2 + (uint)CARRY4(uVar9,uVar9);
      for (iVar7 = iVar7 - (uint)(param_2 <= param_4 &&
                                 (uint)(param_3 <= param_1) <= param_2 - param_4); uVar9 = uVar9 * 2
          , iVar7 < 0;
          iVar7 = iVar7 * 2 + (uint)(bVar10 || CARRY4(uVar2,(uint)bVar11)) +
                  (uint)(CARRY4(uVar5,param_4) || CARRY4(uVar5 + param_4,(uint)bVar12))) {
        iVar6 = iVar6 + -1;
        if (iVar6 == 0) goto LAB_0238f06c;
        bVar11 = CARRY4(uVar3,uVar3);
        uVar2 = uVar4 * 2;
        bVar10 = CARRY4(uVar4,uVar4);
        uVar5 = uVar4 * 2 + (uint)bVar11;
        bVar12 = CARRY4(uVar3 * 2,param_3);
        uVar3 = uVar3 * 2 + param_3;
        uVar4 = uVar5 + param_4 + (uint)bVar12;
        iVar8 = iVar8 * 2 + (uint)CARRY4(uVar9,uVar9);
      }
      uVar9 = uVar9 | 1;
      iVar6 = iVar6 + -1;
      if (iVar6 == 0) break;
      param_1 = uVar3 * 2;
      param_2 = uVar4 * 2 + (uint)CARRY4(uVar3,uVar3);
      iVar7 = iVar7 * 2 + (uint)(CARRY4(uVar4,uVar4) || CARRY4(uVar4 * 2,(uint)CARRY4(uVar3,uVar3)))
      ;
    }
LAB_0238f06c:
    if (-1 < iVar1) {
      return CONCAT44(iVar8,uVar9);
    }
  }
  return CONCAT44(-(iVar8 + (uint)(uVar9 != 0)),-uVar9);
}



undefined8 FUN_0238f0dc(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  undefined8 uVar5;
  
  uVar2 = (param_1 ^ param_2) & 0x80000000;
  bVar3 = (int)param_1 < 0;
  if (bVar3) {
    param_1 = -param_1;
    uVar2 = uVar2 + 1;
  }
  bVar4 = param_2 != 0;
  if ((int)param_2 < 0) {
    param_2 = -param_2;
  }
  uVar1 = param_1;
  if (bVar4) {
    if (param_2 <= param_1) {
      uVar1 = 0x1c;
      uVar2 = param_1 >> 4;
      if ((int)param_2 <= (int)(param_1 >> 0x10)) {
        uVar1 = 0xc;
        uVar2 = param_1 >> 0x14;
      }
      if ((int)param_2 <= (int)(uVar2 >> 4)) {
        uVar1 = uVar1 - 8;
        uVar2 = uVar2 >> 8;
      }
      if ((int)param_2 <= (int)uVar2) {
        uVar1 = uVar1 - 4;
        uVar2 = uVar2 >> 4;
      }
                    // WARNING: Could not recover jumptable at 0x0238f148. Too many branches
                    // WARNING: Treating indirect jump as call
      uVar5 = (*(code *)(uVar1 * 0xc + 0x238f150))
                        ((param_1 << (uVar1 & 0xff)) * 2,-param_2,uVar1 * 3,uVar2);
      return uVar5;
    }
    uVar1 = 0;
    param_2 = param_1;
  }
  if ((uVar2 & 0x80000000) != 0) {
    uVar1 = -uVar1;
  }
  if (bVar3) {
    param_2 = -param_2;
  }
  return CONCAT44(param_2,uVar1);
}



void FUN_0238f2e8(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    return;
  }
  if (param_2 <= param_1) {
    uVar1 = 0x1c;
    uVar2 = param_1 >> 4;
    if ((int)param_2 <= (int)(param_1 >> 0x10)) {
      uVar1 = 0xc;
      uVar2 = param_1 >> 0x14;
    }
    if ((int)param_2 <= (int)(uVar2 >> 4)) {
      uVar1 = uVar1 - 8;
      uVar2 = uVar2 >> 8;
    }
    if ((int)param_2 <= (int)uVar2) {
      uVar1 = uVar1 - 4;
      uVar2 = uVar2 >> 4;
    }
                    // WARNING: Could not recover jumptable at 0x0238f33c. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)(uVar1 * 0xc + 0x238f344))((param_1 << (uVar1 & 0xff)) * 2,-param_2,uVar1 * 3,uVar2);
    return;
  }
  return;
}



void FUN_0238f2f0(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  if (param_2 <= param_1) {
    uVar1 = 0x1c;
    uVar2 = param_1 >> 4;
    if ((int)param_2 <= (int)(param_1 >> 0x10)) {
      uVar1 = 0xc;
      uVar2 = param_1 >> 0x14;
    }
    if ((int)param_2 <= (int)(uVar2 >> 4)) {
      uVar1 = uVar1 - 8;
      uVar2 = uVar2 >> 8;
    }
    if ((int)param_2 <= (int)uVar2) {
      uVar1 = uVar1 - 4;
      uVar2 = uVar2 >> 4;
    }
                    // WARNING: Could not recover jumptable at 0x0238f33c. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)(uVar1 * 0xc + 0x238f344))((param_1 << (uVar1 & 0xff)) * 2,-param_2,uVar1 * 3,uVar2);
    return;
  }
  return;
}



void FUN_0238f778(void)

{
  *(undefined2 *)PTR_REG_IME_0238f78c = 0;
                    // WARNING: Could not recover jumptable at 0x0238f788. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_0238f790)();
  return;
}



uint FUN_0238f884(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined8 uVar6;
  
  uVar1 = param_1 & DAT_0238f9ac & 0xffff;
  if (uVar1 == 0) {
    uVar1 = 0;
  }
  else {
    for (uVar4 = 0; ((int)uVar4 < 0x10 && ((uVar1 & 1 << (uVar4 & 0xff)) == 0)); uVar4 = uVar4 + 1)
    {
    }
    for (uVar5 = 0xf; (uVar5 != 0 && ((uVar1 & 1 << (uVar5 & 0xff)) == 0)); uVar5 = uVar5 - 1) {
    }
    if ((int)(uVar5 - uVar4) < 5) {
      uVar1 = 1 << (uVar4 & 0xff) & 0xffff;
    }
    else {
      uVar6 = FUN_0238f0dc(uVar5 + uVar4,2);
      uVar3 = (uint)uVar6;
      for (uVar2 = 0; (int)uVar2 < (int)(uVar5 - uVar4); uVar2 = uVar2 + 1) {
        uVar6 = FUN_0238f0dc(uVar2,2);
        uVar3 = uVar2 * ((int)((ulonglong)uVar6 >> 0x20) * 2 + -1) + uVar3;
        if ((uVar1 & 1 << (uVar3 & 0xff)) != 0) break;
      }
      if (((int)(uVar5 - uVar3) < 5) || ((int)(uVar3 - uVar4) < 5)) {
        uVar1 = (1 << (uVar4 & 0xff) | 1 << (uVar5 & 0xff)) & 0xffff;
      }
      else {
        uVar1 = (1 << (uVar5 & 0xff) | 1 << (uVar3 & 0xff) | 1 << (uVar4 & 0xff)) & 0xffff;
      }
    }
  }
  return uVar1;
}



int FUN_0238fbf8(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  func_0x033ad8a0();
  iVar2 = *(int *)(DAT_0238fc64 + 0x518);
  if (iVar2 != 0) {
    for (iVar4 = 0; iVar4 < 0x20; iVar4 = iVar4 + 1) {
      iVar1 = iVar4 * 0x10;
      if ((*(uint *)(iVar2 + iVar4 * 0x10 + 0xf8) & 0x8000) != 0) {
        iVar2 = iVar2 + 0xf8;
        iVar3 = iVar2 + iVar1;
        *(uint *)(iVar2 + iVar1) = *(uint *)(iVar2 + iVar1) & 0xffff7fff;
        break;
      }
    }
  }
  func_0x033ad8b4();
  return iVar3;
}



void FUN_0238fc68(undefined2 param_1,undefined2 param_2,undefined2 param_3)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = param_1;
  puVar1[1] = 1;
  puVar1[2] = param_2;
  puVar1[3] = param_3;
  func_0x033b74e0();
  return;
}



void FUN_0238fc9c(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = func_0x033ad8a0();
  func_0x033ab880();
  func_0x033ab968(DAT_0238fcf0,*(undefined4 *)(DAT_0238fcf4 + 0x530));
  iVar2 = FUN_02397a28();
  func_0x033ab968(iVar2,*(undefined4 *)(DAT_0238fcf4 + 0x534));
  func_0x033ab968(DAT_0238fcf8,*(undefined4 *)(DAT_0238fcf4 + 0x538));
  func_0x033ab848();
  func_0x033ad8b4(uVar1);
  return;
}



void FUN_0238fcfc(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = func_0x033ad8a0();
  func_0x033ab880();
  func_0x033ab968(DAT_0238fd50,*(undefined4 *)(DAT_0238fd54 + 0x544));
  iVar2 = FUN_02397a28();
  func_0x033ab968(iVar2,*(undefined4 *)(DAT_0238fd54 + 0x540));
  func_0x033ab968(DAT_0238fd58,*(undefined4 *)(DAT_0238fd54 + 0x53c));
  func_0x033ab848();
  func_0x033ad8b4(uVar1);
  return;
}



undefined4 FUN_0238fd5c(uint param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 8) {
    return 0;
  }
  if (0xd < param_1) {
    if (param_1 < 0x14) {
      uVar1 = 2;
    }
    else {
      uVar1 = 3;
    }
    return uVar1;
  }
  return 1;
}



void FUN_0238fd84(void)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = 0;
  iVar2 = 0;
  do {
    uVar1 = uVar1 + *(byte *)(DAT_0238fdb8 + iVar2 + 0x151c);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
                    // WARNING: Could not recover jumptable at 0x0238fdb4. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_0238fdbc)(uVar1 >> 4);
  return;
}



void FUN_0238fdc0(undefined param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_0238fdf0;
  iVar2 = 0;
  do {
    *(undefined *)(iVar1 + iVar2 + 0x151c) = param_1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  *(undefined4 *)(DAT_0238fdf4 + 0x52c) = 0;
  return;
}



void FUN_0238fdf8(undefined param_1)

{
  int iVar1;
  
  iVar1 = DAT_0238fe1c;
  *(undefined *)(DAT_0238fe20 + *(int *)(DAT_0238fe1c + 0x52c)) = param_1;
  *(uint *)(iVar1 + 0x52c) = *(int *)(iVar1 + 0x52c) + 1U & 0xf;
  return;
}



uint FUN_0238fe24(uint param_1)

{
  uint uVar1;
  
  uVar1 = (int)param_1 >> 2;
  if ((param_1 & 2) == 0) {
    uVar1 = uVar1 + 0x19;
  }
  return uVar1 & 0xff;
}



bool FUN_0238fe40(undefined2 param_1,undefined2 *param_2)

{
  short sVar1;
  undefined uVar2;
  int iVar3;
  undefined2 *puVar4;
  int *piVar5;
  
  iVar3 = FUN_023901d8();
  piVar5 = *(int **)(iVar3 + 0x1518);
  func_0x033adc88(*piVar5 + 0xdc,param_2 + 8,6);
  param_2[0xb] = 7;
  param_2[0xc] = *(undefined2 *)(*piVar5 + 0x1f0);
  param_2[0xf] = *(undefined2 *)(*piVar5 + 0x1e8);
  param_2[0xe] = *(undefined2 *)(*piVar5 + 0xe2);
  if (*(int *)(*piVar5 + 0x194) == 0) {
    param_2[0x10] = 0;
    param_2[0x11] = 0;
    func_0x033adb48(0,param_2 + 0x12,0x50);
    param_2[0x4f] = 0;
  }
  else {
    FUN_023901d8();
    param_2[0x10] = *(undefined2 *)(*piVar5 + 0x192);
    param_2[0x11] = *(undefined2 *)(*piVar5 + 0xc0);
    func_0x033adc88(*piVar5 + 0x198,param_2 + 0x12,0x50);
    param_2[0x4f] = 1;
  }
  param_2[0x3a] = 1;
  param_2[0x3b] = 1;
  if (*(short *)(*piVar5 + 0xe2) == 1) {
    param_2[0x3c] = 0;
  }
  else {
    param_2[0x3c] = 0x10;
  }
  param_2[0x3d] = 10;
  func_0x033adb48(0,param_2 + 0x3e,8);
  func_0x033adb48(DAT_0238ffc0 & 0xffff,param_2 + 0x42,0x18);
  param_2[0x4e] = *(undefined2 *)(*piVar5 + 0x1ea);
  puVar4 = FUN_02391e54(param_2);
  sVar1 = puVar4[2];
  if (sVar1 == 0) {
    puVar4 = (undefined2 *)0x1;
  }
  uVar2 = SUB41(puVar4,0);
  if (sVar1 != 0) {
    FUN_0238fc68(param_1,0x200,sVar1);
    uVar2 = 0;
  }
  return (bool)uVar2;
}



void FUN_0238ffc4(undefined2 *param_1,undefined4 *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  *(undefined4 *)(param_1 + 2) = param_2[2];
  param_1[4] = *(undefined2 *)(param_2 + 3);
  if (*(short *)((int)param_2 + 0x12) == 0) {
    bVar1 = 0;
  }
  else {
    bVar1 = 2;
  }
  if (*(short *)(param_2 + 5) == 0) {
    bVar3 = 0;
  }
  else {
    bVar3 = 4;
  }
  if (*(short *)((int)param_2 + 0x16) == 0) {
    bVar2 = 0;
  }
  else {
    bVar2 = 8;
  }
  *(byte *)((int)param_1 + 0xb) = bVar2 | bVar3 | *(short *)((int)param_2 + 0xe) != 0 | bVar1;
  *(char *)(param_1 + 5) = (char)*(undefined2 *)(param_2 + 1);
  *param_1 = 1;
  param_1[6] = *(undefined2 *)(param_2 + 0xd);
  param_1[7] = *(undefined2 *)((int)param_2 + 0x36);
  if (*(byte *)(param_1 + 5) != 0) {
    func_0x033adc88(*param_2,param_1 + 8,*(byte *)(param_1 + 5) + 1 & 0xfffffffe);
  }
  return;
}



undefined4 FUN_02390074(char *param_1)

{
  int iVar1;
  
  iVar1 = **(int **)(DAT_023900ec + 0x518);
  if ((((*param_1 == *(char *)(iVar1 + 0xdc)) && (param_1[1] == *(char *)(iVar1 + 0xdd))) &&
      (param_1[2] == *(char *)(iVar1 + 0xde))) &&
     (((param_1[3] == *(char *)(iVar1 + 0xdf) && (param_1[4] == *(char *)(iVar1 + 0xe0))) &&
      (param_1[5] == *(char *)(iVar1 + 0xe1))))) {
    return 1;
  }
  return 0;
}



void FUN_023900f0(undefined4 param_1,undefined2 *param_2,int param_3)

{
  int iVar1;
  undefined2 *puVar2;
  
  if (((param_3 == 0) && (iVar1 = func_0x033ac16c(DAT_02390150,param_2,0), iVar1 == 0)) &&
     (*(int *)(DAT_02390154 + 0x518) != 0)) {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = *param_2;
    puVar2[1] = 8;
    puVar2[2] = 0;
    puVar2[3] = 0;
    func_0x033b74e0();
  }
  return;
}



int FUN_02390158(undefined4 param_1)

{
  undefined2 *puVar1;
  int local_8 [2];
  
  func_0x033ac16c(DAT_023901d0,param_1,1);
  func_0x033ac0cc(DAT_023901d4,local_8,1);
  if (*(short *)(local_8[0] + (uint)*(ushort *)(local_8[0] + 0xe) * 2 + 0x14) == 0xe) {
    puVar1 = (undefined2 *)func_0x033b7438();
    *puVar1 = 0x80;
    puVar1[1] = 0x13;
    puVar1[2] = 0x17;
    func_0x033b74e0();
    func_0x033ae2b8();
    func_0x033ad930();
  }
  return local_8[0];
}



undefined4 FUN_023901d8(void)

{
  return DAT_023901e0;
}



undefined2 FUN_023901e4(int *param_1,undefined4 *param_2)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  
  iVar1 = DAT_0239035c;
  *(undefined4 *)(DAT_0239035c + 0x50c) = *param_2;
  *(int *)(iVar1 + 0x510) = param_1[9];
  *(int *)(iVar1 + 0x514) = param_1[10];
  *(undefined4 *)(iVar1 + 0x518) = 0;
  func_0x033ac200(DAT_02390360,DAT_02390364,2);
  func_0x033ac200(DAT_02390368,DAT_0239036c,4);
  func_0x033ac200(DAT_02390370,DAT_02390374,4);
  func_0x033ac200(DAT_02390378,DAT_0239037c,0x20);
  param_1[4] = DAT_02390360;
  param_1[5] = DAT_02390368;
  iVar1 = DAT_0239035c;
  *(undefined4 *)(DAT_0239035c + 0x530) = param_2[2];
  *(undefined4 *)(iVar1 + 0x534) = param_2[6];
  *(undefined4 *)(iVar1 + 0x538) = param_2[4];
  *(undefined4 *)(iVar1 + 0x53c) = param_2[1];
  *(undefined4 *)(iVar1 + 0x540) = param_2[5];
  *(undefined4 *)(iVar1 + 0x544) = param_2[3];
  func_0x033ac3d0(DAT_02390380);
  func_0x033abc80(DAT_02390384,DAT_02390388,0,DAT_02390380,0x400,param_2[1]);
  func_0x033abb18(DAT_02390384);
  func_0x033abc80(DAT_0239038c,DAT_02390390,0,DAT_02390394,0x1000,param_2[3]);
  func_0x033abb18(DAT_0239038c);
  iVar1 = DAT_02390360;
  iVar3 = 0;
  do {
    *(undefined *)(iVar1 + iVar3 + 0x151c) = 0;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x10);
  *(undefined4 *)(DAT_0239035c + 0x52c) = 0;
  func_0x033addc0();
  func_0x033adfb8(10,DAT_02390398);
  param_1[6] = 2;
  param_1[3] = param_2[5];
  uVar2 = FUN_02397a3c(param_1);
  return uVar2;
}



void FUN_0239039c(void)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x80;
  puVar1[1] = 0;
  puVar1[2] = 0x13;
  func_0x033b74e0();
  return;
}



void FUN_023903d0(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined4 uVar4;
  uint uVar5;
  short *psVar6;
  int iVar7;
  short **ppsVar8;
  char local_28;
  char local_27;
  char local_26;
  char local_25;
  char local_24;
  char local_23;
  
  iVar2 = FUN_023901d8();
  ppsVar8 = *(short ***)(iVar2 + 0x1518);
  psVar6 = *ppsVar8;
  if ((*psVar6 == 7) || (*psVar6 == 9)) {
    func_0x033adc88(param_1 + 0x10,&local_28,6);
    uVar5 = 0;
    for (iVar2 = 0; iVar2 < 0xf; iVar2 = iVar2 + 1) {
      iVar7 = iVar2 * 6;
      if ((((local_28 == *(char *)(psVar6 + iVar2 * 3 + 0x92)) &&
           (local_27 == *(char *)((int)psVar6 + iVar7 + 0x125))) &&
          (local_26 == *(char *)(psVar6 + iVar2 * 3 + 0x93))) &&
         (((local_25 == *(char *)((int)psVar6 + iVar7 + 0x127) &&
           (local_24 == *(char *)(psVar6 + iVar2 * 3 + 0x94))) &&
          (local_23 == *(char *)((int)psVar6 + iVar7 + 0x129))))) {
        uVar5 = iVar2 + 1U & 0xffff;
        func_0x033ad8a0();
        uVar1 = ~(ushort)(1 << (iVar2 + 1U & 0xff));
        psVar6[0xbf] = psVar6[0xbf] & uVar1;
        psVar6[0x43] = psVar6[0x43] & uVar1;
        *(undefined4 *)(psVar6 + uVar5 * 4 + 0x398) = 0;
        *(undefined4 *)(psVar6 + uVar5 * 4 + 0x39a) = 0;
        func_0x033ad8b4();
        *(undefined *)(psVar6 + iVar2 * 3 + 0x92) = 0;
        *(undefined *)((int)psVar6 + iVar7 + 0x125) = 0;
        *(undefined *)(psVar6 + iVar2 * 3 + 0x93) = 0;
        *(undefined *)((int)psVar6 + iVar7 + 0x127) = 0;
        *(undefined *)(psVar6 + iVar2 * 3 + 0x94) = 0;
        *(undefined *)((int)psVar6 + iVar7 + 0x129) = 0;
        break;
      }
    }
    if (uVar5 != 0) {
      puVar3 = (undefined2 *)func_0x033b7438();
      *puVar3 = 8;
      puVar3[1] = 0;
      puVar3[4] = 9;
      puVar3[9] = *(undefined2 *)(param_1 + 0x16);
      puVar3[8] = (short)uVar5;
      func_0x033adc88(param_1 + 0x10,puVar3 + 5,6);
      func_0x033b74e0(puVar3);
      if (*(int *)(psVar6 + 6) == 1) {
        FUN_02396268((ushort)(1 << (uVar5 & 0xff)));
      }
    }
  }
  else {
    uVar4 = func_0x033ad8a0();
    iVar2 = *(int *)(psVar6 + 6);
    if (iVar2 == 1) {
      *(undefined4 *)(psVar6 + 6) = 0;
      func_0x033ad4f0(ppsVar8 + 0x34);
      FUN_0238fcfc();
    }
    psVar6[0xbf] = 0;
    psVar6[0x43] = 0;
    *(undefined4 *)(psVar6 + 10) = 0;
    *(undefined4 *)(psVar6 + 8) = 0;
    *(undefined4 *)(psVar6 + 0xe) = 0;
    psVar6[0x5f] = 0;
    *psVar6 = 3;
    func_0x033ad8b4(uVar4);
    puVar3 = (undefined2 *)func_0x033b7438();
    *puVar3 = 0xc;
    puVar3[1] = 0;
    puVar3[4] = 9;
    puVar3[6] = *(undefined2 *)(param_1 + 0x16);
    puVar3[5] = psVar6[0xc2];
    psVar6[199] = 0;
    psVar6[200] = 0;
    func_0x033b74e0();
    if (iVar2 == 1) {
      FUN_02396268(1);
    }
  }
  return;
}



void FUN_02390628(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined2 *puVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  undefined8 uVar8;
  
  iVar2 = FUN_023901d8();
  iVar2 = **(int **)(iVar2 + 0x1518);
  uVar1 = *(ushort *)(param_1 + 0x16);
  uVar7 = (uint)uVar1;
  if ((uVar7 != 0) && (uVar7 < 0x10)) {
    if (*(short *)(iVar2 + 0xf2) == 0) {
      puVar3 = (undefined4 *)FUN_0238fbf8();
      if (puVar3 == (undefined4 *)0x0) {
        iVar2 = 0;
      }
      else {
        *puVar3 = 0x22;
        func_0x033adc88(param_1 + 0x10,puVar3 + 1,6);
        iVar2 = FUN_023901d8();
        iVar2 = func_0x033ac16c(iVar2 + 100,puVar3,0);
      }
      if (iVar2 == 0) {
        puVar4 = (undefined2 *)func_0x033b7438();
        *puVar4 = 0x80;
        puVar4[1] = 8;
        puVar4[2] = 0x16;
        puVar4[3] = 0x22;
        func_0x033b74e0();
      }
    }
    else {
      func_0x033adc88(param_1 + 0x10,(uVar7 - 1) * 6 + iVar2 + 0x124);
      uVar5 = func_0x033ad8a0();
      *(ushort *)(iVar2 + 0x17e) = *(ushort *)(iVar2 + 0x17e) | (ushort)(1 << (uVar7 & 0xff));
      *(ushort *)(iVar2 + 0x86) = *(ushort *)(iVar2 + 0x86) & ~(ushort)(1 << (uVar7 & 0xff));
      uVar8 = func_0x033acba8();
      iVar6 = iVar2 + uVar7 * 8;
      *(uint *)(iVar6 + 0x730) = (uint)uVar8 | 1;
      *(int *)(iVar6 + 0x734) = (int)((ulonglong)uVar8 >> 0x20);
      func_0x033ad8b4(uVar5);
      func_0x033adb48(1,iVar2 + 500 + uVar7 * 0x10,0x10);
      puVar4 = (undefined2 *)func_0x033b7438();
      *puVar4 = 8;
      puVar4[1] = 0;
      puVar4[4] = 7;
      func_0x033adc88(param_1 + 0x10,puVar4 + 5,6);
      puVar4[8] = uVar1;
      func_0x033adb60(param_1 + 0x22,puVar4 + 10,0x18);
      func_0x033b74e0(puVar4);
    }
  }
  return;
}



void FUN_023907ac(void)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x80;
  puVar1[1] = 0;
  puVar1[2] = 0x12;
  func_0x033b74e0();
  return;
}



void FUN_023907e0(void)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x80;
  puVar1[1] = 0;
  puVar1[2] = 0x11;
  func_0x033b74e0();
  return;
}



void FUN_02390814(void)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined2 *puVar4;
  short **ppsVar5;
  
  iVar2 = FUN_023901d8();
  ppsVar5 = *(short ***)(iVar2 + 0x1518);
  if ((*ppsVar5)[0x6d] != 1) {
    puVar3 = (undefined4 *)FUN_0238fbf8();
    if (puVar3 == (undefined4 *)0x0) {
      iVar2 = 0;
    }
    else {
      *puVar3 = 0x25;
      puVar3[2] = DAT_023908e4;
      sVar1 = **ppsVar5;
      if ((sVar1 == 9) || (sVar1 == 7)) {
        puVar3[1] = DAT_023908e8;
      }
      else if ((sVar1 == 10) || (sVar1 == 8)) {
        puVar3[1] = 1;
      }
      iVar2 = FUN_023901d8();
      iVar2 = func_0x033ac16c(iVar2 + 100,puVar3,0);
    }
    if (iVar2 == 0) {
      puVar4 = (undefined2 *)func_0x033b7438();
      *puVar4 = 0x80;
      puVar4[1] = 8;
      puVar4[2] = 0x16;
      puVar4[3] = 0x25;
      func_0x033b74e0();
    }
  }
  return;
}



void FUN_023908ec(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined2 *puVar5;
  
  iVar2 = FUN_023901d8();
  iVar2 = **(int **)(iVar2 + 0x1518);
  if (*(int *)(iVar2 + 0x10) != 0) {
    FUN_023901d8();
    uVar3 = FUN_0238fe24((uint)*(byte *)(param_1 + 0x1f));
    FUN_0238fdf8((char)uVar3);
    uVar1 = FUN_0238fd84();
    *(undefined2 *)(iVar2 + 0xb8) = uVar1;
    iVar4 = FUN_02390074((char *)(param_1 + 0x2e));
    if (iVar4 != 1) {
      *(ushort *)(iVar2 + 0xaa) = *(ushort *)(iVar2 + 0xaa) ^ 1;
      iVar2 = *(int *)(iVar2 + (uint)*(ushort *)(iVar2 + 0xaa) * 4 + 0xac);
      func_0x033adc88(param_1 + 0x10,iVar2,*(ushort *)(param_1 + 0x16) + 0x2d & 0xfffffffe);
      func_0x033adc88(param_1 + 0x28,iVar2 + 0x18,6);
      func_0x033adc88(param_1 + 0x2e,iVar2 + 0x1e,6);
      puVar5 = (undefined2 *)func_0x033b7438();
      *puVar5 = 0x11;
      puVar5[1] = 0;
      puVar5[2] = 0xf;
      *(int *)(puVar5 + 4) = iVar2;
      func_0x033b74e0();
    }
  }
  return;
}



void FUN_023909c4(int param_1)

{
  ushort uVar1;
  short sVar2;
  bool bVar3;
  int iVar4;
  undefined4 uVar5;
  undefined2 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  
  iVar4 = FUN_023901d8();
  iVar9 = **(int **)(iVar4 + 0x1518);
  iVar4 = 0;
  if (*(int *)(iVar9 + 0xc) != 0) {
    if (*(short *)(param_1 + 0xe) == 0) {
      iVar8 = 1;
      uVar1 = *DAT_02390ca0;
      if ((uint)*DAT_02390c9c < (uint)*DAT_02390c9c) {
        uVar1 = *DAT_02390ca0;
      }
      if ((int)((((uVar1 & 0xf) << 0xc | (int)(uint)*DAT_02390c9c >> 4) -
                (uint)*(ushort *)(iVar9 + 0x56)) * 0x10000) >> 0x10 < 1) {
        return;
      }
    }
    else {
      iVar8 = 0;
    }
    uVar5 = func_0x033ad8a0();
    if (*(short *)(iVar9 + 0x84) == 0) {
      func_0x033ad8b4();
    }
    else {
      *(undefined2 *)(iVar9 + 0x84) = 0;
      sVar2 = *(short *)(iVar9 + 0x90);
      func_0x033ace94(iVar9 + 0x58);
      func_0x033ad8b4(uVar5);
      bVar3 = true;
      if ((*(short *)(iVar9 + 0x8c) != 0) &&
         ((iVar8 != 0 ||
          (((uint)*(ushort *)(param_1 + 0x3e) & 1 << (*(ushort *)(iVar9 + 0x184) & 0xff)) == 0)))) {
        bVar3 = false;
      }
      if ((sVar2 != 0) && ((iVar8 != 0 || (bVar3)))) {
        *(undefined2 *)(iVar9 + 0xba) = 4;
      }
      if (*(short *)(iVar9 + 0x8c) != 0) {
        *(undefined2 *)(iVar9 + 0x8c) = 0;
      }
      if (*(short *)(iVar9 + 0x8e) != 0) {
        *(undefined2 *)(iVar9 + 0x8e) = 0;
        iVar4 = FUN_0239644c(iVar8,(ushort)bVar3);
      }
      puVar6 = (undefined2 *)func_0x033b7438();
      *puVar6 = 0xe;
      if (sVar2 == 0) {
        puVar6[1] = 0xd;
      }
      else if (iVar8 == 0) {
        if (((uint)*(ushort *)(param_1 + 0x3e) & 1 << (*(ushort *)(iVar9 + 0x184) & 0xff)) == 0) {
          puVar6[1] = 0;
        }
        else {
          puVar6[1] = 0xf;
        }
      }
      else {
        puVar6[1] = 9;
      }
      puVar6[2] = 0xd;
      *(undefined4 *)(puVar6 + 4) = 0;
      if (iVar8 == 0) {
        puVar6[6] = *(undefined2 *)(param_1 + 0x1c);
        puVar6[7] = *(undefined2 *)(param_1 + 0x1e);
        func_0x033adc88(param_1 + 0x28,puVar6 + 8,6);
        func_0x033adc88(param_1 + 0x2e,puVar6 + 0xb,6);
        puVar6[0xe] = *(undefined2 *)(param_1 + 0x3a);
        puVar6[0xf] = *(undefined2 *)(param_1 + 0x3c);
        puVar6[0x10] = *(undefined2 *)(param_1 + 0x3e);
      }
      func_0x033b74e0(puVar6);
      if (sVar2 != 0) {
        if ((iVar4 == 1) || (*(short *)(iVar9 + 0x30) == 0)) {
          puVar7 = (undefined4 *)FUN_0238fbf8();
          iVar4 = FUN_023901d8();
          iVar8 = 0;
          *(undefined2 *)(iVar9 + 0x30) = 0;
          *(undefined2 *)(iVar9 + 0x32) = 0;
          *(undefined2 *)(iVar9 + 0x88) = 0;
          if (puVar7 != (undefined4 *)0x0) {
            *puVar7 = 0x29;
            iVar8 = func_0x033ac16c(iVar4 + 100,puVar7);
          }
          if ((iVar8 == 0) && (*(int *)(iVar4 + 0x1518) != 0)) {
            puVar6 = (undefined2 *)func_0x033b7438();
            *puVar6 = 0x80;
            puVar6[1] = 8;
            puVar6[2] = 0x16;
            puVar6[3] = 0x29;
            func_0x033b74e0();
          }
        }
        else {
          *(undefined2 *)(iVar9 + 0x30) = 0;
          *(undefined2 *)(iVar9 + 0x32) = 1;
          *(undefined2 *)(iVar9 + 0x88) = 0;
        }
      }
    }
  }
  return;
}



void FUN_02390ca4(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined2 *puVar4;
  
  iVar1 = FUN_023901d8();
  iVar2 = func_0x033ac97c(*(undefined4 *)(iVar1 + 0x1510),*(undefined4 *)(iVar1 + 0x1514),0x40);
  *(short *)(iVar2 + 0xc) = (short)DAT_02390d38;
  *(undefined2 *)(iVar2 + 0xe) = 0;
  iVar3 = func_0x033ac16c(iVar1 + 0x1c,iVar2);
  if (iVar3 == 0) {
    FUN_0239169c(iVar2);
    if (*(int *)(iVar1 + 0x1518) != 0) {
      puVar4 = (undefined2 *)func_0x033b7438();
      *puVar4 = 0x80;
      puVar4[1] = 8;
      puVar4[2] = 0x16;
      puVar4[3] = 0x80;
      func_0x033b74e0();
    }
  }
  return;
}



void FUN_02390d3c(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined2 *puVar8;
  int iVar9;
  bool bVar10;
  bool bVar11;
  undefined8 uVar12;
  
  iVar3 = FUN_023901d8();
  iVar3 = **(int **)(iVar3 + 0x1518);
  uVar4 = FUN_0238fe24((uint)*(byte *)(param_1 + 0x1f));
  if (uVar4 < *(ushort *)(iVar3 + 0xba)) {
    *(short *)(iVar3 + 0xba) = (short)uVar4;
  }
  if (*(int *)(iVar3 + 0xc) != 0) {
    if (*(short *)(iVar3 + 0x32) == 1) {
      *(undefined2 *)(iVar3 + 0x32) = 0;
    }
    sVar1 = *(short *)(iVar3 + 0x8e);
    *(ushort *)(iVar3 + 0x44) = *(ushort *)(iVar3 + 0x44) ^ 1;
    iVar9 = *(int *)(iVar3 + (uint)*(ushort *)(iVar3 + 0x44) * 4 + 0x48);
    uVar4 = *(ushort *)(param_1 + 0x16) + 0x30;
    if (*(ushort *)(iVar3 + 0x46) < uVar4) {
      uVar4 = (uint)*(ushort *)(iVar3 + 0x46);
    }
    func_0x033adc88(param_1 + 0x10,iVar9,uVar4);
    uVar5 = func_0x033ad8a0();
    bVar10 = *(short *)(iVar3 + 0x84) == 1;
    if (bVar10) {
      func_0x033ace94(iVar3 + 0x58);
    }
    uVar4 = (uint)bVar10;
    *(undefined2 *)(iVar3 + 0x84) = 1;
    *(undefined2 *)(iVar3 + 0x56) = *(undefined2 *)(iVar9 + 10);
    bVar10 = ((uint)*(ushort *)(iVar9 + 0x2e) & 1 << (*(ushort *)(iVar3 + 0x184) & 0xff)) != 0;
    *(ushort *)(iVar3 + 0x90) = (ushort)bVar10;
    uVar6 = func_0x033b6b64((((uint)*(ushort *)(iVar9 + 10) - (uint)*(ushort *)(iVar9 + 0xc) &
                             0xffff) + 0x80) * 0x10 * DAT_02391014,0x40);
    iVar7 = func_0x033b6b64(uVar6,0x400);
    func_0x033acfa0(iVar3 + 0x58,iVar7,iVar7 >> 0x1f,DAT_02391018,0);
    uVar2 = *(ushort *)(param_1 + 0x18);
    bVar11 = (uVar2 & 0x2800) == 0x2800;
    if (bVar11) {
      *(undefined2 *)(iVar3 + 0x8a) = 0;
    }
    *(ushort *)(iVar3 + 0x8e) = (ushort)bVar11;
    *(ushort *)(iVar3 + 0x8c) = (ushort)((uVar2 & 0x6000) == 0x6000);
    func_0x033ad8b4(uVar5);
    if (uVar4 != 0) {
      if (sVar1 == 1) {
        FUN_0239644c(uVar4,0);
      }
      puVar8 = (undefined2 *)func_0x033b7438();
      *puVar8 = 0xe;
      puVar8[1] = 9;
      puVar8[2] = 0xd;
      *(undefined4 *)(puVar8 + 4) = 0;
      func_0x033b74e0();
    }
    func_0x033adc88(param_1 + 0x28,iVar9 + 0x18,6);
    func_0x033adc88(param_1 + 0x2e,iVar9 + 0x1e,6);
    if (*(ushort *)(iVar9 + 6) < 2) {
      *(undefined2 *)(iVar9 + 6) = 0;
      *(undefined2 *)(iVar3 + 0x30) = 0;
      puVar8 = (undefined2 *)func_0x033b7438();
      *puVar8 = 0xe;
      if (bVar10) {
        puVar8[1] = 0xe;
      }
      else {
        puVar8[1] = 0xd;
      }
      puVar8[2] = 0xc;
      *(int *)(puVar8 + 4) = iVar9;
      func_0x033b74e0();
      func_0x033b7494();
    }
    else {
      *(ushort *)(iVar9 + 6) = *(ushort *)(iVar9 + 6) - 2;
      *(ushort *)(iVar3 + 0x30) = (ushort)((*(ushort *)(iVar9 + 0x30) & 0x8000) != 0);
      puVar8 = (undefined2 *)func_0x033b7438();
      *puVar8 = 0xe;
      if (bVar10) {
        puVar8[1] = 0;
      }
      else {
        puVar8[1] = 0xd;
      }
      puVar8[2] = 0xc;
      *(int *)(puVar8 + 4) = iVar9;
      func_0x033b74e0();
      if (*(ushort *)(iVar9 + 6) != 0) {
        FUN_02395ff4(0,(uint)*(ushort *)(iVar9 + 0x30),(ushort *)(iVar9 + 0x32),
                     (uint)*(ushort *)(iVar9 + 6),iVar9);
        func_0x033b7494();
      }
    }
    if (*(int *)(iVar3 + 0x7b4) != 0 || *(int *)(iVar3 + 0x7b0) != 0) {
      uVar12 = func_0x033acba8();
      *(uint *)(iVar3 + 0x730) = (uint)uVar12 | 1;
      *(int *)(iVar3 + 0x734) = (int)((ulonglong)uVar12 >> 0x20);
    }
  }
  return;
}



void FUN_0239101c(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  iVar1 = FUN_023901d8();
  uVar3 = (uint)*(ushort *)(**(int **)(iVar1 + 0x1518) + 0xba);
  if (param_2 == 0) {
    if (*(short *)(param_1 + 0x14) == 0) {
      return;
    }
    for (iVar4 = 0; iVar4 < (int)(uint)*(ushort *)(param_1 + 0x14); iVar4 = iVar4 + 1) {
      uVar2 = FUN_0238fe24((uint)*(byte *)((uint)*(ushort *)(param_1 + 0x16) * iVar4 + param_1 +
                                          0x1d));
      if (uVar2 < uVar3) {
        uVar3 = uVar2;
      }
    }
  }
  else if (4 < uVar3) {
    uVar3 = 4;
  }
  *(short *)(**(int **)(iVar1 + 0x1518) + 0xba) = (short)uVar3;
  return;
}



void FUN_023910ac(int param_1)

{
  short sVar1;
  bool bVar2;
  ushort uVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined2 *puVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  ushort *puVar14;
  ushort *puVar15;
  bool bVar16;
  undefined8 uVar17;
  int local_38;
  
  iVar4 = FUN_023901d8();
  iVar4 = **(int **)(iVar4 + 0x1518);
  bVar2 = false;
  if (*(int *)(iVar4 + 0xc) != 0) {
    if ((*(short *)(param_1 + 0x12) == 0) &&
       ((*(int *)(iVar4 + 0x38) != 1 || (*(short *)(param_1 + 0x10) == 0)))) {
      if (*(int *)(iVar4 + 0x38) != 0) {
        *(undefined4 *)(iVar4 + 0x38) = 0;
      }
      puVar15 = *(ushort **)(iVar4 + (uint)*(ushort *)(iVar4 + 0x44) * 4 + 0x48);
      uVar11 = (uint)*(ushort *)(param_1 + 0x16) * (uint)*(ushort *)(param_1 + 0x14) + 10;
      if (*(ushort *)(iVar4 + 0x46) < uVar11) {
        uVar11 = (uint)*(ushort *)(iVar4 + 0x46);
      }
      func_0x033adc88(param_1 + 0x10,puVar15,uVar11);
      FUN_0239101c(param_1,(uint)*puVar15);
      uVar17 = func_0x033acba8();
      iVar6 = (int)((ulonglong)uVar17 >> 0x20);
      uVar11 = (uint)uVar17 | 1;
      puVar14 = puVar15 + 5;
      local_38 = 0;
      for (uVar3 = 0; uVar3 < puVar15[2]; uVar3 = uVar3 + 1) {
        uVar12 = (uint)puVar14[2];
        if ((uVar12 != 0) && (uVar12 < 0x10)) {
          uVar9 = (uint)*puVar14;
          if ((uVar9 < 2) || (uVar9 == DAT_023914ac)) {
            if (uVar9 == 0) {
              iVar10 = iVar4 + uVar12 * 8;
              uVar12 = *(uint *)(iVar10 + 0x730);
              iVar10 = *(int *)(iVar10 + 0x734);
              uVar13 = *(uint *)(iVar4 + 0x7b0);
              uVar9 = *(uint *)(iVar4 + 0x7b4);
              if ((uVar9 != 0 || uVar13 != 0) && (iVar10 != 0 || uVar12 != 0)) {
                uVar8 = iVar6 - (iVar10 + (uint)(uVar11 < uVar12));
                bVar16 = uVar9 <= uVar8;
                if (uVar8 == uVar9) {
                  bVar16 = uVar13 <= uVar11 - uVar12;
                }
                if (bVar16 && (uVar8 != uVar9 || uVar11 - uVar12 != uVar13)) {
                  puVar5 = (undefined4 *)FUN_0238fbf8();
                  iVar10 = iVar4 + (uint)puVar14[2] * 8;
                  *(undefined4 *)(iVar10 + 0x730) = 0;
                  *(undefined4 *)(iVar10 + 0x734) = 0;
                  iVar10 = local_38;
                  if (puVar5 != (undefined4 *)0x0) {
                    *puVar5 = 0x25;
                    puVar5[1] = 1 << (puVar14[2] & 0xff);
                    puVar5[2] = DAT_023914b0;
                    iVar10 = FUN_023901d8();
                    iVar10 = func_0x033ac16c(iVar10 + 100,puVar5,0);
                  }
                  if (iVar10 == 0) {
                    puVar7 = (undefined2 *)func_0x033b7438();
                    *puVar7 = 0x80;
                    puVar7[1] = 8;
                    puVar7[2] = 0x16;
                    puVar7[3] = 0x25;
                    func_0x033b74e0();
                  }
                }
              }
            }
          }
          else {
            *puVar14 = *puVar14 - 2;
            *(ushort *)(iVar4 + 0x86) =
                 *(ushort *)(iVar4 + 0x86) | (ushort)(1 << (puVar14[2] & 0xff));
            iVar10 = iVar4 + (uint)puVar14[2] * 8;
            *(uint *)(iVar10 + 0x730) = uVar11;
            *(int *)(iVar10 + 0x734) = iVar6;
            if (*puVar14 != 0) {
              FUN_02395ff4((uint)puVar14[2],(uint)puVar14[4],puVar14 + 5,(uint)*puVar14,puVar15);
            }
          }
        }
        puVar14 = (ushort *)((int)puVar14 + (uint)puVar15[3]);
      }
      FUN_0239644c(0,*puVar15);
      if (((*puVar15 != 0) && (*(short *)(iVar4 + 0x96) == 0)) && (*(short *)(iVar4 + 0x34) != 0)) {
        bVar2 = true;
      }
      puVar7 = (undefined2 *)func_0x033b7438();
      *puVar7 = 0xe;
      puVar7[1] = 0;
      puVar7[2] = 0xb;
      *(ushort **)(puVar7 + 4) = puVar15;
      func_0x033b74e0();
      func_0x033b7494();
      *(ushort *)(iVar4 + 0x44) = *(ushort *)(iVar4 + 0x44) ^ 1;
      func_0x033ad8a0();
      if (!bVar2) {
        *(short *)(iVar4 + 0x36) = *(short *)(iVar4 + 0x36) + -1;
      }
      sVar1 = *(short *)(iVar4 + 0x36);
      func_0x033ad8b4();
      if (sVar1 != 0) {
        uVar11 = DAT_023914ac;
        if (bVar2) {
          uVar11 = (uint)*(ushort *)(param_1 + 0x10);
        }
        puVar5 = (undefined4 *)FUN_0238fbf8();
        iVar4 = FUN_023901d8();
        if (puVar5 == (undefined4 *)0x0) {
          iVar6 = 0;
        }
        else {
          *puVar5 = 0x28;
          puVar5[1] = uVar11;
          iVar6 = func_0x033ac16c(iVar4 + 100,puVar5,0);
        }
        if ((iVar6 == 0) && (*(int *)(iVar4 + 0x1518) != 0)) {
          puVar7 = (undefined2 *)func_0x033b7438();
          *puVar7 = 0x80;
          puVar7[1] = 8;
          puVar7[2] = 0x16;
          puVar7[3] = 0x28;
          func_0x033b74e0();
        }
      }
    }
    else {
      puVar5 = (undefined4 *)FUN_0238fbf8();
      if (puVar5 == (undefined4 *)0x0) {
        iVar6 = 0;
      }
      else {
        *puVar5 = 0x2a;
        puVar5[1] = (uint)*(ushort *)(iVar4 + 0x3c);
        iVar6 = FUN_023901d8();
        iVar6 = func_0x033ac16c(iVar6 + 100,puVar5,0);
      }
      if (iVar6 == 0) {
        puVar7 = (undefined2 *)func_0x033b7438();
        *puVar7 = 0x80;
        puVar7[1] = 8;
        puVar7[2] = 0x16;
        puVar7[3] = 0x2a;
        func_0x033b74e0();
      }
      else {
        *(undefined4 *)(iVar4 + 0x38) = 1;
      }
    }
  }
  return;
}



void FUN_023914b4(void)

{
  int iVar1;
  undefined2 *puVar2;
  
  iVar1 = FUN_023901d8();
  if (*(short *)(**(int **)(iVar1 + 0x1518) + 0xbe) != 0) {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 0xc;
    puVar2[1] = 0;
    puVar2[4] = 8;
    func_0x033b74e0();
  }
  return;
}



void FUN_02391504(int param_1)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined2 *puVar4;
  short *psVar5;
  short **ppsVar6;
  
  iVar2 = FUN_023901d8();
  ppsVar6 = *(short ***)(iVar2 + 0x1518);
  psVar5 = *ppsVar6;
  sVar1 = *psVar5;
  if ((sVar1 == 8) || (sVar1 == 10)) {
    if (psVar5[0x5b] == *(short *)(param_1 + 0x44)) {
      iVar2 = FUN_023901d8();
      if (*(short *)(**(int **)(iVar2 + 0x1518) + 0xbe) != 0) {
        puVar4 = (undefined2 *)func_0x033b7438();
        *puVar4 = 0x80;
        puVar4[1] = 0;
        puVar4[2] = 0x10;
        puVar4[3] = *(undefined2 *)(param_1 + 0x44);
        puVar4[4] = **ppsVar6;
        puVar4[5] = *(undefined2 *)(param_1 + 0x16);
        if ((ushort)puVar4[5] < 0x81) {
          func_0x033adb60(param_1 + 0x3c,puVar4 + 6,(ushort)puVar4[5] + 1 & 0xfffffffe);
        }
        func_0x033b74e0(puVar4);
      }
    }
    else {
      puVar3 = (undefined4 *)FUN_0238fbf8();
      if (puVar3 == (undefined4 *)0x0) {
        iVar2 = 0;
      }
      else {
        *puVar3 = 0x25;
        puVar3[1] = 1;
        puVar3[2] = DAT_02391644;
        iVar2 = FUN_023901d8();
        iVar2 = func_0x033ac16c(iVar2 + 100,puVar3,0);
      }
      if (iVar2 == 0) {
        puVar4 = (undefined2 *)func_0x033b7438();
        *puVar4 = 0x80;
        puVar4[1] = 8;
        puVar4[2] = 0x16;
        puVar4[3] = 0x25;
        func_0x033b74e0();
      }
    }
  }
  return;
}



void FUN_02391648(void)

{
  int iVar1;
  undefined2 *puVar2;
  
  iVar1 = FUN_023901d8();
  if (*(short *)(**(int **)(iVar1 + 0x1518) + 0xbe) != 0) {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 8;
    puVar2[1] = 0;
    puVar2[4] = 2;
    func_0x033b74e0();
  }
  return;
}



void FUN_02391698(void)

{
  return;
}



void FUN_0239169c(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_023901d8();
  uVar2 = func_0x033ad8a0();
  func_0x033ac908(*(undefined4 *)(iVar1 + 0x1510),*(undefined4 *)(iVar1 + 0x1514),param_1);
  func_0x033ad8b4(uVar2);
  return;
}



void FUN_023916d8(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_023901d8();
  if (*(int *)(iVar1 + 0x1518) == 0) {
    return;
  }
  iVar1 = FUN_023901d8();
  if (***(short ***)(iVar1 + 0x1518) == 1) {
    return;
  }
  uVar2 = (uint)*(ushort *)(param_1 + 0xc);
  if (DAT_02391854 < (int)uVar2) {
    if (DAT_02391858 < (int)uVar2) {
      if (uVar2 == DAT_0239185c) {
        FUN_02390814();
        goto LAB_02391844;
      }
    }
    else {
      if (DAT_02391858 <= (int)uVar2) {
        FUN_023909c4(param_1);
        goto LAB_02391844;
      }
      if (uVar2 == 0x184) {
        FUN_023910ac(param_1);
        goto LAB_02391844;
      }
    }
    goto switchD_02391734_caseD_a;
  }
  if (DAT_02391854 <= (int)uVar2) {
    FUN_02390d3c(param_1);
    goto LAB_02391844;
  }
  switch(uVar2) {
  case 0x84:
    FUN_0239039c();
    break;
  case 0x85:
    FUN_023903d0(param_1);
    break;
  case 0x86:
    FUN_02390628(param_1);
    break;
  case 0x87:
    FUN_023907ac();
    break;
  case 0x88:
    FUN_023907e0();
    break;
  case 0x89:
  case 0xbad1abe1:
switchD_02391734_caseD_a:
    FUN_02391698();
    break;
  case 0x8a:
    goto switchD_02391734_caseD_a;
  case 0x8b:
    FUN_023914b4();
    break;
  case 0x8c:
    FUN_02391648();
    break;
  case 0x8d:
    FUN_02391504(param_1);
    break;
  default:
    if (uVar2 == 0x180) {
      FUN_023908ec(param_1);
      break;
    }
    goto switchD_02391734_caseD_a;
  }
LAB_02391844:
  FUN_0239169c(param_1);
  return;
}



void FUN_02391860(void)

{
  ushort uVar1;
  int iVar2;
  int local_18;
  
  iVar2 = FUN_023901d8();
  while( true ) {
    func_0x033ac0cc(iVar2 + 0x1c,&local_18,1);
    if (local_18 == 0) break;
    uVar1 = *(ushort *)(local_18 + 0xc);
    if ((((uVar1 & 0xff00) == 0) || ((uVar1 & 0xff00) == 0x100)) && ((uVar1 & 0x80) != 0)) {
      FUN_023916d8(local_18);
    }
    else {
      func_0x033ac16c(iVar2 + 0x40,local_18,1);
    }
  }
  func_0x033abc24();
  return;
}



void FUN_023918fc(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  ushort *local_28 [2];
  
  iVar2 = FUN_023901d8();
  iVar1 = DAT_023919b0;
  while (func_0x033ac0cc(iVar2 + 100,local_28,1), local_28[0] != (ushort *)0x0) {
    uVar3 = (uint)*local_28[0];
    if ((*local_28[0] & 0x8000) != 0) {
      uVar3 = uVar3 & 0xffff7fff;
    }
    if (uVar3 < 0x2b) {
      *(undefined4 *)(**(int **)(iVar2 + 0x1518) + 4) = 1;
      *(ushort *)(**(int **)(iVar2 + 0x1518) + 2) = (ushort)uVar3;
      (**(code **)(iVar1 + uVar3 * 4))(local_28[0]);
      *(undefined4 *)(**(int **)(iVar2 + 0x1518) + 4) = 0;
    }
    *local_28[0] = (ushort)uVar3 | 0x8000;
  }
  func_0x033abc24();
  return;
}



undefined2 * FUN_023919b4(undefined2 *param_1,undefined2 param_2,undefined2 param_3)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = param_2;
  param_1[7] = 0;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = param_3;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 *
FUN_02391a04(undefined2 *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
            undefined2 param_5)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = (short)DAT_02391a74;
  param_1[7] = 4;
  param_1[8] = param_2;
  param_1[9] = param_3;
  param_1[10] = param_4;
  param_1[0xb] = param_5;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



void FUN_02391a78(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02391a84. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02391a88)(param_1,0x308,2);
  return;
}



void FUN_02391a8c(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02391a98. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02391aa0)(param_1,DAT_02391a9c,0x5c);
  return;
}



void FUN_02391aa4(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02391ab0. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02391ab8)(param_1,DAT_02391ab4,9);
  return;
}



void FUN_02391abc(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02391ac8. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02391ad0)(param_1,DAT_02391acc,1);
  return;
}



void FUN_02391ad4(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02391ae0. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02391ae4)(param_1,0x304,1);
  return;
}



void FUN_02391ae8(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02391af4. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02391afc)(param_1,DAT_02391af8,1);
  return;
}



void FUN_02391b00(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02391b0c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02391b14)(param_1,DAT_02391b10,1);
  return;
}



void FUN_02391b18(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02391b24. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02391b2c)(param_1,DAT_02391b28,1);
  return;
}



void FUN_02391b30(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02391b3c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02391b40)(param_1,0x284,2);
  return;
}



void FUN_02391b44(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02391b50. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02391b58)(param_1,DAT_02391b54,3);
  return;
}



void FUN_02391b5c(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02391b68. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02391b70)(param_1,DAT_02391b6c,4);
  return;
}



undefined2 * FUN_02391b74(undefined2 *param_1,int param_2,undefined4 param_3)

{
  ushort uVar1;
  short sVar2;
  
  FUN_023901d8();
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = (short)DAT_02391c04;
  sVar2 = func_0x033b6b64(param_2 + 1,2);
  param_1[7] = sVar2 + 1;
  param_1[8] = (short)param_2;
  func_0x033adb60(param_3,param_1 + 9,param_2);
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 * FUN_02391c08(undefined2 *param_1,undefined2 param_2)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = (short)DAT_02391c64;
  param_1[7] = 1;
  param_1[8] = param_2;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 * FUN_02391c68(undefined2 *param_1,undefined2 param_2)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = (short)DAT_02391cc4;
  param_1[7] = 1;
  param_1[8] = param_2;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 * FUN_02391cc8(undefined2 *param_1,undefined2 param_2)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = (short)DAT_02391d24;
  param_1[7] = 1;
  param_1[8] = param_2;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 *
FUN_02391d28(undefined2 *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = (short)DAT_02391d90;
  param_1[7] = 3;
  param_1[8] = param_2;
  param_1[9] = param_3;
  param_1[10] = param_4;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 * FUN_02391d94(undefined2 *param_1,undefined2 param_2)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = (short)DAT_02391df0;
  param_1[7] = 1;
  param_1[8] = param_2;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 * FUN_02391df4(undefined2 *param_1,undefined2 param_2)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = (short)DAT_02391e50;
  param_1[7] = 1;
  param_1[8] = param_2;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 * FUN_02391e54(undefined2 *param_1)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0x200;
  param_1[7] = 0x48;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 * FUN_02391eb0(undefined2 *param_1,undefined2 param_2)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0x104;
  param_1[7] = 1;
  param_1[8] = param_2;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 *
FUN_02391f0c(undefined2 *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
            undefined2 param_5,undefined2 param_6,undefined2 param_7,undefined2 param_8,
            undefined2 param_9,undefined4 param_10)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = (short)DAT_02391fa4;
  param_1[7] = 10;
  param_1[8] = param_2;
  param_1[9] = param_3;
  param_1[10] = param_4;
  param_1[0xb] = param_5;
  param_1[0xc] = param_6;
  param_1[0xd] = param_7;
  param_1[0xe] = param_8;
  param_1[0xf] = param_9;
  *(undefined4 *)(param_1 + 0x10) = param_10;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 *
FUN_02391fa8(undefined2 *param_1,undefined2 param_2,undefined2 param_3,undefined4 param_4)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = (short)DAT_02392010;
  param_1[7] = 4;
  param_1[8] = param_2;
  param_1[9] = param_3;
  *(undefined4 *)(param_1 + 10) = param_4;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 * FUN_02392014(undefined2 *param_1,int param_2)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0x100;
  param_1[7] = 0x18;
  func_0x033adb60(param_2,param_1 + 8,0x30);
  *(undefined2 *)(param_2 + 2) = 0;
  *(undefined2 *)(param_2 + 4) = 0;
  *(undefined2 *)(param_2 + 8) = 0;
  *(undefined2 *)(param_2 + 10) = 0;
  *(undefined2 *)(param_2 + 0xc) = 0;
  *(undefined2 *)(param_2 + 0x10) = 0;
  *(undefined2 *)(param_2 + 0x12) = 0;
  *(undefined2 *)(param_2 + 0x14) = 0;
  *(undefined2 *)(param_2 + 0x16) = 0;
  *(undefined2 *)(param_2 + 0x24) = 0;
  *(undefined2 *)(param_2 + 0x26) = 0;
  *(undefined2 *)(param_2 + 0x28) = 0;
  *(undefined2 *)(param_2 + 0x2a) = 0;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 2;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 *
FUN_023920cc(undefined2 *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
            undefined4 param_5)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 10;
  param_1[7] = 0xc;
  param_1[8] = 0;
  param_1[9] = param_2;
  param_1[10] = param_3;
  param_1[0xb] = param_4;
  func_0x033adb60(param_5,param_1 + 0xc,0x10);
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 0x12;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 *
FUN_02392158(undefined2 *param_1,undefined2 param_2,undefined4 param_3,undefined2 param_4,
            undefined2 param_5,undefined2 param_6,undefined2 param_7,undefined2 param_8,
            ushort param_9,undefined4 param_10)

{
  ushort uVar1;
  short sVar2;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 9;
  sVar2 = func_0x033b6b64(param_9 + 1,2);
  param_1[7] = sVar2 + 0x17;
  param_1[8] = param_2;
  func_0x033adb60(param_3,param_1 + 9,0x20);
  param_1[0x19] = param_4;
  param_1[0x1a] = param_5;
  param_1[0x1b] = param_6;
  param_1[0x1c] = param_7;
  param_1[0x1d] = param_8;
  param_1[0x1e] = param_9;
  func_0x033adb60(param_10,param_1 + 0x1f);
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 *
FUN_0239222c(undefined2 *param_1,undefined4 param_2,undefined2 param_3,undefined2 param_4)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 6;
  param_1[7] = 5;
  func_0x033adb60(param_2,param_1 + 8);
  param_1[0xb] = param_3;
  param_1[0xc] = param_4;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 3;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 * FUN_023922ac(undefined2 *param_1,undefined4 param_2,undefined2 param_3)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 5;
  param_1[7] = 4;
  func_0x033adb60(param_2,param_1 + 8,6);
  param_1[0xb] = param_3;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 4;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 *
FUN_02392330(undefined2 *param_1,undefined4 param_2,undefined2 param_3,undefined2 param_4)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 4;
  param_1[7] = 5;
  func_0x033adb60(param_2,param_1 + 8,6);
  param_1[0xb] = param_3;
  param_1[0xc] = param_4;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 6;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 * FUN_023923b4(undefined2 *param_1,undefined2 param_2,undefined4 param_3)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 3;
  param_1[7] = 0x22;
  param_1[8] = param_2;
  param_1[9] = 0;
  func_0x033adb60(param_3,param_1 + 10,0x44);
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 5;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 *
FUN_02392438(undefined2 *param_1,uint param_2,undefined4 param_3,undefined2 param_4,
            undefined4 param_5,undefined2 param_6,undefined4 param_7,undefined2 param_8)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 2;
  param_1[7] = 0x1f;
  func_0x033adb60(param_3,param_1 + 8,6);
  param_1[0xb] = param_4;
  func_0x033adb60(param_5,param_1 + 0xc,0x20);
  param_1[0x1c] = param_6;
  func_0x033adb60(param_7,param_1 + 0x1d,0x10);
  param_1[0x25] = param_8;
  param_1[0x26] = 0;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = (short)(param_2 >> 1) + -0x2c;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 *
FUN_023924f4(undefined2 *param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 1;
  param_1[7] = 3;
  param_1[8] = param_2;
  param_1[9] = param_3;
  param_1[10] = param_4;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



undefined2 * FUN_02392558(undefined2 *param_1,undefined2 param_2)

{
  ushort uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 1;
  param_1[8] = param_2;
  uVar1 = param_1[7];
  param_1[uVar1 + 8] = param_1[6];
  param_1[uVar1 + 9] = 1;
  FUN_02390158(param_1);
  return param_1 + uVar1 + 8;
}



void FUN_023925b0(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  undefined4 *puVar3;
  undefined2 local_10;
  undefined2 local_e;
  
  iVar1 = FUN_023901d8();
  *(undefined4 *)(iVar1 + 0x1518) = *(undefined4 *)(param_1 + 4);
  puVar3 = *(undefined4 **)(iVar1 + 0x1518);
  *puVar3 = *(undefined4 *)(param_1 + 8);
  puVar3[2] = *(undefined4 *)(param_1 + 0xc);
  FUN_0239731c();
  func_0x033b54a0(0xf);
  *(undefined2 *)*puVar3 = 1;
  iVar1 = FUN_02397584(&local_10,&local_e);
  if (iVar1 == 0) {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 0;
    puVar2[1] = 1;
    puVar2[2] = local_10;
    puVar2[3] = local_e;
    func_0x033b74e0();
  }
  else {
    *(undefined2 *)*puVar3 = 2;
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 0;
    puVar2[1] = 0;
    func_0x033b74e0();
  }
  return;
}



void FUN_02392664(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 1;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



// WARNING: Removing unreachable block (ram,0x023927c4)

void FUN_0239269c(void)

{
  ushort uVar1;
  short sVar2;
  bool bVar3;
  int iVar4;
  undefined4 uVar5;
  undefined2 *puVar6;
  short *psVar7;
  uint uVar8;
  short **ppsVar9;
  undefined auStack_224 [6];
  undefined auStack_21e [6];
  undefined2 auStack_218 [256];
  
  iVar4 = FUN_023901d8();
  ppsVar9 = *(short ***)(iVar4 + 0x1518);
  bVar3 = false;
  uVar5 = func_0x033ad8a0();
  if (*(int *)(*ppsVar9 + 6) == 1) {
    *(undefined4 *)(*ppsVar9 + 6) = 0;
    bVar3 = true;
    func_0x033ad4f0(ppsVar9 + 0x34);
    FUN_0238fcfc();
    psVar7 = *ppsVar9;
    if (*psVar7 == 10) {
      *psVar7 = 8;
    }
    else if (*psVar7 == 9) {
      *psVar7 = 7;
    }
  }
  (*ppsVar9)[0xbf] = 0;
  (*ppsVar9)[0x43] = 0;
  *(undefined4 *)(*ppsVar9 + 10) = 0;
  *(undefined4 *)(*ppsVar9 + 8) = 0;
  *(undefined4 *)(*ppsVar9 + 0xe) = 0;
  (*ppsVar9)[0x5f] = 0;
  func_0x033ad8b4(uVar5);
  if (bVar3) {
    FUN_02396268((ushort)DAT_02392a18);
  }
  iVar4 = FUN_02391a78(auStack_218);
  if (*(short *)(iVar4 + 4) != 0) {
    FUN_02392664(0x308,*(short *)(iVar4 + 4));
    return;
  }
  uVar1 = *(ushort *)(iVar4 + 6);
  iVar4 = FUN_02391b30(auStack_218);
  if (*(short *)(iVar4 + 4) != 0) {
    FUN_02392664(0x284,*(short *)(iVar4 + 4));
    return;
  }
  uVar8 = (uint)*(ushort *)(iVar4 + 6);
  if (uVar1 < 0x21) {
    if (0x1f < uVar1) goto LAB_023928dc;
    if (uVar1 == 0) goto LAB_02392900;
    if ((0x12 < uVar1) || (uVar1 < 0x10)) goto LAB_023929e4;
    if (uVar1 != 0x10) {
      if ((uVar1 != 0x11) && (uVar1 != 0x12)) goto LAB_023929e4;
      if (uVar8 == 0) {
        puVar6 = FUN_02391a04(auStack_218,0,0,0x14,1);
        if (puVar6[2] != 0) {
          FUN_02392664((short)DAT_02392a2c,puVar6[2]);
          return;
        }
      }
      iVar4 = FUN_02391b00(auStack_218);
      if (*(short *)(iVar4 + 4) != 0) {
        FUN_02392664((short)DAT_02392a24,*(short *)(iVar4 + 4));
        return;
      }
      **ppsVar9 = 2;
      goto LAB_023929f4;
    }
  }
  else {
    if (uVar1 < 0x31) {
      if (uVar1 != 0x30) {
LAB_023929e4:
        FUN_02392664(0x308,0);
        return;
      }
    }
    else if (uVar1 != 0x40) goto LAB_023929e4;
    if ((uVar8 + DAT_02392a1c & 0xffff) < 2) {
      func_0x033adc88((int)*ppsVar9 + DAT_02392a20,auStack_224,6);
      for (iVar4 = 0; iVar4 < 2; iVar4 = iVar4 + 1) {
        puVar6 = FUN_023922ac(auStack_218,auStack_224,3);
        sVar2 = puVar6[2];
        if (sVar2 == 0) {
          **ppsVar9 = 3;
          break;
        }
        if ((sVar2 != 7) && (sVar2 != 0xc)) break;
      }
    }
    else if (uVar8 == 1) {
      func_0x033adbf4(auStack_21e,0xff,6);
      puVar6 = FUN_023922ac(auStack_218,auStack_21e,3);
      if (puVar6[2] == 0) {
        **ppsVar9 = 3;
      }
    }
LAB_023928dc:
    puVar6 = FUN_02392558(auStack_218,1);
    if (puVar6[2] != 0) {
      FUN_02392664(0,puVar6[2]);
      return;
    }
LAB_02392900:
    iVar4 = FUN_02391b00(auStack_218);
    if (*(short *)(iVar4 + 4) != 0) {
      FUN_02392664((short)DAT_02392a24,*(short *)(iVar4 + 4));
      return;
    }
  }
  if ((*ppsVar9)[0xf5] == 0) {
    puVar6 = FUN_02391d94(auStack_218,1);
    if (puVar6[2] != 0) {
      FUN_02392664((short)DAT_02392a28,puVar6[2]);
      return;
    }
    (*ppsVar9)[0xf5] = 1;
  }
  **ppsVar9 = 2;
LAB_023929f4:
  puVar6 = (undefined2 *)func_0x033b7438();
  *puVar6 = 1;
  puVar6[1] = 0;
  func_0x033b74e0();
  return;
}



void FUN_02392a30(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 2;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_02392a6c(void)

{
  int iVar1;
  undefined2 *puVar2;
  short **ppsVar3;
  undefined auStack_208 [512];
  
  iVar1 = FUN_023901d8();
  ppsVar3 = *(short ***)(iVar1 + 0x1518);
  if (**ppsVar3 == 2) {
    iVar1 = FUN_02391b18(auStack_208);
    if (*(short *)(iVar1 + 4) == 0) {
      **ppsVar3 = 1;
      func_0x033b54a0();
      **ppsVar3 = 0;
      puVar2 = (undefined2 *)func_0x033b7438();
      *puVar2 = 2;
      puVar2[1] = 0;
      func_0x033b74e0();
    }
    else {
      FUN_02392a30((short)DAT_02392b0c,*(short *)(iVar1 + 4));
    }
  }
  else {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 2;
    puVar2[1] = 3;
    func_0x033b74e0();
  }
  return;
}



void FUN_02392b10(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 7;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_02392b4c(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  int *piVar3;
  undefined2 auStack_210 [258];
  
  iVar1 = FUN_023901d8();
  piVar3 = *(int **)(iVar1 + 0x1518);
  func_0x033adc88(*(undefined4 *)(param_1 + 4),*piVar3 + 0xe4,0x40);
  iVar1 = *piVar3;
  if ((1 << (*(ushort *)(iVar1 + 0x116) & 0xff) & (uint)*(ushort *)(iVar1 + 0x1f0)) == 0) {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 7;
    puVar2[1] = 6;
    func_0x033b74e0();
  }
  else {
    puVar2 = FUN_02391cc8(auStack_210,*(undefined2 *)(iVar1 + 0xf4));
    if (puVar2[2] == 0) {
      puVar2 = (undefined2 *)func_0x033b7438();
      *puVar2 = 7;
      puVar2[1] = 0;
      func_0x033b74e0();
    }
    else {
      FUN_02392b10((short)DAT_02392bfc,puVar2[2]);
    }
  }
  return;
}



void FUN_02392c00(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 8;
  puVar1[1] = 1;
  puVar1[4] = 0;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_02392c44(int param_1)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  short *psVar6;
  short **ppsVar7;
  undefined2 local_2b4;
  undefined2 local_2b2;
  short local_2b0;
  undefined2 local_2ae;
  undefined2 auStack_294 [256];
  undefined2 auStack_94 [66];
  
  iVar3 = FUN_023901d8();
  ppsVar7 = *(short ***)(iVar3 + 0x1518);
  psVar6 = *ppsVar7;
  if (*psVar6 == 2) {
    iVar3 = *(int *)(param_1 + 4);
    if (((uint)(ushort)psVar6[0xf9] & (1 << ((ushort)psVar6[0x8b] & 0xff)) >> 1) == 0) {
      puVar4 = (undefined2 *)func_0x033b7438();
      *puVar4 = 8;
      puVar4[1] = 6;
      puVar4[4] = 0;
      func_0x033b74e0();
    }
    else {
      psVar6[0x71] = 1;
      (*ppsVar7)[0xc2] = 0;
      func_0x033ad8a0();
      (*ppsVar7)[0xbf] = 0;
      (*ppsVar7)[0x43] = 0;
      func_0x033ad8b4();
      (*ppsVar7)[0xf5] = 1;
      bVar1 = FUN_0238fe40(8,auStack_294);
      if (bVar1) {
        iVar5 = FUN_02391ae8(auStack_294);
        if (*(short *)(iVar5 + 4) == 0) {
          bVar1 = iVar3 != 0;
          if (bVar1) {
            iVar5 = 1;
          }
          sVar2 = (short)iVar5;
          if (!bVar1) {
            sVar2 = 0;
          }
          puVar4 = FUN_023924f4(auStack_294,sVar2,0,1);
          if (puVar4[2] == 0) {
            (*ppsVar7)[0x61] = sVar2;
            psVar6 = *ppsVar7;
            func_0x033adb48(0,auStack_94,0x80);
            FUN_0238ffc4(auStack_94,(undefined4 *)(psVar6 + 0x72));
            func_0x033adb48(0,&local_2b4,0x20);
            local_2b4 = (undefined2)*(undefined4 *)(psVar6 + 0x76);
            local_2b2 = (undefined2)((uint)*(undefined4 *)(psVar6 + 0x76) >> 0x10);
            local_2b0 = psVar6[0x78];
            local_2ae = 0;
            puVar4 = FUN_02392158(auStack_294,0x20,&local_2b4,psVar6[0x7e],2,psVar6[0x8b],3,3,
                                  psVar6[0x74] + 0x10,auStack_94);
            if (puVar4[2] == 0) {
              if (psVar6[0x7c] == 0) {
                sVar2 = 0;
              }
              else {
                sVar2 = 0x2a;
              }
              (*ppsVar7)[199] = psVar6[0x8c] + 4 + sVar2;
              if (psVar6[0x7c] == 0) {
                sVar2 = 0;
              }
              else {
                sVar2 = 6;
              }
              (*ppsVar7)[200] = psVar6[0x8d] + 2 + sVar2;
              puVar4 = (undefined2 *)func_0x033b7438();
              **ppsVar7 = 7;
              *puVar4 = 8;
              puVar4[1] = 0;
              puVar4[4] = 0;
              func_0x033b74e0();
              (*ppsVar7)[0x5f] = 1;
            }
            else {
              FUN_02392c00(9,puVar4[2]);
            }
          }
          else {
            FUN_02392c00(1,puVar4[2]);
          }
        }
        else {
          FUN_02392c00((short)DAT_02392ef8,*(short *)(iVar5 + 4));
        }
      }
    }
  }
  else {
    puVar4 = (undefined2 *)func_0x033b7438();
    *puVar4 = 8;
    puVar4[1] = 3;
    puVar4[4] = 0;
    func_0x033b74e0();
  }
  return;
}



void FUN_02392efc(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 9;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_02392f38(void)

{
  uint uVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  undefined2 *puVar5;
  short *psVar6;
  uint uVar7;
  short **ppsVar8;
  undefined auStack_230 [8];
  undefined2 auStack_228 [258];
  
  iVar4 = FUN_023901d8();
  ppsVar8 = *(short ***)(iVar4 + 0x1518);
  if (**ppsVar8 == 7) {
    uVar7 = 1;
    do {
      uVar1 = 1 << (uVar7 & 0xff);
      if (((ushort)(*ppsVar8)[0xbf] & uVar1) != 0) {
        func_0x033adc88(*ppsVar8 + (uVar7 - 1) * 3 + 0x92,auStack_230,6);
        for (iVar4 = 0; iVar4 < 2; iVar4 = iVar4 + 1) {
          puVar5 = FUN_023922ac(auStack_228,auStack_230,3);
          sVar2 = puVar5[2];
          if ((sVar2 == 0) || ((sVar2 != 7 && (sVar2 != 0xc)))) break;
        }
        func_0x033ad8a0();
        uVar3 = ~(ushort)uVar1;
        (*ppsVar8)[0xbf] = (*ppsVar8)[0xbf] & uVar3;
        (*ppsVar8)[0x43] = (*ppsVar8)[0x43] & uVar3;
        psVar6 = *ppsVar8;
        *(undefined4 *)(psVar6 + uVar7 * 4 + 0x398) = 0;
        *(undefined4 *)(psVar6 + uVar7 * 4 + 0x39a) = 0;
        func_0x033ad8b4();
      }
      uVar7 = uVar7 + 1;
    } while ((int)uVar7 < 0x10);
    puVar5 = FUN_02392558(auStack_228,1);
    if (puVar5[2] == 0) {
      (*ppsVar8)[0x5f] = 0;
      **ppsVar8 = 3;
      iVar4 = FUN_02391b00(auStack_228);
      if (*(short *)(iVar4 + 4) == 0) {
        **ppsVar8 = 2;
        (*ppsVar8)[199] = 0;
        (*ppsVar8)[200] = 0;
        puVar5 = (undefined2 *)func_0x033b7438();
        *puVar5 = 9;
        puVar5[1] = 0;
        func_0x033b74e0();
      }
      else {
        FUN_02392efc((short)DAT_023930f4,*(short *)(iVar4 + 4));
      }
    }
    else {
      FUN_02392efc(0,puVar5[2]);
    }
  }
  else {
    puVar5 = (undefined2 *)func_0x033b7438();
    *puVar5 = 9;
    puVar5[1] = 3;
    func_0x033b74e0();
  }
  return;
}



void FUN_023930f8(undefined2 param_1,undefined2 param_2,int param_3)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  if (param_3 == 0) {
    *puVar1 = 10;
  }
  else {
    *puVar1 = 0x26;
  }
  puVar1[1] = 1;
  puVar1[4] = 4;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



int FUN_02393144(int param_1)

{
  int iVar1;
  
  iVar1 = func_0x033b6d70(param_1 + -0x40,0x42);
  return param_1 + iVar1 * -2 + 0x5e;
}



void FUN_02393168(int param_1)

{
  short sVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  undefined2 uVar5;
  ushort uVar6;
  ushort uVar7;
  bool bVar8;
  int iVar9;
  undefined2 *puVar10;
  undefined2 *puVar11;
  undefined4 uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  ushort *puVar16;
  uint uVar17;
  short **ppsVar18;
  
  iVar15 = -DAT_023935c0;
  puVar10 = (undefined2 *)(&stack0x00000024 + iVar15);
  iVar9 = FUN_023901d8();
  ppsVar18 = *(short ***)(iVar9 + 0x1518);
  sVar1 = **ppsVar18;
  if (((sVar1 == 2) || (sVar1 == 3)) || (sVar1 == 5)) {
    *(undefined4 *)(*ppsVar18 + 0xc0) = *(undefined4 *)(param_1 + 4);
    uVar2 = *(ushort *)(param_1 + 2);
    (*ppsVar18)[0xc6] = uVar2;
    uVar3 = *(ushort *)(param_1 + 10);
    func_0x033adc88(param_1 + 0xc,&stack0xffffffee + iVar15,6);
    uVar4 = *(ushort *)(param_1 + 0x12);
    uVar5 = *(undefined2 *)(param_1 + 0x14);
    func_0x033adc88(param_1 + 0x16,&stack0xfffffff4 + iVar15,0x20);
    uVar6 = *(ushort *)(param_1 + 8);
    uVar7 = *(ushort *)(&stack0xffffffee + iVar15);
    if ((uVar7 != DAT_023935c4) && ((uVar7 & 1) != 0)) {
      *(ushort *)(&stack0xffffffee + iVar15) = uVar7 & 0xfffe;
    }
    uVar17 = ((uint)uVar2 << 0x11) >> 0x10 & (uint)(ushort)(*ppsVar18)[0xf8];
    if (uVar17 == 0) {
      puVar10 = (undefined2 *)func_0x033b7438();
      *puVar10 = 0x26;
      puVar10[1] = 6;
      puVar10[4] = 4;
      func_0x033b74e0();
    }
    else if (((*(uint *)(param_1 + 4) == 0) || ((*(uint *)(param_1 + 4) & 3) != 0)) ||
            (*(ushort *)(param_1 + 8) < 0x40)) {
      puVar10 = (undefined2 *)func_0x033b7438();
      *puVar10 = 0x26;
      puVar10[1] = 6;
      puVar10[4] = 4;
      func_0x033b74e0();
    }
    else {
      (*ppsVar18)[0x71] = 2;
      iVar9 = FUN_02391a78(puVar10);
      if (*(short *)(iVar9 + 4) == 0) {
        if (*(short *)(iVar9 + 6) == 0x10) {
          bVar8 = FUN_0238fe40(0x26,puVar10);
          if (!bVar8) {
            return;
          }
          iVar9 = FUN_02391ae8(puVar10);
          if (*(short *)(iVar9 + 4) != 0) {
            FUN_023930f8((short)DAT_023935c8,*(short *)(iVar9 + 4),1);
            return;
          }
          **ppsVar18 = 3;
          puVar11 = FUN_023924f4(puVar10,1,0,1);
          if (puVar11[2] != 0) {
            FUN_023930f8(1,puVar11[2],1);
            return;
          }
          (*ppsVar18)[0x61] = 1;
        }
        if (uVar4 == 0) {
          if ((*ppsVar18)[0xf5] == 1) {
            puVar11 = FUN_02391d94(puVar10,0);
            if (puVar11[2] != 0) {
              FUN_023930f8((short)DAT_023935cc,puVar11[2],1);
              return;
            }
            (*ppsVar18)[0xf5] = 0;
          }
        }
        else if ((*ppsVar18)[0xf5] == 0) {
          puVar11 = FUN_02391d94(puVar10,1);
          if (puVar11[2] != 0) {
            FUN_023930f8((short)DAT_023935cc,puVar11[2],1);
            return;
          }
          (*ppsVar18)[0xf5] = 1;
        }
        **ppsVar18 = 5;
        uVar14 = 0;
        func_0x033adbf4(&stack0x00000014 + iVar15,0,0x10);
        uVar13 = 1;
        do {
          if ((uVar17 & 1 << (uVar13 & 0xff)) != 0) {
            (&stack0x00000014)[uVar14 + iVar15] = (char)uVar13;
            uVar14 = uVar14 + 1 & 0xffff;
          }
          uVar13 = uVar13 + 1 & 0xffff;
        } while (uVar13 < 0xf);
        uVar14 = FUN_02393144((uint)uVar6);
        *(undefined **)(&stack0xffffffdc + iVar15) = &stack0xfffffff4 + iVar15;
        *(uint *)(&stack0xffffffe0 + iVar15) = (uint)uVar4;
        *(undefined **)(&stack0xffffffe4 + iVar15) = &stack0x00000014 + iVar15;
        *(uint *)(&stack0xffffffe8 + iVar15) = (uint)uVar3;
        puVar10 = FUN_02392438(puVar10,uVar14,&stack0xffffffee + iVar15,uVar5,
                               *(undefined4 *)(&stack0xffffffdc + iVar15),
                               *(undefined2 *)(&stack0xffffffe0 + iVar15),
                               *(undefined4 *)(&stack0xffffffe4 + iVar15),
                               *(undefined2 *)(&stack0xffffffe8 + iVar15));
        if (puVar10[2] == 0) {
          puVar11 = (undefined2 *)func_0x033b7438();
          uVar5 = (undefined2)((int)uVar17 >> 1);
          if (puVar10[4] == 0) {
            *puVar11 = 0x26;
            puVar11[1] = 0;
            puVar11[4] = 4;
            puVar11[7] = 0;
            puVar11[5] = uVar5;
          }
          else {
            puVar16 = puVar10 + 5;
            uVar17 = *(uint *)(*ppsVar18 + 0xc0);
            *(undefined2 *)(&stack0xffffffec + iVar15) = 0;
            func_0x033adb48(*(undefined2 *)(&stack0xffffffec + iVar15),uVar17,(uint)uVar6);
            for (iVar15 = 0; iVar15 < (int)(uint)(ushort)puVar10[4]; iVar15 = iVar15 + 1) {
              uVar14 = (uint)*puVar16 << 0x11;
              func_0x033adc88(puVar16,uVar17,uVar14 >> 0x10);
              *(uint *)(puVar11 + iVar15 * 2 + 8) = uVar17;
              uVar13 = FUN_0238fe24(puVar16[1] & 0xff);
              uVar12 = FUN_0238fd5c(uVar13);
              puVar11[iVar15 + 0x28] = (short)uVar12;
              puVar16 = (ushort *)((int)puVar16 + (uVar14 >> 0x10));
              uVar17 = uVar17 + (uVar14 >> 0x10);
              if ((uVar17 & 2) != 0) {
                uVar17 = uVar17 + 2 & 0xfffffffc;
              }
            }
            *puVar11 = 0x26;
            puVar11[1] = 0;
            puVar11[4] = 5;
            puVar11[7] = puVar10[4];
            puVar11[5] = uVar5;
          }
          func_0x033b74e0(puVar11);
        }
        else {
          FUN_023930f8(2,puVar10[2],1);
        }
      }
      else {
        FUN_023930f8(0x308,*(short *)(iVar9 + 4),1);
      }
    }
  }
  else {
    puVar10 = (undefined2 *)func_0x033b7438();
    *puVar10 = 0x26;
    puVar10[1] = 3;
    puVar10[4] = 4;
    func_0x033b74e0();
  }
  return;
}



void FUN_023935d0(int param_1)

{
  short sVar1;
  ushort uVar2;
  undefined2 uVar3;
  bool bVar4;
  int iVar5;
  undefined2 *puVar6;
  undefined2 *puVar7;
  uint uVar8;
  undefined4 uVar9;
  short **ppsVar10;
  ushort local_252 [3];
  undefined auStack_24c [32];
  undefined local_22c;
  undefined auStack_22b [15];
  undefined2 auStack_21c [258];
  
  iVar5 = FUN_023901d8();
  ppsVar10 = *(short ***)(iVar5 + 0x1518);
  sVar1 = **ppsVar10;
  if (((sVar1 == 2) || (sVar1 == 3)) || (sVar1 == 5)) {
    *(undefined4 *)(*ppsVar10 + 0xc0) = *(undefined4 *)(param_1 + 4);
    uVar2 = *(ushort *)(param_1 + 2);
    (*ppsVar10)[0xc6] = uVar2;
    uVar3 = *(undefined2 *)(param_1 + 8);
    func_0x033adc88(param_1 + 10,local_252,6);
    if ((local_252[0] != DAT_0239396c) && ((local_252[0] & 1) != 0)) {
      local_252[0] = local_252[0] & 0xfffe;
    }
    if (uVar2 == 0) {
      puVar6 = (undefined2 *)func_0x033b7438();
      *puVar6 = 10;
      puVar6[1] = 6;
      puVar6[4] = 4;
      func_0x033b74e0();
    }
    else if ((1 << (uVar2 & 0xff) & (uint)(ushort)(*ppsVar10)[0xf8]) == 0) {
      puVar6 = (undefined2 *)func_0x033b7438();
      *puVar6 = 10;
      puVar6[1] = 6;
      puVar6[4] = 4;
      func_0x033b74e0();
    }
    else {
      (*ppsVar10)[0x71] = 2;
      iVar5 = FUN_02391a78(auStack_21c);
      if (*(short *)(iVar5 + 4) == 0) {
        if (*(short *)(iVar5 + 6) == 0x10) {
          bVar4 = FUN_0238fe40(10,auStack_21c);
          if (!bVar4) {
            return;
          }
          iVar5 = FUN_02391ae8(auStack_21c);
          if (*(short *)(iVar5 + 4) != 0) {
            FUN_023930f8((short)DAT_02393970,*(short *)(iVar5 + 4),0);
            return;
          }
          **ppsVar10 = 3;
          puVar6 = FUN_023924f4(auStack_21c,1,0,1);
          if (puVar6[2] != 0) {
            FUN_023930f8(1,puVar6[2],0);
            return;
          }
          (*ppsVar10)[0x61] = 1;
        }
        **ppsVar10 = 5;
        func_0x033adb48(DAT_0239396c & 0xffff,auStack_24c,0x20);
        local_22c = (undefined)uVar2;
        func_0x033adbf4(auStack_22b,0,0xf);
        puVar6 = FUN_02392438(auStack_21c,DAT_02393974,local_252,0,auStack_24c,1,&local_22c,uVar3);
        if (puVar6[2] == 0) {
          puVar7 = (undefined2 *)func_0x033b7438();
          if (puVar6[4] == 0) {
            *puVar7 = 10;
            puVar7[1] = 0;
            puVar7[4] = 4;
            puVar7[8] = uVar2;
            puVar7[9] = 0;
          }
          else {
            func_0x033adb48(0,*(int *)(*ppsVar10 + 0xc0) + 0x40,0x80);
            func_0x033adc88(puVar6 + 5,*(undefined4 *)(*ppsVar10 + 0xc0),
                            (uint)(ushort)puVar6[5] << 1);
            *puVar7 = 10;
            puVar7[1] = 0;
            puVar7[4] = 5;
            puVar7[8] = puVar6[0x20];
            uVar8 = FUN_0238fe24((ushort)puVar6[6] & 0xff);
            uVar9 = FUN_0238fd5c(uVar8);
            puVar7[9] = (short)uVar9;
            puVar7[10] = puVar6[10];
            func_0x033adc88(puVar6 + 7,puVar7 + 5,6);
            func_0x033adb60(puVar6 + 0xb,puVar7 + 0xb,0x20);
            puVar7[0x1b] = puVar6[0x23];
            if ((ushort)puVar7[0x1b] < 0x81) {
              func_0x033adb48(0,puVar7 + 0x1c,0x80);
              func_0x033adb60(puVar6 + 0x25,puVar7 + 0x1c,(ushort)puVar7[0x1b] + 1 & 0xfffffffe);
            }
            else {
              *puVar7 = 10;
              puVar7[1] = 0;
              puVar7[4] = 4;
              puVar7[8] = uVar2;
              puVar7[9] = 0;
            }
          }
          func_0x033b74e0(puVar7);
        }
        else {
          FUN_023930f8(2,puVar6[2],0);
        }
      }
      else {
        FUN_023930f8(0x308,*(short *)(iVar5 + 4),0);
      }
    }
  }
  else {
    puVar6 = (undefined2 *)func_0x033b7438();
    *puVar6 = 10;
    puVar6[1] = 3;
    puVar6[4] = 4;
    func_0x033b74e0();
  }
  return;
}



void FUN_02393978(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0xb;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_023939b4(void)

{
  int iVar1;
  undefined2 *puVar2;
  short **ppsVar3;
  undefined2 auStack_210 [258];
  
  iVar1 = FUN_023901d8();
  ppsVar3 = *(short ***)(iVar1 + 0x1518);
  if (**ppsVar3 == 5) {
    iVar1 = FUN_02391b00(auStack_210);
    if (*(short *)(iVar1 + 4) == 0) {
      **ppsVar3 = 2;
      if ((*ppsVar3)[0xf5] == 0) {
        puVar2 = FUN_02391d94(auStack_210,1);
        if (puVar2[2] != 0) {
          FUN_02393978((short)DAT_02393a94,puVar2[2]);
          return;
        }
        (*ppsVar3)[0xf5] = 1;
      }
      puVar2 = (undefined2 *)func_0x033b7438();
      *puVar2 = 0xb;
      puVar2[1] = 0;
      func_0x033b74e0();
    }
    else {
      FUN_02393978((short)DAT_02393a90,*(short *)(iVar1 + 4));
    }
  }
  else {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 0xb;
    puVar2[1] = 3;
    func_0x033b74e0();
  }
  return;
}



void FUN_02393a98(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0xc;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_02393ad4(int param_1)

{
  bool bVar1;
  int iVar2;
  undefined2 *puVar3;
  short *psVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 uVar7;
  short sVar8;
  short **ppsVar9;
  undefined8 uVar10;
  undefined auStack_266 [6];
  undefined auStack_260 [8];
  undefined2 auStack_258 [256];
  undefined auStack_58 [10];
  undefined2 local_4e;
  undefined2 local_4c;
  undefined2 local_4a;
  undefined2 local_48;
  undefined2 local_46;
  undefined auStack_44 [48];
  
  iVar2 = FUN_023901d8();
  ppsVar9 = *(short ***)(iVar2 + 0x1518);
  if (**ppsVar9 == 2) {
    func_0x033adc88(*(undefined4 *)(param_1 + 4),ppsVar9 + 4,0xc0);
    if ((*(ushort *)(ppsVar9 + 0x13) < 0x10) || ((*(byte *)((int)ppsVar9 + 0x5b) & 1) != 0)) {
      uVar6 = 1 << (*(ushort *)((int)ppsVar9 + 0x46) & 0xff);
      if (((uVar6 & (ushort)(*ppsVar9)[0xf8]) == 0) || (((int)uVar6 >> 1 & DAT_02394050) == 0)) {
        puVar3 = (undefined2 *)func_0x033b7438();
        *puVar3 = 0xc;
        puVar3[1] = 6;
        puVar3[4] = 6;
        func_0x033b74e0();
      }
      else {
        puVar3 = (undefined2 *)func_0x033b7438();
        *puVar3 = 0xc;
        puVar3[1] = 0;
        puVar3[4] = 6;
        func_0x033b74e0();
        psVar4 = *ppsVar9;
        if (psVar4[0xf4] == 1) {
          if ((*(ushort *)((int)ppsVar9 + 0x3e) & 1) == 0) {
            psVar4[0xf4] = 2;
          }
          else {
            psVar4[0xf4] = 1;
          }
        }
        else if ((*(ushort *)((int)ppsVar9 + 0x3e) & 2) == 0) {
          psVar4[0xf4] = 1;
        }
        else {
          psVar4[0xf4] = 2;
        }
        if ((*(ushort *)(ppsVar9 + 0xf) & 0x20) == 0) {
          (*ppsVar9)[0xf5] = 0;
        }
        else {
          (*ppsVar9)[0xf5] = 1;
        }
        if ((*(ushort *)(ppsVar9 + 0xf) & 0x10) == 0) {
          *(undefined4 *)(*ppsVar9 + 0xca) = 0;
        }
        else {
          *(undefined4 *)(*ppsVar9 + 0xca) = 1;
        }
        if (*(short *)(ppsVar9 + 0x13) == 0) {
          (*ppsVar9)[0x71] = 3;
        }
        else {
          (*ppsVar9)[0x71] = 2;
        }
        bVar1 = FUN_0238fe40(0xc,auStack_258);
        if (bVar1) {
          iVar2 = FUN_02391ae8(auStack_258);
          if (*(short *)(iVar2 + 4) == 0) {
            **ppsVar9 = 3;
            iVar2 = *(int *)(param_1 + 0x20);
            bVar1 = iVar2 != 0;
            if (bVar1) {
              iVar2 = 1;
            }
            sVar8 = (short)iVar2;
            if (!bVar1) {
              sVar8 = 0;
            }
            puVar3 = FUN_023924f4(auStack_258,sVar8,0,1);
            if (puVar3[2] == 0) {
              (*ppsVar9)[0x61] = sVar8;
              func_0x033adc88(ppsVar9 + 4,auStack_58,0x40);
              if ((*ppsVar9)[0x71] == 2) {
                local_4e = 0x20;
                local_4c = SUB42(ppsVar9[0x15],0);
                local_4a = (undefined2)((uint)ppsVar9[0x15] >> 0x10);
                local_48 = *(undefined2 *)(ppsVar9 + 0x16);
                local_46 = 0;
                func_0x033adc88(param_1 + 8,auStack_44,0x18);
              }
              puVar3 = FUN_023923b4(auStack_258,2000,auStack_58);
              if ((puVar3[2] == 0) && (puVar3[3] == 0)) {
                func_0x033adc88(puVar3 + 4,(int)*ppsVar9 + DAT_02394058,6);
                if ((*(byte *)((int)ppsVar9 + 0x5b) & 4) == 0) {
                  sVar8 = 0;
                }
                else {
                  sVar8 = 6;
                }
                (*ppsVar9)[199] = *(short *)((int)ppsVar9 + 0x5e) + 2 + sVar8;
                if ((*(byte *)((int)ppsVar9 + 0x5b) & 4) == 0) {
                  sVar8 = 0;
                }
                else {
                  sVar8 = 0x2a;
                }
                (*ppsVar9)[200] = *(short *)(ppsVar9 + 0x17) + 4 + sVar8;
                func_0x033adc88((int)*ppsVar9 + DAT_02394058,auStack_266,6);
                puVar3 = FUN_02392330(auStack_258,auStack_266,*(undefined2 *)(param_1 + 0x26),2000);
                sVar8 = puVar3[2];
                if ((sVar8 == 0xc) && (puVar3[3] == 0x13)) {
                  puVar3 = (undefined2 *)func_0x033b7438();
                  *puVar3 = 0xc;
                  puVar3[1] = 0xc;
                  puVar3[4] = 6;
                  func_0x033b74e0();
                }
                else if ((sVar8 == 0) && (puVar3[3] == 0)) {
                  func_0x033adc88((int)*ppsVar9 + DAT_02394058,auStack_260,6);
                  puVar3 = FUN_0239222c(auStack_258,auStack_260,1,2000);
                  uVar5 = func_0x033ad8a0();
                  if ((puVar3[2] == 0xc) && (puVar3[3] == 0x13)) {
                    func_0x033ad8b4();
                    puVar3 = (undefined2 *)func_0x033b7438();
                    *puVar3 = 0xc;
                    puVar3[1] = 0xc;
                    puVar3[4] = 6;
                    func_0x033b74e0();
                  }
                  else if ((puVar3[2] == 0) && (puVar3[3] == 0)) {
                    (*ppsVar9)[0xc2] = puVar3[4];
                    (*ppsVar9)[0x5b] = *(short *)(ppsVar9 + 0x16);
                    func_0x033adb48(1,*ppsVar9 + 0xfa,0x10);
                    uVar6 = FUN_0238fe24(*(ushort *)((int)ppsVar9 + 0x12) & 0xff);
                    uVar7 = FUN_0238fd5c(uVar6);
                    (*ppsVar9)[0x5c] = (short)uVar7;
                    FUN_0238fdc0((char)uVar6);
                    uVar7 = func_0x033ad8a0();
                    (*ppsVar9)[0xbf] = 1;
                    (*ppsVar9)[0x43] = 1;
                    if (*(int *)(*ppsVar9 + 0x3da) != 0 || *(int *)(*ppsVar9 + 0x3d8) != 0) {
                      uVar10 = func_0x033acba8();
                      psVar4 = *ppsVar9;
                      *(uint *)(psVar4 + 0x398) = (uint)uVar10 | 1;
                      *(int *)(psVar4 + 0x39a) = (int)((ulonglong)uVar10 >> 0x20);
                    }
                    **ppsVar9 = 8;
                    func_0x033ad8b4(uVar7);
                    (*ppsVar9)[0x5f] = 1;
                    puVar3 = (undefined2 *)func_0x033b7438();
                    *puVar3 = 0xc;
                    puVar3[1] = 0;
                    puVar3[4] = 7;
                    puVar3[5] = (*ppsVar9)[0xc2];
                    func_0x033b74e0();
                    func_0x033ad8b4(uVar5);
                  }
                  else {
                    func_0x033ad8b4(uVar5);
                    FUN_02393a98(6,puVar3[2]);
                  }
                }
                else {
                  FUN_02393a98(4,sVar8);
                }
              }
              else {
                FUN_02393a98(3,puVar3[2]);
              }
            }
            else {
              FUN_02393a98(1,puVar3[2]);
            }
          }
          else {
            FUN_02393a98((short)DAT_02394054,*(short *)(iVar2 + 4));
          }
        }
      }
    }
    else {
      puVar3 = (undefined2 *)func_0x033b7438();
      *puVar3 = 0xc;
      puVar3[1] = 0xb;
      puVar3[4] = 6;
      func_0x033b74e0();
    }
  }
  else {
    puVar3 = (undefined2 *)func_0x033b7438();
    *puVar3 = 0xc;
    puVar3[1] = 3;
    puVar3[4] = 6;
    func_0x033b74e0();
  }
  return;
}



void FUN_0239405c(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x25;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  puVar1[4] = param_3;
  puVar1[5] = param_4;
  func_0x033b74e0();
  return;
}



void FUN_023940a8(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0xd;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  puVar1[4] = param_3;
  puVar1[5] = param_4;
  func_0x033b74e0();
  return;
}



undefined4 FUN_023940f4(int param_1,int param_2,undefined2 *param_3)

{
  uint uVar1;
  short sVar2;
  undefined2 uVar3;
  ushort uVar4;
  ushort uVar5;
  undefined2 uVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined2 *puVar10;
  short *psVar11;
  uint uVar12;
  undefined2 uVar13;
  uint uVar14;
  short **ppsVar15;
  bool bVar16;
  int local_258;
  undefined auStack_234 [6];
  undefined auStack_22e [6];
  undefined2 auStack_228 [258];
  
  iVar7 = FUN_023901d8();
  ppsVar15 = *(short ***)(iVar7 + 0x1518);
  uVar8 = *(uint *)(param_1 + 4);
  if (param_2 == 0) {
    uVar6 = 0;
  }
  else {
    uVar6 = (undefined2)*(undefined4 *)(param_1 + 8);
  }
  uVar14 = 0;
  bVar16 = false;
  sVar2 = **ppsVar15;
  uVar3 = (undefined2)uVar8;
  if ((sVar2 == 9) || (sVar2 == 7)) {
    bVar16 = *(int *)(*ppsVar15 + 6) == 1;
  }
  else {
    if ((sVar2 != 10) && (sVar2 != 8)) {
      if (param_2 == 0) {
        puVar10 = (undefined2 *)func_0x033b7438();
        *puVar10 = 0xd;
        puVar10[1] = 3;
        puVar10[2] = 0;
        puVar10[3] = 0;
        puVar10[4] = uVar3;
        puVar10[5] = 0;
        func_0x033b74e0();
      }
      return 0;
    }
    uVar9 = func_0x033ad8a0();
    if (*(int *)(*ppsVar15 + 6) == 1) {
      *(undefined4 *)(*ppsVar15 + 6) = 0;
      bVar16 = true;
      func_0x033ad4f0(ppsVar15 + 0x34);
      FUN_0238fcfc();
      if (**ppsVar15 == 10) {
        **ppsVar15 = 8;
      }
    }
    (*ppsVar15)[0xbf] = 0;
    (*ppsVar15)[0x43] = 0;
    *(undefined4 *)(*ppsVar15 + 10) = 0;
    *(undefined4 *)(*ppsVar15 + 8) = 0;
    *(undefined4 *)(*ppsVar15 + 0xe) = 0;
    func_0x033ad8b4(uVar9);
  }
  sVar2 = **ppsVar15;
  if ((sVar2 == 10) || (sVar2 == 8)) {
    func_0x033adc88((int)*ppsVar15 + DAT_0239467c,auStack_234,6);
    for (iVar7 = 0; iVar7 < 2; iVar7 = iVar7 + 1) {
      puVar10 = FUN_023922ac(auStack_228,auStack_234,3);
      sVar2 = puVar10[2];
      if (sVar2 == 0) break;
      if ((sVar2 != 7) && (sVar2 != 0xc)) {
        if (param_2 == 0) {
          FUN_023940a8(5,sVar2,uVar3,0);
        }
        else {
          FUN_0239405c(5,sVar2,uVar3,0);
        }
        if (bVar16) {
          FUN_02396268(1);
        }
        return 0;
      }
    }
    uVar13 = 1;
    (*ppsVar15)[0x5f] = 0;
    **ppsVar15 = 3;
    puVar10 = FUN_02392558(auStack_228,1);
    sVar2 = puVar10[2];
    if (sVar2 != 0) {
      if (param_2 == 0) {
        FUN_023940a8(0,sVar2,uVar3,1);
      }
      else {
        FUN_0239405c(0,sVar2,uVar3,1);
      }
      if (bVar16) {
        FUN_02396268(1);
      }
      return 0;
    }
    iVar7 = FUN_02391b00(auStack_228);
    sVar2 = *(short *)(iVar7 + 4);
    if (sVar2 != 0) {
      if (param_2 == 0) {
        FUN_023940a8((short)DAT_02394680,sVar2,uVar3,1);
      }
      else {
        FUN_0239405c((short)DAT_02394680,sVar2,uVar3,1);
      }
      if (bVar16) {
        FUN_02396268(1);
      }
      return 0;
    }
    **ppsVar15 = 2;
    if (param_2 == 1) {
      puVar10 = (undefined2 *)func_0x033b7438();
      *puVar10 = 0xc;
      puVar10[1] = 0;
      puVar10[4] = 9;
      puVar10[6] = uVar6;
      puVar10[5] = (*ppsVar15)[0xc2];
      (*ppsVar15)[199] = 0;
      (*ppsVar15)[200] = 0;
      func_0x033b74e0();
    }
    if (bVar16) {
      FUN_02396268(1);
    }
  }
  else {
    for (uVar12 = 1; uVar13 = (undefined2)uVar14, (int)uVar12 < 0x10; uVar12 = uVar12 + 1) {
      uVar1 = 1 << (uVar12 & 0xff);
      if ((uVar1 & (uint)(ushort)(*ppsVar15)[0xbf] & uVar8 & 0xffff) != 0) {
        func_0x033adc88(*ppsVar15 + (uVar12 - 1) * 3 + 0x92,auStack_22e,6);
        for (local_258 = 0; local_258 < 2; local_258 = local_258 + 1) {
          puVar10 = FUN_023922ac(auStack_228,auStack_22e,3);
          sVar2 = puVar10[2];
          if (sVar2 == 0) break;
          if ((sVar2 != 7) && (sVar2 != 0xc)) {
            if (param_2 == 0) {
              FUN_023940a8(5,sVar2,uVar3,uVar13);
            }
            else {
              FUN_0239405c(5,sVar2,uVar3,uVar13);
            }
            if (bVar16) {
              FUN_02396268(1);
            }
            return 0;
          }
        }
        uVar14 = uVar14 | 1 << (uVar12 & 0xff) & 0xffffU;
        func_0x033ad8a0();
        uVar5 = (ushort)uVar1;
        uVar4 = ~uVar5;
        (*ppsVar15)[0xbf] = (*ppsVar15)[0xbf] & uVar4;
        (*ppsVar15)[0x43] = (*ppsVar15)[0x43] & uVar4;
        psVar11 = *ppsVar15;
        *(undefined4 *)(psVar11 + (uVar12 & 0xffff) * 4 + 0x398) = 0;
        *(undefined4 *)(psVar11 + (uVar12 & 0xffff) * 4 + 0x39a) = 0;
        func_0x033ad8b4();
        iVar7 = uVar12 * 6;
        *(undefined *)(*ppsVar15 + uVar12 * 3 + 0x8f) = 0;
        *(undefined *)((int)*ppsVar15 + iVar7 + 0x11f) = 0;
        *(undefined *)(*ppsVar15 + uVar12 * 3 + 0x90) = 0;
        *(undefined *)((int)*ppsVar15 + iVar7 + 0x121) = 0;
        *(undefined *)(*ppsVar15 + uVar12 * 3 + 0x91) = 0;
        *(undefined *)((int)*ppsVar15 + iVar7 + 0x123) = 0;
        if (param_2 == 1) {
          puVar10 = (undefined2 *)func_0x033b7438();
          *puVar10 = 8;
          puVar10[1] = 0;
          puVar10[4] = 9;
          puVar10[9] = uVar6;
          puVar10[8] = (short)uVar12;
          func_0x033adc88(auStack_22e,puVar10 + 5,6);
          func_0x033b74e0(puVar10);
        }
        if (bVar16) {
          FUN_02396268(uVar5);
        }
      }
    }
  }
  if (param_3 != (undefined2 *)0x0) {
    *param_3 = uVar13;
  }
  return 1;
}



void FUN_02394684(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  undefined4 uVar3;
  undefined2 local_10 [4];
  
  uVar3 = *(undefined4 *)(param_1 + 4);
  iVar1 = FUN_023940f4(param_1,0,local_10);
  if (iVar1 == 1) {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 0xd;
    puVar2[1] = 0;
    puVar2[4] = (short)uVar3;
    puVar2[5] = local_10[0];
    func_0x033b74e0();
  }
  return;
}



void FUN_023946dc(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  undefined2 *puVar4;
  undefined4 uVar5;
  int iVar6;
  ushort *puVar7;
  bool bVar8;
  undefined8 uVar9;
  
  iVar2 = FUN_023901d8();
  puVar7 = **(ushort ***)(iVar2 + 0x1518);
  iVar6 = *(int *)(param_1 + 4);
  uVar3 = *(uint *)(param_1 + 8);
  if ((puVar7[0x71] == 2) &&
     (((uint)puVar7[0xf9] &
      (1 << (*(ushort *)((int)*(ushort ***)(iVar2 + 0x1518) + 0x46) & 0xff)) >> 1) == 0)) {
    puVar4 = (undefined2 *)func_0x033b7438();
    *puVar4 = 0xe;
    puVar4[1] = 6;
    puVar4[2] = 10;
    func_0x033b74e0();
  }
  else {
    if (*(int *)(puVar7 + 6) != 0) {
      *(undefined4 *)(puVar7 + 6) = 0;
      FUN_02396268((ushort)DAT_02394944);
    }
    FUN_023970fc();
    uVar5 = func_0x033ad8a0();
    if (((uint)*puVar7 + DAT_02394948 & 0xffff) < 2) {
      puVar7[0x42] = 0;
      puVar7[0x18] = 0;
      puVar7[0x19] = 1;
      puVar7[0x44] = 0;
      puVar7[0x4d] = 0;
      puVar7[0x4e] = 0x3c;
      *(undefined4 *)(puVar7 + 0x396) = 0;
      puVar7[0x45] = 0;
      puVar7[0x46] = 0;
      puVar7[0x47] = 0;
      puVar7[0x48] = 0;
      *(undefined4 *)(puVar7 + 0x1c) = 0;
      *(int *)(puVar7 + 0x24) = iVar6;
      puVar7[0x23] = (ushort)uVar3;
      *(uint *)(puVar7 + 0x26) = iVar6 + (uVar3 & 0xffff);
      puVar7[0x22] = 0;
      *(undefined4 *)(puVar7 + 0x28) = *(undefined4 *)(param_1 + 0xc);
      puVar7[0x2a] = (ushort)*(undefined4 *)(param_1 + 0x10);
      puVar7[0x1a] = (ushort)*(undefined4 *)(param_1 + 0x14);
      if (puVar7[0x1a] == 0) {
        puVar7[0x1a] = 0x10;
      }
      puVar7[0x4c] = (ushort)*(undefined4 *)(param_1 + 0x18);
      iVar2 = *(int *)(param_1 + 0x1c);
      bVar8 = iVar2 != 0;
      if (bVar8) {
        iVar2 = 1;
      }
      uVar1 = (ushort)iVar2;
      if (!bVar8) {
        uVar1 = 0;
      }
      puVar7[0x49] = uVar1;
      iVar2 = *(int *)(param_1 + 0x20);
      bVar8 = iVar2 != 0;
      if (bVar8) {
        iVar2 = 1;
      }
      uVar1 = (ushort)iVar2;
      if (!bVar8) {
        uVar1 = 0;
      }
      puVar7[0x4a] = uVar1;
      iVar2 = *(int *)(param_1 + 0x24);
      bVar8 = iVar2 != 0;
      if (bVar8) {
        iVar2 = 1;
      }
      uVar1 = (ushort)iVar2;
      if (!bVar8) {
        uVar1 = 0;
      }
      puVar7[0x4b] = uVar1;
      puVar7[0x1b] = 0;
      puVar7[0x1e] = 0;
      puVar7[0x1f] = 0;
      puVar7[0x5d] = (ushort)DAT_02394944;
      puVar7[0x5e] = 4;
      puVar7[0x6d] = (ushort)(*(int *)(param_1 + 0x28) != 0);
      uVar9 = func_0x033acba8();
      iVar2 = 0;
      do {
        *(uint *)(puVar7 + iVar2 * 4 + 0x398) = (uint)uVar9 | 1;
        *(int *)(puVar7 + iVar2 * 4 + 0x39a) = (int)((ulonglong)uVar9 >> 0x20);
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0x10);
      FUN_0238fc9c();
      puVar7[0x65] = 0;
      FUN_02395c74();
      if (*puVar7 == 8) {
        *puVar7 = 10;
      }
      else if (*puVar7 == 7) {
        *puVar7 = 9;
      }
      puVar4 = (undefined2 *)func_0x033b7438();
      *puVar4 = 0xe;
      puVar4[1] = 0;
      puVar4[2] = 10;
      func_0x033b74e0();
      *(undefined4 *)(puVar7 + 6) = 1;
      func_0x033ad8b4(uVar5);
    }
    else {
      func_0x033ad8b4();
      puVar4 = (undefined2 *)func_0x033b7438();
      *puVar4 = 0xe;
      puVar4[1] = 3;
      puVar4[2] = 10;
      func_0x033b74e0();
    }
  }
  return;
}



void FUN_0239494c(int param_1)

{
  uint *puVar1;
  ushort uVar2;
  ushort uVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  undefined2 *puVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  uint uVar11;
  undefined4 uVar12;
  bool bVar13;
  
  iVar6 = FUN_023901d8();
  iVar6 = **(int **)(iVar6 + 0x1518);
  uVar2 = *(ushort *)(iVar6 + 0x17e);
  uVar12 = *(undefined4 *)(param_1 + 4);
  sVar4 = (short)*(undefined4 *)(param_1 + 8);
  uVar11 = *(uint *)(param_1 + 0xc);
  uVar8 = *(uint *)(param_1 + 0x10);
  puVar1 = (uint *)(param_1 + 0x14);
  uVar10 = *(undefined4 *)(param_1 + 0x18);
  uVar9 = *(undefined4 *)(param_1 + 0x1c);
  if (*(short *)(iVar6 + 0x184) != 0) {
    uVar11 = 1;
  }
  bVar13 = *(int *)(iVar6 + 0xc) == 0;
  if (bVar13) {
    param_1 = 3;
  }
  uVar3 = (ushort)uVar11;
  if (!bVar13) {
    if ((uVar11 & uVar2) == 0) {
      param_1 = 0;
    }
    else {
      sVar5 = FUN_02396760(uVar2,*puVar1 & 0xffff,uVar8 & 0xffff,uVar3,uVar12,sVar4);
      param_1 = (int)sVar5;
    }
  }
  if (param_1 != 2) {
    puVar7 = (undefined2 *)func_0x033b7438();
    *puVar7 = 0x81;
    puVar7[1] = (short)param_1;
    puVar7[4] = 0x14;
    puVar7[5] = (short)uVar8;
    puVar7[6] = uVar3;
    if (param_1 == 10) {
      puVar7[7] = uVar3 & uVar2;
    }
    else {
      puVar7[7] = 0;
    }
    puVar7[8] = 0;
    puVar7[0xc] = sVar4;
    *(undefined4 *)(puVar7 + 10) = uVar12;
    *(undefined4 *)(puVar7 + 0xe) = uVar10;
    *(undefined4 *)(puVar7 + 0x10) = uVar9;
    puVar7[0xd] = (short)DAT_02394a5c;
    func_0x033b74e0();
  }
  return;
}



void FUN_02394a60(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x10;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_02394a9c(void)

{
  int iVar1;
  undefined2 *puVar2;
  undefined4 uVar3;
  int iVar4;
  short *psVar5;
  undefined2 auStack_218 [258];
  
  iVar1 = FUN_023901d8();
  psVar5 = **(short ***)(iVar1 + 0x1518);
  if ((*psVar5 == 9) || (*psVar5 == 10)) {
    uVar3 = func_0x033ad8a0();
    iVar4 = *(int *)(psVar5 + 6);
    *(undefined4 *)(psVar5 + 6) = 0;
    func_0x033ad4f0(*(int *)(iVar1 + 0x1518) + 0xd0);
    FUN_0238fcfc();
    if (*psVar5 == 10) {
      *psVar5 = 8;
    }
    else if (*psVar5 == 9) {
      *psVar5 = 7;
    }
    func_0x033ad8b4(uVar3);
    puVar2 = FUN_02391eb0(auStack_218,7);
    if (puVar2[2] == 0) {
      if (iVar4 == 1) {
        FUN_02396268((ushort)DAT_02394b9c);
      }
      puVar2 = (undefined2 *)func_0x033b7438();
      *puVar2 = 0x10;
      puVar2[1] = 0;
      func_0x033b74e0();
    }
    else {
      FUN_02394a60(0x104,puVar2[2]);
    }
  }
  else {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 0x10;
    puVar2[1] = 3;
    func_0x033b74e0();
  }
  return;
}



void FUN_02394ba0(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  undefined2 *puVar5;
  
  iVar1 = FUN_023901d8();
  puVar5 = (undefined2 *)**(undefined4 **)(iVar1 + 0x1518);
  iVar1 = *(int *)(param_1 + 4);
  uVar2 = *(uint *)(param_1 + 8);
  uVar3 = func_0x033ad8a0();
  *(int *)(puVar5 + 0x56) = iVar1;
  puVar5[0x5a] = (short)uVar2;
  *(uint *)(puVar5 + 0x58) = iVar1 + (uVar2 & 0xffff);
  puVar5[0x55] = 0;
  *(undefined4 *)(puVar5 + 0x52) = 0;
  puVar5[0x54] = 0;
  *(undefined4 *)(puVar5 + 0xc) = 0;
  *puVar5 = 0xb;
  puVar4 = (undefined2 *)func_0x033b7438();
  *puVar4 = 0x11;
  puVar4[1] = 0;
  puVar4[2] = 0xe;
  func_0x033b74e0();
  *(undefined4 *)(puVar5 + 8) = 1;
  func_0x033ad8b4(uVar3);
  return;
}



void FUN_02394c34(int param_1)

{
  short sVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  bool bVar5;
  undefined2 local_23c [3];
  undefined2 local_236;
  undefined local_22e;
  undefined auStack_224 [6];
  undefined auStack_21e [14];
  undefined4 local_210;
  undefined2 auStack_20c [256];
  
  iVar2 = FUN_023901d8();
  iVar2 = **(int **)(iVar2 + 0x1518);
  func_0x033adc88(param_1 + 4,iVar2 + 0x9e,6);
  *(undefined4 *)(iVar2 + 0xa4) = *(undefined4 *)(param_1 + 0xc);
  *(short *)(iVar2 + 0xa8) = (short)*(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(iVar2 + 0x18) = 1;
  func_0x033adb48(0,local_23c,0x30);
  local_23c[0] = 0;
  local_236 = (undefined2)*(undefined4 *)(param_1 + 0x10);
  sVar1 = *(short *)(iVar2 + 0x1e8);
  bVar5 = sVar1 == 2;
  if (bVar5) {
    sVar1 = 0x14;
  }
  local_22e = (undefined)sVar1;
  if (!bVar5) {
    local_22e = 10;
  }
  func_0x033adc88(param_1 + 4,auStack_224,6);
  func_0x033adc88(iVar2 + 0xdc,auStack_21e,6);
  local_210 = *(undefined4 *)(param_1 + 0xc);
  puVar3 = FUN_02392014(auStack_20c,(int)local_23c);
  puVar4 = (undefined2 *)func_0x033b7438();
  *puVar4 = 0x12;
  puVar4[1] = (ushort)(puVar3[2] != 0);
  if (puVar3[2] != 0) {
    puVar4[2] = 0x100;
    puVar4[3] = puVar3[2];
  }
  func_0x033b74e0();
  return;
}



void FUN_02394d38(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x13;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_02394d74(void)

{
  int iVar1;
  undefined2 *puVar2;
  short *psVar3;
  undefined2 auStack_208 [256];
  
  iVar1 = FUN_023901d8();
  psVar3 = **(short ***)(iVar1 + 0x1518);
  func_0x033ad8a0();
  if (*psVar3 == 0xb) {
    *(undefined4 *)(psVar3 + 8) = 0;
    *psVar3 = 8;
    func_0x033ad8b4();
    puVar2 = FUN_02391eb0(auStack_208,7);
    if (puVar2[2] == 0) {
      puVar2 = (undefined2 *)func_0x033b7438();
      *puVar2 = 0x13;
      puVar2[1] = 0;
      func_0x033b74e0();
    }
    else {
      FUN_02394d38(0x104,puVar2[2]);
    }
  }
  else {
    func_0x033ad8b4();
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 0x13;
    puVar2[1] = 3;
    func_0x033b74e0();
  }
  return;
}



void FUN_02394e18(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x14;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_02394e54(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  undefined2 auStack_210 [258];
  
  iVar1 = FUN_023901d8();
  iVar1 = **(int **)(iVar1 + 0x1518);
  *(short *)(iVar1 + 0x192) = (short)*(undefined4 *)(param_1 + 4);
  switch(*(undefined2 *)(iVar1 + 0x192)) {
  case 0:
    *(undefined4 *)(iVar1 + 0x194) = 0;
    goto LAB_02394ebc;
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  default:
    *(undefined4 *)(iVar1 + 0x194) = 0;
    goto LAB_02394ebc;
  }
  *(undefined4 *)(iVar1 + 0x194) = 1;
LAB_02394ebc:
  func_0x033adc88(*(undefined4 *)(param_1 + 8),iVar1 + 0x198,0x50);
  *(short *)(iVar1 + 0xc0) = (short)*(undefined4 *)(param_1 + 0xc);
  puVar2 = FUN_02391df4(auStack_210,*(undefined2 *)(iVar1 + 0xc0));
  if (puVar2[2] != 0) {
    FUN_02394e18((short)DAT_02394f18,puVar2[2]);
  }
  puVar2 = (undefined2 *)func_0x033b7438();
  *puVar2 = 0x27;
  puVar2[1] = 0;
  func_0x033b74e0();
  return;
}



void FUN_02394f1c(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  
  iVar1 = FUN_023901d8();
  iVar1 = **(int **)(iVar1 + 0x1518);
  *(short *)(iVar1 + 0x192) = (short)*(undefined4 *)(param_1 + 4);
  switch(*(undefined2 *)(iVar1 + 0x192)) {
  case 0:
    *(undefined4 *)(iVar1 + 0x194) = 0;
    goto LAB_02394f80;
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  default:
    *(undefined4 *)(iVar1 + 0x194) = 0;
    goto LAB_02394f80;
  }
  *(undefined4 *)(iVar1 + 0x194) = 1;
LAB_02394f80:
  func_0x033adc88(*(undefined4 *)(param_1 + 8),iVar1 + 0x198,0x50);
  puVar2 = (undefined2 *)func_0x033b7438();
  *puVar2 = 0x14;
  puVar2[1] = 0;
  func_0x033b74e0();
  return;
}



void FUN_02394fb0(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  undefined2 auStack_290 [256];
  undefined2 auStack_90 [66];
  
  iVar1 = FUN_023901d8();
  iVar1 = **(int **)(iVar1 + 0x1518);
  *(undefined4 *)(iVar1 + 0xe4) = *(undefined4 *)(param_1 + 4);
  *(short *)(iVar1 + 0xe8) = (short)*(undefined4 *)(param_1 + 8);
  *(undefined4 *)(iVar1 + 0xec) = *(undefined4 *)(param_1 + 0xc);
  *(short *)(iVar1 + 0xf0) = (short)*(undefined4 *)(param_1 + 0x10);
  uVar2 = *(uint *)(param_1 + 0x14);
  *(ushort *)(iVar1 + 0xf2) = (ushort)((uVar2 & 1) != 0);
  *(ushort *)(iVar1 + 0xf6) = (ushort)((uVar2 & 2) != 0);
  *(ushort *)(iVar1 + 0xf8) = (ushort)((uVar2 & 4) != 0);
  *(ushort *)(iVar1 + 0xfa) = (ushort)((uVar2 & 8) != 0);
  FUN_0238ffc4(auStack_90,(undefined4 *)(iVar1 + 0xe4));
  puVar3 = FUN_02391b74(auStack_290,*(ushort *)(iVar1 + 0xe8) + 0x10 & 0xffff,auStack_90);
  puVar4 = (undefined2 *)func_0x033b7438();
  *puVar4 = 0x18;
  puVar4[1] = (ushort)(puVar3[2] != 0);
  if (puVar3[2] != 0) {
    puVar4[2] = (short)DAT_023950a8;
    puVar4[3] = puVar3[2];
  }
  func_0x033b74e0();
  return;
}



void FUN_023950ac(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x19;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_023950e8(int param_1)

{
  undefined2 *puVar1;
  undefined2 auStack_208 [256];
  
  FUN_023901d8();
  puVar1 = FUN_02391c68(auStack_208,(short)*(undefined4 *)(param_1 + 4));
  if (puVar1[2] == 0) {
    puVar1 = (undefined2 *)func_0x033b7438();
    *puVar1 = 0x19;
    puVar1[1] = 0;
    func_0x033b74e0();
  }
  else {
    FUN_023950ac((short)DAT_02395148,puVar1[2]);
  }
  return;
}



void FUN_0239514c(void)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x1a;
  puVar1[1] = 4;
  func_0x033b74e0();
  return;
}



void FUN_02395178(void)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x1b;
  puVar1[1] = 4;
  func_0x033b74e0();
  return;
}



void FUN_023951a4(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x1d;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_023951e0(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined2 *puVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  undefined2 auStack_210 [256];
  
  iVar2 = FUN_023901d8();
  iVar2 = **(int **)(iVar2 + 0x1518);
  uVar1 = *(uint *)(param_1 + 0x10) & 0xffff;
  puVar3 = FUN_02391d28(auStack_210,(short)*(undefined4 *)(param_1 + 4),
                        (short)*(undefined4 *)(param_1 + 8),(short)*(undefined4 *)(param_1 + 0xc));
  if (puVar3[2] == 0) {
    if (uVar1 == DAT_023952e4) {
      *(undefined4 *)(iVar2 + 0x7b0) = 0;
      *(undefined4 *)(iVar2 + 0x7b4) = 0;
    }
    else {
      if (uVar1 == 0) {
        iVar4 = 1;
        iVar5 = 0;
      }
      else {
        iVar4 = func_0x033b6b64(uVar1 * DAT_023952e8,0x40);
        iVar5 = iVar4 >> 0x1f;
      }
      *(int *)(iVar2 + 0x7b0) = iVar4;
      *(int *)(iVar2 + 0x7b4) = iVar5;
    }
    uVar6 = func_0x033acba8();
    iVar5 = 0;
    do {
      iVar4 = iVar2 + iVar5 * 8;
      *(uint *)(iVar4 + 0x730) = (uint)uVar6 | 1;
      *(int *)(iVar4 + 0x734) = (int)((ulonglong)uVar6 >> 0x20);
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x10);
    puVar3 = (undefined2 *)func_0x033b7438();
    *puVar3 = 0x1d;
    puVar3[1] = 0;
    func_0x033b74e0();
  }
  else {
    FUN_023951a4((short)DAT_023952e0,puVar3[2]);
  }
  return;
}



void FUN_023952ec(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x1e;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_02395328(int param_1)

{
  short sVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  ushort uVar6;
  bool bVar7;
  int iVar8;
  undefined2 *puVar9;
  short **ppsVar10;
  undefined local_22c [16];
  undefined2 auStack_21c [256];
  
  iVar8 = FUN_023901d8();
  ppsVar10 = *(short ***)(iVar8 + 0x1518);
  if (**ppsVar10 == 2) {
    iVar8 = FUN_02391a78(auStack_21c);
    if (*(short *)(iVar8 + 4) == 0) {
      sVar1 = *(short *)(iVar8 + 6);
      (*ppsVar10)[0x71] = 2;
      if (sVar1 == 0x10) {
        bVar7 = FUN_0238fe40(10,auStack_21c);
        if (!bVar7) {
          return;
        }
        iVar8 = FUN_02391ae8(auStack_21c);
        if (*(short *)(iVar8 + 4) != 0) {
          FUN_023952ec((short)DAT_023954e8,*(short *)(iVar8 + 4));
          return;
        }
        **ppsVar10 = 3;
        puVar9 = FUN_023924f4(auStack_21c,1,0,1);
        if (puVar9[2] != 0) {
          FUN_023952ec(1,puVar9[2]);
          return;
        }
        (*ppsVar10)[0x61] = 1;
      }
      uVar2 = *(undefined2 *)(param_1 + 2);
      uVar3 = *(undefined2 *)(param_1 + 4);
      uVar4 = *(undefined2 *)(param_1 + 6);
      uVar5 = *(undefined2 *)(param_1 + 8);
      func_0x033adbf4(local_22c,0,0x10);
      local_22c[0] = (undefined)uVar4;
      puVar9 = FUN_023920cc(auStack_21c,uVar2,uVar3,uVar5,local_22c);
      if (puVar9[2] == 0) {
        uVar6 = puVar9[4];
        iVar8 = FUN_02391b00(auStack_21c);
        if (*(short *)(iVar8 + 4) == 0) {
          **ppsVar10 = 2;
          puVar9 = (undefined2 *)func_0x033b7438();
          *puVar9 = 0x1e;
          puVar9[1] = 0;
          puVar9[4] = uVar6 & 0xff;
          puVar9[5] = (short)((uint)uVar6 >> 8);
          func_0x033b74e0();
        }
        else {
          FUN_023952ec((short)DAT_023954ec,*(short *)(iVar8 + 4));
        }
      }
      else {
        FUN_023952ec(10,puVar9[2]);
      }
    }
    else {
      FUN_023952ec(0x308,*(short *)(iVar8 + 4));
    }
  }
  else {
    puVar9 = (undefined2 *)func_0x033b7438();
    *puVar9 = 0x1e;
    puVar9[1] = 3;
    func_0x033b74e0();
  }
  return;
}



void FUN_023954f0(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x1f;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_0239552c(void)

{
  int iVar1;
  undefined2 *puVar2;
  undefined auStack_208 [520];
  
  FUN_023901d8();
  iVar1 = FUN_02391abc(auStack_208);
  if (*(short *)(iVar1 + 4) == 0) {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 0x1f;
    puVar2[1] = 0;
    func_0x033b74e0();
  }
  else {
    FUN_023954f0((short)DAT_0239557c,*(short *)(iVar1 + 4));
  }
  return;
}



void FUN_02395580(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x20;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_023955bc(void)

{
  int iVar1;
  undefined2 *puVar2;
  undefined auStack_210 [516];
  
  FUN_023901d8();
  iVar1 = FUN_02391a8c(auStack_210);
  if (*(short *)(iVar1 + 4) == 0) {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 0x20;
    puVar2[1] = 0;
    func_0x033adb60(iVar1 + 8,puVar2 + 4,0xb4);
    func_0x033b74e0(puVar2);
  }
  else {
    FUN_02395580((short)DAT_02395628,*(short *)(iVar1 + 4));
  }
  return;
}



void FUN_0239562c(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  
  iVar1 = FUN_023901d8();
  iVar5 = **(int **)(iVar1 + 0x1518);
  func_0x033ad8a0();
  if (*(short *)(iVar5 + 0xca) == 1) {
    func_0x033ad8b4();
  }
  else {
    *(undefined2 *)(iVar5 + 0xca) = 1;
    func_0x033ad8b4();
    puVar2 = (undefined4 *)FUN_0238fbf8();
    if (puVar2 == (undefined4 *)0x0) {
      iVar3 = 0;
    }
    else {
      *puVar2 = 0x1c;
      iVar3 = func_0x033ac16c(iVar1 + 100,puVar2,0);
    }
    if ((iVar3 == 0) && (*(undefined2 *)(iVar5 + 0xca) = 0, *(int *)(iVar1 + 0x1518) != 0)) {
      puVar4 = (undefined2 *)func_0x033b7438();
      *puVar4 = 0x80;
      puVar4[1] = 8;
      puVar4[2] = 0x16;
      puVar4[3] = 0x1c;
      func_0x033b74e0();
    }
  }
  return;
}



void FUN_023956e4(void)

{
  int iVar1;
  
  iVar1 = FUN_023901d8();
  if (*(int *)(**(int **)(iVar1 + 0x1518) + 0xc) == 1) {
    func_0x033ad664(*(int **)(iVar1 + 0x1518) + 0x34,0xd1,DAT_02395730,DAT_02395734,0xd1);
    FUN_0239562c();
  }
  return;
}



void FUN_02395738(void)

{
  ushort uVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = FUN_023901d8();
  piVar3 = *(int **)(iVar2 + 0x1518);
  uVar1 = *(ushort *)(*piVar3 + 0xd8);
  if (uVar1 < 0x3c) {
    *(ushort *)(*piVar3 + 0xd8) = uVar1 + 1;
  }
  else {
    uVar1 = *(ushort *)PTR_REG_VCOUNT_023957b4;
    if ((0xd0 < uVar1) && (uVar1 < 0xd4)) {
      *(ushort *)PTR_REG_VCOUNT_023957b4 = uVar1;
      *(undefined2 *)(*piVar3 + 0xd8) = 0;
    }
  }
  FUN_02395b94();
  func_0x033ad664(piVar3 + 0x34,0x104,DAT_023957b8,DAT_023957bc,0x104);
  return;
}



void FUN_023957c0(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined2 *puVar3;
  uint uVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  undefined8 uVar9;
  
  iVar1 = FUN_023901d8();
  piVar5 = *(int **)(iVar1 + 0x1518);
  if (*(int *)(*piVar5 + 0xc) == 1) {
    func_0x033ad664(piVar5 + 0x34,200,DAT_023958e4,DAT_023958e8,200);
    if (*(int *)(*piVar5 + 0x7b4) != 0 || *(int *)(*piVar5 + 0x7b0) != 0) {
      uVar9 = func_0x033acba8();
      uVar7 = (uint)uVar9 | 1;
      iVar1 = *piVar5;
      uVar4 = *(uint *)(iVar1 + 0x730);
      if (*(int *)(iVar1 + 0x734) != 0 || uVar4 != 0) {
        uVar6 = uVar7 - uVar4;
        uVar7 = (int)((ulonglong)uVar9 >> 0x20) - (*(int *)(iVar1 + 0x734) + (uint)(uVar7 < uVar4));
        uVar4 = *(uint *)(iVar1 + 0x7b4);
        bVar8 = uVar4 <= uVar7;
        if (uVar7 == uVar4) {
          bVar8 = *(uint *)(iVar1 + 0x7b0) <= uVar6;
        }
        if (bVar8 && (uVar7 != uVar4 || uVar6 != *(uint *)(iVar1 + 0x7b0))) {
          *(undefined4 *)(iVar1 + 0x730) = 0;
          *(undefined4 *)(iVar1 + 0x734) = 0;
          puVar2 = (undefined4 *)FUN_0238fbf8();
          if (puVar2 == (undefined4 *)0x0) {
            iVar1 = 0;
          }
          else {
            *puVar2 = 0x25;
            puVar2[1] = 0;
            puVar2[2] = DAT_023958ec;
            iVar1 = FUN_023901d8();
            iVar1 = func_0x033ac16c(iVar1 + 100,puVar2,0);
          }
          if (iVar1 != 0) {
            return;
          }
          puVar3 = (undefined2 *)func_0x033b7438();
          *puVar3 = 0x80;
          puVar3[1] = 8;
          puVar3[2] = 0x16;
          puVar3[3] = 0x25;
          func_0x033b74e0();
          return;
        }
      }
    }
    FUN_0239562c();
  }
  return;
}



void FUN_023958f0(void)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = FUN_023901d8();
  piVar2 = *(int **)(iVar1 + 0x1518);
  FUN_023959ec();
  iVar1 = *piVar2;
  if (0x7e < *(uint *)(iVar1 + 0xd4)) {
    *(undefined4 *)(iVar1 + 0x1c) = 0;
  }
  func_0x033ad664(piVar2 + 0x34,0xf0,DAT_02395940,DAT_02395944,0xf0);
  return;
}



void FUN_02395948(void)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = FUN_023901d8();
  piVar2 = *(int **)(iVar1 + 0x1518);
  *(uint *)(*piVar2 + 0xcc) = (uint)*DAT_023959e0;
  iVar1 = *piVar2;
  if (*(int *)(iVar1 + 0xd0) != *(int *)(iVar1 + 0xcc)) {
    *(int *)(iVar1 + 0xd0) = *(int *)(iVar1 + 0xcc);
    FUN_02395a88();
  }
  if (*(uint *)(*piVar2 + 0xd4) < 0x80) {
    *(undefined4 *)(*piVar2 + 0x1c) = 1;
    func_0x033ad664(piVar2 + 0x34,0xf0,DAT_023959e4,DAT_023959e8,0xf0);
  }
  else {
    func_0x033ad664(piVar2 + 0x34,0xd0,DAT_023959e4,DAT_023959e8,0xd0);
  }
  return;
}



void FUN_023959ec(void)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  
  iVar2 = FUN_023901d8();
  piVar5 = *(int **)(iVar2 + 0x1518);
  uVar1 = *(ushort *)PTR_REG_VCOUNT_02395a84;
  if (((0xcf < uVar1) && (uVar1 < 0xd4)) && (uVar3 = *(uint *)(*piVar5 + 0xd4), 0x7e < uVar3)) {
    for (iVar2 = 1; (iVar2 < 7 && (iVar2 * 0x3f + 0x7fU <= uVar3)); iVar2 = iVar2 + 1) {
    }
    *(ushort *)PTR_REG_VCOUNT_02395a84 = uVar1 + (1 - (short)iVar2);
    iVar4 = *piVar5;
    *(int *)(iVar4 + 0xd4) = *(int *)(iVar4 + 0xd4) + iVar2 * -0x3f;
  }
  return;
}



void FUN_02395a88(void)

{
  undefined2 uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  iVar2 = FUN_023901d8();
  piVar3 = *(int **)(iVar2 + 0x1518);
  *(int *)(*piVar3 + 0xcc) = *(int *)(*piVar3 + 0xcc) << 6;
  iVar2 = DAT_02395b8c;
  uVar1 = *DAT_02395b7c;
  if (*DAT_02395b78 < *DAT_02395b78) {
    uVar1 = *DAT_02395b7c;
  }
  uVar5 = DAT_02395b84 &
          (DAT_02395b88 - (uint)*(ushort *)PTR_REG_VCOUNT_02395b80) * 0x7f +
          (CONCAT22(uVar1,*DAT_02395b78) & DAT_02395b84) * 2 >> 1;
  iVar4 = *piVar3;
  if (uVar5 < *(uint *)(iVar4 + 0xcc)) {
    *(undefined4 *)(iVar4 + 0xd4) = 0;
  }
  else {
    for (iVar6 = 1; iVar6 < 0x1e; iVar6 = iVar6 + 1) {
      *(int *)(iVar4 + 0xcc) = *(int *)(iVar4 + 0xcc) + iVar2;
      iVar4 = *piVar3;
      if (uVar5 < *(uint *)(iVar4 + 0xcc)) {
        *(uint *)(iVar4 + 0xd4) = *(uint *)(iVar4 + 0xcc) - uVar5;
        if (*(uint *)(*piVar3 + 0xd4) <= DAT_02395b90) {
          return;
        }
        *(undefined4 *)(*piVar3 + 0xd4) = 0;
        return;
      }
    }
    *(undefined4 *)(iVar4 + 0xd4) = 0;
  }
  return;
}



void FUN_02395b94(void)

{
  undefined2 uVar1;
  
  uVar1 = *DAT_02395be4;
  if (*DAT_02395be0 < *DAT_02395be0) {
    uVar1 = *DAT_02395be4;
  }
  *DAT_02395be8 =
       (short)(CONCAT22(uVar1,*DAT_02395be0) * 2 + (uint)*(ushort *)PTR_REG_VCOUNT_02395bdc * -0x7f
              >> 7);
  return;
}



void FUN_02395bec(uint param_1)

{
  if (param_1 < 0xd2) {
    if (param_1 < 0xd0) {
      if (param_1 == 200) {
        FUN_02395948();
      }
    }
    else if (param_1 == 0xd0) {
      FUN_023958f0();
    }
    else if (param_1 == 0xd1) {
      FUN_02395738();
    }
  }
  else if (param_1 < 0xf1) {
    if (param_1 == 0xf0) {
      FUN_023957c0();
    }
  }
  else if (param_1 == 0x104) {
    FUN_023956e4();
  }
  return;
}



void FUN_02395c74(void)

{
  short sVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = FUN_023901d8();
  piVar3 = *(int **)(iVar2 + 0x1518);
  sVar1 = *(short *)(*piVar3 + 0xe2);
  if (sVar1 == 1) {
    if (piVar3[0x34] != 0) {
      func_0x033ad4f0(piVar3 + 0x34);
    }
    func_0x033ad664(piVar3 + 0x34,0xd1,DAT_02395d1c,DAT_02395d20,0xd1);
  }
  else if (sVar1 == 2) {
    *(undefined4 *)(*piVar3 + 0x1c) = 0;
    if (piVar3[0x34] != 0) {
      func_0x033ad4f0(piVar3 + 0x34);
    }
    func_0x033ad664(piVar3 + 0x34,200,DAT_02395d1c,DAT_02395d20,200);
    *(undefined4 *)(*piVar3 + 0xd4) = 0;
  }
  return;
}



void FUN_02395d24(void)

{
  int iVar1;
  
  iVar1 = FUN_023901d8();
  func_0x033ad6fc(*(int *)(iVar1 + 0x1518) + 0xd0);
  return;
}



void FUN_02395d4c(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_023901d8();
  if (***(short ***)(iVar1 + 0x1518) == 9) {
    FUN_02396df0(*(uint *)(param_1 + 4) & 0xffff);
  }
  return;
}



void FUN_02395d88(void)

{
  int iVar1;
  
  iVar1 = FUN_023901d8();
  if (***(short ***)(iVar1 + 0x1518) == 10) {
    FUN_02397034();
  }
  return;
}



void FUN_02395dbc(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_023901d8();
  if (***(short ***)(iVar1 + 0x1518) == 9) {
    FUN_02396ea4(*(uint *)(param_1 + 4) & 0xffff);
  }
  return;
}



void FUN_02395df8(void)

{
  short sVar1;
  int iVar2;
  short *psVar3;
  bool bVar4;
  
  iVar2 = FUN_023901d8();
  psVar3 = **(short ***)(iVar2 + 0x1518);
  psVar3[0x65] = 0;
  psVar3[0x44] = 1;
  psVar3[0x5e] = psVar3[0x5e] + -1;
  if (psVar3[0x5e] == 0) {
    if ((ushort)psVar3[0x5d] != DAT_02395f58) {
      FUN_0238fdf8((char)psVar3[0x5d]);
      sVar1 = FUN_0238fd84();
      psVar3[0x5c] = sVar1;
      psVar3[0x5d] = (short)DAT_02395f58;
    }
    psVar3[0x5e] = 4;
  }
  if (*psVar3 == 9) {
    func_0x033ad8a0();
    sVar1 = psVar3[0x1b];
    psVar3[0x1b] = psVar3[0x1b] + psVar3[0x1a];
    if (0x100 < (ushort)psVar3[0x1b]) {
      psVar3[0x1b] = 0x100;
    }
    if ((sVar1 == 0) && (psVar3[0x1b] != 0)) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
    func_0x033ad8b4();
    if (bVar4) {
      FUN_02396ea4(DAT_02395f58);
    }
    if ((psVar3[0x49] == 1) && (psVar3[0x4e] = psVar3[0x4e] + -1, psVar3[0x4e] == 0)) {
      psVar3[0x4d] = 1;
      psVar3[0x4e] = 0x3c;
    }
  }
  else if (*psVar3 == 10) {
    bVar4 = false;
    func_0x033ad8a0();
    if ((psVar3[0x19] == 1) && (bVar4 = *(int *)(psVar3 + 0x396) != 1, bVar4)) {
      psVar3[0x19] = 0;
    }
    func_0x033ad8b4();
    if (bVar4) {
      FUN_02397034();
    }
  }
  return;
}



uint FUN_02395f5c(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = func_0x033b3a08(param_3);
  iVar2 = DAT_02395fe8 - (uint)*(ushort *)PTR_REG_VCOUNT_02395fe4;
  if (iVar2 < 0) {
    iVar2 = iVar2 + DAT_02395fec;
  }
  uVar3 = (int)((longlong)DAT_02395ff0 * (longlong)(iVar2 * 0x7f) >> 0x23) - (iVar2 * 0x7f >> 0x1f);
  if (uVar3 * 10 < (uint)((param_1 + 0x22) * 4 + param_2 * iVar1 + 1000)) {
    uVar3 = 0;
  }
  return uVar3 & 0xffff;
}



// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_02395ff4(uint param_1,undefined4 param_2,ushort *param_3,uint param_4,undefined4 param_5)

{
  ushort uVar1;
  ushort uVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  ushort *puVar8;
  undefined2 *puVar9;
  uint uVar10;
  ushort *puVar11;
  ushort *puVar12;
  ushort uVar13;
  int iVar14;
  ushort *puVar15;
  int iVar16;
  bool bVar17;
  bool bVar18;
  int iStack_54;
  int iStack_48;
  ushort auStack_c [6];
  
  iVar4 = FUN_023901d8();
  iVar4 = **(int **)(iVar4 + 0x1518);
  if (param_4 == 0) {
    return;
  }
  if (*(ushort *)(iVar4 + 400) < param_4) {
    return;
  }
  if (param_1 == *(ushort *)(iVar4 + 0x184)) {
    return;
  }
  if (0xf < param_1) {
    return;
  }
  if ((param_4 & 1) != 0) {
    return;
  }
  bVar3 = true;
  if ((int)param_4 < 1) {
    return;
  }
  iVar16 = iVar4 + 500 + param_1 * 0x10;
  iStack_54 = 0x200;
  iStack_48 = 2;
  do {
    if (bVar3) {
      bVar3 = false;
      puVar12 = auStack_c;
      puVar15 = param_3;
    }
    else {
      puVar15 = param_3 + 1;
      param_4 = param_4 - 2;
      puVar12 = param_3;
    }
    uVar13 = *puVar12;
    iVar14 = (uVar13 & 0xff) << 1;
    if ((uVar13 & 0xff) == 0) {
      iVar14 = iStack_54;
    }
    bVar17 = (uVar13 & 0x1000) == 0;
    bVar18 = (uVar13 & 0x800) == 0;
    iVar6 = iStack_48;
    if (bVar17) {
      iVar6 = 0;
    }
    iVar5 = iStack_48;
    if (bVar18) {
      iVar5 = 0;
    }
    iVar6 = iVar14 + iVar5 + iVar6;
    param_4 = param_4 - iVar6;
    if ((int)param_4 < 0) {
      return;
    }
    uVar10 = uVar13 & 0xf00;
    puVar11 = (ushort *)((int)puVar15 + iVar14);
    param_3 = (ushort *)((int)puVar15 + iVar6);
    puVar12 = puVar11;
    uVar13 = (ushort)DAT_02396264;
    if (bVar18) {
LAB_023961d4:
      if (((bVar17) || (((uint)*puVar12 & 1 << (*(ushort *)(iVar4 + 0x184) & 0xff)) != 0)) &&
         (iVar14 != 0)) {
        puVar9 = (undefined2 *)func_0x033b7438();
        *puVar9 = 0x82;
        puVar9[1] = 0;
        puVar9[2] = 0x15;
        puVar9[3] = (short)(uVar10 >> 8);
        *(undefined4 *)(puVar9 + 4) = param_5;
        *(ushort **)(puVar9 + 6) = puVar15;
        puVar9[8] = (short)iVar14;
        puVar9[9] = (short)param_1;
        puVar9[0x10] = *(undefined2 *)(iVar4 + 0x184);
        puVar9[0xd] = uVar13;
        func_0x033b74e0();
      }
    }
    else {
      uVar7 = (uVar10 << 8) >> 0x10 & 7;
      puVar8 = (ushort *)(iVar16 + uVar7 * 2);
      uVar1 = *(ushort *)(iVar16 + uVar7 * 2);
      puVar12 = puVar11 + 1;
      uVar2 = *puVar11;
      if ((uVar1 & 1) != 0) {
        *puVar8 = uVar2 << 1;
        uVar13 = uVar2;
        goto LAB_023961d4;
      }
      uVar13 = uVar2 * 2;
      if (0xff < (ushort)(uVar1 + uVar2 * -2)) {
        *puVar8 = uVar13;
        goto LAB_023961d4;
      }
    }
    if ((int)param_4 < 1) {
      return;
    }
  } while( true );
}



void FUN_02396268(ushort param_1)

{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  ushort *puVar7;
  undefined2 *puVar8;
  ushort *puVar9;
  ushort *puVar10;
  uint uVar11;
  int iVar12;
  int local_48;
  int local_44;
  
  iVar6 = FUN_023901d8();
  iVar12 = **(int **)(iVar6 + 0x1518);
  iVar6 = iVar12 + 0x2f4;
  uVar2 = ~param_1 & *(ushort *)(iVar12 + 0x17e);
  func_0x033ac344(iVar12 + DAT_02396440);
  uVar5 = DAT_02396448;
  local_48 = 0;
  puVar7 = (ushort *)(iVar12 + DAT_02396444);
  do {
    local_44 = 0;
    puVar9 = puVar7;
    do {
      uVar1 = *puVar9;
      puVar3 = puVar9;
      uVar4 = uVar5;
      while (uVar11 = (uint)uVar1, uVar11 != uVar5) {
        puVar10 = (ushort *)(iVar6 + uVar11 * 0x20);
        puVar10[3] = puVar10[3] & uVar2;
        puVar10[5] = puVar10[5] & uVar2;
        if (puVar10[3] == 0) {
          puVar8 = (undefined2 *)func_0x033b7438();
          *puVar8 = 0x81;
          puVar8[1] = 0;
          puVar8[4] = 0x14;
          puVar8[5] = puVar10[1];
          puVar8[6] = puVar10[2];
          puVar8[7] = puVar10[3];
          puVar8[8] = puVar10[4];
          puVar8[0xc] = puVar10[7];
          *(undefined4 *)(puVar8 + 10) = *(undefined4 *)(puVar10 + 10);
          *(undefined4 *)(puVar8 + 0xe) = *(undefined4 *)(puVar10 + 0xc);
          *(undefined4 *)(puVar8 + 0x10) = *(undefined4 *)(puVar10 + 0xe);
          puVar8[0xd] = puVar10[8];
          func_0x033b74e0();
          if (*puVar10 == uVar5) {
            puVar9[1] = (ushort)uVar4;
          }
          *puVar3 = *puVar10;
          *puVar10 = (ushort)uVar5;
          if (*(ushort *)(iVar12 + 0x6f6) == uVar5) {
            *(ushort *)(iVar12 + 0x6f4) = uVar1;
          }
          else {
            *(ushort *)(iVar6 + (uint)*(ushort *)(iVar12 + 0x6f6) * 0x20) = uVar1;
          }
          *(ushort *)(iVar12 + 0x6f6) = uVar1;
          uVar11 = uVar4;
        }
        uVar4 = uVar11;
        if (uVar11 == uVar5) {
          uVar1 = *puVar9;
          puVar3 = puVar9;
        }
        else {
          uVar1 = *(ushort *)(iVar6 + uVar11 * 0x20);
          puVar3 = (ushort *)(iVar6 + uVar11 * 0x20);
        }
      }
      puVar9 = puVar9 + 2;
      local_44 = local_44 + 1;
    } while (local_44 < 4);
    local_48 = local_48 + 1;
  } while (local_48 < 2);
  func_0x033ac2d4(iVar12 + DAT_02396440);
  return;
}



undefined4 FUN_0239644c(int param_1,ushort param_2)

{
  ushort uVar1;
  ushort uVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined2 *puVar8;
  uint uVar9;
  ushort *puVar10;
  ushort *puVar11;
  short *psVar12;
  ushort uVar13;
  int local_4c;
  undefined4 local_48;
  uint local_44;
  
  iVar7 = FUN_023901d8();
  psVar12 = **(short ***)(iVar7 + 0x1518);
  local_48 = 0;
  if (*psVar12 == 9) {
    bVar3 = true;
  }
  else {
    if (*psVar12 != 10) {
      return 0;
    }
    bVar3 = false;
  }
  func_0x033ac344((int)psVar12 + DAT_02396754);
  if (*(int *)(psVar12 + 0x396) != 0) {
    if (bVar3) {
      func_0x033ad8a0();
      uVar13 = psVar12[0xbf];
      func_0x033ad8b4();
    }
    else {
      uVar13 = 1;
    }
    uVar6 = DAT_0239675c;
    local_4c = 0;
    puVar11 = (ushort *)((int)psVar12 + DAT_02396758);
    do {
      uVar1 = *puVar11;
      uVar4 = uVar6;
      uVar5 = uVar6;
      while (uVar9 = (uint)uVar1, uVar9 != uVar6) {
        puVar10 = (ushort *)(psVar12 + uVar9 * 0x10 + 0x17a);
        if (param_1 == 0) {
          puVar10[4] = puVar10[4] | puVar10[5] & ~param_2;
          puVar10[3] = puVar10[3] & ~puVar10[4];
        }
        puVar10[3] = puVar10[3] & uVar13;
        puVar10[5] = 0;
        uVar2 = (ushort)uVar6;
        if ((puVar10[3] == 0) || (((puVar10[1] & 8) == 0 && (puVar10[9] == 0)))) {
          puVar8 = (undefined2 *)func_0x033b7438();
          *puVar8 = 0x81;
          if (puVar10[3] == 0) {
            puVar8[1] = 0;
          }
          else {
            puVar8[1] = 0xf;
          }
          puVar8[4] = 0x14;
          puVar8[5] = puVar10[1];
          puVar8[6] = puVar10[2];
          puVar8[7] = puVar10[3];
          puVar8[8] = puVar10[4];
          puVar8[0xc] = puVar10[7];
          *(undefined4 *)(puVar8 + 10) = *(undefined4 *)(puVar10 + 10);
          *(undefined4 *)(puVar8 + 0xe) = *(undefined4 *)(puVar10 + 0xc);
          *(undefined4 *)(puVar8 + 0x10) = *(undefined4 *)(puVar10 + 0xe);
          puVar8[0xd] = puVar10[8];
          func_0x033b74e0();
          if (*puVar10 == uVar6) {
            puVar11[1] = uVar2;
          }
          *puVar11 = *puVar10;
          *puVar10 = uVar2;
          if ((ushort)psVar12[0x37b] == uVar6) {
            psVar12[0x37a] = uVar1;
          }
          else {
            psVar12[(uint)(ushort)psVar12[0x37b] * 0x10 + 0x17a] = uVar1;
          }
          psVar12[0x37b] = uVar1;
          uVar9 = uVar5;
          local_44 = uVar4;
        }
        else {
          local_48 = 1;
          if (puVar10[9] != 0) {
            puVar10[9] = puVar10[9] - 1;
          }
          if (*puVar10 == uVar6) {
            puVar11[1] = uVar2;
          }
          *puVar11 = *puVar10;
          *puVar10 = uVar2;
          local_44 = uVar9;
          if (uVar5 != uVar6) {
            psVar12[uVar5 * 0x10 + 0x17a] = uVar1;
            local_44 = uVar4;
          }
        }
        uVar4 = local_44;
        uVar5 = uVar9;
        uVar1 = *puVar11;
      }
      if (uVar5 != uVar6) {
        psVar12[uVar5 * 0x10 + 0x17a] = psVar12[local_4c * 2 + 900];
        if ((ushort)psVar12[local_4c * 2 + 0x385] == uVar6) {
          psVar12[local_4c * 2 + 0x385] = (short)uVar5;
        }
        psVar12[local_4c * 2 + 900] = (short)uVar4;
      }
      puVar11 = puVar11 + 2;
      local_4c = local_4c + 1;
    } while (local_4c < 4);
    *(undefined4 *)(psVar12 + 0x396) = 0;
    func_0x033ac2d4((int)psVar12 + DAT_02396754);
    return local_48;
  }
  func_0x033ac2d4((int)psVar12 + DAT_02396754);
  return 0;
}



// WARNING: Restarted to delay deadcode elimination for space: stack

short FUN_02396760(ushort param_1,int param_2,uint param_3,ushort param_4,undefined4 param_5,
                  short param_6)

{
  ushort uVar1;
  undefined2 uVar2;
  uint uVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined2 *puVar8;
  ushort *unaff_r4;
  ushort *puVar9;
  int unaff_r5;
  int unaff_r6;
  int iVar10;
  ushort unaff_r7;
  uint unaff_r8;
  ushort unaff_r9;
  undefined *puVar11;
  undefined auStack_20 [4];
  
  iVar5 = FUN_023901d8();
  iVar10 = **(int **)(iVar5 + 0x1518);
  puVar9 = (ushort *)(iVar10 + DAT_023968bc + param_2 * 4);
  iVar5 = iVar10 + 0x2f4;
  puVar11 = auStack_20;
  sVar4 = param_6;
  if (param_6 == 0) {
    sVar4 = 6;
    puVar9 = unaff_r4;
    iVar5 = unaff_r5;
    iVar10 = unaff_r6;
    param_3 = unaff_r8;
    puVar11 = (undefined *)register0x00000054;
    param_4 = unaff_r7;
    param_1 = unaff_r9;
  }
  if (param_6 == 0) {
    return sVar4;
  }
  if ((param_3 & 8) == 0) {
    iVar7 = 0;
  }
  else {
    iVar7 = 2;
  }
  if ((uint)*(ushort *)(puVar11 + 0x24) + iVar7 <= (uint)*(ushort *)(iVar10 + 0x18e)) {
    func_0x033ac344(iVar10 + DAT_023968c0);
    uVar3 = DAT_023968c4;
    uVar1 = *(ushort *)(iVar10 + 0x6f4);
    uVar6 = (uint)uVar1;
    if (uVar6 != DAT_023968c4) {
      puVar8 = (undefined2 *)(iVar5 + uVar6 * 0x20);
      *(undefined2 *)(iVar10 + 0x6f4) = *(undefined2 *)(iVar5 + uVar6 * 0x20);
      if (*(ushort *)(iVar10 + 0x6f6) == uVar6) {
        *(short *)(iVar10 + 0x6f6) = (short)uVar3;
      }
      puVar8[1] = (short)param_3;
      puVar8[2] = param_4;
      puVar8[3] = param_4 & param_1;
      puVar8[4] = 0;
      puVar8[5] = 0;
      *(undefined4 *)(puVar8 + 10) = *(undefined4 *)(puVar11 + 0x20);
      puVar8[7] = *(undefined2 *)(puVar11 + 0x24);
      *(undefined4 *)(puVar8 + 0xc) = *(undefined4 *)(puVar11 + 0x28);
      *(undefined4 *)(puVar8 + 0xe) = *(undefined4 *)(puVar11 + 0x2c);
      uVar3 = DAT_023968c4;
      uVar2 = (undefined2)DAT_023968c4;
      *puVar8 = uVar2;
      puVar8[8] = uVar2;
      puVar8[9] = *(undefined2 *)(iVar10 + 0x98);
      if (puVar9[1] == uVar3) {
        *puVar9 = uVar1;
      }
      else {
        *(ushort *)(iVar5 + (uint)puVar9[1] * 0x20) = uVar1;
      }
      puVar9[1] = uVar1;
      func_0x033ac2d4(iVar10 + DAT_023968c0);
      return 2;
    }
    func_0x033ac2d4(iVar10 + DAT_023968c0);
    return 10;
  }
  return 6;
}



// WARNING: Restarted to delay deadcode elimination for space: stack

undefined4
FUN_023968c8(uint param_1,uint param_2,uint param_3,int param_4,ushort *param_5,ushort *param_6,
            uint *param_7,int *param_8)

{
  uint uVar1;
  short sVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  int iVar7;
  short *psVar8;
  int iVar9;
  short *psVar10;
  int iVar11;
  uint uVar12;
  undefined2 *puVar13;
  ushort uVar14;
  int iVar15;
  uint uVar16;
  ushort *puVar17;
  ushort *puVar18;
  ushort *puVar19;
  undefined2 *puVar20;
  ushort *puVar21;
  bool bVar22;
  uint uStack_7c;
  uint uStack_70;
  uint uStack_68;
  uint uStack_60;
  short *psStack_5c;
  ushort *puStack_58;
  undefined2 *puStack_54;
  int iStack_3c;
  int iStack_34;
  
  iVar7 = FUN_023901d8();
  psVar8 = **(short ***)(iVar7 + 0x1518);
  if (0xf < (ushort)psVar8[0xc2]) {
    return 1;
  }
  if (*psVar8 == 9) {
    bVar4 = true;
  }
  else {
    if (*psVar8 != 10) {
      return 1;
    }
    bVar4 = false;
  }
  uStack_70 = 0;
  *param_5 = 0;
  *param_7 = 0;
  iVar7 = 0;
  *param_8 = 0;
  if (param_4 < 0) {
    return 1;
  }
  uStack_68 = param_3;
  if (bVar4) {
    if (psVar8[0x49] != 0) {
      uStack_68 = param_2;
    }
    bVar3 = psVar8[0x49] == 0;
  }
  else {
    bVar3 = false;
  }
  uStack_7c = 0;
  bVar5 = true;
  func_0x033ac344((int)psVar8 + DAT_02396ddc);
  if (*(int *)(psVar8 + 0x396) == 1) {
    func_0x033ac2d4((int)psVar8 + DAT_02396ddc);
    return 1;
  }
  *(undefined4 *)(psVar8 + 0x396) = 1;
  uStack_60 = 0;
  puVar21 = (ushort *)((int)psVar8 + DAT_02396de0);
  psStack_5c = (short *)((int)psVar8 + DAT_02396de4);
  iStack_3c = 2;
  iStack_34 = 0;
  while ((uStack_60 < 4 && (2 < param_4))) {
    puStack_54 = DAT_02396de8;
    puVar20 = (undefined2 *)(uint)*puVar21;
    puStack_58 = puVar21;
    while ((puVar20 != DAT_02396de8 && (2 < param_4))) {
      puVar17 = (ushort *)(psVar8 + (int)puVar20 * 0x10 + 0x17a);
      uVar1 = 1 << (puVar17[1] & 0xff);
      if ((uStack_7c & uVar1) == 0) {
        uStack_7c = uStack_7c | uVar1;
        uVar16 = puVar17[3] & uStack_68;
        if ((!bVar3) || ((uVar16 & ~(param_3 & param_1)) == 0)) {
          bVar22 = (puVar17[1] & 8) != 0;
          if ((bVar4) && ((undefined2 *)(uVar16 | 1) != DAT_02396de8)) {
            bVar6 = true;
          }
          else {
            bVar6 = false;
          }
          if ((puVar17[7] & 1) == 1) {
            puVar17[7] = puVar17[7] + 1;
          }
          iVar9 = iStack_3c;
          if (!bVar22) {
            iVar9 = 0;
          }
          iVar15 = iStack_34;
          if (!bVar5) {
            iVar15 = 2;
          }
          iVar11 = iStack_3c;
          if (!bVar6) {
            iVar11 = 0;
          }
          if ((int)(iVar11 + (uint)puVar17[7] + iVar15 + iVar9) <= param_4) {
            puVar18 = param_6;
            if (!bVar5) {
              puVar18 = param_6 + 1;
              *param_6 = 0;
              iVar7 = iVar7 + 2;
              param_4 = param_4 + -2;
              param_5 = param_6;
            }
            *param_5 = *param_5 | (puVar17[1] & 0xf) << 8 | puVar17[7] >> 1 & 0xff;
            func_0x033adb60(*(undefined4 *)(puVar17 + 10),puVar18);
            uVar12 = (uint)puVar17[7];
            puVar18 = (ushort *)((int)puVar18 + (uVar12 & 0xfffffffe));
            iVar7 = iVar7 + uVar12;
            param_4 = param_4 - uVar12;
            puVar19 = puVar18;
            if (bVar22) {
              if ((puVar17[8] & 1) == 0) {
                uVar14 = (ushort)((int)(uint)puVar17[8] >> 1);
              }
              else {
                uVar14 = psVar8[(uint)(ushort)psVar8[0xc2] * 8 + (puVar17[1] & 7) + 0xfa];
                psVar8[(uint)(ushort)psVar8[0xc2] * 8 + (puVar17[1] & 7) + 0xfa] = uVar14 + 1;
                puVar17[8] = uVar14 << 1;
              }
              puVar19 = puVar18 + 1;
              *puVar18 = uVar14 & (ushort)DAT_02396dec;
              iVar7 = iVar7 + 2;
              param_4 = param_4 + -2;
            }
            param_6 = puVar19;
            if (bVar6) {
              *param_5 = *param_5 | 0x1000;
              param_6 = puVar19 + 1;
              *puVar19 = (ushort)uVar16;
              iVar7 = iVar7 + 2;
              param_4 = param_4 + -2;
            }
            if (bVar5) {
              bVar5 = false;
            }
            if ((undefined2 *)(uint)puVar21[1] == puVar20) {
              puVar21[1] = (ushort)puStack_54;
            }
            *puStack_58 = *puVar17;
            *puVar17 = (ushort)DAT_02396de8;
            puVar13 = (undefined2 *)(uint)(ushort)psStack_5c[1];
            psVar10 = DAT_02396de8;
            if (puVar13 == DAT_02396de8) {
              psVar10 = psStack_5c;
            }
            sVar2 = (short)puVar20;
            if (puVar13 == DAT_02396de8) {
              *psVar10 = sVar2;
            }
            else {
              psVar8[(int)puVar13 * 0x10 + 0x17a] = sVar2;
            }
            psStack_5c[1] = sVar2;
            puVar17[5] = (ushort)uVar16;
            uStack_7c = uStack_7c & ~uVar1;
            uStack_70 = uStack_70 | puVar17[2];
            puVar20 = puStack_54;
            if (psVar8[0x4a] == 1) goto LAB_02396da8;
          }
        }
      }
      puStack_54 = puVar20;
      if (puVar20 == DAT_02396de8) {
        puVar20 = (undefined2 *)(uint)*puVar21;
        puStack_58 = puVar21;
      }
      else {
        puVar20 = (undefined2 *)(uint)(ushort)psVar8[(int)puVar20 * 0x10 + 0x17a];
        puStack_58 = (ushort *)(psVar8 + (int)puVar20 * 0x10 + 0x17a);
      }
    }
    puVar21 = puVar21 + 2;
    psStack_5c = psStack_5c + 2;
    uStack_60 = uStack_60 + 1;
  }
LAB_02396da8:
  *param_7 = uStack_70;
  *param_8 = iVar7;
  func_0x033ac2d4((int)psVar8 + DAT_02396ddc);
  return 0;
}



void FUN_02396df0(uint param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  ushort uVar5;
  uint uVar6;
  undefined2 auStack_218 [258];
  
  iVar3 = FUN_023901d8();
  iVar3 = **(int **)(iVar3 + 0x1518);
  func_0x033ad8a0();
  func_0x033ad8b4();
  uVar1 = *DAT_02396e9c;
  uVar5 = *(ushort *)(iVar3 + 0x3e);
  uVar6 = param_1 & *(ushort *)(iVar3 + 0x17e);
  if (*(short *)(iVar3 + 0x36) == 1) {
    uVar4 = FUN_02395f5c((uint)*(ushort *)(iVar3 + 0x42),(uint)*(ushort *)(iVar3 + 0x40),uVar6);
    uVar2 = (undefined2)uVar4;
    uVar5 = uVar5 | 0x8000;
  }
  else {
    uVar2 = 0;
    uVar5 = uVar5 & 0x7fff;
  }
  FUN_02391f0c(auStack_218,(short)DAT_02396ea0,0,0,(short)uVar6,uVar2,uVar1,0,uVar5,0);
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_02396ea4(uint param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  ushort *puVar7;
  ushort local_228 [2];
  uint uStack_224;
  int local_220;
  undefined2 auStack_21c [258];
  
  iVar3 = FUN_023901d8();
  iVar3 = **(int **)(iVar3 + 0x1518);
  func_0x033ad8a0();
  uVar6 = (uint)*(ushort *)(iVar3 + 0x17e);
  uVar1 = *(ushort *)(iVar3 + 0x86);
  func_0x033ad8b4();
  uVar5 = DAT_0239702c;
  puVar7 = *(ushort **)(iVar3 + 0x50);
  local_228[0] = 0;
  if (*(short *)(iVar3 + 0x88) == 1) {
    *(undefined2 *)(iVar3 + 0x88) = 0;
    param_1 = uVar5;
  }
  if (*(short *)(iVar3 + 0x9a) == 0) {
    iVar4 = FUN_023968c8(param_1,uVar6,(uint)uVar1,(uint)*(ushort *)(iVar3 + 0x18e),local_228,puVar7
                         ,&uStack_224,&local_220);
    if (iVar4 == 1) {
      return;
    }
    iVar4 = *(ushort *)(iVar3 + 400) + 2;
    if (*(short *)(iVar3 + 0x92) == 1) {
      param_1 = uStack_224;
    }
    uVar6 = param_1 & uVar6;
    if (*(short *)(iVar3 + 0x36) == 1) {
      uVar5 = FUN_02395f5c(local_220,iVar4,uVar6);
      uVar2 = (undefined2)uVar5;
      local_228[0] = local_228[0] | 0x8000;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    iVar4 = 0;
    *(undefined2 *)(iVar3 + 0x9a) = 0;
    uVar2 = 0;
    local_220 = 0;
    local_228[0] = 0;
    *(short *)(iVar3 + 0x36) = *(short *)(iVar3 + 0x36) + 1;
  }
  FUN_02391f0c(auStack_21c,0,0,(short)iVar4,(short)uVar6,uVar2,*DAT_02397030,(short)local_220,
               local_228[0],puVar7);
  *(short *)(iVar3 + 0x3c) = (short)uVar6;
  *(ushort *)(iVar3 + 0x3e) = local_228[0];
  *(short *)(iVar3 + 0x40) = (short)iVar4;
  *(short *)(iVar3 + 0x42) = (short)local_220;
  return;
}



// WARNING: Restarted to delay deadcode elimination for space: stack

void FUN_02397034(void)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  ushort *puVar4;
  ushort auStack_218 [2];
  uint uStack_214;
  undefined2 uStack_210;
  undefined2 auStack_20c [256];
  
  iVar1 = FUN_023901d8();
  iVar1 = **(int **)(iVar1 + 0x1518);
  if (*(short *)(iVar1 + 0x17e) == 0) {
    return;
  }
  puVar4 = *(ushort **)(iVar1 + 0x50);
  auStack_218[0] = 0;
  iVar2 = FUN_023968c8(1,1,1,(uint)*(ushort *)(iVar1 + 0x18e),auStack_218,puVar4,&uStack_214,
                       (int *)&uStack_210);
  if (iVar2 == 1) {
    return;
  }
  if (*(int *)(iVar1 + 0x1c) == 1) {
    auStack_218[0] = auStack_218[0] | 0x8000;
  }
  puVar3 = FUN_02391fa8(auStack_20c,uStack_210,auStack_218[0],puVar4);
  if (puVar3[2] == 0) {
    *(undefined2 *)(iVar1 + 0x8a) = 1;
  }
  return;
}



void FUN_023970fc(void)

{
  uint uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  iVar4 = FUN_023901d8();
  iVar4 = **(int **)(iVar4 + 0x1518);
  func_0x033ac344(iVar4 + DAT_023971c8);
  func_0x033adb48(0,iVar4 + 0x2f4,0x400);
  uVar6 = 0;
  do {
    uVar1 = uVar6 + 1 & 0xffff;
    uVar2 = (undefined2)((uVar6 + 1) * 0x10000 >> 0x10);
    *(undefined2 *)(iVar4 + uVar6 * 0x20 + 0x2f4) = uVar2;
    uVar6 = uVar1;
  } while (uVar1 < 0x1f);
  uVar3 = (undefined2)DAT_023971cc;
  *(undefined2 *)(iVar4 + uVar1 * 0x20 + 0x2f4) = uVar3;
  uVar6 = 0;
  *(undefined2 *)(iVar4 + 0x6f4) = 0;
  *(undefined2 *)(iVar4 + 0x6f6) = uVar2;
  do {
    iVar5 = iVar4 + uVar6 * 4;
    *(undefined2 *)(iVar5 + 0x708) = uVar3;
    *(undefined2 *)(iVar5 + 0x70a) = uVar3;
    *(undefined2 *)(iVar5 + 0x6f8) = uVar3;
    *(undefined2 *)(iVar5 + 0x6fa) = uVar3;
    uVar6 = uVar6 + 1 & 0xffff;
  } while (uVar6 < 4);
  func_0x033ac2d4(iVar4 + DAT_023971c8);
  return;
}



void FUN_023971d0(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  undefined2 auStack_290 [256];
  undefined2 auStack_90 [66];
  
  iVar1 = FUN_023901d8();
  iVar1 = **(int **)(iVar1 + 0x1518);
  *(short *)(iVar1 + 0xf2) = (short)*(undefined4 *)(param_1 + 4);
  FUN_0238ffc4(auStack_90,(undefined4 *)(iVar1 + 0xe4));
  puVar2 = FUN_02391b74(auStack_290,*(ushort *)(iVar1 + 0xe8) + 0x10 & 0xffff,auStack_90);
  puVar3 = (undefined2 *)func_0x033b7438();
  *puVar3 = 0x21;
  if (puVar2[2] == 0) {
    puVar3[1] = 0;
  }
  else {
    puVar3[1] = 1;
    puVar3[2] = (short)DAT_02397268;
    puVar3[3] = puVar2[2];
  }
  func_0x033b74e0();
  return;
}



void FUN_0239726c(int param_1)

{
  short sVar1;
  undefined2 *puVar2;
  undefined2 *unaff_r4;
  int iVar3;
  undefined auStack_220 [8];
  undefined2 auStack_218 [256];
  
  func_0x033adc88(param_1 + 4,auStack_220,6);
  for (iVar3 = 0; iVar3 < 2; iVar3 = iVar3 + 1) {
    unaff_r4 = FUN_023922ac(auStack_218,auStack_220,0x13);
    sVar1 = unaff_r4[2];
    if ((sVar1 == 0) || ((sVar1 != 7 && (sVar1 != 0xc)))) break;
  }
  puVar2 = (undefined2 *)func_0x033b7438();
  *puVar2 = 0x22;
  if (unaff_r4[2] == 0) {
    puVar2[1] = 0;
  }
  else {
    puVar2[1] = 1;
    puVar2[2] = 5;
    puVar2[3] = unaff_r4[2];
  }
  func_0x033b74e0();
  return;
}



void FUN_0239731c(void)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  bool bVar4;
  
  iVar1 = FUN_023901d8();
  piVar3 = *(int **)(iVar1 + 0x1518);
  uVar2 = func_0x033ad8a0();
  bVar4 = *(int *)(*piVar3 + 0xc) == 1;
  if (bVar4) {
    *(undefined4 *)(*piVar3 + 0xc) = 0;
    func_0x033ad4f0(piVar3 + 0x34);
    FUN_0238fcfc();
  }
  *(undefined2 *)(*piVar3 + 0x17e) = 0;
  *(undefined2 *)(*piVar3 + 0x86) = 0;
  *(undefined4 *)(*piVar3 + 0x14) = 0;
  *(undefined4 *)(*piVar3 + 0x10) = 0;
  *(undefined4 *)(*piVar3 + 0x1c) = 0;
  *(undefined2 *)(*piVar3 + 0x92) = 0;
  *(undefined2 *)(*piVar3 + 0x94) = 0;
  *(undefined2 *)(*piVar3 + 0x96) = 0;
  *(undefined2 *)(*piVar3 + 0x18e) = 0;
  *(undefined2 *)(*piVar3 + 400) = 0;
  *(undefined2 *)(*piVar3 + 0xca) = 0;
  *(undefined2 *)(*piVar3 + 0xbe) = 0;
  *(undefined2 *)(*piVar3 + 0xc2) = 0;
  *(undefined2 *)(*piVar3 + 0x1ea) = 1;
  func_0x033ad8b4(uVar2);
  if (bVar4) {
    FUN_02396268((ushort)DAT_02397468);
  }
  iVar1 = 0;
  do {
    piVar3[iVar1 * 4 + 0x3e] = 0x8000;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x20);
  func_0x033adb48(1,*piVar3 + 500,0x100);
  func_0x033ad144(*piVar3 + 0x58);
  func_0x033ac3d0(*piVar3 + DAT_0239746c);
  FUN_02395d24();
  return;
}



void FUN_02397470(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  undefined4 *puVar3;
  
  iVar1 = FUN_023901d8();
  *(undefined4 *)(iVar1 + 0x1518) = *(undefined4 *)(param_1 + 4);
  puVar3 = *(undefined4 **)(iVar1 + 0x1518);
  *puVar3 = *(undefined4 *)(param_1 + 8);
  puVar3[2] = *(undefined4 *)(param_1 + 0xc);
  FUN_0239731c();
  func_0x033b54a0(0xf);
  *(undefined2 *)*puVar3 = 1;
  puVar2 = (undefined2 *)func_0x033b7438();
  *puVar2 = 3;
  puVar2[1] = 0;
  func_0x033b74e0();
  return;
}



void FUN_023974dc(void)

{
  int iVar1;
  undefined2 *puVar2;
  short **ppsVar3;
  
  iVar1 = FUN_023901d8();
  ppsVar3 = *(short ***)(iVar1 + 0x1518);
  if (**ppsVar3 == 1) {
    func_0x033b54a0(1);
    **ppsVar3 = 0;
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 4;
    puVar2[1] = 0;
    func_0x033b74e0();
  }
  else {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 4;
    puVar2[1] = 3;
    func_0x033b74e0();
  }
  return;
}



void FUN_0239754c(void)

{
  *DAT_02397574 = 200;
  *DAT_02397578 = 2000;
  *DAT_02397580 = (short)DAT_0239757c;
  return;
}



undefined4 FUN_02397584(undefined2 *param_1,undefined2 *param_2)

{
  ushort uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 *puVar5;
  int *piVar6;
  undefined2 auStack_218 [258];
  
  iVar3 = FUN_023901d8();
  piVar6 = *(int **)(iVar3 + 0x1518);
  iVar3 = FUN_02391ad4(auStack_218);
  if (*(short *)(iVar3 + 4) == 0) {
    iVar3 = FUN_02391b00(auStack_218);
    if (*(short *)(iVar3 + 4) == 0) {
      FUN_0239754c();
      iVar3 = FUN_02391b44(auStack_218);
      if (*(short *)(iVar3 + 4) == 0) {
        uVar1 = *(ushort *)(iVar3 + 6);
        *(ushort *)(*piVar6 + 0x1f0) = uVar1;
        uVar2 = func_0x033b730c(((uint)uVar1 << 0xf) >> 0x10);
        *(undefined2 *)(*piVar6 + 0x1f2) = uVar2;
        FUN_02391d28(auStack_218,(short)DAT_02397790,0x28,5);
        iVar3 = *piVar6;
        *(undefined4 *)(iVar3 + 0x7b0) = DAT_02397794;
        *(undefined4 *)(iVar3 + 0x7b4) = 0;
        *(undefined2 *)(*piVar6 + 0x1e8) = 2;
        *(undefined2 *)(*piVar6 + 0x1ea) = 1;
        iVar3 = FUN_02391aa4(auStack_218);
        if (*(short *)(iVar3 + 4) == 0) {
          func_0x033adb60(iVar3 + 6,*piVar6 + 0x20,8);
          *(undefined2 *)(*piVar6 + 0x28) = *(undefined2 *)(iVar3 + 0xe);
          *(undefined2 *)(*piVar6 + 0x2c) = *(undefined2 *)(iVar3 + 0x10);
          *(undefined2 *)(*piVar6 + 0x2e) = *(undefined2 *)(iVar3 + 0x12);
          *(undefined2 *)(*piVar6 + 0x2a) = *(undefined2 *)(iVar3 + 0x14);
          iVar3 = FUN_02391b5c(auStack_218);
          if (*(short *)(iVar3 + 4) == 0) {
            func_0x033adc88(iVar3 + 6,*piVar6 + 0xdc,6);
            puVar5 = FUN_02391c68(auStack_218,1);
            if (puVar5[2] == 0) {
              uVar4 = 1;
            }
            else {
              *param_1 = (short)DAT_023977a0;
              *param_2 = puVar5[2];
              uVar4 = 0;
            }
          }
          else {
            *param_1 = (short)DAT_0239779c;
            *param_2 = *(undefined2 *)(iVar3 + 4);
            uVar4 = 0;
          }
        }
        else {
          *param_1 = (short)DAT_02397798;
          *param_2 = *(undefined2 *)(iVar3 + 4);
          uVar4 = 0;
        }
      }
      else {
        *param_1 = (short)DAT_0239778c;
        *param_2 = *(undefined2 *)(iVar3 + 4);
        uVar4 = 0;
      }
    }
    else {
      *param_1 = (short)DAT_02397788;
      *param_2 = *(undefined2 *)(iVar3 + 4);
      uVar4 = 0;
    }
  }
  else {
    *param_1 = 0x304;
    *param_2 = *(undefined2 *)(iVar3 + 4);
    uVar4 = 0;
  }
  return uVar4;
}



void FUN_023977a4(void)

{
  int iVar1;
  undefined2 *puVar2;
  short **ppsVar3;
  undefined2 local_10;
  undefined2 local_e [3];
  
  iVar1 = FUN_023901d8();
  ppsVar3 = *(short ***)(iVar1 + 0x1518);
  if (**ppsVar3 == 1) {
    iVar1 = FUN_02397584(&local_10,local_e);
    if (iVar1 == 0) {
      puVar2 = (undefined2 *)func_0x033b7438();
      *puVar2 = 5;
      puVar2[1] = 1;
      puVar2[2] = local_10;
      puVar2[3] = local_e[0];
      func_0x033b74e0();
    }
    else {
      **ppsVar3 = 2;
      puVar2 = (undefined2 *)func_0x033b7438();
      *puVar2 = 5;
      puVar2[1] = 0;
      func_0x033b74e0();
    }
  }
  else {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 5;
    puVar2[1] = 3;
    func_0x033b74e0();
  }
  return;
}



void FUN_02397854(void)

{
  int iVar1;
  undefined2 *puVar2;
  short **ppsVar3;
  undefined auStack_210 [516];
  
  iVar1 = FUN_023901d8();
  ppsVar3 = *(short ***)(iVar1 + 0x1518);
  if (**ppsVar3 == 2) {
    iVar1 = FUN_02391b18(auStack_210);
    if (*(short *)(iVar1 + 4) == 0) {
      **ppsVar3 = 1;
      puVar2 = (undefined2 *)func_0x033b7438();
      *puVar2 = 6;
      puVar2[1] = 0;
      func_0x033b74e0();
    }
    else {
      puVar2 = (undefined2 *)func_0x033b7438();
      *puVar2 = 6;
      puVar2[1] = 1;
      puVar2[2] = (short)DAT_02397908;
      puVar2[3] = *(undefined2 *)(iVar1 + 4);
      func_0x033b74e0();
    }
  }
  else {
    puVar2 = (undefined2 *)func_0x033b7438();
    *puVar2 = 6;
    puVar2[1] = 3;
    func_0x033b74e0();
  }
  return;
}



void FUN_0239790c(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  uint uVar3;
  
  iVar1 = FUN_023901d8();
  iVar1 = **(int **)(iVar1 + 0x1518);
  uVar3 = *(uint *)(param_1 + 4) & 0xffff;
  if (uVar3 == 0) {
    uVar3 = 0x10;
  }
  func_0x033ad8a0();
  *(short *)(iVar1 + 0x34) = (short)uVar3;
  if (uVar3 < *(ushort *)(iVar1 + 0x36)) {
    *(short *)(iVar1 + 0x36) = (short)uVar3;
  }
  func_0x033ad8b4();
  puVar2 = (undefined2 *)func_0x033b7438();
  *puVar2 = 0x23;
  puVar2[1] = 0;
  func_0x033b74e0();
  return;
}



void FUN_02397974(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)func_0x033b7438();
  *puVar1 = 0x24;
  puVar1[1] = 1;
  puVar1[2] = param_1;
  puVar1[3] = param_2;
  func_0x033b74e0();
  return;
}



void FUN_023979b0(int param_1)

{
  undefined2 *puVar1;
  undefined2 auStack_208 [256];
  
  FUN_023901d8();
  puVar1 = FUN_02391c08(auStack_208,(short)*(undefined4 *)(param_1 + 4));
  if (puVar1[2] == 0) {
    puVar1 = (undefined2 *)func_0x033b7438();
    *puVar1 = 0x24;
    puVar1[1] = 0;
    func_0x033b74e0();
  }
  else {
    FUN_02397974((short)DAT_02397a10,puVar1[2]);
  }
  return;
}



int FUN_02397a28(void)

{
  return *DAT_02397a38 + 0x18;
}



undefined2 FUN_02397a3c(int *param_1)

{
  int *piVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uStack_10;
  undefined4 local_c;
  
  iVar4 = *param_1;
  *DAT_02397c0c = iVar4;
  local_c = 0;
  func_0x033adba8(0,iVar4,0x640);
  uVar3 = func_0x033ab52c();
  piVar1 = DAT_02397c0c;
  *(undefined4 *)(*DAT_02397c0c + 0x2e8) = uVar3;
  *(int *)(*piVar1 + 0x2e0) = param_1[6];
  *(uint *)(*piVar1 + 0x2e4) = (uint)param_1[7] >> 1;
  if (*(int *)(*piVar1 + 0x2e4) == 0) {
    *(undefined4 *)(*piVar1 + 0x2e4) = 0xffffffff;
  }
  FUN_02397db4(param_1 + 8);
  FUN_023a43d8();
  *(ushort *)PTR_REG_POWCNT2_02397c10 = *(ushort *)PTR_REG_POWCNT2_02397c10 | 2;
  *(undefined2 *)PTR_REG_WIFIWAITCNT_02397c14 = 0x30;
  piVar1 = DAT_02397c0c;
  *(undefined4 *)(*DAT_02397c0c + 0x638) = 3;
  FUN_023a451c(0x3c,2,(ushort *)(*piVar1 + DAT_02397c18));
  FUN_023a451c(0x3e,2,(ushort *)(*DAT_02397c0c + DAT_02397c1c));
  piVar1 = DAT_02397c0c;
  *(int *)(*DAT_02397c0c + 0x2dc) = param_1[4];
  *(int *)(*piVar1 + 0x2d8) = param_1[5];
  uVar2 = func_0x033b6d70(param_1[0xc],0x1c);
  FUN_0239a308(param_1[0xb],uVar2);
  FUN_02397c78();
  FUN_0239b9ac();
  FUN_0239ba38();
  FUN_0239ac78();
  FUN_02398760();
  iVar4 = FUN_023a45bc(&uStack_10);
  if (iVar4 == 0) {
    FUN_023989d0();
    FUN_0239a81c();
    FUN_0239930c();
    FUN_02398998();
    FUN_023987ac();
    FUN_0239a698();
    FUN_0239a3a0();
    FUN_02398934();
    FUN_02399840();
    FUN_023993a0();
  }
  else {
    *(ushort *)(*DAT_02397c0c + 0x312) = *(ushort *)(*DAT_02397c0c + 0x312) | 0x80;
  }
  func_0x033abc80(*DAT_02397c0c + 0x18,DAT_02397c20,0,param_1[1],param_1[2],param_1[3]);
  func_0x033abb18(*DAT_02397c0c + 0x18);
  FUN_0239a9f0();
  return *(undefined2 *)(*DAT_02397c0c + 0x312);
}



void FUN_02397c24(void)

{
  FUN_02398518();
  FUN_023993a0();
  FUN_02398998();
  FUN_02397d58();
  FUN_02397c78();
  FUN_0239a308(*(undefined4 *)(*DAT_02397c74 + 0x2f0),*(undefined2 *)(*DAT_02397c74 + 0x2f4));
  FUN_0239b9ac();
  FUN_0239ba38();
  FUN_0239ac78();
  FUN_02399840();
  return;
}



void FUN_02397c78(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = *DAT_02397cf8;
  uVar4 = 0;
  *(undefined2 *)(iVar6 + 0x10) = 0;
  *(undefined2 *)(iVar6 + 0x12) = 0;
  uVar1 = DAT_02397cfc;
  do {
    iVar3 = iVar6 + uVar4 * 2;
    *(short *)(iVar3 + 8) = (short)uVar1;
    *(undefined2 *)(iVar6 + uVar4 * 2) = *(undefined2 *)(iVar3 + 8);
    iVar3 = DAT_02397d00;
    uVar2 = DAT_02397cfc;
    uVar4 = uVar4 + 1;
  } while (uVar4 < 4);
  uVar4 = 0;
  do {
    iVar5 = iVar6 + uVar4 * 8;
    *(short *)(iVar5 + 0x90) = (short)uVar2;
    *(undefined2 *)(iVar5 + 0x92) = 0;
    *(undefined4 *)(iVar5 + 0x94) = *(undefined4 *)(iVar3 + uVar4 * 4);
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x18);
  func_0x033a81e8(3,0xc);
  return;
}



void FUN_02397d04(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *param_1;
  if (*(short *)(param_1 + 2) != 0) {
    while (iVar2 != -1) {
      iVar1 = func_0x033a8734(iVar2);
      func_0x033a85a8(param_1,iVar2);
      iVar2 = iVar1;
    }
  }
  return;
}



void FUN_02397d58(void)

{
  int iVar1;
  
  iVar1 = *DAT_02397db0;
  FUN_02397d04((int *)(iVar1 + 0x168));
  FUN_02397d04((int *)(iVar1 + 0x174));
  FUN_02397d04((int *)(iVar1 + 0x180));
  FUN_02397d04((int *)(iVar1 + 0x18c));
  FUN_02397d04((int *)(iVar1 + 0x198));
  FUN_02397d04((int *)(iVar1 + 0x1a4));
  FUN_02397d04((int *)(iVar1 + 0x1b0));
  FUN_02397d04((int *)(iVar1 + 0x1bc));
  return;
}



void FUN_02397db4(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *DAT_02397e94;
  *(undefined4 *)(iVar2 + 0x150) = *param_1;
  *(undefined4 *)(iVar2 + 0x154) = param_1[1];
  *(undefined4 *)(iVar2 + 0x158) = param_1[2];
  FUN_02397e98((undefined4 *)(iVar2 + 0x15c),2);
  FUN_02397e98((undefined4 *)(iVar2 + 0x168),3);
  FUN_02397e98((undefined4 *)(iVar2 + 0x174),4);
  FUN_02397e98((undefined4 *)(iVar2 + 0x180),5);
  FUN_02397e98((undefined4 *)(iVar2 + 0x18c),6);
  FUN_02397e98((undefined4 *)(iVar2 + 0x198),7);
  FUN_02397e98((undefined4 *)(iVar2 + 0x1a4),8);
  FUN_02397e98((undefined4 *)(iVar2 + 0x1b0),9);
  FUN_02397e98((undefined4 *)(iVar2 + 0x1bc),10);
  FUN_02397e98((undefined4 *)(iVar2 + 0x1c8),0xb);
  FUN_02397e98((undefined4 *)(iVar2 + 0x1d4),0xc);
  iVar1 = func_0x033a8500(iVar2 + 0x15c,0x81);
  *(int *)(iVar2 + 0x3b4) = iVar1 + 0xc;
  *(undefined2 *)(iVar2 + 0x3b8) = 0;
  *(undefined2 *)(iVar2 + 0x3bc) = 0;
  return;
}



void FUN_02397e98(undefined4 *param_1,undefined2 param_2)

{
  *param_1 = 0xffffffff;
  param_1[1] = 0xffffffff;
  *(undefined2 *)(param_1 + 2) = 0;
  *(undefined2 *)((int)param_1 + 10) = param_2;
  return;
}



void FUN_02397eb4(void)

{
  int iVar1;
  
  iVar1 = *DAT_02397f04;
  FUN_0239a9c8();
  func_0x033a85a8(iVar1 + 0x15c,*(int *)(*DAT_02397f04 + 0x2ec) + -0xc);
  func_0x033a85a8(iVar1 + 0x15c,*(int *)(*DAT_02397f04 + 0x3b4) + -0xc);
  func_0x033abc24();
  return;
}



void FUN_02397f08(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = DAT_02397fa4;
  *(ushort *)(*DAT_02397fa4 + 0x312) = *(ushort *)(*DAT_02397fa4 + 0x312) | 0x8000;
  if (*(short *)(*piVar1 + 800) != 0) {
    func_0x033a8fa0();
    piVar1 = DAT_02397fa4;
    if (*(short *)(*DAT_02397fa4 + 0x3d8) != 0) {
      *(undefined2 *)(*DAT_02397fa4 + 0x3d8) = 0;
      *(undefined2 *)(*(int *)(*piVar1 + 0x3f4) + 4) = 6;
      FUN_0239bfe0();
    }
    FUN_023993a0();
  }
  do {
    iVar2 = func_0x033a82a8(3);
  } while (iVar2 != DAT_02397fa8);
  func_0x033a81e8(3,0x17);
  return;
}



void FUN_02397fac(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *DAT_0239802c;
  if ((*(short *)(iVar2 + 0x3c8) != 0) && (iVar1 = func_0x033a8500(iVar2 + 0x15c,0x12), iVar1 != 0))
  {
    *(short *)(iVar1 + 0xc) = (short)DAT_02398030;
    *(undefined2 *)(iVar1 + 0xe) = 1;
    func_0x033ab364(0x1000000);
    *(undefined2 *)(iVar1 + 0x10) = *(undefined2 *)(iVar2 + 0x3c8);
    *(undefined2 *)(iVar2 + 0x3c8) = 0;
    func_0x033ab3a0();
    func_0x033a8a4c(*DAT_0239802c + 0x15c,iVar1);
  }
  return;
}



void FUN_02398034(ushort param_1)

{
  func_0x033ab364(0x1000000);
  *(ushort *)(*DAT_02398074 + 0x3c8) = *(ushort *)(*DAT_02398074 + 0x3c8) | param_1;
  func_0x033ab3a0();
  func_0x033a81e8(2,0x15);
  return;
}



void FUN_02398078(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *DAT_02398170;
  if (*(short *)(iVar1 + 0x324) == 1) {
    iVar2 = FUN_02398208(iVar1 + 0x478);
    if (iVar2 != 0) {
      FUN_023981c4();
      FUN_0239fdc8();
    }
    iVar2 = FUN_02398208(iVar1 + 0x428);
    if (iVar2 != 0) {
      FUN_02398178((short *)(iVar1 + 0x428));
    }
  }
  else if (*(short *)(iVar1 + 0x324) == 2) {
    FUN_02398208(iVar1 + 0x464);
    iVar2 = FUN_02398208(iVar1 + 0x428);
    if (iVar2 != 0) {
      if (*(short *)(iVar1 + 0x428) != 0) {
        FUN_023981c4();
      }
      FUN_0239f504(*(ushort *)(iVar1 + 0x382));
      *(short *)(iVar1 + 0x3d0) = *(short *)(iVar1 + 0x3d0) + 1;
    }
  }
  iVar2 = FUN_02398208(iVar1 + 0x414);
  if (iVar2 != 0) {
    FUN_02398178((short *)(iVar1 + 0x414));
  }
  iVar2 = FUN_02398208((int)(short *)(iVar1 + 0x400));
  if (iVar2 != 0) {
    FUN_02398178((short *)(iVar1 + 0x400));
  }
  if (*DAT_02398174 == 0) {
    *DAT_02398174 = 1;
  }
  return;
}



void FUN_02398178(short *param_1)

{
  if (*param_1 != 0) {
    FUN_023981c4();
    FUN_023a1034(*(int *)(param_1 + 4),*(int *)(param_1 + 6) + -0x10);
    *(short *)(*DAT_023981c0 + 0x3d0) = *(short *)(*DAT_023981c0 + 0x3d0) + 1;
  }
  return;
}



void FUN_023981c4(void)

{
  int iVar1;
  
  *DAT_02398200 = 0;
  iVar1 = 0x10;
  while( true ) {
    if (iVar1 == 0) {
      return;
    }
    if (*DAT_02398204 == 0) break;
    if (*DAT_02398204 == 9) {
      return;
    }
    iVar1 = iVar1 + -1;
  }
  return;
}



undefined4 FUN_02398208(int param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 8);
  if ((*(ushort *)(iVar4 + -4) == DAT_02398290) && (*(ushort *)(iVar4 + -2) == DAT_02398294)) {
    uVar3 = 0;
  }
  else {
    *(undefined2 *)(iVar4 + 10) = 1;
    uVar1 = (undefined2)DAT_02398290;
    *(undefined2 *)(iVar4 + -4) = uVar1;
    uVar2 = (undefined2)DAT_02398294;
    *(undefined2 *)(iVar4 + -2) = uVar2;
    iVar4 = *(int *)(param_1 + 8);
    *(undefined2 *)(iVar4 + 0xc) = uVar1;
    *(undefined2 *)(iVar4 + 0xe) = uVar2;
    *(short *)(*DAT_02398298 + 0x3ce) = *(short *)(*DAT_02398298 + 0x3ce) + 1;
    uVar3 = 1;
  }
  return uVar3;
}



uint FUN_0239829c(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = (uint)*(ushort *)(DAT_0239830c + (param_2 & 0xf) * 2) ^
          DAT_02398310 & (int)param_2 >> 4 & 0xffff ^
          (uint)*(ushort *)(DAT_0239830c + (param_1 & 0xf) * 2);
  return (uint)*(ushort *)(DAT_0239830c + (uVar1 & 0xf) * 2) ^ DAT_02398310 & (int)uVar1 >> 4 ^
         (uint)*(ushort *)(DAT_0239830c + ((int)param_1 >> 4 & 0xfU) * 2);
}



undefined2 FUN_02398314(void)

{
  int iVar1;
  
  iVar1 = *DAT_02398344 + DAT_02398348;
  *(short *)(iVar1 + 4) =
       *(short *)(iVar1 + 4) * *(short *)(*DAT_02398344 + 0x5c8) + *(short *)(iVar1 + 2);
  return *(undefined2 *)(iVar1 + 4);
}



void FUN_0239834c(undefined2 param_1)

{
  *(undefined2 *)(*DAT_02398360 + 0x5cc) = param_1;
  return;
}



void FUN_02398364(ushort param_1,ushort param_2)

{
  int iVar1;
  
  iVar1 = *DAT_02398394 + DAT_02398398;
  *(ushort *)(*DAT_02398394 + 0x5c8) = (param_1 & (ushort)DAT_0239839c) + 5;
  *(ushort *)(iVar1 + 2) = param_2 | 1;
  return;
}



uint FUN_023983a0(ushort *param_1)

{
  uint uVar1;
  
  if (((uint)param_1 & 1) == 0) {
    uVar1 = *param_1 & 0xff;
  }
  else {
    uVar1 = (int)(uint)*(ushort *)((int)param_1 + -1) >> 8;
  }
  return uVar1;
}



void FUN_023983c0(ushort *param_1,int param_2)

{
  if (((uint)param_1 & 1) == 0) {
    *param_1 = *param_1 & 0xff00 | (ushort)param_2 & 0xff;
  }
  else {
    *(ushort *)((int)param_1 + -1) = *(ushort *)((int)param_1 + -1) & 0xff | (ushort)(param_2 << 8);
  }
  return;
}



void FUN_023983ec(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  FUN_02398478(param_1,param_2,0x12);
  if (param_4 != 0) {
    FUN_02398478(param_1 + 0x28,param_3,param_4 + 1U >> 1);
  }
  return;
}



void FUN_02398428(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  FUN_02398478(param_1,param_2,0x12);
  if (param_4 != 0) {
    FUN_02398478(param_1 + 0x24,param_3,param_4 + 1U >> 1);
  }
  return;
}



void FUN_02398464(undefined4 param_1,undefined4 param_2,int param_3)

{
                    // WARNING: Could not recover jumptable at 0x02398470. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02398474)(param_1,param_2,param_3 + 1U >> 1);
  return;
}



void FUN_02398478(undefined4 param_1,undefined4 param_2,int param_3)

{
                    // WARNING: Could not recover jumptable at 0x0239848c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02398490)(param_2,param_1,param_3 << 1);
  return;
}



void FUN_02398494(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = param_3 + 1U & 0xfffffffe;
  if (DAT_02398510 < param_2 + uVar1) {
    iVar2 = uVar1 - (DAT_02398510 - param_2);
    uVar1 = DAT_02398510 - param_2;
  }
  else {
    iVar2 = 0;
  }
  func_0x033adb60(param_2,param_1,uVar1);
  if (iVar2 != 0) {
    func_0x033adb60((param_2 + uVar1) - (uint)*(ushort *)(*DAT_02398514 + 0x3b2),param_1 + uVar1,
                    iVar2);
  }
  return;
}



void FUN_02398518(void)

{
                    // WARNING: Could not recover jumptable at 0x0239852c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02398538)(*DAT_02398530 + DAT_02398534);
  return;
}



void FUN_0239853c(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  func_0x033ace94(*DAT_023985a4 + DAT_023985a8);
  uVar1 = func_0x033b6d70((uint)(param_1 * DAT_023985ac) >> 6,1000);
  func_0x033acfa0(*DAT_023985a4 + DAT_023985a8,uVar1,0,param_2,0);
  return;
}



void FUN_023985b0(int param_1,undefined4 param_2)

{
  func_0x033ace94(*DAT_0239860c + DAT_02398610);
  func_0x033acfa0(*DAT_0239860c + DAT_02398610,(uint)(param_1 * DAT_02398614) >> 6,0,param_2,0);
  return;
}



void FUN_02398618(void)

{
  int iVar1;
  
  iVar1 = *DAT_02398694;
  *(int *)(iVar1 + 0x3c0) = *(int *)(iVar1 + 0x3c0) + 1;
  func_0x033a81e8(1,10);
  func_0x033a81e8(2,0x12);
  func_0x033a81e8(1,0x11);
  if (*(short *)(iVar1 + 0x1d0) != 0) {
    func_0x033a81e8(2,0x13);
  }
  if (*(short *)(iVar1 + 0x3c8) != 0) {
    func_0x033a81e8(2,0x15);
  }
  return;
}



void FUN_02398698(void)

{
                    // WARNING: Could not recover jumptable at 0x023986a8. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_023986b0)(*DAT_023986ac + 0x5e0);
  return;
}



void FUN_023986b4(int param_1,undefined4 param_2)

{
  uint uVar1;
  longlong lVar2;
  
  func_0x033ace94(*DAT_02398720 + 0x5e0);
  uVar1 = (uint)(param_1 * DAT_02398724) >> 6;
  lVar2 = func_0x033acba8();
  lVar2 = lVar2 + (ulonglong)uVar1;
  func_0x033acf24(*DAT_02398720 + 0x5e0,(int)lVar2,(int)((ulonglong)lVar2 >> 0x20),uVar1,0,param_2,0
                 );
  return;
}



void FUN_02398728(undefined4 param_1)

{
                    // WARNING: Could not recover jumptable at 0x02398730. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02398738)(param_1,DAT_02398734);
  return;
}



void FUN_0239873c(int param_1)

{
                    // WARNING: Could not recover jumptable at 0x0239874c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02398750)(param_1 * 1000);
  return;
}



void FUN_02398760(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *DAT_023987a4;
  iVar1 = func_0x033ad154();
  if (iVar1 == 0) {
    *(ushort *)(iVar2 + 0x312) = *(ushort *)(iVar2 + 0x312) | 0x40;
  }
  else {
    func_0x033ad144(iVar2 + 0x5e0);
    func_0x033ad144(iVar2 + DAT_023987a8);
  }
  return;
}



void FUN_023987ac(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint local_28;
  undefined4 local_24 [2];
  
  iVar2 = DAT_0239892c;
  iVar1 = *DAT_02398928;
  uVar4 = 0;
  local_24[0] = 0;
  do {
    FUN_023a451c(uVar4 * 2 + 0x44,2,(ushort *)local_24);
    *(short *)(&Wifi_WS1_Region + *(ushort *)(iVar2 + uVar4 * 2)) = (short)local_24[0];
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x10);
  local_28 = *(ushort *)(iVar1 + 0x5d2) & 0x7f | (uint)(*(ushort *)(iVar1 + 0x5d2) >> 7) << 8;
  *DAT_02398930 = (short)local_28;
  iVar3 = 0xce;
  iVar2 = func_0x033b6b64((*(ushort *)(iVar1 + 0x5d2) & 0x7f) + 7,8);
  uVar4 = (uint)*(ushort *)(iVar1 + 0x5d4);
  if (*(short *)(iVar1 + 0x5d0) == 3) {
    FUN_023a451c(uVar4 + 0xce,1,(ushort *)(iVar1 + 0x5d8));
    for (uVar5 = 0; uVar5 < uVar4; uVar5 = uVar5 + 1) {
      local_28 = 0;
      FUN_023a451c(iVar3,1,(ushort *)&local_28);
      local_28 = local_28 | uVar5 * 0x100 + 0x50000;
      FUN_02398abc(local_28);
      iVar3 = iVar3 + 1;
    }
  }
  else {
    local_28 = 0;
    for (; uVar4 != 0; uVar4 = uVar4 - 1) {
      FUN_023a451c(iVar3,iVar2,(ushort *)&local_28);
      FUN_02398abc(local_28);
      if ((*(short *)(iVar1 + 0x5d0) == 2) && (local_28 >> 0x12 == 9)) {
        *(uint *)(iVar1 + 0x5dc) = local_28 & 0xffff83ff;
      }
      iVar3 = iVar3 + iVar2;
    }
  }
  return;
}



void FUN_02398934(void)

{
  int iVar1;
  uint uVar2;
  undefined4 local_18;
  
  *DAT_02398994 = 0x100;
  iVar1 = 100;
  uVar2 = 0;
  local_18 = 0;
  do {
    FUN_023a451c(iVar1,1,(ushort *)&local_18);
    FUN_02398ae4((ushort)uVar2,(short)local_18);
    iVar1 = iVar1 + 1;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x69);
  return;
}



void FUN_02398998(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_023989cc;
  uVar2 = 0;
  do {
    *(undefined2 *)(&Wifi_WS1_Region + *(ushort *)(iVar1 + uVar2 * 4)) =
         *(undefined2 *)(iVar1 + uVar2 * 4 + 2);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x19);
  return;
}



void FUN_023989d0(void)

{
  int iVar1;
  
  iVar1 = *DAT_02398a48;
  func_0x033adb48(0,(ushort *)(iVar1 + 0x5d0),0x10);
  FUN_023a451c(0x40,1,(ushort *)(iVar1 + 0x5d0));
  FUN_023a451c(0x41,1,(ushort *)(iVar1 + 0x5d2));
  FUN_023a451c(0x42,1,(ushort *)(iVar1 + 0x5d4));
  FUN_023a451c(0x43,1,(ushort *)(iVar1 + 0x5d6));
  return;
}



void FUN_02398a4c(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint local_20 [2];
  
  iVar3 = 100;
  uVar1 = 0;
  local_20[0] = 0;
  uVar2 = 0;
  do {
    FUN_023a451c(iVar3,1,(ushort *)local_20);
    if (uVar2 == 1) {
      local_20[0] = local_20[0] & 0x80;
    }
    uVar1 = FUN_0239829c(local_20[0] & 0xff,uVar1);
    iVar3 = iVar3 + 1;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x69);
  return;
}



void FUN_02398abc(undefined4 param_1)

{
  *DAT_02398ad8 = (short)param_1;
  *DAT_02398adc = (short)((uint)param_1 >> 0x10);
                    // WARNING: Could not recover jumptable at 0x02398ad4. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_02398ae0)();
  return;
}



undefined4 FUN_02398ae4(ushort param_1,undefined2 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  *DAT_02398b1c = param_2;
  *DAT_02398b20 = param_1 | 0x5000;
  iVar1 = FUN_0239b8a0();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



undefined2 FUN_02398b24(ushort param_1)

{
  *DAT_02398b50 = param_1 | 0x6000;
  FUN_0239b8a0();
  return *DAT_02398b54;
}



undefined4 FUN_02398b58(void)

{
  short sVar1;
  
  sVar1 = *(short *)(*DAT_02398ba0 + 0x304);
  if (sVar1 == 0) {
    if ((*(ushort *)(*DAT_02398ba0 + 0x378) & 1) != 0) {
      return 10;
    }
  }
  else if (sVar1 == 1) {
    return 10;
  }
  return 0x14;
}



void FUN_02398ba4(int param_1,ushort *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ushort *puVar5;
  uint uVar6;
  
  *param_2 = 0;
  param_2[1] = 0;
  uVar2 = FUN_023983a0((ushort *)(param_1 + 1));
  iVar1 = DAT_02398c5c;
  puVar5 = param_2 + 1;
  for (uVar6 = 0; uVar6 < uVar2; uVar6 = uVar6 + 1) {
    uVar3 = FUN_023983a0((ushort *)(param_1 + 2 + uVar6));
    uVar4 = (uVar3 & 0x7f) - 1;
    if ((uVar4 < 0x78) && (uVar4 = (uint)*(ushort *)(iVar1 + uVar4 * 2), uVar4 != 0xff)) {
      *puVar5 = *puVar5 | (ushort)(1 << (uVar4 & 0xff));
      if ((uVar3 & 0x80) != 0) {
        *param_2 = *param_2 | (ushort)(1 << (uVar4 & 0xff));
      }
    }
    else {
      *puVar5 = *puVar5 | 0x8000;
      if ((uVar3 & 0x80) != 0) {
        *param_2 = *param_2 | 0x8000;
      }
    }
  }
  return;
}



uint FUN_02398c60(uint param_1)

{
  return (uint)*(ushort *)(*DAT_02398c7c + 0x300) & 1 << (param_1 & 0xff);
}



undefined4 FUN_02398c80(short *param_1,short *param_2)

{
  if (((param_1[2] == param_2[2]) && (param_1[1] == param_2[1])) && (*param_1 == *param_2)) {
    return 1;
  }
  return 0;
}



undefined4 FUN_02398cbc(uint param_1,ushort *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  ushort *puVar9;
  bool bVar10;
  
  iVar1 = *DAT_02398d88;
  if (param_1 < 0x21) {
    uVar6 = (uint)*(ushort *)(iVar1 + 0x336);
    if (uVar6 == 0) {
      uVar2 = 1;
    }
    else {
      if (*(short *)(iVar1 + 0x3d8) == 0x13) {
        if (param_1 < uVar6) {
          return 0;
        }
      }
      else {
        bVar10 = param_1 != uVar6;
        uVar6 = param_1;
        if (bVar10) {
          return 0;
        }
      }
      puVar9 = (ushort *)(iVar1 + 0x338);
      puVar8 = (ushort *)(iVar1 + 0x358);
      for (uVar7 = 0; uVar7 < uVar6; uVar7 = uVar7 + 1) {
        uVar3 = FUN_023983a0(puVar8);
        puVar8 = (ushort *)((int)puVar8 + 1);
        uVar4 = FUN_023983a0(param_2);
        param_2 = (ushort *)((int)param_2 + 1);
        uVar5 = FUN_023983a0(puVar9);
        puVar9 = (ushort *)((int)puVar9 + 1);
        if ((uVar4 | uVar3) != (uVar5 | uVar3)) {
          return 0;
        }
      }
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



void FUN_02398d8c(void)

{
  ushort uVar1;
  ushort *puVar2;
  int iVar3;
  
  puVar2 = DAT_02398f8c;
  iVar3 = *DAT_02398f84 + DAT_02398f88;
  *(uint *)(iVar3 + 0x50) = *(int *)(iVar3 + 0x50) + (*DAT_02398f8c & 0xff);
  uVar1 = puVar2[1];
  *(int *)(iVar3 + 0x4c) = *(int *)(iVar3 + 0x4c) + ((int)(uint)uVar1 >> 8);
  *(uint *)(iVar3 + 0x5c) = *(int *)(iVar3 + 0x5c) + (uVar1 & 0xff);
  uVar1 = puVar2[2];
  *(int *)(iVar3 + 0x58) = *(int *)(iVar3 + 0x58) + ((int)(uint)uVar1 >> 8);
  *(uint *)(iVar3 + 0x54) = *(int *)(iVar3 + 0x54) + (uVar1 & 0xff);
  uVar1 = puVar2[3];
  *(int *)(iVar3 + 0x60) = *(int *)(iVar3 + 0x60) + ((int)(uint)uVar1 >> 8);
  *(uint *)(iVar3 + 0x38) = *(int *)(iVar3 + 0x38) + (uVar1 & 0xff);
  *(uint *)(iVar3 + 0x48) = *(int *)(iVar3 + 0x48) + (puVar2[4] & 0xff);
  *(uint *)(iVar3 + 0x20) = *(int *)(iVar3 + 0x20) + (puVar2[5] & 0xff);
  uVar1 = puVar2[6];
  *(int *)(iVar3 + 0x30) = *(int *)(iVar3 + 0x30) + ((int)(uint)uVar1 >> 8);
  *(uint *)(iVar3 + 0x44) = *(int *)(iVar3 + 0x44) + (uVar1 & 0xff);
  uVar1 = puVar2[7];
  *(uint *)(iVar3 + 0x3c) = *(int *)(iVar3 + 0x3c) + (uVar1 & 0xff);
  *(int *)(iVar3 + 0x40) = *(int *)(iVar3 + 0x40) + ((int)(uint)uVar1 >> 8);
  *(uint *)(iVar3 + 0xc) = *(int *)(iVar3 + 0xc) + (puVar2[8] & 0xff);
  *(int *)(iVar3 + 0x78) = *(int *)(iVar3 + 0x78) + ((int)(uint)puVar2[0x10] >> 8);
  uVar1 = puVar2[0x11];
  *(uint *)(iVar3 + 0x7c) = *(int *)(iVar3 + 0x7c) + (uVar1 & 0xff);
  *(int *)(iVar3 + 0x80) = *(int *)(iVar3 + 0x80) + ((int)(uint)uVar1 >> 8);
  uVar1 = puVar2[0x12];
  *(uint *)(iVar3 + 0x84) = *(int *)(iVar3 + 0x84) + (uVar1 & 0xff);
  *(int *)(iVar3 + 0x88) = *(int *)(iVar3 + 0x88) + ((int)(uint)uVar1 >> 8);
  uVar1 = puVar2[0x13];
  *(uint *)(iVar3 + 0x8c) = *(int *)(iVar3 + 0x8c) + (uVar1 & 0xff);
  *(int *)(iVar3 + 0x90) = *(int *)(iVar3 + 0x90) + ((int)(uint)uVar1 >> 8);
  uVar1 = puVar2[0x14];
  *(uint *)(iVar3 + 0x94) = *(int *)(iVar3 + 0x94) + (uVar1 & 0xff);
  *(int *)(iVar3 + 0x98) = *(int *)(iVar3 + 0x98) + ((int)(uint)uVar1 >> 8);
  uVar1 = puVar2[0x15];
  *(uint *)(iVar3 + 0x9c) = *(int *)(iVar3 + 0x9c) + (uVar1 & 0xff);
  *(int *)(iVar3 + 0xa0) = *(int *)(iVar3 + 0xa0) + ((int)(uint)uVar1 >> 8);
  uVar1 = puVar2[0x16];
  *(uint *)(iVar3 + 0xa4) = *(int *)(iVar3 + 0xa4) + (uVar1 & 0xff);
  *(int *)(iVar3 + 0xa8) = *(int *)(iVar3 + 0xa8) + ((int)(uint)uVar1 >> 8);
  uVar1 = puVar2[0x17];
  *(uint *)(iVar3 + 0xac) = *(int *)(iVar3 + 0xac) + (uVar1 & 0xff);
  *(int *)(iVar3 + 0xb0) = *(int *)(iVar3 + 0xb0) + ((int)(uint)uVar1 >> 8);
  return;
}



void FUN_02398f90(void)

{
  FUN_02398d8c();
  func_0x033adb7c(0,*DAT_02398fcc + DAT_02398fd0,0xb4);
  return;
}



void FUN_02398fd4(undefined2 *param_1,undefined2 *param_2,undefined2 *param_3,undefined2 *param_4)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = *param_3;
  param_1[4] = param_3[1];
  param_1[5] = param_3[2];
  param_1[6] = *param_4;
  param_1[7] = param_4[1];
  param_1[8] = param_4[2];
  return;
}



void FUN_02399054(undefined2 *param_1,undefined2 *param_2)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  return;
}



void FUN_02399070(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = DAT_023990d8;
  iVar2 = *DAT_023990d8;
  *(undefined2 *)(iVar2 + 0x382) = 0;
  *(undefined2 *)(*piVar1 + 0x4a2) = 0;
  FUN_0239b8d4();
  *DAT_023990dc = 0;
  *DAT_023990e0 = 0;
  if (*(ushort *)(iVar2 + 0x3a0) != 0) {
    FUN_023a04bc((uint)*(ushort *)(iVar2 + 0x3a0));
    FUN_0239b450((uint)*(ushort *)(iVar2 + 0x3a0),0x20);
    *(undefined2 *)(iVar2 + 0x3a0) = 0;
  }
  return;
}



void FUN_023990e4(uint param_1)

{
  undefined2 uVar1;
  int *piVar2;
  
  piVar2 = DAT_0239911c;
  uVar1 = (undefined2)param_1;
  *(undefined2 *)(*DAT_0239911c + 0x382) = uVar1;
  *(short *)(*piVar2 + 0x4a2) = (short)(1 << (param_1 & 0xff));
  *DAT_02399120 = uVar1;
  *DAT_02399124 = uVar1;
  return;
}



undefined4 FUN_02399128(uint param_1,ushort *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  ushort *puVar5;
  
  iVar1 = *DAT_023991d0;
  if (param_1 < 0x81) {
    if (param_1 != 0) {
      if ((*(ushort *)(iVar1 + 0x3ba) & 1) == 0) {
        func_0x033adb60(param_2,*(undefined4 *)(iVar1 + 0x3b4),param_1 + 1);
      }
      else {
        puVar5 = *(ushort **)(iVar1 + 0x3b4);
        FUN_023983c0(puVar5,0xff);
        for (uVar4 = 0; puVar5 = (ushort *)((int)puVar5 + 1), uVar4 < param_1; uVar4 = uVar4 + 1) {
          uVar3 = FUN_023983a0(param_2);
          FUN_023983c0(puVar5,uVar3);
          param_2 = (ushort *)((int)param_2 + 1);
        }
      }
    }
    *(short *)(iVar1 + 0x3b8) = (short)param_1;
    *(undefined2 *)(iVar1 + 0x3bc) = 1;
    uVar2 = 0;
  }
  else {
    uVar2 = 4;
  }
  return uVar2;
}



undefined4 FUN_023991d4(uint param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *DAT_0239921c;
  if (param_1 < 0x81) {
    func_0x033adb60(param_2,*(undefined4 *)(iVar1 + 0x3b4),param_1 + 1);
    *(short *)(iVar1 + 0x3b8) = (short)param_1;
    uVar2 = 0;
  }
  else {
    uVar2 = 4;
  }
  return uVar2;
}



void FUN_02399220(void)

{
  *(undefined2 *)(*DAT_02399248 + 0x3be) = 0;
  *DAT_0239924c = *DAT_0239924c | 2;
  return;
}



void FUN_02399250(void)

{
  int *piVar1;
  
  piVar1 = DAT_02399298;
  *(undefined2 *)(*DAT_02399298 + 0x3be) = 1;
  if (*(short *)(*piVar1 + 0x43c) != 0) {
    return;
  }
  *DAT_0239929c = *DAT_0239929c & 0xfffd;
  *DAT_023992a0 = 0;
  return;
}



undefined4 FUN_023992a4(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = DAT_02399308;
  iVar2 = *DAT_02399304;
  if (param_1 == DAT_02399308) {
    *(undefined2 *)(iVar2 + 0x30c) = 0xff;
    *(short *)(iVar2 + 0x3a4) = (short)iVar1;
  }
  else {
    uVar3 = func_0x033b6d70(param_1 * (uint)*(ushort *)(iVar2 + 0x386),100);
    if (0x10000 < uVar3) {
      return 5;
    }
    *(short *)(iVar2 + 0x30c) = (short)param_1;
    *(short *)(iVar2 + 0x3a4) = (short)uVar3;
  }
  return 0;
}



void FUN_0239930c(void)

{
  ushort uVar1;
  
  *DAT_02399394 = 0;
  FUN_0239873c(8);
  *DAT_02399398 = 0;
  if (*(short *)(*DAT_0239939c + 0x5d0) == 2) {
    uVar1 = FUN_02398b24(1);
    FUN_02398ae4(1,uVar1 & 0x7f);
    FUN_02398ae4(1,uVar1);
    FUN_0239873c(0x28);
    FUN_023987ac();
  }
  else if (*(short *)(*DAT_0239939c + 0x5d0) == 3) {
    FUN_023987ac();
  }
  return;
}



void FUN_023993a0(void)

{
  ushort uVar1;
  
  if (*(short *)(*DAT_02399400 + 0x5d0) == 2) {
    FUN_02398abc(DAT_02399404);
  }
  uVar1 = FUN_02398b24(0x1e);
  FUN_02398ae4(0x1e,uVar1 | 0x3f);
  *DAT_0239940c = (short)DAT_02399408;
  *DAT_02399410 = 1;
  return;
}



undefined4 FUN_02399414(undefined2 param_1)

{
  *DAT_02399424 = param_1;
  return 0;
}



undefined4 FUN_02399428(uint param_1)

{
  *(short *)(*DAT_0239944c + 0x328) = (short)(param_1 >> 1);
  *DAT_02399450 = (short)param_1;
  return 0;
}



undefined4 FUN_02399454(int param_1)

{
  int iVar1;
  
  iVar1 = *DAT_023994c0;
  *(short *)(iVar1 + 0x326) = (short)param_1;
  if ((param_1 == 0) || (*(short *)(iVar1 + 0x302) == 1)) {
    *DAT_023994c4 = *DAT_023994c4 & 0xffbf;
    FUN_02399ecc((uint)*(ushort *)(iVar1 + 0x310),0);
  }
  else {
    *DAT_023994c4 = *DAT_023994c4 | 0x40;
  }
  return 0;
}



void FUN_023994c8(void)

{
  int iVar1;
  int local_8 [2];
  
  local_8[0] = DAT_02399544;
  FUN_023a451c(0x58,2,(ushort *)local_8);
  local_8[0] = local_8[0] + DAT_02399548;
  iVar1 = FUN_02398b58();
  if ((iVar1 == 0x14) && (local_8[0] = local_8[0] - DAT_0239954c, (*DAT_02399550 & 2) != 0)) {
    local_8[0] = local_8[0] - DAT_02399554;
  }
  *DAT_02399558 = (short)local_8[0];
  return;
}



undefined4 FUN_0239955c(ushort *param_1)

{
  int iVar1;
  
  iVar1 = *DAT_023995a0;
  *(ushort *)(iVar1 + 0x378) = *param_1;
  *(ushort *)(iVar1 + 0x37a) = param_1[1] | *param_1;
  FUN_023994c8();
  return 0;
}



undefined4 FUN_023995a4(uint param_1,int param_2)

{
  undefined2 uVar1;
  short sVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  code *pcVar7;
  uint local_30;
  undefined4 local_2c [2];
  
  pcVar7 = DAT_0239981c;
  if (param_2 == 0) {
    pcVar7 = DAT_02399820;
  }
  uVar5 = FUN_02398c60(param_1);
  if (uVar5 == 0) {
    return 5;
  }
  uVar1 = *DAT_02399824;
  *DAT_02399824 = (short)DAT_02399828;
  piVar3 = DAT_02399834;
  do {
    do {
    } while ((int)(uint)*DAT_0239982c >> 8 != 2);
  } while ((*DAT_02399830 != 0) && (*DAT_02399830 != 9));
  *(short *)(*DAT_02399834 + 0x392) = (short)param_1;
  iVar6 = *piVar3;
  sVar2 = *(short *)(iVar6 + 0x5d0);
  if (sVar2 != 2) {
    if (sVar2 == 3) {
      iVar6 = *(ushort *)(iVar6 + 0x5d4) + 0xcf;
      for (uVar5 = 0; piVar4 = DAT_02399834, uVar5 < *(ushort *)(*piVar3 + 0x5d8); uVar5 = uVar5 + 1
          ) {
        local_30 = 0;
        local_2c[0] = 0;
        (*pcVar7)(iVar6,1,local_2c);
        (*pcVar7)(iVar6 + param_1,1,&local_30);
        FUN_02398ae4((ushort)local_2c[0],(short)local_30);
        iVar6 = iVar6 + 0xf;
      }
      for (uVar5 = 0; uVar5 < *(ushort *)(*piVar4 + 0x5d6); uVar5 = uVar5 + 1) {
        local_30 = 0;
        (*pcVar7)(iVar6,1,&local_30);
        local_30 = local_30 << 8;
        (*pcVar7)(iVar6 + param_1,1,&local_30);
        local_30 = local_30 | 0x50000;
        FUN_02398abc(local_30);
        iVar6 = iVar6 + 0xf;
      }
      goto LAB_023997f8;
    }
    if (sVar2 != 5) goto LAB_023997f8;
  }
  local_30 = 0;
  iVar6 = (param_1 - 1) * 6;
  (*pcVar7)(iVar6 + 0xf2,3,&local_30);
  FUN_02398abc(local_30);
  (*pcVar7)(iVar6 + 0xf5,3,&local_30);
  FUN_02398abc(local_30);
  local_30 = 0;
  if ((*(uint *)(*DAT_02399834 + 0x5dc) & 0x10000) == 0) {
    (*pcVar7)((param_1 - 1) + DAT_02399838,1,&local_30);
    FUN_02398ae4(0x1e,(short)local_30);
  }
  else if ((*(uint *)(*DAT_02399834 + 0x5dc) & 0x8000) == 0) {
    (*pcVar7)(param_1 + 0x153,1,&local_30);
    local_30 = *(uint *)(*DAT_02399834 + 0x5dc) | (local_30 & 0x1f) << 10;
    FUN_02398abc(local_30);
  }
LAB_023997f8:
  *DAT_02399824 = uVar1;
  *DAT_0239983c = 3;
  return 0;
}



void FUN_02399840(void)

{
  ushort local_10;
  ushort auStack_e [7];
  
  FUN_023a451c(0x36,6,auStack_e);
  FUN_023a451c(0x3c,2,&local_10);
  FUN_0239a2a8(auStack_e);
  FUN_0239a274(7);
  FUN_0239a234(local_10 & DAT_0239996c);
  FUN_0239a1ac(2);
  FUN_0239a170(0);
  FUN_0239a0bc(0);
  FUN_0239a098(0);
  FUN_0239a034(DAT_02399970);
  FUN_02399a08(500);
  FUN_02399ffc(0);
  FUN_02399fc4(0);
  FUN_02399f8c(0x10);
  FUN_02399ecc(DAT_02399974,0);
  FUN_02399e9c(DAT_02399978);
  FUN_02399ddc(1);
  FUN_02399db8(0);
  FUN_0239955c(DAT_0239997c);
  FUN_02399d70(0,0x1f);
  FUN_023992a4(5);
  FUN_02399c2c(0,0);
  FUN_02399d08(0);
  FUN_02399bec(0);
  FUN_02398364(*DAT_02399980 + *DAT_02399980 * 0x100,*DAT_02399980);
  *(undefined2 *)(*DAT_02399984 + 0x32c) = 1;
  return;
}



undefined4 FUN_02399988(uint param_1)

{
  if ((param_1 != 0) && (param_1 < 0x100)) {
    *(short *)(*DAT_023999b8 + 0x388) = (short)param_1;
    return 0;
  }
  return 5;
}



undefined4 FUN_023999bc(uint param_1)

{
  if ((param_1 != 0) && (param_1 < 0x100)) {
    *(short *)(*DAT_023999fc + 0x38c) = (short)param_1;
    *DAT_02399a00 = (short)param_1;
    *DAT_02399a04 = 0;
    return 0;
  }
  return 5;
}



undefined4 FUN_02399a08(uint param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
  piVar1 = DAT_02399a60;
  if ((param_1 < 10) || (1000 < param_1)) {
    uVar2 = 5;
  }
  else {
    *(short *)(*DAT_02399a60 + 0x386) = (short)param_1;
    *DAT_02399a64 = (short)param_1;
    FUN_023992a4((uint)*(ushort *)(*piVar1 + 0x30c));
    uVar2 = 0;
  }
  return uVar2;
}



undefined4 FUN_02399a68(uint param_1,ushort *param_2)

{
  ushort uVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  
  iVar6 = *DAT_02399b80;
  bVar2 = false;
  if (param_1 < 0x21) {
    if ((*(short *)(iVar6 + 800) == 0x40) && (*(short *)(iVar6 + 0x302) == 1)) {
      if (*(ushort *)(iVar6 + 0x336) != param_1) {
        return 6;
      }
      if (*(short *)(iVar6 + 0x3aa) != 0) {
        bVar2 = true;
      }
    }
    for (uVar7 = 0; uVar7 < param_1; uVar7 = uVar7 + 1) {
      uVar5 = FUN_023983a0(param_2);
      FUN_023983c0((ushort *)(iVar6 + 0x338 + uVar7),uVar5);
      param_2 = (ushort *)((int)param_2 + 1);
    }
    for (; uVar7 < 0x20; uVar7 = uVar7 + 1) {
      FUN_023983c0((ushort *)(iVar6 + 0x338 + uVar7),0);
    }
    *(short *)(iVar6 + 0x336) = (short)param_1;
    if (bVar2) {
      iVar4 = *(int *)(*DAT_02399b80 + 0x480);
      uVar1 = *(ushort *)(iVar6 + 0x3aa);
      for (uVar7 = 0; uVar7 < param_1; uVar7 = uVar7 + 1) {
        uVar5 = FUN_023983a0((ushort *)(iVar6 + 0x338 + uVar7));
        FUN_023983c0((ushort *)(iVar4 + 0x26 + (uint)uVar1 + uVar7),uVar5);
      }
    }
    uVar3 = 0;
  }
  else {
    uVar3 = 5;
  }
  return uVar3;
}



undefined4 FUN_02399b84(ushort *param_1)

{
  FUN_02399054((undefined2 *)(*DAT_02399be0 + 0x37c),param_1);
  FUN_02399054(DAT_02399be4,param_1);
  if ((*param_1 & 1) == 0) {
    *DAT_02399be8 = *DAT_02399be8 | 0x400;
  }
  else {
    *DAT_02399be8 = *DAT_02399be8 & 0xfbff;
  }
  return 0;
}



undefined4 FUN_02399bec(uint param_1)

{
  if (param_1 < 2) {
    *(ushort *)(*DAT_02399c28 + 0x30e) =
         *(ushort *)(*DAT_02399c28 + 0x30e) & 0xffbf | (ushort)((param_1 & 1) << 6);
    return 0;
  }
  return 5;
}



undefined4 FUN_02399c2c(uint param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  
  if ((param_1 < 2) && (param_2 < 2)) {
    if (param_1 == 0) {
      *(ushort *)(*DAT_02399d00 + 0x30e) =
           *(ushort *)(*DAT_02399d00 + 0x30e) & 0xffdf | (ushort)((param_2 & 1) << 5);
    }
    else if (param_1 == 1) {
      iVar2 = *DAT_02399d00;
      if (*(short *)(iVar2 + 0x302) != 1) {
        return 0xb;
      }
      *(ushort *)(iVar2 + 0x30e) = *(ushort *)(iVar2 + 0x30e) & 0xffdf;
    }
    piVar1 = DAT_02399d00;
    *(ushort *)(*DAT_02399d00 + 0x30e) =
         *(ushort *)(*DAT_02399d00 + 0x30e) & 0xffef | (ushort)((param_1 & 1) << 4);
    *DAT_02399d04 =
         (ushort)((ushort)(((uint)*(ushort *)(*piVar1 + 0x30e) << 0x1a) >> 0x10) ^
                 (ushort)(((uint)*(ushort *)(*piVar1 + 0x30e) << 0x1c) >> 0x10)) >> 0xf;
    return 0;
  }
  return 5;
}



undefined4 FUN_02399d08(uint param_1)

{
  int *piVar1;
  
  piVar1 = DAT_02399d68;
  if (param_1 < 2) {
    *(ushort *)(*DAT_02399d68 + 0x30e) =
         *(ushort *)(*DAT_02399d68 + 0x30e) & 0xfff7 | (ushort)((param_1 & 1) << 3);
    *DAT_02399d6c =
         (ushort)((ushort)(((uint)*(ushort *)(*piVar1 + 0x30e) << 0x1a) >> 0x10) ^
                 (ushort)(((uint)*(ushort *)(*piVar1 + 0x30e) << 0x1c) >> 0x10)) >> 0xf;
    return 0;
  }
  return 5;
}



undefined4 FUN_02399d70(uint param_1,uint param_2)

{
  undefined4 uVar1;
  
  if (param_1 < 4) {
    if (param_2 < 0x40) {
      FUN_02398ae4(0x13,(short)param_1);
      FUN_02398ae4(0x35,(short)param_2);
      uVar1 = 0;
    }
    else {
      uVar1 = 5;
    }
  }
  else {
    uVar1 = 5;
  }
  return uVar1;
}



undefined4 FUN_02399db8(uint param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 2) {
    *(short *)(*DAT_02399dd8 + 0x306) = (short)param_1;
    uVar1 = 0;
  }
  else {
    uVar1 = 5;
  }
  return uVar1;
}



undefined4 FUN_02399ddc(uint param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *DAT_02399e94;
  if (param_1 < 2) {
    *(ushort *)(iVar2 + 0x30e) = *(ushort *)(iVar2 + 0x30e) & 0xfffb | (ushort)((param_1 & 1) << 2);
    if (param_1 == 0) {
      *(ushort *)(iVar2 + 0x394) = *(ushort *)(iVar2 + 0x394) & 0xffdf;
    }
    else {
      *(ushort *)(iVar2 + 0x394) = *(ushort *)(iVar2 + 0x394) | 0x20;
    }
    if ((*(short *)(iVar2 + 800) == 0x40) && (*(short *)(*DAT_02399e94 + 0x302) == 1)) {
      *(undefined2 *)(*(int *)(*DAT_02399e94 + 0x480) + 0x2e) = *(undefined2 *)(iVar2 + 0x394);
    }
    if (param_1 == 0) {
      *DAT_02399e98 = *DAT_02399e98 & 0xfff9;
    }
    else {
      *DAT_02399e98 = *DAT_02399e98 | 6;
    }
    FUN_023994c8();
    uVar1 = 0;
  }
  else {
    uVar1 = 5;
  }
  return uVar1;
}



undefined4 FUN_02399e9c(undefined2 *param_1)

{
  undefined2 *puVar1;
  uint uVar2;
  
  uVar2 = 0;
  puVar1 = (undefined2 *)(*DAT_02399ec8 + 0x358);
  do {
    *puVar1 = *param_1;
    uVar2 = uVar2 + 1;
    param_1 = param_1 + 1;
    puVar1 = puVar1 + 1;
  } while (uVar2 < 0x10);
  return 0;
}



undefined4 FUN_02399ecc(uint param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 < 10) {
    uVar1 = 5;
  }
  else {
    *(short *)(*DAT_02399f84 + 0x310) = (short)param_1;
    if (param_2 != 0) {
      *DAT_02399f88 = (short)param_1;
    }
    iVar2 = *DAT_02399f84;
    if (*(short *)(iVar2 + 0x478) != 0) {
      iVar3 = *(int *)(iVar2 + 0x480) + (uint)*(ushort *)(iVar2 + 0x3ae);
      if (*(short *)(iVar2 + 0x326) == 1) {
        FUN_023983c0((ushort *)(iVar3 + 0x2a),param_1 & 0xff);
        FUN_023983c0((ushort *)(iVar3 + 0x2b),(int)param_1 >> 8 & 0xff);
      }
      else {
        FUN_023983c0((ushort *)(iVar3 + 0x2a),0xff);
        FUN_023983c0((ushort *)(iVar3 + 0x2b),0xff);
      }
    }
    uVar1 = 0;
  }
  return uVar1;
}



undefined4 FUN_02399f8c(uint param_1)

{
  int *piVar1;
  
  piVar1 = DAT_02399fc0;
  if (param_1 < 0x100) {
    *(undefined2 *)(*DAT_02399fc0 + 0x398) = 0;
    *(short *)(*piVar1 + 0x396) = (short)param_1;
    return 0;
  }
  return 5;
}



undefined4 FUN_02399fc4(uint param_1)

{
  if (param_1 < 2) {
    *(ushort *)(*DAT_02399ff8 + 0x30e) =
         *(ushort *)(*DAT_02399ff8 + 0x30e) & 0xfffd | (ushort)((param_1 & 1) << 1);
    return 0;
  }
  return 5;
}



undefined4 FUN_02399ffc(uint param_1)

{
  if (param_1 < 2) {
    *(ushort *)(*DAT_0239a030 + 0x30e) =
         *(ushort *)(*DAT_0239a030 + 0x30e) & 0xfffe | (ushort)param_1 & 1;
    return 0;
  }
  return 5;
}



undefined4 FUN_0239a034(int param_1)

{
  FUN_02398464(DAT_0239a088,param_1,0x14);
  FUN_02398464(DAT_0239a08c,param_1 + 0x14,0x14);
  FUN_02398464(DAT_0239a090,param_1 + 0x28,0x14);
  FUN_02398464(DAT_0239a094,param_1 + 0x3c,0x14);
  return 0;
}



undefined4 FUN_0239a098(uint param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 4) {
    *(short *)(*DAT_0239a0b8 + 0x30a) = (short)param_1;
    uVar1 = 0;
  }
  else {
    uVar1 = 5;
  }
  return uVar1;
}



undefined4 FUN_0239a0bc(uint param_1)

{
  int iVar1;
  
  iVar1 = *DAT_0239a164;
  if (param_1 < 4) {
    *(short *)(iVar1 + 0x308) = (short)param_1;
    if (param_1 == 0) {
      *(ushort *)(iVar1 + 0x394) = *(ushort *)(iVar1 + 0x394) & 0xffef;
      *(ushort *)(iVar1 + 0x3a2) = *(ushort *)(iVar1 + 0x3a2) & 0xbfff;
    }
    else {
      *(ushort *)(iVar1 + 0x394) = *(ushort *)(iVar1 + 0x394) | 0x10;
      *(ushort *)(iVar1 + 0x3a2) = *(ushort *)(iVar1 + 0x3a2) | 0x4000;
    }
    if ((*(short *)(iVar1 + 800) == 0x40) && (param_1 == 1)) {
      *(undefined2 *)(*(int *)(*DAT_0239a164 + 0x480) + 0x2e) = *(undefined2 *)(iVar1 + 0x394);
    }
    if (param_1 == 0) {
      param_1 = 1;
    }
    *DAT_0239a168 = *DAT_0239a168 & (ushort)DAT_0239a16c | (ushort)(param_1 << 3);
    return 0;
  }
  return 5;
}



undefined4 FUN_0239a170(uint param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 3) {
    *(short *)(*DAT_0239a1a8 + 0x304) = (short)param_1;
    FUN_023994c8();
    uVar1 = 0;
  }
  else {
    uVar1 = 5;
  }
  return uVar1;
}



undefined4 FUN_0239a1ac(uint param_1)

{
  ushort uVar1;
  int *piVar2;
  undefined4 uVar3;
  
  piVar2 = DAT_0239a228;
  if (param_1 < 4) {
    uVar1 = (ushort)param_1;
    *(ushort *)(*DAT_0239a228 + 0x302) = uVar1;
    *(ushort *)(*piVar2 + 0x324) = uVar1;
    *DAT_0239a22c = *DAT_0239a22c & (ushort)DAT_0239a230 | uVar1;
    FUN_02399454((uint)*(ushort *)(*piVar2 + 0x326));
    *(uint *)(*DAT_0239a228 + 0x314) = *(uint *)(*DAT_0239a228 + 0x314) | 8;
    uVar3 = 0;
  }
  else {
    uVar3 = 5;
  }
  return uVar3;
}



undefined4 FUN_0239a234(uint param_1)

{
  int *piVar1;
  
  piVar1 = DAT_0239a270;
  if ((param_1 & DAT_0239a26c) != 0) {
    *(short *)(*DAT_0239a270 + 0x300) = (short)param_1;
    *(uint *)(*piVar1 + 0x314) = *(uint *)(*piVar1 + 0x314) | 4;
    return 0;
  }
  return 5;
}



undefined4 FUN_0239a274(uint param_1)

{
  if (param_1 < 0x100) {
    *(short *)(*DAT_0239a2a0 + 0x2fe) = (short)param_1;
    *DAT_0239a2a4 = (short)param_1;
    return 0;
  }
  return 5;
}



undefined4 FUN_0239a2a8(ushort *param_1)

{
  undefined4 uVar1;
  
  if ((*param_1 & 1) == 0) {
    FUN_02399054((undefined2 *)(*DAT_0239a300 + 0x2f8),param_1);
    FUN_02399054(DAT_0239a304,param_1);
    *(uint *)(*DAT_0239a300 + 0x314) = *(uint *)(*DAT_0239a300 + 0x314) | 2;
    uVar1 = 0;
  }
  else {
    uVar1 = 5;
  }
  return uVar1;
}



void FUN_0239a308(undefined4 param_1,undefined2 param_2)

{
  int *piVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(*DAT_0239a39c + 0x3b4);
  func_0x033adb48(0,*DAT_0239a39c + 0x2f0,0x28);
  func_0x033adb48(0,*DAT_0239a39c + 0x318,0xc0);
  piVar1 = DAT_0239a39c;
  *(undefined4 *)(*DAT_0239a39c + 0x2f0) = param_1;
  *(undefined2 *)(*piVar1 + 0x2f4) = param_2;
  *(undefined2 *)(*piVar1 + 0x2f6) = param_2;
  *(undefined4 *)(*piVar1 + 0x3b4) = uVar2;
  return;
}



void FUN_0239a3a0(void)

{
  short sVar1;
  ushort uVar2;
  short sVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  
  iVar11 = DAT_0239a690;
  if (*(short *)(*DAT_0239a68c + 0x5d0) != 5) {
    iVar11 = DAT_0239a694;
  }
  for (uVar7 = 0; uVar7 < 0x69; uVar7 = uVar7 + 1) {
    iVar6 = FUN_02398ae4((ushort)uVar7,0xff);
    if (iVar6 == -1) {
      uVar7 = 1;
      goto LAB_0239a660;
    }
  }
  iVar6 = 0;
  uVar8 = 0;
  for (uVar5 = 0; uVar5 < 0x69; uVar5 = uVar5 + 1) {
    uVar7 = uVar8;
    if (uVar5 == *(ushort *)(iVar11 + iVar6 * 2)) {
      iVar6 = iVar6 + 1;
    }
    else {
      sVar1 = FUN_02398b24((ushort)uVar5);
      if ((sVar1 != 0xff) && (uVar7 = uVar8 + 1, 0x20 < uVar8)) goto LAB_0239a660;
    }
    uVar8 = uVar7;
  }
  uVar7 = 0;
  do {
    FUN_02398ae4((ushort)uVar7,0);
    uVar7 = uVar7 + 1;
  } while (uVar7 < 0x69);
  iVar6 = 0;
  for (uVar5 = 0; uVar5 < 0x69; uVar5 = uVar5 + 1) {
    uVar7 = uVar8;
    if (uVar5 == *(ushort *)(iVar11 + iVar6 * 2)) {
      iVar6 = iVar6 + 1;
    }
    else {
      sVar1 = FUN_02398b24((ushort)uVar5);
      if ((sVar1 != 0) && (uVar7 = uVar8 + 1, 0x20 < uVar8)) goto LAB_0239a660;
    }
    uVar8 = uVar7;
  }
  uVar4 = 0x55;
  uVar7 = 0;
  do {
    FUN_02398ae4((ushort)uVar7,uVar4);
    uVar7 = uVar7 + 1;
    uVar4 = ~uVar4;
  } while (uVar7 < 0x69);
  uVar4 = 0x55;
  iVar6 = 0;
  for (uVar5 = 0; uVar5 < 0x69; uVar5 = uVar5 + 1) {
    uVar7 = uVar8;
    if (uVar5 == *(ushort *)(iVar11 + iVar6 * 2)) {
      iVar6 = iVar6 + 1;
    }
    else {
      uVar2 = FUN_02398b24((ushort)uVar5);
      if ((uVar2 != uVar4) && (uVar7 = uVar8 + 1, 0x20 < uVar8)) goto LAB_0239a660;
    }
    uVar4 = ~uVar4 & 0xff;
    uVar8 = uVar7;
  }
  sVar1 = 0xff;
  uVar7 = 0;
  do {
    FUN_02398ae4((ushort)uVar7,sVar1);
    uVar7 = uVar7 + 1;
    sVar1 = sVar1 + -1;
  } while (uVar7 < 0x69);
  sVar1 = 0xff;
  iVar6 = 0;
  for (uVar5 = 0; uVar7 = uVar8, uVar5 < 0x69; uVar5 = uVar5 + 1) {
    if (uVar5 == *(ushort *)(iVar11 + iVar6 * 2)) {
      iVar6 = iVar6 + 1;
    }
    else {
      sVar3 = FUN_02398b24((ushort)uVar5);
      if ((sVar3 != sVar1) && (uVar7 = uVar8 + 1, 0x20 < uVar8)) goto LAB_0239a660;
    }
    sVar1 = sVar1 + -1;
    uVar8 = uVar7;
  }
  iVar6 = 0;
  for (uVar8 = 0; uVar8 < 0x69; uVar8 = uVar8 + 1) {
    uVar5 = uVar7;
    if (uVar8 == *(ushort *)(iVar11 + iVar6 * 2)) {
      iVar6 = iVar6 + 1;
    }
    else {
      uVar9 = 1;
      for (uVar10 = 0; uVar10 < 9; uVar10 = uVar10 + 1) {
        FUN_02398ae4((ushort)uVar8,(short)uVar9);
        uVar4 = FUN_02398b24((ushort)uVar8);
        uVar7 = uVar5;
        if ((uVar4 != uVar9) && (uVar7 = uVar5 + 1, 0x20 < uVar5)) goto LAB_0239a660;
        uVar9 = ((uVar9 & 0x7f) << 0x11) >> 0x10;
        uVar5 = uVar7;
      }
    }
    uVar7 = uVar5;
  }
LAB_0239a660:
  if (uVar7 != 0) {
    *(ushort *)(*DAT_0239a68c + 0x312) = *(ushort *)(*DAT_0239a68c + 0x312) | 8;
  }
  return;
}



void FUN_0239a698(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  ushort *puVar4;
  uint uVar5;
  
  uVar5 = 0;
  uVar2 = DAT_0239a80c;
  puVar4 = DAT_0239a808;
  do {
    *puVar4 = (ushort)uVar2;
    uVar5 = uVar5 + 2;
    uVar2 = uVar2 - 1 & 0xffff;
    puVar4 = puVar4 + 1;
  } while (uVar5 < 0x2000);
  uVar5 = 0;
  uVar2 = DAT_0239a80c;
  puVar4 = DAT_0239a808;
  for (uVar3 = 0; uVar3 < 0x2000; uVar3 = uVar3 + 2) {
    uVar1 = uVar5;
    if ((*puVar4 != uVar2) && (uVar1 = uVar5 + 1, 0x20 < uVar5)) goto LAB_0239a7e4;
    puVar4 = puVar4 + 1;
    uVar2 = uVar2 - 1 & 0xffff;
    uVar5 = uVar1;
  }
  uVar3 = 0;
  uVar2 = DAT_0239a810;
  puVar4 = DAT_0239a808;
  do {
    *puVar4 = (ushort)uVar2;
    uVar3 = uVar3 + 2;
    uVar2 = ~uVar2 & 0xffff;
    puVar4 = puVar4 + 1;
  } while (uVar3 < 0x2000);
  uVar2 = DAT_0239a810;
  puVar4 = DAT_0239a808;
  for (uVar3 = 0; uVar3 < 0x2000; uVar3 = uVar3 + 2) {
    uVar1 = uVar5;
    if ((*puVar4 != uVar2) && (uVar1 = uVar5 + 1, 0x20 < uVar5)) goto LAB_0239a7e4;
    puVar4 = puVar4 + 1;
    uVar2 = ~uVar2 & 0xffff;
    uVar5 = uVar1;
  }
  uVar3 = 0;
  uVar2 = DAT_0239a814;
  puVar4 = DAT_0239a808;
  do {
    *puVar4 = (ushort)uVar2;
    uVar3 = uVar3 + 2;
    uVar2 = ~uVar2 & 0xffff;
    puVar4 = puVar4 + 1;
  } while (uVar3 < 0x2000);
  uVar3 = 0;
  uVar2 = DAT_0239a814;
  puVar4 = DAT_0239a808;
  while ((uVar1 = uVar5, uVar3 < 0x2000 && ((*puVar4 == uVar2 || (uVar1 = uVar5 + 1, uVar5 < 0x21)))
         )) {
    uVar3 = uVar3 + 2;
    puVar4 = puVar4 + 1;
    uVar2 = ~uVar2 & 0xffff;
    uVar5 = uVar1;
  }
LAB_0239a7e4:
  if (uVar1 == 0) {
    return;
  }
  *(ushort *)(*DAT_0239a818 + 0x312) = *(ushort *)(*DAT_0239a818 + 0x312) | 2;
  return;
}



void FUN_0239a81c(void)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  iVar5 = DAT_0239a9bc;
  iVar3 = DAT_0239a9b8;
  uVar8 = 0;
  for (uVar7 = 0; uVar6 = DAT_0239a9c0, iVar4 = DAT_0239a9b8, uVar7 < 3; uVar7 = uVar7 + 1) {
    for (uVar6 = 0; uVar6 < 0x1b; uVar6 = uVar6 + 1) {
      uVar1 = *(ushort *)(iVar3 + uVar6 * 4);
      uVar2 = *(ushort *)(iVar5 + uVar7 * 2) & *(ushort *)(iVar3 + uVar6 * 4 + 2);
      *(ushort *)(&Wifi_WS1_Region + uVar1) = uVar2;
      uVar9 = uVar8;
      if ((*(ushort *)(&Wifi_WS1_Region + uVar1) != uVar2) && (uVar9 = uVar8 + 1, 0x20 < uVar8))
      goto LAB_0239a98c;
      uVar8 = uVar9;
    }
  }
  uVar9 = 0;
  uVar7 = DAT_0239a9c0;
  do {
    *(ushort *)(&Wifi_WS1_Region + *(ushort *)(iVar4 + uVar9 * 4)) =
         (ushort)uVar7 & *(ushort *)(iVar4 + uVar9 * 4 + 2);
    iVar3 = DAT_0239a9b8;
    uVar7 = uVar7 + uVar6 & 0xffff;
    uVar9 = uVar9 + 1;
  } while (uVar9 < 0x1b);
  uVar7 = DAT_0239a9c0;
  for (uVar6 = 0; uVar6 < 0x1b; uVar6 = uVar6 + 1) {
    uVar9 = uVar8;
    if (((uint)*(ushort *)(&Wifi_WS1_Region + *(ushort *)(DAT_0239a9b8 + uVar6 * 4)) !=
         (uVar7 & *(ushort *)(DAT_0239a9b8 + uVar6 * 4 + 2))) && (uVar9 = uVar8 + 1, 0x20 < uVar8))
    goto LAB_0239a98c;
    uVar7 = uVar7 + DAT_0239a9c0 & 0xffff;
    uVar8 = uVar9;
  }
  uVar7 = 0;
  while ((uVar9 = uVar8, uVar7 < 0x1b &&
         ((uVar1 = *(ushort *)(iVar3 + uVar7 * 4), *(short *)(&Wifi_WS1_Region + uVar1) = 0,
          *(short *)(&Wifi_WS1_Region + uVar1) == 0 || (uVar9 = uVar8 + 1, uVar8 < 0x21))))) {
    uVar7 = uVar7 + 1;
    uVar8 = uVar9;
  }
LAB_0239a98c:
  if (uVar9 != 0) {
    *(ushort *)(*DAT_0239a9c4 + 0x312) = *(ushort *)(*DAT_0239a9c4 + 0x312) | 1;
  }
  return;
}



void FUN_0239a9c8(void)

{
  func_0x033ab364(0x1000000);
  func_0x033ab458(0x1000000,0);
  return;
}



void FUN_0239a9f0(void)

{
  func_0x033ab458(0x1000000,DAT_0239aa18);
  func_0x033ab3a0(0x1000000);
  return;
}



undefined4 FUN_0239aa1c(short *param_1)

{
  undefined4 uVar1;
  
  if (((*param_1 == 0) || ((**(ushort **)(param_1 + 4) & 1) == 0)) ||
     ((((uint)*(ushort **)(param_1 + 4) & DAT_0239aa7c) >> 1 | 0x8000) == (uint)*DAT_0239aa80)) {
    uVar1 = 0;
  }
  else {
    FUN_023a07e4(param_1);
    uVar1 = 1;
  }
  return uVar1;
}



void FUN_0239aa84(void)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  ushort *puVar4;
  int iVar5;
  
  puVar4 = DAT_0239aae0;
  uVar3 = DAT_0239aadc;
  iVar5 = *DAT_0239aad8;
  uVar1 = *(ushort *)(iVar5 + 0x4a6);
  if (uVar1 != DAT_0239aadc) {
    uVar2 = *DAT_0239aae0;
    *DAT_0239aae0 = uVar1;
    *DAT_0239aae4 = *DAT_0239aae4 | 0x80;
    *puVar4 = uVar2;
    *(short *)(iVar5 + 0x4a6) = (short)uVar3;
  }
  return;
}



void FUN_0239aafc(uint param_1,undefined2 *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *DAT_0239abd8;
  iVar2 = *(int *)(iVar1 + 0x2f0) + param_1 * 0x1c;
  if (*(short *)(*(int *)(iVar1 + 0x2f0) + param_1 * 0x1c) == 0) {
    *(short *)(iVar1 + 0x504) = *(short *)(iVar1 + 0x504) + 1;
  }
  func_0x033adb48(0,iVar2,0x1a);
  *(ushort *)(*DAT_0239abd8 + 0x50c) =
       *(ushort *)(*DAT_0239abd8 + 0x50c) & ~(ushort)(1 << (param_1 & 0xff));
  FUN_0239b3d4(param_1 & 0xffff,0);
  FUN_0239b370(param_1);
  FUN_02399054((undefined2 *)(iVar2 + 4),param_2);
  *(short *)(iVar2 + 0x14) = (short)DAT_0239abdc;
  *(undefined2 *)(iVar2 + 0x10) = *(undefined2 *)(*DAT_0239abd8 + 0x37a);
  *(undefined2 *)(iVar2 + 0x18) = *(undefined2 *)(iVar2 + 0x1a);
  FUN_0239b450(param_1 & 0xffff,0x20);
  return;
}



void FUN_0239abe0(void)

{
  ushort uVar1;
  int iVar2;
  undefined2 *puVar3;
  int iVar4;
  uint uVar5;
  
  iVar2 = *DAT_0239ac6c;
  iVar4 = *(int *)(iVar2 + 0x2f0);
  puVar3 = (undefined2 *)(iVar2 + DAT_0239ac70);
  uVar1 = *(ushort *)(iVar2 + 0x2f6);
  for (uVar5 = 1; uVar5 < uVar1; uVar5 = uVar5 + 1) {
    func_0x033adb48(0,uVar5 * 0x1c + iVar4,0x1a);
  }
  *puVar3 = 1;
  puVar3[1] = 0;
  puVar3[2] = 1;
  puVar3[3] = (short)DAT_0239ac74;
  puVar3[6] = 0;
  puVar3[4] = 0;
  puVar3[7] = 1;
  return;
}



void FUN_0239ac78(void)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *(int *)(*DAT_0239ad20 + 0x2f0);
  uVar3 = (uint)*(ushort *)(*DAT_0239ad20 + 0x2f6);
  func_0x033adb48(0,iVar4,uVar3 * 0x1c);
  func_0x033adb48(0,*DAT_0239ad20 + DAT_0239ad24,0x10);
  uVar1 = (undefined2)DAT_0239ad28;
  *(undefined2 *)(iVar4 + 0x1a) = uVar1;
  for (uVar2 = 1; uVar2 < uVar3; uVar2 = uVar2 + 1) {
    *(undefined2 *)(uVar2 * 0x1c + iVar4 + 0x1a) = uVar1;
  }
  FUN_0239aafc(0,DAT_0239ad2c);
  FUN_0239b450(0,0x40);
  return;
}



void FUN_0239ad30(int param_1)

{
  int *piVar1;
  
  piVar1 = DAT_0239ad64;
  *(undefined2 *)(*(int *)(*DAT_0239ad64 + 0x2f0) + param_1 * 0x1c) = 0;
  *(short *)(*piVar1 + 0x504) = *(short *)(*piVar1 + 0x504) + -1;
  return;
}



void FUN_0239ad68(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;
  undefined2 *puVar4;
  uint uVar5;
  uint uVar6;
  ushort *puVar7;
  int iVar8;
  
  iVar8 = *DAT_0239af2c;
  uVar1 = *(ushort *)(iVar8 + 0x504);
  uVar5 = 0;
  uVar6 = 1;
  puVar3 = *(ushort **)(iVar8 + 0x2f0);
  do {
    puVar7 = puVar3 + 0xe;
    if (*(ushort *)(iVar8 + 0x2f6) <= uVar6) {
      return;
    }
    if (*puVar7 == 0) {
LAB_0239af00:
      if (uVar1 <= uVar5) {
        return;
      }
    }
    else {
      uVar2 = puVar3[0x1a];
      if (((uVar2 == 0) || (uVar2 == DAT_0239af30)) || (puVar3[0x1a] = uVar2 - 1, puVar3[0x1a] != 0)
         ) {
LAB_0239aefc:
        uVar5 = uVar5 + 1;
        goto LAB_0239af00;
      }
      if (*puVar7 < 0x20) {
LAB_0239aee4:
        *puVar7 = 0;
        *(short *)(iVar8 + 0x504) = *(short *)(iVar8 + 0x504) + -1;
        goto LAB_0239aefc;
      }
      FUN_023a04bc(uVar6);
      if (*(short *)(iVar8 + 0x324) != 1) {
        if (uVar6 == *(ushort *)(iVar8 + 0x3a0)) {
          puVar4 = (undefined2 *)FUN_0239f558(puVar3 + 0x10,1);
          if (puVar4 != (undefined2 *)0x0) {
            *puVar4 = 1;
            FUN_023a02b8((int)puVar4);
            uVar5 = uVar5 + 1;
            goto LAB_0239af08;
          }
          func_0x033a9058(0x20);
          FUN_02399070();
          FUN_0239bee8(puVar3 + 0x10,1);
        }
LAB_0239aed4:
        FUN_0239b450(uVar6 & 0xffff,0x20);
        goto LAB_0239aee4;
      }
      if (*puVar7 < 0x21) goto LAB_0239aed4;
      *(ushort *)(*DAT_0239af2c + 0x50c) =
           *(ushort *)(*DAT_0239af2c + 0x50c) | (ushort)(1 << (uVar6 & 0xff));
      FUN_0239b3d4(uVar6 & 0xffff,0);
      FUN_0239b370(uVar6);
      puVar4 = (undefined2 *)FUN_0239f558(puVar3 + 0x10,1);
      if (puVar4 == (undefined2 *)0x0) {
        FUN_0239bee8(puVar3 + 0x10,1);
        goto LAB_0239aed4;
      }
      *puVar4 = 1;
      FUN_023a02b8((int)puVar4);
      uVar5 = uVar5 + 1;
    }
LAB_0239af08:
    uVar6 = uVar6 + 1;
    puVar3 = puVar7;
  } while( true );
}



void FUN_0239af34(int param_1)

{
  short sVar1;
  ushort uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  ushort *puVar6;
  
  sVar1 = FUN_0239b1b0(param_1);
  if (sVar1 == 0x40) {
    iVar5 = (uint)*(ushort *)(*DAT_0239afd8 + 0x3ac) + DAT_0239afdc;
    uVar3 = func_0x033ab364(0x1000000);
    if (param_1 == 0) {
      uVar4 = FUN_023983a0((ushort *)(iVar5 + 4));
      FUN_023983c0((ushort *)(iVar5 + 4),uVar4 & 0xfe);
    }
    else {
      uVar2 = FUN_0239b0d8(param_1);
      puVar6 = (ushort *)(iVar5 + 5 + (uint)(uVar2 >> 3));
      uVar4 = FUN_023983a0(puVar6);
      FUN_023983c0(puVar6,~(1 << (uVar2 & 7)) & uVar4 & 0xff);
    }
    func_0x033ab3a0(uVar3);
  }
  return;
}



void FUN_0239afe0(uint param_1)

{
  short sVar1;
  ushort uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  ushort *puVar6;
  
  sVar1 = FUN_0239b1b0(param_1);
  if ((sVar1 == 0x40) && (((uint)*(ushort *)(*DAT_0239b098 + 0x50c) & 1 << (param_1 & 0xff)) == 0))
  {
    iVar5 = (uint)*(ushort *)(*DAT_0239b098 + 0x3ac) + DAT_0239b09c;
    uVar3 = func_0x033ab364(0x1000000);
    if (param_1 == 0) {
      uVar4 = FUN_023983a0((ushort *)(iVar5 + 4));
      FUN_023983c0((ushort *)(iVar5 + 4),uVar4 & 0xff | 1);
    }
    else {
      uVar2 = FUN_0239b0d8(param_1);
      puVar6 = (ushort *)(iVar5 + 5 + (uint)(uVar2 >> 3));
      uVar4 = FUN_023983a0(puVar6);
      FUN_023983c0(puVar6,(uVar4 | 1 << (uVar2 & 7)) & 0xff);
    }
    func_0x033ab3a0(uVar3);
  }
  return;
}



int FUN_0239b0a0(int param_1)

{
  return param_1 * 0x1c + *(int *)(*DAT_0239b0b8 + 0x2f0);
}



undefined2 FUN_0239b0bc(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0239b0a0(param_1);
  return *(undefined2 *)(iVar1 + 0x16);
}



undefined2 FUN_0239b0d8(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0239b0a0(param_1);
  return *(undefined2 *)(iVar1 + 2);
}



undefined4 FUN_0239b0f4(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0239b0a0(param_1);
  if ((*(ushort *)(iVar1 + 0x10) & 2) == 0) {
    uVar2 = 10;
  }
  else {
    uVar2 = 0x14;
  }
  return uVar2;
}



undefined2 FUN_0239b11c(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0239b0a0(param_1);
  return *(undefined2 *)(iVar1 + 0x14);
}



undefined2 FUN_0239b138(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0239b0a0(param_1);
  return *(undefined2 *)(iVar1 + 0xe);
}



int FUN_0239b154(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0239b0a0(param_1);
  return iVar1 + 4;
}



uint FUN_0239b170(uint param_1)

{
  return (int)(uint)*(ushort *)(*DAT_0239b18c + 0x506) >> (param_1 & 0xff) & 1;
}



uint FUN_0239b190(uint param_1)

{
  return (int)(uint)*(ushort *)(*DAT_0239b1ac + 0x508) >> (param_1 & 0xff) & 1;
}



undefined2 FUN_0239b1b0(int param_1)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)FUN_0239b0a0(param_1);
  return *puVar1;
}



void FUN_0239b1cc(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *DAT_0239b238;
  FUN_0239af34(param_1);
  uVar1 = FUN_0239b0d8(param_1);
  iVar2 = FUN_0239b0a0(param_1);
  *(undefined2 *)(iVar2 + 2) = 0;
  *(ushort *)(iVar3 + 0x512) = *(ushort *)(iVar3 + 0x512) & ~(ushort)(1 << (uVar1 & 0xff));
  *(short *)(iVar3 + 0x510) = *(short *)(iVar3 + 0x510) + -1;
  if (*(short *)(iVar3 + 0x510) == 0) {
    FUN_02399250();
  }
  return;
}



uint FUN_0239b23c(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *DAT_0239b2e4 + DAT_0239b2e8;
  uVar1 = func_0x033ab364(0x1000000);
  uVar3 = 1;
  uVar2 = 2;
  while( true ) {
    if (0xf < uVar3) {
      func_0x033ab3a0(uVar1);
      return 0;
    }
    if ((*(ushort *)(iVar4 + 0xe) & uVar2) == 0) break;
    uVar3 = uVar3 + 1;
    uVar2 = uVar2 << 1;
  }
  *(ushort *)(iVar4 + 0xe) = *(ushort *)(iVar4 + 0xe) | (ushort)uVar2;
  *(short *)(iVar4 + 0xc) = *(short *)(iVar4 + 0xc) + 1;
  if (*(short *)(iVar4 + 0xc) == 1) {
    FUN_02399220();
  }
  iVar4 = FUN_0239b0a0(param_1);
  *(short *)(iVar4 + 2) = (short)uVar3;
  func_0x033ab3a0(uVar1);
  return uVar3;
}



void FUN_0239b2ec(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 * 0x1c + *(int *)(*DAT_0239b30c + 0x2f0);
  *(undefined2 *)(iVar1 + 0x18) = *(undefined2 *)(iVar1 + 0x1a);
  return;
}



void FUN_0239b310(int param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = FUN_0239b0a0(param_1);
  *(undefined2 *)(iVar1 + 0xe) = param_2;
  return;
}



void FUN_0239b328(int param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = FUN_0239b0a0(param_1);
  *(undefined2 *)(iVar1 + 0x14) = param_2;
  return;
}



void FUN_0239b340(int param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = FUN_0239b0a0(param_1);
  *(undefined2 *)(iVar1 + 0x10) = param_2;
  return;
}



void FUN_0239b358(int param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = FUN_0239b0a0(param_1);
  *(undefined2 *)(iVar1 + 0xc) = param_2;
  return;
}



void FUN_0239b370(uint param_1)

{
  *(ushort *)(*DAT_0239b390 + 0x508) =
       *(ushort *)(*DAT_0239b390 + 0x508) | (ushort)(1 << (param_1 & 0xff));
  return;
}



void FUN_0239b394(uint param_1)

{
  short sVar1;
  
  sVar1 = FUN_0239b1b0(param_1);
  if (sVar1 == 0x40) {
    *(ushort *)(*DAT_0239b3d0 + 0x508) =
         *(ushort *)(*DAT_0239b3d0 + 0x508) & ~(ushort)(1 << (param_1 & 0xff));
  }
  return;
}



void FUN_0239b3d4(uint param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *DAT_0239b428 + DAT_0239b42c;
  *(ushort *)(iVar1 + 2) =
       *(ushort *)(iVar1 + 2) & ~(ushort)(1 << (param_1 & 0xff)) |
       (ushort)(param_2 << (param_1 & 0xff));
  if ((*(ushort *)(iVar1 + 2) & ~*(ushort *)(iVar1 + 6)) == 0) {
    *DAT_0239b434 = 8;
  }
  else {
    *DAT_0239b430 = 8;
  }
  return;
}



void FUN_0239b438(int param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = FUN_0239b0a0(param_1);
  *(undefined2 *)(iVar1 + 10) = param_2;
  return;
}



void FUN_0239b450(uint param_1,uint param_2)

{
  int *piVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined2 *puVar5;
  
  uVar3 = func_0x033ab364(0x1000000);
  if (param_2 < 0x40) {
    FUN_0239b370(param_1);
    piVar1 = DAT_0239b518;
    *(ushort *)(*DAT_0239b518 + 0x50a) =
         *(ushort *)(*DAT_0239b518 + 0x50a) | (ushort)(1 << (param_1 & 0xff));
    if ((*(short *)(*piVar1 + 0x324) == 1) && (sVar2 = FUN_0239b1b0(param_1), sVar2 == 0x40)) {
      FUN_0239b1cc(param_1);
    }
  }
  else {
    *(ushort *)(*DAT_0239b518 + 0x50a) =
         *(ushort *)(*DAT_0239b518 + 0x50a) & ~(ushort)(1 << (param_1 & 0xff));
    uVar4 = FUN_0239b170(param_1);
    if (uVar4 != 0) {
      FUN_0239b394(param_1);
    }
  }
  puVar5 = (undefined2 *)FUN_0239b0a0(param_1);
  *puVar5 = (short)param_2;
  func_0x033ab3a0(uVar3);
  return;
}



void FUN_0239b51c(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar1 = *(ushort *)(param_1 + 2);
  iVar2 = FUN_0239b0a0((uint)uVar1);
  uVar3 = func_0x033ab364(0x1000000);
  if ((*(short *)(*DAT_0239b584 + 0x324) == 1) && (*(short *)(iVar2 + 0x16) == 1)) {
    FUN_0239af34((uint)uVar1);
  }
  *(short *)(iVar2 + 0x16) = *(short *)(iVar2 + 0x16) + -1;
  func_0x033ab3a0(uVar3);
  return;
}



void FUN_0239b588(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar3 = (uint)*(ushort *)(param_1 + 2);
  iVar1 = FUN_0239b0a0(uVar3);
  uVar2 = func_0x033ab364(0x1000000);
  if ((*(short *)(*DAT_0239b614 + 0x324) == 1) && (*(short *)(iVar1 + 0x16) == 0)) {
    FUN_0239afe0(uVar3);
  }
  *(short *)(iVar1 + 0x16) = *(short *)(iVar1 + 0x16) + 1;
  func_0x033ab3a0(uVar2);
  if (((uint)*(ushort *)(*DAT_0239b614 + 0x50c) & 1 << (uVar3 & 0xff)) == 0) {
    *(undefined2 *)(iVar1 + 0x18) = *(undefined2 *)(iVar1 + 0x1a);
  }
  return;
}



void FUN_0239b618(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *DAT_0239b678;
  uVar2 = func_0x033ab364(0x1000000);
  if (*(short *)(iVar1 + 0x188) == 0) {
    FUN_0239afe0(0);
  }
  func_0x033a862c(param_1,iVar1 + 0x180,param_2);
  func_0x033ab3a0(uVar2);
  return;
}



uint FUN_0239b67c(ushort *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  short *psVar6;
  uint uVar7;
  
  piVar1 = DAT_0239b7c0;
  iVar2 = *DAT_0239b7c0;
  if ((*param_1 & 1) == 0) {
    iVar4 = iVar2;
    if (*(ushort *)(iVar2 + 0x504) < 2) {
      uVar3 = 1;
    }
    else {
      uVar5 = 0;
      uVar7 = 0;
      psVar6 = *(short **)(iVar2 + 0x2f0);
      for (uVar3 = 1; uVar3 < *(ushort *)(iVar2 + 0x2f6); uVar3 = uVar3 + 1) {
        if (psVar6[0xe] == 0) {
          if (uVar5 == 0) {
            uVar5 = uVar3;
          }
        }
        else {
          iVar4 = FUN_02398c80(psVar6 + 0x10,(short *)param_1);
          if (iVar4 != 0) {
            return uVar3;
          }
          uVar7 = uVar7 + 1;
          iVar4 = *piVar1;
          if (*(ushort *)(iVar4 + 0x504) <= uVar7) break;
        }
        psVar6 = psVar6 + 0xe;
      }
      if (uVar5 != 0) {
        uVar3 = uVar5;
      }
    }
    if (*(ushort *)(iVar4 + 0x2f6) <= uVar3) {
      psVar6 = *(short **)(iVar2 + 0x2f0);
      uVar5 = 0x10000;
      uVar3 = 0;
      for (uVar7 = 1; uVar7 < *(ushort *)(iVar2 + 0x2f6); uVar7 = uVar7 + 1) {
        if ((((ushort)psVar6[uVar7 * 0xe] < 0x30) && (psVar6[uVar7 * 0xe + 0xb] == 0)) &&
           ((ushort)psVar6[uVar7 * 0xe + 0xc] < uVar5)) {
          uVar3 = uVar7;
          uVar5 = (uint)(ushort)psVar6[uVar7 * 0xe + 0xc];
        }
      }
      if (uVar3 == 0) {
        return 0xff;
      }
    }
    FUN_0239aafc(uVar3,param_1);
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



uint FUN_0239b7c4(ushort *param_1)

{
  short *psVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  piVar2 = DAT_0239b868;
  if ((*param_1 & 1) == 0) {
    iVar4 = *DAT_0239b868;
    if (1 < *(ushort *)(iVar4 + 0x504)) {
      uVar3 = 0;
      psVar1 = *(short **)(iVar4 + 0x2f0);
      for (uVar5 = 1; uVar5 < *(ushort *)(iVar4 + 0x2f6); uVar5 = uVar5 + 1) {
        if (psVar1[0xe] != 0) {
          iVar4 = FUN_02398c80(psVar1 + 0x10,(short *)param_1);
          if (iVar4 != 0) {
            return uVar5;
          }
          uVar3 = uVar3 + 1;
          iVar4 = *piVar2;
          if (*(ushort *)(iVar4 + 0x504) <= uVar3) break;
        }
        psVar1 = psVar1 + 0xe;
      }
    }
    uVar3 = 0xff;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



undefined4 FUN_0239b8a0(void)

{
  uint uVar1;
  
  uVar1 = 0;
  while( true ) {
    if (0x27ff < uVar1) {
      return 1;
    }
    if ((*DAT_0239b8d0 & 1) == 0) break;
    uVar1 = uVar1 + 1;
  }
  return 0;
}



void FUN_0239b8d4(void)

{
  do {
    do {
    } while ((*DAT_0239b908 & 1) != 0);
  } while ((*DAT_0239b904 == 6) || (*DAT_0239b904 == 5));
  return;
}



void FUN_0239b90c(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int local_c;
  
  local_c = 1;
  uVar1 = func_0x033b6d70((uint)(param_1 * DAT_0239b974) >> 6,1000);
  func_0x033acfa0(*DAT_0239b978 + DAT_0239b97c,uVar1,0,param_2,&local_c);
  do {
  } while (local_c != 0);
  return;
}



void FUN_0239b9ac(void)

{
  *(undefined2 *)(*DAT_0239b9c4 + 0x3fc) = 0;
  return;
}



void FUN_0239ba38(void)

{
  func_0x033adb48(0,*DAT_0239ba6c + 0x3d8,0x20);
  return;
}



undefined4 FUN_0239ba70(int param_1)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  ushort *puVar4;
  uint uVar5;
  int iVar6;
  ushort *puVar7;
  uint uVar8;
  
  iVar6 = *DAT_0239bb98;
  iVar2 = func_0x033a8500(iVar6 + 0x15c,*(ushort *)(iVar6 + 0x3b8) + 0x3e);
  if (iVar2 == 0) {
    FUN_02398034(1);
    uVar3 = 0;
  }
  else {
    *(undefined2 *)(iVar2 + 0xc) = 0x8d;
    sVar1 = func_0x033b6b64(*(ushort *)(iVar6 + 0x3b8) + 1,2);
    *(short *)(iVar2 + 0xe) = sVar1 + 0x16;
    FUN_023983c0((ushort *)(iVar2 + 0x1f),*(ushort *)(param_1 + 0x12) & 0xff);
    FUN_023983c0((ushort *)(iVar2 + 0x1e),*(ushort *)(param_1 + 0xe) & 0xff);
    FUN_02399054((undefined2 *)(iVar2 + 0x2e),(undefined2 *)(param_1 + 0x1e));
    *(undefined2 *)(iVar2 + 0x16) = *(undefined2 *)(iVar6 + 0x3b8);
    if (*(ushort *)(iVar2 + 0x16) != 0) {
      if ((*(ushort *)(iVar6 + 0x3ba) & 1) == 0) {
        func_0x033adb60(*(undefined4 *)(iVar6 + 0x3b4),iVar2 + 0x3c,*(ushort *)(iVar2 + 0x16) + 1);
      }
      else {
        puVar4 = *(ushort **)(iVar6 + 0x3b4);
        puVar7 = (ushort *)(iVar2 + 0x3c);
        for (uVar8 = 0; puVar4 = (ushort *)((int)puVar4 + 1), uVar8 < *(ushort *)(iVar2 + 0x16);
            uVar8 = uVar8 + 1) {
          uVar5 = FUN_023983a0(puVar4);
          FUN_023983c0(puVar7,uVar5);
          puVar7 = (ushort *)((int)puVar7 + 1);
        }
      }
    }
    func_0x033a8a4c(*DAT_0239bb98 + 0x15c,iVar2);
    uVar3 = 1;
  }
  return uVar3;
}



bool FUN_0239bb9c(void)

{
  int iVar1;
  
  iVar1 = func_0x033a8500(*DAT_0239bc00 + 0x15c,0x10);
  if (iVar1 != 0) {
    *(undefined2 *)(iVar1 + 0xc) = 0x8c;
    *(undefined2 *)(iVar1 + 0xe) = 0;
    func_0x033a8a4c(*DAT_0239bc00 + 0x15c);
  }
  else {
    FUN_02398034(1);
  }
  return iVar1 != 0;
}



bool FUN_0239bc04(undefined2 *param_1)

{
  int iVar1;
  
  iVar1 = func_0x033a8500(*DAT_0239bc7c + 0x15c,0x16);
  if (iVar1 != 0) {
    *(undefined2 *)(iVar1 + 0xc) = 0x8b;
    *(undefined2 *)(iVar1 + 0xe) = 3;
    FUN_02399054((undefined2 *)(iVar1 + 0x10),param_1);
    func_0x033a8a4c(*DAT_0239bc7c + 0x15c,iVar1);
  }
  else {
    FUN_02398034(1);
  }
  return iVar1 != 0;
}



bool FUN_0239bc80(undefined2 *param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = func_0x033a8500(*DAT_0239bcf8 + 0x15c,0x18);
  if (iVar1 != 0) {
    *(undefined2 *)(iVar1 + 0xc) = 0x88;
    *(undefined2 *)(iVar1 + 0xe) = 4;
    FUN_02399054((undefined2 *)(iVar1 + 0x10),param_1);
    *(undefined2 *)(iVar1 + 0x16) = param_2;
    func_0x033a8a4c(*DAT_0239bcf8 + 0x15c,iVar1);
  }
  else {
    FUN_02398034(1);
  }
  return iVar1 != 0;
}



undefined4 FUN_0239bcfc(undefined2 *param_1,undefined2 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = func_0x033a8500(*DAT_0239bde8 + 0x15c,0x3a);
  if (iVar1 == 0) {
    FUN_02398034(1);
    uVar2 = 0;
  }
  else {
    *(undefined2 *)(iVar1 + 0xc) = 0x87;
    *(undefined2 *)(iVar1 + 0xe) = 0x15;
    FUN_02399054((undefined2 *)(iVar1 + 0x10),param_1);
    *(undefined2 *)(iVar1 + 0x16) = param_2;
    uVar3 = FUN_023983a0((ushort *)(param_3 + 1));
    *(short *)(iVar1 + 0x18) = (short)uVar3;
    for (uVar3 = 0; (uVar3 < *(ushort *)(iVar1 + 0x18) && (uVar3 < 0x20)); uVar3 = uVar3 + 1) {
      uVar4 = FUN_023983a0((ushort *)(param_3 + 2 + uVar3));
      FUN_023983c0((ushort *)(iVar1 + 0x1a + uVar3),uVar4);
    }
    for (; uVar3 < 0x20; uVar3 = uVar3 + 1) {
      FUN_023983c0((ushort *)(iVar1 + 0x1a + uVar3),0);
    }
    func_0x033a8a4c(*DAT_0239bde8 + 0x15c,iVar1);
    uVar2 = 1;
  }
  return uVar2;
}



undefined4 FUN_0239bdec(undefined2 *param_1,ushort param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = func_0x033a8500(*DAT_0239bee0 + 0x15c,0x3a);
  if (iVar1 == 0) {
    FUN_02398034(1);
    uVar2 = 0;
  }
  else {
    *(undefined2 *)(iVar1 + 0xc) = 0x86;
    *(undefined2 *)(iVar1 + 0xe) = 0x15;
    FUN_02399054((undefined2 *)(iVar1 + 0x10),param_1);
    *(ushort *)(iVar1 + 0x16) = param_2 & (ushort)DAT_0239bee4;
    uVar3 = FUN_023983a0((ushort *)(param_3 + 1));
    *(short *)(iVar1 + 0x18) = (short)uVar3;
    for (uVar3 = 0; (uVar3 < *(ushort *)(iVar1 + 0x18) && (uVar3 < 0x20)); uVar3 = uVar3 + 1) {
      uVar4 = FUN_023983a0((ushort *)(param_3 + 2 + uVar3));
      FUN_023983c0((ushort *)(iVar1 + 0x1a + uVar3),uVar4);
    }
    for (; uVar3 < 0x20; uVar3 = uVar3 + 1) {
      FUN_023983c0((ushort *)(iVar1 + 0x1a + uVar3),0);
    }
    func_0x033a8a4c(*DAT_0239bee0 + 0x15c,iVar1);
    uVar2 = 1;
  }
  return uVar2;
}



bool FUN_0239bee8(undefined2 *param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = func_0x033a8500(*DAT_0239bf60 + 0x15c,0x18);
  if (iVar1 != 0) {
    *(undefined2 *)(iVar1 + 0xc) = 0x85;
    *(undefined2 *)(iVar1 + 0xe) = 4;
    FUN_02399054((undefined2 *)(iVar1 + 0x10),param_1);
    *(undefined2 *)(iVar1 + 0x16) = param_2;
    func_0x033a8a4c(*DAT_0239bf60 + 0x15c,iVar1);
  }
  else {
    FUN_02398034(1);
  }
  return iVar1 != 0;
}



bool FUN_0239bf64(undefined2 *param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = func_0x033a8500(*DAT_0239bfdc + 0x15c,0x18);
  if (iVar1 != 0) {
    *(undefined2 *)(iVar1 + 0xc) = 0x84;
    *(undefined2 *)(iVar1 + 0xe) = 4;
    FUN_02399054((undefined2 *)(iVar1 + 0x10),param_1);
    *(undefined2 *)(iVar1 + 0x16) = param_2;
    func_0x033a8a4c(*DAT_0239bfdc + 0x15c,iVar1);
  }
  else {
    FUN_02398034(1);
  }
  return iVar1 != 0;
}



void FUN_0239bfe0(void)

{
  int iVar1;
  
  iVar1 = *DAT_0239c02c;
  *(ushort *)(iVar1 + 0x3fc) = *(ushort *)(iVar1 + 0x3fc) & 0xfffe;
  func_0x033a8a4c(iVar1 + 0x1d4,*(undefined4 *)(iVar1 + 0x3f8));
  if (*(short *)(iVar1 + 0x1dc) != 0) {
    func_0x033a81e8(2,0xb);
  }
  return;
}



void FUN_0239c080(void)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  short *psVar6;
  bool bVar7;
  
  iVar2 = *DAT_0239c2f0;
  psVar6 = (short *)(iVar2 + 0x3d8);
  switch(*(undefined2 *)(iVar2 + 0x3d8)) {
  case 0x80:
    *(undefined2 *)(iVar2 + 0x3ec) = 0;
    uVar1 = FUN_02398b24(0x13);
    *(undefined2 *)(iVar2 + 0x3e6) = uVar1;
    uVar1 = FUN_02398b24(0x35);
    *(undefined2 *)(iVar2 + 1000) = uVar1;
    FUN_02399d70((uint)*(ushort *)(*(int *)(iVar2 + 0x3f0) + 0x12),
                 (uint)*(ushort *)(*(int *)(iVar2 + 0x3f0) + 0x14));
    *(undefined2 *)(iVar2 + 0x324) = 4;
    *(undefined2 *)(iVar2 + 0x3ee) = 0;
    goto LAB_0239c104;
  case 0x81:
LAB_0239c104:
    *(undefined4 *)(iVar2 + 0x3dc) = 0;
    *(undefined4 *)(iVar2 + 0x3e0) = 0;
    uVar5 = FUN_023983a0((ushort *)
                         (*(int *)(iVar2 + 0x3f0) + 0x18 + (uint)*(ushort *)(iVar2 + 0x3ec)));
    if ((uVar5 == 0) || (0xf < *(ushort *)(iVar2 + 0x3ec))) {
      *psVar6 = 0x84;
    }
    else {
      iVar3 = FUN_023a45bc((uint *)0x0);
      bVar7 = iVar3 != 0;
      if (bVar7) {
        iVar3 = 0xe;
      }
      if (bVar7) {
        *(short *)(iVar2 + 0x3ee) = (short)iVar3;
        *psVar6 = 0x84;
      }
      else {
        if (*psVar6 == 0x80) {
          FUN_023995a4(uVar5 & 0xffff,0);
          func_0x033a8adc();
          *(undefined2 *)(iVar2 + 0x3e4) = *DAT_0239c2f4;
          FUN_02399414(0x8000);
        }
        else {
          FUN_023995a4(uVar5 & 0xffff,0);
        }
        *psVar6 = 0x82;
        FUN_023985b0((uint)*(ushort *)(*(int *)(iVar2 + 0x3f0) + 0x16),DAT_0239c2f8);
LAB_0239c1c4:
        *(int *)(iVar2 + 0x3dc) = *(int *)(iVar2 + 0x3dc) + 1;
        if ((*DAT_0239c2fc & 1) != 0) {
          *(int *)(iVar2 + 0x3e0) = *(int *)(iVar2 + 0x3e0) + 100;
        }
      }
    }
    break;
  case 0x82:
    goto LAB_0239c1c4;
  case 0x83:
    uVar5 = FUN_023983a0((ushort *)
                         (*(int *)(iVar2 + 0x3f0) + 0x18 + (uint)*(ushort *)(iVar2 + 0x3ec)));
    uVar4 = 0;
    if ((*(int *)(iVar2 + 0x3dc) != 0) && (*(int *)(iVar2 + 0x3e0) != 0)) {
      iVar3 = func_0x033b6d70();
      uVar4 = iVar3 + 1;
      if (100 < uVar4) {
        uVar4 = 100;
      }
    }
    *(ushort *)(*(int *)(iVar2 + 0x3f4) + (uint)*(ushort *)(iVar2 + 0x3ec) * 2 + 8) =
         (ushort)uVar5 | (ushort)(uVar4 << 8);
    *(short *)(iVar2 + 0x3ec) = *(short *)(iVar2 + 0x3ec) + 1;
    *psVar6 = 0x81;
    break;
  case 0x84:
    func_0x033a8fa0();
    *(undefined2 *)(iVar2 + 0x324) = *(undefined2 *)(*DAT_0239c2f0 + 0x302);
    FUN_02398ae4(0x13,*(undefined2 *)(iVar2 + 0x3e6));
    FUN_02398ae4(0x35,*(undefined2 *)(iVar2 + 1000));
    FUN_02399414(*(undefined2 *)(iVar2 + 0x3e4));
    *(undefined2 *)(*(int *)(iVar2 + 0x3f4) + 4) = *(undefined2 *)(iVar2 + 0x3ee);
    *psVar6 = 0;
    for (uVar5 = (uint)*(ushort *)(iVar2 + 0x3ec); uVar5 < 0x10; uVar5 = uVar5 + 1) {
      *(undefined2 *)(*(int *)(iVar2 + 0x3f4) + uVar5 * 2 + 8) = 0;
    }
    FUN_0239bfe0();
  }
  if (*psVar6 != 0) {
    func_0x033a81e8(2,5);
  }
  return;
}



void FUN_0239c33c(void)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  
  iVar1 = *DAT_0239c3e8;
  puVar3 = (undefined2 *)(iVar1 + 0x3d8);
  if (*(short *)(iVar1 + 0x3d8) == 0x60) {
    iVar2 = FUN_0239fad4((undefined2 *)(*(int *)(iVar1 + 0x3f0) + 0x10));
    if (iVar2 == 0) {
      *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 4) = 8;
      *puVar3 = 99;
      func_0x033a81e8(2,4);
    }
    else {
      *puVar3 = 0x61;
      FUN_023a02b8(iVar2);
      FUN_023985b0((uint)*(ushort *)(*(int *)(iVar1 + 0x3f0) + 0x18),DAT_0239c3ec);
    }
  }
  else if (*(short *)(iVar1 + 0x3d8) == 99) {
    FUN_023a0628(1);
    FUN_023a02d8(1,0);
    *puVar3 = 0;
    FUN_0239bfe0();
  }
  return;
}



void FUN_0239c42c(void)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  
  iVar1 = *DAT_0239c4e0;
  puVar3 = (undefined2 *)(iVar1 + 0x3d8);
  if (*(short *)(iVar1 + 0x3d8) == 0x50) {
    iVar2 = FUN_0239fb8c((undefined2 *)(*(int *)(iVar1 + 0x3f0) + 0x10));
    if (iVar2 == 0) {
      *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 4) = 8;
      *puVar3 = 0x53;
      func_0x033a81e8(2,3);
    }
    else {
      *puVar3 = 0x51;
      FUN_023a02b8(iVar2);
      FUN_023985b0((uint)*(ushort *)(*(int *)(iVar1 + 0x3f0) + 0x18),DAT_0239c4e4);
    }
  }
  else if (*(short *)(iVar1 + 0x3d8) == 0x53) {
    FUN_023a0598(1);
    FUN_023a0628(1);
    FUN_023a02d8(1,0);
    *puVar3 = 0;
    FUN_0239bfe0();
  }
  return;
}



void FUN_0239c524(void)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  
  iVar1 = *DAT_0239c5f8;
  puVar3 = (undefined2 *)(iVar1 + 0x3d8);
  if (*(short *)(iVar1 + 0x3d8) == 0x30) {
    iVar2 = FUN_0239f5dc((undefined2 *)(*(int *)(iVar1 + 0x3f0) + 0x10),0);
    if (iVar2 == 0) {
      *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 4) = 8;
      *puVar3 = 0x35;
      func_0x033a81e8(2,2);
    }
    else {
      *(undefined2 *)(iVar2 + 0x2c) = *(undefined2 *)(*(int *)(iVar1 + 0x3f0) + 0x16);
      *(undefined2 *)(iVar2 + 0x2e) = 1;
      *(undefined2 *)(iVar2 + 0x30) = 0;
      *puVar3 = 0x31;
      FUN_023a02b8(iVar2);
      FUN_023985b0((uint)*(ushort *)(*(int *)(iVar1 + 0x3f0) + 0x18),DAT_0239c5fc);
    }
  }
  else if (*(short *)(iVar1 + 0x3d8) == 0x35) {
    FUN_023a0598(1);
    FUN_023a0628(1);
    FUN_023a02d8(1,0);
    *puVar3 = 0;
    FUN_0239bfe0();
  }
  return;
}



undefined4 FUN_0239ca08(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  iVar1 = *DAT_0239cba0;
  *(undefined2 *)(param_2 + 2) = 1;
  if ((*(short *)(iVar1 + 0x302) == 1) || (*(short *)(iVar1 + 0x302) == 0)) {
    if (*(short *)(iVar1 + 800) == 0x20) {
      if (*(ushort *)(param_1 + 0x10) < 0x21) {
        if (*(ushort *)(param_1 + 0x10) == 0) {
          uVar2 = 5;
        }
        else if (*(ushort *)(param_1 + 0x32) < 10) {
          uVar2 = 5;
        }
        else if (*(ushort *)(param_1 + 0x32) < 0x3e9) {
          if (*(ushort *)(param_1 + 0x34) == 0) {
            uVar2 = 5;
          }
          else if (*(ushort *)(param_1 + 0x34) < 0x100) {
            if ((*(ushort *)(param_1 + 0x36) & DAT_0239cba4) == 0) {
              uVar3 = FUN_02398c60((uint)*(ushort *)(param_1 + 0x36));
              if (uVar3 == 0) {
                uVar2 = 5;
              }
              else if (*(ushort *)(param_1 + 0x38) == 0) {
                uVar2 = 5;
              }
              else if ((*(ushort *)(param_1 + 0x38) & 0xf000) == 0) {
                if (*(ushort *)(param_1 + 0x3a) == 0) {
                  uVar2 = 5;
                }
                else if ((*(ushort *)(param_1 + 0x3a) & 0xf000) == 0) {
                  if (*(ushort *)(param_1 + 0x3c) < 0x81) {
                    iVar4 = FUN_023a45bc((uint *)0x0);
                    if (iVar4 == 0) {
                      if (*(short *)(iVar1 + 0x302) == 0) {
                        FUN_02399b84(DAT_0239cba8);
                      }
                      else {
                        FUN_02399b84((ushort *)(iVar1 + 0x2f8));
                      }
                      FUN_02399a68((uint)*(ushort *)(param_1 + 0x10),(ushort *)(param_1 + 0x12));
                      FUN_02399a08((uint)*(ushort *)(param_1 + 0x32));
                      FUN_023999bc((uint)*(ushort *)(param_1 + 0x34));
                      FUN_023995a4((uint)*(ushort *)(param_1 + 0x36),0);
                      FUN_0239955c((ushort *)(param_1 + 0x38));
                      FUN_023991d4((uint)*(ushort *)(param_1 + 0x3c),param_1 + 0x3e);
                      *(undefined2 *)(iVar1 + 0x3bc) = 0;
                      func_0x033a8adc();
                      uVar2 = 0;
                    }
                    else {
                      uVar2 = 0xe;
                    }
                  }
                  else {
                    uVar2 = 5;
                  }
                }
                else {
                  uVar2 = 5;
                }
              }
              else {
                uVar2 = 5;
              }
            }
            else {
              uVar2 = 5;
            }
          }
          else {
            uVar2 = 5;
          }
        }
        else {
          uVar2 = 5;
        }
      }
      else {
        uVar2 = 5;
      }
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0xb;
  }
  return uVar2;
}



undefined4 FUN_0239cbac(int param_1,int param_2)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  piVar2 = DAT_0239cca4;
  iVar3 = *DAT_0239cca4;
  *(undefined2 *)(param_2 + 2) = 1;
  sVar1 = *(short *)(*piVar2 + 0x302);
  if (sVar1 == 0) {
    uVar4 = 0xb;
  }
  else if ((sVar1 == 1) || ((*(ushort *)(param_1 + 0x10) & 1) == 0)) {
    if (*(short *)(*piVar2 + 800) == 0x40) {
      iVar5 = FUN_0239fc38((undefined2 *)(param_1 + 0x10),*(undefined2 *)(param_1 + 0x16));
      if (iVar5 == 0) {
        uVar4 = 8;
      }
      else {
        *(int *)(iVar3 + 0x3f0) = param_1;
        *(int *)(iVar3 + 0x3f4) = param_2;
        *(undefined2 *)(iVar3 + 0x3d8) = 0x71;
        if ((*(ushort *)(param_1 + 0x10) & 1) == 0) {
          FUN_023a0458((ushort *)(param_1 + 0x10));
          FUN_023a02b8(iVar5);
        }
        else {
          FUN_0239b618(*DAT_0239cca4 + 0x15c,iVar5 + -0x10);
          if ((*(ushort *)(*DAT_0239cca4 + 0x506) & ~*(ushort *)(*DAT_0239cca4 + 0x50a)) == 0) {
            FUN_023a1180();
          }
        }
        uVar4 = 0x80;
      }
    }
    else {
      uVar4 = 1;
    }
  }
  else {
    uVar4 = 5;
  }
  return uVar4;
}



undefined4 FUN_0239cca8(int param_1,int param_2)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *DAT_0239cd6c;
  *(undefined2 *)(param_2 + 2) = 3;
  if ((*(short *)(iVar3 + 0x302) == 3) || (*(short *)(iVar3 + 0x302) == 2)) {
    if (*(ushort *)(iVar3 + 800) < 0x30) {
      uVar2 = 1;
    }
    else if ((*(ushort *)(param_1 + 0x10) & 1) == 0) {
      uVar1 = *(ushort *)(param_1 + 0x16);
      if (uVar1 == 0) {
        uVar2 = 5;
      }
      else if (uVar1 < 0x100) {
        if (*(ushort *)(param_1 + 0x18) < 0x7d1) {
          if (*(ushort *)(param_1 + 0x18) < 10) {
            uVar2 = 5;
          }
          else {
            *(ushort *)(iVar3 + 0x388) = uVar1;
            *(undefined2 *)(iVar3 + 0x38a) = *(undefined2 *)(param_1 + 0x16);
            *(int *)(iVar3 + 0x3f0) = param_1;
            *(int *)(iVar3 + 0x3f4) = param_2;
            *(undefined2 *)(iVar3 + 0x3d8) = 0x60;
            FUN_0239c33c();
            uVar2 = 0x80;
          }
        }
        else {
          uVar2 = 5;
        }
      }
      else {
        uVar2 = 5;
      }
    }
    else {
      uVar2 = 5;
    }
  }
  else {
    uVar2 = 0xb;
  }
  return uVar2;
}



undefined4 FUN_0239cd70(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *DAT_0239ce4c;
  *(undefined2 *)(param_2 + 2) = 3;
  if ((*(short *)(iVar2 + 0x302) == 3) || (*(short *)(iVar2 + 0x302) == 2)) {
    if (*(ushort *)(iVar2 + 800) < 0x30) {
      uVar1 = 1;
    }
    else if ((*(ushort *)(param_1 + 0x10) & 1) == 0) {
      if (*(ushort *)(param_1 + 0x16) == 0) {
        uVar1 = 5;
      }
      else if (*(ushort *)(param_1 + 0x16) < 0x100) {
        if (*(ushort *)(param_1 + 0x18) < 0x7d1) {
          if (*(ushort *)(param_1 + 0x18) < 10) {
            uVar1 = 5;
          }
          else {
            func_0x033a9058(0x30);
            FUN_02399070();
            *(undefined2 *)(iVar2 + 0x388) = *(undefined2 *)(param_1 + 0x16);
            *(undefined2 *)(iVar2 + 0x38a) = *(undefined2 *)(param_1 + 0x16);
            *(int *)(iVar2 + 0x3f0) = param_1;
            *(int *)(iVar2 + 0x3f4) = param_2;
            *(undefined2 *)(iVar2 + 0x3d8) = 0x50;
            FUN_0239c42c();
            uVar1 = 0x80;
          }
        }
        else {
          uVar1 = 5;
        }
      }
      else {
        uVar1 = 5;
      }
    }
    else {
      uVar1 = 5;
    }
  }
  else {
    uVar1 = 0xb;
  }
  return uVar1;
}



undefined4 FUN_0239ce50(int param_1,int param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  *(undefined2 *)(param_2 + 2) = 4;
  uVar4 = (uint)*(ushort *)(*DAT_0239cf74 + 0x302);
  if (((uVar4 == 3) || (uVar4 == 2)) || (uVar4 == 1)) {
    if (*(ushort *)(*DAT_0239cf74 + 800) < 0x30) {
      uVar2 = 1;
    }
    else if (((uVar4 + DAT_0239cf78 & 0xffff) < 2) && ((*(ushort *)(param_1 + 0x10) & 1) != 0)) {
      uVar2 = 5;
    }
    else {
      FUN_02399054((undefined2 *)(param_2 + 6),(undefined2 *)(param_1 + 0x10));
      iVar3 = FUN_0239f558((undefined2 *)(param_2 + 6),*(undefined2 *)(param_1 + 0x16));
      piVar1 = DAT_0239cf74;
      if (iVar3 == 0) {
        uVar2 = 8;
      }
      else {
        *(int *)(*DAT_0239cf74 + 0x3f0) = param_1;
        *(int *)(*piVar1 + 0x3f4) = param_2;
        *(undefined2 *)(*piVar1 + 0x3d8) = 0x41;
        if ((*(ushort *)(param_1 + 0x10) & 1) == 0) {
          FUN_023a0458((ushort *)(param_1 + 0x10));
          FUN_023a02b8(iVar3);
        }
        else {
          FUN_0239b618(*piVar1 + 0x15c,iVar3 + -0x10);
          if ((*(ushort *)(*DAT_0239cf74 + 0x506) & ~*(ushort *)(*DAT_0239cf74 + 0x50a)) == 0) {
            FUN_023a1180();
          }
        }
        uVar2 = 0x80;
      }
    }
  }
  else {
    uVar2 = 0xb;
  }
  return uVar2;
}



undefined4 FUN_0239cf7c(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *DAT_0239d04c;
  *(undefined2 *)(param_2 + 2) = 6;
  if ((*(short *)(iVar2 + 0x302) == 3) || (*(short *)(iVar2 + 0x302) == 2)) {
    if (*(ushort *)(iVar2 + 800) < 0x20) {
      uVar1 = 1;
    }
    else if ((*(ushort *)(param_1 + 0x10) & 1) == 0) {
      if (*(ushort *)(param_1 + 0x16) < 2) {
        if (*(ushort *)(param_1 + 0x18) < 0x7d1) {
          if (*(ushort *)(param_1 + 0x18) < 10) {
            uVar1 = 5;
          }
          else {
            func_0x033a9058(0x20);
            *(int *)(iVar2 + 0x3f0) = param_1;
            *(int *)(iVar2 + 0x3f4) = param_2;
            *(undefined2 *)(iVar2 + 0x3d8) = 0x30;
            *(undefined2 *)(param_2 + 0xe) = *(undefined2 *)(*(int *)(iVar2 + 0x3f0) + 0x16);
            FUN_02399054((undefined2 *)(param_2 + 8),(undefined2 *)(*(int *)(iVar2 + 0x3f0) + 0x10))
            ;
            FUN_0239c524();
            uVar1 = 0x80;
          }
        }
        else {
          uVar1 = 5;
        }
      }
      else {
        uVar1 = 5;
      }
    }
    else {
      uVar1 = 5;
    }
  }
  else {
    uVar1 = 0xb;
  }
  return uVar1;
}



undefined4 FUN_0239d050(int param_1,int param_2)

{
  ushort uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = *DAT_0239d1f4;
  *(undefined2 *)(param_2 + 2) = 5;
  if ((*(short *)(iVar5 + 0x302) == 3) || (*(short *)(iVar5 + 0x302) == 2)) {
    if (*(ushort *)(iVar5 + 800) < 0x20) {
      uVar2 = 1;
    }
    else {
      func_0x033a9058(0x20);
      if ((*(ushort *)(param_1 + 0x18) & 1) == 0) {
        if (*(ushort *)(param_1 + 0x1e) == 0) {
          uVar2 = 5;
        }
        else if (*(ushort *)(param_1 + 0x1e) < 0x21) {
          if (*(ushort *)(param_1 + 0x46) < 10) {
            uVar2 = 5;
          }
          else if (*(ushort *)(param_1 + 0x46) < 0x3e9) {
            if (*(ushort *)(param_1 + 0x48) < 0x100) {
              if ((*(ushort *)(param_1 + 0x4a) & DAT_0239d1f8) == 0) {
                uVar3 = FUN_02398c60((uint)*(ushort *)(param_1 + 0x4a));
                if (uVar3 == 0) {
                  uVar2 = 5;
                }
                else {
                  uVar1 = *(ushort *)(param_1 + 0x42);
                  if ((uVar1 & 0xf000) == 0) {
                    if ((*(ushort *)(param_1 + 0x44) & 0xf000) == 0) {
                      if (uVar1 == 0) {
                        uVar2 = 5;
                      }
                      else if ((*(ushort *)(param_1 + 0x44) | uVar1) == 0) {
                        uVar2 = 5;
                      }
                      else if (*(ushort *)(param_1 + 0x10) < 0x7d1) {
                        iVar4 = FUN_023a45bc((uint *)0x0);
                        if (iVar4 == 0) {
                          if ((*(ushort *)(param_1 + 0x40) & 0x20) == 0) {
                            FUN_02399ddc(0);
                          }
                          FUN_02399b84((ushort *)(param_1 + 0x18));
                          FUN_02399a68((uint)*(ushort *)(param_1 + 0x1e),(ushort *)(param_1 + 0x20))
                          ;
                          FUN_02399a08((uint)*(ushort *)(param_1 + 0x46));
                          FUN_023995a4((uint)*(ushort *)(param_1 + 0x4a),0);
                          FUN_0239955c((ushort *)(param_1 + 0x42));
                          *(int *)(iVar5 + 0x3f0) = param_1;
                          *(int *)(iVar5 + 0x3f4) = param_2;
                          *(undefined2 *)(iVar5 + 0x3d8) = 0x20;
                          func_0x033a81e8(2,1);
                          uVar2 = 0x80;
                        }
                        else {
                          uVar2 = 0xe;
                        }
                      }
                      else {
                        uVar2 = 5;
                      }
                    }
                    else {
                      uVar2 = 5;
                    }
                  }
                  else {
                    uVar2 = 5;
                  }
                }
              }
              else {
                uVar2 = 5;
              }
            }
            else {
              uVar2 = 5;
            }
          }
          else {
            uVar2 = 5;
          }
        }
        else {
          uVar2 = 5;
        }
      }
      else {
        uVar2 = 5;
      }
    }
  }
  else {
    uVar2 = 0xb;
  }
  return uVar2;
}



undefined4 FUN_0239d1fc(int param_1,int param_2)

{
  short sVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  iVar5 = *DAT_0239d33c;
  *(short *)(iVar5 + 0x3dc) = *(short *)(param_2 + 2) + -3;
  *(undefined2 *)(param_2 + 2) = 3;
  sVar1 = *(short *)(iVar5 + 0x302);
  if (((sVar1 == 1) || (sVar1 == 3)) || (sVar1 == 2)) {
    if (*(ushort *)(*DAT_0239d33c + 800) < 0x20) {
      uVar2 = 1;
    }
    else if (*(ushort *)(param_1 + 0x16) < 0x21) {
      if (*(ushort *)(param_1 + 0x38) < 2) {
        uVar3 = FUN_023983a0((ushort *)(param_1 + 0x3a));
        if (uVar3 == 0) {
          uVar2 = 5;
        }
        else if (*(ushort *)(param_1 + 0x4a) < 0x3e9) {
          if (*(ushort *)(param_1 + 0x4a) < 10) {
            uVar2 = 5;
          }
          else if (*(ushort *)(param_1 + 0x4c) < 0x11) {
            uVar3 = 0;
            while ((uVar3 < 0x10 &&
                   (uVar4 = FUN_023983a0((ushort *)(param_1 + 0x3a + uVar3)), uVar4 != 0))) {
              uVar4 = FUN_02398c60(uVar4);
              if (uVar4 == 0) {
                return 5;
              }
              uVar3 = uVar3 + 1;
            }
            FUN_02399b84((ushort *)(param_1 + 0x10));
            FUN_02399a68((uint)*(ushort *)(param_1 + 0x16),(ushort *)(param_1 + 0x18));
            *(int *)(iVar5 + 0x3f0) = param_1;
            *(int *)(iVar5 + 0x3f4) = param_2;
            *(undefined2 *)(iVar5 + 0x3d8) = 0x10;
            func_0x033a81e8(2,0);
            uVar2 = 0x80;
          }
          else {
            uVar2 = 5;
          }
        }
        else {
          uVar2 = 5;
        }
      }
      else {
        uVar2 = 5;
      }
    }
    else {
      uVar2 = 5;
    }
  }
  else {
    uVar2 = 0xb;
  }
  return uVar2;
}



undefined4 FUN_0239d340(int param_1,int param_2)

{
  undefined4 uVar1;
  
  *(undefined2 *)(param_2 + 2) = 9;
  if (*(ushort *)(param_1 + 0x10) < 2) {
    if (*(ushort *)(param_1 + 0x12) < 2) {
      if (*(ushort *)(param_1 + 0x14) < 2) {
        FUN_02399454((uint)*(ushort *)(param_1 + 0x10));
        if (*(short *)(param_1 + 0x10) == 1) {
          if (*(short *)(param_1 + 0x12) == 1) {
            FUN_02399414((short)DAT_0239d3e4);
          }
          else {
            FUN_02399414(0);
          }
          *(undefined2 *)(*DAT_0239d3e8 + 0x32c) = *(undefined2 *)(param_1 + 0x14);
        }
        else {
          FUN_02399414(0x8000);
          FUN_02399428(2);
        }
        uVar1 = 0;
      }
      else {
        uVar1 = 5;
      }
    }
    else {
      uVar1 = 5;
    }
  }
  else {
    uVar1 = 5;
  }
  return uVar1;
}



undefined4 FUN_0239d3ec(int param_1,int param_2)

{
  undefined4 uVar1;
  
  *(undefined2 *)(param_2 + 2) = 1;
  if (*(ushort *)(param_1 + 0x10) < 2) {
    func_0x033a8fa0();
    if (*(short *)(param_1 + 0x10) == 1) {
      FUN_02398f90();
    }
    uVar1 = 0;
  }
  else {
    uVar1 = 5;
  }
  return uVar1;
}



int FUN_0239d42c(undefined4 param_1,int param_2)

{
  short sVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  ushort *puVar8;
  bool bVar9;
  
  if (1 < *(ushort *)(param_2 + 2)) {
    *(undefined2 *)(param_2 + 6) = *(undefined2 *)(*DAT_0239d50c + 0x3b8);
  }
  iVar6 = *DAT_0239d50c;
  iVar2 = iVar6 + 0x300;
  uVar5 = (uint)*(ushort *)(iVar6 + 0x3b8);
  iVar4 = *(ushort *)(param_2 + 2) - 2;
  uVar7 = iVar4 * 2;
  bVar9 = (int)(uVar5 + iVar4 * -2) < 0;
  if (uVar5 != uVar7 && bVar9 == SBORROW4(uVar5,uVar7)) {
    iVar2 = 4;
  }
  if (uVar5 == uVar7 || bVar9 != SBORROW4(uVar5,uVar7)) {
    if (*(ushort *)(param_2 + 6) != 0) {
      if ((*(ushort *)(iVar2 + 0xba) & 1) == 0) {
        func_0x033adb60(*(undefined4 *)(iVar6 + 0x3b4),param_2 + 8,*(ushort *)(param_2 + 6) + 1);
      }
      else {
        puVar3 = *(ushort **)(iVar6 + 0x3b4);
        puVar8 = (ushort *)(param_2 + 8);
        for (uVar7 = 0; puVar3 = (ushort *)((int)puVar3 + 1), uVar7 < *(ushort *)(param_2 + 6);
            uVar7 = uVar7 + 1) {
          uVar5 = FUN_023983a0(puVar3);
          FUN_023983c0(puVar8,uVar5);
          puVar8 = (ushort *)((int)puVar8 + 1);
        }
      }
    }
    sVar1 = func_0x033b6b64(*(ushort *)(param_2 + 6) + 1,2);
    *(short *)(param_2 + 2) = sVar1 + 2;
    iVar2 = 0;
  }
  return iVar2;
}



undefined4 FUN_0239d9c0(undefined4 param_1,int param_2)

{
  int *piVar1;
  
  *(undefined2 *)(param_2 + 2) = 0x21;
  FUN_02399054((undefined2 *)(param_2 + 6),(undefined2 *)(*DAT_0239daf4 + 0x2f8));
  piVar1 = DAT_0239daf4;
  *(undefined2 *)(param_2 + 0xc) = *(undefined2 *)(*DAT_0239daf4 + 0x2fe);
  *(undefined2 *)(param_2 + 0xe) = *(undefined2 *)(*piVar1 + 0x300);
  *(undefined2 *)(param_2 + 0x10) = *(undefined2 *)(*piVar1 + 0x392);
  *(undefined2 *)(param_2 + 0x12) = *(undefined2 *)(*piVar1 + 0x302);
  *(undefined2 *)(param_2 + 0x14) = *(undefined2 *)(*piVar1 + 0x304);
  *(undefined2 *)(param_2 + 0x16) = *(undefined2 *)(*piVar1 + 0x308);
  *(undefined2 *)(param_2 + 0x18) = *(undefined2 *)(*piVar1 + 0x30a);
  *(ushort *)(param_2 + 0x1a) = (ushort)(((uint)*(ushort *)(*piVar1 + 0x30e) << 0x1f) >> 0x1f);
  *(ushort *)(param_2 + 0x1c) = (ushort)(((uint)*(ushort *)(*piVar1 + 0x30e) << 0x1e) >> 0x1f);
  *(undefined2 *)(param_2 + 0x1e) = *(undefined2 *)(*piVar1 + 0x396);
  *(undefined2 *)(param_2 + 0x20) = *(undefined2 *)(*piVar1 + 0x310);
  func_0x033adb60(*piVar1 + 0x358,param_2 + 0x22,0x20);
  piVar1 = DAT_0239daf4;
  *(ushort *)(param_2 + 0x42) = (ushort)(((uint)*(ushort *)(*DAT_0239daf4 + 0x30e) << 0x1d) >> 0x1f)
  ;
  *(undefined2 *)(param_2 + 0x44) = *(undefined2 *)(*piVar1 + 0x306);
  return 0;
}



undefined4 FUN_0239daf8(int param_1,int param_2)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  
  *(undefined2 *)(param_2 + 2) = 1;
  if (*(short *)(*DAT_0239db64 + 0x302) == 1) {
    uVar1 = *(ushort *)(param_1 + 0x10);
    iVar3 = func_0x033b6b64(uVar1 + 1,2);
    if ((int)(uint)*(ushort *)(param_1 + 0xe) < iVar3 + 1) {
      uVar2 = 4;
    }
    else {
      uVar2 = FUN_02399128((uint)uVar1,(ushort *)(param_1 + 0x12));
    }
  }
  else {
    uVar2 = 0xb;
  }
  return uVar2;
}



void FUN_0239db68(int param_1,int param_2)

{
  *(undefined2 *)(param_2 + 2) = 1;
  if ((*(short *)(*DAT_0239dbb0 + 0x302) == 2) || (*(short *)(*DAT_0239dbb0 + 0x302) == 3)) {
    FUN_02399988((uint)*(ushort *)(param_1 + 0x10));
  }
  return;
}



void FUN_0239dbb4(int param_1,int param_2)

{
  *(undefined2 *)(param_2 + 2) = 1;
  if (*(short *)(*DAT_0239dbf4 + 0x302) == 1) {
    FUN_023999bc((uint)*(ushort *)(param_1 + 0x10));
  }
  return;
}



void FUN_0239dbf8(int param_1,int param_2)

{
  *(undefined2 *)(param_2 + 2) = 1;
  if (*(short *)(*DAT_0239dc38 + 0x302) == 1) {
    FUN_02399a08((uint)*(ushort *)(param_1 + 0x10));
  }
  return;
}



void FUN_0239dcbc(int param_1,int param_2)

{
  *(undefined2 *)(param_2 + 2) = 1;
  if (0xf < *(ushort *)(*DAT_0239dd00 + 800)) {
    FUN_02399c2c((uint)*(ushort *)(param_1 + 0x10),(uint)*(ushort *)(param_1 + 0x12));
  }
  return;
}



undefined4 FUN_0239dd04(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  *(undefined2 *)(param_2 + 2) = 1;
  if (0xf < *(ushort *)(*DAT_0239dd48 + 800)) {
    uVar1 = FUN_02399d08((uint)*(ushort *)(param_1 + 0x10));
  }
  return uVar1;
}



undefined4 FUN_0239e068(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  *(undefined2 *)(param_2 + 2) = 1;
  if (*(short *)(*DAT_0239e0ac + 800) == 0x10) {
    uVar1 = FUN_0239a234((uint)*(ushort *)(param_1 + 0x10));
  }
  return uVar1;
}



uint FUN_0239e110(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  
  uVar1 = 1;
  *(undefined2 *)(param_2 + 2) = 1;
  if (*(short *)(*DAT_0239e200 + 800) == 0x10) {
    uVar2 = FUN_0239a2a8((ushort *)(param_1 + 0x10));
    uVar3 = FUN_0239a274((uint)*(ushort *)(param_1 + 0x16));
    uVar4 = FUN_0239a234((uint)*(ushort *)(param_1 + 0x18));
    uVar5 = FUN_0239a1ac((uint)*(ushort *)(param_1 + 0x1c));
    uVar6 = FUN_0239a170((uint)*(ushort *)(param_1 + 0x1e));
    uVar7 = FUN_0239a0bc((uint)*(ushort *)(param_1 + 0x20));
    uVar8 = FUN_0239a098((uint)*(ushort *)(param_1 + 0x22));
    uVar9 = FUN_0239a034(param_1 + 0x24);
    uVar10 = FUN_02399ffc((uint)*(ushort *)(param_1 + 0x74));
    uVar11 = FUN_02399fc4((uint)*(ushort *)(param_1 + 0x76));
    uVar12 = FUN_02399f8c((uint)*(ushort *)(param_1 + 0x78));
    uVar13 = FUN_02399ecc((uint)*(ushort *)(param_1 + 0x7a),0);
    uVar14 = FUN_02399e9c((undefined2 *)(param_1 + 0x7c));
    uVar15 = FUN_02399ddc((uint)*(ushort *)(param_1 + 0x9c));
    uVar1 = FUN_02399db8((uint)*(ushort *)(param_1 + 0x9e));
    uVar1 = uVar2 | uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8 | uVar9 | uVar10 | uVar11 | uVar12
            | uVar13 | uVar14 | uVar15 | uVar1;
  }
  return uVar1;
}



void FUN_0239e2ac(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined2 uVar4;
  int iVar5;
  undefined2 *puVar6;
  uint uVar7;
  
  iVar5 = *DAT_0239e3cc;
  func_0x033a8adc();
  func_0x033a8fa0();
  uVar4 = FUN_02398b24(6);
  *(undefined2 *)(iVar5 + 0x3c4) = uVar4;
  if (*(short *)(param_1 + 0x12) == 4) {
    FUN_02398ae4(6,0);
  }
  func_0x033adb48(0,DAT_0239e3d0,0xc);
  uVar1 = DAT_0239e3d0;
  *(undefined2 *)(DAT_0239e3d0 + 8) = 0x14;
  *(undefined2 *)(uVar1 + 10) = 2000;
  uVar3 = DAT_0239e3d8;
  uVar2 = DAT_0239e3d4;
  uVar7 = 0;
  puVar6 = (undefined2 *)(uVar1 + 0xc);
  do {
    *puVar6 = (short)uVar2;
    uVar7 = uVar7 + 2;
    puVar6 = puVar6 + 1;
  } while (uVar7 < uVar3);
  *(undefined2 *)(DAT_0239e3d0 + 0xc) = 8;
  *DAT_0239e3dc = 6;
  *(undefined2 *)(iVar5 + 800) = 0x12;
  *(undefined2 *)(iVar5 + 0x330) = 1;
  FUN_023995a4((uint)*(ushort *)(param_1 + 0x16),1);
  *DAT_0239e3e0 = 0x8000;
  FUN_02398728(DAT_0239e3e4);
  *DAT_0239e3e8 = 2;
  *DAT_0239e3ec = 1;
  *DAT_0239e3f0 = 1;
  *DAT_0239e3f8 = (ushort)(((DAT_0239e3d0 & DAT_0239e3f4) << 0xf) >> 0x10) | 0x8000;
  return;
}



undefined4 FUN_0239e3fc(int param_1,int param_2)

{
  uint uVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint local_18 [2];
  
  iVar3 = *DAT_0239e64c;
  *(undefined2 *)(param_2 + 2) = 1;
  if ((*(ushort *)(iVar3 + 800) & 0xf0) != 0x10) {
    return 1;
  }
  if (1 < *(ushort *)(param_1 + 0x10)) {
    return 5;
  }
  if ((*(short *)(param_1 + 0x14) != 10) && (*(short *)(param_1 + 0x14) != 0x14)) {
    return 5;
  }
  if (4 < *(ushort *)(param_1 + 0x12)) {
    return 5;
  }
  iVar4 = FUN_023a45bc((uint *)0x0);
  if (iVar4 != 0) {
    return 0xe;
  }
  if (*(short *)(param_1 + 0x10) == 0) {
    if (*(short *)(iVar3 + 800) == 0x11) {
      FUN_02398698();
      *DAT_0239e668 = 0;
      *DAT_0239e660 = 1;
      *DAT_0239e654 = 0;
      uVar2 = FUN_02398b24(2);
      local_18[0] = uVar2 & 0xffffffcf;
      FUN_02398ae4(2,(short)local_18[0]);
    }
    else {
      if (*(short *)(iVar3 + 800) != 0x12) {
        return 1;
      }
      *(undefined2 *)(iVar3 + 0x330) = 0;
      do {
      } while (*DAT_0239e66c != 0);
      FUN_02398ae4(6,*(undefined2 *)(iVar3 + 0x3c4));
    }
    *(undefined2 *)(iVar3 + 800) = 0x10;
    return 0;
  }
  if (*(short *)(param_1 + 0x10) != 1) {
    return 0;
  }
  if (*(short *)(iVar3 + 800) != 0x10) {
    return 1;
  }
  local_18[0] = 0;
  FUN_023a44cc(0x65,1,(int)local_18);
  uVar1 = local_18[0];
  uVar2 = FUN_02398b24(1);
  if (uVar1 != uVar2) {
    FUN_02398ae4(1,(short)uVar1);
    FUN_02398728(DAT_0239e650);
  }
  switch(*(undefined2 *)(param_1 + 0x12)) {
  case 0:
    break;
  case 1:
    break;
  case 2:
    break;
  case 3:
    goto LAB_0239e5a0;
  case 4:
LAB_0239e5a0:
    FUN_0239e2ac(param_1);
  default:
    goto switchD_0239e4e4_caseD_5;
  }
  *(undefined2 *)(iVar3 + 800) = 0x11;
  FUN_023995a4((uint)*(ushort *)(param_1 + 0x16),1);
  *DAT_0239e654 = 0x8000;
  FUN_02398728(DAT_0239e658);
  *(undefined2 *)(iVar3 + 0x32e) = *(undefined2 *)(param_1 + 0x14);
  uVar2 = FUN_02398b24(2);
  local_18[0] = (uint)uVar2;
  if (*(ushort *)(param_1 + 0x12) < 2) {
    local_18[0] = local_18[0] | 0x10;
  }
  *DAT_0239e65c = *(undefined2 *)(param_1 + 0x14);
  if (*(short *)(param_1 + 0x12) == 1) {
    local_18[0] = local_18[0] | 0x20;
    *DAT_0239e660 = 3;
  }
  else {
    *DAT_0239e660 = *(short *)(param_1 + 0x12);
  }
  FUN_02398ae4(2,(short)local_18[0]);
  *DAT_0239e668 = (short)DAT_0239e664;
switchD_0239e4e4_caseD_5:
  return 0;
}



undefined4 FUN_0239e6f8(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  
  *(undefined2 *)(param_2 + 2) = 9;
  func_0x033adb60(DAT_0239e758,param_2 + 6,8);
  *(undefined2 *)(param_2 + 0xe) = *(undefined2 *)PTR_Wifi_WS1_Region_0239e75c;
  uVar1 = FUN_02398b24(0);
  *(undefined2 *)(param_2 + 0x10) = uVar1;
  uVar1 = FUN_02398a4c();
  *(undefined2 *)(param_2 + 0x12) = uVar1;
  *(undefined2 *)(param_2 + 0x14) = *(undefined2 *)(*DAT_0239e760 + 0x5d0);
  return 0;
}



bool FUN_0239e764(undefined4 param_1,int param_2)

{
  undefined uVar1;
  bool bVar3;
  short sVar2;
  
  sVar2 = *(short *)(*DAT_0239e7a4 + 800);
  bVar3 = sVar2 == 0;
  if (bVar3) {
    sVar2 = 1;
  }
  uVar1 = (undefined)sVar2;
  if (!bVar3) {
    *(undefined2 *)(param_2 + 2) = 1;
    FUN_02398f90();
    uVar1 = 0;
  }
  return (bool)uVar1;
}



undefined4 FUN_0239e7a8(undefined4 param_1,int param_2)

{
  *(undefined2 *)(param_2 + 2) = 1;
  if (0x1f < *(ushort *)(*DAT_0239e7e8 + 800)) {
    func_0x033a8fa0();
  }
  FUN_02397c24();
  return 0;
}



undefined4 FUN_0239e7ec(undefined4 param_1,int param_2)

{
  short sVar1;
  undefined4 uVar2;
  
  *(undefined2 *)(param_2 + 2) = 1;
  sVar1 = *(short *)(*DAT_0239e848 + 800);
  if ((sVar1 == 0x10) || ((sVar1 == 0x20 && (*(short *)(*DAT_0239e848 + 0x32a) == 0)))) {
    func_0x033a9058(0x20);
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



undefined4 FUN_0239e84c(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 1;
  *(undefined2 *)(param_2 + 2) = 1;
  if ((*(ushort *)(*DAT_0239e8ac + 800) < 0x21) && (*(short *)(*DAT_0239e8ac + 0x32a) == 0)) {
    iVar2 = FUN_023a45bc((uint *)0x0);
    if (iVar2 == 0) {
      func_0x033a9058(0x10);
      uVar1 = 0;
    }
    else {
      uVar1 = 0xe;
    }
  }
  return uVar1;
}



undefined4 FUN_0239e8b0(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  *(undefined2 *)(param_2 + 2) = 1;
  if ((*(short *)(*DAT_0239e8f8 + 800) == 0) || (*(short *)(*DAT_0239e8f8 + 800) == 0x10)) {
    func_0x033a9058(0);
    uVar1 = 0;
  }
  return uVar1;
}



void FUN_0239e8fc(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_2 + (uint)*(ushort *)(param_2 + 0xe) * 2;
  *(undefined2 *)(param_2 + 0xc) = *(undefined2 *)(iVar1 + 0x10);
  *(undefined2 *)(iVar1 + 0x12) = 2;
  *(undefined2 *)(iVar1 + 0x14) = 0;
  *(undefined2 *)(iVar1 + 0x16) = *(undefined2 *)(param_2 + 0x18);
                    // WARNING: Could not recover jumptable at 0x0239e92c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_0239e930)();
  return;
}



undefined4 FUN_0239e934(int param_1,int param_2)

{
  *(undefined2 *)(param_2 + 2) = 1;
  if ((*(ushort *)(param_1 + 0x10) & 1) != 0) {
    FUN_023a07a0();
  }
  if ((*(ushort *)(param_1 + 0x10) & 2) != 0) {
    FUN_023a0748();
  }
  if ((*(ushort *)(param_1 + 0x10) & 4) != 0) {
    FUN_023a0698();
  }
  return 0;
}



undefined4 FUN_0239e980(int param_1,int param_2)

{
  *(undefined2 *)(param_2 + 2) = 1;
  *(short *)(param_1 + 0xc) = (short)DAT_0239e9dc;
  *(undefined2 *)(param_1 + 0x12) = 0;
  *(undefined2 *)(param_1 + 0x22) = *(undefined2 *)(param_1 + 0x16);
  FUN_0239b588(param_1 + 0x10);
  func_0x033a862c(*DAT_0239e9e0 + 0x1d4,*DAT_0239e9e0 + 0x168,param_1);
  FUN_023a1240(0);
  return 0;
}



undefined4 FUN_0239e9e4(int param_1,int param_2)

{
  ushort uVar1;
  bool bVar2;
  uint uVar3;
  short sVar4;
  short sVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined2 *puVar8;
  uint uVar9;
  int iVar10;
  undefined2 *puVar11;
  int iVar12;
  ushort uVar13;
  bool bVar14;
  
  iVar10 = *DAT_0239ee84;
  uVar1 = *(ushort *)(iVar10 + 0x63c);
  bVar2 = true;
  *(undefined2 *)(param_2 + 2) = 1;
  if (*(short *)(iVar10 + 0x302) == 1) {
    if (*(short *)(iVar10 + 0x43c) == 0) {
      puVar11 = *(undefined2 **)(iVar10 + 0x444);
      if ((*(ushort *)(param_1 + 0x10) & 0x8000) != 0) {
        if ((*(ushort *)(param_1 + 0x10) & 2) == 0) {
          *(undefined2 *)(param_1 + 0x14) = *(undefined2 *)(iVar10 + 0x494);
        }
        if ((*(ushort *)(param_1 + 0x10) & 4) == 0) {
          *(undefined2 *)(param_1 + 0x16) = *(undefined2 *)(iVar10 + 0x4a0);
        }
        if ((*(ushort *)(param_1 + 0x10) & 8) == 0) {
          *(undefined2 *)(param_1 + 0x18) = *(undefined2 *)(iVar10 + 0x496);
        }
        if ((*(ushort *)(param_1 + 0x10) & 0x10) == 0) {
          *(undefined2 *)(param_1 + 0x1c) = *(undefined2 *)(iVar10 + 0x49c);
          bVar2 = false;
        }
      }
      if (*(ushort *)(param_1 + 0x1c) < 0x205) {
        iVar12 = 0;
        for (uVar7 = 2; uVar7 != 0; uVar7 = (uVar7 << 0x11) >> 0x10) {
          if ((*(ushort *)(param_1 + 0x16) & uVar7) != 0) {
            iVar12 = iVar12 + 1;
          }
        }
        *(undefined2 *)(iVar10 + 0x494) = *(undefined2 *)(param_1 + 0x14);
        uVar13 = *(ushort *)(param_1 + 0x14);
        if ((uVar13 & 0x8000) == 0) {
          bVar14 = (uVar1 & 2) != 0;
          if (bVar14) {
            sVar5 = 2;
            sVar4 = 6;
          }
          else {
            sVar5 = 0;
            sVar4 = sVar5;
          }
          uVar9 = (uint)bVar14;
          uVar7 = uVar13 + uVar9;
          if (uVar9 + DAT_0239ee8c < uVar7) {
            return 5;
          }
          *(short *)(param_1 + 0x14) = sVar5 + (short)uVar7 * 4 + 0xd0;
          puVar11[7] = sVar4 + 0xea;
        }
        else {
          *(ushort *)(param_1 + 0x14) = uVar13 & (ushort)DAT_0239ee88;
          uVar7 = *(ushort *)(param_1 + 0x14) - 0xd0 >> 2;
          puVar11[7] = 0xea;
          if (0x10000 < uVar7) {
            return 5;
          }
        }
        uVar7 = uVar7 + 9 & 0xfffffffe;
        uVar6 = func_0x033a8500(iVar10 + 0x15c,uVar7 * iVar12 + 0x1a);
        *(undefined4 *)(iVar10 + 0x490) = uVar6;
        if (*(int *)(iVar10 + 0x490) == 0) {
          uVar6 = 8;
        }
        else {
          *(undefined2 *)(iVar10 + 0x43c) = 1;
          *(short *)(iVar10 + 0x43e) = *(short *)(iVar10 + 0x43e) + 1;
          *(undefined2 *)(iVar10 + 0x496) = *(undefined2 *)(param_1 + 0x18);
          *(undefined2 *)(iVar10 + 0x498) = *(undefined2 *)(param_1 + 0x16);
          *(undefined2 *)(iVar10 + 0x49a) = 0;
          *(undefined2 *)(iVar10 + 0x49c) = *(undefined2 *)(param_1 + 0x1c);
          *(undefined2 *)(iVar10 + 0x49e) = *(undefined2 *)(param_1 + 0x12);
          *puVar11 = 0;
          puVar11[1] = *(undefined2 *)(param_1 + 0x16);
          puVar11[2] = 0;
          puVar11[4] = 0x14;
          puVar11[5] = *(short *)(param_1 + 0x1c) + 0x22;
          puVar11[6] = 0x228;
          puVar11[7] = (*(short *)(param_1 + 0x14) + 10) * (short)iVar12 + puVar11[7];
          FUN_02398fd4(puVar11 + 8,DAT_0239ee90,(undefined2 *)(iVar10 + 0x37c),
                       (undefined2 *)(iVar10 + 0x2f8));
          if (((*(ushort *)(param_1 + 0x10) & 0x8000) == 0) ||
             ((ushort)puVar11[0x11] == DAT_0239ee94)) {
            uVar13 = 0;
            puVar11[0x11] = (short)DAT_0239ee94;
          }
          else {
            uVar13 = 0x4000;
          }
          puVar11[0x12] = *(undefined2 *)(param_1 + 0x14);
          puVar11[0x13] = *(undefined2 *)(param_1 + 0x16);
          puVar11[0x14] = *(undefined2 *)(param_1 + 0x1e);
          if ((bVar2) && (*(ushort *)(param_1 + 0x1c) != 0)) {
            FUN_02398464(puVar11 + 0x15,*(undefined4 *)(param_1 + 0x20),
                         (uint)*(ushort *)(param_1 + 0x1c));
          }
          if ((uVar1 & 4) != 0) {
            puVar8 = (undefined2 *)((int)puVar11 + *(ushort *)(param_1 + 0x1c) + 0x2d & 0xfffffffc);
            *puVar8 = (short)DAT_0239ee98;
            puVar8[1] = (short)DAT_0239ee9c;
          }
          *(undefined2 *)(*(int *)(iVar10 + 0x490) + 0xc) = 0x184;
          *(short *)(*(int *)(iVar10 + 0x490) + 0xe) = (short)(uVar7 * iVar12 + 0xb >> 1);
          *(undefined2 *)(*(int *)(iVar10 + 0x490) + 0x10) = *(undefined2 *)(param_1 + 0x16);
          *(short *)(*(int *)(iVar10 + 0x490) + 0x14) = (short)iVar12;
          *(short *)(*(int *)(iVar10 + 0x490) + 0x16) = (short)uVar7;
          *(undefined2 *)(*(int *)(iVar10 + 0x490) + 0x18) = 0;
          uVar3 = DAT_0239ee94;
          puVar8 = (undefined2 *)(*(int *)(iVar10 + 0x490) + 0x1a);
          sVar5 = 1;
          for (uVar9 = 2; uVar9 != 0; uVar9 = (uVar9 << 0x11) >> 0x10) {
            if ((*(ushort *)(param_1 + 0x16) & uVar9) != 0) {
              *puVar8 = (short)uVar3;
              puVar8[1] = 0;
              puVar8[3] = 0;
              puVar8[2] = sVar5;
              puVar8 = (undefined2 *)((int)puVar8 + uVar7);
            }
            sVar5 = sVar5 + 1;
          }
          *DAT_0239eea0 = *(undefined2 *)(param_1 + 0x14);
          *DAT_0239eea4 = puVar11[7];
          uVar1 = *(ushort *)(param_1 + 0x1a);
          if (*(short *)(param_1 + 0x18) == 0) {
            sVar5 = func_0x033b6d70((*(ushort *)(param_1 + 0x1c) + 0x22) * 4 +
                                    (uint)*(ushort *)(param_1 + 0x14) * iVar12 + 0x41a,10);
            func_0x033ad8a0();
            *DAT_0239eea8 = sVar5;
            *DAT_0239eeb0 = (ushort)(((uint)puVar11 & DAT_0239eeac) >> 1) | 0x8000 | uVar13;
            func_0x033ad8b4();
          }
          else {
            uVar6 = func_0x033ad8a0();
            iVar12 = func_0x033b6d70((0x10000 - (uint)uVar1) + (uint)*DAT_0239eeb4 & DAT_0239ee94,10
                                    );
            if ((uint)*(ushort *)(param_1 + 0x18) <= iVar12 + 3U) {
              func_0x033ad8b4(uVar6);
              func_0x033a85a8(iVar10 + 0x15c,*(undefined4 *)(iVar10 + 0x490));
              *(undefined2 *)(iVar10 + 0x43c) = 0;
              *(short *)(iVar10 + 0x43e) = *(short *)(iVar10 + 0x43e) + -1;
              return 5;
            }
            *DAT_0239eea8 = (*(ushort *)(param_1 + 0x18) - (short)iVar12) + -1;
            *DAT_0239eeb0 = (ushort)(((uint)puVar11 & DAT_0239eeac) >> 1) | 0x8000 | uVar13;
            func_0x033ad8b4(uVar6);
          }
          uVar6 = 0;
        }
      }
      else {
        uVar6 = 5;
      }
    }
    else {
      uVar6 = 8;
    }
  }
  else {
    uVar6 = 0xb;
  }
  return uVar6;
}



undefined4 FUN_0239eeb8(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  int iVar5;
  undefined2 *puVar6;
  
  iVar2 = *DAT_0239f018;
  uVar1 = *(ushort *)(iVar2 + 0x63c);
  *(undefined2 *)(param_2 + 2) = 1;
  if (*(short *)(iVar2 + 0x302) == 2) {
    if (*(ushort *)(param_1 + 0x10) < 0x205) {
      iVar5 = (uint)(*(short *)(iVar2 + 0x450) != 0) * 0x14;
      if (*(short *)(iVar2 + 0x450 + iVar5) == 0) {
        if ((*DAT_0239f01c & 0x8000) == 0) {
          puVar6 = *(undefined2 **)(iVar2 + iVar5 + 0x458);
          *puVar6 = 0;
          puVar6[2] = 0;
          puVar6[4] = 0x14;
          puVar6[5] = *(short *)(param_1 + 0x10) + 0x1e;
          puVar6[6] = 0x118;
          FUN_02398fd4(puVar6 + 8,(undefined2 *)(iVar2 + 0x37c),(undefined2 *)(iVar2 + 0x2f8),
                       DAT_0239f020);
          puVar6[0x12] = *(undefined2 *)(param_1 + 0x12);
          if (*(ushort *)(param_1 + 0x10) != 0) {
            FUN_02398464(puVar6 + 0x13,*(undefined4 *)(param_1 + 0x14),
                         (uint)*(ushort *)(param_1 + 0x10));
          }
          if ((uVar1 & 4) != 0) {
            puVar4 = (undefined2 *)((int)puVar6 + *(ushort *)(param_1 + 0x10) + 0x29 & 0xfffffffc);
            *puVar4 = (short)DAT_0239f024;
            puVar4[1] = (short)DAT_0239f028;
          }
          *(undefined2 *)(iVar2 + 0x450 + iVar5) = 1;
          *(short *)(iVar2 + 0x452 + iVar5) = *(short *)(iVar2 + 0x452 + iVar5) + 1;
          *DAT_0239f01c = (ushort)(((uint)puVar6 & DAT_0239f02c) >> 1) | 0x8000;
          uVar3 = 0;
        }
        else {
          uVar3 = 8;
        }
      }
      else {
        uVar3 = 8;
      }
    }
    else {
      uVar3 = 5;
    }
  }
  else {
    uVar3 = 0xb;
  }
  return uVar3;
}



undefined4 FUN_0239f030(int param_1)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  iVar2 = *DAT_0239f208;
  if (DAT_0239f20c < *(ushort *)(param_1 + 0x16)) {
    uVar3 = 5;
  }
  else {
    if (*(short *)(iVar2 + 0x302) == 1) {
      uVar4 = FUN_0239b7c4((ushort *)(param_1 + 0x28));
      if ((uVar4 == 0xff) || (sVar1 = FUN_0239b1b0(uVar4), sVar1 != 0x40)) {
        return 10;
      }
    }
    else {
      uVar4 = (uint)*(ushort *)(iVar2 + 0x3a0);
    }
    *(short *)(param_1 + 0x12) = (short)uVar4;
    *(short *)(param_1 + 0x14) = (short)*(undefined4 *)(*DAT_0239f208 + 0x3c0);
    if ((*(ushort *)(param_1 + 0x1e) & 0xff) == 0) {
      uVar3 = FUN_0239b0f4(uVar4);
      *(short *)(param_1 + 0x20) = (short)uVar3;
    }
    else {
      *(ushort *)(param_1 + 0x20) = *(ushort *)(param_1 + 0x1e);
      *(undefined2 *)(param_1 + 0x1e) = 0;
    }
    if (*(short *)(param_1 + 0x16) == 0) {
      *(ushort *)(param_1 + 0x24) = *(ushort *)(iVar2 + 0x3a2) & 0xbfff | 0x40;
      *(undefined2 *)(param_1 + 0x22) = 0x1c;
    }
    else {
      *(undefined2 *)(param_1 + 0x24) = *(undefined2 *)(iVar2 + 0x3a2);
      if (*(short *)(iVar2 + 0x308) == 0) {
        *(short *)(param_1 + 0x22) = *(short *)(param_1 + 0x16) + 0x1c;
      }
      else {
        *(short *)(param_1 + 0x22) = *(short *)(param_1 + 0x16) + 0x24;
      }
    }
    sVar1 = *(short *)(iVar2 + 0x302);
    if (sVar1 == 1) {
      FUN_02399054((undefined2 *)(param_1 + 0x34),(undefined2 *)(param_1 + 0x2e));
      FUN_02399054((undefined2 *)(param_1 + 0x2e),(undefined2 *)(iVar2 + 0x37c));
      if (uVar4 == 0) {
        FUN_0239b618(iVar2 + 0x1d4,param_1);
        if ((*(ushort *)(*DAT_0239f208 + 0x506) & ~*(ushort *)(*DAT_0239f208 + 0x50a)) == 0) {
          FUN_023a1180();
        }
      }
      else {
        FUN_0239b588(param_1 + 0x10);
        func_0x033a862c(iVar2 + 0x1d4,iVar2 + 0x168,param_1);
        FUN_023a1240(0);
      }
    }
    else if ((sVar1 == 2) || (sVar1 == 3)) {
      FUN_02399054((undefined2 *)(param_1 + 0x34),(undefined2 *)(param_1 + 0x28));
      FUN_02399054((undefined2 *)(param_1 + 0x28),(undefined2 *)(iVar2 + 0x37c));
      FUN_0239b588(param_1 + 0x10);
      func_0x033a862c(iVar2 + 0x1d4,iVar2 + 0x168,param_1);
      FUN_023a1240(0);
    }
    uVar3 = 0x81;
  }
  return uVar3;
}



int FUN_0239f210(ushort *param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  ushort *puVar5;
  uint uVar6;
  
  iVar3 = *DAT_0239f32c;
  FUN_023983c0(param_1,0xdd);
  FUN_023983c0((ushort *)((int)param_1 + 1),*(ushort *)(*DAT_0239f32c + 0x3b8) + 8 & 0xff);
  FUN_023983c0(param_1 + 1,0);
  FUN_023983c0((ushort *)((int)param_1 + 3),9);
  FUN_023983c0(param_1 + 2,0xbf);
  FUN_023983c0((ushort *)((int)param_1 + 5),0);
  FUN_023983c0(param_1 + 3,*(ushort *)(iVar3 + 0x310) & 0xff);
  FUN_023983c0((ushort *)((int)param_1 + 7),(int)(uint)*(ushort *)(iVar3 + 0x310) >> 8);
  uVar1 = *DAT_0239f330;
  FUN_023983c0(param_1 + 4,uVar1 & 0xff);
  FUN_023983c0((ushort *)((int)param_1 + 9),(uint)(uVar1 >> 8));
  iVar4 = 10;
  if (*(short *)(iVar3 + 0x3b8) != 0) {
    puVar5 = *(ushort **)(iVar3 + 0x3b4);
    if ((*(ushort *)(iVar3 + 0x3ba) & 1) != 0) {
      puVar5 = (ushort *)((int)puVar5 + 1);
    }
    for (uVar6 = 0; uVar6 < *(ushort *)(iVar3 + 0x3b8); uVar6 = uVar6 + 1) {
      uVar2 = FUN_023983a0(puVar5);
      FUN_023983c0((ushort *)((int)param_1 + iVar4),uVar2);
      iVar4 = iVar4 + 1;
      puVar5 = (ushort *)((int)puVar5 + 1);
    }
  }
  return iVar4;
}



undefined4 FUN_0239f334(ushort *param_1)

{
  FUN_023983c0(param_1,3);
  FUN_023983c0((ushort *)((int)param_1 + 1),1);
  FUN_023983c0(param_1 + 1,*(ushort *)(*DAT_0239f378 + 0x392) & 0xff);
  return 3;
}



int FUN_0239f37c(ushort *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  iVar3 = *DAT_0239f42c;
  FUN_023983c0(param_1,1);
  iVar2 = DAT_0239f430;
  iVar5 = 2;
  uVar4 = 0;
  do {
    uVar1 = 1 << (uVar4 & 0xff);
    if ((*(ushort *)(iVar3 + 0x37a) & uVar1) != 0) {
      if ((*(ushort *)(iVar3 + 0x378) & uVar1) == 0) {
        FUN_023983c0((ushort *)((int)param_1 + iVar5),*(ushort *)(iVar2 + uVar4 * 2) & 0xff);
      }
      else {
        FUN_023983c0((ushort *)((int)param_1 + iVar5),*(ushort *)(iVar2 + uVar4 * 2) & 0xff | 0x80);
      }
      iVar5 = iVar5 + 1;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x10);
  FUN_023983c0((ushort *)((int)param_1 + 1),iVar5 - 2U & 0xff);
  return iVar5;
}



int FUN_0239f434(ushort *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  iVar2 = *DAT_0239f4a4;
  uVar4 = (uint)*(ushort *)(iVar2 + 0x336);
  FUN_023983c0(param_1,0);
  FUN_023983c0((ushort *)((int)param_1 + 1),uVar4 & 0xff);
  iVar5 = 2;
  for (uVar3 = 0; uVar3 < uVar4; uVar3 = uVar3 + 1) {
    uVar1 = FUN_023983a0((ushort *)(iVar2 + 0x338 + uVar3));
    FUN_023983c0((ushort *)((int)param_1 + iVar5),uVar1);
    iVar5 = iVar5 + 1;
  }
  return iVar5;
}



void FUN_0239f4a8(int param_1,undefined2 *param_2)

{
  undefined4 uVar1;
  
  func_0x033adb48(0,param_1,0x2c);
  uVar1 = FUN_02398b58();
  *(short *)(param_1 + 0x10) = (short)uVar1;
  FUN_02398fd4((undefined2 *)(param_1 + 0x18),param_2,(undefined2 *)(*DAT_0239f500 + 0x2f8),
               (undefined2 *)(*DAT_0239f500 + 0x37c));
  return;
}



void FUN_0239f504(ushort param_1)

{
  int *piVar1;
  undefined2 *puVar2;
  
  piVar1 = DAT_0239f550;
  puVar2 = *(undefined2 **)(*DAT_0239f550 + 0x430);
  *puVar2 = 0;
  puVar2[1] = 0;
  puVar2[2] = 0;
  puVar2[5] = 0x14;
  puVar2[6] = 0xa4;
  puVar2[7] = param_1 | 0xc000;
                    // WARNING: Could not recover jumptable at 0x0239f54c. Too many branches
                    // WARNING: Treating indirect jump as call
  (*DAT_0239f554)(puVar2 + 8,*piVar1 + 0x37c,*piVar1 + 0x2f8);
  return;
}



int FUN_0239f558(undefined2 *param_1,undefined2 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = func_0x033a8500(*DAT_0239f5d4 + 0x15c,0x36);
  if (iVar1 == 0) {
    FUN_02398034(2);
    iVar2 = iVar1;
  }
  else {
    *(short *)(iVar1 + 0xc) = (short)DAT_0239f5d8;
    iVar2 = iVar1 + 0x10;
    FUN_0239f4a8(iVar2,param_1);
    *(undefined2 *)(iVar1 + 0x3c) = param_2;
    *(undefined2 *)(iVar1 + 0x16) = 2;
    *(short *)(iVar1 + 0x22) = *(short *)(iVar1 + 0x16) + 0x1c;
    *(undefined2 *)(iVar1 + 0x24) = 0xc0;
  }
  return iVar2;
}



int FUN_0239f5dc(undefined2 *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = func_0x033a8500(*DAT_0239f684 + 0x15c,param_2 + DAT_0239f688);
  if (iVar1 == 0) {
    FUN_02398034(2);
    iVar2 = iVar1;
  }
  else {
    *(short *)(iVar1 + 0xc) = (short)DAT_0239f68c;
    iVar2 = iVar1 + 0x10;
    FUN_0239f4a8(iVar2,param_1);
    if (param_2 != 0) {
      FUN_023983c0((ushort *)(iVar1 + 0x42),0x10);
      FUN_023983c0((ushort *)(iVar1 + 0x43),param_2 & 0xff);
      param_2 = param_2 + 2 & 0xffff;
    }
    *(short *)(iVar1 + 0x16) = (short)param_2 + 6;
    *(short *)(iVar1 + 0x22) = *(short *)(iVar1 + 0x16) + 0x1c;
    *(undefined2 *)(iVar1 + 0x24) = 0xb0;
  }
  return iVar2;
}



int FUN_0239f690(undefined2 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = *DAT_0239f758;
  iVar2 = func_0x033a8500(iVar1 + 0x15c,*(ushort *)(iVar1 + 0x3b8) + 0x78);
  if (iVar2 == 0) {
    FUN_02398034(2);
    iVar5 = iVar2;
  }
  else {
    *(short *)(iVar2 + 0xc) = (short)DAT_0239f75c;
    iVar5 = iVar2 + 0x10;
    FUN_0239f4a8(iVar5,param_1);
    *(undefined2 *)(iVar2 + 0x44) = *(undefined2 *)(iVar1 + 0x386);
    *(undefined2 *)(iVar2 + 0x46) = *(undefined2 *)(iVar1 + 0x394);
    iVar1 = FUN_0239f434((ushort *)(iVar2 + 0x48));
    iVar3 = FUN_0239f37c((ushort *)(iVar2 + 0x48 + iVar1));
    iVar4 = FUN_0239f334((ushort *)(iVar2 + 0x48 + iVar1 + iVar3));
    iVar4 = iVar1 + iVar3 + iVar4;
    iVar1 = FUN_0239f210((ushort *)(iVar2 + 0x48 + iVar4));
    *(short *)(iVar2 + 0x16) = (short)iVar4 + (short)iVar1 + 0xc;
    *(short *)(iVar2 + 0x22) = *(short *)(iVar2 + 0x16) + 0x1c;
    *(undefined2 *)(iVar2 + 0x24) = 0x50;
  }
  return iVar5;
}



int FUN_0239f760(undefined2 *param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar2 = func_0x033a8500(*DAT_0239f7e8 + 0x15c,0x5a);
  if (iVar2 == 0) {
    FUN_02398034(2);
    iVar5 = iVar2;
  }
  else {
    *(short *)(iVar2 + 0xc) = (short)DAT_0239f7ec;
    iVar5 = iVar2 + 0x10;
    FUN_0239f4a8(iVar5,param_1);
    iVar3 = FUN_0239f434((ushort *)(iVar2 + 0x3c));
    iVar4 = FUN_0239f37c((ushort *)(iVar2 + 0x3c + iVar3));
    sVar1 = (short)iVar3 + (short)iVar4;
    *(short *)(iVar2 + 0x16) = sVar1;
    *(short *)(iVar2 + 0x22) = sVar1 + 0x1c;
    *(undefined2 *)(iVar2 + 0x24) = 0x40;
  }
  return iVar5;
}



int FUN_0239f7f0(int param_1,int param_2,ushort *param_3)

{
  int iVar1;
  uint uVar2;
  undefined2 *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  ushort *puVar8;
  
  iVar1 = func_0x033a8500(*DAT_0239f954 + 0x15c,0x60);
  if (iVar1 == 0) {
    FUN_02398034(2);
    iVar7 = iVar1;
  }
  else {
    *(short *)(iVar1 + 0xc) = (short)DAT_0239f958;
    iVar7 = iVar1 + 0x10;
    if (param_2 == 0) {
      uVar2 = FUN_0239b23c(param_1);
      if (uVar2 == 0) {
        param_2 = 0x13;
      }
    }
    else {
      uVar2 = 0;
    }
    puVar3 = (undefined2 *)FUN_0239b154(param_1);
    FUN_0239f4a8(iVar7,puVar3);
    *(undefined2 *)(iVar1 + 0x3c) = *(undefined2 *)(*DAT_0239f954 + 0x394);
    *(short *)(iVar1 + 0x3e) = (short)param_2;
    *(ushort *)(iVar1 + 0x40) = (ushort)uVar2 | 0xc000;
    iVar4 = FUN_0239f37c((ushort *)(iVar1 + 0x42));
    *(short *)(iVar1 + 0x16) = (short)iVar4 + 6;
    *(short *)(iVar1 + 0x22) = *(short *)(iVar1 + 0x16) + 0x1c;
    *(undefined2 *)(iVar1 + 0x24) = 0x30;
    puVar8 = (ushort *)(iVar1 + 0x24 + (uint)*(ushort *)(iVar1 + 0x22));
    if (param_3 == (ushort *)0x0) {
      FUN_023983c0(puVar8,0);
      FUN_023983c0((ushort *)((int)puVar8 + 1),0);
    }
    else {
      uVar2 = FUN_023983a0((ushort *)((int)param_3 + 1));
      uVar5 = FUN_023983a0(param_3);
      FUN_023983c0(puVar8,uVar5);
      FUN_023983c0((ushort *)((int)puVar8 + 1),uVar2 & 0xff);
      puVar8 = puVar8 + 1;
      for (uVar5 = 0; uVar5 < uVar2; uVar5 = uVar5 + 1) {
        uVar6 = FUN_023983a0((ushort *)((int)param_3 + uVar5 + 2));
        FUN_023983c0(puVar8,uVar6);
        puVar8 = (ushort *)((int)puVar8 + 1);
      }
    }
  }
  return iVar7;
}



int FUN_0239f95c(int param_1,int param_2,ushort *param_3)

{
  int iVar1;
  uint uVar2;
  undefined2 *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  ushort *puVar8;
  ushort *puVar9;
  
  iVar1 = func_0x033a8500(*DAT_0239facc + 0x15c,0x60);
  if (iVar1 == 0) {
    FUN_02398034(2);
    iVar7 = iVar1;
  }
  else {
    *(short *)(iVar1 + 0xc) = (short)DAT_0239fad0;
    iVar7 = iVar1 + 0x10;
    if (param_2 == 0) {
      uVar2 = FUN_0239b23c(param_1);
      if (uVar2 == 0) {
        param_2 = 0x13;
      }
    }
    else {
      uVar2 = 0;
    }
    puVar3 = (undefined2 *)FUN_0239b154(param_1);
    FUN_0239f4a8(iVar7,puVar3);
    *(undefined2 *)(iVar1 + 0x3c) = *(undefined2 *)(*DAT_0239facc + 0x394);
    *(short *)(iVar1 + 0x3e) = (short)param_2;
    *(short *)(iVar1 + 0x40) = (short)uVar2;
    if (uVar2 != 0) {
      *(ushort *)(iVar1 + 0x40) = *(ushort *)(iVar1 + 0x40) | 0xc000;
    }
    iVar4 = FUN_0239f37c((ushort *)(iVar1 + 0x42));
    *(short *)(iVar1 + 0x16) = (short)iVar4 + 6;
    *(short *)(iVar1 + 0x22) = *(short *)(iVar1 + 0x16) + 0x1c;
    *(undefined2 *)(iVar1 + 0x24) = 0x10;
    puVar8 = (ushort *)(iVar1 + 0x24 + (uint)*(ushort *)(iVar1 + 0x22));
    if (param_3 == (ushort *)0x0) {
      FUN_023983c0(puVar8,0);
      FUN_023983c0((ushort *)((int)puVar8 + 1),0);
    }
    else {
      uVar2 = FUN_023983a0((ushort *)((int)param_3 + 1));
      uVar5 = FUN_023983a0(param_3);
      FUN_023983c0(puVar8,uVar5);
      puVar9 = puVar8 + 1;
      FUN_023983c0((ushort *)((int)puVar8 + 1),uVar2 & 0xff);
      for (uVar5 = 0; uVar5 < uVar2; uVar5 = uVar5 + 1) {
        uVar6 = FUN_023983a0((ushort *)((int)param_3 + uVar5 + 2));
        FUN_023983c0(puVar9,uVar6);
        puVar9 = (ushort *)((int)puVar9 + 1);
      }
    }
  }
  return iVar7;
}



int FUN_0239fad4(undefined2 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = *DAT_0239fb84;
  iVar2 = func_0x033a8500(iVar1 + 0x15c,100);
  if (iVar2 == 0) {
    FUN_02398034(2);
    iVar4 = iVar2;
  }
  else {
    *(short *)(iVar2 + 0xc) = (short)DAT_0239fb88;
    iVar4 = iVar2 + 0x10;
    FUN_0239f4a8(iVar4,param_1);
    *(undefined2 *)(iVar2 + 0x3c) = *(undefined2 *)(iVar1 + 0x394);
    *(undefined2 *)(iVar2 + 0x3e) = *(undefined2 *)(iVar1 + 0x388);
    FUN_02399054((undefined2 *)(iVar2 + 0x40),(undefined2 *)(iVar1 + 0x39a));
    iVar1 = FUN_0239f434((ushort *)(iVar2 + 0x46));
    iVar3 = FUN_0239f37c((ushort *)(iVar2 + 0x46 + iVar1));
    *(short *)(iVar2 + 0x16) = (short)iVar1 + (short)iVar3 + 10;
    *(short *)(iVar2 + 0x22) = *(short *)(iVar2 + 0x16) + 0x1c;
    *(undefined2 *)(iVar2 + 0x24) = 0x20;
  }
  return iVar4;
}



int FUN_0239fb8c(undefined2 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = *DAT_0239fc30;
  iVar2 = func_0x033a8500(iVar1 + 0x15c,0x5e);
  if (iVar2 == 0) {
    FUN_02398034(2);
    iVar4 = iVar2;
  }
  else {
    *(short *)(iVar2 + 0xc) = (short)DAT_0239fc34;
    iVar4 = iVar2 + 0x10;
    FUN_0239f4a8(iVar4,param_1);
    *(undefined2 *)(iVar2 + 0x3c) = *(undefined2 *)(iVar1 + 0x394);
    *(undefined2 *)(iVar2 + 0x3e) = *(undefined2 *)(iVar1 + 0x388);
    iVar1 = FUN_0239f434((ushort *)(iVar2 + 0x40));
    iVar3 = FUN_0239f37c((ushort *)(iVar2 + 0x40 + iVar1));
    *(short *)(iVar2 + 0x16) = (short)iVar1 + (short)iVar3 + 4;
    *(short *)(iVar2 + 0x22) = *(short *)(iVar2 + 0x16) + 0x1c;
    *(undefined2 *)(iVar2 + 0x24) = 0;
  }
  return iVar4;
}



int FUN_0239fc38(undefined2 *param_1,undefined2 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = func_0x033a8500(*DAT_0239fcb4 + 0x15c,0x36);
  if (iVar1 == 0) {
    FUN_02398034(2);
    iVar2 = iVar1;
  }
  else {
    *(short *)(iVar1 + 0xc) = (short)DAT_0239fcb8;
    iVar2 = iVar1 + 0x10;
    FUN_0239f4a8(iVar2,param_1);
    *(undefined2 *)(iVar1 + 0x3c) = param_2;
    *(undefined2 *)(iVar1 + 0x16) = 2;
    *(short *)(iVar1 + 0x22) = *(short *)(iVar1 + 0x16) + 0x1c;
    *(undefined2 *)(iVar1 + 0x24) = 0xa0;
  }
  return iVar2;
}



void FUN_0239fcbc(void)

{
  int iVar1;
  undefined2 *puVar2;
  uint uVar3;
  int iVar4;
  
  iVar1 = *DAT_0239fdb8;
  iVar4 = *(int *)(iVar1 + 0x480) + 0x24 + (uint)*(ushort *)(iVar1 + 0x3ae);
  uVar3 = (uint)*(ushort *)(iVar1 + 0x3b8);
  if (uVar3 != 0) {
    if ((*(ushort *)(iVar1 + 0x3ba) & 1) == 0) {
      FUN_02398464(iVar4 + 10,*(undefined4 *)(iVar1 + 0x3b4),uVar3 + 1);
    }
    else {
      FUN_02398464(iVar4 + 9,*(undefined4 *)(iVar1 + 0x3b4),uVar3 + 2);
      FUN_023983c0((ushort *)(iVar4 + 9),(int)(uint)*DAT_0239fdbc >> 8);
    }
  }
  *(short *)(*(int *)(*DAT_0239fdb8 + 0x480) + 10) =
       *(short *)(iVar1 + 0x3ae) + 0x26 + *(short *)(iVar1 + 0x3b8);
  FUN_023983c0((ushort *)(iVar4 + 1),*(ushort *)(iVar1 + 0x3b8) + 8 & 0xff);
  if ((*(ushort *)(*DAT_0239fdb8 + 0x63c) & 4) != 0) {
    puVar2 = (undefined2 *)(iVar4 + 0xd + (uint)*(ushort *)(iVar1 + 0x3b8) & 0xfffffffc);
    *puVar2 = (short)DAT_0239fdc0;
    puVar2[1] = (short)DAT_0239fdc4;
  }
  *(undefined2 *)(iVar1 + 0x3bc) = 0;
  return;
}



void FUN_0239fdc8(void)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  undefined2 *puVar7;
  uint uVar8;
  ushort *puVar9;
  ushort *puVar10;
  undefined2 *puVar11;
  
  iVar3 = *DAT_023a011c;
  puVar11 = *(undefined2 **)(iVar3 + 0x480);
  *puVar11 = 0;
  puVar11[1] = 0;
  puVar11[2] = 0;
  puVar11[3] = 0;
  uVar4 = FUN_02398b58();
  puVar11[4] = (short)uVar4;
  puVar11[6] = 0x80;
  puVar11[7] = 0;
  FUN_02398fd4(puVar11 + 8,DAT_023a0120,(undefined2 *)(iVar3 + 0x2f8),(undefined2 *)(iVar3 + 0x2f8))
  ;
  puVar11[0x11] = 0;
  sVar2 = (short)puVar11 + 0x24;
  *(undefined4 *)(puVar11 + 0x12) = 0;
  *(undefined4 *)(puVar11 + 0x14) = 0;
  puVar11[0x16] = *(undefined2 *)(iVar3 + 0x386);
  puVar11[0x17] = *(undefined2 *)(iVar3 + 0x394);
  puVar9 = puVar11 + 0x18;
  if ((int)((uint)*(ushort *)(iVar3 + 0x30e) << 0x1f) < 0) {
    *(undefined2 *)(iVar3 + 0x3aa) = 0;
  }
  else {
    *(short *)(iVar3 + 0x3aa) = (short)puVar9 - sVar2;
    FUN_023983c0(puVar9,0);
    puVar9 = puVar11 + 0x19;
    FUN_023983c0((ushort *)((int)puVar11 + 0x31),*(ushort *)(iVar3 + 0x336) & 0xff);
    for (uVar8 = 0; uVar8 < *(ushort *)(iVar3 + 0x336); uVar8 = uVar8 + 1) {
      uVar6 = FUN_023983a0((ushort *)(iVar3 + 0x338 + uVar8));
      FUN_023983c0(puVar9,uVar6);
      puVar9 = (ushort *)((int)puVar9 + 1);
    }
    FUN_023983c0((ushort *)((int)puVar9 + (-1 - uVar8)),uVar8 & 0xff);
  }
  iVar5 = FUN_0239f37c(puVar9);
  puVar9 = (ushort *)((int)puVar9 + iVar5);
  FUN_023983c0(puVar9,3);
  FUN_023983c0((ushort *)((int)puVar9 + 1),1);
  FUN_023983c0(puVar9 + 1,*(ushort *)(iVar3 + 0x392) & 0xff);
  *(short *)(iVar3 + 0x3ac) = (short)(ushort *)((int)puVar9 + 3) - sVar2;
  *DAT_023a0124 = *(short *)(iVar3 + 0x3ac) + 2;
  FUN_023983c0((ushort *)((int)puVar9 + 3),5);
  FUN_023983c0(puVar9 + 2,5);
  FUN_023983c0((ushort *)((int)puVar9 + 5),0);
  FUN_023983c0(puVar9 + 3,*(ushort *)(iVar3 + 0x38c) & 0xff);
  FUN_023983c0((ushort *)((int)puVar9 + 7),0);
  FUN_023983c0(puVar9 + 4,0);
  FUN_023983c0((ushort *)((int)puVar9 + 9),0);
  *(short *)(iVar3 + 0x3ae) = (short)(puVar9 + 5) - sVar2;
  *(ushort *)(iVar3 + 0x3ba) = *(ushort *)(iVar3 + 0x3ae) & 1;
  FUN_023983c0(puVar9 + 5,0xdd);
  FUN_023983c0((ushort *)((int)puVar9 + 0xb),*(ushort *)(iVar3 + 0x3b8) + 8 & 0xff);
  FUN_023983c0(puVar9 + 6,0);
  FUN_023983c0((ushort *)((int)puVar9 + 0xd),9);
  FUN_023983c0(puVar9 + 7,0xbf);
  FUN_023983c0((ushort *)((int)puVar9 + 0xf),0);
  if (*(short *)(iVar3 + 0x326) == 1) {
    FUN_023983c0(puVar9 + 8,*(ushort *)(iVar3 + 0x310) & 0xff);
    FUN_023983c0((ushort *)((int)puVar9 + 0x11),(int)(uint)*(ushort *)(iVar3 + 0x310) >> 8);
  }
  else {
    FUN_023983c0(puVar9 + 8,0xff);
    FUN_023983c0((ushort *)((int)puVar9 + 0x11),0xff);
  }
  uVar1 = *DAT_023a0128;
  FUN_023983c0(puVar9 + 9,uVar1 & 0xff);
  puVar10 = puVar9 + 10;
  FUN_023983c0((ushort *)((int)puVar9 + 0x13),(uint)(uVar1 >> 8));
  puVar9 = *(ushort **)(iVar3 + 0x3b4);
  for (uVar8 = 0; uVar8 < *(ushort *)(iVar3 + 0x3b8); uVar8 = uVar8 + 1) {
    uVar6 = FUN_023983a0(puVar9);
    FUN_023983c0(puVar10,uVar6);
    puVar10 = (ushort *)((int)puVar10 + 1);
    puVar9 = (ushort *)((int)puVar9 + 1);
  }
  if (*(short *)(iVar3 + 0x3ba) != 0) {
    puVar9 = (ushort *)(*(int *)(iVar3 + 0x3b4) + (uint)*(ushort *)(iVar3 + 0x3b8));
    for (uVar8 = 0; uVar8 < *(ushort *)(iVar3 + 0x3b8); uVar8 = uVar8 + 1) {
      uVar6 = FUN_023983a0((ushort *)((int)puVar9 + -1));
      FUN_023983c0(puVar9,uVar6);
      puVar9 = (ushort *)((int)puVar9 + -1);
    }
  }
  if ((*(ushort *)(*DAT_023a011c + 0x63c) & 4) != 0) {
    puVar7 = (undefined2 *)((int)puVar10 + 3U & 0xfffffffc);
    *puVar7 = (short)DAT_023a012c;
    puVar7[1] = (short)DAT_023a0130;
  }
  *(undefined2 *)(iVar3 + 0x3bc) = 0;
  puVar11[5] = ((short)puVar10 + 0x1c) - sVar2;
  return;
}



void FUN_023a01a8(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 *puVar3;
  
  iVar2 = *DAT_023a0234;
  puVar3 = (undefined2 *)(iVar2 + DAT_023a0238);
  puVar3[1] = puVar3[1] + 1;
  if (*(short *)(iVar2 + 0x428) == 0) {
    *puVar3 = 1;
    **(undefined2 **)(puVar3 + 4) = 0;
    *(undefined2 *)(*(int *)(puVar3 + 4) + 4) = 0;
    uVar1 = FUN_02398b58();
    *(short *)(*(int *)(puVar3 + 4) + 8) = (short)uVar1;
    *DAT_023a0240 = (ushort)(((*(uint *)(puVar3 + 4) & DAT_023a023c) << 0xf) >> 0x10) | 0x8000;
  }
  else {
    *(undefined2 *)(*(int *)(puVar3 + 4) + 4) = 0;
  }
  return;
}



void FUN_023a0244(int param_1)

{
  uint uVar1;
  
  uVar1 = FUN_0239b7c4((ushort *)(param_1 + 0x18));
  *(short *)(param_1 + 2) = (short)uVar1;
  if (*(short *)(param_1 + 2) == 0xff) {
    *(undefined2 *)(param_1 + 2) = 0;
  }
  *(short *)(param_1 + 4) = (short)*(undefined4 *)(*DAT_023a02b4 + 0x3c0);
  if ((*(ushort *)(param_1 + 0x14) & 0x4000) != 0) {
    *(short *)(param_1 + 0x12) = *(short *)(param_1 + 0x12) + 8;
  }
  FUN_0239b588(param_1);
  func_0x033a862c(*DAT_023a02b4 + 0x15c,*DAT_023a02b4 + 0x174,param_1 + -0x10);
  return;
}



void FUN_023a02b8(int param_1)

{
  FUN_023a0244(param_1);
  FUN_023a1240(1);
  return;
}



void FUN_023a02d8(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(*DAT_023a036c + param_1 * 0xc + 0x168);
  while (iVar1 = iVar2, iVar1 != -1) {
    iVar2 = func_0x033a8734(iVar1);
    if (param_1 != 2) {
      FUN_0239b51c(iVar1 + 0x10);
    }
    *(undefined2 *)(iVar1 + 0x18) = 2;
    if (param_2 != 0) {
      FUN_0239e8fc(*DAT_023a036c + 0x168 + param_1 * 0xc,iVar1);
    }
  }
  return;
}



void FUN_023a0370(void)

{
  short sVar1;
  int iVar2;
  
  iVar2 = *DAT_023a0454;
  sVar1 = *(short *)(iVar2 + 0x324);
  if (sVar1 == 1) {
    FUN_023a02d8(0,1);
    FUN_023a02d8(1,0);
    FUN_023a02d8(2,1);
    if (*(short *)(iVar2 + 0x43c) != 0) {
      *(undefined2 *)(iVar2 + 0x43c) = 0;
      *(short *)(iVar2 + 0x43e) = *(short *)(iVar2 + 0x43e) + -1;
      func_0x033a85a8(*DAT_023a0454 + 0x15c,*(undefined4 *)(iVar2 + 0x490));
    }
  }
  else if ((sVar1 == 2) || (sVar1 == 3)) {
    FUN_023a02d8(0,1);
    FUN_023a02d8(1,0);
    FUN_023a02d8(2,0);
  }
  else {
    FUN_023a02d8(0,0);
    FUN_023a02d8(1,0);
    FUN_023a02d8(2,0);
  }
  return;
}



void FUN_023a0458(ushort *param_1)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = DAT_023a04b8;
  if ((*param_1 & 1) == 0) {
    uVar2 = FUN_0239b7c4(param_1);
    if (uVar2 != 0xff) {
      FUN_023a04bc(uVar2);
    }
  }
  else {
    for (uVar2 = 1; uVar2 < *(ushort *)(*piVar1 + 0x2f6); uVar2 = uVar2 + 1) {
      FUN_023a04bc(uVar2);
    }
  }
  return;
}



void FUN_023a04bc(uint param_1)

{
  bool bVar1;
  int *piVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  bVar1 = false;
  sVar3 = FUN_0239b0bc(param_1);
  piVar2 = DAT_023a0594;
  if (sVar3 != 0) {
    uVar5 = 0;
    do {
      iVar6 = *(int *)(*piVar2 + uVar5 * 0xc + 0x168);
      if (iVar6 != -1) {
        do {
          iVar4 = func_0x033a8734(iVar6);
          if ((*(ushort *)(iVar6 + 0x12) == param_1) &&
             (iVar6 + 0x10 != *(int *)(uVar5 * 0x14 + *piVar2 + 0x40c))) {
            *(undefined2 *)(iVar6 + 0x18) = 2;
            FUN_0239b51c(iVar6 + 0x10);
            FUN_0239e8fc(*piVar2 + 0x168 + uVar5 * 0xc,iVar6);
            if (!bVar1) {
              bVar1 = true;
            }
          }
          iVar6 = iVar4;
        } while (iVar4 != -1);
      }
      uVar5 = uVar5 + 2;
    } while (uVar5 < 3);
  }
  return;
}



void FUN_023a0598(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *DAT_023a061c;
  iVar2 = iVar1 + 0x400 + param_1 * 0x14;
  func_0x033ab364(0x1000000);
  *DAT_023a0624 = *(undefined2 *)(DAT_023a0620 + param_1 * 2);
  if (*(short *)(iVar1 + 0x400 + param_1 * 0x14) != 0) {
    if ((*(ushort *)(*(int *)(iVar2 + 0xc) + 0x14) & 0x4000) == 0) {
      *(undefined2 *)(*(int *)(iVar2 + 0xc) + 0xc) = *(undefined2 *)(*(int *)(iVar2 + 8) + 4);
    }
    *(undefined2 *)(*(int *)(iVar2 + 0xc) + 0x2a) = *(undefined2 *)(*(int *)(iVar2 + 8) + 0x22);
  }
  func_0x033ab3a0();
  return;
}



void FUN_023a0628(int param_1)

{
  int iVar1;
  
  iVar1 = *DAT_023a0694 + 0x400 + param_1 * 0x14;
  if (*(short *)(*DAT_023a0694 + 0x400 + param_1 * 0x14) != 0) {
    if (**(short **)(iVar1 + 8) == 0) {
      *(undefined2 *)(*(int *)(iVar1 + 0xc) + 8) = 2;
    }
    else {
      *(short *)(*(int *)(iVar1 + 0xc) + 8) = **(short **)(iVar1 + 8);
    }
    (**(code **)(iVar1 + 0x10))(*(undefined4 *)(iVar1 + 0xc),0);
  }
  return;
}



void FUN_023a0698(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *DAT_023a0740;
  uVar2 = func_0x033ab364(0x1000000);
  if (*(short *)(*DAT_023a0740 + 0x324) == 1) {
    *DAT_023a0744 = 9;
    if (*(short *)(iVar1 + 0x428) != 0) {
      FUN_023a0628(2);
    }
    FUN_023a02d8(2,1);
  }
  else {
    *DAT_023a0744 = 1;
  }
  if (*(short *)(iVar1 + 0x400) != 0) {
    FUN_023a0628(0);
  }
  FUN_023a02d8(0,1);
  func_0x033ab3a0(uVar2);
  return;
}



void FUN_023a0748(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *DAT_023a0798;
  uVar2 = func_0x033ab364(0x1000000);
  *DAT_023a079c = 2;
  if (*(short *)(iVar1 + 0x43c) != 0) {
    func_0x033aa954();
  }
  func_0x033ab3a0(uVar2);
  return;
}



void FUN_023a07a0(void)

{
  int iVar1;
  
  iVar1 = *DAT_023a07dc;
  func_0x033ab364(0x1000000);
  *DAT_023a07e0 = 0xc0;
  *(undefined2 *)(iVar1 + 0x450) = 0;
  *(undefined2 *)(iVar1 + 0x464) = 0;
  func_0x033ab3a0();
  return;
}



void FUN_023a07e4(undefined2 *param_1)

{
  int iVar1;
  
  iVar1 = *DAT_023a0830 + DAT_023a0834;
  if ((*(ushort *)(*(int *)(param_1 + 4) + 4) & 0xff) == 0) {
    *(int *)(iVar1 + 0x6c) = *(int *)(iVar1 + 0x6c) + 1;
  }
  else {
    *(uint *)(iVar1 + 0x68) =
         *(int *)(iVar1 + 0x68) + (*(ushort *)(*(int *)(param_1 + 4) + 4) & 0xff);
  }
  param_1[2] = param_1[2] + 1;
  *param_1 = 0;
  return;
}



void FUN_023a0838(short *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = *DAT_023a094c;
  *(int *)(iVar2 + 0x528) = *(int *)(iVar2 + 0x528) + 1;
  if (((uint)(ushort)param_1[10] << 0x1c) >> 0x1e == 0) {
    FUN_0239b588((int)param_1);
    func_0x033a862c(iVar2 + 0x180,iVar2 + 0x174,param_1 + -8);
    FUN_023a09cc(param_1,0);
  }
  else {
    FUN_0239e8fc(iVar2 + 0x180,(int)(param_1 + -8));
  }
  piVar1 = DAT_023a094c;
  *(undefined2 *)(*DAT_023a094c + 0x428) = 0;
  if (-1 < (int)((uint)*(ushort *)(*(int *)(*piVar1 + 0x430) + 0xc) << 0x12)) {
    *DAT_023a0950 = 8;
    *DAT_023a0954 = 5;
    if (param_2 != 0) {
      if (*(short *)(iVar2 + 0x17c) != 0) {
        FUN_023a1240(1);
      }
      if (*(short *)(iVar2 + 0x170) != 0) {
        FUN_023a1240(0);
      }
    }
  }
  if (*(short *)(iVar2 + 0x188) == 0) {
    FUN_0239af34(0);
  }
  else if (param_2 != 0) {
    FUN_023a1240(2);
  }
  return;
}



void FUN_023a09cc(short *param_1,int param_2)

{
  ushort uVar1;
  uint uVar2;
  undefined2 *puVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  short *psVar7;
  
  iVar4 = *DAT_023a0e94;
  psVar7 = (short *)(iVar4 + 0x3d8);
  piVar5 = (int *)(iVar4 + DAT_023a0e98);
  uVar6 = (uint)(ushort)param_1[1];
  if ((param_1[4] & 2U) == 0) {
    *piVar5 = *piVar5 + 1;
    if ((param_1[0xc] & 1U) == 0) {
      piVar5[4] = piVar5[4] + 1;
    }
    else {
      piVar5[5] = piVar5[5] + 1;
    }
    uVar2 = FUN_0239b170(uVar6);
    if ((uVar2 != 0) && ((param_1[10] & 0x2000U) == 0)) {
      FUN_0239b394(uVar6);
    }
  }
  else {
    piVar5[1] = piVar5[1] + 1;
  }
  if ((int)((uint)(ushort)param_1[10] << 0x11) < 0) {
    piVar5[6] = piVar5[6] + 1;
  }
  piVar5[2] = piVar5[2] + ((ushort)param_1[6] & 0xff);
  piVar5 = DAT_023a0e94;
  uVar1 = param_1[10] & 0xfc;
  if (uVar1 < 0xa1) {
    if (uVar1 < 0xa0) {
      if (uVar1 < 0x11) {
        if (uVar1 != 0x10) goto LAB_023a0e44;
      }
      else if (uVar1 != 0x30) goto LAB_023a0e44;
      if ((param_1[4] & 2U) == 0) {
        if (param_1[0x17] == 0) {
          FUN_0239b450(uVar6,0x40);
          if (uVar1 == 0x10) {
            FUN_0239bdec(param_1 + 0xc,param_1[0x18],(int)param_1 + (ushort)param_1[9] + 0x14);
          }
          else {
            FUN_0239bcfc(param_1 + 0xc,param_1[0x18],(int)param_1 + (ushort)param_1[9] + 0x14);
          }
        }
      }
      else {
        FUN_0239b1cc(uVar6);
        puVar3 = (undefined2 *)FUN_0239f558(param_1 + 0xc,1);
        if (puVar3 != (undefined2 *)0x0) {
          *puVar3 = 2;
          if (param_2 == 0) {
            FUN_023a0244((int)puVar3);
          }
          else {
            FUN_023a02b8((int)puVar3);
          }
        }
      }
    }
    else {
      if (*(short *)(iVar4 + 0x324) == 1) {
        if (uVar6 == 0) {
          if ((param_1[0xc] & 1U) != 0) {
            for (uVar6 = 1; uVar6 < *(ushort *)(*piVar5 + 0x2f6); uVar6 = uVar6 + 1) {
              uVar1 = FUN_0239b1b0(uVar6);
              if (0x30 < uVar1) {
                FUN_0239b450(uVar6 & 0xffff,0x30);
              }
            }
          }
        }
        else {
          uVar1 = FUN_0239b1b0(uVar6);
          if (0x30 < uVar1) {
            FUN_0239b450(uVar6,0x30);
          }
        }
      }
      else if (0x30 < *(ushort *)(iVar4 + 800)) {
        func_0x033a9058(0x30);
        FUN_02399070();
      }
      if (*psVar7 == 0x71) {
        if ((param_1[4] & 2U) == 0) {
          *(undefined2 *)(*(int *)(iVar4 + 0x3f4) + 4) = 0;
        }
        else {
          *(undefined2 *)(*(int *)(iVar4 + 0x3f4) + 4) = 0xc;
        }
        *psVar7 = 0;
        FUN_0239bfe0();
      }
    }
  }
  else if (uVar1 < 0xb1) {
    if ((uVar1 == 0xb0) && ((param_1[4] & 2U) == 0)) {
      if ((param_1[0x16] == 0) && ((param_1[0x17] == 2 && (param_1[0x18] == 0)))) {
        FUN_0239b450(uVar6,0x30);
        FUN_0239bf64(param_1 + 0xc,param_1[0x16]);
      }
      else if ((param_1[0x16] == 1) && ((param_1[0x17] == 4 && (param_1[0x18] == 0)))) {
        FUN_0239b450(uVar6,0x30);
        FUN_0239bf64(param_1 + 0xc,param_1[0x16]);
      }
    }
  }
  else if (uVar1 == 0xc0) {
    if (*(short *)(iVar4 + 0x324) == 1) {
      if (uVar6 == 0) {
        if ((param_1[0xc] & 1U) != 0) {
          for (uVar2 = 1; uVar2 < *(ushort *)(*piVar5 + 0x2f6); uVar2 = uVar2 + 1) {
            uVar1 = FUN_0239b1b0(uVar2);
            if (0x20 < uVar1) {
              FUN_0239b450(uVar2 & 0xffff,0x20);
            }
          }
        }
      }
      else {
        uVar1 = FUN_0239b1b0(uVar6);
        if (0x20 < uVar1) {
          FUN_0239b450(uVar6,0x20);
        }
      }
    }
    else if (0x20 < *(ushort *)(iVar4 + 800)) {
      func_0x033a9058(0x20);
      FUN_02399070();
    }
    if (*psVar7 == 0x41) {
      if ((param_1[4] & 2U) == 0) {
        *(undefined2 *)(*(int *)(iVar4 + 0x3f4) + 4) = 0;
      }
      else {
        *(undefined2 *)(*(int *)(iVar4 + 0x3f4) + 4) = 0xc;
      }
      *psVar7 = 0;
      FUN_0239bfe0();
    }
    if (*param_1 == 1) {
      *(ushort *)(*DAT_023a0e94 + 0x50c) =
           *(ushort *)(*DAT_023a0e94 + 0x50c) & ~(ushort)(1 << (uVar6 & 0xff));
      FUN_0239ad30(uVar6);
      FUN_0239bee8(param_1 + 0xc,1);
    }
    else if (*param_1 == 2) {
      FUN_0239bee8(param_1 + 0xc,1);
    }
  }
LAB_023a0e44:
  FUN_0239b51c((int)param_1);
  func_0x033a85a8(iVar4 + 0x174,param_1 + -8);
  *(undefined2 *)(*DAT_023a0e94 + 0x414) = 0;
  if ((param_2 != 0) && (*(short *)(iVar4 + 0x17c) != 0)) {
    FUN_023a1240(1);
  }
  return;
}



void FUN_023a0e9c(int param_1,int param_2)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  
  iVar3 = *DAT_023a1028;
  piVar4 = (int *)(iVar3 + DAT_023a102c);
  FUN_0239b51c(param_1);
  if ((*(ushort *)(param_1 + 8) & 2) == 0) {
    *piVar4 = *piVar4 + 1;
    if ((int)((uint)*(ushort *)(param_1 + 0x14) << 0x17) < 0) {
      if ((*(ushort *)(param_1 + 0x24) & 1) == 0) {
        piVar4[4] = piVar4[4] + 1;
      }
      else {
        piVar4[5] = piVar4[5] + 1;
      }
    }
    else if ((*(ushort *)(param_1 + 0x18) & 1) == 0) {
      piVar4[4] = piVar4[4] + 1;
    }
    else {
      piVar4[5] = piVar4[5] + 1;
    }
  }
  else {
    piVar4[1] = piVar4[1] + 1;
  }
  if ((int)((uint)*(ushort *)(param_1 + 0x14) << 0x11) < 0) {
    piVar4[6] = piVar4[6] + 1;
  }
  FUN_0239e8fc(iVar3 + 0x168,param_1 + -0x10);
  *(undefined2 *)(*DAT_023a1028 + 0x400) = 0;
  uVar2 = FUN_0239b170((uint)*(ushort *)(param_1 + 2));
  if ((uVar2 != 0) && ((*(ushort *)(param_1 + 0x14) & 0x2000) == 0)) {
    FUN_0239b394((uint)*(ushort *)(param_1 + 2));
  }
  if (param_2 != 0) {
    if (*(short *)(iVar3 + 0x170) == 0) {
      if ((((((uint)*(ushort *)(iVar3 + 0x324) + DAT_023a1030 & 0xffff) < 2) &&
           (*(short *)(iVar3 + 800) == 0x40)) && (*(short *)(iVar3 + 0x326) != 0)) &&
         ((sVar1 = FUN_0239b0bc((uint)*(ushort *)(iVar3 + 0x3a0)), sVar1 == 0 &&
          (*(short *)(iVar3 + 0x3a6) == 0)))) {
        FUN_02399428(1);
      }
    }
    else {
      FUN_023a1240(0);
    }
  }
  return;
}



void FUN_023a1034(int param_1,int param_2)

{
  ushort *puVar1;
  int *piVar2;
  undefined2 *puVar3;
  
  if ((*(ushort *)(param_2 + 0x24) & 0x4000) == 0) {
    if (*(ushort *)(param_2 + 0xc) == DAT_023a116c) {
      FUN_02398464(param_1,param_2 + 0x18,*(ushort *)(param_2 + 0x16) + 0x24);
    }
    else {
      FUN_02398428(param_1,param_2 + 0x18,*(undefined4 *)(param_2 + 0x3c),
                   (uint)*(ushort *)(param_2 + 0x16));
    }
  }
  else {
    if (*(ushort *)(param_2 + 0xc) == DAT_023a116c) {
      FUN_023983ec(param_1,param_2 + 0x18,param_2 + 0x3c,(uint)*(ushort *)(param_2 + 0x16));
    }
    else {
      FUN_023983ec(param_1,param_2 + 0x18,*(undefined4 *)(param_2 + 0x3c),
                   (uint)*(ushort *)(param_2 + 0x16));
    }
    puVar1 = DAT_023a1170;
    *(ushort *)(param_1 + 0x24) = *DAT_023a1170 + *DAT_023a1170 * 0x100;
    piVar2 = DAT_023a1174;
    *(ushort *)(param_1 + 0x26) = *puVar1 & 0xff | *(short *)(*DAT_023a1174 + 0x30a) << 0xe;
    if ((*(ushort *)(*piVar2 + 0x63c) & 8) != 0) {
      puVar3 = (undefined2 *)(param_1 + (uint)*(ushort *)(param_2 + 0x22) + 5 & 0xfffffffe);
      *puVar3 = 0;
      puVar3[1] = 0;
    }
  }
  if ((*(ushort *)(*DAT_023a1174 + 0x63c) & 4) != 0) {
    puVar3 = (undefined2 *)(param_1 + (uint)*(ushort *)(param_2 + 0x22) + 0xb & 0xfffffffc);
    *puVar3 = (short)DAT_023a1178;
    puVar3[1] = (short)DAT_023a117c;
  }
  return;
}



void FUN_023a1180(void)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  short *psVar5;
  
  iVar3 = *DAT_023a1230;
  psVar5 = (short *)(iVar3 + DAT_023a1234);
  uVar1 = *(ushort *)(iVar3 + 0x188);
  if (uVar1 != 0) {
    uVar2 = func_0x033ab364(0x1000000);
    if (*psVar5 == 0) {
      *psVar5 = 1;
      psVar5[1] = psVar5[1] + 1;
      iVar3 = *(int *)(iVar3 + 0x180);
      uVar4 = *(uint *)(psVar5 + 4);
      *(int *)(psVar5 + 6) = iVar3 + 0x10;
      FUN_023a1034(uVar4,iVar3);
      if (1 < uVar1) {
        *(ushort *)(uVar4 + 0xc) = *(ushort *)(uVar4 + 0xc) | 0x2000;
      }
      *DAT_023a123c = (ushort)((uVar4 & DAT_023a1238) >> 1) | 0x8000;
      func_0x033ab3a0(uVar2);
    }
    else {
      func_0x033ab3a0();
    }
  }
  return;
}



void FUN_023a1240(int param_1)

{
  short sVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  ushort *puVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  short *psVar10;
  int *piVar11;
  int local_34;
  
  iVar7 = *DAT_023a1480;
  psVar10 = (short *)(param_1 * 0x14 + iVar7 + 0x400);
  piVar11 = (int *)(param_1 * 0xc + iVar7 + 0x168);
  if (*(short *)(piVar11 + 2) != 0) {
    uVar3 = func_0x033ab364(0x1000000);
    if (*psVar10 == 0) {
      iVar4 = *piVar11;
      while (local_34 = iVar4, local_34 != -1) {
        iVar4 = func_0x033a8734();
        iVar9 = local_34 + 0x10;
        uVar8 = (uint)*(ushort *)(local_34 + 0x12);
        if (((uint)*(ushort *)(iVar7 + 0x3a4) <
             (*(int *)(iVar7 + 0x3c0) - (uint)*(ushort *)(local_34 + 0x14) & 0xffff)) &&
           ((((uint)*(ushort *)(local_34 + 0x24) << 0x1c) >> 0x1e != 0 ||
            (*(short *)(local_34 + 0x1c) != 0)))) {
          *(short *)(iVar7 + 0x4b0) = *(short *)(iVar7 + 0x4b0) + 1;
          *(undefined2 *)(local_34 + 0x18) = 2;
          psVar10[2] = psVar10[2] + 1;
          (**(code **)(psVar10 + 8))(iVar9,0);
        }
        else {
          if ((param_1 != 0) && ((param_1 != 1 || (sVar1 = FUN_0239b1b0(uVar8), sVar1 != 0x40))))
          goto LAB_023a13b0;
          uVar5 = FUN_0239b190(uVar8);
          if (uVar5 != 0) {
            sVar1 = FUN_0239b1b0(uVar8);
            if (sVar1 == 0x40) {
LAB_023a13b0:
              *psVar10 = 1;
              psVar10[1] = psVar10[1] + 1;
              *(int *)(psVar10 + 6) = iVar9;
              uVar5 = *(uint *)(psVar10 + 4);
              if (*(short *)(iVar7 + 0x328) == 0) {
                FUN_02399428(2);
              }
              FUN_023a1034(uVar5,local_34);
              if ((*(short *)(iVar7 + 0x324) == 1) && (uVar2 = FUN_0239b0bc(uVar8), 1 < uVar2)) {
                *(ushort *)(uVar5 + 0xc) = *(ushort *)(uVar5 + 0xc) | 0x2000;
              }
              puVar6 = (ushort *)(DAT_023a1484 + param_1 * 4);
              uVar2 = (ushort)((uVar5 & DAT_023a1488) >> 1);
              if ((*(ushort *)(local_34 + 0x24) & 0xc) == 4) {
                *puVar6 = uVar2 | 0xa000;
              }
              else if ((*(ushort *)(local_34 + 0x24) & 0xfc) == 0x50) {
                *puVar6 = uVar2 | 0x9000;
              }
              else {
                *puVar6 = uVar2 | 0x8000;
              }
              func_0x033ab3a0(uVar3);
              return;
            }
            *(undefined2 *)(local_34 + 0x18) = 2;
            FUN_0239e8fc(piVar11,local_34);
            FUN_0239b51c(iVar9);
          }
        }
      }
      func_0x033ab3a0(uVar3);
    }
    else {
      func_0x033ab3a0();
    }
  }
  return;
}



void FUN_023a148c(void)

{
  short sVar1;
  int *piVar2;
  short *psVar3;
  uint uVar4;
  int iVar5;
  
  piVar2 = DAT_023a14fc;
  iVar5 = *DAT_023a14fc + DAT_023a1500;
  uVar4 = 0;
  do {
    psVar3 = (short *)(iVar5 + uVar4 * 0x18);
    sVar1 = *(short *)(iVar5 + uVar4 * 0x18);
    if ((sVar1 != 0) && (*psVar3 = sVar1 + -1, *psVar3 == 0)) {
      func_0x033a85a8(*piVar2 + 0x15c,*(undefined4 *)(psVar3 + 10));
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < 3);
  return;
}



void FUN_023a1504(ushort *param_1,short *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  uint unaff_r5;
  uint uVar6;
  int iVar7;
  uint unaff_r11;
  int local_30;
  
  iVar3 = *DAT_023a1738;
  iVar7 = iVar3 + DAT_023a173c;
  param_1[4] = param_1[4] - 0x18;
  uVar6 = 0;
  do {
    if (2 < uVar6) {
LAB_023a15e4:
      if (uVar6 != 3) {
        iVar5 = uVar6 * 0x18;
        iVar1 = *(int *)(iVar7 + iVar5 + 0x14);
        uVar6 = *(ushort *)(iVar1 + 0x20) + unaff_r5;
        if (DAT_023a1740 < uVar6) {
          func_0x033a85a8(iVar3 + 0x15c,iVar1);
          *(undefined2 *)(iVar7 + iVar5) = 0;
        }
        else {
          func_0x033adb60((int)param_1 + local_30 + 0x24,
                          iVar1 + 0x3c + (uint)*(ushort *)(iVar1 + 0x20),unaff_r5 + 1);
          *(short *)(iVar1 + 0x20) = (short)uVar6;
          iVar2 = func_0x033b6b64(*param_1 & 0xf0,0x10);
          puVar4 = (undefined2 *)(iVar7 + iVar5);
          puVar4[8] = puVar4[8] & 0xfff0 |
                      (ushort)(((iVar2 - unaff_r11) + ((ushort)puVar4[8] & 0xf)) * 0x10000 >> 0x10)
                      & 0xf;
          *(int *)(*DAT_023a1738 + 0x538) = *(int *)(*DAT_023a1738 + 0x538) + iVar2;
          if ((*param_1 & 0x100) == 0) {
            *puVar4 = 0;
            *(ushort *)(iVar1 + 0x18) = (*(ushort *)(iVar1 + 0x18) & 0xff0f) + 0x10;
            *(short *)(iVar1 + 0x20) = *(short *)(iVar1 + 0x20) + 0x18;
            if ((*(ushort *)(iVar1 + 0x18) & 0xf) == 0) {
              func_0x033a862c(iVar3 + 0x15c,iVar3 + 0x1b0,iVar1);
              func_0x033a81e8(1,7);
            }
            else if ((*(ushort *)(iVar1 + 0x18) & 0xf) == 8) {
              func_0x033a862c(iVar3 + 0x15c,iVar3 + 0x198,iVar1);
              func_0x033a81e8(2,6);
            }
            else {
              func_0x033a85a8(iVar3 + 0x15c,iVar1);
            }
          }
        }
      }
      return;
    }
    iVar1 = uVar6 * 0x18;
    iVar5 = iVar7 + iVar1;
    if ((((*(short *)(iVar7 + iVar1) != 0) &&
         (iVar2 = FUN_02398c80((short *)(iVar5 + 4),param_2), iVar2 != 0)) &&
        (iVar2 = FUN_02398c80((short *)(iVar5 + 10),param_2 + 3), iVar2 != 0)) &&
       (((uint)(ushort)param_2[6] << 0x10) >> 0x14 ==
        ((uint)*(ushort *)(iVar5 + 0x10) << 0x10) >> 0x14)) {
      unaff_r11 = (uint)*(ushort *)(iVar7 + iVar1 + 0x10) - (uint)(ushort)param_2[6];
      if ((unaff_r11 & 0x80000000) != 0) {
        return;
      }
      local_30 = unaff_r11 * *(ushort *)(iVar7 + iVar1 + 2);
      unaff_r5 = (uint)param_1[4] - local_30;
      if (unaff_r5 == 0) {
        return;
      }
      if ((unaff_r5 & 0x80000000) != 0) {
        return;
      }
      goto LAB_023a15e4;
    }
    uVar6 = uVar6 + 1;
  } while( true );
}



void FUN_023a1744(ushort *param_1,short *param_2)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  
  iVar7 = *DAT_023a1988 + DAT_023a198c;
  uVar6 = 0;
  uVar2 = 0xffffffff;
  while( true ) {
    if (2 < uVar6) {
      if (uVar2 != 0xffffffff) {
        iVar3 = func_0x033a8500(*DAT_023a1988 + 0x15c,DAT_023a1990);
        if (iVar3 == 0) {
          FUN_02398034(4);
        }
        else {
          iVar5 = iVar7 + uVar2 * 0x18;
          func_0x033adb60(param_2,iVar5 + 4,0x10);
          *(undefined2 *)(iVar7 + uVar2 * 0x18) = 5;
          *(int *)(iVar5 + 0x14) = iVar3;
          func_0x033adb60(param_1,iVar3 + 0x18,param_1[4] + 0xc);
          func_0x033adad8(*(undefined4 *)(*DAT_023a1988 + 0x2e0));
          iVar7 = func_0x033b6b64(*(ushort *)(iVar3 + 0x18) & 0xf0,0x10);
          *(ushort *)(iVar5 + 0x10) = *(ushort *)(iVar5 + 0x10) & 0xfff0 | (ushort)iVar7 & 0xf;
          *(int *)(*DAT_023a1988 + 0x538) = *(int *)(*DAT_023a1988 + 0x538) + iVar7;
          *(ushort *)(iVar3 + 0x20) = param_1[4] - 0x18;
          uVar1 = func_0x033b6d70(*(undefined2 *)(iVar3 + 0x20));
          *(undefined2 *)(iVar5 + 2) = uVar1;
        }
      }
      return;
    }
    iVar3 = iVar7 + uVar6 * 0x18;
    uVar4 = uVar6;
    if ((((*(short *)(iVar7 + uVar6 * 0x18) != 0) &&
         (iVar5 = FUN_02398c80((short *)(iVar3 + 4),param_2), uVar4 = uVar2, iVar5 != 0)) &&
        (iVar5 = FUN_02398c80((short *)(iVar3 + 10),param_2 + 3), iVar5 != 0)) &&
       (((uint)(ushort)param_2[6] << 0x10) >> 0x14 ==
        ((uint)*(ushort *)(iVar3 + 0x10) << 0x10) >> 0x14)) break;
    uVar6 = uVar6 + 1;
    uVar2 = uVar4;
  }
  iVar7 = func_0x033b6b64(*param_1 & 0xf0,0x10);
  uVar2 = iVar7 - (*(ushort *)(iVar3 + 0x10) & 0xf);
  if (uVar2 == 0) {
    return;
  }
  if ((uVar2 & 0x80000000) != 0) {
    return;
  }
  iVar5 = *(int *)(iVar3 + 0x14);
  uVar2 = (uint)*(ushort *)(iVar5 + 0x20);
  uVar6 = (param_1[4] - uVar2) - 0x18;
  if (uVar6 == 0) {
    return;
  }
  if ((uVar6 & 0x80000000) != 0) {
    return;
  }
  func_0x033adb60((int)param_1 + uVar2 + 0x24,iVar5 + 0x3c + uVar2,uVar6);
  *(short *)(iVar5 + 0x20) = *(short *)(iVar5 + 0x20) + (short)uVar6;
  *(ushort *)(iVar3 + 0x10) = *(ushort *)(iVar3 + 0x10) & 0xfff0 | (ushort)iVar7 & 0xf;
  *(int *)(*DAT_023a1988 + 0x538) = *(int *)(*DAT_023a1988 + 0x538) + iVar7;
  return;
}



void FUN_023a1994(void)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  short asStack_28 [3];
  undefined2 auStack_22 [3];
  undefined2 local_1c;
  
  iVar2 = *DAT_023a1aa8;
  iVar3 = *(int *)(iVar2 + 0x1bc);
  if (iVar3 == -1) {
    return;
  }
  if ((*(short *)(iVar2 + 800) == 0x40) && (*(ushort *)(iVar3 + 0x20) <= DAT_023a1aac)) {
    uVar1 = *(ushort *)(iVar3 + 0x24);
    if ((uVar1 & 0x100) == 0) {
      FUN_02399054(asStack_28,(undefined2 *)(iVar3 + 0x28));
      if ((uVar1 & 0x200) == 0) {
        FUN_02399054(auStack_22,(undefined2 *)(iVar3 + 0x2e));
      }
      else {
        FUN_02399054(auStack_22,(undefined2 *)(iVar3 + 0x34));
      }
    }
    else {
      FUN_02399054(asStack_28,(undefined2 *)(iVar3 + 0x34));
      if ((uVar1 & 0x200) != 0) goto LAB_023a1a78;
      FUN_02399054(auStack_22,(undefined2 *)(iVar3 + 0x2e));
    }
    local_1c = *(undefined2 *)(iVar3 + 0x3a);
    if (((uVar1 & 0x400) == 0) || ((*(ushort *)(iVar3 + 0x3a) & 0xf) != 0)) {
      FUN_023a1504((ushort *)(iVar3 + 0x18),asStack_28);
    }
    else {
      FUN_023a1744((ushort *)(iVar3 + 0x18),asStack_28);
    }
  }
LAB_023a1a78:
  func_0x033a85a8(iVar2 + 0x1bc,iVar3);
  if (*(short *)(iVar2 + 0x1c4) != 0) {
    func_0x033a81e8(2,9);
  }
  return;
}



undefined4 FUN_023a1ab0(int param_1)

{
  undefined2 uVar1;
  ushort uVar2;
  uint uVar3;
  undefined4 uVar4;
  ushort *puVar5;
  uint uVar6;
  
  uVar1 = FUN_0239b138((uint)*(ushort *)(param_1 + 2));
  FUN_0239834c(uVar1);
  uVar3 = FUN_023983a0((ushort *)(param_1 + 0x33));
  uVar6 = 0;
  puVar5 = (ushort *)(param_1 + 0x34);
  while( true ) {
    if (uVar3 >> 1 <= uVar6) {
      if (((uVar3 & 1) == 0) || (uVar2 = FUN_02398314(), (*puVar5 & 0xff) == (uVar2 & 0xff))) {
        uVar4 = 1;
      }
      else {
        uVar4 = 0;
      }
      return uVar4;
    }
    uVar2 = FUN_02398314();
    if (*puVar5 != uVar2) break;
    uVar6 = uVar6 + 1;
    puVar5 = puVar5 + 1;
  }
  return 0;
}



void FUN_023a1b38(int param_1,int param_2)

{
  short sVar1;
  undefined2 uVar2;
  uint uVar3;
  undefined2 *puVar4;
  uint uVar5;
  
  sVar1 = *DAT_023a1ba8 + *DAT_023a1ba8 * 0x100;
  if (sVar1 == 0) {
    sVar1 = 1;
  }
  FUN_0239834c(sVar1);
  FUN_0239b310(param_1,sVar1);
  uVar3 = FUN_023983a0((ushort *)(param_2 + 0x33));
  puVar4 = (undefined2 *)(param_2 + 0x34);
  for (uVar5 = 0; uVar5 < uVar3; uVar5 = uVar5 + 2) {
    uVar2 = FUN_02398314();
    *puVar4 = uVar2;
    puVar4 = puVar4 + 1;
  }
  return;
}



void FUN_023a1bac(void)

{
  uint uVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  
  iVar9 = *DAT_023a1eec;
  iVar11 = iVar9 + DAT_023a1ef0;
  sVar2 = *(short *)(iVar9 + 0x324);
  iVar5 = *(int *)(iVar9 + 0x1b0);
  if (iVar5 == -1) {
    return;
  }
  iVar10 = iVar5 + 0x10;
  if ((*(ushort *)(iVar5 + 0x28) & 1) == 0) {
    *(int *)(iVar11 + 0x28) = *(int *)(iVar11 + 0x28) + 1;
  }
  else {
    *(int *)(iVar11 + 0x2c) = *(int *)(iVar11 + 0x2c) + 1;
  }
  iVar6 = func_0x033b6b64(*(ushort *)(iVar5 + 0x18) & 0xf0,0x10);
  *(int *)(iVar11 + 0x24) = *(int *)(iVar11 + 0x24) + iVar6 + -1;
  uVar7 = (uint)*(ushort *)(iVar5 + 0x24);
  uVar1 = (uVar7 << 0x1c) >> 0x1e;
  uVar7 = (uVar7 << 0x18) >> 0x1c;
  uVar8 = FUN_0239b67c((ushort *)(iVar5 + 0x2e));
  *(short *)(iVar5 + 0x12) = (short)uVar8;
  if (uVar8 == 0xff) {
    *(undefined2 *)(iVar5 + 0x12) = 0;
    if ((sVar2 == 1) && (uVar1 == 0)) {
      if (uVar7 == 0) {
        FUN_023a3124(iVar10);
      }
      else if (uVar7 == 4) {
        FUN_023a2cb8(iVar10);
      }
      else if (uVar7 == 0xb) {
        FUN_023a23b4(iVar10);
      }
    }
  }
  else {
    FUN_0239b438(uVar8 & 0xffff,*(ushort *)(iVar5 + 0x22) & 0xff);
    if (uVar1 == 0) {
      sVar3 = *(short *)(iVar5 + 0x3a);
      sVar4 = FUN_0239b11c(uVar8);
      if (sVar3 == sVar4) {
        *(int *)(iVar11 + 0x3c) = *(int *)(iVar11 + 0x3c) + 1;
        goto switchD_023a1d40_caseD_d;
      }
      FUN_0239b328(uVar8,sVar3);
    }
    if (sVar2 == 1) {
      FUN_0239b3d4(uVar8 & 0xffff,((uint)*(ushort *)(iVar5 + 0x24) << 0x13) >> 0x1f);
      if (uVar1 == 0) {
        switch(uVar7) {
        case 0:
          FUN_023a3124(iVar10);
          break;
        case 1:
          break;
        case 2:
          FUN_023a2e8c(iVar10);
          break;
        case 3:
          break;
        case 4:
          FUN_023a2cb8(iVar10);
          break;
        case 5:
          FUN_023a28c0(iVar10,(ushort **)0x0);
          break;
        case 6:
          break;
        case 7:
          break;
        case 8:
          FUN_023a33b8(iVar10);
          break;
        case 9:
          break;
        case 10:
          FUN_023a32c8(iVar10);
          break;
        case 0xb:
          FUN_023a23b4(iVar10);
          break;
        case 0xc:
          FUN_023a22f8(iVar10);
        }
      }
      else if ((uVar1 == 1) && (uVar7 == 10)) {
        FUN_023a2290(iVar10);
      }
    }
    else if ((sVar2 == 2) || (sVar2 == 3)) {
      if (uVar1 == 0) {
        switch(uVar7) {
        case 0:
          break;
        case 1:
          FUN_023a3000(iVar10);
          break;
        case 2:
          break;
        case 3:
          FUN_023a2d60(iVar10);
          break;
        case 4:
          break;
        case 5:
          FUN_023a28c0(iVar10,(ushort **)0x0);
          break;
        case 6:
          break;
        case 7:
          break;
        case 8:
          FUN_023a33b8(iVar10);
          break;
        case 9:
          break;
        case 10:
          FUN_023a32c8(iVar10);
          break;
        case 0xb:
          FUN_023a23b4(iVar10);
          break;
        case 0xc:
          FUN_023a22f8(iVar10);
        }
      }
      else if ((uVar1 == 1) && ((uVar7 == 0xe || (uVar7 == 0xf)))) {
        FUN_023a228c();
      }
    }
  }
switchD_023a1d40_caseD_d:
  func_0x033a85a8(iVar9 + 0x1b0,iVar5);
  if (*(short *)(iVar9 + 0x1b8) != 0) {
    func_0x033a81e8(1,7);
  }
  return;
}



void FUN_023a1ef4(ushort **param_1)

{
  ushort uVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  ushort *puVar9;
  ushort *puVar10;
  
  iVar3 = *DAT_023a2288;
  puVar9 = *param_1;
  *(undefined2 *)((int)param_1 + 0x12) = *(undefined2 *)(iVar3 + 0x392);
  if ((*(ushort *)(param_1 + 3) & 0x800) != 0) {
    *(ushort *)((int)param_1 + 10) = *(ushort *)((int)param_1 + 10) | 1;
  }
  uVar8 = (uint)*(ushort *)(param_1 + 2);
  do {
    if ((int)uVar8 < 1) {
      if (((*(ushort *)(param_1 + 3) & 8) != 0) &&
         (((*(ushort *)(iVar3 + 0x37c) & 1) != 0 || ((*(ushort *)(param_1 + 1) & 0x8000) != 0)))) {
        *(ushort *)((int)param_1 + 10) = *(ushort *)((int)param_1 + 10) | 8;
      }
      if ((*(ushort *)(param_1 + 3) & 0x30) != 0) {
        if ((*(ushort *)((int)param_1 + 6) & 3) == (*(ushort *)(iVar3 + 0x394) & 3)) {
          *(ushort *)((int)param_1 + 10) = *(ushort *)((int)param_1 + 10) | 0x10;
        }
        if ((*(ushort *)((int)param_1 + 6) & 0x10) == (*(ushort *)(iVar3 + 0x394) & 0x10)) {
          *(ushort *)((int)param_1 + 10) = *(ushort *)((int)param_1 + 10) | 0x20;
        }
      }
      return;
    }
    uVar4 = FUN_023983a0(puVar9);
    puVar10 = puVar9 + 1;
    uVar5 = FUN_023983a0((ushort *)((int)puVar9 + 1));
    switch(uVar4) {
    case 0:
      bVar2 = true;
      for (uVar4 = 0; uVar4 < uVar5; uVar4 = uVar4 + 1) {
        uVar6 = FUN_023983a0((ushort *)((int)puVar10 + uVar4));
        if (uVar6 != 0) {
          bVar2 = false;
          break;
        }
      }
      if ((bVar2) || (0x20 < uVar5)) {
        *(ushort *)(param_1 + 3) = *(ushort *)(param_1 + 3) & 0xfffe;
        param_1[7] = (ushort *)0x0;
      }
      else {
        *(ushort *)(param_1 + 3) = *(ushort *)(param_1 + 3) | 1;
        param_1[7] = puVar9;
        if ((uVar5 == 0) && ((*(ushort *)(param_1 + 3) & 0x800) != 0)) {
          *(ushort *)((int)param_1 + 10) = *(ushort *)((int)param_1 + 10) | 1;
        }
        else {
          *(ushort *)((int)param_1 + 10) = *(ushort *)((int)param_1 + 10) & 0xfffe;
          iVar7 = FUN_02398cbc(uVar5 & 0xffff,puVar10);
          if (iVar7 != 0) {
            *(ushort *)((int)param_1 + 10) = *(ushort *)((int)param_1 + 10) | 1;
          }
        }
      }
      break;
    case 1:
      if (uVar5 != 0) {
        *(ushort *)(param_1 + 3) = *(ushort *)(param_1 + 3) | 4;
        FUN_02398ba4((int)puVar9,(ushort *)(param_1 + 5));
        uVar1 = *(ushort *)(iVar3 + 0x378);
        if (((*(ushort *)(param_1 + 5) & ~(uVar1 | *(ushort *)(iVar3 + 0x37a))) == 0) &&
           (uVar1 == (uVar1 & (*(ushort *)(param_1 + 5) | *(ushort *)((int)param_1 + 0x16))))) {
          *(ushort *)((int)param_1 + 10) = *(ushort *)((int)param_1 + 10) | 4;
        }
        else {
          *(ushort *)((int)param_1 + 10) = *(ushort *)((int)param_1 + 10) & 0xfffb;
        }
      }
      break;
    case 2:
      break;
    case 3:
      if (uVar5 != 0) {
        *(ushort *)(param_1 + 3) = *(ushort *)(param_1 + 3) | 2;
        uVar4 = FUN_023983a0(puVar10);
        *(short *)((int)param_1 + 0x12) = (short)uVar4;
        if (*(short *)((int)param_1 + 0x12) == *(short *)(*(int *)(*DAT_023a2288 + 0x3f0) + 0x4a)) {
          *(ushort *)((int)param_1 + 10) = *(ushort *)((int)param_1 + 10) | 2;
        }
        else {
          *(ushort *)((int)param_1 + 10) = *(ushort *)((int)param_1 + 10) & 0xfffd;
        }
      }
      break;
    case 4:
      if (5 < uVar5) {
        *(ushort *)(param_1 + 3) = *(ushort *)(param_1 + 3) | 0x200;
        param_1[8] = puVar9;
      }
      break;
    case 5:
      if (2 < uVar5) {
        *(ushort *)(param_1 + 3) = *(ushort *)(param_1 + 3) | 0x100;
        param_1[9] = puVar9;
      }
      break;
    case 6:
      break;
    default:
      if (uVar4 == 0xdd) {
        if ((((uVar5 < 8) || (uVar4 = FUN_023983a0(puVar10), uVar4 != 0)) ||
            (uVar4 = FUN_023983a0((ushort *)((int)puVar9 + 3)), uVar4 != 9)) ||
           ((uVar4 = FUN_023983a0(puVar9 + 2), uVar4 != 0xbf ||
            (uVar4 = FUN_023983a0((ushort *)((int)puVar9 + 5)), uVar4 != 0)))) {
          *(short *)(param_1 + 6) = *(short *)(param_1 + 6) + 1;
          *(short *)((int)param_1 + 0x1a) = *(short *)((int)param_1 + 0x1a) + (short)uVar5 + 2;
        }
        else {
          *(ushort *)(param_1 + 3) = *(ushort *)(param_1 + 3) | 0x400;
          param_1[10] = puVar9;
        }
      }
      else {
        *(short *)(param_1 + 6) = *(short *)(param_1 + 6) + 1;
        *(short *)((int)param_1 + 0x1a) = *(short *)((int)param_1 + 0x1a) + (short)uVar5 + 2;
      }
    }
    puVar9 = (ushort *)((int)puVar10 + uVar5);
    uVar8 = uVar8 - (uVar5 + 2);
  } while( true );
}



void FUN_023a228c(void)

{
  return;
}



void FUN_023a2290(int param_1)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  
  iVar3 = *DAT_023a22f4;
  uVar1 = *(ushort *)(param_1 + 2);
  sVar2 = FUN_0239b1b0((uint)uVar1);
  if (sVar2 == 0x40) {
    FUN_0239b370((uint)uVar1);
    if (*(short *)(iVar3 + 0x17c) != 0) {
      FUN_023a1240(1);
    }
    if (*(short *)(iVar3 + 0x170) != 0) {
      FUN_023a1240(0);
    }
  }
  return;
}



uint FUN_023a22f8(int param_1)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  iVar3 = *DAT_023a23b0;
  uVar5 = (uint)*(ushort *)(param_1 + 2);
  uVar4 = (uint)*(ushort *)(iVar3 + 0x324);
  if (uVar4 == 1) {
    uVar2 = FUN_0239b1b0(uVar5);
    uVar4 = (uint)uVar2;
    if (0x20 < uVar4) {
      FUN_0239b450(uVar5,0x20);
      FUN_0239bee8((undefined2 *)(param_1 + 0x1e),*(undefined2 *)(param_1 + 0x2c));
      uVar4 = FUN_023a04bc(uVar5);
    }
  }
  else if ((((uVar4 == 2) || (uVar4 == 3)) && (uVar4 = (uint)*(ushort *)(iVar3 + 800), 0x20 < uVar4)
           ) && (uVar4 = FUN_02398c80((short *)(param_1 + 0x1e),(short *)(iVar3 + 0x39a)),
                uVar4 != 0)) {
    func_0x033a9058(0x20);
    FUN_02399070();
    bVar1 = FUN_0239bee8((undefined2 *)(param_1 + 0x1e),*(undefined2 *)(param_1 + 0x2c));
    uVar4 = (uint)bVar1;
  }
  return uVar4;
}



void FUN_023a23b4(int param_1)

{
  undefined2 *puVar1;
  short sVar2;
  ushort uVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  undefined2 unaff_r4;
  uint uVar7;
  short *psVar8;
  short *psVar9;
  bool bVar10;
  bool bVar11;
  
  puVar1 = DAT_023a28bc;
  iVar6 = *DAT_023a28b0;
  psVar9 = (short *)(iVar6 + 0x3d8);
  psVar8 = (short *)(param_1 + 0x2c);
  if ((*(ushort *)(iVar6 + 0x63c) & 8) != 0) {
    uVar3 = *DAT_023a28b4;
    if (((((uVar3 & 1) == 0) || (*(short *)(iVar6 + 0x400) == 0)) &&
        (((uVar3 & 4) == 0 || (*(short *)(iVar6 + 0x414) == 0)))) &&
       ((((uVar3 & 8) == 0 || (*(short *)(iVar6 + 0x428) == 0)) && ((*DAT_023a28b8 & 1) == 0)))) {
      *DAT_023a28bc = 0;
      *puVar1 = 0x8000;
      *(undefined2 *)(*DAT_023a28b0 + 0x4b6) = 0;
    }
  }
  sVar2 = *(short *)(param_1 + 0x2e) + 1;
  uVar7 = (uint)*(ushort *)(param_1 + 2);
  bVar10 = uVar7 == 0;
  if (bVar10) {
    unaff_r4 = 0x13;
  }
  else {
    if (*(short *)(iVar6 + 0x324) == 1) {
      uVar3 = FUN_0239b1b0(uVar7);
      if (0x20 < uVar3) {
        FUN_0239b450(uVar7,0x20);
        FUN_0239bee8((undefined2 *)(param_1 + 0x1e),1);
      }
      if (((*(ushort *)(param_1 + 8) & 0x400) != 0) && (sVar4 = FUN_0239b138(uVar7), sVar4 != 0)) {
        bVar10 = true;
        *psVar8 = 1;
        unaff_r4 = 0xf;
        sVar2 = 4;
        FUN_0239b310(uVar7,0);
        goto LAB_023a2874;
      }
    }
    if (*psVar8 == 0) {
      sVar4 = *(short *)(iVar6 + 0x324);
      if (sVar4 == 1) {
        bVar11 = *(short *)(*DAT_023a28b0 + 0x306) == 1;
        if (bVar11) {
          unaff_r4 = 0xd;
        }
        bVar10 = bVar11 || bVar10;
        if (bVar11) goto LAB_023a2874;
      }
      if (sVar4 == 1) {
        if (*(short *)(param_1 + 0x2e) == 1) {
          unaff_r4 = 0;
        }
        else {
          unaff_r4 = 0xe;
          sVar2 = 2;
        }
        bVar10 = true;
      }
      else if (((sVar4 != 1) && (*(short *)(param_1 + 0x2e) == 2)) &&
              ((*(short *)(*(int *)(iVar6 + 0x3f0) + 0x16) == 0 &&
               ((iVar5 = FUN_02398c80((short *)(*(int *)(iVar6 + 0x3f0) + 0x10),
                                      (short *)(param_1 + 0x1e)), iVar5 != 0 && (*psVar9 == 0x31))))
              )) {
        FUN_02398518();
        if (*(short *)(param_1 + 0x30) == 0) {
          func_0x033a9058(0x30);
          *(undefined2 *)(*(int *)(iVar6 + 0x3f4) + 4) = 0;
          *(undefined2 *)(*(int *)(iVar6 + 0x3f4) + 6) = 0;
        }
        else {
          *(undefined2 *)(*(int *)(iVar6 + 0x3f4) + 4) = 0xc;
          *(undefined2 *)(*(int *)(iVar6 + 0x3f4) + 6) = *(undefined2 *)(param_1 + 0x30);
        }
        *psVar9 = 0x35;
        func_0x033a81e8(2,2);
      }
    }
    else if (*psVar8 == 1) {
      if (*(short *)(iVar6 + 0x324) == 1) {
        FUN_0239b450(uVar7,0x20);
        if (*(short *)(param_1 + 0x2e) == 1) {
          iVar6 = FUN_0239f5dc((undefined2 *)(param_1 + 0x1e),0x80);
          if (iVar6 != 0) {
            *(short *)(iVar6 + 0x2c) = *psVar8;
            *(short *)(iVar6 + 0x2e) = sVar2;
            *(undefined2 *)(iVar6 + 0x30) = 0;
            FUN_023a1b38(uVar7,iVar6);
            FUN_023a02b8(iVar6);
          }
        }
        else if (*(short *)(param_1 + 0x2e) == 3) {
          sVar4 = FUN_0239b1b0(uVar7);
          if ((sVar4 == 0x20) && (sVar4 = FUN_0239b138(uVar7), sVar4 != 0)) {
            iVar6 = FUN_023a1ab0(param_1);
            if (iVar6 == 0) {
              unaff_r4 = 0xf;
              bVar10 = true;
              FUN_0239b310(uVar7,0);
            }
            else {
              FUN_0239b310(uVar7,0);
              unaff_r4 = 0;
              bVar10 = true;
            }
          }
          else {
            unaff_r4 = 1;
            bVar10 = true;
          }
        }
        else {
          FUN_0239b310(uVar7,0);
          unaff_r4 = 0xe;
          sVar2 = 2;
          bVar10 = true;
        }
      }
      else if ((*(short *)(*(int *)(iVar6 + 0x3f0) + 0x16) == 1) &&
              (iVar5 = FUN_02398c80((short *)(*(int *)(iVar6 + 0x3f0) + 0x10),
                                    (short *)(param_1 + 0x1e)), iVar5 != 0)) {
        if (*(short *)(param_1 + 0x2e) == 2) {
          if (*psVar9 == 0x31) {
            if (*(short *)(param_1 + 0x30) == 0) {
              *psVar9 = 0x33;
              uVar7 = FUN_023983a0((ushort *)(param_1 + 0x33));
              iVar6 = FUN_0239f5dc((undefined2 *)(param_1 + 0x1e),uVar7);
              if (iVar6 != 0) {
                *(ushort *)(iVar6 + 0x14) = *(ushort *)(iVar6 + 0x14) | 0x4000;
                func_0x033adb60(param_1 + 0x2c,iVar6 + 0x2c,*(ushort *)(param_1 + 6) + 1);
                *(short *)(iVar6 + 0x2c) = *psVar8;
                *(undefined2 *)(iVar6 + 0x2e) = 3;
                *(undefined2 *)(iVar6 + 0x30) = 0;
                FUN_023a02b8(iVar6);
              }
            }
            else {
              FUN_02398518();
              *psVar9 = 0x35;
              *(undefined2 *)(*(int *)(iVar6 + 0x3f4) + 4) = 0xc;
              *(undefined2 *)(*(int *)(iVar6 + 0x3f4) + 6) = *(undefined2 *)(param_1 + 0x30);
              func_0x033a81e8(2,2);
              func_0x033a9058(0x20);
            }
          }
        }
        else if ((*(short *)(param_1 + 0x2e) == 4) && (*psVar9 == 0x33)) {
          FUN_02398518();
          if (*(short *)(param_1 + 0x30) == 0) {
            func_0x033a9058(0x30);
            *(undefined2 *)(*(int *)(iVar6 + 0x3f4) + 4) = 0;
            *(undefined2 *)(*(int *)(iVar6 + 0x3f4) + 6) = 0;
          }
          else {
            *(undefined2 *)(*(int *)(iVar6 + 0x3f4) + 4) = 0xc;
            *(undefined2 *)(*(int *)(iVar6 + 0x3f4) + 6) = *(undefined2 *)(param_1 + 0x30);
          }
          *psVar9 = 0x35;
          func_0x033a81e8(2,2);
        }
      }
    }
    else if (*(short *)(iVar6 + 0x324) == 1) {
      unaff_r4 = 0xd;
      bVar10 = true;
    }
  }
LAB_023a2874:
  if ((bVar10) && (iVar6 = FUN_0239f5dc((undefined2 *)(param_1 + 0x1e),0), iVar6 != 0)) {
    *(short *)(iVar6 + 0x2c) = *psVar8;
    *(short *)(iVar6 + 0x2e) = sVar2;
    *(undefined2 *)(iVar6 + 0x30) = unaff_r4;
    FUN_023a02b8(iVar6);
  }
  return;
}



void FUN_023a28c0(int param_1,ushort **param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  short *psVar7;
  ushort *puVar8;
  uint uVar9;
  ushort *puVar10;
  int iVar11;
  ushort *puVar12;
  uint local_60;
  ushort *local_50;
  undefined2 local_4c;
  undefined2 local_4a;
  short local_48;
  undefined2 local_46;
  undefined2 local_44;
  
  iVar2 = *DAT_023a2cb0;
  if (*(short *)(iVar2 + 0x3d8) == 0x13) {
    iVar11 = *(int *)(iVar2 + 0x3f4);
    psVar7 = (short *)(*(int *)(iVar2 + 0x3f0) + 0x4e);
    for (uVar9 = 0; uVar9 < *(ushort *)(*(int *)(iVar2 + 0x3f0) + 0x4c); uVar9 = uVar9 + 1) {
      iVar3 = FUN_02398c80(psVar7,(short *)(param_1 + 0x24));
      if (iVar3 != 0) {
        *(ushort *)(iVar11 + 6) = *(ushort *)(iVar11 + 6) | (ushort)(1 << (uVar9 & 0xff));
        return;
      }
      psVar7 = psVar7 + 3;
    }
    puVar10 = (ushort *)(iVar11 + 10);
    for (uVar9 = 0; uVar9 < *(ushort *)(iVar11 + 8); uVar9 = uVar9 + 1) {
      iVar3 = FUN_02398c80((short *)(param_1 + 0x24),(short *)(puVar10 + 2));
      if (iVar3 != 0) {
        return;
      }
      puVar10 = puVar10 + *puVar10;
    }
    func_0x033adb48(0,puVar10,0x40);
    uVar1 = *(ushort *)(param_1 + 6);
    if (0xc < uVar1) {
      if (param_2 == (ushort **)0x0) {
        func_0x033adb7c(0,&local_50,0x2c);
        local_50 = (ushort *)(param_1 + 0x38);
        local_48 = uVar1 - 0xc;
        local_46 = 3;
        local_44 = 0x38;
        local_4c = *(undefined2 *)(param_1 + 8);
        local_4a = *(undefined2 *)(param_1 + 0x36);
        FUN_023a1ef4(&local_50);
        param_2 = &local_50;
      }
      if (param_2[10] == (ushort *)0x0) {
        *puVar10 = (ushort)(*(ushort *)((int)param_2 + 0x1a) + 0x41 >> 1);
      }
      else {
        uVar9 = FUN_023983a0((ushort *)((int)param_2[10] + 1));
        puVar10[0x1e] = (short)uVar9 - 8;
        *puVar10 = (ushort)(puVar10[0x1e] + 0x41 >> 1);
      }
      if (((*(ushort *)((int)param_2 + 10) & 1) == 1) &&
         (*puVar10 <= *(ushort *)(*DAT_023a2cb0 + 0x3dc))) {
        puVar10[0x16] = *(ushort *)(param_1 + 0x36);
        FUN_02399054(puVar10 + 2,(undefined2 *)(param_1 + 0x24));
        puVar10[0x19] = *(ushort *)(param_1 + 0x34);
        puVar10[1] = *(ushort *)(param_1 + 0x12) & 0xff;
        if (param_2[10] == (ushort *)0x0) {
          puVar10[0x1f] = *(ushort *)(param_2 + 6);
          if (*(short *)(param_2 + 6) != 0) {
            puVar8 = (ushort *)(param_1 + 0x38);
            puVar12 = puVar10 + 0x20;
            uVar9 = 0;
            local_60 = 0;
            while (uVar9 < *(ushort *)(param_2 + 6)) {
              uVar6 = FUN_023983a0(puVar8);
              uVar4 = FUN_023983a0((ushort *)((int)puVar8 + 1));
              if ((uVar6 < 7) || (puVar8 == param_2[10])) {
                puVar8 = (ushort *)((int)puVar8 + uVar4 + 2);
              }
              else {
                for (uVar6 = local_60; uVar6 < uVar4 + 2; uVar6 = uVar6 + 1) {
                  uVar5 = FUN_023983a0(puVar8);
                  FUN_023983c0(puVar12,uVar5);
                  puVar12 = (ushort *)((int)puVar12 + 1);
                  puVar8 = (ushort *)((int)puVar8 + 1);
                }
                uVar9 = uVar9 + 1;
              }
            }
          }
        }
        else {
          for (uVar9 = 0; uVar9 < puVar10[0x1e]; uVar9 = uVar9 + 1) {
            uVar6 = FUN_023983a0((ushort *)((int)param_2[10] + uVar9 + 10));
            FUN_023983c0((ushort *)((int)puVar10 + uVar9 + 0x40),uVar6);
          }
        }
        if (param_2[7] == (ushort *)0x0) {
          uVar9 = 0;
          puVar10[5] = 0;
          do {
            FUN_023983c0((ushort *)((int)puVar10 + uVar9 + 0xc),0);
            uVar9 = uVar9 + 1;
          } while (uVar9 < 0x20);
        }
        else {
          uVar9 = FUN_023983a0((ushort *)((int)param_2[7] + 1));
          puVar10[5] = (ushort)uVar9;
          for (uVar9 = 0; uVar9 < puVar10[5]; uVar9 = uVar9 + 1) {
            uVar6 = FUN_023983a0((ushort *)((int)param_2[7] + uVar9 + 2));
            FUN_023983c0((ushort *)((int)puVar10 + uVar9 + 0xc),uVar6);
          }
        }
        puVar10[0x17] = *(ushort *)(param_2 + 5);
        puVar10[0x18] = *(ushort *)((int)param_2 + 0x16);
        puVar10[0x1b] = *(ushort *)((int)param_2 + 0x12);
        if (param_2[8] != (ushort *)0x0) {
          uVar9 = FUN_023983a0((ushort *)((int)param_2[8] + 3));
          puVar10[0x1c] = (ushort)uVar9;
        }
        if (param_2[9] != (ushort *)0x0) {
          uVar9 = FUN_023983a0((ushort *)((int)param_2[9] + 3));
          puVar10[0x1a] = (ushort)uVar9;
        }
        *(ushort *)(iVar11 + 2) = *(short *)(iVar11 + 2) + *puVar10;
        *(short *)(iVar11 + 8) = *(short *)(iVar11 + 8) + 1;
        *(ushort *)(iVar2 + 0x3dc) = *(short *)(iVar2 + 0x3dc) - *puVar10;
        if (*(ushort *)(iVar2 + 0x3dc) < 0x20) {
          FUN_02398518();
          *(undefined2 *)(iVar2 + 0x3d8) = 0x15;
          func_0x033a81e8(2,0);
        }
      }
      else {
        FUN_02399054(puVar10 + 2,DAT_023a2cb4);
      }
    }
  }
  return;
}



void FUN_023a2cb8(int param_1)

{
  int iVar1;
  ushort *local_34 [2];
  undefined2 local_2c;
  ushort local_2a;
  undefined2 uStack_28;
  
  if (((*(ushort *)(param_1 + 0x24) & 1) != 0) || ((*(ushort *)(param_1 + 8) & 0x8000) != 0)) {
    func_0x033adb7c(0,local_34,0x2c);
    local_34[0] = (ushort *)(param_1 + 0x2c);
    local_2c = *(undefined2 *)(param_1 + 6);
    if (-1 < (int)((uint)*(ushort *)(*DAT_023a2d5c + 0x30e) << 0x1e)) {
      uStack_28 = 0x800;
    }
    FUN_023a1ef4(local_34);
    if (((local_2a & 1) == 1) && (iVar1 = FUN_0239f690((undefined2 *)(param_1 + 0x1e)), iVar1 != 0))
    {
      FUN_023a02b8(iVar1);
    }
  }
  return;
}



void FUN_023a2d60(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *DAT_023a2e84;
  if ((((*(short *)(iVar1 + 0x324) == 2) || (*(short *)(iVar1 + 0x324) == 3)) &&
      (*(short *)(iVar1 + 0x3d8) == 0x61)) &&
     (iVar2 = FUN_02398c80((short *)(*(int *)(iVar1 + 0x3f0) + 0x10),(short *)(param_1 + 0x1e)),
     iVar2 != 0)) {
    FUN_02398518();
    if (*(short *)(param_1 + 0x2e) == 0) {
      FUN_023990e4(*(ushort *)(param_1 + 0x30) & DAT_023a2e88);
      FUN_0239f504(*(ushort *)(iVar1 + 0x382));
      FUN_02399054((undefined2 *)(iVar1 + 0x39a),(undefined2 *)(param_1 + 0x1e));
      uVar3 = FUN_0239b7c4((ushort *)(param_1 + 0x1e));
      *(short *)(iVar1 + 0x3a0) = (short)uVar3;
      FUN_0239b450((uint)*(ushort *)(iVar1 + 0x3a0),0x40);
      func_0x033a9058(0x40);
    }
    if (*(short *)(param_1 + 0x2e) == 0) {
      *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 4) = 0;
      *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 6) = 0;
      func_0x033a9058(0x40);
    }
    else {
      *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 4) = 0xc;
      *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 6) = *(undefined2 *)(param_1 + 0x2e);
    }
    *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 8) = *(undefined2 *)(iVar1 + 0x382);
    *(short *)(iVar1 + 0x3d8) = 99;
    func_0x033a81e8(2,4);
  }
  return;
}



void FUN_023a2e8c(int param_1)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  ushort *local_44 [2];
  short local_3c;
  ushort local_3a;
  undefined2 local_38;
  undefined2 local_2e;
  ushort *local_28;
  
  iVar5 = *DAT_023a2ff8;
  uVar1 = *(ushort *)(param_1 + 6);
  if ((10 < uVar1) && (*(short *)(iVar5 + 0x324) == 1)) {
    uVar4 = (uint)*(ushort *)(param_1 + 2);
    uVar2 = FUN_0239b1b0(uVar4);
    if (uVar2 < 0x30) {
      iVar5 = FUN_0239f558((undefined2 *)(param_1 + 0x1e),6);
      if (iVar5 != 0) {
        FUN_023a02b8(iVar5);
      }
    }
    else {
      sVar3 = FUN_0239b1b0(uVar4);
      if (sVar3 == 0x40) {
        FUN_0239b450(uVar4,0x30);
        FUN_0239bc80((undefined2 *)(param_1 + 0x1e),1);
      }
      func_0x033adb7c(0,local_44,0x2c);
      local_44[0] = (ushort *)(param_1 + 0x36);
      local_3c = uVar1 - 10;
      local_38 = 0x800;
      FUN_023a1ef4(local_44);
      uVar1 = *(ushort *)(param_1 + 0x2c);
      if ((((uVar1 & DAT_023a2ffc) == 0) &&
          ((sVar3 = *(short *)(iVar5 + 0x308), sVar3 != 0 || (-1 < (int)((uint)uVar1 << 0x1b))))) &&
         ((sVar3 == 0 || ((int)((uint)*(ushort *)(param_1 + 0x2c) << 0x1b) < 0)))) {
        FUN_0239b358(uVar4,uVar1);
        if ((local_3a & 1) == 0) {
          iVar5 = 1;
        }
        else if ((local_3a & 4) == 0) {
          iVar5 = 0x12;
        }
        else {
          FUN_0239b340(uVar4,local_2e);
          iVar5 = 0;
        }
      }
      else {
        iVar5 = 10;
      }
      iVar5 = FUN_0239f7f0(uVar4,iVar5,local_28);
      if (iVar5 != 0) {
        FUN_023a02b8(iVar5);
      }
    }
  }
  return;
}



void FUN_023a3000(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *DAT_023a311c;
  if ((((*(short *)(iVar1 + 0x324) == 2) || (*(short *)(iVar1 + 0x324) == 3)) &&
      (*(short *)(iVar1 + 0x3d8) == 0x51)) &&
     (iVar2 = FUN_02398c80((short *)(*(int *)(iVar1 + 0x3f0) + 0x10),(short *)(param_1 + 0x1e)),
     iVar2 != 0)) {
    FUN_02398518();
    if (*(short *)(param_1 + 0x2e) == 0) {
      FUN_023990e4(*(ushort *)(param_1 + 0x30) & DAT_023a3120);
      FUN_0239f504(*(ushort *)(iVar1 + 0x382));
      FUN_02399054((undefined2 *)(iVar1 + 0x39a),(undefined2 *)(param_1 + 0x1e));
      uVar3 = FUN_0239b7c4((ushort *)(param_1 + 0x1e));
      *(short *)(iVar1 + 0x3a0) = (short)uVar3;
      FUN_0239b450((uint)*(ushort *)(iVar1 + 0x3a0),0x40);
    }
    if (*(short *)(param_1 + 0x2e) == 0) {
      *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 4) = 0;
      *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 6) = 0;
      func_0x033a9058(0x40);
    }
    else {
      *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 4) = 0xc;
      *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 6) = *(undefined2 *)(param_1 + 0x2e);
    }
    *(undefined2 *)(*(int *)(iVar1 + 0x3f4) + 8) = *(undefined2 *)(iVar1 + 0x382);
    *(short *)(iVar1 + 0x3d8) = 0x53;
    func_0x033a81e8(2,3);
  }
  return;
}



void FUN_023a3124(int param_1)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  ushort *puVar7;
  ushort *local_44 [2];
  short local_3c;
  ushort local_3a;
  undefined2 local_2e;
  ushort *local_28;
  
  iVar4 = *DAT_023a32c0;
  uVar1 = *(ushort *)(param_1 + 6);
  puVar7 = (ushort *)(param_1 + 0x2c);
  if ((4 < uVar1) && (*(short *)(iVar4 + 0x324) == 1)) {
    uVar6 = (uint)*(ushort *)(param_1 + 2);
    if ((uVar6 == 0) || (uVar2 = FUN_0239b1b0(uVar6), uVar2 < 0x30)) {
      iVar4 = FUN_0239f558((undefined2 *)(param_1 + 0x1e),6);
      if (iVar4 != 0) {
        FUN_023a02b8(iVar4);
      }
    }
    else {
      sVar3 = FUN_0239b1b0(uVar6);
      if (sVar3 == 0x40) {
        FUN_0239b450(uVar6,0x30);
        FUN_0239bc80((undefined2 *)(param_1 + 0x1e),1);
      }
      func_0x033adb7c(0,local_44,0x2c);
      local_44[0] = (ushort *)(param_1 + 0x30);
      local_3c = uVar1 - 4;
      FUN_023a1ef4(local_44);
      uVar5 = (uint)*puVar7;
      if ((((((uVar5 & DAT_023a32c4) == 0) && ((int)(uVar5 << 0x1f) < 0)) &&
           ((*(short *)(iVar4 + 0x308) != 0 || (-1 < (int)(uVar5 << 0x1b))))) &&
          ((*(short *)(iVar4 + 0x308) == 0 || ((int)((uint)*puVar7 << 0x1b) < 0)))) &&
         ((-1 < (int)((uint)*(ushort *)(iVar4 + 0x30e) << 0x1d) ||
          ((int)((uint)*puVar7 << 0x1a) < 0)))) {
        FUN_0239b358(uVar6,*puVar7);
        if ((local_3a & 1) == 0) {
          iVar4 = 1;
        }
        else if ((local_3a & 4) == 0) {
          iVar4 = 0x12;
        }
        else {
          FUN_0239b340(uVar6,local_2e);
          iVar4 = 0;
        }
      }
      else {
        iVar4 = 10;
      }
      iVar4 = FUN_0239f95c(uVar6,iVar4,local_28);
      if (iVar4 != 0) {
        FUN_023a02b8(iVar4);
      }
    }
  }
  return;
}



uint FUN_023a32c8(int param_1)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  iVar3 = *DAT_023a33b4;
  uVar5 = (uint)*(ushort *)(param_1 + 2);
  uVar4 = (uint)*(ushort *)(iVar3 + 0x324);
  if (uVar4 == 1) {
    sVar2 = FUN_0239b1b0(uVar5);
    if (sVar2 == 0x40) {
      FUN_0239b450(uVar5,0x30);
      FUN_0239bc80((undefined2 *)(param_1 + 0x1e),*(undefined2 *)(param_1 + 0x2c));
      uVar4 = FUN_023a04bc(uVar5);
    }
    else {
      if (sVar2 == 0x30) {
        uVar4 = FUN_0239fc38((undefined2 *)(param_1 + 0x1e),7);
      }
      else {
        uVar4 = FUN_0239f558((undefined2 *)(param_1 + 0x1e),7);
      }
      if (uVar4 != 0) {
        uVar4 = FUN_023a02b8(uVar4);
      }
    }
  }
  else if ((((uVar4 == 2) || (uVar4 == 3)) &&
           (uVar4 = (uint)*(ushort *)(iVar3 + 800), uVar4 == 0x40)) &&
          (uVar4 = FUN_02398c80((short *)(param_1 + 0x1e),(short *)(iVar3 + 0x39a)), uVar4 != 0)) {
    func_0x033a9058(0x30);
    FUN_02399070();
    bVar1 = FUN_0239bc80((undefined2 *)(param_1 + 0x1e),*(undefined2 *)(param_1 + 0x2c));
    uVar4 = (uint)bVar1;
  }
  return uVar4;
}



void FUN_023a33b8(int param_1)

{
  ushort uVar1;
  short sVar2;
  ushort uVar3;
  longlong lVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  longlong lVar11;
  ushort local_70;
  undefined2 uStack_6e;
  undefined2 local_6c;
  undefined2 uStack_6a;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  ushort *local_54;
  undefined2 local_50;
  undefined2 local_4e;
  short local_4c;
  ushort local_4a;
  ushort local_48;
  ushort local_42;
  undefined2 local_3e;
  int local_38;
  int local_34;
  int local_30;
  uint local_2c;
  
  iVar9 = *DAT_023a3a70;
  *(int *)(iVar9 + 0x548) = *(int *)(iVar9 + 0x548) + 1;
  uVar5 = FUN_0239b67c((ushort *)(param_1 + 0x1e));
  *(short *)(param_1 + 2) = (short)uVar5;
  if (uVar5 == 0xff) {
    return;
  }
  FUN_0239b438(uVar5 & 0xffff,*(undefined2 *)(param_1 + 0x12));
  uVar1 = *(ushort *)(param_1 + 6);
  if (uVar1 < 0xd) {
    return;
  }
  func_0x033adb7c(0,&local_54,0x2c);
  local_54 = (ushort *)(param_1 + 0x38);
  local_4c = uVar1 - 0xc;
  local_4a = 2;
  if (*(short *)(iVar9 + 0x336) == 0) {
    local_4a = 3;
  }
  local_48 = 0x38;
  local_50 = *(undefined2 *)(param_1 + 8);
  local_4e = *(undefined2 *)(param_1 + 0x36);
  FUN_023a1ef4(&local_54);
  if ((local_34 != 0) && ((*(ushort *)(param_1 + 0x16) & 0x8000) != 0)) {
    uVar6 = FUN_023983a0((ushort *)(local_34 + 6));
    uVar7 = FUN_023983a0((ushort *)(local_34 + 7));
    *DAT_023a3a74 = (short)uVar6 + (short)uVar7 * 0x100;
  }
  sVar2 = *(short *)(iVar9 + 0x3d8);
  if ((sVar2 == 0x13) && (*(short *)(*(int *)(iVar9 + 0x3f0) + 0x38) == 1)) {
    if ((local_4a & 9) == 9) {
      FUN_023a28c0(param_1,&local_54);
    }
    goto LAB_023a3a4c;
  }
  if (((local_4a & 8) == 0) ||
     (((local_48 & 1) != 0 && (((local_48 & 1) == 0 || ((local_4a & 1) == 0)))))) goto LAB_023a3a4c;
  if (sVar2 == 0x21) {
    FUN_02398518();
    if ((local_4a & 0x30) == 0x30) {
      if ((local_4a & 4) == 0) {
        *(undefined2 *)(iVar9 + 0x3dc) = 0xc;
        *(undefined2 *)(iVar9 + 0x3de) = 0x12;
      }
      else if (*(ushort *)(param_1 + 0x34) < 0x3e9) {
        *(undefined2 *)(iVar9 + 0x3dc) = 0;
        if (((local_48 & 2) != 0) && ((local_4a & 2) == 0)) {
          FUN_023995a4((uint)local_42,0);
        }
        FUN_0239b340(uVar5,local_3e);
        uVar6 = local_2c;
        if (*(short *)(iVar9 + 0x324) == 2) {
          if (local_2c == 0) {
            FUN_02399ecc(DAT_023a3a7c,1);
            *DAT_023a3a78 = 0;
          }
          else {
            uVar7 = FUN_023983a0((ushort *)(local_2c + 6));
            uVar6 = FUN_023983a0((ushort *)(uVar6 + 7));
            FUN_02399ecc(uVar7 + uVar6 * 0x100 & 0xffff,1);
            uVar6 = FUN_023983a0((ushort *)(local_2c + 8));
            uVar7 = FUN_023983a0((ushort *)(local_2c + 9));
            *DAT_023a3a78 = (short)uVar6 + (short)uVar7 * 0x100;
          }
        }
        uVar6 = FUN_023983a0((ushort *)(local_30 + 3));
        FUN_023999bc(uVar6);
        uVar6 = FUN_023983a0((ushort *)(local_30 + 2));
        *(short *)(iVar9 + 0x38e) = (short)uVar6;
        FUN_02399a08((uint)*(ushort *)(param_1 + 0x34));
        *(undefined2 *)(iVar9 + 0x32a) = 1;
        *(undefined2 *)(iVar9 + 0x332) = 1;
        if (*(short *)(iVar9 + 0x324) == 2) {
          *DAT_023a3a80 = 3;
        }
        *DAT_023a3a84 = *DAT_023a3a84 | 1;
      }
      else {
        *(undefined2 *)(iVar9 + 0x3dc) = 0xc;
        *(undefined2 *)(iVar9 + 0x3de) = 1;
      }
    }
    else {
      *(undefined2 *)(iVar9 + 0x3dc) = 0xc;
      *(undefined2 *)(iVar9 + 0x3de) = 10;
    }
    FUN_02399054((undefined2 *)(*(int *)(iVar9 + 0x3f4) + 8),(undefined2 *)(param_1 + 0x1e));
    *(short *)(iVar9 + 0x3d8) = 0x25;
    func_0x033a81e8(2,1);
  }
  uVar6 = local_2c;
  if (*(short *)(iVar9 + 0x324) == 2) {
    if (local_2c != 0) {
      uVar7 = FUN_023983a0((ushort *)(local_2c + 6));
      uVar6 = FUN_023983a0((ushort *)(uVar6 + 7));
      FUN_02399ecc(uVar7 + uVar6 * 0x100 & 0xffff,0);
      uVar6 = FUN_023983a0((ushort *)(local_2c + 8));
      uVar7 = FUN_023983a0((ushort *)(local_2c + 9));
      *DAT_023a3a78 = (short)uVar6 + (short)uVar7 * 0x100;
      uVar6 = FUN_023983a0((ushort *)(local_2c + 1));
      *(short *)(iVar9 + 0x3b8) = (short)uVar6 + -8;
      uVar6 = (uint)*(ushort *)(iVar9 + 0x3b8);
      if (uVar6 != 0) {
        if ((local_2c & 1) == 0) {
          func_0x033adb60(local_2c + 10,*(undefined4 *)(iVar9 + 0x3b4),uVar6 + 1);
          *(undefined2 *)(iVar9 + 0x3ba) = 0;
        }
        else {
          func_0x033adb60(local_2c + 9,*(undefined4 *)(iVar9 + 0x3b4),uVar6 + 2);
          *(undefined2 *)(iVar9 + 0x3ba) = 1;
        }
      }
    }
LAB_023a3788:
    *(undefined2 *)(iVar9 + 0x398) = 0;
    FUN_0239b2ec(uVar5);
    uVar1 = *(ushort *)(iVar9 + 0x386);
    uVar5 = (uint)uVar1 * 0x400;
    lVar11 = func_0x033b695c(*(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x30),uVar5,0
                            );
    lVar4 = (ulonglong)uVar1 * 0x400 * (lVar11 + 1U & 0xffffffff);
    iVar8 = (int)(lVar11 + 1U >> 0x20) * uVar5 + (int)((ulonglong)lVar4 >> 0x20);
    uStack_6a = (undefined2)((uint)iVar8 >> 0x10);
    *DAT_023a3a88 = uStack_6a;
    local_6c = (undefined2)iVar8;
    *DAT_023a3a8c = local_6c;
    uStack_6e = (undefined2)((ulonglong)lVar4 >> 0x10);
    *DAT_023a3a90 = uStack_6e;
    local_70 = (ushort)lVar4;
    *DAT_023a3a94 = local_70 | 1;
    if ((*(short *)(iVar9 + 0x324) == 2) && (*(short *)(iVar9 + 0x332) != 0)) {
      uVar6 = (uint)lVar4 + (uint)uVar1 * -0x400;
      iVar8 = iVar8 - (uint)((uint)lVar4 < uVar5);
      func_0x033ad8a0();
      uVar1 = *DAT_023a3a98;
      local_68 = CONCAT22(*DAT_023a3a9c,uVar1);
      local_64 = (uint)*DAT_023a3aa0;
      uVar3 = *DAT_023a3a98;
      local_60 = CONCAT22(*DAT_023a3a9c,uVar3);
      local_5c = (uint)*DAT_023a3aa0;
      func_0x033ad8b4();
      if (uVar1 < uVar3) {
        uVar5 = local_68 - uVar6 >> 10 | (local_64 - (iVar8 + (uint)(local_68 < uVar6))) * 0x400000;
      }
      else {
        uVar5 = local_60 - uVar6 >> 10 | (local_5c - (iVar8 + (uint)(local_60 < uVar6))) * 0x400000;
      }
      uVar6 = (uint)*(ushort *)(iVar9 + 0x310);
      bVar10 = uVar5 < uVar6;
      if (bVar10) {
        uVar5 = uVar6 - uVar5;
      }
      if (bVar10) {
        *DAT_023a3aa8 = (short)uVar5;
      }
      else {
        *DAT_023a3aa8 = 0;
      }
    }
    if (((*(short *)(iVar9 + 800) == 0x40) && (local_30 != 0)) && (*(short *)(iVar9 + 0x326) == 1))
    {
      uVar5 = FUN_023983a0((ushort *)(local_30 + 2));
      if (*(ushort *)(iVar9 + 0x38e) != uVar5) {
        *(short *)(iVar9 + 0x38e) = (short)uVar5;
      }
      *(undefined2 *)(iVar9 + 0x3a6) = 0;
      if ((uVar5 == 0) && (uVar5 = FUN_023983a0((ushort *)(local_30 + 4)), (uVar5 & 1) != 0)) {
        *(ushort *)(iVar9 + 0x3a6) = *(ushort *)(iVar9 + 0x3a6) | 1;
      }
      uVar5 = FUN_023983a0((ushort *)(local_30 + 4));
      uVar5 = uVar5 & 0xfe;
      uVar6 = FUN_023983a0((ushort *)(local_30 + 1));
      uVar7 = (uint)*(ushort *)(iVar9 + 0x382);
      if (((uVar5 * 8 <= uVar7) && (uVar7 <= (uVar5 + uVar6 + -3) * 8)) &&
         (uVar7 = uVar7 + uVar5 * -8, uVar5 = FUN_023983a0((ushort *)(local_30 + 5 + (uVar7 >> 3))),
         (1 << (uVar7 & 7) & uVar5) != 0)) {
        *(ushort *)(iVar9 + 0x3a6) = *(ushort *)(iVar9 + 0x3a6) | 2;
        FUN_023a01a8();
      }
      if (((*(short *)(iVar9 + 0x170) == 0) && (*(short *)(iVar9 + 0x17c) == 0)) &&
         (*(short *)(iVar9 + 0x3a6) == 0)) {
        FUN_02399428(1);
      }
    }
  }
  else if (*(short *)(iVar9 + 0x324) == 3) goto LAB_023a3788;
  if ((int)((uint)*(ushort *)(iVar9 + 0x30e) << 0x19) < 0) {
    FUN_0239ba70(param_1);
  }
LAB_023a3a4c:
  if (local_38 != 0) {
    FUN_023a427c(local_42,param_1,local_38);
  }
  return;
}



undefined4 FUN_023a3aac(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar2 = *DAT_023a3b80;
  if (*(short *)(iVar2 + 800) == 0x40) {
    iVar4 = FUN_02398c80((short *)(param_1 + 0x1e),(short *)(iVar2 + 0x37c));
    if ((iVar4 == 0) ||
       (iVar2 = FUN_02398c80((short *)(param_1 + 0x24),(short *)(iVar2 + 0x39a)), iVar2 == 0)) {
      uVar3 = 1;
    }
    else {
      *(short *)(param_1 + 6) = *(short *)(param_1 + 0x10) + -0x1c;
      *(short *)(param_1 + -4) = (short)DAT_023a3b84;
      *(undefined2 *)(param_1 + -2) = 0x18;
      piVar1 = DAT_023a3b80;
      *(ushort *)(param_1 + 8) =
           *(ushort *)(param_1 + 8) |
           *(ushort *)(*DAT_023a3b80 + 0x4ba) | (ushort)((int)(*DAT_023a3b8c & 0x8000) >> 4) |
           (ushort)((int)(*DAT_023a3b88 & 0x8000) >> 3);
      func_0x033a8a4c(*piVar1 + 0x15c);
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}



void FUN_023a3b90(int param_1)

{
  uint uVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  ushort *puVar8;
  
  iVar7 = *DAT_023a3d54;
  iVar4 = *(int *)(iVar7 + 0x490);
  if (((*(short *)(iVar7 + 0x43c) != 0) &&
      (iVar5 = FUN_02398c80((short *)(param_1 + 0x18),(short *)(iVar7 + 0x37c)), iVar5 != 0)) &&
     ((int)(*(ushort *)(param_1 + 0x10) - 0x18) <= (int)(*(ushort *)(iVar4 + 0x16) - 8))) {
    uVar6 = FUN_0239b7c4((ushort *)(param_1 + 0x1e));
    if ((uVar6 == 0xff) || ((uVar6 != 0 && (sVar2 = FUN_0239b1b0(uVar6), sVar2 != 0x40)))) {
      iVar4 = FUN_0239f558((undefined2 *)(param_1 + 0x1e),7);
      if (iVar4 != 0) {
        FUN_023a02b8(iVar4);
      }
    }
    else if (uVar6 != 0) {
      sVar2 = FUN_0239b1b0(uVar6);
      if (sVar2 == 0x40) {
        FUN_0239b3d4(uVar6 & 0xffff,((uint)*(ushort *)(param_1 + 0x14) << 0x13) >> 0x1f);
        FUN_0239b2ec(uVar6);
        uVar3 = FUN_0239b0d8(uVar6);
        uVar1 = 1 << (uVar3 & 0xff);
        uVar6 = uVar1 & 0xffff;
        if (((uVar6 & *(ushort *)(iVar7 + 0x49a)) == 0) &&
           ((uVar6 & *(ushort *)(iVar7 + 0x498)) != 0)) {
          uVar3 = (ushort)uVar1;
          *(ushort *)(iVar7 + 0x49a) = *(ushort *)(iVar7 + 0x49a) | uVar3;
          *(ushort *)(iVar4 + 0x10) = *(ushort *)(iVar4 + 0x10) & ~uVar3;
          puVar8 = (ushort *)(iVar4 + 0x1a);
          while (uVar6 = (uVar6 << 0xf) >> 0x10, uVar6 != 1) {
            if ((uVar6 & *(ushort *)(iVar7 + 0x498)) != 0) {
              puVar8 = (ushort *)((int)puVar8 + (uint)*(ushort *)(iVar4 + 0x16));
            }
          }
          *puVar8 = *(short *)(param_1 + 0x10) - 0x18;
          FUN_023983c0((ushort *)((int)puVar8 + 3),*(ushort *)(param_1 + 0x12) & 0xff);
          FUN_023983c0(puVar8 + 1,*(ushort *)(param_1 + 0xe) & 0xff);
          if (*puVar8 != 0) {
            func_0x033adb60(param_1 + 0x2c,puVar8 + 4,*puVar8 + 1);
          }
        }
      }
      else {
        iVar4 = FUN_0239f558((undefined2 *)(param_1 + 0x1e),7);
        if (iVar4 != 0) {
          FUN_023a02b8(iVar4);
        }
      }
    }
  }
  return;
}



undefined4 FUN_023a3d58(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  short *psVar5;
  
  iVar3 = *DAT_023a3ef8;
  psVar5 = (short *)(iVar3 + DAT_023a3efc);
  if (*(short *)(iVar3 + 800) == 0x40) {
    if (*psVar5 == *(short *)(param_1 + 0x2a)) {
      *(int *)(iVar3 + 0x554) = *(int *)(iVar3 + 0x554) + 1;
      uVar1 = 1;
    }
    else {
      *psVar5 = *(short *)(param_1 + 0x2a);
      iVar2 = FUN_02398c80((short *)(param_1 + 0x1e),(short *)(iVar3 + 0x37c));
      if ((iVar2 == 0) ||
         (iVar2 = FUN_02398c80((short *)(param_1 + 0x24),(short *)(iVar3 + 0x39a)), iVar2 == 0)) {
        uVar1 = 1;
      }
      else {
        if ((1 << (*(ushort *)(iVar3 + 0x382) & 0xff) & 0xffffU & (uint)*(ushort *)(param_1 + 0x2e))
            == 0) {
          psVar5[3] = 0;
        }
        else {
          psVar5[3] = 0x2000;
        }
        if (((*DAT_023a3f00 & 0x8000) != 0) &&
           (*(short *)((*DAT_023a3f00 & DAT_023a3f04) * 2 + 0x4804004) != 0)) {
          psVar5[3] = psVar5[3] | 0x4000;
        }
        FUN_0239b2ec((uint)*(ushort *)(iVar3 + 0x3a0));
        *(short *)(param_1 + 6) = *(short *)(param_1 + 0x10) + -0x1c;
        *(short *)(param_1 + -4) = (short)DAT_023a3f08;
        *(short *)(param_1 + -2) = (short)(*(ushort *)(param_1 + 6) + 0x31 >> 1);
        iVar3 = 0;
        for (uVar4 = (uint)*(ushort *)(param_1 + 0x2e); uVar4 != 0; uVar4 = (uVar4 << 0xf) >> 0x10)
        {
          if ((uVar4 & 1) != 0) {
            iVar3 = iVar3 + 1;
          }
        }
        *(ushort *)(param_1 + 8) =
             *(ushort *)(param_1 + 8) |
             psVar5[3] | (ushort)((int)(*DAT_023a3f00 & 0x8000) >> 4) |
             (ushort)((int)(*DAT_023a3f0c & 0x8000) >> 3);
        *(short *)(param_1 + 10) =
             *(short *)(param_1 + 0xc) +
             (short)(iVar3 * (*(ushort *)(param_1 + 0x2c) + 10) + 0xfc >> 4);
        func_0x033a8a4c(*DAT_023a3ef8 + 0x15c);
        uVar1 = 0;
      }
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



void FUN_023a3f10(void)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  uint unaff_r5;
  int iVar5;
  int iVar6;
  
  iVar4 = *DAT_023a41ec;
  iVar5 = iVar4 + DAT_023a41f0;
  iVar6 = *(int *)(iVar4 + 0x198);
  if (iVar6 != -1) {
    if (*(short *)(iVar4 + 800) == 0x40) {
      if ((int)((uint)*(ushort *)(iVar6 + 0x24) << 0x17) < 0) {
        if ((*(ushort *)(iVar6 + 0x34) & 1) == 0) {
          *(int *)(iVar5 + 0x28) = *(int *)(iVar5 + 0x28) + 1;
        }
        else {
          *(int *)(iVar5 + 0x2c) = *(int *)(iVar5 + 0x2c) + 1;
        }
      }
      else if ((*(ushort *)(iVar6 + 0x28) & 1) == 0) {
        *(int *)(iVar5 + 0x28) = *(int *)(iVar5 + 0x28) + 1;
      }
      else {
        *(int *)(iVar5 + 0x2c) = *(int *)(iVar5 + 0x2c) + 1;
      }
      iVar3 = func_0x033b6b64(*(ushort *)(iVar6 + 0x18) & 0xf0,0x10);
      *(int *)(iVar5 + 0x24) = *(int *)(iVar5 + 0x24) + iVar3 + -1;
      bVar1 = true;
      sVar2 = *(short *)(iVar4 + 0x324);
      if (sVar2 == 1) {
        if ((*(ushort *)(iVar6 + 0x24) & 1) == 0) {
          unaff_r5 = FUN_0239b7c4((ushort *)(iVar6 + 0x2e));
          if ((unaff_r5 == 0xff) || (sVar2 = FUN_0239b1b0(unaff_r5), sVar2 != 0x40)) {
            sVar2 = FUN_0239b1b0(unaff_r5);
            if (sVar2 == 0x30) {
              iVar5 = FUN_0239fc38((undefined2 *)(iVar6 + 0x2e),7);
            }
            else {
              iVar5 = FUN_0239f558((undefined2 *)(iVar6 + 0x2e),7);
            }
            if (iVar5 != 0) {
              FUN_023a02b8(iVar5);
            }
          }
          else {
            FUN_0239b3d4(unaff_r5 & 0xffff,((uint)*(ushort *)(iVar6 + 0x24) << 0x13) >> 0x1f);
            sVar2 = FUN_0239b11c(unaff_r5);
            if (*(short *)(iVar6 + 0x3a) == sVar2) {
              *(int *)(iVar5 + 0x3c) = *(int *)(iVar5 + 0x3c) + 1;
            }
            else {
              FUN_02399054((undefined2 *)(iVar6 + 0x28),(undefined2 *)(iVar6 + 0x34));
              bVar1 = false;
            }
          }
        }
      }
      else if (((sVar2 == 2) || (sVar2 == 3)) && ((*(ushort *)(iVar6 + 0x24) & 1) == 0)) {
        if ((*(short *)(iVar4 + 0x326) != 0) && ((*(ushort *)(iVar6 + 0x24) & 0x2000) == 0)) {
          if ((*(ushort *)(iVar6 + 0x28) & 1) == 0) {
            if (sVar2 != 3) {
              *(ushort *)(iVar4 + 0x3a6) = *(ushort *)(iVar4 + 0x3a6) & 0xfffd;
            }
          }
          else {
            *(ushort *)(iVar4 + 0x3a6) = *(ushort *)(iVar4 + 0x3a6) & 0xfffe;
          }
          if (((*(short *)(iVar4 + 0x3a6) == 0) && (*(short *)(iVar4 + 0x170) == 0)) &&
             (*(short *)(iVar4 + 0x17c) == 0)) {
            FUN_02399428(1);
          }
        }
        unaff_r5 = (uint)*(ushort *)(iVar4 + 0x3a0);
        sVar2 = FUN_0239b11c(unaff_r5);
        if (*(short *)(iVar6 + 0x3a) == sVar2) {
          *(int *)(iVar5 + 0x3c) = *(int *)(iVar5 + 0x3c) + 1;
        }
        else {
          FUN_02399054((undefined2 *)(iVar6 + 0x2e),(undefined2 *)(iVar6 + 0x34));
          bVar1 = false;
        }
      }
      if (bVar1) {
        func_0x033a85a8(iVar4 + 0x198,iVar6);
      }
      else {
        *(short *)(iVar6 + 0x12) = (short)unaff_r5;
        FUN_0239b438(unaff_r5 & 0xffff,*(ushort *)(iVar6 + 0x22) & 0xff);
        FUN_0239b328(unaff_r5,*(undefined2 *)(iVar6 + 0x3a));
        FUN_0239b2ec(unaff_r5);
        *(short *)(iVar6 + 0x16) = *(short *)(iVar6 + 0x20) + -0x18;
        *(undefined2 *)(iVar6 + 0xc) = 0x180;
        *(short *)(iVar6 + 0xe) = (short)(*(ushort *)(iVar6 + 0x16) + 0x2d >> 1);
        func_0x033a8a4c(iVar4 + 0x198,iVar6);
      }
      if (*(short *)(iVar4 + 0x1a0) != 0) {
        func_0x033a81e8(2,6);
      }
    }
    else {
      func_0x033a85a8(iVar4 + 0x198,iVar6);
    }
  }
  return;
}



void FUN_023a427c(undefined2 param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  short *psVar8;
  
  psVar8 = (short *)(*DAT_023a43d4 + 0x210);
  uVar1 = FUN_023983a0((ushort *)(param_3 + 1));
  if (uVar1 < 0x21) {
    uVar1 = 4;
    uVar4 = 0x400;
    uVar3 = 4;
    for (uVar7 = 0; uVar7 < 4; uVar7 = uVar7 + 1) {
      uVar5 = uVar7;
      if (*psVar8 != 0) {
        iVar2 = FUN_02398c80(psVar8 + 3,(short *)(param_2 + 0x24));
        if (iVar2 != 0) goto LAB_023a4328;
        uVar5 = uVar3;
        if ((ushort)psVar8[0x18] < uVar4) {
          uVar1 = uVar7;
          uVar4 = psVar8[0x18];
        }
      }
      psVar8 = psVar8 + 0x19;
      uVar3 = uVar5;
    }
    uVar7 = uVar3;
    if ((uVar3 != 4) || (uVar7 = uVar1, uVar1 != 4)) {
LAB_023a4328:
      iVar2 = *DAT_023a43d4;
      iVar6 = iVar2 + 0x210 + uVar7 * 0x32;
      func_0x033adb48(0,iVar6);
      *(undefined2 *)(iVar6 + 0x30) = 0x400;
      *(ushort *)(iVar2 + 0x210 + uVar7 * 0x32) = *(ushort *)(param_2 + 0x12) & 0xff;
      *(undefined2 *)(iVar6 + 2) = param_1;
      FUN_02399054((undefined2 *)(iVar6 + 6),(undefined2 *)(param_2 + 0x24));
      uVar1 = FUN_023983a0((ushort *)(param_3 + 1));
      *(short *)(iVar6 + 0xc) = (short)uVar1;
      for (uVar1 = 0; uVar1 < *(ushort *)(iVar6 + 0xc); uVar1 = uVar1 + 1) {
        uVar3 = FUN_023983a0((ushort *)(param_3 + 2 + uVar1));
        FUN_023983c0((ushort *)(iVar6 + 0xe + uVar1),uVar3);
      }
      *(undefined2 *)(iVar6 + 0x2e) = *(undefined2 *)(param_2 + 0x34);
      *(undefined2 *)(iVar6 + 4) = *(undefined2 *)(param_2 + 0x36);
    }
  }
  return;
}



undefined4 FUN_023a43d8(void)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint local_8 [2];
  
  func_0x033b3ddc(*(undefined4 *)(*DAT_023a44c4 + 0x2e8));
  FUN_023a457c();
  local_8[0] = 0;
  FUN_023a522c(0x2c,2,(int)local_8);
  func_0x033b3d70(*(undefined4 *)(*DAT_023a44c4 + 0x2e8));
  if ((local_8[0] < 0xa4) || (DAT_023a44c8 < local_8[0])) {
    uVar2 = 0;
  }
  else {
    local_8[0] = local_8[0] + 2;
    uVar2 = func_0x033a8500(*DAT_023a44c4 + 0x15c);
    piVar1 = DAT_023a44c4;
    *(undefined4 *)(*DAT_023a44c4 + 0x2ec) = uVar2;
    iVar4 = *piVar1;
    iVar3 = *(int *)(iVar4 + 0x2ec);
    if (iVar3 == 0) {
      uVar2 = 0;
    }
    else {
      *(int *)(iVar4 + 0x2ec) = iVar3 + 0xc;
      func_0x033b3ddc(*(undefined4 *)(*piVar1 + 0x2e8));
      FUN_023a457c();
      FUN_023a522c(0x2a,local_8[0],*(int *)(*DAT_023a44c4 + 0x2ec));
      func_0x033b3d70(*(undefined4 *)(*DAT_023a44c4 + 0x2e8));
      uVar2 = 1;
    }
  }
  return uVar2;
}



void FUN_023a44cc(undefined4 param_1,int param_2,int param_3)

{
  func_0x033b3ddc(*(undefined4 *)(*DAT_023a4518 + 0x2e8));
  FUN_023a457c();
  FUN_023a522c(param_1,param_2,param_3);
  func_0x033b3d70(*(undefined4 *)(*DAT_023a4518 + 0x2e8));
  return;
}



void FUN_023a451c(int param_1,int param_2,ushort *param_3)

{
  uint uVar1;
  ushort *puVar2;
  
  if (*(int *)(*DAT_023a4578 + 0x2ec) != 0) {
    puVar2 = (ushort *)(*(int *)(*DAT_023a4578 + 0x2ec) + param_1 + -0x2a);
    for (; param_2 != 0; param_2 = param_2 + -1) {
      uVar1 = FUN_023983a0(puVar2);
      puVar2 = (ushort *)((int)puVar2 + 1);
      FUN_023983c0(param_3,uVar1);
      param_3 = (ushort *)((int)param_3 + 1);
    }
  }
  return;
}



void FUN_023a457c(void)

{
  uint local_10 [2];
  
  do {
    while (FUN_023a534c((undefined *)local_10), (local_10[0] & 0x20) != 0) {
      FUN_023a4b74();
    }
  } while ((local_10[0] & 1) != 0);
  return;
}



undefined4 FUN_023a45bc(uint *param_1)

{
  ushort uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ushort *puVar6;
  
  uVar5 = (uint)*(ushort *)(*(int *)(*DAT_023a4660 + 0x2ec) + 2);
  if ((uVar5 < 0xa4) || (DAT_023a4664 < uVar5)) {
    uVar2 = 2;
  }
  else {
    puVar6 = (ushort *)(*(int *)(*DAT_023a4660 + 0x2ec) + 2);
    uVar4 = 0;
    for (; uVar5 != 0; uVar5 = uVar5 - 1) {
      uVar3 = FUN_023983a0(puVar6);
      puVar6 = (ushort *)((int)puVar6 + 1);
      uVar4 = FUN_0239829c(uVar3 & 0xff,uVar4 & 0xffff);
    }
    uVar1 = **(ushort **)(*DAT_023a4660 + 0x2ec);
    if (param_1 != (uint *)0x0) {
      *param_1 = (uint)uVar1 | uVar4 << 0x10;
    }
    if (uVar4 == uVar1) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}



undefined4 FUN_023a4668(void)

{
  undefined4 uVar1;
  ushort local_8 [4];
  
  FUN_023a534c((undefined *)local_8);
  if ((local_8[0] & 1) == 0) {
    if ((local_8[0] & 2) == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



bool FUN_023a46a0(void)

{
  ushort local_8 [4];
  
  FUN_023a534c((undefined *)local_8);
  return (local_8[0] & 1) == 0;
}



void FUN_023a46cc(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = func_0x033ad8a0();
  iVar3 = func_0x033b3c80(1);
  if (iVar3 == 0) {
    func_0x033ad8b4(uVar2);
    func_0x033b3c9c(*(uint *)(param_1 + 4) & 0xffff,4);
  }
  else {
    func_0x033b3c68(1);
    func_0x033ad8b4(uVar2);
    switch(*(undefined4 *)(param_1 + 4)) {
    case 0x20:
      FUN_023a5400();
      break;
    case 0x21:
      FUN_023a53c0();
      break;
    case 0x22:
      FUN_023a534c(*(undefined **)(param_1 + 0x10));
      break;
    case 0x23:
      bVar1 = FUN_023a46a0();
      if (!bVar1) {
        func_0x033b3c9c(*(uint *)(param_1 + 4) & 0xffff,3);
        func_0x033b3c24(1);
        return;
      }
      FUN_023a522c(*(undefined4 *)(param_1 + 8),*(int *)(param_1 + 0xc),*(int *)(param_1 + 0x10));
      break;
    case 0x24:
      bVar1 = FUN_023a46a0();
      if (!bVar1) {
        func_0x033b3c9c(*(uint *)(param_1 + 4) & 0xffff,3);
        func_0x033b3c24(1);
        return;
      }
      FUN_023a50f0(*(undefined4 *)(param_1 + 8),*(int *)(param_1 + 0xc),*(int *)(param_1 + 0x10));
      break;
    case 0x25:
      iVar3 = FUN_023a4668();
      if (iVar3 == 0) {
        func_0x033b3c9c(*(uint *)(param_1 + 4) & 0xffff,3);
        func_0x033b3c24(1);
        return;
      }
      FUN_023a4fc4(*(uint *)(param_1 + 8),*(uint *)(param_1 + 0xc) & 0xffff,*(int *)(param_1 + 0x10)
                  );
      break;
    case 0x26:
      iVar3 = FUN_023a4668();
      if (iVar3 == 0) {
        func_0x033b3c9c(*(uint *)(param_1 + 4) & 0xffff,3);
        func_0x033b3c24(1);
        return;
      }
      FUN_023a4e98(*(uint *)(param_1 + 8),*(uint *)(param_1 + 0xc) & 0xffff,*(int *)(param_1 + 0x10)
                  );
      break;
    case 0x27:
      iVar3 = FUN_023a4668();
      if (iVar3 == 0) {
        func_0x033b3c9c(*(uint *)(param_1 + 4) & 0xffff,3);
        func_0x033b3c24(1);
        return;
      }
      FUN_023a4dd4(*(undefined4 *)(param_1 + 8));
      break;
    case 0x28:
      iVar3 = FUN_023a4668();
      if (iVar3 == 0) {
        func_0x033b3c9c(*(uint *)(param_1 + 4) & 0xffff,3);
        func_0x033b3c24(1);
        return;
      }
      FUN_023a4d10(*(undefined4 *)(param_1 + 8));
      break;
    case 0x29:
      FUN_023a4cd0();
      break;
    case 0x2a:
      FUN_023a4c90();
      break;
    case 0x2b:
      iVar3 = FUN_023a4668();
      if (iVar3 == 0) {
        func_0x033b3c9c(*(uint *)(param_1 + 4) & 0xffff,3);
        func_0x033b3c24(1);
        return;
      }
      FUN_023a4c50();
      break;
    case 0x2c:
      FUN_023a4bb4(*(undefined **)(param_1 + 0x10));
      break;
    case 0x2d:
      FUN_023a4b74();
      break;
    default:
      func_0x033b3c24(1);
      func_0x033b3c9c(*(uint *)(param_1 + 4) & 0xffff,1);
      return;
    }
    func_0x033b3c9c(*(uint *)(param_1 + 4) & 0xffff,0);
    func_0x033b3c24(1);
  }
  return;
}



void FUN_023a49a8(uint param_1,undefined4 param_2,uint param_3,uint param_4)

{
  uint uVar1;
  ushort *puVar2;
  uint uVar3;
  int iVar4;
  uint in_r12;
  
  puVar2 = DAT_023a4b48;
  if ((param_1 & 0x2000000) != 0) {
    iVar4 = 0;
    do {
      puVar2[iVar4] = 0;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x10);
  }
  puVar2 = DAT_023a4b48;
  DAT_023a4b48[(param_1 & 0xf0000) >> 0x10] = (ushort)param_1;
  if ((param_1 & 0x1000000) == 0) {
    return;
  }
  uVar3 = (uint)*puVar2;
  uVar1 = ((uVar3 & 0xff00) << 8) >> 0x10;
  switch(uVar1) {
  case 0x22:
    goto LAB_023a4a40;
  case 0x23:
    goto LAB_023a4a7c;
  case 0x24:
LAB_023a4a7c:
    in_r12 = CONCAT22(puVar2[4],puVar2[5]);
    if ((in_r12 < 0x2000000) || (0x23fffff < in_r12)) {
      func_0x033b3c9c(uVar1,2);
      return;
    }
    param_4 = (uint)puVar2[1] | (uVar3 & 0xff) << 0x10;
    param_3 = CONCAT22(puVar2[2],puVar2[3]);
    break;
  case 0x25:
    goto LAB_023a4ac4;
  case 0x26:
LAB_023a4ac4:
    in_r12 = CONCAT22(puVar2[3],puVar2[4]);
    if ((in_r12 < 0x2000000) || (0x23fffff < in_r12)) {
      func_0x033b3c9c(uVar1,2);
      return;
    }
    param_4 = (uint)puVar2[1] | (uVar3 & 0xff) << 0x10;
    param_3 = (uint)puVar2[2];
    break;
  case 0x27:
    goto LAB_023a4b04;
  case 0x28:
LAB_023a4b04:
    param_4 = (uint)puVar2[1] | (uVar3 & 0xff) << 0x10;
    break;
  case 0x29:
    break;
  case 0x2a:
    break;
  case 0x2b:
    break;
  case 0x2c:
LAB_023a4a40:
    in_r12 = uVar3 << 0x18 | (uint)puVar2[1] << 8 | (uint)(puVar2[2] >> 8);
    if ((in_r12 < 0x2000000) || (0x23fffff < in_r12)) {
      func_0x033b3c9c(uVar1,2);
      return;
    }
  }
  iVar4 = func_0x033b3b50(1,uVar1,3,param_4,param_3,in_r12);
  if (iVar4 == 0) {
    func_0x033b3c9c(uVar1,4);
  }
  return;
}



void FUN_023a4b74(void)

{
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4bac & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a4bac = 0x8100;
  *(undefined2 *)PTR_SPI_bus_Data_023a4bb0 = 0xff;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4bac & 0x80) != 0);
  return;
}



void FUN_023a4bb4(undefined *param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4c48 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a4c48 = 0x8900;
  *(undefined2 *)PTR_SPI_bus_Data_023a4c4c = 0x9f;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4c48 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Data_023a4c4c = 0;
  puVar2 = PTR_SPI_bus_Data_023a4c4c;
  puVar1 = PTR_SPI_bus_Control_023a4c48;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4c48 & 0x80) != 0);
  *param_1 = (char)*(undefined2 *)PTR_SPI_bus_Data_023a4c4c;
  *(undefined2 *)puVar1 = 0x8100;
  *(undefined2 *)puVar2 = 0;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4c48 & 0x80) != 0);
  param_1[1] = (char)*(undefined2 *)PTR_SPI_bus_Data_023a4c4c;
  return;
}



void FUN_023a4c50(void)

{
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4c88 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a4c88 = 0x8100;
  *(undefined2 *)PTR_SPI_bus_Data_023a4c8c = 199;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4c88 & 0x80) != 0);
  return;
}



void FUN_023a4c90(void)

{
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4cc8 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a4cc8 = 0x8100;
  *(undefined2 *)PTR_SPI_bus_Data_023a4ccc = 0xab;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4cc8 & 0x80) != 0);
  return;
}



void FUN_023a4cd0(void)

{
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4d08 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a4d08 = 0x8100;
  *(undefined2 *)PTR_SPI_bus_Data_023a4d0c = 0xb9;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4d08 & 0x80) != 0);
  return;
}



void FUN_023a4d10(undefined4 param_1)

{
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4dcc & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a4dcc = 0x8900;
  *(undefined2 *)PTR_SPI_bus_Data_023a4dd0 = 0xd8;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4dcc & 0x80) != 0);
  *(ushort *)PTR_SPI_bus_Data_023a4dd0 = (ushort)((uint)param_1 >> 0x10) & 0xff;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4dcc & 0x80) != 0);
  *(ushort *)PTR_SPI_bus_Data_023a4dd0 = (ushort)((uint)param_1 >> 8) & 0xff;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4dcc & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a4dcc = 0x8100;
  *(ushort *)PTR_SPI_bus_Data_023a4dd0 = (ushort)param_1 & 0xff;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4dcc & 0x80) != 0);
  return;
}



void FUN_023a4dd4(undefined4 param_1)

{
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4e90 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a4e90 = 0x8900;
  *(undefined2 *)PTR_SPI_bus_Data_023a4e94 = 0xdb;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4e90 & 0x80) != 0);
  *(ushort *)PTR_SPI_bus_Data_023a4e94 = (ushort)((uint)param_1 >> 0x10) & 0xff;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4e90 & 0x80) != 0);
  *(ushort *)PTR_SPI_bus_Data_023a4e94 = (ushort)((uint)param_1 >> 8) & 0xff;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4e90 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a4e90 = 0x8100;
  *(ushort *)PTR_SPI_bus_Data_023a4e94 = (ushort)param_1 & 0xff;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a4e90 & 0x80) != 0);
  return;
}



void FUN_023a4e98(uint param_1,uint param_2,int param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  int iVar5;
  ushort local_10 [4];
  
  if (param_2 != 0) {
    if (param_1 >> 8 < (param_1 + param_2) - 1 >> 8) {
      param_2 = 0x100 - (param_1 & 0xff) & 0xffff;
    }
    local_10[0] = (ushort)((param_1 & 0xff00ff) >> 0x10);
    local_10[1] = (ushort)(param_1 >> 8) & 0xff;
    local_10[2] = (short)(param_1 & 0xff00ff);
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_023a4fbc & 0x80) != 0);
    *(undefined2 *)PTR_SPI_bus_Control_023a4fbc = 0x8900;
    puVar3 = PTR_SPI_bus_Data_023a4fc0;
    *(undefined2 *)PTR_SPI_bus_Data_023a4fc0 = 2;
    puVar1 = PTR_SPI_bus_Control_023a4fbc;
    iVar5 = 0;
    do {
      do {
      } while ((*(ushort *)puVar1 & 0x80) != 0);
      *(ushort *)puVar3 = local_10[iVar5] & 0xff;
      puVar4 = PTR_SPI_bus_Data_023a4fc0;
      puVar2 = PTR_SPI_bus_Control_023a4fbc;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 3);
    for (iVar5 = 0; iVar5 < (int)(param_2 - 1); iVar5 = iVar5 + 1) {
      do {
      } while ((*(ushort *)puVar2 & 0x80) != 0);
      *(ushort *)puVar4 = (ushort)*(byte *)(param_3 + iVar5);
    }
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_023a4fbc & 0x80) != 0);
    *(undefined2 *)PTR_SPI_bus_Control_023a4fbc = 0x8100;
    *(ushort *)PTR_SPI_bus_Data_023a4fc0 = (ushort)*(byte *)(param_3 + iVar5);
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_023a4fbc & 0x80) != 0);
  }
  return;
}



void FUN_023a4fc4(uint param_1,uint param_2,int param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  int iVar5;
  ushort local_10 [4];
  
  if (param_2 != 0) {
    if (param_1 >> 8 < (param_1 + param_2) - 1 >> 8) {
      param_2 = 0x100 - (param_1 & 0xff) & 0xffff;
    }
    local_10[0] = (ushort)((param_1 & 0xff00ff) >> 0x10);
    local_10[1] = (ushort)(param_1 >> 8) & 0xff;
    local_10[2] = (short)(param_1 & 0xff00ff);
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_023a50e8 & 0x80) != 0);
    *(undefined2 *)PTR_SPI_bus_Control_023a50e8 = 0x8900;
    puVar3 = PTR_SPI_bus_Data_023a50ec;
    *(undefined2 *)PTR_SPI_bus_Data_023a50ec = 10;
    puVar1 = PTR_SPI_bus_Control_023a50e8;
    iVar5 = 0;
    do {
      do {
      } while ((*(ushort *)puVar1 & 0x80) != 0);
      *(ushort *)puVar3 = local_10[iVar5] & 0xff;
      puVar4 = PTR_SPI_bus_Data_023a50ec;
      puVar2 = PTR_SPI_bus_Control_023a50e8;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 3);
    for (iVar5 = 0; iVar5 < (int)(param_2 - 1); iVar5 = iVar5 + 1) {
      do {
      } while ((*(ushort *)puVar2 & 0x80) != 0);
      *(ushort *)puVar4 = (ushort)*(byte *)(param_3 + iVar5);
    }
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_023a50e8 & 0x80) != 0);
    *(undefined2 *)PTR_SPI_bus_Control_023a50e8 = 0x8100;
    *(ushort *)PTR_SPI_bus_Data_023a50ec = (ushort)*(byte *)(param_3 + iVar5);
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_023a50e8 & 0x80) != 0);
  }
  return;
}



void FUN_023a50f0(undefined4 param_1,int param_2,int param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  uint uVar4;
  int iVar5;
  ushort local_10 [4];
  
  if (param_2 != 0) {
    local_10[0] = (ushort)((uint)param_1 >> 0x10) & 0xff;
    local_10[1] = (ushort)((uint)param_1 >> 8) & 0xff;
    local_10[2] = (ushort)param_1 & 0xff;
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_023a5224 & 0x80) != 0);
    *(undefined2 *)PTR_SPI_bus_Control_023a5224 = 0x8900;
    puVar3 = PTR_SPI_bus_Data_023a5228;
    *(undefined2 *)PTR_SPI_bus_Data_023a5228 = 0xb;
    puVar1 = PTR_SPI_bus_Control_023a5224;
    iVar5 = 0;
    do {
      do {
      } while ((*(ushort *)puVar1 & 0x80) != 0);
      *(ushort *)puVar3 = local_10[iVar5] & 0xff;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 3);
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_023a5224 & 0x80) != 0);
    *(undefined2 *)PTR_SPI_bus_Data_023a5228 = 0;
    puVar3 = PTR_SPI_bus_Data_023a5228;
    puVar1 = PTR_SPI_bus_Control_023a5224;
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_023a5224 & 0x80) != 0);
    for (uVar4 = 0; puVar2 = PTR_SPI_bus_Control_023a5224, uVar4 < param_2 - 1U; uVar4 = uVar4 + 1)
    {
      *(undefined2 *)puVar3 = 0;
      do {
      } while ((*(ushort *)puVar1 & 0x80) != 0);
      *(char *)(param_3 + uVar4) = (char)*(undefined2 *)puVar3;
    }
    *(undefined2 *)PTR_SPI_bus_Control_023a5224 = 0x8100;
    *(undefined2 *)PTR_SPI_bus_Data_023a5228 = 0;
    do {
    } while ((*(ushort *)puVar2 & 0x80) != 0);
    *(char *)(param_3 + uVar4) = (char)*(undefined2 *)PTR_SPI_bus_Data_023a5228;
  }
  return;
}



void FUN_023a522c(undefined4 param_1,int param_2,int param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  uint uVar5;
  int iVar6;
  ushort local_10 [4];
  
  if (param_2 != 0) {
    local_10[0] = (ushort)((uint)param_1 >> 0x10) & 0xff;
    local_10[1] = (ushort)((uint)param_1 >> 8) & 0xff;
    local_10[2] = (ushort)param_1 & 0xff;
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_023a5344 & 0x80) != 0);
    *(undefined2 *)PTR_SPI_bus_Control_023a5344 = 0x8900;
    puVar3 = PTR_SPI_bus_Data_023a5348;
    *(undefined2 *)PTR_SPI_bus_Data_023a5348 = 3;
    puVar1 = PTR_SPI_bus_Control_023a5344;
    iVar6 = 0;
    do {
      do {
      } while ((*(ushort *)puVar1 & 0x80) != 0);
      *(ushort *)puVar3 = local_10[iVar6] & 0xff;
      puVar4 = PTR_SPI_bus_Data_023a5348;
      puVar2 = PTR_SPI_bus_Control_023a5344;
      iVar6 = iVar6 + 1;
    } while (iVar6 < 3);
    do {
    } while ((*(ushort *)PTR_SPI_bus_Control_023a5344 & 0x80) != 0);
    for (uVar5 = 0; puVar1 = PTR_SPI_bus_Control_023a5344, uVar5 < param_2 - 1U; uVar5 = uVar5 + 1)
    {
      *(undefined2 *)puVar4 = 0;
      do {
      } while ((*(ushort *)puVar2 & 0x80) != 0);
      *(char *)(param_3 + uVar5) = (char)*(undefined2 *)puVar4;
    }
    *(undefined2 *)PTR_SPI_bus_Control_023a5344 = 0x8100;
    *(undefined2 *)PTR_SPI_bus_Data_023a5348 = 0;
    do {
    } while ((*(ushort *)puVar1 & 0x80) != 0);
    *(char *)(param_3 + uVar5) = (char)*(undefined2 *)PTR_SPI_bus_Data_023a5348;
  }
  return;
}



void FUN_023a534c(undefined *param_1)

{
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a53b8 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a53b8 = 0x8900;
  *(undefined2 *)PTR_SPI_bus_Data_023a53bc = 5;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a53b8 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a53b8 = 0x8100;
  *(undefined2 *)PTR_SPI_bus_Data_023a53bc = 0;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a53b8 & 0x80) != 0);
  *param_1 = (char)*(undefined2 *)PTR_SPI_bus_Data_023a53bc;
  return;
}



void FUN_023a53c0(void)

{
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a53f8 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a53f8 = 0x8100;
  *(undefined2 *)PTR_SPI_bus_Data_023a53fc = 4;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a53f8 & 0x80) != 0);
  return;
}



void FUN_023a5400(void)

{
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a5438 & 0x80) != 0);
  *(undefined2 *)PTR_SPI_bus_Control_023a5438 = 0x8100;
  *(undefined2 *)PTR_SPI_bus_Data_023a543c = 6;
  do {
  } while ((*(ushort *)PTR_SPI_bus_Control_023a5438 & 0x80) != 0);
  return;
}



int FUN_023a5440(uint param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  uVar1 = 0;
  while( true ) {
    if (7 < (int)uVar1) {
      uVar1 = 0;
      iVar2 = 1;
      do {
        iVar3 = iVar2 * (param_1 >> ((uVar1 & 0x3f) << 2) & 0xf) + iVar3;
        uVar1 = uVar1 + 1;
        iVar2 = iVar2 * 10;
      } while ((int)uVar1 < 8);
      return iVar3;
    }
    if (9 < (param_1 >> ((uVar1 & 0x3f) << 2) & 0xf)) break;
    uVar1 = uVar1 + 1;
  }
  return 0;
}



undefined4 FUN_023a54b8(uint param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_r1;
  
  if (param_2 - 1U < 2) {
    param_1 = param_1 - 1;
    param_2 = param_2 + 0xc;
  }
  iVar1 = func_0x033b6d70(param_1,400);
  iVar2 = func_0x033b6d70(param_1,100);
  iVar3 = func_0x033b6d70(param_2 * 0xd + 8,5);
  func_0x033b6d70(param_3 + iVar1 + ((param_1 + (param_1 >> 2)) - iVar2) + iVar3,7);
  return extraout_r1;
}



void FUN_023a5534(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  ushort local_18;
  ushort local_16;
  uint local_14 [2];
  
  FUN_023a61e8(&local_18);
  FUN_023a6190(&local_16);
  if ((((int)((uint)local_18 << 0x18) < 0) || ((int)((uint)local_18 << 0x19) < 0)) ||
     ((int)((uint)local_16 << 0x18) < 0)) {
    local_18 = local_18 & 0xfffe | 1;
    FUN_023a61bc(&local_18);
  }
  if (((int)((uint)local_18 << 0x1b) < 0) || ((int)((uint)local_18 << 0x1a) < 0)) {
    local_16 = local_16 & 0xffb0;
    FUN_023a6164(&local_16);
  }
  FUN_023a64a4((ushort *)local_14);
  iVar1 = FUN_023a5440(local_14[0] & 0xff);
  iVar2 = FUN_023a5440((local_14[0] << 0x13) >> 0x1b);
  iVar3 = FUN_023a5440((local_14[0] << 10) >> 0x1a);
  uVar4 = FUN_023a54b8(iVar1 + 2000,iVar2,iVar3);
  if ((local_14[0] << 5) >> 0x1d != uVar4) {
    local_14[0] = local_14[0] & 0xf8ffffff | (uVar4 & 7) << 0x18;
    FUN_023a6478((ushort *)local_14);
  }
  FUN_023a64d0(1);
  return;
}



void FUN_023a5654(void)

{
  uint uVar1;
  bool bVar2;
  ushort local_10;
  ushort auStack_e [3];
  
  FUN_023a61e8(&local_10);
  if (((int)((uint)local_10 << 0x1b) < 0) || ((int)((uint)local_10 << 0x1a) < 0)) {
    FUN_023a6190(auStack_e);
    bVar2 = (int)((uint)local_10 << 0x1b) < 0;
    uVar1 = (uint)bVar2;
    if (bVar2) {
      auStack_e[0] = auStack_e[0] & 0xfff0;
    }
    if ((int)((uint)local_10 << 0x1a) < 0) {
      uVar1 = uVar1 | 2;
      auStack_e[0] = auStack_e[0] & 0xffbf;
    }
    FUN_023a6164(auStack_e);
    FUN_023a5ba0(0x30,uVar1);
  }
  return;
}



void FUN_023a56e4(void)

{
  ushort uVar1;
  ushort *puVar2;
  int iVar3;
  bool bVar4;
  ushort *puVar5;
  undefined auStack_28 [4];
  
  iVar3 = DAT_023a5b98;
  puVar2 = DAT_023a5b94;
  puVar5 = DAT_023a5b94 + 2;
LAB_023a579c:
  func_0x033ac0cc(iVar3,auStack_28,1);
  uVar1 = *(ushort *)(DAT_023a5b9c + 0xa0);
  switch((uint)uVar1) {
  case 0:
    FUN_023a65d0();
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0,0);
    goto LAB_023a579c;
  case 1:
    FUN_023a64d0(((uint)*puVar2 << 0x1e) >> 0x1f);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(1,0);
    goto LAB_023a579c;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  case 8:
    break;
  case 9:
    break;
  case 10:
    break;
  case 0xb:
    break;
  case 0xc:
    break;
  case 0xd:
    break;
  case 0xe:
    break;
  case 0xf:
    break;
  case 0x10:
    FUN_023a64a4(puVar2);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x10,0);
    goto LAB_023a579c;
  case 0x11:
    FUN_023a644c(puVar2);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x11,0);
    goto LAB_023a579c;
  case 0x12:
    FUN_023a6420(puVar2 + 2);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x12,0);
    goto LAB_023a579c;
  case 0x13:
    bVar4 = FUN_023a63a0(puVar5);
    if (bVar4) {
      *(undefined4 *)(iVar3 + 0x19c) = 0;
      FUN_023a5ba0(0x13,0);
    }
    else {
      *(undefined4 *)(iVar3 + 0x19c) = 0;
      FUN_023a5ba0(0x13,2);
    }
    goto LAB_023a579c;
  case 0x14:
    bVar4 = FUN_023a62fc(puVar5);
    if (bVar4) {
      *(undefined4 *)(iVar3 + 0x19c) = 0;
      FUN_023a5ba0(0x14,0);
    }
    else {
      *(undefined4 *)(iVar3 + 0x19c) = 0;
      FUN_023a5ba0(0x14,2);
    }
    goto LAB_023a579c;
  case 0x15:
    bVar4 = FUN_023a6260(puVar5);
    if (bVar4) {
      *(undefined4 *)(iVar3 + 0x19c) = 0;
      FUN_023a5ba0(0x15,0);
    }
    else {
      *(undefined4 *)(iVar3 + 0x19c) = 0;
      FUN_023a5ba0(0x15,2);
    }
    goto LAB_023a579c;
  case 0x16:
    FUN_023a61e8(puVar2);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x16,0);
    goto LAB_023a579c;
  case 0x17:
    FUN_023a6190(puVar2 + 1);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x17,0);
    goto LAB_023a579c;
  case 0x18:
    FUN_023a6138(puVar2 + 2);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x18,0);
    goto LAB_023a579c;
  case 0x19:
    FUN_023a60e0(puVar2 + 2);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x19,0);
    goto LAB_023a579c;
  case 0x1a:
    break;
  case 0x1b:
    break;
  case 0x1c:
    break;
  case 0x1d:
    break;
  case 0x1e:
    break;
  case 0x1f:
    break;
  case 0x20:
    FUN_023a6478(puVar2);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x20,0);
    goto LAB_023a579c;
  case 0x21:
    FUN_023a6420(puVar2 + 2);
    FUN_023a6478(puVar2);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x21,0);
    goto LAB_023a579c;
  case 0x22:
    FUN_023a63f4(puVar2 + 2);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x22,0);
    goto LAB_023a579c;
  case 0x23:
    bVar4 = FUN_023a634c(puVar5);
    if (bVar4) {
      *(undefined4 *)(iVar3 + 0x19c) = 0;
      FUN_023a5ba0(0x23,0);
    }
    else {
      *(undefined4 *)(iVar3 + 0x19c) = 0;
      FUN_023a5ba0(0x23,2);
    }
    goto LAB_023a579c;
  case 0x24:
    bVar4 = FUN_023a62ac(puVar5);
    if (bVar4) {
      *(undefined4 *)(iVar3 + 0x19c) = 0;
      FUN_023a5ba0(0x24,0);
    }
    else {
      *(undefined4 *)(iVar3 + 0x19c) = 0;
      FUN_023a5ba0(0x24,2);
    }
    goto LAB_023a579c;
  case 0x25:
    bVar4 = FUN_023a6214(puVar5);
    if (bVar4) {
      *(undefined4 *)(iVar3 + 0x19c) = 0;
      FUN_023a5ba0(0x25,0);
    }
    else {
      *(undefined4 *)(iVar3 + 0x19c) = 0;
      FUN_023a5ba0(0x25,2);
    }
    goto LAB_023a579c;
  case 0x26:
    FUN_023a61bc(puVar2);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x26,0);
    goto LAB_023a579c;
  case 0x27:
    FUN_023a6164(puVar2 + 1);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x27,0);
    goto LAB_023a579c;
  case 0x28:
    FUN_023a610c(puVar2 + 2);
    *(undefined4 *)(iVar3 + 0x19c) = 0;
    FUN_023a5ba0(0x28,0);
    goto LAB_023a579c;
  case 0x29:
    goto LAB_023a5b68;
  }
  *(undefined4 *)(iVar3 + 0x19c) = 0;
  FUN_023a5ba0((uint)uVar1,1);
  goto LAB_023a579c;
LAB_023a5b68:
  FUN_023a60b4(puVar2 + 2);
  *(undefined4 *)(iVar3 + 0x19c) = 0;
  FUN_023a5ba0(0x29,0);
  goto LAB_023a579c;
}



void FUN_023a5ba0(uint param_1,uint param_2)

{
  int iVar1;
  
  do {
    iVar1 = func_0x033adeec(5,(param_1 & 0x7f) << 8 | 0x8000 | param_2 & 0xff,0);
  } while (iVar1 < 0);
  return;
}



void FUN_023a5be0(undefined4 param_1,uint param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = DAT_023a5d14;
  if (param_3 != 0) {
    return;
  }
  uVar1 = ((param_2 & 0x7f00) << 8) >> 0x10;
  switch(uVar1) {
  case 0:
    break;
  case 1:
    break;
  case 2:
  default:
switchD_023a5bfc_caseD_2a:
    FUN_023a5ba0(uVar1,1);
    return;
  case 3:
    goto switchD_023a5bfc_caseD_2a;
  case 4:
    goto switchD_023a5bfc_caseD_2a;
  case 5:
    goto switchD_023a5bfc_caseD_2a;
  case 6:
    goto switchD_023a5bfc_caseD_2a;
  case 7:
    goto switchD_023a5bfc_caseD_2a;
  case 8:
    goto switchD_023a5bfc_caseD_2a;
  case 9:
    goto switchD_023a5bfc_caseD_2a;
  case 10:
    goto switchD_023a5bfc_caseD_2a;
  case 0xb:
    goto switchD_023a5bfc_caseD_2a;
  case 0xc:
    goto switchD_023a5bfc_caseD_2a;
  case 0xd:
    goto switchD_023a5bfc_caseD_2a;
  case 0xe:
    goto switchD_023a5bfc_caseD_2a;
  case 0xf:
    goto switchD_023a5bfc_caseD_2a;
  case 0x10:
    break;
  case 0x11:
    break;
  case 0x12:
    break;
  case 0x13:
    break;
  case 0x14:
    break;
  case 0x15:
    break;
  case 0x16:
    break;
  case 0x17:
    break;
  case 0x18:
    break;
  case 0x19:
    break;
  case 0x1a:
    goto switchD_023a5bfc_caseD_2a;
  case 0x1b:
    goto switchD_023a5bfc_caseD_2a;
  case 0x1c:
    goto switchD_023a5bfc_caseD_2a;
  case 0x1d:
    goto switchD_023a5bfc_caseD_2a;
  case 0x1e:
    goto switchD_023a5bfc_caseD_2a;
  case 0x1f:
    goto switchD_023a5bfc_caseD_2a;
  case 0x20:
    break;
  case 0x21:
    break;
  case 0x22:
    break;
  case 0x23:
    break;
  case 0x24:
    break;
  case 0x25:
    break;
  case 0x26:
    break;
  case 0x27:
    break;
  case 0x28:
    break;
  case 0x29:
  }
  if (*(int *)(DAT_023a5d14 + 0x19c) == 0) {
    *(undefined4 *)(DAT_023a5d14 + 0x19c) = 1;
    *(short *)(DAT_023a5d18 + 0xa0) = (short)((param_2 & 0x7f00) >> 8);
    iVar2 = func_0x033ac16c(iVar2,0,0);
    if (iVar2 == 0) {
      FUN_023a5ba0(uVar1,4);
    }
  }
  else {
    FUN_023a5ba0(uVar1,3);
  }
  return;
}



void FUN_023a5d1c(undefined4 param_1)

{
  undefined4 uVar1;
  
  if (*DAT_023a5df0 == 0) {
    *DAT_023a5df0 = 1;
    *(undefined4 *)(DAT_023a5df4 + 0x19c) = 1;
    FUN_023a5534();
    *(undefined4 *)(DAT_023a5df4 + 0x19c) = 0;
    func_0x033addc0();
    func_0x033adfb8(5,DAT_023a5df8);
    func_0x033ac200(DAT_023a5df4,DAT_023a5dfc,4);
    func_0x033abc80(DAT_023a5e00,DAT_023a5e04,0,DAT_023a5e08,0x100,param_1);
    func_0x033abb18(DAT_023a5e00);
    func_0x033ae100(0x8000);
    func_0x033ae11c(0x40,0);
    func_0x033ae11c(0x100,0x100);
    uVar1 = func_0x033ad8a0();
    func_0x033ab458(0x80,DAT_023a5e0c);
    func_0x033ab3a0(0x80);
    func_0x033ad8b4(uVar1);
  }
  return;
}



void FUN_023a5e10(uint param_1,uint param_2,ushort *param_3,int param_4)

{
  FUN_023a6610();
  FUN_023a6684(param_1,param_2);
  if (param_1 == 6) {
    FUN_023a66f4(param_3,param_4);
  }
  else if (param_1 == 0x86) {
    FUN_023a6784(param_3,param_4);
  }
  FUN_023a6650();
  return;
}



void FUN_023a5e74(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = *param_1;
  uVar1 = (uVar2 << 0x12) >> 0x1a;
  switch(uVar1) {
  case 0:
    goto LAB_023a5f1c;
  case 1:
    goto LAB_023a5f1c;
  case 2:
    goto LAB_023a5f1c;
  case 3:
    goto LAB_023a5f1c;
  case 4:
    goto LAB_023a5f1c;
  case 5:
    goto LAB_023a5f1c;
  case 6:
    goto LAB_023a5f1c;
  case 7:
    goto LAB_023a5f1c;
  case 8:
    goto LAB_023a5f40;
  case 9:
LAB_023a5f40:
    if (-1 < (int)(uVar2 << 0x11)) {
      return;
    }
    *param_1 = uVar2 & 0xffffc0ff | (uVar1 + 0x18 & 0x3f) << 8;
    return;
  case 10:
    break;
  case 0xb:
    break;
  case 0xc:
    break;
  case 0xd:
    break;
  case 0xe:
    break;
  case 0xf:
    break;
  case 0x10:
    goto LAB_023a5f1c;
  case 0x11:
LAB_023a5f1c:
    if (-1 < (int)(uVar2 << 0x11)) {
      return;
    }
    *param_1 = uVar2 & 0xffffc0ff | (uVar1 + 0x12 & 0x3f) << 8;
    return;
  case 0x12:
    goto LAB_023a5f64;
  case 0x13:
    goto LAB_023a5f64;
  case 0x14:
    goto LAB_023a5f64;
  case 0x15:
    goto LAB_023a5f64;
  case 0x16:
    goto LAB_023a5f64;
  case 0x17:
    goto LAB_023a5f64;
  case 0x18:
    goto LAB_023a5f64;
  case 0x19:
    goto LAB_023a5f64;
  case 0x1a:
    break;
  case 0x1b:
    break;
  case 0x1c:
    break;
  case 0x1d:
    break;
  case 0x1e:
    break;
  case 0x1f:
    break;
  case 0x20:
    goto LAB_023a5f64;
  case 0x21:
    goto LAB_023a5f64;
  case 0x22:
    goto LAB_023a5f64;
  case 0x23:
LAB_023a5f64:
    *param_1 = uVar2 | 0x4000;
    return;
  }
  *param_1 = *param_1 & 0xffffbfff;
  *param_1 = *param_1 & 0xffffc0ff;
  return;
}



void FUN_023a5f8c(uint *param_1)

{
  uint uVar1;
  
  uVar1 = *param_1;
  switch((uVar1 << 0x12) >> 0x1a) {
  case 0:
    goto LAB_023a6034;
  case 1:
    goto LAB_023a6034;
  case 2:
    goto LAB_023a6034;
  case 3:
    goto LAB_023a6034;
  case 4:
    goto LAB_023a6034;
  case 5:
    goto LAB_023a6034;
  case 6:
    goto LAB_023a6034;
  case 7:
    goto LAB_023a6034;
  case 8:
    goto LAB_023a6034;
  case 9:
    goto LAB_023a6034;
  case 10:
    break;
  case 0xb:
    break;
  case 0xc:
    break;
  case 0xd:
    break;
  case 0xe:
    break;
  case 0xf:
    break;
  case 0x10:
    goto LAB_023a6034;
  case 0x11:
LAB_023a6034:
    *param_1 = uVar1 & 0xffffbfff;
    return;
  case 0x12:
    goto LAB_023a6040;
  case 0x13:
    goto LAB_023a6040;
  case 0x14:
    goto LAB_023a6040;
  case 0x15:
    goto LAB_023a6040;
  case 0x16:
    goto LAB_023a6040;
  case 0x17:
    goto LAB_023a6040;
  case 0x18:
    goto LAB_023a6040;
  case 0x19:
    goto LAB_023a6040;
  case 0x1a:
    break;
  case 0x1b:
    break;
  case 0x1c:
    break;
  case 0x1d:
    break;
  case 0x1e:
    break;
  case 0x1f:
    break;
  case 0x20:
    goto LAB_023a606c;
  case 0x21:
LAB_023a606c:
    *param_1 = uVar1 | 0x4000;
    *param_1 = *param_1 & 0xffffc0ff | (((*param_1 << 0x12) >> 0x1a) - 0x18 & 0x3f) << 8;
    return;
  case 0x22:
    goto LAB_023a6040;
  case 0x23:
LAB_023a6040:
    *param_1 = uVar1 | 0x4000;
    *param_1 = *param_1 & 0xffffc0ff | (((*param_1 << 0x12) >> 0x1a) - 0x12 & 0x3f) << 8;
    return;
  }
  *param_1 = *param_1 & 0xffffbfff;
  *param_1 = *param_1 & 0xffffc0ff;
  return;
}



void FUN_023a60b4(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(6,0x70,param_1,1);
  return;
}



void FUN_023a60e0(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(0x86,0x70,param_1,1);
  return;
}



void FUN_023a610c(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(6,0x30,param_1,1);
  return;
}



void FUN_023a6138(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(0x86,0x30,param_1,1);
  return;
}



void FUN_023a6164(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(6,0x40,param_1,1);
  return;
}



void FUN_023a6190(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(0x86,0x40,param_1,1);
  return;
}



void FUN_023a61bc(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(6,0,param_1,1);
  return;
}



void FUN_023a61e8(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(0x86,0,param_1,1);
  return;
}



bool FUN_023a6214(ushort *param_1)

{
  bool bVar1;
  ushort local_10 [4];
  
  FUN_023a6190(local_10);
  bVar1 = (int)((uint)local_10[0] << 0x19) < 0;
  if (bVar1) {
    FUN_023a5e10(6,0x50,param_1,3);
  }
  return bVar1;
}



bool FUN_023a6260(ushort *param_1)

{
  bool bVar1;
  ushort local_10 [4];
  
  FUN_023a6190(local_10);
  bVar1 = (int)((uint)local_10[0] << 0x19) < 0;
  if (bVar1) {
    FUN_023a5e10(0x86,0x50,param_1,3);
  }
  return bVar1;
}



bool FUN_023a62ac(ushort *param_1)

{
  bool bVar1;
  ushort local_10 [4];
  
  FUN_023a6190(local_10);
  bVar1 = (local_10[0] & 0xf) == 4;
  if (bVar1) {
    FUN_023a5e10(6,0x10,param_1,3);
  }
  return bVar1;
}



bool FUN_023a62fc(ushort *param_1)

{
  bool bVar1;
  ushort local_10 [4];
  
  FUN_023a6190(local_10);
  bVar1 = (local_10[0] & 0xf) == 4;
  if (bVar1) {
    FUN_023a5e10(0x86,0x10,param_1,3);
  }
  return bVar1;
}



bool FUN_023a634c(ushort *param_1)

{
  bool bVar1;
  ushort local_10 [4];
  
  FUN_023a6190(local_10);
  bVar1 = (local_10[0] & 0xb) == 1;
  if (bVar1) {
    FUN_023a5e10(6,0x10,param_1,1);
  }
  return bVar1;
}



bool FUN_023a63a0(ushort *param_1)

{
  bool bVar1;
  ushort local_10 [4];
  
  FUN_023a6190(local_10);
  bVar1 = (local_10[0] & 0xb) == 1;
  if (bVar1) {
    FUN_023a5e10(0x86,0x10,param_1,1);
  }
  return bVar1;
}



void FUN_023a63f4(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(6,0x60,param_1,3);
  return;
}



void FUN_023a6420(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(0x86,0x60,param_1,3);
  return;
}



void FUN_023a644c(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(0x86,0x20,param_1,4);
  return;
}



void FUN_023a6478(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(6,0x20,param_1,7);
  return;
}



void FUN_023a64a4(ushort *param_1)

{
  func_0x033ae100(0x8000);
  FUN_023a5e10(0x86,0x20,param_1,7);
  return;
}



// WARNING: Removing unreachable block (ram,0x023a659c)

void FUN_023a64d0(uint param_1)

{
  ushort local_18 [2];
  uint auStack_14 [2];
  
  if (((param_1 & 1) == 1) && (FUN_023a61e8(local_18), -1 < (int)((uint)local_18[0] << 0x1e))) {
    local_18[0] = local_18[0] & 0xfffd | (ushort)((param_1 & 1) << 1);
    FUN_023a61bc(local_18);
    FUN_023a5e10(0x86,0x10,(ushort *)auStack_14,3);
    if ((param_1 & 1) == 0) {
      FUN_023a5f8c(auStack_14);
    }
    else {
      FUN_023a5e74(auStack_14);
    }
    FUN_023a5e10(6,0x10,(ushort *)auStack_14,3);
    FUN_023a5e10(0x86,0x50,(ushort *)auStack_14,3);
    FUN_023a5e74(auStack_14);
    FUN_023a5e10(6,0x50,(ushort *)auStack_14,3);
  }
  return;
}



void FUN_023a65d0(void)

{
  ushort local_8 [4];
  
  func_0x033ae100(0x8000);
  local_8[0] = local_8[0] & 0xfffe | 1;
  FUN_023a5e10(6,0,local_8,1);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_023a6610(void)

{
  int iVar1;
  
  iVar1 = 2;
  do {
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  _RTC_Realtime_Clock_Bus = _RTC_Realtime_Clock_Bus & 0xff88 | 0x76;
  iVar1 = 2;
  do {
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_023a6650(void)

{
  int iVar1;
  
  iVar1 = 2;
  do {
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  _RTC_Realtime_Clock_Bus = _RTC_Realtime_Clock_Bus & 0xfffb;
  iVar1 = 2;
  do {
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_023a6684(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  _RTC_Realtime_Clock_Bus = _RTC_Realtime_Clock_Bus & 0xff88 | 0x74;
  uVar1 = 0;
  do {
    iVar2 = 9;
    do {
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    _RTC_Realtime_Clock_Bus =
         _RTC_Realtime_Clock_Bus & 0xfffc |
         (ushort)(((param_1 | param_2) >> (uVar1 & 0xff) & 1) != 0) | 2;
    iVar2 = 9;
    do {
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    uVar1 = uVar1 + 1;
  } while (uVar1 != 8);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_023a66f4(ushort *param_1,int param_2)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  
  do {
    if (((uint)param_1 & 1) == 0) {
      uVar1 = *param_1;
    }
    else {
      uVar1 = *(ushort *)((int)param_1 + -1) >> 8;
    }
    _RTC_Realtime_Clock_Bus = _RTC_Realtime_Clock_Bus & 0xff88 | 0x74;
    uVar2 = 0;
    do {
      iVar3 = 9;
      do {
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      _RTC_Realtime_Clock_Bus =
           _RTC_Realtime_Clock_Bus & 0xfffc | (ushort)((uVar1 >> (uVar2 & 0xff) & 1) != 0) | 2;
      iVar3 = 9;
      do {
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      uVar2 = uVar2 + 1;
    } while (uVar2 != 8);
    param_1 = (ushort *)((int)param_1 + 1);
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return;
}



// WARNING: Removing unreachable block (ram,0x023a67c8)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_023a6784(ushort *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  do {
    _RTC_Realtime_Clock_Bus = _RTC_Realtime_Clock_Bus & 0xff88 | 100;
    iVar1 = 0;
    do {
      iVar2 = 9;
      do {
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
      _RTC_Realtime_Clock_Bus = _RTC_Realtime_Clock_Bus & 0xfffc | 2;
      iVar2 = 9;
      do {
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
      iVar1 = iVar1 + 1;
    } while (iVar1 != 8);
    if (((uint)param_1 & 1) == 0) {
      *param_1 = *param_1 & 0xff00;
    }
    else {
      *(ushort *)((int)param_1 + -1) = *(ushort *)((int)param_1 + -1) & 0xff;
    }
    param_1 = (ushort *)((int)param_1 + 1);
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return;
}


