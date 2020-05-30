#include "StdAfx.h"
#include "editredir.h"

CEditRedirector::CEditRedirector(void)
{
	m_pWnd = NULL;
}

CEditRedirector::~CEditRedirector(void)
{
}

void CEditRedirector::WriteStdOut(LPCSTR pszOutput)
{
	if (m_pWnd != NULL)
	{
		int nSize = m_pWnd->GetWindowTextLength();
		m_pWnd->SetSel(nSize, nSize);
		m_pWnd->ReplaceSel(pszOutput);		// add the message to the end of Edit control
	}
}

void CEditRedirector::WriteStdError(LPCSTR pszError)
{
	WriteStdOut("\r\nError message: ");
	WriteStdOut(pszError);
}
