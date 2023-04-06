d1 1
a1 1
#ident "$Id: rvl_image.c,v 1.9 2006/03/21 00:32:19 craig Exp $"
a54 1
#include "alt_types.h"
d59 1
d119 1
a119 1
                     ESRsa2048RsaCert **certArray);
d122 1
a122 1
                          ESTitleMeta **tmd, ESRsa2048RsaCert **certArray);
d522 1
a522 1
                     ESRsa2048RsaCert *certArray[])
d544 1
a544 1
                ESRsa2048RsaCert *certArray[])
d550 2
a551 2
    *certArray = (ESRsa2048RsaCert *)
                  malloc (sizeof (ESRsa2048RsaCert) * numCerts);
d562 1
a562 1
        if (sizeof(ESRsa2048RsaCert) != statBuf.st_size) {
d565 1
a565 1
                     ProgName, statBuf.st_size, sizeof(ESRsa2048RsaCert));
d575 1
a575 1
        numRead = fread(&((*certArray)[i]), sizeof(ESRsa2048RsaCert),
d707 1
a707 1
                      + (gamePart->numCertificates * sizeof(ESRsa2048RsaCert));
d720 1
a720 1
        gameCopy.certificates    = (ESRsa2048RsaCert *)
d755 1
a755 1
                   sizeof(ESRsa2048RsaCert),
d885 1
a885 1
                    + (updatePart->numCertificates * sizeof(ESRsa2048RsaCert));
d897 1
a897 1
        updateCopy.certificates = (ESRsa2048RsaCert *)
d931 1
a931 1
                   sizeof(ESRsa2048RsaCert),
