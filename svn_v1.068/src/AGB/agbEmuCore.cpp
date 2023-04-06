/**
 * @file agbEmuCore.cpp
 * @author zhfang & chentian
 * @date 2009.11.25
 * @brief TRL Emulate For CTR - Emu Core AGB
 */
#include "agbEmuCore.h"
#include "agbMemory.h"
#include "agbRegister.h"
#include "agbBackup.h"
#include "agbGraphic.h"
#include "agbSound.h"
#include "agbCPU.h"
#include "agbDMA.h"
#include "agbInput.h"
#include "agbTime.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
trlSEmuShellBuffer *g_pAgbEmuBuf = NULL;
trlSEmuShellCore g_sEmuCoreAGB = {
	agbEmuCoreInit,
	agbEmuCoreRunOneFrame,
	agbEmuCoreReset,
	agbEmuCoreInput,
	agbEmuCoreResume,
	agbEmuCoreExit,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL };
//@}

/** @brief EmuCore init */
void agbEmuCoreInit(trlSEmuShellBuffer* pBuf)
{	
	if(pBuf == NULL)
		return;

	g_pAgbEmuBuf = pBuf;

	agbMemInit();
	agbRegInit();
	agbDmaInit();
	agbBakInit();
	agbGrpInit();
	agbSndInit();
	agbKeyInit();
	agbTimeInit();
	agbCPUInit();
}

/** @brief EmuCore RunOneFrame */
void agbEmuCoreRunOneFrame()
{
#if ((TRL_EMUTYPE==0) || (TRL_EMUTYPE==2))
	g_nAgbBreakFlag = 0;
	while(1)
	{
		agbCPURun();				

		u32 nRunTicks = g_nAgbCPUClock;
		g_nAgbCPUClock = 0;

		if(g_pAgbHaltCnt->rHalt)
			nRunTicks = 400;

		agbGrpUpdateTicks(nRunTicks);

		if(!g_pAgbHaltCnt->rPowerDown)
			agbTimeUpdate(nRunTicks);
		
		agbSndUpdateTicks(nRunTicks);

		if(g_nAgbBreakFlag)
			return;
	}
#endif
}

/** @brief EmuCore Reset */
void agbEmuCoreReset()
{
	agbMemReset();
	agbRegReset();
	agbDmaReset();
	agbBakReset();
	agbGrpReset();
	agbSndReset();
	agbKeyReset();
	agbTimeReset();
	agbCPUReset();
}

/** @brief EmuCore Input */
void agbEmuCoreInput(u32 nKeyBuf)
{
	agbKeyUpdate(nKeyBuf);
}

/** @brief EmuCore Resume */
void agbEmuCoreResume()
{
}

/** @brief EmuCore Exit */
void agbEmuCoreExit()
{
	agbBakExit();
}
