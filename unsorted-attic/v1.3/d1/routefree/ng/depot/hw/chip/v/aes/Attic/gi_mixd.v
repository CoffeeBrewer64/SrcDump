d1 94
a94 91
/*
 *               Copyright (C) 2003-2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in part,
 *  without the prior written consent of BroadOn Communications Corp.
 *
 */ 
// gi_mixd.v Frank Berndt
// aes inverse column mixer;
//
//  CVS Log
//
//  $Id:  $
//
//  $Date:  $
//  $Revision:  $
//  $Author: nima $
//  $Locker:  $
//  $State: Exp $
//
//  Change History:
//               $Log:  $
//
//
//
//






`timescale 1ps / 1ps

module gi_mixd ( i, o );
	input [31:0] i;			// input word;
	output [31:0] o;		// output word;

	// byte mixer;
	// x = (b << 1) ^ (8'h1b & {8{b[7]}});

	function [7:0] x;
		input [7:0] b;
		begin
			x = { b[6:4], b[3]^b[7], b[2]^b[7], b[1], b[0]^b[7], b[7] };
		end
	endfunction

	// partial rounds;

	wire [7:0] i31, i32, i34, i38;
	wire [7:0] i21, i22, i24, i28;
	wire [7:0] i11, i12, i14, i18;
	wire [7:0] i01, i02, i04, i08;

	assign i31 = i[31:24];
	assign i32 = x(i31);
	assign i34 = x(i32);
	assign i38 = x(i34);

	assign i21 = i[23:16];
	assign i22 = x(i21);
	assign i24 = x(i22);
	assign i28 = x(i24);

	assign i11 = i[15:8];
	assign i12 = x(i11);
	assign i14 = x(i12);
	assign i18 = x(i14);

	assign i01 = i[7:0];
	assign i02 = x(i01);
	assign i04 = x(i02);
	assign i08 = x(i04);

	// final product;
	//	[31:24]	e b d 9
	//	[23:16]	9 e b d
	//	[15:8]	d 9 e b
	//	[7:0]	b d 9 e

	assign o[31:24] = i38^i34^i32 ^ i28^i22^i21 ^ i18^i14^i11 ^ i08^i01;
	assign o[23:16] = i38^i31     ^ i28^i24^i22 ^ i18^i12^i11 ^ i08^i04^i01;
	assign o[15:8]  = i38^i34^i31 ^ i28^i21     ^ i18^i14^i12 ^ i08^i02^i01;
	assign o[7:0]   = i38^i32^i31 ^ i28^i24^i21 ^ i18^i11     ^ i08^i04^i02;

endmodule

