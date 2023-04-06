/*
*************************************************************************
*									*
*               Copyright (C) 1994, Silicon Graphics, Inc.		*
*									*
*  These coded instructions, statements, and computer programs  contain	*
*  unpublished  proprietary  information of Silicon Graphics, Inc., and	*
*  are protected by Federal copyright  law.  They  may not be disclosed	*
*  to  third  parties  or copied or duplicated in any form, in whole or	*
*  in part, without the prior written consent of Silicon Graphics, Inc.	*
*									*
*************************************************************************
*/

// $Id: dprgf020h.v,v 1.1 2002/05/21 23:55:45 berndt Exp $

module dprgf020h (
                  INST_RAL, INST_RALB,
                  INST_RAH, INST_RAHB,
                  INST_RBL, INST_RBLB,
                  INST_RBH, INST_RBHB,
                  INST_RCL, INST_RCLB,
                  INST_RCH, INST_RCHB,
                  INST_W0L,  INST_W0LB,
                  INST_W0H,  INST_W0HB,
                  INST_W1LX,  INST_W1LXB,
                  INST_W1HX,  INST_W1HXB,
                  INST_W1LY,  INST_W1LYB,
                  INST_W1HY,  INST_W1HYB,
                  d0,d1,
                  a, b, c
                 );
input  [15:0]  INST_RAL, INST_RALB ;
input  [15:0]  INST_RAH, INST_RAHB ;
input  [15:0]  INST_RBL, INST_RBLB ;
input  [15:0]  INST_RBH, INST_RBHB ;
input  [15:0]  INST_RCL, INST_RCLB ;
input  [15:0]  INST_RCH, INST_RCHB ;

input  [15:0]  INST_W0L,  INST_W0LB  ;
input  [15:0]  INST_W0H,  INST_W0HB  ;
input  [15:0]  INST_W1LX,  INST_W1LXB  ;
input  [15:0]  INST_W1HX,  INST_W1HXB  ;
input  [15:0]  INST_W1LY,  INST_W1LYB  ;
input  [15:0]  INST_W1HY,  INST_W1HYB  ;

input  [15:0]  d0, d1;
output [15:0]  a, b, c;

/***********************************************************
 * Local signals,mem and variables
 **********************************************************/
reg [15:0] mem[0:31];
reg [15:0] a, b, c;

reg [4:0] ra_addr, rb_addr, rc_addr, wo_addr, wix_addr, wiy_addr;
reg WOen,     WIXen,     WIYen;
reg WOenHard, WIXenHard, WIYenHard;
reg WOenSoft, WIXenSoft, WIYenSoft;

reg raError, rbError, rcError, woError,wixError,wiyError; 
reg WrConflict;
reg rawConflict, rbwConflict, rcwConflict;

reg ErrorEn;

reg Report_Error;

reg Noise;

initial 
  begin
   WrConflict = 0;
   ErrorEn = 0;

   Noise = 0;

   WOen=0;     WIXen=0;     WIYen=0;
   WOenHard=0; WIXenHard=0; WIYenHard=0;
   WOenSoft=0; WIXenSoft=0; WIYenSoft=0;

   raError=0; rbError=0; rcError=0; woError=0;wixError=0; wiyError=0; 
   WrConflict=0;
   rawConflict=0; rbwConflict=0; rcwConflict=0;

   Report_Error = 0;
  end

initial 
  begin
   #200 ErrorEn = 1;
  end

/************************************************************
 * Address Encoding and Error detection. 
 ************************************************************/
//
// Read Port A address encode and illigal address detect.
//
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
   default : begin
              ra_addr = 5'd0;
              raError = ErrorEn;
             end
  endcase
end
//
// Read Port B address encode and illigal address detect.
//
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
   default : begin
              rb_addr = 5'd0;
              rbError = ErrorEn;
             end
  endcase
end
//
// Read Port C address encode and illigal address detect.
//
always @(INST_RCL or INST_RCH or INST_RCLB or INST_RCHB)
begin
  rcError = 0;
  case ({INST_RCHB,INST_RCLB,INST_RCH,INST_RCL})
   64'hffff_fffe_0000_0001: rc_addr = 5'd0; 
   64'hffff_fffd_0000_0002: rc_addr = 5'd1; 
   64'hffff_fffb_0000_0004: rc_addr = 5'd2; 
   64'hffff_fff7_0000_0008: rc_addr = 5'd3; 
   64'hffff_ffef_0000_0010: rc_addr = 5'd4; 
   64'hffff_ffdf_0000_0020: rc_addr = 5'd5; 
   64'hffff_ffbf_0000_0040: rc_addr = 5'd6; 
   64'hffff_ff7f_0000_0080: rc_addr = 5'd7; 
   64'hffff_feff_0000_0100: rc_addr = 5'd8; 
   64'hffff_fdff_0000_0200: rc_addr = 5'd9; 
   64'hffff_fbff_0000_0400: rc_addr = 5'd10; 
   64'hffff_f7ff_0000_0800: rc_addr = 5'd11; 
   64'hffff_efff_0000_1000: rc_addr = 5'd12; 
   64'hffff_dfff_0000_2000: rc_addr = 5'd13; 
   64'hffff_bfff_0000_4000: rc_addr = 5'd14; 
   64'hffff_7fff_0000_8000: rc_addr = 5'd15; 
   64'hfffe_ffff_0001_0000: rc_addr = 5'd16; 
   64'hfffd_ffff_0002_0000: rc_addr = 5'd17; 
   64'hfffb_ffff_0004_0000: rc_addr = 5'd18; 
   64'hfff7_ffff_0008_0000: rc_addr = 5'd19; 
   64'hffef_ffff_0010_0000: rc_addr = 5'd20; 
   64'hffdf_ffff_0020_0000: rc_addr = 5'd21; 
   64'hffbf_ffff_0040_0000: rc_addr = 5'd22; 
   64'hff7f_ffff_0080_0000: rc_addr = 5'd23; 
   64'hfeff_ffff_0100_0000: rc_addr = 5'd24; 
   64'hfdff_ffff_0200_0000: rc_addr = 5'd25; 
   64'hfbff_ffff_0400_0000: rc_addr = 5'd26; 
   64'hf7ff_ffff_0800_0000: rc_addr = 5'd27; 
   64'hefff_ffff_1000_0000: rc_addr = 5'd28; 
   64'hdfff_ffff_2000_0000: rc_addr = 5'd29; 
   64'hbfff_ffff_4000_0000: rc_addr = 5'd30; 
   64'h7fff_ffff_8000_0000: rc_addr = 5'd31; 
   default : begin
              rc_addr = 5'd0;
              rcError = ErrorEn;
             end
  endcase
