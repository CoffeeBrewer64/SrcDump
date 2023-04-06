/**
 * @file agbGraphic.cpp
 * @author Chentian
 * @date 2009.11.24
 * @brief AGB Emulate For CTR - Graphic
 */
#include "agbGraphic.h"
#include "agbRegister.h"
#include "agbDMA.h"

/** @name Macro Define */
//@{
#define AGB_GRP_TICKS0				960								///< None H interval ticks
#define AGB_GRP_TICKS1				272								///< H interval ticks
#define AGB_GRP_VCOUNTMAX			228								///< V Count Max Value
#define AGB_GRP_BG0					0								///< Layer: BG0
#define AGB_GRP_BG1					1								///< Layer: BG1
#define AGB_GRP_BG2					2								///< Layer: BG2
#define AGB_GRP_BG3					3								///< Layer: BG3
#define AGB_GRP_OBJ					4								///< Layer: OBJ
#define AGB_GRP_LAYER_MAX			5								///< Layer: MAX
#define AGB_GRP_WIN0				1								///< Window: Window 0
#define AGB_GRP_WIN1				2								///< Window: Window 1
#define AGB_GRP_OBJWIN				4								///< Window: Object Window
#define AGB_GRP_TRANS				0x8000							///< Transparent Color
#define AGB_GRP_OBJMAX				128								///< OBJ Max Number
#define AGB_GRP_SX					240								///< Screen X Size
#define AGB_GRP_SY					160								///< Screen Y Size
#define AGB_GRP_VX					512								///< Virtual Screen X Size
#define AGB_GRP_VY					256								///< Virtual Screen Y Size
#define AGB_GRP_OBJ2D_XCHAR			32								///< 2D Mapping for OBJ Characters X Tile Count
#define AGB_GRP_R(x)				(x&0x1F)						///< Get R Value From Pixel
#define AGB_GRP_G(x)				((x>>5)&0x1F)					///< Get G Value From Pixel
#define AGB_GRP_B(x)				((x>>10)&0x1F)					///< Get B Value From Pixel
#define AGB_GRP_COLOR_MAX(x)		(((x) > 0x1F) ? 0x1F : (x))		///< Limit Color Max Value
#define AGB_GRP_COLOR_MIN(x)		(((x) < 0) ? 0 : (x))			///< Limit Color Min Value
#define AGB_GRP_COLOR_16TO32(x)		(((x&0x7C00)<<10) | ((x&0x03E0)<<5) | (x&0x001F))
#define AGB_GRP_BGRA2RGBA(v)		((((u16)(v&0x001F))<<11) | (((u16)(v&0x7C00))>>9) | ((v&0x03E0)<<1))
//@}

/** @name Global Variable */
//@{
s32					g_nAgbGrpTicks = 0;												///< LCD Ticks
u16*				g_pAgbGrpLineBuf[AGB_GRP_LAYER_MAX] = {0,0,0,0,0};				///< Line Buffer
u8*					g_pAgbGrpWinBuf = NULL;											///< Window Buffer
u16*				g_pAgbGrpBGPRAM = NULL;											///< BG Palette Address
u16*				g_pAgbGrpOBJPRAM = NULL;										///< OBJ Palette Address
s32					g_nAgbGrpBGCrdFlag[2] = {0,0};									///< BG Coordinate Register Change Flag
s32					g_nAgbGrpEVA = 0;												///< Color Special Effect Value: EVA
s32					g_nAgbGrpEVB = 0;												///< Color Special Effect Value: EVB
s32					g_nAgbGrpEVY = 0;												///< Color Special Effect Value: EVY
agbSGrpBGRSData		g_sAgbGrpBGRSData[2];											///< BG Rotation and Scaling Parameter
agbSGrpOAMData*		g_pAgbGrpOBJWin = NULL;											///< Object Window Data
s32					g_nAgbGrpOBJWinCount = 0;										///< Object Window Count
agbSRegWINCNT8*		g_pAgbGrpWINCnt[4] = {0,0,0,0};									///< The WININ and WINOUT Registers - 8 Bits
agbSGrpBGLayerInfo	g_sAgbGrpBGInfo[4];												///< BG Layer Info
agbSGrpBGLayerInfo*	g_pAgbGrpLayerInfo = NULL;										///< BG Layer Info Pointer
agbSGrpOBJLineInfo*	g_pAgbGrpOBJInfo = NULL;										///< OBJ Line Info
s32					g_nAgbGrpBGLayerChange = 1;										///< BG Layer Change Flag
s32					g_nAgbGrpOBJLayerChange = 1;									///< OBJ Layer Change Flag
agbSGrpOAMData*		g_pAgbGrpOAMData = NULL;										///< OAM Data
s32					g_nAgbGrpOAMCount = 0;											///< OAM Data Count
s32					g_nAgbGrpWinEnable = 0;											///< Window Enable Flag
const u32			g_nAgbGrpSrnTextSizeX[4] = {256, 512, 256, 512};				///< Text BG Screen Size X
const u32			g_nAgbGrpSrnTextSizeY[4] = {256, 256, 512, 512};				///< Text BG Screen Size Y
const u32			g_nAgbGrpSrnRotSize[4] = {128, 256, 512, 1024};					///< Rotation and Scaling BG Screen Size
const s32			g_nAgbGrpOBJSizeX[3][4] = {8,16,32,64, 16,32,32,64, 8,8,16,32};	///< Object X Size
const s32			g_nAgbGrpOBJSizeY[3][4] = {8,16,32,64, 8,8,16,32, 16,32,32,64};	///< Object Y Size
const s32			g_nAgbGrpOBJTileX[3][4] = {1,2,4,8, 2,4,4,8, 1,1,2,4};			///< Object X Tile Count
void				(*agbGrpRenderLinePointer[6])();								///< Render a Single Line Function Pointer
u16*				g_pAgbGrpRenderBuf = NULL;										///< Render Buffer
//@}

static u8 t_nGrpColorID;
/** @brief Get Pixel Color from Tile - 16 Colors */
inline u16 agbGrpGetPixelColor16(u16* pPal, u32 nX, u32 nY, u8* pTile)
{
	t_nGrpColorID = *(pTile + (nY<<2) + (nX>>1));
	if(nX&1)
		t_nGrpColorID >>= 4;
	else
		t_nGrpColorID &= 0x0F;
	if(t_nGrpColorID==0)
		return AGB_GRP_TRANS;
	return *(pPal + t_nGrpColorID);
}

/** @brief Get Pixel Color from Tile - 256 Colors */
inline u16 agbGrpGetPixelColor256(u16* pPal, u32 nX, u32 nY, u8* pTile)
{
	t_nGrpColorID = *(pTile + (nY<<3) + nX);
	if(t_nGrpColorID==0)
		return AGB_GRP_TRANS;
	return *(pPal + t_nGrpColorID);
}

/** @brief Array Layer Priority */
inline void agbGrpArrayLayer(u32 nLayer)
{
	g_sAgbGrpBGInfo[nLayer].nPrio = g_pAgbBGCnt[nLayer]->rPrio;
	g_sAgbGrpBGInfo[nLayer].nWin = 0;
	g_sAgbGrpBGInfo[nLayer].nEffect = 0;
	g_sAgbGrpBGInfo[nLayer].pNext = NULL;
	for(u32 i=0; i<4; ++i)
		if((g_pAgbGrpWINCnt[i]->rBG >> nLayer) & 0x01)
			g_sAgbGrpBGInfo[nLayer].nWin |= (1<<i);
	g_sAgbGrpBGInfo[nLayer].nEffect |= (g_pAgbBLDCnt->r1BG >> nLayer) & 0x01;
	g_sAgbGrpBGInfo[nLayer].nEffect |= ((g_pAgbBLDCnt->r2BG >> nLayer) & 0x01)<<1;

	if(g_pAgbGrpLayerInfo==NULL)
	{
		g_pAgbGrpLayerInfo = &g_sAgbGrpBGInfo[nLayer];
		return;
	}
	agbSGrpBGLayerInfo* pParentLayer = NULL;
	agbSGrpBGLayerInfo* pLayer = g_pAgbGrpLayerInfo;
	while(pLayer)
	{
		if(g_sAgbGrpBGInfo[nLayer].nPrio < pLayer->nPrio)
			break;
		if(g_sAgbGrpBGInfo[nLayer].nPrio == pLayer->nPrio)
			if(g_sAgbGrpBGInfo[nLayer].nLayer < pLayer->nLayer)
				break;
		pParentLayer = pLayer;
		pLayer = pLayer->pNext;
	};
	g_sAgbGrpBGInfo[nLayer].pNext = pLayer;
	if(pParentLayer)
		pParentLayer->pNext = &g_sAgbGrpBGInfo[nLayer];
	else
		g_pAgbGrpLayerInfo = &g_sAgbGrpBGInfo[nLayer];
}

