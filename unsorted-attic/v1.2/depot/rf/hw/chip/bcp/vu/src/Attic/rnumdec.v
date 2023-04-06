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

// $Id: rnumdec.v,v 1.1 2002/05/21 23:55:45 berndt Exp $

// rnumdec.v:		register address decode, 5->32, 4 times (or so)
//			includes logic for write enable stability and transpose

`timescale 1ns / 10ps


   // *** The read ports of the register file must always be driven (from
   // *** Compass designer), so make sure exactly one decoded read line is 
   // *** active.

   module rnumdec (clk, st_rnum, xp_rnum, ld_rnum, vd, wbv_wr_en, bwe, xpose, slice,
	wb_div_type, wb_div_elem,  
	vurfile_ld_hi_t, vurfile_ld_hi_f, vurfile_ld_lo_t, vurfile_ld_lo_f,
	vurfile_st_t, vurfile_st_f, vurfile_vd_t, vurfile_vd_f);

	input		clk;
	input 	[4:0] 	st_rnum;      	// RD stage ST addr,
	input 	[4:0] 	xp_rnum;      	// RD stage ST XPOSE addr
	input 	[4:0] 	ld_rnum;      	// ACC stage LD addr
	input	[4:0]	vd;		// WB stage
	input		wbv_wr_en;	// write enable for dp results,WB stage
	input	[1:0]	bwe;		// load port byte write enable,WB stage
        input 		xpose;
        input 	[2:0] 	slice;
        input		wb_div_type;
	input	[2:0]	wb_div_elem;
   
	output	[31:0]	vurfile_ld_hi_t;
	output	[31:0]	vurfile_ld_hi_f;
	output	[31:0]	vurfile_ld_lo_t; 
	output	[31:0]	vurfile_ld_lo_f;
   	output	[31:0]  vurfile_st_t;
   	output	[31:0]  vurfile_st_f;

   	output	[31:0]  vurfile_vd_t; 
   	output	[31:0]  vurfile_vd_f; 

        wire	[4:0]	next_ld_rnum;
	wire	[31:0]	vurfile_ls;
	wire	[31:0]	vurfile_ls_bar;
	wire	[31:0]	vurfile_ld_hi_bar;
	wire	[31:0]	vurfile_ld_lo_bar;
	wire	[31:0]	vurfile_vd_bar;
	wire		write_this;



/*
*   	function [31:0] rNumDecode;
*	    input [4:0] rNum;
*	    integer i;
*	    integer bitValue;
*	    begin
*	      rNumDecode = 0;
*	      bitValue = 1;
*
*              for (i=0; i<32; i=i+1) begin
*                  if (rNum==i) rNumDecode = bitValue;
*	          bitValue = bitValue*2;
*              end
*            end
*   	endfunction
*/

	// *** Check read port timing (store, vs, vt) for Compass; t/f skew

	// store port

	wire	[4:0]	actual_xpst_rnum;
        wire	[2:0]	xpose_st_rnum;

	wire	vct_xposeadd0co_rd ;		/* carry out of bit 0 of xpose adder */
	wire	vct_xposeadd1co_rd ;		/* carry out of bit 1 of xpose adder */
	wire	vct_xposeadd2co_rd ;		/* carry out of bit 2 of xpose adder - unused */

	assign	vct_xposeadd0co_rd =	slice[0] && xp_rnum[0] ;

	xo02d1h vctxposeadd0rd	(
				  .z		(xpose_st_rnum[0]),
				  .a1		(xp_rnum[0]),
				  .a2		(slice[0])
				) ;

	ad01d1h	vctxposeadd1rd	(
				  .co		(vct_xposeadd1co_rd),
				  .s		(xpose_st_rnum[1]),
				  .a		(xp_rnum[1]),
				  .b		(slice[1]),
				  .ci		(vct_xposeadd0co_rd)
				) ;

	ad01d1h	vctxposeadd2rd	(
				  .co		(vct_xposeadd2co_rd),
				  .s		(xpose_st_rnum[2]),
				  .a		(xp_rnum[2]),
				  .b		(slice[2]),
				  .ci		(vct_xposeadd1co_rd)
				) ;

	mx21d1h	vctxposemx0rd	(
				  .z		(actual_xpst_rnum[0]),
				  .i0		(st_rnum[0]),
				  .i1		(xpose_st_rnum[0]),
				  .s		(xpose)
				) ;

	mx21d1h	vctxposemx1rd	(
				  .z		(actual_xpst_rnum[1]),
				  .i0		(st_rnum[1]),
				  .i1		(xpose_st_rnum[1]),
				  .s		(xpose)
				) ;

	mx21d1h	vctxposemx2rd	(
				  .z		(actual_xpst_rnum[2]),
				  .i0		(st_rnum[2]),
				  .i1		(xpose_st_rnum[2]),
				  .s		(xpose)
				) ;

	mx21d1h	vctxposemx3rd	(
				  .z		(actual_xpst_rnum[3]),
				  .i0		(st_rnum[3]),
				  .i1		(xp_rnum[3]),
				  .s		(xpose)
				) ;

	mx21d1h	vctxposemx4rd	(
				  .z		(actual_xpst_rnum[4]),
				  .i0		(st_rnum[4]),
				  .i1		(xp_rnum[4]),
				  .s		(xpose)
				) ;

regfile_decode decode_store (	.rNumdecode	(vurfile_st_t),  
				.rNumdecode_b	(vurfile_st_f),  
				.rNum		(actual_xpst_rnum) 
			  );


	// load port

        wire	[2:0]	xpose_ld_rnum;
	wire	[4:0]	actual_ld_rnum;

	wire	vct_loadadd0co_rd ;		/* carry out of bit 0 of load adder */
	wire	vct_loadadd1co_rd ;		/* carry out of bit 1 of load adder */
	wire	vct_loadadd2co_rd ;		/* carry out of bit 2 of load adder - unused */

	assign	vct_loadadd0co_rd =	slice[0] && ld_rnum[0] ;

	xo02d1h vctloadadd0rd	(
				  .z		(xpose_ld_rnum[0]),
				  .a1		(ld_rnum[0]),
				  .a2		(slice[0])
				) ;

	ad01d1h	vctloadadd1rd	(
				  .co		(vct_loadadd1co_rd),
				  .s		(xpose_ld_rnum[1]),
				  .a		(ld_rnum[1]),
				  .b		(slice[1]),
				  .ci		(vct_loadadd0co_rd)
				) ;

	ad01d1h	vctloadadd2rd	(
				  .co		(vct_loadadd2co_rd),
				  .s		(xpose_ld_rnum[2]),
				  .a		(ld_rnum[2]),
				  .b		(slice[2]),
				  .ci		(vct_loadadd1co_rd)
				) ;

	mx21d1h	vctloadmx0rd	(
				  .z		(actual_ld_rnum[0]),
				  .i0		(ld_rnum[0]),
				  .i1		(xpose_ld_rnum[0]),
				  .s		(xpose)
				) ;

	mx21d1h	vctloadmx1rd	(
				  .z		(actual_ld_rnum[1]),
				  .i0		(ld_rnum[1]),
				  .i1		(xpose_ld_rnum[1]),
				  .s		(xpose)
				) ;

	mx21d1h	vctloadmx2rd	(
				  .z		(actual_ld_rnum[2]),
				  .i0		(ld_rnum[2]),
				  .i1		(xpose_ld_rnum[2]),
				  .s		(xpose)
				) ;

	assign actual_ld_rnum[3] =  ld_rnum[3] ;

	assign actual_ld_rnum[4] =  ld_rnum[4] ;



        asdff #(5,0) ls_rnum_wr_x_ff(next_ld_rnum, actual_ld_rnum, clk, 1'b1);


regfile_decode decode_load (	.rNumdecode	(vurfile_ls),  
				.rNumdecode_b	(vurfile_ls_bar),  
				.rNum		(next_ld_rnum) 
			  );

/*
*	assign xpose_ls_rnum = ls_rnum[2:0] + slice;
*
*	assign actual_ls_rnum = xpose ? {ls_rnum[4:3],xpose_ls_rnum} : ls_rnum;
*
*       assign vurfile_ls = rNumDecode(next_ls_rnum);
*/

/*
*	assign vurfile_st_t = vurfile_ls;
*	assign vurfile_st_f = vurfile_ls_bar;
*/

        assign vurfile_ld_hi_bar = ~({32{bwe[1]}} & vurfile_ls);
        assign vurfile_ld_lo_bar = ~({32{bwe[0]}} & ~vurfile_ls_bar);
        rsp_lden32_t u_vurfile_ld_hi_t(
		.en_t	(vurfile_ld_hi_t), 
		.ld_bar	(vurfile_ld_hi_bar),
		.clk	(clk)
	);
        rsp_lden32_f u_vurfile_ld_hi_f(
		.en_f	(vurfile_ld_hi_f), 
		.ld_bar	(vurfile_ld_hi_bar),
		.clk	(clk)
	);
        rsp_lden32_t u_vurfile_ld_lo_t(
		.en_t(vurfile_ld_lo_t), 
		.ld_bar(vurfile_ld_lo_bar),
		.clk(clk)
	);
        rsp_lden32_f u_vurfile_ld_lo_f(
		.en_f(vurfile_ld_lo_f), 
		.ld_bar(vurfile_ld_lo_bar),
		.clk(clk)
	);

/*
*	The VS and VT address decoding is done in vuctl since it is
*	not dependent on slice and can be shared between the two
*	datapaths.
*/

	// VD port

	wire	[31:0]	vurfile_vd_dec;
	wire	[31:0]	vurfile_vd_dec_bar;


regfile_decode decode_vd (	.rNumdecode	(vurfile_vd_dec),  
				.rNumdecode_b	(vurfile_vd_dec_bar),  
				.rNum		(vd) 
			);
	assign write_this = wbv_wr_en && (!wb_div_type ||(wb_div_elem==slice));
        assign vurfile_vd_bar = ~(vurfile_vd_dec & {32{write_this}});
        rsp_lden32_t u_vurfile_vd_t(
		.en_t	(vurfile_vd_t), 
		.ld_bar	(vurfile_vd_bar),
		.clk	(clk)
	);
        rsp_lden32_f u_vurfile_vd_f(
		.en_f	(vurfile_vd_f), 
		.ld_bar	(vurfile_vd_bar),
		.clk	(clk)
	);

   endmodule
