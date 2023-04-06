/**
 * @file cgbSound.cpp
 * @author Chentian
 * @date 2009.12.23
 * @brief CGB Emulate For CTR - Sound
 */
#include "cgbRegister.h"
#include "cgbSound.h"
#include "cgbSoundReplace.h"
#include "cgbRegister.h"

/** @name Macro Define */
//@{

#define		CGB_SND_COUNT				(8)				///< Sound Count
//CGB one frame the CPU ticks is 17556
//our emu is play sound at 44100 hz,so one frame is 737 sample (44100/60 = 735, but it isn't 60frame/second, is about 59.7...frame/second
//so the sample /frame is bigger than 735
//but real test, the result is 737.1 sample/frame at CTR hardware at 44100 hz
//so our emu should make 737sample(some time 738 sample) per frame
//per tiger make 8sample, so must tiger 737(738)/8 = 92.xx, so one frame sound must be tiger at least 93 times
//this CGB_SND_TICKS 's usage is only to make sure that, 17556/93 = 188.7742 ,take 188
//CGB hz = 4194304
#define		CGB_SND_TICKS				(188)													


#define		CGB_SND_HI					1
#if (TRL_SOUND_WAVE_TEST== 1)
#define		CGB_SND_LO					-1
#else
#define		CGB_SND_LO					(-1)
#endif
//@}

/** @TRL_SOUND_CGB_FAST */
//@{
#if TRL_SOUND_CGB_FAST
u16 g_pCGBSndRegWriteLog_Addr[TRL_SOUND_REG_LOG_MAX];
u16 g_pCGBSndRegWriteLog_Value[TRL_SOUND_REG_LOG_MAX];
u32 g_pCGBSndRegWriteLog_Ticks[TRL_SOUND_REG_LOG_MAX];
u8  g_pCGBSndRegWriteLog_Type[TRL_SOUND_REG_LOG_MAX];
u32 g_pCGBSndRegWriteLog_Ct = 0;
u32 g_pCGBSndRegWriteLog_Run = 0;
u32 g_nCGBSndRegWriteLog_Ticks;
u8  g_pCGBSndRegFrameBeginValue[0x26-0x10 + 1];

static u32 nCGBRegWriteLog_ticks = 0;
static u32 nCGBRegWriteLog_tickspersample = 0;
static u32 nCGBRegWriteLog_ct = 0;


//call this at frame begin
void cgbSndRegWriteLog_LogBegin()
{
	g_pCGBSndRegWriteLog_Ct = 0;
	g_pCGBSndRegWriteLog_Run = 0;
	g_nCGBSndRegWriteLog_Ticks = 0;

	for(int i=0x10;i<0x26;i++)
	{
		g_pCGBSndRegFrameBeginValue[i-0x10] = g_pCgbREG[i];
	}
}


//ticks add 
void cgbSndRegWriteLog_LogTicksAdd(u32 n)
{
	g_nCGBSndRegWriteLog_Ticks += n;
}


void cgbSndRegWriteLog_LogRun()
{	
	g_pCGBSndRegWriteLog_Run = 1;

	for(int i=0x10;i<0x26;i++)
	{
		g_pCgbREG[i] = g_pCGBSndRegFrameBeginValue[i-0x10];
	}

	nCGBRegWriteLog_ticks = 0;
	nCGBRegWriteLog_ct = 0;
	if(g_pCgbEmuBuf->nAudioSampleCurFrame != 0)
	{		
		nCGBRegWriteLog_tickspersample = g_nCGBSndRegWriteLog_Ticks/g_pCgbEmuBuf->nAudioSampleCurFrame + 1;
	}
	else
	{
		for(u32 i=0;i<g_pCGBSndRegWriteLog_Ct;i++)
		{
			cgbRegWrite((u8)g_pCGBSndRegWriteLog_Addr[i], (u8)g_pCGBSndRegWriteLog_Value[i]);
		}
	}
}

void cgbSndRegWriteLog_LogRunOneSample()
{
	if(nCGBRegWriteLog_ct >= g_pCGBSndRegWriteLog_Ct)
		return;
	nCGBRegWriteLog_ticks += nCGBRegWriteLog_tickspersample;
	while(nCGBRegWriteLog_ticks >= g_pCGBSndRegWriteLog_Ticks[nCGBRegWriteLog_ct])
	{
		cgbRegWrite((u8)g_pCGBSndRegWriteLog_Addr[nCGBRegWriteLog_ct], (u8)g_pCGBSndRegWriteLog_Value[nCGBRegWriteLog_ct]);
		nCGBRegWriteLog_ct++;
		if(nCGBRegWriteLog_ct >= g_pCGBSndRegWriteLog_Ct)
			return;
	}
}
#endif
//@}

/** @name Global Variable */
//@{
s8			g_nCgbSndWavePattern[4][8] = {				///< Sound Wave Pattern Data
				CGB_SND_HI, CGB_SND_LO, CGB_SND_LO, CGB_SND_LO, CGB_SND_LO, CGB_SND_LO, CGB_SND_LO, CGB_SND_LO, 
				CGB_SND_HI, CGB_SND_HI, CGB_SND_LO, CGB_SND_LO, CGB_SND_LO, CGB_SND_LO, CGB_SND_LO, CGB_SND_LO,
				CGB_SND_HI, CGB_SND_HI, CGB_SND_HI, CGB_SND_HI, CGB_SND_LO, CGB_SND_LO, CGB_SND_LO, CGB_SND_LO,
				CGB_SND_HI, CGB_SND_HI, CGB_SND_HI, CGB_SND_HI, CGB_SND_HI, CGB_SND_HI, CGB_SND_LO, CGB_SND_LO };


#if (TRL_SOUND_WAVE_TEST== 1)
s8 g_nCgbSndWavePattern2[4][8*CGB_SND_STEP];
s8 g_nCgbSndWavePattern3[4][8*CGB_SND_STEP];
void cgbSndInitWavePattern2()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<8*CGB_SND_STEP;j++)
		{
			g_nCgbSndWavePattern3[i][j] = g_nCgbSndWavePattern[i][j/CGB_SND_STEP];			
		}
	}
	s8 snd_window = 12;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<8*CGB_SND_STEP;j++)
		{
			g_nCgbSndWavePattern2[i][j] = 0;
			for(int k=0;k<snd_window;k++)
				g_nCgbSndWavePattern2[i][j] += g_nCgbSndWavePattern3[i][(j+k)%(8*CGB_SND_STEP)];
			g_nCgbSndWavePattern2[i][j] = g_nCgbSndWavePattern2[i][j]*CGB_SND_VOLUMESCALE/snd_window;
		}
	}
}
#endif

