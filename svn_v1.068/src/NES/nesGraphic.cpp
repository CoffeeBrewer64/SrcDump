/**
* @file nesGraphic.cpp
* @author Chentian
* @date 2010.06.25
* @brief NES Emulate For CTR - Graphic
*/
#include "nesGraphic.h"
#include "nesCPU.h"
#include "nesCard.h"

/** @name Macro Define */
//@{
#define NES_GRP_SX			256							///< Screen X Size
#define NES_GRP_SY			240							///< Screen Y Size
#define NES_GRP_NX			(NES_GRP_SX*2)				///< Background X Size
#define NES_GRP_NY			(NES_GRP_SY*2)				///< Background Y Size
#define NES_GRP_TX			32							///< Tile X Count
#define NES_GRP_TY			30							///< Tile Y Count
#define NES_GRP_SPRMAX		64							///< Sprite Max Number
#define NES_GRP_SPRLINEMAX	8							///< Sprite Max Number in OneScanline
#define NES_GRP_PAL			32							///< Palette Size
#define NES_GRP_INFO_BG		0x03						///< Line Pixel Info - BG Pixel
#define NES_GRP_INFO_SPR	0x04						///< Line Pixel Info - Sprite Pixel
#define NES_GRP_INFO_SPR0	0x08						///< Line Pixel Info - Sprite 0 Pixel
#define NES_GRP_INFO_PRIO	0x10						///< Line Pixel Info - Sprite Priority

#define	NES_GRP_SCANLINE_XSIZE	272
//@}

/** @name Global Variable */
//@{
s32							g_nNesPPULineCycles;					///< PPU cycles per line
s32							g_nNesGrpTicks;							///< PPU Ticks
u32							g_nNesGrpLines;							///< Current Scanline
u8							g_nNesGrpReg[3];						///< PPU Register
u8							g_nNesGrpSPRRAMAddr;					///< SPR-RAM Address
u16							g_nNesGrpRegReload;						///< Reload Register
u16							g_nNesGrpRegReloadX;					///< Reload Register X Scroll
u16							g_nNesGrpVRAMAddr;						///< VRAM Address
u16							g_nNesGrpVRAMAddrInc;					///< VRAM Address Increment
u8							g_nNesGrpVRAMBuffer;					///< VRAM I/O Buffer
u8							g_nNesGrpRegWriteFlag;					///< Register Write Flag
u8*							g_pNesGrpNameTab[5];					///< Name Table and Attribute Table
u8*							g_pNesGrpLineInfo;						///< Line Pixel Info
u16							g_nNesGrpMonoFilter;					///< Monochrome Filter
u16							g_nNesGrpColorFilter;					///< Color Filter
u32							g_nNesGrpNameTabMapping;				///< Name Table and Attribute Table Mapping
u32							g_nNesGrpEnable;						///< Video Enable
u32							g_bNesGrpSPRChange;						///< Sprite Change Flag
u32							g_nNesGrpPatternTabBG;					///< Pattern Tab for BG
u32							g_nNesGrpPatternTabSPR;					///< Pattern Tab for Sprite

nesSGrpRegCtrl1*			g_pNesGrpReg2000;						///< PPU Control Register 1
nesSGrpRegCtrl2*			g_pNesGrpReg2001;						///< PPU Control Register 2
nesSGrpRegStatus*			g_pNesGrpReg2002;						///< PPU Status Register
nesSGrpSprAttr*				g_pNesGrpSprite;						///< Sprite Attributes
nesSGrpSprData				g_sNesGrpSprData[NES_GRP_SPRMAX];		///< Sprite Data
u32							g_nNesGrpSprData;						///< Sprite Data Count
u16*						g_pNesGrpRenderBuf;						///< Render Buffer
u16*						g_pNesGrpPal;							///< Palette Data
u8*							g_pNesGrpFlipData;						///< Flip X Data

u32							g_nNesLineMaxSprite;					///Default is 8

#if TRL_HVC_GRAPHIC
u32							g_nNesGrpSprBuf;						///< Sprite Line Render Count
u16*						g_pNesGrpSprBuf;						///< Sprite Line Buffer
#endif

u16					g_nNesGrpPalTable[0x40] = {				///< Palette Table
	//0x6319, 0x0061, 0x1025, 0x3021, 0x5017, 0x5805, 0x4801, 0x3081, 
	//0x1941, 0x01C1, 0x01C1, 0x0187, 0x0155, 0x0001, 0x0001, 0x0001,
	//0xB5AD, 0x1A35, 0x4179, 0x70B5, 0x90AB, 0x9895, 0x9181, 0x7241, 
	//0x5301, 0x1BC1, 0x03C1, 0x0393, 0x0363, 0x0001, 0x0001, 0x0001,
	//0xFFFF, 0x753F, 0x9C7F, 0xC3FF, 0xE3BF, 0xF3AD, 0xEC59, 0xD4CB, 
	//0xBDC7, 0x8647, 0x6693, 0x5665, 0x5E37, 0x0001, 0x0001, 0x0001,
	//0xFFFF, 0xCF3F, 0xDEFF, 0xEEBF, 0xFEBF, 0xFEBD, 0xFEF5, 0xFF2F, 
	//0xF76D, 0xDFAB, 0xCFB1, 0xC7B7, 0xCFBD, 0x0001, 0x0001, 0x0001 };
	0x739D, 0x20E3, 0x002B, 0x4027, 0x881D, 0xA805, 0xA001, 0x7841,
	0x4141, 0x0201, 0x0281, 0x01C5, 0x19D7, 0x0001, 0x0001, 0x0001,
	0xBDEF, 0x03BB, 0x21FB, 0x803D, 0xB82F, 0xE017, 0xD941, 0xCA43,
	0x8B81, 0x0481, 0x0541, 0x048F, 0x0423, 0x1085, 0x0001, 0x0001,
	0xFFFF, 0x3DFF, 0x5CBF, 0xA47F, 0xF3FF, 0xFBAD, 0xFB99, 0xFCCF,
	0xF5CF, 0x8685, 0x4ED3, 0x5FE7, 0x0777, 0x39CF, 0x0001, 0x0001,
	0xFFFF, 0xAF3F, 0xC6BF, 0xD67F, 0xFE3F, 0xFE37, 0xFDED, 0xFEEB,
	0xFF29, 0xE7E9, 0xAFAF, 0xB7F3, 0x9FFD, 0x8C63, 0x0001, 0x0001 
};

u16					g_nNesGrpPalTable_Origin[0x40] = {				///< Palette Table
	//0x6319, 0x0061, 0x1025, 0x3021, 0x5017, 0x5805, 0x4801, 0x3081, 
	//0x1941, 0x01C1, 0x01C1, 0x0187, 0x0155, 0x0001, 0x0001, 0x0001,
	//0xB5AD, 0x1A35, 0x4179, 0x70B5, 0x90AB, 0x9895, 0x9181, 0x7241, 
	//0x5301, 0x1BC1, 0x03C1, 0x0393, 0x0363, 0x0001, 0x0001, 0x0001,
	//0xFFFF, 0x753F, 0x9C7F, 0xC3FF, 0xE3BF, 0xF3AD, 0xEC59, 0xD4CB, 
	//0xBDC7, 0x8647, 0x6693, 0x5665, 0x5E37, 0x0001, 0x0001, 0x0001,
	//0xFFFF, 0xCF3F, 0xDEFF, 0xEEBF, 0xFEBF, 0xFEBD, 0xFEF5, 0xFF2F, 
	//0xF76D, 0xDFAB, 0xCFB1, 0xC7B7, 0xCFBD, 0x0001, 0x0001, 0x0001 };
	0x739D, 0x20E3, 0x002B, 0x4027, 0x881D, 0xA805, 0xA001, 0x7841,
	0x4141, 0x0201, 0x0281, 0x01C5, 0x19D7, 0x0001, 0x0001, 0x0001,
	0xBDEF, 0x03BB, 0x21FB, 0x803D, 0xB82F, 0xE017, 0xD941, 0xCA43,
	0x8B81, 0x0481, 0x0541, 0x048F, 0x0423, 0x1085, 0x0001, 0x0001,
	0xFFFF, 0x3DFF, 0x5CBF, 0xA47F, 0xF3FF, 0xFBAD, 0xFB99, 0xFCCF,
	0xF5CF, 0x8685, 0x4ED3, 0x5FE7, 0x0777, 0x39CF, 0x0001, 0x0001,
	0xFFFF, 0xAF3F, 0xC6BF, 0xD67F, 0xFE3F, 0xFE37, 0xFDED, 0xFEEB,
	0xFF29, 0xE7E9, 0xAFAF, 0xB7F3, 0x9FFD, 0x8C63, 0x0001, 0x0001 
};
u32							g_pNesGrpClip[4];						///< Clip Pixel
u32							g_nNesGrpSaveData;						///< Graphic Save Data Count
trlSEmuShellResume			g_sNesGrpSaveData[NES_GRP_SAVEDATA_MAX];///< Graphic Save Data

void						(*nesGrpRenderBG)() = NULL;				///< Render BG Function Pointer

//@}

//const ... color adjust...
static f32 rtmul[4]={
			1.0f,
			1.3f,
			0.8f,
			0.8f
};
static f32 gtmul[4]={
			1.0f,
			0.8f,
			1.1f,
			0.8f
};
static f32 btmul[4]={
			1.0f,
			0.8f,
			0.8f,
			1.3f
};

/** @brief Update Palette Color */
inline void nesGrpUpdatePal()
{
	if(g_nNesGrpColorFilter == 0){
		for(u32 n=0; n<NES_GRP_PAL; ++n)
			g_pNesGrpPal[n] = g_nNesGrpPalTable[g_pNesPALRAM[n] & g_nNesGrpMonoFilter];
	}
	else{
		u32 r,g,b;

		for(u32 n=0; n<NES_GRP_PAL; ++n){
			r=((g_nNesGrpPalTable[g_pNesPALRAM[n] & g_nNesGrpMonoFilter] )>>11)&0x1F;
			g=((g_nNesGrpPalTable[g_pNesPALRAM[n] & g_nNesGrpMonoFilter] )>>6 )&0x1F;
			b=((g_nNesGrpPalTable[g_pNesPALRAM[n] & g_nNesGrpMonoFilter] )>>1 )&0x1F;

			r=(u32)((r<<15)*rtmul[g_nNesGrpColorFilter])>>15;
			g=(u32)((g<<15)*gtmul[g_nNesGrpColorFilter])>>15;
			b=(u32)((b<<15)*btmul[g_nNesGrpColorFilter])>>15;

			if(r>0x1F)
				r=0x1F;
			if(g>0x1F)
				g=0x1F;
			if(b>0x1F)
				b=0x1F;

			g_pNesGrpPal[n]=((r<<11)|(g<<6))|((b<<1)|(0x1));
		}
	}
}

void nesGrpUpdatePalA()
{
	if(g_nNesGrpColorFilter == 0){
		for(u32 n=0; n<NES_GRP_PAL; ++n)
			g_pNesGrpPal[n] = g_nNesGrpPalTable[g_pNesPALRAM[n] & g_nNesGrpMonoFilter];
	}
	else{
		u32 r,g,b;

		for(u32 n=0; n<NES_GRP_PAL; ++n){
			r=((g_nNesGrpPalTable[g_pNesPALRAM[n] & g_nNesGrpMonoFilter] )>>11)&0x1F;
			g=((g_nNesGrpPalTable[g_pNesPALRAM[n] & g_nNesGrpMonoFilter] )>>6 )&0x1F;
			b=((g_nNesGrpPalTable[g_pNesPALRAM[n] & g_nNesGrpMonoFilter] )>>1 )&0x1F;

			r=(u32)((r<<15)*rtmul[g_nNesGrpColorFilter])>>15;
			g=(u32)((g<<15)*gtmul[g_nNesGrpColorFilter])>>15;
			b=(u32)((b<<15)*btmul[g_nNesGrpColorFilter])>>15;

			if(r>0x1F)
				r=0x1F;
			if(g>0x1F)
				g=0x1F;
			if(b>0x1F)
				b=0x1F;

			g_pNesGrpPal[n]=((r<<11)|(g<<6))|((b<<1)|(0x1));
		}
	}
}


/** @brief Update Latch */
inline void nesGrpUpdateLatch(u32 nIndex, u32 nValue)
{
	if(g_nNesCardLatch[nIndex] != nValue)
	{
		g_nNesCardLatch[nIndex] = nValue;
		nesCardRegisterLatch(nIndex);
	}
}

/** @brief Initialize Graphic */
void nesGrpInit()
{
#if TRL_HVC_GRAPHIC
	g_pNesGrpSprBuf = (u16*)trlMemAlloc(NES_GRP_SX*2);
#endif
	g_pNesGrpLineInfo = (u8*)trlMemAlloc(NES_GRP_SCANLINE_XSIZE);
	g_pNesGrpPal = (u16*)trlMemAlloc(NES_GRP_PAL*2);
	g_pNesGrpFlipData = (u8*)trlMemAlloc(256);
	for(u32 n=0; n<256; ++n)
		g_pNesGrpFlipData[n] = (n>>7) | ((n>>5) & 0x2) | ((n>>3) & 0x4) | ((n>>1) & 0x8) | ((n<<1) & 0x10) | ((n<<3) & 0x20) | ((n<<5) & 0x40) | (n<<7);

	g_pNesGrpReg2000 = (nesSGrpRegCtrl1*)&g_nNesGrpReg[0];
	g_pNesGrpReg2001 = (nesSGrpRegCtrl2*)&g_nNesGrpReg[1];
	g_pNesGrpReg2002 = (nesSGrpRegStatus*)&g_nNesGrpReg[2];
	g_pNesGrpSprite = (nesSGrpSprAttr*)g_pNesSPRRAM;

	g_pNesGrpClip[0] = g_pNesEmuBuf->funcConfigData("NES", "ClipUp", 0);
	g_pNesGrpClip[1] = NES_GRP_SY - g_pNesEmuBuf->funcConfigData("NES", "ClipDown", 0);
	g_pNesGrpClip[2] = g_pNesEmuBuf->funcConfigData("NES", "ClipLeft", 0);
	g_pNesGrpClip[3] = NES_GRP_SX - g_pNesEmuBuf->funcConfigData("NES", "ClipRight", 0);

	// Save Data
	g_nNesGrpSaveData = 0;
	g_sNesGrpSaveData[g_nNesGrpSaveData++].SetData(&g_nNesGrpTicks, 4, 1, 0);
	g_sNesGrpSaveData[g_nNesGrpSaveData++].SetData(&g_nNesGrpLines, 4, 1, 0);
	g_sNesGrpSaveData[g_nNesGrpSaveData++].SetData(g_nNesGrpReg, 3, 1, 0);
	g_sNesGrpSaveData[g_nNesGrpSaveData++].SetData(&g_nNesGrpSPRRAMAddr, 1, 1, 0);
	g_sNesGrpSaveData[g_nNesGrpSaveData++].SetData(&g_nNesGrpRegReload, 4, 1, 0);
	g_sNesGrpSaveData[g_nNesGrpSaveData++].SetData(&g_nNesGrpRegReloadX, 4, 1, 0);
	g_sNesGrpSaveData[g_nNesGrpSaveData++].SetData(&g_nNesGrpVRAMAddr, 2, 1, 0);
	g_sNesGrpSaveData[g_nNesGrpSaveData++].SetData(&g_nNesGrpVRAMBuffer, 1, 1, 0);
	g_sNesGrpSaveData[g_nNesGrpSaveData++].SetData(&g_nNesGrpRegWriteFlag, 1, 1, 0);
	g_sNesGrpSaveData[g_nNesGrpSaveData++].SetData(&g_nNesGrpNameTabMapping, 4, 1, 0);

	g_nNesPPULineCycles = g_pNesEmuBuf->funcConfigData("NES", "PPULineCycles", 341);
	nesGrpReset();
}

