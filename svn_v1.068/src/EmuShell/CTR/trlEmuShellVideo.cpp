/**
 * @file trlEmuShellVideo_CTR.cpp
 * @author Chentian
 * @date 2011.08.26
 * @brief TRL Emulate For CTR - EmuShell Video Module
 */
#include "..\trlEmuShellVideo.h"
#include "..\trlEmuShellFont.h"
#include "..\trlEmuShellData.h"
#include "..\trlEmuShellPatch.h"
#include "..\trlEmuShellStruct.h"
#include "..\trlEmuShellMenu.h"
#include "EmuMenu\trlEmuMenu.h"

#include <nn/os.h>
#include <nn/fs.h>
#include <nn/fnd.h>
#include <nn/ptm.h>
#include <nn/math.h>
#include <nn/ulcd.h>

using namespace nn::os;
using namespace nn::fs;
using namespace nn::math;
using namespace nn::fnd;
using namespace nn::ulcd;

/** @name Macro Define */
//@{
#define TRL_DEBUGDISP_FONTSIZE	11
#define TRL_DISPLAY_WIDTH		NN_GX_DISPLAY0_HEIGHT
#define TRL_DISPLAY_HEIGHT		NN_GX_DISPLAY0_WIDTH
#define TRL_VIDEO_BMHEADER		54
#define TRL_DEBUG_TEX_X			64
#define TRL_DEBUG_TEX_Y			64
#define TRL_3D_FRAME			2
#define TRL_3D_OFFSET			(TRL_3D_FRAME+1)
#define TRL_SHADER_COUNT		4
#define TRL_TEXFORMAT_COUNT		14
//@}

/** @name Global Variable */
//@{
char					g_szTrlVidioString[128];
trlSEmuShellVideoMask	g_sTrlVideoMaskData;
GLuint					g_nTrlVideoShaderID;
GLuint					g_nTrlVideoProgramID[TRL_SHADER_COUNT];
GLuint					g_nTrlVideoTexIDMB;
GLuint					g_nTrlVideoTexID0[2];
GLuint					g_nTrlVideoArrayBufferID0;
GLuint					g_nTrlVideoElementArrayBuffer;
GLuint					g_nTrlVideoTexID1;
GLuint					g_nTrlVideoArrayBufferID1;
GLuint					g_nTrlVideoTexIDDebug;
GLuint					g_nTrlVideoArrayBufferIDDebug;
GLuint					g_nTrlVideoTexIDFace[3];
GLuint					g_nTrlVideoArrayBufferIDFace[4];
void*					g_pTrlVideoMotionTexBuf;
void*					g_pTrlVideoMenuTexBuf;
void*					g_pTrlVideoDebugTexBuf;
u32						g_nTrlVideoFaceTexData;
trlSEmuShellTexData*	g_pTrlVideoFaceTexData;
u16						g_nTrlVideoBitmapHeader[] = {			// 400*240
	0x4D42, 0xEE38, 0x0002, 0x0000, 0x0000, 0x0036, 0x0000, 0x0028,
	0x0000, 0x0190, 0x0000, 0x00F0, 0x0000, 0x0001, 0x0010, 0x0000,
	0x0000, 0xEE02, 0x0002, 0x0B12, 0x0000, 0x0B12, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000 };
static const GLenum		g_nTrlVideoTexFormat[TRL_TEXFORMAT_COUNT] = 
{
	GL_LUMINANCE_NATIVE_DMP,		// L4
	GL_LUMINANCE_NATIVE_DMP,		// L8
	GL_ALPHA_NATIVE_DMP,			// A4
	GL_ALPHA_NATIVE_DMP,			// A8
	GL_LUMINANCE_ALPHA_NATIVE_DMP,	// La4
	GL_LUMINANCE_ALPHA_NATIVE_DMP,	// La8
	GL_HILO8_DMP_NATIVE_DMP,		// Hilo8
	GL_RGB_NATIVE_DMP,				// Rgb565
	GL_RGB_NATIVE_DMP,				// Rgb8
	GL_RGBA_NATIVE_DMP,				// Rgb5_a1
	GL_RGBA_NATIVE_DMP,				// Rgba4
	GL_RGBA_NATIVE_DMP,				// Rgba8
	GL_SHADOW_NATIVE_DMP,			// Etc1
	GL_GAS_NATIVE_DMP,				// Etc1_a4
};
static const GLenum		g_nTrlVideoTexType[TRL_TEXFORMAT_COUNT] = 
{
	GL_UNSIGNED_4BITS_DMP,			// L4
	GL_UNSIGNED_BYTE,				// L8
	GL_UNSIGNED_4BITS_DMP,			// A4
	GL_UNSIGNED_BYTE,				// A8
	GL_UNSIGNED_BYTE_4_4_DMP,		// La4
	GL_UNSIGNED_BYTE,				// La8
	GL_UNSIGNED_BYTE,				// Hilo8
	GL_UNSIGNED_SHORT_5_6_5,		// Rgb565
	GL_UNSIGNED_BYTE,				// Rgb8
	GL_UNSIGNED_SHORT_5_5_5_1,		// Rgb5_a1
	GL_UNSIGNED_SHORT_4_4_4_4,		// Rgba4
	GL_UNSIGNED_BYTE,				// Rgba8
	GL_UNSIGNED_INT,				// Etc1
	GL_UNSIGNED_SHORT,				// Etc1_a4
};

static GLfloat			g_fTrlVideoBatteryFog[2][6][3] = 
{
	// DMG
	0.00f, 0.00f, 0.00f,
	0.05f, 0.00f, 0.00f,
	0.10f, 0.00f, 0.00f,
	0.15f, 0.00f, 0.00f,
	0.20f, 0.00f, 0.00f,
	0.30f, 0.00f, 0.00f,
	// GBC
	0.00f, 0.00f, 0.00f,
	0.20f, 0.00f, 0.00f,
	0.40f, 0.00f, 0.00f,
	0.60f, 0.00f, 0.00f,
	0.80f, 0.00f, 0.00f,
	1.00f, 0.00f, 0.00f,
};
static GLfloat			g_fTrlVideoBatteryLed[2][6][3] = 
{
	// DMG
	0.00f, 0.00f, 0.00f,
	0.10f, 0.00f, 0.00f,
	0.20f, 0.00f, 0.00f,
	0.30f, 0.00f, 0.00f,
	0.40f, 0.00f, 0.00f,
	0.60f, 0.10f, 0.00f,
	// GBC
	0.00f, 0.00f, 0.00f,
	0.00f, 0.00f, 0.00f,
	0.00f, 0.00f, 0.00f,
	0.00f, 0.00f, 0.00f,
	0.00f, 0.00f, 0.00f,
	0.00f, 0.15f, 0.00f,
};

u32						g_hTrlVideoBattery = 0x15;
u32						g_bTrlVideoBatteryThreadFlag;
Thread					g_hTrlVideoBatteryThread;

GLuint					g_nTrlVideoCmdList;
GLuint					g_nTrlVideoDispBuf0[2];
GLuint					g_nTrlVideoDispBuf0Ext[2];
GLuint					g_nTrlVideoDispBuf1[2];
s32						g_nTrlVideoCurDispBuf0;
s32						g_nTrlVideoCurDispBuf0Ext;
s32						g_nTrlVideoCurDispBuf1;

GLuint					g_nTrlVideoRenderBuf0[2];
GLuint					g_nTrlVideoRenderBuf0Ext[2];
GLuint					g_nTrlVideoRenderBuf1[2];
GLuint					g_nTrlVideoFrameBufObj[3];

StereoCamera			g_nTrlVideoStereoCamera;
u32						g_bTrlVideoStereoEnable;
Matrix44				g_sTrlVideoStereoValue;
u32						g_bTrlVideoFaceEnable;
u32						g_nTrlVideoMenuDark;
u32						g_bTrlVideoInit = 0;
//static const char		g_szTrlVideoFaceAGB[] = "rom:/face_agb.ttp";
static const char		g_szTrlVideoFaceCGB[] = "rom:/face_cgb.ttp";
//static const char		g_szTrlVideoFaceNES[] = "rom:/face_nes.ttp";
static const char		g_szTrlVideoShader[] = "rom:/shader.shbin";
static const u32		g_szTrlVideoTTPFlag = 0x46505454;				///< TTL File Header Flag - "TTPF"

extern CEmuMenu			g_hTrlEmuMenu;
extern MENU_SWITCHGBCOLOR_STATE		g_nTrlEmuMenuSwitchGBColorState;
//@}

/** @brief Battery Thread Function */
void trlEmuShellVideoBatteryThreadFunc()
{
	while(g_bTrlVideoBatteryThreadFlag)
	{
		// Update Battery
		u32 nBattery = 5;
		if(nn::ptm::CTR::GetAdapterState() == nn::ptm::CTR::ADAPTERSTATE_NOCONNECTED)
			nBattery = (u32)nn::ptm::CTR::GetBatteryLevel();
		if(g_hTrlVideoBattery != nBattery)
			g_hTrlVideoBattery = nBattery | 0x10;
		Thread::Sleep(nn::fnd::TimeSpan::FromSeconds(1));
	};
}

