/**
 * @file trlEmuDemo.cpp
 * @author zhfang
 * @date 2010.09.12
 * @brief TRL Emulate For CTR - EmuShell Demo
 */
#include "..\EmuShell\trlEmuShellStruct.h"

#include <nn\os.h>
#include <nn\fs.h>
#include <nn\hid.h>
#include <nn\hid\CTR\hid_PadReaderForVc.h>
#include <nn\cfg.h>

using namespace nn::hid::CTR;
using namespace nn::os;

void PrintGLError(const GLenum errorCode)
{
	if ( errorCode != GL_NO_ERROR )
	{
		switch ( errorCode )
		{
		case GL_INVALID_ENUM:
			NN_LOG("GL Error : GL_INVALID_ENUM\n");
			break;
		case GL_INVALID_VALUE:
			NN_LOG("GL Error : GL_INVALID_VALUE\n");
			break;
		case GL_INVALID_OPERATION:
			NN_LOG("GL Error : GL_INVALID_OPERATION\n");
			break;
		case GL_OUT_OF_MEMORY:
			NN_LOG("GL Error : GL_OUT_OF_MEMORY\n");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: 
			NN_LOG("GL Error : GL_INVALID_FRAMEBUFFER_OPERATION\n");
			break;
		default:
			NN_LOG("GL Error : errorCode = 0x%x\n", errorCode);
			break;
		}
	}
}



#define DEMO_ASSERT_GL_ERROR()			\
{										\
	GLenum errorCode = glGetError();	\
	if ( errorCode != GL_NO_ERROR )		\
	{									\
		PrintGLError(errorCode);		\
		NN_LOG("\n");					\
	}									\
}


typedef struct BitmapFileHeader
{
    u8 bfType[2];
    u16 bfSize[2];
    u16 bfReserved1;
    u16 bfReserved2;
    u16 bfOffBits[2];    
} BitmapFileHeader;

typedef struct BitmapInfoHeader
{
    u32 biSize;
    s32 biWidth;
    s32 biHeight;
    u16 biPlanes;
    u16 biBitCount;
    u32 biCompression;
    u32 biSizeImage;
    s32 biXPixPerMeter;
    s32 biYPixPerMeter;
    u32 biClrUsed;
    u32 biClrImportant;    
} BitmapInfoHeader;

enum EDemoTexture
{
	eDemoTexture_Bottom_Manual = 0,
	eDemoTexture_Bottom_Thankyou,
	eDemoTexture_Bottom_Wait,
	eDemoTexture_Upper_Thankyou,
	eDemoTexture_Upper_Wait,
	eDemoTextureNum
};

const wchar_t* strDemoTextureFileName[] = 
{
	L"rom:/demo/Bottom_Manual.bmp",
	L"rom:/demo/Bottom_Thank.bmp",
	L"rom:/demo/Bottom_Wait.bmp",
	L"rom:/demo/Upper_ThankYou.bmp",
	L"rom:/demo/Upper_Wait.bmp"
};

static const char	g_szEmuDemoDefaultSavePath[] = "rom:/demo/default.sav";

GLuint demoTextureID[eDemoTextureNum];
GLuint demoVersionTextureID;
u8*	   demoVersionTextureBuf;
u32 nDemoVersionTextureWidth;
u32 nDemoVersionTexutreHeigh;
u32 nTextureWidth[eDemoTextureNum];
u32 nTextureHeigh[eDemoTextureNum];
u32 nBmpWidth[eDemoTextureNum];
u32 nBmpHeigh[eDemoTextureNum];

void trlEmuDemoLoadTexture();

u8* GetTextureData(const wchar_t* bmpRomFilename, u32& bmpWidth, u32& bmpHeight, u32& textureWidth, u32& textureHeight);
u8* GetBmpFileData(u8* rawDataBuffer, u32& bmpWidth, u32& bmpHeight);
u8* GetTextureDataFromBmpFileData(const u32& bmpWidth, const u32& bmpHeight, u8* bmpDataBuffer, u32& textureWidth, u32& textureHeight);
u32 GetTextureLength(const u32& imageLength);
bool ConvertGLTextureToNative(const GLenum format, const u32 width, const u32 height, void* glData, void* dmpData);

void DrawDisplay0(u32 demotexture);
void DrawDisplay1(u32 demotexture);
void DrawVersion();

GLuint	demoArrayBuffer0;
GLuint	demoElementArrayBuffer0;
GLuint	demoVersionArrayBuffer;
GLuint	demoVersionElementArrayBuffer;
GLuint	demoArrayBuffer1;
GLuint	demoElementArrayBuffer1;

extern GLuint					g_nTrlVideoFrameBufObj[2];
extern GLuint					g_nTrlVideoProgramID[2];
extern char						g_szEmuShellBuildTime[];