end
//
// Write Port O address encode and illigal address detect.
//
always @(INST_W0L or INST_W0H or INST_W0LB or INST_W0HB)
begin

  woError = 0;

  case ({INST_W0HB,INST_W0LB,INST_W0H,INST_W0L})
   64'hffff_ffff_0000_0000: begin wo_addr = 5'd0;  WOenHard = 0; 
						   WOenSoft = 0; end 

   64'hffff_fffe_0000_0000: begin wo_addr = 5'd0;  WOenSoft = 1; end
   64'hffff_fffd_0000_0000: begin wo_addr = 5'd1;  WOenSoft = 1; end
   64'hffff_fffb_0000_0000: begin wo_addr = 5'd2;  WOenSoft = 1; end
   64'hffff_fff7_0000_0000: begin wo_addr = 5'd3;  WOenSoft = 1; end
   64'hffff_ffef_0000_0000: begin wo_addr = 5'd4;  WOenSoft = 1; end
   64'hffff_ffdf_0000_0000: begin wo_addr = 5'd5;  WOenSoft = 1; end
   64'hffff_ffbf_0000_0000: begin wo_addr = 5'd6;  WOenSoft = 1; end
   64'hffff_ff7f_0000_0000: begin wo_addr = 5'd7;  WOenSoft = 1; end
   64'hffff_feff_0000_0000: begin wo_addr = 5'd8;  WOenSoft = 1; end
   64'hffff_fdff_0000_0000: begin wo_addr = 5'd9;  WOenSoft = 1; end
   64'hffff_fbff_0000_0000: begin wo_addr = 5'd10; WOenSoft = 1; end
   64'hffff_f7ff_0000_0000: begin wo_addr = 5'd11; WOenSoft = 1; end
   64'hffff_efff_0000_0000: begin wo_addr = 5'd12; WOenSoft = 1; end
   64'hffff_dfff_0000_0000: begin wo_addr = 5'd13; WOenSoft = 1; end
   64'hffff_bfff_0000_0000: begin wo_addr = 5'd14; WOenSoft = 1; end
   64'hffff_7fff_0000_0000: begin wo_addr = 5'd15; WOenSoft = 1; end
   64'hfffe_ffff_0000_0000: begin wo_addr = 5'd16; WOenSoft = 1; end
   64'hfffd_ffff_0000_0000: begin wo_addr = 5'd17; WOenSoft = 1; end
   64'hfffb_ffff_0000_0000: begin wo_addr = 5'd18; WOenSoft = 1; end
   64'hfff7_ffff_0000_0000: begin wo_addr = 5'd19; WOenSoft = 1; end
   64'hffef_ffff_0000_0000: begin wo_addr = 5'd20; WOenSoft = 1; end
   64'hffdf_ffff_0000_0000: begin wo_addr = 5'd21; WOenSoft = 1; end
   64'hffbf_ffff_0000_0000: begin wo_addr = 5'd22; WOenSoft = 1; end
   64'hff7f_ffff_0000_0000: begin wo_addr = 5'd23; WOenSoft = 1; end
   64'hfeff_ffff_0000_0000: begin wo_addr = 5'd24; WOenSoft = 1; end
   64'hfdff_ffff_0000_0000: begin wo_addr = 5'd25; WOenSoft = 1; end
   64'hfbff_ffff_0000_0000: begin wo_addr = 5'd26; WOenSoft = 1; end
   64'hf7ff_ffff_0000_0000: begin wo_addr = 5'd27; WOenSoft = 1; end
   64'hefff_ffff_0000_0000: begin wo_addr = 5'd28; WOenSoft = 1; end
   64'hdfff_ffff_0000_0000: begin wo_addr = 5'd29; WOenSoft = 1; end
   64'hbfff_ffff_0000_0000: begin wo_addr = 5'd30; WOenSoft = 1; end
   64'h7fff_ffff_0000_0000: begin wo_addr = 5'd31; WOenSoft = 1; end

   64'hffff_ffff_0000_0001: begin wo_addr = 5'd0;  WOenSoft = 1; end
   64'hffff_ffff_0000_0002: begin wo_addr = 5'd1;  WOenSoft = 1; end
   64'hffff_ffff_0000_0004: begin wo_addr = 5'd2;  WOenSoft = 1; end
   64'hffff_ffff_0000_0008: begin wo_addr = 5'd3;  WOenSoft = 1; end
   64'hffff_ffff_0000_0010: begin wo_addr = 5'd4;  WOenSoft = 1; end
   64'hffff_ffff_0000_0020: begin wo_addr = 5'd5;  WOenSoft = 1; end
   64'hffff_ffff_0000_0040: begin wo_addr = 5'd6;  WOenSoft = 1; end
   64'hffff_ffff_0000_0080: begin wo_addr = 5'd7;  WOenSoft = 1; end
   64'hffff_ffff_0000_0100: begin wo_addr = 5'd8;  WOenSoft = 1; end
   64'hffff_ffff_0000_0200: begin wo_addr = 5'd9;  WOenSoft = 1; end
   64'hffff_ffff_0000_0400: begin wo_addr = 5'd10; WOenSoft = 1; end
   64'hffff_ffff_0000_0800: begin wo_addr = 5'd11; WOenSoft = 1; end
   64'hffff_ffff_0000_1000: begin wo_addr = 5'd12; WOenSoft = 1; end
   64'hffff_ffff_0000_2000: begin wo_addr = 5'd13; WOenSoft = 1; end
   64'hffff_ffff_0000_4000: begin wo_addr = 5'd14; WOenSoft = 1; end
   64'hffff_ffff_0000_8000: begin wo_addr = 5'd15; WOenSoft = 1; end
   64'hffff_ffff_0001_0000: begin wo_addr = 5'd16; WOenSoft = 1; end
   64'hffff_ffff_0002_0000: begin wo_addr = 5'd17; WOenSoft = 1; end
   64'hffff_ffff_0004_0000: begin wo_addr = 5'd18; WOenSoft = 1; end
   64'hffff_ffff_0008_0000: begin wo_addr = 5'd19; WOenSoft = 1; end
   64'hffff_ffff_0010_0000: begin wo_addr = 5'd20; WOenSoft = 1; end
   64'hffff_ffff_0020_0000: begin wo_addr = 5'd21; WOenSoft = 1; end
   64'hffff_ffff_0040_0000: begin wo_addr = 5'd22; WOenSoft = 1; end
   64'hffff_ffff_0080_0000: begin wo_addr = 5'd23; WOenSoft = 1; end
   64'hffff_ffff_0100_0000: begin wo_addr = 5'd24; WOenSoft = 1; end
   64'hffff_ffff_0200_0000: begin wo_addr = 5'd25; WOenSoft = 1; end
   64'hffff_ffff_0400_0000: begin wo_addr = 5'd26; WOenSoft = 1; end
   64'hffff_ffff_0800_0000: begin wo_addr = 5'd27; WOenSoft = 1; end
   64'hffff_ffff_1000_0000: begin wo_addr = 5'd28; WOenSoft = 1; end
   64'hffff_ffff_2000_0000: begin wo_addr = 5'd29; WOenSoft = 1; end
   64'hffff_ffff_4000_0000: begin wo_addr = 5'd30; WOenSoft = 1; end
   64'hffff_ffff_8000_0000: begin wo_addr = 5'd31; WOenSoft = 1; end

   64'hffff_fffe_0000_0001: begin wo_addr = 5'd0;  WOenHard = 1; end
   64'hffff_fffd_0000_0002: begin wo_addr = 5'd1;  WOenHard = 1; end
   64'hffff_fffb_0000_0004: begin wo_addr = 5'd2;  WOenHard = 1; end
   64'hffff_fff7_0000_0008: begin wo_addr = 5'd3;  WOenHard = 1; end
   64'hffff_ffef_0000_0010: begin wo_addr = 5'd4;  WOenHard = 1; end
   64'hffff_ffdf_0000_0020: begin wo_addr = 5'd5;  WOenHard = 1; end
   64'hffff_ffbf_0000_0040: begin wo_addr = 5'd6;  WOenHard = 1; end
   64'hffff_ff7f_0000_0080: begin wo_addr = 5'd7;  WOenHard = 1; end
   64'hffff_feff_0000_0100: begin wo_addr = 5'd8;  WOenHard = 1; end
   64'hffff_fdff_0000_0200: begin wo_addr = 5'd9;  WOenHard = 1; end
   64'hffff_fbff_0000_0400: begin wo_addr = 5'd10; WOenHard = 1; end
   64'hffff_f7ff_0000_0800: begin wo_addr = 5'd11; WOenHard = 1; end
   64'hffff_efff_0000_1000: begin wo_addr = 5'd12; WOenHard = 1; end
   64'hffff_dfff_0000_2000: begin wo_addr = 5'd13; WOenHard = 1; end
   64'hffff_bfff_0000_4000: begin wo_addr = 5'd14; WOenHard = 1; end
   64'hffff_7fff_0000_8000: begin wo_addr = 5'd15; WOenHard = 1; end
   64'hfffe_ffff_0001_0000: begin wo_addr = 5'd16; WOenHard = 1; end
   64'hfffd_ffff_0002_0000: begin wo_addr = 5'd17; WOenHard = 1; end
   64'hfffb_ffff_0004_0000: begin wo_addr = 5'd18; WOenHard = 1; end
   64'hfff7_ffff_0008_0000: begin wo_addr = 5'd19; WOenHard = 1; end
   64'hffef_ffff_0010_0000: begin wo_addr = 5'd20; WOenHard = 1; end
   64'hffdf_ffff_0020_0000: begin wo_addr = 5'd21; WOenHard = 1; end
   64'hffbf_ffff_0040_0000: begin wo_addr = 5'd22; WOenHard = 1; end
   64'hff7f_ffff_0080_0000: begin wo_addr = 5'd23; WOenHard = 1; end
   64'hfeff_ffff_0100_0000: begin wo_addr = 5'd24; WOenHard = 1; end
   64'hfdff_ffff_0200_0000: begin wo_addr = 5'd25; WOenHard = 1; end
   64'hfbff_ffff_0400_0000: begin wo_addr = 5'd26; WOenHard = 1; end
   64'hf7ff_ffff_0800_0000: begin wo_addr = 5'd27; WOenHard = 1; end
   64'hefff_ffff_1000_0000: begin wo_addr = 5'd28; WOenHard = 1; end
   64'hdfff_ffff_2000_0000: begin wo_addr = 5'd29; WOenHard = 1; end
   64'hbfff_ffff_4000_0000: begin wo_addr = 5'd30; WOenHard = 1; end
   64'h7fff_ffff_8000_0000: begin wo_addr = 5'd31; WOenHard = 1; end
   default : begin
              wo_addr = 5'd0; WOenHard = 0; WOenSoft = 0;
              woError = ErrorEn;
             end
  endcase

  WOen = WOenHard | WOenSoft;

  //$display($time," WO = %b_%b_%b_%b, DO=%h",INST_W0HB,INST_W0LB,INST_W0H,INST_W0L,d0);