/** @brief Load TTP */
u32 trlEmuShellVideoLoadTTP(const char* pFilename)
{
	g_nTrlVideoFaceTexData = 0;
	g_pTrlVideoFaceTexData = NULL;

	u8* pTTPBuf = NULL;
	trlFileRead(pFilename, (void**)&pTTPBuf);
	u8* pCurBuf = pTTPBuf;

	trlSEmuShellTTPHeader* pHeader = (trlSEmuShellTTPHeader*)pCurBuf;
	pCurBuf += sizeof(trlSEmuShellTTPHeader);
	if(pHeader->nFlag != g_szTrlVideoTTPFlag)
	{
		trlMemFree(pTTPBuf);
		return 0;
	}
	g_nTrlVideoFaceTexData = pHeader->nCount;
	g_pTrlVideoFaceTexData = (trlSEmuShellTexData*)trlMemAlloc(sizeof(trlSEmuShellTexData)*g_nTrlVideoFaceTexData);

	for(u32 n=0; n<g_nTrlVideoFaceTexData; ++n)
	{
		trlSEmuShellTTPSegment* pSegment = (trlSEmuShellTTPSegment*)pCurBuf;
		pCurBuf += sizeof(trlSEmuShellTTPHeader);

		g_pTrlVideoFaceTexData[n].nFormat = pSegment->nFormatLength >> 24;
		g_pTrlVideoFaceTexData[n].nLength = pSegment->nFormatLength & 0x00FFFFFF;
		g_pTrlVideoFaceTexData[n].nWidth = pSegment->nWidth;
		g_pTrlVideoFaceTexData[n].nHeight = pSegment->nHeight;
		g_pTrlVideoFaceTexData[n].nX0 = pSegment->nOffsetX;
		g_pTrlVideoFaceTexData[n].nY0 = pSegment->nOffsetY;
		g_pTrlVideoFaceTexData[n].nX1 = pSegment->nOffsetX + pSegment->nSizeX;
		g_pTrlVideoFaceTexData[n].nY1 = pSegment->nOffsetY + pSegment->nSizeY;
		g_pTrlVideoFaceTexData[n].pData = trlMemAllocDevice(g_pTrlVideoFaceTexData[n].nLength, 128);
		trlMemCopy(g_pTrlVideoFaceTexData[n].pData, pCurBuf, g_pTrlVideoFaceTexData[n].nLength);
		pCurBuf += g_pTrlVideoFaceTexData[n].nLength;
	}

	trlMemFree(pTTPBuf);
	return 1;
}

/** @brief Init Hardware */
void trlEmuShellVideoInitHardware()
{
	nngxInitialize(trlMemAllocVram, trlMemFreeVram);
	nngxGenCmdlists(1, &g_nTrlVideoCmdList);
	nngxBindCmdlist(g_nTrlVideoCmdList);
	nngxCmdlistStorage(0x40000, 128);
	nngxSetCmdlistParameteri(NN_GX_CMDLIST_RUN_MODE, NN_GX_CMDLIST_SERIAL_RUN);

	// Create Display buffers
    nngxActiveDisplay(NN_GX_DISPLAY0);
    nngxGenDisplaybuffers(2, g_nTrlVideoDispBuf0);
    nngxBindDisplaybuffer(g_nTrlVideoDispBuf0[0]);
    nngxDisplaybufferStorage(GL_RGB5_A1, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT, NN_GX_MEM_VRAMA);
    nngxBindDisplaybuffer(g_nTrlVideoDispBuf0[1]);
    nngxDisplaybufferStorage(GL_RGB5_A1, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT, NN_GX_MEM_VRAMA);
    nngxDisplayEnv(0, 0);
    nngxBindDisplaybuffer(0);
    g_nTrlVideoCurDispBuf0 = 0;

#if TRL_STEREO
	if(g_bTrlVideoStereoEnable)
	{
		nngxActiveDisplay(NN_GX_DISPLAY0_EXT);
		nngxGenDisplaybuffers(2, g_nTrlVideoDispBuf0Ext);
		nngxBindDisplaybuffer(g_nTrlVideoDispBuf0Ext[0]);
		nngxDisplaybufferStorage(GL_RGB5_A1, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT, NN_GX_MEM_VRAMA);
		nngxBindDisplaybuffer(g_nTrlVideoDispBuf0Ext[1]);
		nngxDisplaybufferStorage(GL_RGB5_A1, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT, NN_GX_MEM_VRAMA);
		nngxDisplayEnv(0, 0);
		nngxBindDisplaybuffer(0);
		g_nTrlVideoCurDispBuf0Ext = 0;
	}
#endif

    nngxActiveDisplay(NN_GX_DISPLAY1);
    nngxGenDisplaybuffers(2, g_nTrlVideoDispBuf1);
    nngxBindDisplaybuffer(g_nTrlVideoDispBuf1[0]);
    nngxDisplaybufferStorage(GL_RGB8_OES, nn::gx::DISPLAY1_WIDTH, nn::gx::DISPLAY1_HEIGHT, NN_GX_MEM_VRAMB);
    nngxBindDisplaybuffer(g_nTrlVideoDispBuf1[1]);
    nngxDisplaybufferStorage(GL_RGB8_OES, nn::gx::DISPLAY1_WIDTH, nn::gx::DISPLAY1_HEIGHT, NN_GX_MEM_VRAMB);
    nngxDisplayEnv(0, 0);
    nngxBindDisplaybuffer(0);
    g_nTrlVideoCurDispBuf1 = 0;

	// Create Render buffer
#if TRL_STEREO
    glGenFramebuffers(3, g_nTrlVideoFrameBufObj);
#else
    glGenFramebuffers(2, g_nTrlVideoFrameBufObj);
#endif

    // DISPLAY0
    glGenRenderbuffers(2, g_nTrlVideoRenderBuf0);
    glBindRenderbuffer(GL_RENDERBUFFER, g_nTrlVideoRenderBuf0[0]);
    glRenderbufferStorage(GL_RENDERBUFFER | NN_GX_MEM_VRAMA, GL_RGB5_A1, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[0]);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, g_nTrlVideoRenderBuf0[0]);

	glBindRenderbuffer(GL_RENDERBUFFER, g_nTrlVideoRenderBuf0[1]);
    glRenderbufferStorage(GL_RENDERBUFFER | NN_GX_MEM_VRAMA, GL_DEPTH_COMPONENT16, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, g_nTrlVideoRenderBuf0[1]);

#if TRL_STEREO
	// DISPLAY0 Extent
    glGenRenderbuffers(2, g_nTrlVideoRenderBuf0Ext);
    glBindRenderbuffer(GL_RENDERBUFFER, g_nTrlVideoRenderBuf0Ext[0]);
    glRenderbufferStorage(GL_RENDERBUFFER | NN_GX_MEM_VRAMA, GL_RGB5_A1, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[2]);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, g_nTrlVideoRenderBuf0Ext[0]);

	glBindRenderbuffer(GL_RENDERBUFFER, g_nTrlVideoRenderBuf0Ext[1]);
    glRenderbufferStorage(GL_RENDERBUFFER | NN_GX_MEM_VRAMA, GL_DEPTH_COMPONENT16, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, g_nTrlVideoRenderBuf0Ext[1]);
#endif

    // DISPLAY1
    glGenRenderbuffers(2, g_nTrlVideoRenderBuf1);
    glBindRenderbuffer(GL_RENDERBUFFER, g_nTrlVideoRenderBuf1[0]);
    glRenderbufferStorage(GL_RENDERBUFFER | NN_GX_MEM_VRAMB, GL_RGBA8_OES, nn::gx::DISPLAY1_WIDTH, nn::gx::DISPLAY1_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[1]);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, g_nTrlVideoRenderBuf1[0]);

    glBindRenderbuffer(GL_RENDERBUFFER, g_nTrlVideoRenderBuf1[1]);
    glRenderbufferStorage(GL_RENDERBUFFER | NN_GX_MEM_VRAMB, GL_DEPTH_COMPONENT16, nn::gx::DISPLAY1_WIDTH, nn::gx::DISPLAY1_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, g_nTrlVideoRenderBuf1[1]);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

	nngxRunCmdlist();
}

/** @brief Init Frame */
void trlEmuShellVideoInitFrame()
{
	g_sEmuShellBuffer.nTexWidth = TRL_EMUCORE_TEX_X;
	g_sEmuShellBuffer.nTexHeight = TRL_EMUCORE_TEX_Y;

	g_sEmuShellBuffer.pTextureBuf[0] = trlMemAllocDevice(TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2, 128);
	u16* pBuffer = (u16*)g_sEmuShellBuffer.pTextureBuf[0];
	for(u32 n=0; n<TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y; ++n, ++pBuffer)
		*pBuffer = 0x0001;
	g_sEmuShellBuffer.pTextureBuf[1] = trlMemAllocDevice(TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2, 128);
	pBuffer = (u16*)g_sEmuShellBuffer.pTextureBuf[1];
	for(u32 n=0; n<TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y; ++n, ++pBuffer)
		*pBuffer = 0x0001;
	g_sEmuShellBuffer.nTexID = 0;
	g_sEmuShellBuffer.pScreenBuf = g_sEmuShellBuffer.pTextureBuf[g_sEmuShellBuffer.nTexID];
	g_pTrlVideoMotionTexBuf = trlMemAllocDevice(TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2, 128);
	pBuffer = (u16*)g_pTrlVideoMotionTexBuf;
	for(u32 n=0; n<TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y; ++n, ++pBuffer)
		*pBuffer = 0x0001;
	g_pTrlVideoMenuTexBuf = trlMemAllocDevice((TRL_EMUCORE_TEX_X/2)*TRL_EMUCORE_TEX_Y*2, 128);
	pBuffer = (u16*)g_pTrlVideoMenuTexBuf;
	for(u32 n=0; n<((TRL_EMUCORE_TEX_X/2)*TRL_EMUCORE_TEX_Y); ++n, ++pBuffer)
		*pBuffer = 0x0001;

#if TRL_DEBUGINFO
	g_pTrlVideoDebugTexBuf = trlMemAllocDevice(TRL_DEBUG_TEX_X*TRL_DEBUG_TEX_Y*2, 128);
	pBuffer = (u16*)g_pTrlVideoDebugTexBuf;
	for(u32 n=0; n<TRL_DEBUG_TEX_X*TRL_DEBUG_TEX_Y; ++n, ++pBuffer)
		*pBuffer = 0x0001;
#endif
}

