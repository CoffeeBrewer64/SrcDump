a30 3
    message("content size: ");
    output_int32_hex(pCmdh->size);
    message("\n");
a38 6
    message("Cmd id: ");
    output_int32_hex(pCmdh->id);
    message("\n");
    message(appName);
    message("\n");

a39 1
        message("Failed to open app on fs.\n");
d46 1
a46 1
//    ALIGN_DCACHE(blkList);
a47 1
    message("Calling osBbFStat for app file.\n");
a49 1
        message("Failed to stat app file\n");
a51 3
    message("osBbFStat, app size: ");
    output_int32_hex(fsStat.size);
    message("\n");
a56 1
    message("setting up atb.\n");
d117 1
a117 1
        ALIGN_DCACHE(blkList);
a155 2

    message("inval caches and call skLaunch()\n");
