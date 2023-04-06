/*
*************************************************************************
*									*
*               Copyright (C) 1994, Silicon Graphics, Inc.		*
*									*
*  These coded instructions, statements, and computer programs  contain	*
*  unpublished  proprietary  information of Silicon Graphics, Inc., and	*
*  are protected by Federal copyright  law.  They  may not be disclosed	*
*  to  third  parties  or copied or duplicated in any form, in whole or	*
*  in part, without the prior written consent of Silicon Graphics, Inc.	*
*									*
*************************************************************************
*/

// $Id: div_clkgen.v,v 1.1 2002/05/21 23:55:45 berndt Exp $

module div_clkgen(CLK, RunClk, ROMCLK);

input CLK;				// Clock input
input RunClk;			        // NOP
output ROMCLK;			        // Clock to ROM	

/**********************************************************
 * ROM CLOCK Generator
 *********************************************************/
wire RunClk;
wire RunClkB1;
wire RunClkB2;
wire RunClkLat;
wire RunClkLatB1;
wire RunClkLatB2;

ni01d1	u1(.z(RunClkB1), .i(RunClk));
ni01d1	u2(.z(RunClkB2), .i(RunClkB1));

lanfnb  u3(.q(RunClkLat),.d(RunClkB2), .en(CLK));

ni01d1	u4(.z(RunClkLatB1), .i(RunClkLat));
ni01d1	u5(.z(RunClkLatB2), .i(RunClkLatB1));

an02d2  u6(.z(ROMCLK), .a1(CLK), .a2(RunClkLatB2));

endmodule//div_clkgen
