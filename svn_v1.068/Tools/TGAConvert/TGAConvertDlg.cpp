
// TGAConvertDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TGAConvert.h"
#include "TGAConvertDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTGAConvertDlg �Ի���




CTGAConvertDlg::CTGAConvertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTGAConvertDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTGAConvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTGAConvertDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CTGAConvertDlg ��Ϣ�������

BOOL CTGAConvertDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTGAConvertDlg::OnPaint()
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTGAConvertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTGAConvertDlg::OnDropFiles(HDROP hDropInfo)
{
	WCHAR szFilename[MAX_PATH] = {0};
	DragQueryFile(hDropInfo, 0, szFilename, MAX_PATH);
	Convert(szFilename);
	CDialog::OnDropFiles(hDropInfo);
}

#pragma pack(1)
/**
 * @class STGAHeader
 * @brief TGA File Header
 */
struct STGAHeader
{
	BYTE	nInfoSize;
	BYTE	nPadding0;
	BYTE	nTgaType;
	BYTE	nPadding1;
	DWORD	nPadding2;
	WORD	nX;
	WORD	nY;
	WORD	nWidth;
	WORD	nHeight;
	WORD	nPadding3;
	char	szNW4C[16];
	DWORD	nDataAddr;
};

/**
 * @class STGATFMHeader
 * @brief TGA TFM Header
 */
struct STGATFMHeader
{
	char	szFlag[8];
	DWORD	nSize;
};
#pragma pack(4)

char g_szNW4C[10] = "NW4C_Tga";
char g_szNW4C_TFM[10] = "nw4c_tfm";

void CTGAConvertDlg::Convert(const CString &csFilename)
{
	CFile hFile;
	if(!hFile.Open(csFilename, CFile::modeRead|CFile::typeBinary))
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

	STGAHeader* pHeader = (STGAHeader*)pBuf;
	if(memcmp(pHeader->szNW4C, g_szNW4C, 8))
	{
		MessageBox(L"This File isn't the NW4C Tga File.", L"Error", MB_OK|MB_ICONERROR);
		delete []pBuf;
		return;
	}

	STGATFMHeader* pTFMHeader = (STGATFMHeader*)(pBuf + pHeader->nDataAddr);
	if(memcmp(pTFMHeader->szFlag, g_szNW4C_TFM, 8))
	{
		MessageBox(L"This File's TFM block has a error.", L"Error", MB_OK|MB_ICONERROR);
		delete []pBuf;
		return;
	}

	BYTE *pData = pBuf + pHeader->nDataAddr + sizeof(STGATFMHeader) + pTFMHeader->nSize;
	nSize = *(long*)(pData - 4) - sizeof(STGATFMHeader);

	CString csRAWname = csFilename.Left(csFilename.GetLength()-3) + "raw";
	if(!hFile.Open(csRAWname, CFile::modeWrite|CFile::modeCreate|CFile::typeBinary))
	{
		MessageBox(L"File can't create.", L"Error", MB_OK|MB_ICONERROR);
		return;
	}
	hFile.Write(pData, nSize);
	hFile.Close();
	delete []pBuf;

	MessageBox(L"Finished.", L"OK", MB_OK|MB_ICONINFORMATION);
}
