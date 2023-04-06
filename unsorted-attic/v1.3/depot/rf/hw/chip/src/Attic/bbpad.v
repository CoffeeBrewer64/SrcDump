d22 9
a30 7
	pad_sm_ce, sm_ce,
	pad_sm_ale, sm_ale,
	pad_sm_cle, sm_cle,
	pad_sm_re, sm_re,
	pad_sm_we, sm_we,
	pad_sm_wp, sm_wp,
	pad_sm_ryby, sm_ryby,
d38 1
d88 21
a108 14
	output pad_sm_ce;			// chip enable pin;
	input sm_ce;				// chip enable pin;
	output pad_sm_ale;			// address latch enable pin;
	input sm_ale;				// address latch enable pin;
	output pad_sm_cle;			// command latch enable pin;
	input sm_cle;				// command latch enable pin;
	output pad_sm_re;			// read eanble pin;
	input sm_re;				// read eanble pin;
	output pad_sm_we;			// write eanble pin;
	input sm_we;				// write eanble pin;
	output pad_sm_wp;			// write protect pin;
	input sm_wp;				// write protect pin;
	input pad_sm_ryby;			// ready/busy pin;
	output sm_ryby;				// ready/busy pin;
d124 2
d378 29
a406 1
	// XXX instantiate real io cells;
d408 2
a409 7
	assign pad_sm_ce = sm_ce;
	assign pad_sm_ale = sm_ale;
	assign pad_sm_cle = sm_cle;
	assign pad_sm_re = sm_re;
	assign pad_sm_we = sm_we;
	assign pad_sm_wp = sm_wp;
	assign pad_sm_ryby = sm_ryby;
d411 18
a428 1
	// XXX instantiate real io cells;
d430 11
a440 7
	assign pad_fl_ce = fl_ce;
	assign pad_fl_ale = fl_ale;
	assign pad_fl_cle = fl_cle;
	assign pad_fl_re = fl_re;
	assign pad_fl_we = fl_we;
	assign pad_fl_wp = fl_wp;
	assign pad_fl_ryby = fl_ryby;
d442 8
