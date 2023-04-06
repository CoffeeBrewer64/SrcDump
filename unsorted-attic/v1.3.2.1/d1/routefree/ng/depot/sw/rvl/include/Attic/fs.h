d107 6
a112 6
    u8          path[ISFS_PATH_MAXLEN];     /* NULL terminated string */
    u8          ownerAccess;                /* Least significant 2 bits */
    u8          groupAccess;                /* Least significant 2 bits */
    u8          othersAccess;               /* Least significant 2 bits */
    u8          attr;                       /* Attribute bits */
} __attribute__ ((packed)) ISFSPathAttrArgs;
