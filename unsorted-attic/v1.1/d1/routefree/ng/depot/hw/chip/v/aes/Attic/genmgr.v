d14 2
a15 2
		ExpKeyTrdy, ExpKeyIrdy, SecretKey, aes_iv, Cmd,                   //AES Block
		AesIrdy, AesBank, AesSize, AesTrdy, Sos                             //AESMNGR Block
d20 1
a20 1
		cpu_hresp_o, cpu_hrdata_o, cpu_hsplit_o, int_o,
a40 1
   output 	  AesBank ;    //indicates which bank to operate on
d79 1
a79 1
   wire [31:0] 	    cpu_hrdata_o;
d100 6
d123 8
a130 8
   parameter [3:0]  IDLE  = 3'd0,
		    EXPKEY= 3'd1,
		    RD1   = 3'd2,
		    AES1  = 3'd3,
		    RDN   = 3'd4,
		    AES2  = 3'd5,
		    WR    = 3'd6,
		    WRLAST= 3'd7;
d180 1
d191 1
a191 1
		    `AESCTRL: cpu_hrdata_o  <=  Aes_ctrl;
d277 3
a279 3
	if (MemTrdy &&  MemRd_Wr)  MemRdDone <= 1'b1  else if (ClrTrdyDone) MemRdDone <= 1'b0 ;
	if (MemTrdy && !MemRd_Wr)  MemWrDone <= 1'b1  else if (ClrTrdyDone) MemWrDone <= 1'b0 ;
	if (AesTrdy)               AesDone   <= 1'b1  else if (ClrTrdyDone) AesDone   <= 1'b0 ;
d284 1
a284 1
   wire    LastPkt   = (ctl_size == 10'b1111111111 ) OR  (aes_exec==1'b0); //stop if zero writen to exec bit
d290 1
a290 1
   assign  AesBank   = !CurBank ;
d293 1
a293 1
   assign  aes_iv  = {aes_iv4,, aes_iv3,  aes_iv2,  aes_iv1  } ;
d316 1
a316 1
             end ;
d395 1
a395 1
	  default:  next = IDLE ;
