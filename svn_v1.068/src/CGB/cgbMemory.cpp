/**
 * @file cgbMemory.cpp
 * @author Chentian
 * @date 2009.11.18
 * @brief CGB Emulate For CTR - Memory Map
 */
#include "cgbMemory.h"
#include "cgbRegister.h"
#include "cgbCard.h"
#include "cgbGraphic.h"
#include "cgbCPU.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
u8*					g_pCgbCurWRAM = NULL;					///< Current WRAM Pointer
u8*					g_pCgbCurVRAM = NULL;					///< Current VRAM Pointer
u32					g_nCgbMemWRAMSize = 0x2000;				///< WRAM Size
u32					g_nCgbMemVRAMSize = 0x2000;				///< VRAM Size
trlSEmuShellResume	g_sCgbMemSaveData[CGB_MEM_SAVEDATA];	///< Memory Save Data
//@}

/** @brief Initialize Memory */
void cgbMemInit()
{
	g_pCgbROM = (u8*)g_pCgbEmuBuf->pRomBuf;
	g_pCgbROMHeader = (cgbSROMHeader*)(&g_pCgbROM[0x0100]);

	g_nCgbMemWRAMSize = 0x2000;				///< WRAM Size
	g_nCgbMemVRAMSize = 0x2000;				///< VRAM Size
	if(g_pCgbROMHeader->nCGBFlag & 0x80)
	{
		g_nCgbGameType = CGB_GAMETYPE_CGB;
		g_nCgbMemWRAMSize *= 4;
		g_nCgbMemVRAMSize *= 2;
	}
	else
		g_nCgbGameType = CGB_GAMETYPE_DMG;
	g_pCgbWRAM = (u8*)trlMemAlloc(g_nCgbMemWRAMSize);
	g_pCgbVRAM = (u8*)trlMemAlloc(g_nCgbMemVRAMSize);
	g_pCgbOAM = (u8*)trlMemAlloc(0xA0);
	g_pCgbREG = (u8*)trlMemAlloc(0x100);
	g_pCgbHRAM = &g_pCgbREG[0x80];
	
	// Save Data
	g_sCgbMemSaveData[0].SetData(g_pCgbWRAM, g_nCgbMemWRAMSize, 1, 0);
	g_sCgbMemSaveData[1].SetData(g_pCgbVRAM, g_nCgbMemVRAMSize, 1, 0);
	g_sCgbMemSaveData[2].SetData(g_pCgbOAM, 0xA0, 1, 0);
	g_sCgbMemSaveData[3].SetData(g_pCgbREG, 0x100, 1, 0);

	cgbMemReset();
}

/** @brief Reset Memory */
void cgbMemReset()
{
	memset(g_pCgbWRAM, 0, g_nCgbMemWRAMSize);
	memset(g_pCgbVRAM, 0, g_nCgbMemVRAMSize);
	memset(g_pCgbOAM, 0, 0xA0);
	memset(g_pCgbREG, 0, 0x100);
	g_pCgbCurVRAM = g_pCgbVRAM;
	g_pCgbCurWRAM = &g_pCgbWRAM[0x1000];
}

/** @brief Resume Memory */
void cgbMemResume()
{
	if(g_nCgbGameType == CGB_GAMETYPE_DMG)
	{
		g_pCgbCurVRAM = g_pCgbVRAM;
		g_pCgbCurWRAM = &g_pCgbWRAM[0x1000];
	}
	else
	{
		if(g_pCgbRegSVBK->rWRAMBank)
			g_pCgbCurWRAM = &g_pCgbWRAM[g_pCgbRegSVBK->rWRAMBank*0x1000];
		else
			g_pCgbCurWRAM = &g_pCgbWRAM[0x1000];
		g_pCgbCurVRAM = &g_pCgbVRAM[g_pCgbRegVBK->rBank*0x2000];
	}
}

/** @brief Exit Memory */
void cgbMemExit()
{
	trlMemFree(g_pCgbWRAM);
	trlMemFree(g_pCgbVRAM);
	trlMemFree(g_pCgbOAM);
	trlMemFree(g_pCgbREG);
}

