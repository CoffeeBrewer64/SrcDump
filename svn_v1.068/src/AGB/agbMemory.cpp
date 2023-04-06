/**
 * @file agbMemory.cpp
 * @author Chentian
 * @date 2009.11.23
 * @brief AGB Emulate For CTR - Memory Map
 */
#include "agbMemory.h"
#include "agbRegister.h"
#include "agbBackup.h"
#include "agbCPUData.h"
#include "agbGraphic.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
#ifdef TRL_PLATFORM_CTR
static const char			g_szAgbMemBIOSPath[]			= "rom:/agb.bin";
#endif
#ifdef TRL_PLATFORM_PC
static const char			g_szAgbMemBIOSPath[]			= "../files/agb.bin";
#endif
//@}

/** @brief Initialize Memory */
void agbMemInit()
{
//	g_pAgbSROM = (u8*)trlMemAlloc(0x4000);
	g_pAgbEWRAM = (u8*)trlMemAlloc(0x40000);
	g_pAgbIWRAM = (u8*)trlMemAlloc(0x8000);
	g_pAgbREG = (u8*)trlMemAlloc(0x400);
	g_pAgbPRAM = (u8*)trlMemAlloc(0x400);
	g_pAgbVRAM = (u8*)trlMemAlloc(0x18000);
	g_pAgbOAM = (u8*)trlMemAlloc(0x400);
	g_pAgbGPROM = (u8*)g_pAgbEmuBuf->pRomBuf;
	g_pAgbROMHeader = (agbSROMHeader*)g_pAgbGPROM;

	if(trlFileRead(g_szAgbMemBIOSPath, (void**)(&g_pAgbSROM))!=0x4000)
	{
		TRL_ERROR("Load agb.bin Fail.");
		return;
	}
	agbMemReset();
}

/** @brief Reset Memory */
void agbMemReset()
{
	memset(g_pAgbEWRAM, 0, 0x40000);
	memset(g_pAgbIWRAM, 0, 0x8000);
	memset(g_pAgbREG, 0, 0x400);
	memset(g_pAgbPRAM, 0, 0x400);
	memset(g_pAgbVRAM, 0, 0x18000);
	memset(g_pAgbOAM, 0, 0x400);
}

/** @brief Read 8 bits data from Memory Map */
extern "C" u8 agbMemRead8(u32 nAddr)
{
	switch(nAddr >> 24)
	{
	case 0x0:	// System ROM (16 Kbytes)
		if(nAddr < 0x00004000)
		{
			if(g_nAgbCPUReg[15]>>24)
				return 0;
			else
				return g_pAgbSROM[nAddr];
		}
		break;
	case 0x2:	// CPU External Working RAM (256 Kbytes)
		return g_pAgbEWRAM[nAddr & 0x3FFFF];
	case 0x3:	// CPU Internal Working RAM (32 Kbytes)
		return g_pAgbIWRAM[nAddr & 0x7FFF];
	case 0x4:	// I/O,Registers
    	if(nAddr < 0x4000400)
		{
			nAddr &= 0x000003FF;
			return g_pAgbREG[nAddr] & g_pAgbRegWrite[nAddr];
		}
    	break;
	case 0x8:	// Game Pak ROM
	case 0x9:
	case 0xA:
	case 0xB:
	case 0xC:
		return g_pAgbGPROM[nAddr & 0x1FFFFFF];
	case 0xD:	// Game Pak ROM \ Game Pak RAM (EEPROM)
		nAddr &= 0x1FFFFFF;
		if(g_pAgbEmuBuf->nBackupType < AGB_BAK_TYPE_EEPROM4)
			return g_pAgbGPROM[nAddr];
		else if(g_pAgbEmuBuf->nRomBufSize >= 0x1000000)
		{
			if(nAddr >= 0x1FFFF00)
				return agbBakReadEEPROM();
			else
				return g_pAgbGPROM[nAddr];
		}
		else
			return agbBakReadEEPROM();
	case 0xE:	// Game Pak RAM
		return agbBakReadGPROM(nAddr & 0x0000FFFF);
	}
//	TRL_ERROR("Unknow Address: agbMemRead8.");
	NN_LOG("Unknow Address: agbMemRead8  addr = 0x%08X\n", nAddr);
	return 0;
}