const s32	g_nCgbSndFreqRatio[8] = 					///< Sound Frequency Ratio (4.194304 MHz / 8 / (0.5~7))
				{ 1048576, 524288, 262144, 174763, 131072, 104858, 87381, 74898 };
const s32	g_nCgbSndShiftClock[16]= 					///< Sound Shift Clock Frequency's Formula
				{ 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 1, 1 };

s16*		g_pCgbSndBuf = 0;							///< Sound Data Buffer Header
s32			g_nCgbSndBufSize = 0;						///< Sound Data Buffer Size
s32			g_nCgbSndBufPos = 0;						///< Sound Data Buffer Size
s32			g_nCgbSndBufDiff = 0;						///< Sound Data Buffer Difference
s32			g_nCgbSndBufAdd = CGB_SND_COUNT;			///< Sound Data Buffer Add Value
s32			g_nCgbSndBufOutput1 = 0;					///< Sound Data Output 1
s32			g_nCgbSndBufOutput2 = 0;					///< Sound Data Output 2
s32			g_nCgbSndBufSwap = 0;						///< Sound Data Swap L/R Flag

s32			g_nCgbSndTicks = 0;							///< Sound Ticks
s32			g_nCgbSndTick0 = CGB_SND_TICKS;				///< Sound Interval Ticks
s32			g_nCgbSndVolume1 = 0;						///< Sound SO1 Volume
s32			g_nCgbSndVolume2 = 0;						///< Sound SO2 Volume

s32			g_nCgbSnd1Index = 0;						///< Sound 1 Data Index
s32			g_nCgbSnd1Length = 0;						///< Sound 1 Length
u32			g_nCgbSnd1Frequency = 0;					///< Sound 1 Output Frequency
s32			g_nCgbSnd1EnvelopeValue = 0;				///< Sound 1 Envelope Value
s32			g_nCgbSnd1EnvelopeLength = 0;				///< Sound 1 Envelope Length
s32			g_nCgbSnd1EnvelopeLengthInit = 0;			///< Sound 1 Envelope Length Init Value
s32			g_nCgbSnd1SweepLimit = 2047;				///< Sound 1 Sweep Limit
s32			g_nCgbSnd1SweepLength = 0;					///< Sound 1 Sweep Length
s32			g_nCgbSnd1SweepLengthInit = 0;				///< Sound 1 Sweep Length Init Value
s8*			g_pCgbSnd1Wave = g_nCgbSndWavePattern[2];	///< Sound 1 Wave
u32			g_nCgbSnd1SweepFreq = 0;					///< Sound 1 Sweep Freq
u32			g_bCgbSnd1SweepMode = 0;					///< Sound 1 Sweep Mode

s32			g_nCgbSnd2Index = 0;						///< Sound 2 Data Index
s32			g_nCgbSnd2Length = 0;						///< Sound 2 Length
u32			g_nCgbSnd2Frequency = 0;					///< Sound 2 Output Frequency
s32			g_nCgbSnd2EnvelopeValue = 0;				///< Sound 2 Envelope Value
s32			g_nCgbSnd2EnvelopeLength = 0;				///< Sound 2 Envelope Length
s32			g_nCgbSnd2EnvelopeLengthInit = 0;			///< Sound 2 Envelope Length Init Value
s8*			g_pCgbSnd2Wave = g_nCgbSndWavePattern[2];	///< Sound 2 Wave

s32			g_nCgbSnd3Index = 0;						///< Sound 3 Data Index
s32			g_nCgbSnd3Length = 0;						///< Sound 3 Length
u32			g_nCgbSnd3Frequency = 0;					///< Sound 3 Output Frequency

s32			g_nCgbSnd4Index = 0;						///< Sound 4 Data Index
s32			g_nCgbSnd4Length = 0;						///< Sound 4 Length
u32			g_nCgbSnd4Frequency = 0;					///< Sound 4 Output Frequency
s32			g_nCgbSnd4EnvelopeValue = 0;				///< Sound 4 Envelope Value
s32			g_nCgbSnd4EnvelopeLength = 0;				///< Sound 4 Envelope Length
s32			g_nCgbSnd4EnvelopeLengthInit = 0;			///< Sound 4 Envelope Length Init Value
s32			g_nCgbSnd4Shift = 0xFFFFFFFF;				///< Sound 4 Shift
u32			g_bCgbSnd4NoiseTable = 0;					///< Sound 4 Noise Mode

s32			g_nCgbSnd4TableIndex = 0;

s32			g_nCgbSnd1Reset = 0;
s32			g_nCgbSnd2Reset = 0;


u32			g_nCgbSndMultiSample = 1;

const u8 cgbSndNoiseStep7Length = 127;
s8 cgbSndNoiseStep7Table[cgbSndNoiseStep7Length];
const u32 cgbSndNoiseStep7ShiftMask = 0xFF;
s32 cgbSndNoiseStep7ShiftIndex[0x100];

const u32 cgbSndNoiseStep15Length = 32767;
s8 cgbSndNoiseStep15Table[cgbSndNoiseStep15Length];
const u32 cgbSndNoiseStep15ShiftMask = 0xFFFF;
s32 cgbSndNoiseStep15ShiftIndex[0x10000];


s16 cgbSndNoiseStep7Table_6[] = 
{
	455,  529,  605,  690,  793,  918, 1058, 1193, 1295, 1336, 1284, 1118,  834,  446,  -11, -489, 
-929, -1276, -1488, -1543, -1443, -1225, -934, -635, -385, -234, -204, -289, -458, -663, -844, -949, 
-938, -802, -555, -239,   88,  364,  539,  580,  481,  267,  -14, -304, -544, -685, -703, -596, 
-393, -137,  118,  325,  446,  470,  407,  285,  145,   32,  -22,    3,  103,  258,  431,  582, 
 674,  685,  606,  451,  247,   28, -169, -318, -400, -421, -395, -341, -289, -260, -263, -297, 
-351, -403, -432, -420, -355, -242,  -92,   74,  232,  363,  454,  504,  522,  523,  522,  537, 
 569,  617,  668,  700,  694,  633,  511,  334,  124,  -92, -278, -405, -450, -404, -275,  -84, 
 140,  361,  552,  686,  757,  767,  726,  651,  560,  464,  367,  271,  172,   63,  -53
};
s16 cgbSndNoiseStep7Table_5[] = 
{
	498,  598,  696,  804,  934, 1088, 1251, 1388, 1456, 1408, 1215,  873,  407, -126, -651, -1090, 
-1385, -1504, -1454, -1271, -1017, -760, -554, -433, -401, -442, -526, -615, -682, -712, -700, -652, 
-569, -457, -317, -146,   42,  232,  389,  476,  456,  315,   62, -260, -578, -816, -901, -795, 
-511, -103,  330,  684,  868,  841,  614,  261, -108, -378, -460, -317,   14,  445,  854, 1120, 
1163,  965,  573,   92, -356, -663, -763, -657, -406, -111,  118,  203,  109, -133, -447, -729, 
-890, -872, -675, -347,   23,  342,  538,  581,  489,  322,  161,   81,  122,  287,  531,  790, 
 988, 1066, 1002,  809,  535,  238,  -20, -199, -286, -292, -246, -177, -110,  -52,    5,   79, 
 182,  319,  478,  635,  758,  821,  809,  721,  578,  407,  236,   86,  -35, -128, -201
};

