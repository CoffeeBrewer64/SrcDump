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

// $Id: regfile_decode.v,v 1.1 2002/05/21 23:55:44 berndt Exp $

// regfile_decode.v:	register address decode, 5->32,

`timescale 1ns / 10ps

module regfile_decode
	(
		rNum, 
		rNumdecode,
		rNumdecode_b
	);

	input	[4:0]	rNum ;
	output	[31:0]	rNumdecode ;
	output	[31:0]	rNumdecode_b ;

	wire	[7:0]	dec_enable ;
	wire	rNumbuf1 ;
	wire	rNumbuf2 ;
	wire	rNumbufcopy1 ;
	wire	rNumbufcopy2 ;

	wire	[31:0]	Numdecode ;
	wire	[31:0]	Numdecode_b ;

	dc38d2 rf_decode_1ststg (
				  .a0 (rNum[0]), .a1 (rNum[3]), .a2 (rNum[4]),
				  .z0n	(dec_enable[0]), .z1n (dec_enable[1]),
				  .z2n	(dec_enable[2]), .z3n (dec_enable[3]),
				  .z4n	(dec_enable[4]), .z5n (dec_enable[5]),
				  .z6n	(dec_enable[6]), .z7n (dec_enable[7])
				);

	ni01d5	address_buf2	(
				  .i (rNum[2]),	.z (rNumbuf2)
				);

	ni01d5	address_buf1	(
				  .i (rNum[1]),	.z (rNumbuf1)
				);

	ni01d5	address_bufcopy2 (
				  .i (rNum[2]),	.z (rNumbufcopy2)
				);

	ni01d5	address_bufcopy1 (
				  .i (rNum[1]),	.z (rNumbufcopy1)
				);

	de28d1	rf_decode_0to6	(
				  .a0 (rNumbuf1), .a1 (rNumbuf2), .en (dec_enable[0]),
				  .z0 (Numdecode[0]),	.z1 (Numdecode[2]),
				  .z2 (Numdecode[4]),	.z3 (Numdecode[6]),
				  .z0n (Numdecode_b[0]),	.z1n (Numdecode_b[2]),
				  .z2n (Numdecode_b[4]),	.z3n (Numdecode_b[6])
				);

	de28d1	rf_decode_1to7	(
				  .a0 (rNumbuf1), .a1 (rNumbuf2), .en (dec_enable[1]),
				  .z0 (Numdecode[1]),	.z1 (Numdecode[3]),
				  .z2 (Numdecode[5]),	.z3 (Numdecode[7]),
				  .z0n (Numdecode_b[1]),	.z1n (Numdecode_b[3]),
				  .z2n (Numdecode_b[5]),	.z3n (Numdecode_b[7])
				);

	de28d1	rf_decode_8to14	(
				  .a0 (rNumbuf1), .a1 (rNumbuf2), .en (dec_enable[2]),
				  .z0 (Numdecode[8]),	.z1 (Numdecode[10]),
				  .z2 (Numdecode[12]),	.z3 (Numdecode[14]),
				  .z0n (Numdecode_b[8]),	.z1n (Numdecode_b[10]),
				  .z2n (Numdecode_b[12]),	.z3n (Numdecode_b[14])
				);

	de28d1	rf_decode_9to15 (
				  .a0 (rNumbuf1), .a1 (rNumbuf2), .en (dec_enable[3]),
				  .z0 (Numdecode[9]),	.z1 (Numdecode[11]),
				  .z2 (Numdecode[13]),	.z3 (Numdecode[15]),
				  .z0n (Numdecode_b[9]),	.z1n (Numdecode_b[11]),
				  .z2n (Numdecode_b[13]),	.z3n (Numdecode_b[15])
				);

	de28d1	rf_decode_16to22 (
				  .a0 (rNumbufcopy1), .a1 (rNumbufcopy2), .en (dec_enable[4]),
				  .z0 (Numdecode[16]),	.z1 (Numdecode[18]),
				  .z2 (Numdecode[20]),	.z3 (Numdecode[22]),
				  .z0n (Numdecode_b[16]),	.z1n (Numdecode_b[18]),
				  .z2n (Numdecode_b[20]),	.z3n (Numdecode_b[22])
				);

	de28d1	rf_decode_17to23 (
				  .a0 (rNumbufcopy1), .a1 (rNumbufcopy2), .en (dec_enable[5]),
				  .z0 (Numdecode[17]),	.z1 (Numdecode[19]),
				  .z2 (Numdecode[21]),	.z3 (Numdecode[23]),
				  .z0n (Numdecode_b[17]),	.z1n (Numdecode_b[19]),
				  .z2n (Numdecode_b[21]),	.z3n (Numdecode_b[23])
				);

	de28d1	rf_decode_24to30 (
				  .a0 (rNumbufcopy1),  .a1 (rNumbufcopy2),  .en (dec_enable[6]),
				  .z0 (Numdecode[24]),	.z1 (Numdecode[26]),
				  .z2 (Numdecode[28]),	.z3 (Numdecode[30]),
				  .z0n (Numdecode_b[24]),	.z1n (Numdecode_b[26]),
				  .z2n (Numdecode_b[28]),	.z3n (Numdecode_b[30])
				);

	de28d1	rf_decode_25to31 (
				  .a0 (rNumbufcopy1), .a1 (rNumbufcopy2), .en (dec_enable[7]),
				  .z0 (Numdecode[25]),	.z1 (Numdecode[27]),
				  .z2 (Numdecode[29]),	.z3 (Numdecode[31]),
				  .z0n (Numdecode_b[25]),	.z1n (Numdecode_b[27]),
				  .z2n (Numdecode_b[29]),	.z3n (Numdecode_b[31])
				);

/*
*	This following code was done to ensure the output address was buffered 
*	with an inverter rather than a non-inverter since this helps with
*	timing.
*/

	assign	rNumdecode =	~Numdecode_b ;

	assign	rNumdecode_b =	~Numdecode ;


endmodule

