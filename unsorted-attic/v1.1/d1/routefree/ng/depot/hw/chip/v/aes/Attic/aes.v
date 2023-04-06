d1 1
a1 1
// Filename        : aes_top.v
d13 1
a13 1
module aes_top(clk, rst, 
d15 1
a15 1
	       ExpKeyTrdy, ExpKeyIrdy, SecretKey, aes_iv, Cmd,   // genmgr.v
d27 1
d57 1
d61 3
d65 1
a65 1
      ExpKeyTrdy   <= ~reset   & ke_end;
d90 1
d183 2
a184 2
   reg [127:0] 	de_iv    			//  decryption IV;
		reg [127:0] en_iv    			//  decryption IV;
d215 1
a215 1
   wire [3:0] 	cntr;			//  counter used for both en & de timing
d221 4
d234 1
a234 1
	 if      (en_go  || de_go)   cntr <= 4'd11    
a254 1
   assign  TextXfd  =  Cmd[1] ?   (Cmd[0] ?  de_x : en_x)  : en_iv ;  //NOP, send out TextRaw
a348 1
   reg 		en_run;					// run encryption rounds;
a350 2
   reg 		en_done;				// done with encryption;
   reg 		en_go;				
d384 2
d449 1
a449 1
endmodule;