/** @brief Reset Graphic */
void nesGrpReset()
{
	g_nNesGrpTicks = NES_GRP_TICKS;
	g_nNesGrpLines = 241;
	g_nNesGrpReg[0] = 0x00;
	g_nNesGrpReg[1] = 0x00;
	g_nNesGrpReg[2] = 0x80;
	g_nNesGrpSPRRAMAddr = 0;
	g_nNesGrpRegReload = 0;
	g_nNesGrpRegReloadX = 0;
	g_nNesGrpVRAMAddr = 0;
	g_nNesGrpVRAMAddrInc = 1;
	g_nNesGrpVRAMBuffer = 0;
	g_nNesGrpRegWriteFlag = 0;
	g_nNesGrpMonoFilter = 0x3F;
	g_nNesGrpColorFilter = 0;
	g_nNesGrpEnable = 0;
	g_bNesGrpSPRChange = 1;
	g_nNesGrpPatternTabBG = 0;
	g_nNesGrpPatternTabSPR = 0;

	nesGrpChangeNameTabMap(g_pNesROMHeader->nNameTabMapping);

#if TRL_HVC_GRAPHIC
	g_nNesGrpSprBuf = 0;
	memset(g_pNesGrpSprBuf, 0, NES_GRP_SX*2);
#endif
	memset(g_pNesGrpLineInfo, 0, NES_GRP_SCANLINE_XSIZE);
	
	g_nNesLineMaxSprite = g_pNesEmuBuf->funcConfigData("NES", "MaxSpritePerLine", 8);
	for(u32 n=0; n<NES_GRP_PAL; ++n)
		g_pNesGrpPal[n] = g_nNesGrpPalTable[0];
}

/** @brief Resume Graphic */
void nesGrpResume()
{
	if(g_pNesGrpReg2001->rColorMode)
		g_nNesGrpMonoFilter = 0x30;
	else
		g_nNesGrpMonoFilter = 0x3F;
	switch(g_pNesGrpReg2001->rBGColor)
	{
	case 1:	// Red
		g_nNesGrpColorFilter = 1;
		break;
	case 2:	// Green
		g_nNesGrpColorFilter = 2;
		break;
	case 4:	// Blue
		g_nNesGrpColorFilter = 3;
		break;
	default:
		g_nNesGrpColorFilter = 0;
	}
	g_nNesGrpEnable = g_nNesGrpReg[1]&0x18;
	nesGrpUpdatePal();
	if(g_pNesGrpReg2000->rVRAMAddrInc)
		g_nNesGrpVRAMAddrInc = 32;
	else
		g_nNesGrpVRAMAddrInc = 1;
	g_bNesGrpSPRChange = 1;
	if(g_nNesGrpPatternTabBG<8)
		g_nNesGrpPatternTabBG = g_pNesGrpReg2000->rPatternTabBG * 4;
	g_nNesGrpPatternTabSPR = g_pNesGrpReg2000->rPatternTabSPR * 4;
	nesGrpChangeNameTabMap(g_nNesGrpNameTabMapping);
	g_nNesLineMaxSprite = g_pNesEmuBuf->funcConfigData("NES", "MaxSpritePerLine", 8);
#if TRL_HVC_GRAPHIC
	g_nNesGrpSprBuf = 0;
	memset(g_pNesGrpSprBuf, 0, NES_GRP_SX*2);
	memset(g_pNesGrpLineInfo, 0, NES_GRP_SCANLINE_XSIZE);
#endif
}

/** @brief Exit Graphic */
void nesGrpExit()
{
#if TRL_HVC_GRAPHIC
	trlMemFree(g_pNesGrpSprBuf);
#endif
	trlMemFree(g_pNesGrpLineInfo);
	trlMemFree(g_pNesGrpPal);
	trlMemFree(g_pNesGrpFlipData);
}

#if BG_OFFSETY_GT239
static bool g_bATTenable=false;
#endif

#if !TRL_MMC5_CASTLEVANIA3
void nesGrpRenderBGNormal()
{
#if TRL_DEBUG
	extern s32 g_nTrlEmuGraphicOn;
	if(g_nTrlEmuGraphicOn == 0)
		return;
#endif


	//u16 tempRenderBuf[272];
	//u8 tempLineInfo[272];
				register u16*	pScn = g_pNesGrpRenderBuf+(NES_GRP_TEX_OFFSET-g_nNesGrpRegReloadX);//g_pNesGrpRenderBuf-g_nNesGrpRegReloadX;
				register u8	*pBGw = g_pNesGrpLineInfo+(NES_GRP_TEX_OFFSET-g_nNesGrpRegReloadX);

				s32	tileofs = (g_pNesGrpReg2000->rPatternTabBG)?0x1000:0;
				s32	ntbladr = 0x2000+(g_nNesGrpVRAMAddr&0x0FFF);
				s32	attradr = 0x23C0+(g_nNesGrpVRAMAddr&0x0C00)+((g_nNesGrpVRAMAddr&0x0380)>>4);
				s32	ntbl_x  = ntbladr&0x001F;
				s32	attrsft = (ntbladr&0x0040)>>4;
				u8*	pNTBL = g_pNesGrpNameTab[(ntbladr>>10)-8];

				register s32	tileadr;
				s32	cache_tile = 0xFFFF0000;
				u8	cache_attr = 0xFF;

				u8	chr_l,chr_h,attr;

				attradr &= 0x3FF;

				u32 i;
				for( i = 0; i < 33; i++ ) {
					tileadr = tileofs+pNTBL[ntbladr&0x03FF]*0x10+((g_nNesGrpVRAMAddr&0x7000)>>12);
					attr = ((pNTBL[attradr+(ntbl_x>>2)]>>((ntbl_x&2)+attrsft))&3)<<2;

					if( cache_tile == tileadr && cache_attr == attr ) {
						*(u32*)(pScn)=*(u32*)(pScn-8);
						*(u32*)(pScn+2)=*(u32*)(pScn-6);
						*(u32*)(pScn+4)=*(u32*)(pScn-4);
						*(u32*)(pScn+6)=*(u32*)(pScn-2);
						*(u32*)(pBGw)=*(u32*)(pBGw-8);
						*(u32*)(pBGw+4)=*(u32*)(pBGw-4);
						pScn+=8;
						pBGw+=8;
					} else 

					{
						cache_tile = tileadr;
						cache_attr = attr;
						chr_l = g_pNesCHRBank[tileadr>>10][ tileadr&0x03FF   ];
						chr_h = g_pNesCHRBank[tileadr>>10][(tileadr&0x03FF)+8];
						register u16 nBitData = (chr_h<<8)|chr_l;

						u16*	pBGPAL = &g_pNesGrpPal[attr];

						//u32 nBitData = (*(pTile + 8 + nTY) << 8) + *(pTile + nTY);
						if(nBitData){
							u32 nIndex = ((nBitData >> 7) & 0x1) | ((nBitData >> 14) & 0x2);
							u32 nInfo = nIndex;
							u32 nColor = pBGPAL[nIndex];
							nIndex = ((nBitData >> 6) & 0x1) | ((nBitData >> 13) & 0x2);
							nInfo += nIndex << 8;
							nColor += pBGPAL[nIndex] << 16;
							*((u32*)pScn) = nColor;
							pScn+=2;

							nIndex = ((nBitData >> 5) & 0x1) | ((nBitData >> 12) & 0x2);
							nInfo += nIndex << 16;
							nColor = pBGPAL[nIndex];
							nIndex = ((nBitData >> 4) & 0x1) | ((nBitData >> 11) & 0x2);
							nInfo += nIndex << 24;
							nColor += pBGPAL[nIndex] << 16;
							*((u32*)pScn) = nColor;
							pScn+=2;

							*((u32*)pBGw) = nInfo;

							pBGw+=4;

							nIndex = ((nBitData >> 3) & 0x1) | ((nBitData >> 10) & 0x2);
							nInfo = nIndex;
							nColor = pBGPAL[nIndex];
							nIndex = ((nBitData >> 2) & 0x1) | ((nBitData >> 9) & 0x2);
							nInfo += nIndex << 8;
							nColor += pBGPAL[nIndex] << 16;
							*((u32*)pScn) = nColor;
							pScn+=2;

							nIndex = ((nBitData >> 1) & 0x1) | ((nBitData >> 8) & 0x2);
							nInfo += nIndex << 16;
							nColor = pBGPAL[nIndex];
							nIndex = (nBitData & 0x1) | ((nBitData >> 7) & 0x2);
							nInfo += nIndex << 24;
							nColor += pBGPAL[nIndex] << 16;
							*((u32*)pScn) = nColor;
							pScn+=2;

							*((u32*)pBGw) = nInfo;

							pBGw+=4;
						}else
						{
							for(int j=0;j<8;j++){
								*pScn=pBGPAL[0];
								pScn++;
							}
							*(u32*)(pBGw)=0;
							*(u32*)(pBGw+4)=0;
							pBGw+=8;
						}
					}

					if( ++ntbl_x == 32 ) {
						ntbl_x = 0;
						ntbladr ^= 0x41F;
						attradr = 0x03C0+((ntbladr&0x0380)>>4);
						pNTBL = g_pNesGrpNameTab[(ntbladr>>10)-8];
					} else {
						ntbladr++;
					}
				}
//	memcpy(g_pNesGrpRenderBuf, &tempRenderBuf[8], 256*sizeof(u16));
				/*
	for(int i=0;i < 256; i++){
		g_pNesGrpRenderBuf[i]=tempRenderBuf[8+i];
		g_pNesGrpLineInfo[i]=tempLineInfo[8+i];
	}
	*/

	for(i=0;i<8;i++){
		g_pNesGrpRenderBuf[i]=0x0001;
		g_pNesGrpRenderBuf[NES_GRP_SCANLINE_XSIZE-i-1]=0x0001;
		g_pNesGrpLineInfo[i]=0;
		g_pNesGrpLineInfo[NES_GRP_SCANLINE_XSIZE-i-1]=0;
	}

	if(!g_pNesGrpReg2001->rBGClip)
	{
		for(i=NES_GRP_TEX_OFFSET;i < (NES_GRP_TEX_OFFSET+8); i++)
		{
			g_pNesGrpRenderBuf[i] = g_pNesGrpPal[0];
			g_pNesGrpLineInfo[i] = 0;
		}
	}
	return;
}

