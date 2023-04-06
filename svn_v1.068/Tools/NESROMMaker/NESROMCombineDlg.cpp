/**
 * @file NESROMCombineDlg.cpp
 * @author Chentian
 * @date 2010.07.06
 * @brief NESROMCombineDlg
 */
#include "stdafx.h"
#include "NESROMCombine.h"
#include "NESROMCombineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const BYTE g_nNesCartMapper[256] = {			// TRL - iNes Mapper 对应表
//    0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	  0,   1,   6,   7,   3,   5, 255,   9, 255,   2,   4, 255, 255, 255, 255, 255,	// 00
	255, 255,  32,  36, 100,  20,  17,  18,  25,  21,  26, 255, 255, 255, 255, 255,	// 10
	 49,  40, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 20
	 42, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 30
	255,  50,   8,  12,  13,  14,  15, 255,  29,  19, 255,  16,  37,  45,  47, 255,	// 40
	 43, 255,  44, 255, 255,  27,  31,  28,  38,  11, 255, 255,  30,  33,  34,  35,	// 50
	255,  46, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 60
	255, 255, 255, 255, 255, 255,  39, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 70
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// 80
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 90
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// A0
	255, 255, 255, 255, 255, 255, 255, 255,  10,  51, 255, 255, 255, 255, 255, 255,	// B0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// C0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// D0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// E0
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,	// F0
};

static const BYTE g_nNesCartFDSID[15] = {			// TRL - FDS Header ID
	0x01, 0x2A, 0x4E, 0x49, 0x4E, 0x54, 0x45, 0x4E, 
	0x44, 0x4F, 0x2D, 0x48, 0x56, 0x43, 0x2A
};

/**
 * @class nesSFDSROMInfo
 * @brief The Disk System
 */
struct nesSFDSROMInfo
{
	UINT		nID;
	UINT		nAddr;
	UINT		nSize;
	UINT		nDisk;
	UINT		nSide;
}g_sFDSROMInfo[4];

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CNESROMCombineDlg 对话框

CNESROMCombineDlg::CNESROMCombineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNESROMCombineDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNESROMCombineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PRGROM, m_hStaticPRGROM);
	DDX_Control(pDX, IDC_STATIC_CHRROM, m_hStaticCHRROM);
	DDX_Control(pDX, IDC_COMBO_CARDTYPE, m_hComboCardType);
	DDX_Control(pDX, IDC_COMBO_MAPMODE, m_hComboMapMode);
	DDX_Control(pDX, IDC_TAB_TYPE, m_hTabCntType);
	DDX_Control(pDX, IDC_TAB_MODE, m_hTabCntMode);
	DDX_Control(pDX, IDC_CHECK_BATTERY, m_hButtonBattery);
}

BEGIN_MESSAGE_MAP(CNESROMCombineDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_PRGROM, &CNESROMCombineDlg::OnBnClickedButtonPrgrom)
	ON_BN_CLICKED(IDC_BUTTON_CHRROM, &CNESROMCombineDlg::OnBnClickedButtonChrrom)
	ON_BN_CLICKED(IDC_BUTTON_MAKE, &CNESROMCombineDlg::OnBnClickedButtonMake)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_TYPE, &CNESROMCombineDlg::OnTcnSelchangeTabType)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MODE, &CNESROMCombineDlg::OnTcnSelchangeTabMode)
	ON_MESSAGE(WM_STATIC_DROPFILE, OnStaticDrapFile)
END_MESSAGE_MAP()


// CNESROMCombineDlg 消息处理程序