/** @brief Render a Single Line By Text BG */
inline void agbGrpRenderBGText(u32 nLayer)
{
	u8* pCharBase = &g_pAgbVRAM[g_pAgbBGCnt[nLayer]->rChrBaseBlock * 0x4000];
	u16* pSrnBase = (u16*)&g_pAgbVRAM[g_pAgbBGCnt[nLayer]->rSrnBaseBlock * 0x800];
	u32 nSizeX = g_nAgbGrpSrnTextSizeX[g_pAgbBGCnt[nLayer]->rSrnSize];
	u32 nSizeY = g_nAgbGrpSrnTextSizeY[g_pAgbBGCnt[nLayer]->rSrnSize];
	u32 nX = g_pAgbBGHofs[nLayer]->rOffset & (nSizeX - 1);
	u32 nY = g_pAgbBGVofs[nLayer]->rOffset + g_pAgbVCount->rVCountVal;

	// Mosaic
//	s32 nMX = 1;
	s32 nMY = 0;
	if(g_pAgbBGCnt[nLayer]->rMosaic)
	{
//		nMX = g_pAgbMosaic->rBGHSize + 1;
		nMY = g_pAgbVCount->rVCountVal % (g_pAgbMosaic->rBGVSize+1);
	}
	nY = (nY - nMY) & (nSizeY - 1);
//	nY &= (nSizeY - 1);

	// Render Line
	if(nY >= 256)
		pSrnBase += 1024 * (nSizeX >> 8) + ((nY-256)>>3) * 32;
	else
		pSrnBase += (nY>>3) * 32;

	u16* pSrnLine = pSrnBase;
	if(nX >= 256)
		pSrnLine += 1024 + ((nX-256)>>3);
	else
		pSrnLine += nX>>3;

	u32 nTileX = nX & 0x07;
	u32 nTileY0 = nY & 0x07;
//	u32	nTileY = ((*pSrnLine)&0x0800) ? (7 - nTileY0) : nTileY0;

	if(g_pAgbBGCnt[nLayer]->rColorMode)	// 256 Colors
	{
		//u16* pLineBuf = g_pAgbGrpLineBuf[nLayer];
		//for(s32 x=0, m=0; x<AGB_GRP_SX; ++x, --m)
		//{
		//	if(m)
		//		pLineBuf[x] = pLineBuf[x-1];
		//	else
		//	{
		//		pLineBuf[x] = agbGrpGetPixelColor256(g_pAgbGrpBGPRAM, (((*pSrnLine)&0x0400) ? 7-nTileX : nTileX), nTileY, pCharBase + ((*pSrnLine)&0x3FF)*64);
		//		m = nMX;
		//	}

		//	++nTileX;
		//	if(nTileX==8)
		//	{
		//		nTileX = 0;
		//		if((nX+x+1) == nSizeX)
		//			pSrnLine = pSrnBase;
		//		else if((nX+x+1) == 256)
		//			pSrnLine = pSrnBase + 1024;
		//		else
		//			++pSrnLine;
		//		nTileY = ((*pSrnLine)&0x0800) ? (7 - nTileY0) : nTileY0;
		//	}
		//}

		u8* pPixel;
		u32 nSrnData = 0xFFFFFFFF;
		u16* pLineBuf = g_pAgbGrpLineBuf[nLayer] - (s32)nTileX;
		s32 x = 0;

		while(1)
		{
			if(nSrnData == *(u16*)pSrnLine)
			{
				trlMemMove(pLineBuf, pLineBuf-8, 16);
				pLineBuf += 8;
			}
			else
			{
				nSrnData = *pSrnLine;
				if((*pSrnLine)&0x0800)
					pPixel = (pCharBase + (nSrnData&0x3FF)*64) + (7 - nTileY0) * 8;
				else
					pPixel = (pCharBase + (nSrnData&0x3FF)*64) + nTileY0 * 8;

				if(nSrnData&0x0400)
				{
					pPixel += 8;
					for(u32 n=0; n<8; ++n, --pPixel)
					{
						if(*pPixel)
							*pLineBuf = *(g_pAgbGrpBGPRAM + *pPixel);
						else
							*pLineBuf = AGB_GRP_TRANS;
						++pLineBuf;
					}
				}
				else
				{
					for(u32 n=0; n<8; ++n, ++pPixel)
					{
						if(*pPixel)
							*pLineBuf = *(g_pAgbGrpBGPRAM + *pPixel);
						else
							*pLineBuf = AGB_GRP_TRANS;
						++pLineBuf;
					}
				}
			}

			x += 8-nTileX;
			if(x >= AGB_GRP_SX)
				break;
			if((nX+x) == nSizeX)
				pSrnLine = pSrnBase;
			else if((nX+x) == 256)
				pSrnLine = pSrnBase + 1024;
			else
				++pSrnLine;
			nTileX = 0;
		};

	}
	else								// 16 Colors
	{
		//u16* pLineBuf = g_pAgbGrpLineBuf[nLayer];
		//u16* pPal = g_pAgbGrpBGPRAM + (((*pSrnLine)&0xF000)>>8);
		//u8* pChar = pCharBase + ((*pSrnLine)&0x3FF)*32;
		//for(s32 x=0, m=0; x<AGB_GRP_SX; ++x, --m)
		//{
		//	if(m)
		//		pLineBuf[x] = pLineBuf[x-1];
		//	else
		//	{
		//		pLineBuf[x] = agbGrpGetPixelColor16(pPal, ((*pSrnLine & 0x0400) ? 7-nTileX : nTileX), nTileY, pChar);
		//		m = nMX;
		//	}

		//	++nTileX;
		//	if(nTileX==8)
		//	{
		//		nTileX = 0;
		//		if((nX+x+1) == nSizeX)
		//			pSrnLine = pSrnBase;
		//		else if((nX+x+1) == 256)
		//			pSrnLine = pSrnBase + 1024;
		//		else
		//			++pSrnLine;
		//		nTileY = (*pSrnLine & 0x0800) ? (7 - nTileY0) : nTileY0;
		//		pPal = g_pAgbGrpBGPRAM + (((*pSrnLine)&0xF000)>>8);
		//		pChar = pCharBase + ((*pSrnLine)&0x3FF)*32;
		//	}
		//}

		u32 nPixel;
		u32 nSrnData = 0xFFFFFFFF;
		u16* pLineBuf = g_pAgbGrpLineBuf[nLayer] - (s32)nTileX;
		s32 x = 0;

		while(1)
		{
			if(nSrnData == *(u16*)pSrnLine)
			{
				trlMemMove(pLineBuf, pLineBuf-8, 16);
				pLineBuf += 8;
			}
			else
			{
				nSrnData = *pSrnLine;
				u16* pPal = g_pAgbGrpBGPRAM + ((nSrnData&0xF000)>>8);
				if((*pSrnLine)&0x0800)
					nPixel = *(((u32*)(pCharBase + (nSrnData&0x3FF)*32)) + 7 - nTileY0);
				else
					nPixel = *(((u32*)(pCharBase + (nSrnData&0x3FF)*32)) + nTileY0);

				if(nSrnData&0x0400)
				{
					for(u32 n=0; n<8; ++n, nPixel <<= 4)
					{
						if(nPixel&0xF0000000)
							*pLineBuf = *(pPal + (nPixel>>28));
						else
							*pLineBuf = AGB_GRP_TRANS;
						++pLineBuf;
					}
				}
				else
				{
					for(u32 n=0; n<8; ++n, nPixel >>= 4)
					{
						if(nPixel&0x0F)
							*pLineBuf = *(pPal + (nPixel&0x0F));
						else
							*pLineBuf = AGB_GRP_TRANS;
						++pLineBuf;
					}
				}
			}

			x += 8-nTileX;
			if(x >= AGB_GRP_SX)
				break;
			if((nX+x) == nSizeX)
				pSrnLine = pSrnBase;
			else if((nX+x) == 256)
				pSrnLine = pSrnBase + 1024;
			else
				++pSrnLine;
			nTileX = 0;
		};
	}

	// Array Layer Priority
	if(g_nAgbGrpBGLayerChange)
		agbGrpArrayLayer(nLayer);
}

/** @brief A 16 Bits Signed Fixed-Point Number Transform To A s32 Number */
inline s32 agbGrpF16toS32(u16 nFixed)
{
	if(nFixed & 0x8000)
		return nFixed | 0xFFFF8000;
	else
		return nFixed;
}

