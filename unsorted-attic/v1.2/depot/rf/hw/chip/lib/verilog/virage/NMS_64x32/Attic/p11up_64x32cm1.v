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
//  Software           : Rev: 3.2.1 alpha                              
//  Library Format     : Rev: 1.05.00                                  
//  Compiler Name      : nc15upfp1p11nonrm16sa                         
//  Date of Generation : Fri Nov 01 18:54:40 GMT 2002                  
//                                                                     
//---------------------------------------------------------------------
//   --------------------------------------------------------------     
//                       Template Revision : 1.0.3                      
//   --------------------------------------------------------------     



//                * Synchronous, 1-Port Non Volatile RAM *            
//                      * Verilog Behavioral Model *                  
//                THIS IS A SYNCHRONOUS 1-PORT MEMORY MODEL           
//                                                                    
//   Memory Name:p11up_64x32cm1                                       
//   Memory Size:64 words x 32 bits                                   
//                                                                    
//                               PORT NAME                            
//                               ---------                            
//               Output Ports                                         
//                                   Q[31:0]                          
//                                   SO                               
//                                   MATCH                            
//                                   RCREADY                          
//               Input Ports:                                         
//                                   ADR[5:0]                         
//                                   D[31:0]                          
//                                   WE                               
//                                   ME                               
//                                   OE                               
//                                   CLK                              
//                                   SI                               
//                                   SCLK                             
//                                   SME                              
//                                   COMP                             
//                                   STORE                            
//                                   RECALL                           
//                                   VPP                              
//                                   MRCL0                            
//                                   MRCL1                            
//                                   TECC0                            
//                                   TECC1                            
//                                   BIAS0                            
//                                   BIAS1                            
//                                   PU1                              
//                                   PU2                              