BOOL CNESROMCombineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	SetDlgItemInt(IDC_EDIT_PRGROMBANK, 0);
	SetDlgItemInt(IDC_EDIT_CHRROMBANK, 0);
	SetDlgItemInt(IDC_EDIT_SRAMBANK, 0);

	m_hComboCardType.AddString(L"No Mapper");
	m_hComboCardType.AddString(L"MMC-1");
	m_hComboCardType.AddString(L"MMC-2");
	m_hComboCardType.AddString(L"MMC-3");
	m_hComboCardType.AddString(L"MMC-4");
	m_hComboCardType.AddString(L"MMC-5");
	m_hComboCardType.AddString(L"UNROM");
	m_hComboCardType.AddString(L"CNROM");
	m_hComboCardType.AddString(L"GNROM");
	m_hComboCardType.AddString(L"Rare");
	m_hComboCardType.AddString(L"Sunsoft-1");
	m_hComboCardType.AddString(L"Sunsoft-2");
	m_hComboCardType.AddString(L"Sunsoft-3");
	m_hComboCardType.AddString(L"Sunsoft-4");
	m_hComboCardType.AddString(L"Sunsoft-5");
	m_hComboCardType.AddString(L"Bandai");
	m_hComboCardType.AddString(L"Konami-VRC1");
	m_hComboCardType.AddString(L"Konami-VRC2A");
	m_hComboCardType.AddString(L"Konami-VRC2B");
	m_hComboCardType.AddString(L"Konami-VRC3");
	m_hComboCardType.AddString(L"Konami-VRC4A");
	m_hComboCardType.AddString(L"Konami-VRC4B");
	m_hComboCardType.AddString(L"Konami-VRC4C");
	m_hComboCardType.AddString(L"Konami-VRC4D");
	m_hComboCardType.AddString(L"Konami-VRC4E");
	m_hComboCardType.AddString(L"Konami-VRC6A");
	m_hComboCardType.AddString(L"Konami-VRC6B");
	m_hComboCardType.AddString(L"Konami-VRC7");
	m_hComboCardType.AddString(L"Jaleco-1");
	m_hComboCardType.AddString(L"Jaleco-2");
	m_hComboCardType.AddString(L"Jaleco-3");
	m_hComboCardType.AddString(L"Jaleco-4");
	m_hComboCardType.AddString(L"Jaleco-SS8806");
	m_hComboCardType.AddString(L"74161A");
	m_hComboCardType.AddString(L"74161B");
	m_hComboCardType.AddString(L"Namcot");
	m_hComboCardType.AddString(L"Namcot-106");
	m_hComboCardType.AddString(L"Namco-109");
	m_hComboCardType.AddString(L"Namco-118");
	m_hComboCardType.AddString(L"MMC-3+TLS");
	m_hComboCardType.AddString(L"Taito-TC0190");
	m_hComboCardType.AddString(L"Taito-TC0350");
	m_hComboCardType.AddString(L"Taito-TC190V");
	m_hComboCardType.AddString(L"Taito-X-005");
	m_hComboCardType.AddString(L"Taito-X1-17");
	m_hComboCardType.AddString(L"Irem-1");
	m_hComboCardType.AddString(L"Irem-2");
	m_hComboCardType.AddString(L"Irem-74HC161");
	m_hComboCardType.AddString(L"Irem-74HC32");
	m_hComboCardType.AddString(L"Irem-G-101");
	m_hComboCardType.AddString(L"Irem-H-3001");
	m_hComboCardType.AddString(L"VROM-disable");
	m_hComboCardType.SetCurSel(0);

	m_hComboMapMode.AddString(L"Auto");
	m_hComboMapMode.AddString(L"Vertical Scroll");
	m_hComboMapMode.AddString(L"Horizontal Scroll");
	m_hComboMapMode.AddString(L"Single Screen 0");
	m_hComboMapMode.AddString(L"Single Screen 1");
	m_hComboMapMode.AddString(L"Extend");
	m_hComboMapMode.SetCurSel(0);

	m_hTabCntMode.InsertItem(0, L"Combine");
	m_hTabCntMode.InsertItem(1, L"Convert");
	m_hTabCntMode.InsertItem(2, L"Modify");

	m_hTabCntType.InsertItem(0, L"Cartridge");
	m_hTabCntType.InsertItem(1, L"Disk System");

	m_hButtonBattery.SetCheck(BST_UNCHECKED);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNESROMCombineDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNESROMCombineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNESROMCombineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNESROMCombineDlg::ResetControl()
{
	m_hComboCardType.SetCurSel(0);
	m_hComboMapMode.SetCurSel(0);
	SetDlgItemInt(IDC_EDIT_PRGROMBANK, 0);
	SetDlgItemInt(IDC_EDIT_CHRROMBANK, 0);
	SetDlgItemInt(IDC_EDIT_SRAMBANK, 0);
	m_hButtonBattery.SetCheck(BST_UNCHECKED);
	ZeroMemory(g_sFDSROMInfo, sizeof(nesSFDSROMInfo)*4);
}

