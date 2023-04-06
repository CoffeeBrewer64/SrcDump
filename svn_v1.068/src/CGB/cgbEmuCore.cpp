/**
 * @file cgbEmuCore.cpp
 * @author zhfang & chentian
 * @date 2009.11.25
 * @brief TRL Emulate For CTR - Emu Core CGB
 */
#include "cgbEmuCore.h"
#include "cgbMemory.h"
#include "cgbRegister.h"
#include "cgbCard.h"
#include "cgbGraphic.h"
#include "cgbSound.h"
#include "cgbCPU.h"
#include "cgbDMA.h"
#include "cgbInput.h"
#include "cgbTime.h"
#include "cgbSerial.h"
#include "cgbDMGPalette.h"

/** @name Macro Define */
//@{
#define CGB_EMU_SAVEDATA	9										///< EmuCore Save Data Count
//@}

/** @name Global Variable */
//@{
trlSEmuShellBuffer*			g_pCgbEmuBuf = NULL;					///< Emu Engine Buffer Data
trlSEmuShellCore			g_sEmuCoreCGB = {
	cgbEmuCoreInit,
	cgbEmuCoreRunOneFrame,
	cgbEmuCoreReset,
	cgbKeyUpdate,
	cgbEmuCoreResume,
	cgbEmuCoreExit,
	cgbEmuCorePatch,
	cgbEmuCoreGetPalette,
	cgbEmuCoreSetPalette,
	cgbEmuCoreSwapPalette,
	NULL };
trlSEmuShellResume			g_sCgbEmuSaveData[CGB_EMU_SAVEDATA];	///< EmuCore Save Data
//@}

/** @brief EmuCore Initialize */
void cgbEmuCoreInit(trlSEmuShellBuffer* pBuf)
{
	g_pCgbEmuBuf = pBuf;

	// Initialize
	cgbMemInit();
	cgbCardInit();
	cgbRegInit();
	cgbTimeInit();
	cgbDmaInit();
	cgbEmuCoreConfig();
	cgbGrpInit();
	cgbSndInit();
	cgbKeyInit();
	cgbSerialInit();
	cgbCpuInit();

	// Save Data
	g_sCgbEmuSaveData[0].SetData(&g_sCgbConfigData.nDMGColor, 4, 7, 0);
	g_sCgbEmuSaveData[1].SetData(NULL, 4, 12, 14);
	g_sCgbEmuSaveData[2].SetData(NULL, 4, 10, 14);
	g_sCgbEmuSaveData[3].SetData(NULL, 4, 10, 14);
	g_sCgbEmuSaveData[4].SetData(&g_pCgbEmuBuf->nPatchMask, 4, 14, 0);
	g_sCgbEmuSaveData[5].SetData(&g_pCgbEmuBuf->nPatchPalette, 4, 14, 0);
	g_sCgbEmuSaveData[6].SetData(&g_pCgbEmuBuf->nPatchActive, 4, 14, 0);
	g_sCgbEmuSaveData[7].SetData(g_pCgbEmuBuf->sPatchActive, sizeof(trlSEmuShellPatchActive)*TRL_EMUCORE_PATCH_ACTIVEMAX, 14, 0);
	g_sCgbEmuSaveData[8].SetData(&g_pCgbEmuBuf->nFrameDouble, 4, 14, 0);

	g_pCgbEmuBuf->pSaveData[0].SetData(g_sCgbEmuSaveData, CGB_EMU_SAVEDATA, 7, 0);
	g_pCgbEmuBuf->pSaveData[1].SetData(g_sCgbMemSaveData, CGB_MEM_SAVEDATA, 1, 0);
	g_pCgbEmuBuf->pSaveData[2].SetData(g_sCgbCardSaveData, CGB_CARD_SAVEDATA, 1, 0);
	g_pCgbEmuBuf->pSaveData[3].SetData(g_sCgbTimeSaveData, CGB_TIME_SAVEDATA, 1, 0);
	g_pCgbEmuBuf->pSaveData[4].SetData(g_sCgbDmaSaveData, CGB_DMA_SAVEDATA, 1, 0);
	g_pCgbEmuBuf->pSaveData[5].SetData(g_sCgbGrpSaveData, CGB_GRP_SAVEDATA, 1, 0);
	g_pCgbEmuBuf->pSaveData[6].SetData(g_sCgbSndSaveData, CGB_SND_SAVEDATA, 1, 0);
	g_pCgbEmuBuf->pSaveData[7].SetData(g_sCgbSerialSaveData, CGB_SERIAL_SAVEDATA, 1, 0);
	g_pCgbEmuBuf->pSaveData[8].SetData(g_sCgbCpuSaveData, CGB_CPU_SAVEDATA, 1, 0);
}

