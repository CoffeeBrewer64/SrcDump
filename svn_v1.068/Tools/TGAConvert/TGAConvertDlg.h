
// TGAConvertDlg.h : ͷ�ļ�
//

#pragma once


// CTGAConvertDlg �Ի���
class CTGAConvertDlg : public CDialog
{
// ����
public:
	CTGAConvertDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TGACONVERT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void Convert(const CString &csFilename);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
