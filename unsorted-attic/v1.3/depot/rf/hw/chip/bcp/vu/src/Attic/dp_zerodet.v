// Module instances modified by /home/rws/workarea/rf/sw/bbplayer/tools/necprimfix 
//
//    1 instance of nd04d1 changed to j_nd04.
//    1 instance of ni01d5 changed to j_ni01.
//    4 instances of nr04d1 changed to j_nr04.
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
*  module:	dp_zerodet.v						*
*  description:	16 bit buffer using j_ni01 cells			*
*									*
*  designer:	Brian Ferguson						*
*  date:	4/12/95							*
*									*
*************************************************************************
*/

// $Id: dp_zerodet.v,v 1.2 2002/11/13 02:11:42 rws Exp $

module dp_zerodet (
			input_data,
			out
		 ) ;

input	[15:0]	input_data ;

output	out ;

	wire	[3:0]	intzerodet;
	wire	out ;
	

	j_nr04	zerodet0to3	(	.zn		(intzerodet[0]),
					.a1		(input_data[3]),
					.a2		(input_data[2]),
					.a3		(input_data[1]),
					.a4		(input_data[0])
				) ;

	j_nr04	zerodet4to7	(	.zn		(intzerodet[1]),
					.a1		(input_data[7]),
					.a2		(input_data[6]),
					.a3		(input_data[5]),
					.a4		(input_data[4])
				) ;

	j_nr04	zerodet8to11	(	.zn		(intzerodet[2]),
					.a1		(input_data[11]),
					.a2		(input_data[10]),
					.a3		(input_data[9]),
					.a4		(input_data[8])
				) ;

	j_nr04	zerodet12to15	(	.zn		(intzerodet[3]),
					.a1		(input_data[15]),
					.a2		(input_data[14]),
					.a3		(input_data[13]),
					.a4		(input_data[12])
				) ;

	j_nd04	zerodetfinal	(	.zn		(out_inv),
					.a1		(intzerodet[0]),
					.a2		(intzerodet[1]),
					.a3		(intzerodet[2]),
					.a4		(intzerodet[3])
				) ;

/*
*	in01d7	zerodetinv	(	.i		(out_inv),
*					.zn		(out)
*				) ;
*/

	assign	out =	!out_inv;

endmodule  //  dp_zerodet