/** @brief Read 16 bits data from Memory Map */
extern "C" u16 agbMemRead16(u32 nAddr)
{
	nAddr &= 0xFFFFFFFE;
	switch(nAddr >> 24)
	{
	case 0x0:	// System ROM (16 Kbytes)
		if(nAddr < 0x00004000)
		{
			if(g_nAgbCPUReg[15]>>24)
				return 0;
			else
				return *((u16*)&g_pAgbSROM[nAddr]);
		}
		break;
	case 0x2:	// CPU External Working RAM (256 Kbytes)
		return *((u16*)&g_pAgbEWRAM[nAddr & 0x3FFFF]);
	case 0x3:	// CPU Internal Working RAM (32 Kbytes)
		return *((u16*)&g_pAgbIWRAM[nAddr & 0x7FFF]);
	case 0x4:	// I/O,Registers
    	if(nAddr < 0x4000400)
		{
			nAddr &= 0x000003FF;
			return (*((u16*)&g_pAgbREG[nAddr])) & (*((u16*)&g_pAgbRegWrite[nAddr]));
		}
    	break;
	case 0x5:	// Palette RAM (1 Kbyte)
		return *((u16*)&g_pAgbPRAM[nAddr & 0x3FF]);
	case 0x6:	// VRAM (96 Kbyte)
		nAddr &= 0x1FFFF;
		if(nAddr >= 0x18000)
			nAddr &= 0x17FFF;
		return *((u16*)&g_pAgbVRAM[nAddr]);
	case 0x7:	// OAM (1 Kbyte)
		return *((u16*)&g_pAgbOAM[nAddr & 0x3FF]);
	case 0x8:	// Game Pak ROM
	case 0x9:
	case 0xA:
	case 0xB:
	case 0xC:
		return *((u16*)&g_pAgbGPROM[nAddr & 0x1FFFFFF]);
	case 0xD:	// Game Pak ROM \ Game Pak RAM (EEPROM)
		nAddr &= 0x1FFFFFF;
		if(g_pAgbEmuBuf->nBackupType < AGB_BAK_TYPE_EEPROM4)
			return *((u16*)&g_pAgbGPROM[nAddr]);
		else if(g_pAgbEmuBuf->nRomBufSize >= 0x1000000)
		{
			if(nAddr >= 0x1FFFF00)
				return agbBakReadEEPROM();
			else
				return *((u16*)&g_pAgbGPROM[nAddr]);
		}
		else
			return agbBakReadEEPROM();
	}
//	TRL_ERROR("Unknow Address: agbMemRead16.");
	NN_LOG("Unknow Address: agbMemRead16  addr = 0x%08X\n", nAddr);
	return 0;
}

/** @brief Read 32 bits data from Memory Map */
extern "C"  u32 agbMemRead32(u32 nAddr)
{
	nAddr &= 0xFFFFFFFC;
	switch(nAddr >> 24)
	{
	case 0x0:	// System ROM (16 Kbytes)
		if(nAddr < 0x00004000)
		{
			if(g_nAgbCPUReg[15]>>24)
				return 0;
			else
				return *((u32*)&g_pAgbSROM[nAddr]);
		}
		break;
	case 0x2:	// CPU External Working RAM (256 Kbytes)
		return *((u32*)&g_pAgbEWRAM[nAddr & 0x3FFFF]);
	case 0x3:	// CPU Internal Working RAM (32 Kbytes)
		return *((u32*)&g_pAgbIWRAM[nAddr & 0x7FFF]);
	case 0x4:	// I/O,Registers
    	if(nAddr < 0x4000400)
		{
			nAddr &= 0x000003FF;
			return (*((u32*)&g_pAgbREG[nAddr])) & (*((u32*)&g_pAgbRegWrite[nAddr]));
		}
    	break;
	case 0x5:	// Palette RAM (1 Kbyte)
		return *((u32*)&g_pAgbPRAM[nAddr & 0x3FF]);
	case 0x6:	// VRAM (96 Kbyte)
		nAddr &= 0x1FFFF;
		if(nAddr >= 0x18000)
			nAddr &= 0x17FFF;
		return *((u32*)&g_pAgbVRAM[nAddr]);
	case 0x7:	// OAM (1 Kbyte)
		return *((u32*)&g_pAgbOAM[nAddr & 0x3FF]);
	case 0x8:	// Game Pak ROM
	case 0x9:
	case 0xA:
	case 0xB:
	case 0xC:
		return *((u32*)&g_pAgbGPROM[nAddr & 0x1FFFFFF]);
	case 0xD:	// Game Pak ROM \ Game Pak RAM (EEPROM)
		nAddr &= 0x1FFFFFF;
		if(g_pAgbEmuBuf->nBackupType < AGB_BAK_TYPE_EEPROM4)
			return *((u32*)&g_pAgbGPROM[nAddr]);
		else if(g_pAgbEmuBuf->nRomBufSize >= 0x1000000)
		{
			if(nAddr >= 0x1FFFF00)
				return agbBakReadEEPROM();
			else
				return *((u32*)&g_pAgbGPROM[nAddr]);
		}
		else
			return agbBakReadEEPROM();
	}
//	TRL_ERROR("Unknow Address: agbMemRead32.");
	NN_LOG("Unknow Address: agbMemRead32  addr = 0x%08X\n", nAddr);
	return 0;
}

