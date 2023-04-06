/**
 * @file TexturePackagerForTRLDlg.cpp
 * @author Chentian
 * @date 2010.12.28
 * @brief Texture Packager For TRL - Main Dialog
 */
#include "stdafx.h"
#include "TexturePackagerForTRL.h"
#include "TexturePackagerForTRLDlg.h"

/** @name Macro Define */
//@{
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define FORMAT_COUNT	14
//@}

/** @name Global Variable */
//@{
static const WCHAR g_szFormatName[FORMAT_COUNT][8] = 
{
	L"L4",		// 4-bit luminance
	L"L8",		// 8-bit luminance 
	L"A4",		// 4-bit alpha
	L"A8",		// 8-bit alpha
	L"La4",		// 4-bit luminance and 4-bit alpha
	L"La8",		// 8-bit luminance and 8-bit alpha
	L"Hilo8",	// 8-bit R,G
	L"Rgb565",	// 5-bit R, 6-bit G, 5-bit B
	L"Rgb8",	// 8-bit R,G,B
	L"Rgb5_a1",	// 5-bit R,G,B and 1-bit alpha
	L"Rgba4",	// 4-bit R,G,B,A
	L"Rgba8",	// 8-bit R,G,B,A
	L"Etc1",	// RGB compression
	L"Etc1_a4",	// RGB compression and 4-bit alpha
};
static const char g_szFormatFlag[FORMAT_COUNT][8] = 
{
	"L4nw4c_",	// 4-bit luminance
	"L8nw4c_",	// 8-bit luminance 
	"A4nw4c_",	// 4-bit alpha
	"A8nw4c_",	// 8-bit alpha
	"La4nw4c",	// 4-bit luminance and 4-bit alpha
	"La8nw4c",	// 8-bit luminance and 8-bit alpha
	"Hilo8nw",	// 8-bit R,G
	"Rgb565n",	// 5-bit R, 6-bit G, 5-bit B
	"Rgb8nw4",	// 8-bit R,G,B
	"Rgb5_a1",	// 5-bit R,G,B and 1-bit alpha
	"Rgba4nw",	// 4-bit R,G,B,A
	"Rgba8nw",	// 8-bit R,G,B,A
	"Etc1nw4",	// RGB compression
	"Etc1_a4",	// RGB compression and 4-bit alpha
};
static const char	g_szNW4C[10] = "NW4C_Tga";
static const char	g_szNW4C_TFM[10] = "nw4c_tfm";
static const DWORD	g_szTTPFlag = 0x46505454;		///< TTL File Header Flag - "TTPF"
//@}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

/** @brief DDX/DDV support */
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTexturePackagerForTRLDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CTexturePackagerForTRLDlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CTexturePackagerForTRLDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CTexturePackagerForTRLDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CTexturePackagerForTRLDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CTexturePackagerForTRLDlg::OnBnClickedButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CTexturePackagerForTRLDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CTexturePackagerForTRLDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CTexturePackagerForTRLDlg::OnBnClickedButtonRemove)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TEXTURE, &CTexturePackagerForTRLDlg::OnNMClickListTexture)
END_MESSAGE_MAP()

/** @name Construction */
//@{
CTexturePackagerForTRLDlg::CTexturePackagerForTRLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTexturePackagerForTRLDlg::IDD, pParent), m_pItemData(NULL), m_nItemData(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CTexturePackagerForTRLDlg::~CTexturePackagerForTRLDlg()
{
	if(m_pItemData)
		delete []m_pItemData;
	for(int n=0; n<(int)m_vecItemData.size(); ++n)
	{
		if(m_vecItemData[n].pData)
			delete []m_vecItemData[n].pData;
	}
}
//@}

/** @brief DDX/DDV support */
void CTexturePackagerForTRLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TEXTURE, m_hListTexture);
}

