d44 1
a44 1
//#define CONFIG_USB_DEBUG
d126 1
a126 1
	int			bulk_in_size;		/* the full size of the read buffer */
d400 1
a400 1
	spin_lock(&dev->lock);
d404 1
a404 1
	spin_unlock(&dev->lock);
d429 1
a429 1
	spin_lock_bh(&dev->lock);
d431 1
a431 1
		spin_unlock_bh(&dev->lock);
d437 1
a437 1
		spin_unlock_bh(&dev->lock);
d443 1
a443 1
	spin_unlock_bh(&dev->lock);
d451 1
a451 1
        dbg(__FUNCTION__ " urb: pipe %d tbuf 0x%x tlen %d actlen %d", 
d461 1
a461 1
		spin_lock_bh(&dev->lock);
d463 1
a463 1
		spin_unlock_bh(&dev->lock);
d505 1
a505 1
	spin_lock_bh(&dev->lock);
d507 1
a507 1
	    spin_unlock_bh(&dev->lock);
d531 1
a531 1
	    spin_lock_bh(&dev->lock);
d535 1
d537 1
a537 1
	        spin_unlock_bh(&dev->lock);
d550 4
d558 1
d565 1
a565 4
	            } else {
			/* just slide down to the front of urb buffer */
		        bcopy(&dev->bulk_in_curbuf[rcount], dev->bulk_in_curbuf, urb->actual_length);
		    }
d576 1
a576 1
	spin_lock_bh(&dev->lock);
d581 1
a581 1
	        spin_unlock_bh(&dev->lock);
d583 3
a585 2
	    } else
	        spin_unlock_bh(&dev->lock);
d592 1
a592 1
	spin_lock_bh(&dev->lock);
d594 1
a594 1
	    spin_unlock_bh(&dev->lock);
d612 1
a612 1
	    spin_unlock_bh(&dev->lock);
d753 1
a753 1
	spin_lock_bh(&dev->lock);
d756 1
a756 1
	spin_unlock_bh(&dev->lock);
