d11 1
a11 1

d51 1
a51 2
    char *infilename;
    char *outfilename;
d65 2
a66 2
    if (argc != 5){
        fprintf(stderr,"Usage: test inputcmdfile outputticketfile  offset num_bytes\n");
d68 1
d75 2
a76 2
    start_offset = atoi(argv[3]);
    bytes = atoi(argv[4]);
d82 2
a83 1
    outfileptr = fopen(argv[2], "wb");
d85 4
a88 5
    /* initialize from random fields */
    random_field(&temp, 1234);
    field_to_bigint(&temp, &a);
    random_field(&temp, 4567);
    field_to_bigint(&temp, &b);
d96 1
a96 1
    random_field(&private_key1, 8768 );
d171 1
a171 1

d190 12
