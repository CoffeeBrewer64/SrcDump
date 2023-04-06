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
// gi_kbuf.v Frank Berndt
// aes decryption key buffer;
//
//  CVS Log
//
//  $Id: gi_kbuf.v,v 1.3 2005/05/18 21:52:39 nima Exp $
//
//  $Date: 2005/05/18 21:52:39 $
//  $Revision: 1.3 $
//  $Author: nima $
//  $Locker:  $
//  $State: Exp $
//
//  Change History:
//               $Log: gi_kbuf.v,v $
//               Revision 1.3  2005/05/18 21:52:39  nima
//               ran dos2unix on all files
//
//               Revision 1.2  2005/05/18 21:28:17  nima
//               added the BroadOn banner
//
//
//
//
// :set tabstop=4

`timescale 1ps/1ps

module gi_kbuf (
	clk, load, shift, kin, kout
);
	input clk;				// system clock;
	input load;				// load expanded key word;
	input shift;			// shift one round;
	input [127:0] kin;		// expanded key to load;
	output [127:0] kout;	// expanded key for core;

	// implemented as circular shift register to reduce logic;
	// which means that abort is only possible after an entire
	// data block (16 bytes) has been decrypted; aborting in
	// the middle would leave expanded key messed up;
	// XXX is sram smaller than flops?

	reg [10:0] kl;				// buffered load;
	reg [10:0] ks;				// buffered shift;
	reg [127:0] k0, k1, k2,	k3, k4, k5, k6, k7, k8, k9, k10;

	always @(posedge clk)
	begin
		kl <= {11{load}};
		ks <= {11{shift}};
		k10 <= kl[10]? kin : ks[10]? k9  : k10;
		k9  <= kl[9]?  k10 : ks[9]?  k8  : k9;
		k8  <= kl[8]?  k9  : ks[8]?  k7  : k8;
		k7  <= kl[7]?  k8  : ks[7]?  k6  : k7;
		k6  <= kl[6]?  k7  : ks[6]?  k5  : k6;
		k5  <= kl[5]?  k6  : ks[5]?  k4  : k5;
		k4  <= kl[4]?  k5  : ks[4]?  k3  : k4;
		k3  <= kl[3]?  k4  : ks[3]?  k2  : k3;
		k2  <= kl[2]?  k3  : ks[2]?  k1  : k2;
		k1  <= kl[1]?  k2  : ks[1]?  k0  : k1;
		k0  <= kl[0]?  k1  : ks[0]?  k10 : k0;
	end

	assign kout = k10;

endmodule

