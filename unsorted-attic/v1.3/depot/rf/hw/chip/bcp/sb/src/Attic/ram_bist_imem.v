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

// $Id: ram_bist_imem.v,v 1.2 2002/10/23 00:06:33 rws Exp $

////////////////////////////////////////////////////////////////////////
//
// Project Reality
//
// module:	ram_bist_imem
// description:	built-in-self-test for imem. Detects all 
//		stuck-at and almost all coupling faults.
//
// designer:	Tony DeLaurier
// date:	10/28/94
//
////////////////////////////////////////////////////////////////////////

module ram_bist_imem (clk, reset_l, iddq_test, 
		      bist_go, bist_check, sys_addr, sys_din, 
		      dma_addr, dma_cycle, sys_web, sys_csb, 
		      ram_do, ram_addr, ram_din, ram_web, 
		      ram_csb, bist_done, bist3_fail, bist2_fail, bist1_fail, 
		      bist0_fail);

  input clk;			// clock
  input reset_l;		// reset (active low)
  input iddq_test;
  input bist_go;		// mem test enable
  input bist_check;		// bist test enable

  input [8:0] sys_addr;		// online address
  input [63:0] sys_din;		// online data
  input [8:0] dma_addr;		// dma address
  input dma_cycle;
  input sys_web;		// online web
  input sys_csb;		// online csb

  input [63:0] ram_do;		// dout from ram

  output [8:0] ram_addr;	// address to ram
  output [63:0] ram_din;	// data_in to ram
  output ram_web;		// web to ram
  output ram_csb;		// csb to ram

  output bist_done;		// bist done
  reg bist_done;		// bist done
  output bist3_fail;		// mem test fail flag (active high) (bnk3)
  reg bist3_fail;		// mem test fail flag (active high) (bnk3)
  output bist2_fail;		// mem test fail flag (active high) (bnk2)
  reg bist2_fail;		// mem test fail flag (active high) (bnk2)
  output bist1_fail;		// mem test fail flag (active high) (bnk1)
  reg bist1_fail;		// mem test fail flag (active high) (bnk1)
  output bist0_fail;		// mem test fail flag (active high) (bnk0)
  reg bist0_fail;		// mem test fail flag (active high) (bnk0)

  reg bist_go_1d;		// bist_go delayed 1 cycle
  reg [4:0] bist_state;		// bist state -> 0 to 18
  reg [4:0] bist_state_n;	// next bist_state
  reg [12:0] cell_cnt;		// cell counter
  reg [12:0] cell_cnt_n;	// next cell_cnt
  reg [1:0] cyc_cnt;		// cell-cycle counter
  reg [1:0] cyc_cnt_n;		// next cyc_cnt
  reg [15:0] dec0;		// decode
  reg [15:0] dec0_swiz;		// dec0 swizzled
  reg [15:0] dec1;		// decode with trailing ones
  reg [15:0] dec1_swiz;		// dec1 swizzled
  reg [8:0] bist_addr;		// bist address
  reg [15:0] bist_din;		// bist data into mux
  reg bist_web;			// bist web
  reg bist_csb;			// bist csb
  reg select_bist;		// mux select (bist vs normal)
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

  wire [12:0] first_cell = 13'h0000; 
  wire [12:0] last_cell  = 13'h1fff; 


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

  assign last = ((cell_cnt == last_cell) &&
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
	   num_cyc2 or num_cyc3 or cyc_cnt or cell_cnt or first_cell or 
	   last_cell)
  begin

    if (bist_go_pulse || bist_check0 || bist_check1)
      cell_cnt_n = first_cell;
    else
    begin
      if ((num_cyc1) || 
         ((num_cyc2) && (cyc_cnt[1:0] == 2'b01)) ||
         ((num_cyc3) && (cyc_cnt[1:0] == 2'b10)))
      begin
        if (cell_cnt == last_cell)
          cell_cnt_n = first_cell;
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
      cell_cnt <= first_cell;
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

    bist_addr[8:0] <= cell_cnt_n[12:4] ^ {9{reverse}};

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

  // mux addr, di, web and csb based on bist_state

  always @(posedge clk)
  begin

    select_bist <= (bist_state_n != 0);
    bist_csb <= !(bist_state_n != 0);

  end // always
  
  assign ram_addr = select_bist ? bist_addr : dma_cycle ? dma_addr : sys_addr;
  assign ram_din  = select_bist ? {bist_din, bist_din, bist_din, bist_din} : sys_din;
  assign ram_web  = select_bist ? bist_web  : sys_web;
  assign ram_csb  = !iddq_test & (select_bist ? bist_csb  : sys_csb);


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

    bist0_fail <= compare (ram_do[15:0], bit_sel, force_one, force_zero, 
		           cmp_bit, cmp_en);

    bist1_fail <= compare (ram_do[31:16], bit_sel, force_one, force_zero, 
		           cmp_bit, cmp_en);

    bist2_fail <= compare (ram_do[47:32], bit_sel, force_one, force_zero, 
		           cmp_bit, cmp_en);

    bist3_fail <= compare (ram_do[63:48], bit_sel, force_one, force_zero, 
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
  
endmodule // ram_bist_imem

