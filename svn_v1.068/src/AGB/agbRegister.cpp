/**
 * @file agbRegister.cpp
 * @author Chentian
 * @date 2009.11.23
 * @brief AGB Emulate For CTR - Register
 */
#include "agbRegister.h"
#include "agbGraphic.h"
#include "agbSound.h"
#include "agbTime.h"
#include "agbDMA.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
const u32			g_nAgbRegSize = 0x400;		///< I/O and Registers Count
u8*					g_pAgbRegMask = NULL;		///< I/O and Registers Mask Code
u8*					g_pAgbRegWrite = NULL;		///< I/O and Registers Write Only Code
u8*					g_pAgbRegRead = NULL;		///< I/O and Registers Read Only Code
u16					g_nAgbRegLast = 0;			///< I/O and Registers Last Value
agbSRegDISPCNT*		g_pAgbDispCnt = NULL;		///< 0x000
agbSRegDISPSTAT*	g_pAgbDispStat = NULL;		///< 0x004
agbSRegVCOUNT*		g_pAgbVCount = NULL;		///< 0x006
agbSRegBGCNT*		g_pAgbBGCnt[4] = {0,0,0,0};	///< 0x008, 0x00A, 0x00C, 0x00E
agbSRegBGOFS*		g_pAgbBGHofs[4] = {0,0,0,0};///< 0x010, 0x014, 0x018, 0x01C
agbSRegBGOFS*		g_pAgbBGVofs[4] = {0,0,0,0};///< 0x012, 0x016, 0x01A, 0x01E
u16*				g_pAgbBGPA[2] = {0,0};		///< 0x020, 0x030
u16*				g_pAgbBGPB[2] = {0,0};		///< 0x022, 0x032
u16*				g_pAgbBGPC[2] = {0,0};		///< 0x024, 0x034
u16*				g_pAgbBGPD[2] = {0,0};		///< 0x026, 0x036
agbSRegBGSP*		g_pAgbBGX[2] = {0,0};		///< 0x028, 0x038
agbSRegBGSP*		g_pAgbBGY[2] = {0,0};		///< 0x02C, 0x03C
agbSRegWINCOORD*	g_pAgbWINH[2] = {0,0};		///< 0x040, 0x044
agbSRegWINCOORD*	g_pAgbWINV[2] = {0,0};		///< 0x042, 0x046
agbSRegWINCNT*		g_pAgbWININ = NULL;			///< 0x048
agbSRegWINCNT*		g_pAgbWINOUT = NULL;		///< 0x04A
agbSRegMOSAIC*		g_pAgbMosaic = NULL;		///< 0x04C
agbSRegBLDCNT*		g_pAgbBLDCnt = NULL;		///< 0x050
agbSRegBLDALPHA*	g_pAgbBLDAlpha = NULL;		///< 0x052
agbSRegBLDY*		g_pAgbBLDY = NULL;			///< 0x054
agbSRegSOUND1CNTL*	g_pAgbSound1CntL = NULL;	///< 0x060
agbSRegSOUNDXCNT12*	g_pAgbSound1CntH = NULL;	///< 0x062
agbSRegSOUNDXCNT34*	g_pAgbSound1CntX = NULL;	///< 0x064
agbSRegSOUNDXCNT12*	g_pAgbSound2CntL = NULL;	///< 0x068
agbSRegSOUNDXCNT34*	g_pAgbSound2CntH = NULL;	///< 0x06C
agbSRegSOUND3CNTL*	g_pAgbSound3CntL = NULL;	///< 0x070
agbSRegSOUND3CNTH*	g_pAgbSound3CntH = NULL;	///< 0x072
agbSRegSOUNDXCNT34*	g_pAgbSound3CntX = NULL;	///< 0x074
agbSRegSOUNDXCNT12*	g_pAgbSound4CntL = NULL;	///< 0x078
agbSRegSOUND4CNTH*	g_pAgbSound4CntH = NULL;	///< 0x07C
agbSRegSOUNDCNTL*	g_pAgbSoundCntL = NULL;		///< 0x080
agbSRegSOUNDCNTH*	g_pAgbSoundCntH = NULL;		///< 0x082
agbSRegSOUNDCNTX*	g_pAgbSoundCntX = NULL;		///< 0x084
agbSRegSOUNDBIAS*	g_pAgbSoundBias = NULL;		///< 0x088
agbSRegWAVERAM*		g_pAgbWaveRam0L = NULL;		///< 0x090
agbSRegWAVERAM*		g_pAgbWaveRam0H = NULL;		///< 0x092
agbSRegWAVERAM*		g_pAgbWaveRam1L = NULL;		///< 0x094
agbSRegWAVERAM*		g_pAgbWaveRam1H = NULL;		///< 0x096
agbSRegWAVERAM*		g_pAgbWaveRam2L = NULL;		///< 0x098
agbSRegWAVERAM*		g_pAgbWaveRam2H = NULL;		///< 0x09A
agbSRegWAVERAM*		g_pAgbWaveRam3L = NULL;		///< 0x09C
agbSRegWAVERAM*		g_pAgbWaveRam3H = NULL;		///< 0x09E
agbSRegFIFO*		g_pAgbFifoA = NULL;			///< 0x0A0
agbSRegFIFO*		g_pAgbFifoB = NULL;			///< 0x0A4
agbSRegDMAAddr27*	g_pAgbDMA0Sad = NULL;		///< 0x0B0
agbSRegDMAAddr27*	g_pAgbDMA0Dad = NULL;		///< 0x0B4
agbSRegDMACNTL*		g_pAgbDMA0Count = NULL;		///< 0x0B8
agbSRegDMACNTH*		g_pAgbDMACnt[4] = {0,0,0,0};///< 0x0BA, 0x0C6, 0x0D2£¬0x0DE
agbSRegDMAAddr28*	g_pAgbDMA1Sad = NULL;		///< 0x0BC
agbSRegDMAAddr27*	g_pAgbDMA1Dad = NULL;		///< 0x0C0
agbSRegDMACNTL*		g_pAgbDMA1Count = NULL;		///< 0x0C4
agbSRegDMAAddr28*	g_pAgbDMA2Sad = NULL;		///< 0x0C8
agbSRegDMAAddr27*	g_pAgbDMA2Dad = NULL;		///< 0x0CC
agbSRegDMACNTL*		g_pAgbDMA2Count = NULL;		///< 0x0D0
agbSRegDMAAddr28*	g_pAgbDMA3Sad = NULL;		///< 0x0D4
agbSRegDMAAddr28*	g_pAgbDMA3Dad = NULL;		///< 0x0D8
u16*				g_pAgbDMA3Count = NULL;		///< 0x0DC
u16*				g_pAgbTMCntL[4] = {0,0,0,0};///< 0x100, 0x104, 0x108, 0x10C
agbSRegTMCNT*		g_pAgbTMCntH[4] = {0,0,0,0};///< 0x102, 0x106, 0x10A, 0x10E
agbSRegKEYINPUT*	g_pAgbKeyInput = NULL;		///< 0x130
agbSRegKEYCNT*		g_pAgbKeyCnt = NULL;		///< 0x132
agbSRegINT*			g_pAgbIE = NULL;			///< 0x200
agbSRegINT*			g_pAgbIF = NULL;			///< 0x202
agbSRegWAITCNT*		g_pAgbWaitCnt = NULL;		///< 0x204
agbSRegIME*			g_pAgbIME = NULL;			///< 0x208
agbSRegHALTCNT*		g_pAgbHaltCnt = NULL;		///< 0x300
const u16			g_nAgbRegMaskTable[176] = {	///< I/O and Registers Mask Code Table
	0xFFFF, 0xFFFF, 0xFF3F, 0x00FF, 0xDFCF, 0xDFCF, 0xFFCF, 0xFFCF,		// 00
	0x01FF, 0x01FF, 0x01FF, 0x01FF, 0x01FF, 0x01FF, 0x01FF, 0x01FF,		// 01
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0FFF, 0xFFFF, 0x0FFF,		// 02
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0FFF, 0xFFFF, 0x0FFF,		// 03
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x3F3F, 0x3F3F, 0xFFFF, 0xFFFF,		// 04
	0x3FFF, 0x1F1F, 0x001F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,		// 05
	0x007F, 0xFFFF, 0xC7FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xC7FF, 0xFFFF,		// 06
	0x00E0, 0xE0FF, 0xC7FF, 0xFFFF, 0xFF3F, 0xFFFF, 0xC0FF, 0xFFFF,		// 07
	0xFF77, 0xFF0F, 0x008F, 0xFFFF, 0xC3FF, 0xFFFF, 0xFFFF, 0xFFFF,		// 08
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,		// 09
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,		// 0A
	0xFFFF, 0x07FF, 0xFFFF, 0x07FF, 0x3FFF, 0xF7E0, 0xFFFF, 0x0FFF,		// 0B
	0xFFFF, 0x07FF, 0x3FFF, 0xF7E0, 0xFFFF, 0x0FFF, 0xFFFF, 0x07FF,		// 0C
	0x3FFF, 0xF7E0, 0xFFFF, 0x0FFF, 0xFFFF, 0x0FFF, 0xFFFF, 0xFFE0,		// 0D
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,		// 0E
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,		// 0F
	0xFFFF, 0x00C7, 0xFFFF, 0x00C7, 0xFFFF, 0x00C7, 0xFFFF, 0x00C7,		// 10
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,		// 11
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x7FFF, 0x00FF, 0xFFFF, 0xFFFF,		// 12
	0x03FF, 0xC3FF, 0xC1FF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,		// 13
	0x0047, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,		// 14
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x003A, 0xFFFF, 0xFFFF, 0xFFFF, };	// 15
const u16			g_nAgbRegReadTable[112] = {	///< I/O and Registers Write Only Code Table
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 	// 00
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 	// 01
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 	// 02
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 	// 03
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 	// 04
	0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 	// 05
	0xFFFF, 0xFFC0, 0x7800, 0xFFFF, 0xFFC0, 0xFFFF, 0x7800, 0xFFFF, 	// 06
	0xFFFF, 0xFF00, 0x7800, 0xFFFF, 0xFFC0, 0xFFFF, 0x7FFF, 0xFFFF, 	// 07
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 	// 08
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 	// 09
	0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 	// 0A
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 	// 0B
	0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 	// 0C
	0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, };	// 0D
