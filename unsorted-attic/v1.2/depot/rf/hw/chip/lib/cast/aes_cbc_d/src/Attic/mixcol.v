// This confidential and propriety software may be used
// only as authorized by a licensing agreement from
// Ocean Logic Pty Ltd http://www.ocean-logic.com
// 
// In the event of publication, the following notice is
// applicable
// 
// (C) COPYRIGHT 2001 Ocean Logic Pty Ltd
// ALL RIGHTS RESERVED
//
// the entire notice must be reproduced on all
// authorized copies
// 
// File : mixcol.vhd
// Author : Vincenzo Liguori
// Date : 01-03-02
// Version 1.0
// Abstract :
// This implements the AES Mix col operation
// 
// Modification history :
// Date      by  Version  Change description
// -------------------------------------------------
// 01-03-02  VL   1.0     Original

module mixcol(
x,
do0,
do1,
do2,
do3
);

input[7:0] x;
output[7:0] do0, do1, do2, do3;

wire  [7:0] x;
wire  [7:0] do0;
wire  [7:0] do1;
wire  [7:0] do2;
wire  [7:0] do3;


wire [7:0] x2;
wire [7:0] x4;
wire [7:0] x8;
wire [7:0] xc;

  assign x2 = {x[6:4] ,x[3]  ^ x[7] ,x[2]  ^ x[7] ,x[1] ,x[0]  ^ x[7] ,x[7] };
  assign x4 = {x[5:4] ,x[3]  ^ x[7] ,x[2]  ^ x[7]  ^ x[6] ,x[1]  ^ x[6] ,x[0]  ^ x[7] ,x[7]  ^ x[6] ,x[6] };
  assign x8 = {x[4] ,x[3]  ^ x[7] ,x[2]  ^ x[7]  ^ x[6] ,x[1]  ^ x[6]  ^ x[5] ,x[0]  ^ x[7]  ^ x[5] ,x[7]  ^ x[6] ,x[6]  ^ x[5] ,x[5] };
  assign xc = x4 ^ x8;
  assign do0 = xc ^ x2;
  assign do1 = x8 ^ x2 ^ x;
  assign do2 = xc ^ x;
  assign do3 = x8 ^ x;

endmodule
