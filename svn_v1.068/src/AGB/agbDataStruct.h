/**
 * @file agbDataStruct.h
 * @author Chentian
 * @date 2009.11.23
 * @brief AGB Emulate For CTR - Data Struct
 */
#pragma once
#include "agbGlobal.h"

////// Register Struct //////

/**
 * @struct agbSRegDISPCNT
 * @brief REG: The DISPCNT Register (R/W)
 */
struct agbSRegDISPCNT
{
	u16		rBGMode			:3;		///< Bit 0-2:	BG Mode
	u16		rCGBMode		:1;		///< Bit 3:		CGB Mode
	u16		rFrameID		:1;		///< Bit 4:		Display Frame Selection
	u16		rOBJH			:1;		///< Bit 5:		H-Blank Interval OBJ Processing Flag
	u16		rOBJMap			:1;		///< Bit 6:		OBJ Character VRAM Mapping Format
	u16		rForcedBlank	:1;		///< Bit 7:		Forced Blank
	u16		rBG0			:1;		///< Bit 8:		Individual Screens Display Flag - BG0
	u16		rBG1			:1;		///< Bit 9:		Individual Screens Display Flag - BG1
	u16		rBG2			:1;		///< Bit 10:	Individual Screens Display Flag - BG2
	u16		rBG3			:1;		///< Bit 11:	Individual Screens Display Flag - BG3
	u16		rOBJ			:1;		///< Bit 12:	Individual Screens Display Flag - OBJ
	u16		rWIN0			:1;		///< Bit 13:	Display Flags for Windows 0
	u16		rWIN1			:1;		///< Bit 14:	Display Flags for Windows 1
	u16		rOBJWIN			:1;		///< Bit 15:	OBJ Window Display Flag
};

/**
 * @struct agbSRegDISPSTAT
 * @brief REG: The DISPSTAT Register (R/W)
 */
struct agbSRegDISPSTAT
{
	u8		rVBlank			:1;		///< Bit 0:		V-Blank Status
	u8		rHBlank			:1;		///< Bit 1:		H-Blank Status
	u8		rVCountEva		:1;		///< Bit 2:		V Counter Evaluation
	u8		rVBlankInt		:1;		///< Bit 3:		V-Blank Interrupt Request Enable Flag
	u8		rHBlankInt		:1;		///< Bit 4:		H-Blank Interrupt Request Enable Flag
	u8		rVCountMatch	:1;		///< Bit 5:		V Counter Match Interrupt Request Enable Flag
	u8		rPadding		:2;		///< Bit 6-7:	Unused
	u8		rVCount;				///< Bit 8-15:	V Count Setting
};

/**
 * @struct agbSRegVCOUNT
 * @brief REG: The VCOUNT Register (R)
 */
struct agbSRegVCOUNT
{
	u8		rVCountVal;				///< Bit 0-7:	V Counter Value
	u8		rPadding;				///< Bit 8-15:	Unused
};

/**
 * @struct agbSRegBGCNT
 * @brief REG: Background Screen Control Registers (R/W)
 */
struct agbSRegBGCNT
{
	u16		rPrio			:2;		///< Bit 0-1:	Priority Among BGs
	u16		rChrBaseBlock	:2;		///< Bit 2-3:	Character Base Block Specification
	u16		rPadding		:2;		///< Bit 4-5:	Unused
	u16		rMosaic			:1;		///< Bit 6:		Mosaic
	u16		rColorMode		:1;		///< Bit 7:		Color Mode
	u16		rSrnBaseBlock	:5;		///< Bit 8-12:	Screen Base Block Specification 
	u16		rAreaOverflow	:1;		///< Bit 13:	Area Overflow Processing
	u16		rSrnSize		:2;		///< Bit 14-15:	Screen Size
};

/**
 * @struct agbSRegBGOFS
 * @brief REG: Offset Settings Registers (W)
 */
struct agbSRegBGOFS
{
	u16		rOffset			:9;		///< Bit 0-8:	Offset
	u16		rPadding		:7;		///< Bit 9-15:	Unused
};

