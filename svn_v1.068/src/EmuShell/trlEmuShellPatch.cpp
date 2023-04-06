/**
 * @file trlEmuShellPatch.h
 * @author zhfang, chentian
 * @date 2011.03.31
 * @brief TRL Emulate - EmuShell Patch Module
 */
#include "trlEmuShellVideo.h"
#include "trlEmuShellData.h"
#include "trlEmuShellPatch.h"

#if TRL_PATCH
/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
extern trlSEmuShellVideoMask	g_sTrlVideoMaskData;

static const char				g_szEmuShellPatchValueName[TRL_EMUCORE_PATCH_DATAMAX][16]	= {
	"Mode", "Type", "Index", "Address", "MemAddress", "Fixcode", "DelayFrame", "FadeFrame",
	"DarkEnable0", "DarkEnable1", "ReduceEnable0", "ReduceEnable1", "MotionBEnable0", "MotionBEnable1",	"Dark0", "Dark1", 
	"ReduceColorR0", "ReduceColorR1", "ReduceColorG0", "ReduceColorG1", "ReduceColorB0", "ReduceColorB1", "MotionBlur0", "MotionBlur1",
	"ConditionType", "ConditionValueA", "ConditionValueB", "ConditionValueC"};
//@}

/** @brief Patch Active End */
inline void trlEmuShellPatchActiveEnd(u32& nIndex)
{
	g_sEmuShellBuffer.nPatchActive--;
	if(nIndex==g_sEmuShellBuffer.nPatchActive)
		g_sEmuShellBuffer.sPatchActive[nIndex].Clear();
	else
	{
		g_sEmuShellBuffer.sPatchActive[nIndex] = g_sEmuShellBuffer.sPatchActive[g_sEmuShellBuffer.nPatchActive];
		g_sEmuShellBuffer.sPatchActive[g_sEmuShellBuffer.nPatchActive].Clear();
		nIndex--;
	}
}

#if 0
void trlBGHack_TCFNY279(u8* bgsrn, u8 reg_Y)
{
	struct hack_data{
		u16	addr;
		u8	value;
	};

	struct hack_data hd1[15]={
		{0x11A, 0x49},
		{0x11B, 0x49},
		{0x13A, 0x49},
		{0x13B, 0x49},
		{0x15A, 0x49},
		{0x15B, 0x49},
		{0x17A, 0x49},
		{0x17B, 0x49},
		{0x19A, 0x49},
		{0x19B, 0x49},
		{0x1BA, 0x49},
		{0x1BB, 0x49},
		{0x1DA, 0xF0},
		{0x1DB, 0x49},
		{0x1FB, 0xF1},
	};

	struct hack_data hd2[11]={
		{0x0D4, 0x49},
		//{0x0D5, 0x49},
		{0x0F4, 0x49},
		{0x0F5, 0x49},
		{0x114, 0x49},
		{0x115, 0x49},
		{0x134, 0x49},
		{0x135, 0x49},
		{0x154, 0x49},
		{0x155, 0x49},
		{0x174, 0xE4},
		{0x175, 0xE5},
	};

	struct hack_data hd3[14]={
		{0x0D8, 0x49},
		//{0x0D9, 0x49},
		{0x0F8, 0x49},
		//{0x0F9, 0x49},
		{0x118, 0x49},
		{0x119, 0x49},
		{0x138, 0x49},
		{0x139, 0x49},
		{0x158, 0x49},
		{0x159, 0x49},
		{0x178, 0x49},
		{0x179, 0x49},
		{0x198, 0x49},
		{0x199, 0x49},
		{0x1B8, 0xE7},
		{0x1B9, 0xE5},
	};

	struct hack_data hd4[20]={
		{0x096, 0x49},
		{0x097, 0x49},
		{0x0B6, 0x49},
		{0x0B7, 0x49},
		{0x0D6, 0x49},
		{0x0D7, 0x49},
		{0x0F6, 0x49},
		{0x0F7, 0x49},
		{0x116, 0x49},
		{0x117, 0x49},
		{0x136, 0x49},
		{0x137, 0x49},
		{0x156, 0x49},
		{0x157, 0x49},
		{0x176, 0x49},
		{0x177, 0x49},
		{0x196, 0x49},
		{0x197, 0x49},
		{0x1B6, 0xE4},
		{0x1B7, 0xE6},
	};

	int i;
	switch(reg_Y){
		case 0x15:
			for(i=0;i<15;i++)
				bgsrn[hd1[i].addr]=hd1[i].value;
			break;
		case 0x11:
			for(i=0;i<11;i++)
				bgsrn[hd2[i].addr]=hd2[i].value;
			break;
		case 0x14:
			for(i=0;i<14;i++)
				bgsrn[hd3[i].addr]=hd3[i].value;
			break;
		case 0x1A:
			for(i=0;i<20;i++)
				bgsrn[hd4[i].addr]=hd4[i].value;
			break;
	}
	return;
}
#endif