/** @brief Rotation and Scaling BG */
inline void agbGrpRotationAndScalingBG(u32 nLayer, s32 &nRX, s32 &nRY, s32 &nMX)
{
	// Rotation and Scaling
	if(g_pAgbVCount->rVCountVal==0)
		g_nAgbGrpBGCrdFlag[nLayer] = 0x3;
	if(g_nAgbGrpBGCrdFlag[nLayer] & 0x1)
		g_sAgbGrpBGRSData[nLayer].nCX = g_sAgbGrpBGRSData[nLayer].nX;
	else
		g_sAgbGrpBGRSData[nLayer].nCX += g_sAgbGrpBGRSData[nLayer].nPB;

	if(g_nAgbGrpBGCrdFlag[nLayer] & 0x2)
		g_sAgbGrpBGRSData[nLayer].nCY = g_sAgbGrpBGRSData[nLayer].nY;
	else
		g_sAgbGrpBGRSData[nLayer].nCY += g_sAgbGrpBGRSData[nLayer].nPD;
	g_nAgbGrpBGCrdFlag[nLayer] = 0;

	nRX = g_sAgbGrpBGRSData[nLayer].nCX;
	nRY = g_sAgbGrpBGRSData[nLayer].nCY;

	// Mosaic
	nMX = 1;
	if(g_pAgbBGCnt[nLayer+2]->rMosaic)
	{
		int nV = g_pAgbVCount->rVCountVal % (g_pAgbMosaic->rBGVSize + 1);
		nRX -= nV * g_sAgbGrpBGRSData[nLayer].nPB;
		nRY -= nV * g_sAgbGrpBGRSData[nLayer].nPD;
		nMX = g_pAgbMosaic->rBGHSize + 1;
	}
}

/** @brief Render a Single Line By Rotation and Scaling Text BG */
inline void agbGrpRenderBGTextRot(u32 nLayer)
{
	u8* pCharBase = &g_pAgbVRAM[g_pAgbBGCnt[nLayer]->rChrBaseBlock * 0x4000];
	u8* pSrnBase = &g_pAgbVRAM[g_pAgbBGCnt[nLayer]->rSrnBaseBlock * 0x800];
	s32 nSize = g_nAgbGrpSrnRotSize[g_pAgbBGCnt[nLayer]->rSrnSize];

	s32 nRX, nRY, nMX;
	agbGrpRotationAndScalingBG(nLayer-2, nRX, nRY, nMX);

	// Render Line
	for(s32 x=0, m=0; x<AGB_GRP_SX; ++x, --m)
	{
		if(m)
			g_pAgbGrpLineBuf[nLayer][x] = g_pAgbGrpLineBuf[nLayer][x-1];
		else
		{
			s32 nX = nRX >> 8;
			s32 nY = nRY >> 8;
			if(g_pAgbBGCnt[nLayer]->rAreaOverflow)
			{
				if(nX < 0 || nX >= nSize)
				{
					nX %= nSize;
					if(nX < 0)
						nX += nSize;
				}
				if(nY < 0 ||  nY >= nSize)
				{
					nY %= nSize;
					if(nY < 0)
						nY += nSize;
				}
				u8 nTile = *(pSrnBase + (nX>>3) + (nY>>3)*(nSize>>3));
				g_pAgbGrpLineBuf[nLayer][x] = agbGrpGetPixelColor256(g_pAgbGrpBGPRAM, (nX & 7), (nY & 7), pCharBase + nTile*64);
			}
			else
			{
				if((nX < 0) || (nY < 0) || (nX >= nSize) || (nY >= nSize))
					g_pAgbGrpLineBuf[nLayer][x] = AGB_GRP_TRANS;
				else
				{
					u8 nTile = *(pSrnBase + (nX>>3) + (nY>>3)*(nSize>>3));
					g_pAgbGrpLineBuf[nLayer][x] = agbGrpGetPixelColor256(g_pAgbGrpBGPRAM, (nX & 7), (nY & 7), pCharBase + nTile*64);
				}
			}
			m = nMX;
		}
		nRX += g_sAgbGrpBGRSData[nLayer].nPA;
		nRY += g_sAgbGrpBGRSData[nLayer].nPC;
	}

	// Array Layer Priority
	if(g_nAgbGrpBGLayerChange)
		agbGrpArrayLayer(nLayer);
}

/** @brief Render a Single Line By 32,768 colors Bitmap BG */
inline void agbGrpRenderBG16BitBitmap(u32 nFrame)
{
	u16* pSrnBase;
	s32 nSizeX, nSizeY;
	if(nFrame==1)
	{
		pSrnBase = (u16*)g_pAgbVRAM;
		nSizeX = 240;
		nSizeY = 160;
	}
	else
	{
		pSrnBase = (u16*)(g_pAgbDispCnt->rFrameID ? &g_pAgbVRAM[0xA000] : &g_pAgbVRAM[0x0000]);
		nSizeX = 160;
		nSizeY = 128;
	}

	s32 nRX, nRY, nMX;
	agbGrpRotationAndScalingBG(0, nRX, nRY, nMX);

	// Render Line
	for(s32 x=0, m=0; x<AGB_GRP_SX; ++x, --m)
	{
		if(m)
			g_pAgbGrpLineBuf[2][x] = g_pAgbGrpLineBuf[2][x-1];
		else
		{
			s32 nX = nRX >> 8;
			s32 nY = nRY >> 8;
			if(nX < 0 || nY < 0 || nX >= nSizeX || nY >= nSizeY)
				g_pAgbGrpLineBuf[2][x] = AGB_GRP_TRANS;
			else
				g_pAgbGrpLineBuf[2][x] = pSrnBase[nY * nSizeX + nX];
			m = nMX;
		}
		nRX += g_sAgbGrpBGRSData[0].nPA;
		nRY += g_sAgbGrpBGRSData[0].nPC;
	}

	// Array Layer Priority
	if(g_nAgbGrpBGLayerChange)
		agbGrpArrayLayer(2);
}

/** @brief Render a Single Line By 256 colors Bitmap BG */
inline void agbGrpRenderBG8BitBitmap()
{
	u8* pSrnBase = g_pAgbDispCnt->rFrameID ? &g_pAgbVRAM[0xA000] : &g_pAgbVRAM[0x0000];

	// Rotation And Scaling
	s32 nRX, nRY, nMX;
	agbGrpRotationAndScalingBG(0, nRX, nRY, nMX);

	// Render Line
	for(s32 x=0, m=0; x<AGB_GRP_SX; ++x, --m)
	{
		if(m)
			g_pAgbGrpLineBuf[2][x] = g_pAgbGrpLineBuf[2][x-1];
		else
		{
			s32 nX = nRX >> 8;
			s32 nY = nRY >> 8;
			if(nX < 0 || nY < 0 || nX >= 240 || nY >= 160)
				g_pAgbGrpLineBuf[2][x] = AGB_GRP_TRANS;
			else
				g_pAgbGrpLineBuf[2][x] = g_pAgbGrpBGPRAM[pSrnBase[nY * 240 + nX]];
			m = nMX;
		}
		nRX += g_sAgbGrpBGRSData[0].nPA;
		nRY += g_sAgbGrpBGRSData[0].nPC;
	}

	// Array Layer Priority
	if(g_nAgbGrpBGLayerChange)
		agbGrpArrayLayer(2);
}

/** @brief Update a Object Pixel */
inline void agbGrpOBJUpdatePixel(agbSGrpOAMData* pData, s32 x, u16 nColor)
{
	if(nColor == AGB_GRP_TRANS)
		return;
	if(pData->nPrio >= g_pAgbGrpOBJInfo[x].nPrio)		/*! Unfinished: When orders of OBJ number and OBJ priority are reversed, the display is not right. */
		return;
	g_pAgbGrpLineBuf[AGB_GRP_OBJ][x] = nColor;
	g_pAgbGrpOBJInfo[x].nPrio = pData->nPrio;
	g_pAgbGrpOBJInfo[x].nMode = pData->nMode;
}

