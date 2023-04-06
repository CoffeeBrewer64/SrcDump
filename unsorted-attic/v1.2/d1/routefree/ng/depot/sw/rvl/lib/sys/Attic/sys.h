#ifndef __IOP_SYS_H__
#define __IOP_SYS_H__

/* Based on ATI's sys.h */

/* XXX These are from simulation. May not be correct for the real
 * system.
 */
#define PPC_PLL_RESET_TIME  2000000
#define PPC_PLL_LOCK_TIME   10000000
#define DSK_PLL_LOCK_TIME   10000000
#define SYS_CLOCK_FAST_TIME 4115
#define SYS_CLOCK_SLOW_TIME 6173
#define FXCLK_SWITCH_DELAY_CYCLES 64
#define DSK_RESET_DELAY_CYCLES 200


// system utility enums
enum sysClkSpeed_e { compatclockspeed, enhancedclockspeed};
enum sysMode_e { compatmode, enhancedmode};
enum memAhbFlushGroup_e {
    // cpu_ahb masters
    wb_iop, wb_iod, wb_bmc, 
    // dma_ahb masters
    wb_aim, wb_fla, wb_aes, wb_sha, wb_ehc, wb_oh0, wb_oh1,
    wb_sd0, wb_sd1, wb_bmd,
    // the 4 real groups
    wb_cpu, wb_dmaA, wb_dmaB, wb_dmaC,
    wb_all
};
enum memAhbReadBuffer_e {
    rb_iod, rb_ioi, rb_bmc,
    rb_bmd, rb_aim, rb_fla, rb_aes, rb_sha, rb_ehc, rb_oh0, rb_oh1, rb_sd0, rb_sd1,
};
extern enum sysClkSpeed_e sysSpeed;
extern enum sysMode_e sysMode;

// system utility structs
typedef struct pllCfg_s {
    int clkR;
    int clkF;
    int clkO;
} pllCfg;

typedef struct selCfg_s {
    int colSel;
    int rowSel;
    int bankSel;
} selCfg;

// system utility function prototypes
void bootPPC(void);
void initChip(void);
void initPLLs(void);
void enableChipBlocks(void);
void setSysClockSpeed(enum sysClkSpeed_e);
void setSysMode(enum sysMode_e);
void setSysPllCfg(pllCfg);
void setDDRPllCfg(pllCfg);
void setDDRSelCfg(selCfg);
void initCompatSettings(void);
void initSecuritySettings(void);
void initMemBlock(void);
void initDDR(void);
void initNapa(void);
void EnableARAMEmu(void);
void ahbMemFlush( enum memAhbFlushGroup_e );
void ahbMemRBInvalidate(enum memAhbReadBuffer_e);
void bistRegWrite(u16 addr, u16 val);
void seqRegWrite(u16 addr, u16 val);
void initSWWorkArounds(void);
#endif // __DIAG_SYS_H__
