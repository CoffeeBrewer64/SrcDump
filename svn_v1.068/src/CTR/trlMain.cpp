/**
 * @file trlMain.cpp
 * @author zhfang
 * @date 2009.11.19
 * @brief TRL Emulate For CTR - Trl Main
 */
#include "..\EmuShell\trlEmuShell.h"
#include "..\EmuShell\trlEmuShellSuspend.h"

/** @brief nnMain*/
void nnMain()
{
	g_eTrlEmuShellState = eTrlEmuShellStateInitSleep;
	g_bQuit = eTrlQuit_NONE;
	while(g_bQuit != eTrlQuit_Close)
		trlEmuShellMain();	
}
