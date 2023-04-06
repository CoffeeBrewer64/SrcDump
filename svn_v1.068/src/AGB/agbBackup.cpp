/**
 * @file agbBackup.cpp
 * @author Chentian
 * @date 2009.11.23
 * @brief AGB Emulate For CTR - Backup
 */
#include "agbBackup.h"

/** @name Macro Define */
//@{
//@}

/**
 * @enum agbEBackupFlashState
 * @brief The Flash Memory State
 */
enum agbEBackupFlashState
{
	eBF_Read			= 0,			///< Read Data
	eBF_Step1			= 1,			///< Command Step 1
	eBF_Step2			= 2,			///< Command Step 2
	eBF_Identify		= 3,			///< Chip Identification
	eBF_EraseStep1		= 4,			///< Erase Data Step 1
	eBF_EraseStep2		= 5,			///< Erase Data Step 2
	eBF_Erase			= 6,			///< Erase Data
	eBF_EraseComplete	= 7,			///< Erase Data Complete
	eBF_Write			= 8,			///< Write Data
	eBF_Bank			= 9,			///< Switch Bank 
	eBF_Max
};

/**
 * @enum agbEBackupEepromState
 * @brief The Eeprom State
 */
enum agbEBackupEepromState
{
	eBE_Wait			= 0,			///< Wait Request
	eBE_Address			= 1,			///< Set Address
	eBE_Ready			= 2,			///< Ready Read Data
	eBE_Read			= 3,			///< Read Data
	eBE_Write			= 4,			///< Write Data
	eBE_Max
};

/** @name Global Variable */
//@{
const u32				g_nAgbBackupSize[AGB_BAK_TYPE_MAX] =					///< The Backup Data Size
						{ 0, 0, 0x8000, 0x10000, 0x20000, 0x200, 0x2000 };
u8						(*agbBakReadGPROM)(u32 nAddr) = NULL;					///< Read 8 bits data from Game Pak RAM
void					(*agbBakWriteGPROM)(u32 nAddr, u8 nData) = NULL;		///< Write 8 bits data to Game Pak RAM
agbEBackupFlashState	g_eAgbFlashState = eBF_Read;							///< Flash Memory State
agbEBackupFlashState	g_eAgbFlashSubState = eBF_Read;							///< Flash Memory Sub State
u8						g_nAgbFlashDeviceID = 0;								///< Flash Memory Device ID
u8						g_nAgbFlashManufacturerID = 0;							///< Flash Memory Manufacturer ID
u32						g_nAgbFlashBank = 0;									///< Flash Memory Bank ID
agbEBackupEepromState	g_eAgbEepromState = eBE_Wait;							///< Eeprom State
u32						g_nAgbEepromByte = 0;									///< Eeprom Current Byte Count
u32						g_nAgbEepromBits = 0;									///< Eeprom Current Bit Count
s32						g_nAgbEepromAddr = -1;									///< Eeprom Fransfer Address
u8						g_nAgbEepromBuff[8] = {0,0,0,0,0,0,0,0};				///< Eeprom Data Buffer
//@}

/** @brief Read 8 bits data from SRAM */
u8 agbBakReadSRAM(u32 nAddr)
{
	return g_pAgbGPRAM[nAddr];
}

/** @brief Write 8 bits data to SRAM */
void agbBakWriteSRAM(u32 nAddr, u8 nData)
{
	g_pAgbGPRAM[nAddr] = nData;
}

/** @brief Read 8 bits data from FLASH */
u8 agbBakReadFLASH(u32 nAddr)
{
	switch(g_eAgbFlashState)
	{
	case eBF_Read:
		return g_pAgbGPRAM[g_nAgbFlashBank + nAddr];
	case eBF_Identify:
		if(nAddr == 0)
			return g_nAgbFlashManufacturerID;
		else if(nAddr == 1)
			return g_nAgbFlashDeviceID;
		break;
	case eBF_EraseComplete:
		g_eAgbFlashState = eBF_Read;
		g_eAgbFlashSubState = eBF_Read;
		return 0xFF;
	};
	return 0;
}

