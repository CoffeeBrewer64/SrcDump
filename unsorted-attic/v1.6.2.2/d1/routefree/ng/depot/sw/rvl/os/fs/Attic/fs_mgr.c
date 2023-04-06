d41 1
d833 1
a833 1
                    (const u8 *) pathAttrArgs->path, pathAttrArgs->attr,
d846 1
a846 1
            rc = isfsSetAttr(entry->uid, (const u8 *) pathAttrArgs->path,
a864 11
#ifdef NAPA_WORKAROUND      /* TODO: Temporary workaround */
            u32     word, *wordPtr;

            word = (groupAcc & 0xff) | ((ownerAcc & 0xff) << 8);
            wordPtr = (u32 *) (&(pathAttrArgs->ownerAccess) - 2);
            *wordPtr = word;

            word = ((attr & 0xff) << 16) | ((othersAcc & 0xff) << 24);
            wordPtr = (u32 *) &(pathAttrArgs->othersAccess);
            *wordPtr = word;
#else
a868 2
#endif

d901 1
a901 1
                            (const u8 *) pathAttrArgs->path, pathAttrArgs->attr,
d916 1
a916 1
                                (const u8 *) pathAttrArgs->path,
d1233 3
