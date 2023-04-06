 /************************************************************************\
 *									  *
 *		 Copyright (C) 1994, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs	 contain  *
 *  unpublished	 proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright	law.  They  may not be disclosed  *
 *  to	third  parties	or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 \************************************************************************/

// $Id: pi_controller.v,v 1.1 2002/05/21 23:55:44 berndt Exp $
// SCCSID: %W% %G%

/************************************************************************
	   PERIPHERAL INTERFACE CONTROLLER (PI_CONTROLLER) MODULE

  Peripheral Interface Controller, manages the transfer of data between
  DRAM and peripherals on the AD16 bus.  It consist mainly of a 128-byte
  buffer and two state-machines.  The state-machines coordinates the
  transfer as well as generate the appropriate bus signals adhering to
  the specified bus protocol.
 ************************************************************************/
module pi_controller(
  /* Rsvd    */	clock,		reset_l,
  /* GENERAL */	osr_pic_intr,	osr_io_busy,
  /* DMA     */	icw_dma_grant,	icw_dma_start,	icw_dma_last,	ocr_dma_req,
		ocr_dma_read,	ocr_dma_len,	oar_dma_addr,
  /* CMD REG */	icw_reg_wenb,	icw_reg_addr,	iaw_ioc_addr,	idw_reg_wdata,
		odw_reg_rdata,
  /* AD BUS  */	osr_adb_aleh,	osr_adb_alel,	osr_adb_rd_l,	osr_adb_wr_l,
		idw_adb_din,	ocr_adb_oenb_l,	odr_adb_dout,
  /* DX BUF  */	ocr_buf_wenb,	oaw_buf_addr,	odr_buf_din,	idw_buf_dout,
  /* DBUS    */	icw_dbu_oenb,	tbw_dbu_data);
  
  `include "pi.vh"

  /**********************************************************************
    DATA TRANSFER (MASTER) STATE MACHINE
    Note: state encoding below are optimized for timing.  be careful in
	  re-assigning state values!
   **********************************************************************/
  parameter DSM_IDLE = 4'b0000;		// idle-wait for req from CPU
  parameter DSM_DLEN = 4'b0001;		// calc DMA length taking into
					// account data xfer length
  parameter DSM_PLEN = 4'b0011;		// calc DMA length taking into
					// account 2K page boundary
					// DRAM -> BSD
  parameter DSM_RREQ = 4'b0111;		// request DMA read from DRAM
  parameter DSM_RDMA = 4'b1011;		// perform DMA read from DRAM
  parameter DSM_RADB = 4'b1111;		// write data to BSD
					// BSD -> DRAM
  parameter DSM_WADB = 4'b1100;		// read data from BSD
  parameter DSM_WREQ = 4'b0100;		// request DMA write to DRAM
  parameter DSM_WDMA = 4'b1000;		// perform DMA write to DRAM
  parameter DSM_IORW = 4'b1110;		// perform special IO rd/wr

  /**********************************************************************
    AD16 BUS PROTOCOL (SLAVE) STATE-MACHINE
    Note: state encoding below are chosen to make encoding of AD16 bus
	  signals straight-forward.
	  Bits 1 and 0 are ALEH and ALEL, respectively.
	  Bits (3 & 2) indicate read/write cycle - used	in qualifying
		RD_ and WR_ signals.
	  Bit 2 is used to differenciate between RD_WR and RELRW at the
		adder input mux.
   **********************************************************************/
  parameter ASM_STDBY = 4'b01_10;	// standby
  parameter ASM_HIADR = 4'b01_11;	// issue high 16b of address
  parameter ASM_LOADR = 4'b01_01;	// issue low 16b of address
  parameter ASM_LWAIT = 4'b01_00;	// gen dev specific latency
  parameter ASM_RD_WR = 4'b11_00;	// perform read/write
  parameter ASM_RELRW = 4'b10_00;	// release from read/write
  parameter ASM_PGBRK = 4'b10_10;	// pause for page break
  parameter ASM_PAUSE = 4'b00_00;	// pause while we DMA data

  /**********************************************************************
    INPUT/OUTPUT DECLARATIONS
   **********************************************************************/
  input				clock;		// system clock
  input				reset_l;	// system reset asserted low
  
  output			osr_pic_intr;	// PIC interrupt reg
  output			osr_io_busy;	// IO busy reg

  input				icw_dma_grant;	// grant the DMA operation
  input				icw_dma_start;	// start the DMA operation
  input				icw_dma_last;	// end the DMA operation
  output			ocr_dma_req;	// DMA request signal
  output			ocr_dma_read;	// DMA read/write select
  output [DMA_LENGTH_SIZE-1:0]	ocr_dma_len;	// DMA length in words
  output [DRAM_ADDRESS_SIZE-1:0] oar_dma_addr;	// DMA slave address

  input				icw_reg_wenb;	// cmd reg write enable
  input	 [PI_REG_ADDRESS_SIZE-1:0] icw_reg_addr;// cmd reg read/write addr
  input	 [31:0]	iaw_ioc_addr;	// CBUS io read addr
  input	 [31:0]	idw_reg_wdata;	// cmd reg write data fr CBUS
  output [31:0]	odw_reg_rdata;	// reg read data to CBUS

  output			osr_adb_aleh;	// high addr latch enable
  output			osr_adb_alel;	// low addr latch enable
  output			osr_adb_rd_l;	// read from BSD enable
  output			osr_adb_wr_l;	// write to BSD enabbl
  input	 [`PIC_ADB_WIDTH-1:0]	idw_adb_din;	// AD16 address/data in
  output			ocr_adb_oenb_l;	// AD16 bus output enable
  output [`PIC_ADB_WIDTH-1:0]	odr_adb_dout;	// AD16 address/data out

  output			ocr_buf_wenb;	// write enable control reg
  output [`PIC_BUF_ADRSZ-4:0]	oaw_buf_addr;	// addr (to buffer)
  output [`PIC_BUF_LNWDTH-1:0]	odr_buf_din;	// input (to buffer) data reg
  input	 [`PIC_BUF_LNWDTH-1:0]	idw_buf_dout;	// output (fr buffer) data reg
  
  input				icw_dbu_oenb;	// DBUS output enable
  inout	 [DBUS_DATA_SIZE-1:0]	tbw_dbu_data;	// DMA DBUS
  
  /**********************************************************************
    REGISTER/VARIABLE DEFINITIONS
   **********************************************************************/

  /**************************************************************
    PERIPHERAL INTERFACE
   **************************************************************/
  reg				osr_pic_error;	// Error bit reg
  reg				osr_pic_intr;	// PIC busy output reg
  reg				lsw_pic_busy;	// PIC busy reg next
  reg				lsr_pic_busy;	// PIC busy output reg
  reg				lsw_io_busy;	// IO busy reg next
  reg				osr_io_busy;	// IO busy output reg
  reg				ocr_dma_req;	// DMA req output reg
  reg				icr_dma_last;	// end the DMA operation
  reg				ocr_dma_read;	// DMA read output reg
  reg  [DMA_LENGTH_SIZE-1:0]	lcw_dma_len;	// DMA length
  reg  [DMA_LENGTH_SIZE-1:0]	ocr_dma_len;	// DMA length reg
  reg  [DRAM_ADDRESS_SIZE-1:0]	law_dma_addr;	// DMA addr
  reg  [DRAM_ADDRESS_SIZE-1:0]	oar_dma_addr;	// DMA addr reg
  reg  [31:0]	odw_reg_rdata;	// reg read data to CBUS
  
  /**************************************************************
    AD16 BUS
   **************************************************************/
  reg				lcw_adb_expire;	// adb_len down to zero
  reg				lcw_adb_done;	// done signal
  reg				lcw_adb_pgbrk;	// page break signal
  reg				lcr_adb_pgbrk;	// page break signal reg
  reg				lcw_adb_cntdn;	// delay counter done
  reg				osr_adb_rd_l;	// read from BSD enable
  reg				osr_adb_wr_l;	// write to BSD enabbl
  reg  [`PIC_ADB_CYCTR_SZ-1:0]	lcw_adb_cycs;	// delay counter (temp)
  reg  [`PIC_ADB_CYCTR_SZ-1:0]	lcr_adb_cycs;	// delay counter
  reg  [DMA_LENGTH_SIZE-1:0]	lcw_adb_len;	// length reg input
  reg  [DMA_LENGTH_SIZE-1:0]	lcr_adb_len;	// length reg
  reg  [`PIC_ADB_WIDTH-1:0]	ldw_adb_dout;	// data output reg
  reg				ocr_adb_oenb_l;	// bus output enable reg
  reg  [PBUS_ADDRESS_SIZE-1:0]	law_adb_addr;	// addr reg
  reg  [PBUS_ADDRESS_SIZE-1:0]	oar_adb_addr;	// addr reg
  reg  [`PIC_ADB_WIDTH-1:0]	odr_adb_dout;	// bus output reg
  
  /**************************************************************
    BSD - BLOCK STORAGE DEVICE(S)
   **************************************************************/
  reg				lcw_bsd_dom;	// current addr domain
  reg  [`PIC_ADB_LAREG_SZ-1:0]	lcr_bsd_lat1;	// latency reg dom 1
  reg  [`PIC_ADB_LAREG_SZ-1:0]	lcr_bsd_lat2;	// latency reg dom 2
  reg  [`PIC_ADB_PWREG_SZ-1:0]	lcr_bsd_pwd1;	// pulse width reg dom 1
  reg  [`PIC_ADB_PWREG_SZ-1:0]	lcr_bsd_pwd2;	// pulse width reg dom 2
  reg  [`PIC_ADB_PGREG_SZ-1:0]	lcw_bsd_pgsz;	// page size for cur domain
  reg  [`PIC_ADB_PGREG_SZ-1:0]	lcr_bsd_pgs1;	// page size reg dom 1
  reg  [`PIC_ADB_PGREG_SZ-1:0]	lcr_bsd_pgs2;	// page size reg dom 2
  reg  [`PIC_ADB_RLREG_SZ-1:0]	lcr_bsd_rls1;	// release duration dom 1
  reg  [`PIC_ADB_RLREG_SZ-1:0]	lcr_bsd_rls2;	// release duration dom 2

  /**************************************************************
    STATE-MACHINES
    Note: asm_go only need not be latched because we know for sure
	  that the ASM state-machine has time to return to standby
	  and remain there for at least three cycles which satisfies
	  the AD16 Bus spec.  Therefore, our cycle counter _adb_cycs
	  is guaranteed (by spec, not by design) to have expired.
	  This would change if the required time in standby is
	  lengthened.  We may then have to latch asm_go.
   **************************************************************/
  reg				lcw_dsm_godx;	// go service data xfer req
  reg				lcw_dsm_iorw;	// go service special IO r/w
  reg  [`PIC_DSM_SIZE-1:0]	lcr_dsm_st;	// data xfer SM current state
  reg  [`PIC_DSM_SIZE-1:0]	lcw_dsm_st_nx;	// data xfer SM next state
  reg				lcr_dsm_expire;	// dsm_len down to zero
  reg  [`PIC_LENGTH_SIZE-1:0]	lcw_dsm_len;	// data xfer length reg
  reg  [`PIC_LENGTH_SIZE-1:0]	lcr_dsm_len;	// data xfer length reg

  reg				lcw_asm_go;	// AD16 bus SM go
  reg  [`PIC_ASM_SIZE-1:0]	lcr_asm_st;	// AD16 bus SM current state
  reg  [`PIC_ASM_SIZE-1:0]	lcw_asm_st_nx;	// AD16 bus SM next state

  reg				lcr_dsm_reset;	// abort/soft reset

  /**************************************************************
    ADDER - not generic.
   **************************************************************/
  reg				lsw_inc_co;	// carry out (top)
  reg  [PBUS_ADDRESS_SIZE-1:17]	ldw_inc_s;	// inc sum
  reg				lsw_dec_co;	// carry out (top)
  reg  [PBUS_ADDRESS_SIZE-1:17]	ldw_dec_s;	// inc sum

  reg  [16: 1]			ldw_add_op2i;	// input operand 2 sub
  reg  [PBUS_ADDRESS_SIZE-1:0]	ldw_add_op1;	// input operand 1
  reg  [6:0]			ldw_add_op2;	// input operand 2
  reg				lcw_add_sub;	// subtract control
  reg				lcw_add_ci;	// carry in
  reg  [15:8]			lsw_add_co0;	// carry out
  reg  [15:8]			lsw_add_co1;	// carry out
  reg  [16:9]			ldw_add_s0;	// output
  reg  [16:9]			ldw_add_s1;	// output
  reg  [15:0]			lsw_add_co;	// carry out (pgs)
  reg  [PBUS_ADDRESS_SIZE-1:1]	ldw_add_s;	// output
  reg  [PBUS_ADDRESS_SIZE-1:0]	ldw_add_sum;	// output
  reg  [PBUS_ADDRESS_SIZE-1:0]	ldw_add_dif;	// output
  reg				lsw_add_lt;	// less than (op1<op2)

  reg  [31:0]	odr_ioc_data;	// AD IO data reg

  
  /**********************************************************************
    128-BYTE DATA TRANSFER BUFFER (BUFFER)

                             <<<  DATAPATH  >>>
                             
                              dbu_data     reg_wdata          adb_din
                                 |             |                 |
                                 /64           /32               /16
                                 +=========+===|=====+=========+ |
                                 | +=======|=+=|=====|=+=======|=+
                   _____         | | +=====|=|=+     | |       | |
      buf_wdbu--->|     |        | | | +-+ | | | +-+ | | +-+-+ | | +-+-+
      buf_wadb--->| COMB|  8    _V_V_V_V_|_V_V_V_V_|_V_V_V_V_|_V_V_V_V_|
      buf_wiod--->|LOGIC|--/--->\__4:1__/|\__4:1__/|\__4:1__/|\__4:1__/|
            +====>|_____|           |    |    |    |    |    |    |    |
            |                   ____V____|____V____|____V____|____V____|
            |[2:1]             |>________|>________|>________|>_buf_din|
            |                       +====+    +====+    +====+    +====+
            |                       +=========+=========|=======+ |
       _    |                   ____V_________V_________V_______|_V____
      | |   |                  |   DI0       DI1       DI2      |DI3   |
      | |===+=buf_addr[6:3]===>|A                               |      |
      |>|   |                  |                                |      |
        _   +=========+        |         64b x 16 REGISTER FILE |      |
       | |            |        |                                |      |
       | |--buf_wenb--|------->|WEN                             |      |
       |>|            |        |___DO0_______DO1_______DO2______|DO3___|
                      |             |[63:48]  |[47:32]  |[31:16]| |[15:0]
                      |             +=+       +=+       +=+     | +=+
                      |         ____V_|__ ____V_|__ ____V_|__ __|_V_|__
                      | always@|>_____|__|>_____|__|>_____|__|>_|___|__|
                      |             | |       | |       | |     | | |
                      |             +=|=======+=|=======+=|=====|=+ | buf_dout
                      |          ___|_V_________V_________V_____|___V_____
                [2:1] +=========>\__|_______________4:1_________|________/
                                    |                |          | 
                                    /[63:0]          /16        /32
                                    |            ____V____  ____V____ 
                                    |           |>________||>________|
                                    |                |          |     
                                    V                V          V     
                                 dbu_data         adb_dout   ioc_data
    
   **********************************************************************/
  reg				lcw_buf_wdbu;	// DBUS buffer write select
  reg				lcw_buf_wadb;	// bus buffer write select
  reg                           lcw_buf_wiod;	// buffer write select
  reg				lcw_buf_wenb;	// write enable control
  reg				ocr_wenb_unbuf;	// write enable control reg
  reg  [`PIC_BUF_LNWDTH-1:0]	idr_buf_dout;	// data buffer output reg
  reg  [`PIC_BUF_ADRSZ-1:0]	law_buf_addr;	// addr (to buffer)
  reg  [`PIC_BUF_ADRSZ-1:0]	oar_buf_addr;	// addr (to buffer) reg
  reg  [`PIC_BUF_LNWDTH-1:0]	ldw_buf_din;	// data buffer input reg
  reg  [`PIC_BUF_LNWDTH-1:0]	odr_buf_din;	// data buffer input reg

  wire				ocr_buf_wenb;   // buffer to remove hold problem
  ni01d2 uocr_buf_wenb (.i(ocr_wenb_unbuf), .z(ocr_buf_wenb));


  /**********************************************************************
		    < <	 S E R I O U S	 S T U F F  > > (START)
   **********************************************************************/
  /**********************************************************************
    BCADD8 - 
   **********************************************************************/
  function [15:0] bcadd8;	// 8b adder that gen sum and all carries
    input [7:0] a;		// input operand 1
    input [7:0] b;		// input operand 2
    input ci;			// carry in
  
    reg [7:0] p0z;
    reg [7:0] p1;
    reg [7:0] p2z;
    reg [7:0] p3;
    reg [7:0] g0z;
    reg [7:0] g1;
    reg [7:0] g2z;
    reg [7:0] g3;
    reg [7:0] x;

    begin
	// LEVEL 0-: initial p, g generation
	p0z = ~(a | b);						// nr02d2's
	g0z = ~(a & b);						// nd02d2's
	x   =  (a ^ b);						// xo02d2's
      
	// LEVEL 1+: binary p, g propagation
	p1  = ~(p0z | { p0z[6:0], 1'b0 });			// nr02d2's
	g1  = ~((p0z | { g0z[6:0], 1'b1 }) & g0z);		// oa04d2's
      
	// LEVEL 2-: binary p, g propagation
	p2z = ~(p1 & { p1[5:0], 2'b11 });			// nd02d2's
	g2z = ~((p1 & { g1[5:0], 2'b0 }) | g1);			// ao04d1's
      
	// LEVEL 3+: binary p, g propagation
	p3  = ~(p2z | { p2z[3:0], 4'b0 });			// nr02d2's
	g3  = ~((p2z | { g2z[3:0], 4'hF }) & g2z);		// oa04d2's
      
	// Sum and Carry generation
	bcadd8[15:8] = ( {8{ci}} & p3) | g3;			// ao04d1's
	bcadd8[7:0] = { bcadd8[14:8], ci } ^ x;			// xo02d2's
    end
  endfunction // bcadd8

  /**************************************************************
    COMMAND REGISTER READ MUX

    Note: might remove osr_pic_intr later.  only for chn's debug.
   **************************************************************/
  always @(icw_reg_addr	   or
	   oar_dma_addr	   or
	   oar_adb_addr	   or
	   ocr_dma_len	   or
	   lcr_bsd_lat1    or
	   lcr_bsd_pwd1    or
	   lcr_bsd_pgs1    or
	   lcr_bsd_rls1    or
	   lcr_bsd_lat2    or
	   lcr_bsd_pwd2    or
	   lcr_bsd_pgs2    or
	   lcr_bsd_rls2    or
	   osr_pic_intr	   or
	   lsr_pic_busy	   or
	   osr_io_busy	   or
	   osr_pic_error   or
	   odr_ioc_data	   ) begin
    case (icw_reg_addr)
      PI_DRAM_ADDRESS_REG : odw_reg_rdata = oar_dma_addr;
      PI_PBUS_ADDRESS_REG : odw_reg_rdata = oar_adb_addr;
      PI_READ_LENGTH_REG,
      PI_WRITE_LENGTH_REG : odw_reg_rdata = ocr_dma_len;
      PI_STATUS_REG	  : odw_reg_rdata =
				{ osr_pic_intr, osr_pic_error,
				  osr_io_busy,  lsr_pic_busy };
      PI_BSD_DOM1_LAT_REG : odw_reg_rdata = lcr_bsd_lat1;
      PI_BSD_DOM1_PWD_REG : odw_reg_rdata = lcr_bsd_pwd1;
      PI_BSD_DOM1_PGS_REG : odw_reg_rdata = lcr_bsd_pgs1;
      PI_BSD_DOM1_RLS_REG : odw_reg_rdata = lcr_bsd_rls1;
      PI_BSD_DOM2_LAT_REG : odw_reg_rdata = lcr_bsd_lat2;
      PI_BSD_DOM2_PWD_REG : odw_reg_rdata = lcr_bsd_pwd2;
      PI_BSD_DOM2_PGS_REG : odw_reg_rdata = lcr_bsd_pgs2;
      PI_BSD_DOM2_RLS_REG : odw_reg_rdata = lcr_bsd_rls2;
      PI_IO_READ_REG	  : odw_reg_rdata = odr_ioc_data;
      PI_IO_WRITE_REG	  : odw_reg_rdata = odr_ioc_data;
      default		  : odw_reg_rdata = 'bx;
    endcase
  end /* always */

  /**************************************************************
    DMA BUS OUTPUT, AD16 BUS SIGNALS, IO BUFFER ADDRESS
   **************************************************************/
  dbus_driver dbus_driver_0(idr_buf_dout, icw_dbu_oenb, tbw_dbu_data);
  assign osr_adb_aleh = lcr_asm_st[1];
  assign osr_adb_alel = lcr_asm_st[0];
  assign oaw_buf_addr = oar_buf_addr[6:3];

  /**********************************************************************
    ON RISING CLOCK EDGE OR RESET
   **********************************************************************/
  always @(posedge clock or negedge reset_l) begin
  
    /************************************************************
      RESET CODE
     ************************************************************/
    if (!reset_l) begin
    
	// resetable state registers
	osr_pic_error	<= LOW;		// reset error bit
	osr_pic_intr	<= LOW;		// start idle
	lsr_pic_busy	<= LOW;		// start idle
	osr_io_busy	<= LOW;		// start idle
	ocr_dma_req	<= LOW;		// don't request DMA
	osr_adb_rd_l	<= HIGH;	// disable AD16 read
	osr_adb_wr_l	<= HIGH;	// disable AD16 write
	ocr_adb_oenb_l	<= HIGH;	// don't drive AD16 bus
	lcr_adb_cycs	<= 8'h0x;	// don't get stuck in IDLE too long
	lcr_dsm_st	<= DSM_IDLE;	// start DX SM from idle
	lcr_asm_st	<= ASM_STDBY;	// start AD16 SM from standby
	ocr_wenb_unbuf	<= LOW;		// inhibit write to buffer
	lcr_dsm_len	<= 'b1;		// reset for gate-level simulation

	// ROM device configuration registers
	lcr_bsd_lat1	<= ~(8'b0);	// 0xFF, See AD16 Spec
	lcr_bsd_pwd1	<= ~(8'b0);	// 0xFF, See AD16 Spec
	lcr_bsd_pgs1	<=   4'b0;	// 0x0,	 See AD16 Spec
	lcr_bsd_rls1	<= ~(2'b0);	// 0x3,	 See AD16 Spec
	lcr_bsd_lat2	<= ~(8'b0);	// 0xFF, See AD16 Spec
	lcr_bsd_pwd2	<= ~(8'b0);	// 0xFF, See AD16 Spec
	lcr_bsd_pgs2	<=   4'b0;	// 0x0,	 See AD16 Spec
	lcr_bsd_rls2	<= ~(2'b0);	// 0x3,	 See AD16 Spec
	
	// non-resetable registers
	lcr_dsm_reset	<= 'bx;		// DSM==IDLE will reset this
	lcr_dsm_expire	<= 'bx;		// irrelevant till CPU requests
	icr_dma_last	<= 'bx;		// irrelevant till CPU requests
	ocr_dma_read	<= 'bx;		// irrelevant till CPU requests
	ocr_dma_len	<= 'bx;		// irrelevant till CPU requests
	oar_dma_addr	<= 'bx;		// irrelevant till CPU requests
	lcr_adb_pgbrk	<= 'bx;		// irrelevant till CPU requests
	odr_buf_din	<= 'bx;		// write disabled
	idr_buf_dout	<= 'bx;		// irrelevant till CPU requests
	oar_buf_addr	<= 'bx;		// irrelevant till CPU requests
	odr_adb_dout	<= 'bx;		// irrelevant till CPU requests
	oar_adb_addr	<= 'bx;		// irrelevant till CPU requests
	lcr_adb_len	<= 'bx;		// irrelevant till CPU requests
	odr_ioc_data	<= 'bx;		// irrelevant till CPU requests

	end /* !reset_l */
    
    /************************************************************
      EXECUTION CODE
     ************************************************************/
    else begin
    
      /**************************************************************
	SIGNALS BASED ON REGISTER OUTPUT
       **************************************************************/
      // AD16 BUS OUTPUTS
      case (oar_buf_addr[2:1]) // AD16 BUS DATA OUT MUX (AT BUFFER OUTPUT)
	2'b00	: ldw_adb_dout = idw_buf_dout[63:48];
	2'b01	: ldw_adb_dout = idw_buf_dout[47:32];
	2'b10	: ldw_adb_dout = idw_buf_dout[31:16];
	2'b11	: ldw_adb_dout = idw_buf_dout[15: 0];
	default : ldw_adb_dout = 'bx; // never happens
      endcase

      /**********************************************************
	DEFAULT CONTROL VALUES AND STATUS SIGNALS
       **********************************************************/
      lsw_pic_busy	= lsr_pic_busy;
      lsw_io_busy	= osr_io_busy;
      lcw_buf_wenb	= LOW;
      lcw_buf_wdbu	= LOW;
      lcw_buf_wadb	= LOW;
      lcw_buf_wiod	= LOW;
      lcw_dsm_godx	= LOW;
      lcw_dsm_iorw	= LOW;
      lcw_asm_go	= LOW;
      lcw_adb_expire	= lcr_adb_len[DMA_LENGTH_SIZE-1:1] == 0;
      lcw_adb_cntdn	= lcr_adb_cycs == 0;	// artificial delay
      lcw_adb_done	= lcr_asm_st == ASM_RELRW & lcw_adb_cntdn &
					(lcw_adb_expire | lcr_dsm_reset);

      lcw_dma_len	= ocr_dma_len;
      law_dma_addr	= oar_dma_addr;
      lcw_dsm_len	= lcr_dsm_len;
      law_buf_addr	= oar_buf_addr;
      lcw_adb_len	= lcr_adb_len;
      law_adb_addr	= oar_adb_addr;

      /**********************************************************
	AD16 DEVICE DOMAIN DETERMINATION:

	The following table shows the AD16 bus memory map.  DMA
	controller filters out non-AD16 requests.  We only need
	to differenciate between domain 1 and domain 2.  In our
	design, we perform this differenciation continually.
	By doing so we are guaranteed to be using the appropriate
	configuration registers even when the data in a CPU request
	crosses the domain boundary.

	     Address
	starting   ending     designation
	---------  ---------  ----------------------------------
	1FC0_4000  FFFF_FFFF  Domain 1 (ROM)
	1FC0_0000  1FC0_3FFF  **PIF*** (not pos. elim by DMA ctlr)
	1000_0000  1FBF_FFFF  Domain 1 (ROM)
	0800_0000  0FFF_FFFF  Domain 2 (RAM)
	0600_0000  07FF_FFFF  Domain 1
	0500_0000  05FF_FFFF  Domain 2
	0400_0000  04FF_FFFF  **GrE*** (not pos. elim by DMA ctlr)
	0000_0000  03FF_FFFF  **DRAM** (not pos. elim by DMA ctlr)
       **********************************************************/
      lcw_bsd_dom = (oar_adb_addr[31:28] == 4'b0 &&
		     (oar_adb_addr[27] == 1'b1
		      || oar_adb_addr[26:24] == 3'b101));

      /**********************************************************
	COMMAND REGISTER WRITE BY CPU (REG)

	* Writes to READ_LENGTH, WRITE_LENGTH, IO_READ, and
	  IO_WRITE will start the respective operations.
	* Writes to STATUS will cause the error bit to be reset.
	  If the pic is busy at the time of writing to STATUS, the
	  on-going operation will be aborted (elegantly) and the
	  the state-machines returned to idle.
	* While the pic is busy, writes any register other than
	  STATUS are ignored and will cause the error bit to be set.
	* The error bit does not affect the operation during which
	  it is set and will not affect any future operations.  It
	  is purely for debugging/diagnostic purposes.  It indicates
	  that a request was made to pic while it was busy and was
	  thus dropped.
       **********************************************************/
      if (icw_reg_wenb) begin
      
	if (icw_reg_addr == PI_STATUS_REG) begin
	  osr_pic_intr  <= !idw_reg_wdata[1] & osr_pic_intr;	// clr intr
	  osr_pic_error <= !idw_reg_wdata[0] & osr_pic_error;	// clr error
	  lcr_dsm_reset <=  idw_reg_wdata[0] & (lsr_pic_busy | osr_io_busy);
						// turn on soft reset flag
	  end

        else if (!lsr_pic_busy			// not performing DMA
		 && !osr_io_busy) begin		// not performing IO op

	  case (icw_reg_addr)

	    PI_DRAM_ADDRESS_REG: begin		// write DRAM addr reg
	      law_dma_addr = { idw_reg_wdata[31:1], 1'b0 };
	      end
	      
	    PI_PBUS_ADDRESS_REG: begin		// write BSD addr reg
	      law_adb_addr = { idw_reg_wdata[31:1], 1'b0 };
	      end
	      
	    PI_READ_LENGTH_REG: begin		// DRAM -> BSD
	      lsw_pic_busy = HIGH;		// raise busy signal
	      ocr_dma_read <= HIGH;		// mark as read from DRAM
	      lcr_dsm_expire <= LOW;		// reset expire flag
	      lcw_dsm_godx = HIGH;		// kick off DSM
	      lcw_dsm_len  = idw_reg_wdata;	// write dsm_len reg
	      lcw_dma_len  = {4'hF,~oar_dma_addr[2:0]};	// max DMA len
	      end
	      
	    PI_WRITE_LENGTH_REG: begin		// BSD -> DRAM
	      lsw_pic_busy = HIGH;		// raise busy signal
	      ocr_dma_read <= LOW;		// mark as write to DRAM
	      lcr_dsm_expire <= LOW;		// reset expire flag
	      lcw_dsm_godx = HIGH;		// kick off DSM
	      lcw_dsm_len  = idw_reg_wdata;	// write dsm_len reg
	      lcw_dma_len  = {4'hF,~oar_dma_addr[2:0]};	// max DMA len
	      end

	    PI_IO_READ_REG: begin		// BSD -> CPU
	      lsw_io_busy  = HIGH;		// raise ioc busy signal
	      ocr_dma_read <= LOW;		// mark as read from BSD
	      lcr_dsm_expire <= HIGH;		// set expire flag
	      lcw_dsm_iorw = HIGH;		// kick off DSM
	      law_buf_addr = 0;			// reset buffer address
	      law_dma_addr[2:0] = 0;		// force buffer alignment
	      law_adb_addr = iaw_ioc_addr;	// load read address
	      lcw_adb_len  = 'h3;		// simulate a 4-byte data xfer
	      end

	    PI_IO_WRITE_REG: begin		// CPU -> BSD
	      lsw_io_busy  = HIGH;		// raise ioc busy signal
	      ocr_dma_read <= HIGH;		// mark as write to BSD
	      lcr_dsm_expire <= HIGH;		// set expire flag
	      lcw_dsm_iorw = HIGH;		// kick off DSM
	      lcw_buf_wiod = HIGH;		// load data into buf din reg
	      lcw_buf_wenb = HIGH;		// write data into buffer
	      law_buf_addr = 0;			// reset buffer address
	      law_dma_addr[2:0] = 0;		// force buffer alignment
	      law_adb_addr = iaw_ioc_addr;	// load write address
	      lcw_adb_len  = 'h3;		// simulate a 4-byte data xfer
	      end

            PI_BSD_DOM1_LAT_REG: begin
              lcr_bsd_lat1 <= idw_reg_wdata[`PIC_ADB_LAREG_SZ-1:0];
              end
            PI_BSD_DOM2_LAT_REG: begin
              lcr_bsd_lat2 <= idw_reg_wdata[`PIC_ADB_LAREG_SZ-1:0];
              end
            PI_BSD_DOM1_PWD_REG: begin
              lcr_bsd_pwd1 <= idw_reg_wdata[`PIC_ADB_PWREG_SZ-1:0];
              end
            PI_BSD_DOM2_PWD_REG: begin
              lcr_bsd_pwd2 <= idw_reg_wdata[`PIC_ADB_PWREG_SZ-1:0];
              end
            PI_BSD_DOM1_PGS_REG: begin
              lcr_bsd_pgs1 <= idw_reg_wdata[`PIC_ADB_PGREG_SZ-1:0];
              end
            PI_BSD_DOM2_PGS_REG: begin
              lcr_bsd_pgs2 <= idw_reg_wdata[`PIC_ADB_PGREG_SZ-1:0];
              end
            PI_BSD_DOM1_RLS_REG: begin
              lcr_bsd_rls1 <= idw_reg_wdata[`PIC_ADB_RLREG_SZ-1:0];
              end
            PI_BSD_DOM2_RLS_REG: begin
              lcr_bsd_rls2 <= idw_reg_wdata[`PIC_ADB_RLREG_SZ-1:0];
	      end

	    default: begin
	      $display("Panic!	Illegal PI register write - <%h>.",
		       icw_reg_addr);
	      $finish;
	      end
	    endcase /* reg_addr */
	    end /* !busy */

        else
	    osr_pic_error <= HIGH;		// set error bit!

      end /* reg_wenb */
      
      /******************************************************************
	ADDER (ADD):

	Performs op1+op2 (op1-op2) and generates the sum (difference)
	and all carry outs.  This adder is used to compute DMA length,
	ROM data transfer length, remaining data transfer length, and
	to update DMA address and ROM address.

	This adder has evolved from a generic 32-bit adder to a highly
	specialized block.  It now consists of an incrementor/decrementor
	for the most significant 15 bits, two 8-bit adders for the next
	16 bits, and a forced least significant bit.  All of this is
	done for timing reasons.  These changes had been anticipated
	as possible optimizations in previous check'ins.  Now they are
	actually implemented here in verilog.
       ******************************************************************/
      
      ldw_add_op1 = 'bx;		// default to dontcares
      ldw_add_op2 = 'bx;		// default to dontcares
      lcw_add_sub = 'bx;		// default to dontcares
      lcw_add_ci  = 'bx;		// default to dontcares

      case (lcr_dsm_st[3:2])
      
	2'b00: begin	// DSM_DLEN: dma_len = min(dsm_len,dma_len);
			// DSM_PLEN: dma_len = min(rem_page_len,dma_len);
	  ldw_add_op1 = lcr_dsm_st[1] ? { 21'b0,~oar_dma_addr[10:0] } : lcr_dsm_len;
	  ldw_add_op2 = ocr_dma_len;
	  lcw_add_sub = HIGH;
	  lcw_add_ci  = HIGH;
	  end /* PLEN, DLEN */
	  
	2'b01: begin	// DSM_RREQ,
			// DSM_WREQ: dsm_len = dsm_len - dma_len;
	  ldw_add_op1 = lcr_dsm_len;
	  ldw_add_op2 = ocr_dma_len;
	  lcw_add_sub = HIGH;		// special subtraction
	  lcw_add_ci  = LOW;
	  end /* RREQ, WREQ */
	  
	2'b10: begin	// DSM_RDMA,
			// DSM_WDMA: dma_addr = (dma_addr + 8) & ~7;
	  ldw_add_op1 = oar_dma_addr;
	  ldw_add_op2 = 'h8;
	  lcw_add_sub = LOW;
	  lcw_add_ci  = LOW;
	  end /* RDMA, WDMA */

	2'b11: begin	// DSM_RADB,
			// DSM_WADB,
			// DSM_IORW:
			// ASM_RD_WR: adb_addr = (adb_addr + 2) & ~1;
	  ldw_add_op1 = oar_adb_addr;
	  ldw_add_op2 = 'h2;
	  lcw_add_sub = LOW;
	  lcw_add_ci  = LOW;
	  end /* RADB, WADB, IORW */

      endcase	/* ADDER INPUT MUXING */ 

      // INCREMENTOR/DECREMENTOR

      { lsw_inc_co,ldw_inc_s[31:17] } =  { 1'b0,ldw_add_op1[31:17] } + 1'b1;
      { lsw_dec_co,ldw_dec_s[31:17] } =  { 1'b0,ldw_add_op1[31:17] } - 1'b1;

      // ADDER

      ldw_add_op2i[16:1] =
	  lcw_add_sub ? {10'h3FF,~ldw_add_op2[6:1]} : {10'h0,ldw_add_op2[6:1]};

      { lsw_add_co[ 7:0], ldw_add_s[ 8:1] } =
	  bcadd8(ldw_add_op1[ 8:1],ldw_add_op2i[ 8:1],lcw_add_ci);
      { lsw_add_co0[15:8], ldw_add_s0[16:9] } =
	  bcadd8(ldw_add_op1[16:9],ldw_add_op2i[16:9],1'b0);
      { lsw_add_co1[15:8], ldw_add_s1[16:9] } =
	  bcadd8(ldw_add_op1[16:9],ldw_add_op2i[16:9],1'b1);
      { lsw_add_co[15:8], ldw_add_s[16:9] } =
	  lsw_add_co[7] ? { lsw_add_co1[15:8], ldw_add_s1[16:9] }
			: { lsw_add_co0[15:8], ldw_add_s0[16:9] };

      // COMBINE RESULTS
      ldw_add_sum[31:17] = lsw_add_co[15] ? ldw_inc_s[31:17] : ldw_add_op1[31:17];
      ldw_add_sum[16: 1] = ldw_add_s[16:1];
      ldw_add_sum[    0] = lcw_add_sub;
      ldw_add_dif[31:17] = lsw_add_co[15] ? ldw_add_op1[31:17] : ldw_dec_s[31:17];
      ldw_add_dif[16: 1] = ldw_add_s[16:1];
      ldw_add_dif[    0] = lcw_add_sub;

      // LESS-THAN FLAG
      lsw_add_lt = !lsw_add_co[15] & lsw_dec_co;


      /******************************************************************
	PAGE BOUNDARY DETECTION -
	page size = 2*2^(PGS+1) bytes.  Therefore, we detect for CO[PGS+1]
	which is the carry out of bit PGS+1 of adder.
       ******************************************************************/
      lcw_bsd_pgsz = lcw_bsd_dom ? lcr_bsd_pgs2 : lcr_bsd_pgs1;
      lcw_adb_pgbrk = lsw_add_co[lcw_bsd_pgsz];	// AD16 bus dev page boundary

      /******************************************************************
	DATA TRANSFER STATE-MACHINE (DSM)

	ALGORITHM:
	  save BSD starting domain for domain boundary check;
	  set DMA length = buffer size - starting misalignment;
	  while not done:
	    adjust DMA length with regards to size of remaining data;
	    adjust DMA length with regards to DMA 2K page boundary;
	    if transfering from DRAM to BSD:
		move data from DRAM into buffer via DMA;
		move data from buffer to BSD;
	    endif
	    else from BSD to DRAM:
		move data from BSD into buffer;
		move data from buffer into DRAM via DMA;
	    endelse
	  endwhile

	DMA READ HANDSHAKE PROTOCOL:
                  _   _   _   _   _   _   _   _   _   _   _   _
	  Clock _/ :_/ :_/ :_/ :_/ :_/ :_/ :_/ :_/ :_/ :_/ :_/ :_
                  ___________
	  Req   _/           \___________________________________
                          ___
          Grant _________/   \___________________________________
                                  ___
          Start _________________/   \___________________________
                                              ___
          Last  _____________________________/   \_______________

	  DBUS  ------------------<D0><D1><D2><D3>---------------
	    
	DMA WRITE HANDSHAKE PROTOCOL:
                  _   _   _   _   _   _   _   _   _   _   _   _
	  Clock _/ :_/ :_/ :_/ :_/ :_/ :_/ :_/ :_/ :_/ :_/ :_/ :_
                  ___________
	  Req   _/           \___________________________________
                          ___
          Grant _________/   \___________________________________
                                  ___
          Start _________________/   \___________________________
                                              ___
          Last  _____________________________/   \_______________

	  DBUS  ----------------------<D0><D1><D2><D3>-----------
	    
       ******************************************************************/
      case (lcr_dsm_st)

	DSM_IDLE: begin // wait for go to start servicing a request
	  lcr_dsm_reset <= LOW;
	  if (!lcw_dsm_godx & !lcw_dsm_iorw) lsw_pic_busy = LOW;
	  // === next-state logic === (no prioritizing necessary)
					lcw_dsm_st_nx = DSM_IDLE;
	  if (lcw_dsm_godx)		lcw_dsm_st_nx = DSM_DLEN;
	  if (lcw_dsm_iorw)		lcw_dsm_st_nx = DSM_IORW;
	  end /* IDLE */

	/********************************************************
	  PREPARATION STATES
	 ********************************************************/

	DSM_DLEN: begin // compute max DMA len considering remaining len
	  lcw_dma_len = lsw_add_lt ? lcr_dsm_len : ocr_dma_len;
	  // === next-state logic ===
	  if (lcr_dsm_reset)		lcw_dsm_st_nx = DSM_IDLE;
	  else				lcw_dsm_st_nx = DSM_PLEN;
	  end /* DLEN */

	DSM_PLEN: begin
	  ocr_dma_req <= ocr_dma_read;
	  lcw_dma_len  =
	      lsw_add_lt ? ~oar_dma_addr[DMA_LENGTH_SIZE-1:0] : ocr_dma_len;
	  lcw_adb_len  = lcw_dma_len;	// copy dma_len into adb_len at input
	  law_buf_addr = oar_dma_addr[2:0];	// line 0 with starting offset
	  // === next-state logic ===
	  if (lcr_dsm_reset)		lcw_dsm_st_nx = DSM_IDLE;
	  else if (ocr_dma_read)	lcw_dsm_st_nx = DSM_RREQ;
	  else				lcw_dsm_st_nx = DSM_WADB;
	  end /* PLEN */

	/****************************************************************
	  READ (DRAM -> AD16) STATES.
	 ****************************************************************/

	DSM_RREQ: begin
	  if (icw_dma_grant)			// grant received
	    ocr_dma_req <= LOW;			// - lower req, watch for start
	  if (icw_dma_start &
	      (!ocr_dma_req | (ocr_dma_req & icw_dma_grant))) begin
	    lcr_dsm_expire <= ldw_add_dif[24];	// - set expire flag
	    lcw_dsm_len  = ldw_add_dif;		// - update data xfer length
	    lcw_buf_wdbu = HIGH;		// - latch DBUS data
	    lcw_buf_wenb = HIGH;		// - write to buffer next cycle
	    end
	  // === next-state logic === (priority intended)
	  if (lcr_dsm_reset)		lcw_dsm_st_nx = DSM_IDLE;
	  else if (icw_dma_start &
		   (!ocr_dma_req | (ocr_dma_req & icw_dma_grant)))
					lcw_dsm_st_nx = DSM_RDMA;
	  else				lcw_dsm_st_nx = DSM_RREQ;
	  end /* RREQ */

	DSM_RDMA: begin
	  lcw_buf_wdbu = !icr_dma_last;		// latch DBUS data
	  lcw_buf_wenb = !icr_dma_last;		// write to buffer next cycle
	  law_dma_addr =			// update DMA addr using ALU
	      { ldw_add_sum[DRAM_ADDRESS_SIZE-1:3], 3'b0 };
	  law_buf_addr = oar_buf_addr + 8;	// continue with RDMA
	  // === next-state logic ===
	  if (lcr_dsm_reset)		lcw_dsm_st_nx = DSM_IDLE;
	  else if (icr_dma_last)	lcw_dsm_st_nx = DSM_RADB;
	  else				lcw_dsm_st_nx = DSM_RDMA;
	  end /* RDMA */

	DSM_RADB: begin				// ASM takes over
	  lcw_asm_go = HIGH;			// AD16 SM kick-off (DRAM->BSD)
	  if (lcw_adb_done) begin
	    lcw_dma_len = { 4'hF, ~oar_dma_addr[2:0] }; // reset dma_len
	    if (lcr_dsm_expire) begin
		lsw_pic_busy = LOW;		// completely done
		osr_pic_intr <= HIGH;		// tell CPU we're done
		end
	    end
	  // === next-state logic === (priority intended)
	  if (lcw_adb_done) begin
	    if (lcr_dsm_reset)		lcw_dsm_st_nx = DSM_IDLE;
	    else if (lcr_dsm_expire)	lcw_dsm_st_nx = DSM_IDLE;
	    else			lcw_dsm_st_nx = DSM_DLEN; end
	  else				lcw_dsm_st_nx = DSM_RADB;
	  end /* RADB */

	/****************************************************************
	  WRITE (AD16 -> DRAM) STATES.
	 ****************************************************************/

	DSM_WADB: begin				// ASM takes over
	  lcw_asm_go = HIGH;			// AD16 SM Kick-off (BSD->DRAM)
	  if (lcw_adb_done & !lcr_dsm_reset)
	      ocr_dma_req <= HIGH;		// raise req to DMA controller
	  // === next-state logic ===
	  if (lcr_dsm_reset)		lcw_dsm_st_nx = DSM_IDLE;
	  else if (lcw_adb_done)	lcw_dsm_st_nx = DSM_WREQ;
	  else				lcw_dsm_st_nx = DSM_WADB;
	  end /* WADB */

	DSM_WREQ: begin
	  law_buf_addr = oar_dma_addr[2:0];	// line 0 with starting offset
	  if (icw_dma_grant)			// grant received
	    ocr_dma_req <= LOW;			// - lower req, watch for start
	  if (icw_dma_start &
	      (!ocr_dma_req | (ocr_dma_req & icw_dma_grant))) begin
	    lcr_dsm_expire <= ldw_add_dif[24];	// - set expire flag
	    lcw_dsm_len	 = ldw_add_dif;		// - update data xfer length
	    law_buf_addr = oar_buf_addr + 8;	// - update buffer addr
	    end
	  // === next-state logic ===
	  if (lcr_dsm_reset)		lcw_dsm_st_nx = DSM_IDLE;
	  else if (icw_dma_start &
		   (!ocr_dma_req | (ocr_dma_req & icw_dma_grant)))
					lcw_dsm_st_nx = DSM_WDMA;
	  else				lcw_dsm_st_nx = DSM_WREQ;
	  end /* WREQ */

	DSM_WDMA: begin
	  law_buf_addr = oar_buf_addr + 8;	// update DMA buffer addr
	  law_dma_addr =			// update DMA addr using ALU
	      { ldw_add_sum[DRAM_ADDRESS_SIZE-1:3], 3'b0 };
	  if (icr_dma_last)
	      lcw_dma_len = { 4'hF, ~oar_dma_addr[2:0] };
	  if (icr_dma_last & lcr_dsm_expire) begin
	      lsw_pic_busy = LOW;
	      osr_pic_intr <= HIGH;		// tell CPU we're done
	      end
	  // === next-state logic ===
	  if (lcr_dsm_reset)		lcw_dsm_st_nx = DSM_IDLE;
	  else if (icr_dma_last) begin
	    if (lcr_dsm_expire)		lcw_dsm_st_nx = DSM_IDLE;
	    else			lcw_dsm_st_nx = DSM_DLEN; end
	  else				lcw_dsm_st_nx = DSM_WDMA;
	  end /* WDMA */

	DSM_IORW: begin
	  lcw_asm_go = HIGH;			// kick off ASM
	  if (lcw_adb_done) begin
	    odr_ioc_data <= odr_buf_din[63:32];	// save in special register
	    lsw_io_busy = LOW;
	    end
	  // === next-state logic ===
	  if (lcw_adb_done)		lcw_dsm_st_nx = DSM_IDLE;
	  else				lcw_dsm_st_nx = DSM_IORW;
	  end /* IORW */

	default:  lcw_dsm_st_nx = DSM_IDLE;

      endcase	/* MEMORY OPERATION STATE-MACHINE */

      /******************************************************************
	AD16 BUS STATE-MACHINE (ASM)

	*****************************************************************
	INTERFACE LOGIC:

			  PIC		     PI		  AD16
	    adb_aleh		      :		    :
	    -|>____|--|>o-o|>---------------------------> ALEH
	    adb_alel                  :		    :
	    -|>____|--|>o-o|>---------------------------> ALEL
	    adb_rd_l		      :		    :
	    -|>_|-log-|>o-o|>---------------------------> RD_
	    adb_wr_l		      :		    :
	    -|>_|-log-|>o-o|>---------------------------> WR_
		       _	      :		    :
		      | | adb_oenb    :		    :
	    --------->| |--------------------+	    :
		      |>|	      :	     |	    :
		       _	      :	     |	    :
		      | | adb_dout    :	     V	    :
	    --------->| |-------------------|>---+  :
		      |>|	      :		 |  :
		       		      :		 ===:==== AD[15:0]
	                  adb_din     :		 |  :
	     +--+--+--+--------------------<|----+  :
            _V__V__V__V_
            \_/\_/\_/\_/ 4x(4:1) muxes
            _|__|__|__|_
           |>___________| buf_din
                 |

	What is shown in the above diagram is that there is a tiny bit of
	logic after the register before the signals RD_ (adb_rd_l) and WR_
	(adb_wr_l) go out to the bus.  Plus, inputs from the bus goes
	through one level of 4:1 mux before being latched into the register.
       ******************************************************************/

      case (lcr_asm_st)

	ASM_STDBY: begin // standing by. waiting for go signal to kick off SM
	  ocr_adb_oenb_l <= HIGH;		// disable bus driver
	  odr_adb_dout <= 'bx;			// output dontcare to bus
	  if (lcw_asm_go) law_buf_addr = oar_buf_addr[2:0];
	  // === next-state logic ===		// guaranteed 3 cycs by DSM
	  lcw_asm_st_nx = lcw_asm_go ? ASM_HIADR : ASM_STDBY;
	  end /* STDBY */

	ASM_HIADR: begin // place high order address onto AD bus
	  ocr_adb_oenb_l <= LOW;		// enable bus driver
	  odr_adb_dout <= oar_adb_addr[31:16];	// output high addr to bus
	  // === next-state logic ===
	  lcw_asm_st_nx	 = lcw_adb_cntdn ? ASM_LOADR : ASM_HIADR;
	  end /* HIADR */

	ASM_LOADR: begin // place low order address onto AD bus
	  odr_adb_dout <= oar_adb_addr[15:0];	// output low addr to bus
	  // === next-state logic ===
	  lcw_asm_st_nx	 = lcw_adb_cntdn ? ASM_LWAIT : ASM_LOADR;
	  end /* LOADR */

	ASM_LWAIT: begin // create artificial delay per BSD requirement
	  ocr_adb_oenb_l <= !(lcw_adb_cntdn & ocr_dma_read);	// drv iff DRAM->BSD
	  odr_adb_dout <= ldw_adb_dout;		// output data to bus
	  // === next-state logic ===
	  lcw_asm_st_nx	 = lcw_adb_cntdn ? ASM_RD_WR : ASM_LWAIT;
	  end /* LWAIT */

	ASM_RD_WR: begin // place data onto bus or read data off of bus
	  if (lcw_adb_cntdn) begin
	    lcw_buf_wadb = !ocr_dma_read;	// write data into buf din reg
	    law_adb_addr =			// advance BSD addr
		{ ldw_add_sum[PBUS_ADDRESS_SIZE-1:1], 1'b0 };
	    lcr_adb_pgbrk <= lcw_adb_pgbrk;	// save page break info
	    lcw_buf_wenb =			// write to buffer next cycle
		!ocr_dma_read && (lcw_adb_expire || (oar_buf_addr[2:1] == 2'b11));
            if (ocr_dma_read)			// advance buffer address
		law_buf_addr = oar_buf_addr+2;	//   only if ->BSD
            end
	  // === next-state logic ===
	  if (lcw_adb_cntdn)		lcw_asm_st_nx = ASM_RELRW;
	  else				lcw_asm_st_nx = ASM_RD_WR;
	  end /* RD_WR */

	ASM_RELRW: begin // release from read/write
	  odr_adb_dout <= ldw_adb_dout;		// output data to bus
	  if (lcw_adb_cntdn) begin		// do in last cycle
	    lcw_adb_len	 = lcr_adb_len-2;	// adb_len -= 2
            if (!ocr_dma_read)			// advance buffer address
		law_buf_addr = oar_buf_addr+2;	//   only if <-BSD
	    end
	  // === next-state logic === (priority intended)
	  if (lcw_adb_cntdn) begin
	    if (lcr_dsm_reset)		lcw_asm_st_nx = ASM_STDBY;
	    else if (lcw_adb_expire) begin
	        if (lcr_dsm_expire | ocr_dma_read)
					lcw_asm_st_nx = ASM_STDBY;
		else			lcw_asm_st_nx = ASM_PAUSE; end
	    else if (lcr_adb_pgbrk) begin
		if (ocr_dma_read)	lcw_asm_st_nx = ASM_PGBRK;
		else			lcw_asm_st_nx = ASM_HIADR; end
	    else			lcw_asm_st_nx = ASM_RD_WR; end
	  else				lcw_asm_st_nx = ASM_RELRW;
	  end /* RELRW */

	ASM_PAUSE: begin // pause while DMA data (ROM -> RDRAM only)
	  // === next-state logic ===
	  if (lcr_dsm_reset | lcr_dsm_expire)
					lcw_asm_st_nx = ASM_STDBY;
	  else if (lcw_asm_go) begin
	      law_buf_addr = oar_buf_addr[2:0];	// update buffer pointer
	      if (lcr_adb_pgbrk)	lcw_asm_st_nx = ASM_PGBRK;
	      else			lcw_asm_st_nx = ASM_RD_WR;
	      end
	  else				lcw_asm_st_nx = ASM_PAUSE;
	  end /* ASM_PAUSE */

	ASM_PGBRK: begin // pause for page break before re-starting
	  ocr_adb_oenb_l <= HIGH;		// disable bus driver
	  odr_adb_dout <= 'bx;			// output dontcare to bus
	  // === next-state logic ===
	  lcw_asm_st_nx = lcw_adb_cntdn ? ASM_HIADR : ASM_PGBRK;
	  end /* PGBRK */

	default:   begin // just in case
	  ocr_adb_oenb_l <= HIGH;		// disable bus driver
	  odr_adb_dout <= 'bx;			// output dontcare to bus
	  // === next-state logic ===
	  lcw_asm_st_nx = ASM_STDBY;
	  end /* default */

      endcase	/* AD16 BUS STATE-MACHINE */

      /******************************************************************
	NEXT-CYCLE MISC. REGISTER CONTENT UPDATE
       ******************************************************************/

      /**********************************************************************
	CYCLE COUNTER

	Based on the AD16 Bus ROM/RAM timing spec and the assumption that
	1 clock cycle is equivalent to 16ns, we implement the following
	delays.  If each clock cycle turns out to be less 15 ns, then the
	programmed delay must be updated to meet the delay requirements.

         +--------------------------------------------------------------+
         | STATES      SYMBOL  REQUIREMENT                 IMPLEMENTED  |
         + ----------  ------  --------------------------  ------------ +
         | STANDBY:    --      none                            1 cycle  |
         | HIADDR:     tALES   tALES > 90ns                    7 cycles |
         | LOADDR:     tALED   tALED > 90ns                    7 cycles | 
         | WAIT:       tL1/2   tL1/2 = Lat1/2 + 1          Lat+1 cycles |
         | RDWR:       tP1/2   tP1/2 = Pwd1/2 + 1          Pwd+1 cycles |
         | RELEASE:    tR1/2   tR1/2 = Rls1/2 + 1          Rls+1 cycles |
         | PGBREAK:    tWRC    tWRC > 20ns                     2 cycles |
         +--------------------------------------------------------------+
       **********************************************************************/
      lcw_adb_cycs = lcr_adb_cycs - 1'b1;			// decrement
      if (lcr_asm_st != lcw_asm_st_nx) begin
	case (lcw_asm_st_nx)
	  ASM_STDBY,						// no effect
	  ASM_HIADR,
	  ASM_LOADR: lcr_adb_cycs <= 8'h6;			// tALES,tALED
	  ASM_LWAIT: lcr_adb_cycs <= lcw_bsd_dom ? lcr_bsd_lat2 : lcr_bsd_lat1;
	  ASM_RD_WR: lcr_adb_cycs <= lcw_bsd_dom ? lcr_bsd_pwd2 : lcr_bsd_pwd1;
	  ASM_RELRW: lcr_adb_cycs <= lcw_bsd_dom ? lcr_bsd_rls2 : lcr_bsd_rls1;
	  ASM_PAUSE,
	  ASM_PGBRK: lcr_adb_cycs <= 8'h1;			// tWRC
	  default  : lcr_adb_cycs <= 8'h0;			// --
	endcase
	end
      else if (!lcw_adb_cntdn)
		     lcr_adb_cycs <= lcw_adb_cycs;		// decrement

      /**********************************************************
	REGISTER UPDATES
       **********************************************************/
      // INPUT DATA FROM BUSES
      idr_buf_dout <= idw_buf_dout;

      // STATE-MACHINE STATE UPDATES
      lcr_dsm_st <= lcw_dsm_st_nx;
      lcr_asm_st <= lcw_asm_st_nx;

      // OTHERS
      osr_adb_rd_l <= !((lcw_asm_st_nx == ASM_RD_WR) & !ocr_dma_read);
      osr_adb_wr_l <= !((lcw_asm_st_nx == ASM_RD_WR) &  ocr_dma_read);
      icr_dma_last <= icw_dma_last;
      lsr_pic_busy <= lsw_pic_busy;
      osr_io_busy  <= lsw_io_busy;
      ocr_dma_len  <= lcw_dma_len;
      oar_dma_addr <= law_dma_addr;
      lcr_dsm_len  <= lcw_dsm_len;
      lcr_adb_len  <= lcw_adb_len;
      oar_adb_addr <= law_adb_addr;

      /**********************************************************
	BUFFER INTERFACE LOGIC AND SIGNALS
       **********************************************************/
      ldw_buf_din = odr_buf_din;			// default
      if (lcw_buf_wdbu) ldw_buf_din = tbw_dbu_data;	// from DBUS reg
      if (lcw_buf_wadb)					// from AD16
	case (oar_buf_addr[2:1])
	  2'b00	  : ldw_buf_din[63:48] = idw_adb_din;
	  2'b01	  : ldw_buf_din[47:32] = idw_adb_din;
	  2'b10	  : ldw_buf_din[31:16] = idw_adb_din;
	  2'b11	  : ldw_buf_din[15: 0] = idw_adb_din;
	  default : ldw_buf_din	       = 'bx; // should never happen
	endcase
      if (lcw_buf_wiod) ldw_buf_din[63:32] = idw_reg_wdata;

      ocr_wenb_unbuf <= lcw_buf_wenb;
      oar_buf_addr <= law_buf_addr;
      odr_buf_din  <= ldw_buf_din;

      end /* reset_l */
    end /* always */

endmodule /* pi_controller */

/************************************************************************
  TODOs:
    1. Hardware to detect and report illegal state combinations.

  NOTATION:

    ADB/adb	= AD16 bus.
    ASM/asm	= AD16 bus protocol state-machine.
    BSD/bsd	= Block storage device on AD16 bus.
    BUF/buf	= 128-byte register file type buffer on PI.
    dbu		= DBUS.	 See below.
    DMA/dma	= Direct memory access.
    DSM/dsm	= Data transfer state-machine.
    ioc		= Special IO read/write commands.
    PI		= Peripheral Interface Module.
    PIC/pic	= Peripheral Interface Controller (us).
    reg		= Command register.

    The following are defined externally:

    CBUS = RAMBUS command bus.
    DBUS = RAMBUS data bus.
    DMA	 = Direct Memory Access.
    DRAM = CPU DRAM.
    REG	 = Command registers.
    PBUS = Peripheral bus (same as ADB).

    Prefix Notation:
	First Char	Second Char	Third Char
	--------------	--------------	-------------
	i = input	c = control	r = register
	o = output	s = signal	w = wire
	l = local	d = data	m = memory
	t = tri-state	a = address
			b = bus

 ************************************************************************/
