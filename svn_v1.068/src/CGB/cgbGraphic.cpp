/**
 * @file cgbGraphic.cpp
 * @author Chentian
 * @date 2009.11.24
 * @brief CGB Emulate For CTR - Graphic
 */
#include "cgbGraphic.h"
#include "cgbRegister.h"
#include "cgbDMA.h"

/** @name Macro Define */
//@{
#define CGB_GRP_TICKS0				51								///< H-Blank Ticks
#define CGB_GRP_TICKS1				114								///< One Line Ticks
#define CGB_GRP_TICKS2				20								///< Searching OAM-RAM Ticks
#define CGB_GRP_TICKS3				43								///< Transfering Data to LCD Driver Ticks
#define CGB_GRP_VCOUNTMAX			154								///< V Count Max Value
#define CGB_GRP_BG_SIZE				256								///< BG Size
#define CGB_GRP_BG_MASK				255								///< BG Size Mask
#define CGB_GRP_BG_TILE				32								///< BG Tile
#define CGB_GRP_SX					160								///< Screen X Size
#define CGB_GRP_SY					144								///< Screen Y Size
#define CGB_GRP_OBJLINEMAX			10								///< OBJ Max Number in One Line
#define CGB_GRP_OBJMAX				40								///< OBJ Max Number
#define CGB_GRP_OAMMAX				160								///< OBJ Max Number
#define CGB_GRP_BGCOLOR				0x03							///< BG Color Flag
#define CGB_GRP_BGPRIO				0x04							///< BG Priority Flag
#define CGB_GRP_OBJINFO				0x10							///< OBJ Info Flag
#define CGB_GRP_OBJPRIO				0x80							///< OBJ Priority Flag
#define CGB_GRP_COLORLCD			0xFFFF							///< LCD Color (0xFFFF)
//@}

/** @name Global Variable */
//@{
void				(*cgbGrpRenderLine)();								///< Render a Single Line
s32					g_nCgbGrpTicks = 0;									///< LCD Ticks
s32					g_nCgbGrpTick0 = CGB_GRP_TICKS0;					///< H-Blank Ticks
s32					g_nCgbGrpTick1 = CGB_GRP_TICKS1;					///< One Line Ticks
s32					g_nCgbGrpTick2 = CGB_GRP_TICKS2;					///< Searching OAM-RAM Ticks
s32					g_nCgbGrpTick3 = CGB_GRP_TICKS3;					///< Transfering Data to LCD Driver Ticks
u8*					g_pCgbGrpLineInfo = NULL;							///< Line Pixel Info
u16					g_nCgbGrpDMGColor[14];								///< DMG Color
u16					g_nCgbGrpBGPalReal[8][4];							///< BG Real Palette Data
u16					g_nCgbGrpOBJPalReal[8][4];							///< OBJ Real Palette Data
u16					g_nCgbGrpBGPal[8][4];								///< BG Palette Data
u16					g_nCgbGrpOBJPal[8][4];								///< OBJ Palette Data
s32					g_nCgbGrpWinY = 0;									///< Window Line Value
cgbSGrpOAMInfo*		g_pCgbGrpOAMInfo = NULL;							///< OAM Info
u32					g_nCgbGrpOAMInfoCount = 0;							///< OAM Info Count
u8*					g_pCgbGrpBGSrnDataBase = NULL;						///< BG Screen Data Base Address
u8*					g_pCgbGrpBGAtrDataBase = NULL;						///< BG Attribute Data Base Address
u8*					g_pCgbGrpWinSrnDataBase = NULL;						///< Window Screen Data Base Address
u8*					g_pCgbGrpWinAtrDataBase = NULL;						///< Window Attribute Data Base Address
u16*				g_pCgbGrpBGWinTileDataBase = NULL;					///< BG & Window Tile Data Base Address
u8					g_nCgbGrpBGWinTileOffset = 0;						///< BG & Window Tile Offset
s32					g_nCgbGrpOBJSize = 8;								///< OBJ Size
u32					g_bCgbGrpOAMChange = 1;								///< OAM Change Flag
u16*				g_pCgbGrpRenderBuf = NULL;							///< Render Buffer
u8*					g_pCgbGrpCGBFlipData = NULL;						///< CGB BG Flip X Data
u32					g_bCgbGrpLCDEnable = 1;								///< LCD Enable Flag
u32					g_bCgbGrpVBlankMode = 0;							///< VBlank Mode Flag
u32					g_bCgbGrpRenderTime = 0;							///< Render Time
u32					g_bCgbGrpWinEnable = 0;								///< Last Frame Window Stat
u32					g_bCgbGrpLogo = 0;									///< Show Nintendo(R) Logo Flag
u32					g_bCgbGrpObjLineLimit = 1;							///< Obj Line Limit Flag
u32					g_nCgbGrpLCDCIntFlag = 0;							///< LCDC Interrupt Stat Flag
u32					g_nCgbGrpLCDCInt = 0;								///< LCDC Interrupt Stat
u32					g_nCgbGrpLCDOnDelay = 0;							///< LCD On Delay Frame
s32					g_nCgbGrpVBlankDelay = 1;							///< VBlank Delay Ticks
trlSEmuShellResume	g_sCgbGrpSaveData[CGB_GRP_SAVEDATA];				///< Graphic Save Data
//@}

/** @brief Render a Single Line By BG & Window - DMG */
void cgbGrpRenderBGWIN_DMG(u32 nX, u32 nY, u8* pSrnDataBase, u32 nSX, u32 nEX)
{
	u8* pSrnData = pSrnDataBase + (nY>>3) * CGB_GRP_BG_TILE;
	u8* pSrnLine = pSrnData + (nX>>3);
	u16* pChrData = g_pCgbGrpBGWinTileDataBase + (nY & 0x07);
	u16* pPal = g_nCgbGrpBGPal[0];

	u8* pInfo = &g_pCgbGrpLineInfo[nSX];
	u16* pBuf = &g_pCgbGrpRenderBuf[nSX];
	if(nX & 0x07)
	{
		u32 nTileX = nX & 0x07;
		u16 nChar = *(pChrData + ((u8)(*pSrnLine + g_nCgbGrpBGWinTileOffset)) * 8);
		do{
			u8 nColorID = ((nChar >> (7-nTileX)) & 0x1) | ((nChar >> (14-nTileX)) & 0x2);
			*pInfo++ = nColorID;
			*pBuf++ = pPal[nColorID];
			++nTileX;
			++nSX;
			if(nTileX==8)
				break;
		}while(nSX<nEX);
		++pSrnLine;
	}
	if(nSX ==nEX)
		return;

#if	BG_RENDER_REPEAT_FAST
	u8 nCachepSrnLine=0xFF;
	bool bCached=false;
#endif

	do{
		if((nX+nSX) == CGB_GRP_BG_SIZE)
			pSrnLine = pSrnData;
		u16 nChar = *(pChrData + ((u8)(*pSrnLine + g_nCgbGrpBGWinTileOffset)) * 8);

		if((nSX+8) > nEX)
		{
			u32 nTileX = 0;
			do{
				u8 nColorID = ((nChar >> (7-nTileX)) & 0x1) | ((nChar >> (14-nTileX)) & 0x2);
				*pInfo++ = nColorID;
				*pBuf++ = pPal[nColorID];
				++nTileX;
				++nSX;
			}while(nSX<nEX);
		}
		else
		{
#if	BG_RENDER_REPEAT_FAST
			if(bCached){
				if(nCachepSrnLine==*pSrnLine){
					*(u32*)(pBuf)=*(u32*)(pBuf-8);
					*(u32*)(pBuf+2)=*(u32*)(pBuf-6);
					*(u32*)(pBuf+4)=*(u32*)(pBuf-4);
					*(u32*)(pBuf+6)=*(u32*)(pBuf-2);
					*(u32*)(pInfo)=*(u32*)(pInfo-8);
					*(u32*)(pInfo+4)=*(u32*)(pInfo-4);
					pBuf+=8;
					pInfo+=8;
					
					nSX += 8;
					++pSrnLine;
					if(nSX<nEX)
						continue;
					else
						break;
				}
			}
			nCachepSrnLine=*pSrnLine;
			bCached=true;
#endif
			u32 nColorID = ((nChar >> 7) & 0x1) | ((nChar >> 14) & 0x2);
			u32 nInfo = nColorID;
			u32 nColor = pPal[nColorID];
			nColorID = ((nChar >> 6) & 0x1) | ((nChar >> 13) & 0x2);
			nInfo += nColorID << 8;
			nColor += pPal[nColorID] << 16;
			*((u32*)pBuf) = nColor;
			pBuf+=2;

			nColorID = ((nChar >> 5) & 0x1) | ((nChar >> 12) & 0x2);
			nInfo += nColorID << 16;
			nColor = pPal[nColorID];
			nColorID = ((nChar >> 4) & 0x1) | ((nChar >> 11) & 0x2);
			nInfo += nColorID << 24;
			nColor += pPal[nColorID] << 16;
			*((u32*)pBuf) = nColor;
			pBuf+=2;
			*((u32*)pInfo) = nInfo;
			pInfo+=4;

			nColorID = ((nChar >> 3) & 0x1) | ((nChar >> 10) & 0x2);
			nInfo = nColorID;
			nColor = pPal[nColorID];
			nColorID = ((nChar >> 2) & 0x1) | ((nChar >> 9) & 0x2);
			nInfo += nColorID << 8;
			nColor += pPal[nColorID] << 16;
			*((u32*)pBuf) = nColor;
			pBuf+=2;

			nColorID = ((nChar >> 1) & 0x1) | ((nChar >> 8) & 0x2);
			nInfo += nColorID << 16;
			nColor = pPal[nColorID];
			nColorID = (nChar & 0x1) | ((nChar >> 7) & 0x2);
			nInfo += nColorID << 24;
			nColor += pPal[nColorID] << 16;
			*((u32*)pBuf) = nColor;
			pBuf+=2;
			*((u32*)pInfo) = nInfo;
			pInfo+=4;

			nSX += 8;
			++pSrnLine;
		}
	}while(nSX<nEX);
}

