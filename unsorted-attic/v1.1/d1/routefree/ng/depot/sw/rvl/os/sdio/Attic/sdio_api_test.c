d11 1
a11 1
 * $Id: sdio_api_test.c,v 1.16 2006/01/25 01:02:07 jlivesey Exp $
d14 1
a14 1
char ident[] = "$Id: sdio_api_test.c,v versa-mod jlivesey Exp $";
a41 2
	#define malloc(size) IOS_Alloc(0,size)
	#define free(ptr) 	IOS_Free(0,ptr)	