extern void trlEmuShellVideoSwapBuffer(const s32 display, const bool isWaitVSync);
extern void trlEmuShellVideoDrawDebugInfo(u32 nLine, const char *szFormat, ...);
extern void trlEmuShellFontDraw(u32 nX, u32 nY, u32 nTileX, const char *szText, u32 nCount, u16* pBuffer, u32 nColor);
extern u32 trlEmuShellDataGetConfigData(const char* szSection, const char* szValue, u32 nDefault);
extern void trlEmuShellAudioPlay();
extern void trlEmuShellAudioStop();
extern void trlEmuShellAudioReset();
extern void trlEmuShellAudioStart();
extern void trlEmuShellAudioMain();
extern void trlEmuShellVideoFrame();


/** @brief EmuDemo Init*/
void trlEmuDemoInit()
{
	GLushort nIdxs[] = {0, 1, 2, 3};
	GLfloat nCoords[] = {  //y, x, z
		-1.f,  1.f, 0.f,
		 1.f,  1.f, 0.f,
		-1.f,  -1.f, 0.f,
		 1.f,  -1.f, 0.f,
	};	
	GLfloat w00 = 0,h00 = 0;
	GLfloat w01 = 0.78125,h01 = 0.9375;
	GLfloat nTexCoords0[] = {
		w00, h00,		
		w00, h01,
		w01, h00,		
		w01, h01,
	};
	GLfloat w1 = 0.625,h1 =0.9375;
	GLfloat nTexCoords1[] = {
		0.f, 0.f,
		0.f,  h1,
		w1,  0.f,
		w1,   h1,
	};
	
	glGenBuffers(1, &demoArrayBuffer0);
	glBindBuffer(GL_ARRAY_BUFFER, demoArrayBuffer0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nCoords) + sizeof(nTexCoords0), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(nCoords), nCoords);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(nCoords), sizeof(nTexCoords0), nTexCoords0);

	glGenBuffers(1, &demoElementArrayBuffer0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, demoElementArrayBuffer0);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(nIdxs), nIdxs, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0) ;
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(nCoords));

	glGenBuffers(1, &demoArrayBuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, demoArrayBuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nCoords) + sizeof(nTexCoords1), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(nCoords), nCoords);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(nCoords), sizeof(nTexCoords1), nTexCoords1);

	glGenBuffers(1, &demoElementArrayBuffer1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, demoElementArrayBuffer1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(nIdxs), nIdxs, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0) ;
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(nCoords));

	GLfloat nVersionCoords[] = {  //y, x, z
		0.87f,  1.f, 0.f,
		 1.0f,  1.f, 0.f,
		0.87f,  -1.f, 0.f,
		 1.0f,  -1.f, 0.f,
	};
	GLfloat nVersionTexCoords[] = {
		0,0,
		0,1,
		1,0,
		1,1		
	};

	glGenBuffers(1, &demoVersionArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, demoVersionArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nVersionCoords) + sizeof(nVersionTexCoords), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(nVersionCoords), nVersionCoords);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(nVersionCoords), sizeof(nVersionTexCoords), nVersionTexCoords);

	glGenBuffers(1, &demoVersionElementArrayBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, demoVersionElementArrayBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(nIdxs), nIdxs, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0) ;
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(nVersionCoords));
	
	trlEmuDemoLoadTexture();

	trlEmuShellAudioStart();
}

enum EDemoState
{
	eDemoState_WaitFadeIn,
	eDemoState_Wait,
	eDemoState_WaitFadeOut,
	eDemoState_Game,
	eDemoState_EndFadeIn,
	eDemoState_End0,
	eDemoState_End1,
	eDemoState_EndFadeOut
};

EDemoState eDemoState;


s32 nDemoFadeCt = 0;
s32 nDemoDisplayVerCt = 0;
const s32 nDemoDisplayVerMax = 60;
const s32 nDemoFadeMax = 30;
s32 nDemoGameCt = 0;
s32 nDemoGameMax = 60;
s32 nDemoGameResetMax = 60;
s32 nDemoThxCt = 0;
const s32 nDemoThxMax0 = 120;
const s32 nDemoThxMax1 = 480;


inline void SetFade(f32 alpha)
{
	glBlendColor(0, 0, 0,alpha);
}

inline s32 trlEmuShellDemoFadeIn()
{
	f32 fade = 1.0 *nDemoFadeCt / nDemoFadeMax;
	SetFade(fade);
	if(nDemoFadeCt >= nDemoFadeMax)
	{
		nDemoFadeCt = nDemoFadeMax;
		return 0;		
	}
	nDemoFadeCt++;
	return 1;
}

inline s32 trlEmuShellDemoFadeOut()
{
	f32 fade = 1.0 *nDemoFadeCt / nDemoFadeMax;
	SetFade(fade);
	if(nDemoFadeCt <=0)
	{
		nDemoFadeCt = 0;
		return 0;		
	}
	nDemoFadeCt--;
	return 1;
}

void OpenFade()
{
	glEnable(GL_BLEND);		
	glBlendFunc(GL_CONSTANT_ALPHA, GL_ZERO);
	glBlendEquation(GL_ADD);
}