/** @brief Render a Single Line by Objects */
inline void agbGrpRenderOBJ()
{
//	s32 nRenderPixMax = g_pAgbDispCnt->rOBJH ? 954 : 1226;		// OBJ Display Capability on a Single Line	/*! Unfinished */
	memset(g_pAgbGrpOBJInfo, 0xFF, AGB_GRP_SX*2);

	agbSGrpOAMData* pData = g_pAgbGrpOAMData;
    for(s32 n=0; n < g_nAgbGrpOAMCount; ++n, ++pData)
	{
		if((g_pAgbVCount->rVCountVal >= pData->nBottom) || (g_pAgbVCount->rVCountVal < pData->nTop))
			continue;
		pData->nY = g_pAgbVCount->rVCountVal - pData->nSY;

		// Process Mosaic
		s32 nMX = 1;
		if(pData->bMosaic)
		{
			nMX = g_pAgbMosaic->rOBJHSize + 1;
			pData->nY -= pData->nY % (g_pAgbMosaic->rOBJVSize+1);
		}

		if(pData->bRot)	// Rotation/Scaling OBJ
		{
			s32 nRX = pData->nRX + pData->nY * pData->nDMX;
			s32 nRY = pData->nRY + pData->nY * pData->nDMY;

			// Render Line
			u16 nColor;
			u32 nChar;
			s32 nTX, nTY;
			for(s32 x=pData->nLeft, m=0; x<pData->nRight; ++x, --m)
			{
				nRX += pData->nDX;
				nRY += pData->nDY;
				if(m)
					agbGrpOBJUpdatePixel(pData, x, g_pAgbGrpLineBuf[AGB_GRP_OBJ][x-1]);
				else
				{
					m = nMX;
					nTX = nRX >> 8;
					nTY = nRY >> 8;
					if(nTX < 0 || nTY < 0 || nTX >= pData->nSizeX || nTY >= pData->nSizeY)
					{
						agbGrpOBJUpdatePixel(pData, x, AGB_GRP_TRANS);
						continue;
					}

					nChar = (nTY >> 3) * pData->nCharBase + (nTX >> 3);

					// Get Pixel Color
					if(pData->nColor)	// 256 Colors
						nColor = agbGrpGetPixelColor256(g_pAgbGrpOBJPRAM, nTX & 0x7, nTY & 0x7, pData->pTileBase + nChar * 64);
					else				// 16 Colors
						nColor = agbGrpGetPixelColor16(g_pAgbGrpOBJPRAM + (pData->nPal<<4), nTX & 0x7, nTY & 0x7, pData->pTileBase + nChar * 32);
					// Update Pixel
					agbGrpOBJUpdatePixel(pData, x, nColor);
				}
			}
		}
		else
		{
			// Process V-Flip
			if(pData->bVFlip)
				pData->nY = pData->nSizeY - pData->nY - 1;

			u32 nCharBase = (pData->nY >> 3) * pData->nCharBase;

			// Render Line
			u32 nTileX;
			u32 nTileY = pData->nY & 0x7;
			u16 nColor;
			u32 nChar;
			s32 nTX = pData->nX;
			for(s32 x=pData->nLeft, m=0; x<pData->nRight; ++x, ++nTX, --m)
			{
				if(m)
					agbGrpOBJUpdatePixel(pData, x, g_pAgbGrpLineBuf[AGB_GRP_OBJ][x-1]);
				else
				{
					m = nMX;
					// Process H-Flip
					if(pData->bHFlip)
					{
						nChar = nCharBase + ((pData->nSizeX - nTX - 1) >> 3);
						nTileX = (pData->nSizeX - nTX - 1) & 0x7;
					}
					else
					{
						nChar = nCharBase + (nTX >> 3);
						nTileX = nTX & 0x7;
					}
					// Get Pixel Color
					if(pData->nColor)	// 256 Colors
						nColor = agbGrpGetPixelColor256(g_pAgbGrpOBJPRAM, nTileX, nTileY, pData->pTileBase + nChar * 64);
					else				// 16 Colors
						nColor = agbGrpGetPixelColor16(g_pAgbGrpOBJPRAM + (pData->nPal<<4), nTileX, nTileY, pData->pTileBase + nChar * 32);
					// Update Pixel
					agbGrpOBJUpdatePixel(pData, x, nColor);
				}
			}
		}
	}
}

static u32 g_nAgbGrpAlphaColor1;
static u32 g_nAgbGrpAlphaColor2;
/** @brief Color Special Effects - Alpha Blending */
inline void agbGrpAlphaBlend(u16* pColor1, u16* pColor2)
{
	g_nAgbGrpAlphaColor1 = AGB_GRP_COLOR_16TO32(*pColor1);
	g_nAgbGrpAlphaColor2 = AGB_GRP_COLOR_16TO32(*pColor2);
	g_nAgbGrpAlphaColor1 = g_nAgbGrpAlphaColor1 * g_nAgbGrpEVA + g_nAgbGrpAlphaColor2 * g_nAgbGrpEVB;
	if(g_nAgbGrpAlphaColor1 & 0x00000200)
		g_nAgbGrpAlphaColor2 = 0x001F;
	else
		g_nAgbGrpAlphaColor2 = (g_nAgbGrpAlphaColor1 & 0x0000001F0) >> 4;

	if(g_nAgbGrpAlphaColor1 & 0x00080000)
		g_nAgbGrpAlphaColor2 |= 0x03E0;
	else
		g_nAgbGrpAlphaColor2 |= (g_nAgbGrpAlphaColor1 & 0x0007C000) >> 9;

	if(g_nAgbGrpAlphaColor1 & 0x20000000)
		g_nAgbGrpAlphaColor2 |= 0x7C00;
	else
		g_nAgbGrpAlphaColor2 |= (g_nAgbGrpAlphaColor1 & 0x1F000000) >> 14;
	*pColor1 = g_nAgbGrpAlphaColor2;
}

/** @brief Color Special Effects - Brightness Increase */
inline void agbGrpBrightnessIncrease(u16* pColor)
{
	register s32 nTemp = AGB_GRP_R(*pColor);
	nTemp += ((31 - nTemp) * g_nAgbGrpEVY) >> 4;
	register s32 nResult = AGB_GRP_COLOR_MAX(nTemp);

	nTemp = AGB_GRP_G(*pColor);
	nTemp += ((31 - nTemp) * g_nAgbGrpEVY) >> 4;
	nResult |= AGB_GRP_COLOR_MAX(nTemp) << 5;

	nTemp = AGB_GRP_B(*pColor);
	nTemp += ((31 - nTemp) * g_nAgbGrpEVY) >> 4;
	*pColor = nResult | (AGB_GRP_COLOR_MAX(nTemp) << 10);
}

/** @brief Color Special Effects - Brightness Decrease */
inline void agbGrpBrightnessDecrease(u16* pColor)
{
	register s32 nTemp = AGB_GRP_R(*pColor);
	nTemp -= (nTemp * g_nAgbGrpEVY) >> 4;
	register s32 nResult = AGB_GRP_COLOR_MIN(nTemp);

	nTemp = AGB_GRP_G(*pColor);
	nTemp -= (nTemp * g_nAgbGrpEVY) >> 4;
	nResult |= AGB_GRP_COLOR_MIN(nTemp) << 5;

	nTemp = AGB_GRP_B(*pColor);
	nTemp -= (nTemp * g_nAgbGrpEVY) >> 4;
	*pColor = nResult | (AGB_GRP_COLOR_MIN(nTemp) << 10);
}

/** @brief Render a Single Line By Mode 0 */
inline void agbGrpRenderLineMode0()
{
	if(g_pAgbDispCnt->rBG0)
		agbGrpRenderBGText(AGB_GRP_BG0);
	if(g_pAgbDispCnt->rBG1)
		agbGrpRenderBGText(AGB_GRP_BG1);
	if(g_pAgbDispCnt->rBG2)
		agbGrpRenderBGText(AGB_GRP_BG2);
	if(g_pAgbDispCnt->rBG3)
		agbGrpRenderBGText(AGB_GRP_BG3);
	if(g_pAgbDispCnt->rOBJ)
		agbGrpRenderOBJ();
}

/** @brief Render a Single Line By Mode 1 */
inline void agbGrpRenderLineMode1()
{
	if(g_pAgbDispCnt->rBG0)
		agbGrpRenderBGText(AGB_GRP_BG0);
	if(g_pAgbDispCnt->rBG1)
		agbGrpRenderBGText(AGB_GRP_BG1);
	if(g_pAgbDispCnt->rBG2)
		agbGrpRenderBGTextRot(AGB_GRP_BG2);
	if(g_pAgbDispCnt->rOBJ)
		agbGrpRenderOBJ();
}

/** @brief Render a Single Line By Mode 2 */
inline void agbGrpRenderLineMode2()
{
	if(g_pAgbDispCnt->rBG2)
		agbGrpRenderBGTextRot(AGB_GRP_BG2);
	if(g_pAgbDispCnt->rBG3)
		agbGrpRenderBGTextRot(AGB_GRP_BG3);
	if(g_pAgbDispCnt->rOBJ)
		agbGrpRenderOBJ();
}

/** @brief Render a Single Line By Mode 3 */
inline void agbGrpRenderLineMode3()
{
	if(g_pAgbDispCnt->rBG2)
		agbGrpRenderBG16BitBitmap(1);
	if(g_pAgbDispCnt->rOBJ)
		agbGrpRenderOBJ();
}

