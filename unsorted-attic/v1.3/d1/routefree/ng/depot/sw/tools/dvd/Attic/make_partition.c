d41 5
d144 3
a421 1
    status = system(commandBuf);
d426 1
d556 2
a557 1
        fprintf(stderr, "Error: sizeof of ticket file (%d) does not match the sizeof an ESTicket (%d)\n", ticketSize, sizeof(ESTicket));