/** @brief EmuShell Demo Reset */
void trlEmuShellDemoReset()
{
	trlEmuShellAudioStop();
	g_pEmuShellCore->trlEmuCoreReset();
	trlEmuShellAudioReset();
	memset(g_sEmuShellBuffer.pTextureBuf[0], 0, TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2);	
	memset(g_sEmuShellBuffer.pTextureBuf[1], 0, TRL_EMUCORE_TEX_X*TRL_EMUCORE_TEX_Y*2);

	if(g_sEmuShellBuffer.nBackupDataSize)
	{
		if(trlFileRead(g_szEmuDemoDefaultSavePath, g_sEmuShellBuffer.pBackupData, g_sEmuShellBuffer.nBackupDataSize) != TRL_FILE_SUCCESS)
			memset(g_sEmuShellBuffer.pBackupData, 0, g_sEmuShellBuffer.nBackupDataSize);
	}
}

/** @brief EmuDemo Main Run */
void trlEmuShellDemoRun()
{	
	trlFileRead(g_szEmuDemoDefaultSavePath, g_sEmuShellBuffer.pBackupData, g_sEmuShellBuffer.nBackupDataSize);

	nDemoGameMax = trlEmuShellDataGetConfigData("Demo", "DemoTime", 180)*60;
	nDemoGameResetMax = trlEmuShellDataGetConfigData("Demo", "DemoResetTime", 1000)*60/1000;
	nDemoGameResetMax = 1;

	if(1)
	{
		eDemoState = eDemoState_WaitFadeIn;
		nDemoFadeCt = 0;
	}
	else
	{
		eDemoState = eDemoState_Wait;
		nDemoFadeCt = nDemoFadeMax;
		trlEmuShellDemoFadeIn();
	}


	PadReaderForVc sPad;
	PadStatus sPadStatus;
	TouchPanelReader sTouch;
	TouchPanelStatus sTouchStatus;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);


	OpenFade();	
	while(1)
	{
		sPad.ReadLatest(&sPadStatus);
		sTouch.ReadLatest(&sTouchStatus);

		sPadStatus.hold |= ((sPadStatus.hold & PLUS_BUTTON_EMULATION_MASK)>>24);

		switch(eDemoState)
		{
		case eDemoState_WaitFadeIn:	
			if(trlEmuShellDemoFadeIn() == 0)
			{
				eDemoState = eDemoState_Wait;
			}
			DrawDisplay0(eDemoTexture_Upper_Wait);
			DrawVersion();
			DrawDisplay1(eDemoTexture_Bottom_Wait);
			trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY_BOTH,true);
			break;
		case eDemoState_Wait:			
			DrawDisplay0(eDemoTexture_Upper_Wait);
			DrawVersion();
			DrawDisplay1(eDemoTexture_Bottom_Wait);		
			trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY_BOTH,true);
			{
				static s32 bDemoWaitFlag = 0;
				if( sPadStatus.hold & BUTTON_A)
				{
					if(bDemoWaitFlag == 1)
					{
						eDemoState = eDemoState_WaitFadeOut;
						bDemoWaitFlag = 0;
					}						
				}
				else
				{
					if(bDemoWaitFlag == 0)
					{
						bDemoWaitFlag = 1;
					}					
				}
			}
			break;
		case eDemoState_WaitFadeOut:
			if(trlEmuShellDemoFadeOut() == 0)
			{				
				trlEmuShellAudioPlay();
				eDemoState = eDemoState_Game;
				nDemoGameCt = 0;
			}
			DrawDisplay0(eDemoTexture_Upper_Wait);
			DrawVersion();
			DrawDisplay1(eDemoTexture_Bottom_Wait);
			trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY_BOTH,true);
			break;
		case eDemoState_Game:
			{			
				static s32 bDemoResetFlag = 0;
				static s32 nDemoResetCt = 0;
				// Update Input				
				if((sPadStatus.hold & (BUTTON_RIGHT|BUTTON_LEFT)) == (BUTTON_RIGHT|BUTTON_LEFT))
					sPadStatus.hold &= ~BUTTON_RIGHT;
				if((sPadStatus.hold & (BUTTON_UP|BUTTON_DOWN)) == (BUTTON_UP|BUTTON_DOWN))
					sPadStatus.hold &= ~BUTTON_DOWN;
				g_pEmuShellCore->trlEmuCoreInput(~sPadStatus.hold);
				// TRL Kernel
				g_pEmuShellCore->trlEmuCoreRunOneFrame();
				// CTR Render
				trlEmuShellVideoFrame();

				DrawDisplay1(eDemoTexture_Bottom_Manual);
				trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY_BOTH,true);				
				if( (sPadStatus.hold & BUTTON_L) && (sPadStatus.hold & BUTTON_R) && (sPadStatus.hold & BUTTON_START))
				{
					if(bDemoResetFlag == 1)
					{
						nDemoResetCt++;
						if(nDemoResetCt >= nDemoGameResetMax)
						{
							nDemoResetCt = 0;
							bDemoResetFlag = 0;

							trlEmuShellDemoReset();
							eDemoState = eDemoState_WaitFadeIn;						
							nDemoFadeCt = 0;						
							OpenFade();

							if( (sPadStatus.hold & BUTTON_L) && (sPadStatus.hold & BUTTON_R))
							{
								nDemoDisplayVerCt = nDemoDisplayVerMax;
							}
						}
					}
				}
				else
				{
					if(bDemoResetFlag == 0)
						bDemoResetFlag = 1;		
					nDemoResetCt = 0;
				}
				nDemoGameCt++;				
				if(nDemoGameCt >= nDemoGameMax)
				{
					trlEmuShellDemoReset();
					eDemoState = eDemoState_EndFadeIn;
					OpenFade();
					nDemoFadeCt = 0;
					break;
				}
				trlEmuShellAudioMain();
			}
			break;
		case eDemoState_EndFadeIn:			
			if(trlEmuShellDemoFadeIn() == 0)
			{				
				eDemoState = eDemoState_End0;
				nDemoThxCt = 0;

			}
			DrawDisplay0(eDemoTexture_Upper_Thankyou);
			DrawVersion();
			DrawDisplay1(eDemoTexture_Bottom_Thankyou);
			trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY_BOTH,true);
			break;
		case eDemoState_End0:
			nDemoThxCt++;
			if(nDemoThxCt >= nDemoThxMax0)
			{
				eDemoState = eDemoState_End1;
			}
			DrawDisplay0(eDemoTexture_Upper_Thankyou);
			DrawVersion();
			DrawDisplay1(eDemoTexture_Bottom_Thankyou);
			trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY_BOTH,true);
			break;
		case eDemoState_End1:
			nDemoThxCt++;
			if(nDemoThxCt >= nDemoThxMax1)
			{
				eDemoState = eDemoState_EndFadeOut;
			}
			if( sPadStatus.hold != 0)
			{
				eDemoState = eDemoState_EndFadeOut;
			}			
			DrawDisplay0(eDemoTexture_Upper_Thankyou);
			DrawVersion();
			DrawDisplay1(eDemoTexture_Bottom_Thankyou);
			trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY_BOTH,true);
			break;
		case eDemoState_EndFadeOut:
			if(trlEmuShellDemoFadeOut() == 0)
			{
				eDemoState = eDemoState_WaitFadeIn;
			}
			DrawDisplay0(eDemoTexture_Upper_Thankyou);
			DrawVersion();
			DrawDisplay1(eDemoTexture_Bottom_Thankyou);
			trlEmuShellVideoSwapBuffer(NN_GX_DISPLAY_BOTH,true);
			break;
		}
	}	
}


