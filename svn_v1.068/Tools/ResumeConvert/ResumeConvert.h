
// ResumeConvert.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CResumeConvertApp:
// �йش����ʵ�֣������ ResumeConvert.cpp
//

class CResumeConvertApp : public CWinAppEx
{
public:
	CResumeConvertApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CResumeConvertApp theApp;