/** @brief Render a Single Line By Mode 4 */
inline void agbGrpRenderLineMode4()
{
	if(g_pAgbDispCnt->rBG2)
		agbGrpRenderBG8BitBitmap();
	if(g_pAgbDispCnt->rOBJ)
		agbGrpRenderOBJ();
}

/** @brief Render a Single Line By Mode 5 */
inline void agbGrpRenderLineMode5()
{
	if(g_pAgbDispCnt->rBG2)
		agbGrpRenderBG16BitBitmap(2);
	if(g_pAgbDispCnt->rOBJ)
		agbGrpRenderOBJ();
}

/** @brief Get Window Buffer */
inline void agbGrpGetWindowBuffer(u32 nWindow)
{
	if((g_pAgbVCount->rVCountVal < g_pAgbWINV[nWindow]->rLeftUp) || (g_pAgbVCount->rVCountVal >= g_pAgbWINV[nWindow]->rRightLow))
		return;
	if(g_pAgbWINH[nWindow]->rLeftUp < g_pAgbWINH[nWindow]->rRightLow)
	{
		for(s32 x = g_pAgbWINH[nWindow]->rLeftUp; x<g_pAgbWINH[nWindow]->rRightLow; ++x)
			g_pAgbGrpWinBuf[x] |= (1<<nWindow);
	}
	else if(g_pAgbWINH[nWindow]->rLeftUp > g_pAgbWINH[nWindow]->rRightLow)
	{
		for(s32 x=0; x<g_pAgbWINH[nWindow]->rRightLow; ++x)
			g_pAgbGrpWinBuf[x] |= (1<<nWindow);
		for(s32 x = g_pAgbWINH[nWindow]->rLeftUp; x<AGB_GRP_SX; ++x)
			g_pAgbGrpWinBuf[x] |= (1<<nWindow);
	}
}

/** @brief Get OBJ Window Pixel */
inline void agbGrpGetOBJWindowPixel(agbSGrpOAMData* pData, u32 nChar, u32 nTileX, u32 nTileY, s32 nX)
{
	pData->pTile = pData->pTileBase;
	if(pData->nColor)	// 256 Colors
	{
		pData->pTile += nChar * 64;
		if(*(pData->pTile + nTileY*8 + nTileX))
			g_pAgbGrpWinBuf[nX] |= AGB_GRP_OBJWIN;
	}
	else				// 16 Colors
	{
		pData->pTile += nChar * 32;
		u8 nTemp = *(pData->pTile + nTileY*4 + (nTileX>>1));
		if(nTileX&1)
		{
			if(nTemp>>4)
				g_pAgbGrpWinBuf[nX] |= AGB_GRP_OBJWIN;
		}
		else
		{
			if(nTemp&0x0F)
				g_pAgbGrpWinBuf[nX] |= AGB_GRP_OBJWIN;
		}
	}
}

/** @brief Get OBJ Window Buffer */
inline void agbGrpGetOBJWindowBuffer()
{
	agbSGrpOAMData* pData = g_pAgbGrpOBJWin;
	for(s32 n=0; n<g_nAgbGrpOBJWinCount; ++n, ++pData)
	{
		pData->nY = g_pAgbVCount->rVCountVal;
		if((pData->nY >= pData->nBottom) || (pData->nY < pData->nTop))
			continue;
		pData->nY -= pData->nSY;

		// Process Mosaic
		if(pData->bMosaic)
			pData->nY -= pData->nY % (g_pAgbMosaic->rOBJVSize+1);

		u32 nChar;
		if(pData->bRot)	// Rotation/Scaling OBJ
		{
			s32 nRX = pData->nRX + pData->nY * pData->nDMX;
			s32 nRY = pData->nRY + pData->nY * pData->nDMY;

			// Render Line
			s32 nTX, nTY;
			for(s32 x=pData->nLeft, m=0; x<pData->nRight; ++x, --m)
			{
				nRX += pData->nDX;
				nRY += pData->nDY;
				nTX = nRX >> 8;
				nTY = nRY >> 8;
				if(nTX < 0 || nTY < 0 || nTX >= pData->nSizeX || nTY >= pData->nSizeY)
					continue;
				nChar = (nTY >> 3) * pData->nCharBase + (nTX >> 3);
				agbGrpGetOBJWindowPixel(pData, nChar, nTX & 0x7, nTY & 0x7, x);
			}
		}
		else
		{
			// Process V-Flip
			if(pData->bVFlip)
				pData->nY = pData->nSizeY - pData->nY - 1;
			u32 nCharBase = (pData->nY >> 3) * pData->nCharBase;

			// Render Line
			u32 nTileX;
			u32 nTileY = pData->nY & 0x7;
			s32 nTX = pData->nX;
			for(s32 x=pData->nLeft; x<pData->nRight; ++x, ++nTX)
			{
				// Process H-Flip
				if(pData->bHFlip)
				{
					nChar = nCharBase + ((pData->nSizeX - nTX - 1) >> 3);
					nTileX = (pData->nSizeX - nTX - 1) & 0x7;
				}
				else
				{
					nChar = nCharBase + (nTX >> 3);
					nTileX = nTX & 0x7;
				}
				agbGrpGetOBJWindowPixel(pData, nChar, nTileX, nTileY, x);
			}
		}

		// Process Mosaic
		if(pData->bMosaic)
		{
			s32 nMX = g_pAgbMosaic->rOBJHSize + 1;
			u8 nWinFlag = 0;
			for(s32 x=pData->nLeft, m=0; x<pData->nRight; ++x, --m)
			{
				if(m)
					g_pAgbGrpWinBuf[x] |= nWinFlag;
				else
				{
					m = nMX;
					nWinFlag = g_pAgbGrpWinBuf[x] & AGB_GRP_OBJWIN;
				}
			}
		}
	}
}

/** @brief Process Alpha Blend by OBJ */
inline u32 agbGrpProcessAlphaBlendOBJ(agbSGrpBGLayerInfo* pLayer, s32 x)
{
	while(pLayer)
	{
		if(pLayer->pLineBuf[x] != AGB_GRP_TRANS)
		{
			if(pLayer->nEffect & 0x02)
				agbGrpAlphaBlend(g_pAgbGrpRenderBuf + x, &pLayer->pLineBuf[x]);
			return 1;
		}
		pLayer = pLayer->pNext;
	};
	if(g_pAgbBLDCnt->r2BD)
	{
		agbGrpAlphaBlend(g_pAgbGrpRenderBuf + x, &g_pAgbGrpBGPRAM[0]);
		return 1;
	}
	return 0;
}

/** @brief Process Alpha Blend by BG */
inline void agbGrpProcessAlphaBlendBG(agbSGrpBGLayerInfo* pLayer, s32 x)
{
	if(g_pAgbGrpOBJInfo[x].nPrio == 0xFF)
	{
		while(pLayer)
		{
			if(pLayer->pLineBuf[x] != AGB_GRP_TRANS)
			{
				if(pLayer->nEffect & 0x02)
					agbGrpAlphaBlend(g_pAgbGrpRenderBuf + x, &pLayer->pLineBuf[x]);
				return;
			}
			pLayer = pLayer->pNext;
		};
	}
	else
	{
		while(1)
		{
			if(pLayer == NULL)
			{
				if(g_pAgbBLDCnt->r2OBJ && (g_pAgbGrpOBJInfo[x].nPrio != 0xFF))
				{
					agbGrpAlphaBlend(g_pAgbGrpRenderBuf + x, &g_pAgbGrpLineBuf[AGB_GRP_OBJ][x]);
					return;
				}
				break;
			}
			if(pLayer->nPrio >= g_pAgbGrpOBJInfo[x].nPrio)
			{
				if(g_pAgbBLDCnt->r2OBJ)
					agbGrpAlphaBlend(g_pAgbGrpRenderBuf + x, &g_pAgbGrpLineBuf[AGB_GRP_OBJ][x]);
				return;
			}
			if(pLayer->pLineBuf[x] != AGB_GRP_TRANS)
			{
				if(pLayer->nEffect & 0x02)
					agbGrpAlphaBlend(g_pAgbGrpRenderBuf + x, &pLayer->pLineBuf[x]);
				return;
			}
			pLayer = pLayer->pNext;
		};
	}
	if(g_pAgbBLDCnt->r2BD)
		agbGrpAlphaBlend(g_pAgbGrpRenderBuf + x, &g_pAgbGrpBGPRAM[0]);
}

