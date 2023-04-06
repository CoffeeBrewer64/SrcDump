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
// File : mem4.vhd
// Author : Vincenzo Liguori
// Date : 01-03-02
// Version 1.0
// Abstract :
// This implements the AES status registers
// 
// Modification history :
// Date      by  Version  Change description
// -------------------------------------------------
// 01-03-02  VL   1.0     Original

module mem4(
clk,
rstn,
en,
we,
ar,
aw,
din,
dout
);

input clk, rstn;
input en, we;
input[1:0] ar, aw;
input[7:0] din;
output[7:0] dout;

wire   clk;
wire   rstn;
wire   en;
wire   we;
wire  [1:0] ar;
wire  [1:0] aw;
wire  [7:0] din;
reg  [7:0] dout;


reg [7:0] d0;
reg [7:0] d1;
reg [7:0] d2;
reg [7:0] d3;

  always @(ar or d0 or d1 or d2 or d3) begin
    case(ar)
      2'b 00 : dout <= d0;
      2'b 01 : dout <= d1;
      2'b 10 : dout <= d2;
      default : dout <= d3;
    endcase
  end

  always @(posedge clk or negedge rstn) begin
    if(rstn == 1'b 0) begin
      d0 <= {8{1'b0}};
      d1 <= {8{1'b0}};
      d2 <= {8{1'b0}};
      d3 <= {8{1'b0}};
    end else begin
      if(en == 1'b 1) begin
        if(we == 1'b 1) begin
          case(aw)
          2'b 00 : begin
            d0 <= din;
          end
          2'b 01 : begin
            d1 <= din;
          end
          2'b 10 : begin
            d2 <= din;
          end
          default : begin
            d3 <= din;
          end
          endcase
        end
      end
    end
  end


endmodule