s16 cgbSndNoiseStep7Table_3[] = 
{
	585,  818, 1037, 1198, 1268, 1291, 1361, 1522, 1644, 1455,  739, -410, -1539, -2085, -1786, -934, 
-209, -176, -841, -1627, -1825, -1186, -142,  530,  338, -524, -1341, -1465, -848,  -53,  244, -171, 
-870, -1157, -655,  391, 1309, 1526,  958,   11, -782, -1115, -1031, -740, -419, -127,  114,  246, 
 213,   70,   -2,  167,  550,  879,  841,  347, -346, -802, -712, -116,  656, 1250, 1489, 1391, 
1024,  419, -375, -1150, -1546, -1270, -388,  608, 1089,  741, -179, -1026, -1267, -876, -307,  -72, 
-291, -625, -603,  -81,  627, 1015,  831,  287, -145, -141,  224,  597,  701,  585,  537,  771, 
1173, 1375, 1075,  321, -484, -884, -713, -187,  281,  393,  155, -190, -378, -290,   10,  370, 
 664,  834,  881,  835,  741,  640,  545,  430,  261,   43, -155, -246, -202,  -96,  -49
};

s16 cgbSndNoiseStep7Table_4[] = 
{
	 151,  112,  220,  517,  958, 1421, 1762, 1867, 1692, 1277,  722,  135, -395, -818, -1118, -1295, 
-1354, -1297, -1142, -933, -731, -598, -559, -597, -654, -662, -590, -466, -362, -361, -491, -699, 
-859, -828, -529,   -5,  578,  995, 1062,  733,  125, -531, -985, -1086, -845, -422,  -27,  179, 
 168,   45,  -23,   83,  358,  667,  817,  672,  243, -295, -675, -672, -224,  525, 1275, 1699, 
1598,  990,  103, -725, -1199, -1189, -774, -184,  304,  499,  358,  -14, -440, -755, -877, -817, 
-644, -433, -232,  -42,  150,  338,  491,  558,  506,  351,  167,   57,  104,  333,  681, 1024, 
1225, 1202,  952,  550,  126, -200, -364, -365, -260, -124,  -22,   16,    3,  -24,  -20,   46, 
 190,  398,  632,  843,  972,  974,  837,  587,  288,   25, -134, -166,  -99,  -10,   22
};

s16 cgbSndNoiseStep7Table_9[] = 
{
	541,  661,  780,  893,  993, 1073, 1130, 1159, 1155, 1118, 1047,  942,  806,  644,  463,  268, 
  67, -133, -322, -499, -653, -783, -885, -957, -1000, -1014, -1002, -968, -914, -845, -764, -675, 
-582, -489, -398, -312, -233, -163, -103,  -56,  -23,   -2,    5,    0,  -18,  -43,  -76, -111, 
-145, -175, -195, -204, -197, -173, -132,  -75,   -2,   80,  168,  255,  337,  408,  462,  496, 
 508,  496,  464,  411,  342,  262,  176,   89,    5,  -72, -138, -194, -238, -273, -298, -316, 
-331, -341, -349, -354, -352, -344, -325, -290, -240, -169,  -78,   31,  156,  290,  428,  559, 
 676,  766,  825,  846,  825,  762,  660,  528,  373,  211,   54,  -86, -196, -266, -290, -265, 
-195,  -84,   55,  212,  370,  514,  631,  710,  742,  726,  663,  558,  423,  272,  119
};
s16 cgbSndNoiseStep7Table_12[] = 
{
	396,  466,  537,  607,  673,  734,  789,  833,  864,  882,  882,  865,  830,  774,  700,  607, 
 497,  372,  235,   91,  -61, -212, -361, -502, -631, -744, -839, -912, -961, -986, -986, -963, 
-916, -852, -770, -675, -573, -467, -364, -264, -175,  -96,  -33,   13,   42,   53,   49,   31, 
   2,  -35,  -75, -114, -150, -177, -193, -196, -184, -156, -112,  -55,   15,   92,  175,  257, 
 336,  406,  465,  506,  529,  529,  509,  468,  404,  323,  227,  119,    5, -109, -219, -320, 
-408, -478, -525, -549, -550, -526, -479, -411, -326, -226, -118,   -5,  107,  215,  311,  396, 
 465,  516,  548,  561,  558,  537,  505,  461,  413,  360,  307,  257,  214,  178,  152,  135, 
 129,  131,  141,  159,  179,  203,  225,  246,  262,  274,  281,  282,  279,  272,  261
};

trlSEmuShellResume	g_sCgbSndSaveData[CGB_SND_SAVEDATA];///< Sound Save Data
//@}

#if TRL_SOUND_DEBUG
extern s32			g_bCgbSndOnOffCH1;
extern s32			g_bCgbSndOnOffCH2;
extern s32			g_bCgbSndOnOffCH3;
extern s32			g_bCgbSndOnOffCH4;
#endif

