// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TConsole.h"

#include "MainFrm.h"
#include ".\mainfrm.h"
#include "TransparencyDlg.h"
#include <winuser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WS_EX_LAYERED           0x00080000
#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE( WM_ENTERSIZEMOVE, OnEnterSizeMove)
	ON_MESSAGE( WM_EXITSIZEMOVE, OnExitSizeMove)
	ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
	SaveTransparency();
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE)^WS_EX_LAYERED);
	LoadTransparency();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers
LRESULT CMainFrame::OnEnterSizeMove( WPARAM wparam, LPARAM lparam)
{
    // do stuff
	::SetLayeredWindowAttributes(m_hWnd,RGB(0,0,0),255,LWA_ALPHA);
    return (LRESULT)0;
}

LRESULT CMainFrame::OnExitSizeMove( WPARAM wparam, LPARAM lparam)
{
    // do stuff
	::SetLayeredWindowAttributes(m_hWnd,RGB(0,0,0),m_trans,LWA_ALPHA);
    return (LRESULT)0;
}


void CMainFrame::OnViewOptions()
{
	CTransparencyDlg dlg(this, m_trans);
	if(dlg.DoModal() == IDOK)
	{
		if (m_trans != 255)
			::SetLayeredWindowAttributes(m_hWnd,RGB(0,0,0),255,LWA_ALPHA);
        m_trans = dlg.GetTransparency();		
		::SetLayeredWindowAttributes(m_hWnd,RGB(0,0,0),m_trans,LWA_ALPHA);
	}
}

void CMainFrame::SaveTransparency()
{
	CString strSection = "Transparency";
    CWinApp* pApp = AfxGetApp();

	pApp->WriteProfileInt(strSection, "Level", m_trans);
}

void CMainFrame::LoadTransparency()
{
	CString strSection = "Transparency";
	CWinApp* pApp = AfxGetApp();

	m_trans = pApp->GetProfileInt(strSection, "Level", 255);
	::SetLayeredWindowAttributes(m_hWnd,RGB(0,0,0),m_trans,LWA_ALPHA);
}