/** @brief Update Palette Color */
inline void cgbEmuCoreUpdatePalette()
{
	g_nCgbGrpBGPal[0][0] = g_nCgbGrpDMGColor[g_pCgbRegBGP->rColor0];
	g_nCgbGrpBGPal[0][1] = g_nCgbGrpDMGColor[g_pCgbRegBGP->rColor1];
	g_nCgbGrpBGPal[0][2] = g_nCgbGrpDMGColor[g_pCgbRegBGP->rColor2];
	g_nCgbGrpBGPal[0][3] = g_nCgbGrpDMGColor[g_pCgbRegBGP->rColor3];
	g_nCgbGrpOBJPal[0][0] = g_nCgbGrpDMGColor[g_pCgbRegOBP0->rColor0+4];
	g_nCgbGrpOBJPal[0][1] = g_nCgbGrpDMGColor[g_pCgbRegOBP0->rColor1+4];
	g_nCgbGrpOBJPal[0][2] = g_nCgbGrpDMGColor[g_pCgbRegOBP0->rColor2+4];
	g_nCgbGrpOBJPal[0][3] = g_nCgbGrpDMGColor[g_pCgbRegOBP0->rColor3+4];
	g_nCgbGrpOBJPal[1][0] = g_nCgbGrpDMGColor[g_pCgbRegOBP1->rColor0+8];
	g_nCgbGrpOBJPal[1][1] = g_nCgbGrpDMGColor[g_pCgbRegOBP1->rColor1+8];
	g_nCgbGrpOBJPal[1][2] = g_nCgbGrpDMGColor[g_pCgbRegOBP1->rColor2+8];
	g_nCgbGrpOBJPal[1][3] = g_nCgbGrpDMGColor[g_pCgbRegOBP1->rColor3+8];
}

/** @brief EmuCore Patch */
void cgbEmuCorePatch(trlSEmuShellPatch* pPatch)
{
	switch(pPatch->sData.sA.nMode)
	{
	case 7:
	case 4:	// Palette
		switch(pPatch->sData.sA.nType)
		{
		case 0:		// Begin
			{
				u32 nID = 0;
				if(g_sCgbConfigData.nDMGColor == 2)	// green
					nID += 5;

				for(u32 n=0; n<3; ++n)
					for(u32 m=0; m<4; ++m)
						if(pPatch->nPalette[m+nID]!=0xFFFFFFFF)
							g_nCgbGrpDMGColor[n*4+m] = pPatch->nPalette[m+nID];
				if(pPatch->nPalette[nID+4]!=0xFFFFFFFF)
					g_nCgbGrpDMGColor[12] = pPatch->nPalette[nID+4];
			}
			break;
		case 1:		// End
			switch(g_sCgbConfigData.nDMGColor)
			{
			case 0:  // gray
				for(u32 n=0; n<3; ++n)
					for(u32 m=0; m<4; ++m)
						g_nCgbGrpDMGColor[n*4+m] = g_sCgbConfigData.nGrayPal[m];
				g_nCgbGrpDMGColor[12] = g_sCgbConfigData.nGrayPal[4];
				break;
			case 2:  // green
				for(u32 n=0; n<3; ++n)
					for(u32 m=0; m<4; ++m)
						g_nCgbGrpDMGColor[n*4+m] = g_sCgbConfigData.nGreenPal[m];
				g_nCgbGrpDMGColor[12] = g_sCgbConfigData.nGreenPal[4];
				break;
			}
			break;
		}
		cgbEmuCoreUpdatePalette();
		break;
	}
}