/** @brief Swap Buffer */
void trlEmuShellVideoSwapBuffer(const s32 display, const bool isWaitVSync)
{
#if TRL_DEMO
    if (display == NN_GX_DISPLAY0 || display == NN_GX_DISPLAY_BOTH)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[0]);
        nngxTransferRenderImage(g_nTrlVideoDispBuf0[g_nTrlVideoCurDispBuf0], NN_GX_ANTIALIASE_NOT_USED, GL_FALSE, 0, 0);
    }
#endif

    if (display == NN_GX_DISPLAY1 || display == NN_GX_DISPLAY_BOTH)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[1]);
        nngxTransferRenderImage(g_nTrlVideoDispBuf1[g_nTrlVideoCurDispBuf1], NN_GX_ANTIALIASE_NOT_USED, GL_FALSE, 0, 0);
    }

    if (display == NN_GX_DISPLAY0 || display == NN_GX_DISPLAY_BOTH)
    {
        nngxActiveDisplay(NN_GX_DISPLAY0);
        nngxBindDisplaybuffer(g_nTrlVideoDispBuf0[g_nTrlVideoCurDispBuf0]);
        g_nTrlVideoCurDispBuf0 = !g_nTrlVideoCurDispBuf0;

#if TRL_STEREO
		if(g_bTrlVideoStereoEnable)
		{
			nngxActiveDisplay(NN_GX_DISPLAY0_EXT);
			nngxBindDisplaybuffer(g_nTrlVideoDispBuf0Ext[g_nTrlVideoCurDispBuf0Ext]);
			g_nTrlVideoCurDispBuf0Ext = !g_nTrlVideoCurDispBuf0Ext;
		}
#endif
    }
    if (display == NN_GX_DISPLAY1 || display == NN_GX_DISPLAY_BOTH)
    {
        nngxActiveDisplay(NN_GX_DISPLAY1);
        nngxBindDisplaybuffer(g_nTrlVideoDispBuf1[g_nTrlVideoCurDispBuf1]);
        g_nTrlVideoCurDispBuf1 = !g_nTrlVideoCurDispBuf1;
    }

    nngxSplitDrawCmdlist();
    nngxRunCmdlist();
    nngxWaitCmdlistDone();

    nngxSwapBuffers(display);
    if (isWaitVSync)
		nngxWaitVSync(display);
    nngxClearCmdlist();
}

/** @brief Init Display0 */
void trlEmuShellVideoInitDisplay0()
{
	u32 nWidth = 400;
	u32 nHeight = 240;
	u32 nTexOffsetS = 8;
	u32 nTexOffsetT = 0;
	g_sEmuShellBuffer.nScreenBufOffset = 0;
	switch(g_sEmuShellBuffer.nRomType)
	{
	case TRL_EMUCORE_ROMTYPE_AGB:
		nWidth = trlEmuShellDataGetConfigData("AGB", "Width", 360);
		nHeight = trlEmuShellDataGetConfigData("AGB", "Height", 240);
		break;
	case TRL_EMUCORE_ROMTYPE_CGB:
		if(g_bTrlVideoFaceEnable)
		{
			nWidth = 160;
			nHeight = 144;
			if(g_bTrlVideoStereoEnable)
			{
				nTexOffsetS = TRL_3D_OFFSET*2;
				nTexOffsetT = TRL_3D_FRAME*2;
				nWidth += nTexOffsetS;
				nHeight += nTexOffsetT;
				glScissor(46, 118, 148, 164);
				g_sEmuShellBuffer.nScreenBufOffset = TRL_EMUCORE_TEX_X*TRL_3D_FRAME + TRL_3D_OFFSET;
				g_sEmuShellBuffer.pScreenBuf = (u16*)g_sEmuShellBuffer.pTextureBuf[g_sEmuShellBuffer.nTexID] + g_sEmuShellBuffer.nScreenBufOffset;
			}
		}
		else
		{
			nWidth = trlEmuShellDataGetConfigData("CGB", "Width", 267);
			nHeight = trlEmuShellDataGetConfigData("CGB", "Height", 240);
		}
		break;
	case TRL_EMUCORE_ROMTYPE_NES:
		nWidth = trlEmuShellDataGetConfigData("NES", "Width", 256);
		nHeight = trlEmuShellDataGetConfigData("NES", "Height", 240);
		break;
	}

	f32 fWidth0, fWidth1,fHeight0, fHeight1, fDepth = 0.0f;
	if(nWidth&1)
	{
		fWidth0 = (nWidth/2)/(TRL_DISPLAY_WIDTH/2.0f);
		fWidth1 = (nWidth/2+1)/(TRL_DISPLAY_WIDTH/2.0f);
	}
	else
		fWidth0 = fWidth1 = nWidth * 1.0f/TRL_DISPLAY_WIDTH;
	if(nHeight&1)
	{
		fHeight0 = (nHeight/2)/(TRL_DISPLAY_HEIGHT/2.0f);
		fHeight1 = (nHeight/2+1)/(TRL_DISPLAY_HEIGHT/2.0f);
	}
	else
		fHeight0 = fHeight1 = nHeight * 1.0f/TRL_DISPLAY_HEIGHT;

#if TRL_STEREO
	if(g_bTrlVideoStereoEnable)
		fDepth = -0.5f;
#endif

	GLfloat nCoords[] = {
		 fHeight0, fWidth0, fDepth,
		-fHeight1, fWidth0, fDepth,
		 fHeight0, -fWidth1, fDepth,
		-fHeight1, -fWidth1, fDepth,
	};

	f32 fTexS0= nTexOffsetS*1.0f/g_sEmuShellBuffer.nTexWidth;
	//f32 fTexT0= 1.0f-(8*1.0f/272);

//NN_LOG("%d %d %d %d\n", g_sEmuShellBuffer.nWidth,g_sEmuShellBuffer.nHeight, g_sEmuShellBuffer.nTexWidth, g_sEmuShellBuffer.nTexHeight);

	f32 fTexS = (g_sEmuShellBuffer.nWidth+nTexOffsetS) * 1.0f / g_sEmuShellBuffer.nTexWidth;
	f32 fTexT = 1.0f - (g_sEmuShellBuffer.nHeight+nTexOffsetT) * 1.0f / g_sEmuShellBuffer.nTexHeight;
	/*
	GLfloat nTexCoords[] = {
		0.f, 1.f,
		0.f, fTexT,
		fTexS, 1.f,
		fTexS, fTexT,
	};
	*/
	GLfloat nTexCoords[] = {
		fTexS0, 1.0f,
		fTexS0, fTexT,
		fTexS, 1.0f,
		fTexS, fTexT,
	};
	GLushort nIdxs[] = { 3, 2, 1, 0	};

	glGenBuffers(1, &g_nTrlVideoArrayBufferID0);
	glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferID0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nCoords) + sizeof(nTexCoords), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(nCoords), nCoords);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(nCoords), sizeof(nTexCoords), nTexCoords);

	glGenBuffers(1, &g_nTrlVideoElementArrayBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_nTrlVideoElementArrayBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(nIdxs), nIdxs, GL_STATIC_DRAW);

	glGenTextures(2, g_nTrlVideoTexID0);
	glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexID0[0]);
	glTexImage2D(GL_TEXTURE_2D | NN_GX_MEM_VRAMA | GL_NO_COPY_FCRAM_DMP, 0, GL_RGBA_NATIVE_DMP, g_sEmuShellBuffer.nTexWidth, g_sEmuShellBuffer.nTexHeight, 0, GL_RGBA_NATIVE_DMP, GL_UNSIGNED_SHORT_5_5_5_1, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexID0[1]);
	glTexImage2D(GL_TEXTURE_2D | NN_GX_MEM_VRAMA | GL_NO_COPY_FCRAM_DMP, 0, GL_RGBA_NATIVE_DMP, g_sEmuShellBuffer.nTexWidth, g_sEmuShellBuffer.nTexHeight, 0, GL_RGBA_NATIVE_DMP, GL_UNSIGNED_SHORT_5_5_5_1, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &g_nTrlVideoTexIDMB);
	glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexIDMB);
	glTexImage2D(GL_TEXTURE_2D | NN_GX_MEM_FCRAM | GL_NO_COPY_FCRAM_DMP, 0, GL_RGBA_NATIVE_DMP, g_sEmuShellBuffer.nTexWidth, g_sEmuShellBuffer.nTexHeight, 0, GL_RGBA_NATIVE_DMP, GL_UNSIGNED_SHORT_5_5_5_1, g_pTrlVideoMotionTexBuf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

/** @brief Init Display1 */
void trlEmuShellVideoInitDisplay1()
{
	GLfloat nCoords[] = {
		 1.f, 1.f, 0.f,
		-1.f, 1.f, 0.f,
		 1.f, -1.f, 0.f,
		-1.f, -1.f, 0.f,
	};
	GLfloat nTexCoords[] = {
		0.f, 1.f,
		0.f, 0.25f,
		1.0f, 1.f,
		1.0f, 0.25f,
	};

	glGenBuffers(1, &g_nTrlVideoArrayBufferID1);
	glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferID1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nCoords) + sizeof(nTexCoords), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(nCoords), nCoords);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(nCoords), sizeof(nTexCoords), nTexCoords);

	glGenTextures(1, &g_nTrlVideoTexID1);
	glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexID1);
	glTexImage2D(GL_TEXTURE_2D | NN_GX_MEM_FCRAM | GL_NO_COPY_FCRAM_DMP, 0, GL_RGBA_NATIVE_DMP, TRL_EMUCORE_TEX_X/2, TRL_EMUCORE_TEX_Y, 0, GL_RGBA_NATIVE_DMP, GL_UNSIGNED_SHORT_5_5_5_1, g_pTrlVideoMenuTexBuf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
}

