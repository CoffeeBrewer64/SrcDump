/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1994, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/
// $Id: dmemx2.v,v 1.1 2002/05/21 23:55:43 berndt Exp $

// dmemx2: two dmem's, side-by-side

`timescale 1ns / 10ps

module dmemx2(clk, df_chip_sel_l, df_wen_l, df_addr_low, df_addr_high, 
	df_datain, dmem_dataout);

   input		clk;
   input		df_chip_sel_l;
   input	[15:0]	df_wen_l;
   input	[11:4]	df_addr_low;
   input	[11:4]	df_addr_high;
   input	[127:0]	df_datain;

   output	[127:0]	dmem_dataout;


   dmem dmemLow(
        .di	 		(df_datain[63:0]),
        .a	 		(df_addr_low[11:4]),
        .csb	 		(df_chip_sel_l),
        .pcg 			(clk),
        .web	 		(df_wen_l[7:0]),
        .dout	 		(dmem_dataout[63:0])
   );

   dmem dmemHigh(
        .di	 		(df_datain[127:64]),
        .a	 		(df_addr_high[11:4]),
        .csb	 		(df_chip_sel_l),
        .pcg 			(clk),
        .web	 		(df_wen_l[15:8]),
        .dout	 		(dmem_dataout[127:64])
   );

endmodule