/** @brief Process a Pixel by Semi-transparent OBJ */
inline void agbGrpProcessOBJSemi(agbSGrpBGLayerInfo* pLayer, s32 x)
{
	if(g_pAgbBLDCnt->rColorSE < 2)
		agbGrpProcessAlphaBlendOBJ(pLayer, x);
	else if(g_pAgbBLDCnt->r1OBJ == 1)
	{
		if(agbGrpProcessAlphaBlendOBJ(pLayer, x))
			return;
		if(g_pAgbBLDCnt->rColorSE == 2)
			agbGrpBrightnessIncrease(g_pAgbGrpRenderBuf + x);
		else
			agbGrpBrightnessDecrease(g_pAgbGrpRenderBuf + x);
	}
}

/** @brief Process a Pixel by Normal OBJ */
inline void agbGrpProcessOBJNormal(agbSGrpBGLayerInfo* pLayer, s32 x)
{
	switch(g_pAgbBLDCnt->rColorSE)
	{
	case 1:		// Alpha blending
		agbGrpProcessAlphaBlendOBJ(pLayer, x);
		break;
	case 2:		// Brightness Increase
		agbGrpBrightnessIncrease(g_pAgbGrpRenderBuf + x);
		break;
	case 3:		// Brightness Decrease
		agbGrpBrightnessDecrease(g_pAgbGrpRenderBuf + x);
		break;
	}
}

/** @brief Process a Pixel by OBJ */
inline u32 agbGrpProcessOBJWin(agbSGrpBGLayerInfo* pLayer, s32 x)
{
	// Process Window
	if(g_pAgbGrpWinBuf[x])	// In Window
	{
		for(u32 i=0, j=1; i<3; ++i, j<<=1)
		{
			if(g_pAgbGrpWinBuf[x] & j)
			{
				if(g_pAgbGrpWINCnt[i]->rOBJ==0)
				{
					g_pAgbGrpOBJInfo[x].nPrio = 0xFF;
					return 0;
				}
				g_pAgbGrpRenderBuf[x] = g_pAgbGrpLineBuf[AGB_GRP_OBJ][x];
				if(g_pAgbGrpWINCnt[i]->rSE == 0)
					return 1;
				break;
			}
		}
	}
	else				// Out Window
	{
		if(g_pAgbWINOUT->r0OBJ==0)
		{
			g_pAgbGrpOBJInfo[x].nPrio = 0xFF;
			return 0;
		}
		g_pAgbGrpRenderBuf[x] = g_pAgbGrpLineBuf[AGB_GRP_OBJ][x];
		if(g_pAgbWINOUT->r0SE == 0)
			return 1;
	}
	g_pAgbGrpRenderBuf[x] = g_pAgbGrpLineBuf[AGB_GRP_OBJ][x];
	if(g_pAgbGrpOBJInfo[x].nMode == 0x1)
		agbGrpProcessOBJSemi(pLayer, x);
	else if(g_pAgbBLDCnt->r1OBJ)
		agbGrpProcessOBJNormal(pLayer, x);
	return 1;
}

/** @brief Process a Pixel by BG */
inline void agbGrpProcessBG(agbSGrpBGLayerInfo* pLayer, s32 x)
{
	// Process Color Special Effects
	switch(g_pAgbBLDCnt->rColorSE)
	{
	case 1:		// Alpha blending
		agbGrpProcessAlphaBlendBG(pLayer->pNext, x);
		return;
	case 2:		// Brightness Increase
		agbGrpBrightnessIncrease(g_pAgbGrpRenderBuf + x);
		return;
	case 3:		// Brightness Decrease
		agbGrpBrightnessDecrease(g_pAgbGrpRenderBuf + x);
		return;
	}
}

/** @brief Process a Pixel by BG */
inline u32 agbGrpProcessBGWin(agbSGrpBGLayerInfo* pLayer, s32 x)
{
	// Process Window
	if(g_pAgbGrpWinBuf[x])	// In Window
	{
		for(u32 i=0, j=1; i<3; ++i, j<<=1)
		{
			if(g_pAgbGrpWinBuf[x] & j)
			{
				if((pLayer->nWin & j) == 0)
					return 0;
				g_pAgbGrpRenderBuf[x] = pLayer->pLineBuf[x];
				if(g_pAgbGrpWINCnt[i]->rSE == 0)
					return 1;
				break;
			}
		}
	}
	else				// Out Window
	{
		if((pLayer->nWin & 8) == 0)
			return 0;
		g_pAgbGrpRenderBuf[x] = pLayer->pLineBuf[x];
		if(g_pAgbWINOUT->r0SE == 0)
			return 1;
	}
	g_pAgbGrpRenderBuf[x] = pLayer->pLineBuf[x];
	if(pLayer->nEffect & 0x1)
		agbGrpProcessBG(pLayer, x);
	return 1;
}

/** @brief Process a Pixel by Backdrop */
inline void agbGrpProcessBD(s32 x)
{
	g_pAgbGrpRenderBuf[x] = g_pAgbGrpBGPRAM[0];
	if(!g_pAgbBLDCnt->r1BD)
		return;
	switch(g_pAgbBLDCnt->rColorSE)
	{
	case 2:		// Brightness Increase
		agbGrpBrightnessIncrease(g_pAgbGrpRenderBuf + x);
		return;
	case 3:		// Brightness Decrease
		agbGrpBrightnessDecrease(g_pAgbGrpRenderBuf + x);
		return;
	}
}

/** @brief Process OAM Data */
inline void agbGrpProcessOAM()
{
	g_nAgbGrpOAMCount = 0;
	g_nAgbGrpOBJWinCount = 0;
	agbSGrpOAMData* pData;
    for(s32 n=0, i=0; n < AGB_GRP_OBJMAX; ++n, i+=4)
	{
		agbSGrpOamAttr0* pAttr0 = &((agbSGrpOamAttr0*)g_pAgbOAM)[i];
		if(pAttr0->rDouble == 1 && pAttr0->rRot == 0)
			continue;
		if(pAttr0->rShape == 3)
			continue;
		if(pAttr0->rMode == 3)
			continue;
		if(pAttr0->rMode == 2 && g_pAgbDispCnt->rOBJWIN == 0)
			continue;

		if(pAttr0->rMode == 2)
			pData = &g_pAgbGrpOBJWin[g_nAgbGrpOBJWinCount];
		else
			pData = &g_pAgbGrpOAMData[g_nAgbGrpOAMCount];

		agbSGrpOamAttr1* pAttr1 = &((agbSGrpOamAttr1*)g_pAgbOAM)[i+1];
		agbSGrpOamAttr2* pAttr2 = &((agbSGrpOamAttr2*)g_pAgbOAM)[i+2];

		pData->nSizeX = g_nAgbGrpOBJSizeX[pAttr0->rShape][pAttr1->rSize];
		pData->nSizeY = g_nAgbGrpOBJSizeY[pAttr0->rShape][pAttr1->rSize];
		pData->nFieldX = pData->nSizeX;
		pData->nFieldY = pData->nSizeY;
		pData->nSX = pAttr1->rX;
		pData->nSY = pAttr0->rY;
		// Process Double
		if(pAttr0->rRot && pAttr0->rDouble)
		{
			pData->nFieldX <<= 1;
			pData->nFieldY <<= 1;
		}

		// Clipping
		if((pData->nSX + pData->nFieldX) > AGB_GRP_VX)
			pData->nSX -= AGB_GRP_VX;
		else if(pData->nSX >= AGB_GRP_SX)
			continue;
		if((pData->nSY + pData->nFieldY) > AGB_GRP_VY)
			pData->nSY -= AGB_GRP_VY;
		else if(pData->nSY >= AGB_GRP_SY)
			continue;

		// Get Rect
		pData->nRight = pData->nSX + pData->nFieldX;
		pData->nBottom = pData->nSY + pData->nFieldY;
		if(pData->nSX < 0)
		{
			pData->nX = -pData->nSX;
			pData->nLeft = 0;
		}
		else
		{
			pData->nX = 0;
			pData->nLeft = pData->nSX;
			if(pData->nRight > AGB_GRP_SX)
				pData->nRight = AGB_GRP_SX;
		}

		if(pData->nSY < 0)
			pData->nTop = 0;
		else
		{
			pData->nTop = pData->nSY;
			if(pData->nBottom > AGB_GRP_SY)
				pData->nBottom = AGB_GRP_SY;
		}

		pData->bMosaic = (pAttr0->rMosaic && pAttr0->rMode!=2);
		pData->bRot = pAttr0->rRot;
		pData->nPrio = pAttr2->rPrio;
		pData->nMode = pAttr0->rMode;
		pData->nPal = pAttr2->rPal;
		pData->nColor = pAttr0->rColor;
		if(g_pAgbDispCnt->rOBJMap)	// 1D Mode
			pData->nCharBase = g_nAgbGrpOBJTileX[pAttr0->rShape][pAttr1->rSize];
		else						// 2D Mode
			pData->nCharBase = (AGB_GRP_OBJ2D_XCHAR >> pAttr0->rColor);
		pData->pTileBase = &g_pAgbVRAM[0x10000] + pAttr2->rChar * 32;

		if(pData->bRot)	// Rotation/Scaling OBJ
		{
			// Process Rotation & Scaling
			u32 nRotPara = ((agbSGrpOamAttr1Rot*)pAttr1)->rRotPara * 16;
			pData->nDX = agbGrpF16toS32(((u16*)g_pAgbOAM)[nRotPara+3]);
			pData->nDMX = agbGrpF16toS32(((u16*)g_pAgbOAM)[nRotPara+7]);
			pData->nDY = agbGrpF16toS32(((u16*)g_pAgbOAM)[nRotPara+11]);
			pData->nDMY = agbGrpF16toS32(((u16*)g_pAgbOAM)[nRotPara+15]);
			pData->nRX = ((pData->nSizeX) << 7) + (pData->nX - 1 - (pData->nFieldX >> 1))*pData->nDX - (pData->nFieldY >> 1) * pData->nDMX;
			pData->nRY = ((pData->nSizeY) << 7) + (pData->nX - 1 - (pData->nFieldX >> 1))*pData->nDY - (pData->nFieldY >> 1) * pData->nDMY;
		}
		else				// Normal OBJ
		{
			pData->bHFlip = pAttr1->rHFlip;
			pData->bVFlip = pAttr1->rVFlip;
		}

		if(pAttr0->rMode == 2)
			++g_nAgbGrpOBJWinCount;
		else
			++g_nAgbGrpOAMCount;
	}
}

