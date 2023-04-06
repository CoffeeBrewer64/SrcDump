d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.10 2006/01/13 21:35:53 craig Exp $"
d46 2
a600 1
            freeDiOtherMesg(inMesg.otherMesg);
d606 1
a725 1
            freeDiOtherMesg(inMesg.otherMesg);
a793 1
    diOtherMesg_t       *timeoutMesg;
d805 2
a806 3
    timeoutMesg = newDiOtherMesg();
    timeoutMesg->mesgType = DI_MESG_TIMEOUT;
    timeoutMesg->commandNum = currentCommandNum;
d812 1
a812 1
                                    (IOSMessage) timeoutMesg);
d822 49
