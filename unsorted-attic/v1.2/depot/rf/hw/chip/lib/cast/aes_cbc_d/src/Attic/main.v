// This confidential and propriety software may be used
// only as authorized by a licensing agreement from
// Ocean Logic Pty Ltd http:/www.ocean-logic.com
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
// File : main.vhd
// Author : Vincenzo Liguori
// Date : 01-03-02
// Version 1.0
// Abstract :
// This implements the main AES loop
// 
// Modification history :
// Date      by  Version  Change description
// -------------------------------------------------
// 01-03-02  VL   1.0     Original

module main(
clk,
rstn,
en,
dinit,
ibypass,
final,
din,
olddata,
key,
dout
);

// Inputs
input clk, rstn;
input en, dinit, ibypass, final;
input[31:0] din, olddata, key;
// Outputs 
output[31:0] dout;

wire   clk;
wire   rstn;
wire   en;
wire   dinit;
wire   ibypass;
wire   final;
wire  [31:0] din;
wire  [31:0] olddata;
wire  [31:0] key;
wire  [31:0] dout;


// AES S-boxes 
wire [31:0] dd;
wire [31:0] dloop;
// Intermediate products
wire [7:0] ddata;
wire [7:0] s0;
wire [7:0] s1;
wire [7:0] s2;
wire [7:0] s3;
wire [7:0] pp00;
wire [7:0] pp01;
wire [7:0] pp02;
wire [7:0] pp03;
wire [7:0] pp10;
wire [7:0] pp11;
wire [7:0] pp12;
wire [7:0] pp13;
wire [7:0] pp20;
wire [7:0] pp21;
wire [7:0] pp22;
wire [7:0] pp23;
wire [7:0] pp30;
wire [7:0] pp31;
wire [7:0] pp32;
wire [7:0] pp33;

  // First column product
  sbox sbx00(
      // Inputs
    .rstn(rstn),
    .clk(clk),
    .en(en),
    .din(olddata[31:24] ),
    // Outputs 
    .s(s0));

  // Mix Col module
  mixcol mx0(
      .x(s0),
    .do0(pp00),
    .do1(pp01),
    .do2(pp02),
    .do3(pp03));

  // Second column product
  assign ddata = ibypass == 1'b 1 ? dout[23:16]  : olddata[23:16] ;
  sbox sbx10(
      // Inputs
    .rstn(rstn),
    .clk(clk),
    .en(en),
    .din(ddata),
    // Outputs 
    .s(s1));

  // Mix Col module
  mixcol mx1(
      .x(s1),
    .do0(pp10),
    .do1(pp11),
    .do2(pp12),
    .do3(pp13));

  // Third column product
  sbox sbx20(
      // Inputs
    .rstn(rstn),
    .clk(clk),
    .en(en),
    .din(olddata[15:8] ),
    // Outputs 
    .s(s2));

  // Mix Col module
  mixcol mx2(
      .x(s2),
    .do0(pp20),
    .do1(pp21),
    .do2(pp22),
    .do3(pp23));

  // Fourth column product
  sbox sbx30(
      // Inputs
    .rstn(rstn),
    .clk(clk),
    .en(en),
    .din(olddata[7:0] ),
    // Outputs 
    .s(s3));

  // Mix Col module
  mixcol mx3(
      .x(s3),
    .do0(pp30),
    .do1(pp31),
    .do2(pp32),
    .do3(pp33));

  assign dloop[31:24]  = final == 1'b 0 ? pp00 ^ pp11 ^ pp22 ^ pp33 : s0;
  assign dloop[23:16]  = final == 1'b 0 ? pp03 ^ pp10 ^ pp21 ^ pp32 : s1;
  assign dloop[15:8]  = final == 1'b 0 ? pp02 ^ pp13 ^ pp20 ^ pp31 : s2;
  assign dloop[7:0]  = final == 1'b 0 ? pp01 ^ pp12 ^ pp23 ^ pp30 : s3;
  assign dd = dinit == 1'b 1 ? din : dloop;
  assign dout = dd ^ key;

endmodule
