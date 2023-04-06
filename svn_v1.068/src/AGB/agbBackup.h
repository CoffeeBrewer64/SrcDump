/**
 * @file agbBackup.h
 * @author Chentian
 * @date 2009.11.23
 * @brief AGB Emulate For CTR - Backup
 */
#pragma once
#include "agbGlobal.h"

/** @name Macro Define */
//@{
#define AGB_BAK_TYPE_UNKNOW			0		///< Unknow
#define AGB_BAK_TYPE_NONE			1		///< None
#define AGB_BAK_TYPE_SRAM256		2		///< 256 Kilobit SRAM
#define AGB_BAK_TYPE_FLASH512		3		///< 512 Kilobit Flash ROM
#define AGB_BAK_TYPE_FLASH1M		4		///< 1 Megabit Flash ROM
#define AGB_BAK_TYPE_EEPROM4		5		///< 4 Kilobit EEPROM
#define AGB_BAK_TYPE_EEPROM64		6		///< 64 Kilobit EEPROM
#define AGB_BAK_TYPE_MAX			7		///< Type Max Value
//@}

/** @name Global Variable */
//@{
//@}

/** @brief Initialize Backup */
void agbBakInit();
/** @brief Reset Backup */
void agbBakReset();
/** @brief Exit Backup */
void agbBakExit();

/** @brief Read 8 bits data from Game Pak RAM */
extern u8 (*agbBakReadGPROM)(u32 nAddr);
/** @brief Write 8 bits data to Game Pak RAM */
extern void (*agbBakWriteGPROM)(u32 nAddr, u8 nData);

/** @brief Read 8 bits data from EEPROM */
u8 agbBakReadEEPROM();
/** @brief Write 8 bits data to EEPROM */
void agbBakWriteEEPROM(u8 nData);
