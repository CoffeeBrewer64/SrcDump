d44 1
a44 1
#define CONFIG_USB_DEBUG	/* XXX force this for now */
d615 4
a618 1
    dbg(__FUNCTION__ " - minor %d, returning bytes = %d", dev->minor, total);
d708 2
a709 2
		err(__FUNCTION__ " - nonzero write bulk status received: %d",
		    dev->write_urb->status);
a812 2
char null_setup[8];

d902 1
a902 1
			buffer_size = 1024;
d927 1
a927 1
			buffer_size = 1024;
