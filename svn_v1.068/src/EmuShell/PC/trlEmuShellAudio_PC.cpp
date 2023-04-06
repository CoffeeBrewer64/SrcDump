/**
 * @file trlEmuShellAudio_PC.cpp
 * @author Chentian
 * @date 2011.08.26
 * @brief TRL Emulate For PC - EmuShell Audio Module
 */
#include "..\trlEmuShellAudio.h"
#include "..\trlEmuShellStruct.h"
#pragma comment(lib, "Winmm.lib")

/**
 * @struct trlSESAudioWaveform
 * @brief EmuShell Audio Waveform
 */
struct trlSESAudioWaveform
{
	DWORD		dwRIFF;
	DWORD		dwRiffBlockSize;
	DWORD		dwWAVE;
	DWORD		dwFMT;
	DWORD		dwFmtBlockSize;
	WORD		wFormatTag;
	WORD		wChannels;
	DWORD		dwSamplesPerSec;
	DWORD		dwAvgBytesPerSec;
	WORD		wBlockAlign;
	WORD		wBitsPerSample;
	DWORD		dwDATA;
	DWORD		dwDataBlockSize;
};

/** @name Global Variable */
//@{
extern HWND		g_hWnd;
u64				g_nTrlAudioTime = 0;
s32				g_nTrlAudioPos = 0;
extern u32		g_bTrlAudioPaused;
extern u32		g_bTrlAudioRecord;
FILE*			g_pAudioRecord;

UINT			wResult;
HWAVEOUT		hWaveOut;
WAVEFORMATEX	pcmWaveFormat;
WAVEHDR			waveHdr;
MMTIME			mmtime;
//@}

/** @brief EmuShell Audio Get Play Position */
s32 trlEmuShellAudioGetPlayPosition()
{	
	mmtime.wType = TIME_SAMPLES;
	if(waveOutGetPosition(hWaveOut, &mmtime, sizeof(MMTIME)) != MMSYSERR_NOERROR )
		NN_LOG("waveOutGetPosition error\n");
	return mmtime.u.sample%(TRL_EMUCORE_SNDBUF/4);
}

/** @brief EmuShell Audio Get Play Size */
s32 trlEmuShellAudioGetPlaySize()
{
	s32 nPos;
	if(g_sEmuShellBuffer.nRomType == TRL_EMUCORE_ROMTYPE_NES)
		nPos = (s32)((trlTimeGet_us() - g_nTrlAudioTime) * 0.048f);
	else
		nPos = (s32)((trlTimeGet_us() - g_nTrlAudioTime) * 0.032728);
	s32 nDiff = nPos - g_nTrlAudioPos;
	g_nTrlAudioPos = nPos;
	return nDiff;
}

/** @brief EmuShell Audio Change Mono Filter */
void trlEmuShellAudioMonoFilter(u32 nMode)
{
}