/** @brief Write 8 bits data to FLASH */
void agbBakWriteFLASH(u32 nAddr, u8 nData)
{
	switch(g_eAgbFlashSubState)
	{
	case eBF_Read:
		if(nAddr == 0x5555 && nData == 0xAA)
			g_eAgbFlashSubState = eBF_Step1;
		return;
	case eBF_Step1:
		if(nAddr == 0x2AAA && nData == 0x55)
		{
			g_eAgbFlashSubState = eBF_Step2;
			return;
		}
		break;
	case eBF_Step2:
		if(nAddr == 0x5555)
		{
			switch(nData)
			{
			case 0x80:
				g_eAgbFlashSubState = eBF_EraseStep1;
				return;
			case 0x90:
				g_eAgbFlashState = eBF_Identify;
				g_eAgbFlashSubState = eBF_Identify;
				return;
			case 0xA0:
				g_eAgbFlashSubState = eBF_Write;
				return;
			case 0xB0:
				if(g_pAgbEmuBuf->nBackupType == AGB_BAK_TYPE_FLASH1M)
				{
					g_eAgbFlashSubState = eBF_Bank;
					return;
				}
				break;
			}
		}
		break;
	case eBF_EraseStep1:
		if(nAddr == 0x5555 && nData == 0xAA)
		{
			g_eAgbFlashSubState = eBF_EraseStep2;
			return;
		}
		break;
	case eBF_EraseStep2:
		if(nAddr == 0x2AAA && nData == 0x55)
		{
			g_eAgbFlashSubState = eBF_Erase;
			return;
		}
		break;
	case eBF_Erase:
		switch(nData)
		{
		case 0x10:	// Erase Entire Chip
			memset(g_pAgbGPRAM, 0, g_pAgbEmuBuf->nBackupDataSize);
			g_eAgbFlashState = eBF_EraseComplete;
			return;
		case 0x30:	// Erase 4Kbyte Sector
			memset(&g_pAgbGPRAM[g_nAgbFlashBank + (nAddr & 0xF000)], 0, 0x1000);
			g_eAgbFlashState = eBF_EraseComplete;
			return;
		}
		break;
	case eBF_Identify:
		if(nAddr == 0x5555 && nData == 0xAA)
		{
			g_eAgbFlashSubState = eBF_Step1;
			return;
		}
		break;
	case eBF_Write:
		g_pAgbGPRAM[g_nAgbFlashBank + nAddr] = nData;
		break;
	case eBF_Bank:
		if(nAddr == 0)
			g_nAgbFlashBank = (nData & 1) * 0x10000;
		break;
	}
	g_eAgbFlashState = eBF_Read;
	g_eAgbFlashSubState = eBF_Read;
}

/** @brief Read 8 bits data from EEPROM */
u8 agbBakReadEEPROM()
{
	switch(g_eAgbEepromState)
	{
	case eBE_Ready:
		++g_nAgbEepromBits;
		if(g_nAgbEepromBits == 4)
		{
			g_eAgbEepromState = eBE_Read;
			g_nAgbEepromBits = 0;
		}
		return 0;
	case eBE_Read:
		{
			u8 nData = (g_pAgbGPRAM[g_nAgbEepromAddr] >> (7 - (g_nAgbEepromBits & 7))) & 1;
			++g_nAgbEepromBits;
			if((g_nAgbEepromBits & 7) == 0)
				++g_nAgbEepromAddr;
			if(g_nAgbEepromBits == 64)
				g_eAgbEepromState = eBE_Wait;
			return nData;
		}
	}
	return 1;
}