//#ifdef TRL_PLATFORM_CTR
/** @brief Render a Single Line By BG & Window - DMG */
//asm void cgbGrpRenderBGWIN_DMG(u32, u32, u8*, u32, u32)
//{
//	IMPORT g_nCgbGrpBGWinTileOffset
//	IMPORT g_nCgbGrpBGPal
//
//	PUSH     {r4-r11,lr}
//	LSR      r12,r1,#3
//	ADD      r6,r2,r12,LSL #5
//	AND      lr,r1,#7
//	LDR      r1,[pc,#204]
//	ADD      r2,r6,r0,LSR #3
//	LDR      r9,[pc,#200]
//	LDRB     r12,[r2,#0]
//	LDRB     r4,[r1,#0]
//	LDR      r5,[r1,#0x34]
//	ADD      r12,r12,r4
//	AND      r12,r12,#0xff
//	ADD      r7,r5,lr,LSL #1
//	ADD      r12,r7,r12,LSL #4
//	LDRH     lr,[r12,#0]
//	LDR      r12,[r1,#0x1c]
//	LDR      r1,[r1,#0x40]
//	ADD      r12,r12,r3
//	ADD      r4,r1,r3,LSL #2
//	AND      r1,r0,#7
//	B        Lable2
//Lable0
//	RSB      r5,r1,#7
//	RSB      r8,r1,#0xe
//	LSR      r5,lr,r5
//	LSR      r8,lr,r8
//	AND      r5,r5,#1
//	AND      r8,r8,#2
//	LDRB     r10,[r12,#0]
//	ORR      r5,r5,r8
//	MOV      r8,r12
//	ADD      r11,r9,r5,LSL #1
//	ORR      r5,r5,r10
//	STRB     r5,[r8,#0]
//	LDR      r8,[r4],#4
//	LDRH     r5,[r11,#0]
//	CMP      r1,#7
//	ADD      r12,r12,#1
//	ADDNE    r1,r1,#1
//	STRH     r5,[r8,#0]
//	BNE      Lable1
//	ADD      lr,r0,r3
//	LDR      r5,[pc,#56]
//	CMP      lr,#0xff
//	ADDNE    r2,r2,#1
//	MOVEQ    r2,r6
//	LDRB     r5,[r5,#0]
//	LDRB     lr,[r2,#0]
//	MOV      r1,#0
//	ADD      lr,lr,r5
//	AND      lr,lr,#0xff
//	ADD      lr,r7,lr,LSL #4
//	LDRH     lr,[lr,#0]
//Lable1
//	ADD      r3,r3,#1
//Lable2
//	LDR      r5,[sp,#0x24]
//	CMP      r3,r5
//	BCC      Lable0
//	POP      {r4-r11,pc}
//}
//#endif

//inline u16 cgbGrpMotionBlur(u16 nX, u16 nY)
//{
//	u32 nB1 = (nX>>1) & 0x1F;
//	u32 nG1 = (nX>>6) & 0x1F;
//	u32 nR1 = (nX>>11) & 0x1F;
//	u32 nB2 = (nY>>1) & 0x1F;
//	u32 nG2 = (nY>>6) & 0x1F;
//	u32 nR2 = (nY>>11) & 0x1F;
//	if(nR1 < nR2)
//		nR1 = (nR1 + nR2) >> 1;
//	if(nG1 < nG2)
//		nG1 = (nG1 + nG2) >> 1;
//	if(nB1 < nB2)
//		nB1 = (nB1 + nB2) >> 1;
//	return (nR1<<11) + (nG1<<6) + (nB1<<1);
//}

/** @brief Render a Single Line By BG & Window - CGB */
void cgbGrpRenderBGWIN_CGB(u32 nX, u32 nY, u8* pSrnDataBase, u8* pAtrDataBase, u32 nSX, u32 nEX)
{
	pSrnDataBase += (nY>>3) * CGB_GRP_BG_TILE;
	pAtrDataBase += (nY>>3) * CGB_GRP_BG_TILE;
	u8* pSrnData = pSrnDataBase + (nX>>3);
	u8* pAtrData = pAtrDataBase + (nX>>3);

	u8* pInfo = &g_pCgbGrpLineInfo[nSX];
	u16* pBuf = &g_pCgbGrpRenderBuf[nSX];

	if(nX & 0x07)
	{
		u32 nTileX = nX & 0x07;
		u16* pPal = g_nCgbGrpBGPal[*pAtrData & 0x07];
		u8 nPrio = (*pAtrData & 0x80) ? CGB_GRP_BGPRIO : 0;
		u32 nTileY = (*pAtrData & 0x40) ? (7 - nY & 0x07) : (nY & 0x07);
		u32 nChar = *((u16*)&g_pCgbGrpBGWinTileDataBase[(*pAtrData & 0x08) << 9] + ((u8)(*pSrnData + g_nCgbGrpBGWinTileOffset)) * 8 + nTileY);
		if(*pAtrData & 0x20)
			nChar = (g_pCgbGrpCGBFlipData[nChar>>8] << 8) | g_pCgbGrpCGBFlipData[nChar&0xFF];
		do{
			u8 nColorID = ((nChar >> (7-nTileX)) & 0x1) | ((nChar >> (14-nTileX)) & 0x2);
			*pInfo++ = nColorID ? (nColorID | nPrio) : 0;
			*pBuf++ = pPal[nColorID];
			++nTileX;
			++nSX;
			if(nTileX==8)
				break;
		}while(nSX<nEX);
		++pAtrData;
		++pSrnData;
	}

	if(nSX ==nEX)
		return;

#if	BG_RENDER_REPEAT_FAST
	u8 nCacheSrnData=0xFF;
	u8 nCacheAtrData=0xFF;
	bool bCached=false;
#endif

	do{
		if((nX+nSX) == CGB_GRP_BG_SIZE)
		{
			pAtrData = pAtrDataBase;
			pSrnData = pSrnDataBase;
		}

		u16* pPal = g_nCgbGrpBGPal[*pAtrData & 0x07];
		u8 nPrio = (*pAtrData & 0x80) >> 5;
		u32 nTileY = (*pAtrData & 0x40) ? (7 - nY & 0x07) : (nY & 0x07);
		u32 nChar = *((u16*)&g_pCgbGrpBGWinTileDataBase[(*pAtrData & 0x08) << 9] + ((u8)(*pSrnData + g_nCgbGrpBGWinTileOffset)) * 8 + nTileY);
		if(*pAtrData & 0x20)
			nChar = (g_pCgbGrpCGBFlipData[nChar>>8] << 8) | g_pCgbGrpCGBFlipData[nChar&0xFF];

		if((nSX+8) > nEX)
		{
			u32 nTileX = 0;
			do{
				u8 nColorID = ((nChar >> (7-nTileX)) & 0x1) | ((nChar >> (14-nTileX)) & 0x2);
				*pInfo++ = nColorID ? (nColorID | nPrio) : 0;
				*pBuf++ = pPal[nColorID];
				++nTileX;
				++nSX;
			}while(nSX<nEX);
		}
		else
		{
#if	BG_RENDER_REPEAT_FAST
			if(bCached){
				if(nCacheSrnData==*pSrnData && nCacheAtrData==*pAtrData){
					*(u32*)(pBuf)=*(u32*)(pBuf-8);
					*(u32*)(pBuf+2)=*(u32*)(pBuf-6);
					*(u32*)(pBuf+4)=*(u32*)(pBuf-4);
					*(u32*)(pBuf+6)=*(u32*)(pBuf-2);
					*(u32*)(pInfo)=*(u32*)(pInfo-8);
					*(u32*)(pInfo+4)=*(u32*)(pInfo-4);
					pBuf+=8;
					pInfo+=8;
					
					nSX += 8;
					++pAtrData;
					++pSrnData;
					if(nSX<nEX)
						continue;
					else
						break;
				}
			}
			nCacheSrnData=*pSrnData;
			nCacheAtrData=*pAtrData;
			bCached=true;
#endif
			u32 nColorID = ((nChar >> 7) & 0x1) | ((nChar >> 14) & 0x2);
			u32 nInfo = 0;
			if(nColorID)
				nInfo = nColorID | nPrio;
			u32 nColor = pPal[nColorID];
			nColorID = ((nChar >> 6) & 0x1) | ((nChar >> 13) & 0x2);
			if(nColorID)
				nInfo += (nColorID | nPrio) << 8;
			nColor += pPal[nColorID] << 16;
			*((u32*)pBuf) = nColor;
			pBuf+=2;

			nColorID = ((nChar >> 5) & 0x1) | ((nChar >> 12) & 0x2);
			if(nColorID)
				nInfo += (nColorID | nPrio) << 16;
			nColor = pPal[nColorID];
			nColorID = ((nChar >> 4) & 0x1) | ((nChar >> 11) & 0x2);
			if(nColorID)
				nInfo += (nColorID | nPrio) << 24;
			nColor += pPal[nColorID] << 16;
			*((u32*)pBuf) = nColor;
			pBuf+=2;
			*((u32*)pInfo) = nInfo;
			pInfo+=4;

			nColorID = ((nChar >> 3) & 0x1) | ((nChar >> 10) & 0x2);
			nInfo = 0;
			if(nColorID)
				nInfo = nColorID | nPrio;
			nColor = pPal[nColorID];
			nColorID = ((nChar >> 2) & 0x1) | ((nChar >> 9) & 0x2);
			if(nColorID)
				nInfo += (nColorID | nPrio) << 8;
			nColor += pPal[nColorID] << 16;
			*((u32*)pBuf) = nColor;
			pBuf+=2;

			nColorID = ((nChar >> 1) & 0x1) | ((nChar >> 8) & 0x2);
			if(nColorID)
				nInfo += (nColorID | nPrio) << 16;
			nColor = pPal[nColorID];
			nColorID = (nChar & 0x1) | ((nChar >> 7) & 0x2);
			if(nColorID)
				nInfo += (nColorID | nPrio) << 24;
			nColor += pPal[nColorID] << 16;
			*((u32*)pBuf) = nColor;
			pBuf+=2;
			*((u32*)pInfo) = nInfo;
			pInfo+=4;

			nSX += 8;
			++pAtrData;
			++pSrnData;
		}
	}while(nSX<nEX);
}

