#ifndef NN_HW_IOREG_H_
#define NN_HW_IOREG_H_

#if     defined(SDK_ARM11) || defined(NN_PROCESSOR_ARM_V6)
#   include <nn/hw/CTR/MPCore/mmap_global.h> // TORIAEZU:
#   if defined(SDK_NE1EMU)
#       include <nn/hw/CTR-NE1TB/MPCore/ioreg.h>
#   elif defined(SDK_MG20EMU)
#       include <nn/hw/CTR/MPCore/ioreg.h>
#       include <nn/hw/CTR-MG20/MPCore/ioreg.h>
#   else // SDK_TS || SDK_TEG || NN_HARDWARE_CTR_TS || NN_HARDWARE_CTR_TEG2
#       include <nn/hw/CTR/MPCore/ioreg.h>
#   endif
#endif  //SDK_ARM9

#if     defined(SDK_ARM9) || defined(NN_PROCESSOR_ARM_V5)
#   include <nn/hw/CTR/ARM9/mmap_global.h> // TORIAEZU:
#   if defined(SDK_MG20EMU)
#       include <nn/hw/CTR-MG20/ARM9/ioreg.h>
#   else // SDK_TS || SDK_TEG || NN_HARDWARE_CTR_TS || NN_HARDWARE_CTR_TEG2
#       include <nn/hw/CTR/ARM9/ioreg.h>
#   endif
#endif

#endif //NN_HW_IOREG_H_