/** @brief EmuCore RunOneFrame */
void cgbEmuCoreRunOneFrame()
{
#if ((TRL_EMUTYPE==0) || (TRL_EMUTYPE==1))
	if(g_pCgbEmuBuf->nFrameDouble)
		g_pCgbEmuBuf->nTexID = 1 - g_pCgbEmuBuf->nTexID;
	g_pCgbEmuBuf->pScreenBuf = (u16*)(g_pCgbEmuBuf->pTextureBuf[g_pCgbEmuBuf->nTexID]) + g_pCgbEmuBuf->nScreenBufOffset;

	trlTraceFrameBegin();
	g_nCgbBreakFlag = 0;

#if TRL_SOUND_CGB_FAST
	cgbSndRegWriteLog_LogBegin();
#endif

#if TRL_PATCH
	if(g_pCgbEmuBuf->bFrameDelayEnable == 2)
	{
#if TRL_SOUND_CGB_FAST
		cgbSndRegWriteLog_LogRun();
		cgbSndUpdateTicksOneFrame();
#else
		u32 nTimes = g_nCgbGrpTick1 * 154 / g_nCgbSndTick0;
		for(u32 n=0; n<nTimes; ++n)
			cgbSndUpdateTicks();
#endif
		if(g_pCgbEmuBuf->nFrameDelay > 0)
		{
			--g_pCgbEmuBuf->nFrameDelay;
			if(!g_pCgbEmuBuf->nFrameDelay)
				g_pCgbEmuBuf->bFrameDelayEnable = 0;
		}
		g_pCgbEmuBuf->nFrames++;
		return;
	}
#endif

	while(1)
	{
		// Update Dma
		if(g_nCgbDmaTicks)
		{
			if(g_nCgbDmaTicks <= g_nCgbCpuEventTicks)
			{
				g_nCgbCpuEventTicks -= g_nCgbDmaTicks;
				g_nCgbDmaTicks = 0;
			}
			else
			{
				g_nCgbDmaTicks -= g_nCgbCpuEventTicks;
				g_nCgbCpuEventTicks = 0;
			}
		}

		// Update CPU
		cgbCpuRun();
		g_nCgbCpuEventTicks = 0xFFFF;
		
		trlTraceTickAdd(g_nCgbCpuTicks);
#if TRL_SOUND_CGB_FAST
		cgbSndRegWriteLog_LogTicksAdd(g_nCgbCpuTicks);
#endif

		// Update Div
		g_nCgbDivTicks -= g_nCgbCpuTicks;
		if(g_nCgbDivTicks <= 0)
		{
			++(*g_pCgbRegDIV);
			g_nCgbDivTicks += CGB_DIV_TICKS;
		}
		if(g_nCgbCpuEventTicks > g_nCgbDivTicks)
			g_nCgbCpuEventTicks = g_nCgbDivTicks;

		// Update Graphic
		g_nCgbGrpTicks -= g_nCgbCpuTicks;
		if(g_nCgbGrpTicks <= 0)
			cgbGrpUpdateTicks();
		if(g_nCgbCpuEventTicks > g_nCgbGrpTicks)
			g_nCgbCpuEventTicks = g_nCgbGrpTicks;

		// Update Sound
#if !TRL_SOUND_CGB_FAST
		g_nCgbSndTicks -= g_nCgbCpuTicks;
		if(g_nCgbSndTicks <= 0)
		{
			g_nCgbSndTicks += g_nCgbSndTick0;
			cgbSndUpdateTicks();
		}
		if(g_nCgbCpuEventTicks > g_nCgbSndTicks)
			g_nCgbCpuEventTicks = g_nCgbSndTicks;
#endif
		// Update Time
		if(g_pCgbRegTAC->rTimerStop)
		{
			cgbTimeUpdate();
			if(g_nCgbCpuEventTicks > g_nCgbTimeTicks)
				g_nCgbCpuEventTicks = g_nCgbTimeTicks;
		}
		g_nCgbTimeValue -= g_nCgbCpuTicks;
		while(g_nCgbTimeValue < 0)
			g_nCgbTimeValue += 0x100;

		// Update Serial
		if(g_pCgbRegSC->rTransfer)
		{
			if(g_pCgbRegSC->rClockShift)
			{
				g_nCgbSerialTicks -= g_nCgbCpuTicks;
				if(g_nCgbSerialTicks <= 0)
				{
					g_nCgbSerialTicks += g_nCgbSerialTick0;
					cgbSerialUpdate();
				}
				if(g_nCgbCpuEventTicks > g_nCgbSerialTicks)
					g_nCgbCpuEventTicks = g_nCgbSerialTicks;
			}
		}

		if(g_nCgbBreakFlag)
			break;
	}
#if TRL_SOUND_CGB_FAST
	cgbSndRegWriteLog_LogRun();
	cgbSndUpdateTicksOneFrame();
#endif
	g_pCgbEmuBuf->nFrames++;
	trlTraceFrameEnd();
#endif
}

