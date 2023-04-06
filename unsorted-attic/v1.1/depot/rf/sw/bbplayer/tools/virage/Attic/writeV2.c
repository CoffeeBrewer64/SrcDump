d21 1
a21 1
#define OPTARG      "h"
d24 32
d61 1
a76 1
    //u8 virage2[VIRAGE2_RAM_END - VIRAGE2_RAM_START];
d85 10
d98 10
a107 6
            case 'h': { /* Help */
                usage();
                exit(0);
            }
            default:
                break;
d111 4
a142 4

    virage2Bytes = sizeof(virage2);
    virage2Sum = 0;
    memset(&virage2,0,virage2Bytes);
