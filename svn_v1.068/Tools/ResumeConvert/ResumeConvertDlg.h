
// ResumeConvertDlg.h : 头文件
//

#pragma once


// CResumeConvertDlg 对话框
class CResumeConvertDlg : public CDialog
{
// 构造
public:
	CResumeConvertDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RESUMECONVERT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_hComboMode;
	CComboBox m_hComboInit;
	afx_msg void OnBnClickedButtonApply();
	CString m_szFilename;
	void Reset();
	bool Analyse();
	afx_msg void OnCbnSelchangeComboMode();
	afx_msg void OnBnClickedCheckEnable();
	afx_msg void OnCbnSelchangeComboInit();
};
