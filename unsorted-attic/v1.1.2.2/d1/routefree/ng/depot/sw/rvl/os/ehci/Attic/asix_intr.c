a512 2
//#define TWO_DONGLE_TEST 1

a521 3
#ifdef TWO_DONGLE_TEST
    IOSFd fd1;
#endif
a525 3
#ifdef TWO_DONGLE_TEST
    printf("ASIX interrupt transfer test: Needs TWO Asix dongles\n");
#endif
d527 1
a528 4
#ifdef TWO_DONGLE_TEST
    __registerInsertionHandlerTest("/dev/usb/ehc", 0x0b95, 0x7720);
    fd1 = IOS_Open("/dev/usb/ehc/0b95/7720", 0);
#endif
a533 3
#ifdef TWO_DONGLE_TEST
    initEth(fd1, __eeprom.primaryPhyInfo & AX_EEPROM_PHYID_MASK, &setting);
#endif
a534 3
#ifdef TWO_DONGLE_TEST
    __intrTransferTest(fd1);
#endif
