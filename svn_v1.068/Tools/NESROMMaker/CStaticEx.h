/**
 * @file CStaticEx.h
 * @author Chentian
 * @date 2010.07.06
 * @brief ��չ��̬�ؼ�
 */
#pragma once
#include "afxcmn.h"

/**
 * @class CListCtrlEx
 * @brief ��չ�б�ؼ�
 */
class CStaticEx :public CStatic
{
	DECLARE_DYNAMIC(CStaticEx)
// ����
public:
	/** @name ��������� */
	//@{
	CStaticEx(void);
	~CStaticEx(void);
	//@}
	/** @brief �Ϸ��ļ����� */
	afx_msg void OnDropFiles(HDROP hDropInfo);
protected:
	DECLARE_MESSAGE_MAP()

// ����
public:
};
