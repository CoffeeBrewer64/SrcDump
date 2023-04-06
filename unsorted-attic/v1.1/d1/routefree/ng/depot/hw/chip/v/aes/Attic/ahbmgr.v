d15 1
a15 1
                AesWr,  AesRd, AesBank, AesRdAdd, AesWrAdd, AesWrData, AesRdData ,  //AesMgr    
d23 1
a41 1
   input 	   AesBank  ;
d66 3
d72 4
d85 1
a85 1
	if            (MemIrdyP)     f2m_req  <= 1'b1            else if (m2f_ack) f2m_req    <= 1'b0 ;
d93 3
a97 2
   assign B0      = !MemBank ;
   assign B1      =  MemBank ;
d110 1
a110 1
   assing  f2m_addr  = {MemAdd[21:0] , 2'b00}  ; //check make sure this is all right.....<<<<<
d112 1
a112 1
   assing  f2m_write =  MemRd_Wr;                // 0=mem write to flash, 1=flash write to mem;
d121 1
a121 1
   Mem1R1W32x32  Bank0 (
d131 1
a131 1
   Mem1R1W32x32  Bank1 (
d143 1
a143 1
endmodule  ;