#else
/** @brief Render a Single Scanline by BG for Normal **/
void nesGrpRenderBGNormal()
{
#if TRL_DEBUG
	extern s32 g_nTrlEmuGraphicOn;
	if(g_nTrlEmuGraphicOn == 0)
		return;
#endif
	s32 nX = ((g_nNesGrpVRAMAddr>>2)&0x0100) | ((g_nNesGrpVRAMAddr&0x001F)<<3) | g_nNesGrpRegReloadX;
	s32 nY = (((g_nNesGrpVRAMAddr>>2)&0x00F8) | ((g_nNesGrpVRAMAddr>>12)&0x0007)) + (((g_nNesGrpVRAMAddr>>11) & 0x0001) * 240);

	if(nX>=NES_GRP_NX)
		nX -= NES_GRP_NX;
	if(nY<0)
		nY += NES_GRP_NY;
	else if(nY>=NES_GRP_NY)
		nY -= NES_GRP_NY;

	u32 nCX = 0;
	u16* pBuf = &g_pNesGrpRenderBuf[nCX]+NES_GRP_TEX_OFFSET;
	u8* pInfo = &g_pNesGrpLineInfo[nCX]+NES_GRP_TEX_OFFSET;
	if(!g_pNesGrpReg2001->rBGClip)
	{
		for(; nCX < 8; ++nCX, ++nX)
		{
			*pBuf++ = g_pNesGrpPal[0];
			*pInfo++ = 0;
		}
		if(nX>=NES_GRP_NX)
			nX -= NES_GRP_NX;
	}

	u8* pName[2];
	u8* pAtti[2];
	if(nY<NES_GRP_SY)
	{
		pName[0] = g_pNesGrpNameTab[0] + (nY>>3)*NES_GRP_TX;
		pName[1] = g_pNesGrpNameTab[1] + (nY>>3)*NES_GRP_TX;
		pAtti[0] = g_pNesGrpNameTab[0] + 0x3C0 + (nY>>5)*8;
		pAtti[1] = g_pNesGrpNameTab[1] + 0x3C0 + (nY>>5)*8;
	}
	else
	{
//modify by yuans;
#if BG_OFFSETY_GT239
		if(g_bATTenable){
			pName[0] = g_pNesGrpNameTab[0] + (nY>>3)*NES_GRP_TX;
			pName[1] = g_pNesGrpNameTab[1] + (nY>>3)*NES_GRP_TX;
			pAtti[0] = g_pNesGrpNameTab[0] + 0x3C0 + (nY>>5)*8;
			pAtti[1] = g_pNesGrpNameTab[1] + 0x3C0 + (nY>>5)*8;
		}else
#endif
		{
			nY -= NES_GRP_SY;
			pName[0] = g_pNesGrpNameTab[2] + (nY>>3)*NES_GRP_TX;
			pName[1] = g_pNesGrpNameTab[3] + (nY>>3)*NES_GRP_TX;
			pAtti[0] = g_pNesGrpNameTab[2] + 0x3C0 + (nY>>5)*8;
			pAtti[1] = g_pNesGrpNameTab[3] + 0x3C0 + (nY>>5)*8;
		}

//end of modify

	}	

	u32 nPage;
	if(nX >= NES_GRP_SX)
	{
		nX -= NES_GRP_SX;
		nPage = 1;
	}
	else
		nPage = 0;

	u32 nT = nX >> 3;
	u32 nTY = nY & 0x7;

	u32 nAttiOffset = ((nY&31) >= 16) ? 4 : 0;
	u8 nPalData = pAtti[nPage][nT>>2] >> nAttiOffset;
	u8 nPal = ((nPalData >> (nT&0x2)) & 0x3) * 4;

	u8* pPattTab[4];
	pPattTab[0] = g_pNesCHRBank[g_nNesGrpPatternTabBG];
	pPattTab[1] = g_pNesCHRBank[g_nNesGrpPatternTabBG+1];
	pPattTab[2] = g_pNesCHRBank[g_nNesGrpPatternTabBG+2];
	pPattTab[3] = g_pNesCHRBank[g_nNesGrpPatternTabBG+3];

	if(nX & 7)
	{
		u32 nTab = pName[nPage][nT]>>6;
		u32 nTile = pName[nPage][nT]&0x3F;
		u8* pTile = pPattTab[nTab] + nTile * 16;
		u32 nBitData = (*(pTile + 8 + nTY) << 8) + *(pTile + nTY);
		do{
			u32 nColor = ((nBitData >> (7-(nX & 0x7))) & 0x1) | ((nBitData >> (14-(nX & 0x7))) & 0x2);
			*pBuf++ = g_pNesGrpPal[nPal+nColor];
#if TRL_HVC_GRAPHIC
			*pInfo++ |= nColor;
#else
			*pInfo++ = nColor;
#endif
			++nX;
			++nCX;
		}while(nX & 7);
		++nT;
	}

#if	BG_RENDER_REPEAT_FAST
	u8* pCacheTileAddr=(u8*)0xFFFF0000;
	u8 nCacheAttr=0xFF;
#endif		

	do{
		if(!(nX & 15))
		{
			if(!(nX & 31))
			{
				if(nX == NES_GRP_SX)
				{
					nX = 0;
					nT = 0;
					nPage = 1 - nPage;
				}
				nPalData = pAtti[nPage][nT>>2] >> nAttiOffset;
			}
			nPal = ((nPalData >> (nT&0x2)) & 0x3) * 4;
		}

		u32 nTab = pName[nPage][nT]>>6;
		u32 nTile = pName[nPage][nT]&0x3F;
		u8* pTile = pPattTab[nTab] + nTile * 16;
#if	BG_RENDER_REPEAT_FAST
		if((pCacheTileAddr == pTile) && (nCacheAttr==pAtti[nPage][nT>>2])){
			*(u32*)(pBuf)=*(u32*)(pBuf-8);
			*(u32*)(pBuf+2)=*(u32*)(pBuf-6);
			*(u32*)(pBuf+4)=*(u32*)(pBuf-4);
			*(u32*)(pBuf+6)=*(u32*)(pBuf-2);
			*(u32*)(pInfo)=*(u32*)(pInfo-8);
			*(u32*)(pInfo+4)=*(u32*)(pInfo-4);
			pBuf+=8;
			pInfo+=8;
		}
		else{
			pCacheTileAddr=pTile;
			nCacheAttr=pAtti[nPage][nT>>2];
#endif
		u32 nBitData = (*(pTile + 8 + nTY) << 8) + *(pTile + nTY);

		u32 nIndex = ((nBitData >> 7) & 0x1) | ((nBitData >> 14) & 0x2);
		u32 nInfo = nIndex;
		u32 nColor = g_pNesGrpPal[nPal+nIndex];
		nIndex = ((nBitData >> 6) & 0x1) | ((nBitData >> 13) & 0x2);
		nInfo += nIndex << 8;
		nColor += g_pNesGrpPal[nPal+nIndex] << 16;
		*((u32*)pBuf) = nColor;
		pBuf+=2;

		nIndex = ((nBitData >> 5) & 0x1) | ((nBitData >> 12) & 0x2);
		nInfo += nIndex << 16;
		nColor = g_pNesGrpPal[nPal+nIndex];
		nIndex = ((nBitData >> 4) & 0x1) | ((nBitData >> 11) & 0x2);
		nInfo += nIndex << 24;
		nColor += g_pNesGrpPal[nPal+nIndex] << 16;
		*((u32*)pBuf) = nColor;
		pBuf+=2;
#if TRL_HVC_GRAPHIC
		*((u32*)pInfo) |= nInfo;
#else
		*((u32*)pInfo) = nInfo;
#endif
		pInfo+=4;

		nIndex = ((nBitData >> 3) & 0x1) | ((nBitData >> 10) & 0x2);
		nInfo = nIndex;
		nColor = g_pNesGrpPal[nPal+nIndex];
		nIndex = ((nBitData >> 2) & 0x1) | ((nBitData >> 9) & 0x2);
		nInfo += nIndex << 8;
		nColor += g_pNesGrpPal[nPal+nIndex] << 16;
		*((u32*)pBuf) = nColor;
		pBuf+=2;

		nIndex = ((nBitData >> 1) & 0x1) | ((nBitData >> 8) & 0x2);
		nInfo += nIndex << 16;
		nColor = g_pNesGrpPal[nPal+nIndex];
		nIndex = (nBitData & 0x1) | ((nBitData >> 7) & 0x2);
		nInfo += nIndex << 24;
		nColor += g_pNesGrpPal[nPal+nIndex] << 16;
		*((u32*)pBuf) = nColor;
		pBuf+=2;
#if TRL_HVC_GRAPHIC
		*((u32*)pInfo) |= nInfo;
#else
		*((u32*)pInfo) = nInfo;
#endif
		pInfo+=4;
#if	BG_RENDER_REPEAT_FAST
		}
#endif
		nX += 8;
		nCX += 8;
		++nT;
	}while(nCX <= (NES_GRP_SX-8));

	if(nCX != NES_GRP_SX)
	{
		if(!(nX & 15))
		{
			if(!(nX & 31))
			{
				if(nX == NES_GRP_SX)
				{
					nX = 0;
					nT = 0;
					nPage = 1 - nPage;
				}
				nPalData = pAtti[nPage][nT>>2] >> nAttiOffset;
			}
			nPal = ((nPalData >> (nT&0x2)) & 0x3) * 4;
		}
		u32 nTab = pName[nPage][nT]>>6;
		u32 nTile = pName[nPage][nT]&0x3F;
		u8* pTile = pPattTab[nTab] + nTile * 16;
		u32 nBitData = (*(pTile + 8 + nTY) << 8) + *(pTile + nTY);
		do{
			u32 nColor = ((nBitData >> (7-(nX & 0x7))) & 0x1) | ((nBitData >> (14-(nX & 0x7))) & 0x2);
			*pBuf++ = g_pNesGrpPal[nPal+nColor];
#if TRL_HVC_GRAPHIC
			*pInfo++ |= nColor;
#else
			*pInfo++ = nColor;
#endif
			++nX;
			++nCX;
		}while(nCX < NES_GRP_SX);
	}
}
#endif


#if 1
/** @brief Update BG for Latch */
inline void nesGrpRenderUpdateBGforLatch(u8 nTile)
{
	u32 nValue;
	switch(nTile)
	{
	case 0xFD:
		nValue = 1;
		break;
	case 0xFE:
		nValue = 0;
		break;
	default:
		return;
	}
	if(g_nNesCardLatch[g_pNesGrpReg2000->rPatternTabBG] == nValue)
		return;
	g_nNesCardLatch[g_pNesGrpReg2000->rPatternTabBG] = nValue;
	nesCardRegisterLatch(g_pNesGrpReg2000->rPatternTabBG);
#if TRL_MMC4_SPEEDUP
	g_bNesGrpSPRChange &= 1;
#endif
}
#else
/** @brief Update BG for Latch */
inline void nesGrpRenderUpdateBGforLatch(u8 nTile, u8* pPattTab[4])
{
	u32 nValue;
	switch(nTile)
	{
	case 0xFD:
		nValue = 1;
		break;
	case 0xFE:
		nValue = 0;
		break;
	default:
		return;
	}
	if(g_nNesCardLatch[g_pNesGrpReg2000->rPatternTabBG] == nValue)
		return;
	g_nNesCardLatch[g_pNesGrpReg2000->rPatternTabBG] = nValue;
	nesCardRegisterLatch(g_pNesGrpReg2000->rPatternTabBG);
#if TRL_MMC4_SPEEDUP
	g_bNesGrpSPRChange &= 1;
#endif
	if(pPattTab)
	{
		pPattTab[0] = g_pNesCHRBank[g_nNesGrpPatternTabBG];
		pPattTab[1] = g_pNesCHRBank[g_nNesGrpPatternTabBG+1];
		pPattTab[2] = g_pNesCHRBank[g_nNesGrpPatternTabBG+2];
		pPattTab[3] = g_pNesCHRBank[g_nNesGrpPatternTabBG+3];
	}
}
#endif

#if 1
void nesGrpRenderBGLatch()
{
#if TRL_DEBUG
	extern s32 g_nTrlEmuGraphicOn;
	if(g_nTrlEmuGraphicOn == 0)
		return;
#endif


	//u16 tempRenderBuf[272];
	//u8 tempLineInfo[272];
				register u16*	pScn = g_pNesGrpRenderBuf+(NES_GRP_TEX_OFFSET-g_nNesGrpRegReloadX);//g_pNesGrpRenderBuf-g_nNesGrpRegReloadX;
				register u8	*pBGw = g_pNesGrpLineInfo+(NES_GRP_TEX_OFFSET-g_nNesGrpRegReloadX);

				s32	tileofs = (g_pNesGrpReg2000->rPatternTabBG)?0x1000:0;
				s32	ntbladr = 0x2000+(g_nNesGrpVRAMAddr&0x0FFF);
				s32	attradr = 0x23C0+(g_nNesGrpVRAMAddr&0x0C00)+((g_nNesGrpVRAMAddr&0x0380)>>4);
				s32	ntbl_x  = ntbladr&0x001F;
				s32	attrsft = (ntbladr&0x0040)>>4;
				u8*	pNTBL = g_pNesGrpNameTab[(ntbladr>>10)-8];

				register s32	tileadr;
				//s32	cache_tile = 0xFFFF0000;
				//u8	cache_attr = 0xFF;

				u8	chr_l,chr_h,attr;

				attradr &= 0x3FF;

				u32 i;
				for( i = 0; i < 33; i++ ) {
					tileadr = tileofs+pNTBL[ntbladr&0x03FF]*0x10+((g_nNesGrpVRAMAddr&0x7000)>>12);
					attr = ((pNTBL[attradr+(ntbl_x>>2)]>>((ntbl_x&2)+attrsft))&3)<<2;
/*
					if( cache_tile == tileadr && cache_attr == attr ) {
						*(u32*)(pScn)=*(u32*)(pScn-8);
						*(u32*)(pScn+2)=*(u32*)(pScn-6);
						*(u32*)(pScn+4)=*(u32*)(pScn-4);
						*(u32*)(pScn+6)=*(u32*)(pScn-2);
						*(u32*)(pBGw)=*(u32*)(pBGw-8);
						*(u32*)(pBGw+4)=*(u32*)(pBGw-4);
						pScn+=8;
						pBGw+=8;
					} else 
*/
					{
						//cache_tile = tileadr;
						//cache_attr = attr;
						chr_l = g_pNesCHRBank[tileadr>>10][ tileadr&0x03FF   ];
						chr_h = g_pNesCHRBank[tileadr>>10][(tileadr&0x03FF)+8];
						register u16 nBitData = (chr_h<<8)|chr_l;

						u16*	pBGPAL = &g_pNesGrpPal[attr];

						//u32 nBitData = (*(pTile + 8 + nTY) << 8) + *(pTile + nTY);
						if(nBitData){
							u32 nIndex = ((nBitData >> 7) & 0x1) | ((nBitData >> 14) & 0x2);
							u32 nInfo = nIndex;
							u32 nColor = pBGPAL[nIndex];
							nIndex = ((nBitData >> 6) & 0x1) | ((nBitData >> 13) & 0x2);
							nInfo += nIndex << 8;
							nColor += pBGPAL[nIndex] << 16;
							*((u32*)pScn) = nColor;
							pScn+=2;

							nIndex = ((nBitData >> 5) & 0x1) | ((nBitData >> 12) & 0x2);
							nInfo += nIndex << 16;
							nColor = pBGPAL[nIndex];
							nIndex = ((nBitData >> 4) & 0x1) | ((nBitData >> 11) & 0x2);
							nInfo += nIndex << 24;
							nColor += pBGPAL[nIndex] << 16;
							*((u32*)pScn) = nColor;
							pScn+=2;

							*((u32*)pBGw) = nInfo;

							pBGw+=4;

							nIndex = ((nBitData >> 3) & 0x1) | ((nBitData >> 10) & 0x2);
							nInfo = nIndex;
							nColor = pBGPAL[nIndex];
							nIndex = ((nBitData >> 2) & 0x1) | ((nBitData >> 9) & 0x2);
							nInfo += nIndex << 8;
							nColor += pBGPAL[nIndex] << 16;
							*((u32*)pScn) = nColor;
							pScn+=2;

							nIndex = ((nBitData >> 1) & 0x1) | ((nBitData >> 8) & 0x2);
							nInfo += nIndex << 16;
							nColor = pBGPAL[nIndex];
							nIndex = (nBitData & 0x1) | ((nBitData >> 7) & 0x2);
							nInfo += nIndex << 24;
							nColor += pBGPAL[nIndex] << 16;
							*((u32*)pScn) = nColor;
							pScn+=2;

							*((u32*)pBGw) = nInfo;

							pBGw+=4;
						}else{
							for(int j=0;j<8;j++){
								*pScn=pBGPAL[0];
								pScn++;
							}
							*(u32*)(pBGw)=0;
							*(u32*)(pBGw+4)=0;
							pBGw+=8;
						}
					}

					nesGrpRenderUpdateBGforLatch((tileadr>>4)&0xFF);

					if( ++ntbl_x == 32 ) {
						ntbl_x = 0;
						ntbladr ^= 0x41F;
						attradr = 0x03C0+((ntbladr&0x0380)>>4);
						pNTBL = g_pNesGrpNameTab[(ntbladr>>10)-8];
					} else {
						ntbladr++;
					}
				}
//	memcpy(g_pNesGrpRenderBuf, &tempRenderBuf[8], 256*sizeof(u16));
				/*
	for(int i=0;i < 256; i++){
		g_pNesGrpRenderBuf[i]=tempRenderBuf[8+i];
		g_pNesGrpLineInfo[i]=tempLineInfo[8+i];
	}
	*/
/*
	for(i=0;i<8;i++){
		g_pNesGrpRenderBuf[i]=0x0001;
		g_pNesGrpRenderBuf[NES_GRP_SCANLINE_XSIZE-i-1]=0x0001;
		g_pNesGrpLineInfo[i]=0;
		g_pNesGrpLineInfo[NES_GRP_SCANLINE_XSIZE-i-1]=0;
	}
*/
	if(!g_pNesGrpReg2001->rBGClip)
	{
		for(i=NES_GRP_TEX_OFFSET;i < (NES_GRP_TEX_OFFSET+8); i++)
		{
			g_pNesGrpRenderBuf[i] = g_pNesGrpPal[0];
			g_pNesGrpLineInfo[i] = 0;
		}
	}
	return;
}