const s32			g_nAgbRegCoefficient[] = {	///< Coefficients for Color Special Effects
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 
	16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};
//@}

/** @brief Initialize Registers */
void agbRegInit()
{
	// Initialize Mask Table
	g_pAgbRegMask = (u8*)trlMemAlloc(g_nAgbRegSize);
	trlMemCopy(g_pAgbRegMask, g_nAgbRegMaskTable, 352);
	memset(&g_pAgbRegMask[352], 0xFF, g_nAgbRegSize-352);
	g_pAgbRegMask[0x201] = 0x3F;
	g_pAgbRegMask[0x203] = 0x3F;
	g_pAgbRegMask[0x205] = 0xDF;
	g_pAgbRegMask[0x208] = 0x01;
	g_pAgbRegMask[0x209] = 0x00;
	g_pAgbRegMask[0x300] = 0x01;
	g_pAgbRegMask[0x301] = 0x80;
	// Initialize Write Only Table
	g_pAgbRegWrite = (u8*)trlMemAlloc(g_nAgbRegSize);
	trlMemCopy(g_pAgbRegWrite, g_nAgbRegReadTable, 224);
	memset(&g_pAgbRegWrite[224], 0xFF, g_nAgbRegSize-224);
	// Initialize Read Only Table
	g_pAgbRegRead = (u8*)trlMemAlloc(g_nAgbRegSize);
	memset(g_pAgbRegRead, 0xFF, g_nAgbRegSize);
	g_pAgbRegRead[0x004] = 0xF8;
	g_pAgbRegRead[0x006] = 0x00;
	g_pAgbRegRead[0x084] = 0xF0;
	g_pAgbRegRead[0x205] = 0x7F;
	// Set Register Point
	g_pAgbDispCnt = (agbSRegDISPCNT*)(&g_pAgbREG[0x000]);
	g_pAgbDispStat = (agbSRegDISPSTAT*)(&g_pAgbREG[0x004]);
	g_pAgbVCount = (agbSRegVCOUNT*)(&g_pAgbREG[0x006]);
	g_pAgbBGCnt[0] = (agbSRegBGCNT*)(&g_pAgbREG[0x008]);
	g_pAgbBGCnt[1] = (agbSRegBGCNT*)(&g_pAgbREG[0x00A]);
	g_pAgbBGCnt[2] = (agbSRegBGCNT*)(&g_pAgbREG[0x00C]);
	g_pAgbBGCnt[3] = (agbSRegBGCNT*)(&g_pAgbREG[0x00E]);
	g_pAgbBGHofs[0] = (agbSRegBGOFS*)(&g_pAgbREG[0x010]);
	g_pAgbBGVofs[0] = (agbSRegBGOFS*)(&g_pAgbREG[0x012]);
	g_pAgbBGHofs[1] = (agbSRegBGOFS*)(&g_pAgbREG[0x014]);
	g_pAgbBGVofs[1] = (agbSRegBGOFS*)(&g_pAgbREG[0x016]);
	g_pAgbBGHofs[2] = (agbSRegBGOFS*)(&g_pAgbREG[0x018]);
	g_pAgbBGVofs[2] = (agbSRegBGOFS*)(&g_pAgbREG[0x01A]);
	g_pAgbBGHofs[3] = (agbSRegBGOFS*)(&g_pAgbREG[0x01C]);
	g_pAgbBGVofs[3] = (agbSRegBGOFS*)(&g_pAgbREG[0x01E]);
	g_pAgbBGPA[0] = (u16*)(&g_pAgbREG[0x020]);
	g_pAgbBGPB[0] = (u16*)(&g_pAgbREG[0x022]);
	g_pAgbBGPC[0] = (u16*)(&g_pAgbREG[0x024]);
	g_pAgbBGPD[0] = (u16*)(&g_pAgbREG[0x026]);
	g_pAgbBGX[0] = (agbSRegBGSP*)(&g_pAgbREG[0x028]);
	g_pAgbBGY[0] = (agbSRegBGSP*)(&g_pAgbREG[0x02C]);
	g_pAgbBGPA[1] = (u16*)(&g_pAgbREG[0x030]);
	g_pAgbBGPB[1] = (u16*)(&g_pAgbREG[0x032]);
	g_pAgbBGPC[1] = (u16*)(&g_pAgbREG[0x034]);
	g_pAgbBGPD[1] = (u16*)(&g_pAgbREG[0x036]);
	g_pAgbBGX[1] = (agbSRegBGSP*)(&g_pAgbREG[0x038]);
	g_pAgbBGY[1] = (agbSRegBGSP*)(&g_pAgbREG[0x03C]);
	g_pAgbWINH[0] = (agbSRegWINCOORD*)(&g_pAgbREG[0x040]);
	g_pAgbWINH[1] = (agbSRegWINCOORD*)(&g_pAgbREG[0x042]);
	g_pAgbWINV[0] = (agbSRegWINCOORD*)(&g_pAgbREG[0x044]);
	g_pAgbWINV[1] = (agbSRegWINCOORD*)(&g_pAgbREG[0x046]);
	g_pAgbWININ = (agbSRegWINCNT*)(&g_pAgbREG[0x048]);
	g_pAgbWINOUT = (agbSRegWINCNT*)(&g_pAgbREG[0x04A]);
	g_pAgbMosaic = (agbSRegMOSAIC*)(&g_pAgbREG[0x04C]);
	g_pAgbBLDCnt = (agbSRegBLDCNT*)(&g_pAgbREG[0x050]);
	g_pAgbBLDAlpha = (agbSRegBLDALPHA*)(&g_pAgbREG[0x052]);
	g_pAgbBLDY = (agbSRegBLDY*)(&g_pAgbREG[0x054]);
	g_pAgbSound1CntL = (agbSRegSOUND1CNTL*)(&g_pAgbREG[0x060]);
	g_pAgbSound1CntH = (agbSRegSOUNDXCNT12*)(&g_pAgbREG[0x062]);
	g_pAgbSound1CntX = (agbSRegSOUNDXCNT34*)(&g_pAgbREG[0x064]);
	g_pAgbSound2CntL = (agbSRegSOUNDXCNT12*)(&g_pAgbREG[0x068]);
	g_pAgbSound2CntH = (agbSRegSOUNDXCNT34*)(&g_pAgbREG[0x06C]);
	g_pAgbSound3CntL = (agbSRegSOUND3CNTL*)(&g_pAgbREG[0x070]);
	g_pAgbSound3CntH = (agbSRegSOUND3CNTH*)(&g_pAgbREG[0x072]);
	g_pAgbSound3CntX = (agbSRegSOUNDXCNT34*)(&g_pAgbREG[0x074]);
	g_pAgbSound4CntL = (agbSRegSOUNDXCNT12*)(&g_pAgbREG[0x078]);
	g_pAgbSound4CntH = (agbSRegSOUND4CNTH*)(&g_pAgbREG[0x07C]);
	g_pAgbSoundCntL = (agbSRegSOUNDCNTL*)(&g_pAgbREG[0x080]);
	g_pAgbSoundCntH = (agbSRegSOUNDCNTH*)(&g_pAgbREG[0x082]);
	g_pAgbSoundCntX = (agbSRegSOUNDCNTX*)(&g_pAgbREG[0x084]);
	g_pAgbSoundBias = (agbSRegSOUNDBIAS*)(&g_pAgbREG[0x088]);
	g_pAgbWaveRam0L = (agbSRegWAVERAM*)(&g_pAgbREG[0x090]);
	g_pAgbWaveRam0H = (agbSRegWAVERAM*)(&g_pAgbREG[0x092]);
	g_pAgbWaveRam1L = (agbSRegWAVERAM*)(&g_pAgbREG[0x094]);
	g_pAgbWaveRam1H = (agbSRegWAVERAM*)(&g_pAgbREG[0x096]);
	g_pAgbWaveRam2L = (agbSRegWAVERAM*)(&g_pAgbREG[0x098]);
	g_pAgbWaveRam2H = (agbSRegWAVERAM*)(&g_pAgbREG[0x09A]);
	g_pAgbWaveRam3L = (agbSRegWAVERAM*)(&g_pAgbREG[0x09C]);
	g_pAgbWaveRam3H = (agbSRegWAVERAM*)(&g_pAgbREG[0x09E]);
	g_pAgbFifoA = (agbSRegFIFO*)(&g_pAgbREG[0x0A0]);
	g_pAgbFifoB = (agbSRegFIFO*)(&g_pAgbREG[0x0A4]);
	g_pAgbDMA0Sad = (agbSRegDMAAddr27*)(&g_pAgbREG[0x0B0]);
	g_pAgbDMA0Dad = (agbSRegDMAAddr27*)(&g_pAgbREG[0x0B4]);
	g_pAgbDMA0Count = (agbSRegDMACNTL*)(&g_pAgbREG[0x0B8]);
	g_pAgbDMACnt[0] = (agbSRegDMACNTH*)(&g_pAgbREG[0x0BA]);
	g_pAgbDMA1Sad = (agbSRegDMAAddr28*)(&g_pAgbREG[0x0BC]);
	g_pAgbDMA1Dad = (agbSRegDMAAddr27*)(&g_pAgbREG[0x0C0]);
	g_pAgbDMA1Count = (agbSRegDMACNTL*)(&g_pAgbREG[0x0C4]);
	g_pAgbDMACnt[1] = (agbSRegDMACNTH*)(&g_pAgbREG[0x0C6]);
	g_pAgbDMA2Sad = (agbSRegDMAAddr28*)(&g_pAgbREG[0x0C8]);
	g_pAgbDMA2Dad = (agbSRegDMAAddr27*)(&g_pAgbREG[0x0CC]);
	g_pAgbDMA2Count = (agbSRegDMACNTL*)(&g_pAgbREG[0x0D0]);
	g_pAgbDMACnt[2] = (agbSRegDMACNTH*)(&g_pAgbREG[0x0D2]);
	g_pAgbDMA3Sad = (agbSRegDMAAddr28*)(&g_pAgbREG[0x0D4]);
	g_pAgbDMA3Dad = (agbSRegDMAAddr28*)(&g_pAgbREG[0x0D8]);
	g_pAgbDMA3Count = (u16*)(&g_pAgbREG[0x0DC]);
	g_pAgbDMACnt[3] = (agbSRegDMACNTH*)(&g_pAgbREG[0x0DE]);
	g_pAgbTMCntL[0] = (u16*)(&g_pAgbREG[0x100]);
	g_pAgbTMCntH[0] = (agbSRegTMCNT*)(&g_pAgbREG[0x102]);
	g_pAgbTMCntL[1] = (u16*)(&g_pAgbREG[0x104]);
	g_pAgbTMCntH[1] = (agbSRegTMCNT*)(&g_pAgbREG[0x106]);
	g_pAgbTMCntL[2] = (u16*)(&g_pAgbREG[0x108]);
	g_pAgbTMCntH[2] = (agbSRegTMCNT*)(&g_pAgbREG[0x10A]);
	g_pAgbTMCntL[3] = (u16*)(&g_pAgbREG[0x10C]);
	g_pAgbTMCntH[3] = (agbSRegTMCNT*)(&g_pAgbREG[0x10E]);
	g_pAgbKeyInput = (agbSRegKEYINPUT*)(&g_pAgbREG[0x130]);
	g_pAgbKeyCnt = (agbSRegKEYCNT*)(&g_pAgbREG[0x132]);
	g_pAgbIE = (agbSRegINT*)(&g_pAgbREG[0x200]);
	g_pAgbIF = (agbSRegINT*)(&g_pAgbREG[0x202]);
	g_pAgbWaitCnt = (agbSRegWAITCNT*)(&g_pAgbREG[0x204]);
	g_pAgbIME = (agbSRegIME*)(&g_pAgbREG[0x208]);
	g_pAgbHaltCnt = (agbSRegHALTCNT*)(&g_pAgbREG[0x300]);

	agbRegReset();
}

