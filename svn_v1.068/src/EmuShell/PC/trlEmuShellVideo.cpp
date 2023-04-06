/**
 * @file trlEmuShellVideo_PC.cpp
 * @author Chentian
 * @date 2011.08.26
 * @brief TRL Emulate For PC - EmuShell Video Module
 */
#include "..\trlEmuShellVideo.h"
#include "..\trlEmuShellFont.h"
#include "..\trlEmuShellData.h"
#include "..\trlEmuShellPatch.h"
#include "..\trlEmuShellStruct.h"


//#include <atlbase.h>
//#include <atltypes.h>

/** @name Macro Define */
//@{
#define TRL_DEBUGDISP_FONTSIZE	14
//@}

/** @name Global Variable */
//@{
char					g_szTrlVidioString[128];
trlSEmuShellVideoMask	g_sTrlVideoMaskData;
RECT					g_hTrlVideoDrawRect;
HDC						g_hTrlVideoDC;
HFONT					g_hTrlVideoFont;
BITMAPV4HEADER			g_hTrlVideoBmi;
//@}

/** @brief Init Frame */
inline void trlEmuShellVideoInitFrame()
{
	g_sEmuShellBuffer.nTexWidth = TRL_EMUCORE_TEX_X;
	g_sEmuShellBuffer.nTexHeight = TRL_EMUCORE_TEX_Y;
	g_sEmuShellBuffer.pTextureBuf[0] = trlMemAllocDevice(TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2, 128);
	g_sEmuShellBuffer.pTextureBuf[1] = trlMemAllocDevice(TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2, 128);
	g_sEmuShellBuffer.pScreenBuf = g_sEmuShellBuffer.pTextureBuf[0];
	g_sEmuShellBuffer.nTexID = 0;
	memset(g_sEmuShellBuffer.pTextureBuf[0], 0, TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2);
	memset(g_sEmuShellBuffer.pTextureBuf[1], 0, TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2);
}

/** @brief Init */
void trlEmuShellVideoInit(u32 nPara)
{
	trlEmuShellVideoInitFrame();

	//g_hTrlVideoDrawRect.SetRect(4,0,g_sEmuShellBuffer.nWidth-4, TRL_DEBUGDISP_FONTSIZE);
	g_hTrlVideoDrawRect.left = 4;
	g_hTrlVideoDrawRect.right = g_sEmuShellBuffer.nWidth-4;
	g_hTrlVideoDrawRect.top = 0;
	g_hTrlVideoDrawRect.bottom = TRL_DEBUGDISP_FONTSIZE;
	
	g_hTrlVideoFont = CreateFont(TRL_DEBUGDISP_FONTSIZE,0,0,0,FW_NORMAL,FALSE,FALSE,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"Arial");
	g_hTrlVideoDC = GetDC((HWND)nPara);
	SetBkColor(g_hTrlVideoDC, RGB(255,255,255));
	SetTextColor(g_hTrlVideoDC, RGB(0,0,0));
	SelectObject(g_hTrlVideoDC, g_hTrlVideoFont);

	memset(&g_hTrlVideoBmi, 0, sizeof(g_hTrlVideoBmi));
	g_hTrlVideoBmi.bV4Size			= sizeof(BITMAPV4HEADER);
	g_hTrlVideoBmi.bV4Width			= g_sEmuShellBuffer.nTexWidth;
	g_hTrlVideoBmi.bV4Height		= -g_sEmuShellBuffer.nTexHeight;
	g_hTrlVideoBmi.bV4Planes		= 1;
	g_hTrlVideoBmi.bV4BitCount		= 16;
	g_hTrlVideoBmi.bV4V4Compression = BI_BITFIELDS;
	g_hTrlVideoBmi.bV4ClrUsed		= 1;

	if(g_sEmuShellBuffer.nRomType == TRL_EMUCORE_ROMTYPE_AGB)
	{
		g_hTrlVideoBmi.bV4RedMask	  = 0x001F;
		g_hTrlVideoBmi.bV4GreenMask   = 0x03E0;
		g_hTrlVideoBmi.bV4BlueMask    = 0x7C00;
	//	g_hTrlVideoBmi.bV4AlphaMask   = 0x8000;
	}
	else
	{
		g_hTrlVideoBmi.bV4RedMask	  = 0xF800;
		g_hTrlVideoBmi.bV4GreenMask   = 0x07C0;
		g_hTrlVideoBmi.bV4BlueMask    = 0x003E;
	//	g_hTrlVideoBmi.bV4AlphaMask   = 0x0001;
	}

	g_sEmuShellBuffer.funcChangeMaskMode = trlEmuShellVideoMaskChangeMode;

	// Init Mask
	g_sTrlVideoMaskData.bDarkEnable[0] = trlEmuShellDataGetConfigData("Mask", "DarkEnable0", 0);
	g_sTrlVideoMaskData.bReduceEnable[0] = trlEmuShellDataGetConfigData("Mask", "ReduceEnable0", 0);
	g_sTrlVideoMaskData.bMotionBEnable[0] = trlEmuShellDataGetConfigData("Mask", "MotionBEnable0", 0);
	g_sTrlVideoMaskData.nDark[0] = trlEmuShellDataGetConfigData("Mask", "Dark0", 10);
	g_sTrlVideoMaskData.nReduceColorR[0] = trlEmuShellDataGetConfigData("Mask", "ReduceColorR0", 0);
	g_sTrlVideoMaskData.nReduceColorG[0] = trlEmuShellDataGetConfigData("Mask", "ReduceColorG0", 0);
	g_sTrlVideoMaskData.nReduceColorB[0] = trlEmuShellDataGetConfigData("Mask", "ReduceColorB0", 0);
	g_sTrlVideoMaskData.nMotionBlur[0] = trlEmuShellDataGetConfigData("Mask", "MotionBlur0", 8);
	
	g_sTrlVideoMaskData.bDarkEnable[1] = trlEmuShellDataGetConfigData("Mask", "DarkEnable1", 0);
	g_sTrlVideoMaskData.bReduceEnable[1] = trlEmuShellDataGetConfigData("Mask", "ReduceEnable1", 0);
	g_sTrlVideoMaskData.bMotionBEnable[1] = trlEmuShellDataGetConfigData("Mask", "MotionBEnable1", 0);
	g_sTrlVideoMaskData.nDark[1] = trlEmuShellDataGetConfigData("Mask", "Dark1", 10);
	g_sTrlVideoMaskData.nReduceColorR[1] = trlEmuShellDataGetConfigData("Mask", "ReduceColorR1", 0);
	g_sTrlVideoMaskData.nReduceColorG[1] = trlEmuShellDataGetConfigData("Mask", "ReduceColorG1", 0);
	g_sTrlVideoMaskData.nReduceColorB[1] = trlEmuShellDataGetConfigData("Mask", "ReduceColorB1", 0);
	g_sTrlVideoMaskData.nMotionBlur[1] = trlEmuShellDataGetConfigData("Mask", "MotionBlur1", 8);

	trlEmuShellVideoMaskChangeMode(0);
}

