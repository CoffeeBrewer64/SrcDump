/**
 * @file trlEmuShellAudio_CTR.cpp
 * @author Chentian
 * @date 2011.08.26
 * @brief TRL Emulate For CTR - EmuShell Audio Module
 */
#include "..\trlEmuShellAudio.h"
#include "..\trlEmuShellData.h"
#include "..\trlEmuShellStruct.h"
#include "EmuMenu\trlEmuMenu.h"
#include <nn/os.h>
#include <nn/cfg.h>
#include <nn/snd.h>
#include <nw/snd.h>
using namespace nn::os;
using namespace nn::snd;

/** @name Global Variable */
//@{
MixParam	g_hTrlAudioMix;
Voice*		g_pTrlAudioVoice = NULL;
WaveBuffer	g_hTrlAudioBuffer;
Thread		g_hTrlAudioThread;
u32			g_bTrlAudioThreadFlag = 0;
s32			g_nTrlAudioPos = 0;
extern u32	g_bTrlAudioPaused;
extern u32	g_bTrlAudioRecord;
extern CEmuMenu g_hTrlEmuMenu;
//@}

#define NW_SND_LOCK 1



/** @brief EmuShell Audio Thread Function */
void trlEmuShellAudioThreadFunc()
{
	while (g_bTrlAudioThreadFlag)
	{		
		nn::snd::WaitForDspSync();
		nw::snd::SoundSystem::SoundFrameProcess();
		nn::snd::FlushDataCache(reinterpret_cast<uptr>(g_sEmuShellBuffer.pSoundBuf), TRL_EMUCORE_SNDBUF);
		nn::snd::SendParameterToDsp();
	}
}

/** @brief EmuShell Audio Get Play Position */
s32 trlEmuShellAudioGetPlayPosition()
{
#if NW_SND_LOCK
	nw::snd::SoundSystem::SoundThreadScopedLock lock;
#endif
	return g_pTrlAudioVoice->GetPlayPosition();
}

/** @brief EmuShell Audio Get Play Size */
s32 trlEmuShellAudioGetPlaySize()
{
#if NW_SND_LOCK
	nw::snd::SoundSystem::SoundThreadScopedLock lock;
#endif
	s32 nPos = g_pTrlAudioVoice->GetPlayPosition();
	s32 nDiff = nPos - g_nTrlAudioPos;
	if(nDiff < 0)
		nDiff += (TRL_EMUCORE_SNDBUF>>2);
	g_nTrlAudioPos = nPos;
	return nDiff;
}

/** @brief EmuShell Audio Change Mono Filter */
void trlEmuShellAudioMonoFilter(u32 nMode)
{
#if NW_SND_LOCK
	nw::snd::SoundSystem::SoundThreadScopedLock lock;
#endif
#if TRL_SOUND_MONOFILTER
	if(nMode)
	{
		g_pTrlAudioVoice->SetFilterType(FILTER_TYPE_MONOPOLE);
		g_pTrlAudioVoice->EnableMonoFilter(1);
	}
	else
	{
		//all mode use the filter		
		g_pTrlAudioVoice->SetFilterType(FILTER_TYPE_MONOPOLE);		//g_pTrlAudioVoice->SetFilterType(FILTER_TYPE_NONE);
		g_pTrlAudioVoice->EnableMonoFilter(1);						//g_pTrlAudioVoice->EnableMonoFilter(0);
	}
#endif
}

/** @brief EmuShell Audio Init */
void trlEmuShellAudioInit()
{
	g_sEmuShellBuffer.funcChangeFilterMode = trlEmuShellAudioMonoFilter;
	g_sEmuShellBuffer.funcSoundPlaySize = trlEmuShellAudioGetPlaySize;
	g_sEmuShellBuffer.funcAudioRecord = trlEmuShellAudioRecordMain;
	g_sEmuShellBuffer.nSoundBufSize = TRL_EMUCORE_SNDBUF;
	g_sEmuShellBuffer.pSoundBuf = trlMemAllocDevice(g_sEmuShellBuffer.nSoundBufSize, 32);
	memset(g_sEmuShellBuffer.pSoundBuf, 0, TRL_EMUCORE_SNDBUF);

	nn::Result result = nn::dsp::Initialize();
	NN_UTIL_PANIC_IF_FAILED(result);
	result = nn::dsp::LoadDefaultComponent();
	NN_UTIL_PANIC_IF_FAILED(result);
	result = nn::snd::Initialize();
	NN_UTIL_PANIC_IF_FAILED(result);

	nn::snd::SetMasterVolume( 1.0f );
	nn::snd::SetSoundOutputMode((nn::snd::OutputMode )nn::cfg::CTR::GetSoundOutputMode());

	g_hTrlAudioMix.mainBus[CHANNEL_INDEX_FRONT_LEFT ] = 1.0f;
	g_hTrlAudioMix.mainBus[CHANNEL_INDEX_FRONT_RIGHT] = 1.0f;

	{
		#if NW_SND_LOCK
		//nw::snd::SoundSystem::SoundThreadScopedLock lock;
		#endif
		g_pTrlAudioVoice = nn::snd::AllocVoice(128, NULL, NULL);
		NN_TASSERT_(g_pTrlAudioVoice);
		g_pTrlAudioVoice->SetChannelCount( 2 );
		g_pTrlAudioVoice->SetSampleFormat( SAMPLE_FORMAT_PCM16 );
		g_pTrlAudioVoice->SetMixParam(g_hTrlAudioMix);
		g_pTrlAudioVoice->SetVolume(trlEmuShellDataGetConfigData("Sound", "Volume", 88)/100.f);
		g_pTrlAudioVoice->SetSampleRate(TRL_EMUCORE_AUDIO_SAMPLERATE);
		g_pTrlAudioVoice->SetPitch(1.0);
		g_pTrlAudioVoice->SetMonoFilterCoefficients(10000); //g_pTrlAudioVoice->SetMonoFilterCoefficients(12000);
		g_pTrlAudioVoice->SetFilterType(FILTER_TYPE_NONE);

		g_hTrlAudioBuffer.bufferAddress		= g_sEmuShellBuffer.pSoundBuf;
		g_hTrlAudioBuffer.sampleLength		= GetSampleLength(g_sEmuShellBuffer.nSoundBufSize, SAMPLE_FORMAT_PCM16, 2);
		g_hTrlAudioBuffer.loopFlag			= true;
		g_hTrlAudioBuffer.status			= WaveBuffer::STATUS_FREE;
		g_pTrlAudioVoice->AppendWaveBuffer(&g_hTrlAudioBuffer);
	}

	trlEmuShellAudioResume();
}