/** @brief Init Debug */
void trlEmuShellVideoInitDebug()
{
	GLfloat nCoords[] = {
		1.f, -0.68f, 0.f,
		0.467f, -0.68f, 0.f,
		1.f, -1.f, 0.f,
		0.467f, -1.f, 0.f,
	};
	GLfloat nTexCoords[] = { 0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0.f };

	if(g_sEmuShellBuffer.nRomType == TRL_EMUCORE_ROMTYPE_NES)
	{
		nCoords[1] = nCoords[4] = -0.71f;
		nCoords[7] = nCoords[10] = -1.03f;
	}

	glGenBuffers(1, &g_nTrlVideoArrayBufferIDDebug);
	glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferIDDebug);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nCoords) + sizeof(nTexCoords), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(nCoords), nCoords);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(nCoords), sizeof(nTexCoords), nTexCoords);


#if TRL_DEBUGINFO
	glGenTextures(1, &g_nTrlVideoTexIDDebug);
	glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexIDDebug);
	glTexImage2D(GL_TEXTURE_2D | NN_GX_MEM_FCRAM | GL_NO_COPY_FCRAM_DMP, 0, GL_RGBA_NATIVE_DMP, TRL_DEBUG_TEX_X, TRL_DEBUG_TEX_Y, 0, GL_RGBA_NATIVE_DMP, GL_UNSIGNED_SHORT_5_5_5_1, g_pTrlVideoDebugTexBuf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
#endif
}

/** @brief Init Face */
void trlEmuShellVideoInitFace()
{
	if(g_bTrlVideoFaceEnable)
	{
		switch(g_sEmuShellBuffer.nRomType)
		{
		case TRL_EMUCORE_ROMTYPE_AGB:
			{
			}
			break;
		case TRL_EMUCORE_ROMTYPE_CGB:
			{
				if(!trlEmuShellVideoLoadTTP(g_szTrlVideoFaceCGB))
					return;

				GLfloat fX = g_pTrlVideoFaceTexData[0].nWidth * 1.0f / TRL_DISPLAY_WIDTH;
				GLfloat fY = g_pTrlVideoFaceTexData[0].nHeight * 1.0f / TRL_DISPLAY_HEIGHT;
				GLfloat nCoordsFace[] = { fY, fX, 0.f, -fY, fX, 0.f, fY, -fX, 0.f, -fY, -fX, 0.f };
				GLfloat nTexCoords[] = { 0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0.f };

				s32 nCenterX = g_pTrlVideoFaceTexData[0].nWidth / 2;
				s32 nCenterY = g_pTrlVideoFaceTexData[0].nHeight / 2;
				fX = (nCenterX - g_pTrlVideoFaceTexData[1].nX0) * 1.0f / (TRL_DISPLAY_WIDTH>>1);
				fY = (nCenterY - g_pTrlVideoFaceTexData[1].nY0) * 1.0f / (TRL_DISPLAY_HEIGHT>>1);
				GLfloat fX1 = (nCenterX - g_pTrlVideoFaceTexData[1].nX1) * 1.0f / (TRL_DISPLAY_WIDTH>>1);
				GLfloat fY1 = (nCenterY - g_pTrlVideoFaceTexData[1].nY1) * 1.0f / (TRL_DISPLAY_HEIGHT>>1);
				GLfloat fZ = -0.3f;
				GLfloat nCoordsLight[] = { fY, fX, fZ, fY1, fX, fZ, fY, fX1, fZ, fY1, fX1, fZ };

				fX = (nCenterX - g_pTrlVideoFaceTexData[2].nX0) * 1.0f / (TRL_DISPLAY_WIDTH>>1);
				fY = (nCenterY - g_pTrlVideoFaceTexData[2].nY0) * 1.0f / (TRL_DISPLAY_HEIGHT>>1);
				fX1 = (nCenterX - g_pTrlVideoFaceTexData[2].nX1) * 1.0f / (TRL_DISPLAY_WIDTH>>1);
				fY1 = (nCenterY - g_pTrlVideoFaceTexData[2].nY1) * 1.0f / (TRL_DISPLAY_HEIGHT>>1);
				GLfloat nCoordsFog[] = { fY, fX, 0.f, fY1, fX, 0.f, fY, fX1, 0.f, fY1, fX1, 0.f };

				g_pTrlVideoFaceTexData[2].nX0 -= 4;
				g_pTrlVideoFaceTexData[2].nY0 -= 4;
				g_pTrlVideoFaceTexData[2].nX1 += 4;
				g_pTrlVideoFaceTexData[2].nY1 += 4;
				fX = (nCenterX - g_pTrlVideoFaceTexData[2].nX0) * 1.0f / (TRL_DISPLAY_WIDTH>>1);
				fY = (nCenterY - g_pTrlVideoFaceTexData[2].nY0) * 1.0f / (TRL_DISPLAY_HEIGHT>>1);
				fX1 = (nCenterX - g_pTrlVideoFaceTexData[2].nX1) * 1.0f / (TRL_DISPLAY_WIDTH>>1);
				fY1 = (nCenterY - g_pTrlVideoFaceTexData[2].nY1) * 1.0f / (TRL_DISPLAY_HEIGHT>>1);
				GLfloat nCoordsPart[] = { fY, fX, 0.f, fY1, fX, 0.f, fY, fX1, 0.f, fY1, fX1, 0.f };

				fX = g_pTrlVideoFaceTexData[2].nX0 * 1.0f / g_pTrlVideoFaceTexData[0].nWidth;
				fY = (g_pTrlVideoFaceTexData[0].nHeight - g_pTrlVideoFaceTexData[2].nY0) * 1.0f / g_pTrlVideoFaceTexData[0].nHeight;
				fX1 = g_pTrlVideoFaceTexData[2].nX1 * 1.0f / g_pTrlVideoFaceTexData[0].nWidth;
				fY1 = (g_pTrlVideoFaceTexData[0].nHeight - g_pTrlVideoFaceTexData[2].nY1) * 1.0f / g_pTrlVideoFaceTexData[0].nHeight;
				GLfloat nTexCoordsPart[] = { fX, fY, fX, fY1, fX1, fY, fX1, fY1 };

				glGenBuffers(4, g_nTrlVideoArrayBufferIDFace);
				glGenTextures(3, g_nTrlVideoTexIDFace);

				// Face
				glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferIDFace[0]);
				glBufferData(GL_ARRAY_BUFFER, 20*sizeof(GLfloat), 0, GL_STATIC_DRAW);
				glBufferSubData(GL_ARRAY_BUFFER, 0, 12*sizeof(GLfloat), nCoordsFace);
				glBufferSubData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), 8*sizeof(GLfloat), nTexCoords);

				glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexIDFace[0]);
				glTexImage2D(GL_TEXTURE_2D | NN_GX_MEM_FCRAM | GL_NO_COPY_FCRAM_DMP, 0, g_nTrlVideoTexFormat[g_pTrlVideoFaceTexData[0].nFormat], g_pTrlVideoFaceTexData[0].nWidth, g_pTrlVideoFaceTexData[0].nHeight, 0, g_nTrlVideoTexFormat[g_pTrlVideoFaceTexData[0].nFormat], g_nTrlVideoTexType[g_pTrlVideoFaceTexData[0].nFormat], g_pTrlVideoFaceTexData[0].pData);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				// Light
				glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferIDFace[1]);
				glBufferData(GL_ARRAY_BUFFER, 20*sizeof(GLfloat), 0, GL_STATIC_DRAW);
				glBufferSubData(GL_ARRAY_BUFFER, 0, 12*sizeof(GLfloat), nCoordsLight);
				glBufferSubData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), 8*sizeof(GLfloat), nTexCoords);

				glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexIDFace[1]);
				glTexImage2D(GL_TEXTURE_2D | NN_GX_MEM_FCRAM | GL_NO_COPY_FCRAM_DMP, 0, g_nTrlVideoTexFormat[g_pTrlVideoFaceTexData[1].nFormat], g_pTrlVideoFaceTexData[1].nWidth, g_pTrlVideoFaceTexData[1].nHeight, 0, g_nTrlVideoTexFormat[g_pTrlVideoFaceTexData[1].nFormat], g_nTrlVideoTexType[g_pTrlVideoFaceTexData[1].nFormat], g_pTrlVideoFaceTexData[1].pData);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				// Part
				glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferIDFace[2]);
				glBufferData(GL_ARRAY_BUFFER, 20*sizeof(GLfloat), 0, GL_STATIC_DRAW);
				glBufferSubData(GL_ARRAY_BUFFER, 0, 12*sizeof(GLfloat), nCoordsPart);
				glBufferSubData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), 8*sizeof(GLfloat), nTexCoordsPart);

				// Fog
				glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferIDFace[3]);
				glBufferData(GL_ARRAY_BUFFER, 20*sizeof(GLfloat), 0, GL_STATIC_DRAW);
				glBufferSubData(GL_ARRAY_BUFFER, 0, 12*sizeof(GLfloat), nCoordsFog);
				glBufferSubData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), 8*sizeof(GLfloat), nTexCoords);

				glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexIDFace[2]);
				glTexImage2D(GL_TEXTURE_2D | NN_GX_MEM_FCRAM | GL_NO_COPY_FCRAM_DMP, 0, g_nTrlVideoTexFormat[g_pTrlVideoFaceTexData[2].nFormat], g_pTrlVideoFaceTexData[2].nWidth, g_pTrlVideoFaceTexData[2].nHeight, 0, g_nTrlVideoTexFormat[g_pTrlVideoFaceTexData[2].nFormat], g_nTrlVideoTexType[g_pTrlVideoFaceTexData[2].nFormat], g_pTrlVideoFaceTexData[2].pData);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		 
				glBindTexture(GL_TEXTURE_2D, 0);

				GLfloat* pColor = g_fTrlVideoBatteryLed[g_sEmuShellBuffer.nRomSubType-1][g_hTrlVideoBattery];
				glUseProgram(g_nTrlVideoProgramID[2]);
				glUniform4f(glGetUniformLocation(g_nTrlVideoProgramID[2], "dmp_TexEnv[0].constRgba"), pColor[0], pColor[1], pColor[2], 1.0f);
				glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[2], "dmp_TexEnv[0].srcRgb"), GL_CONSTANT, GL_TEXTURE0, GL_CONSTANT);
				glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[2], "dmp_TexEnv[0].srcAlpha"), GL_PRIMARY_COLOR, GL_TEXTURE0, GL_CONSTANT);
				glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[2], "dmp_TexEnv[0].operandRgb"), GL_SRC_COLOR, GL_SRC_COLOR, GL_SRC_COLOR);
				glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[2], "dmp_TexEnv[0].operandAlpha"), GL_SRC_ALPHA, GL_SRC_ALPHA, GL_SRC_ALPHA);
				glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[2], "dmp_TexEnv[0].combineRgb"), GL_ADD);
				glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[2], "dmp_TexEnv[0].combineAlpha"), GL_MODULATE);

				pColor = g_fTrlVideoBatteryFog[g_sEmuShellBuffer.nRomSubType-1][g_hTrlVideoBattery];
				glUseProgram(g_nTrlVideoProgramID[3]);
				glUniform4f(glGetUniformLocation(g_nTrlVideoProgramID[3], "dmp_TexEnv[0].constRgba"), pColor[0], pColor[1], pColor[2], 1.0f);
				glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[3], "dmp_TexEnv[0].srcRgb"), GL_CONSTANT, GL_TEXTURE0, GL_CONSTANT);
				glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[3], "dmp_TexEnv[0].srcAlpha"), GL_TEXTURE0, GL_TEXTURE0, GL_CONSTANT);
				glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[3], "dmp_TexEnv[0].operandRgb"), GL_SRC_COLOR, GL_SRC_COLOR, GL_SRC_COLOR);
				glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[3], "dmp_TexEnv[0].operandAlpha"), GL_SRC_ALPHA, GL_SRC_ALPHA, GL_SRC_ALPHA);
				glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[3], "dmp_TexEnv[0].combineRgb"), GL_MODULATE);
				glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[3], "dmp_TexEnv[0].combineAlpha"), GL_REPLACE);
			}
			break;
		case TRL_EMUCORE_ROMTYPE_NES:
			{
			}
			break;
		}
	}

