/**
 * @file trlEmuShellVideo.h
 * @author Chentian
 * @date 2009.11.24
 * @brief TRL Emulate - EmuShell Video Module
 */
#pragma once
#include "..\trlHeader.h"

/** @brief EmuShell Video Init */
void trlEmuShellVideoInit(u32 nPara);
/** @brief Start */
void trlEmuShellVideoStart();
/** @brief Render Frame */
void trlEmuShellVideoFrame();
/** @brief Render Frame Menu */
void trlEmuShellVideoFrameMenu();
/** @brief Swap Buffer */
void trlEmuShellVideoSwapBuffer(const s32 display, const bool isWaitVSync);
/** @brief Frame Blend */
void trlEmuShellVideoFrameBlend();
/** @brief Draw Debug Info */
void trlEmuShellVideoDrawDebugInfo(u32 nLine, const char *szFormat, ...);
/** @brief Draw Debug Warn */
void trlEmuShellVideoDrawDebugWarn(u32 nLine, const char *szFormat, ...);
/** @brief Draw Text */
void trlEmuShellVideoDrawText(u32 nColor, u32 nX, u32 nY, const char *szFormat, ...);
/** @brief Clear */
void trlEmuShellVideoClear();
/** @brief Capture Current Frame */
void trlEmuShellVideoCapture();
/** @brief Change Mask Mode */
void trlEmuShellVideoMaskChangeMode(u32 nMode);
/** @brief Change Motion Blur */
void trlEmuShellVideoMotionBlur();
/** @brief Change Mask Mode */
void trlEmuShellVideoMaskMode(u32 nDark = 0, f32 nDarkRate = 0.0f);
/** @brief Change Texture Filter Mode */
void trlEmuShellVideoFilterMode(u32 nMode);
/** @brief Exit */
void trlEmuShellVideoExit();
