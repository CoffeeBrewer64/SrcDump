/**
 * @file cgbCard.cpp
 * @author Chentian
 * @date 2009.11.19
 * @brief CGB Emulate For CTR - Cartridge
 */
#include "cgbCard.h"
#include "cgbDMA.h"
#include "cgbCPU.h"
#include "cgbMemory.h"

/** @name Global Variable */
//@{
u8*		g_pCgbCurROM = NULL;		///< Current ROM Bank
u8*		g_pCgbCurERAM = NULL;		///< Current External RAM Bank
u8*		g_pCgbERAMMBC4N64 = NULL;	///< The MBC4 N64-GB Communicate RAM
u8*		g_pCgbMBC3RTCReg = NULL;	///< The MBC3 RTC Register
u64*	g_pCgbMBC3Timer = NULL;		///< The MBC3 Timer

u32		g_nCgbRAMEnable = 0;		///< RAM Enable Flag by Read/Write
u32		g_nCgbROMBank = 1;			///< ROM Bank Number
u32		g_nCgbRAMBank = 0;			///< External RAM Bank Number
u32		g_nCgbROMBankMask = 0;		///< ROM Bank Mask
u32		g_nCgbRAMBankMask = 0;		///< RAM Bank Mask
u32		g_nCgbCardERAMSize = 0;		///< ERAM Size
u32		g_nCgbMBC1Mode = 2;			///< The MBC1 ROM/RAM Mode Select Register
u32		g_nCgbMBC3RTCSelect = 0;	///< The MBC3 RTC Select Register
u32		g_nCgbMBC3ClockLatch = 0;	///< The MBC3 Latch Clock Register
u8		g_nCgbMBC3RTCLatch[8];		///< The MBC3 RTC Latch Register
u32		g_nCgbMBC4N64 = 0;			///< The MBC4 N64-GB Communicate Flag
u32		g_nCgbMBC5Rumble = 0;		///< The MBC5 Rumble On/Off Flag
u32		g_nCgbCardWriteFlag = 0;	///< Card RAM Write Flag

void	(*cgbCardRegister)(u16, u8) = NULL;		///< Game Card RAM Register Function Pointer
void	(*cgbCardWriteRAM)(u16, u8) = NULL;		///< Game Card RAM Write Function Pointer
u8		(*cgbCardReadRAM)(u16) = NULL;			///< Game Card RAM Read Function Pointer
trlSEmuShellResume	g_sCgbCardSaveData[CGB_CARD_SAVEDATA];	///< Card Save Data
//@}

/** @brief Update Cpu PC */
inline void cgbCardUpdatePC()
{
//	if((g_nCgbCpuRegPC >= 0x4000 && g_nCgbCpuRegPC < 0x8000) || (g_nCgbCpuRegPC >= 0xA000 && g_nCgbCpuRegPC < 0xC000))
	if(g_nCgbCpuRegPC >= 0x4000 && g_nCgbCpuRegPC < 0x8000)
	{
//		NN_LOG("CpuPC: cgbCardUpdatePC()\n");
		g_pCgbCpuPC = &g_pCgbCurROM[g_nCgbCpuRegPC-0x4000];
	}
}

/** @brief Write MBC RAM Data */
void cgbCardWriteRamMBC(u16 nAddr, u8 nValue)
{
	if(g_nCgbRAMEnable)
	{
		g_pCgbCurERAM[nAddr-0xA000] = nValue;
		g_nCgbCardWriteFlag = 1;
	}
}

/** @brief Read MBC RAM Data */
u8 cgbCardReadRamMBC(u16 nAddr)
{
	if(g_nCgbRAMEnable)
		return g_pCgbCurERAM[nAddr-0xA000];
	return 0xFF;
}

