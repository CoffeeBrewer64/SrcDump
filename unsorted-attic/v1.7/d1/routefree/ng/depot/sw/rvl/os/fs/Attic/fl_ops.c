d47 6
d1403 8
d1413 1
a1413 3
        if (eccResult == 0) {       /* No bit error */
            continue;
        } else if ((eccResult & (eccResult - 1)) == 0) {
