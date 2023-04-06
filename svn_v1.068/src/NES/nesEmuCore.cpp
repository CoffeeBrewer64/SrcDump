/**
 * @file nesEmuCore.cpp
 * @author chentian
 * @date 2010.06.24
 * @brief TRL Emulate For CTR - Emu Core NES
 */
#include "nesEmuCore.h"
#include "nesMemory.h"
#include "nesCard.h"
#include "nesGraphic.h"
#include "nesSound.h"
#include "nesCPU.h"
#include "nesInput.h"

/** @name Macro Define */
//@{
#define NES_EMU_SAVEDATA_MAX	8									///< EmuCore Save Data Max Count
//@}

/** @name Global Variable */
//@{
trlSEmuShellBuffer*		g_pNesEmuBuf = NULL;						///< Emu Engine Buffer Data
trlSEmuShellCore		g_sEmuCoreNES = {
	nesEmuCoreInit,
	nesEmuCoreRunOneFrame,
	nesEmuCoreReset,
	nesInputUpdate,
	nesEmuCoreResume,
	nesEmuCoreExit,
	nesEmuCorePatch,
	NULL,
	NULL,
	nesEmuCoreSwapPlayer,
	NULL };
u32						g_nNesEmuSaveData;							///< EmuCore Save Data Count
trlSEmuShellResume		g_sNesEmuSaveData[NES_EMU_SAVEDATA_MAX];	///< EmuCore Save Data
u32						g_nNesEmuSwitchPlayer;						///< EmuCore Switch Player
//@}

/** @brief EmuCore Initialize */
void nesEmuCoreInit(trlSEmuShellBuffer* pBuf)
{
	if(pBuf == NULL)
		return;

	g_pNesEmuBuf = pBuf;
	g_nNesEmuSwitchPlayer = 0;

	// Initialize
	nesMemInit();
	nesCardInit();
	nesGrpInit();
	nesSndInit();
	nesInputInit();
	nesCpuInit();

	// Save Data
	g_nNesEmuSaveData = 0;
	g_sNesEmuSaveData[g_nNesEmuSaveData++].SetData(&g_nNesEmuSwitchPlayer, 4, 1, 0);
	g_sNesEmuSaveData[g_nNesEmuSaveData++].SetData(&g_pNesEmuBuf->nPatchMask, 4, 2, 0);
	g_sNesEmuSaveData[g_nNesEmuSaveData++].SetData(&g_pNesEmuBuf->nPatchPalette, 4, 2, 0);
	g_sNesEmuSaveData[g_nNesEmuSaveData++].SetData(&g_pNesEmuBuf->nPatchActive, 4, 2, 0);
	g_sNesEmuSaveData[g_nNesEmuSaveData++].SetData(g_pNesEmuBuf->sPatchActive, sizeof(trlSEmuShellPatchActive)*TRL_EMUCORE_PATCH_ACTIVEMAX, 2, 0);

	g_pNesEmuBuf->pSaveData[0].SetData(g_sNesEmuSaveData, g_nNesEmuSaveData, 1, 0);
	g_pNesEmuBuf->pSaveData[1].SetData(g_sNesMemSaveData, g_nNesMemSaveData, 1, 0);
	g_pNesEmuBuf->pSaveData[2].SetData(g_sNesCpuSaveData, g_nNesCpuSaveData, 1, 0);
	g_pNesEmuBuf->pSaveData[3].SetData(g_sNesInputSaveData, g_nNesInputSaveData, 1, 0);
	g_pNesEmuBuf->pSaveData[4].SetData(g_sNesGrpSaveData, g_nNesGrpSaveData, 1, 0);
	g_pNesEmuBuf->pSaveData[5].SetData(g_sNesSndSaveData, g_nNesSndSaveData, 1, 0);
	g_pNesEmuBuf->pSaveData[6].SetData(g_sNesCardSaveData, g_nNesCardSaveData, 1, 0);
}