/** @brief Write MBC1 Register */
void cgbCardRegisterMBC1(u16 nAddr, u8 nValue)
{
	switch(nAddr & 0x6000)
	{
	case 0x0000: // RAM Enable Register
		nValue &= 0x0A;
		g_nCgbRAMEnable = (nValue==0x0A);
		if(g_nCgbCardWriteFlag)
		{
			g_nCgbCardWriteFlag = 0;
			g_pCgbEmuBuf->nSaveUpdate |= 1;
		}
		return;
	case 0x2000: // ROM Bank Number
		nValue &= 0x1F;
		if(nValue == 0)
			nValue = 1;
		if(nValue == g_nCgbROMBank)
			return;
	    g_nCgbROMBank = nValue;
		if(g_nCgbMBC1Mode)
			g_pCgbCurROM = &g_pCgbROM[(g_nCgbROMBank & g_nCgbROMBankMask) * 0x4000];
		else
			g_pCgbCurROM = &g_pCgbROM[((g_nCgbROMBank+(g_nCgbRAMBank<<5)) & g_nCgbROMBankMask) * 0x4000];
		cgbCardUpdatePC();
		return;
	case 0x4000: // External RAM Bank Number
		nValue &= 0x3;
		if(nValue == g_nCgbRAMBank)
			return;
	    g_nCgbRAMBank = nValue;
	    if(g_nCgbMBC1Mode)
			g_pCgbCurERAM = &g_pCgbERAM[(g_nCgbRAMBank & g_nCgbRAMBankMask) * 0x2000];
	    else
	    {
			g_pCgbCurROM = &g_pCgbROM[((g_nCgbROMBank+(g_nCgbRAMBank<<5)) & g_nCgbROMBankMask) * 0x4000];
			cgbCardUpdatePC();
	    }
		return;
	case 0x6000: // ROM/RAM Mode Select
		nValue &= 0x1;
		if(nValue == g_nCgbMBC1Mode)
			return;
	    g_nCgbMBC1Mode = nValue;
	    if(g_nCgbMBC1Mode)
	    {
			g_pCgbCurROM = &g_pCgbROM[(g_nCgbROMBank & g_nCgbROMBankMask) * 0x4000];
			g_pCgbCurERAM = &g_pCgbERAM[(g_nCgbRAMBank & g_nCgbRAMBankMask) * 0x2000];
	    }
	    else
	    {
			g_pCgbCurROM = &g_pCgbROM[((g_nCgbROMBank+(g_nCgbRAMBank<<5)) & g_nCgbROMBankMask) * 0x4000];
	    	g_pCgbCurERAM = g_pCgbERAM;
	    }
		cgbCardUpdatePC();
		return;
	}
}

/** @brief Write MBC2 Register */
void cgbCardRegisterMBC2(u16 nAddr, u8 nValue)
{
	switch(nAddr & 0x6000)
	{
	case 0x0000: // RAM Enable Register
		if(nAddr & 0x0100)
			return;
		nValue &= 0x0F;
		g_nCgbRAMEnable = (nValue==0x0A);
		if(g_nCgbCardWriteFlag)
		{
			g_nCgbCardWriteFlag = 0;
			g_pCgbEmuBuf->nSaveUpdate |= 1;
		}
		return;
	case 0x2000: // ROM Bank Number
		if(!(nAddr & 0x0100))
			return;
		nValue &= 0x0F;
		if(nValue == 0)
			nValue = 1;
		if(nValue == g_nCgbROMBank)
			return;
	    g_nCgbROMBank = nValue;
		g_pCgbCurROM = &g_pCgbROM[(g_nCgbROMBank & g_nCgbROMBankMask) * 0x4000];
		cgbCardUpdatePC();
		return;
	}
}

/** @brief Write MBC2 RAM Data */
void cgbCardWriteRamMBC2(u16 nAddr, u8 nValue)
{
	if(g_nCgbRAMEnable)
	{
		g_pCgbCurERAM[nAddr-0xA000] = nValue & 0x0F;
		g_nCgbCardWriteFlag = 1;
	}
}

/** @brief Write MBC3 Register */
void cgbCardRegisterMBC3(u16 nAddr, u8 nValue)
{
	switch(nAddr & 0x6000)
	{
	case 0x0000: // RAM Enable Register
		nValue &= 0x0A;
		g_nCgbRAMEnable = (nValue==0x0A);
		if(g_nCgbCardWriteFlag)
		{
			g_nCgbCardWriteFlag = 0;
			g_pCgbEmuBuf->nSaveUpdate |= 1;
		}
		return;
	case 0x2000: // ROM Bank Number
		nValue &= 0x7F;
		if(nValue == 0)
			nValue = 1;
		if(nValue == g_nCgbROMBank)
			return;
		g_nCgbROMBank = nValue;
		g_pCgbCurROM = &g_pCgbROM[(g_nCgbROMBank & g_nCgbROMBankMask) * 0x4000];
		cgbCardUpdatePC();
		return;
	case 0x4000: // External RAM Bank Number
		if(nValue > 3)
			return;
		if(nValue == g_nCgbRAMBank)
			return;
		g_nCgbRAMBank = nValue;
		g_pCgbCurERAM = &g_pCgbERAM[(g_nCgbRAMBank & g_nCgbRAMBankMask) * 0x2000];
		return;
	}
}

