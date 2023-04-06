
// ResumeConvertDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ResumeConvert.h"
#include "ResumeConvertDlg.h"
#include "..\..\src\EmuShell\trlEmuShellStruct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TRL_DATA_RESUME_BACKUP		0
#define TRL_DATA_RESUME_SUSPEND		1
#define TRL_DATA_RESUME_HOME		1
#define TRL_DATA_RESUME_SLEEP		2

static const u32	g_szEmuShellResumeFlag			= 0x53524354;		///< TRL Resume File Header Flag - "TCRS"


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CResumeConvertDlg �Ի���




CResumeConvertDlg::CResumeConvertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResumeConvertDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CResumeConvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODE, m_hComboMode);
	DDX_Control(pDX, IDC_COMBO_INIT, m_hComboInit);
}

BEGIN_MESSAGE_MAP(CResumeConvertDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CResumeConvertDlg::OnBnClickedButtonApply)
	ON_CBN_SELCHANGE(IDC_COMBO_MODE, &CResumeConvertDlg::OnCbnSelchangeComboMode)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, &CResumeConvertDlg::OnBnClickedCheckEnable)
	ON_CBN_SELCHANGE(IDC_COMBO_INIT, &CResumeConvertDlg::OnCbnSelchangeComboInit)
END_MESSAGE_MAP()


// CResumeConvertDlg ��Ϣ�������

BOOL CResumeConvertDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_hComboMode.AddString(L"Backup");
	m_hComboMode.AddString(L"Suspend");

	m_hComboInit.AddString(L"Normal");
	m_hComboInit.AddString(L"Advance");
	m_hComboInit.AddString(L"Initial");

	Reset();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CResumeConvertDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CResumeConvertDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CResumeConvertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CResumeConvertDlg::OnDropFiles(HDROP hDropInfo)
{
	WCHAR szFilename[MAX_PATH] = {0};
	DragQueryFile(hDropInfo, 0, szFilename, MAX_PATH);
	m_szFilename = szFilename;
	GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(0);
	if(!Analyse())
		Reset();
	CDialog::OnDropFiles(hDropInfo);
}

void CResumeConvertDlg::OnBnClickedButtonApply()
{
	CFile hFile;
	if(!hFile.Open(m_szFilename, CFile::modeRead|CFile::typeBinary))
	{
		MessageBox(L"File can't open.", L"Error", MB_OK|MB_ICONERROR);
		return;
	}
	long nSize = (long)hFile.GetLength();
	BYTE* pBuf = new BYTE[nSize];
	UINT nRead = hFile.Read(pBuf, nSize);
	hFile.Close();
	if(nRead!=nSize)
	{
		MessageBox(L"File read error.", L"Error", MB_OK|MB_ICONERROR);
		delete []pBuf;
		return;
	}

	trlSEmuShellResumeHeader* pResumeHeader = (trlSEmuShellResumeHeader*)(pBuf + sizeof(trlSEmuShellFileHeader));

	pResumeHeader->nType = m_hComboMode.GetCurSel();
	pResumeHeader->nEnable = ((CButton*)GetDlgItem(IDC_CHECK_ENABLE))->GetCheck();
	pResumeHeader->nVCMMode = m_hComboInit.GetCurSel();

	if(!hFile.Open(m_szFilename, CFile::modeWrite|CFile::modeCreate|CFile::typeBinary))
	{
		MessageBox(L"File can't open.", L"Error", MB_OK|MB_ICONERROR);
		delete []pBuf;
		return;
	}
	hFile.Write(pBuf, nSize);
	hFile.Close();
	delete []pBuf;
	GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(0);
	MessageBox(L"Finished.", L"OK", MB_OK|MB_ICONINFORMATION);
}

void CResumeConvertDlg::Reset()
{
	m_szFilename = "";
	SetDlgItemText(IDC_EDIT_VER, L"");
	SetDlgItemText(IDC_EDIT_TYPE, L"");
	SetDlgItemText(IDC_EDIT_SIZE, L"");
	GetDlgItem(IDC_EDIT_VER)->EnableWindow(0);
	GetDlgItem(IDC_EDIT_TYPE)->EnableWindow(0);
	GetDlgItem(IDC_EDIT_SIZE)->EnableWindow(0);
	GetDlgItem(IDC_COMBO_MODE)->EnableWindow(0);
	GetDlgItem(IDC_CHECK_ENABLE)->EnableWindow(0);
	GetDlgItem(IDC_COMBO_INIT)->EnableWindow(0);
	GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(0);
}