end
//
// Write Port IX address encode and illigal address detect.
//
always @(INST_W1LX or INST_W1HX or INST_W1LXB or INST_W1HXB)
begin

  wixError = 0;

  case ({INST_W1HXB,INST_W1LXB,INST_W1HX,INST_W1LX})
   64'hffff_ffff_0000_0000: begin wix_addr = 5'd0;  WIXenHard = 0; 
						    WIXenSoft = 0; end 

   64'hffff_fffe_0000_0000: begin wix_addr = 5'd0;  WIXenSoft = 1; end
   64'hffff_fffd_0000_0000: begin wix_addr = 5'd1;  WIXenSoft = 1; end
   64'hffff_fffb_0000_0000: begin wix_addr = 5'd2;  WIXenSoft = 1; end
   64'hffff_fff7_0000_0000: begin wix_addr = 5'd3;  WIXenSoft = 1; end
   64'hffff_ffef_0000_0000: begin wix_addr = 5'd4;  WIXenSoft = 1; end
   64'hffff_ffdf_0000_0000: begin wix_addr = 5'd5;  WIXenSoft = 1; end
   64'hffff_ffbf_0000_0000: begin wix_addr = 5'd6;  WIXenSoft = 1; end
   64'hffff_ff7f_0000_0000: begin wix_addr = 5'd7;  WIXenSoft = 1; end
   64'hffff_feff_0000_0000: begin wix_addr = 5'd8;  WIXenSoft = 1; end
   64'hffff_fdff_0000_0000: begin wix_addr = 5'd9;  WIXenSoft = 1; end
   64'hffff_fbff_0000_0000: begin wix_addr = 5'd10; WIXenSoft = 1; end
   64'hffff_f7ff_0000_0000: begin wix_addr = 5'd11; WIXenSoft = 1; end
   64'hffff_efff_0000_0000: begin wix_addr = 5'd12; WIXenSoft = 1; end
   64'hffff_dfff_0000_0000: begin wix_addr = 5'd13; WIXenSoft = 1; end
   64'hffff_bfff_0000_0000: begin wix_addr = 5'd14; WIXenSoft = 1; end
   64'hffff_7fff_0000_0000: begin wix_addr = 5'd15; WIXenSoft = 1; end
   64'hfffe_ffff_0000_0000: begin wix_addr = 5'd16; WIXenSoft = 1; end
   64'hfffd_ffff_0000_0000: begin wix_addr = 5'd17; WIXenSoft = 1; end
   64'hfffb_ffff_0000_0000: begin wix_addr = 5'd18; WIXenSoft = 1; end
   64'hfff7_ffff_0000_0000: begin wix_addr = 5'd19; WIXenSoft = 1; end
   64'hffef_ffff_0000_0000: begin wix_addr = 5'd20; WIXenSoft = 1; end
   64'hffdf_ffff_0000_0000: begin wix_addr = 5'd21; WIXenSoft = 1; end
   64'hffbf_ffff_0000_0000: begin wix_addr = 5'd22; WIXenSoft = 1; end
   64'hff7f_ffff_0000_0000: begin wix_addr = 5'd23; WIXenSoft = 1; end
   64'hfeff_ffff_0000_0000: begin wix_addr = 5'd24; WIXenSoft = 1; end
   64'hfdff_ffff_0000_0000: begin wix_addr = 5'd25; WIXenSoft = 1; end
   64'hfbff_ffff_0000_0000: begin wix_addr = 5'd26; WIXenSoft = 1; end
   64'hf7ff_ffff_0000_0000: begin wix_addr = 5'd27; WIXenSoft = 1; end
   64'hefff_ffff_0000_0000: begin wix_addr = 5'd28; WIXenSoft = 1; end
   64'hdfff_ffff_0000_0000: begin wix_addr = 5'd29; WIXenSoft = 1; end
   64'hbfff_ffff_0000_0000: begin wix_addr = 5'd30; WIXenSoft = 1; end
   64'h7fff_ffff_0000_0000: begin wix_addr = 5'd31; WIXenSoft = 1; end

   64'hffff_ffff_0000_0001: begin wix_addr = 5'd0;  WIXenSoft = 1; end
   64'hffff_ffff_0000_0002: begin wix_addr = 5'd1;  WIXenSoft = 1; end
   64'hffff_ffff_0000_0004: begin wix_addr = 5'd2;  WIXenSoft = 1; end
   64'hffff_ffff_0000_0008: begin wix_addr = 5'd3;  WIXenSoft = 1; end
   64'hffff_ffff_0000_0010: begin wix_addr = 5'd4;  WIXenSoft = 1; end
   64'hffff_ffff_0000_0020: begin wix_addr = 5'd5;  WIXenSoft = 1; end
   64'hffff_ffff_0000_0040: begin wix_addr = 5'd6;  WIXenSoft = 1; end
   64'hffff_ffff_0000_0080: begin wix_addr = 5'd7;  WIXenSoft = 1; end
   64'hffff_ffff_0000_0100: begin wix_addr = 5'd8;  WIXenSoft = 1; end
   64'hffff_ffff_0000_0200: begin wix_addr = 5'd9;  WIXenSoft = 1; end
   64'hffff_ffff_0000_0400: begin wix_addr = 5'd10; WIXenSoft = 1; end
   64'hffff_ffff_0000_0800: begin wix_addr = 5'd11; WIXenSoft = 1; end
   64'hffff_ffff_0000_1000: begin wix_addr = 5'd12; WIXenSoft = 1; end
   64'hffff_ffff_0000_2000: begin wix_addr = 5'd13; WIXenSoft = 1; end
   64'hffff_ffff_0000_4000: begin wix_addr = 5'd14; WIXenSoft = 1; end
   64'hffff_ffff_0000_8000: begin wix_addr = 5'd15; WIXenSoft = 1; end
   64'hffff_ffff_0001_0000: begin wix_addr = 5'd16; WIXenSoft = 1; end
   64'hffff_ffff_0002_0000: begin wix_addr = 5'd17; WIXenSoft = 1; end
   64'hffff_ffff_0004_0000: begin wix_addr = 5'd18; WIXenSoft = 1; end
   64'hffff_ffff_0008_0000: begin wix_addr = 5'd19; WIXenSoft = 1; end
   64'hffff_ffff_0010_0000: begin wix_addr = 5'd20; WIXenSoft = 1; end
   64'hffff_ffff_0020_0000: begin wix_addr = 5'd21; WIXenSoft = 1; end
   64'hffff_ffff_0040_0000: begin wix_addr = 5'd22; WIXenSoft = 1; end
   64'hffff_ffff_0080_0000: begin wix_addr = 5'd23; WIXenSoft = 1; end
   64'hffff_ffff_0100_0000: begin wix_addr = 5'd24; WIXenSoft = 1; end
   64'hffff_ffff_0200_0000: begin wix_addr = 5'd25; WIXenSoft = 1; end
   64'hffff_ffff_0400_0000: begin wix_addr = 5'd26; WIXenSoft = 1; end
   64'hffff_ffff_0800_0000: begin wix_addr = 5'd27; WIXenSoft = 1; end
   64'hffff_ffff_1000_0000: begin wix_addr = 5'd28; WIXenSoft = 1; end
   64'hffff_ffff_2000_0000: begin wix_addr = 5'd29; WIXenSoft = 1; end
   64'hffff_ffff_4000_0000: begin wix_addr = 5'd30; WIXenSoft = 1; end
   64'hffff_ffff_8000_0000: begin wix_addr = 5'd31; WIXenSoft = 1; end

   64'hffff_fffe_0000_0001: begin wix_addr = 5'd0;  WIXenHard = 1; end
   64'hffff_fffd_0000_0002: begin wix_addr = 5'd1;  WIXenHard = 1; end
   64'hffff_fffb_0000_0004: begin wix_addr = 5'd2;  WIXenHard = 1; end
   64'hffff_fff7_0000_0008: begin wix_addr = 5'd3;  WIXenHard = 1; end
   64'hffff_ffef_0000_0010: begin wix_addr = 5'd4;  WIXenHard = 1; end
   64'hffff_ffdf_0000_0020: begin wix_addr = 5'd5;  WIXenHard = 1; end
   64'hffff_ffbf_0000_0040: begin wix_addr = 5'd6;  WIXenHard = 1; end
   64'hffff_ff7f_0000_0080: begin wix_addr = 5'd7;  WIXenHard = 1; end
   64'hffff_feff_0000_0100: begin wix_addr = 5'd8;  WIXenHard = 1; end
   64'hffff_fdff_0000_0200: begin wix_addr = 5'd9;  WIXenHard = 1; end
   64'hffff_fbff_0000_0400: begin wix_addr = 5'd10; WIXenHard = 1; end
   64'hffff_f7ff_0000_0800: begin wix_addr = 5'd11; WIXenHard = 1; end
   64'hffff_efff_0000_1000: begin wix_addr = 5'd12; WIXenHard = 1; end
   64'hffff_dfff_0000_2000: begin wix_addr = 5'd13; WIXenHard = 1; end
   64'hffff_bfff_0000_4000: begin wix_addr = 5'd14; WIXenHard = 1; end
   64'hffff_7fff_0000_8000: begin wix_addr = 5'd15; WIXenHard = 1; end
   64'hfffe_ffff_0001_0000: begin wix_addr = 5'd16; WIXenHard = 1; end
   64'hfffd_ffff_0002_0000: begin wix_addr = 5'd17; WIXenHard = 1; end
   64'hfffb_ffff_0004_0000: begin wix_addr = 5'd18; WIXenHard = 1; end
   64'hfff7_ffff_0008_0000: begin wix_addr = 5'd19; WIXenHard = 1; end
   64'hffef_ffff_0010_0000: begin wix_addr = 5'd20; WIXenHard = 1; end
   64'hffdf_ffff_0020_0000: begin wix_addr = 5'd21; WIXenHard = 1; end
   64'hffbf_ffff_0040_0000: begin wix_addr = 5'd22; WIXenHard = 1; end
   64'hff7f_ffff_0080_0000: begin wix_addr = 5'd23; WIXenHard = 1; end
   64'hfeff_ffff_0100_0000: begin wix_addr = 5'd24; WIXenHard = 1; end
   64'hfdff_ffff_0200_0000: begin wix_addr = 5'd25; WIXenHard = 1; end
   64'hfbff_ffff_0400_0000: begin wix_addr = 5'd26; WIXenHard = 1; end
   64'hf7ff_ffff_0800_0000: begin wix_addr = 5'd27; WIXenHard = 1; end
   64'hefff_ffff_1000_0000: begin wix_addr = 5'd28; WIXenHard = 1; end
   64'hdfff_ffff_2000_0000: begin wix_addr = 5'd29; WIXenHard = 1; end
   64'hbfff_ffff_4000_0000: begin wix_addr = 5'd30; WIXenHard = 1; end
   64'h7fff_ffff_8000_0000: begin wix_addr = 5'd31; WIXenHard = 1; end
   default : begin
              wix_addr = 5'd0; WIXenHard = 0; WIXenSoft = 0;
              wixError = ErrorEn;
             end
  endcase

  WIXen = WIXenHard | WIXenSoft;

  //$display($time," WIX=%b_%b_%b_%b, DI=%h",INST_W1HXB,INST_W1LXB,INST_W1HX,INST_W1LX,d1);

