/**
 * @file trlMacro.h
 * @author zhfang & Chentian
 * @date 2009.11.16
 * @brief TRL Emulate - Macro Define
 */
#pragma once

#ifndef TRL_PRODUCTION
#define TRL_PRODUCTION 0
#endif

#ifndef TRL_DEBUG
#define TRL_DEBUG 1
#endif

#ifndef TRL_EMUTYPE
#define TRL_EMUTYPE 0
#endif

#ifndef TRL_BACKUPTYPE
#define TRL_BACKUPTYPE 0
#endif

#ifndef TRL_NETTYPE
#define TRL_NETTYPE 0
#endif

#ifndef TRL_VERSION
#define TRL_VERSION "version 1.068"
#endif

#ifndef TRL_VSYNC
#define TRL_VSYNC 1
#endif

#ifndef TRL_PATCH
#define TRL_PATCH 1
#endif

#ifndef TRL_STEREO
#define TRL_STEREO 1
#endif

#ifndef TRL_MENU
#define TRL_MENU 1
#endif

#ifndef TRL_DEBUGINFO
#define TRL_DEBUGINFO 1
#endif

#ifndef TRL_DEMO
#define TRL_DEMO 0
#endif

#ifndef TRL_COLORDMG
#define TRL_COLORDMG 0
#endif

#ifndef TRL_SWITCHICON
#define TRL_SWITCHICON 1
#endif

#ifndef TRL_AGBCMP
#define TRL_AGBCMP 0
#endif

#ifndef TRL_SOUND
#define TRL_SOUND 1
#endif

#ifndef TRL_SOUND_DEBUG
#define TRL_SOUND_DEBUG 1
#endif

#ifndef TRL_SOUND_FREQ_LIMIT
#define	TRL_SOUND_FREQ_LIMIT 1
#endif

#ifndef TRL_SOUND_WAVE_TEST
#define TRL_SOUND_WAVE_TEST 0
#endif

#ifndef TRL_SOUND_NOISE_TEST
#define TRL_SOUND_NOISE_TEST 1
#endif

#ifndef TRL_SOUND_MONOFILTER
#define TRL_SOUND_MONOFILTER 1
#endif

#ifndef TRL_SOUND_CGB_FAST
#define TRL_SOUND_CGB_FAST 1
#endif

#ifndef TRL_SOUND_CGB_CH3_VOLUME_HALF
#define TRL_SOUND_CGB_CH3_VOLUME_HALF 0
#endif

#ifndef TRL_SOUND_NES_FAST
#define TRL_SOUND_NES_FAST 0
#endif

#ifndef TRL_SOUND_REG_LOG
#define TRL_SOUND_REG_LOG 1
#endif

#ifndef TRL_NETWORK
#define TRL_NETWORK 1
#endif

#ifndef TRL_MIC
#define TRL_MIC 1
#endif

#ifndef TRL_NETWORK_PIA_WITH_MIC
#define TRL_NETWORK_PIA_WITH_MIC 0
#endif

#ifndef TRL_SAVE_DUPLICATE
#define TRL_SAVE_DUPLICATE 1
#endif

#ifndef TRL_VCM_WAITICON
#define TRL_VCM_WAITICON 0
#endif

#ifndef TRL_VCM_LANGFILE_SD
#define TRL_VCM_LANGFILE_SD 0
#endif

#ifndef TRL_HVC_GRAPHIC
#define TRL_HVC_GRAPHIC 0
#endif

#ifndef TRL_HVC_SWITCHPLAYER
#define TRL_HVC_SWITCHPLAYER 1
#endif

#ifndef TRL_HVC_FDSFAST
#define TRL_HVC_FDSFAST 1
#endif

#ifndef TRL_HVC_CPU_BRANCH_SHORTTIME
#define TRL_HVC_CPU_BRANCH_SHORTTIME 0
#endif

#ifndef TRL_HVC_FDSDISK
#define TRL_HVC_FDSDISK 0
#endif

