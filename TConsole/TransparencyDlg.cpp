// PropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TConsole.h"
#include "TransparencyDlg.h"


// CTransparencyDlg dialog

IMPLEMENT_DYNAMIC(CTransparencyDlg, CDialog)
CTransparencyDlg::CTransparencyDlg(CWnd* pParent /*=NULL*/, int trans)
	: CDialog(CTransparencyDlg::IDD, pParent)
{
	m_nTransPos = trans;
}

CTransparencyDlg::~CTransparencyDlg()
{
}

void CTransparencyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
}


BEGIN_MESSAGE_MAP(CTransparencyDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CTransparencyDlg message handlers

BOOL CTransparencyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_slider.SetRange(0, 255);
	m_slider.SetTic(1);
	m_slider.SetPos(m_nTransPos);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

int CTransparencyDlg::GetTransparency() const
{
	return m_nTransPos;
}
void CTransparencyDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_nTransPos = m_slider.GetPos();
	OnOK();
}
