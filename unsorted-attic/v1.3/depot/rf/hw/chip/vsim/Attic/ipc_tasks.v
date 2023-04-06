
/****************************************************************
 *
 * Start of IPC definitions
 *
 ****************************************************************/

reg ipc_monitor;
initial ipc_monitor = $test$plusargs("ipc_mon");

parameter       IPC_SERVER      = 2;
parameter       PKT_SIZE_BYTE   = 48;
parameter       PKT_SIZE_WORD   = 12;

/* SysCmd(1:0) single read request size */
parameter       SYS_CMD_SRDSZ_1BYTE = 0,
                SYS_CMD_SRDSZ_2BYTE = 1,        /* Half Word */
                SYS_CMD_SRDSZ_3BYTE = 2,        /* Tri-Byte */
                SYS_CMD_SRDSZ_4BYTE = 3;        /* Single Word */

/* SysCmd(1:0) block read request size */
parameter       SYS_CMD_BRDSZ_2WORD = 0,
                SYS_CMD_BRDSZ_4WORD = 1,
                SYS_CMD_BRDSZ_8WORD = 2;

/* SysCmd(1:0) single write request size */
parameter       SYS_CMD_SWRSZ_1BYTE = 0,
                SYS_CMD_SWRSZ_2BYTE = 1,        /* Half Word */
                SYS_CMD_SWRSZ_3BYTE = 2,        /* Tri-Byte */
                SYS_CMD_SWRSZ_4BYTE = 3;        /* Single Word */

/* SysCmd(1:0) block write request size */
parameter       SYS_CMD_BWRSZ_2WORD = 0,
                SYS_CMD_BWRSZ_4WORD = 1,
                SYS_CMD_BWRSZ_8WORD = 2;

/* Offset to various fields in IpcPkt structure */
`define         PKT_LEN_OFS     0
`define         PKT_CODE_OFS    1
`define         PKT_SIZE_OFS    2
`define         PKT_ADDR_OFS    3
`define         PKT_DATA_OFS    4

/* Request codes */
`define         REQ_SINGLE_READ         1
`define         REQ_SINGLE_WRITE        2
`define         REQ_BLOCK_READ          3
`define         REQ_BLOCK_WRITE         4
`define         REQ_STALL               5
`define         REQ_CONFIG_RDRAM        6 //XXX
`define         REQ_LOG        		6
`define         REQ_RUN_TEST		7
`define         REQ_QUIT                100

/* Request size codes */
`define         REQ_SZ_BYTE     1
`define         REQ_SZ_HALF     2
`define         REQ_SZ_WORD     4
`define         REQ_SZ_DWORD    8

/* Response codes */
`define         RSP_OK          1
`define         RSP_DATA        2
`define         RSP_LOAD        3
`define         RSP_STORE       4
`define         RSP_ERROR       100
/*
typedef struct _IpcPktStruct {
        unsigned int    length;
        unsigned int  code;
        unsigned int  size;
        unsigned int    address;
        unsigned int    data[8];
} IpcPkt;
*/

reg [1:256*8]	ipc_name; 
integer		ipc_fd, new_fd;
integer		ret;
integer		reset_done;

initial		reset_done = 0;

reg [31:0] req_code;
reg [31:0] req_size;
reg [31:0] req_address;
reg [31:0] req_data0;
reg [31:0] req_data1;
reg [31:0] req_data2;
reg [31:0] req_data3;
reg [31:0] req_data4;
reg [31:0] req_data5;
reg [31:0] req_data6;
reg [31:0] req_data7;

reg [31:0] rsp[0:PKT_SIZE_WORD-1];      /* IpcPkt structure = 12 words  */

parameter	TID_PBUS_REG	=	1,
		TID_PBUS_IO	=	2,
		TID_PBUS_DMA	=	3,
		TID_ABUS_REG	=	4,
		TID_ABUS_DMA	=	5,
		TID_VBUS_REG	=	6,
		TID_VBUS_DMA	=	7,
		TID_PIF_REG	=	8,
		TID_PIF_IO 	=	9,
		TID_PIF_DMA	=	10,
		TID_CBUF_DMA	=	11,
		TID_RDRAM	=	12, //XXX
		TID_CFG_RDRAM	=	13; //XXX

/****************************************************************
 *
 * End of IPC definitions
 *
 ****************************************************************/


initial begin
   test_selected <= LOW;
   @(posedge clock);
   wait(`SYSTEM_READY);

   /******************************************************
    * New IPC
    */
	reset_done = 1;

	if ($getstr$plusarg("ipc=", ipc_name) != 1) 
	begin
		ipc_name = "NULL";
	end

        ret = $ipc_init(ipc_name);
        ipc_fd = $ipc_open(IPC_SERVER);
        if (ipc_fd < 0) begin
                $display("ERROR: ipc_open failed!");
        end
   /******************************************************/

end


/**************************************************************
 *
 * Start of IPC commands
 *
 **************************************************************/