/** @brief Clear */
void trlEmuShellVideoClear()
{
	RECT rect = {
		0,g_sEmuShellBuffer.nHeight, g_sEmuShellBuffer.nWidth, g_sEmuShellBuffer.nHeight *2};
	FillRect(g_hTrlVideoDC, &rect, (HBRUSH) GetStockObject(WHITE_BRUSH));
}

/** @brief Draw Debug Info */
void trlEmuShellVideoDrawDebugInfo(u32 nLine, const char *szFormat, ...)
{
	va_list va;
	va_start(va, szFormat);
	s32 nStringSize = vsnprintf_s(g_szTrlVidioString, 128, 128, szFormat, va);
	va_end(va);
	if(nStringSize>0)
	{		
		COLORREF clr = SetTextColor(g_hTrlVideoDC, 0);

		g_hTrlVideoDrawRect.bottom = (nLine*TRL_DEBUGDISP_FONTSIZE+g_sEmuShellBuffer.nHeight) + g_hTrlVideoDrawRect.bottom - g_hTrlVideoDrawRect.top;
		g_hTrlVideoDrawRect.top = (nLine*TRL_DEBUGDISP_FONTSIZE+g_sEmuShellBuffer.nHeight);
		DrawText(g_hTrlVideoDC, g_szTrlVidioString, nStringSize, &g_hTrlVideoDrawRect, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOCLIP);
		SetTextColor(g_hTrlVideoDC, clr);
	}
}

/** @brief Draw Debug Warn */
void trlEmuShellVideoDrawDebugWarn(u32 nLine, const char *szFormat, ...)
{
	va_list va;
	va_start(va, szFormat);
	s32 nStringSize = vsnprintf_s(g_szTrlVidioString, 128, 128, szFormat, va);
	va_end(va);
	if(nStringSize>0)
	{		
		COLORREF clr = SetTextColor(g_hTrlVideoDC, RGB(0x00, 0x00, 0xFF));
		g_hTrlVideoDrawRect.bottom = g_hTrlVideoDrawRect.bottom - g_hTrlVideoDrawRect.top + (nLine*TRL_DEBUGDISP_FONTSIZE+g_sEmuShellBuffer.nHeight);
		g_hTrlVideoDrawRect.top = (nLine*TRL_DEBUGDISP_FONTSIZE+g_sEmuShellBuffer.nHeight);
		DrawText(g_hTrlVideoDC, g_szTrlVidioString, nStringSize, &g_hTrlVideoDrawRect, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOCLIP);
		SetTextColor(g_hTrlVideoDC, clr);
	}
}

