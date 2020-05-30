#pragma once
#include "redir.h"

class CEditRedirector :
	public CRedirector
{
public:
	CEditRedirector(void);
	~CEditRedirector(void);

public:
	CEdit* m_pWnd;

protected:
	// overrides:
	virtual void WriteStdOut(LPCSTR pszOutput);
	virtual void WriteStdError(LPCSTR pszError);
};
