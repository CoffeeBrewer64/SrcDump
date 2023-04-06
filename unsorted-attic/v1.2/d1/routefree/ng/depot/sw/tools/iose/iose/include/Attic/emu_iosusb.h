/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */
#ifndef __EMU_IOSUSB_H__
#define __EMU_IOSUSB_H__
/* Must match values appropriate for local linux system */
#define USB_EMU_URB_DISABLE_SPD 1 
#define USB_EMU_URB_ISO_ASAP    2 
#define USB_EMU_URB_QUEUE_BULL  0x10
                                                                                
#define USB_EMU_URB_ISO             0
#define USB_EMU_URB_INTERRUPT       1
#define USB_EMU_URB_CONTROL         2
#define USB_EMU_URB_BULK            3
                                                                                
#endif /* __EMU_IOSUSB_H__ */