end
//
// Write Port IY address encode and illigal address detect.
//
always @(INST_W1LY or INST_W1HY or INST_W1LYB or INST_W1HYB)
begin

  wiyError = 0;

  case ({INST_W1HYB,INST_W1LYB,INST_W1HY,INST_W1LY})
   64'hffff_ffff_0000_0000: begin wiy_addr = 5'd0;  WIYenHard = 0; 
						    WIYenSoft = 0; end

   64'hffff_fffe_0000_0000: begin wiy_addr = 5'd0;  WIYenSoft = 1; end
   64'hffff_fffd_0000_0000: begin wiy_addr = 5'd1;  WIYenSoft = 1; end
   64'hffff_fffb_0000_0000: begin wiy_addr = 5'd2;  WIYenSoft = 1; end
   64'hffff_fff7_0000_0000: begin wiy_addr = 5'd3;  WIYenSoft = 1; end
   64'hffff_ffef_0000_0000: begin wiy_addr = 5'd4;  WIYenSoft = 1; end
   64'hffff_ffdf_0000_0000: begin wiy_addr = 5'd5;  WIYenSoft = 1; end
   64'hffff_ffbf_0000_0000: begin wiy_addr = 5'd6;  WIYenSoft = 1; end
   64'hffff_ff7f_0000_0000: begin wiy_addr = 5'd7;  WIYenSoft = 1; end
   64'hffff_feff_0000_0000: begin wiy_addr = 5'd8;  WIYenSoft = 1; end
   64'hffff_fdff_0000_0000: begin wiy_addr = 5'd9;  WIYenSoft = 1; end
   64'hffff_fbff_0000_0000: begin wiy_addr = 5'd10; WIYenSoft = 1; end
   64'hffff_f7ff_0000_0000: begin wiy_addr = 5'd11; WIYenSoft = 1; end
   64'hffff_efff_0000_0000: begin wiy_addr = 5'd12; WIYenSoft = 1; end
   64'hffff_dfff_0000_0000: begin wiy_addr = 5'd13; WIYenSoft = 1; end
   64'hffff_bfff_0000_0000: begin wiy_addr = 5'd14; WIYenSoft = 1; end
   64'hffff_7fff_0000_0000: begin wiy_addr = 5'd15; WIYenSoft = 1; end
   64'hfffe_ffff_0000_0000: begin wiy_addr = 5'd16; WIYenSoft = 1; end
   64'hfffd_ffff_0000_0000: begin wiy_addr = 5'd17; WIYenSoft = 1; end
   64'hfffb_ffff_0000_0000: begin wiy_addr = 5'd18; WIYenSoft = 1; end
   64'hfff7_ffff_0000_0000: begin wiy_addr = 5'd19; WIYenSoft = 1; end
   64'hffef_ffff_0000_0000: begin wiy_addr = 5'd20; WIYenSoft = 1; end
   64'hffdf_ffff_0000_0000: begin wiy_addr = 5'd21; WIYenSoft = 1; end
   64'hffbf_ffff_0000_0000: begin wiy_addr = 5'd22; WIYenSoft = 1; end
   64'hff7f_ffff_0000_0000: begin wiy_addr = 5'd23; WIYenSoft = 1; end
   64'hfeff_ffff_0000_0000: begin wiy_addr = 5'd24; WIYenSoft = 1; end
   64'hfdff_ffff_0000_0000: begin wiy_addr = 5'd25; WIYenSoft = 1; end
   64'hfbff_ffff_0000_0000: begin wiy_addr = 5'd26; WIYenSoft = 1; end
   64'hf7ff_ffff_0000_0000: begin wiy_addr = 5'd27; WIYenSoft = 1; end
   64'hefff_ffff_0000_0000: begin wiy_addr = 5'd28; WIYenSoft = 1; end
   64'hdfff_ffff_0000_0000: begin wiy_addr = 5'd29; WIYenSoft = 1; end
   64'hbfff_ffff_0000_0000: begin wiy_addr = 5'd30; WIYenSoft = 1; end
   64'h7fff_ffff_0000_0000: begin wiy_addr = 5'd31; WIYenSoft = 1; end

   64'hffff_ffff_0000_0001: begin wiy_addr = 5'd0;  WIYenSoft = 1; end
   64'hffff_ffff_0000_0002: begin wiy_addr = 5'd1;  WIYenSoft = 1; end
   64'hffff_ffff_0000_0004: begin wiy_addr = 5'd2;  WIYenSoft = 1; end
   64'hffff_ffff_0000_0008: begin wiy_addr = 5'd3;  WIYenSoft = 1; end
   64'hffff_ffff_0000_0010: begin wiy_addr = 5'd4;  WIYenSoft = 1; end
   64'hffff_ffff_0000_0020: begin wiy_addr = 5'd5;  WIYenSoft = 1; end
   64'hffff_ffff_0000_0040: begin wiy_addr = 5'd6;  WIYenSoft = 1; end
   64'hffff_ffff_0000_0080: begin wiy_addr = 5'd7;  WIYenSoft = 1; end
   64'hffff_ffff_0000_0100: begin wiy_addr = 5'd8;  WIYenSoft = 1; end
   64'hffff_ffff_0000_0200: begin wiy_addr = 5'd9;  WIYenSoft = 1; end
   64'hffff_ffff_0000_0400: begin wiy_addr = 5'd10; WIYenSoft = 1; end
   64'hffff_ffff_0000_0800: begin wiy_addr = 5'd11; WIYenSoft = 1; end
   64'hffff_ffff_0000_1000: begin wiy_addr = 5'd12; WIYenSoft = 1; end
   64'hffff_ffff_0000_2000: begin wiy_addr = 5'd13; WIYenSoft = 1; end
   64'hffff_ffff_0000_4000: begin wiy_addr = 5'd14; WIYenSoft = 1; end
   64'hffff_ffff_0000_8000: begin wiy_addr = 5'd15; WIYenSoft = 1; end
   64'hffff_ffff_0001_0000: begin wiy_addr = 5'd16; WIYenSoft = 1; end
   64'hffff_ffff_0002_0000: begin wiy_addr = 5'd17; WIYenSoft = 1; end
   64'hffff_ffff_0004_0000: begin wiy_addr = 5'd18; WIYenSoft = 1; end
   64'hffff_ffff_0008_0000: begin wiy_addr = 5'd19; WIYenSoft = 1; end
   64'hffff_ffff_0010_0000: begin wiy_addr = 5'd20; WIYenSoft = 1; end
   64'hffff_ffff_0020_0000: begin wiy_addr = 5'd21; WIYenSoft = 1; end
   64'hffff_ffff_0040_0000: begin wiy_addr = 5'd22; WIYenSoft = 1; end
   64'hffff_ffff_0080_0000: begin wiy_addr = 5'd23; WIYenSoft = 1; end
   64'hffff_ffff_0100_0000: begin wiy_addr = 5'd24; WIYenSoft = 1; end
   64'hffff_ffff_0200_0000: begin wiy_addr = 5'd25; WIYenSoft = 1; end
   64'hffff_ffff_0400_0000: begin wiy_addr = 5'd26; WIYenSoft = 1; end
   64'hffff_ffff_0800_0000: begin wiy_addr = 5'd27; WIYenSoft = 1; end
   64'hffff_ffff_1000_0000: begin wiy_addr = 5'd28; WIYenSoft = 1; end
   64'hffff_ffff_2000_0000: begin wiy_addr = 5'd29; WIYenSoft = 1; end
   64'hffff_ffff_4000_0000: begin wiy_addr = 5'd30; WIYenSoft = 1; end
   64'hffff_ffff_8000_0000: begin wiy_addr = 5'd31; WIYenSoft = 1; end

   64'hffff_fffe_0000_0001: begin wiy_addr = 5'd0;  WIYenHard = 1; end
   64'hffff_fffd_0000_0002: begin wiy_addr = 5'd1;  WIYenHard = 1; end
   64'hffff_fffb_0000_0004: begin wiy_addr = 5'd2;  WIYenHard = 1; end
   64'hffff_fff7_0000_0008: begin wiy_addr = 5'd3;  WIYenHard = 1; end
   64'hffff_ffef_0000_0010: begin wiy_addr = 5'd4;  WIYenHard = 1; end
   64'hffff_ffdf_0000_0020: begin wiy_addr = 5'd5;  WIYenHard = 1; end
   64'hffff_ffbf_0000_0040: begin wiy_addr = 5'd6;  WIYenHard = 1; end
   64'hffff_ff7f_0000_0080: begin wiy_addr = 5'd7;  WIYenHard = 1; end
   64'hffff_feff_0000_0100: begin wiy_addr = 5'd8;  WIYenHard = 1; end
   64'hffff_fdff_0000_0200: begin wiy_addr = 5'd9;  WIYenHard = 1; end
   64'hffff_fbff_0000_0400: begin wiy_addr = 5'd10; WIYenHard = 1; end
   64'hffff_f7ff_0000_0800: begin wiy_addr = 5'd11; WIYenHard = 1; end
   64'hffff_efff_0000_1000: begin wiy_addr = 5'd12; WIYenHard = 1; end
   64'hffff_dfff_0000_2000: begin wiy_addr = 5'd13; WIYenHard = 1; end
   64'hffff_bfff_0000_4000: begin wiy_addr = 5'd14; WIYenHard = 1; end
   64'hffff_7fff_0000_8000: begin wiy_addr = 5'd15; WIYenHard = 1; end
   64'hfffe_ffff_0001_0000: begin wiy_addr = 5'd16; WIYenHard = 1; end
   64'hfffd_ffff_0002_0000: begin wiy_addr = 5'd17; WIYenHard = 1; end
   64'hfffb_ffff_0004_0000: begin wiy_addr = 5'd18; WIYenHard = 1; end
   64'hfff7_ffff_0008_0000: begin wiy_addr = 5'd19; WIYenHard = 1; end
   64'hffef_ffff_0010_0000: begin wiy_addr = 5'd20; WIYenHard = 1; end
   64'hffdf_ffff_0020_0000: begin wiy_addr = 5'd21; WIYenHard = 1; end
   64'hffbf_ffff_0040_0000: begin wiy_addr = 5'd22; WIYenHard = 1; end
   64'hff7f_ffff_0080_0000: begin wiy_addr = 5'd23; WIYenHard = 1; end
   64'hfeff_ffff_0100_0000: begin wiy_addr = 5'd24; WIYenHard = 1; end
   64'hfdff_ffff_0200_0000: begin wiy_addr = 5'd25; WIYenHard = 1; end
   64'hfbff_ffff_0400_0000: begin wiy_addr = 5'd26; WIYenHard = 1; end
   64'hf7ff_ffff_0800_0000: begin wiy_addr = 5'd27; WIYenHard = 1; end
   64'hefff_ffff_1000_0000: begin wiy_addr = 5'd28; WIYenHard = 1; end
   64'hdfff_ffff_2000_0000: begin wiy_addr = 5'd29; WIYenHard = 1; end
   64'hbfff_ffff_4000_0000: begin wiy_addr = 5'd30; WIYenHard = 1; end
   64'h7fff_ffff_8000_0000: begin wiy_addr = 5'd31; WIYenHard = 1; end
   default : begin
              wiy_addr = 5'd0; WIYenHard = 0; WIYenSoft = 0;
              wiyError = ErrorEn;
             end
  endcase

  WIYen = WIYenHard | WIYenSoft;

  //$display($time," WIY=%b_%b_%b_%b, DI=%h",INST_W1HYB,INST_W1LYB,INST_W1HY,INST_W1LY,d1);