/**
 * @struct agbSRegBGSP
 * @brief REG: Registers for Setting the Starting Point of BG Data (W)
 */
struct agbSRegBGSP
{
	u32		rCoodinate		:28;	///< Bit 0-27:	Coodinate
	u32		rPadding		:4;		///< Bit 28-31:	Unused
};

/**
 * @struct agbSRegWINCOORD
 * @brief REG: Window Position Setting Registers (W)
 */
struct agbSRegWINCOORD
{
	u8		rRightLow;				///< Bit 0-7:	Left-upper coordinate of window
	u8		rLeftUp;				///< Bit 8-15:	Right-lower coordinate of window
};

/**
 * @struct agbSRegWINCNT
 * @brief REG: The WININ and WINOUT Registers (R/W)
 */
struct agbSRegWINCNT
{
	u16		r0BG			:4;		///< Bit 0-3:	BG0-3
	u16		r0OBJ			:1;		///< Bit 4:		OBJ
	u16		r0SE			:1;		///< Bit 5:		Special Effects
	u16		rPadding0		:2;		///< Bit 6-7:	Unused
	u16		r1BG			:4;		///< Bit 8-11:	BG0-3
	u16		r1OBJ			:1;		///< Bit 12:	OBJ
	u16		r1SE			:1;		///< Bit 13:	Special Effects
	u16		rPadding1		:2;		///< Bit 14-15:	Unused
};

/**
 * @struct agbSRegWINCNT8
 * @brief REG: The WININ and WINOUT Registers - 8 Bits (R/W)
 */
struct agbSRegWINCNT8
{
	u8		rBG				:4;		///< Bit 0-3:	BG0-3
	u8		rOBJ			:1;		///< Bit 4:		OBJ
	u8		rSE				:1;		///< Bit 5:		Special Effects
	u8		rPadding0		:2;		///< Bit 6-7:	Unused
};

/**
 * @struct agbSRegMOSAIC
 * @brief REG: The MOSAIC Register (W)
 */
struct agbSRegMOSAIC
{
	u16		rBGHSize		:4;		///< Bit 0-3:	BG Mosaic Horizontal Size 
	u16		rBGVSize		:4;		///< Bit 4-7:	BG Mosaic Vertical Size 
	u16		rOBJHSize		:4;		///< Bit 8-11:	OBJ Mosaic Horizontal Size 
	u16		rOBJVSize		:4;		///< Bit 12-15:	OBJ Mosaic Vertical Size 
};

/**
 * @struct agbSRegBLDCNT
 * @brief REG: The BLDCNT Register (R/W)
 */
struct agbSRegBLDCNT
{
	u16		r1BG			:4;		///< Bit 0-3:	1st Target Pixel - BG0-3
	u16		r1OBJ			:1;		///< Bit 4:		1st Target Pixel - OBJ
	u16		r1BD			:1;		///< Bit 5:		1st Target Pixel - BD
	u16		rColorSE		:2;		///< Bit 6-7:	Color Special Effects Setting
	u16		r2BG			:4;		///< Bit 8-11:	2nd Target Pixel - BG0-3
	u16		r2OBJ			:1;		///< Bit 12:	2nd Target Pixel - OBJ
	u16		r2BD			:1;		///< Bit 13:	2nd Target Pixel - BD
	u16		rPadding		:2;		///< Bit 14-15:	Unused
};

/**
 * @struct agbSRegBLDALPHA
 * @brief REG: The BLDALPHA Register (R/W)
 */
struct agbSRegBLDALPHA
{
	u16		rEVA			:5;		///< Bit 0-4:	Color Special Effect Coefficient EVA
	u16		rPadding0		:3;		///< Bit 5-7:	Unused
	u16		rEVB			:5;		///< Bit 8-12:	Color Special Effect Coefficient EVB
	u16		rPadding1		:3;		///< Bit 13-15:	Unused
};

/**
 * @struct agbSRegBLDY
 * @brief REG: The BLDY Register (W)
 */
