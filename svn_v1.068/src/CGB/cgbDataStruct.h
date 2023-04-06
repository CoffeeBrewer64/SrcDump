/**
 * @file cgbDataStruct.h
 * @author Chentian
 * @date 2009.11.18
 * @brief CGB Emulate For CTR - Data Structs
 */
#pragma once
#include "cgbGlobal.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
//@}

/**
 * @struct cgbSRegJOYP
 * @brief REG: FF00 - P1/JOYP - Joypad (R/W)
 */
struct cgbSRegJOYP
{
	u8		rKey			:4;		///< Bit 0:   P10 Input Right or Button A (0=Pressed) (Read Only)
									///< Bit 1:   P11 Input Left  or Button B (0=Pressed) (Read Only)
									///< Bit 2:   P12 Input Up    or Select   (0=Pressed) (Read Only)
									///< Bit 3:   P13 Input Down  or Start    (0=Pressed) (Read Only)
	u8		rDirection		:1;		///< Bit 4:   P14 Select Direction Keys   (0=Select)
	u8		rButton			:1;		///< Bit 5:   P15 Select Button Keys      (0=Select)
	u8		rPadding		:2;		///< Bit 6-7: Unused
};

/**
 * @struct cgbSRegSC
 * @brief REG: FF02 - SC - Serial Transfer Control (R/W)
 */
struct cgbSRegSC
{
	u8		rClockShift		:1;		///< Bit 0:   Shift Clock (0=External Clock, 1=Internal Clock)
	u8		rClockSpeed		:1;		///< Bit 1:   Clock Speed (0=Normal, 1=Fast) ** CGB Mode Only **
	u8		rPadding		:5;		///< Bit 2-6: Unused
	u8		rTransfer		:1;		///< Bit 7:   Transfer Start Flag (0=No Transfer, 1=Start)
};

/**
 * @struct cgbSRegTAC
 * @brief REG: FF07 - TAC - Timer Control (R/W)
 */
struct cgbSRegTAC
{
	u8		rInputClock		:2;		///< Bit 0-1: Input Clock Select
	u8		rTimerStop		:1;		///< Bit 2:   Timer Stop  (0=Stop, 1=Start)
	u8		rPadding		:5;		///< Bit 3-7: Unused
};

/**
 * @struct cgbSRegINT
 * @brief REG: FF0F - IF - Interrupt Flag (R/W)
 * @brief REG: FFFF - IE - Interrupt Enable (R/W)
 */
struct cgbSRegINT
{
	u8		rVBlank			:1;		///< Bit 0:   V-Blank  Interrupt Request (INT 40h)  (1=Request)
	u8		rLCD			:1;		///< Bit 1:   LCD STAT Interrupt Request (INT 48h)  (1=Request)
	u8		rTimer			:1;		///< Bit 2:   Timer    Interrupt Request (INT 50h)  (1=Request)
	u8		rSerial			:1;		///< Bit 3:   Serial   Interrupt Request (INT 58h)  (1=Request)
	u8		rJoypad			:1;		///< Bit 4:   Joypad   Interrupt Request (INT 60h)  (1=Request)
	u8		rPadding		:3;		///< Bit 5-7: Unused
};

/**
 * @struct cgbSRegNR10
 * @brief REG: FF10 - NR10 - Channel 1 Sweep register (R/W)
 */
struct cgbSRegNR10
{
	u8		rShift			:3;		///< Bit 0-2: Number of sweep shift (n: 0-7)
	u8		rAS				:1;		///< Bit 3:   Sweep Increase/Decrease
	u8		rTime			:3;		///< Bit 4-6: Sweep Time
	u8		rPadding		:1;		///< Bit 7:   Unused
};

/**
 * @struct cgbSRegNRX1
 * @brief REG: FF11 - NR11 - Channel 1 Sound Length/Wave Pattern Duty (R/W)
 * @brief REG: FF16 - NR21 - Channel 2 Sound Length/Wave Pattern Duty (R/W)
 */
struct cgbSRegNRX1
{
	u8		rLength			:6;		///< Bit 0-5: Sound length data (Write Only) (t1: 0-63)
	u8		rDuty			:2;		///< Bit 6-7: Wave Pattern Duty (Read/Write)
};

