a2 45
#if 0
static int
read_blist(bbc_hand *hp)
{
}

static int
write_block(bbc_hand *hp, const void* block, const void*spare,  int off)
{
    unsigned int hbuf[2], r;
    /* write a block on the BBCard */
    hbuf[0] = spare ? REQ_WRITE_BLOCK_SP : REQ_WRITE_BLOCK;
    r = 255-hbuf[0];
    hbuf[1] = off;
    __bbc_send_cmd(hp->bh_pofd, hbuf, 8);
    __bbc_send_data(hp->bh_pofd, block, BB_FL_BLOCK_SIZE);
    if (spare) __bbc_send_data(hp->bh_pofd, spare, BB_FL_SPARE_SIZE);
    __bbc_read_rsp(hp->bh_pifd, hbuf, 8);
    if (hbuf[0] != r || hbuf[1] != 0) {
	fprintf(stderr, "write block %d failed\n", off);
	return -1;
    }
    return 0;
}

static int
read_block(bbc_hand *hp, void* block, void* spare, int off)
{
    unsigned int hbuf[2], r;
    /* write a block on the BBCard */
    hbuf[0] = spare ? REQ_READ_BLOCK_SP : REQ_READ_BLOCK;
    r = 255-hbuf[0];
    hbuf[1] = off;
    __bbc_send_cmd(hp->bh_pofd, hbuf, 8);
    __bbc_read_rsp(hp->bh_pifd, hbuf, 8);
    __bbc_read_data(hp->bh_pifd, block, BB_FL_BLOCK_SIZE);
    if (spare) __bbc_read_data(hp->bh_pifd, spare, BB_FL_SPARE_SIZE);
    if (hbuf[0] != r || hbuf[1] != 0) {
	fprintf(stderr, "read block %d failed\n", off);
	return -1;
    }
    return 0;
}
#endif

