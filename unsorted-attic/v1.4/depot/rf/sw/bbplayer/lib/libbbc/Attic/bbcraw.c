#include "bbclocal.h"

int
__BBC_ReadBlock(bbc_hand *hp, int blk, void *buf, void *spare)
{
    unsigned int hbuf[2], r;

    if (hp->bh_type == BBC_HT_READER) {
	return BBC_NOCARD;
    }

    /* BBC_HT_DIRECT */

    hbuf[0] = spare ? REQ_READ_BLOCK_SP : REQ_READ_BLOCK;
    r = 255-hbuf[0];
    hbuf[1] = blk;
    __bbc_send_cmd(hp->bh_pofd, hbuf, 8);
    __bbc_read_rsp(hp->bh_pifd, hbuf, 8);
    __bbc_read_data(hp->bh_pifd, buf, BB_FL_BLOCK_SIZE);
    if (spare) __bbc_read_data(hp->bh_pifd, spare, BB_FL_SPARE_SIZE);
    if (hbuf[0] != r || hbuf[1] != 0) {
	fprintf(stderr, "read block %d failed\n", blk);
	return BBC_ERROR;
    }
    
    return BBC_OK;
}

int
__BBC_WriteBlock(bbc_hand *hp, int blk, const void *buf, const void *spare)
{
    unsigned int hbuf[2], r;

    if (hp->bh_type == BBC_HT_READER) {
	return BBC_NOCARD;
    }

    /* BBC_HT_DIRECT */

    hbuf[0] = spare ? REQ_WRITE_BLOCK_SP : REQ_WRITE_BLOCK;
    r = 255-hbuf[0];
    hbuf[1] = blk;
    __bbc_send_cmd(hp->bh_pofd, hbuf, 8);
    __bbc_send_data(hp->bh_pofd, buf, BB_FL_BLOCK_SIZE);
    if (spare) __bbc_send_data(hp->bh_pofd, spare, BB_FL_SPARE_SIZE);
    __bbc_read_rsp(hp->bh_pifd, hbuf, 8);
    if (hbuf[0] != r || hbuf[1] != 0) {
	fprintf(stderr, "write block %d failed\n", blk);
	return BBC_ERROR;
    }

    return BBC_OK;
}
