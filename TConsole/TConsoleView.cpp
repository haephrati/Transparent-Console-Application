// TConsoleView.cpp : implementation of the CTConsoleView class
//

#include "stdafx.h"
#include "TConsole.h"

#include "TConsoleDoc.h"
#include "TConsoleView.h"
#include ".\tconsoleview.h"
#include "hmxcombobox.h"
#include "hmxedit.h"
#include "colordlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern "C" {
	WINUSERAPI
BOOL
WINAPI
SetLayeredWindowAttributes(
    HWND hwnd,
    COLORREF crKey,
    BYTE bAlpha,
    DWORD dwFlags);
}


// CTConsoleView

IMPLEMENT_DYNCREATE(CTConsoleView, CFormView)

BEGIN_MESSAGE_MAP(CTConsoleView, CFormView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_NEWCONSOLE, OnNewconsole)
	ON_COMMAND(ID_VIEW_COLORS, OnViewColors)
END_MESSAGE_MAP()

// CTConsoleView construction/destruction

CTConsoleView::CTConsoleView()
	: CFormView(CTConsoleView::IDD),
	cslFntHelper("Fonts", "Console"),
	cmdFntHelper("Fonts", "Command")
{
	// TODO: add construction code here	
	m_comboHeight = 18;
	m_crBackground = GetSysColor(COLOR_3DFACE);
	m_wndbkBrush.CreateSolidBrush(m_crBackground); 
}

CTConsoleView::~CTConsoleView()
{
	cslFntHelper.Save();
	cmdFntHelper.Save();
	SaveColors();
}

void CTConsoleView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
}

BOOL CTConsoleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CTConsoleView::SetBackgroundColor(COLORREF crBackground)
{
	m_crBackground = crBackground;
	
	if(m_wndbkBrush.GetSafeHandle())
		m_wndbkBrush.DeleteObject();

	m_wndbkBrush.CreateSolidBrush(m_crBackground); 
}

void CTConsoleView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();    
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	LoadColors();

	cslFntHelper.Restore();
	LOGFONT lf;
	cslFntHelper.GetLogFont(lf);
	m_edit.SetTextFont(lf);	
	m_edit.SetToolTipText( "Console output window");

	m_edit.RedrawWindow();
	
	cmdFntHelper.Restore();
	cmdFntHelper.GetLogFont(lf);
	m_combo.SetTextFont(lf);
	m_combo.SetToolTipText("Select from list or type your own");
	m_combo.AddString("dir");

	m_combo.Register(this);

	m_redir.m_pWnd = &m_edit;
	m_redir.m_pWnd->SetWindowText("");
	m_redir.Close();
	m_redir.Open("Cmd");
}


// CTConsoleView diagnostics

#ifdef _DEBUG
void CTConsoleView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTConsoleView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTConsoleDoc* CTConsoleView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTConsoleDoc)));
	return (CTConsoleDoc*)m_pDocument;
}
#endif //_DEBUG

void CTConsoleView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CRect rect;                               	
	GetClientRect(&rect);

	int edtYTo     = 0;
	int edtYHeight = rect.bottom-2*c_comboShift-m_comboHeight*2;
	int cmbYTop    = rect.bottom-c_comboShift-m_comboHeight*2;
	int cmbYHeight = m_comboHeight;

	if(m_edit)
		m_edit.SetWindowPos(&m_edit, 
                       0, 
					   edtYTo, 
                       rect.right, 
                       edtYHeight, 
                       SWP_NOZORDER | SWP_SHOWWINDOW);
	if(m_combo)
		m_combo.SetWindowPos(&m_combo, 
                       0, 
					   cmbYTop, 
                       rect.right, 
                       cmbYHeight*15, 
                       SWP_NOZORDER | SWP_SHOWWINDOW);

}

void CTConsoleView::OnNewconsole()
{
	// TODO: Add your command handler code here
	
	m_redir.m_pWnd = &m_edit;
	m_redir.m_pWnd->SetWindowText("");
	m_redir.Close();
	m_redir.Open("Cmd");
}

void CTConsoleView::PerformAction(const CString& strCmd)
{
	if(!strCmd.Left(4).CompareNoCase("edit"))
	{
		CString cmd = "notepad.exe ";
		cmd += strCmd.Right(strCmd.GetLength()-4);
		WinExec(cmd, SW_SHOW);
		return;
	}
	m_redir.Printf("%s\r\n", strCmd);
	m_combo.SetWindowText("");
}