struct agbSRegBLDY
{
	u16		rEVY			:5;		///< Bit 0-4:	Color Special Effect Coefficient EVY
	u16		rPadding		:11;	///< Bit 5-15:	Unused
};

/**
 * @struct agbSRegSOUND1CNTL
 * @brief REG: The NR10 Register (R/W)
 */
struct agbSRegSOUND1CNTL
{
	u16		rShift			:3;		///< Bit 0-2:   Number of Sweep Shifts
	u16		rAS				:1;		///< Bit 3:     Sweep Increase/Decrease
	u16		rTime			:3;		///< Bit 4-6:   Sweep Time
	u16		rPadding		:9;		///< Bit 7-15:  Unused
};

/**
 * @struct agbSRegSOUNDXCNT12
 * @brief REG: The NR11 & NR12 Register (R/W)
 * @brief REG: The NR21 & NR22 Register (R/W)
 * @brief REG: The NR41 & NR42 Register (R/W)
 */
struct agbSRegSOUNDXCNT12
{
	u16		rLength			:6;		///< Bit 0-5:   Sound Length
	u16		rDuty			:2;		///< Bit 6-7:   Waveform Duty Cycle
	u16		rSteps			:3;		///< Bit 8-10:  Number of Envelope Steps
	u16		rDirection		:1;		///< Bit 11:    Envelope Increase/Decrease 
	u16		rValue			:4;		///< Bit 12-15: Envelope Initial-Value
};

/**
 * @struct agbSRegSOUNDXCNT34
 * @brief REG: The NR13 & NR14 Register (R/W)
 * @brief REG: The NR23 & NR24 Register (R/W)
 * @brief REG: The NR33 & NR34 Register (R/W)
 */
struct agbSRegSOUNDXCNT34
{
	u16		rFreq			:11;	///< Bit 0-10:  Frequency Data
	u16		rPadding		:3;		///< Bit 11-13: Unused
	u16		rCounter		:1;		///< Bit 14:    Sound Length Flag
	u16		rInitial		:1;		///< Bit 15:    Initialization Flag
};

/**
 * @struct agbSRegSOUND3CNTL
 * @brief REG: The NR30 Register (R/W)
 */
struct agbSRegSOUND3CNTL
{
	u8		rPadding0		:5;		///< Bit 0-4:   Unused
	u8		rData			:1;		///< Bit 5:     Waveform RAM Data Association Specification
	u8		rBank			:1;		///< Bit 6:     Waveform RAM Bank Specification
	u8		rOutput			:1;		///< Bit 7:     Sound Output Flag
	u8		rPadding1;				///< Bit 8-15:  Unused
};

/**
 * @struct agbSRegSOUND3CNTH
 * @brief REG: The NR31 & NR32 Register (R/W)
 */
struct agbSRegSOUND3CNTH
{
	u8		rLength;				///< Bit 0-7:   Sound Length
	u8		rPadding		:5;		///< Bit 8-12:  Unused
	u8		rLevel			:2;		///< Bit 13-14: Output Level Selection
	u8		rForcedLevel	:1;		///< Bit 15:    Forced 3/4 Output Level Specification Flag
};

/**
 * @struct agbSRegSOUND4CNTH
 * @brief REG: The NR43 & NR44 Register (R/W)
 */
struct agbSRegSOUND4CNTH
{
	u16		rDividingRatio	:3;		///< Bit 0-2:   Dividing Ratio Frequency Selection
	u16		rStepNumber		:1;		///< Bit 3:     Polynomial Counter Step Number Selection
	u16		rShiftClock		:4;		///< Bit 4-7:   Polynomial Counter Shift Clock Frequency Selection
	u16		rPadding		:6;		///< Bit 8-13:  Unused
	u16		rCounter		:1;		///< Bit 14:    Sound Length Flag
	u16		rInitial		:1;		///< Bit 15:    Initialization Flag
};

/**
 * @struct agbSRegSOUNDCNTL
 * @brief REG: The NR50 & NR51 Register (R/W)
 */