#else

/** @brief Render a Single Scanline by BG for Latch */
void nesGrpRenderBGLatch()
{
#if TRL_DEBUG
	extern s32 g_nTrlEmuGraphicOn;
	if(g_nTrlEmuGraphicOn == 0)
		return;
#endif
	s32 nX = ((g_nNesGrpVRAMAddr>>2)&0x0100) | ((g_nNesGrpVRAMAddr&0x001F)<<3) | g_nNesGrpRegReloadX;
	s32 nY = (((g_nNesGrpVRAMAddr>>2)&0x00F8) | ((g_nNesGrpVRAMAddr>>12)&0x0007)) + (((g_nNesGrpVRAMAddr>>11) & 0x0001) * 240);

	if(nX>=NES_GRP_NX)
		nX -= NES_GRP_NX;
	if(nY<0)
		nY += NES_GRP_NY;
	else if(nY>=NES_GRP_NY)
		nY -= NES_GRP_NY;

	u32 nCX = 0;
	u16* pBuf = &g_pNesGrpRenderBuf[nCX]+NES_GRP_TEX_OFFSET;
	u8* pInfo = &g_pNesGrpLineInfo[nCX]+NES_GRP_TEX_OFFSET;
	if(!g_pNesGrpReg2001->rBGClip)
	{
		for(; nCX < 8; ++nCX, ++nX)
		{
			*pBuf++ = g_pNesGrpPal[0];
#if !TRL_HVC_GRAPHIC
			*pInfo++ = 0;
#endif
		}
		if(nX>=NES_GRP_NX)
			nX -= NES_GRP_NX;
	}

	u8* pName[2];
	u8* pAtti[2];
	if(nY<NES_GRP_SY)
	{
		pName[0] = g_pNesGrpNameTab[0] + (nY>>3)*NES_GRP_TX;
		pName[1] = g_pNesGrpNameTab[1] + (nY>>3)*NES_GRP_TX;
		pAtti[0] = g_pNesGrpNameTab[0] + 0x3C0 + (nY>>5)*8;
		pAtti[1] = g_pNesGrpNameTab[1] + 0x3C0 + (nY>>5)*8;
	}
	else
	{
//modify by yuans;
#if BG_OFFSETY_GT239
		if(g_bATTenable){
			pName[0] = g_pNesGrpNameTab[0] + (nY>>3)*NES_GRP_TX;
			pName[1] = g_pNesGrpNameTab[1] + (nY>>3)*NES_GRP_TX;
			pAtti[0] = g_pNesGrpNameTab[0] + 0x3C0 + (nY>>5)*8;
			pAtti[1] = g_pNesGrpNameTab[1] + 0x3C0 + (nY>>5)*8;
		}else
#endif
		{
			nY -= NES_GRP_SY;
			pName[0] = g_pNesGrpNameTab[2] + (nY>>3)*NES_GRP_TX;
			pName[1] = g_pNesGrpNameTab[3] + (nY>>3)*NES_GRP_TX;
			pAtti[0] = g_pNesGrpNameTab[2] + 0x3C0 + (nY>>5)*8;
			pAtti[1] = g_pNesGrpNameTab[3] + 0x3C0 + (nY>>5)*8;
		}

//end of modify
	}

	u32 nPage;
	if(nX >= NES_GRP_SX)
	{
		nX -= NES_GRP_SX;
		nPage = 1;
	}
	else
		nPage = 0;

	u32 nT = nX >> 3;
	u32 nTY = nY & 0x7;

	u32 nAttiOffset = ((nY&31) >= 16) ? 4 : 0;
	u8 nPalData = pAtti[nPage][nT>>2] >> nAttiOffset;
	u8 nPal = ((nPalData >> (nT&0x2)) & 0x3) * 4;

	u8* pPattTab[4];
	pPattTab[0] = g_pNesCHRBank[g_nNesGrpPatternTabBG];
	pPattTab[1] = g_pNesCHRBank[g_nNesGrpPatternTabBG+1];
	pPattTab[2] = g_pNesCHRBank[g_nNesGrpPatternTabBG+2];
	pPattTab[3] = g_pNesCHRBank[g_nNesGrpPatternTabBG+3];

	if(nX & 7)
	{
		u32 nTab = pName[nPage][nT]>>6;
		u32 nTile = pName[nPage][nT]&0x3F;
		u8* pTile = pPattTab[nTab] + nTile * 16;
		u32 nBitData = (*(pTile + 8 + nTY) << 8) + *(pTile + nTY);

		// Update Latch
		nesGrpRenderUpdateBGforLatch(pName[nPage][nT], pPattTab);

		do{
			u32 nColor = ((nBitData >> (7-(nX & 0x7))) & 0x1) | ((nBitData >> (14-(nX & 0x7))) & 0x2);
			*pBuf++ = g_pNesGrpPal[nPal+nColor];
#if TRL_HVC_GRAPHIC
			*pInfo++ |= nColor;
#else
			*pInfo++ = nColor;
#endif
			++nX;
			++nCX;
		}while(nX & 7);
		++nT;
	}
#if	BG_RENDER_REPEAT_FAST
	u8* pCacheTileAddr=(u8*)0xFFFF0000;
	u8 nCacheAttr=0xFF;
#endif
	do{
		if(!(nX & 15))
		{
			if(!(nX & 31))
			{
				if(nX == NES_GRP_SX)
				{
					nX = 0;
					nT = 0;
					nPage = 1 - nPage;
				}
				nPalData = pAtti[nPage][nT>>2] >> nAttiOffset;
			}
			nPal = ((nPalData >> (nT&0x2)) & 0x3) * 4;
		}

		u32 nTab = pName[nPage][nT]>>6;
		u32 nTile = pName[nPage][nT]&0x3F;
		u8* pTile = pPattTab[nTab] + nTile * 16;
#if	BG_RENDER_REPEAT_FAST
		if((pCacheTileAddr == pTile) && (nCacheAttr==pAtti[nPage][nT>>2])){
			*(u32*)(pBuf)=*(u32*)(pBuf-8);
			*(u32*)(pBuf+2)=*(u32*)(pBuf-6);
			*(u32*)(pBuf+4)=*(u32*)(pBuf-4);
			*(u32*)(pBuf+6)=*(u32*)(pBuf-2);
			*(u32*)(pInfo)=*(u32*)(pInfo-8);
			*(u32*)(pInfo+4)=*(u32*)(pInfo-4);
			pBuf+=8;
			pInfo+=8;
		}
		else{
			pCacheTileAddr=pTile;
			nCacheAttr=pAtti[nPage][nT>>2];
#endif

#if 1
		u32 nBitData = (*(pTile + 8 + nTY) << 8) + *(pTile + nTY);

#if 1
		u32 nIndex0;
		u32 nInfo;
		register u32 nColor0;

		nIndex0 = ((nBitData >> 7) & 0x1);
		nIndex0 |= ((nBitData >> 14) & 0x2);
		nColor0 = g_pNesGrpPal[nPal+nIndex0];
		nInfo = nIndex0;



		nIndex0 = ((nBitData >> 6) & 0x1);
		nIndex0 |= ((nBitData >> 13) & 0x2);		
		nColor0 += g_pNesGrpPal[nPal+nIndex0]<<16;		
		nInfo += nIndex0 << 8;
		
		*((u32*)pBuf) = nColor0;
		pBuf+=2;

		nIndex0 = ((nBitData >> 5) & 0x1);
		nIndex0 |= ((nBitData >> 12) & 0x2);
		nColor0 = g_pNesGrpPal[nPal+nIndex0];
		nInfo += nIndex0 << 16;

		nIndex0 = ((nBitData >> 4) & 0x1);
		nIndex0 |= ((nBitData >> 11) & 0x2);		
		nColor0 += g_pNesGrpPal[nPal+nIndex0]<<16;		
		nInfo += nIndex0 << 24;
		*((u32*)pInfo) = nInfo;
		pInfo+=4;

		*((u32*)pBuf) = nColor0;
		pBuf+=2;

		



		nIndex0 = ((nBitData >> 3) & 0x1);
		nIndex0 |= ((nBitData >> 10) & 0x2);
		nColor0 = g_pNesGrpPal[nPal+nIndex0];
		nInfo = nIndex0;

		nIndex0 = ((nBitData >> 2) & 0x1);
		nIndex0 |= ((nBitData >> 9) & 0x2);		
		nColor0 += g_pNesGrpPal[nPal+nIndex0]<<16;		
		nInfo += nIndex0 << 8;
		
		*((u32*)pBuf) = nColor0;
		pBuf+=2;

		nIndex0 = ((nBitData >> 1) & 0x1);
		nIndex0 |= ((nBitData >> 8) & 0x2);
		nColor0 = g_pNesGrpPal[nPal+nIndex0];
		nInfo += nIndex0 << 16;

		nIndex0 = ((nBitData >> 0) & 0x1);
		nIndex0 |= ((nBitData >> 7) & 0x2);		
		nColor0 += g_pNesGrpPal[nPal+nIndex0]<<16;		
		nInfo += nIndex0 << 24;
		*((u32*)pInfo) = nInfo;
		pInfo+=4;

		*((u32*)pBuf) = nColor0;
		pBuf+=2;

#else		
		//u32 nIndex0;//, nIndex1,nIndex2, nIndex3;
		u8 nIndex[4];
		#define nIndex0 nIndex[0]
		#define nIndex1 nIndex[1]
		#define nIndex2 nIndex[2]
		#define nIndex3 nIndex[3]

		u32 nInfo;
		u32 nColor[2];
		#define nColor0 nColor[0]
		#define nColor1 nColor[1]

		nIndex0 = ((nBitData >> 7) & 0x1) | ((nBitData >> 14) & 0x2);
		nIndex1 = ((nBitData >> 6) & 0x1) | ((nBitData >> 13) & 0x2);
		nColor0 = g_pNesGrpPal[nPal+nIndex0];
		nColor1 = g_pNesGrpPal[nPal+nIndex1]<<16;
		nInfo = nIndex0;
		nInfo += nIndex1 << 8;
		*((u32*)pBuf) = nColor0 + nColor1;
		pBuf+=2;

		nIndex2 = ((nBitData >> 5) & 0x1) | ((nBitData >> 12) & 0x2);
		nIndex3 = ((nBitData >> 4) & 0x1) | ((nBitData >> 11) & 0x2);
		nColor0 = g_pNesGrpPal[nPal+nIndex2];
		nColor1 = g_pNesGrpPal[nPal+nIndex3]<<16;
		nInfo += nIndex2 << 16;
		nInfo += nIndex3 << 24;
		*((u32*)pBuf) = nColor0 + nColor1;
		pBuf+=2;

		*((u32*)pInfo) = nInfo;
		pInfo+=4;

		nIndex0 = ((nBitData >> 3) & 0x1) | ((nBitData >> 10) & 0x2);
		nIndex1 = ((nBitData >> 2) & 0x1) | ((nBitData >> 9) & 0x2);
		nColor0 = g_pNesGrpPal[nPal+nIndex0];
		nColor1 = g_pNesGrpPal[nPal+nIndex1]<<16;
		nInfo = nIndex0;
		nInfo += nIndex1 << 8;
		*((u32*)pBuf) = nColor0 + nColor1;
		pBuf+=2;

		nIndex2 = ((nBitData >> 1) & 0x1) | ((nBitData >> 8) & 0x2);
		nIndex3 = (nBitData & 0x1) | ((nBitData >> 7) & 0x2);
		nColor0 = g_pNesGrpPal[nPal+nIndex2];
		nColor1 = g_pNesGrpPal[nPal+nIndex3]<<16;
		nInfo += nIndex2 << 16;
		nInfo += nIndex3 << 24;
		*((u32*)pBuf) = nColor0 + nColor1;
		pBuf+=2;

		*((u32*)pInfo) = nInfo;
		pInfo+=4;
#endif
#else
		u32 nBitData = (*(pTile + 8 + nTY) << 8) + *(pTile + nTY);
		u32 nIndex = ((nBitData >> 7) & 0x1) | ((nBitData >> 14) & 0x2);
		u32 nInfo = nIndex;
		u32 nColor = g_pNesGrpPal[nPal+nIndex];
		nIndex = ((nBitData >> 6) & 0x1) | ((nBitData >> 13) & 0x2);
		nInfo += nIndex << 8;
		nColor += g_pNesGrpPal[nPal+nIndex] << 16;
		*((u32*)pBuf) = nColor;
		pBuf+=2;

		nIndex = ((nBitData >> 5) & 0x1) | ((nBitData >> 12) & 0x2);
		nInfo += nIndex << 16;
		nColor = g_pNesGrpPal[nPal+nIndex];
		nIndex = ((nBitData >> 4) & 0x1) | ((nBitData >> 11) & 0x2);
		nInfo += nIndex << 24;
		nColor += g_pNesGrpPal[nPal+nIndex] << 16;
		*((u32*)pBuf) = nColor;
		pBuf+=2;
#if TRL_HVC_GRAPHIC
		*((u32*)pInfo) |= nInfo;
#else
		*((u32*)pInfo) = nInfo;
#endif
		pInfo+=4;

		nIndex = ((nBitData >> 3) & 0x1) | ((nBitData >> 10) & 0x2);
		nInfo = nIndex;
		nColor = g_pNesGrpPal[nPal+nIndex];
		nIndex = ((nBitData >> 2) & 0x1) | ((nBitData >> 9) & 0x2);
		nInfo += nIndex << 8;
		nColor += g_pNesGrpPal[nPal+nIndex] << 16;
		*((u32*)pBuf) = nColor;
		pBuf+=2;

		nIndex = ((nBitData >> 1) & 0x1) | ((nBitData >> 8) & 0x2);
		nInfo += nIndex << 16;
		nColor = g_pNesGrpPal[nPal+nIndex];
		nIndex = (nBitData & 0x1) | ((nBitData >> 7) & 0x2);
		nInfo += nIndex << 24;
		nColor += g_pNesGrpPal[nPal+nIndex] << 16;
		*((u32*)pBuf) = nColor;
		pBuf+=2;
#if TRL_HVC_GRAPHIC
		*((u32*)pInfo) |= nInfo;
#else
		*((u32*)pInfo) = nInfo;
#endif
		pInfo+=4;
#endif


#if	BG_RENDER_REPEAT_FAST
		}
#endif
		// Update Latch
		nesGrpRenderUpdateBGforLatch(pName[nPage][nT], pPattTab);

		nX += 8;
		nCX += 8;
		++nT;
	}while(nCX <= (NES_GRP_SX-8));

	if(nCX != NES_GRP_SX)
	{
		if(!(nX & 15))
		{
			if(!(nX & 31))
			{
				if(nX == NES_GRP_SX)
				{
					nX = 0;
					nT = 0;
					nPage = 1 - nPage;
				}
				nPalData = pAtti[nPage][nT>>2] >> nAttiOffset;
			}
			nPal = ((nPalData >> (nT&0x2)) & 0x3) * 4;
		}
		u32 nTab = pName[nPage][nT]>>6;
		u32 nTile = pName[nPage][nT]&0x3F;
		u8* pTile = pPattTab[nTab] + nTile * 16;
		u32 nBitData = (*(pTile + 8 + nTY) << 8) + *(pTile + nTY);

		// Update Latch
		nesGrpRenderUpdateBGforLatch(pName[nPage][nT], pPattTab);

		do{
			u32 nColor = ((nBitData >> (7-(nX & 0x7))) & 0x1) | ((nBitData >> (14-(nX & 0x7))) & 0x2);
			*pBuf++ = g_pNesGrpPal[nPal+nColor];
#if TRL_HVC_GRAPHIC
			*pInfo++ |= nColor;
#else
			*pInfo++ = nColor;
#endif
			++nX;
			++nCX;
		}while(nCX < NES_GRP_SX);
		++nT;
	}

	// Update Latch
	u32 nLoop = (nX & 7) ? 1 : 2;
	for(u32 n=0; n<nLoop; ++n)
	{
		if(nX >= NES_GRP_SX)
		{
			nT = 0;
			nPage = 1 - nPage;
		}
		nesGrpRenderUpdateBGforLatch(pName[nPage][nT], NULL);
		nX += 8;
		++nT;
	}
}
#endif