/** @brief Render a Single Line By Objects */
void cgbGrpRenderOBJ_DMG()
{
	// Arrange OAM Priority
	u32 nOAMCount = 0;
	s32 nLY = *g_pCgbRegLY;
	cgbSGrpOAMInfo* pCurrent = g_pCgbGrpOAMInfo;
	cgbSGrpOAMInfo* pHeader = NULL;
	cgbSGrpOAMInfo* pParent = NULL;
	cgbSGrpOAMInfo* pNode = NULL;
	for(u32 n=0; n<g_nCgbGrpOAMInfoCount; ++n)
	{
		if((nLY >= pCurrent->nTop) && (nLY < pCurrent->nBottom))
		{
			if(pCurrent->nCharID != 0xFFFFFFFF)
			{
				if(!pHeader)
				{
					pCurrent->pNext = NULL;
					pHeader = pCurrent;
				}
				else
				{
					u32 nInsert = 0;
					pParent = NULL;
					pNode = pHeader;
					while(pNode)
					{
						if(pCurrent->nSX < pNode->nSX)
						{
							pCurrent->pNext = pNode;
							if(!pParent)
								pHeader = pCurrent;
							else
								pParent->pNext = pCurrent;
							nInsert = 1;
							break;
						}
						pParent = pNode;
						pNode = pNode->pNext;
					}
					if(!nInsert)
					{
						pCurrent->pNext = NULL;
						pParent->pNext = pCurrent;
					}
				}
			}
			++nOAMCount;
			if(nOAMCount == CGB_GRP_OBJLINEMAX)
				if(g_bCgbGrpObjLineLimit)
					break;
		}
		++pCurrent;
	}
	// Render
	while(pHeader)
	{
		s32 nY = nLY - pHeader->nTop;
		u32 nAttr = pHeader->nAttr;
		if(nAttr & 0x40)
		{
			if(g_nCgbGrpOBJSize)
				nY = 7 - nY;
			else
				nY = 15 - nY;
		}

		// Character
		u32 nChar = pHeader->nCharID;
		if(!g_nCgbGrpOBJSize)
		{
			if(nY >= 8)
				nChar |= 0x01;
			else
				nChar &= 0xFE;
		}
		nChar = *((u16*)&g_pCgbVRAM[nChar*16] + (nY & 0x07));

		s32 nInc = (nAttr & 0x20) ? -1 : 1;
		u8* pInfo = &g_pCgbGrpLineInfo[pHeader->nStart];

		if(nAttr & CGB_GRP_OBJPRIO)
		{
			for(s32 x=pHeader->nStart, nTileX = pHeader->nTileX; x < pHeader->nEnd; ++x, ++pInfo, nTileX += nInc)
			{
				if(*pInfo & CGB_GRP_OBJINFO)
					continue;
				u8 nColorID = ((nChar >> (7-nTileX)) & 0x1) | ((nChar >> (14-nTileX)) & 0x2);
				if(nColorID)
				{
					if(!(*pInfo & CGB_GRP_BGCOLOR))
						g_pCgbGrpRenderBuf[x] = pHeader->pPal[nColorID];
					*pInfo |= CGB_GRP_OBJINFO;
				}
			}
		}
		else
		{
			for(s32 x=pHeader->nStart, nTileX = pHeader->nTileX; x < pHeader->nEnd; ++x, ++pInfo, nTileX += nInc)
			{
				if(*pInfo & CGB_GRP_OBJINFO)
					continue;
				u8 nColorID = ((nChar >> (7-nTileX)) & 0x1) | ((nChar >> (14-nTileX)) & 0x2);
				if(nColorID)
				{
					g_pCgbGrpRenderBuf[x] = pHeader->pPal[nColorID];
					*pInfo |= CGB_GRP_OBJINFO;
				}
			}
		}
		pHeader = pHeader->pNext;
	}
}

/** @brief Render a Single Line By Objects */
//void cgbGrpRenderOBJ_CGB()
//{
//	cgbSGrpOAMInfo* pHeader = g_pCgbGrpOAMInfo;
//	u32 nOAMCount = 0;
//	s32 nLY = *g_pCgbRegLY;
//	u32 bBG = g_pCgbREG[0x40] & 0x1;
//	for(u32 n=0; n<g_nCgbGrpOAMInfoCount; ++n)
//	{
//		if((nLY >= pHeader->nBottom) || (nLY < pHeader->nTop))
//			++pHeader;
//		else
//		{
//			if(pHeader->nCharID != 0xFFFFFFFF)
//			{
//				s32 nY = nLY - pHeader->nTop;
//				u32 nAttr = pHeader->nAttr;
//				if(nAttr & 0x40)
//				{
//					if(g_nCgbGrpOBJSize)
//						nY = 7 - nY;
//					else
//						nY = 15 - nY;
//				}
//
//				// Character
//				u32 nChar = pHeader->nCharID;
//				if(!g_nCgbGrpOBJSize)
//				{
//					if(nY >= 8)
//						nChar |= 0x01;
//					else
//						nChar &= 0xFE;
//				}
//				nChar = *((u16*)&g_pCgbVRAM[nChar*16 + pHeader->nCharOffset] + (nY & 0x07));
//
//				s32 nInc = (nAttr & 0x20) ? -1 : 1;
//				u8* pInfo = &g_pCgbGrpLineInfo[pHeader->nStart];
//				if(bBG)
//				{
//					if(nAttr & CGB_GRP_OBJPRIO)
//					{
//						for(s32 x=pHeader->nStart, nTileX = pHeader->nTileX; x < pHeader->nEnd; ++x, ++pInfo, nTileX += nInc)
//						{
//							if(*pInfo & CGB_GRP_OBJINFO)
//								continue;
//							u8 nColorID = ((nChar >> (7-nTileX)) & 0x1) | ((nChar >> (14-nTileX)) & 0x2);
//							if(nColorID)
//							{
//								if(!(*pInfo & (CGB_GRP_BGPRIO | CGB_GRP_BGCOLOR)))
//									g_pCgbGrpRenderBuf[x] = pHeader->pPal[nColorID];
//								*pInfo |= CGB_GRP_OBJINFO;
//							}
//						}
//					}
//					else
//					{
//						for(s32 x=pHeader->nStart, nTileX = pHeader->nTileX; x < pHeader->nEnd; ++x, ++pInfo, nTileX += nInc)
//						{
//							if(*pInfo & CGB_GRP_OBJINFO)
//								continue;
//							u8 nColorID = ((nChar >> (7-nTileX)) & 0x1) | ((nChar >> (14-nTileX)) & 0x2);
//							if(nColorID)
//							{
//								if(!(*pInfo & CGB_GRP_BGPRIO))
//									g_pCgbGrpRenderBuf[x] = pHeader->pPal[nColorID];
//								*pInfo |= CGB_GRP_OBJINFO;
//							}
//						}
//					}
//				}
//				else
//				{
//					for(s32 x=pHeader->nStart, nTileX = pHeader->nTileX; x < pHeader->nEnd; ++x, ++pInfo, nTileX += nInc)
//					{
//						if(*pInfo & CGB_GRP_OBJINFO)
//							continue;
//						u8 nColorID = ((nChar >> (7-nTileX)) & 0x1) | ((nChar >> (14-nTileX)) & 0x2);
//						if(nColorID)
//						{
//							g_pCgbGrpRenderBuf[x] = pHeader->pPal[nColorID];
//							*pInfo |= CGB_GRP_OBJINFO;
//						}
//					}
//				}
//			}
//
//			++nOAMCount;
//			if(nOAMCount == CGB_GRP_OBJLINEMAX)
//				if(g_bCgbGrpObjLineLimit)
//					break;
//			++pHeader;
//		}
//	}
//}