struct agbSRegSOUNDCNTL
{
	u16		rRVolume		:3;		///< Bit 0-2:   R Output Level
	u16		rPadding0		:1;		///< Bit 3:     Unused
	u16		rLVolume		:3;		///< Bit 4-6:   L Output Level
	u16		rPadding1		:1;		///< Bit 7:     Unused
	u16		rSoundR			:4;		///< Bit 8-11:  Sound R Output Flag
	u16		rSoundL			:4;		///< Bit 12-15: Sound L Output Flag
};

/**
 * @struct agbSRegSOUNDCNTH
 * @brief REG: The SOUND Control H Register (R/W)
 */
struct agbSRegSOUNDCNTH
{
	u16		rSynthesis		:2;		///< Bit 0-1:   Output Ratio for Synthesis of Sounds 1-4
	u16		rRatioA			:1;		///< Bit 2:     Output Ratio for Direct Sound A
	u16		rRatioB			:1;		///< Bit 3:     Output Ratio for Direct Sound B
	u16		rPadding		:4;		///< Bit 4-7:   Unused
	u16		rROutputA		:1;		///< Bit 8:     R Output for Direct Sound A
	u16		rLOutputA		:1;		///< Bit 9:     L Output for Direct Sound A
	u16		rTimerA			:1;		///< Bit 10:    Timer Selection for Direct Sound A
	u16		rFIFOA			:1;		///< Bit 11:    FIFO Clear and Sequencer Reset for Direct Sound A
	u16		rROutputB		:1;		///< Bit 12:    R Output for Direct Sound B
	u16		rLOutputB		:1;		///< Bit 13:    L Output for Direct Sound B
	u16		rTimerB 		:1;		///< Bit 14:    Timer Selection for Direct Sound B
	u16		rFIFOB			:1;		///< Bit 15:    FIFO Clear and Sequencer Reset for Direct Sound B
};

/**
 * @struct agbSRegSOUNDCNTX
 * @brief REG: The NR52 Register (R/W)
 */
struct agbSRegSOUNDCNTX
{
	u8		rSound1			:1;		///< Bit 0:     Sound 1 Operation Flags
	u8		rSound2			:1;		///< Bit 1:     Sound 2 Operation Flags
	u8		rSound3			:1;		///< Bit 2:     Sound 3 Operation Flags
	u8		rSound4			:1;		///< Bit 3:     Sound 4 Operation Flags
	u8		rPadding0		:3;		///< Bit 4-6:   Unused
	u8		rSoundAll		:1;		///< Bit 7:     All Sounds Operation Flag
	u8		rPadding1;				///< Bit 8-15:  Unused
};

/**
 * @struct agbSRegSOUNDBIAS
 * @brief REG: The SOUNDBIAS Register (R/W)
 */
struct agbSRegSOUNDBIAS
{
	u16		rBiasLevel		:10;	///< Bit 0-9:	Bias Level
	u16		rPadding		:4;		///< Bit 10-13:	Unused
	u16		rARSC			:2;		///< Bit 14-15:	Amplitude Resolution/Sampling Cycle
};

/**
 * @struct agbSRegWAVERAM
 * @brief REG: Waveform RAM Registers (R/W)
 */
struct agbSRegWAVERAM
{
	u8		rStep01;				///< Bit 0-7:	Step 0 & 1
	u8		rStep23;				///< Bit 8-15:	Step 2 & 3
};

/**
 * @struct agbSRegFIFO
 * @brief REG: Sound FIFO Input Registers (R/W)
 */
struct agbSRegFIFO
{
	s8		rSoundData0;			///< Bit 0-7:	Sound Data 0
	s8		rSoundData1;			///< Bit 8-15:	Sound Data 1
	s8		rSoundData2;			///< Bit 16-23:	Sound Data 2
	s8		rSoundData3;			///< Bit 24-31:	Sound Data 3
};

/**
 * @struct agbSRegDMAAddr27
 * @brief REG: 27 bits DMA Address Registers (W)
 */
