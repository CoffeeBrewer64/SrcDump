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
// $Id: cvvalidpix.v,v 1.1 2002/05/21 23:55:43 berndt Exp $

   /////////////////////////////////////////////////////////////////////////
   //
   // Project Reality
   //
   // module:      cvvalidpix
   // description: generate one bit indicating if the current pixel
   // 	       	     is valid or not.  Active high.
   //
   // designer:    Mike M. Cai	 6/16/94
   //
   /////////////////////////////////////////////////////////////////////////


module cvvalidpix(   // output
      	       	     valid_pixel, 
		     // inputs
		     valid_pixel_m,
		     new_span, reset, gclk); 
output 	    valid_pixel;
input 	    valid_pixel_m;
input 	    new_span, reset, gclk;

reg   	    s1, s0;
reg   	    valid_pixel;

always @(posedge gclk or negedge reset)
   if ( reset == 1'h0)
      begin
      	 s1 <= 1'h0;
	 s0 <= 1'h0;
      end
  else  begin
      s1    <= ~new_span & ( s1 | (~valid_pixel_m & s0));
      s0    <= ~new_span & valid_pixel_m & ~s1;
      valid_pixel <= s1 ? 1'h0 : valid_pixel_m;
   end

endmodule  //  cvvalidpix