/**
 * @struct cgbSRegNRX2
 * @brief REG: FF12 - NR12 - Channel 1 Volume Envelope (R/W)
 * @brief REG: FF17 - NR22 - Channel 2 Volume Envelope (R/W)
 * @brief REG: FF21 - NR42 - Channel 4 Volume Envelope (R/W)
 */
struct cgbSRegNRX2
{
	u8		rSteps			:3;		///< Bit 0-2: Number of envelope sweep (n: 0-7) (If zero, stop envelope operation.)
	u8		rDirection		:1;		///< Bit 3:   Envelope Direction (0=Decrease, 1=Increase)
	u8		rValue			:4;		///< Bit 4-7: Initial Volume of envelope (0-0Fh) (0=No Sound)
};

/**
 * @struct cgbSRegNRX34
 * @brief REG: FF13 - NR13 - Channel 1 Frequency's lower data (R/W)
 * @brief REG: FF14 - NR14 - Channel 1 Frequency's higher data (R/W)
 * @brief REG: FF18 - NR23 - Channel 2 Frequency's lower data (R/W)
 * @brief REG: FF19 - NR24 - Channel 2 Frequency's higher data (R/W)
 * @brief REG: FF1D - NR33 - Channel 3 Frequency's lower data (R/W)
 * @brief REG: FF1E - NR34 - Channel 3 Frequency's higher data (R/W)
 */
struct cgbSRegNRX34
{
	u16		rFreq			:11;	///< Bit 0-10:  Frequency's 11 bits (x) (Write Only)
	u16		rPadding		:3;		///< Bit 11-13: Unused
	u16		rCounter		:1;		///< Bit 14:    Counter/consecutive selection (Read/Write) (1=Stop output when length in NR11 expires)
	u16		rInitial		:1;		///< Bit 15:    Initial (1=Restart Sound)     (Write Only)
};

/**
 * @struct cgbSRegNR30
 * @brief REG: FF1A - NR30 - Channel 3 Sound on/off (R/W)
 */
struct cgbSRegNR30
{
	u8		rPadding		:7;		///< Bit 0-6: Unused
	u8		rOutput			:1;		///< Bit 7:   Sound Channel 3 Off  (0=Stop, 1=Playback)  (Read/Write)
};

/**
 * @struct cgbSRegNR32
 * @brief REG: FF1C - NR32 - Channel 3 Select output level (R/W)
 */
struct cgbSRegNR32
{
	u8		rPadding0		:5;		///< Bit 0-4: Unused
	u8		rLevel			:2;		///< Bit 5-6: Select output level (Read/Write)
	u8		rPadding1		:1;		///< Bit 7:   Unused
};

/**
 * @struct cgbSRegNR41
 * @brief REG: FF20 - NR41 - Channel 4 Sound Length (R/W)
 */
struct cgbSRegNR41
{
	u8		rLength			:6;		///< Bit 0-5: Sound length data (t1: 0-63)
	u8		rPadding		:2;		///< Bit 6-7: Unused
};

/**
 * @struct cgbSRegNR43
 * @brief REG: FF22 - NR43 - Channel 4 Polynomial Counter (W)
 */
struct cgbSRegNR43
{
	u8		rDividingRatio	:3;		///< Bit 0-2: Dividing Ratio of Frequencies (r)
	u8		rStepNumber		:1;		///< Bit 3:   Counter Step/Width (0=15 bits, 1=7 bits)
	u8		rShiftClock		:4;		///< Bit 4-7: Shift Clock Frequency (s)
};

/**
 * @struct cgbSRegNR44
 * @brief REG: FF23 - NR44 - Channel 4 Counter/consecutive, Inital (R/W)
 */
struct cgbSRegNR44
{
	u8		rPadding		:6;		///< Bit 0-5: Unused
	u8		rCounter		:1;		///< Bit 6:   Counter/consecutive selection (Read/Write) (1=Stop output when length in NR41 expires)
	u8		rInitial		:1;		///< Bit 7:   Initial (1=Restart Sound)     (Write Only)
};

/**
 * @struct cgbSRegNR50
 * @brief REG: FF24 - NR50 - Channel control / ON-OFF / Volume (R/W)
 */
