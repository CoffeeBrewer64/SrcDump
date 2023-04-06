// Module instances modified by /home/rws/workarea/rf/sw/bbplayer/tools/necprimfix 
//
//    17 instances of ni01d5 changed to j_ni01.
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
*  module:	dp_buf16.v						*
*  description:	16 bit buffer using j_ni01 cells			*
*									*
*  designer:	Brian Ferguson						*
*  date:	3/21/95							*
*									*
*************************************************************************
*/

// $Id: dp_buf16.v,v 1.2 2002/11/13 02:11:42 rws Exp $

module dp_buf16 (
			input_data,
			output_data
		 ) ;

input	[15:0]	input_data ;

output	[15:0]	output_data ;


	j_ni01	buf_b0 (	.z		(output_data[0]),
				.i		(input_data[0])
		       ) ;


	j_ni01	buf_b1 (	.z		(output_data[1]),
				.i		(input_data[1])
		       ) ;


	j_ni01	buf_b2 (	.z		(output_data[2]),
				.i		(input_data[2])
		       ) ;


	j_ni01	buf_b3 (	.z		(output_data[3]),
				.i		(input_data[3])

		       ) ;


	j_ni01	buf_b4 (	.z		(output_data[4]),
				.i		(input_data[4])
		       ) ;


	j_ni01	buf_b5 (	.z		(output_data[5]),
				.i		(input_data[5])
		       ) ;


	j_ni01	buf_b6 (	.z		(output_data[6]),
				.i		(input_data[6])
		       ) ;


	j_ni01	buf_b7 (	.z		(output_data[7]),
				.i		(input_data[7])
		       ) ;


	j_ni01	buf_b8 (	.z		(output_data[8]),
				.i		(input_data[8])
		       ) ;


	j_ni01	buf_b9 (	.z		(output_data[9]),
				.i		(input_data[9])
		       ) ;


	j_ni01	buf_b10 (	.z		(output_data[10]),
				.i		(input_data[10])
		        ) ;


	j_ni01	buf_b11 (	.z		(output_data[11]),
				.i		(input_data[11])
		        ) ;


	j_ni01	buf_b12 (	.z		(output_data[12]),
				.i		(input_data[12])
		        ) ;


	j_ni01	buf_b13 (	.z		(output_data[13]),
				.i		(input_data[13])
		        ) ;


	j_ni01	buf_b14 (	.z		(output_data[14]),
				.i		(input_data[14])
		        ) ;


	j_ni01	buf_b15 (	.z		(output_data[15]),
				.i		(input_data[15])
		        ) ;



endmodule  //  dp_buf16


