#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include <PR/bbticket.h>

#define PAGE_SIZE	512

int main(int argc, char* argv[]) 
{
    FILE* in = stdin, * out = stdout;
    char c;
    unsigned char buf[PAGE_SIZE];
    int bytesin, bytes = 0, loadAddr = 0xa0001000;
    BbTicket ticket;

    opterr = 0;
    while((c = getopt(argc, argv, "l:o:")) != (char)-1) {
        switch(c) {
	case 'o':
	    if ((out = fopen(optarg, "w")) == NULL) {
		perror(optarg);
		return 1;
	    }
	    break;
        case 'l':  /* load address */
            loadAddr = atoi(optarg);
            break;
	default:
	usage:
	    fprintf(stderr, 
                    "Usage: mkBootTicket [-o outBinaryFile -l loadAddr "
                    "inBinaryFile]\n"
                    "  NOTE: default to stdin/stdout for "
                    "inBinaryFile/outBinaryFile\n");
	    return 1;
	}
    }

    //if (optind >= argc) in = stdinm
    if (optind < argc && (in = fopen(argv[optind], "r")) == NULL) {
	perror(argv[optind]);
	return 1;
    }

    //memset(buf, 0, sizeof buf);
    while((bytesin = fread(buf, sizeof buf[0], PAGE_SIZE, in)) > 0) {
        bytes += bytesin;
    }

    memset(&ticket, 0, sizeof(ticket));
    ticket.cmd.head.size = htonl(bytes); 
    ticket.cmd.head.bootLength  = htonl(bytes); 

    /* XXX: must encrypt portions appropriately. */
    ticket.cmd.head.loadAddress = htonl(loadAddr);

    if (fwrite((void *)&ticket, 1, sizeof(ticket), out) < 0) {
        perror("fwrite");
        return ;
    }

    return 0;
}
