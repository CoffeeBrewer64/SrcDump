/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/
// $Id: dprgf011h.v,v 1.1 2002/05/21 23:55:44 berndt Exp $

// Scalar Unit 2Read/1Write Register File

module dprgf011h(
		  INST_RAL, INST_RALB,
		  INST_RAH, INST_RAHB,
		  INST_RBL, INST_RBLB,
		  INST_RBH, INST_RBHB,
		  INST_WL,  INST_WLB,
		  INST_WH,  INST_WHB,
		  d,
		  a, b
		 );
input  [15:0]  INST_RAL, INST_RALB ;
input  [15:0]  INST_RAH, INST_RAHB ;
input  [15:0]  INST_RBL, INST_RBLB ;
input  [15:0]  INST_RBH, INST_RBHB ;
input  [15:0]  INST_WL,  INST_WLB  ;
input  [15:0]  INST_WH,  INST_WHB  ;
input  [31:0]  d;
output [31:0]  a, b;

/***********************************************************
 * Local signals,mem and variables
 **********************************************************/
reg [31:0] mem[0:31];
reg [31:0] a, b;
reg raError, rbError, wError; 
reg [4:0] ra_addr, rb_addr, w_addr;
reg Wen,WenSoft,WenHard;

reg ErrorEn;
reg Noise;

initial
begin
  ErrorEn = 0;
  raError = 0;
  rbError = 0;
  wError = 0;
  Wen = 0;
  WenSoft = 0;
  WenHard = 0;

  Noise = 0;
end

initial
  begin
   #100 ErrorEn = 1;
  end


/************************************************************
 * Address Encoding and Error detection. 
 ************************************************************/

always @(INST_RAL or INST_RAH or INST_RALB or INST_RAHB)
begin
  raError = 0;
  case ({INST_RAHB,INST_RALB,INST_RAH,INST_RAL})
   64'hffff_fffe_0000_0001: ra_addr = 5'd0; 
   64'hffff_fffd_0000_0002: ra_addr = 5'd1; 
   64'hffff_fffb_0000_0004: ra_addr = 5'd2; 
   64'hffff_fff7_0000_0008: ra_addr = 5'd3; 
   64'hffff_ffef_0000_0010: ra_addr = 5'd4; 
   64'hffff_ffdf_0000_0020: ra_addr = 5'd5; 
   64'hffff_ffbf_0000_0040: ra_addr = 5'd6; 
   64'hffff_ff7f_0000_0080: ra_addr = 5'd7; 
   64'hffff_feff_0000_0100: ra_addr = 5'd8; 
   64'hffff_fdff_0000_0200: ra_addr = 5'd9; 
   64'hffff_fbff_0000_0400: ra_addr = 5'd10; 
   64'hffff_f7ff_0000_0800: ra_addr = 5'd11; 
   64'hffff_efff_0000_1000: ra_addr = 5'd12; 
   64'hffff_dfff_0000_2000: ra_addr = 5'd13; 
   64'hffff_bfff_0000_4000: ra_addr = 5'd14; 
   64'hffff_7fff_0000_8000: ra_addr = 5'd15; 
   64'hfffe_ffff_0001_0000: ra_addr = 5'd16; 
   64'hfffd_ffff_0002_0000: ra_addr = 5'd17; 
   64'hfffb_ffff_0004_0000: ra_addr = 5'd18; 
   64'hfff7_ffff_0008_0000: ra_addr = 5'd19; 
   64'hffef_ffff_0010_0000: ra_addr = 5'd20; 
   64'hffdf_ffff_0020_0000: ra_addr = 5'd21; 
   64'hffbf_ffff_0040_0000: ra_addr = 5'd22; 
   64'hff7f_ffff_0080_0000: ra_addr = 5'd23; 
   64'hfeff_ffff_0100_0000: ra_addr = 5'd24; 
   64'hfdff_ffff_0200_0000: ra_addr = 5'd25; 
   64'hfbff_ffff_0400_0000: ra_addr = 5'd26; 
   64'hf7ff_ffff_0800_0000: ra_addr = 5'd27; 
   64'hefff_ffff_1000_0000: ra_addr = 5'd28; 
   64'hdfff_ffff_2000_0000: ra_addr = 5'd29; 
   64'hbfff_ffff_4000_0000: ra_addr = 5'd30; 
   64'h7fff_ffff_8000_0000: ra_addr = 5'd31; 
   default :	      begin ra_addr = 5'd0; raError = ErrorEn; end
  endcase
end

