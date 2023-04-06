d87 1
d92 1
a92 1
static char* options = "ho:t:v";
d126 2
a127 2
    fprintf (stderr, "Usage: %s [options] content_file\n", ProgName);
    fprintf(stderr,
d131 9
a139 1
        " -v, --verbose         - print out messages as image is created\n");
d189 5
d200 1
a200 1
        fprintf (stderr, "%s: Need content name\n", argv[0]);