/** @brief Update MBC3 Timer */
inline void cgbCardUpdateMBC3Timer()
{
	if(*g_pCgbMBC3Timer == 0)
		*g_pCgbMBC3Timer = trlTimeGetNow();

	u64 nCurTime = trlTimeGetNow();
	s32 nTime = trlTimeGetElapsedTime(*g_pCgbMBC3Timer, nCurTime);
	if(nTime > 0)
	{
		g_pCgbMBC3RTCReg[0] += (u8)(nTime % 60);
		if(g_pCgbMBC3RTCReg[0] > 59)
		{
			g_pCgbMBC3RTCReg[0] -= 60;
			g_pCgbMBC3RTCReg[1]++;
		}
		nTime /= 60;
		g_pCgbMBC3RTCReg[1] += (u8)(nTime % 60);
		if(g_pCgbMBC3RTCReg[1] > 59)
		{
			g_pCgbMBC3RTCReg[1] -= 60;
			g_pCgbMBC3RTCReg[2]++;
		}
		nTime /= 60;
		u32 nDay = ((g_pCgbMBC3RTCReg[4] & 0x01) << 8) + g_pCgbMBC3RTCReg[3];
		g_pCgbMBC3RTCReg[2] += (u8)(nTime % 24);
		if(g_pCgbMBC3RTCReg[2] > 23)
		{
			g_pCgbMBC3RTCReg[2] -= 24;
			nDay++;
		}
		nTime /= 24;
		nDay += (u32)nTime;
		g_pCgbMBC3RTCReg[3] = nDay & 0xFF;
		g_pCgbMBC3RTCReg[4] = (g_pCgbMBC3RTCReg[4] & 0xFE) | ((nDay>>8) & 0x01) | ((nDay > 0x1FF) ? 0x80 : 0);
	}
	*g_pCgbMBC3Timer = nCurTime;
}

/** @brief Write MBC3 Register With Timer */
void cgbCardRegisterMBC3Timer(u16 nAddr, u8 nValue)
{
	switch(nAddr & 0x6000)
	{
	case 0x0000: // RAM Enable Register
		nValue &= 0x0A;
		g_nCgbRAMEnable = (nValue==0x0A);
		if(g_nCgbCardWriteFlag)
		{
			g_nCgbCardWriteFlag = 0;
			cgbCardUpdateMBC3Timer();
			g_pCgbEmuBuf->nSaveUpdate |= 1;
		}
		return;
	case 0x2000: // ROM Bank Number
		nValue &= 0x7F;
		if(nValue == 0)
			nValue = 1;
		if(nValue == g_nCgbROMBank)
			return;
		g_nCgbROMBank = nValue;
		g_pCgbCurROM = &g_pCgbROM[(g_nCgbROMBank & g_nCgbROMBankMask) * 0x4000];
		cgbCardUpdatePC();
		return;
	case 0x4000: // External RAM Bank Number and RTC Register Select
		if(nValue < 8)
		{
			if(nValue > 3)
				return;
			g_nCgbMBC3RTCSelect = 0;
			if(nValue == g_nCgbRAMBank)
				return;
			g_nCgbRAMBank = nValue;
			g_pCgbCurERAM = &g_pCgbERAM[(g_nCgbRAMBank & g_nCgbRAMBankMask) * 0x2000];
		}
		else
			g_nCgbMBC3RTCSelect = nValue;
		return;
	case 0x6000: // Latch Clock Data
		nValue &= 0x1;
		if(g_nCgbMBC3ClockLatch == 0 && nValue == 1)
		{
			if((g_pCgbMBC3RTCReg[4] & 0x40) == 0)
				cgbCardUpdateMBC3Timer();
			trlMemCopy(g_nCgbMBC3RTCLatch, g_pCgbMBC3RTCReg, 8);
		}
		g_nCgbMBC3ClockLatch = nValue;
		return;
	}
}

