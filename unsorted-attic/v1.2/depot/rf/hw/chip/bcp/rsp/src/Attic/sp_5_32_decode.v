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
// $Id: sp_5_32_decode.v,v 1.1 2002/05/21 23:55:44 berndt Exp $

// sp_5_32_decode.v: 5 to 32-bit decoder

`timescale 1ns / 10ps

module sp_5_32_decode (out_b, in);

	input	[4:0]	in ;
	output	[31:0]	out_b ;

	wire	[7:0]	dec_enable ;
	wire	[1:0]	inbuf ;

	dc38d2 rf_decode_1ststg (
				  .a0 (in[2]), .a1 (in[3]), .a2 (in[4]),
				  .z0n	(dec_enable[0]), .z1n (dec_enable[1]),
				  .z2n	(dec_enable[2]), .z3n (dec_enable[3]),
				  .z4n	(dec_enable[4]), .z5n (dec_enable[5]),
				  .z6n	(dec_enable[6]), .z7n (dec_enable[7])
				);

	ni01d5	address_buf0	(
				  .i (in[0]),	.z (inbuf[0])
				);

	ni01d5	address_buf1	(
				  .i (in[1]),	.z (inbuf[1])
				);

	de24d1	rf_decode_0to3	(
				  .a0 (inbuf[0]), .a1 (inbuf[1]), .en (dec_enable[0]),
				  .z0n (out_b[0]),	.z1n (out_b[1]),
				  .z2n (out_b[2]),	.z3n (out_b[3])
				);
	de24d1	rf_decode_4to7	(
				  .a0 (inbuf[0]), .a1 (inbuf[1]), .en (dec_enable[1]),
				  .z0n (out_b[4]),	.z1n (out_b[5]),
				  .z2n (out_b[6]),	.z3n (out_b[7])
				);

	de24d1	rf_decode_8to11	(
				  .a0 (inbuf[0]), .a1 (inbuf[1]), .en (dec_enable[2]),
				  .z0n (out_b[8]),	.z1n (out_b[9]),
				  .z2n (out_b[10]),	.z3n (out_b[11])
				);
	de24d1	rf_decode_12to15 (
				  .a0 (inbuf[0]), .a1 (inbuf[1]), .en (dec_enable[3]),
				  .z0n (out_b[12]),	.z1n (out_b[13]),
				  .z2n (out_b[14]),	.z3n (out_b[15])
				);

	de24d1	rf_decode_16to19 (
				  .a0 (inbuf[0]), .a1 (inbuf[1]), .en (dec_enable[4]),
				  .z0n (out_b[16]),	.z1n (out_b[17]),
				  .z2n (out_b[18]),	.z3n (out_b[19])
				);

	de24d1	rf_decode_20to23 (
				  .a0 (inbuf[0]), .a1 (inbuf[1]), .en (dec_enable[5]),
				  .z0n (out_b[20]),	.z1n (out_b[21]),
				  .z2n (out_b[22]),	.z3n (out_b[23])
				);

	de24d1	rf_decode_24to27 (
				  .a0 (inbuf[0]),  .a1 (inbuf[1]),  .en (dec_enable[6]),
				  .z0n (out_b[24]),	.z1n (out_b[25]),
				  .z2n (out_b[26]),	.z3n (out_b[27])
				);

	de24d1	rf_decode_28to31 (
				  .a0 (inbuf[0]), .a1 (inbuf[1]), .en (dec_enable[7]),
				  .z0n (out_b[28]),	.z1n (out_b[29]),
				  .z2n (out_b[30]),	.z3n (out_b[31])
				);

endmodule