/** @brief Draw Text */
void trlEmuShellVideoDrawText(u32 nColor, u32 nX, u32 nY, const char *szFormat, ...)
{
	va_list va;
	va_start(va, szFormat);
	s32 nStringSize = vsnprintf_s(g_szTrlVidioString, 128, 128, szFormat, va);
	va_end(va);
	
	if(nStringSize>0)
	{
		COLORREF clr;
		switch(nColor)
		{
		case TRL_FONT_WHITE:
			clr = SetTextColor(g_hTrlVideoDC, RGB(0x00, 0x00, 0x00));
			break;
		case TRL_FONT_RED:
			clr = SetTextColor(g_hTrlVideoDC, RGB(0xFF, 0x00, 0x00));
			break;
		case TRL_FONT_YELLOW:
			clr = SetTextColor(g_hTrlVideoDC, RGB(0x00, 0x00, 0xFF));
			break;
		}
		g_hTrlVideoDrawRect.bottom = g_hTrlVideoDrawRect.bottom - g_hTrlVideoDrawRect.top  + (nY*TRL_DEBUGDISP_FONTSIZE+g_sEmuShellBuffer.nHeight);
		g_hTrlVideoDrawRect.top  = (nY*TRL_DEBUGDISP_FONTSIZE+g_sEmuShellBuffer.nHeight);
		DrawText(g_hTrlVideoDC, g_szTrlVidioString, nStringSize, &g_hTrlVideoDrawRect, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOCLIP);
		SetTextColor(g_hTrlVideoDC, clr);
	}
}

/** @brief Render Frame */
void trlEmuShellVideoFrame()
{
	SetDIBitsToDevice(g_hTrlVideoDC, -8,0,g_sEmuShellBuffer.nWidth+8,g_sEmuShellBuffer.nHeight,0,0,0,g_sEmuShellBuffer.nHeight, g_sEmuShellBuffer.pScreenBuf,(BITMAPINFO*)&g_hTrlVideoBmi,DIB_RGB_COLORS);
}

/** @brief Capture Current Frame */
void trlEmuShellVideoCapture()
{
}

/** @brief Change Mask Mode */
void trlEmuShellVideoMaskChangeMode(u32 nMode)
{
	g_sTrlVideoMaskData.nMode = nMode;
	g_sTrlVideoMaskData.pDarkEnable = &g_sTrlVideoMaskData.bDarkEnable[nMode];
	g_sTrlVideoMaskData.pReduceEnable = &g_sTrlVideoMaskData.bReduceEnable[nMode];
	g_sTrlVideoMaskData.pMotionBEnable = &g_sTrlVideoMaskData.bMotionBEnable[nMode];
	g_sTrlVideoMaskData.pDark = &g_sTrlVideoMaskData.nDark[nMode];
	g_sTrlVideoMaskData.pReduceColorR = &g_sTrlVideoMaskData.nReduceColorR[nMode];
	g_sTrlVideoMaskData.pReduceColorG = &g_sTrlVideoMaskData.nReduceColorG[nMode];
	g_sTrlVideoMaskData.pReduceColorB = &g_sTrlVideoMaskData.nReduceColorB[nMode];
	g_sTrlVideoMaskData.pMotionBlur = &g_sTrlVideoMaskData.nMotionBlur[nMode];

	trlEmuShellVideoMaskMode();
	trlEmuShellVideoMotionBlur();
}

/** @brief Change Motion Blur */
void trlEmuShellVideoMotionBlur()
{
}

/** @brief Change Mask Mode */
void trlEmuShellVideoMaskMode(u32 bDark, f32 fDarkRate)
{
}

/** @brief Change Texture Filter Mode */
void trlEmuShellVideoFilterMode(u32 nMode)
{
}

/** @brief Exit */
void trlEmuShellVideoExit()
{
}

/** @brief Start */
void trlEmuShellVideoStart()
{
}

/** @brief Render Frame Menu */
void trlEmuShellVideoFrameMenu()
{
}

/** @brief Swap Buffer */
void trlEmuShellVideoSwapBuffer(const s32 display, const bool isWaitVSync)
{
}

/** @brief Frame Blend */
void trlEmuShellVideoFrameBlend()
{
}