/** @brief Render a Single Line By Objects */
void cgbGrpRenderOBJ_CGB()
{
	cgbSGrpOAMInfo* pHeader = g_pCgbGrpOAMInfo;
	u32 nOAMCount = 0;
	s32 nLY = *g_pCgbRegLY;
	for(u32 n=0; n<g_nCgbGrpOAMInfoCount; ++n)
	{
		if((nLY >= pHeader->nBottom) || (nLY < pHeader->nTop))
			++pHeader;
		else
		{
			if(pHeader->nCharID != 0xFFFFFFFF)
			{
				s32 nY = nLY - pHeader->nTop;
				u32 nAttr = pHeader->nAttr;
				if(nAttr & 0x40)
				{
					if(g_nCgbGrpOBJSize)
						nY = 7 - nY;
					else
						nY = 15 - nY;
				}

				// Character
				u32 nChar = pHeader->nCharID;
				if(!g_nCgbGrpOBJSize)
				{
					if(nY >= 8)
						nChar |= 0x01;
					else
						nChar &= 0xFE;
				}
				nChar = *((u16*)&g_pCgbVRAM[nChar*16 + pHeader->nCharOffset] + (nY & 0x07));

				u8* pInfo = &g_pCgbGrpLineInfo[pHeader->nStart];
				u8 nInfoFlag = ((g_pCgbREG[0x40] & 0x1)?CGB_GRP_BGPRIO:0) | ((nAttr & CGB_GRP_OBJPRIO)?CGB_GRP_BGCOLOR:0);
				if((pHeader->nEnd - pHeader->nStart) == 8)
				{
					u16* pPal = pHeader->pPal;
					u16* pBuf = &g_pCgbGrpRenderBuf[pHeader->nStart];
					u32 nInfo = *((u32*)pInfo);

					if(nAttr & 0x20)
					{
						if(!(nInfo & CGB_GRP_OBJINFO))
						{
							u32 nColorID = (nChar & 0x1) | ((nChar >> 7) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & nInfoFlag))
									*pBuf = pPal[nColorID];
								nInfo |= CGB_GRP_OBJINFO;
							}
						}
						pBuf++;

						if(!(nInfo & (CGB_GRP_OBJINFO<<8)))
						{
							u32 nColorID = ((nChar >> 1) & 0x1) | ((nChar >> 8) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & (nInfoFlag<<8)))
									*pBuf = pPal[nColorID];
								nInfo |= (CGB_GRP_OBJINFO << 8);
							}
						}
						pBuf++;

						if(!(nInfo & (CGB_GRP_OBJINFO<<16)))
						{
							u32 nColorID = ((nChar >> 2) & 0x1) | ((nChar >> 9) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & (nInfoFlag<<16)))
									*pBuf = pPal[nColorID];
								nInfo |= (CGB_GRP_OBJINFO << 16);
							}
						}
						pBuf++;

						if(!(nInfo & (CGB_GRP_OBJINFO<<24)))
						{
							u32 nColorID = ((nChar >> 3) & 0x1) | ((nChar >> 10) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & (nInfoFlag<<24)))
									*pBuf = pPal[nColorID];
								nInfo |= (CGB_GRP_OBJINFO << 24);
							}
						}
						pBuf++;

						*((u32*)pInfo) = nInfo;
						pInfo+=4;

						nInfo = *((u32*)pInfo);
						if(!(nInfo & CGB_GRP_OBJINFO))
						{
							u32 nColorID = ((nChar >> 4) & 0x1) | ((nChar >> 11) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & nInfoFlag))
									*pBuf = pPal[nColorID];
								nInfo |= CGB_GRP_OBJINFO;
							}
						}
						pBuf++;

						if(!(nInfo & (CGB_GRP_OBJINFO<<8)))
						{
							u32 nColorID = ((nChar >> 5) & 0x1) | ((nChar >> 12) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & (nInfoFlag<<8)))
									*pBuf = pPal[nColorID];
								nInfo |= (CGB_GRP_OBJINFO << 8);
							}
						}
						pBuf++;

						if(!(nInfo & (CGB_GRP_OBJINFO<<16)))
						{
							u32 nColorID = ((nChar >> 6) & 0x1) | ((nChar >> 13) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & (nInfoFlag<<16)))
									*pBuf = pPal[nColorID];
								nInfo |= (CGB_GRP_OBJINFO << 16);
							}
						}
						pBuf++;

						if(!(nInfo & (CGB_GRP_OBJINFO<<24)))
						{
							u32 nColorID = ((nChar >> 7) & 0x1) | ((nChar >> 14) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & (nInfoFlag<<24)))
									*pBuf = pPal[nColorID];
								nInfo |= (CGB_GRP_OBJINFO << 24);
							}
						}
						*((u32*)pInfo) = nInfo;
					}
					else
					{
						if(!(nInfo & CGB_GRP_OBJINFO))
						{
							u32 nColorID = ((nChar >> 7) & 0x1) | ((nChar >> 14) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & nInfoFlag))
									*pBuf = pPal[nColorID];
								nInfo |= CGB_GRP_OBJINFO;
							}
						}
						pBuf++;

						if(!(nInfo & (CGB_GRP_OBJINFO<<8)))
						{
							u32 nColorID = ((nChar >> 6) & 0x1) | ((nChar >> 13) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & (nInfoFlag<<8)))
									*pBuf = pPal[nColorID];
								nInfo |= (CGB_GRP_OBJINFO << 8);
							}
						}
						pBuf++;

						if(!(nInfo & (CGB_GRP_OBJINFO<<16)))
						{
							u32 nColorID = ((nChar >> 5) & 0x1) | ((nChar >> 12) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & (nInfoFlag<<16)))
									*pBuf = pPal[nColorID];
								nInfo |= (CGB_GRP_OBJINFO << 16);
							}
						}
						pBuf++;

						if(!(nInfo & (CGB_GRP_OBJINFO<<24)))
						{
							u32 nColorID = ((nChar >> 4) & 0x1) | ((nChar >> 11) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & (nInfoFlag<<24)))
									*pBuf = pPal[nColorID];
								nInfo |= (CGB_GRP_OBJINFO << 24);
							}
						}
						pBuf++;

						*((u32*)pInfo) = nInfo;
						pInfo+=4;

						nInfo = *((u32*)pInfo);
						if(!(nInfo & CGB_GRP_OBJINFO))
						{
							u32 nColorID = ((nChar >> 3) & 0x1) | ((nChar >> 10) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & nInfoFlag))
									*pBuf = pPal[nColorID];
								nInfo |= CGB_GRP_OBJINFO;
							}
						}
						pBuf++;

						if(!(nInfo & (CGB_GRP_OBJINFO<<8)))
						{
							u32 nColorID = ((nChar >> 2) & 0x1) | ((nChar >> 9) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & (nInfoFlag<<8)))
									*pBuf = pPal[nColorID];
								nInfo |= (CGB_GRP_OBJINFO << 8);
							}
						}
						pBuf++;

						if(!(nInfo & (CGB_GRP_OBJINFO<<16)))
						{
							u32 nColorID = ((nChar >> 1) & 0x1) | ((nChar >> 8) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & (nInfoFlag<<16)))
									*pBuf = pPal[nColorID];
								nInfo |= (CGB_GRP_OBJINFO << 16);
							}
						}
						pBuf++;

						if(!(nInfo & (CGB_GRP_OBJINFO<<24)))
						{
							u32 nColorID = (nChar & 0x1) | ((nChar >> 7) & 0x2);
							if(nColorID)
							{
								if(!(nInfo & (nInfoFlag<<24)))
									*pBuf = pPal[nColorID];
								nInfo |= (CGB_GRP_OBJINFO << 24);
							}
						}
						*((u32*)pInfo) = nInfo;
					}
				}
				else
				{
					s32 nInc = (nAttr & 0x20) ? -1 : 1;
					for(s32 x=pHeader->nStart, nTileX = pHeader->nTileX; x < pHeader->nEnd; ++x, ++pInfo, nTileX += nInc)
					{
						if(*pInfo & CGB_GRP_OBJINFO)
							continue;
						u8 nColorID = ((nChar >> (7-nTileX)) & 0x1) | ((nChar >> (14-nTileX)) & 0x2);
						if(nColorID)
						{
							if(!(*pInfo & nInfoFlag))
								g_pCgbGrpRenderBuf[x] = pHeader->pPal[nColorID];
							*pInfo |= CGB_GRP_OBJINFO;
						}
					}
				}
			}

			++nOAMCount;
			if(nOAMCount == CGB_GRP_OBJLINEMAX)
				if(g_bCgbGrpObjLineLimit)
					break;
			++pHeader;
		}
	}
}

