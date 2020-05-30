// ColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TConsole.h"
#include "ColorDlg.h"
#include ".\colordlg.h"


// CColorDlg dialog

IMPLEMENT_DYNAMIC(CColorDlg, CDialog)
CColorDlg::CColorDlg(CFontHelper* cslFonts,
					 CFontHelper* cmdFonts,
					 CWnd* pParent, 
					 COLORREF clrBk,
					 COLORREF clrFont,
					 COLORREF clrFocusBk,
					 COLORREF clrFocusFont,
					 COLORREF cmdClrBk,
					 COLORREF cmdClrFont,
					 COLORREF clrForm)
	: CDialog(CColorDlg::IDD, pParent),cslFntHelper(cslFonts),cmdFntHelper(cmdFonts)
{
	m_cslBkColor.SetColor(clrBk);
	m_cslFontColor.SetColor(clrFont);
	m_cslFocusBkColor.SetColor(clrFocusBk);
	m_cslFontFocusColor.SetColor(clrFocusFont);
	m_cmdBkColor.SetColor(cmdClrBk);
	m_cmdFontColor.SetColor(cmdClrFont);
	m_clrForm.SetColor(clrForm);
}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_cslBkColor);
	DDX_Control(pDX, IDC_BUTTON2, m_cslFontColor);
	DDX_Control(pDX, IDC_STATIC_FONT, m_stFont);
	DDX_Control(pDX, IDC_BUTTON4, m_cslFocusBkColor);
	DDX_Control(pDX, IDC_BUTTON5, m_cslFontFocusColor);
	DDX_Control(pDX, IDC_BUTTON6, m_cmdBkColor);
	DDX_Control(pDX, IDC_BUTTON7, m_cmdFontColor);
	DDX_Control(pDX, IDC_STATIC_FONT2, m_cmdStFont);
	DDX_Control(pDX, IDC_BUTTON9, m_clrForm);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButtonFonts)
	ON_BN_CLICKED(IDC_BUTTON8, OnBnClickedButton8)
//	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CColorDlg message handlers
COLORREF CColorDlg::GetConsoleBkColor() const
{
	return m_cslBkColor.GetColor();
}
COLORREF CColorDlg::GetConsoleFontColor() const
{
	return m_cslFontColor.GetColor();
}

COLORREF CColorDlg::GetConsoleFocusBkColor() const
{
	return m_cslFocusBkColor.GetColor();
}

COLORREF CColorDlg::GetConsoleFocusFontColor() const
{
	return m_cslFontFocusColor.GetColor();
}

COLORREF CColorDlg::GetCommandBkColor() const
{
	return m_cmdBkColor.GetColor();
}

COLORREF CColorDlg::GetCommandFontColor() const
{
	return m_cmdFontColor.GetColor();
}

COLORREF CColorDlg::GetFormColor() const
{
	return m_clrForm.GetColor();
}

void CColorDlg::OnBnClickedButtonFonts()
{
	if(cslFntHelper && cslFntHelper->ChooseFont())
	{		
		LOGFONT lf;
		cslFntHelper->GetLogFont(lf);
		CFont font;
		VERIFY(font.CreateFontIndirect(&lf));  // create the font
		m_stFont.SetFont(&font);
		m_stFont.SetWindowText(lf.lfFaceName);
	}
}

void CColorDlg::OnBnClickedButton8()
{
	if(cmdFntHelper && cmdFntHelper->ChooseFont())
	{		
		LOGFONT lf;
		cmdFntHelper->GetLogFont(lf);
		CFont font;
		VERIFY(font.CreateFontIndirect(&lf));  // create the font
		m_cmdStFont.SetFont(&font);
		m_cmdStFont.SetWindowText(lf.lfFaceName);
	}
}