always @(INST_RBL or INST_RBH or INST_RBLB or INST_RBHB)
begin
  rbError = 0;
  case ({INST_RBHB,INST_RBLB,INST_RBH,INST_RBL})
   64'hffff_fffe_0000_0001: rb_addr = 5'd0; 
   64'hffff_fffd_0000_0002: rb_addr = 5'd1; 
   64'hffff_fffb_0000_0004: rb_addr = 5'd2; 
   64'hffff_fff7_0000_0008: rb_addr = 5'd3; 
   64'hffff_ffef_0000_0010: rb_addr = 5'd4; 
   64'hffff_ffdf_0000_0020: rb_addr = 5'd5; 
   64'hffff_ffbf_0000_0040: rb_addr = 5'd6; 
   64'hffff_ff7f_0000_0080: rb_addr = 5'd7; 
   64'hffff_feff_0000_0100: rb_addr = 5'd8; 
   64'hffff_fdff_0000_0200: rb_addr = 5'd9; 
   64'hffff_fbff_0000_0400: rb_addr = 5'd10; 
   64'hffff_f7ff_0000_0800: rb_addr = 5'd11; 
   64'hffff_efff_0000_1000: rb_addr = 5'd12; 
   64'hffff_dfff_0000_2000: rb_addr = 5'd13; 
   64'hffff_bfff_0000_4000: rb_addr = 5'd14; 
   64'hffff_7fff_0000_8000: rb_addr = 5'd15; 
   64'hfffe_ffff_0001_0000: rb_addr = 5'd16; 
   64'hfffd_ffff_0002_0000: rb_addr = 5'd17; 
   64'hfffb_ffff_0004_0000: rb_addr = 5'd18; 
   64'hfff7_ffff_0008_0000: rb_addr = 5'd19; 
   64'hffef_ffff_0010_0000: rb_addr = 5'd20; 
   64'hffdf_ffff_0020_0000: rb_addr = 5'd21; 
   64'hffbf_ffff_0040_0000: rb_addr = 5'd22; 
   64'hff7f_ffff_0080_0000: rb_addr = 5'd23; 
   64'hfeff_ffff_0100_0000: rb_addr = 5'd24; 
   64'hfdff_ffff_0200_0000: rb_addr = 5'd25; 
   64'hfbff_ffff_0400_0000: rb_addr = 5'd26; 
   64'hf7ff_ffff_0800_0000: rb_addr = 5'd27; 
   64'hefff_ffff_1000_0000: rb_addr = 5'd28; 
   64'hdfff_ffff_2000_0000: rb_addr = 5'd29; 
   64'hbfff_ffff_4000_0000: rb_addr = 5'd30; 
   64'h7fff_ffff_8000_0000: rb_addr = 5'd31; 
   default :	      begin rb_addr = 5'd0; rbError = ErrorEn; end
  endcase
end

