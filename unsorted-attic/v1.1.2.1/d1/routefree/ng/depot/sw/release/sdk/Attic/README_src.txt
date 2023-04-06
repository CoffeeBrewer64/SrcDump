a0 125

Date: 12/01/2009


A. Overview

The purpose of the IOS SRC SDK is to provide all the necessary source files
to build boot1, boot2 loader, compat boot, mini IOS, IOS kernel, and other 
BroadOn Resource Managers such as DI, FS, and SDI.  It contains some source 
codes, header files, libraries, and tools to build the following main
components:

   1) Various libraries
      - System library
        * This is the main library that contains all the hardware 
          initialization routines.
      - EEPROM library
      - ISFS library
      - SDI library
      - Libc library
   2) boot1 for diag
   3) boot2 for development
   4) Loader
   5) GC compat mode boot (bc.wad)
   6) Mini-IOS
   7) IOS Kernels
   8) ISFS Resource Manager
   9) DI Resource Manager
  10) SDI Resource Manager


B. SDK Structure

The SDK has the following directory structure:
  - usr/
      - bin/
          - x86/
              - Cygwin-based tools
          - rvl/
              - Pre-built IOP-based programs
      - include/
              - Header files required to build programs and libraries
      - lib/rvl/
              - Pre-built IOP-based libraries
      - src/
          - apps/
               - common/
                      - Source to build libapputils.a (used by minimon0).
               - eemon/
                      - Source to build eemon.elf.
               - iossh/
                      - Source to build libiossh.elf (used by IOS shell).
               - minimon0_sram/
                      - Source to build minimon0_sram.elf.
          - boot/
               - boot1.diag/
                      - Source to build development various boot1 images:
                        - boot1_dev.flash
                          * This image can be used on existing NDEV systems
                        - boot1_prod_diag.flash
                          * This image can be used on NDEV systems to debug
                            production boot2.
                        - boot1_ati.flash
                          * This image is for old ATI diag (3 blocks) boot
                        - boot1_nintendo.flash
                          * This image is for old Nintendo diag boot
               - boot2/
                      - Source to build boot2.wad.
                        * Need RVL SDK installed and REVOLUTION_SDK_ROOT set.
               - compat/
                      - Source to build GC compat boot (bc.wad).
                        * Need RVL SDK installed and REVOLUTION_SDK_ROOT set.
               - loader/
                      - Source to build loader.bin and loader_boot2.bin.
          - lib/
              - ee/
                 - Source to build EEPROM library (libee.a).
              - fs/
                 - Source to build ISFS library (libfs.a).
              - iosc/
                 - Source to build crypto interface library (libiosc.a).
              - ioslibc/
                 - Source to build IOS libc (libioslibc.a).
              - sdi/
                 - Source to build SDI library (libsdi.a).
              - sys/
                 - Source to build libsys.a and contains all the hardware 
                   initialization routines used on IOP.
          - os/
              - di/
                 - Source to build DI Resource Manager.
              - fs/
                 - Source to build ISFS Resource Manager.
              - ios/
                 - Source to build IOS kernels and IOS shell.
              - mini_ios/
                 - Source to build Mini-IOS.
              - sdi/
                 - Source to build SDI Resource Manager.
          - signum/
                 - Contains various definition and macro files to be used
                   with Chameleon JTAGJet program.


C. Installing & Building SDK

To install the SDK:
   - Start a Cygwin shell window
   - Unpack the SDK image (unzip) into the installed directory
   - Set the environment variable $ROOT to point to the installed directory
   - Set the environment variable $RVL_MEM to 128 (for 128MB GDDR3 config).
   - Install RVL SDK and set REVOLUTION_SDK_ROOT environment variable.
     Various tools (ticket.exe and tmd.exe) and configuration files (pki_data)
     are needed to build WAD files (such as boot2.wad).

To build the SDK:
   - Go to $ROOT/usr/src
   - Type "make" to build libraries and programs in local directories but 
     not installing them.
   - Type "make exports" to build libraries and programs in local directories 
     AND installing them to $ROOT/usr/lib/rvl and $ROOT/usr/bin/rvl.
     For example, if you modify libsys.a, you would want to do "make exports"
     so that boot1 build would pickup your changes.


