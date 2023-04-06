//**************************************************************************************************
//  K9F1208U0M, 512Mbit(x8) 1st Generation NAND FLASH TIMING VECTOR FOR PROGRAM  MODE  TEST      
//  Programmed By NAND Flash Memory Product Planning Team, Samsung Semiconductor Co. LTD.
//  NOTICE:
//  - This test vector file provides simultaneous PROGRAM/ERASE capability up Max.four PAGES/BLOCKS.
//  - And provides also COPY-BACK / PRELOAD functions. 
//  Rev. 1.1 
//**************************************************************************************************

`timescale 1ns/1ps

`define PWRUP   	5000 	 // Wait Time
`define TPROGRAM   	200100   // Program Time
`define TERASE   	2000100  // Erase Time
`define TREAD      	12100    // Data Transfer form Cell to Register
`define TDBSY		1500	 // Dummy Busy Time for Multi Plane Program

module nand_driver();
reg     [7:0]   io;
wire    [7:0]   i_o=io;
reg     		ceb, cle, ale, web, reb, wpb;

integer i;

km29u512  flash(.ceb(ceb), .cle(cle), .ale(ale), 
		.web(web), .reb(reb), .io(i_o), 
		.wpb(wpb), .rbb(rbb));

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
	wpb = 1;
end  

// timing for command latch 
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


// timing for address latch
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


// timing for data latch
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


// timing for serial read
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

// timing for serial read (/CE don't care)
task    serial_read1;
        input  [16:0]   cnt1;

        begin
                cle = 0;
                ale = 0;
                web = 1;
                for ( i=0; i < cnt1; i = i+1)
                begin
                   #26
			ceb = 0;
                        reb = 0;
                   #56
                        reb = 1;
			ceb = 1;
                end
        end
endtask


//******************************
// User Test Vector Here
//******************************

initial
begin
	#`PWRUP