/** @brief Initialize Sound */
void cgbSndInit()
{
#if (TRL_SOUND_WAVE_TEST== 1)
	cgbSndInitWavePattern2();
#endif
	g_bCgbSnd1SweepMode = g_pCgbEmuBuf->funcConfigData("CGB", "SoundCH1Sweep", 0);
	g_bCgbSnd4NoiseTable = g_pCgbEmuBuf->funcConfigData("CGB", "SoundNoiseTable", 0);
	g_nCgbSndMultiSample = g_pCgbEmuBuf->funcConfigData("CGB", "SoundMultiSample", 1);
	g_nCgbSnd1Reset = g_pCgbEmuBuf->funcConfigData("CGB", "SoundCH1Reset", 0);
	g_nCgbSnd2Reset = g_pCgbEmuBuf->funcConfigData("CGB", "SoundCH2Reset", 0);
	g_nCgbSnd1SweepLimit = g_pCgbEmuBuf->funcConfigData("CGB", "SoundCH1SweepLimit", 2047);

	g_pCgbSndBuf = (s16*)g_pCgbEmuBuf->pSoundBuf;
	g_nCgbSndBufSize = g_pCgbEmuBuf->nSoundBufSize >> 1;
	g_nCgbSndBufSwap = g_sCgbConfigData.nSoundSwapLR;

	g_sCgbSndSaveData[0].SetData(&g_nCgbSndTicks, 4, 1, 2);
	g_sCgbSndSaveData[1].SetData(&g_nCgbSnd1Index, 4, 1, 0);
	g_sCgbSndSaveData[2].SetData(&g_nCgbSnd1Length, 4, 1, 0);
	g_sCgbSndSaveData[3].SetData(&g_nCgbSnd1Frequency, 4, 1, 0);
	g_sCgbSndSaveData[4].SetData(&g_nCgbSnd1EnvelopeValue, 4, 1, 0);
	g_sCgbSndSaveData[5].SetData(&g_nCgbSnd1EnvelopeLength, 4, 1, 0);
	g_sCgbSndSaveData[6].SetData(&g_nCgbSnd2Index, 4, 1, 0);
	g_sCgbSndSaveData[7].SetData(&g_nCgbSnd2Length, 4, 1, 0);
	g_sCgbSndSaveData[8].SetData(&g_nCgbSnd2Frequency, 4, 1, 0);
	g_sCgbSndSaveData[9].SetData(&g_nCgbSnd2EnvelopeValue, 4, 1, 0);
	g_sCgbSndSaveData[10].SetData(&g_nCgbSnd2EnvelopeLength, 4, 1, 0);
	g_sCgbSndSaveData[11].SetData(&g_nCgbSnd3Index, 4, 1, 0);
	g_sCgbSndSaveData[12].SetData(&g_nCgbSnd3Length, 4, 1, 0);
	g_sCgbSndSaveData[13].SetData(&g_nCgbSnd3Frequency, 4, 1, 0);
	g_sCgbSndSaveData[14].SetData(&g_nCgbSnd4Index, 4, 1, 0);
	g_sCgbSndSaveData[15].SetData(&g_nCgbSnd4Length, 4, 1, 0);
	g_sCgbSndSaveData[16].SetData(&g_nCgbSnd4Frequency, 4, 1, 0);
	g_sCgbSndSaveData[17].SetData(&g_nCgbSnd4EnvelopeValue, 4, 1, 0);
	g_sCgbSndSaveData[18].SetData(&g_nCgbSnd4EnvelopeLength, 4, 1, 0);
	g_sCgbSndSaveData[19].SetData(&g_nCgbSnd1SweepLimit, 4, 14, 0);
	g_sCgbSndSaveData[20].SetData(&g_nCgbSnd1SweepLength, 4, 1, 0);
	g_sCgbSndSaveData[21].SetData(&g_nCgbSnd4Shift, 4, 1, 0);
	g_sCgbSndSaveData[22].SetData(&g_nCgbSndTicks, 4, 4, 0);
	
	{
		void cgbSndChannel4MakeTable();
		cgbSndChannel4MakeTable();
	}

	cgbSndReset();
}

/** @brief Reset Sound */
void cgbSndReset()
{
	g_nCgbSndBufPos = (g_pCgbEmuBuf->nAudioSampleOffset<<1);
	g_nCgbSndBufDiff = 0;
	g_nCgbSndBufAdd = CGB_SND_COUNT;

	g_nCgbSndTicks = 0;
	g_nCgbSndTick0 = CGB_SND_TICKS;

	g_nCgbSnd1Index = 0;
	g_nCgbSnd1Length = 0;
	g_nCgbSnd1Frequency = 0;
	g_nCgbSnd1EnvelopeValue = 0;
	g_nCgbSnd1EnvelopeLength = 0;
	g_nCgbSnd1EnvelopeLengthInit = 0;
	g_nCgbSnd1SweepLimit = 2047;
	g_nCgbSnd1SweepLength = 0;
	g_nCgbSnd1SweepLengthInit = 0;
	g_pCgbSnd1Wave = g_nCgbSndWavePattern[2];

	g_nCgbSnd2Index = 0;
	g_nCgbSnd2Length = 0;
	g_nCgbSnd2Frequency = 0;
	g_nCgbSnd2EnvelopeValue = 0;
	g_nCgbSnd2EnvelopeLength = 0;
	g_nCgbSnd2EnvelopeLengthInit = 0;
	g_pCgbSnd2Wave = g_nCgbSndWavePattern[2];

	g_nCgbSnd3Index = 0;
	g_nCgbSnd3Length = 0;
	g_nCgbSnd3Frequency = 0;

	g_nCgbSnd4Index = 0;
	g_nCgbSnd4Length = 0;
	g_nCgbSnd4Frequency = 0;
	g_nCgbSnd4EnvelopeValue = 0;
	g_nCgbSnd4EnvelopeLength = 0;
	g_nCgbSnd4EnvelopeLengthInit = 0;
	g_nCgbSnd4Shift = 0xFFFFFFFF;//0x7F;

	g_nCgbSnd4TableIndex = 0;

	g_nCgbSnd1SweepLimit = g_pCgbEmuBuf->funcConfigData("CGB", "SoundCH1SweepLimit", 2047);

	g_nCgbSnd1SweepFreq = g_pCgbRegNR14->rFreq;
}