struct agbSRegDMAAddr27
{
	u32		rAddress		:27;	///< Bit 0-26:	Address
	u32		rPadding		:5;		///< Bit 27-31: Unused
};

/**
 * @struct agbSRegDMAAddr28
 * @brief REG: 28 bits DMA Address Registers (W)
 */
struct agbSRegDMAAddr28
{
	u32		rAddress		:28;	///< Bit 0-27:	Address
	u32		rPadding		:4;		///< Bit 28-31: Unused
};

/**
 * @struct agbSRegDMACNTL
 * @brief REG: The DMACNT_L Register (W)
 */
struct agbSRegDMACNTL
{
	u16		rCount			:14;	///< Bit 0-13:  Word Count
	u16		rPadding		:2;		///< Bit 14-15: Unused
};

/**
 * @struct agbSRegDMACNTH
 * @brief REG: The DMACNT_H Register (R/W)
 */
struct agbSRegDMACNTH
{
	u16		rPadding		:5;		///< Bit 0-4:	Unused
	u16		rDestAddr		:2;		///< Bit 5-6:	Destination Address Control Flag
	u16		rSrcAddr		:2;		///< Bit 7-8:	Source Address Control Flag
	u16		rRepeat			:1;		///< Bit 9:		DMA Repeat
	u16		rTransfer		:1;		///< Bit 10:	DMA Transfer Type
	u16		rDREQ			:1;		///< Bit 11:	Game Pak Data Request Transfer Flag(DMA3 Only)
	u16		rStartup		:2;		///< Bit 12-13:	DMA Startup Timing
	u16		rInterrupt		:1;		///< Bit 14:	Interrupt Request Enable Flag
	u16		rEnable			:1;		///< Bit 15:	DMA Enable Flag 
};

/**
 * @struct agbSRegTMCNT
 * @brief REG: Timer Control Registers (R/W)
 */
struct agbSRegTMCNT
{
	u8		rPrescalar		:2;		///< Bit 0-1:	Prescalar Selection
	u8		rCount			:1;		///< Bit 2:		Count-Up Timing
	u8		rPadding0		:3;		///< Bit 3-5:	Unused
	u8		rInterrupt		:1;		///< Bit 6:		Interrupt Request Enable Flag
	u8		rEnable			:1;		///< Bit 7:		Timer Operation Flag
	u8		rPadding1;				///< Bit 8-15:	Unused
};

/*
SIODATA32_L (32bit/Normal SIO), SIOMULTI0 (Multi Play)
SIODATA32_H (32bit/Normal SIO), SIOMULTI1 (Multi Play)
SIOMULTI2
SIOMULTI3
SCCNT (Normal SIO Communication), (Multi-Play Communication), (UART Communication)
SIOMLT_SEND (Multi Play)
SIODATA8 (Normal SIO)
*/

/**
 * @struct agbSRegKEYINPUT
 * @brief REG: The KEYINPUT Register (R/W)
 */
struct agbSRegKEYINPUT
{
	u16		rButtons		:10;	///< Bit 0-9:	Buttons
	u16		rPadding		:6;		///< Bit 10-15:	Unused
};

/**
 * @struct agbSRegKEYCNT
 * @brief REG: The KEYCNT Register (R/W)
 */
struct agbSRegKEYCNT
{
	u16		rButtons		:10;	///< Bit 0-9:	Buttons
	u16		rPadding		:4;		///< Bit 10-13:	Unused
	u16		rIntEnable		:1;		///< Bit 14:	Interrupt Request Enable Flag
	u16		rIntConditions	:1;		///< Bit 15:	Interrupt Conditions Specification Flag
};

/**
 * @struct agbSRegRCNT
 * @brief REG: The RCNT Register (General-Purpose Communication) (R/W)
 */