/** @brief Write MBC3 RAM Data With Timer */
void cgbCardWriteRamMBC3Timer(u16 nAddr, u8 nValue)
{
	if(!g_nCgbRAMEnable)
		return;
	switch(g_nCgbMBC3RTCSelect)
	{
	case 0:
		g_pCgbCurERAM[nAddr-0xA000] = nValue;
		g_nCgbCardWriteFlag = 1;
		return;
	case 0x08:		// Seconds
        g_pCgbMBC3RTCReg[0] = nValue;
		return;
	case 0x09:		// Minutes
        g_pCgbMBC3RTCReg[1] = nValue;
		return;
	case 0x0A:		// Hours
        g_pCgbMBC3RTCReg[2] = nValue;
		return;
	case 0x0B:		// Lower 8 bits of Day Counter
        g_pCgbMBC3RTCReg[3] = nValue;
		return;
	case 0x0C:		// Upper 1 bit of Day Counter, Carry Bit, Halt Flag
		nValue &= 0xC1;
		if((g_pCgbMBC3RTCReg[4] ^ nValue) & 0x40)
		{
			if(nValue & 0x40)
				cgbCardUpdateMBC3Timer();
			else
				*g_pCgbMBC3Timer = trlTimeGetNow();
		}
		g_pCgbMBC3RTCReg[4] = nValue;
		return;
	}
}

/** @brief Read MBC3 RAM Data With Timer */
u8 cgbCardReadRamMBC3Timer(u16 nAddr)
{
	if(!g_nCgbRAMEnable)
		return 0xFF;
	switch(g_nCgbMBC3RTCSelect)
	{
	case 0:
		return g_pCgbCurERAM[nAddr-0xA000];
	case 0x08:		// Seconds
		return g_nCgbMBC3RTCLatch[0];
	case 0x09:		// Minutes
        return g_nCgbMBC3RTCLatch[1];
	case 0x0A:		// Hours
        return g_nCgbMBC3RTCLatch[2];
	case 0x0B:		// Lower 8 bits of Day Counter
        return g_nCgbMBC3RTCLatch[3];
	case 0x0C:		// Upper 1 bit of Day Counter, Carry Bit, Halt Flag
        return g_nCgbMBC3RTCLatch[4];
	}	
	return 0xFF;
}

/** @brief Write MBC4 Register */
void cgbCardRegisterMBC4(u16 nAddr, u8 nValue)
{
	switch(nAddr & 0x6000)
	{
	case 0x0000: // RAM Enable Register
		nValue &= 0x0A;
		g_nCgbRAMEnable = (nValue==0x0A);
		if(g_nCgbCardWriteFlag)
		{
			g_nCgbCardWriteFlag = 0;
			g_pCgbEmuBuf->nSaveUpdate |= 1;
		}
		return;
	case 0x2000: // ROM Bank Number
		nValue &= 0x7F;
		if(nValue == 0)
			nValue = 1;
		if(nValue == g_nCgbROMBank)
			return;
		g_nCgbROMBank = nValue;
		g_pCgbCurROM = &g_pCgbROM[(g_nCgbROMBank & g_nCgbROMBankMask) * 0x4000];
		cgbCardUpdatePC();
		return;
	case 0x4000: // External RAM Bank Number and RTC Register Select
		if(nValue == g_nCgbRAMBank)
			return;
		g_nCgbRAMBank = nValue;
		if(g_nCgbRAMBank == 0x40)
			g_pCgbCurERAM = g_pCgbERAMMBC4N64;
		else
			g_pCgbCurERAM = &g_pCgbERAM[(g_nCgbRAMBank & g_nCgbRAMBankMask) * 0x2000];
		return;
	}
}

/** @brief Write MBC5 Register */
void cgbCardRegisterMBC5(u16 nAddr, u8 nValue)
{
	switch(nAddr & 0x6000)
	{
	case 0x0000: // RAM Enable Register
		nValue &= 0x0A;
		g_nCgbRAMEnable = (nValue==0x0A);
		if(g_nCgbCardWriteFlag)
		{
			g_nCgbCardWriteFlag = 0;
			g_pCgbEmuBuf->nSaveUpdate |= 1;
		}
		return;
	case 0x2000: // ROM Bank Number
		if(nAddr < 0x3000)
		{
			if(nValue == (g_nCgbROMBank & 0xFF))
				return;
			g_nCgbROMBank = (g_nCgbROMBank & 0x0100) + nValue;
		}
		else
		{
			nValue &= 0x1;
			if(nValue == (g_nCgbROMBank>>8))
				return;
			g_nCgbROMBank = (g_nCgbROMBank & 0xFF) | (nValue << 8);
		}
		g_pCgbCurROM = &g_pCgbROM[(g_nCgbROMBank & g_nCgbROMBankMask) * 0x4000];
		cgbCardUpdatePC();
		return;
	case 0x4000: // External RAM Bank Number
		nValue &= 0x0F;
		if(nValue == g_nCgbRAMBank)
			return;
		g_nCgbRAMBank = nValue;
		g_pCgbCurERAM = &g_pCgbERAM[(g_nCgbRAMBank & g_nCgbRAMBankMask) * 0x2000];
		return;
	}
}