/** @brief EmuCore Patch */
void nesEmuCorePatch(trlSEmuShellPatch* pPatch)
{
	switch(pPatch->sData.sA.nMode)
	{
	case 7:
	case 4:
		switch(pPatch->sData.sA.nType)
		{
		case 0:		// Begin
			{
				for(u32 i=0;i<pPatch->sData.sA.nFixcode;i++)
				{
					g_nNesGrpPalTable[pPatch->pFixcode[i]] = pPatch->nPalette[i];
				}
			}
			break;
		case 1:		// End
			{
				for(int i=0;i<0x40;i++)
					g_nNesGrpPalTable[i] = g_nNesGrpPalTable_Origin[i];
			}
			break;
		}
		extern void nesGrpUpdatePalA();
		nesGrpUpdatePalA();
		break;
	}
}

#define NES_DEBUG_TIME 0
#if NES_DEBUG_TIME
	u64 g_nNesTimeCPU = 0;
	u64 g_nNesTimeGPU = 0;
	u64 g_nNesTimeAPU = 0;
	u64 g_nNesTime0 = 0;
	u64 g_nNesTime1 = 0;
#endif

#if TRL_HVC_EMUCORE_NEW
/** @brief EmuCore RunOneFrame */
void nesEmuCoreRunOneFrame()
{
	trlTraceFrameBegin();
	g_nNesBreakFlag = 0;
	nesSndRegWriteLog_LogBegin();

	while(1)
	{		
		g_nNesCpuEventTicks = g_nNesGrpTicks/3;

		// Update CPU
		nesCpuRun();
		trlTraceTickAdd(g_nNesCpuEventTicks);
		nesSndRegWriteLog_LogTicksAdd(g_nNesCpuEventTicks);

		// Update Graphic
		g_nNesGrpTicks -= g_nNesCpuEventTicks * 3;		
		g_nNesGrpTicks += NES_GRP_TICKS;
		nesGrpUpdate();

		if(g_nNesBreakFlag)
		{
			nesSndRegWriteLog_LogRun();
			nesSndUpdate();
			g_pNesEmuBuf->nFrames++;
			trlTraceFrameEnd();
			return;
		}
	}
}
#else
/** @brief EmuCore RunOneFrame */
void nesEmuCoreRunOneFrame()
{
#if ((TRL_EMUTYPE==0) || (TRL_EMUTYPE==3))

	extern trlSEmuShellVideoMask	g_sTrlVideoMaskData;

	g_pNesEmuBuf->nTexID = 1 - g_pNesEmuBuf->nTexID;
	if(g_pNesEmuBuf->nMotion2Frames < 2)
		g_pNesEmuBuf->nMotion2Frames++;
	g_pNesEmuBuf->pScreenBuf = (u16*)(g_pNesEmuBuf->pTextureBuf[g_pNesEmuBuf->nTexID]) + g_pNesEmuBuf->nScreenBufOffset;

#if NES_DEBUG_TIME
	g_nNesTimeCPU = 0;
	g_nNesTimeGPU = 0;
	g_nNesTimeAPU = 0;
#endif
	trlTraceFrameBegin();
	g_nNesBreakFlag = 0;

	nesSndRegWriteLog_LogBegin();

	while(1)
	{
#if NES_DEBUG_TIME
	g_nNesTime0 = trlTimeGet_us();
#endif
		// Update CPU
		nesCpuRun();
		trlTraceTickAdd(g_nNesCpuEventTicks);
		nesSndRegWriteLog_LogTicksAdd(g_nNesCpuEventTicks);
		s32 nRunTicks = g_nNesCpuEventTicks;
		g_nNesCpuEventTicks = 0xFFFFFF;
#if NES_DEBUG_TIME
		g_nNesTime1 = trlTimeGet_us();
		g_nNesTimeCPU += g_nNesTime1 - g_nNesTime0;
#endif

		// Update Card IRQ
		if(g_nNesCardIRQEnable == NES_CARD_IRQ_CPUCYCLE)
		{
			g_nNesCardIRQTicks -= nRunTicks;
			if(g_nNesCardIRQTicks <= 0)
				nesCardUpdateIRQ();
			if(g_nNesCpuEventTicks > g_nNesCardIRQTicks)
				g_nNesCpuEventTicks = g_nNesCardIRQTicks;
		}

#if 1
		// Update Disk IRQ
		if(g_nNesCardIRQDiskTicks > 0)
		{
			g_nNesCardIRQDiskTicks -= nRunTicks;
			if(g_nNesCardIRQDiskTicks <= 0)
			{
				if(g_nNesCardIRQDiskEnable)
					g_nNesCpuIRQFlag |= 2;
			}
			else if(g_nNesCpuEventTicks > g_nNesCardIRQDiskTicks)
				g_nNesCpuEventTicks = g_nNesCardIRQDiskTicks;
		}
#endif

		// Update Graphic
		g_nNesGrpTicks -= nRunTicks * 3;
		while(g_nNesGrpTicks <= 0)
		{
			g_nNesGrpTicks += NES_GRP_TICKS;
			nesGrpUpdate();
		};
		s32 nGrpTicks = (3 - g_nNesGrpTicks%3 + g_nNesGrpTicks) / 3;
		if(g_nNesCpuEventTicks > nGrpTicks)
			g_nNesCpuEventTicks = nGrpTicks;

#if NES_DEBUG_TIME
	g_nNesTime0 = trlTimeGet_us();
	g_nNesTimeGPU += g_nNesTime0 - g_nNesTime1;
#endif

		if(g_nNesBreakFlag)
		{
			nesSndRegWriteLog_LogRun();
			nesSndUpdate();
#if NES_DEBUG_TIME
	g_nNesTime1 = trlTimeGet_us();
	g_nNesTimeAPU = g_nNesTime1 - g_nNesTime0;
#endif
			g_pNesEmuBuf->nFrames++;
			trlTraceFrameEnd();
			return;
		}
	}
#endif
}
#endif//TRL_HVC_EMUCORE_NEW
/** @brief EmuCore Reset */
void nesEmuCoreResetCold()
{
	nesCpuReset();
	nesMemReset();
	nesCardReset();
	nesGrpReset();
	nesSndReset();
	nesInputReset();
}