/** @brief Read Data From Memory Map - 8 Bit */
u8 cgbMemRead8(u16 nAddr)
{
#if TRL_PROFILER
	g_pCgbEmuBuf->nProfiler1++;	
#endif
	trlTraceMemRead(nAddr, 0);
	switch(nAddr >> 12)
	{
	case 0x0:	// 0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
	case 0x1:
	case 0x2:
	case 0x3:
		return g_pCgbROM[nAddr];
	case 0x4:	// 4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
	case 0x5:
	case 0x6:
	case 0x7:
		return g_pCgbCurROM[nAddr-0x4000];
	case 0x8:	// 8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
	case 0x9:
		if(g_pCgbRegSTAT->rMode < 3)
			return g_pCgbCurVRAM[nAddr-0x8000];
//		NN_LOG("Cannot Access to VRAM: cgbMemRead8  addr = 0x%04X  Mode = 3\n", nAddr);
		break;
	case 0xA:	// A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
	case 0xB:
		if(cgbCardReadRAM)
			return cgbCardReadRAM(nAddr);
		break;
	case 0xC:	// C000-CFFF   4KB Work RAM Bank 0 (WRAM)
		return g_pCgbWRAM[nAddr-0xC000];
	case 0xD:	// D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
		return g_pCgbCurWRAM[nAddr-0xD000];
	case 0xE:	// E000-EFFF   4KB Work RAM Bank 0 (WRAM) Echo
		return g_pCgbWRAM[nAddr-0xE000];
	case 0xF:
		if(nAddr>=0xFF80)					// FF80-FFFE   High RAM (HRAM) & FFFF I/O Ports
			return g_pCgbHRAM[nAddr-0xFF80];
		if(nAddr>=0xFF00)					// FF00-FF7F   I/O Ports
			return g_pCgbREG[nAddr-0xFF00] & g_pCgbRegWrite[nAddr-0xFF00];
		if(nAddr>=0xFE00 && nAddr<0xFEA0)	// FE00-FE9F   Sprite Attribute Table (OAM)
		{
//			if(g_pCgbRegSTAT->rMode < 2)
				return g_pCgbOAM[nAddr-0xFE00];
//			NN_LOG("Cannot Access to OAM: cgbMemRead8  addr = 0x%04X  Mode = %d\n", nAddr, g_pCgbRegSTAT->rMode);
//			break;
		}
		if(nAddr<0xFE00)					// F000-FDFF   4KB Work RAM Bank 1 (WRAM) Echo
			return g_pCgbCurWRAM[nAddr-0xF000];
		break;
	}
//	TRL_ERROR("Unknow Address: cgbMemRead8.");
	NN_LOG("Unknow Address: cgbMemRead8  addr = 0x%04X\n", nAddr);
	return 0xFF;
}

/** @brief Write Data to Memory Map - 8 Bit */
void cgbMemWrite8(u16 nAddr, u8 nValue)
{
#if TRL_PROFILER
	g_pCgbEmuBuf->nProfiler2++;
#endif
	trlTraceMemWrite(nAddr, nValue);
	switch(nAddr >> 12)
	{
	case 0x0:	// 0000-7FFF   32KB Cartridge Register
	case 0x1:
	case 0x2:
	case 0x3:
	case 0x4:
	case 0x5:
	case 0x6:
	case 0x7:
		if(cgbCardRegister)
			cgbCardRegister(nAddr, nValue);
		return;
	case 0x8:	// 8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
	case 0x9:
//		if(g_pCgbRegSTAT->rMode < 3)
			g_pCgbCurVRAM[nAddr-0x8000] = nValue;
//		else
//			NN_LOG("Cannot Access to VRAM: cgbMemWrite8  addr = 0x%04X  Mode = 3\n", nAddr);
		return;
	case 0xA:	// A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
	case 0xB:
		if(cgbCardWriteRAM)
			cgbCardWriteRAM(nAddr, nValue);
		return;
	case 0xC:	// C000-CFFF   4KB Work RAM Bank 0 (WRAM)
		g_pCgbWRAM[nAddr-0xC000] = nValue;
		return;
	case 0xD:	// D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
		g_pCgbCurWRAM[nAddr-0xD000] = nValue;
		return;
	case 0xE:	// E000-EFFF   4KB Work RAM Bank 0 (WRAM) Echo
		g_pCgbWRAM[nAddr-0xE000] = nValue;
		return;
	case 0xF:
		if(nAddr == 0xFFFF)					// FFFF   I/O Ports
		{
			g_pCgbREG[0xFF] = nValue & 0x1F;
			g_nCgbCpuEventTicks = 0;
			return;
		}
		if(nAddr>=0xFF80)					// FF80-FFFE   High RAM (HRAM)
		{
			g_pCgbHRAM[nAddr-0xFF80] = nValue;
			return;
		}
		if(nAddr>=0xFF00)					// FF00-FF7F   I/O Ports
		{
			cgbRegWrite(nAddr-0xFF00, nValue);
			return;
		}
		if(nAddr>=0xFE00 && nAddr<0xFEA0)	// FE00-FE9F   Sprite Attribute Table (OAM)
		{
//			if(g_pCgbRegSTAT->rMode < 2)
//			{
				g_pCgbOAM[nAddr-0xFE00] = nValue;
				g_bCgbGrpOAMChange = 1;
				return;
//			}
//			NN_LOG("Cannot Access to OAM: cgbMemWrite8  addr = 0x%04X  Mode = 3\n", nAddr);
//			return;
		}
		if(nAddr<0xFE00)					// F000-FDFF   4KB Work RAM Bank 1 (WRAM) Echo
		{
			g_pCgbCurWRAM[nAddr-0xF000] = nValue;
			return;
		}
		break;
	}
	//TRL_ERROR("Unknow Address: cgbMemWrite8.");
	//NN_LOG("Unknow Address: cgbMemWrite8  addr = 0x%04X  value = 0x%02X\n", nAddr, nValue);
}