void CNESROMCombineDlg::OnBnClickedButtonPrgrom()
{
	switch(m_hTabCntType.GetCurSel())
	{
	case 0:		// Cartridge
		switch(m_hTabCntMode.GetCurSel())
		{
		case 0:		// Combine
			{
				CFileDialog dlg(TRUE, _T(""), _T("*.*"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("PRG-ROM Files(*.*)|*.*||"));
				dlg.m_pOFN->lpstrTitle = _T("Open PRG-ROM File");
				if(dlg.DoModal()==IDOK)
				{
					m_hStaticPRGROM.SetWindowText(dlg.GetPathName());
					AnalyseFile(IDC_STATIC_PRGROM);
				}
			}
			break;
		case 1:		// Convert
			{
				CFileDialog dlg(TRUE, _T(""), _T("*.nes"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("iNES ROM Files(*.nes)|*.nes||"));
				dlg.m_pOFN->lpstrTitle = _T("Open iNES ROM File");
				if(dlg.DoModal()==IDOK)
				{
					m_hStaticPRGROM.SetWindowText(dlg.GetPathName());
					AnalyseiNESFile();
				}
			}
			break;
		case 2:		// Modify
			{
				CFileDialog dlg(TRUE, _T(""), _T("*.*"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Trl ROM Files(*.*)|*.*||"));
				dlg.m_pOFN->lpstrTitle = _T("Open Trl ROM File");
				if(dlg.DoModal()==IDOK)
				{
					m_hStaticPRGROM.SetWindowText(dlg.GetPathName());
					AnalyseTrlFile();
				}
			}
			break;
		}
		break;
	case 1:		// Disk System
		switch(m_hTabCntMode.GetCurSel())
		{
		case 0:		// Combine
			{
				CFileDialog dlg(TRUE, _T(""), _T("*.qd"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("FDS ROM Files(*.qd)|*.qd||"));
				dlg.m_pOFN->lpstrTitle = _T("Open QD ROM File");
				if(dlg.DoModal()==IDOK)
				{
					m_hStaticPRGROM.SetWindowText(dlg.GetPathName());
					AnalyseQDFile(IDC_STATIC_PRGROM);
				}
			}
			break;
		case 1:		// Convert
			{
				CFileDialog dlg(TRUE, _T(""), _T("*.fds"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("iNES ROM Files(*.fds)|*.nes||"));
				dlg.m_pOFN->lpstrTitle = _T("Open FDS ROM File");
				if(dlg.DoModal()==IDOK)
				{
					m_hStaticPRGROM.SetWindowText(dlg.GetPathName());
					AnalyseFDSFile();
				}
			}
			break;
		}
		break;
	}
}

void CNESROMCombineDlg::OnBnClickedButtonChrrom()
{
	switch(m_hTabCntType.GetCurSel())
	{
	case 0:		// Cartridge
		switch(m_hTabCntMode.GetCurSel())
		{
		case 0:		// Combine
			{
				CFileDialog dlg(TRUE, _T(""), _T("*.*"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("CHR-ROM Files(*.*)|*.*||"));
				dlg.m_pOFN->lpstrTitle = _T("Open CHR-ROM File");
				if(dlg.DoModal()==IDOK)
				{
					m_hStaticCHRROM.SetWindowText(dlg.GetPathName());
					AnalyseFile(IDC_STATIC_CHRROM);
				}
			}
			break;
		}
		break;
	case 1:		// Disk System
		switch(m_hTabCntMode.GetCurSel())
		{
		case 0:		// Combine
			{
				CFileDialog dlg(TRUE, _T(""), _T("*.qd"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("FDS ROM Files(*.qd)|*.qd||"));
				dlg.m_pOFN->lpstrTitle = _T("Open QD ROM File");
				if(dlg.DoModal()==IDOK)
				{
					m_hStaticCHRROM.SetWindowText(dlg.GetPathName());
					AnalyseQDFile(IDC_STATIC_CHRROM);
				}
			}
			break;
		}
		break;
	}
}

LRESULT CNESROMCombineDlg::OnStaticDrapFile(WPARAM wParam, LPARAM lParam)
{
	switch(m_hTabCntType.GetCurSel())
	{
	case 0:		// Cartridge
		switch(m_hTabCntMode.GetCurSel())
		{
		case 0:		// Combine
			AnalyseFile(wParam);
			break;
		case 1:		// Convert
			AnalyseiNESFile();
			break;
		case 2:		// Modify
			AnalyseTrlFile();
			break;
		}
		break;
	case 1:		// Disk System
		switch(m_hTabCntMode.GetCurSel())
		{
		case 0:		// Combine
			AnalyseQDFile(wParam);
			break;
		case 1:		// Convert
			AnalyseFDSFile();
			break;
		}
		break;
	}
	return 0;
}

void CNESROMCombineDlg::AnalyseFile(UINT nID)
{
	CString szFile;
	CFile hFile;
	CStaticEx* pStatic0;
	CStaticEx* pStatic1;
	UINT nSizeID0, nSizeID1;
	wchar_t wzGetAt, wzSetAt;
	if(nID == IDC_STATIC_PRGROM)
	{
		pStatic0 = &m_hStaticPRGROM;
		pStatic1 = &m_hStaticCHRROM;
		nSizeID0 = IDC_EDIT_PRGROMBANK;
		nSizeID1 = IDC_EDIT_CHRROMBANK;
		wzGetAt = 'P';
		wzSetAt = 'C';
	}
	else
	{
		pStatic0 = &m_hStaticCHRROM;
		pStatic1 = &m_hStaticPRGROM;
		nSizeID0 = IDC_EDIT_CHRROMBANK;
		nSizeID1 = IDC_EDIT_PRGROMBANK;
		wzGetAt = 'C';
		wzSetAt = 'P';
	}

	pStatic0->GetWindowText(szFile);
	if(!hFile.Open(szFile, CFile::modeRead|CFile::typeBinary))
	{
		MessageBox(L"File can't open.", L"Error", MB_OK|MB_ICONERROR);
		pStatic0->SetWindowText(L"");
		ResetControl();
		return;
	}
	SetDlgItemInt(nSizeID0, (UINT)(hFile.GetLength()/0x2000));
	hFile.Close();

	CString szStatic;
	pStatic1->GetWindowText(szStatic);
	if(!szStatic.IsEmpty())
		return;

	int nPos = szFile.ReverseFind('.');
	if(nPos==-1)
	{
		pStatic1->SetWindowText(L"");
		return;
	}
	wchar_t szText = szFile.GetAt(nPos-1);
	if(szText != wzGetAt)
	{
		pStatic1->SetWindowText(L"");
		return;
	}
	szFile.SetAt(nPos-1, wzSetAt);

	if(hFile.Open(szFile, CFile::modeRead|CFile::typeBinary))
	{
		pStatic1->SetWindowText(szFile);
		SetDlgItemInt(nSizeID1, (UINT)(hFile.GetLength()/0x2000));
		hFile.Close();
		return;
	}
}

/**
 * @class nesSINESROMHeader
 * @brief The iNES Cartridge Header
 */
struct nesSINESROMHeader
{
	DWORD	nFlag;						///< Flag 'NES',1Ah
	BYTE	nPRGBanks;					///< Number of 16K PRG-ROM Banks
	BYTE	nCHRBanks;					///< Number of 8K CHR-ROM Banks
	BYTE	nType0;						///< Cartridge Type LSB
	BYTE	nType1;						///< Cartridge Type MSB
	BYTE	nSRAMBanks;					///< Number of 8K SRAM Banks
	BYTE	nPadding0;
	WORD	nPadding1;
	DWORD	nPadding2;
};

void CNESROMCombineDlg::AnalyseiNESFile()
{
	CString wzFile;
	m_hStaticPRGROM.GetWindowText(wzFile);
	CFile hFile;
	if(!hFile.Open(wzFile, CFile::modeRead|CFile::typeBinary))
	{
		MessageBox(L"File can't open.", L"Error", MB_OK|MB_ICONERROR);
		m_hStaticPRGROM.SetWindowText(L"");
		ResetControl();
		return;
	}
	nesSINESROMHeader sHeader;
	hFile.Read(&sHeader, sizeof(nesSINESROMHeader));
	hFile.Close();
	if(sHeader.nFlag != 0x1A53454E)
	{
		MessageBox(L"This File is't the iNes Rom.", L"Error", MB_OK|MB_ICONERROR);
		m_hStaticPRGROM.SetWindowText(L"");
		ResetControl();
		return;
	}

	int nCartType = g_nNesCartMapper[((sHeader.nType0>>4)&0x0F) | (sHeader.nType1&0xF0)];
	if(nCartType >= m_hComboCardType.GetCount())
	{
		CString csMessage;
		csMessage.Format(L"This rom's mapper nonsupport now. (%d)", ((sHeader.nType0>>4)&0x0F) | (sHeader.nType1&0xF0));
		MessageBox(csMessage, L"Error", MB_OK|MB_ICONERROR);
		m_hStaticPRGROM.SetWindowText(L"");
		ResetControl();
		return;
	}

	if(sHeader.nType0&0x02)
	{
		if(sHeader.nSRAMBanks == 0)
			sHeader.nSRAMBanks = 1;
	}
	if(sHeader.nType0&0x08)
		m_hComboMapMode.SetCurSel(5);
	else if(sHeader.nType0&0x01)
		m_hComboMapMode.SetCurSel(2);
	else
		m_hComboMapMode.SetCurSel(1);

	SetDlgItemInt(IDC_EDIT_PRGROMBANK, sHeader.nPRGBanks*2);
	SetDlgItemInt(IDC_EDIT_CHRROMBANK, sHeader.nCHRBanks);
	SetDlgItemInt(IDC_EDIT_SRAMBANK, sHeader.nSRAMBanks);
	m_hComboCardType.SetCurSel(nCartType);
	m_hButtonBattery.SetCheck(sHeader.nType0&0x02);
}

void CNESROMCombineDlg::OnTcnSelchangeTabType(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch(m_hTabCntType.GetCurSel())
	{
	case 0:		// Cartridge
		m_hTabCntMode.InsertItem(2, L"Modify");
		m_hComboCardType.ShowWindow(SW_SHOW);
		m_hComboMapMode.ShowWindow(SW_SHOW);
		m_hButtonBattery.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CARDTYPETEXT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MAPMODETEXT)->ShowWindow(SW_SHOW);
		SetDlgItemText(IDC_STATIC_SRAMBANKTEXT, L"SRAM Bank:");
		SetDlgItemText(IDC_STATIC_PRGROMTEXT, L"PRG-ROM Bank:");
		SetDlgItemText(IDC_STATIC_CHRROMTEXT, L"CHR-ROM Bank:");
		((CEdit*)GetDlgItem(IDC_EDIT_SRAMBANK))->SetReadOnly(false);
		break;
	case 1:		// Disk System
		m_hTabCntMode.DeleteItem(2);
		m_hComboCardType.ShowWindow(SW_HIDE);
		m_hComboMapMode.ShowWindow(SW_HIDE);
		m_hButtonBattery.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CARDTYPETEXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MAPMODETEXT)->ShowWindow(SW_HIDE);
		SetDlgItemText(IDC_STATIC_SRAMBANKTEXT, L"Disks:");
		SetDlgItemText(IDC_STATIC_PRGROMTEXT, L"Disk A Sides:");
		SetDlgItemText(IDC_STATIC_CHRROMTEXT, L"Disk B Sides:");
		((CEdit*)GetDlgItem(IDC_EDIT_SRAMBANK))->SetReadOnly(true);
		break;
	}
	m_hTabCntMode.SetCurSel(0);
	OnTcnSelchangeTabMode(pNMHDR,pResult);
}

void CNESROMCombineDlg::OnTcnSelchangeTabMode(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch(m_hTabCntType.GetCurSel())
	{
	case 0:		// Cartridge
		switch(m_hTabCntMode.GetCurSel())
		{
		case 0:		// Combine
			GetDlgItem(IDC_BUTTON_CHRROM)->SetWindowPos(NULL, 0,0,0,0, SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_CHRROM)->SetWindowPos(NULL, 0,0,0,0, SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_CHRAREA)->SetWindowPos(NULL, 0,0,0,0, SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_PRGAREA)->SetWindowText(L"PRG-ROM");
			GetDlgItem(IDC_STATIC_CHRAREA)->SetWindowText(L"CHR-ROM");
			break;
		case 1:		// Convert
			GetDlgItem(IDC_BUTTON_CHRROM)->SetWindowPos(NULL, 0,0,0,0, SWP_HIDEWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_CHRROM)->SetWindowPos(NULL, 0,0,0,0, SWP_HIDEWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_CHRAREA)->SetWindowPos(NULL, 0,0,0,0, SWP_HIDEWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_PRGAREA)->SetWindowText(L"iNES ROM");
			break;
		case 2:		// Modify
			GetDlgItem(IDC_BUTTON_CHRROM)->SetWindowPos(NULL, 0,0,0,0, SWP_HIDEWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_CHRROM)->SetWindowPos(NULL, 0,0,0,0, SWP_HIDEWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_CHRAREA)->SetWindowPos(NULL, 0,0,0,0, SWP_HIDEWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_PRGAREA)->SetWindowText(L"TRL ROM");
			break;
		}
		break;
	case 1:		// Disk System
		switch(m_hTabCntMode.GetCurSel())
		{
		case 0:		// Combine
			GetDlgItem(IDC_BUTTON_CHRROM)->SetWindowPos(NULL, 0,0,0,0, SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_CHRROM)->SetWindowPos(NULL, 0,0,0,0, SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_CHRAREA)->SetWindowPos(NULL, 0,0,0,0, SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_PRGAREA)->SetWindowText(L"Disk A");
			GetDlgItem(IDC_STATIC_CHRAREA)->SetWindowText(L"Disk B");
			break;
		case 1:		// Convert
			GetDlgItem(IDC_BUTTON_CHRROM)->SetWindowPos(NULL, 0,0,0,0, SWP_HIDEWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_CHRROM)->SetWindowPos(NULL, 0,0,0,0, SWP_HIDEWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_CHRAREA)->SetWindowPos(NULL, 0,0,0,0, SWP_HIDEWINDOW|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			GetDlgItem(IDC_STATIC_PRGAREA)->SetWindowText(L"FDS ROM");
			break;
		}
		break;
	}

	m_hStaticPRGROM.SetWindowText(L"");
	m_hStaticCHRROM.SetWindowText(L"");
	ResetControl();
	*pResult = 0;
}

void CNESROMCombineDlg::ResetControlFDS()
{
	UINT nDisk = 0;
	CString wzFile;
	m_hStaticPRGROM.GetWindowText(wzFile);
	if(wzFile.IsEmpty())
	{
		SetDlgItemInt(IDC_EDIT_PRGROMBANK, 0);
		ZeroMemory(g_sFDSROMInfo, sizeof(nesSFDSROMInfo)*2);
	}
	else
		nDisk++;
	m_hStaticCHRROM.GetWindowText(wzFile);
	if(wzFile.IsEmpty())
	{
		SetDlgItemInt(IDC_EDIT_CHRROMBANK, 0);
		ZeroMemory(&g_sFDSROMInfo[2], sizeof(nesSFDSROMInfo)*2);
	}
	else
		nDisk++;
	SetDlgItemInt(IDC_EDIT_SRAMBANK, nDisk);
}

void CNESROMCombineDlg::AnalyseQDFile(UINT nID)
{
	CStaticEx* pStatic;
	nesSFDSROMInfo* pFDSROMInfo;
	UINT nEditID;
	switch(nID)
	{
	case IDC_STATIC_PRGROM:
		pStatic = &m_hStaticPRGROM;
		pFDSROMInfo = g_sFDSROMInfo;
		nEditID = IDC_EDIT_PRGROMBANK;
		break;
	case IDC_STATIC_CHRROM:
		pStatic = &m_hStaticCHRROM;
		pFDSROMInfo = &g_sFDSROMInfo[2];
		nEditID = IDC_EDIT_CHRROMBANK;
		break;
	}
	ZeroMemory(pFDSROMInfo, sizeof(nesSFDSROMInfo)*2);

	CString wzFile;
	pStatic->GetWindowText(wzFile);
	CFile hFile;
	if(!hFile.Open(wzFile, CFile::modeRead|CFile::typeBinary))
	{
		MessageBox(L"File can't open.", L"Error", MB_OK|MB_ICONERROR);
		pStatic->SetWindowText(L"");
		ResetControlFDS();
		return;
	}

	UINT nSize = (UINT)hFile.GetLength();
	BYTE* pROM = new BYTE[nSize];
	hFile.Read(pROM, nSize);
	hFile.Close();

	UINT side_number=GetFDSInfo(pROM, nSize, nID);
	delete []pROM;

	//We don't check QD file becausing of the file you give us has too many types.
	/*
	if((pFDSROMInfo[0].nID == 0) || (pFDSROMInfo[0].nAddr != 0))
	{
		MessageBox(L"This File is't the QD Rom.", L"Error", MB_OK|MB_ICONERROR);
		pStatic->SetWindowText(L"");
		ResetControlFDS();
		return;
	}
	*/
	int nDisk = 0;
	int nSide[2] = {0, 0};
	nSide[0]=GetDlgItemInt(IDC_EDIT_PRGROMBANK);
	nSide[1]=GetDlgItemInt(IDC_EDIT_CHRROMBANK);
	switch(nID)
	{
	case IDC_STATIC_PRGROM:
		//We don't check QD file becausing of the file you give us has too many types.
		/*
		if(pFDSROMInfo[0].nSide != 0)
		{
			MessageBox(L"This QD Rom is't the Disk A.", L"Error", MB_OK|MB_ICONERROR);
			pStatic->SetWindowText(L"");
			ResetControlFDS();
			return;
		}
		*/
		nSide[0]=side_number;
		break;
	case IDC_STATIC_CHRROM:
		//We don't check QD file becausing of the file you give us has too many types.
		/*
		if(pFDSROMInfo[0].nSide != 1)
		{
			MessageBox(L"This QD Rom is't the Disk B.", L"Error", MB_OK|MB_ICONERROR);
			pStatic->SetWindowText(L"");
			ResetControlFDS();
			return;
		}
		*/
		nSide[1]=side_number;
		break;
	}
	UINT total=nSide[0]+nSide[1];
		nDisk=total>>1;
	if(total&0x1)
		nDisk+=1;
	/*
	int nSide[2] = {0, 0};
	for(int n=0; n<4; ++n)
	{
		if(g_sFDSROMInfo[n].nID == 0)
			break;
		nSide[g_sFDSROMInfo[n].nDisk]++;
	}
	int nDisk = 0;
	for(int n=0; n<2; ++n)
	{
		if(nSide[n])
			nDisk++;
	}
	*/
	SetDlgItemInt(IDC_EDIT_SRAMBANK, nDisk);
	SetDlgItemInt(IDC_EDIT_PRGROMBANK, nSide[0]);
	SetDlgItemInt(IDC_EDIT_CHRROMBANK, nSide[1]);
}

void CNESROMCombineDlg::AnalyseFDSFile()
{
	CString wzFile;
	m_hStaticPRGROM.GetWindowText(wzFile);
	CFile hFile;
	if(!hFile.Open(wzFile, CFile::modeRead|CFile::typeBinary))
	{
		MessageBox(L"File can't open.", L"Error", MB_OK|MB_ICONERROR);
		m_hStaticPRGROM.SetWindowText(L"");
		ResetControlFDS();
		return;
	}
	UINT nSize = (UINT)hFile.GetLength();
	BYTE* pROM = new BYTE[nSize];
	hFile.Read(pROM, nSize);
	hFile.Close();
	
	if(!((pROM[0] == 0x46) && (pROM[1] == 0x44) && (pROM[2] == 0x53)))
	{
		MessageBox(L"This File is't the FDS Rom.", L"Error", MB_OK|MB_ICONERROR);
		m_hStaticPRGROM.SetWindowText(L"");
		delete []pROM;
		ResetControlFDS();
		return;
	}

	ZeroMemory(g_sFDSROMInfo, sizeof(nesSFDSROMInfo)*4);
	GetFDSInfo(pROM, nSize, IDC_STATIC_PRGROM);
	delete []pROM;

	if(g_sFDSROMInfo[0].nID == 0)
	{
		MessageBox(L"This File is't the FDS Rom.", L"Error", MB_OK|MB_ICONERROR);
		m_hStaticPRGROM.SetWindowText(L"");
		ResetControlFDS();
		return;
	}

	int nSide[2] = {0, 0};
	for(int n=0; n<4; ++n)
	{
		if(g_sFDSROMInfo[n].nID == 0)
			break;
		nSide[g_sFDSROMInfo[n].nDisk]++;
	}
	int nDisk = 0;
	for(int n=0; n<2; ++n)
	{
		if(nSide[n])
			nDisk++;
	}
	SetDlgItemInt(IDC_EDIT_SRAMBANK, nDisk);
	SetDlgItemInt(IDC_EDIT_PRGROMBANK, nSide[0]);
	SetDlgItemInt(IDC_EDIT_CHRROMBANK, nSide[1]);
}


//return number of disk sides of the QD file.
UINT CNESROMCombineDlg::GetFDSInfo(BYTE* pROM, UINT nSize, UINT nID)
{
	UINT nIndex = 0;
	//if(nID == IDC_STATIC_CHRROM)
	//	nIndex = 2;

	int nStart = -1;
	for(UINT nPos=0; nPos<(nSize-15); ++nPos)
	{
		if(memcmp(&pROM[nPos], g_nNesCartFDSID, 15)!=0)
			continue;
		g_sFDSROMInfo[nIndex].nID = nID;
		g_sFDSROMInfo[nIndex].nAddr = nPos;
		g_sFDSROMInfo[nIndex].nDisk = pROM[nPos + 0x16];
		g_sFDSROMInfo[nIndex].nSide = pROM[nPos + 0x15];
		if(nStart>=0)
			g_sFDSROMInfo[nIndex-1].nSize = nPos - nStart;
		nStart = nPos;
		nIndex++;
	}
	if(nStart>=0)
		g_sFDSROMInfo[nIndex-1].nSize = nSize - nStart;
	return nIndex;
}

/**
 * @class nesSROMHeader
 * @brief The Cartridge Header
 */
struct nesSROMHeader
{
	DWORD		nFlag;						///< Flag "TNES"
	BYTE		nMapper;					///< Mapper Number
	BYTE		nPRGBanks;					///< Number of 8K PRG-ROM Banks
	BYTE		nCHRBanks;					///< Number of 8K CHR-ROM Banks
	BYTE		nSRAMBanks;					///< Number of 8K SRAM Banks
	BYTE		nNameTabMapping;			///< Name Table Mapping Type
	BYTE		nBattery;					///< Support Battery
	BYTE		nSideNumber;				///< Number of Sides
	BYTE		nCRC;						///< CRC Enable Flag
	DWORD		nPadding;
};

void CNESROMCombineDlg::AnalyseTrlFile()
{
	CString wzFile;
	m_hStaticPRGROM.GetWindowText(wzFile);
	CFile hFile;
	if(!hFile.Open(wzFile, CFile::modeRead|CFile::typeBinary))
	{
		MessageBox(L"File can't open.", L"Error", MB_OK|MB_ICONERROR);
		m_hStaticPRGROM.SetWindowText(L"");
		ResetControl();
		return;
	}
	nesSROMHeader sHeader;
	hFile.Read(&sHeader, sizeof(nesSROMHeader));
	hFile.Close();
	if(sHeader.nFlag != 0x53454E54)
	{
		MessageBox(L"This File is't the Trl Rom.", L"Error", MB_OK|MB_ICONERROR);
		m_hStaticPRGROM.SetWindowText(L"");
		ResetControl();
		return;
	}
	if(sHeader.nMapper == 100)
	{
		MessageBox(L"Trl FDS Rom can't modify.", L"Error", MB_OK|MB_ICONERROR);
		m_hStaticPRGROM.SetWindowText(L"");
		ResetControl();
		return;
	}

	SetDlgItemInt(IDC_EDIT_SRAMBANK, sHeader.nSRAMBanks);
	SetDlgItemInt(IDC_EDIT_PRGROMBANK, sHeader.nPRGBanks);
	SetDlgItemInt(IDC_EDIT_CHRROMBANK, sHeader.nCHRBanks);
	m_hComboCardType.SetCurSel(sHeader.nMapper);
	m_hComboMapMode.SetCurSel(sHeader.nNameTabMapping);
	m_hButtonBattery.SetCheck(sHeader.nBattery);
}

void CNESROMCombineDlg::OnBnClickedButtonMake()
{
	nesSROMHeader sHeader;
	ZeroMemory(&sHeader, sizeof(nesSROMHeader));
	sHeader.nFlag = 0x53454E54;
	sHeader.nMapper = m_hComboCardType.GetCurSel();
	sHeader.nNameTabMapping = m_hComboMapMode.GetCurSel();
	sHeader.nBattery = m_hButtonBattery.GetCheck();

	CString wzFile;
	m_hStaticPRGROM.GetWindowText(wzFile);
	if(wzFile.IsEmpty())
	{
		MessageBox(L"Please choice rom first!", L"Warning", MB_OK|MB_ICONWARNING);
		GetDlgItem(IDC_BUTTON_PRGROM)->SetFocus();
		return;
	}
	CFile hFile;

	switch(m_hTabCntType.GetCurSel())
	{
	case 0:		// Cartridge
		sHeader.nPRGBanks = GetDlgItemInt(IDC_EDIT_PRGROMBANK);
		sHeader.nCHRBanks = GetDlgItemInt(IDC_EDIT_CHRROMBANK);
		sHeader.nSRAMBanks = GetDlgItemInt(IDC_EDIT_SRAMBANK);
		switch(m_hTabCntMode.GetCurSel())
		{
		case 0:		// Combine
			{
				int nPos = wzFile.ReverseFind('.');
				CString wzExtName = wzFile.Right(wzFile.GetLength()-nPos);
				wzFile = wzFile.Left(nPos-1);
				wzFile.Append(L"A");
				wzFile.Append(wzExtName);
				if(!hFile.Open(wzFile, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))
				{
					MessageBox(L"File can't create.", L"Error", MB_OK|MB_ICONERROR);
					return;
				}
				hFile.Write(&sHeader, sizeof(nesSROMHeader));
				m_hStaticPRGROM.GetWindowText(wzFile);
				CFile hFileROM(wzFile, CFile::modeRead|CFile::typeBinary);
				BYTE* pROM = new BYTE[(UINT)hFileROM.GetLength()];
				hFileROM.Read(pROM, (UINT)hFileROM.GetLength());
				hFile.Write(pROM, (UINT)hFileROM.GetLength());
				delete[] pROM;
				hFileROM.Close();
				m_hStaticCHRROM.GetWindowText(wzFile);
				if(!wzFile.IsEmpty())
				{
					hFileROM.Open(wzFile, CFile::modeRead|CFile::typeBinary);
					pROM = new BYTE[(UINT)hFileROM.GetLength()];
					hFileROM.Read(pROM, (UINT)hFileROM.GetLength());
					hFile.Write(pROM, (UINT)hFileROM.GetLength());
					delete[] pROM;
					hFileROM.Close();
				}
			}
			break;
		case 1:		// Convert
			{
				int nPos = wzFile.ReverseFind('.');
				wzFile = wzFile.Left(nPos);
				wzFile.Append(L"A.000");
				if(!hFile.Open(wzFile, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))
				{
					MessageBox(L"File can't create.", L"Error", MB_OK|MB_ICONERROR);
					return;
				}
				hFile.Write(&sHeader, sizeof(nesSROMHeader));
				m_hStaticPRGROM.GetWindowText(wzFile);
				CFile hFileROM(wzFile, CFile::modeRead|CFile::typeBinary);
				BYTE* pROM = new BYTE[(UINT)hFileROM.GetLength()];
				hFileROM.Read(pROM, (UINT)hFileROM.GetLength());
				hFile.Write(pROM+16, (UINT)hFileROM.GetLength()-16);
				delete[] pROM;
				hFileROM.Close();
			}
			break;
		case 2:		// Modify
			if(!hFile.Open(wzFile, CFile::modeWrite|CFile::typeBinary))
			{
				MessageBox(L"File can't open.", L"Error", MB_OK|MB_ICONERROR);
				return;
			}
			hFile.Write(&sHeader, sizeof(nesSROMHeader));
			break;
		}
		break;
	case 1:		// Disk System
		{
			int nPos = wzFile.ReverseFind('.');
			wzFile = wzFile.Left(nPos);
			wzFile.Append(L"A.tds");
			if(!hFile.Open(wzFile, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))
			{
				MessageBox(L"File can't create.", L"Error", MB_OK|MB_ICONERROR);
				return;
			}

			// Header
			sHeader.nMapper = 100;
			sHeader.nSideNumber = GetDlgItemInt(IDC_EDIT_PRGROMBANK)+GetDlgItemInt(IDC_EDIT_CHRROMBANK);
			sHeader.nCRC = m_hTabCntMode.GetCurSel() ? 0 : 2;
			hFile.Write(&sHeader, sizeof(nesSROMHeader));

			// BIOS
			HRSRC hBIOS = FindResource(NULL, MAKEINTRESOURCE(IDR_FDSBIOS), TEXT("FDSBIOS"));
			DWORD* pBIOS = (DWORD*)LoadResource(NULL, hBIOS);
			hFile.Write(pBIOS, 8192);

			// DISK
			BYTE buffDISK[0x10000];
			if(GetDlgItemInt(IDC_EDIT_PRGROMBANK)>0){
				m_hStaticPRGROM.GetWindowText(wzFile);
				CFile hFileROM(wzFile, CFile::modeRead|CFile::typeBinary);
				for(int n=0; n<GetDlgItemInt(IDC_EDIT_PRGROMBANK); ++n)
				{
					ZeroMemory(buffDISK, 0x10000);
					hFileROM.Read(buffDISK, 0x10000);
					hFile.Write(buffDISK, 0x10000);
				}
				hFileROM.Close();
			}
			if(GetDlgItemInt(IDC_EDIT_CHRROMBANK)>0){
				m_hStaticCHRROM.GetWindowText(wzFile);
				CFile hFileROM(wzFile, CFile::modeRead|CFile::typeBinary);
				for(int n=0; n<GetDlgItemInt(IDC_EDIT_CHRROMBANK); ++n)
				{
					ZeroMemory(buffDISK, 0x10000);
					hFileROM.Read(buffDISK, 0x10000);
					hFile.Write(buffDISK, 0x10000);
				}
				hFileROM.Close();
			}
		}
		break;
	}
	hFile.Close();
	MessageBox(L"Finish!", L"Information", MB_OK|MB_ICONINFORMATION);
}
