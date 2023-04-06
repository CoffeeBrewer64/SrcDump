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
// gi_mixe.v Frank Berndt
// aes forward column mixer;
//
//  CVS Log
//
//  $Id: gi_mixe.v,v 1.3 2005/05/18 21:52:39 nima Exp $
//
//  $Date: 2005/05/18 21:52:39 $
//  $Revision: 1.3 $
//  $Author: nima $
//  $Locker:  $
//  $State: Exp $
//
//  Change History:
//               $Log: gi_mixe.v,v $
//               Revision 1.3  2005/05/18 21:52:39  nima
//               ran dos2unix on all files
//
//               Revision 1.2  2005/05/18 21:28:17  nima
//               added the BroadOn banner
//
//
//
//
//

module gi_mixe ( i, o );
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

	// mix each byte;

	wire [7:0] i3, i2, i1, i0;
	wire [7:0] x3, x2, x1, x0;

	assign i3 = i[31:24];
	assign i2 = i[23:16];
	assign i1 = i[15:8];
	assign i0 = i[7:0];

	assign x3 = x(i3);
	assign x2 = x(i2);
	assign x1 = x(i1);
	assign x0 = x(i0);

	// final product;

	assign o[31:24] = x3^x2^i2^i1^i0;
	assign o[23:16] = i3^x2^x1^i1^i0;
	assign o[15:8]  = i3^i2^x1^x0^i0;
	assign o[7:0]   = x3^i3^i2^i1^x0;

endmodule

