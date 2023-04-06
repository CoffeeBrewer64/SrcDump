d1 1
a1 1
#ident "$Id$"
d38 5
a42 1
/* Assumes current command byte contents are 0 */
d62 6
d92 90
d211 7
d227 6
a232 2
void
handleDiCommand()
d239 2
d247 1
a247 1
    switch (diCommand.the_command) {
d252 1
d254 1
d261 2
a262 2
        setDiCommandWord2(diCommand.argument1);
        setDiCommandWord3(diCommand.argument2);
d264 2
a265 1
             startTimedTransfer(readLengthToTimeout(diCommand.argument2));
d271 1
a271 1
        setDiCommandWord2(diCommand.argument1);
d273 6
d283 2
a284 1
        setDiEjectBit(diCommand.argument1);
d286 1
d291 1
d294 1
d298 8
d307 3
a309 2
        setDiCommandByte(diCommand.the_command);
        setDiAudioSubCode(diCommand.argument1);
d311 1
d316 2
a317 2
        setDiAudioBufferSwitch(diCommand.argument1);
        setDiAudioBufferSize(diCommand.argument2);
d320 114
d440 5
d482 1
a482 2
        sendError = IOS_SendMessage(dvdDriverOutQueue,
                                    DI_ERR_NO_ERROR, IOS_MESSAGE_BLOCK);
d489 1
d491 45
a535 2
    if (sendError != IOS_ERROR_OK) {
        diFatalError ("(handleDiCommand) send of NO_ERROR failed");
d538 10
