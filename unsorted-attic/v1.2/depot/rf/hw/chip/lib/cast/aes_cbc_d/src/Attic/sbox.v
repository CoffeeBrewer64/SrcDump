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
// File : sbox.vhd
// Author : Vincenzo Liguori
// Date : 01-03-02
// Version 1.0
// Abstract :
// This implements an AES S-box
// 
// Modification history :
// Date      by  Version  Change description
// -------------------------------------------------
// 01-03-02  VL   1.0     Original

module sbox(
rstn,
clk,
en,
din,
s
);

// Inputs
input rstn, clk;
input en;
input[7:0] din;
// Outputs 
output[7:0] s;

wire   rstn;
wire   clk;
wire   en;
wire  [7:0] din;
reg  [7:0] s;


reg [7:0] x;

  always @(posedge clk or negedge rstn) begin
    if(rstn == 1'b 0) begin
      x <= {8{1'b0}};
    end else begin
      if(en == 1'b 1) begin
        x <= din;
      end
    end
  end

  always @(x) begin
    case(x)
    8'b 00000000 : begin
      s <= 8'b 01010010;
    end
    8'b 00000001 : begin
      s <= 8'b 00001001;
    end
    8'b 00000010 : begin
      s <= 8'b 01101010;
    end
    8'b 00000011 : begin
      s <= 8'b 11010101;
    end
    8'b 00000100 : begin
      s <= 8'b 00110000;
    end
    8'b 00000101 : begin
      s <= 8'b 00110110;
    end
    8'b 00000110 : begin
      s <= 8'b 10100101;
    end
    8'b 00000111 : begin
      s <= 8'b 00111000;
    end
    8'b 00001000 : begin
      s <= 8'b 10111111;
    end
    8'b 00001001 : begin
      s <= 8'b 01000000;
    end
    8'b 00001010 : begin
      s <= 8'b 10100011;
    end
    8'b 00001011 : begin
      s <= 8'b 10011110;
    end
    8'b 00001100 : begin
      s <= 8'b 10000001;
    end
    8'b 00001101 : begin
      s <= 8'b 11110011;
    end
    8'b 00001110 : begin
      s <= 8'b 11010111;
    end
    8'b 00001111 : begin
      s <= 8'b 11111011;
    end
    8'b 00010000 : begin
      s <= 8'b 01111100;
    end
    8'b 00010001 : begin
      s <= 8'b 11100011;
    end
    8'b 00010010 : begin
      s <= 8'b 00111001;
    end
    8'b 00010011 : begin
      s <= 8'b 10000010;
    end
    8'b 00010100 : begin
      s <= 8'b 10011011;
    end
    8'b 00010101 : begin
      s <= 8'b 00101111;
    end
    8'b 00010110 : begin
      s <= 8'b 11111111;
    end
    8'b 00010111 : begin
      s <= 8'b 10000111;
    end
    8'b 00011000 : begin
      s <= 8'b 00110100;
    end
    8'b 00011001 : begin
      s <= 8'b 10001110;
    end
    8'b 00011010 : begin
      s <= 8'b 01000011;
    end
    8'b 00011011 : begin
      s <= 8'b 01000100;
    end
    8'b 00011100 : begin
      s <= 8'b 11000100;
    end
    8'b 00011101 : begin
      s <= 8'b 11011110;
    end
    8'b 00011110 : begin
      s <= 8'b 11101001;
    end
    8'b 00011111 : begin
      s <= 8'b 11001011;
    end
    8'b 00100000 : begin
      s <= 8'b 01010100;
    end
    8'b 00100001 : begin
      s <= 8'b 01111011;
    end
    8'b 00100010 : begin
      s <= 8'b 10010100;
    end
    8'b 00100011 : begin
      s <= 8'b 00110010;
    end
    8'b 00100100 : begin
      s <= 8'b 10100110;
    end
    8'b 00100101 : begin
      s <= 8'b 11000010;
    end
    8'b 00100110 : begin
      s <= 8'b 00100011;
    end
    8'b 00100111 : begin
      s <= 8'b 00111101;
    end
    8'b 00101000 : begin
      s <= 8'b 11101110;
    end
    8'b 00101001 : begin
      s <= 8'b 01001100;
    end
    8'b 00101010 : begin
      s <= 8'b 10010101;
    end
    8'b 00101011 : begin
      s <= 8'b 00001011;
    end
    8'b 00101100 : begin
      s <= 8'b 01000010;
    end
    8'b 00101101 : begin
      s <= 8'b 11111010;
    end
    8'b 00101110 : begin
      s <= 8'b 11000011;
    end
    8'b 00101111 : begin
      s <= 8'b 01001110;
    end
    8'b 00110000 : begin
      s <= 8'b 00001000;
    end
    8'b 00110001 : begin
      s <= 8'b 00101110;
    end
    8'b 00110010 : begin
      s <= 8'b 10100001;
    end
    8'b 00110011 : begin
      s <= 8'b 01100110;
    end
    8'b 00110100 : begin
      s <= 8'b 00101000;
    end
    8'b 00110101 : begin
      s <= 8'b 11011001;
    end
    8'b 00110110 : begin
      s <= 8'b 00100100;
    end
    8'b 00110111 : begin
      s <= 8'b 10110010;
    end
    8'b 00111000 : begin
      s <= 8'b 01110110;
    end
    8'b 00111001 : begin
      s <= 8'b 01011011;
    end
    8'b 00111010 : begin
      s <= 8'b 10100010;
    end
    8'b 00111011 : begin
      s <= 8'b 01001001;
    end
    8'b 00111100 : begin
      s <= 8'b 01101101;
    end
    8'b 00111101 : begin
      s <= 8'b 10001011;
    end
    8'b 00111110 : begin
      s <= 8'b 11010001;
    end
    8'b 00111111 : begin
      s <= 8'b 00100101;
    end
    8'b 01000000 : begin
      s <= 8'b 01110010;
    end
    8'b 01000001 : begin
      s <= 8'b 11111000;
    end
    8'b 01000010 : begin
      s <= 8'b 11110110;
    end
    8'b 01000011 : begin
      s <= 8'b 01100100;
    end
    8'b 01000100 : begin
      s <= 8'b 10000110;
    end
    8'b 01000101 : begin
      s <= 8'b 01101000;
    end
    8'b 01000110 : begin
      s <= 8'b 10011000;
    end
    8'b 01000111 : begin
      s <= 8'b 00010110;
    end
    8'b 01001000 : begin
      s <= 8'b 11010100;
    end
    8'b 01001001 : begin
      s <= 8'b 10100100;
    end
    8'b 01001010 : begin
      s <= 8'b 01011100;
    end
    8'b 01001011 : begin
      s <= 8'b 11001100;
    end
    8'b 01001100 : begin
      s <= 8'b 01011101;
    end
    8'b 01001101 : begin
      s <= 8'b 01100101;
    end
    8'b 01001110 : begin
      s <= 8'b 10110110;
    end
    8'b 01001111 : begin
      s <= 8'b 10010010;
    end
    8'b 01010000 : begin
      s <= 8'b 01101100;
    end
    8'b 01010001 : begin
      s <= 8'b 01110000;
    end
    8'b 01010010 : begin
      s <= 8'b 01001000;
    end
    8'b 01010011 : begin
      s <= 8'b 01010000;
    end
    8'b 01010100 : begin
      s <= 8'b 11111101;
    end
    8'b 01010101 : begin
      s <= 8'b 11101101;
    end
    8'b 01010110 : begin
      s <= 8'b 10111001;
    end
    8'b 01010111 : begin
      s <= 8'b 11011010;
    end
    8'b 01011000 : begin
      s <= 8'b 01011110;
    end
    8'b 01011001 : begin
      s <= 8'b 00010101;
    end
    8'b 01011010 : begin
      s <= 8'b 01000110;
    end
    8'b 01011011 : begin
      s <= 8'b 01010111;
    end
    8'b 01011100 : begin
      s <= 8'b 10100111;
    end
    8'b 01011101 : begin
      s <= 8'b 10001101;
    end
    8'b 01011110 : begin
      s <= 8'b 10011101;
    end
    8'b 01011111 : begin
      s <= 8'b 10000100;
    end
    8'b 01100000 : begin
      s <= 8'b 10010000;
    end
    8'b 01100001 : begin
      s <= 8'b 11011000;
    end
    8'b 01100010 : begin
      s <= 8'b 10101011;
    end
    8'b 01100011 : begin
      s <= 8'b 00000000;
    end
    8'b 01100100 : begin
      s <= 8'b 10001100;
    end
    8'b 01100101 : begin
      s <= 8'b 10111100;
    end
    8'b 01100110 : begin
      s <= 8'b 11010011;
    end
    8'b 01100111 : begin
      s <= 8'b 00001010;
    end
    8'b 01101000 : begin
      s <= 8'b 11110111;
    end
    8'b 01101001 : begin
      s <= 8'b 11100100;
    end
    8'b 01101010 : begin
      s <= 8'b 01011000;
    end
    8'b 01101011 : begin
      s <= 8'b 00000101;
    end
    8'b 01101100 : begin
      s <= 8'b 10111000;
    end
    8'b 01101101 : begin
      s <= 8'b 10110011;
    end
    8'b 01101110 : begin
      s <= 8'b 01000101;
    end
    8'b 01101111 : begin
      s <= 8'b 00000110;
    end
    8'b 01110000 : begin
      s <= 8'b 11010000;
    end
    8'b 01110001 : begin
      s <= 8'b 00101100;
    end
    8'b 01110010 : begin
      s <= 8'b 00011110;
    end
    8'b 01110011 : begin
      s <= 8'b 10001111;
    end
    8'b 01110100 : begin
      s <= 8'b 11001010;
    end
    8'b 01110101 : begin
      s <= 8'b 00111111;
    end
    8'b 01110110 : begin
      s <= 8'b 00001111;
    end
    8'b 01110111 : begin
      s <= 8'b 00000010;
    end
    8'b 01111000 : begin
      s <= 8'b 11000001;
    end
    8'b 01111001 : begin
      s <= 8'b 10101111;
    end
    8'b 01111010 : begin
      s <= 8'b 10111101;
    end
    8'b 01111011 : begin
      s <= 8'b 00000011;
    end
    8'b 01111100 : begin
      s <= 8'b 00000001;
    end
    8'b 01111101 : begin
      s <= 8'b 00010011;
    end
    8'b 01111110 : begin
      s <= 8'b 10001010;
    end
    8'b 01111111 : begin
      s <= 8'b 01101011;
    end
    8'b 10000000 : begin
      s <= 8'b 00111010;
    end
    8'b 10000001 : begin
      s <= 8'b 10010001;
    end
    8'b 10000010 : begin
      s <= 8'b 00010001;
    end
    8'b 10000011 : begin
      s <= 8'b 01000001;
    end
    8'b 10000100 : begin
      s <= 8'b 01001111;
    end
    8'b 10000101 : begin
      s <= 8'b 01100111;
    end
    8'b 10000110 : begin
      s <= 8'b 11011100;
    end
    8'b 10000111 : begin
      s <= 8'b 11101010;
    end
    8'b 10001000 : begin
      s <= 8'b 10010111;
    end
    8'b 10001001 : begin
      s <= 8'b 11110010;
    end
    8'b 10001010 : begin
      s <= 8'b 11001111;
    end
    8'b 10001011 : begin
      s <= 8'b 11001110;
    end
    8'b 10001100 : begin
      s <= 8'b 11110000;
    end
    8'b 10001101 : begin
      s <= 8'b 10110100;
    end
    8'b 10001110 : begin
      s <= 8'b 11100110;
    end
    8'b 10001111 : begin
      s <= 8'b 01110011;
    end
    8'b 10010000 : begin
      s <= 8'b 10010110;
    end
    8'b 10010001 : begin
      s <= 8'b 10101100;
    end
    8'b 10010010 : begin
      s <= 8'b 01110100;
    end
    8'b 10010011 : begin
      s <= 8'b 00100010;
    end
    8'b 10010100 : begin
      s <= 8'b 11100111;
    end
    8'b 10010101 : begin
      s <= 8'b 10101101;
    end
    8'b 10010110 : begin
      s <= 8'b 00110101;
    end
    8'b 10010111 : begin
      s <= 8'b 10000101;
    end
    8'b 10011000 : begin
      s <= 8'b 11100010;
    end
    8'b 10011001 : begin
      s <= 8'b 11111001;
    end
    8'b 10011010 : begin
      s <= 8'b 00110111;
    end
    8'b 10011011 : begin
      s <= 8'b 11101000;
    end
    8'b 10011100 : begin
      s <= 8'b 00011100;
    end
    8'b 10011101 : begin
      s <= 8'b 01110101;
    end
    8'b 10011110 : begin
      s <= 8'b 11011111;
    end
    8'b 10011111 : begin
      s <= 8'b 01101110;
    end
    8'b 10100000 : begin
      s <= 8'b 01000111;
    end
    8'b 10100001 : begin
      s <= 8'b 11110001;
    end
    8'b 10100010 : begin
      s <= 8'b 00011010;
    end
    8'b 10100011 : begin
      s <= 8'b 01110001;
    end
    8'b 10100100 : begin
      s <= 8'b 00011101;
    end
    8'b 10100101 : begin
      s <= 8'b 00101001;
    end
    8'b 10100110 : begin
      s <= 8'b 11000101;
    end
    8'b 10100111 : begin
      s <= 8'b 10001001;
    end
    8'b 10101000 : begin
      s <= 8'b 01101111;
    end
    8'b 10101001 : begin
      s <= 8'b 10110111;
    end
    8'b 10101010 : begin
      s <= 8'b 01100010;
    end
    8'b 10101011 : begin
      s <= 8'b 00001110;
    end
    8'b 10101100 : begin
      s <= 8'b 10101010;
    end
    8'b 10101101 : begin
      s <= 8'b 00011000;
    end
    8'b 10101110 : begin
      s <= 8'b 10111110;
    end
    8'b 10101111 : begin
      s <= 8'b 00011011;
    end
    8'b 10110000 : begin
      s <= 8'b 11111100;
    end
    8'b 10110001 : begin
      s <= 8'b 01010110;
    end
    8'b 10110010 : begin
      s <= 8'b 00111110;
    end
    8'b 10110011 : begin
      s <= 8'b 01001011;
    end
    8'b 10110100 : begin
      s <= 8'b 11000110;
    end
    8'b 10110101 : begin
      s <= 8'b 11010010;
    end
    8'b 10110110 : begin
      s <= 8'b 01111001;
    end
    8'b 10110111 : begin
      s <= 8'b 00100000;
    end
    8'b 10111000 : begin
      s <= 8'b 10011010;
    end
    8'b 10111001 : begin
      s <= 8'b 11011011;
    end
    8'b 10111010 : begin
      s <= 8'b 11000000;
    end
    8'b 10111011 : begin
      s <= 8'b 11111110;
    end
    8'b 10111100 : begin
      s <= 8'b 01111000;
    end
    8'b 10111101 : begin
      s <= 8'b 11001101;
    end
    8'b 10111110 : begin
      s <= 8'b 01011010;
    end
    8'b 10111111 : begin
      s <= 8'b 11110100;
    end
    8'b 11000000 : begin
      s <= 8'b 00011111;
    end
    8'b 11000001 : begin
      s <= 8'b 11011101;
    end
    8'b 11000010 : begin
      s <= 8'b 10101000;
    end
    8'b 11000011 : begin
      s <= 8'b 00110011;
    end
    8'b 11000100 : begin
      s <= 8'b 10001000;
    end
    8'b 11000101 : begin
      s <= 8'b 00000111;
    end
    8'b 11000110 : begin
      s <= 8'b 11000111;
    end
    8'b 11000111 : begin
      s <= 8'b 00110001;
    end
    8'b 11001000 : begin
      s <= 8'b 10110001;
    end
    8'b 11001001 : begin
      s <= 8'b 00010010;
    end
    8'b 11001010 : begin
      s <= 8'b 00010000;
    end
    8'b 11001011 : begin
      s <= 8'b 01011001;
    end
    8'b 11001100 : begin
      s <= 8'b 00100111;
    end
    8'b 11001101 : begin
      s <= 8'b 10000000;
    end
    8'b 11001110 : begin
      s <= 8'b 11101100;
    end
    8'b 11001111 : begin
      s <= 8'b 01011111;
    end
    8'b 11010000 : begin
      s <= 8'b 01100000;
    end
    8'b 11010001 : begin
      s <= 8'b 01010001;
    end
    8'b 11010010 : begin
      s <= 8'b 01111111;
    end
    8'b 11010011 : begin
      s <= 8'b 10101001;
    end
    8'b 11010100 : begin
      s <= 8'b 00011001;
    end
    8'b 11010101 : begin
      s <= 8'b 10110101;
    end
    8'b 11010110 : begin
      s <= 8'b 01001010;
    end
    8'b 11010111 : begin
      s <= 8'b 00001101;
    end
    8'b 11011000 : begin
      s <= 8'b 00101101;
    end
    8'b 11011001 : begin
      s <= 8'b 11100101;
    end
    8'b 11011010 : begin
      s <= 8'b 01111010;
    end
    8'b 11011011 : begin
      s <= 8'b 10011111;
    end
    8'b 11011100 : begin
      s <= 8'b 10010011;
    end
    8'b 11011101 : begin
      s <= 8'b 11001001;
    end
    8'b 11011110 : begin
      s <= 8'b 10011100;
    end
    8'b 11011111 : begin
      s <= 8'b 11101111;
    end
    8'b 11100000 : begin
      s <= 8'b 10100000;
    end
    8'b 11100001 : begin
      s <= 8'b 11100000;
    end
    8'b 11100010 : begin
      s <= 8'b 00111011;
    end
    8'b 11100011 : begin
      s <= 8'b 01001101;
    end
    8'b 11100100 : begin
      s <= 8'b 10101110;
    end
    8'b 11100101 : begin
      s <= 8'b 00101010;
    end
    8'b 11100110 : begin
      s <= 8'b 11110101;
    end
    8'b 11100111 : begin
      s <= 8'b 10110000;
    end
    8'b 11101000 : begin
      s <= 8'b 11001000;
    end
    8'b 11101001 : begin
      s <= 8'b 11101011;
    end
    8'b 11101010 : begin
      s <= 8'b 10111011;
    end
    8'b 11101011 : begin
      s <= 8'b 00111100;
    end
    8'b 11101100 : begin
      s <= 8'b 10000011;
    end
    8'b 11101101 : begin
      s <= 8'b 01010011;
    end
    8'b 11101110 : begin
      s <= 8'b 10011001;
    end
    8'b 11101111 : begin
      s <= 8'b 01100001;
    end
    8'b 11110000 : begin
      s <= 8'b 00010111;
    end
    8'b 11110001 : begin
      s <= 8'b 00101011;
    end
    8'b 11110010 : begin
      s <= 8'b 00000100;
    end
    8'b 11110011 : begin
      s <= 8'b 01111110;
    end
    8'b 11110100 : begin
      s <= 8'b 10111010;
    end
    8'b 11110101 : begin
      s <= 8'b 01110111;
    end
    8'b 11110110 : begin
      s <= 8'b 11010110;
    end
    8'b 11110111 : begin
      s <= 8'b 00100110;
    end
    8'b 11111000 : begin
      s <= 8'b 11100001;
    end
    8'b 11111001 : begin
      s <= 8'b 01101001;
    end
    8'b 11111010 : begin
      s <= 8'b 00010100;
    end
    8'b 11111011 : begin
      s <= 8'b 01100011;
    end
    8'b 11111100 : begin
      s <= 8'b 01010101;
    end
    8'b 11111101 : begin
      s <= 8'b 00100001;
    end
    8'b 11111110 : begin
      s <= 8'b 00001100;
    end
    default : begin
      s <= 8'b 01111101;
    end
    endcase
  end


endmodule