/** @brief Read Data From Memory Map - 16 Bit */
u16 cgbMemRead16(u16 nAddr)
{
#if TRL_PROFILER
	g_pCgbEmuBuf->nProfiler1++;
#endif
	switch(nAddr >> 12)
	{
	case 0x0:	// 0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
	case 0x1:
	case 0x2:
	case 0x3:
		return *((u16*)&g_pCgbROM[nAddr]);
	case 0x4:	// 4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
	case 0x5:
	case 0x6:
	case 0x7:
		return *((u16*)&g_pCgbCurROM[nAddr-0x4000]);
	case 0x8:	// 8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
	case 0x9:
//		if(g_pCgbRegSTAT->rMode < 3)
			return *((u16*)&g_pCgbCurVRAM[nAddr-0x8000]);
//		NN_LOG("Cannot Access to VRAM: cgbMemRead16  addr = 0x%04X  Mode = 3\n", nAddr);
//		break;
	case 0xA:	// A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
	case 0xB:
		if(cgbCardReadRAM)
			return ((u16)cgbCardReadRAM(nAddr+1) << 8) | cgbCardReadRAM(nAddr);
		break;
	case 0xC:	// C000-CFFF   4KB Work RAM Bank 0 (WRAM)
		return *((u16*)&g_pCgbWRAM[nAddr-0xC000]);
	case 0xD:	// D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
		return *((u16*)&g_pCgbCurWRAM[nAddr-0xD000]);
	case 0xE:	// E000-EFFF   4KB Work RAM Bank 0 (WRAM) Echo
		return *((u16*)&g_pCgbWRAM[nAddr-0xE000]);
	case 0xF:
		if(nAddr>=0xFF80)					// FF80-FFFE   High RAM (HRAM) & FFFF I/O Ports
			return *((u16*)&g_pCgbHRAM[nAddr-0xFF80]);
		if(nAddr>=0xFF00)					// FF00-FF7F   I/O Ports
			return *((u16*)&g_pCgbREG[nAddr-0xFF00]) & *((u16*)&g_pCgbRegWrite[nAddr-0xFF00]);
		if(nAddr>=0xFE00 && nAddr<0xFEA0)	// FE00-FE9F   Sprite Attribute Table (OAM)
		{
//			if(g_pCgbRegSTAT->rMode < 2)
				return *((u16*)&g_pCgbOAM[nAddr-0xFE00]);
//			NN_LOG("Cannot Access to OAM: cgbMemRead16  addr = 0x%04X  Mode = %d\n", nAddr, g_pCgbRegSTAT->rMode);
//			break;
		}
		if(nAddr<0xFE00)					// F000-FDFF   4KB Work RAM Bank 1 (WRAM) Echo
			return *((u16*)&g_pCgbCurWRAM[nAddr-0xF000]);
		break;
	}
//	TRL_ERROR("Unknow Address: cgbMemRead16.");
//	NN_LOG("Unknow Address: cgbMemRead16  addr = 0x%04X\n", nAddr);
	return 0xFFFF;
}