/** @brief Update OAM - CGB */
inline void cgbGrpUpdateOAM_CGB()
{
	cgbSGrpOAMInfo* pCurrent = g_pCgbGrpOAMInfo;
	g_nCgbGrpOAMInfoCount = 0;
	for(u32 i=0; i < CGB_GRP_OAMMAX; i+=4)
	{
		s32 nSY = g_pCgbOAM[i];
		if(nSY<=g_nCgbGrpOBJSize || nSY>=CGB_GRP_SX)
			continue;
		pCurrent->nTop = nSY-16;
		pCurrent->nBottom = nSY-g_nCgbGrpOBJSize;

		s32 nSX = g_pCgbOAM[i+1];
		if(nSX==0 || nSX>=168)
			pCurrent->nCharID = 0xFFFFFFFF;
		else
		{
			pCurrent->nCharID = g_pCgbOAM[i+2];
			pCurrent->nAttr = g_pCgbOAM[i+3];
			pCurrent->nEnd = (nSX > CGB_GRP_SX) ? CGB_GRP_SX : nSX;
			pCurrent->nStart = (nSX < 8) ? 0 : (nSX - 8);
			nSX = (nSX < 8) ? ((8 - nSX) & 0x07) : 0;
			pCurrent->nTileX = (pCurrent->nAttr & 0x20) ? 7 - nSX : nSX;
			pCurrent->pPal = g_nCgbGrpOBJPal[pCurrent->nAttr & 0x07];
			pCurrent->nCharOffset = (pCurrent->nAttr & 0x08) ? 0x2000 : 0;
		}
		++pCurrent;
		++g_nCgbGrpOAMInfoCount;
	}
}

/** @brief Update OAM - DMG */
inline void cgbGrpUpdateOAM_DMG()
{
	cgbSGrpOAMInfo* pCurrent = g_pCgbGrpOAMInfo;
	g_nCgbGrpOAMInfoCount = 0;
	for(u32 i=0; i < CGB_GRP_OAMMAX; i+=4)
	{
		s32 nSY = g_pCgbOAM[i];
		if(nSY<=g_nCgbGrpOBJSize || nSY>=CGB_GRP_SX)
			continue;
		pCurrent->nTop = nSY-16;
		pCurrent->nBottom = nSY-g_nCgbGrpOBJSize;

		s32 nSX = g_pCgbOAM[i+1];
		if(nSX==0 || nSX>=168)
			pCurrent->nCharID = 0xFFFFFFFF;
		else
		{
			pCurrent->nCharID = g_pCgbOAM[i+2];
			pCurrent->nSX = nSX;
			pCurrent->nAttr = g_pCgbOAM[i+3];
			pCurrent->nEnd = (nSX > CGB_GRP_SX) ? CGB_GRP_SX : nSX;
			pCurrent->nStart = (nSX < 8) ? 0 : (nSX - 8);
			nSX = (nSX < 8) ? ((8 - nSX) & 0x07) : 0;
			pCurrent->nTileX = (pCurrent->nAttr & 0x20) ? 7 - nSX : nSX;
			pCurrent->pPal = g_nCgbGrpOBJPal[(pCurrent->nAttr >> 4) & 0x01];
		}
		++pCurrent;
		++g_nCgbGrpOAMInfoCount;
	}
}

/** @brief Render a Single Line - DMG */
void cgbGrpRenderLine_DMG()
{
	g_pCgbGrpRenderBuf = &((u16*)g_pCgbEmuBuf->pScreenBuf)[*g_pCgbRegLY * g_pCgbEmuBuf->nTexWidth];
	// Window
	u32 nWinX = CGB_GRP_SX;
	if(g_pCgbRegLCDC->rWinEnable)
	{
		if((g_nCgbGrpWinY >= 0) && (*g_pCgbRegLY >= *g_pCgbRegWY) && (*g_pCgbRegWX <= 166))
		{
			u32 nX = 0;
			if(*g_pCgbRegWX < 7)
			{
				nWinX = 0;
				nX = 7 - *g_pCgbRegWX;
			}
			else
				nWinX = *g_pCgbRegWX - 7;
			cgbGrpRenderBGWIN_DMG(nX, g_nCgbGrpWinY++, g_pCgbGrpWinSrnDataBase, nWinX, CGB_GRP_SX);
		}
	}
	// BG
	if(nWinX)
	{
		if(g_pCgbRegLCDC->rBGEnable)
		{
			u32 nX = *g_pCgbRegSCX & CGB_GRP_BG_MASK;
			u32 nY = (*g_pCgbRegSCY + *g_pCgbRegLY) & CGB_GRP_BG_MASK;
			cgbGrpRenderBGWIN_DMG(nX, nY, g_pCgbGrpBGSrnDataBase, 0, nWinX);
		}
		else
		{
			u8* pInfo = g_pCgbGrpLineInfo;
			u16* pBuf = g_pCgbGrpRenderBuf;
			u16 nPal = g_nCgbGrpBGPal[0][0];
			for(u32 x=0; x<nWinX; ++x)
			{
				*pBuf++ = nPal;
				*pInfo++ = 0;
			}
		}
	}
	// OBJ
	if(g_pCgbRegLCDC->rOBJEnable)
	{
		if(g_bCgbGrpOAMChange)
		{
			g_bCgbGrpOAMChange = 0;
			cgbGrpUpdateOAM_DMG();
		}
		cgbGrpRenderOBJ_DMG();
	}
}

/** @brief Render a Single Line - CGB in DMG Mode*/
void cgbGrpRenderLine_CDMG()
{
	g_pCgbGrpRenderBuf = &((u16*)g_pCgbEmuBuf->pScreenBuf)[*g_pCgbRegLY * g_pCgbEmuBuf->nTexWidth];

	// Window
	if(g_pCgbRegLCDC->rBGEnable)
	{
		u32 nWinX = CGB_GRP_SX;
		if(g_pCgbRegLCDC->rWinEnable)
		{
			if((g_nCgbGrpWinY >= 0) && (*g_pCgbRegLY >= *g_pCgbRegWY) && (*g_pCgbRegWX <= 166))
			{
				u32 nX = 0;
				if(*g_pCgbRegWX < 7)
				{
					nWinX = 0;
					nX = 7 - *g_pCgbRegWX;
				}
				else
					nWinX = *g_pCgbRegWX - 7;
				cgbGrpRenderBGWIN_DMG(nX, g_nCgbGrpWinY++, g_pCgbGrpWinSrnDataBase, nWinX, CGB_GRP_SX);
			}
		}
		// BG
		if(nWinX)
		{
			u32 nX = *g_pCgbRegSCX & CGB_GRP_BG_MASK;
			u32 nY = (*g_pCgbRegSCY + *g_pCgbRegLY) & CGB_GRP_BG_MASK;
			cgbGrpRenderBGWIN_DMG(nX, nY, g_pCgbGrpBGSrnDataBase, 0, nWinX);
		}
	}
	else
	{
		u8* pInfo = g_pCgbGrpLineInfo;
		u16* pBuf = g_pCgbGrpRenderBuf;
		u16 nPal = g_nCgbGrpBGPal[0][0];
		for(u32 x=0; x<CGB_GRP_SX; ++x)
		{
			*pBuf++ = nPal;
			*pInfo++ = 0;
		}
	}
	// OBJ
	if(g_pCgbRegLCDC->rOBJEnable)
	{
		if(g_bCgbGrpOAMChange)
		{
			g_bCgbGrpOAMChange = 0;
			cgbGrpUpdateOAM_DMG();
		}
		cgbGrpRenderOBJ_DMG();
	}
}

