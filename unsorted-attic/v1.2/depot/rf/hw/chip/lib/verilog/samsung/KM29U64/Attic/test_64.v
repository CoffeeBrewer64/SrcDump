//****************************************************************************************
//  K9F6408U0A, 64Mbit(x8) 2nd Generation NAND FLASH TIMING VECTOR FOR PROGRAM MODE TEST      
//  Programmed By NAND Flash Memory Product Planning Team, Samsung Semiconductor Co. LTD.
//  Rev. 1.1 
//****************************************************************************************

`timescale 1ns/1ps

`define PWRUP   	5000 	  // Wait Time
`define TPROGRAM   	200100    // Program Time
`define TERASE   	2000100   // Erase Time
`define TREAD      	10100     // Data Transfer form Cell to Register

module nand_driver();
reg     [7:0]   io;
wire    [7:0]   i_o=io;
reg     		ceb, cle, ale, web, reb, seb, wpb;

integer i;

km29u64   flash(.ceb(ceb), .cle(cle), .ale(ale), 
				.web(web), .reb(reb), .io(i_o), 
				.seb(seb), .wpb(wpb), .rbb(rbb));

initial
begin
	$dumpvars();
	$dumpfile("test.dump");
end

initial
begin
	ceb = 1; 
	cle = 0;        
	ale = 0; 
	web = 1; 
	reb = 1;
	io  = 8'hzz; 
	seb = 0;
	wpb = 1;
end  

// Timing for command latch 
task	cmd_latch;
	input [7:0] cmd;

	begin
	    #20
		ceb = 0;
		web = 1;
		cle = 0;
		ale = 0;
	    #10
		cle = 1;
	    #1
		web = 0;
		io  = cmd;
	    #26
		web = 1;
	    #11
		io  = 8'hzz;
	    #6
		cle = 0;
            #10
                ceb = 1;
	end
endtask


// Timing for address latch
task	add_latch;
	input [7:0] add;

	begin
		ceb = 0;
            #20
		cle = 0;
		ale = 1;
	    #1
		web = 0;
	    #5
		io  = add;
	    #22
		web = 1;
	    #11
		io  = 8'hzz;
	    #6
		ale = 0;
		ceb = 0;
	end
endtask


// Timing for data latch
task	data_latch;
	input [10:0] cnt;
	input [7:0] data;

	begin
		for (i=0; i < cnt; i=i+1)
		begin
	    	   #20
			ceb = 0;
	    	   #1
			web = 0;
	    	   #5
			io  = data + i;
	    	   #22
			web = 1;
		   #11
			io  = 8'hzz;
		end
	end
endtask

// Timing for data latch with ceb don't care
task    data_latch1;
        input [10:0] cnt1;
        input [7:0] data1;

        begin
                for (i=0; i < cnt1; i=i+1)
                begin
                   #5
                        ceb = 0;
                   #8
                        web = 0;
                   #5
                        io  = data1 + i;
                   #22
                        web = 1;
		   #11
			ceb = 1;
                   #11
                        io  = 8'hzz;
                end
        end
endtask



// Timing for serial read
task	serial_read;
	input  [16:0]	cnt;

	begin
		cle = 0;
		ale = 0;
		web = 1;
	    	for ( i=0; i < cnt; i = i+1) 
		begin
		   #16
			reb = 0;
	    	   #36
			reb = 1;
		end
	end
endtask

// Timing for serial read with ceb don't care
task	serial_read1;
	input	[16:0]	cnt1;

	begin
		cle = 0;
		ale = 0;
		web = 1;
		for ( i=0; i<cnt1; i = i+1)
		begin
		   #26
			reb = 0;
			ceb = 0;
			//reb = 0;
                   #50
			reb = 1;
			ceb = 1;
		end
	end
endtask

// Timing for serial read with ceb don't care
task    serial_read2;
        input   [16:0]  cnt2;

        begin
                cle = 0;
                ale = 0;
                web = 1;
                for ( i=0; i<cnt2; i = i+1)
                begin
                   #20
                        reb = 0;
		   #6	
                        ceb = 0;
                        //reb = 0;
                   #50
                        reb = 1;
		   #6
                        ceb = 1;
                        //reb = 1;
                end
        end
endtask

// Timing for serial read with ceb don't care
task    serial_read3;
        input   [16:0]  cnt3;

        begin
                cle = 0;
                ale = 0;
                web = 1;
                for ( i=0; i<cnt3; i = i+1)
                begin
                   #20
                        ceb = 0;
                   #6
                        reb = 0;
                   #50
                        ceb = 1;
                   #6
                        reb = 1;
                        //reb = 1;
                end
        end
endtask

//******************************
// User Test Vector Here
//******************************

initial
begin
	#`PWRUP

