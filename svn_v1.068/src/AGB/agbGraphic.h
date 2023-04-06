/**
 * @file agbGraphic.h
 * @author Chentian
 * @date 2009.11.24
 * @brief AGB Emulate For CTR - Graphic
 */
#pragma once
#include "agbDataStruct.h"

/** @name Macro Define */
//@{
//@}

/** @name Global Variable */
//@{
extern s32				g_nAgbGrpBGCrdFlag[2];			///< BG Coordinate Register Change Flag
extern s32				g_nAgbGrpOBJLayerChange;		///< OBJ Layer Change Flag
extern s32				g_nAgbGrpBGLayerChange;			///< BG Layer Change Flag
extern s32				g_nAgbGrpWinEnable;				///< Window Enable Flag
extern s32				g_nAgbGrpEVA;					///< Color Special Effect Value: EVA
extern s32				g_nAgbGrpEVB;					///< Color Special Effect Value: EVB
extern s32				g_nAgbGrpEVY;					///< Color Special Effect Value: EVY
extern agbSGrpBGRSData	g_sAgbGrpBGRSData[2];			///< BG Rotation and Scaling Parameter
//@}

/** @brief Initialize Graphic */
void agbGrpInit();
/** @brief Reset Graphic */
void agbGrpReset();
/** @brief Update Ticks */
void agbGrpUpdateTicks(u32 nTicks);
/** @brief Update BG Screen Data Map */
void agbGrpUpdateBGScreenMap(u32 nAddr, u32 nCount);
