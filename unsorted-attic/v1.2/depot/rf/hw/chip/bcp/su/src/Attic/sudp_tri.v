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

/*
*************************************************************************
*									*
*  Project Reality							*
*									*
*  module:	sudp_tri.v						*
*  description:	32 bit tri-state buffer using nt01d5 cells		*
*									*
*  designer:	Phil Gossett						*
*  date:	4/7/95							*
*									*
*************************************************************************
*/

// $Id: sudp_tri.v,v 1.1 2002/05/21 23:55:44 berndt Exp $

module sudp_tri (i, en, z);

input [31:0] i;
input en;

output [31:0] z;

wire enba;
wire enbb;
wire enbc;
wire enbd;

ni01d5 gbufa  (.z(enba), .i(en));
ni01d5 gbufb  (.z(enbb), .i(en));
ni01d5 gbufc  (.z(enbc), .i(en));
ni01d5 gbufd  (.z(enbd), .i(en));

nt01d5 gtri0  (.z(z[0]),  .oe(enba), .i(i[0]));
nt01d5 gtri1  (.z(z[1]),  .oe(enba), .i(i[1]));
nt01d5 gtri2  (.z(z[2]),  .oe(enba), .i(i[2]));
nt01d5 gtri3  (.z(z[3]),  .oe(enba), .i(i[3]));
nt01d5 gtri4  (.z(z[4]),  .oe(enba), .i(i[4]));
nt01d5 gtri5  (.z(z[5]),  .oe(enba), .i(i[5]));
nt01d5 gtri6  (.z(z[6]),  .oe(enba), .i(i[6]));
nt01d5 gtri7  (.z(z[7]),  .oe(enba), .i(i[7]));
nt01d5 gtri8  (.z(z[8]),  .oe(enbb), .i(i[8]));
nt01d5 gtri9  (.z(z[9]),  .oe(enbb), .i(i[9]));
nt01d5 gtri10 (.z(z[10]), .oe(enbb), .i(i[10]));
nt01d5 gtri11 (.z(z[11]), .oe(enbb), .i(i[11]));
nt01d5 gtri12 (.z(z[12]), .oe(enbb), .i(i[12]));
nt01d5 gtri13 (.z(z[13]), .oe(enbb), .i(i[13]));
nt01d5 gtri14 (.z(z[14]), .oe(enbb), .i(i[14]));
nt01d5 gtri15 (.z(z[15]), .oe(enbb), .i(i[15]));
nt01d5 gtri16 (.z(z[16]), .oe(enbc), .i(i[16]));
nt01d5 gtri17 (.z(z[17]), .oe(enbc), .i(i[17]));
nt01d5 gtri18 (.z(z[18]), .oe(enbc), .i(i[18]));
nt01d5 gtri19 (.z(z[19]), .oe(enbc), .i(i[19]));
nt01d5 gtri20 (.z(z[20]), .oe(enbc), .i(i[20]));
nt01d5 gtri21 (.z(z[21]), .oe(enbc), .i(i[21]));
nt01d5 gtri22 (.z(z[22]), .oe(enbc), .i(i[22]));
nt01d5 gtri23 (.z(z[23]), .oe(enbc), .i(i[23]));
nt01d5 gtri24 (.z(z[24]), .oe(enbd), .i(i[24]));
nt01d5 gtri25 (.z(z[25]), .oe(enbd), .i(i[25]));
nt01d5 gtri26 (.z(z[26]), .oe(enbd), .i(i[26]));
nt01d5 gtri27 (.z(z[27]), .oe(enbd), .i(i[27]));
nt01d5 gtri28 (.z(z[28]), .oe(enbd), .i(i[28]));
nt01d5 gtri29 (.z(z[29]), .oe(enbd), .i(i[29]));
nt01d5 gtri30 (.z(z[30]), .oe(enbd), .i(i[30]));
nt01d5 gtri31 (.z(z[31]), .oe(enbd), .i(i[31]));

endmodule  //  sudp_tri


