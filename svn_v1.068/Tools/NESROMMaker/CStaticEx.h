/**
 * @file CStaticEx.h
 * @author Chentian
 * @date 2010.07.06
 * @brief 扩展静态控件
 */
#pragma once
#include "afxcmn.h"

/**
 * @class CListCtrlEx
 * @brief 扩展列表控件
 */
class CStaticEx :public CStatic
{
	DECLARE_DYNAMIC(CStaticEx)
// 函数
public:
	/** @name 构造和析构 */
	//@{
	CStaticEx(void);
	~CStaticEx(void);
	//@}
	/** @brief 拖放文件处理 */
	afx_msg void OnDropFiles(HDROP hDropInfo);
protected:
	DECLARE_MESSAGE_MAP()

// 变量
public:
};
