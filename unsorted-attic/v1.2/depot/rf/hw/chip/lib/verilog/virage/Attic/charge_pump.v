//---------------------------------------------------------------------
//               Copyright(c) Virage Logic Corporation.                
//     All Rights reserved - Unpublished -rights reserved under        
//     the Copyright laws of the United States of America.             
//                                                                     
//  This file includes the Confidential information of Virage Logic    
//  and NEC                                                            
//  The receiver of this Confidential Information shall not disclose   
//  it to any third party and shall protect its confidentiality by     
//  using the same degree of care, but not less then a reasonable      
//  degree of care, as the receiver uses to protect receiver's own     
//  Confidential Information.                                          
//                                                                     
//                    Virage Logic Corporation.                        
//                    46501 Landing Parkway                            
//                    Fremont , California 94538.                      
//                                                                     
//---------------------------------------------------------------------
//                                                                     
//  Software           : Rev: 3.2.0 (build REL-3-2-0-2002-09-27)       
//  Library Format     : Rev: 1.05.00                                  
//  Compiler Name      : nc15s1p11cpra                                 
//  Date of Generation : Thu Oct 24 12:40:30 PDT 2002                  
//                                                                     
//---------------------------------------------------------------------

//   --------------------------------------------------------------     
//                       Template Revision : 1.0.0                      
//   --------------------------------------------------------------     


//                            * Charge Pump *                         
//                      * Verilog Behavioral Model *                  
//                       THIS IS A CHARGE PUMP MODEL                  
//                                                                    
//   Charge Pump instance Name:charge_pump                            
//                                                                    
//                               PORT NAME                            
//                               ---------                            
//               Output Ports                                         
//                                   VPP                              
//                                   UNLOCK                           
//                                   PU1                              
//                                   PU2                              
//                                   PORST                            
//               Input Ports:                                         
//                                   VPPRANGE                         
//                                   VPPSEL[3:0]                      
//                                   PE                               
//                                   RST                              
//                                   CLK                              
//                                   D                                
//                                   CLKE                             
//                                   STORE                            




