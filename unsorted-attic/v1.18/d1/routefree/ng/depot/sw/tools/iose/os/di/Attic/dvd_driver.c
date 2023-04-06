d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.17 2006/01/28 03:38:11 craig Exp $"
d69 1
a69 1
IOSError        DiIoctl(IOSResourceIoctl* const ioctlMesg);
d93 1
a93 6
    IOSError            sendError, receiveError;
    uint32_t            commandErrorCode;
    /*
    char                highStack[HIGH_STACK_SIZE];
    IOSThreadId         highThreadId;
    */
a115 18
    /*
     * TODO - Remove the following commented out code - only
     * needed for debugging
     */

    /*
    highThreadId = IOS_CreateThread(dvd_high, NULL, highStack,
                                    HIGH_STACK_SIZE, 50);
    if (highThreadId < 0) {
        printf ("Error: could not create high thread - exiting\n");
        IOS_DestroyThread(0);
    }
    if (IOS_StartThread(highThreadId) != IOS_ERROR_OK) {
        printf ("Error: could not start high thread\n");
        IOS_DestroyThread(0);
    }
    */

d136 3
a138 3
            sendError = DiOpen();
            printf ("(dvd_driver) Open returns: %d\n", sendError);
            IOS_ResourceRespond(inMesg.resourceMesg, sendError);
d144 2
a145 2
            sendError = DiClose((DiFileDescriptor_t *) inMesg.resourceMesg->handle);
            IOS_ResourceRespond(inMesg.resourceMesg, sendError);
d149 2
a150 3
            sendError = DiIoctl(&(inMesg.resourceMesg->args.ioctl));
            // FIXME - what value should sendError really have?
            IOS_ResourceRespond(inMesg.resourceMesg, sendError);
d172 1
a172 10
        case DI_MESG_COMMAND:
            commandErrorCode = handleDiCommand(&interfaceDiCommand);
            sendError = IOS_SendMessage(dvdDriverOutQueue,
                                        commandErrorCode, IOS_MESSAGE_BLOCK);
            if (sendError != IOS_ERROR_OK) {
                diFatalError ("(handleDiCommand) send of NO_ERROR failed");
            }
            break;

        case DI_MESG_COVER:
d338 6
a343 1
IOSError
d386 1
d396 1
a396 1
        diFatalError ("Do something here\n");
d400 1
a400 2
        // TODO
        diFatalError ("Do something here\n");
a403 1
        assert(ioctlMesg->outLen >= sizeof(uint32_t));
d423 1
a423 1
            commandResult = handleDiCommand(command);
a450 1
        * (uint32_t *) ioctlMesg->outPtr = ioctlReturn;
d453 1
a453 1
    return(IOS_ERROR_OK);
