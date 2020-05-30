#pragma once
#include <afxcmn.h>
#include <afxwin.h>

// CTransparencyDlg dialog

class CTransparencyDlg : public CDialog
{
	DECLARE_DYNAMIC(CTransparencyDlg)

public:
	CTransparencyDlg(CWnd* pParent = NULL, int trans = 255);   // standard constructor
	virtual ~CTransparencyDlg();
	int GetTransparency() const;

// Dialog Data
	enum { IDD = IDD_PROP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	CSliderCtrl m_slider;
	int m_nTransPos;
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();	
};