void DrawDisplay0(u32 demotexture)
{	
	glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[0]);
    glViewport(0, 0, nn::gx::DISPLAY0_WIDTH, nn::gx::DISPLAY0_HEIGHT);
	glDisable(GL_COLOR_LOGIC_OP);	

	glUseProgram(g_nTrlVideoProgramID[0]);

	glBindBuffer(GL_ARRAY_BUFFER, demoArrayBuffer0);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, demoElementArrayBuffer0);
    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12*sizeof(GLfloat)));

	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, demoTextureID[demotexture]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);	
}

void DrawVersion()
{
	/*if(nDemoDisplayVerCt > 0)
	{
		nDemoDisplayVerCt--;

		glBindBuffer(GL_ARRAY_BUFFER, demoVersionArrayBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, demoVersionElementArrayBuffer);
		//glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12*sizeof(GLfloat)));
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, demoVersionTextureID);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
		//glDisableVertexAttribArray(0);
		//glDisableVertexAttribArray(1);		
	}*/
}

void DrawDisplay1(u32 demotexture)
{   
	glBindFramebuffer(GL_FRAMEBUFFER, g_nTrlVideoFrameBufObj[1]);
    glViewport(0, 0, nn::gx::DISPLAY1_WIDTH, nn::gx::DISPLAY1_HEIGHT);
	glDisable(GL_COLOR_LOGIC_OP);

	glUseProgram(g_nTrlVideoProgramID[1]);	
	glBindBuffer(GL_ARRAY_BUFFER, demoArrayBuffer1);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, demoElementArrayBuffer1);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12*sizeof(GLfloat)));
	
	glActiveTexture(GL_TEXTURE0);	
	glBindTexture(GL_TEXTURE_2D, demoTextureID[demotexture]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
}