void CTConsoleView::PerformSpecialAction(UINT nAction)
{
	switch(nAction)
	{
	case VK_F1: OnNewconsole();
		        break;
	default: break;
	}
}

void CTConsoleView::OnViewColors()
{
	// TODO: Add your command handler code here
	COLORREF cslBk, cslFont, cslFocusBk, cslFocusFont, cmdBk, cmdFont;

	m_edit.GetBkClr(cslBk);           m_edit.GetTextClr(cslFont);
    m_edit.GetBkClrFocus(cslFocusBk); m_edit.GetTextClrFocus(cslFocusFont);
    m_combo.GetBkClr(cmdBk);          m_combo.GetTextClr(cmdFont);

	CColorDlg dlg(&cslFntHelper,
				  &cmdFntHelper,
				  this,
				  cslBk,
				  cslFont,
				  cslFocusBk,
				  cslFocusFont,
				  cmdBk,
				  cmdFont,
				  m_crBackground);

	if( dlg.DoModal() == IDOK )
	{
		SetBackgroundColor(dlg.GetFormColor());

		m_edit.SetBkClr(dlg.GetConsoleBkColor());		
		m_edit.SetTextClr( dlg.GetConsoleFontColor() );
		m_edit.SetBkClrFocus(dlg.GetConsoleFocusBkColor());
		m_edit.SetTextClrFocus(dlg.GetConsoleFocusFontColor());		

		m_combo.SetBkClr(dlg.GetCommandBkColor());		
		m_combo.SetTextClr( dlg.GetCommandFontColor() );

		LOGFONT lf;
		cslFntHelper.GetLogFont(lf);
		m_edit.SetTextFont(lf);

		cmdFntHelper.GetLogFont(lf);
		m_combo.SetTextFont(lf);

		m_edit.RedrawWindow();
		m_combo.RedrawWindow();

		Invalidate();
	}
}

void CTConsoleView::SaveColors()
{
	CString strSection = "Colors";
	COLORREF cr;

    CWinApp* pApp = AfxGetApp();

	m_edit.GetBkClr(cr);
    pApp->WriteProfileInt(strSection, "Console background", cr);
	m_edit.GetTextClr(cr);
	pApp->WriteProfileInt(strSection, "Console text", cr);
	m_edit.GetBkClrFocus(cr);
	pApp->WriteProfileInt(strSection, "Console focus background", cr);
	m_edit.GetTextClrFocus(cr);
	pApp->WriteProfileInt(strSection, "Console focus Text", cr);

	m_combo.GetBkClr(cr);
	pApp->WriteProfileInt(strSection, "Command background", cr);
	m_combo.GetTextClr(cr);
	pApp->WriteProfileInt(strSection, "Command text", cr);

	pApp->WriteProfileInt(strSection, "Form",m_crBackground);
}

void CTConsoleView::LoadColors()
{
	CString strSection = "Colors";
	CWinApp* pApp = AfxGetApp();

    COLORREF crCslBkColor          = pApp->GetProfileInt(strSection, "Console background", RGB( 0, 0, 0));
	COLORREF crCslTextColor        = pApp->GetProfileInt(strSection, "Console text", RGB( 255,255, 255));
	COLORREF crCslFocusBkColor     = pApp->GetProfileInt(strSection, "Console focus background", RGB( 200, 200, 200 ));
	COLORREF crCslFocusTextColor   = pApp->GetProfileInt(strSection, "Console focus text", RGB( 128, 0, 0));

	COLORREF crCmdBkColor          = pApp->GetProfileInt(strSection, "Command background", RGB(255, 255, 204));
	COLORREF crCmdTextColor        = pApp->GetProfileInt(strSection, "Command text", RGB( 0, 0, 0));
	COLORREF crBackground          = pApp->GetProfileInt(strSection, "Form", COLOR_BTNFACE);

	m_edit.SetBkClr( crCslBkColor );
	m_edit.SetTextClr( crCslTextColor );
	m_edit.SetBkClrFocus( crCslFocusBkColor );
	m_edit.SetTextClrFocus( crCslFocusTextColor );

	m_combo.SetBkClr( crCmdBkColor );	
	m_combo.SetTextClr( crCmdTextColor );

	SetBackgroundColor(crBackground);
}

BOOL CTConsoleView::OnEraseBkgnd(CDC* pDC) 
{
	//CFormView::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(rect);

	pDC->FillRect(&rect, &m_wndbkBrush);

	return TRUE;
}
