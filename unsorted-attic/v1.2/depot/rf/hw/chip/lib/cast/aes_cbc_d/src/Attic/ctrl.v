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
// File : ctrl.vhd
// Author : Vincenzo Liguori
// Date : 01-03-02
// Version 1.0
// Abstract :
// This implements the AES controller
// 
// Modification history :
// Date      by  Version  Change description
// -------------------------------------------------
// 01-03-02  VL   1.0     Original

module ctrl(
clk,
rstn,
en,
go,
ksize,
dinit,
ibypass,
final,
raddr0,
raddr1,
raddr2,
raddr3,
waddr0,
waddr1,
waddr2,
waddr3,
dout_vld
);

// Inputs
input clk, rstn;
input en, go;
input[1:0] ksize;
// Outputs 
output dinit, ibypass;
output final;
output[1:0] raddr0, raddr1, raddr2, raddr3;
output[1:0] waddr0, waddr1, waddr2, waddr3;
output dout_vld;

wire   clk;
wire   rstn;
wire   en;
wire   go;
wire  [1:0] ksize;
reg   dinit;
wire   ibypass;
reg   final;
reg  [1:0] raddr0;
wire  [1:0] raddr1;
wire  [1:0] raddr2;
wire  [1:0] raddr3;
reg  [1:0] waddr0;
reg  [1:0] waddr1;
reg  [1:0] waddr2;
reg  [1:0] waddr3;
wire   dout_vld;


wire [1:0] inc1;
wire [1:0] inc2;
wire [1:0] inc3;
wire  finali;
wire  endround;
wire  byps;
reg [3:0] round;
reg [3:0] maxround;

  always @(ksize) begin
    // Select the number of rounds
    case(ksize)
    2'b 00 : begin
      maxround <= 4'b 1010;
    end
    2'b 01 : begin
      maxround <= 4'b 1100;
    end
    default : begin
      maxround <= 4'b 1110;
    end
    endcase
  end

  assign byps = raddr0 == 2'b 00 ? 1'b 1 : 1'b 0;
  assign ibypass = byps;
  assign endround = raddr0 == 2'b 11 ? 1'b 1 : 1'b 0;
  assign finali = round == maxround ? 1'b 1 : 1'b 0;
  assign dout_vld = final;
  always @(posedge clk or negedge rstn) begin
    if(rstn == 1'b 0) begin
      round <= {4{1'b0}};
      raddr0 <= {2{1'b0}};
      waddr0 <= {2{1'b0}};
      waddr1 <= {2{1'b0}};
      waddr2 <= {2{1'b0}};
      waddr3 <= {2{1'b0}};
      dinit <= 1'b 0;
      final <= 1'b 0;
    end else begin
      if(en == 1'b 1) begin
        final <= finali;
        if(go == 1'b 0) begin
          dinit <= 1'b 0;
          round <= {4{1'b0}};
          raddr0 <= {2{1'b0}};
        end
        else begin
          if(round == 4'b 0000) begin
            dinit <= 1'b 1;
          end
          else begin
            dinit <= 1'b 0;
          end
          if(endround == 1'b 1) begin
            raddr0 <= {2{1'b0}};
            if(finali == 1'b 1) begin
              round <= {4{1'b0}};
            end
            else begin
              round <= round + 1'b 1;
            end
          end
          else begin
            raddr0 <= raddr0 + 1'b 1;
          end
        end
        waddr0 <= raddr0;
        waddr1 <= raddr1;
        waddr2 <= raddr2;
        waddr3 <= raddr3;
      end
    end
  end

  assign inc1 = 2'b 00;
  addmod ad1(
      // Inputs
    .clk(clk),
    .rstn(rstn),
    .en(en),
    .clrn(go),
    .endround(endround),
    .inc(inc1),
    // Outputs 
    .raddr(raddr1));

  assign inc2 = 2'b 11;
  addmod ad2(
      // Inputs
    .clk(clk),
    .rstn(rstn),
    .en(en),
    .clrn(go),
    .endround(endround),
    .inc(inc2),
    // Outputs 
    .raddr(raddr2));

  assign inc3 = 2'b 10;
  addmod ad3(
      // Inputs
    .clk(clk),
    .rstn(rstn),
    .en(en),
    .clrn(go),
    .endround(endround),
    .inc(inc3),
    // Outputs 
    .raddr(raddr3));


endmodule
