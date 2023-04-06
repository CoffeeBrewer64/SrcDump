d107 6
a112 6
    u32         path[ISFS_PATH_MAXLEN];     /* NULL terminated string */
    u32         ownerAccess;                /* Least significant 2 bits */
    u32         groupAccess;                /* Least significant 2 bits */
    u32         othersAccess;               /* Least significant 2 bits */
    u32         attr;                       /* Attribute bits */
} /*__attribute__ ((packed))i*/ ISFSPathAttrArgs;