void trlEmuDemoLoadTexture()
{
	for(int i=0;i<eDemoTextureNum;i++)
	{
		u8* textureDataPtr = GetTextureData(strDemoTextureFileName[i], nBmpWidth[i], nBmpHeigh[i], nTextureWidth[i], nTextureHeigh[i]); 

		GLenum target = GL_TEXTURE_2D;
		GLenum internalFormat = GL_RGB_NATIVE_DMP; 
		GLenum format = GL_RGB_NATIVE_DMP;
		GLenum type = GL_UNSIGNED_BYTE;
		GLuint textureId = 0;

		//gentexture
		{
			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &textureId);
			 DEMO_ASSERT_GL_ERROR();

			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(target, 0, internalFormat,
							nTextureWidth[i], nTextureHeigh[i], 0,
							format, type, textureDataPtr);
			DEMO_ASSERT_GL_ERROR();
		}

		if(textureId != 0)
		{
			demoTextureID[i] = textureId;
			NN_LOG("Demo Create Texture %d\n", i);
		}
		trlMemFreeDevice(textureDataPtr);
	}

	nDemoVersionTextureWidth = 256;
	nDemoVersionTexutreHeigh = 16;
	demoVersionTextureBuf = (u8*)trlMemAllocDevice(nDemoVersionTextureWidth*nDemoVersionTexutreHeigh*2, 128);
	memset(demoVersionTextureBuf, 0, nDemoVersionTextureWidth*nDemoVersionTexutreHeigh*2);
	glGenTextures(1, &demoVersionTextureID);
	glBindTexture(GL_TEXTURE_2D, demoVersionTextureID);
	glTexImage2D(GL_TEXTURE_2D | NN_GX_MEM_FCRAM | GL_NO_COPY_FCRAM_DMP, 0, GL_RGBA_NATIVE_DMP, nDemoVersionTextureWidth, nDemoVersionTexutreHeigh, 0, GL_RGBA_NATIVE_DMP, GL_UNSIGNED_SHORT_5_5_5_1, demoVersionTextureBuf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);


	{
		int ct = 0;
		while(g_szEmuShellBuildTime[ct] != 0)
		{
			ct++;
			if(ct >= 0x20)
				break;
		}
		trlEmuShellFontDraw(0,0,0, g_szEmuShellBuildTime,ct, (u16*)demoVersionTextureBuf,0);
	}	
}

u8* GetTextureData(const wchar_t* bmpRomFilename, 
                   u32& bmpWidth, u32& bmpHeight,
                   u32& textureWidth, u32& textureHeight)
{   
    NN_LOG("\nReading data form ROMFS...\n");

    nn::fs::FileReader file(bmpRomFilename);
    
    size_t fileSize = file.GetSize();
    NN_LOG("  fileSize = %d (Byte)\n", fileSize);
    if ( fileSize == 0 )
    {
        NN_TPANIC_("Failed to open bmp file.\n");
        return NULL;
    }

    void* buf = trlMemAllocDevice(fileSize);		

    s32 readSize = file.Read(buf, fileSize);
    NN_LOG("  file readSize = %d (Byte)\n", readSize);
    if ( readSize == 0 )
    {
        NN_TPANIC_("Failed to open bmp file.\n");
        return NULL;
    }

    u8* bmpDataBuffer = NULL;
    bmpDataBuffer = GetBmpFileData((u8*)buf, bmpWidth, bmpHeight);
    NN_LOG("  bmpWidth = %d, bmpHeight = %d\n", bmpWidth, bmpHeight);

    u8* textureDataBuffer = NULL;
    textureDataBuffer = GetTextureDataFromBmpFileData(bmpWidth, bmpHeight, bmpDataBuffer,
        textureWidth, textureHeight);
    NN_LOG("  textureWidth = %d, textureHeight = %d\n", textureWidth, textureHeight);

    file.Finalize();
    trlMemFreeDevice(buf);
    return textureDataBuffer;
}

u8* GetBmpFileData(u8* rawDataBuffer,
                    u32& bmpWidth, u32& bmpHeight)
{
    BitmapInfoHeader* bmp_info_header_ptr = (BitmapInfoHeader*)(rawDataBuffer + sizeof(BitmapFileHeader));
    bmpWidth = bmp_info_header_ptr->biWidth;
    bmpHeight = bmp_info_header_ptr->biHeight;
    u8* bmpDataBuffer = rawDataBuffer + sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    return bmpDataBuffer;
}

u8* GetTextureDataFromBmpFileData(const u32& bmpWidth, const u32& bmpHeight, u8* bmpDataBuffer, 
                                    u32& textureWidth, u32& textureHeight)
{
    // Convert BMP to OpenGL RGB format
    textureWidth = GetTextureLength(bmpWidth);
    textureHeight = GetTextureLength(bmpHeight);
    u8* textureGLDataBuffer = reinterpret_cast<u8*>( trlMemAllocDevice(3 * textureWidth * textureHeight) );

    for (u32 y = 0; y < textureHeight; y++)
    {        
        for (u32 x = 0; x < textureWidth; x++)
        {
            u8* textureDataPtr = textureGLDataBuffer;
            textureDataPtr += 3 * ((static_cast<u32>(textureWidth) * y) + x);
            if ( ( x >= bmpWidth ) || ( y >= bmpHeight ) )
            {
                (*textureDataPtr) = 0x00;
                textureDataPtr += 1;
                
                (*textureDataPtr) = 0x00;
                textureDataPtr += 1;
                
                (*textureDataPtr) = 0x00;
            }
            else
            {
                u8* bmpDataPtr = bmpDataBuffer;
                bmpDataPtr += 3 * (bmpWidth * y + x);
                
                (*textureDataPtr) = (*(bmpDataPtr + 2));
                textureDataPtr += 1;
                (*textureDataPtr) = (*(bmpDataPtr + 1));
                textureDataPtr += 1;
                
                (*textureDataPtr) = (*(bmpDataPtr + 0));
            }
        }
    }

    u8* textureDataBuffer = reinterpret_cast<u8*>( trlMemAllocDevice(3 * textureWidth * textureHeight) );

    // Convert OpenGL RGB format to PICA Native RGB format
    GLenum format = GL_RGB_NATIVE_DMP;
    bool result = ConvertGLTextureToNative(
        format, textureWidth, textureHeight,
        textureGLDataBuffer, textureDataBuffer);
    if ( result )
    {
        NN_LOG("  Convert to GL_RGB_NATIVE_DMP succeeded.\n");
    }
    else
    {
        NN_TPANIC_("  Convert to GL_RGB_NATIVE_DMP failed.\n");
    }

    trlMemFreeDevice(textureGLDataBuffer);

    return textureDataBuffer;
}