/** @brief Write MBC5 Register With Rumble */
void cgbCardRegisterMBC5Rumble(u16 nAddr, u8 nValue)
{
	switch(nAddr & 0x6000)
	{
	case 0x0000: // RAM Enable Register
		nValue &= 0x0A;
		g_nCgbRAMEnable = (nValue==0x0A);
		if(g_nCgbCardWriteFlag)
		{
			g_nCgbCardWriteFlag = 0;
			g_pCgbEmuBuf->nSaveUpdate |= 1;
		}
		return;
	case 0x2000: // ROM Bank Number
		if(nAddr < 0x3000)
		{
			if(nValue == g_nCgbROMBank)
				return;
			g_nCgbROMBank = (g_nCgbROMBank & 0x0100) + nValue;
		}
		else
		{
			nValue &= 0x1;
			if(nValue == (g_nCgbROMBank>>8))
				return;
			g_nCgbROMBank = (g_nCgbROMBank & 0xFF) | (nValue << 8);
		}
		g_pCgbCurROM = &g_pCgbROM[(g_nCgbROMBank & g_nCgbROMBankMask) * 0x4000];
		cgbCardUpdatePC();
		return;
	case 0x4000: // External RAM Bank Number, Rumble
		g_nCgbMBC5Rumble = (nValue >> 3) & 0x1;
		nValue &= 0x07;
		if(nValue == g_nCgbRAMBank)
			return;
		g_nCgbRAMBank = nValue;
		g_pCgbCurERAM = &g_pCgbERAM[(g_nCgbRAMBank & g_nCgbRAMBankMask) * 0x2000];
		return;
	}
}

/** @brief Read HuC1 RAM Data */
u8 cgbCardReadRamHuC1(u16 nAddr)
{
	return g_pCgbCurERAM[nAddr-0xA000];
}

/** @brief Write HuC1 Register */
void cgbCardRegisterHuC1(u16 nAddr, u8 nValue)
{
	switch(nAddr & 0x6000)
	{
	case 0x0000: // RAM Enable Register
		nValue &= 0x0A;
		g_nCgbRAMEnable = (nValue==0x0A);
		if(g_nCgbCardWriteFlag)
		{
			g_nCgbCardWriteFlag = 0;
			g_pCgbEmuBuf->nSaveUpdate |= 1;
		}
		return;
	case 0x2000: // ROM Bank Number
		nValue &= 0x3F;
		if(nValue == 0)
			nValue = 1;
		if(nValue == g_nCgbROMBank)
			return;
	    g_nCgbROMBank = nValue;
		if(g_nCgbMBC1Mode)
			g_pCgbCurROM = &g_pCgbROM[(g_nCgbROMBank & g_nCgbROMBankMask) * 0x4000];
		else
			g_pCgbCurROM = &g_pCgbROM[((g_nCgbROMBank+(g_nCgbRAMBank<<6)) & g_nCgbROMBankMask) * 0x4000];
		cgbCardUpdatePC();
		return;
	case 0x4000: // RAM Bank Number
		nValue &= 0x3;
		if(nValue == g_nCgbRAMBank)
			return;
	    g_nCgbRAMBank = nValue;
	    if(g_nCgbMBC1Mode)
			g_pCgbCurERAM = &g_pCgbERAM[(g_nCgbRAMBank & g_nCgbRAMBankMask) * 0x2000];
	    else
		{
			g_pCgbCurROM = &g_pCgbROM[((g_nCgbROMBank+(g_nCgbRAMBank<<6)) & g_nCgbROMBankMask) * 0x4000];
			cgbCardUpdatePC();
		}
		return;
	case 0x6000: // ROM/RAM Mode Select
		nValue &= 0x1;
		if(nValue == g_nCgbMBC1Mode)
			return;
	    g_nCgbMBC1Mode = nValue;
	    if(g_nCgbMBC1Mode)
	    {
			g_pCgbCurROM = &g_pCgbROM[(g_nCgbROMBank & g_nCgbROMBankMask) * 0x4000];
			g_pCgbCurERAM = &g_pCgbERAM[(g_nCgbRAMBank & g_nCgbRAMBankMask) * 0x2000];
	    }
	    else
	    {
			g_pCgbCurROM = &g_pCgbROM[((g_nCgbROMBank+(g_nCgbRAMBank<<6)) & g_nCgbROMBankMask) * 0x4000];
	    	g_pCgbCurERAM = g_pCgbERAM;
	    }
		cgbCardUpdatePC();
		return;
	}
}

