d1 1
a1 1
#ident "$Id: dvd_low.c,v 1.26 2006/02/22 20:59:46 craig Exp $"
d357 1
a357 11
    /*
     * Note: TC status should already have been cleared
     *       after the previous successful transfer,
     *       but we do it here anyway to be safe.
     *       The error status is cleared by the function
     *       which retreives the DI error code, but there
     *       is no guarantee this will be called after
     *       an error occurred.
     */
    diClearTransCompStatus();
    diClearErrorStatus();
d793 2
