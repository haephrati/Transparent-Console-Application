#if !defined(AFX_HMXCOMBOBOX_H__4B614252_74B7_11D5_BD28_0060520365FB__INCLUDED_)
#define AFX_HMXCOMBOBOX_H__4B614252_74B7_11D5_BD28_0060520365FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HMXCombobox.h : header file
//
#include "eventer.h"
/////////////////////////////////////////////////////////////////////////////
// CHMXCombobox window

class CHMXComboBox : public CComboBox
{
// Construction
public:
	CHMXComboBox();

// Attributes
public:
	BOOL m_bAutoComplete;

// Operations
public:
	void Register(Eventer* pEventer);
	void UnRegister(Eventer* pEventer);

protected:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHMXComboBox)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	
// Implementation
public:
	bool SetToolTipText(const CString& sText, bool bActivate = true);
	bool ActivateToolTip(bool bEnable = true);
	bool SetFontBold( bool bBold = true);
	bool SetFontItalic( bool bItalic = true);
	bool SetFontHeight( int nHeight );
	bool SetFontFaceName( const CString& sFaceName );
	bool EnableEditing(bool bEnableEditing = true);
	bool GetTextFont( LOGFONT* plgfnt);
	bool SetTextFont( LONG nHeight, bool bBold, bool bItalic, const CString& sFaceName );
	bool SetTextFont( const LOGFONT& lgfnt );
	bool GetTextClr(COLORREF &clr);
	bool SetTextClr( COLORREF clr );
	bool GetBkClr(COLORREF &clr);
	bool SetBkClr( COLORREF clr );
	virtual ~CHMXComboBox();

protected:
	bool InitToolTip();
	CToolTipCtrl m_tt;
	bool m_bEnableEditing;
	CFont m_fntText;
	COLORREF m_clrTextClr;
	COLORREF m_clrBkClr;
	CBrush m_brsBkGnd;
	CPtrArray m_arrEventers;

	// Generated message map functions
protected:
	//{{AFX_MSG(CHMXComboBox)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEditUpdate();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HMXCOMBOBOX_H__4B614252_74B7_11D5_BD28_0060520365FB__INCLUDED_)