/** @brief Initialize Card */
void cgbCardInit()
{
	// Get Rom Size
	switch(g_pCgbROMHeader->nROMSize)
	{
	case 0x00:	// 256Kbit (2 banks)
		g_nCgbROMBankMask = 0x01;
		break;
	case 0x01:	// 512Kbit (4 banks)
		g_nCgbROMBankMask = 0x03;
		break;
	case 0x02:	// 1Mbit (8 banks)
		g_nCgbROMBankMask = 0x07;
		break;
	case 0x03:	// 2Mbit (16 banks)
		g_nCgbROMBankMask = 0x0F;
		break;
	case 0x04:	// 4Mbit (32 banks)
		g_nCgbROMBankMask = 0x1F;
		break;
	case 0x05:	// 8Mbit (64 banks)
		g_nCgbROMBankMask = 0x3F;
		break;
	case 0x06:	// 16Mbit (128 banks)
		g_nCgbROMBankMask = 0x7F;
		break;
	case 0x07:	// 32Mbit (256 banks)
		g_nCgbROMBankMask = 0xFF;
		break;
	case 0x52:	// 9Mbit (72 banks)
		g_nCgbROMBankMask = 0x7F;
		break;
	case 0x53:	// 10Mbit (80 banks)
		g_nCgbROMBankMask = 0xFF;
		break;
	case 0x54:	// 12Mbit (96 banks)
		g_nCgbROMBankMask = 0xFF;
		break;
	default:
		NN_LOG("Unknow ROM Size: cgbMemInit  size = %d\n", g_pCgbROMHeader->nROMSize);
	}

	// Get Ram Size
	switch(g_pCgbROMHeader->nRAMSize)
	{
	case 0:		// None
		g_nCgbCardERAMSize = 0;
		g_nCgbRAMBankMask = 0x00;
		g_pCgbERAM = NULL;
		break;
	case 1:		// 16kBit (1 bank)
		g_nCgbCardERAMSize = 0x800;
		g_nCgbRAMBankMask = 0x00;
		break;
	case 2:		// 64kBit (1 bank)
		g_nCgbCardERAMSize = 0x2000;
		g_nCgbRAMBankMask = 0x00;
		break;
	case 3:		// 256kBit (4 banks)
		g_nCgbCardERAMSize = 0x8000;
		g_nCgbRAMBankMask = 0x03;
		break;
	case 4:		// 1MBit (16 banks)
		g_nCgbCardERAMSize = 0x20000;
		g_nCgbRAMBankMask = 0x0F;
		break;
	case 5:		// 512kBit (8 banks)
		g_nCgbCardERAMSize = 0x10000;
		g_nCgbRAMBankMask = 0x07;
		break;
	default:
		NN_LOG("Unknow RAM Size: cgbMemInit  size = %d\n", g_pCgbROMHeader->nRAMSize);
	}

	// Get Cart Type
	u32 bTimer = 0;
	u32 bBattery = 0;
	cgbCardRegister = NULL;
	cgbCardWriteRAM = NULL;
	cgbCardReadRAM = NULL;
	g_nCgbMBC1Mode = 2;
	switch(g_pCgbROMHeader->nCartType)
	{
	case 0x09:	// ROM+RAM+BATTERY
		bBattery = 1;
	case 0x08:	// ROM+RAM
	case 0x00:	// ROM ONLY
		break;
		
	case 0x03:	// MBC1+RAM+BATTERY
		bBattery = 1;
	case 0x02:	// MBC1+RAM
		cgbCardWriteRAM = cgbCardWriteRamMBC;
		cgbCardReadRAM = cgbCardReadRamMBC;
	case 0x01:	// MBC1
		cgbCardRegister = cgbCardRegisterMBC1;
		g_nCgbMBC1Mode = 0;
		break;
		
	case 0x06:	// MBC2+BATTERY
		cgbCardWriteRAM = cgbCardWriteRamMBC2;
		cgbCardReadRAM = cgbCardReadRamMBC;
		g_nCgbCardERAMSize = 0x200;
		bBattery = 1;
	case 0x05:	// MBC2
		cgbCardRegister = cgbCardRegisterMBC2;
		break;
		
	case 0x10:	// MBC3+TIMER+RAM+BATTERY
	case 0x0F:	// MBC3+TIMER+BATTERY
		g_nCgbCardERAMSize += 16;
		cgbCardWriteRAM = cgbCardWriteRamMBC3Timer;
		cgbCardReadRAM = cgbCardReadRamMBC3Timer;
		cgbCardRegister = cgbCardRegisterMBC3Timer;
		bTimer = 1;
		bBattery = 1;
		break;
				
	case 0x13:	// MBC3+RAM+BATTERY
		bBattery = 1;
	case 0x12:	// MBC3+RAM
		cgbCardWriteRAM = cgbCardWriteRamMBC;
		cgbCardReadRAM = cgbCardReadRamMBC;
	case 0x11:	// MBC3
		cgbCardRegister = cgbCardRegisterMBC3;
		break;
		
	case 0x17:	// MBC4+RAM+BATTERY
		bBattery = 1;
	case 0x16:	// MBC4+RAM
		cgbCardWriteRAM = cgbCardWriteRamMBC;
		cgbCardReadRAM = cgbCardReadRamMBC;
	case 0x15:	// MBC4
		cgbCardRegister = cgbCardRegisterMBC4;
		g_pCgbERAMMBC4N64 = (u8*)trlMemAlloc(0x2000);
		break;
		
	case 0x1E:	// MBC5+RUMBLE+RAM+BATTERY
		bBattery = 1;
	case 0x1D:	// MBC5+RUMBLE+RAM
		cgbCardWriteRAM = cgbCardWriteRamMBC;
		cgbCardReadRAM = cgbCardReadRamMBC;
	case 0x1C:	// MBC5+RUMBLE
		cgbCardRegister = cgbCardRegisterMBC5Rumble;
		break;
	
	case 0x1B:	// MBC5+RAM+BATTERY
		bBattery = 1;
	case 0x1A:	// MBC5+RAM
		cgbCardWriteRAM = cgbCardWriteRamMBC;
		cgbCardReadRAM = cgbCardReadRamMBC;
	case 0x19:	// MBC5
		cgbCardRegister = cgbCardRegisterMBC5;
		break;
		
	case 0xFF:	// HuC1+RAM+BATTERY
		cgbCardWriteRAM = cgbCardWriteRamMBC;
		cgbCardReadRAM = cgbCardReadRamHuC1;
		cgbCardRegister = cgbCardRegisterHuC1;
		g_nCgbMBC1Mode = 0;
		bBattery = 1;
		break;

	case 0x0D:	// MMM01+BATTERY
		bBattery = 1;
	case 0x0C:	// MMM01+RAM
	case 0x0B:	// MMM01
	case 0xFC:	// POCKET CAMERA
	case 0xFD:	// BANDAI TAMA5
	case 0xFE:	// HuC3
		NN_LOG("Unfinished Cart Type: 0x%02X\n", g_pCgbROMHeader->nCartType);
		break;
	default:
		NN_LOG("Unknow Cart Type: 0x%02X\n", g_pCgbROMHeader->nCartType);
	}

	// Backup Data
	if(g_nCgbCardERAMSize)
	{
		g_pCgbERAM = (u8*)trlMemAlloc(g_nCgbCardERAMSize);
		{
			u8 eramvalue = g_pCgbEmuBuf->funcConfigData("CGB", "SDataInitValue", 0);
			memset(g_pCgbERAM, eramvalue, g_nCgbCardERAMSize);
		}

		if(bBattery)
		{
			g_pCgbEmuBuf->nBackupDataSize = g_nCgbCardERAMSize;
			g_pCgbEmuBuf->pBackupData = g_pCgbERAM;
		}
	}

	// Timer
	g_pCgbMBC3RTCReg = NULL;
	g_pCgbMBC3Timer = NULL;
	if(bTimer)
	{
		g_pCgbMBC3RTCReg = g_pCgbERAM + g_nCgbCardERAMSize - 16;
		g_pCgbMBC3Timer = (u64*)(g_pCgbERAM + g_nCgbCardERAMSize - 8);
	}

	// Save Data
	g_sCgbCardSaveData[0].SetData(g_pCgbERAM, g_nCgbCardERAMSize, 1, 0);
	g_sCgbCardSaveData[1].SetData(&g_nCgbRAMEnable, 4, 1, 0);
	g_sCgbCardSaveData[2].SetData(&g_nCgbROMBank, 4, 1, 0);
	g_sCgbCardSaveData[3].SetData(&g_nCgbRAMBank, 4, 1, 0);
	g_sCgbCardSaveData[4].SetData(&g_nCgbMBC1Mode, 4, 1, 0);
	g_sCgbCardSaveData[5].SetData(&g_nCgbMBC3RTCSelect, 4, 1, 0);
	g_sCgbCardSaveData[6].SetData(&g_nCgbMBC3ClockLatch, 4, 1, 0);
	g_sCgbCardSaveData[7].SetData(g_nCgbMBC3RTCLatch, 8, 9, 0);
	g_sCgbCardSaveData[8].SetData(NULL, 4, 1, 9);
	g_sCgbCardSaveData[9].SetData(NULL, 4, 1, 9);
	g_sCgbCardSaveData[10].SetData(NULL, 4, 1, 9);
	g_sCgbCardSaveData[11].SetData(NULL, 4, 1, 9);
	g_sCgbCardSaveData[12].SetData(NULL, 4, 1, 9);
	g_sCgbCardSaveData[13].SetData(NULL, 8, 1, 9);
	g_sCgbCardSaveData[14].SetData(NULL, 8, 8, 9);
	g_sCgbCardSaveData[15].SetData(NULL, 8, 8, 9);
	g_sCgbCardSaveData[16].SetData(&g_nCgbMBC4N64, 4, 1, 0);
	g_sCgbCardSaveData[17].SetData(&g_nCgbMBC5Rumble, 4, 1, 0);
	g_sCgbCardSaveData[18].SetData(&g_nCgbCardWriteFlag, 4, 1, 0);

	cgbCardReset();
}