/** @brief EmuCore Reset */
void cgbEmuCoreReset()
{
	if(g_nCgbGameType == CGB_GAMETYPE_DMG)
		cgbEmuCoreSwapPalette(3);

	cgbCpuReset();
	cgbMemReset();
	cgbCardReset();
	cgbRegReset();
	cgbTimeReset();
	cgbDmaReset();
	cgbGrpReset();
	cgbSndReset();
	cgbKeyReset();
	cgbSerialReset();
}

/** @brief EmuCore Resume */
void cgbEmuCoreResume()
{
	if(g_nCgbGameType == CGB_GAMETYPE_DMG)
		cgbEmuCoreSwapPalette(3);
	else
		g_pCgbEmuBuf->funcChangeMaskMode(0);

	cgbMemResume();
	cgbCardResume();
	cgbTimeResume();
	cgbDmaResume();
	cgbGrpResume();
	cgbSndResume();
	cgbSerialResume();
	cgbCpuResume();
}

/** @brief EmuCore Exit */
void cgbEmuCoreExit()
{
	cgbGrpExit();
	cgbCardExit();
	cgbRegExit();
	cgbMemExit();
}

/** @brief EmuCore Config */
void cgbEmuCoreConfig()
{
	g_sCgbConfigData.nDMGColor = TRL_COLORDMG;
	if(g_nCgbGameType == CGB_GAMETYPE_DMG)
	{
		// Gary Palette
		g_sCgbConfigData.nGrayPal[0] = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_GRAY", "Color0", CGB_RGB(25,25,21));
		g_sCgbConfigData.nGrayPal[1] = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_GRAY", "Color1", CGB_RGB(20,20,17));
		g_sCgbConfigData.nGrayPal[2] = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_GRAY", "Color2", CGB_RGB(13,13,10));
		g_sCgbConfigData.nGrayPal[3] = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_GRAY", "Color3", CGB_RGB(5,5,3));
		g_sCgbConfigData.nGrayPal[4] = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_GRAY", "ColorLCD", CGB_RGB(25,25,21));

		// Green Palette
		g_sCgbConfigData.nGreenPal[0] = g_pCgbEmuBuf->funcConfigData("DMG_COLOR", "Color0", CGB_RGB(23,31,4));
		g_sCgbConfigData.nGreenPal[1] = g_pCgbEmuBuf->funcConfigData("DMG_COLOR", "Color1", CGB_RGB(19,29,5));
		g_sCgbConfigData.nGreenPal[2] = g_pCgbEmuBuf->funcConfigData("DMG_COLOR", "Color2", CGB_RGB(11,17,8));
		g_sCgbConfigData.nGreenPal[3] = g_pCgbEmuBuf->funcConfigData("DMG_COLOR", "Color3", CGB_RGB(9,9,9));
		g_sCgbConfigData.nGreenPal[4] = g_pCgbEmuBuf->funcConfigData("DMG_COLOR", "ColorLCD", CGB_RGB(20,27,7));

		// Color Palette
		//cgbDMGPaletteInit();
		//u16 nColor = cgbDMGPaletteGetColor(0);
		//nR = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_COLOR", "bgcolor0R", CGB_BGRA_R(nColor));
		//nG = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_COLOR", "bgcolor0G", CGB_BGRA_G(nColor));
		//nB = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_COLOR", "bgcolor0B", CGB_BGRA_B(nColor));
		//g_sCgbConfigData.nColorPal[0] = (nB << 1) | (nG << 6) | (nR << 11);
		//nColor = cgbDMGPaletteGetColor(1);
		//nR = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_COLOR", "bgcolor1R", CGB_BGRA_R(nColor));
		//nG = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_COLOR", "bgcolor1G", CGB_BGRA_G(nColor));
		//nB = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_COLOR", "bgcolor1B", CGB_BGRA_B(nColor));
		//g_sCgbConfigData.nColorPal[1] = (nB << 1) | (nG << 6) | (nR << 11);
		//nColor = cgbDMGPaletteGetColor(2);
		//nR = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_COLOR", "bgcolor2R", CGB_BGRA_R(nColor));
		//nG = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_COLOR", "bgcolor2G", CGB_BGRA_G(nColor));
		//nB = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_COLOR", "bgcolor2B", CGB_BGRA_B(nColor));
		//g_sCgbConfigData.nColorPal[2] = (nB << 1) | (nG << 6) | (nR << 11);
		//nColor = cgbDMGPaletteGetColor(3);
		//nR = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_COLOR", "bgcolor3R", CGB_BGRA_R(nColor));
		//nG = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_COLOR", "bgcolor3G", CGB_BGRA_G(nColor));
		//nB = g_pCgbEmuBuf->funcConfigData("DMG_COLOR_COLOR", "bgcolor3B", CGB_BGRA_B(nColor));
		//g_sCgbConfigData.nColorPal[3] = (nB << 1) | (nG << 6) | (nR << 11);

		//nColor = cgbDMGPaletteGetColor(4);
		//nR = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj0color0R", CGB_BGRA_R(nColor));
		//nG = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj0color0G", CGB_BGRA_G(nColor));
		//nB = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj0color0B", CGB_BGRA_B(nColor));
		//g_sCgbConfigData.nColorPal[4] = (nB << 1) | (nG << 6) | (nR << 11);
		//nColor = cgbDMGPaletteGetColor(5);
		//nR = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj0color1R", CGB_BGRA_R(nColor));
		//nG = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj0color1G", CGB_BGRA_G(nColor));
		//nB = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj0color1B", CGB_BGRA_B(nColor));
		//g_sCgbConfigData.nColorPal[5] = (nB << 1) | (nG << 6) | (nR << 11);
		//nColor = cgbDMGPaletteGetColor(6);
		//nR = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj0color2R", CGB_BGRA_R(nColor));
		//nG = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj0color2G", CGB_BGRA_G(nColor));
		//nB = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj0color2B", CGB_BGRA_B(nColor));
		//g_sCgbConfigData.nColorPal[6] = (nB << 1) | (nG << 6) | (nR << 11);
		//nColor = cgbDMGPaletteGetColor(7);
		//nR = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj0color3R", CGB_BGRA_R(nColor));
		//nG = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj0color3G", CGB_BGRA_G(nColor));
		//nB = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj0color3B", CGB_BGRA_B(nColor));
		//g_sCgbConfigData.nColorPal[7] = (nB << 1) | (nG << 6) | (nR << 11);

		//nColor = cgbDMGPaletteGetColor(8);
		//nR = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj1color0R", CGB_BGRA_R(nColor));
		//nG = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj1color0G", CGB_BGRA_G(nColor));
		//nB = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj1color0B", CGB_BGRA_B(nColor));
		//g_sCgbConfigData.nColorPal[8] = (nB << 1) | (nG << 6) | (nR << 11);
		//nColor = cgbDMGPaletteGetColor(9);
		//nR = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj1color1R", CGB_BGRA_R(nColor));
		//nG = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj1color1G", CGB_BGRA_G(nColor));
		//nB = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj1color1B", CGB_BGRA_B(nColor));
		//g_sCgbConfigData.nColorPal[9] = (nB << 1) | (nG << 6) | (nR << 11);
		//nColor = cgbDMGPaletteGetColor(10);
		//nR = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj1color2R", CGB_BGRA_R(nColor));
		//nG = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj1color2G", CGB_BGRA_G(nColor));
		//nB = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj1color2B", CGB_BGRA_B(nColor));
		//g_sCgbConfigData.nColorPal[10] = (nB << 1) | (nG << 6) | (nR << 11);
		//nColor = cgbDMGPaletteGetColor(11);
		//nR = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj1color3R", CGB_BGRA_R(nColor));
		//nG = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj1color3G", CGB_BGRA_G(nColor));
		//nB = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "obj1color3B", CGB_BGRA_B(nColor));
		//g_sCgbConfigData.nColorPal[11] = (nB << 1) | (nG << 6) | (nR << 11);

		//nR = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "LCDcolorR", 31);
		//nG = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "LCDcolorG", 31);
		//nB = g_pCgbEmuBuf->funcConfigData("[DMG_COLOR_COLOR]", "LCDcolorB", 31);
		//g_sCgbConfigData.nColorPal[12] = (nB << 1) | (nG << 6) | (nR << 11);

		cgbEmuCoreSwapPalette(g_sCgbConfigData.nDMGColor);

		// Clear LCD
		u16 nColorLCD = g_nCgbGrpDMGColor[12];
		u16* pBuf0 = (u16*)g_pCgbEmuBuf->pTextureBuf[0];
		u16* pBuf1 = (u16*)g_pCgbEmuBuf->pTextureBuf[1];
		u32 nHeight = g_pCgbEmuBuf->nHeight + (g_pCgbEmuBuf->nScreenBufOffset / TRL_EMUCORE_TEX_X) * 2;
		u32 nWidth = g_pCgbEmuBuf->nWidth + (g_pCgbEmuBuf->nScreenBufOffset % TRL_EMUCORE_TEX_X) * 2;
		for(u32 n=0; n<nHeight; ++n)
		{
			for(u32 m=0; m<nWidth; ++m)
				pBuf0[m] = pBuf1[m] = nColorLCD;
			pBuf0 += TRL_EMUCORE_TEX_X;
			pBuf1 += TRL_EMUCORE_TEX_X;
		}
	}
	g_sCgbConfigData.nSoundSwapLR = g_pCgbEmuBuf->funcConfigData("CGB", "SoundSwapLR", 0);
}

