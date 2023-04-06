/**
 * @file CStaticEx.cpp
 * @author Chentian
 * @date 2010.07.06
 * @brief 扩展静态控件
 */
#include "StdAfx.h"
#include ".\CStaticEx.h"

IMPLEMENT_DYNAMIC(CStaticEx, CStatic)
/** @name 构造和析构 */
//@{
CStaticEx::CStaticEx(void)
{
}

CStaticEx::~CStaticEx(void)
{
}
//@}

BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

void CStaticEx::OnDropFiles(HDROP hDropInfo)
{
	UINT nSize = DragQueryFile(hDropInfo, 0, NULL, 0) + 1;
	if(nSize>1)
	{
		wchar_t* pFile = new wchar_t[nSize];
		ZeroMemory(pFile, nSize*sizeof(wchar_t));
		DragQueryFile(hDropInfo, 0, pFile, nSize);
		SetWindowText(pFile);
		delete[] pFile;
		GetParent()->SendMessage(WM_STATIC_DROPFILE, GetDlgCtrlID());
	}
	CStatic::OnDropFiles(hDropInfo);
}