/** @brief Reset Card */
void cgbCardReset()
{
	if(g_nCgbCardWriteFlag && g_nCgbRAMEnable)
		g_pCgbEmuBuf->funcSaveBackup();

	g_nCgbRAMEnable = 0;
	g_nCgbROMBank = 1;
	g_nCgbRAMBank = 0;
	if(g_nCgbMBC1Mode != 2)
		g_nCgbMBC1Mode = 0;
	if(g_pCgbMBC3Timer)
	{
		g_nCgbMBC3RTCSelect = 0;
		g_nCgbMBC3ClockLatch = 0;
	}
	g_nCgbMBC4N64 = 0;
	g_nCgbMBC5Rumble = 0;
	g_nCgbCardWriteFlag = 0;
	g_pCgbCurROM = &g_pCgbROM[0x4000];
	g_pCgbCurERAM = g_pCgbERAM;
}

/** @brief Resume Card */
void cgbCardResume()
{
	switch(g_nCgbMBC1Mode)
	{
	case 0:		// MBC1 Mode 0
		g_pCgbCurROM = &g_pCgbROM[((g_nCgbROMBank+(g_nCgbRAMBank<<5)) & g_nCgbROMBankMask) * 0x4000];
    	g_pCgbCurERAM = g_pCgbERAM;
		break;
	case 1:		// MBC1 Mode 1
	case 2:		// Normal
		g_pCgbCurROM = &g_pCgbROM[(g_nCgbROMBank & g_nCgbROMBankMask) * 0x4000];
		g_pCgbCurERAM = &g_pCgbERAM[(g_nCgbRAMBank & g_nCgbRAMBankMask) * 0x2000];
		break;
	}
}

/** @brief Exit Card */
void cgbCardExit()
{
//	if(g_nCgbCardWriteFlag && g_nCgbRAMEnable)
		g_pCgbEmuBuf->funcSaveBackup();

	switch(g_pCgbROMHeader->nCartType)
	{
	case 0x17:	// MBC4+RAM+BATTERY
	case 0x16:	// MBC4+RAM
	case 0x15:	// MBC4
		trlMemFree(g_pCgbERAMMBC4N64);
		break;
	}
	if(g_nCgbCardERAMSize)
		trlMemFree(g_pCgbERAM);
}