end
//
// Two Write Ports address Conflict.
//
always @(wo_addr or wix_addr or wiy_addr or WOen or WIXen or WIYen)
begin
  if (wo_addr==wix_addr & WOen & WIXen & ErrorEn)
    begin
     WrConflict = 1;
     $display($time,"  ERROR:Write Conflict Port (O,IX) for 3R/2W regfile"); 
    end

  if (wo_addr==wiy_addr & WOen & WIYen & ErrorEn)
    begin
     WrConflict = 1;
     $display($time,"  ERROR:Write Conflict Port (O,IY) for 3R/2W regfile"); 
    end
end
//
// ReadPort:A to WrAddress conflict 
//
always @(wo_addr or wix_addr or wiy_addr or WOen or WIXen or WIYen or ra_addr)
begin
 rawConflict = 0;
 if (wo_addr== ra_addr & WOen & ErrorEn)
   begin
     rawConflict = 1;
   end
 if (wix_addr== ra_addr & WIXen & ErrorEn)
   begin
     rawConflict = 1;
   end
 if (wiy_addr== ra_addr & WIYen & ErrorEn)
   begin
     rawConflict = 1;
   end
end
//
// ReadPort:B to WrAddress conflict 
//
always @(wo_addr or wix_addr or wiy_addr or WOen or WIXen or WIYen or rb_addr)
begin
 rbwConflict = 0;
 if (wo_addr== rb_addr & WOen & ErrorEn)
   begin
     rbwConflict = 1;
   end
 if (wix_addr== rb_addr & WIXen & ErrorEn)
   begin
     rbwConflict = 1;
   end
 if (wiy_addr== rb_addr & WIYen & ErrorEn)
   begin
     rbwConflict = 1;
   end
