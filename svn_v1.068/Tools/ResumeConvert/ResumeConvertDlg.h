
// ResumeConvertDlg.h : ͷ�ļ�
//

#pragma once


// CResumeConvertDlg �Ի���
class CResumeConvertDlg : public CDialog
{
// ����
public:
	CResumeConvertDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RESUMECONVERT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