/** @brief Write 8 bits data to EEPROM */
void agbBakWriteEEPROM(u8 nData)
{
	u8 nBit = nData & 1;
	switch(g_eAgbEepromState)
	{
	case eBE_Wait:
		g_nAgbEepromByte = 0;
		g_nAgbEepromBits = 1;
		g_nAgbEepromAddr = -1;
		g_nAgbEepromBuff[g_nAgbEepromByte] = nBit;
		g_eAgbEepromState = eBE_Address;
		break;
	case eBE_Address:
		g_nAgbEepromBuff[g_nAgbEepromByte] <<= 1;
		g_nAgbEepromBuff[g_nAgbEepromByte] |= nBit;
		++g_nAgbEepromBits;
		if((g_nAgbEepromBits & 7) == 0)
			++g_nAgbEepromByte;
		if(g_pAgbEmuBuf->nBackupType == AGB_BAK_TYPE_EEPROM4)
		{
			if(g_nAgbEepromBits == 0x09)
				g_nAgbEepromAddr = g_nAgbEepromBuff[0] & 0x3F;
		}
		else
		{
			if(g_nAgbEepromBits == 0x11)
				g_nAgbEepromAddr = ((u16*)g_nAgbEepromBuff)[0] & 0x3FFF;
		}
		if(g_nAgbEepromAddr >= 0)
		{
			g_nAgbEepromAddr <<= 3;
			if(g_nAgbEepromBuff[0] & 0x40)
			{
				g_eAgbEepromState = eBE_Ready;
				g_nAgbEepromBits = 0;
			}
			else
			{
				g_nAgbEepromBuff[0] = nBit;          
				g_eAgbEepromState = eBE_Write;
				g_nAgbEepromBits = 1;
			}
			g_nAgbEepromByte = 0;
		}
		break;
	case eBE_Write:
		++g_nAgbEepromBits;
		if(g_nAgbEepromBits > 64)
		{
			g_eAgbEepromState = eBE_Wait;
			break;
		}
		g_nAgbEepromBuff[g_nAgbEepromByte] <<= 1;
		g_nAgbEepromBuff[g_nAgbEepromByte] |= nBit;
		if((g_nAgbEepromBits & 7) == 0)
			++g_nAgbEepromByte;
		if(g_nAgbEepromBits == 64)
			trlMemCopy(&g_pAgbGPRAM[g_nAgbEepromAddr], g_nAgbEepromBuff, 8);
		break;
	}
}

/** @brief Reset Backup */
void agbBakReset()
{
	switch(g_pAgbEmuBuf->nBackupType)
	{
	case AGB_BAK_TYPE_EEPROM4:
	case AGB_BAK_TYPE_EEPROM64:
		g_eAgbEepromState = eBE_Wait;
		g_nAgbEepromByte = 0;
		g_nAgbEepromBits = 0;
		g_nAgbEepromAddr = -1;
		return;
	case AGB_BAK_TYPE_FLASH512:
	case AGB_BAK_TYPE_FLASH1M:
		g_eAgbFlashState = eBF_Read;
		g_eAgbFlashSubState = eBF_Read;
		g_nAgbFlashDeviceID = 0;
		g_nAgbFlashManufacturerID = 0;
		g_nAgbFlashBank = 0;
		return;
	}
}