/** @brief EmuShell Patch Main */
void trlEmuShellPatchMain()
{
	for(u32 n=0; n<g_sEmuShellBuffer.nPatchActive; ++n)
	{
		trlSEmuShellPatchActive* pActive = &g_sEmuShellBuffer.sPatchActive[n];
		if(pActive->nDelay < g_sEmuShellBuffer.pPatchData[pActive->nIndex].sData.sA.nDelayFrame)
			pActive->nDelay++;
		else
		{
			switch(pActive->nMode)
			{
			case 3:	// Mask
				switch(g_sEmuShellBuffer.pPatchData[pActive->nIndex].sData.sA.nType)
				{
				case 0:		// Begin
					g_sEmuShellBuffer.nPatchMask = pActive->nIndex;
					if(g_sEmuShellBuffer.pPatchData[pActive->nIndex].sData.sA.nFadeFrame)
					{
						trlSEmuShellPatch* pPatch = &g_sEmuShellBuffer.pPatchData[g_sEmuShellBuffer.nPatchMask];
						if(pPatch->sData.sA.bDarkEnable[g_sTrlVideoMaskData.nMode] != 0xFFFFFFFF)
						{
							g_sTrlVideoMaskData.pDarkEnable = &pPatch->sData.sA.bDarkEnable[g_sTrlVideoMaskData.nMode];
							if(!pActive->nValue)
							{
								if((*g_sTrlVideoMaskData.pDarkEnable) && (*g_sTrlVideoMaskData.pDark > pPatch->sData.sA.nDark[g_sTrlVideoMaskData.nMode]))
								{
									pActive->nValue = *g_sTrlVideoMaskData.pDark - 1;
									g_sTrlVideoMaskData.pDark = &pActive->nValue;
									pActive->nFade = 0;
								}
							}
							else
							{
								pActive->nFade++;
								if(pActive->nFade >= pPatch->sData.sA.nFadeFrame)
								{
									pActive->nFade = 0;
									pActive->nValue--;
									if(pActive->nValue > pPatch->sData.sA.nDark[g_sTrlVideoMaskData.nMode])
										g_sTrlVideoMaskData.pDark = &pActive->nValue;
									else
									{
										pActive->nValue = 0;
										g_sTrlVideoMaskData.pDark = &pPatch->sData.sA.nDark[g_sTrlVideoMaskData.nMode];
									}
								}
							}
						}
						else
						{
							g_sTrlVideoMaskData.pDarkEnable = &g_sTrlVideoMaskData.bDarkEnable[g_sTrlVideoMaskData.nMode];
							g_sTrlVideoMaskData.pDark = &g_sTrlVideoMaskData.nDark[g_sTrlVideoMaskData.nMode];
						}
						if(pPatch->sData.sA.bReduceEnable[g_sTrlVideoMaskData.nMode] != 0xFFFFFFFF)
						{
							g_sTrlVideoMaskData.pReduceEnable = &pPatch->sData.sA.bReduceEnable[g_sTrlVideoMaskData.nMode];
							g_sTrlVideoMaskData.pReduceColorR = &pPatch->sData.sA.nReduceColorR[g_sTrlVideoMaskData.nMode];
							g_sTrlVideoMaskData.pReduceColorG = &pPatch->sData.sA.nReduceColorG[g_sTrlVideoMaskData.nMode];
							g_sTrlVideoMaskData.pReduceColorB = &pPatch->sData.sA.nReduceColorB[g_sTrlVideoMaskData.nMode];
						}
						else
						{
							g_sTrlVideoMaskData.pReduceEnable = &g_sTrlVideoMaskData.bReduceEnable[g_sTrlVideoMaskData.nMode];
							g_sTrlVideoMaskData.pReduceColorR = &g_sTrlVideoMaskData.nReduceColorR[g_sTrlVideoMaskData.nMode];
							g_sTrlVideoMaskData.pReduceColorG = &g_sTrlVideoMaskData.nReduceColorG[g_sTrlVideoMaskData.nMode];
							g_sTrlVideoMaskData.pReduceColorB = &g_sTrlVideoMaskData.nReduceColorB[g_sTrlVideoMaskData.nMode];
						}
						if(pPatch->sData.sA.bMotionBEnable[g_sTrlVideoMaskData.nMode] != 0xFFFFFFFF)
						{
							g_sTrlVideoMaskData.pMotionBEnable = &pPatch->sData.sA.bMotionBEnable[g_sTrlVideoMaskData.nMode];
							g_sTrlVideoMaskData.pMotionBlur = &pPatch->sData.sA.nMotionBlur[g_sTrlVideoMaskData.nMode];
						}
						else
						{
							g_sTrlVideoMaskData.pMotionBEnable = &g_sTrlVideoMaskData.bMotionBEnable[g_sTrlVideoMaskData.nMode];
							g_sTrlVideoMaskData.pMotionBlur = &g_sTrlVideoMaskData.nMotionBlur[g_sTrlVideoMaskData.nMode];
						}

						trlEmuShellVideoMaskMode();
						trlEmuShellVideoMotionBlur();
						if(!pActive->nValue)
							trlEmuShellPatchActiveEnd(n);
					}
					else
					{
						trlEmuShellVideoMaskChangeMode(g_sTrlVideoMaskData.nMode);
						trlEmuShellPatchActiveEnd(n);
					}
					break;
				case 1:		// End
					g_sEmuShellBuffer.nPatchMask = 0xFFFFFFFF;
					trlEmuShellVideoMaskChangeMode(g_sTrlVideoMaskData.nMode);
					trlEmuShellPatchActiveEnd(n);
					break;
				}
				break;
			case 7:
				switch(g_sEmuShellBuffer.pPatchData[pActive->nIndex].sData.sA.nType)
				{
				case 0:		// Begin
					g_sEmuShellBuffer.nPatchMask = pActive->nIndex;					
					g_sEmuShellBuffer.nPatchPalette = pActive->nIndex;					
					break;
				case 1:		// End
					g_sEmuShellBuffer.nPatchMask = 0xFFFFFFFF;
					g_sEmuShellBuffer.nPatchPalette = 0xFFFFFFFF;					
					break;
				}
				trlEmuShellVideoMaskChangeMode(g_sTrlVideoMaskData.nMode);
				g_pEmuShellCore->trlEmuCorePatch(&g_sEmuShellBuffer.pPatchData[pActive->nIndex]);
				trlEmuShellPatchActiveEnd(n);
				break;
			case 4:	// Palette
				switch(g_sEmuShellBuffer.pPatchData[pActive->nIndex].sData.sA.nType)
				{
				case 0:		// Begin
					g_sEmuShellBuffer.nPatchPalette = pActive->nIndex;
					break;
				case 1:		// End
					g_sEmuShellBuffer.nPatchPalette = 0xFFFFFFFF;
					break;
				}
				g_pEmuShellCore->trlEmuCorePatch(&g_sEmuShellBuffer.pPatchData[pActive->nIndex]);
				trlEmuShellPatchActiveEnd(n);
				break;
			case 5:	// Double Frame
				switch(g_sEmuShellBuffer.pPatchData[pActive->nIndex].sData.sA.nType)
				{
				case 0:		// Begin
					g_sEmuShellBuffer.nFrameDouble = 1;
					trlMemCopy(g_sEmuShellBuffer.pTextureBuf[1-g_sEmuShellBuffer.nTexID], g_sEmuShellBuffer.pTextureBuf[g_sEmuShellBuffer.nTexID], g_sEmuShellBuffer.nTexHeight*g_sEmuShellBuffer.nTexWidth*2);
					break;
				case 1:		// End
					g_sEmuShellBuffer.nFrameDouble = 0;
					break;
				}
				trlEmuShellPatchActiveEnd(n);
				break;
			case 10:	// Patch for FDS switch ROM.
				//using type value for skip frame number;
				extern trlSEmuShellBuffer*		g_pNesEmuBuf;
				g_pNesEmuBuf->nSwitchDisk += g_sEmuShellBuffer.pPatchData[pActive->nIndex].sData.sA.nType;
				trlEmuShellPatchActiveEnd(n);
				break;
#if 0
			case 8: //BG lock
				static bool bLock = false;
				switch(g_sEmuShellBuffer.pPatchData[pActive->nIndex].sData.sA.nType)
				{
				case 0:		// lock
					bLock = true;
					break;
				case 1:		// reset lock
					if(bLock){
						bLock = false;
						u32 opcode=g_sEmuShellBuffer.pPatchData[pActive->nIndex].nOpcode;
						//add 3 nops.
						opcode&=0xFF;
						opcode|=0xEAEAEA00;
						g_sEmuShellBuffer.pPatchData[pActive->nIndex].nOpcode=opcode;
					}
					break;
				}
				trlEmuShellPatchActiveEnd(n);
				break;
#endif
			}
		}
	}
}

