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
*  module:	dp_reg16.v						*
*  description:	16 bit register using cell dfntnh.			*
*									*
*  designer:	Brian Ferguson						*
*  date:	3/17/95							*
*									*
*************************************************************************
*/

// $Id: dp_reg16.v,v 1.1 2002/05/21 23:55:45 berndt Exp $


module dp_reg16 (
			clk,
			input_data,
			output_data
		   ) ;

input	clk ;
input	[15:0]	input_data ;

output	[15:0]	output_data ;


	dfntnq reg_b0 (
			.cp		(clk),
			.d		(input_data[0]),
			.q		(output_data[0])
		      ) ;


	dfntnq reg_b1 (
			.cp		(clk),
			.d		(input_data[1]),
			.q		(output_data[1])
		      ) ;


	dfntnq reg_b2 (
			.cp		(clk),
			.d		(input_data[2]),
			.q		(output_data[2])
		      ) ;


	dfntnq reg_b3 (
			.cp		(clk),
			.d		(input_data[3]),
			.q		(output_data[3])
		      ) ;


	dfntnq reg_b4 (
			.cp		(clk),
			.d		(input_data[4]),
			.q		(output_data[4])
		      ) ;


	dfntnq reg_b5 (
			.cp		(clk),
			.d		(input_data[5]),
			.q		(output_data[5])
		      ) ;


	dfntnq reg_b6 (
			.cp		(clk),
			.d		(input_data[6]),
			.q		(output_data[6])
		      ) ;


	dfntnq reg_b7 (
			.cp		(clk),
			.d		(input_data[7]),
			.q		(output_data[7])
		      ) ;


	dfntnq reg_b8 (
			.cp		(clk),
			.d		(input_data[8]),
			.q		(output_data[8])
		      ) ;


	dfntnq reg_b9 (
			.cp		(clk),
			.d		(input_data[9]),
			.q		(output_data[9])
		      ) ;


	dfntnq reg_b10 (
			.cp		(clk),
			.d		(input_data[10]),
			.q		(output_data[10])
		       ) ;


	dfntnq reg_b11 (
			.cp		(clk),
			.d		(input_data[11]),
			.q		(output_data[11])
		       ) ;


	dfntnq reg_b12 (
			.cp		(clk),
			.d		(input_data[12]),
			.q		(output_data[12])
		       ) ;


	dfntnq reg_b13 (
			.cp		(clk),
			.d		(input_data[13]),
			.q		(output_data[13])
		      ) ;


	dfntnq reg_b14 (
			.cp		(clk),
			.d		(input_data[14]),
			.q		(output_data[14])
		      ) ;


	dfntnq reg_b15 (
			.cp		(clk),
			.d		(input_data[15]),
			.q		(output_data[15])
		      ) ;


endmodule  //  dp_reg16