#ifndef TRL_HVC_EMUCORE_NEW
#define TRL_HVC_EMUCORE_NEW 0
#endif

#ifndef TRL_HVC_OBJ_HIT_HACK
#define TRL_HVC_OBJ_HIT_HACK 1
#endif

#ifndef TRL_HVC_NMI_LINE240
#define TRL_HVC_NMI_LINE240 0
#endif

#ifndef TRL_HOMENIX_UPSCREEN
#define TRL_HOMENIX_UPSCREEN 1
#endif

//add by yuans: MMC3 nIRQCount hack
#ifndef TRL_MMC3_HACK_IRQCOUNT
#define TRL_MMC3_HACK_IRQCOUNT 0
#endif

#ifndef TRL_MMC3_IRQRELOAD_RESET
#define TRL_MMC3_IRQRELOAD_RESET 1
#endif

#ifndef	TRL_MMC5_CASTLEVANIA3
#define TRL_MMC5_CASTLEVANIA3	0
#endif

#ifndef BG_OFFSETY_GT239
#define BG_OFFSETY_GT239 0
#endif

#ifndef	BG_RENDER_REPEAT_FAST
#define BG_RENDER_REPEAT_FAST 0
#endif

#ifndef TRL_HVC_FDSDISK_SWITCHDISK_OLD_METHOD
#define TRL_HVC_FDSDISK_SWITCHDISK_OLD_METHOD 0
#endif
//end of add

#ifndef TRL_PROFILER
#define TRL_PROFILER 0
#endif

#ifndef TRL_HVC_SOUND_TEST
#define TRL_HVC_SOUND_TEST 1
#endif

#ifndef TRL_VCM_MSG_DEBUG
#define TRL_VCM_MSG_DEBUG 1
#endif

#ifndef TRL_CPU_OPCODE_REG_FAST
#define TRL_CPU_OPCODE_REG_FAST 1
#endif

#ifndef TRL_MMC4_SPEEDUP
#define	TRL_MMC4_SPEEDUP	1
#endif

#ifndef TRL_FAKE_RENDER_CLIP
#define	TRL_FAKE_RENDER_CLIP	1
#endif

#ifndef TRL_OBJ0_HIT_DELAY
#define	TRL_OBJ0_HIT_DELAY	0
#endif

#ifndef TRL_FDISK_RESET_MEM
#define	TRL_FDISK_RESET_MEM	0
#endif

#ifndef TRL_NES_SOUND_LENGTH_PALNTSC
#define TRL_NES_SOUND_LENGTH_PALNTSC 0
#endif

//set 1 for NTSC mode, 0 for PAL mode
#ifndef TRL_NES_SOUND_ENVELOPE_FREQ_NTSC
#define TRL_NES_SOUND_ENVELOPE_FREQ_NTSC 1
#endif


#if TRL_DEMO
	#undef TRL_MENU
	#define TRL_MENU 0

	#undef TRL_SWITCHICON
	#define TRL_SWITCHICON 0

	#undef TRL_PRODUCTION
	#define TRL_PRODUCTION 1
#endif

#if TRL_PRODUCTION
	#undef TRL_SOUND_DEBUG
	#define TRL_SOUND_DEBUG 0

	#undef TRL_DEBUGINFO
	#define TRL_DEBUGINFO 0
	
	#undef TRL_VCM_MSG_DEBUG
	#define TRL_VCM_MSG_DEBUG 0

	#undef TRL_HVC_FDSDISK
	#define TRL_HVC_FDSDISK 0

	#undef TRL_PROFILER
	#define TRL_PROFILER 0

	#undef TRL_DEBUG
	#define TRL_DEBUG 0

	#undef TRL_HVC_SOUND_TEST
	#define TRL_HVC_SOUND_TEST 0
#endif

#define TRL_EMUCORE_NETTYPE_NONE		0
#define TRL_EMUCORE_NETTYPE_PARENT		1
#define TRL_EMUCORE_NETTYPE_CHILD		2