//u64 g_nCgbTimeOBJ = 0;
//u64 g_nCgbTimeTemp0 = 0;
//u64 g_nCgbTimeTemp1 = 0;

/** @brief Render a Single Line - CGB */
void cgbGrpRenderLine_CGB()
{
#if TRL_DEBUG
	extern s32 g_nTrlEmuGraphicOn;
	if(g_nTrlEmuGraphicOn == 0)
		return;
#endif
	g_pCgbGrpRenderBuf = &((u16*)g_pCgbEmuBuf->pScreenBuf)[*g_pCgbRegLY * g_pCgbEmuBuf->nTexWidth];
	// Window
	u32 nWinX = CGB_GRP_SX;
	if(g_pCgbRegLCDC->rWinEnable)
	{
		if((g_nCgbGrpWinY >= 0) && (*g_pCgbRegLY >= *g_pCgbRegWY) && (*g_pCgbRegWX <= 166))
		{
			u32 nX = 0;
			if(*g_pCgbRegWX < 7)
			{
				nWinX = 0;
				nX = 7 - *g_pCgbRegWX;
			}
			else
				nWinX = *g_pCgbRegWX - 7;
			cgbGrpRenderBGWIN_CGB(nX, g_nCgbGrpWinY++, g_pCgbGrpWinSrnDataBase, g_pCgbGrpWinAtrDataBase, nWinX, CGB_GRP_SX);
		}
	}
	// BG
	if(nWinX)
	{
		u32 nX = *g_pCgbRegSCX & CGB_GRP_BG_MASK;
		u32 nY = (*g_pCgbRegSCY + *g_pCgbRegLY) & CGB_GRP_BG_MASK;
		cgbGrpRenderBGWIN_CGB(nX, nY, g_pCgbGrpBGSrnDataBase, g_pCgbGrpBGAtrDataBase, 0, nWinX);
	}
	// OBJ
	if(g_pCgbRegLCDC->rOBJEnable)
	{
		if(g_bCgbGrpOAMChange)
		{
			g_bCgbGrpOAMChange = 0;
			cgbGrpUpdateOAM_CGB();
		}
//g_nCgbTimeTemp0 = trlTimeGet_us();
		cgbGrpRenderOBJ_CGB();
//g_nCgbTimeTemp1 = trlTimeGet_us();
//g_nCgbTimeOBJ += g_nCgbTimeTemp1 - g_nCgbTimeTemp0;
	}
}

/** @brief Render a White Screen */
inline void cgbGrpRenderWhite()
{
#if TRL_DEBUG
	extern s32 g_nTrlEmuGraphicOn;
	if(g_nTrlEmuGraphicOn == 0)
		return;
#endif
	g_pCgbGrpRenderBuf = (u16*)g_pCgbEmuBuf->pScreenBuf;
	for(u32 y=0; y<CGB_GRP_SY; ++y)
	{
		for(u32 x=0; x<CGB_GRP_SX; ++x)
			g_pCgbGrpRenderBuf[x] = g_nCgbGrpDMGColor[12];

		g_pCgbGrpRenderBuf += g_pCgbEmuBuf->nTexWidth;
	}
	if(g_pCgbEmuBuf->nFrameDouble)
		memcpy(g_pCgbEmuBuf->pTextureBuf[1-g_pCgbEmuBuf->nTexID], g_pCgbEmuBuf->pTextureBuf[g_pCgbEmuBuf->nTexID], g_pCgbEmuBuf->nTexHeight*g_pCgbEmuBuf->nTexWidth*2);
}

/** @brief Compare LY */
inline void cgbGrpLYCompare()
{
	if(*g_pCgbRegLY == *g_pCgbRegLYC)
	{
		g_pCgbRegSTAT->rCoincidence = 1;
		if(g_pCgbRegSTAT->rLYCEnable)
		{
			g_nCgbGrpLCDCInt = g_nCgbGrpLCDCIntFlag;
			g_pCgbRegIF->rLCD = 1;
		}
	}
	else
	{
		g_nCgbGrpLCDCInt = 0;
		g_pCgbRegSTAT->rCoincidence = 0;
	}
}

/** @brief Update LCD */
void cgbGrpUpdateLCD(u8 nRegLast)
{
	u8 nChange = g_pCgbREG[0x40] ^ nRegLast;
	if(nChange & 0x80)
	{
		if(g_pCgbRegLCDC->rLCDEnable)
		{
			*g_pCgbRegLY = 0;
			g_bCgbGrpLCDEnable = 3 + g_nCgbGrpLCDOnDelay;
			g_pCgbRegSTAT->rMode = 2;
			g_nCgbGrpTicks = g_nCgbGrpTick2;
			if(g_pCgbRegSTAT->rOAMEnable)
				g_pCgbRegIF->rLCD = 1;
			cgbGrpLYCompare();
		}
		else
		{
			g_nCgbGrpLCDCInt = 0;
			g_bCgbGrpLCDEnable = 2;
			g_pCgbRegSTAT->rMode = 0;
			g_nCgbGrpTicks = g_nCgbGrpTick1;
		}
	}

	if(nChange & 0x08)
	{
		if(g_nCgbGameType == CGB_GAMETYPE_CGB)
		{
			if(g_pCgbRegLCDC->rBGSrnSel)
			{
				g_pCgbGrpBGSrnDataBase = &g_pCgbVRAM[0x1C00];
				g_pCgbGrpBGAtrDataBase = &g_pCgbVRAM[0x3C00];
			}
			else
			{
				g_pCgbGrpBGSrnDataBase = &g_pCgbVRAM[0x1800];
				g_pCgbGrpBGAtrDataBase = &g_pCgbVRAM[0x3800];
			}
		}
		else
		{
			if(g_pCgbRegLCDC->rBGSrnSel)
				g_pCgbGrpBGSrnDataBase = &g_pCgbVRAM[0x1C00];
			else
				g_pCgbGrpBGSrnDataBase = &g_pCgbVRAM[0x1800];
		}
	}

	if(nChange & 0x40)
	{
		if(g_nCgbGameType == CGB_GAMETYPE_CGB)
		{
			if(g_pCgbRegLCDC->rWinSrnSel)
			{
				g_pCgbGrpWinSrnDataBase = &g_pCgbVRAM[0x1C00];
				g_pCgbGrpWinAtrDataBase = &g_pCgbVRAM[0x3C00];
			}
			else
			{
				g_pCgbGrpWinSrnDataBase = &g_pCgbVRAM[0x1800];
				g_pCgbGrpWinAtrDataBase = &g_pCgbVRAM[0x3800];
			}
		}
		else
		{
			if(g_pCgbRegLCDC->rWinSrnSel)
				g_pCgbGrpWinSrnDataBase = &g_pCgbVRAM[0x1C00];
			else
				g_pCgbGrpWinSrnDataBase = &g_pCgbVRAM[0x1800];
		}
	}

	if(nChange & 0x20)
	{
		if(g_pCgbRegLCDC->rWinEnable && (!g_bCgbGrpWinEnable))
		{
			if((*g_pCgbRegLY > *g_pCgbRegWY) && (*g_pCgbRegLY < CGB_GRP_SY))
				g_nCgbGrpWinY = -1;
		}
	}

	if(nChange & 0x10)
	{
		if(g_pCgbRegLCDC->rBGWinChrSel)
		{
			g_pCgbGrpBGWinTileDataBase = (u16*)&g_pCgbVRAM[0x0000];
			g_nCgbGrpBGWinTileOffset = 0;
		}
		else
		{
			g_pCgbGrpBGWinTileDataBase = (u16*)&g_pCgbVRAM[0x0800];
			g_nCgbGrpBGWinTileOffset = 128;
		}
	}

	if(nChange & 0x4)
	{
		g_nCgbGrpOBJSize = g_pCgbRegLCDC->rOBJSize ? 0 : 8;
		g_bCgbGrpOAMChange = 1;
	}

	if(nChange & 0x2)
		g_bCgbGrpOAMChange = 1;
}