/** @brief Resume Sound */
void cgbSndResume()
{
	g_nCgbSndBufPos = (g_pCgbEmuBuf->nAudioSampleOffset<<1);
	//g_nCgbSndBufPos = (g_nCgbSndBufSize >> 1);
	g_nCgbSndBufDiff = 0;
	g_nCgbSndBufAdd = CGB_SND_COUNT;

	g_nCgbSndVolume1 = g_pCgbRegNR50->rSO1Volume;
	g_nCgbSndVolume2 = g_pCgbRegNR50->rSO2Volume;

#if (TRL_SOUND_WAVE_TEST== 1)
	g_pCgbSnd1Wave = g_nCgbSndWavePattern2[g_pCgbRegNR11->rDuty];
	g_pCgbSnd2Wave = g_nCgbSndWavePattern2[g_pCgbRegNR21->rDuty];
#else
	g_pCgbSnd1Wave = g_nCgbSndWavePattern[g_pCgbRegNR11->rDuty];
	g_pCgbSnd2Wave = g_nCgbSndWavePattern[g_pCgbRegNR21->rDuty];
#endif
	
	g_nCgbSnd1SweepLengthInit = CGB_SND_LENGTH2 * g_pCgbRegNR10->rTime;
	g_nCgbSnd1EnvelopeLengthInit = CGB_SND_LENGTH3 * g_pCgbRegNR12->rSteps;
	g_nCgbSnd2EnvelopeLengthInit = CGB_SND_LENGTH3 * g_pCgbRegNR22->rSteps;
	g_nCgbSnd4EnvelopeLengthInit = CGB_SND_LENGTH3 * g_pCgbRegNR42->rSteps;

	g_nCgbSnd4TableIndex = 0;
	if(g_pCgbRegNR43->rStepNumber)	// 7 Steps
	{
		g_nCgbSnd4TableIndex = cgbSndNoiseStep7ShiftIndex[g_nCgbSnd4Shift&cgbSndNoiseStep7ShiftMask];
		if(g_nCgbSnd4TableIndex == -1)
		{
			NN_LOG("Bad g_nCgbSnd4TableIndex\n");
			g_nCgbSnd4TableIndex = 0x7F;
		}
	}
	else
	{
		g_nCgbSnd4TableIndex = cgbSndNoiseStep15ShiftIndex[g_nCgbSnd4Shift&cgbSndNoiseStep15ShiftMask];
		if(g_nCgbSnd4TableIndex == -1)
		{
			NN_LOG("Bad g_nCgbSnd4TableIndex\n");
			g_nCgbSnd4TableIndex = 0x7FFF;
		}
	}

	g_nCgbSnd1SweepFreq = g_pCgbRegNR14->rFreq;
}

/** @brief Process Sound Channel 1 */
inline void cgbSndChannel1()
{
	trlTraceSoundDetailMakeSample();
	u32 g_nCgbSnd1FrequencyEx = g_nCgbSnd1Frequency>>g_nCgbSndMultiSample;
	s32 sample1 = 0;
	s32 sample2 = 0;
	for(int i=0;i<(1<<g_nCgbSndMultiSample);i++)
	// Process Data
	if(g_nCgbSnd1Length || !g_pCgbRegNR14->rCounter)
	{
		g_nCgbSnd1Index += g_nCgbSnd1FrequencyEx;
		g_nCgbSnd1Index &= 0x1FFFFFFF;
#if (TRL_SOUND_WAVE_TEST==1)
		s16 nData = g_pCgbSnd1Wave[g_nCgbSnd1Index>>(26-CGB_SND_STEP_SHIFT)] * g_nCgbSnd1EnvelopeValue;
#else
		s16 nData = g_pCgbSnd1Wave[g_nCgbSnd1Index>>26] * g_nCgbSnd1EnvelopeValue * CGB_SND_VOLUMESCALE;
#endif		

#if (TRL_SOUND_FREQ_LIMIT == 1)
		if(g_nCgbSnd1Frequency >= CGB_SND_FREQLIMIT)
			nData = 0;
#endif
#if TRL_SOUND_DEBUG
		if(g_bCgbSndOnOffCH1 == 0)
			nData = 0;
#endif

		if(g_pCgbRegNR51->rSoundSO1 & 1)
			sample1 += nData;
		if(g_pCgbRegNR51->rSoundSO2 & 1)
			sample2 += nData;
	}
	g_nCgbSndBufOutput1 += sample1>>g_nCgbSndMultiSample;
	g_nCgbSndBufOutput2 += sample2>>g_nCgbSndMultiSample;

	// Calculate Length
	if(g_nCgbSnd1Length)
	{
		--g_nCgbSnd1Length;
		if(g_nCgbSnd1Length <=0 && g_pCgbRegNR14->rCounter)
			g_pCgbRegNR52->rSound1 = 0;
	}

	// Process Envelope
	if(g_nCgbSnd1EnvelopeLength)
	{
		--g_nCgbSnd1EnvelopeLength;
		if(g_nCgbSnd1EnvelopeLength <= 0)
		{
			if(g_pCgbRegNR12->rDirection)
			{
				if(g_nCgbSnd1EnvelopeValue < 15)
					++g_nCgbSnd1EnvelopeValue;
			}
			else
			{
				if(g_nCgbSnd1EnvelopeValue)
					--g_nCgbSnd1EnvelopeValue;
			}
			g_nCgbSnd1EnvelopeLength += g_nCgbSnd1EnvelopeLengthInit;
		}
	}

	// Process Sweep
	if(g_nCgbSnd1SweepLength)
	{
		--g_nCgbSnd1SweepLength;
		if(g_nCgbSnd1SweepLength<=0)
		{
			s32 nFreq = g_pCgbRegNR14->rFreq;

			if(g_bCgbSnd1SweepMode)	// New
			{
				nFreq = g_nCgbSnd1SweepFreq;
				if(g_pCgbRegNR10->rShift)	// DMGARIE0.G28: no need if 
				{
					if(g_pCgbRegNR10->rAS)
						nFreq -= nFreq >> g_pCgbRegNR10->rShift;
					else
						nFreq += nFreq >> g_pCgbRegNR10->rShift;					
				}
				g_nCgbSnd1SweepFreq = nFreq;
			}
			else					// Old
			{
				if(g_pCgbRegNR10->rShift)
				{
					if(g_pCgbRegNR10->rAS)
						nFreq -= g_pCgbRegNR14->rFreq >> g_pCgbRegNR10->rShift;
					else
						nFreq += g_pCgbRegNR14->rFreq >> g_pCgbRegNR10->rShift;
					if(nFreq == g_pCgbRegNR14->rFreq)
						nFreq = 0;
				}
			}

			if(nFreq < 0)
				g_nCgbSnd1SweepLength += g_nCgbSnd1SweepLengthInit;
			else if(nFreq > g_nCgbSnd1SweepLimit)
			{
				g_nCgbSnd1SweepLength = 0;
				g_pCgbRegNR52->rSound1 = 0;
			}
			else
			{
				g_nCgbSnd1SweepLength += g_nCgbSnd1SweepLengthInit;
				g_nCgbSnd1Frequency = (CGB_SND_FREQ<<1) / ((2048 - nFreq));
				g_pCgbRegNR14->rFreq = nFreq;
			}
			trlTraceSoundDetallSweepFreq(nFreq);
		}
	}
}