`resetall 

`timescale 1 ns / 10 ps 
`celldefine 

`define True    1'b1
`define False   1'b0

module p11up_64x32cm1 ( Q, SO, MATCH, ADR, D, WE, ME, OE, CLK, SI, SCLK, SME, COMP, STORE, RECALL, VPP, MRCL0, MRCL1, TECC0, TECC1, BIAS0, BIAS1, RCREADY, PU1, PU2);

output  [31:0] Q;
output SO;
output MATCH;
input  [5:0] ADR;
input  [31:0] D;
input WE;
input ME;
input OE;
input CLK;
input SI;
input SCLK;
input SME;
input COMP;
input STORE;
input RECALL;
input VPP;
input MRCL0;
input MRCL1;
input TECC0;
input TECC1;
input BIAS0;
input BIAS1;
output RCREADY;
input PU1;
input PU2;


parameter MES_ALL = "ON";

// Local registers, wires, etc


reg notif_adr; 
reg notif_d; 
reg notif_we; 
reg notif_me; 
reg notif_clk; 
reg notif_clk_COMP_rise_rec;
reg notif_clk_SCLK_rise_rec;
reg notif_clk_RECALL_rise_rec;
reg notif_clk_STORE_rise_rec;
reg notif_si; 
reg notif_sclk; 
reg notif_sclk_COMP_rise_rec;
reg notif_sclk_CLK_rise_rec;
reg notif_sclk_RECALL_rise_rec;
reg notif_sclk_STORE_rise_rec;
reg notif_sme; 
reg notif_comp; 
reg notif_comp_RECALL_rise_rec;
reg notif_comp_STORE_rise_rec;
reg notif_comp_SCLK_rise_rec;
reg notif_comp_CLK_rise_rec;
reg notif_store; 
reg notif_store_RECALL_rise_rec;
reg notif_store_VPP_rise_rec;
reg notif_store_COMP_rise_rec;
reg notif_store_SCLK_rise_rec;
reg notif_store_CLK_rise_rec;
reg notif_recall; 
reg notif_recall_STORE_rise_rec;
reg notif_recall_COMP_rise_rec;
reg notif_recall_SCLK_rise_rec;
reg notif_recall_CLK_rise_rec;
reg notif_vpp; 
reg notif_vpp_STORE_fall_rec;
reg notif_mrcl0; 
reg notif_mrcl1; 
reg notif_tecc0; 
reg notif_tecc1; 
reg notif_bias0; 
reg notif_bias1; 
reg ADRFLAGA;
wire CHKENWE;
wire CHKENCLK;
wire CHKENSCLK;
wire CHKENCLKSCLK;
wire CHKENSCLKCLK;
wire CHKENME;
wire CHKENADR;
wire CHKEND;
wire CHKEN;
wire CHKEN6A;
wire CHKEN7A;
wire CHKEN10A;
wire CHKEN11A;
wire CHKEN12A;
wire CHKEN13A;
wire CHKEN14A;
reg SMElatched;
reg chk_tmp0;
reg chk_tp0;
wire OE_eff;


reg [5:0] ADRlatched;
reg [31:0] Dlatched;
reg WElatched;
reg MElatched;

wire [31:0] Q_buf;
bufif1 (Q[0], Q_buf[0], OE_eff );
bufif1 (Q[1], Q_buf[1], OE_eff );
bufif1 (Q[2], Q_buf[2], OE_eff );
bufif1 (Q[3], Q_buf[3], OE_eff );
bufif1 (Q[4], Q_buf[4], OE_eff );
bufif1 (Q[5], Q_buf[5], OE_eff );
bufif1 (Q[6], Q_buf[6], OE_eff );
bufif1 (Q[7], Q_buf[7], OE_eff );
bufif1 (Q[8], Q_buf[8], OE_eff );
bufif1 (Q[9], Q_buf[9], OE_eff );
bufif1 (Q[10], Q_buf[10], OE_eff );
bufif1 (Q[11], Q_buf[11], OE_eff );
bufif1 (Q[12], Q_buf[12], OE_eff );
bufif1 (Q[13], Q_buf[13], OE_eff );
bufif1 (Q[14], Q_buf[14], OE_eff );
bufif1 (Q[15], Q_buf[15], OE_eff );
bufif1 (Q[16], Q_buf[16], OE_eff );
bufif1 (Q[17], Q_buf[17], OE_eff );
bufif1 (Q[18], Q_buf[18], OE_eff );
bufif1 (Q[19], Q_buf[19], OE_eff );
bufif1 (Q[20], Q_buf[20], OE_eff );
bufif1 (Q[21], Q_buf[21], OE_eff );
bufif1 (Q[22], Q_buf[22], OE_eff );
bufif1 (Q[23], Q_buf[23], OE_eff );
bufif1 (Q[24], Q_buf[24], OE_eff );
bufif1 (Q[25], Q_buf[25], OE_eff );
bufif1 (Q[26], Q_buf[26], OE_eff );
bufif1 (Q[27], Q_buf[27], OE_eff );
bufif1 (Q[28], Q_buf[28], OE_eff );
bufif1 (Q[29], Q_buf[29], OE_eff );
bufif1 (Q[30], Q_buf[30], OE_eff );
bufif1 (Q[31], Q_buf[31], OE_eff );
buf (SO, SO_buf);
buf (MATCH, MATCH_buf);
wire [5:0] ADR_buf;
buf (ADR_buf[0], ADR[0]);
buf (ADR_buf[1], ADR[1]);
buf (ADR_buf[2], ADR[2]);
buf (ADR_buf[3], ADR[3]);
buf (ADR_buf[4], ADR[4]);
buf (ADR_buf[5], ADR[5]);
wire [31:0] D_buf;
buf (D_buf[0], D[0]);
buf (D_buf[1], D[1]);
buf (D_buf[2], D[2]);
buf (D_buf[3], D[3]);
buf (D_buf[4], D[4]);
buf (D_buf[5], D[5]);
buf (D_buf[6], D[6]);
buf (D_buf[7], D[7]);
buf (D_buf[8], D[8]);
buf (D_buf[9], D[9]);
buf (D_buf[10], D[10]);
buf (D_buf[11], D[11]);
buf (D_buf[12], D[12]);
buf (D_buf[13], D[13]);
buf (D_buf[14], D[14]);
buf (D_buf[15], D[15]);
buf (D_buf[16], D[16]);
buf (D_buf[17], D[17]);
buf (D_buf[18], D[18]);
buf (D_buf[19], D[19]);
buf (D_buf[20], D[20]);
buf (D_buf[21], D[21]);
buf (D_buf[22], D[22]);
buf (D_buf[23], D[23]);
buf (D_buf[24], D[24]);
buf (D_buf[25], D[25]);
buf (D_buf[26], D[26]);
buf (D_buf[27], D[27]);
buf (D_buf[28], D[28]);
buf (D_buf[29], D[29]);
buf (D_buf[30], D[30]);
buf (D_buf[31], D[31]);
buf (WE_buf, WE);
buf (ME_buf, ME);
buf (OE_buf, OE);
buf (CLK_buf, CLK);
buf (SI_buf, SI);
buf (SCLK_buf, SCLK);
buf (SME_buf, SME);
buf (COMP_buf, COMP);
buf (STORE_buf, STORE);
buf (RECALL_buf, RECALL);
buf (VPP_buf, VPP);
buf (MRCL0_buf, MRCL0);
buf (MRCL1_buf, MRCL1);
buf (TECC0_buf, TECC0);
buf (TECC1_buf, TECC1);
buf (BIAS0_buf, BIAS0);
buf (BIAS1_buf, BIAS1);
buf (RCREADY, RCREADY_buf);
buf (PU1_buf, PU1);
buf (PU2_buf, PU2);

// Disable recovery checks for initial 10 ns
wire enable_recovery_checks;
assign enable_recovery_checks = (( $time > 10)?1'b1:1'b0);

and u_chk_enable_sclk ( CHKENSCLK, SME_buf, enable_recovery_checks);
and u_chk_enableclksclk ( CHKENCLKSCLK, MElatched,SME_buf);
and u_chk_enablesclkclk ( CHKENSCLKCLK, SME_buf,ME_buf);
and u_CHKENWE_0 ( CHKENWE, ME_buf, ADRFLAGA);
and u_chk_enable_clk ( CHKENCLK, ME_buf, enable_recovery_checks);
and u_CHKEND_0 ( CHKEND, ME_buf, ADRFLAGA, WE_buf);
buf u_CHKENADR_0 ( CHKENADR, ME_buf );

buf u_CHKENME_0 ( CHKENME, ADRFLAGA );

and u_CHKEN10A_0 ( CHKEN10A, !ME_buf, !SME_buf, !STORE_buf,  !VPP_buf, !RECALL_buf );
and u_CHKEN11A_0 ( CHKEN11A, !ME_buf, !SME_buf, VPP_buf, !COMP_buf, !RECALL_buf );
and u_CHKEN12A_0 ( CHKEN12A, !WE_buf, !SME_buf, !STORE_buf, !VPP_buf, !COMP_buf );
and u_CHKEN13A_0 ( CHKEN13A, SME_buf, !STORE_buf, !VPP_buf, !COMP_buf );
and u_CHKEN14A_0 ( CHKEN14A, !STORE_buf, !VPP_buf, !COMP_buf );

specify
 
    specparam PATHPULSE$OE$Q = ( 0, 0.01 );
    specparam PATHPULSE$RECALL$RCREADY = ( 0, 0.01 );
    specparam PATHPULSE$COMP$RCREADY = ( 0, 0.01 );
    specparam

        Tac = 1.20,
        Tcax = 1.00,
        Tdc = 1.20,
        Tcdx = 1.00,
        Twc = 1.20,
        Tcwx = 1.00,
        Tmc = 1.20,
        Tcmx = 1.00,
        Tcc = 6.71,
        Tcl = 1.42,
        Tch = 1.42,
        Tdcs = 4.25,
        Tcdxs = 1.00,
        Tccs = 96.54,
        Tcls = 3.54,
        Tchs = 3.54,
        Tmcs = 4.25,
        Tcmxs = 2.77,
        Trcomp = 4008.40,
        Tcomp = 44017.79,
        Trstore = 3837102.33,
        Txvpp = 492199.73,
        Tstore = 10000000.00,
        Trrecall = 4008.40,
        Trecall = 44017.79,
        Trvpp = 194139.11,
        Tvpp = 8000000.00,
        Tscomp = 8850.46,
        Thcomp = 35.40,
        Tcq = 6.52,
        Tcqx = 0.35,
        Toq = 1.27,
        Toqz = 1.27,
        Tcqs = 96.54,
        Tcqxs = 0.47,
        Tcso = 4.49,
        Tcsox = 0.35,
        Tcmatch = 44012.48,
        Txmatch = 1.77,
        Trcrdy = 44017.79,
        Txrcrdy = 3.54;

     if ( OE )
       ( posedge CLK => (  Q[0]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[1]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[2]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[3]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[4]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[5]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[6]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[7]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[8]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[9]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[10]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[11]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[12]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[13]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[14]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[15]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[16]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[17]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[18]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[19]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[20]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[21]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[22]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[23]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[24]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[25]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[26]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[27]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[28]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[29]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[30]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
     if ( OE )
       ( posedge CLK => (  Q[31]  : 1'bx )) = (  Tcq, Tcq, Tcqx, Tcq, Tcqx, Tcq );
       ( OE =>  Q[0] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[1] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[2] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[3] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[4] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[5] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[6] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[7] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[8] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[9] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[10] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[11] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[12] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[13] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[14] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[15] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[16] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[17] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[18] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[19] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[20] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[21] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[22] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[23] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[24] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[25] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[26] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[27] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[28] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[29] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[30] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
       ( OE =>  Q[31] ) = (  Toq, Toq, Toqz, Toq, Toqz, Toq );
     if ( SME  )
       ( posedge SCLK => (  SO  : 1'bx )) = (  Tcqs, Tcqs, Tcqxs, Tcqs, Tcqxs, Tcqs );
       ( posedge CLK => (  SO  : 1'bx )) = (  Tcso, Tcso, Tcsox, Tcso, Tcsox, Tcso );
       ( COMP =>  MATCH ) = (  Tcmatch, Txmatch );
       ( COMP =>  RCREADY ) = (  Trcrdy, Txrcrdy );
       ( RECALL =>  RCREADY ) = (  Trcrdy, Txrcrdy );
// Timing Checks
    $width (negedge CLK, Tcl, 0, notif_clk);
    $width (posedge CLK, Tch, 0, notif_clk);
    $period (posedge CLK, Tcc, notif_clk);
    $period (negedge CLK, Tcc, notif_clk);
    $width (negedge SCLK, Tcls, 0, notif_sclk);
    $width (posedge SCLK, Tchs, 0, notif_sclk);
    $period (posedge SCLK, Tccs, notif_sclk);
    $period (negedge SCLK, Tccs, notif_sclk);
    $width (posedge COMP, Tcomp, 0, notif_comp);
    $width (posedge STORE, Tstore, 0, notif_store);
    $width (posedge RECALL, Trecall, 0, notif_recall);
    $width (posedge VPP, Tvpp, 0, notif_vpp);
    $hold (posedge CLK  &&& CHKENADR, posedge ADR[0], Tcax, notif_adr );
    $hold (posedge CLK  &&& CHKENADR, negedge ADR[0], Tcax, notif_adr );
    $hold (posedge CLK  &&& CHKENADR, posedge ADR[1], Tcax, notif_adr );
    $hold (posedge CLK  &&& CHKENADR, negedge ADR[1], Tcax, notif_adr );
    $hold (posedge CLK  &&& CHKENADR, posedge ADR[2], Tcax, notif_adr );
    $hold (posedge CLK  &&& CHKENADR, negedge ADR[2], Tcax, notif_adr );
    $hold (posedge CLK  &&& CHKENADR, posedge ADR[3], Tcax, notif_adr );
    $hold (posedge CLK  &&& CHKENADR, negedge ADR[3], Tcax, notif_adr );
    $hold (posedge CLK  &&& CHKENADR, posedge ADR[4], Tcax, notif_adr );
    $hold (posedge CLK  &&& CHKENADR, negedge ADR[4], Tcax, notif_adr );
    $hold (posedge CLK  &&& CHKENADR, posedge ADR[5], Tcax, notif_adr );
    $hold (posedge CLK  &&& CHKENADR, negedge ADR[5], Tcax, notif_adr );
    $setup ( posedge ADR[0],posedge CLK  &&& CHKENADR, Tac, notif_adr );
    $setup ( negedge ADR[0],posedge CLK  &&& CHKENADR, Tac, notif_adr );
    $setup ( posedge ADR[1],posedge CLK  &&& CHKENADR, Tac, notif_adr );
    $setup ( negedge ADR[1],posedge CLK  &&& CHKENADR, Tac, notif_adr );
    $setup ( posedge ADR[2],posedge CLK  &&& CHKENADR, Tac, notif_adr );
    $setup ( negedge ADR[2],posedge CLK  &&& CHKENADR, Tac, notif_adr );
    $setup ( posedge ADR[3],posedge CLK  &&& CHKENADR, Tac, notif_adr );
    $setup ( negedge ADR[3],posedge CLK  &&& CHKENADR, Tac, notif_adr );
    $setup ( posedge ADR[4],posedge CLK  &&& CHKENADR, Tac, notif_adr );
    $setup ( negedge ADR[4],posedge CLK  &&& CHKENADR, Tac, notif_adr );
    $setup ( posedge ADR[5],posedge CLK  &&& CHKENADR, Tac, notif_adr );
    $setup ( negedge ADR[5],posedge CLK  &&& CHKENADR, Tac, notif_adr );
    $hold (posedge CLK  &&& CHKEND, posedge D[0], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[0], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[1], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[1], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[2], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[2], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[3], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[3], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[4], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[4], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[5], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[5], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[6], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[6], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[7], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[7], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[8], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[8], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[9], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[9], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[10], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[10], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[11], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[11], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[12], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[12], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[13], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[13], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[14], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[14], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[15], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[15], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[16], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[16], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[17], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[17], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[18], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[18], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[19], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[19], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[20], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[20], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[21], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[21], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[22], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[22], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[23], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[23], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[24], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[24], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[25], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[25], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[26], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[26], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[27], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[27], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[28], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[28], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[29], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[29], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[30], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[30], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, posedge D[31], Tcdx, notif_d );
    $hold (posedge CLK  &&& CHKEND, negedge D[31], Tcdx, notif_d );
    $setup ( posedge D[0],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[0],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[1],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[1],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[2],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[2],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[3],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[3],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[4],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[4],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[5],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[5],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[6],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[6],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[7],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[7],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[8],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[8],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[9],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[9],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[10],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[10],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[11],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[11],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[12],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[12],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[13],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[13],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[14],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[14],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[15],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[15],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[16],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[16],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[17],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[17],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[18],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[18],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[19],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[19],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[20],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[20],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[21],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[21],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[22],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[22],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[23],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[23],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[24],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[24],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[25],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[25],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[26],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[26],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[27],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[27],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[28],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[28],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[29],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[29],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[30],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[30],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( posedge D[31],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $setup ( negedge D[31],posedge CLK  &&& CHKEND, Tdc, notif_d );
    $hold (posedge CLK  &&& CHKENWE, posedge WE, Tcwx, notif_we );
    $hold (posedge CLK  &&& CHKENWE, negedge WE, Tcwx, notif_we );
    $setup ( posedge WE,posedge CLK  &&& CHKENWE, Twc, notif_we );
    $setup ( negedge WE,posedge CLK  &&& CHKENWE, Twc, notif_we );
    $hold (posedge CLK  &&& CHKENME, posedge ME, Tcmx, notif_me );
    $hold (posedge CLK  &&& CHKENME, negedge ME, Tcmx, notif_me );
    $setup ( posedge ME,posedge CLK  &&& CHKENME, Tmc, notif_me );
    $setup ( negedge ME,posedge CLK  &&& CHKENME, Tmc, notif_me );
    $hold (posedge SCLK , posedge SI, Tcdxs, notif_si );
    $hold (posedge SCLK , negedge SI, Tcdxs, notif_si );
    $setup ( posedge SI,posedge SCLK , Tdcs, notif_si );
    $setup ( negedge SI,posedge SCLK , Tdcs, notif_si );
    $hold (posedge SCLK , posedge SME, Tcmxs, notif_sme );
    $hold (posedge SCLK , negedge SME, Tcmxs, notif_sme );
    $setup ( posedge SME,posedge SCLK , Tmcs, notif_sme );
    $setup ( negedge SME,posedge SCLK , Tmcs, notif_sme );
    $hold (negedge COMP , posedge MRCL0, Thcomp, notif_mrcl0 );
    $hold (negedge COMP , negedge MRCL0, Thcomp, notif_mrcl0 );
    $setup ( posedge MRCL0,posedge COMP , Tscomp, notif_mrcl0 );
    $setup ( negedge MRCL0,posedge COMP , Tscomp, notif_mrcl0 );
    $hold (negedge RECALL , posedge MRCL0, Thcomp, notif_mrcl0 );
    $hold (negedge RECALL , negedge MRCL0, Thcomp, notif_mrcl0 );
    $setup ( posedge MRCL0,posedge RECALL , Tscomp, notif_mrcl0 );
    $setup ( negedge MRCL0,posedge RECALL , Tscomp, notif_mrcl0 );
    $hold (negedge COMP , posedge MRCL1, Thcomp, notif_mrcl1 );
    $hold (negedge COMP , negedge MRCL1, Thcomp, notif_mrcl1 );
    $setup ( posedge MRCL1,posedge COMP , Tscomp, notif_mrcl1 );
    $setup ( negedge MRCL1,posedge COMP , Tscomp, notif_mrcl1 );
    $hold (negedge RECALL , posedge MRCL1, Thcomp, notif_mrcl1 );
    $hold (negedge RECALL , negedge MRCL1, Thcomp, notif_mrcl1 );
    $setup ( posedge MRCL1,posedge RECALL , Tscomp, notif_mrcl1 );
    $setup ( negedge MRCL1,posedge RECALL , Tscomp, notif_mrcl1 );
    $hold (negedge COMP , posedge TECC0, Thcomp, notif_tecc0 );
    $hold (negedge COMP , negedge TECC0, Thcomp, notif_tecc0 );
    $setup ( posedge TECC0,posedge COMP , Tscomp, notif_tecc0 );
    $setup ( negedge TECC0,posedge COMP , Tscomp, notif_tecc0 );
    $hold (negedge RECALL , posedge TECC0, Thcomp, notif_tecc0 );
    $hold (negedge RECALL , negedge TECC0, Thcomp, notif_tecc0 );
    $setup ( posedge TECC0,posedge RECALL , Tscomp, notif_tecc0 );
    $setup ( negedge TECC0,posedge RECALL , Tscomp, notif_tecc0 );
    $hold (negedge COMP , posedge TECC1, Thcomp, notif_tecc1 );
    $hold (negedge COMP , negedge TECC1, Thcomp, notif_tecc1 );
    $setup ( posedge TECC1,posedge COMP , Tscomp, notif_tecc1 );
    $setup ( negedge TECC1,posedge COMP , Tscomp, notif_tecc1 );
    $hold (negedge RECALL , posedge TECC1, Thcomp, notif_tecc1 );
    $hold (negedge RECALL , negedge TECC1, Thcomp, notif_tecc1 );
    $setup ( posedge TECC1,posedge RECALL , Tscomp, notif_tecc1 );
    $setup ( negedge TECC1,posedge RECALL , Tscomp, notif_tecc1 );
    $hold (negedge COMP , posedge BIAS0, Thcomp, notif_bias0 );
    $hold (negedge COMP , negedge BIAS0, Thcomp, notif_bias0 );
    $setup ( posedge BIAS0,posedge COMP , Tscomp, notif_bias0 );
    $setup ( negedge BIAS0,posedge COMP , Tscomp, notif_bias0 );
    $hold (negedge RECALL , posedge BIAS0, Thcomp, notif_bias0 );
    $hold (negedge RECALL , negedge BIAS0, Thcomp, notif_bias0 );
    $setup ( posedge BIAS0,posedge RECALL , Tscomp, notif_bias0 );
    $setup ( negedge BIAS0,posedge RECALL , Tscomp, notif_bias0 );
    $hold (negedge COMP , posedge BIAS1, Thcomp, notif_bias1 );
    $hold (negedge COMP , negedge BIAS1, Thcomp, notif_bias1 );
    $setup ( posedge BIAS1,posedge COMP , Tscomp, notif_bias1 );
    $setup ( negedge BIAS1,posedge COMP , Tscomp, notif_bias1 );
    $hold (negedge RECALL , posedge BIAS1, Thcomp, notif_bias1 );
    $hold (negedge RECALL , negedge BIAS1, Thcomp, notif_bias1 );
    $setup ( posedge BIAS1,posedge RECALL , Tscomp, notif_bias1 );
    $setup ( negedge BIAS1,posedge RECALL , Tscomp, notif_bias1 );


    $recovery ( posedge CLK ,posedge COMP  &&& CHKENCLK, Tcc, notif_clk_COMP_rise_rec);




    $recovery ( posedge CLK ,posedge SCLK  &&& CHKENSCLKCLK, Tcc, notif_clk_SCLK_rise_rec);




    $recovery ( posedge CLK ,posedge RECALL  &&& CHKENCLK, Tcc, notif_clk_RECALL_rise_rec);




    $recovery ( posedge CLK ,posedge STORE  &&& CHKENCLK, Tcc, notif_clk_STORE_rise_rec);




    $recovery ( posedge SCLK ,posedge COMP  &&& CHKENSCLK, Tccs, notif_sclk_COMP_rise_rec);




    $recovery ( posedge SCLK ,posedge CLK  &&& CHKENCLKSCLK, Tccs, notif_sclk_CLK_rise_rec);




    $recovery ( posedge SCLK ,posedge RECALL  &&& CHKENSCLK, Tccs, notif_sclk_RECALL_rise_rec);




    $recovery ( posedge SCLK ,posedge STORE  &&& CHKENSCLK, Tccs, notif_sclk_STORE_rise_rec);



    $recovery ( negedge COMP ,posedge RECALL , Trcomp, notif_comp_RECALL_rise_rec);

    $recovery ( posedge COMP ,posedge RECALL , Trcomp, notif_comp_RECALL_rise_rec);



    $recovery ( negedge COMP ,posedge STORE , Trcomp, notif_comp_STORE_rise_rec);

    $recovery ( posedge COMP ,posedge STORE , Trcomp, notif_comp_STORE_rise_rec);



    $recovery ( negedge COMP ,posedge SCLK  &&& CHKENSCLK, Trcomp, notif_comp_SCLK_rise_rec);




    $recovery ( negedge COMP ,posedge CLK  &&& CHKENCLK, Trcomp, notif_comp_CLK_rise_rec);




    $recovery ( negedge STORE ,posedge RECALL , Trstore, notif_store_RECALL_rise_rec);





    $recovery ( posedge STORE ,posedge VPP , Txvpp, notif_store_VPP_rise_rec);



    $recovery ( negedge STORE ,posedge COMP , Trstore, notif_store_COMP_rise_rec);




    $recovery ( negedge STORE ,posedge SCLK  &&& CHKENSCLK, Trstore, notif_store_SCLK_rise_rec);




    $recovery ( negedge STORE ,posedge CLK  &&& CHKENCLK, Trstore, notif_store_CLK_rise_rec);




    $recovery ( negedge RECALL ,posedge STORE , Trrecall, notif_recall_STORE_rise_rec);




    $recovery ( negedge RECALL ,posedge COMP , Trrecall, notif_recall_COMP_rise_rec);




    $recovery ( negedge RECALL ,posedge SCLK  &&& CHKENSCLK, Trrecall, notif_recall_SCLK_rise_rec);




    $recovery ( negedge RECALL ,posedge CLK  &&& CHKENCLK, Trrecall, notif_recall_CLK_rise_rec);






    $recovery ( negedge VPP ,negedge STORE , Trvpp, notif_vpp_STORE_fall_rec);


endspecify



generic_behav_p11up_64x32cm1 #(MES_ALL) uut (  Q_buf, SO_buf, MATCH_buf, ADR_buf, D_buf, WE_buf, ME_buf, OE_buf, CLK_buf, SI_buf, SCLK_buf, SME_buf, COMP_buf, STORE_buf, RECALL_buf, VPP_buf, MRCL0_buf, MRCL1_buf, TECC0_buf, TECC1_buf, BIAS0_buf, BIAS1_buf, RCREADY_buf, PU1_buf, PU2_buf,notif_adr, notif_d, notif_we, notif_me, notif_clk, notif_clk_COMP_rise_rec, notif_clk_SCLK_rise_rec, notif_clk_RECALL_rise_rec, notif_clk_STORE_rise_rec, notif_si, notif_sclk, notif_sclk_COMP_rise_rec, notif_sclk_CLK_rise_rec, notif_sclk_RECALL_rise_rec, notif_sclk_STORE_rise_rec, notif_sme, notif_comp, notif_comp_RECALL_rise_rec, notif_comp_STORE_rise_rec, notif_comp_SCLK_rise_rec, notif_comp_CLK_rise_rec, notif_store, notif_store_RECALL_rise_rec, notif_store_VPP_rise_rec, notif_store_COMP_rise_rec, notif_store_SCLK_rise_rec, notif_store_CLK_rise_rec, notif_recall, notif_recall_STORE_rise_rec, notif_recall_COMP_rise_rec, notif_recall_SCLK_rise_rec, notif_recall_CLK_rise_rec, notif_vpp, notif_vpp_STORE_fall_rec, notif_mrcl0, 
notif_mrcl1, notif_tecc0, notif_tecc1, notif_bias0, notif_bias1 );

and u_OE_0 (OE_eff, OE_buf, 1'b1);

always @( posedge CLK_buf )
 begin
   ADRlatched = ADR_buf;
   Dlatched = D_buf;
   WElatched = WE_buf;
   MElatched = ME_buf;
   ADRFLAGA = 1;
 end

always @( posedge SCLK_buf )
 begin
   SMElatched = SME;
 end


endmodule




module generic_behav_p11up_64x32cm1 (  Q, SO, MATCH, ADR, D, WE, ME, OE, CLK, SI, SCLK, SME, COMP, STORE, RECALL, VPP, MRCL0, MRCL1, TECC0, TECC1, BIAS0, BIAS1, RCREADY, PU1, PU2,notif_adr, notif_d, notif_we, notif_me, notif_clk, notif_clk_COMP_rise_rec, notif_clk_SCLK_rise_rec, notif_clk_RECALL_rise_rec, notif_clk_STORE_rise_rec, notif_si, notif_sclk, notif_sclk_COMP_rise_rec, notif_sclk_CLK_rise_rec, notif_sclk_RECALL_rise_rec, notif_sclk_STORE_rise_rec, notif_sme, notif_comp, notif_comp_RECALL_rise_rec, notif_comp_STORE_rise_rec, notif_comp_SCLK_rise_rec, notif_comp_CLK_rise_rec, notif_store, notif_store_RECALL_rise_rec, notif_store_VPP_rise_rec, notif_store_COMP_rise_rec, notif_store_SCLK_rise_rec, notif_store_CLK_rise_rec, notif_recall, notif_recall_STORE_rise_rec, notif_recall_COMP_rise_rec, notif_recall_SCLK_rise_rec, notif_recall_CLK_rise_rec, notif_vpp, notif_vpp_STORE_fall_rec, notif_mrcl0, notif_mrcl1, notif_tecc0, notif_tecc1, notif_bias0, notif_bias1 );

parameter MES_ALL = "ON";
parameter words = 64, bits = 32, addrbits = 6, timingmode = 1;

output [bits-1:0] Q;
output SO;
output MATCH;
input [addrbits-1:0] ADR;
input [bits-1:0] D;
input WE;
input ME;
input OE;
input CLK;
input SI;
input SCLK;
input SME;
input COMP;
input STORE;
input RECALL;
input VPP;
input MRCL0;
input MRCL1;
input TECC0;
input TECC1;
input BIAS0;
input BIAS1;
output RCREADY;
input PU1;
input PU2;
input notif_adr, notif_d, notif_we, notif_me, notif_clk, notif_clk_COMP_rise_rec, notif_clk_SCLK_rise_rec, notif_clk_RECALL_rise_rec, notif_clk_STORE_rise_rec, notif_si, notif_sclk, notif_sclk_COMP_rise_rec, notif_sclk_CLK_rise_rec, notif_sclk_RECALL_rise_rec, notif_sclk_STORE_rise_rec, notif_sme, notif_comp, notif_comp_RECALL_rise_rec, notif_comp_STORE_rise_rec, notif_comp_SCLK_rise_rec, notif_comp_CLK_rise_rec, notif_store, notif_store_RECALL_rise_rec, notif_store_VPP_rise_rec, notif_store_COMP_rise_rec, notif_store_SCLK_rise_rec, notif_store_CLK_rise_rec, notif_recall, notif_recall_STORE_rise_rec, notif_recall_COMP_rise_rec, notif_recall_SCLK_rise_rec, notif_recall_CLK_rise_rec, notif_vpp, notif_vpp_STORE_fall_rec, notif_mrcl0, notif_mrcl1, notif_tecc0, notif_tecc1, notif_bias0, notif_bias1;


parameter DataX = { bits { 1'bx } };
parameter DataZ = { bits { 1'bz } };

reg [bits-1:0] memb [words-1:0];
reg [bits-1:0] earom [words-1:0];

reg [bits-1:0] temp1;
reg [bits-1:0] temp2;
reg [bits-1:0] temp3;
integer store_success_count;



real comp_start_time;
real comp_end_time;
real recall_start_time;
real recall_end_time;
real CLK_T;
reg
        flaga_read_ok,
        flaga_we_ok,
        flaga_d_ok,
        flaga_adr_ok,
        flaga_range_ok;
reg     flaga_adr_viol;
reg     flaga_clk_valid;
reg     flaga_output_ok;
reg     flaga_serial_read_ok;
reg     flaga_si_ok;
reg     flaga_sclk_valid;
reg     flag_keep_match_low ;
reg     rcready_viol_flag ;


reg [bits-1:0] Q;
reg [bits-1:0] QI;

integer i,j;
integer store_ctr;
integer store_ctr_buf;

task BlastCell;
    input [bits - 1 : 0] bits; 
    integer i;
begin
    if ($time > 0) begin
      $display("      time=%t; instance=%m (NVM1H)",$realtime);
      $display("      Corrupting the SRAM");
      if (store_ctr != 0) begin
        store_ctr = 0;
      end
      for (i = 0; i < words; i = i + 1)
        memb[i] = memb[i] ^ (bits & DataX); 
    end
end
endtask


task corrupt_all_loc;
    input flag_range_ok; 
    integer i;
begin
   if( flag_range_ok == `True) 
    if ($time > 0) 
     if (store_ctr != 0) begin
      store_ctr = 0;
     end
        for (i = 0; i < words; i = i + 1)
            memb[i] <= DataX; 
