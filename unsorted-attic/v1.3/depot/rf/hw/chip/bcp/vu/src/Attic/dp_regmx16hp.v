// Module instances modified by /home/rws/workarea/rf/sw/bbplayer/tools/necprimfix 
//
//    16 instances of dfntnq2 changed to j_dfntnq2.
//    17 instances of me41d1h changed to j_me41.
//

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

/*
*************************************************************************
*									*
*  Project Reality							*
*									*
*  module:	dp_regmx16hp.v						*
*  description:	16 bit register with 4 to 1 mux to implement		*
*		2 to 1 data mux, reset and clock enable functionalty.	*
*		If both selects are low or both high then register	*
*		its old value.						*
*									*
*		The mux cell used is the high performance j_me41 cells.*
*									*
*  designer:	Brian Ferguson						*
*  date:	3/17/95							*
*									*
*************************************************************************
*/

// $Id: dp_regmx16hp.v,v 1.2 2002/11/13 02:11:42 rws Exp $


module dp_regmx16hp (
			clk,
			input0, input1,
			select,
			output_data
		   ) ;

input	clk ;
input	[15:0]	input0 ;
input	[15:0]	input1 ;
input	[1:0]	select ;

output	[15:0]	output_data ;


wire	[15:0]	reg_data_in ;	// data selected as input to register

	j_me41	mx_b0 (	.z		(reg_data_in[0]),
			.i0		(output_data[0]),
			.i1		(input0[0]),
			.i2		(input1[0]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b1 (	.z		(reg_data_in[1]),
			.i0		(output_data[1]),
			.i1		(input0[1]),
			.i2		(input1[1]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b2 (	.z		(reg_data_in[2]),
			.i0		(output_data[2]),
			.i1		(input0[2]),
			.i2		(input1[2]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b3 (	.z		(reg_data_in[3]),
			.i0		(output_data[3]),
			.i1		(input0[3]),
			.i2		(input1[3]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b4 (	.z		(reg_data_in[4]),
			.i0		(output_data[4]),
			.i1		(input0[4]),
			.i2		(input1[4]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b5 (	.z		(reg_data_in[5]),
			.i0		(output_data[5]),
			.i1		(input0[5]),
			.i2		(input1[5]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b6 (	.z		(reg_data_in[6]),
			.i0		(output_data[6]),
			.i1		(input0[6]),
			.i2		(input1[6]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b7 (	.z		(reg_data_in[7]),
			.i0		(output_data[7]),
			.i1		(input0[7]),
			.i2		(input1[7]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b8 (	.z		(reg_data_in[8]),
			.i0		(output_data[8]),
			.i1		(input0[8]),
			.i2		(input1[8]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b9 (	.z		(reg_data_in[9]),
			.i0		(output_data[9]),
			.i1		(input0[9]),
			.i2		(input1[9]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b10 (.z		(reg_data_in[10]),
			.i0		(output_data[10]),
			.i1		(input0[10]),
			.i2		(input1[10]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b11 (.z		(reg_data_in[11]),
			.i0		(output_data[11]),
			.i1		(input0[11]),
			.i2		(input1[11]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b12 (.z		(reg_data_in[12]),
			.i0		(output_data[12]),
			.i1		(input0[12]),
			.i2		(input1[12]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b13 (.z		(reg_data_in[13]),
			.i0		(output_data[13]),
			.i1		(input0[13]),
			.i2		(input1[13]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		      ) ;


	j_me41	mx_b14 (.z		(reg_data_in[14]),
			.i0		(output_data[14]),
			.i1		(input0[14]),
			.i2		(input1[14]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		       ) ;


	j_me41	mx_b15 (.z		(reg_data_in[15]),
			.i0		(output_data[15]),
			.i1		(input0[15]),
			.i2		(input1[15]),
			.i3		(1'b0),
			.en		(1'b0),
			.s0		(select[0]),
			.s1		(select[1])
		       ) ;



	j_dfntnq2 reg_b0 (
			.cp		(clk),
			.d		(reg_data_in[0]),
			.q		(output_data[0])
		      ) ;


	j_dfntnq2 reg_b1 (
			.cp		(clk),
			.d		(reg_data_in[1]),
			.q		(output_data[1])
		      ) ;


	j_dfntnq2 reg_b2 (
			.cp		(clk),
			.d		(reg_data_in[2]),
			.q		(output_data[2])
		      ) ;


	j_dfntnq2 reg_b3 (
			.cp		(clk),
			.d		(reg_data_in[3]),
			.q		(output_data[3])
		      ) ;


	j_dfntnq2 reg_b4 (
			.cp		(clk),
			.d		(reg_data_in[4]),
			.q		(output_data[4])
		      ) ;


	j_dfntnq2 reg_b5 (
			.cp		(clk),
			.d		(reg_data_in[5]),
			.q		(output_data[5])
		      ) ;


	j_dfntnq2 reg_b6 (
			.cp		(clk),
			.d		(reg_data_in[6]),
			.q		(output_data[6])
		      ) ;


	j_dfntnq2 reg_b7 (
			.cp		(clk),
			.d		(reg_data_in[7]),
			.q		(output_data[7])
		      ) ;


	j_dfntnq2 reg_b8 (
			.cp		(clk),
			.d		(reg_data_in[8]),
			.q		(output_data[8])
		      ) ;


	j_dfntnq2 reg_b9 (
			.cp		(clk),
			.d		(reg_data_in[9]),
			.q		(output_data[9])
		      ) ;


	j_dfntnq2 reg_b10 (
			.cp		(clk),
			.d		(reg_data_in[10]),
			.q		(output_data[10])
		       ) ;


	j_dfntnq2 reg_b11 (
			.cp		(clk),
			.d		(reg_data_in[11]),
			.q		(output_data[11])
		       ) ;


	j_dfntnq2 reg_b12 (
			.cp		(clk),
			.d		(reg_data_in[12]),
			.q		(output_data[12])
		       ) ;


	j_dfntnq2 reg_b13 (
			.cp		(clk),
			.d		(reg_data_in[13]),
			.q		(output_data[13])
		      ) ;


	j_dfntnq2 reg_b14 (
			.cp		(clk),
			.d		(reg_data_in[14]),
			.q		(output_data[14])
		      ) ;


	j_dfntnq2 reg_b15 (
			.cp		(clk),
			.d		(reg_data_in[15]),
			.q		(output_data[15])
		      ) ;


endmodule  //  dp_regmx16hp


