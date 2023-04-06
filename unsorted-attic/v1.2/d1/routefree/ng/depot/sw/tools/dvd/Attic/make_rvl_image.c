d1 1
a1 1
#ident "$Id: make_rvl_image.c,v 1.1 2006/04/14 01:30:38 craig Exp $"
d592 1
a592 1
    sprintf(certFileName, "%s/usr/etc/pki_data/cert_tpki.sys", root);
d617 1
a617 1
    strcat (commandBuf, " -P t");               // test PKI
d688 1
a688 1
    strcat (commandBuf, " -P t");               // test PKI
