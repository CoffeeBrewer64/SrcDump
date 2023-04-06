/**
 * @file TexturePackagerForTRLDlg.h
 * @author Chentian
 * @date 2010.12.28
 * @brief Texture Packager For TRL - Main Dialog
 */
#pragma once
#include <vector>
using std::vector;

/**
 * @struct CAboutDlg
 * @brief About Dialog
 */
class CAboutDlg : public CDialog
{
// Function
public:
	/** @name Construction */
	//@{
	CAboutDlg() : CDialog(CAboutDlg::IDD) {}
	//@}
	enum { IDD = IDD_ABOUTBOX };

protected:
	DECLARE_MESSAGE_MAP()
	/** @brief DDX/DDV support */
	virtual void DoDataExchange(CDataExchange* pDX);
};

/**
 * @class STTPHeader
 * @brief TTP File Header
 */
struct STTPHeader
{
	DWORD	nFlag;
	DWORD	nCount;
	DWORD	nPadding0;
	DWORD	nPadding1;
};

/**
 * @class STTPSegment
 * @brief TTP File Segment
 */
struct STTPSegment
{
	DWORD	nFormatLength;
	WORD	nWidth;
	WORD	nHeight;
	WORD	nOffsetX;
	WORD	nOffsetY;
	WORD	nSizeX;
	WORD	nSizeY;
};

/**
 * @class SItemData
 * @brief Item Data
 */
struct SItemData
{
	int		nFormat;
	int		nWidth;
	int		nHeight;
	int		nOffsetX;
	int		nOffsetY;
	int		nSizeX;
	int		nSizeY;
	int		nData;
	BYTE*	pData;
};

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

/**
 * @struct CTexturePackagerForTRLDlg
 * @brief Main Dialog
 */
class CTexturePackagerForTRLDlg : public CDialog
{
// Function
public:
	/** @name Construction */
	//@{
	CTexturePackagerForTRLDlg(CWnd* pParent = NULL);
	~CTexturePackagerForTRLDlg();
	//@}
	enum { IDD = IDD_TEXTUREPACKAGERFORTRL_DIALOG };

protected:
	DECLARE_MESSAGE_MAP()
	/** @brief DDX/DDV support */
	virtual void DoDataExchange(CDataExchange* pDX);
	/** @brief Initialize Dialog */
	virtual BOOL OnInitDialog();
	/** @brief System Command */
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	/** @brief Paint */
	afx_msg void OnPaint();
	/** @brief Query Drag Icon */
	afx_msg HCURSOR OnQueryDragIcon();
public:
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnNMClickListTexture(NMHDR *pNMHDR, LRESULT *pResult);
private:
	void ResetInfoCtrl();
	int GetFormatID();
	bool CheckTextureInfo();
	bool AnalyseNW4CTga(const CString& csFilename);

// Parameter
protected:
	HICON				m_hIcon;
	CListCtrl			m_hListTexture;
	BYTE*				m_pItemData;
	int					m_nItemData;
	vector<SItemData>	m_vecItemData;
};
