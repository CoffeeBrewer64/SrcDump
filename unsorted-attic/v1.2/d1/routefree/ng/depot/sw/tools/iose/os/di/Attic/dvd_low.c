d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.1 2005/11/22 22:18:42 craig Exp $"
d36 1
d53 1
a53 1
    DICmdBuf[0] |= (subCommand << 6);
d201 11
d214 4
d219 1
d234 12
d475 1
d479 1
d513 1
d516 2
a517 2
        /* FIXME */
        abort();
a518 2
        sendError = IOS_SendMessage(dvdDriverOutQueue, DI_ERR_TIMEOUT,
                                    IOS_MESSAGE_BLOCK);
d522 1
a522 1
}
a525 1
#ifdef notused
d530 2
a531 2
 *                     address reside in
 *   offset: the word offset of the address within the block
d533 1
a533 1
static inline uint32_t
d535 3
a537 1
                      uint32_t *physicalBlockNum, uint32_t *offset)
d543 1
a543 1
    *offset = (virtualSubBlockNum % 31) * 256 + (virtualAddr & 0xFF);
d548 1
a548 1
 *        addr is virtual disk address to read
a553 15
uint32_t
doReadCheckHashedBlock(uint8_t *dest, const uint32_t blockNum, const int len)
{
    diCommand_t         readCommand;
    uint32_t            commandResult;

    readCommand.the_command = DI_READ_COMMAND;
    readCommand.argument1   = blockNum * WORDS_PER_BLOCK;
    readCommand.argument2   = WORDS_PER_BLOCK;
    DIDmaDestAddr           = (uint32_t) dest;
    commandResult = handleDiCommand(readCommand);
    if (commandResult != DI_ERR_NO_ERROR) {
        return(commandResult);
    }
}
d556 1
a556 1
doRvlRead(uint8_t *dest_addr, uint32_t wordLength, uint32_t wordOffset)
d558 1
a558 1
    uint32_t firstBlockNum, offset;
d560 2
a561 1
    diskVirtualtoPhysical(wordOffset, firstBlockNum, offset);
a563 2
#endif

d567 1
a567 3
#ifdef notdef

static void
d570 1
d572 2
a573 2
    dvdState.currentCommand = dvdRequestError;
    startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d576 2
d582 3
a584 2
static uint32_t
doDiskRequestError(dvdStatus &driveStatus, uint32_t &errorCode)
d586 5
d592 1
d596 1
a596 1
    DiCmdBuf[0] = 0;
d598 3
a600 1
    sendRequestError();
d621 7
d645 6
d652 2
a653 2
        sendError = IOS_SendMessage(dvdDriverOutQueue,
                                    DI_ERROR_NO_ERROR, IOS_MESSAGE_BLOCK);
d655 5
d661 1
a661 8
    else {
    }
    if (sendError != IOS_ERROR_OK) {
        diFatalError ("(handleDiCommand) send of NO_ERROR failed");
    }

}
#endif
d682 1
a682 1
}
