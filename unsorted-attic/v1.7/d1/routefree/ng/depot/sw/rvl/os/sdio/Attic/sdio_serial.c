d12 1
a12 1
#ident "$Id: sdio_serial.c,v 1.6 2006/03/18 01:16:12 gbarnard Exp $"
d325 1
a325 1
    u32 pri = IOS_GetThreadPriority(0)+1; //100; /* max prioroty for irq */ //IOS_GetThreadPriority(0);
d537 1
a537 1
			//printf("   ===> IRQ in slot 0x%04X\n",(u32)dwIntStatus);
d547 1
a547 1
		 			//printk (KERN_INFO "%s: norm int status = 0x%x\n", __FUNCTION__,
d715 4
a718 2
    caddr_t buffer;
    int buf_len;
d1011 1
a1011 1
        memset(&reg_op, 0, sizeof(reg_op));
d1017 22
a1038 17
        buf_len = (reg_op.blk_num == 0) ? reg_op.blk_size 
            : reg_op.blk_num * reg_op.blk_size;
        buffer = kmalloc(buf_len, GFP_KERNEL|GFP_DMA);
        //printf("   buffer=%x\n",buffer);
        memset (buffer, 0, buf_len);
        status = read_card_data(sdh_global, reg_op.dev, reg_op.function,
                                reg_op.reg, (u32)buffer, reg_op.blk_size, 
                                reg_op.blk_num, reg_op.dma, reg_op.busy);
        if (reg_op.buffer) {
            if (copy_to_user(reg_op.buffer, buffer, buf_len)) {
                SER_DEBUG (DEBUG_SER_ERR, "%s: copy_to_user failed\n",
                        __FUNCTION__);
                return IOS_ERROR_ACCESS;
            }
        }

        kfree (buffer);
d1042 1
a1042 1
        memset(&reg_op, 0, sizeof(reg_op));
d1048 22
a1069 16
        buf_len = (reg_op.blk_num == 0) ? reg_op.blk_size 
            : reg_op.blk_num * reg_op.blk_size;
        buffer = kmalloc(buf_len, GFP_KERNEL|GFP_DMA);
        //printf("   buffer=%x\n",buffer);
        
        if (reg_op.buffer) {
            if (copy_from_user(buffer, reg_op.buffer, buf_len)) {
                SER_DEBUG (DEBUG_SER_ERR, "%s: copy_from_user failed\n",
                        __FUNCTION__);
                return IOS_ERROR_ACCESS;
            }
        }
        status = write_card_data(sdh_global, reg_op.dev, reg_op.function,
                                 reg_op.reg, (u32)buffer, reg_op.blk_size, 
                                 reg_op.blk_num, reg_op.dma, reg_op.busy);
        kfree (buffer);
