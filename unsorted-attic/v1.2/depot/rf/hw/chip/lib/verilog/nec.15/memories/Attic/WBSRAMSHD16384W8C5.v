//VERSION: 7.1.3 DATE:01/10/26 RAM TYPE: 1port RAM
`timescale 1ps / 1ps
`celldefine
`ifdef verifault
    `suppress_faults
    `enable_portfaults
`endif
module WBSRAMSHD16384W8C5 (
	DO7,
	DO6,
	DO5,
	DO4,
	DO3,
	DO2,
	DO1,
	DO0,
	DI7,
	DI6,
	DI5,
	DI4,
	DI3,
	DI2,
	DI1,
	DI0,
	A13,
	A12,
	A11,
	A10,
	A9,
	A8,
	A7,
	A6,
	A5,
	A4,
	A3,
	A2,
	A1,
	A0,
	WEB,
	CSB,
	BE,
	TBE,
	TEST,
	BUB
	);

    input DI0 ;
    input DI1 ;
    input DI2 ;
    input DI3 ;
    input DI4 ;
    input DI5 ;
    input DI6 ;
    input DI7 ;
    input A0 ;
    input A1 ;
    input A2 ;
    input A3 ;
    input A4 ;
    input A5 ;
    input A6 ;
    input A7 ;
    input A8 ;
    input A9 ;
    input A10 ;
    input A11 ;
    input A12 ;
    input A13 ;
    input WEB ;
    input CSB ;
    input BE ;
    input TBE ;
    input TEST ;
    input BUB ;
    output DO0 ;
    output DO1 ;
    output DO2 ;
    output DO3 ;
    output DO4 ;
    output DO5 ;
    output DO6 ;
    output DO7 ;

    parameter BIT=8;
    parameter WORD=16384;
    parameter ADD_BIT=14;

	wire[BIT-1:0] DI;
	wire[ADD_BIT-1:0] A;

/* -------------------------- */
reg [BIT-1:0] DO;
reg [BIT-1:0] tmp_DO;

reg [ADD_BIT-1:0] address;
reg intcsb, pre_BE,pre_TBE;