/** @brief Mix Layers */
inline void agbGrpMixLayers()
{
	// Mix Layers
	if(g_pAgbGrpLayerInfo == NULL)
	{
		if(g_pAgbDispCnt->rOBJ == 0)
		{
			// Process BD Line Buffer
			for(s32 x=0; x<AGB_GRP_SX; ++x)
				agbGrpProcessBD(x);
		}
		else
		{
			for(s32 x=0; x<AGB_GRP_SX; ++x)
			{
				// Process OBJ Line Buffer
				if(g_pAgbGrpOBJInfo[x].nPrio != 0xFF)
				{
					g_pAgbGrpRenderBuf[x] = g_pAgbGrpLineBuf[AGB_GRP_OBJ][x];
					if(g_pAgbGrpOBJInfo[x].nMode == 0x1)
						agbGrpProcessOBJSemi(NULL, x);
					else if(g_pAgbBLDCnt->r1OBJ)					
						agbGrpProcessOBJNormal(NULL, x);
				}
				else
					agbGrpProcessBD(x);
			}
		}
	}
	else
	{
		agbSGrpBGLayerInfo* pLayer;
		if(g_pAgbDispCnt->rOBJ == 1)
		{
			for(s32 x=0; x<AGB_GRP_SX; ++x)
			{
				pLayer = g_pAgbGrpLayerInfo;

				if(g_pAgbGrpOBJInfo[x].nPrio == 0xFF)
				{
					while(1)
					{
						// Process BG Line Buffer
						if(pLayer->pLineBuf[x] != AGB_GRP_TRANS)
						{
							g_pAgbGrpRenderBuf[x] = pLayer->pLineBuf[x];
							if(pLayer->nEffect & 0x1)
							{
								// Process Color Special Effects
								switch(g_pAgbBLDCnt->rColorSE)
								{
								case 1:		// Alpha blending
									agbGrpProcessAlphaBlendBG(pLayer->pNext, x);
									break;
								case 2:		// Brightness Increase
									agbGrpBrightnessIncrease(g_pAgbGrpRenderBuf + x);
									break;
								case 3:		// Brightness Decrease
									agbGrpBrightnessDecrease(g_pAgbGrpRenderBuf + x);
									break;
								}
							}
//								agbGrpProcessBG(pLayer, x);
							break;
						}
						if(pLayer->pNext == NULL)
						{
							agbGrpProcessBD(x);
							break;
						}
						pLayer = pLayer->pNext;
					};
				}
				else
				{
					while(1)
					{
						// Process OBJ Line Buffer
						if(pLayer->nPrio >= g_pAgbGrpOBJInfo[x].nPrio)
						{
							g_pAgbGrpRenderBuf[x] = g_pAgbGrpLineBuf[AGB_GRP_OBJ][x];
							if(g_pAgbGrpOBJInfo[x].nMode == 0x1)
								agbGrpProcessOBJSemi(pLayer, x);
							else if(g_pAgbBLDCnt->r1OBJ)					
								agbGrpProcessOBJNormal(pLayer, x);
							break;
						}

						// Process BG Line Buffer
						if(pLayer->pLineBuf[x] != AGB_GRP_TRANS)
						{
							g_pAgbGrpRenderBuf[x] = pLayer->pLineBuf[x];
							if(pLayer->nEffect & 0x1)
							{
								// Process Color Special Effects
								switch(g_pAgbBLDCnt->rColorSE)
								{
								case 1:		// Alpha blending
									agbGrpProcessAlphaBlendBG(pLayer->pNext, x);
									break;
								case 2:		// Brightness Increase
									agbGrpBrightnessIncrease(g_pAgbGrpRenderBuf + x);
									break;
								case 3:		// Brightness Decrease
									agbGrpBrightnessDecrease(g_pAgbGrpRenderBuf + x);
									break;
								}
							}
//								agbGrpProcessBG(pLayer, x);
							break;
						}
						if(pLayer->pNext == NULL)
						{
							g_pAgbGrpRenderBuf[x] = g_pAgbGrpLineBuf[AGB_GRP_OBJ][x];
							if(g_pAgbGrpOBJInfo[x].nMode == 0x1)
								agbGrpProcessOBJSemi(NULL, x);
							else if(g_pAgbBLDCnt->r1OBJ)					
								agbGrpProcessOBJNormal(NULL, x);
							break;
						}
						pLayer = pLayer->pNext;
					};
				}
			}
		}
		else
		{
			for(s32 x=0; x<AGB_GRP_SX; ++x)
			{
				pLayer = g_pAgbGrpLayerInfo;
				while(1)
				{
					// Process BG Line Buffer
					if(pLayer->pLineBuf[x] != AGB_GRP_TRANS)
					{
						g_pAgbGrpRenderBuf[x] = pLayer->pLineBuf[x];
						if(pLayer->nEffect & 0x1)
							agbGrpProcessBG(pLayer, x);
						break;
					}
					if(pLayer->pNext == NULL)
					{
						// Process BD Pixel
						agbGrpProcessBD(x);
						break;
					}
					pLayer = pLayer->pNext;
				};
			}
		}
	}
}

/** @brief Mix Layers With Window */
inline void agbGrpMixLayersWin()
{
	// Mix Layers
	if(g_pAgbGrpLayerInfo == NULL)
	{
		if(g_pAgbDispCnt->rOBJ == 0)
		{
			// Process BD Line Buffer
			for(s32 x=0; x<AGB_GRP_SX; ++x)
				agbGrpProcessBD(x);
		}
		else
		{
			for(s32 x=0; x<AGB_GRP_SX; ++x)
			{
				// Process OBJ Line Buffer
				if(g_pAgbGrpOBJInfo[x].nPrio != 0xFF)
				{
					if(agbGrpProcessOBJWin(NULL, x))
						continue;
				}
				// Process BD Pixel
				agbGrpProcessBD(x);
			}
		}
	}
	else
	{
		agbSGrpBGLayerInfo* pLayer;
		if(g_pAgbDispCnt->rOBJ == 1)
		{
			for(s32 x=0; x<AGB_GRP_SX; ++x)
			{
				pLayer = g_pAgbGrpLayerInfo;
				while(1)
				{
					// Process OBJ Line Buffer
					if(pLayer->nPrio >= g_pAgbGrpOBJInfo[x].nPrio)
					{
						if(agbGrpProcessOBJWin(pLayer, x))
							break;
					}

					// Process BG Line Buffer
					if(pLayer->pLineBuf[x] != AGB_GRP_TRANS)
					{
						g_pAgbGrpRenderBuf[x] = pLayer->pLineBuf[x];
						if(pLayer->nEffect & 0x1)
							if(agbGrpProcessBGWin(pLayer, x))
								break;
					}
					if(pLayer->pNext == NULL)
					{
						if(g_pAgbGrpOBJInfo[x].nPrio != 0xFF)
						{
							if(agbGrpProcessOBJWin(NULL, x))
								break;
						}
						else
							agbGrpProcessBD(x);
						break;
					}
					pLayer = pLayer->pNext;
				};
			}
		}
		else
		{
			for(s32 x=0; x<AGB_GRP_SX; ++x)
			{
				pLayer = g_pAgbGrpLayerInfo;
				while(1)
				{
					// Process BG Line Buffer
					if(pLayer->pLineBuf[x] != AGB_GRP_TRANS)
					{
						if(agbGrpProcessBGWin(pLayer, x))
							break;
					}
					if(pLayer->pNext == NULL)
					{
						// Process BD Pixel
						agbGrpProcessBD(x);
						break;
					}
					pLayer = pLayer->pNext;
				};
			}
		}
	}
}

