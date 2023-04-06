#ifndef NN_HW_MEMORYMAP_H_
#define NN_HW_MEMORYMAP_H_

#if     defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6)
#include    <nn/hw/CTR/MPcore/mmu_table.h>
#include    <nn/hw/CTR/MPcore/mmap_axi_wram.h>

#else  //SDK_ARM9
#include    <nn/hw/CTR/MPcore/mmap_axi_wram.h>
#include    <nn/hw/CTR/ARM9/mmap_prv_wram.h>
#include    <nn/hw/CTR/ARM9/mmap_global.h>
#endif

#include    <nn/hw/CTR/mmap_shared.h>
#include    <nn/hw/ioreg.h>

/* NN_HW_MEMORYMAP_H_ */
#endif
