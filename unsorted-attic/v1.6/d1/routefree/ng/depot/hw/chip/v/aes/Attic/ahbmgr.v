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
// Filename        : ahbmgr.v
// Description     : This block interfaces to the cpu_ahb bus.
//                   Contrls operation of each of the other managers.
//                   Manages the rd & wr pointers.
//
//                   Nima Nikuie  --May 2 2005 
//
//  CVS Log
//
//  $Id: ahbmgr.v,v 1.5 2005/05/18 21:52:39 nima Exp $
//
//  $Date: 2005/05/18 21:52:39 $
//  $Revision: 1.5 $
//  $Author: nima $
//  $Locker:  $
//  $State: Exp $
//
//  Change History:
//               $Log: ahbmgr.v,v $
//               Revision 1.5  2005/05/18 21:52:39  nima
//               ran dos2unix on all files
//
//               Revision 1.4  2005/05/18 21:28:17  nima
//               added the BroadOn banner
//
//
//
//
//
`timescale 1ps/1ps
`include "ahb_fdl_defs.v"


module ahbmgr ( 
		clk, rst, ScanMode,
		DmaSize, MemAdd, MemBank, MemIrdy, MemRd_Wr, MemTrdy, dma_ahb_err,  //GenMgr
                AesWr,  AesRd,  AesRdAdd, AesWrAdd, AesWrData, AesRdData ,  //AesMgr    
		f2m_req, f2m_write, f2m_addr, f2m_len, dma_hwdata_o,                //fla_hbm
		m2f_ack, m2f_frvalid, m2f_fwvalid, m2f_viol,  dma_hrdata_i          //fla_hbm
		);

   //these params are declared to support either 64byte or 128byte mem buffers
   parameter   SBASE  =  1;  // 64B = 1;  128B = 2   Size BASE of the Num of pkts to process=[SBASE : 0]
   parameter   NOPKT  =  4;  // 64B = 4;  128B = 8   Number of pkts  processed each time in decimal
   parameter   ADDW   =  3;  // 64B = 3;  128B = 4   ADDress Width of the RD/WR add cntrs to pkt buffer

   input       clk;		// system clock;
   input       rst;		// controller and system reset;
   input       ScanMode;		

   
   //interface to the GenMgr
   input [SBASE:0] DmaSize;       //indicates how many packets to rd or wr
   input [27:0]    MemAdd;     //Memory Rd/Wr Address of the begining of a pkt
   input 	   MemBank ;   //indicates which bank to operate on
   input 	   MemIrdy;    //starts memory rd/wr operation
   input 	   MemRd_Wr;   //1=rd ;  0=wr
   output 	   MemTrdy ;   
   output 	   dma_ahb_err ;  //set by bhm if error on the dma bus

   
   // interface to the AesMgr
   input 	   AesWr    ;
   input 	   AesRd    ;
   input [ADDW:0]  AesRdAdd ; 
   input [ADDW:0]  AesWrAdd ;
   input [31:0]    AesWrData ;
   output [31:0]   AesRdData ;


   // interface to the fla_hbm from Peter
   output 	   f2m_req;        // transaction request to mem;
   output [5:0]    f2m_len;        // length of transfer, One based. for 64byte , max=16; 
   				   //                                for 128byte, max=32
   output 	   f2m_write;      // 0=mem write to flash, 1=flash write to mem;
   output [25:2]   f2m_addr;       // transaction start address (word aligned);
   output [31:0]   dma_hwdata_o;	// AMBA AHB Write Data

   input 	   m2f_ack;        // transaction ack from mem; This pulse marks the end of mem access
   input 	   m2f_fwvalid;    // mem data to flash valid this clock;
   input 	   m2f_frvalid;    // mem accepting flash data this clock;
   input 	   m2f_viol;       // illegal transaction, abort now iff m2f_ack;
   input [31:0]    dma_hrdata_i;	// AMBA AHB Read Data


   reg [ADDW:0]    dma_BufAdd ; //one buffer address used for rd & wr to both banks !!!
   reg [31:0] 	   dma_hwdata_o;	// AMBA AHB Write Data

   reg   	   MemIrdy_d; 
   reg    	   f2m_req;        // transaction request to mem;

   wire            MemIrdyP, m2f_valid , ExtraP,  B0, B1;

   assign 	   MemIrdyP  =  MemIrdy  & !MemIrdy_d ;  //pulse at the rising edge of Irdy
   assign 	   m2f_valid =  MemRd_Wr ?  m2f_fwvalid  :  m2f_frvalid  ;
   assign 	   ExtraP    = !MemRd_Wr && MemIrdyP ;  //extra pulse to do a read ahead of the buffer 
   assign B0      = !MemBank ;
   assign B1      =  MemBank ;

   wire [31:0]   B0RdData, B1RdData ;

   // 
   always @(posedge clk)
     if(rst) begin
	f2m_req     <= 1'b0 ;
        dma_BufAdd   <= 0 ;
     end
     else begin
	MemIrdy_d   <=  MemIrdy ;
	if            (MemIrdyP)     f2m_req  <= 1'b1 ;          else if (m2f_ack) f2m_req    <= 1'b0 ;
	if (m2f_valid || ExtraP)  dma_BufAdd  <= dma_BufAdd + 1; else if (m2f_ack) dma_BufAdd <= 0 ;
        if (m2f_valid || ExtraP) dma_hwdata_o <= B1 ? B1RdData : B0RdData ;
     end




   wire  [ADDW:0]  B0WrAdd, B0RdAdd ;
   wire  [ADDW:0]  B1WrAdd, B1RdAdd ;
   wire  [31:0]  B0Din, B1Din ;
   wire  B0WrEnb, B1WrEnb ;


   assign B0Din   = B0 ? dma_hrdata_i : AesWrData ;  //Wr to buffer when rd from Mem or write from aes
   assign B0WrAdd = B0 ? dma_BufAdd   : AesWrAdd  ;
   assign B0RdAdd = B0 ? dma_BufAdd   : AesRdAdd  ;
   assign B0WrEnb = B0 ? m2f_fwvalid  : AesWr     ; 

   assign B1Din   = B1 ? dma_hrdata_i : AesWrData ;  //Wr to buffer when rd from Mem or write from aes
   assign B1WrAdd = B1 ? dma_BufAdd   : AesWrAdd  ;
   assign B1RdAdd = B1 ? dma_BufAdd   : AesRdAdd  ;
   assign B1WrEnb = B1 ? m2f_fwvalid  : AesWr     ; 

   assign AesRdData  = B0 ? B1RdData : B0RdData ;

   assign  f2m_addr  = {MemAdd[21:0] , 2'b00}  ; //check make sure this is all right.....<<<<<
   assign f2m_len   = {DmaSize + 4'b1, 2'b00} ; // length of transfer, either 4(64byte)  or 8 (128byte) ;
   assign  f2m_write =  MemRd_Wr;                // 0=mem write to flash, 1=flash write to mem;

   assign MemTrdy     = m2f_ack;
   assign dma_ahb_err = m2f_viol;       




   // This design assumes that these regfiles are asynch access.
   Mem1R1W16x32  Bank0 (
			.RdClk(clk),
			.WrClk(clk),
			.ScanMode(ScanMode),
			.e1WrEn(B0WrEnb),
			.e1RdAdr(B0RdAdd),
			.e1WrAdr(B0WrAdd),
			.e1WrDat(B0Din),
			.RdDat(B0RdData) );

   Mem1R1W16x32  Bank1 (
			.RdClk(clk),
			.WrClk(clk),
			.ScanMode(ScanMode),
			.e1WrEn(B1WrEnb),
			.e1RdAdr(B1RdAdd),
			.e1WrAdr(B1WrAdd),
			.e1WrDat(B1Din),
			.RdDat(B1RdData) );


   
endmodule  