struct agbSRegRCNT
{
	u16		rDBSC			:1;		///< Bit 0:		Data Bit - SC
	u16		rDBSD			:1;		///< Bit 1:		Data Bit - SD
	u16		rDBSI			:1;		///< Bit 2:		Data Bit - SI
	u16		rDBSO			:1;		///< Bit 3:		Data Bit - SO
	u16		rIOSC			:1;		///< Bit 4:		Input/Output Selection Flag - SC
	u16		rIOSD			:1;		///< Bit 5:		Input/Output Selection Flag - SD
	u16		rIOSI			:1;		///< Bit 6:		Input/Output Selection Flag - SI
	u16		rIOSO			:1;		///< Bit 7:		Input/Output Selection Flag - SO
	u16		rInterrupt		:1;		///< Bit 8:		Interrupt Request Enable Flag
	u16		rPadding		:5;		///< Bit 9-13:	Unused
	u16		rCommunication	:2;		///< Bit 14-15:	Communication Function Set Flag
};

/*
JOY_CNT
JOYRECV_L
JOYRECV_H
JOYTRANS_L
JOYTRANS_H
JOYSTAT
*/

/**
 * @struct agbSRegINT
 * @brief REG: Interrupt Enable Register (R/W)
 * @brief REG: Interrupt Request Register (R/W)
 */
struct agbSRegINT
{
	u16		rVBlank			:1;		///< Bit 0:		V Blank
	u16		rHBlank			:1;		///< Bit 1:		H Blank
	u16		rVCounter		:1;		///< Bit 2:		V Counter Match
	u16		rTMR			:4;		///< Bit 3-6:	Timer 0-4
	u16		rSIO			:1;		///< Bit 7:		SIO
	u16		rDMA			:4;		///< Bit 8-11:	DMA 0-4
	u16		rKey			:1;		///< Bit 12:	Key
	u16		rGamePak		:1;		///< Bit 13:	Game Pak
	u16		rPadding		:2;		///< Bit 14-15:	Unused
};

/**
 * @struct agbSRegWAITCNT
 * @brief REG: Wait Control Register (R/W)
 */
struct agbSRegWAITCNT
{
	u16		rGPRWaitCnt		:2;		///< Bit 0-1:	Game Pak RAM Wait Control
	u16		rWaitState0		:3;		///< Bit 2-4:	Wait State 0 Wait Control
	u16		rWaitState1		:3;		///< Bit 5-7:	Wait State 1 Wait Control
	u16		rWaitState2		:3;		///< Bit 8-10:	Wait State 2 Wait Control
	u16		rPHICnt			:2;		///< Bit 10-12:	PHI Terminal Output Control
	u16		rPadding		:1;		///< Bit 13:	Unused
	u16		rPrefetch		:1;		///< Bit 14:	Prefetch
	u16		rGPType			:1;		///< Bit 15:	Game Pak Type
};

/**
 * @struct agbSRegIME
 * @brief REG: Interrupt Master Enable Register (R/W)
 */
struct agbSRegIME
{
	u16		rEnable			:1;		///< Bit 0:		Interrupt Master Enable Flag
	u16		rPadding		:15;	///< Bit 1-15:	Unused
};

/**
 * @struct agbSRegHALTCNT
 * @brief REG: Halt Control Register (R/W)
 */
struct agbSRegHALTCNT
{
	u16		rFirstBoot		:1;		///< Bit 0:		First Boot
	u16		rPadding		:13;	///< Bit 1-13:	Unused
	u16		rHalt			:1;		///< Bit 14:	Halt - *Nonexistent
	u16		rPowerDown		:1;		///< Bit 15:	Power Down
};

////// Graphic Struct //////

/**
 * @struct agbSGrpSrnData
 * @brief Text BG Screen Data
 */
struct agbSGrpSrnData
{
	u16		rChar			:10;	///< Bit 0-9:	Character Name
	u16		rHFlip			:1;		///< Bit 10:	Horizontal Flip Flag
	u16		rVFlip			:1;		///< Bit 11:	Vertical Flip Flag
	u16		rPal			:4;		///< Bit 12-15:	Color Palette
};

/**
 * @struct agbSGrpOamAttr0
 * @brief OAM Attribute 0 Data
 */