#if TRL_STEREO
	if(g_bTrlVideoStereoEnable)
	{
		g_nTrlVideoStereoCamera.Initialize();
		g_nTrlVideoStereoCamera.SetBaseFrustum( -0.04f, 0.04f, -0.04f, 0.04f, 0.2f, 30.f);
		nn::math::Matrix34 view;
		nn::math::Vector3 camPos(0.f, 0.f, 4.5f);
		nn::math::Vector3 camUp(1.f, 0.f, 0.f);
		nn::math::Vector3 target(0.f, 0.f, 0.f);
		nn::math::MTX34LookAt(&view, &camPos, &camUp, &target);
		g_nTrlVideoStereoCamera.SetBaseCamera(&view);
		switch(g_sEmuShellBuffer.nRomType)
		{
		case TRL_EMUCORE_ROMTYPE_AGB:
			break;
		case TRL_EMUCORE_ROMTYPE_CGB:
			g_nTrlVideoStereoCamera.SetLimitParallax(trlEmuShellDataGetConfigData("CGB", "Parallax", 300)/1000.0f);
			break;
		case TRL_EMUCORE_ROMTYPE_NES:
			break;
		}
		nngxSetDisplayMode(NN_GX_DISPLAYMODE_STEREO);
	}
#endif
}

/** @brief Init Shader */
void trlEmuShellVideoInitShader()
{
	void* pBuf = NULL;
	s32 nSize = trlFileRead(g_szTrlVideoShader, &pBuf);
	GLfloat m[16] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	g_nTrlVideoShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderBinary(1, &g_nTrlVideoShaderID, GL_PLATFORM_BINARY_DMP, pBuf, nSize);

	for(u32 n=0; n<TRL_SHADER_COUNT; ++n)
	{
		g_nTrlVideoProgramID[n] = glCreateProgram();

		glAttachShader(g_nTrlVideoProgramID[n], g_nTrlVideoShaderID);
		glAttachShader(g_nTrlVideoProgramID[n], GL_DMP_FRAGMENT_SHADER_DMP);

		glBindAttribLocation(g_nTrlVideoProgramID[n], 0, "aPosition");
		glBindAttribLocation(g_nTrlVideoProgramID[n], 1, "aTexCoord");

		glLinkProgram(g_nTrlVideoProgramID[n]);
		glValidateProgram(g_nTrlVideoProgramID[n]);
		glUseProgram(g_nTrlVideoProgramID[n]);

		glUniformMatrix4fv(glGetUniformLocation(g_nTrlVideoProgramID[n], "uProjection"), 1, GL_FALSE, m);
		glUniformMatrix4fv(glGetUniformLocation(g_nTrlVideoProgramID[n], "uModelView"), 1, GL_FALSE, m);
		glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[n], "dmp_Texture[0].samplerType"), GL_TEXTURE_2D);
		glUniform1f(glGetUniformLocation(g_nTrlVideoProgramID[n], "dmp_TexEnv[0].scaleRgb"), 1.0f);
		glUniform1f(glGetUniformLocation(g_nTrlVideoProgramID[n], "dmp_TexEnv[0].scaleAlpha"), 1.0f);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[n], "dmp_TexEnv[0].srcRgb"), GL_TEXTURE0, GL_TEXTURE0, GL_TEXTURE0);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[n], "dmp_TexEnv[0].srcAlpha"), GL_TEXTURE0, GL_TEXTURE0, GL_TEXTURE0);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[n], "dmp_TexEnv[0].operandRgb"), GL_SRC_COLOR, GL_SRC_COLOR, GL_SRC_COLOR);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[n], "dmp_TexEnv[0].operandAlpha"), GL_SRC_ALPHA, GL_SRC_ALPHA, GL_SRC_ALPHA);
		glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[n], "dmp_TexEnv[0].combineRgb"), GL_REPLACE);
		glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[n], "dmp_TexEnv[0].combineAlpha"), GL_REPLACE);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}
	trlMemFree(pBuf);
}

/** @brief Clear */
void trlEmuShellVideoClear()
{
	memset(g_pTrlVideoMenuTexBuf, 0, (TRL_EMUCORE_TEX_X/2)*TRL_EMUCORE_TEX_Y*2);
}

/** @brief Render Screen */
void trlEmuShellVideoScreen(u32 nMask)
{
	glUseProgram(g_nTrlVideoProgramID[0]);
    glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferID0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_nTrlVideoElementArrayBuffer);
    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12*sizeof(GLfloat)));

	switch(*g_sTrlVideoMaskData.pMotionBEnable & nMask)
	{
	case 0:	// Normal
		//glDisable(GL_BLEND);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexID0[g_sEmuShellBuffer.nTexID]);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
		break;
	case 1:	// Black Fade
		if(g_sEmuShellBuffer.nRomSubType == TRL_EMUCORE_GBTYPE_DMG)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexIDMB);
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
			glBlendEquation(GL_FUNC_ADD);
			glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexID0[g_sEmuShellBuffer.nTexID]);
			glBlendFunc(GL_ONE, GL_ONE);
			glBlendEquation(GL_MIN);
			glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

			glBlendEquation(GL_FUNC_ADD);
			glDisable(GL_BLEND);
		}
		break;
	case 2:	// White Fade
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexID0[g_sEmuShellBuffer.nTexID]);
			glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

			if(g_sEmuShellBuffer.nMotion2Frames >= 2)
			{
				glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexID0[1 - g_sEmuShellBuffer.nTexID]);
				glEnable(GL_BLEND);
				f32 fColor = *g_sTrlVideoMaskData.pMotionBlur / 32.0f;
				glBlendColor(fColor, fColor, fColor, fColor);
				glBlendFunc(GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR);
				glBlendEquation(GL_FUNC_ADD);
				glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
				glDisable(GL_BLEND);
			}
		break;
	case 3:	// Frame Blend
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexID0[g_sEmuShellBuffer.nTexID]);
			glEnable(GL_BLEND);
			f32 fColor = *g_sTrlVideoMaskData.pMotionBlur / 31.0f;
			glBlendColor(fColor, fColor, fColor, fColor);
			glBlendFunc(GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR);
			glBlendEquation(GL_FUNC_ADD);
			glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
			glDisable(GL_BLEND);
		}
		break;
	}
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
}

/** @brief Render Face */
void trlEmuShellVideoFace()
{
	glUseProgram(g_nTrlVideoProgramID[1]);
	glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferIDFace[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_nTrlVideoElementArrayBuffer);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12*sizeof(GLfloat)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexIDFace[0]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	glDisable(GL_BLEND);
}