struct cgbSRegNR50
{
	u8		rSO1Volume		:3;		///< Bit 0-2: SO1 output level (volume)  (0-7)
	u8		rSO1VinEnable	:1;		///< Bit 3:   Output Vin to SO1 terminal (1=Enable)
	u8		rSO2Volume		:3;		///< Bit 4-6: SO2 output level (volume)  (0-7)
	u8		rSO2VinEnable	:1;		///< Bit 7:   Output Vin to SO2 terminal (1=Enable)
};

/**
 * @struct cgbSRegNR51
 * @brief REG: FF25 - NR51 - Selection of Sound output terminal (R/W)
 */
struct cgbSRegNR51
{
	u8		rSoundSO1		:4;		///< Bit 0-3: Output sound to SO1 terminal
	u8		rSoundSO2		:4;		///< Bit 4-7: Output sound to SO2 terminal
};

/**
 * @struct cgbSRegNR52
 * @brief REG: FF26 - NR52 - Sound on/off (R/W)
 */
struct cgbSRegNR52
{
	u8		rSound1			:1;		///< Bit 0:   Sound 1 ON flag (Read Only)
	u8		rSound2			:1;		///< Bit 1:   Sound 2 ON flag (Read Only)
	u8		rSound3			:1;		///< Bit 2:   Sound 3 ON flag (Read Only)
	u8		rSound4			:1;		///< Bit 3:   Sound 4 ON flag (Read Only)
	u8		rPadding		:3;		///< Bit 4-6: Unused
	u8		rSoundAll		:1;		///< Bit 7:   All sound on/off  (0: stop all sound circuits) (Read/Write)
};

/**
 * @struct cgbSRegLCDC
 * @brief REG: FF40 - LCDC - LCD Control (R/W)
 */
struct cgbSRegLCDC
{
	u8		rBGEnable		:1;		///< Bit 0: BG Display			           (0=Off, 1=On)
	u8		rOBJEnable		:1;		///< Bit 1: OBJ (Sprite) Display Enable    (0=Off, 1=On)
	u8		rOBJSize		:1;		///< Bit 2: OBJ (Sprite) Size              (0=8x8, 1=8x16)
	u8		rBGSrnSel		:1;		///< Bit 3: BG Tile Map Display Select     (0=9800-9BFF, 1=9C00-9FFF)
	u8		rBGWinChrSel	:1;		///< Bit 4: BG & Window Tile Data Select   (0=8800-97FF, 1=8000-8FFF)
	u8		rWinEnable		:1;		///< Bit 5: Window Display Enable          (0=Off, 1=On)
	u8		rWinSrnSel		:1;		///< Bit 6: Window Tile Map Display Select (0=9800-9BFF, 1=9C00-9FFF)
	u8		rLCDEnable		:1;		///< Bit 7: LCD Display Enable             (0=Off, 1=On)
};

/**
 * @struct cgbSRegSTAT
 * @brief REG: FF41 - STAT - LCDC Status (R/W)
 */
struct cgbSRegSTAT
{
	u8		rMode			:2;		///< Bit 1-0: Mode Flag       (Mode 0-3) (Read Only)
									///< 	0: During H-Blank
									///< 	1: During V-Blank
									///< 	2: During Searching OAM-RAM
									///< 	3: During Transfering Data to LCD Driver
	u8		rCoincidence	:1;		///< Bit 2:   Coincidence Flag  (0:LYC<>LY, 1:LYC=LY) (Read Only)
	u8		rHBlankEnable	:1;		///< Bit 3:   Mode 0 H-Blank Interrupt     (1=Enable) (Read/Write)
	u8		rVBlankEnable	:1;		///< Bit 4:   Mode 1 V-Blank Interrupt     (1=Enable) (Read/Write)
	u8		rOAMEnable		:1;		///< Bit 5:   Mode 2 OAM Interrupt         (1=Enable) (Read/Write)
	u8		rLYCEnable		:1;		///< Bit 6:   LYC=LY Coincidence Interrupt (1=Enable) (Read/Write)
	u8		rPadding		:1;		///< Bit 7:   Unused
};

/**
 * @struct cgbSRegPAL
 * @brief REG: FF47 - BGP - BG Palette Data (R/W) - Non CGB Mode Only
 * @brief REG: FF48 - OBP0 - Object Palette 0 Data (R/W) - Non CGB Mode Only
 * @brief REG: FF49 - OBP1 - Object Palette 1 Data (R/W) - Non CGB Mode Only
 */