`resetall 

`timescale 1 ns / 10 ps 
`celldefine 

`define True    1'b1
`define False   1'b0

module charge_pump ( VPPRANGE, VPPSEL, PE, RST, CLK, D, CLKE, STORE, VPP, UNLOCK, PU1, PU2, PORST);

input VPPRANGE;
input  [3:0] VPPSEL;
input PE;
input RST;
input CLK;
input D;
input CLKE;
input STORE;
output VPP;
output UNLOCK;
output PU1;
output PU2;
output PORST;


parameter MES_ALL = "ON";

// Local registers, wires, etc
reg notif_vpprange;
reg notif_vppsel;
reg notif_pe;
reg notif_pe_STORE_fall_rec;
reg notif_rst;
reg notif_rst_CLK_rise_rec;
reg notif_clk;
reg notif_d;
reg notif_clke;
reg notif_store;
reg notif_store_PE_rise_rec;

reg VPPRANGElatched;
reg [3:0] VPPSELlatched;
reg Dlatched;
reg CLKElatched;

buf (VPPRANGE_buf, VPPRANGE);
wire [3:0] VPPSEL_buf;
buf (VPPSEL_buf[0], VPPSEL[0]);
buf (VPPSEL_buf[1], VPPSEL[1]);
buf (VPPSEL_buf[2], VPPSEL[2]);
buf (VPPSEL_buf[3], VPPSEL[3]);
buf (PE_buf, PE);
buf (RST_buf, RST);
buf (CLK_buf, CLK);
buf (D_buf, D);
buf (CLKE_buf, CLKE);
buf (STORE_buf, STORE);
buf (VPP, VPP_buf);
buf (UNLOCK, UNLOCK_buf);
buf (PORST, PORST_buf);

wire CHKEN1;
wire CHKEN2;

assign CHKEN1 = (UNLOCK & CLKE_buf);
assign CHKEN2 = CLKE_buf;

specify
 
    specparam

        Tvpc = 1.60,
        Tcvpx = 1.60,
        Tvc = 1.60,
        Tcvx = 1.60,
        Trps = 1000000.00,
        Tph = 10000000.00,
        Trrc = 200.00,
        Trh = 5000.00,
        Tcl = 2.60,
        Tch = 2.60,
        Tcc = 6.40,
        Tdc = 1.60,
        Tcdx = 1.60,
        Tec = 1.60,
        Tcex = 1.60,
        Trsp = 100000.00,
        Tpvh = 500000.00,
        Tpvl = 500000.00,
        Tcu = 6.00;
       ( posedge PE => (  VPP  : 1'bx )) = (  Tpvh, Tpvl );
       ( posedge CLK => (  UNLOCK  : 1'bx )) = (  Tcu, Tcu );

// Timing Checks

    $width (posedge PE, Tph, 0, notif_pe);
    $width (posedge RST, Trh, 0, notif_rst);
    $width (negedge CLK, Tcl, 0, notif_clk);
    $width (posedge CLK, Tch, 0, notif_clk);
    $period (posedge CLK, Tcc, notif_clk);
    $period (negedge CLK, Tcc, notif_clk);
    $setuphold (posedge CLK  &&& CHKEN1, posedge VPPRANGE,Tvpc, Tcvpx, notif_vpprange );
    $setuphold (posedge CLK  &&& CHKEN1, negedge VPPRANGE,Tvpc, Tcvpx, notif_vpprange );
    $setuphold (posedge CLK  &&& CHKEN1, posedge VPPSEL[0], Tvc, Tcvx, notif_vppsel );
    $setuphold (posedge CLK  &&& CHKEN1, negedge VPPSEL[0], Tvc, Tcvx, notif_vppsel );
    $setuphold (posedge CLK  &&& CHKEN1, posedge VPPSEL[1], Tvc, Tcvx, notif_vppsel );
    $setuphold (posedge CLK  &&& CHKEN1, negedge VPPSEL[1], Tvc, Tcvx, notif_vppsel );
    $setuphold (posedge CLK  &&& CHKEN1, posedge VPPSEL[2], Tvc, Tcvx, notif_vppsel );
    $setuphold (posedge CLK  &&& CHKEN1, negedge VPPSEL[2], Tvc, Tcvx, notif_vppsel );
    $setuphold (posedge CLK  &&& CHKEN1, posedge VPPSEL[3], Tvc, Tcvx, notif_vppsel );
    $setuphold (posedge CLK  &&& CHKEN1, negedge VPPSEL[3], Tvc, Tcvx, notif_vppsel );
    $setuphold (posedge CLK  &&& CHKEN2, posedge D,Tdc, Tcdx, notif_d );
    $setuphold (posedge CLK  &&& CHKEN2, negedge D,Tdc, Tcdx, notif_d );
    $setuphold (posedge CLK , posedge CLKE,Tec, Tcex, notif_clke );
    $setuphold (posedge CLK , negedge CLKE,Tec, Tcex, notif_clke );
    $recovery ( negedge PE,negedge STORE &&& CHKEN1, Trps, notif_pe_STORE_fall_rec);
    $recovery ( negedge RST,posedge CLK &&& CHKEN2, Trrc, notif_rst_CLK_rise_rec);
    $recovery ( posedge STORE,posedge PE &&& CHKEN1, Trsp, notif_store_PE_rise_rec);

endspecify



generic_behav_charge_pump #(MES_ALL) uut (  VPPRANGE_buf, VPPSEL_buf, PE_buf, RST_buf, CLK_buf, D_buf, CLKE_buf, STORE_buf, VPP_buf, UNLOCK_buf, PORST_buf,notif_vpprange, notif_vppsel, notif_pe, notif_pe_STORE_fall_rec, notif_rst, notif_rst_CLK_rise_rec, notif_clk, notif_d, notif_clke, notif_store, notif_store_PE_rise_rec );

always @( posedge CLK_buf )
 begin
   VPPRANGElatched = VPPRANGE_buf;
   VPPSELlatched = VPPSEL_buf;
   Dlatched = D_buf;
   CLKElatched = CLKE_buf;
 end


endmodule




module generic_behav_charge_pump (  VPPRANGE, VPPSEL, PE, RST, CLK, D, CLKE, STORE, VPP, UNLOCK, PORST,notif_vpprange, notif_vppsel, notif_pe, notif_pe_STORE_fall_rec, notif_rst, notif_rst_CLK_rise_rec, notif_clk, notif_d, notif_clke, notif_store, notif_store_PE_rise_rec );

parameter MES_ALL = "ON";
parameter words = 1, bits = 1, timingmode = 1;

input VPPRANGE;
input [3:0] VPPSEL;
input PE;
input RST;
input CLK;
input D;
input CLKE;
input STORE;
output VPP;
output UNLOCK;
output PORST;
input notif_vpprange, notif_vppsel, notif_pe, notif_pe_STORE_fall_rec, notif_rst, notif_rst_CLK_rise_rec, notif_clk, notif_d, notif_clke, notif_store, notif_store_PE_rise_rec;


parameter DataX = { bits { 1'bx } };
parameter DataZ = { bits { 1'bz } };


reg [3:0] VPPSEL_latched;
reg VPPRANGE_latched;
reg RST_start;
reg RST_pulse_over;
reg [7:0] D_req;

reg UNLOCK_I;
reg UNLOCK_prev;
reg PORST_I;
reg VPP_I;
reg store_start;
reg flag_scan;

integer i,j ;
integer D_count ;

reg vppsel_ok, vpprange_ok;

initial
begin
i = 0;
j = 0;
RST_start = 1'b0;
RST_pulse_over = 1'b0;
store_start = 1'b0;
D_count = 0;
D_req = 8'b01101001;
UNLOCK_I = 1'b0;
flag_scan = `True ;
PORST_I = 1'b0;
#1.000;
PORST_I = 1'b1;
#1000000;
PORST_I = 1'b0;
vppsel_ok = 1'b0;
vpprange_ok = 1'b0;
end

