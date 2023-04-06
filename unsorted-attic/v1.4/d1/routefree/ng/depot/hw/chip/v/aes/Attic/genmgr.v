d1 430
a430 427
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
// Filename        : genmgr.v
// Description     : This block interfaces to the cpu_ahb bus.
//                   Contrls operation of each of the other managers.
//                   Manages the rd & wr pointers.
//
//                   Nima Nikuie  --May 2 2005 
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
`timescale 1ps/1ps
`include "ahb_fdl_defs.v"


module genmgr ( 
		clk, rst,
		ExpKeyTrdy, ExpKeyIrdy, SecretKey, aes_iv, Cmd,                     //AES Block
		AesIrdy,  AesSize, AesTrdy, Sos,                            //AESMNGR Block
		DmaSize, MemAdd, MemBank, MemIrdy, MemRd_Wr, MemTrdy, dma_ahb_err,  //DMA Memory 
		cpu_htrans_i, cpu_haddr_i, cpu_hwrite_i,
		cpu_hsize_i, cpu_hburst_i, cpu_hwdata_i,
		cpu_hsel_i, cpu_hready_o, cpu_hready_smx_i,
		cpu_hresp_o, cpu_hrdata_o, cpu_hsplit_o, int_o
		); 

   //these params are declared to support either 64byte or 128byte mem buffers
   parameter   SBASE  =  1;  // 64B = 1;  128B = 2   Size BASE of the Num of pkts to process=[SBASE : 0]
   parameter   NOPKT  =  4;  // 64B = 4;  128B = 8   Number of pkts  processed each time in decimal
   
   input       clk;		// system clock;
   input       rst;		// controller and system reset;

   
   // interface to the AES Block
   input       ExpKeyTrdy;
   output      ExpKeyIrdy ;
   output [127:0] SecretKey ;
   output [127:0] aes_iv  ;
   output [1:0]   Cmd    ; //  0X= NOP;  10=Encrypt ;   11=Decrypt
   

   // interface to the aesmgr
   output 	  AesIrdy;     //starts packet processing
   output [SBASE:0] AesSize;        //indicates how many packets to process
   input 	    AesTrdy;     //indicates pkt processing done
   output           Sos    ;     //Start of session

   //interface to the ambmgr
   output [SBASE:0] DmaSize;       //indicates how many packets to rd or wr
   output [27:0]    MemAdd;     //Memory Rd/Wr Address of the begining of a pkt
   output 	    MemBank ;   //indicates which bank to operate on
   output 	    MemIrdy;    //starts memory rd/wr operation
   output 	    MemRd_Wr;   //1=rd ;  0=wr
   input 	    MemTrdy ;   
   input 	    dma_ahb_err ;  //set by bhm if error on the dma bus
   
   

   // sequencer interface to/from processor;

   input [1:0] 	    cpu_htrans_i;	// AMBA AHB Transfer Type
   input [9:0] 	    cpu_haddr_i;	// AMBA AHB Address
   input 	    cpu_hwrite_i;	// AMBA AHB Write Request
   input [2:0] 	    cpu_hsize_i;	// AMBA AHB Transfer Size
   input [2:0] 	    cpu_hburst_i;	// AMBA AHB Burst Type
   input [31:0]     cpu_hwdata_i;	// AMBA AHB Write Data
   input 	    cpu_hsel_i;	// AMBA AHB Selected Slave
   input 	    cpu_hready_smx_i; // AMBA AHB Current Active Slave Ready

   output 	    cpu_hready_o;	// AMBA AHB Slave Ready
   output [1:0]     cpu_hresp_o;	// AMBA AHB Response
   output [31:0]    cpu_hrdata_o;	// AMBA AHB Read Data
   output [15:0]    cpu_hsplit_o;	// AMBA AHB Split Release (bit per master)

   output 	    int_o;		// Interrupt
   

   // wires, registers
   wire 	    cpu_hready_o;		// HREADY will be 1ws for reads and 0ws for writes
   wire [1:0] 	    cpu_hresp_o = 2'h0;	// HRESP is always OKAY
   wire [15:0] 	    cpu_hsplit_o = 16'h0;	// The FLA slave interface does not support SPLIT
   reg  [31:0] 	    cpu_hrdata_o;
   
   reg [1:0] 	    cpu_htrans_i_d1;	// AMBA AHB Transfer Type
   reg [9:0] 	    cpu_haddr_i_d1;		// AMBA AHB Address
   reg 		    cpu_hwrite_i_d1;	// AMBA AHB Write Request
   reg [2:0] 	    cpu_hsize_i_d1;		// AMBA AHB Transfer Size
   reg [2:0] 	    cpu_hburst_i_d1;	// AMBA AHB Burst Type
   reg 		    cpu_hsel_i_d1;		// AMBA AHB Selected Slave
   reg 		    cpu_hready_smx_i_d1; 	// AMBA AHB Current Active Slave Ready

   reg [SBASE:0]    AesSize, NextAesSize;        //indicates how many packets to process
   reg 		    RegAesSize; 
   reg 		    Sos; 

   reg 		    ClrTrdyDone  ;
   reg 		    CurBank ;
   reg [2:0] 	    State ;

   wire [SBASE:0]   DmaSizeRd ;
   wire [SBASE:0]   DmaSizeWr ;

   reg    	    MemIrdy;    //starts memory rd/wr operation
   reg    	    AesIrdy;    //starts memory rd/wr operation
   reg    	    MemRd_Wr;   //1=rd ;  0=wr
   reg    	    int_o;  
   reg    	    ExpKeyIrdy;  

   wire [31:0] 	    Aes_ctrl;	// AES  control register fields bundle;
   reg 		    aes_busy, aes_mask, aes_mviol;
   reg [1:0] 	    aes_cmd  ;
   reg [9:0] 	    ctl_size ;
   reg [31:4] 	    RdPtr    ;      //Read  Pointer
   reg [31:4] 	    WrPtr    ;      //Write Pointer
   reg [31:0] 	    aes_iv1  ;      //1st 32 bit of the iv vector
   reg [31:0] 	    aes_iv2  ;      //2nd 32 bit of the iv vector
   reg [31:0] 	    aes_iv3  ;      //3rd 32 bit of the iv vector
   reg [31:0] 	    aes_iv4  ;      //4th 32 bit of the iv vector
   reg [31:0] 	    aes_key1  ;     //1st 32 bit of the key vector
   reg [31:0] 	    aes_key2  ;     //2nd 32 bit of the key vector
   reg [31:0] 	    aes_key3  ;     //3rd 32 bit of the key vector
   reg [31:0] 	    aes_key4  ;     //4th 32 bit of the key vector

   reg 		    MemRdDone, MemWrDone, AesDone ;
   
   parameter        IDLE  = 3'h0,
		    EXPKEY= 3'h1,
		    RD1   = 3'h2,
		    AES1  = 3'h3,
		    RDN   = 3'h4,
		    AES2  = 3'h5,
		    WR    = 3'h6,
		    WRLAST= 3'h7;




   // Flop all CPU AHB inputs except wdata  before use due to tight input timings
   always @(posedge clk)
     begin
	cpu_htrans_i_d1 <=  cpu_htrans_i;
	cpu_haddr_i_d1  <=  cpu_haddr_i;
	cpu_hwrite_i_d1 <=  cpu_hwrite_i;
	cpu_hsize_i_d1  <=  cpu_hsize_i;
	cpu_hburst_i_d1 <=  cpu_hburst_i;
	cpu_hsel_i_d1   <=  cpu_hsel_i;
	cpu_hready_smx_i_d1 <=  cpu_hready_smx_i;
     end 

   // PIO REGISTER ACCESS

   wire cpu_hreq_vld =  (cpu_hburst_i_d1 == 3'h0) && (cpu_hsize_i_d1 == 3'h2);
   wire reg_rd = cpu_hsel_i_d1 && cpu_hready_smx_i_d1 && !cpu_hwrite_i_d1 && cpu_htrans_i_d1[1];
   wire reg_wr = cpu_hsel_i_d1 && cpu_hready_smx_i_d1 &&  cpu_hwrite_i_d1 && cpu_htrans_i_d1[1];


   wire  aes_ctrl_we,   aes_exec_we, aes_rdptr_we, aes_wrptr_we, aes_key_we 	, aes_iv_we 	;


   assign aes_ctrl_we   = reg_wr && cpu_hreq_vld && (cpu_haddr_i_d1 == `AESCTRL) && !aes_busy;
   assign aes_exec_we   = reg_wr && cpu_hreq_vld && (cpu_haddr_i_d1 == `AESCTRL) ;
   assign aes_rdptr_we  = reg_wr && cpu_hreq_vld && (cpu_haddr_i_d1 == `AESRDPTR) && !aes_busy;
   assign aes_wrptr_we 	= reg_wr && cpu_hreq_vld && (cpu_haddr_i_d1 == `AESWRPTR) && !aes_busy;
   assign aes_key_we 	= reg_wr && cpu_hreq_vld && (cpu_haddr_i_d1 == `AESWKEY ) && !aes_busy;
   assign aes_iv_we 	= reg_wr && cpu_hreq_vld && (cpu_haddr_i_d1 == `AESWIV  ) && !aes_busy;

   // HREADY
   wire   cpu_hready_w;
   reg 	  cpu_hready_r;

   

   always @(posedge clk)
     begin
	cpu_hready_r <=  reg_rd;
     end

   assign cpu_hready_w = reg_wr;

   wire   snd_okay;
   assign snd_okay     = cpu_hsel_i_d1 && cpu_hready_smx_i_d1 && !cpu_htrans_i_d1[1];
   assign cpu_hready_o = cpu_hready_r  || cpu_hready_w        ||  snd_okay;

   reg    aes_exec;
   
   // register reads

   always @(posedge clk)
     begin
	if (reg_rd)
	  begin
	     if (cpu_hreq_vld)
	       begin
		  case (cpu_haddr_i_d1)
		    `AESCTRL : cpu_hrdata_o  <=  Aes_ctrl;
		    `AESRDPTR: cpu_hrdata_o  <=  {RdPtr , 4'b0} ;
		    `AESWRPTR: cpu_hrdata_o  <=  {WrPtr , 4'b0} ;
		    //`AESKEY : cpu_hrdata_o  <=  32'd0 ;   // Key & IV are not allowed to be readable
		    //`AESIV  : cpu_hrdata_o  <=  32'd0 ;

		    default:  cpu_hrdata_o  <=  32'h0;
		    
		  endcase // case(cpu_haddr_i_d1)
	       end
	     else
	       cpu_hrdata_o  <=  32'h0;
	  end	
     end

   assign Aes_ctrl = { aes_busy,  aes_mask, aes_mviol, aes_cmd, 17'b0, ctl_size  };


   wire   SessionDone = (State == WRLAST) && MemTrdy ;

   // register writes
   always @(posedge clk)
     begin
	if(rst) begin
	   aes_exec <= 1'b0;
	   aes_busy <= 1'b0 ;
	   aes_mask <= 1'b0 ;
	   aes_mviol<= 1'b0 ;
	   aes_cmd  <= 2'b00;
	end
	else  begin
	   if      (aes_exec_we)    aes_exec <= cpu_hwdata_i[31];  
	   else if (SessionDone)    aes_exec <= 1'b0 ;

	   if(aes_ctrl_we) begin
	      aes_busy <= cpu_hwdata_i[31]? 1'b1 : aes_busy ;   //sets when a session is started
	      aes_mask <= cpu_hwdata_i[30];
	      aes_mviol<= cpu_hwdata_i[31]? 1'b0 : aes_mviol ;  //clear on writing 1 into exec bit
	      aes_cmd  <= cpu_hwdata_i[28:27];
	   end 
	   else begin 
	      if ( MemTrdy && dma_ahb_err ) aes_mviol<=  1'b1 ; //set MemViolation. reset when wr 1 to exec
	      if (SessionDone)    aes_busy <= 1'b0 ;      //clear busy when session is done
	      if (!aes_exec)         int_o <= 1'b0 ; 
	      else if (SessionDone)  int_o <= aes_mask ;  //when done, interrupt if not masked.
	   end
	end
	
	if(aes_ctrl_we) ctl_size <= cpu_hwdata_i[9:0];  //length of zero = 1 pkt;  10'hFFF = all done
	else   if (MemTrdy && MemRd_Wr && MemIrdy)      // reduce the size each time there is memory read
	  if (ctl_size >= NOPKT )   ctl_size <= ctl_size - NOPKT ; 
	  else                      ctl_size <= 10'b1111111111   ; 

	if(aes_rdptr_we) RdPtr <= cpu_hwdata_i[31:4];  //advance RdPtr with every memory rd.
	else   if (MemTrdy && MemRd_Wr && MemIrdy ) 
	  RdPtr <=  RdPtr + DmaSizeRd + 28'b1 ;

	if(aes_wrptr_we) WrPtr <= cpu_hwdata_i[31:4];  //advance WrPtr with every memory wr.
	else   if (MemTrdy && !MemRd_Wr && MemIrdy ) 
	  WrPtr <=  WrPtr + DmaSizeWr + 28'b1 ; //DmaSizeWr is zero based, henc "+1".

	if (MemTrdy && MemRd_Wr && MemIrdy)    NextAesSize  <= ctl_size ; //remember how many pkt were just read
	if (RegAesSize)    AesSize  <=  NextAesSize  ;

	if(aes_key_we) aes_key4 <= cpu_hwdata_i[31:0];  //push the key vector 32 bits at a time
	if(aes_key_we) aes_key3 <= aes_key4 ;
	if(aes_key_we) aes_key2 <= aes_key3 ;
	if(aes_key_we) aes_key1 <= aes_key2 ;

	if(aes_iv_we) aes_iv4 <= cpu_hwdata_i[31:0];    //push the iv vector 32 bits at a time
	if(aes_iv_we) aes_iv3 <= aes_iv4 ;
	if(aes_iv_we) aes_iv2 <= aes_iv3 ;
	if(aes_iv_we) aes_iv1 <= aes_iv2 ;

	
     end


   // Managing Trdy signals.
   always @(posedge clk)
     if(rst) begin
        MemRdDone <= 1'b0 ;
        MemWrDone <= 1'b0 ;
	AesDone   <= 1'b0 ;
     end
     else begin
	if (MemTrdy &&  MemRd_Wr)  MemRdDone <= 1'b1; else if (ClrTrdyDone) MemRdDone <= 1'b0 ;
	if (MemTrdy && !MemRd_Wr)  MemWrDone <= 1'b1; else if (ClrTrdyDone) MemWrDone <= 1'b0 ;
	if (AesTrdy)               AesDone   <= 1'b1; else if (ClrTrdyDone) AesDone   <= 1'b0 ;
     end


   
   wire    LastPkt   = (ctl_size == 10'b1111111111 ) |  (aes_exec==1'b0); //stop if zero writen to exec bit
   assign  DmaSizeRd = (ctl_size >= NOPKT ) ? (NOPKT-1) : ctl_size[SBASE:0]  ; 
   assign  DmaSizeWr = (State==WR) ? (NOPKT-1) : AesSize; //always NOPKT during WR & the remainder at WRLAST
   assign  DmaSize   = MemRd_Wr ?  DmaSizeRd : DmaSizeWr ; //DmaSize is zero based: 0=1pkt...3=4pkt
   assign  MemBank   = CurBank ;
   assign  MemAdd    = MemRd_Wr ?  RdPtr : WrPtr ;
   //assign  AesBank   = !CurBank ;
   assign  Cmd       = aes_cmd  ;
   assign  SecretKey = {aes_key4, aes_key3, aes_key2, aes_key1 } ;
   assign  aes_iv    = {aes_iv4, aes_iv3,  aes_iv2,  aes_iv1  } ;
   
   always @(posedge clk) 
     if (!rst) begin
	State    <= IDLE ;
	AesIrdy  <= 1'b0 ;     
	MemIrdy  <= 1'b0 ;     
     end
     else begin
	RegAesSize    <= 1'b0;
	ClrTrdyDone   <= 1'b0;

	case (State)
	  IDLE: begin
	     State   <= IDLE;
	     CurBank <= 1'b0 ;  //Always start with Bank 0
	     if (aes_exec) begin 
		if (aes_cmd == 2'b11)  begin
		   State      <= EXPKEY;
		   ExpKeyIrdy <= 1'b1 ;
		end
		else
		  State <= RD1   ;
             end 
	  end
	  
	  EXPKEY  :   if (ExpKeyTrdy) begin    State <= RD1 ; ExpKeyIrdy <= 1'b0  ; end 
	  
	  RD1  : begin
	     MemRd_Wr  <= 1'b1 ;
	     MemIrdy   <= 1'b1 ;
	     if (MemTrdy)  begin
		State      <= AES1 ;
		MemIrdy    <= 1'b0 ;
		ClrTrdyDone<= 1'b1 ;
		RegAesSize <= 1'b1 ;      //one clk pulse to reg and hold the AesSize signal
		CurBank    <= !CurBank ;  //Toggle current bank
	     end
	  end
	  
	  AES1  : begin
	     AesIrdy    <=  1'b1 ;     
	     Sos        <=  1'b1 ;     
	     if (LastPkt)  
	       if (AesTrdy) begin
		  State   <=  WRLAST ;
		  CurBank <=  !CurBank ; 
		  AesIrdy    <=  1'b0 ;     
	          Sos        <=  1'b0 ;     
	       end
	       else State <=  RDN ;
	  end
	  
	  RDN  : begin
	     MemRd_Wr  <= 1'b1 ;
	     MemIrdy   <= 1'b1 ;
	     if (MemRdDone && AesDone)  begin
		State       <= AES2 ;
		MemIrdy     <= 1'b0 ;
		AesIrdy     <= 1'b0 ;
	        Sos         <= 1'b0 ;     
		ClrTrdyDone <= 1'b1 ;
		RegAesSize <= 1'b1 ;      //one clk pulse to reg and hold the AesSize signal
		CurBank     <=  !CurBank ;  //Toggle current bank
	     end
	  end
	  
	  
	  AES2 : begin
	     AesIrdy    <= 1'b1 ;     
	     State      <= WR ;
	  end
	  
	  WR  : begin
	     MemRd_Wr  <= 1'b0 ;
	     MemIrdy   <= 1'b1 ;
	     if (LastPkt)  
	       if (MemWrDone && AesDone) begin
		  State    <=  WRLAST ;
		  MemIrdy     <= 1'b0 ;
		  AesIrdy     <= 1'b0 ;
		  ClrTrdyDone <= 1'b1 ;
		  CurBank  <=  !CurBank ;  //Toggle current bank
	       end
	       else 
		 if (MemTrdy)  begin
		    State     <=  RDN ;
		    MemIrdy   <= 1'b0 ;
		 end
	  end
	  
	  WRLAST  : begin
	     MemRd_Wr  <= 1'b0 ;
	     MemIrdy   <= 1'b1 ;
	     if (MemTrdy)  begin
		State       <=  IDLE ;
		MemIrdy     <= 1'b0 ;
		AesIrdy     <= 1'b0 ;
		ClrTrdyDone <= 1'b1 ;
	     end
	  end
	  
	  default:  State= IDLE ;
	endcase
     end


endmodule // genmgr