// This function is PRELOAD function and you can read external data(2blocks size=528Byte*16pages*2blocks=16896Bytes) from External_File.txt.
// If you don't want to use this operating, you have to remove this function.
        cmd_latch(8'h00);
    add_latch(8'h00);
    add_latch(8'h00);
    add_latch(8'h00);
        #`TREAD
    serial_read(16'h210); // Sequential read from the 1st block's 1st page.	
	 #`TREAD
    serial_read(16'h210);       
         #`TREAD        
    serial_read(16'h210);       
        #`TREAD 
    serial_read(16'h210);       
         #`TREAD                
    serial_read(16'h210);               
         #`TREAD                
    serial_read(16'h210);               
        #`TREAD                
    serial_read(16'h210);               
         #`TREAD                
    serial_read(16'h210);               
	#`TREAD
    serial_read(16'h210);
         #`TREAD        
    serial_read(16'h210);       
         #`TREAD        
    serial_read(16'h210);       
        #`TREAD 
    serial_read(16'h210);       
         #`TREAD                
    serial_read(16'h210);               
         #`TREAD                
    serial_read(16'h210);               
        #`TREAD                
    serial_read(16'h210);               
         #`TREAD                
    serial_read(16'h210);               
        ceb = 1'b1;
	#1000

	cmd_latch(8'h00);
    add_latch(8'h00);
    add_latch(8'h20);
    add_latch(8'h00);
        #`TREAD
    serial_read(16'h210); // Sequential read from the 2nd block's 1st page.
         #`TREAD        
    serial_read(16'h210);       
         #`TREAD        
    serial_read(16'h210);       
        #`TREAD 
    serial_read(16'h210);       
         #`TREAD                
    serial_read(16'h210);               
         #`TREAD                
    serial_read(16'h210);               
        #`TREAD                
    serial_read(16'h210);               
         #`TREAD                
    serial_read(16'h210);               
        #`TREAD
    serial_read(16'h210);
         #`TREAD        
    serial_read(16'h210);       
         #`TREAD        
    serial_read(16'h210);       
        #`TREAD 
    serial_read(16'h210);       
         #`TREAD                
    serial_read(16'h210);               
         #`TREAD                
    serial_read(16'h210);               
        #`TREAD                
    serial_read(16'h210);               
         #`TREAD                
    serial_read(16'h210);               
        ceb = 1'b1;
	
        #10000 
  
// ID Read
        cmd_latch(8'h90);
    add_latch(8'h00);
    add_latch(8'h00);
        #100
    serial_read(16'h2);
        #20000

// Block Erase
        cmd_latch(8'h60);
    add_latch(8'he0);
    add_latch(8'h00);
        cmd_latch(8'hD0);
        #`TERASE
    cmd_latch(8'h70); // Status Check Command
        ceb = 1'b0;
    serial_read(16'h1); 
        ceb = 1'b1;
        #1000

// 1st Page Program
        cmd_latch(8'h80);
    add_latch(8'h00);
    add_latch(8'he0);
    add_latch(8'h00);
        data_latch(10'h200,8'h10);
	data_latch(10'h10,8'h90);
    cmd_latch(8'h10);
        #`TPROGRAM 
    cmd_latch(8'h70); //Status Check Command
        ceb = 1'b0;
    serial_read(16'h1);
        ceb = 1'b1;
        #1000

// 2nd Page program
        cmd_latch(8'h80);
    add_latch(8'h00);
    add_latch(8'he1);
    add_latch(8'h00);
        data_latch1(10'h210,8'h20);
    cmd_latch(8'h10);
        #`TPROGRAM 
    cmd_latch(8'h70); //Status Check Command
        ceb = 1'b0;
    serial_read(16'h1);
        ceb = 1'b1;
        #1000

// Sequential Read
        cmd_latch(8'h00);
    add_latch(8'h00);
    add_latch(8'he0);
    add_latch(8'h00);
        #`TREAD
    serial_read(16'h20f);
	#20
	reb = 0;
	#50
	ceb = 1;
	#50
	reb = 1;
	#40
        #`TREAD
    serial_read3(16'h210);
        ceb = 1'b1;
        #1000

// Read with ceb don't care
	cmd_latch(8'h00);
    add_latch(8'h00);
    add_latch(8'he0);
    add_latch(8'h00);
        #`TREAD
	ceb = 1;
	reb = 1;
	#20
	ceb = 0;
	reb = 0;
    serial_read1(16'h210);
        ceb = 1'b1;
        #1000

// Read spare area
	cmd_latch(8'h50);
    add_latch(8'h00);
    add_latch(8'he0);
    add_latch(8'h00);
        #`TREAD
    serial_read(16'h10); //1Byte read
	#`TREAD
    serial_read1(16'h10);
        ceb = 1'b1;
        #1000

	cmd_latch(8'h50);
    add_latch(8'h01);
    add_latch(8'he0);
    add_latch(8'h00);
        #`TREAD
    serial_read1(16'h3); //3Byte read
        ceb = 1'b1;
        #1000
        $finish;
end
endmodule  
