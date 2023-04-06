
`include "rcp.vh"

// bus widths
parameter PI_REG_ADDRESS_SIZE	= 4;

// register addresses
parameter PI_DRAM_ADDRESS_REG = (BUS_ADDRESS_PI_DRAM_ADDRESS>>2)&32'h0000_000F;
parameter PI_PBUS_ADDRESS_REG = (BUS_ADDRESS_PI_PBUS_ADDRESS>>2)&32'h0000_000F;
parameter PI_READ_LENGTH_REG  = (BUS_ADDRESS_PI_READ_LENGTH >>2)&32'h0000_000F;
parameter PI_WRITE_LENGTH_REG = (BUS_ADDRESS_PI_WRITE_LENGTH>>2)&32'h0000_000F;
parameter PI_STATUS_REG	      = (BUS_ADDRESS_PI_STATUS      >>2)&32'h0000_000F;
parameter PI_BSD_DOM1_LAT_REG = (BUS_ADDRESS_PI_DOM1_LAT    >>2)&32'h0000_000F;
parameter PI_BSD_DOM1_PWD_REG = (BUS_ADDRESS_PI_DOM1_PWD    >>2)&32'h0000_000F;
parameter PI_BSD_DOM1_PGS_REG = (BUS_ADDRESS_PI_DOM1_PGS    >>2)&32'h0000_000F;
parameter PI_BSD_DOM1_RLS_REG = (BUS_ADDRESS_PI_DOM1_RLS    >>2)&32'h0000_000F;
parameter PI_BSD_DOM2_LAT_REG = (BUS_ADDRESS_PI_DOM2_LAT    >>2)&32'h0000_000F;
parameter PI_BSD_DOM2_PWD_REG = (BUS_ADDRESS_PI_DOM2_PWD    >>2)&32'h0000_000F;
parameter PI_BSD_DOM2_PGS_REG = (BUS_ADDRESS_PI_DOM2_PGS    >>2)&32'h0000_000F;
parameter PI_BSD_DOM2_RLS_REG = (BUS_ADDRESS_PI_DOM2_RLS    >>2)&32'h0000_000F;
parameter PI_IO_READ_REG      = (BUS_ADDRESS_PI_IO_READ_REG >>2)&32'h0000_000F;
parameter PI_IO_WRITE_REG     = (BUS_ADDRESS_PI_IO_WRITE_REG>>2)&32'h0000_000F;


/************************************************************************
  MACRO/PARAMETER DEFINES
 ************************************************************************/
// misc
`define PIC_LENGTH_SIZE		24	// data xfer length reg size
`define PIC_DSM_SIZE		4	// data transfer statemachine size
`define PIC_ASM_SIZE		4	// AD16 statemachine size

// buffer
`define PIC_BUF_ADRSZ		7	// buffer address size (byte)
`define PIC_BUF_LNWDTH		64	// buffer line width (bits)

// AD16 bus
`define PIC_ADB_WIDTH		16	// AD16 bus width (bits)
`define PIC_ADB_CYCTR_SZ	8	// AD16 delay counter size (bits)
`define PIC_ADB_LAREG_SZ	8	// ROM device latency reg size
`define PIC_ADB_PWREG_SZ	8	// ROM device pulsewidth reg size
`define PIC_ADB_PGREG_SZ	4	// ROM device page size reg size
`define PIC_ADB_RLREG_SZ	2	// ROM device release reg size