end
endtask

task corrupt_cur_loc;
    input flag_range_ok; 
    input [5:0] ADRlatched;
    integer i;
begin
   if( flag_range_ok == `False) 
    if ($time > 0) 
     if (store_ctr != 0) begin
      store_ctr = 0;
     end
       if ( ADRlatched < words ) 
         memb[ADRlatched] = DataX;
end

endtask


task BlastEarom;
    integer i;
begin
    if ($time > 0) begin
      $display("      time=%t; instance=%m (NVM1H)",$realtime);
      $display("      Corrupting the EAROM");
      if (store_ctr != 0) begin
        store_ctr = 0;
      end
      for (i = 0; i < words; i = i + 1)
        earom[i] = DataX; 
    end
end
endtask

reg SOI;
reg MATCHI;
reg CLK_old;
reg SCLK_old;
reg STORE_old;
reg RECALL_old;
reg VPP_old;
reg RCREADYI;

reg WElatched;
reg WE_old;
reg MElatched;
reg ME_old;
reg [addrbits-1:0] ADRlatched;

reg [addrbits-1:0] ADR_old;

reg [bits-1:0] Dlatched;

reg [bits-1:0] D_old;

reg ME_chk;
reg WE_chk;
reg SME_chk;
reg SMElatched;





// Perform Sanity Check on Port A, Corrupt memory if required

task checkSanityOnAport;

 #0                // let CLOCK and NOTIFIER stuff execute first
 case ( {flaga_serial_read_ok,flaga_adr_ok, flaga_we_ok, flaga_d_ok} ) // only 1 and 0

  4'b1111   : ;                                                // everything ok!!!

  4'b1101,
  4'b1100   : corrupt_cur_loc( flaga_we_ok,ADRlatched);          // WE is unstable

  4'b1110   : if (WElatched !== 1'b0)
              corrupt_cur_loc( flaga_d_ok,ADRlatched);         // Data is unstable

  4'b1000,
  4'b1001   : corrupt_all_loc(flaga_range_ok);            // ADR and WE unstable

  4'b1010,
  4'b1011   : corrupt_all_loc(flaga_range_ok);

 endcase
endtask


// PORT FUNCTIONALITY FOR VIOLATION BEHAVIOR
initial
 begin
  store_success_count = 1;
  store_ctr = 0;
  store_ctr_buf = 0;
  flaga_adr_ok  = `True;
  flaga_range_ok = `True;
  flaga_we_ok   = `True;
  flaga_d_ok    = `True;
  flaga_read_ok = `True;
  flaga_output_ok = `True;
  flaga_adr_viol = `True;
  flaga_clk_valid = `True;
  flaga_si_ok    = `True;
  flaga_serial_read_ok = `True;
  flaga_sclk_valid = `True;
  flag_keep_match_low = `False;
end

always @(notif_bias0)            // BIAS0 violation
begin
 if  ( $realtime == recall_start_time )    // For setup violation with RECALL
  BlastCell(DataX);
 else if ( $realtime == comp_start_time ) begin   // For setup violation with COMP
  flag_keep_match_low = `True;
  MATCHI = 1'b0;
 end
 else if (($realtime - recall_end_time ) > ($realtime - comp_end_time)) begin // For hold violation with COMP
  flag_keep_match_low = `True;
  MATCHI = 1'b0;
  end
 else if (($realtime - recall_end_time) < ($realtime - comp_end_time)) // For hold violation with RECALL
  BlastCell(DataX);
end

always @(notif_bias1)            // BIAS1 violation
begin
 if  ( $realtime == recall_start_time )    // For setup violation with RECALL
  BlastCell(DataX);
 else if ( $realtime == comp_start_time ) begin   // For setup violation with COMP
  flag_keep_match_low = `True;
  MATCHI = 1'b0;
 end
 else if (($realtime - recall_end_time ) > ($realtime - comp_end_time)) begin // For hold violation with COMP
  flag_keep_match_low = `True;
  MATCHI = 1'b0;
  end
 else if (($realtime - recall_end_time) < ($realtime - comp_end_time)) // For hold violation with RECALL
  BlastCell(DataX);
end

always @(notif_mrcl0)            // MRCL0 violation
begin
 if  ( $realtime == recall_start_time )    // For setup violation with RECALL
  BlastCell(DataX);
 else if ( $realtime == comp_start_time ) begin   // For setup violation with COMP
  flag_keep_match_low = `True;
  MATCHI = 1'b0;
 end
 else if (($realtime - recall_end_time ) > ($realtime - comp_end_time)) begin // For hold violation with COMP
  flag_keep_match_low = `True;
  MATCHI = 1'b0;
  end
 else if (($realtime - recall_end_time) < ($realtime - comp_end_time)) // For hold violation with RECALL
  BlastCell(DataX);
end

always @(notif_mrcl1)            // MRCL1 violation
begin
 if  ( $realtime == recall_start_time )    // For setup violation with RECALL
  BlastCell(DataX);
 else if ( $realtime == comp_start_time ) begin   // For setup violation with COMP
  flag_keep_match_low = `True;
  MATCHI = 1'b0;
 end
 else if (($realtime - recall_end_time ) > ($realtime - comp_end_time)) begin // For hold violation with COMP
  flag_keep_match_low = `True;
  MATCHI = 1'b0;
  end
 else if (($realtime - recall_end_time) < ($realtime - comp_end_time)) // For hold violation with RECALL
  BlastCell(DataX);
end

always @(notif_tecc0)            // TECC0 violation
begin
 if  ( $realtime == recall_start_time )    // For setup violation with RECALL
  BlastCell(DataX);
 else if ( $realtime == comp_start_time ) begin   // For setup violation with COMP
  flag_keep_match_low = `True;
  MATCHI = 1'b0;
 end
 else if (($realtime - recall_end_time ) > ($realtime - comp_end_time)) begin // For hold violation with COMP
  flag_keep_match_low = `True;
  MATCHI = 1'b0;
  end
 else if (($realtime - recall_end_time) < ($realtime - comp_end_time)) // For hold violation with RECALL
  BlastCell(DataX);
end

always @(notif_tecc1)            // TECC1 violation
begin
 if  ( $realtime == recall_start_time )    // For setup violation with RECALL
  BlastCell(DataX);
 else if ( $realtime == comp_start_time ) begin   // For setup violation with COMP
  flag_keep_match_low = `True;
  MATCHI = 1'b0;
 end
 else if (($realtime - recall_end_time ) > ($realtime - comp_end_time)) begin // For hold violation with COMP
  flag_keep_match_low = `True;
  MATCHI = 1'b0;
  end
 else if (($realtime - recall_end_time) < ($realtime - comp_end_time)) // For hold violation with RECALL
  BlastCell(DataX);
end


always @(notif_recall)            // RECALL violation
begin
      BlastCell(DataX);
      BlastEarom;
      QI <= DataX;
      SOI <= 1'bx;
    flaga_read_ok = `False;

 end

always @(notif_store)            // STORE violation 
begin
      BlastEarom;
    flaga_read_ok = `False;
 end



always @(notif_vpp)            // pulse width violation of VPP
begin
      BlastEarom;
      disable STORE_OP;
end

always @(notif_sme)            // pin_name(sme,0) violation 
begin
      BlastCell(DataX);
      QI <= DataX;
    flaga_read_ok = `False;
      disable serial_blk;
      SOI <= 1'bx;
    flaga_serial_read_ok = `False;
      checkSanityOnAport;
 end


always @(notif_sclk)            // SCLK violation 
begin
      BlastCell(DataX);
    flaga_serial_read_ok = `False;
      QI <= DataX;
      SOI <= 1'bx;
      checkSanityOnAport;
 end


always @(notif_si)            // SI violation 
begin
      temp3 = memb[0];
      memb[0] = {temp3[bits-1:1],1'bx};
 end






always @(notif_clk_SCLK_rise_rec)            // RECOVERY between posedge SCLK and posedge CLK
begin
      QI <= DataX;
      BlastCell(DataX);
      SOI <= 1'bx;
    flaga_read_ok = `False;
    flaga_serial_read_ok = `False;
 end

always @(notif_sclk_CLK_rise_rec)            // RECOVERY between posedge CLK and posedge SCLK
begin
      BlastCell(DataX);
      SOI <= 1'bx;
      QI <= DataX;
    flaga_read_ok = `False;
    flaga_serial_read_ok = `False;
 end



always @(notif_clk_COMP_rise_rec)            // RECOVERY between posedge CLK and posedge COMP
begin
      BlastCell(DataX);
      BlastEarom;
      SOI <= 1'bx;
      QI <= DataX;

      MATCHI = 1'b0;
 end

always @(notif_clk_RECALL_rise_rec)            // RECOVERY between posedge CLK and posedge RECALL
begin
      BlastCell(DataX);
      BlastEarom;
      QI <= DataX;
      SOI <= 1'bx;
    flaga_serial_read_ok = `False;
    flaga_read_ok = `False;
 end

always @(notif_clk_STORE_rise_rec)            // RECOVERY between posedge CLK and posedge STORE
begin
      BlastEarom;
      BlastCell(DataX);
      QI <= DataX;
      SOI <= 1'bx;
      checkSanityOnAport;
    flaga_read_ok = `False;
 end

always @(notif_comp_CLK_rise_rec)            // RECOVERY between negedge COMP and posedge CLK
begin
      MATCHI = 1'b0;
      BlastEarom;
      BlastCell(DataX);
      QI <= DataX;
      SOI <= 1'bx;
    flaga_serial_read_ok = `False;
 end

always @(notif_store_CLK_rise_rec)            // RECOVERY between negedge STORE and posedge CLK
begin
      BlastEarom;
      BlastCell(DataX);
      QI <= DataX;
      SOI <= 1'bx;
    flaga_serial_read_ok = `False;
 end

always @(notif_recall_CLK_rise_rec)            // RECOVERY between RECALL and posedge CLK
begin
      BlastCell(DataX);
      BlastEarom;
      QI <= DataX;
      disable WriteArrayA.SERIAL_OUT;
      disable serial_blk;
      SOI <= 1'bx;
    flaga_serial_read_ok = `False;
    flaga_read_ok = `False;
 end



always @(notif_sclk_COMP_rise_rec)            // RECOVERY between posedge SCLK and posedge COMP
begin
      BlastCell(DataX);
      BlastEarom;
      MATCHI = 1'b0;
      SOI <= 1'bx;
 end

always @(notif_sclk_RECALL_rise_rec)            // RECOVERY between posedge SCLK and posedge RECALL
begin
      BlastCell(DataX);
      BlastEarom;
      QI <= DataX;
      flaga_read_ok = `False;
      SOI <= 1'bx;
      checkSanityOnAport;

 end

always @(notif_sclk_STORE_rise_rec)            // RECOVERY between posedge SCLK and negedge STORE
begin
    BlastEarom;
    BlastCell(DataX);
      QI <= DataX;
      flaga_read_ok = `False;
      SOI <= 1'bx;
      flaga_serial_read_ok = `False;
 end

always @(notif_comp_SCLK_rise_rec)            // RECOVERY between negedge COMP and posedge SCLK
begin
    MATCHI = 1'b0;
    BlastCell(DataX);
    BlastEarom;
      QI <= DataX;
      flaga_read_ok = `False;
      SOI <= 1'bx;
      flaga_serial_read_ok = `False;
 end

always @(notif_store_SCLK_rise_rec)            // RECOVERY between negedge STORE and posedge SCLK
begin
      BlastEarom;
      BlastCell(DataX);
      QI <= DataX;
      flaga_read_ok = `False;
      SOI <= 1'bx;
 end

always @(notif_recall_SCLK_rise_rec)            // RECOVERY between negedge RECALL and posedge SCLK
begin
      BlastCell(DataX);
      BlastEarom;
      QI <= DataX;
      flaga_read_ok = `False;
      SOI <= 1'bx;
 end


always @(notif_comp_RECALL_rise_rec)            // RECOVERY between COMP and RECALL
begin
    RCREADYI = 1'b0;
    rcready_viol_flag = 1'b1;
    disable RECALL_BLK;
    MATCHI = 1'b0;
      BlastEarom;
      BlastCell(DataX);
      QI <= DataX;
      SOI <= 1'bx;

      flaga_read_ok = `False;
 end

always @(notif_comp_STORE_rise_rec)            // RECOVERY between posedge COMP and posedge STORE
begin
      BlastEarom;
      BlastCell(DataX);
      flaga_read_ok = `False;
    MATCHI = 1'b0;
      SOI <= 1'bx;
 end


always @(notif_store_RECALL_rise_rec)            // RECOVERY between negedge STORE and posedge RECALL
begin
      BlastCell(DataX);
      BlastEarom;
      QI <= DataX;
      flaga_read_ok = `False;
      SOI <= 1'bx;
 end

always @(notif_store_COMP_rise_rec)            // RECOVERY between negedge STORE and posedge COMP
begin
      BlastCell(DataX);
      BlastEarom;
      MATCHI = 1'b0;
      SOI <= 1'bx;
 end

always @(notif_recall_STORE_rise_rec)            // RECOVERY between negedge RECALL and posedge STORE
begin
      BlastCell(DataX);
      BlastEarom;
      QI <= DataX;
      flaga_read_ok = `False;
      SOI <= 1'bx;
 end

always @(notif_recall_COMP_rise_rec)            // RECOVERY between negedge RECALL and posedge COMP
begin
    RCREADYI = 1'b0;
    rcready_viol_flag = 1'b1;
    disable COMP_BLK;
    MATCHI = 1'b0;
      BlastCell(DataX);
      BlastEarom;
      QI <= DataX;
      flaga_read_ok = `False;
 end

always @(notif_vpp_STORE_fall_rec)            // RECOVERY between negedge VPP and negedge STORE
begin
    $display("Trvpp violation.POSSIBLE CHIP DAMAGE!! ");
      BlastEarom;
      BlastCell(DataX);
      SOI <= 1'bx;
    flaga_read_ok = `False;
    end

always @(notif_store_VPP_rise_rec)            // RECOVERY between posedge VPP and posedge STORE
begin
    $display("Txvpp violation.POSSIBLE CHIP DAMAGE!! ");
      BlastEarom;
      BlastCell(DataX);
      SOI <= 1'bx;
    flaga_read_ok = `False;
    end




always @(notif_clk)            // CLK violation
 begin
  flaga_clk_valid = `False;
  flaga_output_ok = `False;
  flaga_adr_ok = `False;
  flaga_we_ok  = `False;
   QI <= DataX;
      SOI <= 1'bx;
  checkSanityOnAport;
  flaga_read_ok = `False;     
 end

always @(notif_d)             // D violation
 begin
  if ( $realtime == CLK_T )
   ME_chk = ME;
  else
   ME_chk = MElatched;
  if (ME_chk !== 1'b0)
   begin
    flaga_d_ok = `False;
    flaga_read_ok = `False;
    checkSanityOnAport;
      QI <= DataX;
     if ( ADRlatched == words - 1 && WElatched !== 1'b0) begin
      disable WriteArrayA.SERIAL_OUT;
      disable serial_blk;
      SOI <= 1'bx;
     end 
   end
 end

always @(notif_comp)             // COMP violation
 begin
      BlastEarom;
     MATCHI = 1'b0;
 end

always @(notif_we)            // WE violation
 begin
  if ( $realtime == CLK_T )
   ME_chk = ME;
  else
   ME_chk = MElatched;
  if (ME_chk !== 1'b0)
   begin
    flaga_we_ok = `False;
    flaga_output_ok = `False;
    flaga_read_ok = `False;
      QI <= DataX;
     if ( ADRlatched == words - 1 ) begin
      disable WriteArrayA.SERIAL_OUT;
      disable serial_blk;
      SOI <= 1'bx;
     end 
    checkSanityOnAport;
   end
 end

always @(notif_me)            // ME violation
 begin
  if ( $realtime == CLK_T )
   WE_chk = WE;
  else
   WE_chk = WElatched;
  if (WE_chk != 1'b0) begin
  flaga_adr_ok = `False;
  end
  flaga_read_ok = `False;     // irrespective of WE
  flaga_output_ok = `False;
  disable OUTPUT;
  QI <= DataX;
     if ( WE_chk !== 1'b0) begin
  SOI <= 1'bx;
     end 
  checkSanityOnAport;
 end

always @(notif_adr )           // ADR violation
 begin
  if ( $realtime == CLK_T )
   ME_chk = ME;
  else
   ME_chk = MElatched;
  if (ME_chk !== 1'b0)
   begin
    flaga_adr_ok = `False;
    flaga_read_ok = `False; // irrespective of WE
    flaga_output_ok = `False;
   QI <= DataX;
      SOI <= 1'bx;
    checkSanityOnAport;
   end
 end


// PORT FUNCTIONALITY
//---- Clock Negative Edge
always @( negedge CLK) begin
   if ( CLK !== 1'bx ) begin     //RESETTING FLAGS FOR NEXT CYCLE
   #0.01;
   flaga_range_ok  = `True;
   flaga_read_ok = `True;
   flaga_adr_viol = `True;
   flaga_clk_valid = `True;
   flaga_output_ok = `True;
  end
  else
   begin
    flaga_clk_valid = `False;
    corrupt_all_loc(`True);
   end
end
//---- Scan Clock Negative Edge
always @( negedge SCLK) begin
   SCLK_old <= SCLK;
   if ( SCLK_old ===1'b1 && SCLK===1'bx) begin
      if( MES_ALL=="ON" ) begin 
        $display("<<SCLK unknown>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end 
      BlastCell(DataX);
      QI = DataX;
      SOI <= 1'bx;
   end
   else 
    begin
   flaga_serial_read_ok = `True;
   flaga_sclk_valid = `True;
    end
end

//---- Scan Clock Positive Edge
always @( posedge SCLK) begin
  #0
   SCLK_old <= SCLK;
// Scan Clock 0-X
   if ( SCLK===1'bx) begin
      if( MES_ALL=="ON" && $realtime != 0) begin
        $display("<<SCLK unknown>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end
      BlastCell(DataX);
      QI = DataX;
      SOI <= 1'bx;
   end
// Scan Clock X-1
   else if ( SCLK_old ===1'bx) begin
      QI = DataX;
      SOI <= 1'bx;
   end
   else begin
     SMElatched = SME;
      if ( SME == 1'b1 ) begin
       if ( RECALL == 1'b0 && STORE == 1'b0 && COMP == 1'b0 ) begin : serial_blk
         if ( store_ctr != 0) begin
           if ( store_ctr < store_success_count-1) begin
             $display("Attempt to Write was made in the middle of a store operation from serial port , corrupting EAROM. time = %t",$realtime);
             BlastEarom;
           end
           else begin
             store_ctr = 0;
           end
         end

        for ( i = words-1; i>0; i = i-1 ) begin
         temp1 = memb[i] << 1;
         temp2 = memb[i-1];
         memb[i] = {temp1[bits-1:1],temp2[bits-1]};
        end
        temp1 = memb[0] << 1;
        memb[0] = {temp1[bits-1:1],SI};
        SOI <= 1'bx;
        #0.01
        temp1 = memb[words-1];
        SOI = temp1[bits-1];
       end
       else begin
          if ( RECALL !== 1'b0 && SME == 1'b1) begin
            if( MES_ALL=="ON" && $realtime != 0) begin
              $display("<<RECALL non-zero at postive edge of SCLK>>");
              $display("      time=%t; instance=%m (NVM1H)",$realtime);
            end
            BlastCell(DataX);
            BlastEarom;
            SOI <= 1'bx;


          end
          if ( STORE !== 1'b0 && SME == 1'b1) begin
            if( MES_ALL=="ON" && $realtime != 0) begin
              $display("<<STORE non-zero at postive edge of SCLK>>");
              $display("      time=%t; instance=%m (NVM1H)",$realtime);
            end
            BlastEarom;
            BlastCell(DataX);
            SOI <= 1'bx;
          end
          if ( COMP !== 1'b0 && SME == 1'b1) begin
            if( MES_ALL=="ON" && $realtime != 0) begin
              $display("<<COMP non-zero at postive edge of SCLK >>");
              $display("      time=%t; instance=%m (NVM1H)",$realtime);
            end
            BlastCell(DataX);
            BlastEarom;
            SOI <= 1'bx;
            MATCHI = 1'b0;
          end
        end
      end
      else if ( SME === 1'bx ) begin
        BlastCell(DataX);
        SOI <= 1'bx;
        if ( STORE !== 1'b0 ) begin
          if( MES_ALL=="ON" && $realtime != 0) begin
            $display("<<STORE non-zero at postive edge of SCLK>>");
            $display("      time=%t; instance=%m (NVM1H)",$realtime);
          end
          BlastEarom;
        end
      end
   end
end
assign SO = SOI;


always @( BIAS0 )
 begin
   if ( RECALL !== 1'b0  ) 
    BlastCell(DataX);
    else if ( COMP !== 1'b0 ) begin 
     flag_keep_match_low = `True;
     MATCHI = 1'b0;
    end
 end

always @( BIAS1 )
 begin
   if ( RECALL !== 1'b0  ) 
    BlastCell(DataX);
    else if ( COMP !== 1'b0 ) begin 
     flag_keep_match_low = `True;
     MATCHI = 1'b0;
    end
 end

always @( TECC0 )
 begin
   if ( RECALL !== 1'b0  ) 
    BlastCell(DataX);
    else if ( COMP !== 1'b0 ) begin 
     flag_keep_match_low = `True;
     MATCHI = 1'b0;
    end
 end
always @( TECC1 )
 begin
   if ( RECALL !== 1'b0  ) 
    BlastCell(DataX);
    else if ( COMP !== 1'b0 ) begin 
     flag_keep_match_low = `True;
     MATCHI = 1'b0;
    end
 end

always @( MRCL0 )
 begin
   if ( RECALL !== 1'b0  ) 
    BlastCell(DataX);
    else if ( COMP !== 1'b0 ) begin 
     flag_keep_match_low = `True;
     MATCHI = 1'b0;
    end
 end
always @( MRCL1 )
 begin
   if ( RECALL !== 1'b0  ) 
    BlastCell(DataX);
    else if ( COMP !== 1'b0 ) begin 
     flag_keep_match_low = `True;
     MATCHI = 1'b0;
    end
 end

always @( negedge CLK or WE )
 begin
   if ( CLK == 1'b0 )
     WE_old = WE;
 end

always @( negedge CLK or ME )
 begin
   if ( CLK == 1'b0 )
     ME_old = ME;
 end

always @( negedge CLK or ADR )
 begin
   if ( CLK == 1'b0 )
     ADR_old = ADR;
 end

always @( negedge CLK or D )
 begin
   if ( CLK == 1'b0 )
     D_old = D;
 end


task WriteArrayA;
begin
  if ( (ADRlatched ^ ADRlatched) !== 0 ) begin
     BlastCell(DataX);
     if( MES_ALL=="ON" && $realtime != 0) begin
       $display("<<ADR unknown>>");
       $display("      time=%t; instance=%m (NVM1H)",$realtime);
     end
        QI = DataX;
        SOI = 1'bx;
  end
  else if ( ADRlatched < words ) begin
     memb[ADRlatched] = Dlatched;
      QI = Dlatched;
     if ( ADRlatched == words - 1 ) begin : SERIAL_OUT
        SOI <= 1'bx;
        #0.01
       SOI = Dlatched[bits-1];
     end
  end
  else if( MES_ALL=="ON" && $realtime != 0) begin
     $display("<<WARNING:address is out of range\n RANGE:0 to 63>>\n");
     $display("      time=%t; instance=%m (NVM1H)",$realtime);
        QI = Dlatched;
  end
end
endtask

task WriteFaultA;
begin
  if ( (ADRlatched ^ ADRlatched) !== 0 ) begin
     BlastCell(DataX);
  end
  else if ( ADRlatched < words ) begin
     memb[ADRlatched] = DataX;
  end

  else if( MES_ALL=="ON" && $realtime != 0) begin
     $display("<<%m WARNING:address is out of range\n RANGE:0 to 63>>\n");
  end
   QI = DataX;
end
endtask


//---- RECALL Negative Edge
always @( negedge RECALL) begin
   recall_end_time = $realtime ;
   if ( RECALL === 1'b0 && rcready_viol_flag !== 1'b1 ) RCREADYI <= RECALL;
    rcready_viol_flag = 1'b0;
   RECALL_old <= RECALL;
   if ( RECALL_old ===1'b1 && RECALL===1'bx) begin
      if( MES_ALL=="ON" ) begin 
        $display("<<RECALL unknown>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end 
      BlastCell(DataX);
      BlastEarom;
      QI <= DataX;
      SOI <= 1'bx;
   end
end

//---- RECALL Positive Edge
always @( posedge RECALL) begin : RECALL_BLK
   recall_start_time = $realtime ;
  if ( RECALL === 1'b1 && rcready_viol_flag !== 1'b1 ) RCREADYI <= RECALL;
    rcready_viol_flag = 1'b0;
   RECALL_old <= RECALL;
// RECALL 0-X
   if ( RECALL===1'bx) begin
      if( MES_ALL=="ON" && $realtime != 0) begin
        $display("<<RECALL unknown>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end
      BlastCell(DataX);
      BlastEarom;
      QI <= DataX;
      SOI <= 1'bx;
   end
// RECALL X-1
   else if ( RECALL_old ===1'bx) begin
      QI <= DataX;
      SOI <= 1'bx;
   end
   else if ( COMP != 1'b0) begin
      BlastCell(DataX);
      BlastEarom;
      MATCHI = 1'b0;
      SOI <= 1'bx;
   end
   else begin
      for ( i = words-1; i>=0; i = i-1 ) begin
        memb[i] = earom[i]; 
      end
      temp1 = memb[words-1];
      SOI <= temp1[bits-1];
   end
end

task store;
  begin
    for ( i = words-1; i>=0; i = i-1 ) begin
      earom[i] = memb[i]; 
    end
  end
endtask

task recall;
  begin
     if (store_ctr != 0) begin
      store_ctr = 0;
     end
    for ( i = words-1; i>=0; i = i-1 ) begin
      memb[i] = earom[i]; 
    end
  end
endtask

reg store_start;
reg vpp_start;
reg vpp_end;
//---- STORE Negative Edge
always @( negedge STORE) begin
   STORE_old <= STORE;
// STORE 1-X
   if ( STORE_old ===1'b1 && STORE===1'bx) begin
      if( MES_ALL=="ON" ) begin 
        $display("<<STORE unknown>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end 
      BlastEarom;
   end
   else if ( STORE_old ===1'bx) begin
   end
   else begin
      if ( store_start == 1'b1 && vpp_start == 1'b1 && vpp_end == 1'b1 ) begin
         store_start = 1'b0;
         vpp_start = 1'b0;
         vpp_end = 1'b0;
      end
      else begin
          BlastEarom;
        if( MES_ALL=="ON" ) begin 
          $display("<<STORE AND VPP Sequence Wrong>>");
          $display("      time=%t; instance=%m (NVM1H)",$realtime);
        end 
      end
   end
end

//---- STORE Positive Edge
always @( posedge STORE) begin
  STORE_old <= STORE;
// STORE 0-X
    if ( STORE===1'bx) begin
      if( MES_ALL=="ON" && $realtime != 0) begin
        $display("<<STORE unknown>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end
      BlastEarom;
    end
// STORE X-1
    else if ( STORE_old ===1'bx) begin
     store_ctr = 0;
    end
    else if (RECALL == 1'b1) begin
      BlastEarom;
      BlastCell(DataX);
      QI <= DataX;
      SOI <= 1'bx;
    end
    else if (COMP == 1'b1) begin
      BlastEarom;
      BlastCell(DataX);
      QI <= DataX;
      MATCHI = 1'b0;
      SOI <= 1'bx;
    end
    else begin
      store_start = 1'b1;
    end
end

//---- VPP Negative Edge
always @( negedge VPP) begin
  VPP_old <= VPP;
// VPP 1-X
    if ( VPP_old ===1'b1 && VPP===1'bx) begin
      if( MES_ALL=="ON" ) begin 
        $display("<<VPP unknown>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end 
      BlastEarom;
    end
    else if ( VPP_old ===1'bx) begin
    end
    else begin
      if ( store_start == 1'b1 && vpp_start == 1'b1 ) begin : STORE_OP
        vpp_end = 1;
        if ( store_ctr >= store_success_count  - 1) begin
          store;
          store_ctr = store_ctr + 1;
        end
        else begin 
          store_ctr = store_ctr + 1;
          store_ctr_buf = store_ctr;
          BlastEarom;
          store_ctr = store_ctr_buf;
        end
      end
      else begin
        BlastEarom;
        if( MES_ALL=="ON" ) begin 
          $display("<<STORE AND VPP Sequence Wrong>>");
          $display("      time=%t; instance=%m (NVM1H)",$realtime);
        end 
      end
    end
end

//---- VPP Positive Edge
always @( posedge VPP) begin
   VPP_old <= VPP;
      if ( STORE == 1'b0) begin
    $display("VPP is not low when STORE is low.POSSIBLE CHIP DAMAGE!!.Exiting simulation. ");
    $finish;
      end
// VPP 0-X
   else if ( VPP===1'bx) begin
      if( MES_ALL=="ON" && $realtime != 0) begin
        $display("<<VPP unknown>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end
      BlastEarom;
      vpp_start = 0;
      vpp_end = 0;
   end
// VPP X-1
   else if ( VPP_old ===1'bx) begin
      vpp_start = 0;
      vpp_end = 0;
   end
   else if ( store_start == 1'b1 ) begin
      vpp_start = 1;
      vpp_end = 0;
   end
   else begin
      vpp_start = 0;
      vpp_end = 0;
      if( MES_ALL=="ON" && $realtime != 0) begin
        $display("<<VPP is ON, but STORE is OFF>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end
      if ( STORE == 1'b0) begin
       BlastCell(DataX);
      end
      BlastEarom;
   end
end

reg temp_comp;
reg COMP_old;

//---- Compare operation between EAROM & SRAM
always @( negedge COMP) begin
   if ( COMP === 1'b0 && rcready_viol_flag !== 1'b1 ) RCREADYI <= COMP;
    rcready_viol_flag = 1'b0;
   comp_end_time = $realtime ;
   COMP_old <= COMP;
   flag_keep_match_low = `False;
   if ( COMP_old ===1'b1 && COMP===1'bx) begin
      if( MES_ALL=="ON" ) begin 
        $display("<<COMP unknown>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end 
      BlastEarom;
      MATCHI = 1'b0;
   end
   else
      MATCHI = 1'b0;
end
//---- COMP Positive Edge
always @( posedge COMP) begin : COMP_BLK
   if ( COMP === 1'b1  && rcready_viol_flag !== 1'b1 ) RCREADYI <= COMP;
    rcready_viol_flag = 1'b0;
   comp_start_time = $realtime ;
   COMP_old <= COMP;
// COMP 0-X
   if ( COMP===1'bx) begin
      if( MES_ALL=="ON" && $realtime != 0) begin
        $display("<<COMP unknown>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end
      BlastEarom;
      MATCHI = 1'b0;
   end
// COMP X-1
   else if ( COMP_old ===1'bx) begin
   end
    else if (RECALL == 1'b1) begin
      BlastEarom;
      BlastCell(DataX);
      QI <= DataX;
      MATCHI = 1'b0;
      SOI <= 1'bx;
    end

   else if ( STORE != 1'b0) begin
      BlastCell(DataX);
      BlastEarom;
      MATCHI = 1'b0;
      SOI <= 1'bx;
   end
   else if ( flag_keep_match_low ) begin 
    MATCHI = 1'b0;
   end
   else begin
      temp_comp = 1'b1;
      for ( i = 0; i<words; i = i+1 ) begin
        temp_comp = temp_comp&(&(~(earom[i] ^ memb[i]))); 
        if ( temp_comp == 1'b0 ) i = words;
      end
        if ( temp_comp === 1'bx ) begin
          MATCHI = 1'b0;
        end
        else begin
          MATCHI = temp_comp;
        end
   end
end

assign MATCH = (flag_keep_match_low?0:MATCHI);
assign RCREADY = RCREADYI;
//---- Clock Negative Edge
always @( negedge CLK) begin
   CLK_old <= CLK;
   if ( CLK_old ===1'b1 && CLK===1'bx) begin
      if( MES_ALL=="ON" ) begin 
        $display("<<CLK unknown>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end 
      BlastCell(DataX);
      QI <= DataX;
     SOI <= 1'bx;
   end
end


always @( posedge CLK )
 begin
  #0
  CLK_T = $realtime ;
  flaga_adr_ok  = `True;
   flaga_we_ok   = `True;
   flaga_d_ok    = `True;

  if ( RECALL == 1'b0  &&  flaga_clk_valid ) begin
   CLK_old <= CLK;
// Clock 0-X
   if ( CLK===1'bx) begin
      if( MES_ALL=="ON" && $realtime != 0) begin
        $display("<<CLK unknown>>");
        $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end
      BlastCell(DataX);
      QI <= DataX;
     SOI <= 1'bx;
   end

// Clock X-1
   else if ( CLK_old ===1'bx) begin
      QI <= DataX;
     SOI <= 1'bx;
   end
   else if ( STORE !== 1'b0 && ME !== 1'b0) begin
     if( MES_ALL=="ON" && $realtime != 0) begin
       $display("<<STORE non-zero at postive edge of CLK>>");
       $display("      time=%t; instance=%m (NVM1H)",$realtime);
     end
     BlastCell(DataX);
     BlastEarom;
     QI <= DataX;
     SOI <= 1'bx;
   end
   else if ( COMP !== 1'b0 && ME !== 1'b0) begin
     if( MES_ALL=="ON" && $realtime != 0) begin
       $display("<<COMP non-zero at postive edge of CLK >>");
       $display("      time=%t; instance=%m (NVM1H)",$realtime);
     end
     BlastCell(DataX);
     BlastEarom;
     QI <= DataX;
     SOI <= 1'bx;
      MATCHI = 1'b0;
   end

// ---- Normal Mode
   else begin : OUTPUT
   #0
     WElatched = WE_old;
     MElatched = ME_old;
     ADRlatched = ADR_old;
     Dlatched = D_old;
     if ( MElatched == 1'b1 ) begin
        if ( WElatched !== 1'b0 &&  flaga_read_ok && flaga_we_ok  &&  flaga_adr_ok &&  flaga_d_ok) begin // Write operation
         if ( store_ctr != 0) begin
           if ( store_ctr < store_success_count-1) begin
             $display("Attempt to Write was made in the middle of a store operation from parallel port, corrupting EAROM. time = %t",$realtime);
             BlastEarom;
           end
           else begin
             store_ctr = 0;
           end
         end
          if ( WElatched == 1'b1 ) begin
             WriteArrayA;
          end
          else begin
             if( MES_ALL=="ON" && $realtime != 0 ) begin
               $display("<<WE unknown>>");
               $display("      time=%t; instance=%m (NVM1H)",$realtime);
             end
             WriteFaultA;
            if ( ADRlatched == words - 1) begin
                SOI <= 1'bx;
            end
          end
        end // End of Write operation
        else begin // Valid read operation
          if ( WElatched == 1'b0 &&  flaga_read_ok &&  flaga_output_ok &&  flaga_adr_ok) begin 
            if ( (ADRlatched ^ ADRlatched) !== 0 ) begin
              if( MES_ALL=="ON" && $realtime != 0) begin
                $display("<<ADR unknown>>");
                $display("      time=%t; instance=%m (NVM1H)",$realtime);
              end
              BlastCell(DataX);
              BlastEarom;
              QI <= DataX;
              SOI <= 1'bx;
            end
            else if ( ADRlatched < words ) begin
              QI <= DataX;
              #0.01
              QI <= memb[ADRlatched];
            end
            else begin
              if( MES_ALL=="ON" && $realtime != 0) begin
                $display("<<WARNING:address is out of range\n RANGE:0 to 63>>\n");
                $display("      time=%t; instance=%m (NVM1H)",$realtime);
              end
              QI <= DataX;
              flaga_read_ok = `True;
              flaga_output_ok = `True;
            end
          end
          else begin
              QI <= DataX;
              flaga_read_ok = `True;
              flaga_output_ok = `True;
          end
        end // End of Read operation
      end // MElatched = 1'b1
      else if ( MElatched === 1'bx ) begin
        if( MES_ALL=="ON" && $realtime != 0 ) begin
          $display("<<ME unknown>>");
          $display("      time=%t; instance=%m (NVM1H)",$realtime);
        end
        if ( WElatched !== 1'b0 ) begin
              SOI <= 1'bx;
          QI <= DataX;
          BlastCell(DataX);
        end
        else
          QI <= DataX;
      end // MElatched = 1'bx
    end
   end
   else if ( RECALL !== 1'b0 && ME !== 1'b0 && WE !== 1'b0) begin
     if( MES_ALL=="ON" && $realtime != 0) begin
       $display("<<RECALL non-zero at postive edge of CLK >>");
       $display("      time=%t; instance=%m (NVM1H)",$realtime);
     end
     BlastCell(DataX);
     BlastEarom;
     QI <= DataX;
     SOI <= 1'bx;
   end

 end


always @( OE or QI )
begin
   if ( OE ) begin
     Q <= QI;
   end
   else if ( !OE ) begin
      Q <= DataZ;
   end
   else begin
      if( MES_ALL=="ON" && $realtime != 0 ) begin
         $display("<<OE unknown>>");
         $display("      time=%t; instance=%m (NVM1H)",$realtime);
      end
      Q <= DataX;
   end
end



endmodule
`endcelldefine