/** @brief Write Data to Memory Map - 16 Bit */
void cgbMemWrite16(u16 nAddr, u16 nValue)
{
#if TRL_PROFILER
	g_pCgbEmuBuf->nProfiler2++;
#endif
	switch(nAddr >> 12)
	{
	case 0x0:	// 0000-7FFF   32KB Cartridge Register
	case 0x1:
	case 0x2:
	case 0x3:
	case 0x4:
	case 0x5:
	case 0x6:
	case 0x7:
		if(cgbCardRegister)
		{
			cgbCardRegister(nAddr, nValue&0xFF);
			cgbCardRegister(nAddr+1, nValue>>8);
		}
		return;
	case 0x8:	// 8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
	case 0x9:
//		if(g_pCgbRegSTAT->rMode < 3)
			*((u16*)&g_pCgbCurVRAM[nAddr-0x8000]) = nValue;
//		else
//			NN_LOG("Cannot Access to VRAM: cgbMemWrite16  addr = 0x%04X  Mode = 3\n", nAddr);
		return;
	case 0xA:	// A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
	case 0xB:
		if(cgbCardWriteRAM)
		{
			cgbCardWriteRAM(nAddr, nValue&0xFF);
			cgbCardWriteRAM(nAddr+1, nValue>>8);
		}
		return;
	case 0xC:	// C000-CFFF   4KB Work RAM Bank 0 (WRAM)
		*((u16*)&g_pCgbWRAM[nAddr-0xC000]) = nValue;
		return;
	case 0xD:	// D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
		*((u16*)&g_pCgbCurWRAM[nAddr-0xD000]) = nValue;
		return;
	case 0xE:	// E000-EFFF   4KB Work RAM Bank 0 (WRAM) Echo
		*((u16*)&g_pCgbWRAM[nAddr-0xE000]) = nValue;
		return;
	case 0xF:
		if(nAddr>=0xFF80)					// FF80-FFFE   High RAM (HRAM) & FFFF I/O Ports
		{
			*((u16*)&g_pCgbHRAM[nAddr-0xFF80]) = nValue;
			return;
		}
		if(nAddr>=0xFF00)					// FF00-FF7F   I/O Ports
		{
			cgbRegWrite(nAddr-0xFF00, nValue&0xFF);
			cgbRegWrite(nAddr-0xFF00+1, nValue >> 8);
			return;			
		}
		if(nAddr>=0xFE00 && nAddr<0xFEA0)	// FE00-FE9F   Sprite Attribute Table (OAM)
		{
//			if(g_pCgbRegSTAT->rMode < 2)
//			{
				*((u16*)&g_pCgbOAM[nAddr-0xFE00]) = nValue;
				g_bCgbGrpOAMChange = 1;
//			}
//			else
//				NN_LOG("Cannot Access to OAM: cgbMemWrite16  addr = 0x%04X  Mode = %d\n", nAddr, g_pCgbRegSTAT->rMode);
			return;
		}
		if(nAddr<0xFE00)					// F000-FDFF   4KB Work RAM Bank 1 (WRAM) Echo
		{
			*((u16*)&g_pCgbCurWRAM[nAddr-0xF000]) = nValue;
			return;
		}
		break;
	}
//	TRL_ERROR("Unknow Address: cgbMemWrite16.");
//	NN_LOG("Unknow Address: cgbMemWrite16  addr = 0x%04X  value = 0x%04X\n", nAddr, nValue);
}

/** @brief Read Opcode From Memory Map */
u8* cgbMemReadOpcode(u16 nAddr)
{
	switch(nAddr >> 12)
	{
	case 0x0:	// 0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
	case 0x1:
	case 0x2:
	case 0x3:
		return &g_pCgbROM[nAddr];
	case 0x4:	// 4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
	case 0x5:
	case 0x6:
	case 0x7:
		return &g_pCgbCurROM[nAddr-0x4000];
	case 0xC:	// C000-CFFF   4KB Work RAM Bank 0 (WRAM)
		return &g_pCgbWRAM[nAddr-0xC000];
	case 0xD:	// D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
		return &g_pCgbCurWRAM[nAddr-0xD000];
	case 0xE:	// E000-EFFF   4KB Work RAM Bank 0 (WRAM) Echo
		return &g_pCgbWRAM[nAddr-0xE000];
	case 0xF:
		if(nAddr>=0xFF80)					// FF80-FFFE   High RAM (HRAM)
			return &g_pCgbHRAM[nAddr-0xFF80];
		if(nAddr<0xFE00)					// F000-FDFF   4KB Work RAM Bank 1 (WRAM) Echo
			return &g_pCgbCurWRAM[nAddr-0xF000];
		break;
	}
//	TRL_ERROR("Unknow Address: cgbMemReadOpcode.");
	NN_LOG("Unknow Address: cgbMemReadOpcode  addr = 0x%04X\n", nAddr);
	g_pCgbEmuBuf->bError = 1;
	return g_pCgbCpuPC;
}