assign PORST = PORST_I;
assign UNLOCK = UNLOCK_I;
assign VPP = VPP_I;

always @(notif_d)
begin
 D_count = 0;
 UNLOCK_I <= 1'b0;
 disable OUTPUT_D;
 flag_scan = `False ;
end
always @(notif_pe)
begin
  VPP_I <= 1'bx;
end

always @(notif_pe_STORE_fall_rec)
begin
  VPP_I <= 1'bx;
end

always @(notif_rst_CLK_rise_rec)
begin
  D_count = 0;
  UNLOCK_I <= 1'b0;
end

always @(notif_store_PE_rise_rec)
begin
  VPP_I <= 1'bx;
end

always @(notif_clke)
begin
 if (UNLOCK_prev == 1'b1) begin
  VPP_I <= 1'bx;
  vpprange_ok = 1'b0;
  vppsel_ok = 1'b0;
 end
 else
 begin
  D_count = 0;
  UNLOCK_I <= 1'b0;
  disable OUTPUT_D;
  flag_scan = `False ;
 end
end

always @(notif_vppsel)
begin
 if (UNLOCK == 1'b1 && CLKE === 1'b1) begin
  VPP_I <= 1'bx;
  vppsel_ok = 1'b0;
 end
end
always @(notif_vpprange)
begin
 if (UNLOCK == 1'b1 && CLKE === 1'b1) begin
  VPP_I <= 1'bx;
  vpprange_ok = 1'b0;
 end
end