/** @brief Process Sound Channel 2 */
inline void cgbSndChannel2()
{
	// Process Data
	u32 g_nCgbSnd2FrequencyEx = g_nCgbSnd2Frequency>>g_nCgbSndMultiSample;
	s32 sample1 = 0;
	s32 sample2 = 0;
	for(int i=0;i<(1<<g_nCgbSndMultiSample);i++)
	if(g_nCgbSnd2Length || !g_pCgbRegNR24->rCounter)
	{
		g_nCgbSnd2Index += g_nCgbSnd2FrequencyEx;
		g_nCgbSnd2Index &= 0x1FFFFFFF;
#if (TRL_SOUND_WAVE_TEST==1)
		s16 nData = g_pCgbSnd2Wave[g_nCgbSnd2Index>>(26-CGB_SND_STEP_SHIFT)] * g_nCgbSnd2EnvelopeValue;
#else
		s16 nData = g_pCgbSnd2Wave[g_nCgbSnd2Index>>26] * g_nCgbSnd2EnvelopeValue * CGB_SND_VOLUMESCALE;
#endif		

#if (TRL_SOUND_FREQ_LIMIT == 1)
		if(g_nCgbSnd2Frequency >= CGB_SND_FREQLIMIT)
			nData = 0;
#endif
#if TRL_SOUND_DEBUG
		if(g_bCgbSndOnOffCH2 == 0)
			nData = 0;
#endif

		if(g_pCgbRegNR51->rSoundSO1 & 2)
			sample1 += nData;
		if(g_pCgbRegNR51->rSoundSO2 & 2)
			sample2 += nData;
	}
	g_nCgbSndBufOutput1 += sample1>>g_nCgbSndMultiSample;
	g_nCgbSndBufOutput2 += sample2>>g_nCgbSndMultiSample;

	// Calculate Length
	if(g_nCgbSnd2Length)
	{
		--g_nCgbSnd2Length;
		if(g_nCgbSnd2Length <= 0 && g_pCgbRegNR24->rCounter)
			g_pCgbRegNR52->rSound2 = 0;
	}

	// Process Envelope
	if(g_nCgbSnd2EnvelopeLength)
	{
		--g_nCgbSnd2EnvelopeLength;
		if(g_nCgbSnd2EnvelopeLength <= 0)
		{
			if(g_pCgbRegNR22->rDirection)
			{
				if(g_nCgbSnd2EnvelopeValue < 15)
					++g_nCgbSnd2EnvelopeValue;
			}
			else
			{
				if(g_nCgbSnd2EnvelopeValue)
					--g_nCgbSnd2EnvelopeValue;
			}
			g_nCgbSnd2EnvelopeLength += g_nCgbSnd2EnvelopeLengthInit;
		}
	}
}

/** @brief Process Sound Channel 3 */
inline void cgbSndChannel3()
{
	// Process Data
	u32 g_nCgbSnd3FrequencyEx = g_nCgbSnd3Frequency>>g_nCgbSndMultiSample;
	s32 sample1 = 0;
	s32 sample2 = 0;
	for(int i=0;i<(1<<g_nCgbSndMultiSample);i++)
	if(g_nCgbSnd3Length || !g_pCgbRegNR34->rCounter)
	{
		g_nCgbSnd3Index += g_nCgbSnd3FrequencyEx;
		g_nCgbSnd3Index &= 0x1FFFFFFF;
		s32 nData = g_pCgbREG[0x30+(g_nCgbSnd3Index>>25)];
		

		if(g_nCgbSnd3Index & 0x01000000)
			nData &= 0x0F;
		else
			nData >>= 4;

		
		nData -= 8;
#if !TRL_SOUND_CGB_CH3_VOLUME_HALF
		nData *= 2;
#endif
		

#if (TRL_SOUND_FREQ_LIMIT == 1)
		if(g_nCgbSnd3Frequency >= CGB_SND_FREQLIMIT)
			nData = 0;
#endif


		switch(g_pCgbRegNR32->rLevel)
		{
		case 0:
			nData = 0;
			break;
		case 2:
			nData >>= 1;
			break;
		case 3:
			nData >>= 2;
			break;
		}

		nData *= CGB_SND_VOLUMESCALE;
#if TRL_SOUND_DEBUG
		if(g_bCgbSndOnOffCH3 == 0)
			nData = 0;
#endif
		if(g_pCgbRegNR51->rSoundSO1 & 4)
			sample1 += nData;
			
		if(g_pCgbRegNR51->rSoundSO2 & 4)
			sample2 += nData;
	}
	
	g_nCgbSndBufOutput1 += sample1>>g_nCgbSndMultiSample;
	g_nCgbSndBufOutput2 += sample2>>g_nCgbSndMultiSample;
	// Calculate Length
	if(g_nCgbSnd3Length)
	{
		--g_nCgbSnd3Length;
		if(g_nCgbSnd3Length <= 0 && g_pCgbRegNR34->rCounter)
			g_pCgbRegNR52->rSound3 = 0;
	}
}

void cgbSndChannel4MakeTable()
{
	u32 shift;
	u8 feedbit = 0;
	u8 feedbit2 = 0;
	u32 loopbit = 0;
	u8 out = 0;
	u8 bit1, bit3;
	u32 NOISE_OUTPUT;

	for(int i=0;i<0x100;i++)
		cgbSndNoiseStep7ShiftIndex[i] = -1;
	for(int i=0;i<0x10000;i++)
		cgbSndNoiseStep15ShiftIndex[i] = -1;
	


	//step 7
	shift = 0x7F;
	feedbit = 0x02;
	feedbit2 = 0x01;
	loopbit = 0x80;

	for(int i=0;i<cgbSndNoiseStep7Length;i++)
	{
		out = 1;
		bit1 = (u8)(shift & feedbit);
		bit3 = (u8)(shift & feedbit2);
		if(bit1 && bit3)
			out = 0;
		else if( (bit1 == 0) && (bit3 == 0) )
			out = 0;

		NOISE_OUTPUT = bit3;
		shift &= (~loopbit);	
		


		cgbSndNoiseStep7Table[i] = NOISE_OUTPUT;
		if(cgbSndNoiseStep7ShiftIndex[shift] == -1)
		{
			cgbSndNoiseStep7ShiftIndex[shift]  = i;
		}
		else
		{
			NN_LOG("cgbSndNoiseStep7ShiftIndex  repeat\n");
			while(1){};
		}
		if(out)
			shift |= loopbit;
		shift >>=1;
	}

	//step 15
	shift = 0x7FFF;
	feedbit = 0x02;
	feedbit2 = 0x01;
	loopbit = 0x8000;

	for(int i=0;i<cgbSndNoiseStep15Length;i++)
	{
		out = 1;
		bit1 = (u8)(shift & feedbit);
		bit3 = (u8)(shift & feedbit2);
		if(bit1 && bit3)
			out = 0;
		else if( (bit1 == 0) && (bit3 == 0) )
			out = 0;

		NOISE_OUTPUT = bit3;
		shift &= (~loopbit);	
		


		cgbSndNoiseStep15Table[i] = NOISE_OUTPUT;
		if(cgbSndNoiseStep15ShiftIndex[shift] == -1)
		{
			cgbSndNoiseStep15ShiftIndex[shift]  = i;
		}
		else
		{
			NN_LOG("cgbSndNoiseStep15ShiftIndex  repeat\n");
			while(1){};
		}
		if(out)
			shift |= loopbit;
		shift >>=1;
	}
}


