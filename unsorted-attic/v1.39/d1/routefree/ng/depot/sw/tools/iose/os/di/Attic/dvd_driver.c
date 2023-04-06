d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.38 2006/03/01 21:06:48 craig Exp $"
a113 1
    uint32_t		statusVal;
d188 1
a188 2
	    statusVal = readDIStatus();
            DPRINT2 ("(dvd_driver) Status reg val is: 0x%x\n", statusVal);
d458 1
a458 1
        tmpVal  = readDICoverReg();
d466 1
a466 1
        tmpVal  = readDICoverReg();
d474 1
a474 1
        tmpVal  = readDICoverReg();