u32 GetTextureLength(const u32& imageLength)
{        
    u32 textureLength = 8;

    // 8, 16, 32, 64, 128, 256, 512, 1024
    for (u32 i = 0; i < 7; i++)
    {
        if ( imageLength > textureLength )
        {
            textureLength *= 2;
        }
        else
        {
            return textureLength;
        }
    }

    return 1024;
}

////////////////////////////////

/*
*  Definitions
*/    
const u32 TEXTURE_BLOCK_SIZE = 8;
const u32 TEXTURE_PIXELS_IN_BLOCK = TEXTURE_BLOCK_SIZE * TEXTURE_BLOCK_SIZE;
#define SWAP(A, B)		tmp = (A); (A) = (B); (B) = tmp

/*
*  Type definitions
*/

enum TextureMode
{
	TEXTURE_LINE_TO_BLOCK_MODE = 0,
	TEXTURE_BLOCK_TO_LINE_MODE = 1
};

typedef struct
{	    
	GLenum format;        
	s32 blocksInRow;
	s32	blocksInCol;
	u8*	src;
	u8*	dst;
	u32	width;
	u32	height;
	u32	yflip;
	u32	mode;
} TextureInformation;

typedef s32 (*textureConvertFunction)(TextureInformation* textureInformation);

/*
*  Local Function Declaration
*/
static s32 GetPixelByte(const GLenum format);

static s32 ReadBlock(u32 no, u8* buf, TextureInformation* textureInformation);
static s32 WriteBlock(u32 no, const u8* pSrc, TextureInformation* textureInformation);
static s32 DeBlock(const u8* pSrc, u8* pDst, s32 blocksize, TextureInformation* textureInformation);
static s32 EnBlock(const u8* pSrc, u8* pDst, s32 blocksize, TextureInformation* textureInformation);
static s32 SwapColorComponents(TextureInformation* textureInformation);

static s32 ConvertFormat8888Function(TextureInformation* textureInformation);
static s32 ConvertFormat888Function(TextureInformation* textureInformation);
static s32 ConvertFormat88Function(TextureInformation* textureInformation);
static s32 ConvertFormatXXXXFunction(TextureInformation* textureInformation);

static textureConvertFunction convertFunctionArray[] =
{
	ConvertFormat8888Function,  /* GL_RGBA_NATIVE_DMP R8G8B8A8 */
	ConvertFormat888Function,   /* GL_RGB_NATIVE_DMP R8G8B8 */
	ConvertFormat88Function,    /* GL_LUMINANCE_ALPHA_NATIVE_DMP L8A8 */
	ConvertFormatXXXXFunction,  /* else     */
	ConvertFormatXXXXFunction,  /* R5G6B5   */
	ConvertFormatXXXXFunction,  /* R5G5B5A1 */
	ConvertFormatXXXXFunction,  /* R4G4B4A4 */	    
	ConvertFormatXXXXFunction,  /* L8       */
	ConvertFormatXXXXFunction   /* A8       */
};

/*
*	Export functions
*/

/* Block <--> Linear conversion */
bool ConvertGLTextureToNative(const GLenum format, const u32 width, const u32 height,
							  void* glData, void* dmpData)
{
	bool yflip = true;
	TextureMode mode = TEXTURE_LINE_TO_BLOCK_MODE;

	u8 blockBuf[TEXTURE_PIXELS_IN_BLOCK * 4];
	TextureInformation textureInformation;

	if (width & 0x00000003 || height & 0x00000003)
	{
		return false;
	}

	textureInformation.format = format;
	textureInformation.width = width;
	textureInformation.height = height;
	textureInformation.blocksInRow = (textureInformation.width / TEXTURE_BLOCK_SIZE);
	textureInformation.blocksInCol = (textureInformation.height / TEXTURE_BLOCK_SIZE);
	textureInformation.src = (u8*)glData;
	textureInformation.dst = (u8*)dmpData;
	if ( yflip )
	{
		textureInformation.yflip = 1;
	}
	else
	{
		textureInformation.yflip = 0;
	}
	textureInformation.mode = mode;

	/* Convert color format */
	SwapColorComponents(&textureInformation);
	/* for each row */
	for (s32 row = 0; row < textureInformation.blocksInCol; row++)
	{
		/* for each column */
		for (s32 col = 0; col < textureInformation.blocksInRow; col++)
		{
			/* Read one unit from source buffer. Read in source addressing and color format */
			ReadBlock(row * textureInformation.blocksInRow + col, blockBuf, &textureInformation);
			/* Write one unit to destination buffer. written with converting addressing format */
			WriteBlock(row * textureInformation.blocksInRow + col, blockBuf, &textureInformation);
		}
	}

	return true;
}

