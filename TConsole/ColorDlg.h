#pragma once
#include <afxwin.h>
#include "ColourPickerXP.h"
#include "fonthelper.h"

// CColorDlg dialog

class CColorDlg : public CDialog
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CFontHelper* cslFonts,
			  CFontHelper* cmdFonts,
			  CWnd* pParent = NULL, 
			  COLORREF clrBk = RGB(0,0,0),
			  COLORREF clrFont = RGB(255,255,255),
			  COLORREF clrFocusBk = RGB(200,200,200),
			  COLORREF clrFocusFont =  RGB(128,0,0),
			  COLORREF cmdClrBk =  RGB(255,255,204),
			  COLORREF cmdClrFont = RGB(0,0,0),
			  COLORREF clrForm = COLOR_BTNFACE);   // standard constructor
	virtual ~CColorDlg();

	// operations
	COLORREF GetConsoleBkColor() const;
	COLORREF GetConsoleFontColor() const;
	COLORREF GetConsoleFocusBkColor() const;
	COLORREF GetConsoleFocusFontColor() const;
	COLORREF GetCommandBkColor() const;
	COLORREF GetCommandFontColor() const;
	COLORREF GetFormColor() const;

// Dialog Data
	enum { IDD = IDD_COLOR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CString m_strFontName;

	DECLARE_MESSAGE_MAP()
public:
	CColourPickerXP m_cslBkColor;
	CColourPickerXP m_cslFontColor;
	CColourPickerXP m_cslFocusBkColor;
	CColourPickerXP m_cslFontFocusColor;
	CColourPickerXP m_clrForm;
	CColourPickerXP m_cmdBkColor;
	CColourPickerXP m_cmdFontColor;

	CFontHelper* cslFntHelper;
	CFontHelper* cmdFntHelper;

	CStatic m_stFont;
	CStatic m_cmdStFont;

	afx_msg void OnBnClickedButtonFonts();
	afx_msg void OnBnClickedButton8();
};
