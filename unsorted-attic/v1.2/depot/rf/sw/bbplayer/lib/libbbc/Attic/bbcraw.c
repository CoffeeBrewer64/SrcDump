a53 74

int
__BBC_ScanBadBlocks(bbc_hand *hp)
{
    unsigned int hbuf[2];
    int rv = BBC_OK;

    if (hp->bh_type == BBC_HT_READER) {
	return BBC_NOCARD;
    }

    /* BBC_HT_DIRECT */

    hbuf[0] = REQ_SCAN_BLOCKS;
    hbuf[1] = hp->bh_seqno;
    __bbc_send_cmd(hp->bh_pofd, hbuf, 8);
    __bbc_read_rsp(hp->bh_pifd, hbuf, 8);
    if (hbuf[0] != 255-REQ_SCAN_BLOCKS || (hbuf[1]&0x80000000)) {
	fprintf(stderr, "scan blocks failed %d\n", hbuf[1]);
	return BBC_ERROR;
    }
    if (hp->bh_blist == NULL) {
	hp->bh_cardsize = (int)hbuf[1];
	if ((hp->bh_blist = malloc(hp->bh_cardsize)) == NULL) {
	    perror("malloc");
	    return BBC_ERROR;
	}
    } else {
	if (hp->bh_cardsize != (int)hbuf[1]) {
	    free(hp->bh_blist);
	    hp->bh_cardsize = (int)hbuf[1];
	    if ((hp->bh_blist = malloc(hp->bh_cardsize)) == NULL) {
	        perror("malloc");
	        return BBC_ERROR;
	    }
	}
    }
    if (hp->bh_sblocks == NULL) {
	if ((hp->bh_sblocks = malloc(SYS_BLOCKS)) == NULL) {
	    perror("malloc");
	    return BBC_ERROR;
	}
    }
    rv = __bbc_read_data(hp->bh_pifd, hp->bh_blist, hp->bh_cardsize);
    if (rv > 0) {
	/* compute addresses for sk, sal, and sa */
	int i, j;
	for(j = i = 0; i < hp->bh_cardsize; i++) {
	    if (hp->bh_blist[i] == 0) {
		hp->bh_sblocks[j++] = i;
		if (j >= SYS_BLOCKS) break;
	    }
	}
	printf("found %d sys blocks\n", j);
    }
    return rv;

    return BBC_OK;
}

int
__BBC_Format(bbc_hand *hp)
{
    unsigned int hbuf[2];
    int rv = BBC_OK;

    if (hp->bh_type == BBC_HT_READER) {
	return BBC_NOCARD;
    }

    /* BBC_HT_DIRECT */

    return rv;
}