/** @brief EmuCore Reset */
void nesEmuCoreReset()
{
	//g_pNesWRAM[0xFF]=0xFF;
//	nesCpuReset();
#if	TRL_FDISK_RESET_MEM
	nesMemReset();
#endif
	//nesCardReset();
	//nesGrpReset();
	nesSndReset();
	//nesInputReset();
	
	g_nNesCpuRESETFlag = 1;
	
	for(int i=0;i<0x40;i++)
			g_nNesGrpPalTable[i] = g_nNesGrpPalTable_Origin[i];
}

/** @brief EmuCore Resume */
void nesEmuCoreResume()
{
	if(g_pNesEmuBuf->nPatchPalette != 0xFFFFFFFF)
	{
		trlSEmuShellPatch* pPatch = &g_pNesEmuBuf->pPatchData[g_pNesEmuBuf->nPatchPalette];
		nesEmuCorePatch(pPatch);
	}
	else
	{
		for(int i=0;i<0x40;i++)
			g_nNesGrpPalTable[i] = g_nNesGrpPalTable_Origin[i];
	}

	g_pNesEmuBuf->funcChangeMaskMode(0);
	nesMemResume();
	nesCardResume();
	nesInputResume();
	nesSndResume();
	nesGrpResume();
	nesCpuResume();
}

/** @brief EmuCore Exit */
void nesEmuCoreExit()
{
	nesGrpExit();
	nesCardExit();
	nesMemExit();
}

/** @brief EmuCore Config */
void nesEmuCoreConfig()
{
}

/** @brief Single Mode Swap Player */
u32 nesEmuCoreSwapPlayer(s32 nMode)
{
	switch(nMode)
	{
	case 2:
		g_nNesEmuSwitchPlayer = 1 - g_nNesEmuSwitchPlayer;
		break;
	}
	if(g_nNesEmuSwitchPlayer == 0)
		return 0;
	else
		return 2;
}