/** @brief Initialize Backup */
void agbBakInit()
{
	if(g_pAgbEmuBuf->nBackupType == AGB_BAK_TYPE_NONE)
		return;

	// Automatically identify a backup type
	if(g_pAgbEmuBuf->nBackupType == AGB_BAK_TYPE_UNKNOW)
	{
		u8* pRom = (u8*)g_pAgbEmuBuf->pRomBuf;
		u8* pRomEnd = (u8*)g_pAgbEmuBuf->pRomBuf + g_pAgbEmuBuf->nRomBufSize-16;
		for(; pRom < pRomEnd; ++pRom)
		{
			switch(*(u32*)pRom)
			{
			case 0x52504545:	// 4 Kilobit EEPROM or 64 Kilobit EEPROM
				if(!memcmp(pRom+4, "OM_V", 4))
				{
					g_pAgbEmuBuf->nBackupType = AGB_BAK_TYPE_EEPROM4; // Or AGB_BAK_TYPE_EEPROM64
					pRom = pRomEnd;
				}
				break;
			case 0x4D415253:	// 256 Kilobit SRAM
				if(!memcmp(pRom+4, "_V", 2))
				{
					g_pAgbEmuBuf->nBackupType = AGB_BAK_TYPE_SRAM256;
					pRom = pRomEnd;
				}
				break;
			case 0x53414C46:	// Flash ROM
				if(!memcmp(pRom+4, "H_V", 3))			// 512 Kilobit Flash ROM
				{
					g_pAgbEmuBuf->nBackupType = AGB_BAK_TYPE_FLASH512;
					pRom = pRomEnd;
				}
				else if(!memcmp(pRom+4, "H512_V", 6))	// 512 Kilobit Flash ROM
				{
					g_pAgbEmuBuf->nBackupType = AGB_BAK_TYPE_FLASH512;
					pRom = pRomEnd;
				}
				else if(!memcmp(pRom+4, "H1M_V", 5))	// 1 Megabit Flash ROM
				{
					g_pAgbEmuBuf->nBackupType = AGB_BAK_TYPE_FLASH1M;
					pRom = pRomEnd;
				}
				break;
//			case 0x52494953:	// RTC ROM	/*! Unfinished */
//				if(!memcmp(pRom+4, "TC_V", 4))
//				{
//					g_pAgbEmuBuf->nBackupType = ;
//					pRom = pRomEnd;
//				}
//				break;
			}
		}
		if(g_pAgbEmuBuf->nBackupType == AGB_BAK_TYPE_UNKNOW)
		{
			g_pAgbEmuBuf->nBackupType = AGB_BAK_TYPE_NONE;
			return;
		}
	}

	if(g_pAgbEmuBuf->nBackupDataSize )	// Load Backup Data
	{
		if(g_pAgbEmuBuf->nBackupDataSize != g_nAgbBackupSize[g_pAgbEmuBuf->nBackupType])
		{
			TRL_WARN(0, "Savedata size Error.");
			g_pAgbEmuBuf->nBackupDataSize = g_nAgbBackupSize[g_pAgbEmuBuf->nBackupType];
			if(g_pAgbEmuBuf->nBackupDataSize)
			{
				g_pAgbEmuBuf->pBackupData = trlMemAlloc(g_pAgbEmuBuf->nBackupDataSize);
				memset(g_pAgbEmuBuf->pBackupData, 0, g_pAgbEmuBuf->nBackupDataSize);
			}
		}
	}
	else		// Initialize Backup Data
	{
		g_pAgbEmuBuf->nBackupDataSize = g_nAgbBackupSize[g_pAgbEmuBuf->nBackupType];
		if(g_pAgbEmuBuf->nBackupDataSize)
		{
			g_pAgbEmuBuf->pBackupData = trlMemAlloc(g_pAgbEmuBuf->nBackupDataSize);
			memset(g_pAgbEmuBuf->pBackupData, 0, g_pAgbEmuBuf->nBackupDataSize);
		}
	}
	g_pAgbGPRAM = (u8*)g_pAgbEmuBuf->pBackupData;

	switch(g_pAgbEmuBuf->nBackupType)
	{
	case AGB_BAK_TYPE_SRAM256:
		agbBakReadGPROM = agbBakReadSRAM;
		agbBakWriteGPROM = agbBakWriteSRAM;
		break;
	case AGB_BAK_TYPE_FLASH512:
	case AGB_BAK_TYPE_FLASH1M:
		agbBakReadGPROM = agbBakReadFLASH;
		agbBakWriteGPROM = agbBakWriteFLASH;
		break;
	}

	agbBakReset();
}

/** @brief Exit Backup */
void agbBakExit()
{
	trlMemFree(g_pAgbGPRAM);
}