/** @brief Render a Single Scanline by BG for MMC5 */
void nesGrpRenderBGMMC5()
{
#if TRL_DEBUG
	extern s32 g_nTrlEmuGraphicOn;
	if(g_nTrlEmuGraphicOn == 0)
		return;
#endif
	s32 nX = ((g_nNesGrpVRAMAddr>>2)&0x0100) | ((g_nNesGrpVRAMAddr&0x001F)<<3) | g_nNesGrpRegReloadX;
	s32 nY = (((g_nNesGrpVRAMAddr>>2)&0x00F8) | ((g_nNesGrpVRAMAddr>>12)&0x0007)) + (((g_nNesGrpVRAMAddr>>11) & 0x0001) * 240);

	if(nX>=NES_GRP_NX)
		nX -= NES_GRP_NX;
	if(nY<0)
		nY += NES_GRP_NY;
	else if(nY>=NES_GRP_NY)
		nY -= NES_GRP_NY;

	u32 nCX = 0;
	u16* pBuf = &g_pNesGrpRenderBuf[nCX]+NES_GRP_TEX_OFFSET;
	u8* pInfo = &g_pNesGrpLineInfo[nCX]+NES_GRP_TEX_OFFSET;
	if(!g_pNesGrpReg2001->rBGClip)
	{
		for(; nCX < 8; ++nCX, ++nX)
		{
			*pBuf++ = g_pNesGrpPal[0];
#if !TRL_HVC_GRAPHIC
			*pInfo++ = 0;
#endif
		}
		if(nX>=NES_GRP_NX)
			nX -= NES_GRP_NX;
	}

	u8* pName[2];
	if(nY<NES_GRP_SY)
	{
		pName[0] = g_pNesGrpNameTab[0] + (nY>>3)*NES_GRP_TX;
		pName[1] = g_pNesGrpNameTab[1] + (nY>>3)*NES_GRP_TX;
	}
	else
	{
//modify by yuans;
#if BG_OFFSETY_GT239
		if(g_bATTenable){
			pName[0] = g_pNesGrpNameTab[0] + (nY>>3)*NES_GRP_TX;
			pName[1] = g_pNesGrpNameTab[1] + (nY>>3)*NES_GRP_TX;

		}else
#endif
		{
			nY -= NES_GRP_SY;
			pName[0] = g_pNesGrpNameTab[2] + (nY>>3)*NES_GRP_TX;
			pName[1] = g_pNesGrpNameTab[3] + (nY>>3)*NES_GRP_TX;
		}

//end of modify
	}
	u8* pNameEx = g_pNesGrpNameTab[4] + (nY>>3)*NES_GRP_TX;

	u32 nPage;
	if(nX >= NES_GRP_SX)
	{
		nX -= NES_GRP_SX;
		nPage = 1;
	}
	else
		nPage = 0;

	u32 nT = nX >> 3;
	u32 nTY = nY & 0x7;
	if(nX & 7)
	{
		u8* pTile = g_pNesCHRROM + (((pNameEx[nT]&0x3F) << 8) + pName[nPage][nT]) * 16;
		u16 nBitData = (*(pTile + 8 + nTY) << 8) + *(pTile + nTY);
		u32 nPal = (pNameEx[nT] & 0xC0) >> 4;
		do{
			u32 nColor = ((nBitData >> (7-(nX & 0x7))) & 0x1) | ((nBitData >> (14-(nX & 0x7))) & 0x2);
			*pBuf++ = g_pNesGrpPal[nPal+nColor];
#if TRL_HVC_GRAPHIC
			*pInfo++ |= nColor;
#else
			*pInfo++ = nColor;
#endif
			++nX;
			++nCX;
		}while(nX & 7);
		++nT;
	}
#if	BG_RENDER_REPEAT_FAST
	u8* pCacheTileAddr=(u8*)0xFFFF0000;
	u8 nCacheAttr=0xFF;
#endif
	do{
		u8* pTile = g_pNesCHRROM + (((pNameEx[nT]&0x3F) << 8) + pName[nPage][nT]) * 16;
#if	BG_RENDER_REPEAT_FAST
		if((pCacheTileAddr == pTile) && (nCacheAttr==pNameEx[nT])){
			*(u32*)(pBuf)=*(u32*)(pBuf-8);
			*(u32*)(pBuf+2)=*(u32*)(pBuf-6);
			*(u32*)(pBuf+4)=*(u32*)(pBuf-4);
			*(u32*)(pBuf+6)=*(u32*)(pBuf-2);
			*(u32*)(pInfo)=*(u32*)(pInfo-8);
			*(u32*)(pInfo+4)=*(u32*)(pInfo-4);
			pBuf+=8;
			pInfo+=8;
		}
		else{
			pCacheTileAddr=pTile;
			nCacheAttr=pNameEx[nT];
#endif
		u32 nBitData = (*(pTile + 8 + nTY) << 8) + *(pTile + nTY);
		u16* pPalBuf = g_pNesGrpPal + ((pNameEx[nT] & 0xC0) >> 4);

		u32 nIndex = ((nBitData >> 7) & 0x1) | ((nBitData >> 14) & 0x2);
		u32 nInfo = nIndex;
		u32 nColor = pPalBuf[nIndex];
		nIndex = ((nBitData >> 6) & 0x1) | ((nBitData >> 13) & 0x2);
		nInfo += nIndex << 8;
		nColor += pPalBuf[nIndex] << 16;
		*((u32*)pBuf) = nColor;
		pBuf+=2;

		nIndex = ((nBitData >> 5) & 0x1) | ((nBitData >> 12) & 0x2);
		nInfo += nIndex << 16;
		nColor = pPalBuf[nIndex];
		nIndex = ((nBitData >> 4) & 0x1) | ((nBitData >> 11) & 0x2);
		nInfo += nIndex << 24;
		nColor += pPalBuf[nIndex] << 16;
		*((u32*)pBuf) = nColor;
		pBuf+=2;
#if TRL_HVC_GRAPHIC
		*((u32*)pInfo) |= nInfo;
#else
		*((u32*)pInfo) = nInfo;
#endif
		pInfo+=4;

		nIndex = ((nBitData >> 3) & 0x1) | ((nBitData >> 10) & 0x2);
		nInfo = nIndex;
		nColor = pPalBuf[nIndex];
		nIndex = ((nBitData >> 2) & 0x1) | ((nBitData >> 9) & 0x2);
		nInfo += nIndex << 8;
		nColor += pPalBuf[nIndex] << 16;
		*((u32*)pBuf) = nColor;
		pBuf+=2;

		nIndex = ((nBitData >> 1) & 0x1) | ((nBitData >> 8) & 0x2);
		nInfo += nIndex << 16;
		nColor = pPalBuf[nIndex];
		nIndex = (nBitData & 0x1) | ((nBitData >> 7) & 0x2);
		nInfo += nIndex << 24;
		nColor += pPalBuf[nIndex] << 16;
		*((u32*)pBuf) = nColor;
		pBuf+=2;
#if TRL_HVC_GRAPHIC
		*((u32*)pInfo) |= nInfo;
#else
		*((u32*)pInfo) = nInfo;
#endif
		pInfo+=4;
#if	BG_RENDER_REPEAT_FAST
		}
#endif
		nCX += 8;
		++nT;
	}while(nCX <= (NES_GRP_SX-8));

	if(nCX != NES_GRP_SX)
	{
		u8* pTile = g_pNesCHRROM + (((pNameEx[nT]&0x3F) << 8) + pName[nPage][nT]) * 16;
		u16 nBitData = (*(pTile + 8 + nTY) << 8) + *(pTile + nTY);
		u32 nPal = (pNameEx[nT] & 0xC0) >> 4;
		do{
			u32 nColor = ((nBitData >> (7-(nX & 0x7))) & 0x1) | ((nBitData >> (14-(nX & 0x7))) & 0x2);
			*pBuf++ = g_pNesGrpPal[nPal+nColor];
#if TRL_HVC_GRAPHIC
			*pInfo++ |= nColor;
#else
			*pInfo++ = nColor;
#endif
			++nX;
			++nCX;
		}while(nCX < NES_GRP_SX);
	}
}

/** @brief Update Sprites Data - HFlip & VFilp */
inline void nesGrpUpdateSPRDataH1V1(u16* pBitData, u8* pTile)
{
	for(u32 m=0; m<8; ++m)
		pBitData[m] = (g_pNesGrpFlipData[*(pTile + 15 - m)] << 8) + g_pNesGrpFlipData[*(pTile + 7 - m)];
}

/** @brief Update Sprites Data - HFlip */
inline void nesGrpUpdateSPRDataH1V0(u16* pBitData, u8* pTile)
{
	for(u32 m=0; m<8; ++m)
		pBitData[m] = (g_pNesGrpFlipData[*(pTile + 8 + m)] << 8) + g_pNesGrpFlipData[*(pTile + m)];
}

/** @brief Update Sprites Data - VFilp */
inline void nesGrpUpdateSPRDataH0V1(u16* pBitData, u8* pTile)
{
	for(u32 m=0; m<8; ++m)
		pBitData[m] = (*(pTile + 15 - m) << 8) + *(pTile + 7 - m);
}

/** @brief Update Sprites Data - None Filp */
inline void nesGrpUpdateSPRDataH0V0(u16* pBitData, u8* pTile)
{
	for(u32 m=0; m<8; ++m)
		pBitData[m] = (*(pTile + 8 + m) << 8) + *(pTile + m);
}

/** @brief Update Sprites Data - Size 8 */
inline void nesGrpUpdateSPRData8(nesSGrpSprData* pData)
{
	// Get Tile Address
	u8* pTile = g_pNesCHRBank[g_nNesGrpPatternTabSPR + (pData->nTile>>6)] + (pData->nTile&0x3F) * 16;
	// Get Bit Data
	if(pData->nHFlip)
		if(pData->nVFlip)
			nesGrpUpdateSPRDataH1V1(pData->nBitData, pTile);
		else
			nesGrpUpdateSPRDataH1V0(pData->nBitData, pTile);
	else
		if(pData->nVFlip)
			nesGrpUpdateSPRDataH0V1(pData->nBitData, pTile);
		else
			nesGrpUpdateSPRDataH0V0(pData->nBitData, pTile);
}

