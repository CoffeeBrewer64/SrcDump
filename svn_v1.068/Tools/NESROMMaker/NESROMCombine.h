/**
 * @file NESROMCombine.h
 * @author Chentian
 * @date 2010.07.06
 * @brief PROJECT_NAME 应用程序的主头文件
 */
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CNESROMCombineApp:
// 有关此类的实现，请参阅 NESROMCombine.cpp
//

class CNESROMCombineApp : public CWinAppEx
{
public:
	CNESROMCombineApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CNESROMCombineApp theApp;