//static u64 g_nTime123 = 0;
//static u64 g_nTime124 = 0;
//static u32 g_nCount = 0;
/** @brief Render a Single Line */
inline void agbGrpRenderLine()
{
//////////////////////////////////
//TRL_TIME_BEGIN(123);
//////////////////////////////////
	g_pAgbGrpRenderBuf = &((u16*)g_pAgbEmuBuf->pScreenBuf)[g_pAgbVCount->rVCountVal * g_pAgbEmuBuf->nTexWidth];

	// Process Forced Blank
	if(g_pAgbDispCnt->rForcedBlank)
	{
		for(s32 x=0; x<AGB_GRP_SX; ++x)
#ifdef TRL_PLATFORM_PC
			g_pAgbGrpRenderBuf[x] = 0x7FFF;
#endif
#ifdef TRL_PLATFORM_CTR
			g_pAgbGrpRenderBuf[x] = 0xFFFE;
#endif
		return;
	}

	// Process OAM
	if(g_nAgbGrpOBJLayerChange)
	{
		g_nAgbGrpOBJLayerChange = 0;
		agbGrpProcessOAM();
	}

	// Process Window Buffer
	if(g_nAgbGrpWinEnable)
	{
		memset(g_pAgbGrpWinBuf, 0, AGB_GRP_SX);
		if(g_pAgbDispCnt->rWIN0)
			agbGrpGetWindowBuffer(0);
		if(g_pAgbDispCnt->rWIN1)
			agbGrpGetWindowBuffer(1);
		if(g_pAgbDispCnt->rOBJWIN)
			agbGrpGetOBJWindowBuffer();
	}

	// Array BG Layer
	if(g_nAgbGrpBGLayerChange)
		g_pAgbGrpLayerInfo = NULL;

	// Render Layers
	agbGrpRenderLinePointer[g_pAgbDispCnt->rBGMode]();

	g_nAgbGrpBGLayerChange = 0;

////////////////////////////////////
//g_nTime123 += TRL_TIME_GET64(123);
//TRL_TIME_BEGIN(124);
////////////////////////////////////
	if(g_nAgbGrpWinEnable)
		agbGrpMixLayersWin();
	else
		agbGrpMixLayers();

#ifdef TRL_PLATFORM_CTR
	for(s32 x=0; x<AGB_GRP_SX; ++x)
		g_pAgbGrpRenderBuf[x] = AGB_GRP_BGRA2RGBA(g_pAgbGrpRenderBuf[x]);
#endif

////////////////////////////////////
//g_nTime124 += TRL_TIME_GET64(124);
//if(!g_pAgbVCount->rVCountVal)
//{
//	++g_nCount;
//	if(g_nCount == 64)
//	{
//		NN_LOG("agbGrpRenderLine: T1: %d T2: %d Sum: %d\n", (u32)(g_nTime123>>6), (u32)(g_nTime124>>6), (u32)((g_nTime124+g_nTime123)>>6));
//		g_nCount = 0;
//		g_nTime123 = 0;
//		g_nTime124 = 0;
//	}
//}
////////////////////////////////////
}

/** @brief V Counter Match */
inline void agbGrpVCounterMatch()
{
	if(g_pAgbVCount->rVCountVal == g_pAgbDispStat->rVCount)
	{
		g_pAgbDispStat->rVCountEva = 1;
		if(g_pAgbDispStat->rVCountMatch)
			g_pAgbIF->rVCounter = 1;
	}
	else
		g_pAgbDispStat->rVCountEva = 0;
}

/** @brief Update Ticks */
void agbGrpUpdateTicks(u32 nTicks)
{
	g_nAgbGrpTicks -= nTicks;
	if(g_nAgbGrpTicks > 0)
		return;

	if(g_pAgbDispStat->rHBlank)	// Outside H-blank interval
	{
		g_pAgbDispStat->rHBlank = 0;
		g_nAgbGrpTicks += AGB_GRP_TICKS0;
		++g_pAgbVCount->rVCountVal;
		if(g_pAgbVCount->rVCountVal == AGB_GRP_SY)	// Outside V-blank interval
		{
			g_pAgbDispStat->rVBlank = 1;
			if(g_pAgbDispStat->rVBlankInt)
				g_pAgbIF->rVBlank = 1;
			agbDmaTransferVBlank();
			g_nAgbBreakFlag = 1;
		}
		if(g_pAgbDMACnt[3]->rStartup == 0x03)		// Synchronize with display and start
			agbDmaTransferSynchronize();
		agbGrpVCounterMatch();
	}
	else						// Start H-blank interval
	{
		if(g_pAgbDispStat->rVBlank == 0)			// Outside V-blank interval
		{
			agbGrpRenderLine();
			agbDmaTransferHBlank();
		}

		g_pAgbDispStat->rHBlank = 1;
		g_nAgbGrpTicks += AGB_GRP_TICKS1;
		if(g_pAgbDispStat->rHBlankInt)
			g_pAgbIF->rHBlank = 1;
	}
	// Check V Count Max
	if(g_pAgbVCount->rVCountVal == AGB_GRP_VCOUNTMAX)
	{
		g_pAgbDispStat->rVBlank = 0;
		g_pAgbDispStat->rHBlank = 0;
		g_pAgbVCount->rVCountVal = 0;
		agbGrpVCounterMatch();
	}
}

/** @brief Reset Graphic */
void agbGrpReset()
{
	g_nAgbGrpTicks = AGB_GRP_TICKS0;
	g_nAgbGrpOAMCount = 0;
	g_nAgbGrpWinEnable = 0;
	g_nAgbGrpOBJWinCount = 0;
	g_nAgbGrpEVA = 0;
	g_nAgbGrpEVB = 0;
	g_nAgbGrpEVY = 0;
	memset(g_sAgbGrpBGRSData, 0, sizeof(agbSGrpBGRSData)*2);
}

/** @brief Initialize Memory */
void agbGrpInit()
{
	g_pAgbGrpBGPRAM = (u16*)g_pAgbPRAM;
	g_pAgbGrpOBJPRAM = (u16*)(&g_pAgbPRAM[0x200]);
	g_pAgbGrpWINCnt[0] = (agbSRegWINCNT8*)(&g_pAgbREG[0x048]);
	g_pAgbGrpWINCnt[1] = (agbSRegWINCNT8*)(&g_pAgbREG[0x049]);
	g_pAgbGrpWINCnt[2] = (agbSRegWINCNT8*)(&g_pAgbREG[0x04B]);
	g_pAgbGrpWINCnt[3] = (agbSRegWINCNT8*)(&g_pAgbREG[0x04A]);

	for(u32 n=0; n<AGB_GRP_LAYER_MAX; ++n)
		g_pAgbGrpLineBuf[n] = ((u16*)trlMemAlloc(AGB_GRP_SX*2+32)) + 8;
	g_pAgbGrpWinBuf = (u8*)trlMemAlloc(AGB_GRP_SX);
	g_pAgbGrpOBJWin = (agbSGrpOAMData*)trlMemAlloc(AGB_GRP_OBJMAX*sizeof(agbSGrpOAMData));

	g_pAgbGrpOBJInfo = (agbSGrpOBJLineInfo*)trlMemAlloc(AGB_GRP_SX*sizeof(agbSGrpOBJLineInfo));
	for(u32 n=0; n<4; ++n)
	{
		g_sAgbGrpBGInfo[n].nLayer = n;
		g_sAgbGrpBGInfo[n].pLineBuf = g_pAgbGrpLineBuf[n];
	}

	agbGrpRenderLinePointer[0] = agbGrpRenderLineMode0;
	agbGrpRenderLinePointer[1] = agbGrpRenderLineMode1;
	agbGrpRenderLinePointer[2] = agbGrpRenderLineMode2;
	agbGrpRenderLinePointer[3] = agbGrpRenderLineMode3;
	agbGrpRenderLinePointer[4] = agbGrpRenderLineMode4;
	agbGrpRenderLinePointer[5] = agbGrpRenderLineMode5;

	g_pAgbGrpOAMData = (agbSGrpOAMData*)trlMemAlloc(AGB_GRP_OBJMAX*sizeof(agbSGrpOAMData));

	agbGrpReset();
}