#if TRL_SOUND_NOISE_TEST
static u8  NOISE_PULSE = 0x60;
static u8  NOISE_OUTPUT = 0;
#endif
/** @brief Process Sound Channel 4 */
inline void cgbSndChannel4()
{
	// Process Data
	if((g_nCgbSnd4Length || !g_pCgbRegNR44->rCounter) && (g_pCgbRegNR43->rShiftClock < 0x0D))
	{
		g_nCgbSnd4Index += g_nCgbSnd4Frequency;
#if TRL_SOUND_NOISE_TEST
		s8 level = 0;
		u32 avg = 0;
		s8 ct = 0;
		u8 feedbit = 0;
		u8 feedbit2 = 0;
		u32 loopbit = 0;
		u8 out = 0;
		u8 bit1, bit3;

		if(g_pCgbRegNR43->rStepNumber)	// 7 Steps
		{
			feedbit = 0x02;
			feedbit2 = 0x01;
			loopbit = 0x80;
		}
		else
		{
			feedbit = 0x02;
			feedbit2 = 0x01;
			loopbit = 0x8000;
		}
		#define SND4_FREQ_COSNT 0x11A9F90

		while(g_nCgbSnd4Index >= SND4_FREQ_COSNT)		
		{
			ct++;
			out = 1;
			bit1 = (u8)(g_nCgbSnd4Shift & feedbit);
			bit3 = (u8)(g_nCgbSnd4Shift & feedbit2);
			if(bit1 && bit3)
				out = 0;
			else if( (bit1 == 0) && (bit3 == 0) )
				out = 0;

			NOISE_OUTPUT = bit3;		

			g_nCgbSnd4Shift &= (~loopbit);
			if(out)
				g_nCgbSnd4Shift |= loopbit;

			g_nCgbSnd4Shift >>=1;

			if(g_bCgbSnd4NoiseTable)		
			{
				if(g_pCgbRegNR43->rStepNumber)	// 7 Steps
				{
					NOISE_OUTPUT = cgbSndNoiseStep7Table[g_nCgbSnd4TableIndex++];
					if(g_nCgbSnd4TableIndex >= cgbSndNoiseStep7Length)
						g_nCgbSnd4TableIndex = 0;
				}
				else
				{
					NOISE_OUTPUT = cgbSndNoiseStep15Table[g_nCgbSnd4TableIndex++];
					if(g_nCgbSnd4TableIndex >= cgbSndNoiseStep15Length)
						g_nCgbSnd4TableIndex = 0;
				}
			}

			if(NOISE_OUTPUT)
				avg++;
			g_nCgbSnd4Index -= SND4_FREQ_COSNT;
		}
		if(ct > 1)
		{			
			level = (s8)(1.0*avg*NOISE_PULSE/ct);			
		}
		else
			if(NOISE_OUTPUT)
				level = (s8)NOISE_PULSE;
			else
				level = 0;

		level -= ((s8)NOISE_PULSE/2);

		s16 nData = -1*(level) * g_nCgbSnd4EnvelopeValue * CGB_SND_VOLUMESCALE/ (NOISE_PULSE/2);
		if(g_bCgbSnd4NoiseTable)
		{
			if(ct > 4)
			{
				if(g_pCgbRegNR43->rStepNumber)	// 7 Steps
					nData = -1*cgbSndNoiseStep7Table_12[g_nCgbSnd4TableIndex]*g_nCgbSnd4EnvelopeValue*CGB_SND_VOLUMESCALE/0xF/0x60;
			}
		}
#else
		if(g_pCgbRegNR43->rStepNumber)	// 7 Steps
		{

			while(g_nCgbSnd4Index >= 0x200000)
			{
				g_nCgbSnd4Shift = (((g_nCgbSnd4Shift << 6) ^ (g_nCgbSnd4Shift << 5)) & 0x40) | (g_nCgbSnd4Shift >> 1);
				g_nCgbSnd4Index -= 0x200000;
			}
		}
		else							// 15 Steps
		{
			while(g_nCgbSnd4Index >= 0x200000)
			{
				g_nCgbSnd4Shift = (((g_nCgbSnd4Shift << 14) ^ (g_nCgbSnd4Shift << 13)) & 0x4000) | (g_nCgbSnd4Shift >> 1);
				g_nCgbSnd4Index -= 0x200000;
			}
		}
		s16 nData = (((g_nCgbSnd4Shift & 1) << 1) - 1) * g_nCgbSnd4EnvelopeValue*CGB_SND_STEP;
#endif

#if (TRL_SOUND_FREQ_LIMIT == 1)
		if(g_nCgbSnd4Frequency >= CGB_SND_FREQLIMIT)
			nData = 0;
#endif
#if TRL_SOUND_DEBUG
		if(g_bCgbSndOnOffCH4 == 0)
			nData = 0;
#endif
		if(g_pCgbRegNR51->rSoundSO1 & 8)
			g_nCgbSndBufOutput1 += (s16)nData;
		if(g_pCgbRegNR51->rSoundSO2 & 8)
			g_nCgbSndBufOutput2 += (s16)nData;
	}

	// Calculate Length
	if(g_nCgbSnd4Length)
	{
		--g_nCgbSnd4Length;
		if(g_nCgbSnd4Length <= 0 && g_pCgbRegNR44->rCounter)
			g_pCgbRegNR52->rSound4 = 0;
	}

	// Process Envelope
	if(g_nCgbSnd4EnvelopeLength)
	{
		--g_nCgbSnd4EnvelopeLength;
		if(g_nCgbSnd4EnvelopeLength <= 0)
		{
			if(g_pCgbRegNR42->rDirection)
			{
				if(g_nCgbSnd4EnvelopeValue < 15)
					++g_nCgbSnd4EnvelopeValue;
			}
			else
			{
				if(g_nCgbSnd4EnvelopeValue)
					--g_nCgbSnd4EnvelopeValue;
			}
			g_nCgbSnd4EnvelopeLength += g_nCgbSnd4EnvelopeLengthInit;
		}
	}
}

