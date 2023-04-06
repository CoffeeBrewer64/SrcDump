// Module instances modified by /home/rws/workarea/rf/sw/bbplayer/tools/necprimfix 
//
//    4 instances of nd04d1 changed to j_nd04.
//    1 instance of ni01d5 changed to j_ni01.
//    1 instance of nr04d2 changed to j_nr04.
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
*  module:	dp_onedet.v						*
*  description:	16 bit buffer using j_ni01 cells			*
*									*
*  designer:	Brian Ferguson						*
*  date:	4/12/95							*
*									*
*************************************************************************
*/

// $Id: dp_onedet.v,v 1.2 2002/11/13 02:11:42 rws Exp $

module dp_onedet (
			input_data,
			out
		 ) ;

input	[15:0]	input_data ;

output	out ;

	wire	[3:0]	intonedet;
	

	j_nd04	onedet0to3	(	.zn		(intonedet[0]),
					.a1		(input_data[3]),
					.a2		(input_data[2]),
					.a3		(input_data[1]),
					.a4		(input_data[0])
				) ;

	j_nd04	onedet4to7	(	.zn		(intonedet[1]),
					.a1		(input_data[7]),
					.a2		(input_data[6]),
					.a3		(input_data[5]),
					.a4		(input_data[4])
				) ;

	j_nd04	onedet8to11	(	.zn		(intonedet[2]),
					.a1		(input_data[11]),
					.a2		(input_data[10]),
					.a3		(input_data[9]),
					.a4		(input_data[8])
				) ;

	j_nd04	onedet12to15	(	.zn		(intonedet[3]),
					.a1		(input_data[15]),
					.a2		(input_data[14]),
					.a3		(input_data[13]),
					.a4		(input_data[12])
				) ;

	j_nr04	onedetfinal	(	.zn		(out),
					.a1		(intonedet[3]),
					.a2		(intonedet[2]),
					.a3		(intonedet[1]),
					.a4		(intonedet[0])
				) ;


endmodule  //  dp_onedet