struct agbSGrpOamAttr0
{
	u16		rY				:8;		///< Bit 0-7:	Y Coordinate
	u16		rRot			:1;		///< Bit 8:		Rotation/Scaling
	u16		rDouble			:1;		///< Bit 9:		Double Size Flag
	u16		rMode			:2;		///< Bit 10-11:	OBJ Mode
	u16		rMosaic			:1;		///< Bit 12:	Mosaic
	u16		rColor			:1;		///< Bit 13:	Color Mode
	u16		rShape			:2;		///< Bit 14-15:	OBJ Shape
};

/**
 * @struct agbSGrpOamAttr1
 * @brief OAM Attribute 1 Data
 */
struct agbSGrpOamAttr1
{
	u16		rX				:9;		///< Bit 0-8:	X Coordinate
	u16		rPadding		:3;		///< Bit 9-10:	Unused
	u16		rHFlip			:1;		///< Bit 12:	Hflip
	u16		rVFlip			:1;		///< Bit 13:	Vflip
	u16		rSize			:2;		///< Bit 14-15:	OBJ Size
};

/**
 * @struct agbSGrpOamAttr1Rot
 * @brief OAM Attribute 1 Data - Rotation/Scaling
 */
struct agbSGrpOamAttr1Rot
{
	u16		rX				:9;		///< Bit 0-8:	X Coordinate
	u16		rRotPara		:5;		///< Bit 9-13:	Rotation/Scaling Parameter Selection
	u16		rSize			:2;		///< Bit 14-15:	OBJ Size
};

/**
 * @struct agbSGrpOamAttr2
 * @brief OAM Attribute 2 Data
 */
struct agbSGrpOamAttr2
{
	u16		rChar			:10;	///< Bit 0-9:	Character Name
	u16		rPrio			:2;		///< Bit 10-11:	Designate Priority
	u16		rPal			:4;		///< Bit 12-15:	Palette No.
};

/**
 * @struct agbSGrpOBJLineInfo
 * @brief OBJ Line Info
 */
struct agbSGrpOBJLineInfo
{
	u8		nPrio;					///< Designate Priority
	u8		nMode;					///< OBJ Mode
};

/**
 * @struct agbSGrpBGLayerInfo
 * @brief BG Layer Info
 */
struct agbSGrpBGLayerInfo
{
	u8		nLayer;					///< Layer
	u8		nPrio;					///< Designate Priority
	u8		nWin;					///< Window In Flag
	u8		nEffect;				///< Effect Target Flag
	u16*	pLineBuf;				///< Line Buffer
	agbSGrpBGLayerInfo*	pNext;		///< Next Layer Pointer
};

/**
 * @struct agbSGrpBGRSData
 * @brief Background Rotation and Scaling Parameter
 */
struct agbSGrpBGRSData
{
	s32		nPA;					///< BG Direction Parameter: A (DX)
	s32		nPB;					///< BG Direction Parameter: B (DMX)
	s32		nPC;					///< BG Direction Parameter: C (DY)
	s32		nPD;					///< BG Direction Parameter: D (DMY)
	s32		nX;						///< BG Starting Point: X
	s32		nY;						///< BG Starting Point: Y
	s32		nCX;					///< Current X
	s32		nCY;					///< Current Y
};

/**
 * @struct agbSGrpOAMData
 * @brief OAM Data
 */
struct agbSGrpOAMData
{
	s32		nSizeX;
	s32		nSizeY;
	s32		nFieldX;
	s32		nFieldY;
	s32		nSX;
	s32		nSY;
	s32		nX;
	s32		nY;
	s32		bMosaic;
	s32		bRot;
	s32		nPrio;
	s32		nMode;
	s32		nPal;
	s32		nColor;
	s32		nDX;
	s32		nDMX;
	s32		nDY;
	s32		nDMY;
	s32		nRX;
	s32		nRY;
	s32		nCharBase;
	s32		bHFlip;
	s32		bVFlip;
	s32		nLeft;
	s32		nRight;
	s32		nTop;
	s32		nBottom;
	u8*		pTileBase;
	u8*		pTile;
};
