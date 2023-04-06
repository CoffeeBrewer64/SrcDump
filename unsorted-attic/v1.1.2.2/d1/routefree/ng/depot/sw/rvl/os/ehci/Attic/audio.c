d277 1
a277 8
    printf("test: suspend/resume device loop\n");
    while (1) {
        IUSB_SuspendDevice(fd0);
        usleep(500000);
        IUSB_ResumeDevice(fd0);
        usleep(500000);
    }
    //    __isoTest(fd0);