// This function is PRELOAD function and you can read external data(2blocks size=528Byte*32pages*2blocks=33792Bytes) from External_File.txt.
// If you don't want to use this operating, you have to remove this function.
        cmd_latch(8'h00);
    add_latch(8'h00);
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
         #`TREAD                
    serial_read(16'h210);               
        ceb = 1'b1;
	#1000

	cmd_latch(8'h00);
    add_latch(8'h00);
    add_latch(8'h20);
    add_latch(8'h00);
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
         #`TREAD                
    serial_read(16'h210);               
        ceb = 1'b1;
	
        #10000

// ID Read
        cmd_latch(8'h90);
    add_latch(8'h00);
        #100
    serial_read(16'h4);
        #20000

// 1Block Erase 
	cmd_latch(8'h60);
    add_latch(8'h40);
    add_latch(8'h00);
    add_latch(8'h00);	
	cmd_latch(8'hD0);
	#`TERASE
    cmd_latch(8'h70);    // Status Check Command 
        ceb = 1'b0;
	#18
    serial_read(16'h1);
        ceb = 1'b1;
        #1000 


// Multi_Plane Block(4Blocks) Erase
// NOTICE :
//   You can simultaneously erase only one block from each plane, up to four blocks. 
  
	cmd_latch(8'h60);
    add_latch(8'h80);
    add_latch(8'h00);
    add_latch(8'h00);
	#230
	cmd_latch(8'h60);
    add_latch(8'ha0);
    add_latch(8'h00);
    add_latch(8'h00);
        #230
	cmd_latch(8'h60);
    add_latch(8'hc0);
    add_latch(8'h00);
    add_latch(8'h00);
        #230
	cmd_latch(8'h60);
    add_latch(8'he0);
    add_latch(8'h00);
    add_latch(8'h00);
        cmd_latch(8'hD0);
	#`TERASE
    cmd_latch(8'h71);   // Multi_Status Check Command
	ceb = 1'b0;
	#18
    serial_read(16'h1);
   	ceb = 1'b1;
	#1000 

// Multi_Plane Page(4pages) Program
// NOTICE :
//   While any block in each plane may be addressable for Multi_Plane Page Program, the four least 
//   significant address(A9-A13) for the selected pages at one operation must be the same.
 
	cmd_latch(8'h80);
    add_latch(8'h00);
    add_latch(8'hc1);
    add_latch(8'h00);
    add_latch(8'h00);
	data_latch(10'h210,8'h00);
    cmd_latch(8'h11);
	#`TDBSY
        cmd_latch(8'h80);
    add_latch(8'h00);
    add_latch(8'ha1);
    add_latch(8'h00);
    add_latch(8'h00);
        data_latch(10'h210,8'h10); 
    cmd_latch(8'h11);
	#`TDBSY 
       cmd_latch(8'h80);
    add_latch(8'h00);
    add_latch(8'he1);
    add_latch(8'h00);
    add_latch(8'h00); 
        data_latch(10'h210,8'h20); 
    cmd_latch(8'h11);
	#`TDBSY 
        cmd_latch(8'h80);
    add_latch(8'h00);
    add_latch(8'h81);
    add_latch(8'h00);
    add_latch(8'h00); 
        data_latch(10'h210,8'h30); 
    cmd_latch(8'h10);
	#`TPROGRAM 
    cmd_latch(8'h71);    // Multi_Status Check Command
        ceb = 1'b0;
	#18 
    serial_read(16'h1);
	ceb = 1'b1;
        #1000

// Copy_Back #1 ( Moving programmed 528-Byte to lower-address from current address )
// NOTICE: Whenever you use this function, you have to check that address 14 ,the plane address, of source and destination
//         page address must be same.
        cmd_latch(8'h00);
    add_latch(8'h00);
    add_latch(8'ha1); //source page address
    add_latch(8'h00);
    add_latch(8'h00);	
        #`TREAD

        cmd_latch(8'h8a);
    add_latch(8'h00);
    add_latch(8'h41); //destination page address
    add_latch(8'h00);
    add_latch(8'h00);
        #`TPROGRAM

    cmd_latch(8'h70); // Status Check Command
        ceb = 1'b0;
    serial_read(16'h1);
        ceb = 1'b1;
        #1000

// Copy_Back #2  ( Moving programmed 528-Byte to higher-address from current address )
// NOTICE: Whenever you use this function, you have to check that address 14 ,the plane address, of source and destination
//         page address must be same.
        cmd_latch(8'h00);
    add_latch(8'h00);
    add_latch(8'hc1); //source page address
    add_latch(8'h00);
    add_latch(8'h00);
        #`TREAD

        cmd_latch(8'h8a);
    add_latch(8'h00);
    add_latch(8'he2); //destination page address
    add_latch(8'h00);
    add_latch(8'h00);
        #`TPROGRAM

    cmd_latch(8'h70);
        ceb = 1'b0;
    serial_read(16'h1);
        ceb = 1'b1;
        #1000

// Sequential Read
        cmd_latch(8'h00);
    add_latch(8'h00);
    add_latch(8'h41);	
    add_latch(8'h00);
    add_latch(8'h00);
	#`TREAD
    serial_read(16'h210);
	ceb = 1'b1;	
	#1000

	cmd_latch(8'h00);
    add_latch(8'h00);
    add_latch(8'h81);
    add_latch(8'h00);
    add_latch(8'h00);
	#`TREAD
    serial_read(16'h210);
	ceb = 1'b1;
	#1000

	cmd_latch(8'h00);
    add_latch(8'h00);
    add_latch(8'he1);
    add_latch(8'h00);
    add_latch(8'h00);
        #`TREAD
    serial_read(16'h210);
	ceb = 1'b1;
        #1000

	cmd_latch(8'h00);
    add_latch(8'h00);
    add_latch(8'he2);
    add_latch(8'h00);
    add_latch(8'h00);
        #`TREAD
    serial_read1(16'h210);
	ceb = 1'b1; 
        #1000
       
  	$finish;
end
endmodule  
