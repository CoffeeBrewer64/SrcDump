
// TGAConvert.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTGAConvertApp:
// �йش����ʵ�֣������ TGAConvert.cpp
//

class CTGAConvertApp : public CWinAppEx
{
public:
	CTGAConvertApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTGAConvertApp theApp;