/*
*	Local functions
*/
static s32 GetPixelByte(const GLenum format)
{
	/* GL_RGBA_NATIVE_DMP R8G8B8A8 */
	if ( format == GL_RGBA_NATIVE_DMP )
	{
		return 4;
	}
	/* GL_RGB_NATIVE_DMP R8G8B8 */
	else if ( format == GL_RGB_NATIVE_DMP )
	{
		return 3;
	}
	/* GL_LUMINANCE_ALPHA_NATIVE_DMP L8A8 */
	else if ( format == GL_LUMINANCE_ALPHA_NATIVE_DMP )
	{
		return 2;
	}
	else
	{
		NN_TLOG_("Unsupported texture format.");
		NN_TASSERT_(0);

		return 1;
	}
}

static s32 ReadBlock(u32 no, u8* buf, TextureInformation* textureInformation)
{
	u32 row = (no / textureInformation->blocksInRow);
	u32 column = (no % textureInformation->blocksInRow);
	u32 pixelByte = GetPixelByte(textureInformation->format);

	/* Read src us32 */
	if (textureInformation->mode == TEXTURE_BLOCK_TO_LINE_MODE)
	{
		/* Get source buffer pointer */
		const u8* pSrc = textureInformation->src + 
			no * pixelByte * TEXTURE_PIXELS_IN_BLOCK;

		/* read uint image from block format buffer */
		trlMemCopy(buf, pSrc, (TEXTURE_PIXELS_IN_BLOCK * pixelByte) );
	}
	else // if (mode == L2B)
	{
		/* Get source buffer pointer */
		const u8* pSrc = textureInformation->src + 
			(row * TEXTURE_PIXELS_IN_BLOCK * pixelByte * textureInformation->blocksInRow) + 
			(column * pixelByte * TEXTURE_BLOCK_SIZE);

		/* read uint image from linear format buffer */
		for (s32 i = 0; i < TEXTURE_BLOCK_SIZE; i++)
		{
			trlMemCopy(buf, pSrc, pixelByte * TEXTURE_BLOCK_SIZE);
			buf += pixelByte * TEXTURE_BLOCK_SIZE;
			pSrc += pixelByte * textureInformation->width;
		}
	}

	return 1;
}

static s32 WriteBlock(u32 no, const u8* pSrc, TextureInformation* textureInformation)
{
	u32 row = (no / textureInformation->blocksInRow);
	u32 column = (no % textureInformation->blocksInRow);
	u32 pixelByte = GetPixelByte(textureInformation->format);

	/* Read src uint */
	if (textureInformation->mode == TEXTURE_BLOCK_TO_LINE_MODE)
	{
		/* Get destination buffer pointer */
		u8*	pDst;

		/* Get destination pointer */
		if (textureInformation->yflip)
		{
			pDst = textureInformation->dst + 
				((textureInformation->blocksInCol - row - 1) * TEXTURE_PIXELS_IN_BLOCK * pixelByte * 
				textureInformation->blocksInRow) + column * pixelByte * TEXTURE_BLOCK_SIZE;
		}
		else
		{
			pDst = textureInformation->dst + 
				(row * TEXTURE_PIXELS_IN_BLOCK * pixelByte * textureInformation->blocksInRow) + 
				column * pixelByte * TEXTURE_BLOCK_SIZE;
		}

		/* write uint image to linear format buffer */
		DeBlock(pSrc, pDst, TEXTURE_BLOCK_SIZE, textureInformation);
	}
	else // if (mode == L2B)
	{
		/* Get destination buffer pointer */
		u8* pDst;

		if (textureInformation->yflip)
		{
			pDst = textureInformation->dst + 
				((textureInformation->blocksInCol - row - 1) * textureInformation->blocksInRow + column) * 
				TEXTURE_PIXELS_IN_BLOCK * pixelByte;
		}
		else
		{
			pDst = textureInformation->dst + 
				no * TEXTURE_PIXELS_IN_BLOCK * pixelByte;
		}

		/* write uint image to block format buffer */
		EnBlock(pSrc, pDst, TEXTURE_BLOCK_SIZE, textureInformation);
	}

	return 1;
}