/** @brief Reset Registers */
void agbRegReset()
{
	g_pAgbREG[0x000] = 0x80;
	g_pAgbREG[0x021] = 0x01;
	g_pAgbREG[0x027] = 0x01;
	g_pAgbREG[0x031] = 0x01;
	g_pAgbREG[0x037] = 0x01;
	g_pAgbREG[0x089] = 0x02;
	g_pAgbREG[0x130] = 0xFF;
	g_pAgbREG[0x131] = 0x03;
}

/** @brief A 16 Bits Signed Fixed-Point Number Transform To A s32 Number */
inline s32 agbRegF16toS32(u16 nFixed)
{
	if(nFixed & 0x8000)
		return nFixed | 0xFFFF8000;
	else
		return nFixed;
}

/** @brief A 28 Bits Signed Fixed-Point Number Transform To A s32 Number */
inline s32 agbRegF28toS32(u32 nFixed)
{
	if(nFixed & 0x08000000)
		return nFixed | 0xF8000000;
	else
		return nFixed;
}

static u16 g_tRegUpdateTemp = 0;
/** @brief Update Registers */
inline void agbRegUpdate(u32 nAddr)
{
	switch(nAddr)
	{
	case 0x300:
		g_pAgbHaltCnt->rHalt = 1;
		break;
	case 0x000:
		if((*((u16*)&g_pAgbREG[0x000])^g_nAgbRegLast) & 0x0F07)
			g_nAgbGrpBGLayerChange = 1;
		g_nAgbGrpWinEnable = *((u16*)&g_pAgbREG[0x000]) & 0xE000;
		break;
	case 0x008:
		g_tRegUpdateTemp = *((u16*)&g_pAgbREG[0x008])^g_nAgbRegLast;
		if(g_tRegUpdateTemp & 0x0003)
			g_nAgbGrpBGLayerChange = 1;
		break;
	case 0x00A:
		g_tRegUpdateTemp = *((u16*)&g_pAgbREG[0x00A])^g_nAgbRegLast;
		if(g_tRegUpdateTemp & 0x0003)
			g_nAgbGrpBGLayerChange = 1;
		break;
	case 0x00C:
		g_tRegUpdateTemp = *((u16*)&g_pAgbREG[0x00C])^g_nAgbRegLast;
		if(g_tRegUpdateTemp & 0x0003)
			g_nAgbGrpBGLayerChange = 1;
		break;
	case 0x00E:
		g_tRegUpdateTemp = *((u16*)&g_pAgbREG[0x00E])^g_nAgbRegLast;
		if(g_tRegUpdateTemp & 0x0003)
			g_nAgbGrpBGLayerChange = 1;
		break;
	case 0x048:
	case 0x04A:
	case 0x050:
		if(g_nAgbRegLast != *((u16*)&g_pAgbREG[nAddr]))
			g_nAgbGrpBGLayerChange = 1;
		break;
	case 0x020:
		g_sAgbGrpBGRSData[0].nPA = agbRegF16toS32(*((u16*)&g_pAgbREG[0x020]));
		break;
	case 0x022:
		g_sAgbGrpBGRSData[0].nPB = agbRegF16toS32(*((u16*)&g_pAgbREG[0x022]));
		break;
	case 0x024:
		g_sAgbGrpBGRSData[0].nPC = agbRegF16toS32(*((u16*)&g_pAgbREG[0x024]));
		break;
	case 0x026:
		g_sAgbGrpBGRSData[0].nPD = agbRegF16toS32(*((u16*)&g_pAgbREG[0x026]));
		break;
	case 0x028:
	case 0x02A:
		g_sAgbGrpBGRSData[0].nX = agbRegF28toS32(g_pAgbBGX[0]->rCoodinate);
		g_nAgbGrpBGCrdFlag[0] |= 0x1;
		break;
	case 0x02C:
	case 0x02E:
		g_sAgbGrpBGRSData[0].nY = agbRegF28toS32(g_pAgbBGY[0]->rCoodinate);
		g_nAgbGrpBGCrdFlag[0] |= 0x2;
		break;
	case 0x030:
		g_sAgbGrpBGRSData[1].nPA = agbRegF16toS32(*((u16*)&g_pAgbREG[0x030]));
		break;
	case 0x032:
		g_sAgbGrpBGRSData[1].nPB = agbRegF16toS32(*((u16*)&g_pAgbREG[0x032]));
		break;
	case 0x034:
		g_sAgbGrpBGRSData[1].nPC = agbRegF16toS32(*((u16*)&g_pAgbREG[0x034]));
		break;
	case 0x036:
		g_sAgbGrpBGRSData[1].nPD = agbRegF16toS32(*((u16*)&g_pAgbREG[0x036]));
		break;
	case 0x038:
	case 0x03A:
		g_sAgbGrpBGRSData[1].nX = agbRegF28toS32(g_pAgbBGX[1]->rCoodinate);
		g_nAgbGrpBGCrdFlag[1] |= 0x1;
		break;
	case 0x03C:
	case 0x03E:
		g_sAgbGrpBGRSData[1].nY = agbRegF28toS32(g_pAgbBGY[1]->rCoodinate);
		g_nAgbGrpBGCrdFlag[1] |= 0x2;
		break;
	case 0x052:
		g_nAgbGrpEVA = g_nAgbRegCoefficient[g_pAgbBLDAlpha->rEVA];
		g_nAgbGrpEVB = g_nAgbRegCoefficient[g_pAgbBLDAlpha->rEVB];
		break;
	case 0x054:
		g_nAgbGrpEVY = g_nAgbRegCoefficient[g_pAgbBLDY->rEVY];
		break;
	case 0x0BA:
		if(g_nAgbDmaEnable[0]!=g_pAgbDMACnt[0]->rEnable)
		{
			g_nAgbDmaEnable[0] = g_pAgbDMACnt[0]->rEnable;
			if(g_pAgbDMACnt[0]->rEnable)
				agbDmaTransfer[0](1);
		}
		break;
	case 0x0C6:
		if(g_nAgbDmaEnable[1]!=g_pAgbDMACnt[1]->rEnable)
		{
			g_nAgbDmaEnable[1] = g_pAgbDMACnt[1]->rEnable;
			if(g_pAgbDMACnt[1]->rEnable)
				agbDmaTransfer[1](1);
		}
		break;
	case 0x0D2:
		if(g_nAgbDmaEnable[2]!=g_pAgbDMACnt[2]->rEnable)
		{
			g_nAgbDmaEnable[2] = g_pAgbDMACnt[2]->rEnable;
			if(g_pAgbDMACnt[2]->rEnable)
				agbDmaTransfer[2](1);
		}
		break;
	case 0x0DE:
		if(g_nAgbDmaEnable[3]!=g_pAgbDMACnt[3]->rEnable)
		{
			g_nAgbDmaEnable[3] = g_pAgbDMACnt[3]->rEnable;
			if(g_pAgbDMACnt[3]->rEnable)
				agbDmaTransfer[3](1);
		}
		break;
	case 0x100:
		g_nAgbTimeCounter[0] = *g_pAgbTMCntL[0];
		break;
	case 0x104:
		g_nAgbTimeCounter[1] = *g_pAgbTMCntL[1];
		break;
	case 0x108:
		g_nAgbTimeCounter[2] = *g_pAgbTMCntL[2];
		break;
	case 0x10C:
		g_nAgbTimeCounter[3] = *g_pAgbTMCntL[3];
		break;
	}
}

