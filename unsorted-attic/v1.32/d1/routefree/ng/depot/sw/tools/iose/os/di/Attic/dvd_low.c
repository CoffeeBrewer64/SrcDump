d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.31 2006/02/28 04:03:46 craig Exp $"
d312 1
a312 1
    tempVal  = readDIStatus();
d330 1
a330 1
    tempVal  = readDIStatus();
d353 1
a353 1
        writeDIControl(DI_TRANSFER);
d368 1
a368 1
    tempVal  = readDICoverReg();
d392 1
a392 1
    tempVal  = readDICoverReg();
d412 1
a412 1
    tempVal     = readDICoverReg();
d431 1
a431 1
    tempVal   = readDIStatus();
d451 1
a451 1
    tempVal   = readDIStatus();
d463 1
a463 1
    tempVal   = readDIStatus();