end
//
// ReadPort:C to WrAddress conflict 
//
always @(wo_addr or wix_addr or wiy_addr or WOen or WIXen or WIYen or rc_addr)
begin
 rcwConflict = 0;
 if (wo_addr== rc_addr & WOen & ErrorEn)
   begin
     rcwConflict = 1;
   end
 if (wix_addr== rc_addr & WIXen & ErrorEn)
   begin
     rcwConflict = 1;
   end
 if (wiy_addr== rc_addr & WIYen & ErrorEn)
   begin
     rcwConflict = 1;
   end
end

/**************************************************************
 * Write Ports (O, IX, IY)
 **************************************************************/
// Port O
always @(wo_addr or d0 or WOenSoft or WOenHard or woError or WrConflict)
  if (woError)
   begin
    if (Report_Error)
     $display($time,"  ERROR:(Port:O) Write Address Error for 3R/2W regfile"); 
   end
  else
  if (WOenSoft & !WOenHard & !WrConflict)
      mem[wo_addr] = 16'hx;
  else
  if (WOenHard & !WrConflict)
      mem[wo_addr] = d0;

// Port IX
always @(wix_addr or d1 or WIXenSoft or WIXenHard or wixError or WrConflict)
  if (wixError)
   begin
    if (Report_Error)
     $display($time,"  ERROR:(Port:IX) Write Address Error for 3R/2W regfile"); 
   end
  else
  if (WIXenSoft & !WIXenHard & !WrConflict)
      mem[wix_addr] = mem[wix_addr]&16'hffxx;
  else
  if (WIXenHard & !WrConflict)
      mem[wix_addr] = mem[wix_addr]&16'hff00 | d1[7:0];

