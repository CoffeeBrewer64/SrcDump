//  version: 0.0.5 date  8.sep.1994 series sgi_custom/uc1  voltage 3.3v
//  register file: iobuf: 16words*64bits: single port
//
//  copyright  (c) nec corporation 1994
//
//  for logic only verilog
//      ^^^^^^^^^^
//

`define functional
 

`timescale 10ps/10ps    //1unit = 0.01ns
`celldefine

`ifdef verifault
    `suppress_faults
    `enable_portfaults
`endif

module iobuf (
		wen,		// in write enable
		clk,		// in clock input
		a,		// in address input
		di,		// in data input
		dout		// ot data output
		);

/****************************************************************/
/*    parameter //// define bit and address pin number          */
/*              bit_num = 64,           // number of databit    */
/*              adr_num = 4;           // number of address    */
/****************************************************************/

	input	wen;
	input	clk;
	input	[3:0] a;
	input	[63:0] di;
	output	[63:0] dout;

		wire	[3:0] a;
		wire	[63:0] di;
		wire	[63:0] dout;

		wire [3:0] _a;
		wire [3:0] _an;
		wire [63:0] _di;
		wire [63:0] _din;
		reg [63:0] out1r;
		reg [63:0] out1io;
		reg [63:0] out1wo;
		wire [63:0] out1;
		wire [63:0] rd_do, wo_do, io_do;
		wire n_write ;
		reg  _st1, _st2, notif_w ;


/****************************************************************/
	parameter 
//     
		tra	 = 400 ,  // ra -> do tpd ( read access time )
		two	 = 400 ,  // clk -> do tpd ( clk fall edge to output ) 
		tio	 = 500 ;  // di   -> do tpd ( data input to output )



/****************************************************************/
// control signal select

buf (_wen,wen);
buf (_clk,clk);


// input data signal select

buf (_din[0],di[0]);
buf (_din[1],di[1]);
buf (_din[2],di[2]);
buf (_din[3],di[3]);
buf (_din[4],di[4]);
buf (_din[5],di[5]);
buf (_din[6],di[6]);
buf (_din[7],di[7]);
buf (_din[8],di[8]);
buf (_din[9],di[9]);
buf (_din[10],di[10]);
buf (_din[11],di[11]);
buf (_din[12],di[12]);
buf (_din[13],di[13]);
buf (_din[14],di[14]);
buf (_din[15],di[15]);
buf (_din[16],di[16]);
buf (_din[17],di[17]);
buf (_din[18],di[18]);
buf (_din[19],di[19]);
buf (_din[20],di[20]);
buf (_din[21],di[21]);
buf (_din[22],di[22]);
buf (_din[23],di[23]);
buf (_din[24],di[24]);
buf (_din[25],di[25]);
buf (_din[26],di[26]);
buf (_din[27],di[27]);
buf (_din[28],di[28]);
buf (_din[29],di[29]);
buf (_din[30],di[30]);
buf (_din[31],di[31]);
buf (_din[32],di[32]);
buf (_din[33],di[33]);
buf (_din[34],di[34]);
buf (_din[35],di[35]);
buf (_din[36],di[36]);
buf (_din[37],di[37]);
buf (_din[38],di[38]);
buf (_din[39],di[39]);
buf (_din[40],di[40]);
buf (_din[41],di[41]);
buf (_din[42],di[42]);
buf (_din[43],di[43]);
buf (_din[44],di[44]);
buf (_din[45],di[45]);
buf (_din[46],di[46]);
buf (_din[47],di[47]);
buf (_din[48],di[48]);
buf (_din[49],di[49]);
buf (_din[50],di[50]);
buf (_din[51],di[51]);
buf (_din[52],di[52]);
buf (_din[53],di[53]);
buf (_din[54],di[54]);
buf (_din[55],di[55]);
buf (_din[56],di[56]);
buf (_din[57],di[57]);
buf (_din[58],di[58]);
buf (_din[59],di[59]);
buf (_din[60],di[60]);
buf (_din[61],di[61]);
buf (_din[62],di[62]);
buf (_din[63],di[63]);


// address signal select

buf (_an[0],a[0]);
buf (_an[1],a[1]);
buf (_an[2],a[2]);
buf (_an[3],a[3]);


// output data signal select

buf (dout[0],out1[0]);
buf (dout[1],out1[1]);
buf (dout[2],out1[2]);
buf (dout[3],out1[3]);
buf (dout[4],out1[4]);
buf (dout[5],out1[5]);
buf (dout[6],out1[6]);
buf (dout[7],out1[7]);
buf (dout[8],out1[8]);
buf (dout[9],out1[9]);
buf (dout[10],out1[10]);
buf (dout[11],out1[11]);
buf (dout[12],out1[12]);
buf (dout[13],out1[13]);
buf (dout[14],out1[14]);
buf (dout[15],out1[15]);
buf (dout[16],out1[16]);
buf (dout[17],out1[17]);
buf (dout[18],out1[18]);
buf (dout[19],out1[19]);
buf (dout[20],out1[20]);
buf (dout[21],out1[21]);
buf (dout[22],out1[22]);
buf (dout[23],out1[23]);
buf (dout[24],out1[24]);
buf (dout[25],out1[25]);
buf (dout[26],out1[26]);
buf (dout[27],out1[27]);
buf (dout[28],out1[28]);
buf (dout[29],out1[29]);
buf (dout[30],out1[30]);
buf (dout[31],out1[31]);
buf (dout[32],out1[32]);
buf (dout[33],out1[33]);
buf (dout[34],out1[34]);
buf (dout[35],out1[35]);
buf (dout[36],out1[36]);
buf (dout[37],out1[37]);
buf (dout[38],out1[38]);
buf (dout[39],out1[39]);
buf (dout[40],out1[40]);
buf (dout[41],out1[41]);
buf (dout[42],out1[42]);
buf (dout[43],out1[43]);
buf (dout[44],out1[44]);
buf (dout[45],out1[45]);
buf (dout[46],out1[46]);
buf (dout[47],out1[47]);
buf (dout[48],out1[48]);
buf (dout[49],out1[49]);
buf (dout[50],out1[50]);
buf (dout[51],out1[51]);
buf (dout[52],out1[52]);
buf (dout[53],out1[53]);
buf (dout[54],out1[54]);
buf (dout[55],out1[55]);
buf (dout[56],out1[56]);
buf (dout[57],out1[57]);
buf (dout[58],out1[58]);
buf (dout[59],out1[59]);
buf (dout[60],out1[60]);
buf (dout[61],out1[61]);
buf (dout[62],out1[62]);
buf (dout[63],out1[63]);

/****************************************************************/
bufif1 (_di[0],_din[0],_wen);
bufif1 (_di[1],_din[1],_wen);
bufif1 (_di[2],_din[2],_wen);
bufif1 (_di[3],_din[3],_wen);
bufif1 (_di[4],_din[4],_wen);
bufif1 (_di[5],_din[5],_wen);
bufif1 (_di[6],_din[6],_wen);
bufif1 (_di[7],_din[7],_wen);
bufif1 (_di[8],_din[8],_wen);
bufif1 (_di[9],_din[9],_wen);
bufif1 (_di[10],_din[10],_wen);
bufif1 (_di[11],_din[11],_wen);
bufif1 (_di[12],_din[12],_wen);
bufif1 (_di[13],_din[13],_wen);
bufif1 (_di[14],_din[14],_wen);
bufif1 (_di[15],_din[15],_wen);
bufif1 (_di[16],_din[16],_wen);
bufif1 (_di[17],_din[17],_wen);
bufif1 (_di[18],_din[18],_wen);
bufif1 (_di[19],_din[19],_wen);
bufif1 (_di[20],_din[20],_wen);
bufif1 (_di[21],_din[21],_wen);
bufif1 (_di[22],_din[22],_wen);
bufif1 (_di[23],_din[23],_wen);
bufif1 (_di[24],_din[24],_wen);
bufif1 (_di[25],_din[25],_wen);
bufif1 (_di[26],_din[26],_wen);
bufif1 (_di[27],_din[27],_wen);
bufif1 (_di[28],_din[28],_wen);
bufif1 (_di[29],_din[29],_wen);
bufif1 (_di[30],_din[30],_wen);
bufif1 (_di[31],_din[31],_wen);
bufif1 (_di[32],_din[32],_wen);
bufif1 (_di[33],_din[33],_wen);
bufif1 (_di[34],_din[34],_wen);
bufif1 (_di[35],_din[35],_wen);
bufif1 (_di[36],_din[36],_wen);
bufif1 (_di[37],_din[37],_wen);
bufif1 (_di[38],_din[38],_wen);
bufif1 (_di[39],_din[39],_wen);
bufif1 (_di[40],_din[40],_wen);
bufif1 (_di[41],_din[41],_wen);
bufif1 (_di[42],_din[42],_wen);
bufif1 (_di[43],_din[43],_wen);
bufif1 (_di[44],_din[44],_wen);
bufif1 (_di[45],_din[45],_wen);
bufif1 (_di[46],_din[46],_wen);
bufif1 (_di[47],_din[47],_wen);
bufif1 (_di[48],_din[48],_wen);
bufif1 (_di[49],_din[49],_wen);
bufif1 (_di[50],_din[50],_wen);
bufif1 (_di[51],_din[51],_wen);
bufif1 (_di[52],_din[52],_wen);
bufif1 (_di[53],_din[53],_wen);
bufif1 (_di[54],_din[54],_wen);
bufif1 (_di[55],_din[55],_wen);
bufif1 (_di[56],_din[56],_wen);
bufif1 (_di[57],_din[57],_wen);
bufif1 (_di[58],_din[58],_wen);
bufif1 (_di[59],_din[59],_wen);
bufif1 (_di[60],_din[60],_wen);
bufif1 (_di[61],_din[61],_wen);
bufif1 (_di[62],_din[62],_wen);
bufif1 (_di[63],_din[63],_wen);
buf (_a[0],_an[0]);
buf (_a[1],_an[1]);
buf (_a[2],_an[2]);
buf (_a[3],_an[3]);
/****************************************************************/

/*	assign #tra 	rd_do = out1r;
	assign #two 	wo_do = out1wo;
	assign #tio 	io_do = out1io;
*/
	assign  	rd_do = out1r;
	assign  	wo_do = out1wo;
	assign  	io_do = out1io;
        assign out1	 = ( rd_do & {64{_st1}}) |
        			(wo_do & {64{~_st1}} & {64{_st2}}) |
				(io_do & {64{~_st1}} & {64{~_st2}} );

// mode definition.
	assign  n_write = (~_clk & _wen);	 // write

// ram cell.

	reg [63:0] memory[0:(2<<4)-1];


// read
always @(_a)
	begin 
		if (_a<=15) 
			begin
		        #tra	out1r=memory[_a];
				_st1=1'b1; 
			end
		else
			begin
			#tra	out1r=64'bx;
				_st1=1'b1; 
			end
	end




// write
always @(negedge _clk)
  begin
	if ( _wen==1'b1 )
		begin
		memory[_a]=_di;
				if (_a <= 15)
					begin
					#two	out1wo=_di;
						_st1=1'b0; 
						_st2=1'b1; 
					end
				else
					begin
					#two	out1wo=64'bx;
						_st1=1'b0; 
						_st2=1'b1; 
					end
		end
  end

// write
always @(_di)
  begin
	if ( n_write==1'b1 )
		begin 
		memory[_a]=_di;
				if (_a <= 15)	
					begin
					#tio	out1io=_di;
						_st1=1'b0; 
						_st2=1'b0; 
					end
				else
					begin
					#tio	out1io=64'bx;
						_st1=1'b0; 
						_st2=1'b0; 
					end
		end
  end

`ifdef functional
`else
// timing violation ( insert x value when timing violation occur )

	always @(notif_w) begin
		memory[_a]= {64{1'bx}};
		out1wo = {64{1'bx}};
		out1io = {64{1'bx}};
	end
`endif

