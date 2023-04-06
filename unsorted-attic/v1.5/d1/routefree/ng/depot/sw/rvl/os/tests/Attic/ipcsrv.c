d299 1
a299 9
        if ((busRd32(ACR_INTMASK_TRUSTED) & ACRINTSTS_ACRIPCIOP_MASK) == 0) {

            IPC_LOG("INTSTS1: %x INTSTS: %x INTMSK: %x\n", 
                busRd32(ACR_IOPINTSTS_TRUSTED),
                busRd32(ACR_INTMASK_TRUSTED),
                IOS_ReadIPCIOPCtrlReg());

            IOS_ClearAndEnableIPCIOPIntr();
            IPC_LOG("INTSTS2: %x INTSTS: %x INTMSK: %x\n", 
a302 1
        }