/** @brief Write 8 bits data to Registers */
void agbRegWrite8(u32 nAddr, u8 nData)
{
	nData &= g_pAgbRegMask[nAddr];
	if(g_pAgbRegRead[nAddr] != 0xFF)
		g_pAgbREG[nAddr] = (nData & g_pAgbRegRead[nAddr]) | (g_pAgbREG[nAddr] & (~g_pAgbRegRead[nAddr]));
//	else if((nAddr == 0x202) || (nAddr == 0x203))
//		g_pAgbREG[nAddr] ^= nData & g_pAgbREG[nAddr];
	else
		g_pAgbREG[nAddr] = nData;

	agbRegUpdate(nAddr & 0xFFFFFFFE);
	if(nAddr>=0x60 && nAddr<0xA0)
		agbSndUpdateReg8(nAddr);
	if(nAddr>=0x90 && nAddr<0xA0)
		NN_LOG("Write 8 bits data to WAVE_RAM\n");
//	if(nAddr>=0xA0 && nAddr<0xA8)
//		NN_LOG("Write 8 bits data to Sound Register: addr = 0x%08X, data = 0x%08X\n", nAddr, nData);
}

/** @brief Write 16 bits data to Registers */
void agbRegWrite16(u32 nAddr, u16 nData)
{
	nData &= *((u16*)&g_pAgbRegMask[nAddr]);
	g_nAgbRegLast = *((u16*)&g_pAgbREG[nAddr]);
	if( *((u16*)&g_pAgbRegRead[nAddr]) != 0xFFFF )
		*((u16*)&g_pAgbREG[nAddr]) = (nData & (*((u16*)&g_pAgbRegRead[nAddr]))) | ((*((u16*)&g_pAgbREG[nAddr])) & (~(*((u16*)&g_pAgbRegRead[nAddr]))));
	else if(nAddr == 0x202)
		(*((u16*)&g_pAgbREG[nAddr])) ^= nData & (*((u16*)&g_pAgbREG[nAddr]));
	else
	{
		if(nAddr == 0x130)
			(*((u16*)&g_pAgbREG[nAddr])) |= nData;
		else
			*((u16*)&g_pAgbREG[nAddr]) = nData;
	}

	agbRegUpdate(nAddr);
	if(nAddr>=0x60 && nAddr<0xA8)
		agbSndUpdateReg16(nAddr);
	if(nAddr>=0x90 && nAddr<0xA0)
		NN_LOG("Write 16 bits data to WAVE_RAM\n");
	if(nAddr>=0xA0 && nAddr<0xA8)
		NN_LOG("Write 16 bits data to FIFO\n");
}

/** @brief Write 32 bits data to Registers */
void agbRegWrite32(u32 nAddr, u32 nData)
{
	nData &= *((u32*)(&g_pAgbRegMask[nAddr]));
	if( *((u32*)&g_pAgbRegRead[nAddr]) != 0xFFFFFFFF )
		*((u32*)&g_pAgbREG[nAddr]) = (nData & (*((u32*)&g_pAgbRegRead[nAddr]))) | ((*((u32*)&g_pAgbREG[nAddr])) & (~(*((u32*)&g_pAgbRegRead[nAddr]))));
	else
	{
		if(nAddr == 0x130)
		{
			(*((u16*)&g_pAgbREG[nAddr])) |= nData;
			(*((u16*)&g_pAgbREG[nAddr+2])) = nData>>16;
		}
		else
			*((u32*)&g_pAgbREG[nAddr]) = nData;
	}
	agbRegUpdate(nAddr);
	agbRegUpdate(nAddr+2);
	if(nAddr>=0x90 && nAddr<0xA8)
		agbSndUpdateReg32(nAddr);
//	if(nAddr>=0x60 && nAddr<0x90)
//		NN_LOG("Write 32 bits data to Sound Register: addr = 0x%08X, data = 0x%08X\n", nAddr, nData);
}