/** @brief Get Palette Color */
u16 cgbEmuCoreGetPalette(u32 nIndex)
{
	return g_nCgbGrpDMGColor[nIndex];
}

/** @brief Set Palette Color */
void cgbEmuCoreSetPalette(u32 nIndex, u16 nColor, u32 bGray)
{
	g_nCgbGrpDMGColor[nIndex] = nColor;
	if(nIndex == 12)
		return;

	if(bGray)
	{
		g_nCgbGrpDMGColor[nIndex+4] = nColor;
		g_nCgbGrpDMGColor[nIndex+8] = nColor;
	}

	cgbEmuCoreUpdatePalette();
}

/** @brief Swap DMG Palette Mode */
u32 cgbEmuCoreSwapPalette(s32 nMode)
{
	if((g_nCgbGameType != CGB_GAMETYPE_DMG) || (nMode == -1))
		return g_sCgbConfigData.nDMGColor;

	switch(nMode)
	{
	case 0:
		g_sCgbConfigData.nDMGColor = 0;
		g_pCgbEmuBuf->funcChangeMaskMode(0);
		g_pCgbEmuBuf->funcChangeFilterMode(0);
		break;
	case 1:
		g_sCgbConfigData.nDMGColor = 1;
		break;
	case 2:
		if(g_sCgbConfigData.nDMGColor == 0 || g_sCgbConfigData.nDMGColor == 1)
		{
			g_sCgbConfigData.nDMGColor = 2;
			g_pCgbEmuBuf->funcChangeMaskMode(1);
			g_pCgbEmuBuf->funcChangeFilterMode(1);
		}
		else
		{
			g_sCgbConfigData.nDMGColor = 0;
			g_pCgbEmuBuf->funcChangeMaskMode(0);
			g_pCgbEmuBuf->funcChangeFilterMode(0);
		}
		break;
	case 3:
		switch(g_sCgbConfigData.nDMGColor)
		{
		case 0:
			g_pCgbEmuBuf->funcChangeMaskMode(0);
			g_pCgbEmuBuf->funcChangeFilterMode(0);
			break;
		case 1:
			break;
		case 2:
			g_pCgbEmuBuf->funcChangeMaskMode(1);
			g_pCgbEmuBuf->funcChangeFilterMode(1);
			break;
		}
		break;
	default:
		g_sCgbConfigData.nDMGColor = 1 - g_sCgbConfigData.nDMGColor;
		break;
	}

	switch(g_sCgbConfigData.nDMGColor)
	{
	case 0:  // gray
		for(u32 n=0; n<3; ++n)
			for(u32 m=0; m<4; ++m)
				g_nCgbGrpDMGColor[n*4+m] = g_sCgbConfigData.nGrayPal[m];
		g_nCgbGrpDMGColor[12] = g_sCgbConfigData.nGrayPal[4];
		break;
	case 1:  // color
		for(u32 n=0; n<13; ++n)
			g_nCgbGrpDMGColor[n] = g_sCgbConfigData.nColorPal[n];
		break;
	case 2:  // green
		for(u32 n=0; n<3; ++n)
			for(u32 m=0; m<4; ++m)
				g_nCgbGrpDMGColor[n*4+m] = g_sCgbConfigData.nGreenPal[m];
		g_nCgbGrpDMGColor[12] = g_sCgbConfigData.nGreenPal[4];
		break;
	}

#if TRL_PATCH
	// Patch
	if(g_pCgbEmuBuf->nPatchPalette != 0xFFFFFFFF)
	{
		trlSEmuShellPatch* pPatch = &g_pCgbEmuBuf->pPatchData[g_pCgbEmuBuf->nPatchPalette];
		u32 nID = 0;
		if(g_sCgbConfigData.nDMGColor == 2)	// green
			nID += 5;

		for(u32 n=0; n<3; ++n)
			for(u32 m=0; m<4; ++m)
				if(pPatch->nPalette[m+nID]!=0xFFFFFFFF)
					g_nCgbGrpDMGColor[n*4+m] = pPatch->nPalette[m+nID];
		if(pPatch->nPalette[nID+4]!=0xFFFFFFFF)
			g_nCgbGrpDMGColor[12] = pPatch->nPalette[nID+4];
	}
#endif

	// Change LCD Color
	u16 nColorLCD = g_nCgbGrpDMGColor[12];
	u16* pBuf0 = (u16*)g_pCgbEmuBuf->pTextureBuf[0];
	u16* pBuf1 = (u16*)g_pCgbEmuBuf->pTextureBuf[1];
	u32 nFrameHeight = g_pCgbEmuBuf->nScreenBufOffset / TRL_EMUCORE_TEX_X;
	u32 nFrameWidth = g_pCgbEmuBuf->nScreenBufOffset % TRL_EMUCORE_TEX_X;
	u32 nFrameLine = g_pCgbEmuBuf->nWidth + nFrameWidth * 2;
	for(u32 n=0; n<nFrameHeight; ++n)
	{
		for(u32 m=0; m<nFrameLine; ++m)
			pBuf0[m] = pBuf1[m] = nColorLCD;
		pBuf0 += TRL_EMUCORE_TEX_X;
		pBuf1 += TRL_EMUCORE_TEX_X;
	}
	for(s32 n=0; n<g_pCgbEmuBuf->nHeight; ++n)
	{
		for(u32 m=0; m<nFrameWidth; ++m)
		{
			pBuf0[m] = pBuf1[m] = nColorLCD;
			pBuf0[g_pCgbEmuBuf->nWidth+m+nFrameWidth] = nColorLCD;
			pBuf1[g_pCgbEmuBuf->nWidth+m+nFrameWidth] = nColorLCD;
		}
		pBuf0 += TRL_EMUCORE_TEX_X;
		pBuf1 += TRL_EMUCORE_TEX_X;
	}
	for(u32 n=0; n<nFrameHeight; ++n)
	{
		for(u32 m=0; m<nFrameLine; ++m)
			pBuf0[m] = pBuf1[m] = nColorLCD;
		pBuf0 += TRL_EMUCORE_TEX_X;
		pBuf1 += TRL_EMUCORE_TEX_X;
	}

	// Update Pal
	cgbEmuCoreUpdatePalette();
	return g_sCgbConfigData.nDMGColor;
}