/** @brief Render LED */
void trlEmuShellVideoLED()
{
	g_hTrlVideoBattery &= 0x0F;
	// Light
	GLfloat* pColor = g_fTrlVideoBatteryLed[g_sEmuShellBuffer.nRomSubType-1][g_hTrlVideoBattery];
	glUseProgram(g_nTrlVideoProgramID[2]);
	glUniform4f(glGetUniformLocation(g_nTrlVideoProgramID[2], "dmp_TexEnv[0].constRgba"), pColor[0], pColor[1], pColor[2], 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferIDFace[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_nTrlVideoElementArrayBuffer);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12*sizeof(GLfloat)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexIDFace[1]);
	glDisable(GL_BLEND);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

	// Part
	glUseProgram(g_nTrlVideoProgramID[1]);
	glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferIDFace[2]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_nTrlVideoElementArrayBuffer);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12*sizeof(GLfloat)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexIDFace[0]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

	// Fog
	pColor = g_fTrlVideoBatteryFog[g_sEmuShellBuffer.nRomSubType-1][g_hTrlVideoBattery];
	glUseProgram(g_nTrlVideoProgramID[3]);
	glUniform4f(glGetUniformLocation(g_nTrlVideoProgramID[3], "dmp_TexEnv[0].constRgba"), pColor[0], pColor[1], pColor[2], 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferIDFace[3]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_nTrlVideoElementArrayBuffer);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12*sizeof(GLfloat)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexIDFace[2]);
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE, GL_ONE, GL_ONE);//GL_ZERO);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	glDisable(GL_BLEND);
}

/** @brief Render Debug */
void trlEmuShellVideoDebug()
{
#if TRL_DEBUGINFO
	glUseProgram(g_nTrlVideoProgramID[1]);
	glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferIDDebug);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_nTrlVideoElementArrayBuffer);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12*sizeof(GLfloat)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexIDDebug);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
#endif
}

/** @brief Render Frame */
void trlEmuShellVideoFrame()
{	
	nngxUpdateBuffer(g_sEmuShellBuffer.pTextureBuf[g_sEmuShellBuffer.nTexID], TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2);	
	nngxTransferLinearImage(g_sEmuShellBuffer.pTextureBuf[g_sEmuShellBuffer.nTexID], g_nTrlVideoTexID0[g_sEmuShellBuffer.nTexID], GL_TEXTURE_2D);

	u32 nMask = 0xFFFFFFFF;
	if(g_sEmuShellBuffer.nVCMState)
	{
		if(g_sEmuShellBuffer.nVCMState == 2)
			g_sEmuShellBuffer.nVCMState = 0;
		nMask = 0;
	}

#if TRL_STEREO
	if(g_bTrlVideoStereoEnable)
	{
		Matrix44 projL, projR;
		Matrix44 viewL, viewR;
		g_nTrlVideoStereoCamera.CalculateMatrices(&projL, (Matrix34*)&viewL, &projR, (Matrix34*)&viewR, 1.0f, 1.0f, PIVOT_UPSIDE_TO_TOP);
        viewL._30 = viewL._31 = viewL._32 = 0.f; viewL._33 = 1.f;
        viewR._30 = viewR._31 = viewR._32 = 0.f; viewR._33 = 1.f;

		u32 nStereoChange = g_hTrlVideoBattery & 0x10;
		if(g_sTrlVideoStereoValue != projL)
		{
			g_sTrlVideoStereoValue = projL;
			nStereoChange = 1;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[0]);
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
		g_hTrlEmuMenu.ClearWarningDL();
#endif
		glViewport(0, 0, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT);
		glDisable(GL_COLOR_LOGIC_OP);
#if TRL_SWITCHICON
		if(g_nTrlEmuMenuSwitchGBColorState != MENU_SWITCHGBCOLOR_CLOSED)
		{
			g_hTrlEmuMenu.UpdateSwitchIcon0();
			g_hTrlEmuMenu.DrawSwitchIcon();
		}		
#endif
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
		g_hTrlEmuMenu.UpdateWarningDL();
		g_hTrlEmuMenu.DrawWarningDL();
#endif
#if TRL_HOMENIX_UPSCREEN
		g_hTrlEmuMenu.DrawHomeNix();
#endif

		glUseProgram(g_nTrlVideoProgramID[0]);
		glUniformMatrix4fv(glGetUniformLocation(g_nTrlVideoProgramID[0], "uProjection"), 1, GL_TRUE, static_cast<f32*>(projL));
		glUniformMatrix4fv(glGetUniformLocation(g_nTrlVideoProgramID[0], "uModelView"), 1, GL_TRUE, (f32*)(viewL));
		glEnable(GL_SCISSOR_TEST);
		trlEmuShellVideoScreen(nMask);
		glDisable(GL_SCISSOR_TEST);

        nngxUpdateState(NN_GX_STATE_ALL);
        nngxValidateState(NN_GX_STATE_ALL,GL_TRUE);

		if(!g_bTrlVideoInit)
			trlEmuShellVideoFace();

		if(nStereoChange)
		{
			glUseProgram(g_nTrlVideoProgramID[2]);
			glUniformMatrix4fv(glGetUniformLocation(g_nTrlVideoProgramID[2], "uProjection"), 1, GL_TRUE, static_cast<f32*>(projL));
			glUniformMatrix4fv(glGetUniformLocation(g_nTrlVideoProgramID[2], "uModelView"), 1, GL_TRUE, (f32*)(viewL));
			trlEmuShellVideoLED();
		}
		trlEmuShellVideoDebug();
		nngxTransferRenderImage(g_nTrlVideoDispBuf0[g_nTrlVideoCurDispBuf0], NN_GX_ANTIALIASE_NOT_USED, GL_FALSE, 0, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[2]);
		glViewport(0, 0, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT);
		glDisable(GL_COLOR_LOGIC_OP);
#if TRL_SWITCHICON
		if(g_nTrlEmuMenuSwitchGBColorState != MENU_SWITCHGBCOLOR_CLOSED)
			g_hTrlEmuMenu.DrawSwitchIcon();
#endif
#if TRL_HOMENIX_UPSCREEN
		g_hTrlEmuMenu.DrawHomeNix();
#endif
		glUseProgram(g_nTrlVideoProgramID[0]);
		glUniformMatrix4fv(glGetUniformLocation(g_nTrlVideoProgramID[0], "uProjection"), 1, GL_TRUE, static_cast<f32*>(projR));
		glUniformMatrix4fv(glGetUniformLocation(g_nTrlVideoProgramID[0], "uModelView"), 1, GL_TRUE, (f32*)(viewR));
		glEnable(GL_SCISSOR_TEST);
		trlEmuShellVideoScreen(nMask);
		glDisable(GL_SCISSOR_TEST);

        nngxUpdateState(NN_GX_STATE_ALL);
        nngxValidateState(NN_GX_STATE_ALL,GL_TRUE);

		if(!g_bTrlVideoInit)
		{
			g_bTrlVideoInit = 1;
			trlEmuShellVideoFace();
		}

		if(nStereoChange)
		{
			glUseProgram(g_nTrlVideoProgramID[2]);
			glUniformMatrix4fv(glGetUniformLocation(g_nTrlVideoProgramID[2], "uProjection"), 1, GL_TRUE, static_cast<f32*>(projR));
			glUniformMatrix4fv(glGetUniformLocation(g_nTrlVideoProgramID[2], "uModelView"), 1, GL_TRUE, (f32*)(viewR));
			trlEmuShellVideoLED();
		}
		trlEmuShellVideoDebug();
		nngxTransferRenderImage(g_nTrlVideoDispBuf0Ext[g_nTrlVideoCurDispBuf0Ext], NN_GX_ANTIALIASE_NOT_USED, GL_FALSE, 0, 0);
	}
	else
#endif
	{
		glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[0]);	
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
		g_hTrlEmuMenu.ClearWarningDL();
#endif
		glViewport(0, 0, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT);		
		glDisable(GL_COLOR_LOGIC_OP);
		trlEmuShellVideoScreen(nMask);
#if TRL_SWITCHICON
		if(g_nTrlEmuMenuSwitchGBColorState != MENU_SWITCHGBCOLOR_CLOSED)
		{
			g_hTrlEmuMenu.UpdateSwitchIcon0();
			g_hTrlEmuMenu.DrawSwitchIcon();
		}
#endif
#if TRL_NETTYPE != TRL_EMUCORE_NETTYPE_NONE
		g_hTrlEmuMenu.UpdateWarningDL();
		g_hTrlEmuMenu.DrawWarningDL();
#endif
#if TRL_HOMENIX_UPSCREEN
		g_hTrlEmuMenu.DrawHomeNix();
#endif
#if TRL_DEBUGINFO
		trlEmuShellVideoDebug();
#endif
		nngxTransferRenderImage(g_nTrlVideoDispBuf0[g_nTrlVideoCurDispBuf0], NN_GX_ANTIALIASE_NOT_USED, GL_FALSE, 0, 0);
	}
}

/** @brief Render Frame Menu */
void trlEmuShellVideoFrameMenu()
{
	nngxUpdateBuffer(g_pTrlVideoMenuTexBuf, (TRL_EMUCORE_TEX_X/2)*TRL_EMUCORE_TEX_Y*2);

    glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[1]);
    glViewport(0, 0, nn::gx::DISPLAY1_WIDTH, nn::gx::DISPLAY1_HEIGHT);

    glUseProgram(g_nTrlVideoProgramID[1]);
    glBindBuffer(GL_ARRAY_BUFFER, g_nTrlVideoArrayBufferID1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_nTrlVideoElementArrayBuffer);
    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12*sizeof(GLfloat)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexID1);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
    //glDisableVertexAttribArray(0);
    //glDisableVertexAttribArray(1);
}

