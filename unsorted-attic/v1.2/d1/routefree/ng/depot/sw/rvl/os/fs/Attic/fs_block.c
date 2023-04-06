d189 4
a192 4
    ISFSError   rc = ISFS_ERROR_OK;
    IOSError    ret;
    u32         count;
    u8          spareBuf[FL_VIRT_SPARE_SIZE];
d194 2
a195 1
    u8          mac[ISFS_MAC_LEN];
d271 7
a277 7
            /*
             * If the chain bit is set, only verify the HMAC once
             * after all the blocks have been read
             */
            if (!(flags & ISFS_BLOCK_OP_CHAIN) || (count == (numBlocks - 1))) {
                u8      *input;
                u32     size;
d279 10
a288 7
                if (flags & ISFS_BLOCK_OP_CHAIN) {
                    input = buf;
                    size = ISFS_BLOCK_SIZE * numBlocks;
                } else {
                    input = buf + (count * ISFS_BLOCK_SIZE);
                    size = ISFS_BLOCK_SIZE;
                }
d290 3
a292 3
                ret = IOSC_GenerateBlockMAC(input, size, (u8 *) customData,
                                sizeof (ISFSCustomData), IOSC_FS_MAC_HANDLE,
                                mac, -1, 0);
d294 3
a296 2
                    isfsPrint(FS_DEBUG_ERROR, "Failed to calculate HMAC for"
                                        " block %d\n", fsBlockIndex + count);
d388 7
a394 4
    ISFSError   rc = ISFS_ERROR_OK;
    IOSError    ret;
    u32         count;
    u8          spareBuf[FL_VIRT_SPARE_SIZE];
d421 7
a427 7
            /*
             * If the chain bit is set, only compute the HMAC once
             * when writing the last block
             */
            if (!(flags & ISFS_BLOCK_OP_CHAIN) || (count == (numBlocks - 1))) {
                u8      *input;
                u32     size;
d429 10
a438 7
                if (flags & ISFS_BLOCK_OP_CHAIN) {
                    input = (u8 *) buf;
                    size = ISFS_BLOCK_SIZE * numBlocks;
                } else {
                    input = (u8 *) (buf + (count * ISFS_BLOCK_SIZE));
                    size = ISFS_BLOCK_SIZE;
                }
d440 3
a442 3
                ret = IOSC_GenerateBlockMAC(input, size, (u8 *) customData,
                                sizeof (ISFSCustomData), IOSC_FS_MAC_HANDLE,
                                spareBuf, -1, 0);
d445 2
a446 1
                        " signing %d, rc=%d\n", fsBlockIndex + count, ret);
