d16 2
a17 2
	       AesIrdy, AesBank, AesSize, AesTrdy, Sos            // genmgr.v
               AesWr,  AesRd, AesBank, AesRdAdd, AesWrAdd, AesWrData, AesRdData   //AesMgr    
d30 1
a30 2
   input       AesBank ;    //= which bank to operate on
   input [SBASE:0] Size;        //= how many packets to process. 
a37 1
   output 	   AesBank  ;
d57 1
a57 1
   parameter [3:0] IDLE  = 4'd0,
d69 2
a70 2
   reg [3:0] 	   state, next;
   reg 		   RdEnb    , RdEnb_nxt  , WrEnb    , WrEnb_nxt, 
d76 2
d87 1
a87 1
     end ;
d89 1
a89 1
   assign LastPkt = (AesRdAdd[3:2] == Size) ;
d107 1
a107 1
     end ;
d119 1
a119 1
     end ;
d135 1
a135 1
     end case
d164 1
a164 1
	     end ;
d166 1
a166 1
   always @(state or *) begin
d182 1
a182 1
           end ;
d272 1
a272 1
endmodule  ; // aesmgr
