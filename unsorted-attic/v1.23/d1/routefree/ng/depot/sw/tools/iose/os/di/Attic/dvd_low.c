d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.22 2006/02/16 00:25:31 craig Exp $"
d34 2
d72 2
d75 4
d84 2
d87 3
d95 2
d98 3
d106 2
d109 4
d118 2
d121 4
d130 2
d133 4
d142 2
d145 4
d154 2
d157 4
d166 2
d169 3
d177 2
d180 3
d188 2
d191 4
d200 2
d203 4
d212 2
d215 4
d224 2
d227 4
d236 2
d239 4
d248 2
d251 4
d260 2
d263 4
d272 2
d275 4
d284 2
d287 4
d296 2
d299 4
d308 2
d311 4
d320 2
d323 4
d332 2
d335 4
d345 1
d352 1
d358 4
d364 1
d368 1
d370 1
d376 4
d382 1
d386 1
d388 1
d394 1
a394 1
    return((DIStatus & DI_ERROR_INTR) == 0 ? false : true);
d404 1
d408 1
d423 1
d428 2
d431 4
d440 2
d443 4
d452 2
d455 4
d464 2
d467 4
d476 2
d479 4
d515 1
d566 1
d595 1
d609 1
d620 1
d636 1
d663 1
a674 1
        isDmaCommand    = true;
d688 1
d716 1
d766 1
d850 1
a850 1
                if ((DICoverReg & DI_COVER_STATUS) == 0) {
d991 1
a991 1
    if ((DIStatus & DI_ERROR_INTR_MASK) == 0) {
d996 1
a996 1
    if ((DIStatus & DI_TRANS_COMPLETE_INTR_MASK) == 0) {