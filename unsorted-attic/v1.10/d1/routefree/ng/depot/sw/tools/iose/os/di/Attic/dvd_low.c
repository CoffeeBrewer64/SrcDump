d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.9 2006/01/10 20:40:59 craig Exp $"
d314 1
a314 1
    case DI_NOTIFY_RESET:
a346 5
    case DI_GET_COVER_STATUS:
        dvdCoverStatus = DICoverReg;
        transactionNeeded = false;
        break;

d381 1
a381 1
    case DI_READ_DISK_ID:
d425 1
a425 1
    case DI_READ_DVD_PHYSICAL:
d437 1
a437 1
    case DI_READ_DVD_COPYRIGHT:
d449 1
a449 1
    case DI_READ_DVD_DISC_KEY:
d461 1
a461 1
    case DI_READ_RVL:
d523 1
a523 1
        DILength = sizeof(DVDLowDriverSer);
d528 6
d551 1
a551 1
    case DI_WAIT_FOR_COVER_CLOSE:
d589 1
a589 1
        switch(inMesg.mesgType) {
d592 1
a592 1
            if (inMesg.commandNum == currentCommandNum) {
d599 1
d617 2
a618 1
    if (commandTerminated && inMesg.mesgType == DI_MESG_TRANS_COMPLETE) {
d622 2
a623 1
    } else if (commandTerminated && inMesg.mesgType == DI_MESG_TRANS_ERROR) {
d711 1
a711 1
        switch(inMesg.mesgType) {
d714 1
a714 1
            if (inMesg.commandNum == currentCommandNum) {
d724 1
d748 2
a749 1
    if (commandTerminated && inMesg.mesgType == DI_MESG_TRANS_COMPLETE) {
d752 2
a753 1
    } else if (commandTerminated && inMesg.mesgType == DI_MESG_TRANS_ERROR) {
d768 1
d781 1
a781 1
        if (     inMesg.mesgType == DI_MESG_COVER
d793 1
a793 1
    diIOSMessage_t      diIOSMessage;
d805 3
a807 2
    diIOSMessage.inMesg.mesgType = DI_MESG_TIMEOUT;
    diIOSMessage.inMesg.commandNum = currentCommandNum;
d813 1
a813 1
                                    diIOSMessage.mesg);
