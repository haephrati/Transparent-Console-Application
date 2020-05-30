// TConsoleView.h : interface of the CTConsoleView class
//


#pragma once
#include <afxwin.h>
#include "editredir.h"
#include "hmxedit.h"
#include "hmxcombobox.h"
#include "eventer.h"
#include "fonthelper.h"

class CTConsoleView : public CFormView, Eventer
{
protected: // create from serialization only
	CTConsoleView();
	DECLARE_DYNCREATE(CTConsoleView)

public:
	enum{ IDD = IDD_TCONSOLE_FORM };

// Attributes
public:
	CTConsoleDoc* GetDocument() const;

// Operations
public:
	void SetBackgroundColor(COLORREF crBackground);
// Overrides
	public:
		virtual void PerformAction(const CString& strCmd);
		virtual void PerformSpecialAction(UINT nAction);

virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CTConsoleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CEditRedirector m_redir;
	int m_comboHeight;
	static const int c_comboShift = 20;
	CFontHelper cslFntHelper;
	CFontHelper cmdFntHelper;

	COLORREF m_crBackground;
	CBrush m_wndbkBrush;	// background brush

	void SaveColors();
	void LoadColors();
// Generated message map functions
protected:
	
	DECLARE_MESSAGE_MAP()	

public:
	CHMXEdit m_edit;
	CHMXComboBox m_combo;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNewconsole();
	afx_msg void OnViewColors();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in TConsoleView.cpp
inline CTConsoleDoc* CTConsoleView::GetDocument() const
   { return reinterpret_cast<CTConsoleDoc*>(m_pDocument); }
#endif

