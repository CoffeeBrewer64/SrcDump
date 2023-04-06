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

// $Id: ram_bist_tmem.v,v 1.2 2002/10/23 00:06:33 rws Exp $

////////////////////////////////////////////////////////////////////////
//
// Project Reality
//
// module:	ram_bist_tmem
// description:	built-in-self-test for tmem banks. Detects all
//		stuck-at and coupling faults.
//
// designer:	Tony DeLaurier
// date:	10/25/94
//
////////////////////////////////////////////////////////////////////////

module ram_bist_tmem (clk, reset_l, bist_go, bist_check, sys0_addr, sys1_addr, 
		      sys2_addr, sys3_addr, sys4_addr, sys5_addr, sys6_addr, 
		      sys7_addr, sys0_din, sys1_din, sys2_din, sys3_din, 
		      sys4_din, sys5_din, sys6_din, sys7_din, sys0_web, 
		      sys1_web, sys2_web, sys3_web, sys4_web, sys5_web, 
		      sys6_web, sys7_web, ram0_do, ram1_do, ram2_do, ram3_do, 
		      ram4_do, ram5_do, ram6_do, ram7_do, ram0_addr, ram1_addr,
		      ram2_addr, ram3_addr, ram4_addr, ram5_addr, ram6_addr, 
		      ram7_addr, ram0_din, ram1_din, ram2_din, ram3_din, 
		      ram4_din, ram5_din, ram6_din, ram7_din,  ram0_web, 
		      ram1_web, ram2_web, ram3_web, ram4_web, ram5_web, 
		      ram6_web, ram7_web, bist_done, bist0_fail, bist1_fail, 
		      bist2_fail, bist3_fail, bist4_fail, bist5_fail, 
		      bist6_fail, bist7_fail);

  input clk;			// clock
  input reset_l;		// reset (active low)
  input bist_go;		// mem test enable
  input bist_check;		// bist test enable

  input [7:0] sys0_addr;	// online address (bnk0)
  input [7:0] sys1_addr;	// online address (bnk1)
  input [7:0] sys2_addr;	// online address (bnk2)
  input [7:0] sys3_addr;	// online address (bnk3)
  input [7:0] sys4_addr;	// online address (bnk4)
  input [7:0] sys5_addr;	// online address (bnk5)
  input [7:0] sys6_addr;	// online address (bnk6)
  input [7:0] sys7_addr;	// online address (bnk7)

  input [15:0] sys0_din;	// online data in (bnk0)
  input [15:0] sys1_din;	// online data in (bnk1)
  input [15:0] sys2_din;	// online data in (bnk2)
  input [15:0] sys3_din;	// online data in (bnk3)
  input [15:0] sys4_din;	// online data in (bnk4)
  input [15:0] sys5_din;	// online data in (bnk5)
  input [15:0] sys6_din;	// online data in (bnk6)
  input [15:0] sys7_din;	// online data in (bnk7)

  input sys0_web;		// online web (bnk0)
  input sys1_web;		// online web (bnk1)
  input sys2_web;		// online web (bnk2)
  input sys3_web;		// online web (bnk3)
  input sys4_web;		// online web (bnk4)
  input sys5_web;		// online web (bnk5)
  input sys6_web;		// online web (bnk6)
  input sys7_web;		// online web (bnk7)

  input [15:0] ram0_do;		// dout from ram (bnk0)
  input [15:0] ram1_do;		// dout from ram (bnk1)
  input [15:0] ram2_do;		// dout from ram (bnk2)
  input [15:0] ram3_do;		// dout from ram (bnk3)
  input [15:0] ram4_do;		// dout from ram (bnk4)
  input [15:0] ram5_do;		// dout from ram (bnk5)
  input [15:0] ram6_do;		// dout from ram (bnk6)
  input [15:0] ram7_do;		// dout from ram (bnk7)

  output [7:0] ram0_addr;	// address to ram (bnk0)
  output [7:0] ram1_addr;	// address to ram (bnk1)
  output [7:0] ram2_addr;	// address to ram (bnk2)
  output [7:0] ram3_addr;	// address to ram (bnk3)
  output [7:0] ram4_addr;	// address to ram (bnk4)
  output [7:0] ram5_addr;	// address to ram (bnk5)
  output [7:0] ram6_addr;	// address to ram (bnk6)
  output [7:0] ram7_addr;	// address to ram (bnk7)

  output [15:0] ram0_din;	// data_in to ram (bnk0)
  output [15:0] ram1_din;	// data_in to ram (bnk1)
  output [15:0] ram2_din;	// data_in to ram (bnk2)
  output [15:0] ram3_din;	// data_in to ram (bnk3)
  output [15:0] ram4_din;	// data_in to ram (bnk4)
  output [15:0] ram5_din;	// data_in to ram (bnk5)
  output [15:0] ram6_din;	// data_in to ram (bnk6)
  output [15:0] ram7_din;	// data_in to ram (bnk7)

  output ram0_web;		// web to ram (bnk0)
  output ram1_web;		// web to ram (bnk1)
  output ram2_web;		// web to ram (bnk2)
  output ram3_web;		// web to ram (bnk3)
  output ram4_web;		// web to ram (bnk4)
  output ram5_web;		// web to ram (bnk5)
  output ram6_web;		// web to ram (bnk6)
  output ram7_web;		// web to ram (bnk7)

  output bist_done;		// bist done
  reg bist_done;		// bist done
  output bist0_fail;		// mem test fail flag (active high) (bnk0)
  reg bist0_fail;		// mem test fail flag (active high) (bnk0)
  output bist1_fail;		// mem test fail flag (active high) (bnk1)
  reg bist1_fail;		// mem test fail flag (active high) (bnk1)
  output bist2_fail;		// mem test fail flag (active high) (bnk2)
  reg bist2_fail;		// mem test fail flag (active high) (bnk2)
  output bist3_fail;		// mem test fail flag (active high) (bnk3)
  reg bist3_fail;		// mem test fail flag (active high) (bnk3)
  output bist4_fail;		// mem test fail flag (active high) (bnk4)
  reg bist4_fail;		// mem test fail flag (active high) (bnk4)
  output bist5_fail;		// mem test fail flag (active high) (bnk5)
  reg bist5_fail;		// mem test fail flag (active high) (bnk5)
  output bist6_fail;		// mem test fail flag (active high) (bnk6)
  reg bist6_fail;		// mem test fail flag (active high) (bnk6)
  output bist7_fail;		// mem test fail flag (active high) (bnk7)
  reg bist7_fail;		// mem test fail flag (active high) (bnk7)

  reg bist_go_1d;		// bist_go delayed 1 cycle
  reg [4:0] bist_state;		// bist state -> 0 to 18
  reg [4:0] bist_state_n;	// next bist_state
  reg [11:0] cell_cnt;		// cell counter
  reg [11:0] cell_cnt_n;	// next cell_cnt
  reg [1:0] cyc_cnt;		// cell-cycle counter
  reg [1:0] cyc_cnt_n;		// next cyc_cnt
  reg [15:0] dec0;		// decode
  reg [15:0] dec0_swiz;		// dec0 swizzled
  reg [15:0] dec1;		// decode with trailing ones
  reg [15:0] dec1_swiz;		// dec1 swizzled
  reg [7:0] bist_addr;		// bist address
  reg [15:0] bist_din;		// bist data into mux
  reg bist_web;			// bist web
  reg select_bist;		// mux select (bist vs normal)

  reg sel0_bist;		// mux select (address bnk0)
  reg sel1_bist;		// mux select (address bnk1)
  reg sel2_bist;		// mux select (address bnk2)
  reg sel3_bist;		// mux select (address bnk3)
  reg sel4_bist;		// mux select (address bnk4)
  reg sel5_bist;		// mux select (address bnk5)
  reg sel6_bist;		// mux select (address bnk6)
  reg sel7_bist;		// mux select (address bnk7)

  reg sel0_bist_web;		// mux select (web bnk0)
  reg sel1_bist_web;		// mux select (web bnk1)
  reg sel2_bist_web;		// mux select (web bnk2)
  reg sel3_bist_web;		// mux select (web bnk3)
  reg sel4_bist_web;		// mux select (web bnk4)
  reg sel5_bist_web;		// mux select (web bnk5)
  reg sel6_bist_web;		// mux select (web bnk6)
  reg sel7_bist_web;		// mux select (web bnk7)

  reg select_bist_1d;		// select_bist delayed 1
  reg [3:0] bit_sel;		// mux select for ram_do
  reg cmp_bit;			// compare bit
  reg cmp_en;			// compare enable
  reg bist_check_1d;		// bist_check delayed 1
  reg bc0_lev;			// bist test (cmp_bit = 0) level
  reg bc1_lev;			// bist test (cmp_bit = 1) level
  reg force_one;		// force 1 on ram_bit
  reg force_zero;		// force 0 on ram_bit

  wire reverse;			// walk addresses in reverse flag
  wire bist_go_pulse;		// rising-edge detect of bist_go
  wire last;			// last cycle, last cell of memory
  wire num_cyc1;		// 1 cycle per cell
  wire num_cyc2;		// 2 cycles per cell
  wire num_cyc3;		// 3 cycles per cell
  wire bist_check0;		// bist test (cmp_bit = 0) pulse
  wire bist_check1;		// bist test (cmp_bit = 1) pulse

  parameter FIRST_CELL = 12'h000; 
  parameter LAST_CELL  = 12'hfff; 


  // determine # of cycles per cell

  assign num_cyc1 = ((bist_state == 5'h01) || (bist_state == 5'h03) || 
	      	     (bist_state == 5'h05) || (bist_state == 5'h07) || 
	      	     (bist_state == 5'h09) || (bist_state == 5'h0b) || 
	      	     (bist_state == 5'h0d) || (bist_state == 5'h0e) || 
	      	     (bist_state == 5'h10) || (bist_state == 5'h12));

  assign num_cyc2 = ((bist_state == 5'h02) || (bist_state == 5'h04) || 
	      	     (bist_state == 5'h06) || (bist_state == 5'h08));

  assign num_cyc3 = ((bist_state == 5'h0a) || (bist_state == 5'h0c) || 
	      	     (bist_state == 5'h0f) || (bist_state == 5'h11));


  // detect last cycle of last memory cell

  assign last = ((cell_cnt == LAST_CELL) &&
		 ( num_cyc1 || 
		  (num_cyc2 && (cyc_cnt[1:0] == 2'b01)) || 
		  (num_cyc3 && (cyc_cnt[1:0] == 2'b10))));


  // edge detect bist_go

  always @(posedge clk)
  begin
    bist_go_1d <= bist_go;
  end // always

  assign bist_go_pulse = bist_go && !bist_go_1d;
  

  // determine bist state

  always @(bist_go_pulse or bist_state or bist_check0 or bist_check1 or 
	   last or bc0_lev or bc1_lev)
  begin

    if (bist_go_pulse || bist_check0 || bist_check1)
      bist_state_n = 5'h01;

    else if (bist_state != 5'h00)
    begin
      if (last)
      begin
        if ((bist_state == 5'h12) || 
	    ((bist_state == 5'h03) && (bc0_lev || bc1_lev)))
          bist_state_n = 5'h00;
        else
          bist_state_n = bist_state + 1;
      end
      else
        bist_state_n = bist_state;
    end

    else
      bist_state_n = 5'h00;

  end // always

  always @(posedge clk)
  begin

    if (reset_l == 1'b0)
      bist_state <= 5'h00;
    else
      bist_state <= bist_state_n;

  end // always


  // determine cyc_cnt

  always @(bist_go_pulse or bist_check0 or bist_check1 or 
    	   num_cyc2 or cyc_cnt or num_cyc3)
  begin

    if (bist_go_pulse || bist_check0 || bist_check1)
      cyc_cnt_n = 2'b00;

    else
    begin
      if ((num_cyc2 && (cyc_cnt[1:0] != 2'b01)) ||
          (num_cyc3 && (cyc_cnt[1:0] != 2'b10)))
        cyc_cnt_n = cyc_cnt + 1;
      else
        cyc_cnt_n = 2'b00;
    end

  end // always

  always @(posedge clk)
  begin

    if (reset_l == 1'b0)
      cyc_cnt <= 2'b00;
    else
      cyc_cnt <= cyc_cnt_n;

  end // always


  // determine cell_cnt

  always @(bist_go_pulse or bist_check0 or bist_check1 or num_cyc1 or 
	   num_cyc2 or num_cyc3 or cyc_cnt or cell_cnt)
  begin

    if (bist_go_pulse || bist_check0 || bist_check1)
      cell_cnt_n = FIRST_CELL;
    else
    begin
      if ((num_cyc1) || 
         ((num_cyc2) && (cyc_cnt[1:0] == 2'b01)) ||
         ((num_cyc3) && (cyc_cnt[1:0] == 2'b10)))
      begin
        if (cell_cnt == LAST_CELL)
          cell_cnt_n = FIRST_CELL;
        else
          cell_cnt_n = cell_cnt + 1;
      end
      else
        cell_cnt_n = cell_cnt;
    end
  end // always

  always @(posedge clk)
  begin

    if (reset_l == 1'b0)
      cell_cnt <= FIRST_CELL;
    else
      cell_cnt <= cell_cnt_n;

  end // always

  
  // determine bist address

  assign reverse = ((bist_state_n == 5'h03) || (bist_state_n == 5'h05) || 
		    (bist_state_n == 5'h06) || (bist_state_n == 5'h08) || 
		    (bist_state_n == 5'h0b) || (bist_state_n == 5'h0c) || 
		    (bist_state_n == 5'h10) || (bist_state_n == 5'h11));

  always @(posedge clk)
  begin

    bist_addr[7:0] <= cell_cnt_n[11:4] ^ {8{reverse}};

  end // always

  // determine bist din

  always @(posedge clk)
  begin

    case (cell_cnt_n[3:0])
      4'h0:
	begin
          dec0 = 16'h0001;
          dec1 = 16'h0001;
	end
      4'h1:
	begin
          dec0 = 16'h0002;
          dec1 = 16'h0003;
	end
      4'h2:
	begin
          dec0 = 16'h0004;
          dec1 = 16'h0007;
	end
      4'h3:
	begin
          dec0 = 16'h0008;
          dec1 = 16'h000f;
	end
      4'h4:
	begin
          dec0 = 16'h0010;
          dec1 = 16'h001f;
	end
      4'h5:
	begin
          dec0 = 16'h0020;
          dec1 = 16'h003f;
	end
      4'h6:
	begin
          dec0 = 16'h0040;
          dec1 = 16'h007f;
	end
      4'h7:
	begin
          dec0 = 16'h0080;
          dec1 = 16'h00ff;
	end
      4'h8:
	begin
          dec0 = 16'h0100;
          dec1 = 16'h01ff;
	end
      4'h9:
	begin
          dec0 = 16'h0200;
          dec1 = 16'h03ff;
	end
      4'ha:
	begin
          dec0 = 16'h0400;
          dec1 = 16'h07ff;
	end
      4'hb:
	begin
          dec0 = 16'h0800;
          dec1 = 16'h0fff;
	end
      4'hc:
	begin
          dec0 = 16'h1000;
          dec1 = 16'h1fff;
	end
      4'hd:
	begin
          dec0 = 16'h2000;
          dec1 = 16'h3fff;
	end
      4'he:
	begin
          dec0 = 16'h4000;
          dec1 = 16'h7fff;
	end
      4'hf:
	begin
          dec0 = 16'h8000;
          dec1 = 16'hffff;
	end
      default:
	begin
          dec0 = 16'hx;
          dec1 = 16'hx;
        end
    endcase

    dec1_swiz[15:0] = {dec1[0], dec1[1], dec1[2], dec1[3], dec1[4], dec1[5], 
	  	       dec1[6], dec1[7], dec1[8], dec1[9], dec1[10], dec1[11], 
		       dec1[12], dec1[13], dec1[14], dec1[15]};

    dec0_swiz[15:0] = {dec0[0], dec0[1], dec0[2], dec0[3], dec0[4], dec0[5], 
	  	       dec0[6], dec0[7], dec0[8], dec0[9], dec0[10], dec0[11], 
		       dec0[12], dec0[13], dec0[14], dec0[15]};

    case (bist_state_n)
      5'h02: 
	bist_din[15:0] <= dec1 & {16{(cyc_cnt_n == 2'b01)}};
      5'h04: 
	bist_din[15:0] <= ~dec1 & {16{(cyc_cnt_n == 2'b01)}};
      5'h06: 
  	bist_din[15:0] <= dec1_swiz & {16{(cyc_cnt_n == 2'b01)}};
      5'h08:
	bist_din[15:0] <= ~dec1_swiz & {16{(cyc_cnt_n == 2'b01)}};
      5'h0a:
	bist_din[15:0] <= dec0 & {16{(cyc_cnt_n == 2'b01)}};
      5'h0c:
	bist_din[15:0] <= dec0_swiz & {16{(cyc_cnt_n == 2'b01)}};
      5'h0e: 
	bist_din[15:0] <= 16'hffff;
      5'h0f:
	bist_din[15:0] <= (~dec0 & {16{(cyc_cnt_n == 2'b01)}}) | 
			  {16{(cyc_cnt_n == 2'b10)}};
      5'h11:
	bist_din[15:0] <= (~dec0_swiz & {16{(cyc_cnt_n == 2'b01)}}) | 
			  {16{(cyc_cnt_n == 2'b10)}};
      default: 
	bist_din[15:0] <= 16'h0000;
    endcase

  end // always


  // determine bist web

  always @(posedge clk)
  begin

    case (bist_state_n)
      5'h01,
      5'h0e:
        bist_web <= 1'b0;
      default: 
        bist_web <= (cyc_cnt_n == 2'b00);
    endcase

  end // always

  // mux addr, di, and web based on bist_state

  always @(posedge clk)
  begin

    select_bist <= (bist_state_n != 0);

    sel0_bist <= (bist_state_n != 0);
    sel1_bist <= (bist_state_n != 0);
    sel2_bist <= (bist_state_n != 0);
    sel3_bist <= (bist_state_n != 0);
    sel4_bist <= (bist_state_n != 0);
    sel5_bist <= (bist_state_n != 0);
    sel6_bist <= (bist_state_n != 0);
    sel7_bist <= (bist_state_n != 0);

    sel0_bist_web <= (bist_state_n != 0);
    sel1_bist_web <= (bist_state_n != 0);
    sel2_bist_web <= (bist_state_n != 0);
    sel3_bist_web <= (bist_state_n != 0);
    sel4_bist_web <= (bist_state_n != 0);
    sel5_bist_web <= (bist_state_n != 0);
    sel6_bist_web <= (bist_state_n != 0);
    sel7_bist_web <= (bist_state_n != 0);

  end // always
  
  assign ram0_addr = sel0_bist ? bist_addr : sys0_addr;
  assign ram1_addr = sel1_bist ? bist_addr : sys1_addr;
  assign ram2_addr = sel2_bist ? bist_addr : sys2_addr;
  assign ram3_addr = sel3_bist ? bist_addr : sys3_addr;
  assign ram4_addr = sel4_bist ? bist_addr : sys4_addr;
  assign ram5_addr = sel5_bist ? bist_addr : sys5_addr;
  assign ram6_addr = sel6_bist ? bist_addr : sys6_addr;
  assign ram7_addr = sel7_bist ? bist_addr : sys7_addr;

  assign ram0_din  = select_bist ? bist_din  : sys0_din;
  assign ram1_din  = select_bist ? bist_din  : sys1_din;
  assign ram2_din  = select_bist ? bist_din  : sys2_din;
  assign ram3_din  = select_bist ? bist_din  : sys3_din;
  assign ram4_din  = select_bist ? bist_din  : sys4_din;
  assign ram5_din  = select_bist ? bist_din  : sys5_din;
  assign ram6_din  = select_bist ? bist_din  : sys6_din;
  assign ram7_din  = select_bist ? bist_din  : sys7_din;

  assign ram0_web  = sel0_bist_web ? bist_web  : sys0_web;
  assign ram1_web  = sel1_bist_web ? bist_web  : sys1_web;
  assign ram2_web  = sel2_bist_web ? bist_web  : sys2_web;
  assign ram3_web  = sel3_bist_web ? bist_web  : sys3_web;
  assign ram4_web  = sel4_bist_web ? bist_web  : sys4_web;
  assign ram5_web  = sel5_bist_web ? bist_web  : sys5_web;
  assign ram6_web  = sel6_bist_web ? bist_web  : sys6_web;
  assign ram7_web  = sel7_bist_web ? bist_web  : sys7_web;


  // determine bit select

  always @(posedge clk)
  begin

    if ((bist_state == 5'h03) || (bist_state == 5'h05) || 
        (bist_state == 5'h06) || (bist_state == 5'h08) || 
        (bist_state == 5'h0b) || (bist_state == 5'h0c) || 
        (bist_state == 5'h10) || (bist_state == 5'h11))
      bit_sel[3:0] <= ~cell_cnt[3:0];
    else
      bit_sel[3:0] <= cell_cnt[3:0];
  
  end // always


  // determine compare bit

  always @(posedge clk)
  begin

    if ((bist_state == 5'h03) || (bist_state == 5'h04) ||
        (bist_state == 5'h07) || (bist_state == 5'h08) ||
        (bist_state == 5'h0f) || (bist_state == 5'h10) ||
        (bist_state == 5'h11) || (bist_state == 5'h12))
      cmp_bit <= 1'b1;
    else
      cmp_bit <= 1'b0;

  end // always


  // determine compare enable

  always @(posedge clk)
  begin

    if (((bist_state != 5'h00) && (bist_state != 5'h01) &&
         (bist_state != 5'h0e)) && (cyc_cnt == 2'b00))
      cmp_en <= 1'b1;
    else
      cmp_en <= 1'b0;

  end // always


  // detect mis-compare's

  always @(posedge clk)
  begin

    bist0_fail <= compare (ram0_do, bit_sel, force_one, force_zero, 
		           cmp_bit, cmp_en);

    bist1_fail <= compare (ram1_do, bit_sel, force_one, force_zero, 
		           cmp_bit, cmp_en);

    bist2_fail <= compare (ram2_do, bit_sel, force_one, force_zero, 
		           cmp_bit, cmp_en);

    bist3_fail <= compare (ram3_do, bit_sel, force_one, force_zero, 
		           cmp_bit, cmp_en);

    bist4_fail <= compare (ram4_do, bit_sel, force_one, force_zero, 
		           cmp_bit, cmp_en);

    bist5_fail <= compare (ram5_do, bit_sel, force_one, force_zero, 
		           cmp_bit, cmp_en);

    bist6_fail <= compare (ram6_do, bit_sel, force_one, force_zero, 
		           cmp_bit, cmp_en);

    bist7_fail <= compare (ram7_do, bit_sel, force_one, force_zero, 
		           cmp_bit, cmp_en);

  end // always


  // determine bist done flag

  always @(posedge clk)
  begin

    select_bist_1d <= select_bist;
    bist_done <= ~select_bist & select_bist_1d;

  end // always

 
  // edge detect bist_check

  always @(posedge clk)
  begin

    bist_check_1d <= bist_check;

  end // always

  assign bist_check0 = bist_check & ~bist_check_1d;
  assign bist_check1 = ~bist_check & bist_check_1d;

  always @(posedge clk)
  begin

    if (bist_check0)
      bc0_lev <= 1'b1;
    else if (bist_state_n == 5'h00)
      bc0_lev <= 1'b0;
    else
      bc0_lev <= bc0_lev;
   
    force_one <= bc0_lev;

  end // always

  always @(posedge clk)
  begin

    if (bist_check1)
      bc1_lev <= 1'b1;
    else if (bist_state_n == 5'h00)
      bc1_lev <= 1'b0;
    else
      bc1_lev <= bc1_lev;

    force_zero <= bc1_lev;

  end // always


  // compare function

  function compare;

    input [15:0] ram_do;
    input [3:0] bit_sel;
    input force_one;
    input force_zero;
    input cmp_bit;
    input cmp_en;

    reg ram_bit;

    begin

      case (bit_sel)
        4'h0: ram_bit = ram_do[0];
        4'h1: ram_bit = ram_do[1];
        4'h2: ram_bit = ram_do[2];
        4'h3: ram_bit = ram_do[3];
        4'h4: ram_bit = ram_do[4];
        4'h5: ram_bit = ram_do[5];
        4'h6: ram_bit = ram_do[6];
        4'h7: ram_bit = ram_do[7];
        4'h8: ram_bit = ram_do[8];
        4'h9: ram_bit = ram_do[9];
        4'ha: ram_bit = ram_do[10];
        4'hb: ram_bit = ram_do[11];
        4'hc: ram_bit = ram_do[12];
        4'hd: ram_bit = ram_do[13];
        4'he: ram_bit = ram_do[14];
        4'hf: ram_bit = ram_do[15];
        default: ram_bit = 1'bx;
      endcase

      ram_bit = (ram_bit | force_one) & !force_zero;

      compare = cmp_en & (cmp_bit ^ ram_bit);

    end
  endfunction // compare
  
endmodule // ram_bist_tmem

