d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.38 2006/03/04 05:28:32 craig Exp $"
d856 1
a856 1
        DPRINT2("(handleDICommand) DIStatus(2): 0x%x\n", readGoodDIStatus());
d871 1
a871 1
        DPRINT2("(handleDICommand) DIStatus(3): 0x%x\n", readGoodDIStatus());
a1147 1

d1151 3
a1153 1
 * but don't recycle timeout messages.
d1169 1
a1169 10
            DPRINT ("(clearTimeoutsFromQueue) Queue (now) empty\n");
            if (firstMesgSet == true) {
                DPRINT ("(clearTimeoutsFromQueue) Re-enqueuing message\n");
                sendError = IOS_SendMessage(queueId,
                                            (IOSMessage) firstMesgPtr.otherMesg,
                                            IOS_MESSAGE_NOBLOCK);
                if (sendError != IOS_ERROR_OK) {
                    diFatalError("(clearTimeoutsFromQueue) Can't send message");
                }
            }
d1177 1
a1177 1
            DPRINT ("(clearTimeoutsFromQueue) A\n");
d1180 8
d1196 1
a1196 1
            DPRINT ("(clearTimeoutsFromQueue) B\n");
d1202 2
a1203 1
                DPRINT2("(clearTimeoutsFromQueue) JamMessage returns %d\n", sendError);
d1209 1
a1209 1
            DPRINT ("(clearTimeoutsFromQueue) C\n");
d1214 2
a1215 1
                DPRINT2("(clearTimeoutsFromQueue) SendMessage returns %d\n", sendError);
d1224 46