always @(posedge clock) begin

	wait(reset_done);

        test_selected <= HIGH;
	repeat (10) @(posedge clock);

        /* Block on accept */
        new_fd = $ipc_accept(ipc_fd);
        if (new_fd < 0) begin
                $display("ERROR: ipc_accept failed!");
        end
        else begin

                /* Read in request packet */
                ret = $ipc_receive(new_fd,
                        req_code, req_size, req_address,
                        req_data0, req_data1, req_data2, req_data3,
                        req_data4, req_data5, req_data6, req_data7);

                if (ret < 0) begin
                        $display("ERROR: ipc_receive failed!");
                end
                else begin
                        /*
                        $display("Pkt: code=%0d, size=%0d, addr=%h",
                                req_code, req_size, req_address);
                        $display("Data: %h %h %h %h %h %h %h %h",
                                req_data0, req_data1, req_data2, req_data3,
                                req_data4, req_data5, req_data6, req_data7);
                        */

                        test_selected <= HIGH;

                        /* Process request code */
                        case (req_code)
                                `REQ_SINGLE_READ: begin
					if (ipc_monitor)
                                        	$display("Code = SINGLE_READ");
                                        sread(req_address, req_size);
                                        reply_cmd(`RSP_DATA);
                                        end
                                `REQ_BLOCK_READ: begin
					if (ipc_monitor)
                                        	$display("Code = BLOCK_READ");
                                        read_block(req_address, req_size);
                                        reply_cmd(`RSP_DATA);
                                        end
                                `REQ_SINGLE_WRITE: begin
					if (ipc_monitor)
                                        	$display("Code = SINGLE_WRITE");
                                        swrite(req_address, req_size,
                                                req_data0);
                                        reply_cmd(`RSP_OK);
                                        end
                                `REQ_BLOCK_WRITE: begin
					if (ipc_monitor)
                                        	$display("Code = BLOCK_WRITE");
                        		data[0] = req_data0;
                        		data[1] = req_data1;
                        		data[2] = req_data2;
                        		data[3] = req_data3;
                        		data[4] = req_data4;
                        		data[5] = req_data5;
                        		data[6] = req_data6;
                        		data[7] = req_data7;
                                        write_block(req_address, req_size);
                                        reply_cmd(`RSP_OK);
                                        end
                                `REQ_STALL: begin
					if (ipc_monitor)
                                        	$display(
						"Code = STALL, cycles=%0d",
						req_data0);
                                        reply_cmd(`RSP_OK);
                                        repeat(req_data0) @(posedge clock);
                                        end
                                `REQ_LOG: begin
					if (ipc_monitor)
                                        	$display("Code = LOG");
					$fwrite(vsim.rcp_attest_tab.tab_file_ptr,
					        "-- v %.3d 0x%.8x 0x%.8x 0x%.8x 0x%.8x \n",
                                		req_data0, req_data1, 
						req_data2, req_data3, 
						req_data4);
                                        reply_cmd(`RSP_OK);
                                        end
                                `REQ_QUIT: begin
					if (ipc_monitor)
                                        	$display("Code = QUIT");
                                        reply_cmd(`RSP_OK);
`ifdef MSPAN_MON
					vsim.mspan_mon_0.ms_state_results;
`endif
                                        $finish;
                                        end
                                default: begin
                                        $display("ERROR: unknown req code=%0d",
                                                req_code);
                                        reply_cmd(`RSP_ERROR);
                                        end
                        endcase


                end  /* else */

                /* Here, we close the new socket */
                ret = $ipc_close(new_fd);
        end  /* else */

        p_valid <= LOW;

end  /* always */


task reply_cmd;
        input [31:0] code;

	integer i;
        begin
		for (i = 0; i < PKT_SIZE_WORD; i = i+1) 
			rsp[i] = 0;

                /* Update code and send back packet to requestor */
                rsp[`PKT_LEN_OFS]    = PKT_SIZE_BYTE;
                rsp[`PKT_CODE_OFS]   = code;
                rsp[`PKT_SIZE_OFS]   = req_size;
                rsp[`PKT_DATA_OFS]   = data[0];
                rsp[`PKT_DATA_OFS+1] = data[1];
                rsp[`PKT_DATA_OFS+2] = data[2];
                rsp[`PKT_DATA_OFS+3] = data[3];
                rsp[`PKT_DATA_OFS+4] = data[4];
                rsp[`PKT_DATA_OFS+5] = data[5];
                rsp[`PKT_DATA_OFS+6] = data[6];
                rsp[`PKT_DATA_OFS+7] = data[7];

		/*
		if (ipc_monitor)
                	$display("reply_cmd: code=%0d len=%0d size=%0d\n data: %h %h %h %h %h %h %h %h",
                        rsp[`PKT_CODE_OFS],
                        rsp[`PKT_LEN_OFS],
                        rsp[`PKT_SIZE_OFS],
                        rsp[`PKT_DATA_OFS],
                        rsp[`PKT_DATA_OFS+1],
                        rsp[`PKT_DATA_OFS+2],
                        rsp[`PKT_DATA_OFS+3],
                        rsp[`PKT_DATA_OFS+4],
                        rsp[`PKT_DATA_OFS+5],
                        rsp[`PKT_DATA_OFS+6],
                        rsp[`PKT_DATA_OFS+7]);
		*/

                ret = $ipc_send(new_fd,
                                rsp[`PKT_CODE_OFS],
                                rsp[`PKT_SIZE_OFS],
                                rsp[`PKT_ADDR_OFS],
                                rsp[`PKT_DATA_OFS],
                                rsp[`PKT_DATA_OFS+1],
                                rsp[`PKT_DATA_OFS+2],
                                rsp[`PKT_DATA_OFS+3],
                                rsp[`PKT_DATA_OFS+4],
                                rsp[`PKT_DATA_OFS+5],
                                rsp[`PKT_DATA_OFS+6],
                                rsp[`PKT_DATA_OFS+7]);

                if (ret < 0) begin
                        $display("ERROR: ipc_send failed!");
                end  /* if */
        end
endtask  /* reply_cmd */


/**************************************************************
 *
 * End of IPC commands
 *
 **************************************************************/


