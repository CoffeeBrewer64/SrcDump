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
*  module:	dp_tribuf16.v						*
*  description:	16 bit tri-state buffer using nt01d5 cells		*
*									*
*  designer:	Brian Ferguson						*
*  date:	3/21/95							*
*									*
*************************************************************************
*/

// $Id: dp_tribuf16.v,v 1.1 2002/05/21 23:55:45 berndt Exp $

module dp_tribuf16 (
			input_data,
			enable,
			output_data
		    ) ;

input	[15:0]	input_data ;
input	enable ;

output	[15:0]	output_data ;

	wire	buffered_enable ;

	ni01d5  buf_enable (
				.z		(buffered_enable),
				.i		(enable)
			   ) ;


	nt01d5	tribuf_b0 (	.z		(output_data[0]),
				.oe		(buffered_enable),
				.i		(input_data[0])
		          ) ;


	nt01d5	tribuf_b1 (	.z		(output_data[1]),
				.oe		(buffered_enable),
				.i		(input_data[1])
		          ) ;


	nt01d5	tribuf_b2 (	.z		(output_data[2]),
				.oe		(buffered_enable),
				.i		(input_data[2])
		          ) ;


	nt01d5	tribuf_b3 (	.z		(output_data[3]),
				.oe		(buffered_enable),
				.i		(input_data[3])
		          ) ;


	nt01d5	tribuf_b4 (	.z		(output_data[4]),
				.oe		(buffered_enable),
				.i		(input_data[4])
		          ) ;


	nt01d5	tribuf_b5 (	.z		(output_data[5]),
				.oe		(buffered_enable),
				.i		(input_data[5])
		          ) ;


	nt01d5	tribuf_b6 (	.z		(output_data[6]),
				.oe		(buffered_enable),
				.i		(input_data[6])
		          ) ;


	nt01d5	tribuf_b7 (	.z		(output_data[7]),
				.oe		(buffered_enable),
				.i		(input_data[7])
		          ) ;


	nt01d5	tribuf_b8 (	.z		(output_data[8]),
				.oe		(buffered_enable),
				.i		(input_data[8])
		          ) ;


	nt01d5	tribuf_b9 (	.z		(output_data[9]),
				.oe		(buffered_enable),
				.i		(input_data[9])
		          ) ;


	nt01d5	tribuf_b10 (	.z		(output_data[10]),
				.oe		(buffered_enable),
				.i		(input_data[10])
		           ) ;


	nt01d5	tribuf_b11 (	.z		(output_data[11]),
				.oe		(buffered_enable),
				.i		(input_data[11])
		           ) ;


	nt01d5	tribuf_b12 (	.z		(output_data[12]),
				.oe		(buffered_enable),
				.i		(input_data[12])
		           ) ;


	nt01d5	tribuf_b13 (	.z		(output_data[13]),
				.oe		(buffered_enable),
				.i		(input_data[13])
		           ) ;


	nt01d5	tribuf_b14 (	.z		(output_data[14]),
				.oe		(buffered_enable),
				.i		(input_data[14])
		           ) ;


	nt01d5	tribuf_b15 (	.z		(output_data[15]),
				.oe		(buffered_enable),
				.i		(input_data[15])
		            ) ;

endmodule  //  dp_tribuf16