/** @brief Capture Current Frame */
void trlEmuShellVideoCapture()
{
	DateTime now = DateTime::GetNow();
	char szFileName[256];
	sprintf(szFileName, "sdmc:/%04d%02d%02d-%02d'%02d'%02d.bmp", now.GetYear(), now.GetMonth(), now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond());

	trlEmuShellVideoMaskMode(false);
	trlEmuShellVideoFrame();
	trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY0, false);

	u32 nSize = TRL_VIDEO_BMHEADER + TRL_DISPLAY_HEIGHT*TRL_DISPLAY_WIDTH*2 + 2;
	u8* pBitmap = (u8*)trlMemAlloc(nSize);
	trlMemCopy(pBitmap, g_nTrlVideoBitmapHeader, TRL_VIDEO_BMHEADER);

	GLint nAddr;
	nngxActiveDisplay(NN_GX_DISPLAY0);
    nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_ADDRESS, &nAddr);

	u16* pData = reinterpret_cast<u16*>(nAddr);
	u16* pTemp = (u16*)&pBitmap[TRL_VIDEO_BMHEADER];
	for (int y = 0, i = 0; y < TRL_DISPLAY_HEIGHT; ++y)
	{
		i = y;
		for (int x = 0; x < TRL_DISPLAY_WIDTH; ++x)
		{
			*pTemp++ = pData[i]>>1;
			i += TRL_DISPLAY_HEIGHT;
		}
	}

	nngxUpdateBuffer(pBitmap, nSize);
	trlFileWrite(szFileName, pBitmap, nSize);
	trlMemFree(pBitmap);
}

/** @brief Change Texture Filter Mode */
void trlEmuShellVideoFilterMode(u32 nMode)
{
	glBindTexture(GL_TEXTURE_2D, g_nTrlVideoTexID0[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, nMode);
	glBindTexture(GL_TEXTURE_2D, 0);
}

/** @brief Change Mask Mode */
void trlEmuShellVideoMaskChangeMode(u32 nMode)
{
	g_sTrlVideoMaskData.nMode = nMode;
	g_sTrlVideoMaskData.pDarkEnable = &g_sTrlVideoMaskData.bDarkEnable[g_sTrlVideoMaskData.nMode];
	g_sTrlVideoMaskData.pReduceEnable = &g_sTrlVideoMaskData.bReduceEnable[g_sTrlVideoMaskData.nMode];
	g_sTrlVideoMaskData.pMotionBEnable = &g_sTrlVideoMaskData.bMotionBEnable[g_sTrlVideoMaskData.nMode];
	g_sTrlVideoMaskData.pDark = &g_sTrlVideoMaskData.nDark[g_sTrlVideoMaskData.nMode];
	g_sTrlVideoMaskData.pReduceColorR = &g_sTrlVideoMaskData.nReduceColorR[g_sTrlVideoMaskData.nMode];
	g_sTrlVideoMaskData.pReduceColorG = &g_sTrlVideoMaskData.nReduceColorG[g_sTrlVideoMaskData.nMode];
	g_sTrlVideoMaskData.pReduceColorB = &g_sTrlVideoMaskData.nReduceColorB[g_sTrlVideoMaskData.nMode];
	g_sTrlVideoMaskData.pMotionBlur = &g_sTrlVideoMaskData.nMotionBlur[g_sTrlVideoMaskData.nMode];

	trlEmuShellPatchMaskChangeMode(nMode);
	trlEmuShellVideoMaskMode();
	trlEmuShellVideoMotionBlur();
}

/** @brief Change Motion Blur */
void trlEmuShellVideoMotionBlur()
{
	switch(*g_sTrlVideoMaskData.pMotionBEnable)
	{
	case 0:	// Normal
		break;
	case 1:	// Black Fade
		{
			u16 nColor = (0x842 * (*g_sTrlVideoMaskData.pMotionBlur)) | 1;
			u16* pFrame = (u16*)g_pTrlVideoMotionTexBuf;
			if(*pFrame != nColor)
			{
				for(u32 n=0; n<TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y; ++n, ++pFrame)
					*pFrame = nColor;
				nngxUpdateBuffer(g_pTrlVideoMotionTexBuf, TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2);
			}
		}
		break;
	case 2:	// White Fade
		break;
	case 3:	// Frame Blend
		break;
	}
}

/** @brief Change Mask Mode */
void trlEmuShellVideoMaskMode(u32 nDark, f32 fDarkRate)
{
    glUseProgram(g_nTrlVideoProgramID[0]);
	if(*g_sTrlVideoMaskData.pReduceEnable)
	{
		glUniform4f(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].constRgba"), *g_sTrlVideoMaskData.pReduceColorR / 31.f, *g_sTrlVideoMaskData.pReduceColorG / 31.f, *g_sTrlVideoMaskData.pReduceColorB / 31.f, 1.0f);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].srcRgb"), GL_TEXTURE0, GL_CONSTANT, GL_CONSTANT);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].srcAlpha"), GL_TEXTURE0, GL_TEXTURE0, GL_TEXTURE0);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].operandRgb"), GL_SRC_COLOR, GL_SRC_COLOR, GL_SRC_COLOR);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].operandAlpha"), GL_SRC_ALPHA, GL_SRC_ALPHA, GL_SRC_ALPHA);
		glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].combineRgb"), GL_SUBTRACT);
		glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].combineAlpha"), GL_REPLACE);
	}
	else
	{
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].srcRgb"), GL_TEXTURE0, GL_TEXTURE0, GL_TEXTURE0);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].srcAlpha"), GL_TEXTURE0, GL_TEXTURE0, GL_TEXTURE0);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].operandRgb"), GL_SRC_COLOR, GL_SRC_COLOR, GL_SRC_COLOR);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].operandAlpha"), GL_SRC_ALPHA, GL_SRC_ALPHA, GL_SRC_ALPHA);
		glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].combineRgb"), GL_REPLACE);
		glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[0].combineAlpha"), GL_REPLACE);
	}

	switch(nDark)
	{
	case 0:	// Mask
		fDarkRate = *g_sTrlVideoMaskData.pDark / 10.f;
		break;
	case 1:	// VCM Normal Dark
		fDarkRate = (g_nTrlVideoMenuDark + fDarkRate * (10 - g_nTrlVideoMenuDark)) / 10.f;
		if(*g_sTrlVideoMaskData.pDarkEnable)
			fDarkRate *= *g_sTrlVideoMaskData.pDark / 10.f;
		break;
	case 2:	// VCM All Dark
		if(*g_sTrlVideoMaskData.pDarkEnable)
			fDarkRate *= *g_sTrlVideoMaskData.pDark / 10.f;
		break;
	}
	if(*g_sTrlVideoMaskData.pDarkEnable || nDark)
	{
		glUniform4f(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].constRgba"), fDarkRate, fDarkRate, fDarkRate, 1.0f);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].srcRgb"), GL_PREVIOUS, GL_CONSTANT, GL_CONSTANT);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].srcAlpha"), GL_PREVIOUS, GL_PREVIOUS, GL_PREVIOUS);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].operandRgb"), GL_SRC_COLOR, GL_SRC_COLOR, GL_SRC_COLOR);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].operandAlpha"), GL_SRC_ALPHA, GL_SRC_ALPHA, GL_SRC_ALPHA);
		glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].combineRgb"), GL_MODULATE);
		glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].combineAlpha"), GL_REPLACE);
	}
	else
	{
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].srcRgb"), GL_PREVIOUS, GL_PREVIOUS, GL_PREVIOUS);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].srcAlpha"), GL_PREVIOUS, GL_PREVIOUS, GL_PREVIOUS);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].operandRgb"), GL_SRC_COLOR, GL_SRC_COLOR, GL_SRC_COLOR);
		glUniform3i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].operandAlpha"), GL_SRC_ALPHA, GL_SRC_ALPHA, GL_SRC_ALPHA);
		glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].combineRgb"), GL_REPLACE);
		glUniform1i(glGetUniformLocation(g_nTrlVideoProgramID[0], "dmp_TexEnv[1].combineAlpha"), GL_REPLACE);
	}
}

/** @brief Frame Blend */
void trlEmuShellVideoFrameBlend()
{
	u16* pTex0 = (u16*)g_sEmuShellBuffer.pTextureBuf[0];
	u16* pTex1 = (u16*)g_sEmuShellBuffer.pTextureBuf[1];
	u16* pScrn = (u16*)g_sEmuShellBuffer.pTextureBuf[g_sEmuShellBuffer.nTexID];
	for(u32 n=0; n<TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y; ++n)
	{
		u16 nR = (((*pTex0>>1) & 0x001F) + ((*pTex1>>1) & 0x001F)) >> 1;
		u16 nG = (((*pTex0>>6) & 0x001F) + ((*pTex1>>6) & 0x001F)) >> 1;
		u16 nB = (((*pTex0>>11) & 0x001F) + ((*pTex1>>11) & 0x001F)) >> 1;
		*pScrn = (nR<<1) | (nG<<6) | (nB<<11) | 1;
		pTex0++;
		pTex1++;
		pScrn++;
	}
}

/** @brief Draw Debug Info */
void trlEmuShellVideoDrawDebugInfo(u32 nLine, const char *szFormat, ...)
{
	va_list va;
	va_start(va, szFormat);
	s32 nStringSize = vsnprintf(g_szTrlVidioString, 128, szFormat, va);
	va_end(va);

	if(nStringSize>0)
	{
		if(nStringSize>8)
			nStringSize = 8;
		trlEmuShellFontDraw(0, nLine, 8, g_szTrlVidioString, nStringSize, (u16*)g_pTrlVideoDebugTexBuf, TRL_FONT_WHITE);
	}
}