/** @brief Update Sprites Data - Size 16 */
inline void nesGrpUpdateSPRData16(nesSGrpSprData* pData)
{
	// Get Tile Address
	u8* pTile = g_pNesCHRBank[(pData->nTile & 0x1)*4 + (pData->nTile>>6)] + (pData->nTile&0x3E) * 16;
	// Get Bit Data
	if(pData->nHFlip)
	{
		if(pData->nVFlip)
		{
			nesGrpUpdateSPRDataH1V1(pData->nBitData, pTile + 16);
			nesGrpUpdateSPRDataH1V1(pData->nBitData+8, pTile);
		}
		else
		{
			nesGrpUpdateSPRDataH1V0(pData->nBitData, pTile);
			nesGrpUpdateSPRDataH1V0(pData->nBitData+8, pTile + 16);
		}
	}
	else
	{
		if(pData->nVFlip)
		{
			nesGrpUpdateSPRDataH0V1(pData->nBitData, pTile + 16);
			nesGrpUpdateSPRDataH0V1(pData->nBitData+8, pTile);
		}
		else
		{
			nesGrpUpdateSPRDataH0V0(pData->nBitData, pTile);
			nesGrpUpdateSPRDataH0V0(pData->nBitData+8, pTile + 16);
		}
	}
}

/** @brief Update Sprites */
void nesGrpUpdateSPR()
{
	nesSGrpSprData* pData = g_sNesGrpSprData;
#if 0
	//if(g_bNesGrpSPRChange & 0x1)
#else
	if(g_bNesGrpSPRChange & 0x1)
#endif
	{
		#if TRL_DEBUG
		extern s32 g_nTrlEmuOBJNum;
		g_nTrlEmuOBJNum = 0;
		#endif
		nesSGrpSprAttr* pSpr = g_pNesGrpSprite;
		g_nNesGrpSprData = 0;
		if(g_pNesGrpReg2000->rSPRSize)
		{
			for(u32 n=0; n<NES_GRP_SPRMAX; ++n, ++pSpr)
			{
				// Clip
				if(pSpr->nY >= (NES_GRP_SY-1))
					continue;
				if(pSpr->nX == NES_GRP_SX)
					continue;
				pData->nID = n;
				pData->nX = pSpr->nX;
				pData->nY = pSpr->nY + 1;
				pData->nTile = pSpr->nTile;
				pData->nPal = 0x10 + pSpr->rPal*4;
				pData->nPrio = pSpr->rPrio;
				pData->nHFlip = pSpr->rHFlip;
				pData->nVFlip = pSpr->rVFlip;

				nesGrpUpdateSPRData16(pData++);
				g_nNesGrpSprData++;
				#if TRL_DEBUG
				g_nTrlEmuOBJNum++;
				#endif
			}
		}
		else
		{
			for(u32 n=0; n<NES_GRP_SPRMAX; ++n, ++pSpr)
			{
				// Clip
				if(pSpr->nY >= (NES_GRP_SY-1))
					continue;
				if(pSpr->nX == NES_GRP_SX)
					continue;
				pData->nID = n;
				pData->nX = pSpr->nX;
				pData->nY = pSpr->nY + 1;
				pData->nTile = pSpr->nTile;
				pData->nPal = 0x10 + pSpr->rPal*4;
				pData->nPrio = pSpr->rPrio;
				pData->nHFlip = pSpr->rHFlip;
				pData->nVFlip = pSpr->rVFlip;

				nesGrpUpdateSPRData8(pData++);
				g_nNesGrpSprData++;
				#if TRL_DEBUG
				g_nTrlEmuOBJNum++;
				#endif
			}
		}
	}
#if 0
	/*
	else
	{
		if(g_pNesGrpReg2000->rSPRSize)
		{
			for(u32 n=0; n<g_nNesGrpSprData; ++n)
				nesGrpUpdateSPRData16(pData++);
		}
		else
		{
			for(u32 n=0; n<g_nNesGrpSprData; ++n)
				nesGrpUpdateSPRData8(pData++);
		}
	}
	*/
#else
	else
	{
		if(g_pNesGrpReg2000->rSPRSize)
		{
			for(u32 n=0; n<g_nNesGrpSprData; ++n){
#if	0
				if(pData->nY >= (NES_GRP_SY+1))
					continue;
				if(pData->nX == NES_GRP_SX)
					continue;
#endif
				nesGrpUpdateSPRData16(pData++);
			}
		}
		else
		{
			for(u32 n=0; n<g_nNesGrpSprData; ++n){
#if 0
					if(pData->nY >= (NES_GRP_SY+1))
						continue;
					if(pData->nX == NES_GRP_SX)
						continue;
#endif
					nesGrpUpdateSPRData8(pData++);
			}
		}
	}
#endif
	g_bNesGrpSPRChange = 0;
}

/** @brief Update Sprites for Latch */
inline void nesGrpRenderUpdateSPRforLatch(nesSGrpSprData* pData)
{
	u32 nValue;
	switch(pData->nTile)
	{
	case 0xFD:
		nValue = 1;
		break;
	case 0xFE:
		nValue = 0;
		break;
	default:
		return;
	}
	if(g_nNesCardLatch[g_pNesGrpReg2000->rPatternTabSPR] == nValue)
		return;
	g_nNesCardLatch[g_pNesGrpReg2000->rPatternTabSPR] = nValue;
	nesCardRegisterLatch(g_pNesGrpReg2000->rPatternTabSPR);
#if 0
	nesGrpUpdateSPR();
#else
	u32 nSPRChange = g_bNesGrpSPRChange & 0x01;
	g_bNesGrpSPRChange = 0x02;
	nesGrpUpdateSPR();
	g_bNesGrpSPRChange = nSPRChange;
#endif
}

/** @brief Render a Single Scanline by Sprites */
void nesGrpRenderSPR()
{
#if TRL_DEBUG
	extern s32 g_nTrlEmuGraphicOn;
	if(g_nTrlEmuGraphicOn == 0)
		return;
#endif
	u32 nSize = g_pNesGrpReg2000->rSPRSize?16:8;
	u32 nCount = 0;
	nesSGrpSprData* pData = g_sNesGrpSprData;
	u32 nData = 0;

#if TRL_HVC_GRAPHIC
	g_nNesGrpSprBuf = 0;
	for(; nData<g_nNesGrpSprData; ++nData, ++pData)
	{
		// Clip
		u32 nY = pData->nY;
		if((g_nNesGrpLines < nY) || (g_nNesGrpLines >= (nY + nSize)))
			continue;
		++nCount;
		if(nCount>NES_GRP_SPRLINEMAX)
		{
			g_pNesGrpReg2002->rSPRLost = 1;
			break;
		}

		u32 nX = pData->nX;
		u32 nTX = 0;
		if(!g_pNesGrpReg2001->rSPRClip)
		{
			if(nX==0)
				continue;
			if(nX<8)
			{
				nTX = 8 - nX;
				nX = 8;
			}
		}

		// Get BitData
		u16 nBitData = pData->nBitData[g_nNesGrpLines - nY];	
		// Latch
		if(nesCardRegisterLatch)
			nesGrpRenderUpdateSPRforLatch(pData);
		if(nBitData==0)
			continue;

		// Render
		u8 nInfoFlag = NES_GRP_INFO_SPR;
		if(pData->nID == 0)
			nInfoFlag |= NES_GRP_INFO_SPR0;
		if(pData->nPrio)
			nInfoFlag |= NES_GRP_INFO_PRIO;

		u16* pPalBuf = g_pNesGrpPal + pData->nPal;
		u16* pBuf = &g_pNesGrpSprBuf[nX];
		u8* pInfo = &g_pNesGrpLineInfo[nX];
		u32 nXM = 8 - nTX + nX;
		if(nXM > NES_GRP_SX)
			nXM = 8 - (nXM - NES_GRP_SX);
		else
			nXM = 8;

		for(u32 tx=nTX; tx<nXM; ++tx, ++pBuf, ++pInfo)
		{
			if(*pInfo & NES_GRP_INFO_SPR)
				continue;

			u32 nColor = ((nBitData >> (7-tx)) & 0x1) | ((nBitData >> (14-tx)) & 0x2);
			if(nColor)
			{
				*pBuf = pPalBuf[nColor];
				*pInfo = nInfoFlag;
				g_nNesGrpSprBuf++;
			}
		}
	}
#else

#if	TRL_OBJ0_HIT_DELAY
	static u32 nHit = 0;
	if(nHit){
		g_pNesGrpReg2002->rSPRHit = 1;
		nHit=0;
	}
#endif
	// First Sprite
	while(pData->nID == 0)
	{
		// Clip
		u32 nY = pData->nY;
		if((g_nNesGrpLines < nY) || (g_nNesGrpLines >= (nY + nSize)))
		{
			++pData;
			++nData;
			break;
		}
		++nCount;

		u32 nX = pData->nX;
		u32 nTX = 0;
		if(!g_pNesGrpReg2001->rSPRClip)
		{
			if(nX==0)
			{
				++pData;
				++nData;
				break;
			}
			if(nX<8)
			{
				nTX = 8 - nX;
				nX = 8;
			}
		}

		// Get Bit Data
		u16 nBitData = pData->nBitData[g_nNesGrpLines - nY];
		if(nBitData!=0)
		{
			// Render
			u32 nPal = pData->nPal;
			u16* pBuf = &g_pNesGrpRenderBuf[nX]+NES_GRP_TEX_OFFSET;
			u8* pInfo = &g_pNesGrpLineInfo[nX]+NES_GRP_TEX_OFFSET;
#if	!TRL_OBJ0_HIT_DELAY
			u32 nHit = 0;	
#endif
			if(pData->nPrio)
			{
				for(; nTX<8; ++nTX, ++pBuf, ++pInfo, ++nX)
				{
					if(nX>=NES_GRP_SX)
						break;

					u32 nColor = ((nBitData >> (7-nTX)) & 0x1) | ((nBitData >> (14-nTX)) & 0x2);
					if(nColor)
					{
						if(*pInfo & NES_GRP_INFO_BG){
							nHit = 1;
						}
						else
							*pBuf = g_pNesGrpPal[nPal+nColor];
						*pInfo = NES_GRP_INFO_SPR;
					}
				}
			}
			else
			{
				for(; nTX<8; ++nTX, ++pBuf, ++pInfo, ++nX)
				{
					if(nX>=NES_GRP_SX)
						break;
					u32 nColor = ((nBitData >> (7-nTX)) & 0x1) | ((nBitData >> (14-nTX)) & 0x2);
					if(nColor)
					{
						if(*pInfo & NES_GRP_INFO_BG)
							nHit = 1;
						*pBuf = g_pNesGrpPal[nPal+nColor];
						*pInfo = NES_GRP_INFO_SPR;
					}
				}
			}
#if	!TRL_OBJ0_HIT_DELAY
			if(nHit)
				g_pNesGrpReg2002->rSPRHit = nHit;
#endif
		}

		// Update Latch
		if(nesCardRegisterLatch)
			nesGrpRenderUpdateSPRforLatch(pData);

		++pData;
		++nData;
		break;
	};

	// Other Sprite
	for(; nData<g_nNesGrpSprData; ++nData, ++pData)
	{
		// Clip
		u32 nY = pData->nY;
		if((g_nNesGrpLines < nY) || (g_nNesGrpLines >= (nY + nSize)))
			continue;
		++nCount;
		if(nCount>NES_GRP_SPRLINEMAX)
		{
			g_pNesGrpReg2002->rSPRLost = 1;
			if(nCount>g_nNesLineMaxSprite)
				break;
		}

		u32 nX = pData->nX;
		u32 nTX = 0;
		if(!g_pNesGrpReg2001->rSPRClip)
		{
			if(nX==0)
				continue;
			if(nX<8)
			{
				nTX = 8 - nX;
				nX = 8;
			}
		}

		// Get BitData
		u16 nBitData = pData->nBitData[g_nNesGrpLines - nY];	
		// Update Latch
		if(nesCardRegisterLatch)
			nesGrpRenderUpdateSPRforLatch(pData);
		if(nBitData==0)
			continue;

		// Render
		u16* pPalBuf = g_pNesGrpPal + pData->nPal;
		u16* pBuf = &g_pNesGrpRenderBuf[nX]+NES_GRP_TEX_OFFSET;
		u8* pInfo = &g_pNesGrpLineInfo[nX]+NES_GRP_TEX_OFFSET;
		u32 nXM = 8 - nTX + nX;
		if(nXM > NES_GRP_SX)
			nXM = 8 - (nXM - NES_GRP_SX);
		else
			nXM = 8;
		if(pData->nPrio)
		{
			for(; nTX<nXM; ++nTX, ++pBuf, ++pInfo)
			{
				if(*pInfo & NES_GRP_INFO_SPR)
					continue;

				u32 nColor = ((nBitData >> (7-nTX)) & 0x1) | ((nBitData >> (14-nTX)) & 0x2);
				if(nColor)
				{
					if(!(*pInfo & NES_GRP_INFO_BG))
						*pBuf = pPalBuf[nColor];
					*pInfo = NES_GRP_INFO_SPR;
				}
			}
		}
		else
		{
			for(; nTX<nXM; ++nTX, ++pBuf, ++pInfo)
			{
				if(*pInfo & NES_GRP_INFO_SPR)
					continue;
				u32 nColor = ((nBitData >> (7-nTX)) & 0x1) | ((nBitData >> (14-nTX)) & 0x2);
				if(nColor)
				{
					*pBuf = pPalBuf[nColor];
					*pInfo = NES_GRP_INFO_SPR;
				}
			}
		}
	}
#endif
}

