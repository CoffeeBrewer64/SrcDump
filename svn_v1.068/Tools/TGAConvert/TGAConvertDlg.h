
// TGAConvertDlg.h : 头文件
//

#pragma once


// CTGAConvertDlg 对话框
class CTGAConvertDlg : public CDialog
{
// 构造
public:
	CTGAConvertDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TGACONVERT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void Convert(const CString &csFilename);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