//error message

always @( _an[0] ) begin
         if(_wen==1'b1 && _clk==1'b0) begin
                $display("\n ** error !! ( time %0d ) **\n",$time);
                $display("     can not change address (a0) during data write\n");
         end
end 
always @( _an[1] ) begin
         if(_wen==1'b1 && _clk==1'b0) begin
                $display("\n ** error !! ( time %0d ) **\n",$time);
                $display("     can not change address (a1) during data write\n");
         end
end 
always @( _an[2] ) begin
         if(_wen==1'b1 && _clk==1'b0) begin
                $display("\n ** error !! ( time %0d ) **\n",$time);
                $display("     can not change address (a2) during data write\n");
         end
end 
always @( _an[3] ) begin
         if(_wen==1'b1 && _clk==1'b0) begin
                $display("\n ** error !! ( time %0d ) **\n",$time);
                $display("     can not change address (a3) during data write\n");
         end
end 
always @(_wen) begin
	if(_clk==1'b0) begin
		$display("\n ** error !! ( time %0d ) **\n",$time);
		$display("     can not change writeenablesignal when clk=0\n");               
	end
end

/****************************************************************/
`ifdef functional
`else
	specify specparam

		tph	 = 600 ,  // clk minimam high pulse width 	
		tpl	 = 600 ,  // clk minimam low pulse width 	
                twas	 = 100 ,  // address setup ( write address setup time )
                twah	 = 50  ,  // address hold ( write address hold time )
                twes	 = 100 ,  // wen setup ( write enable setup time )
                tweh	 = 50  ,  // wen hold ( write enable hold time )
                tds 	 = 300 ,  // data setup ( data setup time)
		tdh	 = 50 ;   // data hold ( data hold time )

/****************************************************************/


		$width( posedge clk,  tph:tph:tph);
		$width( negedge clk,  tpl:tpl:tpl);

		$setup(a[0],negedge clk &&& wen ,twas:twas:twas, notif_w);
		$setup(a[1],negedge clk &&& wen ,twas:twas:twas, notif_w);
		$setup(a[2],negedge clk &&& wen ,twas:twas:twas, notif_w);
		$setup(a[3],negedge clk &&& wen ,twas:twas:twas, notif_w);

		$hold(posedge clk &&& wen,a[0] ,twah:twah:twah, notif_w);
		$hold(posedge clk &&& wen,a[1] ,twah:twah:twah, notif_w);
		$hold(posedge clk &&& wen,a[2] ,twah:twah:twah, notif_w);
		$hold(posedge clk &&& wen,a[3] ,twah:twah:twah, notif_w);

		$setup(di[0],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[1],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[2],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[3],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[4],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[5],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[6],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[7],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[8],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[9],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[10],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[11],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[12],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[13],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[14],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[15],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[16],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[17],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[18],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[19],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[20],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[21],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[22],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[23],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[24],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[25],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[26],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[27],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[28],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[29],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[30],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[31],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[32],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[33],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[34],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[35],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[36],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[37],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[38],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[39],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[40],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[41],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[42],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[43],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[44],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[45],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[46],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[47],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[48],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[49],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[50],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[51],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[52],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[53],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[54],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[55],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[56],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[57],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[58],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[59],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[60],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[61],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[62],posedge clk &&& wen ,tds:tds:tds, notif_w);
		$setup(di[63],posedge clk &&& wen ,tds:tds:tds, notif_w);

		$hold(negedge clk &&& wen,di[0] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[1] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[2] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[3] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[4] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[5] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[6] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[7] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[8] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[9] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[10] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[11] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[12] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[13] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[14] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[15] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[16] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[17] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[18] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[19] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[20] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[21] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[22] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[23] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[24] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[25] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[26] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[27] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[28] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[29] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[30] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[31] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[32] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[33] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[34] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[35] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[36] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[37] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[38] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[39] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[40] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[41] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[42] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[43] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[44] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[45] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[46] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[47] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[48] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[49] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[50] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[51] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[52] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[53] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[54] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[55] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[56] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[57] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[58] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[59] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[60] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[61] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[62] ,tdh:tdh:tdh, notif_w);
		$hold(negedge clk &&& wen,di[63] ,tdh:tdh:tdh, notif_w);

endspecify
`endif
endmodule

`ifdef verifault
    `nosuppress_faults
    `disable_portfaults
`endif

`endcelldefine