/** @brief Change Mask Mode */
void trlEmuShellPatchMaskChangeMode(u32 nMode)
{
	if(g_sEmuShellBuffer.nPatchMask != 0xFFFFFFFF)
	{
		trlSEmuShellPatch* pPatch = &g_sEmuShellBuffer.pPatchData[g_sEmuShellBuffer.nPatchMask];
		if(pPatch->sData.sA.bDarkEnable[nMode] != 0xFFFFFFFF)
		{
			g_sTrlVideoMaskData.pDarkEnable = &pPatch->sData.sA.bDarkEnable[nMode];
			g_sTrlVideoMaskData.pDark = &pPatch->sData.sA.nDark[nMode];
		}
		if(pPatch->sData.sA.bReduceEnable[nMode] != 0xFFFFFFFF)
		{
			g_sTrlVideoMaskData.pReduceEnable = &pPatch->sData.sA.bReduceEnable[nMode];
			g_sTrlVideoMaskData.pReduceColorR = &pPatch->sData.sA.nReduceColorR[nMode];
			g_sTrlVideoMaskData.pReduceColorG = &pPatch->sData.sA.nReduceColorG[nMode];
			g_sTrlVideoMaskData.pReduceColorB = &pPatch->sData.sA.nReduceColorB[nMode];
		}
		if(pPatch->sData.sA.bMotionBEnable[nMode] != 0xFFFFFFFF)
		{
			g_sTrlVideoMaskData.pMotionBEnable = &pPatch->sData.sA.bMotionBEnable[nMode];
			g_sTrlVideoMaskData.pMotionBlur = &pPatch->sData.sA.nMotionBlur[nMode];
		}
	}
}