// Port IY
always @(wiy_addr or d1 or WIYenSoft or WIYenHard or wiyError or WrConflict)
  if (wiyError)
   begin
   if (Report_Error)
     $display($time,"  ERROR:(Port:IY) Write Address Error for 3R/2W regfile"); 
   end
  else
  if (WIYenSoft & !WIYenHard & !WrConflict)
      mem[wiy_addr] = mem[wiy_addr]&16'hxxff;
  else
  if (WIYenHard & !WrConflict)
      mem[wiy_addr] = mem[wiy_addr]&16'h00ff | {d1[15:8],8'h0};


/**************************************************************
 * Read Port:A
 **************************************************************/
always @(ra_addr or raError or wo_addr or WOen or Noise or 
	 wix_addr or WIXen or wiy_addr or WIYen or d1 or d0 or rawConflict)
  if (raError | rawConflict)
     a[15:0] = 16'hx;
  else
     a[15:0] = mem[ra_addr];

/**************************************************************
 * Read Port:B
 **************************************************************/
always @(rb_addr or rbError or wo_addr or WOen or Noise or 
	 wix_addr or WIXen or wiy_addr or WIYen or d1 or d0 or rbwConflict)
  if (rbError | rbwConflict)
     b[15:0] = 16'hx;
  else
     b[15:0] = mem[rb_addr];

/**************************************************************
 * Read Port:C
 **************************************************************/
always @(rc_addr or rcError or wo_addr or WOen or Noise or 
	 wix_addr or WIXen or wiy_addr or WIYen or d1 or d0 or rcwConflict)
  if (rcError | rcwConflict)
     c[15:0] = 16'hx;
  else
     c[15:0] = mem[rc_addr];

endmodule
