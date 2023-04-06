d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.40 2006/03/05 00:31:24 craig Exp $"
d1225 6
a1230 1
#ifdef notdone
d1233 1
a1233 4
 * timeout messages.  Recycle all non-timeout messages,
 * but don't recycle timeout messages.  Stop when we dequeue
 * the first message seen, which we then need to jam back
 * onto the front.
d1252 1
a1252 1
    mesgArray = dvdMemAlloc(sizeof(IOSMessage) * queueLeng);
d1259 3
a1261 3
            mesgArray[mesgNum++] = inMesgPtr;
            DPRINT ("(clearTimeoutsFromQueue) Storing message #%d\n",
                     mesgNum - 1);
d1266 13
a1278 3
    } while (receiveError != IOS_ERROR_QEMPT && mesgNum < queueLen);
    for (int i = 0; i 
} // clearTimeoutsFromQueue