#if TRL_HVC_GRAPHIC
/** @brief Render a Single Scanline */
inline void nesGrpRenderLine()
{
	u8* pInfo = g_pNesGrpLineInfo;
	u32 nHit = 0;
	for(u32 n=0; n<NES_GRP_SX; ++n, ++pInfo)
	{
		u8 nInfo = *pInfo;
		if(nInfo & NES_GRP_INFO_SPR)
		{
			if(nInfo & NES_GRP_INFO_SPR0)
			{
				if(nInfo & NES_GRP_INFO_BG)
				{
					nHit = 1;
					if(nInfo & NES_GRP_INFO_PRIO)
						continue;
				}
			}
			else
			{
				if(nInfo & NES_GRP_INFO_PRIO)
				{
					if(nInfo & NES_GRP_INFO_BG)
						continue;
				}
			}
			g_pNesGrpRenderBuf[n] = g_pNesGrpSprBuf[n];
		}
	}
	if(nHit)
		g_pNesGrpReg2002->rSPRHit = nHit;
}
#endif

/** @brief Update Ticks */
void nesGrpUpdate()
{
	if(g_nNesCardIRQEnable == NES_CARD_IRQ_SCANLINEV)
		nesCardUpdateIRQ();
	if(g_nNesGrpLines<=239)			// 0~239	Render
	{
		g_pNesGrpRenderBuf = &((u16*)g_pNesEmuBuf->pScreenBuf)[g_nNesGrpLines * g_pNesEmuBuf->nTexWidth];
		if(g_nNesGrpEnable)
		{
			if(g_nNesGrpLines == 0){
				g_nNesGrpVRAMAddr = g_nNesGrpRegReload;
//add by yuans
#if BG_OFFSETY_GT239
				if(((g_nNesGrpVRAMAddr>>5)&0x1F)>29)
					g_bATTenable=true;
				else
					g_bATTenable=false;
#endif
//end of add
			}
			else
				g_nNesGrpVRAMAddr = (g_nNesGrpVRAMAddr & 0xFBE0) | (g_nNesGrpRegReload & 0x041F);
			// Y Clip
			if((g_nNesGrpLines < g_pNesGrpClip[0]) || (g_nNesGrpLines >= g_pNesGrpClip[1]))
			{
				for(u32 x=0; x<NES_GRP_SCANLINE_XSIZE; ++x){
					g_pNesGrpRenderBuf[x] = 0x1;
				}
#if !TRL_FAKE_RENDER_CLIP
				g_pNesGrpRenderBuf = &((u16*)g_pNesEmuBuf->pScreenBuf)[(NES_GRP_SY+8) * g_pNesEmuBuf->nTexWidth];
				if(g_pNesGrpReg2001->rBGEnable)
					nesGrpRenderBG();
#if !TRL_HVC_GRAPHIC
				else
					memset(g_pNesGrpLineInfo, 0, NES_GRP_SX);
				if(g_pNesGrpReg2001->rSPREnable)
				{
					if(g_bNesGrpSPRChange)
						nesGrpUpdateSPR();
					if(g_nNesGrpSprData)
						nesGrpRenderSPR();
				}
#else
				if(g_nNesGrpSprBuf)
				{
					g_nNesGrpSprBuf = 0;
					nesGrpRenderLine();
				}
#endif
#endif
			}
			else
			{
				if(g_pNesGrpReg2001->rBGEnable)
					nesGrpRenderBG();
				else
				{
					for(u32 x=g_pNesGrpClip[2]; x<g_pNesGrpClip[3]; ++x)
						g_pNesGrpRenderBuf[x+NES_GRP_TEX_OFFSET] = g_pNesGrpPal[0];
#if !TRL_HVC_GRAPHIC
					memset(g_pNesGrpLineInfo, 0, NES_GRP_SX);
#endif
				}

#if TRL_HVC_GRAPHIC
				if(g_nNesGrpSprBuf)
				{
					g_nNesGrpSprBuf = 0;
					nesGrpRenderLine();
				}
#else
				if(g_pNesGrpReg2001->rSPREnable)
				{
					if(g_bNesGrpSPRChange)
						nesGrpUpdateSPR();
					if(g_nNesGrpSprData)
						nesGrpRenderSPR();
				}
#endif
				// X Clip
				for(u32 x=0; x<g_pNesGrpClip[2]; ++x)
					g_pNesGrpRenderBuf[x+NES_GRP_TEX_OFFSET] = 0x0001;
				for(u32 x=g_pNesGrpClip[3]; x<NES_GRP_SX; ++x)
					g_pNesGrpRenderBuf[x+NES_GRP_TEX_OFFSET] = 0x0001;
			}

#if TRL_HVC_GRAPHIC
			g_nNesGrpLines++;
			if(g_nNesGrpLines<=239)
			{
				memset(g_pNesGrpLineInfo, 0, NES_GRP_SX);
				if(g_pNesGrpReg2001->rSPREnable)
				{
					if(g_bNesGrpSPRChange)
						nesGrpUpdateSPR();
					if(g_nNesGrpSprData)
						nesGrpRenderSPR();
				}
			}
#endif

			if((g_nNesGrpVRAMAddr & 0x7000) == 0x7000)
			{
				g_nNesGrpVRAMAddr &= 0x8FFF;
				switch(g_nNesGrpVRAMAddr & 0x03E0)
				{
				case 0x03A0:
					g_nNesGrpVRAMAddr ^= 0x0800;
					g_nNesGrpVRAMAddr &= 0xFC1F;
					break;
				case 0x03E0:
					g_nNesGrpVRAMAddr &= 0xFC1F;
					break;
				default:
					g_nNesGrpVRAMAddr += 0x0020;
				}
			}
			else
				g_nNesGrpVRAMAddr += 0x1000;

			//if(g_nNesCardIRQEnable == NES_CARD_IRQ_SCANLINE)
			if(nesCardUpdateIRQ)
				//if(g_nNesCardIRQEnable != NES_CARD_IRQ_SCANLINEV && g_nNesCardIRQEnable!=NES_CARD_IRQ_CPUCYCLE)
				if(g_pNesROMHeader->nMapper!=100)
					nesCardUpdateIRQ();
#if !TRL_HVC_GRAPHIC
			g_nNesGrpLines++;
#endif
		}
		else
		{
			if(g_nNesGrpLines >= g_pNesGrpClip[0] && g_nNesGrpLines < g_pNesGrpClip[1])
				for(u32 x=g_pNesGrpClip[2]; x<g_pNesGrpClip[3]; ++x)
					g_pNesGrpRenderBuf[x+NES_GRP_TEX_OFFSET] = g_pNesGrpPal[0];
#if TRL_HVC_GRAPHIC
			memset(g_pNesGrpLineInfo, 0, NES_GRP_SX);
#endif
			g_nNesGrpLines++;
		}
#if TRL_HVC_NMI_LINE240
		if(g_nNesGrpLines == 240)
			if(g_pNesGrpReg2000->rNMI)
				g_nNesCpuNMIFlag = 1;
#endif
	}
	else if(g_nNesGrpLines == 240)	// 240		Render Finish
	{
#if !TRL_HVC_NMI_LINE240
		g_pNesGrpReg2002->rVBlank = 1;
#endif
		g_nNesBreakFlag = 1;
#if TRL_HVC_NMI_LINE240
		g_pNesGrpReg2002->rVBlank = 1;
#endif
		g_nNesGrpLines++;

	}
	else if(g_nNesGrpLines == 241)	// 241		VBlank Start
	{
#if !TRL_HVC_NMI_LINE240
		if(g_pNesGrpReg2000->rNMI)
			g_nNesCpuNMIFlag = 1;
#endif
		g_nNesGrpLines++;
	}
	else if(g_nNesGrpLines == 261)	// 261		VBlank Finish
	{
		g_nNesGrpReg[2] &= 0x1F;
		g_nNesGrpLines = 0;
#if TRL_HVC_GRAPHIC
		memset(g_pNesGrpLineInfo, 0, NES_GRP_SX);
		if(g_pNesGrpReg2001->rSPREnable)
		{
			if(g_bNesGrpSPRChange)
				nesGrpUpdateSPR();
			if(g_nNesGrpSprData)
				nesGrpRenderSPR();
		}
#endif
	}
	else							// 242~260	VBlank
	{
		g_nNesGrpLines++;
	}
}

/** @brief Read Data From PPU Register */
u8 nesGrpRegRead(u8 nAddr)
{
	switch(nAddr)
	{
	case 2:		// 2002h - PPU Status Register
		{
			u8 nTemp = g_nNesGrpReg[2];
			g_nNesGrpRegWriteFlag = 0;
			g_pNesGrpReg2002->rVBlank = 0;
			return nTemp;
		}
	case 4:		// 2004h - SPR-RAM Data Register
		//Comment by yuans: Fix SunSoft5 crash BUG...
		//if(g_pNesGrpReg2002->rVBlank)
			return g_pNesSPRRAM[g_nNesGrpSPRRAMAddr];
		//break;
	case 7:		// 2007h - VRAM Read Data Register
		{
			u8 nData;
			u16 nVRAMAddr = g_nNesGrpVRAMAddr & 0x3FFF;
			switch(nVRAMAddr >> 10)
			{
			case 0x0:				// 0000h-03FFh   Pattern Table 0 (1K) (64 Tiles)
				nData = g_nNesGrpVRAMBuffer;
				g_nNesGrpVRAMBuffer = g_pNesCHRBank[0][nVRAMAddr&0x3FF];
				break;
			case 0x1:				// 0400h-07FFh   Pattern Table 0 (1K) (64 Tiles)
				nData = g_nNesGrpVRAMBuffer;
				g_nNesGrpVRAMBuffer = g_pNesCHRBank[1][nVRAMAddr&0x3FF];
				break;
			case 0x2:				// 0800h-0CFFh   Pattern Table 0 (1K) (64 Tiles)
				nData = g_nNesGrpVRAMBuffer;
				g_nNesGrpVRAMBuffer = g_pNesCHRBank[2][nVRAMAddr&0x3FF];
				break;
			case 0x3:				// 0D00h-0FFFh   Pattern Table 0 (1K) (64 Tiles)
				nData = g_nNesGrpVRAMBuffer;
				g_nNesGrpVRAMBuffer = g_pNesCHRBank[3][nVRAMAddr&0x3FF];
				if(nesCardRegisterLatch)
				{
					switch(nVRAMAddr & 0x1FF0)
					{
					case 0x0FD0:
						nesGrpUpdateLatch(0, 1);
						break;
					case 0x0FE0:
						nesGrpUpdateLatch(0, 0);
						break;
					}
				}
				break;
			case 0x4:				// 1000h-13FFh   Pattern Table 1 (1K) (64 Tiles)
				nData = g_nNesGrpVRAMBuffer;
				g_nNesGrpVRAMBuffer = g_pNesCHRBank[4][nVRAMAddr&0x3FF];
				break;
			case 0x5:				// 1400h-17FFh   Pattern Table 1 (1K) (64 Tiles)
				nData = g_nNesGrpVRAMBuffer;
				g_nNesGrpVRAMBuffer = g_pNesCHRBank[5][nVRAMAddr&0x3FF];
				break;
			case 0x6:				// 1800h-1CFFh   Pattern Table 1 (1K) (64 Tiles)
				nData = g_nNesGrpVRAMBuffer;
				g_nNesGrpVRAMBuffer = g_pNesCHRBank[6][nVRAMAddr&0x3FF];
				break;
			case 0x7:				// 1D00h-1FFFh   Pattern Table 1 (1K) (64 Tiles)
				nData = g_nNesGrpVRAMBuffer;
				g_nNesGrpVRAMBuffer = g_pNesCHRBank[7][nVRAMAddr&0x3FF];
				if(nesCardRegisterLatch)
				{
					switch(nVRAMAddr & 0x1FF0)
					{
					case 0x1FD0:
						nesGrpUpdateLatch(1, 1);
						break;
					case 0x1FE0:
						nesGrpUpdateLatch(1, 0);
						break;
					}
				}
				break;
			case 0x8:				// 2000h-23FFh   Name Table 0 and Attribute Table 0 (1K) (32x30 BG Map)
			case 0xC:
				nData = g_nNesGrpVRAMBuffer;
				g_nNesGrpVRAMBuffer = g_pNesGrpNameTab[0][nVRAMAddr&0x3FF];
				break;
			case 0x9:				// 2400h-27FFh   Name Table 1 and Attribute Table 1 (1K) (32x30 BG Map)
			case 0xD:
				nData = g_nNesGrpVRAMBuffer;
				g_nNesGrpVRAMBuffer = g_pNesGrpNameTab[1][nVRAMAddr&0x3FF];
				break;
			case 0xA:				// 2800h-2BFFh   Name Table 2 and Attribute Table 2 (1K) (32x30 BG Map)
			case 0xE:
				nData = g_nNesGrpVRAMBuffer;
				g_nNesGrpVRAMBuffer = g_pNesGrpNameTab[2][nVRAMAddr&0x3FF];
				break;
			case 0xB:				// 2C00h-2FFFh   Name Table 3 and Attribute Table 3 (1K) (32x30 BG Map)
				nData = g_nNesGrpVRAMBuffer;
				g_nNesGrpVRAMBuffer = g_pNesGrpNameTab[3][nVRAMAddr&0x3FF];
				break;
			case 0xF:
				if(nVRAMAddr<0x3F00)	// 3000h-3EFFh   Mirror of 2C00h-2EFFh
				{
					nData = g_nNesGrpVRAMBuffer;
					g_nNesGrpVRAMBuffer = g_pNesGrpNameTab[3][nVRAMAddr&0x3FF];
				}
				else				// 3F00h-3FFFh   Background and Sprite Palettes (25 entries used)
					nData = g_pNesPALRAM[nVRAMAddr & 0x1F] & g_nNesGrpMonoFilter;
				break;
			}
			g_nNesGrpVRAMAddr += g_nNesGrpVRAMAddrInc;
			return nData;
		}
	}
	return 0x00;
}