/** @brief Update Ticks */
void cgbGrpUpdateTicks()
{
	switch(g_bCgbGrpLCDEnable)
	{
	case 0:		// LCD Off
		++(*g_pCgbRegLY);
		if(*g_pCgbRegLY == CGB_GRP_SY)
			g_nCgbBreakFlag = 1;
		else if(*g_pCgbRegLY == CGB_GRP_VCOUNTMAX)
			*g_pCgbRegLY = 0;
		g_nCgbGrpTicks += g_nCgbGrpTick1;
		break;
	case 1:		// LCD On
		switch(g_pCgbRegSTAT->rMode)
		{
		case 2:	// During Searching OAM-RAM
			if(!g_bCgbGrpRenderTime)
				cgbGrpRenderLine();
			g_pCgbRegSTAT->rMode = 3;
			g_nCgbGrpTicks += g_nCgbGrpTick3;
			break;
		case 3:	// During Transfering Data to LCD Driver
			if(g_bCgbGrpRenderTime)
				cgbGrpRenderLine();
			g_pCgbRegSTAT->rMode = 0;
			g_nCgbGrpTicks += g_nCgbGrpTick0;
			if(g_pCgbRegSTAT->rHBlankEnable && (!g_nCgbGrpLCDCInt))
				g_pCgbRegIF->rLCD = 1;
			if(g_nCgbDmaHDMAFlag)
				cgbDmaTransferHDMA_HBlank();
			break;
		case 0:	// During H-Blank
			++(*g_pCgbRegLY);
			cgbGrpLYCompare();
			if(*g_pCgbRegLY < CGB_GRP_SY)
			{
				g_pCgbRegSTAT->rMode = 2;
				g_nCgbGrpTicks += g_nCgbGrpTick2;
				if(g_pCgbRegSTAT->rOAMEnable)
					g_pCgbRegIF->rLCD = 1;
			}
			else
			{
				g_nCgbGrpWinY = 0;
				g_pCgbRegSTAT->rMode = 1;
				g_nCgbGrpTicks += g_nCgbGrpVBlankDelay;
				g_bCgbGrpVBlankMode = 3;
				if(g_pCgbRegSTAT->rVBlankEnable)
					g_pCgbRegIF->rLCD = 1;
			}
			break;
		case 1:	// During V-Blank
			switch(g_bCgbGrpVBlankMode)
			{
			case 0:
				++(*g_pCgbRegLY);
				cgbGrpLYCompare();
				if(*g_pCgbRegLY == (CGB_GRP_VCOUNTMAX-1))
				{
					g_bCgbGrpVBlankMode = 1;
					g_nCgbGrpTicks += 1;
				}
				else
					g_nCgbGrpTicks += g_nCgbGrpTick1;
				break;
			case 1:
				*g_pCgbRegLY = 0;
				g_bCgbGrpVBlankMode = 2;
				g_nCgbGrpTicks += g_nCgbGrpTick1 - 1;
				cgbGrpLYCompare();
				break;
			case 2:
				g_bCgbGrpVBlankMode = 3;
				g_pCgbRegSTAT->rMode = 2;
				g_bCgbGrpWinEnable = g_pCgbRegLCDC->rWinEnable;
				g_nCgbGrpTicks += g_nCgbGrpTick2;
				if(g_pCgbRegSTAT->rOAMEnable)
					g_pCgbRegIF->rLCD = 1;
				break;
			case 3:
				g_bCgbGrpVBlankMode = 0;
				g_pCgbRegIF->rVBlank = 1;
				g_nCgbGrpTicks += g_nCgbGrpTick1 - g_nCgbGrpVBlankDelay;
				g_nCgbBreakFlag = 1;
				break;
			}
			break;
		}
		break;
	case 2:		// LCD Prepare Off
		++(*g_pCgbRegLY);
		if(*g_pCgbRegLY == CGB_GRP_SY)
			g_nCgbBreakFlag = 1;
		else if(*g_pCgbRegLY == CGB_GRP_VCOUNTMAX)
		{
			cgbGrpRenderWhite();
			g_bCgbGrpLCDEnable = 0;
			*g_pCgbRegLY = 0;
		}
		g_nCgbGrpTicks += g_nCgbGrpTick1;
		break;
	default:	// LCD Prepare On
		switch(g_pCgbRegSTAT->rMode)
		{
		case 2:	// During Searching OAM-RAM
			g_pCgbRegSTAT->rMode = 3;
			g_nCgbGrpTicks += g_nCgbGrpTick3;
			break;
		case 3:	// During Transfering Data to LCD Driver
			g_pCgbRegSTAT->rMode = 0;
			g_nCgbGrpTicks += g_nCgbGrpTick0;
			if(g_pCgbRegSTAT->rHBlankEnable && (!g_nCgbGrpLCDCInt))
				g_pCgbRegIF->rLCD = 1;
			if(g_nCgbDmaHDMAFlag)
				cgbDmaTransferHDMA_HBlank();
			break;
		case 0:	// During H-Blank
			++(*g_pCgbRegLY);
			cgbGrpLYCompare();
			if(*g_pCgbRegLY < CGB_GRP_SY)
			{
				g_pCgbRegSTAT->rMode = 2;
				g_nCgbGrpTicks += g_nCgbGrpTick2;
				if(g_pCgbRegSTAT->rOAMEnable)
					g_pCgbRegIF->rLCD = 1;
			}
			else
			{
				g_nCgbGrpWinY = 0;
				g_pCgbRegSTAT->rMode = 1;
				g_nCgbGrpTicks += g_nCgbGrpVBlankDelay;
				g_bCgbGrpVBlankMode = 3;
				if(g_pCgbRegSTAT->rVBlankEnable)
					g_pCgbRegIF->rLCD = 1;
				if(g_bCgbGrpLCDEnable == 3)
					g_bCgbGrpLCDEnable = 1;
				else
					g_bCgbGrpLCDEnable--;
			}
			break;
		case 1:	// During V-Blank
			switch(g_bCgbGrpVBlankMode)
			{
			case 0:
				++(*g_pCgbRegLY);
				cgbGrpLYCompare();
				if(*g_pCgbRegLY == (CGB_GRP_VCOUNTMAX-1))
				{
					g_bCgbGrpVBlankMode = 1;
					g_nCgbGrpTicks += 1;
				}
				else
					g_nCgbGrpTicks += g_nCgbGrpTick1;
				break;
			case 1:
				*g_pCgbRegLY = 0;
				g_bCgbGrpVBlankMode = 2;
				g_nCgbGrpTicks += g_nCgbGrpTick1 - 1;
				cgbGrpLYCompare();
				break;
			case 2:
				g_bCgbGrpVBlankMode = 3;
				g_pCgbRegSTAT->rMode = 2;
				g_bCgbGrpWinEnable = g_pCgbRegLCDC->rWinEnable;
				g_nCgbGrpTicks += g_nCgbGrpTick2;
				if(g_pCgbRegSTAT->rOAMEnable)
					g_pCgbRegIF->rLCD = 1;
				break;
			case 3:
				g_bCgbGrpVBlankMode = 0;
				g_pCgbRegIF->rVBlank = 1;
				g_nCgbGrpTicks += g_nCgbGrpTick1 - g_nCgbGrpVBlankDelay;
				g_nCgbBreakFlag = 1;
				break;
			}
			break;
		}
		break;
	}
}

/** @brief Load Nintendo Logo */
void cgbGrpLoadLogo()
{
	u32* pChar = (u32*)&g_pCgbVRAM[0x100];
	for(u32 n=0; n<48; ++n)
	{
		u8 nVal = g_pCgbROMHeader->nLogo[n];
		u8 nHalf = nVal >> 4;
		nHalf = ((nHalf&0x08)<<3) + ((nHalf&0x04)<<2) + ((nHalf&0x02)<<1) + (nHalf&0x01);
		nHalf |= nHalf<<1;
		*pChar = (nHalf<<24) + (nHalf<<16) + (nHalf<<8) + nHalf;
		++pChar;
		nHalf = nVal & 0xF;
		nHalf = ((nHalf&0x08)<<3) + ((nHalf&0x04)<<2) + ((nHalf&0x02)<<1) + (nHalf&0x01);
		nHalf |= nHalf<<1;
		*pChar = (nHalf<<24) + (nHalf<<16) + (nHalf<<8) + nHalf;
		++pChar;
	}

	*pChar++ = 0x42423C3C;
	*pChar++ = 0xA5A5B9B9;
	*pChar++ = 0xA5A5B9B9;
	*pChar++ = 0x3C3C4242;

	u8* pMap = &g_pCgbVRAM[0x1904];
	for(u32 n=0; n<12; ++n, ++pMap)
		*pMap = 0x10 + n;
	pMap = &g_pCgbVRAM[0x1924];
	for(u32 n=0; n<12; ++n, ++pMap)
		*pMap = 0x1C + n;
	g_pCgbVRAM[0x1910] = 0x28;
}