static s32 DeBlock(const u8* pSrc, u8* pDst, s32 blocksize, TextureInformation* textureInformation)
{
	u32 pixelByte = GetPixelByte(textureInformation->format);

	if (blocksize != 1)
	{
		s32 pixels;
		blocksize >>= 1;
		pixels = blocksize * blocksize;            
		//s32 dstWidth = textureInformation->width;

		if (!textureInformation->yflip)
		{
			DeBlock(pSrc + (pixelByte * pixels * 0), 
				pDst, blocksize, textureInformation);

			DeBlock(pSrc + (pixelByte * pixels * 1), 
				pDst + (pixelByte * blocksize),
				blocksize, textureInformation);

			DeBlock(pSrc + (pixelByte * pixels * 2),
				pDst + (pixelByte * textureInformation->width * blocksize),
				blocksize, textureInformation);

			DeBlock(pSrc + (pixelByte * pixels * 3), 
				pDst + (pixelByte * (blocksize + (textureInformation->width * blocksize))), 
				blocksize, textureInformation);
		}
		else
		{
			DeBlock(pSrc + (pixelByte * pixels * 0), 
				pDst + (pixelByte * textureInformation->width*blocksize),
				blocksize, textureInformation);

			DeBlock(pSrc + (pixelByte * pixels * 1),
				pDst + (pixelByte * (blocksize + (textureInformation->width * blocksize))), 
				blocksize, textureInformation);

			DeBlock(pSrc + (pixelByte * pixels * 2), pDst,       
				blocksize, textureInformation);

			DeBlock(pSrc + (pixelByte * pixels * 3), 
				pDst+(pixelByte * blocksize),
				blocksize, textureInformation);
		}
	}
	else
		trlMemCopy((void*)pDst, pSrc, pixelByte);

	return 1;
}

static s32 EnBlock(const u8* pSrc, u8* pDst, s32 blocksize, TextureInformation* textureInformation)
{    
	u32 pixelByte = GetPixelByte(textureInformation->format);

	if (blocksize != 1)
	{            
		s32 pixels;
		blocksize >>= 1;
		pixels = blocksize * blocksize;

		if (! textureInformation->yflip )
		{
			EnBlock(pSrc,
				pDst + (pixelByte * pixels * 0), 
				blocksize, textureInformation);

			EnBlock(pSrc + (pixelByte * blocksize),                  
				pDst + (pixelByte * pixels * 1),
				blocksize, textureInformation);

			EnBlock(pSrc + (pixelByte * blocksize * TEXTURE_BLOCK_SIZE),
				pDst + (pixelByte * pixels * 2),
				blocksize, textureInformation);

			EnBlock(pSrc + (pixelByte * blocksize * (TEXTURE_BLOCK_SIZE + 1)),
				pDst + (pixelByte * pixels * 3),
				blocksize, textureInformation);
		}
		else
		{
			EnBlock(pSrc,
				pDst + (pixelByte * pixels * 2),
				blocksize, textureInformation);

			EnBlock(pSrc + (pixelByte * blocksize),
				pDst + (pixelByte * pixels * 3),
				blocksize, textureInformation);

			EnBlock(pSrc + (pixelByte * blocksize * TEXTURE_BLOCK_SIZE),
				pDst + (pixelByte * pixels * 0),                    
				blocksize, textureInformation);

			EnBlock(pSrc + (pixelByte * blocksize * (TEXTURE_BLOCK_SIZE + 1)),
				pDst + (pixelByte * pixels * 1),
				blocksize, textureInformation);
		}

	}
	else
	{
		trlMemCopy((void*)pDst, pSrc, pixelByte);
	}

	return 1;
}

static s32 SwapColorComponents(TextureInformation* textureInformation)
{
	if ( textureInformation->format == GL_RGBA_NATIVE_DMP )
	{
		return convertFunctionArray[0](textureInformation);
	}
	else if ( textureInformation->format == GL_RGB_NATIVE_DMP )
	{
		return convertFunctionArray[1](textureInformation);
	}
	else if ( textureInformation->format == GL_LUMINANCE_ALPHA_NATIVE_DMP )
	{
		return convertFunctionArray[2](textureInformation);
	}
	else
	{
		return convertFunctionArray[3](textureInformation);
	}
}

static s32 ConvertFormat8888Function(TextureInformation* textureInformation)
{
	u8 tmp;
	u32 pixelByte = GetPixelByte(textureInformation->format);
	s32 total = static_cast<s32>(textureInformation->width * textureInformation->height * pixelByte);

	for (s32 i = 0; i< total; i+= pixelByte)
	{
		SWAP(textureInformation->src[i + 0], textureInformation->src[i + 3]);
		SWAP(textureInformation->src[i + 1], textureInformation->src[i + 2]);
	}

	return 1;
}

static s32 ConvertFormat888Function(TextureInformation* textureInformation)
{
	u8 tmp;
	u32 pixelByte = GetPixelByte(textureInformation->format);
	s32 total = static_cast<s32>(textureInformation->width * textureInformation->height * pixelByte);

	for (s32 i = 0; i < total; i += pixelByte)
	{
		SWAP(textureInformation->src[i + 0], textureInformation->src[i + 2]);
	}

	return 1;
}

static s32 ConvertFormat88Function(TextureInformation* textureInformation)
{
	u8 tmp;
	u32 pixelByte = GetPixelByte(textureInformation->format);
	s32 total = static_cast<s32>(textureInformation->width * textureInformation->height * pixelByte);

	for (s32 i = 0; i < total; i += pixelByte)
	{
		SWAP(textureInformation->src[i+0], textureInformation->src[i+1]);
	}

	return 1;
}

static s32 ConvertFormatXXXXFunction(TextureInformation* textureInformation)
{
	(void)textureInformation;    
	NN_TLOG_("Unsupported texture format.");
	NN_TASSERT_(0);

	return 1;
}
