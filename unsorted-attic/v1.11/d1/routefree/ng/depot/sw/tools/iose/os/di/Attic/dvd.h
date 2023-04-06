d1 1
a1 1
#ident "$Id: dvd.h,v 1.10 2006/02/01 01:58:17 craig Exp $"
a34 4
/*
 * These are the values taken by the argument to the
 * callback function
 */
a35 6
#define DVD_INTTYPE_TC                  0x00000001
#define DVD_INTTYPE_DE                  0x00000002
#define DVD_INTTYPE_CVR                 0x00000004
#define DVD_INTTYPE_BRK                 0x00000008
#define DVD_INTTYPE_TIMEOUT             0x00000010
#define DVD_INTTYPE_SECURITY_ERROR      0x00000020
a61 8
typedef struct diCommand {
    /* Command code or psuedo-command code from dvd_hw.h */
    uint8_t     theCommand;
    uint32_t    arg[5];
} diCommand_t;

extern diCommand_t      interfaceDiCommand;