/** @brief Load Patch File */
void trlEmuShellPatchLoad()
{
	u8 nPatchCode = 0;
	switch(g_sEmuShellBuffer.nRomType)
	{
	case TRL_EMUCORE_ROMTYPE_CGB:
		nPatchCode = 0xFC;
		break;
	case TRL_EMUCORE_ROMTYPE_AGB:
		break;
	case TRL_EMUCORE_ROMTYPE_NES:
		nPatchCode = 0xFB;
		break;
	}

	g_sEmuShellBuffer.pPatchData = (trlSEmuShellPatch*)trlMemAlloc(sizeof(trlSEmuShellPatch) * g_sEmuShellPatch.nCount, 4);
	memset(g_sEmuShellBuffer.pPatchData, 0xFF, sizeof(trlSEmuShellPatch) * g_sEmuShellPatch.nCount);
	trlSEmuShellConfigSection* pSection = g_sEmuShellPatch.sSection;
	trlSEmuShellConfigValue* pValue;
	trlSEmuShellPatch* pPatch = g_sEmuShellBuffer.pPatchData;
	for(u32 n=0; n<g_sEmuShellPatch.nCount; ++n, ++pSection)
	{
		pPatch->sData.sA.nDelayFrame = 0;
		pPatch->sData.sA.nFadeFrame = 0;
		pPatch->pFixcode = NULL;
		pPatch->pConditionValueA = NULL;
		pPatch->pConditionValueB = NULL;
		pPatch->pConditionValueC = NULL;

		for(u32 m=0; m<pSection->nCount; ++m)
		{
			pValue = &pSection->sValue[m];

			if(!strncmp("Palette", pValue->szName, 7))
			{
				u32 nPal = 0;
				u32 nLen = strlen(pValue->szName);
				for(u32 i=7; i<nLen; ++i)
					nPal = nPal * 10 + pValue->szName[i] - 0x30;
				if(nPal<TRL_EMUCORE_PATCH_PALMAX)
					pPatch->nPalette[nPal] = pValue->nValue;
				continue;
			}

			for(u32 v = 0; v<TRL_EMUCORE_PATCH_DATAMAX; ++v)
			{
				if(!strcmp(g_szEmuShellPatchValueName[v], pValue->szName))
				{
					pPatch->sData.nD[v] = pValue->nValue;
					if(v == 5)
						pPatch->pFixcode = pValue->pValue;
					else if(v == 0x19)
						pPatch->pConditionValueA = pValue->pValue;
					else if(v == 0x1A)
						pPatch->pConditionValueB = pValue->pValue;
					else if(v == 0x1B)
						pPatch->pConditionValueC = pValue->pValue;
					break;
				}
			}

		}
		switch(pPatch->sData.sA.nMode)
		{
		case 1: // Fixcode
			if(pPatch->pFixcode)
				trlMemCopy(&((u8*)g_sEmuShellBuffer.pRomBuf)[pPatch->sData.sA.nAddress], pPatch->pFixcode, pPatch->sData.sA.nFixcode);
			else
				((u8*)g_sEmuShellBuffer.pRomBuf)[pPatch->sData.sA.nAddress] = pPatch->sData.sA.nFixcode;
			pPatch->pFixcode = NULL;
			memset(pPatch, 0xFF, sizeof(trlSEmuShellPatch));
			break;
		//case 8: //BG change
		//	break;
		case 2: // Fixvalue
			if(pPatch->sData.sA.nIndex == 0xFFFFFFFF)
				pPatch->sData.sA.nIndex = pPatch->sData.sA.nType;
		default:
			pPatch->nOpcode = ((u8*)g_sEmuShellBuffer.pRomBuf)[pPatch->sData.sA.nAddress];			
			++pPatch;
			++g_sEmuShellBuffer.nPatchCount;
		}
	}
	for(int i=0;i<g_sEmuShellBuffer.nPatchCount;i++)
	{
		((u8*)g_sEmuShellBuffer.pRomBuf)[g_sEmuShellBuffer.pPatchData[i].sData.sA.nAddress] = nPatchCode;
	}

}
#endif //if PACTH