struct cgbSRegPAL
{
	u8		rColor0			:2;		///< Bit 0-1: Color 0
	u8		rColor1			:2;		///< Bit 2-3: Color 1
	u8		rColor2			:2;		///< Bit 4-5: Color 2
	u8		rColor3			:2;		///< Bit 6-7: Color 3
}; 


/**
 * @struct cgbSRegKEY1
 * @brief REG: FF4D - KEY1 - CGB Mode Only - Prepare Speed Switch (R/W)
 */
struct cgbSRegKEY1
{
	u8		rSpeed			:1;		///< Bit 0:   Prepare Speed Switch (0=No, 1=Prepare) (Read/Write)
	u8		rPadding		:6;		///< Bit 1-7: Unused
	u8		rCurSpeed		:1;		///< Bit 7:   Current Speed     (0=Normal, 1=Double) (Read Only)
}; 

/**
 * @struct cgbSRegVBK
 * @brief REG: FF4F - VBK - CGB Mode Only - VRAM Bank (R/W)
 */
struct cgbSRegVBK
{
	u8		rBank			:1;		///< Bit 0:   VRAM Bank (0-1)
	u8		rPadding		:7;		///< Bit 1-7: Unused
};

/**
 * @struct cgbSRegHDMA5
 * @brief REG: FF55 - HDMA5 - CGB Mode Only - New DMA Length/Mode/Start (W)
 */
struct cgbSRegHDMA5
{
	u8		rLength			:7;		///< Bit 0-6: Transfer Length
	u8		rMode			:1;		///< Bit 7:   (0=General Purpose DMA) (1=H-Blank DMA)
};

/**
 * @struct cgbSRegRP
 * @brief REG: FF56 - RP - CGB Mode Only - Infrared Communications Port (R/W)
 */
struct cgbSRegRP
{
	u8		rWrite			:1;		///< Bit 0:   Write Data   (0=LED Off, 1=LED On)             (Read/Write)
	u8		rRead			:1;		///< Bit 1:   Read Data    (0=Receiving IR Signal, 1=Normal) (Read Only)
	u8		rPadding		:4;		///< Bit 2-5: Unused
	u8		rReadEnable		:2;		///< Bit 6-7: Data Read Enable (0=Disable, 3=Enable)         (Read/Write)
};

/**
 * @struct cgbSRegCPS
 * @brief REG: FF68 - BCPS/BGPI - CGB Mode Only - Background Palette Index (R/W)
 * @brief REG: FF6A - OCPS/OBPI - CGB Mode Only - Sprite Palette Index (R/W)
 */
struct cgbSRegCPS
{
	u8		rHL				:1;		///< Bit 0:   H/L Select
	u8		rPalDataNo		:2;		///< Bit 1-2: Palette Data No.
	u8		rPalNo			:3;		///< Bit 3-5: Palette No.
	u8		rPadding		:1;		///< Bit 6:   Unused
	u8		rAutoInc		:1;		///< Bit 7:   Auto Increment  (0=Disabled, 1=Increment after Writing)
};

/**
 * @struct cgbSRegSVBK
 * @brief REG: FF70 - SVBK - CGB Mode Only - WRAM Bank (R/W)
 */
struct cgbSRegSVBK
{
	u8		rWRAMBank		:3;		///< Bit 0-2: Select WRAM Bank (Read/Write)
	u8		rPadding		:5;		///< Bit 3-7: Unused
};

/**
 * @struct cgbSGrpOAMInfo
 * @brief OAM Info
 */
struct cgbSGrpOAMInfo
{
	s32				nTop;					///< OAM Top Postion
	s32				nBottom;				///< OAM Bottom Postion
	s32				nSX;					///< OAM X Coordinate
	u32				nCharID;				///< Char ID OAM
	u32				nAttr;					///< Attribute OAM
	s32				nStart;					///< Start Coordinate
	s32				nEnd;					///< End Coordinate
	u16*			pPal;					///< Palette Pointer
	u32				nCharOffset;			///< Char ID Offset
	s32				nTileX;					///< Tile X Start Coordinate
	cgbSGrpOAMInfo*	pNext;					///< Next Node
};