bool CResumeConvertDlg::Analyse()
{
	CFile hFile;
	if(!hFile.Open(m_szFilename, CFile::modeRead|CFile::typeBinary))
	{
		MessageBox(L"File can't open.", L"Error", MB_OK|MB_ICONERROR);
		return 0;
	}
	long nSize = (long)hFile.GetLength();
	BYTE* pBuf = new BYTE[nSize];
	UINT nRead = hFile.Read(pBuf, nSize);
	hFile.Close();
	if(nRead!=nSize)
	{
		MessageBox(L"File read error.", L"Error", MB_OK|MB_ICONERROR);
		delete []pBuf;
		return 0;
	}

	// Read Header
	trlSEmuShellFileHeader* pHeader = (trlSEmuShellFileHeader*)pBuf;
	if(pHeader->nFlag != g_szEmuShellResumeFlag)
	{
		MessageBox(L"This file isn't the TRL Resume file.", L"Error", MB_OK|MB_ICONERROR);
		delete []pBuf;
		return 0;
	}
	GetDlgItem(IDC_EDIT_VER)->EnableWindow(1);
	GetDlgItem(IDC_EDIT_TYPE)->EnableWindow(1);
	GetDlgItem(IDC_EDIT_SIZE)->EnableWindow(1);

	SetDlgItemInt(IDC_EDIT_VER, pHeader->nVer);
	SetDlgItemInt(IDC_EDIT_SIZE, pHeader->nSize);

	CString szFilename = m_szFilename.Right(m_szFilename.GetLength()-m_szFilename.ReverseFind(_T('\\'))-1);
	switch(pHeader->nType)
	{
	case 0:
		if(!szFilename.Left(3).CompareNoCase(L"DMG") || !szFilename.Left(3).CompareNoCase(L"CGB"))
		{
			pHeader->nType = 1;
			SetDlgItemText(IDC_EDIT_TYPE, L"DMG & CGB");
		}
		else// if(!szFilename.Left(3).CompareNoCase(L"HVC"))
		{
			pHeader->nType = 3;
			SetDlgItemText(IDC_EDIT_TYPE, L"HVC");
		}
		break;
	case 1:
		SetDlgItemText(IDC_EDIT_TYPE, L"DMG & CGB");
		break;
	case 2:
		SetDlgItemText(IDC_EDIT_TYPE, L"AGB");
		break;
	case 3:
		SetDlgItemText(IDC_EDIT_TYPE, L"HVC");
		break;
	}


	if(pHeader->nVer <= 11 && pHeader->nType == 1)
	{
		GetDlgItem(IDC_COMBO_MODE)->EnableWindow(0);
		GetDlgItem(IDC_CHECK_ENABLE)->EnableWindow(0);
		GetDlgItem(IDC_COMBO_INIT)->EnableWindow(0);
	}
	else
	{
		trlSEmuShellResumeHeader* pResumeHeader = (trlSEmuShellResumeHeader*)(pBuf + sizeof(trlSEmuShellFileHeader));
		GetDlgItem(IDC_COMBO_MODE)->EnableWindow(1);
		// Check Type
		switch(pResumeHeader->nType)
		{
		case TRL_DATA_RESUME_BACKUP:
			m_hComboMode.SetCurSel(0);
			GetDlgItem(IDC_CHECK_ENABLE)->EnableWindow(0);
			GetDlgItem(IDC_COMBO_INIT)->EnableWindow(0);
			break;
		case TRL_DATA_RESUME_SUSPEND:
		case TRL_DATA_RESUME_SLEEP:
			m_hComboMode.SetCurSel(1);
			GetDlgItem(IDC_CHECK_ENABLE)->EnableWindow(1);
			GetDlgItem(IDC_COMBO_INIT)->EnableWindow(1);
			break;
		}

		((CButton*)GetDlgItem(IDC_COMBO_MODE))->SetCheck(pResumeHeader->nType);
		((CButton*)GetDlgItem(IDC_CHECK_ENABLE))->SetCheck(pResumeHeader->nEnable);
		m_hComboInit.SetCurSel(pResumeHeader->nVCMMode);
	}

	delete []pBuf;
	return 1;
}

void CResumeConvertDlg::OnCbnSelchangeComboMode()
{
	switch(m_hComboMode.GetCurSel())
	{
	case 0:
		GetDlgItem(IDC_CHECK_ENABLE)->EnableWindow(0);
		GetDlgItem(IDC_COMBO_INIT)->EnableWindow(0);
		break;
	case 1:
		GetDlgItem(IDC_CHECK_ENABLE)->EnableWindow(1);
		GetDlgItem(IDC_COMBO_INIT)->EnableWindow(1);
		break;
	}
	GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(1);
}

void CResumeConvertDlg::OnBnClickedCheckEnable()
{
	GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(1);
}

void CResumeConvertDlg::OnCbnSelchangeComboInit()
{
	GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(1);
}