/** @brief EmuShell Audio Init */
void trlEmuShellAudioInit()
{
	g_sEmuShellBuffer.funcChangeFilterMode = trlEmuShellAudioMonoFilter;
	g_sEmuShellBuffer.funcSoundPlaySize = trlEmuShellAudioGetPlaySize;
	g_sEmuShellBuffer.funcAudioRecord = trlEmuShellAudioRecordMain;
	g_sEmuShellBuffer.nSoundBufSize = TRL_EMUCORE_SNDBUF;

	g_sEmuShellBuffer.pWaveBuf = trlMemAlloc(g_sEmuShellBuffer.nSoundBufSize + 44, 4);
	g_sEmuShellBuffer.pSoundBuf = &((u8*)g_sEmuShellBuffer.pWaveBuf)[44];
	trlSESAudioWaveform* pWaveform = (trlSESAudioWaveform*)g_sEmuShellBuffer.pWaveBuf;
	pWaveform->dwRIFF = 0x46464952;
	pWaveform->dwRiffBlockSize = g_sEmuShellBuffer.nSoundBufSize + 40;
	pWaveform->dwWAVE = 0x45564157;
	pWaveform->dwFMT = 0x20746D66;
	pWaveform->dwFmtBlockSize = 0x10;
	pWaveform->wFormatTag = WAVE_FORMAT_PCM;
	pWaveform->wChannels = 2;
	pWaveform->dwSamplesPerSec = TRL_EMUCORE_AUDIO_SAMPLERATE;
	pWaveform->wBitsPerSample = 16;
	pWaveform->wBlockAlign = pWaveform->wChannels * pWaveform->wBitsPerSample / 8;
	pWaveform->dwAvgBytesPerSec = pWaveform->dwSamplesPerSec * pWaveform->wBlockAlign;
	pWaveform->dwDATA = 0x61746164;
	pWaveform->dwDataBlockSize = g_sEmuShellBuffer.nSoundBufSize;
	memset(g_sEmuShellBuffer.pSoundBuf, 0, g_sEmuShellBuffer.nSoundBufSize);

	pcmWaveFormat.wFormatTag = WAVE_FORMAT_PCM; 
	pcmWaveFormat.nChannels = 2; 
	pcmWaveFormat.nSamplesPerSec = 44100L; 
	pcmWaveFormat.nAvgBytesPerSec = 176400L; 
	pcmWaveFormat.nBlockAlign = 4; 
	pcmWaveFormat.wBitsPerSample = 16; 
	pcmWaveFormat.cbSize = 0;
	
	if (waveOutOpen((LPHWAVEOUT)&hWaveOut, WAVE_MAPPER, (LPWAVEFORMATEX )&pcmWaveFormat, (LONG)g_hWnd, 0L, CALLBACK_WINDOW)) 
		NN_LOG("waveOutOpen error\n");
	
	waveHdr.lpData = (LPSTR)g_sEmuShellBuffer.pSoundBuf; 
    waveHdr.dwBufferLength = g_sEmuShellBuffer.nSoundBufSize; 
    waveHdr.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP; 
    waveHdr.dwLoops = -1; 
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR));

	trlEmuShellAudioResume();
}

/** @brief EmuShell Audio Start */
void trlEmuShellAudioStart()
{
#if TRL_SOUND
	//sndPlaySound((LPCSTR)g_sEmuShellBuffer.pWaveBuf, SND_MEMORY | SND_ASYNC | SND_LOOP);//SND_SYNC
	wResult = waveOutWrite(hWaveOut, &waveHdr, sizeof(WAVEHDR)); 
    if (wResult != 0) 
		NN_LOG("trlEmuShellAudioStart error\n");

	g_nTrlAudioTime = trlTimeGet_us();
	g_nTrlAudioPos = 0;
#endif
}

/** @brief EmuShell Audio Reset */
void trlEmuShellAudioReset()
{
	trlEmuShellAudioStop();	
	trlEmuShellAudioResume();
	trlEmuShellAudioStart();
}

/** @brief EmuShell Audio Play Sound */
void trlEmuShellAudioPlay()
{
	waveOutRestart(hWaveOut);
	//trlEmuShellAudioStart();
}

/** @brief EmuShell Audio Pause Sound */
void trlEmuShellAudioPause()
{
	g_bTrlAudioPaused = 1;
	waveOutPause(hWaveOut);
	//trlEmuShellAudioStop();
}

/** @brief EmuShell Audio Stop Sound */
void trlEmuShellAudioStop()
{
	waveOutReset(hWaveOut);
	//sndPlaySound(NULL, SND_NODEFAULT);
}

/** @brief EmuShell Audio Exit */
void trlEmuShellAudioExit()
{
	trlEmuShellAudioStop();
	trlMemFree(g_sEmuShellBuffer.pSoundBuf);
}

/** @brief EmuShell Audio Record Main */
void trlEmuShellAudioRecordMain(u8* pBuf, u32 nSize)
{	
	if(g_bTrlAudioRecord)	
		fwrite(pBuf, 1, nSize, g_pAudioRecord);			
}

/** @brief EmuShell Audio Record Update */
void trlEmuShellAudioRecordUpdate()
{	
	if(g_bTrlAudioRecord)
		fclose(g_pAudioRecord);
	else
		g_pAudioRecord = fopen("d:\\record.raw", "wb");	
	g_bTrlAudioRecord = !g_bTrlAudioRecord;	
}
