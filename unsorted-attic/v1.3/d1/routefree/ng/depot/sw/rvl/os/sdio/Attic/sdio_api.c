d12 1
a12 1
#ident "$Id: sdio_api.c,v 1.2 2006/03/15 01:10:15 gbarnard Exp $"
d113 2
a114 1
		
a128 1
			IOSMessage msg;
d133 1
a133 1
			IOS_ReceiveMessage(sdrmQidr, &msg, IOS_MESSAGE_BLOCK);
d136 1
a136 1
		return 0;
