/**
 * @file NESROMCombine.h
 * @author Chentian
 * @date 2010.07.06
 * @brief PROJECT_NAME Ӧ�ó������ͷ�ļ�
 */
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNESROMCombineApp:
// �йش����ʵ�֣������ NESROMCombine.cpp
//

class CNESROMCombineApp : public CWinAppEx
{
public:
	CNESROMCombineApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNESROMCombineApp theApp;