/** @brief Write 8 bits data to Memory Map */
extern "C" void agbMemWrite8(u32 nAddr, u8 nData)
{
	switch(nAddr >> 24)
	{
	case 0x2:	// CPU External Working RAM (256 Kbytes)
		g_pAgbEWRAM[nAddr & 0x3FFFF] = nData;
		return;
	case 0x3:	// CPU Internal Working RAM (32 Kbytes)
		g_pAgbIWRAM[nAddr & 0x7FFF] = nData;
		return;
	case 0x4:	// I/O,Registers
    	if(nAddr < 0x4000400)
		{
			agbRegWrite8(nAddr-0x4000000, nData);
			return;
		}
		break;
/*	case 0x6:	// VRAM (96 Kbyte)
		nAddr &= 0x1FFFF;
		if(nAddr >= 0x18000)
			nAddr &= 0x17FFF;
		g_pAgbVRAM[nAddr] = nData;
		return;*/
	case 0xD:	// Game Pak RAM (EEPROM)
		if(g_pAgbEmuBuf->nBackupType >= AGB_BAK_TYPE_EEPROM4)
		{
			nAddr &= 0xFFFFFF;
			if(g_pAgbEmuBuf->nRomBufSize >= 0x1000000)
			{
				if(nAddr >= 0xFFFF00)
				{
					agbBakWriteEEPROM(nData);
					return;
				}
			}
			else
			{
				agbBakWriteEEPROM(nData);
				return;
			}
		}
		break;
	case 0xE:	// Game Pak RAM (512 Kbits)
		agbBakWriteGPROM(nAddr & 0x0000FFFF, nData);
		return;
	}
//	TRL_ERROR("Unknow Address: agbMemWrite8.");
	if(nAddr != 0x79)
	NN_LOG("Unknow Address: agbMemWrite8  addr = 0x%08X  value = 0x%02X\n", nAddr, nData);
}

/** @brief Write 16 bits data to Memory Map */
extern "C" void agbMemWrite16(u32 nAddr, u16 nData)
{
	nAddr &= 0xFFFFFFFE;
	switch(nAddr >> 24)
	{
	case 0x2:	// CPU External Working RAM (256 Kbytes)
		*((u16*)&g_pAgbEWRAM[nAddr & 0x3FFFF]) = nData;
		return;
	case 0x3:	// CPU Internal Working RAM (32 Kbytes)
		*((u16*)&g_pAgbIWRAM[nAddr & 0x7FFF]) = nData;
		return;
	case 0x4:	// I/O,Registers
    	if(nAddr < 0x4000400)
		{
			agbRegWrite16(nAddr-0x4000000, nData);
			return;
		}
		break;
	case 0x5:	// Palette RAM (1 Kbyte)
		*((u16*)&g_pAgbPRAM[nAddr & 0x3FF]) = nData;
		return;
	case 0x6:	// VRAM (96 Kbyte)
		nAddr &= 0x1FFFF;
		if(nAddr >= 0x18000)
			nAddr &= 0x17FFF;
		*((u16*)&g_pAgbVRAM[nAddr]) = nData;
		return;
	case 0x7:	// OAM (1 Kbyte)
		g_nAgbGrpOBJLayerChange = 1;
		*((u16*)&g_pAgbOAM[nAddr & 0x3FF]) = nData;
		return;
	case 0xD:	// Game Pak RAM (EEPROM)
		if(g_pAgbEmuBuf->nBackupType >= AGB_BAK_TYPE_EEPROM4)
		{
			nAddr &= 0xFFFFFF;
			if(g_pAgbEmuBuf->nRomBufSize >= 0x1000000)
			{
				if(nAddr >= 0xFFFF00)
				{
					agbBakWriteEEPROM((u8)nData);
					return;
				}
			}
			else
			{
				agbBakWriteEEPROM((u8)nData);
				return;
			}
		}
		break;
	}
//	TRL_ERROR("Unknow Address: agbMemWrite16.");
	NN_LOG("Unknow Address: agbMemWrite16  addr = 0x%08X  value = 0x%04X\n", nAddr, nData);
}

