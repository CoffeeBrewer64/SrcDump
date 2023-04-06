//
//------------------------------------------------------------
// Copyright(c) 2009-2010 by Digital Media Professionals Inc.
// All rights reserved.
//------------------------------------------------------------
// This source code is the confidential and proprietary
// of Digital Media Professionals Inc.
//------------------------------------------------------------
//

//------------------------------------------
//  related cmp
//------------------------------------------
#define CMP_MODE_EQ         0
#define CMP_MODE_NE         1
#define CMP_MODE_LT         2
#define CMP_MODE_LE         3
#define CMP_MODE_GT         4
#define CMP_MODE_GE         5

//------------------------------------------
//  related condition
//------------------------------------------
#define COND_MODE_OR        0
#define COND_MODE_AND       1
#define COND_MODE_STA0      2
#define COND_MODE_STA1      3

//------------------------------------------
//  related status reg
//------------------------------------------
#define STAT0_0             0
#define STAT0_1             1
#define STAT1_0             0
#define STAT1_1             1

// Input registers map
#define aPosition           v0
#define aTexCoord           v1

#define uProjection         c0
#define uModelView          c4

// Constant registers map
#define CONST               c95     // 0.0 0.5 1.0 3.0

#define EQ                  0
#define NEQ                 1
#define LESS                2
#define LEQ                 3
#define GT                  4
#define GEQ                 5

// Temporary registers map
#define TEMP0               r0
#define TEMP1               r1
#define TEMP2               r2
#define TEMP3               r3
#define TEMP4               r4

#define TEMP_TEX0           r10
#define TEMP_TEX1           r11
#define TEMP_TEX2           r12
#define TEMP_TEX3           r13
#define TEMP_TANG           r13
#define TEMP_NORM           r14
#define TEMP_VIEW           r15
#define TEMP_POS            r12

// Constant registers
def     CONST,              0.0, 0.5, 1.0, 3.0

#pragma bind_symbol(aPosition.xyzw,v0,v0)
#pragma bind_symbol(aTexCoord.xyz,v1,v1)

#pragma output_map (position, o0)
#pragma output_map (texture0, o1.xy)
#pragma output_map (texture1, o2.xy)
#pragma output_map (texture2, o3.xy)

#pragma bind_symbol(uProjection,c0,c3)
#pragma bind_symbol(uModelView,c4,c7)

l_position:
    m4x4    TEMP_VIEW,          aPosition,          uModelView
    dp4     o0.x,               TEMP_VIEW,          uProjection[0]
    dp4     o0.y,               TEMP_VIEW,          uProjection[1]
    dp4     o0.z,               TEMP_VIEW,          uProjection[2]
    dp4     o0.w,               TEMP_VIEW,          uProjection[3]
    ret
    nop

main:
    call    l_position
    mov     o1, aTexCoord
    mov     o2, aTexCoord
    mov     o3, aTexCoord
    end
endmain:
