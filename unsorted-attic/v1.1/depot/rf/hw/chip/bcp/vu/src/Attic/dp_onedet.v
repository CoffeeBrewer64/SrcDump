d1 7
d28 1
a28 1
*  description:	16 bit buffer using ni01d5 cells			*
d36 1
a36 1
// $Id: dp_onedet.v,v 1.1 2002/03/28 00:26:14 berndt Exp $
d50 1
a50 1
	nd04d1	onedet0to3	(	.zn		(intonedet[0]),
d57 1
a57 1
	nd04d1	onedet4to7	(	.zn		(intonedet[1]),
d64 1
a64 1
	nd04d1	onedet8to11	(	.zn		(intonedet[2]),
d71 1
a71 1
	nd04d1	onedet12to15	(	.zn		(intonedet[3]),
d78 1
a78 1
	nr04d2	onedetfinal	(	.zn		(out),