/** @brief Write 32 bits data to Memory Map */
extern "C" void agbMemWrite32(u32 nAddr, u32 nData)
{
	nAddr &= 0xFFFFFFFC;
	switch(nAddr >> 24)
	{
	case 0x2:	// CPU External Working RAM (256 Kbytes)
		*((u32*)&g_pAgbEWRAM[nAddr & 0x3FFFF]) = nData;
		return;
	case 0x3:	// CPU Internal Working RAM (32 Kbytes)
		*((u32*)&g_pAgbIWRAM[nAddr & 0x7FFF]) = nData;
		return;
	case 0x4:	// I/O,Registers
    	if(nAddr < 0x4000400)
		{
			agbRegWrite32((nAddr-0x4000000)&0x3ff, nData);
			return;
		}
		break;
	case 0x5:	// Palette RAM (1 Kbyte)
		*((u32*)&g_pAgbPRAM[nAddr & 0x3FF]) = nData;
		return;
	case 0x6:	// VRAM (96 Kbyte)
		nAddr &= 0x1FFFF;
		if(nAddr >= 0x18000)
			nAddr &= 0x17FFF;
		*((u32*)&g_pAgbVRAM[nAddr]) = nData;
		return;
	case 0x7:	// OAM (1 Kbyte)
		g_nAgbGrpOBJLayerChange = 1;
		*((u32*)&g_pAgbOAM[nAddr & 0x3FF]) = nData;
		return;
	case 0xD:	// Game Pak RAM (EEPROM)
		if(g_pAgbEmuBuf->nBackupType >= AGB_BAK_TYPE_EEPROM4)
		{
			nAddr &= 0xFFFFFF;
			if(g_pAgbEmuBuf->nRomBufSize >= 0x1000000)
			{
				if(nAddr >= 0xFFFF00)
				{
					agbBakWriteEEPROM((u8)nData);
					return;
				}
			}
			else
			{
				agbBakWriteEEPROM((u8)nData);
				return;
			}
		}
		break;
	}
//	TRL_ERROR("Unknow Address: agbMemWrite32.");
	if(nAddr != 0x18)
		NN_LOG("Unknow Address: agbMemWrite32  addr = 0x%08X  value = 0x%08X\n", nAddr, nData);
}

/** @brief Get Read 16 bits data Address */
inline u8* agbMemGetAddressRead16(u32 nAddr)
{
	switch(nAddr >> 24)
	{
	case 0x0:	// System ROM (16 Kbytes)
		if(nAddr < 0x00004000)
			return &g_pAgbSROM[nAddr];
		break;
	case 0x2:	// CPU External Working RAM (256 Kbytes)
		return &g_pAgbEWRAM[nAddr & 0x3FFFF];
	case 0x3:	// CPU Internal Working RAM (32 Kbytes)
		return &g_pAgbIWRAM[nAddr & 0x7FFF];
	case 0x5:	// Palette RAM (1 Kbyte)
		return &g_pAgbPRAM[nAddr & 0x3FF];
	case 0x6:	// VRAM (96 Kbyte)
		nAddr &= 0x1FFFF;
		if(nAddr >= 0x18000)
			nAddr &= 0x17FFF;
		return &g_pAgbVRAM[nAddr];
	case 0x7:	// OAM (1 Kbyte)
		return &g_pAgbOAM[nAddr & 0x3FF];
	case 0x8:	// Game Pak ROM
	case 0x9:
	case 0xA:
	case 0xB:
	case 0xC:
		return &g_pAgbGPROM[nAddr & 0x1FFFFFF];
	case 0xD:	// Game Pak ROM \ Game Pak RAM (EEPROM)
		nAddr &= 0x1FFFFFF;
		if(g_pAgbEmuBuf->nBackupType < AGB_BAK_TYPE_EEPROM4)
			return &g_pAgbGPROM[nAddr];
		else if(g_pAgbEmuBuf->nRomBufSize >= 0x1000000)
		{
			if(nAddr < 0x1FFFF00)
				return &g_pAgbGPROM[nAddr];
		}
		break;
	}
	return NULL;
}