/** @brief Update Ticks */
void cgbSndUpdateTicks()
{	
	if(g_pCgbEmuBuf->nAudioSampleSkip != 0)
	{
		for(s32 n=0;n<g_pCgbEmuBuf->nAudioSampleSkip;++n)
		{
			g_pCgbSndBuf[g_nCgbSndBufPos+g_nCgbSndBufSwap] = 0;
			g_pCgbSndBuf[g_nCgbSndBufPos+1-g_nCgbSndBufSwap] = 0;
			g_nCgbSndBufPos += 2;
			if(g_nCgbSndBufPos >= g_nCgbSndBufSize)
			{
				g_nCgbSndBufPos = 0;
			}
		}
		g_pCgbEmuBuf->nAudioSampleSkip = 0;
	}
	
	if(g_pCgbEmuBuf->nAudioSampleCurFrame == 0)
		return;
	s32 nSize = CGB_SND_COUNT;
	if(g_pCgbEmuBuf->nAudioSampleCurFrame >= nSize)
		g_pCgbEmuBuf->nAudioSampleCurFrame -=nSize;
	else
	{
		nSize = g_pCgbEmuBuf->nAudioSampleCurFrame;
		g_pCgbEmuBuf->nAudioSampleCurFrame = 0;
	}
	if(g_pCgbRegNR52->rSoundAll)
	{
		for(s32 n=0; n<nSize; ++n)
		{
			g_nCgbSndBufOutput1 = 0;
			g_nCgbSndBufOutput2 = 0;

			if(g_pCgbRegNR52->rSound1)
				cgbSndChannel1();
			if(g_pCgbRegNR52->rSound2)
				cgbSndChannel2();
			if(g_pCgbRegNR52->rSound3)
				cgbSndChannel3();
			if(g_pCgbRegNR52->rSound4)
				cgbSndChannel4();

			g_nCgbSndBufOutput2 *= g_nCgbSndVolume2;
			if(g_nCgbSndBufOutput2 >= 32768)
				g_nCgbSndBufOutput2 = 32767;
			else if(g_nCgbSndBufOutput2 < -32768)
				g_nCgbSndBufOutput2 = -32768;
			g_pCgbSndBuf[g_nCgbSndBufPos+g_nCgbSndBufSwap] = (s16)g_nCgbSndBufOutput2;

			g_nCgbSndBufOutput1 *= g_nCgbSndVolume1;
			if(g_nCgbSndBufOutput1 >= 32768)
				g_nCgbSndBufOutput1 = 32767;
			else if(g_nCgbSndBufOutput1 < -32768)
				g_nCgbSndBufOutput1 = -32768;
			g_pCgbSndBuf[g_nCgbSndBufPos+1-g_nCgbSndBufSwap] = (s16)g_nCgbSndBufOutput1;

			g_nCgbSndBufPos += 2;

			if(g_nCgbSndBufPos >= g_nCgbSndBufSize)
			{
#ifdef TRL_PLATFORM_PC
				g_pCgbEmuBuf->funcAudioRecord((u8*)g_pCgbSndBuf, g_nCgbSndBufSize*2);
#endif
				g_nCgbSndBufPos = 0;
			}
		}
	}
	else
	{
		for(s32 n=0; n<nSize; ++n)
		{
			g_pCgbSndBuf[g_nCgbSndBufPos++] = 0;
			g_pCgbSndBuf[g_nCgbSndBufPos++] = 0;
			if(g_nCgbSndBufPos >= g_nCgbSndBufSize)
				g_nCgbSndBufPos = 0;
		}
	}
}

/** @brief Update Ticks */
void cgbSndUpdateTicksOneFrame()
{
	if(g_pCgbEmuBuf->nAudioSampleSkip != 0)
	{
		for(s32 n=0;n<g_pCgbEmuBuf->nAudioSampleSkip;++n)
		{
			g_pCgbSndBuf[g_nCgbSndBufPos+g_nCgbSndBufSwap] = 0;
			g_pCgbSndBuf[g_nCgbSndBufPos+1-g_nCgbSndBufSwap] = 0;
			g_nCgbSndBufPos += 2;
			if(g_nCgbSndBufPos >= g_nCgbSndBufSize)
			{
				g_nCgbSndBufPos = 0;
			}
		}
		g_pCgbEmuBuf->nAudioSampleSkip = 0;
	}
	s32 nSize = g_pCgbEmuBuf->nAudioSampleCurFrame;
	g_pCgbEmuBuf->nAudioSampleCurFrame = 0;
	if(g_pCgbRegNR52->rSoundAll)
	{
		for(s32 n=0; n<nSize; ++n)
		{
			cgbSndRegWriteLog_LogRunOneSample();
			g_nCgbSndBufOutput1 = 0;
			g_nCgbSndBufOutput2 = 0;

			if(g_pCgbRegNR52->rSound1)
				cgbSndChannel1();
			if(g_pCgbRegNR52->rSound2)
				cgbSndChannel2();
			if(g_pCgbRegNR52->rSound3)
				cgbSndChannel3();
			if(g_pCgbRegNR52->rSound4)
				cgbSndChannel4();

			g_nCgbSndBufOutput2 *= g_nCgbSndVolume2;
			if(g_nCgbSndBufOutput2 >= 32768)
				g_nCgbSndBufOutput2 = 32767;
			else if(g_nCgbSndBufOutput2 < -32768)
				g_nCgbSndBufOutput2 = -32768;
			g_pCgbSndBuf[g_nCgbSndBufPos+g_nCgbSndBufSwap] = (s16)g_nCgbSndBufOutput2;

			g_nCgbSndBufOutput1 *= g_nCgbSndVolume1;
			if(g_nCgbSndBufOutput1 >= 32768)
				g_nCgbSndBufOutput1 = 32767;
			else if(g_nCgbSndBufOutput1 < -32768)
				g_nCgbSndBufOutput1 = -32768;
			g_pCgbSndBuf[g_nCgbSndBufPos+1-g_nCgbSndBufSwap] = (s16)g_nCgbSndBufOutput1;

			g_nCgbSndBufPos += 2;

			if(g_nCgbSndBufPos >= g_nCgbSndBufSize)
			{
#ifdef TRL_PLATFORM_PC
				g_pCgbEmuBuf->funcAudioRecord((u8*)g_pCgbSndBuf, g_nCgbSndBufSize*2);
#endif
				g_nCgbSndBufPos = 0;
			}
		}
	}
	else
	{
		for(s32 n=0; n<nSize; ++n)
		{
			g_pCgbSndBuf[g_nCgbSndBufPos++] = 0;
			g_pCgbSndBuf[g_nCgbSndBufPos++] = 0;
			if(g_nCgbSndBufPos >= g_nCgbSndBufSize)
				g_nCgbSndBufPos = 0;
		}
	}
}