/** @brief Draw Debug Warn */
void trlEmuShellVideoDrawDebugWarn(u32 nLine, const char *szFormat, ...)
{
	va_list va;
	va_start(va, szFormat);
	s32 nStringSize = vsnprintf(g_szTrlVidioString, 128, szFormat, va);
	va_end(va);

	if(nStringSize>0)
	{
		if(nStringSize>8)
			nStringSize = 8;
		trlEmuShellFontDraw(0, nLine, 8, g_szTrlVidioString, nStringSize, (u16*)g_pTrlVideoDebugTexBuf, TRL_FONT_YELLOW);
	}
}

/** @brief Draw Text */
void trlEmuShellVideoDrawText(u32 nColor, u32 nX, u32 nY, const char *szFormat, ...)
{
	va_list va;
	va_start(va, szFormat);
	s32 nStringSize = vsnprintf(g_szTrlVidioString, 128, szFormat, va);
	va_end(va);

	if(nStringSize>0)
		trlEmuShellFontDraw(nX, nY, 32, g_szTrlVidioString, nStringSize, (u16*)g_pTrlVideoMenuTexBuf, nColor);
}

/** @brief Init */
void trlEmuShellVideoInit(u32 nPara)
{
#if TRL_DEMO
	nPara = 0;
#endif

	switch(g_sEmuShellBuffer.nRomType)
	{
	case TRL_EMUCORE_ROMTYPE_AGB:
		g_bTrlVideoStereoEnable = 0;
		g_bTrlVideoFaceEnable = 0;
		break;
	case TRL_EMUCORE_ROMTYPE_CGB:
		g_bTrlVideoStereoEnable = nPara;
		g_bTrlVideoFaceEnable = nPara;
		break;
	case TRL_EMUCORE_ROMTYPE_NES:
		g_bTrlVideoStereoEnable = 0;
		g_bTrlVideoFaceEnable = 0;
		break;
	}

	g_bTrlVideoInit = 0;
	g_nTrlVideoMenuDark = trlEmuShellDataGetConfigData("Menu", "MenuDark", 4);

	trlEmuShellFontInit();
	trlEmuShellVideoInitHardware();
	trlEmuShellVideoInitFrame();
	trlEmuShellVideoInitShader();
	trlEmuShellVideoInitDisplay0();
	trlEmuShellVideoInitDisplay1();
	trlEmuShellVideoInitDebug();
	trlEmuShellVideoInitFace();

	g_sEmuShellBuffer.funcChangeMaskMode = trlEmuShellVideoMaskChangeMode;

	// Init Mask
	g_sTrlVideoMaskData.bDarkEnable[0] = trlEmuShellDataGetConfigData("Mask", "DarkEnable0", 0);
	g_sTrlVideoMaskData.bReduceEnable[0] = trlEmuShellDataGetConfigData("Mask", "ReduceEnable0", 0);
	g_sTrlVideoMaskData.bMotionBEnable[0] = trlEmuShellDataGetConfigData("Mask", "MotionBEnable0", 0);
	g_sTrlVideoMaskData.nDark[0] = trlEmuShellDataGetConfigData("Mask", "Dark0", 10);
	g_sTrlVideoMaskData.nReduceColorR[0] = trlEmuShellDataGetConfigData("Mask", "ReduceColorR0", 0);
	g_sTrlVideoMaskData.nReduceColorG[0] = trlEmuShellDataGetConfigData("Mask", "ReduceColorG0", 0);
	g_sTrlVideoMaskData.nReduceColorB[0] = trlEmuShellDataGetConfigData("Mask", "ReduceColorB0", 0);
	g_sTrlVideoMaskData.nMotionBlur[0] = trlEmuShellDataGetConfigData("Mask", "MotionBlur0", 31);

#if TRL_STEREO
	if(g_bTrlVideoStereoEnable)
	{
		memset(&g_sTrlVideoStereoValue, 0xFF, sizeof(g_sTrlVideoStereoValue));

		g_sTrlVideoMaskData.bDarkEnable[1] = trlEmuShellDataGetConfigData("Mask", "DarkEnable2", 1);
		g_sTrlVideoMaskData.bReduceEnable[1] = trlEmuShellDataGetConfigData("Mask", "ReduceEnable2", 0);
		g_sTrlVideoMaskData.bMotionBEnable[1] = trlEmuShellDataGetConfigData("Mask", "MotionBEnable2", 1);
		g_sTrlVideoMaskData.nDark[1] = trlEmuShellDataGetConfigData("Mask", "Dark2", 8);
		g_sTrlVideoMaskData.nReduceColorR[1] = trlEmuShellDataGetConfigData("Mask", "ReduceColorR2", 0);
		g_sTrlVideoMaskData.nReduceColorG[1] = trlEmuShellDataGetConfigData("Mask", "ReduceColorG2", 0);
		g_sTrlVideoMaskData.nReduceColorB[1] = trlEmuShellDataGetConfigData("Mask", "ReduceColorB2", 0);
		g_sTrlVideoMaskData.nMotionBlur[1] = trlEmuShellDataGetConfigData("Mask", "MotionBlur2", 10);

		g_bTrlVideoBatteryThreadFlag = 1;
		g_hTrlVideoBatteryThread.StartUsingAutoStack(trlEmuShellVideoBatteryThreadFunc, 4096, 21);
	}
	else
#endif
	{
		g_sTrlVideoMaskData.bDarkEnable[1] = trlEmuShellDataGetConfigData("Mask", "DarkEnable1", 1);
		g_sTrlVideoMaskData.bReduceEnable[1] = trlEmuShellDataGetConfigData("Mask", "ReduceEnable1", 0);
		g_sTrlVideoMaskData.bMotionBEnable[1] = trlEmuShellDataGetConfigData("Mask", "MotionBEnable1", 1);
		g_sTrlVideoMaskData.nDark[1] = trlEmuShellDataGetConfigData("Mask", "Dark1", 8);
		g_sTrlVideoMaskData.nReduceColorR[1] = trlEmuShellDataGetConfigData("Mask", "ReduceColorR1", 0);
		g_sTrlVideoMaskData.nReduceColorG[1] = trlEmuShellDataGetConfigData("Mask", "ReduceColorG1", 0);
		g_sTrlVideoMaskData.nReduceColorB[1] = trlEmuShellDataGetConfigData("Mask", "ReduceColorB1", 0);
		g_sTrlVideoMaskData.nMotionBlur[1] = trlEmuShellDataGetConfigData("Mask", "MotionBlur1", 8);
	}

	trlEmuShellVideoMaskChangeMode(0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepthf(1.0f);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
}

/** @brief Start */
void trlEmuShellVideoStart()
{
	glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[0]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	nngxTransferRenderImage(g_nTrlVideoDispBuf0[g_nTrlVideoCurDispBuf0], NN_GX_ANTIALIASE_NOT_USED, GL_FALSE, 0, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[1]);        
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	nngxTransferRenderImage(g_nTrlVideoDispBuf1[g_nTrlVideoCurDispBuf1], NN_GX_ANTIALIASE_NOT_USED, GL_FALSE, 0, 0);
#if TRL_STEREO
	if(g_bTrlVideoStereoEnable)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[2]);        
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		nngxTransferRenderImage(g_nTrlVideoDispBuf0Ext[g_nTrlVideoCurDispBuf0Ext], NN_GX_ANTIALIASE_NOT_USED, GL_FALSE, 0, 0);
	}
#endif

	trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY_BOTH, true);
    nngxStartLcdDisplay();
}

/** @brief Exit */
void trlEmuShellVideoExit()
{
#if TRL_STEREO
	if(g_bTrlVideoStereoEnable)
	{
		g_bTrlVideoBatteryThreadFlag = 0;
		g_hTrlVideoBatteryThread.Join();
		g_hTrlVideoBatteryThread.Finalize();
		g_nTrlVideoStereoCamera.Finalize();
	}
    glDeleteRenderbuffers(2, g_nTrlVideoRenderBuf0Ext);    
    glDeleteFramebuffers(3, g_nTrlVideoFrameBufObj);
#else
    glDeleteFramebuffers(2, g_nTrlVideoFrameBufObj);
#endif

	glDeleteFramebuffers(2,g_nTrlVideoRenderBuf1);
    glDeleteRenderbuffers(2, g_nTrlVideoRenderBuf0); 

	for(u32 n=0; n<TRL_SHADER_COUNT; ++n)
		glDeleteProgram(g_nTrlVideoProgramID[n]);
	glDeleteShader(g_nTrlVideoShaderID);

	nngxActiveDisplay(NN_GX_DISPLAY1);
    nngxDeleteDisplaybuffers(2, g_nTrlVideoDispBuf1);

#if TRL_STEREO
	if(g_bTrlVideoStereoEnable)
	{
		nngxActiveDisplay(NN_GX_DISPLAY0_EXT);
		nngxDeleteDisplaybuffers(2, g_nTrlVideoDispBuf0Ext);		
	}
#endif
	
    nngxActiveDisplay(NN_GX_DISPLAY0);
    nngxDeleteDisplaybuffers(2, g_nTrlVideoDispBuf0);
	nngxDeleteCmdlists(1, &g_nTrlVideoCmdList);
    nngxFinalize();

	trlEmuShellFontExit();

	if(g_bTrlVideoFaceEnable)
	{
		for(u32 n=0; n<g_nTrlVideoFaceTexData; ++n)
			trlMemFreeDevice(g_pTrlVideoFaceTexData[n].pData);
		trlMemFree(g_pTrlVideoFaceTexData);
	}
	trlMemFreeDevice(g_pTrlVideoDebugTexBuf);	
	trlMemFreeDevice(g_pTrlVideoMenuTexBuf);	
	trlMemFreeDevice(g_pTrlVideoMotionTexBuf);
	trlMemFreeDevice(g_sEmuShellBuffer.pTextureBuf[1]);
	trlMemFreeDevice(g_sEmuShellBuffer.pTextureBuf[0]);

	g_bTrlVideoInit = 0;
}
