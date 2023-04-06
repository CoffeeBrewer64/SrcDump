d35 1
a35 1
#define SRAM_SOURCE_ADDRESS	(SRN_SRAM_BASE+0x2000)
d40 1
a40 1
#define NAPA_SOURCE_ADDRESS	(SPLASH_BASE+0x80000)
d85 1
a85 1
static u32 blockSize[4] = {64, 512, 1024, 4096};
a344 1
    len *= 4;     /* Need to increase len to do byte comparison */
a412 5
            /* Skip testing SRAM if numBlocks is greater than 1024 */
            if (((srcIndx == SRAM_ID) || (dstIndx == SRAM_ID)) && 
                (numBlocks > 1024))
                continue;
            