/** @brief Get Read 32 bits data Address */
inline u8* agbMemGetAddressRead32(u32 nAddr)
{
	switch(nAddr >> 24)
	{
	case 0x0:	// System ROM (16 Kbytes)
		if(nAddr < 0x00004000)
			return &g_pAgbSROM[nAddr];
		break;
	case 0x2:	// CPU External Working RAM (256 Kbytes)
		return &g_pAgbEWRAM[nAddr & 0x3FFFF];
	case 0x3:	// CPU Internal Working RAM (32 Kbytes)
		return &g_pAgbIWRAM[nAddr & 0x7FFF];
	case 0x5:	// Palette RAM (1 Kbyte)
		return &g_pAgbPRAM[nAddr & 0x3FF];
	case 0x6:	// VRAM (96 Kbyte)
		nAddr &= 0x1FFFF;
		if(nAddr >= 0x18000)
			nAddr &= 0x17FFF;
		return &g_pAgbVRAM[nAddr];
	case 0x7:	// OAM (1 Kbyte)
		return &g_pAgbOAM[nAddr & 0x3FF];
	case 0x8:	// Game Pak ROM
	case 0x9:
	case 0xA:
	case 0xB:
	case 0xC:
		return &g_pAgbGPROM[nAddr & 0x1FFFFFF];
	case 0xD:	// Game Pak ROM \ Game Pak RAM (EEPROM)
		nAddr &= 0x1FFFFFF;
		if(g_pAgbEmuBuf->nBackupType < AGB_BAK_TYPE_EEPROM4)
			return &g_pAgbGPROM[nAddr];
		else if(g_pAgbEmuBuf->nRomBufSize >= 0x1000000)
		{
			if(nAddr < 0x1FFFF00)
				return &g_pAgbGPROM[nAddr];
		}
	}
	return NULL;
}

/** @brief Get Write 16 bits data Address */
inline u8* agbMemGetAddressWrite16(u32 nAddr)
{
	switch(nAddr >> 24)
	{
	case 0x2:	// CPU External Working RAM (256 Kbytes)
		return &g_pAgbEWRAM[nAddr & 0x3FFFF];
	case 0x3:	// CPU Internal Working RAM (32 Kbytes)
		return &g_pAgbIWRAM[nAddr & 0x7FFF];
	case 0x5:	// Palette RAM (1 Kbyte)
		return &g_pAgbPRAM[nAddr & 0x3FF];
	case 0x6:	// VRAM (96 Kbyte)
		nAddr &= 0x1FFFF;
		if(nAddr >= 0x18000)
			nAddr &= 0x17FFF;
		return &g_pAgbVRAM[nAddr];
	case 0x7:	// OAM (1 Kbyte)
		g_nAgbGrpOBJLayerChange = 1;
		return &g_pAgbOAM[nAddr & 0x3FF];
	}
	return NULL;
}

/** @brief Get Write 32 bits data Address */
inline u8* agbMemGetAddressWrite32(u32 nAddr)
{
	switch(nAddr >> 24)
	{
	case 0x2:	// CPU External Working RAM (256 Kbytes)
		return &g_pAgbEWRAM[nAddr & 0x3FFFF];
	case 0x3:	// CPU Internal Working RAM (32 Kbytes)
		return &g_pAgbIWRAM[nAddr & 0x7FFF];
	case 0x5:	// Palette RAM (1 Kbyte)
		return &g_pAgbPRAM[nAddr & 0x3FF];
	case 0x6:	// VRAM (96 Kbyte)
		nAddr &= 0x1FFFF;
		if(nAddr >= 0x18000)
			nAddr &= 0x17FFF;
		return &g_pAgbVRAM[nAddr];
	case 0x7:	// OAM (1 Kbyte)
		g_nAgbGrpOBJLayerChange = 1;
		return &g_pAgbOAM[nAddr & 0x3FF];
	}
	return NULL;
}

/** @brief Copy 16 bits data */
u32 agbMemCopy16(u32 nAddrD, u32 nAddrS, u32 nCount)
{
	u8* pAddrS = agbMemGetAddressRead16(nAddrS);
	if(!pAddrS)
		return 0;
	u8* pAddrD = agbMemGetAddressWrite16(nAddrD);
	if(!pAddrD)
		return 0;
	trlMemCopy(pAddrD, pAddrS, nCount);
	return 1;
}

/** @brief Copy 32 bits data */
u32 agbMemCopy32(u32 nAddrD, u32 nAddrS, u32 nCount)
{
	u8* pAddrS = agbMemGetAddressRead32(nAddrS);
	if(!pAddrS)
		return 0;
	u8* pAddrD = agbMemGetAddressWrite32(nAddrD);
	if(!pAddrD)
		return 0;
	trlMemCopy(pAddrD, pAddrS, nCount);
	return 1;
}