/** @brief Reset Graphic */
void cgbGrpReset()
{
	g_nCgbGrpTick0 = CGB_GRP_TICKS0;
	g_nCgbGrpTick1 = CGB_GRP_TICKS1;
	g_nCgbGrpTick2 = CGB_GRP_TICKS2;
	g_nCgbGrpTick3 = CGB_GRP_TICKS3;
	g_nCgbGrpTicks = g_nCgbGrpTick1;
	g_bCgbGrpOAMChange = 1;
	g_nCgbGrpOAMInfoCount = 0;
	g_bCgbGrpLCDEnable = 1;
	g_bCgbGrpVBlankMode = 0;
	g_nCgbGrpWinY = 0;
	g_nCgbGrpLCDCInt = 0;
	g_bCgbGrpWinEnable = 0;
	memset(g_pCgbGrpLineInfo, 0, CGB_GRP_SX);

	g_pCgbGrpBGSrnDataBase = g_pCgbRegLCDC->rBGSrnSel ? &g_pCgbVRAM[0x1C00] : &g_pCgbVRAM[0x1800];
	g_pCgbGrpWinSrnDataBase = g_pCgbRegLCDC->rWinSrnSel ? &g_pCgbVRAM[0x1C00] : &g_pCgbVRAM[0x1800];
	g_pCgbGrpBGWinTileDataBase = (u16*)&g_pCgbVRAM[g_pCgbRegLCDC->rBGWinChrSel ? 0x0000 : 0x0800];
	g_nCgbGrpBGWinTileOffset = g_pCgbRegLCDC->rBGWinChrSel ? 0x0000 : 128;
	g_nCgbGrpOBJSize = g_pCgbRegLCDC->rOBJSize ? 0 : 8;
	if(g_nCgbGameType == CGB_GAMETYPE_CGB)
	{
		g_nCgbGrpDMGColor[12] = g_pCgbEmuBuf->funcConfigData("CGB", "ColorLCD", 0xFFFF);
		g_pCgbGrpBGAtrDataBase = g_pCgbRegLCDC->rBGSrnSel ? &g_pCgbVRAM[0x3C00] : &g_pCgbVRAM[0x3800];
		g_pCgbGrpWinAtrDataBase = g_pCgbRegLCDC->rWinSrnSel ? &g_pCgbVRAM[0x3C00] : &g_pCgbVRAM[0x3800];
		for(u32 n=0; n<8; ++n)
		{
			for(u32 m=0; m<4; ++m)
			{
				g_nCgbGrpBGPal[n][m] = g_nCgbGrpDMGColor[12];
				g_nCgbGrpOBJPal[n][m] = g_nCgbGrpDMGColor[12];
				g_nCgbGrpBGPalReal[n][m] = CGB_BGRA2RGBA(g_nCgbGrpDMGColor[12]);
				g_nCgbGrpOBJPalReal[n][m] = CGB_BGRA2RGBA(g_nCgbGrpDMGColor[12]);
			}
		}
	}
	else
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
		if(g_bCgbGrpLogo)
			cgbGrpLoadLogo();
	}
	cgbGrpRenderWhite();
}

/** @brief Initialize Graphic */
void cgbGrpInit()
{
	g_pCgbGrpLineInfo = (u8*)trlMemAlloc(CGB_GRP_SX);
	g_pCgbGrpOAMInfo = (cgbSGrpOAMInfo*)trlMemAlloc(CGB_GRP_OBJMAX*sizeof(cgbSGrpOAMInfo));

	g_bCgbGrpRenderTime = g_pCgbEmuBuf->funcConfigData("CGB", "RenderTime", 0);
	g_bCgbGrpLogo = g_pCgbEmuBuf->funcConfigData("CGB", "Logo", 0);
	g_bCgbGrpObjLineLimit = g_pCgbEmuBuf->funcConfigData("CGB", "ObjLineLimit", 1);
	g_nCgbGrpLCDCIntFlag = g_pCgbEmuBuf->funcConfigData("CGB", "LCDIntOnce", 0);
	g_nCgbGrpVBlankDelay = g_pCgbEmuBuf->funcConfigData("CGB", "VBlankDelay", 1);

	if(g_nCgbGameType == CGB_GAMETYPE_CGB)
	{
		g_pCgbGrpCGBFlipData = (u8*)trlMemAlloc(256);
		for(u32 n=0; n<256; ++n)
			g_pCgbGrpCGBFlipData[n] = (n>>7) | ((n>>5) & 0x2) | ((n>>3) & 0x4) | ((n>>1) & 0x8) | ((n<<1) & 0x10) | ((n<<3) & 0x20) | ((n<<5) & 0x40) | (n<<7);

		cgbGrpRenderLine = cgbGrpRenderLine_CGB;
	}
	else
	{
		g_nCgbGrpLCDOnDelay = g_pCgbEmuBuf->funcConfigData("CGB", "LCDOnDelay", 0);
		cgbGrpRenderLine = cgbGrpRenderLine_DMG;
	}

	// Save Data
	g_sCgbGrpSaveData[0].SetData(&g_nCgbGrpTicks, 4, 1, 0);
	g_sCgbGrpSaveData[1].SetData(g_nCgbGrpBGPalReal, 64, 1, 0);
	g_sCgbGrpSaveData[2].SetData(g_nCgbGrpOBJPalReal, 64, 1, 0);
	g_sCgbGrpSaveData[3].SetData(&g_bCgbGrpLCDEnable, 4, 3, 0);
	g_sCgbGrpSaveData[4].SetData(&g_bCgbGrpVBlankMode, 4, 3, 0);

	cgbGrpReset();
}

/** @brief Resume Graphic */
void cgbGrpResume()
{
	if(g_pCgbRegKEY1->rCurSpeed)
	{
		g_nCgbGrpTick0 = CGB_GRP_TICKS0 * 2;
		g_nCgbGrpTick1 = CGB_GRP_TICKS1 * 2;
		g_nCgbGrpTick2 = CGB_GRP_TICKS2 * 2;
		g_nCgbGrpTick3 = CGB_GRP_TICKS3 * 2;
	}
	else
	{
		g_nCgbGrpTick0 = CGB_GRP_TICKS0;
		g_nCgbGrpTick1 = CGB_GRP_TICKS1;
		g_nCgbGrpTick2 = CGB_GRP_TICKS2;
		g_nCgbGrpTick3 = CGB_GRP_TICKS3;
	}

	g_bCgbGrpOAMChange = 1;
	g_nCgbGrpOAMInfoCount = 0;
	g_nCgbGrpWinY = 0;
	g_nCgbGrpLCDCInt = 0;
	memset(g_pCgbGrpLineInfo, 0, CGB_GRP_SX);

	g_pCgbGrpBGSrnDataBase = g_pCgbRegLCDC->rBGSrnSel ? &g_pCgbVRAM[0x1C00] : &g_pCgbVRAM[0x1800];
	g_pCgbGrpWinSrnDataBase = g_pCgbRegLCDC->rWinSrnSel ? &g_pCgbVRAM[0x1C00] : &g_pCgbVRAM[0x1800];
	g_pCgbGrpBGWinTileDataBase = (u16*)&g_pCgbVRAM[g_pCgbRegLCDC->rBGWinChrSel ? 0x0000 : 0x0800];
	g_nCgbGrpBGWinTileOffset = g_pCgbRegLCDC->rBGWinChrSel ? 0x0000 : 128;
	g_nCgbGrpOBJSize = g_pCgbRegLCDC->rOBJSize ? 0 : 8;
	g_bCgbGrpWinEnable = g_pCgbRegLCDC->rWinEnable;
	if(g_nCgbGameType == CGB_GAMETYPE_CGB)
	{
		g_pCgbGrpBGAtrDataBase = g_pCgbRegLCDC->rBGSrnSel ? &g_pCgbVRAM[0x3C00] : &g_pCgbVRAM[0x3800];
		g_pCgbGrpWinAtrDataBase = g_pCgbRegLCDC->rWinSrnSel ? &g_pCgbVRAM[0x3C00] : &g_pCgbVRAM[0x3800];
		for(u32 m=0; m<8; ++m)
		{
			for(u32 n=0; n<4; ++n)
			{
				g_nCgbGrpBGPal[m][n] = CGB_BGRA2RGBA(g_nCgbGrpBGPalReal[m][n]);
				g_nCgbGrpOBJPal[m][n] = CGB_BGRA2RGBA(g_nCgbGrpOBJPalReal[m][n]);
			}
		}
	}
	else
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
}

/** @brief Exit Graphic */
void cgbGrpExit()
{
	trlMemFree(g_pCgbGrpLineInfo);
	trlMemFree(g_pCgbGrpOAMInfo);
	if(g_nCgbGameType == CGB_GAMETYPE_CGB)
		trlMemFree(g_pCgbGrpCGBFlipData);
}