/** @brief Initialize Dialog */
BOOL CTexturePackagerForTRLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_hListTexture.SetExtendedStyle(LVS_REPORT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_hListTexture.InsertColumn(0, L"Length", LVCFMT_LEFT, 60 );
	m_hListTexture.InsertColumn(1, L"Format", LVCFMT_LEFT, 60 );
	m_hListTexture.InsertColumn(2, L"Width", LVCFMT_LEFT, 50 );
	m_hListTexture.InsertColumn(3, L"Height", LVCFMT_LEFT, 50 );
	m_hListTexture.InsertColumn(4, L"OffsetX", LVCFMT_LEFT, 55 );
	m_hListTexture.InsertColumn(5, L"OffsetY", LVCFMT_LEFT, 55 );
	m_hListTexture.InsertColumn(6, L"SizeX", LVCFMT_LEFT, 50 );
	m_hListTexture.InsertColumn(7, L"SizeY", LVCFMT_LEFT, 50 );

	ResetInfoCtrl();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

/** @brief System Command */
void CTexturePackagerForTRLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

/** @brief Paint */
void CTexturePackagerForTRLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

/** @brief Query Drag Icon */
HCURSOR CTexturePackagerForTRLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTexturePackagerForTRLDlg::OnBnClickedButtonNew()
{
	m_hListTexture.DeleteAllItems();
	m_nItemData = 0;
	if(m_pItemData)
	{
		delete []m_pItemData;
		m_pItemData = NULL;
	}
	for(int n=0; n<(int)m_vecItemData.size(); ++n)
	{
		if(m_vecItemData[n].pData)
			delete []m_vecItemData[n].pData;
	}
	m_vecItemData.clear();
	ResetInfoCtrl();
}

void CTexturePackagerForTRLDlg::OnBnClickedButtonLoad()
{
	CFileDialog dlg(TRUE, _T("ttp"), _T("*.ttp"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("TRL Texture Package File (*.ttp)|*.ttp||"));
	dlg.m_pOFN->lpstrTitle = _T("Load...");
	if(dlg.DoModal()==IDOK)
	{
		CFile hFile;
		if(!hFile.Open(dlg.GetPathName(), CFile::modeRead|CFile::typeBinary))
		{
			MessageBox(L"File can't open.", L"Error", MB_OK|MB_ICONERROR);
			return;
		}

		STTPHeader sHeader;
		hFile.Read(&sHeader, sizeof(STTPHeader));
		if(sHeader.nFlag != g_szTTPFlag)
		{
			MessageBox(L"This file isn't the TRL Texture Package File.", L"Error", MB_OK|MB_ICONERROR);
			hFile.Close();
			return;
		}

		OnBnClickedButtonNew();

		for(DWORD n=0; n<sHeader.nCount; ++n)
		{
			STTPSegment sSegment;
			hFile.Read(&sSegment, sizeof(STTPSegment));

			SItemData sData;
			sData.nFormat = sSegment.nFormatLength >> 24;
			sData.nWidth = sSegment.nWidth;
			sData.nHeight = sSegment.nHeight;
			sData.nOffsetX = sSegment.nOffsetX;
			sData.nOffsetY = sSegment.nOffsetY;
			sData.nSizeX = sSegment.nSizeX;
			sData.nSizeY = sSegment.nSizeY;
			sData.nData = sSegment.nFormatLength & 0x00FFFFFF;
			sData.pData = new BYTE[sData.nData];
			hFile.Read(sData.pData, sData.nData);
			m_vecItemData.push_back(sData);

			CString szItemText;
			szItemText.Format(L"%d", sData.nData);
			m_hListTexture.InsertItem(n, szItemText);
			m_hListTexture.SetItemText(n, 1, g_szFormatName[sData.nFormat]);
			szItemText.Format(L"%d", sData.nWidth);
			m_hListTexture.SetItemText(n, 2, szItemText);
			szItemText.Format(L"%d", sData.nHeight);
			m_hListTexture.SetItemText(n, 3, szItemText);
			szItemText.Format(L"%d", sData.nOffsetX);
			m_hListTexture.SetItemText(n, 4, szItemText);
			szItemText.Format(L"%d", sData.nOffsetY);
			m_hListTexture.SetItemText(n, 5, szItemText);
			szItemText.Format(L"%d", sData.nSizeX);
			m_hListTexture.SetItemText(n, 6, szItemText);
			szItemText.Format(L"%d", sData.nSizeY);
			m_hListTexture.SetItemText(n, 7, szItemText);
		}
	}
}

void CTexturePackagerForTRLDlg::OnBnClickedButtonSave()
{
	if(m_vecItemData.empty())
	{
		MessageBox(L"Please add Texture first.", L"Error", MB_OK|MB_ICONERROR);
		return;
	}
	CFileDialog dlg(FALSE, _T("ttp"), _T("*.ttp"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("TRL Texture Package File (*.ttp)|*.ttp||"));
	dlg.m_pOFN->lpstrTitle = _T("Save...");
	if(dlg.DoModal()==IDOK)
	{
		CFile hFile;
		if(!hFile.Open(dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))
		{
			MessageBox(L"File can't create.", L"Error", MB_OK|MB_ICONERROR);
			return;
		}

		STTPHeader sHeader;
		sHeader.nFlag = g_szTTPFlag;
		sHeader.nCount = m_vecItemData.size();
		sHeader.nPadding0 = 0;
		sHeader.nPadding1 = 0;
		hFile.Write(&sHeader, sizeof(STTPHeader));

		for(DWORD n=0; n<sHeader.nCount; ++n)
		{
			STTPSegment sSegment;
			sSegment.nFormatLength = (m_vecItemData[n].nFormat << 24) | m_vecItemData[n].nData;
			sSegment.nWidth = m_vecItemData[n].nWidth;
			sSegment.nHeight = m_vecItemData[n].nHeight;
			sSegment.nOffsetX = m_vecItemData[n].nOffsetX;
			sSegment.nOffsetY = m_vecItemData[n].nOffsetY;
			sSegment.nSizeX = m_vecItemData[n].nSizeX;
			sSegment.nSizeY = m_vecItemData[n].nSizeY;
			hFile.Write(&sSegment, sizeof(STTPSegment));
			hFile.Write(m_vecItemData[n].pData, m_vecItemData[n].nData);
		}

		hFile.Close();

		MessageBox(L"Finished.", L"OK", MB_OK|MB_ICONINFORMATION);
	}
}

void CTexturePackagerForTRLDlg::OnBnClickedButtonExit()
{
	OnOK();
}

void CTexturePackagerForTRLDlg::OnBnClickedButtonFile()
{
	CFileDialog dlg(TRUE, _T("tga"), _T("*.tga"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("NW4C_Tga (*.tga)|*.tga||"));
	dlg.m_pOFN->lpstrTitle = _T("Open File");
	if(dlg.DoModal()==IDOK)
		AnalyseNW4CTga(dlg.GetPathName());
}

void CTexturePackagerForTRLDlg::OnBnClickedButtonAdd()
{
	if(!CheckTextureInfo())
		return;

	SItemData sData;
	sData.nFormat = GetFormatID();
	sData.nWidth = GetDlgItemInt(IDC_STATIC_WIDTH);
	sData.nHeight = GetDlgItemInt(IDC_STATIC_HEIGHT);
	sData.nOffsetX = GetDlgItemInt(IDC_EDIT_OFFSETX);
	sData.nOffsetY = GetDlgItemInt(IDC_EDIT_OFFSETY);
	sData.nSizeX = GetDlgItemInt(IDC_EDIT_SIZEX);
	sData.nSizeY = GetDlgItemInt(IDC_EDIT_SIZEY);
	sData.nData = m_nItemData;
	sData.pData = new BYTE[m_nItemData];
	memcpy(sData.pData, m_pItemData, m_nItemData);
	m_vecItemData.push_back(sData);

	int nItem = m_vecItemData.size()-1;
	CString szItemText;
	szItemText.Format(L"%d", sData.nData);
	m_hListTexture.InsertItem(nItem, szItemText);
	m_hListTexture.SetItemText(nItem, 1, g_szFormatName[sData.nFormat]);
	szItemText.Format(L"%d", sData.nWidth);
	m_hListTexture.SetItemText(nItem, 2, szItemText);
	szItemText.Format(L"%d", sData.nHeight);
	m_hListTexture.SetItemText(nItem, 3, szItemText);
	szItemText.Format(L"%d", sData.nOffsetX);
	m_hListTexture.SetItemText(nItem, 4, szItemText);
	szItemText.Format(L"%d", sData.nOffsetY);
	m_hListTexture.SetItemText(nItem, 5, szItemText);
	szItemText.Format(L"%d", sData.nSizeX);
	m_hListTexture.SetItemText(nItem, 6, szItemText);
	szItemText.Format(L"%d", sData.nSizeY);
	m_hListTexture.SetItemText(nItem, 7, szItemText);
}

void CTexturePackagerForTRLDlg::OnBnClickedButtonEdit()
{
	int nItem = m_hListTexture.GetNextItem(-1, LVNI_SELECTED);
	if(nItem == -1)
		return;
	if(!CheckTextureInfo())
		return;
	SItemData* pData = &m_vecItemData[nItem];
	pData->nFormat = GetFormatID();
	pData->nWidth = GetDlgItemInt(IDC_STATIC_WIDTH);
	pData->nHeight = GetDlgItemInt(IDC_STATIC_HEIGHT);
	pData->nOffsetX = GetDlgItemInt(IDC_EDIT_OFFSETX);
	pData->nOffsetY = GetDlgItemInt(IDC_EDIT_OFFSETY);
	pData->nSizeX = GetDlgItemInt(IDC_EDIT_SIZEX);
	pData->nSizeY = GetDlgItemInt(IDC_EDIT_SIZEY);
	pData->nData = m_nItemData;
	delete []pData->pData;
	pData->pData = new BYTE[m_nItemData];
	memcpy(pData->pData, m_pItemData, m_nItemData);

	CString szItemText;
	szItemText.Format(L"%d", pData->nData);
	m_hListTexture.SetItemText(nItem, 0, szItemText);
	m_hListTexture.SetItemText(nItem, 1, g_szFormatName[pData->nFormat]);
	szItemText.Format(L"%d", pData->nWidth);
	m_hListTexture.SetItemText(nItem, 2, szItemText);
	szItemText.Format(L"%d", pData->nHeight);
	m_hListTexture.SetItemText(nItem, 3, szItemText);
	szItemText.Format(L"%d", pData->nOffsetX);
	m_hListTexture.SetItemText(nItem, 4, szItemText);
	szItemText.Format(L"%d", pData->nOffsetY);
	m_hListTexture.SetItemText(nItem, 5, szItemText);
	szItemText.Format(L"%d", pData->nSizeX);
	m_hListTexture.SetItemText(nItem, 6, szItemText);
	szItemText.Format(L"%d", pData->nSizeY);
	m_hListTexture.SetItemText(nItem, 7, szItemText);
}

void CTexturePackagerForTRLDlg::OnBnClickedButtonRemove()
{
	int nItem = m_hListTexture.GetNextItem(-1, LVNI_SELECTED);
	if(nItem == -1)
		return;
	m_hListTexture.DeleteItem(nItem);
	delete []m_vecItemData[nItem].pData;
	m_vecItemData.erase(m_vecItemData.begin()+nItem);
	ResetInfoCtrl();
}

void CTexturePackagerForTRLDlg::OnNMClickListTexture(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if(pNMItemActivate->iItem == -1)
		ResetInfoCtrl();
	else
	{
		SItemData* pData = &m_vecItemData[pNMItemActivate->iItem];
		SetDlgItemText(IDC_STATIC_FORMAT, g_szFormatName[pData->nFormat]);
		SetDlgItemInt(IDC_STATIC_LENGTH, pData->nData);
		SetDlgItemInt(IDC_STATIC_WIDTH, pData->nWidth);
		SetDlgItemInt(IDC_STATIC_HEIGHT, pData->nHeight);
		SetDlgItemInt(IDC_EDIT_OFFSETX, pData->nOffsetX);
		SetDlgItemInt(IDC_EDIT_OFFSETY, pData->nOffsetY);
		SetDlgItemInt(IDC_EDIT_SIZEX, pData->nSizeX);
		SetDlgItemInt(IDC_EDIT_SIZEY, pData->nSizeY);
		m_nItemData = pData->nData;
		if(m_pItemData)
			delete []m_pItemData;
		m_pItemData = new BYTE[m_nItemData];
		memcpy(m_pItemData, pData->pData, m_nItemData);
	}
	*pResult = 0;
}

void CTexturePackagerForTRLDlg::ResetInfoCtrl()
{
	SetDlgItemText(IDC_STATIC_FORMAT, L"");
	SetDlgItemInt(IDC_STATIC_LENGTH, 0);
	SetDlgItemInt(IDC_STATIC_WIDTH, 0);
	SetDlgItemInt(IDC_STATIC_HEIGHT, 0);
	SetDlgItemInt(IDC_EDIT_OFFSETX, 0);
	SetDlgItemInt(IDC_EDIT_OFFSETY, 0);
	SetDlgItemInt(IDC_EDIT_SIZEX, 0);
	SetDlgItemInt(IDC_EDIT_SIZEY, 0);
	m_nItemData = 0;
	if(m_pItemData)
	{
		delete []m_pItemData;
		m_pItemData = NULL;
	}
}

int CTexturePackagerForTRLDlg::GetFormatID()
{
	WCHAR szFormat[8];
	GetDlgItemText(IDC_STATIC_FORMAT, szFormat, 8);
	for(int n=0; n<FORMAT_COUNT; ++n)
	{
		if(wcscmp(g_szFormatName[n], szFormat)==0)
			return n;
	}
	return -1;
}

bool CTexturePackagerForTRLDlg::CheckTextureInfo()
{
	if(m_nItemData == 0)
	{
		MessageBox(L"Please choice the NW4C Tga file.", L"Warning", MB_OK|MB_ICONWARNING);
		GetDlgItem(IDC_BUTTON_FILE)->SetFocus();
		return false;
	}

	int nValue = GetDlgItemInt(IDC_EDIT_SIZEX);
	if(nValue == 0)
	{
		MessageBox(L"Size must > 0.", L"Warning", MB_OK|MB_ICONWARNING);
		GetDlgItem(IDC_EDIT_SIZEX)->SetFocus();
		return false;
	}

	nValue = GetDlgItemInt(IDC_EDIT_SIZEY);
	if(nValue == 0)
	{
		MessageBox(L"Size must > 0.", L"Warning", MB_OK|MB_ICONWARNING);
		GetDlgItem(IDC_EDIT_SIZEY)->SetFocus();
		return false;
	}
	return true;
}

bool CTexturePackagerForTRLDlg::AnalyseNW4CTga(const CString& csFilename)
{
	CFile hFile;
	if(!hFile.Open(csFilename, CFile::modeRead|CFile::typeBinary))
	{
		MessageBox(L"File can't open.", L"Error", MB_OK|MB_ICONERROR);
		return false;
	}
	long nSize = (long)hFile.GetLength();
	BYTE* pBuf = new BYTE[nSize];
	UINT nRead = hFile.Read(pBuf, nSize);
	hFile.Close();
	if(nRead!=nSize)
	{
		MessageBox(L"File read error.", L"Error", MB_OK|MB_ICONERROR);
		delete []pBuf;
		return false;
	}

	STGAHeader* pHeader = (STGAHeader*)pBuf;
	if(memcmp(pHeader->szNW4C, g_szNW4C, 8))
	{
		MessageBox(L"This file isn't the NW4C Tga File.", L"Error", MB_OK|MB_ICONERROR);
		delete []pBuf;
		return false;
	}

	STGATFMHeader* pTFMHeader = (STGATFMHeader*)(pBuf + pHeader->nDataAddr);
	if(memcmp(pTFMHeader->szFlag, g_szNW4C_TFM, 8))
	{
		MessageBox(L"This file's TFM block has a error.", L"Error", MB_OK|MB_ICONERROR);
		delete []pBuf;
		return false;
	}

	BYTE* pTemp = pBuf + pHeader->nDataAddr + sizeof(STGATFMHeader);
	int nFormat = -1;
	for(int n=0; n<FORMAT_COUNT; ++n)
	{
		if(memcmp(pTemp, g_szFormatFlag[n], 7)==0)
		{
			nFormat = n;
			break;
		}
	}
	if(nFormat == -1)
	{
		MessageBox(L"This file's Format not support.", L"Error", MB_OK|MB_ICONERROR);
		delete []pBuf;
		return false;
	}

	if(m_pItemData)
		delete []m_pItemData;
	pTemp += pTFMHeader->nSize;
	m_nItemData = *(long*)(pTemp - 4) - sizeof(STGATFMHeader);
	m_pItemData = new BYTE[m_nItemData];
	memcpy(m_pItemData, pTemp, m_nItemData);

	SetDlgItemText(IDC_STATIC_FORMAT, g_szFormatName[nFormat]);
	SetDlgItemInt(IDC_STATIC_LENGTH, m_nItemData);
	SetDlgItemInt(IDC_STATIC_WIDTH, pHeader->nWidth);
	SetDlgItemInt(IDC_STATIC_HEIGHT, pHeader->nHeight);
	delete []pBuf;
	MessageBox(L"OK.", L"OK", MB_OK|MB_ICONINFORMATION);
	return true;
}
