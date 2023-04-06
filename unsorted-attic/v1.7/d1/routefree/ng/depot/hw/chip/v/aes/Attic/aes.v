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
// Filename        : aes.v
// Description     : This blocks performs the actual encryption, decryption
// 		     logic
//
//
//                   Nima Nikuie  --May 4 2005 
//  CVS Log
//
//  $Id: aes.v,v 1.6 2005/05/18 22:42:08 nima Exp $
//
//  $Date: 2005/05/18 22:42:08 $
//  $Revision: 1.6 $
//  $Author: nima $
//  $Locker:  $
//  $State: Exp $
//
//  Change History:
//               $Log: aes.v,v $
//               Revision 1.6  2005/05/18 22:42:08  nima
//               fixed typo
//
//               Revision 1.5  2005/05/18 21:26:34  nima
//               cleand up ^M chars
//
//               Revision 1.4  2005/05/18 21:19:51  nima
//               changed sbox to function
//
//
//
//
//
//
//               
`timescale 1ps/1ps
`include "ahb_fdl_defs.v"



module aes(clk, rst, 
	       TextLoad, TextRaw, TextXfd, TextTrdy, FirstPkt,    // aesmgr.v
	       ExpKeyTrdy, ExpKeyIrdy, SecretKey, aes_iv, Cmd    // genmgr.v
	       );


   input		clk, rst;


   // interface to the AES Block
   input [127:0] 	TextRaw     ;
   input 		TextLoad ;
   output [127:0] 	TextXfd   ;
   output 		TextTrdy ;
   input 		FirstPkt ;

   // interface to the genmgr.v  Block
   output 		ExpKeyTrdy;
   input 		ExpKeyIrdy ;
   input [127:0] 	SecretKey ;
   input [127:0] 	aes_iv  ;
   input [1:0] 		Cmd    ; //  0X= NOP;  10=Encrypt ;   11=Decrypt

   // aes-128 key expander;
   // cmd tells aes what to do:  0x=NOP (loop the data);  10=Enc; 11=Dec
   // one key-expander for decryption
   // encryption does not need buffer, does live key expansion;
   // can only perform one of the tasks above indicated by cmd.

   // the encryption key and initial IV are both input to this block
   // buffer is also used for expansion of decryption keys;
   // flush out key during reset;
   // 
   // expansion of decryption keys;
   // started by the assertion of ExpKeyIrdy
   // nothing to expand for encryption key;
   // by design, ExpKeyIrdy will never come during an actual enc/dec
   // session.  Comes once at the begining of every dec session
   

   wire 		ke_end;				// key expansion done;
   wire 		ke_start;				// start key expansion;
   reg 			ke_load;				// Load phase of key_buff
   reg 			ke_go  ;				// 
   reg 			ExpKeyIrdy_d  ;				// 
   wire 		ke_set;				// load key from k_buf;
   wire 		ke_en;				// starts key expansion for Enc. sequence.

   reg 			ExpKeyTrdy  ;				// 
   reg	 		TextTrdy ;

   always @(posedge clk) begin
      ExpKeyTrdy   <= ~rst   & ke_end;
      ExpKeyIrdy_d <=  ExpKeyIrdy    ;
      ke_load      <= ~ke_end  & (ke_load | ke_start);
      ke_go        <=  ke_load ; 
   end
   

   assign ke_start = ExpKeyIrdy & ~ExpKeyIrdy_d ; //pulse at rising edge of Irdy
   assign ke_set = ~(ke_go | ke_en);

   // actual key expander;
   // expands key into 11x128 bits;
   // use sbox function 
   // encryption key has to be reloaded before expansion is started.
   // rcon logic has been written as shift register,
   // from which key expansion state is decoded;
   // assert ke_set when idle to reduce toggling;


   reg [31:0] kw0, kw1, kw2, kw3;
   wire [31:0] kn0, kn1, kn2, kn3;
   wire [127:0] kexp;			// expanded key;
   wire [31:0] 	ksr;			// sub ^ rcon;
   reg [31:24] 	krc;			// rcon;
   wire [31:0] 	ksub;			// sbox substitutions;
   wire [127:0] k_buf = SecretKey ;

   assign 	ke_end = (krc[29:28] == 2'b11);	// 'h36;

   always @(posedge clk)
     begin
	kw3 <= ke_set? k_buf[127:96] : kn3;
	kw2 <= ke_set? k_buf[95:64]  : kn2;
	kw1 <= ke_set? k_buf[63:32]  : kn1;
	kw0 <= ke_set? k_buf[31:0]   : kn0;
	if(ke_set)
	  krc <= 8'h01;		// rounds 0..7, 01..80;
	else if(krc[31])
	  krc <= 8'h1b;		// rounds 8..9, 1b..36;
	else if(ke_end)
	  krc <= 8'h00;		// round 10, 00;
	else
	  krc <= { krc[30:24], 1'b0 };
     end

   assign kexp = { kw3, kw2, kw1, kw0 };
   assign ksr = ksub ^ { krc, 24'd0 };
   assign kn3 = ksr ^ kw3;     //i=Nk;  kw=w[i-Nk]  
   assign kn2 = kn3 ^ kw2;     //i=i+1
   assign kn1 = kn2 ^ kw1;
   assign kn0 = kn1 ^ kw0;

   assign ksub[31:24] = sbox(kw0[23:16]);   
   assign ksub[23:16] = sbox(kw0[15:8]) ;  
   assign ksub[15:8]  = sbox(kw0[7:0])  ;   
   assign ksub[7:0]   = sbox(kw0[31:24]); 


   // buffers for expanded decryption keys;
   // one for MC, one for DC, each is 11x128 bits;
   // implemented as circular shift register to reduce logic;
   // which means that abort is only possible after an entire
   // data block (16 bytes) has been decrypted; aborting in
   // the middle would leave expanded key messed up;

   // Decryption key buffer;

   wire   kmc_shift;				// shift kdc;
   wire [127:0] kmc;			// expanded MC key word;


   gi_kbuf kmc_buf (
		    .clk(clk),
		    .load(ke_load),
		    .shift(kmc_shift),
		    .kin(kexp),
		    .kout(kmc)
		    );






   

   // aes decryption core;
   // single issue sequential operation;
   // 4 clocks to load data from buffer and the
   // 4 clocks to write back to buffer are hidden by the aesmgr.v
   // 11 clocks to decrypt, leaves data in output reg;

   // input data/IV registers;
   // 4 loads from sram to pull 128 bits of data;
   // implemented as shift reg to reduce loading of sram_rdata;
   // 4 words of IV must be loaded before decryption start;
   // the old encrypted data become the new IV,
   // shift IVs into buffers for MC or DC;
   // saving and reloading in sram is too expensive;
   // NOP commands are treated the same exact way at de,
   // except that at the last minute, the TextRaw is copied to TextXfd

   reg [127:0] 	de_iv;   			//  decryption IV;
   reg [127:0] en_iv ;  			//  decryption IV;

		always @(posedge clk)
		begin
	 	   if( FirstPkt)                   //pulses one clk before Load only for the first pkt of the session
		     en_iv  <= aes_iv  ;
		   else if (TextTrdy && (Cmd==2'b10))        //for en, use text_out as new IV
		     en_iv  <= TextXfd  ;
		   else if (TextLoad && (Cmd!=2'b10)) begin  //for de, use text_in as new IV
		      en_iv  <= TextRaw  ;
		      de_iv  <= en_iv  ;
		   end

		end





   // decryption round state;
   // do initial permutation one clock after start;
   // followed by 10 rounds;
   // de_work stops aes core (and sim) from toggling;

   reg de_start;				// start decryption;
   reg de_work;				// work on decryption;
   reg [127:0] de_x;			// decryption state;
   wire [127:0] de_sr;			// scrambled round;
   wire [127:0] de_sub;			// inverse sbox substitutions;
   wire [127:0] de_rk;			// sub round key;
   wire [127:0] de_next;			// next state;
   reg  [3:0] 	cntr;			//  counter used for both en & de timing
   reg 		de_cbc;				// do cbc on result;
   reg 		de_run;				// run decryption rounds;
   wire 	de_last;				// last decryption round;
   wire 	de_go ;

   reg 		en_done;				// done with encryption;
   wire		en_go;				
   reg 		en_run;					// run encryption rounds;

   assign 	de_last = de_work & (cntr == 4'd1);

   
   always @(posedge clk) begin
      if (rst) begin
	 TextTrdy <= 1'b0 ;
	 cntr     <= 4'd0 ;
      end else begin
	 TextTrdy <= (de_work &&de_cbc) || (en_done)  ;
	 if      (en_go  || de_go)   cntr <= 4'd11    ;
	   else if (en_run || de_run)  cntr <= cntr - 4'b1 ;
      end
      de_run   <= de_go | (~de_last & de_run);
      de_start <=  de_run & ~de_work;
      de_work  <=  de_run;
      de_cbc   <= de_last;
   end
   

   assign de_go    = TextLoad & (Cmd!=2'b10); //pulse at rising edge of Irdy
   assign kmc_shift = de_run ;
   
   // decryption result handling;
   // XOR result with iv;
   always @(posedge clk)
     begin
	if    (de_start)  de_x <= TextRaw ^ kmc;
	else  if(de_work) de_x <= de_cbc ?  (de_rk ^ de_iv)    : de_next;
     end



   // scramble rounds;
   // basically reorder the bytes;
   //				in	ik	sa	sr		rk	out
   //							sub
   //	[127:120]	15	15	00	00=15	15	15
   //	[119:112]	14	14	10	11=10	10
   //	[111:104]	13	13	20	22=5	5
   //	[103:96]	12	12	30	33=0	0
   //	[95:88]		11	11	01	01=11	11
   //	[87:80]		10	10	11	12=6	6
   //	[79:72]		9	9	21	23=1	1
   //	[71:64]		8	8	31	30=12	12
   //	[63:56]		7	7	02	02=7	7
   //	[55:48]		6	6	12	13=2	2
   //	[47:40]		5	5	22	20=13	13
   //	[39:32]		4	4	32	31=8	8
   //	[31:24]		3	3	03	03=3	3
   //	[23:16]		2	2	13	10=14	14
   //	[15:8]		1	1	23	21=9	9
   //	[7:0]		0	0	33	32=4	4

   assign  de_sr = { 
		     de_x[127:120], de_x[23:16], de_x[47:40], de_x[71:64],
		     de_x[95:88], de_x[119:112], de_x[15:8], de_x[39:32],
		     de_x[63:56], de_x[87:80], de_x[111:104], de_x[7:0],
		     de_x[31:24], de_x[55:48], de_x[79:72], de_x[103:96] };

   // inverse cipher sboxes;
   // basically 8->8 recoders;

   assign  de_sub[127:120]     =  inv_sbox(de_sr[127:120]) ;
   assign  de_sub[119:112]     =  inv_sbox(de_sr[119:112]) ;
   assign  de_sub[111:104]     =  inv_sbox(de_sr[111:104]) ;
   assign  de_sub[103:96]      =  inv_sbox(de_sr[103:96])  ;
   assign  de_sub[95:88]       =  inv_sbox(de_sr[95:88])   ;
   assign  de_sub[87:80]       =  inv_sbox(de_sr[87:80])   ;
   assign  de_sub[79:72]       =  inv_sbox(de_sr[79:72])   ;
   assign  de_sub[71:64]       =  inv_sbox(de_sr[71:64])   ;
   assign  de_sub[63:56]       =  inv_sbox(de_sr[63:56])   ;
   assign  de_sub[55:48]       =  inv_sbox(de_sr[55:48])   ;
   assign  de_sub[47:40]       =  inv_sbox(de_sr[47:40])   ;
   assign  de_sub[39:32]       =  inv_sbox(de_sr[39:32])   ;
   assign  de_sub[31:24]       =  inv_sbox(de_sr[31:24])   ;
   assign  de_sub[23:16]       =  inv_sbox(de_sr[23:16])   ;
   assign  de_sub[15:8]        =  inv_sbox(de_sr[15:8])    ;
   assign  de_sub[7:0]         =  inv_sbox(de_sr[7:0])     ;


   // xor substitutions with key stream;
   // instantiate inverse column mixers;

   assign  de_rk = de_sub ^ kmc;

   gi_mixd mixd3 ( .i(de_rk[127:96]), .o(de_next[127:96]) );
   gi_mixd mixd2 ( .i(de_rk[95:64]), .o(de_next[95:64]) );
   gi_mixd mixd1 ( .i(de_rk[63:32]), .o(de_next[63:32]) );
   gi_mixd mixd0 ( .i(de_rk[31:0]), .o(de_next[31:0]) );















   
   // aes encryption core;
   // single issue sequential operation;
   // 4 clocks to load data from sram;
   // 11 clocks to encrypt, leaves data in output reg;
   // 4 clocks to write back to sram;
   // 100Mhz * 16bytes / 24 clocks = 66MBytes/sec;
   // sufficient bandwidth for MC;

   // input data/IV registers;
   // 4 loads from sram to pull 128 bits of data;
   // implemented as shift reg to reduce loading of sram_rdata;
   // 4 words of IV must be loaded before encryption start;
   // no IV buffer needed, load en_in with IV, then XOR data into;
   // shift in the encrypted data, which is the new iv;
   // expanded key stream comes live from key expander;

   wire [2:0] en_load;			// load ct, data (cbc), iv;
   wire [127:0] en_ks;			// encryption key stream;
   reg 		en_start;				// start encryption;
   reg 		en_work;				// work on encryption;
   wire         en_last;

   assign 	en_ks = kexp;
   assign 	en_go    = TextLoad & (Cmd==2'b10); //pulse at rising edge of Irdy
   assign 	en_last = en_work & (cntr == 4'd1);
   assign 	ke_en = en_work;

   always @(posedge clk)
     begin
	en_run   <=  en_go | (~en_last & en_run);
	en_start <=  en_run & ~en_work;
	en_work  <=  en_run;
	en_done  <=  en_last;
     end

   // encryption round state;
   // do initial permutation one clock after start;
   // followed by 10 rounds;
   // en_work stops aes core (and sim) from toggling;

   reg [127:0] en_x;			// encryption state;
   wire [127:0] en_sub;		// sbox substitutions;
   wire [127:0] en_sr;			// scrambled round;
   wire [127:0] en_mix;		// mixed columns;
   wire [127:0] en_next;		// next state;

   always @(posedge clk)
     begin
	if(en_go)           en_x <= TextRaw ^ en_iv ;   //cbc step
	else if(en_start)   en_x <= en_x ^ en_ks;    //clk 1    ;1st AddRound()
	else if(en_done)    en_x <= en_sr ^ en_ks;   //clk 11
	else if(en_work)    en_x <= en_next;         //clk 2-10
     end

   assign  TextXfd  =  Cmd[1] ?   (Cmd[0] ?  de_x : en_x)  : en_iv ;  //NOP, send out TextRaw

   // forward cipher sboxes;
   // basically 8->8 recoders;

   assign  en_sub[127:120]= sbox(en_x[127:120]);   
   assign  en_sub[119:112]= sbox(en_x[119:112]);   
   assign  en_sub[111:104]= sbox(en_x[111:104]);   
   assign  en_sub[103:96] = sbox(en_x[103:96]);    
   assign  en_sub[95:88]  = sbox(en_x[95:88]);     
   assign  en_sub[87:80]  = sbox(en_x[87:80]);     
   assign  en_sub[79:72]  = sbox(en_x[79:72]);     
   assign  en_sub[71:64]  = sbox(en_x[71:64]);       
   assign  en_sub[63:56]  = sbox(en_x[63:56]);       
   assign  en_sub[55:48]  = sbox(en_x[55:48]);       
   assign  en_sub[47:40]  = sbox(en_x[47:40]);       
   assign  en_sub[39:32]  = sbox(en_x[39:32]);       
   assign  en_sub[31:24]  = sbox(en_x[31:24]);       
   assign  en_sub[23:16]  = sbox(en_x[23:16]);       
   assign  en_sub[15:8]   = sbox(en_x[15:8]);        
   assign  en_sub[7:0]    = sbox(en_x[7:0]);         

   // scramble rounds;
   // basically reorder the bytes;
   //				in	ik	sub	sr		rk	out
   //							mix
   //	[127:120]	15	15	00	00=15	15
   //	[119:112]	14	14	10	13=2
   //	[111:104]	13	13	20	22=5
   //	[103:96]	12	12	30	31=8
   //	[95:88]		11	11	01	01=11
   //	[87:80]		10	10	11	10=14
   //	[79:72]		9	9	21	23=1
   //	[71:64]		8	8	31	32=4
   //	[63:56]		7	7	02	02=7
   //	[55:48]		6	6	12	11=10
   //	[47:40]		5	5	22	20=13
   //	[39:32]		4	4	32	33=0
   //	[31:24]		3	3	03	03=3
   //	[23:16]		2	2	13	12=6
   //	[15:8]		1	1	23	21=9
   //	[7:0]		0	0	33	30=12

   assign en_sr = { 
		    en_sub[127:120], en_sub[87:80], en_sub[47:40], en_sub[7:0],
		    en_sub[95:88], en_sub[55:48], en_sub[15:8], en_sub[103:96],
		    en_sub[63:56], en_sub[23:16], en_sub[111:104], en_sub[71:64],
		    en_sub[31:24], en_sub[119:112], en_sub[79:72], en_sub[39:32] };

   // instantiate column mixers;
   // xor scrambled with key stream;

   gi_mixe mixe3 ( .i(en_sr[127:96]), .o(en_mix[127:96]) );
   gi_mixe mixe2 ( .i(en_sr[95:64]), .o(en_mix[95:64]) );
   gi_mixe mixe1 ( .i(en_sr[63:32]), .o(en_mix[63:32]) );
   gi_mixe mixe0 ( .i(en_sr[31:0]), .o(en_mix[31:0]) );

   assign en_next = en_mix ^ en_ks;


function [7:0] inv_sbox ;
input	[7:0]	a;

	case(a)		// synopsys full_case parallel_case
	   8'h00: inv_sbox=8'h52;
	   8'h01: inv_sbox=8'h09;
	   8'h02: inv_sbox=8'h6a;
	   8'h03: inv_sbox=8'hd5;
	   8'h04: inv_sbox=8'h30;
	   8'h05: inv_sbox=8'h36;
	   8'h06: inv_sbox=8'ha5;
	   8'h07: inv_sbox=8'h38;
	   8'h08: inv_sbox=8'hbf;
	   8'h09: inv_sbox=8'h40;
	   8'h0a: inv_sbox=8'ha3;
	   8'h0b: inv_sbox=8'h9e;
	   8'h0c: inv_sbox=8'h81;
	   8'h0d: inv_sbox=8'hf3;
	   8'h0e: inv_sbox=8'hd7;
	   8'h0f: inv_sbox=8'hfb;
	   8'h10: inv_sbox=8'h7c;
	   8'h11: inv_sbox=8'he3;
	   8'h12: inv_sbox=8'h39;
	   8'h13: inv_sbox=8'h82;
	   8'h14: inv_sbox=8'h9b;
	   8'h15: inv_sbox=8'h2f;
	   8'h16: inv_sbox=8'hff;
	   8'h17: inv_sbox=8'h87;
	   8'h18: inv_sbox=8'h34;
	   8'h19: inv_sbox=8'h8e;
	   8'h1a: inv_sbox=8'h43;
	   8'h1b: inv_sbox=8'h44;
	   8'h1c: inv_sbox=8'hc4;
	   8'h1d: inv_sbox=8'hde;
	   8'h1e: inv_sbox=8'he9;
	   8'h1f: inv_sbox=8'hcb;
	   8'h20: inv_sbox=8'h54;
	   8'h21: inv_sbox=8'h7b;
	   8'h22: inv_sbox=8'h94;
	   8'h23: inv_sbox=8'h32;
	   8'h24: inv_sbox=8'ha6;
	   8'h25: inv_sbox=8'hc2;
	   8'h26: inv_sbox=8'h23;
	   8'h27: inv_sbox=8'h3d;
	   8'h28: inv_sbox=8'hee;
	   8'h29: inv_sbox=8'h4c;
	   8'h2a: inv_sbox=8'h95;
	   8'h2b: inv_sbox=8'h0b;
	   8'h2c: inv_sbox=8'h42;
	   8'h2d: inv_sbox=8'hfa;
	   8'h2e: inv_sbox=8'hc3;
	   8'h2f: inv_sbox=8'h4e;
	   8'h30: inv_sbox=8'h08;
	   8'h31: inv_sbox=8'h2e;
	   8'h32: inv_sbox=8'ha1;
	   8'h33: inv_sbox=8'h66;
	   8'h34: inv_sbox=8'h28;
	   8'h35: inv_sbox=8'hd9;
	   8'h36: inv_sbox=8'h24;
	   8'h37: inv_sbox=8'hb2;
	   8'h38: inv_sbox=8'h76;
	   8'h39: inv_sbox=8'h5b;
	   8'h3a: inv_sbox=8'ha2;
	   8'h3b: inv_sbox=8'h49;
	   8'h3c: inv_sbox=8'h6d;
	   8'h3d: inv_sbox=8'h8b;
	   8'h3e: inv_sbox=8'hd1;
	   8'h3f: inv_sbox=8'h25;
	   8'h40: inv_sbox=8'h72;
	   8'h41: inv_sbox=8'hf8;
	   8'h42: inv_sbox=8'hf6;
	   8'h43: inv_sbox=8'h64;
	   8'h44: inv_sbox=8'h86;
	   8'h45: inv_sbox=8'h68;
	   8'h46: inv_sbox=8'h98;
	   8'h47: inv_sbox=8'h16;
	   8'h48: inv_sbox=8'hd4;
	   8'h49: inv_sbox=8'ha4;
	   8'h4a: inv_sbox=8'h5c;
	   8'h4b: inv_sbox=8'hcc;
	   8'h4c: inv_sbox=8'h5d;
	   8'h4d: inv_sbox=8'h65;
	   8'h4e: inv_sbox=8'hb6;
	   8'h4f: inv_sbox=8'h92;
	   8'h50: inv_sbox=8'h6c;
	   8'h51: inv_sbox=8'h70;
	   8'h52: inv_sbox=8'h48;
	   8'h53: inv_sbox=8'h50;
	   8'h54: inv_sbox=8'hfd;
	   8'h55: inv_sbox=8'hed;
	   8'h56: inv_sbox=8'hb9;
	   8'h57: inv_sbox=8'hda;
	   8'h58: inv_sbox=8'h5e;
	   8'h59: inv_sbox=8'h15;
	   8'h5a: inv_sbox=8'h46;
	   8'h5b: inv_sbox=8'h57;
	   8'h5c: inv_sbox=8'ha7;
	   8'h5d: inv_sbox=8'h8d;
	   8'h5e: inv_sbox=8'h9d;
	   8'h5f: inv_sbox=8'h84;
	   8'h60: inv_sbox=8'h90;
	   8'h61: inv_sbox=8'hd8;
	   8'h62: inv_sbox=8'hab;
	   8'h63: inv_sbox=8'h00;
	   8'h64: inv_sbox=8'h8c;
	   8'h65: inv_sbox=8'hbc;
	   8'h66: inv_sbox=8'hd3;
	   8'h67: inv_sbox=8'h0a;
	   8'h68: inv_sbox=8'hf7;
	   8'h69: inv_sbox=8'he4;
	   8'h6a: inv_sbox=8'h58;
	   8'h6b: inv_sbox=8'h05;
	   8'h6c: inv_sbox=8'hb8;
	   8'h6d: inv_sbox=8'hb3;
	   8'h6e: inv_sbox=8'h45;
	   8'h6f: inv_sbox=8'h06;
	   8'h70: inv_sbox=8'hd0;
	   8'h71: inv_sbox=8'h2c;
	   8'h72: inv_sbox=8'h1e;
	   8'h73: inv_sbox=8'h8f;
	   8'h74: inv_sbox=8'hca;
	   8'h75: inv_sbox=8'h3f;
	   8'h76: inv_sbox=8'h0f;
	   8'h77: inv_sbox=8'h02;
	   8'h78: inv_sbox=8'hc1;
	   8'h79: inv_sbox=8'haf;
	   8'h7a: inv_sbox=8'hbd;
	   8'h7b: inv_sbox=8'h03;
	   8'h7c: inv_sbox=8'h01;
	   8'h7d: inv_sbox=8'h13;
	   8'h7e: inv_sbox=8'h8a;
	   8'h7f: inv_sbox=8'h6b;
	   8'h80: inv_sbox=8'h3a;
	   8'h81: inv_sbox=8'h91;
	   8'h82: inv_sbox=8'h11;
	   8'h83: inv_sbox=8'h41;
	   8'h84: inv_sbox=8'h4f;
	   8'h85: inv_sbox=8'h67;
	   8'h86: inv_sbox=8'hdc;
	   8'h87: inv_sbox=8'hea;
	   8'h88: inv_sbox=8'h97;
	   8'h89: inv_sbox=8'hf2;
	   8'h8a: inv_sbox=8'hcf;
	   8'h8b: inv_sbox=8'hce;
	   8'h8c: inv_sbox=8'hf0;
	   8'h8d: inv_sbox=8'hb4;
	   8'h8e: inv_sbox=8'he6;
	   8'h8f: inv_sbox=8'h73;
	   8'h90: inv_sbox=8'h96;
	   8'h91: inv_sbox=8'hac;
	   8'h92: inv_sbox=8'h74;
	   8'h93: inv_sbox=8'h22;
	   8'h94: inv_sbox=8'he7;
	   8'h95: inv_sbox=8'had;
	   8'h96: inv_sbox=8'h35;
	   8'h97: inv_sbox=8'h85;
	   8'h98: inv_sbox=8'he2;
	   8'h99: inv_sbox=8'hf9;
	   8'h9a: inv_sbox=8'h37;
	   8'h9b: inv_sbox=8'he8;
	   8'h9c: inv_sbox=8'h1c;
	   8'h9d: inv_sbox=8'h75;
	   8'h9e: inv_sbox=8'hdf;
	   8'h9f: inv_sbox=8'h6e;
	   8'ha0: inv_sbox=8'h47;
	   8'ha1: inv_sbox=8'hf1;
	   8'ha2: inv_sbox=8'h1a;
	   8'ha3: inv_sbox=8'h71;
	   8'ha4: inv_sbox=8'h1d;
	   8'ha5: inv_sbox=8'h29;
	   8'ha6: inv_sbox=8'hc5;
	   8'ha7: inv_sbox=8'h89;
	   8'ha8: inv_sbox=8'h6f;
	   8'ha9: inv_sbox=8'hb7;
	   8'haa: inv_sbox=8'h62;
	   8'hab: inv_sbox=8'h0e;
	   8'hac: inv_sbox=8'haa;
	   8'had: inv_sbox=8'h18;
	   8'hae: inv_sbox=8'hbe;
	   8'haf: inv_sbox=8'h1b;
	   8'hb0: inv_sbox=8'hfc;
	   8'hb1: inv_sbox=8'h56;
	   8'hb2: inv_sbox=8'h3e;
	   8'hb3: inv_sbox=8'h4b;
	   8'hb4: inv_sbox=8'hc6;
	   8'hb5: inv_sbox=8'hd2;
	   8'hb6: inv_sbox=8'h79;
	   8'hb7: inv_sbox=8'h20;
	   8'hb8: inv_sbox=8'h9a;
	   8'hb9: inv_sbox=8'hdb;
	   8'hba: inv_sbox=8'hc0;
	   8'hbb: inv_sbox=8'hfe;
	   8'hbc: inv_sbox=8'h78;
	   8'hbd: inv_sbox=8'hcd;
	   8'hbe: inv_sbox=8'h5a;
	   8'hbf: inv_sbox=8'hf4;
	   8'hc0: inv_sbox=8'h1f;
	   8'hc1: inv_sbox=8'hdd;
	   8'hc2: inv_sbox=8'ha8;
	   8'hc3: inv_sbox=8'h33;
	   8'hc4: inv_sbox=8'h88;
	   8'hc5: inv_sbox=8'h07;
	   8'hc6: inv_sbox=8'hc7;
	   8'hc7: inv_sbox=8'h31;
	   8'hc8: inv_sbox=8'hb1;
	   8'hc9: inv_sbox=8'h12;
	   8'hca: inv_sbox=8'h10;
	   8'hcb: inv_sbox=8'h59;
	   8'hcc: inv_sbox=8'h27;
	   8'hcd: inv_sbox=8'h80;
	   8'hce: inv_sbox=8'hec;
	   8'hcf: inv_sbox=8'h5f;
	   8'hd0: inv_sbox=8'h60;
	   8'hd1: inv_sbox=8'h51;
	   8'hd2: inv_sbox=8'h7f;
	   8'hd3: inv_sbox=8'ha9;
	   8'hd4: inv_sbox=8'h19;
	   8'hd5: inv_sbox=8'hb5;
	   8'hd6: inv_sbox=8'h4a;
	   8'hd7: inv_sbox=8'h0d;
	   8'hd8: inv_sbox=8'h2d;
	   8'hd9: inv_sbox=8'he5;
	   8'hda: inv_sbox=8'h7a;
	   8'hdb: inv_sbox=8'h9f;
	   8'hdc: inv_sbox=8'h93;
	   8'hdd: inv_sbox=8'hc9;
	   8'hde: inv_sbox=8'h9c;
	   8'hdf: inv_sbox=8'hef;
	   8'he0: inv_sbox=8'ha0;
	   8'he1: inv_sbox=8'he0;
	   8'he2: inv_sbox=8'h3b;
	   8'he3: inv_sbox=8'h4d;
	   8'he4: inv_sbox=8'hae;
	   8'he5: inv_sbox=8'h2a;
	   8'he6: inv_sbox=8'hf5;
	   8'he7: inv_sbox=8'hb0;
	   8'he8: inv_sbox=8'hc8;
	   8'he9: inv_sbox=8'heb;
	   8'hea: inv_sbox=8'hbb;
	   8'heb: inv_sbox=8'h3c;
	   8'hec: inv_sbox=8'h83;
	   8'hed: inv_sbox=8'h53;
	   8'hee: inv_sbox=8'h99;
	   8'hef: inv_sbox=8'h61;
	   8'hf0: inv_sbox=8'h17;
	   8'hf1: inv_sbox=8'h2b;
	   8'hf2: inv_sbox=8'h04;
	   8'hf3: inv_sbox=8'h7e;
	   8'hf4: inv_sbox=8'hba;
	   8'hf5: inv_sbox=8'h77;
	   8'hf6: inv_sbox=8'hd6;
	   8'hf7: inv_sbox=8'h26;
	   8'hf8: inv_sbox=8'he1;
	   8'hf9: inv_sbox=8'h69;
	   8'hfa: inv_sbox=8'h14;
	   8'hfb: inv_sbox=8'h63;
	   8'hfc: inv_sbox=8'h55;
	   8'hfd: inv_sbox=8'h21;
	   8'hfe: inv_sbox=8'h0c;
	   8'hff: inv_sbox=8'h7d;
	endcase
endfunction

function [7:0]  sbox ;
input	[7:0]	a;

	case(a)		// synopsys full_case parallel_case
	   8'h00: sbox=8'h63;
	   8'h01: sbox=8'h7c;
	   8'h02: sbox=8'h77;
	   8'h03: sbox=8'h7b;
	   8'h04: sbox=8'hf2;
	   8'h05: sbox=8'h6b;
	   8'h06: sbox=8'h6f;
	   8'h07: sbox=8'hc5;
	   8'h08: sbox=8'h30;
	   8'h09: sbox=8'h01;
	   8'h0a: sbox=8'h67;
	   8'h0b: sbox=8'h2b;
	   8'h0c: sbox=8'hfe;
	   8'h0d: sbox=8'hd7;
	   8'h0e: sbox=8'hab;
	   8'h0f: sbox=8'h76;
	   8'h10: sbox=8'hca;
	   8'h11: sbox=8'h82;
	   8'h12: sbox=8'hc9;
	   8'h13: sbox=8'h7d;
	   8'h14: sbox=8'hfa;
	   8'h15: sbox=8'h59;
	   8'h16: sbox=8'h47;
	   8'h17: sbox=8'hf0;
	   8'h18: sbox=8'had;
	   8'h19: sbox=8'hd4;
	   8'h1a: sbox=8'ha2;
	   8'h1b: sbox=8'haf;
	   8'h1c: sbox=8'h9c;
	   8'h1d: sbox=8'ha4;
	   8'h1e: sbox=8'h72;
	   8'h1f: sbox=8'hc0;
	   8'h20: sbox=8'hb7;
	   8'h21: sbox=8'hfd;
	   8'h22: sbox=8'h93;
	   8'h23: sbox=8'h26;
	   8'h24: sbox=8'h36;
	   8'h25: sbox=8'h3f;
	   8'h26: sbox=8'hf7;
	   8'h27: sbox=8'hcc;
	   8'h28: sbox=8'h34;
	   8'h29: sbox=8'ha5;
	   8'h2a: sbox=8'he5;
	   8'h2b: sbox=8'hf1;
	   8'h2c: sbox=8'h71;
	   8'h2d: sbox=8'hd8;
	   8'h2e: sbox=8'h31;
	   8'h2f: sbox=8'h15;
	   8'h30: sbox=8'h04;
	   8'h31: sbox=8'hc7;
	   8'h32: sbox=8'h23;
	   8'h33: sbox=8'hc3;
	   8'h34: sbox=8'h18;
	   8'h35: sbox=8'h96;
	   8'h36: sbox=8'h05;
	   8'h37: sbox=8'h9a;
	   8'h38: sbox=8'h07;
	   8'h39: sbox=8'h12;
	   8'h3a: sbox=8'h80;
	   8'h3b: sbox=8'he2;
	   8'h3c: sbox=8'heb;
	   8'h3d: sbox=8'h27;
	   8'h3e: sbox=8'hb2;
	   8'h3f: sbox=8'h75;
	   8'h40: sbox=8'h09;
	   8'h41: sbox=8'h83;
	   8'h42: sbox=8'h2c;
	   8'h43: sbox=8'h1a;
	   8'h44: sbox=8'h1b;
	   8'h45: sbox=8'h6e;
	   8'h46: sbox=8'h5a;
	   8'h47: sbox=8'ha0;
	   8'h48: sbox=8'h52;
	   8'h49: sbox=8'h3b;
	   8'h4a: sbox=8'hd6;
	   8'h4b: sbox=8'hb3;
	   8'h4c: sbox=8'h29;
	   8'h4d: sbox=8'he3;
	   8'h4e: sbox=8'h2f;
	   8'h4f: sbox=8'h84;
	   8'h50: sbox=8'h53;
	   8'h51: sbox=8'hd1;
	   8'h52: sbox=8'h00;
	   8'h53: sbox=8'hed;
	   8'h54: sbox=8'h20;
	   8'h55: sbox=8'hfc;
	   8'h56: sbox=8'hb1;
	   8'h57: sbox=8'h5b;
	   8'h58: sbox=8'h6a;
	   8'h59: sbox=8'hcb;
	   8'h5a: sbox=8'hbe;
	   8'h5b: sbox=8'h39;
	   8'h5c: sbox=8'h4a;
	   8'h5d: sbox=8'h4c;
	   8'h5e: sbox=8'h58;
	   8'h5f: sbox=8'hcf;
	   8'h60: sbox=8'hd0;
	   8'h61: sbox=8'hef;
	   8'h62: sbox=8'haa;
	   8'h63: sbox=8'hfb;
	   8'h64: sbox=8'h43;
	   8'h65: sbox=8'h4d;
	   8'h66: sbox=8'h33;
	   8'h67: sbox=8'h85;
	   8'h68: sbox=8'h45;
	   8'h69: sbox=8'hf9;
	   8'h6a: sbox=8'h02;
	   8'h6b: sbox=8'h7f;
	   8'h6c: sbox=8'h50;
	   8'h6d: sbox=8'h3c;
	   8'h6e: sbox=8'h9f;
	   8'h6f: sbox=8'ha8;
	   8'h70: sbox=8'h51;
	   8'h71: sbox=8'ha3;
	   8'h72: sbox=8'h40;
	   8'h73: sbox=8'h8f;
	   8'h74: sbox=8'h92;
	   8'h75: sbox=8'h9d;
	   8'h76: sbox=8'h38;
	   8'h77: sbox=8'hf5;
	   8'h78: sbox=8'hbc;
	   8'h79: sbox=8'hb6;
	   8'h7a: sbox=8'hda;
	   8'h7b: sbox=8'h21;
	   8'h7c: sbox=8'h10;
	   8'h7d: sbox=8'hff;
	   8'h7e: sbox=8'hf3;
	   8'h7f: sbox=8'hd2;
	   8'h80: sbox=8'hcd;
	   8'h81: sbox=8'h0c;
	   8'h82: sbox=8'h13;
	   8'h83: sbox=8'hec;
	   8'h84: sbox=8'h5f;
	   8'h85: sbox=8'h97;
	   8'h86: sbox=8'h44;
	   8'h87: sbox=8'h17;
	   8'h88: sbox=8'hc4;
	   8'h89: sbox=8'ha7;
	   8'h8a: sbox=8'h7e;
	   8'h8b: sbox=8'h3d;
	   8'h8c: sbox=8'h64;
	   8'h8d: sbox=8'h5d;
	   8'h8e: sbox=8'h19;
	   8'h8f: sbox=8'h73;
	   8'h90: sbox=8'h60;
	   8'h91: sbox=8'h81;
	   8'h92: sbox=8'h4f;
	   8'h93: sbox=8'hdc;
	   8'h94: sbox=8'h22;
	   8'h95: sbox=8'h2a;
	   8'h96: sbox=8'h90;
	   8'h97: sbox=8'h88;
	   8'h98: sbox=8'h46;
	   8'h99: sbox=8'hee;
	   8'h9a: sbox=8'hb8;
	   8'h9b: sbox=8'h14;
	   8'h9c: sbox=8'hde;
	   8'h9d: sbox=8'h5e;
	   8'h9e: sbox=8'h0b;
	   8'h9f: sbox=8'hdb;
	   8'ha0: sbox=8'he0;
	   8'ha1: sbox=8'h32;
	   8'ha2: sbox=8'h3a;
	   8'ha3: sbox=8'h0a;
	   8'ha4: sbox=8'h49;
	   8'ha5: sbox=8'h06;
	   8'ha6: sbox=8'h24;
	   8'ha7: sbox=8'h5c;
	   8'ha8: sbox=8'hc2;
	   8'ha9: sbox=8'hd3;
	   8'haa: sbox=8'hac;
	   8'hab: sbox=8'h62;
	   8'hac: sbox=8'h91;
	   8'had: sbox=8'h95;
	   8'hae: sbox=8'he4;
	   8'haf: sbox=8'h79;
	   8'hb0: sbox=8'he7;
	   8'hb1: sbox=8'hc8;
	   8'hb2: sbox=8'h37;
	   8'hb3: sbox=8'h6d;
	   8'hb4: sbox=8'h8d;
	   8'hb5: sbox=8'hd5;
	   8'hb6: sbox=8'h4e;
	   8'hb7: sbox=8'ha9;
	   8'hb8: sbox=8'h6c;
	   8'hb9: sbox=8'h56;
	   8'hba: sbox=8'hf4;
	   8'hbb: sbox=8'hea;
	   8'hbc: sbox=8'h65;
	   8'hbd: sbox=8'h7a;
	   8'hbe: sbox=8'hae;
	   8'hbf: sbox=8'h08;
	   8'hc0: sbox=8'hba;
	   8'hc1: sbox=8'h78;
	   8'hc2: sbox=8'h25;
	   8'hc3: sbox=8'h2e;
	   8'hc4: sbox=8'h1c;
	   8'hc5: sbox=8'ha6;
	   8'hc6: sbox=8'hb4;
	   8'hc7: sbox=8'hc6;
	   8'hc8: sbox=8'he8;
	   8'hc9: sbox=8'hdd;
	   8'hca: sbox=8'h74;
	   8'hcb: sbox=8'h1f;
	   8'hcc: sbox=8'h4b;
	   8'hcd: sbox=8'hbd;
	   8'hce: sbox=8'h8b;
	   8'hcf: sbox=8'h8a;
	   8'hd0: sbox=8'h70;
	   8'hd1: sbox=8'h3e;
	   8'hd2: sbox=8'hb5;
	   8'hd3: sbox=8'h66;
	   8'hd4: sbox=8'h48;
	   8'hd5: sbox=8'h03;
	   8'hd6: sbox=8'hf6;
	   8'hd7: sbox=8'h0e;
	   8'hd8: sbox=8'h61;
	   8'hd9: sbox=8'h35;
	   8'hda: sbox=8'h57;
	   8'hdb: sbox=8'hb9;
	   8'hdc: sbox=8'h86;
	   8'hdd: sbox=8'hc1;
	   8'hde: sbox=8'h1d;
	   8'hdf: sbox=8'h9e;
	   8'he0: sbox=8'he1;
	   8'he1: sbox=8'hf8;
	   8'he2: sbox=8'h98;
	   8'he3: sbox=8'h11;
	   8'he4: sbox=8'h69;
	   8'he5: sbox=8'hd9;
	   8'he6: sbox=8'h8e;
	   8'he7: sbox=8'h94;
	   8'he8: sbox=8'h9b;
	   8'he9: sbox=8'h1e;
	   8'hea: sbox=8'h87;
	   8'heb: sbox=8'he9;
	   8'hec: sbox=8'hce;
	   8'hed: sbox=8'h55;
	   8'hee: sbox=8'h28;
	   8'hef: sbox=8'hdf;
	   8'hf0: sbox=8'h8c;
	   8'hf1: sbox=8'ha1;
	   8'hf2: sbox=8'h89;
	   8'hf3: sbox=8'h0d;
	   8'hf4: sbox=8'hbf;
	   8'hf5: sbox=8'he6;
	   8'hf6: sbox=8'h42;
	   8'hf7: sbox=8'h68;
	   8'hf8: sbox=8'h41;
	   8'hf9: sbox=8'h99;
	   8'hfa: sbox=8'h2d;
	   8'hfb: sbox=8'h0f;
	   8'hfc: sbox=8'hb0;
	   8'hfd: sbox=8'h54;
	   8'hfe: sbox=8'hbb;
	   8'hff: sbox=8'h16;
	endcase

endfunction



endmodule