/** @brief Write Data to PPU Register */
void nesGrpRegWrite(u8 nAddr, u8 nValue)
{
	//trlTraceSoundDetailWriteReg(nAddr + 0x2000, nValue);
	switch(nAddr)
	{
	case 0:		// 2000h - PPU Control Register 1
		{
			u8 nChange = g_nNesGrpReg[0] ^ nValue;
			g_nNesGrpReg[0] = nValue;
			g_nNesGrpRegReload = (g_nNesGrpRegReload & 0xF3FF)|((nValue & 0x03)<<10);

			if(nChange & 0x80)
			{
				if(g_pNesGrpReg2000->rNMI && g_pNesGrpReg2002->rVBlank)
				{
					if(g_nNesGrpLines > 241)
						g_nNesCpuNMIFlag = 1;
					g_nNesCpuEventTicks = g_nNesCpuTicks + 2;
				}
			}

			if(g_pNesGrpReg2000->rVRAMAddrInc)
				g_nNesGrpVRAMAddrInc = 32;
			else
				g_nNesGrpVRAMAddrInc = 1;

			if(g_nNesGrpPatternTabBG<8)
				g_nNesGrpPatternTabBG = g_pNesGrpReg2000->rPatternTabBG * 4;
			if(nChange & 0x08)
			{
				g_nNesGrpPatternTabSPR = g_pNesGrpReg2000->rPatternTabSPR * 4;
				g_bNesGrpSPRChange |= 0x2;
			}
		}
		break;
	case 1:		// 2001h - PPU Control Register 2
		{
			u8 nChange = g_nNesGrpReg[1] ^ nValue;
			g_nNesGrpReg[1] = nValue;
			if(nChange & 0xE1)
			{
				if(g_pNesGrpReg2001->rColorMode)
					g_nNesGrpMonoFilter = 0x30;
				else
					g_nNesGrpMonoFilter = 0x3F;
				switch(g_pNesGrpReg2001->rBGColor)
				{
				case 1:	// Red
					g_nNesGrpColorFilter = 1;
					break;
				case 2:	// Green
					g_nNesGrpColorFilter = 2;
					break;
				case 4:	// Blue
					g_nNesGrpColorFilter = 3;
					break;
				default:
					g_nNesGrpColorFilter = 0;
				}
				nesGrpUpdatePal();
			}
			if(nChange & 0x18)
			{
				//if((!g_nNesGrpEnable) && g_nNesGrpLines && (g_nNesGrpLines<240))
				//	g_nNesGrpVRAMAddr = g_nNesGrpRegReload;
				g_nNesGrpEnable = g_nNesGrpReg[1]&0x18;
				if(!g_nNesGrpEnable && (g_nNesGrpLines<240)){
					//SPR-RAM is dynamic memory, refreshed during rendering, it does no longer receive refresh cycles 
					//(and will lose its content) when the display is disabled (by clearing both Bit 3 and 4 in Port 2001h).
					memset(g_pNesSPRRAM, 0, 0x100);
					g_bNesGrpSPRChange = 1;
				}
			}
		}
		break;
	case 2:		// 2002h - PPU Status Register
		break;
	case 3:		// 2003h - SPR-RAM Address Register
		g_nNesGrpSPRRAMAddr = nValue;
		break;
	case 4:		// 2004h - SPR-RAM Data Register
		if(g_pNesGrpReg2002->rVBlank && (g_nNesGrpReg[1]&0x18))
		{
			g_pNesSPRRAM[g_nNesGrpSPRRAMAddr] = nValue;
			++g_nNesGrpSPRRAMAddr;
			g_bNesGrpSPRChange = 1;
		}
		break;
	case 5:		// 2005h - PPU Background Scrolling Offset
		if(g_nNesGrpRegWriteFlag)
			g_nNesGrpRegReload = (g_nNesGrpRegReload & 0x8C1F) | ((nValue & 0xF8)<<2) | ((nValue & 0x07)<<12);
		else
		{
			g_nNesGrpRegReload = (g_nNesGrpRegReload & 0xFFE0) | (nValue>>3);
			g_nNesGrpRegReloadX = nValue & 0x07;
		}
		g_nNesGrpRegWriteFlag = !g_nNesGrpRegWriteFlag;
		break;
	case 6:		// 2006h - VRAM Address Register
		if(g_nNesGrpRegWriteFlag)
		{
			g_nNesGrpRegReload = (g_nNesGrpRegReload & 0xFF00) | nValue;
			g_nNesGrpVRAMAddr = g_nNesGrpRegReload;
		}
		else
			g_nNesGrpRegReload = (g_nNesGrpRegReload & 0x00FF) | ((nValue & 0x3F)<<8);
		g_nNesGrpRegWriteFlag = !g_nNesGrpRegWriteFlag;
		break;
	case 7:		// 2007h - VRAM Write Data Register
		{
			u16 nVRAMAddr = g_nNesGrpVRAMAddr & 0x3FFF;
			trlTraceSoundDetailWriteReg(nVRAMAddr, nValue);
			switch(nVRAMAddr >> 10)
			{
			case 0x0:				// 0000h-03FFh   Pattern Table 0 (1K) (64 Tiles)
				if(g_nPPUCHRRAM&(1<<(nVRAMAddr>>10))){
					g_pNesCHRBank[0][nVRAMAddr&0x3FF] = nValue;
					g_bNesGrpSPRChange |= 2;
				}
				break;
			case 0x1:				// 0400h-07FFh   Pattern Table 0 (1K) (64 Tiles)
				if(g_nPPUCHRRAM&(1<<(nVRAMAddr>>10))){
					g_pNesCHRBank[1][nVRAMAddr&0x3FF] = nValue;
					g_bNesGrpSPRChange |= 2;
				}
				break;
			case 0x2:				// 0800h-0BFFh   Pattern Table 0 (1K) (64 Tiles)
				if(g_nPPUCHRRAM&(1<<(nVRAMAddr>>10))){
					g_pNesCHRBank[2][nVRAMAddr&0x3FF] = nValue;
					g_bNesGrpSPRChange |= 2;
				}
				break;
			case 0x3:				// 0C00h-0FFFh   Pattern Table 0 (1K) (64 Tiles)
				if(g_nPPUCHRRAM&(1<<(nVRAMAddr>>10))){
					g_pNesCHRBank[3][nVRAMAddr&0x3FF] = nValue;
					g_bNesGrpSPRChange |= 2;
					if(nesCardRegisterLatch)
					{
						switch(nVRAMAddr & 0x1FF0)
						{
						case 0x0FD0:
							nesGrpUpdateLatch(0, 1);
							break;
						case 0x0FE0:
							nesGrpUpdateLatch(0, 0);
							break;
						}
					}
				}
				break;
			case 0x4:				// 1000h-13FFh   Pattern Table 1 (1K) (64 Tiles)
				if(g_nPPUCHRRAM&(1<<(nVRAMAddr>>10))){
					g_pNesCHRBank[4][nVRAMAddr&0x3FF] = nValue;
					g_bNesGrpSPRChange |= 2;
				}
				break;
			case 0x5:				// 1400h-17FFh   Pattern Table 1 (1K) (64 Tiles)
				if(g_nPPUCHRRAM&(1<<(nVRAMAddr>>10))){
					g_pNesCHRBank[5][nVRAMAddr&0x3FF] = nValue;
					g_bNesGrpSPRChange |= 2;
				}
				break;
			case 0x6:				// 1800h-1CFFh   Pattern Table 1 (1K) (64 Tiles)
				if(g_nPPUCHRRAM&(1<<(nVRAMAddr>>10))){
					g_pNesCHRBank[6][nVRAMAddr&0x3FF] = nValue;
					g_bNesGrpSPRChange |= 2;
				}
				break;
			case 0x7:				// 1D00h-1FFFh   Pattern Table 1 (1K) (64 Tiles)
				if(g_nPPUCHRRAM&(1<<(nVRAMAddr>>10))){
					g_pNesCHRBank[7][nVRAMAddr&0x3FF] = nValue;
					g_bNesGrpSPRChange |= 2;
					if(nesCardRegisterLatch)
					{
						switch(nVRAMAddr & 0x1FF0)
						{
						case 0x1FD0:
							nesGrpUpdateLatch(1, 1);
							break;
						case 0x1FE0:
							nesGrpUpdateLatch(1, 0);
							break;
						}
					}
				}
				break;
			case 0x8:				// 2000h-23FFh   Name Table 0 and Attribute Table 0 (1K) (32x30 BG Map)
			case 0xC:
				g_pNesGrpNameTab[0][nVRAMAddr&0x3FF] = nValue;
				break;
			case 0x9:				// 2400h-27FFh   Name Table 1 and Attribute Table 1 (1K) (32x30 BG Map)
			case 0xD:
				g_pNesGrpNameTab[1][nVRAMAddr&0x3FF] = nValue;
				break;
			case 0xA:				// 2800h-2BFFh   Name Table 2 and Attribute Table 2 (1K) (32x30 BG Map)
			case 0xE:
				g_pNesGrpNameTab[2][nVRAMAddr&0x3FF] = nValue;
				break;
			case 0xB:				// 2C00h-2FFFh   Name Table 3 and Attribute Table 3 (1K) (32x30 BG Map)
				g_pNesGrpNameTab[3][nVRAMAddr&0x3FF] = nValue;
				break;
			case 0xF:
				if(nVRAMAddr<0x3F00)	// 3000h-3EFFh   Mirror of 2C00h-2EFFh
					g_pNesGrpNameTab[3][nVRAMAddr&0x3FF] = nValue;
				else				// 3F00h-3FFFh   Background and Sprite Palettes (25 entries used)
				{
					u32 nIndex = nVRAMAddr & 0x1F;
					if(g_pNesPALRAM[nIndex] != nValue)
					{
						if((nIndex&0x0F) == 0)
						{
							g_pNesPALRAM[0] = nValue;
							
							if(g_nNesGrpColorFilter == 0)
								g_pNesGrpPal[0] = g_nNesGrpPalTable[nValue & g_nNesGrpMonoFilter];// & g_nNesGrpColorFilter;
							else{
								u32 r,g,b;
								r=((g_nNesGrpPalTable[nValue & g_nNesGrpMonoFilter] )>>11)&0x1F;
								g=((g_nNesGrpPalTable[nValue & g_nNesGrpMonoFilter] )>>6 )&0x1F;
								b=((g_nNesGrpPalTable[nValue & g_nNesGrpMonoFilter] )>>1 )&0x1F;

								r=(u32)((r<<15)*rtmul[g_nNesGrpColorFilter])>>15;
								g=(u32)((g<<15)*gtmul[g_nNesGrpColorFilter])>>15;
								b=(u32)((b<<15)*btmul[g_nNesGrpColorFilter])>>15;

								if(r>0x1F)
									r=0x1F;
								if(g>0x1F)
									g=0x1F;
								if(b>0x1F)
									b=0x1F;

								g_pNesGrpPal[0]=((r<<11)|(g<<6))|((b<<1)|(0x1));
							}
							for(u32 n=4; n<0x20; n+=4)
							{
								g_pNesPALRAM[n] = g_pNesPALRAM[0];
								g_pNesGrpPal[n] = g_pNesGrpPal[0];
							}
						}
						else if(nIndex&0x03)
						{
							g_pNesPALRAM[nIndex] = nValue;

							if(g_nNesGrpColorFilter == 0)
								g_pNesGrpPal[nIndex] = g_nNesGrpPalTable[nValue & g_nNesGrpMonoFilter];// & g_nNesGrpColorFilter;
							else{
								u32 r,g,b;
								r=((g_nNesGrpPalTable[nValue & g_nNesGrpMonoFilter] )>>11)&0x1F;
								g=((g_nNesGrpPalTable[nValue & g_nNesGrpMonoFilter] )>>6 )&0x1F;
								b=((g_nNesGrpPalTable[nValue & g_nNesGrpMonoFilter] )>>1 )&0x1F;

								r=(u32)((r<<15)*rtmul[g_nNesGrpColorFilter])>>15;
								g=(u32)((g<<15)*gtmul[g_nNesGrpColorFilter])>>15;
								b=(u32)((b<<15)*btmul[g_nNesGrpColorFilter])>>15;

								if(r>0x1F)
									r=0x1F;
								if(g>0x1F)
									g=0x1F;
								if(b>0x1F)
									b=0x1F;

								g_pNesGrpPal[nIndex]=((r<<11)|(g<<6))|((b<<1)|(0x1));
							}
							
						}
					}
				}
				break;
			}
			g_nNesGrpVRAMAddr += g_nNesGrpVRAMAddrInc;
		}
		break;
	}
}

/** @brief Change the Name Table Mapping */
void nesGrpChangeNameTabMap(u32 nMapping)
{
	g_nNesGrpNameTabMapping = nMapping;
	switch(g_nNesGrpNameTabMapping)
	{
	case NES_GRP_MAP_AUTO:		// Card Auto Control
		g_pNesGrpNameTab[0] = g_pNesGrpNameTab[2] = g_pNesVRAM;
		g_pNesGrpNameTab[1] = g_pNesGrpNameTab[3] = g_pNesVRAM + 0x400;
		break;
	case NES_GRP_MAP_HORI:		// Horizontal Mirroring
		g_pNesGrpNameTab[0] = g_pNesGrpNameTab[1] = g_pNesVRAM;
		g_pNesGrpNameTab[2] = g_pNesGrpNameTab[3] = g_pNesVRAM + 0x400;
		break;
	case NES_GRP_MAP_VERT:		// Vertical Mirroring
		g_pNesGrpNameTab[0] = g_pNesGrpNameTab[2] = g_pNesVRAM;
		g_pNesGrpNameTab[1] = g_pNesGrpNameTab[3] = g_pNesVRAM + 0x400;
		break;
	case NES_GRP_MAP_SINGLE0:	// Single Screen 0
		g_pNesGrpNameTab[0] = g_pNesGrpNameTab[1] = g_pNesGrpNameTab[2] = g_pNesGrpNameTab[3] = g_pNesVRAM;
		break;
	case NES_GRP_MAP_SINGLE1:	// Single Screen 1
		g_pNesGrpNameTab[0] = g_pNesGrpNameTab[1] = g_pNesGrpNameTab[2] = g_pNesGrpNameTab[3] = g_pNesVRAM + 0x400;
		break;
	case NES_GRP_MAP_EXTEND:	// Card Extend Control
		break;
	}
}

/** @brief Change the BG Render */
void nesGrpChangeRenderBG(u32 nMode)
{
	switch(nMode)
	{
	case NES_GRP_BG_NORMAL:
		nesGrpRenderBG = nesGrpRenderBGNormal;
		break;
	case NES_GRP_BG_LATCH:
		nesGrpRenderBG = nesGrpRenderBGLatch;
		break;
	case NES_GRP_BG_MMC5:
		nesGrpRenderBG = nesGrpRenderBGMMC5;
		break;
	}
}