parameter all_X={BIT{1'bx}};

reg[BIT-1:0] memory[0:WORD-1];

// address "X" 
reg[ADD_BIT-1:0] x_add_num[0:ADD_BIT];
integer i,x_count;

   integer do_flag;

`ifdef  NEC_RTL_SIM
   parameter  tACC_w = 892;  // Dummy value in Wrtie through
   parameter  tACC_r = 2703;  // Dummy value in Read mode
`endif  // NEC_RTL_SIM

/* -------------------------- */

	// ------------------------------------- specify check flg
	wire normal_mode;
	wire test_mode;

`ifdef  NEC_RTL_SIM
`else
	reg notifier_w;
	reg notifier_a;
	reg notifier_wr;
	reg notifier_period;

`endif

`ifdef  NEC_RTL_SIM
    initial begin
      PrintRTLMsg;
    end
`endif

	// ------------------------------------- dummy buffer
    buf ( _DI0, DI0 );
    buf ( _DI1, DI1 );
    buf ( _DI2, DI2 );
    buf ( _DI3, DI3 );
    buf ( _DI4, DI4 );
    buf ( _DI5, DI5 );
    buf ( _DI6, DI6 );
    buf ( _DI7, DI7 );
    buf ( _A0, A0 );
    buf ( _A1, A1 );
    buf ( _A2, A2 );
    buf ( _A3, A3 );
    buf ( _A4, A4 );
    buf ( _A5, A5 );
    buf ( _A6, A6 );
    buf ( _A7, A7 );
    buf ( _A8, A8 );
    buf ( _A9, A9 );
    buf ( _A10, A10 );
    buf ( _A11, A11 );
    buf ( _A12, A12 );
    buf ( _A13, A13 );
    buf ( _WEB, WEB );
    buf ( _CSB, CSB );
    buf ( _BE, BE );
    buf ( _TBE, TBE );
    buf ( _TEST, TEST );
    buf ( _BUB, BUB );

    buf ( DI[0], _DI0 );
    buf ( DI[1], _DI1 );
    buf ( DI[2], _DI2 );
    buf ( DI[3], _DI3 );
    buf ( DI[4], _DI4 );
    buf ( DI[5], _DI5 );
    buf ( DI[6], _DI6 );
    buf ( DI[7], _DI7 );

    buf ( A[0], _A0 );
    buf ( A[1], _A1 );
    buf ( A[2], _A2 );
    buf ( A[3], _A3 );
    buf ( A[4], _A4 );
    buf ( A[5], _A5 );
    buf ( A[6], _A6 );
    buf ( A[7], _A7 );
    buf ( A[8], _A8 );
    buf ( A[9], _A9 );
    buf ( A[10], _A10 );
    buf ( A[11], _A11 );
    buf ( A[12], _A12 );
    buf ( A[13], _A13 );

	wire [BIT-1:0] dmy_DO;
	assign dmy_DO=DO;

    nmos ( DO0, dmy_DO[0], 1'b1 );
    nmos ( DO1, dmy_DO[1], 1'b1 );
    nmos ( DO2, dmy_DO[2], 1'b1 );
    nmos ( DO3, dmy_DO[3], 1'b1 );
    nmos ( DO4, dmy_DO[4], 1'b1 );
    nmos ( DO5, dmy_DO[5], 1'b1 );
    nmos ( DO6, dmy_DO[6], 1'b1 );
    nmos ( DO7, dmy_DO[7], 1'b1 );

/* ----------------------- specify */
	assign normal_mode=((_BUB!==0) && (_TEST!==1));
	assign test_mode=((_BUB!==0) && (_TEST!==0));

`ifdef  NEC_RTL_SIM
`else
     wire _check_n1;
     wire _check_t1;
     wire _check_n2;
     wire _check_t2;
     wire _check_n3;
     wire _check_t3;
     wire _check_bubn;
     wire _check_bubt;
     wire _check_test;
     wire _check_periodn;
     wire _check_periodt;
`endif

`ifdef  NEC_RTL_SIM
`else
     assign _check_n1=((_CSB!==1'b1) && (normal_mode==1));
     assign _check_t1=((_CSB!==1'b1) && (test_mode==1));
     assign _check_n2=((_CSB!==1'b1) && (_WEB!==1'b1) && (normal_mode==1));
     assign _check_t2=((_CSB!==1'b1) && (_WEB!==1'b1) && (test_mode==1));
     assign _check_n3=((normal_mode==1));
     assign _check_t3=((test_mode==1));
     assign _check_bubn=((_CSB!==1'b1) && (_TEST!==1'b1));
     assign _check_bubt=((_CSB!==1'b1) && (_TEST!==1'b0));
     assign _check_test=((_CSB!==1'b1) && (_BUB!==1'b0));
     buf #1 (pre_csb,intcsb);
     assign _check_periodn=((normal_mode==1));
     assign _check_periodt=((test_mode==1));
`endif  // NEC_RTL_SIM

`ifdef  NEC_RTL_SIM
`else
    specify
        specparam DMY_SPC=1:1:1;

	$setup ( posedge DI0, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( posedge DI1, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( posedge DI2, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( posedge DI3, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( posedge DI4, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( posedge DI5, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( posedge DI6, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( posedge DI7, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( negedge DI0, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( negedge DI1, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( negedge DI2, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( negedge DI3, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( negedge DI4, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( negedge DI5, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( negedge DI6, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( negedge DI7, posedge BE &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, posedge DI0 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, posedge DI1 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, posedge DI2 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, posedge DI3 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, posedge DI4 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, posedge DI5 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, posedge DI6 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, posedge DI7 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, negedge DI0 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, negedge DI1 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, negedge DI2 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, negedge DI3 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, negedge DI4 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, negedge DI5 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, negedge DI6 &&& _check_n2, DMY_SPC, notifier_w );
	$hold ( posedge BE, negedge DI7 &&& _check_n2, DMY_SPC, notifier_w );
	$setup ( posedge DI0, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( posedge DI1, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( posedge DI2, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( posedge DI3, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( posedge DI4, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( posedge DI5, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( posedge DI6, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( posedge DI7, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( negedge DI0, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( negedge DI1, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( negedge DI2, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( negedge DI3, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( negedge DI4, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( negedge DI5, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( negedge DI6, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$setup ( negedge DI7, posedge TBE &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, posedge DI0 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, posedge DI1 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, posedge DI2 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, posedge DI3 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, posedge DI4 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, posedge DI5 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, posedge DI6 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, posedge DI7 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, negedge DI0 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, negedge DI1 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, negedge DI2 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, negedge DI3 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, negedge DI4 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, negedge DI5 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, negedge DI6 &&& _check_t2, DMY_SPC, notifier_w );
	$hold ( posedge TBE, negedge DI7 &&& _check_t2, DMY_SPC, notifier_w );

	$setup ( posedge A0, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A1, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A2, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A3, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A4, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A5, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A6, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A7, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A8, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A9, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A10, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A11, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A12, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A13, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A0, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A1, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A2, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A3, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A4, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A5, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A6, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A7, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A8, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A9, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A10, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A11, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A12, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( negedge A13, posedge BE &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A0 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A1 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A2 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A3 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A4 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A5 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A6 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A7 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A8 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A9 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A10 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A11 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A12 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, posedge A13 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A0 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A1 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A2 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A3 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A4 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A5 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A6 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A7 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A8 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A9 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A10 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A11 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A12 &&& _check_n1, DMY_SPC, notifier_a );
	$hold ( posedge BE, negedge A13 &&& _check_n1, DMY_SPC, notifier_a );
	$setup ( posedge A0, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A1, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A2, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A3, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A4, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A5, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A6, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A7, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A8, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A9, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A10, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A11, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A12, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( posedge A13, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A0, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A1, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A2, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A3, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A4, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A5, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A6, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A7, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A8, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A9, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A10, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A11, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A12, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$setup ( negedge A13, posedge TBE &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A0 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A1 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A2 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A3 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A4 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A5 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A6 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A7 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A8 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A9 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A10 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A11 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A12 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, posedge A13 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A0 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A1 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A2 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A3 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A4 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A5 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A6 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A7 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A8 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A9 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A10 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A11 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A12 &&& _check_t1, DMY_SPC, notifier_a );
	$hold ( posedge TBE, negedge A13 &&& _check_t1, DMY_SPC, notifier_a );

        $setup ( posedge WEB, posedge BE &&& _check_n1, DMY_SPC, notifier_w );
        $setup ( negedge WEB, posedge BE &&& _check_n1, DMY_SPC, notifier_w );
        $hold ( posedge BE, posedge WEB &&& _check_n1, DMY_SPC, notifier_w );
        $hold ( posedge BE, negedge WEB &&& _check_n1, DMY_SPC, notifier_w );
        $setup ( posedge WEB, posedge TBE &&& _check_t1, DMY_SPC, notifier_w );
        $setup ( negedge WEB, posedge TBE &&& _check_t1, DMY_SPC, notifier_w );
        $hold ( posedge TBE, posedge WEB &&& _check_t1, DMY_SPC, notifier_w );
        $hold ( posedge TBE, negedge WEB &&& _check_t1, DMY_SPC, notifier_w );

        $setup ( posedge CSB, posedge BE &&& _check_n3, DMY_SPC, notifier_a );
        $setup ( negedge CSB, posedge BE &&& _check_n3, DMY_SPC, notifier_a );
        $hold ( posedge BE, posedge CSB &&& _check_n3, DMY_SPC, notifier_a );
        $hold ( posedge BE, negedge CSB &&& _check_n3, DMY_SPC, notifier_a );
        $setup ( posedge CSB, posedge TBE &&& _check_t3, DMY_SPC, notifier_a );
        $setup ( negedge CSB, posedge TBE &&& _check_t3, DMY_SPC, notifier_a );
        $hold ( posedge TBE, posedge CSB &&& _check_t3, DMY_SPC, notifier_a );
        $hold ( posedge TBE, negedge CSB &&& _check_t3, DMY_SPC, notifier_a );

        $width ( posedge BE &&& _check_n1, DMY_SPC, 0, notifier_wr );
        $width ( negedge BE &&& _check_n1, DMY_SPC, 0, notifier_a );
        $width ( posedge TBE &&& _check_t1, DMY_SPC, 0, notifier_wr );
        $width ( negedge TBE &&& _check_t1, DMY_SPC, 0, notifier_a );

        $setup ( posedge BUB, posedge BE &&& _check_bubn, DMY_SPC, notifier_a );
        $setup ( negedge BUB, posedge BE &&& _check_bubn, DMY_SPC, notifier_a );
        $hold ( posedge BE &&& _check_bubn, posedge BUB, DMY_SPC, notifier_a );
        $hold ( posedge BE &&& _check_bubn, negedge BUB, DMY_SPC, notifier_a );
        $setup ( posedge BUB, negedge BE &&& _check_bubn, DMY_SPC, notifier_a );
        $setup ( negedge BUB, negedge BE &&& _check_bubn, DMY_SPC, notifier_a );
        $hold ( negedge BE &&& _check_bubn, posedge BUB, DMY_SPC, notifier_a );
        $hold ( negedge BE &&& _check_bubn, negedge BUB, DMY_SPC, notifier_a );

        $setup ( posedge TEST, posedge BE &&& _check_test, DMY_SPC, notifier_a );
        $setup ( negedge TEST, posedge BE &&& _check_test, DMY_SPC, notifier_a );
        $hold ( posedge BE &&& _check_test, posedge TEST, DMY_SPC, notifier_a );
        $hold ( posedge BE &&& _check_test, negedge TEST, DMY_SPC, notifier_a );
        $setup ( posedge TEST, negedge BE &&& _check_test, DMY_SPC, notifier_a );
        $setup ( negedge TEST, negedge BE &&& _check_test, DMY_SPC, notifier_a );
        $hold ( negedge BE &&& _check_test, posedge TEST, DMY_SPC, notifier_a );
        $hold ( negedge BE &&& _check_test, negedge TEST, DMY_SPC, notifier_a );

        $setup ( posedge BUB, posedge TBE &&& _check_bubt, DMY_SPC, notifier_a );
        $setup ( negedge BUB, posedge TBE &&& _check_bubt, DMY_SPC, notifier_a );
        $hold ( posedge TBE &&& _check_bubt, posedge BUB, DMY_SPC, notifier_a );
        $hold ( posedge TBE &&& _check_bubt, negedge BUB, DMY_SPC, notifier_a );
        $setup ( posedge BUB, negedge TBE &&& _check_bubt, DMY_SPC, notifier_a );
        $setup ( negedge BUB, negedge TBE &&& _check_bubt, DMY_SPC, notifier_a );
        $hold ( negedge TBE &&& _check_bubt, posedge BUB, DMY_SPC, notifier_a );
        $hold ( negedge TBE &&& _check_bubt, negedge BUB, DMY_SPC, notifier_a );

        $setup ( posedge TEST, posedge TBE &&& _check_test, DMY_SPC, notifier_a );
        $setup ( negedge TEST, posedge TBE &&& _check_test, DMY_SPC, notifier_a );
        $hold ( posedge TBE &&& _check_test, posedge TEST, DMY_SPC, notifier_a );
        $hold ( posedge TBE &&& _check_test, negedge TEST, DMY_SPC, notifier_a );
        $setup ( posedge TEST, negedge TBE &&& _check_test, DMY_SPC, notifier_a );
        $setup ( negedge TEST, negedge TBE &&& _check_test, DMY_SPC, notifier_a );
        $hold ( negedge TBE &&& _check_test, posedge TEST, DMY_SPC, notifier_a );
        $hold ( negedge TBE &&& _check_test, negedge TEST, DMY_SPC, notifier_a );

        $period ( posedge BE &&& _check_periodn, DMY_SPC, notifier_period );
        $period ( posedge TBE &&& _check_periodt, DMY_SPC, notifier_period );

// <-- new spec

	if (BE&&WEB) ( BE => DO0 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&WEB) ( BE => DO1 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&WEB) ( BE => DO2 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&WEB) ( BE => DO3 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&WEB) ( BE => DO4 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&WEB) ( BE => DO5 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&WEB) ( BE => DO6 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&WEB) ( BE => DO7 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&WEB) ( TBE => DO0 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&WEB) ( TBE => DO1 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&WEB) ( TBE => DO2 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&WEB) ( TBE => DO3 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&WEB) ( TBE => DO4 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&WEB) ( TBE => DO5 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&WEB) ( TBE => DO6 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&WEB) ( TBE => DO7 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&!WEB) ( BE => DO0 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&!WEB) ( BE => DO1 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&!WEB) ( BE => DO2 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&!WEB) ( BE => DO3 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&!WEB) ( BE => DO4 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&!WEB) ( BE => DO5 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&!WEB) ( BE => DO6 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (BE&&!WEB) ( BE => DO7 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&!WEB) ( TBE => DO0 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&!WEB) ( TBE => DO1 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&!WEB) ( TBE => DO2 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&!WEB) ( TBE => DO3 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&!WEB) ( TBE => DO4 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&!WEB) ( TBE => DO5 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&!WEB) ( TBE => DO6 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );
	if (TBE&&!WEB) ( TBE => DO7 ) = ( DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC, DMY_SPC );

        // ------------ ( BUB,TEST,BUNRI => DO,TDO )= ?->"x" or "x"->? or Z
	(BUB=> DO0)=1;
	(BUB=> DO1)=1;
	(BUB=> DO2)=1;
	(BUB=> DO3)=1;
	(BUB=> DO4)=1;
	(BUB=> DO5)=1;
	(BUB=> DO6)=1;
	(BUB=> DO7)=1;
	(TEST=> DO0)=1;
	(TEST=> DO1)=1;
	(TEST=> DO2)=1;
	(TEST=> DO3)=1;
	(TEST=> DO4)=1;
	(TEST=> DO5)=1;
	(TEST=> DO6)=1;
	(TEST=> DO7)=1;
    endspecify
`endif  // NEC_RTL_SIM

/* ************************** */

// ----------------------------------------- timing error
`ifdef  NEC_RTL_SIM
`else
always @ ( notifier_w ) begin
    address=A;
    WriteAddressXCount;
    if (x_count !== 0) WriteAddX;
    else memory[address]=all_X;
    disable FUNCT_NORMAL;
    disable FUNCT_TEST;
    DO=all_X;
end

always @ ( notifier_a ) begin
    address=A;
    MemWriteX;
    disable FUNCT_NORMAL;
    disable FUNCT_TEST;
    DO=all_X;
end

always @ ( notifier_period ) begin
    if ( pre_csb !== 1 ) begin
    address=A;
    MemWriteX;
    disable FUNCT_NORMAL;
    disable FUNCT_TEST;
    DO=all_X;
    end
end

always @ ( notifier_wr ) begin
    address=A;
    if (_WEB!==1'b1) begin
        WriteAddressXCount;
        if (x_count !== 0) WriteAddX;
        else memory[address]=all_X;
    end
    disable FUNCT_NORMAL;
    disable FUNCT_TEST;
    DO=all_X;
end
`endif  // NEC_RTL_SIM

// ----------------------------------------- ram function

always @ ( _TEST ) begin
	   pre_BE = _BE ;
	   pre_TBE = _TBE ;
	   if ( _BUB!==1'b0 && (_BE!==1'b0 || _TBE!==1'b0)
					&& intcsb!==1'b1) begin
    		MemWriteX;
    		DO=all_X;
    		tmp_DO=all_X;
	   end
	   else if ( _TEST===1'bx) begin
    		DO=all_X;
    		tmp_DO=all_X;
    		if ( _CSB!==1'b1 && (_BE!==1'b0 || _TBE!==1'b0) ) begin
	  	   MemWriteX;
    	  	   tmp_DO=all_X;
          	   DO=all_X;
    		end
	   end
end

always @ ( _BUB ) begin
	   pre_BE = _BE ;
	   pre_TBE = _TBE ;
	   if ( _BUB===1'bx) begin
    		MemWriteX;
    		DO=all_X;
    		tmp_DO=all_X;
	   end
	   else if ( _TEST!==1'b1 && _BE!==1'b0 && intcsb!==1'b1) begin
    		MemWriteX;
    		DO=all_X;
    		tmp_DO=all_X;
	   end
	   else if ( _TEST!==1'b0 && _TBE!==1'b0 && intcsb!==1'b1) begin
    		MemWriteX;
    		DO=all_X;
    		tmp_DO=all_X;
	   end
	   else if ( _BUB===1'b0) begin
		DO=all_X;
	   end
end

// ---------------------------------------- _CSB change on BE/TBE=X
always @ ( _CSB ) begin
  if ((_BE===1'bx) && (_CSB!==1'b1) && (_BUB!==1'b0) && (_TEST!==1'b1)) begin
    MemWriteX;
    DO=all_X;
    tmp_DO=all_X;
  end
  if ((_TBE===1'bx) && (_CSB!==1'b1) && (_BUB!==1'b0) && (_TEST!==1'b0)) begin
    MemWriteX;
    DO=all_X;
    tmp_DO=all_X;
  end
end
// ---------------------------------------- _WEB change on BE/TBE=X
always @ ( _WEB ) begin
  if ((_BE===1'bx) && (_CSB!==1'b1) && (_WEB!==1'b1) 
			&& (_BUB!==1'b0) && (_TEST!==1'b1)) begin
    MemWriteX;
    DO=all_X;
    tmp_DO=all_X;
  end
  if ((_TBE===1'bx) && (_CSB!==1'b1) && (_WEB!==1'b1)
			&& (_BUB!==1'b0) && (_TEST!==1'b0)) begin
    MemWriteX;
    DO=all_X;
    tmp_DO=all_X;
  end
end

// ---------------------------------- function
always @ ( _BE ) begin : FUNCT_NORMAL
  if ( (_BUB===1'b1) && (_TEST===1'b0)) begin // --- normal mode
     casez ( {pre_BE,_BE} )
	2'b01 : begin // -------------- 0->1 posedge
           address=A;
           intcsb=_CSB;
	   ////
	   if ( _CSB===1'b0) begin
	      if (address > (WORD-1)) PrintWMsg_1;
	      WriteAddressXCount;
	      ///
	      if (x_count !== 0) begin
		WriteAddX;
            	DO=all_X;
	      end
	      ///
	      else begin
	         //
	         if ( _WEB===1'b0) begin
            	    memory[address]=DI;
            	    tmp_DO=DI;

// add
`ifdef  NEC_RTL_SIM
                   #(tACC_w)  DO = tmp_DO;
`else
                   if ( DO === tmp_DO ) begin
                       DO=tmp_DO;
                   end
                   else begin
                     if (DO===all_X) begin
                       DO=tmp_DO;
                     end
                     else begin
			DO={BIT{1'bx}};
			#1;
			if (DO===all_X) begin
			   DO=tmp_DO;
			end
                     end
	           end
`endif  // NEC_RTL_SIM
                 end
// add
	         //
	         else if ( _WEB===1'b1) begin
            	    tmp_DO=memory[address];

// add
`ifdef  NEC_RTL_SIM
                   #(tACC_r)  DO = tmp_DO;
`else
                   if ( DO === tmp_DO ) begin
                       DO=tmp_DO;
                   end
                   else begin
                     if (DO===all_X) begin
                       DO=tmp_DO;
                     end
                     else begin
			DO={BIT{1'bx}};
			#1;
			if (DO===all_X) begin
			   DO=tmp_DO;
			end
		     end
	           end
`endif  // NEC_RTL_SIM
                 end
// add
	         //
	         else begin
            	    memory[address]=all_X;
    		    tmp_DO=all_X;
                    DO=all_X;
	         end
	         //
	      end
	      ///
	   end
	   ////
	   else if ( _CSB===1'bx) begin
	         MemWriteX;
    		 tmp_DO=all_X;
                 DO=all_X;
	   end
	   ////
	end

        2'bx1 ,
        2'b?x : begin // -------------- x edge
           intcsb=1'bx;
	   if ( _CSB!==1'b1) begin
	         MemWriteX;
    		 tmp_DO=all_X;
                 DO=all_X;
	   end
	end
     endcase
	   pre_BE = _BE ;
  end
  else if ( (_BUB===1'b1) && (_TEST===1'bx)) begin // --- unkown mode
    if ( _CSB!==1'b1 && _BE!==1'b1) begin
	  pre_BE = _BE ;
          intcsb=1'bx;
	  MemWriteX;
    	  tmp_DO=all_X;
          DO=all_X;
    end
  end

end

// ---------------------------------- Test mode function (mode==4 only)
always @ ( _TBE ) begin : FUNCT_TEST
  if ( (_BUB===1'b1) && (_TEST===1'b1)) begin // --- normal mode
     casez ( {pre_TBE,_TBE} )
	2'b01 : begin // -------------- 0->1 posedge
           address=A;
           intcsb=_CSB;
	   ////
	   if ( _CSB===1'b0) begin
	      if (address > (WORD-1)) PrintWMsg_1;
	      WriteAddressXCount;
	      ///
	      if (x_count !== 0) begin
		WriteAddX;
            	DO=all_X;
	      end
	      ///
	      else begin
	         //
	         if ( _WEB===1'b0) begin
            	    memory[address]=DI;
            	    tmp_DO=DI;

// add
`ifdef  NEC_RTL_SIM
                   #(tACC_w)  DO = tmp_DO;
`else
                   if ( DO === tmp_DO ) begin
                       DO=tmp_DO;
                   end
                   else begin
                     if (DO===all_X) begin
                       DO=tmp_DO;
                     end
                     else begin
			DO={BIT{1'bx}};
			#1;
			if (DO===all_X) begin
			   DO=tmp_DO;
			end
                     end
	           end
`endif  // NEC_RTL_SIM
                 end
// add
	         //
	         else if ( _WEB===1'b1) begin
            	    tmp_DO=memory[address];

// add
`ifdef  NEC_RTL_SIM
                   #(tACC_r)  DO = tmp_DO;
`else
                   if ( DO === tmp_DO ) begin
                       DO=tmp_DO;
                   end
                   else begin
                     if (DO===all_X) begin
                       DO=tmp_DO;
                     end
                     else begin
			DO=all_X;
			#1;
			if (DO===all_X) begin
			   DO=tmp_DO;
			end
		     end
	          end
`endif  // NEC_RTL_SIM
                 end
// add
	         //
	         else begin
            	    memory[address]=all_X;
    		    tmp_DO=all_X;
                    DO=all_X;
	         end
	         //
	      end
	      ///
	   end
	   ////
	   else if ( _CSB===1'bx) begin
	         MemWriteX;
    		 tmp_DO=all_X;
                 DO=all_X;
	   end
	   ////
	end

        2'bx1 ,
        2'b?x : begin // -------------- x edge
           intcsb=1'bx;
	   if ( _CSB!==1'b1) begin
	         MemWriteX;
    		 tmp_DO=all_X;
                 DO=all_X;
	   end
	end
     endcase
	   pre_TBE = _TBE ;
  end
  else if ( (_BUB===1'b1) && (_TEST===1'bx)) begin // --- unkown mode
    if ( _CSB!==1'b1 && _TBE!==1'b1) begin
	  pre_TBE = _TBE ;
          intcsb=1'bx;
	  MemWriteX;
    	  tmp_DO=all_X;
          DO=all_X;
    end
  end

end

// ---------------------------------- Test mode function (mode==4 only)

/* ----------------------------------- "x" conunt task */
task WriteAddressXCount;
begin
    x_count=0;                              // write address "x" count
    for (i=0;i<ADD_BIT;i=i+1) begin
        if (address[i]===1'bx) begin
            x_add_num[x_count]=i;
            x_count=x_count+1;
        end
    end
end
endtask

/* ----------------------------------- find address & write task */
task WriteAddX;

reg[ADD_BIT-1:0] new_address;
reg[ADD_BIT-1:0] b_count,num_count;
integer j,k,m;

begin
    new_address=address;
    b_count=(2<<(x_count-1))-1;
    num_count={ADD_BIT{1'b0}};
    for (j=0;j<=b_count;j=j+1) begin
        for (k=0;k<x_count;k=k+1) begin
            new_address[x_add_num[k]] = num_count[k];
            memory[new_address]=all_X;
        end
        num_count=num_count+1;
    end
end
endtask

/* ------------ write x in all address */
task MemWriteX;
integer i;
begin
  for(i=0;i<WORD;i=i+1) memory[i]=all_X;
end
endtask

/* ------------ access invalid address warning message */
task PrintWMsg_1;
begin
	//$display( $time,,"%m #### You are accessing the invalid address, please read the users manual. There is same possibility of that quiescent current(iddq) will flows.\n");
	$display( $time,,"%m #### You are accessing the invalid address.\n");
end
endtask

`ifdef  NEC_RTL_SIM
task  PrintRTLMsg;
begin
	$display("===============================================");
	$display("Behavior Function Mode : WBSRAMSHD16384W8C5");
	$display("Instance       : %m");
	$display("Abstract Delay :");
	$display("   tACC (Read) : %d",tACC_r);
	$display("   tACC (Write): %d",tACC_w);
 	$display("===============================================");
end
endtask
`endif


/* ************************** */

endmodule
`ifdef verifault
    `nosuppress_faults
    `disable_portfaults
`endif
`endcelldefine