/** @brief EmuShell Audio Start */
void trlEmuShellAudioStart()
{
#if TRL_SOUND
	g_nTrlAudioPos = 0;
	g_bTrlAudioThreadFlag = 1;
	g_hTrlAudioThread.StartUsingAutoStack(trlEmuShellAudioThreadFunc, 4096, 10);
	//g_pTrlAudioVoice->SetState( Voice::STATE_PLAY );
#endif
}

/** @brief EmuShell Audio Reset */
void trlEmuShellAudioReset()
{
#if NW_SND_LOCK
	nw::snd::SoundSystem::SoundThreadScopedLock lock;
#endif
	g_nTrlAudioPos = 0;
	g_pTrlAudioVoice->SetState( Voice::STATE_STOP );
	g_hTrlAudioBuffer.status = WaveBuffer::STATUS_FREE;
	g_pTrlAudioVoice->AppendWaveBuffer(&g_hTrlAudioBuffer);
	memset(g_sEmuShellBuffer.pSoundBuf, 0, TRL_EMUCORE_SNDBUF);	

	trlEmuShellAudioResume();
}

/** @brief EmuShell Audio Play Sound */
void trlEmuShellAudioPlay()
{
	if(g_pTrlAudioVoice != NULL)
	{
#if NW_SND_LOCK
		nw::snd::SoundSystem::SoundThreadScopedLock lock;
#endif
		g_pTrlAudioVoice->SetState( Voice::STATE_PLAY );
	}
}

/** @brief EmuShell Audio Pause Sound */
void trlEmuShellAudioPause()
{
	g_bTrlAudioPaused = 1;
	if(g_pTrlAudioVoice != NULL)
	{
#if NW_SND_LOCK
		nw::snd::SoundSystem::SoundThreadScopedLock lock;
#endif		
		g_pTrlAudioVoice->SetState( Voice::STATE_PAUSE );
	}
}

/** @brief EmuShell Audio Stop Sound */
void trlEmuShellAudioStop()
{
	if(g_pTrlAudioVoice != NULL)
	{
#if NW_SND_LOCK
		nw::snd::SoundSystem::SoundThreadScopedLock lock;
#endif
		g_pTrlAudioVoice->SetState( Voice::STATE_STOP );
	}
	g_nTrlAudioPos = 0;
}

/** @brief EmuShell Audio Exit */
void trlEmuShellAudioExit()
{	
	trlEmuShellAudioStop();

	g_hTrlEmuMenu.Release();
	
	g_bTrlAudioThreadFlag = 0;
	g_hTrlAudioThread.Join();
    g_hTrlAudioThread.Finalize();	

	{
#if NW_SND_LOCK
		nw::snd::SoundSystem::SoundThreadScopedLock lock;
#endif
		nn::snd::FreeVoice(g_pTrlAudioVoice);
	}
	g_hTrlEmuMenu.ReleaseSound();
	g_hTrlEmuMenu.Release1();	
    nn::Result result = nn::snd::Finalize();
    NN_UTIL_PANIC_IF_FAILED(result);
    result = nn::dsp::UnloadComponent();
    NN_UTIL_PANIC_IF_FAILED(result);
    nn::dsp::Finalize();

	trlMemFreeDevice(g_sEmuShellBuffer.pSoundBuf);
}

/** @brief EmuShell Audio Record Main */
void trlEmuShellAudioRecordMain(u8* pBuf, u32 nSize)
{	
	if(g_bTrlAudioRecord == 1)	
		trlFileAppend("sdmc:/record.raw", pBuf, nSize);			
}

/** @brief EmuShell Audio Record Update */
void trlEmuShellAudioRecordUpdate()
{	
	g_bTrlAudioRecord = !g_bTrlAudioRecord;	
}
