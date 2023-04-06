d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.3 2005/12/06 02:27:06 craig Exp $"
d23 1
d32 2
d38 13
a50 3
static IOSTimerId startTimedTransfer(IOSTime duration);
static void doDiskRequestError(dvdStatus_t *status, uint32_t *errorCode);
static void doWaitForCoverClose(void);
d175 1
a175 1
    DICmdBuf[0] |= (subCode & 0x1) << 15;
d181 1
a181 1
    DICmdBuf[0] |= (clearVal & 0x1) << 9;
d187 1
a187 1
    DICmdBuf[0] |= (ENAVal & 0x1) << 8;
d193 1
a193 1
    DICmdBuf[0] |= (subCode & 0x3) << 8;
d197 1
a197 1
setDiCommandWord2(const uint32_t command_word)
d203 1
a203 1
setDiCommandWord3(const uint32_t command_word)
d209 1
a209 1
diStartTransfer(void)
d211 6
a216 1
    DIControl |= DI_TRANSFER;
d280 1
d296 1
d307 2
a308 17
    case DI_READ_DISK_ID:
        setDiCommandByte(DI_READ_CMD);
        setDiReadSubCommandByte(DI_DISC_ID_READ);
        DIDmaDestAddr = diCommand->argument1;
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
        transactionNeeded = true;
        break;

    /* This reads the raw data from a RVL game disk */
    case DI_READ_CMD:
        setDiCommandByte(DI_READ_CMD);
        setDiReadSubCommandByte(DI_NORMAL_READ);
        setDiCommandWord2(diCommand->argument1);
        setDiCommandWord3(diCommand->argument2);
        commandTimeoutId =
             startTimedTransfer(readLengthToTimeout(diCommand->argument2));
        transactionNeeded = true;
d311 2
a312 28
    /* FIXME - Need a longer timeout here? */
    case DI_SEEK_CMD:
        setDiCommandByte(DI_SEEK_CMD);
        setDiCommandWord2(diCommand->argument1);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
        transactionNeeded = true;
        break;

    case DI_WAIT_FOR_COVER_CLOSE:
        enableCoverInterrupt();
        doWaitForCoverClose();
        transactionNeeded = false;
        break;

    case DI_STOP_MOTOR_CMD:
        setDiCommandByte(DI_STOP_MOTOR_CMD);
        setDiEjectBit(diCommand->argument1);
        setDiSavingBit(diCommand->argument2);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
        transactionNeeded = true;
        break;

    case DI_INQUIRY_CMD:
        setDiCommandByte(DI_INQUIRY_CMD);
        DIDmaDestAddr = diCommand->argument1;
        setDiCommandWord2(0);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
        transactionNeeded = true;
d318 4
a321 3
        setDiCommandWord2(diCommand->argument3);
        setDiCommandWord3(diCommand->argument2);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d328 3
a330 2
        setDiCommandWord2(0);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d339 2
a340 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d350 52
d408 1
a408 1
        setDiCommandWord2(0);
d411 2
a412 1
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d420 2
d423 2
a424 3
        setDiDVDConfigValue(diCommand->argument3);
        setDiCommandWord3(0);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d433 1
d435 2
a436 2
        setDiCommandWord3(0);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d445 2
d448 1
a448 2
        setDiCommandWord3(0);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d457 2
d460 1
a460 2
        setDiCommandWord3(0);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d464 6
d473 1
d475 2
d478 15
a492 3
        setDiReportKeyLSN(diCommand->argument3);
        setDiCommandWord3(0);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d496 4
a499 5
    case DI_OFFSET_CMD:
        setDiCommandByte(DI_OFFSET_CMD);
        setDiOffsetSubCode(diCommand->argument1);
        setDiCommandWord2(diCommand->argument2);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d503 6
a508 3
    case DI_STOP_LASER_CMD:
        setDiCommandByte(DI_STOP_LASER_CMD);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d512 5
a516 4
    case DI_READ_DISC_INFO_CMD:
        setDiCommandByte(DI_READ_DISC_INFO_CMD);
        DIDmaDestAddr = diCommand->argument1;
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d524 3
a526 2
        setDiSerMeasENA(diCommand->argument2);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d530 5
a534 3
    case DI_REQUEST_DISC_STATUS_CMD:
        setDiCommandByte(DI_REQUEST_DISC_STATUS_CMD);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d538 6
a543 3
    case DI_REQUEST_RETRY_NUMBER_CMD:
        setDiCommandByte(DI_REQUEST_RETRY_NUMBER_CMD);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
d547 4
a550 5
    case DI_SET_MAXIMUM_ROTATION_CMD:
        setDiCommandByte(DI_SET_MAXIMUM_ROTATION_CMD);
        setDiMaxRotationSubcode(diCommand->argument1);
        commandTimeoutId = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
        transactionNeeded = true;
d554 3
a556 1
        diFatalError("Unhandled case in handleDiCommand");
d617 8
a624 18
/*
 * INPUT: the virtual word address (byte address >> 2)
 * OUTPUT:
 *   physicalBlockNum: which 32K physical block does the
 *                     WORD address reside in
 *   offset: the WORD offset of the address within the block
 */
static inline void
diskVirtualToPhysical(const uint32_t virtualWordAddr,
                      uint32_t *physicalBlockNum,
                      uint32_t *physcialSubBlockNum,
                      uint32_t *offset)
{
    uint32_t            virtualSubBlockNum;

    virtualSubBlockNum = virtualWordAddr >> 8;
    *physicalBlockNum = virtualSubBlockNum / 31;
    *offset = (virtualSubBlockNum % 31) * 256 + (virtualWordAddr & 0xFF);
d627 2
d630 2
a631 3
 * Input: dest is destination for data
          blockNum is the physical block number to read
 *        len is the length to read
d634 32
a665 1
#define WORDS_PER_BLOCK 8 * 1024
d667 4
d672 14
a685 4
void
doRvlRead(uint8_t *dest_addr, uint32_t byteLength, uint32_t virtWordOffset)
{
    uint32_t    physBlockNum, physSubBlockNum, physOffset;
d687 4
a690 3
    diskVirtualToPhysical(virtWordOffset, &physBlockNum,
                          &physSubBlockNum, &physOffset);
}
d692 9
a700 1
/*************************************************************/
d702 12
d715 1
a715 8
static IOSTimerId
sendRequestError(void)
{
    IOSTimerId  return_val;
    setDiCommandByte(DI_REQUEST_ERROR_CMD);
    return_val = startTimedTransfer(DI_IMM_COMMAND_TIMEOUT);
    return(return_val);
}
d831 1
a831 1
startTimedTransfer(IOSTime duration)
d849 1
a849 1
    diStartTransfer();
