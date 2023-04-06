/**
 * @file NESROMCombineDlg.h
 * @author Chentian
 * @date 2010.07.06
 * @brief NESROMCombineDlg
 */
#pragma once
#include "CStaticEx.h"


// CNESROMCombineDlg 对话框
class CNESROMCombineDlg : public CDialog
{
// 构造
public:
	CNESROMCombineDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NESROMCOMBINE_DIALOG };

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonPrgrom();
	afx_msg void OnBnClickedButtonChrrom();
	afx_msg void OnBnClickedButtonMake();
	afx_msg void OnTcnSelchangeTabType(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabMode(NMHDR *pNMHDR, LRESULT *pResult);
	LRESULT OnStaticDrapFile(WPARAM wParam, LPARAM lParam);
	void AnalyseFile(UINT nID);
	void AnalyseiNESFile();
	void AnalyseQDFile(UINT nID);
	void AnalyseFDSFile();
	void AnalyseTrlFile();
	UINT GetFDSInfo(BYTE* pROM, UINT nSize, UINT nID);
	void ResetControl();
	void ResetControlFDS();

// 实现
protected:
	HICON m_hIcon;
	CStaticEx m_hStaticPRGROM;
	CStaticEx m_hStaticCHRROM;
	CComboBox m_hComboCardType;
	CComboBox m_hComboMapMode;
	CTabCtrl m_hTabCntType;
	CTabCtrl m_hTabCntMode;
	CButton	m_hButtonBattery;
};
