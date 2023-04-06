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
// Filename        : aesmgr.v
// Description     : This manager reads pkt data from one the banks,
//                   pushes the pkt through aes, and
//                   writes the encrypted/decrypted pkt back into buffer.
//
//
//                   Nima Nikuie  --May 2 2005 
//
//  CVS Log
//
//  $Id: aesmgr.v,v 1.4 2005/05/18 21:28:17 nima Exp $
//
//  $Date: 2005/05/18 21:28:17 $
//  $Revision: 1.4 $
//  $Author: nima $
//  $Locker:  $
//  $State: Exp $
//
//  Change History:
//               $Log: aesmgr.v,v $
//               Revision 1.4  2005/05/18 21:28:17  nima
//               added the BroadOn banner
//
//
//
//
//

`timescale 1ps/1ps
`include "ahb_fdl_defs.v"

module aesmgr (
	       clk, rst,
	       TextLoad, TextRaw, TextXfd, TextTrdy, FirstPkt,    // aes.v
	       AesIrdy,  AesSize, AesTrdy, Sos,           // genmgr.v
               AesWr,  AesRd,  AesRdAdd, AesWrAdd, AesWrData, AesRdData   //AesMgr    
	       ) ;

   //these params are declared to support either 64byte or 128byte mem buffers
   parameter   SBASE  =  1;  // 64B = 1;  128B = 2   Size BASE of the Num of pkts to process=[SBASE : 0]
   parameter   ADDW   =  3;  // 64B = 3;  128B = 4   ADDress Width of the RD/WR add cntrs to pkt buffer
   parameter   NOPKT  =  4;  // 64B = 4;  128B = 8   Number of pkts  processed each time in decimal
   
   input       clk, rst;


   // interface to the genmgr
   input       AesIrdy;     //starts packet processing
   input [SBASE:0] AesSize;        //= how many packets to process. 
   output 	   AesTrdy;     //= pkt processing done 
   input 	   Sos ;        //Start of session


   // interface to the ahbmgr
   output 	   AesWr    ;
   output 	   AesRd    ;
   output [ADDW:0] AesRdAdd ; 
   output [ADDW:0] AesWrAdd ;
   output [31:0]   AesWrData ;
   input [31:0]    AesRdData ;

   // interface to the AES Block
   output [127:0]  TextRaw     ;
   output 	   TextLoad ;
   output 	   FirstPkt ;
   input [127:0]   TextXfd   ;
   input 	   TextTrdy ;

   reg 		   AesTrdy;
   reg 		   TextLoad ;
   reg 		   FirstPkt ;
   reg [ADDW:0]    AesRdAdd, AesWrAdd ;
   reg [127:0] 	   TextRaw ;
   reg [127:0] 	   TextOut ; //registerd version of TextXfd
   
   parameter       IDLE  = 4'd0,
		   RD1   = 4'd1,
		   AES1  = 4'd2,
		   RDN   = 4'd3,
		   WT1   = 4'd4,
		   AESN  = 4'd5,
		   WR    = 4'd6,
		   WT2   = 4'd7,
		   WRLAST= 4'd8;


   
   reg [3:0]    state, next;
   reg      	RdEnb    , RdEnb_nxt  , WrEnb    , WrEnb_nxt, 
		   TextLoad_nxt, ClrCntrs ,  ClrCntrs_nxt,    AesTrdy_nxt,
		   RegRdData,  RegRdData_nxt, RegRdData0, RegRdData1, RegRdData2, RegRdData3;


   wire 	   RdDone, WrDone, LastPkt;
 
   reg    [31:0]   AesWrData ;

   assign 	   AesWr = WrEnb   ;
   assign 	   AesRd = RdEnb   ;

   always @(posedge clk )
     if (!rst || ClrCntrs ) begin
        AesRdAdd    <= 4'b0;
        AesWrAdd    <= 4'b0;
     end 
     else      begin 
	if (RdEnb) AesRdAdd    <= AesRdAdd + 4'b1 ;
	if (WrEnb) AesWrAdd    <= AesWrAdd + 4'b1 ;
     end 

   assign LastPkt = (AesRdAdd[3:2] == AesSize) ;
   assign RdDone  = (AesRdAdd[1:0] == 2'b11) ;
   assign WrDone  = (AesWrAdd[1:0] == 2'b11) ;
   
   //assume asynch buff mem.  there should be 2 clk delay btwn TextLoad
   //& RegRdData so aes.v has time to react
   always @(posedge clk )
     if (!rst) begin
        RegRdData0  <= 1'b0;
        RegRdData1  <= 1'b0;
        RegRdData2  <= 1'b0;
        RegRdData3  <= 1'b0;
     end 
     else      begin 
        RegRdData0 <= RegRdData  ;
        RegRdData1 <= RegRdData0 ;
        RegRdData2 <= RegRdData1 ;
        RegRdData3 <= RegRdData2 ;
     end 
   
   
   always @(posedge clk ) //register pkt into local registers during a read
     if (!rst) begin
        TextRaw     <= 128'b0;
     end 
     else  begin //assuming pkt addr is pointing to the MSB of a data unit in the memory.
 	if (RegRdData0)   TextRaw[127:96] <= AesRdData  ; 
 	if (RegRdData1)   TextRaw[ 95:64] <= AesRdData  ;
 	if (RegRdData2)   TextRaw[ 63:32] <= AesRdData  ;
 	if (RegRdData3)   TextRaw[ 31:0 ] <= AesRdData  ;
     end 
   
   
   always @(posedge clk ) 
     if (!rst) begin
        TextOut     <= 128'b0;
     end 
     else  if (TextTrdy)   TextOut[127:0 ] <= TextXfd  ;

   
   always @(AesWrAdd[1:0] or TextOut) 
     case (AesWrAdd[1:0])
       2'b00:  AesWrData = TextOut[127:96] ;
       2'b01:  AesWrData = TextOut[ 95:64] ;
       2'b10:  AesWrData = TextOut[ 63:32] ;
       2'b11:  AesWrData = TextOut[ 31:0 ] ;
     endcase

	   



	   // AES Manager State Machine
	   // Continuesly reads/xforms/writes back into the holding buffer up to
	   // the entire content of the buffer or last pkt reached.

	   
	   always @(posedge clk )
	     if (!rst) begin
		state    <= IDLE;
		RdEnb    <= 1'b0;    
		WrEnb    <= 1'b0;    
		TextLoad  <= 1'b0;
		ClrCntrs <= 1'b0;
		RegRdData<= 1'b0;
		AesTrdy  <= 1'b0;
	     end 
	     else      begin 
		state    <= next;
      		RdEnb    <= RdEnb_nxt; 
      		WrEnb    <= WrEnb_nxt; 
		TextLoad  <= TextLoad_nxt;
		ClrCntrs <= ClrCntrs_nxt ;
		RegRdData<= RegRdData_nxt;
		AesTrdy  <= AesTrdy_nxt  ;
	     end 
   
   always @(state or AesIrdy or RdDone or Sos or LastPkt or WrDone or TextTrdy) begin
      RdEnb_nxt     = 1'b0;    //default values for all outputs
      WrEnb_nxt     = 1'b0; 
      TextLoad_nxt   = 1'b0;
      ClrCntrs_nxt  = 1'b0;
      RegRdData_nxt = 1'b0;
      AesTrdy_nxt  = 1'b0;
      FirstPkt     = 1'b0;

      case (state)
	IDLE: begin
	   next = IDLE;
	   if (AesIrdy) begin 
              next = RD1;  
              RdEnb_nxt = 1'b1;
              RegRdData_nxt = 1'b1;
           end 
	end
	
	RD1  : begin
	   next = RD1  ;
           RdEnb_nxt = 1'b1;
	   if (RdDone)  begin
	      next =  AES1; 
	      FirstPkt  = Sos;  //if first pkt of first session, assert FirstPkt
              RdEnb_nxt = 1'b0;
	      TextLoad_nxt = 1'b1 ;  // give me a pulse on the nxt clk to start AES
	   end
	end
	

	AES1: begin
	   if (LastPkt) 
	     next = WT2;
	   else begin
	      next = RDN ;
              RegRdData_nxt = 1'b1;
	   end
	end

	
	RDN: begin
	   next = RDN  ;
           RdEnb_nxt = 1'b1;
	   if (RdDone)  begin
	      next = WT1;
              RdEnb_nxt = 1'b0;
	   end	  
	end

	WT1: begin
	   next = WT1    ;
	   if (TextTrdy) begin
	      next = AESN  ;
	      TextLoad_nxt = 1'b1 ;  //  pulse on the nxt clk to start AES
	   end
	end
	
	
	
	AESN: begin
	   next = WR    ;
           WrEnb_nxt = 1'b1;
	end

	
	WR: begin
	   next = WR  ;
           WrEnb_nxt = 1'b1;
	   if (WrDone)
	     if  (LastPkt) 
	       next = WT2;
	     else begin
		next = RDN ;
		RdEnb_nxt = 1'b1;
                RegRdData_nxt = 1'b1;
	     end  
	end

	
	WT2: begin
	   next = WT2    ;
	   if (TextTrdy) begin
	      next = WRLAST;
	      WrEnb_nxt = 1'b1 ;
	   end
	end
	
	WRLAST: begin
	   next = WRLAST  ;
           WrEnb_nxt = 1'b1;
	   if (WrDone) begin
	      next = IDLE ;
	      ClrCntrs_nxt = 1'b1;
	      AesTrdy_nxt  = 1'b1;
	   end  
	end


	
	default:  next = IDLE ;
      endcase
   end



endmodule   // aesmgr