always @(notif_clk)
begin
 if (UNLOCK_prev == 1'b1) begin
  VPP_I <= 1'bx;
  vpprange_ok = 1'b0;
  vppsel_ok = 1'b0;
 end
 else
 begin
  D_count = 0;
  UNLOCK_I <= 1'b0;
  flag_scan = `False ;
  disable OUTPUT_D;
  disable OUTPUT_D.INCR_COUNT;
 end
end

//---- RST Pulse edge
always @( posedge RST)
begin
 RST_start = 1'b1;
 UNLOCK_I <= 1'b0;
 if (UNLOCK_prev == 1'b1 && STORE == 1'b1 )
 begin
 VPP_I <= 1'bx;
 D_count = 1'b0;
 end
 else
 VPP_I <= 1'b0;
end

always @( negedge RST)
begin
 if ( RST_start == 1'b1)
 begin
  RST_pulse_over = 1'b1;
 end
 D_count = 0;
end

//----Posedge of CLK
always @( posedge CLK )
begin
#0
 if (CLKE === 1'bx)
 begin
   if (UNLOCK_prev == 1'b1) begin
     VPP_I <= 1'bx;
     vppsel_ok = 1'b0;
     vpprange_ok = 1'b0;
   end
   else if (UNLOCK_prev == 1'b0)
     D_count <= 1'b0;
 end
 else
 begin
   if (CLKE == 1'b1 && CLK === 1'bx) begin
     if (UNLOCK_prev == 1'b0)
       D_count = 0;
     else if (UNLOCK_prev == 1'b1) begin
       VPP_I <= 1'bx;
       vppsel_ok = 1'b0;
       vpprange_ok = 1'b0;
     end
   end
   else if (CLKE == 1'b1 && RST_pulse_over == 1'b1 && flag_scan ) begin : OUTPUT_D
     if (UNLOCK_prev === 1'b1 && ( STORE !== 1'b0 || PE !== 1'b0) )
       VPP_I <= 1'bx;
     else if (UNLOCK_prev === 1'b1 && STORE === 1'b0 && PE === 1'b0 ) begin
       if ( (VPPRANGE^VPPRANGE) == 0 ) begin
         vpprange_ok = 1'b1;
         VPPRANGE_latched = VPPRANGE;
       end
       else begin
         vpprange_ok = 1'b0;
         VPPRANGE_latched = 1'bx;
       end
       if ( (VPPSEL^VPPSEL) == 0 ) begin
         vppsel_ok = 1'b1;
         VPPSEL_latched = VPPSEL;
       end
       else begin
         vppsel_ok = 1'b0;
         VPPSEL_latched = 4'bx;
       end
     end
     else if ( UNLOCK_prev === 1'b0 ) begin
       #0
       if (D === 1'bx) begin
         D_count = 0;
       end
       else if (D_req[D_count] === D ) begin  : INCR_COUNT
         D_count = D_count + 1;
       end
       else begin
         D_count = 0;
       end
       if (D_count == 8)
       begin
         #0
         UNLOCK_I <= 1'b1;
         if (STORE !== 1'b0 && PE !== 1'b0)
           VPP_I <= 1'bx;
       end
     end
   end
 end
 UNLOCK_prev <= UNLOCK_I;
end

//----Negedge of CLK
always @( negedge CLK )
begin
 flag_scan = `True ;
end

always @( posedge STORE )
begin
  if (STORE === 1'bx && UNLOCK_prev == 1'b1)
    VPP_I <= 1'bx;
  else begin
    if (UNLOCK_I == 1'b1) begin
      if ( vppsel_ok == 1'b1 && vpprange_ok == 1'b1 )
        store_start = 1'b1;
      else
        store_start = 1'b0;
    end
  end
end

always @( negedge STORE )
begin
 if (UNLOCK === 1'b1 && PE == 1'b1)
  VPP_I <= 1'bx;
  store_start = 1'b0;
end

always @(posedge PE)
begin
 if (PE === 1'bx && UNLOCK_prev == 1'b1)
  VPP_I <= 1'bx;
 else
 begin
  if (UNLOCK === 1'b1)
  begin
   if (store_start == 1'b1)
   begin
    VPP_I <= 1'b1;
   end
   else
    VPP_I <= 1'bx;
  end
 end

end

always @(negedge PE)
begin
  VPP_I <= 1'b0;
end

endmodule
