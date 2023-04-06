/**
 * @file trlEmuShellAudio.h
 * @author Chentian
 * @date 2009.12.17
 * @brief TRL Emulate - EmuShell Audio Module
 */
#pragma once
#include "..\trlHeader.h"

/** @name Macro Define */
//@{
#define TRL_EMUCORE_AUDIO_SAMPLERATE	44100
//@}

/** @brief EmuShell Audio Init */
void trlEmuShellAudioInit();
/** @brief EmuShell Audio Start */
void trlEmuShellAudioStart();
/** @brief EmuShell Audio Resume */
void trlEmuShellAudioResume();
/** @brief EmuShell Audio Reset */
void trlEmuShellAudioReset();
/** @brief EmuShell Audio Play Sound */
void trlEmuShellAudioPlay();
/** @brief EmuShell Audio Pause Sound */
void trlEmuShellAudioPause();
/** @brief EmuShell Audio Stop Sound */
void trlEmuShellAudioStop();
/** @brief EmuShell Audio Exit */
void trlEmuShellAudioExit();
/** @brief EmuShell Audio Main(oneframe) */
void trlEmuShellAudioMain();
/** @brief EmuShell Audio Get Play Position */
s32 trlEmuShellAudioGetPlayPosition();
/** @brief EmuShell Audio Record Main */
void trlEmuShellAudioRecordMain(u8* pBuf, u32 nSize);
/** @brief EmuShell Audio Record Update */
void trlEmuShellAudioRecordUpdate();