always @(INST_WL or INST_WH or INST_WLB or INST_WHB)
begin
  wError = 0;
  case ({INST_WHB,INST_WLB,INST_WH,INST_WL})
   64'hffff_ffff_0000_0000: begin
		   	      w_addr = 5'd0; 
		   	      WenSoft = 0;
		   	      WenHard = 0;
	     		    end
   64'hffff_fffe_0000_0000: begin w_addr = 5'd0;  WenSoft = 1; end
   64'hffff_fffd_0000_0000: begin w_addr = 5'd1;  WenSoft = 1; end
   64'hffff_fffb_0000_0000: begin w_addr = 5'd2;  WenSoft = 1; end
   64'hffff_fff7_0000_0000: begin w_addr = 5'd3;  WenSoft = 1; end
   64'hffff_ffef_0000_0000: begin w_addr = 5'd4;  WenSoft = 1; end
   64'hffff_ffdf_0000_0000: begin w_addr = 5'd5;  WenSoft = 1; end
   64'hffff_ffbf_0000_0000: begin w_addr = 5'd6;  WenSoft = 1; end
   64'hffff_ff7f_0000_0000: begin w_addr = 5'd7;  WenSoft = 1; end
   64'hffff_feff_0000_0000: begin w_addr = 5'd8;  WenSoft = 1; end
   64'hffff_fdff_0000_0000: begin w_addr = 5'd9;  WenSoft = 1; end
   64'hffff_fbff_0000_0000: begin w_addr = 5'd10; WenSoft = 1; end
   64'hffff_f7ff_0000_0000: begin w_addr = 5'd11; WenSoft = 1; end
   64'hffff_efff_0000_0000: begin w_addr = 5'd12; WenSoft = 1; end
   64'hffff_dfff_0000_0000: begin w_addr = 5'd13; WenSoft = 1; end
   64'hffff_bfff_0000_0000: begin w_addr = 5'd14; WenSoft = 1; end
   64'hffff_7fff_0000_0000: begin w_addr = 5'd15; WenSoft = 1; end
   64'hfffe_ffff_0000_0000: begin w_addr = 5'd16; WenSoft = 1; end
   64'hfffd_ffff_0000_0000: begin w_addr = 5'd17; WenSoft = 1; end
   64'hfffb_ffff_0000_0000: begin w_addr = 5'd18; WenSoft = 1; end
   64'hfff7_ffff_0000_0000: begin w_addr = 5'd19; WenSoft = 1; end
   64'hffef_ffff_0000_0000: begin w_addr = 5'd20; WenSoft = 1; end
   64'hffdf_ffff_0000_0000: begin w_addr = 5'd21; WenSoft = 1; end
   64'hffbf_ffff_0000_0000: begin w_addr = 5'd22; WenSoft = 1; end
   64'hff7f_ffff_0000_0000: begin w_addr = 5'd23; WenSoft = 1; end
   64'hfeff_ffff_0000_0000: begin w_addr = 5'd24; WenSoft = 1; end
   64'hfdff_ffff_0000_0000: begin w_addr = 5'd25; WenSoft = 1; end
   64'hfbff_ffff_0000_0000: begin w_addr = 5'd26; WenSoft = 1; end
   64'hf7ff_ffff_0000_0000: begin w_addr = 5'd27; WenSoft = 1; end
   64'hefff_ffff_0000_0000: begin w_addr = 5'd28; WenSoft = 1; end
   64'hdfff_ffff_0000_0000: begin w_addr = 5'd29; WenSoft = 1; end
   64'hbfff_ffff_0000_0000: begin w_addr = 5'd30; WenSoft = 1; end
   64'h7fff_ffff_0000_0000: begin w_addr = 5'd31; WenSoft = 1; end

   64'hffff_ffff_0000_0001: begin w_addr = 5'd0;  WenSoft = 1; end
   64'hffff_ffff_0000_0002: begin w_addr = 5'd1;  WenSoft = 1; end
   64'hffff_ffff_0000_0004: begin w_addr = 5'd2;  WenSoft = 1; end
   64'hffff_ffff_0000_0008: begin w_addr = 5'd3;  WenSoft = 1; end
   64'hffff_ffff_0000_0010: begin w_addr = 5'd4;  WenSoft = 1; end
   64'hffff_ffff_0000_0020: begin w_addr = 5'd5;  WenSoft = 1; end
   64'hffff_ffff_0000_0040: begin w_addr = 5'd6;  WenSoft = 1; end
   64'hffff_ffff_0000_0080: begin w_addr = 5'd7;  WenSoft = 1; end
   64'hffff_ffff_0000_0100: begin w_addr = 5'd8;  WenSoft = 1; end
   64'hffff_ffff_0000_0200: begin w_addr = 5'd9;  WenSoft = 1; end
   64'hffff_ffff_0000_0400: begin w_addr = 5'd10; WenSoft = 1; end
   64'hffff_ffff_0000_0800: begin w_addr = 5'd11; WenSoft = 1; end
   64'hffff_ffff_0000_1000: begin w_addr = 5'd12; WenSoft = 1; end
   64'hffff_ffff_0000_2000: begin w_addr = 5'd13; WenSoft = 1; end
   64'hffff_ffff_0000_4000: begin w_addr = 5'd14; WenSoft = 1; end
   64'hffff_ffff_0000_8000: begin w_addr = 5'd15; WenSoft = 1; end
   64'hffff_ffff_0001_0000: begin w_addr = 5'd16; WenSoft = 1; end
   64'hffff_ffff_0002_0000: begin w_addr = 5'd17; WenSoft = 1; end
   64'hffff_ffff_0004_0000: begin w_addr = 5'd18; WenSoft = 1; end
   64'hffff_ffff_0008_0000: begin w_addr = 5'd19; WenSoft = 1; end
   64'hffff_ffff_0010_0000: begin w_addr = 5'd20; WenSoft = 1; end
   64'hffff_ffff_0020_0000: begin w_addr = 5'd21; WenSoft = 1; end
   64'hffff_ffff_0040_0000: begin w_addr = 5'd22; WenSoft = 1; end
   64'hffff_ffff_0080_0000: begin w_addr = 5'd23; WenSoft = 1; end
   64'hffff_ffff_0100_0000: begin w_addr = 5'd24; WenSoft = 1; end
   64'hffff_ffff_0200_0000: begin w_addr = 5'd25; WenSoft = 1; end
   64'hffff_ffff_0400_0000: begin w_addr = 5'd26; WenSoft = 1; end
   64'hffff_ffff_0800_0000: begin w_addr = 5'd27; WenSoft = 1; end
   64'hffff_ffff_1000_0000: begin w_addr = 5'd28; WenSoft = 1; end
   64'hffff_ffff_2000_0000: begin w_addr = 5'd29; WenSoft = 1; end
   64'hffff_ffff_4000_0000: begin w_addr = 5'd30; WenSoft = 1; end
   64'hffff_ffff_8000_0000: begin w_addr = 5'd31; WenSoft = 1; end

   64'hffff_fffe_0000_0001: begin w_addr = 5'd0;  WenHard = 1; end
   64'hffff_fffd_0000_0002: begin w_addr = 5'd1;  WenHard = 1; end
   64'hffff_fffb_0000_0004: begin w_addr = 5'd2;  WenHard = 1; end
   64'hffff_fff7_0000_0008: begin w_addr = 5'd3;  WenHard = 1; end
   64'hffff_ffef_0000_0010: begin w_addr = 5'd4;  WenHard = 1; end
   64'hffff_ffdf_0000_0020: begin w_addr = 5'd5;  WenHard = 1; end
   64'hffff_ffbf_0000_0040: begin w_addr = 5'd6;  WenHard = 1; end
   64'hffff_ff7f_0000_0080: begin w_addr = 5'd7;  WenHard = 1; end
   64'hffff_feff_0000_0100: begin w_addr = 5'd8;  WenHard = 1; end
   64'hffff_fdff_0000_0200: begin w_addr = 5'd9;  WenHard = 1; end
   64'hffff_fbff_0000_0400: begin w_addr = 5'd10; WenHard = 1; end
   64'hffff_f7ff_0000_0800: begin w_addr = 5'd11; WenHard = 1; end
   64'hffff_efff_0000_1000: begin w_addr = 5'd12; WenHard = 1; end
   64'hffff_dfff_0000_2000: begin w_addr = 5'd13; WenHard = 1; end
   64'hffff_bfff_0000_4000: begin w_addr = 5'd14; WenHard = 1; end
   64'hffff_7fff_0000_8000: begin w_addr = 5'd15; WenHard = 1; end
   64'hfffe_ffff_0001_0000: begin w_addr = 5'd16; WenHard = 1; end
   64'hfffd_ffff_0002_0000: begin w_addr = 5'd17; WenHard = 1; end
   64'hfffb_ffff_0004_0000: begin w_addr = 5'd18; WenHard = 1; end
   64'hfff7_ffff_0008_0000: begin w_addr = 5'd19; WenHard = 1; end
   64'hffef_ffff_0010_0000: begin w_addr = 5'd20; WenHard = 1; end
   64'hffdf_ffff_0020_0000: begin w_addr = 5'd21; WenHard = 1; end
   64'hffbf_ffff_0040_0000: begin w_addr = 5'd22; WenHard = 1; end
   64'hff7f_ffff_0080_0000: begin w_addr = 5'd23; WenHard = 1; end
   64'hfeff_ffff_0100_0000: begin w_addr = 5'd24; WenHard = 1; end
   64'hfdff_ffff_0200_0000: begin w_addr = 5'd25; WenHard = 1; end
   64'hfbff_ffff_0400_0000: begin w_addr = 5'd26; WenHard = 1; end
   64'hf7ff_ffff_0800_0000: begin w_addr = 5'd27; WenHard = 1; end
   64'hefff_ffff_1000_0000: begin w_addr = 5'd28; WenHard = 1; end
   64'hdfff_ffff_2000_0000: begin w_addr = 5'd29; WenHard = 1; end
   64'hbfff_ffff_4000_0000: begin w_addr = 5'd30; WenHard = 1; end
   64'h7fff_ffff_8000_0000: begin w_addr = 5'd31; WenHard = 1; end
   default : begin 
		   w_addr = 5'd0; 
		   WenSoft = 0;
		   WenHard = 0;
		   wError = ErrorEn; 
	     end
  endcase

  Wen = WenSoft | WenHard;
end

/**************************************************************
 * Write Port
 **************************************************************/

always @(w_addr or d or Wen or WenHard or wError)
  if (wError)
     $display($time,"  ERROR: Write Address Error for 2R/1W regfile"); 
  else
  if (Wen && !WenHard)
      mem[w_addr] = 32'hx;
  else
  if (Wen && WenHard)
      mem[w_addr] = d;

/**************************************************************
 * Read Port:A
 **************************************************************/
always @(ra_addr or raError or w_addr or Wen or d or Noise)
  if (raError)
     a[31:0] = 32'hx;
  else
     a[31:0] = mem[ra_addr];

/**************************************************************
 * Read Port:B
 **************************************************************/
always @(rb_addr or rbError or w_addr or Wen or d or Noise)
  if (rbError)
     b[31:0] = 32'hx;
  else
     b[31:0] = mem[rb_addr];
endmodule

